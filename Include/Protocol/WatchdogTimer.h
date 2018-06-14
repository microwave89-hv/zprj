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
// $Header: /Alaska/BIN/Core/CORE_DXE/ArchProtocol/WatchdogTimer.h 1     3/13/06 1:45a Felixp $
//
// $Revision: 1 $
//
// $Date: 3/13/06 1:45a $
//*****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/CORE_DXE/ArchProtocol/WatchdogTimer.h $
// 
// 1     3/13/06 1:45a Felixp
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
// 3     3/29/04 5:16p Felixp
// 
// 2     3/25/04 5:09p Robert
// Updated the watchdog protocols with correct values from the
// specification
// 
// 1     12/31/03 11:05a Robert
//
//*****************************************************************************
//<AMI_FHDR_START>
//
// Name:	WatchdogTimer.h
//
// Description:	This file contains Data structures and support values for the
//			Watchdog Timer Architectural Protocol
//
//<AMI_FHDR_END>
//*****************************************************************************
#ifndef __WATCHDOG_TIMER_ARCH_PROTOCOL_H__
#define __WATCHDOG_TIMER_ARCH_PROTOCOL_H__
#ifdef __cplusplus
extern "C" {
#endif
#include <EFI.h>

// GUID for the Timer Architectural Protocol
#define EFI_WATCHDOG_TIMER_ARCH_PROTOCOL_GUID \
  { 0x665E3FF5, 0x46CC, 0x11D4, 0x9A, 0x38, 0x00, 0x90, 0x27, 0x3F, 0xC1, 0x4D }

GUID_VARIABLE_DECLARATION(gEfiWatchdogTimerArchProtocolGuid, EFI_WATCHDOG_TIMER_ARCH_PROTOCOL_GUID);

// Declare an empty structure for the Timer Architectural Protocol
typedef struct _EFI_WATCHDOG_TIMER_ARCH_PROTOCOL EFI_WATCHDOG_TIMER_ARCH_PROTOCOL;


//<AMI_PHDR_START>
//============================================================================
// Procedure Type:	EFI_WATCHDOG_TIMER_NOTIFY
//
// Description:	  The function of this type is called from the Watchdog Notify
//		function.  This is the type defnition of the Registered Handler.
//
// Input:
//	  Time - Time since the last timer interrupt in 100 ns units.
//
// Output:	None
//
// Referrals:
//
//============================================================================
//<AMI_PHDR_END>
typedef
VOID
(EFIAPI *EFI_WATCHDOG_TIMER_NOTIFY) (
	IN UINT64 Timer
	);


//<AMI_PHDR_START>
//============================================================================
// Procedure Type:	EFI_WATCHDOG_NOTIFY
//
// Description:	  The function of this type is called when the watchdog Event
//		is signalled
//
// Input:
//	  Time - Time since the last timer interrupt in 100 ns units.
//
// Output:	None
//
// Referrals:
//
//============================================================================
//<AMI_PHDR_END>
typedef
VOID
(EFIAPI *EFI_WATCHDOG_NOTIFY) (
  IN EFI_EVENT	Event,
  IN VOID				*Context
  );


//<AMI_PHDR_START>
//============================================================================
// Procedure Type:	EFI_WATCHDOG_TIMER_REGISTER_HANDLER
//
// Description:	  The function of this type registers the notify function
//		that will be called if the timer interrupt fires
//
// Input:
//	  This - The instance of the EFI_WATCHDOG_TIMER_ARCH_PROTOCOL
//
//	  NotifyFunction - The function to call when a timer interrupt fires
//
// Output:	  EFI_SUCCESS           - The timer handler was registered.
//
// Referrals:
//
//============================================================================
//<AMI_PHDR_END>
typedef
EFI_STATUS
(EFIAPI *EFI_WATCHDOG_TIMER_REGISTER_HANDLER) (
  IN EFI_WATCHDOG_TIMER_ARCH_PROTOCOL	*This,
  IN EFI_WATCHDOG_TIMER_NOTIFY        	NotifyFunction
);


//<AMI_PHDR_START>
//============================================================================
// Procedure Type:	EFI_WATCHDOG_TIMER_SET_TIMER_PERIOD
//
// Description:	  The function of this type sets the timer interrupt interval
//		based on the input value in TimerPeriod
//
// Input:
//	  This - The instance of the EFI_WATCHDOG_TIMER_ARCH_PROTOCOL
//
//		TimerPeriod - The rate to program the timer interrupt in 100 nS units.
//
// Output:	  EFI_SUCCESS           - The timer handler was registered.
//
// Referrals:
//
//============================================================================
//<AMI_PHDR_END>
typedef
EFI_STATUS
(EFIAPI *EFI_WATCHDOG_TIMER_SET_TIMER_PERIOD) (
  IN EFI_WATCHDOG_TIMER_ARCH_PROTOCOL  *This,
  IN UINT64                          	 TimerPeriod
  );


//<AMI_PHDR_START>
//============================================================================
// Procedure Type:	EFI_WATCHDOG_TIMER_GET_TIMER_PERIOD
//
// Description:	  The function of this type gets the timer interrupt in
//		100ns increments
//
// Input:
//	  This - The instance of the EFI_WATCHDOG_TIMER_ARCH_PROTOCOL
//
//		*TimerPeriod - Pointer to the timer period in 100 nS units.
//
// Output:
//		EFI_SUCCESS           - The timer period was returned in TimerPeriod.
//		EFI_INVALID_PARAMETER - TimerPeriod is NULL.
//
// Referrals:
//
//============================================================================
//<AMI_PHDR_END>
typedef
EFI_STATUS
(EFIAPI *EFI_WATCHDOG_TIMER_GET_TIMER_PERIOD) (
  IN EFI_WATCHDOG_TIMER_ARCH_PROTOCOL		*This,
  IN UINT64                          		*TimerPeriod
  );




// Interface for the Timer Architectural Protocol
typedef struct _EFI_WATCHDOG_TIMER_ARCH_PROTOCOL {
  EFI_WATCHDOG_TIMER_REGISTER_HANDLER        RegisterHandler;
  EFI_WATCHDOG_TIMER_SET_TIMER_PERIOD        SetTimerPeriod;
  EFI_WATCHDOG_TIMER_GET_TIMER_PERIOD        GetTimerPeriod;
} EFI_WATCHDOG_TIMER_ARCH_PROTOCOL;

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
