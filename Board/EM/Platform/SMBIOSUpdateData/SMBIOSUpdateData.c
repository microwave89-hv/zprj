//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
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
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/Platform/SMBIOSUpdateData/SMBIOSUpdateData.c 1     2/09/12 12:35a Yurenlai $
//
// $Revision: 1 $
//
// $Date: 2/09/12 12:35a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/Platform/SMBIOSUpdateData/SMBIOSUpdateData.c $
// 
// 1     2/09/12 12:35a Yurenlai
// Initial check in.
// 
//*************************************************************************


#include "Tiano.h"
#include "EfiDriverLib.h"
#include <Protocol\SMBios.h>
#include <Protocol\SmbiosGetFlashDataProtocol.h>
#include "SmbiosUpdateDataProtocol.h"

EFI_GUID   gEfiSmbiosProtocolGuid = EFI_SMBIOS_PROTOCOL_GUID;
EFI_SMBIOS_PROTOCOL *gSmbiosProtocol;

EFI_GUID    gEfiSmbiosUpdateDataProtocolGuid    = EFI_SMBIOS_UPDATE_DATA_PROTOCOL_GUID;

EFI_SMBIOS_UPDATE_DATA_PROTOCOL SmbiosUpdateDataProtocol = {SMBIOS_GetFreeHandle,
                                                           SMBIOS_FindStructure,
                                                           SMBIOS_GetStructureBase,
                                                           SMBIOS_DeleteStructure,
                                                           SMBIOS_CopyStructure,
                                                           SMBIOS_InsertStructure};

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetStructureLength
//
// Description: Returns the length of the structure pointed by BufferStart
//              in bytes
//
// Input:       UINT8 *BufferStart
//
// Output:      Structure Size
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16
GetStructureLength(
    IN  UINT8    *BufferStart
)
{
	UINT8     *BufferEnd = BufferStart;

	BufferEnd += ((SMBIOS_STRUCTURE_HEADER*)BufferStart)->Length;
	while (*(UINT16*)BufferEnd != 0) {
		BufferEnd++;
	}
	return (UINT16)(BufferEnd + 2 - BufferStart);   // +2 for double zero terminator
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetTotalStructureSize
//
// Description: Returns the total structure size
//
// Input:       UINT8   *Buffer
//
// Output:      Total structure size
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16
GetTotalStructureSize(
    IN  UINT8    *Buffer
)
{
	UINT16  Length = 0;
	UINT16  BlockSize;

	while (((SMBIOS_STRUCTURE_HEADER*)Buffer)->Type != 127) {
		BlockSize = GetStructureLength(Buffer);
		Length = Length +BlockSize;
		Buffer += BlockSize;
	}
	Length = Length+ GetStructureLength(Buffer);
	return Length;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   FindStructureByType
//
// Description: Find structure type starting from memory location pointed by
//              Buffer
//
// Input:       UINT8   **Buffer
//              UINT8   **StructureFoundPtr
//              UINT8   SearchType
//              UINT8   Instance
//
// Output:      If SearchType is found:
//                UINT8   **Buffer - Points to the next structure
//                UINT8   **StructureFoundPtr - Points to the structure
//                                              that was found
//              If SearchType is not found:
//                UINT8   **Buffer - No change
//                UINT8   **StructureFoundPtr = NULL
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN
FindStructureByType(
  IN OUT  UINT8    **Buffer,            
  IN OUT  UINT8    **StructureFoundPtr, 
  IN      UINT8    SearchType,
  IN      UINT8    Instance             // 1-based
)
{
  UINT8     *BufferPtr = *Buffer;
  BOOLEAN   FindStatus = FALSE;

  *StructureFoundPtr = NULL;
  while (((SMBIOS_STRUCTURE_HEADER*)BufferPtr)->Type != 127) {
    if (((SMBIOS_STRUCTURE_HEADER*)BufferPtr)->Type == SearchType) {
      // If this instance, set the find status flag and update the Buffer pointer
      if (--Instance == 0) {
        FindStatus = TRUE;
        *StructureFoundPtr = BufferPtr;
        *Buffer = BufferPtr + GetStructureLength(BufferPtr);
        break;
      }
    }
    BufferPtr += GetStructureLength(BufferPtr);
  }
  if ((FindStatus == FALSE) && (SearchType == 127)) {
    FindStatus = TRUE;
    *StructureFoundPtr = BufferPtr;
    *Buffer = BufferPtr + GetStructureLength(BufferPtr);
  }
  return FindStatus;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   FindStructureByHandle
//
// Description: Find structure handle starting from memory location pointed
//              by Buffer
//
// Input:       UINT8   **Buffer
//              UINT16  Handle
//
// Output:      If SearchType is found:
//                UINT8   **Buffer - Points to the structure that was found
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN
FindStructureByHandle(
    IN OUT  UINT8     **Buffer,
    IN      UINT16    Handle
)
{
	while (((SMBIOS_STRUCTURE_HEADER*)*Buffer)->Handle != Handle) {
		if (((SMBIOS_STRUCTURE_HEADER*)*Buffer)->Type == 127) {
			return FALSE;
		}
		*Buffer += GetStructureLength(*Buffer);
	}
	return TRUE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetNumberOfStructures
//
// Description: Returns the number of structures starting from Buffer til
//              (and including) type 127 structure.
//
// Input:       UINT8   *Buffer
//
// Output:      Number of structures
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16
GetNumberOfStructures(
    IN  UINT8    *Buffer
)
{
	UINT8     *BufferPtr = Buffer;
	UINT16    SmbiosStrucCount = 1;

	while (((SMBIOS_STRUCTURE_HEADER*)BufferPtr)->Type != 127) {
		++SmbiosStrucCount;
		BufferPtr += GetStructureLength(BufferPtr);
	}
	return SmbiosStrucCount;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetLargestStructureSize
//
// Description: Returns the largest structure size
//
// Input:       UINT8   *Buffer
//
// Output:      Largest structure size
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16
GetLargestStructureSize(
    IN  UINT8    *Buffer
)
{
	UINT8     *BufferPtr = Buffer;
	UINT8     *LastBufferPtr;
	UINT16    LargestStructureSize = 0;
	UINT16    CurrentStructureSize;

	while (((SMBIOS_STRUCTURE_HEADER*)BufferPtr)->Type != 127) {
		LastBufferPtr = BufferPtr;
		BufferPtr += ((SMBIOS_STRUCTURE_HEADER*)BufferPtr)->Length;
		while (TRUE) {
			if ((*(UINT16*)BufferPtr) == 0) {
				BufferPtr += 2;
				break;
			}
			BufferPtr++;
		}
		CurrentStructureSize = (UINT16)(BufferPtr - LastBufferPtr);
		if (CurrentStructureSize > LargestStructureSize) {
			LargestStructureSize = CurrentStructureSize;
		}
	}
	return LargestStructureSize;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SmbiosCheckSum
//
// Description: Returns the checksum of "length" bytes starting from the
//              "*ChecksumSrc"
//
// Input:       UINT8 *ChecksumSrc
//              UINT8 length
//
// Output:      Checksum value
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8
SmbiosCheckSum(
    IN  UINT8    *ChecksumSrc,
    IN  UINT8    length
)
{
	UINT8     Checksum = 0;
	UINT8     i;

	for (i = 0; i < length; i++) {
		Checksum = Checksum + *ChecksumSrc++;
	}
	return (0 - Checksum);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   UpdateEPSHeader
//
// Description: Updates the SMBIOS Entry Point Header
//
// Input:       SMBIOS_TABLE_ENTRY_POINT  *pSmbiosTableEntryPoint
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
UpdateEPSHeader(
    IN  SMBIOS_TABLE_ENTRY_POINT    *pSmbiosTableEntryPoint
)
{
    UINT8    *SmbiosDataTableAddr = NULL; 
  
    // Get Smbios Data Table Address
    SmbiosDataTableAddr = (UINT8*)(UINTN)pSmbiosTableEntryPoint->TableAddress;

	// Updating EPS Header
	// Update SMBIOS Data Structure Table length in EPS Header
	pSmbiosTableEntryPoint->TableLength = GetTotalStructureSize(SmbiosDataTableAddr);

	// Find and update number of SMBios Structures in EPS Header
	pSmbiosTableEntryPoint->NumberOfSmbiosStructures = GetNumberOfStructures(SmbiosDataTableAddr);

	// Find and update largest SMBios Structure in EPS Header
	pSmbiosTableEntryPoint->MaxStructureSize = GetLargestStructureSize((UINT8*)(UINTN)pSmbiosTableEntryPoint->TableAddress);

	// Update Checksums in EPS Header
	pSmbiosTableEntryPoint->IntermediateChecksum = 0;
	pSmbiosTableEntryPoint->IntermediateChecksum = SmbiosCheckSum((UINT8*)pSmbiosTableEntryPoint + 0x10, 15);
	pSmbiosTableEntryPoint->EntryPointStructureChecksum = 0;
	pSmbiosTableEntryPoint->EntryPointStructureChecksum = SmbiosCheckSum((UINT8*)pSmbiosTableEntryPoint,
	                                                                     pSmbiosTableEntryPoint->EntryPointLength);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SMBIOS_GetFreeHandle
//
// Description: SMBIOSUpdateData protocol - Searches available handle 
//                                          of Smbios Data Table
//                                      
//
// Input:       SMBIOS_TABLE_ENTRY_POINT  *pSmbiosTableEntryPoint
//
// Output:      UINT16 Handle or -1(if not found)
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16
SMBIOS_GetFreeHandle(
    IN  SMBIOS_TABLE_ENTRY_POINT    *pSmbiosTableEntryPoint
)
{
    EFI_STATUS    FoundStatus;

    UINT16        Handle = 0;
	UINT8         *StructurePtr = NULL;
    UINT8         *SmbiosDataTableAddr = NULL; 
  
    // Get Smbios Data Table Address
    SmbiosDataTableAddr = (UINT8*)(UINTN)pSmbiosTableEntryPoint->TableAddress;

    //Count Handle form 0 to 0xFFFF to find available Handle
    for(Handle = 0; Handle < 0xFFFF; Handle++){
        StructurePtr = SmbiosDataTableAddr;
        FoundStatus = FindStructureByHandle(&StructurePtr,Handle);
        if(!FoundStatus){
            return Handle;
        }
    }

	return (UINT16)-1; // No available Handle to use;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SMBIOS_FindStructure
//
// Description: SMBIOSUpdateData protocol - Searches handle of Smbios Table by Type 
//                                      
//
// Input:       SMBIOS_TABLE_ENTRY_POINT  *pSmbiosTableEntryPoint
//              UINT8                     Type
//              UINT8                     Index
//
// Output:      UINT16 Handle or -1(if not found)
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16
SMBIOS_FindStructure(
    IN  SMBIOS_TABLE_ENTRY_POINT  *pSmbiosTableEntryPoint,
    IN  UINT8                     Type, 
    IN  UINT8                     Index
) 
{
    EFI_STATUS    FoundStatus;

    UINT16        Handle = 0;
	UINT8         *StructurePtr = NULL;
    UINT8         *SmbiosDataTableAddr = NULL; 
  
    // Get Smbios Data Table Address
    SmbiosDataTableAddr = (UINT8*)(UINTN)pSmbiosTableEntryPoint->TableAddress;
    
    FoundStatus = FindStructureByType(&SmbiosDataTableAddr, &StructurePtr, Type, Index);
    Handle = ((SMBIOS_STRUCTURE_HEADER*)StructurePtr)->Handle;

    // Return Handle of found structure
    if(FoundStatus){
	    return Handle; 
    } else{
        return (UINT16)-1;
    }

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SMBIOS_GetStructureBase
//
// Description: SMBIOSUpdateData protocol - Get structure address by Handle 
//                                      
//
// Input:       SMBIOS_TABLE_ENTRY_POINT  *pSmbiosTableEntryPoint
//              UINT8                     *StructureFoundPtr
//              UINT16                    Handle
//              
// Output:      UINT8 * or NULL - Points to the structure that was found
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8 *
SMBIOS_GetStructureBase(
    IN  SMBIOS_TABLE_ENTRY_POINT  *pSmbiosTableEntryPoint,
    IN  UINT16                    Handle
) 
{
    EFI_STATUS      FoundStatus;

	UINT8           *FoundStructurePtr = NULL;
    UINT8           *SmbiosDataTableAddr = NULL; 
  
    // Get Smbios Data Table Address
    SmbiosDataTableAddr = (UINT8*)(UINTN)pSmbiosTableEntryPoint->TableAddress;
    FoundStructurePtr = SmbiosDataTableAddr;

	FoundStatus = FindStructureByHandle(&FoundStructurePtr, Handle);

    if(FoundStatus){
        return FoundStructurePtr;
    } else{
        return NULL;
    }

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SMBIOS_DeleteStructure
//
// Description: SMBIOSUpdateData protocol - Delete SMBIOS structure by handle
//
// Input:       SMBIOS_TABLE_ENTRY_POINT  *pSmbiosTableEntryPoint
//              UINT16                    Handle
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
SMBIOS_DeleteStructure(
    IN  SMBIOS_TABLE_ENTRY_POINT  *pSmbiosTableEntryPoint,
    IN  UINT16                    Handle
)
{
/*
    EFI_STATUS    FoundStatus;

	UINT16        BufferSize = 0;
  	UINT8         *StructurePtr = NULL;
	UINT8         *NextStructurePtr = NULL;
    UINT8         *SmbiosDataTableAddr = NULL; 

    // Get Smbios Data Table Address
    SmbiosDataTableAddr = (UINT8*)pSmbiosTableEntryPoint->TableAddress;
    StructurePtr = SmbiosDataTableAddr;

    FoundStatus = FindStructureByHandle(&StructurePtr, Handle); 

	if (FoundStatus){
        // Calculate data size which we want to move
    	BufferSize = GetTotalStructureSize(StructurePtr) - GetStructureLength(StructurePtr);

        // Calculate next structure address
		NextStructurePtr = StructurePtr + GetStructureLength(StructurePtr);

		// Copy Structure
        gBS->CopyMem(StructurePtr, NextStructurePtr, BufferSize);
		
        UpdateEPSHeader(pSmbiosTableEntryPoint);
	}

	return FoundStatus;
*/
    return gSmbiosProtocol->SmbiosDeleteStructure(Handle);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SMBIOS_CopyStructure
//
// Description: SMBIOSUpdateData protocol - Copy SMBIOS structure by Handle
//              to a new allocated memory
//
// Input:       SMBIOS_TABLE_ENTRY_POINT  *pSmbiosTableEntryPoint
//              UINT16                    Handle
//
// Output:      UINT8 * or NULL - Points to the new structure address
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8 *
SMBIOS_CopyStructure(
    IN  SMBIOS_TABLE_ENTRY_POINT  *pSmbiosTableEntryPoint,
    IN  UINT16                    Handle
)
{
    EFI_STATUS    FoundStatus;

    UINT16        BufferSize;
	UINT8         *BufferPtrTemp;
	UINT8         *FoundStructurePtr = NULL;
    UINT8         *SmbiosDataTableAddr = NULL; 

    // Get Smbios Data Table Address
    SmbiosDataTableAddr = (UINT8*)(UINTN)pSmbiosTableEntryPoint->TableAddress;
    FoundStructurePtr = SmbiosDataTableAddr;

    // Check Handle of Structure if exit
    FoundStatus = FindStructureByHandle(&FoundStructurePtr, Handle); 
    
	if (FoundStatus){
    	BufferSize = GetStructureLength(FoundStructurePtr);
        
        // Allocate Memory for structure copy
        gBS->AllocatePool(EfiBootServicesData, BufferSize, &BufferPtrTemp);

        // Copy Structure to memory
		gBS->CopyMem(BufferPtrTemp, FoundStructurePtr, BufferSize);

        return BufferPtrTemp;

	} else {
	    return  NULL;
    }

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SMBIOS_InsertStructure
//
// Description: SMBIOSUpdateData protocol - Insert SMBIOS structure 
//
// Input:       SMBIOS_TABLE_ENTRY_POINT  *pSmbiosTableEntryPoint
//              UINT8                     *SourceStructurePtr
//              UINTN                     BufferSize 
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
SMBIOS_InsertStructure(
    IN  SMBIOS_TABLE_ENTRY_POINT  *pSmbiosTableEntryPoint,
    IN  UINT8                     *StructurePtrTemp,
    IN  UINT16                    BufferSize
)
{
/*
    EFI_STATUS    FoundStatus;

    UINT16        Handle = 0;
	UINT16        EOSBufferSize = 0;
	UINT8         *EOSBufferPtrTemp = NULL;
    UINT8         *FoundStructurePtr = NULL;
    UINT8         *SmbiosDataTableAddr = NULL; 

    // Get Smbios Data Table Address
    SmbiosDataTableAddr = (UINT8*)pSmbiosTableEntryPoint->TableAddress;
    EOSBufferPtrTemp = SmbiosDataTableAddr;
    FoundStructurePtr = SmbiosDataTableAddr;

    // Check Handle of Structure if available
    Handle = ((SMBIOS_STRUCTURE_HEADER*)StructurePtrTemp)->Handle;   
    FoundStatus = FindStructureByHandle(&FoundStructurePtr, Handle);

	if (!FoundStatus){
        // Move End-of-table Structure(Type 127) to allocate space for structure copy
        FindStructureByHandle(&EOSBufferPtrTemp, 127);
        EOSBufferSize = GetStructureLength(EOSBufferPtrTemp);
        FoundStructurePtr = EOSBufferPtrTemp + BufferSize;
		gBS->CopyMem(FoundStructurePtr, EOSBufferPtrTemp, EOSBufferSize);

        // Copy Source Structure form memory
		gBS->CopyMem(EOSBufferPtrTemp, StructurePtrTemp, BufferSize);

        UpdateEPSHeader(pSmbiosTableEntryPoint);
    }

    return !FoundStatus;
*/
    UINT16        Handle = 0;

    Handle = ((SMBIOS_STRUCTURE_HEADER*)StructurePtrTemp)->Handle;   
    return gSmbiosProtocol->SmbiosAddStrucByHandle(Handle, StructurePtrTemp, BufferSize);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: SMIBiosUpdateMemoryRecordDriverEntryPoint  
//
// Description: Update memory record DXE driver for Intel Tiano SmBiosMemory Driver.
//
// Input:       
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
EFI_STATUS SMBIOSUpdateDataDriverEntryPoint(
    IN EFI_HANDLE           ImageHandle,
	IN EFI_SYSTEM_TABLE     *SystemTable
)
{
    EFI_STATUS Status;

    DxeInitializeDriverLib (ImageHandle, SystemTable);

	Status = gBS->LocateProtocol(&gEfiSmbiosProtocolGuid, NULL, &gSmbiosProtocol);
	ASSERT_EFI_ERROR(Status);

    Status = gBS->InstallProtocolInterface(&ImageHandle,
	                                       &gEfiSmbiosUpdateDataProtocolGuid,
	                                       EFI_NATIVE_INTERFACE,
	                                       &SmbiosUpdateDataProtocol);

    return Status;
}

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************