//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**           5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093      **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/CSM/Generic/Thunk/INT13/CsmBlockIo.c 51    9/09/15 11:46a Olegi $
//
// $Revision: 51 $
//
// $Date: 9/09/15 11:46a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/CSM/Generic/Thunk/INT13/CsmBlockIo.c $
// 
// 51    9/09/15 11:46a Olegi
// [TAG]  		EIP237391
// [Description]  	Aptio4 CSM: CsmBlockIo drive handle is lost
// 
// 50    9/09/15 11:26a Olegi
// cleanup
// 
// 49    8/06/14 1:20p Fasihm
// [TAG]           EIP180668
// [Category]      Bug Fix
// [Severity]      Normal
// [Symptom]       Aptio 4 CSM: CsmBlkIO: Start function might incorrectly
// initialize IBV fields in BBS table.
// [Solution]      Maintain the number of newly created BBS entries;
// initialize IBV fields only for those entries created by the Option ROM.
// [Files]
//         Core\EM\CSM\thunk\BlockIo\CsmBlockIo.c
// 
// 48    12/23/13 3:38p Olegi
// EIP128504: implement EFI_COMPONENT_NAME2_PROTOCOL for CsmBlockIo driver
// 
// 47    12/23/13 3:14p Olegi
// EIP148138: use AMI_BLOCKIO_WRITE_PROTECTION_PROTOCOL instead of
// EFI_MBR_WRITE_PROTECTION_PROTOCOL
// 
// 46    12/23/13 10:22a Olegi
// EIP148123: CSM includes file which name has been changed
// 
// 45    12/06/13 12:07a Rameshr
// [TAG]  		EIP143793
// [Category]  	Improvement
// [Description]  	For onboard Raid controller, consumed
// DevicePathProtocol - By driver and as a child controller, instead of
// the PciIo Protocol. Because PciIo protocol us already consumed by
// SataController driver.
// [Files]  		CsmBlockIo.c
// 
// 44    7/01/13 5:56a Kapilporwal
// [TAG]  		EIP125560
// [Category]  	Improvement
// [Description]  	 	Please support Boot Sector Virus Protection for CSM
// Disabled Mode
// [Files]  		VirusProtect.c, VirusProtect.dxs, AhciBus.c,
// AhciController.c, CsmBlockIo.c, CsmInt13.c, Ata.c, IdeBus.c,
// SdioBlkIo.c, SdioDriver.c, efiusbmass.c
// 
// 43    3/07/13 10:47p Olegi
// [TAG]  		EIP117323
// [Category]  	New Feature
// [Description]  	Fiber Channel controllers support in CsmBlockIo
// 
// 42    12/14/12 3:29p Olegi
// 
// 41    12/23/11 2:12p Olegi
// [TAG]  		EIP78921
// [Category]  	Improvement
// [Description]  	CsmBlockIo should create device handle in BBS table
// [Files]  		CsmBlockIo.c
// CsmBlockIo.h
// 
// 39    11/10/11 7:15p Olegi
// Installed thunk driver GUID
// 
// 38    11/04/11 12:41p Olegi
// 
// 37    8/15/11 9:45a Olegi
// 
// 36    8/12/11 3:05p Olegi
// Correction to the previous check-in: in Supported function some
// protocols can not be open BY_DRIVER for the onboard RAID. Changed the
// OpenProtocol attributes.
// 
// 35    8/10/11 11:48a Olegi
// GUID and variable names are corrected; Supported function modified to
// close PciIo protocol right after it is used. EIP49352.
// 
// 34    7/20/11 12:21p Olegi
// Added dependency on the HDD security SDL token.
// 
// 33    6/27/11 4:50p Olegi
// Cleaning the headers and the comments. Change in Supported function
// that partially undoing EIP39017 and allows non-Intel RAID option ROMs
// produce BlkIo.
// 
// 32    4/27/11 6:47p Olegi
// [TAG]  		EIP54911
// [Category]  	Improvement
// [Description]  	Start function modified to return the proper value.
// [Files]  		CsmBlockIo.c
// 
// 31    1/19/11 10:19a Olegi
// 
// 29    12/14/10 12:08p Olegi
// [TAG]  		EIP48212
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	Some controllers are not enabled before executing their
// Option ROM
// [RootCause]  	There is no code that enable a device in CsmBlockIo start
// function.
// [Solution]  	Added a call that enables device to the CsmBlockIo start
// function.
// [Files]  		CsmBlockIo.c, PciInterrupts.c
// 
// 28    7/29/10 3:20p Olegi
// EIP39017:: Added code in Supported function to prevent BlockIo from
// binding prematurely.
// 
// 27    3/12/10 9:49a Olegi
// Onboard RAID option ROM related changes. EIP34602.
// 
// 26    1/12/10 11:50a Olegi
// Copyright message updated.
// 
// 25    8/07/09 2:46p Rameshr
// SD boot support Added.
// 
// 24    10/04/07 3:04p Olegi
// Bugfix in CsmBlockIoStart for HW interrupt save/restore in case of
// multiple drives connected.
// 
// 23    10/03/07 4:41p Yakovlevs
// Removed Component Name Protocol and its Strings in NO DEBUG mode to
// save some space. 
// 
// 22    4/27/07 5:14p Olegi
// CSM.CHM file preparation.
//
// 21    4/13/07 9:37a Olegi
//
// 20    3/29/07 5:51p Olegi
//
// 19    3/29/07 1:37p Felixp
// Bug fix in BuildDevicePath: properly initialize device path for unknown
// devices
//
// 18    12/07/06 3:13p Olegi
// Support for embedded OpROMs added.
//
// 17    7/31/06 4:11p Olegi
//
// 16    5/19/06 11:25p Felixp
// Device Path code updated to use NEXT_NODE/NODE_LENGTH/SET_NODE_LENGTH
// macros to remove direct access to the Length field
//
// 15    5/01/06 3:57p Olegi
// CheckPciRom will be called from LegacyBios.InstallPciRom, no need to
// call it again.
//
// 14    3/13/06 4:15p Felixp
//
// 13    3/13/06 2:38p Felixp
//
// 12    10/13/05 6:21p Olegi
// Added HW interrupt handling
//
// 11    8/30/05 9:06a Olegi
// BuildDevicePath correction.
//
// 10    7/26/05 2:51p Olegi
//
// 9     6/23/05 5:26p Olegi
//
// 8     6/22/05 8:34a Olegi
//
// 7     4/20/05 4:16p Olegi
// INT 13 vector maintenance has been moved to the main CSM module.
//
// 6     4/12/05 12:21p Olegi
//
// 5     3/16/05 11:05a Olegi
//
// 4     3/04/05 1:45p Mandal
//
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:    CsmBlockIo.c
//
// Description: CSM Block I/O Module. Main module, containing entry,
//              supported, start, and stop functions.
//
//<AMI_FHDR_END>
//**********************************************************************

