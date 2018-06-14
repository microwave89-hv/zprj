//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**        5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093         **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/SwitchableGraphics/Sg TPV/Sg nVidia Optimus SMM/NvOptimusSMM.c 3     10/16/12 4:25a Joshchou $
//
// $Revision: 3 $
//
// $Date: 10/16/12 4:25a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/SwitchableGraphics/Sg TPV/Sg nVidia Optimus SMM/NvOptimusSMM.c $
// 
// 3     10/16/12 4:25a Joshchou
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Update for SA and ACPI RC 0.7.1
// [Files]  		NvOptimusSmm.c
// 
// 2     9/09/12 11:07p Joshchou
// [TAG]  		EIPNone
// [Category]  	Improvement
// [Description]  	Tpv module support for sharkbay.
// [Files]  		NvOptimusSMM.mak
// NvOptimusSMM.c
// NvOptimusSMM.dxs
// NvOptimusSMM.ssp
// NvOptimusSMM.asl
// NvOptimusSMM.cif
// 
//**********************************************************************
#include "Efi.h"
#include "token.h"
#include <AmiLib.h>
#include <AmiDxeLib.h>
#include <AmiCspLib.h>
#include <Protocol\SmmSwDispatch.h>
#include <Protocol\SmmBase.h>
#include <CmosAccess.h>
#include <Core\EM\CmosManager\CmosManager.h>

#include <SaGlobalNvsArea\SaGlobalNvsArea.h>


SYSTEM_AGENT_GLOBAL_NVS_AREA  *mSaGlobalNvsAreaPtr = NULL;
extern EFI_BOOT_SERVICES    *pBS;
//
// GUID Definitions
//
EFI_GUID mSwDispatchProtocolGuid = EFI_SMM_SW_DISPATCH_PROTOCOL_GUID;
EFI_GUID gSmmCmosServiceProtocolGuid = EFI_SMM_CMOS_ACCESS_GUID;
EFI_GUID gSaGlobalNvsAreaProtocolGuid = SYSTEM_AGENT_GLOBAL_NVS_AREA_PROTOCOL_GUID;

EFI_CMOS_MANAGER_INTERFACE    *CmosManager=NULL ;
VOID NvCmosFunction (EFI_HANDLE DispatchHandle,EFI_SMM_SW_DISPATCH_CONTEXT *DispatchContext );
VOID NvCmosFunction1 (EFI_HANDLE DispatchHandle,EFI_SMM_SW_DISPATCH_CONTEXT *DispatchContext );

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   NvCmosFunction
//
// Description: Write AcpiNvs->AudioCodec to CMOS:AudioCodec.
//
// Input:EFI_HANDLE                   DispatchHandle,
//       EFI_SMM_SW_DISPATCH_CONTEXT  *DispatchContext
//              
// Output:
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID NvCmosFunction (
        IN EFI_HANDLE                   DispatchHandle,
        IN EFI_SMM_SW_DISPATCH_CONTEXT  *DispatchContext )
{
        UINT8  CheckPoint;

        CheckPoint = (mSaGlobalNvsAreaPtr->SgFeatureList & 0x2) >> 1; // dGPUAudioCodec flag bit2
        CmosManager->Access.Write(&CmosManager->Access, CMOS_OEM_NVSWSMI_CODE, CheckPoint);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: NvCmosFunction1
//
// Description: Read CMOS:AudioCodec to AcpiNvs->AudioCodec.
//
// Input: EFI_HANDLE                   DispatchHandle,
//        EFI_SMM_SW_DISPATCH_CONTEXT  *DispatchContext
//
// Output:
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID NvCmosFunction1 (
        IN EFI_HANDLE                   DispatchHandle,
        IN EFI_SMM_SW_DISPATCH_CONTEXT  *DispatchContext )
{
        UINT8  CheckPoint;

        CmosManager->Access.Read(&CmosManager->Access, CMOS_OEM_NVSWSMI_CODE,&CheckPoint);
        mSaGlobalNvsAreaPtr->SgFeatureList |= (CheckPoint & 1) << 1; // dGPUAudioCodec flag bit2
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: InSmmFunction
//
// Description: InSmmFunction
//
// Input:      
//
// Output: 
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS InSmmFunction (EFI_HANDLE ImageHandle,EFI_SYSTEM_TABLE *SystemTable )
{
    EFI_STATUS Status;
    SYSTEM_AGENT_GLOBAL_NVS_AREA_PROTOCOL   *SaGlobalNvsAreaProtocol;
    EFI_SMM_SW_DISPATCH_PROTOCOL      *SwDispatch;
    EFI_SMM_SW_DISPATCH_CONTEXT        NvSwSmiContext = {SWSMI_NVOEM_CMOS_W};
    EFI_SMM_SW_DISPATCH_CONTEXT        NvSwSmiContext1 = {SWSMI_NVOEM_CMOS_R};
    EFI_HANDLE                         SwHandle;

    UINT8  CheckPoint;


    Status = pBS->LocateProtocol ( &mSwDispatchProtocolGuid, NULL, &SwDispatch );
    ASSERT_EFI_ERROR(Status);
    //
    //  Locate the Global NVS Protocol.
    //
    Status = pBS->LocateProtocol (&gSaGlobalNvsAreaProtocolGuid, NULL, &SaGlobalNvsAreaProtocol);
    ASSERT_EFI_ERROR (Status);
    if (EFI_ERROR (Status)) {
      return Status;
    } 
    mSaGlobalNvsAreaPtr = SaGlobalNvsAreaProtocol->Area;
    TRACE((-1,"AcpiNvs Addr->SgFeatureList = %X\n", &mSaGlobalNvsAreaPtr->SgFeatureList));

    LOCATE_CMOS_ACCESS_SMM_PROTOCOL(Status, CmosManager); 

    if (CmosManager != NULL)
    {
       Status = SwDispatch->Register( SwDispatch, NvCmosFunction, &NvSwSmiContext, &SwHandle);
       Status = SwDispatch->Register( SwDispatch, NvCmosFunction1, &NvSwSmiContext1, &SwHandle);
// Init dGPUAudioCodec flag
        CmosManager->Access.Read(&CmosManager->Access,CMOS_OEM_NVSWSMI_CODE,&CheckPoint);       
        mSaGlobalNvsAreaPtr->SgFeatureList |= (CheckPoint & 1) << 1; // dGPUAudioCodec flag bit2
    }

    return Status;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: NvSwSmiEntry
//
// Description: NvSwSmiEntry
//
// Input:       EFI_HANDLE           ImageHandle,
//              EFI_SYSTEM_TABLE     *SystemTable
//
// Output:
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS NvSwSmiEntry (
        IN EFI_HANDLE           ImageHandle,
        IN EFI_SYSTEM_TABLE      *SystemTable )
{
    InitAmiLib(ImageHandle,SystemTable);

    return InitSmmHandler( ImageHandle, SystemTable, InSmmFunction, NULL );
}

//**********************************************************************
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**        5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093         **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************