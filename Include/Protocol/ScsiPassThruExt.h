//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

//*************************************************************************
// $Header: /Alaska/BIN/Core/Include/Protocol/ScsiPassThruExt.h 1     8/16/12 5:00a Rajeshms $
//
// $Revision: 1 $
//
// $Date: 8/16/12 5:00a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/Protocol/ScsiPassThruExt.h $
// 
// 1     8/16/12 5:00a Rajeshms
// [TAG]  		EIP97048
// [Category]  	New Feature
// [Description]  	ATAPI PassThru Support using
// EFI_EXT_SCSI_PASS_THRU_PROTOCOL.
// [Files]  		AhciBus.c, AhciController.c, IdeBus.c, Atapi.c, PIDEBus.h,
// PAhciBus.h, ScsiPassThruAtapi.sdl, ScsiPassThruAtapi.mak,
// ScsiPassThruAtapi.c, ScsiPassThruAtapiSupport.h, ScsiPassThruAtapi.chm,
// ScsiPassThruExt.h
//
// 
//*************************************************************************
//<AMI_FHDR_START>
//
//  Name: ScsiPassThruExt.h
//
//  Description:
//  EFI_EXT_SCSI_PASS_THRU_PROTOCOL definition file.
//
//<AMI_FHDR_END>
//*************************************************************************

#ifndef __EXT_SCSI_PASS_THROUGH_PROTOCOL_H__
#define __EXT_SCSI_PASS_THROUGH_PROTOCOL_H__

