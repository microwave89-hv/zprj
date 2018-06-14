//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/CMOS Manager/CMOS Board/CMOS Messages/CmosMessages.c 2     6/15/10 2:22p Michaela $
//
// $Date: 6/15/10 2:22p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/CMOS Manager/CMOS Board/CMOS Messages/CmosMessages.c $
// 
// 2     6/15/10 2:22p Michaela
// 
//**********************************************************************

//<AMI_FHDR_START>
//---------------------------------------------------------------------------
//
// Name:        CmosMessages.c
//
// Description: Contains code to display CMOS-related boot messages.
//
//---------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "Tiano.h"
#include <Efi.h>
#include <AmiDxeLib.h>
#include <SspData.h>
#include <SspTokens.h>
#include <CmosAccess.h>
#include "CmosManager.h"
#include <Setup.h>
#include <Protocol\AMIPostMgr.h>
#include <Protocol\SimpleTextIn.h>
#include <Protocol\SimpleTextOut.h>
#include "HiiLib.h"
#include "Mem.h"
#include "AMITSEStrTokens.h"
#include "AmiVfr.h"

#if EFI_SPECIFICATION_VERSION > 0x20000
#include "Include\UefiHii.h"
#include "Protocol\HiiDatabase.h"
#include "Protocol\HiiString.h"
#else
#include <Protocol/Hii.h>
#endif


extern EFI_BOOT_SERVICES        *gBS;
extern EFI_SYSTEM_TABLE         *gST;
extern EFI_RUNTIME_SERVICES     *gRT;

// Console messages are only supported if TSE sources are included

#if !TSE_SOURCES_SUPPORT
  #ifdef CMOS_TRACE_FULL
    #undef CMOS_TRACE_FULL
  #endif
  #define CMOS_TRACE_FULL
#endif

