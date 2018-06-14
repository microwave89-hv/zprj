/**************************************************************************;
;*                                                                        *;
;*    Intel Confidential                                                  *;
;*                                                                        *;
;*    Intel Corporation - ACPI Reference Code for the Sandy Bridge        *;
;*    Family of Customer Reference Boards.                                *;
;*                                                                        *;
;*                                                                        *;
;*    Copyright (c)  1999 - 2010 Intel Corporation. All rights reserved   *;
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

Scope(\_SB)
{
  Device(PWRB)
  {
    Name(_HID,EISAID("PNP0C0C"))

    // GPI14 = GPE30 = Waketime SCI.  The PRW isn't working when
    // placed in any of the logical locations ( PS2K, PS2M,
    // H_EC ), so a Power Button Device was created specifically
    // for the WAKETIME_SCI PRW.

    Name(_PRW, Package(){30,4})
    
    Method(_STA)
    {
      Return(0x0F)
    }
  }//end device PWRB
}//end scope _SB


