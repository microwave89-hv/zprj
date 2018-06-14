//****************************************************************************
//****************************************************************************
//**                                                                        **
//**             (C)Copyright 1985-2014, American Megatrends, Inc.          **
//**                                                                        **
//**                          All Rights Reserved.                          **
//**                                                                        **
//**                 5555 Oakbrook Pkwy, Norcross, GA 30093                 **
//**                                                                        **
//**                          Phone (770)-246-8600                          **
//**                                                                        **
//****************************************************************************
//****************************************************************************
// $Header: /Alaska/SOURCE/Modules/HddSecurity/HddPassword/HddPassword.h 11    9/10/14 2:59a Divyac $
//
// $Revision: 11 $
//
// $Date: 9/10/14 2:59a $
//
//*****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/HddSecurity/HddPassword/HddPassword.h $
// 
// 11    9/10/14 2:59a Divyac
// [TAG]  		EIP181548 
// [Category]  	Improvement
// [Description]  	Implement event signaling during HDD Passwords Prompt.
// [Files]  		HddPassword.c
// HddPassword.h
// 
// 10    4/29/13 2:30a Kapilporwal
// fixing build errors, when tse soruce is not present, from last check-in
// 
// 9     4/25/13 9:28a Kapilporwal
// [TAG]  		EIP108583
// [Category]  	New Feature
// [Description]  	support set HDD password in same page
// [Files]  		IdeSecurity.cif, IdeSecurity.mak, IdeSecurity.sdl,
// IdeSecurity.uni, IdeSecurityCommon.sd, IdeSecuritySetup.c,
// HddPassword.c, HddPassword.h, HddPassword.mak, HddPassword.sdl
// 
// 8     6/28/11 6:24a Anandv
// [TAG]  		EIP62381
// [Category]  	Improvement
// [Description]  	In IdeSecurity Module, display HDD number in Setup
// based 
//                                on results from WhichIde() function of
// DiskInfo Protocol.
// 
// [Files]  		HddPassword.c, HddPassword.h, SBDxe.c, PIDEController.h
// 
// 7     5/21/10 2:58p Aaronp
// Fix for EIP 38473 - Device names are not displayed when built in UEFI
// 2.1 mode
// 
// 6     3/11/10 3:50a Rameshr
// Issue: Same Structure definied in Hddpassword and Amitse.
// Solution: Amitse created tsecommon.h with all the common definition.
// EIP: 27339
// 
// 5     1/15/10 10:11a Yul
// Coding Standard
//
// 4     9/28/09 4:59p Rameshr
//
// 3     9/21/09 3:48p Rameshr
// The data structure AMI_IFR_MSGBOX in HddPassword.h and MessageBox.h are
// not the same
// EIP 27157
//
// 2     7/27/09 5:37p Pats
// EIP 22925: Request to set HDD password length by token.
// Solution: Token added to IdeSecurity.sdl, and definition removed from
// HddPassword.h
//
// 1     5/01/09 11:09a Rameshr
// Initial Check-in
//*****************************************************************************//

//<AMI_FHDR_START>
//---------------------------------------------------------------------------
//
// Name: HddPassword.h
//
// Description:	Header file for the HddPassword
//
//---------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef _IDEPASSWORD_H_
#define _IDEPASSWORD_H_

#include "AmiStatusCodes.h"

#define IDE_SECURITY_INTERFACE_GUID \
    { 0xF4F63529, 0x281E, 0x4040, 0xA3, 0x13, 0xC1, 0xD6, 0x76, 0x63, 0x84,\
      0xBE }

#define HDD_SECURITY_END_PROTOCOL_GUID \
    { 0xad77ae29, 0x4c20, 0x4fdd, 0x85, 0x04, 0x81, 0x76, 0x61, 0x9b, 0x67,\
      0x6a }

#define HDD_UNLOCKED_GUID \
    { 0x1fd29be6, 0x70d0, 0x42a4, 0xa6, 0xe7, 0xe5, 0xd1, 0xe, 0x6a, 0xc3, 0x76};

