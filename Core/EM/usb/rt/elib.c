//****************************************************************************
//****************************************************************************
//**                                                                        **
//**             (C)Copyright 1985-2016, American Megatrends, Inc.          **
//**                                                                        **
//**                          All Rights Reserved.                          **
//**                                                                        **
//**                 5555 Oakbrook Pkwy, Norcross, GA 30093                 **
//**                                                                        **
//**                          Phone (770)-246-8600                          **
//**                                                                        **
//****************************************************************************
//****************************************************************************

//****************************************************************************
// $Header: /Alaska/SOURCE/Modules/USB/ALASKA/RT/elib.c 22    10/16/16 10:12p Wilsonlee $
//
// $Revision: 22 $
//
// $Date: 10/16/16 10:12p $
//****************************************************************************
//****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/USB/ALASKA/RT/elib.c $
// 
// 22    10/16/16 10:12p Wilsonlee
// [TAG]  		EIP288158
// [Category]  	Improvement
// [Description]  	Check if gUsbData is integrity.
// [Files]  		amiusb.cif, usbsb.c, AmiUsbLib.cif, AmiUsbLib.sdl,
// AmiUsbSmmGlobalDataValidationLib.c,
// AmiUsbSmmGlobalDataValidationLib.cif,
// AmiUsbSmmGlobalDataValidationLib.mak, Crc32.c, amiusb.c, amiusb.h,
// ehci.c, elib.c, ohci.c, syskbc.c, uhci.c, usb.c, usbCCID.c, usbdef.h,
// usbhid.c, usbhub.c, usbkbd.c, usbmass.c, usbms.c, usbrt.mak, xhci.c,
// amiusbhc.c, efiusbccid.c, efiusbmass.c, uhcd.c, usbmisc.c,
// AmiUsbController.h, AmiUsbLibInclude.cif,
// AmiUsbSmmGlobalDataValidationLib.h
// 
// 21    3/18/13 4:47a Ryanchou
// [TAG]  		EIP98377
// [Category]  	Improvement
// [Description]  	Optimize USB controller timing.
// [Files]  		usb.sdl, usbport.c, ehci.c, elib.c, ohci.c, uhci.c,
// usbdef.h, usbhub.c, xhci.c, uhcd.c
// 
// 20    9/28/12 2:39a Wilsonlee
// [TAG]  		EIP93154
// [Category]  	Improvement
// [Description]  	Change the unit of the FixedDelay from 15 us to 1 us.
// [Files]  		amiusb.h, xhci.c, ehci.c, ohci.c, uhci.c, usb.c, usbCCID.c,
// usbmass.c, usbhub.c, elib.c
// 
// 19    8/29/12 8:16a Ryanchou
// [TAG]  		EIP77262
// [Category]  	New Feature
// [Description]  	Remove SMM dependency of USB.
// [Files]  		usb.sdl, usbport.c, amiusb.c, amiusb.dxs, amiusb.h, ehci.c,
// elib.c, ohci.c, uhci.c, usb.c, usbdef.h, usbrt.mak, xhci.c, amiusbhc.c,
// efiusbccid.c, efiusbhid.c, efiusbkb.c, efiusbmass.c, uhcd.c, uhcd.dxs,
// uhcd.h, usbmisc.c, AmiUsbController.h
// 
// 18    4/07/11 3:48a Ryanchou
// [TAG]  		EIP57802
// [Category]  	Improvement
// [Description]  	The variable dCount should not be increase, undo the
// EIP55960 change in elib.c.
// [Files]  		elib.c
// 
// 17    4/06/11 3:53a Ryanchou
// [TAG]  		EIP55960
// [Category]  	Improvement
// [Description]  	The Host Controller must halt within 16 micro-frames
// after software clears the Run bit.
// [Files]  		ehci.c, elib.c
// 
// 16    3/31/11 9:45a Tonylo
// [TAG]  		EIP56841
// [Category]  	Improvement
// [Description]  	Remove IO port 0x61 dependency.
// [Files]  		elib.c
// 
// 15    10/02/09 10:49a Olegi
// Code cleanup.
// 
// 14    5/16/08 12:01p Olegi
// Compliance with AMI coding standard.
// 
// 13    5/22/07 12:28p Olegi
// Added USB_BEEP_ENABLE token functionality.
// 
// 12    4/26/07 6:10p Olegi
// DwordReadMem and DwordWriteMem work with volatile memory.
// 
// 7     10/12/06 9:03p Andriyn
// Debug DELAY function: slow down portion of code
//
// 6     7/24/06 6:05p Olegi
// FixedDelay optimization (by Stacy Howell)
//
// 5     4/14/06 6:39p Olegi
// Conversion to be able to use x64 compiler.
//
// 3     3/20/06 3:37p Olegi
// Version 8.5 - x64 compatible.
//
// 2     12/19/05 10:14a Olegi
// Beep routine modified.
//
// 1     3/15/05 9:23a Olegi
// Initial VSS check-in.
//
//****************************************************************************

