//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
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
// $Header: /Alaska/BIN/Chipset/Intel/NorthBridge/Haswell/Intel SystemAgent NB Chipset/NB Protocols/NBMemInfo.h 2     10/14/12 12:13a Jeffch $
//
// $Revision: 2 $
//
// $Date: 10/14/12 12:13a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Chipset/Intel/NorthBridge/Haswell/Intel SystemAgent NB Chipset/NB Protocols/NBMemInfo.h $
// 
// 2     10/14/12 12:13a Jeffch
// [TAG]         None
// [Severity]    Important
// [Description] Follow MahoBay Update.
// [Files]       NBMemInfo.h, NBPEI.c, PciHostBridge.c
// 
// 1     2/08/12 4:35a Yurenlai
// Intel Haswell/NB eChipset initially releases.
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:        NBMemInfo.h
//
// Description: The header file for NB Memory Information 
//
//<AMI_FHDR_END>
//*************************************************************************

#ifndef _NB_MEMORY_INFO_
#define _NB_MEMORY_INFO_

#ifdef __cplusplus
extern "C" {
#endif

#include <Token.h>

#define EFI_NB_MEMORY_INFO_GUID \
  {0x490216c0, 0x76a, 0x44d3, 0xa5, 0x36, 0xac, 0xe0, 0x5c, 0x90, 0xe3, 0x86}

// {40312829-7891-4abd-B200-0C541B061939}
#define EFI_NB_MRC_S3_DATA_GUID \
  {0x40312829, 0x7891, 0x4abd, 0xb2, 0x00, 0x0c, 0x54, 0x1b, 0x06, 0x19, 0x39}

GUID_VARIABLE_DECLARATION(gEfiNBMemoryInfoGuid, EFI_NB_MEMORY_INFO_GUID);

#define NB_MEMORY_INFO_VARIABLE L"NBMemoryInfo"

#pragma pack(push,1)


#pragma pack(pop)

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif

#endif

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
