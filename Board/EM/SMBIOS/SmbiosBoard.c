//****************************************************************************
//****************************************************************************
//**                                                                        **
//**           (C)Copyright 1985-2013, American Megatrends, Inc.            **
//**                                                                        **
//**                          All Rights Reserved.                          **
//**                                                                        **
//**           5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093            **
//**                                                                        **
//**                          Phone: (770)-246-8600                         **
//**                                                                        **
//****************************************************************************
//****************************************************************************
//****************************************************************************
// $Header: /Alaska/BIN/Modules/SMBIOS/SmbiosBoard.c 29    5/07/14 10:33a Davidd $
//
// $Revision: 29 $
//
// $Date: 5/07/14 10:33a $
//****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/SMBIOS/SmbiosBoard.c $
// 
// 29    5/07/14 10:33a Davidd
// [TAG]  		EIP157418
// [Category]  	Improvement
// [Description]  	Removal of temporary bus assignment or sample code from
// SmbiosBoard.c template
// [Files]  		SmbiosBoard.c
//
// 28    11/15/13 4:31p Davidd
// [TAG]           EIP143321
// [Category]      Improvement
// [Description]   Perform "CppCheck" on Smbios module for
// '4.6.5.1_SMBIOS_36' release
// [Files]         SmbiosBoard.c
//                 Smbios.c
//                 SmbiosDMIEdit.c
//                 SmbiosDMIEditFunc.c
//                 SmbiosNvramFunc.c
//
// 27    5/23/13 2:36p Davidd
// [TAG]  		    EIP104836
// [Category]  	New Feature
// [Description]  	DMIEdit support edit type 4
// [Files]  		SmbiosBoard.c
//                 SmbiosDMIEditBoard.sdl
//                 Smbios.c
//                 SmbiosDMIEditFunc.c
//                 Smbios.h
//                 SmbiosDynamicData.h
//
// 26    5/04/11 3:33p Davidd
// [TAG]           EIP57144
// [Category]      NEW FEATURE
// [Description]   Allow SMBIOS Type 39 to be modified using DMIEdit
// [Files]         SmbiosBoard.c
//                 Smbios.h
//                 SmbiosDynamicData.h
//                 Smbios.c
//                 SmbiosDmieditFunc.c
//                 SmbiosNvramFunc.c
//
// 25    4/05/11 11:38a Davidd
// [TAG]           EIP55656
// [Category]      Improvement
// [Description]   Provide generic support in SMBIOS module to include
// build time EC version
// [Files]         SmbiosBoard.c
//
// 24    2/09/11 10:57a Davidd
// [TAG]  		EIP52505
// [Category]  	Improvement
// [Description]  	Dynamically update SMBIOS Type24 (Hardware Security)
// according to Administrator/User password setup question.
// [Files]  		SmbiosBoard.c
//
// 23    11/22/10 12:36p Davidd
// [TAG]           EIP44236
// [Category]      BUG FIX
// [Severity]      Normal
// [Symptom]       SMBIOS type 4 Processor Version is incorrect
// [RootCause]     Type 4 Version string is not resized as updated.
// [Solution]      Added code to replace the Version strings as updated.
// Same
// also applied to Manufacturer string.
// [Files]
//    Smbios.c
//    SmbiosBoard.c
//
// 22    11/15/10 2:18p Davidd
// [TAG]           EIP46936
// [Category]      Improvement
// [Description]   Generic Smbios module should have the support to
// disable SMBIOS memory update
// [Files]
//    Smbios.c
//    Smbios.sdl
//    SmbiosBoard.c
//    SmbiosDynamicData.h
//
// 21    11/01/10 12:36p Davidd
// [TAG]           EIP41560
// [Category]      Improvement
// [Description]   DMIEDIT modified values are not preserved in reboot
// [Files]
//    Smbios.c
//    Smbios.sdl
//    SmbiosBoard.c
//    SmbiosBoard.mak
//
// 20    6/02/09 3:43p Davidd
// Updated AMI and function headers (EIP 22180)
//
// 19    5/19/09 11:01a Davidd
// Changes added to improve memory type 17 porting (EIP 22241).
//
// 18    12/30/08 3:11p Davidd
// Fixed the hanging problem when only SMBIOS binary component is present
// (ref. EIP 18370)
//
// 17    11/14/08 4:39p Davidd
// - Added OemUpdate protocol. OEM can add code to update any structure
// here. This function will be called after all structures have been
// updated with DMI or dynamic data.
//
// 16    10/27/08 12:52p Davidd
// - Code added for memory SPD data access.
// - Added Type 41 support (SMBIOS v2.6)
//
// 15    2/22/08 10:19a Davidd
// Simplified the way the number of memory slots for each physical memory
// array are defined.
//
// 14    2/13/08 12:41p Davidd
// Added a close comment missing in CreateBatteryDataForSMBios().
//
// 13    2/06/08 3:58p Davidd
// Added NO_OF_PORTABLE_BATTERY field to SmbiosBoardProtocol to hold the
// number of batteries in the system.
//
// 12    12/17/07 12:09p Davidd
// Added PORTABLE_BATTERY_INFO to EFI_SMBIOS_BOARD_PROTOCOL.
// Removed entries intended as reminder of porting is needed. This causes
// BQA Module Delete/Insertion test to fail.
//
// 11    11/28/07 10:56a Davidd
// Changes added to dynamically update the Processor Information Type 4
// Voltage field.
//
// 10    11/21/07 12:11p Davidd
//
// 9     11/21/07 12:04p Davidd
// Added function CreateBatteryDataForSMBios to support Portable Battery
// Data structure type 22.
//
// 8     6/05/07 4:03p Michaela
// Added porting comment for CreateCPUDataForSMBios() to clarify
// usage for backward compatibility only
//
// 7     3/29/07 3:23p Davidd
// Provide sample template code for both Intel and AMD platforms. User to
// uncomment appropriate blocks to use. Sample template code might need
// additional changes depending on platform.
//
// 6     3/21/07 4:35p Michaela
// minor modification to CreateCPUDataForSMBios to meet
// coding standards, add support for AMD and add comments.
//
// 5     12/15/06 1:13p Davidd
// Reformatted to coding  standard.
//
// 1     5/24/06 11:59a Fasihm
// Initial check-in for the Santa Rosa Project. (Matanzas CRB) with
// Crestline + ICH8M + Merom Processor.
//
// 3     3/15/06 5:50p Fasihm
// Code modified to get the CPU data by making call to the CPU protocol.
// Added some SDL token values into the SmbiosBoardProtocol.
//
// 4     3/03/06 5:32p Davidd
// Code modified to get the CPU data by making call to the CPU protocol.
//
// 3     7/27/05 1:23p Davidd
// Added some SDL token values into the SmbiosBoardProtocol.
//
// 2     7/20/05 11:17a Davidd
// Commented out sample code. Sample code is for reference only.
//
// 1     7/18/05 5:57p Davidd
// File added. This file is used to port the CPU, System Slot, and
// On-Board Devices dynamic information.
//
//****************************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:    SmbiosBoard.C
//
// Description: This file contains code for OEM related code for SMBIOS
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

//----------------------------------------------------------------------------
// Includes

#include <Token.h>
#include <EFI.h>
#include <AmiDxeLib.h>
#include <CacheSubClass.h>
#include <Protocol\AmiCpuInfo.h>
#include <Protocol\PciIO.h>
#include <Protocol\PciRootBridgeIo.h>
#include <Protocol\SmbiosDynamicData.h>
#include <AMICSPLIBInc.h>
#include <Protocol\SMBUS.h>
#include <Protocol\Smbios.h>

#define PCI_CFG_ADDRESS(bus,dev,func,reg) \
    ((UINT64)((((UINTN)bus) << 24) + (((UINTN)dev) << 16) + (((UINTN)func) << 8) + ((UINTN)reg)))& 0x00000000ffffffff

extern  EFI_BOOT_SERVICES   *pBS;

UINT8                       SmbusCmdReg;
EFI_GUID                    gEfiSmbiosProtocolGuid = EFI_SMBIOS_PROTOCOL_GUID;
EFI_SMBIOS_PROTOCOL         *gSmbiosProtocol;
EFI_SMBUS_HC_PROTOCOL       *gSMBus = NULL;

EFI_GUID  gEfiSmbiosBoardProtocolGuid  = EFI_SMBIOS_BOARD_PROTOCOL_GUID;

