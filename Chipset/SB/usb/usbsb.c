//****************************************************************************
//****************************************************************************
//**                                                                        **
//**             (C)Copyright 1985-2013, American Megatrends, Inc.          **
//**                                                                        **
//**                          All Rights Reserved.                          **
//**                                                                        **
//**             5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093          **
//**                                                                        **
//**                          Phone (770)-246-8600                          **
//**                                                                        **
//****************************************************************************
//****************************************************************************

//****************************************************************************
// $Header: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/chipset/sb/usb/usbsb.c 2     2/10/17 1:48a Chienhsieh $
//
// $Revision: 2 $
//
// $Date: 2/10/17 1:48a $
//
//****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/chipset/sb/usb/usbsb.c $
// 
// 2     2/10/17 1:48a Chienhsieh
// [TAG]  		EIP316430
// [Description]  	[Haswell Series] Modules Update/Function
// implementation/Bug fixed on 'SharkBay DT' CRB049 project label.
// Sync with 4.6.5.1_USB_08.10.36
// 
// 1     8/08/16 4:02a Chienhsieh
// Sync with 4.6.3_USB_08.10.35.
// 
// 29    6/11/14 2:26a Littleyan
// Update USBSB Template to 4.6.3_USB_08.10.30.
// 
// 28    1/17/14 4:20a Littleyan
// Update USBSB Template to 4.6.3_USB_08.10.29.
// 
// 27    12/10/13 6:04a Littleyan
// Add WPT Sku
// 
// 26    5/13/13 12:17a Wesleychen
// Update address of GPE0_STS and GPE0_EN for Intel PCH LPT-LP.
// 
// 25    4/02/13 5:31a Wesleychen
// Update USBSB Template to 4.6.3_USB_08.10.26.
// 
// 23    1/22/13 5:00a Wesleychen
// Fix USB keyboard cannot work in DOS if LPT xHCI Mode = Enabled.
// 
// 22    1/14/13 10:05p Wesleychen
// Improve IsAllEhciDisabled().
// 
// 21    1/11/13 5:47a Wesleychen
// Fixed coding error.
// 
// 19    1/06/13 9:55p Wesleychen
// Update for Intel LPT RC 0.8.1. Turen on the SWSMI Timer when all EHCI
// controllers are disabled.
// 
// 18    12/20/12 8:11a Wesleychen
// [TAG]       EIP108635
// [Category]  Bug Fix
// [Severity]  Important
// [Symptom]   Lynx Point USB ports have no function in DOS when
//             all EHCIs are disabled and only xHCI exists.
// [RootCause] Legacy keyboard support is rely on EHCI H/W SMI to
//             trigger it, that is why the USB KB couldn't working
//             under DOS if you issue a warm boot from Windows 8 or
//             set "xHCI Mode" = "Enabled".
// [Solution]  Use SW Timer SMI to instead of EHCI H/W SMI.
// [Files]     usbsb.c
// 
// 15    10/31/12 2:11a Wesleychen
// Update for Intel PCH Lynx Point-LP support.
// 
// 13    6/05/12 2:13a Wesleychen
// Update USBSB Template to 4.6.3_USB_08.10.22.
// 
// 30    5/22/12 10:02a Ryanchou
// [TAG]          EIP90154
// [Category]      Improvement
// [Description]      Remove the USBSB_EnableSmmPeriodicSmi and
// USBSB_DisableSmmPeriodicSmi hooks.
// [Files]          amidef.h, amiusb.c, usb.c, usbsb.c
// 
// 29    5/04/12 6:36a Ryanchou
// [TAG]          EIP82875
// [Category]      Improvement
// [Description]      Support start/stop individual USB host to avoid
// reconnect issues.
// [Files]          usbport.c, usbsb.c, amiusb.c, amiusb.h, ehci.c, ohci.c,
// uhci.c, uhci.h, usb.c, usbdef.h, xhci.c, amiusbhc.c, uhcd.c, uhcd.h,
// usbbus.c, usbmisc.c
// 
// 28    5/03/12 6:31a Roberthsu
// [TAG]           EIP84455
// [Category]      Improvement
// [Description]   Implement usb hid device gencric.
// [Files]          amiusb.c,amiusbhc.c,efiusbhid.c,efiusbkb.c,ehci.c,ohci.c,uhc
// d.c,uhci.c,usbdef.h,usbhid.c,usbhub.c,usbkbd.c,usbkbd.h,usbms.c,usbsb.c
// ,usbsrc.sdl
// 
// 27    1/16/12 6:02a Ryanchou
// [TAG]          EIP81132
// [Description]      Add core version check for EIP80609 solution.
// [Files]          amiusb.c, usbrt.mak, usbsb.c
// 
// 26    1/14/12 4:11a Ryanchou
// [TAG]          EIP80609
// [Category]      Bug Fix
// [Severity]      Important
// [Symptom]      If to enable debug mode and set launch CSM is "Never" in
// setup, system will hang at 0xB1
// [RootCause]      The pointer AmiUsb is invalid if CSM is not launched,
// that may cause CPU exception.
// [Solution]      Added USB smm protocol, and use SmmLocateProtocol to get
// the pointer.
// [Files]          amiusb.c, AmiUsbController.h, usbrt.mak, usbsb.c
// 
// 25    11/08/11 2:02a Ryanchou
// [TAG]          EIP63188
// [Category]      Improvement
// [Description]      External USB controller support.
// [Files]          amidef.h, amiusb.c, ehci.c, ohci.c, uhcd.c, uhcd.h, uhci.c,
// usbdef.h, usbmisc.c, usbsb.c, xhci.c
// 
// 24    10/17/11 2:25a Ryanchou
// [TAG]          EIP69136
// [Category]      Improvement
// [Description]      Remove the dependency of EBDA in USB module for CSM
// disabling.
// [Files]          amiusb.c, uhcd.c, usbport.c, usbsb.c
// 
// 23    8/08/11 7:03a Ryanchou
// [TAG]          EIP54018
// [Category]      New Feature
// [Description]      Added USB S5 wake up support.
// [Files]          amiusb.c, ehci.c, ohci.c, uhci.c, usb.c, usb.sdl, usbdef.h,
// usbsb.c xhci.c
// 
// 22    7/15/11 6:33a Ryanchou
// [TAG]          EIP38434
// [Category]      New Feature
// [Description]      Added USB HID report protocol support.
// [Files]          amiusb.c, AmiUsbController.h, amiusbhc.c, efiusbkb.c,
// efiusbkb.h, efiusbpoint.c, ehci.c, ohci.c, uhcd.c uhcd.cif, uhci.c,
// usb.c, usbdef.h, usbhid.c, usbkbd.c, usbkbd.h, usbms.c, usbpoint.c,
// usbrt.cif, usbsb.c, usbsetup.c, usbsrc.sdl, xhci.c
// 
// 21    6/22/11 4:48a Ryanchou
// [TAG]          EIP61556
// [Category]      Improvement
// [Description]      Add both bitmapped and index based GPI number for
// better compatibility.
// [Files]          usbsb.c
// 
// 20    4/06/11 3:29a Ryanchou
// [TAG]          EIP55275
// [Category]      Bug Fix
// [Severity]      Important
// [Symptom]      EBDA:108 conflict
// [RootCause]      The EIP48064 save EFI_USB_PROTOCOL pointer in EBDA:108,
// but Keymon filter driver used the same location.
// [Solution]      Use the EBDA:32 to save EFI_USB_PROTOCOL pointer and add a
// signature in EFI_USB_PROTOCOL.
// [Files]          amidef.h, AmiUsbController.h, uhcd.c, usbsb.c
// 
// 19    3/29/11 10:23a Ryanchou
// [TAG]          EIP53518
// [Category]      Improvement
// [Description]      Added chipset xHCI chip support.
// [Files]          amiusb.c, amiusb.h, ehci.c, ohci.c, uhcd.c, uhci.c, usb.c,
// usb.sdl, usbdef.h, usbport, usbsb.c, xhci.c
// 
// 18    12/29/10 1:51a Ryanchou
// [TAG]          EIP50358
// [Category]      Bug Fix
// [Severity]      Important
// [Symptom]      System hang at "Starting Windows".
// [RootCause]      The EIP48064 modification save EFI_USB_PROTOCOL pointer
// to EBDA, if disable USB Support, the pointer will be 0.
// [Solution]      Check the pointer in EBDA before use it.
// [Files]          usbsb.c
// 
// 17    12/29/10 1:29a Ryanchou
// [TAG]          EIP50943
// [Category]      Bug Fix
// [Severity]      Minor
// [Symptom]      USB Keyboard abnormal
// [RootCause]      We only check the aUSBKBDeviceTable entry 0, if the value
// is 0, we will not send the characters to KBC.
// [Solution]      The solution is search all the aUSBKBDeviceTable. 
// [Files]          usbsb.c
// 
// 16    11/22/10 8:48a Ryanchou
// [TAG]          EIP48064
// [Category]      Improvement
// [Description]      The SB template implemented elink
// AcpiEnableCallbackList, the XHCI/EHCI hand off function should be
// invoked via the elink AcpiEnableCallbackList.
// [Files]          amidef.h, amiusb.c, amiusb.dxs, amiusb.h,
// AmiUsbController.h, usb.sdl, usbrt.mak, usbsb.c
// 
// 15    11/02/10 12:04a Tonylo
// EIP45564 - System hang when resume from S3.
// 
// 13    10/21/10 8:58a Ryanchou
// EIP44570: Added multiple xHCI SMI pin support. 
// 
// 12    10/07/10 10:12a Ryanchou
// EIP41379: Move the code that install xHCI hardware SMI handler in
// XHCI_Start function.
// 
// 11    8/31/10 11:32p Tonylo
// EIP43380 - BIOS build failed with WDK 7600.16385.1.
// 
// 10    7/13/10 7:09a Ryanchou
// EIP38356: Implement shutdown USB legacy support in ACPI enable call.
// 
// 9     7/13/10 5:32a Ryanchou
// EIP40732: Implement xHCI periodic timer handler to replace the XHCI HW
// SMI functionality.
// 
// 8     6/15/10 1:23a Ryanchou
// Implement xHCI USB Legacy Capability.
// 
// 7     4/29/10 10:07a Olegi
// 
// 6     4/14/10 5:42p Olegi
// Unnecessary code commented out, left for reference only.
// 
// 4     1/29/10 4:55p Olegi
// 
// 3     11/20/09 6:17p Olegi
// Sample implementation added.
// 
// 2     11/18/09 4:25p Olegi
// Copyright message update.
// 
// 1     2/19/08 2:32p Olegi
//
//****************************************************************************
//
//<AMI_FHDR_START>
//-----------------------------------------------------------------------------
//
//  Name:   USBSB.C
//
//  Description:    USB South Bridge Porting Hooks
//
//-----------------------------------------------------------------------------
//<AMI_FHDR_END>

