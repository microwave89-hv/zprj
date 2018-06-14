// Set of generic ACPI Control Methods to configure SATA Controller and SATA Drives settings
// File is included under SATA controller PCI device scope
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
// $Header: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Chipset/SB/SATA.ASL 1     6/17/16 4:05a Chienhsieh $
//
// $Revision: 1 $
//
// $Date: 6/17/16 4:05a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Chipset/SB/SATA.ASL $
// 
// 1     6/17/16 4:05a Chienhsieh
// [TAG]  		EIP255383
// [Category]  	Improvement
// [Description]  	when the FORCE_HDD_PASSWORD_PROMPT sdl token enabled ,
// even though use select s4 option, on resume system booted like S5. 
// set HDD password and enter Win8 S4(Hibernate) sleep, behaviour of S4
// resume would be like restart.
// [Files]  		SATA.ASL
// 
// 2     10/23/12 3:19a Scottyang
// [TAG]      EIP84560
// [Category] Bug Fix
// [Symptom]  Can't enter Win8 after Win8 AHCI driver version:11.5.0.1122
// install.
// [Solution] fixed in EIP84560
// [Files]    sb.sdl, sb.mak, sata.asl
// 
// 1     2/08/12 8:25a Yurenlai
// Intel Lynx Point/SB eChipset initially releases.
// 
//*************************************************************************

