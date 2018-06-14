//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2006, American Megatrends, Inc.         **
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
// $Header: /Alaska/SOURCE/Core/EDK/Tiano.h 7     5/27/11 5:44p Felixp $
//
// $Revision: 7 $
//
// $Date: 5/27/11 5:44p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Core/EDK/Tiano.h $
// 
// 7     5/27/11 5:44p Felixp
// EFI_FIRMWARE_VOLUME_BLOCK_PROTOCOL_GUID definition is removed
// (the macro is now defined in the FirmwareVolumeBlock.h
// 
// 6     9/22/10 7:09p Felixp
// Bug fix: PEI_REPORT_STATUS_CODE was not properly defined.
// 
// 5     4/25/07 11:31a Felixp
// 
// 4     10/07/06 10:23a Felixp
// UIEFI2.0 support.
// Updated to EDK 20060904
// 
// 3     8/24/06 9:40a Felixp
// x64 support
// 
// 2     5/20/06 9:38p Felixp
// 
// 1     5/19/06 11:28p Felixp
// 
// 1     3/13/06 1:57a Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	Tiano.h
//
// Description:	
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __TIANO__H__
#define __TIANO__H__
#ifdef __cplusplus
extern "C" {
#endif
#include <EFI.h>
#include <DXE.h>
#include <StatusCodes.h>
#include <Protocol/DevicePath.h>

//from EfiStdArg.h
#define _EFI_INT_SIZE_OF(n) ((sizeof (n) + sizeof (UINTN) - 1) &~(sizeof (UINTN) - 1))

//
// Also support coding convention rules for var arg macros
//
#ifndef VA_START

typedef CHAR8 *VA_LIST;
#define VA_START(ap, v) (ap = (VA_LIST) & (v) + _EFI_INT_SIZE_OF (v))
#define VA_ARG(ap, t)   (*(t *) ((ap += _EFI_INT_SIZE_OF (t)) - _EFI_INT_SIZE_OF (t)))
#define VA_END(ap)      (ap = (VA_LIST) 0)

#endif

#include <EfiDebug.h>

#define EFI_STRINGIZE(a)            #a

#define EFI_PROTOCOL_DEFINITION(a)  EFI_STRINGIZE (Protocol/a.h)
#define EFI_GUID_DEFINITION(a)      EFI_STRINGIZE (Guid/a.h)
#define EFI_ARCH_PROTOCOL_DEFINITION(a) EFI_STRINGIZE (Protocol/a.h)

#define EFI_PROTOCOL_PRODUCER(a)    EFI_PROTOCOL_DEFINITION (a)
#define EFI_PROTOCOL_CONSUMER(a)    EFI_PROTOCOL_DEFINITION (a)
#define EFI_PROTOCOL_DEPENDENCY(a)  EFI_PROTOCOL_DEFINITION (a)

#define EFI_PPI_DEFINITION(a)           EFI_STRINGIZE (Ppi/a.h)
#define EFI_PPI_PRODUCER(a)             EFI_PPI_DEFINITION (a)
#define EFI_PPI_CONSUMER(a)             EFI_PPI_DEFINITION (a)
#define EFI_PPI_DEPENDENCY(a)           EFI_PPI_DEFINITION (a)

#define CONST const
#define STATIC    static
#define VOLATILE  volatile

#define EFI_BOOTSERVICE
#define EFI_RUNTIMESERVICE
#define EFI_BOOTSERVICE11
#define EFI_DXESERVICE
//
//  ALIGN_POINTER - aligns a pointer to the lowest boundry
//
#define ALIGN_POINTER(p, s) ((VOID *) (p + ((s - ((UINTN) p)) & (s - 1))))

//
//  ALIGN_VARIABLE - aligns a variable up to the next natural boundry for int size of a processor
//
#define ALIGN_VARIABLE(Value, Adjustment) \
  (UINTN) Adjustment = 0; \
  if ((UINTN) Value % sizeof (UINTN)) { \
    (UINTN) Adjustment = sizeof (UINTN) - ((UINTN) Value % sizeof (UINTN)); \
  } \
  Value = (UINTN) Value + (UINTN) Adjustment

//
//  EFI_FIELD_OFFSET - returns the byte offset to a field within a structure
//
#define EFI_FIELD_OFFSET(TYPE,Field) ((UINTN)(&(((TYPE *) 0)->Field)))

//
//  CONTAINING_RECORD - returns a pointer to the structure
//      from one of it's elements.
//
#define _CR(Record, TYPE, Field)  ((TYPE *) ((CHAR8 *) (Record) - (CHAR8 *) &(((TYPE *) 0)->Field)))

//
// Define macros to build data structure signatures from characters.
//
#define EFI_SIGNATURE_16(A, B)        ((A) | (B << 8))
#define EFI_SIGNATURE_32(A, B, C, D)  (EFI_SIGNATURE_16 (A, B) | (EFI_SIGNATURE_16 (C, D) << 16))
#define EFI_SIGNATURE_64(A, B, C, D, E, F, G, H) \
    (EFI_SIGNATURE_32 (A, B, C, D) | ((UINT64) (EFI_SIGNATURE_32 (E, F, G, H)) << 32))

//AMI <--> EDK mapping
#define EFI_LOADED_IMAGE_INFORMATION_REVISION EFI_LOADED_IMAGE_PROTOCOL_REVISION
typedef DXE_SERVICES EFI_DXE_SERVICES;
#define EFI_TPL_APPLICATION TPL_APPLICATION
#define EFI_TPL_CALLBACK TPL_CALLBACK
#define EFI_TPL_NOTIFY TPL_NOTIFY
#define EFI_TPL_HIGH_LEVEL TPL_HIGH_LEVEL

#define END_DEVICE_PATH_TYPE 0x7F
#define END_ENTIRE_DEVICE_PATH_SUBTYPE 0xFF
#define EFI_EVENT_EFI_SIGNAL_MASK               0x000000FF
#define EFI_EVENT_EFI_SIGNAL_MAX                4
#define EFI_TPL_DRIVER      6
#define EFI_DXE_SERVICES_SIGNATURE DXE_SERVICES_SIGNATURE
#define EFI_DXE_SERVICES_REVISION DXE_SERVICES_REVISION
#define EFI_DXE_ENTRY_POINT(EntryPoint)
#ifndef EFI_DEADLOOP
#define EFI_DEADLOOP() { volatile UINTN __DeadLoopVar__ = 1; while (__DeadLoopVar__); }
#endif
#define EFI_BREAKPOINT()  EFI_DEADLOOP()
#define EFI_BAD_POINTER          0xAFAFAFAF
//This is defined in FirmwareValume.h but has nothing to do with the protocol.
//It should be in DxeMain internal header
#define FV_DEVICE_SIGNATURE EFI_SIGNATURE_32 ('_', 'F', 'V', '_')
#define EFI_FVH_SIGNATURE FV_SIGNATURE
#define EFI_FV_BLOCK_MAP_ENTRY FvBlockMapEntry
//This is define in TianoType.h, however, this is not in DXECIS
//
// attributes for reserved memory before it is promoted to system memory
//
#define EFI_MEMORY_PRESENT      0x0100000000000000
#define EFI_MEMORY_INITIALIZED  0x0200000000000000
#define EFI_MEMORY_TESTED       0x0400000000000000

//
// range for memory mapped port I/O on IPF
//
#define EFI_MEMORY_PORT_IO  0x4000000000000000
//
// A pointer to a function in IPF points to a plabel.
//
typedef struct {
  UINT64  EntryPoint;
  UINT64  GP;
} EFI_PLABEL;
////////////////////////////////////////////////
//defined for every CPU architecture
// Maximum legal IA-32 address
#define EFI_MAX_ADDRESS   0xFFFFFFFF
////////////////////////////////////////////////
//from AmiLib.h
#define EFI_PAGE_MASK   (EFI_PAGE_SIZE - 1)
#define EFI_PAGE_SHIFT  12
#define EFI_SIZE_TO_PAGES(s)  \
    ( (((UINTN)(s)) >> EFI_PAGE_SHIFT) + ((((UINTN)(s)) & EFI_PAGE_MASK) ? 1 : 0) )

#define EFI_PAGES_TO_SIZE(p)   ( ((UINTN)(p)) << EFI_PAGE_SHIFT)

//from EfiDevicePath.h
#define EFI_DP_TYPE_MASK                    0x7F
#define EFI_DP_TYPE_UNPACKED                0x80
#define END_INSTANCE_DEVICE_PATH_SUBTYPE    0x01

#define DP_IS_END_TYPE(a)
#define DP_IS_END_SUBTYPE(a)        ( ((a)->SubType == END_ENTIRE_DEVICE_PATH_SUBTYPE )

#define DevicePathType(a)           ( ((a)->Type) & EFI_DP_TYPE_MASK )
#define DevicePathSubType(a)        ( (a)->SubType )
#define DevicePathNodeLength(a)     ( ((a)->Length[0]) | ((a)->Length[1] << 8) )

#define IsDevicePathEndType(a)      ( DevicePathType(a) == END_DEVICE_PATH_TYPE )
#define IsDevicePathEndSubType(a)   ( (a)->SubType == END_ENTIRE_DEVICE_PATH_SUBTYPE )
#define IsDevicePathEnd(a)          ( IsDevicePathEndType(a) && IsDevicePathEndSubType(a) )
#define NextDevicePathNode(a)       ( (EFI_DEVICE_PATH_PROTOCOL *) ( ((UINT8 *) (a)) + DevicePathNodeLength(a)))

#define SetDevicePathNodeLength(a,l) {                \
          (a)->Length[0] = (UINT8) (l);               \
          (a)->Length[1] = (UINT8) ((l) >> 8);        \
          }

