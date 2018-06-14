//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             5555 Oakbrook Pkwy, Norcross, GA 30093               **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
// $Header: /Alaska/BIN/Modules/ACPI/Template/Core/midi.asl 3     3/26/09 4:53p Oleksiyy $
//
// $Revision: 3 $
//
// $Date: 3/26/09 4:53p $
//**********************************************************************;
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/ACPI/Template/Core/midi.asl $
// 
// 3     3/26/09 4:53p Oleksiyy
// New ACPI Core implementation - improves logic, execution time and
// memory usage of ACPI module.
// 
// 2     4/03/06 4:05p Felixp
// New Super I/O infrastructure Support
// 
// 1     3/24/05 5:01p Sivagarn
// 
// 1     2/03/05 6:42p Sivagarn
// 0ABHI001 Check in
// 
// 1     7/27/04 2:48p Yakovlevs
// 
// 5     03/04/07 5:41p Chung
// Modify all I/O beta version
// 
// 4     9/06/02 10:53a Alexp
// Add SourceSafe headers to all core asl files
//
//**********************************************************************;
//**********************************************************************;
// Generic MPU 401 Device
//**********************************************************************;
// Category # :0x05
Device(MIDI){
	Name(_HID, EISAID("PNPB006"))	//PnP ID for GamePort
	Method(_STA, 0) {Return(DSTA(5))}	//Get status
	Method(_DIS, 0) {DCNT(5,0)}	//Disable

//-----------------------------------------------------------------------
// MIDIPort Current Resources template (returned by _CRS)
//-----------------------------------------------------------------------
	Name(MDCR, ResourceTemplate(){
//		IO(Decode16, 0, 0, 0x30, 2, GIO1)
//		IRQNoFlags(GIRQ) {10}
		IO(Decode16, 0, 0, 1, 2, GIO1)
		IRQNoFlags(GIRQ) {5}
	})

	Method(_CRS, 0){
		CreateWordField(MDCR, ^GIO1._MIN, IOML)	//Range 2 Min Base Word
		CreateWordField(MDCR, ^GIO1._MAX, IOMH)	//Range 2 Max Base Word
		CreateWordField(MDCR, ^GIRQ._INT, IRQM)	//IRQ mask 0x1

		ENFG(CGLD(5))		//Enter Config Mode, Select LDN

// Write Current Settings into Buffer for IO Descriptor
// IO ports for MPU 401
		ShiftLeft(IOAH, 8, IOML)	//Get IO Base MSB
		Or(IOAL, IOML, IOML)	//Get IO Base LSB
		Store(IOML, IOMH)	//Set Max Base Word
// Write Current Settings into IRQ descriptor
		If(INTR)
			{ShiftLeft(1, INTR, IRQM)}
		Else
			{Store(0, IRQM)}	//No IRQ used
		EXFG()			//Exit Config Mode
		Return(MDCR)		//Return Byte Stream
	}

	Method(_SRS, 1){
// Arg0 - PnP Resource String to set
		CreateWordField(Arg0, ^GIO1._MIN, IO11)	//Range 1 Min Base Word
		CreateWordField(Arg0, ^GIRQ._INT, IRQM)	//IRQ mask 0x1

		ENFG(CGLD(5))		//Enter Config Mode, Select LDN

		// Set Midi Base IO Address
		And(IO11, 0xFF, IOAL)		//Set IO Base LSB
		ShiftRight(IO11, 0x08, IOAH)	//Set IO Base MSB
		// Set IRQ
		If(IRQM){
			FindSetRightBit(IRQM, Local0)
			Subtract(Local0, 1, INTR)
		}
		Else
			{Store(0, INTR)}	//No IRQ used
		DCNT(5, 1)		//Enable Device (Routing)
		EXFG()			//Exit Config Mode
	}

//-----------------------------------------------------------------------
// MIDIPort Possible Resources
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
//NOTE: _PRS MUST be the NAME not a METHOD object 
//to have GENERICSIO.C working right! 
//-----------------------------------------------------------------------
	Name(_PRS, ResourceTemplate(){
		StartDependentFnNoPri(){
			IO(Decode16, 0x300, 0x300, 1, 2)
			IRQNoFlags() {5,7,9,10,11}
		}
		StartDependentFnNoPri(){
			IO(Decode16, 0x330, 0x330, 1, 2)
			IRQNoFlags() {5,7,9,10,11}
		}
		EndDependentFn()
	})
} // End Of Midi ////////////////////////////////////////////////////////
