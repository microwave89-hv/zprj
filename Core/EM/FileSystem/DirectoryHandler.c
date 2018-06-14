//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
// $Header: /Alaska/SOURCE/Core/Modules/FileSystem/DirectoryHandler.c 6     7/07/10 2:54p Pats $
//
// $Revision: 6 $
//
// $Date: 7/07/10 2:54p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Core/Modules/FileSystem/DirectoryHandler.c $
// 
// 6     7/07/10 2:54p Pats
// EIP 38291: Fails Klocwork test.
// Problem: No error return if short name is null in GenUniqueShortName()
// Solution: Added error return.
// 
// 5     7/02/09 5:47p Pats
// Updated to latest coding standard. No code changes.
//
// 4     4/13/07 7:07p Pats
// Edited to conform with coding standards. No code changes.
//
// 3     11/03/05 2:16p Srinin
// Fixed VC7.1 warning msg.
//
// 2     9/08/05 4:41p Pats
// Fixed problem of short filename having exactly 8 characters in mame and
// 3 in ext being handled as long file name (and ~ name generated).
//
// 1     4/26/05 6:05p Srinin
//
//
//**********************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------
//
// Name:    DirectoryHandler.c
//
// Description: Fat File System driver -- Directory Functions
//
//----------------------------------------------------------------------
//<AMI_FHDR_END>

//----------------------------------------------------------------------

#include "FileSystem.h"

//----------------------------------------------------------------------


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       GetNameComponent
//
// Description:     Gets the name component from a path
//
// Parameters:      CHAR16 *Path - Pointer to input path
//                  CHAR16 *Name - Pointer to output name
//
// Return value:    CHAR16 * path truncated to name
//
// Modified:        None
//
// Referral(s):     None
//
// NOTE(S):
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

