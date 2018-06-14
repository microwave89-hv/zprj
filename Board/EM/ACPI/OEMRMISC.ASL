// THIS FILE IS INCLUDED to South Bridge device scope
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
// $Header: /Alaska/BIN/Modules/ACPI/Template/Board/OEMRMISC.ASL 6     3/26/09 4:55p Oleksiyy $
//
// $Revision: 6 $
//
// $Date: 3/26/09 4:55p $
//****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/ACPI/Template/Board/OEMRMISC.ASL $
// 
// 6     3/26/09 4:55p Oleksiyy
// New ACPI Core implementation - improves logic, execution time and
// memory usage of ACPI module.
// 
// 1     2/18/09 3:50p Oleksiyy
// 
// 5     4/13/07 4:19p Yakovlevs
// 
// 4     12/12/05 9:26p Yakovlevs
// comments changed
// 
// 3     11/04/05 5:48p Yakovlevs
// Rearrange resources and resolve resource conflicts
// 
// 2     3/24/05 5:13p Sivagarn
// Code cleanup
// 
// 1     3/24/05 5:00p Sivagarn
// 
//****************************************************************************


//-----------------------------------------------------------------------
// Any OEM Specific ISA control code to be defined in this file
//-----------------------------------------------------------------------
//<AMI_PHDR_START>
//------------------------------------------------------------------------
//
// Procedure:	OMSC
//
// Description:	OEM Miscellaneous I/O and memory resources
// This table should contain any I/O port that is not used by a specific
// device but does not return FFh when read.  Some examples of I/O ports
// that should be reserved here are:
//   Any I/O port in the range 00 - FF that is not used by any other dev node
//   The IRQ edge/level control ports (4D0/4D1)
//
//  Input: Nothing
//
//  Output: _CRS buffer
//
//-------------------------------------------------------------------------
//<AMI_PHDR_END>

	Device(OMSC) {

		Name(_HID, EISAID("PNP0C02"))	// System board resources device node ID
		Name(_UID, 0x0E11)			// Unique ID. 
//S.Y !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//All these resources has been moved to SB ASL

//		Name(CRS, ResourceTemplate() {
// GP I/O space(if applicable)
//			IO(Decode16, 0, 0, 0, 0, IO1)
// Base Address I/O APIC
//			Memory32Fixed(ReadOnly, 0x00000, 0x0, ME01 )	//Non-writeable
// Base Address local APIC (boot strap CPU)
//			Memory32Fixed(ReadOnly, 0x00000, 0x0, ME02 )	//Non-writeable
//		}		// End of ResourceTemplate
//		)		// end of CRS

//		Method (_CRS, 0)
//		{
// GPIO,GPIL - General purpose I/O Base addfress & length
//			If(GPIO)
//			{
//				CreateWordField(CRS, ^IO1._MIN, GP10) // GPIO 1 Base
//				CreateWordField(CRS, ^IO1._MAX, GP11)
//				CreateByteField(CRS, ^IO1._LEN, GP1L) // GPIO length
//				Store(GPIO, GP10)	// Min Base address
//				Store(GPIO, GP11)	// Max Base address
//				Store(GPIL, GP1L)	// Region length
//			}
// Reserve IO & Local APIC memory ranges only if IO APIC is decoded/enabled
// APCB,APCL - on chip I/O APIC Base address & region length
//			If(APCB)
//			{
//				CreateDwordField(CRS, ^ME01._LEN, ML01)
//				CreateDwordField(CRS, ^ME01._BAS, MB01)
//				CreateDwordField(CRS, ^ME02._LEN, ML02)
//				CreateDwordField(CRS, ^ME02._BAS, MB02)
//				Store(APCB, MB01)	// Base address I/O APIC
//				Store(APCL, ML01)	// Region length
//				Store(0xFEE00000, MB02)	// Base address Local APIC
//				Store(0x1000, ML02)	// Region length
//			}
//			Return(CRS)
//		}//	End _CRS
//S.Y !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!



	}

//-----------------------------------------------------------------------
// System board extension Device node for ACPI BIOS
//-----------------------------------------------------------------------

