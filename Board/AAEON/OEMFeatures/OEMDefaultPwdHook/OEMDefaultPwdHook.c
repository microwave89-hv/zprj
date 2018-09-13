//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2008, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
// $Header: $
//
// $Revision: $
//
// $Date: $
//**********************************************************************
// Revision History
// ----------------
// $Log: $
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	<This File Name>
//
// Description:	
//
//<AMI_FHDR_END>
//**********************************************************************

#include "token.h"
#include <EFI.h>
#include <AMIVfr.h>
#include <Protocol/SimpleTextIn.h>
#include <Protocol/EfiOEMBadging.h>

#if EFI_SPECIFICATION_VERSION>0x20000
#include <UefiHii.h>
#include <Protocol/HiiDatabase.h>
#include <Protocol/HiiString.h>
#else
#include <Protocol/Hii.h>
#endif //EFI_SPECIFICATION_VERSION>0x20000

#include "commonoem.h"

extern VOID PasswordEncodeHook( CHAR16 *Password, UINTN MaxSize);
extern VOID *VarGetNvramName( CHAR16 *name, EFI_GUID *guid, UINT32 *attributes, UINTN *size );
extern EFI_STATUS VarSetNvramName( CHAR16 *name, EFI_GUID *guid, UINT32 attributes, VOID *buffer, UINTN size );
extern VOID *VarGetNvram( UINT32 variable, UINTN *size );
extern EFI_STATUS VarSetNvram( UINT32 variable, VOID *buffer, UINTN size );
extern VOID *EfiLibAllocateZeroPool ( IN  UINTN   AllocationSize);
extern VOID MemFreePointer( VOID **ptr );
extern VOID
    EfiStrCpy (
      IN CHAR16   *Destination,
      IN CHAR16   *Source
      );
extern VOID MemCopy( VOID *dest, VOID *src, UINTN size );
extern VOID MemSet( VOID *buffer, UINTN size, UINT8 value );

extern EFI_RUNTIME_SERVICES			*gRT;


#define	VARIABLE_ID_AMITSESETUP     5
#define ___INTERNAL_CONVERT_TO_WSTRING___(a) L#a
#define CONVERT_TO_WSTRING(a) ___INTERNAL_CONVERT_TO_WSTRING___(a)

VOID OemSetDefaultPasswordHook(VOID)
{
	EFI_STATUS Status;
	//CHAR16 *AdminPassword, *UserPassword;
	CHAR16 *AdminPassword;
	#if defined(USER_PASSWORD_SUPPORT) && (USER_PASSWORD_SUPPORT == 1)
	CHAR16 *UserPassword;
	#endif
	CHAR16 *EncPass=NULL;
	const UINTN TsePasswordLength = SETUP_PASSWORD_LENGTH;
	
	EFI_GUID    AmiTseSetupGuid = AMITSESETUP_GUID;
	AMITSESETUP AmiTseSetup;
	UINT32 Attrib=0;
	UINTN Size=0;
	
	UINT16   Buffer;
	EFI_GUID EfiGlobalVariableGuid = EFI_GLOBAL_VARIABLE_GUID;
	
	Size = sizeof(UINT16);

	// Check first boot
	Status = gRT->GetVariable(L"OemFirstBoot", &EfiGlobalVariableGuid, NULL, &Size, &Buffer);
	if (EFI_ERROR(Status))
	{
	    Buffer = 1;
	    Status = gRT->SetVariable(L"OemFirstBoot", 
	                    &EfiGlobalVariableGuid, 
	                    EFI_VARIABLE_NON_VOLATILE | 
	                    EFI_VARIABLE_BOOTSERVICE_ACCESS | 
	                    EFI_VARIABLE_RUNTIME_ACCESS,    
	                    Size, 
	                    &Buffer);
	}
	else
        	return;
    
	// Initial 
	AdminPassword = EfiLibAllocateZeroPool((TsePasswordLength + 1)*sizeof(CHAR16));
	#if defined(USER_PASSWORD_SUPPORT) && (USER_PASSWORD_SUPPORT == 1)
	UserPassword = EfiLibAllocateZeroPool((TsePasswordLength + 1)*sizeof(CHAR16));
	#endif
	EncPass = EfiLibAllocateZeroPool((TsePasswordLength + 1)*sizeof(CHAR16));
    
	AdminPassword = CONVERT_TO_WSTRING(DEFAULT_ADMIN_PASSWORD);
	#if defined(USER_PASSWORD_SUPPORT) && (USER_PASSWORD_SUPPORT == 1)
	UserPassword = CONVERT_TO_WSTRING(DEFAULT_USER_PASSWORD);
	#endif
	
	// Get Setting	
	Size = sizeof(AMITSESETUP);
	Status = gRT->GetVariable(L"AMITSESetup", &AmiTseSetupGuid, &Attrib, &Size, &AmiTseSetup);

	// Set Admin password
	EfiStrCpy( EncPass, AdminPassword );
	PasswordEncodeHook( EncPass, TsePasswordLength*sizeof(CHAR16));
	MemCopy(&AmiTseSetup.AdminPassword, EncPass, TsePasswordLength*sizeof(CHAR16));

	// Clear EncPass buffer
	MemSet(EncPass, (TsePasswordLength + 1)*sizeof(CHAR16), 0);
    
	#if defined(USER_PASSWORD_SUPPORT) && (USER_PASSWORD_SUPPORT == 1)
	// Set user password
	EfiStrCpy( EncPass, UserPassword);
	PasswordEncodeHook( EncPass, TsePasswordLength*sizeof(CHAR16));
	MemCopy(&AmiTseSetup.UserPassword, EncPass, TsePasswordLength*sizeof(CHAR16));
	#endif
    
	Status = gRT->SetVariable(L"AMITSESetup", &AmiTseSetupGuid, Attrib, Size, &AmiTseSetup);
	
	// Free all pool
	MemFreePointer((VOID**) &EncPass);
	MemFreePointer((VOID**) &AdminPassword);
	#if defined(USER_PASSWORD_SUPPORT) && (USER_PASSWORD_SUPPORT == 1)
	MemFreePointer((VOID**) &UserPassword);
	#endif
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2008, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
