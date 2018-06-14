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
// $Header: /Alaska/BIN/Modules/ACPI/Template/Core/PS2ms.asl 8     5/07/12 10:50a Oleksiyy $
//
// $Revision: 8 $
//
// $Date: 5/07/12 10:50a $
//**********************************************************************;
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/ACPI/Template/Core/PS2ms.asl $
// 
// 8     5/07/12 10:50a Oleksiyy
// [TAG]  		EIP88686
// [Category]  	Improvement
// [Description]  	Add tokens for _CID and _HID to pass the WHCK
// [Files]  		ACPI.sdl, PS2kb.asl and PS2ms.asl
// 
// 7     3/26/09 4:53p Oleksiyy
// New ACPI Core implementation - improves logic, execution time and
// memory usage of ACPI module.
// 
// 6     4/16/08 12:08p Yakovlevs
// Added 60, 64 resources when KB is not present. 
// 
// 5     4/15/08 9:22p Yakovlevs
// Moved from OEMDSDT device specific 2nd Level wake up control method and
// wake flag
// 
// 4     4/09/08 6:04p Yakovlevs
// 
// 3     4/09/08 5:09p Yakovlevs
// Made _STA return bit set value from \IOST object
// 
// 2     4/03/06 4:05p Felixp
// New Super I/O infrastructure Support
// 
// 1     3/24/05 5:01p Sivagarn
// 
// 1     2/03/05 6:42p Sivagarn
// 0ABHI001 Check in
// 
// 2     9/17/04 12:10p Yakovlevs
// 
// 1     7/27/04 2:48p Yakovlevs
// 
// 6     9/06/02 10:53a Alexp
// Add SourceSafe headers to all core asl files
// 
//
//**********************************************************************;
// PS2 Mouse Device, IO category # - 12
//---------------------------------------------------------------------
Device(PS2M) {

//        Name(_HID, EISAID("PNP0F03"))	// Hardware Device ID - Microsoft mouse
					// check if MSFT Mouse driver supports D3 properly on all MSFT OSes. 
					// It may prevent OS to go to S3 sleep state
					// Use Logitech _HID instead if OS rejecting to go to S3.
        Method(_HID,0){
            Return (\HIDM)
        }
//        Name(_HID, EISAID("PNP0F12"))	// Logitech PS2 Mouse ID
//        Name(_CID, EISAID("PNP0F13"))	// Compatible ID
        Method(_CID,0){
            Return (\CIDM)
        }

        Method(_STA, 0) {
                // Check if PS2Mouse detected in BIOS Post
                // IOST - bit mask of enabled devices, 0x4000 - PS2M mask
                If(And(\IOST, 0x4000)){		// Check if PS2MS detected in BIOS Post
                	Return(0x0f) 
				} else {
					Return(0x00)// device's not present
				}
        }
        Name(CRS1, ResourceTemplate()
        {
                IRQNoFlags(){12}
        })
        Name(CRS2, ResourceTemplate()
	{
		IO(Decode16, 0x60, 0x60, 0, 0x1)
		IO(Decode16, 0x64, 0x64, 0, 0x1)
                IRQNoFlags(){12}
	})
        Method(_CRS,0)
        {
        	If(And(\IOST, 0x0400)){	// PS2K is present, I/O resources 0x60 & 0x64 are reserved there
       		    Return(CRS1)
		} else {	        // single PS/2 mouse(no PS/2 kbd), need to supply I/O resources 0x60 & 0x64 for PS/2 Controller.
		    Return(CRS2)
		}
   	}

//-----------------------------------------------------------------------
//NOTE: _PRS MUST be the NAME not a METHOD object 
//to have GENERICSIO.C working right! 
//-----------------------------------------------------------------------
	Name(_PRS, ResourceTemplate(){
		StartDependentFn(0, 0) { 
			IRQNoFlags(){12} 
		}
		EndDependentFn()
	})

	// Mouse 2nd Level wake up control method
	Method(_PSW, 1){
		Store(Arg0, \MSFG)
	}

}// End of PS2M

Scope(\){
	Name(\MSFG, 0x01)	//Mouse wake-up flag default enable
}
