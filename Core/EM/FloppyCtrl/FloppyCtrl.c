//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
//**********************************************************************
// $Header: /Alaska/SOURCE/Core/CORE_DXE/FloppyCtrl/FloppyCtrl.c 47    11/03/11 6:13a Rajeshms $
//
// $Revision: 47 $
//
// $Date: 11/03/11 6:13a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Core/CORE_DXE/FloppyCtrl/FloppyCtrl.c $
// 
// 47    11/03/11 6:13a Rajeshms
// [TAG]  		EIP73253
// [Category]  	Improvement
// [Description]  	Floppy Driver Follow the UEFI Driver Model as per the
// UEFI Spec.
// [Files]  		FloppyCtrl.c
// 
// 46    10/27/09 12:24p Pats
// EIP21981: enable RAID module hangs on checkpoint 99
// Solution: Small delay in DMAChInit()
// 
// 45    8/28/09 10:29a Felixp
// Component Name protocol implementation is upadted  to support both 
// ComponentName and ComponentName2 protocols
// (based on value of the EFI_SPECIFICATION_VERSION SDL token).
// 
// 44    7/02/09 12:40p Yul
// Syns to coding standards
//
// 43    7/02/09 10:14a Yul
// Update Header and Tailer and syns with coding standards
//
// 42    6/24/09 11:12a Yul
// Fix for the EIP 14848 AMIDIAG issue.
// Instead of reading flag directly, check drive status and update the
// flag.
//
// 41    4/13/07 1:37p Ambikas
// Coding standards changes: added a couple of AMI_PHDRs; moved mPpiList
// before FDCPeimEntryPoint declaration.
//
// 40    4/13/07 12:02p Ambikas
//
// 39    4/13/07 11:57a Ambikas
// Coding standard changes: updated year in AMI copyright header and
// footer; removed commented out function GetFloppyModel.
//
// 38    4/10/07 10:01a Felixp
// LookupHID routine renamed to LookupFloppyHid to avoid linking issue
// when linking with PS2CTRL module
//
// 37    3/29/07 2:53p Yakovlevs
// Excluded GetFloppy_DP from PEI build path
//
// 36    3/29/07 2:09p Yakovlevs
// Replaced Device Path manipulation with Lib function call.
//
// 35    1/19/07 1:04p Yakovlevs
// Fixes for Legacy Free system EIP issue 8888
//
// 34    10/04/06 12:24p Markw
// Add x64 support.
//
// 33    6/04/06 10:43p Ambikas
//
// 32    5/23/06 4:12a Felixp
// Bug fix: missing CloseProtocol calls added
//
// 31    5/20/06 9:30p Felixp
// minor bug fix: parameter was missing in ASSERT_PEI_ERROR
//
// 30    5/19/06 10:33p Felixp
// Device Path code updated to use NEXT_NODE/NODE_LENGTH macros to remove
// direct access to the Length field
//
// 29    5/05/06 5:21p Ambikas
//
// 28    4/03/06 3:55p Felixp
// Converted to support new Super I/O infrastructure
//
// 27    3/13/06 2:22a Felixp
//
// 26    12/21/05 11:42a Ambikas
// BIOS Recovery using floppy didn't work. The Fix:
// -Added function CheckMRQBit_NoDelay.
// -FddReadWriteFn: After initializing DMA registers and sending command
// packet, we wait for the result packet. Instead of calling CheckMRQBit,
// we call CheckMRQBit_NoDelay. Comment in that spot explains the reason
// why.
//
// 25    12/20/05 10:50p Ambikas
// Edited Revision History header part 24.
//
// 24    12/20/05 10:47p Ambikas
// Minor changes:
// -Added gPeiStall. Delay(): no longer use Locate Ppi every time for Stall Ppi.
// -Got rid of unused bit defs for FloppyInterface->FdcFlag and consolidated remaining bit defs with bit defs for global var FdcFlag.
// Eliminated FdcFlag. Added global var gPeiToDxeFloppyDrive0Status, which will pass state of floppy at end of pei to dxe, as FdcFlag  did.
// Replaced constants (e.g. BIT00) with names.
// -UINT8 MediaType replaced with FLOPPY_DISK_FORMAT FloppyDiskFormat. -Added InitFloppyBlockIOLastBlockAndMaxSectors().
// -FddReadWriteFn: For command packet, only check MRQ bit; don't check DIO bit. Got rid of other unnnessary checking of DIO/MRQ bits. Changed error message.
// -DmaInitTable: got rid of lines writing nonexistent registers 9 and 0xd2. (This is Ich7).
// -DmaInitForFloppy: write the clear byte register (DMA1_RESET_REG) before writing the count value.
// -SetDataRate: Configuration Control Register is 0x3f7, not 0x3f4.
//
// 23    11/23/05 11:30a Felixp
// When floppy driver is not connected, stop SIO driver
//
// 21    9/30/05 4:03p Felixp
// VC7.1 warnings removed
//
// 20    9/28/05 12:00p Felixp
// bug fix in UpdateIOST
//
// 19    8/22/05 5:32p Felixp
// Disable Floppy when controller is not detected
// (update vIOST variable)
//
// 18    8/10/05 1:06p Mandal
// FDCReset function - Considering the return status of FloopyDriveInit
// function.
//
// 17    5/14/05 5:13p Eswark
//
// 16    5/14/05 5:07p Eswark
// MotorOff function included in FdcReset Function.
//
// 15    7/18/05 3:51p Felixp
//
// 14    4/01/05 4:13p Eswark
//
// 13    4/01/05 11:54a Eswark
// Interface structure is getting the proper media change value from
// "CheckMediaChange" function.
//
// 12    3/25/05 6:39p Felixp
//
// 11    3/25/05 6:09p Eswark
// Moved code from "FDCPeimEntryPoint" to "GetBlockDeviceMediaInfo".
//
// 9     3/25/05 8:27a Felixp
//
// 8     3/25/05 7:58a Felixp
//
// 7     3/24/05 6:28p Felixp
//
// 6     3/24/05 11:51a Eswark
// Added Floppy  peim code based on recovery specifixcation.
//
// 4     3/22/05 4:47p Eswark
// Added pei support.
//
// 3     3/04/05 11:28a Mandal
//
// 2     2/07/05 4:03p Yakovlevs
//
// 1     2/01/05 1:12a Felixp
//
// 7     2/01/05 12:30a Felixp
//
// 6     1/22/05 12:41p Felixp
// Bug fix:
// Last parameter to AllocatePages was UINT8* instead of
// EFI_PHYSICAL_ADDRESS*, which
// resulted in a stack corruption.
//
// 5     1/18/05 3:22p Felixp
// PrintDebugMessage renamed to Trace
//
// 4     1/04/05 11:20a Felixp
//
// 1     12/22/04 6:19p Admin
//
// 1     12/22/04 6:18p Admin
//
// 8     12/17/04 7:38p Olegi
//
// 7     12/17/04 6:59p Felixp
// DEBUG_MSG renamed to TRACE
//
// 6     12/17/04 9:39a Olegi
//
// 5     12/16/04 10:38a Eswark
// Added header for the floppy driver.
//**********************************************************************


//**********************************************************************
//<AMI_FHDR_START>
//
// Name: FloppyCtrl.c - Floppy Controller DXE driver
//
// Description:
//  This driver initializes floppy controller and produces block IO protocol
//  for floppy read and write access.
//
//<AMI_FHDR_END>
//**********************************************************************

//======================================================================
// Module specific Includes
#include "FloppyCtrl.h"
#include <Protocol/PCIIO.h>

//======================================================================
// GUID Definitions
static EFI_GUID                    gEfiBlockIoProtocolGuid    = EFI_BLOCK_IO_PROTOCOL_GUID;
static EFI_GUID                    gEfiAmiSioProtocolGuid     = EFI_AMI_SIO_PROTOCOL_GUID;
static EFI_GUID                    gDriverBindingProtocolGuid = EFI_DRIVER_BINDING_PROTOCOL_GUID;
static EFI_GUID                    gDevicePathProtocolGuid    = EFI_DEVICE_PATH_PROTOCOL_GUID;
static EFI_GUID                    gEfiPeiStallPpiGuid        = EFI_PEI_STALL_PPI_GUID;
#ifndef EFI_COMPONENT_NAME2_PROTOCOL_GUID //old Core
static EFI_GUID                    gComponentNameProtocolGuid = EFI_COMPONENT_NAME_PROTOCOL_GUID;
#else
static EFI_GUID                    gComponentNameProtocolGuid = EFI_COMPONENT_NAME2_PROTOCOL_GUID;
#endif
static EFI_GUID                    gPciIoProtocolGuid         = EFI_PCI_IO_PROTOCOL_GUID;

extern EFI_COMPONENT_NAME_PROTOCOL gFloppyCtlDriverName;

static EFI_SYSTEM_TABLE            *gSysTable    = NULL;
static EFI_PEI_SERVICES            **PeiServices = NULL;

EFI_PEI_STALL_PPI                  *gPeiStall = NULL;

// gPeiToDxeFloppyDrive0Status:
//	The last thing Pei Recovery function GetBlockDeviceMediaInfo does is to
//  set gPeiToDxeFloppyDrive0Status to the current value of
//  FloppyInterface->FdcFlag
//	The dxe entry point FloppyCtrlStart copies gPeiToDxeFloppyDrive0Status
//  to its FloppyInterface->FdcFlag for floppy drive 0.
//	This way, FloppyCtrlStart can check if floppy drive0 has been initialized
//  in pei and if so, can bypass initialization in dxe.
//
UINT8   gPeiToDxeFloppyDrive0Status = FDC_FLAG_NOT_INTIALIZED;

// PEIM specific code start
static EFI_GUID guidBlockIo = EFI_PEI_VIRTUAL_BLOCK_IO_PPI;

// PPI that are installed
static EFI_PEI_PPI_DESCRIPTOR mPpiList[] = {
    EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
    &guidBlockIo,
    NULL
}; //initialized by the entry point

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:	FDCPeimEntryPoint
//
// Description:
//  This is the entry point of PEIM FDC
//
// Input:
//  IN EFI_FFS_FILE_HEADER       *FfsHeader,
//  IN EFI_PEI_SERVICES          **PeiServices
//
// Output:
//	EFI_STATUS
//
// Modified:
//
// Referrals: InitAmiLib InstallMultipleProtocolInterfaces
//
// Notes:
//  Here is the control flow of this function:
//  1. Initialize Ami Lib.
//	2. Install Driver Binding Protocol
//  3. Return EFI_SUCCESS.
//
//<AMI_PHDR_END>
//**********************************************************************

#ifdef PEI_FLOPPY_CTRL
EFI_STATUS FDCPeimEntryPoint(
    IN EFI_FFS_FILE_HEADER *FfsHeader,
    IN EFI_PEI_SERVICES    **pPeiServices )
{
    EFI_STATUS           Status = EFI_SUCCESS;
    FLOPPY_CTRL_PROTOCOL *FloppyInterface;

    PeiServices = pPeiServices;

    //Allocate Storage for FLOPPY_CTRL_PROTOCOL;
    Status = (**PeiServices).AllocatePool( PeiServices, \
    sizeof(FLOPPY_CTRL_PROTOCOL), (VOID**)&FloppyInterface );
    ASSERT_PEI_ERROR( PeiServices, Status );
    //Clear data
    MemSet((void*)FloppyInterface, sizeof(FLOPPY_CTRL_PROTOCOL), 0 );

    FloppyInterface->PeimRecBlk.GetNumberOfBlockDevices
        = GetNumberOfBlockDevices;
    FloppyInterface->PeimRecBlk.GetBlockDeviceMediaInfo
        = GetBlockDeviceMediaInfo;
    FloppyInterface->PeimRecBlk.ReadBlocks = PeimReadBlocks;

    mPpiList[0].Ppi = &FloppyInterface->PeimRecBlk;
    Status          = (*PeiServices)->InstallPpi( PeiServices, &mPpiList[0] );
    ASSERT_PEI_ERROR( PeiServices, Status );

    Status = (*PeiServices)->LocatePpi( PeiServices, &gEfiPeiStallPpiGuid, \
                                        0, NULL, &gPeiStall );
    ASSERT_PEI_ERROR( PeiServices, Status );

    return Status;
}