#define SetDevicePathEndNode(a)  {                       \
          (a)->Type = END_DEVICE_PATH_TYPE;              \
          (a)->SubType = END_ENTIRE_DEVICE_PATH_SUBTYPE; \
          (a)->Length[0] = sizeof(EFI_DEVICE_PATH_PROTOCOL);      \
          (a)->Length[1] = 0;                            \
          }

//from DevicePath.h
#define EFI_END_ENTIRE_DEVICE_PATH            0x7f
#define EFI_END_ENTIRE_DEVICE_PATH_SUBTYPE    0xff
#define EFI_END_INSTANCE_DEVICE_PATH          0x01
#define EFI_END_DEVICE_PATH_LENGTH            (sizeof (EFI_DEVICE_PATH_PROTOCOL))

#define EfiDevicePathNodeLength(a)            (((a)->Length[0]) | ((a)->Length[1] << 8))

#define EfiNextDevicePathNode(a)              ((EFI_DEVICE_PATH_PROTOCOL *) (((UINT8 *) (a)) + EfiDevicePathNodeLength (a)))

#define EfiDevicePathType(a)                  (((a)->Type) & 0x7f)
#define EfiIsDevicePathEndType(a)             (EfiDevicePathType (a) == 0x7f)

#define EfiIsDevicePathEndSubType(a)          ((a)->SubType == EFI_END_ENTIRE_DEVICE_PATH_SUBTYPE)
#define EfiIsDevicePathEndInstanceSubType(a)  ((a)->SubType == EFI_END_INSTANCE_DEVICE_PATH)

