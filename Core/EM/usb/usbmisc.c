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
// $Header: /Alaska/SOURCE/Modules/USB/ALASKA/usbmisc.c 28    10/16/16 10:18p Wilsonlee $
//
// $Revision: 28 $
//
// $Date: 10/16/16 10:18p $
//****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/USB/ALASKA/usbmisc.c $
// 
// 28    10/16/16 10:18p Wilsonlee
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
// 27    7/07/16 1:12a Wilsonlee
// [TAG]  		EIP277810
// [Category]  	Improvement
// [Description]  	Validate the memory buffer is entirely outside of SMM.
// [Files]  		usbsb.c, amiusb.c, ehci.c, ohci.c, uhci.c, usbCCID.c,
// usbdef.h, usbmass.c, xhci.c, amiusbhc.c, efiusbccid.c, efiusbmass.c,
// uhcd.c, uhcd.h, usbmisc.c
// 
// 26    4/29/15 7:00a Wilsonlee
// [TAG]  		EIP215978
// [Category]  	Improvement
// [Description]  	Remove "TotalSize" parameter from
// AlignPhysicalAddress() .
// [Files]  		usbmisc.c
// 
// 25    4/03/14 3:44a Wilsonlee
// [TAG]  		EIP156742
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	System hang at 0x9C during DC cycle test under RHEL6.5
// UEF.I
// [RootCause]  	The hw smi may be triggered when we reallocate memory for
// gUsbData->HcTable.
// [Solution]  	Assign the new memory space to gUsbData->HcTable before we
// free the old.
// [Files]  		uhcd.c, uhcd.h, usbmisc.c
// 
// 24    3/19/13 4:00a Ryanchou
// [TAG]  		EIP118177
// [Category]  	Improvement
// [Description]  	Dynamically allocate HCStrucTable at runtime.
// [Files]  		usb.sdl, usbport.c, usbsb.c, amiusb.c, ehci.c, ohci.c,
// syskbc.c, sysnokbc.c, uhci.c, usb.c, usbCCID.c, usbdef.h, usbhid.c,
// usbhub.c, usbmass.c, usbrt.mak, usb.sd, amiusbhc.c, efiusbccid.c,
// efiusbhid.c, efiusbmass.c, efiusbms.c, uhcd.c, uhcd.h, uhcd.mak,
// usbmisc.c, usbsrc.sdl
// 
// 23    1/11/13 4:19a Ryanchou
// [TAG]  		EIP102491
// [Category]  	Improvement
// [Description]  	Synchronized with Aptio V USB module
// [Files]  		usbport.c, usbsb.c, ehci.c, ehci.h, ohci.c, ohci.h, uhci.h,
// usb.c, usbdef.h, usbhid.c, usbhub.c, usbkbd.c, usbkbd.h, usbmass.c.
// usbms.c, usbpoint.c, xhci.h, usb.sd, amiusbhc.c, componentname.c,
// efiusbkc.c, efiusbmass.c, uhcd.c, uhcd.h, usbbus.c, usbbus.h, usbmisc.c
// 
// 22    8/29/12 8:37a Ryanchou
// [TAG]  		EIP77262
// [Category]  	New Feature
// [Description]  	Remove SMM dependency of USB.
// [Files]  		usb.sdl, usbport.c, amiusb.c, amiusb.dxs, amiusb.h, ehci.c,
// elib.c, ohci.c, uhci.c, usb.c, usbdef.h, usbrt.mak, xhci.c, amiusbhc.c,
// efiusbccid.c, efiusbhid.c, efiusbkb.c, efiusbmass.c, uhcd.c, uhcd.dxs,
// uhcd.h, usbmisc.c, AmiUsbController.h
// 
// 21    5/04/12 6:43a Ryanchou
// [TAG]  		EIP82875
// [Category]  	Improvement
// [Description]  	Support start/stop individual USB host to avoid
// reconnect issues.
// [Files]  		usbport.c, usbsb.c, amiusb.c, amiusb.h, ehci.c, ohci.c,
// uhci.c, uhci.h, usb.c, usbdef.h, xhci.c, amiusbhc.c, uhcd.c, uhcd.h,
// usbbus.c, usbmisc.c
// 
// 20    11/08/11 1:59a Ryanchou
// [TAG]  		EIP63188
// [Category]  	Improvement
// [Description]  	External USB controller support.
// [Files]  		amidef.h, amiusb.c, ehci.c, ohci.c, uhcd.c, uhcd.h, uhci.c,
// usbdef.h, usbmisc.c, usbsb.c, xhci.c
// 
// 19    7/13/11 4:11a Ryanchou
// [TAG]  		EIP59332
// [Category]  	Improvement
// [Description]  	Modified the Stop function for UHCD and USBBUS to
// properly stop devices and uninstall the protocols.
// [Files]  		uhcd.c, uhcd.h, uhci.c, usbbus.c, UsbInt13.c, usbmisc.c
// 
// 18    4/06/11 3:25a Tonylo
// [TAG]  		EIP57354
// [Category]  	Improvement
// [Description]  	Core 4.6.5.0 compliant. UEFI 2.3 and PI 1.x support.
// 
// 17    2/07/11 12:44p Olegi
// [TAG]  		EIPN/A
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	Memory corruption in 32-bit mode
// [RootCause]  	AllocatePages updates 64-bit variable with the allocated
// address; in case of 32-bit project VOID* can not be passed - it will
// cause memory corruption.
// [Solution]  	Use EFI_PHYSICAL_ADDRESS instead of VOID* for memory
// allocation address.
// [Files]  		usbmisc.c
// 
// 16    10/30/09 5:48p Olegi
// 
// 15    10/09/09 5:57p Olegi
// 
// 14    2/05/09 2:53p Olegi
// Bugfix in AllocateAlignedMemory, size of the block is made 4K aligned
// for VTD. EIP#14470.
// 
// 13    7/04/08 1:02p Olegi
// AllocAlignedMemory allocates the 4K aligned block for global USB data
// area.
// 
// 12    5/16/08 12:02p Olegi
// Compliance with AMI coding standard.
// 
// 11    8/14/07 11:24a Olegi
// 
// 10    8/09/07 3:52p Artems
// Added VT-d support - USB controllers use one continuous region of
// memory
//
// 9     7/09/07 2:12p Olegi
// Changed the maximum data size of the BulkTransfer from 1kB to 64kB.
//
// 
// 8     3/20/07 1:29p Olegi
//
// 6     4/14/06 6:41p Olegi
//
// 5     3/20/06 3:37p Olegi
// Version 8.5 - x64 compatible.
//
// 4     5/20/05 11:04a Andriyn
// reconcile Aptio changes with Alaska
//
// 3     5/19/05 8:06p Olegi
// Aptio changes in driver 8.1 implementation.
//
// 2     5/10/05 4:13p Andriyn
// USBBUS implementation
//
// 1     3/28/05 6:20p Olegi
//
// 1     3/15/05 9:23a Olegi
// Initial VSS check-in.
//
//****************************************************************************


