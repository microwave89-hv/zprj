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
// $Header: /Alaska/BIN/IO/Fintek/F81216_Sec/F81216.ASL 6     4/01/13 3:15a Elviscai $
//
// $Revision: 6 $
//
// $Date: 4/01/13 3:15a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/IO/Fintek/F81216_Sec/F81216.ASL $
// 
// 6     4/01/13 3:15a Elviscai
// [TAG]  		EIP115780
// [Category]  	Bug Fix
// [Symptom]  	Burn in test faile while dual IO using same idex/data port
// [RootCause]  	Method DSTA retrned before exit config mode.
// 
// 5     7/18/12 9:31p Elviscai
// [TAG]  		EIPNONE
// [Category]  	Bug Fix
// [Solution]  	Change UHID judgement if IR mode
// 
// 4     2/01/12 10:46p Elviscai
// [TAG]  		EIP76584
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	BIT test fail under OS
// [Solution]  	Update DSR3 Method
// 
// 3     7/04/11 3:22a Kasalinyi
// [Category]  	Improvement
// [Description]  	Update to new template
// [Files]  		IO_F81216.SDL
// F81216.ASL
// F81216.MAK
// F81216.SD
// F81216.UNI
// F81216DXE.C
// F81216PEI.C
// F81216Setup.H
// F81216.CIF
// 
// 2     10/28/10 2:25a Mikes
// Clean code and implement new name rule
// 
// 1     3/31/10 5:55a Fantasylai
// Initial release to F81216 just as a second IO
// 
//*************************************************************************

//<AMI_FHDR_START>
//
// Name:  <F81216.ASL>
//
// Description: Define ACPI method or namespce For Super IO
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
Device(SIO2) {
    Name(_HID, EISAID("PNP0C02"))       // System board resources device node ID
    Name(_UID,0x222)                    // Unique ID. First IO use 0x111, Second IO use 0x222 ...

    Name(CRS, ResourceTemplate(){
        IO(Decode16, 0, 0, 0, 0, IOI)   // Index/Data Io address
    }) // end CRS

    Method (_CRS, 0){
        // Reserve Super I/O Configuration Port
        // 0x0 to 0xF0 already reserved
        // 0x3F0 - 0x3F1 are reserved in FDC
        If(LAnd(LLess(SP2O, 0x3F0), LGreater(SP2O, 0x0F0))){
            CreateWordField(CRS, ^IOI._MIN, GPI0)
            CreateWordField(CRS, ^IOI._MAX, GPI1)
            CreateByteField(CRS, ^IOI._LEN, GPIL)
            Store(SP2O, GPI0)    //Index/Data Base address
            Store(SP2O, GPI1)
            Store(0x02, GPIL)    //IO range
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
        0xFF,    // 0x00 - Serial A (SP1)   
        0xFF,    //   01 - Serial B (SP2)
        0xFF,    //   02 - LPT
        0xFF,    //   03 - FDD
        0xFF,    //   04 - SB16 Audio
        0xFF,    //   05 - MIDI
        0xFF,    //   06 - MSS Audio
        0xFF,    //   07 - AdLib sound (FM synth)
        0x00,    //   08 - Game port #1
        0x01,    //   09 - Game port #2
        0xFF,    //   0A - KBC 60 & 64
        0xFF,    //   0B - EC 62 & 66
        0x02,    //   0C - Reserved 
        0x03,    //   0D - Reserved
        0xFF,    //   0E - PS/2 Mouse
        0xFF,    //   0F - Reserved
//----add your other device below,if no,please cut and modify Package number----------//
        0xFF,    //   10 - CIR
        0x00,    //   11 - Serial A2
        0x01,    //   12 - Serial B2
        0x02,    //   13 - Serial C2
        0x03,    //   14 - Serial D2
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
        Store(ENT2, INDX)
        Store(ENT2, INDX)
        Store(Arg0, LDN)    //Select LDN
    }

    //---------------------------------------------------------------------
    // Exit Config Mode
    //---------------------------------------------------------------------
    Method(EXFG, 0) {
        //AMI_TODO: exit config mode
        Store(0xAA, INDX)
        Release(MUT0)
    }
    //---------------------------------------------------------------------
    // Return current UART mode PnP ID : 0-plain Serial port, non Zero-IrDa mode
    // Arg0 : Device Category #
    //---------------------------------------------------------------------
    Method(UHID, 1){
        //AMI_TODO: Return the correct HID base on UART mode (UART/IR)
        ENFG(CGLD(Arg0))                //Enter Config Mode, Select LDN
        And(OPT1, 0x10, Local0)         //Ir mode is active
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
// Notes: OpeRegion address is defined by 'SP2O' global name. 
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
        SP2O,               // Offset to start of region
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

        Offset(0x25),
        SCF5, 8,        //Set SCF5 

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
        // IO Device presence status is determined during first _STA invocation. 
        // If "Activate" bit is set during first _STA invocation, IO device 
        // present status is stored into IOST global variable.
        // IOST global variable contains the bit mask of all enabled Io devices.
        ENFG(CGLD(Arg0))        //Enter Config Mode, Select LDN
        Store(ACTR, Local0)
        Or(ShiftLeft(IOAH, 8),IOAL,Local1)
        EXFG()                  //Exit Config Mode

        // LDN's not decoded, Device not present.
        If(LEqual(Local0, 0xFF)) {Return(0x0)}    

        //Assume register(ACTR) bit0 is "Active" bit.
        //AMI_TODO: If register(ACTR) non-bit0 is "Active" bit, change below code.
        And(Local0, 1, Local0)  //Leave only "Activate" bit

        // Update IO device status in IOST according to the category#
        // Note. Once device is detected its status bit cannot be removed
        If(Local0){ 
            Return(0x0F)            // Device present & Active
        }    
        Else{
                If(Local1) { Return(0x0D)}  // Device Detected & Not Active
//              Or(ShiftLeft(IOH2, 8),IOL2,Local0)    
//              If(Local0) { Return(0x0D)}  // Device Detected & Not Active
                Return(0x00) // Device not present
        }
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
    	    // Set IRQ Type:porting according INTT
            //AMI_TODO:
            If(And(INTT,0x01)){
                Store(0x18, IRQS)       // IRQ Type: Active-Low-Level-Triggered,Shared.
            } Else {
                Store(1, IRQS)          // IRQ Type: Active-High-Edge-Triggered,No-Shared(default)
            }
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
            //Set IRQ flag,AMI_TODO: bit4:_SHR,bit3:_LL,bit0:_HE
            Store(0x01, INTT) //some relative share,active-low/high registers
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

} // End of SIO2

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




