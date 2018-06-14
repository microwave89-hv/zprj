/**************************************************************************;
;*                                                                        *;
;*    Intel Confidential                                                  *;
;*                                                                        *;
;*    Intel Corporation - ACPI Reference Code for the Haswell             *;
;*    Family of Customer Reference Boards.                                *;
;*                                                                        *;
;*                                                                        *;
;*    Copyright (c)  1999 - 2012 Intel Corporation. All rights reserved   *;
;*    This software and associated documentation (if any) is furnished    *;
;*    under a license and may only be used or copied in accordance        *;
;*    with the terms of the license. Except as permitted by such          *;
;*    license, no part of this software or documentation may be           *;
;*    reproduced, stored in a retrieval system, or transmitted in any     *;
;*    form or by any means without the express written consent of         *;
;*    Intel Corporation.                                                  *;
;*                                                                        *;
;*                                                                        *;
;**************************************************************************/
/*++
  This file contains an 'Intel Peripheral Driver' and is
  licensed for Intel CPUs and chipsets under the terms of your  
  license agreement with Intel or your vendor.  This file may   
  be modified by the user, subject to additional terms of the   
  license agreement                                             
--*/   

      OperationRegion(PWKE,PCI_Config,0x54,0x12)

      Field(PWKE,DWordAcc,NoLock,Preserve)
      {
            , 8,
        PMEE, 1, // PWR_CNTL_STS.PME_En
            , 6,
        PMES, 1, // PWR_CNTL_STS.PME_Sts
        Offset (0x0E),
            , 1,
        PWUC, 6 // Port Wake Up Capability Mask
      }

      Method(_PSW,1)
      {
        If(Arg0)
        {
          Store(Ones,PWUC)
        }
        Else
        {
          Store(0,PWUC)
        }
      }

      // The CRB leaves the USB ports on in S3/S4 to allow
      // the ability to Wake from USB.  Therefore, define
      // the below control methods to state D2 entry during
      // the given S-State.

      Method(_S3D,0)
      {
        Return(2)
      }

      Method(_S4D,0)
      {
        Return(2)
      }

      Device(HUBN)
      {
        Name(_ADR, Zero)

        Device(PR01)
        {
          Name(_ADR, One)

          //
          // There will have "Generic USB Hub" existed at Port 1 of each EHCI controller
          // in Windows "Device Manager" while RMH is enabled, so need to add _UPC
          // and _PLD to report OS that it's not user visible to pass WHQL: Single Computer
          // Display Object test in Win7
          //
          Method(_UPC,0,Serialized) {
            Name(UPCA, Package() { ASL_EHC2_PR01_UPC })
            Return(UPCA)
          }
          Method(_PLD,0,Serialized) {
            Name(PLDP, Package() {
              Buffer (0x10) {
                ASL_EHC2_PR01_PLD}
                })
              Return (PLDP)
            }

          Device(PR11)
          {
            Name(_ADR, One)
            Method(_UPC,0,Serialized) {
              Name(UPCP, Package() { ASL_EHC2_PR11_UPC })
              Return(UPCP)
            }
            Method(_PLD,0,Serialized) {
              Name(PLDP, Package() {
                Buffer (0x10) {
                  ASL_EHC2_PR11_PLD}
                })
              Return (PLDP)
            }
          }

          Device(PR12)
          {
            Name(_ADR, 0x02)
            Method(_UPC,0,Serialized) {
              Name(UPCP, Package() { ASL_EHC2_PR12_UPC })
              Return(UPCP)
            }
            Method(_PLD,0,Serialized) {
              Name(PLDP, Package() {
                Buffer (0x10) {
                  ASL_EHC2_PR12_PLD}
                })
              Return (PLDP)
            }
            Alias(SBV1,SDGV) // copy USB Sideband Deferring GPE Vector (HOST_ALERT#1) to DSM method
            Include("UsbSBD.ASL")
          }

          Device(PR13)
          {
            Name(_ADR, 0x03)
            Method(_UPC,0,Serialized) {
              Name(UPCP, Package() { ASL_EHC2_PR13_UPC })
              Return(UPCP)
            }
            Method(_PLD,0,Serialized) {
              Name(PLDP, Package() {
                Buffer (0x10) {
                  ASL_EHC2_PR13_PLD}
              })
              CreateBitField(DeRefOf(Index(PLDP,0)),64,VIS)
              If(LEqual(And(CDID,0xF000), 0x9000)) {  // on LPT-LP platforms this port is internal
                And(VIS,0,VIS)
              }
              Return (PLDP)
            }
            Alias(SBV2,SDGV) // copy USB Sideband Deferring GPE Vector (HOST_ALERT#2) to DSM method
            Include("UsbSBD.ASL")
          }

          Device(PR14)
          {
            Name(_ADR, 0x04)
            Method(_UPC,0,Serialized) {
              Name(UPCP, Package() { ASL_EHC2_PR14_UPC })
              Return(UPCP)
            }
            Method(_PLD,0,Serialized) {
              Name(PLDP, Package() {
                Buffer (0x10) {
                  ASL_EHC2_PR14_PLD}
                })
              Return (PLDP)
            }
          }

          Device(PR15)
          {
            Name(_ADR, 0x05)
            Method(_UPC,0,Serialized) {
              Name(UPCP, Package() { ASL_EHC2_PR15_UPC })
              Return(UPCP)
            }
            Method(_PLD,0,Serialized) {
              Name(PLDP, Package() {
                Buffer (0x10) {
                  ASL_EHC2_PR15_PLD}
                })
              Return (PLDP)
            }
          }

          Device(PR16)
          {
            Name(_ADR, 0x06)
            Method(_UPC,0,Serialized) {
              Name(UPCP, Package() { ASL_EHC2_PR16_UPC })
              Return(UPCP)
            }
            Method(_PLD,0,Serialized) {
              Name(PLDP, Package() {
                Buffer (0x10) {
                  ASL_EHC2_PR16_PLD}
                })
              Return (PLDP)
            }
          }

        } // End of PR01
      } // End of HUBN