EFI_SMBIOS_BOARD_PROTOCOL   SmbiosBoardProtocol = {BASE_BOARD_INFO,
                                                  SYS_CHASSIS_INFO,
                                                  PROCESSOR_DMIEDIT_SUPPORT,
                                                  OEM_STRING_INFO,
                                                  SYSTEM_CONFIG_OPTION_INFO,
                                                  MEMORY_ERROR_INFO,
                                                  ONBOARD_DEVICE_INFO,
                                                  PORTABLE_BATTERY_INFO,
                                                  ADDITIONAL_INFO,
                                                  ONBOARD_DEVICE_EXTENDED_INFO,
                                                  SYSTEM_POWER_SUPPLY_INFO,
                                                  NO_OF_PROCESSOR_SOCKETS,
                                                  NUMBER_OF_SYSTEM_SLOTS,
                                                  NUMBER_OF_ONBOARD_DEVICES,
                                                  NO_OF_PHYSICAL_MEMORY_ARRAY,
                                                  NO_OF_PORTABLE_BATTERY,
                                                  ONBOARD_DEVICE_EXT_COUNT,
                                                  CreateBaseBoardDataForSMBios,
                                                  CreateChassisDataForSMBios,
                                                  CreateCPUDataForSMBios,
                                                  CreateSlotDataForSMBios,
                                                  CreateOnBoardDevDataForSMBios,
                                                  CreateBatteryDataForSMBios,
                                                  CreateOnBoardDevExtInfoForSMBios,
                                                  EnableSmbusController,
                                                  RestoreSmbusController,
                                                  GetSpdByte,
                                                  OemUpdate,
                                                  A1_MEMORY_SOCKETS,
#if NO_OF_PHYSICAL_MEMORY_ARRAY >= 2
                                                  A2_MEMORY_SOCKETS,
#endif
#if NO_OF_PHYSICAL_MEMORY_ARRAY >= 3
                                                  A3_MEMORY_SOCKETS,
#endif
#if NO_OF_PHYSICAL_MEMORY_ARRAY == 4
                                                  A4_MEMORY_SOCKETS,
#endif
                                                  };

typedef VOID (SMBIOS_OEM_UPDATE) (VOID);
extern SMBIOS_OEM_UPDATE SMBIOS_OEM_UPDATE_LIST EndOfSmbiosOemUpdateList;
SMBIOS_OEM_UPDATE* SmbiosOemUpdate[] = {SMBIOS_OEM_UPDATE_LIST NULL};

