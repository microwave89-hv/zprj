//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/NVMe/NvmeBus.h 5     5/18/15 2:50a Karthikar $
//
// $Revision: 5 $
//
// $Date: 5/18/15 2:50a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/NVMe/NvmeBus.h $
// 
// 5     5/18/15 2:50a Karthikar
// [TAG]  		EIP216763
// [Category]  	Improvement
// [Description]  	Update the Aptio 4.x Nvme driver to Aptio 5.x Nvme
// driver Label 05
// [Files]  		[Files] Nvme.mak,NvmeBus.c, NvmeBus.h, NvmeController.c,
// NvmePassthru.c,NvmePassthru.h, NvmeSmm.c, NvmExpressPassThru.h.
// 
// 4     5/14/15 2:38a Karthikar
// 
// 3     9/23/14 2:29a Anandakrishnanl
// [TAG]  		EIP180861
// [Category]  	Improvement
// [Description]  	
// Add Legacy Boot support in Aptio 4.x Nvme driver - NON PI 1.2 Support
// [Files]  		NvmeBus.c
// NvmeBus.h
// NvmeSmm.c
// NvmeSmm.h
// NvmeSmm.dxs
// NvmeSmm.sdl
// 	
// 	
// 
// 
// 
// 
// 
// 2     9/04/14 7:35a Anandakrishnanl
// [TAG]  		EIP180861
// [Category]  	Improvement
// [Description]  	Legacy Boot support in Aptio 4.x Nvme driver
// [Files]  		
// Nvme.cif	
// Nvme.mak	
// Nvme.uni
// Nvme.chm	
// NvmeSetup.c
// NvmeBus.c
// NvmeComponentName.c
// NvmeIncludes.h
// NvmeBus.h
// [NvmeControllerLib]
// [NvmeSmm]
// [NVMEINT13]
// [NvmeProtocol]
// 
// 1     6/20/14 6:27a Anandakrishnanl
// [TAG]  		EIP172958
// [Category]  	New Feature
// [Description]  	Nvme Driver Intial Checkin
// [Files]  		Nvme.cif
// Nvme.sdl
// Nvme.mak
// Nvme.sd
// Nvme.uni
// Nvme.chm
// NvmeSetup.c
// NvmeBus.c
// NvmeController.c
// NvmeComponentName.c
// NvmeIncludes.h
// NvmeBus.h
// NvmeController.h
// 
//**********************************************************************
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:        NvmeBus.h
//
// Description: Header file for the Nvme Bus Driver
//
//<AMI_FHDR_END>
//**********************************************************************

#ifndef _NVME_BUS_H_
#define _NVME_BUS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "NvmeController.h"
#include "NvmeIncludes.h"
#include <Protocol/pDiskInfo.h>
#include <Protocol/AmiNvmeController.h>
#include <Protocol/AmiNvmePassThru.h>

#define ADMIN_QUEUE_SIZE          0x100
#define QUEUE1_SIZE               0x100

#define EFI_SIGNATURE_16( A, B )        ( (A) | (B << 8) )
#define EFI_SIGNATURE_32( A, B, C, D )  ( EFI_SIGNATURE_16( A, B ) | (EFI_SIGNATURE_16( C, D ) << 16))

#define ACTIVE_NAME_SPACE_SIG     EFI_SIGNATURE_32('N','V','M','E')
  
#define PCI_CLASS_MASS_STORAGE                            0x01
#define PCI_CLASS_MASS_STORAGE_SOLID_STATE                0x08
#define PCI_IF_MASS_STORAGE_SOLID_STATE                   0x00
#define PCI_IF_MASS_STORAGE_SOLID_STATE_NVMHCI            0x01
#define PCI_IF_MASS_STORAGE_SOLID_STATE_ENTERPRISE_NVMHCI 0x02

#define IS_CLASS1(_p, c)              ((_p)->Hdr.ClassCode[2] == (c))
#define IS_CLASS2(_p, c, s)           (IS_CLASS1 (_p, c) && ((_p)->Hdr.ClassCode[1] == (s)))
#define IS_CLASS3(_p, c, s, p)        (IS_CLASS2 (_p, c, s) && ((_p)->Hdr.ClassCode[0] == (p)))

#ifndef CR
#define CR(record, TYPE, field, signature) _CR(record, TYPE, field)
#endif

#ifndef _CR
#define _CR(Record, TYPE, Field)  ((TYPE *) ((CHAR8 *) (Record) - (CHAR8 *) &(((TYPE *) 0)->Field)))
#endif

#define SetDevicePathNodeLength(a,l) {                           \
          (a)->Length[0] = (UINT8) (l);                          \
          (a)->Length[1] = (UINT8) ((l) >> 8);                   \
          }

