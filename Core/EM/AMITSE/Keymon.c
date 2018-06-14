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
// $Archive: /Alaska/BIN/Modules/AMITSE2_0/AMITSE/Keymon.c $
//
// $Author: Premkumara $
//
// $Revision: 7 $
//
// $Date: 8/28/14 4:29a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/AMITSE2_0/AMITSE/Keymon.c $
// 
// 7     8/28/14 4:29a Premkumara
// EIP-135253 Updating file name proper in #include
// 
// 6     10/18/12 5:31a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 6     10/10/12 12:23p Arunsb
// Synched the source for v2.16.1232 backup with Aptio
// 
// 5     11/04/11 4:37a Arunsb
// [TAG]  		EIP67615
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Keyattribute support doesn't work in AMITSE Keymon support
// [RootCause]  	{SETUP_ENTRY_LEGACY_CODE,0} - This initilization code
// initilize only ScanCode and ShiftKey.
// It doesn't initilize the AltKey, CtrlKey etc ( Other fields in the
// KEY_ATTRIBUTE structure).
// [Solution]  	Modified the initilization like
// {SETUP_ENTRY_LEGACY_CODE,{0,0,0,0}}
// [Files]  		keymon.c
// 
// 4     2/19/10 12:58p Madhans
// Updated for TSE 2.01. Refer Changelog.log for File change history.
// 
// 4     2/19/10 7:59a Mallikarjunanv
// updated the year in copyright message
// 
// 3     7/14/09 6:32p Blaines
// For GTSE first Release.,
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
// 3     10/03/08 12:40p Madhans
// Update the changes provided by the core team
// 
// 2     7/18/07 7:58a Arunkumars
// clean up
// 
// 1     7/09/07 1:18p Arunkumars
// - Added elink hooks for Logo, Password management and Control Keys
// customizations
//
//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
//<AMI_FHDR_START>
//
// Name:		Keymon.c
//
// Description:	Contains key monitoring functions.
//
//<AMI_FHDR_END>
//**********************************************************************

#ifdef TSE_FOR_APTIO_4_50

#include "Token.h"
#include <Efi.h>

#else //#ifdef TSE_FOR_APTIO_4_50

#include "minisetup.h"

#endif //#ifdef TSE_FOR_APTIO_4_50

#if SETUP_SUPPORT_KEY_MONITORING

#include <Protocol\KeyMonPlatform.h>
#include <Protocol\MonitorKeyFilter.h>

#include "KeyMon.h"


EFI_STATUS
GetPlatformMonitorKeyOptions(
  IN   EFI_KEYMON_PLATFORM_PROTOCOL *This,
  OUT  KEY_ELEMENT                    **KeyList,
  OUT  UINTN                          *KeyListSize
  );

static EFI_GUID EfiKeyMonPlatformProtocolGuid = EFI_KEYMON_PLATFORM_PROTOCOL_GUID;

static EFI_KEYMON_PLATFORM_PROTOCOL gKeyMonPlatformProtocol =
{
    GetPlatformMonitorKeyOptions
};

enum SETUP_KEYS
{
    SK_EntryKey
#if SETUP_ALT_ENTRY_ENABLE
    ,SK_AltEntryKey
#endif
#if SETUP_BBS_POPUP_ENABLE
    ,SK_PopupBootEntryKey
#endif
#if SETUP_OEM_KEY1_ENABLE
    ,SK_OemKey1
#endif
#if SETUP_OEM_KEY2_ENABLE
    ,SK_OemKey2
#endif
#if SETUP_OEM_KEY3_ENABLE
    ,SK_OemKey3
#endif
#if SETUP_OEM_KEY4_ENABLE
    ,SK_OemKey4
#endif
};

