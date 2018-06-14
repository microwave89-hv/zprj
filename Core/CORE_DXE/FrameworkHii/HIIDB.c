//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2005, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
// $Header: /Alaska/SOURCE/Core/CORE_DXE/FrameworkHii/HIIDB.c 5     2/10/10 5:08p Felixp $
//
// $Revision: 5 $
//
// $Date: 2/10/10 5:08p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Core/CORE_DXE/FrameworkHii/HIIDB.c $
// 
// 5     2/10/10 5:08p Felixp
// Bug fix in HiiExtGetFormInfo function.
// 
// 4     2/10/10 3:43p Felixp
// x64 compiler warnings are fixed.
// 
// 3     12/29/09 2:38p Yakovlevs
// Fixed issue with hanging in TSE big number of setup questions.
// Changed size of Length fields in  some HII internal structures from
// UIN16 to UINTN. 
// Code clenup (removed not used variables changes to compile with W4)
// 
// 2     12/04/09 2:16p Yakovlevs
// 1.Fixed potential NULL pointer use in function NewFontPack()
// 2.Fixed inconsistancy in VarStore management (requires updated HiiDb.h)
// 
// 1     10/09/09 6:10p Felixp
// 
// 45    6/03/09 10:58a Yakovlevs
// if Hii->RemovePack is called reset global pointers to NULL since they
// might pointing at data that was freed.
// 
// 44    10/01/08 1:01p Yakovlevs
// fixed bug in HiiExtGetFormLabels() function.
// 
// 43    1/09/08 10:49a Yakovlevs
// 
// 42    9/05/07 9:18p Felixp
// 
// 41    9/05/07 5:59p Yakovlevs
// Bug fixes in UpdateForm and RemovePack routines.
// 
// 2     6/28/07 5:16p Yakovlevs
// Fixed FormUpdate Protocol Function, and some other minor bug fixes.
// 
// 39    5/23/07 4:32p Pavell
// Reindexing formsets
// 
// 38    3/18/07 3:10p Felixp
// GetSecondaryLanguages fix: return EFI_NOT_FOUND when no languages found
// 
// 37    3/12/07 6:06p Yakovlevs
// Fixed NewKbPack function.
// 
// 36    3/12/07 1:46p Yakovlevs
// Handled a situation when there are no Keyboard Layout data in HII
// Database.
// 
// 35    3/07/07 8:21p Yakovlevs
// Added GetKeyboardLayout function implamentation.
// 
// 34    1/23/07 12:23p Yakovlevs
// 
// 33    12/21/06 1:57p Felixp
// 
// 32    12/20/06 10:37a Felixp
// 
// 31    12/18/06 5:42p Pavell
// Added a fix for variable size determination
// 30    11/15/06 5:55p Yakovlevs
// 
// 29    11/02/06 6:45p Yakovlevs
// Fixed HiiTestString NON_SPACING attribute handling
// 
// 27    10/31/06 11:15a Yakovlevs
// HiiTestString fixed to skip none spacing characters.
// 
// 25    10/30/06 6:09p Yakovlevs
// HII Spec v 0.92 updates
// 
// 24    9/27/06 7:44p Felixp
// Improvement in GetHiiString: 
// If string is not found for the current system language language, try
// with the package primary language.
// 
// 23    9/26/06 9:03a Felixp
// Multilanguage Support. Do not use hard-coded glyphs. Load font file
// instead.
// 
// 22    9/18/06 6:23p Felixp
// Bug fix in HiiGetString: buffer overrun when Raw is FALSE
// 
// 21    8/24/06 10:11a Felixp
// x64 support: warning/error fixes
// 
// 20    8/04/06 5:18p Felixp
// Bug fix in NewFontPack function (wide glyph handling).
// 
// 19    7/24/06 11:46a Yakovlevs
// Hii->ExportDatabase support added.
// 
// 18    3/13/06 5:30p Felixp
// 
// 17    10/03/05 2:47p Markw
// Fixed uninitialized variables.
// 
// 16    7/20/05 6:43p Felixp
// GlyphToBlt modifed to support wide characters
// 
// 15    7/19/05 8:17p Felixp
// NewString modified to support update for all languages when three
// spaces Language provided
// 
// 13    7/13/05 9:46p Felixp
// 
// 12    6/24/05 2:03p Yakovlevs
// 
// 11    6/23/05 5:43p Yakovlevs
// Fixed "Missing String" message
// 
// 10    5/27/05 12:16p Felixp
// bug fix in HiiGetString
// 
// 9     2/28/05 6:21p Yakovlevs
// Fixed DateTime and Object Conditions issue;
// 
// 8     3/17/05 1:57p Felixp
// implementation of HiiNewPackNew updated
// 
// 7     3/04/05 12:52p Felixp
// 
// 6     3/04/05 9:23a Mandal
// 

//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	<This File Name>
//
// Description:	
//
//<AMI_FHDR_END>
//**********************************************************************
//
// Module Name: HIIDB.C
//
// Abstract: This file contains implementation of HII Database Protocol.
//
#include <HiiDb.h>
#include <Protocol/DevicePath.h>
#include <Protocol/HiiUtilities.h>
extern UINT8	*UsStdNarrowGlyphData;
extern HII_UTILITIES_PROTOCOL HiiUtilitiesProtocol;

//==================================================================================
// Some globals we need 
//==================================================================================

//------------------------------------------
//Prototypes
EFI_STATUS InitPrivateData(EFI_HANDLE MyImgHandle);
EFI_STATUS CreateLabelObjects(HII_LABEL *Label);
//EFI_STATUS HiiNewPack (IN EFI_HII_PROTOCOL		*This,
//					IN EFI_HII_PACK_LIST	*Package,
//					OUT EFI_HII_HANDLE		*Handle);

//------------------------------------------
//GUIDs
EFI_GUID gEfiHiiProtocolGuidOld	= EFI_HII_OLD_PROTOCOL_GUID;
EFI_GUID gEfiHiiProtocolGuidNew	= EFI_HII_NEW_PROTOCOL_GUID;
static EFI_GUID gEfiExtHiiProtocolGuid	= EFI_HII_EXT_PROTOCOL_GUID;
//------------------------------------------
//Data Vars 

//Define String Database Key fields
#define STR_KEY			0
#define STR_KEY_CNT		1
//it is going to be combined key 
//Token->size16;LangIdx->size32;Handle->size16; total = 8 byte->UINT64
//Token->Least Segnificant Field Handle Most Significant Field
//the resulting Index for StringToken->23, LangIndex->2, Hii Handle=1 will be 
//	   Handle|LangIdx |Token
//     0x0001|00000002|0023 -> easy to sort easy to find
static DBE_OFFSET_KEY_CONTEXT gStrOffsetInfo = {EFI_FIELD_OFFSET(HII_STR ,Token), 8 };
static DBE_KEY_FIELD	gStrKey=OFFSET_KEY(gStrOffsetInfo);

//Any Language Printable string
static UINT16	gAnyLang[]=L"Any Language";
//HII DATABASE global var
static	HII_DB			gHiiDb;

///////////////////////////////////////////////////////////////////
//in order to save some time when LocateHandle routine been called 
//I have decide to save Current HandleInfo structure pionter 
//here rather than locate it every time 
static HII_HANDLE	*mCurHnd=NULL;
static HII_LANG		*mCurLang=NULL;
static UINTN		mCurHid=0, mCurLid=0;

///////////////////////////////////////////////////////////////////
//in order to save some time when HiiGetLine routine been called 
//I have decide to save Current StringInfo structure pionter 
//here rather than locate it every time HiiGetLine been called 
static HII_STR		*mCurStr=NULL;

///////////////////////////////////////////////////////////////////
// save the varstore context based on the formset
static UINT16  CurrentVarId = 0;

//==================================================================================
// Entry Point
//==================================================================================
//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:	HiiDbEntryPoint()
//
// Description: Initialize HII Database (Standard EFI Image entry - EFI_IMAGE_ENTRY_POINT)
//
// Input:	EFI_HANDLE			ImageHandle		This Driver Image Handle.
//			EFI_SYSTEM_TABLE 	*SystemTable	Pointer to the EFI System Table
//
// Output:  EFI_STATUS	  	EFI_SUCCESS - Driver Loadded.
//  						Other       - Driver Error
//
//<AMI_PHDR_END>
//**********************************************************************

EFI_STATUS HiiDbEntryPoint(IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable){
	EFI_STATUS				Status=0;
	UINTN					hCnt;
	EFI_HANDLE				*hBuf;
//-----------------------------------
	InitAmiLib(ImageHandle, SystemTable);

	//Only one HII Driver has to be in the system
	Status=pBS->LocateHandleBuffer(ByProtocol, &gEfiHiiProtocolGuidOld, NULL, &hCnt, &hBuf);

  	//If there was no error, report that we has been already started
  	if (!EFI_ERROR(Status)) {
		if (!hBuf)pBS->FreePool(hBuf); //Don't forget to free the memory
		return EFI_ALREADY_STARTED;
	}

	Status=InitPrivateData(ImageHandle);
	if(EFI_ERROR(Status)) return Status;

	Status = pBS->InstallMultipleProtocolInterfaces(&gHiiDb.HiiHandle,
					&gEfiHiiProtocolGuidOld,&gHiiDb.HiiProtocolOld,
					&gEfiHiiProtocolGuidNew,&gHiiDb.HiiProtocolNew,
					&gEfiExtHiiProtocolGuid,&gHiiDb.HiiExtProtocol,
                    &gHiiUtilitiesProtocolGuid, &HiiUtilitiesProtocol,
					NULL);
 	return Status;
}

///////////////////////////////////////////////////////////////////
// Common Worker Functions
///////////////////////////////////////////////////////////////////
//*************************************************************************
//<AMI_PHDR_START>
//
// Name: GetDefaultLang
//
// Description:
//  EFI_STATUS GetDefaultLang(OUT CHAR16 *DefaultLang) returns the default 
// system language in the string specified by DefaultLang.
//
// Input:
//  OUT CHAR16 *DefaultLang
// Pointer to the null-terminated Unicode string.
//
// Output:
//  EFI_NOT_FOUND, if the default language could not be found.
//  Otherwise, EFI_SUCCESS.
//
// Modified:
//
// Referrals:
// 
// Notes:	
//          
//<AMI_PHDR_END>
//*************************************************************************
//Get System Default Language
EFI_STATUS GetDefaultLang(CHAR16 *DefaultLang){
	EFI_GUID 	EfiGlobalVariableGuid = EFI_GLOBAL_VARIABLE;		
	EFI_STATUS	Status=0;
	UINT8       al[3];
	UINTN		i=sizeof(al);
//-----------------------
    Status=pRS->GetVariable(L"Lang",&EfiGlobalVariableGuid,NULL,&i,al);
    if (EFI_ERROR(Status)) return Status;
	
	for(i=0; i<sizeof(al) ;i++) DefaultLang[i]=al[i];
	DefaultLang[sizeof(al)]=0;
	return Status;
}

//-----------------------------------------------------------------
//This Function will look in Item List and try to find mutch for Item of Size.
//if it finds it will return Pointer to the matching Item and update Index if not - NULL
EFI_STATUS LocateItem(T_ITEM_LIST *ItemLst, VOID *Item, UINTN Size, OUT UINTN *Index){
	UINTN		i;
//-----------------	
	for(i=0; i<ItemLst->ItemCount; i++){
		if(!MemCmp(ItemLst->Items[i],Item,Size)) {
			if(Index)*Index=i;
			return EFI_SUCCESS;
		}
	}
	return EFI_NOT_FOUND;
}

///////////////////////////////////////////////////////////////////
//Will return Lenth of the screen representation of Str with respect 
//of wide narrow and non spacing glyphs it using
//Len excluding '0' char (\n)
UINT16 GetScrLen(CHAR16 *Str, UINT16 Len){
	UINTN		i;
	UINT16		u,sl=0;
	HII_N_FONT	*fnt;
//--------------------------------------
	for(i=0;i<Len;i++){
		u=Str[i];
		if(u<0x20 || u>=0xfff0)continue;
		fnt=gHiiDb.FontDb[u];
		if(fnt){
			if(fnt->Attr & GLYPH_NON_SPACING) continue;
			if(fnt->Attr & GLYPH_WIDE) sl+=2;
			else sl++;
		} else sl++; //we will print empty rect for non existent glyph
	}
	return sl;
}

///////////////////////////////////////////////////////////////////
//Will allocate Mem for the length of the string and Copy "Str" there
UINT16* StrAlloc(UINT16 *Str,UINT16 *StrLen OPTIONAL, UINT16 *ScrLen OPTIONAL){
	UINT16				len;
	UINT16				*str;
//-------------------------------------
	len=(UINT16)Wcslen(Str);//terminator not included
	str=(UINT16*)Malloc((len+1)*sizeof(UINT16));
	if(!str)return NULL;
	Wcscpy(str,Str);
	if(StrLen)*StrLen=len+1;
	if(ScrLen)*ScrLen=GetScrLen(Str,len);
	return str;
}

///////////////////////////////////////////////////////////////////
//This will Change Language Attributes
//VOID SetLangAttr(UINTN Index, UINT32 Attr){
//	HII_LANG	*lang;
//--------------------
//	lang=(HII_LANG*)gHiiDb.LangDb.ResDsc[Index];
//	lang->Attr=Attr;
//}

///////////////////////////////////////////////////////////////////
//this will find and return HII_LANG "Index", 
//if "Language" is stored In Hii Handle Database 
HII_LANG* LocateLang(UINT16 *Language, UINTN *Index){
	EFI_STATUS	Status;
	UINTN		idx;
//------------------------
	if( !mCurLang || MemCmp(&mCurLang->sName[0],Language,sizeof(mCurLang->sName)) )
	{
		Status=LocateItem(&gHiiDb.LangDb,Language,sizeof(UINT16)*4,&idx);
		if(EFI_ERROR(Status)){
			mCurLang=NULL; //flush Language Cache
			mCurLid=0;	  //make index to generate exception if used
		} else {
			mCurLang=gHiiDb.LangDb.Items[idx];
			mCurLid=idx;
		}
	}
	if(mCurLang && Index)*Index=mCurLid;
	return mCurLang;
}

HII_HANDLE *LocateHandleGuid(EFI_GUID *Guid, UINTN	*Index){
	HII_HANDLE		*phnd=NULL;	
	UINTN			i;	
//-------------------------------
	for(i=0; i<gHiiDb.HandleDb.ItemCount; i++){
		phnd=gHiiDb.HandleDb.Items[i];
		if(!MemCmp(&phnd->Guid,Guid,sizeof(EFI_GUID)))break;
		else phnd=NULL;
	}
	if(phnd && Index)*Index=i;
	return phnd;
}

///////////////////////////////////////////////////////////////////
//This function will Locate another Handle with the same Guid as 
//passed Handle. 
//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO
//This function is Obsolete but I need it for compliance with Intel's
//Setup because they using same guid more than once per Ifr and Strings pare.
//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO
VOID LocateSameGuidHandle(UINTN CurIdx, UINTN *IdxBuffer, UINTN *IdxCount){
	HII_HANDLE	*phnd=NULL,*chnd=gHiiDb.HandleDb.Items[CurIdx];
	UINTN		i, c=0;
//----------------------------
	for(i=0; i<gHiiDb.HandleDb.ItemCount; i++){
		if(i==CurIdx) continue;
		phnd=gHiiDb.HandleDb.Items[i];
		if(!MemCmp(&phnd->Guid,&chnd->Guid,sizeof(EFI_GUID))){
			IdxBuffer[c]=i;
			c++;
		}else phnd=NULL;
	}
	*IdxCount=c;
}

///////////////////////////////////////////////////////////////////
//if on passed handle in any string function there are no 
//strings associated with we need to find another handle with 
//the same guid having strings on it
HII_HANDLE	*LocateStrHandleGuid(UINTN CurIdx, UINTN *Index){
	HII_HANDLE	*phnd=NULL,*chnd=gHiiDb.HandleDb.Items[CurIdx];
	UINTN		i;
//----------------------------
	for(i=0; i<gHiiDb.HandleDb.ItemCount; i++){
		if(i==CurIdx) continue;
		phnd=gHiiDb.HandleDb.Items[i];
		if(!MemCmp(&phnd->Guid,&chnd->Guid,sizeof(EFI_GUID)) && phnd->HasStr){
			if(Index)*Index=i;
			break;
		}else phnd=NULL;
	}
	return phnd;
}

///////////////////////////////////////////////////////////////////
//this will find and return HII_HANDLE "Index", 
//if "Handle" is stored In Hii Handle Database 
static HII_HANDLE* LocateHandle(EFI_HII_HANDLE Handle, UINTN	*Index){
	EFI_STATUS	Status;
	UINTN		idx;
//------------------------
	if((!mCurHnd) || (mCurHnd->Handle!=Handle)){
		Status=LocateItem(&gHiiDb.HandleDb,&Handle,sizeof(EFI_HII_HANDLE),&idx);	
		if(EFI_ERROR(Status)){
			mCurHnd=NULL; //flush Handle Cache
			mCurHid=-1;	  //make index to generate exception if used
		} else {
			mCurHnd=gHiiDb.HandleDb.Items[idx];
			mCurHid=idx;
		}
	}
	if(mCurHnd && Index)*Index=mCurHid;
	return mCurHnd;
}

///////////////////////////////////////////////////////////////////
//this will find and return HII_HANDLE "Index", 
//if "Handle" is stored in Handle Database 
//or Append Handle Database with this Handle if not and return a new "Index" 
EFI_STATUS LocateHandleAdd(EFI_HII_HANDLE Handle, EFI_GUID *GuidId, UINTN *Index){
	EFI_STATUS		Status=0;
	HII_HANDLE		*phnd;
//----------------
	phnd=LocateHandle(Handle,Index);
	if(!phnd){
		phnd=MallocZ(sizeof(HII_HANDLE));
		if(!phnd)return EFI_OUT_OF_RESOURCES;
		pBS->CopyMem(&phnd->Guid,GuidId,sizeof(EFI_GUID));
		phnd->Handle=Handle;
		Status=AppendItemLst(&gHiiDb.HandleDb,phnd);
		if(EFI_ERROR(Status)) return Status;
		*Index=gHiiDb.HandleDb.ItemCount-1;
	}
	return EFI_SUCCESS;
}

