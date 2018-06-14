// OEM DSDT file. Main ASL Board specific file. 
//**********************************************************************;
//**********************************************************************;
//**********************************************************************;
//**                                                                  **;
//**      (C)Copyright 1985-2005, American Megatrends, Inc.           **;
//**                                                                  **;
//**                     All Rights Reserved.                         **;
//**                                                                  **;
//**           6145-F Northbelt Pkwy, Norcross, GA 30071              **;
//**                                                                  **;
//**                     Phone (770)-246-8600                         **;
//**                                                                  **;
//**********************************************************************;
//**********************************************************************;
//**********************************************************************;
// $Header: /Alaska/BIN/Modules/ACPI/Template/Board/oemDSDT.asl 23    4/04/11 1:44p Yakovlevs $
//
// $Revision: 23 $
//
// $Date: 4/04/11 1:44p $
//
//****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/ACPI/Template/Board/oemDSDT.asl $
// 
// 23    4/04/11 1:44p Yakovlevs
// [TAG]  		EIP55906 
// [Category]  	Improvement
// [Description]  	Can the _INI Method in BOARD\EM\ACPI\oemDSDT.asl be
// Removed 
// [Files]  		OemDsdt.asl
// 
// 22    9/28/09 6:40p Yakovlevs
// Changes to support Multy Root resource reporting features.
// All PCI ROOT resource reporting features moved to RbRes.asl
// 
// 21    5/14/09 6:19p Yakovlevs
// 
// 20    4/15/08 8:59p Yakovlevs
// Keybord and Mouse specific mehods were moved in PS2K.ASL and PS2MS.ASL
// 
// 2     5/20/07 8:09p Yakovlevs
// 
// 19    3/23/07 10:52a Yakovlevs
// 
// 18    12/31/06 2:49p Yakovlevs
// Moved Chipset Specific Code to the SB module
// 
// 17    2/16/06 10:01a Felixp
// 
// 15    1/25/06 11:55a Felixp
// 
// 11    12/05/05 10:04a Yakovlevs
// 
// 10    11/04/05 5:49p Yakovlevs
// Rearrange resources and resolve resource conflicts
// 
// 9     10/07/05 2:52p Markw
// Improved calling sequence of invoking methods.  
// 
// 8     9/29/05 4:13p Markw
// Fix by Sergiy for video to turn on when Windows wakes up.
// 
// 7     8/03/05 7:49a Felixp
// breakpoint is commented out
// 
// 6     5/31/05 12:13p Yakovlevs
// 
// 5     5/24/05 7:29p Yakovlevs
// 
// 4     5/18/05 12:06p Yakovlevs
// 
// 3     5/05/05 6:42p Yakovlevs
// 
// 2     5/05/05 6:39p Yakovlevs
// 
// 1     4/26/05 11:50a Markw
// 
// 2     3/24/05 5:13p Sivagarn
// Code cleanup
// 
// 1     3/24/05 5:00p Sivagarn
// 
//****************************************************************************

//----------------------------------------------------------------------
// List of mandatory ASL objects to be defined in this file:
// \_SB.PCI0._CRS Root PCI0 Bus (Compatibility bus) Current Resources
// \_PTS METHOD CALLED BY OS PRIOR TO ENTER ANY SLEEP STATE
// \_WAK METHOD CALLED ON WAKE UP FROM ANY SLEEP STATE
//----------------------------------------------------------------------


//----------------------------------------------------------------------
// List of global variables defined in amlUpd.asl
//----------------------------------------------------------------------
// File defines OperationRegion "BIOS" and Field names that refer to the AML-BIOS POST data exchange memory area
// Names MG1B, MG1L, MG2B, MG2L

//----------------------------------------------------------------------
// List of global variables and Control Methods defined in aslLIB.asl
//----------------------------------------------------------------------
// RRIO(4) & rDMA(3). Dummy control methods. Required when I/O Positive decoding is disabled
// OSFL(). Control Method. Rreturn value is used to distinguish the currently running OS
// PICM. Global Name. Returns current Interrupt controller mode; updated from _PIC control method
// MCTH(Str1, Str2). Control Method. Compares Str1 and Str2. Return Zero if strings are different.
// GPRW(Package(x,y)) Generic Wake up Control Method to detect the Max Sleep State available in ASL Name scope
//      and Return the Package compatible with _PRW format
// WAKP(Package). Control Method. Returns package compatible with _WAK method
// DBG8 & DBG9 - Debug OperationRegions used to display ASL checkpoints into LED CheckPoint Card