//****************************************************************************

#include "Efi.h"
#include "token.h"
#include "amidef.h"
#include "usbdef.h"
#include "amiusb.h"
#include "usbkbd.h"
#include "AmiCspLib.h"
#include <Setup.h>

#ifndef USB_ACPI_ENABLE_CALLBACK

#include <Edk\Foundation\Framework\Protocol\SmmPeriodicTimerDispatch\SmmPeriodicTimerDispatch.h>
#include <Protocol\SmmGpiDispatch.h>

#ifdef USB_ACPI_ENABLE_DISPATCH
#include <Chipset\SB\AcpiModeEnable.h>

EFI_GUID    gEfiAcpiEnDispatchProtocolGuid = EFI_ACPI_EN_DISPATCH_PROTOCOL_GUID;
#endif

#include <AmiBufferValidationLib.h>
#include <AmiUsbSmmGlobalDataValidationLib.h>

// Timer service
EFI_GUID    gEfiSmmPeriodicTimerDispatchProtocolGuid = EFI_SMM_PERIODIC_TIMER_DISPATCH_PROTOCOL_GUID;
EFI_SMM_PERIODIC_TIMER_DISPATCH_PROTOCOL *gPeriodicTimerDispatch = NULL;
EFI_HANDLE  gPeriodicTimerHandle = NULL;
EFI_HANDLE  gUsbIntTimerHandle = NULL;