///////////////////////////////////////////////////////////////////
//this will find and return HII_LANG "Index", 
//if "Language" is stored in Handle Database 
//or Append Handle Database with this Handle if not and return a new "Index" 
EFI_STATUS LocateLangAdd(UINT16 *Language, UINT16 *PrintLanguage, UINTN *Index){
	EFI_STATUS	Status;
	HII_LANG	*lang;
//------------------
	//Check if we have the Language installed already
	lang=LocateLang(Language,Index);	
	if(!lang){ 
		lang=MallocZ(sizeof(HII_LANG));
		if(!lang)return EFI_OUT_OF_RESOURCES;
		pBS->CopyMem(&lang->sName,Language,sizeof(UINT16)*4);
		if(PrintLanguage){
			lang->lName=StrAlloc(PrintLanguage,NULL,NULL);
			if(!lang->lName) return EFI_OUT_OF_RESOURCES;
		}
		Status=AppendItemLst(&gHiiDb.LangDb,lang);
		if(EFI_ERROR(Status)) return Status;
		if(Index)*Index=gHiiDb.LangDb.ItemCount-1;
	}
	return EFI_SUCCESS;
}


///////////////////////////////////////////////////////////////////
//This will check if Lang Index is present in Secondary Lang List 
//on this Handle
///////////////////////////////////////////////////////////////////
EFI_STATUS LocateSecLangAdd(HII_HANDLE *Hnd, UINTN	*SecLangIdx, BOOLEAN AddIt){
	UINTN		i;
//------------------------------
	for(i=0; i<Hnd->SecLang.ItemCount; i++){
		if(*SecLangIdx==(UINTN)(Hnd->SecLang.Items[i])) return EFI_SUCCESS;
	}
	if(AddIt)return AppendItemLst(&Hnd->SecLang,(VOID*)(*SecLangIdx));
	else return EFI_NOT_FOUND;
}


///////////////////////////////////////////////////////////////////
//=================================================================
//HII Database Protocol Functions 
//=================================================================
///////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////
// Font related 
///////////////////////////////////////////////////////////////////
EFI_STATUS NewFontPack(IN EFI_HII_FONT_PACK		*Package)
{
	UINTN				i;
	UINT16				u;
	EFI_NARROW_GLYPH	*ng;
	EFI_WIDE_GLYPH		*wg;
//--------------------------

    //Set Pointer to the beginning of Package Data.
    ng=(EFI_NARROW_GLYPH*)(Package+1);

	if(Package->NumberOfNarrowGlyphs){
		HII_N_FONT			*fnt;
	//---------------------------
		//Allocate Space for Number of Narrow Glyphs
		fnt=(HII_N_FONT*)Malloc(sizeof(HII_N_FONT)*Package->NumberOfNarrowGlyphs);
		if(!fnt)return EFI_OUT_OF_RESOURCES;

		for(i=0; i<Package->NumberOfNarrowGlyphs; i++){
			u=ng[i].UnicodeWeight;
//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO
		//we will populate only empty spots in FontD or oposite
//made SDL token for that 
			if(!gHiiDb.FontDb[u]){
//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO
				//fnt=(HII_FONT*)Malloc(sizeof(HII_FONT));
				pBS->CopyMem((VOID*)&fnt[i], &ng[i].Attributes,sizeof(HII_N_FONT));
				gHiiDb.FontDb[u]=&fnt[i];
			}
		}
	}


	if(Package->NumberOfWideGlyphs){
		UINTN		j,k;
		HII_W_FONT	*fnt;
	//---------------
		//Allocate Space for Number of Wide Glyphs
		wg=(EFI_WIDE_GLYPH*)(ng+Package->NumberOfNarrowGlyphs);
		fnt=(HII_W_FONT*)Malloc((sizeof(HII_W_FONT))*Package->NumberOfWideGlyphs);
		if(!fnt)return EFI_OUT_OF_RESOURCES;
		
		for(i=0; i<Package->NumberOfWideGlyphs; i++){
			u=wg[i].UnicodeWeight;
			if(!gHiiDb.FontDb[u]){
				fnt[i].Attr=wg[i].Attributes;
				for(j=0,k=0; j<NG_SIZE;j++, k+=2){
					fnt[i].GlData[k]=wg[i].GlyphCol1[j];
					fnt[i].GlData[k+1]=wg[i].GlyphCol2[j];
				}
				gHiiDb.FontDb[u]=(HII_N_FONT*)&fnt[i];
			}
		}
	}
	return EFI_SUCCESS;
}



///////////////////////////////////////////////////////////////////
EFI_STATUS HiiTestString(IN EFI_HII_PROTOCOL	*This, 
						 IN CHAR16				*StringToTest,
						 IN OUT UINT32			*FirstMissing,
						 OUT UINT32				*GlyphBufferSize)
{
	EFI_STATUS		Status=0;
	UINT32			i;
	UINT32			bs=0;
	HII_N_FONT		*fnt;
//------------------------------
	if(!This) return EFI_INVALID_PARAMETER;
	if ((!FirstMissing)||(!StringToTest)||(!GlyphBufferSize)) return EFI_INVALID_PARAMETER;

	i=*FirstMissing;
	while (StringToTest[i]!=0){
		fnt=gHiiDb.FontDb[ StringToTest[i] ];
		if(fnt){
			if(fnt->Attr& GLYPH_NON_SPACING ){
				i++;
				continue;
			}
			if(fnt->Attr&GLYPH_WIDE) bs+=WG_SIZE;		
			else bs+=NG_SIZE;		
			i++;
		} else {
			Status=EFI_NOT_FOUND;
			break;
		}
	}
	*FirstMissing=i;
	*GlyphBufferSize=bs;
	return Status;
}

static UINT8	gGE[NG_SIZE]=
	{0x00,0x00,0x00,0x7E,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x7E,0x00,0x00,0x00};// \
//     0x00,0x00,0x00,0x7E,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x7E,0x00,0x00,0x00};

static EFI_WIDE_GLYPH	gGB;
///////////////////////////////////////////////////////////////////
EFI_STATUS HiiGetGlyph(IN EFI_HII_PROTOCOL	*This,
					   IN CHAR16			*Source,
					   IN OUT UINT16		*Index,
					   OUT UINT8			**GlyphBuffer,
					   OUT UINT16			*BitWidth,
					   IN OUT UINT32		*InternalStatus)
{
	UINTN				i, bs=NG_SIZE;
	HII_N_FONT			*fnt;//=gHiiDb.FontDb[Source[j]];
//	HII_GL_COL			*gc1=NULL, *gc2=NULL;
//	BOOLEAN				w=FALSE;
//------------------------------------------
	if(!This) return EFI_INVALID_PARAMETER;

	if((!GlyphBuffer)||(!Index)||(!Source)||(!BitWidth)) return EFI_INVALID_PARAMETER;
	fnt=gHiiDb.FontDb[Source[*Index]];

	if(!fnt) {
		if(InternalStatus)*InternalStatus=(UINT32)-1;
		//If after calling TestString somebody will call us with invalid Unicode Char
		pBS->CopyMem(&gGB.GlyphCol1[0],&gGE, NG_SIZE); 
		*BitWidth=GLYPH_W;
		*GlyphBuffer=(UINT8*)&gGB;
		(*Index)++;
		return EFI_NOT_FOUND;
	} 

	//first char must not be the non-spacing character 
	if(fnt->Attr&GLYPH_NON_SPACING) return EFI_INVALID_PARAMETER;

	if(fnt->Attr&GLYPH_WIDE){
		*BitWidth=GLYPH_W*2;
		bs=WG_SIZE;
	} else *BitWidth=GLYPH_W;
	
	pBS->SetMem(&gGB,sizeof(EFI_WIDE_GLYPH),0);
	do{
		fnt=gHiiDb.FontDb[Source[*Index]];
		for(i=0;i<bs;i++) gGB.GlyphCol1[i]|=fnt->GlData[i]; 
		(*Index)++;
	} while(fnt->Attr&GLYPH_NON_SPACING);
	*GlyphBuffer=(UINT8*)&gGB;
	if(InternalStatus)*InternalStatus=0;
		
	return EFI_SUCCESS;
}


///////////////////////////////////////////////////////////////////
//!!!! this function suppose to take care of thing with mixed size gpyphs 
EFI_STATUS HiiGlyphToBlt(IN EFI_HII_PROTOCOL	*This,
						 IN UINT8				*GlyphBuffer,
						 IN EFI_UGA_PIXEL		Foreground,
						 IN EFI_UGA_PIXEL		Background,
						 IN UINTN				Count,//Number of NARROW Glyps left in BltBuffer
						 //or count from the end of the buffer in terms of NARROW glyphs
						 IN UINTN				Width,
						 IN UINTN				Height,
						 IN OUT EFI_UGA_PIXEL	*BltBuffer)
{
//	UINTN	x,y;//,i,o;
//	UINT8	k = Width > GLYPH_W ? 2 : 1;
//------------------------------------
//	if(!This) return EFI_INVALID_PARAMETER;
//	if( !(Width==GLYPH_W || Width==(GLYPH_W*2)) || Height!=GLYPH_H )return EFI_INVALID_PARAMETER;
/*	for (y=0,o=0; y<Height; y++){
		for(i=0; i<Width/GLYPH_W; i++){
			for (x=0; x<GLYPH_W; x++){
				if ( GlyphBuffer[y*k+i] & (0x80 >> x)) BltBuffer[y*GLYPH_W*Count+x+o]=Foreground;
				else BltBuffer[y*GLYPH_W*Count+x+o]=Background;
			}
			o=GLYPH_W;
		}
	}

	return EFI_SUCCESS;
  UINTN                     X;
  UINTN                     Y;
*/
	UINT8 Mask;
	UINTN Index, Line, Part;
	UINTN TotalParts = Width/GLYPH_W;
	EFI_NARROW_GLYPH *Glyph = (EFI_NARROW_GLYPH *)GlyphBuffer;
	if(!This) return EFI_INVALID_PARAMETER;
	if( !(Width==GLYPH_W || Width==GLYPH_W*2) || Height!=GLYPH_H || Count<TotalParts)return EFI_INVALID_PARAMETER;
	for (Line = 0, Index=0; Line < Height; Line++, Index+=GLYPH_W * (Count-TotalParts)) {
		for(Part=0; Part<TotalParts; Part++){
			for (Mask = 0x80; Mask > 0; Mask>>=1, Index++) {
				if (Glyph->GlyphCol1[Line*TotalParts+Part] & Mask)
					BltBuffer[Index] = Foreground;
				else
					BltBuffer[Index] = Background;
			}
		}
	}
/*///
	BltBuffer[Index] = (Glyph->GlyphCol1[y] & (1 << x)) ? Foreground : Background;
	if (Width > GLYPH_W)
		BltBuffer[Index+GLYPH_W] = (Glyph->GlyphCol1[GLYPH_H+y] & (1 << x)) ? Foreground : Background;
///
	EFI_NARROW_GLYPH *Glyph = (EFI_NARROW_GLYPH *)GlyphBuffer;
	for (y = 0; y < Height; y++) {
		for (x = 0; x < GLYPH_W; x++) {
			UINTN Index = y * GLYPH_W * Count + (GLYPH_W - x - 1);
			for(i=0; i<Width/GLYPH_W; i++)
				if ((Glyph->GlyphCol1[i*GLYPH_H+y] & (1 << x)) != 0)
					BltBuffer[Index+GLYPH_W*i] = Foreground;
				else
					BltBuffer[Index+GLYPH_W*i] = Background;
		}
	}*/
  return EFI_SUCCESS;
}

///////////////////////////////////////////////////////////////////
// String related
///////////////////////////////////////////////////////////////////
HII_STR	*LocateString(HII_HANDLE *PHnd, UINTN LangIdx, STRING_REF Token/*, UINTN HandleIdx OPTIONAL*/){
	UINTN			li=LangIdx, j;
	HII_STR			sd = {0,0,0,0,NULL};
	INT8			v;
	VOID			**cs;
//-----------------
	//if CurrentString must be refreshed	
	if(!mCurStr || mCurStr->LangIdx!=LangIdx || mCurStr->Token!=Token || mCurStr->Handle!=PHnd->Handle)
	{

		//---------------------
		do {
			sd.Handle=PHnd->Handle;
			sd.LangIdx=(UINT32)li;
			sd.Token=Token;

			DbeLocateKey(&gHiiDb.StringDb,STR_KEY,(VOID*)&sd,(VOID**)&cs,&v,&j);

			if(v)mCurStr=NULL;
			else {
				mCurStr=(HII_STR*)(*cs);
				break;
			}

			//if we were looking for any language and failed
			//just get Primary Package Language
			if(!li)li=PHnd->PriLang;
			else break;
		} while(v);
//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO
//this patch was made to keep compatibility with Intel's implemntation
//of BDS - DevicerManagerVfrBin and FrontPageVfrBin uses the same Guid
//and Same String Pack expecting valid strings on from one StringPack
//when passing different GUIDs?????????
/*		if(!mCurStr){
			HII_HANDLE	*phnd;
			UINTN		i,sgib[10]={0,0,0,0,0,0,0,0,0,0};//same GUID index Buffer
		//----------------------------------
			LocateSameGuidHandle(HandleIdx,&sgib[0],&c);
			for(i=0; i<c;i++){
				li=LangIdx;
				phnd=gHiiDb.HandleDb.Items[sgib[i]];
				do {
					sd.Handle=phnd->Handle;
					sd.LangIdx=(UINT32)li;
					sd.Token=Token;

					DbeLocateKey(&gHiiDb.StringDb,STR_KEY,(VOID*)&sd,(VOID**)&cs,&v,&j);

					if(v)mCurStr=NULL;
					else {
						mCurStr=(HII_STR*)(*cs);
						break;
					}
					//if we were looking for any language and faild
					//just get Primary Package Language
					if(!li)li=PHnd->PriLang;
					else break;
				} while(v);
				if(mCurStr)break;
			}
		}
*/
//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO
	}
	return mCurStr;
}

///////////////////////////////////////////////////////////////////
EFI_STATUS	ReplaceString(HII_STR *StrData, UINT16 *Replacement)
{
	UINT16	*str;
	UINT16	len,slen;
//-----------------------------
	str=StrAlloc(Replacement, &len, &slen);
	if(!str)return EFI_OUT_OF_RESOURCES;
	
	if(StrData->NewStr.StrPtr)pBS->FreePool(StrData->NewStr.StrPtr);

	StrData->NewStr.StrLen=len;
	StrData->NewStr.ScrLen=slen;
	StrData->NewStr.StrPtr=str;
	
	return EFI_SUCCESS;
}

///////////////////////////////////////////////////////////////////
EFI_STATUS	AddString(UINTN	LangIdx, HII_HANDLE *PHandle, UINT16 *String, BOOLEAN Initial, STRING_REF *Token)
{
	HII_STR				*str;
//-------------------------------------
	str=MallocZ(sizeof(HII_STR));
	if(!str) return EFI_OUT_OF_RESOURCES;

	if(Initial){
		str->String.StrPtr=StrAlloc(String,&str->String.StrLen,&str->String.ScrLen);
		if(!(str->String.StrPtr))return EFI_OUT_OF_RESOURCES;
	} else {
		str->NewStr.StrPtr=StrAlloc(String,&str->NewStr.StrLen, &str->NewStr.ScrLen);
		if(!(str->NewStr.StrPtr))return EFI_OUT_OF_RESOURCES;
	}
	
	str->LangIdx=(UINT32)LangIdx;
	//if Token is provided, use it. Otherwise assign new one.
	if (Token && *Token) str->Token=*Token;
	else
	{
		str->Token=PHandle->NextStrToken;
		PHandle->NextStrToken++;
		if (Token) *Token = str->Token;
	}
	str->Handle=PHandle->Handle;

	return DbeInsert(&gHiiDb.StringDb,(VOID*)str);
}

EFI_STATUS UpdateString(IN UINTN				li,
                        IN HII_HANDLE			*phnd,
                        IN STRING_REF			*Reference,
						IN CHAR16				*NewString)
{
	EFI_STATUS Status;
	//Check if String with this Token#  already present in String Db
	if((*Reference)==0){
		Status=AddString(li,phnd,NewString,FALSE,Reference);
		if(EFI_ERROR(Status)) return Status;
	} else {
		HII_STR			*str;	
		if (*Reference >= phnd->NextStrToken) return EFI_INVALID_PARAMETER;
		str=LocateString(phnd,li,*Reference);
		//if str is NULL, it means that string with this token has been created 
		//for a different language 
		Status= (str) ? ReplaceString(str,NewString) : AddString(li,phnd,NewString,FALSE,Reference);
	}
	return Status;

}
///////////////////////////////////////////////////////////////////
EFI_STATUS HiiNewString(IN EFI_HII_PROTOCOL		*This,
						IN CHAR16				*Language,
                        IN EFI_HII_HANDLE		Handle,
                        IN STRING_REF			*Reference,
						IN CHAR16				*NewString)
{
	UINTN			li=0, hi=0;
	HII_LANG		*lang;
	HII_HANDLE		*phnd;
	EFI_STATUS		Status=0;
	UINT16			dl[4]={0x20,0x20,0x20,0}, *pdl;//Any Lang
//-------------------------------
	if(!This || !Reference || !NewString) return EFI_INVALID_PARAMETER;
	//first Check if the Handle is valid. 
	phnd=LocateHandle(Handle,&hi);
	if(!phnd) return EFI_INVALID_PARAMETER;

	if(!phnd->HasStr){
		phnd=LocateStrHandleGuid(hi,&hi);
		if(!phnd) return EFI_INVALID_PARAMETER;
	}
	
	if(!Language){
		pdl=&dl[0];
		if(EFI_ERROR( GetDefaultLang(pdl))){
			pdl=(UINT16*)gHiiDb.LangDb.Items[phnd->PriLang];
		}
	} else pdl=Language;

	//dl has a language string "xxx"
	lang=LocateLang(pdl,&li);

	if (!li)
	{//language index 0 referes to language "   ", which means we have to update
	 //string for all languages
		//update string for primary language
		Status = UpdateString(phnd->PriLang,phnd,Reference,NewString);
		//update string for all secondary languages
		for(li=0; !EFI_ERROR(Status) && li<phnd->SecLang.ItemCount; li++)
			Status = UpdateString((UINTN)phnd->SecLang.Items[li],phnd,Reference,NewString);
		return Status;
	}

	if(!lang) return EFI_INVALID_PARAMETER;

	//If language is valid but not mutch Pack PriLang
	if(phnd->PriLang!=li){
		Status=LocateSecLangAdd(phnd,&li,FALSE);
		if(EFI_ERROR(Status))li=phnd->PriLang;
		//lang=(HII_LANG*)gHiiDb.LangDb.Items[li];
	} 
	return UpdateString(li,phnd,Reference,NewString);
}

///////////////////////////////////////////////////////////////////
EFI_STATUS GetLanguageFromPack(EFI_HII_STRING_PACK *Pack, UINTN *LangIndex){
	UINT16		*sn, *ln;		
	UINT8		*ofs=(UINT8*)Pack;//(Pack+1);
//-------------------------
	sn=(UINT16*)(ofs+Pack->LanguageNameString);
	ln=(UINT16*)(ofs+Pack->PrintableLanguageName);
	return LocateLangAdd(sn,ln,LangIndex);	
}

