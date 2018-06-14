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
//**********************************************************************
//
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/AmtWrapper/AsfTable/AsfTable.c 3     6/18/14 3:14a Larryliu $
//
// $Revision: 3 $
//
// $Date: 6/18/14 3:14a $
//
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/AmtWrapper/AsfTable/AsfTable.c $
// 
// 3     6/18/14 3:14a Larryliu
// [TAG]  		EIP173999
// [Category]  	Improvement
// [Description]  	[HWR]Remove useless comments from Intel ME
// component.(except RC)
// [Files]  		AsfTable.c
// 
// 1     2/08/12 1:09a Klzhan
// 
// 1     2/25/11 1:44a Klzhan
// Initial Check-in
// 
// 1     12/03/10 5:10a Klzhan
// Initial Check-in.
// 
//
//**********************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		AsfTable.c
//
// Description:	Create ASF Acpi table
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>
#include "AsfTable.h"

EFI_GUID gAcpiSupportGuid = EFI_ACPI_SUPPORT_GUID;

EFI_STATUS
AsfBuildTbl(
  IN EFI_EVENT    Event,
  IN VOID         *Context
  );

//----------------------------------------------------------------------------
// Variable declaration
//----------------------------------------------------------------------------
VOID      *mAsfRegistration;

//
// Driver entry point
//
EFI_DRIVER_ENTRY_POINT (AsfTableEntryPoint);

//
// Function implementations
//
EFI_STATUS
EFIAPI
AsfTableEntryPoint (
    IN EFI_HANDLE ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable
)
{
	EFI_EVENT                 FilterEvent;
	EFI_STATUS				  Status;

    //
    // Initialize the EFI Driver Library
    //
    EfiInitializeDriverLib (ImageHandle, SystemTable);

	Status = gBS->CreateEvent (	EFI_EVENT_NOTIFY_SIGNAL, 
								EFI_TPL_CALLBACK,
								AsfBuildTbl, 
								NULL, 
								&FilterEvent);
	if (EFI_ERROR(Status)) {
		return Status;
	}

	// Register for protocol notifactions on this event
	Status = gBS->RegisterProtocolNotify (	&gAcpiSupportGuid, 
											FilterEvent,
											&mAsfRegistration);

	ASSERT_EFI_ERROR (Status);

	gBS->SignalEvent (FilterEvent);

    return Status;
}

//-----------------------------------------------------------------------------
// ASF Table
//-----------------------------------------------------------------------------
//The table shound be runtime build like as ASFBSP
//
// ASF Definitions
//
#define EFI_ACPI_1_0_ASF_DESCRIPTION_TABLE_REVISION   0x20

