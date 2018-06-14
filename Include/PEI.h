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
// $Header: /Alaska/BIN/Core/Include/PEI.h 13    6/16/11 2:52p Felixp $
//
// $Revision: 13 $
//
// $Date: 6/16/11 2:52p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/PEI.h $
// 
// 13    6/16/11 2:52p Felixp
// Surround backward compatibility definitions with #if
// BACKWARD_COMPATIBLE_MODE
// 
// 12    5/27/11 5:49p Felixp
// The definitions that will be removed in the future versions are marked
// with the comments.
// 
// 11    3/16/11 11:31p Felixp
// Several identifiers have been updated to match with the latest revision
// of the PI spec.
// 
// 10    3/09/11 5:36p Artems
// PI 1.0 clean-up - added EFI_FV_INFO and EFI_FV_FILE_INFO definitions
// 
// 9     2/05/11 1:48p Artems
// Added PI 1.0-1.1 support
// 
// 8     11/02/06 10:25p Felixp
// EFI_PEI_END_OF_PEI_PHASE_PPI_GUID added
// 
// 7     3/13/06 1:15a Felixp
// 
// 6     6/06/05 7:49p Felixp
// 
// 5     6/06/05 1:24p Felixp
// Type parameter removed from AllocatePages to match PEI CIS 0.91
// 
// 4     6/03/05 3:44p Felixp
// Updated to support changes introduced in PEI CIS 0.91
// 
// 3     3/22/05 5:31p Felixp
// 
// 2     3/04/05 10:20a Mandal
// 
// 1     1/28/05 12:44p Felixp
// 
// 3     1/18/05 3:21p Felixp
// PrintDebugMessage renamed to Trace
// 
// 1     12/23/04 9:41a Felixp
// 
// 11    3/29/04 2:32a Felixp
// 
// 10    2/24/04 10:20a Felixp
// 
// 9     2/04/04 12:34a Felixp
// definition of EFI_PEI_REPORT_STATUS_CODE is fixed
// to match the spec (PEICIS)
// 
// 8     1/28/04 3:24a Felixp
// 
// 7     1/19/04 4:25p Felixp
// EFI_PEIM_ENTRY_POINT added
// 
// 6     1/06/04 4:02p Felixp
// 
// 5     12/29/03 6:58p Felixp
// 
// 4     12/29/03 5:25p Felixp
// preffix 'EFI_' added to the names of the PEIM descriptor structures and
// flags
// 
// 3     12/17/03 11:08a Markw
// Uncommented Hob and FFS defintions. Added Boot Mode include.
// 
// 2     12/15/03 5:33p Robert
// 
// 1     12/15/03 3:40p Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	pei.h
//
// Description:	PEI definitions
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __PEI__H__
#define __PEI__H__

#include "efi.h"
#include "ffs.h"