BOOLEAN CmosMgrProcessConInAvailability( VOID )
{
    EFI_GUID                    AmiPostManagerProtocolGuid 
                                    = AMI_POST_MANAGER_PROTOCOL_GUID;
    AMI_POST_MANAGER_PROTOCOL   *AmiPostMgr;
    UINT8                       Selection = 0;
    EFI_STATUS                  Status;
    EFI_TPL                     OldTpl = 0;  // zero initial value required
    EFI_CMOS_ACCESS_INTERFACE   *Cmos = NULL;
    EFI_GUID                    CmosGuid = EFI_DXE_CMOS_ACCESS_GUID;
    BOOLEAN                     BadBattery = FALSE;
    BOOLEAN                     DefaultsLoaded = FALSE;
    BOOLEAN                     NotUsable = FALSE;
    BOOLEAN                     BadChecksum = FALSE;
    BOOLEAN                     FirstBoot = FALSE;
    CMOS_STATUS_BYTES           CmosInfo;
   	CHAR16                      *Title = NULL;
    CHAR16                      *BatteryMsg = NULL;
    CHAR16                      *ChecksumMsg = NULL;
    CHAR16                      *DefaultsMsg = NULL;
    CHAR16                      *UsableMsg = NULL;
    CHAR16                      *FirstBootMsg = NULL;

    CMOS_TRACE_FULL(( CMOS_TRACE_ALWAYS, 
        "Locate CMOS Manager interface...\n" ));
    Status = gBS->LocateProtocol( &CmosGuid, NULL, &Cmos);
    if (!EFI_ERROR (Status)) {
        Cmos->ReadCmosStatusBytes(Cmos, &CmosInfo);

        NotUsable = CmosInfo.ConfigurationStatus.NotUsable;
    }
    else {
        CMOS_TRACE_FULL(( CMOS_TRACE_ALWAYS, 
            "Could not locate CMOS Manager\n" ));
    }

    if ( !NotUsable ) {
        Cmos->Read(Cmos, CMOS_MGR_CHECKSUM_BAD,        &BadChecksum);
        Cmos->Read(Cmos, CMOS_MGR_BATTERY_BAD,         &BadBattery);
        Cmos->Read(Cmos, CMOS_MGR_DEFAULTS_LOADED,     &DefaultsLoaded);
        Cmos->Read(Cmos, CMOS_MGR_FIRST_BOOT_DETECTED, &FirstBoot);
    }

    // Show messages if the battery is bad or defaults were loaded.

    if ( BadChecksum || BadBattery || DefaultsLoaded 
         || NotUsable || FirstBoot )
    {
        CMOS_TRACE_FULL(( CMOS_TRACE_ALWAYS, 
            "Locate POST Manager interface...\n" ));
        Status = gBS->LocateProtocol( &AmiPostManagerProtocolGuid, NULL, 
                                      &AmiPostMgr );
        if (EFI_ERROR (Status)) {
            CMOS_TRACE_FULL(( CMOS_TRACE_ALWAYS, 
                              "Could not locate POST manager\n" ));
            return FALSE;
        }   

        // get strings

        Title = HiiGetString( gHiiHandle, STRING_TOKEN(CMOS_MESSAGE_TITLE));
        BatteryMsg = HiiGetString( gHiiHandle, STRING_TOKEN(BAD_BATTERY_MESSAGE));
        ChecksumMsg = HiiGetString( gHiiHandle, STRING_TOKEN(BAD_CHECKSUM_MESSAGE));
        DefaultsMsg = HiiGetString( gHiiHandle, STRING_TOKEN(DEFAULTS_LOADED_MESSAGE));
        UsableMsg = HiiGetString( gHiiHandle, STRING_TOKEN(NOT_USABLE_MESSAGE));
        FirstBootMsg = HiiGetString( gHiiHandle, STRING_TOKEN(FIRST_BOOT_MESSAGE));

        // save current TPL and then lower TPL to EFI_TPL_APPLICATION

        OldTpl = gBS->RaiseTPL( EFI_TPL_HIGH_LEVEL );  
        gBS->RestoreTPL( EFI_TPL_APPLICATION );

        AmiPostMgr->SwitchToPostScreen(); 
    }

    if ( BadBattery  ){
        CMOS_TRACE_FULL(( CMOS_TRACE_ALWAYS, 
            "Displaying bad battery POST message box...\n" ));
        Status = AmiPostMgr->DisplayMsgBox( Title, 
                                             BatteryMsg,
                                             MSGBOX_TYPE_OK, 
                                             &Selection);
    } 

    if ( FirstBoot  ){
        CMOS_TRACE_FULL(( CMOS_TRACE_ALWAYS, 
            "Displaying first boot POST message box...\n" ));
        Status = AmiPostMgr->DisplayMsgBox( Title, 
                                             FirstBootMsg,
                                             MSGBOX_TYPE_OK,
                                             &Selection);        
    }

    // The bad checksum message is expected on the first boot

    if ( BadChecksum && !FirstBoot  ){
        CMOS_TRACE_FULL(( CMOS_TRACE_ALWAYS, 
            "Displaying bad checksum POST message box...\n" ));
        Status = AmiPostMgr->DisplayMsgBox( Title, 
                                             ChecksumMsg,
                                             MSGBOX_TYPE_OK,
                                             &Selection);        
    }

    if ( NotUsable ){
        CMOS_TRACE_FULL(( CMOS_TRACE_ALWAYS, 
            "Displaying bad CMOS POST message box...\n" ));
        Status = AmiPostMgr->DisplayMsgBox( Title, 
                                             UsableMsg,
                                             MSGBOX_TYPE_OK, 
                                             &Selection);
    } 

    if ( DefaultsLoaded ){
        CMOS_TRACE_FULL(( CMOS_TRACE_ALWAYS, 
            "Displaying defaults loaded POST message box...\n" ));
        Status = AmiPostMgr->DisplayMsgBox( Title, 
                                            DefaultsMsg,
                                             MSGBOX_TYPE_OK,
                                             &Selection);        
    }

    if ( OldTpl != 0 )
        gBS->RaiseTPL(OldTpl);

    // free string memory

    if ( Title != NULL )
        MemFreePointer( (VOID **)&Title );
    if ( BatteryMsg != NULL )
        MemFreePointer( (VOID **)&BatteryMsg );
    if ( ChecksumMsg != NULL )
        MemFreePointer( (VOID **)&ChecksumMsg );
    if ( DefaultsMsg != NULL )
        MemFreePointer( (VOID **)&DefaultsMsg );
    if ( UsableMsg != NULL )
        MemFreePointer( (VOID **)&UsableMsg );
    if ( FirstBootMsg != NULL )
        MemFreePointer( (VOID **)&FirstBootMsg );

    return FALSE;  // This routine is not used for password
}

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