#define EFI_DISK_INFO_NVME_INTERFACE_GUID {  0x3ab14680, 0x5d3f, 0x4a4d, 0xbc, 0xdc, 0xcc, 0x38, 0x0, 0x18, 0xc7, 0xf7  }
#define NVME_SMM_GUID {0x1b30f467, 0xbf8b, 0x43b0, 0x81, 0x62, 0x29, 0xa, 0x27, 0xfd, 0x10, 0xcc}

typedef struct {
  CHAR8   *Language;
  CHAR16  *UnicodeString;
} EFI_UNICODE_STRING_TABLE;

typedef struct {
  UINT16  VendorId;
  UINT16  DeviceId;
  UINT16  Command;
  UINT16  Status;
  UINT8   RevisionID;
  UINT8   ClassCode[3];
  UINT8   CacheLineSize;
  UINT8   LatencyTimer;
  UINT8   HeaderType;
  UINT8   BIST;
} PCI_DEVICE_INDEPENDENT_REGION;

typedef struct {
  UINT32  Bar[6];
  UINT32  CISPtr;
  UINT16  SubsystemVendorID;
  UINT16  SubsystemID;
  UINT32  ExpansionRomBar;
  UINT8   CapabilityPtr;
  UINT8   Reserved1[3];
  UINT32  Reserved2;
  UINT8   InterruptLine;
  UINT8   InterruptPin;
  UINT8   MinGnt;
  UINT8   MaxLat;
} PCI_DEVICE_HEADER_TYPE_REGION;

typedef struct {
  PCI_DEVICE_INDEPENDENT_REGION Hdr;
  PCI_DEVICE_HEADER_TYPE_REGION Device;
} PCI_TYPE00;

typedef struct {
    EFI_DEVICE_PATH_PROTOCOL        Header;
    UINT32                          Nsid;
    UINT64                          EUI64;
} NVME_DEVICE_PATH;


typedef struct {
    UINT32                       Signature;
    EFI_HANDLE                   NvmeDeviceHandle;
    BOOLEAN                      Configured;                     // Updated after installing BLOCK_IO_PROTOCOL
    UINT32                       ActiveNameSpaceID;
  
    AMI_NVME_CONTROLLER_PROTOCOL *NvmeController;
    
    UINT64                       *PRP2List;                       // if the data transfer size is more than twice the max. page size 
    EFI_PHYSICAL_ADDRESS         PRP2ListMappedAddr;             
    VOID                         *PRP2ListUnMap;                  // if the data transfer size is more than twice the max. page size 
                                                                 // then PRP List is used.
    IDENTIFY_NAMESPACE_DATA      IdentifyNamespaceData;
    
    EFI_BLOCK_IO_PROTOCOL        NvmeBlockIO;
    EFI_DISK_INFO_PROTOCOL       NvmeDiskInfo;
    EFI_DEVICE_PATH_PROTOCOL     *EfiDevicePath;
    EFI_UNICODE_STRING_TABLE     *UDeviceName;
    UINT8                        Int13DeviceAddress;            // Used only for legacy Support
    UINT16                       wEmulationOption;              // For INT13 support
    UINT8                        bHiddenSectors;
    UINT8                        NumHeads;
    UINT8                        LBANumHeads;
    UINT16                       NumCylinders;
    UINT16                       LBANumCyls;
    UINT8                        NumSectors;
    UINT8                        LBANumSectors;
    UINT64                       dMaxLBA;
    UINT16                       wBlockSize;
    UINT8                        bStorageType;
    UINT8                        bEmuType;
    UINT8                        PNM[27];
    UINT8                        NvmeManufactureId[NVME_MANUFACTUREID_LENGTH];

    EFI_LIST_ENTRY                   Link;                           // Links to parent NVM Controller
    
} ACTIVE_NAMESPACE_DATA;

#define ACTIVE_NAMESPACE_DATA_FROM_THIS(a) \
  CR(a, ACTIVE_NAMESPACE_DATA, NvmeBlockIO, ACTIVE_NAME_SPACE_SIG)

#define ACTIVE_NAMESPACE_DATA_FROM_THIS_FOR_DISKINFO(a) \
  CR(a, ACTIVE_NAMESPACE_DATA, NvmeDiskInfo, ACTIVE_NAME_SPACE_SIG)

typedef	struct _NVME_MASS_DEV_INFO NVME_MASS_DEV_INFO;

EFI_STATUS 
NvmeBusSupported(
    IN EFI_DRIVER_BINDING_PROTOCOL    *This,
    IN EFI_HANDLE                     Controller,
    IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
);

