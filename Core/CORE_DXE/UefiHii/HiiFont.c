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
// $Header: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Core/CORE_DXE/UefiHii/HiiFont.c 3     3/18/13 8:31a Thomaschen $
//
// $Revision: 3 $
//
// $Date: 3/18/13 8:31a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Core/CORE_DXE/UefiHii/HiiFont.c $
// 
// 3     3/18/13 8:31a Thomaschen
// Update to rev.16.
// 
// 16    3/11/13 4:40p Artems
// [TAG]  		EIP110240
// [Category]  	Improvement
// [Description]  	Raise the TPL of StringToImage function to TPL_NOTIFY
// to protect internal global data
// [Files]  		HiiFont.c
// 
// 15    1/24/13 11:12a Artems
// [TAG]  		EIP112874
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	System displays output in wrong colors
// [RootCause]  	If system failed to find font, described in passed font
// info structure it also ignored passed colors
// [Solution]  	Preserve passed colors even if font not found
// [Files]  		HiiFont.c
// 
// 14    12/26/12 1:40p Artems
// [TAG]  		EIP109050
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	Memory leal in call to GetGlyph function
// [RootCause]  	GetGlyph function called GetFontInfo function to obtain
// proper font and didn't release font info buffer
// [Solution]  	Fixed GetGlyph function
// [Files]  		HiiFont.c
// 
// 13    11/14/12 5:58p Artems
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
// 12    9/25/12 5:46p Artems
// [TAG]  		EIP101224
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	System freezes
// [RootCause]  	Memory leak in StringToImage function. When called many
// times may lead to memory exhaustion
// [Solution]  	Fixed memory leak
// [Files]  		HiiFont.c
// 
// 11    6/27/12 4:16p Artems
// [TAG]  		EIP93526
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	Aptio 4 - Proportional Font EFI_HII_OUT_FLAG_WRAP issue
// [RootCause]  	Passed drawing flags contained both Clip and Wrap. Clip
// gets analyzed first so clipping control flow was enacted
// [Solution]  	Changed order of drawind flags analysis
// [Files]  		HiiFont.c
// 
// 10    6/15/12 12:19p Artems
// [TAG]  		EIP N/A
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	project doesn't build in 32-bit mode
// [RootCause]  	Signed/Unsigned mismatch reported by 32-bit compiler
// [Solution]  	typecasted one parameter to signed
// [Files]  		HiiFont.c HiiFontEx.c
// 
// 9     6/14/12 6:31p Artems
// [TAG]  		EIP83593
// [Category]  	New Feature
// [Description]  	Proportional font support for Aptio fixed SCT reported
// bugs
// [Files]  		HiiFont.c HiiFontEx.c
// 
// 8     5/24/12 2:58p Artems
// [TAG]  		EIP83593
// [Category]  	Bug Fix
// [Severity]  	Critical
// [Symptom]  	No symbols are shown in GSE
// [RootCause]  	Incorrect BaseLineOffset was set. Transparent drawing was
// not supported
// [Solution]  	Set correct BaseLineOffset. Add check for transparency
// flag
// [Files]  		HiiFont.c
// 
// 7     5/22/12 4:14p Artems
// [TAG]  		EIP83593
// [Category]  	New Feature
// [Description]  	Proportional font support for Aptio. Removed unused
// functions
// [Files]  		HiiFont.c
// 
// 6     5/21/12 6:28p Artems
// [TAG]  		EIP83593
// [Category]  	New Feature
// [Description]  	Proportional font support for Aptio
// [Files]  		HiiDatabase.c HiiFont.c HiiFontEx.c HiiPrivate.h HiiString.c
// 
// 5     10/25/11 7:04p Artems
// EIP 70530: Fixed bugs reported by SCT 2.3.1
// 
// 4     5/17/11 4:05p Artems
// EIP 59787: Bug fix - when drawing multi-line string X position wasn't
// updated to start of new line
// 
// 3     5/13/11 6:14p Artems
// Renamed functions HiiGetString and HiiSetString to AmiHiiGetString and
// AmiHiiSetString 
// to avoid collusion with EdkII native library functions
// 
// 2     12/03/09 6:04p Artems
// SCT bug fix
// 
// 1     10/09/09 6:12p Felixp
// 
// 1     2/27/09 3:55p Artems
// Initial check-in
// 
// 1     3/18/07 5:23p Felixp
// 
//**********************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:	HiiFont.c
//
// Description:	Hii font protocol functions implementation
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include <AmiDxeLib.h>
#include "HiiPrivate.h"

const EFI_GRAPHICS_OUTPUT_BLT_PIXEL Black = { 0, 0, 0, 0 };
const EFI_GRAPHICS_OUTPUT_BLT_PIXEL White = { 0xff, 0xff, 0xff, 0 };

