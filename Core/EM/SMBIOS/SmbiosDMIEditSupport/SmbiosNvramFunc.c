//**********************************************************************//
//**********************************************************************//
//**                                                                  **//
//**        (C)Copyright 1985-2015, American Megatrends, Inc.         **//
//**                                                                  **//
//**                       All Rights Reserved.                       **//
//**                                                                  **//
//**        5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093         **//
//**                                                                  **//
//**                       Phone: (770)-246-8600                      **//
//**                                                                  **//
//**********************************************************************//
//**********************************************************************//

//**********************************************************************//
// $Header: /Alaska/SOURCE/Modules/SMBIOS/SmbiosDMIEditSupport/SmbiosNvramFunc.c 11    2/17/15 1:16p Davidd $
//
// $Revision: 11 $
//
// $Date: 2/17/15 1:16p $
//**********************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SMBIOS/SmbiosDMIEditSupport/SmbiosNvramFunc.c $
// 
// 11    2/17/15 1:16p Davidd
// [TAG]  		EIP205509
// [Category]  	Improvement
// [Description]  	Merge Aptio V Smbios EIP193807, 193858, 196901 changes
// into Aptio 4 Smbios
// [Files]  		SmbiosDmiEdit.sdl
// SmbiosDmiEdit.c
// SmbiosNvramFunc.c
// SmbiosGetFlashData.c
//
// 10    11/15/13 4:34p Davidd
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
// 9     9/04/12 11:05a Davidd
// [TAG]  		EIP96286
// [Category]  	Improvement
// [Description]  	Please help to reserve DMI Data for AFUDOS with /r in
// Capsule Mode
// [Files]  		Smbios.sdl
// SmbiosDMIEdit.mak
// SmbiosNvramFunc.c
//
// 8     8/02/12 12:48p Davidd
// [TAG]  		EIP96064
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	SMBIOS: DmiEdit support creates NVRAM variables with names
// of incorrect length
// [RootCause]  	Swprintf_s function creates 15 characters variable name
// with NULL terminator in last byte.
// [Solution]  	Use Swprintf function instead
// [Files]  		Smbios.c
// SmbiosDMIEditFunc.c
// SmbiosNvramFunc.c
//
// 7     11/17/11 2:41p Davidd
// [TAG]           EIP74579
// [Category]      Improvement
// [Description]   Update SMBIOS moudule to let AMDELNX support SMBIOS
// spec 2.7
//                 (remove the 64 characters string limitation)
// [Files]         Smbios.h
//                 SmbiosStaticData.sdl
//                 Smbios.c
//                 SMBios.dxs
//                 SmbiosDMIEdit.sdl
//                 SmbiosDMIEdit.h
//                 SmbiosDMIEditFunc.c
//                 SmbiosNvram.c
//                 SmbiosFlashData.sdl
//
// 6     5/04/11 3:20p Davidd
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
// 5     3/02/11 11:47a Davidd
// [TAG]  		EIP54264
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Data is assumed valid without checking after some
// GetVariable calls
// [RootCause]  	No error checking
// [Solution]  	Problem has been fixed with code changes
// [Files]  		SmbiosNvramFunc.c
// SmbiosDMIEditFunc.c
//
// 4     1/14/11 3:57p Davidd
// [TAG]  		EIP50564
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	BIOS can't keep DMI data after flash BIOS with /p /b /n /r
// parameters
// [RootCause]  	Side effect of previous changes (NVRAM variable name
// format
// has been changed)
// [Solution]  	Problem has been fixed with code changes
// [Files]  		SmbiosNvramFunc.c
//
// 3     10/21/10 11:36a Davidd
// [TAG]           EIP46394
// [Category]      BUG FIX
// [Severity]      Important
// [Symptom]       Incorrect variable size for GetVariable() usage in
// Smbios module
// [RootCause]     GetVariable is called with incorrect "DataSize" type.
// [Solution]      Corrected "DataSize" type in all GetVariable calls.
// [Files]
//    Smbios.c
//    SmbiosDMIEditFunc.c
//    SmbiosNvramFunc.c
//
// 2     12/04/09 3:28p Davidd
// Corrected the DMIEdit data not updated after being updated 5-6 times
// (when NVRAM is used to store DMIEdit data) - EIP 30837.
//
// 1     2/02/09 4:21p Davidd
// Initial checkin
//
//**********************************************************************//

#include <AmiDxeLib.h>
#include <Token.h>
#include "Protocol\Smbios.h"
#include "SmbiosDMIEdit.h"

