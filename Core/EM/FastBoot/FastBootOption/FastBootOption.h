//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/PTT/FastBootOption/FastBootOption.h 1     10/30/12 4:22a Bibbyyeh $
//
// $Revision: 1 $
//
// $Date: 10/30/12 4:22a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/PTT/FastBootOption/FastBootOption.h $
// 
// 1     10/30/12 4:22a Bibbyyeh
// [TAG]           EIP105177
// [Category]      New Feature
// [Description]   Report pseudo boot option for Windows 'Boot To Device'
// support
// [Files]         FastBootOption.cif FastBootOption.sdl
// FastBootOption.mak FastBootOption.h FastBootOption.c
// FastBootOptionBds.c FastBootOption.dxs
// 
//
//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:    <FastBootOption.h>
//
// Description: This file contains the Includes, Definitions, typedefs,
//              Variable and External Declarations, Structure and
//              function prototypes needed for the IdeSecurity driver
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef _FastBootOption_
#define _FastBootOption_

#ifdef __cplusplus
extern "C" {
#endif

#include <Efi.h>
#include <Token.h>
#include <Dxe.h>
#include <AmiDxeLib.h>
#include <Protocol\Devicepath.h>

#if CORE_COMBINED_VERSION > 0x40280	//4.6.4.1 or Last
#define gBootName L"Boot%04X"		
#else
#define gBootName L"Boot%04x"
#endif

#define TempUefiHddDevice 0x80
#define TempUefiOddDevice 0x81
#define TempUefiRemDevice 0x82
#define TempUefiNetDevice 0x83

typedef struct {
	UINT16 DeviceTypeId;
	CHAR8 *TempName;
} TempDeviceMap;

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif

#endif

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
