// THIS FILE IS INCLUDED to South Bridge device scope
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
//
//*************************************************************************
// $Header: /Alaska/BIN/IO/Fintek/F81866/F81866.ASL 3     4/01/13 3:20a Elviscai $
//
// $Revision: 3 $
//
// $Date: 4/01/13 3:20a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/IO/Fintek/F81866/F81866.ASL $
// 
// 3     4/01/13 3:20a Elviscai
// [TAG]  		EIP115780
// [Category]  	Bug Fix
// [Symptom]  	Burn in test faile while dual IO using same idex/data port
// [RootCause]  	Method DSTA retrned before exit config mode.
// 
// 2     2/03/12 1:59a Elviscai
// Remove unused PME name block.
// 
// 1     7/20/11 4:22a Kasalinyi
// [Category]  	Improvement
// [Description]  	Initial Porting 
// [Files]  		F81866.CIF
// IO_F81866.SDL
// F81866.ASL
// F81866.MAK
// F81866.SD
// F81866.UNI
// F81866DXE.C
// F81866PEI.C
// F81866PeiDebugger.C
// F81866Setup.C
// F81866Setup.H
// History.txt
// F81866.chm
// 
// 4     3/21/11 9:41p Mikes
// seperate the core and oem job
// 
//*************************************************************************

