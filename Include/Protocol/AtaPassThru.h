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

//*************************************************************************
// $Header: /Alaska/BIN/Core/Include/Protocol/AtaPassThru.h 1     6/13/11 6:35p Artems $
//
// $Revision: 1 $
//
// $Date: 6/13/11 6:35p $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/Protocol/AtaPassThru.h $
// 
// 1     6/13/11 6:35p Artems
// 
//*************************************************************************
//<AMI_FHDR_START>
//
//  Name: AtaPassThru.h
//
//  Description:
//  EFI_DRIVER_HEALTH_PROTOCOL definition file
//
//<AMI_FHDR_END>
//*************************************************************************
#ifndef __ATA_PASS_THRU_PROTOCOL__H__
#define __ATA_PASS_THRU_PROTOCOL__H__
#ifdef __cplusplus
extern "C" {
#endif

#include <EFI.h>
#include <Protocol/DevicePath.h>

#define EFI_ATA_PASS_THRU_PROTOCOL_GUID \
    { 0x1d3de7f0, 0x807, 0x424f, 0xaa, 0x69, 0x11, 0xa5, 0x4e, 0x19, 0xa4, 0x6f }

GUID_VARIABLE_DECLARATION(gEfiAtaPassThruProtocolGuid, EFI_ATA_PASS_THRU_PROTOCOL_GUID);

typedef struct _EFI_ATA_PASS_THRU_PROTOCOL EFI_ATA_PASS_THRU_PROTOCOL;

typedef struct {
    UINT32 Attributes;
    UINT32 IoAlign;
} EFI_ATA_PASS_THRU_MODE;

#define EFI_ATA_PASS_THRU_ATTRIBUTES_PHYSICAL   0x0001
#define EFI_ATA_PASS_THRU_ATTRIBUTES_LOGICAL    0x0002
#define EFI_ATA_PASS_THRU_ATTRIBUTES_NONBLOCKIO 0x0004

typedef struct _EFI_ATA_COMMAND_BLOCK {
    UINT8 Reserved1[2];
    UINT8 AtaCommand;
    UINT8 AtaFeatures;
    UINT8 AtaSectorNumber;
    UINT8 AtaCylinderLow;
    UINT8 AtaCylinderHigh;
    UINT8 AtaDeviceHead;
    UINT8 AtaSectorNumberExp;
    UINT8 AtaCylinderLowExp;
    UINT8 AtaCylinderHighExp;
    UINT8 AtaFeaturesExp;
    UINT8 AtaSectorCount;
    UINT8 AtaSectorCountExp;
    UINT8 Reserved2[6];
} EFI_ATA_COMMAND_BLOCK;

typedef struct _EFI_ATA_STATUS_BLOCK {
    UINT8 Reserved1[2];
    UINT8 AtaStatus;
    UINT8 AtaError;
    UINT8 AtaSectorNumber;
    UINT8 AtaCylinderLow;
    UINT8 AtaCylinderHigh;
    UINT8 AtaDeviceHead;
    UINT8 AtaSectorNumberExp;
    UINT8 AtaCylinderLowExp;
    UINT8 AtaCylinderHighExp;
    UINT8 Reserved2;
    UINT8 AtaSectorCount;
    UINT8 AtaSectorCountExp;
    UINT8 Reserved3[6];
} EFI_ATA_STATUS_BLOCK;

typedef UINT8 EFI_ATA_PASS_THRU_CMD_PROTOCOL;

#define EFI_ATA_PASS_THRU_PROTOCOL_ATA_HARDWARE_RESET 0x00
#define EFI_ATA_PASS_THRU_PROTOCOL_ATA_SOFTWARE_RESET 0x01
#define EFI_ATA_PASS_THRU_PROTOCOL_ATA_NON_DATA       0x02
#define EFI_ATA_PASS_THRU_PROTOCOL_PIO_DATA_IN        0x04
#define EFI_ATA_PASS_THRU_PROTOCOL_PIO_DATA_OUT       0x05
#define EFI_ATA_PASS_THRU_PROTOCOL_DMA                0x06
#define EFI_ATA_PASS_THRU_PROTOCOL_DMA_QUEUED         0x07
#define EFI_ATA_PASS_THRU_PROTOCOL_DEVICE_DIAGNOSTIC  0x08
#define EFI_ATA_PASS_THRU_PROTOCOL_DEVICE_RESET       0x09
#define EFI_ATA_PASS_THRU_PROTOCOL_UDMA_DATA_IN       0x0A
#define EFI_ATA_PASS_THRU_PROTOCOL_UDMA_DATA_OUT      0x0B
#define EFI_ATA_PASS_THRU_PROTOCOL_FPDMA              0x0C
#define EFI_ATA_PASS_THRU_PROTOCOL_RETURN_RESPONSE    0xFF

typedef UINT8 EFI_ATA_PASS_THRU_LENGTH;

#define EFI_ATA_PASS_THRU_LENGTH_BYTES            0x80
#define EFI_ATA_PASS_THRU_LENGTH_MASK             0x70
#define EFI_ATA_PASS_THRU_LENGTH_NO_DATA_TRANSFER 0x00
#define EFI_ATA_PASS_THRU_LENGTH_FEATURES         0x10
#define EFI_ATA_PASS_THRU_LENGTH_SECTOR_COUNT     0x20
#define EFI_ATA_PASS_THRU_LENGTH_TPSIU            0x30
#define EFI_ATA_PASS_THRU_LENGTH_COUNT            0x0F

typedef struct {
    EFI_ATA_STATUS_BLOCK           *Asb;
    EFI_ATA_COMMAND_BLOCK          *Acb;
    UINT64                         Timeout;
    VOID                           *InDataBuffer;
    VOID                           *OutDataBuffer;
    UINT32                         InTransferLength;
    UINT32                         OutTransferLength;
    EFI_ATA_PASS_THRU_CMD_PROTOCOL Protocol;
    EFI_ATA_PASS_THRU_LENGTH       Length;
} EFI_ATA_PASS_THRU_COMMAND_PACKET;

typedef EFI_STATUS (EFIAPI *EFI_ATA_PASS_THRU_PASSTHRU) (
    IN     EFI_ATA_PASS_THRU_PROTOCOL       *This,
    IN     UINT16                           Port,
    IN     UINT16                           PortMultiplierPort,
    IN OUT EFI_ATA_PASS_THRU_COMMAND_PACKET *Packet,
    IN     EFI_EVENT                        Event OPTIONAL
);

typedef EFI_STATUS (EFIAPI *EFI_ATA_PASS_THRU_GET_NEXT_PORT) (
    IN     EFI_ATA_PASS_THRU_PROTOCOL *This,
    IN OUT UINT16                     *Port
);

typedef EFI_STATUS (EFIAPI *EFI_ATA_PASS_THRU_GET_NEXT_DEVICE) (
    IN     EFI_ATA_PASS_THRU_PROTOCOL *This,
    IN     UINT16                     Port,
    IN OUT UINT16                     *PortMultiplierPort
);

typedef EFI_STATUS (EFIAPI *EFI_ATA_PASS_THRU_BUILD_DEVICE_PATH) (
    IN     EFI_ATA_PASS_THRU_PROTOCOL *This,
    IN     UINT16                     Port,
    IN     UINT16                     PortMultiplierPort,
    IN OUT EFI_DEVICE_PATH_PROTOCOL   **DevicePath
);

typedef EFI_STATUS (EFIAPI *EFI_ATA_PASS_THRU_GET_DEVICE) (
    IN  EFI_ATA_PASS_THRU_PROTOCOL *This,
    IN  EFI_DEVICE_PATH_PROTOCOL   *DevicePath,
    OUT UINT16                     *Port,
    OUT UINT16                     *PortMultiplierPort
);

typedef EFI_STATUS (EFIAPI *EFI_ATA_PASS_THRU_RESET_PORT) (
    IN EFI_ATA_PASS_THRU_PROTOCOL *This,
    IN UINT16                     Port
);

typedef EFI_STATUS (EFIAPI *EFI_ATA_PASS_THRU_RESET_DEVICE) (
    IN EFI_ATA_PASS_THRU_PROTOCOL *This,
    IN UINT16                     Port,
    IN UINT16                     PortMultiplierPort
);

struct _EFI_ATA_PASS_THRU_PROTOCOL {
    EFI_ATA_PASS_THRU_MODE              *Mode;
    EFI_ATA_PASS_THRU_PASSTHRU          PassThru;
    EFI_ATA_PASS_THRU_GET_NEXT_PORT     GetNextPort;
    EFI_ATA_PASS_THRU_GET_NEXT_DEVICE   GetNextDevice;
    EFI_ATA_PASS_THRU_BUILD_DEVICE_PATH BuildDevicePath;
    EFI_ATA_PASS_THRU_GET_DEVICE        GetDevice;
    EFI_ATA_PASS_THRU_RESET_PORT        ResetPort;
    EFI_ATA_PASS_THRU_RESET_DEVICE      ResetDevice;
};


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
