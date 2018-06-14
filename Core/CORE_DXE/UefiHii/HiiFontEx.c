//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
// $Header: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Core/CORE_DXE/UefiHii/HiiFontEx.c 2     9/17/13 10:19p Thomaschen $
//
// $Revision: 2 $
//
// $Date: 9/17/13 10:19p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Core/CORE_DXE/UefiHii/HiiFontEx.c $
// 
// 2     9/17/13 10:19p Thomaschen
// Update for EIP105534 and EIP126176.
// 
// 1     11/21/12 4:08a Wesleychen
// Update rev.6 for EIP105534.
// 11    5/16/13 5:01p Artems
// [TAG]  		EIP123904
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	HiiFont and HiiConfig SCT tests are failed
// [RootCause]  	Regression bugs when implementing new features or spec
// updates
// [Solution]  	Fixed code logic
// [Files]  		HiiConfig.c HiiFontEx.c
// 
// 10    5/02/13 1:52p Artems
// [TAG]  		EIP121673
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	Incorrect line width returned by function StringToImage
// [RootCause]  	When determine line width function ignored flag
// "IGNORE_IF_NO_GLYPH"
// so line width was bigger if some glyphs were absent
// [Solution]  	Modified code logic to not count width of absent glyphs
// [Files]  		HiiFontEx.c
// 
// 9     5/02/13 1:43p Artems
// [TAG]  		EIP113105
// [Category]  	Spec Update
// [Severity]  	Important
// [Description]  	Wording for proportional font display was vague. After
// clarification
// code logic was slightly changed
// [Files]  		HiiFontEx.c HiiPrivate.h
// 
// 8     3/26/13 3:18p Artems
// [TAG]  		EIP119250
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	System hang on Setup entry 
// [RootCause]  	Incorrect boundaries checking in HiiFontEx.c function
// CheckVisible()
// [Solution]  	Changed checking condition
// [Files]  		HiiFontEx.c
// 
// 7     2/25/13 4:44p Artems
// [TAG]  		EIP101673
// [Category]  	New Feature
// [Description]  	Add support for AMI custom large fixed font
// [Files]  		HiiDatabase.c HiiFontEx.c HiiPrivate.h UefiHiiUtils.c GC.c
// new LargeFont Core modulePart
// 
// 6     11/14/12 6:03p Artems
// [TAG]  		EIP105534
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	system hangs during SCT execution
// [RootCause]  	Incorrect handling of FORM_FEED escape character in
// StringToImage function
// [Solution]  	Graphics console - added flag to ignore line breaks
// HiiFont - fixed multiline drawing logic
// [Files]  		Gc.c HiiFont.c HiiFontEx.c
// 
// 5     8/24/12 5:34p Artems
// [TAG]  		EIP N/A
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	One character is not displayed properly
// [RootCause]  	Never accounted for the case, where character is
// completely below base line
// [Solution]  	added check that character height is less than OffsetY
// [Files]  		HiiFontEx.c
// 
// 4     6/15/12 12:21p Artems
// [TAG]  		EIP N/A
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	doesn't build in 32-bit mode
// [RootCause]  	Signed/Unsigned mismatch reported by 32-bit compiler
// [Solution]  	typecasted one parameter to INTN
// [Files]  		HiiFont.c HiiFontEx.c
// 
// 3     6/14/12 6:32p Artems
// [TAG]  		EIP83593
// [Category]  	New Feature
// [Description]  	Proportional font support for Aptio fixed SCT reported
// bugs
// [Files]  		HiiFont.c HiiFontEx.c
// 
// 2     5/24/12 3:00p Artems
// [TAG]  		EIP83593
// [Category]  	Bug Fix
// [Severity]  	Critical
// [Symptom]  	system dead loops in HiiGetFontInfo function
// [RootCause]  	When loop through linked list of installed fonts pointer
// was not updated
// [Solution]  	Added pointer update
// [Files]  		HiiFontEx.c
// 
// 1     5/22/12 3:29p Artems
// [TAG]  		EIP83593
// [Category]  	New Feature
// [Description]  	Proportional font support
// [Files]  		HiiFontEx.c HiiFont.c HiiDatabase.c HiiString.c HiiPrivate.h
// UefiHii.h
// 
// 
//**********************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:	HiiFontEx.c
//
// Description:	Proportional font support
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include <UefiHii.h>
#include <AmiDxeLib.h>
#include "HiiPrivate.h"

#define LOOSE_SIZE_MARGIN 4

