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
// $Header: /Alaska/BIN/Modules/ACPI/Template/Core/LM75.ASL 2     3/26/09 4:53p Oleksiyy $
//
// $Revision: 2 $
//
// $Date: 3/26/09 4:53p $
//**********************************************************************;
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/ACPI/Template/Core/LM75.ASL $
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
//;**********************************************************************;
//**********************************************************************;
//              ASL interface to LM75 thermal sensor over SMBus
//**********************************************************************;

// change LM75 trip points
	Method(TCHG, 0) {

	Store(RBYT(TSAD, 0x00), Local0) // Read Current temp
/*
If(LGreaterEqual(Local0,TMAX)) {
			Store(TCRT, Local1) 	// Tcrt
			}
	Else	{
	If(LGreaterEqual(Local0,TMIN)) {
			Store(TMAX, Local1) 	// Thigh
			}
		Else {
		Store(TMIN, Local1)		// TLow
		}
	}
	STOS(0,Local1)			// Set Thigh

	STHY(0, Add(Local0, 2))		// Set TLow T + 2.0C to arm the Thermal int

//	Subtract(TMIN, 5, Local2)	// Set Thyst as TMIN-5.0

//	Add(Local0, 0x5, Local1)	// Set Thigh T + 5.0 C
	Subtract(Local0, 0x1, Local2)	// Set Tlow  T - 1.0 C
	Subtract(TMIN, 0x5, Local3)	// Set Tlow  TMIN - 5.0 C
//	If(LGreater(Local2,Local3))
//	{
//		Store(Local3, Local2)
//	}

	STHY(0,Local2)                  // Set TLow
*/
	STOS(TCRT)			// Set Thigh TCRT
	STHY(Subtract(Local0, 5))	// Set TLow TMIN-5.0C

	Notify(\_TZ.THRM, 0x81)		// Notify of trip point change
        }

// Set configuration register
Method(SCFG, 1) {
	// Arg0 = configuration byte

	WBYT(TSAD, 0x01, Arg0)
	}

// Set Tos register

Method(STOS, 1) {
	// Arg0 = temperature word data

	// Set pointer register (occupy the command byte) to 0x03
	// Somehow LM75 wants to send out the MSB byte first !

	WWRD(TSAD, 0x03, Arg0)
	}

// Set Thyst register

Method(STHY, 1) {
	// Arg0 = temperature word data

	// Set pointer register (occupy the command byte) to 0x02
	// Somehow LM75 wants to send out the MSB byte first !

	WWRD(TSAD, 0x02, Arg0)
	}

// Read temperature register

Method(RTMP, 0) {
	// Set pointer register (occupy the command byte) to 0x00

	Store(RWRD(TSAD, 0x00), Local0)

Store(Local0, DBG8)

	// Somehow LM75 returns right byte first!

	If(Not(Local0)) 	// Read command completed
	{
		Return( Local0 )
	}
	Else 			// Read command failed
	{
		Store("_TMP Read ERROR", Debug)
		Return(Add(TMIN, 2))	// MIN trip point + 2.0 C
	}

	} // Method(RTMP)

// LM75 Thermal interrupt handler
Method(THDL,0) {
//**********************************************************************;
// Trip point handler
// TPOL status bit applys for PIIX4 based design only
// PMBS is an ACPI I/O Base address
// PM controller IO space
        OperationRegion(PMRG, SystemIO, PMBS, 0x40)
        Field(PMRG,ByteAcc,NoLock,Preserve)
        {
        Offset(0x28),
        ,2,
        TPOL,1,         // 28.2h Thermal Polarity bit
        }

	If(TPOL)
// Temp goes up, Tos threshold being crossed
	{
		\GFAN._ON()  	// Turn FAN On
	}
	Else
// Temp goes down, Thyst threshold being crossed
	{
		\GFAN._OFF()	// Turn FAN Off
	}

	TCHG()			// Reevaluate Thigh/TLow for LM75
	Not(TPOL,TPOL)		// Toggle the Polarity pin
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
//**********************************************************************;
//		DON'T CHANGE ANY CODE UNLESS REQUIRED !!!
//**********************************************************************;