EFI_STATUS 
NvmeBusStart (
    IN EFI_DRIVER_BINDING_PROTOCOL    *This,
    IN EFI_HANDLE                     Controller,
    IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath 
);

EFI_STATUS 
NvmeBusStop (
    IN EFI_DRIVER_BINDING_PROTOCOL    *This,
    IN EFI_HANDLE                     Controller,
    IN UINTN                          NumberOfChildren,
    IN EFI_HANDLE                     *ChildHandleBuffer
);

EFI_STATUS
InitializeNvmeController(
    IN  EFI_HANDLE                      Controller,
    IN  EFI_HANDLE                      DriverBindingHandle,
    OUT AMI_NVME_CONTROLLER_PROTOCOL    **NvmeController
);

EFI_STATUS
InstallBlockIoDiskInfo (
    IN EFI_DRIVER_BINDING_PROTOCOL     *This,
    IN AMI_NVME_CONTROLLER_PROTOCOL    *NvmeController
);

EFI_STATUS
CreateAdditionalSubmissionCompletionQueue ( 
    IN AMI_NVME_CONTROLLER_PROTOCOL    *NvmeController,
    IN NVME_COMMAND_WRAPPER            *NvmeCmdWrapper,
    IN UINT16                          QueueNumber,
    IN UINT32                          QueueSize
);

EFI_STATUS
ExecuteNvmeCmd (
    IN  AMI_NVME_CONTROLLER_PROTOCOL    *NvmeController, 
    IN  NVME_COMMAND_WRAPPER            *NvmeCmdWrapper,
    OUT COMPLETION_QUEUE_ENTRY          *CmdCompletionData
);

EFI_STATUS  
GetIdentifyData (
    IN  AMI_NVME_CONTROLLER_PROTOCOL    *NvmeController, 
    OUT UINT8                           *IdentifyData,
    IN  UINT8                           ControllerNameSpaceStructure, 
    IN  UINT32                          NameSpaceID
);

VOID
PrintNvmeCapability (
    AMI_NVME_CONTROLLER_PROTOCOL        *NvmeController
);


VOID
PrintNvmeMassDevInfo (
    NVME_MASS_DEV_INFO  *NvmeMassDevInfo
);

EFI_STATUS
AddToAdminSubmissionQueue (
    IN AMI_NVME_CONTROLLER_PROTOCOL    *NvmeController,
    IN NVME_COMMAND_WRAPPER            *NvmeCmdWrapper
);

EFI_STATUS
AddToQueue1SubmissionQueue (
    IN AMI_NVME_CONTROLLER_PROTOCOL    *NvmeController,
    IN NVME_COMMAND_WRAPPER            *NvmeCmdWrapper
);


EFI_STATUS
UpdateDoorBellRegister (
    IN AMI_NVME_CONTROLLER_PROTOCOL    *NvmeController,
    IN UINT16                          QueueNumber,
    IN UINT32                          Value
);

EFI_STATUS
WaitForCompletionQueueUpdate (
    IN  AMI_NVME_CONTROLLER_PROTOCOL    *NvmeController,
    IN  NVME_COMMAND_WRAPPER            *NvmeCmdWrapper,
    OUT COMPLETION_QUEUE_ENTRY          *CmdCompletionData 
);

EFI_STATUS
SetNumberOfQueues (
    IN AMI_NVME_CONTROLLER_PROTOCOL     *NvmeController
);

EFI_STATUS
EnumerateActiveNameSpace (
    IN OUT AMI_NVME_CONTROLLER_PROTOCOL    *NvmeController    
);

EFI_STATUS
DetectActiveNameSpace (
    IN  AMI_NVME_CONTROLLER_PROTOCOL   *NvmeController,
    OUT ACTIVE_NAMESPACE_DATA          *ActiveNameSpaceData
);


VOID
PrintIdentifyDataStructure (
    IN UINT8       *IdentifyData, 
    IN UINT8       ControllerNameSpaceStructure
);

VOID
PrintCommandCompletionData (
    IN COMPLETION_QUEUE_ENTRY   *pCmdCompletionData
);

VOID
PrintNvmeCmdWrapper(
    IN NVME_COMMAND_WRAPPER            *NvmeCmdWrapper
);

EFI_STATUS
ReadBlock (
    IN AMI_NVME_CONTROLLER_PROTOCOL  *NvmeController,
    IN ACTIVE_NAMESPACE_DATA         *ActiveNameSpace,
    OUT UINT8                           *Buffer
);

EFI_STATUS
CreateNvmeDevicePath (
    IN EFI_DRIVER_BINDING_PROTOCOL     *This, 
    IN ACTIVE_NAMESPACE_DATA           *ActiveNameSpaceData
);

