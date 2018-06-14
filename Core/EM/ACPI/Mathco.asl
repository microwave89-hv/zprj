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
// $Header: /Alaska/BIN/Modules/ACPI/Template/Core/Mathco.asl 2     3/26/09 4:53p Oleksiyy $
//
// $Revision: 2 $
//
// $Date: 3/26/09 4:53p $
//**********************************************************************;
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/ACPI/Template/Core/Mathco.asl $
// 
// 2     3/26/09 4:53p Oleksiyy
// New ACPI Core implementation - improves logic, execution time and
// memory usage of ACPI module.
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
//;**********************************************************************;
//-------------------------
// Math Coprocessor Device
//-------------------------
Device(COPR) {
	Name(_HID,EISAID("PNP0C04"))
	Name(_CRS, ResourceTemplate()
	{
		IO(Decode16, 0xf0, 0xf0, 0, 0x10)
		IRQNoFlags(){13}
	})
}	// End of Math Coprocessor