///////////////////////////////////////////////////////////////////
BOOLEAN IsLastStrPack(EFI_HII_STRING_PACK *Pack){
	if(Pack->Header.Type==EFI_HII_STRING && 
		Pack->Header.Length == 0 && Pack->Attributes == 0 &&
		Pack->LanguageNameString == 0 && Pack->NumStringPointers == 0 &&
		Pack->PrintableLanguageName == 0 ) return TRUE;
	return FALSE;
}

///////////////////////////////////////////////////////////////////
EFI_STATUS HiiGetPrimaryLanguage(IN EFI_HII_PROTOCOL	*This,
								 IN EFI_HII_HANDLE		Handle,
								 OUT EFI_STRING *LanguageString)
{
	HII_HANDLE		*phnd;
	HII_LANG		*lang;
	UINTN			hi;
	UINT16			*ls,*bp;
//----------------------
	if(!This || !LanguageString) return EFI_INVALID_PARAMETER;

	phnd=LocateHandle(Handle,&hi);
	if(!phnd) return EFI_INVALID_PARAMETER;
	if(!phnd->HasStr){
		phnd=LocateStrHandleGuid(hi,&hi);
		if(!phnd) return EFI_INVALID_PARAMETER;
	}
//TODO//TODO//TODO//TODO//TODO//TODO//TODO//???????????????????????????????????????
	//if for some reson Somebody submit just IFR vith no Strings
	//there are no way to determine language so I just put there 0 -Any Language
	//but Intel's code expect me to return something like "eng" 
	//so I will return Default System Lang.
//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO
	ls=Malloc(sizeof(UINT16)*3*(phnd->SecLang.ItemCount+1)+1); //4 characters 
	if(!ls) return EFI_OUT_OF_RESOURCES;

	bp=ls;
	lang=gHiiDb.LangDb.Items[phnd->PriLang];
	pBS->CopyMem(ls,&lang->sName,sizeof(UINT16)*3);
	bp+=3;

	for(hi=0;hi<phnd->SecLang.ItemCount; hi++){
		lang=gHiiDb.LangDb.Items[(UINTN)phnd->SecLang.Items[hi]];
		pBS->CopyMem(bp,&lang->sName,sizeof(UINT16)*3);
		bp+=3;
	}
	*bp=0;
	*LanguageString=ls;

	return EFI_SUCCESS;
}

///////////////////////////////////////////////////////////////////
//
EFI_STATUS HiiGetSecondaryLanguages(IN EFI_HII_PROTOCOL		*This,
									IN EFI_HII_HANDLE		Handle,
                                    IN CHAR16				*PrimaryLanguage,
									OUT EFI_STRING			*LanguageString)
{
	UINTN			id,i;
	HII_HANDLE		*phnd;
	HII_LANG		*lang;
	UINT16			*ls;
//----------------------
	if(!This) return EFI_INVALID_PARAMETER;

	phnd=LocateHandle(Handle,NULL);
	if(!phnd) return EFI_INVALID_PARAMETER;
	
	//Some how caller managed to scrue up with parameters.
	lang=LocateLang(PrimaryLanguage,&id);//Lang provided does not mutch with what we've recorded 
	if( !lang || phnd->PriLang!=id ) return EFI_INVALID_PARAMETER;
	
	if(phnd->SecLang.ItemCount>0){
		UINT16	*l;
	//----------------
		ls=Malloc(sizeof(UINT16)*3*phnd->SecLang.ItemCount+1);
		if(!ls) return EFI_OUT_OF_RESOURCES;
		l=ls;
		for(i=0; i<phnd->SecLang.ItemCount; i++){
			//we are not returning Any Language str "   "
			//And Any Lang String has index 0 upon initialization
			if((UINTN)(phnd->SecLang.Items[i])){
				lang=(HII_LANG*)gHiiDb.LangDb.Items[(UINTN)(phnd->SecLang.Items[i])];
				pBS->CopyMem(l,&lang->sName[0],sizeof(UINT16)*3);//4 unicode chars;
				l+=3; 
			}
		}//resulting string will be consist of N*3xUINT16+TERMINATOR 
		*l=0x0000; //put terminator at the end of set of sec lang
		*LanguageString=ls;
	}else { *LanguageString=NULL; return EFI_NOT_FOUND;}
	return EFI_SUCCESS;
}

///////////////////////////////////////////////////////////////////
//This is a worker function to avoid dubliceted code in HiiGetString,
//HiiGetLine and ExtHiiGetStrInfo
HII_STR *GetHiiString(EFI_HII_HANDLE Handle, UINT16 *Lang, STRING_REF	Token){
	UINTN			li,hi;
	UINT16			dl[4]={0x20,0x20,0x20,0}, *pdl;
	HII_HANDLE		*phnd;
	HII_STR			*str;
//------------------------------
	phnd=LocateHandle(Handle,&hi);
	if(!phnd) return NULL;

	if(!phnd->HasStr){
		phnd=LocateStrHandleGuid(hi,&hi);
		if(!phnd) return NULL;
	}

	if(!Lang){
		pdl=&dl[0];
		if(EFI_ERROR(GetDefaultLang(pdl)))pdl=(UINT16*)gHiiDb.LangDb.Items[phnd->PriLang];
	} else pdl=Lang;

	//dl has a language string it "   " or "xxx"
	//lang=LocateLang(pdl,&li);
	if(!LocateLang(pdl,&li)) return NULL;
	str=LocateString(phnd,li,Token);

	// If String is not found and language is not specified,
	// let's try with the primary package language.
	if (!str && !Lang) str=LocateString(phnd,0,Token);

	return str;
}


///////////////////////////////////////////////////////////////////
EFI_STATUS HiiGetStringNew(IN EFI_HII_PROTOCOL		*This,
						IN EFI_HII_HANDLE		Handle,
						IN STRING_REF			Token,
						IN BOOLEAN				Raw,
						IN CHAR16				*LanguageString,
						IN OUT UINTN			*BufferLength, //in units of UINT16
						OUT EFI_STRING			StringBuffer)
{
	HII_STR			*str;
	UINTN			j,i;
	UINT16			*ps, sl; 
//--------------------------
	
	if( !This || !BufferLength || *BufferLength && !StringBuffer ) return EFI_INVALID_PARAMETER;

	str=GetHiiString(Handle,LanguageString,Token);
	if(!str) return EFI_INVALID_PARAMETER;

	if(str->NewStr.StrPtr){
		ps=str->NewStr.StrPtr;
		sl=str->NewStr.StrLen;
	} else {
		ps=str->String.StrPtr;
		sl=str->String.StrLen;
	}
	//str->StrLen in UINT16 units
	if(*BufferLength<sl*sizeof(UINT16)) {
		*BufferLength=sl*sizeof(UINT16);
		return EFI_BUFFER_TOO_SMALL;
	}

	if(Raw){
		pBS->CopyMem(&StringBuffer[0],ps,sl*sizeof(UINT16));
		*BufferLength=sl*sizeof(UINT16);
	} else {
		for(i=0,j=0;i<(UINTN)(sl-1);i++){
			//replace <CR> with <Space>
			//if(ps[i]==0x0013) 
			//	StringBuffer[j]=0x0020;	
			//else {
				//skip all Special and Control Characters. 
				if((ps[i]>=0xFFF0 && ps[i]<=0xFFFF))
//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO
//It is amazing how Intel's engineers not in compliance with 
//their own Specs. 
//"If (Raw) TRUE, the string is returned unedited in the internal storage format described
//above. If FALSE, the string returned is edited by replacing !!<cr>!! with <space> and by
//removing special characters such as the ??<wide>?? prefix."
//					||(ps[i]>=0x0000 && ps[i]<=0x001F)) 
//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO
				   continue;
				//Copy the rest of chars
				else StringBuffer[j]=ps[i];
			//}
			j++;
		}
		StringBuffer[j]=0;//Terminate String!!
		*BufferLength=(UINT16)((j+1)*sizeof(UINT16));
	}
	return EFI_SUCCESS;
}

///////////////////////////////////////////////////////////////////
EFI_STATUS HiiGetStringOld(IN EFI_HII_PROTOCOL		*This,
						IN EFI_HII_HANDLE		Handle,
						IN STRING_REF			Token,
						IN BOOLEAN				Raw,
						IN CHAR16				*LanguageString,
						IN OUT UINT16			*BufferLength, //in units of UINT16
						OUT EFI_STRING			StringBuffer)
{
	EFI_STATUS	Status;
	UINTN		bl;
//-----------------
	if(BufferLength==NULL) return EFI_INVALID_PARAMETER;

	bl=(UINTN)(*BufferLength);
	Status=HiiGetStringNew(This,Handle,Token,Raw,LanguageString,&bl,StringBuffer);
	(*BufferLength)=(UINT16)bl;

	if((Status==EFI_BUFFER_TOO_SMALL) && (bl > 0xFFFF)) Status=EFI_INVALID_PARAMETER;
	
	return Status;
}


///////////////////////////////////////////////////////////////////
EFI_STATUS HiiGetLine(IN EFI_HII_PROTOCOL		*This,
					  IN EFI_HII_HANDLE			Handle,
					  IN STRING_REF				Token,
					  IN OUT UINT16				*Index,
					  IN UINT16					LineWidth,
					  IN CHAR16					*LanguageString,
					  IN OUT UINT16				*BufferLength,
					  OUT EFI_STRING			StringBuffer)
{
	HII_STR			*str;
	UINTN			j,i;
	UINT16			*ps, sl; 
	BOOLEAN			cr=FALSE;
//--------------------------
	
	if( !This || !BufferLength || !StringBuffer ) return EFI_INVALID_PARAMETER;
	
	str=GetHiiString(Handle,LanguageString,Token);
	if(!str) return EFI_INVALID_PARAMETER;

	if(str->NewStr.StrPtr){
		ps=str->NewStr.StrPtr;
		sl=str->NewStr.StrLen;
	} else {
		ps=str->String.StrPtr;
		sl=str->String.StrLen;
	}

	//I don't know should I remove a special chars or not 
	// So I will for now 
	for(j=0,i=*Index; (i<sl || i<LineWidth); i++ ){
		//replace <CR> with <Space>
		if(ps[i]==0x0013){
			if(cr) { //if <CR> hit second time in a row - terminate string
				StringBuffer[j]=0x0000;	
				*Index=(UINT16)i;
				break;
			} else { //else replece it with space an set "cr" flag
				StringBuffer[j]=0x0020;
				cr=TRUE;
			}
		}else{
			cr=FALSE; //if we here - reset "cr" flarg 
			//skip all Special and Control Characters. 
			if((ps[i]>=0xFFF0 && ps[i]<=0xFFFF)||(ps[i]<=0x001F)) 
				continue; //will not increase "j" the buffer index
			//Copy the rest of chars into the Buffer
			else 
				StringBuffer[j]=ps[i];
		}
		j++;
	}
	StringBuffer[j]=0;//Terminate String!!
	*BufferLength=(UINT16)((j+1)*sizeof(UINT16));
	return EFI_SUCCESS;
}

///////////////////////////////////////////////////////////////////
EFI_STATUS HiiResetStrings(IN EFI_HII_PROTOCOL			*This,
						   IN EFI_HII_HANDLE			Handle)
{
	HII_STR			*str;
	UINTN			i,hi;//,j,gbi[10],gc=0;
	HII_HANDLE		*phnd;
//------------------------

	if(!This) return EFI_INVALID_PARAMETER;
	phnd=LocateHandle(Handle,&hi);
	if(!phnd) return EFI_INVALID_PARAMETER;
	
	if(!phnd->HasStr){
		phnd=LocateStrHandleGuid(hi,&hi);
		if(!phnd) return EFI_INVALID_PARAMETER;
	}
	//LocateSameGuidHandle(hi, &gbi[0], &gc);

	//for(j=0; j<=gc; j++){
	for(i=0; i<gHiiDb.StringDb.RecordCount;i++){
		//if(!phnd->HasStr) break;
		DbeGoToIndex(&gHiiDb.StringDb,STR_KEY,i,&str);
		if(str->Handle==phnd->Handle){
			if(str->NewStr.StrPtr){
				pBS->FreePool(str->NewStr.StrPtr);
				str->NewStr.StrPtr=NULL;
				str->NewStr.StrLen=0;
				str->NewStr.ScrLen=0;
				//Cleanup Dtabase from RECORDS which was addes
				//after initial Package
				if(!str->String.StrPtr){
					DbeDelete(&gHiiDb.StringDb, str, TRUE);
					i--;//we ned to step on the same data index 
					continue;
					//since we have delited current one
					//phnd->NextStrToken--;
				}
				
			}
		}
		if(str->Handle>phnd->Handle) break;
	}
	phnd->NextStrToken=phnd->StrCount;

	//	if(j<gc)phnd=gHiiDb.HandleDb.Items[gbi[j]];	
	//}
	return EFI_SUCCESS;
}

///////////////////////////////////////////////////////////////////
EFI_STATUS NewStringPack(IN EFI_HII_STRING_PACK	*Package,
						 UINTN					HandleId)
{
	UINTN				i,lid;
	UINT8				*ofs;
	UINT16				*str;
	RELOFST				*ps;//string pointer
	EFI_HII_STRING_PACK	*cp=Package;
	EFI_STATUS			Status=0;
	BOOLEAN				f=TRUE;
	HII_HANDLE		*phnd=(HII_HANDLE*)gHiiDb.HandleDb.Items[HandleId];
//--------------------------------
	while(!IsLastStrPack(cp)){
		ps=(RELOFST*)(cp+1);
		ofs=(UINT8*)cp;
		//Check if Language exists already
		Status=GetLanguageFromPack(cp,&lid);
		if(EFI_ERROR(Status)) return Status;
		if(f){//if this is first string pack make this lang Primary
			phnd->PriLang=(UINT32)lid;
			f=FALSE;
		} else {
			//All other languages if any will be Secondary languages
			Status=LocateSecLangAdd(phnd,&lid,TRUE);
			if(EFI_ERROR(Status)) return Status;
		}

		for(i=0; i<Package->NumStringPointers; i++){
			phnd->NextStrToken=(STRING_REF)i;
			if(!ps[i]) continue;
			str=(UINT16*)(ofs+ps[i]);
			Status=AddString(lid,phnd,str,TRUE,NULL);
			if(EFI_ERROR(Status)) return Status;
		}
		

		cp=(EFI_HII_STRING_PACK*)((UINT8*)cp+cp->Header.Length);
	}
	phnd->StrCount=(STRING_REF)Package->NumStringPointers;
	phnd->HasStr=TRUE;
	return Status;
}


///////////////////////////////////////////////////////////////////
// IFR Releated Functions 
///////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////
//this one will calculate length in bytes for the buffer designed 
//to receive a copy of form instance
//UINT16	GetFormLen(HII_FORM *Form){
//	HII_LABEL	*lbl;
//	UINTN		i;
//	UINT16		len=Form->BufferLength;
//------------------------
//	for(i=0; i<Form->Labels.ItemCount; i++){
//		lbl=Form->Labels.Items[i];
//		if(lbl->Erased) len-=lbl->OrgDataLength;
//		len+=lbl->UpdDataLength;
//	}
//	return len;
//}

///////////////////////////////////////////////////////////////////
//this one will calculate length in bytes for the buffer designed 
//to receive a copy of FormSet instance
//UINT16	GetFormSetLen(HII_FORMSET *FormSet){
//	UINT16		len=0;
//	UINTN		i;
//	HII_FORM	*frm;
//------------------
//	for(i=0; i<FormSet->Forms.ItemCount; i++){
//		frm=FormSet->Forms.Items[i];
//		len+=GetFormLen(frm);
//	}
//	return len+FormSet->FormSetData->Header.Length+FormSet->EndFormSet->Header.Length;
//}

UINTN	GetDataLen(	UINT8 *OpCode, UINTN *Count, BOOLEAN Remove){
	UINTN				i;
	UINTN				len=0;
	UINT8				*p=OpCode;
//------------------------
	for(i=0; i<*Count; i++){
//		if( !Remove && 
//			( (*p)==EFI_IFR_END_FORM_OP || (*p)==EFI_IFR_LABEL_OP )
//		){ 
//			i=i;
//		}
		if( ( Remove && ( (*p)==EFI_IFR_END_FORM_OP || (*p)==EFI_IFR_LABEL_OP )
//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO
	//when adding data I expect that caller knows what he is doing and 
	//passes me correct Data Count. Guess what? This is not TRUE in Intel's Setup.
	//Intel uses Zeroed buffer to fill with desired Opcodes, set Data count to 0xFF and here we go.
	//In this case if in buffer we will found junk which satisfy conditions below
	//we can seriousely scrue up!!!!!
//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO
			  || ((*p)==0 || (*p)>EFI_IFR_VARSTORE_SELECT_PAIR_OP ))){ 
				  *Count=i; 
				  break;
		}
		len = len + ((EFI_IFR_OP_HEADER*)p)->Length;
		p=OpCode+len;
	}
	return len;
}


///////////////////////////////////////////////////////////////////
//this will copy form from HII DB private storage to decignated Buffer
VOID CopyForm(UINT8* Buffer, HII_FORM *Form, UINTN *BytesCnt){
	UINTN		i,cnt=0; 
	HII_LABEL	*lbl=NULL;
	UINT8		*bp=Buffer;
//----------------

	//Now First Label has data starting from opcode next to FORM_OP  
	//and lbl->Label of very first label in the list actualy FORM_OP
	//so don't need following code

	//if(Form->Labels.ItemCount)lbl=(HII_LABEL*)Form->Labels.Items[0];
	//1. copy form till first label (including LABEL OPCODE)
	//if(lbl)//Total Bufferlength including EOF opcode 
	//	cnt=(UINT8*)(lbl->Label)-(UINT8*)Form->FormData;  
	//else 
	//	cnt=Form->BufferLength-Form->EndForm->Header.Length;

	//pBS->CopyMem(bp,Form->FormData,For);
	//bp+=cnt; //Advance buffer pointer;
	//(*BytesCnt)=cnt;
	(*BytesCnt)=0;
	//Keep circling trough Labels copying corresponded data 
	for(i=0;i<Form->Labels.ItemCount;i++){
		lbl=(HII_LABEL*)Form->Labels.Items[i];
		//copy Label OpCode
		pBS->CopyMem(bp,lbl->Label,lbl->Label->Header.Length);
		bp+=lbl->Label->Header.Length;
		(*BytesCnt)+=lbl->Label->Header.Length;

		//if Label was updated copy Update data first...
		if(lbl->LabelData){
			pBS->CopyMem(bp,lbl->LabelData,lbl->DataLength);
			bp+=lbl->DataLength;
			(*BytesCnt)+=lbl->DataLength;
		}
	}
	//Copy EOF opcode
	cnt=Form->EndForm->Header.Length;
	pBS->CopyMem(bp,Form->EndForm,cnt);
	(*BytesCnt)+=cnt;
	return;
}

