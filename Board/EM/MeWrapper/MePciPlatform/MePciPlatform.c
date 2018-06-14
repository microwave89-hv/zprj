//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.            **
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
//
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/MeWrapper/MePciPlatform/MePciPlatform.c 1     2/08/12 1:05a Klzhan $
//
// $Revision: 1 $
//
// $Date: 2/08/12 1:05a $
//
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/MeWrapper/MePciPlatform/MePciPlatform.c $
// 
// 1     2/08/12 1:05a Klzhan
// Initial Check in 
// 
// 1     2/25/11 1:41a Klzhan
// Initial Check-in
// 
// 1     12/03/10 5:09a Klzhan
// Initial Check-in.
// 
//
//**********************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:            MePciPlatform.c
//
// Description:
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>
/*++

This file contains a 'Sample Driver' and is licensed as such
under the terms of your license agreement with Intel or your
vendor.  This file may be modified by the user, subject to  
the additional terms of the license agreement               

--*/

/*++
Copyright (c)  2008 Intel Corporation. All rights reserved
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.
  
Module Name:

 MePciPlatform.c

Abstract:

  
--*/
#include "MePciPlatform.h"

#define SETUP_GUID \
  {0xEC87D643, 0xEBA4, 0x4BB5, 0xA1, 0xE5, 0x3F, 0x3E, 0x36, 0xB2, 0x0D, 0xA9}
EFI_GUID gSetupGuid                     = SETUP_GUID;
//-jeff PLATFORM_INFO_PROTOCOL                  *gPlatformInfoProtocol;

EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL   *PciRootBridgeIo;
EFI_PCI_PLATFORM_PROTOCOL         *MePciPlatformInstance;
PLATFORM_PCI_EXPRESS_BRIDGE       *mPlatformPciExpressBridge;

EFI_STATUS
EFIAPI
PhaseNotify (
  IN EFI_PCI_PLATFORM_PROTOCOL                       *This,
  IN  EFI_HANDLE                                     HostBridge,
  IN  EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PHASE  Phase,
  IN  EFI_PCI_CHIPSET_EXECUTION_PHASE                ChipsetPhase  
  )
