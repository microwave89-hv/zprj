//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
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
// $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/SB Protocols/SbHpet.h 1     11/19/13 7:27a Barretlin $
//
// $Revision: 1 $
//
// $Date: 11/19/13 7:27a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/SB Protocols/SbHpet.h $
// 
// 1     11/19/13 7:27a Barretlin
// [TAG]  		EIP141917
// [Category]  	New Feature
// [Description]  	Support SetTimer() with HPET Timer on Lynx Point
// [Files]  		SB.sdl SBGeneric.c SBDxe.c SbHpet.h SamrtTimer.sdl
// 
// 6     1/13/10 2:13p Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:  SbHPET.h
//
// Description:	High Precision Event Timer register definitions.
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __SB_HPET__H__
#define __SB_HPET__H__
#ifdef __cplusplus
extern "C" {
#endif

#include <Efi.h>

//----------------------------------------------------------------------------
// High Precision Event Timer Registers
//----------------------------------------------------------------------------
// HPET General Register Offsets
#define HPET_GENERAL_CAPABILITIES_ID_OFFSET     0x000
#define HPET_GENERAL_CONFIGURATION_OFFSET       0x010
#define HPET_GENERAL_INTERRUPT_STATUS_OFFSET    0x020
// HPET Timer Register Offsets
#define HPET_MAIN_COUNTER_OFFSET                0x0F0
#define HPET_TIMER_CONFIGURATION_OFFSET         0x100
#define HPET_TIMER_COMPARATOR_OFFSET            0x108
#define HPET_TIMER_MSI_ROUTE_OFFSET             0x110
// Stride between sets of HPET Timer Registers
#define HPET_TIMER_STRIDE                       0x020

#pragma pack(push,1)

// HPET General Capabilities and ID Register
typedef union {
  struct {
    UINT32  Revision:8;
    UINT32  NumberOfTimers:5;
    UINT32  CounterSize:1;
    UINT32  Reserved0:1;
    UINT32  LegacyRoute:1;
    UINT32  VendorId:16;
    UINT32  CounterClockPeriod:32;
  } Bits;
  UINT64  Uint64;
} HPET_GENERAL_CAPABILITIES_ID_REGISTER;

// HPET General Configuration Register
typedef union {
  struct {
    UINT32  MainCounterEnable:1;
    UINT32  LegacyRouteEnable:1;
    UINT32  Reserved0:30;
    UINT32  Reserved1:32;
  } Bits;
  UINT64  Uint64;
} HPET_GENERAL_CONFIGURATION_REGISTER;

// HPET General Interrupt Status Register
typedef union {
  struct {
    UINT32  Timer0InterruptActive:1;
    UINT32  Timer1InterruptActive:1;		
    UINT32  Timer2InterruptActive:1;
    UINT32  Reserved0:29;
    UINT32  Reserved1:32;
  } Bits;
  UINT64  Uint64;
} HPET_GENERAL_INTERRUPT_STATUS_REGISTER;

// HPET Timer Configuration Register
typedef union {
  struct {
    UINT32  Reserved0:1;
    UINT32  LevelTriggeredInterrupt:1;
    UINT32  InterruptEnable:1;
    UINT32  PeriodicInterruptEnable:1;
    UINT32  PeriodicInterruptCapablity:1;
    UINT32  CounterSizeCapablity:1;
    UINT32  ValueSetEnable:1;
    UINT32  Reserved1:1;
    UINT32  CounterSizeEnable:1;
    UINT32  InterruptRoute:5;
    UINT32  MsiInterruptEnable:1;
    UINT32  MsiInterruptCapablity:1;
    UINT32  Reserved2:16;
    UINT32  InterruptRouteCapability;
  } Bits;
  UINT64  Uint64;
} HPET_TIMER_CONFIGURATION_REGISTER;

// HPET Timer MSI Route Register
typedef union {
  struct {
    UINT32  Value:32;
    UINT32  Address:32;
  } Bits;
  UINT64  Uint64;
} HPET_TIMER_MSI_ROUTE_REGISTER;

#if defined(HPET_APIC_INTERRUPT_MODE) && (HPET_APIC_INTERRUPT_MODE != 0)
//-------------------------
// HPET APIC Support
//-------------------------
#define IO_APIC_REDIR_TABLE_LOW 0x10 // Reditection Table Low 32 bits.
#define IO_APIC_REDIR_TABLE_HIGH 0x11 // Reditection Table High 32 bits.

#define APIC_EOI_REGISTER 0xB0
#define APIC_PPR_REGISTER 0xA0
#define APIC_APR_REGISTER 0x90
#define APIC_ISR_REGISTER 0x100
#define ISR_REG(v) (APIC_ISR_REGISTER + (v / 32) * 0x10)
#define ISR_BIT(v) (UINT32) (1 << (v % 32))

struct IO_APIC {
	UINT8   Index;
    UINT8   Unused[3];
	UINT32  Unused1[3];
	UINT32  Data;
	UINT32  Unused2[11];
	UINT32  Eoi;
};

typedef struct {
	UINT32  Vector			:  8,
			DeliveryMode	:  3,
			DestMode		:  1,
			DeliveryStatus	:  1,
			Polarity		:  1,
			Irr				:  1,
			Trigger			:  1,
			Mask			:  1,
			__Reserved_2	: 15;

	UINT32	__Reserved_3	: 24,
			Dest			:  8;
} IO_APIC_ROUTE_ENTRY;

union ENTRY_UNION {
	struct { UINT32 W1, W2; };
	IO_APIC_ROUTE_ENTRY Entry;
};

//---------------------------------------------------------------------------
struct IO_APIC* IoApicBase( VOID );

EFI_STATUS IoApicWrite (
    IN UINT8        Reg,
    IN UINT32       Value
);

UINT32 IoApicRead(
    IN UINT8        Reg
);

EFI_STATUS IoApicEnableIrq (
    IN UINT8        Irq,
    IN BOOLEAN      LevelTriggered,
    IN BOOLEAN      Polarity
);

EFI_STATUS
IoApicDisableIrq (
  IN UINT8 Irq
  );

EFI_STATUS IoApicEoi (
    IN UINT8        Irq
);

EFI_STATUS IoApicMaskIrq (
    IN UINT8        Irq
);

EFI_STATUS IoApicUnmaskIrq (
    IN UINT8        Irq
);

UINT8 GetHpetApicPin ( VOID );

BOOLEAN IsHpetApicEnable ( VOID );

#endif

#pragma pack(pop)

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