///////////////////////////////////////////////////////////////////
//will copy entire formset data excluding Pcakage Header
VOID CopyFormSet(UINT8* Buffer, HII_FORMSET *FormSet, UINTN *BytesCnt){
	UINTN		i; 
	UINT8		*bp=Buffer,*pp;
	UINTN		cnt;
	HII_FORM	*frm;
//----------------
	bp=Buffer;
	//Copy Formset OpCode...
	pBS->CopyMem(bp,FormSet->FormSetData,FormSet->FormSetData->Header.Length);
	bp+=FormSet->FormSetData->Header.Length;
	*BytesCnt=FormSet->FormSetData->Header.Length;
	//Copy any information that we might have from end of FormSet Opcode 
	//to the befinning of FOrm OpCode VARSTORE for example.
	if(FormSet->Forms.ItemCount){
		pp=(UINT8*)FormSet->FormSetData+FormSet->FormSetData->Header.Length;
		frm=FormSet->Forms.Items[0];
		cnt=(UINTN)((UINT8*)frm->FormData-pp);
		pBS->CopyMem(bp,pp,cnt);
		bp+=cnt;
		*BytesCnt+=cnt;
	}

	for(i=0; i<FormSet->Forms.ItemCount; i++){
		frm=FormSet->Forms.Items[i];
		CopyForm(bp,frm,&cnt);
		bp+=cnt;
		*BytesCnt+=cnt;
	}
	//copy END_OF_FORM_SET OP here
	cnt=FormSet->EndFormSet->Header.Length;
	pBS->CopyMem(bp,&FormSet->EndFormSet->Header.OpCode,cnt);
	*BytesCnt+=cnt;
	return;
}



///////////////////////////////////////////////////////////////////
//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO
// Cache Form and Formset 
HII_FORM	*LocateForm(HII_FORMSET *FormSet, EFI_FORM_ID FormId){
	EFI_STATUS			Status=0;
	UINTN				fid;
//----------------------------------------------
	Status=LocateItem(&FormSet->Forms,&FormId,sizeof(EFI_FORM_ID),&fid);
	if(EFI_ERROR(Status)) return NULL;

	return (HII_FORM*)FormSet->Forms.Items[fid]; 
}

///////////////////////////////////////////////////////////////////
//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO
// Cache Form and Formset 
HII_FORMSET *LocateFormSet(UINTN HandleIdx, UINTN* FormSetIdx){
	EFI_STATUS			Status=0;
	UINTN				fsid;
//--------------------------
	Status=LocateItem(&gHiiDb.IfrDb,&((UINT32)HandleIdx),sizeof(UINT32),&fsid);
	if(EFI_ERROR(Status)) return NULL; 
	if(FormSetIdx!=NULL)*FormSetIdx=fsid;
	return (HII_FORMSET*)gHiiDb.IfrDb.Items[fsid];
}


HII_LABEL *LocateFormLabel(HII_FORM *Form, EFI_FORM_LABEL LabelId, UINTN *LabelIdx){
	EFI_STATUS			Status=0;
	UINTN				lid;
//----------------------------------------------
	Status=LocateItem(&Form->Labels,&LabelId, sizeof(EFI_FORM_LABEL),&lid);
	if(EFI_ERROR(Status)) return NULL;
		
	*LabelIdx=lid;
	return (HII_LABEL*)Form->Labels.Items[lid]; 
}

HII_LABEL *LocateFormSetLabel(HII_FORMSET *FormSet, EFI_FORM_LABEL LabelId, UINTN *LabelIdx){
	EFI_STATUS			Status=0;
	UINTN				lid;
//----------------------------------------------
	Status=LocateItem(&FormSet->Labels,&LabelId, sizeof(EFI_FORM_LABEL),&lid);
	if(EFI_ERROR(Status)) return NULL;
		
	if(LabelIdx)*LabelIdx=lid;
	return (HII_LABEL*)FormSet->Labels.Items[lid]; 
}


///////////////////////////////////////////////////////////////////
//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO
//This MUST be here to make Shell working 
static UINT8 gDummyVfr[] = {
	//Header 
	0x2c, 0x00, 0x00, 0x00, //Actual Length of Data Buffer
	0x03, 0x00,				//Type;
	// start of IFR data
	/*O*/ 0x0E, //Opcode=EFI_IFR_FORM_SET_OP
	/*L*/ 0x24, //Length
	//Offset=8
	/*G*/ 0xBC, 0x30, 0x0C, 0x9E, 0x06, 0x3F, 0xA6, 0x4B, 0x82, 0x88, 0x09, 0x17, 0x9B, 0x85, 0x5D, 0xBE, //GUID
	/*S*/ 0x02, 0x00, //FormSet Title
	/*S*/ 0x00, 0x00, //Help
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,//Callback
	0x00, 0x00, //Class
	0x00, 0x00, //SubClass
	0x00, 0x00, //NvDataSize
	/*O*/ 0x0D, //OpCOde=EFI_IFR_END_FORM_SET_OP
	/*L*/ 0x02, 
};
//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO
///////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////
EFI_STATUS HiiGetFormsNew(IN EFI_HII_PROTOCOL		*This,
					   IN EFI_HII_HANDLE		Handle,
					   IN EFI_FORM_ID			FormId,
					   IN OUT UINTN             *BufferLength,
					   OUT UINT8				*Buffer)
{
	UINTN				hid;
	HII_FORMSET			*fs;
	HII_FORM			*frm;
	HII_HANDLE			*phnd;
	UINTN				len;
//--------------------------------------
	if(This==NULL && BufferLength==NULL) return EFI_INVALID_PARAMETER;
	//phnd=LocateHandle(Handle, &hid);
	//TODO: Felix: by the HII Spec. we should return EFI_INVALID_PARAMETER
	//However, Intel Device Manager expects EFI_NOT_FOUND
	//(it hangs if it is something else)
	phnd=LocateHandle(Handle, &hid);
	if(!phnd) return EFI_NOT_FOUND;

	fs=LocateFormSet(hid, NULL);
	if(!fs){
		if(!FormId){
		//Technically I must Return NOT_FOUND ERROR but...
//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO
//this patch was made to keep Shell working. Shell and HII coexistance is 
//based on assumption that "It must be some IFR pack associated with String pack"
//If this statement FALSE Shell will hang in INFINITE LOOP!!!!
////////////////////////////////////////////////////////////////////////
//this comments I took from Intel's HII Database Driver
//	"If someone is passing in a string only, create a dummy IfrPack with a Guid 
//	to enable future searching of this data."
////////////////////////////////////////////////////////////////////////
			if(*BufferLength< sizeof(gDummyVfr)) {
				*BufferLength=sizeof(gDummyVfr);
				return EFI_BUFFER_TOO_SMALL;
			}
			*BufferLength=sizeof(gDummyVfr);
			pBS->CopyMem(Buffer,&gDummyVfr[0],sizeof(gDummyVfr));
			//copy handle guid here Shell expect it to mutch with some standart guids
			pBS->CopyMem((VOID*)(Buffer+8),(VOID*)&(phnd->Guid),sizeof(EFI_GUID));
			return EFI_SUCCESS;
		} else return EFI_NOT_FOUND;
//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO
	}

	if(!FormId){//we must return whole FormSet
		//STUPID SHELL expect me to return formset with EFI_HII_PACK_HEADER
		// why? I don't know!
		len=fs->BufferLength+sizeof(EFI_HII_PACK_HEADER);
	} else {
		frm=LocateForm(fs,FormId);
		if(!frm) return EFI_NOT_FOUND;
		len=frm->BufferLength;
	}

	if(*BufferLength<len){
		*BufferLength=len;
		return EFI_BUFFER_TOO_SMALL;
	}
	*BufferLength=len;

	//If "FormId" we must return whole FormSet
	if(!FormId){
		//STUPID SHELL expect me to return formset with EFI_HII_PACK_HEADER
		//Create it
		*((UINT32*)Buffer)=(UINT32)len;
		*((UINT16*)(Buffer+4))=3;//IFR Type
		CopyFormSet(Buffer+6,fs,&hid);
	}
	else 
		CopyForm(Buffer,frm,&hid);

	return	EFI_SUCCESS; 
}

///////////////////////////////////////////////////////////////////
EFI_STATUS HiiGetFormsOld(IN EFI_HII_PROTOCOL		*This,
					   IN EFI_HII_HANDLE		Handle,
					   IN EFI_FORM_ID			FormId,
					   IN OUT UINT16            *BufferLength,
					   OUT UINT8				*Buffer)
{
	EFI_STATUS			Status=0;
	UINTN				bl;
//--------------------------------
	if(BufferLength==NULL) return EFI_INVALID_PARAMETER;

	bl=(UINTN)(*BufferLength);
	Status=HiiGetFormsNew(This,Handle,FormId,&bl,Buffer);
	(*BufferLength)=(UINT16)bl;

	if((Status==EFI_BUFFER_TOO_SMALL) && (bl > 0xFFFF)) Status=EFI_INVALID_PARAMETER;
	return Status;
}


///////////////////////////////////////////////////////////////////
//Will free all memory blocks associated with Label->Objects structures
VOID DeleteLabelObjects(HII_LABEL *Label){
	UINTN		i;
	HII_OBJECT	*obj;
//------------------
	for(i=0;i<Label->Objects.ItemCount; i++){
		obj=Label->Objects.Items[i];
		ClearItemLst(&obj->Conditions,FALSE);
		ClearItemLst(&obj->Options,FALSE);
	}
	ClearItemLst(&Label->Objects,TRUE);
}



///////////////////////////////////////////////////////////////////
EFI_STATUS HiiUpdateForm(IN EFI_HII_PROTOCOL		*This,
						 IN EFI_HII_HANDLE			Handle,
						 IN EFI_FORM_LABEL			Label,
						 IN BOOLEAN					AddData,
						 IN EFI_HII_UPDATE_DATA		*Data)
{
	EFI_STATUS			Status=0;
	UINTN				hid,lid;
	HII_FORMSET			*fs;
	HII_FORM			*frm;
	HII_LABEL			*lbl;
	UINTN				len,cnt;
	UINT8				*ub;
	EFI_IFR_OP_HEADER	*op;
//-------------------------
	if(!This || !Data ) return EFI_INVALID_PARAMETER;

	if(!LocateHandle(Handle, &hid)) return EFI_INVALID_PARAMETER;
	
	//Find Formset
	fs=LocateFormSet(hid, NULL);
	if(!fs) return EFI_INVALID_PARAMETER;
	
	//Find Label
	//FormUpdate= TRUE means just change Form Title!!!
	if(Data->FormUpdate){ 
//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO
//In Intel's HII implementation Data->FormValue field is missing
		//Find Form using UPDATE Data
//		frm=LocateForm(fs,Data->FormValue);
//		if(!frm) return EFI_NOT_FOUND;
		//Update Form Title
//		frm->FormData->FormTitle=Data->FormTitle;
//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO
	}

	//
	if(Data->DataCount){
		//Find Label
		lbl=LocateFormSetLabel(fs, Label, &lid);
		if(!lbl) return EFI_NOT_FOUND;	
		frm=lbl->OwnerForm;
		cnt=Data->DataCount;
		if(AddData){
			op=(EFI_IFR_OP_HEADER*)&Data->Data;
			if(!op->OpCode || !op->Length) return EFI_INVALID_PARAMETER;
			//Calculate size of UPDATE data
			len=GetDataLen((UINT8*)op,&cnt,FALSE);
			ub=Malloc(len+lbl->DataLength);
			if(!ub) return EFI_OUT_OF_RESOURCES;
		
//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO
			//Copy Update Data in Private Buffer
			pBS->CopyMem(ub,op,len);	
			//Copy Old Data in same Private Buffer
			if(lbl->LabelData)pBS->CopyMem((VOID*)(ub+len),lbl->LabelData,lbl->DataLength);
//for coimpatibility with Intel's setup I've change order in which the chanks of opcodes
// been copied in a new label buffer - New data will be added after the old data
			//if(lbl->LabelData)pBS->CopyMem(ub,lbl->LabelData,lbl->DataLength);
			//pBS->CopyMem((VOID*)(ub+lbl->DataLength),op,len);	
//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO

			//Update Buffer parameters in every structure affected by update
			lbl->DataLength = lbl->DataLength + len;
			lbl->DataCount = lbl->DataCount + Data->DataCount;
			if(lbl->Updated && lbl->LabelData)pBS->FreePool(lbl->LabelData);
			lbl->LabelData=(EFI_IFR_OP_HEADER*)ub;
			fs->BufferLength = fs->BufferLength + len;
			frm->BufferLength = frm->BufferLength + len;
			//Delete Old Data
			DeleteLabelObjects(lbl);
		}else{
			//we will not erase an empty Label!
			if(lbl->LabelData){
				op=lbl->LabelData;
				if(Data->DataCount>=lbl->DataCount){
					cnt=lbl->DataCount;
					len=lbl->DataLength;
				} else len=GetDataLen((UINT8*)op,&cnt,TRUE);
				
				//if after erasing no data has left, no need to allocate new buffer 
				if((INTN)(lbl->DataLength-len)>0){
					ub=Malloc(lbl->DataLength-len);	
					if(!ub) 
						return EFI_OUT_OF_RESOURCES;
					//Copy rest of Old Data in Private Buffer
					pBS->CopyMem(ub,(UINT8*)lbl->LabelData+len,lbl->DataLength-len);
				} else ub=NULL;
										
				//Update Buffer parameters in every structure affected by update
				lbl->DataLength = lbl->DataLength - len;
				lbl->DataCount = lbl->DataCount - cnt;
				if(lbl->Updated && lbl->LabelData)pBS->FreePool(lbl->LabelData);
				lbl->LabelData=(EFI_IFR_OP_HEADER*)ub;
				fs->BufferLength = fs->BufferLength - len;
				frm->BufferLength = frm->BufferLength - len;
				DeleteLabelObjects(lbl);
			}
		}
		//Populate pointers on Label Objects from Label Dtat Buffer
		if(lbl->LabelData!=NULL)Status=CreateLabelObjects(lbl);
		if(EFI_ERROR(Status))return Status;
		lbl->Updated=TRUE;

		if(lbl->UpdateCallBack)	lbl->UpdateCallBack(Label, Handle,AddData);			
	}

	if(Data->FormSetUpdate){
		fs->FormSetData->CallbackHandle=Data->FormCallbackHandle;
	}
	
	return EFI_SUCCESS;
}

EFI_STATUS InitDefStorage(HII_FORMSET *FormSet){
	EFI_STATUS			Status;
	HII_STORE			*st;
	static CHAR8		*ss="Setup";//{'S','e','t','u','p',0};
	CHAR8				*pn;//pointer to var name;
//------------------------------------------------
	st=MallocZ(sizeof(HII_STORE));
	if(!st)return EFI_OUT_OF_RESOURCES;

	Status=AppendItemLst(&FormSet->Storages,st);

	st->VarStore=MallocZ(sizeof(EFI_IFR_VARSTORE)+6);
	if(!st->VarStore)return EFI_OUT_OF_RESOURCES;
	
	//Init Default VarStore Structure VarId is Always 0x0000
	st->VarStore->Header.Length=sizeof(EFI_IFR_VARSTORE)+6;
	st->VarStore->Header.OpCode=EFI_IFR_VARSTORE_OP;
	st->VarStore->Size=FormSet->FormSetData->NvDataSize;

	//Copy formset GUID here 
	pBS->CopyMem(&st->VarStore->Guid,&FormSet->FormSetData->Guid,sizeof(EFI_GUID));
	
	pn=(CHAR8*)st->VarStore;
	pn+=sizeof(EFI_IFR_VARSTORE);
	pBS->CopyMem(pn,ss,6);

	return EFI_SUCCESS;
}

//Selects Var Store Object
HII_STORE *LocateStorage(HII_FORMSET *FormSet, UINT16 VarId, UINTN *StoreId OPTIONAL){
	UINTN		i;
	HII_STORE	*st;
//---------------------
	for(i=0; i<FormSet->Storages.ItemCount; i++){
		st=(HII_STORE*)FormSet->Storages.Items[i];
		if(st->VarStore->VarId==VarId) {
			if(StoreId)*StoreId=i;
			return st;
		}
	}
	return NULL;
}


