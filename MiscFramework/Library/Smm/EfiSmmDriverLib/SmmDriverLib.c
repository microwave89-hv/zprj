/*++
  This file contains 'Framework Code' and is licensed as such   
  under the terms of your license agreement with Intel or your  
  vendor.  This file may not be modified, except as allowed by  
  additional terms of your license agreement.                   
--*/
/*++

Copyright (c)  1999 - 2002 Intel Corporation. All rights reserved
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation. 


Module Name:

  MgmtModeRuntimeUtils.c

Abstract:

  Light weight lib to support EFI 2.0 SMM based drivers.

--*/

// GC_TODO: fix comment to set correct module name: SmmDriverLib.c
#include "Tiano.h"
#include "EfiCommonLib.h"
#include "EfiSmmDriverLib.h"
#include EFI_PROTOCOL_DEFINITION (LoadedImage)

EFI_DEVICE_PATH_PROTOCOL  *
EfiAppendDevicePath (
  IN EFI_DEVICE_PATH_PROTOCOL  *Src1,
  IN EFI_DEVICE_PATH_PROTOCOL  *Src2
  );

EFI_STATUS
EfiInitializeSmmDriverLib (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable,
  IN OUT BOOLEAN          *InSmm
  )
/*++

Routine Description:

  Intialize runtime Driver Lib if it has not yet been initialized. 

Arguments:

  (Standard EFI Image entry - EFI_IMAGE_ENTRY_POINT)

  GoVirtualChildEvent - Caller can register a virtual notification event.

Returns: 

  EFI_STATUS always returns EFI_SUCCESS

--*/
// GC_TODO:    ImageHandle - add argument and description to function comment
// GC_TODO:    SystemTable - add argument and description to function comment
// GC_TODO:    InSmm - add argument and description to function comment
{
  EFI_STATUS                Status;
  EFI_HANDLE                Handle;
  EFI_LOADED_IMAGE_PROTOCOL *LoadedImage;
  EFI_DEVICE_PATH_PROTOCOL  *CompleteFilePath;
  EFI_DEVICE_PATH_PROTOCOL  *ImageDevicePath;

  gSMM      = NULL;
  mSmmDebug = NULL;

  if ((SystemTable != NULL) && (SystemTable->BootServices != NULL)) {

    gST = SystemTable;
    gBS = SystemTable->BootServices;
    gRT = SystemTable->RuntimeServices;

    //
    // It is OK if the SmmStatusCode Protocol is not found, don't check the status.
    //
    Status  = gBS->LocateProtocol (&gEfiSmmStatusCodeProtocolGuid, NULL, &mSmmDebug);

    Status  = gBS->LocateProtocol (&gEfiSmmBaseProtocolGuid, NULL, &gSMM);
    if (EFI_ERROR (Status)) {
      return Status;
    }

    gSMM->InSmm (gSMM, InSmm);

    if (!(*InSmm)) {
      //
      // Not in SMM, initialization code is running under DXE environment
      //
      //
      // Load this driver's image to memory
      //
      if (ImageHandle != NULL) {
        Status = gBS->HandleProtocol (
                        ImageHandle,
                        &gEfiLoadedImageProtocolGuid,
                        (VOID *) &LoadedImage
                        );

        if (EFI_ERROR (Status)) {
          return Status;
        }

        gBS->HandleProtocol (
              LoadedImage->DeviceHandle,
              &gEfiDevicePathProtocolGuid,
              (VOID *) &ImageDevicePath
              );

        if (EFI_ERROR (Status)) {
          return Status;
        }

        CompleteFilePath = EfiAppendDevicePath (
                            ImageDevicePath,
                            LoadedImage->FilePath
                            );
        //
        // Load the image in memory to SMRAM; it will automatically generate the
        // SMI.
        //
        Status = gSMM->Register (gSMM, CompleteFilePath, NULL, 0, &Handle, FALSE);
        if (EFI_ERROR (Status)) {
          return Status;
        }
      }
    }
  }

  return EFI_SUCCESS;

}

UINTN
EfiDevicePathSize (
  IN EFI_DEVICE_PATH_PROTOCOL  *DevicePath
  )
/*++

Routine Description:

  GC_TODO: Add function description

Arguments:

  DevicePath  - GC_TODO: add argument description

Returns:

  GC_TODO: add return values

--*/
{
  EFI_DEVICE_PATH_PROTOCOL  *Start;

  if (NULL == DevicePath) {
    return 0;
  }
  //
  // Search for the end of the device path structure
  //
  Start = DevicePath;
  while (!EfiIsDevicePathEnd (DevicePath)) {
    DevicePath = EfiNextDevicePathNode (DevicePath);
  }
  //
  // Compute the size and add back in the size of the end device path structure
  //
  return ((UINTN) DevicePath - (UINTN) Start) + sizeof (EFI_DEVICE_PATH_PROTOCOL);
}

EFI_DEVICE_PATH_PROTOCOL *
EfiAppendDevicePath (
  IN EFI_DEVICE_PATH_PROTOCOL  *Src1,
  IN EFI_DEVICE_PATH_PROTOCOL  *Src2
  )
/*++

Routine Description:
  Function is used to append a Src1 and Src2 together.

Arguments:
  Src1  - A pointer to a device path data structure.

  Src2  - A pointer to a device path data structure.

Returns:

  A pointer to the new device path is returned.
  NULL is returned if space for the new device path could not be allocated from pool.
  It is up to the caller to free the memory used by Src1 and Src2 if they are no longer needed.

--*/
{
  EFI_STATUS                Status;
  UINTN                     Size;
  UINTN                     Size1;
  UINTN                     Size2;
  EFI_DEVICE_PATH_PROTOCOL  *NewDevicePath;
  EFI_DEVICE_PATH_PROTOCOL  *SecondDevicePath;

  //
  // Allocate space for the combined device path. It only has one end node of
  // length EFI_DEVICE_PATH_PROTOCOL
  //
  Size1 = EfiDevicePathSize (Src1);
  Size2 = EfiDevicePathSize (Src2);
  Size  = Size1 + Size2;

  if (Size1 != 0 && Size2 != 0) {
    Size -= sizeof (EFI_DEVICE_PATH_PROTOCOL);
  }

  Status = gBS->AllocatePool (EfiBootServicesData, Size, (VOID **) &NewDevicePath);

  if (EFI_ERROR (Status)) {
    return NULL;
  }

  gBS->CopyMem (NewDevicePath, Src1, Size1);

  //
  // Over write Src1 EndNode and do the copy
  //
  if (Size1 != 0) {
    SecondDevicePath = (EFI_DEVICE_PATH_PROTOCOL *) ((CHAR8 *) NewDevicePath + (Size1 - sizeof (EFI_DEVICE_PATH_PROTOCOL)));
  } else {
    SecondDevicePath = NewDevicePath;

  }

  gBS->CopyMem (SecondDevicePath, Src2, Size2);

  return NewDevicePath;
}
