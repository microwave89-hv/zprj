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

//**********************************************************************
// $Header: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Include/Protocol/MpService.h 1     10/25/12 8:54a Wesleychen $
//
// $Revision: 1 $
//
// $Date: 10/25/12 8:54a $
//*****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Include/Protocol/MpService.h $
// 
// 1     10/25/12 8:54a Wesleychen
// EFI_MP_PROC_CONTEXT is copyied from Intel CPU RC.
// 
// 5     11/12/11 6:46p Artems
// 
// 5     9/09/11 4:47p Markw
// [TAG]  		EIP64115
// [Category]  	Spec Update
// [Description]  	Always support Framework MP Services for binaries.
// Support Framework MP Service header for Framework, and
// support PI MP Service header for PI.
// 
// [Files]  		Cpu.sdl, CpuMp.c, CpuDxe.h, CpuDxe.c, MpServices.h
// 
// 4     7/13/11 3:39p Felixp
// #if PI_SPECIFICATION_VERSION <= 0x0001000A is replaced with
// #if PI_SPECIFICATION_VERSION < 0x0001000A
// (equal sign is removed).
// 
// 3     6/23/11 5:34p Felixp
// Improved compatibility with existing CPU modules.
// (PI definitions are disabled when NO_PI_MP_SERVICES_SUPPORT macro is
// defined).
// 
// 2     6/16/11 9:50a Felixp
// Header is updated to include PI and Framework flavors of the protocol
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

#include <Efi.h>

