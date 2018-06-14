//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1987-2013, American Megatrends, Inc.            **
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
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/Haswell/AMI Cpu PKG/CPU Core/CpuProtocols/MpService/MpService.h 2     2/23/12 2:05a Davidhsieh $
//
// $Revision: 2 $
//
// $Date: 2/23/12 2:05a $
//*****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/Haswell/AMI Cpu PKG/CPU Core/CpuProtocols/MpService/MpService.h $
// 
// 2     2/23/12 2:05a Davidhsieh
// [TAG]  		EIP72056
// [Category]  	Improvement
// [Description]  	Change EFI_MP_PROC_CONTEXT to follow Intel CPU driver
// 
// 1     2/07/12 3:59a Davidhsieh
// 
// 1     7/07/11 4:41a Davidhsieh
// 
// 1     5/06/11 6:08a Davidhsieh
// First release
// 
// 3     8/03/09 4:04p Markw
// Add GetProcessorContext update.
// 
// 2     3/04/09 10:45a Markw
// Update copyright header.
// 
// 1     11/02/07 1:59p Markw
// 
// 1     11/02/07 1:45p Markw
// 
// 2     7/23/07 7:33p Markw
// Make EFI_MP_SERVICES_PROTOCOL output parameters optional.
// 
// 1     3/28/06 1:07p Markw
// 
// 
//*****************************************************************************
//<AMI_FHDR_START>
//
// Name:	MpService.h
//
// Description:	This file is an include file used to define the Protocol for the
//		        DXE Mp Service Protocol.
//
//<AMI_FHDR_END>
//*****************************************************************************

#ifndef _MP_SERVICES_H_
#define _MP_SERVICES_H_

#include "efi.h"