#define EfiIsDevicePathEnd(a)                 (EfiIsDevicePathEndType (a) && EfiIsDevicePathEndSubType (a))
#define EfiIsDevicePathEndInstance(a)         (EfiIsDevicePathEndType (a) && EfiIsDevicePathEndInstanceSubType (a))

//EfiTypes.h
#define NULL_HANDLE ((VOID *) 0)
//defined in Protocol/SimpleFileSystem - not in efi spec.
//protocol name does not match uefi2.0 (EFI_FILE)
#include <Protocol/SimpleFileSystem.h>
typedef EFI_FILE_PROTOCOL *EFI_FILE_HANDLE;

//EfiApi.h
#define NextMemoryDescriptor(_Ptr, _Size)   ((EFI_MEMORY_DESCRIPTOR *) (((UINT8 *) (_Ptr)) + (_Size)))
//EfiImageFormat.h
#define SECTION_SIZE(SectionHeaderPtr) \
    ((UINT32) (*((UINT32 *) ((EFI_COMMON_SECTION_HEADER *) SectionHeaderPtr)->Size) & 0x00ffffff))
#define EFI_CUSTOMIZED_COMPRESSION  0x02
//
// Bit values for AuthenticationStatus
//
#define EFI_AGGREGATE_AUTH_STATUS_PLATFORM_OVERRIDE 0x000001
#define EFI_AGGREGATE_AUTH_STATUS_IMAGE_SIGNED      0x000002
#define EFI_AGGREGATE_AUTH_STATUS_NOT_TESTED        0x000004
#define EFI_AGGREGATE_AUTH_STATUS_TEST_FAILED       0x000008
#define EFI_AGGREGATE_AUTH_STATUS_ALL               0x00000f

#define EFI_LOCAL_AUTH_STATUS_PLATFORM_OVERRIDE     0x010000
#define EFI_LOCAL_AUTH_STATUS_IMAGE_SIGNED          0x020000
#define EFI_LOCAL_AUTH_STATUS_NOT_TESTED            0x040000
#define EFI_LOCAL_AUTH_STATUS_TEST_FAILED           0x080000
#define EFI_LOCAL_AUTH_STATUS_ALL                   0x0f0000
//////////////////////////// PEI //////////////////////////
#include <Pei.h>
#include <PeiDebug.h>
#include <PeiHob.h>