extern HII_DATABASE_PRIVATE_DATA PrivateData;
extern SIMPLE_FONT DefaultFont[0x10000];

EFI_GRAPHICS_OUTPUT_BLT_PIXEL DefForegroundColor;
EFI_GRAPHICS_OUTPUT_BLT_PIXEL DefBackgroundColor;

static UINTN TextStartX;
static UINTN TextStartY;
static EFI_GRAPHICS_OUTPUT_BLT_PIXEL *ImageBlt;     //buffer, where to draw

EFI_FONT_HANDLE CurFont;                            //font to use
CHAR16 *DrawString;                                 //string to draw
EFI_HII_OUT_FLAGS DrawFlags = 0;
DLIST DrawLines = {0, NULL, NULL};
UINTN ImageWidth;
UINTN ImageHeight;

#pragma optimize( "", off )
EFI_STATUS CheckParameters(VOID *One, VOID *Two)
{
    return (One == NULL || Two == NULL) ? EFI_INVALID_PARAMETER : EFI_SUCCESS;
}
#pragma optimize( "", on )

//**************************** Protocol functions implementation ***************************

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   HiiStringToImage
//
//  Description:
//  This function is HII Font protocol function StringToImage implementation 
//
//  Input:
// 	IN EFI_HII_FONT_PROTOCOL *This - Pointer to EFI_HII_FONT_PROTOCOL structure
// 	IN EFI_HII_OUT_FLAGS Flags - Drawing flags
//  IN EFI_STRING String - String to draw
//  IN EFI_FONT_DISPLAY_INFO *StringInfo - Pointer to display info
//  IN OUT EFI_IMAGE_OUTPUT **Blt - Pointer to output buffer
//  IN UINTN BltX - start horizontal position
//  IN UINTN BltY - start vertical position
//  OUT EFI_HII_ROW_INFO **RowInfoArray - Pointer to returned row info array
//  OUT UINTN *RowInfoArraySize - Pointer to store row info array size
//  OUT UINTN *ColumnInfoArray - Pointer to returned column info array
//
//  Output:
//  EFI_SUCCESS - Function executed successfully
//  EFI_OUT_OF_RESOURCES - Not enough memory to perform operation
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS HiiStringToImage(
	IN CONST EFI_HII_FONT_PROTOCOL	*This,
	IN EFI_HII_OUT_FLAGS			Flags,
	IN CONST EFI_STRING				String,
	IN CONST EFI_FONT_DISPLAY_INFO	*StringInfo OPTIONAL,
	IN OUT EFI_IMAGE_OUTPUT			**Blt,
	IN UINTN						BltX,
	IN UINTN						BltY,
	OUT EFI_HII_ROW_INFO			**RowInfoArray OPTIONAL,
	OUT UINTN						*RowInfoArraySize OPTIONAL,
	OUT UINTN						*ColumnInfoArray OPTIONAL)
{
	EFI_STATUS Status;
	EFI_GRAPHICS_OUTPUT_BLT_PIXEL *NewBlt = NULL;
	EFI_IMAGE_OUTPUT *Io = *Blt;
	EFI_HII_ROW_INFO *RowInfo;
	UINTN i, j;
	UINTN Offset;
	DRAW_LINE *Link;
    UINTN Delta = 0;
    EFI_FONT_DISPLAY_INFO *Info = NULL;
	EFI_TPL OldTpl;

    Status = CheckParameters(String, Blt);
    if(EFI_ERROR(Status))
        return Status;

    if (Io == NULL) {
    //
    // These two flag cannot be used if Blt is NULL upon entry.
    //
        if ((Flags & EFI_HII_OUT_FLAG_TRANSPARENT) == EFI_HII_OUT_FLAG_TRANSPARENT)
            return EFI_INVALID_PARAMETER;

        if ((Flags & EFI_HII_OUT_FLAG_CLIP) == EFI_HII_OUT_FLAG_CLIP)
            return EFI_INVALID_PARAMETER;
    }
  //
  // These two flags require that EFI_HII_OUT_FLAG_CLIP be also set.
  //
    if ((Flags & (EFI_HII_OUT_FLAG_CLIP | EFI_HII_OUT_FLAG_CLIP_CLEAN_X)) ==  EFI_HII_OUT_FLAG_CLIP_CLEAN_X)
        return EFI_INVALID_PARAMETER;

    if ((Flags & (EFI_HII_OUT_FLAG_CLIP | EFI_HII_OUT_FLAG_CLIP_CLEAN_Y)) ==  EFI_HII_OUT_FLAG_CLIP_CLEAN_Y)
        return EFI_INVALID_PARAMETER;
  //
  // This flag cannot be used with EFI_HII_OUT_FLAG_CLIP_CLEAN_X.
  //
    if ((Flags & (EFI_HII_OUT_FLAG_WRAP | EFI_HII_OUT_FLAG_CLIP_CLEAN_X)) ==  (EFI_HII_OUT_FLAG_WRAP | EFI_HII_OUT_FLAG_CLIP_CLEAN_X))
        return EFI_INVALID_PARAMETER;

//check string size - if two bytes - means empty string - do nothing
    i = StrSize16(String);

    if(i <= 2)
        return EFI_SUCCESS;

    OldTpl = pBS->RaiseTPL(TPL_NOTIFY);

//first initialize global variables and split string
/* SCT assumes that EFI_HII_OUT_FLAG_CLIP flag is implied when direct to screen output is performed 
   unless EFI_HII_OUT_FLAG_WRAP flag is set */
	DrawFlags = Flags;
    if(Flags & EFI_HII_IGNORE_LINE_BREAK || 
       (Flags & EFI_HII_DIRECT_TO_SCREEN && !(Flags & EFI_HII_OUT_FLAG_WRAP)))
        DrawFlags |= EFI_HII_OUT_FLAG_CLIP;

	DrawString = String;
	TextStartX = BltX;
	TextStartY = BltY;
    CurFont = NULL;
    Status = HiiGetFontInfo(This, &CurFont, StringInfo, &Info, NULL);
    if(EFI_ERROR(Status)) {
        CurFont = (EFI_FONT_HANDLE)(UINTN)DEFAULT_FONT_HANDLE;
        Info = NULL;
    }

    if (Info != NULL) {
        DefForegroundColor = Info->ForegroundColor;
        DefBackgroundColor = Info->BackgroundColor;
        pBS->FreePool(Info);        //it's no longer needed
    } else {
        if(StringInfo != NULL) {    //even though correct font not found we preserve passed colors if any
            DefForegroundColor = StringInfo->ForegroundColor;
            DefBackgroundColor = StringInfo->BackgroundColor;
        } else {
            DefForegroundColor = White;
            DefBackgroundColor = Black;
        }
    }    

	Status = SplitByLineBreaks(DrawString);
	if(EFI_ERROR(Status)) {
        pBS->RestoreTPL(OldTpl);
		return EFI_OUT_OF_RESOURCES;
    }

	if(Io != NULL) {
		if(!(Flags & EFI_HII_DIRECT_TO_SCREEN)) {
            //if we're drawing on given bitmap - take its size
            ImageWidth = Io->Width;
            ImageHeight = Io->Height;
			NewBlt = Io->Image.Bitmap;
        } else {
             //make sure we fit in screen resolution
		    ImageWidth = Io->Width - BltX;
		    ImageHeight = Io->Height - BltY;

            //clear TextStartX and TextStartY
            TextStartX = 0;
            TextStartY = 0;
        }
    /* since bitmap size is fixed we have to adjust text to fit in */
        Status = AdjustLineSize();
        if(EFI_ERROR(Status)) {
            pBS->RestoreTPL(OldTpl);
		    return EFI_OUT_OF_RESOURCES;
        }
	} else {
        //calculate size of the image
        GetDrawImageSize(&ImageWidth, &ImageHeight);
		//add to required image size initial offset
		ImageWidth += BltX;
		ImageHeight += BltY;
	}

	if(NewBlt == NULL) {
    /* buffer not initialized because of DirectToScreen flag or Io == NULL */
		Status = pBS->AllocatePool(
		                    EfiBootServicesData, 
							sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL) * ImageWidth * ImageHeight, 
							&NewBlt);
		if (EFI_ERROR(Status)) {
            pBS->RestoreTPL(OldTpl);
			return EFI_OUT_OF_RESOURCES;
        }
        MemSet(NewBlt, sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL) * ImageWidth * ImageHeight, 0);
	}

	ImageBlt = NewBlt;
    Draw();

    if(Flags & EFI_HII_DIRECT_TO_SCREEN)
    {
        EFI_GRAPHICS_OUTPUT_PROTOCOL *Screen;

        if(ImageWidth < Io->Width)      //we need to draw a subrectange, calculate Delta
            Delta = ImageWidth * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL);

        Screen = (EFI_GRAPHICS_OUTPUT_PROTOCOL *)(Io->Image.Screen);
        Status = Screen->Blt(Screen, ImageBlt, EfiBltBufferToVideo, 
                             0, 0, BltX, BltY, ImageWidth, ImageHeight, Delta);
        pBS->FreePool(ImageBlt);
    }

