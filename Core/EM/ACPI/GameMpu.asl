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
// $Header: /Alaska/BIN/Modules/ACPI/Template/Core/GameMpu.asl 3     3/26/09 4:53p Oleksiyy $
//
// $Revision: 3 $
//
// $Date: 3/26/09 4:53p $
//**********************************************************************;
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/ACPI/Template/Core/GameMpu.asl $
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
// 4     03/04/07 5:40p Chung
// Modify all I/O beta version
// 
// 3     9/06/02 10:53a Alexp
// Add SourceSafe headers to all core asl files
// 
//
//**********************************************************************;
// Combined Game & Midi Logical Device 
//**********************************************************************;
// Generic Game Port
//-----------------------------------------------------------------------
// Category # :0x08
Device(GAME){
	Name(_HID, EISAID("PNPB02F"))		//PnP ID for GamePort
	Method(_STA, 0) {Return(DSTA(8))}	//Get status
//	Method(_DIS, 0) {DCNT(8,0)}		//Disable
//-----------------------------------------------------------------------
// GamePort Current Resource template (to be returned by _CRS)
//-----------------------------------------------------------------------
	Name(GMCR, ResourceTemplate(){
		IO(Decode16, 0x201, 0x201, 1, 8, GMIO)
	})

	Method(_CRS, 0){
		CreateByteField(GMCR, 0x02, IOLO)	//Range Min Base LSB
		CreateByteField(GMCR, 0x03, IOHI)	//Range Min Base MSB
		CreateWordField(GMCR, 0x02, IOHL)	//Range Min Base Word
		CreateWordField(GMCR, 0x04, IORL)	//Range Max Base Word

		ENFG(CGLD(8))		//Enter Config Mode, Select LDN

// Write Current Settings into Buffer for IO Descriptor
		Store(IOAH, IOHI)	//Get IO Base MSB
		Store(IOAL, IOLO)	//Get IO Base LSB
		Store(IOHL, IORL)	//Set MaxBase = MinBase

		EXFG()			//Exit Config Mode
		Return(GMCR)		//Return Byte Stream
	}

	Method(_SRS, 1){
		CreateByteField (Arg0, 0x02, POLB)	// Range Min Base LSB
		CreateByteField (Arg0, 0x03, POHB)	// Range Min Base MSB

		ENFG(CGLD(8))		// Enter Config Mode, Select LDN

// Set Base IO Address
		Store(POLB, IOAL)	// Set IO Base LSB
		Store(POHB, IOAH)	// Set IO Base MSB
// Enable ACTR
		DCNT(8, 1)		// Enable Device (Routing)
		EXFG()			// Exit Config Mode
	}
//-----------------------------------------------------------------------
// GamePort Possible Resources (returned by _PRS)
//-----------------------------------------------------------------------
//NOTE: _PRS MUST be the NAME not a METHOD object 
//to have GENERICSIO.C working right! 
//-----------------------------------------------------------------------
	Name(_PRS, ResourceTemplate(){
		StartDependentFn(0,0) {
			IO(Decode16, 0x201, 0x201, 1, 8)
		}
		StartDependentFnNoPri(){
			IO(Decode16, 0x209, 0x209, 1, 8)
		}
		EndDependentFn()
	})
}
// End Of GamePort //////////////////////////////////////////////////////
// Win627 specific Combined Game & Midi Logical Device 
// IO ports are defined at offset 0x62, 0x63 of LDN configuratsion space
//**********************************************************************;
// Generic MPU 401 Device
//**********************************************************************;
// Category # :0x05
Device(MIDI){
	Name(_HID, EISAID("PNPB006"))	//PnP ID for GamePort
	Method(_STA, 0) {Return(DSTA(5))}	//Get status
//	Method(_DIS, 0) {DCNT(5,0)}	//Disable
//-----------------------------------------------------------------------
// MIDIPort Current Resources template (returned by _CRS)
//-----------------------------------------------------------------------
	Name(MDCR, ResourceTemplate(){
		IO(Decode16, 0x300, 0x300, 1, 2, MDIO)
		IRQNoFlags(MBI1) {5}
	})

	Method(_CRS, 0){
		CreateByteField(MDCR, 0x02, IOLO)	//Range Min Base LSB
		CreateByteField(MDCR, 0x03, IOHI)	//Range Min Base MSB
		CreateWordField(MDCR, 0x02, IOHL)	//Range Min Base Word
		CreateWordField(MDCR, 0x04, IORL)	//Range Max Base Word
		CreateWordField(MDCR, 0x09, MIRQ)	//IRQ Mask (word)

		ENFG(CGLD(5))		//Enter Config Mode, Select LDN

// Write Current Settings into Buffer for IO Descriptor
		Store(IOH2, IOHI)	//Get IO Base MSB
		Store(IOL2, IOLO)	//Get IO Base LSB
		Store(IOHL, IORL)	//Set MaxBase = MinBase
// Write Current Settings into IRQ descriptor
		ShiftLeft(1, INTR, MIRQ)

		EXFG()			//Exit Config Mode
		Return(MDCR)		//Return Byte Stream
	}

	Method(_SRS, 1){
// Arg0 - PnP Resource String to set
		CreateByteField (Arg0, 0x02, POLB)	//Range Min Base LSB
		CreateByteField (Arg0, 0x03, POHB)	//Range Min Base MSB
		CreateWordField (Arg0, 0x09, MIRQ)	//IRQ mask (word)

		ENFG(CGLD(5))		//Enter Config Mode, Select LDN

// Set Base IO Address
		Store(POLB, IOL2)	//Set IO Base LSB
		Store(POHB, IOH2)	//Set IO Base MSB

// Set IRQ
		FindSetRightBit(MIRQ, Local0)
		Subtract(Local0, 1, INTR)

		DCNT(5, 1)		//Enable Device (Routing)
		EXFG()			//Exit Config Mode
	}

//-----------------------------------------------------------------------
// MIDIPort Possible Resources (returned by _PRS)
//------------------------------------------------------------------------
//NOTE: _PRS MUST be the NAME not a METHOD object 
//to have GENERICSIO.C working right! 
//-----------------------------------------------------------------------
	Name(_PRS, ResourceTemplate(){
		StartDependentFnNoPri()	{
			IO(Decode16, 0x300, 0x300, 1, 2)
			IRQNoFlags() {5,7,9,10,11}
		}
		StartDependentFnNoPri()	{
			IO(Decode16, 0x330, 0x330, 1, 2)
			IRQNoFlags() {5,7,9,10,11}
		}
		EndDependentFn()
	})
}
// End Of Midi //////////////////////////////////////////////////////////
