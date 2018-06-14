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
// $Header: /Alaska/BIN/Modules/ACPI/Template/Core/game.asl 3     3/26/09 4:53p Oleksiyy $
//
// $Revision: 3 $
//
// $Date: 3/26/09 4:53p $
//**********************************************************************;
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/ACPI/Template/Core/game.asl $
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
// 5     03/04/07 5:39p Chung
// Modify all I/O beta version
// 
// 4     9/06/02 10:53a Alexp
// Add SourceSafe headers to all core asl files
// 
//
//**********************************************************************;
//**********************************************************************;
// Generic Game Port
//------------------------------------------------------------------------
// Category # :0x08
Device(GAME) {
	Name(_HID, EISAID("PNPB02F"))		// PnP ID for GamePort
	Method(_STA, 0) { Return(DSTA(8))}	// Get status
	Method(_DIS, 0) { DCNT(8,0) }		// Disable
// GamePort Current Resource template (to be returned by _CRS)
	Name(GMCR, ResourceTemplate() {
		IO(Decode16, 0, 0, 8, 8, GIO1)
	})

	Method(_CRS, 0) {
		CreateWordField(GMCR, ^GIO1._MIN, IOGL)	// Min Base Word
		CreateWordField(GMCR, ^GIO1._MAX, IOGH)	// Max Base Word

		ENFG(CGLD(8))		// Enter Config Mode, Select LDN

// Write Current Settings into Buffer for IO Descriptor
// IO ports for Game
		ShiftLeft(IOAH, 8, IOGL)	// Get IO Base MSB
		Or(IOAL, IOGL, IOGL)		// Get IO Base LSB
		Store(IOGL, IOGH)		// Set Max Base Word

		EXFG()			// Exit Config Mode
		Return(GMCR)		// Return Byte Stream
	}

	Method(_SRS, 1) {
		CreateWordField(Arg0, ^GIO1._MIN, IO11)	// Range 1 Min Base Word
		ENFG(CGLD(8))		// Enter Config Mode, Select LDN
// Set Game Base IO Address
		And(IO11, 0xff, IOAL)		// Set IO Base LSB
		ShiftRight(IO11, 0x8, IOAH)	// Set IO Base MSB
		DCNT(8, 1)		// Enable Device (Routing)
		EXFG()			// Exit Config Mode
	}
//------------------------------------------------------------------------
// GamePort Possible Resources
//------------------------------------------------------------------------
//NOTE: _PRS MUST be the NAME not a METHOD object 
//to have GENERICSIO.C working right! 
//-----------------------------------------------------------------------

	Name(_PRS, ResourceTemplate() {
		StartDependentFn(0,0) {
			IO(Decode16, 0x201, 0x201, 1, 8)
		}
		StartDependentFnNoPri(){
			IO(Decode16, 0x209, 0x209, 1, 8)
		}
		EndDependentFn()
	})

} // End Of GamePort ////////////////////////////////////////////////////
