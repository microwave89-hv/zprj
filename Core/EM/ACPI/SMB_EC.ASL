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
// $Header: /Alaska/BIN/Modules/ACPI/Template/Core/SMB_EC.ASL 2     3/26/09 4:53p Oleksiyy $
//
// $Revision: 2 $
//
// $Date: 3/26/09 4:53p $
//**********************************************************************;
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/ACPI/Template/Core/SMB_EC.ASL $
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
// 2     9/06/02 10:53a Alexp
// Add SourceSafe headers to all core asl files
// 
//
//**********************************************************************;
//**********************************************************************;
//		DON'T CHANGE ANY NAMES UNLESS REQUIRED !!!
//**********************************************************************;
//     ACPI Embedded controller SMBus interface methods
//**********************************************************************;

// SMBR - SMBus read method
//
//	Arg0 - Device address
// 	Arg1 - Command Code
//	Arg2 - Data to write
//	Arg3 - Protocol (basically RDWD, WRWD or RDBL)

        Method(SMBR,4) {
                If (LEqual(Arg3,RDBL)) {Store(0,DATB)}
        	Store(5, Local0)
        	While(Local0) {
        		Store(Arg0, ADDR)	// Set the device address
        		Store(Arg1, SCMD)	// Read Power unit value 0x3 offset
			If (LEqual(Arg3, WRWD))	{Store(Arg2, DAT0)}
        		Store(Arg3, PRTC)       // Set protocol - start SMBus transaction
        		Wait(SMBF, 0xFFF)	// Wait till SMBus transaction completed

        		Reset(SMBF)

// One of known problems - ReadBlock of GLW SmartBattery may return BCNT=3
// and data as FF FF FF with no any SMBus errors. To avoid this:
//        		If(Or(SSTS,And(LEqual(Arg2,RDBL),And(LEqual(BCNT,3),LEqual(DAT0,0xFFFF)))))
			If(SSTS)
				{Decrement(Local0)}  // If any SMBus error

                	Else {
				Return(Ones)	// exit on OK
                        }
        	}
		Return(Zero)			// exit on failure
        }

//**********************************************************************;
//     *****************************************************************;
//     *****************************************************************;
//     **                                                             **;
//     **      (C)Copyright 1985-1996, American Megatrends, Inc.      **;
//     **                                                             **;
//     **                     All Rights Reserved.                    **;
//     **                                                             **;
//     **           6145-F Northbelt Pkwy, Norcross, GA 30071         **;
//     **                                                             **;
//     **                     Phone (770)-246-8600                    **;
//     **                                                             **;
//     *****************************************************************;
//     *****************************************************************;