EFI_STATUS CreateLabelObjects(HII_LABEL *Label)
{
	EFI_IFR_OP_HEADER	*op;
	UINTN				i,j=0, k;
	HII_OBJECT			*obj=NULL;
	HII_STORE			*st1=NULL, *st2=NULL;
	static T_ITEM_LIST	clst={0,0,NULL},olst={0,0,NULL};	//temp conditions and objects list list 
    static T_ITEM_LIST  supprstores = {0, 0, NULL};
	EFI_STATUS			Status;
	BOOLEAN				cf=FALSE;	//conditions flag
    BOOLEAN             Suppress = FALSE;
//-------------------------------------------
	op=Label->LabelData;

	obj=NULL;
	//st1=(HII_STORE*)Label->OwnerForm->Owner->Storages.Items[0];
    st1 = LocateStorage(Label->OwnerForm->Owner, CurrentVarId, NULL);
    if(!st1) { st1=(HII_STORE*)Label->OwnerForm->Owner->Storages.Items[0]; CurrentVarId = 0; }
	st2=NULL;
	for(i=0;i<Label->DataCount;i++){
		//Select Default Storage so Store1
		switch(op->OpCode){
			//Storage Select Opcodes
			case EFI_IFR_VARSTORE_SELECT_OP:
			{
				EFI_IFR_VARSTORE_SELECT	*vs=(EFI_IFR_VARSTORE_SELECT*)op;
				HII_STORE				*st=LocateStorage(Label->OwnerForm->Owner,vs->VarId,NULL);
                // preserve the varstore selection - to be reset only by the next varstore select
                // or a new formset
			//------------------------
				if(st) { st1=st; CurrentVarId = vs->VarId; }
			}	
			break;
			case EFI_IFR_VARSTORE_SELECT_PAIR_OP:
			{
				EFI_IFR_VARSTORE_SELECT_PAIR	*v2=(EFI_IFR_VARSTORE_SELECT_PAIR*)op;
				HII_STORE				*s1=LocateStorage(Label->OwnerForm->Owner,v2->VarId,NULL);
				HII_STORE				*s2=LocateStorage(Label->OwnerForm->Owner,v2->SecondaryVarId,NULL);
				//------------------------
				if(s1) { st1=s1; CurrentVarId = v2->VarId; }
				if(s2) st2=s2; 
			}
			break;
			//Condition OpCodes
			case EFI_IFR_GRAYOUT_IF_OP:
			case EFI_IFR_SUPPRESS_IF_OP:
			case EFI_IFR_INCONSISTENT_IF_OP:
				//if we found some logical expression and local ovject list(olst) has some objects 
				//we must add this objects with no conditions to the Label->Objects list
				//and clear local object list to start fill it with objects who has conditions.
				if(!cf){
					for(j=0;j<olst.ItemCount;j++){
						obj=olst.Items[j];
						Status=AppendItemLst(&Label->Objects,obj);
						ASSERT(!EFI_ERROR(Status));
						if(EFI_ERROR(Status)) return Status;
					}
					ClearItemLst(&olst,FALSE);
					obj=NULL;
				}
				cf=TRUE;
                if( op->OpCode == EFI_IFR_SUPPRESS_IF_OP) Suppress = TRUE;
                else Suppress = FALSE;
			///////////////////////////////////////////////////////////////////////
			//Do not add break instruction  here it is not present for a reason!!!!
			///////////////////////////////////////////////////////////////////////
			case EFI_IFR_AND_OP:
			case EFI_IFR_OR_OP:
			case EFI_IFR_NOT_OP:
			case EFI_IFR_EQ_ID_VAL_OP: 
			case EFI_IFR_EQ_ID_ID_OP:
			case EFI_IFR_EQ_ID_LIST_OP:	
			case EFI_IFR_EQ_VAR_VAL_OP:
				//Add Opcode to the temp Condition list;
				Status=AppendItemLst(&clst,op);
				ASSERT(!EFI_ERROR(Status));
				if(EFI_ERROR(Status)) return Status;//out of resources

                if(op->OpCode == EFI_IFR_EQ_ID_VAL_OP && Suppress)
                {
                    Status = AppendItemLst(&supprstores, st1);
                    ASSERT(!EFI_ERROR(Status));
                }
			break;
			//end of conditions OpCode
			case EFI_IFR_END_IF_OP:
				//this is definetely end of object presentation,
				//but some times it might be no object to add conditions info to
				if(!olst.ItemCount){
					for(j=0; j<clst.ItemCount;j++) {
						Status=AppendItemLst(&Label->Conditions,clst.Items[j]);
						ASSERT(!EFI_ERROR(Status));
						if(EFI_ERROR(Status)) return Status;
					}
				}
				for(j=0;j<olst.ItemCount;j++){
					obj=olst.Items[j];
					//I'm trying to allocate exactly as mutch memory as I need for Conditions.Items[] array.
					//If you initialize ItemList.InitialCount with some specific value>0, then next call to 
					//Append ItemLst function will allocate this number of entries for ItemList.Items[] Array.
					obj->Conditions.InitialCount=clst.ItemCount;
					Status=AppendItemLst(&obj->Conditions,clst.Items[0]);
					ASSERT(!EFI_ERROR(Status));
					if(EFI_ERROR(Status)) return Status;
					pBS->CopyMem(&obj->Conditions.Items[1],&clst.Items[1],sizeof(VOID*)*(clst.ItemCount-1));
					obj->Conditions.ItemCount=clst.ItemCount;
                    for(k = 0; k < supprstores.ItemCount; k++)
                    {
                        Status=AppendItemLst(&obj->SuppressStores,supprstores.Items[k]);
						ASSERT(!EFI_ERROR(Status));
						if(EFI_ERROR(Status)) return Status;
                    }
                    
					Status=AppendItemLst(&Label->Objects,obj);
					ASSERT(!EFI_ERROR(Status));
					if(EFI_ERROR(Status)) return Status;
				}
				ClearItemLst(&clst,FALSE); //don't need to free data - it's VFR pointers!
				ClearItemLst(&olst,FALSE); 
                ClearItemLst(&supprstores,FALSE);
				obj=NULL;
				cf=FALSE;
                Suppress = FALSE;
			break;
			//visual opcodes
			case EFI_IFR_SUBTITLE_OP:
			case EFI_IFR_TEXT_OP:
			case EFI_IFR_INVENTORY_OP:
			case EFI_IFR_GRAPHIC_OP:
			case EFI_IFR_CHECKBOX_OP:
			case EFI_IFR_NUMERIC_OP:
			case EFI_IFR_PASSWORD_OP:
			case EFI_IFR_REF_OP:
			case EFI_IFR_DATE_OP:
			case EFI_IFR_TIME_OP:
			case EFI_IFR_STRING_OP:
			case EFI_IFR_SAVE_DEFAULTS_OP:
			case EFI_IFR_RESTORE_DEFAULTS_OP:
			case EFI_IFR_HIDDEN_OP:
			//continiouse 
			case EFI_IFR_ONE_OF_OP:
			case EFI_IFR_ORDERED_LIST_OP:
				ASSERT(!obj); //obj pointer must be cleared when we enter there
				if(obj)return EFI_INVALID_PARAMETER; 
				obj=MallocZ(sizeof(HII_OBJECT));
				ASSERT(obj);//Allocation Problems!
				if(!obj) return EFI_OUT_OF_RESOURCES;
				obj->ObjectCode=op;
				obj->Store1=st1;
				obj->Store2=st2;
				Status=AppendItemLst(&olst,obj);	
				ASSERT(!EFI_ERROR(Status));
				if(EFI_ERROR(Status)) return Status;
				//in case of DATE or Time opcode advance by 2 opcodes
				if(op->OpCode==EFI_IFR_TIME_OP || op->OpCode==EFI_IFR_DATE_OP){
					op=(EFI_IFR_OP_HEADER*)((UINT8*)op+op->Length);
					op=(EFI_IFR_OP_HEADER*)((UINT8*)op+op->Length);
					i+=2;
				}
				obj=NULL;
			break;
			case EFI_IFR_ONE_OF_OPTION_OP:
				ASSERT(olst.ItemCount);
				if(!olst.ItemCount)	return EFI_INVALID_PARAMETER;
				obj=(HII_OBJECT*)olst.Items[olst.ItemCount-1];
				if(!obj) return EFI_INVALID_PARAMETER; //obj must be allocated!
				Status=AppendItemLst(&obj->Options,op);
				ASSERT(!EFI_ERROR(Status));
				if(EFI_ERROR(Status)) return Status;//out of resources
			break;
			case EFI_IFR_END_ONE_OF_OP:					
				obj=NULL;
			break;

		}//end switch;
		//Advance to next opcode
		op=(EFI_IFR_OP_HEADER*)((UINT8*)op+op->Length);
	}
	//If there were no any Condition Opcodes contents of the ObjectList(olst) was not copied to the Label.Objects
	for(j=0;j<olst.ItemCount;j++){
		obj=olst.Items[j];
		Status=AppendItemLst(&Label->Objects,obj);
		ASSERT(!EFI_ERROR(Status));
		if(EFI_ERROR(Status)) return Status;
	}
	ClearItemLst(&olst,FALSE); 
	return EFI_SUCCESS;
}

//This Routine is called to parse FormVfr and Create Objects which must be shown on the screen;
EFI_STATUS CreateFormObjects(HII_FORM *Form){
	UINTN		i;
	EFI_STATUS	Status = EFI_SUCCESS;
//---------------------------------
	
	for(i=0; i<Form->Labels.ItemCount; i++){
		Status=CreateLabelObjects((HII_LABEL*)Form->Labels.Items[i]);		
		ASSERT(!EFI_ERROR(Status));
		if(EFI_ERROR(Status))return Status;
	}
	return Status;
}

EFI_STATUS NewKbdPack(EFI_HII_KEYBOARD_PACK	*Package,
					  UINTN				HandleId)
{
	EFI_STATUS			Status;
	HII_KB_LAYOUT_DATA	*kbld;	
//--------------------
	//Get Some Memory to accomodate Kb Layout Buffer	
	kbld=Malloc(sizeof(EFI_KEY_DESCRIPTOR)*Package->DescriptorCount+sizeof(HII_KB_LAYOUT_DATA));
	ASSERT(kbld);
	if(kbld==NULL) return EFI_OUT_OF_RESOURCES;

	kbld->HandleIndex=HandleId; //just in case to find HII_HANDLE structure assotiated with this PACK
	kbld->KeyDscCount=Package->DescriptorCount;
	//We will store KB Layout Data right after the HII_KB_LAYOUT_DATA structure itself
	kbld->KeyDsc=(EFI_KEY_DESCRIPTOR*)(kbld+1);
	MemCpy((VOID*)kbld->KeyDsc, (VOID*)Package->Descriptor, sizeof(EFI_KEY_DESCRIPTOR)*kbld->KeyDscCount);	
	
	//Add saved KB Layout Data to the HII DB 
	Status=AppendItemLst((T_ITEM_LIST*)&gHiiDb.KeybdDb.KblInitCount,(VOID*)kbld); 
	ASSERT_EFI_ERROR(Status);

	//Set recently submitted KB Layout as the current one
	gHiiDb.KeybdDb.ActiveLayout=gHiiDb.KeybdDb.KblCount-1;

	return Status;
}

EFI_STATUS NewIfrPack(EFI_HII_IFR_PACK	*Package,
					  UINTN				HandleId)
{
	EFI_STATUS			Status;
	EFI_IFR_OP_HEADER	*op;
//	INT32				id=0;
	HII_FORM			*cf=NULL;
	HII_FORMSET			*cfs=NULL;
	HII_LABEL			*cl=NULL;
	HII_STORE			*st=NULL;
	HII_HANDLE			*phnd=(HII_HANDLE*)gHiiDb.HandleDb.Items[HandleId];
	UINT8				*p;
	BOOLEAN				la=FALSE;//label active flag - helps count OPCODES and Label.dLength
//---------------------------------------------
	//Copy Data to a new Storage =(EFI_IFR_OP_HEADER*)(Package+1);
	p=Malloc(Package->Header.Length);
	if(!p) return EFI_OUT_OF_RESOURCES;
	pBS->CopyMem(p,Package,Package->Header.Length);

	op=(EFI_IFR_OP_HEADER*)(p+sizeof(EFI_HII_PACK_HEADER));
	//Parse IFR and crete Working set of data 
	//Every IFR Pack must start from FORM_SET_OP
	while(/*(op->OpCode!=EFI_IFR_END_FORM_SET_OP)||*/((UINTN)op<((UINTN)p)+Package->Header.Length)){
		switch (op->OpCode){
			//Take care of Forms Sets
			case EFI_IFR_FORM_SET_OP:
                CurrentVarId = 0;
				cfs=MallocZ(sizeof(HII_FORMSET));
				if(!cfs) return EFI_OUT_OF_RESOURCES;
				//cfs->BufferLength=0; it is 0 
				cfs->FormSetData=(EFI_IFR_FORM_SET*)op;
				cfs->HandleId=(UINT32)HandleId;
				cfs->Handle=phnd->Handle;
				//Setup Initial Storage var 
				Status=InitDefStorage(cfs);
				if(EFI_ERROR(Status)) return Status;
			break;
			case EFI_IFR_VARSTORE_OP:
				if(!cfs) return EFI_INVALID_PARAMETER; 
				st=MallocZ(sizeof(HII_STORE));
				if(!st) return EFI_OUT_OF_RESOURCES;
				Status=AppendItemLst(&cfs->Storages,st);
				st->VarStore=(EFI_IFR_VARSTORE*)op;
			break;
			case EFI_IFR_END_FORM_SET_OP:
				if(!cfs)return EFI_INVALID_PARAMETER; //found EFI_IFR_END_FORM_SET_OP without EFI_IFR_FORM_SET_OP
				//cfs->BufferLength=(UINT16)((UINT8*)op+op->Length-(UINT8*)cfs->FormSetData);
                CurrentVarId = 0;
				cfs->EndFormSet=(EFI_IFR_END_FORM_SET*)op;
				cfs->HandleId=(UINT32)HandleId;
				cfs->BufferLength = cfs->BufferLength + op->Length;
				Status=AppendItemLst(&gHiiDb.IfrDb,(VOID*)cfs);
				if(EFI_ERROR(Status)) return Status;
				cfs=NULL;
			break;
			//Take care of Forms and Labels
			case EFI_IFR_FORM_OP:
			case EFI_IFR_LABEL_OP:
			{	
				EFI_IFR_OP_HEADER	*nxt;
			//----------------------------
				if(op->OpCode==EFI_IFR_FORM_OP){
					//it must be some FORM_SET OpCode before we met FORM OpCode
					if(!cfs) return EFI_INVALID_PARAMETER; 
					cf=MallocZ(sizeof(HII_FORM));
					if(!cf) return EFI_OUT_OF_RESOURCES;
					//cf->BufferLength=0; 
					cf->FormData=(EFI_IFR_FORM*)op;
					cf->FormId=cf->FormData->FormId;
					cf->Owner=cfs;
				}
				if(!cf && !cfs )return EFI_INVALID_PARAMETER; //Form mus be present
				cl=MallocZ(sizeof(HII_LABEL));
				if(!cl) return EFI_OUT_OF_RESOURCES;

				cl->OwnerForm=cf;
				cl->Label=(EFI_IFR_LABEL*)op;
				//it must be a valid opcode next...
				nxt=(EFI_IFR_OP_HEADER*)((UINT8*)op+op->Length);
				if(nxt->OpCode!=EFI_IFR_END_FORM_OP && nxt->OpCode!=EFI_IFR_LABEL_OP)cl->LabelData=nxt;
			
				if(op->OpCode==EFI_IFR_FORM_OP){
					cl->LabelId=0xFACE; //Fake LabelID
				} else {
					cl->LabelId=cl->Label->LabelId;
					Status=AppendItemLst(&cfs->Labels,cl);
					if(EFI_ERROR(Status)) return Status;
				}
	
				Status=AppendItemLst(&cf->Labels,cl);
				if(EFI_ERROR(Status)) return Status;

				la=TRUE;
			}
			break;
			case EFI_IFR_END_FORM_OP:
				if(!cf)return EFI_INVALID_PARAMETER; //found EFI_IFR_END_FORM_OP without EFI_IFR_FORM_OP
				//cf->BufferLength=(UINT16)((UINT8*)op+op->Length-(UINT8*)cf->FormData);
				cf->EndForm=(EFI_IFR_END_FORM*)op;
				cf->BufferLength = cf->BufferLength + op->Length;
				Status=AppendItemLst(&cfs->Forms,cf);
				if(EFI_ERROR(Status)) return Status;
				Status=CreateFormObjects(cf);
				cf=NULL;
				la=FALSE;
			break;
			//Labels Has Left
			/*case EFI_IFR_LABEL_OP:{
				EFI_IFR_OP_HEADER	*nxt;
			//---------------------------
				if(!cf && !cfs )return EFI_INVALID_PARAMETER; //Form mus be present
				cl=MallocZ(sizeof(HII_LABEL));
				if(!cl) return EFI_OUT_OF_RESOURCES;

				cl->Label=(EFI_IFR_LABEL*)op;
				cl->LabelId=cl->Label->LabelId;
				cl->OwnerForm=cf;
				nxt=(EFI_IFR_OP_HEADER*)(cl->Label+1);
				//it must be a valid opcode next...
				if(nxt->OpCode!=EFI_IFR_END_FORM_OP && nxt->OpCode!=EFI_IFR_LABEL_OP)cl->LabelData=nxt;

				Status=AppendItemLst(&cf->Labels,cl);
				if(EFI_ERROR(Status)) return Status;

				Status=AppendItemLst(&cfs->Labels,cl);
				if(EFI_ERROR(Status)) return Status;
				la=TRUE;
				break;
				}
			*/
			default :
				if(la){
					cl->DataCount++;
					cl->DataLength = cl->DataLength + op->Length;
				}
		} //Switch
		if(cfs)cfs->BufferLength = cfs->BufferLength + op->Length;
		if(cf)cf->BufferLength = cf->BufferLength + op->Length;
		op=(EFI_IFR_OP_HEADER*)((UINT8*)op+op->Length);
	}
	phnd->Ifr=p;
	return EFI_SUCCESS;
}

///////////////////////////////////////////////////////////////////
// Common Interface functions
///////////////////////////////////////////////////////////////////
EFI_STATUS HiiNewPackNew(IN EFI_HII_PROTOCOL	*This,
						 IN  EFI_HII_PACKAGES    *Packages,
						 OUT EFI_HII_HANDLE      *Handle)
{
	UINTN				i;
	EFI_HII_PACK_HEADER	*hdr, **hdrptr;
	EFI_STATUS			Status=0;
	UINTN				c=0,hid=0;
	HII_HANDLE			*phnd=NULL;
	BOOLEAN 			sp=0,vp=0,hp=0;
//-----------------------------------------
	if(!This) return EFI_INVALID_PARAMETER;
		
	hdrptr=(EFI_HII_PACK_HEADER**)(Packages+1);
	for(i=0; i<Packages->NumberOfPackages; i++){
		hdr=hdrptr[i];
		switch(hdr->Type){
			case EFI_HII_FONT:
				Status=NewFontPack((EFI_HII_FONT_PACK*)hdr); 
				if(EFI_ERROR(Status)) return Status;
			break;
			case EFI_HII_STRING:
				if(sp)return EFI_INVALID_PARAMETER;
				phnd=LocateHandleGuid(Packages->GuidId,&hid);
//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO
//this is wrong !!! 
		//here we are trying to check if somebody using passed GuidId registered Ifr with us 
		//it should not be like this but Intel's Setup Browser uses same GuidId sor 2 different 
		//Ifr instances. To maintain compatibility I'll try to patch code...
				if(!phnd || phnd->HasStr){
//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO
					Status=LocateHandleAdd(gHiiDb.NextHiiHandle,Packages->GuidId,&hid);
					if(Status) return Status;		
					else c++;
					phnd=gHiiDb.HandleDb.Items[hid];
				}
				Status=NewStringPack((EFI_HII_STRING_PACK*)hdr, hid); 
				if(EFI_ERROR(Status)) return Status;
				sp=TRUE;
			break;
			case EFI_HII_IFR:
				if(vp)return EFI_INVALID_PARAMETER;
				phnd=LocateHandleGuid(Packages->GuidId,&hid);
//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO
//this is wrong !!!//same goes gor IFR 
				if(!phnd || phnd->Ifr){
//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO
					Status=LocateHandleAdd(gHiiDb.NextHiiHandle,Packages->GuidId,&hid);
					if(Status) return Status;		
					else c++;
					phnd=gHiiDb.HandleDb.Items[hid];
				}
		
				Status=NewIfrPack((EFI_HII_IFR_PACK*)hdr, hid); 
				if(EFI_ERROR(Status)) return Status;
				vp=TRUE;
			break;
			case EFI_HII_KEYBOARD:
				Status=NewKbdPack((EFI_HII_KEYBOARD_PACK*)hdr, hid);
			break;
			case EFI_HII_HANDLES:
				if(hp)return EFI_INVALID_PARAMETER;
//TODO			
				hp=TRUE;	
			break;
			case EFI_HII_VARIABLE:
//TODO			
			break;
			case EFI_HII_DEVICE_PATH:
//TODO
			break;
			default: return EFI_INVALID_PARAMETER;
		}//switch
	}
	if(c)gHiiDb.NextHiiHandle++;

	if(phnd)*Handle=phnd->Handle;
	else *Handle=0;

	return Status; 
}

