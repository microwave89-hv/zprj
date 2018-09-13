//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
//**                                                             **//
//**         (C)Copyright 2010, American Megatrends, Inc.        **//
//**                                                             **//
//**                     All Rights Reserved.                    **//
//**                                                             **//
//**   5555 Oakbrook Pkwy, Building 200,Norcross, Georgia 30093  **//
//**                                                             **//
//**                     Phone (770)-246-8600                    **//
//**                                                             **//
//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/BootOnly/bbs.h $
//
// $Author: Arunsb $
//
// $Revision: 6 $
//
// $Date: 10/18/12 5:58a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/BootOnly/bbs.h $
// 
// 6     10/18/12 5:58a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 9     10/10/12 12:36p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 5     12/21/10 11:46a Mallikarjunanv
// [TAG]  		EIP47353
// [Category]  	Improvement
// [Description]  	The #define 32 is tokenized so it can be able to
// display more than 32 characters for some boot options. 
// [Files]  		bbs.h, MiniSetup.sdl
// 
// 4     2/19/10 8:14a Mallikarjunanv
// updated year in copyright message
// 
// 3     6/16/09 2:16p Presannar
// Added File Headers for Header Files
// 
// 2     6/12/09 7:41p Presannar
// Initial implementation of coding standards
// 
// 1     6/04/09 8:05p Madhans
// 
// 1     4/28/09 11:11p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 2     1/30/09 6:06p Madhans
// Function headers added. 
// 
// 1     12/18/08 7:58p Madhans
// Intial version of TSE Lite sources
// 
//*****************************************************************//
//*****************************************************************//
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:		bbs.h
//
// Description:	Header file for bbs/legacy boot management.
//
//<AMI_FHDR_END>
//**********************************************************************

#ifndef _BBS_H_
#define _BBS_H_

UINT16	gBBSHardDiskOffset ;
UINT16	gBBSCDOffset ;
UINT16	gBBSFloppyOffset ;
UINT16	gBBSNetworkOffset ;
UINT16	gBBSBevOffset ;

#ifndef MAX_DRIVE_NAME
#define MAX_DRIVE_NAME TSE_MAX_DRIVE_NAME // EIP : 47353 MAX_DRIVE_NAME 32 macro value is changed to TSE_MAX_DRIVE_NAME SDL TOKEN. So maximum character of Drive name can be determined at run time
#endif //MAX_DRIVE_NAME

typedef struct
{
	UINT16	HardDiskCount;
	UINT16	CDROMCount;
	UINT16	FloppyCount;
	UINT16	NetworkCount;
	UINT16	BevCount;
}
BBS_DEVICE_COUNT;

typedef struct
{
	UINT32	Type;
	UINT16	Length;
	UINT16	Data[1];
}
BBS_ORDER_TABLE;

#define BBS_ORDER_DISABLE_MASK  0xFF00

typedef struct _BBS_ORDER_LIST
{
    UINT16	Index;
    CHAR16	Name[MAX_DRIVE_NAME];
}
BBS_ORDER_LIST;

//exported variables
extern EFI_GUID gLegacyDevGuid;

//exported functions
VOID BBSGetDeviceList( VOID );
VOID BBSSetBootPriorities( BOOT_DATA *pBootData, UINT16 *pOrder, UINTN u16OrderCount);
EFI_STATUS BBSSetBootNowPriority( BOOT_DATA *BootData,UINTN uiPrefferedDevice,BOOLEAN ShowAllBbsDev);
BOOLEAN BBSValidDevicePath( EFI_DEVICE_PATH_PROTOCOL *DevicePath );
EFI_STATUS BBSLaunchDevicePath( EFI_DEVICE_PATH_PROTOCOL *DevicePath );

VOID BBSUpdateBootData(UINT16 GroupNo);
CHAR16 *BBSGetOptionName( UINT16 *Option, UINT16 Pos  );
//VOID BBSUpdateOrder(UINT16 newOption,UINT32 *offset,UINTN *size, VOID **buffer);
VOID BBSSetDisabled(UINT16 Index, VOID **DisDPs, UINTN *DPSize);

EFI_STATUS BbsItkBoot();

#endif /* _BBS_H_ */

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**     5555 Oakbrook Pkwy, Building 200,Norcross, Georgia 30093     **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
