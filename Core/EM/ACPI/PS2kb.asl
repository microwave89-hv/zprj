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
// $Header: /Alaska/BIN/Modules/ACPI/Template/Core/PS2kb.asl 10    5/07/12 10:49a Oleksiyy $
//
// $Revision: 10 $
//
// $Date: 5/07/12 10:49a $
//**********************************************************************;
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/ACPI/Template/Core/PS2kb.asl $
// 
// 10    5/07/12 10:49a Oleksiyy
// [TAG]  		EIP88686
// [Category]  	Improvement
// [Description]  	Add tokens for _CID and _HID to pass the WHCK
// [Files]  		ACPI.sdl, PS2kb.asl and PS2ms.asl
// 
// 9     2/09/12 2:08p Oleksiyy
// [TAG]  		EIP82016
// [Category]  	Improvement
// [Description]  	Change ASL macro FixedIO to IO
// [Files]  		PS2kb.asl and GenericSio.c
// 
// 8     3/26/09 4:53p Oleksiyy
// New ACPI Core implementation - improves logic, execution time and
// memory usage of ACPI module.
// 
// 7     4/16/08 12:09p Yakovlevs
// Changed 0x60 0x64 resources to clame 16 bit IO.
// 
// 6     4/15/08 9:25p Yakovlevs
// Moved from OEMDSDT device specific 2nd Level wake up control method and
// wake flag
// 
// 5     4/09/08 6:05p Yakovlevs
// 
// 4     4/09/08 5:10p Yakovlevs
// 
// 3     4/03/06 4:05p Felixp
// New Super I/O infrastructure Support
// 
// 2     7/12/05 10:57a Girim
// Updated and Cleaned up the code.
// 
// 1     3/24/05 5:01p Sivagarn
// 
// 1     2/03/05 6:42p Sivagarn
// 0ABHI001 Check in
// 
// 1     7/27/04 2:48p Yakovlevs
// 
// 4     9/06/02 10:53a Alexp
// Add SourceSafe headers to all core asl files
// 
//
//**********************************************************************;
// PS2 Keyboard Device, IO category # - 10
//---------------------------------------------------------------------


Device(PS2K) {
    //Name(_HID,EISAID("PNP0303"))        // Standard Keyboard 101/102
        Method(_HID,0){
            Return (\HIDK)
        }

    //Name(_CID,EISAID("PNP030b"))        // Compatible ID, PC/AT Enhanced Keyboard 101/102
        Method(_CID,0){
            Return (\CIDK)
        }

    Method(_STA,0) {
		If(And(\IOST, 0x0400)){
			Return (0x0F)
		} else {
			Return (0x00)
		}
	}

    Name(_CRS,ResourceTemplate()
    {
        IO(Decode16, 0x60, 0x60, 0, 0x1)    //PS2 resource
		IO(Decode16, 0x64, 0x64, 0, 0x1)
		IRQNoFlags(){1}
    })

//-----------------------------------------------------------------------
//NOTE: _PRS MUST be the NAME not a METHOD object 
//to have GENERICSIO.C working right! 
//-----------------------------------------------------------------------
	Name(_PRS, ResourceTemplate(){
		StartDependentFn(0, 0) {  
            IO(Decode16, 0x60, 0x60, 0, 0x1)  
            IO(Decode16, 0x64, 0x64, 0, 0x1)
			IRQNoFlags(){1}
		}
		EndDependentFn()
	})

	// Keyboard 2nd Level wake up control method
	Method(_PSW, 1){
		Store(Arg0, \KBFG)
	}

}// End of PS2K

Scope(\){
	Name(\KBFG, 0x01)	//Keyboard wake-up flag default enable
}
