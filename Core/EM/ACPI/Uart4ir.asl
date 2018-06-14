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
//**********************************************************************;
// $Header: /Alaska/BIN/Modules/ACPI/Template/Core/Uart4ir.asl 3     3/26/09 4:53p Oleksiyy $
//
// $Revision: 3 $
//
// $Date: 3/26/09 4:53p $
//**********************************************************************;
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/ACPI/Template/Core/Uart4ir.asl $
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
// 1     2/03/05 6:41p Sivagarn
// 0ABHI001 Check in
// 
// 1     7/27/04 2:48p Yakovlevs
// 
// 1     03/04/07 5:57p Chung
// Add ASL core for new all I/O beta version
//
//**********************************************************************;
// UART4 - COMD or Infrared //
// Requires Uart4(ir).asl component present as well
// Cannot be included along with UART4IR.ASL. Only one UART4 Device can be present in ASL.
// Category # :0x01
Device(UAR4) {
	Name(_UID, 4)				//Generic ID for COMD
	Method(_HID, 0) {				//PnP Device ID
		if(SI1P){Return(^^SIO2.UHID(1))}
		else{Return(^^SIO1.UHID(1))}
	}
	Method(_STA, 0) {				//Get UART status
		if(SI1P){Return(^^SIO2.DSTA(1))}
		else{Return(^^SIO1.DSTA(1))}
	}
	Method(_DIS, 0) {				//Disable UART
		if(SI1P){^^SIO2.DCNT(1, 0)}
		else{^^SIO1.DCNT(1, 0)}
	}
	Method(_CRS, 0) {				//Get UART current resources
		if(SI1P){Return(^^SIO2.DCRS(1, 1))}
		else{Return(^^SIO1.DCRS(1, 1))}
	}
	Method(_SRS, 1) {				//Set UART resources
		if(SI1P){^^SIO2.DSRS(Arg0, 1)}
		else{^^SIO1.DSRS(Arg0, 1)}
	}


//-----------------------------------------------------------------------
// UART4 IrDa Possible Resources
//-----------------------------------------------------------------------
//NOTE: _PRS MUST be the NAME not a METHOD object 
//to have GENERICSIO.C working right! 
//-----------------------------------------------------------------------

	Name(_PRS, ResourceTemplate() {
// IRQ, No DMA
		StartDependentFn(0, 0) {
			IO(Decode16, 0x2E8, 0x2E8, 1, 8)
			IRQNoFlags() {10}
			DMA(Compatibility, NotBusMaster, Transfer8) {}
		}
		StartDependentFnNoPri() {
			IO(Decode16, 0x3F8, 0x3F8, 1, 8)
			IRQNoFlags() {3,4,5,6,7,9,10,11,12}
			DMA(Compatibility, NotBusMaster, Transfer8) {}
		}
		StartDependentFnNoPri() {
			IO(Decode16, 0x2F8, 0x2F8, 1, 8)
			IRQNoFlags() {3,4,5,6,7,9,10,11,12}
			DMA(Compatibility, NotBusMaster, Transfer8) {}
		}
		StartDependentFnNoPri() {
			IO(Decode16, 0x3E8, 0x3E8, 1, 8)
			IRQNoFlags() {3,4,5,6,7,9,10,11,12}
			DMA(Compatibility, NotBusMaster, Transfer8) {}
		}
		StartDependentFnNoPri() {
			IO(Decode16, 0x2E8, 0x2E8, 1, 8)
			IRQNoFlags() {3,4,5,6,7,9,10,11,12}
			DMA(Compatibility, NotBusMaster, Transfer8) {}
		}
// IRQ, DMA
		StartDependentFnNoPri() {
			IO(Decode16, 0x3F8, 0x3F8, 1, 8)
			IRQNoFlags() {3,4,5,6,7,9,10,11,12}
			DMA(Compatibility, NotBusMaster, Transfer8) {0,1,2,3}
		}
		StartDependentFnNoPri() {
			IO(Decode16, 0x2F8, 0x2F8, 1, 8)
			IRQNoFlags() {3,4,5,6,7,9,10,11,12}
			DMA(Compatibility, NotBusMaster, Transfer8) {0,1,2,3}
		}
		StartDependentFnNoPri() {
			IO(Decode16, 0x3E8, 0x3E8, 1, 8)
			IRQNoFlags() {3,4,5,6,7,9,10,11,12}
			DMA(Compatibility, NotBusMaster, Transfer8) {0,1,2,3}
		}
		StartDependentFnNoPri() {
			IO(Decode16, 0x2E8, 0x2E8, 1, 8)
			IRQNoFlags() {3,4,5,6,7,9,10,11,12}
			DMA(Compatibility, NotBusMaster, Transfer8) {0,1,2,3}
		}
		EndDependentFn()
	})
} // End Of UAR4 //------------------------------------------------------
