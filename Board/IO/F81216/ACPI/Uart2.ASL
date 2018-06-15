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
// $Header: /Alaska/BIN/IO/Fintek/F81216_Sec/F81216 Device ASL Files/Uart2.ASL 2     7/04/11 3:23a Kasalinyi $
//
// $Revision: 2 $
//
// $Date: 7/04/11 3:23a $
//**********************************************************************;
// Revision History
// ----------------
// $Log: /Alaska/BIN/IO/Fintek/F81216_Sec/F81216 Device ASL Files/Uart2.ASL $
// 
// 2     7/04/11 3:23a Kasalinyi
// [Category]  	Improvement
// [Description]  	Update to new template
// [Files]  		Uart3.ASL
// Uart4.ASL
// Uart2.ASL
// Uart1.ASL
// DeviceASL.cif
// 
// 1     10/28/10 2:32a Mikes
// Implement new name rule
// 
// 1     3/31/10 5:56a Fantasylai
//**********************************************************************;
// UART2 //
// Category # :0x12
Device(UR12) {
    Name(_HID, EISAID("PNP0501"))    //PnP Device ID 16550 Type
	Name(_UID, 0x12)	
                            //Generic ID for COMD
//	Method(_HID, 0)	{Return(^^SIO2.UHID(0x12))}	//PnP Device ID
	Method(_STA, 0) {Return(^^SIO2.DSTA(0x12))}	//Get UART status
	Method(_DIS, 0) {^^SIO2.DCNT(0x12, 0)}			//Disable UART
    //Default is share mode
	Method(_CRS, 0) {Return(^^SIO2.DCR3(0x12, 0))} //Get UART current resources
	Method(_SRS, 1) {^^SIO2.DSR3(Arg0, 0x12)}      //Set UART recources

//-----------------------------------------------------------------------
// UART2 Possible Resources
//-----------------------------------------------------------------------
//NOTE: _PRS MUST be the NAME not a METHOD object 
//to have GENERICSIO.C working right! 
//-----------------------------------------------------------------------
	Name(_PRS, ResourceTemplate() {
		StartDependentFn(0, 0) {
			IO(Decode16, 0x268, 0x268, 1, 8)
			IRQ(Level,ActiveLow,Shared) {11}
			DMA(Compatibility, NotBusMaster, Transfer8) {}
		}
		StartDependentFnNoPri() {
			IO(Decode16, 0x260, 0x260, 1, 8)
			IRQ(Level,ActiveLow,Shared) {10,11,12}
			DMA(Compatibility, NotBusMaster, Transfer8) {}
		}
		StartDependentFnNoPri() {
			IO(Decode16, 0x268, 0x268, 1, 8)
			IRQ(Level,ActiveLow,Shared) {10,11,12}
			DMA(Compatibility, NotBusMaster, Transfer8) {}
		}
		StartDependentFnNoPri() {
			IO(Decode16, 0x270, 0x270, 1, 8)
			IRQ(Level,ActiveLow,Shared) {10,11,12}
			DMA(Compatibility, NotBusMaster, Transfer8) {}
		}
		StartDependentFnNoPri() {
			IO(Decode16, 0x278, 0x278, 1, 8)
			IRQ(Level,ActiveLow,Shared) {10,11,12}
			DMA(Compatibility, NotBusMaster, Transfer8) {}
		}
		EndDependentFn()
	})
/*
//---------Power Resources for UART2 -------------------------
	PowerResource(URP2, 0, 0) {	//SystemLevel Parameter=0,
					//which means UART can be turned off
					//in any sleep state
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
//-----------------------------------------------------------------------

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2008, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************