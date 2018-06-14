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
// $Header: /Alaska/BIN/Core/Include/ProcessorSubClass.h 2     10/11/05 11:19a Markw $
//
// $Revision: 2 $
//
// $Date: 10/11/05 11:19a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/ProcessorSubClass.h $
// 
// 2     10/11/05 11:19a Markw
// Added proc subclass version.
// 
// 1     10/10/05 4:25p Markw
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name: ProcessorSubClass.h
//
// Description:	ProcessorSubClass definitions.
//
//<AMI_FHDR_END>
//**********************************************************************

#ifndef __PROCESSOR_SUBCLASS_H__
#define __PROCESSOR_SUBCLASS_H__

#include <efi.h>
#include <DataHubSubClass.h>

#ifdef __cplusplus
extern "C" {
#endif

#define EFI_PROCESSOR_SUBCLASS_GUID \
	{0x26fdeb7e,0xb8af,0x4ccf,0xaa,0x97,0x2,0x63,0x3c,0xe4,0x8c,0xa7}

#define EFI_PROCESSOR_CLASS EFI_DATA_CLASS_DATA

#define EFI_PROCESSOR_SUBCLASS_VERSION		0x00010000


//Core Frequency
#define EFI_PROCESSOR_FREQUENCY_RECORD_NUMBER		0x00000001
typedef EFI_EXP_BASE10_DATA EFI_PROCESSOR_CORE_FREQUENCY_DATA;

//Front Side Bus Frequency
#define EFI_PROCESSOR_BUS_FREQUENCY_RECORD_NUMBER	0x00000002
typedef EFI_EXP_BASE10_DATA EFI_PROCESSOR_FSB_FREQUENCY_DATA;

//Version
#define EFI_PROCESSOR_VERSION_RECORD_NUMBER			0x00000003
typedef STRING_REF EFI_PROCESSOR_VERSION_DATA;

//Manufacturer
#define EFI_PROCESSOR_MANUFACTURER_RECORD_NUMBER	0x00000004
typedef STRING_REF EFI_PROCESSOR_MANUFACTURER_DATA;

//Serial Number
#define EFI_PROCESSOR_SERIAL_NUMBER_RECORD_NUMBER	0x00000005
typedef STRING_REF EFI_PROCESSOR_SERIAL_NUMBER_DATA;


//ID
#define EFI_PROCESSOR_ID_RECORD_NUMBER				0x00000006


typedef struct {
	UINT32 ProcessorSteppingId	:4;
	UINT32 ProcessorModel		:4;
	UINT32 ProcessorFamily		:4;
	UINT32 ProcessorType		:2;
	UINT32 ProcessorReserved1	:2;
	UINT32 ProcessorXModel		:4;
	UINT32 ProcessorXFamily		:8;
	UINT32 ProcessorReserved2	:4;
} EFI_PROCESSOR_SIGNATURE;

typedef struct {
	UINT32 ProcessorBrandIndex	:8;
	UINT32 ProcessorClflush		:8;
	UINT32 ProcessorReserved	:8;
	UINT32 ProcessorDfltApicId	:8;
} EFI_PROCESSOR_MISC_INFO;

typedef struct {
	UINT32 ProcessorFpu	:1;
	UINT32 ProcessorVme	:1;
	UINT32 ProcessorDe	:1;
	UINT32 ProcessorPse	:1;
	UINT32 ProcessorTsc	:1;
	UINT32 ProcessorMsr	:1;
	UINT32 ProcessorPae	:1;
	UINT32 ProcessorMce	:1;
	UINT32 ProcessorCx8	:1;
	UINT32 ProcessorApic:1;
	UINT32 ProcessorReserved1:1;
	UINT32 ProcessorSep	:1;
	UINT32 ProcessorMtrr:1;
	UINT32 ProcessorPge	:1;
	UINT32 ProcessorMca	:1;
	UINT32 ProcessorCmov:1;
	UINT32 ProcessorPat	:1;
	UINT32 ProcessorPse36:1;
	UINT32 ProcessorPsn	:1;
	UINT32 ProcessorClfsh:1;
	UINT32 ProcessorReserved2:1;
	UINT32 ProcessorDs	:1;
	UINT32 ProcessorAcpi:1;
	UINT32 ProcessorMmx	:1;
	UINT32 ProcessorFxsr:1;
	UINT32 ProcessorSse	:1;
	UINT32 ProcessorSse2:1;
	UINT32 ProcessorSs	:1;
	UINT32 ProcessorReserved3:1;
	UINT32 ProcessorTm	:1;
	UINT32 ProcessorReserved4:2;
} EFI_PROCESSOR_FEATURE_FLAGS;

typedef struct {
	EFI_PROCESSOR_SIGNATURE		Signature;
	EFI_PROCESSOR_MISC_INFO		MiscInfo;
	UINT32						Reserved;
	EFI_PROCESSOR_FEATURE_FLAGS	FeatureFlags;
} EFI_PROCESSOR_ID_DATA;

//Type
#define EFI_PROCESSOR_TYPE_RECORD_NUMBER			0x00000007
typedef enum {
	EfiProcessorOther	= 1,
	EfiProcessorUnknown	= 2,
	EfiCentralProcessor	= 3,
	EfiMathProcessor	= 4,
	EfiDspProcessor		= 5,
	EfiVideoProcessor	= 6
} EFI_PROCESSOR_TYPE_DATA;


//Family
#define EFI_PROCESSOR_FAMILY_RECORD_NUMBER			0x00000008
typedef enum {
	EfiProcessorFamilyOther					= 1,
	EfiProcessorFamilyUnknown				= 2,
	EfiProcessorFamily8086					= 3,
	EfiProcessorFamily80286					= 4,
	EfiProcessorFamilyIntel386				= 5,
	EfiProcessorFamilyIntel486				= 6,
	EfiProcessorFamily8087					= 7,
	EfiProcessorFamily80287					= 8,
	EfiProcessorFamily80387					= 9,
	EfiProcessorFamily80487					= 0x0A,
	EfiProcessorFamilyPentium				= 0x0B,
	EfiProcessorFamilyPentiumPro			= 0x0C,
	EfiProcessorFamilyPentiumII				= 0x0D,
	EfiProcessorFamilyPentiumMMX			= 0x0E,
	EfiProcessorFamilyCeleron				= 0x0F,
	EfiProcessorFamilyPentiumIIXeon			= 0x10,
	EfiProcessorFamilyPentiumIII			= 0x11,
	EfiProcessorFamilyM1					= 0x12,
	EfiProcessorFamilyM1Reserved1			= 0x13,
	EfiProcessorFamilyM1Reserved2			= 0x14,
	EfiProcessorFamilyM1Reserved3			= 0x15,
	EfiProcessorFamilyM1Reserved4			= 0x16,
	EfiProcessorFamilyM1Reserved5			= 0x17,
	EfiProcessorFamilyM1Reserved6			= 0x18,
	EfiProcessorFamilyK5					= 0x19,
	EfiProcessorFamilyK5Reserved1			= 0x1A,
	EfiProcessorFamilyK5Reserved2			= 0x1B,
	EfiProcessorFamilyK5Reserved3			= 0x1C,
	EfiProcessorFamilyK5Reserved4			= 0x1D,
	EfiProcessorFamilyK5Reserved5			= 0x1E,
	EfiProcessorFamilyK5Reserved6			= 0x1F,
	EfiProcessorFamilyPowerPC				= 0x20,
	EfiProcessorFamilyPowerPC601			= 0x21,
	EfiProcessorFamilyPowerPC603			= 0x22,
	EfiProcessorFamilyPowerPC603Plus		= 0x23,
	EfiProcessorFamilyPowerPC604			= 0x24,
	EfiProcessorFamilyAlpha2				= 0x30,
	EfiProcessorFamilyMips					= 0x40,
	EfiProcessorFamilySparc					= 0x50,
	EfiProcessorFamily68040					= 0x60,
	EfiProcessorFamily68xxx					= 0x61,
	EfiProcessorFamily68000					= 0x62,
	EfiProcessorFamily68010					= 0x63,
	EfiProcessorFamily68020					= 0x64,
	EfiProcessorFamily68030					= 0x65,
	EfiProcessorFamilyHobbit				= 0x70,
	EfiProcessorFamilyWeitek				= 0x80,
	EfiProcessorFamilyPARISC				= 0x90,
	EfiProcessorFamilyV30					= 0xA0,
	EfiProcessorFamilyPentiumIIIXeon		= 0xB0,
	EfiProcessorFamilyPentiumIIISpeedStep	= 0xB1,
	EfiProcessorFamilyPentium4				= 0xB2,
	EfiProcessorFamilyIntelXeon				= 0xB3,
	EfiProcessorFamilyAS400					= 0xB4,
	EfiProcessorFamilyIntelXeonMP			= 0xB5,
	EfiProcessorFamilyAMDAthlonXP			= 0xB6,
	EfiProcessorFamilyAMDAthlonMP			= 0xB7,
	EfiProcessorFamilyIBM390				= 0xC8,
	EfiProcessorFamilyG4					= 0xC9,
	EfiProcessorFamilyG5					= 0xCA,
	EfiProcessorFamilyi860					= 0xFA,
	EfiProcessorFamilyi960					= 0xFB
} EFI_PROCESSOR_TYPE;



//Volatage
#define EFI_PROCESSOR_VOLTAGE_RECORD_NUMBER			0x00000009
typedef EFI_EXP_BASE10_DATA EFI_PROCESSOR_VOLTAGE_DATA;

//Processor APIC ID
#define EFI_PROCESSOR_APIC_ID_RECORD_NUMBER			0x0000000B
typedef UINT32 EFI_PROCESSOR_APIC_ID_DATA;


//APIC Version Number
#define EFI_PROCESSOR_APIC_VER_NUMBER_RECORD_NUMBER	0x0000000C
typedef UINT32 EFI_PROCESSOR_APIC_VERSION_NUMBER_DATA;


//Microcode Update Revision
#define EFI_PROCESSOR_MICROCODE_REVISION_RECORD_NUMBER	0x0000000D

typedef enum {
	EfiProcessorIa32Microcode		= 1,
	EfiProcessorIpfPalAMicrocode	= 2,
	EfiProcessorIpfPalBMicrocode	= 3,
} EFI_PROCESSOR_MICROCODE_TYPE;

typedef struct {
	EFI_PROCESSOR_MICROCODE_TYPE	ProcessorMicrocodeType;
	UINT32							ProcessorMicrocodeRevisionNumber;
} EFI_PROCESSOR_MICROCODE_REVISION_DATA;



//Processor Status
#define EFI_PROCESSOR_STATUS_RECORD_NUMBER			0x0000000E

typedef struct {
	UINT32 CpuStatus		:3;
	UINT32 Reserved			:3;
	UINT32 SocketPopulated	:1;
	UINT32 Reserved2		:1;
	UINT32 ApicEnable		:1;
	UINT32 BootApplicationProcessor :1;
	UINT32 Reserved3		:22;
} EFI_PROCESSOR_STATUS_DATA;

typedef enum {
	EfiCpuStatusUnknown			= 0,
	EfiCpuStatusEnabled			= 1,
	EfiCpuStatusDisabledByUser	= 2,
	EfiCpuStatusDisabledbyBios	= 3,
	EfiCpuStatusIdle			= 4,
	EfiCpuStatusOther			= 7
} EFI_CPU_STATUS;

//Socket Type
#define EFI_PROCESSOR_SOCKET_TYPE_RECORD_NUMBER		0x0000000F

typedef enum {
	EfiProcessorSocketOther				= 1,
	EfiProcessorSocketUnknown			= 2,
	EfiProcessorSocketDaughterBoard		= 3,
	EfiProcessorSocketZIF				= 4,
	EfiProcessorSocketReplacePiggyBack	= 5,
	EfiProcessorSocketNone				= 6,
	EfiProcessorSocketLIF				= 7,
	EfiProcessorSocketSlot1				= 8,
	EfiProcessorSocketSlot2				= 9,
	EfiProcessorSocket370Pin			= 0xA,
	EfiProcessorSocketSlotA				= 0xB,
	EfiProcessorSocketSlotM				= 0xC,
	EfiProcessorSocket423				= 0xD,
	EfiProcessorSocketA462				= 0xE,
	EfiProcessorSocket478				= 0xF
} EFI_PROCESSOR_SOCKET_TYPE_DATA;


//Socket Name
#define EFI_PROCESSOR_SOCKET_NAME_RECORD_NUMBER		0x00000010
typedef STRING_REF EFI_PROCESSOR_SOCKET_NAME_DATA;


//Cache Association
#define EFI_SUBCLASS_ASSOCIATION_RECORD_NUMBER		0x00000011
typedef EFI_INTER_LINK_DATA EFI_CACHE_ASSOCIATION_DATA;

//Processor Maximum Frequency
#define EFI_PROCESSOR_MAX_FREQUENCY_RECORD_NUMBER	0x00000012
typedef EFI_EXP_BASE10_DATA EFI_PROCESSOR_MAX_FREQUENCY_DATA;


//Processor Asset Tag
#define EFI_PROCESSOR_ASSET_TAG_RECORD_NUMBER		0x000000013
typedef STRING_REF EFI_PROCESSOR_ASSET_TAG_DATA;


//Processor Maximum Bus Frequency
#define EFI_PROCESSOR_MAX_FSB_FREQUENCY_RECORD_NUMBER	0x000000014
typedef EFI_EXP_BASE10_DATA EFI_PROCESSOR_MAX_FSB_FREQUENCY_DATA;


//Processor Package Number
#define EFI_PROCESSOR_PACKAGE_NUMBER_RECORD_NUMBER	0x00000015
typedef UINTN EFI_PROCESSOR_PACKAGE_NUMBER_DATA;

//Core Frequency List
#define EFI_PROCESSOR_FREQUENCY_LIST_RECORD_NUMBER	0x00000016
typedef EFI_EXP_BASE10_DATA	*EFI_PROCESSOR_CORE_FREQUENCY_LIST_DATA;


//Front Side Bus Frequency List
#define EFI_PROCESSOR_BUS_FREQUENCY_LIST_RECORD_NUMBER	0x00000017
typedef EFI_EXP_BASE10_DATA *EFI_PROCESSOR_FSB_FREQUENCY_LIST_DATA;


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