EFI_STATUS HiiNewPackOld (IN EFI_HII_PROTOCOL	*This,
					IN EFI_HII_PACK_LIST	*Package,
					OUT EFI_HII_HANDLE		*Handle)
{
	EFI_STATUS			Status=0;
	UINTN				c=0,hid;
	HII_HANDLE			*phnd=NULL;
//----------------------------------
	if(!This) return EFI_INVALID_PARAMETER;

	//Check if we have this GUID ib GuidDb already 
	//For Font and Keyboadr Data HAndle is allways = 0  	
	if(Package->FontPack) Status=NewFontPack(Package->FontPack); 
	if(EFI_ERROR(Status)) return Status;

	if(Package->StringPack){
		phnd=LocateHandleGuid(Package->GuidId,&hid);
//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO
//this is wrong !!! 
		//here we are trying to check if somebody using passed GuidId registered Ifr with us 
		//it should not be like this but Intel's Setup Browser uses same GuidId sor 2 different 
		//Ifr instances. To maintain compatibility I'll try to patch code...
		if(!phnd || phnd->HasStr){
//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO
//		if(!phnd){
			Status=LocateHandleAdd(gHiiDb.NextHiiHandle,Package->GuidId,&hid);
			if(Status) return Status;		
			else c++;
			phnd=gHiiDb.HandleDb.Items[hid];
		}

		//if(phnd->HasStr) return EFI_INVALID_PARAMETER;
		Status=NewStringPack(Package->StringPack, hid); 
		if(EFI_ERROR(Status)) return Status;
	}

	if(Package->IfrPack){
		phnd=LocateHandleGuid(Package->GuidId,&hid);
//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO
//this is wrong !!! 
		//here we are trying to check if somebody using passed GuidId registered Ifr with us 
		//it should not be like this but Intel's Setup Browser uses same GuidId sor 2 different 
		//Ifr instances. To maintain compatibility I'll try to patch code...
		if(!phnd || phnd->Ifr){
//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO
//		if(!phnd){
			Status=LocateHandleAdd(gHiiDb.NextHiiHandle,Package->GuidId,&hid);
			if(Status) return Status;		
			else c++;
			phnd=gHiiDb.HandleDb.Items[hid];
		}
		
		//if(phnd->HasIfr) return EFI_INVALID_PARAMETER;
		Status=NewIfrPack(Package->IfrPack, hid); 
		if(EFI_ERROR(Status)) return Status;
	}
//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO
//nothing is done for keyboard layout functions 
//this is empty spot in spec!
//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO
	if(c)gHiiDb.NextHiiHandle++;

	if(phnd)*Handle=phnd->Handle;
	else *Handle=0;

	return Status; 
}

///////////////////////////////////////////////////////////////////
//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO
//this function even not in spec yet so UNSUPPORT it!!!
// here is an explanation I've got from Initial's Source 
//  "This function allows to extract the NV Image 
//  that represents the default storage image"
//Still Unclear what to do with it
EFI_STATUS HiiGetDefaultImageOld(IN EFI_HII_PROTOCOL		*This,
							  IN EFI_HII_HANDLE			Handle,
							  IN UINTN					DefaultMask,
							  IN OUT UINT16             *BufferLength,
							  IN OUT UINT8              *Buffer)
{
	HII_HANDLE			*phnd;
	HII_FORMSET			*fs;
	EFI_IFR_OP_HEADER	*op;
	UINTN				hi,fsi,i,t=0,cv=0;
	UINT8				*fsb;//formset buffer
	BOOLEAN				ol=FALSE; 
	EFI_STATUS			Status;
//---------------------------------
	if(!This) return EFI_INVALID_PARAMETER;
	
	phnd=LocateHandle(Handle,&hi);
	if(!phnd || !phnd->Ifr) return EFI_INVALID_PARAMETER;
	
	fs=LocateFormSet(hi,&fsi);
	if(!fs) return EFI_INVALID_PARAMETER;

	if(*BufferLength<fs->FormSetData->NvDataSize){
		*BufferLength=fs->FormSetData->NvDataSize;
		return EFI_BUFFER_TOO_SMALL;
	}
	*BufferLength=fs->FormSetData->NvDataSize;
	i=*BufferLength;

	if (DefaultMask & EFI_IFR_FLAG_DEFAULT) 
		Status=pRS->GetVariable(L"SetupDefaultOverride",&phnd->Guid,NULL,&i,Buffer);
	else {
		if (DefaultMask & EFI_IFR_FLAG_MANUFACTURING) 
            Status=pRS->GetVariable(L"SetupManufacturingOverride",&phnd->Guid,NULL,&i,Buffer);
		else {
			DefaultMask = DefaultMask | EFI_IFR_FLAG_DEFAULT;
			Status=pRS->GetVariable(L"Setup",&phnd->Guid,NULL,&i,Buffer);
		}
	}
	
	fsb=Malloc(fs->BufferLength);
	if(!fsb) return EFI_OUT_OF_RESOURCES;
	CopyFormSet(fsb,fs,&i);

	op=(EFI_IFR_OP_HEADER*)fsb;
	while(op->OpCode!=EFI_IFR_END_FORM_SET_OP){
		switch(op->OpCode){
			case EFI_IFR_ORDERED_LIST_OP:
				ol=TRUE;
				i=((EFI_IFR_ONE_OF*)op)->QuestionId;
				t=((EFI_IFR_ONE_OF*)op)->Width;
				break;
			case EFI_IFR_ONE_OF_OP:
				ol=FALSE;
				i=((EFI_IFR_ONE_OF*)op)->QuestionId;
				t=((EFI_IFR_ONE_OF*)op)->Width;
				break;
			case EFI_IFR_ONE_OF_OPTION_OP:{
				EFI_IFR_ONE_OF_OPTION	*ifro=(EFI_IFR_ONE_OF_OPTION*)op;
			//-----------------
				if(!cv){ 
					if(ol){
						//pBS->CopyMem(&Buffer[i],&((EFI_IFR_ONE_OF_OPTION*)op)->Value, 1);
						pBS->CopyMem(&Buffer[i],&ifro->Value, 1);	
						i++;
					} else {
						//if (((EFI_IFR_ONE_OF_OPTION*)op)->Flags & DefaultMask) 
						//	pBS->CopyMem(&Buffer[i],&((EFI_IFR_ONE_OF_OPTION*)op)->Value,t);
						if (ifro->Flags & DefaultMask) 
							pBS->CopyMem(&Buffer[i],&ifro->Value,t);
            		}
				} 
			} break;
			case EFI_IFR_END_OP:
				t=0;
				break;
			case EFI_IFR_CHECKBOX_OP:{
				EFI_IFR_CHECK_BOX *ifrc=(EFI_IFR_CHECK_BOX*)op;
			//--------------------
				if(!cv){
					//if(((EFI_IFR_CHECK_BOX*)op)->Flags & DefaultMask)
					//	Buffer[((EFI_IFR_CHECK_BOX*)op)->QuestionId] = 1;
					//else
					//	Buffer[((EFI_IFR_CHECK_BOX*)op)->QuestionId] = 0;
					if(ifrc->Flags & DefaultMask)
						Buffer[ifrc->QuestionId] = 1;
					else
						Buffer[ifrc->QuestionId] = 0;
				}
			} break;
			case EFI_IFR_NUMERIC_OP:{
				EFI_IFR_NUMERIC *ifrn=(EFI_IFR_NUMERIC*)op;
			//--------------------------
		    	//if (!cv)pBS->CopyMem(&Buffer[((EFI_IFR_NUMERIC*)op)->QuestionId],
				//		&((EFI_IFR_NUMERIC*)op)->Default,((EFI_IFR_NUMERIC*)op)->Width);
		        if (!cv){
					pBS->CopyMem(&Buffer[ifrn->QuestionId],	&ifrn->Default,ifrn->Width);
				}
			} break;
			
			case EFI_IFR_VARSTORE_SELECT_OP:
			case EFI_IFR_VARSTORE_SELECT_PAIR_OP:
				cv=((EFI_IFR_VARSTORE_SELECT*)op)->VarId;
			break;
		}
		op=(EFI_IFR_OP_HEADER*)((UINT8*)op+op->Length);
	}
	pBS->FreePool(fsb);
	return EFI_SUCCESS;
}
///////////////////////////////////////////////////////////////////
EFI_STATUS HiiFindHandles(IN EFI_HII_PROTOCOL	*This,
						  //spec not says in what units assume, for now, it is in EFI_HII_HANDLE
						  IN OUT UINT16			*HandleBufferLength,
						  OUT EFI_HII_HANDLE	*Handle)
{
	UINTN				i;
	HII_HANDLE			*hnd;
//-------------------------------
	if(!This) return EFI_INVALID_PARAMETER;

	if(*HandleBufferLength<gHiiDb.HandleDb.ItemCount*sizeof(EFI_HII_HANDLE)){
		*HandleBufferLength = (UINT16)gHiiDb.HandleDb.ItemCount*sizeof(EFI_HII_HANDLE);
 		return EFI_BUFFER_TOO_SMALL;
	}
	*HandleBufferLength = (UINT16)gHiiDb.HandleDb.ItemCount*sizeof(EFI_HII_HANDLE);
	for (i=0; i<gHiiDb.HandleDb.ItemCount; i++){
		hnd=(HII_HANDLE*)gHiiDb.HandleDb.Items[i];
		Handle[i]=hnd->Handle;
	}
	return EFI_SUCCESS;
}

///////////////////////////////////////////////////////////////////
// Will remove all stuff associated with form set on particular handle
// including all Update Data and Free all memory used to store private data  
//	This function assumes "HandleIdx" is valid.
VOID RemoveFormSet(UINTN HandleIdx){
	HII_FORMSET		*fst;
	HII_FORM		*frm;
	HII_LABEL		*lbl;
	UINTN			i,j,fsi;
//--------------------------------
	while(TRUE) { //it might be more then one formset with the same Handle
		fst=LocateFormSet(HandleIdx, &fsi);
		if(!fst) return; //Not a single form set was registred with this Handle

		for(i=0;i<fst->Forms.ItemCount;i++){
			frm=(HII_FORM*)fst->Forms.Items[i];
			for(j=0;j<frm->Labels.ItemCount;j++){
				lbl=frm->Labels.Items[j];
				DeleteLabelObjects(lbl);
				if(lbl->LabelData && lbl->Updated) pBS->FreePool(lbl->LabelData);
			}
			ClearItemLst(&frm->Labels,TRUE);
		}
		ClearItemLst(&fst->Labels,FALSE);
		ClearItemLst(&fst->Forms,TRUE);
		DeleteItemLst(&gHiiDb.IfrDb,fsi,TRUE);
	}
}

///////////////////////////////////////////////////////////////////
// Will remove all String records associated with "HandleIdx" for 
// all languages.  This function assumes "HandleIdx" is valid.
VOID RemoveStrings(UINTN HandleIdx){
	HII_HANDLE		*hnd=(HII_HANDLE*)gHiiDb.HandleDb.Items[HandleIdx];
	HII_STR			*str;
	INTN			i;
//-----------------------
	for(i=0; (UINTN)i<gHiiDb.StringDb.RecordCount; i++){
		DbeGoToIndex(&gHiiDb.StringDb,STR_KEY,(UINTN)i,&str);
		if(str->Handle==hnd->Handle){
			if(str->String.StrPtr)pBS->FreePool(str->String.StrPtr);
			if(str->NewStr.StrPtr)pBS->FreePool(str->NewStr.StrPtr);
			DbeDelete(&gHiiDb.StringDb,str,TRUE);
			i--;
			continue;
		}
		if(str->Handle>hnd->Handle) break;
	}
}


///////////////////////////////////////////////////////////////////
EFI_STATUS HiiRemovePack(IN EFI_HII_PROTOCOL		*This,
						 IN EFI_HII_HANDLE			Handle)

{
	UINTN				hid;
	HII_HANDLE			*phnd;
	HII_FORMSET			*fs;
	UINTN				i;
//--------------------
	if(!This) return EFI_INVALID_PARAMETER;
	
	//Here we will try to remove Pack from DB
	phnd=LocateHandle(Handle,&hid);
	if(!phnd) return EFI_INVALID_PARAMETER;

	//So we found requested Handle, now remove all stuff associated with it.
	//Remove IFRs
	if(phnd->Ifr){ 
		RemoveFormSet(hid); 
		pBS->FreePool(phnd->Ifr);
	}
	//Remove Strings
	if(phnd->HasStr)RemoveStrings(hid);

	//Free Items[] buffer if it was allocated
	//if no Secondary Languages installed for this HII_HANDLE nothing has to be done
	if(phnd->SecLang.ItemCount)ClearItemLst(&phnd->SecLang,FALSE);

	//reindexing remaining formsets to take care of
	//removed HII_HANDLE record from HiiDB.HandleDb[]
	for(i=0; i<gHiiDb.IfrDb.ItemCount; i++) {
		fs=gHiiDb.IfrDb.Items[i];
		if(fs->HandleId>hid) fs->HandleId--;
	}

	DeleteItemLst(&gHiiDb.HandleDb, hid, TRUE);

    //The current saved handle might be pointing on the one been removed.
    //so reset them to initial values.
    mCurHnd=NULL;
    mCurLang=NULL;
    mCurHid=0;
    mCurLid=0;
    mCurStr=NULL;

	return EFI_SUCCESS;
}

///////////////////////////////////////////////////////////////////
//HelperFunction to calculate size needed to dump the database
//excluding EFI_HII_DATA_TABLE header 
UINTN	GetHandleExpBuffSize(HII_HANDLE *HiiHandle, UINTN HndIndex){
	UINTN			sz=0, i, li=(UINTN)-1;	
	HII_FORMSET		*fs=NULL;
	HII_STR			*str=NULL;
	HII_STORE		*st=NULL;
//-------------------------------------	

	//This is an order of data structures as provided in Intel's implementation	
	//DevPath Data stuff Dummy so far just reserve space for DP_PACK and END_OF_DP
	sz+=sizeof(EFI_HII_DEVICE_PATH_PACK)+sizeof(EFI_DEVICE_PATH_PROTOCOL);

	//Find Formset we are working with
	fs=LocateFormSet(HndIndex, NULL);

	if(!fs) sz+= sizeof(gDummyVfr); //no formset no VAR data just Dummy Formset
	else {	
		//Variable data	
		for(i=0; i<fs->Storages.ItemCount; i++){
		//--------------------
			st=fs->Storages.Items[i];
			if(st->VarStore->Size){
				UINT8	*p;
				UINTN	ind = 0, vsize = 0;
				UINT16 VarName[256] = {0};
			//---------------------
				sz+=sizeof(EFI_HII_VARIABLE_PACK);
				//sz+=st->VarStore->Size;
				p=(UINT8*)(st->VarStore+1);
				while(*p){
					p++;
					vsize+=sizeof(UINT16); 
				}
				vsize+=sizeof(UINT16);//NULL terminator
				sz+=vsize;
				
				p=(UINT8*)(st->VarStore+1);
				while(*p && ind < sizeof(VarName)){
					VarName[ind] = (CHAR16)*p;
					p++; ind++;
				}
				vsize=0;
				pRS->GetVariable(VarName,&st->VarStore->Guid,NULL,&vsize,NULL);
				if(vsize)
					sz+=vsize;
				else
					sz += st->VarStore->Size;
			}	
		}
		if(fs->Storages.ItemCount > 0)
			sz+=sizeof(EFI_HII_VARIABLE_PACK); // !! added dummy VARIABLE PACK

		//formset data size
		sz+=fs->BufferLength+sizeof(EFI_HII_PACK_HEADER);// !! changed to +=
	}	

	//string data size 
	if(HiiHandle->HasStr){
		for(i=0; i<gHiiDb.StringDb.RecordCount; i++){
			DbeGoToIndex(&gHiiDb.StringDb,STR_KEY,(UINTN)i,&str);
			if(str->Handle==HiiHandle->Handle){
				if((li==-1)||(li!=str->LangIdx)){
					li=str->LangIdx;
					sz+=sizeof(EFI_HII_STRING_PACK); //new pack for new language
				}
				//the StrLen stored in UNICODECHAR units
				if(str->NewStr.StrPtr)sz+=str->NewStr.StrLen*sizeof(CHAR16)+sizeof(RELOFST);
				else sz+=str->String.StrLen*sizeof(CHAR16)+sizeof(RELOFST); 
			}
			if((str->Handle>HiiHandle->Handle)||(i==gHiiDb.StringDb.RecordCount-1)){ 
				sz+=sizeof(EFI_HII_STRING_PACK);//terminator pack
				break;
			}
		}
	}
	return sz;
}


UINT32 CountStrOfLang(HII_HANDLE *HiiHandle, UINTN StartIdx, UINTN LangIdx ){
	UINTN	i;
	UINT32	cnt=0;
	HII_STR	*str;
//----------------------
	for (i=StartIdx; i<gHiiDb.StringDb.RecordCount;i++){
		DbeGoToIndex(&gHiiDb.StringDb,STR_KEY,i,&str);
		if(str->Handle==HiiHandle->Handle){
			if(str->LangIdx==LangIdx)cnt++;
			else break;
		} else break;
	}
	return cnt;
}


