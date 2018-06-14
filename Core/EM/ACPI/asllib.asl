// ASL generic library objects
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             5555 Oakbrook Pkwy, Norcross, GA 30093               **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
// $Header: /Alaska/BIN/Modules/ACPI/Template/Core/asllib.asl 10    6/04/13 4:39p Oleksiyy $
//
// $Revision: 10 $
//
// $Date: 6/04/13 4:39p $
//**********************************************************************;
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/ACPI/Template/Core/asllib.asl $
// 
// 10    6/04/13 4:39p Oleksiyy
// [TAG]  		EIP125640
// [Category]  	Improvement
// [Description]  	Adding Win 8.1 to the OS list in OSFL method.
// [Files]  		asllib.asl
// 
// 9     7/20/12 5:00p Oleksiyy
// [TAG]  		EIP92404
// [Category]  	Improvement
// [Description]  	ACPI method _OSI("Linux") should no longer be used
// [Files]  		asllib.asl
// 
// 8     4/10/12 6:23p Oleksiyy
// [TAG]  		EIP87370
// [Category]  	Improvement
// [Description]  	Operation System Vendor String for Win8
// [Files]  		asllib.asl
// 
// 7     9/29/09 5:06p Oleksiyy
// EIP 20586: RRIO and rDMA methods removed. They are implemented in
// SB.asl file.
// 
// 6     9/08/09 11:16a Yakovlevs
// Fixed issue in OSVR detection. Because of "ElseIf" statement it use to
// return  wrong (Lovest) value.
// 
// 4     3/26/09 4:53p Oleksiyy
// New ACPI Core implementation - improves logic, execution time and
// memory usage of ACPI module.
// 
// 3     5/24/06 3:50p Ambikas
// 
// 2     5/05/05 7:10p Yakovlevs
// 
// 1     3/24/05 5:01p Sivagarn
// 
// 1     2/03/05 6:42p Sivagarn
// 0ABHI001 Check in
// 
// 1     7/27/04 2:48p Yakovlevs
// 
// 18    1/22/03 3:38p Alexp
// Modify GPRW() method
// 
// 17    1/15/03 6:09p Alexp
// GPRW-> modify code to make use of Sleep State Bit mask field inside
// BIOS OpRegion. 
// 
// 16    10/08/02 10:44a Mirk
// missing bracket in OSFL method
// 
// 15    10/08/02 10:38a Mirk
// Display proper cp ACPI in PIC mode : AC and for APIC mode : AA
// 
// 14    9/20/02 10:04a Alexp
// Uncomment code to store detected WinME to OSFL OS flag. 
// 
// 13    9/06/02 10:53a Alexp
// Add SourceSafe headers to all core asl files
// 
//
//;**********************************************************************;
//              File to be included to root ASL scope of DSDT.ASL
//**********************************************************************;
// 1. RRIO(4) & rDMA(3) Dummy control methods. Required when I/O Positive decoding's disabled
// 2. Name PICM - Global Name returns current Interrupt controller mode; updated from _PIC control method
// 3. Method _PIC(1) - Updates PICM with current Interrupt controller mode
// 4. Method MCTH(Str1, Str2) - Compare Str1 and Str2.
// 5. Method GPRW(Package(x,y)) Generic Wake up Control Method to detect the Max Sleep State available in ASL Name scope
//      and Return the Package compatible with _PRW format
// 6. Method WAKP(Package) - Return package for _WAK method
// 7. Debug OperationRegions used to display ASL checkpoints int LED CheckPoint Card
//----------------------------------------------------------------------

/*
;<AMI_PHDR_START>
;------------------------------------------------------------------------
;
; Procedure:	_PIC
;
; Description:	Interrupt mode Control method, returns current Interrupt controller mode; updated from _PIC control method
;		OS invokes _PIC to notify ASL of current Interrupt controller mode
; 		_PIC Input arguments : 0-PIC mode (Default), 1-APIC mode
;  Input: Arg0 - Interrupt mode 
;  Output: Nothing
;
;-------------------------------------------------------------------------
;<AMI_PHDR_END>
*/
	Name(PICM, 0)	// Global Name, returns current Interrupt controller mode; updated from _PIC control method