/*
//----------------------------------------------------------------------------
// ==================================================================
// ==================================================================
// ==================================================================
// ===                                                            ===
// ===   End of SAMPLE TEMPLATE CODE for Intel Weybridge CRB      ===
// ===   platform. Uncomment this block to use.                   ===
// ===                                                            ===
// ===   Might need changes for other platforms.                  ===
// ===                                                            ===
// ==================================================================
// ==================================================================
// ==================================================================
//----------------------------------------------------------------------------
*/

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//                     ***** PORTING REQUIRED *****
//               (if SMBIOS module is part of the project)
//----------------------------------------------------------------------------
// Procedure:   OemUpdate
//
// Description: The purpose of this function is to allow OEM to update the
//              SMBIOS table as needed. OEM can use the EFI_SMBIOS_PROTOCOL
//              to read, add, delete, and write to the SMBIOS table.
//
// Input:  None
//
// Output: None
//
// Note:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
OemUpdate (VOID)
{
/*
//----------------------------------------------------------------------------
    // ==================================================================
    // ==================================================================
    // ==================================================================
    // ===                                                            ===
    // ===   The following sample code DOES NOT serve any purposes.   ===
    // ===   It is included to illustrate the use of the SMBIOS       ===
    // ===   protocols only.                                          ===
    // ===                                                            ===
    // ==================================================================
    // ==================================================================
    // ==================================================================
    EFI_STATUS      Status;
    UINT8           *Buffer;
    UINT16          BSize;
    UINT16          Handle;

	Status = pBS->LocateProtocol(&gEfiSmbiosProtocolGuid, NULL, &gSmbiosProtocol);
	ASSERT_EFI_ERROR(Status);

    // Read CPU structure
    Status = gSmbiosProtocol->SmbiosReadStrucByType(4, 1, &Buffer, &BSize);

    if (!EFI_ERROR(Status)) {
        // Update previously read CPU structure and write it back, overwriting old data
        Handle = ((SMBIOS_STRUCTURE_HEADER*)Buffer)->Handle;
        ((SMBIOS_PROCESSOR_INFO*)Buffer)->MaxSpeed = 0x1234;
        gSmbiosProtocol->SmbiosWriteStructure(Handle, Buffer, BSize);

        // Add structure with specific handle = 0x60
        Handle = 0x60;
        gSmbiosProtocol->SmbiosAddStrucByHandle(Handle, Buffer, BSize);

        // Add structure with next available handle number
        gSmbiosProtocol->SmbiosAddStructure(Buffer, BSize);

        // Delete structure with handle = 3
        gSmbiosProtocol->SmbiosDeleteStructure(3);

        // Get available free handle, then add structure with that handle
        Handle = gSmbiosProtocol->SmbiosGetFreeHandle();
        if (Handle != -1) {
            gSmbiosProtocol->SmbiosAddStrucByHandle(Handle, Buffer, BSize);
        }

        // Free memory allocated by the earlier gSmbiosProtocol->SmbiosReadStrucByType call
        pBS->FreePool(Buffer);
    }
    // ==================================================================
    // ==================================================================
    // ==================================================================
    // ===                                                            ===
    // ===   End of sample code                                       ===
    // ===                                                            ===
    // ==================================================================
    // ==================================================================
    // ==================================================================

//----------------------------------------------------------------------------
*/

//===========================================================================
// 			 EC Version (Type 0 Offset 0x16-0x17) dynamic update
//
// This code requires EC major & minor versions to be available in
// ECRev1 & ECRev2 NVRAM variables respectively
//===========================================================================
#if (defined(DYNAMIC_UPDATE_TYPE0_EC_VERSION) && (DYNAMIC_UPDATE_TYPE0_EC_VERSION == 1))
{
    EFI_STATUS  		Status;
	EFI_GUID    		gEfiGlobalVariableGuid = EFI_GLOBAL_VARIABLE;
	UINT8				EcMajorVersion;
	UINT8				EcMinorVersion;
	UINTN				Size = sizeof(EcMajorVersion);
	UINT8				Type0Data[sizeof(SMBIOS_BIOS_INFO)];
	UINT16				Type0DataSize = sizeof(SMBIOS_BIOS_INFO);
	UINT8				*Type0DataPtr = &Type0Data[0];

	// Get EC version from ECRev1 & ECRev2 variables
    Status = pRS->GetVariable( L"ECRev1", \
                               &gEfiGlobalVariableGuid, \
                               NULL, \
                               &Size, \
                               &EcMajorVersion );
	if (EFI_ERROR(Status)) goto exitEcVersionUpdate;

    Status = pRS->GetVariable( L"ECRev2", \
                               &gEfiGlobalVariableGuid, \
                               NULL, \
                               &Size, \
                               &EcMinorVersion );
	if (EFI_ERROR(Status)) goto exitEcVersionUpdate;

    Status = pBS->LocateProtocol(
								&gEfiSmbiosProtocolGuid,
								NULL,
								&gSmbiosProtocol);
    ASSERT_EFI_ERROR(Status);

    if (Status == EFI_SUCCESS) {
		// Read Smbios Type 0 structure, update EC version and write it back
		Status = gSmbiosProtocol->SmbiosReadStrucByType(
														0,
														1,
														&Type0DataPtr,
														&Type0DataSize);
	    ASSERT_EFI_ERROR(Status);

		((SMBIOS_BIOS_INFO*)Type0DataPtr)->ECFirmwareMajorRelease = EcMajorVersion;
		((SMBIOS_BIOS_INFO*)Type0DataPtr)->ECFirmwareMinorRelease = EcMinorVersion;

    	if (Status == EFI_SUCCESS) {
			Status = gSmbiosProtocol->SmbiosWriteStructure(
						((SMBIOS_BIOS_INFO*)Type0DataPtr)->StructureType.Handle,
						Type0DataPtr,
						Type0DataSize);
		    ASSERT_EFI_ERROR(Status);
		}
	}

exitEcVersionUpdate:
	Status = EFI_SUCCESS;		// Dummy - To avoid build error in some cases
}
#endif
//===========================================================================
// 			 EC Version (Type 0 Offset 0x16-0x17) dynamic update End
//===========================================================================

//===========================================================================
//                *****  DO NOT REMOVE THIS BLOCK  *****
//
// 			 Hardware Security (Type 24) dynamic update Start
//
// Update Type 24 Administrator and Power-on Password Status based on
// Setup settings
//===========================================================================
#if (defined(TSE_BUILD) && (HARDWARE_SECURITY_INFO == 1))	// Token indicating AMI TSE is used
{
#include <Setup.h>

#define AMITSESETUP_GUID \
 { 0xc811fa38, 0x42c8, 0x4579, 0xa9, 0xbb, 0x60, 0xe9, 0x4e, 0xdd, 0xfb, 0x34 }

    EFI_STATUS  Status;
	EFI_GUID 	AmiTseSetupGuid = AMITSESETUP_GUID;
	AMITSESETUP AmiTseData;
    UINTN       VariableSize = sizeof(AMITSESETUP);
	UINTN		TsePasswordLength = SETUP_PASSWORD_LENGTH * sizeof(CHAR16);
	CHAR16 		*TestPassWord;
	UINT8		HwdSecSettings = 0;
	UINT8		*Type24Data;
	UINT16		Type24Size;

    Status = pRS->GetVariable ( L"AMITSESetup", \
                                &AmiTseSetupGuid, \
                                NULL, \
                                &VariableSize, \
                                &AmiTseData );

    if (!EFI_ERROR(Status)) {
	    Status = pBS->AllocatePool(EfiRuntimeServicesData, TsePasswordLength, &TestPassWord);
		if (Status == EFI_SUCCESS) {
			MemSet(TestPassWord, TsePasswordLength, 0);

			if (MemCmp(AmiTseData.UserPassword, TestPassWord, TsePasswordLength) != 0) {
				HwdSecSettings |= BIT6;			// Power-on Password
			}
			if (MemCmp(AmiTseData.AdminPassword, TestPassWord, TsePasswordLength) != 0) {
				HwdSecSettings |= BIT2;			// Administrator Password
			}

		    Status = pBS->LocateProtocol(
										&gEfiSmbiosProtocolGuid,
										NULL,
										&gSmbiosProtocol);
		    ASSERT_EFI_ERROR(Status);

		    if (Status == EFI_SUCCESS) {
				Status = gSmbiosProtocol->SmbiosReadStrucByType(
																24,
																1,
																&Type24Data,
																&Type24Size);

			    ASSERT_EFI_ERROR(Status);

		    	if (Status == EFI_SUCCESS) {
					((SMBIOS_HARDWARE_SECURITY_INFO*)Type24Data)->HardwareSecSettings &= 0x33;	// Clear Admin & Power-on pwd
					((SMBIOS_HARDWARE_SECURITY_INFO*)Type24Data)->HardwareSecSettings |= HwdSecSettings;
					Status = gSmbiosProtocol->SmbiosWriteStructure(
								((SMBIOS_HARDWARE_SECURITY_INFO*)Type24Data)->StructureType.Handle,
								Type24Data,
								Type24Size);
				    ASSERT_EFI_ERROR(Status);

					pBS->FreePool(Type24Data);
				}
			}

			pBS->FreePool(TestPassWord);
		}
	}
}
#endif
//===========================================================================
// 			 Hardware Security (Type 24) dynamic update End
//===========================================================================

//===========================================================================
//                *****  DO NOT REMOVE THIS BLOCK  *****
//                *****  Calling OEM Update eLinks *****
//
//                     OEM Update eLinks Block Start
//===========================================================================
    {
        UINT8   i;

        for (i = 0; SmbiosOemUpdate[i] != NULL; i++) {
            SmbiosOemUpdate[i]();
        }
    }
//===========================================================================
//                     OEM Update eLinks Block End
//===========================================================================
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//                     ***** PORTING REQUIRED *****
//               (if SMBIOS module is part of the project)
//----------------------------------------------------------------------------
// Procedure:   EnableSmbusController
//
// Description: This function saves the current setting of the Smbus
//              Controller CMD register and then enables it so that SPD data
//              can be accessed.
//
// Input:   None
//
// Output:  EFI_STATUS
//
// Note:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
EnableSmbusController (VOID)
{
    EFI_GUID        EfiSMBusProtocolGuid = EFI_SMBUS_HC_PROTOCOL_GUID;

    // Enables the SMBus controller command register if needed.

    return pBS->LocateProtocol( &EfiSMBusProtocolGuid, NULL, &gSMBus );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//                     ***** PORTING REQUIRED *****
//               (if SMBIOS module is part of the project)
//----------------------------------------------------------------------------
// Procedure:   RestoreSmbusController
//
// Description: This function restores the Smbus Controller CMD register
//              to the previously saved setting.
//
// Input:   None
//
// Output:  EFI_STATUS
//
// Note:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
RestoreSmbusController (VOID)
{
    EFI_STATUS  Status = EFI_UNSUPPORTED;

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//                     ***** PORTING REQUIRED *****
//               (if SMBIOS module is part of the project)
//----------------------------------------------------------------------------
// Procedure:   GetSpdByte
//
// Description: This function reads a byte from the system memory SPD
//
// Input:   IN      EFI_SMBUS_DEVICE_ADDRESS    SpdAddr
//          IN      UINT8                       Offset
//          IN OUT  UINT8                       *Data
//
// Output:  EFI_STATUS
//          UINT8       *Data
//
// Note:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
GetSpdByte (
    IN      EFI_SMBUS_DEVICE_ADDRESS    SpdAddr,
    IN      UINT8                       Offset,
    IN OUT  UINT8                       *Data
)
{
    UINTN   Length = 1;

    if (gSMBus == NULL) return EFI_UNSUPPORTED;

    return gSMBus->Execute( gSMBus,
                            SpdAddr,
                            Offset,
                            EfiSmbusReadByte,
                            FALSE,
                            &Length,
                            Data );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//                     ***** PORTING REQUIRED *****
//               (if SMBIOS module is part of the project)
//----------------------------------------------------------------------------
// Procedure:   CreateSlotDataForSMBios
//
// Description: This function gathers the System Slot status information and
//              saves them in a variable named "SmbiosSlotsVar". This variable
//              with the slot information is needed by the SMBIOS module to
//              create the REQUIRED "Type 9" structure
//
// Input:   None
//
// Output:  EFI_STATUS
//          Variable named "SmbiosSlotsVar" with system slot information
//
// Note:    Refer to SYSTEM_SLOT_DYNAMIC_DATA in SmbiosDynamicData.h for
//          structure information.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
CreateSlotDataForSMBios (VOID)
{
    EFI_STATUS                      Status = EFI_SUCCESS;

#if UPDATE_SLOT_TYPE9
/*
//----------------------------------------------------------------------------
//   PORTING REQUIRED   -   PORTING REQUIRED   -   PORTING REQUIRED
//----------------------------------------------------------------------------
//
// Create a SYSTEM_SLOT_DYNAMIC_DATA structure and fill it with system slots
// information - bus number for the slot and its current usage status.
// Return the slot structure information in a variable named "SmbiosSlotsVar"
//
*/
#endif      // UPDATE_SLOT_TYPE9

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   FillStringBufferWithSpaces
//
// Description: This function fills the input buffer with spaces. The number
//              of spaces to be filled is specified in the input BufferSize
//
// Input:   IN UINT8    *BufferPtr
//          IN UINT8    BufferSize
//
// Output:  Buffer pointed by BufferPtr is filled with spaces
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
FillStringBufferWithSpaces (
    IN UINT8    *BufferPtr,
    IN UINT8    BufferSize
)
{
    UINT8   i;

    for (i = 0; i < (BufferSize - 1); i++) {
        *BufferPtr = 0x20;
        BufferPtr++;
    }
    *BufferPtr = 0;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//                     ***** PORTING REQUIRED *****
//               (if SMBIOS module is part of the project)
//----------------------------------------------------------------------------
// Procedure: CreateBaseBoardDataForSMBios
//
// Description: This function provides system chassis information. SMBIOS
//              Core uses these information to dynamically update SMBIOS
//              Chassis Type 2.
//
// Input:  None
//
// Output: Creates variable named "SmbiosBaseBoardVar" with Chassis information
//
// Note: Refer to BASE_BOARD_DATA in SmbiosDynamicData.h for structure
//       information.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
CreateBaseBoardDataForSMBios (
)
{
    EFI_STATUS  Status = EFI_SUCCESS;

#if UPDATE_BASEBOARD_TYPE2
/*
//----------------------------------------------------------------------------
    // ==================================================================
    // ==================================================================
    // ==================================================================
    // ===                                                            ===
    // ===               Start of SAMPLE TEMPLATE CODE                ===
    // ===                                                            ===
    // ===          Might need changes for specific platform          ===
    // ===                                                            ===
    // ==================================================================
    // ==================================================================
    // ==================================================================

    EFI_GUID            EfiSmbiosDynamicDataGuid = EFI_SMBIOS_DYNAMIC_DATA_GUID;
    BASE_BOARD_DATA     BaseBoardInfo;
    UINTN               VarSize;
    UINT32              Attributes = EFI_VARIABLE_BOOTSERVICE_ACCESS;

    char* BoardID_Index[] = {
          "Board Name 1",       // 0x00
          "Board Name ",        // 0x01
          "Board Name ",        // 0x02
    };

    char* BoardManufacturerName = "XYZ Corporation";

    Status = pBS->LocateProtocol(
                        &gPlatformInfoProtocolGuid,
                        NULL,
                        &gPlatformInfoProtocol);
    ASSERT_EFI_ERROR(Status);

    Status = pBS->AllocatePool(
                        EfiBootServicesData,
                        strlen(BoardManufacturerName),
                        &BaseBoardInfo.BoardManufacturer);

    strcpy(BaseBoardInfo.BoardManufacturer, BoardManufacturerName);

    Status = pBS->AllocatePool(
                        EfiBootServicesData,
                        strlen(BoardID_Index[gPlatformInfoProtocol->BoardId]),
                        &BaseBoardInfo.BoardName);

    strcpy(BaseBoardInfo.BoardName, BoardID_Index[gPlatformInfoProtocol->BoardId]);

    VarSize = sizeof(BASE_BOARD_DATA);

    Status = pRS->SetVariable(
                        SmbiosBaseBoardVar,
                        &EfiSmbiosDynamicDataGuid,
                        Attributes,
                        VarSize,
                        &BaseBoardInfo);

    // ==================================================================
    // ==================================================================
    // ==================================================================
    // ===                                                            ===
    // ===                End of SAMPLE TEMPLATE CODE                 ===
    // ===                                                            ===
    // ==================================================================
    // ==================================================================
    // ==================================================================
//----------------------------------------------------------------------------
*/
#endif      // UPDATE_BASEBOARD_TYPE2

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//                     ***** PORTING REQUIRED *****
//               (if SMBIOS module is part of the project)
//----------------------------------------------------------------------------
// Procedure: CreateChassisDataForSMBios
//
// Description: This function provides system chassis information. SMBIOS
//              Core uses these information to dynamically update SMBIOS
//              Chassis Type 3.
//
// Input:  None
//
// Output: Creates variable named "SmbiosChassisVar" with Chassis information
//
// Note: Refer to CHASSIS_DATA in SmbiosDynamicData.h for structure
//       information.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
CreateChassisDataForSMBios (
)
{
    EFI_STATUS          Status = EFI_SUCCESS;

#if UPDATE_SYSTEM_CHASSIS_TYPE3
/*
//----------------------------------------------------------------------------
    // ==================================================================
    // ==================================================================
    // ==================================================================
    // ===                                                            ===
    // ===               Start of SAMPLE TEMPLATE CODE                ===
    // ===                                                            ===
    // ===          Might need changes for specific platform          ===
    // ===                                                            ===
    // ==================================================================
    // ==================================================================
    // ==================================================================

    EFI_GUID            EfiSmbiosDynamicDataGuid = EFI_SMBIOS_DYNAMIC_DATA_GUID;
    CHASSIS_DATA        ChassisInfo;
    UINTN               VarSize;
    UINT32              Attributes = EFI_VARIABLE_BOOTSERVICE_ACCESS;

    Status = pBS->LocateProtocol(
                        &gPlatformInfoProtocolGuid,
                        NULL,
                        &gPlatformInfoProtocol);
    ASSERT_EFI_ERROR(Status);

    switch (gPlatformInfoProtocol->PlatformFlavor) {
        case FlavorMobile:
            ChassisInfo.Type = 0x09; // EfiMiscChassisTypeLapTop
            break;
        case FlavorDesktop:
            ChassisInfo.Type = 0x03; // EfiMiscChassisTypeDeskTop
            break;
        case FlavorUpServer:
            ChassisInfo.Type = 0x11; // EfiMiscChassisTypeMainServerChassis
            break;
        default:
            ChassisInfo.Type = 0x02; // EfiMiscChassisTypeUnknown;
    }

    VarSize = sizeof(CHASSIS_DATA);
    Status = pRS->SetVariable(
                        SmbiosChassisVar,
                        &EfiSmbiosDynamicDataGuid,
                        Attributes,
                        VarSize,
                        &ChassisInfo);

    // ==================================================================
    // ==================================================================
    // ==================================================================
    // ===                                                            ===
    // ===                End of SAMPLE TEMPLATE CODE                 ===
    // ===                                                            ===
    // ==================================================================
    // ==================================================================
    // ==================================================================
//----------------------------------------------------------------------------
*/
#endif      // UPDATE_SYSTEM_CHASSIS_TYPE3

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//                     ***** PORTING REQUIRED *****
//               (if SMBIOS module is part of the project)
//----------------------------------------------------------------------------
// Procedure:   CreateCPUDataForSMBios
//
// Description: This function gathers the System Processor information and
//              saves them in a variable named "SmbiosCpuVar". This variable
//              with the CPU information is needed by the SMBIOS module to
//              create the "Type 4, 7" structure.
//
// Input:   None
//
// Output:  EFI_STATUS
//          Variable named "SmbiosCpuVar" with System CPU information
//
// Note:    Refer to CPU_DYNAMIC_DATA in SmbiosDynamicData.h for
//          structure information.
//
//          ******************** PORTING NOTE ********************
//          By default, this function only returns EFI_SUCCESS and should
//          only be ported if the CPU module does not install the
//          SMBIOS_CPU_INFO_PROTOCOL.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
CreateCPUDataForSMBios (VOID)
{
    EFI_STATUS                  Status = EFI_SUCCESS;

#if UPDATE_CPU_TYPE4
/*
//----------------------------------------------------------------------------
    // ==================================================================
    // ==================================================================
    // ==================================================================
    // ===                                                            ===
    // ===   Start of SAMPLE TEMPLATE CODE for Intel Weybridge CRB    ===
    // ===   platform. Uncomment this block to use.                   ===
    // ===                                                            ===
    // ===   Might need changes for other platforms.                  ===
    // ===                                                            ===
    // ==================================================================
    // ==================================================================
    // ==================================================================
    EFI_GUID                    gAmiCpuInfoProtocolGuid = AMI_CPU_INFO_PROTOCOL_GUID;
    EFI_GUID                    EfiSmbiosDynamicDataGuid = EFI_SMBIOS_DYNAMIC_DATA_GUID;
    UINTN                       NumCores = 1;
    UINTN                       NumHts = 1;
    UINTN                       i;
    UINTN                       j;
    UINT32                      Attributes = EFI_VARIABLE_BOOTSERVICE_ACCESS;
    UINT32                      L1Cache;
    UINT32                      L2Cache;
    UINT32                      L3Cache;
    AMI_CPU_INFO                *GetCpuInfo = NULL;
    AMI_CPU_INFO_PROTOCOL       *AmiCpuInfo;
    CPU_DYNAMIC_DATA            CpuInfo;
    CACHE_DESCRIPTOR_INFO       *CacheDescInfo;
    UINT8                       CacheTypeTable[] = {4, 3, 1, 5};
    UINT8                       AssociativityTable[] = {6, 1, 4, 1, 5, 1, 1, 1, 7, 1, 1, 1, 1, 1, 1, 1, 8};

    Status = pBS->LocateProtocol (&gAmiCpuInfoProtocolGuid, NULL, &AmiCpuInfo);
    if (EFI_ERROR(Status)) return Status;

	CpuInfo.NumberCPU = NO_OF_PROCESSOR_SOCKETS;

    for(i = 0; i < NO_OF_PROCESSOR_SOCKETS; ++i) {
	    Status = AmiCpuInfo->GetCpuInfo(AmiCpuInfo, (UINTN)i*NumCores*NumHts, &GetCpuInfo);
	    if (Status) {
            // No data available from CPU module
            CpuInfo.CpuData[i].CpuData.Status = 0;
            CpuInfo.CpuData[i].CpuData.CurrentSpeed = 0;
            // Hardcode MaxSpeed to 4GHz (assumed system max speed)
            CpuInfo.CpuData[i].CpuData.MaxSpeed = 0x0FA0;
            CpuInfo.CpuData[i].CpuData.ExtClockFreq = CpuInfo.CpuData[0].CpuData.ExtClockFreq;
            CpuInfo.CpuData[i].CpuData.ProcessorID_1 = 0;
            CpuInfo.CpuData[i].CpuData.ProcessorID_2 = 0;
            CpuInfo.CpuData[i].CpuData.Voltage = BIT01;         // Assume 3.3V
            CpuInfo.CpuData[i].CpuData.Upgrade = CpuInfo.CpuData[0].CpuData.Upgrade;
            CpuInfo.CpuData[i].CpuData.Family = CpuInfo.CpuData[0].CpuData.Family;
            MemCpy(CpuInfo.CpuData[i].CpuData.Manufacturer, CpuInfo.CpuData[0].CpuData.Manufacturer, 18);
            MemCpy(CpuInfo.CpuData[i].CpuData.Version, CpuInfo.CpuData[0].CpuData.Version, 48);
            continue;
	    }

	    NumCores = GetCpuInfo->NumCores;
	    NumHts = GetCpuInfo->NumHts;
        CacheDescInfo = GetCpuInfo->CacheInfo;

        L1Cache = 0;
        L2Cache = 0;
        L3Cache = 0;
        CpuInfo.CpuData[i].L1Cache.SystemCacheType = 0xFF;
        CpuInfo.CpuData[i].L2Cache.SystemCacheType = 0xFF;
        CpuInfo.CpuData[i].L3Cache.SystemCacheType = 0xFF;
        for(j = 0; CacheDescInfo[j].Desc; ++j) {  // End of descriptors, Desc = 0.
            switch(GetCpuInfo->CacheInfo[j].Level) {
                case 1:
                        L1Cache = CacheDescInfo[j].Size;
                        if (CpuInfo.CpuData[i].L1Cache.SystemCacheType == 0xFF) {
           	                CpuInfo.CpuData[i].L1Cache.SystemCacheType = CacheTypeTable[CacheDescInfo[j].Type];
                        }
                        else {
			                CpuInfo.CpuData[i].L1Cache.SystemCacheType = 0x05;
                        }
                        CpuInfo.CpuData[i].L1Cache.Associativity = AssociativityTable[CacheDescInfo[j].Associativity];
                        break;
                case 2:
                        L2Cache = CacheDescInfo[j].Size;
                        if (CpuInfo.CpuData[i].L2Cache.SystemCacheType == 0xFF) {
                            CpuInfo.CpuData[i].L2Cache.SystemCacheType = CacheTypeTable[CacheDescInfo[j].Type];
                        }
                        else {
                            CpuInfo.CpuData[i].L2Cache.SystemCacheType = 0x05;
                        }
                        CpuInfo.CpuData[i].L2Cache.Associativity = AssociativityTable[CacheDescInfo[j].Associativity];
                        break;
                case 3:
                        L3Cache = CacheDescInfo[j].Size;
                        if (CpuInfo.CpuData[i].L3Cache.SystemCacheType == 0xFF) {
           	                CpuInfo.CpuData[i].L3Cache.SystemCacheType = CacheTypeTable[CacheDescInfo[j].Type];
                        }
                        else {
			                CpuInfo.CpuData[i].L3Cache.SystemCacheType = 0x05;
                        }
                        CpuInfo.CpuData[i].L3Cache.Associativity = AssociativityTable[CacheDescInfo[j].Associativity];
                        break;
            }
        }

        CpuInfo.CpuData[i].CpuData.CurrentSpeed = (UINT16)(GetCpuInfo->IntendedFreq);
        CpuInfo.CpuData[i].CpuData.MaxSpeed = 3800;     // Value from Intel Tiano BIOS
        CpuInfo.CpuData[i].CpuData.ExtClockFreq = (UINT16)(GetCpuInfo->FSBFreq);
        CpuInfo.CpuData[i].CpuData.ProcessorID_1 = (UINT32)(GetCpuInfo->Version);
        CpuInfo.CpuData[i].CpuData.ProcessorID_2 = (UINT32)(GetCpuInfo->Features);

        // From CPU module: GetCpuInfo->Voltage = Volt * 10000
        // From SMBIOS spec, this field should be set to CPU voltage * 10
        // Therefore this field should be set to GetCpuInfo->Voltage / 1000
        CpuInfo.CpuData[i].CpuData.Voltage = (UINT8)(GetCpuInfo->Voltage / 1000);
        CpuInfo.CpuData[i].CpuData.Status = 0x41;
        CpuInfo.CpuData[i].CpuData.Upgrade = 1;
        CpuInfo.CpuData[i].CpuData.Family = 0xBF;       // Intel(R) Core(TM) 2 Duo processor

        CpuInfo.CpuData[i].CpuData.CoreCount = GetCpuInfo->NumCores;
        CpuInfo.CpuData[i].CpuData.CoreEnabled = 1;
        CpuInfo.CpuData[i].CpuData.ThreadCount = GetCpuInfo->NumHts;
        CpuInfo.CpuData[i].CpuData.Family2 = 0xBF;

        if(i == 0) {
            FillStringBufferWithSpaces(CpuInfo.CpuData[i].CpuData.Version, sizeof(CpuInfo.CpuData[i].CpuData.Version));
            MemCpy(CpuInfo.CpuData[i].CpuData.Version, GetCpuInfo->BrandString, sizeof(CpuInfo.CpuData[i].CpuData.Version) - 1);
            FillStringBufferWithSpaces(CpuInfo.CpuData[i].CpuData.Manufacturer, sizeof(CpuInfo.CpuData[i].CpuData.Manufacturer));
            MemCpy(CpuInfo.CpuData[i].CpuData.Manufacturer, "Intel", 6);
        }
        else {
            MemCpy(CpuInfo.CpuData[i].CpuData.Manufacturer, CpuInfo.CpuData[0].CpuData.Manufacturer, sizeof(CpuInfo.CpuData[0].CpuData.Manufacturer));
            MemCpy(CpuInfo.CpuData[i].CpuData.Version, CpuInfo.CpuData[0].CpuData.Version, sizeof(CpuInfo.CpuData[0].CpuData.Version));
        }
        CpuInfo.CpuData[i].L1Cache.CacheConfig = 0x180;
        CpuInfo.CpuData[i].L1Cache.MaxCacheSize = L1Cache;  // CacheL1
        CpuInfo.CpuData[i].L1Cache.InstalledSize = L1Cache;
        CpuInfo.CpuData[i].L1Cache.SupportSRAM = 0x01;
        CpuInfo.CpuData[i].L1Cache.CurrentSRAM = 0x01;
        CpuInfo.CpuData[i].L1Cache.CacheSpeed = 0;
        CpuInfo.CpuData[i].L1Cache.ErrorCorrectionType = 0x03;

        CpuInfo.CpuData[i].L2Cache.CacheConfig = 0x281;
        CpuInfo.CpuData[i].L2Cache.MaxCacheSize = L2Cache;  // CacheL2
        CpuInfo.CpuData[i].L2Cache.InstalledSize = L2Cache;
        CpuInfo.CpuData[i].L2Cache.SupportSRAM = 0x01;
        CpuInfo.CpuData[i].L2Cache.CurrentSRAM = 0x01;
        CpuInfo.CpuData[i].L2Cache.CacheSpeed = 0;
        CpuInfo.CpuData[i].L2Cache.ErrorCorrectionType = 0x03;

        CpuInfo.CpuData[i].L3Cache.CacheConfig = 0x302;
        CpuInfo.CpuData[i].L3Cache.MaxCacheSize = L3Cache;  // CacheL3
        CpuInfo.CpuData[i].L3Cache.InstalledSize = L3Cache;
        CpuInfo.CpuData[i].L3Cache.SupportSRAM = 0x01;
        CpuInfo.CpuData[i].L3Cache.CurrentSRAM = 0x01;
        CpuInfo.CpuData[i].L3Cache.CacheSpeed = 0;
        CpuInfo.CpuData[i].L3Cache.ErrorCorrectionType = 0x03;
    }
    Status = pRS->SetVariable(
                            SmbiosCpuVar,
                            &EfiSmbiosDynamicDataGuid,
                            Attributes,
                            sizeof(CPU_DYNAMIC_DATA),
                            &CpuInfo);
    ASSERT_EFI_ERROR(Status);
    // ==================================================================
    // ==================================================================
    // ==================================================================
    // ===                                                            ===
    // ===   End of SAMPLE TEMPLATE CODE for Intel Weybridge CRB      ===
    // ===   platform. Uncomment this block to use.                   ===
    // ===                                                            ===
    // ===   Might need changes for other platforms.                  ===
    // ===                                                            ===
    // ==================================================================
    // ==================================================================
    // ==================================================================
//----------------------------------------------------------------------------
*/

/*
//----------------------------------------------------------------------------
    // ==================================================================
    // ==================================================================
    // ==================================================================
    // ===                                                            ===
    // ===      Start of SAMPLE TEMPLATE CODE for AMD Warthog         ===
    // ===      platform. Uncomment this block to use.                ===
    // ===                                                            ===
    // ===      Might need changes for other platforms.               ===
    // ===                                                            ===
    // ==================================================================
    // ==================================================================
    // ==================================================================

    EFI_GUID                gAmiCpuInfoProtocolGuid = AMI_CPU_INFO_PROTOCOL_GUID;
    EFI_GUID                EfiSmbiosDynamicDataGuid = EFI_SMBIOS_DYNAMIC_DATA_GUID;
    UINT8                   AmiType, AmiAssoc, AmiCurLevel;
    UINT16                  AmiCurSize, L1CacheSize, L2CacheSize, L3CacheSize;
    UINT32                  Attributes = EFI_VARIABLE_BOOTSERVICE_ACCESS;
    UINTN                   NumHts = 1, CurNode=0, CurCPU=0, NumCores = 1, CurCacheIndex;
    AMI_CPU_INFO            *AmiCpuInfo = NULL;
    AMI_CPU_INFO_PROTOCOL   *AmiCpuInfoProtocol;
    CPU_DYNAMIC_DATA        CpuInfo;
    CACHE_DESCRIPTOR_INFO   *AmiCacheDesc;
    CPU_DATA                *CurCpuData, *Cpu0Data;
    CACHE_DATA              *CurL1Cache, *CurL2Cache, *CurL3Cache;

    // ==================================================================
    // The mapping between AMI_CPU_INFO.CACHE_DESCRIPTOR_INFO.Type
    // and CPU_DYNAMIC_DATA.SINGLE_CPU_DATA.CACHE_DATA.SystemCacheType
    // should not require a translation table as the cache type is
    // encoded the same for both structures:
    //
    // CACHE_DESCRIPTOR_INFO.Type <-> CACHE_DATA.SystemCacheType
    //                (Other)   1 <-> 1
    //              (Unknown)   2 <-> 2
    //          (Instruction)   3 <-> 3
    //                 (Data)   4 <-> 4
    //              (Unified)   5 <-> 5
    //
    // ==================================================================
    // The mapping between AMI_CPU_INFO.CACHE_DESCRIPTOR_INFO.Associativity
    // and CPU_DYNAMIC_DATA.SINGLE_CPU_DATA.CACHE_DATA.Associativity
    // should not require a translation table as the cache associativity
    // is encoded the same for both structures:
    //
    // CACHE_DESCRIPTOR_INFO.Associativity <-> CACHE_DATA.Associativity
    //                         (Other)   1 <-> 1
    //                       (Unknown)   2 <-> 2
    //                        (Direct)   3 <-> 3
    //                     (2-way Set)   4 <-> 4
    //                     (4-way Set)   5 <-> 5
    //                         (Fully)   6 <-> 6
    //                     (8-way Set)   7 <-> 7
    //                    (16-way Set)   8 <-> 8
    //
    // ==================================================================
    // Fill Processor Information Table (Type 4) and associated Cache
    // Information structures.
    //
    // Notes:   A SINGLE_CPU_DATA structure is created for each
    //          slot/socket such that only one structure is created for
    //          a multi-core processor.  This implies the assumption
    //          that all cores on a processor have identical
    //          configuration.
    //
    // ==================================================================
    Status = pBS->LocateProtocol (
                &gAmiCpuInfoProtocolGuid,
                NULL,
                &AmiCpuInfoProtocol);
    if (EFI_ERROR(Status))
        return Status;

    Status = AmiCpuInfoProtocol->GetCpuInfo(
                AmiCpuInfoProtocol,
                0,
                &AmiCpuInfo);
    if (EFI_ERROR(Status))
        return Status;

    CpuInfo.NumberCPU = NO_OF_PROCESSOR_SOCKETS;
    Cpu0Data = &(CpuInfo.CpuData[0].CpuData);

    // For each Core0 on each slot/node, create a
    // CPU information table.
    for(CurNode=0, CurCPU=0;
        CurNode < NO_OF_PROCESSOR_SOCKETS;
        CurNode++, CurCPU = AmiCpuInfo->NumCores*CurNode )
    {
        Status = AmiCpuInfoProtocol->GetCpuInfo(
                        AmiCpuInfoProtocol,
                        CurCPU,
                        &AmiCpuInfo);

        // some pointers to make code easier to read/type
        CurCpuData = &(CpuInfo.CpuData[CurNode].CpuData);
        CurL1Cache = &(CpuInfo.CpuData[CurNode].L1Cache);
        CurL2Cache = &(CpuInfo.CpuData[CurNode].L2Cache);
        CurL3Cache = &(CpuInfo.CpuData[CurNode].L3Cache);

        // if an AMI_CPU_INFO structure does not exist for this Socket
        // then fill with default data and attempt to get next
        // socket information.
        if (Status) {
            CurCpuData->Status = 0;
            CurCpuData->CurrentSpeed = 0;
            CurCpuData->MaxSpeed = 0x0FA0;
            CurCpuData->ExtClockFreq = Cpu0Data->ExtClockFreq;
            CurCpuData->ProcessorID_1 = 0;
            CurCpuData->ProcessorID_2 = 0;
            CurCpuData->Status = 0;
            CurCpuData->Upgrade = Cpu0Data->Upgrade;
            CurCpuData->Family = Cpu0Data->Family;
            MemCpy(CurCpuData->Manufacturer, Cpu0Data->Manufacturer, 18);
            MemCpy(CurCpuData->Version, Cpu0Data->Version, 48);
            continue;
        }

        NumCores = AmiCpuInfo->NumCores;
        NumHts = AmiCpuInfo->NumHts;
        AmiCacheDesc = AmiCpuInfo->CacheInfo;
        L1CacheSize = 0;
        L2CacheSize = 0;
        L3CacheSize = 0;

        // if more than one L1, L2, or L3 cache exits,
        // its type will be unified by default.
        CurL1Cache->SystemCacheType = 0xFF;
        CurL2Cache->SystemCacheType = 0xFF;
        CurL3Cache->SystemCacheType = 0xFF;

        // ==========================================================
        // Fill Cache Information Table (Type 7) for this slot/node
        // ==========================================================
        for ( CurCacheIndex = 0;
              AmiCacheDesc[CurCacheIndex].Desc;   // Desc == 0 is last
              ++CurCacheIndex )
        {
            AmiType = AmiCacheDesc[CurCacheIndex].Type;
            AmiAssoc = AmiCacheDesc[CurCacheIndex].Associativity;
            AmiCurLevel = AmiCacheDesc[CurCacheIndex].Level;
            AmiCurSize = AmiCacheDesc[CurCacheIndex].Size;

            switch ( AmiCurLevel )
            {
                case EFI_CACHE_L1:
                    L1CacheSize = AmiCurSize;
                    if (CurL1Cache->SystemCacheType == 0xFF)
                        CurL1Cache->SystemCacheType = AmiType;
                    else
                        CurL1Cache->SystemCacheType = 0x05;
                    CurL1Cache->Associativity = AmiAssoc;
                    break;
                case EFI_CACHE_L2:
                    L2CacheSize = AmiCurSize;
                    if (CurL2Cache->SystemCacheType == 0xFF)
                        CurL2Cache->SystemCacheType = AmiType;
                    else
                        CurL2Cache->SystemCacheType = 0x05;
                    CurL2Cache->Associativity = AmiAssoc;
                    break;
                case EFI_CACHE_L3:
                    L3CacheSize = AmiCurSize;
                    if (CurL3Cache->SystemCacheType == 0xFF)
                        CurL3Cache->SystemCacheType = AmiType;
                    else
                        CurL3Cache->SystemCacheType = 0x05;
                    CurL3Cache->Associativity = AmiAssoc;
                    break;
            } // switch
        } // for

        CurCpuData->CurrentSpeed = (UINT16)(AmiCpuInfo->ActualFreq);
#if AMD_SYSTEM_BOARD == 1
        CurCpuData->MaxSpeed = (UINT16)(AmiCpuInfo->MaxFreq);
#endif
        CurCpuData->ExtClockFreq = (UINT16)(AmiCpuInfo->FSBFreq);
        CurCpuData->ProcessorID_1 = (UINT32)(AmiCpuInfo->Version);
        CurCpuData->ProcessorID_2 = (UINT32)(AmiCpuInfo->Features);
        CurCpuData->Status = 0x41;                  // Socket popuated
                                                    // and CPU enabled
        CurCpuData->Upgrade = SMBIOS_PROCESSOR_UPGRADE; // CPU.sdl tokens
        CurCpuData->Family = SMBIOS_PROCESSOR_FAMILY;
        if(CurNode == 0) {
            FillStringBufferWithSpaces(
                CurCpuData->Version,
                sizeof(CurCpuData->Version));
            MemCpy(
                CurCpuData->Version,
                AmiCpuInfo->BrandString,
                sizeof(CurCpuData->Version) - 1);
            FillStringBufferWithSpaces(
                CurCpuData->Manufacturer,
                sizeof(CurCpuData->Manufacturer));
            MemCpy(
                CurCpuData->Manufacturer,
                AmiCpuInfo->BrandString,
                5);
        }
        else {
            MemCpy(
                CurCpuData->Manufacturer,
                Cpu0Data->Manufacturer,
                sizeof(Cpu0Data->Manufacturer));
            MemCpy(
                CurCpuData->Version,
                Cpu0Data->Version,
                sizeof(Cpu0Data->Version));
        }
        CurL1Cache->CacheConfig = 0x180;
        CurL1Cache->MaxCacheSize = L1CacheSize;  // CacheL1
        CurL1Cache->InstalledSize = L1CacheSize;
        CurL1Cache->SupportSRAM = 0x01;
        CurL1Cache->CurrentSRAM = 0x01;
        CurL1Cache->CacheSpeed = 0;
        CurL1Cache->ErrorCorrectionType = 0x03;

        CurL2Cache->CacheConfig = 0x281;
        CurL2Cache->MaxCacheSize = L2CacheSize;  // CacheL2
        CurL2Cache->InstalledSize = L2CacheSize;
        CurL2Cache->SupportSRAM = 0x01;
        CurL2Cache->CurrentSRAM = 0x01;
        CurL2Cache->CacheSpeed = 0;
        CurL2Cache->ErrorCorrectionType = 0x03;

        CurL3Cache->CacheConfig = 0x302;
        CurL3Cache->MaxCacheSize = L3CacheSize;  // CacheL3
        CurL3Cache->InstalledSize = L3CacheSize;
        CurL3Cache->SupportSRAM = 0x01;
        CurL3Cache->CurrentSRAM = 0x01;
        CurL3Cache->CacheSpeed = 0;
        CurL3Cache->ErrorCorrectionType = 0x03;
    } // for

    Status = pRS->SetVariable(  SmbiosCpuVar,
                                &EfiSmbiosDynamicDataGuid,
                                Attributes,
                                sizeof(CPU_DYNAMIC_DATA),
                                &CpuInfo );
    ASSERT_EFI_ERROR(Status);

    // ==================================================================
    // ==================================================================
    // ==================================================================
    // ===                                                            ===
    // ===      End of SAMPLE TEMPLATE CODE for AMD Warthog           ===
    // ===      platform. Uncomment this block to use.                ===
    // ===                                                            ===
    // ===      Might need changes for other platforms.               ===
    // ===                                                            ===
    // ==================================================================
    // ==================================================================
    // ==================================================================
//----------------------------------------------------------------------------
*/
#endif      // UPDATE_CPU_TYPE4

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//                         ***** OPTIONAL *****
//               (if SMBIOS module is part of the project)
//----------------------------------------------------------------------------
// Procedure:   CreateOnBoardDevDataForSMBios
//
// Description: This function gathers the Onboard Device status information and
//              saves them in a variable named "SmbiosOnBoardVar". This variable
//              with the OnBoard Device information is needed by the SMBIOS
//              module to create the "Type 10" structure.
//
// Input:   None
//
// Output:  EFI_STATUS
//          Variable named "SmbiosOnBoardVar" with on-board device information
//
// Note:    Refer to ONBOARD_DEV_DYNAMIC_DATA in SmbiosDynamicData.h for
//          structure information.
//
//          Set device status to 0 if disabled.
//          Set device status to 0x80 if enabled.
//          Ex: In sample code
//              OnBoardDevInfo.OnBoardDev[0] = 0;           // Disabled
//              OnBoardDevInfo.OnBoardDev[0] = 0x80;        // Enabled
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
CreateOnBoardDevDataForSMBios (VOID)
{
    EFI_STATUS                      Status = EFI_SUCCESS;

#if UPDATE_ONBOARD_DEV_TYPE10
/*
//----------------------------------------------------------------------------
    // ==================================================================
    // ==================================================================
    // ==================================================================
    // ===                                                            ===
    // ===   Start of SAMPLE TEMPLATE CODE for Intel Weybridge CRB    ===
    // ===   platform. Uncomment this block to use.                   ===
    // ===                                                            ===
    // ===   Might need changes for other platforms.                  ===
    // ===                                                            ===
    // ==================================================================
    // ==================================================================
    // ==================================================================

    EFI_GUID                        EfiSmbiosDynamicDataGuid = EFI_SMBIOS_DYNAMIC_DATA_GUID;
    UINTN                           VarSize;
    UINT32                          Attributes = EFI_VARIABLE_BOOTSERVICE_ACCESS;
    ONBOARD_DEV_DYNAMIC_DATA        OnBoardDevInfo;
    UINT64                          PciAddress;
    UINT8                           Value8;
    EFI_GUID gEfiPciRootBridgeIoProtocolGuid  = EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_GUID;
    EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *gPciRootBridgeIo;

    Status = pBS->LocateProtocol(
                                &gEfiPciRootBridgeIoProtocolGuid,
                                NULL,
                                &gPciRootBridgeIo);
    ASSERT_EFI_ERROR(Status);

    // Onboard Video
    PciAddress = PCI_CFG_ADDRESS (0, 0, 0, MCH_REG_GGC);
    gPciRootBridgeIo->Pci.Read (
                                gPciRootBridgeIo,
                                EfiPciWidthUint8,
                                PciAddress,
                                1,
                                &Value8);
    if (Value8 & BIT01) {
        OnBoardDevInfo.OnBoardDev[0] = 0;           // Disabled
    }
    else {
        OnBoardDevInfo.OnBoardDev[0] = 0x80;        // Enabled
    }

    // Onboard LAN
    Value8 = *(UINT8*)(SB_RCBA + R_RCBA_BUC);
    if (Value8 & B_LAN_DISABLE) {
        OnBoardDevInfo.OnBoardDev[1] = 0;           // Disabled
    }
    else {
        OnBoardDevInfo.OnBoardDev[1] = 0x80;        // Enabled
    }

    // Onboard 1394 - Use GPIO49 0/1 = Enabled/Disabled
    Value8 = IoRead32(GPIO_BASE_ADDRESS + ICH_GPIO_GP_LVL2 + 2);
    if (Value8 & BIT01) {
        OnBoardDevInfo.OnBoardDev[2] = 0;           // Disabled
    }
    else {
        OnBoardDevInfo.OnBoardDev[2] = 0x80;        // Enabled
    }

    VarSize = sizeof(ONBOARD_DEV_DYNAMIC_DATA);
    Status = pRS->SetVariable(SmbiosOnBoardVar, &EfiSmbiosDynamicDataGuid,
                        Attributes, VarSize, &OnBoardDevInfo);

    // ==================================================================
    // ==================================================================
    // ==================================================================
    // ===                                                            ===
    // ===   End of SAMPLE TEMPLATE CODE for Intel Weybridge CRB      ===
    // ===   platform. Uncomment this block to use.                   ===
    // ===                                                            ===
    // ===   Might need changes for other platforms.                  ===
    // ===                                                            ===
    // ==================================================================
    // ==================================================================
    // ==================================================================
//----------------------------------------------------------------------------
*/
#endif      // UPDATE_ONBOARD_DEV_TYPE10

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//                         ***** OPTIONAL *****
//               (if SMBIOS module is part of the project)
//----------------------------------------------------------------------------
// Procedure:   CreateOnBoardDevExtInfoForSMBios
//
// Description: This function gathers the Onboard Device status information
//              and saves them in a variable named "SmbiosOnBoardExtVar".
//              This variable with the OnBoard Device Extended information
//              is needed by the SMBIOS module to create the "Type 41"
//              structure.
//
// Input:   None
//
// Output:  EFI_STATUS
//          Variable named "SmbiosOnBoardExtVar" with on-board device
//          information.
//
// Note:    Refer to ONBOARD_DEV_EXT_DYNAMIC_DATA in SmbiosDynamicData.h for
//          structure information.
//
//          Set device status to 0 if disabled.
//          Set device status to 0x80 if enabled.
//          Ex: In sample code
//              OnBoardDevInfo.OnBoardDev[0] = 0;           // Disabled
//              OnBoardDevInfo.OnBoardDev[0] = 0x80;        // Enabled
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
CreateOnBoardDevExtInfoForSMBios (VOID)
{
    EFI_STATUS                      Status = EFI_SUCCESS;

#if UPDATE_DEVICE_EXT_TYPE41
/*
//----------------------------------------------------------------------------
    // ==================================================================
    // ==================================================================
    // ==================================================================
    // ===                                                            ===
    // ===   Start of SAMPLE TEMPLATE CODE for Intel Weybridge CRB    ===
    // ===   platform. Uncomment this block to use.                   ===
    // ===                                                            ===
    // ===   Might need changes for other platforms.                  ===
    // ===                                                            ===
    // ==================================================================
    // ==================================================================
    // ==================================================================

    EFI_GUID                        EfiSmbiosDynamicDataGuid = EFI_SMBIOS_DYNAMIC_DATA_GUID;
    UINTN                           VarSize;
    UINT32                          Attributes = EFI_VARIABLE_BOOTSERVICE_ACCESS;
    ONBOARD_DEV_EXT_DYNAMIC_DATA    OnBoardDevExtInfo;
    UINT64                          PciAddress;
    UINT8                           Value8;
    EFI_GUID gEfiPciRootBridgeIoProtocolGuid  = EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_GUID;
    EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *gPciRootBridgeIo;

    Status = pBS->LocateProtocol(
                                &gEfiPciRootBridgeIoProtocolGuid,
                                NULL,
                                &gPciRootBridgeIo);
    ASSERT_EFI_ERROR(Status);

    // Onboard Video
    PciAddress = PCI_CFG_ADDRESS (0, 0, 0, MCH_REG_GGC);
    gPciRootBridgeIo->Pci.Read (
                                gPciRootBridgeIo,
                                EfiPciWidthUint8,
                                PciAddress,
                                1,
                                &Value8);
    if (Value8 & BIT01) {
        OnBoardDevExtInfo.OnBoardDev[0] = 0;           // Disabled
    }
    else {
        OnBoardDevExtInfo.OnBoardDev[0] = 0x80;        // Enabled
    }

    OnBoardDevExtInfo.BusNumber[0] = 0;

    // Onboard LAN
    Value8 = *(UINT8*)(SB_RCBA + R_RCBA_BUC);
    if (Value8 & B_LAN_DISABLE) {
        OnBoardDevExtInfo.OnBoardDev[1] = 0;           // Disabled
    }
    else {
        OnBoardDevExtInfo.OnBoardDev[1] = 0x80;        // Enabled
    }

    OnBoardDevExtInfo.BusNumber[1] = 0;

    // Onboard 1394 - Use GPIO49 0/1 = Enabled/Disabled
    Value8 = IoRead32(GPIO_BASE_ADDRESS + ICH_GPIO_GP_LVL2 + 2);
    if (Value8 & BIT01) {
        OnBoardDevExtInfo.OnBoardDev[2] = 0;           // Disabled
    }
    else {
        OnBoardDevExtInfo.OnBoardDev[2] = 0x80;        // Enabled
    }

    PciAddress = PCI_CFG_ADDRESS (0, 0x1C, 2, 0x19);
    gPciRootBridgeIo->Pci.Read (
                                gPciRootBridgeIo,
                                EfiPciWidthUint8,
                                PciAddress,
                                1,
                                &Value8);

    OnBoardDevExtInfo.BusNumber[2] = Value8;

    VarSize = sizeof(ONBOARD_DEV_EXT_DYNAMIC_DATA);
    Status = pRS->SetVariable(SmbiosOnBoardExtVar, &EfiSmbiosDynamicDataGuid,
                        Attributes, VarSize, &OnBoardDevExtInfo);

    // ==================================================================
    // ==================================================================
    // ==================================================================
    // ===                                                            ===
    // ===   End of SAMPLE TEMPLATE CODE for Intel Weybridge CRB      ===
    // ===   platform. Uncomment this block to use.                   ===
    // ===                                                            ===
    // ===   Might need changes for other platforms.                  ===
    // ===                                                            ===
    // ==================================================================
    // ==================================================================
    // ==================================================================
//----------------------------------------------------------------------------
*/
#endif      // UPDATE_DEVICE_EXT_TYPE41

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//                     ***** PORTING REQUIRED *****
//               (if SMBIOS module is part of the project)
//----------------------------------------------------------------------------
// Procedure:   CreateBatteryDataForSMBios
//
// Description: This function provides system battery information. SMBIOS
//              Core uses these information to dynamically update SMBIOS
//              Portable Battery Data structure Type 22.
//
// Input:   None
//
// Output:  EFI_STATUS
//          Variable named "SmbiosBatteryVar" with Battery information
//
// Note:    Refer to BATTERY_DYNAMIC_DATA in SmbiosDynamicData.h for
//          structure information.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
CreateBatteryDataForSMBios (VOID)
{
    EFI_STATUS              Status = EFI_SUCCESS;

#if UPDATE_BATTERY_TYPE22
/*
//----------------------------------------------------------------------------
    // ==================================================================
    // ==================================================================
    // ==================================================================
    // ===                                                            ===
    // ===                    Start of dummy code                     ===
    // ===                                                            ===
    // ===        PORTING IS NEEDED FOR INDIVIDUAL PLATFORM !!!       ===
    // ===                                                            ===
    // ==================================================================
    // ==================================================================
    // ==================================================================

    EFI_GUID                EfiSmbiosDynamicDataGuid = EFI_SMBIOS_DYNAMIC_DATA_GUID;
    BATTERY_DYNAMIC_DATA    BatteryInfo;
    UINTN                   VarSize;
    UINT32                  Attributes = EFI_VARIABLE_BOOTSERVICE_ACCESS;
    UINT8                   DeviceName1[] = "BATT 1";
    UINT8                   DeviceName2[] = "Another Battery Name";
    UINT8                   SbdsVersion1[] = "01.12.912";
    UINT8                   SbdsVersion2[] = "00.01";

    BatteryInfo.BatteryDynamicData[0].DesignCapacity = 1;
    BatteryInfo.BatteryDynamicData[0].DesignVoltage = 5000;
    BatteryInfo.BatteryDynamicData[0].SbdsSerialNumber = 0x1111;
    BatteryInfo.BatteryDynamicData[0].SbdsManufacturedDate = 0x2841;
    BatteryInfo.BatteryDynamicData[0].DesignCapacityMult = 1000;
    // When copying strings, MAKE SURE THE ZERO TERMINATOR
    // for the string is included
    MemCpy (BatteryInfo.BatteryDynamicData[0].DeviceName, DeviceName1, sizeof(DeviceName1));
    MemCpy (BatteryInfo.BatteryDynamicData[0].SbdsVersion, SbdsVersion1, sizeof(SbdsVersion1));
    BatteryInfo.BatteryDynamicData[0].Valid = TRUE;

    BatteryInfo.BatteryDynamicData[1].DesignCapacity = 1;
    BatteryInfo.BatteryDynamicData[1].DesignVoltage = 9000;
    BatteryInfo.BatteryDynamicData[1].SbdsSerialNumber = 0x4444;
    BatteryInfo.BatteryDynamicData[1].SbdsManufacturedDate = 0x1814;
    BatteryInfo.BatteryDynamicData[1].DesignCapacityMult = 500;
    // When copying strings, MAKE SURE THE ZERO TERMINATOR
    // for the string is included
    MemCpy (BatteryInfo.BatteryDynamicData[1].DeviceName, DeviceName2, sizeof(DeviceName2));
    MemCpy (BatteryInfo.BatteryDynamicData[1].SbdsVersion, SbdsVersion2, sizeof(SbdsVersion2));
    BatteryInfo.BatteryDynamicData[1].Valid = FALSE;

    BatteryInfo.BatteryDynamicData[2].DesignCapacity = 1;
    BatteryInfo.BatteryDynamicData[2].DesignVoltage = 3000;
    BatteryInfo.BatteryDynamicData[2].SbdsSerialNumber = 0x7777;
    BatteryInfo.BatteryDynamicData[2].SbdsManufacturedDate = 0x0814;
    BatteryInfo.BatteryDynamicData[2].DesignCapacityMult = 200;
    // When copying strings, MAKE SURE THE ZERO TERMINATOR
    // for the string is included
    MemCpy (BatteryInfo.BatteryDynamicData[2].DeviceName, DeviceName2, sizeof(DeviceName2));
    MemCpy (BatteryInfo.BatteryDynamicData[2].SbdsVersion, SbdsVersion2, sizeof(SbdsVersion2));
    BatteryInfo.BatteryDynamicData[2].Valid = FALSE;

    BatteryInfo.BatteryDynamicData[3].DesignCapacity = 1;
    BatteryInfo.BatteryDynamicData[3].DesignVoltage = 1000;
    BatteryInfo.BatteryDynamicData[3].SbdsSerialNumber = 0x9999;
    BatteryInfo.BatteryDynamicData[3].SbdsManufacturedDate = 0x5814;
    BatteryInfo.BatteryDynamicData[3].DesignCapacityMult = 700;
    // When copying strings, MAKE SURE THE ZERO TERMINATOR
    // for the string is included
    MemCpy (BatteryInfo.BatteryDynamicData[3].DeviceName, DeviceName2, sizeof(DeviceName2));
    MemCpy (BatteryInfo.BatteryDynamicData[3].SbdsVersion, SbdsVersion2, sizeof(SbdsVersion2));
    BatteryInfo.BatteryDynamicData[3].Valid = TRUE;

    VarSize = sizeof(BATTERY_DYNAMIC_DATA);
    Status = pRS->SetVariable(SmbiosBatteryVar,
                        &EfiSmbiosDynamicDataGuid,
                        Attributes,
                        VarSize,
                        &BatteryInfo);

    // ==================================================================
    // ==================================================================
    // ==================================================================
    // ===                                                            ===
    // ===                     End of dummy code                      ===
    // ===                                                            ===
    // ==================================================================
    // ==================================================================
    // ==================================================================
//----------------------------------------------------------------------------
*/
#endif      // UPDATE_BATTERY_TYPE22

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SMIBiosBoardDriverEntryPoint
//
// Description: SMBIOS Board driver entry point
//
// Input:       IN EFI_HANDLE           ImageHandle,
//              IN EFI_SYSTEM_TABLE     *SystemTable
//
// Output:      EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
SMIBiosBoardDriverEntryPoint(
    IN EFI_HANDLE           ImageHandle,
    IN EFI_SYSTEM_TABLE     *SystemTable
)
{
    EFI_STATUS              Status;

    InitAmiLib(ImageHandle, SystemTable);

    Status = pBS->InstallProtocolInterface(&ImageHandle,
                                          &gEfiSmbiosBoardProtocolGuid,
                                          EFI_NATIVE_INTERFACE,
                                          &SmbiosBoardProtocol);
    return Status;
}

//****************************************************************************
//****************************************************************************
//**                                                                        **
//**           (C)Copyright 1985-2013, American Megatrends, Inc.            **
//**                                                                        **
//**                          All Rights Reserved.                          **
//**                                                                        **
//**           5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093            **
//**                                                                        **
//**                          Phone: (770)-246-8600                         **
//**                                                                        **
//****************************************************************************
//****************************************************************************