#include "CsmBlockIo.h"
#include <Protocol\Legacy8259.h>
#include <Protocol\IdeControllerInit.h>

#if defined CORE_COMBINED_VERSION && (CORE_COMBINED_VERSION > 0x4028E)
#include <Protocol\AmiBlockIoWriteProtection.h>
AMI_BLOCKIO_WRITE_PROTECTION_PROTOCOL *gBlockIoWriteProtectionProtocol = NULL;
#endif

// EFI Driver Binding Protocol Instance
EFI_DRIVER_BINDING_PROTOCOL gCsmBlockIoDriverBinding = {
    CsmBlockIoSupported,
    CsmBlockIoStart,
    CsmBlockIoStop,
    0x10,
    NULL,
    NULL
};

#ifndef EFI_COMPONENT_NAME2_PROTOCOL_GUID //old Core
EFI_GUID gComponentNameProtocolGuid = EFI_COMPONENT_NAME_PROTOCOL_GUID;
extern EFI_COMPONENT_NAME_PROTOCOL gCsmBlockIoComponentName;
#else
EFI_GUID gComponentNameProtocolGuid = EFI_COMPONENT_NAME2_PROTOCOL_GUID;
extern EFI_COMPONENT_NAME2_PROTOCOL gCsmBlockIoComponentName;
#endif

// Number of current users of this driver
UINTN mCurrentUsers = 0;

// Real mode buffer to contain the buffers below
EFI_PHYSICAL_ADDRESS        mRealModeBuffer = 0;

// Packet buffer under 1 MB for all version EDD calls
EDD_DEVICE_ADDRESS_PACKET   *mEDDPacketBuffer;

// EDD 1.1 transfer buffer
VOID                        *mEDDTransferBuffer;

// This is a buffer for INT 13h func 48 information
CSM_LEGACY_DRIVE            *mDriveParameterBuffer;

// The following variables will track the onboard mass storage controller
// in RAID mode with the Option ROM that can not handle ATAPI devices:
//
//  - gOnboardRaidGuid is GUID installed on such controller in SBDXE
//  - gOnboardRaid is the switch indicating the requested controller
//    has gOnboardRaidGuid installed on it
//
#define ONBOARD_RAID_GUID \
    { 0x5d206dd3, 0x516a, 0x47dc, {0xa1, 0xbc, 0x6d, 0xa2, 0x4, 0xaa, 0xbe, 0x8}};
EFI_GUID    gOnboardRaidGuid = ONBOARD_RAID_GUID;

// The following GUID is used to ensure the Start function is executed after all
// individual drives in RAID are unlocked before RAID Option ROM is executed
//
#define HDD_UNLOCKED_GUID \
    { 0x1fd29be6, 0x70d0, 0x42a4, {0xa6, 0xe7, 0xe5, 0xd1, 0xe, 0x6a, 0xc3, 0x76}};
EFI_GUID gHddUnlockedGuid = HDD_UNLOCKED_GUID;

#define LTEB_GUID  \
    {0xC8BCA618, 0xBFC6, 0x46B7, 0x8D, 0x19, 0x83, 0x14, 0xE2, 0xE5, 0x6E, 0xC1}

EFI_GUID gLTEBGuid = LTEB_GUID;

VOID CsmBlockIoComebackFromLegacyBoot(EFI_EVENT, VOID*);


//<AMI_PHDR_START>
//**********************************************************************
//
// Procedure:   CsmBlockIoEntryPoint
//
// Description:
//  This is the CsmBlockIo driver entry point. It installs
//  gCsmBlockIoDriverBinding protocol
//
//**********************************************************************
//<AMI_PHDR_END>

EFI_STATUS
CsmBlockIoEntryPoint (
    IN EFI_HANDLE           ImageHandle,
    IN EFI_SYSTEM_TABLE     *SystemTable
    )

