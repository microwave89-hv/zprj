/** @file
  Header file for the PCH EHCI PPI

@copyright
  Copyright (c) 2009 - 2012 Intel Corporation. All rights reserved
  This software and associated documentation (if any) is furnished
  under a license and may only be used or copied in accordance
  with the terms of the license. Except as permitted by such
  license, no part of this software or documentation may be
  reproduced, stored in a retrieval system, or transmitted in any
  form or by any means without the express written consent of
  Intel Corporation.

  This file contains an 'Intel Peripheral Driver' and uniquely
  identified as "Intel Reference Module" and is
  licensed for Intel CPUs and chipsets under the terms of your
  license agreement with Intel or your vendor.  This file may
  be modified by the user, subject to additional terms of the
  license agreement
**/
#ifndef _PEI_PCH_EHCI_H
#define _PEI_PCH_EHCI_H

//
// External include files do NOT need to be explicitly specified in real EDKII
// environment
//
#if !defined(EDK_RELEASE_VERSION) || (EDK_RELEASE_VERSION < 0x00020000)
#include "EdkIIGluePeim.h"

//
// Driver Produced PPI Prototypes
//
#include EFI_PPI_DEFINITION (UsbController)

//
// Driver Consumed PPI Prototypes
//
#include EFI_PPI_CONSUMER (PchUsbPolicy)
#include "PchAccess.h"
#include "PchUsb.h"
#endif

#define PCH_PCIE_EHCI1_BUS_DEV_FUNC MmPciAddress ( \
                                      0, \
                                      DEFAULT_PCI_BUS_NUMBER_PCH, \
                                      PCI_DEVICE_NUMBER_PCH_USB, \
                                      PCI_FUNCTION_NUMBER_PCH_EHCI, \
                                      0 \
                                      )

#define PCH_PCIE_EHCI2_BUS_DEV_FUNC MmPciAddress ( \
                                      0, \
                                      DEFAULT_PCI_BUS_NUMBER_PCH, \
                                      PCI_DEVICE_NUMBER_PCH_USB_EXT, \
                                      PCI_FUNCTION_NUMBER_PCH_EHCI2, \
                                      0 \
                                      )

#define PCH_H_PCIE_EHCI_ADDR(Controller) ( \
  (Controller == PchEhci1) ? PCH_PCIE_EHCI1_BUS_DEV_FUNC : \
  (Controller == PchEhci2) ? PCH_PCIE_EHCI2_BUS_DEV_FUNC : EFI_UNSUPPORTED \
  )

#define PCH_LP_PCIE_EHCI_ADDR(Controller) ( \
  (Controller == PchEhci1) ? PCH_PCIE_EHCI1_BUS_DEV_FUNC : EFI_UNSUPPORTED \
  )

#define PEI_PCH_EHCI_SIGNATURE  EFI_SIGNATURE_32 ('E', 'H', 'C', 'I')
#define EHCI_MEMORY_SPACE       0x400

typedef struct {
  UINTN                   Signature;
  PEI_USB_CONTROLLER_PPI  EhciControllerPpi;
  EFI_PEI_PPI_DESCRIPTOR  PpiList;
  UINTN                   TotalEhciControllers;
  UINTN                   MemBase[PchEhciControllerMax];
} PCH_EHCI_DEVICE;

#define PCH_EHCI_DEVICE_FROM_THIS(a)  PEI_CR (a, PCH_EHCI_DEVICE, EhciControllerPpi, PEI_PCH_EHCI_SIGNATURE)

#endif