KEY_ELEMENT gLegacyKeyTable[]=
{
    {SETUP_ENTRY_LEGACY_CODE,{0,0,0,0}}
#if SETUP_ALT_ENTRY_ENABLE
    ,{SETUP_ALT_ENTRY_LEGACY_CODE,{0,0,0,0}}
#endif
#if SETUP_BBS_POPUP_ENABLE
    ,{POPUP_MENU_ENTRY_LEGACY_CODE,{0,0,0,0}}
#endif
#if SETUP_OEM_KEY1_ENABLE
    ,{SETUP_OEM_KEY1_LEGACY_CODE,{0,0,0,0}}
#endif
#if SETUP_OEM_KEY2_ENABLE
    ,{SETUP_OEM_KEY2_LEGACY_CODE,{0,0,0,0}}
#endif
#if SETUP_OEM_KEY3_ENABLE
    ,{SETUP_OEM_KEY3_LEGACY_CODE,{0,0,0,0}}
#endif
#if SETUP_OEM_KEY4_ENABLE
    ,{SETUP_OEM_KEY4_LEGACY_CODE,{0,0,0,0}}
#endif
};

UINT32 gLegacyKeys;
EFI_HANDLE KeyMonProtocolHandle;

extern EFI_BOOT_SERVICES *gBS;

VOID InstallKeyMonProtocol(VOID)
{
    gBS->InstallProtocolInterface(
                        &KeyMonProtocolHandle,
                        &EfiKeyMonPlatformProtocolGuid,
                        EFI_NATIVE_INTERFACE,
                        &gKeyMonPlatformProtocol
                        );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	GetPlatformMonitorKeyOptions
//
// Description:	This function registers keys with key monitor driver
//              for monitoring in the legacy mode.
//
// Input:		EFI_USB_LEGACY_PLATFORM_PROTOCOL *This
//              KEY_ELEMENT **KeyList: List of keys to be monitored.
//              UINTN *KeyListSize: Size of data returned in KeyList.
//
// Output:		Return Status based on errors that occurred in library
//              functions.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
GetPlatformMonitorKeyOptions(
  IN   EFI_KEYMON_PLATFORM_PROTOCOL   *This,
  OUT  KEY_ELEMENT                    **KeyList,
  OUT  UINTN                          *KeyListSize
  )
{
    *KeyList = gLegacyKeyTable;
    *KeyListSize = sizeof(gLegacyKeyTable);

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	GetKeysFromKeyMonFilter
//
// Description:	This function receives keys from key monitor filter
//
// Input:		VOID
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID GetKeysFromKeyMonFilter(VOID)
{
    UINT32  KeyDetected;
	EFI_MONITOR_KEY_FILTER_PROTOCOL *MonKey;
    EFI_STATUS  Status;
    EFI_GUID EfiMonitorKeyFilterProtocolGuid = EFI_MONITOR_KEY_FILTER_PROTOCOL_GUID;

    // Locate protocols
	Status = gBS->LocateProtocol (
					&EfiMonitorKeyFilterProtocolGuid,
					NULL, &MonKey);
    if ( !(EFI_ERROR(Status)) )
    {
        MonKey->GetMonitoredKeys(MonKey, &KeyDetected);

        if(KeyDetected & (1 << SK_EntryKey))
        {
            gLegacyKeys|=SETUP_ENTRY_KEY_BIT;
        }
#if SETUP_ALT_ENTRY_ENABLE
        if(KeyDetected & (1 << SK_AltEntryKey))
        {
            gLegacyKeys|=SETUP_ENTRY_KEY_BIT;
        }
#endif
#if SETUP_BBS_POPUP_ENABLE
        if(KeyDetected & (1 << SK_PopupBootEntryKey))
        {
            gLegacyKeys|=POPUP_ENTRY_KEY_BIT;
        }
#endif
#if SETUP_OEM_KEY1_ENABLE
        if(KeyDetected & (1 << SK_OemKey1))
        {
            gLegacyKeys|=OEM_KEY1_BIT;
        }
#endif
#if SETUP_OEM_KEY2_ENABLE
        if(KeyDetected & (1 << SK_OemKey2))
        {
            gLegacyKeys|=OEM_KEY2_BIT;
        }
#endif
#if SETUP_OEM_KEY3_ENABLE
        if(KeyDetected & (1 << SK_OemKey3))
        {
            gLegacyKeys|=OEM_KEY3_BIT;
        }
#endif
#if SETUP_OEM_KEY4_ENABLE
        if(KeyDetected & (1 << SK_OemKey4))
        {
            gLegacyKeys|=OEM_KEY4_BIT;
        }
#endif

    }
}

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