//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
//  Name:           UsbMisc.c
//
//  Description:    AMI USB driver miscellaneous routines
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "Efi.h"

#include "amidef.h"
#include "usbdef.h"
#include "uhcd.h"

#if USB_RUNTIME_DRIVER_IN_SMM
#if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x0001000A)
#include <Protocol\SmmControl2.h>

EFI_SMM_CONTROL2_PROTOCOL *gSmmCtl = NULL;
#else
#include <Protocol\SmmControl.h>

EFI_SMM_CONTROL_PROTOCOL *gSmmCtl = NULL;
#endif
#endif

BOOLEAN gFirstCall = TRUE;
VOID *gGlobalPointer;
VOID *gStartPointer;
VOID *gEndPointer;

extern USB_GLOBAL_DATA             *gUsbData;
extern EFI_USB_PROTOCOL            *gAmiUsbController;

#if USB_RUNTIME_DRIVER_IN_SMM
//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        USBGenerateSWSMI
//
// Description: Generates SW SMI using global SmmCtl pointer.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
USBGenerateSWSMI (
    UINT8   Data
)
{
					                            //(EIP57354)>
	EFI_STATUS Status;
	UINT8 SwSmiValue = Data;
#if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x0001000A)
	UINT8 DataSize = 1;
#else
	UINTN DataSize = 1;
#endif

	if (gSmmCtl == NULL) {
#if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x0001000A)
		Status = gBS->LocateProtocol(&gEfiSmmControl2ProtocolGuid, NULL, &gSmmCtl);
#else
		Status = gBS->LocateProtocol(&gEfiSmmControlProtocolGuid, NULL, &gSmmCtl);
#endif
		if (EFI_ERROR(Status)){
			return;
		}
	}
					                            //<(EIP57354)
    gSmmCtl->Trigger(gSmmCtl, &SwSmiValue, &DataSize, 0, 0);
}
#endif

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        InvokeUsbApi
//
// Description: 
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
InvokeUsbApi(
	URP_STRUC *Urp
)
{
#if	USB_RUNTIME_DRIVER_IN_SMM
	UINTN		Temp;

	Temp = (UINTN)gUsbData->fpURP;
	gUsbData->fpURP = Urp;

	USBGenerateSWSMI (USB_SWSMI);

	gUsbData->fpURP = (URP_STRUC*)Temp;
    
#else
    EFI_TPL               OldTpl;
    OldTpl = gBS->RaiseTPL(TPL_NOTIFY);

	if (gAmiUsbController->UsbInvokeApi) {
		gAmiUsbController->UsbInvokeApi(Urp);
	}
	gBS->RestoreTPL(OldTpl);
#endif
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        MemFill
//
// Description: Fills the specified amount of memory with specified data
//              starting from the specified address.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
MemFill (
    UINT8* Ptr,
    UINT32 Size,
    UINT8  Value
)
{
    UINT32      Count;

    // Check for pointer validity
    if (Ptr == NULL) return;
    for(Count = 0; Count < Size; Count++) {
        Ptr[Count] = Value;
    }
    return;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        AlignPhysicalAddress
//
// Description: Returns the aligned address.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINTN
AlignPhysicalAddress(
    UINTN   PhyAddress,
    UINT16  AlignSize
)
{
    UINTN   AlignAddr;

    USB_DEBUG(DEBUG_LEVEL_7, "Un-aligned address : %lX\n", PhyAddress);
    if ((PhyAddress % AlignSize) != 0) {
        AlignAddr = PhyAddress - (PhyAddress % (UINT32)AlignSize) + AlignSize;
    }
    else {
        AlignAddr = PhyAddress;
    }
    USB_DEBUG(DEBUG_LEVEL_7, "Aligned address : %lX\n", AlignAddr);

    return AlignAddr;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        AllocAlignedMemory
//
// Description: Allocates memory with the given alignment.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID*
AllocAlignedMemory (
    UINT32 AllocSize,
    UINT16 Align
)
{
    UINTN   Ptr;
    UINT32  Size;
    EFI_STATUS  Status;
    EFI_PHYSICAL_ADDRESS    MemAddress;

    if (AllocSize == 0) return NULL;
    //
    // If this is the first time the function is called,
    // allocate the USB memory and make the size 4K aligned (VTD).
    //
    if(gFirstCall) {
        gFirstCall = FALSE;                 // Make sure to only allocate once.
        Size = CalculateMemorySize();       // Determine total required size.
        Size = (Size + 0x1000) >> 12;       // Express Size in pages.
        //
        // Allocate and zero memory in pages.
        //
        MemAddress = 0xFFFFFFFF;
        Status = gBS->AllocatePages(AllocateMaxAddress, EfiRuntimeServicesData,
                Size, &MemAddress);
        ASSERT_EFI_ERROR(Status);

        gGlobalPointer = (VOID*)(UINTN)MemAddress;
        MemFill (gGlobalPointer, (Size << 12), 0);  // Have to express size in bytes for MemFill()
        //
        // Save pointers to beginning and end of region.
        //
        gStartPointer = gGlobalPointer;
        gEndPointer = (VOID *)((UINTN)gGlobalPointer + (Size << 12) - 1);
    }

    //USB_DEBUG(DEBUG_LEVEL_6, "Unaligned : %Fp, %X, %X\n", gGlobalPointer, AllocSize, Align);
    Ptr  = AlignPhysicalAddress( (UINTN)gGlobalPointer, Align);
    //USB_DEBUG(DEBUG_LEVEL_6, "Aligned : %Fp, %X, %X\n", Ptr, AllocSize, Align);

    gGlobalPointer = (VOID*)(Ptr + AllocSize);

    if (gGlobalPointer < gEndPointer)
    {
        return (VOID*)Ptr;
    }
    return NULL;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        AllocateHcMemory
//
// Description: Allocates a number of pages with the given alignment.
//
// Note:        The minimum alignment passed to this function is CPU page, 4K
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID *
AllocateHcMemory (
	IN EFI_PCI_IO_PROTOCOL	*PciIo,
    IN UINTN            	Pages,
    IN UINTN            	Alignment
)
{
    EFI_STATUS            Status;
    VOID                  *Memory;
    UINTN                 AlignedMemory;
    UINTN                 AlignmentMask;
    UINTN                 UnalignedPages;
    UINTN                 RealPages;

    //
    // Alignment must be a power of two or zero.
    //
    ASSERT ((Alignment & (Alignment - 1)) == 0);
 
    if (Pages == 0) {
        return NULL;
    }
    if (Alignment > EFI_PAGE_SIZE) {
        //
        // Caculate the total number of pages since alignment is larger than page size.
        //
        AlignmentMask  = Alignment - 1;
        RealPages      = Pages + EFI_SIZE_TO_PAGES (Alignment);
        //
        // Make sure that Pages plus EFI_SIZE_TO_PAGES (Alignment) does not overflow.
        //
        ASSERT (RealPages > Pages);

 		Memory = (VOID*)0xFFFFFFFF;
        Status = PciIo->AllocateBuffer (PciIo, AllocateMaxAddress, EfiRuntimeServicesData, RealPages,
        			&Memory, 0);
        if (EFI_ERROR (Status)) {
            return NULL;
        }
        AlignedMemory  = ((UINTN) Memory + AlignmentMask) & ~AlignmentMask;
        UnalignedPages = EFI_SIZE_TO_PAGES (AlignedMemory - (UINTN) Memory);
        if (UnalignedPages > 0) {
            //
            // Free first unaligned page(s).
            //
            Status = PciIo->FreeBuffer(PciIo, UnalignedPages, Memory);
            ASSERT_EFI_ERROR (Status);
        }
        Memory         = (VOID*)(AlignedMemory + EFI_PAGES_TO_SIZE (Pages));
        UnalignedPages = RealPages - Pages - UnalignedPages;
        if (UnalignedPages > 0) {
            //
            // Free last unaligned page(s).
            //
			Status = PciIo->FreeBuffer(PciIo, UnalignedPages, Memory);
            ASSERT_EFI_ERROR (Status);
        }
    } else {
        //
        // Do not over-allocate pages in this case.
        //
        Memory = (VOID*)0xFFFFFFFF;
		Status = PciIo->AllocateBuffer (PciIo, AllocateMaxAddress, EfiRuntimeServicesData, Pages,
					 &Memory, 0);
        if (EFI_ERROR (Status)) {
            return NULL;
        }
        AlignedMemory  = (UINTN) Memory;
    }
    return (VOID*) AlignedMemory;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        FreeHcMemory
//
// Description: Free the memory allocated by AllocateHcMemory().
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
FreeHcMemory(
	IN EFI_PCI_IO_PROTOCOL	*PciIo,
	IN UINTN				Pages,
	IN VOID*				Memory
)
{
	EFI_STATUS            Status;

	Status = PciIo->FreeBuffer(PciIo, Pages, Memory);
	ASSERT_EFI_ERROR(Status);
	return;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        ReallocateMemory
//
// Description: 
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
ReallocateMemory (
  IN UINTN  OldSize,
  IN UINTN  NewSize,
  IN VOID   **OldBuffer
)
{
	EFI_STATUS  Status;
    VOID        *NewBuffer = NULL;
	VOID		*FreeBuffer = NULL;

	if (OldBuffer == NULL) {
		return EFI_INVALID_PARAMETER;
	}

	Status = gBS->AllocatePool (EfiRuntimeServicesData, NewSize, &NewBuffer);
    if (EFI_ERROR(Status)) {
        return Status;
    }

    gBS->SetMem(NewBuffer, NewSize, 0);

	if (OldSize > 0 && *OldBuffer != NULL) {
		gBS->CopyMem(NewBuffer, *OldBuffer, (OldSize < NewSize) ? OldSize : NewSize);
		FreeBuffer = *OldBuffer;
	}

	*OldBuffer = NewBuffer;

    if (FreeBuffer != NULL) {
        gBS->FreePool(FreeBuffer);
    }
    return EFI_SUCCESS;
}

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