CHAR16 *
GetNameComponent (
    IN CHAR16  *Path,
    OUT CHAR16 *Name
)
{
    UINTN Len = 0;
    
    while (*Path && *Path != '\\') {
        if (Len < 259) {
            Name[Len] = *Path;
            Len += 1;
        }
        
        Path += 1;
    }
    
    Name[Len] = 0;
    
// Remove trailing '\'
    while (*Path == '\\') {
        Path += 1;
    }
    
    return Path;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       GenShortFilename
//
// Description:     Generates a DOS 8.3 name component from a path
//
// Parameters:      VOLUME_INFO *Vol - Pointer to volume information structure
//                  CHAR16 *InPath - Pointer to input path
//                  CHAR8 *ShortName - Pointer to generated DOS 8.3 name
//
// Return value:    EFI_STATUS - Status of operation (EFI_SUCCESS)
//
// Modified:        None
//
// Referral(s):     None
//
// NOTE(S):
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
GenShortFilename (
    IN VOLUME_INFO *Vol,
    IN CHAR16      *InPath,
    OUT CHAR8      *ShortName
)
{
    CHAR16 *Ext;
    CHAR16 *p;
    CHAR16 CharC;
    
    MemSet(ShortName, 11, 0x20); // Fill short name with spaces
    
    // If this is a '.' or '..' name then it's a special form
    if (InPath[0] == '.' && InPath[1] == 0) {
        ShortName[0] = '.';
        goto Done;
    }
    
    if (InPath[0] == '.' && InPath[1] == '.' && InPath[2] == 0) {
        ShortName[0] = '.';
        ShortName[1] = '.';
        goto Done;
    }
    
// Find the last '.'
    Ext = NULL;
    
    for (p = InPath; *p; p++) {
        if (*p == '.') {
            Ext = p;
        }
    }
    
    if (!Ext) {
        Ext = p;
    }
    
    // Create 8.3 name.  Convert chars to fat values.  Skip any '.' or ' '.
    CharC = *Ext; // Save first char of ext.
    *Ext = 0;  // Zero-terminate name
    Vol->UnicodeCollationInterface->StrToFat (Vol->UnicodeCollationInterface,
            InPath,
            8,
            ShortName);
    *Ext = CharC; // Restore first char of ext.
    Vol->UnicodeCollationInterface->StrToFat (Vol->UnicodeCollationInterface,
            Ext,
            3,
            ShortName+8);
            
Done:
    return EFI_SUCCESS;
    
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       GenUniqueShortFname
//
// Description:     Generates a unique DOS 8.3 name from a possible long name
//
// Parameters:      FILE_HANDLE *fh - Pointer to the file handle structure
//                  CHAR16 *LongName - Pointer to the possible long name
//                  CHAR8 *ShortName - Pointer to generated DOS 8.3 name
//                  BOOLEAN *LfnNeeded - Indicates a long name entry is
//                                       needed for this input name
//
// Return value:    EFI_STATUS - EFI_SUCCESS - Unique name generated
//                               EFI_ACCESS_DENIED - this name already exists
//                               on the volume
//
// Modified:        None
//
// Referral(s):     None
//
// NOTE(S):
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
GenUniqueShortFname (
    IN FILE_HANDLE *fh,
    IN CHAR16      *LongName,
    OUT CHAR8      *ShortName,
    OUT BOOLEAN    *LfnNeeded
)
{

    EFI_STATUS     Status;
    VOLUME_INFO    *Vol = fh->VolumeInterface;
    DIR_ENTRY_LIST *Del;
    CHAR8          Temp[12];
    CHAR16         Temp2[13];
    CHAR16         Temp3[13];
    CHAR8          CounterString[6];
    UINTN          Counter, CounterStringLen;
    UINTN          k;
    CHAR8          *s;
    
    Status = GenShortFilename(Vol, LongName, ShortName);
    
    if (EFI_ERROR(Status)) return Status;
    
    // Check for dot or dotdot entries
    if ((LongName[0] == '.' && LongName[1] == 0) ||
            (LongName[0] == '.' && LongName[1] == '.' && LongName[2] == 0)) {
        *LfnNeeded = FALSE;
        return EFI_SUCCESS;
    }
    
    if (!fh->DirList.pHead) {
        ReadAllDirectoryEntries (fh);
    }
    
    // Find out if the input name is already a valid short name -- i.e., no
    // ~Counter is needed.
    k = Wcslen(LongName) * sizeof(CHAR16) + 2;      // Include Null character
    
    if (k <= 26) {  // If it could be a legal short name... 
                    // (13 * 2 including '.' + 2 for NULL)
        ExtractShortFileName(Vol, Temp2, ShortName);
        pBS->CopyMem(Temp3, LongName, k);
        // Make an upper case copy of the input
        Vol->UnicodeCollationInterface->StrUpr(Vol->UnicodeCollationInterface, Temp3);
        
        if ( !Wcscmp(Temp2, Temp3 )) {
            // If the extracted name is same as upper case copy of input...
            // If the extracted name doesn't equal the non-upper case original,
            // it must have some lower case letters in it, 
            // so therefore a long name entry is needed.
            if (!Wcscmp(Temp2, LongName)) *LfnNeeded = FALSE;
            
            else *LfnNeeded = TRUE;
            
            if (FindMatchingDirEntry (fh, LongName, &Del)) {
                return EFI_ACCESS_DENIED; // Name already exists, can't create
                
            } else {
                return EFI_SUCCESS;  // Name is ok, return
            }
        }
    }
    
    // Now append "~Counter" to the short name, incrementing "Counter"
    // until the file name is unique in that Path
    Zeromemory (CounterString, sizeof(CounterString));
    
    for (Counter = 1; Counter < 65536; Counter++) {
        pBS->CopyMem(Temp, ShortName, 11);
        if (Temp[0] == ' ') return EFI_INVALID_PARAMETER;
        ItoaEx(Counter, CounterString, 10, FALSE);
        CounterStringLen = Strlen(CounterString);
        
        // Right-justify the "~Counter"
        for (k = 0; k < 7 - CounterStringLen; k += 1) {
            if (Temp[k] == ' ') {
                k--;    // In case the name is short
                break;
            }
        }
        
        // Append the "~Counter" to the name
        Temp[k++] = '~';
        
        for (s = CounterString; *s; Temp[k++] = *s++) ;
        
        // Search for the generated name
        Temp[11] = 0;
        
        if (!FindMatchingSFNDirEntry (fh, Temp, &Del)) {
            pBS->CopyMem(ShortName, Temp, 11);
            *LfnNeeded = TRUE;
            return EFI_SUCCESS;
        }
    }
    
    return EFI_ACCESS_DENIED;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       CopyCharsToLfnSlot
//
// Description:     Copies a character to the appropriate slot of a long name
//                  directory structure
//
// Parameters:      DIR_ENTRY_LFN *Slot - Pointer to long name directory
//                                        structure
//                  UINT32 *SlotPos - Pointer to slot position to fill
//                  UINT16 Ch - The character to be placed in the slot
//
// Return value:    None
//
// Modified:        None
//
// Referral(s):     None
//
// NOTE(S):
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

static VOID
CopyCharsToLfnSlot (
    DIR_ENTRY_LFN *Slot,
    UINT32        SlotPos,
    UINT16        Ch
)
{
    if ((SlotPos >= 0)  && (SlotPos <= 4)) Slot->Dir_Name0_4[SlotPos] = Ch;
    
    else if ((SlotPos >= 5)  && (SlotPos <= 10)) Slot->Dir_Name5_10 [SlotPos-5]  = Ch;
    
    else if ((SlotPos >= 11) && (SlotPos <= 12)) Slot->Dir_Name11_12[SlotPos-11] = Ch;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       SplitLFN
//
// Description:     Splits a long file name into long name directory enties.
//
// Parameters:      CHAR16 *LongName - Pointer to a long file name
//                  DIR_ENTRY_32 *ShortEntry - Pointer to the corresponding
//                                             short directory entry
//                  DIR_ENTRY_LFN *Slot - The structure of the long directory
//                                        entries to be filled
//
// Return value:    EFI_STATUS - Status of the operation (EFI_SUCCESS)
//
// Modified:        None
//
// Referral(s):     None
//
// NOTE(S):
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
SplitLFN (
    IN CHAR16         *LongName,
    IN DIR_ENTRY_32   *ShortEntry,
    OUT DIR_ENTRY_LFN *Slot,
    OUT UINT32        *NumSlots
)
{
    UINT32 NamePos;
    UINT32 SlotPos;
    UINT8  Order;
    UINT8  Checksum = LfnChecksum((UINT8 *)ShortEntry);
    UINT32 CharCnt;
    UINT32 Position;
    INTN   i;
    
    CharCnt = (UINT32) Wcslen(LongName);
    *NumSlots = CharCnt / 13;
    
    if (CharCnt % 13) *NumSlots += 1; // Name not evenly divisible by 13
    
    Order = *NumSlots;
    Position = 13 * (Order - 1); // Starting position for extracting characters.
    
    for (i=0; Order; i++, Order--) {
        // Fill in the non-name stuff
        Slot[i].Dir_Order    = Order; // 1-based numeration
        Slot[i].Dir_Attr     = (ATTR_LONG_NAME);
        Slot[i].Dir_Reserved = 0;
        Slot[i].Dir_Checksum = Checksum;
        Slot[i].Dir_FstClus  = 0;
        Slot[i].Dir_FstClus  = 0;
        // Fill in the name
        NamePos = Position;
        SlotPos = 0;
        
        while (LongName[NamePos] && SlotPos < 13) {
            CopyCharsToLfnSlot(&Slot[i], SlotPos++, LongName[NamePos]);
            
            if (++NamePos == MAX_LFN_LENGTH) return EFI_INVALID_PARAMETER;
        }
        
        if (i == 0) { // If last slot
            // Mark the slot as last
            Slot[i].Dir_Order |= 0x40;
            // Insert a Unicode NULL terminator, only if it fits into the slots
            CopyCharsToLfnSlot(&Slot[i], SlotPos++, 0x0000);
            
            // Pad the remaining characters of the slot with FFFFh
            while (SlotPos < 13) CopyCharsToLfnSlot(&Slot[i], SlotPos++, 0xFFFF);
        }
        
        Position -= 13; // Back up to next section to process
    }
    
    return EFI_SUCCESS;
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
