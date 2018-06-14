//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
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
// $Header: /Alaska/BIN/Core/Modules/Recovery/Recovery.h 10    8/02/12 11:54a Artems $
//
// $Revision: 10 $
//
// $Date: 8/02/12 11:54a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Modules/Recovery/Recovery.h $
// 
// 10    8/02/12 11:54a Artems
// [TAG]  		EIP93520
// [Category]  	New Feature
// [Description]  	Support of Microsoft ESRT spec
// [Files]  		Recovery.h Recovery.sdl Recovery.c Reflash.c ReflashWorker.c
// Esrt.c
// 
// 9     5/13/11 4:46p Artems
// Removed RecoveryCapsuleName and RecoveryCapsuleSize constants
// All recovery modules should use GetRecoveryFileInfo instead
// 
// 8     11/25/09 4:46p Felixp
// sAmiRomFile renamed to RecoveryFileName
// FlashSize renamed ro RecoveryImageSize
// 
// 7     7/08/09 6:23p Artems
// Changed file header, minor code clean-up
// 
// 6     6/16/09 5:21p Artems
// EIP 21169 Added Eltorito support
// 
// 5     4/13/07 6:04p Ambikas
// Coding standard changes: udpated the year in the AMI copyright
// header/footer.
// 
// 4     6/28/06 12:44p Felixp
// OEM recovery type added
// 
// 3     4/13/06 2:03p Ambikas
// 
// 2     4/10/06 9:51a Ambikas
// 
// 1     12/01/05 9:35a Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:        Recovery.h
//
// Description:	Recovery devices guid definition
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __RECOVERY__H__
#define __RECOVERY__H__
#ifdef __cplusplus
extern "C" {
#endif

#include <PPI/DeviceRecoveryModule.h>
#include <PPI/DeviceRecoveryBlockIo.h>

//Serial port recovery
#define SERIAL_RECOVERY_CAPSULE_GUID \
	{ 0x699add70, 0x8554, 0x4993, { 0x83, 0xf6, 0xd2, 0xcd, 0xc0, 0x81, 0xdd, 0x85 } }

//Recovery from mass storage device with FAT file system
#define BLOCK_DEVICE_RECOVERY_CAPSULE_GUID \
	{ 0xba8263c, 0xa8bd, 0x4aad, { 0xb4, 0x2, 0x6a, 0x6a, 0xf2, 0xf7, 0xe7, 0x7d } }

// OEM Recovery
// {595A6EDC-6D2C-474a-9082-3B992851DFFE}
#define  OEM_RECOVERY_CAPSULE_GUID \
	{ 0x595a6edc, 0x6d2c, 0x474a, { 0x90, 0x82, 0x3b, 0x99, 0x28, 0x51, 0xdf, 0xfe } }

extern EFI_GUID guidRecoveryDevice;
extern EFI_GUID guidBlockDeviceCapsule;
extern EFI_GUID guidSerialCapsule;
extern EFI_GUID guidOemCapsule;

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************