#endif

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:	GetNumberOfBlockDevices
//
// Description:
//  This is the function to get the number of Block Devices
//
// Input:
//  IN EFI_PEI_SERVICES                       **PeiServices,
//  IN EFI_PEI_RECOVERY_BLOCK_IO_PPI          *This
//
// Output:
//	OUT UINTN   *NumberBlockDevices
//	EFI_STATUS
//
//<AMI_PHDR_END>
//**********************************************************************

EFI_STATUS GetNumberOfBlockDevices(
    IN EFI_PEI_SERVICES              **PeiServices,
    IN EFI_PEI_RECOVERY_BLOCK_IO_PPI *This,
    OUT UINTN                        *NumberBlockDevices   )
{
    *NumberBlockDevices = 01;
    return EFI_SUCCESS;
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:	GetBlockDeviceMediaInfo
//
// Description:
//  This is the function to get the Media information of Block Devices
//
// Input:
//  IN EFI_PEI_SERVICES     **PeiServices,
//  IN EFI_PEI_RECOVERY_BLOCK_IO_PPI    *This,
//  IN UINTN    DeviceIndex
//
// Output:
//	OUT EFI_PEI_BLOCK_IO_MEDIA *MediaInfo
//	EFI_STATUS
//
//<AMI_PHDR_END>
//**********************************************************************

EFI_STATUS GetBlockDeviceMediaInfo(
    IN EFI_PEI_SERVICES              **PeiServices,
    IN EFI_PEI_RECOVERY_BLOCK_IO_PPI *This,
    IN UINTN                         DeviceIndex,
    OUT EFI_PEI_BLOCK_IO_MEDIA       *MediaInfo )
{
    FLOPPY_CTRL_PROTOCOL *FloppyInterface   \
        = OUTTER( This, PeimRecBlk, FLOPPY_CTRL_PROTOCOL );
    EFI_STATUS           Status = EFI_SUCCESS;

    if ( FloppyInterface->FdcFlag & FDC_FLAG_DRIVE_INIT_ERROR ) {
        Status = EFI_DEVICE_ERROR;
    }
    else if ((FloppyInterface->FdcFlag & FDC_FLAG_DRIVE_INIT_SUCCESS)    \
             || (FloppyInterface->FdcFlag == FDC_FLAG_NOT_INTIALIZED))
    {
        FloppyInterface->BlkIo.Media      = &(FloppyInterface->BlkIoMedia);
        MediaInfo->DeviceType             = LegacyFloppy;     // Legacy Floppy
        MediaInfo->BlockSize              = 512;      // SECTOR_SIZE
        FloppyInterface->DriveNum         = 00;
        FloppyInterface->BaseAddr         = 0x3F0;
        FloppyInterface->FloppyDiskFormat = HighDensity1_44Mb;

        InitFloppyBlockIOLastBlockAndMaxSectors( FloppyInterface );

        // Initilize DMA channels
        if ( FloppyInterface->FdcFlag == FDC_FLAG_NOT_INTIALIZED ) {
            DMAChInit( );
        }

        // Initilize floppy controller
        Status = FloppyDriveInit( FloppyInterface );

        MediaInfo->MediaPresent = FloppyInterface->BlkIoMedia.MediaPresent;

        if ( !(EFI_ERROR( Status ))) {
            FloppyInterface->FdcFlag              = FDC_FLAG_DRIVE_INIT_SUCCESS;
            FloppyInterface->BlkIoMedia.BlockSize = 512;

            // FloppyInterface->DMABuffer:
            //	We don't allocate a buffer because we can't get memory at
            //  an address which meets the DMA requirement of being 24 bits
            //  or less in length. Instead, we set the DMA buffer
            //	to address 0x0 as nothing is there currently.

            FloppyInterface->DMABuffer = 0;
        }
        else {
            FloppyInterface->TimerFlag = 01;
            MotorOff( FloppyInterface->Event, FloppyInterface );
            FloppyInterface->FdcFlag |= FDC_FLAG_DRIVE_INIT_ERROR;
        }
    }

    gPeiToDxeFloppyDrive0Status = FloppyInterface->FdcFlag;
    return Status;
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:	PeimReadBlocks
//
// Description:
//  This is the function to Read Blocks in PEIM
//
// Input:
//  IN EFI_PEI_SERVICES     **PeiServices,
//  IN EFI_PEI_RECOVERY_BLOCK_IO_PPI    *This,
//	IN UINTN DeviceIndex,
//  IN EFI_PEI_LBA StartLBA,
//	IN UINTN BufferSize
//
// Output:
//	OUT VOID *Buffer
//	EFI_STATUS
//
//<AMI_PHDR_END>
//**********************************************************************

EFI_STATUS PeimReadBlocks(
    IN EFI_PEI_SERVICES              **PeiServices,
    IN EFI_PEI_RECOVERY_BLOCK_IO_PPI *This,
    IN UINTN                         DeviceIndex,
    IN EFI_PEI_LBA                   StartLBA,
    IN UINTN                         BufferSize,
    OUT VOID                         *Buffer )
{
    FLOPPY_CTRL_PROTOCOL *pFloppyInterface = OUTTER( This, PeimRecBlk, \
                                                     FLOPPY_CTRL_PROTOCOL );

    return FdcBlkRead((EFI_BLOCK_IO_PROTOCOL*)pFloppyInterface, \
                      (UINT32)DeviceIndex, StartLBA, BufferSize, Buffer );
}

// PEIM specific code end
//==================================================================================

//==================================================================================
// Function Prototypes for Driver Binding Protocol Interface
//==================================================================================
#ifdef DXE_FLOPPY_CTRL

EFI_STATUS
EFIAPI FloppyCtrlSupported (
    IN EFI_DRIVER_BINDING_PROTOCOL *This,
    IN EFI_HANDLE                  ControllerHandle,
    IN EFI_DEVICE_PATH_PROTOCOL    *RemainingDevicePath );

EFI_STATUS
EFIAPI FloppyCtrlStart (
    IN EFI_DRIVER_BINDING_PROTOCOL *This,
    IN EFI_HANDLE                  ControllerHandle,
    IN EFI_DEVICE_PATH_PROTOCOL    *RemainingDevicePath );

EFI_STATUS
EFIAPI FloppyCtrlStop (
    IN EFI_DRIVER_BINDING_PROTOCOL *This,
    IN EFI_HANDLE                  ControllerHandle,
    IN UINTN                       NumberOfChildren,
    IN EFI_HANDLE                  *ChildHandleBuffer );

//==================================================================================
// Driver binding protocol instance for Floppy Controller Driver
//==================================================================================
EFI_DRIVER_BINDING_PROTOCOL gFloppyCtrlDriverBindingProtocol = {
    FloppyCtrlSupported,
    FloppyCtrlStart,
    FloppyCtrlStop,
    0x10,
    NULL,
    NULL
};
#endif

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:	IsPei
//
// Description:
//  This is the function to check whether in PEI phase
//
// Input:
//  IN VOID **PeiServices,
//  IN VOID *FfsHeader
//
// Output:
//	OUT BOOLEAN
//
//<AMI_PHDR_END>
//**********************************************************************
BOOLEAN IsPei(
    VOID    *FfsHeader,
    IN VOID *PeiServices )
{
    if ( !FfsHeader ) {
        return TRUE;
    }

    if (   FfsHeader <= (VOID*)IsPei
           || ((EFI_FFS_FILE_HEADER*)FfsHeader)->Type != \
           EFI_FV_FILETYPE_COMBINED_PEIM_DRIVER
           ) {
        return FALSE;
    }

    if ( *(UINT64*)PeiServices == EFI_SYSTEM_TABLE_SIGNATURE ) {
        return FALSE;
    }
    return TRUE;
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:	FloppyCtrlEntryPoint
//
// Description:	Installs gIdeBusDriverBinding protocol
//
// Input:
//	IN EFI_HANDLE        ImageHandle,
//	IN EFI_SYSTEM_TABLE  *SystemTable
//
// Output:
//	EFI_STATUS
//
// Modified:
//
// Referrals: InitAmiLib InstallMultipleProtocolInterfaces
//
// Notes:
//  Here is the control flow of this function:
//  1. Initialize Ami Lib.
//	2. Install Driver Binding Protocol
//  3. Return EFI_SUCCESS.
//
//<AMI_PHDR_END>
//**********************************************************************

EFI_STATUS FloppyCtrlEntryPoint(
    IN EFI_HANDLE       ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable )
{
    EFI_STATUS Status = EFI_SUCCESS;

    #ifdef PEI_FLOPPY_CTRL

    if ( IsPei( ImageHandle, SystemTable )) {
        return FDCPeimEntryPoint((VOID*)ImageHandle, (VOID*)SystemTable );
    }
    #endif

    #ifdef DXE_FLOPPY_CTRL
    InitAmiLib( ImageHandle, SystemTable );

    // Initialize global variable for use in this driver
    gSysTable = SystemTable;

    // initiaize the ImageHandle and DriverBindingHandle
    gFloppyCtrlDriverBindingProtocol.DriverBindingHandle = NULL;
    gFloppyCtrlDriverBindingProtocol.ImageHandle         = ImageHandle;

    Status = pBS->InstallMultipleProtocolInterfaces(
        &gFloppyCtrlDriverBindingProtocol.DriverBindingHandle,
        &gDriverBindingProtocolGuid,
        &gFloppyCtrlDriverBindingProtocol,
        &gComponentNameProtocolGuid, &gFloppyCtlDriverName,
        NULL );
    #endif
    return Status;
}

#ifdef DXE_FLOPPY_CTRL
//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:	FloppyCtrlSupported
//
// Description:	Floppy Controller Driver Supported function
//				This function is a part of DriverBinfing protocol
//
// Input:
//	IN EFI_DRIVER_BINDING_PROTOCOL    *This,
//	IN EFI_HANDLE                     ControllerHandle,
//	IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
//
// Output:
//	EFI_STATUS
//
//<AMI_PHDR_END>
//**********************************************************************

EFI_STATUS
EFIAPI FloppyCtrlSupported(
    IN EFI_DRIVER_BINDING_PROTOCOL *This,
    IN EFI_HANDLE                  ControllerHandle,
    IN EFI_DEVICE_PATH_PROTOCOL    *RemainingDevicePath )
{
    ACPI_HID_DEVICE_PATH * acpiDP;
    EFI_STATUS             Status;

    if ( !EFI_ERROR( Status = GetFloppy_DP( This, ControllerHandle, \
                                   &acpiDP, EFI_OPEN_PROTOCOL_BY_DRIVER, TRUE ))
         && LookupFloppyHid( acpiDP->HID, acpiDP->UID )) {
        return EFI_SUCCESS;
    }

    return Status;
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:	FloppyCtrlStart
//
// Description:	Floppy Controller Driver Start function
//				This function initializes floppy controller and installs
//				Floppy BlkIO protocol.
//
// Input:
//	IN EFI_DRIVER_BINDING_PROTOCOL    *This,
//	IN EFI_HANDLE                     ControllerHandle,
//	IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
//
// Output:
//	EFI_STATUS
//
//<AMI_PHDR_END>
//**********************************************************************

EFI_STATUS
EFIAPI FloppyCtrlStart(
    IN EFI_DRIVER_BINDING_PROTOCOL *This,
    IN EFI_HANDLE                  ControllerHandle,
    IN EFI_DEVICE_PATH_PROTOCOL    *RemainingDevicePath )
{
    EFI_STATUS               Status;
    UINT16                   BaseAddr = 0;
    ACPI_HID_DEVICE_PATH     *acpiDP;
    FLOPPY_CTRL_PROTOCOL     *FloppyInterface;
    AMI_SIO_PROTOCOL         *AmiSio;
    T_ITEM_LIST              *ResList;
    UINT16                   FdcBase = 0;
    UINT8                    FdcDma  = 0;
    UINTN                    i;
    ASLRF_S_HDR              *hdr;
    EFI_DEVICE_PATH_PROTOCOL *FloppyDevPath;
    EFI_PHYSICAL_ADDRESS     Address;

    if ( !EFI_ERROR( GetFloppy_DP( This, ControllerHandle, &acpiDP, \
                                   EFI_OPEN_PROTOCOL_BY_DRIVER, TRUE ))
         && LookupFloppyHid( acpiDP->HID, acpiDP->UID ))
    {
        if ( acpiDP->UID == 00 )
        {
            if ( gPeiToDxeFloppyDrive0Status & FDC_FLAG_DRIVE_INIT_SUCCESS ) {
                return EFI_SUCCESS;
            }

            if ( gPeiToDxeFloppyDrive0Status & FDC_FLAG_DRIVE_INIT_ERROR ) {
                return EFI_DEVICE_ERROR;
            }
        }

        Status = pBS->OpenProtocol( ControllerHandle,
                                    &gEfiAmiSioProtocolGuid,
                                    (VOID**)&AmiSio,
                                    This->DriverBindingHandle,
                                    ControllerHandle,
                                    EFI_OPEN_PROTOCOL_BY_DRIVER );

        if ( !(EFI_ERROR( Status )))
        {
            Status = AmiSio->CurrentRes( AmiSio, 00, &ResList );

            if ( ResList != NULL )
            {
                //FDC uses 8 io ports but ports 3F6 or 376 are reserved
                //in FDC and been used by Legacy IDE mode to avoid resource
                //collision ASL code has 2 IO resource descriptors there
                //
                BOOLEAN ioset = FALSE;

                //----------------
                for ( i = 0; i < ResList->ItemCount; i++ )
                {
                    // We need only DMA chnl and Base Addr
                    hdr = (ASLRF_S_HDR*)ResList->Items[i];

                    switch ( hdr->Name )
                    {
                    case ASLV_RT_FixedIO:

                        if ( !ioset ) {
                            FdcBase = ((ASLR_FixedIO*)hdr)->_BAS;
                            ioset   = TRUE;
                        }
                        break;
                    case ASLV_RT_DMA:
                        FdcDma = ((ASLR_DMA*)hdr)->_DMA;
                        break;
                    case ASLV_RT_IO:

                        if ( !ioset ) {
                            FdcBase = ((ASLR_IO*)hdr)->_MIN;
                            ioset   = TRUE;
                        }
                        break;
                    }
                }
                BaseAddr = FdcBase;
            }
            else {
                Status = EFI_DEVICE_ERROR;
                goto Error;
            }
        }
        else {
            return EFI_DEVICE_ERROR;
        }

        // added code for DMA controller reset
        //dma init only needs to be done once; so even if this is drive 1,
        // we can look at gPeiToDxeFloppyDrive0Status
        if ( gPeiToDxeFloppyDrive0Status == FDC_FLAG_NOT_INTIALIZED ) {
            DMAChInit( );
        }

        // Allocate memory for FLOPPY_CTRL_PROTOCOL
        FloppyInterface = MallocZ( sizeof(FLOPPY_CTRL_PROTOCOL));

        if ( !FloppyInterface ) {
            Status = EFI_OUT_OF_RESOURCES;
            goto Error;
        }

        FloppyInterface->DriveNum = acpiDP->UID;

        if ( BaseAddr == 00 )
        {
            if ( FloppyInterface->DriveNum == 00 ) {
                BaseAddr = 0x3F0;
            }
            else if ( FloppyInterface->DriveNum == 01 )
            {
                BaseAddr = 0x3f0;
            }
            else {
                Status = EFI_UNSUPPORTED;
                goto Error;
            }
        }
        FloppyInterface->BaseAddr         = BaseAddr;
        FloppyInterface->FloppyDiskFormat = HighDensity1_44Mb;

        if ( FloppyInterface->DriveNum == 0 ) {
            FloppyInterface->FdcFlag = gPeiToDxeFloppyDrive0Status;
        }
        else {
            FloppyInterface->FdcFlag = FDC_FLAG_NOT_INTIALIZED;
        }

        // Do Floppy drive initlization (includes controller reset also.)

        // Initilize floppy controller
        Status = FloppyDriveInit( FloppyInterface );

        if ( Status != EFI_DEVICE_ERROR )
        {
            InitFloppyBlockIO( FloppyInterface );
            Address = DMA_MAX_ADDR_LIMIT;
            // Allocate memory for DMA buffer
            Status = pBS->AllocatePages( AllocateMaxAddress, \
                                         EfiBootServicesData, NUM_PAGES, &Address );

            // adjust memory.
            if ( !EFI_ERROR( Status ))
            {
                FloppyInterface->DmaFlag = BIT00;

                if (((Address + FloppyInterface->MaxSectors * SECTOR_SIZE) \
                     & 0xff0000) != (Address & 0xff0000))
                {
                    pBS->FreePages( Address, (UINTN)NUM_PAGES );
                    Address = DMA_MAX_ADDR_LIMIT;
                    Status  = pBS->AllocatePages( AllocateMaxAddress, \
                                                  EfiBootServicesData, NUM_PAGES * 2, &Address );

                    if ( EFI_ERROR( Status )) {
                        Status = pBS->FreePages( Address, NUM_PAGES * 2 );
                    }
                    else {
                        FloppyInterface->DmaFlag |= BIT01;

                        if (((Address + FloppyInterface->MaxSectors   \
                              * SECTOR_SIZE) & 0xff0000) != (Address & 0xff0000)) {
                            Address = Address & 0xff0000;
                        }
                    }
                }
            }
            FloppyInterface->DMABuffer = (UINT8*)Address;
        }

        FloppyInterface->TimerFlag = 01;
        MotorOff( FloppyInterface->Event, FloppyInterface );

        if ( EFI_ERROR( Status ))
        {
            pBS->FreePool( FloppyInterface );
            FloppyInterface->FdcFlag |= FDC_FLAG_DRIVE_INIT_ERROR;
            TRACE((-1, "FDC :Floppy driver start function - Drive initialization error\n"));
            Status = pBS->HandleProtocol( ControllerHandle, \
                                          &gDevicePathProtocolGuid, &FloppyDevPath );

            if ( !EFI_ERROR( Status ))
            {
                //TODO: Intel DxeMain does not like this trick
                //Let's comments it out temporary
                //
                //EFI_HANDLE Handle;
                //Status=pBS->LocateDevicePath(&gPciIoProtocolGuid, &FloppyDevPath,&Handle);
                //if (!EFI_ERROR(Status)) pBS->DisconnectController(Handle,NULL,ControllerHandle);
            }
            Status =  EFI_DEVICE_ERROR;
            goto Error;
        }

        Status = pBS->CreateEvent(
            EVT_TIMER | EVT_NOTIFY_SIGNAL,
            TPL_NOTIFY,
            (EFI_EVENT_NOTIFY)MotorOff,
            (void*)FloppyInterface,
            &(FloppyInterface->Event));

        if ( EFI_ERROR( Status )) {
            goto Error;
        }

        //Status = pBS->OpenProtocol(ControllerHandle, &gDevicePathProtocolGuid,
        //						   (void **)&FloppyDevPath,
        //							This->DriverBindingHandle,
        //							ControllerHandle,
        //							EFI_OPEN_PROTOCOL_BY_DRIVER);

        //if(EFI_ERROR(Status)) return Status;

        // Install Block IO protocol for floppy controller
        Status = pBS->InstallMultipleProtocolInterfaces( &ControllerHandle,
                                                         &gEfiBlockIoProtocolGuid,
                                                         &(FloppyInterface->BlkIo),
                                                         NULL );

        if ( EFI_ERROR( Status ))
        {
            TRACE((-1, "FDC :Floppy driver start function - Out of Resources for Block IO protocol\n"));
            goto Error;
        }

        if ( gSysTable ) {
            pBS->SetTimer( FloppyInterface->Event, TimerRelative, 20000000 );
        }
        return EFI_SUCCESS;
    }
    Status = EFI_UNSUPPORTED;
    goto Error;

Error:
    pBS->CloseProtocol( ControllerHandle,
                        &gEfiAmiSioProtocolGuid,
                        This->DriverBindingHandle,
                        ControllerHandle );
    if( Status == EFI_OUT_OF_RESOURCES ) {
        return EFI_OUT_OF_RESOURCES;
    }
    return EFI_DEVICE_ERROR;
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:	FloppyCtrlStop
//
// Description: Floppy Controller Driver Stop function
//				This functiuon uninstalls Floppy BlkIO protocol and driver
//				binding protocol.
//
// Input:
//	IN EFI_DRIVER_BINDING_PROTOCOL    *This,
//	IN EFI_HANDLE                     ControllerHandle,
//	IN  UINTN                         NumberOfChildren,
//	IN  EFI_HANDLE                    *ChildHandleBuffer
//
// Output:
//	EFI_STATUS
//
//<AMI_PHDR_END>
//**********************************************************************

EFI_STATUS
EFIAPI FloppyCtrlStop(
    IN EFI_DRIVER_BINDING_PROTOCOL *This,
    IN EFI_HANDLE                  ControllerHandle,
    IN UINTN                       NumberOfChildren,
    IN EFI_HANDLE                  *ChildHandleBuffer )
{
    EFI_STATUS           Status;
    FLOPPY_CTRL_PROTOCOL *FloppyInterface;

    if(NumberOfChildren) {
        return EFI_DEVICE_ERROR;
    }

    Status = pBS->OpenProtocol( ControllerHandle,
                                &gEfiBlockIoProtocolGuid,
                                (VOID**)&FloppyInterface,
                                This->DriverBindingHandle,
                                ControllerHandle,
                                EFI_OPEN_PROTOCOL_GET_PROTOCOL );

    if ( EFI_ERROR( Status )) {
        return EFI_DEVICE_ERROR;
    }

    // uninstall block io protocol
    Status = pBS->UninstallMultipleProtocolInterfaces( &ControllerHandle,
                                                       &gEfiBlockIoProtocolGuid, &(FloppyInterface->BlkIo),
                                                       NULL );

    if ( EFI_ERROR( Status )) {
        return EFI_DEVICE_ERROR;
    }

    pBS->CloseProtocol( ControllerHandle,
                        &gEfiAmiSioProtocolGuid,
                        This->DriverBindingHandle,
                        ControllerHandle );
    pBS->CloseProtocol( ControllerHandle,&gDevicePathProtocolGuid,
    				    This->DriverBindingHandle,ControllerHandle);

    // deallocate DMA buffer
    if ( FloppyInterface->DmaFlag & BIT01 ) {
        pBS->FreePages((EFI_PHYSICAL_ADDRESS)( FloppyInterface->DMABuffer ), \
                       (UINTN)NUM_PAGES * 2 );
    }
    pBS->    FreePages((EFI_PHYSICAL_ADDRESS)( FloppyInterface->DMABuffer ), \
                       (UINTN)NUM_PAGES );

    // reset the status flag
    FloppyInterface->FdcFlag = FDC_FLAG_NOT_INTIALIZED;

    pBS->CloseEvent(FloppyInterface->Event);

    // Free memory pool used by floppy interface structure
    pBS->FreePool( FloppyInterface );

    // uninstall driver binding protocol
    //###DEBUGThis needs to be done in the Unload routine
    //Status = pBS->UninstallMultipleProtocolInterfaces(
    //			&gFloppyCtrlDriverBindingProtocol.DriverBindingHandle,
    //			&gDriverBindingProtocolGuid, &gFloppyCtrlDriverBindingProtocol,
    //			&gComponentNameProtocolGuid, &gFloppyCtlDriverName,
    //			NULL);
    //DEBUG END
    return EFI_SUCCESS;
}

#endif


//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:	FloppyDriveInit
//
// Description: This function initializes the floppy driver
//				Do FDC reset, turn on the motor and checks for media change
//
// Input:
//  IN  FLOPPY_CTRL_PROTOCOL    *FloppyInterface
//
// Output:
//	EFI_STATUS
//
//<AMI_PHDR_END>
//**********************************************************************

EFI_STATUS FloppyDriveInit(
    IN FLOPPY_CTRL_PROTOCOL *FloppyInterface )
{
    EFI_STATUS Status = EFI_SUCCESS;
    UINT16     BaseAddr;
    UINT16     DataReg;

    FloppyInterface->FdcFlag = FDC_FLAG_NOT_INTIALIZED;
    FloppyInterface->PrCyl   = 0x0F0;
    BaseAddr                 = FloppyInterface->BaseAddr;
    DataReg                  = FloppyInterface->BaseAddr + 05;

    CtrlReset( FloppyInterface );
    SetDataRate( FloppyInterface );

    if ( EFI_ERROR( MotorOn( FloppyInterface ))) {
        return EFI_DEVICE_ERROR;
    }

    if ( EFI_ERROR( Specify( FloppyInterface ))) {
        return EFI_DEVICE_ERROR;
    }

    FloppyInterface->BlkIoMedia.MediaPresent = TRUE;

    if ( CheckMediaChange( FloppyInterface ) == EFI_MEDIA_CHANGED ) {
        Status = EFI_MEDIA_CHANGED;
    }

    if ( EFI_ERROR( Calibrate( FloppyInterface )))
    {
        Delay( 10000 );

        if ( EFI_ERROR( Calibrate( FloppyInterface ))) {
            return EFI_DEVICE_ERROR;
        }
    }
    FloppyInterface->PrCyl = 00;

    if ( Status == EFI_MEDIA_CHANGED )
    {
        Status = EFI_SUCCESS;

        if ( EFI_ERROR( Seek( FloppyInterface, 00, 01 )))
        {
            Delay( 5000 );

            if ( EFI_ERROR( Seek( FloppyInterface, 00, 01 ))) {
                return EFI_DEVICE_ERROR;
            }
        }
        FloppyInterface->PrCyl = 01;

        if ( CheckMediaChange( FloppyInterface ) == EFI_MEDIA_CHANGED )
        {
            FloppyInterface->BlkIoMedia.MediaPresent = FALSE;
            Status = EFI_NO_MEDIA;
        }
    }

    FloppyInterface->FdcFlag |= FDC_FLAG_DRIVE_INIT_SUCCESS;

    return Status;
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:	InitFloppyBlockIO
//
// Description: Initilizes the data required for floppy block IO protocol
//
// Input:
//  IN  FLOPPY_CTRL_PROTOCOL    *FloppyInterface
//
// Output:
//	EFI_STATUS
//
// Refferals:	EFI 1.1 specification, Chapter 11.6.
//
//<AMI_PHDR_END>
//**********************************************************************

EFI_STATUS InitFloppyBlockIO(
    IN FLOPPY_CTRL_PROTOCOL *FloppyInterface )
{
    EFI_STATUS Status = EFI_SUCCESS;

    FloppyInterface->BlkIo.Revision    = 01;
    FloppyInterface->BlkIo.Reset       = FdcReset;
    FloppyInterface->BlkIo.ReadBlocks  = FdcBlkRead;
    FloppyInterface->BlkIo.WriteBlocks = FdcBlkWrite;
    FloppyInterface->BlkIo.FlushBlocks = FdcBlkFlush;

    FloppyInterface->BlkIo.Media                 = &(FloppyInterface->BlkIoMedia);
    FloppyInterface->BlkIoMedia.MediaId          = FloppyInterface->DriveNum;
    FloppyInterface->BlkIoMedia.RemovableMedia   = TRUE;
    FloppyInterface->BlkIoMedia.LogicalPartition = FALSE;
    FloppyInterface->BlkIoMedia.ReadOnly         = FALSE;
    FloppyInterface->BlkIoMedia.WriteCaching     = FALSE;
    FloppyInterface->BlkIoMedia.BlockSize        = 512;

    InitFloppyBlockIOLastBlockAndMaxSectors( FloppyInterface );

    FloppyInterface->BlkIoMedia.IoAlign = 0;
    return Status;
}

VOID InitFloppyBlockIOLastBlockAndMaxSectors(
    FLOPPY_CTRL_PROTOCOL *FloppyInterface )
{
    // parameters change based on floppy type
    // LastBlock = 2 heads * MaxSectors * NumTracks - 1
    // corresponding to 720KB drive
    if ( FloppyInterface->FloppyDiskFormat == DoubleDensity720Kb )
    {
        FloppyInterface->BlkIoMedia.LastBlock = 1339;     //(2*9*80-1)
        FloppyInterface->MaxSectors           = 0x09;
    }
    // corresponding to 1.44 MB drive
    else if ( FloppyInterface->FloppyDiskFormat == HighDensity1_44Mb )
    {
        FloppyInterface->BlkIoMedia.LastBlock = 2779;     //(2 * 18 * 80 -1)
        FloppyInterface->MaxSectors           = 18;
    }
    // corresponding to 2.88 MB drive
    else {
        FloppyInterface->BlkIoMedia.LastBlock = 5759;     //(2 * 36 * 80 -1)
        FloppyInterface->MaxSectors           = 36;
    }
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:	FdcReset
//
// Description: FDC reset function.
//
// Input:
//      IN EFI_BLOCK_IO_PROTOCOL *This,
//		IN BOOLEAN ExtendedVerification
//
// Output:
//	EFI_STATUS
//
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS FdcReset(
    IN EFI_BLOCK_IO_PROTOCOL *This,
    IN BOOLEAN               ExtendedVerification )
{
    #ifdef DXE_FLOPPY_CTRL
    FLOPPY_CTRL_PROTOCOL *FloppyInterface = (FLOPPY_CTRL_PROTOCOL*)This;
    BOOLEAN              ErrorFlag        = TRUE;

    if ( EFI_ERROR( FloppyDriveInit((FLOPPY_CTRL_PROTOCOL*)This )) == \
         EFI_DEVICE_ERROR ) {
        ErrorFlag = FALSE;
    }
    pBS->SetTimer(((FLOPPY_CTRL_PROTOCOL*)This)->Event, TimerRelative, \
                  20000000 );

    //	MotorOff(((FLOPPY_CTRL_PROTOCOL *)This)->Event, FloppyInterface);
    if ( ErrorFlag == FALSE ) {
        return EFI_DEVICE_ERROR;
    }
    return EFI_SUCCESS;
    #else
    return EFI_UNSUPPORTED;
    #endif
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:	FdcBlkRead
//
// Description: The ReadBlocks() function reads the requested number of
//				blocks from the device. All the blocks are read, or an
//				error is returned.
//
// Input:
//		IN EFI_BLOCK_IO_PROTOCOL *This,
//		IN UINT32 MediaId,
//		IN EFI_LBA LBA,
//		IN UINTN BufferSize,
//
// Output:
//  OUT VOID *Buffer
//  EFI_STATUS -
//	EFI_SUCCESS- The data was read correctly from the device.
//	EFI_DEVICE_ERROR- The device reported an error while attempting to
//		perform the read operation.
//	EFI_NO_MEDIA- There is no media in the device.
//	EFI_MEDIA_CHANGED- The MediaId is not for the current media.
//	EFI_BAD_BUFFER_SIZE- The BufferSize parameter is not a multiple
//		of the intrinsic block size of the device.
//	EFI_INVALID_PARAMETER- The read request contains LBAs that are not valid,
//		 or the buffer is not on proper alignment.
//
//<AMI_PHDR_END>
//**********************************************************************

EFI_STATUS FdcBlkRead(
    IN EFI_BLOCK_IO_PROTOCOL *This,
    IN UINT32                MediaId,
    IN EFI_LBA               LBA,
    IN UINTN                 BufferSize,
    OUT VOID                 *Buffer )
{
    UINT8      RWFlag = READ_OPERATION;
    EFI_STATUS Status;

    Status = FddReadWriteFn( This, MediaId, LBA, BufferSize, RWFlag, Buffer );

    if ( Status == EFI_DEVICE_ERROR )
    {
        if ( EFI_ERROR( FloppyDriveInit((FLOPPY_CTRL_PROTOCOL*)This ))) {
            Status = EFI_DEVICE_ERROR;
        }
        else {
            Status = FddReadWriteFn( This, MediaId, LBA, BufferSize, \
                                     RWFlag, Buffer );
        }
    }
    ((FLOPPY_CTRL_PROTOCOL*)This)->TimerFlag = 01;
    #ifdef DXE_FLOPPY_CTRL

    if ( gSysTable ) {
        pBS->SetTimer(((FLOPPY_CTRL_PROTOCOL*)This)->Event, TimerRelative, \
                      20000000 );
    }
    #endif

    return Status;
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:	FdcBlkWrite
//
// Description: The WriteBlocks() function reads the requested number of
//				blocks from the device. All the blocks are read, or an
//				error is returned.
// Input:
//		IN EFI_BLOCK_IO_PROTOCOL *This,
//		IN UINT32 MediaId,
//		IN EFI_LBA LBA,
//		IN UINTN BufferSize,
//
// Output:
//  OUT VOID *Buffer
//  EFI_STATUS -
//	EFI_SUCCESS- The data was read correctly from the device.
//	EFI_DEVICE_ERROR- The device reported an error while attempting to
//		perform the read operation.
//	EFI_NO_MEDIA- There is no media in the device.
//	EFI_MEDIA_CHANGED- The MediaId is not for the current media.
//	EFI_BAD_BUFFER_SIZE- The BufferSize parameter is not a multiple
//		of the intrinsic block size of the device.
//	EFI_INVALID_PARAMETER- The read request contains LBAs that are not valid,
//		 or the buffer is not on proper alignment.
//
//<AMI_PHDR_END>
//**********************************************************************

EFI_STATUS FdcBlkWrite(
    IN EFI_BLOCK_IO_PROTOCOL *This,
    IN UINT32                MediaId,
    IN EFI_LBA               LBA,
    IN UINTN                 BufferSize,
    OUT VOID                 *Buffer )
{
    UINT8      RWFlag = WRITE_OPERATION;
    EFI_STATUS Status;

    Status = FddReadWriteFn( This, MediaId, LBA, BufferSize, RWFlag, Buffer );

    if ( Status == EFI_DEVICE_ERROR )
    {
        if ( EFI_ERROR( FloppyDriveInit((FLOPPY_CTRL_PROTOCOL*)This ))) {
            Status = EFI_DEVICE_ERROR;
        }
        else {
            Status = FddReadWriteFn( This, MediaId, LBA, BufferSize, RWFlag, Buffer );
        }
    }
    ((FLOPPY_CTRL_PROTOCOL*)This)->TimerFlag = 01;
    #ifdef DXE_FLOPPY_CTRL

    if ( gSysTable ) {
        pBS->SetTimer(((FLOPPY_CTRL_PROTOCOL*)This)->Event, TimerRelative, \
                      20000000 );
    }
    #endif

    return Status;
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:	FdcBlkFlush
//
// Description: The FlushBlocks() function flushes all modified data to
//				the physical block device.
//
// Input:
//		IN EFI_BLOCK_IO_PROTOCOL *This,
//
// Output:
//  EFI_STATUS
//
//<AMI_PHDR_END>
//**********************************************************************

EFI_STATUS FdcBlkFlush(
    IN EFI_BLOCK_IO_PROTOCOL *This )
{
    return EFI_SUCCESS;
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:	FdcBlkWrite
//
// Description: The WriteBlocks() function reads the requested number of
//				blocks from the device. All the blocks are read, or an
//				error is returned.
// Input:
//		IN EFI_BLOCK_IO_PROTOCOL *This,
//		IN UINT32 MediaId,
//		IN EFI_LBA LBA,
//		IN UINTN BufferSize,
//		IN UINT8 RWFlag
//
// Output:
//  OUT VOID *Buffer
//  EFI_STATUS -
//	EFI_SUCCESS- The data was read correctly from the device.
//	EFI_DEVICE_ERROR- The device reported an error while attempting to
//		perform the read operation.
//	EFI_NO_MEDIA- There is no media in the device.
//	EFI_MEDIA_CHANGED- The MediaId is not for the current media.
//	EFI_BAD_BUFFER_SIZE- The BufferSize parameter is not a multiple
//		of the intrinsic block size of the device.
//	EFI_INVALID_PARAMETER- The read request contains LBAs that are not valid,
//		 or the buffer is not on proper alignment.
//
//<AMI_PHDR_END>
//**********************************************************************

EFI_STATUS FddReadWriteFn(
    IN EFI_BLOCK_IO_PROTOCOL *This,
    IN UINT32                MediaId,
    IN EFI_LBA               LBA,
    IN UINTN                 BufferSize,
    IN UINT8                 RWFlag,
    OUT VOID                 *Buffer )
{
    UINT8                Offset;
    UINT8                Head;
    UINT8                Cylinder;
    UINT8                Sector;
    UINT8                MaxSectors;
    UINT8                *LocalBuffer;
    UINT8                *SavedBuffer = Buffer;
    UINT8                St2          = 0xff;
    UINT16               DataReg;
    UINTN                Remainder;
    UINT64               Result;
    UINTN                TrackLength;
    UINTN                NumBlks;
    EFI_LBA              LocalLBA          = LBA;
    EFI_BLOCK_IO_MEDIA   *BlkMedia         = This->Media;
    FLOPPY_CTRL_PROTOCOL *FloppyInterface  = (FLOPPY_CTRL_PROTOCOL*)This;
    FDD_CMD_PKT          *FdcRWCmdPkt      = &(FloppyInterface->CmdRdWrSect);
    UINT8                *ResultPacket     = (UINT8*)(&FloppyInterface->ResultPacket);
    UINTN                CommandPacketSize = sizeof(FDD_CMD_PKT);
    UINTN                ResultPacketSize  = sizeof(FDD_RESULT_PACKET);

    FloppyInterface->TimerFlag = 00;
    #ifdef DXE_FLOPPY_CTRL

    if ( gSysTable ) {
        pBS->SetTimer( FloppyInterface->Event, TimerCancel, 00 );
    }
    #endif

    DataReg = FloppyInterface->BaseAddr + 05;

    // 1. Check the correctness of the input before r/w operation
    if ( gSysTable )
    {
        if ( MediaId != FloppyInterface->BlkIoMedia.MediaId ) {
            return EFI_MEDIA_CHANGED;
        }
    }

    if ( BufferSize == 0 ) {
        return EFI_SUCCESS;
    }

    if ( Buffer == NULL ) {
        return EFI_INVALID_PARAMETER;
    }

    if ((BufferSize % BlkMedia->BlockSize) !=  0 ) {
        return EFI_BAD_BUFFER_SIZE;
    }

    if ((((BufferSize / BlkMedia->BlockSize) + LBA - 1) > BlkMedia->LastBlock)
        || (LBA > BlkMedia->LastBlock)) {
        return EFI_INVALID_PARAMETER;
    }

    //2. Check Motor is ON or OFF
    if ( !(FloppyInterface->FdcFlag & FDC_FLAG_MOTOR_ON))
    {
        SetDataRate( FloppyInterface );

        // Turn on the motor
        if ( EFI_ERROR( MotorOn( FloppyInterface ))) {
            return EFI_DEVICE_ERROR;
        }

        if ( EFI_ERROR( Specify( FloppyInterface ))) {
            return EFI_DEVICE_ERROR;
        }
    }

    // 3. check for media change
    if ( CheckMediaChange( FloppyInterface ) == EFI_MEDIA_CHANGED )
    {
        FloppyInterface->FdcFlag = FDC_FLAG_NOT_INTIALIZED;

        if ( EFI_ERROR( Seek( FloppyInterface, 00, 01 )))
        {
            Delay( 5000 );

            if ( EFI_ERROR( Seek( FloppyInterface, 00, 01 ))) {
                return EFI_DEVICE_ERROR;
            }
        }

        if ( EFI_ERROR( Seek( FloppyInterface, 00, 00 )))
        {
            Delay( 5000 );

            if ( EFI_ERROR( Seek( FloppyInterface, 00, 00 ))) {
                return EFI_DEVICE_ERROR;
            }
        }
        FloppyInterface->PrCyl = 00;

        if ( CheckMediaChange( FloppyInterface ) == EFI_MEDIA_CHANGED )
        {
            FloppyInterface->BlkIoMedia.MediaPresent = FALSE;
            return EFI_NO_MEDIA;
        }
        FloppyInterface->BlkIoMedia.MediaPresent = TRUE;
        (FloppyInterface->BlkIoMedia.MediaId)++;
        FloppyInterface->BlkIoMedia.ReadOnly = FALSE;
    }

    if ( FloppyInterface->BlkIoMedia.MediaPresent == TRUE )
    {
        NumBlks = BufferSize / (BlkMedia->BlockSize);

        if ( RWFlag == WRITE_OPERATION )
        {
            if ( ChkDrSts( FloppyInterface, 00 ) != EFI_WRITE_PROTECTED )
            {
                // Corresponds to write operation
                if ( EFI_ERROR( ChkDrSts( FloppyInterface, 00 )) == \
                     EFI_WRITE_PROTECTED )
                {
                    FloppyInterface->BlkIoMedia.ReadOnly = TRUE;
                    return EFI_WRITE_PROTECTED;
                }
            }
            else {
                FloppyInterface->BlkIoMedia.ReadOnly = TRUE;
                return EFI_WRITE_PROTECTED;
            }
        }

        for (; NumBlks > 0;)
        {
            //7. Prepare Read or Write packet
            FdcRWCmdPkt = &(FloppyInterface->CmdRdWrSect);

            if ( RWFlag == READ_OPERATION ) {
                FdcRWCmdPkt->CommandCode = RD_SECTOR_CMD   \
                                           + M_COMMAND_BIT_MULTITRACK_OPERATION   \
                                           + F_COMMAND_BIT_MFM_RECORDING_METHOD   \
                                           + S_COMMAND_BIT_SKIP_MODE;
            }
            else {
                FdcRWCmdPkt->CommandCode = WR_SECTOR_CMD   \
                                           + F_COMMAND_BIT_MFM_RECORDING_METHOD;
            }

            MaxSectors = FloppyInterface->MaxSectors;
            Result     =        Div64( LocalLBA, (UINT32)MaxSectors,            &Remainder );
            Head       = (UINT8)( Result ) % 02;
            Sector     = (UINT8)Remainder + 01;
            Cylinder   = (UINT8)Div64( LocalLBA, (UINT32)( MaxSectors * 2 ), NULL );

            //7a. Seek to the perticular cylinder
            // Delay(4000);
            // Standard delay =3MilliSec for Track to track change
            if ((FloppyInterface->PrCyl != Cylinder) || (St2 == 0xFF))
            {
                if ( EFI_ERROR( Seek( FloppyInterface, Head, Cylinder )))
                {
                    // Standard delay =3MilliSec for Track to track change
                    Delay( 4000 );

                    if ( EFI_ERROR( Seek( FloppyInterface, Head, Cylinder ))) {
                        return EFI_DEVICE_ERROR;
                    }
                }
                St2                    = 00;
                FloppyInterface->PrCyl = Cylinder;
            }

            FdcRWCmdPkt->HeadDdrSel = (UINT8)( Head << 02 )   \
                                      + FloppyInterface->DriveNum;
            FdcRWCmdPkt->Cylinder = Cylinder;
            FdcRWCmdPkt->Head     = Head;
            FdcRWCmdPkt->Sector   = Sector;
            // Sector size: 00-128Bytes, 01-256Bytes, 02-512Bytes ...07-16Kbytes
            FdcRWCmdPkt->Size        = 02;
            FdcRWCmdPkt->TrackLength = MaxSectors;

            if ((Sector + NumBlks - 1) <= MaxSectors )
            {
                TrackLength = NumBlks;
                NumBlks     = 00;
            }
            //###DEBUG
            //else if((Head == 0 ) && (Sector == 1) && (NumBlks >= (UINTN)MaxSectors *2))
            //{
            //	LocalLBA					+= (MaxSectors * 2) ;
            //	NumBlks						-= (MaxSectors * 2) ;
            //	TrackLength					= MaxSectors * 2;
            //	FdcRWCmdPkt->TrackLength	= MaxSectors * 2;
            //}
            //DEBUG END
            else if ((Sector == 1) && (NumBlks >= (UINTN)MaxSectors))
            {
                LocalLBA   += MaxSectors;
                NumBlks    -= MaxSectors;
                TrackLength = MaxSectors;
                //if(RWFlag == READ_OPERATION)
                //FdcRWCmdPkt->CommandCode= RD_TRACK_CMD + BIT06 + BIT05;
            }
            else {
                LocalLBA += (MaxSectors - Sector + 1);
                NumBlks  -= (MaxSectors - Sector + 1);
                //FdcRWCmdPkt->TrackLength	= MaxSectors - Sector +1;
                TrackLength = MaxSectors - Sector + 1;
            }
            //			TRACE((-1,"FDC RWFunction: RWFlag:%x, Head :%x,Track :%x,Sector :%x,NBlks :%x\n",(UINT16)RWFlag, (UINT16)Head, (UINT16)Cylender, (UINT16)Sector, (UINT16)TrackLength));
            // Standard value = 27 - 3 1/2Floppy, = 42 - 5 1/4 Floppy;
            FdcRWCmdPkt->GapLength = 0x1b;
            // = FF if sector size not equal to 00;
            FdcRWCmdPkt->DataLength = 0Xff;

            if ((((EFI_PHYSICAL_ADDRESS)SavedBuffer   \
                  + (EFI_PHYSICAL_ADDRESS)( TrackLength * SECTOR_SIZE ))
                 > (EFI_PHYSICAL_ADDRESS)DMA_BUFFER_LIMIT)
                || ((((EFI_PHYSICAL_ADDRESS)SavedBuffer   \
                      + (EFI_PHYSICAL_ADDRESS)( TrackLength * SECTOR_SIZE )) & 0xff0000)
                    != ((EFI_PHYSICAL_ADDRESS)SavedBuffer & 0xff0000)))
            {
                LocalBuffer = FloppyInterface->DMABuffer;

                if ( RWFlag == WRITE_OPERATION ) {
                    CopyBuffer( SavedBuffer, LocalBuffer, TrackLength   \
                                * SECTOR_SIZE );
                }
            }
            else {
                LocalBuffer = (UINT8*)SavedBuffer;
            }

            // 7b. Set DMA cotroller
            DMAInitForFloppy( LocalBuffer, TrackLength, RWFlag );

            // 7c. send R/W command
            for ( Offset = 0; Offset < CommandPacketSize; Offset++ )
            {
                if ( EFI_ERROR( CheckMRQBit( FloppyInterface ))) {
                    return EFI_DEVICE_ERROR;
                }
                IoWrite8( DataReg, ((UINT8*)FdcRWCmdPkt)[Offset] );
            }

            //7d. Get the R/W command result packet
            for ( Offset = 0; Offset < ResultPacketSize; Offset++ )
            {
                //      We have initialized the DMA registers and sent the command packet.
                // Now, we wait for the result packet.  We use CheckMRQBit_NoDelay instead
                // of CheckMRQBit.  This is because of the following problem, observed on
                // the Lakeport board with South Bridge Ich7: CheckMRQBit has a loop in
                // which it checks the MRQ bit and if it isn't set calls Delay() with a
                // certain amount of time. CheckMRQBit_NoDelay just checks the MRQ bit
                // continuously until it is set.  The Delay function isn't used. The Delay
                // function uses the Stall Ppi, which is in ROM.  When this Stall Ppi
                // is used while waiting for the result packet, the floppy controller
                // always returns a DMA timeout error.  That is, the floppy controller
                // doesn't receive certain signals from the DMA controller within a required
                // time period. The DMA transaction doesn't get started.  This problem doesn't
                // occur if we don't use the Delay function.  Alternately, the problem also
                // doesn't occur if the Stall Ppi is re-installed in RAM.

                if ( EFI_ERROR( CheckMRQBit_NoDelay( FloppyInterface ))) {
                    return EFI_DEVICE_ERROR;
                }

                ResultPacket[Offset] = IoRead8( DataReg );
            }

            //7d. Check for error condition
            if ( !((*ResultPacket) & (IC1_STATUS0_BIT_INTERRUPT_CODE   \
                                      + IC0_STATUS0_BIT_INTERRUPT_CODE)))
            {
                // Read Write success
                if ( RWFlag == READ_OPERATION )
                {   // Copy Buffer
                    if ((((EFI_PHYSICAL_ADDRESS)SavedBuffer   \
                          + (EFI_PHYSICAL_ADDRESS)( TrackLength * SECTOR_SIZE ))
                         > (EFI_PHYSICAL_ADDRESS)DMA_BUFFER_LIMIT)
                        || ((((EFI_PHYSICAL_ADDRESS)SavedBuffer   \
                              + (EFI_PHYSICAL_ADDRESS)( TrackLength * SECTOR_SIZE )) \
                             & 0xff0000)
                            != ((EFI_PHYSICAL_ADDRESS)SavedBuffer & 0xff0000))) {
                        CopyBuffer( LocalBuffer, SavedBuffer, TrackLength \
                                    * SECTOR_SIZE );
                    }
                }
                SavedBuffer = (UINT8*)((EFI_PHYSICAL_ADDRESS)SavedBuffer   \
                                       + (EFI_PHYSICAL_ADDRESS)( TrackLength * SECTOR_SIZE ));
            }
            else {
                #ifdef EFI_DEBUG

                if ( gSysTable ) {
                    #ifdef DXE_FLOPPY_CTRL
                    TRACE((-1, "FddReadWriteFn Error: \n"));
                    TRACE((-1, "ST0: %x, ST1: %x, ST2: %x\n", FloppyInterface->ResultPacket.Status0, FloppyInterface->ResultPacket.Status1, FloppyInterface->ResultPacket.Status2));
                    TRACE((-1, "Cylinder: %x, Head: %x, Sector Number: %x, Sector Size: %x\n", FloppyInterface->ResultPacket.Cylinder, FloppyInterface->ResultPacket.Head, FloppyInterface->ResultPacket.SectorNumber, FloppyInterface->ResultPacket.SectorSize));
                    #endif
                }
                else {
                    #ifdef PEI_FLOPPY_CTRL
                    PEI_TRACE((-1, PeiServices, "FddReadWriteFn: \n"));
                    PEI_TRACE((-1, PeiServices, "ST0: %x, ST1: %x, ST2: %x\n", FloppyInterface->ResultPacket.Status0, FloppyInterface->ResultPacket.Status1, FloppyInterface->ResultPacket.Status2));
                    PEI_TRACE((-1, PeiServices, "Cylinder: %x, Head: %x, Sector Number: %x, Sector Size: %x\n", FloppyInterface->ResultPacket.Cylinder, FloppyInterface->ResultPacket.Head, FloppyInterface->ResultPacket.SectorNumber, FloppyInterface->ResultPacket.SectorSize));
                    #endif
                }
                #endif
                return EFI_DEVICE_ERROR;
            }
        }   // Read command end
        return EFI_SUCCESS;
    }
    return EFI_NO_MEDIA;
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:	CopyBuffer
//
// Description: Copie source to destination of required size
//
// Input:
//  IN  VOID *InBuffer,
//  IN  VOID *OutBuffer,
//  IN  UINTN Count
//
// Output:
//  VOID
//
//<AMI_PHDR_END>
//**********************************************************************

void CopyBuffer(
    IN VOID  *InBuffer,
    IN VOID  *OutBuffer,
    IN UINTN Count )
{
    UINT32 *SrcBuffer  = (UINT32*)InBuffer;
    UINT32 *DestBuffer = (UINT32*)OutBuffer;
    UINTN  i           = 0;
    UINTN  size        = Count / 4;

    for ( i = 0; i < size; i++ )
    {
        DestBuffer[i] = SrcBuffer[i];
    }
}

static DMA_INIT DmaInitTable [] = {
    // Core8 DMAC.ASM file (Fn-init_8237)
    0x00C,           0x000,   // Reset DMA Controller 1
    0x008,           0x000,   // Enable DMA controller 1

    0x0D8,           0x000,   // Reset DMA Controller 2
    0x0D0,           0x000,   // Enable DMA controller 2

    0x00B,           0x040,   // DMA contr. 1 Ch0 single mode, addr. increment, disable auto init.
    0x00A,           0x000,   // Enable DREQs for channel

    0x00B,           0x041,   // DMA contr. 1 Ch1 single mode, addr. increment, disable auto init.
    0x00A,           0x001,   // Enable DREQs for channel

    0x00B,           0x042,   // DMA contr. 1 Ch2 single mode, addr. increment, disable auto init.
    0x00A,           0x002,   // Enable DREQs for channel

    0x00B,           0x043,   // DMA contr. 1 CH3 single mode, addr. increment, disable auto init.
    0x00A,           0x003,   // Enable DREQs for channel

    0x0D6,           0x0c0,   // DMA contr. 2 Ch4 Cascade mode, addr. increment, disable auto init.
    0x0d4,           0x000,   // Enable DREQs for channel

    0x0D6,           0x041,   // DMA contr. 2 Ch5 single mode, addr. increment, disable auto init.
    0x0D4,           0x001,   // Enable DREQs for channel

    0x0D6,           0x042,   // DMA contr. 2 Ch6 single mode, addr. increment, disable auto init.
    0x0D4,           0x002,   // Enable DREQs for channel

    0x0D6,           0x043,   // DMA contr. 2 Ch7 single mode, addr. increment, disable auto init.
    0x0D4,           0x003    // Enable DREQs for channel
};

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:	DMAChInit
//
// Description: DMA controller reset function
//
// Input:
//  VOID
//
// Output:
//  VOID
//
//<AMI_PHDR_END>
//**********************************************************************

void DMAChInit( )
{
    UINTN Index;

    // DMA controller initialize
    for ( Index = 0; Index < (sizeof(DmaInitTable) / sizeof(DMA_INIT)); Index++ )
    {
        IoWrite8( DmaInitTable[Index].PortAddr, DmaInitTable[Index].Value );
        Delay(10); // Delay 10us
    }
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:	DMAInitForFloppy
//
// Description:	This function program sthe DMA-1 channel-2 for floppy read
//				and write operations
//
// Input:
//    IN VOID *Buffer,
//    IN UINTN NumBlks,
//    IN BOOLEAN RWFlag
//
// Output:
//  VOID
//
//<AMI_PHDR_END>
//**********************************************************************

void DMAInitForFloppy(
    IN VOID    *Buffer,
    IN UINTN   NumBlks,
    IN BOOLEAN RWFlag )
{
    UINTN Count;

        IoWrite8( DMA1_CH_MASK_REG, 0x06 );

    // set mode
    if ( RWFlag == READ_OPERATION ) {
        IoWrite8( DMA1_MODE_REG, 0x46 );
    }
    else {
        IoWrite8( DMA1_MODE_REG, 0x4a );
    }

    // set base address and page register
        IoWrite8( DMA1_RESET_REG,   0x00 );
        IoWrite8( DMA1_ADDR_REG,    (UINT8)( UINTN ) Buffer );
        IoWrite8( DMA1_ADDR_REG,    (UINT8)((UINTN)Buffer >> 8 ));
        IoWrite8( DMA1_PAGE_REG,    (UINT8)((UINTN)Buffer >> 16 ));

    // set count register
        IoWrite8( DMA1_RESET_REG,   0x00 );
    Count = SECTOR_SIZE * NumBlks - 1;
        IoWrite8( DMA1_COUNT_REG,   (UINT8)Count );
    Count >>= 8;
        IoWrite8( DMA1_COUNT_REG,   (UINT8)Count );

    // clear channel 2 mask
        IoWrite8( DMA1_CH_MASK_REG, 0x02 );
}

//////////////////////////////////////////////////////////////////////////////
//							FLOPPY COMMANDS									//
//////////////////////////////////////////////////////////////////////////////

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:	ChkDrSts
//
// Description: This function in the result phase provides the status
//				information concerning the connected drives
//
// Input:
//    IN  FLOPPY_CTRL_PROTOCOL *FloppyInterface,
//    IN  UINT8 HeadNum
//
// Output:
//  EFI_STATUS
//
//<AMI_PHDR_END>
//**********************************************************************

EFI_STATUS ChkDrSts(
    IN FLOPPY_CTRL_PROTOCOL *FloppyInterface,
    IN UINT8                HeadNum )
{
    EFI_STATUS Status3;
    UINT16     DataReg;

    DataReg = FloppyInterface->BaseAddr + 05;

    // Command phase
    if ( EFI_ERROR( CheckBusyBit( FloppyInterface ))) {
        return EFI_DEVICE_ERROR;
    }

    if ( EFI_ERROR( CheckMSRDOBit( FloppyInterface ))) {
        return EFI_DEVICE_ERROR;
    }
    IoWrite8( DataReg, CHECK_DRV_STATUS_CMD );

    if ( EFI_ERROR( CheckMSRDOBit( FloppyInterface ))) {
        return EFI_DEVICE_ERROR;
    }
    IoWrite8( DataReg, (UINT8)((HeadNum << (UINT8)02)   \
                               + FloppyInterface->DriveNum ));

    // Result phase
    if ( EFI_ERROR( CheckMSRDIBit( FloppyInterface ))) {
        return EFI_DEVICE_ERROR;
    }
    Status3 = IoRead8( DataReg );

    if ( Status3 & BIT06 )
    {
        FloppyInterface->FdcFlag |= FDC_FLAG_WRITE_PROTECTED;
        return EFI_WRITE_PROTECTED;
    }

    if ( EFI_ERROR( CheckBusyBit( FloppyInterface ))) {
        return EFI_DEVICE_ERROR;
    }
    return EFI_SUCCESS;
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:	Specify
//
// Description: This function passes the controller mechanical control
//				of the data of the connected drives.
//
// Input:
//    IN  FLOPPY_CTRL_PROTOCOL *FloppyInterface,
//
// Output:
//  EFI_STATUS
//
//<AMI_PHDR_END>
//**********************************************************************

EFI_STATUS Specify(
    IN FLOPPY_CTRL_PROTOCOL *FloppyInterface )
{
    FDD_SPECIFY_CMD *FdcSpecifyCmd;
    UINT8           Offset;
    UINT16          DataReg;

    DataReg       = FloppyInterface->BaseAddr + 05;
    FdcSpecifyCmd = &(FloppyInterface->CmdSpecify);

    FdcSpecifyCmd->CommandCode = SPECIFY_CMD;

    // corresponding to 720KB drive
    if ( FloppyInterface->FloppyDiskFormat == DoubleDensity720Kb )
    {
        FdcSpecifyCmd->Ctrldata1 = 0xaF;
        FdcSpecifyCmd->Ctrldata2 = 02;
    }
    // corresponding to 1.44 MB drive
    else if ( FloppyInterface->FloppyDiskFormat == HighDensity1_44Mb )
    {
        //FdcSpecifyCmd->Ctrldata1	= 0xbF;
        FdcSpecifyCmd->Ctrldata1 = 0xDF;
        FdcSpecifyCmd->Ctrldata2 = 02;
    }
    else {      // corresponding to 2.88 MB drive
        FdcSpecifyCmd->Ctrldata1 = 0xDF;
        FdcSpecifyCmd->Ctrldata2 = 02;
    }

    if ( EFI_ERROR( CheckBusyBit( FloppyInterface ))) {
        return EFI_DEVICE_ERROR;
    }

    for ( Offset = 0; Offset < sizeof (FDD_SPECIFY_CMD); Offset++ )
    {
        if ( EFI_ERROR( CheckMSRDOBit( FloppyInterface ))) {
            return EFI_DEVICE_ERROR;
        }
        IoWrite8( DataReg, *(((UINT8*)FdcSpecifyCmd)++));
    }

    if ( EFI_ERROR( CheckBusyBit( FloppyInterface ))) {
        return EFI_DEVICE_ERROR;
    }
    return EFI_SUCCESS;
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:	Calibrate
//
// Description: This function moves the read/write head to cylinder 0.
//
// Input:
//    IN  FLOPPY_CTRL_PROTOCOL *FloppyInterface,
//
// Output:
//  EFI_STATUS
//
//<AMI_PHDR_END>
//**********************************************************************

EFI_STATUS Calibrate(
    IN FLOPPY_CTRL_PROTOCOL *FloppyInterface )
{
    EFI_STATUS        Status;
    FDD_CALIBRATE_CMD *FdcCalibrateCmd;
    UINT8             Offset;
    UINT8             DriveNum;
    UINT16            DataReg;

    DriveNum        = FloppyInterface->DriveNum;
    DataReg         = FloppyInterface->BaseAddr + 05;
    FdcCalibrateCmd = &(FloppyInterface->CmdCalibrate);

    FdcCalibrateCmd->CommandCode = CALIBRATE_CMD;
    FdcCalibrateCmd->HeadDdrSel  = DriveNum;

    if ( EFI_ERROR( CheckBusyBit( FloppyInterface ))) {
        return EFI_DEVICE_ERROR;
    }

    for ( Offset = 0; Offset < sizeof (FDD_CALIBRATE_CMD); Offset++ )
    {
        if ( EFI_ERROR( CheckMSRDOBit( FloppyInterface ))) {
            return EFI_DEVICE_ERROR;
        }
        IoWrite8( DataReg, *(((UINT8*)FdcCalibrateCmd)++));
    }
    Delay( 200000 );

    // Send CHECK_INT_STATUS command
    if ( EFI_ERROR( CheckMSRDOBit( FloppyInterface ))) {
        return EFI_DEVICE_ERROR;
    }
    IoWrite8( DataReg, (UINT8)CHECK_INT_STATUS_CMD );

    if ( EFI_ERROR( CheckMSRDIBit( FloppyInterface ))) {
        return EFI_DEVICE_ERROR;
    }
    Status = IoRead8( DataReg );

    if ( EFI_ERROR( CheckMRQBit( FloppyInterface ))) {
        return EFI_DEVICE_ERROR;
    }
    IoRead8( DataReg );

    if ((Status & 0xf0) == 0x20 )
    {
        if ( EFI_ERROR( CheckBusyBit( FloppyInterface )))
        {
            #ifdef EFI_DEBUG

            if ( gSysTable ) {
                #ifdef DXE_FLOPPY_CTRL
                TRACE((-1, "FDC: CalibrateFn1 Status: %x\n", Status));
                #endif
            }
            else {
                #ifdef PEI_FLOPPY_CTRL
                PEI_TRACE((-1, PeiServices, "FDC: CalibrateFn1 Status: %x\n", Status));
                #endif
            }
            #endif
            return EFI_DEVICE_ERROR;
        }
        return EFI_SUCCESS;
    }

    #ifdef EFI_DEBUG

    if ( gSysTable ) {
        #ifdef DXE_FLOPPY_CTRL
        TRACE((-1, "FDC: CalibrateFn2 Status: %x\n", Status));
        #endif
    }
    else {
        #ifdef PEI_FLOPPY_CTRL
        PEI_TRACE((-1, PeiServices, "FDC: CalibrateFn2 Status: %x\n", Status));
        #endif
    }
    #endif
    return EFI_DEVICE_ERROR;
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:	Seek
//
// Description: This function moves the read/write head to the park cylinder.
//
// Input:
//    IN  FLOPPY_CTRL_PROTOCOL *FloppyInterface,
//    IN  UINT8 HeadNum,
//    IN  UINT8 CylNum
//
// Output:
//  EFI_STATUS
//
//<AMI_PHDR_END>
//**********************************************************************

EFI_STATUS Seek(
    IN FLOPPY_CTRL_PROTOCOL *FloppyInterface,
    IN UINT8                HeadNum,
    IN UINT8                CylNum )
{
    EFI_STATUS   Status;
    FDD_SEEK_CMD *FdcSeekCmd;
    UINT8        Offset;
    UINT8        DriveNum;
    UINT16       DataReg;

    DriveNum   = FloppyInterface->DriveNum;
    DataReg    = FloppyInterface->BaseAddr + 05;
    FdcSeekCmd = &(FloppyInterface->CmdSeek);

    FdcSeekCmd->CommandCode = SEEK_CMD;
    FdcSeekCmd->DiskHeadSel = (HeadNum << 02) + DriveNum;
    FdcSeekCmd->NewCylinder = CylNum;

    if ( EFI_ERROR( CheckBusyBit( FloppyInterface ))) {
        return EFI_DEVICE_ERROR;
    }

    for ( Offset = 0; Offset < sizeof (FDD_SEEK_CMD); Offset++ )
    {
        if ( EFI_ERROR( CheckMSRDOBit( FloppyInterface ))) {
            return EFI_DEVICE_ERROR;
        }
        IoWrite8( DataReg, *(((UINT8*)FdcSeekCmd)++));
    }

    if ( FloppyInterface->PrCyl > CylNum ) {
        Delay((FloppyInterface->PrCyl - CylNum + 1)  * 4000 );
    }
    else {
        Delay((CylNum - FloppyInterface->PrCyl + 1)  * 4000 );
    }

    // Send CHECK_INT_STATUS command
    if ( EFI_ERROR( CheckMSRDOBit( FloppyInterface ))) {
        return EFI_DEVICE_ERROR;
    }
    IoWrite8( DataReg, (UINT8)CHECK_INT_STATUS_CMD );

    if ( EFI_ERROR( CheckMSRDIBit( FloppyInterface ))) {
        return EFI_DEVICE_ERROR;
    }
    //	Delay(5000);
    Status = IoRead8( DataReg );

    //EK1123	if(EFI_ERROR(CheckMRQBit(FloppyInterface)))
    //EK1123			return EFI_DEVICE_ERROR;
    //EK1123 START
    if ( EFI_ERROR( CheckMSRDIBit( FloppyInterface ))) {
        return EFI_DEVICE_ERROR;
    }
    //EK1123 END
    IoRead8( DataReg );

    if ((Status & 0xf0) == 0x20 ) {
        return EFI_SUCCESS;
    }
    #ifdef EFI_DEBUG

    if ( gSysTable ) {
        #ifdef DXE_FLOPPY_CTRL
        TRACE((-1, "FDC: SeekFn2 Status: %x\n", Status));
        #endif
    }
    else {
        #ifdef PEI_FLOPPY_CTRL
        PEI_TRACE((-1, PeiServices, "FDC: SeekFn2 Status: %x\n", Status));
        #endif
    }
    #endif
    return EFI_DEVICE_ERROR;
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:	Delay
//
// Description: This function introduce delay.
//
// Input:
//    IN  UINT32 MicroSec
//
// Output:
//  VOID
//
//<AMI_PHDR_END>
//**********************************************************************

static void Delay(
    IN UINT32 MicroSec )
{
    if ( gSysTable ) {
        gSysTable->BootServices->Stall( MicroSec );
    }
    else {
        gPeiStall->              Stall( PeiServices, gPeiStall, MicroSec );
    }
}

//////////////////////////////////////////////////////////////////////////////
//						   MOTOR ON/OFF FUNCTIONS							//
//////////////////////////////////////////////////////////////////////////////

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:	MotorOn
//
// Description: This function turns the motor on, selects a perticular drive
//				and enables the DMA controller
//
// Input:
//    IN  FLOPPY_CTRL_PROTOCOL *FloppyInterface
//
// Output:
//  EFI_STATUS
//
//<AMI_PHDR_END>
//**********************************************************************

EFI_STATUS MotorOn(
    IN FLOPPY_CTRL_PROTOCOL *FloppyInterface )
{
    UINT8  Data;
    UINT16 DOR;
    UINT8  DriveNum;

    DriveNum = FloppyInterface->DriveNum;
    DOR      = FloppyInterface->BaseAddr + 02;

    if ( EFI_ERROR( CheckBusyBit( FloppyInterface ))) {
        return EFI_DEVICE_ERROR;
    }
    // Check motor is alredy on
    Data = IoRead8( DOR );

    if ( Data & (MOTORA_START_BIT << DriveNum)) {
        return EFI_SUCCESS;
    }

    // Select drive and enable controller
    Data = CTRL_EN_BIT | DMA_IRQEN_BIT;

    IoWrite8( DOR, Data );
    Delay( 10000 );

    // Turn on the motor
    if ( DriveNum == 00 )
    {
        Data |= DriveNum | MOTORA_START_BIT;
    }
    else {
        Data |= DriveNum | MOTORB_START_BIT;
    }
    IoWrite8( DOR, Data );

    if ( EFI_ERROR( CheckBusyBit( FloppyInterface ))) {
        return EFI_DEVICE_ERROR;
    }

    if ( EFI_ERROR( CheckMRQBit( FloppyInterface ))) {
        return EFI_DEVICE_ERROR;
    }
    FloppyInterface->FdcFlag |= FDC_FLAG_MOTOR_ON;
    Delay( 20000 );

    if ( EFI_ERROR( CheckBusyBit( FloppyInterface ))) {
        return EFI_DEVICE_ERROR;
    }
    return EFI_SUCCESS;
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:	MotorOff
//
// Description: This function turns off the motor.
//
// Input:
//    IN  EFI_EVENT Event,
//    IN  VOID *Context
//
// Output:
//  EFI_STATUS
//
//<AMI_PHDR_END>
//**********************************************************************

EFI_STATUS MotorOff(
    IN EFI_EVENT Event,
    IN VOID      *Context )
{
    UINT8                Data;
    UINT16               DOR;
    UINT8                DriveNum;

    FLOPPY_CTRL_PROTOCOL *FloppyInterface = Context;

    //	create timer event
    if ( FloppyInterface->TimerFlag != 01 ) {
        return EFI_SUCCESS;
    }

    DriveNum = FloppyInterface->DriveNum;
    DOR      = FloppyInterface->BaseAddr + 02;
    // Check motor is alredy on
    //###DEBUG if(EFI_ERROR(CheckBusyBit(FloppyInterface)))
    //	return EFI_DEVICE_ERROR;
    //if(EFI_ERROR(CheckMRQBit(FloppyInterface)))
    //	return EFI_DEVICE_ERROR;
    //Data		= IoRead8(DOR);
    //###DEBUG END
    // Turn OFF the motor

    if ( EFI_ERROR( CheckBusyBit( FloppyInterface ))) {
        return EFI_DEVICE_ERROR;
    }

    if ( EFI_ERROR( CheckMRQBit( FloppyInterface ))) {
        return EFI_DEVICE_ERROR;
    }
    Data = IoRead8( DOR );

    if ( Data & (MOTORA_START_BIT << DriveNum))
    {
        if ( DriveNum == 00 )
        {
            Data &= 0xEF;
            IoWrite8( DOR, Data );
        }

        if ( DriveNum == 01 )
        {
            Data &= 0xDF;
            IoWrite8( DOR, Data );
        }
            Delay( 20000 );
    }
    FloppyInterface->FdcFlag &= ~(FDC_FLAG_MOTOR_ON);
    return EFI_SUCCESS;
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:	CtrlReset
//
// Description: This function resets the controller and enables the
//				Floppy disk controller and DMA controller.
//
// Input:
//    IN  FLOPPY_CTRL_PROTOCOL *FloppyInterface
//
// Output:
//  EFI_STATUS
//
//<AMI_PHDR_END>
//**********************************************************************

EFI_STATUS CtrlReset(
    IN FLOPPY_CTRL_PROTOCOL *FloppyInterface )
{
    UINT8  Data;
    UINT16 DOR;
    UINT8  DriveNum;

    DriveNum = FloppyInterface->DriveNum;
    DOR      = FloppyInterface->BaseAddr + 02;

    Data = 00 + DriveNum;

    IoWrite8( DOR, Data );
    Delay( 1000 );
    Data = CTRL_EN_BIT | DMA_IRQEN_BIT | DriveNum;
    IoWrite8( DOR, Data );
    Delay( 1000 );
    return EFI_SUCCESS;
}

//////////////////////////////////////////////////////////////////////////////
//						FLOPPY DRIVE PARAMETERS								//
//								&                                                                                       //
//						    TESTING FUNCTONS								//
//////////////////////////////////////////////////////////////////////////////

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:	SetDataRate
//
// Description: This function programs the data transmit rate for
//				the floppy controller.
//
// Input:
//    IN  FLOPPY_CTRL_PROTOCOL *FloppyInterface
//
// Output:
//  VOID
//
//<AMI_PHDR_END>
//**********************************************************************

void SetDataRate(
    IN FLOPPY_CTRL_PROTOCOL *FloppyInterface )
{
    UINT8  Data;
    UINT16 CCR;

    //CCR: Configuration Control Register
    CCR = FloppyInterface->BaseAddr + 07;

    if ( FloppyInterface->FloppyDiskFormat == DoubleDensity720Kb ) {
        Data = 10;       // 01 -720kbps/s-720KByte floppy in 1.44MB drive
    }
    else if ( FloppyInterface->FloppyDiskFormat == HighDensity1_44Mb )
    {
        Data = 00;       // 00 -500kbits/s-1.44MB floppy  in 1.44MB drive
    }
    else {
        Data = 00;
    }
    IoWrite8( CCR, Data );
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:	CheckBusyBit
//
// Description: This function checks the main status register BIT04
//				to find whether controller is cutrrently is executing a
//				command or not?
//
// Input:
//    IN  FLOPPY_CTRL_PROTOCOL *FloppyInterface
//
// Output:
//  EFI_STATUS
//
//<AMI_PHDR_END>
//**********************************************************************

EFI_STATUS CheckBusyBit(
    IN FLOPPY_CTRL_PROTOCOL *FloppyInterface )
{
    UINT8  Status;
    UINT16 Count = 30000;
    UINT16 MSR;

    MSR = FloppyInterface->BaseAddr + 04;

    while ( Count-- )
    {
        Status = IoRead8( MSR );

        if ( !(Status & BUSY_BIT)) {
            return EFI_SUCCESS;
        }
        Delay( 100 );
    }
    return EFI_TIMEOUT;
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:	CheckMRQBit
//
// Description: This function checks the main status register BIT04 to find
//				whether data register is free to receive or provide commands.
//
// Input:
//    IN  FLOPPY_CTRL_PROTOCOL *FloppyInterface
//
// Output:
//  EFI_STATUS
//
//<AMI_PHDR_END>
//**********************************************************************

EFI_STATUS CheckMRQBit(
    IN FLOPPY_CTRL_PROTOCOL *FloppyInterface )
{
    UINT8  Status;
    UINT16 Count = 30000;
    UINT16 MSR;

    MSR = FloppyInterface->BaseAddr + 04;

    while ( Count-- )
    {
        Status = IoRead8( MSR );

        if ( Status & MRQ_BIT ) {
            return EFI_SUCCESS;
        }
        Delay( 100 );
    }
    return EFI_TIMEOUT;
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:	CheckMRQBit_NoDelay
//
// Description: This function checks the main status register BIT04 to find
//				whether data register is free to receive or provide commands.
//				It does not use the Delay function.
//
// Input:
//    IN  FLOPPY_CTRL_PROTOCOL *FloppyInterface
//
// Output:
//  EFI_STATUS
//
//<AMI_PHDR_END>
//**********************************************************************

EFI_STATUS CheckMRQBit_NoDelay(
    IN FLOPPY_CTRL_PROTOCOL *FloppyInterface )
{
    UINT8  Status;
    UINT32 Count = 500000;
    UINT16 MSR;

    MSR = FloppyInterface->BaseAddr + 04;

    while ( Count-- )
    {
        Status =         IoRead8( MSR );

        if ( Status & MRQ_BIT ) {
            return EFI_SUCCESS;
        }
    }
    return EFI_TIMEOUT;
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:	CheckMSRDIBit
//
// Description: This function checks the main status register DIO bit6.
//				Using DIO the controller indicates whether it expects data
//				from the CPU or it wants to handover staus information to it.
//
// Input:
//    IN  FLOPPY_CTRL_PROTOCOL *FloppyInterface
//
// Output:
//  EFI_STATUS
//
//<AMI_PHDR_END>
//**********************************************************************

EFI_STATUS CheckMSRDIBit(
    IN FLOPPY_CTRL_PROTOCOL *FloppyInterface )
{
    EFI_STATUS Status;
    UINT16     Count = 20000;
    UINT16     MSR;

    MSR = FloppyInterface->BaseAddr + 04;

    while ( Count-- )
    {
        Status =         IoRead8( MSR );

        if ( Status & BIT06 )
        {
            Count = 20000;
            while ( Count-- )
            {
                Status = IoRead8( MSR );

                if ( Status & MRQ_BIT ) {
                    return EFI_SUCCESS;
                }
                Delay( 100 );
            }
            return EFI_SUCCESS;
        }
                Delay( 100 );
    }
    return EFI_TIMEOUT;
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:	CheckMSRDOBit
//
// Description: This function checks the main status register DIO bit6.
//				Using DIO the controller indicates whether it expects data
//				from the CPU or it wants to handover staus information to it.
//
// Input:
//    IN  FLOPPY_CTRL_PROTOCOL *FloppyInterface
//
// Output:
//  EFI_STATUS
//
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS CheckMSRDOBit(
    IN FLOPPY_CTRL_PROTOCOL *FloppyInterface )
{
    EFI_STATUS Status;
    UINT16     Count = 20000;
    UINT16     MSR;

    MSR = FloppyInterface->BaseAddr + 04;

    while ( Count-- )
    {
        Status =         IoRead8( MSR );

        if ( !(Status & BIT06))
        {
            Count = 20000;
            while ( Count-- )
            {
                Status = IoRead8( MSR );

                if ( Status & MRQ_BIT ) {
                    return EFI_SUCCESS;
                }
                Delay( 100 );
            }
            return EFI_SUCCESS;
        }
                Delay( 100 );
    }
    return EFI_TIMEOUT;
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:	CheckMediaChange
//
// Description: This function reads the DIR register to determine the
//				Disk change.
//
// Input:
//    IN  FLOPPY_CTRL_PROTOCOL *FloppyInterface
//
// Output:
//  EFI_STATUS
//
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS CheckMediaChange(
    IN FLOPPY_CTRL_PROTOCOL *FloppyInterface )
{
    UINT8  Data;
    UINT16 DIR;

    DIR = FloppyInterface->BaseAddr + 07;

    if ( EFI_ERROR( CheckBusyBit( FloppyInterface ))) {
        return EFI_DEVICE_ERROR;
    }

    if ( EFI_ERROR( CheckMRQBit( FloppyInterface ))) {
        return EFI_DEVICE_ERROR;
    }
    Data = IoRead8( DIR );

    if ( EFI_ERROR( CheckBusyBit( FloppyInterface ))) {
        return EFI_DEVICE_ERROR;
    }

    if ( EFI_ERROR( CheckMRQBit( FloppyInterface ))) {
        return EFI_DEVICE_ERROR;
    }

    if ( !(Data & DISK_CHG_STS_BIT))
    {
        FloppyInterface->BlkIoMedia.MediaPresent = TRUE;
        return EFI_SUCCESS;
    }

    //	if(gSysTable)
    //		FloppyInterface->BlkIoMedia.MediaPresent	= FALSE;
    //	else
    //		FloppyInterface->PeimBlkIo.MediaPresent		= FALSE;
    return EFI_MEDIA_CHANGED;
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:	LookupFloppyHid
//
// Description:	This fuction searches the Floppy device in table that
//				matches given HID and UID
//
// Input:
//	UINT32			hid - HID to look for
//	UINT32			uid - UID to look for
//
// Output:
//	TRUE if match is found, FALSE otherwise
//
//<AMI_PHDR_END>
//**********************************************************************
BOOLEAN LookupFloppyHid(
    IN UINT32 hid,
    IN UINT32 uid )
{
    UINT8 FloppyUid;

    for ( FloppyUid = 0; FloppyUid <= 3; FloppyUid++ )
    {
        if ( hid == EISA_PNP_ID( 0x604 ) && uid == FloppyUid ) {
            return TRUE;
        }
    }
    return FALSE;
}

#ifdef DXE_FLOPPY_CTRL
//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:	GetFloppy_DP
//
// Description:	This fuction returns the last node in the device
//  path for the given controller.
//
// Input:
//  IN  EFI_DRIVER_BINDING_PROTOCOL	*This,
//  IN  EFI_HANDLE					Controller,
//  IN  ACPI_HID_DEVICE_PATH**			Floppydp,
//  IN  UINT32						Attributes,
//  IN  BOOLEAN						Close
//
// Output:
//			EFI_SUCCESS or EFI_UNSUPPORTED
//
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS GetFloppy_DP(
    IN EFI_DRIVER_BINDING_PROTOCOL *This,
    IN EFI_HANDLE                  Controller,
    IN ACPI_HID_DEVICE_PATH        ** Floppydp,
    IN UINT32                      Attributes,
    IN BOOLEAN                     Close )
{
    EFI_STATUS               Status;
    ACPI_HID_DEVICE_PATH     *acpiDP;
    EFI_DEVICE_PATH_PROTOCOL * FloppyDevPath;

    // Get device path from Controller handle.
    Status = pBS->OpenProtocol( Controller, &gDevicePathProtocolGuid,
                                (void**)&FloppyDevPath, This->DriverBindingHandle, Controller, Attributes );

    if ( EFI_ERROR( Status )) {
        if( Status == (EFI_ALREADY_STARTED || EFI_ACCESS_DENIED)){
            return Status;
        }
        return EFI_UNSUPPORTED;
    }

    // FloppyDevPath is now the last node
    acpiDP = *Floppydp = (ACPI_HID_DEVICE_PATH*)DPGetLastNode( FloppyDevPath );

    Status = (acpiDP->Header.Type == ACPI_DEVICE_PATH
              && acpiDP->Header.SubType == ACPI_DP) ? EFI_SUCCESS : EFI_UNSUPPORTED;

    if ( Close ) {
        pBS->CloseProtocol( Controller, &gDevicePathProtocolGuid,
                            This->DriverBindingHandle, Controller );
    }

    return Status;
}

#endif
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
