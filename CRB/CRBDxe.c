//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

//*************************************************************************
// $Header: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/CRB/CRBDxe.c 2     4/16/13 5:27a Thomaschen $
//
// $Revision: 2 $
//
// $Date: 4/16/13 5:27a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/CRB/CRBDxe.c $
// 
// 2     4/16/13 5:27a Thomaschen
// 
// 1     2/12/12 10:38p Victortu
// Intel SharkBay CRB initially releases.
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:        CRBDXE.c
//
// Description: This file contains code for Chipset Reference Board Template
//              initialization in the DXE stage
//
//<AMI_FHDR_END>
//*************************************************************************

//---------------------------------------------------------------------------
// Include(s)
//---------------------------------------------------------------------------

#include <Efi.h>
#include <token.h>
#include <AmiLib.h>
#include <AmiDxeLib.h>
#include <Setup.h>
#include <Dxe.h>
#include <PCI.h>
#include <AmiHobs.h>
#include <AmiCspLib.h>

// Produced Protocols

// Consumed Protocols
#include <Protocol\PciIO.h>
#include <Protocol\PciRootBridgeIo.h>

#if ACPI_SUPPORT
 #if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x0001000A)
 #include <Protocol\S3SaveState.h>
 #else
 #include <Protocol\BootScriptSave.h>
 #endif
#endif

//---------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//---------------------------------------------------------------------------
// Constant Definition(s)

#if ACPI_SUPPORT
 #if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x0001000A)
 #define CRB_S3_SAVE_PROTOCOL EFI_S3_SAVE_STATE_PROTOCOL
 #define CRB_S3_SAVE_PROTOCOL_GUID gEfiS3SaveStateProtocolGuid
 #else
 #define CRB_S3_SAVE_PROTOCOL EFI_BOOT_SCRIPT_SAVE_PROTOCOL
 #define CRB_S3_SAVE_PROTOCOL_GUID gEfiBootScriptSaveGuid
 #endif
#endif

// Macro Definition(s)

// Type Definition(s)

// Function Prototype(s)

//---------------------------------------------------------------------------
// Variable and External Declaration(s)
//---------------------------------------------------------------------------
// Variable Declaration(s)

// GUID Definition(s)

// Protocol Definition(s)

// External Declaration(s)

// Function Definition(s)

//---------------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   CRBDXE_Init
//
// Description: This function is the entry point for CRB DXE driver.
//              This function initializes the CRB in DXE phase.
//
// Input:       ImageHandle - Image handle
//              SystemTable - Pointer to the system table
//
// Output:      EFI_SUCCESS
//
// Notes:       This routine is called very early, prior to SBDXE and NBDXE.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS CRBDXE_Init (
    IN EFI_HANDLE       ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable )
{
    EFI_STATUS              Status = EFI_SUCCESS;

    InitAmiLib(ImageHandle, SystemTable);

    return EFI_SUCCESS;
}

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
