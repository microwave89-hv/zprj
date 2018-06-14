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
// $Archive: /Alaska/BIN/Modules/AMITSE2_0/AMITSE/Keymon.h $
//
// $Author: Arunsb $
//
// $Revision: 4 $
//
// $Date: 10/18/12 5:31a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/AMITSE2_0/AMITSE/Keymon.h $
// 
// 4     10/18/12 5:31a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 5     10/10/12 12:23p Arunsb
// Synched the source for v2.16.1232 backup with Aptio
// 
// 3     2/19/10 12:58p Madhans
// Updated for TSE 2.01. Refer Changelog.log for File change history.
// 
// 3     2/19/10 7:59a Mallikarjunanv
// updated the year in copyright message
// 
// 2     6/24/09 6:33p Madhans
// Coding Standards
// 
// 1     6/04/09 7:49p Madhans
// AMI TSE Advanced.
// 
// 1     4/28/09 10:49p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 1     4/28/09 10:24p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 1     7/09/07 1:18p Arunkumars
// - Added elink hooks for Logo, Password management and Control Keys
// customizations
//
//*****************************************************************//
//*****************************************************************//
//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		keymon.h
//
// Description:	header of keymon.c
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>
#if SETUP_SUPPORT_KEY_MONITORING

#define SETUP_ENTRY_KEY_BIT 0x00000001
#if SETUP_BBS_POPUP_ENABLE
#define POPUP_ENTRY_KEY_BIT 0x00000002
#endif
#if SETUP_OEM_KEY1_ENABLE
#define OEM_KEY1_BIT 0x00000004
#endif
#if SETUP_OEM_KEY2_ENABLE
#define OEM_KEY2_BIT 0x00000008
#endif
#if SETUP_OEM_KEY3_ENABLE
#define OEM_KEY3_BIT 0x00000100
#endif
#if SETUP_OEM_KEY4_ENABLE
#define OEM_KEY4_BIT 0x00000200
#endif

VOID InstallKeyMonProtocol(VOID);
VOID GetKeysFromKeyMonFilter(VOID);

extern UINT32 gLegacyKeys;

#endif
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
