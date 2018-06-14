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
// $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/PchWrap/WdtApp/WdtAppDxe/WdtAppDxe.c 2     5/14/14 1:10p Barretlin $
//
// $Revision: 2 $
//
// $Date: 5/14/14 1:10p $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/PchWrap/WdtApp/WdtAppDxe/WdtAppDxe.c $
// 
// 2     5/14/14 1:10p Barretlin
// [TAG]  		EIP167028
// [Category]  	Improvement
// [Description]  	Variable attribute improment
// [Files]  		SB.sd SBDxe.c WdtAppDxe.c
// 
// 1     2/08/12 8:34a Yurenlai
// Intel Lynx Point/SB eChipset initially releases.
// 
//*************************************************************************
#include <Efi.h>
#include <token.h>
#include <AmiLib.h>
#include <AmiDxeLib.h>
#include <Dxe.h>
#include <PCI.h>
#include <AmiCspLib.h>
#include <WdtAppVariable.h>
#include <Protocol\Wdt\Wdt.h>
#include <Protocol\WdtApp\WdtApp.h>

#ifdef EFI_DEBUG
#define WDT_TIMEOUT_VALUE 10     // s
#else
#define WDT_TIMEOUT_VALUE 5      // s
#endif

#define WDT_RELOAD_TIMER 10000000 // in units of 100ns

EFI_GUID guidLegacyBoot = EFI_EVENT_LEGACY_BOOT_GUID;
EFI_GUID  gWdtProtocolGuid = WDT_PROTOCOL_GUID;

EFI_STATUS
StopFeedingWatchdog (
  IN EFI_EVENT Event,
  IN VOID      *Context
);

EFI_STATUS
FeedWatchdog (
  IN EFI_EVENT Event,
  IN VOID      *Context
);

EFI_STATUS
InstallWdtSupport (
  VOID
);

EFI_STATUS
EFIAPI
RequestWdtAfterReboot (
  VOID
);

EFI_STATUS
EFIAPI
RequestWdtNow (
  VOID
);

WDT_APP_PROTOCOL  mWdtAppProtocol = {
  RequestWdtAfterReboot,
  RequestWdtNow
};

