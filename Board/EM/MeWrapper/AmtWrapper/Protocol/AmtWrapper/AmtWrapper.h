//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.            **
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
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/AmtWrapper/AmtWrapperProtocolLib/AmtWrapper/AmtWrapper.h 1     2/08/12 1:09a Klzhan $
//
// $Revision: 1 $
//
// $Date: 2/08/12 1:09a $
//
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/AmtWrapper/AmtWrapperProtocolLib/AmtWrapper/AmtWrapper.h $
// 
// 1     2/08/12 1:09a Klzhan
// Initial Check in 
// 
// 1     2/25/11 1:43a Klzhan
// Initial Check-in
// 
// 1     12/03/10 5:10a Klzhan
// Initial Check-in.
// 
//
//**********************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:            AmtWrapper.c
//
// Description:     Amt Wrapper Define file
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>
#ifndef _EFI_BDS_ASF_H
#define _EFI_BDS_ASF_H

#define EFI_AMT_WRAPPER_PROTOCOL_GUID  \
  	{ 0xd54f49f6, 0xdd4, 0x4276, 0xb0, 0x9c, 0xdf, 0xe1, 0xfd, 0x80, 0x85, 0xf0 }

EFI_FORWARD_DECLARATION (AMT_WRAPPER_PROTOCOL);

typedef
EFI_STATUS
(EFIAPI *AMT_WRAPPER_INIT) (
	EFI_HANDLE ImageHandle, 
	EFI_SYSTEM_TABLE *SystemTable
);

typedef
BOOLEAN
(EFIAPI *AMT_WRAPPER_GET) (
	UINTN Index, 
	VOID *pVar
);

typedef
BOOLEAN 
(EFIAPI *AMT_WRAPPER_SET) (
	UINTN Index, 
	VOID *pVar
);

typedef
BOOLEAN
(EFIAPI *ACTIVE_MANAGEMENT_ENABLE_KVM) (
  IN  VOID
);

typedef
BOOLEAN
(EFIAPI *AMT_INITIALIZATION_KVM) (
  IN  VOID
);

typedef
BOOLEAN
(EFIAPI *ACTIVE_MANAGEMENT_ENABLE_SOL) (
	IN  VOID
);

typedef
BOOLEAN
(EFIAPI *ACTIVE_MANAGEMENT_ENABLE_IDER) (
  	IN  VOID
);

/*
typedef
EFI_STATUS
(EFIAPI *AMT_WRAPPER_INITIALIZATION) (
    IN VOID
);
*/

typedef
EFI_STATUS
(EFIAPI *BDS_BOOT_VIA_ASF) (
  	IN  VOID
);

typedef
BOOLEAN
(EFIAPI *ACTIVE_MANAGEMENT_PAUSE_BOOT) (
  	IN  VOID
);

typedef
BOOLEAN
(EFIAPI *ACTIVE_MANAGEMENT_ENTER_SETUP) (
  	IN  VOID
);

typedef
BOOLEAN
(EFIAPI *ACTIVE_MANAGEMENT_CONSOLE_LOCKED) (
  	IN  VOID
);
typedef
EFI_STATUS
(EFIAPI *BDSLIB_UPDATE_CONSOLE_VARIABLE) (
  	IN  CHAR16                    *ConVarName,
  	IN  EFI_DEVICE_PATH_PROTOCOL  *CustomizedConDevicePath,
  	IN  EFI_DEVICE_PATH_PROTOCOL  *ExclusiveDevicePath
);
  
typedef struct _AMT_WRAPPER_PROTOCOL {
  AMT_WRAPPER_INIT                        AmtWrapperInit;
  AMT_WRAPPER_GET                         AmtWrapperGet;
  AMT_WRAPPER_SET                         AmtWrapperSet;
  ACTIVE_MANAGEMENT_ENABLE_SOL            ActiveManagementEnableSol;  
  ACTIVE_MANAGEMENT_ENABLE_IDER           ActiveManagementEnableIdeR;
  ACTIVE_MANAGEMENT_PAUSE_BOOT            ActiveManagementPauseBoot;
  ACTIVE_MANAGEMENT_ENTER_SETUP           ActiveManagementEnterSetup;
  //AMT_WRAPPER_INITIALIZATION            AsfSupportInit;
  BDS_BOOT_VIA_ASF                        BdsBootViaAsf;
  BDSLIB_UPDATE_CONSOLE_VARIABLE          BdsLibUpdateConsoleVariable;
  ACTIVE_MANAGEMENT_CONSOLE_LOCKED        ActiveManagementConsoleLocked;
  ACTIVE_MANAGEMENT_ENABLE_KVM            ActiveManagementEnableKvm;
  AMT_INITIALIZATION_KVM                  AmtInitializationKvm;
} AMT_WRAPPER_PROTOCOL;

#define GET_SOL_DP		1
#define GET_TIME_OUT	2					// return UINT16
#define GET_BOOT_OPTION	3					// return UINT16
#define GET_IS_SOL		4					// return UINT16
#define GET_IS_IDER		5					// return UINT16

#define SET_BIOS_WDT_START	1
#define SET_WDT_STOP		2
#define SET_OS_SOL			3
#define SET_OS_WDT_START	4

#endif //_EFI_HECI_H
//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************