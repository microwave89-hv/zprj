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
// $Header: /Alaska/BIN/Modules/ACPI/Template/Core/CIR.ASL 4     3/26/09 4:53p Oleksiyy $
//
// $Revision: 4 $
//
// $Date: 3/26/09 4:53p $
//**********************************************************************;
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/ACPI/Template/Core/CIR.ASL $
// 
// 4     3/26/09 4:53p Oleksiyy
// New ACPI Core implementation - improves logic, execution time and
// memory usage of ACPI module.
// 
// 3     4/19/06 1:37p Stacyh
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
// 1     03/04/07 5:48p Chung
// Add ASL core for new all I/O beta version
// 
// 4	 9/06/02 10:53a Alexp
// Add SourceSafe headers to all core asl files
// 
//**********************************************************************;
// Standalone InfraRed device //
//**********************************************************************;
// Category # :0x10 (Generic IO range 1)
Device(CIR){
	Name(_HID, EISAID("PNP0510"))		//PnP Device ID IrDA
	Method(_STA, 0) {Return(IRST(0x10))}	//Get status
	Method(_DIS, 0) {DCNT(0x10, 0)} 	//Disable
	Method(_CRS, 0) {Return(IRCR(0x10))}	//Get CIR current resources
	Method(_SRS, 1) {IRSR(Arg0, 0x10)}	//Set CIR recources
//	Method(_PRS, 0) {Return(IRPR)}		//Return possible resources

//-----------------------------------------------------------------------
// IRST - GET SIO DEVICE STATUS according to ACTR/IOAH/IOAL
//
//	Input - Arg0 : Device's category #
//	Return- Device Status Byte
//-----------------------------------------------------------------------
	Method(IRST, 1){
		ENFG(CGLD(Arg0))	//Enter Config Mode, Select LDN
		If(ACTR)
			{Store(0x0F, Local0)}	//Present & Active
		Else{
			If(IOAH)
				{Store(0x0D, Local0)}	//Then present & not active
			Else
				{Store(0, Local0)}	//Not present
		}
		EXFG()			//Exit Config Mode
		Return(Local0)		//Return device status
	} // End Of IRST

//-----------------------------------------------------------------------
// IrDa Possible Resources
//-----------------------------------------------------------------------
//NOTE: _PRS MUST be the NAME not a METHOD object 
//to have GENERICSIO.C working right! 
//-----------------------------------------------------------------------
	Name(_PRS, ResourceTemplate(){
		StartDependentFn(0, 0){
			IO(Decode16, 0x3E0, 0x3E0, 8, 8)
			IRQNoFlags() {10}
		}
		StartDependentFnNoPri(){
			IO(Decode16, 0x3E0, 0x3E0, 8, 8)
			IRQNoFlags() {3,4,5,6,7,9,10,11,12}
		}
		StartDependentFnNoPri(){
			IO(Decode16, 0x2E0, 0x2E0, 8, 8)
			IRQNoFlags() {3,4,5,6,7,9,10,11,12}
		}
		StartDependentFnNoPri(){
			IO(Decode16, 0x298, 0x298, 8, 8)
			IRQNoFlags() {3,4,5,6,7,9,10,11,12}
		}
		EndDependentFn()
	})

//-----------------------------------------------------------------------
// IRCR - Returns Byte stream of Current resources. May contain Resources such:
//
//	Input - Arg0 : Device's category #
//	Return- Buffer
//-----------------------------------------------------------------------
	Name(PBUF, ResourceTemplate() {
		IO(Decode16, 0, 0, 1, 8, PBP1)
		IRQNoFlags(PBI1) {0}
	})

	Method(IRCR, 1){
	// Arg0 - LDN
		CreateByteField(PBUF, 0x02, IOLO)	//Range Min Base LSB
		CreateByteField(PBUF, 0x03, IOHI)	//Range Min Base MSB
		CreateWordField(PBUF, 0x02, IOHL)	//Range Min Base Word
		CreateWordField(PBUF, 0x04, IORL)	//Range Max Base Word
		CreateByteField(PBUF, 0x06, ALMN)	//Alignment
		CreateByteField(PBUF, 0x07, LENG)	//Number of IO ports
		CreateWordField(PBUF, 0x09, IRQL)	//IRQ Mask

		ENFG(CGLD(Arg0))	//Enter Config Mode, Select LDN

	// Write Current Settings into Buffer for IO Descriptor
		Store(IOAH, IOHI)	//Get IO Base MSB
		Store(IOAL, IOLO)	//Get IO Base LSB
		Store(IOHL, IORL)	//Set MaxBase = MinBase
		Store(0x01, ALMN)	//Set alignment
		Store(0x08, LENG)	//Set IO length

	// Write Current Settings into IRQ descriptor
		Store(One, Local0)
		ShiftLeft(Local0, INTR, IRQL)

		EXFG()			//Exit Config Mode
		Return(PBUF)		//Return Byte Stream
	}

//-----------------------------------------------------------------------
// IRSR - Configures new Resources to be decoded by a Device
//
//	Input - Arg0 : PnP Resource String to set
//		Arg1 : Device's category #
//	Return- nothing
//-----------------------------------------------------------------------
	Method(IRSR, 2){
		CreateByteField (Arg0, 0x02, POLB)	//Range Min Base LSB
		CreateByteField (Arg0, 0x03, POHB)	//Range Min Base MSB
		CreateWordField (Arg0, 0x09, PIRQ)	//IRQ number

		ENFG(CGLD(Arg1))	//Enter Config Mode, Select LDN

	// Set Base IO Address
		Store(POLB, IOAL)	//Set IO Base LSB
		Store(POHB, IOAH)	//Set IO Base MSB

	// Set IRQ
		FindSetRightBit(PIRQ, Local0)
		Subtract(Local0, 1, INTR)

		Store(One, ACTR)	//Activate
		EXFG()			//Exit Config Mode
	}

} // End Of IRDA //
