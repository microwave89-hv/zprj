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
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/AmtWrapper/AmtPetAlert/DevicePath.h 1     2/08/12 1:10a Klzhan $
//
// $Revision: 1 $
//
// $Date: 2/08/12 1:10a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/AmtWrapper/AmtPetAlert/DevicePath.h $
// 
// 1     2/08/12 1:10a Klzhan
// Initial Check in 
// 
// 1     2/25/11 1:45a Klzhan
// Initial Check-in
// 
// 1     12/03/10 5:11a Klzhan
// Initial Check-in.
//
//**********************************************************************
//
//<AMI_FHDR_START>
//---------------------------------------------------------------------------
// Name:		DevicePath.c
//
// Description:	DevicePath functions for AMT Pet Alert.
//
//---------------------------------------------------------------------------
//<AMI_FHDR_END>
#include "Tiano.h"
#include "EfiPrintLib.h"
#include "EfiDriverLib.h"

//
// Internal definitions
//
typedef struct {
  CHAR16  *str;
  UINTN   len;
  UINTN   maxlen;
} POOL_PRINT;

typedef struct {
  UINT8 Type;
  UINT8 SubType;
  VOID (*Function) (POOL_PRINT *, VOID *);
} DEVICE_PATH_STRING_TABLE;

//
// Define Maxmim characters that will be accepted
//
#define MAX_CHAR            480
#define MAX_CHAR_SIZE       (MAX_CHAR * 2)

#define MIN_ALIGNMENT_SIZE  4
#define ALIGN_SIZE(a)       ((a % MIN_ALIGNMENT_SIZE) ? MIN_ALIGNMENT_SIZE - (a % MIN_ALIGNMENT_SIZE) : 0)

CHAR16 *
DevicePathToStr (
  EFI_DEVICE_PATH_PROTOCOL     *DevPath
);

EFI_DEVICE_PATH_PROTOCOL *
BdsLibUnpackDevicePath (
    IN EFI_DEVICE_PATH_PROTOCOL *DevPath
);
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