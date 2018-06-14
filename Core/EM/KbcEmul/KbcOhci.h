//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/KbcEmulation/ALASKA/KBCEMUL/KbcOhci.h 3     12/05/13 12:46a Srikantakumarp $
//
// $Revision: 3 $
//
// $Date: 12/05/13 12:46a $
//
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/KbcEmulation/ALASKA/KBCEMUL/KbcOhci.h $
// 
// 3     12/05/13 12:46a Srikantakumarp
// [TAG]  		EIP145881
// [Category]  	Improvement
// [Description]  	Ohci Emulation support needs to be extended for the
// chipset , where the HCE registers defined in some fixed Memory for
// Aptio 4.x
// [Files]  		KbcEmul.sdl, KbcOhci.c, KbcOhci.h
// 
// 2     2/10/11 1:15a Rameshr
// [TAG]  		EIP53687
// [Category]  	Improvement
// [Description]  	AMI headers update for KbcEmulation Module
// [Files]  		KbcEmul.mak,KbcEmul.dxs,KbcEmul.c,KbcEmul.h,KbcEmulLib.h,Kbc
// EmulLib.c,Kbc.h,KbcDevEmul.h,Kbccore.c,Legacykbc.c,Legacykbd.c,LegacyMo
// use.c,VirtualKbc.c,VirtualKbd.c,VirtualMouse.c,Ap4x.h,Ap4x.c,KbcUhci.c,
// KbcUhci.h,KbcEmulIrq.c, KbcOhci.c, Kbcohci.h
// 
// 1     7/08/10 2:07a Rameshr
// Ohci Emulation support Added.
// EIP 39712
// 
// Initial Check-in
//
//**********************************************************************

//**********************************************************************
//<AMI_FHDR_START>
//
// Name:    KbcOhci.h
//
// Description: Header file for OCHI controller for Emulation
//
//<AMI_FHDR_END>
//**********************************************************************

typedef enum {
  UNSUPPORTED = -1,
  USB1_1 = 0,
  USB1_2,
  USB1_3,
  USB1_4,
  USB2_1,
  NUMBER_USB_CONTROLLERS
} SUPPORTED_USB_CONTROLLERS;

typedef enum {
	PciDevice,
	FixedMemory
} EMUL_DEV_TYPE;

typedef struct {
	EMUL_DEV_TYPE	Type;
    UINT16      BusDevFunc;
	UINTN		MemAddr;
} OHCI_EMUL_DEVICE;

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


#define PCIBUS(x)           ( x << 16)
#define PCIDEV(x)           ( x << 11)
#define PCIFUNC(x)          ( x << 8)


#define PCIOFF_MASK         0x000000FF
#define PCIFUNC_MASK        0x0000FF00
#define PCIDEV_MASK         0x00FF0000
#define PCIBUS_MASK         0xFF000000

// OHCI emulation register equates
#define     OHCI_HCE_CONTROL        0x100
#define     OHCI_HCE_INPUT          0x104
#define     OHCI_HCE_OUTPUT         0x108
#define     OHCI_HCE_STATUS         0x10C

#pragma pack(push, 1)

typedef struct {
	UINT32	HceControl;
	UINT32	HceInput;
	UINT32	HceOutput;
	UINT32	HceStatus;
} OHCI_LEG_SUP_REGS;

#pragma pack(pop)

// Bit definitions for emulation registers
#define     HCE_CNTRL_EMULATION_ENABLE      BIT0
#define     HCE_CNTRL_EMULATION_INTERRUPT   BIT1
#define     HCE_CNTRL_CHARACTER_PENDING     BIT2
#define     HCE_CNTRL_IRQ_ENABLE            BIT3
#define     HCE_CNTRL_EXT_IRQ_ENABLE        BIT4
#define     HCE_CNTRL_GA20_SEQ              BIT5
#define     HCE_CNTRL_IRQ1_ACTIVE           BIT6
#define     HCE_CNTRL_IRQ12_ACTIVE          BIT7
#define     HCE_CNTRL_A20_STATE             BIT8


#define     HCE_STS_OUTPUTFULL      BIT0
#define     HCE_STS_INPUTFULL       BIT1
#define     HCE_STS_FLAG            BIT2
#define     HCE_STS_CMDDATA         BIT3
#define     HCE_STS_INHIBIT_SWITCH  BIT4
#define     HCE_STS_AUXOUTPUTFULL   BIT5
#define     HCE_STS_TIMEOUT         BIT6
#define     HCE_STS_PARITY          BIT7


BOOLEAN     Ohci_HasTrapStatus();
BOOLEAN     Ohci_TrapEnable(BOOLEAN);
BOOLEAN     NonSmmOhci_TrapEnable(BOOLEAN);
BOOLEAN     GetRMhStatus ();

UINT16      GetHceControl();
void        SetHceControl (UINT16);
void        SetHceOutput (UINT8);
UINT8       GetHceOutput();
UINT8       GetHceStatus();
void        SetHceStatus (UINT8);
UINT8       GetHceInput();

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************