/**************************************************************************;
;*                                                                        *;
;*    Intel Confidential                                                  *;
;*                                                                        *;
;*    Intel Corporation - ACPI Reference Code for the Sandy Bridge        *;
;*    Family of Customer Reference Boards.                                *;
;*                                                                        *;
;*                                                                        *;
;*    Copyright (c)  1999 - 2013 Intel Corporation. All rights reserved   *;
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
  This file contains a 'Sample Driver' and is licensed as such  
  under the terms of your license agreement with Intel or your  
  vendor.  This file may be modified by the user, subject to    
  the additional terms of the license agreement                 
--*/

    Name(WKEN, 0)

    Method(_S0W, 0)
    { // PMEs can be generated from D3hot
        Return(3) //For ULT
    } // End _S0W

    Method(_DSW, 3)
    {
      If(Arg1)
      { // Entering Sx, need to disable WAKE# from generating runtime PME
        Store(0, WKEN)
      } Else {  // Staying in S0
        If(LAnd(Arg0, Arg2)) // Exiting D0 and arming for wake
        { // Set PME
          Store(1, WKEN)
        } Else { // Disable runtime PME, either because staying in D0 or disabling wake 
          Store(0, WKEN)
        }
      }
    } // End _DSW
    
    // Define a power resource for PCIe RP D0-D3hot
    PowerResource(PXP, 0, 0)
    {
      Method(_STA, 0)
      {
        if(LAND(LEqual(\_SB.RDGP(PWRG),PONP), LEqual(\_SB.RDGP(RSTG),RONP))){
          Return (1)
        } Else {
          Return (0)
        }
      }
      Method(_ON) // Turn on core power to PCIe Slot
      {

        // Power ON for Slot
        // Dont enable power for NGFF because NGFF only has AUX power
        If(LNot(NGFF)) {
          \_SB.WTGP(PWRG,PONP)
          Sleep(PEP0)     // Sleep for programmable delay
        }

        // Enable PCIe Src Clock
        While(LEqual(PMFS,1)){ // PMC message serviced?
          Stall(10)
        }
        Store(Or(ShiftLeft(SCLK, 24), ShiftLeft(SCLK, 16)), Local1)  // Set Bit and Mask
        Or(Local1, 4, Local1)  // OCKEN command
        Store(Local1, \CKEN)   // Enable Source Clock
        While(LEqual(PMFS,1)){ // PMC message serviced?
          Stall(10)
        }

        \_SB.WTGP(RSTG,RONP) // De-Assert Reset Pin
        Store(1, L23R) // Set L23_Rdy to Detect Transition  (L23R2DT)
        Sleep(16)
        Store(0, Local0)
        // Wait up to 12 ms for transition to Detect
        While(L23R) {
          If(Lgreater(Local0, 4))    // Debug - Wait for 5 ms
          {
            Break
          }
          Sleep(16)
          Increment(Local0)
        }
        // Once in Detect, wait up to 124 ms for Link Active (typically happens in under 70ms)
        // Worst case per PCIe spec from Detect to Link Active is:
        // 24ms in Detect (12+12), 72ms in Polling (24+48), 28ms in Config (24+2+2+2+2)
        Store(0, Local0)
        While(LEqual(LASX,0)) {
          If(Lgreater(Local0, 123))
          {
            Break
          }
          Sleep(16)
          Increment(Local0)
        }
        // ADBG(Local0) // uncomment to print the timeout value for debugging
        Store(0, LEDM) // PCIEDBG.DMIL1EDM (324[3]) = 0
      }
      Method(_OFF) // Turn off core power to PCIe Slot
      {
        // Set L23_Rdy Entry Request (L23ER)
        Store(1, L23E)
        Sleep(16)
        Store(0, Local0)
        While(L23E) {
          If(Lgreater(Local0, 4)){ // Debug - Wait for 5 ms
            Break
          }
          Sleep(16)
          Increment(Local0)
        }
        Store(1, LEDM) // PCIEDBG.DMIL1EDM (324[3]) = 1

        While(LEqual(PMFS,1)){ // PMC message serviced?
          Stall(10)
        }
        // Disable PCIe Src Clock
        Store(Or(ShiftLeft(SCLK, 24), 4), Local1)  // Set Mask, OCKEN command
        Store(Local1, \CKEN)     // Disable Source Clock
        While(LEqual(PMFS,1)){ // PMC message serviced?
          Stall(10)
        }

        \_SB.WTGP(RSTG,Not(RONP)) // Assert Reset Pin
        
        If(LNot(NGFF)) { // Dont disable power for NGFF because NGFF only has AUX power
          \_SB.WTGP(PWRG,Not(PONP)) //Power OFF for Slot
        }

        Store(1, LDIS)
        Store(0, LDIS) //toggle link disable

        If(WKEN) {
          Switch(SLOT){
            Case(0x3){ // Root Port 3
              Store(1, \GS08) //Clear GPE STATUS
              Store(0, \GO08) //GPIO_OWN to ACPI Driver
            }
            Case(0x4){ // Root Port 4
              Store(1, \GS45) //Clear GPE STATUS
              Store(0, \GO45) //GPIO_OWN to ACPI Driver
            }
            Case(0x5){ // Root Port 5
              Store(1, \GS51) //Clear GPE STATUS
              Store(0, \GO51) //GPIO_OWN to ACPI Driver
            }
            Default{
            }
          }
        }
      } // End of Method_OFF
    } // End PXP

    Name(_PR0, Package(){PXP})

