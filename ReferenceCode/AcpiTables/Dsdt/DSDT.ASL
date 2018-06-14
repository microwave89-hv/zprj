/**************************************************************************;
;*                                                                        *;
;*    Intel Confidential                                                  *;
;*                                                                        *;
;*    Intel Corporation - ACPI Reference Code for the Haswell             *;
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


DefinitionBlock (
    "DSDT.aml",
    "DSDT",
    0x02, // DSDT revision.
        // A Revision field value greater than or equal to 2 signifies that integers 
        // declared within the Definition Block are to be evaluated as 64-bit values
    "INTEL", // OEM ID (6 byte string)
    "HSW-LPT", // OEM table ID  (8 byte string)
    0x0 // OEM version of DSDT table (4 byte Integer)
    )

// BEGIN OF ASL SCOPE
{

External(LHIH)
External(LLOW)
External(IGDS)
External(LIDS)
External(BRTL)
External(ALSE)
External(GSMI)
External(\_SB.PCI0.GFX0.ALSI)
External(\_SB.PCI0.GFX0.CDCK)
External(\_SB.PCI0.GFX0.CBLV)
External(\_SB.PCI0.GFX0.GSSE)
External(\_SB.PCI0.PEG0, DeviceObj)
External(\_SB.PCI0.PEG0.PEGP, DeviceObj)
External(\_SB.PCI0.PEG1, DeviceObj)
External(\_SB.PCI0.PEG2, DeviceObj)
External(\_SB.PCI0.GFX0.DD1F, DeviceObj)
External(\_SB.PCI0.GFX0.GDCK, MethodObj)
External(\_SB.PCI0.GFX0.GHDS, MethodObj)
External(\_SB.PCI0.GFX0.AINT, MethodObj)
External(\_SB.PCI0.GFX0.GLID, MethodObj)
External(\_SB.PCI0.GFX0.GSCI, MethodObj)
External(\_PR.CPU0, DeviceObj)
External(\_PR.CPU0._PSS, MethodObj)
External(\_PR.CPU0._PPC, IntObj)


// Miscellaneous services enabled in Project
    include ("amlupd.asl")
    include ("token.asl")
    include ("GloblNvs.asl")
    include ("PCItree.asl")
    include ("Platform.asl")
    include ("CPU.asl")
    include ("Thermal.asl")
    include ("PCI_DRC.asl")
    include ("Video.asl")
    include ("Gpe.asl")
    include ("PCIEDOCK.asl")
    include ("Pch.asl")  // Not in this package. Refer to the PCH Reference Code accordingly
//----------------------------------------------------------------------
    Name(\_S0, Package(4){0x0,0x0,0,0}) // mandatory System state
    if(SS1) { Name(\_S1, Package(4){0x1,0x0,0,0})}
    if(SS3) { Name(\_S3, Package(4){0x5,0x0,0,0})}
    if(SS4) { Name(\_S4, Package(4){0x6,0x0,0,0})}
    Name(\_S5, Package(4){0x7,0x0,0,0}) // mandatory System state

    Method(PTS, 1) {        // METHOD CALLED FROM _PTS PRIOR TO ENTER ANY SLEEP STATE
        If(Arg0)            // entering any sleep state
        {
        }
    }
    Method(WAK, 1) {        // METHOD CALLED FROM _WAK RIGHT AFTER WAKE UP
    }
}// End of ASL File