/*++

  Routine Description:
    The PlatformNotify() function can be used to notify the platform driver so that 
    it can perform platform-specific actions. No specific actions are required. 
    Eight notification points are defined at this time. More synchronization points 
    may be added as required in the future. The PCI bus driver calls the platform driver 
    twice for every Phase-once before the PCI Host Bridge Resource Allocation Protocol 
    driver is notified, and once after the PCI Host Bridge Resource Allocation Protocol 
    driver has been notified. 
    This member function may not perform any error checking on the input parameters. It 
    also does not return any error codes. If this member function detects any error condition, 
    it needs to handle those errors on its own because there is no way to surface any 
    errors to the caller.
    
  Arguments:
    This         - Pointer to the EFI_PCI_PLATFORM_PROTOCOL instance.  
    HostBridge   - The handle of the host bridge controller. 
    Phase        - The phase of the PCI bus enumeration.
    ChipsetPhase - Defines the execution phase of the PCI chipset driver. 
    
  Returns:
    EFI_SUCCESS  - The function completed successfully.
    
--*/
{
/*
  EFI_STATUS                        Status;

  if (Phase == EfiPciHostBridgeEndBusAllocation && ChipsetPhase == ChipsetEntry) {
      Status = HeciSetClockEnables (CurrentClockMask, CurrentClockEnables, TRUE);
  }
*/
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
PlatformPrepController (
  IN  EFI_PCI_PLATFORM_PROTOCOL                      *This,
  IN  EFI_HANDLE                                     HostBridge,
  IN  EFI_HANDLE                                     RootBridge,
  IN  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_PCI_ADDRESS    PciAddress,
  IN  EFI_PCI_CONTROLLER_RESOURCE_ALLOCATION_PHASE   Phase,
  IN  EFI_PCI_CHIPSET_EXECUTION_PHASE                ChipsetPhase
  )
/*++

  Routine Description:
    The PlatformPrepController() function can be used to notify the platform driver so that 
    it can perform platform-specific actions. No specific actions are required. 
    Several notification points are defined at this time. More synchronization points may be 
    added as required in the future. The PCI bus driver calls the platform driver twice for 
    every PCI controller-once before the PCI Host Bridge Resource Allocation Protocol driver 
    is notified, and once after the PCI Host Bridge Resource Allocation Protocol driver has 
    been notified. 
    This member function may not perform any error checking on the input parameters. It also 
    does not return any error codes. If this member function detects any error condition, it 
    needs to handle those errors on its own because there is no way to surface any errors to 
    the caller.  
    
  Arguments:
    This         - Pointer to the EFI_PCI_PLATFORM_PROTOCOL instance.  
    HostBridge   - The associated PCI host bridge handle. 
    RootBridge   - The associated PCI root bridge handle.
    PciAddress   - The address of the PCI device on the PCI bus. 
    Phase        - The phase of the PCI controller enumeration. 
    ChipsetPhase - Defines the execution phase of the PCI chipset driver. 
    
  Returns:
    EFI_SUCCESS  - The function completed successfully.
    
--*/
{
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
GetPlatformPolicy (
  IN  EFI_PCI_PLATFORM_PROTOCOL           *This,
  OUT EFI_PCI_PLATFORM_POLICY             *PciPolicy
  )
/*++

  Routine Description:
    The GetPlatformPolicy() function retrieves the platform policy regarding PCI 
    enumeration. The PCI bus driver and the PCI Host Bridge Resource Allocation Protocol 
    driver can call this member function to retrieve the policy.
    
  Arguments:
    This      - Pointer to the EFI_PCI_PLATFORM_PROTOCOL instance.
    PciPolicy - The platform policy with respect to VGA and ISA aliasing. 
    
  Returns:
    EFI_SUCCESS           - The function completed successfully.
    EFI_INVALID_PARAMETER - PciPolicy is NULL.
    
--*/
{
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
GetPciRom (
  IN   EFI_PCI_PLATFORM_PROTOCOL    *This,
  IN   EFI_HANDLE                   PciHandle,
  OUT  VOID                         **RomImage,
  OUT  UINTN                        *RomSize 
  )
/*++

  Routine Description:
    The GetPciRom() function gets the PCI device's option ROM from a platform-specific location. 
    The option ROM will be loaded into memory. This member function is used to return an image 
    that is packaged as a PCI 2.2 option ROM. The image may contain both legacy and EFI option 
    ROMs. See the EFI 1.10 Specification for details. This member function can be used to return 
    option ROM images for embedded controllers. Option ROMs for embedded controllers are typically 
    stored in platform-specific storage, and this member function can retrieve it from that storage 
    and return it to the PCI bus driver. The PCI bus driver will call this member function before 
    scanning the ROM that is attached to any controller, which allows a platform to specify a ROM 
    image that is different from the ROM image on a PCI card.

  Arguments:
    This      - Pointer to the EFI_PCI_PLATFORM_PROTOCOL instance.
    PciHandle - The handle of the PCI device. 
    RomImage  - If the call succeeds, the pointer to the pointer to the option ROM image. 
                Otherwise, this field is undefined. The memory for RomImage is allocated 
                by EFI_PCI_PLATFORM_PROTOCOL.GetPciRom() using the EFI Boot Service AllocatePool(). 
                It is the caller's responsibility to free the memory using the EFI Boot Service 
                FreePool(), when the caller is done with the option ROM.
    RomSize   - If the call succeeds, a pointer to the size of the option ROM size. Otherwise, 
                this field is undefined.
                
  Returns:
    EFI_SUCCESS          - The option ROM was available for this device and loaded into memory.
    EFI_NOT_FOUND        - No option ROM was available for this device.
    EFI_OUT_OF_RESOURCES - No memory was available to load the option ROM.
    EFI_DEVICE_ERROR     - An error occurred in getting the option ROM.
        
--*/
{
  return EFI_NOT_FOUND;
}

//
// Driver entry point
//
EFI_DRIVER_ENTRY_POINT (MePlatformPolicyEntryPoint)

//
// Function implementations
//
EFI_STATUS
EFIAPI
MePciPlatformEntryPoint (
    IN EFI_HANDLE               ImageHandle,
    IN EFI_SYSTEM_TABLE         *SystemTable
)
/*++
 
Routine Description:
 
  Entry point for the Management Engine Driver.
  
Arguments:
 
  ImageHandle       Image handle of this driver.
  SystemTable       Global system service table.
 
Returns:
 
  EFI_SUCCESS           Initialization complete.
  EFI_UNSUPPORTED       The chipset is unsupported by this driver.
  EFI_OUT_OF_RESOURCES  Do not have enough resources to initialize the driver.
  EFI_DEVICE_ERROR      Device error, driver exits abnormally.
 
--*/
{
  EFI_STATUS            Status;
  EFI_HECI_PROTOCOL     *Heci;
  UINT32                MeMode;


  EfiInitializeDriverLib (ImageHandle, SystemTable);

  //
  // Locate Heci protocol
  //
  Status = gBS->LocateProtocol (&gEfiHeciProtocolGuid, NULL, &Heci);
  if (EFI_ERROR(Status)) {
    DEBUG ((EFI_D_ERROR, "MePciPlatform locate Heci failed and the Status is %r\n", Status));
    return Status;
  }

  Status = Heci->GetMeMode(&MeMode);
  if (EFI_ERROR(Status)) {
    DEBUG ((EFI_D_ERROR, "MePciPlatform Get Me mode failed and the Status is %r\n", Status));
    return Status;
  }
  if (MeMode == ME_MODE_SECOVER) {
    DEBUG ((EFI_D_ERROR, "SetICC doesn't supported in this mode\n"));
    return EFI_UNSUPPORTED;
  }

  MePciPlatformInstance = (EFI_PCI_PLATFORM_PROTOCOL *) (UINTN) AllocatePool (sizeof (EFI_PCI_PLATFORM_PROTOCOL));

 //-jeff Status = gBS->LocateProtocol(&gPlatformInfoProtocolGuid, NULL, &gPlatformInfoProtocol);
 //-jeff  ASSERT_EFI_ERROR (Status);

  // Locate root bridge IO protocol
  //
  Status = gBS->LocateProtocol (&gEfiPciRootBridgeIoProtocolGuid, NULL, &PciRootBridgeIo);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  MePciPlatformInstance->PhaseNotify            = PhaseNotify;
  MePciPlatformInstance->PlatformPrepController = PlatformPrepController;
  MePciPlatformInstance->GetPlatformPolicy      = GetPlatformPolicy;
  MePciPlatformInstance->GetPciRom              = GetPciRom;

  //
  // Install the EFI_MANAGEMENT_ENGINE_PROTOCOL interface
  //
  Status = gBS->InstallProtocolInterface (
               &ImageHandle,
               &gEfiPciPlatformProtocolGuid,
               EFI_NATIVE_INTERFACE,
               MePciPlatformInstance
           );

  return Status;
}

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************