typedef struct {
  UINTN                   BootFirmwareVolume;
  UINTN                   SizeOfCacheAsRam;
  EFI_PEI_PPI_DESCRIPTOR  *DispatchTable;
} EFI_PEI_STARTUP_DESCRIPTOR;

#ifdef EFI_PEI_REPORT_STATUS_CODE_ON
#define PEI_REPORT_STATUS_CODE_CODE(Code) Code
#define PEI_REPORT_STATUS_CODE(PeiServices, CodeType, Value, Instance, CallerId, Data) \
          (*PeiServices)->ReportStatusCode (PeiServices, CodeType, Value, Instance, CallerId, Data)
#else
#define PEI_REPORT_STATUS_CODE_CODE(Code)
#define PEI_REPORT_STATUS_CODE(PeiServices, CodeType, Value, Instance, CallerId, Data)
#endif
#define EFI_PEI_CORE_ENTRY_POINT(EntryPoint)

#define PEI_RESET_PPI EFI_PEI_RESET_PPI

#define EFI_DXE_SERVICES_TABLE_GUID DXE_SERVICES_TABLE_GUID
#define EFI_HOB_LIST_GUID HOB_LIST_GUID
#define EFI_HOB_TYPE_PEI_MEMORY_POOL EFI_HOB_TYPE_MEMORY_POOL

//Compatibility
// PPI's
#define PEI_CPU_IO_PPI_GUID EFI_PEI_CPU_IO_PPI_INSTALLED_GUID
#define PEI_CPU_IO_PPI EFI_PEI_CPU_IO_PPI
#define PEI_PCI_CFG_PPI_GUID EFI_PEI_PCI_CFG_PPI_INSTALLED_GUID
#define PEI_PCI_CFG_PPI EFI_PEI_PCI_CFG_PPI
#define PEI_SMBUS_PPI_GUID EFI_PEI_SMBUS_PPI_GUID
#define PEI_SMBUS_PPI EFI_PEI_SMBUS_PPI
#define PEI_STALL_PPI_GUID EFI_PEI_STALL_PPI_GUID
#define PEI_STALL_PPI EFI_PEI_STALL_PPI
#define PEI_STATUS_CODE_PPI_GUID EFI_PEI_REPORT_PROGRESS_CODE_PPI_GUID
#define PEI_STATUS_CODE_PPI EFI_PEI_PROGRESS_CODE_PPI
#define PEI_READ_ONLY_VARIABLE_ACCESS_PPI_GUID EFI_PEI_READ_ONLY_VARIABLE_PPI_GUID
#define PEI_READ_ONLY_VARIABLE_PPI EFI_PEI_READ_ONLY_VARIABLE_PPI
#define PEI_RESET_PPI_GUID EFI_PEI_RESET_PPI_GUID
#define PEI_RESET_PPI EFI_PEI_RESET_PPI
#define PEI_BOOT_SCRIPT_EXECUTER_PPI_GUID EFI_PEI_BOOT_SCRIPT_EXECUTER_PPI_GUID
#define PEI_BOOT_SCRIPT_EXECUTER_PPI EFI_PEI_BOOT_SCRIPT_EXECUTER_PPI
#define PEI_S3_RESUME_PPI_GUID EFI_PEI_S3_RESUME_PPI_GUID
#define PEI_S3_RESUME_PPI EFI_PEI_S3_RESUME_PPI
#define PEI_RECOVERY_MODULE_INTERFACE_PPI EFI_PEI_RECOVERY_MODULE_PPI_GUID 
#define PEI_RECOVERY_MODULE_INTERFACE EFI_PEI_RECOVERY_MODULE_PPI
// Protocols
#define EFI_INCOMPATIBLE_PCI_DEVICE_SUPPORT EFI_INCOMPATIBLE_PCI_DEVICE_SUPPORT_PROTOCOL
#define EFI_SIMPLE_TEXT_OUT_PROTOCOL_GUID EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL_GUID
#define EFI_SIMPLE_TEXT_OUT_PROTOCOL EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL
#define EFI_SIMPLE_TEXT_IN_PROTOCOL_GUID EFI_SIMPLE_TEXT_INPUT_PROTOCOL_GUID
#define EFI_SIMPLE_TEXT_IN_PROTOCOL EFI_SIMPLE_TEXT_INPUT_PROTOCOL
#define LOAD_FILE_PROTOCOL_GUID EFI_LOAD_FILE_PROTOCOL_GUID
#define EFI_EBC_INTERPRETER_PROTOCOL_GUID EFI_EBC_PROTOCOL_GUID 
/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2006, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************