//<AMI_FHDR_START>
//
// Name:  <F81866.ASL>
//
// Description: Define SIO Device for ACPI OS.
//
//<AMI_FHDR_END>
//*************************************************************************
//Scope(\_SB.PCI0.SBRG) {
//-----------------------------------------------------------------------
// SET OF COMMON DATA/CONTROL METHODS USED FOR ALL LDN BASED SIO DEVICES
//-----------------------------------------------------------------------
// LIST of objects defined in this file:
// SIO specific: SIOR - Device node (_HID=0c02, UID=SPIO), SIO index/DAta IO access & SIO GPIO address space if available
// SIO specific: DCAT - Table correspondence the LDNs to Device order in Routing Table.
// SIO specific: ENFG & EXFG - Control methods to Enter and Exit configuration mode. ENFG & EXFG correspondingly
// SIO specific: LPTM - current parralel port mode
// SIO specific: UHID - PnP ID for given Serial port
// SIO specific: SIOS - SIO Chipset specific code called from _PTS
// SIO specific: SIOW - SIO Chipset specific code called from _WAK
// SIO specific: SIOH - SIO event handler, to be called from correspondent _Lxx method
// SIO specific: PowerResources & _PR0 object to control Power management for FDC, LPT, UART1,2.
//
// Generic :OpRegion & common Fields to access SIO configuration space
// Generic :CGLD - Convert Device category to LDN
// Generic :DSTA - Get device status according to ACTR register in LD IO space
// Generic :DCNT - Enable/Disable Decoding of Device resources, Route/Release resources to LPC bus
// Generic :DCRS - Returns Byte stream of device's Current resources
// Generic :DSRS - Configures new Resources to be decoded by a Device
// Device node:Motherboard resources
// SIO index/DAta IO access & SIO GPIO address space if available
Device(SIO1) {
    Name(_HID, EISAID("PNP0C02"))       // System board resources device node ID
    Name(_UID,0x111)                    // Unique ID. First IO use 0x111, Second IO use 0x222 ...

    Name(CRS, ResourceTemplate(){
        IO(Decode16, 0, 0, 0, 0, IOI)   // Index/Data Io address
        IO(Decode16, 0, 0, 0, 0, IO1)   // GP IO space
        IO(Decode16, 0, 0, 0, 0, IO2)   // PME IO space
        IO(Decode16, 0, 0, 0, 0, IO3)   // HWM IO space
    }) // end CRS

    Method (_CRS, 0){
        // Reserve Super I/O Configuration Port
        // 0x0 to 0xF0 already reserved
        // 0x3F0 - 0x3F1 are reserved in FDC
        If(LAnd(LLess(SP1O, 0x3F0), LGreater(SP1O, 0x0F0))){
            CreateWordField(CRS, ^IOI._MIN, GPI0)
            CreateWordField(CRS, ^IOI._MAX, GPI1)
            CreateByteField(CRS, ^IOI._LEN, GPIL)
            Store(SP1O, GPI0)    //Index/Data Base address
            Store(SP1O, GPI1)
            Store(0x02, GPIL)    //IO range
        }

        // Reserve SIO GP IO space
        If(IO1B){
            CreateWordField(CRS, ^IO1._MIN, GP10)
            CreateWordField(CRS, ^IO1._MAX, GP11)
            CreateByteField(CRS, ^IO1._LEN, GPL1)
            Store(IO1B, GP10)    //GP IO base address
            Store(IO1B, GP11)
            Store(IO1L, GPL1)    //IO range
        }

        // Reserve SIO PME IO space
        If(IO2B){
            CreateWordField(CRS, ^IO2._MIN, GP20)
            CreateWordField(CRS, ^IO2._MAX, GP21)
            CreateByteField(CRS, ^IO2._LEN, GPL2)
            Store(IO2B, GP20)    //PME IO base address
            Store(IO2B, GP21)
            Store(IO2L, GPL2)    //IO range
        }
        
        // Reserve SIO HWM IO space
        If(IO3B){
            CreateWordField(CRS, ^IO3._MIN, GP30)
            CreateWordField(CRS, ^IO3._MAX, GP31)
            CreateByteField(CRS, ^IO3._LEN, GPL3)
            Store(IO3B, GP30)    //HWM IO base address
            Store(IO3B, GP31)
            Store(IO3L, GPL3)    //IO range
        }
        Return(CRS)
    }    //End _CRS

    //---------------------------------------------------------------------
    // Table correspondence the LDNs to Device order in Routing Table
    // Device type selection is achieved by picking the value from DCAT Package by Offset = LDN
    //----------------------------------------------------------------------
    // Elements in the package contain LDN numbers for each category of devices.
    // Default value 0xFF -> no device present.
    // Make sure number of elements not less or equal to largest LDN
    Name (DCAT, Package(0x15){
    // AMI_TODO: fill the table with the present LDN
    // LDN number, 0xFF if device not present
    // We keep category 0x00~0x0F as SIO_DEV_STATUS layout in GenericSio.h to Update IOST 
        0x10,    // 0x00 - Serial A (SP1)
        0x11,    //   01 - Serial B (SP2)
        0x03,    //   02 - LPT
        0x00,    //   03 - FDD
        0xFF,    //   04 - SB16 Audio
        0xFF,    //   05 - MIDI
        0xFF,    //   06 - MSS Audio
        0xFF,    //   07 - AdLib sound (FM synth)
        0xFF,    //   08 - Game port #1
        0xFF,    //   09 - Game port #2
        0x05,    //   0A - KBC 60 & 64
        0xFF,    //   0B - EC 62 & 66
        0xFF,    //   0C - Reserved 
        0xFF,    //   0D - Reserved
        0x05,    //   0E - PS/2 Mouse
        0xFF,    //   0F - Reserved
//----add your other device,if no,please cut and modify Package number----------//
        0xFF,    //   10 - CIR
        0x12,    //   11 - Serial C (SP3) 
        0x13,    //   12 - Serial D (SP4)
        0x14,    //   13 - Serial E (SP5)
        0x15,    //   14 - Serial F (SP6)
    })

    //---------------------------------------------------------------------
    // Mutex object to sincronize the access to Logical devices
    //---------------------------------------------------------------------
    Mutex(MUT0, 0)    

    //---------------------------------------------------------------------
    // Enter Config Mode, Select LDN
    // Arg0 : Logical Device number
    //---------------------------------------------------------------------
    Method(ENFG, 1) {
        Acquire(MUT0, 0xFFF)
        //AMI_TODO: enter config mode and Select LDN.
        Store(ENTK, INDX)
        Store(ENTK, INDX)
        Store(Arg0, LDN)    //Select LDN
    }

    //---------------------------------------------------------------------
    // Exit Config Mode
    //---------------------------------------------------------------------
    Method(EXFG, 0) {
        //AMI_TODO: exit config mode
        Store(EXTK, INDX)
        Release(MUT0)
    }

    //---------------------------------------------------------------------
    // Return current LPT mode : 0-plain LPT, non Zero-ECP mode
    // Arg0 : Device LDN
    //---------------------------------------------------------------------
    Method(LPTM, 1){
        ENFG(CGLD(Arg0))        //Enter Config Mode, Select LDN
        //AMI_TODO: if it's ECP mode .
        And(OPT0, 0x02, Local0) //ECP Mode?
        EXFG()                  //Exit Config Mode
        Return(Local0)
    }

    //---------------------------------------------------------------------
    // Return current UART mode PnP ID : 0-plain Serial port, non Zero-IrDa mode
    // Arg0 : Device Category #
    //---------------------------------------------------------------------
    Method(UHID, 1){
        //AMI_TODO: Return the correct HID base on UART mode (UART/IR)
        ENFG(CGLD(Arg0))                //Enter Config Mode, Select LDN
        And(OPT0, 0x10, Local0)         //Ir mode is active
        EXFG()                          //Exit Config Mode
        If (Local0) {                   //Get Uart mode : 0-Serial port, non-zero - IrDa
            Return(EISAID("PNP0510"))   //PnP Device ID IrDa
        }
        Else {
            Return(EISAID("PNP0501"))   //PnP Device ID 16550 Type
        }
    }

//-------------------------------------------------------------------------
// !!! BELOW ARE GENERIC SIO CONTROL METHODS. DO NOT REQUIRE MODIFICATIONS
//-------------------------------------------------------------------------

//<AMI_THDR_START>
//------------------------------------------------------------------------
// Name: IOID
//
// Type: OperationRegion
//
// Description:    Operation Region to point to SuperIO configuration space
//
// Notes: OpeRegion address is defined by 'SP1O' global name. 
//  'SPIO' is a field isnside AML_Exchange data area defined in SDL file.
//
// Referrals: BIOS, AMLDATA
//
//-------------------------------------------------------------------------
//<AMI_THDR_END>
    //---------------------------------------------------------------------
    //  Set of Field names to be used to access SIO configuration space.
    //---------------------------------------------------------------------
    OperationRegion(IOID,   // Name of Operation Region for SuperIO device
        SystemIO,           // Type of address space
        SP1O,               // Offset to start of region
        2)                  // Size of region in bytes
                            // End of Operation Region
    Field(IOID, ByteAcc, NoLock,Preserve){
        INDX, 8,            // Field named INDX is 8 bit wide
        DATA, 8             // Field DATA is 8 bit wide
    }

    //---------------------------------------------------------------------
    //  Set of Field names to be used to access SIO configuration space.
    //---------------------------------------------------------------------
    IndexField(INDX, DATA, ByteAcc, NoLock, Preserve){
        Offset(0x07),
        LDN, 8,         //Logical Device Number

        Offset(0x20),
        CR20, 8,   
        CR21, 8,  
        CR22, 8, 
        CR23, 8,  
        CR24, 8, 
        CR25, 8,
        CR26, 8, 
        CR27, 8, 
        CR28, 8, 
        CR29, 8, 
        CR2A, 8, 
        CR2B, 8, 
        CR2C, 8,  
        CR2D, 8,                
        Offset(0x30),
        ACTR, 8,        //Activate register
        Offset(0x60),
        IOAH, 8,        //Base I/O High addr
        IOAL, 8,        //Base I/O Low addr
        IOH2, 8,        //Base2 I/O High addr
        IOL2, 8,        //Base2 I/O Low addr
        Offset(0x70),
        INTR, 4,        //IRQ
        INTT, 4,        //IRQ type
        Offset(0x74),
        DMCH, 8,        //DMA channel
        Offset(0xE0),
        RGE0, 8,        //Option Register E0
        RGE1, 8,        //Option Register E1
        RGE2, 8,        //Option Register E2
        RGE3, 8,        //Option Register E3
        RGE4, 8,        //Option Register E4
        RGE5, 8,        //Option Register E5
        RGE6, 8,        //Option Register E6
        RGE7, 8,        //Option Register E7
        RGE8, 8,        //Option Register E8
        RGE9, 8,        //Option Register E9
        Offset(0xF0),
        OPT0, 8,        //Option register 0xF0
        OPT1, 8,        //Option register 0xF1
        OPT2, 8,        //Option register 0xF2
        OPT3, 8,        //Option register 0xF3
        OPT4, 8,        //Option register 0xF4
        OPT5, 8,        //Option register 0xF5
        OPT6, 8,        //Option register 0xF6
        OPT7, 8,        //Option register 0xF7
        OPT8, 8,        //Option register 0xF8
        OPT9, 8,        //Option register 0xF9
    }        //End of indexed field

//<AMI_PHDR_START>
//------------------------------------------------------------------------
// Procedure:    CGLD
// Description:  Convert Device Category to Device's LDN
// Input: Arg0 : Device category #
// Output: LDN
//-------------------------------------------------------------------------
//<AMI_PHDR_END>
    Method(CGLD, 1) {
        Return(DeRefOf(Index(DCAT, Arg0)))    // Return LDN
    }


//<AMI_PHDR_START>
//------------------------------------------------------------------------
// Procedure:    DSTA
// Description:  GET SIO DEVICE STATUS according to ACTR/IOST(category0x00~0x0F) return values
//               GET SIO DEVICE STATUS according to ACTR/IOAH+IOAL/IOH2+IOL2(category>0x0F)
// Input: Arg0 : Device category #
// Output: Device Status
//-------------------------------------------------------------------------
//<AMI_PHDR_END>
    Method(DSTA, 1) {

        ENFG(CGLD(Arg0))    //Enter Config Mode, Select LDN
        Store(ACTR, Local0)
        Or(ShiftLeft(IOAH, 8),IOAL,Local1)
        EXFG()                //Exit Config Mode

        If(LEqual(Local0, 0xFF)) {Return(0x0)}    //LDN's not decoded, Device not present.

        And(Local0, 1, Local0)        //Leave only "Activate" bit

        // IOST only have 16 bits,IOST is for category 0x00~0x0F device
        If(LLess(Arg0,0x10)) {Or(IOST, ShiftLeft(Local0, Arg0), IOST)}

        // Update IO device status in IOST according to the category#
        // Note. Once device is detected its status bit cannot be removed
        If(Local0){ 
            Return(0x0F)            // Device present & Active
        }    
        Else{
            If(LLess(Arg0,0x10)){//by IOST check
                // Check if IO device detected in Local0(IOST) bit mask
                If(And(ShiftLeft(1, Arg0), IOST)){ Return(0x0D)}  // Device Detected & Not Active 
                // IO bit not set in Local0: device is disabled during first 
                // _STA(GSTA) invocationor disabled in BIOS Setup.
                Else{ Return(0x00)}  // Device not present
            }
            Else{//by Base1 & Base2 check
//                Or(ShiftLeft(IOAH, 8),IOAL,Local0)
//                If(Local0) { Return(0x0D)}  // Device Detected & Not Active
//                Or(ShiftLeft(IOH2, 8),IOL2,Local0)    
//                If(Local0) { Return(0x0D)}  // Device Detected & Not Active
                If(Local1) { Return(0x0D)}  // Device Detected & Not Active
                Return(0x00) // Device not present
            }
        }               //Exit Config Mode
    } // End Of DSTA

//<AMI_PHDR_START>
//------------------------------------------------------------------------
// Procedure:    DCNT
// Description:  Enable/Disable Decoding of Device resources, Route/Release
//               I/O & DMA Resources From, To EIO/LPC Bus
// Input: Arg0 : Device catagory #
//        Arg1 : 0/1 Disable/Enable resource decoding
// Output:Nothing
//-------------------------------------------------------------------------
//<AMI_PHDR_END>
    Method(DCNT, 2) {

        ENFG(CGLD(Arg0))    //Enter Config Mode, Select LDN

        // Route/Release DMA channel from/to being ISA/PCI mode
        // Note. DMA channel 0 is currently not decoded, although it can be 
        // used on some of SIO chipsets.
        If(LAnd(LLess(DMCH,4), LNotEqual(And(DMCH, 3, Local1),0))){
            rDMA(Arg0, Arg1, Increment(Local1))
        }

        Store(Arg1, ACTR)           // Update Activate Register
        ShiftLeft(IOAH, 8, local1)  // Get IO Base address
        Or(IOAL, Local1, Local1)

        // Route/Release I/O resources from/to EIO/LPC Bus
        // Arg0      Device Category
        // Arg1      0/1 Disable/Enable resource decoding
        // Arg2      Port to Route/Release
        // Arg3      Port SIZE to Route 
//        RRIO(Arg0, Arg1, Local1, 0x08)

        EXFG()              // Exit Config Mode
    } // End DCNT

//<AMI_THDR_START>
//------------------------------------------------------------------------
// Name: CRS1,CRS2,CRS3
//
// Type: ResourceTemplate
//
// Description: Current Resources Buffer for Generic SIO devices
//
// Notes: Note. DMA channel 0 is currently decoded as reserved,
//        although, it can be used on some of SIO chipsets.
//        Add DMA0 to _PRS if it is used
//        Generic Resourse template for FDC, COMx, LPT and ECP Current Resource Settings
//        (to be initialized and returned by _CRS)
//-------------------------------------------------------------------------
//<AMI_THDR_END>

// CRS buffer with all kinds of resources
Name(CRS1, ResourceTemplate(){
    IO(Decode16, 0, 0, 1, 0, IO01)
    IRQNoFlags(IRQ1) {}
    DMA(Compatibility, NotBusMaster, Transfer8, DMA1) {}
})
CreateWordField(CRS1, IRQ1._INT, IRQM)    //IRQ mask 0x1
CreateByteField(CRS1, DMA1._DMA, DMAM)    //DMA 0x4
CreateWordField(CRS1, IO01._MIN, IO11)    //Range 1 Min Base Word 0x8
CreateWordField(CRS1, IO01._MAX, IO12)    //Range 1 Max Base Word 0xa
CreateByteField(CRS1, IO01._LEN, LEN1)    //Length 1 0xd

// Extended CRS buffer with 2 IO ranges
Name(CRS2, ResourceTemplate(){
    IO(Decode16, 0, 0, 1, 0, IO02)
    IO(Decode16, 0, 0, 1, 0, IO03)
    IRQNoFlags(IRQ2) {}
    DMA(Compatibility, NotBusMaster, Transfer8, DMA2) {}
})
CreateWordField(CRS2, IRQ2._INT, IRQE)    //IRQ mask 0x1
CreateByteField(CRS2, DMA2._DMA, DMAE)    //DMA 0x4
CreateWordField(CRS2, IO02._MIN, IO21)    //Range 1 Min Base Word 0x8
CreateWordField(CRS2, IO02._MAX, IO22)    //Range 1 Max Base Word 0xa
CreateByteField(CRS2, IO02._LEN, LEN2)    //Length 1 0xd
CreateWordField(CRS2, IO03._MIN, IO31)    //Range 2 Min Base Word 0x10
CreateWordField(CRS2, IO03._MAX, IO32)    //Range 2 Max Base Word 0x12
CreateByteField(CRS2, IO03._LEN, LEN3)    //Length 2 0x15

// CRS buffer without DMA resource
Name(CRS3, ResourceTemplate(){
    IO(Decode16, 0, 0, 1, 0, IO04)
    IRQ(Level,ActiveLow,Shared,IRQ3){}    
    DMA(Compatibility, NotBusMaster, Transfer8, DMA3) {}
})
CreateWordField(CRS3, IRQ3._INT, IRQT)    //IRQ mask 0x9
CreateByteField(CRS3, 0x0B,IRQS)         //IRQ Shared/Active-Low/Edge-Triggered/=0x19    0xB   
CreateByteField(CRS3, DMA3._DMA, DMAT)    //DMA 0x4
CreateWordField(CRS3, IO04._MIN, IO41)    //Range 1 Min Base Word 0x2
CreateWordField(CRS3, IO04._MAX, IO42)    //Range 1 Max Base Word 0x4
CreateByteField(CRS3, IO04._LEN, LEN4)    //Length 1 0x7

//<AMI_PHDR_START>
//------------------------------------------------------------------------
// Procedure:    DCRS
// Description:  Get FDC, LPT, ECP, UART, IRDA resources (_CRS)
//               Returns Byte stream of Current resources. May contain Resources such:
//               1 IRQ resource
//               1 DMA resource
//               1 IO Port
// Input: Arg0 : Device catagory #
//        Arg1 : Use/No-Use DMA
// Output:       _CRS Resource Buffer 
//-------------------------------------------------------------------------
//<AMI_PHDR_END>
    Method(DCRS, 2) {
        ENFG(CGLD(Arg0))            //Enter Config Mode, Select LDN

        // Write Current Settings into Buffer for 1st IO Descriptor
        ShiftLeft(IOAH, 8, IO11)    //Get IO Base MSB
        Or(IOAL, IO11, IO11)        //Get IO Base LSB
        Store(IO11, IO12)           //Set Max Base Word

        Store(0x08, LEN1)           //set length

        // Write Current Settings into IRQ descriptor
        If(INTR){
            ShiftLeft(1, INTR, IRQM)
        } 
        Else{
            Store(0, IRQM)          // No IRQ used
        }

        // Write Current Settings into DMA descriptor
        // Note. DMA channel 0 is currently decoded as reserved,
        // although, it can be used on some of SIO chipsets.
        //If(Or(LGreater(DMCH,3), LEqual(And(DMCH, 3, Local1),0))){
        If(LOr(LGreater(DMCH,3), LEqual(Arg1, 0))){
            Store(0, DMAM)          // No DMA
        } 
        Else{
            And(DMCH, 3, Local1)
            ShiftLeft(1, Local1, DMAM)
        }
        EXFG()                      //Exit Config Mode
        Return(CRS1)                //Return Current Resources
    }

//<AMI_PHDR_START>
//------------------------------------------------------------------------
// Procedure:    DCR2
// Description:  Get FDC, LPT, ECP, UART, IRDA resources (_CRS)
//               Returns Byte stream of Current resources. May contain Resources such:
//               1 IRQ resource
//               1 DMA resource
//               2 IO Port
// Input: Arg0 : Device catagory #
//        Arg1 : Use/No-Use DMA
// Output:      _CRS Resource Buffer 
//-------------------------------------------------------------------------
//<AMI_PHDR_END>
    Method(DCR2, 2) {
        ENFG(CGLD(Arg0))            //Enter Config Mode, Select LDN

        // Write Current Settings into Buffer for 1st IO Descriptor
        ShiftLeft(IOAH, 8, IO21)    //Get IO Base MSB
        Or(IOAL, IO21, IO21)        //Get IO Base LSB
        Store(IO21, IO22)           //Set Max Base Word
        Store(0x08, LEN2)

        // Write Current Settings into Buffer for 2nd IO Descriptor
        ShiftLeft(IOH2, 8, IO31)    //Get IO Base MSB
        Or(IOL2, IO31, IO31)        //Get IO Base LSB
        Store(IO31, IO32)           //Set Max Base Word
        Store(0x08, LEN3)

        // Write Current Settings into IRQ descriptor
        If(INTR){
            ShiftLeft(1, INTR, IRQE)
        } 
        Else{
            Store(0, IRQE)          // No IRQ used
        }

        // Write Current Settings into DMA descriptor
        // Note. DMA channel 0 is currently decoded as reserved,
        // although, it can be used on some of SIO chipsets.
        //If(Or(LGreater(DMCH,3), LEqual(And(DMCH, 3, Local1),0))){
        If(LOr(LGreater(DMCH,3), LEqual(Arg1, 0))){
            Store(0, DMAE)          // No DMA
        } Else {
            And(DMCH, 3, Local1)
            ShiftLeft(1, Local1, DMAE)
        }

        EXFG()                      //Exit Config Mode
        Return(CRS2)                //Return Current Resources
    }

//<AMI_PHDR_START>
//------------------------------------------------------------------------
// Procedure:    DCR3
// Description:  Get FDC, LPT, ECP, UART, IRDA resources (_CRS)
//               Returns Byte stream of Current resources. May contain Resources such:
//               1 IRQ resource
//               1 IO Port
// Input: Arg0 : Device catagory #
// Output:      _CRS Resource Buffer 
//-------------------------------------------------------------------------
//<AMI_PHDR_END>
    Method(DCR3, 2) {

        ENFG(CGLD(Arg0))            // Enter Config Mode, Select LDN

        // Write Current Settings into Buffer for 1st IO Descriptor
        ShiftLeft(IOAH, 8, IO41)    //Get IO Base MSB
        Or(IOAL, IO41, IO41)        //Get IO Base LSB
        Store(IO41, IO42)           //Get Max Base Word
        Store(0x08, LEN4)

        // Write Current Settings into IRQ descriptor
        If(INTR){
            ShiftLeft(1, INTR, IRQT)
//	    // Set IRQ Type:porting according IRTT
//        //AMI_TODO:
//        If(And(OPT0,0x01)){
//		If(And(OPT0,0x02)){
//			If(And(OPT6,0x08)){
//				Store(0x18, IRQS)	}	// IRQ Type: Reserved, set as Active-Low-Level-Triggered,Shared.
//			Else{
//				Store(0x11, IRQS)	}	// IRQ Type: Active-High-Edge-Triggered,Shared.
//			}
//		Else{
//			If(And(OPT6,0x08)){
//				Store(0x10, IRQS)	}	// IRQ Type: Active-High-Level-Triggered,Shared.
//			Else{
//				Store(0x18, IRQS)	}	// IRQ Type: Active-Low-Level-Triggered,Shared.
//			}
//        } Else {
//            Store(0x01, IRQS)          // IRQ Type: Active-High-Edge-Triggered,No-Shared(default)
//        }
//
//ray_override / Support F81866 COM3 ~ COM6 IRQ Sharing Mode Selection / Modified >>
//            Store(0x18, IRQS)
            If( And(OPT0,0x01) ) { // Shared
                If( And(OPT0,0x02) ) { // Edge
                    Store(0x19, IRQS)   // High, Edge, Share
                }
                Else { // Level
                    Store(0x18, IRQS)   // Low, Level, Share
                }
            }
            Else { // Non Shared
                If( And(OPT0,0x02) ) { // Edge
                    Store(0x01, IRQS)   // High, Edge, Non Share
                }
                Else { // Level
                    Store(0x08, IRQS)   // Low, Level, Non Share
                }
            }
//ray_override / Support F81866 COM3 ~ COM6 IRQ Sharing Mode Selection / Modified <<
        }Else{
            Store(0, IRQT)            // No IRQ used
        }
        // Write Current Settings into DMA descriptor
        // Note. DMA channel 0 is currently decoded as reserved,
        // although, it can be used on some of SIO chipsets.
        //If(Or(LGreater(DMCH,3), LEqual(And(DMCH, 3, Local1),0))){
        If(LOr(LGreater(DMCH,3), LEqual(Arg1, 0))){
            Store(0, DMAT)          // No DMA
        } Else {
            And(DMCH, 3, Local1)
            ShiftLeft(1, Local1, DMAT)
        }

        EXFG()                        // Exit Config Mode
        Return(CRS3)                  //Return Current Resources
    }

//<AMI_PHDR_START>
//------------------------------------------------------------------------
// Procedure:    DSRS
// Description:  Set FDC, LPT, ECP, UART, IRDA resources (_SRS)
//               Control method can be used for configuring devices with following resource order:
//               1 IRQ resource
//               1 DMA resource
//               1 IO Port
// Input: Arg0 : PnP Resource String to set
//        Arg1 : Device catagory #
// Output:       Nothing
//-------------------------------------------------------------------------
//<AMI_PHDR_END>
    Method(DSRS, 2) {
        If(And(LEqual(Arg1, 0x02),LPTM(Arg1) ) ) {        //LPT logical device? Extended LPT mode ?
                DSR2(Arg0, Arg1)
        } Else {
            //Set resource for other devices from CRS1, or just for Parallel Port LPT Mode
            CreateWordField(Arg0, ^IRQ1._INT, IRQM)    //IRQ mask 0x1
            CreateByteField(Arg0, ^DMA1._DMA, DMAM)    //DMA 0x4
            CreateWordField(Arg0, ^IO01._MIN, IO11)    //Range 1 Min Base Word 0x8
    
            ENFG(CGLD(Arg1))            //Enter Config Mode, Select LDN
    
            // Set Base IO Address
            And(IO11, 0xFF, IOAL)       //Set IO Base LSB
            ShiftRight(IO11, 0x8, IOAH) //Set IO Base MSB
    
            // Set IRQ
            If(IRQM){
                FindSetRightBit(IRQM, Local0)
                Subtract(Local0, 1, INTR)
            }Else{
                Store(0, INTR)          //No IRQ used
            }
    
            // Set DMA
            If(DMAM){
                FindSetRightBit(DMAM, Local0)
                Subtract(Local0, 1, DMCH)
            }Else{
                Store(4, DMCH)          //No DMA
            }
    
            EXFG()                      //Exit Config Mode
    
            // Enable ACTR
            DCNT(Arg1, 1)               //Enable Device (Routing)
    
            Store(Arg1, Local2)
            If (LGreater(Local2, 0)){Subtract(Local2, 1, Local2)}
        }//Else end
    }//Method DSRS end

//<AMI_PHDR_START>
//------------------------------------------------------------------------
// Procedure:    DSR2
// Description:  Set FDC, LPT, ECP, UART, IRDA resources (_SRS)
//               Control method can be used for configuring devices with following resource order:
//               1 IRQ resource
//               1 DMA resource
//               2 IO Port
// Input: Arg0 : PnP Resource String to set
//        Arg1 : Device catagory #
// Output:       Nothing
//-------------------------------------------------------------------------
//<AMI_PHDR_END>
    Method(DSR2, 2) {
        CreateWordField(Arg0, ^IRQ2._INT, IRQE)    //IRQ mask 0x1
        CreateByteField(Arg0, ^DMA2._DMA, DMAE)    //DMA 0x4
        CreateWordField(Arg0, ^IO02._MIN, IO21)    //Range 1 Min Base Word 0x8
        CreateWordField(Arg0, ^IO03._MIN, IO31)    //Range 1 Min Base Word 0x8

        ENFG(CGLD(Arg1))                //Enter Config Mode, Select LDN

        // Set Base IO Address
        And(IO21, 0xFF, IOAL)           //Set IO1 Base LSB
        ShiftRight(IO21, 0x8, IOAH)     //Set IO1 Base MSB

        And(IO31, 0xFF, IOL2)           //Set IO2 Base LSB
        ShiftRight(IO31, 0x8, IOH2)     //Set IO2 Base MSB

        // Set IRQ
        If(IRQE){
            FindSetRightBit(IRQE, Local0)
            Subtract(Local0, 1, INTR)
        }Else{
            Store(0, INTR)              //No IRQ used
        }

        // Set DMA
        If(DMAE){
            FindSetRightBit(DMAE, Local0)
            Subtract(Local0, 1, DMCH)
        }Else{
            Store(4, DMCH)              //No DMA
        }

        EXFG()                          //Exit Config Mode

        // Enable ACTR
        DCNT(Arg1, 1)                   //Enable Device (Routing)

        Store(Arg1, Local2)
        If (LGreater(Local2, 0)){Subtract(Local2, 1, Local2)}
    }

//<AMI_PHDR_START>
//------------------------------------------------------------------------
// Procedure:    DSR3
// Description:  Set FDC, LPT, ECP, UART, IRDA resources (_SRS)
//               Control method can be used for configuring devices with following resource order:
//               1 IRQ resource
//               1 IO Port
// Input: Arg0 : PnP Resource String to set
//        Arg1 : Device catagory #
// Output:       Nothing
//-------------------------------------------------------------------------
//<AMI_PHDR_END>
    Method(DSR3, 2) {
        CreateWordField(Arg0, ^IO04._MIN, IO41) //Range 1 Min Base Word 0x8
        CreateWordField(Arg0, ^IRQ3._INT, IRQT) //IRQ mask 0x1
        CreateByteField(Arg0, 0x0B, IRQS) //IRQ Flag
        CreateByteField(Arg0, ^DMA3._DMA, DMAT)    //DMA

        ENFG(CGLD(Arg1))                // Enter Config Mode, Select LDN

        // Set Base IO Address
        And(IO41,0xff, IOAL)            //Set IO Base LSB
        ShiftRight(IO41, 0x8, IOAH)     //Set IO Base MSB

        // Set IRQ
        If(IRQT){
            FindSetRightBit(IRQT, Local0)
            Subtract(Local0, 1, INTR)
            //Set IRQ flag,AMI_TODO:
    		//Set IRQ flag,AMI_TODO:
//ray_override / Support F81866 COM3 ~ COM6 IRQ Sharing Mode Selection / Modified >>
//    		If(And(IRQS,0x10)){
//    			Or(OPT0, 0x01, OPT0)
//    			If(LEqual(IRQS,0x18)){		// IRQ Type: Active-Low-Level-Triggered,Shared.
//    				And(OPT0, 0xFD, OPT0)
//    				And(OPT6, 0xF7, OPT6)
//    			}
//    			Else{
//    				If(LEqual(IRQS,0x11)){	// IRQ Type: Active-High-Edge-Triggered,Shared.
//    				Or(OPT0, 0x01, OPT0)
//    				And(OPT6, 0xF7, OPT6)
//    				}
//    				Else{
//    					If(LEqual(IRQS,0x10)){	// IRQ Type: Active-High-Level-Triggered,Shared.
//    					And(OPT0, 0xFD, OPT0)
//    					Or(OPT6, 0x08, OPT6)
//    					}
//    				}
//    			}
//    		}
            If( LEqual(CIS1, 0) ) {
                And( OPT6, 0xF7, OPT6 )
                And( OPT0, 0xFC, OPT0 )
                Or( OPT0, 0x01, OPT0 )
            }
            Else {
                And( OPT6, 0xF7, OPT6 )
                And( OPT0, 0xFC, OPT0 )
                Or( OPT0, 0x03, OPT0 )
            }
//ray_override / Support F81866 COM3 ~ COM6 IRQ Sharing Mode Selection / Modified <<
        }Else{
            Store(0, INTR)              //No IRQ used
        }
        // Set DMA
        If(DMAT){
           FindSetRightBit(DMAT, Local0)
           Subtract(Local0, 1, DMCH)
        }Else{
           Store(4, DMCH)          //No DMA
        }

        EXFG()                          // Exit Config Mode
        // Enable ACTR
        DCNT(Arg1, 1)                   // Enable Device (Routing)
        Store(Arg1, Local2)
        If (LGreater(Local2, 0)){Subtract(Local2, 1, Local2)}
    }

} // End of SIO1

