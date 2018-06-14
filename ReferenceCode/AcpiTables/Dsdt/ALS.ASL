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



Device(ALSD) 
{
  Name(_HID,"ACPI0008")

  Method(_STA,0)
  {
    If(LEqual(ALSE,2))
    {
      Return(0x000B)    // ALS Enabled.  Don't show it in UI.
    }

    Return(0x0000)      // ALS Disabled.  Hide it.
  }

  Method(_ALI)
  {
    Return (Or(ShiftLeft(LHIH,8),LLOW))
  }

  Name(_ALR, Package()
  {
    Package() {70,  0},
    Package() {73,  10},
    Package() {85,  80},
    Package() {100, 300},
    Package() {150, 1000}
  })
  
}
