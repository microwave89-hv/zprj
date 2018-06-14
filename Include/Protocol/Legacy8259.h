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
// $Header: /Alaska/BIN/Core/Include/Protocol/Legacy8259.h 2     3/13/06 1:40a Felixp $
//
// $Revision: 2 $
//
// $Date: 3/13/06 1:40a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/Protocol/Legacy8259.h $
// 
// 2     3/13/06 1:40a Felixp
// 
// 1     1/28/05 12:44p Felixp
// 
// 2     1/18/05 3:22p Felixp
// PrintDebugMessage renamed to Trace
// 
// 1     12/23/04 9:41a Felixp
// 
// 1     7/13/04 2:33p Markw
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	
//
// Description:	
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __LEGACY8259_PROTOCOL_H__
#define __LEGACY8259_PROTOCOL_H__
#ifdef __cplusplus
extern "C" {
#endif
#include<EFI.h>

// {38321DBA-4FE0-4E17-8AEC-413055EAEDC1}
#define EFI_LEGACY_8259_PROTOCOL_GUID \
	{0x38321dba,0x4fe0,0x4e17,0x8a,0xec,0x41,0x30,0x55,0xea,0xed,0xc1}

GUID_VARIABLE_DECLARATION(gEfiLegacy8259ProtocolGuid,EFI_LEGACY_8259_PROTOCOL_GUID);

typedef struct _EFI_LEGACY_8259_PROTOCOL EFI_LEGACY_8259_PROTOCOL;


//************************************************
// EFI_8259_MODE
//************************************************
typedef enum {
	Efi8259LegacyMode,
	Efi8259ProtectedMode,
	Efi8259MaxMode
} EFI_8259_MODE;

//******************************************
// EFI_8259_IRQ
//******************************************
typedef enum {
	Efi8259Irq0,  Efi8259Irq1,
	Efi8259Irq2,  Efi8259Irq3,
	Efi8259Irq4,  Efi8259Irq5,
	Efi8259Irq6,  Efi8259Irq7,
	Efi8259Irq8,  Efi8259Irq9,
	Efi8259Irq10, Efi8259Irq11,
	Efi8259Irq12, Efi8259Irq13,
	Efi8259Irq14, Efi8259Irq15,
	Efi8259IrqMax
} EFI_8259_IRQ;


typedef EFI_STATUS (EFIAPI *EFI_LEGACY_8259_SET_VECTOR_BASE) (
	IN EFI_LEGACY_8259_PROTOCOL	*This,
	IN UINT8 					MasterBase,
	IN UINT8 					SlaveBase
);

typedef EFI_STATUS (EFIAPI *EFI_LEGACY_8259_GET_MASK) (
	IN EFI_LEGACY_8259_PROTOCOL	*This,
	OUT UINT16 					*LegacyMask			OPTIONAL,
	OUT UINT16 					*LegacyEdgeLevel	OPTIONAL,
	OUT UINT16 					*ProtectedMask		OPTIONAL,
	OUT UINT16 					*ProtectedEdgeLevel	OPTIONAL
);

typedef EFI_STATUS (EFIAPI *EFI_LEGACY_8259_SET_MASK) (
	IN EFI_LEGACY_8259_PROTOCOL	*This,
	IN UINT16 					*LegacyMask			OPTIONAL,
	IN UINT16 					*LegacyEdgeLevel	OPTIONAL,
	IN UINT16 					*ProtectedMask		OPTIONAL,
	IN UINT16 					*ProtectedEdgeLevel	OPTIONAL
);

typedef EFI_STATUS (EFIAPI *EFI_LEGACY_8259_SET_MODE) (
	IN EFI_LEGACY_8259_PROTOCOL	*This,
	IN EFI_8259_MODE			Mode,
	IN UINT16 					*Mask 		OPTIONAL,
	IN UINT16					*EdgeLevel	OPTIONAL
);

typedef EFI_STATUS (EFIAPI *EFI_LEGACY_8259_GET_VECTOR) (
	IN EFI_LEGACY_8259_PROTOCOL	*This,
	IN EFI_8259_IRQ 			Irq,
	OUT UINT8 					*Vector
);

typedef EFI_STATUS (EFIAPI *EFI_LEGACY_8259_ENABLE_IRQ) (
	IN EFI_LEGACY_8259_PROTOCOL	*This,
	IN EFI_8259_IRQ 			Irq,
	IN BOOLEAN 					LevelTriggered
);

typedef EFI_STATUS (EFIAPI *EFI_LEGACY_8259_DISABLE_IRQ) (
	IN EFI_LEGACY_8259_PROTOCOL	*This,
	IN EFI_8259_IRQ				Irq
);

typedef EFI_STATUS (EFIAPI *EFI_LEGACY_8259_GET_INTERRUPT_LINE) (
	IN EFI_LEGACY_8259_PROTOCOL	*This,
	IN EFI_HANDLE				PciHandle,
	OUT UINT8 					*Vector
);

typedef EFI_STATUS (EFIAPI *EFI_LEGACY_8259_END_OF_INTERRUPT) (
	IN EFI_LEGACY_8259_PROTOCOL	*This,
	IN EFI_8259_IRQ				Irq
);

typedef struct _EFI_LEGACY_8259_PROTOCOL {
	EFI_LEGACY_8259_SET_VECTOR_BASE	SetVectorBase;
	EFI_LEGACY_8259_GET_MASK			GetMask;
	EFI_LEGACY_8259_SET_MASK			SetMask;
	EFI_LEGACY_8259_SET_MODE			SetMode;
	EFI_LEGACY_8259_GET_VECTOR			GetVector;
	EFI_LEGACY_8259_ENABLE_IRQ			EnableIrq;
	EFI_LEGACY_8259_DISABLE_IRQ			DisableIrq;
	EFI_LEGACY_8259_GET_INTERRUPT_LINE	GetInterruptLine;
	EFI_LEGACY_8259_END_OF_INTERRUPT	EndOfInterrupt;
};

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
