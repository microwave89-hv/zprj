//**********************************************************************;
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
// $Header: /Alaska/BIN/Modules/ACPI/Template/Core/Uart3ir.asl 3     3/26/09 4:53p Oleksiyy $
//
// $Revision: 3 $
//
// $Date: 3/26/09 4:53p $
//**********************************************************************;
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/ACPI/Template/Core/Uart3ir.asl $
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
// 1     03/04/07 5:55p Chung
// Add ASL core for new all I/O beta version
//
//**********************************************************************;
// UART3 //
// Category # :0x00
Device(UAR3) {
	Name(_UID, 3)			//Generic ID for COMC
	Method(_HID, 0) {				//PnP Device ID
		if(SI1P){Return(^^SIO2.UHID(0))}
		else{Return(^^SIO1.UHID(0))}
	}
	Method(_STA, 0) {				//Get UART status
		if(SI1P){Return(^^SIO2.DSTA(0))}
		else{Return(^^SIO1.DSTA(0))}
	}
	Method(_DIS, 0) {				//Disable UART
		if(SI1P){^^SIO2.DCNT(0, 0)}
		else{^^SIO1.DCNT(0, 0)}
	}
	Method(_CRS, 0) {				//Get UART current resources
		if(SI1P){Return(^^SIO2.DCRS(0, 1))}
		else{Return(^^SIO1.DCRS(0, 1))}
	}
	Method(_SRS, 1) {				//Set UART resources
		if(SI1P){^^SIO2.DSRS(Arg0, 0)}
		else{^^SIO1.DSRS(Arg0, 0)}
	}


//-----------------------------------------------------------------------
// UART3 IrDa Possible Resources
//-----------------------------------------------------------------------
//NOTE: _PRS MUST be the NAME not a METHOD object 
//to have GENERICSIO.C working right! 
//-----------------------------------------------------------------------

	Name(_PRS, ResourceTemplate() {
// IRQ, No DMA
		StartDependentFn(0, 0) {
			IO(Decode16, 0x3E8, 0X3E8, 1, 8)
			IRQNoFlags() {11}
			DMA(Compatibility, NotBusMaster, Transfer8) {}
		}
		StartDependentFnNoPri() {
			IO(Decode16, 0x3F8, 0X3F8, 1, 8)
			IRQNoFlags() {3,4,5,6,7,9,10,11,12}
			DMA(Compatibility, NotBusMaster, Transfer8) {}
		}
		StartDependentFnNoPri() {
			IO(Decode16, 0x2F8, 0X2F8, 1, 8)
			IRQNoFlags() {3,4,5,6,7,9,10,11,12}
			DMA(Compatibility, NotBusMaster, Transfer8) {}
		}
		StartDependentFnNoPri() {
			IO(Decode16, 0x3E8, 0X3E8, 1, 8)
			IRQNoFlags() {3,4,5,6,7,9,10,11,12}
			DMA(Compatibility, NotBusMaster, Transfer8) {}
		}
		StartDependentFnNoPri() {
			IO(Decode16, 0x2E8, 0X2E8, 1, 8)
			IRQNoFlags() {3,4,5,6,7,9,10,11,12}
			DMA(Compatibility, NotBusMaster, Transfer8) {}
		}
// IRQ, DMA
		StartDependentFnNoPri() {
			IO(Decode16, 0x3F8, 0X3F8, 1, 8)
			IRQNoFlags() {3,4,5,6,7,9,10,11,12}
			DMA(Compatibility, NotBusMaster, Transfer8) {0,1,2,3}
		}
		StartDependentFnNoPri() {
			IO(Decode16, 0x2F8, 0X2F8, 1, 8)
			IRQNoFlags() {3,4,5,6,7,9,10,11,12}
			DMA(Compatibility, NotBusMaster, Transfer8) {0,1,2,3}
		}
		StartDependentFnNoPri() {
			IO(Decode16, 0x3E8, 0X3E8, 1, 8)
			IRQNoFlags() {3,4,5,6,7,9,10,11,12}
			DMA(Compatibility, NotBusMaster, Transfer8) {0,1,2,3}
		}
		StartDependentFnNoPri() {
			IO(Decode16, 0x2E8, 0X2E8, 1, 8)
			IRQNoFlags() {3,4,5,6,7,9,10,11,12}
			DMA(Compatibility, NotBusMaster, Transfer8) {0,1,2,3}
		}
		EndDependentFn()
	})
} // End Of UAR3 //------------------------------------------------------
