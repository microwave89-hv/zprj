//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

//*****************************************************************************
// $Header: /Alaska/SOURCE/Core/EDK/DxeMain/UnicodeCollation.c 14    8/28/09 1:21p Felixp $
//
// $Revision: 14 $
//
// $Date: 8/28/09 1:21p $
//*****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Core/EDK/DxeMain/UnicodeCollation.c $
// 
// 14    8/28/09 1:21p Felixp
// 
// 13    8/28/09 12:26p Felixp
// Support for both UnicodeCollation and UnicodeCollation2 protocols 
// (based on value of the EFI_SPECIFICATION_VERSION SDL token).
// 
// 12    7/08/09 5:53p Vyacheslava
// Updated according to the coding standards.
//
// 11    3/05/09 9:53a Felixp
// Minor big fix: Invalid return type in the StriColl funcation
// declaration.
//
// 10    12/16/08 1:36a Iminglin
// The function value of Is_valid_char for compliance.
//
// 9     4/24/07 5:18p Robert
// Updated headers for CHM compatibility and coding standard compliance
//
// 8     10/30/06 6:34p Felixp
// Language list is extended to fix
// FAT driver failure when non-European
// language is selected as a primary language.
//
// 3     2/15/05 5:01p Felixp
// SpecialChars moved here from protocol header
//
// 2     2/03/05 4:01p Felixp
// small bug fix in StrToFat
//
// 1     1/28/05 12:45p Felixp
//
// 3     1/18/05 3:22p Felixp
// PrintDebugMessage renamed to Trace
//
// 2     12/23/04 6:25p Felixp
// bug fix in StrToFat
//
// 7     12/22/04 9:33a Radhikav
// proper comments added
//
// 6     12/20/04 4:00p Radhikav
// made changes to strtofat and metaimatch.
//
// 5     12/08/04 1:22p Radhikav
// made some changes to StrtoFat function.
//
// 4     11/11/04 11:18a Felixp
//
// 3     10/18/04 1:30p Radhikav
// modified metaimatch routine.
//
// 2     10/08/04 3:57p Radhikav
// modified strlwr and strupper routines.
//
// 1     10/05/04 2:47p Radhikav
// Initial check in.
//
//*****************************************************************************
//<AMI_FHDR_START>
//
// Name: Unicode Collation.c
//
// Description: Provides Unicode String functions
//
//<AMI_FHDR_END>
//*****************************************************************************
#include <Protocol/UnicodeCollation.h>
#include <AmiDxeLib.h>

//----------------------------------------------------------------------
// functions prototype

INTN    StriColl (
    IN    EFI_UNICODE_COLLATION_PROTOCOL         *This,
    IN    CHAR16                                 *S1,
    IN    CHAR16                                 *S2

);
BOOLEAN MetaiMatch (
    IN    EFI_UNICODE_COLLATION_PROTOCOL         *This,
    IN    CHAR16                                 *String,
    IN    CHAR16                                 *Patern

);
BOOLEAN StrToFat (
    IN    EFI_UNICODE_COLLATION_PROTOCOL         *This,
    IN    CHAR16                                 *String,
    IN    UINTN                                  FatSize,
    OUT   CHAR8                                  *Fat
);
VOID FatToStr (
    IN  EFI_UNICODE_COLLATION_PROTOCOL          *This,
    IN UINTN                                    FatSize,
    IN CHAR8                                    *Fat,
    OUT CHAR16                                  *String
);
VOID    StrLwr (
    IN    EFI_UNICODE_COLLATION_PROTOCOL        *This,
    IN    OUT CHAR16                            *String
);
VOID EFIAPI StrUpr (
    IN EFI_UNICODE_COLLATION_PROTOCOL           *This,
    IN OUT CHAR16                               *String
);
BOOLEAN is_valid_char(CHAR16 valid);
CHAR16 toupper(CHAR16 Data);
CHAR16 tolower(CHAR16 Value);