//<AMI_FHDR_START>
//-----------------------------------------------------------------------------
//
//  Name:           Elib.c
//
//  Description:    AMI USB MEM/IO/PCI access routines
//
//-----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "amidef.h"
#include "usbdef.h"

extern  USB_GLOBAL_DATA         *gUsbData;
//extern  EFI_SMM_SYSTEM_TABLE    *gSmst;

UINT8   ByteReadIO(UINT16);
UINT16  WritePCIConfig(UINT16, UINT8);

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   FixedDelay
//
// Description: This routine delays for specified number of micro seconds
//
// Input:   wCount      Amount of delay (count in 1 microsec)
//
// Output:  None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID 
FixedDelay(
    UINTN           Usec                           
 )
{
#if USB_RUNTIME_DRIVER_IN_SMM
    UINTN   Counter, i;
    UINT32  Data32, PrevData;

    Counter = Usec * 3;
    Counter += Usec / 2;
    Counter += (Usec * 2) / 25;

    //
    // Call WaitForTick for Counter + 1 ticks to try to guarantee Counter tick
    // periods, thus attempting to ensure Microseconds of stall time.
    //
    if (Counter != 0) {

        PrevData = IoRead32(PM_BASE_ADDRESS + 8);
        for (i=0; i < Counter; ) {
            Data32 = IoRead32(PM_BASE_ADDRESS + 8);    
            if (Data32 < PrevData) {        // Reset if there is a overlap
                PrevData=Data32;
                continue;
            }
            i += (Data32 - PrevData);        
            PrevData = Data32;
        }
    }
#else
	pBS->Stall(Usec);
#endif
    return;
}

EFI_STATUS
UsbHcStrucValidation(
    HC_STRUC* HcStruc
)
{
    UINTN       Index;

    if (HcStruc == NULL) {
        return EFI_ACCESS_DENIED;
    }
    
    for (Index = 0; Index < gUsbData->HcTableCount; Index++) {
        if (HcStruc == gUsbData->HcTable[Index]) {
            break;
        }
    }

    if (Index == gUsbData->HcTableCount) {
        return EFI_ACCESS_DENIED;
    }

    if (!(HcStruc->dHCFlag & HC_STATE_USED)) {
        return EFI_ACCESS_DENIED;
    }

    return EFI_SUCCESS;
}

