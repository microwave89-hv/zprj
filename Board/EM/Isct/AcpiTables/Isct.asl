//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ISCT/IsctAcpiTables/Isct.asl 7     7/11/14 9:52a Mirayang $
//
// $Revision: 7 $
//
// $Date: 7/11/14 9:52a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ISCT/IsctAcpiTables/Isct.asl $
// 
// 7     7/11/14 9:52a Mirayang
// Remove override.
// 
// 6     7/08/14 5:09a Mirayang
// EIP142924 iSCT 5.0 for Shark Bay Platform
// 
// 5     5/14/13 6:29a Bensonlai
// [TAG]  		EIP123328
// [Category]  	Spec Update
// [Severity]  	Normal
// [Description]  	[SBY] Intel Smart Connect Technology 4.x BIOS Reference
// Code
// 
// 4     3/27/13 9:13a Bensonlai
// [TAG]  		EIP118307
// [Category]  	New Feature
// [Description]  	Implementation of the ISCT Platform Design
// Specification 0.8.
// [Files]  		Isct.asl, IsctAcpi.c, IsctAcpi.mak
// 
// 3     1/14/13 12:03a Bensonlai
// [TAG]  		EIP112064
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	[ISCT] GWLS,SWLS,GWWS and SWWS are fail while set wake up
// timer to RTC
// [Solution]  	Implement the GWLS,SWLS,GWWS and SWWS while set wake up
// timer to RTC
// [Files]  		Isct.asl
// 
// 2     1/13/13 5:14a Bensonlai
// [TAG]  		EIP112064
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	[ISCT] GWLS,SWLS,GWWS and SWWS are fail while set wake up
// timer to RTC
// [Solution]  	Implement the GWLS,SWLS,GWWS and SWWS while set wake up
// timer to RTC
// [Files]  		Isct.asl
// 
// 1     9/02/12 11:18p Bensonlai
// Intel Smart Connect Technology initially releases.
//
//
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:  Isct.asl
//
// Description:	This file provides the ACPI methods for the iSCT agent to use.
//
//<AMI_FHDR_END>
//**********************************************************************

DefinitionBlock (
  "IsctAcpi.aml",
  "SSDT",
  1,
  "Intel_",
  "IsctTabl",
  0x1000
  )

