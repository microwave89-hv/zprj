//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

//*************************************************************************
// $Header: /Alaska/SOURCE/Modules/CMOS Manager/CMOS SMM/CmosAccess.asl 4     1/25/12 2:36p Michaela $
//
// $Revision: 4 $
//
// $Date: 1/25/12 2:36p $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/CMOS Manager/CMOS SMM/CmosAccess.asl $
// 
// 4     1/25/12 2:36p Michaela
// 
// 3     12/11/11 8:52p Michaela
// 
// 2     11/30/11 11:49p Michaela
// [TAG]         EIP56197
// [Category]    New Feature
// [Severity]    Normal
// [Description] CMOS Manager Support in Runtime Code
// [Files]       CmosManager.sdl
//               CmosSetup.uni
//               CmosMessages.uni
//               CmosManagerSmm.cif
//               CmosAccess.h
//               CmosManagerSmm.c
//               CmosAccess.asl
// 
// 1     3/16/11 2:44p Michaela
//
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:    CmosAccess.asl
//
// Description:
//      This file contains an ASL method for accessing CMOS from
//      ASL code.
//
//<AMI_FHDR_END>
//*************************************************************************

Device(CMOS)
{
	Name(_HID, EISAID("PNP0C02"))	// System board resources
	Name(_UID, 0x18)				// Unique ID. 
	
	OperationRegion (SRB0, SystemIO, SRSI, 1)		
	Field (SRB0, ByteAcc, NoLock, Preserve) 
	{
		SRSM,	8 // SW-SMI ctrl port
	}

	// Define a location in root scope to be updated during
	// boot to specify the location of a communication buffer.
	// Search CMOS_SMM_CONTEXT for data size/type info
	// for this operation region (communication buffer).
	// Search gAslContext for additional information regarding
	// initialization and implemenataion details.

	Name(\CCOM, 0x0123456789ABCDEF)

	OperationRegion (CMOP, SystemMemory, CCOM, 40)
	Field (CMOP, AnyAcc, NoLock, Preserve)
	{
		CODE,   8,   // 1 byte Opcode
		TOKN,   16,  // 2 byte CMOS Token
		BYTE,   8,   // 1 byte Data value
		STAT,   8    // 1 byte status value
	}

	//--------------------------------------------------------------------
	// ACCE: access CMOS 
	//      Arg0 - Opcode (0 = Write, 1 = Read)
	//      Arg1 - CmosToken
	//      Arg2 - CmosByte
	//
	//      return - 0/FALSE = unsuccessful
	//               1/TRUE = successful
	//--------------------------------------------------------------------
	Method(ACCE, 3, Serialized){

		// if \CCOM is not updated, there was an error allocating the
		// communication buffer.

		if (LEqual(\CCOM, 0x0123456789ABCDEF)) {
			Return(0)
		}

		// Write code & value to the communication buffer
		Store(Arg0, CODE)
		Store(Arg1, TOKN)
		Store(Arg2, BYTE)
		
		// Generate SMI type = CSMI
		Store(CSMI, SRSM)
        Store(BYTE, Arg2)
        
		// Arg2 (BTYE) contains the CMOS value on read
		// The method return value is Boolean
		Return(STAT)
	}
}

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