#ifdef __cplusplus
extern "C" {
#endif

#if PI_SPECIFICATION_VERSION < 0x0001000A || BACKWARD_COMPATIBLE_MODE && defined(NO_PI_MP_SERVICES_SUPPORT)

#define EFI_MP_SERVICES_PROTOCOL_GUID \
	{0xf33261e7,0x23cb,0x11d5,0xbd,0x5c,0x0,0x80,0xc7,0x3c,0x88,0x81}

GUID_VARIABLE_DECLARATION(gEfiMpServiceProtocolGuid, EFI_MP_SERVICES_PROTOCOL_GUID);

#ifndef EFI_AP_PROCEDURE_TYPE_DEFINED
#define EFI_AP_PROCEDURE_TYPE_DEFINED
typedef VOID (*EFI_AP_PROCEDURE) (
	IN VOID	*Buffer
);
#endif

//*******************************************************
// Processor Context Buffer Definitions.
//*******************************************************
//(Intel CPU RC)>
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
//<(Intel CPU RC)

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

#else // #if PI_SPECIFICATION_VERSION < 0x0001000A

/// Global ID for the EFI_MP_SERVICES_PROTOCOL.
#define EFI_MP_SERVICES_PROTOCOL_GUID \
  { 0x3fdda605, 0xa76e, 0x4f46, 0xad, 0x29, 0x12, 0xf4, 0x53, 0x1b, 0x3d, 0x08 }

GUID_VARIABLE_DECLARATION(gEfiMpServiceProtocolGuid, EFI_MP_SERVICES_PROTOCOL_GUID);

typedef struct _EFI_MP_SERVICES_PROTOCOL EFI_MP_SERVICES_PROTOCOL;

#ifndef EFI_AP_PROCEDURE_TYPE_DEFINED
#define EFI_AP_PROCEDURE_TYPE_DEFINED
typedef VOID (*EFI_AP_PROCEDURE) (
	IN VOID	*Buffer
);
#endif

/// Terminator for a list of failed CPUs returned by StartAllAPs().
#define END_OF_CPU_LIST    0xffffffff

/// This bit is used in the StatusFlag field of EFI_PROCESSOR_INFORMATION and 
/// indicates whether the processor is playing the role of BSP. If the bit is 1,
/// then the processor is BSP. Otherwise, it is AP.
#define PROCESSOR_AS_BSP_BIT         0x00000001

/// This bit is used in the StatusFlag field of EFI_PROCESSOR_INFORMATION and 
/// indicates whether the processor is enabled. If the bit is 1, then the 
/// processor is enabled. Otherwise, it is disabled.
#define PROCESSOR_ENABLED_BIT        0x00000002

/// This bit is used in the StatusFlag field of EFI_PROCESSOR_INFORMATION and 
/// indicates whether the processor is healthy. If the bit is 1, then the 
/// processor is healthy. Otherwise, some fault has been detected for the processor.
#define PROCESSOR_HEALTH_STATUS_BIT  0x00000004

/// Structure that describes the pyhiscal location of a logical CPU.
typedef struct {
  /// Zero-based physical package number that identifies the cartridge of the processor.
  UINT32  Package;
  /// Zero-based physical core number within package of the processor.
  UINT32  Core;
  /// Zero-based logical thread number within core of the processor.
  UINT32  Thread;
} EFI_CPU_PHYSICAL_LOCATION;

/// Structure that describes information about a logical CPU.
typedef struct {
  /// The unique processor ID determined by system hardware.  For IA32 and X64, 
  /// the processor ID is the same as the Local APIC ID. Only the lower 8 bits 
  /// are used, and higher bits are reserved.  For IPF, the lower 16 bits contains
  /// id/eid, and higher bits are reserved.
  ///
  UINT64                     ProcessorId; 
  ///
  /// Flags indicating if the processor is BSP or AP, if the processor is enabled 
  /// or disabled, and if the processor is healthy. Bits 3..31 are reserved and 
  /// must be 0. 
  /// 
  /// <pre>
  /// BSP  ENABLED  HEALTH  Description
  /// ===  =======  ======  ===================================================
  ///  0      0       0     Unhealthy Disabled AP.
  ///  0      0       1     Healthy Disabled AP.
  ///  0      1       0     Unhealthy Enabled AP.
  ///  0      1       1     Healthy Enabled AP.
  ///  1      0       0     Invalid. The BSP can never be in the disabled state.
  ///  1      0       1     Invalid. The BSP can never be in the disabled state.
  ///  1      1       0     Unhealthy Enabled BSP.
  ///  1      1       1     Healthy Enabled BSP.
  /// </pre>
  ///
  UINT32                     StatusFlag;
  ///
  /// The physical location of the processor, including the physical package number
  /// that identifies the cartridge, the physical core number within package, and 
  /// logical thread number within core.
  ///
  EFI_CPU_PHYSICAL_LOCATION  Location;
} EFI_PROCESSOR_INFORMATION;

typedef
EFI_STATUS
(EFIAPI *EFI_MP_SERVICES_GET_NUMBER_OF_PROCESSORS)(
  IN  EFI_MP_SERVICES_PROTOCOL  *This,
  OUT UINTN                     *NumberOfProcessors,
  OUT UINTN                     *NumberOfEnabledProcessors
  );

typedef
EFI_STATUS
(EFIAPI *EFI_MP_SERVICES_GET_PROCESSOR_INFO)(
  IN  EFI_MP_SERVICES_PROTOCOL   *This,
  IN  UINTN                      ProcessorNumber,
  OUT EFI_PROCESSOR_INFORMATION  *ProcessorInfoBuffer
  );

typedef
EFI_STATUS
(EFIAPI *EFI_MP_SERVICES_STARTUP_ALL_APS)(
  IN  EFI_MP_SERVICES_PROTOCOL  *This,
  IN  EFI_AP_PROCEDURE          Procedure,
  IN  BOOLEAN                   SingleThread,
  IN  EFI_EVENT                 WaitEvent               OPTIONAL,
  IN  UINTN                     TimeoutInMicroSeconds,
  IN  VOID                      *ProcedureArgument      OPTIONAL,
  OUT UINTN                     **FailedCpuList         OPTIONAL
  );

typedef
EFI_STATUS
(EFIAPI *EFI_MP_SERVICES_STARTUP_THIS_AP)(
  IN  EFI_MP_SERVICES_PROTOCOL  *This,
  IN  EFI_AP_PROCEDURE          Procedure,
  IN  UINTN                     ProcessorNumber,
  IN  EFI_EVENT                 WaitEvent               OPTIONAL,
  IN  UINTN                     TimeoutInMicroseconds,
  IN  VOID                      *ProcedureArgument      OPTIONAL,
  OUT BOOLEAN                   *Finished               OPTIONAL
  );

typedef
EFI_STATUS
(EFIAPI *EFI_MP_SERVICES_SWITCH_BSP)(
  IN EFI_MP_SERVICES_PROTOCOL  *This,
  IN  UINTN                    ProcessorNumber,
  IN  BOOLEAN                  EnableOldBSP
  );

typedef
EFI_STATUS
(EFIAPI *EFI_MP_SERVICES_ENABLEDISABLEAP)(
  IN  EFI_MP_SERVICES_PROTOCOL  *This,
  IN  UINTN                     ProcessorNumber,
  IN  BOOLEAN                   EnableAP,
  IN  UINT32                    *HealthFlag OPTIONAL
  );

typedef
EFI_STATUS
(EFIAPI *EFI_MP_SERVICES_WHOAMI)(
  IN EFI_MP_SERVICES_PROTOCOL  *This,
  OUT UINTN                    *ProcessorNumber
  );

/// When installed, the MP Services Protocol produces a collection of services 
/// that are needed for MP management.
///
/// Before the UEFI event EFI_EVENT_GROUP_READY_TO_BOOT is signaled, the module 
/// that produces this protocol is required to place all APs into an idle state 
/// whenever the APs are disabled or the APs are not executing code as requested 
/// through the StartupAllAPs() or StartupThisAP() services. The idle state of 
/// an AP before the UEFI event EFI_EVENT_GROUP_READY_TO_BOOT is signaled is 
/// implementation dependent.
///
/// After the UEFI event EFI_EVENT_GROUP_READY_TO_BOOT is signaled, all the APs 
/// must be placed in the OS compatible CPU state as defined by the UEFI 
/// Specification. Implementations of this protocol may use the UEFI event 
/// EFI_EVENT_GROUP_READY_TO_BOOT to force APs into the OS compatible state as 
/// defined by the UEFI Specification. Modules that use this protocol must 
/// guarantee that all non-blocking mode requests on all APs have been completed 
/// before the UEFI event EFI_EVENT_GROUP_READY_TO_BOOT is signaled. Since the 
/// order that event notification functions in the same event group are executed 
/// is not deterministic, an event of type EFI_EVENT_GROUP_READY_TO_BOOT cannot 
/// be used to guarantee that APs have completed their non-blocking mode requests.
///
/// When the UEFI event EFI_EVENT_GROUP_READY_TO_BOOT is signaled, the StartAllAPs() 
/// and StartupThisAp() services must no longer support non-blocking mode requests. 
/// The support for SwitchBSP() and EnableDisableAP() may no longer be supported 
/// after this event is signaled. Since UEFI Applications and UEFI OS Loaders 
/// execute after the UEFI event EFI_EVENT_GROUP_READY_TO_BOOT is signaled, these 
/// UEFI images must be aware that the functionality of this protocol may be reduced.
/// 
struct _EFI_MP_SERVICES_PROTOCOL {
  EFI_MP_SERVICES_GET_NUMBER_OF_PROCESSORS  GetNumberOfProcessors;
  EFI_MP_SERVICES_GET_PROCESSOR_INFO        GetProcessorInfo;
  EFI_MP_SERVICES_STARTUP_ALL_APS           StartupAllAPs;
  EFI_MP_SERVICES_STARTUP_THIS_AP           StartupThisAP;
  EFI_MP_SERVICES_SWITCH_BSP                SwitchBSP;
  EFI_MP_SERVICES_ENABLEDISABLEAP           EnableDisableAP;
  EFI_MP_SERVICES_WHOAMI                    WhoAmI;
};

#endif // #if PI_SPECIFICATION_VERSION <= 0x0001000A
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