//----------------------------------------------------------------------
// List of global variables and Control Methods defined in PCItree.asl
//----------------------------------------------------------------------
// Processor packages. CPUn, n - CPU ID index. IDs must match to CPU IDs defined within ACPI APIC table(TBLACPI.DAT)
// PCI device scope objects.
// PCI0 - Root PCI Bus device scope
// SBRG - South Bridge device scope (LPC bridge)
// SBRG.xxxx - various Legacy IO devices
// Note. Use "Scope" instruction wherever access to PCI Bridge, South Bridge OR Wake up capable PC device is needed.
//	All PCI devices are defined in PCItree.asl, which is generated by AMISDL utility
//	Naming convention for above generated PCI devices: 
//	PCIx - Root PCI bus and all Peer PCI buses, x - Bus number. 
//	PxPy - PCI to PCI bridge, x - Bus number PCI device is decoded on, y - produced PCI Bus number.
//	Hddf - Hot pluggable Slots, dd - device number, f - function number
//	SBRG - South Bridge PCI device
//-----------------------------------------------------------------------

// Note. AMISDL generates complete PCI Bus device tree based on information provided in SDL.
// 	 All the PCI devices are already defined. Use "Scope(DevName)" directives in order to 
//	 add objects to predefined Devices.


//Scope(\_SB) {				// System Bus scope
//
//	Scope(PCI0) {			// Root PCI0 Bus (Compatibility bus) device scope
//
//		Method(_INI,0) {	// Method to be called once during PCI0 Bus initialization
//			breakpoint
//		}			// Place any Chipset/OEM required init code here
//    }
//}



//<AMI_PHDR_START>
//------------------------------------------------------------------------
//
// Procedure:	_PTS
// Description:	METHOD IS CALLED BY OS PRIOR TO ENTER ANY SLEEP STATE
// Input: Arg0 = Arg0 = Sleep state System about to enter
// Output: Nothing
//
//-------------------------------------------------------------------------
//<AMI_PHDR_END>

	Name (WOTB, 0)
	Name (WSSB, 0)
	Name (WAXB, 0)

	Method(_PTS, 1) {

		Store(Arg0, DBG8)		// DBG8 name translates to IO port 80h
								// DBG8 name defined in aslLib.asl
//breakpoint
		if (LAnd(LEqual(Arg0,4),LEqual(OSFL,2))){Sleep(3000)}

		PTS(Arg0)				// defined in DSDT.ASL (generated by ACPI.MAK)

		Store(0, Index(WAKP,0))		// clear Wake up package.
		Store(0, Index(WAKP,1))		// clear Wake up package.

		Store (ASSB, WSSB)
		Store (AOTB, WOTB)
		Store (AAXB, WAXB)

		Store(Arg0, ASSB)		// Save Sleep Level for BIOS
		Store(OSFL(), AOTB)		// Save OS Type for BIOS
		Store(Zero, AAXB)		// Clear Auxiliary Buffer
		Store(One, \_SB.SLPS)
	}


//<AMI_PHDR_START>
//------------------------------------------------------------------------/
//
// Procedure:	_WAK
// Description:	METHOD CALLED ON WAKE UP FROM ANY SLEEP STATE
// Input: Arg0 = Sleep state System is resuming from
// Output: WAKP - return package for _WAK, 2 DWORDS
//
//-------------------------------------------------------------------------
//<AMI_PHDR_END>

	Method(_WAK, 1)
	{
		ShiftLeft(Arg0, 4, DBG8)	// DBG8 name translates to IO port 80h
//		breakpoint
		WAK(Arg0)			// defined in DSDT.ASL (generated by ACPI.MAK)

		If (ASSB) {
			Store (WSSB, ASSB)
			Store (WOTB, AOTB)
			Store (WAXB, AAXB)
		}

		// WAKP - return package for _WAK, 2 DWORDS
		// 0 - Status
		//     0x00000001 - wake was signaled but failed due to lack of power
		//     0x00000002 - wake was signaled but failed due to thermal condition
		//     other bits are reserved
		// 1 - PSS if non-zero, the effective S-state the Power Supply realy entered

// Example of how to update the wake up status. Default : 0 - no errors encountered during wake up
//		Or(DeRefOf(Index(WAKP,0)), 0,  Index(WAKP,0)) // update wake up status

// update WAKP buffer with resume status

		if(DeRefOf(Index(WAKP,0)))		// non 0 : wake up was terminated
		{
			Store(0, Index(WAKP,1))		
		} else {				// wake up to be completed
			Store(Arg0, Index(WAKP,1))	
		}
		Return(WAKP)

	}




//**********************************************************************;
//**********************************************************************;
//**                                                                  **;
//**      (C)Copyright 1985-2005, American Megatrends, Inc.           **;
//**                                                                  **;
//**                     All Rights Reserved.                         **;
//**                                                                  **;
//**           6145-F Northbelt Pkwy, Norcross, GA 30071              **;
//**                                                                  **;
//**                     Phone (770)-246-8600                         **;
//**                                                                  **;
//**********************************************************************;
//**********************************************************************;
