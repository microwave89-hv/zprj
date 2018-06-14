//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.            **
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
// $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/SmmChildDispatcher2/SmiHandlerPorting2.c 9     5/22/15 9:13a Dennisliu $
//
// $Revision: 9 $
//
// $Date: 5/22/15 9:13a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/SmmChildDispatcher2/SmiHandlerPorting2.c $
// 
// 9     5/22/15 9:13a Dennisliu
// [TAG]  		EIP215945 
// [Category]  	Improvement
// [Description]  	[SharkBay][PCH] Executing code outside TSEG check in
// SMM
// 
// 8     3/25/13 5:00a Wesleychen
// [TAG]          None
// [Category]     Improvement
// [Description]  Refine GPI SMM2 related routines.
// [Files]        SmiHandlerGeneric2.c; SmiHandlerPorting2.c;
//                SmmChildDispatch2.h
// 
// 7     3/19/13 8:21a Scottyang
// [TAG]         EIP118158
// [Category]    Improvement
// [Description] Correct SBLib_CmosRead () offset.
// [Files]       SmiHandlerPorting2.c, SBDxe.c, SBGeneric.c, SBSmm.c,
//               SmiHandlerPorting.c
// 
// 6     11/06/12 8:11a Scottyang
// [TAG]         None
// [Category]    Improvement
// [Description] Reduce function "GetPchSeries()".
// [Files]       SBPEI.c, SBDxe.c, SmiHandlerPorting.c, SmiHandlerPorting2.c
// 
// 5     10/19/12 2:52a Scottyang
// [TAG]       EIP93461
// [Category]  Bug Fix
// [Severity]  Normal
// [Symptom]   System halt when AFUDOS is running with /N /ME command.
// [RootCause] An unexpected BIOSWR_STS is set, it causes BIOS stuck
//             at SMM dispatcher.
// [Solution]  Clear BIOSWR_STS if BIOS Lock Enable is not set.
// [Files]     SmiHandlerPorting2.c; SmmChildDispatch2Main.c
//             SmmChildDispatcher2.sdl; SmmChildDispatch2.h
//             SB\SBGeneric.c
// 
// 4     9/26/12 3:56a Victortu
// [TAG]           None
// [Category]      Improvement
// [Description]   Update for PCH LP GPIO compatible.
// [Files]         SB.sdl, SB.H, AcpiModeEnable.c, AcpiModeEnable.sdl,
// SBDxe.c, SBGeneric.c, SBPEI.c, SBSMI.c, SleepSmi.c,
// SmiHandlerPorting.c, SmiHandlerPorting2.c
// 
// 3     7/27/12 6:16a Victortu
// [TAG]           None
// [Category]      Improvement
// [Description]   Update to support ULT Platform.
// [Files]         SB.H, SB.mak, SB.sdl, SB.sd, SBSetup.c,
// AcpiModeEnable.c, SBDxe.c, SBPEI.c, SBSMI.c, SleepSmi.c,
// SmiHandlerPorting.c, SmiHandlerPorting2.c, SBPPI.h, Pch.sdl
// 
// 2     4/25/12 9:30a Victortu
// [TAG]         EIP73033
// [Category]    Improvement
// [Description] 'PciDevicePath' used in GetControllerType(),
// conditionally not set.
// [Files]       SmiHandlerPorting.c; SmiHandlerPorting2.c
// 
// 1     2/08/12 8:28a Yurenlai
// Intel Lynx Point/SB eChipset initially releases.
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:        SmiHandlerPorting2.c
//
// Description: This file contains SMM Child Dispatcher II porting
//              functions
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
#include <Protocol\SmmCpu.h>
#include "SmmChildDispatch2.h"

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
    // Porting required - put all available intervals here (in 100Nanoseconds)
