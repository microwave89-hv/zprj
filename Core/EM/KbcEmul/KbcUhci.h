//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/KbcEmulation/ALASKA/KBCEMUL/KbcUhci.h 7     5/13/13 2:51a Rameshr $
//
// $Revision: 7 $
//
// $Date: 5/13/13 2:51a $
//
//****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/KbcEmulation/ALASKA/KBCEMUL/KbcUhci.h $
// 
// 7     5/13/13 2:51a Rameshr
// [TAG]  		EIP119870
// [Category]  	Improvement
// [Description]  	Build error with KbcEmulation module if update USB
// module label 4.6.3_USB_08.10.26
// [Files]  		KbcEmul.Mak, KbcEmul.SDl, KbcUhci.c, KbcUhci.h, KbcOhci.c
// 
// 6     2/10/11 1:11a Rameshr
// [TAG]  		EIP53687
// [Category]  	Improvement
// [Description]  	AMI headers update for KbcEmulation Module
// [Files]  		KbcEmul.mak,KbcEmul.dxs,KbcEmul.c,KbcEmul.h,KbcEmulLib.h,Kbc
// EmulLib.c,Kbc.h,KbcDevEmul.h,Kbccore.c,Legacykbc.c,Legacykbd.c,LegacyMo
// use.c,VirtualKbc.c,VirtualKbd.c,VirtualMouse.c,Ap4x.h,Ap4x.c,KbcUhci.c,
// KbcUhci.h,KbcEmulIrq.c, KbcOhci.c, Kbcohci.h
// 
// 5     7/08/10 2:07a Rameshr
// Function Output parameter changed for OHCI emulation support.
// 
// 4     6/30/09 11:36a Rameshr
// Coding Standard and File header updated.
// 
// 3     6/01/09 10:03a Rameshr
// Added Emulation Support for RMH enable/Disable
// EIP 21131
// 
// 2     2/05/09 9:44a Rameshr
// Symptom : With Latest CSM Emulation doesn't work.
// Solution: Added Emulation enable code in outside SMM. This is called
// from Uhcd.c when ever USB mode changes to Legacy
// EIP:18730
// 
// 1     12/14/07 10:26a Rameshraju
// Initial Check-in
//****************************************************************************

//<AMI_FHDR_START>
//****************************************************************************
// Name:        KbcUhci.c
//
// Description: Header file for UCHI controller for Emulation
//
//****************************************************************************
//<AMI_FHDR_END>

typedef enum {
  UNSUPPORTED = -1,
  USB1_1 = 0,
  USB1_2,
  USB1_3,
  USB1_4,
  USB2_1,
  NUMBER_USB_CONTROLLERS
} SUPPORTED_USB_CONTROLLERS;

typedef struct {
    UINT16      BusDevFunc;
    UINT8       InterfaceType;
    UINT8       SubClassCode;
    UINT8       BaseClassCode;
    UINT8       LegacyRegOffset;
} UHCI_EMUL_DEVICE;

typedef struct _FULL_USB_DEVICE_PATH
{
  ACPI_HID_DEVICE_PATH acpi;
  PCI_DEVICE_PATH pci;
  EFI_DEVICE_PATH_PROTOCOL end;
} FULL_USB_DEVICE_PATH;

#define ACPI_PATH_MACRO \
    {{ACPI_DEVICE_PATH,ACPI_DP,ACPI_DEVICE_PATH_LENGTH}, EISA_PNP_ID(0x0A03),0}

#define PCI_PATH_MACRO(Device,Function) \
    {{HARDWARE_DEVICE_PATH, HW_PCI_DP, HW_PCI_DEVICE_PATH_LENGTH}, (Function),(Device)}

#define END_PATH_MACRO \
    {END_DEVICE_PATH,END_ENTIRE_SUBTYPE,END_DEVICE_PATH_LENGTH}

#define USB1_1_DEVICE_PATH   \
    { ACPI_PATH_MACRO, PCI_PATH_MACRO(0x1d, 0), END_PATH_MACRO }

//
// Trap Dispatcher
//
//
typedef struct _TRAPDISPATCH {
    UINT16 status_bit;
    void (* trap_function)();
} TRAPDISPATCH;


#define UHCI_SMIBYENDPS     (UINT16)(1U << 15)
#define UHCI_USBPIRQEN      (UINT16)(1U << 13)
#define UHCI_SMIBYUSB       (UINT16)(1U << 12)
#define UHCI_TRAPBY64W      (UINT16)(1U << 11)
#define UHCI_TRAPBY64R      (UINT16)(1U << 10)
#define UHCI_TRAPBY60W      (UINT16)(1U << 9)
#define UHCI_TRAPBY60R      (UINT16)(1U << 8)
#define UHCI_SMIATENDPS     (UINT16)(1U << 7)
#define UHCI_PSTATE         (UINT16)(1U << 6)
#define UHCI_A20PASSEN      (UINT16)(1U << 5)
#define UHCI_USBSMIEN       (UINT16)(1U << 4)
#define UHCI_64WEN          (UINT16)(1U << 3)
#define UHCI_64REN          (UINT16)(1U << 2)
#define UHCI_60WEN          (UINT16)(1U << 1)
#define UHCI_60REN          (UINT16)(1U )

#define PCIBUS(x)           ( x << 16)
#define PCIDEV(x)           ( x << 11)
#define PCIFUNC(x)          ( x << 8)

BOOLEAN     Uhci_HasTrapStatus();
BOOLEAN     Uhci_TrapEnable(BOOLEAN);
BOOLEAN     NonSmmUhci_TrapEnable(BOOLEAN);

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