#if SMBIOS_DMIEDIT_DATA_LOC == 2
static BOOLEAN      DmiEditVarPresent =  FALSE;
EFI_GUID            gEfiSmbiosNvramGuid = EFI_SMBIOS_NVRAM_DATA_GUID;
CHAR16              *DmiArrayVar = L"DmiArray";
DMI_VAR             DmiArray[DMI_ARRAY_COUNT] = {0};
UINTN               DmiArraySize = DMI_ARRAY_COUNT * sizeof(DMI_VAR);
CHAR16              *S1 = L"                ";
UINT8               DmiData[0x1000];
UINT8               *DmiDataPtr;
UINT8               Buffer[0x400];
UINTN               BufferSize;
UINTN               DmiDataLength[DMI_ARRAY_COUNT];
UINT8               gRecoveryKeepDMIFlag = FALSE;

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   PreserveDmiEditData
//
// Description: Preserve the DMIEdit data by loading its data into memory
//              prior to flashing
//
// Input:       None
//
// Output:      None
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
PreserveDmiEditData (VOID)
{
    EFI_STATUS  Status;
    UINT8       Count;
    UINT8       Index;

	//
	// Get number of DMI data records in NVRAM
	//
	// Note: DMI data record actually starts with record #1,
	//		 first record #0 holds total number of DMI data records
	//       instead of TABLE_INFO
	//       ===> DmiArray[0].Type = count
	//
    Status = pRS->GetVariable(
                        DmiArrayVar,
                        &gEfiSmbiosNvramGuid,
                        NULL,
                        &DmiArraySize,
                        &DmiArray[0]);

    if (Status == EFI_SUCCESS) {
        DmiDataPtr = DmiData;

        Count = DmiArray[0].Type;     // Note: DmiArray[0] has count #

		// Get DMI data into memory. The data will be saved back into
		// NVRAM later in RestoreDmiEditData
        for (Index = 0; Index < Count; Index++) {
            Swprintf(S1, L"DmiVar%02x%04x%02x%02x",
					   DmiArray[Index + 1].Type,
					   DmiArray[Index + 1].Handle,
					   DmiArray[Index + 1].Offset,
					   DmiArray[Index + 1].Flags);

            BufferSize = sizeof(Buffer);
            Status = pRS->GetVariable(
                                S1,
                                &gEfiSmbiosNvramGuid,
                                NULL,
                                &BufferSize,
                                &Buffer);

			if (Status == EFI_SUCCESS) {
                MemCpy(DmiDataPtr, Buffer, BufferSize);
				DmiDataLength[Index] = BufferSize;
                DmiDataPtr += BufferSize;
			}
			else {
				DmiDataLength[Index] = 0;
			}
        }

        DmiEditVarPresent = TRUE;
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   RestoreDmiEditData
//
// Description: Restore the DMIEdit data in NVRAM with data previously loaded
//              in memory by PreserveDmiEditData.
//
// Input:       None
//
// Output:      None
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
RestoreDmiEditData (VOID)
{
    UINT8       Count;
    UINT8       Index;

	// DMI data were read and saved in memory in PreserveDmiEditData.
	// Now save DMI data back into NVRAM if present
    if (DmiEditVarPresent) {
        pRS->SetVariable(
                    DmiArrayVar,
                    &gEfiSmbiosNvramGuid,
                    EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_NON_VOLATILE,
                    DmiArraySize,
                    &DmiArray[0]);

        DmiDataPtr = DmiData;

        Count = DmiArray[0].Type;     // Note: DmiArray[0] has count # instead of Type/Offset

        for (Index = 0; Index < Count; Index++) {
            Swprintf(S1, L"DmiVar%02x%04x%02x%02x",
					   DmiArray[Index + 1].Type,
					   DmiArray[Index + 1].Handle,
					   DmiArray[Index + 1].Offset,
					   DmiArray[Index + 1].Flags);

            pRS->SetVariable(
                        S1,
                        &gEfiSmbiosNvramGuid,
                        EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_NON_VOLATILE,
						DmiDataLength[Index],
                        DmiDataPtr);

            DmiDataPtr += DmiDataLength[Index];
        }
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   RecoveryPreserveDmiEditData
//
// Description: Preserve the DMIEdit data by loading its data into memory
//              prior to flashing (for capsule mode)
//
// Input:       None
//
// Output:      None
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
RecoveryPreserveDmiEditData (VOID)
{
    EFI_STATUS      Status;
    EFI_GUID        gEfiSmbiosNvramGuid = {0x4b3082a3, 0x80c6, 0x4d7e, { 0x9c, 0xd0, 0x58, 0x39, 0x17, 0x26, 0x5d, 0xf1 }};
    CHAR16          *PreserveSmbiosNvramVar = L"PreserveSmbiosNvramVar";
    UINTN           Size = sizeof (UINT8);
    UINT32          PreserveSmbiosNvram;

    gRecoveryKeepDMIFlag = FALSE;

    Status = pRS->GetVariable (
            PreserveSmbiosNvramVar,
            &gEfiSmbiosNvramGuid,
            NULL,
            &Size,
            &PreserveSmbiosNvram
            );

    if (!EFI_ERROR (Status)) {
        gRecoveryKeepDMIFlag = TRUE;
        PreserveDmiEditData ();
    }

    Status = pRS->SetVariable (
            PreserveSmbiosNvramVar,
            &gEfiSmbiosNvramGuid,
            EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_NON_VOLATILE,
            0,
            NULL
            );
    ASSERT_EFI_ERROR(Status);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   RecoveryRestoreDmiEditData
//
// Description: Restore the DMIEdit data in NVRAM with data previously loaded
//              in memory by PreserveDmiEditData (for capsule mode)
//
// Input:       None
//
// Output:      None
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
RecoveryRestoreDmiEditData (VOID)
{
    if (gRecoveryKeepDMIFlag) {
        RestoreDmiEditData ();
    }

    gRecoveryKeepDMIFlag = FALSE;
}
#endif

//**********************************************************************//
//**********************************************************************//
//**                                                                  **//
//**        (C)Copyright 1985-2015, American Megatrends, Inc.         **//
//**                                                                  **//
//**                       All Rights Reserved.                       **//
//**                                                                  **//
//**        5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093         **//
//**                                                                  **//
//**                       Phone: (770)-246-8600                      **//
//**                                                                  **//
//**********************************************************************//
//**********************************************************************//