EFI_STATUS
UsbDevInfoValidation(
    DEV_INFO* DevInfo
)
{
    UINTN       Index;
    UINT8       *MemBlockEnd = gUsbData->fpMemBlockStart + (gUsbData->MemPages << 12);

    if (DevInfo == NULL) {
        return EFI_ACCESS_DENIED;
    }
    
    for (Index = 0; Index < MAX_DEVICES; Index++) {
        if (DevInfo == &gUsbData->aDevInfoTable[Index]) {
            break;
        }
    }

    if (Index == MAX_DEVICES) {
        return EFI_ACCESS_DENIED;
    }

#if USB_RUNTIME_DRIVER_IN_SMM
    if (DevInfo->fpPollEDPtr) {
        if ((DevInfo->fpPollEDPtr < gUsbData->fpMemBlockStart) ||
            ((DevInfo->fpPollEDPtr + sizeof(MEM_BLK)) > MemBlockEnd)) {
            return EFI_ACCESS_DENIED;
        }
    }

    if (DevInfo->fpPollTDPtr) {
        if ((DevInfo->fpPollTDPtr < gUsbData->fpMemBlockStart) ||
            ((DevInfo->fpPollTDPtr + sizeof(MEM_BLK)) > MemBlockEnd)) {
            return EFI_ACCESS_DENIED;
        }
    }

    if (DevInfo->fpPollDataBuffer) {
        if ((DevInfo->fpPollDataBuffer < gUsbData->fpMemBlockStart) ||
            ((DevInfo->fpPollDataBuffer + DevInfo->PollingLength) > MemBlockEnd)) {
            return EFI_ACCESS_DENIED;
        }
    }
#endif

    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   DwordReadMem
//
// Description: This routine reads a DWORD from the specified Memory Address
//
// Input:   dBaseAddr   - Memory address to read
//          bOffset     - Offset of dBaseAddr
//
// Output:  Value read
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT32
DwordReadMem(UINT32 dBaseAddr, UINT16 wOffset)
{
    return *(volatile UINT32*)(UINTN)(dBaseAddr+wOffset);
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   DwordWriteMem
//
// Description: This routine writes a DWORD to a specified Memory Address
//
// Input:   dBaseAddr   - Memory address to write
//          bOffset     - Offset of dBaseAddr
//          dValue      - Data to write
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
DwordWriteMem(UINT32 dBaseAddr, UINT16 wOffset, UINT32 dValue)
{
    *(volatile UINT32*)(UINTN)(dBaseAddr+wOffset) = dValue;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   DwordResetMem
//
// Description: This routine resets the specified bits at specified memory address
//
// Input:   dBaseAddr   - Memory address to read
//          bOffset     - Offset of dBaseAddr
//
// Output:  Value read
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
DwordResetMem(UINT32 dBaseAddr, UINT16 wOffset, UINT32 dValue)
{
    UINT32 data = DwordReadMem(dBaseAddr, wOffset);
    data &= ~dValue;
    DwordWriteMem(dBaseAddr, wOffset, data);
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   DwordSetMem
//
// Description: This routine sets the specified bits at specified memory address
//
// Input:   dBaseAddr   - Memory address to read
//          bOffset     - Offset of dBaseAddr
//
// Output:  Value read
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
DwordSetMem(UINT32 dBaseAddr, UINT16 wOffset, UINT32 dValue)
{
    UINT32 data = DwordReadMem(dBaseAddr, wOffset);
    data |= dValue;
    DwordWriteMem(dBaseAddr, wOffset, data);
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ByteReadIO
//
// Description: This routine reads a Byte from the specified IO address
//
// Input:   wIOAddr     I/O address to read
//
// Output:  Value read
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
ByteReadIO(UINT16 wIOAddr)
{
//    UINT8 value;
//    gSmst->SmmIo.Io.Read(&gSmst->SmmIo, SMM_IO_UINT8, (UINT64)wIOAddr, 1, &value);
//    return value;
    return IoRead8(wIOAddr);
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ByteWriteIO
//
// Description: This routine writes a byte to the specified IO address
//
// Input:   wIOAddr     I/O address to write
//          bValue      Byte value to write
//
// Output:  None
//
// Modified:    Nothing
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
ByteWriteIO (UINT16 wIOAddr, UINT8 bValue)
{
//    gSmst->SmmIo.Io.Write(&gSmst->SmmIo, SMM_IO_UINT8, (UINT64)wIOAddr, 1, &bValue);
    IoWrite8(wIOAddr, bValue);
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   WordReadIO
//
// Description: This routine reads a Word from the specified IO address
//
// Input:   wIOAddr     I/O address to read
//
// Output:  Value read
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT16
WordReadIO(UINT16 wIOAddr)
{
//    UINT16 value;
//    gSmst->SmmIo.Io.Read(&gSmst->SmmIo, SMM_IO_UINT16, (UINT64)wIOAddr, 1, &value);
//    return  value;
    return IoRead16(wIOAddr);
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   WordWriteIO
//
// Description: This routine writes a word to the specified IO address
//
// Input:   wIOAddr     I/O address to write
//          wValue      Word value to write
//
// Output:  None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
WordWriteIO (UINT16 wIOAddr, UINT16 wValue)
{
//    gSmst->SmmIo.Io.Write(&gSmst->SmmIo, SMM_IO_UINT16, (UINT64)wIOAddr, 1, &wValue);
    IoWrite16(wIOAddr, wValue);
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   DwordReadIO
//
// Description: This routine reads a dword from the specified IO address
//
// Input:   wIOAddr     I/O address to read
//
// Output:  Value read
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT32
DwordReadIO(UINT16 wIOAddr)
{
//    UINT32  value;
//    gSmst->SmmIo.Io.Read(&gSmst->SmmIo, SMM_IO_UINT32, (UINT64)wIOAddr, 1, &value);
//    return  value;
    return IoRead32(wIOAddr);
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   DwordWriteIO
//
// Description: This routine writes a double word to the specified IO address
//
// Input:   wIOAddr     I/O address to write
//      dValue      Double word value to write
//
// Output:  None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
DwordWriteIO(UINT16 wIOAddr, UINT32 dValue)
{
//    gSmst->SmmIo.Io.Write(&gSmst->SmmIo, SMM_IO_UINT32, (UINT64)wIOAddr, 1, &dValue);
    IoWrite32(wIOAddr, dValue);
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ReadPCIConfig
//
// Description: This routine reads from the PCI configuration space register
//              the value can be typecasted to 8bits - 32bits
//
// Input:   BusDevFunc - Bus, device & function number of the PCI device
//          Register   - Register offset to read
//
// Output:  Value read
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT32
ReadPCIConfig(UINT16 BusDevFunc, UINT8 Register)
{
    UINT32 data;
    DwordWriteIO(0xCF8, (UINT32)(0x80000000 | (BusDevFunc<<8) | (Register & 0xFC)));
    data = DwordReadIO(0xCFC);
    return (data >> ((Register & 3) << 3)); // Adjust uneven register

}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ByteWritePCIConfig
//
// Description: This routine writes a byte value to the PCI configuration
//      register space
//
// Input:   BusDevFunc - Bus, device & function number of the PCI device
//      Register   - Register offset to read
//      Value      - Value to write
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
ByteWritePCIConfig(UINT16 BusDevFunc, UINT8 Register, UINT8 Value)
{
    UINT16 wIOAddr;
    wIOAddr = WritePCIConfig(BusDevFunc, Register);
    ByteWriteIO (wIOAddr, Value);
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   WordWritePCIConfig
//
// Description: This routine writes a byte value to the PCI configuration
//      register space
//
// Input:   BusDevFunc - Bus, device & function number of the PCI device
//      Register   - Register offset to read
//      Value      - Value to write
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
WordWritePCIConfig(UINT16 BusDevFunc, UINT8 Register, UINT16 Value)
{
    UINT16 wIOAddr;
    wIOAddr = WritePCIConfig(BusDevFunc, Register);
    WordWriteIO (wIOAddr, Value);
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   DwordWritePCIConfig
//
// Description: This routine writes a Dword value to the PCI configuration
//      register space
//
// Input:   BusDevFunc - Bus, device & function number of the PCI device
//      Register   - Register offset to read
//      Value      - Value to write
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
DwordWritePCIConfig(UINT16 BusDevFunc, UINT8 Register, UINT32 Value)
{
    UINT16 wIOAddr;
    wIOAddr = WritePCIConfig(BusDevFunc, Register);
    DwordWriteIO (wIOAddr, Value);
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   WritePCIConfig
//
// Description: This function opens PCI configuration for a given register
//
// Input:   wBDF  - Bus, device and function number
//          bReg  - Register number to read
//
// Output:  IO register to write the value
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT16
WritePCIConfig(UINT16 wBDF, UINT8 bReg)
{
    DwordWriteIO(0xCF8, (UINT32)(0x80000000 | (wBDF<<8) | (bReg & 0xFC)));
    return (UINT16)(0xCFC+(bReg & 3));
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SpeakerBeep
//
// Description: This routine produces a sound on the internal PC speaker
//
// Input:   bFreq -     Sound frequency
//      wDuration - Sound duration in 15 microsecond units
//      fpHCStruc - Pointer to HCStruc
//
// Output:  None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
SpeakerBeep (UINT8 bFreq, UINT16 wDuration, HC_STRUC*   fpHCStruc)
{
#if USB_BEEP_ENABLE
    UINT8   bValue;
    if(gUsbData->dUSBStateFlag & USB_FLAG_ENABLE_BEEP_MESSAGE) {
        ByteWriteIO((UINT8)0x43, (UINT8)0xB6);
        ByteWriteIO((UINT8)0x42, (UINT8)bFreq);
        ByteWriteIO((UINT8)0x42, (UINT8)bFreq);
        bValue = ByteReadIO((UINT8)0x61);
        ByteWriteIO((UINT8)0x61, (UINT8)(bValue | 03));
        FixedDelay((UINTN)wDuration * 15);
        ByteWriteIO((UINT8)0x61, (UINT8)(bValue));
    }
#endif
}

#if defined(DEBUG_SWITCH) && (DEBUG_SWITCH == 1)
VOID DEBUG_DELAY()
{
    int i;
     PrintDebugMsg(3,"\nDELAY: ");
    for(i=0;i<10;i++){
        PrintDebugMsg(3,"%d..",i);
        FixedDelay(300 * 1000);        // 200 msec delay
    }
    PrintDebugMsg(3,"\n");
}
#endif

//****************************************************************************
//****************************************************************************
//**                                                                        **
//**             (C)Copyright 1985-2016, American Megatrends, Inc.          **
//**                                                                        **
//**                          All Rights Reserved.                          **
//**                                                                        **
//**                 5555 Oakbrook Pkwy, Norcross, GA 30093                 **
//**                                                                        **
//**                          Phone (770)-246-8600                          **
//**                                                                        **
//****************************************************************************
//****************************************************************************
