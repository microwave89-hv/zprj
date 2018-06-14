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

Scope(\_SB.PCI0.LPCB)
{

Device(H_EC)  // Hitachi Embedded Controller
{
  Name(_HID, EISAID("PNP0C09"))

  Name(_UID,1)

  Method(_STA)
  {
    Store(3, \_SB.PCI0.GFX0.CLID)
    Return(0x00) //Hide device
  }

  Name(B1CC, 0)
  Name(B1ST, 0)
  Name(B2CC, 0)
  Name(B2ST, 0)
  Name(CFAN, 0)
  Name(CMDR, 0)
  Name(DOCK, 0)
  Name(EJET, 0)
  Name(MCAP, 0)
  Name(PLMX, 0)
  Name(PECH, 0)
  Name(PECL, 0)
  Name(PENV, 0)
  Name(PINV, 0)
  Name(PPSH, 0)
  Name(PPSL, 0)
  Name(PSTP, 0)
  Name(RPWR, 0)
  Name(LIDS, 0)
  Name(LSTE, 0)
  Name(SLPC, 0)
  Name(VPWR, 0)
  Name(WTMS, 0)
  Name(AWT2, 0)
  Name(AWT1, 0)
  Name(AWT0, 0)
  Name(DLED, 0)
  Name(IBT1, 0)
  Name(ECAV, Zero)   // OS Bug Checks if EC OpRegion accessed before Embedded Controller Driver loaded
  Name(SPT2, 0)
  Name(PB10, 0)

  // ECRD (Embedded Read Method)
  //
  // Handle all commands sent to EC by BIOS
  //
  //  Arguments: (1)
  //    Arg0 - Object to Read
  //  Return Value:
  //    Read Value
  //    
  Method(ECRD,1,Serialized, 0, IntObj, FieldUnitObj)
  {
    Return(DeRefOf(Arg0))
  }

  // ECWT (Embedded Write Method)
  //
  // Handle all commands sent to EC by BIOS
  //
  //  Arguments: (2)
  //    Arg0 - Value to Write
  //    Arg1 - Object to Write to
  //    
  Method(ECWT,2,Serialized,,,{IntObj, FieldUnitObj})
  {
    Store(Arg0,Arg1)
  }


  Method(ECMD,1,Serialized)  // Handle all commands sent to EC by BIOS
  {
   If (\ECON)
    {
     While(\_SB.PCI0.LPCB.H_EC.CMDR){Stall(20)}
     Store(Arg0, \_SB.PCI0.LPCB.H_EC.CMDR)
    }
  }

    Device(BAT0)
    {
	Name(_HID,EISAID("PNP0C0A"))

	Name(_UID,0)

	Method(_STA,0)
	{
	    Return(0)		// Hide device 
	}
    }

  // Real battery code
  //
    Scope(\)
    {
      // these fields come from the Global NVS area
      Field(GNVS,AnyAcc,Lock,Preserve)
      {
	    Offset(30),	// Battery Support Registers:
            BNUM, 8,	//   (30) Battery Number Present
	    Offset(32),
	    B1SC, 8,	//   (32) Battery 1 Stored Capacity
	    Offset(35),
	    B1SS, 8,	//   (35) Battery 1 Stored Status
      }
    } // end  Scope(\)

    Device(BAT1)
    {
	 Name(_HID,EISAID("PNP0C0A"))

	Name(_UID,1)

	Method(_STA,0)
	{
	    Return(0)		// Hide device 
	}
    }

    Scope(\)
    {
      // these fields come from the Global NVS area
      Field(GNVS,AnyAcc,Lock,Preserve)
      {
    	    Offset(33),
	    B2SC, 8,	//   (33) Battery 2 Stored Capacity
	    Offset(36),
	    B2SS, 8	//   (36) Battery 2 Stored Status
      }
    } // end Scope(\)
    Device(BAT2)
    {
	 Name(_HID,EISAID("PNP0C0A"))

	Name(_UID,2)

	Method(_STA,0)
	{
	    Return(0)		// Hide device 
	}
    }

  }
}// end scope Scope(\_SB.PCI0.LPCB)
  // System Bus

Device (\_SB.PCI0.DOCK)
{
	Name(_HID, "ABCD0000")
	Name(_CID, EISAID("PNP0C15"))
	Name(_UID,2)
    Method(_STA)
    {
      Return(0x00)
    }

}
Scope(\_SB)
{

  // Define a Lid Switch.

  Device(LID0)
  {
    Name(_HID,EISAID("PNP0C0D"))

    Method(_STA)
    {
      Return(0x00)
    }

  }
}//end scope _SB