#define HDD_PASSWORD_PROMPT_ENTER_GUID \
    { 0x8e8d584a, 0x6e32, 0x44bf, { 0xb9, 0x6e, 0x1d, 0x27, 0x7, 0xc4, 0xeb, 0x5c } }

#define HDD_PASSWORD_PROMPT_EXIT_GUID \
    { 0xe22af903, 0xfd6f, 0x4d22, { 0x94, 0xce, 0xf8, 0x49, 0xc6, 0x14, 0xc3, 0x45 } }

#define     SECURITY_SET_PASSWORD           0xF1
#define     SECURITY_UNLOCK                 0xF2
#define     SECURITY_ERASE_PREPARE          0xF3
#define     SECURITY_ERASE_UNIT             0xF4
#define     SECURITY_FREEZE_LOCK            0xF5
#define     SECURITY_DISABLE_PASSWORD       0xF6
#define     SECURITY_BUFFER_LENGTH          512     // Bytes

#define     SecuritySupportedMask       0x0001
#define     SecurityEnabledMask         0x0002
#define     SecurityLockedMask          0x0004
#define     SecurityFrozenMask          0x0008


#ifndef AMI_DXE_BS_EC_INVALID_IDE_PASSWORD
  #define AMI_DXE_BS_EC_INVALID_IDE_PASSWORD (AMI_STATUS_CODE_CLASS\
                                              | 0x00000005)
#endif

#ifndef DXE_INVALID_IDE_PASSWORD
  #define DXE_INVALID_IDE_PASSWORD (EFI_SOFTWARE_DXE_BS_DRIVER\
                                    | AMI_DXE_BS_EC_INVALID_IDE_PASSWORD)
#endif

#define NG_SIZE                     19
#define VARIABLE_ID_AMITSESETUP     5
#if !defined(SECUITY_SETUP_ON_SAME_PAGE) || SECUITY_SETUP_ON_SAME_PAGE == 0
#define INVALID_HANDLE  ((VOID*)-1)
#endif
#include "tsecommon.h"

#define EFI_DP_TYPE_MASK                    0x7F
#define EFI_DP_TYPE_UNPACKED                0x80
#if !defined(SECUITY_SETUP_ON_SAME_PAGE) || SECUITY_SETUP_ON_SAME_PAGE == 0
#define END_DEVICE_PATH_TYPE                0x7f
#define END_ENTIRE_DEVICE_PATH_SUBTYPE      0xff

#define DevicePathType( a )           (((a)->Type) & EFI_DP_TYPE_MASK)
#define DevicePathSubType( a )        ((a)->SubType)
#define DevicePathNodeLength( a )     (((a)->Length[0]) | ((a)->Length[1] << 8))
#define NextDevicePathNode( a )       ((EFI_DEVICE_PATH_PROTOCOL*) (((UINT8*) (\
                                                                         a))\
                                                                    +\
                                                                    DevicePathNodeLength( a )))
#define IsDevicePathEndType( a )      (\
                                                                    DevicePathType( \
            a ) == END_DEVICE_PATH_TYPE)
#define IsDevicePathEndSubType( a )   ((a)->SubType ==\
                                       END_ENTIRE_DEVICE_PATH_SUBTYPE)
#define IsDevicePathEnd( a )          (IsDevicePathEndType( a )\
                                       && IsDevicePathEndSubType( a ))
VOID
HddSecuritySignalProtocolEvent (
    IN  EFI_GUID    *ProtocolGuid
);

#endif

#endif /* _PASSWORD_H_ */

//****************************************************************************
//****************************************************************************
//**                                                                        **
//**             (C)Copyright 1985-2014, American Megatrends, Inc.          **
//**                                                                        **
//**                          All Rights Reserved.                          **
//**                                                                        **
//**                 5555 Oakbrook Pkwy, Norcross, GA 30093                 **
//**                                                                        **
//**                          Phone (770)-246-8600                          **
//**                                                                        **
//****************************************************************************
//****************************************************************************
