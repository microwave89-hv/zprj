//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2005, American Megatrends, Inc.         **
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
// $Header: /Alaska/BIN/Core/Include/CacheSubClass.h 2     6/29/10 2:05a Felixp $
//
// $Revision: 2 $
//
// $Date: 6/29/10 2:05a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/CacheSubClass.h $
// 
// 2     6/29/10 2:05a Felixp
// EFI_CACHE_ASSOCIATIVITY_DATA enum is extended with 32, 48, and 64 way
// values.
// 
// 1     10/10/05 4:45p Markw
// 
// 1     10/10/05 4:25p Markw
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name: CacheSubClass.h
//
// Description:	CacheSubClass definitions.
//
//<AMI_FHDR_END>
//**********************************************************************

#ifndef __CACHE_SUBCLASS_H__
#define __CACHE_SUBCLASS_H__

#include <efi.h>
#include <DataHubSubClass.h>

#ifdef __cplusplus
extern "C" {
#endif

#define EFI_CACHE_SUBCLASS_GUID \
	{0x7f0013a7,0xdc79,0x4b22,0x80,0x99,0x11,0xf7,0x5f,0xdc,0x82,0x9d}
#define EFI_CACHE_CLASS EFI_DATA_CLASS_DATA
#define EFI_CACHE_SUBCLASS_VERSION	0x00010000

//Size
#define EFI_CACHE_SIZE_RECORD_NUMBER			0x00000001
typedef EFI_EXP_BASE2_DATA EFI_CACHE_SIZE_DATA;

//Maximum Size
#define EFI_MAXIMUM_CACHE_SIZE_RECORD_NUMBER	0x00000002
typedef EFI_EXP_BASE2_DATA EFI_MAXIMUM_CACHE_SIZE_DATA;

//Speed
#define EFI_CACHE_SPEED_RECORD_NUMBER			0x00000003
typedef EFI_EXP_BASE10_DATA EFI_CACHE_SPEED_DATA;

//Socket
#define EFI_CACHE_SOCKET_RECORD_NUMBER			0x00000004
typedef STRING_REF EFI_CACHE_SOCKET_DATA;

//SRAM Type Supported
#define EFI_CACHE_SRAM_SUPPORT_RECORD_NUMBER	0x00000005
typedef struct {
	UINT16 Other		:1;
	UINT16 Unknown		:1;
	UINT16 NonBurst		:1;
	UINT16 Burst		:1;
	UINT16 PipelineBurst:1;
	UINT16 Asynchronous	:1;
	UINT16 Synchronous	:1;
	UINT16 Reserved		:9;
} EFI_CACHE_SRAM_TYPE_DATA;

//SRAM Type Installed
#define EFI_CACHE_SRAM_INSTALL_RECORD_NUMBER	0x00000006
typedef EFI_CACHE_SRAM_TYPE_DATA EFI_CACHE_SRAM_INSTALL_DATA;

//Error Correction Type Supported
#define EFI_CACHE_ERROR_SUPPORT_RECORD_NUMBER	0x00000007
typedef enum {
	EfiCacheErrorOther		= 1,
	EfiCacheErrorUnknown	= 2,
	EfiCacheErrorNone		= 3,
	EfiCacheErrorParity		= 4,
	EfiCacheErrorSingleBit	= 5,
	EfiCacheErrorMultiBit	= 6
} EFI_CACHE_ERROR_TYPE_DATA;

//Type
#define EFI_CACHE_TYPE_RECORD_NUMBER			0x00000008
typedef enum {
	EfiCacheTypeOther		= 1,
	EfiCacheTypeUnknown		= 2,
	EfiCacheTypeInstruction	= 3,
	EfiCacheTypeData		= 4,
	EfiCacheTypeUnified		= 5	
} EFI_CACHE_TYPE_DATA;

//Associativity
#define EFI_CACHE_ASSOCIATIVITY_RECORD_NUMBER	0x00000009
typedef enum {
	EfiCacheAssociativityOther			= 1,
	EfiCacheAssociativityUnknown		= 2,
	EfiCacheAssociativityDirectMapped	= 3,
	EfiCacheAssociativity2Way			= 4,
	EfiCacheAssociativity4Way			= 5,
	EfiCacheAssociativityFully			= 6,
	EfiCacheAssociativity8Way			= 7,
	EfiCacheAssociativity16Way			= 8,
	EfiCacheAssociativity32Way			= 9,
	EfiCacheAssociativity48Way			= 10,
	EfiCacheAssociativity64Way			= 11
} EFI_CACHE_ASSOCIATIVITY_DATA;


//Configuration
#define EFI_CACHE_CONFIGURATION_RECORD_NUMBER	0x0000000A;

//The following constants are associated with Level:
#define EFI_CACHE_L1 1
#define EFI_CACHE_L2 2
#define EFI_CACHE_L3 3

//The following constants are associated with Socketed:
#define EFI_CACHE_SOCKETED		1
#define EFI_CACHE_NOT_SOCKETED	0

//The following enumeration is associated with Location:
typedef enum {
	EfiCacheInternal = 0,
	EfiCacheExternal = 1,
	EfiCacheReserved = 2,
	EfiCacheUnknown  = 3
} EFI_CACHE_LOCATION;

//The following constants are associated with Enabled:
#define EFI_CACHE_ENABLED  1
#define EFI_CACHE_DISABLED 0

//The following enumeration is associated with OperationalMode:
typedef enum {
	EfiCacheWriteThrough	= 0,
	EfiCacheWriteBack		= 1,
	EfiCacheDynamicMode		= 2,
	EfiCacheUnknownMode		= 3
} EFI_CACHE_OPERATIONAL_MODE;


typedef struct {
	UINT32 Level		:3;
	UINT32 Socketed		:1;
	UINT32 Reserved2	:1;
	UINT32 Location		:2;
	UINT32 Enable		:1;
	UINT32 OperationalMode:2;
	UINT32 Reserved1	:22;
} EFI_CACHE_CONFIGURATION_DATA;


/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2005, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
