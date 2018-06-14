// OEM ASL file. Defines ASL Name fields to be linked to AML Exchange bufer location
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
// $Header: /Alaska/BIN/Modules/ACPI/Template/Core/AMLUPD.asl 10    10/14/10 4:59p Oleksiyy $
//
// $Revision: 10 $
//
// $Date: 10/14/10 4:59p $
//
//****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/ACPI/Template/Core/AMLUPD.asl $
// 
// 10    10/14/10 4:59p Oleksiyy
// [TAG]  		EIP46166 
// [Category]  	Improvement
// [Description]  	Fix to made Primary VGA selection on different Root
// Bridges backward compatible with Core 4.6.4.0.
// [Files]  		AMLUPD.asl, RbRes.asl
// 
// 9     9/28/09 6:35p Yakovlevs
// Changes to support Multy Root resource reporting features.
// All PCI ROOT resource reporting features moved to RbRes.asl
// 
// 8     3/26/09 4:53p Oleksiyy
// New ACPI Core implementation - improves logic, execution time and
// memory usage of ACPI module.
// 
// 7     6/28/05 5:22p Yakovlevs
// 
// 6     6/03/05 2:42p Yakovlevs
// 
// 5     5/31/05 12:09p Yakovlevs
// 
// 4     5/27/05 5:57p Yakovlevs
// 
// 3     5/18/05 11:49a Yakovlevs
// 
// 2     5/05/05 7:11p Yakovlevs
// 
// 3     5/05/05 5:39p Yakovlevs
// 
// 2     4/28/05 2:51p Yakovlevs
// 
// 1     4/25/05 10:56a Markw
// 
// 1     3/24/05 5:01p Sivagarn
// 
// 1     2/03/05 6:42p Sivagarn
// 0ABHI001 Check in
// 
// 1     7/27/04 2:48p Yakovlevs
// 
// 8     7/17/02 12:13p Alexp
// Add example of code to report memory above 4GB. Code is commented out.
// 
// 7     6/10/02 11:53a Alexp
// Delete IO APIC related ranges from AMLdata buffer. Use ACPI SDL
// parameters to provide same ranges.
// 
// 6     5/17/02 11:01a Alexp
// Removed several names (SPIO, PMBS,..) as they were defined as static
// equates and can be passed to ASL from SDL outut directly, not using
// Aml_exchange buffer
// 
// 5     3/20/02 11:54a Alexp
// 
// 4     2/26/02 12:16p Alexp
// Update headers to generate proper .chm help
// 
// 3     11/05/01 1:23p Alexp
// Remove Thermal variables from Template AML_Exchange buffer
// 
// 2     11/01/01 9:50a Alexp
// 
//----------------------------------------------------------------------


//;<AMI_THDR_START>
//;------------------------------------------------------------------------/
//;
//; Name:	BIOS
//;
//; Type: OperationRegion
//;
//; Description:	Set of name objects used as an exchange buffer for BIOS to 
//;					pass the System information to AML code
//; 				List of mandatory Name Objects to be defined:
//;					SS1 - SS4 - BIOS setup enabled sleep states.
//; 				MG1B, MG1L - Non-shadowed memory range below 1Mb. Available for PCI0 bus.
//; 				MG2B, MG2L - Memory range above available System memory. Available for PCI0 bus.
//;
//; Notes: Memory location and all Name values are updated in BIOS POST
//; Referrals: AMLDATA
//;-------------------------------------------------------------------------
//;<AMI_THDR_END>

///////////////////////////////////////////////////////////////////////////////////
//Values are set like this to have ASL compiler reserve enough space for objects 
///////////////////////////////////////////////////////////////////////////////////
// Available Sleep states
Name(SS1,1)		// is S1 enabled in setup?
Name(SS2,0)
Name(SS3,1)
Name(SS4,1)
///////////////////////////////////////////////////////////////////////////////////
// Bit mask of statuses of IO peripheral devices, enabled in Setup
//      0x0 - Serial A (Modem)
//        1 - Serial B (IR)
//        2 - LPT
//        3 - FDD
//----------------------------
//        4 - SB16 Audio
//        5 - Midi
//        6 - Mss Audio
//        7 - Adlib sound (FM synth)
//----------------------------
//        8 - Game 1 port
//        9 - Game 2 port
//        a - KBC 60 & 64
//        b - EC 62 & 66
//----------------------------
//		  c - reserved
//		  d	- reserved
//        e - PS2Mouse
//        f - reserved
///////////////////////////////////////////////////////////////////////////////////
Name(IOST,0xFFFF)		// Bit mask of statuses of IO peripheral devices, 
						// enabled in Setup
///////////////////////////////////////////////////////////////////////////////////
Name(TOPM,0xFFFFF)   	// System memory top address below 4GB, bytes

///////////////////////////////////////////////////////////////////////////////////
Name(ROMS,0xffe00000)	// Boot strap BIOS image address at top 4Gbyte

///////////////////////////////////////////////////////////////////////////////////
Name(VGAF, 0x1)         //Flag to indicate Legacy VGA Resources were clamed already

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