//----------------------------------------------------------------------
// Protocol Definitions
EFI_UNICODE_COLLATION_PROTOCOL UnicodeCollationProtocol = {
    StriColl,
    MetaiMatch,
    StrLwr,
    StrUpr,
    FatToStr,
    StrToFat,
    LANGUAGE_CODE_ENGLISH
};

CHAR8 SpecialChars[] = {
     '0', '1', '2', '3', '4', '5', '6',  '7', '8', '9',
    '\\', '.', '_', '^', '$', '~', '!',  '#', '%', '&', 
     '-', '{', '}', '(', ')', '@', '`', '\'', '\0'
};

//----------------------------------------------------------------------
// Function Defintions

//----------------------------------------------------------------------
//<AMI_PHDR_START>
//
// Procedure:   UnicodeCollationDriverEntryPoint
//
// Description: Initializes the Unicode Collation Driver
//
// Input:
//  ImageHandle - EFI Handle for the Unicode Collation Protocol
//  *SystemTable - Pointer to the EFI System Table
//
// Output:  EFI_STATUS
//
// Referrals: InstallProtocolInterface
//
// Notes:
//  Here is the control flow of this function:
//  1. Initialize Ami Lib.
//  2. Install Driver Binding Protocol
//  3. Return EFI_SUCCESS.
//
//<AMI_PHDR_END>
//----------------------------------------------------------------------

EFI_STATUS UnicodeCollationEntryPoint (
    IN EFI_HANDLE       ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable
)
{
    EFI_STATUS Status;
    EFI_HANDLE  Handle = NULL;
    
    Status = SystemTable->BootServices->InstallProtocolInterface(
        &Handle, 
        &gEfiUnicodeCollation2ProtocolGuid,
        EFI_NATIVE_INTERFACE, 
        &UnicodeCollationProtocol
    );
    return Status; 
}

//----------------------------------------------------------------------
//<AMI_PHDR_START>
//
// Procedure:   Stricoll
//
// Description: Performs a case-insensitive comparison of two
//      Null-terminated unicode strings.
//
// Input:
//      *This - pointer to the Unicode Collatioon Protocol
//      *s1 - string one
//      *s2 - string two
//
// Output: None
//
// Return:
//      0 - if strings are equal
//      negative value - if s1 is less than s2
//      positive value - if s2 is less than s2
//
// Modified: None
//
// Referrals: tolower
//
//<AMI_PHDR_END>
//----------------------------------------------------------------------

INTN EFIAPI StriColl (
    IN EFI_UNICODE_COLLATION_PROTOCOL       *This,
    IN CHAR16                               *s1,
    IN CHAR16                               *s2
)
{
    INTN    result;
    
    do {
        result = tolower(*s1) - tolower(*s2);
        
        if (result) 
            break;
    } while ( (*s1++) && (*s2++) );
    
    return result;
}


//----------------------------------------------------------------------
//<AMI_PHDR_START>
//
// Procedure:   StrLwr
//
// Description: Converts all the unicode charecters in a
//      Null-terminated string to lowercase unicode.
//
// Input:
//      *This - pointer to the UnicodeCollation Protocol
//      *String - String to convert to lower case
//
// Output: *String - String now in lower case
//
// Modified: *String
//
// Referrals:  tolower
//
//<AMI_PHDR_END>
//----------------------------------------------------------------------

VOID EFIAPI StrLwr (
    IN EFI_UNICODE_COLLATION_PROTOCOL       *This,
    IN OUT CHAR16                           *String
)
{
    CHAR16 *s = String;
    
    while (*s != L'\0')  { 
        *s = tolower(*s); 
        s++; 
    };
    
}

//----------------------------------------------------------------------
//<AMI_PHDR_START>
//
// Procedure:   StrUpr
//
// Description: Converts all the unicodecharecters in a Null terminated
//      unicode string to a uppercase unicode charecters.
//
// Input:
//      *This - pointer to the UnicodeCollation Protocol
//      *String - String to convert to upper case
//
// Output: *String - String now in lower case
//
// Modified: *String
//
// Referrals:  toupper
//
//<AMI_PHDR_END>
//----------------------------------------------------------------------