//Prepare return info if needed
    Link = (DRAW_LINE *)(DrawLines.pHead);
	if(RowInfoArray != NULL && Link->LineHeight != 0) {
        Status = pBS->AllocatePool(
		                    EfiBootServicesData, 
							sizeof(EFI_HII_ROW_INFO) * DrawLines.Size, 
							&RowInfo);
		if (EFI_ERROR(Status)) {
            pBS->RestoreTPL(OldTpl);
			return EFI_OUT_OF_RESOURCES;
        }

		i = 0;
		while(Link != NULL) {
			RowInfo[i].BaselineOffset = 0;      //I'm still confused with this one, but SCT is happy
			RowInfo[i].EndIndex = Link->EndIndex;
			RowInfo[i].LineHeight = Link->LineHeight;
			RowInfo[i].LineWidth = Link->LineWidth;
			RowInfo[i].StartIndex = Link->StartIndex;

			i++;
			Link = (DRAW_LINE *)Link->Link.pNext;
		}
		*RowInfoArray = RowInfo;
        if(RowInfoArraySize != NULL)
		    *RowInfoArraySize = DrawLines.Size;
	} else {
        if(RowInfoArray != NULL)
            *RowInfoArray = NULL;
        if(RowInfoArraySize != NULL)
		    *RowInfoArraySize = 0;
    }	

	if(Io == NULL) {
		Status = pBS->AllocatePool(EfiBootServicesData, sizeof(EFI_IMAGE_OUTPUT), &Io);
		if (EFI_ERROR(Status)) {
            pBS->RestoreTPL(OldTpl);
			return EFI_OUT_OF_RESOURCES;
        }

		Io->Height = (UINT16)ImageHeight;
		Io->Width = (UINT16)ImageWidth;
		Io->Image.Bitmap = NewBlt;

		*Blt = Io;
	}

	if(ColumnInfoArray != NULL) {
		i = 0;
		Link = (DRAW_LINE *)(DrawLines.pHead);
		while(Link != NULL)
		{
			Offset = TextStartX;
			for(j = Link->StartIndex; j <= Link->EndIndex; j++)
			{
                BOOLEAN Dummy;
                EFI_HII_GLYPH_INFO Cell;
				ColumnInfoArray[i] = Offset;
                IntGetGlyph(CurFont, DrawString[j], &Cell, NULL, &Dummy);
				i++;
				Offset += Cell.AdvanceX;
			}
			Link = (DRAW_LINE *)Link->Link.pNext;
		}
	}

