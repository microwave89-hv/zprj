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
// $Header: /Alaska/BIN/Modules/ACPI/Template/Core/MAX1617R.ASL 2     3/26/09 4:53p Oleksiyy $
//
// $Revision: 2 $
//
// $Date: 3/26/09 4:53p $
//**********************************************************************;
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/ACPI/Template/Core/MAX1617R.ASL $
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
//              ASL interface to MAX1617 thermal sensor over SMBus
//                      Remote sensor
//**********************************************************************;

// change max1617 trip point
/*
// Original TCHG method
	Method(TCHG, 0) {

	Store(RBYT(TSAD, 0x01), Local0) // Read remote Current temp

	Add(Local0, 0x5, Local1)	// Set Thigh T + 5.0 C

	Subtract(Local0, 0x5, Local2)	// Set Tlow  T - 5.0 C
//	Subtract(Local0, 0x2, Local2)	// Set Tlow  T - 2.0 C

	Subtract(TMIN, 0x5, Local3)	// Set Tlow  TMIN - 5.0 C
//	If(LGreater(Local2,Local3))
//			{Store(Local3,Local2)}

	STOS(Local1)		// Set Thigh
	STHY(Local2)		// Set Tlow
					// Clear ALARM bit
		Notify(\_TZ.THRM, 0x81)		// Notify of trip point change
	}
*/
// Customized Method
	Method(TCHG, 0) {

	Store(RBYT(TSAD, 0x07), Local0)	// remote high limit
	Store(RBYT(TSAD, 0x08), Local1)	// remote low limit
	Store(RBYT(TSAD, 0x01), Local2)	// remote current temp
	RBYT(TSAD, 0x02)		// Read status byte
	if( LGreaterEqual(Local2,Local0) ) {
		// High limit alert
		if( LEqual(Local0, TMIN) ) {
			// Set TMAX to high limit & TMIN-2 to low limit
			STOS(TMAX)		// Set Thigh to TMAX
			Subtract(TMIN, 2, Local3)
			STHY(Local3)		// Set Tlow to TMIN-2
		}
		else {
			if( LEqual(Local0, TMAX) ) {
				// Set TCRT to high limit & TMAX-2 to low limit
				STOS(TCRT)		// Set Thigh to TCRT
				Subtract(TMAX, 2, Local3)
				STHY(Local3)		// Set Tlow to TMAX-2
			}
			else {
				if( LEqual(Local0, TCRT) ) {
					// Notify OS to shutdown
					// Set Extreeme high to high limit & TCRT-2 to low limit
					STOS(0x7f)		// Set Thigh to extreeme high (127C)
					Subtract(TCRT, 2, Local3)
					STHY(Local3)		// Set Tlow to TCRT-2
				}
//				else {
//					// This from init. set TMIN to high & Extreeme to low limit
//					STOS(TMIN)		// Set Thigh to TMIN
//					STHY(0xc9)		// Set Tlow to extreeme low (-55C)
//				}
			}
		}
	}
	else {
		if( LLessEqual(Local2, Local1) ) {
			// Low limit alert
			if( LLess(Local1, TMIN) ) {
				// Set TMIN to high limit & Extreeme to low limit
				STOS(TMIN)		// Set Thigh to TMIN
				STHY(0xc9)		// Set Tlow to extreeme low (-55C)
			}
			else {
				if( LLess(Local1, TMAX) ) {
					// Set TMAX to high limit & TMIN-2 to low limit
					STOS(TMAX)		// Set Thigh to TMAX
					Subtract(TMIN, 2, Local3)
					STHY(Local3)		// Set Tlow to TMIN-2
				}
				else {
					if( LLess(Local1, TCRT) ) {
						// Set TCRT to high limit & TMAX-2 to low limit
						STOS(TCRT)		// Set Thigh to TCRT
						Subtract(TMAX, 2, Local3)
						STHY(Local3)		// Set Tlow to TMAX-2
					}
//					else {
//						// This from init. set TMIN to high & Extreeme to low
//						STOS(TMIN)		// Set Thigh to TMIN
//						STHY(0xc9)		// Set Tlow to extreeme low (-55C)
//					}
				}
			}
		}
	}


	RBYT(TSAD, 0x02)		// Read status byte after limit changes
	RSBT(0x19, 0) 	         	// Receive Byte, Addr 0x18
	Notify(\_TZ.THRM, 0x81)			// Notify of trip point change
	}

// Set configuration register #0x9
Method(SCFG, 1) {
	// Arg0 = configuration byte

	WBYT(TSAD, 0x09, Arg0)
 }

// Read Status Byte
Method(RSTS, 0) {
	// Arg0 = configuration byte

	Return(RBYT(TSAD, 0x02))
 }

// Set remote Thigh register #0x0d
Method(STOS, 1) {
	// Arg0 = temperature low byte

	// Set pointer register (occupy the command byte) to 0x0d
	// Somehow max1617 wants to send out the MSB byte first !

	 WBYT(TSAD, 0x0d, Arg0)
 }

// Set remote Tlow register #0x0e
Method(STHY, 1) {
	// Arg0 = temperature low byte

	// Set pointer register (occupy the command byte) to 0x0C
	// Somehow max1617 wants to send out the MSB byte first !

	WBYT(TSAD, 0x0e, Arg0)
 }

// Read remote temperature register
Method(RTMP, 0) {
	// Set pointer register (occupy the command byte) to 0x00
	// DATW, DB00 and DB01 are defined as global buffer fields

	Store(RBYT(TSAD, 0x01), Local0)

Store(Local0, DBG8)

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

// MAX1617 Thermal interrupt handler
Method(THDL,0) {
//**********************************************************************;
					// Clear ALARM bit
	RSBT(0x19, 0)          	// Receive Byte, Addr 0x18
	TCHG()			// change Trip points
//**********************************************************************;
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
