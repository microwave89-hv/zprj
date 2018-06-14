//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
//**********************************************************************
//
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/MeWrapper/MeSetup/NfcSupportDxe/NfcSupportDxe.c 1     11/02/14 9:43p Tristinchou $
//
// $Revision: 1 $
//
// $Date: 11/02/14 9:43p $
//
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/MeWrapper/MeSetup/NfcSupportDxe/NfcSupportDxe.c $
// 
// 1     11/02/14 9:43p Tristinchou
// [TAG]  		EIP189985
// [Category]  	Improvement
// [Description]  	For ME 9.1.20.1035, add NFC related option in setup
// [Files]  		NfcSupportDxe.cif
// NfcSupportDxe.c
// NfcSupportDxe.h
// NfcSupportDxe.sdl
// NfcSupportDxe.dxs
// NfcSupportDxe.mak
//
//**********************************************************************
#if !defined(EDK_RELEASE_VERSION) || (EDK_RELEASE_VERSION < 0x00020000)
#include "EdkIIGlueDxe.h"
#include "HeciMsgLib.h"
#include EFI_PROTOCOL_DEFINITION (MeBiosPayloadData)
#include "MELib.h"
#include <token.h>
#endif

#include "NfcSupportDxe.h"

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MeSupportNfc
//
// Description:	This function determines ME firmware support enable/disable
//              NFC state. From ME 9.1.20.1035, ME firmware support this
//              feature.
//
// Input:       DXE_MBP_DATA_PROTOCOL *MbpDataProtocol
//
// Output:      BOOLEAN
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN
MeSupportNfc(
    IN DXE_MBP_DATA_PROTOCOL *MbpDataProtocol
)
{
    //If ME version is above 9.1.20.1035
    if( (MbpDataProtocol != NULL) &&
        ( (MbpDataProtocol->MeBiosPayload.FwVersionName.MajorVersion == 0x09) &&
          (MbpDataProtocol->MeBiosPayload.FwVersionName.MinorVersion == 0x01) &&
          ( (MbpDataProtocol->MeBiosPayload.FwVersionName.HotfixVersion >= 0x14) ||
            (MbpDataProtocol->MeBiosPayload.FwVersionName.BuildVersion >= 0x040B) ) ) )
    {
        return TRUE;
    }

    return FALSE;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	NfcSupportDxeEntryPoint
//
// Description:	Module entry point
//
// Input:       EFI_HANDLE       ImageHandle
//              EFI_SYSTEM_TABLE *SystemTable
//
// Output:      EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
NfcSupportDxeEntryPoint (
    IN EFI_HANDLE       ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable
)
{
    EFI_STATUS                  Status;
    DXE_MBP_DATA_PROTOCOL       *MbpData = NULL;
    UINT32                      VarAttr;
    UINTN                       VarSize;
    EFI_GUID                    NfcSupportDataGuid = NFC_SUPPORT_DATA_GUID;
    NFC_SUPPORT_DATA            NfcSupportData;
    MEFWCAPS_SKU                FwFeatureState;

    DEBUG ((EFI_D_INFO, "[NfcSupportDxe.c] : Entry Point...\n"));

    Status = gBS->LocateProtocol(
                    &gMeBiosPayloadDataProtocolGuid,
                    NULL,
                    (VOID**)&MbpData );
    if( EFI_ERROR(Status) )
        MbpData = NULL;

    VarAttr = 0;
    VarSize = sizeof( NFC_SUPPORT_DATA );
    Status = gRT->GetVariable (
                    L"NfcSupportData",
                    &NfcSupportDataGuid,
                    &VarAttr,
                    &VarSize,
                    &NfcSupportData );
    if( EFI_ERROR(Status) )
        VarAttr = EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_NON_VOLATILE;

    if( MbpData != NULL )
    {
        NfcSupportData.NFCCapability = MbpData->MeBiosPayload.FwCapsSku.FwCapabilities.Fields.NFC;;
        NfcSupportData.NFCDeviceType = MbpData->MeBiosPayload.NfcSupport.NfcData.DeviceType;
    }
    else
    {
        NfcSupportData.NFCCapability = 0;
        NfcSupportData.NFCDeviceType = 0;
    }

    Status = HeciGetFwFeatureStateMsg( &FwFeatureState );
    if( !EFI_ERROR(Status) )
        NfcSupportData.NFCState = FwFeatureState.Fields.NFC;
    else
        NfcSupportData.NFCState = 0;

    if( MeSupportNfc(MbpData) )
        NfcSupportData.MeSupportNFC = 1;
    else
        NfcSupportData.MeSupportNFC = 0;

    Status = gRT->SetVariable(
                    L"NfcSupportData",
                    &NfcSupportDataGuid,
                    VarAttr,
                    VarSize,
                    &NfcSupportData );
    if ( EFI_ERROR(Status) )
        return EFI_SUCCESS;

    //If ME support NFC and NFC capability is on
    if( (NfcSupportData.MeSupportNFC == 1) &&
        (NfcSupportData.NFCCapability == 1) )
    {
        if( (NfcSupportData.NFCEnableUpdate == 1) &&
            (NfcSupportData.NFCState != NfcSupportData.NFCEnable) )
        {
            if( NfcSupportData.NFCEnable == 1 )
                Status = HeciFwFeatureStateOverride( 0x80000000, 0 );
            else
                Status = HeciFwFeatureStateOverride( 0, 0x80000000 );

            Status = HeciSendCbmResetRequest(CBM_RR_REQ_ORIGIN_BIOS_POST, CBM_HRR_GLOBAL_RESET);
//            if( !EFI_ERROR(Status) )
//                EFI_DEADLOOP();
        }
    }

    return   EFI_SUCCESS;
}
//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************