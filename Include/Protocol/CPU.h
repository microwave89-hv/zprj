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
// $Header: /Alaska/BIN/Core/CORE_DXE/ArchProtocol/CPU.h 2     3/13/06 1:45a Felixp $
//
// $Revision: 2 $
//
// $Date: 3/13/06 1:45a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/CORE_DXE/ArchProtocol/CPU.h $
// 
// 2     3/13/06 1:45a Felixp
// 
// 1     1/28/05 12:44p Felixp
// 
// 2     1/18/05 3:21p Felixp
// PrintDebugMessage renamed to Trace
// 
// 1     12/23/04 9:42a Felixp
// 
// 1     12/23/04 9:29a Felixp
// 
// 1     1/05/04 4:07p Markw
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	Cpu.h
//
// Description:	This header defines the CPU Architecture protocol.
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __CPU_ARCH_PROTOCOL_H__
#define __CPU_ARCH_PROTOCOL_H__
#ifdef __cplusplus
extern "C" {
#endif

#define EFI_CPU_ARCH_PROTOCOL_GUID \
    {0x26baccb1,0x6f42,0x11d4,0xbc,0xe7,0x0,0x80,0xc7,0x3c,0x88,0x81}

GUID_VARIABLE_DECLARATION(gEfiCpuArchProtocolGuid, EFI_CPU_ARCH_PROTOCOL_GUID);

#ifndef GUID_VARIABLE_DEFINITION
#include <Protocol/DebugSupport.h>

typedef struct _EFI_CPU_ARCH_PROTOCOL EFI_CPU_ARCH_PROTOCOL;

typedef enum {
    EfiCpuFlushTypeWriteBackInvalidate,
    EfiCpuFlushTypeWriteBack,
    EfiCpuFlushTypeInvalidate,
    EfiCpuMaxFlushType
} EFI_CPU_FLUSH_TYPE;

typedef EFI_STATUS (EFIAPI *EFI_CPU_FLUSH_DATA_CACHE) (
    IN EFI_CPU_ARCH_PROTOCOL    *This,
    IN EFI_PHYSICAL_ADDRESS     Start,
    IN UINT64                   Length,
    IN EFI_CPU_FLUSH_TYPE       FlushType);

typedef EFI_STATUS (EFIAPI *EFI_CPU_ENABLE_INTERRUPT) (
    IN EFI_CPU_ARCH_PROTOCOL *This);

typedef EFI_STATUS (EFIAPI *EFI_CPU_DISABLE_INTERRUPT) (
    IN EFI_CPU_ARCH_PROTOCOL *This);

typedef EFI_STATUS (EFIAPI *EFI_CPU_GET_INTERRUPT_STATE) (
    IN EFI_CPU_ARCH_PROTOCOL *This,
    OUT BOOLEAN             *State);

    typedef enum {
        EfiCpuInit,
        EfiCpuMaxInitType
    } EFI_CPU_INIT_TYPE;

typedef EFI_STATUS (EFIAPI *EFI_CPU_INIT) (
    IN EFI_CPU_ARCH_PROTOCOL *This,
    IN EFI_CPU_INIT_TYPE InitType);


    typedef VOID (*EFI_CPU_INTERRUPT_HANDLER) (
        IN EFI_EXCEPTION_TYPE   InterruptType,
        IN EFI_SYSTEM_CONTEXT   SystemContext);

typedef EFI_STATUS (EFIAPI *EFI_CPU_REGISTER_INTERRUPT_HANDLER) (
    IN EFI_CPU_ARCH_PROTOCOL        *This,
    IN EFI_EXCEPTION_TYPE           InterruptType,
    IN EFI_CPU_INTERRUPT_HANDLER    InterruptHandler);

typedef EFI_STATUS (EFIAPI *EFI_CPU_GET_TIMER_VALUE) (
    IN EFI_CPU_ARCH_PROTOCOL    *This,
    IN UINT32                   TimerIndex,
    OUT UINT64                  *TimerValue,
    OUT UINT64                  *TimerPeriod OPTIONAL);

typedef EFI_STATUS (EFIAPI *EFI_CPU_SET_MEMORY_ATTRIBUTES) (
    IN EFI_CPU_ARCH_PROTOCOL *This,
    IN EFI_PHYSICAL_ADDRESS BaseAddress,
    IN UINT64 Length,
    IN UINT64 Attributes);


//**********************************************************************
//<AMI_SHDR_START>
//
// Name:        EFI_CPU_ARCH_PROTOCOL
//
// Description: CPU Architecture Protocol for modifing the Interrupt state,
//              Interrupt Handles, INIT CPU, Reading CPU timers, flush data
//              cache if needed for DMA, and setting Cache Attributes. 
//
// Fields:     Name        Type        Description
//        ------------------------------------------------------------
//        FlushDataCache            EFI_CPU_FLUSH_DATA_CACHE   
//        EnableInterrupt           EFI_CPU_ENABLE_INTERRUPT   
//        DisableInterrupt          EFI_CPU_DISABLE_INTERRUPT        
//        GetInterruptState         EFI_CPU_GET_INTERRUPT_STATE     
//        Init                      EFI_CPU_INIT       
//        RegisterInterruptHandler  EFI_CPU_REGISTER_INTERRUPT_HANDLER
//        GetTimerValue             EFI_CPU_GET_TIMER_VALUE                  
//        SetMemoryAttributes       EFI_CPU_SET_MEMORY_ATTRIBUTES              
//        NumberOfTimers            UINT32
//        DmaBufferAlignment        UINT32
//
//<AMI_SHDR_END>
//**********************************************************************
typedef struct _EFI_CPU_ARCH_PROTOCOL {
    EFI_CPU_FLUSH_DATA_CACHE            FlushDataCache;
    EFI_CPU_ENABLE_INTERRUPT            EnableInterrupt;
    EFI_CPU_DISABLE_INTERRUPT           DisableInterrupt;
    EFI_CPU_GET_INTERRUPT_STATE         GetInterruptState;
    EFI_CPU_INIT                        Init;
    EFI_CPU_REGISTER_INTERRUPT_HANDLER  RegisterInterruptHandler;
    EFI_CPU_GET_TIMER_VALUE             GetTimerValue;
    EFI_CPU_SET_MEMORY_ATTRIBUTES       SetMemoryAttributes;
    UINT32                              NumberOfTimers;
    UINT32                              DmaBufferAlignment;
} EFI_CPU_ARCH_PROTOCOL;

/****** DO NOT WRITE BELOW THIS LINE *******/
#endif // #ifndef GUID_VARIABLE_DEFINITION
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