DefinitionBlock (
    "Sata.aml",
    "SSDT",
    1,
    "SataRef",
    "SataTabl",
    0x1000
        )
{

External(DSSP, IntObj)
External(\_SB.PCI0.SAT0, DeviceObj)

Scope(\)
{
    // SATA Command Set
    //---------------------------------------------------------------//
    //                    Reg1  Reg2  Reg3  Reg4  Reg5  Reg6  Reg7
    //---------------------------------------------------------------//
    Name(STFE, Buffer(){0x10, 0x06, 0x00, 0x00, 0x00, 0x00, 0xEF,})     // Set Features - Enable USE of SATA Feature
    Name(STFD, Buffer(){0x90, 0x06, 0x00, 0x00, 0x00, 0x00, 0xEF,})     // Set Features - Disable USE of SATA Feature
    Name(FZTF, Buffer(){0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF5 })     // Freeze Lock Command
    Name(DCFL, Buffer(){0xC1, 0x00, 0x00, 0x00, 0x00, 0x00, 0xB1 })     // Device Configuration Freeze Lock Command

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

      Or(CHNF, 0x05, CHNF)

      Return (TMD0)
    }                    // end Method _GTM
////////////////////////////////////////////////////////////////////////////////
    // Set Timing PIO/DMA Mode
    Method(_STM, 3)      // Arg 0 = Channel Timing Info (Package)
                         // Arg 1 = ATA Command set Master(Buffer)
                         // Arg 2 = ATA Command set Slave (Buffer)
    {}                   // end Method _STM
////////////////////////////////////////////////////////////////////////////////
#if defined(ASL_ZPODD_SATA_PORT) && (ASL_ZPODD_SATA_PORT==0)
#else
    // SATA PORT0 //
    Device(SPT0)
    {
        Name(_ADR,0x0000FFFF)

        // GET TASK FILE METHOD
        Method(_GTF, 0, NotSerialized) {
            Store(0, CMDC)                                      // SATA Commands counter

            If(LEqual(DSSP, 0x1)) {                             // Check DISABLE_SOFT_SET_PREV SDL Token Enabled
                GTFB(STFD, 0x06)                                // Disable SW Preservation Settings
            } else {
                GTFB(STFE, 0x06)                                // Enable SW Preservation Settings
            }

            GTFB(FZTF, 0x00)                                    // Issue Freeze Lock Command
            GTFB(DCFL, 0x00)                                    // Issue Device Configuration Freeze Lock Command
            Return(SCBF)
        }
    }

#endif
    // SATA PORT1 //
#if defined(ASL_ZPODD_SATA_PORT) && (ASL_ZPODD_SATA_PORT==1)
#else
    Device(SPT1)
    {
        Name(_ADR,0x0001FFFF)

        // GET TASK FILE METHOD
        Method(_GTF, 0, NotSerialized) {
            Store(0, CMDC)                                      // SATA Commands counter

           If(LEqual(DSSP, 0x1)) {                              // Check DISABLE_SOFT_SET_PREV SDL Token Enabled
                GTFB(STFD, 0x06)                                // Disable SW Preservation Settings
            } else {
                GTFB(STFE, 0x06)                                // Enable SW Preservation Settings
            }

            GTFB(FZTF, 0x00)                                    // Issue Freeze Lock Command
            GTFB(DCFL, 0x00)                                    // Issue Device Configuration Freeze Lock Command
            Return(SCBF)
        }
    }

#endif
    // SATA PORT2 //
#if defined(ASL_ZPODD_SATA_PORT) && (ASL_ZPODD_SATA_PORT==2)
#else
    Device(SPT2)
    {
        Name(_ADR,0x0002FFFF)

        // GET TASK FILE METHOD
        Method(_GTF, 0, NotSerialized) {
            Store(0, CMDC)                                      // SATA Commands counter

           If(LEqual(DSSP, 0x1)) {                              // Check DISABLE_SOFT_SET_PREV SDL Token Enabled
                GTFB(STFD, 0x06)                                // Disable SW Preservation Settings
            } else {
                GTFB(STFE, 0x06)                                // Enable SW Preservation Settings
            }

            GTFB(FZTF, 0x00)                                    // Issue Freeze Lock Command
            GTFB(DCFL, 0x00)                                    // Issue Device Configuration Freeze Lock Command
            Return(SCBF)
        }
    }

#endif
    // SATA PORT3 //
#if defined(ASL_ZPODD_SATA_PORT) && (ASL_ZPODD_SATA_PORT==3)
#else
    Device(SPT3)
    {
        Name(_ADR,0x0003FFFF)

        // GET TASK FILE METHOD
        Method(_GTF, 0, NotSerialized) {
            Store(0, CMDC)                                      // SATA Commands counter

           If(LEqual(DSSP, 0x1)) {                              // Check DISABLE_SOFT_SET_PREV SDL Token Enabled
                GTFB(STFD, 0x06)                                // Disable SW Preservation Settings
            } else {
                GTFB(STFE, 0x06)                                // Enable SW Preservation Settings
            }

            GTFB(FZTF, 0x00)                                    // Issue Freeze Lock Command
            GTFB(DCFL, 0x00)                                    // Issue Device Configuration Freeze Lock Command
            Return(SCBF)
        }
    }

#endif
    // SATA PORT4 //
#if defined(ASL_ZPODD_SATA_PORT) && (ASL_ZPODD_SATA_PORT==4)
#else
    Device(SPT4)
    {
        Name(_ADR,0x0004FFFF)

        // GET TASK FILE METHOD
        Method(_GTF, 0, NotSerialized) {
            Store(0, CMDC)                                      // SATA Commands counter

           If(LEqual(DSSP, 0x1)) {                              // Check DISABLE_SOFT_SET_PREV SDL Token Enabled
                GTFB(STFD, 0x06)                                // Disable SW Preservation Settings
            } else {
                GTFB(STFE, 0x06)                                // Enable SW Preservation Settings
            }

            GTFB(FZTF, 0x00)                                    // Issue Freeze Lock Command
            GTFB(DCFL, 0x00)                                    // Issue Device Configuration Freeze Lock Command
            Return(SCBF)
        }
    }

#endif
    // SATA PORT5 //
#if defined(ASL_ZPODD_SATA_PORT) && (ASL_ZPODD_SATA_PORT==5)
#else
    Device(SPT5)
    {
        Name(_ADR,0x0005FFFF)

        // GET TASK FILE METHOD
        Method(_GTF, 0, NotSerialized) {
            Store(0, CMDC)                                      // SATA Commands counter

           If(LEqual(DSSP, 0x1)) {                              // Check DISABLE_SOFT_SET_PREV SDL Token Enabled
                GTFB(STFD, 0x06)                                // Disable SW Preservation Settings
            } else {
                GTFB(STFE, 0x06)                                // Enable SW Preservation Settings
            }

            GTFB(FZTF, 0x00)                                    // Issue Freeze Lock Command
            GTFB(DCFL, 0x00)                                    // Issue Device Configuration Freeze Lock Command
            Return(SCBF)
        }
    }
#endif
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