//<AMI_PHDR_START>
//------------------------------------------------------------------------
//
// Procedure:	RMEM
//
// Description:	System board extension Device node for ACPI BIOS
// Place the device under \_SB scope, As per Msft the MEM
// Device is used to reserve Resources that are decoded out of PCI Bus
// Important consideration :
// Logic to reserve the memory within 0xC0000 - 0xFFFFF Extended BIOS area is based on assumption, that
// the BIOS Post has detected all expansion ROMs in the region and made their memory ranges
// shadowable ( copied to RAM at the same address, for performance reasons). The rest of the region is left non-Shadowable,
// hence no memory is decoded there. Such region is decoded to PCI bus (to be reserved in PCI0._CRS)
// Whatever memory is Shadowed, thus, decoded as non "FF"s, is required to be reserved in "SYSM" System board extension Device node,
// unless is not already reserved by some of PCI Device drivers. There have been observed the difference of how Win9x & Win2000
// OSes deal with Expansion ROM memory. Win9x Device drivers are tend to claim its expension ROMs regions as used
// by the device; Win2000 never use such ROM regions for its devices. Therefore there can be different
// approach used for different OSes in reservation unclaimed memory in "SYSM" Device node.
// is forwarded to PCI Bus
//
//  Input: Nothing
//
//  Output: _CRS buffer
//
//-------------------------------------------------------------------------
//<AMI_PHDR_END>
	Device(\_SB.RMEM)// Memory
	{
		Name(_HID, EISAID("PNP0C01"))   // Hardware Device ID
		Name(_UID, 1)
/*
		Name(CRS, ResourceTemplate()
		{
// Base Address 0 - 0x9FFFF , 640k DOS memory
//			Memory32Fixed(ReadWrite,0x0000,  0xA0000 )      //Writeable
// Shadow RAM1, C0000 - E0000, 128k Expansion BIOS
			Memory32Fixed(ReadOnly, 0x00000, 0x00000, RAM1) //Non-writeable
// Shadow RAM2, E0000 - 1M, 128k System BIOS
			Memory32Fixed(ReadOnly, 0xE0000, 0x20000, RAM2) //Non-writeable
// Base Address 1M - Top of system present memory
//			Memory32Fixed(ReadWrite,0x100000,0x00000, RAM3) //Writeable
// ROM image if decoded at top of 4GByte space
//			Memory32Fixed(ReadOnly, 0x00000, 0x00000, RESM) //Non-Writeable
// Reserve memory range above 4GB
//			QWORDMemory( ResourceConsumer, PosDecode, MinFixed, MaxFixed,
//			Cacheable,		// _MEM
//			ReadWrite,		// _RW
//			0xfffffff,		// Granularity
//			0x40000000, 0x00000000,	// _MIN, _MAX
//			0x00,			// Translation
//			0x00000000,		// _LEN
//			,,
//			4GBR
//			)
		})

		Method (_CRS, 0)
		{
			CreateDwordField(CRS, ^RAM1._BAS, BAS1)
			CreateDwordField(CRS, ^RAM1._LEN, LEN1)
			CreateDwordField(CRS, ^RAM2._BAS, BAS2)
			CreateDwordField(CRS, ^RAM2._LEN, LEN2)
//			CreateDwordField(CRS, ^RAM3._LEN, LEN3)
//			CreateDwordField(CRS, ^RESM._BAS, BAS4)
//			CreateDwordField(CRS, ^RESM._LEN, LEN4)
//			CreateQwordField(CRS, ^4GBR._MIN, MIN5)
//			CreateQwordField(CRS, ^4GBR._MAX, MAX5)
//			CreateQwordField(CRS, ^4GBR._LEN, LEN5)
			If(LNotEqual(OSFL,0))		// For Win9x do not reserve 0xC0000-0xE0000,
										// The region can already be claimed by some OS driver (video, SCSI,..)
			{
				If(MG1B) // If there is a non-shadowed gap in 0xc0000 - 0xfffff region
				{
				// Shadow RAM1, C0000 - E0000, 128k Expansion BIOS
					If(LGreater(MG1B, 0xC0000))
					{
						Store(0xC0000, BAS1)
						Subtract(MG1B, BAS1, LEN1)
					}
				} Else {
					Store(0xC0000, BAS1)
					Store(0x20000, LEN1)
				}
				// Shadow RAM2, E0000 - 1M, 128k System BIOS
				If(Add(MG1B, MG1L,Local0))
				{
					Store(Local0, BAS2)
					Subtract(0x100000, BAS2, LEN2)
				}
			}
// MIN6 returns the System memory size (PCI0._CRS)
			Subtract(MG2B, 0x100000, LEN3)
// Memory hole at top of 4Gbyte
			Add(MG2B, MG2L, BAS4)
			Subtract(0, BAS4, LEN4)
// above 4GB
//			Store(MG3B, MIN5)
//			Store(MG3L, MAX5)
//			Subtract(MAX5, MIN5, LEN5)
			Return(CRS)
		}	// end of _CRS
*/
	}// End Memory


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