VOID EFIAPI StrUpr (
    IN EFI_UNICODE_COLLATION_PROTOCOL  *This,
    IN OUT CHAR16                      *String
)
{
    CHAR16 *s = String;
    
    while (*s != L'\0') { 
        *s = toupper(*s); 
        s++ ;
    };
}


//----------------------------------------------------------------------
//<AMI_PHDR_START>
//
// Procedure:   MetaiMatch
//
// Description: Performs a case insensitive comparision of a
//      Null-terminated unicode pattern string and a null terminated
//      unicode String Converts all the unicodecharecters in a Null terminated
//      unicode string.
//
// Input:
//      *This - pointer to the UnicodeCollation Protocol
//      *String - String to convert to upper case
//      *Pattern
// Output:
//      TRUE    - Pattern was found in String.
//      FALSE   - Pattern was not found in String.
//
//<AMI_PHDR_END>
//----------------------------------------------------------------------

BOOLEAN EFIAPI MetaiMatch (
    IN EFI_UNICODE_COLLATION_PROTOCOL  *This,
    IN CHAR16                          *String,
    IN CHAR16                          *Pattern
)
{
    CHAR16 ch1, ch, temp;
    UINTN  len1, len2;
    
    for (; ;) {
        len1 = Wcslen(String);
        len2 = Wcslen(Pattern);
        
        if (!len1) {
            if (!len2)
                return TRUE;
            else
                return FALSE;
        }
        
        ch1 = *Pattern;
        Pattern ++;
        
        switch (ch1) {
        
                if (*String)
                    return FALSE;
                else
                    return TRUE ;
                
            case '*':
                while (*String) {
                    if (MetaiMatch(This, String, Pattern))
                        return TRUE;
                        
                    String ++;
                }
                
                return MetaiMatch(This, String, Pattern);
                
            case '?':
                if (!*String)
                    return FALSE;
                    
                String ++;
                break;
                
            case '[':
                ch = *String;
                
                if (!ch)
                    return FALSE;
                    
                temp = 0;
                ch1 = *Pattern++;
                
                while ( ch1 ) {
                    if (ch1 == ']')
                        return FALSE;
                        
                    if (ch1 == '-') {
                        ch1 = *Pattern;
                        
                        if ( ch1 == 0 || ch1 == ']' )
                            return FALSE;
                            
                        if ( toupper(ch) >= toupper(temp) && 
                             toupper(ch) <= toupper(ch1) )
                            break;
                    }
                    
                    temp = ch1;
                    
                    if ( toupper(ch) == toupper(ch1) ) //any charecter
                        break;
                        
                    ch1 = *Pattern++;
                }
                
                while (ch1 && ch1 != ']') {
                    ch1 = *Pattern;
                    Pattern ++;
                }
                
                String ++;
                break;
                
            default:
                ch = *String;
                
                if ( toupper(ch) != toupper(ch1) )
                    return FALSE;
                    
                String ++;
                break;
        }
    }
}


//----------------------------------------------------------------------
//<AMI_PHDR_START>
//
// Procedure:   FatToString
//
// Description: Converts an 8.3 FAT file name in an OEM charecter set
//      to a Null-terminated Unicode string.
//
// Input:
//      *This - Pointer to the Unicode Collation Protocol
//      *FatSize - size of the FAT string
//      *Fat - 8.3 FAT ascii string
// Output:
//      *String - Null terminated Unicode String
//
// Return: VOID
//
//<AMI_PHDR_END>
//----------------------------------------------------------------------

VOID EFIAPI FatToStr (
    IN EFI_UNICODE_COLLATION_PROTOCOL     *This,
    IN UINTN                              FatSize,
    IN CHAR8                              *Fat,
    OUT CHAR16                            *String
)
{
    for (; (*Fat && FatSize) != 0; String++, Fat++, FatSize --)
        *String = *Fat;
    
    *String = 0;
}