{
  External(ICNF) //Isct Configuration
  External(\_SB.PCI0.LPCB.H_EC.IBT1)            // Isct Byte1 for EC
  External(\_SB.PCI0.LPCB.H_EC.IBT2)            // Isct Byte2 for EC
  External(\_SB.PCI0.LPCB.H_EC.ECMD, MethodObj) // EC Command method
  External(\_SB.PCI0.LPCB.H_EC.WTMS)            // EC Wake Timer Settings
  External(\_SB.PCI0.LPCB.H_EC.AWT0)            // EC Wake Timer Value (BIT7-0)
  External(\_SB.PCI0.LPCB.H_EC.AWT1)            // EC Wake Timer Value (BIT15-8)
  External(\_SB.PCI0.LPCB.H_EC.AWT2)            // EC Wake Timer Value (BIT23-16)
  External(\_SB.PCI0.LPCB.H_EC.LSTE)            // Lid State (Lid Open = 1)
  External(\_SB.IFFS.FFSS)

  External(\_SB.PCI0.GFX0.TCHE)                 // Technology enabled indicator
  External(\_SB.PCI0.GFX0.STAT)                 // State Indicator
  External(\_SB.PCI0.GFX0.ASLE)                 // Reg 0xE4, ASLE interrupt register
  External(\_SB.PCI0.GFX0.ASLC)                 // ASLE interrupt command/status
  External(\_SB.PCI0.GFX0.PARD, MethodObj)      // Check if the driver is ready to handle ASLE interrupts
  External(\ADBG, MethodObj)                    // Print message to ACPI Debug Buffer
  
  Scope (\_SB)
  {
    Device (IAOE)
    {
      OperationRegion(ISCT,SystemMemory,0xFFFF0008,0xAA58)
      Field(ISCT,AnyAcc,Lock,Preserve)
      {
        WKRS,  8,      // (0) ISCT Wake Reason
        AOCE,  8,      // (1) ISCT is Enabled
        FFSE,  8,      // (2) IFFS Enabled
        ITMR,  8,      // (3) ISCT Timer Type: 0 = EC, 1 = RTC
        ECTM,  32,     // (4) ISCT EC Timer
        RCTM,  32,     // (8) ISCT RTC Timer
        GNPT,  32,     // (12)ISCT GlobalNvs Ptr
        ATOW,  8,      // (16)ISCT timer over write, 1 = overwrited as ISCT timer
      }
      Name (_HID, "INT33A0")
      Name (_CID, "PNP0C02")
      Name (_UID, 0x00)

      Name (IBT1, 0)   // Isct Byte1 for EC (local)
      Name (IBT2, 0)   // Isct Byte2 for EC (local)
      Name (INSB, 0)   // Isct Notification Status Bit
      Name (WTMS, 0)   // EC Wake Timer Settings (local)
      Name (AWT0, 0)   // EC Wake Timer Value (BIT7-0) (local)
      Name (AWT1, 0)   // EC Wake Timer Value (BIT15-8) (local)
      Name (AWT2, 0)   // EC Wake Timer Value (BIT23-16) (local)
      Name (PTSL, 0)   // Platform Sleep Level
      Name (SLPD, 0)   // Sleep duration for when using NetDetect (dummy)
      Name (IMDS, 0)   // Isct Mode Select Bits
                       // Bits:    Description
                       //  0        Reserved
                       //  1        ISCT Wake Mode Select: 0 = Normal ISCT Wake Mode, 1 = Extended ISCT Wake Mode
                       //  2        Wake From S4: 0 = No Wake from S4, 1 = Wake from S4
                       //  3-7      Reserved
      Name (IWDT, 0)   // Isct Wake Duration Time
 
      /**
        GABS - Get ISCT BIOS Enablign Setting
        Input:   None
        Return:   
        Bits   Description       
        - 0      ISCT Configured: 0 = Disabled, 1 = Enabled 
        - 1      ISCT Notification Control: 0 = Unsupported, 1 = Supported 
        - 2      ISCT WLAN Power Control : 0 = Unsupported, 1 = Supported 
        - 3      ISCT WWAN Power Control : 0 = Unsupported, 1 = Supported 
        - 4      Must be set to 1 (BIOS Program Timer)
        - 5      Sleep duration value format: 0 = Actual time, 1 = Duration in Seconds
        - 6      RF Kill Switch Type: 0 = Software, 1 = Hardware
        - 7      Wake from S4: 0 = Unsupported, 1 = Supported 
      **/
      Method (GABS, 0, NotSerialized) {
        Return (ICNF)
      }

      //
      // GAOS - Get ISCT Function Status
      // Input:   None
      // Return:
      // Bits   Description
      // 0      ISCT Mode: 0 = Disabled, 1 = Enabled
      // 1      ISCT Wake Mode Select: 0 = ISCT Wake Mode, 1 = Extended ISCT Wake
      // 2 - 7  Reserved
      //
      Method (GAOS, 0, NotSerialized)
      {
        //
        // Check for RTC Timer, else EC timer
        //
        If (LEqual(ITMR, 1))
        {
        // Get Isct Mode Enable and Get Isct Wake Mode Select
        //
        Return(Or(And(IBT1, 0x01), And(IMDS, 0x06)))
        }
        Else
        {
          //
          //Get Isct Mode Enable
          //
          If (CondRefOf(\_SB.PCI0.LPCB.H_EC.IBT1))
          {
            Store(\_SB.PCI0.LPCB.H_EC.IBT1, Local0)
          }
          Else
          {	
            Store(IBT1, Local0)
          }
          And(Local0, 0x01, Local0)
          //
          // Get Isct Wake Mode Select
          //
          Or(Local0, And(IMDS, 0x02), Local0)
          Return (Local0)
        }
      }
    
      /**
        SAOS - Set ISCT Function Status
        Input:   
        Bits   Description 
        - 0      ISCT Mode: 0 = Disabled, 1 = Enabled 
        - 1      ISCT Wake Mode Select: 0 = Normal ISCT Wake Mode, 1 = Extended ISCT Wake Mode
        - 2      Wake From S4: 0 = No Wake from S4, 1 = Wake from S4
        - 3 - 7  Reserved 
      **/
      Method (SAOS, 1, NotSerialized)
      {
        //
        // If Graphics Driver supports disable display notification in ISCT mode
        //
        If (And(\_SB.PCI0.GFX0.TCHE, 0x100))
        {
          //
          // Check for RTC Timer, else EC timer
          //
          If (LEqual(ITMR, 1))
          {
            //
          // If iSCT Mode and agent is disabling iSCT Mode and the iSCT Wake Reason indicates display off
            // Then notify graphics driver to turn on display
            //
          If (LAnd(LAnd(And(IBT1, 0x01), LNot(And(Arg0, 0x01))), And(\_SB.IAOE.WKRS, 0x10))) {
              If (LNot(\_SB.PCI0.GFX0.PARD()))
              {
                Store(And(\_SB.PCI0.GFX0.STAT, Not(0x03)), \_SB.PCI0.GFX0.STAT)          // STAT[1:0] = 00, Normal Resume to S0

                Store(Or(\_SB.PCI0.GFX0.ASLC, 0x100), \_SB.PCI0.GFX0.ASLC)               // ASLC[8] = 1, ISCT State Change Request

                Store(0x01, \_SB.PCI0.GFX0.ASLE)                                         // Generate ASLE interrupt
              }
            }
          } else {
            If(CondRefOf(\_SB.PCI0.LPCB.H_EC.IBT1)) {
              //
              // If ISCT Mode and Wake Reason was ISCT wake (EC Timer or Network PME) and agent is disabling ISCT Mode
              // Then notify graphics driver to turn on display
              //
              If (LAnd(LAnd(And(\_SB.PCI0.LPCB.H_EC.IBT1, 0x01), LOr(And(\_SB.IAOE.WKRS, 0x02), And(\_SB.IAOE.WKRS, 0x10))), LNot(And(Arg0, 0x01)))) {
                If (LNot(\_SB.PCI0.GFX0.PARD()))
                {
                  Store(And(\_SB.PCI0.GFX0.STAT, Not(0x03)), \_SB.PCI0.GFX0.STAT)          // STAT[1:0] = 00, Normal Resume to S0

                  Store(Or(\_SB.PCI0.GFX0.ASLC, 0x100), \_SB.PCI0.GFX0.ASLC)               // ASLC[8] = 1, ISCT State Change Request

                  Store(0x01, \_SB.PCI0.GFX0.ASLE)                                         // Generate ASLE interrupt
                }
              }
            }
          }
        }

        //
        // Check for RTC Timer, else EC timer
        //
        If (LEqual(ITMR, 1))
        {
          //
        // Set Isct Wake Mode Selection and Wake from S4
        //
        Store(And(Arg0, 0x06), IMDS)
          /// @note: Low Power Fan control for Extended Wake
        //
        // Set Isct Mode Enable
        //
        Or(And(IBT1, 0xFE), And(Arg0, 0x01), IBT1)
        }
        Else
        {
          //
          //Set Isct Mode Enable
          //
          If (CondRefOf(\_SB.PCI0.LPCB.H_EC.IBT1))
          {
            Store(\_SB.PCI0.LPCB.H_EC.IBT1, Local0)
          }
          Else
          {	
            Store(IBT1, Local0)
          }
          And(Local0, 0xFE, Local0)
          Or(Local0, And(Arg0, 0x01), Local0)
          //
          // Set Isct Wake Mode Select
          //
          Store(And(Arg0, 0x02), IMDS)
            //TBD: Low Power Fan control
          If (CondRefOf(\_SB.PCI0.LPCB.H_EC.IBT1))
          {
            Store(Local0, \_SB.PCI0.LPCB.H_EC.IBT1)
            //Send EC IsctUpdateCommand - 0x2B
            \_SB.PCI0.LPCB.H_EC.ECMD (0x2B)
          }
          Else
          {	
            Store(Local0, IBT1)
          }
        }
      }

      //
      // GANS - Get ISCT Notification Status
      // Input:   None
      // Return:
      // Bits   Description
      // 0      ISCT Notification : 0 = Disabled, 1 = Enabled
      // 1 - 7  Reserved
      //
      Method (GANS, 0, NotSerialized)
      {
        Return (INSB)
      }

      //
      // SANS - Set ISCT Notification Status
      // Input:
      // Bits   Description
      // 0      ISCT Notification : 0 = Disabled, 1 = Enabled
      // 1 - 7  Reserved
      //
      Method (SANS, 1, NotSerialized)
      {
        Store(And(Arg0, 0x01), INSB)
      }

      //
      // GWLS - Get WLAN Module Status
      // Input:   None
      // Return:
      // Bits   Description
      // 0      Reserved(set to 0)
      // 1      WLAN Module Powered in S3: 0 = Disabled, 1 = Enabled
      // 2      WLAN Module Powered in S4: 0 = Disabled, 1 = Enabled
      // 3      WLAN Module Powered in S5: 0 = Disabled, 1 = Enabled
      // 4 - 7  Reserved
      //
      Method (GWLS, 0, NotSerialized)
      {
        If(LEqual(And(ICNF, 0x04), Zero))
        {
          Return (Zero)
        }
        //
        // Check for RTC Timer, else EC timer
        //
        If (LEqual(ITMR, 1))
        {
	  Store(One, Local0)
	  Store(IBT1, Local1)
	  Or(Local0, And(Local1, 0x0E), Local0)
          Return (Local0)
        }
        Else
        {
          //
          // Set WLAN Wireless Disable Bit to 1 if EC
          //
          If (CondRefOf(\_SB.PCI0.LPCB.H_EC.IBT2))
          {
            Store(\_SB.PCI0.LPCB.H_EC.IBT2, Local0)
            Or(Local0, 1, Local0)
          }

          //
          // Get WLAN Powered States
          //
          If (CondRefOf(\_SB.PCI0.LPCB.H_EC.IBT1))
          {
            Store(\_SB.PCI0.LPCB.H_EC.IBT1, Local1)
          }
          Else
          {
            Store(IBT1, Local1)
          }
          Or(Local0, And(Local1, 0x0E), Local0)

          Return (Local0)
        }
      }
      //
      // SWLS - Set WLAN Module Status
      // Input:
      // Bits   Description
      // 0      N/A (WLAN Wireless Disable is Read only)  Always set to 0
      // 1      WLAN Module Powered in S3: 0 = Disabled, 1 = Enabled
      // 2      WLAN Module Powered in S4: 0 = Disabled, 1 = Enabled
      // 3      WLAN Module Powered in S5: 0 = Disabled, 1 = Enabled
      // 4 - 7  Reserved
      //
      Method (SWLS, 1, NotSerialized)
      {
        If(LEqual(And(ICNF, 0x04), Zero))
        {
          Return
        }      
        //
        // Check for RTC Timer, else EC timer
        //
        If (LEqual(ITMR, 1))
        {
          Store(IBT1, Local0)

          //
          // Set new Power States
          //
          And(Local0, 0xF1, Local0)
          Or(Local0, And(Arg0, 0x0E), Local0)
          If(CondRefOf(\_SB.IFFS.FFSS))
          {
            If(LAnd(And(\_SB.IFFS.FFSS, 0x03), And(Arg0,0x02)))
            {
              Or(Local0, 0x04, Local0)
            }
          }
          Store(Local0, IBT1)
        }
        Else
        {
          //
          // Read ISCTByte1 from EC
          //
          If (CondRefOf(\_SB.PCI0.LPCB.H_EC.IBT1))
          {
            Store(\_SB.PCI0.LPCB.H_EC.IBT1, Local0)
          }
          Else
          {
            Store(IBT1, Local0)
          }

          //
          // Set new Power States
          //
          And(Local0, 0xF1, Local0)
          Or(Local0, And(Arg0, 0x0E), Local0)

          //
          // If RapidStart is enabled and WLAN powered in S3, enable power in S4
          //
          If(CondRefOf(\_SB.IFFS.FFSS))
          {
            If(LAnd(And(\_SB.IFFS.FFSS, 0x03), And(Arg0,0x02)))
            {
              Or(Local0, 0x04, Local0)
            }
          }

          //
          // Save ISCTByte1 to EC
          //
          If (CondRefOf(\_SB.PCI0.LPCB.H_EC.IBT1))
          {
            Store(Local0, \_SB.PCI0.LPCB.H_EC.IBT1)
            //Send EC IsctUpdateCommand - 0x2B
            \_SB.PCI0.LPCB.H_EC.ECMD (0x2B)
          }
          Else
          {
            Store(Local0, IBT1)
          }
        }
      }

      //
      // GWWS - Get WWAN Module Status
      // Input:   None
      // Return:
      // Bits   Description
      // 0      WWAN Wireless Disable (W_DISABLE#) :0 = Disabled, 1 = Enabled
      // 1      WWAN Module Powered in S3: 0 = Disabled, 1 = Enabled
      // 2      WWAN Module Powered in S4: 0 = Disabled, 1 = Enabled
      // 3      WWAN Module Powered in S5: 0 = Disabled, 1 = Enabled
      // 4 - 7  Reserved
      //
      Method (GWWS, 0, NotSerialized)
      {
        If(LEqual(And(ICNF, 0x08), Zero))
        {
          Return (Zero)
        }
        //
        // Check for RTC Timer, else EC timer
        //
        If (LEqual(ITMR, 1))
        {
          Store(One, Local0)
	  Store(IBT1, Local1)
	  Or(Local0, ShiftRight(And(Local1, 0x70), 3), Local0)
	  Return (Local0)
        }
        Else
        {
          //
          // Set WWAN Wireless Disable Bit to 1 if EC
          //
          If (CondRefOf(\_SB.PCI0.LPCB.H_EC.IBT2))
          {
            Store(\_SB.PCI0.LPCB.H_EC.IBT2, Local0)
            ShiftRight(Or(Local0, 2), 1, Local0)
          }

          //
          // Get WWAN Powered States
          //
          If (CondRefOf(\_SB.PCI0.LPCB.H_EC.IBT1))
          {
            Store(\_SB.PCI0.LPCB.H_EC.IBT1, Local1)
          }
          Else
          {
            Store(IBT1, Local1)
          }
          Or(Local0, ShiftRight(And(Local1, 0x70), 3), Local0)

          Return (Local0)
        }
      }

      //
      // SWWS - Set WWAN Module Status
      // Input:
      // Bits   Description
      // 0      N/A (WWAN Wireless Disable is Read only)  Always set to 0
      // 1      WWAN Module Powered in S3: 0 = Disabled, 1 = Enabled
      // 2      WWAN Module Powered in S4: 0 = Disabled, 1 = Enabled
      // 3      WWAN Module Powered in S5: 0 = Disabled, 1 = Enabled
      // 4 - 7  Reserved
      //
      Method (SWWS, 1, NotSerialized)
      {
        If(LEqual(And(ICNF, 0x08), Zero))
        {
          Return
        }      
        //
        // Check for RTC Timer, else EC timer
        //
        If (LEqual(ITMR, 1))
        {
	  Store(IBT1, Local0)
          //
          // Set new Power States
          //
          And(Local0, 0x8F, Local0)
          Or(Local0, ShiftLeft(And(Arg0, 0x0E), 3), Local0)
	  
          //
          // If RapidStart is enabled and WWAN powered in S3, enable power in S4
          //
          If(CondRefOf(\_SB.IFFS.FFSS))
          {
            If(LAnd(And(\_SB.IFFS.FFSS, 0x03), And(Arg0,2)))
            {
               Or(Local0, ShiftLeft(0x04, 3), Local0)
            }
          }	  
	  Store(Local0, IBT1)
        }
        Else
        {
          //
          // Read ISCTByte1 from EC
          //
          If (CondRefOf(\_SB.PCI0.LPCB.H_EC.IBT1))
          {
            Store(\_SB.PCI0.LPCB.H_EC.IBT1, Local0)
          }
          Else
          {
            Store(IBT1, Local0)
          }

          //
          // Set new Power States
          //
          And(Local0, 0x8F, Local0)
          Or(Local0, ShiftLeft(And(Arg0, 0x0E), 3), Local0)

          //
          // If RapidStart is enabled and WWAN powered in S3, enable power in S4
          //
          If(CondRefOf(\_SB.IFFS.FFSS))
          {
            If(LAnd(And(\_SB.IFFS.FFSS, 0x03), And(Arg0,2)))
            {
               Or(Local0, ShiftLeft(0x04, 3), Local0)
            }
          }

          //
          // Save ISCTByte1 to EC
          //
          If (CondRefOf(\_SB.PCI0.LPCB.H_EC.IBT1))
          {
            Store(Local0, \_SB.PCI0.LPCB.H_EC.IBT1)
            //Send EC IsctUpdateCommand - 0x2B
            \_SB.PCI0.LPCB.H_EC.ECMD (0x2B)
          }
          Else
          {
            Store(Local0, IBT1)
          }
        }
      }

      //
      // SASD - Set Intel Smart Connect Technology Sleep Duration
      // Input:
      // Bits   Description
      // 0 - 30 Sleep Duration
      // 31  : 0 = Sleep Duration in seconds
      //       1 = Actual time
      //
      Method (SASD, 1, NotSerialized)
      {
        //
        // Arg0  =  0 - NetDetect support
        //       >  0 - EC / RTC Based Timer
        //       Bit31 : 0 - Sleep Duration in seconds
        //               1 - Actual Time
        //
        If(LAnd(And(ICNF, 0x10), LGreater(Arg0, 0)))
        {
          //
          // See if RTC (1) or EC (0) Timer
          //
          If (LEqual(ITMR, 1))
          {
            Store(Arg0, RCTM)
          }
          Else
          {
            Store(Arg0, ECTM)
          }

          If (LAnd(CondRefOf(\_SB.PCI0.LPCB.H_EC.WTMS), LEqual(PTSL, 0x03)))
          {
             Store(And(ECTM, 0xFF), \_SB.PCI0.LPCB.H_EC.AWT0)
             Store(ShiftRight(And(ECTM, 0xFF00), 8), \_SB.PCI0.LPCB.H_EC.AWT1)
             Store(ShiftRight(And(ECTM, 0xFF0000), 16), \_SB.PCI0.LPCB.H_EC.AWT2)
             //
             // Enable EC timer - BIT7
             // Enable wake from S3 on timer exiry - BIT0
             //
             Store(\_SB.PCI0.LPCB.H_EC.WTMS, Local0)
             Store(Or(0x81,Local0), \_SB.PCI0.LPCB.H_EC.WTMS)
          }
          Else
          {
             Store(And(ECTM, 0xFF), AWT0)
             Store(ShiftRight(And(ECTM, 0xFF00), 8), AWT1)
             Store(ShiftRight(And(ECTM, 0xFF0000), 16), AWT2)
             Store(WTMS, Local0)
             Store(Or(0x81,Local0), WTMS)
          }
        }
        Else
        {
          If (LEqual(ITMR, 1))
          {
            Store(0, RCTM)
          } else {
            If(CondRefOf(\_SB.PCI0.LPCB.H_EC.WTMS))
            {
              Store(0, ECTM)
              Store(0, \_SB.PCI0.LPCB.H_EC.WTMS)
            }
          }

          Store(Arg0, SLPD)
        }
      } // Method (SASD)

      //
      // GPWR - Get Wake Reason
      // Input:   None
      // Return:   
      // Bits   Description 
      // 0      User Pressed Power Button: 0 = False, 1 = True
      // 1      EC / RTC caused wake (requested by iSCT agent): 0 = False, 1 = True
      // 2      RTC Timer caused wake: 0 = False, 1 = True
      // 3      Wake due to PME (Not Network Wake): 0 = False, 1 = True
      // 4      Internal BIOS bit PME (Known Network Wake): 0 = False, 1 = True (Reserved for Agent- Must be 0)
      // 5 - 7  Reserved
      //
      Method (GPWR, 0, NotSerialized)
      {
        //
        // Return Wake Reason
        //
        If(And(WKRS,0x2F))
        {
          //
          // Mask out the Internal BIOS Network PME bit and the reserved bits.
          //
          Return(And(WKRS, 0x2F))
        }
        Else
        {
          Return(0)
        }
      } // Method (GPWR)

      //
      // GPCS - Get Platform Component State
      // Input: None
      // Return:
      // Bits   Description
      // 0      LID State: 0 - Closed, 1 - Open
      // 1 - 7  Reserved
      //
      Method (GPCS, 0, NotSerialized)
      {
        //
        // See if EC (0) or RTC (1) Timer
        //
        If (LEqual(ITMR, 0))
        {
          If (CondRefOf(\_SB.PCI0.LPCB.H_EC.LSTE))
          {
            Return(And(\_SB.PCI0.LPCB.H_EC.LSTE,0x01))
          }
        }
        Else
        {
          Return(1)
        }
      } // Method (GPCS)

      //
      // GAWD - Get Isct Wake Duration
      // Input: None
      // Return:
      // Bits   Description
      // 0 - 7  Isct Wake Duration
      //
      Method (GAWD, 0, NotSerialized)
      {
        Return (IWDT)
      }

      //
      // SAWD - Set Isct Wake Duration
      // Input:
      // Bits   Description
      // 0 - 7  Isct Wake Duration
      //
      Method (SAWD, 1, NotSerialized)
      {
        Store (Arg0, IWDT)
          //TBD Set EC Watchdog Timer
      }

    } // Device (IAOE)
  } // Scope (\_SB)
} // End SSDT

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

