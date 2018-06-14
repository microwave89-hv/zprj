//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**           5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093      **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/CSM/Generic/protocol/LegacyInterrupt.h 5     1/12/10 11:51a Olegi $
//
// $Revision: 5 $
//
// $Date: 1/12/10 11:51a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/CSM/Generic/protocol/LegacyInterrupt.h $
// 
// 5     1/12/10 11:51a Olegi
// Copyright message updated.
// 
// 4     4/27/07 5:17p Olegi
// CSM.CHM file preparation.
//
// 3     3/13/06 2:43p Felixp
//
// 2     1/18/05 3:22p Felixp
// PrintDebugMessage renamed to Trace
//
// 1     10/26/04 9:48a Olegi
//
// 2     8/24/04 3:56p Markw
// Fixed ifndef in *.h file.
//
// 1     8/24/04 3:55p Markw
//
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:            LegacyInterrupt.h
//
// Description:     Legacy Interrupt driver header file
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __LEGACY_INTERRUPT_PROTOCOL_H__
#define __LEGACY_INTERRUPT_PROTOCOL_H__
#ifdef __cplusplus
extern "C" {
#endif
#include <EFI.h>

// { 31CE593D-108A-485D-ADB2-78F21F2966BE }
#define EFI_LEGACY_INTERRUPT_PROTOCOL_GUID \
    {0x31ce593d,0x108a,0x485d,0xad,0xb2,0x78,0xf2,0x1f,0x29,0x66,0xbe}

GUID_VARIABLE_DECLARATION(gEfiLegacyInterruptProtocolGuid,EFI_LEGACY_INTERRUPT_PROTOCOL_GUID);

typedef struct _EFI_LEGACY_INTERRUPT_PROTOCOL EFI_LEGACY_INTERRUPT_PROTOCOL;

typedef EFI_STATUS (EFIAPI *EFI_LEGACY_INTERRUPT_GET_NUMBER_PIRQS) (
    IN EFI_LEGACY_INTERRUPT_PROTOCOL    *This,
    OUT UINT8                           *NumberPirqs
);

typedef EFI_STATUS (EFIAPI *EFI_LEGACY_INTERRUPT_GET_LOCATION) (
    IN EFI_LEGACY_INTERRUPT_PROTOCOL    *This,
    OUT UINT8                           *Bus,
    OUT UINT8                           *Device,
    OUT UINT8                           *Function
);

typedef EFI_STATUS (EFIAPI *EFI_LEGACY_INTERRUPT_READ_PIRQ) (
    IN EFI_LEGACY_INTERRUPT_PROTOCOL    *This,
    IN UINT8                            PirqNumber,
    OUT UINT8                           *PirqData
);

typedef EFI_STATUS (EFIAPI *EFI_LEGACY_INTERRUPT_WRITE_PIRQ) (
    IN EFI_LEGACY_INTERRUPT_PROTOCOL    *This,
    IN UINT8                            PirqNumber,
    IN UINT8                            PirqData
);


typedef struct _EFI_LEGACY_INTERRUPT_PROTOCOL {
    EFI_LEGACY_INTERRUPT_GET_NUMBER_PIRQS   GetNumberPirqs;
    EFI_LEGACY_INTERRUPT_GET_LOCATION       GetLocation;
    EFI_LEGACY_INTERRUPT_READ_PIRQ          ReadPirq;
    EFI_LEGACY_INTERRUPT_WRITE_PIRQ         WritePirq;
} EFI_LEGACY_INTERRUPT_PROTOCOL;


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
//**           5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093      **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
