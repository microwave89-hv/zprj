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
// $Header: /Alaska/BIN/Modules/ACPI/Template/Core/irda.asl 3     3/26/09 4:53p Oleksiyy $
//
// $Revision: 3 $
//
// $Date: 3/26/09 4:53p $
//**********************************************************************;
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/ACPI/Template/Core/irda.asl $
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
// 5     03/04/07 5:40p Chung
// Modify all I/O beta version
// 
// 4	 9/06/02 10:53a Alexp
// Add SourceSafe headers to all core asl files
// 
//
//**********************************************************************;
// Standalone InfraRed device //
//**********************************************************************;
// Category # :0x10 (Generic IO range 1)
Device(IRDA) {
	Name(_HID, EISAID("PNP0510"))		//PnP Device ID IrDa
	Name(_UID, 3)				//Unique ID for IrDa 3
	Method(_STA, 0) {Return(DSTA(0x10))}	//Get status
	Method(_DIS, 0) {DCNT(0x10, 0)} 	//Disable
	Method(_CRS, 0) {Return(DCRS(0x10, 0))}	//Get current resources
	Method(_SRS, 1) {DSRS(Arg0, 0x10) }	//Set recources
//	Method(_PRS, 0) {Return(CMPR)}		//Return possible resources


//------------------------------------------------------------------------
// UART1/2 , IrDa Possible Resources
//------------------------------------------------------------------------
//NOTE: _PRS MUST be the NAME not a METHOD object 
//to have GENERICSIO.C working right! 
//-----------------------------------------------------------------------
	Name(_PRS, ResourceTemplate() {
// IRQ, No DMA
		StartDependentFn(0, 0) {
			IO(Decode16, 0x3F8, 0X3F8, 1, 8)
			IRQNoFlags() {4}
			DMA(Compatibility, NotBusMaster, Transfer8) {}
		}
		StartDependentFnNoPri() {
			IO(Decode16, 0x3F8, 0X3F8, 1, 8)
			IRQNoFlags() {3,4,5,6,7,10,11,12}
			DMA(Compatibility, NotBusMaster, Transfer8) {}
		}
		StartDependentFnNoPri() {
			IO(Decode16, 0x2F8, 0X2F8, 1, 8)
			IRQNoFlags() {3,4,5,6,7,10,11,12}
			DMA(Compatibility, NotBusMaster, Transfer8) {}
		}
		StartDependentFnNoPri() {
			IO(Decode16, 0x3E8, 0X3E8, 1, 8)
			IRQNoFlags() {3,4,5,6,7,10,11,12}
			DMA(Compatibility, NotBusMaster, Transfer8) {}
		}
		StartDependentFnNoPri() {
			IO(Decode16, 0x2E8, 0X2E8, 1, 8)
			IRQNoFlags() {3,4,5,6,7,10,11,12}
			DMA(Compatibility, NotBusMaster, Transfer8) {}
		}
// DMA, IRQ
		StartDependentFnNoPri() {
			IO(Decode16, 0x3F8, 0X3F8, 1, 8)
			IRQNoFlags() {3,4,5,6,7,10,11,12}
			DMA(Compatibility, NotBusMaster, Transfer8) {0,1,2,3}
		}
		StartDependentFnNoPri() {
			IO(Decode16, 0x2F8, 0X2F8, 1, 8)
			IRQNoFlags() {3,4,5,6,7,10,11,12}
			DMA(Compatibility, NotBusMaster, Transfer8) {0,1,2,3}
		}
		StartDependentFnNoPri() {
			IO(Decode16, 0x3E8, 0X3E8, 1, 8)
			IRQNoFlags() {3,4,5,6,7,10,11,12}
			DMA(Compatibility, NotBusMaster, Transfer8) {0,1,2,3}
		}
		StartDependentFnNoPri() {
			IO(Decode16, 0x2E8, 0X2E8, 1, 8)
			IRQNoFlags() {3,4,5,6,7,10,11,12}
			DMA(Compatibility, NotBusMaster, Transfer8) {0,1,2,3}
		}
		EndDependentFn()
})
} // End Of IRDA //