EFI_STATUS USBPort_PeriodicTimerCallBack (
  IN  EFI_HANDLE                                DispatchHandle,
  IN  EFI_SMM_PERIODIC_TIMER_DISPATCH_CONTEXT   *DispatchContext
  );

extern  USB_GLOBAL_DATA     *gUsbData;
extern  BOOLEAN gLockSmiHandler;
extern  BOOLEAN gLockHwSmiHandler;

UINT8   ByteReadIO (UINT16);
VOID    ByteWriteIO (UINT16, UINT8);
UINT32  ReadPCIConfig(UINT16, UINT8);

extern  UINT32      DwordReadMem(UINT32, UINT16);
extern  void        DwordWriteMem(UINT32, UINT16, UINT32);

#ifndef GP_IOREG_GPI_ROUT2
#define GP_IOREG_GPI_ROUT2 0x34
#endif

#ifndef ICH_LP_IOREG_GPE0_STS
#define ICH_LP_IOREG_GPE0_STS ACPI_PCHLP_IOREG_GPE0_STS + 0x0c
#endif

#ifndef ICH_LP_IOREG_GPE0_EN
#define ICH_LP_IOREG_GPE0_EN ACPI_PCHLP_IOREG_GPE0_EN + 0x0c
#endif

#define PCH_NON_LPT 0x00  // Non Lynx Point Series
#define PCH_LPT_H   0x01  // Lynx Point 2 Chip
#define PCH_LPT_LP  0x02  // Lynx Point LP