//  OS invokes _PIC to notify ASL of current Interrupt controller mode
// _PIC Input arguments : 0-PIC mode (Default), 1-APIC mode
	Method(_PIC, 1) { 
		if(Arg0) {
			Store(0xAA, DBG8)	// APIC
		} else {
			Store(0xAC, DBG8)	 // PIC
		}
		Store(Arg0, PICM) 
	}

/*
;<AMI_PHDR_START>
;------------------------------------------------------------------------
;
; Procedure:	OSFL
;
; Description:	OSFL object is used to detect the currently running OS
; Input: Nothing
; Output: OS type
; running under 0 - Win 2000
;               1 - Win 98/Se
;               2 - Win Me
;               3 - Linux
;				4 - WinXP
;				5 - Windows Server 2003				
;				6 - FreeBSD		
;				7 - HP-UX
;				8 - OpenVMS		
;-------------------New Values Added -----------------------------
;               9 - WinXP SP1
;              10 - WinXP SP2
;              11 - WinXP SP3    
;              12 - Vista
;              13 - Vista SP1
;              14 - Win7   
;              15 - Win8  
;              16 - Win8.1            
;   17..n - reserved
;
;-------------------------------------------------------------------------
;<AMI_PHDR_END>
*/
	Name(OSVR, Ones)					// Global Name, returns current OS version ID
	Method(OSFL, 0){
		if(LNotEqual(OSVR, Ones)) {Return(OSVR)}	// OS version was already detected
		if(LEqual(PICM,0)) {Store(0xAC, DBG8)}		// to indicate OS is running in ACPI PIC mode
		Store(3, OSVR)					// default - Linux
//// Detect currently running OS
		if(CondRefOf(\_OSI,Local0))
		{
			//If(\_OSI("Linux")){Store(3, OSVR)}	// Tested on the Redhat Linux
			If(\_OSI("Windows 2001")){Store(4, OSVR)}
			If(\_OSI("Windows 2001.1")){Store(5, OSVR)}		
			If(\_OSI("FreeBSD")){Store(6, OSVR)}
			If(\_OSI("HP-UX")){Store(7, OSVR)}
			If(\_OSI("OpenVMS")){Store(8, OSVR)}
            If(\_OSI("Windows 2001 SP1")){Store(9,OSVR)}
            If(\_OSI("Windows 2001 SP2")){Store(10,OSVR)}
            If(\_OSI("Windows 2001 SP3")){Store(11,OSVR)}
            If(\_OSI("Windows 2006")){Store(12,OSVR)}
            If(\_OSI("Windows 2006 SP1")){Store(13,OSVR)}
            If(\_OSI("Windows 2009")){Store(14,OSVR)}
            If(\_OSI("Windows 2012")){Store(15,OSVR)}
            If(\_OSI("Windows 2013")){Store(16,OSVR)}
		} else {
			If(MCTH(\_OS,"Microsoft Windows NT")){Store(0, OSVR)}
			If(MCTH(\_OS,"Microsoft Windows")){Store(1, OSVR)}
			If(MCTH(\_OS,"Microsoft WindowsME: Millennium Edition")){Store(2, OSVR)}
			If(MCTH(\_OS,"Linux")){Store(3, OSVR)}	// Tested on the Redhat Linux
			If(MCTH(\_OS,"FreeBSD")){Store(6, OSVR)}
			If(MCTH(\_OS,"HP-UX")){Store(7, OSVR)}
			If(MCTH(\_OS,"OpenVMS")){Store(8, OSVR)}
		}
		Return(OSVR)
	}

/*
;<AMI_PHDR_START>
;-------------------------------------------------------------------------
;
; Procedure:	MCTH
;
; Description:	Generic control Method. Used to compare two strings and return TRUE/FALSE result
;		MCTH(Str1, Str2) - Compare Str1 and Str2.
; Input: Arg0 - str1, Arg1 - str2
; Output: string comparison result
;        One if Str1 == Str2
;        Zero if Str1 != Str2
;-------------------------------------------------------------------------
;<AMI_PHDR_END>
*/
	Method(MCTH, 2) {
//1. If Length str1 < Str2 - Return (Zero)
		If(LLess(Sizeof(Arg0), Sizeof(Arg1)))
		{
			Return(Zero)
		}
//2. Convert str1 & str2 into buffer with length of str2
		Add(Sizeof(Arg0), 1, Local0)
// Local0 contains length of string + NULL character.
		Name(BUF0, Buffer(Local0) {})
		Name(BUF1, Buffer(Local0) {})
		Store(Arg0, BUF0)
		Store(Arg1, BUF1)
		While(Local0)
		{
			Decrement(Local0)
			If(LNotEqual(Derefof(Index(BUF0, Local0)), Derefof(Index(BUF1, Local0))))
			{ Return(Zero) }
		}
		Return(One)		// Str1 & Str2 are match
	}