EFI_EVENT  mFeedEvent;

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   WdtAppDxeEntryPoint
//
// Description: Turns on WDT during DXE phase according to requests made by
//              OS overclocking application (through WDT status) and BIOS
//              modules (through flash variable)
//
// Input:       IN EFI_HANDLE       ImageHandle,
//              IN EFI_SYSTEM_TABLE *SystemTable
//
// Output:      EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
WdtAppDxeEntryPoint (
  IN EFI_HANDLE       ImageHandle,
  IN EFI_SYSTEM_TABLE *SystemTable
  )
{
  EFI_STATUS           Status;
  WDT_PROTOCOL         *WdtProtocol;
  UINTN                VariableSize;
  UINT32               Attributes;
  EFI_GUID             WdtPersistentDataGuid = WDT_PERSISTENT_DATA_GUID;
  WDT_PERSISTENT_DATA  WdtPersistentData;

  InitAmiLib(ImageHandle, SystemTable);

  TRACE ((-1, "(WdtApp) Entry Point to WdtAppDxe\n"));

  Status = pBS->LocateProtocol(&gWdtProtocolGuid, NULL, &WdtProtocol);
  if ( EFI_ERROR(Status) ) {
    TRACE ((-1, "(WdtApp) Failed to locate Wdt protocol, Status = %r\n",Status));
    return EFI_SUCCESS;
  }

  VariableSize  = sizeof (WDT_PERSISTENT_DATA);
  
  Status = pRS->GetVariable (
                  L"WdtPersistentData",
                  &WdtPersistentDataGuid,
                  &Attributes,
                  &VariableSize,
                  &WdtPersistentData
                  );
  if (EFI_ERROR (Status)) {
    WdtPersistentData.Enable = 0;
    Attributes = EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS;
  }

  if (WdtProtocol->IsWdtRequired() == TRUE || WdtPersistentData.Enable == 1) {
    WdtProtocol->ReloadAndStart(WDT_TIMEOUT_VALUE);
    InstallWdtSupport();
  }

  WdtPersistentData.Enable = 0;
  pRS->SetVariable(
         L"WdtPersistentData",
         &WdtPersistentDataGuid,
         Attributes,
         sizeof (WDT_PERSISTENT_DATA),
         &WdtPersistentData
         );

  Status = pBS->InstallProtocolInterface (
                  &ImageHandle,
                  &gWdtAppProtocolGuid,
                  EFI_NATIVE_INTERFACE,
                  &mWdtAppProtocol
                  );
  
  ASSERT_EFI_ERROR (Status);

  return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   RequestWdtNow
//
// Description: Allows protocol's clients to request that WDT be turned on and periodically kicked, 
//              starting from now.
//
// Input:       None
//
// Output:      EFI_SUCCESS if everything's OK
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
EFIAPI
RequestWdtNow (
  VOID
  )
{
  EFI_STATUS Status;
  Status = InstallWdtSupport();
  return Status;
};


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   RequestWdtAfterReboot
//
// Description: Allows protocol's clients to request that WDT be turned on and periodically kicked 
//              during BIOS execution during next boot.
//
// Input:       None
//
// Output:      EFI_SUCCESS if everything's OK
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
EFIAPI
RequestWdtAfterReboot (
  VOID
  )
{
  EFI_STATUS           Status;
  EFI_GUID             WdtPersistentDataGuid = WDT_PERSISTENT_DATA_GUID;
  WDT_PERSISTENT_DATA  WdtPersistentData;
  UINT32               Attributes;
  UINTN                VariableSize;

  VariableSize  = sizeof (WDT_PERSISTENT_DATA);

  Status = pRS->GetVariable (
                  L"WdtPersistentData",
                  &WdtPersistentDataGuid,
                  &Attributes,
                  &VariableSize,
                  &WdtPersistentData
                  );
  if (EFI_ERROR(Status)) Attributes = EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS;

  WdtPersistentData.Enable = 1;
  Status = pRS->SetVariable(
                  L"WdtPersistentData",
                  &WdtPersistentDataGuid,
                  Attributes,
                  sizeof (WDT_PERSISTENT_DATA),
                  &WdtPersistentData
                  );
  ASSERT_EFI_ERROR(Status);

  return Status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   InstallWdtSupport
//
// Description: Creates events for FeedWatchdog and StopFeedingWatchdog functions.
//
// Input:       None
//
// Output:      EFI_SUCCESS if everything's OK
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
InstallWdtSupport (
  VOID
  )
{
  EFI_STATUS Status;
  EFI_EVENT  BootEvent;
  WDT_PROTOCOL* WdtProtocol;

  TRACE ((-1, "(WdtApp) Wdt turned on\n"));
  
  Status = pBS->LocateProtocol(&gWdtProtocolGuid, NULL, &WdtProtocol);
  ASSERT_EFI_ERROR(Status);
  Status = WdtProtocol->ReloadAndStart(WDT_TIMEOUT_VALUE);
  ASSERT_EFI_ERROR(Status);

  Status = pBS->CreateEvent (
                  EFI_EVENT_TIMER | EFI_EVENT_NOTIFY_SIGNAL,
                  TPL_NOTIFY,
                  FeedWatchdog,
                  NULL,
                  &mFeedEvent
                  );
  ASSERT_EFI_ERROR (Status);
  Status = pBS->SetTimer (
                  mFeedEvent,
                  TimerPeriodic,
                  WDT_RELOAD_TIMER
                  );
  ASSERT_EFI_ERROR (Status);

  Status = pBS->CreateEvent (
                  EVT_SIGNAL_EXIT_BOOT_SERVICES,
                  TPL_CALLBACK,
                  StopFeedingWatchdog,
                  NULL,
                  &BootEvent
                  );

  ASSERT_EFI_ERROR (Status);

  Status = pBS->CreateEventEx(
        EVT_NOTIFY_SIGNAL, 
        TPL_CALLBACK,
        StopFeedingWatchdog,
        NULL, 
        &guidLegacyBoot,
        &BootEvent
    );

  ASSERT_EFI_ERROR (Status);

  return Status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   FeedWatchdog
//
// Description: Prevents WDT timeout by restarting it.
//
// Input:       None
//
// Output:      Nothing
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
FeedWatchdog (
  IN EFI_EVENT Event,
  IN VOID      *Context
  )
{
  EFI_STATUS Status;
  WDT_PROTOCOL* WdtProtocol;

  Status = pBS->LocateProtocol(&gWdtProtocolGuid, NULL, &WdtProtocol);
  if ( EFI_ERROR(Status) ) {
    TRACE ((-1, "(WdtApp) Failed to locate Wdt protocol, Status = %r\n",Status));
    Status = pBS->SetTimer (mFeedEvent, TimerCancel, 0);
    ASSERT_EFI_ERROR(Status);
    Status = pBS->CloseEvent (mFeedEvent);
    ASSERT_EFI_ERROR(Status);
    return Status;
  }
  Status = WdtProtocol->ReloadAndStart(WDT_TIMEOUT_VALUE);
  return Status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   StopFeedingWatchdog
//
// Description: Stops timer and event that kept on feeding watchdog.
//
// Input:       None
//
// Output:      Nothing
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
StopFeedingWatchdog (
  IN EFI_EVENT Event,
  IN VOID      *Context
  )
{
  EFI_STATUS Status;
  WDT_PROTOCOL* WdtProtocol;
  
  TRACE ((-1, "(WdtApp) Stop feeding WDT\n"));
  Status = pBS->SetTimer (mFeedEvent, TimerCancel, 0);
  ASSERT_EFI_ERROR(Status);
  Status = pBS->CloseEvent (mFeedEvent);
  ASSERT_EFI_ERROR(Status);
  Status = pBS->LocateProtocol(&gWdtProtocolGuid, NULL, &WdtProtocol);
  if ( !EFI_ERROR(Status) ) {
    WdtProtocol->Disable();
  }
  return EFI_SUCCESS;
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
