//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

//*************************************************************************
// $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/IDE.ASL 2     10/12/12 1:28a Scottyang $
//
// $Revision: 2 $
//
// $Date: 10/12/12 1:28a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/IDE.ASL $
// 
// 2     10/12/12 1:28a Scottyang
// [TAG]  		EIP83353
// [Category]  	Improvement
// [Description]  	Correct IDE Mode SATA2 Ch1 Master timing.
// [Files]  		IDE.asl
// 
// 1     2/08/12 8:25a Yurenlai
// Intel Lynx Point/SB eChipset initially releases.
// 
//*************************************************************************

DefinitionBlock (
    "Ide.aml",
    "SSDT",
    1,
    "IdeRef",
    "IdeTable",
    0x1000
        )
{

External(DSSP, IntObj)
External(FHPP, IntObj)
External(\_SB.PCI0.SAT0, DeviceObj)
External(\_SB.PCI0.SAT1, DeviceObj)

Scope(\)
{
    // SATA Command Set
    //---------------------------------------------------------------//
    //                    Reg1  Reg2  Reg3  Reg4  Reg5  Reg6  Reg7
    //---------------------------------------------------------------//
    Name(STFE, Buffer(){0x10, 0x06, 0x00, 0x00, 0x00, 0x00, 0xEF,})  // Set Features - Enable USE of SATA Feature
    Name(STFD, Buffer(){0x90, 0x06, 0x00, 0x00, 0x00, 0x00, 0xEF,})  // Set Features - Disable USE of SATA Feature
    Name(FZTF, Buffer(){0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF5 })  // Freeze Lock Command
    Name(DCFL, Buffer(){0xC1, 0x00, 0x00, 0x00, 0x00, 0x00, 0xB1 })  // Device Configuration Freeze Lock Command

    Name(SCBF, Buffer(21){})                                    // SATA Command Buffer to be returned

    // The number of SATA command
    Name (CMDC, 0)                                              // SATA Commands counter

    // Build the return buffer for GTF() control method
    Method (GTFB, 2, Serialized)
    //      Arg0 - Command to write
    //      Arg1 - Subcommand value for "Set Feature command"
    {
        Multiply(CMDC, 56, Local0)
        CreateField(SCBF, Local0, 56, CMDx)                     // Command field
        Multiply(CMDC, 7, Local0)
        CreateByteField(SCBF, Add(Local0, 1), A001)             // Subcommand of "Set Feature" command
        Store(Arg0, CMDx)                                       // Store command into return buffer
        Store(Arg1, A001)                                       // Set Subcommand code
        Increment(CMDC)
    }
}

Scope(\_SB.PCI0.SAT0)
{
    Name(REGF, 1)               // PCI Bus access Flag

    Method(_REG, 2)             // is PCI Config space accessible as OpRegion?
                                // _REG to update REGF status
    {
      If(LEqual(Arg0, 0x2))
      {
         Store(Arg1, REGF)
      }
    }
    // Buffer to be returned by _GTM
    Name(TMD0, Buffer(20){})            // 5 DWORD length
    CreateDWordField(TMD0, 00, PIO0)
    CreateDWordField(TMD0, 04, DMA0)
    CreateDWordField(TMD0, 8,  PIO1)    // do not use "08"
    CreateDWordField(TMD0, 12, DMA1)
    CreateDWordField(TMD0, 16, CHNF)
    Device(CHN0)
    {
        Name(_ADR,0x00)
        // Get Timing PIO/DMA Mode
        Method(_GTM,0 ) {    // Return Buffer
                             // PIO 0 Speed DWORD
                             // DMA 0 Speed DWORD
                             // PIO 1 Speed DWORD
                             // DMA 1 Speed DWORD
                             // Flags DWORD

          Store(120,  PIO0)  // Forced to PIO Mode 4
          Store(20,   DMA0)  // Forced to UDMA Mode 5
          Store(120,  PIO1)  // Forced to PIO Mode 4
          Store(20,   DMA1)  // Forced to UDMA Mode 5
          Store(0x05, CHNF)
          Return (TMD0)
        }                    // end Method _GTM
////////////////////////////////////////////////////////////////////////////////
        // Set Timing PIO/DMA Mode
        Method(_STM, 3)      // Arg 0 = Channel Timing Info (Package)
                             // Arg 1 = ATA Command set Master(Buffer)
                             // Arg 2 = ATA Command set Slave (Buffer)
        { }                  // end Method _STM
////////////////////////////////////////////////////////////////////////////////

        Device(DRV0)
        {
            Name(_ADR,0x00)

            // GET TASK FILE METHOD
            Method(_GTF, 0, NotSerialized) {
                Store(0, CMDC)          // SATA Commands counter
                If(LOr(DSSP, FHPP)) {   // Check DISABLE_SOFT_SET_PREV SDL Token Enabled
                                        // or FORCE_HDD_PASSWORD_PROMPT SDL Token Enabled
                    GTFB(STFD, 0x06)    // Disable SW Preservation Settings
                } else {
                    GTFB(STFE, 0x06)    // Enable SW Preservation Settings
                }

                GTFB(DCFL, 0x00)        // Issue Device Configuration Freeze Lock Command
                GTFB(FZTF, 0x00)        // Issue Freeze Lock Command
                Return(SCBF)
            }
        }

        Device(DRV1)
        {
            Name(_ADR,0x01)

            // GET TASK FILE METHOD
            Method(_GTF, 0, NotSerialized) {
                Store(0, CMDC)          // SATA Commands counter

                If(LOr(DSSP, FHPP)) {   // Check DISABLE_SOFT_SET_PREV SDL Token Enabled
                                        // or FORCE_HDD_PASSWORD_PROMPT SDL Token Enabled
                    GTFB(STFD, 0x06)    // Disable SW Preservation Settings
                } else {
                    GTFB(STFE, 0x06)    // Enable SW Preservation Settings
                }

                GTFB(DCFL, 0x00)        // Issue Device Configuration Freeze Lock Command
                GTFB(FZTF, 0x00)        // Issue Freeze Lock Command
                Return(SCBF)
            }
        }
    }

    Device(CHN1)
    {
        Name(_ADR,0x01)

////////////////////////////////////////////////////////////////////////////////
        // Get Timing PIO/DMA Mode
        Method(_GTM,0 ) {   // Return Buffer
                            // PIO 0 Speed DWORD
                            // DMA 0 Speed DWORD
                            // PIO 1 Speed DWORD
                            // DMA 1 Speed DWORD
                            // Flags DWORD

          Store(120,  PIO0) // Forced to PIO Mode 4
          Store(20,   DMA0) // Forced to UDMA Mode 5
          Store(120,  PIO1) // Forced to PIO Mode 4
          Store(20,   DMA1) // Forced to UDMA Mode 5
          Store(0x05, CHNF)

          Return (TMD0)
        }                   // end Method _GTM
////////////////////////////////////////////////////////////////////////////////
        // Set Timing PIO/DMA Mode
        Method(_STM, 3)     // Arg 0 = Channel Timing Info (Package)
                            // Arg 1 = ATA Command set Master(Buffer)
                            // Arg 2 = ATA Command set Slave (Buffer)
        { }                 // end Method _STM
////////////////////////////////////////////////////////////////////////////////

        Device(DRV0)
        {
            Name(_ADR,0x00)

            // GET TASK FILE METHOD
            Method(_GTF, 0, NotSerialized) {
                Store(0, CMDC)          // SATA Commands counter

                If(LOr(DSSP, FHPP)) {   // Check DISABLE_SOFT_SET_PREV SDL Token Enabled
                                        // or FORCE_HDD_PASSWORD_PROMPT SDL Token Enabled
                    GTFB(STFD, 0x06)    // Disable SW Preservation Settings
                } else {
                    GTFB(STFE, 0x06)    // Enable SW Preservation Settings
                }

                GTFB(DCFL, 0x00)        // Issue Device Configuration Freeze Lock Command
                GTFB(FZTF, 0x00)        // Issue Freeze Lock Command
                Return(SCBF)
            }
        }

        Device(DRV1)
        {
            Name(_ADR,0x01)

            // GET TASK FILE METHOD
            Method(_GTF, 0, NotSerialized) {
                Store(0, CMDC)          // SATA Commands counter

                If(LOr(DSSP, FHPP)) {   // Check DISABLE_SOFT_SET_PREV SDL Token Enabled
                                        // or FORCE_HDD_PASSWORD_PROMPT SDL Token Enabled
                    GTFB(STFD, 0x06)    // Disable SW Preservation Settings
                } else {
                    GTFB(STFE, 0x06)    // Enable SW Preservation Settings
                }

                GTFB(DCFL, 0x00)        // Issue Device Configuration Freeze Lock Command
                GTFB(FZTF, 0x00)        // Issue Freeze Lock Command
                Return(SCBF)
            }
        }
    }
}

Scope(\_SB.PCI0.SAT1)
{
    Name(REGF, 1)		// PCI Bus access Flag

    Method(_REG, 2)		// is PCI Config space accessible as OpRegion?
                                // _REG to update REGF status
    {
      If(LEqual(Arg0, 0x2))
      {
        Store(Arg1, REGF)
      }
    }

    // Buffer to be returned by _GTM
    Name(TMD0, Buffer(20){})            // 5 DWORD length
    CreateDWordField(TMD0, 00, PIO0)
    CreateDWordField(TMD0, 04, DMA0)
    CreateDWordField(TMD0, 8,  PIO1)    // do not use "08"
    CreateDWordField(TMD0, 12, DMA1)
    CreateDWordField(TMD0, 16, CHNF)

    Device(CHN0)
    {
        Name(_ADR,0x00)

////////////////////////////////////////////////////////////////////////////////
        // Get Timing PIO/DMA Mode
        Method(_GTM,0 ) {    // Return Buffer
                             // PIO 0 Speed DWORD
                             // DMA 0 Speed DWORD
                             // PIO 1 Speed DWORD
                             // DMA 1 Speed DWORD
                             // Flags DWORD

          Store(120,  PIO0)  // Forced to PIO Mode 4
          Store(20,   DMA0)  // Forced to UDMA Mode 5
          Store(120,  PIO1)  // Forced to PIO Mode 4
          Store(20,   DMA1)  // Forced to UDMA Mode 5
          Store(0x01, CHNF)

          Return (TMD0)
        }                    // end Method _GTM
////////////////////////////////////////////////////////////////////////////////
        // Set Timing PIO/DMA Mode
        Method(_STM, 3)      // Arg 0 = Channel Timing Info (Package)
                             // Arg 1 = ATA Command set Master(Buffer)
                             // Arg 2 = ATA Command set Slave (Buffer)
        { }                  // end Method _STM
////////////////////////////////////////////////////////////////////////////////

        Device(DRV0)
        {
            Name(_ADR,0x00)

            // GET TASK FILE METHOD
            Method(_GTF, 0, NotSerialized) {
                Store(0, CMDC)          // SATA Commands counter

                If(LOr(DSSP, FHPP)) {   // Check DISABLE_SOFT_SET_PREV SDL Token Enabled
                                        // or FORCE_HDD_PASSWORD_PROMPT SDL Token Enabled
                    GTFB(STFD, 0x06)    // Disable SW Preservation Settings
                } else {
                    GTFB(STFE, 0x06)    // Enable SW Preservation Settings
                }

                GTFB(DCFL, 0x00)        // Issue Device Configuration Freeze Lock Command
                GTFB(FZTF, 0x00)        // Issue Freeze Lock Command
                Return(SCBF)
            }
        }
    }

    Device(CHN1)
    {
        Name(_ADR,0x01)

////////////////////////////////////////////////////////////////////////////////
        // Get Timing PIO/DMA Mode
        Method(_GTM,0 ) {   // Return Buffer
                            // PIO 0 Speed DWORD
                            // DMA 0 Speed DWORD
                            // PIO 1 Speed DWORD
                            // DMA 1 Speed DWORD
                            // Flags DWORD

          Store(120,  PIO0) // Forced to PIO Mode 4
          Store(20,   DMA0) // Forced to UDMA Mode 5
          Store(120,  PIO1) // Forced to PIO Mode 4
          Store(20,   DMA1) // Forced to UDMA Mode 5
          Store(0x01, CHNF)

          Return (TMD0)
        }                   // end Method _GTM
////////////////////////////////////////////////////////////////////////////////
        // Set Timing PIO/DMA Mode
        Method(_STM, 3)     // Arg 0 = Channel Timing Info (Package)
                            // Arg 1 = ATA Command set Master(Buffer)
                            // Arg 2 = ATA Command set Slave (Buffer)
        { }                 // end Method _STM
////////////////////////////////////////////////////////////////////////////////

        Device(DRV0)
        {
            Name(_ADR,0x01)

            // GET TASK FILE METHOD
            Method(_GTF, 0, NotSerialized) {
                Store(0, CMDC)          // SATA Commands counter

                If(LOr(DSSP, FHPP)) {   // Check DISABLE_SOFT_SET_PREV SDL Token Enabled
                                        // or FORCE_HDD_PASSWORD_PROMPT SDL Token Enabled
                    GTFB(STFD, 0x06)    // Disable SW Preservation Settings
                } else {
                    GTFB(STFE, 0x06)    // Enable SW Preservation Settings
                }

                GTFB(DCFL, 0x00)        // Issue Device Configuration Freeze Lock Command
                GTFB(FZTF, 0x00)        // Issue Freeze Lock Command
                Return(SCBF)
            }
        }
    }
}
}//end of SSDT

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************