/*
;<AMI_PHDR_START>
;------------------------------------------------------------------------
;
; Procedure:	GPRW
;
; Description:	Generic Wake up Control Method ("Big brother") to detect the Max Sleep State available in ASL Name scope
;		and Return the Package compatible with _PRW format.
; Input: Arg0 =  bit offset within GPE register space device event will be triggered to
;        Arg1 =  Max Sleep state, device can resume the System from
;             If Arg1 = 0 , Update Arg1 with Max _Sx state enabled in the System
; Output: _PRW package
;
;-------------------------------------------------------------------------
;<AMI_PHDR_END>
*/
	Name(PRWP, Package(){Zero, Zero})		// _PRW Package
	Method(GPRW, 2)
	{
		Store(Arg0, Index(PRWP, 0))		// copy GPE#
// SS1-SS4 - enabled in BIOS Setup Sleep states
                Store(ShiftLeft(SS1,1),Local0)      	// S1 ?
                Or(Local0,ShiftLeft(SS2,2),Local0)      // S2 ?
                Or(Local0,ShiftLeft(SS3,3),Local0)      // S3 ?
                Or(Local0,ShiftLeft(SS4,4),Local0)      // S4 ?
// Local0 has a bit mask of enabled Sx(1 based)
							// bit mask of enabled in BIOS Setup Sleep states(1 based)
		If(And(ShiftLeft(1, Arg1), Local0)){	// Requested wake up value (Arg1) is present in Sx list of available Sleep states
			Store(Arg1, Index(PRWP, 1))	// copy Sx#
		} Else {  				// Not available -> match Wake up value to the higher Sx state
			ShiftRight(Local0, 1, Local0)	
			If(LOr(LEqual(OSFL, 1), LEqual(OSFL, 2))) { 	// ??? Win9x
				FindSetLeftBit(Local0, Index(PRWP,1))	// Arg1 == Max Sx
			} Else { 					// ??? Win2k / XP
				FindSetRightBit(Local0, Index(PRWP,1))	// Arg1 == Min Sx
			}
		}
	Return(PRWP)
	}

/*
;<AMI_PHDR_START>
;------------------------------------------------------------------------
;
; Procedure:	WAKP
;
; Description:	Return package for _WAK method. Contains 2 DWORDS
; 0 - Status
;           0x00000001 - wake was signaled but failed due to lack of power
;           0x00000002 - wake was signaled but failed due to thermal condition
;           other bits are reserved
; 1 - PSS      if non-zero, the effective S-state the Power Supply realy entered
; Output: _WAK return package
;-------------------------------------------------------------------------
;<AMI_PHDR_END>
*/
// Return package for _WAK method 2 DWORDS
	Name(WAKP, Package(){Zero, Zero})

//--------------------------//
// Debug output registers   //
//--------------------------//

/*
;<AMI_PHDR_START>
;------------------------------------------------------------------------
; Procedure:	DBG8
; Procedure:	DBG9
; Description:	Logical names for Debug ports 0x80 (byte) and 0x90(word). 
;		If such debug ports exist in the System, the value, stored into the Port will be displayed to LED
; Input: Nothing
; Output: Nothing
;-------------------------------------------------------------------------
;<AMI_PHDR_END>
*/

	OperationRegion (DEB0, SystemIO, 0x80, 1)
	Field (DEB0, ByteAcc,NoLock,Preserve)
	{ DBG8,8,}

	OperationRegion (DEB1, SystemIO, 0x90, 2)
	Field (DEB1, WordAcc,NoLock,Preserve)
	{ DBG9,16,}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             5555 Oakbrook Pkwy, Norcross, GA 30093               **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
