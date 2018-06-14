//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
//**                                                             **//
//**         (C)Copyright 2010, American Megatrends, Inc.        **//
//**                                                             **//
//**                     All Rights Reserved.                    **//
//**                                                             **//
//**   5555 Oakbrook Pkwy, Building 200,Norcross, Georgia 30093  **//
//**                                                             **//
//**                     Phone (770)-246-8600                    **//
//**                                                             **//
//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
// $Archive: /Alaska/BIN/Modules/AMITSE2_0/AMITSE/Inc/PwdLib.h $
//
// $Author: Arunsb $
//
// $Revision: 4 $
//
// $Date: 10/18/12 5:31a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/AMITSE2_0/AMITSE/Inc/PwdLib.h $
// 
// 4     10/18/12 5:31a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 5     10/10/12 12:23p Arunsb
// Synched the source for v2.16.1232 backup with Aptio
// 
// 3     2/19/10 12:59p Madhans
// Updated for TSE 2.01. Refer Changelog.log for File change history.
// 
// 3     2/19/10 7:59a Mallikarjunanv
// updated the year in copyright message
// 
// 2     10/28/09 5:34p Madhans
// 
// 1     6/04/09 7:49p Madhans
// AMI TSE Advanced.
// 
// 1     4/28/09 10:50p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 1     4/28/09 10:24p Madhans
// Tse 2.0 Code complete Checkin.
// 
//
//*****************************************************************//
//*****************************************************************//
//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		pwdlib.h
//
// Description:	password handling realted header
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef _PWDLIB_H_
#define _PWDLIB_H_

#define	AMI_PASSWORD_NONE	0
#define	AMI_PASSWORD_USER	1
#define	AMI_PASSWORD_ADMIN	2
#define	AMI_PASSWORD_ANY	3

UINT32
CheckSystemPassword(
IN OUT UINT32 EmptyPasswordType,
IN UINTN *NoOfRetries,
IN OUT UINTN *TimeOut
);

BOOLEAN CheckSystemPasswordPolicy(UINT32 PasswordInstalled);

UINT32 PasswordCheckInstalled( VOID );
VOID SetPasswordType( UINT32 PasswordType );

extern UINT32 gPasswordType; //Provides what is the current access level

// Internal Helper functions
// Used for HDD Security module.
VOID _DrawPasswordWindow(UINT16 PromptToken, UINTN PasswordLength, UINTN *CurrXPos, UINTN *CurrYPos);

VOID _ReportInBox(
        UINTN PasswordLength,
        UINT16 BoxToken,
        UINTN CurrXPos,
        UINTN CurrYPos,
        BOOLEAN bWaitForReturn
        );
EFI_STATUS _GetPassword(
        CHAR16 *PasswordEntered,
        UINTN PasswordLength,
        UINTN CurrXPos,
        UINTN CurrYPos,
        UINTN *TimeOut
        );

// Expected from IDE sec module.
extern UINT16 IDEPasswordGetName(UINT16 Index);
extern EFI_STATUS IDEPasswordAuthenticate( 
    CHAR16 *Password, 
    VOID* Ptr, 
    BOOLEAN bCheckUser 
);
extern BOOLEAN IDEPasswordUpdate( 
    UINT32 Index, 
    CHAR16 *Password, 
    BOOLEAN bCheckUser
);
extern VOID* IDEPasswordGetDataPtr( UINTN Index);
extern BOOLEAN IDEPasswordGetLocked(
    UINTN Index
);
extern VOID IDEPasswordCheck();
extern VOID  IDEPasswordFreezeDevices();
extern VOID UnlockHDD(VOID);
extern VOID SetHDDPassword(VOID);
extern VOID IDEUpdateConfig(
    VOID *TempideSecConfig, 
    UINTN value
);



#endif

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**         (C)Copyright 2010, American Megatrends, Inc.             **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**   5555 Oakbrook Pkwy, Building 200,Norcross, Georgia 30093       **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