EFI_STATUS
RecreateQueue1 (
    IN  AMI_NVME_CONTROLLER_PROTOCOL        *NvmeController
);

EFI_STATUS
RecreateAllQueues (
    IN  AMI_NVME_CONTROLLER_PROTOCOL        *NvmeController
);

EFI_STATUS
NvmeReadBlocks(
    IN EFI_BLOCK_IO_PROTOCOL        *This,
    IN UINT32                       MediaId,
    IN EFI_LBA                      LBA,
    IN UINTN                        BufferSize,
    OUT VOID                        *Buffer
);

EFI_STATUS
NvmeWriteBlocks(
    IN EFI_BLOCK_IO_PROTOCOL        *This,
    IN UINT32                       MediaId,
    IN EFI_LBA                      LBA,
    IN UINTN                        BufferSize,
    OUT VOID                        *Buffer
);

EFI_STATUS
NvmeReset (
    IN EFI_BLOCK_IO_PROTOCOL        *This,
    IN BOOLEAN                      ExtendedVerification
);

EFI_STATUS
NvmeFlushBlocks(
    IN EFI_BLOCK_IO_PROTOCOL        *This
);

EFI_STATUS
ProgramPRP2List (
    IN UINT64     *PRP2List, 
    IN UINT32      PageSize, 
    IN UINTN       BufferAddress,
    IN UINTN       BufferSize,
    IN UINTN      *PRP2TransferSize
);

EFI_STATUS
NvmeReadWriteBlocks(
    IN  ACTIVE_NAMESPACE_DATA       *ActiveNameSpace,
    IN UINT32                       MediaId,
    IN EFI_LBA                      LBA,
    IN UINTN                        BufferSize,
    OUT VOID                        *Buffer,
    OUT COMPLETION_QUEUE_ENTRY      *NvmeCompletionData,
    IN UINT8                        ReadWriteOpCode
);

EFI_STATUS
ExperimentWithAsyncEvents (
        AMI_NVME_CONTROLLER_PROTOCOL    *NvmeController        
);

VOID
InstallNvmeLegacyDevice (
    IN  AMI_NVME_CONTROLLER_PROTOCOL    *NvmeController,
    IN  ACTIVE_NAMESPACE_DATA           *ActiveNameSpace,
    IN  UINT8                           *Buffer
);

EFI_STATUS 
NvmeSetDefaultGeometry ( 
    IN  OUT ACTIVE_NAMESPACE_DATA       *ActiveNameSpace
);

VOID
NvmeMassUpdateCylinderInfo (
    IN  OUT ACTIVE_NAMESPACE_DATA       *ActiveNameSpace
);

EFI_STATUS
NvmeValidatePartitionTable (
    IN  UINT8   *Buffer,
    IN  UINT64  dMaxLBA,
    OUT UINT8   **ActPartAddr
);

EFI_STATUS
NvmeUpdateCHSFromBootRecord (
    IN  OUT ACTIVE_NAMESPACE_DATA   *ActiveNameSpace,
    IN  UINT8*                      BootRecord
);

EFI_STATUS
GetNvmeGeometryData (
    IN  OUT ACTIVE_NAMESPACE_DATA   *ActiveNameSpace,
    IN  OUT NVME_MASS_DEV_INFO      *NvmeMassDevInfo,
    IN  UINT8                       *Buffer
);

VOID
TransferNvmeDataToSmram (
    IN  AMI_NVME_CONTROLLER_PROTOCOL    *NvmeController
);

EFI_STATUS
NvmeDiskInfoWhichIde (
    IN EFI_DISK_INFO_PROTOCOL   *This,
    OUT UINT32                  *IdeChannel,
    OUT UINT32                  *IdeDevice
);

EFI_STATUS
NvmeDiskInfoSenseData (
    IN EFI_DISK_INFO_PROTOCOL   *This,
    OUT VOID                    *SenseData,
    OUT UINT32                  *SenseDataSize,
    OUT UINT8                   *SenseDataNumber
);

EFI_STATUS
NvmeDiskInfoIdentify (
    EFI_DISK_INFO_PROTOCOL      *This,
    IN OUT VOID                 *IdentifyData,
    IN OUT UINT32               *IdentifyDataSize
);

EFI_STATUS
NvmeDiskInfoInquiry (
    IN EFI_DISK_INFO_PROTOCOL   *This,
    IN OUT VOID                 *InquiryData,
    IN OUT UINT32               *InquiryDataSize
);


extern EFI_GUID gEfiSmmCommunicationProtocolGuid;
extern EFI_GUID gAmiSmmNvmeCommunicationGuid;

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif

#endif

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