// need to update to asl asf 2.0 table....
EFI_ACPI_1_0_ASF_DESCRIPTION_TABLE ASF_TABLE = {
    EFI_ACPI_1_0_ASF_DESCRIPTION_TABLE_SIGNATURE,
    sizeof (EFI_ACPI_1_0_ASF_DESCRIPTION_TABLE),
    EFI_ACPI_1_0_ASF_DESCRIPTION_TABLE_REVISION,
    0,                // to make sum of entire table == 0
    
    // OEM identification
    'I', 'N', 'T', 'E', 'L', ' ',
    
    // OEM table identification
    ((((((((((((('D' << 8) + '8') << 8) + '6') << 8) + '5') << 8) + 'G') << 8) + 'C') << 8) + 'H') << 8) + ' ', // OEM table identification
    
    1,                // OEM revision number
    ((((('M' << 8) + 'S') << 8) + 'F') << 8) + 'T',  // ASL compiler vendor ID
    1000000,          // ASL compiler revision number

    //
    // ASF_INFO
    //
    0x00,              // Type "ASF_INFO"
    0x00,               // Reserved
    sizeof (EFI_ACPI_ASF_INFO), // Length
    0xFF,               // Min Watchdog Reset Value
    0xFF,               // Min ASF Sensor Inter-poll Wait Time
    0x0001,             // System ID
    0x57010000,         // IANA Manufacture ID for Intel
    0x00,               // Feature Flag
    0x00, 0x00, 0x00,   // Reserved
    
    //
    // ASF_ALRT
    //
    
    0x01,            // Type "ASF_ALRT"
    0x00,             // Reserved
    sizeof (EFI_ACPI_ASF_ALRT), // Length
    0x00,             // Assertion Event Bit Mask
    0x00,             // Deassertion Event Bit Mask
    0x03,             // Number Of Alerts
    0x0C,             // Array Element Length
    //
    // ICH Slave SMBUS Read devices
    //
    0x89, 0x04, 0x01, 0x01, 0x05, 0x6F, 0x00, 0x68, 0x08, 0x88, 0x17, 0x00,  // Device 0
    0x89, 0x04, 0x04, 0x04, 0x07, 0x6F, 0x00, 0x68, 0x20, 0x88, 0x03, 0x00,  // Device 1
    0x89, 0x05, 0x01, 0x01, 0x19, 0x6F, 0x00, 0x68, 0x20, 0x88, 0x22, 0x00,  // Device 2

    //
    // ASF_RCTL
    //
    0x02,                       // Type "ASF_RCTL"
    0x00,                       // Reserved
    sizeof (EFI_ACPI_ASF_RCTL), // Length
    0x04,                       // Number of Controls
    0x04,                       // Array Element Length
    0x0000,                     // Reserved
    //
    // ICH Slave SMBUS Write cmds
    //
    0x00, 0x88, 0x00, 0x03,     // Control 0 --> Reset system
    0x01, 0x88, 0x00, 0x02,     // Control 1 --> Power Off system
    0x02, 0x88, 0x00, 0x01,     // Control 2 --> Power On system
    0x03, 0x88, 0x00, 0x04,     // Control 3 --> Power Cycle Reset (off then on)
  
    //
    // ASF_RCMP
    //
    0x03,                       // Type "ASF_RCMP"
    0x00,                       // Reserved
    sizeof (EFI_ACPI_ASF_RMCP), // Length
    
    // Remote Control Capabilities supported Bit Masks
    // =============================================
    // System Firmware Capabilities Bit Mask Started
    // =============================================
    0x21,                       // System Firmware Capabilities Bit Mask 
                                // (two MSBytes are Rsvd,

                                // Bit7 RSVD 
                                // Bit6 Support Sleep Button LOCK
                                // Bit5 Support KBD LOCK
                                // Bit4-3 RSVD
                                // Bit2 Support Reset Button LOCK
                                // Bit1 Support Power Button LOCK
                                // Bit0 Support Verbosity/ Blank Screen
    0xF8,
                                // Bit7 Support Configration Data Reset
                                // Bit6 Support Verbosity/ Quiet
                                // Bit5 Support Verbosity/ Verbose
                                // Bit4 Support Force Progress Event
                                // Bit3 Support User Password Bypass
                                // Bit2:0 RSVD
    0x00,
    0x00,
    // =============================================
    // Special Commands Bit Mask Started
    // =============================================
    0x00,                       // RSVD
    0x13, 
                                // Bit7:5 RSVD
                                // Bit4 Support Force CD/DVD Boot Command
                                // Bit3 Support Force Diagnostic Boot Command
                                // Bit2 Support Force Hard Drive Safe-mode Boot Command
                                // Bit1 Support Force Hard Drive Boot Command
                                // Bit0 Support Force PXE Boot Command
    // =============================================
    // System Capabilities Bit Mask Started
    // =============================================
    0xF0,                       // System Capabilities Bit Mask (Supports Reset,
                                // Power-Up,Power-Down, Power-Cycle Reset 
                                // for compat and secure port.
    0x00,                       // Boot Option Complete Code
    0x57010000,                 // IANA ID for Intel Manufacturer
    0x00,                       // Special Command
    0x00, 0x00,                 // Special Command Parameter
    0x00, 0x01,                 // Boot Options
    0x00, 0x00,                 // OEM Parameters

    //
    // ASF_ADDR
    //
    0x84,                         // Type "ASF_ADDR", last record
    0x00,                         // Reserved
    sizeof (EFI_ACPI_ASF_ADDR),   // Length
    0x00,                         // SEEPROM Address
    ASF_ADDR_DEVICE_ARRAY_LENGTH, // Number Of Devices
    0x5C, 0x68, 0x88, 0xC2, 0xD2, // Fixed SMBus Address (Heceta 6, 82573E device - static def (also an ARP addr),
    0xDC, 0xA0, 0xA2, 0xA4, 0xA6, // ICH Slave Device, SMB ARP, CK410, DB400/800, SDRAM SPD devices 
    0xC8                          // TEKOA Slave Device
};

EFI_STATUS
AsfBuildTbl(
	IN EFI_EVENT    Event,
	IN VOID         *Context
)
{
    EFI_STATUS Status;
	UINTN						AsfTableHandle=0;
	EFI_ACPI_SUPPORT_PROTOCOL	*AcpiSupport;  
	VOID						*AsfStruc;

	AsfStruc = (VOID *)&ASF_TABLE;

	Status = gBS->LocateProtocol(&gAcpiSupportGuid, 
								 NULL,
								 &AcpiSupport);
	if (EFI_ERROR (Status)) 
	{
		return EFI_ABORTED;
	}

	Status = AcpiSupport->SetAcpiTable (AcpiSupport, 
										AsfStruc, 
										TRUE,
										(EFI_ACPI_TABLE_VERSION_2_0|EFI_ACPI_TABLE_VERSION_1_0B),
										&AsfTableHandle);
	if (EFI_ERROR(Status)) 
	{
		// Handle the error appropriately
		return EFI_ABORTED;
	}

	return Status;
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