VOID ExportHandleData(IN HII_HANDLE *HiiHandle, IN UINTN HndIndex, 
					  IN EFI_HII_DATA_TABLE *DataTbl, IN OUT UINT8 **BufferPointer)
{
	UINTN			sz=0, i;	
	HII_FORMSET		*fs;
	HII_STR			*str;
	HII_STORE		*st;
	UINT8			*p1=*BufferPointer, *p2;
	EFI_STATUS		Status;
//-------------------------------------	

	//This is an order of data structures as provided in Intel's implementation	
	//DevPath Data stuff Dummy so far END_OF_DP
	DataTbl->DevicePathOffset=(UINT32)(p1-(UINT8*)DataTbl);

	((EFI_HII_DEVICE_PATH_PACK*)p1)->Header.Type=EFI_HII_DEVICE_PATH;

	//points to the space after EFI_HII_DEVICE_PATH_PACK structure
	p2=(p1+sizeof(EFI_HII_DEVICE_PATH_PACK));

	((EFI_DEVICE_PATH_PROTOCOL*)p2)->Type=0xFF;
	((EFI_DEVICE_PATH_PROTOCOL*)p2)->SubType=0xFF;
//	((EFI_DEVICE_PATH_PROTOCOL*)p2)->Length=0;
	((EFI_DEVICE_PATH_PROTOCOL*)p2)->Length[0]=0;
	((EFI_DEVICE_PATH_PROTOCOL*)p2)->Length[1]=0;
	((EFI_HII_DEVICE_PATH_PACK*)p1)->Header.Length=(UINT32)(p2-p1+sizeof(EFI_DEVICE_PATH_PROTOCOL));

	p1=p2+sizeof(EFI_DEVICE_PATH_PROTOCOL);

	//Find Formset we are working with
	fs=LocateFormSet(HndIndex, NULL);
	if(!fs) { 
		//No formset no VAR data
		DataTbl->VariableDataOffset=0;
		
		//Copy a Dummy formset to be compatible with Intel
		DataTbl->IfrDataOffset=(UINT32)(p1-(UINT8*)DataTbl);

		pBS->CopyMem(p1,&gDummyVfr[0],sizeof(gDummyVfr));
		//copy handle guid here Shell expect it to mutch with some standart guids
		pBS->CopyMem((VOID*)(p1+8),(VOID*)&HiiHandle->Guid,sizeof(EFI_GUID));
		//Adjust the pointer
		p1+=sizeof(gDummyVfr);
	} else {	
		//Variable data	
		DataTbl->VariableDataOffset=(UINT32)(p1-(UINT8*)DataTbl);
		for(i=0; i<fs->Storages.ItemCount; i++){
		//--------------------
			st=fs->Storages.Items[i];
			if(st->VarStore->Size){
				UINT8	*p;
			//---------------------
				p2=p1+sizeof(EFI_HII_VARIABLE_PACK);
				((EFI_HII_VARIABLE_PACK*)p1)->Header.Type=EFI_HII_VARIABLE;
				//pBS->CopyMem((VOID*)&(((EFI_HII_VARIABLE_PACK*)p1)->VariableGuid), 
				//	&st->VarStore.Guid, sizeof(EFI_GUID));

				((EFI_HII_VARIABLE_PACK*)p1)->VariableGuid=st->VarStore->Guid;
				((EFI_HII_VARIABLE_PACK*)p1)->VariableId=st->VarStore->VarId;

				p=(UINT8*)(st->VarStore+1);
				while(*p){
					*p2=*p;
					p++;
					p2+=sizeof(UINT16);
					//per spec VariableLength goes in Bytes
					((EFI_HII_VARIABLE_PACK*)p1)->VariableNameLength+=sizeof(UINT16);
				}	
				p2+=sizeof(UINT16); //Null terminaterd
				((EFI_HII_VARIABLE_PACK*)p1)->VariableNameLength+=sizeof(UINT16);
				//Copy contents of the variable at present p2
				p=p1+sizeof(EFI_HII_VARIABLE_PACK);
				sz=st->VarStore->Size;
				Status=pRS->GetVariable((UINT16*)p,&st->VarStore->Guid,NULL,&sz,p2);
							
				DataTbl->NumberOfVariableData++;
				//don't forget to update size of Var Data in Pack Header
				((EFI_HII_VARIABLE_PACK*)p1)->Header.Length=(UINT32)(p2+sz-p1);

				p1=p2+sz;
			}		
		}
		if(!DataTbl->NumberOfVariableData)DataTbl->VariableDataOffset=0;	
		else {  // !! Add zero-terminating EFI HII variable
				((EFI_HII_VARIABLE_PACK*)p1)->Header.Type=EFI_HII_VARIABLE;
				((EFI_HII_VARIABLE_PACK*)p1)->Header.Length = sizeof(EFI_HII_VARIABLE_PACK);
				p1 += sizeof(EFI_HII_VARIABLE_PACK);
		}	
		//Formset goes data here
		DataTbl->IfrDataOffset=(UINT32)(p1-(UINT8*)DataTbl);
		p2=p1+sizeof(EFI_HII_PACK_HEADER);
		((EFI_HII_PACK_HEADER*)p1)->Length=(UINT32)fs->BufferLength+sizeof(EFI_HII_PACK_HEADER);
		((EFI_HII_PACK_HEADER*)p1)->Type=EFI_HII_IFR;
		
		i=0;
		CopyFormSet(p2,fs,&i);
		p1=p2+i;
	}	
	//If HIIHandle Data don't have Strings make p2==p1 since we are returning p2 value
	p2=p1;
	//string data goes here 
	if(HiiHandle->HasStr){
		UINT8		*p=p1;
		UINT32		li=(UINTN)-1;
	//-----------------
		DataTbl->StringDataOffset=(UINT32)(p1-(UINT8*)DataTbl);
		for(i=0; i<gHiiDb.StringDb.RecordCount; i++){
			DbeGoToIndex(&gHiiDb.StringDb,STR_KEY,(UINTN)i,&str);
			if(str->Handle==HiiHandle->Handle){
		
				if((li==-1)||(li!=str->LangIdx)){
					//p1 points on the EFI_HII_STRING_PACK
					p1=p;
					((EFI_HII_STRING_PACK*)p1)->Header.Type=EFI_HII_STRING;
					DataTbl->NumberOfLanguages++;
					//p2 points on the RELOFS array
					p2=p1+sizeof(EFI_HII_STRING_PACK);
					
					li=str->LangIdx;
					
					((EFI_HII_STRING_PACK*)p1)->NumStringPointers=CountStrOfLang(HiiHandle,i,li);
					//p points on the UnicodeString;
					p=p2+((EFI_HII_STRING_PACK*)p1)->NumStringPointers*sizeof(UINT32);
					((EFI_HII_STRING_PACK*)p1)->LanguageNameString=(UINT32)((UINTN)p-(UINTN)p1);
					((EFI_HII_STRING_PACK*)p1)->PrintableLanguageName=((EFI_HII_STRING_PACK*)p1)->LanguageNameString
						+4*sizeof(CHAR16);
					((EFI_HII_STRING_PACK*)p1)->Header.Length=sizeof(EFI_HII_STRING_PACK)+
						((EFI_HII_STRING_PACK*)p1)->NumStringPointers*sizeof(UINT32);

				}
				//update offset table 
				*((UINT32*)p2)=(UINT32)((UINTN)p-(UINTN)p1);
				//the StrLen stored in UNICODECHAR units including NULL CHAR16
				if(str->NewStr.StrPtr){
					pBS->CopyMem(p, str->NewStr.StrPtr, str->NewStr.StrLen*sizeof(CHAR16));
					p+=str->NewStr.StrLen*sizeof(CHAR16);
					((EFI_HII_STRING_PACK*)p1)->Header.Length+=str->NewStr.StrLen*sizeof(CHAR16);
				} else {
					pBS->CopyMem(p, str->String.StrPtr, str->String.StrLen*sizeof(CHAR16));
					p+=str->String.StrLen*sizeof(CHAR16);
					((EFI_HII_STRING_PACK*)p1)->Header.Length+=str->String.StrLen*sizeof(CHAR16);
				}
				p2+=sizeof(UINT32);
			}
			//don't forget to put terminator pack at the very end of the string data
			if((str->Handle > HiiHandle->Handle) || (i==gHiiDb.StringDb.RecordCount-1)){ 
				//Create a terminator pack
				p1=p;
				((EFI_HII_STRING_PACK*)p1)->Header.Type=EFI_HII_STRING;
				p2=p1+sizeof(EFI_HII_STRING_PACK);
				break;
			}
		}
	}

	*BufferPointer=p2;

}



///////////////////////////////////////////////////////////////////
EFI_STATUS HiiExport(IN EFI_HII_PROTOCOL		*This,
					 IN EFI_HII_HANDLE			Handle,
					 IN OUT UINTN				*BufferSize,
					 OUT VOID					*Buffer )
{
	UINTN					sz, i;
	HII_HANDLE				*phnd=NULL;
	EFI_HII_EXPORT_TABLE	*expt=NULL;
	EFI_HII_DATA_TABLE		*cdt=NULL;
	UINT8					*bp=NULL;	
//----------------
	if(!This) return EFI_INVALID_PARAMETER;
	
	sz=sizeof(EFI_HII_EXPORT_TABLE);

	//Calculate buffer Size 
	for(i=0; i<gHiiDb.HandleDb.ItemCount; i++){
		phnd=(HII_HANDLE*)gHiiDb.HandleDb.Items[i];
		if(Handle && Handle!=phnd->Handle) continue;
		sz+=GetHandleExpBuffSize(phnd,i) + sizeof(EFI_HII_DATA_TABLE);
	}
	//Check the buffer size provided
	if(sz > *BufferSize){
		*BufferSize=sz;
		return EFI_BUFFER_TOO_SMALL; 
	}	
	pBS->SetMem(Buffer, sz, 0);
	//Export Table
	expt=(EFI_HII_EXPORT_TABLE*)Buffer;
	if((UINTN)This == (UINTN)&gHiiDb.HiiProtocolOld) expt->Revision=gEfiHiiProtocolGuidOld;
	else expt->Revision=gEfiHiiProtocolGuidNew;

	bp=(UINT8*)(expt+1);

	//Start dumping the data
	for(i=0 ; i<gHiiDb.HandleDb.ItemCount; i++){
		
		phnd=(HII_HANDLE*)gHiiDb.HandleDb.Items[i];
		if(Handle && Handle!=phnd->Handle) continue;
		//CurrentDataTable
		cdt=(EFI_HII_DATA_TABLE*)bp;
		bp+=sizeof(EFI_HII_DATA_TABLE);

		sz=GetHandleExpBuffSize(phnd,i);

		cdt->HiiHandle=phnd->Handle;
		cdt->PackageGuid=phnd->Guid;
		cdt->DataTableSize=(UINT32)(sz+sizeof(EFI_HII_DATA_TABLE));

		ExportHandleData(phnd, i, cdt,  &bp);
//debug+ just to test how bp gets incremented
		ASSERT((UINTN)cdt+sizeof(EFI_HII_DATA_TABLE)+sz==(UINTN)bp);
//debug-
		expt->NumberOfHiiDataTables++;
	}
		
	return EFI_SUCCESS;
}

EFI_STATUS GetVarStoreData(HII_FORMSET *FormSet, HII_STORE *VarData, UINT8* Buffer, UINTN DefaultMask){
	HII_LABEL			*lbl;
	HII_OBJECT			*obj;
    HII_FORM            *frm;
	EFI_IFR_OP_HEADER	*op;
	UINTN				i,x,j,k,offs,len;
//------------------
	
	for(i=0; i<FormSet->Forms.ItemCount; i++){
        frm=FormSet->Forms.Items[i];
        for(x=0; x< frm->Labels.ItemCount; x++){
    		//iterate trough the Labels to get each HII_OBJECT 
		    lbl=frm->Labels.Items[x];	
    		for(j=0; j<lbl->Objects.ItemCount; j++){
			    //iterate trough the Objects to see if 
			    obj=lbl->Objects.Items[j];
			
    			if( VarData->VarStore->VarId!=obj->Store1->VarStore->VarId ||
			      MemCmp(&VarData->VarStore->Guid, &obj->Store1->VarStore->Guid, sizeof(EFI_GUID))
				) continue;
			
    			//we focused at the Object which has the same VarStore Properies as passed "VarData"
			    //So parse the object to see if it has any default flags set 
    			op=obj->ObjectCode;
    			switch(op->OpCode){
			
			    	//ONE_OF and ORDERED_LIST has almost the same encoding 
    				case EFI_IFR_ORDERED_LIST_OP:
				    case EFI_IFR_ONE_OF_OP:
    					{
				    		EFI_IFR_ONE_OF_OPTION *opt;
    					//-----------------------
				    		offs=((EFI_IFR_ONE_OF*)op)->QuestionId;
    						len=((EFI_IFR_ONE_OF*)op)->Width;

//DEBUG CODE to check if update runs out of bound
						if(offs>=VarData->VarStore->Size) {
							ASSERT_EFI_ERROR(EFI_BUFFER_TOO_SMALL);
							return EFI_BUFFER_TOO_SMALL;
						}
//DEBUG CODE to check if update runs out of bound
					
    						for(k=0; k<obj->Options.ItemCount; k++){
				    			opt=(EFI_IFR_ONE_OF_OPTION*)obj->Options.Items[k];
    							//for ORDERED_LIST it would not be any Defaults 
				    			if(op->OpCode==EFI_IFR_ORDERED_LIST_OP){
								    pBS->CopyMem(&Buffer[offs],&opt->Value, 1);
    								offs++;									

//DEBUG CODE to check if update runs out of bound
    								if(offs>=VarData->VarStore->Size) return EFI_BUFFER_TOO_SMALL;
//DEBUG CODE to check if update runs out of bound

    							} else {
    								UINTN f=(UINTN)opt->Flags;
				    			//------------------	
								    if (f & DefaultMask) {
    									pBS->CopyMem(&Buffer[offs],&opt->Value,len);
				    					break;
								    } 
    							} 
				    		}
					    }break;
				
    				case EFI_IFR_CHECKBOX_OP:
				    	{
    						EFI_IFR_CHECK_BOX *cb=(EFI_IFR_CHECK_BOX*)obj->ObjectCode;
				    		UINTN f=(UINTN)cb->Flags;
					    //--------------------
    						offs=cb->QuestionId;

//DEBUG CODE to check if update runs out of bound
    						if(offs>=VarData->VarStore->Size) return EFI_BUFFER_TOO_SMALL;
//DEBUG CODE to check if update runs out of bound

    						if(f & DefaultMask) Buffer[offs] = 1;
				    		else Buffer[offs] = 0;
										
    					} break;
					
    				case EFI_IFR_NUMERIC_OP:
				    	{
    						EFI_IFR_NUMERIC *num =(EFI_IFR_NUMERIC*)obj->ObjectCode;
				    	//--------------------------
    						offs=num->QuestionId;
				    		len=num->Width;

//DEBUG CODE to check if update runs out of bound
    						if(offs>=VarData->VarStore->Size) return EFI_BUFFER_TOO_SMALL;
//DEBUG CODE to check if update runs out of bound

    						pBS->CopyMem(&Buffer[offs],&num->Default,len);
				    	} break;
			
			    } //switch(obj->ObjectCode->Opcode)
			
    		} //for(j) loop
        }//for(x) loop
	} //for(i) loop
	return EFI_SUCCESS;
}



EFI_STATUS HiiGetDefaultImageNew(IN EFI_HII_PROTOCOL		*This,
								 IN EFI_HII_HANDLE			Handle,
								 IN UINTN					DefaultMask,
								OUT EFI_HII_VARIABLE_PACK_LIST **VariablePackList)
{
	EFI_STATUS					Status=EFI_NOT_FOUND;
	UINTN						i, j, k, hidx, vnl=0, tbsz=0;
	HII_HANDLE					*phnd;
	EFI_HII_VARIABLE_PACK_LIST	*vpl, *fvpl=NULL, *pvpl=NULL;
	HII_FORMSET					*fs;
	HII_STORE					*st;
	UINT8						*pdb, *pnb;
//----------------------------------
	
	//Check Parameters	
	if(This==NULL || VariablePackList==NULL || !Handle ) return EFI_INVALID_PARAMETER;

	//Find the handle
	phnd=LocateHandle(Handle, &hidx);
	if(phnd==NULL) return EFI_NOT_FOUND;

	//If no VarStores associated with passed Handle will return NULL
	*VariablePackList=NULL;	

	//If Handle Exists then find a FormSet associated with this Handle
	fs=LocateFormSet(hidx, NULL);
	//No formset found => no IFR data
	if(fs==NULL) return EFI_NOT_FOUND;

	//Collect the Variable data	
	for(i=0, hidx=0; i<fs->Storages.ItemCount; i++){
		st=fs->Storages.Items[i];
		if(!st->VarStore->Size) continue;
		
		Status=EFI_SUCCESS;
		hidx++;
		//get the variable name length in bytes(ASCII)
		vnl=st->VarStore->Header.Length-sizeof(EFI_IFR_VARSTORE);
		//determine how much memory we need to accomodate 
		//EFI_VARIABLE_PACK_LIST + EFI_VARIABLE_PACK + VarName + VarData
		vpl=MallocZ(sizeof(EFI_HII_VARIABLE_PACK_LIST)+ //EFI_VARIABLE_PACK_LIST
					sizeof(EFI_HII_VARIABLE_PACK)+		//EFI_VARIABLE_PACK
					(vnl*sizeof(UINT16))+ 				//EFI_VARIABLE_PACK has VarName in UINT16
					st->VarStore->Size);				//Size of actual NV Var Data	

		tbsz+=(sizeof(EFI_HII_VARIABLE_PACK_LIST)+		//EFI_VARIABLE_PACK_LIST
					sizeof(EFI_HII_VARIABLE_PACK)+		//EFI_VARIABLE_PACK
					(vnl*sizeof(UINT16))+ 				//EFI_VARIABLE_PACK has VarName in UINT16
					st->VarStore->Size);				//Size of actual NV Var Data	

		if(!vpl) return EFI_OUT_OF_RESOURCES;

		//determine where in VPL buffer Actual VAriable data suppose to start
		pdb=(UINT8*)vpl+sizeof(EFI_HII_VARIABLE_PACK_LIST)+sizeof(EFI_HII_VARIABLE_PACK)+(vnl*sizeof(UINT16));
		
		GetVarStoreData(fs,st,pdb,DefaultMask);
		
		//if this is the first structure in the list remember it we must return it's address 
		if(fvpl==NULL)fvpl=vpl;
		//if PreviouseVariablePackList ptr was initialized update pointer to next VPL with current VPL
		if(pvpl!=NULL)pvpl->NextVariablePack=vpl;
		//reinitialize PreviouseVariablePackList ptr with current VPL pointer
		pvpl=vpl;

		//Update context of the VariablePack pointer to the next data byte afer itself(per .92 spec)
		vpl->VariablePack = (EFI_HII_VARIABLE_PACK*)(vpl+1);

		//Now fill out fields of HII_VARIABLE_PACK structure
		vpl->VariablePack->Header.Type=EFI_HII_VARIABLE;
		vpl->VariablePack->Header.Length=(UINT32)(sizeof(EFI_HII_VARIABLE_PACK)+(vnl*sizeof(UINT16))+st->VarStore->Size);
		vpl->VariablePack->VariableId=st->VarStore->VarId;
		vpl->VariablePack->VariableNameLength=(UINT32)(vnl*sizeof(UINT16)); // per spec length in bytes.
		pBS->CopyMem(&vpl->VariablePack->VariableGuid, &st->VarStore->Guid, sizeof(EFI_GUID));
		//now copy Variable name "pdb" points at the befinning of VarName buffer 
		pdb=(UINT8*)vpl+sizeof(EFI_HII_VARIABLE_PACK_LIST)+sizeof(EFI_HII_VARIABLE_PACK);
		pnb=(UINT8*)(st->VarStore+1);
		//since in VARIABLE_PACKAGE VAR NAME is UNICODE simple MemCpy wouldn't do.
		for(j=0,k=0; j<vnl; j++, k+=2) {
			pdb[k]=pnb[j];
		}
	}
	
	//Per Spec we have to dump all data in single buffer.
	//Update the IN/OUT parameter
	if(tbsz) {
		*VariablePackList=Malloc(tbsz);
		if(*VariablePackList==NULL) return EFI_OUT_OF_RESOURCES;
	} else *VariablePackList=NULL;
	vpl=fvpl;
	pdb=(UINT8*)(*VariablePackList);
	while (vpl){
		//copy Var_PACK_LIST + VARPACK to the Common Buffer
		pBS->CopyMem(pdb,vpl,sizeof(EFI_HII_VARIABLE_PACK_LIST)+vpl->VariablePack->Header.Length);
		pvpl=(EFI_HII_VARIABLE_PACK_LIST*)pdb;
		pvpl->VariablePack=(EFI_HII_VARIABLE_PACK*)(pdb+sizeof(EFI_HII_VARIABLE_PACK_LIST));

		pdb+=(sizeof(EFI_HII_VARIABLE_PACK_LIST)+vpl->VariablePack->Header.Length);
		if(vpl->NextVariablePack!=NULL)pvpl->NextVariablePack=(EFI_HII_VARIABLE_PACK_LIST*)pdb;

		pvpl=vpl;
		vpl=vpl->NextVariablePack;
		
		pBS->FreePool(pvpl);
	}
		
	return Status;
}