//----------------------------------------------------------------------
//<AMI_PHDR_START>
//
// Procedure:   StrtoFat
//
// Description: Converts a Null-terminated unicode string to legal
//      characters in a FAT file using an OEM charecter set. Converts all
//      the unicodecharecters in a Null terminated unicode string.
//
// Input:
//      *This - Pointer to the Unicode Collation Protocol
//      *FatSize - size of the FAT string
//      *String - Null terminated Unicode String
// Output:
//      *Fat - 8.3 FAT ascii string
//
// Return:
//      TRUE  - Pattern was found in String.
//      FALSE - Pattern was not found in String.
//
// Referrals:  toupper
//
//<AMI_PHDR_END>
//----------------------------------------------------------------------

BOOLEAN  StrToFat (
    IN EFI_UNICODE_COLLATION_PROTOCOL     *This,
    IN CHAR16                             *String,
    IN UINTN                              FatSize,
    OUT CHAR8                             *Fat
)
{
    BOOLEAN InvalidChar;
    int i = 0, j = 0;
    
    InvalidChar = FALSE;
    
    while (String[i] && FatSize) {
    
        if ( String[i] != 0x002E && 
             String[i] != 0x0020 ) {
             
            if ( is_valid_char(String[i]) == 1 ) {
                Fat[j] = (CHAR8)toupper(String[i]);
                j++;
                
            } else {
                Fat[j] = '_';
                InvalidChar = TRUE;
                j++;
            }
            
            FatSize --;
        }
        
        i++;
    }
    
    return(InvalidChar);
}

//----------------------------------------------------------------------
//Local functions

//----------------------------------------------------------------------
//<AMI_PHDR_START>
//
// Procedure:   is_valid_char
//
// Description: Checks to see if the character passed in is a valid.
//      ASCII Character
//
// Input: valid - character to check
//
// Return:
//      TRUE  - Character is valid
//      FALSE - Character is invalid
//
//<AMI_PHDR_END>
//----------------------------------------------------------------------

BOOLEAN is_valid_char(CHAR16 valid)
{
    UINT16 i;
    CHAR16 tempval;
    
    if ( (valid >= 0x0061 && valid <= 0x007a) ||
         (valid >= 0x00E0 && valid <= 0x00F6) ||
         (valid >= 0x00F8 && valid <= 0x00Fe) )
        return TRUE;
        
    else if ( (valid >= 0x0041 && valid <= 0x005a)   ||
                (valid >= 0x00C0 && valid <= 0x00D6) ||
                (valid >= 0x00D8 && valid <= 0x00DE) )
        return TRUE;
        
    else {
        tempval = (CHAR16)valid;
        
        for ( i=0; SpecialChars[i]; i++ ) {
            if (tempval == SpecialChars[i])
                return TRUE;
        }
    }
    
    return (FALSE);
}


//----------------------------------------------------------------------
//<AMI_PHDR_START>
//
// Procedure:   tolower
//
// Description: Converts Unicode standard European characters to lower case
//
// Input: Data - character to convert
//
// Return: the Unicode character in lower case Unicode format
//
//<AMI_PHDR_END>
//----------------------------------------------------------------------

CHAR16 tolower( CHAR16  Data  )
{
    if ( ('A' <= Data && Data <= 'Z')   ||
         (Data >= 0xC0 && Data <= 0xD6) ||
         (Data >= 0xD8 && Data <= 0xDE) )
        return (CHAR16)(Data + 0x20);
    else
        return Data;
}


//----------------------------------------------------------------------
//<AMI_PHDR_START>
//
// Procedure:   toupper
//
// Description: Converts Unicode standard Europeancharacters to upper case
//
// Input: Value - character to convert
//
// Return: the character in upper case Unicode format
//
//<AMI_PHDR_END>
//----------------------------------------------------------------------

CHAR16 toupper( CHAR16  Value )
{
    if ( ('a' <= Value && Value  <= 'z')  ||
         (Value >= 0xE0 && Value <= 0xF6) ||
         (Value >= 0xF8 && Value <= 0xFE) )
        return (CHAR16)(Value - 0x20);
    else
        return Value;
}

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