#ifdef __cplusplus
extern "C" {
#endif

//This Protocol has been significantly changed by the PI spec. If this protocol is used,
//be prepared to update your code accordingly.

#define EFI_MP_SERVICES_PROTOCOL_GUID \
	{0xf33261e7,0x23cb,0x11d5,0xbd,0x5c,0x0,0x80,0xc7,0x3c,0x88,0x81}

typedef VOID (*EFI_AP_PROCEDURE) (
	IN VOID	*Buffer
);

//*******************************************************
// Processor Context Buffer Definitions.
//*******************************************************
//EFI_MP_PROC_CONTEXT is copyied from Intel CPU RC, it's different from Aptio CPU module
//
typedef union {
  struct {
    UINT32  Status : 2;
    UINT32  Tested : 1;
    UINT32  Reserved1 : 13;
    UINT32  VirtualMemoryUnavailable : 1;
    UINT32  Ia32ExecutionUnavailable : 1;
    UINT32  FloatingPointUnavailable : 1;
    UINT32  MiscFeaturesUnavailable : 1;
    UINT32  Reserved2 : 12;
  } Bits;
  UINT32  Uint32;
} EFI_MP_HEALTH_FLAGS;

#define EFI_MP_HEALTH_FLAGS_STATUS_HEALTHY                  0x0
#define EFI_MP_HEALTH_FLAGS_STATUS_PERFORMANCE_RESTRICTED   0x1
#define EFI_MP_HEALTH_FLAGS_STATUS_FUNCTIONALLY_RESTRICTED  0x2

typedef struct {
  EFI_MP_HEALTH_FLAGS Flags;
  UINT32              TestStatus;
} EFI_MP_HEALTH;

typedef enum {
  EfiCpuAP                = 0,
  EfiCpuBSP,
  EfiCpuDesignationMaximum
} EFI_CPU_DESIGNATION;

typedef struct {
  UINT32  Package;
  UINT32  Die;
  UINT32  Core;
  UINT32  Thread;
} PHYSICAL_LOCATION;

typedef struct {
  UINT32              ApicID;
  BOOLEAN             Enabled;
  EFI_CPU_DESIGNATION Designation;
  EFI_MP_HEALTH       Health;
  UINTN               PackageNumber;
  UINTN               NumberOfCores;
  UINTN               NumberOfThreads;
  UINT64              ProcessorPALCompatibilityFlags;
  UINT64              ProcessorTestMask;
} EFI_MP_PROC_CONTEXT;

#define EFI_MP_PROC_CONTEXT_VERSION \
    {0x4DCFD87B, 0x2C99, 0x11d6, 0xAF, 0x22,0x00,0xA0, 0xC9, 0x44, 0xA0, 0x5B}


typedef struct _EFI_MP_SERVICES_PROTOCOL EFI_MP_SERVICES_PROTOCOL;

typedef EFI_STATUS (EFIAPI *EFI_MP_SERVICES_GET_GENERAL_MP_INFO) (
	IN EFI_MP_SERVICES_PROTOCOL	*This,
	OUT UINTN	*NumberOfCPUs           OPTIONAL,
	OUT UINTN	*MaximumNumberOfCPUs    OPTIONAL,
	OUT UINTN	*NumberOfEnabledCPUs    OPTIONAL,
	OUT UINTN	*RendezvousIntNumber    OPTIONAL,
	OUT UINTN	*RendezvousProcLength   OPTIONAL
);

typedef EFI_STATUS (EFIAPI *EFI_MP_SERVICES_GET_PROCESSOR_CONTEXT) (
	IN EFI_MP_SERVICES_PROTOCOL	*This,
	IN UINTN		ProcessorNumber,
	IN OUT UINTN	*BufferLength,
	IN OUT VOID		*ProcessorContextBuffer
);

typedef EFI_STATUS (EFIAPI *EFI_MP_SERVICES_STARTUP_ALL_APS) (
	IN EFI_MP_SERVICES_PROTOCOL	*This,
	IN EFI_AP_PROCEDURE	Procedure,
	IN BOOLEAN		SingleThread,
	IN EFI_EVENT	WaitEvent OPTIONAL,
	IN UINTN		TimeoutInMicroSecs OPTIONAL,
	IN OUT VOID		*ProcArguments OPTIONAL,  
	OUT UINTN		*FailedCPUList OPTIONAL
);

typedef EFI_STATUS (EFIAPI *EFI_MP_SERVICES_STARTUP_THIS_AP) (
	IN EFI_MP_SERVICES_PROTOCOL    *This,
	IN EFI_AP_PROCEDURE	Procedure,
	IN UINTN			ProcessorNumber,
	IN EFI_EVENT		WaitEvent OPTIONAL,
	IN UINTN			TimeoutInMicroSecs OPTIONAL,
	IN OUT VOID			*ProcArguments OPTIONAL
);

typedef EFI_STATUS (EFIAPI *EFI_MP_SERVICES_SWITCH_BSP) (
	IN EFI_MP_SERVICES_PROTOCOL	*This,
	IN UINTN	ProcessorNumber,
	IN BOOLEAN	EnableOldBSP
);

typedef EFI_STATUS (EFIAPI *EFI_MP_SERVICES_SEND_IPI) (
	IN EFI_MP_SERVICES_PROTOCOL    *This,
	IN UINTN	ProcessorNumber,
	IN UINTN	VectorNumber,
	IN UINTN	DeliveryMode
);

typedef EFI_STATUS (EFIAPI *EFI_MP_SERVICES_ENABLEDISABLEAP) (
	IN EFI_MP_SERVICES_PROTOCOL    *This,
	IN UINTN	ProcessorNumber,
	IN BOOLEAN	Enable,
	IN VOID		*HealthState OPTIONAL
);

typedef EFI_STATUS (EFIAPI *EFI_MP_SERVICES_WHOAMI) (
	IN EFI_MP_SERVICES_PROTOCOL	*This,
	OUT UINTN	*ProcessorNumber
);

typedef struct _EFI_MP_SERVICES_PROTOCOL {
	EFI_MP_SERVICES_GET_GENERAL_MP_INFO		GetGeneralMPInfo;
	EFI_MP_SERVICES_GET_PROCESSOR_CONTEXT	GetProcessorContext;
	EFI_MP_SERVICES_STARTUP_ALL_APS			StartupAllAPs;
	EFI_MP_SERVICES_STARTUP_THIS_AP			StartupThisAP;
	EFI_MP_SERVICES_SWITCH_BSP				SwitchBSP;
	EFI_MP_SERVICES_SEND_IPI				SendIPI;
	EFI_MP_SERVICES_ENABLEDISABLEAP			EnableDisableAP;
	EFI_MP_SERVICES_WHOAMI					WhoAmI;
};

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1987-2013, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