///////////////////////////////////////////////////////////////////
//Keyboard
EFI_STATUS HiiGetKeyboardLayout(IN EFI_HII_PROTOCOL		*This,
								OUT UINT16				*DescriptorCount,
								OUT EFI_KEY_DESCRIPTOR	*Descriptor)
{
	HII_KB_LAYOUT_DATA	*kbld;
//-------------------------------
	if(!This) return EFI_INVALID_PARAMETER;

	if(!gHiiDb.KeybdDb.KblCount) return EFI_NOT_FOUND;

	kbld=gHiiDb.KeybdDb.KbLayout[gHiiDb.KeybdDb.ActiveLayout];
	
	//we got small buffer
	if(*DescriptorCount<kbld->KeyDscCount) {
		*DescriptorCount=kbld->KeyDscCount;		
		return EFI_BUFFER_TOO_SMALL;
	}
	
	MemCpy((VOID*)Descriptor, (VOID*)kbld->KeyDsc, sizeof(EFI_KEY_DESCRIPTOR)*kbld->KeyDscCount);	

	return EFI_SUCCESS;
}


////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
//EXTENDED HII INTERFACE 
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
EFI_STATUS HiiExtGetStringInfo(
							IN	EXT_HII_PROTOCOL	*This,
							IN	EFI_HII_HANDLE		Handle,
							IN	STRING_REF			Token,
							IN	CHAR16				*Lang,
							OUT EXT_STR_INFO		**ExtStrInfo)
{
	HII_STR		*str;
//-----------------------------------------
	if(!This || !ExtStrInfo ) return EFI_INVALID_PARAMETER;

	str=GetHiiString(Handle,Lang,Token);
	if(!str) return EFI_NOT_FOUND;

	if(str->NewStr.StrPtr)*ExtStrInfo=&str->NewStr;
	else *ExtStrInfo=&str->String;

	return EFI_SUCCESS;
}


EFI_STATUS HiiExtGetFormInfo(IN  EXT_HII_PROTOCOL	*This,
							 IN  EFI_HII_HANDLE		Handle,
							 IN  EFI_FORM_ID		FormId,
							 OUT HII_FORM			**ExtFormInfo)
{
	HII_FORM		*frm;
	UINTN			hi;
	HII_HANDLE		*phnd;
	HII_FORMSET		*fs;
//-----------------------------------------
	if(!This || !ExtFormInfo ) return EFI_INVALID_PARAMETER;

	phnd=LocateHandle(Handle,&hi);
	ASSERT(phnd);
	if(!phnd)return EFI_NOT_FOUND;

	fs=LocateFormSet(hi,NULL);
	ASSERT(fs);
	if(!fs)return EFI_NOT_FOUND;

	frm=LocateForm(fs,FormId);
	ASSERT(frm);
	if(!frm)return EFI_NOT_FOUND;
	*ExtFormInfo=frm;

	return EFI_SUCCESS;
}


EFI_STATUS HiiExtRegisterLabelUpdateCallback(IN  EXT_HII_PROTOCOL		*This,
									   IN  EFI_HII_HANDLE				Handle,
									   IN  EFI_FORM_LABEL				LabelId,
									   IN  HII_LABEL_UPDATE_CALLBACK	CallBack)
{
	UINTN		hi;
	HII_LABEL	*lbl;
	HII_FORMSET *fs;
//----------------------------------
	if(!This || !CallBack ) return EFI_INVALID_PARAMETER;

	if(!LocateHandle(Handle, &hi)) return EFI_INVALID_PARAMETER;
	
	//Find Formset
	fs=LocateFormSet(hi, NULL);
	if(!fs) return EFI_INVALID_PARAMETER;

	lbl=LocateFormSetLabel(fs,LabelId,NULL);
	if(!lbl) return EFI_NOT_FOUND;

	lbl->UpdateCallBack=CallBack;

	return EFI_SUCCESS;
}

EFI_STATUS HiiExtUnregisterLabelUpdateCallback(IN  EXT_HII_PROTOCOL		*This,
									   IN  EFI_HII_HANDLE				Handle,
									   IN  EFI_FORM_LABEL				LabelId)
{
	UINTN		hi;
	HII_LABEL	*lbl;
	HII_FORMSET *fs;
//----------------------------------
	if(!This) return EFI_INVALID_PARAMETER;

	if(!LocateHandle(Handle, &hi)) return EFI_INVALID_PARAMETER;
	
	//Find Formset
	fs=LocateFormSet(hi, NULL);
	if(!fs) return EFI_INVALID_PARAMETER;

	lbl=LocateFormSetLabel(fs,LabelId,NULL);
	if(!lbl) return EFI_NOT_FOUND;

	lbl->UpdateCallBack=NULL;

	return EFI_SUCCESS;
}

EFI_STATUS	HiiExtGetFormSetInfo(IN  EXT_HII_PROTOCOL	*This,
								IN  UINT16				ClassMask,		//if ==0xFFFF all Classes
								IN	UINT16				SubClass,		//if ==0xFFFF all SubClasses
								OUT T_ITEM_LIST		*FormSetList)
{
	UINTN			i;
	HII_FORMSET		*fs;
//------------------------------
	if(!This || !FormSetList) return EFI_INVALID_PARAMETER;
	
	//Make sure the list is empty
	ClearItemLst(FormSetList,FALSE);
	for(i=0; i<gHiiDb.IfrDb.ItemCount;i++){
		fs=gHiiDb.IfrDb.Items[i];
		if(SubClass!=0xFFFF && SubClass!=fs->FormSetData->SubClass) continue;
		if((fs->FormSetData->Class & ClassMask)==fs->FormSetData->Class) AppendItemLst(FormSetList,fs);
	}
	return EFI_SUCCESS;
}

EFI_STATUS HiiExtGetFormLabels(IN  EXT_HII_PROTOCOL		*This,
							   IN  EFI_HII_HANDLE		Handle,
							   IN  EFI_FORM_ID			FormID,
							   OUT T_ITEM_LIST			*LabelList)
{
	UINTN			i;
	HII_FORMSET		*fs;
	HII_FORM		*frm;
	HII_LABEL		*lbl;
	EFI_STATUS		Status;
//-----------------------------------------
	if(!This || !LabelList ) return EFI_INVALID_PARAMETER;

	if(!LocateHandle(Handle,&i)) return EFI_INVALID_PARAMETER;;

	fs=LocateFormSet(i,NULL);
	ASSERT(fs);
	if(!fs)return EFI_NOT_FOUND;

	frm=LocateForm(fs,FormID);
	ASSERT(frm);
	if(!frm)return EFI_NOT_FOUND;

	ClearItemLst(LabelList,FALSE);
	for(i=1;i<frm->Labels.ItemCount;i++){
		lbl=frm->Labels.Items[i];
		Status=AppendItemLst(LabelList,lbl);
		ASSERT(!EFI_ERROR(Status));
		if(EFI_ERROR(Status))return Status;
	}
	return EFI_SUCCESS;
}


///////////////////////////////////////////////////////////////////
//Init All Private Data
EFI_STATUS InitPrivateData(EFI_HANDLE MyImgHandle){
	EFI_STATUS			Status=0;
	//HII_LANG			*al;//any lang
//TEST//TEST//TEST//TEST//TEST//TEST//TEST//TEST//TEST//TEST//TEST//TEST
	EFI_HII_PACK_LIST	*pl=Malloc(sizeof(EFI_HII_PACK_LIST));
	// {BB2F3C9D-C7A1-4283-8AE2-4F4362990E2E}
	static EFI_GUID		pguid={ 0xbb2f3c9d, 0xc7a1, 0x4283, 0x8a, 0xe2, 0x4f, 0x43, 0x62, 0x99, 0x0e, 0x2e };
	EFI_HII_HANDLE		fph;//,sth;
//	UINT16				bl;
//	UINT8				*fsb;
//TEST//TEST//TEST//TEST//TEST//TEST//TEST//TEST//TEST//TEST//TEST//TEST
//-----------------------------
	pBS->SetMem(&gHiiDb, sizeof(HII_DB),0 );
	
	gHiiDb.ImageHandle=MyImgHandle;
	gHiiDb.NextHiiHandle=1; //Zero Handle is Invalid it must be 1 based

	//Create Any Langguage Entry - empty string L"   " 
	Status=LocateLangAdd(L"   ",L"Any Language",NULL);
	if(EFI_ERROR(Status)) return Status;

	//Create and Initialize String Database
	gHiiDb.StringDb.KeyCount=STR_KEY_CNT;
	gHiiDb.StringDb.InitialCount=STRING_DB_MAX_COUNT;
	gHiiDb.StringDb.KeyField=&gStrKey;
	gHiiDb.StringDb.MemoryType=EfiBootServicesData;
	gHiiDb.StringDb.RecordCount=0;
	gHiiDb.StringDb.IndexArray=MallocZ(sizeof(VOID*)*gHiiDb.StringDb.InitialCount*gHiiDb.StringDb.KeyCount);
	if(!gHiiDb.StringDb.IndexArray) return EFI_OUT_OF_RESOURCES;

	//Init Protocol Instance here
	gHiiDb.HiiProtocolOld.NewPack=HiiNewPackOld;
	gHiiDb.HiiProtocolNew.NewPack=HiiNewPackNew;

	gHiiDb.HiiProtocolOld.RemovePack=HiiRemovePack;
	gHiiDb.HiiProtocolNew.RemovePack=HiiRemovePack;

	gHiiDb.HiiProtocolOld.FindHandles=HiiFindHandles;
	gHiiDb.HiiProtocolNew.FindHandles=HiiFindHandles;

	gHiiDb.HiiProtocolOld.GetDefaultImage=HiiGetDefaultImageOld;
	gHiiDb.HiiProtocolNew.GetDefaultImage=HiiGetDefaultImageNew;

	gHiiDb.HiiProtocolOld.TestString=HiiTestString;
	gHiiDb.HiiProtocolNew.TestString=HiiTestString;

	gHiiDb.HiiProtocolOld.GetGlyph=HiiGetGlyph;
	gHiiDb.HiiProtocolNew.GetGlyph=HiiGetGlyph;

	gHiiDb.HiiProtocolOld.GlyphToBlt=HiiGlyphToBlt;
	gHiiDb.HiiProtocolNew.GlyphToBlt=HiiGlyphToBlt;

	gHiiDb.HiiProtocolOld.NewString=HiiNewString;
	gHiiDb.HiiProtocolNew.NewString=HiiNewString;

	gHiiDb.HiiProtocolOld.GetPrimaryLanguages=HiiGetPrimaryLanguage;
	gHiiDb.HiiProtocolNew.GetPrimaryLanguages=HiiGetPrimaryLanguage;

	gHiiDb.HiiProtocolOld.GetSecondaryLanguages=HiiGetSecondaryLanguages;
	gHiiDb.HiiProtocolNew.GetSecondaryLanguages=HiiGetSecondaryLanguages;

	gHiiDb.HiiProtocolOld.GetString=HiiGetStringOld;
	gHiiDb.HiiProtocolNew.GetString=HiiGetStringNew;

	gHiiDb.HiiProtocolOld.GetLine=HiiGetLine;
	gHiiDb.HiiProtocolNew.GetLine=HiiGetLine;

	gHiiDb.HiiProtocolOld.GetForms=HiiGetFormsOld;
	gHiiDb.HiiProtocolNew.GetForms=HiiGetFormsNew;

	gHiiDb.HiiProtocolOld.UpdateForm=HiiUpdateForm;
	gHiiDb.HiiProtocolNew.UpdateForm=HiiUpdateForm;

	gHiiDb.HiiProtocolOld.GetKeyboardLayout=HiiGetKeyboardLayout;
	gHiiDb.HiiProtocolNew.GetKeyboardLayout=HiiGetKeyboardLayout;

	gHiiDb.HiiProtocolOld.ResetStrings=HiiResetStrings; 
	gHiiDb.HiiProtocolNew.ResetStrings=HiiResetStrings; 

	gHiiDb.HiiProtocolOld.ExportDatabase=HiiExport;
	gHiiDb.HiiProtocolNew.ExportDatabase=HiiExport;

	//Now do Extended Hii Interface
	gHiiDb.HiiExtProtocol.ExtGetStringInfo=HiiExtGetStringInfo;
	gHiiDb.HiiExtProtocol.ExtGetFormInfo=HiiExtGetFormInfo;
	gHiiDb.HiiExtProtocol.ExtGetFormsetInfo=HiiExtGetFormSetInfo;
	gHiiDb.HiiExtProtocol.ExtRegLblCallBack=HiiExtRegisterLabelUpdateCallback;
	gHiiDb.HiiExtProtocol.ExtUnregLblCallBack=HiiExtUnregisterLabelUpdateCallback;
	gHiiDb.HiiExtProtocol.ExtGetFormLabels=HiiExtGetFormLabels;		
	
	//------------------------------------
	//init Font Data 
	pl->FontPack=(EFI_HII_FONT_PACK*)&UsStdNarrowGlyphData;
	pl->GuidId=&pguid;
	pl->IfrPack=NULL;//(EFI_HII_IFR_PACK*)&FrontPageVfrBin;
	pl->KeyboardPack=NULL;
	pl->StringPack=NULL;//(EFI_HII_STRING_PACK*)&FrontPageStrings;
///// Load Font Pack
{
#define FONT_FFS_FILE_GUID { 0xdac2b117, 0xb5fb, 0x4964, { 0xa3, 0x12, 0xd, 0xcc, 0x77, 0x6, 0x1b, 0x9b } }
static EFI_GUID guidFontFile = FONT_FFS_FILE_GUID;
	EFI_STATUS Status;
	EFI_FIRMWARE_VOLUME_PROTOCOL *pFV;
	UINTN DataSize;
	EFI_GUID *pSectionGuid = NULL;
	UINT32 Authentication;
	EFI_HANDLE *pHandle;
	UINTN Number,i;
	Status = pBS->LocateHandleBuffer(ByProtocol,&guidFV, NULL, &Number, &pHandle);
	for(i=0;i<Number; i++)
	{
		Status=pBS->HandleProtocol(pHandle[i], &guidFV, &pFV);
		if (EFI_ERROR(Status)) continue;
		pSectionGuid=NULL;
		DataSize=0;
		Status=pFV->ReadSection (
			pFV,&guidFontFile,
			EFI_SECTION_FREEFORM_SUBTYPE_GUID,0, &pSectionGuid, &DataSize,
			&Authentication
	 	);
		if (!EFI_ERROR(Status))
		{
			pl->FontPack=(EFI_HII_FONT_PACK*)((UINT32*)(pSectionGuid+1)+1);
			break;
		}
	}
	Status=HiiNewPackOld((EFI_HII_PROTOCOL*)&gHiiDb.HiiProtocolOld,pl,&fph);
	pBS->FreePool(pSectionGuid);
}
////////////////////
	if(EFI_ERROR(Status)) return Status;

//TEST//TEST//TEST//TEST//TEST//TEST//TEST//TEST//TEST//TEST//TEST//TEST
/*	pl->FontPack=NULL;
	pl->IfrPack=NULL;	
	pl->KeyboardPack=NULL;
	pl->StringPack=(EFI_HII_STRING_PACK*)&SetupStrings;

	Status=HiiNewPack(&gHiiDb.HiiProtocol,pl,&sth);
	if(EFI_ERROR(Status)) return Status;

	fsb=NULL;
	bl=0;
	Status=HiiGetForms(&gHiiDb.HiiProtocol,fph,0,&bl,fsb);
	if(Status==EFI_BUFFER_TOO_SMALL);
	else if(EFI_ERROR(Status)) return Status;
	fsb=Malloc(bl);
	if(!fsb) return EFI_OUT_OF_RESOURCES;
	Status=HiiGetForms(&gHiiDb.HiiProtocol,fph,0,&bl,fsb);

	//Now, I'll try to ges some strings from FrontPageDb
	{
		UINT16				mystr[81];
		EFI_STRING			plan, slan;
		EFI_IFR_FORM_SET	*fs=(EFI_IFR_FORM_SET*)fsb;
		UINT32				gb,i=0;
	//-----------------------------------
		
		Status=HiiGetPrimaryLanguage(&gHiiDb.HiiProtocol,fph,&plan);
		//it might be more than 1 Sec Lang.
		Status=HiiGetSecondaryLanguages(&gHiiDb.HiiProtocol,fph,plan,&slan);
		

		bl=80;

		Status=HiiGetString(&gHiiDb.HiiProtocol,fph,fs->FormSetTitle,TRUE,slan,&bl,&mystr[0]);

		Status=HiiGetString(&gHiiDb.HiiProtocol,fph,fs->FormSetTitle,TRUE,plan,&bl,&mystr[0]);

		Status=HiiGetString(&gHiiDb.HiiProtocol,fph,fs->Help,TRUE,slan,&bl,&mystr[0]);

		Status=HiiGetString(&gHiiDb.HiiProtocol,fph,fs->Help,TRUE,plan,&bl,&mystr[0]);

		Status=HiiTestString(&gHiiDb.HiiProtocol,&mystr[0],&i,&gb);

	}

*/
//TEST//TEST//TEST//TEST//TEST//TEST//TEST//TEST//TEST//TEST//TEST//TEST
	pBS->FreePool(pl);
//
//	return 	pBS->InstallMultipleProtocolInterfaces(	gHiiDb.ImageHandle,
//				&gEfiHiiProtocolGuid,&gHiiDb.HiiProtocol,NULL,NULL);
	return	EFI_SUCCESS;
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2005, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
