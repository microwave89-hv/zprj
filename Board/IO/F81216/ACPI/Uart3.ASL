//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             5555 Oakbrook Pkwy, Norcross, GA 30093               **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
// $Header: /Alaska/BIN/IO/Fintek/F81216_Sec/F81216 Device ASL Files/Uart3.ASL 3     7/04/11 3:23a Kasalinyi $
//
// $Revision: 3 $
//
// $Date: 7/04/11 3:23a $
//**********************************************************************;
// Revision History
// ----------------
// $Log: /Alaska/BIN/IO/Fintek/F81216_Sec/F81216 Device ASL Files/Uart3.ASL $
// 
// 3     7/04/11 3:23a Kasalinyi
// [Category]  	Improvement
// [Description]  	Update to new template
// [Files]  		Uart3.ASL
// Uart4.ASL
// Uart2.ASL
// Uart1.ASL
// DeviceASL.cif
// 
// 2     10/28/10 2:33a Mikes
// Implement new name rule
// 
// 1     3/31/10 5:56a Fantasylai
//**********************************************************************;
// UART3 //
// Category # :0x13
Device(UR13) {
    Name(_HID, EISAID("PNP0501"))    //PnP Device ID 16550 Type
	Name(_UID, 0x13)	       
	Name(_DDN, "COM9")                  

//	Method(_HID, 0)	{Return(^^SIO2.UHID(0x13))}	//PnP Device ID
	Method(_STA, 0) {Return(^^SIO2.DSTA(0x0C))}	//Get UART status
	Method(_DIS, 0) {^^SIO2.DCNT(0x0C, 0)}		//Disable UART
    //Default is share mode
	Method(_CRS, 0) {Return(^^SIO2.DCR3(0x0C, 0))} //Get UART current resources
	Method(_SRS, 1) {^^SIO2.DSR3(Arg0, 0x0C)}      //Set UART recources

//-----------------------------------------------------------------------
// UART3 Possible Resources
//-----------------------------------------------------------------------
//NOTE: _PRS MUST be the NAME not a METHOD object 
//to have GENERICSIO.C working right! 
//-----------------------------------------------------------------------
	Name(_PRS, ResourceTemplate() {
		StartDependentFn(0, 0) {
			IO(Decode16, 0x2D8, 0x2D8, 1, 8)
			IRQ(Level,ActiveLow,Shared) {5}
			DMA(Compatibility, NotBusMaster, Transfer8) {}
		}
		StartDependentFnNoPri() {
			IO(Decode16, 0x2D8, 0x2D8, 1, 8)
			IRQ(Level,ActiveLow,Shared) {5}
			DMA(Compatibility, NotBusMaster, Transfer8) {}
		}
		StartDependentFnNoPri() {
			IO(Decode16, 0x2D0, 0x2D0, 1, 8)
			IRQ(Level,ActiveLow,Shared) {5}
			DMA(Compatibility, NotBusMaster, Transfer8) {}
		}
//		StartDependentFnNoPri() {
//			IO(Decode16, 0x270, 0x270, 1, 8)
//			IRQ(Level,ActiveLow,Shared) {10,11,12}
//			DMA(Compatibility, NotBusMaster, Transfer8) {}
//		}
//		StartDependentFnNoPri() {
//			IO(Decode16, 0x278, 0x278, 1, 8)
//			IRQ(Level,ActiveLow,Shared) {10,11,12}
//			DMA(Compatibility, NotBusMaster, Transfer8) {}
//		}
		EndDependentFn()
	})

} // End Of UAR3
//-----------------------------------------------------------------------

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