#ifdef __cplusplus
extern "C" {
#endif

// EFI PEI Services Table
#define PEI_SERVICES_SIGNATURE 0x5652455320494550
// PEI Specification Revision information
#ifndef PI_SPECIFICATION_VERSION
#define PI_SPECIFICATION_VERSION 91
#endif
#define PEI_SERVICES_REVISION PI_SPECIFICATION_VERSION
#define PEI_SPECIFICATION_MAJOR_REVISION ((PEI_SERVICES_REVISION)>>16)
#define PEI_SPECIFICATION_MINOR_REVISION ((UINT16)(PEI_SERVICES_REVISION))

//=========================================================================

// PEI Ppi Services List Descriptors
#define EFI_PEI_PPI_DESCRIPTOR_PIC 0x00000001
#define EFI_PEI_PPI_DESCRIPTOR_PPI 0x00000010
#define EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK 0x00000020
#define EFI_PEI_PPI_DESCRIPTOR_NOTIFY_DISPATCH 0x00000040
#define EFI_PEI_PPI_DESCRIPTOR_NOTIFY_TYPES 0x00000060
#define EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST 0x80000000

typedef VOID *EFI_PEI_FILE_HANDLE;
typedef VOID *EFI_PEI_FV_HANDLE;

typedef struct _EFI_SEC_PEI_HAND_OFF {
    UINT16      DataSize;
    VOID        *BootFirmwareVolumeBase;
    UINTN       BootFirmwareVolumeSize;
    VOID        *TemporaryRamBase;
    UINTN       TemporaryRamSize;
    VOID        *PeiTemporaryRamBase;
    UINTN       PeiTemporaryRamSize;
    VOID        *StackBase;
    UINTN       StackSize;
} EFI_SEC_PEI_HAND_OFF;

typedef
EFI_STATUS
(EFIAPI *EFI_PEIM_NOTIFY_ENTRY_POINT) (
  IN struct _EFI_PEI_SERVICES       **PeiServices,
  IN struct _EFI_PEI_NOTIFY_DESCRIPTOR  *NotifyDescriptor,
  IN VOID                           *Ppi
  );

typedef struct _EFI_PEI_PPI_DESCRIPTOR {
  UINTN                        Flags;
  EFI_GUID                     *Guid;
  VOID                         *Ppi;
} EFI_PEI_PPI_DESCRIPTOR;

typedef struct _EFI_PEI_NOTIFY_DESCRIPTOR {
  UINTN                        Flags;
  EFI_GUID                     *Guid;
  EFI_PEIM_NOTIFY_ENTRY_POINT  Notify;
} EFI_PEI_NOTIFY_DESCRIPTOR;

typedef union {
  EFI_PEI_NOTIFY_DESCRIPTOR Notify;
  EFI_PEI_PPI_DESCRIPTOR Ppi;
} EFI_PEI_DESCRIPTOR;

struct _EFI_PEI_SERVICES;

typedef
EFI_STATUS
(EFIAPI *EFI_PEI_INSTALL_PPI) (
  IN struct _EFI_PEI_SERVICES    **PeiServices,
  IN EFI_PEI_PPI_DESCRIPTOR          *PpiList
  );

typedef
EFI_STATUS
(EFIAPI *EFI_PEI_REINSTALL_PPI) (
  IN struct _EFI_PEI_SERVICES    **PeiServices,
  IN EFI_PEI_PPI_DESCRIPTOR          *OldPpi,
  IN EFI_PEI_PPI_DESCRIPTOR          *NewPpi
  );

typedef
EFI_STATUS
(EFIAPI *EFI_PEI_LOCATE_PPI) (
  IN struct _EFI_PEI_SERVICES    **PeiServices,
  IN EFI_GUID                    *Guid,
  IN UINTN                       Instance,
  IN OUT EFI_PEI_PPI_DESCRIPTOR      **PpiDescriptor,
  IN OUT VOID                    **Ppi
  );

typedef
EFI_STATUS
(EFIAPI *EFI_PEI_NOTIFY_PPI) (
  IN struct _EFI_PEI_SERVICES    **PeiServices,
  IN EFI_PEI_NOTIFY_DESCRIPTOR       *NotifyList
  );


// EFI PEI Boot Mode Services
typedef
EFI_STATUS
(EFIAPI *EFI_PEI_GET_BOOT_MODE) (
  IN struct _EFI_PEI_SERVICES    **PeiServices,
  IN OUT EFI_BOOT_MODE           *BootMode
  );

typedef
EFI_STATUS
(EFIAPI *EFI_PEI_SET_BOOT_MODE) (
  IN struct _EFI_PEI_SERVICES    **PeiServices,
  IN EFI_BOOT_MODE               BootMode
  );


// PEI HOB Services
typedef
EFI_STATUS
(EFIAPI *EFI_PEI_GET_HOB_LIST) (
  IN struct _EFI_PEI_SERVICES    **PeiServices,
  IN OUT VOID                    **HobList
  );

typedef
EFI_STATUS
(EFIAPI *EFI_PEI_CREATE_HOB) (
  IN struct _EFI_PEI_SERVICES    **PeiServices,
  IN UINT16                      Type,
  IN UINT16                      Length,
  IN OUT VOID                    **Hob
  );


// FFS Fw Volume support functions
#if PI_SPECIFICATION_VERSION>=0x00010000
typedef
EFI_STATUS
(EFIAPI *EFI_PEI_FFS_FIND_NEXT_VOLUME2) (
  IN struct _EFI_PEI_SERVICES        **PeiServices,
  IN UINTN                           Instance,
  IN OUT EFI_PEI_FV_HANDLE           *FwVolHeader
  );

typedef
EFI_STATUS
(EFIAPI *EFI_PEI_FFS_FIND_NEXT_FILE2) (
  IN struct _EFI_PEI_SERVICES    **PeiServices,
  IN UINT8                       SearchType,
  IN EFI_PEI_FV_HANDLE           FwVolHeader,
  IN OUT EFI_PEI_FILE_HANDLE     *FileHeader
  );

typedef
EFI_STATUS
(EFIAPI *EFI_PEI_FFS_FIND_SECTION_DATA2) (
  IN struct _EFI_PEI_SERVICES    **PeiServices,
  IN EFI_SECTION_TYPE            SectionType,
  IN EFI_PEI_FILE_HANDLE         FfsFileHeader,
  IN OUT VOID                    **SectionData
  );
#else
typedef
EFI_STATUS
(EFIAPI *EFI_PEI_FFS_FIND_NEXT_VOLUME) (
  IN struct _EFI_PEI_SERVICES        **PeiServices,
  IN UINTN                           Instance,
  IN OUT EFI_FIRMWARE_VOLUME_HEADER  **FwVolHeader
  );

typedef
EFI_STATUS
(EFIAPI *EFI_PEI_FFS_FIND_NEXT_FILE) (
  IN struct _EFI_PEI_SERVICES    **PeiServices,
  IN UINT8                       SearchType,
  IN EFI_FIRMWARE_VOLUME_HEADER  *FwVolHeader,
  IN OUT EFI_FFS_FILE_HEADER     **FileHeader
  );

typedef
EFI_STATUS
(EFIAPI *EFI_PEI_FFS_FIND_SECTION_DATA) (
  IN struct _EFI_PEI_SERVICES    **PeiServices,
  IN EFI_SECTION_TYPE            SectionType,
  IN EFI_FFS_FILE_HEADER         *FfsFileHeader,
  IN OUT VOID                    **SectionData
  );
#endif

// Memory Services
typedef
EFI_STATUS
(EFIAPI *EFI_PEI_INSTALL_PEI_MEMORY) (
  IN struct _EFI_PEI_SERVICES   **PeiServices,
  IN EFI_PHYSICAL_ADDRESS       MemoryBegin,
  IN UINT64                     MemoryLength
  );

typedef
EFI_STATUS
(EFIAPI *EFI_PEI_ALLOCATE_PAGES) (
  IN struct _EFI_PEI_SERVICES   **PeiServices,
  IN EFI_MEMORY_TYPE            MemoryType,
  IN UINTN                      Pages,
  IN OUT EFI_PHYSICAL_ADDRESS   *Memory
  );

typedef
EFI_STATUS
(EFIAPI *EFI_PEI_ALLOCATE_POOL) ( 
  IN struct _EFI_PEI_SERVICES   **PeiServices,
  IN UINTN                      Size,
  OUT VOID                      **Buffer
  );

typedef
VOID
(EFIAPI *EFI_PEI_COPY_MEM) ( 
  IN VOID                       *Destination,
  IN VOID                       *Source,
  IN UINTN                      Length
  );

typedef
VOID
(EFIAPI *EFI_PEI_SET_MEM) ( 
  IN VOID                       *Buffer,
  IN UINTN                      Size,
  IN UINT8                      Value
  );

typedef 
EFI_STATUS
(EFIAPI *EFI_PEI_REPORT_STATUS_CODE) (
  IN struct _EFI_PEI_SERVICES **PeiServices,
  IN EFI_STATUS_CODE_TYPE     Type,
  IN EFI_STATUS_CODE_VALUE    Value,  
  IN UINT32                   Instance,
  IN EFI_GUID                 *CallerId OPTIONAL, 
  IN EFI_STATUS_CODE_DATA     *Data OPTIONAL
  );

typedef
EFI_STATUS
(EFIAPI *EFI_PEI_RESET_SYSTEM) (
  IN struct _EFI_PEI_SERVICES   **PeiServices
  );

//forward declaration
typedef struct _EFI_PEI_SERVICES EFI_PEI_SERVICES;

//CPU I/O
typedef	struct _EFI_PEI_CPU_IO_PPI EFI_PEI_CPU_IO_PPI;

typedef	enum{
	EfiPeiCpuIoWidthUint8,
	EfiPeiCpuIoWidthUint16,
	EfiPeiCpuIoWidthUint32,
	EfiPeiCpuIoWidthUint64,
	EfiPeiCpuIoWidthFifoUint8,
	EfiPeiCpuIoWidthFifoUint16,
	EfiPeiCpuIoWidthFifoUint32,
	EfiPeiCpuIoWidthFifoUint64,
	EfiPeiCpuIoWidthFillUint8,
	EfiPeiCpuIoWidthFillUint16,
	EfiPeiCpuIoWidthFillUint32,
	EfiPeiCpuIoWidthFillUint64,
	EfiPeiCpuIoWidthMaximum
} EFI_PEI_CPU_IO_PPI_WIDTH;

typedef
EFI_STATUS
(EFIAPI	*EFI_PEI_CPU_IO_PPI_IO_MEM)	 (
	IN CONST EFI_PEI_SERVICES			**PeiServices,
	IN CONST EFI_PEI_CPU_IO_PPI		*This,
	IN EFI_PEI_CPU_IO_PPI_WIDTH	Width,
	IN UINT64					Address,
	IN UINTN					Count,
	IN OUT VOID					*Buffer
	);

typedef
UINT8
(EFIAPI	*EFI_PEI_CPU_IO_PPI_IO_READ8)	(
	IN CONST EFI_PEI_SERVICES			**PeiServices,
	IN CONST EFI_PEI_CPU_IO_PPI		*This,
	IN UINT64					Address
	);

typedef
UINT16
(EFIAPI	*EFI_PEI_CPU_IO_PPI_IO_READ16) (
	IN CONST EFI_PEI_SERVICES			**PeiServices,
	IN CONST EFI_PEI_CPU_IO_PPI		*This,
	IN UINT64					Address
	);

typedef
UINT32
(EFIAPI	*EFI_PEI_CPU_IO_PPI_IO_READ32) (
	IN CONST EFI_PEI_SERVICES			**PeiServices,
	IN CONST EFI_PEI_CPU_IO_PPI		*This,
	IN UINT64					Address
	);

typedef
UINT64
(EFIAPI	*EFI_PEI_CPU_IO_PPI_IO_READ64) (
	IN CONST EFI_PEI_SERVICES			**PeiServices,
	IN CONST EFI_PEI_CPU_IO_PPI		*This,
	IN UINT64					Address
	);

typedef
VOID
(EFIAPI	*EFI_PEI_CPU_IO_PPI_IO_WRITE8) (
	IN CONST EFI_PEI_SERVICES			**PeiServices,
	IN CONST EFI_PEI_CPU_IO_PPI		*This,
	IN UINT64					Address,
	IN UINT8					Data
	);

typedef
VOID
(EFIAPI	*EFI_PEI_CPU_IO_PPI_IO_WRITE16)	(
	IN CONST EFI_PEI_SERVICES			**PeiServices,
	IN CONST EFI_PEI_CPU_IO_PPI		*This,
	IN UINT64					Address,
	IN UINT16					Data
	);

typedef
VOID
(EFIAPI	*EFI_PEI_CPU_IO_PPI_IO_WRITE32)	(
	IN CONST EFI_PEI_SERVICES			**PeiServices,
	IN CONST EFI_PEI_CPU_IO_PPI		*This,
	IN UINT64					Address,
	IN UINT32					Data
	);

typedef
VOID
(EFIAPI	*EFI_PEI_CPU_IO_PPI_IO_WRITE64)	(
	IN CONST EFI_PEI_SERVICES			**PeiServices,
	IN CONST EFI_PEI_CPU_IO_PPI		*This,
	IN UINT64					Address,
	IN UINT64					Data
	);

typedef
UINT8
(EFIAPI	*EFI_PEI_CPU_IO_PPI_MEM_READ8) (
	IN CONST EFI_PEI_SERVICES			**PeiServices,
	IN CONST EFI_PEI_CPU_IO_PPI		*This,
	IN UINT64					Address
	);

typedef
UINT16
(EFIAPI	*EFI_PEI_CPU_IO_PPI_MEM_READ16)	(
	IN CONST EFI_PEI_SERVICES			**PeiServices,
	IN CONST EFI_PEI_CPU_IO_PPI		*This,
	IN UINT64					Address
	);

typedef
UINT32
(EFIAPI	*EFI_PEI_CPU_IO_PPI_MEM_READ32)	(
	IN CONST EFI_PEI_SERVICES			**PeiServices,
	IN CONST EFI_PEI_CPU_IO_PPI		*This,
	IN UINT64					Address
	);

typedef
UINT64
(EFIAPI	*EFI_PEI_CPU_IO_PPI_MEM_READ64)	(
	IN CONST EFI_PEI_SERVICES			**PeiServices,
	IN CONST EFI_PEI_CPU_IO_PPI		*This,
	IN UINT64					Address
	);

typedef
VOID
(EFIAPI	*EFI_PEI_CPU_IO_PPI_MEM_WRITE8)	(
	IN CONST EFI_PEI_SERVICES			**PeiServices,
	IN CONST EFI_PEI_CPU_IO_PPI		*This,
	IN UINT64					Address,
	IN UINT8					Data
	);

typedef
VOID
(EFIAPI	*EFI_PEI_CPU_IO_PPI_MEM_WRITE16) (
	IN CONST EFI_PEI_SERVICES			**PeiServices,
	IN CONST EFI_PEI_CPU_IO_PPI		*This,
	IN UINT64					Address,
	IN UINT16					Data
	);

typedef
VOID
(EFIAPI	*EFI_PEI_CPU_IO_PPI_MEM_WRITE32) (
	IN CONST EFI_PEI_SERVICES			**PeiServices,
	IN CONST EFI_PEI_CPU_IO_PPI		*This,
	IN UINT64					Address,
	IN UINT32					Data
	);

typedef
VOID
(EFIAPI	*EFI_PEI_CPU_IO_PPI_MEM_WRITE64) (
	IN CONST EFI_PEI_SERVICES			**PeiServices,
	IN CONST EFI_PEI_CPU_IO_PPI		*This,
	IN UINT64					Address,
	IN UINT64					Data
	);

typedef	struct _EFI_PEI_CPU_IO_PPI_ACCESS{
	EFI_PEI_CPU_IO_PPI_IO_MEM				Read;
	EFI_PEI_CPU_IO_PPI_IO_MEM				Write;
} EFI_PEI_CPU_IO_PPI_ACCESS;

// Interface definition
typedef struct _EFI_PEI_CPU_IO_PPI{
	EFI_PEI_CPU_IO_PPI_ACCESS			Mem;
	EFI_PEI_CPU_IO_PPI_ACCESS			Io;
	EFI_PEI_CPU_IO_PPI_IO_READ8			IoRead8;
	EFI_PEI_CPU_IO_PPI_IO_READ16		IoRead16;
	EFI_PEI_CPU_IO_PPI_IO_READ32		IoRead32;
	EFI_PEI_CPU_IO_PPI_IO_READ64		IoRead64;
	EFI_PEI_CPU_IO_PPI_IO_WRITE8		IoWrite8;
	EFI_PEI_CPU_IO_PPI_IO_WRITE16		IoWrite16;
	EFI_PEI_CPU_IO_PPI_IO_WRITE32		IoWrite32;
	EFI_PEI_CPU_IO_PPI_IO_WRITE64		IoWrite64;
	EFI_PEI_CPU_IO_PPI_MEM_READ8		MemRead8;
	EFI_PEI_CPU_IO_PPI_MEM_READ16		MemRead16;
	EFI_PEI_CPU_IO_PPI_MEM_READ32		MemRead32;
	EFI_PEI_CPU_IO_PPI_MEM_READ64		MemRead64;
	EFI_PEI_CPU_IO_PPI_MEM_WRITE8		MemWrite8;
	EFI_PEI_CPU_IO_PPI_MEM_WRITE16	MemWrite16;
	EFI_PEI_CPU_IO_PPI_MEM_WRITE32	MemWrite32;
	EFI_PEI_CPU_IO_PPI_MEM_WRITE64	MemWrite64;
} EFI_PEI_CPU_IO_PPI;

// PCI Cfg

// EFI_PEI_PCI_CFG_PPI_WIDTH
typedef	enum{
	EfiPeiPciCfgWidthUint8,
	EfiPeiPciCfgWidthUint16,
	EfiPeiPciCfgWidthUint32,
	EfiPeiPciCfgWidthUint64,
	EfiPeiPciCfgWidthMaximum
} EFI_PEI_PCI_CFG_PPI_WIDTH;

#define	PEI_PCI_CFG_ADDRESS(bus,dev,func,reg)	\
 ((UINT64) ( (((UINTN)bus) <<	24)	+	(((UINTN)dev)	<< 16) + (((UINTN)func)	<< 8)	+	((UINTN)reg) ))& 0x00000000ffffffff

#ifndef EFI_PEI_PCI_CFG_ADDRESS
#define EFI_PEI_PCI_CFG_ADDRESS(bus,dev,func,reg) \
 ((UINT64) ( (((UINTN)bus) <<	24)	+	(((UINTN)dev)	<< 16) + (((UINTN)func)	<< 8)	+	((UINTN)reg) ))& 0x00000000ffffffff
#endif

typedef	struct{
	UINT8	Register;
	UINT8	Function;
	UINT8	Device;
	UINT8	Bus;
#if PI_SPECIFICATION_VERSION>=0x00010000
    UINT32  ExtendedRegister;
#else
	UINT8	Reserved[4];
#endif
} PEI_PCI_CFG_PPI_PCI_ADDRESS;

#if PI_SPECIFICATION_VERSION<0x00010000
typedef	struct	_EFI_PEI_PCI_CFG_PPI		EFI_PEI_PCI_CFG_PPI;

typedef
EFI_STATUS
(EFIAPI	*EFI_PEI_PCI_CFG_PPI_IO) (
	IN EFI_PEI_SERVICES					**PeiServices,
	IN EFI_PEI_PCI_CFG_PPI				*This,
	IN EFI_PEI_PCI_CFG_PPI_WIDTH		Width,
	IN UINT64							Address,
	IN OUT VOID							*Buffer
	);

typedef
EFI_STATUS
(EFIAPI	*EFI_PEI_PCI_CFG_PPI_RW) (
	IN EFI_PEI_SERVICES					**PeiServices,
	IN EFI_PEI_PCI_CFG_PPI				*This,
	IN EFI_PEI_PCI_CFG_PPI_WIDTH		Width,
	IN UINT64							Address,
	IN UINTN							SetBits,
	IN UINTN							ClearBits
	);

typedef struct _EFI_PEI_PCI_CFG_PPI{
	EFI_PEI_PCI_CFG_PPI_IO			Read;
	EFI_PEI_PCI_CFG_PPI_IO			Write;
	EFI_PEI_PCI_CFG_PPI_RW			Modify;
} EFI_PEI_PCI_CFG_PPI;

//compatibility definition
//for PI 1.x Modules that do not use Modify funciton 
typedef EFI_PEI_PCI_CFG_PPI EFI_PEI_PCI_CFG2_PPI;
#else //#if PI_SPECIFICATION_VERSION<0x00010000
typedef	struct	_EFI_PEI_PCI_CFG2_PPI		EFI_PEI_PCI_CFG2_PPI;
typedef
EFI_STATUS
(EFIAPI	*EFI_PEI_PCI_CFG2_PPI_IO) (
	IN CONST EFI_PEI_SERVICES			**PeiServices,
	IN CONST EFI_PEI_PCI_CFG2_PPI		*This,
	IN EFI_PEI_PCI_CFG_PPI_WIDTH		Width,
	IN UINT64							Address,
	IN OUT VOID							*Buffer
	);

typedef
EFI_STATUS
(EFIAPI	*EFI_PEI_PCI_CFG2_PPI_RW) (
	IN CONST EFI_PEI_SERVICES			**PeiServices,
	IN CONST EFI_PEI_PCI_CFG2_PPI		*This,
	IN EFI_PEI_PCI_CFG_PPI_WIDTH		Width,
	IN UINT64							Address,
	IN VOID							    *SetBits,
	IN VOID							    *ClearBits
	);

typedef struct _EFI_PEI_PCI_CFG2_PPI{
	EFI_PEI_PCI_CFG2_PPI_IO			Read;
	EFI_PEI_PCI_CFG2_PPI_IO			Write;
	EFI_PEI_PCI_CFG2_PPI_RW			Modify;
    UINT16                          Segment;
} EFI_PEI_PCI_CFG2_PPI;

#if BACKWARD_COMPATIBLE_MODE
//compatibility definition
//for PI 0.91 Modules that do not use Modify funciton 
typedef EFI_PEI_PCI_CFG2_PPI EFI_PEI_PCI_CFG_PPI;
#endif

typedef struct {
    EFI_GUID                FileName;
    EFI_FV_FILETYPE         FileType;
    EFI_FV_FILE_ATTRIBUTES  FileAttributes;
    VOID                    *Buffer;
    UINT32                  BufferSize;
} EFI_FV_FILE_INFO;

typedef struct {
    EFI_FVB_ATTRIBUTES_2    FvAttributes;
    EFI_GUID                FvFormat;
    EFI_GUID                FvName;
    VOID                    *FvStart;
    UINT64                  FvSize;
} EFI_FV_INFO;

typedef
EFI_STATUS
(EFIAPI *EFI_PEI_FFS_FIND_BY_NAME) (
  IN CONST EFI_GUID             *FileName,
  IN EFI_PEI_FV_HANDLE          VolumeHandle,
  OUT EFI_PEI_FILE_HANDLE       *FileHandle
  );

typedef
EFI_STATUS
(EFIAPI *EFI_PEI_FFS_GET_FILE_INFO) (
  IN EFI_PEI_FILE_HANDLE        FileHandle,
  OUT EFI_FV_FILE_INFO          *FileInfo
  );

typedef
EFI_STATUS
(EFIAPI *EFI_PEI_FFS_GET_VOLUME_INFO) (
  IN EFI_PEI_FV_HANDLE          VolumeHandle,
  OUT EFI_FV_INFO               *VolumeInfo
  );

typedef
EFI_STATUS
(EFIAPI *EFI_PEI_REGISTER_FOR_SHADOW) (
  IN EFI_PEI_FILE_HANDLE        FileHandle
  );

#endif
//PEI Services
typedef struct _EFI_PEI_SERVICES {
	EFI_TABLE_HEADER                Hdr;
	// PPI Functions
	EFI_PEI_INSTALL_PPI             InstallPpi;
	EFI_PEI_REINSTALL_PPI           ReInstallPpi;
	EFI_PEI_LOCATE_PPI              LocatePpi;
	EFI_PEI_NOTIFY_PPI              NotifyPpi;
	// Boot Mode Functions
	EFI_PEI_GET_BOOT_MODE           GetBootMode;
	EFI_PEI_SET_BOOT_MODE           SetBootMode;
	// HOB Functions
    EFI_PEI_GET_HOB_LIST            GetHobList;
    EFI_PEI_CREATE_HOB              CreateHob;
	// Firmware Volume Functions
#if PI_SPECIFICATION_VERSION>=0x00010000
    EFI_PEI_FFS_FIND_NEXT_VOLUME2 FfsFindNextVolume;
    EFI_PEI_FFS_FIND_NEXT_FILE2 FfsFindNextFile;
    EFI_PEI_FFS_FIND_SECTION_DATA2 FfsFindSectionData;
#else
	EFI_PEI_FFS_FIND_NEXT_VOLUME    FfsFindNextVolume;
	EFI_PEI_FFS_FIND_NEXT_FILE      FfsFindNextFile;
	EFI_PEI_FFS_FIND_SECTION_DATA   FfsFindSectionData;
#endif
	// PEI Memory Functions
	EFI_PEI_INSTALL_PEI_MEMORY      InstallPeiMemory;
	EFI_PEI_ALLOCATE_PAGES          AllocatePages;
	EFI_PEI_ALLOCATE_POOL           AllocatePool;
	EFI_PEI_COPY_MEM                CopyMem;
	EFI_PEI_SET_MEM                 SetMem;
	// Status Code
	EFI_PEI_REPORT_STATUS_CODE      ReportStatusCode;
	// Reset
	EFI_PEI_RESET_SYSTEM            ResetSystem;
	// I/O Abstractions
	EFI_PEI_CPU_IO_PPI				*CpuIo;
    EFI_PEI_PCI_CFG2_PPI			*PciCfg;
#if PI_SPECIFICATION_VERSION>=0x00010000
    EFI_PEI_FFS_FIND_BY_NAME        FfsFindFileByName;
    EFI_PEI_FFS_GET_FILE_INFO       FfsGetFileInfo;
    EFI_PEI_FFS_GET_VOLUME_INFO     FfsGetVolumeInfo;
    EFI_PEI_REGISTER_FOR_SHADOW     RegisterForShadow;
#endif
} EFI_PEI_SERVICES;

typedef EFI_STATUS (EFIAPI *EFI_PEIM_ENTRY_POINT) (
	IN EFI_PEI_FILE_HANDLE FfsHeader,
	IN EFI_PEI_SERVICES **PeiServices
);

#define EFI_PEI_PERMANENT_MEMORY_INSTALLED_PPI \
{0xf894643d, 0xc449, 0x42d1, 0x8e, 0xa8, 0x85, 0xbd, 0xd8, 0xc6, 0x5b, 0xde}

#define EFI_PEI_MASTER_BOOT_MODE_PEIM_PPI \
{0x7408d748, 0xfc8c, 0x4ee6, 0x92, 0x88, 0xc4, 0xbe, 0xc0, 0x92, 0xa4, 0x10}

#define EFI_PEI_BOOT_IN_RECOVERY_MODE_PEIM_PPI \
{0x17ee496a, 0xd8e4, 0x4b9a, 0x94, 0xd1, 0xce, 0x82, 0x72, 0x30, 0x8, 0x50}

#define EFI_DXE_IPL_PPI_GUID \
{ 0xae8ce5d, 0xe448, 0x4437, 0xa8, 0xd7, 0xeb, 0xf5, 0xf1, 0x94, 0xf7, 0x31 }

#define EFI_PEI_END_OF_PEI_PHASE_PPI_GUID \
{ 0x605EA650, 0xC65C, 0x42e1, 0xBA, 0x80, 0x91, 0xA5, 0x2A, 0xB6,0x18, 0xC6 }

typedef struct _EFI_DXE_IPL_PPI EFI_DXE_IPL_PPI;
//TODO: Last parameter differs from PEICIS
typedef EFI_STATUS (EFIAPI *EFI_DXE_IPL_ENTRY) (
	IN EFI_DXE_IPL_PPI *This,
	IN EFI_PEI_SERVICES **PeiServices,
	IN VOID* HobList
);

//PPI Interface Structure
struct _EFI_DXE_IPL_PPI {
	EFI_DXE_IPL_ENTRY Entry;
};
/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif
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
