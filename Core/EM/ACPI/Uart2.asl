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
// $Header: /Alaska/BIN/Modules/ACPI/Template/Core/Uart2.asl 4     3/26/09 4:53p Oleksiyy $
//
// $Revision: 4 $
//
// $Date: 3/26/09 4:53p $
//**********************************************************************;
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/ACPI/Template/Core/Uart2.asl $
// 
// 4     3/26/09 4:53p Oleksiyy
// New ACPI Core implementation - improves logic, execution time and
// memory usage of ACPI module.
// 
// 3     8/03/06 12:45p Stacyh
// Updated to allow the use of SI1P for systems with 2 SIOs.  Now contains
// generic methods assuming SI1P to be 0 as well as methods which check
// SI1P (these are commented out).
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
// 7     03/04/07 5:42p Chung
// Modify all I/O beta version
//
// 5	 9/06/02 10:53a Alexp
// Add SourceSafe headers to all core asl files
//
//**********************************************************************;
// UART2 - COMB or Infrared //
// Requires Uart1(ir).asl component present as well
// Category # :0x01
Device(UAR2) {
	Name(_UID, 2)	//Generic ID for COMB

// Use the following if not using SI1P or only have 1 SIO	
	Method(_HID, 0) {Return(^^SIO1.UHID(1))}	//PnP Device ID
	Method(_STA, 0) {Return(^^SIO1.DSTA(1))}	//Get UART status
	Method(_DIS, 0) {^^SIO1.DCNT(1, 0)}			//Disable UART
	Method(_CRS, 0) {Return(^^SIO1.DCRS(1, 0))}	//Get UART current resources
	Method(_SRS, 1) {^^SIO1.DSRS(Arg0, 1)}		//Set UART resources

// Use the following if using SI1P
//	Method(_HID, 0) {	//PnP Device ID
//		if(SI1P){Return(^^SIO1.UHID(1))}
//		else{Return(^^SIO2.UHID(1))}
//	}
//	Method(_STA, 0) {	//Get UART status
//		if(SI1P){Return(^^SIO1.DSTA(1))}
//		else{Return(^^SIO2.DSTA(1))}
//	}
//	Method(_DIS, 0) {	//Disable UART
//		if(SI1P){^^SIO1.DCNT(1, 0)}
//		else{^^SIO2.DCNT(1, 0)}
//	}
//	Method(_CRS, 0) {	//Get UART current resources
//		if(SI1P){Return(^^SIO1.DCRS(1, 0))}
//		else{Return(^^SIO2.DCRS(1, 0))}
//	}
//	Method(_SRS, 1) {	//Set UART resources
//		if(SI1P){^^SIO1.DSRS(Arg0, 1)}
//		else{^^SIO2.DSRS(Arg0, 1)}
//	}

//------------------------------------------------------------------------
// UART2 Possible Resources
//------------------------------------------------------------------------
//NOTE: _PRS MUST be the NAME not a METHOD object 
//to have GENERICSIO.C working right! 
//-----------------------------------------------------------------------

	Name(_PRS, ResourceTemplate() {
		StartDependentFn(0, 0) {
			IO(Decode16, 0x2F8, 0x2F8, 1, 8)
			IRQNoFlags() {3}
			DMA(Compatibility, NotBusMaster, Transfer8) {}
		}
		StartDependentFnNoPri() {
			IO(Decode16, 0x3F8, 0x3F8, 1, 8)
			IRQNoFlags() {3,4,5,6,7,10,11,12}
			DMA(Compatibility, NotBusMaster, Transfer8) {}
		}
		StartDependentFnNoPri() {
			IO(Decode16, 0x2F8, 0x2F8, 1, 8)
			IRQNoFlags() {3,4,5,6,7,10,11,12}
			DMA(Compatibility, NotBusMaster, Transfer8) {}
		}
		StartDependentFnNoPri() {
			IO(Decode16, 0x3E8, 0x3E8, 1, 8)
			IRQNoFlags() {3,4,5,6,7,10,11,12}
			DMA(Compatibility, NotBusMaster, Transfer8) {}
		}
		StartDependentFnNoPri() {
			IO(Decode16, 0x2E8, 0x2E8, 1, 8)
			IRQNoFlags() {3,4,5,6,7,10,11,12}
			DMA(Compatibility, NotBusMaster, Transfer8) {}
		}
		EndDependentFn()
	})


/*
//---------Power Resources for UART2 -------------------------
	PowerResource(URP2, 0, 0) {	//SystemLevel Parameter=0,
		Method(_STA, 0) {
			Return(URBP)	//Get Power Status
		}			//end of _STA
		Method(_ON) {
			Store(1, URBP)	//Power on
		}			//end of _ON
		Method(_OFF){
			Store(0, URBP)	//Power off
		}			//end of _OFF
	}
	Name(_PR0, Package(){URP2})	//Reference to PowerResources
*/
} // End Of UAR2
