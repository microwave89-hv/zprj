/** @file
  Implementation file for GfxDisplay Dxe functionality

@copyright
  Copyright (c) 2012 Intel Corporation. All rights reserved
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

//
// External include files do NOT need to be explicitly specified in real EDKII
// environment
//
//
// External include files do NOT need to be explicitly specified in real EDKII
// environment
//
#if !defined(EDK_RELEASE_VERSION) || (EDK_RELEASE_VERSION < 0x00020000)
#include "EdkIIGlueDxe.h"
#include "RapidStartData.h"
#include EFI_PROTOCOL_PRODUCER (DxeGfxProtocol)
#include EFI_PROTOCOL_DEPENDENCY (RapidStartGlobalNvsArea)
#include EFI_PROTOCOL_CONSUMER (RapidStartPlatformPolicy)
#include EFI_PROTOCOL_DEPENDENCY (IgdOpRegion)

#define BDS_ALL_DRIVERS_CONNECTED_PROTOCOL_GUID \
  {0xdbc9fd21, 0xfad8, 0x45b0, 0x9e, 0x78, 0x27, 0x15, 0x88, 0x67, 0xcc, 0x93}

#define EFI_CONSOLE_CONTROL_PROTOCOL_GUID \
  {0xf42f7782, 0x12e, 0x4c12, 0x99, 0x56, 0x49, 0xf9, 0x43, 0x4, 0xf7, 0x21}

EFI_GUID   gEfiConsoleControlProtocolGuid = BDS_ALL_DRIVERS_CONNECTED_PROTOCOL_GUID;

#endif

//
// Internal function for GfxDisplayLib used only
//
/**
  Event callback to get screen shot for RapidStart exit

  @param[in] Event    - The event that triggered this notification function
  @param[in] Context  - Pointer to the notification functions context
**/
STATIC
VOID
RapidStartDisplayScreenCallback (
  IN EFI_EVENT Event,
  IN VOID      *Context
  )
{
  EFI_STATUS                           Status, IgdOpRegionStatus;
  VOID                                 *ProtocolPointer;
  DXE_GFX_PROTOCOL                     *DxeGfxProtocol;
  RAPID_START_PLATFORM_POLICY_PROTOCOL *RapidStartPolicy;
  RAPID_START_GLOBAL_NVS_AREA_PROTOCOL *RapidStartGlobalNvsAreaProtocol;
  RAPID_START_PERSISTENT_DATA          *RapidStartData;
  IGD_OPREGION_PROTOCOL                *IgdOpRegion;

  //
  // Check whether this is real protocal callback notification, or just a SignalEvent
  //
  Status = gBS->LocateProtocol (&gEfiConsoleControlProtocolGuid, NULL, &ProtocolPointer);
  if (EFI_ERROR (Status)) {
    return;
  }

  //
  // Locate RapidStart platform policy.
  //
  Status = gBS->LocateProtocol (&gRapidStartPlatformPolicyProtocolGuid, NULL, &RapidStartPolicy);
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "No RapidStart Platform Policy Protocol available\n"));
    return;
  }

  Status = gBS->LocateProtocol (&gRapidStartGlobalNvsAreaProtocolGuid, NULL, &RapidStartGlobalNvsAreaProtocol);
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_INFO, "No RapidStart info protocol available\n"));
    return;
  }

  RapidStartData = RapidStartGlobalNvsAreaProtocol->RapidStartData;

  IgdOpRegionStatus = gBS->LocateProtocol (&gIgdOpRegionProtocolGuid, NULL, &IgdOpRegion);
  if (!EFI_ERROR (IgdOpRegionStatus)) {
    IgdOpRegion->OpRegion->MBox3.FDSP = RapidStartData->DssAddress;
    IgdOpRegion->OpRegion->MBox3.FDSS = (UINT32)(RapidStartData->DssSize);
  }

  if (RapidStartPolicy->DisplaySaveRestore == 1) {
    Status = gBS->LocateProtocol (&gDxeGfxProtocolGuid, NULL, &DxeGfxProtocol);
    DEBUG ((EFI_D_INFO, "RapidStartDisplayScreenCallback():Locating DxeGfxProtocol - Status = %r\n", Status));
    if (!EFI_ERROR(Status)) {
      if (RapidStartPolicy->DisplayType == BIOS_RESTORE) {
        Status = DxeGfxProtocol->SaveDisplay(NULL);
      } else {
        Status = DxeGfxProtocol->SaveDisplay((UINT8*)(UINTN)((RapidStartData)->DssAddress));
      }
    }
  }

  gBS->CloseEvent (Event);
}

//
// Interface functions of GfxDisplayLib
//
/**
 Install EFI_CONSOLE_CONTROL_PROTOCOL_GUID callback handler.
**/
VOID
RegisterForRapidStartDisplayScreenCallback (
  VOID
  )
{
  EFI_EVENT               Event;

  //
  // Create an EFI_CONSOLE_CONTROL_PROTOCOL_GUID protocol call back event, to capture splash screen.
  //
  EfiCreateProtocolNotifyEvent (
    &gEfiConsoleControlProtocolGuid,
    EFI_TPL_CALLBACK,
    RapidStartDisplayScreenCallback,
    NULL,
    &Event
    );
}
