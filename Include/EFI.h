//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
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
// $Header: /Alaska/BIN/Core/Include/EFI.h 30    7/20/12 9:57a Artems $
//
// $Revision: 30 $
//
// $Date: 7/20/12 9:57a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/EFI.h $
// 
// 30    7/20/12 9:57a Artems
// [TAG]  		EIP N/A
// [Category]  	Spec Update
// [Severity]  	Minor
// [Description]  	Added new structure name to be compliant with UEFI spec
// [Files]  		Efi.h
// 
// 29    5/24/12 4:37p Artems
// [TAG]  		EIP N/A
// [Category]  	Spec Update
// [Severity]  	Minor
// [Description]  	Updates structure members name according to UEFI spec
// [Files]  		Efi.h
// 
// 28    5/13/11 6:34p Artems
// Added new Capsule flag, that was introduced in UEFI spec v.2.3.1
// 
// 27    5/06/11 3:22p Artems
// EIP 59569: Minor changes introduced in UEFI spec v. 2.3.1
// 
// 26    5/02/11 5:34p Artems
// EIP 59569: Minor changes introduced in UEFI spec v. 2.3.1
// 
// 25    2/05/11 1:47p Artems
// Added PI 1.1 Error and Warning codes
// 
// 24    11/19/09 12:49p Felixp
// UEFI 2.1 specific definitions are added.
// 
// 23    11/13/09 4:06p Felixp
// GUID_VARIABLE_DECLARATION macro declaration is updated to fix linker
// warnings.
// 
// 22    8/21/09 4:19p Felixp
// EFI_INVALID_LANGUAGE error code is added
// 
// 20    11/18/08 10:18a Felixp
// GLOBAL_REMOVE_IF_UNREFERENCED macro added
// 
// 19    11/11/08 2:38p Felixp
// Disable warning that make it impossible to compile at /W4
// 
// 18    10/12/06 12:59p Felixp
// UEFI2.0 compatibility: PEI/DXE-specific error codes updated.
// 
// 17    10/09/06 11:49a Felixp
// Definition of EFI warnings fixed
// 
// 16    10/07/06 10:17a Felixp
// UEFI 2.0 definitions added
// 
// 15    9/13/06 2:51p Felixp
// CHAR8 and CHAR16 changed to unsigned types.
// 
// 14    8/24/06 9:09a Felixp
// x64 support
// 
// 13    5/19/06 10:18p Felixp
// Device Path Length changed from UINT16 to UINT8[2]
// 
// 5     4/25/05 10:01a Felixp
// type definition for EFI_LOAD_OPTION added
// 
// 4     4/21/05 7:57p Felixp
// values for AMI Status Codes changed to be in the OEM range defined by
// EFI Spec.
// 
// 2     4/05/05 9:14a Felixp
// Boot option attributes added
// 
// 
// 2     1/18/05 3:21p Felixp
// PrintDebugMessage renamed to Trace
// 
// 23    2/20/04 3:16p Markw
// Arranges some of the structures and defines into columns.
// 
// 19    2/09/04 9:48a Felixp
// EFI services added
// 
// 18    2/06/04 2:46a Felixp
//  - Support for VC6 tools
//  - bug fixes
// - component AddOn added
// 
// 17    2/05/04 2:59p Markw
// Added the rest of memory allocation typedefs and rase lower TPL
// typedefs.
// 
// 16    2/04/04 12:35a Felixp
// EFI_PAGE_SIZE defined
// 
// 15    1/30/04 4:58p Felixp
// BOOLEAN changed from char to unsigned char
// VOID changed from typedef to define
// 
// 14    1/22/04 11:54a Markw
// Added more BootServices defintions.
// 
// 13    1/18/04 1:10p Felixp
// EFI_ERROR defined
// 
// 12    1/15/04 6:33p Markw
// Added RTC Services to Runtime Table and InstallMultipleProtocolService
// to Boot Service Table.
// 
// 11    1/06/04 5:01p Yakovlevs
// 
// 10    1/05/04 3:38p Markw
// Added EFI_VIRTUAL_ADDRESS typedef
// 
// 9     1/05/04 3:28p Markw
// Added structure EFI_MEMORY_DESCRIPTOR and definitions for memory
// attributes.
// 
// 8     12/24/03 2:09p Felixp
// TRUE and FALSE added
// 
// 7     12/23/03 2:27p Felixp
// __w64 added to INTN and UINTN definitions to suppress compiler warnings
// 
// 6     12/22/03 12:57p Felixp
// Variable attributes added
// 
// 4     12/11/03 4:08p Markw
// Adding defines for errors and warnings and NULL.
// 
// 3     12/11/03 3:17p Markw
// Added some memory definitions.
// 
// 2     12/11/03 10:30a Felixp
// bugs in type definition fixed
// 
// 1     12/08/03 4:04p Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	EFI.H
//
// Description:	
// EFI Header file. It has standard definitions defined by the 
// UEFI Specification
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __EFI__H__
#define __EFI__H__
#ifdef __cplusplus
extern "C" {
#endif
#if _MSC_EXTENSIONS
// Disable warning that make it impossible to compile at /W4
// Disabling bitfield type checking warnings.
#pragma warning ( disable : 4214 )
// Disabling the unreferenced formal parameter warnings.
#pragma warning ( disable : 4100 )
// Disable slightly different base types warning as CHAR8 * can not be set
// to a constant string.
#pragma warning ( disable : 4057 )
// ASSERT(FALSE) or while (TRUE) are legal constructes so supress this warning
#pragma warning ( disable : 4127 )

// The Microsoft C compiler can removed references to unreferenced data items
//  if the /OPT:REF linker option is used. We defined a macro as this is a 
//  a non standard extension.
#define GLOBAL_REMOVE_IF_UNREFERENCED __declspec(selectany)
#else //#if _MSC_EXTENSIONS
#define GLOBAL_REMOVE_IF_UNREFERENCED
#endif
//**********************************************************************
//<AMI_GHDR_START>
//
// Name:	Types (Common EFI Data Types)
//
// Description:	
//	BOOLEAN - Logical Boolean. 1-byte value containing a 0 for FALSE or a 1 for TRUE. Other values are undefined.
//	INTN - Signed value of native width. (4 bytes on IA-32, 8 bytes on Itanium processor instructions)
//	UINTN - Unsigned value of native width. (4 bytes on IA-32, 8 bytes on Itanium processor instructions)
//	INT8 - 1-byte signed value.
//	UINT8 - 1-byte unsigned value.
//	INT16 - 2-byte signed value.
//	UINT16 - 2-byte unsigned value.
//	INT32 - 4-byte signed value.
//	UINT32 - 4-byte unsigned value.
//	INT64 - 8-byte signed value.
//	UINT64 - 8-byte unsigned value.
//	CHAR8 - 1-byte Character.
//	CHAR16 - 2-byte Character. Unless otherwise specified all strings are stored in the UTF-16 encoding format as defined by Unicode 2.1 and ISO/IEC 10646 standards.
//	VOID - Undeclared type.
//	EFI_GUID - 128-bit buffer containing a unique identifier value. Unless otherwise specified, aligned on a 64-bit boundary.
//	EFI_STATUS - Status code. Type INTN.
//	EFI_HANDLE - A collection of related interfaces. Type VOID *.
//	EFI_EVENT - Handle to an event structure. Type VOID *.
//	EFI_LBA - Logicalbl ock address. Type UINT64.
//	EFI_TPL - Task priority level. Type UINTN.
//	EFI_MAC_ADDRESS - 32-byte buffer containing a network Media Access Controlad dress.
//	EFI_IPv4_ADDRESS - 4-byte buffer. An IPv4 internet protocoladdress .
//	EFI_IPv6_ADDRESS - 16-byte buffer. An IPv6 internet protocoladdr ess.
//	EFI_IP_ADDRESS - 16-byte buffer aligned on a 4-byte boundary. An IPv4 or IPv6 internet protocol address.
//<AMI_GHDR_END>
//**********************************************************************
typedef unsigned char BOOLEAN;
#define TRUE 1
#define FALSE 0
#if !defined (_MSC_VER) || (_MSC_VER < 1300)
#define __w64
#endif
#if defined(EFI64) || defined(EFIx64)
typedef __int64 INTN;
typedef unsigned __int64 UINTN;
#else
typedef int __w64 INTN;
typedef unsigned __w64 UINTN;
#endif
typedef signed char INT8;
typedef unsigned char UINT8;
typedef short INT16;
typedef unsigned short UINT16;
typedef int INT32;
typedef unsigned UINT32;
typedef __int64 INT64;
typedef unsigned __int64 UINT64;
typedef unsigned char CHAR8;
typedef unsigned short CHAR16; 
#define VOID void

typedef struct{
	UINT32  Data1;
	UINT16  Data2;
	UINT16  Data3;
	UINT8   Data4[8]; 
} EFI_GUID; 

typedef UINTN EFI_STATUS;
typedef VOID* EFI_HANDLE;
typedef VOID* EFI_EVENT;
typedef UINT64 EFI_LBA;
typedef UINTN EFI_TPL;

typedef struct{
	UINT8 mac[32];
} EFI_MAC_ADDRESS;

typedef UINT32 EFI_IPv4_ADDRESS;

typedef struct{
	UINT8 ip[16];
} EFI_IPv6_ADDRESS;

typedef union{
	EFI_IPv4_ADDRESS ip4;
	EFI_IPv6_ADDRESS ip6;
}EFI_IP_ADDRESS;

typedef enum {
	AllocateAnyPages,
	AllocateMaxAddress,
	AllocateAddress,
	MaxAllocateType
} EFI_ALLOCATE_TYPE;

typedef enum {
	EfiReservedMemoryType,
	EfiLoaderCode,
	EfiLoaderData,
	EfiBootServicesCode,
	EfiBootServicesData,
	EfiRuntimeServicesCode,
	EfiRuntimeServicesData,
	EfiConventionalMemory,
	EfiUnusableMemory,
	EfiACPIReclaimMemory,
	EfiACPIMemoryNVS,
	EfiMemoryMappedIO,
	EfiMemoryMappedIOPortSpace,
	EfiPalCode,
	EfiMaxMemoryType
} EFI_MEMORY_TYPE;

typedef UINT64 EFI_PHYSICAL_ADDRESS;
typedef UINT64 EFI_VIRTUAL_ADDRESS;

//*******************************************************
// Memory Descriptor Version Number
//*******************************************************
#define EFI_MEMORY_DESCRIPTOR_VERSION 1

//EFI_MEMORY_DESCRIPTOR
//*******************************************************
typedef struct {
    UINT32                  Type;
    EFI_PHYSICAL_ADDRESS    PhysicalStart;
    EFI_VIRTUAL_ADDRESS     VirtualStart;
    UINT64                  NumberOfPages;
    UINT64                  Attribute;
} EFI_MEMORY_DESCRIPTOR;


#define EFI_PAGE_SIZE   4096

//*******************************************************
// Memory Attribute Definitions
//*******************************************************
// These types can be "ORed" together as needed.
#define EFI_MEMORY_UC       0x0000000000000001
#define EFI_MEMORY_WC       0x0000000000000002
#define EFI_MEMORY_WT       0x0000000000000004
#define EFI_MEMORY_WB       0x0000000000000008
#define EFI_MEMORY_UCE      0x0000000000000010
#define EFI_MEMORY_WP       0x0000000000001000
#define EFI_MEMORY_RP       0x0000000000002000
#define EFI_MEMORY_XP       0x0000000000004000
#define EFI_MEMORY_RUNTIME  0x8000000000000000


#define NULL 0

//Error Codes and Warning Codes
#define EFI_ERROR_BIT 	((UINTN)1 << (sizeof(UINTN) * 8 - 1))
#define PI_ERROR_BIT    (EFI_ERROR_BIT | (EFI_ERROR_BIT >> 2))
#define OEM_ERROR_BIT   (EFI_ERROR_BIT | (EFI_ERROR_BIT >> 1))
#define PI_WARNING_BIT  (EFI_ERROR_BIT >> 2)
#define EFI_SUCCESS	    0

#define EFI_ERROR(r) ( (r) & EFI_ERROR_BIT )

#define EFI_LOAD_ERROR                 ( 1 | EFI_ERROR_BIT)
#define EFI_INVALID_PARAMETER          ( 2 | EFI_ERROR_BIT)
#define EFI_UNSUPPORTED                ( 3 | EFI_ERROR_BIT)
#define EFI_BAD_BUFFER_SIZE            ( 4 | EFI_ERROR_BIT)
#define EFI_BUFFER_TOO_SMALL           ( 5 | EFI_ERROR_BIT)
#define EFI_NOT_READY                  ( 6 | EFI_ERROR_BIT)
#define EFI_DEVICE_ERROR               ( 7 | EFI_ERROR_BIT)
#define EFI_WRITE_PROTECTED            ( 8 | EFI_ERROR_BIT)
#define EFI_OUT_OF_RESOURCES           ( 9 | EFI_ERROR_BIT)
#define EFI_VOLUME_CORRUPTED           (10 | EFI_ERROR_BIT) // 0xa
#define EFI_VOLUME_FULL                (11 | EFI_ERROR_BIT) // 0xb
#define EFI_NO_MEDIA                   (12 | EFI_ERROR_BIT) // 0xc
#define EFI_MEDIA_CHANGED              (13 | EFI_ERROR_BIT) // 0xd
#define EFI_NOT_FOUND                  (14 | EFI_ERROR_BIT) // 0xe
#define EFI_ACCESS_DENIED              (15 | EFI_ERROR_BIT) // 0xf
#define EFI_NO_RESPONSE                (16 | EFI_ERROR_BIT) // 0x10
#define EFI_NO_MAPPING                 (17 | EFI_ERROR_BIT) // 0x11
#define EFI_TIMEOUT                    (18 | EFI_ERROR_BIT) // 0x12
#define EFI_NOT_STARTED                (19 | EFI_ERROR_BIT) // 0x13
#define EFI_ALREADY_STARTED            (20 | EFI_ERROR_BIT) // 0x14
#define EFI_ABORTED                    (21 | EFI_ERROR_BIT) // 0x15
#define EFI_ICMP_ERROR                 (22 | EFI_ERROR_BIT) // 0x16
#define EFI_TFTP_ERROR                 (23 | EFI_ERROR_BIT) // 0x17
#define EFI_PROTOCOL_ERROR             (24 | EFI_ERROR_BIT) // 0x18
#define EFI_INCOMPATIBLE_VERSION       (25 | EFI_ERROR_BIT) // 0x19
#define EFI_SECURITY_VIOLATION         (26 | EFI_ERROR_BIT) // 0x1a
#define EFI_CRC_ERROR                  (27 | EFI_ERROR_BIT) // 0x1b
#if EFI_SPECIFICATION_VERSION<0x20000
#define EFI_NOT_AVAILABLE_YET          (28 | EFI_ERROR_BIT) // 0x1c
#define EFI_UNLOAD_IMAGE               (29 | EFI_ERROR_BIT) // 0x1d
#else
#define EFI_END_OF_MEDIA	           (28 | EFI_ERROR_BIT) // 0x1c
#define EFI_END_OF_FILE	               (31 | EFI_ERROR_BIT) // 0x1f
#define EFI_INVALID_LANGUAGE           (32 | EFI_ERROR_BIT) // 0x20
//PI Error Codes
#define EFI_REQUEST_UNLOAD_IMAGE  (1 | PI_ERROR_BIT)
// The PI specification defines error as EFI_REQUEST_UNLOAD_IMAGE.
// EFI_UNLOAD_IMAGE is here for backward compatibility.
#define EFI_UNLOAD_IMAGE EFI_REQUEST_UNLOAD_IMAGE
#define EFI_NOT_AVAILABLE_YET     (2 | PI_ERROR_BIT)
#define EFI_INTERRUPT_PENDING   (0 | PI_ERROR_BIT)
#endif
// AMI Error Codes
#define EFI_DBE_EOF		               (1 | OEM_ERROR_BIT)
#define EFI_DBE_BOF		               (2 | OEM_ERROR_BIT)

#define EFI_WARN_UNKNOWN_GLYPH         ( 1 )
#define EFI_WARN_DELETE_FAILURE        ( 2 )
#define EFI_WARN_WRITE_FAILURE         ( 3 )
#define EFI_WARN_BUFFER_TOO_SMALL      ( 4 )
//PI Warnings
#define EFI_WARN_INTERRUPT_SOURCE_PENDING   (0 | PI_WARNING_BIT)
#define EFI_WARN_INTERRUPT_SOURCE_QUIESCED  (1 | PI_WARNING_BIT)

//**********************************************************************
//<AMI_GHDR_START>
//
// Name:	Modifiers (Modifiers for Common EFI Data Types)
//
// Description:	
//	IN - Datum is passed to the function.
//	OUT - Datum is returned from the function.
//	OPTIONAL - Passing the datum to the function is optional, and a NULL may be passed if the value is not supplied.
//	EFIAPI - Defines the calling convention for EFI interfaces.
//
//<AMI_GHDR_END>
//**********************************************************************
#define IN
#define OUT
#define OPTIONAL
#define EFIAPI
#define CONST const

typedef struct {
	UINT64 Signature;
	UINT32 Revision;
	UINT32 HeaderSize;
	UINT32 CRC32;
	UINT32 Reserved;
}EFI_TABLE_HEADER;

//*******************************************************
// Variable Attributes
//*******************************************************
#define EFI_VARIABLE_NON_VOLATILE                          0x0000000000000001
#define EFI_VARIABLE_BOOTSERVICE_ACCESS                    0x0000000000000002
#define EFI_VARIABLE_RUNTIME_ACCESS                        0x0000000000000004
#if EFI_SPECIFICATION_VERSION >= 0x2000A
#define EFI_VARIABLE_HARDWARE_ERROR_RECORD                 0x0000000000000008
#define EFI_VARIABLE_AUTHENTICATED_WRITE_ACCESS            0x0000000000000010
#define EFI_VARIABLE_TIME_BASED_AUTHENTICATED_WRITE_ACCESS 0x0000000000000020
#define EFI_VARIABLE_APPEND_WRITE                          0x0000000000000040
#endif

//*******************************************************
//Efi Boot Services
//*******************************************************

//*******************************************************
// Task Priority Levels
//*******************************************************
#define TPL_APPLICATION	4
#define TPL_CALLBACK 	8
#define TPL_NOTIFY 		16
#define TPL_HIGH_LEVEL 	31

// Task Priority Services
typedef EFI_TPL (*EFI_RAISE_TPL) (
	IN EFI_TPL NewTpl
);

typedef VOID (*EFI_RESTORE_TPL) (
	IN EFI_TPL OldTpl
);

// Memory Services
typedef EFI_STATUS (*EFI_ALLOCATE_PAGES) (
	IN EFI_ALLOCATE_TYPE 		Type,
	IN EFI_MEMORY_TYPE 			MemoryType,
	IN UINTN 					Pages,
	IN OUT EFI_PHYSICAL_ADDRESS	*Memory
);

typedef EFI_STATUS (*EFI_FREE_PAGES) (
	IN EFI_PHYSICAL_ADDRESS 	Memory,
	IN UINTN 					Pages
);

typedef EFI_STATUS (*EFI_GET_MEMORY_MAP) (
	IN OUT UINTN 					*MemoryMapSize,
	IN OUT EFI_MEMORY_DESCRIPTOR 	*MemoryMap,
	OUT UINTN 						*MapKey,
	OUT UINTN 						*DescriptorSize,
	OUT UINT32 						*DescriptorVersion
);

typedef EFI_STATUS (*EFI_ALLOCATE_POOL) (
    IN EFI_MEMORY_TYPE  PoolType,
    IN UINTN            Size,
    OUT VOID            **Buffer
);

typedef EFI_STATUS (*EFI_FREE_POOL) (
	IN VOID 			*Buffer
);

// Event & Timer Services
//*******************************************************
// Event Types
//*******************************************************
// These types can be "ORed" together as needed. For example,
// EVT_TIMER might be "Ored" with EVT_NOTIFY_WAIT or
// EVT_NOTIFY_SIGNAL.
#define EVT_TIMER 							0x80000000
#define EVT_RUNTIME 						0x40000000
#define EVT_RUNTIME_CONTEXT 				0x20000000
#define EVT_NOTIFY_WAIT 					0x00000100
#define EVT_NOTIFY_SIGNAL 					0x00000200
#define EVT_SIGNAL_EXIT_BOOT_SERVICES 		0x00000201
#define EVT_SIGNAL_VIRTUAL_ADDRESS_CHANGE	0x60000202
//Extended event types defined in the DXE CIS
#define EFI_EVENT_TIMER EVT_TIMER
#define EFI_EVENT_RUNTIME EVT_RUNTIME
#define EFI_EVENT_RUNTIME_CONTEXT EVT_RUNTIME_CONTEXT
#define EFI_EVENT_NOTIFY_WAIT EVT_NOTIFY_WAIT
#define EFI_EVENT_NOTIFY_SIGNAL EVT_NOTIFY_SIGNAL
#define EFI_EVENT_NOTIFY_SIGNAL_ALL 0x00000400
#define EFI_EVENT_SIGNAL_EXIT_BOOT_SERVICES EVT_SIGNAL_EXIT_BOOT_SERVICES
#define EFI_EVENT_SIGNAL_VIRTUAL_ADDRESS_CHANGE EVT_SIGNAL_VIRTUAL_ADDRESS_CHANGE
//Let's make it backward compatible
//#if EFI_SPECIFICATION_VERSION<0x20000
#define EFI_EVENT_SIGNAL_READY_TO_BOOT 0x00000203
#define EFI_EVENT_SIGNAL_LEGACY_BOOT 0x00000204
//#endif
//*******************************************************
// EFI_EVENT_NOTIFY
//*******************************************************
typedef VOID (EFIAPI *EFI_EVENT_NOTIFY) (
	IN EFI_EVENT Event, IN VOID *Context
);

typedef EFI_STATUS (*EFI_CREATE_EVENT)(
	IN UINT32 Type, IN EFI_TPL NotifyTpl,
	IN EFI_EVENT_NOTIFY NotifyFunction,
	IN VOID *NotifyContext, OUT EFI_EVENT *Event
);
//*******************************************************
//EFI_TIMER_DELAY
//*******************************************************
//TODO: TimerTypeMax is not defined in EFI (UEFI) Spec. It is here just for compatibility with EDK
typedef enum {
	TimerCancel, TimerPeriodic, TimerRelative, TimerTypeMax
} EFI_TIMER_DELAY;
typedef EFI_STATUS (*EFI_SET_TIMER)(
	IN EFI_EVENT Event, IN EFI_TIMER_DELAY Type,
	IN UINT64 TriggerTime
);
typedef EFI_STATUS (*EFI_WAIT_FOR_EVENT)(
	IN UINTN NumberOfEvents, IN EFI_EVENT *Event, OUT UINTN *Index
);
typedef EFI_STATUS (*EFI_SIGNAL_EVENT)(IN EFI_EVENT Event);
typedef EFI_STATUS (*EFI_CLOSE_EVENT)(IN EFI_EVENT Event);
typedef EFI_STATUS (*EFI_CHECK_EVENT)(IN EFI_EVENT Event);
// Protocol Handler Services
//**********************************************************************
//<AMI_GHDR_START>
// Name:	EFI_INTERFACE_TYPE
// Description:	Enumeration type.
// The only enumeration value currently defined is 
// 	EFI_NATIVE_INTERFACE
// Refferals: see InstallProtocolInterface for more information about the type usage.
//<AMI_GHDR_END>
//**********************************************************************
typedef enum { EFI_NATIVE_INTERFACE } EFI_INTERFACE_TYPE;
typedef EFI_STATUS (*EFI_INSTALL_PROTOCOL_INTERFACE)(
	IN OUT EFI_HANDLE *Handle, IN EFI_GUID *Protocol,
	IN EFI_INTERFACE_TYPE InterfaceType, IN VOID *Interface
);
typedef EFI_STATUS (*EFI_REINSTALL_PROTOCOL_INTERFACE)(
	IN EFI_HANDLE Handle, IN EFI_GUID *Protocol,
	IN VOID *OldInterface, IN VOID *NewInterface
);
typedef EFI_STATUS (*EFI_UNINSTALL_PROTOCOL_INTERFACE)(
	IN EFI_HANDLE Handle, IN EFI_GUID *Protocol, 
	IN VOID *Interface
);
typedef EFI_STATUS (*EFI_HANDLE_PROTOCOL)(
	IN EFI_HANDLE Handle, IN EFI_GUID *Protocol,
	OUT VOID **Interface
);
typedef EFI_STATUS (*EFI_REGISTER_PROTOCOL_NOTIFY)(
	IN EFI_GUID *Protocol, IN EFI_EVENT Event, 
	OUT VOID **Registration
);
//**********************************************************************
//<AMI_GHDR_START>
// Name:	EFI_LOCATE_SEARCH_TYPE
// Description:	Enumeration type.
//		Defines search type for the LocateHandle, LocateHandleBuffer, 
//		and LocateProtocol functions.
//	AllHandles  - Protocol and SearchKey are ignored and the function
//		returns an array of every handle in the system.
//	ByRegisterNotify - SearchKey supplies the Registration value returned by
//		RegisterProtocolNotify.The function returns the next handle 
//		that is new or the registration. Only one handle is returned at a time,
//		and the caller must loop until no more handles are returned.
//		Protocol is ignored or this search type.
//	ByProtocol - All handles that support Protocol are returned.
//		SearchKey is ignored or this search type.
//<AMI_GHDR_END>
//**********************************************************************
typedef enum {
	AllHandles, ByRegisterNotify, ByProtocol
} EFI_LOCATE_SEARCH_TYPE;
typedef EFI_STATUS (*EFI_LOCATE_HANDLE)(
	IN EFI_LOCATE_SEARCH_TYPE SearchType, 
	IN EFI_GUID *Protocol OPTIONAL, IN VOID *SearchKey OPTIONAL,
	IN OUT UINTN *BufferSize, OUT EFI_HANDLE *Buffer
);
//*******************************************************
// EFI_DEVICE_PATH_PROTOCOL
//*******************************************************
#pragma pack (push,1)	//May not be alligned on a boundary.
typedef struct _EFI_DEVICE_PATH {
	UINT8 Type;
	UINT8 SubType;
	UINT8 Length[2];
} EFI_DEVICE_PATH_PROTOCOL;
#pragma pack (pop)
typedef EFI_STATUS (*EFI_LOCATE_DEVICE_PATH)(
	IN EFI_GUID *Protocol, IN OUT EFI_DEVICE_PATH_PROTOCOL **DevicePath,
	OUT EFI_HANDLE *Device
);
typedef EFI_STATUS (*EFI_INSTALL_CONFIGURATION_TABLE)(
	IN EFI_GUID *Guid, IN VOID *Table
);
// Image Services
// Supported subsystem values
#define EFI_IMAGE_SUBSYSTEM_EFI_APPLICATION 10
#define EFI_IMAGE_SUBSYSTEM_EFI_BOOT_SERVICE_DRIVER 11
#define EFI_IMAGE_SUBSYSTEM_EFI_RUNTIME_DRIVER 12
#define EFI_IMAGE_SUBSYSTEM_SAL_RUNTIME_DRIVER 13
// Supported machine types
#define EFI_IMAGE_MACHINE_IA32 0x014c
#define EFI_IMAGE_MACHINE_IA64 0x0200
#define EFI_IMAGE_MACHINE_EBC 0x0EBC
typedef EFI_STATUS (*EFI_IMAGE_LOAD)(
	IN BOOLEAN BootPolicy, IN EFI_HANDLE ParentImageHandle,
	IN EFI_DEVICE_PATH_PROTOCOL *FilePath, IN VOID *SourceBuffer OPTIONAL,
	IN UINTN SourceSize, OUT EFI_HANDLE *ImageHandle
);
typedef EFI_STATUS (*EFI_IMAGE_START)(
	IN EFI_HANDLE ImageHandle, OUT UINTN *ExitDataSize,
	OUT CHAR16 **ExitData OPTIONAL
);
typedef EFI_STATUS (*EFI_EXIT)(
	IN EFI_HANDLE ImageHandle, IN EFI_STATUS ExitStatus,
	IN UINTN ExitDataSize, IN CHAR16 *ExitData OPTIONAL
);
typedef EFI_STATUS (*EFI_IMAGE_UNLOAD)(IN EFI_HANDLE ImageHandle);
typedef EFI_STATUS (*EFI_EXIT_BOOT_SERVICES)(
	IN EFI_HANDLE ImageHandle, IN UINTN MapKey
);
// Miscellaneous Services
typedef EFI_STATUS (*EFI_GET_NEXT_MONOTONIC_COUNT)(
	OUT UINT64 *Count
);
typedef EFI_STATUS (*EFI_STALL)(IN UINTN Microseconds);
typedef EFI_STATUS (*EFI_SET_WATCHDOG_TIMER)(
	IN UINTN Timeout, IN UINT64 WatchdogCode,
	IN UINTN DataSize, IN CHAR16 *WatchdogData OPTIONAL
);
// DriverSupport Services
typedef EFI_STATUS (*EFI_CONNECT_CONTROLLER)(
	IN EFI_HANDLE ControllerHandle,
	IN EFI_HANDLE *DriverImageHandle OPTIONAL,
	IN EFI_DEVICE_PATH_PROTOCOL *RemainingDevicePath OPTIONAL,
	IN BOOLEAN Recursive
);
typedef EFI_STATUS (*EFI_DISCONNECT_CONTROLLER)(
	IN EFI_HANDLE ControllerHandle,
	IN EFI_HANDLE DriverImageHandle OPTIONAL,
	IN EFI_HANDLE ChildHandle OPTIONAL
);
// Open and Close Protocol Services
#define EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL 	0x00000001
#define EFI_OPEN_PROTOCOL_GET_PROTOCOL 			0x00000002
#define EFI_OPEN_PROTOCOL_TEST_PROTOCOL 		0x00000004
#define EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER	0x00000008
#define EFI_OPEN_PROTOCOL_BY_DRIVER 			0x00000010
#define EFI_OPEN_PROTOCOL_EXCLUSIVE 			0x00000020
typedef EFI_STATUS (*EFI_OPEN_PROTOCOL)(
	IN EFI_HANDLE Handle, IN EFI_GUID *Protocol,
	OUT VOID **Interface OPTIONAL, IN EFI_HANDLE AgentHandle,
	IN EFI_HANDLE ControllerHandle, IN UINT32 Attributes
);
typedef EFI_STATUS (*EFI_CLOSE_PROTOCOL)(
	IN EFI_HANDLE Handle, IN EFI_GUID *Protocol,
	IN EFI_HANDLE AgentHandle, IN EFI_HANDLE ControllerHandle
);
//**********************************************************************
//<AMI_THDR_START>
//
// Name: EFI_OPEN_PROTOCOL_INFORMATION_ENTRY
//
// Fields: Name					Type		Description
//			AgentHandle			EFI_HANDLE
//			ControllerHandle	EFI_HANDLE 
//			Attributes			UINT32
//			OpenCount			UINT32		
//
// Description:	the fields has the same semantics 
//	as corresponding paramters of OpenProtocol function.
//
//<AMI_THDR_END>
//**********************************************************************
typedef struct {
	EFI_HANDLE AgentHandle;
	EFI_HANDLE ControllerHandle;
	UINT32 Attributes;
	UINT32 OpenCount;
} EFI_OPEN_PROTOCOL_INFORMATION_ENTRY;

typedef EFI_STATUS (*EFI_OPEN_PROTOCOL_INFORMATION)(
	IN EFI_HANDLE Handle, IN EFI_GUID *Protocol,
	OUT EFI_OPEN_PROTOCOL_INFORMATION_ENTRY **EntryBuffer,
	OUT UINTN *EntryCount
);

// Library Services
typedef EFI_STATUS (*EFI_PROTOCOLS_PER_HANDLE)(
	IN EFI_HANDLE Handle, OUT EFI_GUID ***ProtocolBuffer,
	OUT UINTN *ProtocolBufferCount
);
typedef EFI_STATUS (*EFI_LOCATE_HANDLE_BUFFER)(
	IN EFI_LOCATE_SEARCH_TYPE SearchType,
	IN EFI_GUID *Protocol OPTIONAL,
	IN VOID *SearchKey OPTIONAL, IN OUT UINTN *NoHandles,
	OUT EFI_HANDLE **Buffer
);
typedef EFI_STATUS (*EFI_LOCATE_PROTOCOL)(
	IN EFI_GUID *Protocol, IN VOID *Registration OPTIONAL,
	OUT VOID **Interface
);
typedef EFI_STATUS (*EFI_INSTALL_MULTIPLE_PROTOCOL_INTERFACES)(
	IN OUT EFI_HANDLE *Handle, ...
);
typedef EFI_STATUS (*EFI_UNINSTALL_MULTIPLE_PROTOCOL_INTERFACES)(
	IN OUT EFI_HANDLE Handle, ...
);
// 32-bit CRC Services
typedef EFI_STATUS (*EFI_CALCULATE_CRC32)(
	IN VOID *Data, IN UINTN DataSize, OUT UINT32 *Crc32
);
// Memory Utility Services
typedef VOID (*EFI_COPY_MEM)(
IN VOID *Destination, IN VOID *Source, IN UINTN Length
);
typedef VOID (*EFI_SET_MEM)(
	IN VOID *Buffer, IN UINTN Size, IN UINT8 Value
);

//UEFI 2.0 Event Service
//Predefined Event Groups
#define EFI_EVENT_GROUP_EXIT_BOOT_SERVICES  \
 	{0x27abf055, 0xb1b8, 0x4c26, 0x80, 0x48, 0x74, 0x8f, 0x37, 0xba, 0xa2, 0xdf}
#define EFI_EVENT_GROUP_VIRTUAL_ADDRESS_CHANGE  \
	{0x13fa7698, 0xc831, 0x49c7, 0x87, 0xea, 0x8f, 0x43, 0xfc, 0xc2, 0x51, 0x96}
#define EFI_EVENT_GROUP_MEMORY_MAP_CHANGE  \
    {0x78bee926, 0x692f, 0x48fd, 0x9e, 0xdb, 0x1, 0x42, 0x2e, 0xf0, 0xd7, 0xab}
#define EFI_EVENT_GROUP_READY_TO_BOOT  \
    {0x7ce88fb3, 0x4bd7, 0x4679, 0x87, 0xa8, 0xa8, 0xd8, 0xde, 0xe5, 0xd, 0x2b}

typedef EFI_STATUS (*EFI_CREATE_EVENT_EX)(
    IN UINT32 Type, IN EFI_TPL NotifyTpl,     
    IN EFI_EVENT_NOTIFY NotifyFunction OPTIONAL,
    IN CONST VOID *NotifyContext OPTIONAL,
    IN CONST EFI_GUID *EventGroup OPTIONAL,
    OUT EFI_EVENT *Event
);

#define EFI_BOOT_SERVICES_SIGNATURE 0x56524553544f4f42
#ifndef EFI_SPECIFICATION_VERSION
#define EFI_BOOT_SERVICES_REVISION ((1<<16) | (10))
#else
#define EFI_BOOT_SERVICES_REVISION EFI_SPECIFICATION_VERSION
#endif
typedef struct {
	EFI_TABLE_HEADER					Hdr;
	// Task Priority Services
	EFI_RAISE_TPL 						RaiseTPL;
	EFI_RESTORE_TPL 					RestoreTPL;
	// Memory Services
	EFI_ALLOCATE_PAGES 					AllocatePages;
	EFI_FREE_PAGES 						FreePages;
	EFI_GET_MEMORY_MAP 					GetMemoryMap;
	EFI_ALLOCATE_POOL 					AllocatePool;
	EFI_FREE_POOL 						FreePool;
	// Event & Timer Services
	EFI_CREATE_EVENT 					CreateEvent;
	EFI_SET_TIMER 						SetTimer;
	EFI_WAIT_FOR_EVENT 					WaitForEvent;
	EFI_SIGNAL_EVENT 					SignalEvent;
	EFI_CLOSE_EVENT 					CloseEvent;
	EFI_CHECK_EVENT 					CheckEvent;
	// Protocol Handler Services
	EFI_INSTALL_PROTOCOL_INTERFACE 		InstallProtocolInterface;
	EFI_REINSTALL_PROTOCOL_INTERFACE 	ReinstallProtocolInterface;
	EFI_UNINSTALL_PROTOCOL_INTERFACE	UninstallProtocolInterface;
	EFI_HANDLE_PROTOCOL					HandleProtocol;
	VOID 								*Reserved;
	EFI_REGISTER_PROTOCOL_NOTIFY 		RegisterProtocolNotify;
	EFI_LOCATE_HANDLE 					LocateHandle;
	EFI_LOCATE_DEVICE_PATH 				LocateDevicePath;
	EFI_INSTALL_CONFIGURATION_TABLE 	InstallConfigurationTable;
	// Image Services
	EFI_IMAGE_LOAD 						LoadImage;
	EFI_IMAGE_START 					StartImage;
	EFI_EXIT 							Exit;
	EFI_IMAGE_UNLOAD 					UnloadImage;
	EFI_EXIT_BOOT_SERVICES 				ExitBootServices;
	// Miscellaneous Services
	EFI_GET_NEXT_MONOTONIC_COUNT 		GetNextMonotonicCount;
	EFI_STALL 							Stall;
	EFI_SET_WATCHDOG_TIMER 				SetWatchdogTimer;
	// DriverSupport Services
	EFI_CONNECT_CONTROLLER 				ConnectController;
	EFI_DISCONNECT_CONTROLLER 			DisconnectController;
	// Open and Close Protocol Services
	EFI_OPEN_PROTOCOL 					OpenProtocol;
	EFI_CLOSE_PROTOCOL 					CloseProtocol;
	EFI_OPEN_PROTOCOL_INFORMATION 		OpenProtocolInformation;
	// Library Services
	EFI_PROTOCOLS_PER_HANDLE 			ProtocolsPerHandle;
	EFI_LOCATE_HANDLE_BUFFER 			LocateHandleBuffer;
	EFI_LOCATE_PROTOCOL 				LocateProtocol;
	EFI_INSTALL_MULTIPLE_PROTOCOL_INTERFACES InstallMultipleProtocolInterfaces;
	EFI_UNINSTALL_MULTIPLE_PROTOCOL_INTERFACES UninstallMultipleProtocolInterfaces;
	// 32-bit CRC Services
	EFI_CALCULATE_CRC32 				CalculateCrc32;
	// Memory Utility Services
	EFI_COPY_MEM 						CopyMem;
	EFI_SET_MEM 						SetMem;
#if EFI_SPECIFICATION_VERSION >=0x20000
    // UEFI 2.0 Event Service
    EFI_CREATE_EVENT_EX                 CreateEventEx;
#endif
} EFI_BOOT_SERVICES;


//*******************************************************
//Efi Runtime Services
//*******************************************************

//*******************************************************
//EFI_TIME
//*******************************************************
// This represents the current time information
typedef struct {
    UINT16  Year;       // 1998 - 2097
    UINT8   Month;      // 1 - 12
    UINT8   Day;        // 1 - 31
    UINT8   Hour;       // 0 - 23
    UINT8   Minute;     // 0 - 59
    UINT8   Second;     // 0 - 59
    UINT8   Pad1;
    UINT32  Nanosecond; // 0 - 999,999,999
    INT16   TimeZone;   // -1440 to 1440 or EFI_UNSPECIFIED_TIMEZONE
    UINT8   Daylight;
    UINT8   Pad2;
} EFI_TIME;

//*******************************************************
// Bit Definitions for EFI_TIME.Daylight. See below.
//*******************************************************
#define EFI_TIME_ADJUST_DAYLIGHT 0x01
#define EFI_TIME_IN_DAYLIGHT 0x02

//*******************************************************
// Value Definition for EFI_TIME.TimeZone. See below.
//*******************************************************
#define EFI_UNSPECIFIED_TIMEZONE 0x07FF

//*******************************************************
// EFI_TIME_CAPABILITIES
//*******************************************************
// This provides the capabilities of the
// real time clock device as exposed through the EFI interfaces.
typedef struct {
    UINT32  Resolution;
    UINT32  Accuracy;
    BOOLEAN SetsToZero;
} EFI_TIME_CAPABILITIES;

typedef EFI_STATUS (*EFI_GET_TIME) (
    OUT EFI_TIME                *Time,
    OUT EFI_TIME_CAPABILITIES   *Capabilities OPTIONAL
);

typedef EFI_STATUS (*EFI_SET_TIME) (
    IN EFI_TIME *Time
);

typedef EFI_STATUS (*EFI_GET_WAKEUP_TIME) (
    OUT BOOLEAN     *Enabled,
    OUT BOOLEAN     *Pending,
    OUT EFI_TIME    *Time
);

typedef EFI_STATUS (*EFI_SET_WAKEUP_TIME) (
    IN BOOLEAN      Enable,
    IN EFI_TIME     *Time OPTIONAL
);

// Virtual Memory Services
typedef EFI_STATUS (*EFI_SET_VIRTUAL_ADDRESS_MAP)(
	IN UINTN MemoryMapSize, IN UINTN DescriptorSize,
	IN UINT32 DescriptorVersion, IN EFI_MEMORY_DESCRIPTOR *VirtualMap
);

#define EFI_OPTIONAL_PTR 1
typedef EFI_STATUS (*EFI_CONVERT_POINTER)(
	IN UINTN DebugDisposition, IN VOID **Address
);
// Variable Services
#define EFI_GLOBAL_VARIABLE \
	{0x8BE4DF61,0x93CA,0x11d2,0xAA,0xD,0x0,0xE0,0x98,0x03,0x2B,0x8C}

typedef EFI_STATUS (*EFI_GET_VARIABLE)(
	IN CHAR16 *VariableName, IN EFI_GUID *VendorGuid,
	OUT UINT32 *Attributes OPTIONAL, IN OUT UINTN *DataSize,
	OUT VOID *Data
);
typedef EFI_STATUS (*EFI_GET_NEXT_VARIABLE_NAME)(
	IN OUT UINTN *VariableNameSize, IN OUT CHAR16 *VariableName,
	IN OUT EFI_GUID *VendorGuid
);
typedef EFI_STATUS (*EFI_SET_VARIABLE)(
	IN CHAR16 *VariableName, IN EFI_GUID *VendorGuid,
	IN UINT32 Attributes, IN UINTN DataSize, IN VOID *Data
);
// Miscellaneous Services
typedef EFI_STATUS (*EFI_GET_NEXT_HIGH_MONO_COUNT)(OUT UINT32 *HighCount);
//*******************************************************
// EFI_RESET_TYPE
//*******************************************************
typedef enum { EfiResetCold, EfiResetWarm, EfiResetShutdown, EfiResetUpdate } EFI_RESET_TYPE;
typedef EFI_STATUS (*EFI_RESET_SYSTEM)(
	IN EFI_RESET_TYPE ResetType, IN EFI_STATUS ResetStatus,
	IN UINTN DataSize, IN CHAR16 *ResetData OPTIONAL
);

// Status Code Type Definition
typedef UINT32 EFI_STATUS_CODE_TYPE;

// A Status Code Type is made up of the code type and severity
// All values masked by EFI_STATUS_CODE_RESERVED_MASK are
// reserved for use by this specification.
#define EFI_STATUS_CODE_TYPE_MASK 0x000000FF
#define EFI_STATUS_CODE_SEVERITY_MASK 0xFF000000
#define EFI_STATUS_CODE_RESERVED_MASK 0x00FFFF00

// Definition of code types, all other values masked by
// EFI_STATUS_CODE_TYPE_MASK are reserved for use by
// this specification.
#define EFI_PROGRESS_CODE 0x00000001
#define EFI_ERROR_CODE 0x00000002
#define EFI_DEBUG_CODE 0x00000003

// Definitions of severities, all other values masked by
// EFI_STATUS_CODE_SEVERITY_MASK are reserved for use by
// this specification.
// Uncontained errors are major errors that could not contained
// to the specific component that is reporting the error
// For example, if a memory error was not detected early enough,
// the bad data could be consumed by other drivers.
#define EFI_ERROR_MINOR 0x40000000
#define EFI_ERROR_MAJOR 0x80000000
#define EFI_ERROR_UNRECOVERED 0x90000000
#define EFI_ERROR_UNCONTAINED 0xa0000000

// Status Code Value Definition
typedef UINT32 EFI_STATUS_CODE_VALUE;

// A Status Code Value is made up of the class, subclass, and
// an operation.
#define EFI_STATUS_CODE_CLASS_MASK 0xFF000000
#define EFI_STATUS_CODE_SUBCLASS_MASK 0x00FF0000
#define EFI_STATUS_CODE_OPERATION_MASK 0x0000FFFF

// Definition of Status Code extended data header.
// The data will follow HeaderSize bytes from the beginning of
// the structure and is Size bytes long.
typedef struct {
	UINT16 HeaderSize;
	UINT16 Size;
	EFI_GUID Type;
} EFI_STATUS_CODE_DATA;

typedef EFI_STATUS (EFIAPI *EFI_REPORT_STATUS_CODE)(
	IN EFI_STATUS_CODE_TYPE Type, IN EFI_STATUS_CODE_VALUE Value,
	IN UINT32 Instance, IN EFI_GUID *CallerId OPTIONAL,
	IN EFI_STATUS_CODE_DATA *Data OPTIONAL
);

// UEFI 2.0 Capsule Services
typedef struct {
    UINT64 Length;
    union { 
        EFI_PHYSICAL_ADDRESS DataBlock;
        EFI_PHYSICAL_ADDRESS ContinuationPointer; 
    };
} EFI_CAPSULE_BLOCK_DESCRIPTOR;

typedef struct {
    EFI_GUID CapsuleGuid;
    UINT32 HeaderSize;
    UINT32 Flags;
    UINT32 CapsuleImageSize;
} EFI_CAPSULE_HEADER;

#define CAPSULE_FLAGS_PERSIST_ACROSS_RESET  0x00010000
#define CAPSULE_FLAGS_POPULATE_SYSTEM_TABLE 0x00020000
#define CAPSULE_FLAGS_INITIATE_RESET        0x00040000

typedef EFI_STATUS (*EFI_UPDATE_CAPSULE) (
    IN EFI_CAPSULE_HEADER **CapsuleHeaderArray,
    IN UINTN CapsuleCount,
    IN EFI_PHYSICAL_ADDRESS ScatterGatherList OPTIONAL
);

typedef EFI_STATUS (*EFI_QUERY_CAPSULE_CAPABILITIES) (
    IN EFI_CAPSULE_HEADER	**CapsuleHeaderArray,
    IN UINTN CapsuleCount,
    OUT	UINT64 *MaximumCapsuleSize,
    OUT EFI_RESET_TYPE *ResetType
);

// Miscellaneous UEFI 2.0 Service
typedef EFI_STATUS (*EFI_QUERY_VARIABLE_INFO) (
    IN UINT32 Attributes,
    OUT UINT64 *MaximumVariableStorageSize,
    OUT UINT64 *RemainingVariableStorageSize,
    OUT UINT64 *MaximumVariableSize
);

#define EFI_RUNTIME_SERVICES_SIGNATURE 0x56524553544e5552
#ifndef EFI_SPECIFICATION_VERSION
#define EFI_RUNTIME_SERVICES_REVISION ((1<<16) | (10))
#else
#define EFI_RUNTIME_SERVICES_REVISION EFI_SPECIFICATION_VERSION
#endif
typedef struct {
	EFI_TABLE_HEADER 				Hdr;
	// Time Services
	EFI_GET_TIME 					GetTime;
	EFI_SET_TIME 					SetTime;
	EFI_GET_WAKEUP_TIME 			GetWakeupTime;
	EFI_SET_WAKEUP_TIME 			SetWakeupTime;
	// Virtual Memory Services
	EFI_SET_VIRTUAL_ADDRESS_MAP 	SetVirtualAddressMap;
	EFI_CONVERT_POINTER 			ConvertPointer;
	// Variable Services
	EFI_GET_VARIABLE 				GetVariable;
	EFI_GET_NEXT_VARIABLE_NAME 		GetNextVariableName;
	EFI_SET_VARIABLE 				SetVariable;
	// Miscellaneous Services
	EFI_GET_NEXT_HIGH_MONO_COUNT	GetNextHighMonotonicCount;
	EFI_RESET_SYSTEM 				ResetSystem;
#if EFI_SPECIFICATION_VERSION <0x20000
    // ReportStatusCode is removed from this table in UEFI2.0
	EFI_REPORT_STATUS_CODE			ReportStatusCode;
#else
    // UEFI 2.0 Capsule Services
    EFI_UPDATE_CAPSULE              UpdateCapsule;             
    EFI_QUERY_CAPSULE_CAPABILITIES  QueryCapsuleCapabilities; 
 
    // Miscellaneous UEFI 2.0 Service
    EFI_QUERY_VARIABLE_INFO         QueryVariableInfo;         

#endif
} EFI_RUNTIME_SERVICES;

#define ACPI_20_TABLE_GUID \
	{0x8868e871,0xe4f1,0x11d3,0xbc,0x22,0x0,0x80,0xc7,0x3c,0x88,0x81}
#define ACPI_TABLE_GUID \
	{0xeb9d2d30,0x2d88,0x11d3,0x9a,0x16,0x0,0x90,0x27,0x3f,0xc1,0x4d}
#define SAL_SYSTEM_TABLE_GUID \
	{0xeb9d2d32,0x2d88,0x11d3,0x9a,0x16,0x0,0x90,0x27,0x3f,0xc1,0x4d}
#define SMBIOS_TABLE_GUID \
	{0xeb9d2d31,0x2d88,0x11d3,0x9a,0x16,0x0,0x90,0x27,0x3f,0xc1,0x4d}
#define MPS_TABLE_GUID \
	{0xeb9d2d2f,0x2d88,0x11d3,0x9a,0x16,0x0,0x90,0x27,0x3f,0xc1,0x4d}

// ACPI 2.0 or newer tables should use EFI_ACPI_TABLE_GUID
#define EFI_ACPI_TABLE_GUID ACPI_20_TABLE_GUID
#define ACPI_10_TABLE_GUID ACPI_TABLE_GUID

typedef struct{
	EFI_GUID VendorGuid;
	VOID *VendorTable;
} EFI_CONFIGURATION_TABLE;

//forward declarations
typedef	struct _EFI_SIMPLE_TEXT_INPUT_PROTOCOL EFI_SIMPLE_TEXT_INPUT_PROTOCOL;
typedef	struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;

#define EFI_SYSTEM_TABLE_SIGNATURE 0x5453595320494249
#ifndef EFI_SPECIFICATION_VERSION
#define EFI_SYSTEM_TABLE_REVISION ((1<<16) | (10))
#else
#define EFI_SYSTEM_TABLE_REVISION EFI_SPECIFICATION_VERSION
#define EFI_2_31_SYSTEM_TABLE_REVISION  ((2<<16) | (31))
#define EFI_2_30_SYSTEM_TABLE_REVISION  ((2<<16) | (30))
#define EFI_2_20_SYSTEM_TABLE_REVISION  ((2<<16) | (20))
#define EFI_2_10_SYSTEM_TABLE_REVISION  ((2<<16) | (10))
#define EFI_2_00_SYSTEM_TABLE_REVISION  ((2<<16) | (00))
#define EFI_1_10_SYSTEM_TABLE_REVISION  ((1<<16) | (10))
#define EFI_1_02_SYSTEM_TABLE_REVISION  ((1<<16) | (02))
#endif
typedef struct {
	EFI_TABLE_HEADER 				Hdr;
	CHAR16 							*FirmwareVendor;
	UINT32 							FirmwareRevision;
	EFI_HANDLE 						ConsoleInHandle;
	EFI_SIMPLE_TEXT_INPUT_PROTOCOL 			*ConIn;
	EFI_HANDLE 						ConsoleOutHandle;
	EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL	*ConOut;
	EFI_HANDLE 						StandardErrorHandle;
	EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL 	*StdErr;
	EFI_RUNTIME_SERVICES 			*RuntimeServices;
	EFI_BOOT_SERVICES 				*BootServices;
	UINTN 							NumberOfTableEntries;
	EFI_CONFIGURATION_TABLE			*ConfigurationTable;
} EFI_SYSTEM_TABLE;

typedef EFI_STATUS (EFIAPI *EFI_IMAGE_ENTRY_POINT) (
	IN EFI_HANDLE ImageHandle,
	IN EFI_SYSTEM_TABLE *SystemTable
);

// EFI_BOOT_MODE
typedef UINT32 EFI_BOOT_MODE;

#define BOOT_WITH_FULL_CONFIGURATION                    0x00
#define BOOT_WITH_MINIMAL_CONFIGURATION                 0x01
#define BOOT_ASSUMING_NO_CONFIGURATION_CHANGES          0x02
#define BOOT_WITH_FULL_CONFIGURATION_PLUS_DIAGNOSTICS   0x03
#define BOOT_WITH_DEFAULT_SETTINGS                      0x04
#define BOOT_ON_S4_RESUME                               0x05
#define BOOT_ON_S5_RESUME                               0x06
#define BOOT_ON_S2_RESUME                               0x10
#define BOOT_ON_S3_RESUME                               0x11
#define BOOT_ON_FLASH_UPDATE                            0x12
#define BOOT_IN_RECOVERY_MODE                           0x20
//0x21 - 0xF..F Reserved Encodings

//*******************************************************
// Boot Option Attributes
//*******************************************************
#define LOAD_OPTION_ACTIVE 0x00000001
#define LOAD_OPTION_FORCE_RECONNECT 0x00000002
#if EFI_SPECIFICATION_VERSION >= 0x2000A
#define LOAD_OPTION_HIDDEN            0x00000008
#define LOAD_OPTION_CATEGORY          0x00001F00
#define LOAD_OPTION_CATEGORY_BOOT     0x00000000
#define LOAD_OPTION_CATEGORY_APP      0x00000100

#define EFI_BOOT_OPTION_SUPPORT_KEY   0x00000001
#define EFI_BOOT_OPTION_SUPPORT_APP   0x00000002
#define EFI_BOOT_OPTION_SUPPORT_COUNT 0x00000300
#endif
#pragma pack(push,1)
typedef struct{
	UINT32 Attributes;
	UINT16 FilePathListLength;
//	CHAR16 Description[];
//	EFI_DEVICE_PATH_PROTOCOL FilePathList[];
//	UINT8 OptionalData[];
} EFI_LOAD_OPTION;
#pragma pack(pop)

#if EFI_SPECIFICATION_VERSION >= 0x2000A
typedef union {
    struct {
        UINT32  Revision        : 8;
        UINT32  ShiftPressed    : 1;
        UINT32  ControlPressed  : 1;
        UINT32  AltPressed      : 1;
        UINT32  LogoPressed     : 1;
        UINT32  MenuPressed     : 1;
        UINT32  SysReqPessed    : 1;
        UINT32  Reserved        : 16;
        UINT32  InputKeyCount   : 2;
  }       Options;
  UINT32  PackedValue;
} EFI_BOOT_KEY_DATA, HOT_KEY_EFI_KEY_DATA;

typedef struct {
    EFI_BOOT_KEY_DATA     KeyOptions;
    UINT32                BootOptionCrc;
    UINT16                BootOption;
//  EFI_INPUT_KEY         Keys[];
} EFI_KEY_OPTION;
#endif

// EFI File location to boot from on removable media devices
#define EFI_REMOVABLE_MEDIA_FILE_NAME_IA32    L"\\EFI\\BOOT\\BOOTIA32.EFI"
#define EFI_REMOVABLE_MEDIA_FILE_NAME_IA64    L"\\EFI\\BOOT\\BOOTIA64.EFI"
#define EFI_REMOVABLE_MEDIA_FILE_NAME_X64     L"\\EFI\\BOOT\\BOOTX64.EFI"
#if defined(EFI64)
#define EFI_REMOVABLE_MEDIA_FILE_NAME EFI_REMOVABLE_MEDIA_FILE_NAME_IA64
#elseif deinfed(EFIx64)
#define EFI_REMOVABLE_MEDIA_FILE_NAME EFI_REMOVABLE_MEDIA_FILE_NAME_X64
#else
#define EFI_REMOVABLE_MEDIA_FILE_NAME EFI_REMOVABLE_MEDIA_FILE_NAME_IA32
#endif

#ifndef GUID_VARIABLE_DEFINITION
#define GUID_VARIABLE_DECLARATION(Variable, Guid) extern EFI_GUID Variable
#else
#define GUID_VARIABLE_DECLARATION(Variable, Guid) GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID Variable=Guid
#endif
#define EFI_FORWARD_DECLARATION(x) typedef struct _##x x
/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