extern HII_DATABASE_PRIVATE_DATA PrivateData;
extern SIMPLE_FONT DefaultFont[];
extern EFI_FONT_HANDLE CurFont;   //font to use
extern CHAR16 *DrawString;        //string to draw
extern EFI_HII_OUT_FLAGS DrawFlags;
extern DLIST DrawLines;
extern UINTN ImageWidth;
extern UINTN ImageHeight;
extern EFI_GRAPHICS_OUTPUT_BLT_PIXEL DefForegroundColor;
extern EFI_GRAPHICS_OUTPUT_BLT_PIXEL DefBackgroundColor;

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   DuplicateGlyph
//
//  Description:
//  This function duplicates glyph from Origin and assigns it to the Char
//
//  Input:
//  IN OUT FONT_LINK *Font - pointer to current font
//  IN CHAR16 Char - character to assign glyph to
//  IN CHAR16 Origin - character to assign glyph from
//
//  Output:
//  EFI_NOT_FOUND - glyph for Origin character not found
//  EFI_SUCCESS - glyph created successfully
//  EFI_OUT_OF_RESOURCES - not enough memory to duplicate glyph
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS DuplicateGlyph(
    IN OUT FONT_LINK *Font,
    IN CHAR16 Char,
    IN CHAR16 Origin
)
{
    EFI_STATUS Status;
    GLYPH_LINK *Link = (GLYPH_LINK *)Font->Glyphs.pHead;
    GLYPH_LINK *New;

    while(Link != NULL) {
        if(Link->Char == Origin)
            break;
        Link = (GLYPH_LINK *) Link->Link.pNext;
    }

    if(Link == NULL)
        return EFI_NOT_FOUND;

    Status = pBS->AllocatePool(EfiBootServicesData, sizeof(GLYPH_LINK), &New);
    if(!EFI_ERROR(Status)) {
        New->Char = Char;
        New->Cell = Link->Cell;
        New->GlyphBlock = Link->GlyphBlock;
        DListAdd(&(Font->Glyphs), (DLINK *)New);
    }
    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   AddGlyphs
//
//  Description:
//  This function adds glyphs to specified font
//
//  Input:
//  IN OUT FONT_LINK *Font - pointer to current font
//  IN EFI_HII_GLYPH_INFO Cell - variable that contains font dimensions
//  IN UINT8 *GlyphBlock - pointer to glyph block
//  IN UINT16 Count - number of glyphs to add
//  IN CHAR16 Char - first character to assign glyph to
//  OUT UINTN *BytesProcessed - number of bytes from glyph block that were assigned
//
//  Output:
//  EFI_SUCCESS - glyph created successfully
//  EFI_OUT_OF_RESOURCES - not enough memory to add glyphs
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS AddGlyphs(
    IN OUT FONT_LINK *Font,
    IN EFI_HII_GLYPH_INFO Cell,
    IN UINT8 *GlyphBlock,
    IN UINT16 Count,
    IN CHAR16 Char,
    OUT UINTN *BytesProcessed
)
{
    EFI_STATUS Status;
    GLYPH_LINK *Glyph;
    UINTN Bytes = ((Cell.Width + 7) / 8) * Cell.Height;
    UINTN i;

    for(i = 0; i < Count; i++) {
        Status = pBS->AllocatePool(EfiBootServicesData, sizeof(GLYPH_LINK), &Glyph);
        if(EFI_ERROR(Status))
            return Status;

        Glyph->Cell = Cell;
        Glyph->Char = Char;
        Char++;
        Glyph->GlyphBlock = GlyphBlock;
        GlyphBlock += Bytes;
        DListAdd(&(Font->Glyphs), (DLINK *)Glyph);
    }

    *BytesProcessed = Bytes * Count;
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   ParseGlyphs
//
//  Description:
//  This function parses packed glyphs and creates glyphs for characters
//
//  Input:
//  IN OUT FONT_LINK *Font - pointer to current font
//
//  Output:
//  EFI_ERROR - some error was encountered during parsing
//  EFI_SUCCESS - glyph created successfully
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ParseGlyphs(
    IN OUT FONT_LINK *Font
)
{
    EFI_STATUS Status;
    CHAR16 Current = 1;
    EFI_HII_GLYPH_INFO Default = Font->FontPackage->Cell;
    EFI_HII_GLYPH_INFO CurCell;
    UINT8 *Walker = (UINT8 *)Font->FontPackage;
    UINT8 *EndMarker;
    UINTN Bytes;
    UINT16 CurCount;
    static const EFI_HII_GLYPH_INFO ZeroCell = { 0, 0, 0, 0, 0 };
    EFI_HII_GLYPH_INFO ChangeCell;
    UINTN BelowBaseLine;
    UINTN AboveBaseLine;
    UINTN MaxBelowBaseLine = 0;
    UINTN MaxAboveBaseLine = 0;

    EndMarker = Walker + Font->FontPackage->Header.Length;
    Walker += Font->FontPackage->GlyphBlockOffset;
    ChangeCell = Default;

    do {
        switch (*Walker) {
            case EFI_HII_GIBT_SKIP1:
                Current += ((EFI_HII_GIBT_SKIP1_BLOCK *)Walker)->SkipCount;
                Walker += sizeof(EFI_HII_GIBT_SKIP1_BLOCK);
                break;
            case EFI_HII_GIBT_SKIP2:
                Current += ((EFI_HII_GIBT_SKIP2_BLOCK *)Walker)->SkipCount;
                Walker += sizeof(EFI_HII_GIBT_SKIP2_BLOCK);
                break;
            case EFI_HII_GIBT_EXT1:
                Walker += sizeof(EFI_HII_GIBT_EXT1_BLOCK);
                break;
            case EFI_HII_GIBT_EXT2:
                Walker += sizeof(EFI_HII_GIBT_EXT2_BLOCK);
                break;
            case EFI_HII_GIBT_EXT4:
                Walker += sizeof(EFI_HII_GIBT_EXT4_BLOCK);
                break;
            case EFI_HII_GIBT_DEFAULTS:
                Default = ((EFI_HII_GIBT_DEFAULTS_BLOCK *)Walker)->Cell;
                ChangeCell = Default;
                Walker += sizeof(EFI_HII_GIBT_DEFAULTS_BLOCK);
                break;
            case EFI_HII_GIBT_END:
                break;
            case EFI_HII_GIBT_GLYPH:
                CurCell = ((EFI_HII_GIBT_GLYPH_BLOCK *)Walker)->Cell;
                ChangeCell = CurCell;
                Walker += sizeof(EFI_HII_GIBT_GLYPH_BLOCK);
                Status = AddGlyphs(Font, CurCell, Walker, 1, Current, &Bytes);
                if(EFI_ERROR(Status))
                    return Status;
                Walker += Bytes;
                Current++;
                break;
            case EFI_HII_GIBT_GLYPH_DEFAULT:
                Walker += sizeof(EFI_HII_GIBT_GLYPH_DEFAULT_BLOCK);
                Status = AddGlyphs(Font, Default, Walker, 1, Current, &Bytes);
                if(EFI_ERROR(Status))
                    return Status;
                Walker += Bytes;
                Current++;
                break;
            case EFI_HII_GIBT_GLYPHS:
                CurCell = ((EFI_HII_GIBT_GLYPHS_BLOCK *)Walker)->Cell;
                CurCount = ((EFI_HII_GIBT_GLYPHS_BLOCK *)Walker)->Count;
                ChangeCell = CurCell;
                Walker += sizeof(EFI_HII_GIBT_GLYPHS_BLOCK);
                Status = AddGlyphs(Font, CurCell, Walker, CurCount, Current, &Bytes);
                if(EFI_ERROR(Status))
                    return Status;
                Walker += Bytes;
                Current += CurCount;
                break;
            case EFI_HII_GIBT_GLYPHS_DEFAULT:
                CurCount = ((EFI_HII_GIBT_GLYPHS_DEFAULT_BLOCK *)Walker)->Count;
                Walker += sizeof(EFI_HII_GIBT_GLYPHS_DEFAULT_BLOCK);
                Status = AddGlyphs(Font, Default, Walker, CurCount, Current, &Bytes);
                if(EFI_ERROR(Status))
                    return Status;
                Walker += Bytes;
                Current += CurCount;
                break;
            case EFI_HII_GIBT_DUPLICATE:
                Status = DuplicateGlyph(Font, Current, ((EFI_HII_GIBT_DUPLICATE_BLOCK *)Walker)->CharValue);
                if(EFI_ERROR(Status))
                    return Status;
                Walker += sizeof(EFI_HII_GIBT_DUPLICATE_BLOCK);
                Current++;
                break;
            default:
                return EFI_NOT_FOUND;
        }

        if(MemCmp(&ChangeCell, (VOID *)&ZeroCell, sizeof(EFI_HII_GLYPH_INFO))) {
            if(ChangeCell.OffsetY < 0) {
                BelowBaseLine = (UINTN)(0 - ChangeCell.OffsetY);
	            AboveBaseLine = (ChangeCell.Height > BelowBaseLine) ? (ChangeCell.Height - BelowBaseLine) : 0;
            } else {
                AboveBaseLine = ChangeCell.Height + ChangeCell.OffsetY;
                BelowBaseLine = 0;
            }
            MaxBelowBaseLine = (MaxBelowBaseLine >= BelowBaseLine) ? MaxBelowBaseLine : BelowBaseLine;
            MaxAboveBaseLine = (MaxAboveBaseLine >= AboveBaseLine) ? MaxAboveBaseLine : AboveBaseLine;
            ChangeCell = ZeroCell;
        }

    } while(*Walker != 0 && Walker <= EndMarker);

    Font->FontHeight = MaxBelowBaseLine + MaxAboveBaseLine;
    Font->FontBaseLine = MaxAboveBaseLine;
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   RepackGlyphBlock
//
//  Description:
//  This function repacks glyph block of AMI custom font package to be similar
//  to proportional font glyph block for easier processing
//
//  Input:
//  IN OUT FONT_LINK *Font - pointer to current font
//
//  Output:
//  EFI_ERROR - some error was encountered during parsing
//  EFI_SUCCESS - glyph created successfully
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS RepackGlyphBlock(
    IN UINT8 *GlyphBlock,
    IN UINT16 Width,
    IN UINT16 Height
)
{
    EFI_STATUS Status;
    UINTN Size;
    UINT8 *Tmp;
    UINT16 Line;
    UINT16 i, j, k = 0;

    Line = (Width + 7) / 8;     //how many bytes describe one line of glyph
    Size = Line * Height;
    Status = pBS->AllocatePool(EfiBootServicesData, Size, &Tmp);
    if(EFI_ERROR(Status))
        return Status;

    for(i = 0; i < Height; i++) {
        for(j = 0; j < Line; j++) {
            Tmp[k] = GlyphBlock[i + j * Height];
            k++;
        }
    }
    MemCpy(GlyphBlock, Tmp, Size);
    pBS->FreePool(Tmp);
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   ParseAmiGlyphs
//
//  Description:
//  This function parses custom AMI packed glyphs and creates glyphs for characters
//
//  Input:
//  IN OUT FONT_LINK *Font - pointer to current font
//
//  Output:
//  EFI_ERROR - some error was encountered during parsing
//  EFI_SUCCESS - glyph created successfully
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ParseAmiGlyphs(
    IN OUT FONT_LINK *Font
)
{
    EFI_STATUS Status;
    EFI_NARROW_GLYPH *Walker;
    EFI_HII_GLYPH_INFO CurCell;
    AMICUSTOM_SIMPLE_FONT_PACKAGE_HDR *AmiHdr;
    UINT16 i;
    UINTN Bytes;

    AmiHdr = (AMICUSTOM_SIMPLE_FONT_PACKAGE_HDR *)Font->FontPackage;
    CurCell.Width = AmiHdr->Width;
    CurCell.Height = AmiHdr->Height;
    CurCell.OffsetX = 0;
    CurCell.OffsetY = 0;
    Walker = (EFI_NARROW_GLYPH *)(AmiHdr + 1);
    for(i = 0; i < AmiHdr->NumberOfNarrowGlyphs; i++) {
        CurCell.AdvanceX = (Walker->Attributes & EFI_GLYPH_NON_SPACING) ? 0 : CurCell.Width;
        Status = RepackGlyphBlock(Walker->GlyphCol1, CurCell.Width, CurCell.Height);
        if(EFI_ERROR(Status))
            return Status;
        Status = AddGlyphs(Font, CurCell, Walker->GlyphCol1, 1, Walker->UnicodeWeight, &Bytes);
        if(EFI_ERROR(Status))
            return Status;

        Walker = (EFI_NARROW_GLYPH *)(Walker->GlyphCol1 + Bytes);
    }

    Font->FontHeight = AmiHdr->Height;
    Font->FontBaseLine = AmiHdr->Height;

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   ParseFontsPackage
//
//  Description:
//  This function parses font package
//
//  Input:
//  IN EFI_HII_FONT_PACKAGE_HDR *Package - pointer to font package
//
//  Output:
//  EFI_ERROR - some error was encountered during parsing
//  EFI_SUCCESS - glyph created successfully
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ParseFontsPackage(
	IN EFI_HII_FONT_PACKAGE_HDR *Package
)
{
    EFI_STATUS Status;
    EFI_HII_FONT_PACKAGE_HDR *Copy;
    FONT_LINK *Font;

/* first make global copy of the package */
    Status = pBS->AllocatePool(EfiBootServicesData, Package->Header.Length, &Copy);
    if(EFI_ERROR(Status))
        return Status;
    MemCpy(Copy, Package, Package->Header.Length);

/* create Font link */
    Status = pBS->AllocatePool(EfiBootServicesData, sizeof(FONT_LINK), &Font);
    if(EFI_ERROR(Status))
        return Status;

/* initialize font link */
    Font->FontPackage = Copy;
    DListInit(&(Font->Glyphs));

    if(Package->Header.Type == AMI_HII_PACKAGE_FONTS)
        Status = ParseAmiGlyphs(Font);
    else
        Status = ParseGlyphs(Font);

    if(!EFI_ERROR(Status))
        DListAdd(&(PrivateData.FontList), (DLINK *)Font);
 
    return Status;   
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   MatchName
//
//  Description:
//  This function checks whether passed name matches name of the passed font
//
//  Input:
//  IN FONT_LINK *Font - pointer to font
//  IN CHAR16 *FontName - pointer to font name to match with
//  IN FONT_MATCH_MASK Mask - matching rules
//
//  Output:
//  TRUE - names are matched
//  FALSE - names are not matched
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN MatchName(
    IN FONT_LINK *Font,
    IN CHAR16 *FontName,
    IN FONT_MATCH_MASK Mask
)
{
    UINT8 *Walker;

    if(Mask.MatchName == MATCH_INGNORE)
        return TRUE;

    if(Font->FontPackage->Header.Type == AMI_HII_PACKAGE_FONTS &&
       !Wcscmp(FontName, L"Ami font"))
        return TRUE;

    Walker = (UINT8 *)Font->FontPackage;
    Walker += sizeof(EFI_HII_FONT_PACKAGE_HDR);
    /* now Walker points to font name */
    if(Wcscmp(FontName, (CHAR16 *)Walker))
       return FALSE;
    return TRUE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   MatchStyle
//
//  Description:
//  This function checks whether passed style matches style of the passed font
//
//  Input:
//  IN FONT_LINK *Font - pointer to font
//  IN EFI_HII_FONT_STYLE FontStyle - font style to match with
//  IN FONT_MATCH_MASK Mask - matching rules
//
//  Output:
//  TRUE - styles are matched
//  FALSE - styles are not matched
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN MatchStyle(
    IN FONT_LINK *Font,
    IN EFI_HII_FONT_STYLE FontStyle,
    IN FONT_MATCH_MASK Mask
)
{
    EFI_HII_FONT_STYLE Cur;

    if(Mask.MatchStyle == MATCH_INGNORE)
        return TRUE;

    if(Font->FontPackage->Header.Type == AMI_HII_PACKAGE_FONTS)
        Cur = EFI_HII_FONT_STYLE_NORMAL;
    else
        Cur = Font->FontPackage->FontStyle;

    if(FontStyle == Cur)
        return TRUE;

/* when restyle is ordered we support interchange between Normal, Bold and Italic styles */
    if(Mask.MatchStyle == MATCH_LOOSE && 
       FontStyle <= 3 &&
       Cur <= 3)
        return TRUE;

    return FALSE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   MatchSize
//
//  Description:
//  This function checks whether passed size matches size of the passed font
//
//  Input:
//  IN FONT_LINK *Font - pointer to font
//  IN UINT16 FontSize - font size to match with
//  IN FONT_MATCH_MASK Mask - matching rules
//
//  Output:
//  TRUE - sizes are matched
//  FALSE - sizes are not matched
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN MatchSize(
    IN FONT_LINK *Font,
    IN UINT16 FontSize,
    IN FONT_MATCH_MASK Mask
)
{
    UINT16 Cur;

    if(Mask.MatchSize == MATCH_INGNORE)
        return TRUE;

    if(Font->FontPackage->Header.Type == AMI_HII_PACKAGE_FONTS)
        Cur = ((AMICUSTOM_SIMPLE_FONT_PACKAGE_HDR *)Font->FontPackage)->Height;
    else
        Cur = Font->FontPackage->Cell.Height;

    if(FontSize == Cur)
        return TRUE;

/* when resize is ordered we support interchange sizes within +/- LOOSE_SIZE_MARGIN from given size */
    if(Mask.MatchSize == MATCH_LOOSE && 
       Cur <= FontSize + LOOSE_SIZE_MARGIN &&
       Cur >= FontSize - LOOSE_SIZE_MARGIN)
        return TRUE;

    return FALSE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   FindGlyph
//
//  Description:
//  This function checks whether glyph for passed character is present, and returns it
//  if necessary
//
//  Input:
//  IN DLIST Glyphs - linked list of glyphs to search within
//  IN CHAR16 Char - character value to return glyph for
//  OUT GLYPH_LINK **Match OPTIONAL - pointer to store returned glyph
//
//  Output:
//  TRUE - glyph found
//  FALSE - glyph not found
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN FindGlyph(
    IN DLIST Glyphs,
    IN CHAR16 Char,
    OUT GLYPH_LINK **Match OPTIONAL
)
{
    GLYPH_LINK *Link = (GLYPH_LINK *)Glyphs.pHead;

    while(Link != NULL) {
        if(Link->Char == Char) {
            if(Match != NULL)
                *Match = Link;
            return TRUE;
        }
        Link = (GLYPH_LINK *)Link->Link.pNext;
    }
    return FALSE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   MatchString
//
//  Description:
//  This function checks whether all character glyphs are present for given string
//
//  Input:
//  IN FONT_LINK *Font - pointer to the font
//  IN CONST EFI_STRING	String - pointer to the string to check
//
//  Output:
//  TRUE - all glyphs are present
//  FALSE - some glyphs are missing
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN MatchString(
    IN FONT_LINK *Font,
    IN CONST EFI_STRING	String
)
{
    CHAR16 *Tst;

    if(String == NULL)
        return TRUE;

    Tst = String;

    while(*Tst != 0) {
        if(!FindGlyph(Font->Glyphs, *Tst, NULL))
            return FALSE;
        Tst++;
    }
    return TRUE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   FindFont
//
//  Description:
//  This function tries to find font in database, that meets the criteria
//
//  Input:
//  IN OUT EFI_FONT_HANDLE *FontHandle - handle in database to start search from
//  IN CHAR16 *FontName - pointer to the font name
//  IN EFI_HII_FONT_STYLE FontStyle - font style
//  IN UINT16 FontSize - font size
//  IN FONT_MATCH_MASK Mask - matching rules
//  IN CONST EFI_STRING	String - pointer to string to verify glyphs presence
//
//  Output:
//  EFI_SUCCESS - font found
//  EFI_NOT_FOUND - font not found
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS FindFont(
    IN OUT EFI_FONT_HANDLE *FontHandle,
    IN CHAR16 *FontName,
    IN EFI_HII_FONT_STYLE FontStyle,
    IN UINT16 FontSize,
    IN FONT_MATCH_MASK Mask,
    IN CONST EFI_STRING	String
)
{
    FONT_LINK *Font;

    if(PrivateData.FontList.Size == 0)
    /* no fonts in database */
        return EFI_NOT_FOUND;

    Font = (FONT_LINK *)PrivateData.FontList.pHead;

/* check if handle passed is not NULL or dummy default font handle */
    if((UINTN)(*FontHandle) != NULL && (UINTN)(*FontHandle) != DEFAULT_FONT_HANDLE) {
        while(Font != NULL) {
            if((VOID *)Font == *FontHandle)
                break;
            Font = (FONT_LINK *)Font->Link.pNext;
        }
        if(Font == NULL) {
        /* end of font list - no matches */
            *FontHandle = NULL;
            return EFI_NOT_FOUND;
        }

        /* match found, it was last returned font, move to the next */
        Font = (FONT_LINK *)Font->Link.pNext;
        if(Font == NULL) {
        /* end of font list, last returned font was last indeed */
            *FontHandle = NULL;
            return EFI_NOT_FOUND;
        }
    }

    while(Font != NULL) {
    /* loop through font list to find the match */   
        if(MatchName(Font, FontName, Mask) &&
           MatchStyle(Font, FontStyle, Mask) &&
           MatchSize(Font, FontSize, Mask) &&
           MatchString(Font, String)) {
        /* match is found */
            *FontHandle = (EFI_FONT_HANDLE)Font;
            return EFI_SUCCESS;
        }
        Font = (FONT_LINK *)Font->Link.pNext;
    }
    *FontHandle = NULL;
    return EFI_NOT_FOUND;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   FillFontInfo
//
//  Description:
//  This function returns EFI_FONT_DISPLAY_INFO data for given font
//
//  Input:
//  IN EFI_FONT_HANDLE FontHandle - font handle to return info about
//  OUT EFI_FONT_DISPLAY_INFO **StringInfoOut - pointer where to store returned info
//
//  Output:
//  EFI_SUCCESS - info returned
//  EFI_OUT_OF_RESOURCES - not enough memory to perform operation
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS FillFontInfo(
    IN EFI_FONT_HANDLE FontHandle,
    OUT EFI_FONT_DISPLAY_INFO **StringInfoOut
)
{
    UINTN NameSize;
    EFI_FONT_DISPLAY_INFO *Ret;
    FONT_LINK *Font;
    UINT8 *Walker;
    EFI_STATUS Status;
    static CHAR16 DefaultFontName[] = L"System font";

    Font = (FONT_LINK *)FontHandle;
    if((UINTN)Font != DEFAULT_FONT_HANDLE) {
        Walker = (UINT8 *)Font->FontPackage;
        Walker += sizeof(EFI_HII_FONT_PACKAGE_HDR);
    } else {
        Walker = (UINT8 *)DefaultFontName;
    }

    NameSize = Wcslen((CHAR16 *)Walker) * sizeof(CHAR16);

/* font display info structure includes font info structure, where one CHAR16 already reserved
   that's why Wcslen used instead fo Wcssize - null-terminator already accounted for */
    Status = pBS->AllocatePool(EfiBootServicesData, sizeof(EFI_FONT_DISPLAY_INFO) + NameSize, &Ret);
    if(!EFI_ERROR(Status)) {
        if((UINTN)Font != DEFAULT_FONT_HANDLE) {
            if(Font->FontPackage->Header.Type == AMI_HII_PACKAGE_FONTS) {
                Ret->FontInfo.FontStyle = EFI_HII_FONT_STYLE_NORMAL;
                Ret->FontInfo.FontSize = ((AMICUSTOM_SIMPLE_FONT_PACKAGE_HDR *)Font->FontPackage)->Height;
            } else {
                Ret->FontInfo.FontStyle = Font->FontPackage->FontStyle;
                Ret->FontInfo.FontSize = Font->FontPackage->Cell.Height;
            }
        } else {
            Ret->FontInfo.FontStyle = EFI_HII_FONT_STYLE_NORMAL;
            Ret->FontInfo.FontSize = EFI_GLYPH_HEIGHT;
        }
        Wcscpy(Ret->FontInfo.FontName, (CHAR16 *)Walker);
        *StringInfoOut = Ret;
    }
    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   IntGetGlyph
//
//  Description:
//  This function returns glyph for given charactef from given font
//
//  Input:
//  IN EFI_FONT_HANDLE FontHandle - font handle of the desired font
//  IN CHAR16 Char - character to return glyph for
//  OUT EFI_HII_GLYPH_INFO *Cell - pointer to store info about glyph dimensions
//  OUT UINT8 **GlyphBlock OPTIONAL - pointer to store glyph
//  OUT BOOLEAN *Free - pointer to return flag was memory allocated for glyph and
//                      should be freed by caller
//
//  Output:
//  EFI_SUCCESS - glyph returned
//  EFI_NOT_FOUND - glyph not found
//  EFI_OUT_OF_RESOURCES - not enough memory to perform operation
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS IntGetGlyph(
    IN EFI_FONT_HANDLE FontHandle, 
    IN CHAR16 Char, 
    OUT EFI_HII_GLYPH_INFO *Cell, 
    OUT UINT8 **GlyphBlock OPTIONAL,
    OUT BOOLEAN *Free
)
{
    EFI_STATUS Status = EFI_SUCCESS;
    EFI_STATUS AllocStatus;
    FONT_LINK *Font;
    GLYPH_LINK *GlyphLink;
    BOOLEAN Found;
    SIMPLE_FONT Glyph;
    UINT8 *WideGlyphBlock;
    UINTN i;

    *Free = FALSE;
    Font = (FONT_LINK *)FontHandle;

    if((UINTN)Font != DEFAULT_FONT_HANDLE) {
        Found = FindGlyph(Font->Glyphs, Char, &GlyphLink);
        if(!Found) {
            Status = EFI_WARN_UNKNOWN_GLYPH;
            Found = FindGlyph(Font->Glyphs, 0xfffd, &GlyphLink);
        }
        if(Found) {
            *Cell = GlyphLink->Cell;
            if(GlyphBlock)
                *GlyphBlock = GlyphLink->GlyphBlock;
            return Status;
        }
        Glyph = DefaultFont[0xfffd];
    } else {
    /* Default font requested */
        Glyph = DefaultFont[(UINTN)Char];
        if(Glyph.NarrowGlyph == NULL && Glyph.WideGlyph == NULL) {
            Glyph = DefaultFont[0xfffd];
            Status = EFI_WARN_UNKNOWN_GLYPH;
        }
    }
/* if we're here we use system font - either because it was requested, or
because supplied font doesn't have requested character or 0xfffd character 
!!!! It is assumed that system font always have 0xfffd character font */
    Cell->Height = EFI_GLYPH_HEIGHT;
    Cell->OffsetX = 0;
    Cell->OffsetY = 0;
    if(Glyph.NarrowGlyph != NULL) {
        Cell->Width = EFI_GLYPH_WIDTH;
        Cell->AdvanceX = ((Glyph.NarrowGlyph)->Attributes & EFI_GLYPH_NON_SPACING) ? 0 : EFI_GLYPH_WIDTH;
        if(GlyphBlock)
            *GlyphBlock = (Glyph.NarrowGlyph)->GlyphCol1;
    } else if(Glyph.WideGlyph != NULL) {
        Cell->Width = EFI_GLYPH_WIDE_WIDTH;
        Cell->AdvanceX = ((Glyph.WideGlyph)->Attributes & EFI_GLYPH_NON_SPACING) ? 0 : EFI_GLYPH_WIDE_WIDTH;
        if(GlyphBlock) {
            AllocStatus = pBS->AllocatePool(EfiBootServicesData, sizeof(UINT8) * 2 * EFI_GLYPH_HEIGHT, &WideGlyphBlock);
            if(EFI_ERROR(AllocStatus))
                return AllocStatus;
            for(i = 0; i < EFI_GLYPH_HEIGHT; i++)  {
                WideGlyphBlock[2 * i] = (Glyph.WideGlyph)->GlyphCol1[i];
                WideGlyphBlock[2 * i + 1] = (Glyph.WideGlyph)->GlyphCol2[i];
            }
            *GlyphBlock = WideGlyphBlock;
            *Free = TRUE;
        }
    } else {
        Cell->AdvanceX = 0;
        return EFI_NOT_FOUND;
    }
    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   UpdateLineSize
//
//  Description:
//  This function updates dimensions in pixels of given line based on glyphs of current font
//
//  Input:
//  IN OUT DRAW_LINE *Line - pointer to the line structure
//
//  Output:
//  None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID UpdateLineSize(
    IN OUT DRAW_LINE *Line
)
{
    EFI_STATUS Status;
    UINTN Width = 0;
    UINTN i;
    EFI_HII_GLYPH_INFO Cell;
    BOOLEAN Dummy;

	for(i = Line->StartIndex; i <= Line->EndIndex; i++) {
        if((DrawFlags & EFI_HII_IGNORE_LINE_BREAK) && IsLineBreak(DrawString[i]))
            continue;

        Status = IntGetGlyph(CurFont, DrawString[i], &Cell, NULL, &Dummy);
        if(Status == EFI_WARN_UNKNOWN_GLYPH && (DrawFlags & EFI_HII_IGNORE_IF_NO_GLYPH))
            continue;

        Width = (Cell.AdvanceX < 0) ? Width : Width + (UINT16)Cell.AdvanceX;
    }
    Line->LineWidth = Width;
    Line->LineHeight = ((UINTN)CurFont == DEFAULT_FONT_HANDLE) ? Cell.Height : ((FONT_LINK *)CurFont)->FontHeight;
    Line->BaseLineOffset = ((UINTN)CurFont == DEFAULT_FONT_HANDLE) ? Cell.Height : ((FONT_LINK *)CurFont)->FontBaseLine;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   ClipLine
//
//  Description:
//  This function updates dimensions in pixels of given line to fit given width
//
//  Input:
//  IN OUT DRAW_LINE *Line - pointer to the line structure
//  IN UINTN Width - width to fit
//  IN BOOLEAN ClipClean - clipping mode
//
//  Output:
//  None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID ClipLine(
    IN OUT DRAW_LINE *Line,
    IN UINTN Width,
    IN BOOLEAN ClipClean
)
{
    UINTN Excess;
    UINTN i;
    EFI_HII_GLYPH_INFO Cell;
    BOOLEAN Dummy;

    Excess = Line->LineWidth - Width;

    for(i = Line->EndIndex; i >= Line->StartIndex; i--) {
        IntGetGlyph(CurFont, DrawString[i], &Cell, NULL, &Dummy);
        if ((INTN)Excess <= Cell.AdvanceX)
            break;
        Excess -= Cell.AdvanceX;
        Line->LineWidth -= Cell.AdvanceX;
    }

    if(Excess == Cell.AdvanceX || ClipClean) {
    /* remove excess character */
        i--;
        Line->LineWidth -= Cell.AdvanceX;
        IntGetGlyph(CurFont, DrawString[i], &Cell, NULL, &Dummy);
        if(Cell.AdvanceX == 0)
        /* the previous character is non-spacing -remove it also */
            i--;
    } else {
    /* perform partial clipping */
        Line->LineWidth -= Excess;
    }
    Line->EndIndex = i;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   WrapLine
//
//  Description:
//  This function updates dimensions in pixels of given line to fit given width
//  and creates additional line if necessary
//
//  Input:
//  IN OUT DRAW_LINE *Line - pointer to the line structure
//  IN UINTN Width - width to fit
//
//  Output:
//  None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS WrapLine(
    IN OUT DRAW_LINE *Line,
    IN UINTN Width
)
{
    UINTN Excess;
    UINTN i;
    UINTN NewEnd;
    UINTN NewStart;
    DRAW_LINE *NewLine;
    EFI_HII_GLYPH_INFO Cell;
    BOOLEAN Dummy;
    UINTN Save;

    Excess = Line->LineWidth - Width;

    for(i = Line->EndIndex; (i >= Line->StartIndex && i != 0); i--) {
        IntGetGlyph(CurFont, DrawString[i], &Cell, NULL, &Dummy);
        if ((INTN)Excess <= Cell.AdvanceX)
            break;
        Excess -= Cell.AdvanceX;
    }
    if(i == 0 || i == Line->StartIndex) {
        Line->EndIndex = i;
        Line->LineWidth = 0;
        return EFI_SUCCESS;
    } else {
        Save = i;   //save index of first excess character
    }               //we will you it if no break opp arises for clip_clean operation

/* we skipped excessed characters - start search for line break opp */
    for(; (i >= Line->StartIndex && i != 0); i--) {
        if(IsLineBreakOpp(DrawString[i])) {
        /* we found line break opportunity */
            NewEnd = Line->EndIndex;
            NewStart = i + 1;
            Line->EndIndex = i;
            UpdateLineSize(Line);
            if(Line->LineWidth > Width)
            /* case when line-break opp character is partially visible - skip it */
                Line->EndIndex--;
        /* add a new line */
            NewLine = (DRAW_LINE *)CreateNewLink(sizeof(UINTN) * 5);
			if(NewLine == NULL)
				return EFI_OUT_OF_RESOURCES;
            NewLine->StartIndex = NewStart;
            NewLine->EndIndex = NewEnd;
            UpdateLineSize(NewLine);
            DListInsert(&DrawLines, (DLINK *)NewLine, (DLINK *)Line);
            return EFI_SUCCESS;
        }
    }
/* if we're here, no line break opp present, use clip clean */
    Line->EndIndex = Save - 1;
    UpdateLineSize(Line);
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   GetDrawImageSize
//
//  Description:
//  This function returns size of image necessary to fit processing string
//  including all wraps and clips
//
//  Input:
//  OUT UINTN *Width - pointer to store required width
//  OUT UINTN *Height - pointer to store required height
//
//  Output:
//  None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID GetDrawImageSize(
    OUT UINTN *Width,
    OUT UINTN *Height
)
{
	DRAW_LINE *Link;
	UINTN MaxWidth = 0;
	UINTN MaxHeight = 0;

	Link = (DRAW_LINE *)(DrawLines.pHead);
	while(Link != NULL)
	{
		MaxWidth = (MaxWidth < Link->LineWidth) ? Link->LineWidth : MaxWidth;
		MaxHeight += Link->LineHeight;
		Link = (DRAW_LINE *)Link->Link.pNext;
	}
    *Width = MaxWidth;
    *Height = MaxHeight;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   PixelSet
//
//  Description:
//  This function checks whether pixel with given coordinates is set in given glyph
//
//  Input:
//  IN UINTN PosX - X coordinate of pixel
//  IN UINTN PosY - Y coordinate of pixel
//  IN UINT8 *GlyphBlock - pointer to glyph array
//  IN UINT16 CharWidth - width of character described by glyph
//
//  Output:
//  TRUE - pixel is set
//  FALSE - pixel is not set
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN PixelSet(
    IN UINTN PosX,
    IN UINTN PosY,
    IN UINT8 *GlyphBlock,
    IN UINT16 CharWidth
)
{
    UINTN Step;
    UINTN Index;
    UINT8 Bit;

    Step = (CharWidth + 7) / 8;
    Index = (PosY * Step) + (PosX / 8);

    Bit = (0x80 >> (PosX % 8));

    return (Bit & GlyphBlock[Index]);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   DrawGlyph
//
//  Description:
//  This function draws given glyph on given bitmap
//
//  Input:
//  IN UINTN StartX - start X coordinate of glyph
//  IN UINTN StartY - start Y coordinate of glyph
//  IN UINTN SizeX - width of glyph
//  IN UINTN SizeY - height of glyph
//  IN UINT8 *GlyphBlock - pointer to glyph array
//  IN BOOLEAN Transparent - flag if image should be transparent
//  IN EFI_GRAPHICS_OUTPUT_BLT_PIXEL *Blt - bitmap to draw on
//  IN UINT16 CharWidth - width of character described by glyph
//
//  Output:
//  None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID DrawGlyph(
    IN UINTN StartX,
    IN UINTN StartY,
    IN UINTN SizeX,
    IN UINTN SizeY,
    IN UINT8 *GlyphBlock,
    IN BOOLEAN Transparent,
    IN EFI_GRAPHICS_OUTPUT_BLT_PIXEL *Blt,
    IN UINT16 CharWidth
)
{
    UINTN i;
    UINTN j;
    UINTN Index;
    UINTN Base;

    Base = StartX + StartY * ImageWidth;
    for(i = 0; i < SizeY; i++ ) {
        for(j = 0; j < SizeX; j++) {
            Index = Base + i * ImageWidth + j;
            if(PixelSet(j, i, GlyphBlock, CharWidth)) {
                Blt[Index] = DefForegroundColor;
            } else if (!Transparent) {
                Blt[Index] = DefBackgroundColor;
            }
        }
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   CheckVisible
//
//  Description:
//  This function checks whether glyph is withing given image rectangle,
//  and clips glyph rectangle if necessary
//
//  Input:
//  IN OUT RECT_COORD *Glyph - pointer to glyph rectangle
//  IN RECT_COORD *Image - pointer to image rectangle
//
//  Output:
//  TRUE - glyph is visible (at least partially)
//  FALSE - glyph is out of image boundaries
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN CheckVisible(
    IN OUT RECT_COORD *Glyph, 
    IN RECT_COORD *Image
)
{
    UINTN delta_x;
    UINTN delta_y;

/*  check whether glyph within given image rectangle */
    if(Glyph->st->x >= (Image->st->x + Image->size->x) || 
       Glyph->st->y >= (Image->st->y + Image->size->y))
        return FALSE;

/* clip glyph size if necessary */
    delta_x = (Image->st->x < Glyph->st->x) ? Glyph->st->x - Image->st->x : 0;
    delta_y = (Image->st->y < Glyph->st->y) ? Glyph->st->y - Image->st->y : 0;

    if(Glyph->size->x > (Image->size->x - delta_x))
        Glyph->size->x = Image->size->x - delta_x;

    if(Glyph->size->y > (Image->size->y - delta_y))
        Glyph->size->y = Image->size->y - delta_y;
    return TRUE;
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
