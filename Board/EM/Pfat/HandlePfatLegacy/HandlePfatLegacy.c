//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.            **
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
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelPfat/Pfatflashlib/HandlePfatLegacy/HandlePfatLegacy.c 2     11/08/12 3:24a Fredericko $
//
// $Revision: 2 $
//
// $Date: 11/08/12 3:24a $
//
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelPfat/Pfatflashlib/HandlePfatLegacy/HandlePfatLegacy.c $
// 
// 2     11/08/12 3:24a Fredericko
// 
// 1     11/02/12 8:23p Fredericko
// [TAG]  		EIP105153
// [Files]  		HandlePfatLegacy.cif
// HandlePfatLegacy.sdl
// HandlePfatLegacy.mak
// HandlePfatLegacy.c
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:   HandlePfatLegacy.c
//
// Description: Code listing file for HandlePfatLegacy
//
//<AMI_FHDR_END>
//**********************************************************************

//----------------------------------------------------------------------
// Includes
#include <efi.h>
#include "token.h"
#include <AmiDxeLib.h>

EFI_EVENT   PfatLegacyBootEvent;

#define PFAT_VAR_GUID \
  { \
    0x6aae75ee, 0xa4bc, 0x40c8, 0x81, 0x3b, 0x8, 0x4e, 0x28, 0x53, 0x5e, 0x79 \
  }

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   HandlePfatOnLegacyBoot
//
// Description: Callback on LegacyBoot Event
//
// Input:       IN  EFI_EVENT       efiev
//              IN  VOID            *ctx
//
// Output:      EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************
void HandlePfatOnLegacyBoot(
    IN EFI_EVENT efiev,
    IN VOID      *ctx )
{
    EFI_STATUS Status;
    UINT32 PfatVar=0;
    UINTN  PfatVarSize = sizeof(UINT32);
    EFI_GUID PfatVarGuid = PFAT_VAR_GUID ;

    Status = pRS->GetVariable(L"PfatVariable", &PfatVarGuid, NULL, &PfatVarSize, &PfatVar);

    PfatVar+=1;

    Status = pRS->SetVariable(L"PfatVariable", 
                              &PfatVarGuid, 
                              (EFI_VARIABLE_BOOTSERVICE_ACCESS | 
                              EFI_VARIABLE_RUNTIME_ACCESS |
                              EFI_VARIABLE_NON_VOLATILE),
                              PfatVarSize,
                              &PfatVar);

     pBS->CloseEvent (PfatLegacyBootEvent);
}


//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:    HandlePfatLegacyBoot
//
// Description: Entry point for subcomponent
//
// Input:       IN    EFI_HANDLE ImageHandle,
//              IN    EFI_SYSTEM_TABLE *SystemTable
//
// Output: EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS HandlePfatLegacyBoot(
    IN EFI_HANDLE       ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable )
{
    EFI_STATUS                   Status;

    InitAmiLib( ImageHandle, SystemTable );

    Status = CreateReadyToBootEvent( TPL_CALLBACK,
                                     HandlePfatOnLegacyBoot,
                                     NULL,
                                     &PfatLegacyBootEvent );

    return Status;
}

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