//-------------------------------------------------------------------------
// SIO_PME WAKE UP EVENTS //
//-------------------------------------------------------------------------
// Following code is the workaround for wake up on RI/Key/Mouse events
// are generated by some SuperIO. The wake up signal (SIO_PME) is
// connected to one of GPIOs of south bridge chip.
// Make sure the correspondent GPIO in south bridge is enabled to generate an SCI
//-------------------------------------------------------------------------
// Add Flag for Fix WakeUp Switch bug. 
Name(PMFG, 0x00)    //PME wake ststus

//-------------------------------------------------------------------------
// SIOS - SIO Chipset specific code called from _PTS
//-------------------------------------------------------------------------
// input  - Arg0 : Sleep state #
// output - nothing
//-------------------------------------------------------------------------
Method(SIOS, 1){
    // Aware wake up events in SIO chip
    Store("SIOS", Debug)

    //AMI_TODO: 
    // 1. select sleep state
    If(LNotEqual(0x05, Arg0)){
        ^SIO1.ENFG(0x0A)                        //Set Logical Device 0A (PME)

        // 2. enable wake-up ; Enable Keyboard, PS/2 Mouse,    UART 1&2 to Generate PME.
        if(\KBFG){
            Or(^SIO1.OPT0, 0x08, ^SIO1.OPT0)    //enable Keyboard Wake-up bit
            Or(^SIO1.RGE8, 0x01, ^SIO1.RGE8)    //enable Keyboard event to wakeup system,bit0
        }        
        Else{
            And(^SIO1.OPT0, 0xF7, ^SIO1.OPT0)   //disable Keyboard Wake-up bit
            And(^SIO1.RGE8, 0xFE, ^SIO1.RGE8)    //disable Keyboard event to wakeup system,bit0
        }
        if(\MSFG){
            Or(^SIO1.OPT0, 0x10, ^SIO1.OPT0)    //enable Mouse Wake-up bit
            Or(^SIO1.RGE8, 0x02, ^SIO1.RGE8)    //enable Keyboard event to wakeup system,bit1
        }        
        Else{
            And(^SIO1.OPT0, 0xEF, ^SIO1.OPT0)   //disable Mouse Wake-up bit
            And(^SIO1.RGE8, 0xFD, ^SIO1.RGE8)    //disable Keyboard event to wakeup system,bit1
        }

        // 3. clear PME Status
        Store(0xFF, ^SIO1.OPT1)                 //Clear I/O PME# Status

        // 4. Enable PME /wakeup
        Or(0x0F, ^SIO1.CR2D,^SIO1.CR2D)            //enable kbc/mouse wakeup
        Or(0x80, ^SIO1.RGE0, ^SIO1.RGE0)           //enable ERP function,bit7   

        ^SIO1.EXFG()
    }
}//End of Method(SIOS, 1){