{
    static EFI_GUID gCsmThunkDriverGuid =
        { 0x2362ea9c, 0x84e5, 0x4dff, 0x83, 0xbc, 0xb5, 0xac, 0xec, 0xb5, 0x7c, 0xbb };

    gCsmBlockIoDriverBinding.DriverBindingHandle = ImageHandle;
    gCsmBlockIoDriverBinding.ImageHandle = ImageHandle;

    InitAmiLib(ImageHandle, SystemTable);

    return pBS->InstallMultipleProtocolInterfaces(
        &gCsmBlockIoDriverBinding.DriverBindingHandle,
        &gEfiDriverBindingProtocolGuid, &gCsmBlockIoDriverBinding,
        &gComponentNameProtocolGuid, &gCsmBlockIoComponentName,
        &gCsmThunkDriverGuid, NULL,
        NULL
    );
}

//<AMI_PHDR_START>
//**********************************************************************
//
// Procedure:   CsmBlockIoSupported
//
// Description:
//  This is a binding protocol function. It checks whether or not this
//  driver supports the given controller
//  
//
// Input:
//  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
//  IN EFI_HANDLE                     Controller,
//  IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
//
//**********************************************************************
//<AMI_PHDR_END>

EFI_STATUS
CsmBlockIoSupported (
    IN EFI_DRIVER_BINDING_PROTOCOL  *This,
    IN EFI_HANDLE                   Controller,
    IN EFI_DEVICE_PATH_PROTOCOL     *RemainingDevicePath
    )
{
    EFI_STATUS                  Status;
    EFI_LEGACY_BIOS_PROTOCOL    *LegacyBios;
    EFI_DEVICE_PATH_PROTOCOL    *ParentDevicePath;
    EFI_PCI_IO_PROTOCOL         *PciIo;
    PCI_STD_DEVICE              Pci;
    VOID                        *IdeControllerInterface;

    // See if the Legacy BIOS Protocol is available
    Status = pBS->LocateProtocol( &gEfiLegacyBiosProtocolGuid,
                    NULL, (VOID**)&LegacyBios);
    if (EFI_ERROR (Status)) {
        return Status;
    }

    // Check whether DevicePath Protocol has been installed on this controller
    Status = pBS->OpenProtocol( Controller,
                    &gEfiDevicePathProtocolGuid,
                    (VOID**)&ParentDevicePath,
                    This->DriverBindingHandle,
                    Controller,
                    EFI_OPEN_PROTOCOL_BY_DRIVER );

    if (EFI_ERROR (Status)) {
        return Status;
    }

    pBS->CloseProtocol (
                    Controller,
                    &gEfiDevicePathProtocolGuid,
                    This->DriverBindingHandle,
                    Controller);

    // Check whether this is Onboard RAID
    Status = pBS->OpenProtocol( Controller,
                    &gOnboardRaidGuid,
                    NULL,
                    This->DriverBindingHandle,
                    Controller,
                    EFI_OPEN_PROTOCOL_TEST_PROTOCOL );

    // Do the checkings/manipulations with the onboard RAID
    if(!EFI_ERROR(Status))
    {
        // Make sure drives are unlocked
#if defined SETUP_IDE_SECURITY_SUPPORT && SETUP_IDE_SECURITY_SUPPORT == 1
        Status = pBS->OpenProtocol( Controller,
                    &gHddUnlockedGuid,
                    NULL,
                    This->DriverBindingHandle,
                    Controller,
                    EFI_OPEN_PROTOCOL_TEST_PROTOCOL );
#endif
        if(EFI_ERROR(Status)) {
            return EFI_UNSUPPORTED;
        }

        // Make sure IDE_CONTROLLER_PROTOCOL is installed; this ensures the
        // controller is initialized
        Status = pBS->OpenProtocol( Controller,
                    &gEfiIdeControllerInitProtocolGuid,
                    (VOID **)&IdeControllerInterface,
                    This->DriverBindingHandle,     
                    Controller,   
                    EFI_OPEN_PROTOCOL_TEST_PROTOCOL);

        if (EFI_ERROR(Status)) {
            return EFI_UNSUPPORTED;
        }

        return EFI_SUCCESS;
    }

    // Check whether PCI Protocol has been installed on this controller
    Status = pBS->OpenProtocol( Controller,
                    &gEfiPciIoProtocolGuid,
                    (VOID**)&PciIo,
                    This->DriverBindingHandle,
                    Controller,
                    EFI_OPEN_PROTOCOL_BY_DRIVER );

    if  (EFI_ERROR(Status)) return Status;

    // Read PCI configuration
    Status = PciIo->Pci.Read (PciIo,
                    EfiPciIoWidthUint32,
                    0,
                    sizeof (Pci) / sizeof (UINT32),
                    &Pci);
    if (EFI_ERROR(Status)) return Status;

    pBS->CloseProtocol( Controller,
        &gEfiPciIoProtocolGuid,
        This->DriverBindingHandle,
        Controller );


    //  Status is EFI_SUCCESS here

    if ( Pci.Header.ClassCode[2] != PCI_CL_MASS_STOR && \
            (Pci.Header.ClassCode[2] != PCI_BASE_CLASS_INTELLIGENT || \
            Pci.Header.ClassCode[1] != PCI_SUB_CLASS_INTELLIGENT) )
    {
        Status = EFI_UNSUPPORTED;
    }
	if ( Pci.Header.ClassCode[1] == PCI_CL_SYSTEM_PERIPHERALS_SCL_SD && \
		 Pci.Header.ClassCode[2] == PCI_CL_SYSTEM_PERIPHERALS ) 
    {
        Status = EFI_SUCCESS;
    }
    if ( Pci.Header.ClassCode[1] ==  PCI_CL_SER_BUS_SCL_FIBCHAN &&
        Pci.Header.ClassCode[2] == PCI_CL_SER_BUS ) 
    {
        Status = EFI_SUCCESS;
    }

//    TRACE((-1, "\nCsmBlockIo.Supported: called for VID/DID: %x %x, CL %x SCL %x; Status = %r\n",
//        Pci.Header.VendorId, Pci.Header.DeviceId, Pci.Header.ClassCode[2], Pci.Header.ClassCode[1], Status));

    return Status;
}


