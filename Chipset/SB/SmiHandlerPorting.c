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
// $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/SmmChildDispatcher/SmiHandlerPorting.c 6     3/19/13 8:21a Scottyang $
//
// $Revision: 6 $
//
// $Date: 3/19/13 8:21a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/SmmChildDispatcher/SmiHandlerPorting.c $
// 
// 6     3/19/13 8:21a Scottyang
// [TAG]  		EIP118158
// [Category]  	Improvement
// [Description]  	Correct SBLib_CmosRead () offset.
// [Files]  		SmiHandlerPorting2.c, SBDxe.c, SBGeneric.c, SBSmm.c,
// SmiHandlerPorting.c
// 
// 5     11/06/12 8:10a Scottyang
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Reduce function "GetPchSeries()".
// [Files]  		SBPEI.c, SBDxe.c, SmiHandlerPorting.c, SmiHandlerPorting2.c
// 
// 4     9/26/12 4:00a Victortu
// [TAG]           None
// [Category]      Improvement
// [Description]   Update for PCH LP GPIO compatible.
// [Files]         SB.sdl, SB.H, AcpiModeEnable.c, AcpiModeEnable.sdl,
// SBDxe.c, SBGeneric.c, SBPEI.c, SBSMI.c, SleepSmi.c,
// SmiHandlerPorting.c, SmiHandlerPorting2.c
// 
// 3     7/27/12 6:15a Victortu
// [TAG]           None
// [Category]      Improvement
// [Description]   Update to support ULT Platform.
// [Files]         SB.H, SB.mak, SB.sdl, SB.sd, SBSetup.c,
// AcpiModeEnable.c, SBDxe.c, SBPEI.c, SBSMI.c, SleepSmi.c,
// SmiHandlerPorting.c, SmiHandlerPorting2.c, SBPPI.h, Pch.sdl
// 
// 2     4/25/12 9:33a Victortu
// 
// [TAG]         None
// [Category]    Improvement
// [Description] Reprogram SMM ChildDispatcher drivers.
// [Files]       SmiHandlerGeneric.c; SmiHandlerPorting.c;
// SmiHandlerGeneric2.c; SmmChildDispatch2Main.c; SmmChildDispatcher2.mak;
// SmmChildDispatcher2.sdl; SmmChildDispatch.h; SmmChildDispatchMain.c;
// SmmChildDispatchProtocol.c; SmmChildDispatcher.dxs;
// PchSmiDispatcher.sdl
// 
// [TAG]         EIP73033
// [Category]    Improvement
// [Description] 'PciDevicePath' used in GetControllerType(),
// conditionally not set.
// [Files]       SmiHandlerPorting.c; SmiHandlerPorting2.c
// 
// 1     2/08/12 8:27a Yurenlai
// Intel Lynx Point/SB eChipset initially releases.
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:        SmiHandlerPorting.c
//
// Description: This file contains SMM Child Dispatcher porting functions
//
//<AMI_FHDR_END>
//*************************************************************************

//---------------------------------------------------------------------------
// Include(s)
//---------------------------------------------------------------------------

#include <Token.h>
#include <AmiDxeLib.h>
#include <AmiCspLib.h>
#include <AmiSmm.h>
#include "SmmChildDispatch.h"

//---------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//---------------------------------------------------------------------------
// Constant Definition(s)

// Macro Definition(s)

// Type Definition(s)

// Function Prototype(s)

//---------------------------------------------------------------------------
// Variable and External Declaration(s)
//---------------------------------------------------------------------------
// Variable Declaration(s)

UINT64 gSupportedIntervals[] = {
    // Porting required - put all available intervals here (in Nanoseconds)
#if SWSMI_TIMER_INSTEAD
     15000, // 1.5ms
    160000, // 16 ms
    320000, // 32 ms
    640000, // 64 ms
#else
    600000000, // 60 Seconds
    320000000, // 32 Seconds
    160000000, // 16 Seconds
     80000000, //  8 Seconds
#endif

    // Terminator record 
    0
};

// GUID Definition(s)

// Protocol Definition(s)

// External Declaration(s)

extern EFI_SMM_SYSTEM_TABLE *pSmst;

