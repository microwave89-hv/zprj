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
// $Header: /Alaska/BIN/IO/Fintek/F81866/F81866 Device ASL Files/Uart5.ASL 2     2/03/12 1:34a Elviscai $
//
// $Revision: 2 $
//
// $Date: 2/03/12 1:34a $
//**********************************************************************;
// Revision History
// ----------------
// $Log: /Alaska/BIN/IO/Fintek/F81866/F81866 Device ASL Files/Uart5.ASL $
// 
// 2     2/03/12 1:34a Elviscai
// [TAG]  		EIPNONE
// [Category]  	Improvement
// [Description]  	Remove _PRS 0x3F8/0x3E8 from UART3/4/5/6
// 
// 1     7/20/11 4:22a Kasalinyi
// [Category]  	Improvement
// [Description]  	Initial Porting
// [Files]  		DeviceASL.cif
// FDC.ASL
// LPTE.ASL
// PS2kb.asl
// PS2ms.asl
// Uart1.ASL
// Uart2.ASL
// Uart3.ASL
// Uart4.ASL
// Uart5.ASL
// Uart6.ASL
// SIOH.ASL
// 
// 3     3/21/11 9:43p Mikes
// Clean code
//**********************************************************************;
// UART5 //
// Category # :0x13
Device(UAR5) {
    Name(_HID, EISAID("PNP0501"))    //PnP Device ID 16550 Type
    //AMI_TODO:If UAR5 support CIR/IR mode, please use below method. 
    //In method UHID(), it should return HID by device mode registers.
    //Method(_HID, 0)	{Return(^^SIO1.UHID(0x13))}	//PnP Device ID

	Name(_DDN, "COM5")
	Name(_UID, 5)	                            //Generic ID for COME
	Method(_STA, 0) {Return(^^SIO1.DSTA(0x13))}	//Get UART status
	Method(_DIS, 0) {^^SIO1.DCNT(0x13, 0)}		//Disable UART

    //Default is share mode
	Method(_CRS, 0) {Return(^^SIO1.DCR3(0x13, 0))} //Get UART current resources
	Method(_SRS, 1) {^^SIO1.DSR3(Arg0, 0x13)}      //Set UART recources
    //AMI_TODO:If use non-share mode, replace with below method.
	//Method(_CRS, 0) {Return(^^SIO1.DCRS(0x13, 0))}	//Get UART current resources
	//Method(_SRS, 1) {^^SIO1.DSRS(Arg0, 0x13)} 		//Set UART recources

//-----------------------------------------------------------------------
// UART3 Possible Resources
//-----------------------------------------------------------------------
//NOTE: _PRS MUST be the NAME not a METHOD object 
//to have GENERICSIO.C working right! 
//-----------------------------------------------------------------------
	Name(_PRS, ResourceTemplate() {
		StartDependentFn(0, 0) {
			IO(Decode16, 0x278, 0x278, 1, 8)
			IRQ(Level,ActiveLow,Shared) {11}
			DMA(Compatibility, NotBusMaster, Transfer8) {}
		}
		StartDependentFnNoPri() {
			IO(Decode16, 0x278, 0x278, 1, 8)
			IRQ(Level,ActiveLow,Shared) {11}
			DMA(Compatibility, NotBusMaster, Transfer8) {}
		}
		StartDependentFnNoPri() {
			IO(Decode16, 0x270, 0x270, 1, 8)
			IRQ(Level,ActiveLow,Shared) {11}
			DMA(Compatibility, NotBusMaster, Transfer8) {}
		}
//        StartDependentFnNoPri() {
//			IO(Decode16, 0x2F0, 0x2F0, 1, 8)
//			IRQ(Level,ActiveLow,Shared) {3,4,5,6,7,10,11,12}
//			DMA(Compatibility, NotBusMaster, Transfer8) {}
//		}
//        StartDependentFnNoPri() {
//			IO(Decode16, 0x2E0, 0x2E0, 1, 8)
//			IRQ(Level,ActiveLow,Shared) {3,4,5,6,7,10,11,12}
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