#if SWSMI_TIMER_INSTEAD
// [ EIP215677 ]
//     15000, // 1.5ms
//    160000, // 16 ms
//    320000, // 32 ms
//    640000, // 64 ms
    640000, // 64 ms
    320000, // 32 ms
    160000, // 16 ms
     15000, // 1.5ms
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

extern EFI_SMM_SYSTEM_TABLE2 *gSmst2;
extern EFI_SMM_CPU_PROTOCOL  *gEfiSmmCpuProtocol;

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
    EFI_STATUS              Status;
    EFI_GUID                SwSmiCpuTriggerGuid = SW_SMI_CPU_TRIGGER_GUID;
    SW_SMI_CPU_TRIGGER      *SwSmiCpuTrigger;
    UINTN                   Cpu = gSmst2->CurrentlyExecutingCpu - 1; // CPU #
    UINT16                  i;
    UINT32                  RegEAX;
    
    for (i = 0; i < gSmst2->NumberOfTableEntries; i++) {
        if (guidcmp(&(gSmst2->SmmConfigurationTable[i].VendorGuid), \
                                                  &SwSmiCpuTriggerGuid) == 0)
            break;
    }

    // If found table, check for the CPU that caused the software Smi.
    if (i != gSmst2->NumberOfTableEntries) {
        SwSmiCpuTrigger = gSmst2->SmmConfigurationTable[i].VendorTable;
        Cpu = SwSmiCpuTrigger->Cpu;
    }

    Status = gEfiSmmCpuProtocol->ReadSaveState ( \
                                            gEfiSmmCpuProtocol, \
                                            4, \
                                            EFI_SMM_SAVE_STATE_REGISTER_RAX, \
                                            Cpu, \
                                            &RegEAX );
    return RegEAX;
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
    IN EFI_SMM_SX_REGISTER_CONTEXT  *SxContext )
{
// TODO YODO TODO
//####    EFI_SMM_CPU_SAVE_STATE  *pCpuSaveState = gSmst2->CpuSaveState;
//####    UINTN                   Cpu = gSmst2->CurrentlyExecutingCpu - 1;
//####    UINT32                  CacheFlush = 0;

    SxSmiDisable(); // Disable sleep SMI.

//#### if (SxContext->Type == SxS5)
//####     SBLib_BeforeShutdown();

//#####if ACPI_SLEEP_IN_SMM
    SET_IO16_PM(ACPI_IOREG_PM1_CNTL, 0x2000); // Set to sleep.
//#####else
//####    CacheFlush = pCpuSaveState[Cpu].Ia32SaveState.IORestart;
//####    pCpuSaveState[Cpu].Ia32SaveState.IORestart = 0xff;
//#####endif

}

//---------------------------------------------------------------------------
//                Periodic timer SMI Handler Porting hooks
//---------------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   TimerSmiEnable2
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

VOID TimerSmiEnable2 (VOID)
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
// Procedure:   TimerSmiDisable2
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

VOID TimerSmiDisable2 (VOID)
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
// Procedure:   TimerSmiClear2
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

VOID TimerSmiClear2 (VOID)
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
// Procedure:   TimerSmiDetect2
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