//clean up
	DeleteList(&DrawLines);
    pBS->RestoreTPL(OldTpl);
	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   HiiStringIdToImage
//
//  Description:
//  This function is HII Font protocol function StringIdToImage implementation 
//
//  Input:
// 	IN EFI_HII_FONT_PROTOCOL *This - Pointer to EFI_HII_FONT_PROTOCOL structure
// 	IN EFI_HII_OUT_FLAGS Flags - Drawing flags
//  IN EFI_HII_HANDLE PackageList - Handle of package list where string resides
//  IN EFI_STRING_ID StringId - String Id
//  IN CHAR8 *Language - Language Id
//  IN EFI_FONT_DISPLAY_INFO *StringInfo - Pointer to display info
//  IN OUT EFI_IMAGE_OUTPUT **Blt - Pointer to output buffer
//  IN UINTN BltX - start horizontal position
//  IN UINTN BltY - start vertical position
//  OUT EFI_HII_ROW_INFO **RowInfoArray - Pointer to returned row info array
//  OUT UINTN *RowInfoArraySize - Pointer to store row info array size
//  OUT UINTN *ColumnInfoArray - Pointer to returned column info array
//
//  Output:
//  EFI_SUCCESS - Function executed successfully
//  EFI_OUT_OF_RESOURCES - Not enough memory to perform operation
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS HiiStringIdToImage (
	IN CONST EFI_HII_FONT_PROTOCOL	*This,
	IN EFI_HII_OUT_FLAGS			Flags,
	IN EFI_HII_HANDLE				PackageList,
	IN EFI_STRING_ID				StringId,
	IN CONST CHAR8*					Language,
	IN CONST EFI_FONT_DISPLAY_INFO	*StringInfo OPTIONAL,
	IN OUT EFI_IMAGE_OUTPUT			**Blt,
	IN UINTN						BltX,
	IN UINTN						BltY,
	OUT EFI_HII_ROW_INFO			**RowInfoArray OPTIONAL,
	OUT UINTN						*RowInfoArraySize OPTIONAL,
	OUT UINTN						*ColumnInfoArray OPTIONAL)
{
	CHAR16 String[0x100];
	UINTN StringSize = 0x100;
	EFI_STATUS Status;

	Status = AmiHiiGetString(NULL, Language, PackageList, StringId, String, &StringSize, NULL);

	if(EFI_ERROR(Status))
	{
		if(Status == EFI_BUFFER_TOO_SMALL)
		{
			Status = pBS->AllocatePool(
		                    EfiBootServicesData, 
							sizeof(CHAR16) * StringSize, 
							(VOID **)&String);
			if (EFI_ERROR(Status))
				return EFI_OUT_OF_RESOURCES;
		}
		else
			return Status;

		Status = AmiHiiGetString(NULL, Language, PackageList, StringId, String, &StringSize, NULL);
	}

	Status = HiiStringToImage(This, Flags, String, StringInfo, Blt, BltX, BltY, 
							  RowInfoArray, RowInfoArraySize, ColumnInfoArray);

	if(StringSize > 0x100)
		pBS->FreePool(String);

	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   HiiGetGlyph
//
//  Description:
//  This function is HII Font protocol function GetGlyph implementation 
//
//  Input:
// 	IN EFI_HII_FONT_PROTOCOL *This - Pointer to EFI_HII_FONT_PROTOCOL structure
//  IN CHAR16 Char - Symbol, which glyph to return
//  IN EFI_FONT_DISPLAY_INFO *StringInfo - Pointer to display info
//  IN OUT EFI_IMAGE_OUTPUT **Blt - Pointer to output buffer
//  OUT UINTN *Baseline - Pointer to baseline placeholder
//
//  Output:
//  EFI_SUCCESS - Function executed successfully
//  EFI_OUT_OF_RESOURCES - Not enough memory to perform operation
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS HiiGetGlyph (
	IN CONST EFI_HII_FONT_PROTOCOL	*This,
	IN CHAR16						Char,
	IN CONST EFI_FONT_DISPLAY_INFO	*StringInfo,
	OUT EFI_IMAGE_OUTPUT			**Blt,
	OUT UINTN						*Baseline OPTIONAL
)
{
    EFI_STATUS Status;
    BOOLEAN GlyphNotFound = FALSE;
    EFI_IMAGE_OUTPUT *Output;
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL *Bitmap;
    EFI_FONT_HANDLE Font;
    EFI_FONT_DISPLAY_INFO *Info = NULL;
    EFI_HII_GLYPH_INFO Cell;
    UINT8 *GlyphBlock;
    BOOLEAN Free;

    if(Blt == NULL || *Blt != NULL)
        return EFI_INVALID_PARAMETER;

    Font = NULL;
    Status = HiiGetFontInfo(This, &Font, StringInfo, &Info, NULL);
    if(EFI_ERROR(Status)) {
        Font = (EFI_FONT_HANDLE)(UINTN)DEFAULT_FONT_HANDLE;
        Info = NULL;
    }

//prepare global data values, used in drawing
    if(Info != NULL) {
        DefForegroundColor = Info->ForegroundColor;
        DefBackgroundColor = Info->BackgroundColor;
        pBS->FreePool(Info);
    } else {
        if(StringInfo != NULL) {
            DefForegroundColor = StringInfo->ForegroundColor;
            DefBackgroundColor = StringInfo->BackgroundColor;
        } else {
            DefForegroundColor = White;
            DefBackgroundColor = Black;
        }
    }    

    Status = IntGetGlyph(Font, Char, &Cell, &GlyphBlock, &Free);
    if(EFI_ERROR(Status))
        return Status;
    if(Status == EFI_WARN_UNKNOWN_GLYPH)
        GlyphNotFound = TRUE;

//allocate memory for output bitmap
    Status = pBS->AllocatePool(EfiBootServicesData, 
							   sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL) * Cell.Width * Cell.Height, 
							   &Bitmap);
	if (EFI_ERROR(Status))
		return EFI_OUT_OF_RESOURCES;

//allocate memory for output data
    Status = pBS->AllocatePool(EfiBootServicesData, 
							   sizeof(EFI_IMAGE_OUTPUT), 
							   &Output);
	if (EFI_ERROR(Status)) {
        pBS->FreePool(Bitmap);
		return EFI_OUT_OF_RESOURCES;
    }

    Output->Width = Cell.Width;
    Output->Height = Cell.Height;
    Output->Image.Bitmap = Bitmap;

    ImageWidth = Output->Width;
    ImageHeight = Output->Height;

//now we are ready to draw the glyph
    DrawGlyph(0, 0, ImageWidth, ImageHeight, GlyphBlock, FALSE, Bitmap, Cell.Width);
    if(Free)
        pBS->FreePool(GlyphBlock);

    *Blt = Output;

    if(Baseline != NULL) {
        if((UINTN)Font == DEFAULT_FONT_HANDLE)
            *Baseline = (Cell.Width == EFI_GLYPH_WIDTH) ? 4 : 5;     //fixed value for system font
        else
            *Baseline = (Cell.OffsetY < 0) ? -(Cell.OffsetY) : 0;
    }

    return (GlyphNotFound) ? EFI_WARN_UNKNOWN_GLYPH : EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   HiiGetFontInfo
//
//  Description:
//  This function is HII Font protocol function GetFontInfo implementation 
//
//  Input:
// 	IN EFI_HII_FONT_PROTOCOL *This - Pointer to EFI_HII_FONT_PROTOCOL structure
//  IN OUT EFI_FONT_HANDLE *FontHandle - Pointer to font handle
//  IN EFI_FONT_DISPLAY_INFO *StringInfoIn - Pointer to display info
//  OUT EFI_FONT_DISPLAY_INFO *StringInfoOut - Pointer to output display info
//  IN EFI_STRING *String - Pointer to string to test
//
//  Output:
//  EFI_SUCCESS - Function executed successfully
//  EFI_OUT_OF_RESOURCES - Not enough memory to perform operation
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS HiiGetFontInfo (
	IN CONST EFI_HII_FONT_PROTOCOL	*This,
	IN OUT EFI_FONT_HANDLE			*FontHandle,
	IN CONST EFI_FONT_DISPLAY_INFO	*StringInfoIn,
	OUT EFI_FONT_DISPLAY_INFO		**StringInfoOut,
	IN CONST EFI_STRING				String OPTIONAL
)
{
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL Fg;
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL Bg;
    EFI_HII_FONT_STYLE            FStyle;
    UINT16                        FSize;
    CHAR16                        *FName;
    FONT_MATCH_MASK               Fm;
    EFI_STATUS                    Status;
    EFI_FONT_DISPLAY_INFO         FdInfo;

    if (StringInfoIn == NULL) {
    /* use default values */
        FdInfo.FontInfoMask = EFI_FONT_INFO_SYS_FONT | 
                              EFI_FONT_INFO_SYS_SIZE |
                              EFI_FONT_INFO_SYS_STYLE |
                              EFI_FONT_INFO_SYS_FORE_COLOR |
                              EFI_FONT_INFO_SYS_BACK_COLOR;
    } else {
        FdInfo = *StringInfoIn;
        FName = (CHAR16 *)StringInfoIn->FontInfo.FontName;
    }
  //
  // Check the font information mask to make sure it is valid.
  //
    if (((FdInfo.FontInfoMask & (EFI_FONT_INFO_SYS_FONT  | EFI_FONT_INFO_ANY_FONT))  == 
        (EFI_FONT_INFO_SYS_FONT | EFI_FONT_INFO_ANY_FONT))   ||
        ((FdInfo.FontInfoMask & (EFI_FONT_INFO_SYS_SIZE  | EFI_FONT_INFO_ANY_SIZE))  == 
        (EFI_FONT_INFO_SYS_SIZE | EFI_FONT_INFO_ANY_SIZE))   ||
        ((FdInfo.FontInfoMask & (EFI_FONT_INFO_SYS_STYLE | EFI_FONT_INFO_ANY_STYLE)) == 
        (EFI_FONT_INFO_SYS_STYLE | EFI_FONT_INFO_ANY_STYLE)) ||
        ((FdInfo.FontInfoMask & (EFI_FONT_INFO_RESIZE    | EFI_FONT_INFO_ANY_SIZE))  == 
        (EFI_FONT_INFO_RESIZE | EFI_FONT_INFO_ANY_SIZE))     ||           
        ((FdInfo.FontInfoMask & (EFI_FONT_INFO_RESTYLE   | EFI_FONT_INFO_ANY_STYLE)) == 
        (EFI_FONT_INFO_RESTYLE | EFI_FONT_INFO_ANY_STYLE)))
        return EFI_INVALID_PARAMETER;

/* first deal with color attributes */
    Fg = (FdInfo.FontInfoMask & EFI_FONT_INFO_SYS_FORE_COLOR) ? White : StringInfoIn->ForegroundColor;
    Bg = (FdInfo.FontInfoMask & EFI_FONT_INFO_SYS_BACK_COLOR) ? Black : StringInfoIn->BackgroundColor;

/* retrieve supplied information */
    FStyle = (FdInfo.FontInfoMask & EFI_FONT_INFO_SYS_STYLE) ? EFI_HII_FONT_STYLE_NORMAL : StringInfoIn->FontInfo.FontStyle;
    FSize = (FdInfo.FontInfoMask & EFI_FONT_INFO_SYS_SIZE) ? EFI_GLYPH_HEIGHT : StringInfoIn->FontInfo.FontSize;

    if(FdInfo.FontInfoMask & EFI_FONT_INFO_SYS_FONT) {
        if(*FontHandle == (EFI_FONT_HANDLE)(UINTN)DEFAULT_FONT_HANDLE) {
        /* we already returned system font, so no other matches for system font present */
            *FontHandle = NULL;
            return EFI_NOT_FOUND;
        }
    /* return system font information and handle */
        *FontHandle = (EFI_FONT_HANDLE)(UINTN)DEFAULT_FONT_HANDLE;
        if(StringInfoOut != NULL) {
            Status = FillFontInfo(*FontHandle, StringInfoOut);
            if(EFI_ERROR(Status))
                return Status;
            (*StringInfoOut)->ForegroundColor = Fg;
            (*StringInfoOut)->BackgroundColor = Bg;
            (*StringInfoOut)->FontInfoMask = FdInfo.FontInfoMask;
        }
        return EFI_SUCCESS;
    }

    Fm.MatchName  = (FdInfo.FontInfoMask & EFI_FONT_INFO_ANY_FONT) ? MATCH_INGNORE : MATCH_STRICT;
    Fm.MatchStyle = (FdInfo.FontInfoMask & EFI_FONT_INFO_ANY_STYLE) ? MATCH_INGNORE : 
                    (FdInfo.FontInfoMask & EFI_FONT_INFO_RESTYLE) ? MATCH_LOOSE : MATCH_STRICT;
    Fm.MatchSize  = (FdInfo.FontInfoMask & EFI_FONT_INFO_ANY_SIZE) ? MATCH_INGNORE : 
                    (FdInfo.FontInfoMask & EFI_FONT_INFO_RESIZE) ? MATCH_LOOSE : MATCH_STRICT;
    
    Status = FindFont(FontHandle, FName, FStyle, FSize, Fm, String);
    if(!EFI_ERROR(Status) && (StringInfoOut != NULL)) {
    /* font found, prepare font info */
        Status = FillFontInfo(*FontHandle, StringInfoOut);
        if(EFI_ERROR(Status))
            return Status;
        (*StringInfoOut)->ForegroundColor = Fg;
        (*StringInfoOut)->BackgroundColor = Bg;
        (*StringInfoOut)->FontInfoMask = FdInfo.FontInfoMask;
    }
        
    return Status;
}



// *************************** Service functions (not for public use) **********************

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   IsLineBreak
//
//  Description:
//  This function checks if given symbol is a line break
//
//  Input:
//  IN CHAR16 Char - Symbol to test
//
//  Output:
//  TRUE - Symbol is a linebreak
//  FALSE - Symbol is not a linebreak
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN IsLineBreak(CHAR16 Char)
{
	switch(Char)
	{
		case 0x000c:
		case 0x000d:
		case 0x2028:
		case 0x2029:
			return TRUE;
		default:
			break;
	}
	return FALSE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   IsLineBreakOpp
//
//  Description:
//  This function checks if given symbol is a line break opportunity
//
//  Input:
//  IN CHAR16 Char - Symbol to test
//
//  Output:
//  TRUE - Symbol is a linebreak opportunity
//  FALSE - Symbol is not a linebreak opportunity
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN IsLineBreakOpp(CHAR16 Char)
{
	if(IsLineBreak(Char))
		return TRUE;

	if(Char >= 0x2000 && Char <= 0x200a)
		return TRUE;

	switch (Char)
	{
		case 0x0020:
		case 0x1680:
		case 0x2013:
		case 0x205f:
			return TRUE;
		default:
			break;
	}
	return FALSE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   SplitByLineBreaks
//
//  Description:
//  This function splits given string into lines on linebreaks
//
//  Input:
//  IN EFI_STRING String - string to split
//
//  Output:
//  EFI_SUCCESS - Function executed successfully
//  EFI_OUT_OF_RESOURCES - Not enough memory to perform operation
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS SplitByLineBreaks(EFI_STRING String)
{
	UINT32 Size;
	UINT32 i;
	DRAW_LINE *Link;

	Size = StrSize16(String) / 2;	//size in symbols
	Link = (DRAW_LINE *)CreateNewLink(sizeof(UINTN) * 5);
	if(Link == NULL)
		return EFI_OUT_OF_RESOURCES;

	Link->StartIndex = 0;
	if(DrawFlags & EFI_HII_IGNORE_LINE_BREAK)
	{
		Link->EndIndex = Size - 2;		//ignore null terminator
        UpdateLineSize(Link);
		DListAdd(&DrawLines, (DLINK *)Link);
		return EFI_SUCCESS;
	}

	for(i = 0; i < (Size - 1); i++)
	{
		if(IsLineBreak(String[i]))
		{
			Link->EndIndex = i;
            UpdateLineSize(Link);
			DListAdd(&DrawLines, (DLINK *)Link);
			Link = (DRAW_LINE *)CreateNewLink(sizeof(UINTN) * 5);
			if(Link == NULL)
				return EFI_OUT_OF_RESOURCES;
			i++;
			Link->StartIndex = i;
		}
	}
	Link->EndIndex = Size - 2;
    UpdateLineSize(Link);
	DListAdd(&DrawLines, (DLINK *)Link);
	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   AdjustLineSize
//
//  Description:
//  This function analyzes lines of the string and makes them fit into drawing area size
//
//  Input:
//  None
//
//  Output:
//  EFI_SUCCESS - Function executed successfully
//  EFI_OUT_OF_RESOURCES - Not enough memory to perform operation
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS AdjustLineSize(VOID)
{
	DRAW_LINE *Link;
	UINTN TextHeight = ImageHeight - TextStartY;
	UINTN TextWidth = ImageWidth - TextStartX;
    EFI_STATUS Status;

	Link = (DRAW_LINE *)(DrawLines.pHead);
	while(Link != NULL)	{
//first detect line height
		if(TextHeight >= Link->LineHeight) {     
        /* line is visible entirely */
			TextHeight -= Link->LineHeight;
		} else {
        /* line is visible partially */
			if(DrawFlags & EFI_HII_OUT_FLAG_CLIP_CLEAN_Y || TextHeight == 0) {
				Link->LineHeight = 0;	//mark line as invisible and stop adjusting - all subsequent lines will be invisible 
				return EFI_SUCCESS;
			} else {
				Link->LineHeight = TextHeight;
				TextHeight = 0;
			}
		}

//second detect line width
		if(Link->LineWidth > TextWidth) {
        /* line needs clipping of wrapping */
			if(DrawFlags & EFI_HII_OUT_FLAG_WRAP) {
            /* wrapping mode */
                Status = WrapLine(Link, TextWidth);
                if(EFI_ERROR(Status))
                    return Status;
			} else {
            /* clipping mode */
                ClipLine(Link, TextWidth, ((DrawFlags & EFI_HII_OUT_FLAG_CLIP_CLEAN_X) ? TRUE : FALSE));
			}
		}
//proceed to next line
		Link = (DRAW_LINE *)Link->Link.pNext;
	}
	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   Draw
//
//  Description:
//  This function draws lines of the string
//
//  Input:
//  None
//
//  Output:
//  None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID Draw(VOID)
{
	DRAW_LINE *Link;
	UINTN i;
	CHAR16 CurrentSymbol;
	BOOLEAN Transparent = FALSE;
    EFI_STATUS Status;

    EFI_HII_GLYPH_INFO Cell;
    UINT8 *GlyphBlock;
    BOOLEAN Free;

    POINT_COORD gl_st;
    POINT_COORD gl_size;
    RECT_COORD glyph;

    POINT_COORD ln_st;
    POINT_COORD ln_size;
    RECT_COORD line;

    POINT_COORD origin;

    glyph.st = &gl_st;
    glyph.size = &gl_size;

    line.st = &ln_st;
    line.size = &ln_size;
    ln_st.y = TextStartY;                               //line start coordinate Y

	if(DrawFlags & EFI_HII_OUT_FLAG_TRANSPARENT)
		Transparent = TRUE;

	Link = (DRAW_LINE *)(DrawLines.pHead);
	while(Link != NULL && Link->LineHeight != 0)		//loop by strings
	{			
    /* init line rectangle */
        ln_st.x = TextStartX;                           //line start coordinate X
        ln_size.x = Link->LineWidth;                    //line width
        ln_size.y = Link->LineHeight;                   //line height

        origin.x = ln_st.x;
        origin.y = ln_st.y + Link->BaseLineOffset;

		for(i = Link->StartIndex; i <= Link->EndIndex; i++)
		{
			CurrentSymbol = DrawString[i];
            if((DrawFlags & EFI_HII_IGNORE_LINE_BREAK) && IsLineBreak(CurrentSymbol))
                continue;

            Status = IntGetGlyph(CurFont, CurrentSymbol, &Cell, &GlyphBlock, &Free);
            if(EFI_ERROR(Status))
                return;

            if(Status == EFI_WARN_UNKNOWN_GLYPH && (DrawFlags & EFI_HII_IGNORE_IF_NO_GLYPH)) {
                if(Free)
                    pBS->FreePool(GlyphBlock);
                continue;
            }
        /* init glyph rectangle */
            gl_st.x = origin.x + Cell.OffsetX;
            gl_st.y = origin.y - (Cell.Height + Cell.OffsetY);
            gl_size.x = Cell.Width;
            gl_size.y = Cell.Height;

            if(CheckVisible(&glyph, &line)) {
            /* symbol is visible at least partially */
            /* at this point symbol rect coordinates were adjusted to fit visible area */
                DrawGlyph(gl_st.x, gl_st.y, gl_size.x, gl_size.y, GlyphBlock, Transparent, ImageBlt, Cell.Width);
            }

            ln_st.x += Cell.AdvanceX;
            ln_size.x = ((INTN)ln_size.x <= Cell.AdvanceX) ? 0 : ln_size.x - Cell.AdvanceX;
            origin.x += Cell.AdvanceX;

            if(Free)
                pBS->FreePool(GlyphBlock);
		}			//end of drawing line

		ln_st.y += ln_size.y;
		Link = (DRAW_LINE *)Link->Link.pNext;
	}
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