// Function Definition(s)

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//                       All purpose SMI Porting hooks 
//---------------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   IsAcpi
//
// Description: This function determines if the system is in ACPI mode.
//
// Input:       None
//
// Output:      BOOLEAN
//                  TRUE  - It is in ACPI mode
//                  FALSE - It is not in ACPI mode
//
// Notes:       Porting required
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN IsAcpi (VOID)
{
    return (READ_IO16_PM(ACPI_IOREG_PM1_CNTL) & 1) ? TRUE : FALSE; // 0x04
};

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   IsMe
//
// Description: This function checks whether the specific SMI event is raised
//
// Input:       CheckBitNo - The bit number for the specific SMI.
//
// Output:      BOOLEAN
//                  TRUE  - It is the specific SMI event
//                  FALSE - It is not the specific SMI event
//
// Notes:       Porting required
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN IsMe (
    IN UINT8        CheckBitNo )
{
    volatile UINT32 Buffer32 = READ_IO32_PM(ACPI_IOREG_SMI_EN); // 0x30  

    Buffer32 &= READ_IO32_PM(ACPI_IOREG_SMI_STS); // 0x34
    return (Buffer32 & (UINT32)(1 << CheckBitNo)) ? TRUE : FALSE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   ClearAllSmi
//
// Description: This function clears all SMI's and issues an EOS (End of SMI).
//
// Input:       None
//
// Output:      None
//
// Notes:       If you are porting INTEL chipset and have to support SWSMI
//              Timer SMI, you must be unable to clear the SWSMI status in
//              this routine.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID ClearAllSmi (VOID)
{
    // Porting Required. Program to clear ALL SMI status bit
    if ( !IsAcpi() ) {
        if (READ_IO16_PM(ACPI_IOREG_PM1_EN) & 0x400)
            if (READ_IO16_PM(ACPI_IOREG_PM1_STS) & 0x400)
                SBLib_CmosRead(0x0C);
        WRITE_IO16_PM(ACPI_IOREG_PM1_STS, 0xcc31);  // 0x00
        if (GetPchSeries() == PchLp) {
          WRITE_IO32_PM(ACPI_PCHLP_IOREG_GPE0_STS+0x0c, 0xffffffff); // 0x8C
          WRITE_IO32(GPIO_BASE_ADDRESS + GP_IOREG_ALTGP_SMI_STS, 0xffffffff); // 0x50
        } else {
          WRITE_IO32_PM(ACPI_IOREG_GPE0_STS, 0xffffffff); // 0x20
          WRITE_IO32_PM(ACPI_IOREG_GPE0_STS+4, 0xffffffff); // 0x24
          WRITE_IO16_PM(ACPI_IOREG_ALTGP_SMI_STS, 0xffff); // 0x3A
        }
        WRITE_IO16_PM(ACPI_IOREG_DEVACT_STS, 0xffff); // 0x44
        WRITE_IO16_TCO(TCO_IOREG_STS1, 0xffff); // 0x04
        WRITE_IO16_TCO(TCO_IOREG_STS2, 0xfffe); // 0x06 (Except Intruder Det)
        WRITE_IO32_PM(ACPI_IOREG_SMI_STS, 0xffffffbf); // 0x34 (Except SWSMI)
        if ((READ_IO16_TCO(TCO_IOREG_CNT1) & 0x300) == 0x300) { // 0x08 
            SET_IO16_TCO(TCO_IOREG_CNT1, 0x100); // Clear NMI_NOW if needed.
        }
    }
    // EOS
    SET_IO8_PM(ACPI_IOREG_SMI_EN, 0x02); // 0x30
    if ((READ_IO8_PM(ACPI_IOREG_SMI_EN) & 0x02) == 0) {
        // Reset GBL_SMI_EN 
        RESET_IO8_PM(ACPI_IOREG_SMI_EN, 0x01); // 0x30
        // Set EOS Again
        SET_IO8_PM(ACPI_IOREG_SMI_EN, 0x02); // 0x30
        // Set GBL_SMI_EN 
        SET_IO8_PM(ACPI_IOREG_SMI_EN, 0x01); // 0x30
    }
}

//---------------------------------------------------------------------------
//                      SW SMI Handler Porting hooks
//---------------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SwSmiEnable
//
// Description: This function enables SW SMI
//
// Input:       None
//
// Output:      None
//
// Notes:       Porting required
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID SwSmiEnable (VOID)
{
    // Porting required
    SET_IO32_PM(ACPI_IOREG_SMI_EN, 0x20); // 0x30
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SwSmiDisable
//
// Description: This function disables SW SMI
//
// Input:       None
//
// Output:      None
//
// Notes:       Porting required
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID SwSmiDisable (VOID)
{
    // Porting required
    RESET_IO32_PM(ACPI_IOREG_SMI_EN, 0x20);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SwSmiClear
//
// Description: This function clears SW SMI
//
// Input:       None
//
// Output:      None
//
// Notes:       Porting required
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID SwSmiClear (VOID)
{
    // Porting required
    WRITE_IO32_PM(ACPI_IOREG_SMI_STS, 0x20); // 0x34
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SwSmiDetect
//
// Description: This function detects SW SMI event
//
// Input:       *Type - Pointer to store SW SMI number
//
// Output:      TRUE - SW SMI occured, FALSE otherwise
//
// Notes:       Porting required
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN SwSmiDetect ( 
    OUT UINT16      *Type )
{
    // Porting required
    if ( IsMe(5) ) {   // SW_SMI
        *Type = IoRead8(SW_SMI_IO_ADDRESS);
        return TRUE;
    }

    return FALSE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   GetEAX
//
// Description: This function returns EAX saved value from CPU that caused
//              SW SMI.
//
// Input:       None
//
// Output:      EAX saved value
//
// Notes:       Porting required
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINTN GetEAX (VOID)
{
    // Porting required for different CPU
    EFI_GUID                SwSmiCpuTriggerGuid = SW_SMI_CPU_TRIGGER_GUID;
    SW_SMI_CPU_TRIGGER      *SwSmiCpuTrigger;
    UINTN                   Cpu = pSmst->CurrentlyExecutingCpu - 1; // CPU #
    EFI_SMM_CPU_SAVE_STATE  *CpuSaveState;
    UINT16                  i;
    
    for (i = 0; i < pSmst->NumberOfTableEntries; i++) {
        if (guidcmp(&(pSmst->SmmConfigurationTable[i].VendorGuid), \
                                                  &SwSmiCpuTriggerGuid) == 0)
            break;
    }

    // If found table, check for the CPU that caused the software Smi.
    if (i != pSmst->NumberOfTableEntries) 
    {
        SwSmiCpuTrigger = pSmst->SmmConfigurationTable[i].VendorTable;
        Cpu = SwSmiCpuTrigger->Cpu;
    }
    CpuSaveState = pSmst->CpuSaveState;

    return CpuSaveState[Cpu].Ia32SaveState.EAX;
}

//---------------------------------------------------------------------------
//                        SX SMI Handler Porting hooks
//---------------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SxSmiEnable
//
// Description: This function enables SX SMI
//
// Input:       None
//
// Output:      None
//
// Notes:       Porting required
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID SxSmiEnable (VOID)
{
    // Porting required
    SET_IO32_PM(ACPI_IOREG_SMI_EN, 0x10); // 0x30
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SxSmiDisable
//
// Description: This function disables SX SMI
//
// Input:       None
//
// Output:      None
//
// Notes:       Porting required
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID SxSmiDisable (VOID)
{
    // Porting required
    RESET_IO32_PM(ACPI_IOREG_SMI_EN, 0x10); // 0x30
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SxSmiClear
//
// Description: This function clears SX SMI
//
// Input:       None
//
// Output:      None
//
// Notes:       Porting required
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID SxSmiClear (VOID)
{
    // Porting required
    WRITE_IO32_PM(ACPI_IOREG_SMI_STS, 0x10); // 0x34
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SxSmiDetect
//
// Description: This function detects SX SMI event
//
// Input:       *Type - Pointer to store value of Sleep type
//
// Output:      TRUE - SX SMI occured, FALSE otherwise
//
// Notes:       Porting required
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN SxSmiDetect (
    OUT UINT16      *Type )
{
    // Porting required
    if (IsMe(4)) {   // SLP_SMI
        switch (READ_IO16_PM(ACPI_IOREG_PM1_CNTL) & (7 << 10)) { // SLP_TYP
            case (0 << 10):
                *Type = SxS0;
                break;
            case (1 << 10):
                *Type = SxS1;
                break;
            case (5 << 10):
                *Type = SxS3;
                break;
            case (6 << 10):
                *Type = SxS4;
                break;
            case (7 << 10):
                *Type = SxS5;
                break;
            default:
                return FALSE;   // Unknown Error.
        }
        return TRUE;
    }
    return FALSE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   PutToSleep
//
// Description: Disable Smi sleep and put to sleep.
//
// Input:       *Context - Pointer to Sleep SMI context
//
// Output:      None
//
// Referrals:   SxSmiDisable
//
// Notes:       Here is the control flow of this function:
//              1. Disable Smi sleep.
//              2. Set to go to sleep if you want to sleep in SMI. otherwise
//                 set IORestart to 0xFF in CPU SMM dump area.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID PutToSleep (
    IN VOID  *SxContext )
{
    EFI_SMM_CPU_SAVE_STATE  *pCpuSaveState = pSmst->CpuSaveState;
    UINTN                   Cpu = pSmst->CurrentlyExecutingCpu - 1;
    UINT32                  CacheFlush = 0;

    SxSmiDisable(); // Disable sleep SMI.

//#### if (SxContext->Type == SxS5)
//####     SBLib_BeforeShutdown();

#if ACPI_SLEEP_IN_SMM
    SET_IO16_PM(ACPI_IOREG_PM1_CNTL, 0x2000); // Set to sleep.
#else
    CacheFlush = pCpuSaveState[Cpu].Ia32SaveState.IORestart;
    pCpuSaveState[Cpu].Ia32SaveState.IORestart = 0xff;
#endif

}

//---------------------------------------------------------------------------
//                Periodic timer SMI Handler Porting hooks
//---------------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   TimerSmiEnable
//
// Description: This function enables Periodic timer SMI
//
// Input:       None
//
// Output:      None
//
// Notes:       Porting required
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID TimerSmiEnable (VOID)
{
    // Porting required
#if SWSMI_TIMER_INSTEAD
    SET_IO32_PM(ACPI_IOREG_SMI_EN, 0x40); // 0x30
#else
    SET_IO32_PM(ACPI_IOREG_SMI_EN, 0x4000); // 0x30
#endif
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   TimerSmiDisable
//
// Description: This function disables Periodic timer SMI
//
// Input:       None
//
// Output:      None
//
// Notes:       Porting required
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID TimerSmiDisable (VOID)
{
    // Porting required
#if SWSMI_TIMER_INSTEAD
    RESET_IO32_PM(ACPI_IOREG_SMI_EN, 0x40); // 0x30
#else
    RESET_IO32_PM(ACPI_IOREG_SMI_EN, 0x4000); // 0x30
#endif
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   TimerSmiClear
//
// Description: This function clears Periodic timer SMI
//
// Input:       None
//
// Output:      None
//
// Notes:       Porting required
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID TimerSmiClear (VOID)
{
    // Porting required
#if SWSMI_TIMER_INSTEAD
    // SWSMI has to be disabled before clear the status
    volatile UINT32 Buffer32 = READ_IO32_PM(ACPI_IOREG_SMI_EN); // 0x30
    WRITE_IO32_PM(ACPI_IOREG_SMI_EN, Buffer32 & (UINT32)(~0x40)); // 0x30
    WRITE_IO32_PM(ACPI_IOREG_SMI_STS, 0x40); // 0x34
    WRITE_IO32_PM(ACPI_IOREG_SMI_EN, Buffer32); // 0x30
#else
    WRITE_IO32_PM(ACPI_IOREG_SMI_STS, 0x4000); // 0x34
#endif
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   TimerSmiDetect
//
// Description: This function detects Periodic timer SMI event
//
// Input:       *Type - Added for compatibility, not used
//
// Output:      TRUE - Periodic timer SMI occured, FALSE otherwise
//
// Notes:       Return TRUE if Timer SMI detected, Type ignored 
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN TimerSmiDetect (
    OUT UINT16          *Type )
{
    // Porting required
    *Type = 0;
#if SWSMI_TIMER_INSTEAD
    return (IsMe(6)) ? TRUE : FALSE;
#else
    return (IsMe(14)) ? TRUE : FALSE;
#endif
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   TimerSetInterval
//
// Description: This function programs Periodic timer to given interval
//
// Input:       Interval - Interval to program
//
// Output:      None
//
// Notes:       Porting required
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID TimerSetInterval (
    IN UINT64       Interval )
{
    // Porting required
    UINT16      RateIndex;
    UINT16      AvailTimer = sizeof(gSupportedIntervals) / sizeof(UINT64) - 1;

    TimerSmiDisable();
    TimerSmiClear();

    for (RateIndex = 0; RateIndex < AvailTimer ; RateIndex++)
        if (Interval == gSupportedIntervals[RateIndex]) break;
#if SWSMI_TIMER_INSTEAD
    RW_PCI16_SB(SB_REG_GEN_PMCON_3, RateIndex << 6, 0xc0); // 0xA4
#else
    RW_PCI16_SB(SB_REG_GEN_PMCON_1, RateIndex, 3); // 0xA0
#endif

    TimerSmiEnable();
}

//---------------------------------------------------------------------------
//                     Usb SMI Handler Porting hooks
//---------------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   UsbSmiSet
//
// Description: This function enables/disables USB SMI based on given
//              Controller type 
//
// Input:       ControllerType - USB controller type variable
//
// Output:      None
//
// Notes:       This function implements logic as follows:
//                  Two lowest bits of ControllerType:
//                  00 - both USB controllers smi are disabled
//                  01 - UHCI/OHCI enabled, EHCI - disabled
//                  10 - UHCI/OHCI disabled, EHCI - enabled
//                  11 - both USB controllers smi are enabled
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID UsbSmiSet(
    IN UINT16   ControllerType )
{
    // Porting required
    switch (ControllerType & 3) {
        case 0 :
                RESET_PCI32_EHCI(EHCI_REG_SPECIAL_SMI, 1);
                RESET_PCI32_EHCI2(EHCI_REG_SPECIAL_SMI, 1);
                RESET_IO32_PM(ACPI_IOREG_SMI_EN, 0x60008); // 0x30
                break;
        case 1 :
                RESET_PCI32_EHCI(EHCI_REG_SPECIAL_SMI, 1);
                RESET_PCI32_EHCI2(EHCI_REG_SPECIAL_SMI, 1);
                RW_IO32_PM(ACPI_IOREG_SMI_EN, 0x08, 0x60008); // 0x30
                break;
        case 2 :
                RW_IO32_PM(ACPI_IOREG_SMI_EN, 0x60000, 0x60008); // 0x30
                SET_PCI32_EHCI(EHCI_REG_SPECIAL_SMI, 1);
                SET_PCI32_EHCI2(EHCI_REG_SPECIAL_SMI, 1);
                break;
        default:
                SET_IO32_PM(ACPI_IOREG_SMI_EN, 0x60008); // 0x30
                SET_PCI32_EHCI(EHCI_REG_SPECIAL_SMI, 1);
                SET_PCI32_EHCI2(EHCI_REG_SPECIAL_SMI, 1);
                break;
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   UsbSmiClear
//
// Description: This function clears USB SMI based on given Controller type
//
// Input:       UINT16 ControllerType - USB controller type variable
//
// Output:      None
//
// Notes:       This function implements logic as follows:
//                  Two lowest bits of ControllerType:        
//                  00 - Nothing to do
//                  01 - Clear UHCI/OHCI USB SMI status
//                  10 - Clear EHCI USB SMI status
//                  11 - Clear UHCI/OHCI & EHCI USB SMI statuses
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID UsbSmiClear (
    IN UINT16   ControllerType )
{
    // Porting required
    switch (ControllerType & 3) {
        case 0 :
                break;
        case 1 :
                WRITE_IO32_PM(ACPI_IOREG_SMI_STS, 0x08); // 0x34
                break;
        case 2 :
                WRITE_IO32_PM(ACPI_IOREG_SMI_STS, 0x20000); // 0x34
                break;
        default:
                WRITE_IO32_PM(ACPI_IOREG_SMI_STS, 0x20008); // 0x34
                break;
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   UsbSmiDetect
//
// Description: This function detects USB SMI event
//
// Input:       *Type - Pointer to store USB controller type, source of event
//
// Output:      TRUE - USB SMI occured, FALSE otherwise
//
// Notes:       This function implements logic as follows:
//                  *Type will be set to 
//                  01 - If UHCI/OHCI USB SMI is occured
//                  02 - If EHCI USB SMI is occured
//                  03 - If UHCI/OHCI & EHCI USB SMI is occured
//                  00 - Nothing is occured and return FALSE
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN UsbSmiDetect (
    OUT UINT16       *Type )
{
    // Porting required
    *Type = 0;
    if (IsMe(3)) *Type |= 1;   // USB_SMI (USB 1.1)
    if (IsMe(17)) *Type |= 2;   // USB_SMI (USB 2.0)

    return (*Type) ? TRUE : FALSE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   GetControllerType
//
// Description: This function returns USB controller type, based on given
//              device path 
//
// Input:       *Device - Pointer USB device path protocol
//
// Output:      UINT16 - USB controller type
//
// Notes:       The USB controller type will be retuened by the follow value:
//                  0 - If there is no matche.
//                  1 - It is an UHCI/OHCI (USB 1.1) controller
//                  2 - It is an EHCI (USB 2.0) controller
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT16 GetControllerType (
    IN EFI_DEVICE_PATH_PROTOCOL *Device)
{

    // Porting required
    EFI_DEVICE_PATH_PROTOCOL    *DevicePath = Device;
    PCI_DEVICE_PATH             *PciDevicePath = NULL; // [EIP73033]
    UINT16                      ControllerType = 0;

    while (!isEndNode( DevicePath )) {
        if ((DevicePath->Type == HARDWARE_DEVICE_PATH) && \
                                        (DevicePath->SubType == HW_PCI_DP)) {
            PciDevicePath = (PCI_DEVICE_PATH *) DevicePath;
            break;
        }
        DevicePath = NEXT_NODE (DevicePath);
    }

    if ((PciDevicePath->Device == EHCI_DEV) || \
                                      (PciDevicePath->Device == EHCI2_DEV)) {
        if ((READ_MEM32_RCRB(0x3598) & 1) == 0) return 2; // RMH Enabled
        ControllerType = 1;
        if (PciDevicePath->Function == 0x07) ControllerType = 2;
    }

    return ControllerType;
}

//---------------------------------------------------------------------------
//                      GPI SMI Handler Porting hooks
//---------------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   GpiSmiSet
//
// Description: This function enables GPI SMI based on given bit field.
//
// Input:       GpiEnableBit - GPI enabled bit field
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID GpiSmiSet (
    IN UINT32       GpiEnableBit )
{
    // Porting required

    UINT8           GpiNum = 0;
	PCH_SERIES 		PchSeries = GetPchSeries();

    if (PchSeries == PchLp) {
      SET_IO32(GPIO_BASE_ADDRESS + GP_IOREG_ALTGP_SMI_EN, GpiEnableBit);
    } else {
      SET_IO16_PM(ACPI_IOREG_ALTGP_SMI_EN, (UINT16)GpiEnableBit);
    }

    while ((GpiEnableBit % 2) == 0) {
            GpiEnableBit /= 2;
            GpiNum++;
    }

    if (PchSeries == PchLp) {
      //Only GPI[47:32] are capable of SMI# generation.
      SET_IO16(GPIO_BASE_ADDRESS+GP_IOREG_GPI_ROUT2, (UINT16)GpiEnableBit);
    } else {
      RW_PCI32_SB(SB_REG_GPI_ROUT, 1 << (GpiNum * 2), 3 << (GpiNum * 2)); // 0xB8,
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   GpiSmiReset
//
// Description: This function disables GPI SMI based on given bit field. 
//
// Input:       GpiDisableBit - GPI disabled bit field
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID GpiSmiReset (
    IN UINT32       GpiDisableBit )
{
    // Porting required

    UINT8           GpiNum = 0;
    PCH_SERIES 		PchSeries = GetPchSeries();

    if (PchSeries == PchLp) {
      RESET_IO32(GPIO_BASE_ADDRESS + GP_IOREG_ALTGP_SMI_EN, GpiDisableBit);
    } else {
      RESET_IO16_PM(ACPI_IOREG_ALTGP_SMI_EN, (UINT16)GpiDisableBit);
    }

    while ((GpiDisableBit % 2) == 0) {
            GpiDisableBit /= 2;
            GpiNum++;
    }

    if (PchSeries == PchLp) {
      //Only GPI[47:32] are capable of SMI# generation.
      RESET_IO16(GPIO_BASE_ADDRESS+GP_IOREG_GPI_ROUT2, (UINT16)GpiDisableBit);
    } else {
      RESET_PCI32_SB(SB_REG_GPI_ROUT, 3 << (GpiNum * 2)); // 0xB8,
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GpiSmiClear
//
// Description: This function clears GPI SMI status based on given bit field
//
// Input:       Type - GPI Disabled bit field
//
// Output:      None
//
// Notes:       All GPIs which correspondent bit in Type set to 1 should
//              be cleared  
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID GpiSmiClear (
    IN UINT32       GpiClearBit )
{
    // Porting required
    if (GetPchSeries() == PchLp) {
      WRITE_IO32(GPIO_BASE_ADDRESS + GP_IOREG_ALTGP_SMI_EN, GpiClearBit);
    } else {
      WRITE_IO16_PM(ACPI_IOREG_ALTGP_SMI_STS, (UINT16)GpiClearBit);
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   GpiSmiDetect
//
// Description: This function detects GPI SMI event
//
// Input:       *Gpi - Pointer to store source of GPI SMI
//
// Output:      TRUE - GPI SMI occured, FALSE otherwise
//
// Notes:       Porting required
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN GpiSmiDetect ( 
    OUT UINT32      *Gpi )
{
    // Porting required
    if (GetPchSeries() == PchLp) {
      *Gpi = READ_IO32(GPIO_BASE_ADDRESS + GP_IOREG_ALTGP_SMI_EN) & READ_IO32(GPIO_BASE_ADDRESS + GP_IOREG_ALTGP_SMI_STS);
    } else {
      *Gpi = READ_IO16_PM(ACPI_IOREG_ALTGP_SMI_EN) & READ_IO16_PM(ACPI_IOREG_ALTGP_SMI_STS);
    }
    
    return (*Gpi) ? TRUE : FALSE;
}

//---------------------------------------------------------------------------
//                 Standby button SMI Handler Porting hooks
//---------------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SButtonSmiEnable
//
// Description: This function enables Standby button SMI
//
// Input:       None
//
// Output:      None
//
// Notes:       Porting required
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID SButtonSmiEnable (VOID)
{
    // Porting required
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SButtonSmiDisable
//
// Description: This function disables Standby button SMI
//
// Input:       None
//
// Output:      None
//
// Notes:       Porting required
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID SButtonSmiDisable (VOID)
{
    // Porting required
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SButtonSmiClear
//
// Description: This function clears Standby button SMI
//
// Input:       None
//
// Output:      None
//
// Notes:       Porting required
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID SButtonSmiClear (VOID)
{
    // Porting required
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SButtonSmiDetect
//
// Description: This function detects Standby button SMI event
//
// Input:       *Type - Pointer to store value of Standby button phase, 
//                      not used.
//
// Output:      TRUE - Standby button SMI occured, FALSE otherwise
//
// Notes:       Porting required
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN SButtonSmiDetect (
    OUT UINT16          *Type )
{
    // Porting required
    return FALSE;
}

//---------------------------------------------------------------------------
//                  Power button SMI Handler Porting hooks
//---------------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   PButtonSmiEnable
//
// Description: This function enables Power button SMI
//
// Input:       None
//
// Output:      None
//
// Notes:       Porting required
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID PButtonSmiEnable (VOID)
{
    // Porting required
    SET_IO16_PM(ACPI_IOREG_PM1_EN, 0x100);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   PButtonSmiDisable
//
// Description: This function disables Power button SMI
//
// Input:       None
//
// Output:      None
//
// Notes:       Porting required
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID PButtonSmiDisable (VOID)
{
    // Porting required
    RESET_IO16_PM(ACPI_IOREG_PM1_EN, 0x100);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   PButtonSmiClear
//
// Description: This function clears Power button SMI
//
// Input:       None
//
// Output:      None
//
// Notes:       Porting required
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID PButtonSmiClear (VOID)
{
    // Porting required
    WRITE_IO16_PM(ACPI_IOREG_PM1_STS, 0x100);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   PButtonSmiDetect
//
// Description: This function detects Power button SMI event
//
// Input:       *Type - pointer to store value of Power button phase
//                      not used.
//
// Output:      TRUE - Power button SMI occured, FALSE - otherwise
//
// Notes:       Porting required
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN PButtonSmiDetect ( 
    OUT UINT16          *Type )
{
    // Porting Required
    UINT16          Buffer16;

    if ( IsAcpi() ) {
        return FALSE;
    } else {
        Buffer16 = READ_IO16_PM(ACPI_IOREG_PM1_STS) & \
                                     READ_IO16_PM(ACPI_IOREG_PM1_EN) & 0x100;
        return (Buffer16) ? TRUE : FALSE;
    }
}

//---------------------------------------------------------------------------
//                       TCO SMI Handler Porting hooks
//---------------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   TcoSmiSet
//
// Description: This function sets TCO functon based on given bit field .
//
// Input:       TcoBitOffset - The offset of TCO bit will be set.
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID TcoSmiSet (
    IN UINT32   TcoBitOffset )
{
    UINT32 PchRcba = READ_PCI32_SB(SB_REG_RCBA);

    // NMI2SMI_STS (TCOBASE+04h[0])
    if (TcoBitOffset == 0) { 
      // Enable NMI by set Port 70h[7] = '0b'
      SwitchAlternateAccessMode (TRUE);
      RESET_IO8(CMOS_ADDR_PORT, BIT07);
      SwitchAlternateAccessMode (FALSE);

      // GBL_SMI_EN = 1
      SET_IO8_PM(ACPI_IOREG_SMI_EN, BIT00);
      // Set NMI2SMI_EN = '1b', TCO_BASE + 08h[9]
      SET_IO16_TCO(TCO_IOREG_CNT1, BIT09);
    }

    // INTRD_DET (TCOBASE+06h[0])
    if (TcoBitOffset == 16) {
      // INTRD_SEL
      RW_IO16_TCO(TCO_IOREG_STS2, BIT02, (BIT01 | BIT02));
    }

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   TcoSmiReset
//
// Description: This function resets TCO functon based on given bit field .
//
// Input:       TcoBitOffset - The offset of TCO bit will be reset.
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID TcoSmiReset (
    IN UINT32   TcoBitOffset )
{
    // NMI2SMI_STS (TCOBASE+04h[0])
    if (TcoBitOffset & BIT00) { 
      // Set NMI2SMI_EN = 0
      RESET_IO16_TCO(TCO_IOREG_CNT1, BIT09);
    }

    // INTRD_DET (TCOBASE+06h[0])
    if (TcoBitOffset & BIT16) {
      // INTRD_SEL
      RESET_IO16_TCO(TCO_IOREG_CNT2, (BIT01 | BIT02));
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   TcoSmiEnable
//
// Description: This function enables TCO SMI
//
// Input:       None
//
// Output:      None
//
// Notes:       Porting required
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID TcoSmiEnable (VOID)
{
    // Porting required
    SET_IO32_PM(ACPI_IOREG_SMI_EN, 0x2000); // 0x30
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   TcoSmiDisable
//
// Description: This function disables TCO SMI
//
// Input:       None
//
// Output:      None
//
// Notes:       Porting required
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID TcoSmiDisable (VOID)
{
    // Porting required
    RESET_IO32_PM(ACPI_IOREG_SMI_EN, 0x2000);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   TcoSmiClear
//
// Description: This function clears TCO SMI and TCO statuses
//
// Input:       None 
//
// Output:      None
//
// Notes:       Porting required
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID TcoSmiClear (VOID)
{
    // Porting required
    WRITE_IO32_TCO(TCO_IOREG_STS1, (UINT32)SUPPORTED_TCOS); // 0x04
    WRITE_IO32_PM(ACPI_IOREG_SMI_STS, 0x2000); // 0x34
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   TcoSmiDetect
//
// Description: This function detects TCO SMI event
//
// Input:       *TcoStatus - Pointer to store TCO SMI status
//
// Output:      TRUE - TCO SMI occured, FALSE otherwise
//
// Notes:       Porting required
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN TcoSmiDetect ( 
    OUT UINT32      *TcoStatus )
{
    // Porting required
    if ( (IsMe(13)) || (READ_IO8_TCO(TCO_IOREG_STS1) & BIT00)) {   // TCO_SMI
        *TcoStatus = READ_IO32_TCO(TCO_IOREG_STS1); // 0x04
        return TRUE;
    }

    return FALSE;
}

//---------------------------------------------------------------------------
//                     I/O Trap SMI Handler Porting hooks
//---------------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   IoTrapSmiSet
//
// Description: This function sets I/O Trap functon based on given the
//              context
//
// Input:       IoTrapContext - Pointer to the context that I/O trap register
//                              will be enabled.
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID IoTrapSmiSet (
    IN EFI_SMM_IO_TRAP_DISPATCH_CONTEXT    *IoTrapContext )
{
    // Porting required if needed.
    UINT32 IoTrapAddr = RCRB_MMIO_IO_TRAP_0; // 0x1E80
    UINT32 i;
    UINT32 Buffer32 = 0;

    // Find an available I/O trap register
    for (i = 0; i < MAX_SUPPORTED_IOTRAP_REGS; i++) {
        if ((READ_MEM32_RCRB(IoTrapAddr) & 1) == 0) break;
        IoTrapAddr += 8;
    }

    IoTrapContext->TrapRegIndex = i;

    if (IoTrapContext->Length < 4) IoTrapContext->Length = 4;
    Buffer32 = IoTrapContext->Length;
    for (i = 0; Buffer32 != 1; Buffer32 >>= 1, i++);
    if (IoTrapContext->Length > (1 << i)) i++;

    IoTrapContext->Length = 1 << i; // Length is always 2^n
    
    Buffer32 = IoTrapContext->Address & 0xfffc;
    Buffer32 |= ((IoTrapContext->Length - 1) & 0xfffc) << 16;
    WRITE_MEM32_RCRB(IoTrapAddr, Buffer32);

    Buffer32 = 0xf0;
    if (IoTrapContext->TrapWidth == AccessWord) Buffer32 = 0x03;
    if (IoTrapContext->TrapWidth == AccessDWord) Buffer32 = 0x0f;

    if (IoTrapContext->TrapOpType == ReadWriteIoCycle) {
        Buffer32 |= (1 << 17); // Both Read/Write Cycles.
    } else {
        if (IoTrapContext->TrapOpType == ReadIoCycle)
            Buffer32 |= (1 << 16); // Read Cycle Only
    }

    WRITE_MEM32_RCRB(IoTrapAddr + 4, Buffer32);
    SET_MEM32_RCRB(IoTrapAddr, 1); // Enable Trap and SMI.
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   IoTrapSmiReset
//
// Description: This function resets I/O Trap functon based on given the
//              context
//
// Input:       IoTrapContext - Pointer to the context that I/O trap register
//                              will be disabled.
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID IoTrapSmiReset (
    IN EFI_SMM_IO_TRAP_DISPATCH_CONTEXT    *IoTrapContext )
{
    // Porting required if needed.
    UINT32 IoTrapAddr = RCRB_MMIO_IO_TRAP_0 + IoTrapContext->TrapRegIndex * 8;

    WRITE_MEM32_RCRB(IoTrapAddr, 0);
    WRITE_MEM32_RCRB(IoTrapAddr + 4, 0);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   IoTrapSmiEnable
//
// Description: This function enables I/O Trap SMI
//
// Input:       None
//
// Output:      None
//
// Notes:       Porting required
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID IoTrapSmiEnable (VOID)
{
    // Porting required if needed.
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   IoTrapSmiDisable
//
// Description: This function disables I/O Trap SMI
//
// Input:       None
//
// Output:      None
//
// Notes:       Porting required
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID IoTrapSmiDisable (VOID)
{
    // Porting required if needed.
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   IoTrapSmiClear
//
// Description: This function clears all I/O Trap SMI status.
//
// Input:       None 
//
// Output:      None
//
// Notes:       Porting required
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID IoTrapSmiClear (VOID)
{
    // Porting required
    SET_MEM32_RCRB(RCRB_MMIO_TRSR, 0); // 0x1E00
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   IoTrapSmiDetect
//
// Description: This function detects I/O Trap SMI event.
//
// Input:       *IoTrapContext - Pointer to EFI_SMM_IO_TRAP_DISPATCH_CONTEXT
//
// Output:      TRUE - I/O Trap SMI occured, the SMI context IoTrapContext
//                     should be updated according to the traped H/W
//                     information.
//
// Notes:       Porting required
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN IoTrapSmiDetect ( 
    OUT EFI_SMM_IO_TRAP_DISPATCH_CONTEXT    *IoTrapContext )
{
    UINT32      IoTrapStatus;
    UINT32      Buffer32;

    // Porting required
    IoTrapStatus = READ_MEM32_RCRB(RCRB_MMIO_TRSR) & 15; // 0x1E00

    if (IoTrapStatus) {

        IoTrapContext->TrapRegIndex = 0;

        while (IoTrapStatus != 1) {
            IoTrapStatus >>= 1;
            IoTrapContext->TrapRegIndex++;
        }

        Buffer32 = READ_MEM32_RCRB(RCRB_MMIO_TRCR); // 0x1E10
        IoTrapContext->TrapAddress = Buffer32 & 0xfffc;
        IoTrapContext->TrapOpType = (Buffer32 & 0x1000000) ? WriteIoCycle :
                                                                  ReadIoCycle;
        if (IoTrapContext->TrapOpType == WriteIoCycle)
            IoTrapContext->TrapData = READ_MEM32_RCRB(RCRB_MMIO_TWDR);

        return TRUE;
    }

    return FALSE;
}

//---------------------------------------------------------------------------
//                  BIOS Write SMI Handler Porting hooks
//---------------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   BiosWriteSmiEnable
//
// Description: This function enables BIOS write SMI
//
// Input:       None
//
// Output:      None
//
// Notes:       Porting required
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID BiosWriteSmiEnable (VOID)
{
    // Enable BIOSWE SMI if needed
//#### SET_PCI8_SB(SB_REG_BIOS_CNTL, 2); // 0xDC
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   BiosWriteSmiDisable
//
// Description: This function disables BIOS write SMI
//
// Input:       None
//
// Output:      None
//
// Notes:       Porting required
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID BiosWriteSmiDisable (VOID)
{
    // Disable BIOSWE SMI if possible.
//#### RESET_PCI8_SB(SB_REG_BIOS_CNTL, 2); // 0xDC
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   BiosWriteSmiClear
//
// Description: This function clears BIOS write SMI status and disables
//              BIOS write function.
//
// Input:       None
//
// Output:      None
//
// Notes:       Porting required
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID BiosWriteSmiClear (VOID)
{
    // Only clear BIOSWR_STS
    WRITE_IO16_TCO(TCO_IOREG_STS1, 0x100); // 0x04
    // Disable BIOS Write
    RESET_PCI8_SB(SB_REG_BIOS_CNTL, 1); // 0xDC
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   BiosWriteSmiDetect
//
// Description: This function detects BIOS write SMI event
//
// Input:       None 
//
// Output:      TRUE - BIOS Write SMI occured, FALSE otherwise
//
// Notes:       Porting required
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN BiosWriteSmiDetect (VOID)
{
    // Check BIOS Lock Enable first.
    if ((READ_PCI8_SB(SB_REG_BIOS_CNTL) & 2) == 0) return FALSE; // 0xDC

    return (READ_IO16_TCO(TCO_IOREG_STS1) & 0x100) ? TRUE : FALSE; // 0x04
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SbSmiWorkaround
//
// Description: This hook is used for all south bridge workaround in SMI.
//
// Input:       None 
//
// Output:      None
//
// Notes:       Porting required
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID SbSmiWorkaround (VOID)
{
    UINT8       DevNum8 = 0;
    UINT32      BaseAddress;
    UINT8       Offset;
    UINT8       EndPort;

    // Sighting #3306438
    if ((READ_IO32_PM(ACPI_IOREG_SMI_EN) & 0x40000) == 0) return;
    if ((READ_IO32_PM(ACPI_IOREG_SMI_STS) & 0x40000) == 0) return;

    // Clear the SMI status
    WRITE_IO32_PM(ACPI_IOREG_SMI_STS, 0x40000);

    if (READ_PCI32_EHCI(EHCI_REG_VID) != 0xffffffff)
        if ((READ_PCI32_EHCI(EHCI_REG_SPECIAL_SMI) & 0x10001) == 0x10001)
            DevNum8 = EHCI_DEV;

    if (READ_PCI32_EHCI2(EHCI_REG_VID) != 0xffffffff)
        if ((READ_PCI32_EHCI2(EHCI_REG_SPECIAL_SMI) & 0x10001) == 0x10001)
            DevNum8 = EHCI2_DEV;

    if (DevNum8) {
        // Clear HCReset SMI status
        WRITE_PCI16(0, DevNum8, 0, EHCI_REG_SPECIAL_SMI + 2, 1);

        BaseAddress = READ_PCI32(0, DevNum8, 0, EHCI_REG_MBASE_ADDR);
        BaseAddress &= 0xfffffff0;
        EndPort = (DevNum8 == EHCI2_DEV) ? 0x78 : 0x80;

        for (Offset = 0x68; Offset <= EndPort; Offset += 4) {
            // Ensure port ownerchip is not been claimed.
            // Clear "Port Owner" bit, Port N Status and Control(PORTSC) [13],
            // if it was set.
            RESET_MEM8(BaseAddress + Offset + 1, 0x20);

            // Set "Port Test Control" bit, PORTSC[19:16], to '1h'.
            RW_MEM8(BaseAddress + Offset + 2, 0x01, 0x0f);

            // Clear "Port Test Control" bit, PORTSC[19:16], to '0h'.
            RESET_MEM8(BaseAddress + Offset + 2, 0x0f);
        }
        // Clear FC[5];
        RESET_PCI16(0, DevNum8, 0, EHCI_REG_IR2, 0x20);
    }
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