BOOLEAN TimerSmiDetect2 (
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
// Procedure:   TimerSetInterval2
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

VOID TimerSetInterval2 (
    IN UINT64       Interval )
{

    // Porting required
    UINT16      RateIndex;
    UINT16      AvailTimer = sizeof(gSupportedIntervals) / sizeof(UINT64) - 1;

    TimerSmiDisable2();
    TimerSmiClear2();

    for (RateIndex = 0; RateIndex < AvailTimer ; RateIndex++)
        if (Interval == gSupportedIntervals[RateIndex]) break;
#if SWSMI_TIMER_INSTEAD
    RW_PCI16_SB(SB_REG_GEN_PMCON_3, RateIndex << 6, 0xc0); // 0xA4
#else
    RW_PCI16_SB(SB_REG_GEN_PMCON_1, RateIndex, 3); // 0xA0
#endif

    TimerSmiEnable2();
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
//                  Three lowest bits of ControllerType:
//                  000 - All USB controllers SMI are disabled
//                  001 - UHCI/OHCI enabled, EHCI/XHCI - disabled
//                  010 - EHCI enabled, UHCI/OHCI/XHCI - disabled
//                  011 - UHCI/OHCI/EHCI enabled, XHCI - disabled
//                  100 - XHCI enabled, UHCI/OHCI/EHCI - disabled
//                  101 - UHCI/OHCI/XHCI enabled, EHCI - disabled
//                  110 - EHCI/XHCI enabled, UHCI/OHCI - disabled
//                  111 - All USB controllers SMI are enabled
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID UsbSmiSet(
    IN UINT16   ControllerType )
{
    // Porting required
    switch (ControllerType & 7) {

        case 0 : // All USB controllers SMI are disabled
                RESET_PCI32_EHCI(EHCI_REG_SPECIAL_SMI, 1);
                RESET_PCI32_EHCI2(EHCI_REG_SPECIAL_SMI, 1);
                RESET_IO32_PM(ACPI_IOREG_SMI_EN, 0x80060008); // 0x30
                break;

        case 1 : // UHCI/OHCI enabled, EHCI/XHCI - disabled
                RESET_PCI32_EHCI(EHCI_REG_SPECIAL_SMI, 1);
                RESET_PCI32_EHCI2(EHCI_REG_SPECIAL_SMI, 1);
                RW_IO32_PM(ACPI_IOREG_SMI_EN, 0x08, 0x80060008); // 0x30
                break;

        case 2 : // EHCI enabled, UHCI/OHCI/XHCI - disabled
                RW_IO32_PM(ACPI_IOREG_SMI_EN, 0x60000, 0x80060008); // 0x30
                SET_PCI32_EHCI(EHCI_REG_SPECIAL_SMI, 1);
                SET_PCI32_EHCI2(EHCI_REG_SPECIAL_SMI, 1);
                break;

        case 3 : // UHCI/OHCI/EHCI enabled, XHCI - disabled
                RW_IO32_PM(ACPI_IOREG_SMI_EN, 0x60008, 0x80060008); // 0x30
                SET_PCI32_EHCI(EHCI_REG_SPECIAL_SMI, 1);
                SET_PCI32_EHCI2(EHCI_REG_SPECIAL_SMI, 1);
                break;

        case 4 : // XHCI enabled, UHCI/OHCI/EHCI - disabled
                RESET_PCI32_EHCI(EHCI_REG_SPECIAL_SMI, 1);
                RESET_PCI32_EHCI2(EHCI_REG_SPECIAL_SMI, 1);
                RW_IO32_PM(ACPI_IOREG_SMI_EN, 0x80000000, 0x80060008); // 0x30
                break;

        case 5 : // UHCI/OHCI/XHCI enabled, EHCI - disabled
                RESET_PCI32_EHCI(EHCI_REG_SPECIAL_SMI, 1);
                RESET_PCI32_EHCI2(EHCI_REG_SPECIAL_SMI, 1);
                RW_IO32_PM(ACPI_IOREG_SMI_EN, 0x80000008, 0x80060008); // 0x30
                break;

        case 6 : // EHCI/XHCI enabled, UHCI/OHCI - disabled
                RW_IO32_PM(ACPI_IOREG_SMI_EN, 0x80060000, 0x80060008); // 0x30
                SET_PCI32_EHCI(EHCI_REG_SPECIAL_SMI, 1);
                SET_PCI32_EHCI2(EHCI_REG_SPECIAL_SMI, 1);
                break;

        default: // All USB controllers SMI are enabled
                SET_IO32_PM(ACPI_IOREG_SMI_EN, 0x80060008); // 0x30
                SET_PCI32_EHCI(EHCI_REG_SPECIAL_SMI, 1);
                SET_PCI32_EHCI2(EHCI_REG_SPECIAL_SMI, 1);
                break;
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   UsbSmiClear
//
// Description: This function clears USB SMI status based on given Controller
//              type.
//
// Input:       UINT16 ControllerType - USB controller type variable
//
// Output:      None
//
// Notes:       This function implements logic as follows:
//                  Three lowest bits of ControllerType:        
//                  Bit 0 - Clear UHCI/OHCI USB SMI status
//                  Bit 1 - Clear EHCI USB SMI status
//                  Bit 2 - Clear XHCI USB SMI status
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID UsbSmiClear (
    IN UINT16   ControllerType )
{
    // Porting required

    if (ControllerType & 1) // Clear UHCI/OHCI USB SMI status
        WRITE_IO32_PM(ACPI_IOREG_SMI_STS, 0x08); // 0x34

    if (ControllerType & 2) // Clear EHCI USB SMI status
        WRITE_IO32_PM(ACPI_IOREG_SMI_STS, 0x20000); // 0x34
    if (ControllerType & 4) // Clear XHCI USB SMI status
        WRITE_IO32_PM(ACPI_IOREG_SMI_STS, 0x80000000); // 0x34
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
//                  000 - There is no SMI occured
//                  Bit 0 - If UHCI/OHCI USB SMI is occured
//                  Bit 1 - If EHCI USB SMI is occured
//                  Bit 2 - If XHCI USB SMI is occured
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN UsbSmiDetect (
    OUT UINT16       *Type )
{
    // Porting required
    *Type = 0;
    if (IsMe(03)) *Type |= 1;   // USB_SMI (USB 1.1)
    if (IsMe(17)) *Type |= 2;   // USB_SMI (USB 2.0)
    if (IsMe(31)) *Type |= 4;   // USB_SMI (USB 3.0)

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
//                  4 - It is a XHCI (USB 3.0) controller
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

// [ EIP215945 ]
//    if (PciDevicePath->Device == EHCI_DEV) {
//        ControllerType = 1;
//        if (PciDevicePath->Function == 0x07) ControllerType = 2;
//        
    if ((PciDevicePath->Device == EHCI_DEV) || (PciDevicePath->Device == EHCI2_DEV))
    {
        ControllerType = 2;
    } else {
      if (PciDevicePath->Device == XHCI_DEV)
        if (PciDevicePath->Function == XHCI_FUN) ControllerType = 4; 
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

    UINT8       GpiNum = 0;
    PCH_SERIES  PchSeries = GetPchSeries();

    if (PchSeries == PchLp) {
      SET_IO16(GPIO_BASE_ADDRESS + GP_IOREG_ALTGP_SMI_EN, (UINT16)GpiEnableBit);
    } else {
      SET_IO16_PM(ACPI_IOREG_ALTGP_SMI_EN, (UINT16)GpiEnableBit);
    }

    while ((GpiEnableBit % 2) == 0) {
            GpiEnableBit /= 2;
            GpiNum++;
    }
    GpiNum *= 2;

    if (PchSeries == PchLp) {
      //Only GPI[47:32] are capable of SMI# generation.
      SET_IO16(GPIO_BASE_ADDRESS + GP_IOREG_GPI_ROUT2, (UINT16)GpiEnableBit);
    } else {
      RW_PCI32_SB(SB_REG_GPI_ROUT, 1 << GpiNum, 3 << GpiNum); // 0xB8
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
      RESET_IO16(GPIO_BASE_ADDRESS + GP_IOREG_ALTGP_SMI_EN, (UINT16)GpiDisableBit);
    } else {
      RESET_IO16_PM(ACPI_IOREG_ALTGP_SMI_EN, (UINT16)GpiDisableBit);
    }

    while ((GpiDisableBit % 2) == 0) {
            GpiDisableBit /= 2;
            GpiNum++;
    }
    GpiNum *= 2;

    if (PchSeries == PchLp) {
      //Only GPI[47:32] are capable of SMI# generation.
      RESET_IO16(GPIO_BASE_ADDRESS+GP_IOREG_GPI_ROUT2, (UINT16)GpiDisableBit);
    } else {
      RESET_PCI32_SB(SB_REG_GPI_ROUT, 3 << GpiNum); // 0xB8
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


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ConvertGpi
//
// Description: This function converts GPI to bitmap in 32 bit.
//
// Input:       Gpi - GPI Pin number or bitmap
//
// Output:      Converted GPI bitmap in 32 bit.
//              GpiBitMap[16:0] = ALT_GPI_SMI_EN[15:0] = LPT-H GPI[15:0]
//              GpiBitMap[16:0] = ALT_GPI_SMI_EN[15:0] = LPT-LP GPI[47:32]
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT32 ConvertGpi (
    IN UINTN Gpi
)
{
    UINT32 GpiBitMap = 0;
    PCH_SERIES  PchSeries = GetPchSeries();

    if (GPI_DISPATCH2_BY_BITMAP) {
       if (PchSeries == PchLp)
         GpiBitMap = (UINT32)(Shr64((UINT64)Gpi, 32));
       else
         GpiBitMap = (UINT32)Gpi;
    } else {
       if (PchSeries == PchLp)
         GpiBitMap |= Shl64(1, (UINT8)(Gpi - 32));
       else
         GpiBitMap |= Shl64(1, (UINT8)Gpi);
    }
    return GpiBitMap;
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
// Input:       IoTrapContext - Pointer to the context
//                              EFI_SMM_IO_TRAP_REGISTER_CONTEXT
//                              
// Output:      TrapRegIndex - Pointer to the index of I/O Trap register
//                             that I/O Trap register will be enabled.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID IoTrapSmiSet2 (
    IN EFI_SMM_IO_TRAP_REGISTER_CONTEXT *IoTrapContext,
    OUT UINT32                          *TrapRegIndex )
{
    // Porting required if needed.
    UINT32  IoTrapAddr = RCRB_MMIO_IO_TRAP_0; // 0x1E80
    UINT32  i;
    UINT32  Buffer32 = 0;
    UINT16  Length = IoTrapContext->Length;

    // Find an available I/O trap register
    for (i = 0; i < MAX_SUPPORTED_IOTRAP_REGS; i++) {
        if ((READ_MEM32_RCRB(IoTrapAddr) & 1) == 0) break;
        IoTrapAddr += 8;
    }

    *TrapRegIndex = i;

    if (*TrapRegIndex == MAX_SUPPORTED_IOTRAP_REGS) return;

    if (Length < 4) Length = 4;
    Buffer32 = Length;
    for (i = 0; Buffer32 != 1; Buffer32 >>= 1, i++);
    if (Length > (1 << i)) i++;

    Length = 1 << i; // Length is always 2^n
    
    Buffer32 = IoTrapContext->Address & 0xfffc;
    Buffer32 |= ((Length - 1) & 0xfffc) << 16;
    WRITE_MEM32_RCRB(IoTrapAddr, Buffer32);

    Buffer32 = 0xf0; // Byte Access
//    if (IoTrapContext->TrapWidth == AccessWord) Buffer32 = 0x03;
//    if (IoTrapContext->TrapWidth == AccessDWord) Buffer32 = 0x0f;

    if (IoTrapContext->Type == ReadWriteTrap) {
        Buffer32 |= (1 << 17); // Both Read/Write Cycles.
    } else {
        if (IoTrapContext->Type == ReadTrap)
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

VOID IoTrapSmiReset2 (
    IN EFI_SMM_IO_TRAP_REGISTER_CONTEXT *IoTrapContext,
    OUT UINT32                          *TrapRegIndex  )
{
    // Porting required if needed.

    UINT32      IoTrapAddr = RCRB_MMIO_IO_TRAP_0; // 0x1E80
    UINT32      i;
    UINT32      TrapContext32 = 0;

    for (i = 0; i < MAX_SUPPORTED_IOTRAP_REGS; i++) {
        TrapContext32 = READ_MEM32_RCRB(IoTrapAddr);
        if (TrapContext32 & 1)
            if ((UINT16)(TrapContext32 & 0xfffc) == IoTrapContext->Address) {
                TrapContext32 = READ_MEM32_RCRB(IoTrapAddr + 4);
                if (TrapContext32 & 0x20000) {
                    if (IoTrapContext->Type == ReadWriteTrap) break;
                } else {
                    if (TrapContext32 & 0x10000) {
                        if (IoTrapContext->Type == ReadTrap) break;
                    } else {
                        if (IoTrapContext->Type == WriteTrap) break;
                    }
                }
            }            
        IoTrapAddr += 8;
    }

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

VOID IoTrapSmiEnable2 (VOID)
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

VOID IoTrapSmiDisable2 (VOID)
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

VOID IoTrapSmiClear2 (VOID)
{
    // Porting required
    SET_MEM32_RCRB(RCRB_MMIO_TRSR, 0); // 0x1E00
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   IoTrapSmiDetect2
//
// Description: This function detects I/O Trap SMI event.
//
// Input:       *IoTrapContext - Pointer to EFI_SMM_IO_TRAP_REGISTER_CONTEXT
//
// Output:      TRUE - I/O Trap SMI occured, the SMI context IoTrapContext
//                     should be updated according to the traped H/W
//                     information.
//
// Notes:       Porting required
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN IoTrapSmiDetect2 ( 
    OUT EFI_SMM_IO_TRAP_REGISTER_CONTEXT    *IoTrapContext,
    OUT UINT32                              *IoTrapWriteData )
{
    // Porting required

    UINT32      Buffer32;
    UINT16      Offset = 0;
    UINT16      i;

    if (READ_MEM32_RCRB(RCRB_MMIO_TRSR) & 15) { // 0x1E00

        Buffer32 = READ_MEM32_RCRB(RCRB_MMIO_TRCR); // 0x1E10
        IoTrapContext->Address = Buffer32 & 0xfffc;
        for (i = 0; i < 4; i++) {
            if (Buffer32 & (1 << (16 + i))) break;
            Offset++;
        }
        IoTrapContext->Address += Offset;
        if (Buffer32 & (1 << 24)) {
            IoTrapContext->Type = ReadTrap;
        } else {
            IoTrapContext->Type = WriteTrap;
            *IoTrapWriteData = READ_MEM32_RCRB(RCRB_MMIO_TWDR); // 0x1E18
        }
        return TRUE;
    }

    return FALSE;
}
                                        // [EIP93461]>
#if BIOS_WRITE_SMI_PATCH_ENABLE
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   PchBiosWritePatch
//
// Description: This function clears unexpected BIOSWR_STS.
//
// Input:       None
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID BiosWriteSmiPatch ( VOID )
{
    // Clear BIOSWR_STS(TCO_BASE + 04h[8]) if BIOS Lock Enable
    // (B0:D31:F0 Reg#DCh[1]) is not set.
    if (((READ_PCI8_SB(SB_REG_BIOS_CNTL) & BIT01) == 0) && \
        (READ_IO16_TCO(TCO_IOREG_STS1) & BIT08)) {

      // Clear BIOSWR_STS
      WRITE_IO16_TCO(TCO_IOREG_STS1, BIT08);
      // Clear TCO_STS
      WRITE_IO16_PM(ACPI_IOREG_SMI_STS, BIT13);

    }
}
#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SbSmiWorkaround2
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

VOID SbSmiWorkaround2 (VOID)
{

#if BIOS_WRITE_SMI_PATCH_ENABLE
    BiosWriteSmiPatch();
#endif

}
                                        // <[EIP93461]
//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