#ifdef __cplusplus
extern "C" {
#endif

#define EFI_EXT_SCSI_PASS_THRU_PROTOCOL_GUID \
  { \
    0x143b7632, 0xb81b, 0x4cb7, {0xab, 0xd3, 0xb6, 0x25, 0xa5, 0xb9, 0xbf, 0xfe } \
  }

GUID_VARIABLE_DECLARATION(gEfiExtScsiPassThruProtocolGuid, EFI_EXT_SCSI_PASS_THRU_PROTOCOL_GUID);

typedef struct _EFI_EXT_SCSI_PASS_THRU_PROTOCOL EFI_EXT_SCSI_PASS_THRU_PROTOCOL;

#define TARGET_MAX_BYTES                             0x10

#define EFI_EXT_SCSI_PASS_THRU_ATTRIBUTES_PHYSICAL   0x0001
#define EFI_EXT_SCSI_PASS_THRU_ATTRIBUTES_LOGICAL    0x0002
#define EFI_EXT_SCSI_PASS_THRU_ATTRIBUTES_NONBLOCKIO 0x0004

//
// DataDirection
//
#define EFI_EXT_SCSI_DATA_DIRECTION_READ             0
#define EFI_EXT_SCSI_DATA_DIRECTION_WRITE            1
#define EFI_EXT_SCSI_DATA_DIRECTION_BIDIRECTIONAL    2
//
// HostAdapterStatus
//
#define EFI_EXT_SCSI_STATUS_HOST_ADAPTER_OK                    0x00
#define EFI_EXT_SCSI_STATUS_HOST_ADAPTER_TIMEOUT_COMMAND       0x09
#define EFI_EXT_SCSI_STATUS_HOST_ADAPTER_TIMEOUT               0x0b
#define EFI_EXT_SCSI_STATUS_HOST_ADAPTER_MESSAGE_REJECT        0x0d
#define EFI_EXT_SCSI_STATUS_HOST_ADAPTER_BUS_RESET             0x0e
#define EFI_EXT_SCSI_STATUS_HOST_ADAPTER_PARITY_ERROR          0x0f
#define EFI_EXT_SCSI_STATUS_HOST_ADAPTER_REQUEST_SENSE_FAILED  0x10
#define EFI_EXT_SCSI_STATUS_HOST_ADAPTER_SELECTION_TIMEOUT     0x11
#define EFI_EXT_SCSI_STATUS_HOST_ADAPTER_DATA_OVERRUN_UNDERRUN 0x12
#define EFI_EXT_SCSI_STATUS_HOST_ADAPTER_BUS_FREE              0x13
#define EFI_EXT_SCSI_STATUS_HOST_ADAPTER_PHASE_ERROR           0x14
#define EFI_EXT_SCSI_STATUS_HOST_ADAPTER_OTHER                 0x7f
//
// TargetStatus
//
#define EFI_EXT_SCSI_STATUS_TARGET_GOOD                        0x00
#define EFI_EXT_SCSI_STATUS_TARGET_CHECK_CONDITION             0x02
#define EFI_EXT_SCSI_STATUS_TARGET_CONDITION_MET               0x04
#define EFI_EXT_SCSI_STATUS_TARGET_BUSY                        0x08
#define EFI_EXT_SCSI_STATUS_TARGET_INTERMEDIATE                0x10
#define EFI_EXT_SCSI_STATUS_TARGET_INTERMEDIATE_CONDITION_MET  0x14
#define EFI_EXT_SCSI_STATUS_TARGET_RESERVATION_CONFLICT        0x18
#define EFI_EXT_SCSI_STATUS_TARGET_TASK_SET_FULL               0x28
#define EFI_EXT_SCSI_STATUS_TARGET_ACA_ACTIVE                  0x30
#define EFI_EXT_SCSI_STATUS_TARGET_TASK_ABORTED                0x40

typedef struct {
    UINT32 AdapterId;
    UINT32 Attributes;
    UINT32 IoAlign;
} EFI_EXT_SCSI_PASS_THRU_MODE;

typedef struct {
    UINT64 Timeout;
    VOID   *InDataBuffer;
    VOID   *OutDataBuffer;
    VOID   *SenseData;
    VOID   *Cdb;
    UINT32 InTransferLength;
    UINT32 OutTransferLength;
    UINT8  CdbLength;
    UINT8  DataDirection;
    UINT8  HostAdapterStatus;
    UINT8  TargetStatus;
    UINT8  SenseDataLength;
} EFI_EXT_SCSI_PASS_THRU_SCSI_REQUEST_PACKET;

typedef
EFI_STATUS
(EFIAPI *EFI_EXT_SCSI_PASS_THRU_PASSTHRU) (
    IN EFI_EXT_SCSI_PASS_THRU_PROTOCOL                *This,
    IN UINT8                                          *Target,
    IN UINT64                                         Lun,
    IN OUT EFI_EXT_SCSI_PASS_THRU_SCSI_REQUEST_PACKET *Packet,
    IN EFI_EVENT                                      Event     OPTIONAL
);      

typedef
EFI_STATUS
(EFIAPI *EFI_EXT_SCSI_PASS_THRU_GET_NEXT_TARGET_LUN) (
    IN EFI_EXT_SCSI_PASS_THRU_PROTOCOL                *This,
    IN OUT UINT8                                      **Target,
    IN OUT UINT64                                     *Lun
);  

typedef
EFI_STATUS
(EFIAPI *EFI_EXT_SCSI_PASS_THRU_BUILD_DEVICE_PATH) (
    IN EFI_EXT_SCSI_PASS_THRU_PROTOCOL               *This,
    IN UINT8                                         *Target,
    IN UINT64                                        Lun,
    IN OUT EFI_DEVICE_PATH_PROTOCOL                  **DevicePath
);

typedef
EFI_STATUS
(EFIAPI *EFI_EXT_SCSI_PASS_THRU_GET_TARGET_LUN) (
    IN EFI_EXT_SCSI_PASS_THRU_PROTOCOL               *This,
    IN EFI_DEVICE_PATH_PROTOCOL                      *DevicePath,
    OUT UINT8                                        **Target,
    OUT UINT64                                       *Lun
);    

typedef
EFI_STATUS
(EFIAPI *EFI_EXT_SCSI_PASS_THRU_RESET_CHANNEL) (
    IN EFI_EXT_SCSI_PASS_THRU_PROTOCOL               *This
);
  
typedef
EFI_STATUS
(EFIAPI *EFI_EXT_SCSI_PASS_THRU_RESET_TARGET_LUN) (
    IN EFI_EXT_SCSI_PASS_THRU_PROTOCOL               *This,
    IN UINT8                                         *Target,
    IN UINT64                                        Lun
);

typedef
EFI_STATUS
(EFIAPI *EFI_EXT_SCSI_PASS_THRU_GET_NEXT_TARGET) (
    IN EFI_EXT_SCSI_PASS_THRU_PROTOCOL               *This,
    IN OUT UINT8                                     **Target
);
  
struct _EFI_EXT_SCSI_PASS_THRU_PROTOCOL {
  EFI_EXT_SCSI_PASS_THRU_MODE                *Mode;
  EFI_EXT_SCSI_PASS_THRU_PASSTHRU            PassThru;
  EFI_EXT_SCSI_PASS_THRU_GET_NEXT_TARGET_LUN GetNextTargetLun;
  EFI_EXT_SCSI_PASS_THRU_BUILD_DEVICE_PATH   BuildDevicePath;
  EFI_EXT_SCSI_PASS_THRU_GET_TARGET_LUN      GetTargetLun;
  EFI_EXT_SCSI_PASS_THRU_RESET_CHANNEL       ResetChannel;
  EFI_EXT_SCSI_PASS_THRU_RESET_TARGET_LUN    ResetTargetLun;
  EFI_EXT_SCSI_PASS_THRU_GET_NEXT_TARGET     GetNextTarget;
};

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
