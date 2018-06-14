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
  This file contains a 'Sample Driver' and is licensed as such  
  under the terms of your license agreement with Intel or your  
  vendor.  This file may be modified by the user, subject to    
  the additional terms of the license agreement                 
--*/


Device (\_SB.PCI0.DOCK)
{

  Name(_HID, "ABCD0000")
  Name(_CID, EISAID("PNP0C15"))
  Name(_UID,"SADDLESTRING")

  Method(_EJ0, 1) {
    P8XH(0,0xED)
    If(LEqual(ECON,1))
    { 
      \_SB.PCI0.LPCB.H_EC.ECWT(1, RefOf(\_SB.PCI0.LPCB.H_EC.EJET))
    }
    Return ()
  }
  
  Method(_STA, 0) {
    If(LEqual(ECON,0))
    { 
      Return(0x0)
    }
    If(LEqual(S0ID,1))
    {
      Return(0x0)
    }
    if(\DSTS) {
      P8XH(1,0x13)
      P8XH(0,0x13)
      Return(0x0F)
    } else {
      P8XH(1,0x14)
      P8XH(0,0x14)
      Return(0x0)
    }
  }

  Method(_DCK, 1) {
    P8XH(0,0xD3)

    If (Arg0) {
      Return (1)
    }
    Else {
      Store(0, \DSTS)
      If(LEqual(ECON,1))
      { 
        \_SB.PCI0.LPCB.H_EC.ECWT(0, RefOf(\_SB.PCI0.LPCB.H_EC.EJET))
      }
      Return (1)
    }    
  }
  

  Name(_EDL, Package( ) {   // DOCK1 has several dependent devices
        \_SB.PCI0.RP07.PXSX,
        \_SB.PCI0.RP08.PXSX,
        \_SB.PCI0.EHC1,
        \_SB.PCI0.SAT0,
        \_SB.PCI0.HDEF,
    })

}
