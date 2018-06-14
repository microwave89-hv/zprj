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
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/SwitchableGraphics/Sg TPV/Sg nVidia API/Mxm30Dxe.c 2     9/09/12 11:12p Joshchou $
//
// $Revision: 2 $
//
// $Date: 9/09/12 11:12p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/SwitchableGraphics/Sg TPV/Sg nVidia API/Mxm30Dxe.c $
// 
// 2     9/09/12 11:12p Joshchou
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Tpv module support for sharkbay.
// [Files]  		MXM30.mak
// Mxm30Dxe.dxs
// Mxm30Dxe.c
// Mxm30Efi.c
// NBCIEfi.c
// MxmInt15.asm
// MXM30.cif
// 
// 3     4/11/12 4:06a Alanlin
// Nvidia Optimus support when CSM module is disabled or CSM is never on
// setup menu.
// 
// 2     12/12/11 9:19p Alanlin
// [TAG]  		EIP74169
// [Category]  	Improvement
// [Description]  	Add OEMSSDT module part. Token "SGOEMSSDT_SUPPORT" to
// create OEM SSDT for discrete VGA card.
// When Primarydisplay = Auto or PEG, it can report OEM SSDT talbes for
// AMD or nVidia dGPU VGA card.
// 
// 1     6/27/11 5:25a Alanlin
// [TAG]  		EIP61848
// [Category]  	New Feature
// [Description]  	Initial check-in.Integrated SwitchableGraphics Intel
// Reference code 0.6.0
// [Files]  		MXM30.cif
// MXM30.sdl
// MXM30.mak
// Mxm30Dxe.dxs
// Mxm30Dxe.c
// Mxm30Efi.c
// NBCIEfi.c
// MxmInt15.asm
// Mxm30ElkCreek4.mxm
// Mxm30ElkCreekIII.mxm
// 
// 
// 2     9/23/10 1:04p Alexp
// comment out unused BDS callback defines
// 
// 1     9/17/10 1:16p Alexp
// [TAG]    	  EIP43103 
// [Category]  Function Request
// [Severity]	  Normal
// [Symptom]    Initial check-in of SgTPV module
// [RootCause] Request to implement SG reference code .
// [Solution]	Initial check-in. 
// [Files]	
//         Mxm30.cif;*.sdl;*.mak;
//         Mxm30Dxe.c;*.dxs 
//         Mxm30efi.c
//         MxmInt15.asm
//         NbciEfi.c
//         Mxm30ElkCreek3(4).mxm
// 
//**********************************************************************
//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		Mxm30DXE.c
//
// Description:	This file contains the etry point of EFI MXM30 Support driver
//              The function istalls MXM EFI, Legacy and Acpi interfaces if 
//              enabled in Setup
//              Installs Acpi Tables for Switchable Graphics
//
// Notes:		MAKE SURE NO PEI OR DXE SPECIFIC CODE IS NEEDED
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>
#include <Token.h>
#include <AmiDxeLib.h>
#include <DXE.h>
#include "SB.h"
#include "Setup.h"
#include <Protocol\Mxm30.h>
#if defined(CsmOptOut_SUPPORT) && (CsmOptOut_SUPPORT == 1)
#include <AmiLoadCsmPolicy.h>
#endif

#if ( defined(CSM_SUPPORT) && (CSM_SUPPORT != 0) )
#include <Protocol\LegacyBios.h>
#include <Protocol\LegacyRegion.h>
#include <Protocol\LegacyBiosExt.h>
#endif
#if defined(CsmOptOut_SUPPORT) && (CsmOptOut_SUPPORT == 1)
AMI_OPROM_POLICY_PROTOCOL     *gAmiOpRomPolicyProtocol = NULL;
EFI_GUID  gAmiOpromPolicyProtocolGuid = AMI_OPROM_POLICY_PROTOCOL_GUID;
#endif

extern EFI_BOOT_SERVICES    *pBS;
extern EFI_RUNTIME_SERVICES *pRS;

VOID    *gMxmLegMemAddr        = NULL;
UINTN    gMxmLegMemSize        = 0;

//#define BDS_ALL_DRIVERS_CONNECTED_PROTOCOL_GUID \
//    {0xdbc9fd21, 0xfad8, 0x45b0, 0x9e, 0x78, 0x27, 0x15, 0x88, 0x67, 0xcc, 0x93}

//EFI_EVENT               mMxmEvent;
//VOID                    *mMxmReg;
//EFI_GUID                gBdsAllDriversConnectedProtocolGuid = BDS_ALL_DRIVERS_CONNECTED_PROTOCOL_GUID;

// extern functions
EFI_STATUS MXM30Interfaces (EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE   *SystemTable);
//EFI_STATUS NBCIInterfaces (EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE   *SystemTable);

