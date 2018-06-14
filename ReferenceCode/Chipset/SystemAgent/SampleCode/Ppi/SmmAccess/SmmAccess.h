/** @file
  This code abstracts the PEI core to provide SmmAccess services.

@copyright
  Copyright (c) 1999 - 2012 Intel Corporation. All rights reserved
  This software and associated documentation (if any) is furnished
  under a license and may only be used or copied in accordance
  with the terms of the license. Except as permitted by such
  license, no part of this software or documentation may be
  reproduced, stored in a retrieval system, or transmitted in any
  form or by any means without the express written consent of
  Intel Corporation.

  This file contains 'Framework Code' and is licensed as such
  under the terms of your license agreement with Intel or your
  vendor.  This file may not be modified, except as allowed by
  additional terms of your license agreement.
**/
#ifndef _PEI_SMM_ACCESS_PPI_H_
#define _PEI_SMM_ACCESS_PPI_H_

#include EFI_GUID_DEFINITION (SmramMemoryReserve)

#define PEI_SMM_ACCESS_PPI_GUID \
  { \
    0x268f33a9, 0xcccd, 0x48be, 0x88, 0x17, 0x86, 0x5, 0x3a, 0xc3, 0x2e, 0xd6 \
  }

EFI_FORWARD_DECLARATION (PEI_SMM_ACCESS_PPI);

typedef
EFI_STATUS
(EFIAPI *PEI_SMM_OPEN) (
  IN EFI_PEI_SERVICES                **PeiServices,
  IN PEI_SMM_ACCESS_PPI              * This,
  IN UINTN                           DescriptorIndex
  )
/**
  This routine accepts a request to "open" a region of SMRAM.  The
  region could be legacy ABSEG, HSEG, or TSEG near top of physical memory.
  The use of "open" means that the memory is visible from all PEIM
  and SMM agents.

  @param[in] This                  - Pointer to the SMM Access Interface.
  @param[in] DescriptorIndex       - Region of SMRAM to Open.

  @retval EFI_SUCCESS           - The region was successfully opened.
  @retval EFI_DEVICE_ERROR      - The region could not be opened because locked by
                          chipset.
  @retval EFI_INVALID_PARAMETER - The descriptor index was out of bounds.
**/
;

typedef
EFI_STATUS
(EFIAPI *PEI_SMM_CLOSE) (
  IN EFI_PEI_SERVICES                **PeiServices,
  IN PEI_SMM_ACCESS_PPI              * This,
  IN UINTN                           DescriptorIndex
  )
/**
  This routine accepts a request to "close" a region of SMRAM.  The
  region could be legacy AB or TSEG near top of physical memory.
  The use of "close" means that the memory is only visible from SMM agents,
  not from PEIM.

  @param[in] This                  - Pointer to the SMM Access Interface.
  @param[in] DescriptorIndex       - Region of SMRAM to Close.

  @retval EFI_SUCCESS           - The region was successfully closed.
  @retval EFI_DEVICE_ERROR      - The region could not be closed because locked by
                            chipset.
  @retval EFI_INVALID_PARAMETER - The descriptor index was out of bounds.
**/
;

typedef
EFI_STATUS
(EFIAPI *PEI_SMM_LOCK) (
  IN EFI_PEI_SERVICES                **PeiServices,
  IN PEI_SMM_ACCESS_PPI              * This,
  IN UINTN                           DescriptorIndex
  )
/**
  This routine accepts a request to "lock" SMRAM.  The
  region could be legacy AB or TSEG near top of physical memory.
  The use of "lock" means that the memory can no longer be opened
  to PEIM.

  @param[in] This                  - Pointer to the SMM Access Interface.
  @param[in] DescriptorIndex       - Region of SMRAM to Lock.

  @retval EFI_SUCCESS           - The region was successfully locked.
  @retval EFI_DEVICE_ERROR      - The region could not be locked because at least
                          one range is still open.
  @retval EFI_INVALID_PARAMETER - The descriptor index was out of bounds.
**/
;

typedef
EFI_STATUS
(EFIAPI *PEI_SMM_CAPABILITIES) (
  IN EFI_PEI_SERVICES                **PeiServices,
  IN PEI_SMM_ACCESS_PPI              * This,
  IN OUT UINTN                       *SmramMapSize,
  IN OUT EFI_SMRAM_DESCRIPTOR        * SmramMap
  )
/**
  This routine services a user request to discover the SMRAM
  capabilities of this platform.  This will report the possible
  ranges that are possible for SMRAM access, based upon the
  memory controller capabilities.

  @param[in] This                  - Pointer to the SMRAM Access Interface.
  @param[in] SmramMapSize          - Pointer to the variable containing size of the
                            buffer to contain the description information.
  @param[in] SmramMap              - Buffer containing the data describing the Smram
                            region descriptors.

  @retval EFI_BUFFER_TOO_SMALL  - The user did not provide a sufficient buffer.
  @retval EFI_SUCCESS           - The user provided a sufficiently-sized buffer.
**/
;

struct _PEI_SMM_ACCESS_PPI {
  PEI_SMM_OPEN          Open;
  PEI_SMM_CLOSE         Close;
  PEI_SMM_LOCK          Lock;
  PEI_SMM_CAPABILITIES  GetCapabilities;
  BOOLEAN               LockState;
  BOOLEAN               OpenState;
};

extern EFI_GUID gPeiSmmAccessPpiGuid;

#endif
