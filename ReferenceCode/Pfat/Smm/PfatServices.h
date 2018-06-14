/**
  This file contains an 'Intel Peripheral Driver' and uniquely        
  identified as "Intel Reference Module" and is
  licensed for Intel CPUs and chipsets under the terms of your   
  license agreement with Intel or your vendor.  This file may   
  be modified by the user, subject to additional terms of the
  license agreement
**/
/**

Copyright (c) 2011 - 2012 Intel Corporation. All rights reserved
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.

@file:

  PfatServices.h

@brief:

  Header file for the PCH PFAT Driver.

**/
#ifndef _PFAT_SERVICES_H_
#define _PFAT_SERVICES_H_

#include "PfatDefinitions.h"
#include "PchAccess.h"
#include "PchPlatformLib.h"
#include "AslUpdateLib.h"

///
/// Driver Dependency Protocols
///
#include EFI_PROTOCOL_PRODUCER   (Pfat)
#include EFI_PROTOCOL_DEPENDENCY (SmmBase)
#include EFI_PROTOCOL_DEPENDENCY (FirmwareVolume)
#include EFI_PROTOCOL_DEPENDENCY (SmmIoTrapDispatch)
#include EFI_GUID_DEFINITION     (SaDataHob)
#include EFI_PROTOCOL_DEPENDENCY (GlobalNvsArea)

UINT8                 mPfatUpdateData[PUP_BUFFER_SIZE];
static UINT16         mPfatUpdateCounter;
PUP                   *mPfatUpdatePackagePtr;
EFI_PHYSICAL_ADDRESS  mPupCertificate;
PFAT_LOG              *mPfatLogPtr;
PFAT_LOG              mPfatLogTemp;
EFI_PHYSICAL_ADDRESS  mPfatMemAddress;
UINT32                mPfatMemSize;
UINT64                mPfatFullStatus;

///
/// Private data structure definitions for the driver
///
#define PFAT_SIGNATURE  EFI_SIGNATURE_32 ('P', 'F', 'A', 'T')

#define PFAT_DIRECTORY_MAX_SIZE               6
#define PFAT_DIRECTORY_PFAT_MODULE_ENTRY      0x00
#define PFAT_DIRECTORY_PPDT_ENTRY             0x01
#define PFAT_DIRECTORY_PUP_ENTRY              0x02
#define PFAT_DIRECTORY_PUP_CERTIFICATE_ENTRY  0x03
#define PFAT_DIRECTORY_PFAT_LOG_ENTRY         0x04
#define PFAT_DIRECTORY_UNDEFINED_ENTRY        0xFE
#define PFAT_DIRECTORY_END_MARKER             0xFF

typedef enum {
  EnumPfatModule        = 0,
  EnumPpdt,
  EnumPup,
  EnumPupCertificate,
  EnumPfatLog,
  EnumPfatDirectoryEnd
} PFAT_DIRECTORY;

typedef struct {
  UINTN                 Signature;
  EFI_HANDLE            Handle;
  PFAT_PROTOCOL         PfatProtocol;
  EFI_PHYSICAL_ADDRESS  PfatDirectory[PFAT_DIRECTORY_MAX_SIZE];
  UINT32                AddrMask;
  UINT64                MsrValue;
} PFAT_INSTANCE;

#define PFAT_INSTANCE_FROM_PFATPROTOCOL(a)  CR (a, PFAT_INSTANCE, PfatProtocol, PFAT_SIGNATURE)

///
/// Stall period in microseconds
///
#define PFAT_WAIT_PERIOD          0
#define PFAT_AP_SAFE_RETRY_LIMIT  1

///
/// Function prototypes used by the PFAT protocol.
///
EFI_STATUS
PfatProtocolConstructor (
  PFAT_INSTANCE          *PfatInstance
  )
/**

@brief

  Initialize PFAT protocol instance.

  @param[in] PfatInstance              Pointer to PfatInstance to initialize

  @retval EFI_SUCCESS               The protocol instance was properly initialized

**/
;

VOID
EFIAPI
PfatModuleExecute (
  IN PFAT_INSTANCE          *PfatInstance
  )
/**

@brief
  
  Set MSR 0x115 with PFAT DIRECTORY Address.
  Trigger MSR 0x116 to invoke PFAT Binary.
  Read MSR 0x115 to get PFAT Binary Status.
  
  @param[in] PfatInstance              Pointer to PfatInstance to initialize


**/
;

EFI_STATUS
EFIAPI
PfatProtocolExecute (
  IN     PFAT_PROTOCOL  *This,
  IN     BOOLEAN        BiosUpdate
  )
/**

@brief
  
  Set PFAT DIRECTORY Address and triggers MSR to pass control to PFAT Binary module to execute command script.
  This function would be called by runtime driver, please do not use any MMIO macro here
  
  @param[in] This                   Pointer to the PFAT_PROTOCOL instance.
  @param[in] BiosUpdate             Flag to indicate flash update is requested by the Tool

  @retval EFI_SUCCESS               Command succeed.
  @retval EFI_INVALID_PARAMETER     The parameters specified are not valid.
  @retval EFI_UNSUPPORTED           The CPU or SPI memory is not supported.
  @retval EFI_DEVICE_ERROR          Device error, command aborts abnormally.

**/
;

VOID
EFIAPI
PfatProtocolWrite (
  IN     PFAT_PROTOCOL  *This,
  IN     UINTN          Address,
  IN     UINT32         DataByteCount,
  IN OUT UINT8          *Buffer
  )
/**

@brief
  
  Fill up Write script data into the PFAT Script buffer.
  This function would be called by runtime driver, please do not use any MMIO macro here
  
  @param[in] This                      Pointer to the PFAT_PROTOCOL instance.
  @param[in] Address                   This value specifies the offset from the start of the SPI Flash component where
                                       BIOS Image is located.
  @param[in] DataByteCount             Number of bytes in the data portion.
  @param[in] Buffer                    Pointer to caller-allocated buffer containing the data to be sent.


**/
;

VOID
EFIAPI
PfatProtocolBlockErase (
  IN     PFAT_PROTOCOL  *This,
  IN     UINTN          Address
  )
/**

@brief
  
  Fill up Erase script data into the PFAT Script buffer.
  This function would be called by runtime driver, please do not use any MMIO macro here
  
  @param[in] This                      Pointer to the PFAT_PROTOCOL instance.
  @param[in] Address                   This value specifies the offset from the start of the SPI Flash component where
                                       BIOS Image is located.
  @param[in] DataByteCount             Number of bytes in the data portion.


**/
;

#endif