#if ( defined(CSM_SUPPORT) && (CSM_SUPPORT != 0) )
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   UpdateInt15MxMData
//
// Description: Get the address of MXM data buffer in legacy bios region
//
// Input:       EFI_LEGACY_BIOS_PROTOCOL            *LegacyBiosProtocol;
//       
//
// Output:      EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
UpdateInt15MxmSISData (
    IN EFI_LEGACY_BIOS_PROTOCOL         *LegacyBiosProtocol
)
{
    EFI_STATUS  Status;
    UINT32      Addr16;
    EFI_IA32_REGISTER_SET RegSet;
    UINT32 *ivt = (UINT32*)0;

    // Get the Data Pointer to MXM Structure within Int15 MXM handler
      MemSet(&RegSet, sizeof (EFI_IA32_REGISTER_SET), 0);
    RegSet.X.AX = 0x5f80;  
    RegSet.X.BX = 0xFF01;  
    RegSet.X.CX = EFI30_DataBlockID;  
    RegSet.X.ES = 0;
    RegSet.X.DI = 0;
    Addr16 = ivt[0x15];
    Status = LegacyBiosProtocol->FarCall86 (LegacyBiosProtocol,
                                (UINT16)(Addr16 >> 16),
                                (UINT16)Addr16,
                                &RegSet, 0, 0);
    Status = (RegSet.X.AX == 0x5F80 || RegSet.X.ES == 0)? EFI_UNSUPPORTED : EFI_SUCCESS;
    ASSERT_EFI_ERROR(Status);

// return updated address
    gMxmLegMemAddr = (UINT8*)((RegSet.X.ES << 4) + (RegSet.X.DI));

// TO DO. Expand the routine to obtain the address of _DOD buffer(MXM Int15 5f80, Func 9)

    return Status;
} 
#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   MxmDriverEntryPoint
//
// Description: Entry point of EFI MXM Support driver. The function istalls 
// 1. Install MXM protocol; 
// 2. Update data structure to be passed to Int15 binary
//      must support multiple MXM data modules. Dependent on controller's handle
//  Load MXM data block <1Mb area.
//      a. Copy MXM Structure below 1MB
//          1. Allocate Legacy mem space for MXM dat <1MB
//          OR          
//          2. Update the MXM data by the pointer returned by Int15 5F80 Func01(default)
//      b. Update the pointer to MXM data in EFI Protocol API
//      c. Create an ACPI SSDT table and copy MXM block there (ASL MXM logic must handle different MXM modules...)
//
// Input:       EFI_HANDLE           ImageHandle,
//              EFI_SYSTEM_TABLE     *SystemTable
//
// Output:      EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
MxmDriverEntryPoint (
    IN EFI_HANDLE         ImageHandle,
    IN EFI_SYSTEM_TABLE   *SystemTable
)
{
    EFI_STATUS  Status = EFI_SUCCESS;
    SETUP_DATA  SetupData;
    EFI_GUID    SetupGuid = SETUP_GUID;//SYSTEM_CONFIGURATION_GUID;
    EFI_GUID    EfiMxmStructGuid = MXMOEM1_GUID; 
//    MXM_STRUCT_HDR     *MxmHdr;

#if ( defined(CSM_SUPPORT) && (CSM_SUPPORT != 0) )
    EFI_LEGACY_BIOS_EXT_PROTOCOL    *BiosExtensions = NULL;
    EFI_LEGACY_BIOS_PROTOCOL        *LegacyBiosProtocol = NULL;
#endif
    VOID        *MxmData;
    UINTN       ImageSize, Size;
#if ( defined(CSM_SUPPORT) && (CSM_SUPPORT != 0) )
    UINT32      LockUnlockAddr, LockUnlockSize;
#endif
    EFI_STATUS  CsmOptOutStatus = EFI_SUCCESS;

    InitAmiLib(ImageHandle, SystemTable);
  TRACE((-1, "==============MxmDriverEntryPoint============\n"));
    //
    // Check if the module is enabled in Setup; if not - return EFI_UNSUPPORTED
    //
    Size = sizeof(SETUP_DATA);
    Status = pRS->GetVariable(L"Setup",
                            &SetupGuid,
                            NULL,
                            &Size,
                            &SetupData);
    if (EFI_ERROR(Status)) return Status;

    // Check to see if Primary Display is set to enable SG
    //
    if ((SetupData.PrimaryDisplay == 1)||  //PEG
        (SetupData.PrimaryDisplay == 3)||  //AUTO
        (SetupData.PrimaryDisplay == 4))   //SG
    { }
    else
        return EFI_UNSUPPORTED;
#if ( defined(CSM_SUPPORT) && (CSM_SUPPORT != 0) )
 #if defined(CsmOptOut_SUPPORT) && (CsmOptOut_SUPPORT == 1)
    CsmOptOutStatus = pBS->LocateProtocol(&gAmiOpromPolicyProtocolGuid, NULL, &gAmiOpRomPolicyProtocol);
 #endif
 if (!EFI_ERROR(CsmOptOutStatus)){
    Status = pBS->LocateProtocol(&gEfiLegacyBiosProtocolGuid, NULL, &LegacyBiosProtocol);
    if (EFI_ERROR(Status)) return Status;

    Status = pBS->LocateProtocol(&gEfiLegacyBiosExtProtocolGuid, NULL, &BiosExtensions);
    if (EFI_ERROR(Status)) return Status;
 }
#endif
// TBD. Proper Mxm structure block can be loaded based on matching dGPU's PCI Dev`ice/Vendor ID with the file Guid
// e.g. EfiMxmStructGuid = Nvidia Mxm, AMD Mxm etc.
// Also, multiple Mxm structure can be loaded if design supports 2 or more Mxm cards plugged in simultaneusly
// Latter scenario will require MxmInt15.asm changes

    Status = LoadFile(&EfiMxmStructGuid, &MxmData, &ImageSize);
    ASSERT_EFI_ERROR(Status);
    if (EFI_ERROR(Status)) return Status;
    // just in case we'll need to change MXM data
    //    MxmHdr = (MXM_STRUCT_HDR*)MxmData;
    //    if(Strcmp(MxmHdr->Sig,"*MXM_"))
    //        return EFI_UNSUPPORTED;

    gMxmLegMemAddr = (UINT8*)0xE0000;
    Size = 0x20000;

#if ( defined(CSM_SUPPORT) && (CSM_SUPPORT != 0) )
 if (!EFI_ERROR(CsmOptOutStatus)){
    BiosExtensions->UnlockShadow(
        (UINT8*)gMxmLegMemAddr, Size,
        &LockUnlockAddr, &LockUnlockSize);
 }
#endif

    gMxmLegMemAddr = MxmData;
    // Int15 may update gMxmLegMemAddr 
#if ( defined(CSM_SUPPORT) && (CSM_SUPPORT != 0) )
 if (!EFI_ERROR(CsmOptOutStatus)){
        // will copy MXM struct to the address returned by Int15 5F80, Func01
    Status = UpdateInt15MxmSISData(LegacyBiosProtocol);
    if (EFI_ERROR(Status)) { 
        return Status;
    }
/*
#else
    //
    // Allocate MXM and E000:0 area
    //
    Address = 0xE0000;
    Status = pBS->AllocatePages (
                AllocateAddress,
                EfiBootServicesCode,
                ImageSize,
                &gMxmLegMemAddr);
#endif
*/
    if (EFI_ERROR(Status)) { 
        BiosExtensions->LockShadow(LockUnlockAddr, LockUnlockSize);
        return Status;
    }

    gMxmLegMemSize = ImageSize;
    //
    // Copy the image into the shadow.
    //
    pBS->CopyMem(gMxmLegMemAddr, MxmData, gMxmLegMemSize);

    BiosExtensions->LockShadow(LockUnlockAddr, LockUnlockSize);

 } // (!EFI_ERROR(CsmOptOutStatus))
#endif // ( defined(CSM_SUPPORT) && (CSM_SUPPORT != 0) )
// Install NBCI & MXM3_EFI_PROTOCOL only if Primary Display is set to enable SG
#if SGOEMSSDT_SUPPORT
    if ((SetupData.PrimaryDisplay == 4) || (SetupData.PrimaryDisplay == 1) || (SetupData.PrimaryDisplay == 3))  //SG
#else
    if (SetupData.PrimaryDisplay == 4)   //SG
#endif
    { 

// Install NBCI_EFI_PROTOCOL, Int15 5F80 handle
//      Status = NBCIInterfaces(ImageHandle, SystemTable);
// Install MXM_EFI_PROTOCOL, Int15 5F80 handle
        Status = MXM30Interfaces(ImageHandle, SystemTable);
        ASSERT_EFI_ERROR (Status);
        if (EFI_ERROR(Status)) return Status;

// wait till Mxm PEG Card is enumerated in BDS
/*
        Status = RegisterProtocolCallback(
                  &gBdsAllDriversConnectedProtocolGuid,
            // Function is linked from MxmAcpiTable.c. Contains OEM implementation for Mxm Acpi table load
                  LoadAcpiTables,   
                  NULL,
                  &mMxmEvent,
                  &mMxmReg
                  );
    
*/
    }
    return Status;
}

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