//<AMI_PHDR_START>
//**********************************************************************
//
// Procedure:   CsmBlockIoStart
//
// Description:
//  Installs BlockIoProtocol using INT13 services produced by Option ROM
//
// Input:
//  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
//  IN EFI_HANDLE                     Controller,
//  IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
//
// Notes:
//  Here is the control flow of this function:
//  1. Open PCI and Devicepath protocol
//  2. Enable the device
//  3. Post the option rom
//  4. If first time, allocate buffer for real mode thunk code
//  5. For each disk...
//     a. Allocate and initialize a private structure
//     b. Install block I/O protocol on a new child device
//     c. Open the child device
//  6. Increment user counter
//
//**********************************************************************
//<AMI_PHDR_END>

EFI_STATUS
CsmBlockIoStart (
    IN EFI_DRIVER_BINDING_PROTOCOL  *This,
    IN EFI_HANDLE                   Controller,
    IN EFI_DEVICE_PATH_PROTOCOL     *RemainingDevicePath
)
{
    EFI_STATUS                Status;
    EFI_LEGACY_BIOS_PROTOCOL  *LegacyBios;
    EFI_PCI_IO_PROTOCOL       *PciIo = NULL;
    UINT8                     FirstDisk;
    UINT8                     LastDisk;
    UINT8                     x = 0;
    CSM_BLOCK_IO_DEV          *PrivateBlockIoStruc = NULL;
    EFI_DEVICE_PATH_PROTOCOL  *PciDevPath;
    UINTN                     i = 0;
    UINTN                     Flags;
    UINTN                     TempAddress = 0;
    UINT8                     irq = 0;
    EFI_LEGACY_8259_PROTOCOL  *i8259;
    UINT32                      *ivt = (UINT32*)0;
    UINT32                      TempInt;
    UINT32                      HwInterruptHandler;
    UINT64                      Capabilities;
    UINT8                       j = 0;
    UINT8                       BbsCount;
    BBS_TABLE*                  BbsEntry = NULL;
    BBS_TABLE*                  BbsTable = NULL;
    BOOLEAN                     BbsEntryPresent[MAX_BBS_ENTRIES_NO] = {0};
    UINTN                       FirstNewBbsEntry = 0;
    EFI_LEGACY_BIOS_EXT_PROTOCOL *LegacyBiosExt;
    BOOLEAN                     OnboardRaidController=FALSE;
    EFI_DEVICE_PATH_PROTOCOL    *ChildPciDevPath;
    UINT8   NumberOfBbsEntriesBeforeOprom = 0;
    UINT8   NumberOfBbsEntriesAfterOprom = 0;
    UINT8   NewBbsEntries;

    // See if the Legacy BIOS Protocol is available
    Status = pBS->LocateProtocol( &gEfiLegacyBiosProtocolGuid,
                NULL, (VOID **)&LegacyBios);
    if (EFI_ERROR (Status)) {
        return Status;
    }

    // See if the Legacy BIOS Ext Protocol is available
    Status = pBS->LocateProtocol ( &gEfiLegacyBiosExtProtocolGuid,
                    NULL, (VOID**)&LegacyBiosExt);
    if (EFI_ERROR (Status)) {
        return Status;
    }

#if defined CORE_COMBINED_VERSION && (CORE_COMBINED_VERSION > 0x4028E)
    if(gBlockIoWriteProtectionProtocol == NULL)
        pBS->LocateProtocol(&gAmiBlockIoWriteProtectionProtocolGuid, NULL, &gBlockIoWriteProtectionProtocol); 
#endif
    Status = pBS->OpenProtocol( Controller,
                &gEfiDevicePathProtocolGuid,
                (VOID**)&PciDevPath,
                This->DriverBindingHandle,
                Controller,
                EFI_OPEN_PROTOCOL_BY_DRIVER );

    if (EFI_ERROR (Status)) {
        return Status;
    }

    // Check whether this is Onboard RAID
    Status = pBS->OpenProtocol( Controller,
                    &gOnboardRaidGuid,
                    NULL,
                    This->DriverBindingHandle,
                    Controller,
                    EFI_OPEN_PROTOCOL_TEST_PROTOCOL );

    if (!EFI_ERROR (Status)) {
        OnboardRaidController=TRUE;
    }
    
    //  Open PCI I/O Protocol
    if (OnboardRaidController) {
        Status = pBS->OpenProtocol( Controller,
                &gEfiPciIoProtocolGuid,
                (VOID **)&PciIo,
                This->DriverBindingHandle,
                Controller,
                EFI_OPEN_PROTOCOL_GET_PROTOCOL );

    } else {
        Status = pBS->OpenProtocol( Controller,
                &gEfiPciIoProtocolGuid,
                (VOID **)&PciIo,
                This->DriverBindingHandle,
                Controller,
                EFI_OPEN_PROTOCOL_BY_DRIVER );
    }

    if  ( EFI_ERROR(Status) ) {
        return Status;
    }

    // Get the hardware interrupt vector and its handler pointer
    Status = PciIo->Pci.Read(PciIo, EfiPciIoWidthUint8, 0x3C, 1, &irq);
    ASSERT_EFI_ERROR(Status);
    if (irq > 0 && irq < 0xF) {
        Status = pBS->LocateProtocol(&gEfiLegacy8259ProtocolGuid, NULL, &i8259);
        ASSERT_EFI_ERROR(Status);

        Status = i8259->GetVector (i8259, irq, &irq);   // irq has INT number
        ASSERT_EFI_ERROR(Status);
    }

    // Store HW interrupt vector, to be restored for PnP ROMs
    TempInt = ivt[irq];

    // Enable the device
    Status = PciIo->Attributes (PciIo,
            EfiPciIoAttributeOperationSupported, 0,
            &Capabilities);     // Get device capabilities

    ASSERT_EFI_ERROR(Status);

    Status = PciIo->Attributes (PciIo,
            EfiPciIoAttributeOperationEnable,
            Capabilities & EFI_PCI_DEVICE_ENABLE,
            NULL);              // Enable device
    ASSERT_EFI_ERROR(Status);

    // Check to see if there is a legacy option ROM image associated with this PCI device
    Status = LegacyBios->CheckPciRom (LegacyBios,
            Controller,
            NULL,
            NULL,
            &Flags
    );

    if ( EFI_ERROR(Status) ) {
        Status = EFI_SUCCESS;
        goto Done;
    }

    // Get BBS table
    Status = LegacyBiosExt->GetBbsTable(
                           &BbsEntry,
                           &BbsCount);
    ASSERT_EFI_ERROR(Status);
    BbsTable = BbsEntry;

    // Loop through table and note entries which are populated
    for (i = 0; i < MAX_BBS_ENTRIES_NO; i++, BbsEntry++) {
    
        if (BbsEntry->BootPriority == BBS_IGNORE_ENTRY) 
            continue;

        BbsEntryPresent[i] = TRUE;
        NumberOfBbsEntriesBeforeOprom++;
    }

    // Post the legacy option ROM if it is available.
    Status = LegacyBios->InstallPciRom( LegacyBios,
                Controller,
                NULL,
                &Flags,
                &FirstDisk,
                &LastDisk,
                NULL,
                NULL );
    if (EFI_ERROR (Status)) {
        goto Done;
    }

    BbsEntry = BbsTable;

    // Loop through BBS table and find first new entry, added due to OpROM execution
    for (i = 0; i < MAX_BBS_ENTRIES_NO; i++, BbsEntry++) {
        if (BbsEntry->BootPriority == BBS_IGNORE_ENTRY) 
            continue;
        if ((BbsEntryPresent[i] == FALSE) && (FirstNewBbsEntry == 0)) {
            FirstNewBbsEntry = i;
        }
        NumberOfBbsEntriesAfterOprom++;
    }

    ASSERT(NumberOfBbsEntriesAfterOprom >= NumberOfBbsEntriesBeforeOprom);
    NewBbsEntries = NumberOfBbsEntriesAfterOprom - NumberOfBbsEntriesBeforeOprom;

    HwInterruptHandler = ivt[irq];

    //  All users share a buffer under 1MB to put real mode thunk code in
    //  If it has not been allocated, then we allocate it.
    if (mRealModeBuffer == 0) {
        //  Allocate below 1MB
        mRealModeBuffer = 0x00000000000FFFFF;
        Status = pBS->AllocatePages( AllocateMaxAddress,
            EfiBootServicesData,
            BLOCK_IO_BUFFER_PAGE_SIZE,
            &mRealModeBuffer );

        //  Check memory allocation success
        if (EFI_ERROR (Status)) {
            ASSERT_EFI_ERROR (Status);
            mRealModeBuffer = 0;
            Status = EFI_OUT_OF_RESOURCES;
            goto Done;
        }

        //  Set up real mode memory for Thunk
        TempAddress = (UINTN)mRealModeBuffer;
        //  Setup the EDD 1.1 transfer buffer
        TempAddress += AlignAddress(TempAddress);
        mEDDTransferBuffer = (VOID *)(TempAddress);
        //  Setup the Legacy Drive buffer
        TempAddress += MAX_EDD11_XFER;
        TempAddress += AlignAddress(TempAddress);
        mDriveParameterBuffer = (CSM_LEGACY_DRIVE *)(TempAddress);
        //  Setup the EDD Packet buffer
        TempAddress += sizeof (CSM_LEGACY_DRIVE);
        TempAddress += AlignAddress(TempAddress);
        mEDDPacketBuffer = (EDD_DEVICE_ADDRESS_PACKET *)TempAddress;
    }

    //  Allocate the private device structure for each disk
    for (i = FirstDisk, j = 0; i < LastDisk; i++, j++) {

        Status = pBS->AllocatePool( EfiBootServicesData,
                sizeof (CSM_BLOCK_IO_DEV),
                &PrivateBlockIoStruc );

        if (EFI_ERROR(Status)) {
            pBS->CloseProtocol( Controller,
                        &gEfiPciIoProtocolGuid,
                        This->DriverBindingHandle,
                        Controller );

            pBS->CloseProtocol( Controller,
                        &gEfiDevicePathProtocolGuid,
                        This->DriverBindingHandle,
                        Controller );

            if (mRealModeBuffer != 0 && mCurrentUsers == 0) {
                pBS->FreePages (mRealModeBuffer, BLOCK_IO_BUFFER_PAGE_SIZE);
                mRealModeBuffer = 0;
            }

            return Status;
        }

        // Zero the private device structure
        pBS->SetMem (PrivateBlockIoStruc, sizeof (CSM_BLOCK_IO_DEV), 0);

        // Initialize the private device structure
        PrivateBlockIoStruc->ControllerHandle   = Controller;
        PrivateBlockIoStruc->LegacyBios         = LegacyBios;
        PrivateBlockIoStruc->PciIo              = PciIo;

        PrivateBlockIoStruc->Drive.Floppy       = FALSE;
        x = (i & 0x40)? 0x40 : 0;
        if (x) {
            PrivateBlockIoStruc->HwInt          = irq;
            PrivateBlockIoStruc->HwIntHandler   = HwInterruptHandler;
            ivt[irq]                            = TempInt;  // Restore HW interrupt
        }
        PrivateBlockIoStruc->Drive.Number       = (UINT8) i - x;
        PrivateBlockIoStruc->Drive.Letter       = (UINT8)(i - x - 0x80  + 'C');
        PrivateBlockIoStruc->BlockMedia.RemovableMedia = FALSE;

        if (InitBlockIo (PrivateBlockIoStruc)) {
            BuildDevicePath( PciDevPath,
                    &PrivateBlockIoStruc->Drive,
                    &PrivateBlockIoStruc->DevicePath);

            // Install the Block Io Protocol onto a new child handle
            Status = pBS->InstallMultipleProtocolInterfaces( &PrivateBlockIoStruc->Handle,
                    &gEfiBlockIoProtocolGuid,
                    &PrivateBlockIoStruc->BlockIo,
                    &gEfiDevicePathProtocolGuid,
                    PrivateBlockIoStruc->DevicePath,
                    NULL );
            if (EFI_ERROR (Status)) {
                pBS->FreePool (PrivateBlockIoStruc);
            }

            // Set handle and BCV information to which BlockIO has been installed
            if (j < NewBbsEntries)
            {
                *(UINTN*)(&(BbsTable[FirstNewBbsEntry + j].IBV1)) = (UINTN)(PrivateBlockIoStruc->Handle);
                PrivateBlockIoStruc->BcvSegment = BbsTable[FirstNewBbsEntry + j].BootHandlerSegment;
                PrivateBlockIoStruc->BcvOffset = BbsTable[FirstNewBbsEntry + j].BootHandlerOffset;
            }

            // For Onboard Raid controller use device path protocol 
            // and other Raid controller uses the PciIO protocol.	

            if(OnboardRaidController) {
                // Open For Child Device
                Status = pBS->OpenProtocol( Controller,
                    &gEfiDevicePathProtocolGuid,
                    (VOID**)&ChildPciDevPath,
                    This->DriverBindingHandle,
                    PrivateBlockIoStruc->Handle,
                    EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER );

            } else {

                // Open For Child Device
                Status = pBS->OpenProtocol( Controller,
                    &gEfiPciIoProtocolGuid,
                    (VOID**)&PrivateBlockIoStruc->PciIo,
                    This->DriverBindingHandle,
                    PrivateBlockIoStruc->Handle,
                    EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER );
            }
            
            // Register callback notification on Legacy2Efi. Use PrivateBlockInfoStruc as Context
            
            Status = pBS->CreateEventEx(
                            EVT_NOTIFY_SIGNAL,
                            TPL_CALLBACK,
                            CsmBlockIoComebackFromLegacyBoot,
                            PrivateBlockIoStruc,
                            &gLTEBGuid,
                            &PrivateBlockIoStruc->Legacy2EfiEvent);
            ASSERT_EFI_ERROR(Status);

        } else {
            pBS->FreePool (PrivateBlockIoStruc);
        }
    }  // end for loop

    mCurrentUsers++;

    return Status;

Done:
    pBS->CloseProtocol( Controller,
        &gEfiPciIoProtocolGuid,
        This->DriverBindingHandle,
        Controller );
    pBS->CloseProtocol( Controller,
        &gEfiDevicePathProtocolGuid,
        This->DriverBindingHandle,
        Controller );
    return Status;

}