UINT8 IsLynxPoint ( VOID )
{
  UINT32  LpcId;
  UINT16  LpcBusDevFunc = (0 << 8) + (0x1F << 3) + 0;

  LpcId = ReadPCIConfig(LpcBusDevFunc, 0);

  if (((UINT16)(LpcId >> 16) & 0xFF00) == 0x8C00)
    return PCH_LPT_H;

  if (((UINT16)(LpcId >> 16) & 0xFF00) == 0x9C00)
    return PCH_LPT_LP;

  return PCH_NON_LPT;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Function:    USBSB_PeriodicTimerCallBack
//
// Description:
//  This function is registers periodic timer callbacks.
//
// Input:
//  Pointer to the EFI System Table
//
// Output:
//  - EFI_SUCCESS if timers are initialized or function is not implemented
//  - timer initialization error
//
// Note:
//  If function is not implemented (timers are not needed for this chipset),
//  function must return EFI_SUCCESS
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
USBSB_PeriodicTimerCallBack (
  IN  EFI_HANDLE                    DispatchHandle,
  IN  EFI_SMM_PERIODIC_TIMER_DISPATCH_CONTEXT   *DispatchContext
  )
{
    DEV_INFO*       fpDevInfo;
    int i;
    DEV_INFO* pDev = gUsbData->aDevInfoTable;
    EFI_STATUS      Status = EFI_SUCCESS;

    if (gLockSmiHandler == TRUE) {
        return EFI_SUCCESS;
    }
#if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x0001000A)&&(CORE_COMBINED_VERSION >= 0x4028B)
    Status = AmiUsbSmmGlobalDataValidation(gUsbData);

    ASSERT_EFI_ERROR(Status);
    
    if (EFI_ERROR(Status)) {
        gLockHwSmiHandler = TRUE;
        gLockSmiHandler = TRUE;
        return EFI_SUCCESS;
    }
#endif

    for (i = 0; i < USB_DEV_HID_COUNT; i++) {
        fpDevInfo = gUsbData->aUSBKBDeviceTable[i];
        if (fpDevInfo != NULL) break;
    }
    if(fpDevInfo == NULL){
        for (i = 1; i < MAX_DEVICES;  ++i, ++pDev ){
#if USB_DRIVER_BUILD_VER > 29
            if ( (pDev->Flag & DEV_INFO_VALID_STRUC) != 0 &&
#else
            if ( (pDev->bFlag & DEV_INFO_VALID_STRUC) != 0 &&
#endif
                pDev->bDeviceType == BIOS_DEV_TYPE_HID &&
#if USB_DRIVER_BUILD_VER > 28
                (pDev->HidDevType & HID_DEV_TYPE_MOUSE) ) {     //(EIP84455)
#else
                (pDev->bSubDeviceType & SUB_DEV_TYPE_MOUSE) ) {     //(EIP84455)
#endif
                fpDevInfo= pDev;    
                break; 
            }
        }
    }

    if (fpDevInfo != NULL){
        USBKBDPeriodicInterruptHandler(gUsbData->HcTable[fpDevInfo->bHCNumber - 1]);
    }
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        USBSB_InstallXhciHwSmiHandler
//
// Description:
//  This function registers XHCI hardware SMI callback function.
//
// Note:
//  Currently EHCI, UHCI and OHCI drivers install their SMI handlers in the
//  corresponding Start functions. In the future all code related to SMI
//  registration can be moved here.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
USBSB_InstallXhciHwSmiHandler()
{
    EFI_STATUS  Status = EFI_SUCCESS;
    EFI_HANDLE    Handle = NULL;

#if	XHCI_SUPPORT
#if XHCI_EVENT_SERVICE_MODE != 0
//GPI service
    EFI_SMM_GPI_DISPATCH_PROTOCOL  *GpiDispatch = NULL;
    EFI_SMM_GPI_DISPATCH_CONTEXT   Context;
    
    UINT8    HwSmiPinTable[] = {USB_XHCI_EXT_HW_SMI_PINS};
    UINT8    i;
    UINT32   Buffer32;

    Status = pBS->LocateProtocol (&gEfiSmmGpiDispatchProtocolGuid, NULL, &GpiDispatch);
    ASSERT_EFI_ERROR(Status);    // driver dependencies?

    if (!EFI_ERROR(Status)) {
      for (i = 0; i < sizeof(HwSmiPinTable)/sizeof(UINT8); i++) {
        if(HwSmiPinTable[i] == 0xFF) continue;
                                        //(EIP61556)>
        Context.GpiNum = HwSmiPinTable[i];
                                        //<(EIP61556)
        GpiDispatch->Register(GpiDispatch, XhciHwSmiHandler, &Context, &Handle);
        if (IsLynxPoint() == PCH_LPT_LP) {
          Buffer32 = IoRead32(GPIO_BASE_ADDRESS + GP_IOREG_GPI_ROUT2);
          Buffer32 &= ~(3 << (Context.GpiNum * 2));
          Buffer32 |= (1 << (Context.GpiNum * 2));
          IoWrite32(GPIO_BASE_ADDRESS + GP_IOREG_GPI_ROUT2, Buffer32);
        } else {
          // Set GPIO_ROUTx = SMI# (B0:D31:F0 B8h[31:0])
          Buffer32 = DwordReadMem(SB_PCIE_CFG_ADDRESS(SB_BUS, SB_DEV, SB_FUN, 0), SB_REG_GPI_ROUT);
          Buffer32 &= ~(3 << (Context.GpiNum * 2));
          Buffer32 |= (1 << (Context.GpiNum * 2));
          DwordWriteMem(SB_PCIE_CFG_ADDRESS(SB_BUS, SB_DEV, SB_FUN, 0), SB_REG_GPI_ROUT, Buffer32);
        }
      }
    }
#endif

#if XHCI_EVENT_SERVICE_MODE != 1
    Status = USBSB_InstallUsbIntTimerHandler();
#endif
#endif

    return Status;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        UsbIntTimerCallBack
//
// Description:
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
UsbIntTimerCallBack (
  IN  EFI_HANDLE                    DispatchHandle,
  IN  EFI_SMM_PERIODIC_TIMER_DISPATCH_CONTEXT   *DispatchContext
)
{
	HC_STRUC*   HcStruc;
	UINT8		i;
    EFI_STATUS  Status;

    if (gLockSmiHandler == TRUE) {
        return;
    }
#if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x0001000A)&&(CORE_COMBINED_VERSION >= 0x4028B)
    Status = AmiUsbSmmGlobalDataValidation(gUsbData);

    ASSERT_EFI_ERROR(Status);
    
    if (EFI_ERROR(Status)) {
        gLockHwSmiHandler = TRUE;
        gLockSmiHandler = TRUE;
        return;
    }
#endif

    for (i = 0; i < gUsbData->HcTableCount; i++) {
	    HcStruc = gUsbData->HcTable[i];
        if (HcStruc == NULL) {
            continue;
        }
	    if((HcStruc->dHCFlag & (HC_STATE_EXTERNAL | HC_STATE_RUNNING)) == 
			(HC_STATE_EXTERNAL | HC_STATE_RUNNING)) {
	        (*gUsbData->aHCDriverTable[
				GET_HCD_INDEX(HcStruc->bHCType)].pfnHCDProcessInterrupt)(HcStruc);
	    }
	}
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        USBSB_InstallUsbIntTimerHandler
//
// Description:
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
USBSB_InstallUsbIntTimerHandler()
{
    EFI_STATUS  Status;
    EFI_SMM_PERIODIC_TIMER_DISPATCH_CONTEXT  TimerContext;
    UINT64      *SmiTickInterval;

    if (gUsbIntTimerHandle != NULL) {
        return EFI_SUCCESS;
    }

    Status = pBS->LocateProtocol (
            &gEfiSmmPeriodicTimerDispatchProtocolGuid, 
            NULL, 
            &gPeriodicTimerDispatch);
    ASSERT_EFI_ERROR(Status);    // driver dependencies?

    if (!EFI_ERROR(Status)) {
        TimerContext.Period = 160000;    //16ms 
        TimerContext.SmiTickInterval = 160000; 
        TimerContext.ElapsedTime = 0;
        SmiTickInterval = NULL;
        //Check SmiTickInterval that are supported by the chipset.
		do {
            Status = gPeriodicTimerDispatch->GetNextShorterInterval(
                                           gPeriodicTimerDispatch,
                                           &SmiTickInterval
                                           );
            if (EFI_ERROR(Status)) {
                break;
            }
            if (SmiTickInterval != NULL) {
                if (*SmiTickInterval <= TimerContext.SmiTickInterval) {
                    TimerContext.SmiTickInterval = *SmiTickInterval; 
                    break;
                }
            }
        } while (SmiTickInterval != NULL);

        Status = gPeriodicTimerDispatch->Register (
                        gPeriodicTimerDispatch, 
                        UsbIntTimerCallBack, 
                        &TimerContext,
                        &gUsbIntTimerHandle);
        ASSERT_EFI_ERROR(Status);
    }

    return Status;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        USBSB_UninstallTimerHandlers
//
// Description: This function unregisters all the periodic timer handles.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
USBSB_UninstallTimerHandlers()
{
    EFI_STATUS  Status = EFI_SUCCESS;

    if (gPeriodicTimerDispatch == NULL) {
        return Status;
    }

    if (gUsbIntTimerHandle) {
        Status = gPeriodicTimerDispatch->UnRegister (
                        gPeriodicTimerDispatch, 
                        gUsbIntTimerHandle);
        ASSERT_EFI_ERROR(Status);

        gUsbIntTimerHandle = NULL;
    }

    if (gPeriodicTimerHandle) {
        Status = gPeriodicTimerDispatch->UnRegister (
                        gPeriodicTimerDispatch, 
                        gPeriodicTimerHandle);
        ASSERT_EFI_ERROR(Status);

        gPeriodicTimerHandle = NULL;
    }

    return Status;
}

#ifdef USB_ACPI_ENABLE_DISPATCH
//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        AcpiEnableCallBack
//
// Description:
//  This is ACPI mode enable callback function. It is a workaround for non 
//    XHCI/EHCI aware OSes.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
AcpiEnableCallBack(
    IN EFI_HANDLE   DispatchHandle
)
{
    USB_StopUnsupportedHc();
    gUsbData->dUSBStateFlag |= USB_FLAG_RUNNING_UNDER_OS;
    gLockSmiHandler = TRUE;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        RegisterAcpiEnableCallBack
//
// Description:
//  This function registers ACPI enable callback function.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
RegisterAcpiEnableCallBack(
    IN EFI_EVENT    Event,
    IN VOID            *Context
)
{
    EFI_STATUS  Status;
    EFI_HANDLE    Handle;

    EFI_ACPI_DISPATCH_PROTOCOL    *AcpiEnDispatch;

    Status = pBS->LocateProtocol(&gEfiAcpiEnDispatchProtocolGuid, NULL, &AcpiEnDispatch);
    if (EFI_ERROR(Status)) return Status;

    Status = AcpiEnDispatch->Register(AcpiEnDispatch, AcpiEnableCallBack, &Handle);
    ASSERT_EFI_ERROR(Status);

    return Status;
}
#endif

BOOLEAN IsAllEhciDisabled ( VOID )
{
  UINT32      XhciDID;
  UINT16      XhciBusDevFunc = (0 << 8) + (0x14 << 3) + 0;
  EFI_STATUS  Status; 
  SETUP_DATA  SetupData;
  EFI_GUID    SetupGuid = SETUP_GUID;
  UINTN       VarSize;

  XhciDID = ReadPCIConfig(XhciBusDevFunc, 0);

  if (((UINT16)(XhciDID >> 16) == 0x8C31) || \
      ((UINT16)(XhciDID >> 16) == 0x8CB1) || \
      ((UINT16)(XhciDID >> 16) == 0x9CB1) || \
      ((UINT16)(XhciDID >> 16) == 0x9C31)) {

    VarSize = sizeof(SETUP_DATA);
    Status = pRS->GetVariable(
                    L"Setup",
                    &SetupGuid,
                    NULL,
                    &VarSize,
                    &SetupData );
    if (!EFI_ERROR(Status)) {
      if ((SetupData.PchUsb30Mode == 1) || \
          ((SetupData.PchUsb20[0] == 0) && \
          (SetupData.PchUsb20[1] == 0)))
        return TRUE;
    }
  }

  return FALSE;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        USBSB_InstallSmiEventHandlers
//
// Description:
//  This function is called from USBRT entry point inside SMM. Any SMI handlers
//  registration related to USB driver can be done here.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
USBSB_InstallSmiEventHandlers(VOID)
{
    EFI_STATUS  Status = EFI_SUCCESS;


#if USB_HID_KEYREPEAT_USE_SETIDLE == 0
    EFI_SMM_PERIODIC_TIMER_DISPATCH_CONTEXT  PeriodicTimerContext;

    if (IsLynxPoint() != PCH_NON_LPT) {

      // [Lynx point] Register Timer SMI if all EHCI controllers are disabled.
      if (!IsAllEhciDisabled()) return Status;

      Status = pBS->LocateProtocol (
              &gEfiSmmPeriodicTimerDispatchProtocolGuid, 
              NULL, 
              &gPeriodicTimerDispatch);
      ASSERT_EFI_ERROR(Status);   // driver dependencies?

      if (!EFI_ERROR(Status)) {
          PeriodicTimerContext.Period = 160000;   //16ms 
          PeriodicTimerContext.SmiTickInterval = 160000; 
          PeriodicTimerContext.ElapsedTime = 0;

          Status = gPeriodicTimerDispatch->Register (
                          gPeriodicTimerDispatch, 
                          USBSB_PeriodicTimerCallBack, 
                          &PeriodicTimerContext,
                          &gPeriodicTimerHandle);
          ASSERT_EFI_ERROR(Status);
      }
      if (EFI_ERROR(Status)) {
          gPeriodicTimerDispatch = NULL;
      }
    }

#endif

#ifdef USB_ACPI_ENABLE_DISPATCH
    {
        EFI_ACPI_DISPATCH_PROTOCOL    *AcpiEnDispatch;
        EFI_EVENT    Event;
        VOID        *Reg;
    
        Status = pBS->LocateProtocol(&gEfiAcpiEnDispatchProtocolGuid, NULL, &AcpiEnDispatch);
        if(!EFI_ERROR(Status)) {
            RegisterAcpiEnableCallBack(NULL, NULL);
        } else {
            Status = RegisterProtocolCallback(
                            &gEfiAcpiEnDispatchProtocolGuid,
                            RegisterAcpiEnableCallBack,
                            NULL,
                            &Event,
                            &Reg);
            ASSERT_EFI_ERROR(Status);
        }
    }
#endif
    return Status;
}
                                        //(EIP54018+)>
#if USB_S5_WAKEUP_SUPPORT
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name:        UsbSbEnablePme
//
// Description: 
//  The funciton enable usb PME
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
UsbSbEnablePme(VOID)
{
    // Disable USB Wake on Device Connect/Disconnect
    *(UINT32*)(SB_RCBA + RCRB_MMIO_RMHWKCTL)= 0x33;

    // Clear PM1_STS
    IoWrite16(PM_BASE_ADDRESS, IoRead16(PM_BASE_ADDRESS));
    if (IsLynxPoint() == PCH_LPT_LP) {
      // Clear GPE0_STS
      IoWrite32(PM_BASE_ADDRESS + ICH_LP_IOREG_GPE0_STS, 0xFFFFFFFF);        // PMBASE + 8Ch
      IoWrite32(PM_BASE_ADDRESS + ICH_LP_IOREG_GPE0_STS - 0x04, 0xFFFFFFFF); // PMBASE + 88h
      IoWrite32(PM_BASE_ADDRESS + ICH_LP_IOREG_GPE0_STS - 0x08, 0xFFFFFFFF); // PMBASE + 84h
      IoWrite32(PM_BASE_ADDRESS + ICH_LP_IOREG_GPE0_STS - 0x0C, 0xFFFFFFFF); // PMBASE + 80h
      // Set PME_B0_EN and PME_EN
      IoWrite16(PM_BASE_ADDRESS + ICH_LP_IOREG_GPE0_EN, BIT13 + BIT11);      // PMBASE + 9Ch
    } else {
      // Clear GPE0_STS
      IoWrite32(PM_BASE_ADDRESS + ICH_IOREG_GPE0_STS, 0xFFFFFFFF);        // PMBASE + 20h
      IoWrite32(PM_BASE_ADDRESS + ICH_IOREG_GPE0_STS + 0x04, 0xFFFFFFFF); // PMBASE + 24h
      // Set PME_B0_EN and PME_EN (PMBASE + 28h)
      IoWrite16(PM_BASE_ADDRESS + ICH_IOREG_GPE0_EN, BIT13 + BIT11);      // PMBASE + 28h
    }
    // Clear PCI Express Wake Disable    
    IoWrite16(PM_BASE_ADDRESS + ACPI_IOREG_PM1_EN,
              IoRead16(PM_BASE_ADDRESS + ACPI_IOREG_PM1_EN & ~BIT14));
}

#endif
                                        //<(EIP54018+)
#else

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        UsbAcpiEnableCallBack
//
// Description:
//  This is ACPI mode enable callback function. It is a workaround for non 
//    XHCI/EHCI aware OSes.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
UsbAcpiEnableCallBack(
    IN EFI_HANDLE                    DispatchHandle,
    IN EFI_SMM_SW_DISPATCH_CONTEXT    *DispatchContext
)
{
#if (defined(PI_SPECIFICATION_VERSION) && (PI_SPECIFICATION_VERSION>=0x0001000A)) && defined(SMM_BUILD)
    EFI_STATUS                Status;
    AMI_USB_SMM_PROTOCOL    *UsbSmmProtocol = NULL;

    Status = pSmst->SmmLocateProtocol(&gAmiUsbSmmProtocolGuid, NULL, &UsbSmmProtocol);
    if (EFI_ERROR(Status)) {
        return;
    }

    UsbSmmProtocol->UsbStopUnsupportedHc();

#else
    EFI_USB_PROTOCOL    *AmiUsb = NULL;
    UINT16                EbdaSeg = *((UINT16*)0x40E);

    AmiUsb = *(EFI_USB_PROTOCOL **)(UINTN)(((UINT32)EbdaSeg << 4) + USB_PROTOCOL_EBDA_OFFSET);
                                        //(EIP50358)>
    if (AmiUsb && AmiUsb->Signature == 0x50425355) {    //USBP    //(EIP55275)
        AmiUsb->UsbStopUnsupportedHc();
    }
                                        //<(EIP50358)
#endif
}

#endif

//****************************************************************************
//****************************************************************************
//**                                                                        **
//**             (C)Copyright 1985-2013, American Megatrends, Inc.          **
//**                                                                        **
//**                          All Rights Reserved.                          **
//**                                                                        **
//**             5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093          **
//**                                                                        **
//**                          Phone (770)-246-8600                          **
//**                                                                        **
//****************************************************************************
//****************************************************************************
