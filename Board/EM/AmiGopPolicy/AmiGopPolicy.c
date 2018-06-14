//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/AmiGopPolicy/AmiGopPolicy.c 6     5/15/14 2:22a Jameswang $
//
// $Revision: 6 $
//
// $Date: 5/15/14 2:22a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AmiGopPolicy/AmiGopPolicy.c $
// 
// 6     5/15/14 2:22a Jameswang
// [TAG]  		EIP168961
// [Category]  	Improvement
// [Description]  	Changed AmiGopOutputDp from AMI_GLOBAL_VARIABLE_GUID to
// AMI_GOP_POLICY_VARIABLE_GUID
// 
// 5     4/03/13 4:16a Josephlin
// Fixed CPU Exception Erro if EdidOverrideProtoco got call.
// 
// 4     12/18/12 11:03p Josephlin
// [TAG]  		EIP108311
// [Category]  	Improvement
// [Description]  	Create eLINK "OemGopEdidOverrideGetEdidList" for easy
// to implement EdidOverrideProtocol in project.
// [Files]  		AmiGopPolicy.c
// AmiGopPolicy.sdl
// AmiGopPolicy.mak
// AmiGopPolicyLib.c
// 
// 3     11/08/12 12:58a Josephlin
// [TAG]  		N/A
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	SCT Test Fail
// [RootCause]  	EFI_GLOBAL_VARIABLE guid is used in non EFI defined
// variable.
// [Solution]  	New guid AMI_GLOBAL_VARIABLE_GUID is created and used.
// [Files]  		AmiGopPolicy.c
// 
// 2     7/26/12 7:30a Josephlin
// Update File Header.
// 
// 1     6/29/12 3:43a Josephlin
// [TAG]  		EIP91970
// [Category]  	New Feature
// [Description]  	Initial Release for Display Switch with UEFI GOP driver
// support.
// [Files]  		AmiGopPolicy.cif
// AmiGopPolicy.c
// AmiGopPolicy.h
// AmiGopPolicy.mak
// AmiGopPolicy.sd
// AmiGopPolicy.sdl
// AmiGopPolicy.uni
// AmiGopPolicyLib.c
// AmiGopPolicySetup.c
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:        AmiGopPolicy.c
//
// Description:	AmiGopPolicy output initialization in the DXE stage.
//
//<AMI_FHDR_END>
//**********************************************************************

//----------------------------------------------------------------------
// Include(s)
//----------------------------------------------------------------------

#include <Efi.h>
#include <AmiLib.h>
#include <AmiDxeLib.h>
#include <AmiCspLib.h>
#include <Setup.h>
#include <token.h>

#include <Protocol\DevicePath.h>
#if OEM_EDID_OVERRIDE_PROTOCOL_SUPPORT
#include <Protocol\EdidOverride.h>
#endif
#include "AmiGopPolicy.h"

//----------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//----------------------------------------------------------------------
// Constant Definition(s)

// Macro Definition(s)

// Type Definition(s)

// Function Prototype(s)

#if OEM_EDID_OVERRIDE_PROTOCOL_SUPPORT
EFI_STATUS AmiGopEdidOverrideGetEdid (
  IN  EFI_EDID_OVERRIDE_PROTOCOL    *This,
  IN  EFI_HANDLE                    *ChildHandle,
  OUT UINT32                        *Attributes,
  IN OUT UINTN                      *EdidSize,
  IN OUT UINT8                      **Edid
);
#endif

//----------------------------------------------------------------------
// Variable and External Declaration(s)
//----------------------------------------------------------------------
// Variable Declaration(s)

// GUID Definition(s)

static EFI_GUID gAmiGopPolicyVariableGuid = AMI_GOP_POLICY_VARIABLE_GUID;    

// Protocol Definition(s)

#if OEM_EDID_OVERRIDE_PROTOCOL_SUPPORT
EFI_EDID_OVERRIDE_PROTOCOL EfiEdidOverrideProtocol = {
  AmiGopEdidOverrideGetEdid
};
#endif

// External Declaration(s)

// Function Definition(s)

VOID ConnectDevicePath(IN EFI_DEVICE_PATH_PROTOCOL *pPath);

//----------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Name:        ConnectAmiGopPolicyConOut
//
// Description: None.
//
// Input:       None.
//
// Output:      None.
//
// Notes:       None.
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

VOID ConnectAmiGopPolicyConOut (VOID)
{
	EFI_STATUS                  Status;
    EFI_DEVICE_PATH_PROTOCOL    *GopDevicePath = NULL;
    UINTN                       VariableSize = 0;

    Status = GetEfiVariable (
             L"AmiGopOutputDp",
             &gAmiGopPolicyVariableGuid,
             NULL,
             &VariableSize,
             &GopDevicePath);
    if ((EFI_ERROR(Status)) || (GopDevicePath == NULL)) return ;

    ConnectDevicePath(GopDevicePath);

    return;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:	AmiGopPolicyEntryPoint
//
// Description:	Installs GOP related protocols
//
// Input:
//	IN EFI_HANDLE        ImageHandle,
//	IN EFI_SYSTEM_TABLE  *SystemTable
//
// Output:
//	EFI_STATUS
//
// Modified:
//  None
//
// Referrals: InitAmiLib InstallMultipleProtocolInterfaces
//
// Notes:
//  Here is the control flow of this function:
//  1. Initialize Ami Lib.
//	2. Install Driver Binding Protocol
//  3. Return EFI_SUCCESS.
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS AmiGopPolicyEntryPoint (
    IN EFI_HANDLE       ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable )
{
    EFI_STATUS  Status = EFI_SUCCESS;
#if OEM_EDID_OVERRIDE_PROTOCOL_SUPPORT
    EFI_HANDLE  Handle = NULL;

    InitAmiLib( ImageHandle, SystemTable );

    Status = pBS->InstallMultipleProtocolInterfaces(
                  &Handle,
                  &gEfiEdidOverrideProtocolGuid,
                  &EfiEdidOverrideProtocol,
                  NULL );
#endif
    return Status;
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