//<AMI_PHDR_START>
//**********************************************************************
//
// Procedure:   CsmBlockIoStop
//
// Description: Installs IdeControllerProtocol
//
// Input:
//  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
//  IN EFI_HANDLE                     Controller,
//  IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
//
// Notes:
//  Here is the control flow of this function:
//  1. Decrement user counter
//  2. Free global buffer
//  3. Release PCI I/O protocol and Block I/O protocol for each child handle.
//  4. Shut down the hardware for each child handle.
//
//**********************************************************************
//<AMI_PHDR_END>

EFI_STATUS
CsmBlockIoStop (
    IN  EFI_DRIVER_BINDING_PROTOCOL     *This,
    IN  EFI_HANDLE                      Controller,
    IN  UINTN                           NumberOfChildren,
    IN  EFI_HANDLE                      *ChildHandleBuffer
)
{
    EFI_STATUS                  Status;
    BOOLEAN                     AllChildrenStopped;
    EFI_BLOCK_IO_PROTOCOL       *BlockIo;
    CSM_BLOCK_IO_DEV            *PrivateBlockIoStruc;
    UINTN                       i;
    BOOLEAN                     OnboardRaidController=FALSE;

    //  Decrement the number of current users
    mCurrentUsers--;

    if (mCurrentUsers == 0) {
        // Free our global buffer
        Status = pBS->FreePages (mRealModeBuffer, BLOCK_IO_BUFFER_PAGE_SIZE);
        ASSERT_EFI_ERROR (Status);
        mRealModeBuffer = 0;
    }

    // Check whether this is Onboard RAID
    Status = pBS->OpenProtocol( Controller,
                            &gOnboardRaidGuid,
                            NULL,
                            This->DriverBindingHandle,
                            Controller,
                            EFI_OPEN_PROTOCOL_TEST_PROTOCOL );

    if (!EFI_ERROR (Status)) {
        OnboardRaidController=TRUE;
    }

    AllChildrenStopped = TRUE;

    // Close protocols and shut down hardware for each child handle.
    for (i = 0; i < NumberOfChildren; i++) {

        Status = pBS->OpenProtocol( ChildHandleBuffer[i],
                            &gEfiBlockIoProtocolGuid,
                            (VOID**)&BlockIo,
                            This->DriverBindingHandle,
                            Controller,
                            EFI_OPEN_PROTOCOL_GET_PROTOCOL );

        if (EFI_ERROR (Status)) {
            return Status;
        }

        PrivateBlockIoStruc = (CSM_BLOCK_IO_DEV *) BlockIo;

        if(OnboardRaidController) {
            pBS->CloseProtocol( Controller,
                            &gEfiDevicePathProtocolGuid,
                            This->DriverBindingHandle,
                            ChildHandleBuffer[i] );
        }
        
        pBS->CloseEvent(PrivateBlockIoStruc->Legacy2EfiEvent);

        //  Release PCI I/O and Block IO Protocols on the clild handle.
        Status = pBS->UninstallMultipleProtocolInterfaces( ChildHandleBuffer[i],
                            &gEfiBlockIoProtocolGuid,
                            &PrivateBlockIoStruc->BlockIo,
                            &gEfiDevicePathProtocolGuid,
                            PrivateBlockIoStruc->DevicePath,
                            NULL );

        if (EFI_ERROR(Status)) {
            AllChildrenStopped = FALSE;
        }

        //  Shutdown the hardware
        PrivateBlockIoStruc->PciIo->Attributes (
                            PrivateBlockIoStruc->PciIo,
                            EfiPciIoAttributeOperationDisable,
                            EFI_PCI_DEVICE_ENABLE,
                            NULL);


        if(!OnboardRaidController) {
            pBS->CloseProtocol( Controller,
                            &gEfiPciIoProtocolGuid,
                            This->DriverBindingHandle,
                            ChildHandleBuffer[i] );
        }

        pBS->FreePool (PrivateBlockIoStruc);
    }  // end for loop

    if (!AllChildrenStopped) {
        return EFI_DEVICE_ERROR;
    }

    Status = pBS->CloseProtocol( Controller,
                            &gEfiDevicePathProtocolGuid,
                            This->DriverBindingHandle,
                            Controller );

    if(!OnboardRaidController) {
        Status = pBS->CloseProtocol( Controller,
                            &gEfiPciIoProtocolGuid,
                            This->DriverBindingHandle,
                            Controller);
    }

    return EFI_SUCCESS;
}