//-----------------------------------------------------------------------
// SIOW - SIO Chipset specific code called from _WAK
//-----------------------------------------------------------------------
// input  - Sleep State #
// output - nothing
//-----------------------------------------------------------------------
Method(SIOW, 1){
    Store("SIOW", Debug)

    //AMI_TODO: 
    ^SIO1.ENFG(0x0A)                    //Set Logical Device 04 (PME)

    // 1. Clear Status
    Store(^SIO1.OPT1, PMFG)             // PMFG=PME  Wake Status
    Store(0xFF, ^SIO1.OPT1)             //Clear I/O PME# Status
    And(^SIO1.OPT0, 0xE7, ^SIO1.OPT0)   //Clear KBC/Mouse PME Event
    And(^SIO1.RGE8, 0xFC, ^SIO1.RGE8)   //Clear KBC/Mouse wakeup Event

    // 2. Disable PME
    And(0xF0, ^SIO1.CR2D,^SIO1.CR2D)            //disable kbc/mouse wakeup
    And(0x7F, ^SIO1.RGE0, ^SIO1.RGE0)           //disable ERP function,bit7        

    ^SIO1.ENFG(0x07)
    And(^SIO1.OPT5, 0xDF, ^SIO1.OPT5)
    Store(^SIO1.OPT5, ^SIO1.OPT5)

    ^SIO1.EXFG()
}

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

