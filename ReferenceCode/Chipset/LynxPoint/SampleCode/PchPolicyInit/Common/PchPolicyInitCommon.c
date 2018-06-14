/** @file
  This file is SampleCode for Intel PCH Common Platform Policy initialzation.

@copyright
  Copyright (c) 2013 Intel Corporation. All rights reserved
  This software and associated documentation (if any) is furnished
  under a license and may only be used or copied in accordance
  with the terms of the license. Except as permitted by such
  license, no part of this software or documentation may be
  reproduced, stored in a retrieval system, or transmitted in any
  form or by any means without the express written consent of
  Intel Corporation.

  This file contains a 'Sample Driver' and is licensed as such
  under the terms of your license agreement with Intel or your
  vendor.  This file may be modified by the user, subject to
  the additional terms of the license agreement

**/
#if !defined(EDK_RELEASE_VERSION) || (EDK_RELEASE_VERSION < 0x00020000)
#include "EdkIIGlueDxe.h"
#include "EdkIIGlueBase.h"
#include "PchPlatformPolicy.h"
#include "PchPlatformLib.h"
#include "PchRegs.h"
#endif

/**
  Initilize Intel USB Common Platform Policy

  @param[in] PchUsbConfig         Usb platform policy structure.

  @retval NONE
**/
VOID
InitPchUsbConfig (
  IN PCH_USB_CONFIG                     *PchUsbConfig
  )
{
  UINTN           PortIndex;
  UINT16          LpcDeviceId;
  PCH_SERIES      PchSeries;

  if (PchUsbConfig == NULL) {
    return;
  }

  PchSeries = GetPchSeries();
  LpcDeviceId = MmioRead16 (MmPciAddress (0, 0, PCI_DEVICE_NUMBER_PCH_LPC, PCI_FUNCTION_NUMBER_PCH_LPC, 0) + R_PCH_LPC_DEVICE_ID);

  //
  // EHCI Host Controller Enable/Disable
  //
  PchUsbConfig->Usb20Settings[0].Enable       = PCH_DEVICE_ENABLE;
  PchUsbConfig->Usb20Settings[1].Enable       = PCH_DEVICE_ENABLE;
  
  //
  // Automatically disable EHCI when XHCI Mode is Enabled to save power.
  //
  if (PchUsbConfig->Usb30Settings.Mode == PCH_XHCI_MODE_ON) {
    PchUsbConfig->Usb20Settings[0].Enable = PCH_DEVICE_DISABLE;
    if (PchSeries == PchH) {
      PchUsbConfig->Usb20Settings[1].Enable = PCH_DEVICE_DISABLE;
    }
  }
  //
  // Set to Enable if BIOS has its own xHCI driver
  //
  PchUsbConfig->Usb30Settings.PreBootSupport  = PCH_DEVICE_ENABLE;
  ///
  /// PCH BIOS Spec Rev 0.5.0 Section 13.1 xHCI controller options in Reference Code
  /// Please refer to Table 13-1 in PCH BIOS Spec for USB Port Operation with no xHCI
  /// pre-boot software.
  /// Please refer to Table 13-2 in PCH BIOS Spec for USB Port Operation with xHCI
  /// pre-boot software.
  ///
  /// The xHCI modes that available in BIOS are:
  /// Disabled   - forces only USB 2.0 to be supported in the OS. The xHCI controller is turned off
  ///              and hidden from the PCI space.
  /// Enabled    - allows USB 3.0 to be supported in the OS. The xHCI controller is turned on. The
  ///              shareable ports are routed to the xHCI controller. OS needs to provide drivers
  ///              to support USB 3.0.
  /// Auto       - This mode uses ACPI protocol to provide an option that enables the xHCI controller
  ///              and reroute USB ports via the _OSC ACPI method call. Note, this mode switch requires
  ///              special OS driver support for USB 3.0.
  /// Smart Auto - This mode is similar to Auto, but it adds the capability to route the ports to xHCI
  ///              or EHCI according to setting used in previous boots (for non-G3 boot) in the pre-boot
  ///              environment. This allows the use of USB 3.0 devices prior to OS boot. Note, this mode
  ///              switch requires special OS driver support for USB 3.0 and USB 3.0 software available
  ///              in the pre-boot enviroment.
  ///
  /// Manual Mode - For validation and experimental purposes only. Do not create setup option for end-user BIOS.
  ///
  /// Recommendations:
  ///  - If BIOS supports xHCI pre-boot driver then use Smart Auto mode as default
  ///  - If BIOS does not support xHCI pre-boot driver then use AUTO mode as default
  ///
  if (PchUsbConfig->Usb30Settings.PreBootSupport == PCH_DEVICE_ENABLE) {
    PchUsbConfig->Usb30Settings.Mode = PCH_XHCI_MODE_SMARTAUTO;
  } else {
    PchUsbConfig->Usb30Settings.Mode = PCH_XHCI_MODE_AUTO;
  }

  //
  // Manual Mode is for validation and experimental purposes only.
  // Do not create setup option for end-user BIOS.
  //
  PchUsbConfig->Usb30Settings.ManualMode = PCH_DEVICE_DISABLE;

  //
  // XhciIdleL1 can be set to disable for LPT-LP Ax stepping to workaround USB3 hot plug will fail after 1 hot plug removal. 
  //
  PchUsbConfig->Usb30Settings.XhciIdleL1 = PCH_DEVICE_ENABLE;

  //
  // Btcg is for enabling/disabling trunk clock gating.
  //
  PchUsbConfig->Usb30Settings.Btcg = PCH_DEVICE_ENABLE;

  for (PortIndex = 0; PortIndex < GetPchUsbMaxPhysicalPortNum (); PortIndex++) {
    PchUsbConfig->Usb30Settings.ManualModeUsb20PerPinRoute[PortIndex]   = 0;
  }

  for (PortIndex = 0; PortIndex < GetPchXhciMaxUsb3PortNum (); PortIndex++) {
    PchUsbConfig->Usb30Settings.ManualModeUsb30PerPinEnable[PortIndex]  = PCH_DEVICE_DISABLE;
  }

  //
  // Use by AMT/MEBx to enable USB-R support.
  //
  PchUsbConfig->Ehci1Usbr                 = PCH_DEVICE_DISABLE;
  PchUsbConfig->Ehci2Usbr                 = PCH_DEVICE_DISABLE;

  //
  // UsbPrecondition = Enable , Force USB Init happen in PEI as part of 2Sec Fast Boot bios optimization
  // UsbPrecondition = Disable, USB Init happen in DXE just like traditionally where it happen.
  //
  PchUsbConfig->UsbPrecondition           = PCH_DEVICE_DISABLE;

  //
  // USB Per-Port Control is use to Enable/Disable individual port.
  //
  PchUsbConfig->UsbPerPortCtl           = PCH_DEVICE_DISABLE;

  PchUsbConfig->PortSettings[0].Enable  = PCH_DEVICE_ENABLE;
  PchUsbConfig->PortSettings[1].Enable  = PCH_DEVICE_ENABLE;
  PchUsbConfig->PortSettings[2].Enable  = PCH_DEVICE_ENABLE;
  PchUsbConfig->PortSettings[3].Enable  = PCH_DEVICE_ENABLE;
  PchUsbConfig->PortSettings[4].Enable  = PCH_DEVICE_ENABLE;
  PchUsbConfig->PortSettings[5].Enable  = PCH_DEVICE_ENABLE;
  PchUsbConfig->PortSettings[6].Enable  = PCH_DEVICE_ENABLE;
  PchUsbConfig->PortSettings[7].Enable  = PCH_DEVICE_ENABLE;
  PchUsbConfig->PortSettings[8].Enable  = PCH_DEVICE_ENABLE;
  PchUsbConfig->PortSettings[9].Enable  = PCH_DEVICE_ENABLE;
  PchUsbConfig->PortSettings[10].Enable = PCH_DEVICE_ENABLE;
  PchUsbConfig->PortSettings[11].Enable = PCH_DEVICE_ENABLE;
  PchUsbConfig->PortSettings[12].Enable = PCH_DEVICE_ENABLE;
  PchUsbConfig->PortSettings[13].Enable = PCH_DEVICE_ENABLE;

  PchUsbConfig->Port30Settings[0].Enable  = PCH_DEVICE_ENABLE;
  PchUsbConfig->Port30Settings[1].Enable  = PCH_DEVICE_ENABLE;
  PchUsbConfig->Port30Settings[2].Enable  = PCH_DEVICE_ENABLE;
  PchUsbConfig->Port30Settings[3].Enable  = PCH_DEVICE_ENABLE;
  PchUsbConfig->Port30Settings[4].Enable  = PCH_DEVICE_ENABLE;
  PchUsbConfig->Port30Settings[5].Enable  = PCH_DEVICE_ENABLE;

  //
  // USB Port Over Current Pins mapping, please set as per board layout.
  //
  PchUsbConfig->Usb20OverCurrentPins[ 0] = PchUsbOverCurrentPin0;
  PchUsbConfig->Usb20OverCurrentPins[ 1] = PchUsbOverCurrentPin0;
  PchUsbConfig->Usb20OverCurrentPins[ 2] = PchUsbOverCurrentPin1;
  PchUsbConfig->Usb20OverCurrentPins[ 3] = PchUsbOverCurrentPin1;
  PchUsbConfig->Usb20OverCurrentPins[ 4] = PchUsbOverCurrentPin2;
  PchUsbConfig->Usb20OverCurrentPins[ 5] = PchUsbOverCurrentPin2;
  PchUsbConfig->Usb20OverCurrentPins[ 6] = PchUsbOverCurrentPin3;
  PchUsbConfig->Usb20OverCurrentPins[ 7] = PchUsbOverCurrentPin3;
  PchUsbConfig->Usb20OverCurrentPins[ 8] = PchUsbOverCurrentPin4;
  PchUsbConfig->Usb20OverCurrentPins[ 9] = PchUsbOverCurrentPin4;
  PchUsbConfig->Usb20OverCurrentPins[10] = PchUsbOverCurrentPin5;
  PchUsbConfig->Usb20OverCurrentPins[11] = PchUsbOverCurrentPin5;
  PchUsbConfig->Usb20OverCurrentPins[12] = PchUsbOverCurrentPin6;
  PchUsbConfig->Usb20OverCurrentPins[13] = PchUsbOverCurrentPin6;

  PchUsbConfig->Usb30OverCurrentPins[0]  = PchUsbOverCurrentPin0;
  PchUsbConfig->Usb30OverCurrentPins[1]  = PchUsbOverCurrentPin0;
  PchUsbConfig->Usb30OverCurrentPins[2]  = PchUsbOverCurrentPin1;
  PchUsbConfig->Usb30OverCurrentPins[3]  = PchUsbOverCurrentPin1;
  PchUsbConfig->Usb30OverCurrentPins[4]  = PchUsbOverCurrentPin2;
  PchUsbConfig->Usb30OverCurrentPins[5]  = PchUsbOverCurrentPin2;

  //
  // USB 2.0 D+/D- trace length in inchs*10 or 1000mils/10 measurement eg. 12.3" = 0x123
  // Please set as per board layout.
  //
  PchUsbConfig->PortSettings[ 0].Usb20PortLength = 0x100;
  PchUsbConfig->PortSettings[ 1].Usb20PortLength = 0x100;
  PchUsbConfig->PortSettings[ 2].Usb20PortLength = 0x100;
  PchUsbConfig->PortSettings[ 3].Usb20PortLength = 0x100;
  PchUsbConfig->PortSettings[ 4].Usb20PortLength = 0x100;
  PchUsbConfig->PortSettings[ 5].Usb20PortLength = 0x100;
  PchUsbConfig->PortSettings[ 6].Usb20PortLength = 0x100;
  PchUsbConfig->PortSettings[ 7].Usb20PortLength = 0x100;
  PchUsbConfig->PortSettings[ 8].Usb20PortLength = 0x100;
  PchUsbConfig->PortSettings[ 9].Usb20PortLength = 0x100;
  PchUsbConfig->PortSettings[10].Usb20PortLength = 0x100;
  PchUsbConfig->PortSettings[11].Usb20PortLength = 0x100;
  PchUsbConfig->PortSettings[12].Usb20PortLength = 0x100;
  PchUsbConfig->PortSettings[13].Usb20PortLength = 0x100;

  //
  // Port Location
  //
  PchUsbConfig->PortSettings[ 0].Location = PchUsbPortLocationFrontPanel;
  PchUsbConfig->PortSettings[ 1].Location = PchUsbPortLocationFrontPanel;
  PchUsbConfig->PortSettings[ 2].Location = PchUsbPortLocationFrontPanel;
  PchUsbConfig->PortSettings[ 3].Location = PchUsbPortLocationFrontPanel;
  PchUsbConfig->PortSettings[ 4].Location = PchUsbPortLocationFrontPanel;
  PchUsbConfig->PortSettings[ 5].Location = PchUsbPortLocationFrontPanel;
  PchUsbConfig->PortSettings[ 6].Location = PchUsbPortLocationFrontPanel;
  PchUsbConfig->PortSettings[ 7].Location = PchUsbPortLocationFrontPanel;
  PchUsbConfig->PortSettings[ 8].Location = PchUsbPortLocationFrontPanel;
  PchUsbConfig->PortSettings[ 9].Location = PchUsbPortLocationFrontPanel;
  PchUsbConfig->PortSettings[10].Location = PchUsbPortLocationFrontPanel;
  PchUsbConfig->PortSettings[11].Location = PchUsbPortLocationFrontPanel;
  PchUsbConfig->PortSettings[12].Location = PchUsbPortLocationFrontPanel;
  PchUsbConfig->PortSettings[13].Location = PchUsbPortLocationFrontPanel;

/*
  Guideline:
  This algorithm is move from chipset level code to board level code to allow OEM more flexibility
  to tune the value for individual board layout electrical characteristics to pass the USB 2.0 Eye Diagram Test.

  IF Board=LPT-H Desktop
    For BIT[10:08] Usb20EyeDiagramTuningParam1 (PERPORTTXISET)
      IF Back Panel
        SET to 4
      ELSE
        SET to 3
      ENDIF

    For BIT[13:11] Usb20EyeDiagramTuningParam2 (PERPORTPETXISET)
      IF Back Panel
        IF Trace Length < 8"
           SET to 2
        ELSE IF Trace Length < 13"
           SET to 3
        ELSE
           SET to 4
        ENDIF
      ELSE
        SET to 2
      ENDIF

    For BIT[14]
      Always SET to 0

  END LPT-H Desktop

  IF Board=LPT-H Mobile
    For BIT[10:08] Usb20EyeDiagramTuningParam1 (PERPORTTXISET)
      IF Interal Topology
        SET to 5
      ELSE IF Dock
        SET to 4
      ELSE
        IF Trace Length < 7"
           SET to 5
        ELSE
           SET to 6
        ENDIF
      ENDIF

    For BIT[13:11] Usb20EyeDiagramTuningParam2 (PERPORTPETXISET)
      IF Interal Topology
        SET to 2
      ELSE IF Dock
        IF Trace Length < 5"
           SET to 1
        ELSE
           SET to 2
        ENDIF
      ELSE
        IF Trace Length < 10"
           SET to 2
        ELSE
           SET to 3
        ENDIF
      ENDIF

    For BIT[14]
      Always SET to 0
  END LPT-H Mobile

  IF Board=LPT-LP
    For BIT[10:08] Usb20EyeDiagramTuningParam1 (PERPORTTXISET)
      IF Back Panel OR MiniPciE
        IF Trace Length < 7"
           SET to 5
        ELSE
           SET to 6
        ENDIF
      ELSE IF Dock
        SET to 4
      ELSE
        SET to 5
      ENDIF

    For BIT[13:11] Usb20EyeDiagramTuningParam2 (PERPORTPETXISET)
      IF Back Panel OR MiniPciE
        IF Trace Length < 10"
           SET to 2
        ELSE
           SET to 3
        ENDIF
      ELSE IF Dock
        IF Trace Length < 5"
           SET to 1
        ELSE
           SET to 2
        ENDIF
      ELSE
        SET to 2
      ENDIF

    For BIT[14]
      Always SET to 0
  END LPT-LP
*/

   //
    // USB 2.0 trace length signal strength
    //
/*
    IF Board=LPT-H Mobile

    END LPT-H Mobile
*/

  if (PchSeries == PchH) {
    if (IS_PCH_LPT_LPC_DEVICE_ID_DESKTOP (LpcDeviceId)) {
      for (PortIndex = 0; PortIndex < GetPchUsbMaxPhysicalPortNum (); PortIndex++) {
        if (PchUsbConfig->PortSettings[PortIndex].Location == PchUsbPortLocationBackPanel) {
          PchUsbConfig->PortSettings[PortIndex].Usb20EyeDiagramTuningParam1 = 4; //Back Panel
        } else {
          PchUsbConfig->PortSettings[PortIndex].Usb20EyeDiagramTuningParam1 = 3; //Front Panel
        }

        if (PchUsbConfig->PortSettings[PortIndex].Location == PchUsbPortLocationBackPanel) {
          if (PchUsbConfig->PortSettings[PortIndex].Usb20PortLength < 0x80) {
            PchUsbConfig->PortSettings[PortIndex].Usb20EyeDiagramTuningParam2 = 2; //Back Panel, less than 7.9"
          } else if (PchUsbConfig->PortSettings[PortIndex].Usb20PortLength < 0x130) {
            PchUsbConfig->PortSettings[PortIndex].Usb20EyeDiagramTuningParam2 = 3; //Back Panel, 8"-12.9"
          } else {
            PchUsbConfig->PortSettings[PortIndex].Usb20EyeDiagramTuningParam2 = 4; //Back Panel, 13" onward
          }
        } else {
          PchUsbConfig->PortSettings[PortIndex].Usb20EyeDiagramTuningParam2 = 2; //Front Panel
        }
      }
    } else if (IS_PCH_LPT_LPC_DEVICE_ID_MOBILE (LpcDeviceId)) {
      for (PortIndex = 0; PortIndex < GetPchUsbMaxPhysicalPortNum (); PortIndex++) {
        if (PchUsbConfig->PortSettings[PortIndex].Location == PchUsbPortLocationInternalTopology) {
          PchUsbConfig->PortSettings[PortIndex].Usb20EyeDiagramTuningParam1 = 5; // Internal Topology
        } else if (PchUsbConfig->PortSettings[PortIndex].Location == PchUsbPortLocationDock) {
          PchUsbConfig->PortSettings[PortIndex].Usb20EyeDiagramTuningParam1 = 4; // Dock
        } else {
          if (PchUsbConfig->PortSettings[PortIndex].Usb20PortLength < 0x70) {
            PchUsbConfig->PortSettings[PortIndex].Usb20EyeDiagramTuningParam1 = 5; //Back Panel, less than 7"
          } else {
            PchUsbConfig->PortSettings[PortIndex].Usb20EyeDiagramTuningParam1 = 6; //Back Panel, 7" onward
          }
        }

        if (PchUsbConfig->PortSettings[PortIndex].Location == PchUsbPortLocationInternalTopology) {
          PchUsbConfig->PortSettings[PortIndex].Usb20EyeDiagramTuningParam2 = 2; // Internal Topology
        } else if (PchUsbConfig->PortSettings[PortIndex].Location == PchUsbPortLocationDock) {
          if (PchUsbConfig->PortSettings[PortIndex].Usb20PortLength < 0x50) {
            PchUsbConfig->PortSettings[PortIndex].Usb20EyeDiagramTuningParam2 = 1; //Dock, less than 5"
          } else {
            PchUsbConfig->PortSettings[PortIndex].Usb20EyeDiagramTuningParam2 = 2; //Dock, 5" onward
          }
        } else {
          if (PchUsbConfig->PortSettings[PortIndex].Usb20PortLength < 0x100) {
            PchUsbConfig->PortSettings[PortIndex].Usb20EyeDiagramTuningParam2 = 2; //Back Panel, less than 10"
          } else {
            PchUsbConfig->PortSettings[PortIndex].Usb20EyeDiagramTuningParam2 = 3; //Back Panel, 10" onward
          }
        }
      }
    }
  } else if (PchSeries == PchLp) {
    for (PortIndex = 0; PortIndex < GetPchUsbMaxPhysicalPortNum (); PortIndex++) {
      if ((PchUsbConfig->PortSettings[PortIndex].Location == PchUsbPortLocationBackPanel) || 
          (PchUsbConfig->PortSettings[PortIndex].Location == PchUsbPortLocationMiniPciE)) {
        if (PchUsbConfig->PortSettings[PortIndex].Usb20PortLength < 0x70) {
          PchUsbConfig->PortSettings[PortIndex].Usb20EyeDiagramTuningParam1 = 5; //Back Panel, less than 7"
        } else {
          PchUsbConfig->PortSettings[PortIndex].Usb20EyeDiagramTuningParam1 = 6; //Back Panel, 7" onward
        }
      } else if (PchUsbConfig->PortSettings[PortIndex].Location == PchUsbPortLocationDock) {
        PchUsbConfig->PortSettings[PortIndex].Usb20EyeDiagramTuningParam1 = 4; // Dock
      } else {
        PchUsbConfig->PortSettings[PortIndex].Usb20EyeDiagramTuningParam1 = 5; // Internal Topology
      } 

      if ((PchUsbConfig->PortSettings[PortIndex].Location == PchUsbPortLocationBackPanel) || 
          (PchUsbConfig->PortSettings[PortIndex].Location == PchUsbPortLocationMiniPciE)) {
        if (PchUsbConfig->PortSettings[PortIndex].Usb20PortLength < 0x100) {
          PchUsbConfig->PortSettings[PortIndex].Usb20EyeDiagramTuningParam2 = 2; //Back Panel, less than 10"
        } else {
          PchUsbConfig->PortSettings[PortIndex].Usb20EyeDiagramTuningParam2 = 3; //Back Panel, 10" onward
        }
      } else if (PchUsbConfig->PortSettings[PortIndex].Location == PchUsbPortLocationDock) {
        if (PchUsbConfig->PortSettings[PortIndex].Usb20PortLength < 0x50) {
          PchUsbConfig->PortSettings[PortIndex].Usb20EyeDiagramTuningParam2 = 1; //Dock, less than 5"
        } else {
          PchUsbConfig->PortSettings[PortIndex].Usb20EyeDiagramTuningParam2 = 2; //Dock, 5" onward
        }
      } else {
        PchUsbConfig->PortSettings[PortIndex].Usb20EyeDiagramTuningParam2 = 2; // Internal Topology
      }
    }
  }

  return;
}