// LOCAL FUNCTIONS
//**********************************************************************

//<AMI_PHDR_START>
//**********************************************************************
//
// Procedure:   BuildDevicePath
//
// Description: Builds device path for this device
//
// Input:
//  IN  EFI_DEVICE_PATH_PROTOCOL  *BaseDevicePath,
//  IN  CSM_LEGACY_DRIVE          *Drive,
//  OUT EFI_DEVICE_PATH_PROTOCOL  **DevicePath
//
// Notes:
//  Here is the control flow of this function:
//  1. Decrement user counter
//  2. Free global buffer
//  3. Release PCI I/O protocol and Block I/O protocol for each child handle.
//  4. Shut down the hardware for each child handle.
//
//**********************************************************************
//<AMI_PHDR_END>

VOID
BuildDevicePath (
    IN  EFI_DEVICE_PATH_PROTOCOL  *BaseDevicePath,
    IN  CSM_LEGACY_DRIVE          *Drive,
    OUT EFI_DEVICE_PATH_PROTOCOL  **DevicePath
)
{
    EFI_GUID                            UnknownDevGuid = UNKNOWN_DEVICE_GUID;   // ditto
    EFI_DEV_PATH                        Node;
    UINT32                              Controller;

    Node.DevPath.Type = 0;
    if (Drive->EddVersion == EDD_VERSION_30 &&
        Drive->Parameters.StructureSize > 0x1A &&
        *(UINT32*)Drive->Parameters.InterfaceType != 0) {
        // Build device path for EDD 3.0 device
        Controller = (UINT32)Drive->Parameters.InterfacePath.Pci.Controller;
        if ((MemCmp ("ATAPI", Drive->Parameters.InterfaceType, 5) == 0) ||
            (MemCmp ("ATA",   Drive->Parameters.InterfaceType, 3) == 0)) {
        // ATA or ATAPI drive found
            Node.Atapi.Header.Type = MESSAGING_DEVICE_PATH;
            Node.Atapi.Header.SubType = MSG_ATAPI_DP;
            SET_NODE_LENGTH(&Node.Atapi.Header,sizeof(ATAPI_DEVICE_PATH));
            Node.Atapi.SlaveMaster = Drive->Parameters.DevicePath.Atapi.Master;
            Node.Atapi.Lun = Drive->Parameters.DevicePath.Atapi.Lun;
            Node.Atapi.PrimarySecondary = (UINT8)Controller;
        } else {
            // Not an ATA/ATAPI drive
            if (Controller != 0) {
                Node.Controller.Header.Type = HARDWARE_DEVICE_PATH;
                Node.Controller.Header.SubType = HW_CONTROLLER_DP;
                SET_NODE_LENGTH(&Node.Controller.Header,sizeof(CONTROLLER_DEVICE_PATH));
                Node.Controller.Controller = Controller;
                *DevicePath = DPAddNode (BaseDevicePath, &Node.DevPath);
                Node.DevPath.Type = 0;
            }
            // Since it's not ATA/ATAPI, find out what kind it is
            if (MemCmp("SCSI", Drive->Parameters.InterfaceType, 4) == 0 ) {
                // SCSI drive
                Node.Scsi.Header.Type = MESSAGING_DEVICE_PATH;
                Node.Scsi.Header.SubType = MSG_SCSI_DP;
                SET_NODE_LENGTH(&Node.Scsi.Header,sizeof(SCSI_DEVICE_PATH));
                Node.Scsi.Lun = (UINT16)Drive->Parameters.DevicePath.Scsi.Lun;
                Node.Scsi.Pun = Drive->Parameters.DevicePath.Scsi.TargetId;
            } else if (MemCmp("USB", Drive->Parameters.InterfaceType, 3) == 0 ) {
                // USB drive
                Node.Usb.Header.Type = MESSAGING_DEVICE_PATH;
                Node.Usb.Header.SubType = MSG_USB_DP;
                SET_NODE_LENGTH(&Node.Usb.Header,sizeof(USB_DEVICE_PATH));
                Node.Usb.ParentPortNumber = (UINT8)Drive->Parameters.DevicePath.Usb.Reserved;
            } else if (MemCmp("1394", Drive->Parameters.InterfaceType, 4) == 0 ) {
                // 1394 drive
                Node.F1394.Header.Type = MESSAGING_DEVICE_PATH;
                Node.F1394.Header.SubType = MSG_1394_DP;
                SET_NODE_LENGTH(&Node.F1394.Header,sizeof(F1394_DEVICE_PATH));
                Node.F1394.Guid = Drive->Parameters.DevicePath.FireWire.Guid;
            } else if (MemCmp("FIBRE", Drive->Parameters.InterfaceType, 5) == 0 ) {
                // Fibre Channel drive
                Node.FibreChannel.Header.Type = MESSAGING_DEVICE_PATH;
                Node.FibreChannel.Header.SubType = MSG_FIBRECHANNEL_DP;
                SET_NODE_LENGTH(&Node.FibreChannel.Header,sizeof(FIBRECHANNEL_DEVICE_PATH));
                Node.FibreChannel.WWN = Drive->Parameters.DevicePath.FibreChannel.Wwn;
                Node.FibreChannel.Lun = Drive->Parameters.DevicePath.FibreChannel.Lun;
            }
        }
    }
    // If Device Path Type is still zero, it means this is either EDD 1.1 device
    // or unreconized EDD 3.0 device. Add vendor HW device node for such devices
    if (Node.DevPath.Type == 0) {
        Node.UnknownVendor.DevicePath.Header.Type = HARDWARE_DEVICE_PATH;
        Node.UnknownVendor.DevicePath.Header.SubType = HW_VENDOR_DP;
        SET_NODE_LENGTH(&Node.UnknownVendor.DevicePath.Header,sizeof(UNKNOWN_DEVICE_VENDOR_DEVICE_PATH));
        Node.UnknownVendor.DevicePath.Guid = UnknownDevGuid;
        Node.UnknownVendor.LegacyDriveLetter = Drive->Number;
    }
    *DevicePath = DPAddNode (BaseDevicePath, &Node.DevPath);
}

// Align address on boundary of UINTN for this compiler
UINTN AlignAddress (UINTN Address)
{
    if((UINTN)Address % sizeof(UINTN)) {
        return sizeof(UINTN) - ((UINTN)Address % sizeof(UINTN));
    } else {
        return 0;
    }
}

/**
    Callback notification on legacy boot return. This function adjusts the INT13 handles
    that might have been changed during legacy boot.

    @note  
  Control flow:
    - locate CSM_BLOCK_IO_DEV device
    - look in IPLDT for this device using BCV Segment/Offset
    - get the handle index from IPLDT ipld_table_entry.VectorIndex
    - get the handle from dimVectorMap[32 max]
    - updates BlockIoDev->Drive->Number with the new handle

**/

#define EFI_CSM_BLOCKIO_MAX_IPLDT_ENTRIES 32

VOID
CsmBlockIoComebackFromLegacyBoot(
    EFI_EVENT Event,
    VOID      *Context
)
{
    CSM_BLOCK_IO_DEV *Device = Context;
    UINT16  EbdaSeg = *(UINT16*)0x40e;
    UINT8   *Ebda = (UINT8*)((UINTN)EbdaSeg<<4);
    UINT8   i;
    UINT8   *Int13Handles = Ebda + 0x3e0;
    UINT8   *Ipldt = Ebda + 0x440;
    UINT8   VectorIndex;
    UINT8   Handle;
    
    TRACE((TRACE_ALWAYS, "CsmBlockIo L2E: BCV at %x:%x\n", Device->BcvSegment, Device->BcvOffset));
    for (i = 0; i < EFI_CSM_BLOCKIO_MAX_IPLDT_ENTRIES; i++)
    {
        if (*((UINT16*)(Ipldt+0xe)) == Device->BcvOffset &&
                (*((UINT16*)(Ipldt + 0x10)) == Device->BcvSegment)) break;
        Ipldt += 0x40;
    }
    if (i == EFI_CSM_BLOCKIO_MAX_IPLDT_ENTRIES)
    {
        TRACE((TRACE_ALWAYS, "Entry is not found in IPLDT\n"));
        return;
    }
    
    VectorIndex = Ipldt[2];
    Handle = Int13Handles[VectorIndex];
    
    TRACE((TRACE_ALWAYS, "IPLDT[%x], index %x, handle %x\n", i, VectorIndex, Handle));
    ASSERT(Handle > 0x7f);
    
    Device->Drive.Number = Handle;
}


//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**           5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093      **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
