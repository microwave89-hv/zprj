//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
// $Header: /Alaska/SOURCE/Core/Modules/IdeBus/IdeBus.c 65    8/16/12 3:01a Rajeshms $
//
// $Revision: 65 $
//
// $Date: 8/16/12 3:01a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Core/Modules/IdeBus/IdeBus.c $
// 
// 65    8/16/12 3:01a Rajeshms
// [TAG]  		EIP97048 
// [Category]  	New Feature
// [Description]  	ATAPI PassThru Support using
// EFI_EXT_SCSI_PASS_THRU_PROTOCOL.
// [Files]  		AhciBus.c, AhciController.c, IdeBus.c, Atapi.c, PIDEBus.h,
// PAhciBus.h, ScsiPassThruAtapi.sdl, ScsiPassThruAtapi.mak,
// ScsiPassThruAtapi.c, ScsiPassThruAtapiSupport.h, ScsiPassThruAtapi.chm,
// ScsiPassThruExt.h
// 
// 64    8/16/12 2:25a Anandakrishnanl
// [TAG]  		EIP97113
// [Category]  	Improvement
// [Description]  	AtaPassThru - Module Enhancement
// [Files]  		AtaPassThru.c,
// AtaPassThruSupport.h,AtaPassThru.mak,IdeBus.c,AhciBus.c
// 
// 63    8/13/12 10:19a Artems
// [TAG]  		EIP97928
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	System doesn't detect drives in IDE mode
// [RootCause]  	Ide driver returns EFI_ERROR if AtaPassThru protocol is
// absent
// [Solution]  	Make driver to return EFI_SUCCESS as long as there are no
// IDE-related errors
// [Files]  		Idebus.c
// 
// 62    7/20/12 6:13a Anandakrishnanl
// [TAG]  		EIP88683
// [Category]  	New Feature
// [Description]  	EFI_ATA_PASS_THRU_PROTOCOL Support for Aptio IDE
// [Files]  		AhciBus.c
// AhciBus.h
// AInt13.h
// IdeBus.c
// IdeBus.h
// PIDEBus.h
// PAhciBus.h
// AtaPassThru.sdl
// AtaPassThru.mak	
// AtaPassThru.c	
// AtaPassThruSupport.h
// AtaPassThru.chm
// 
// 61    6/13/12 8:49a Anandakrishnanl
// [TAG]  		EIP92381
// [Category]  	Improvement
// [Description]  	A slip of pen in function IdeBusStart
// [Files]  		IdeBus.c
// 
// 60    12/05/11 6:12p Rajkumarkc
// [TAG]  		EIP77142 
// [Category]  	Improvement
// [Description]	Added the function 'IdeNonDataCommandExp' in the
// 'IDE_BUS_PROTOCOL' and removed
//               the existing function 'IdeNonDataCommand' for supporting
// the upper 24bits of LBA.
// [Files]
//     Ata.c
//     IdeBus.c
//     Idebus.h
//     PIDEBus.h
// 
// 59    11/16/11 12:35a Rameshr
// [TAG]  		EIP74970
// [Category]  	Improvement
// [Description]  	Generic GUID variables should be defined as static, or
// not used at all
// [Files]  		Idebus.c
// 
// 57    11/04/11 5:45a Rameshr
// [TAG]  		EIP73035
// [Category]  	Improvement
// [Description]  	Status used on line 2561, conditionally not set.
// Initilized to EFI_SUCCESS to avoid Junk values.
// [Files]  		Idebus.c
// 
// 56    11/03/11 6:07a Rajeshms
// [TAG]  		EIP73260
// [Category]  	Improvement
// [Description]  	IDE Driver Follow the UEFI Driver Model as per the UEFI
// Spec. and STOP function was Verified.
// [Files]  		IdeBus.c
// 
// 55    9/27/11 3:13a Rajeshms
// [TAG]  		EIP69295
// [Category]  	Improvement
// [Description]  	The Timeout values used by IDE and AHCI drivers are
// made as SDL tokens, so that the timeout values can be varied.
// [Files]  		IdeBusBoard.c, CORE_DXE.sdl, AhciSmm.h, AhciBus.h, IDESMM.h,
// Ata.c, Atapi.c, IdeBus.c, IdeBus.h, IdeBusMaster.c, IdeBusBoard.h
// 
// 54    8/22/11 2:56a Anandakrishnanl
// [TAG]  		EIP62912
// [Category]  	Improvement
// [Description]  	Opal Security Definitions Should be Moved to PIDEBUS.h
// from StorageSecurityProtocol.h
// StorageSecurityProtocol.h included in OPAL security driver module will
// give build error when disabled without sdl token #if
// OpalSecurity_SUPPORT properly placed in Ahcibus and IdeBus drivers. But
// Bus driver should not depend on any tokens. For this reason need to
// move OPAL_SEC_INIT_PROTOCOL_GUID in Pidebus.h
// [Files]  		IdeBus.c
// Pidebus.h
// OpalSecurity.cif
// OpalSecurity.h
// IdeOpalSec.c
// AhciOpalSec.c
// 
// 53    7/07/11 2:04a Lavanyap
// [TAG]  		EIP60503
// [Description]  	Added proper comment in InitAcousticSupport() function
// header
// [Files]  		IdeBus.c
// 
// 52    7/07/11 1:56a Lavanyap
// [TAG]  		EIP55207 
// [Category]  	Improvement
// [Description]  	Ide Bus Drive Component Name does not remove trailing
// spaces from drive name
// [Files]  		IdeBus.c
// 
// 51    6/13/11 1:27p Artems
// Made file build when OpalSecurity module is absent
// 
// 50    5/19/11 3:10a Anandakrishnanl
// [TAG]  		EIP53565
// [Category]  	New Feature
// [Description]  	UEFI2.3+ Specifications defines Storage Security
// protocol which needs to be implemented.
// [Files]  		AhciBus.c,IdeBus.c,AHCIOpalSec.c,IDEOpalSec.c,OpalSecurity.c
// ,OpalSecurity.chm,OpalSecurity.cif,OpalSecurity.h,OpalSecurity.mak,Opal
// Security.sdl,PIDEBus.h,StorageSecurityProtocol.CIF,StorageSecurityProto
// col.h
// 
// 49    5/02/11 12:38a Rameshr
// [TAG]- EIP 58703
// [Category]-IMPROVEMENT
// [Description]- Implement correct behavior when RemainingDevicePath
// passed to Supported() function consist only of end node, as described
// in UEFI specification Version 2.3.1, page 10.1
// EFI_DRIVER_BINDING_PROTOCOL.Supported() and Start() 
// [Files]- Idebus.c
// 
// 48    5/02/11 12:23a Rameshr
// [TAG]- EIP 58686
// [Category]-IMPROVEMENT
// [Description]- Update implementation of EFI_BLOCK_IO_PROTOCOL as
// described in UEFI specification Version 2.3.1, page 12.8
// [Files]- Idebus.c, Atapi.c
// 
// 47    4/12/11 4:05a Rameshr
// [TAG]- EIP 53710
// [Category]- New Feature
// [Description]- ATAPI ODD loading type information added into ATAPI
// device structure 
// [Files]- Atapi.c, Idebus.c, IdeBus.h 
// 
// 46    12/23/10 3:54a Lavanyap
// [TAG] - EIP41445
// [Category] - NEW FEATURE
// [Description] - Created SataPioDataOut and AtaPioDataOut protocol
// function that can accept additional input parameters.
// [Files] - AhciBus.h, AhciBus.c, AhciController.c, Ata.c, IdeBus.c,
//           IdeBus.h, IdeBusMaster.c,PAhciBus.h, PIdeBus.h
// 
// 45    9/24/10 2:43a Rameshr
// [TAG]- EIP 42817
// [Category]-IMPROVEMENT
// [Description]- Ide Smart checks HDDs for errors moved after Idebus
// Device path has been installed.
// [Files]- AhciBus.c, IdeBus.c
// 
// 44    8/25/10 4:16a Rameshr
// New Feature: EIP 37748
// Description: Move all the IDEBus Source driver SDL token into IdeBus
// Bin Driver.
// FilesModified: Ata.c, Atapi.c, idebus.c, IdeBus.h,
// IdebuscomponentName.c, IdeBusmaster.c IdeBusSrc.mak IdebusSrc.sdl
// IdeHpa.c, IdePowerManagement.c
// 
// 43    7/20/10 4:18p Pats
// EIP 38384: Sytem will get halt with the P-ATA to S-ATA transfer card on
// APTIO 4.6.4.
// Problem: Feature and Sector Count values are reversed in the invocation
// of IdeNonDataCommand to set DEV_CONFIG_FREEZE_LOCK.
// Solution: Fixed Feature and Sector Count values.
// 
// 42    5/26/10 6:02a Rameshr
// Checked the Device Configuration Overlay feature set supported status
// before sending the DEV_CONFIG_FREEZE_LOCK 
// EIP 38384
// 
// 41    4/16/10 4:05p Pats
// EIP 30719: Support for the HDD with sector size more than 512bytes.
// 
// 40    1/11/10 12:10p Krishnakumarg
// Update for Eip 11835 - To implement Acoustic Management function
// Eip 30041 - Aptio 4 Device Initiated Power Management (DipM) support
// for SATA devices
// 
// 39    9/04/09 3:29p Krishnakumarg
// Acoustic Management function updated to set acoustic level according to
// setup option EIP:11835
// CreateIdeDevicePath will now use EFI_OPEN_PROTOCOL_GET_PROTOCOL instead
// of EFI_OPEN_PROTOCOL_BY_DRIVER in openprotocol function.
// 
// 38    8/28/09 11:21a Felixp
// Component Name protocol implementation is upadted  to support both 
// ComponentName and ComponentName2 protocols
// (based on value of the EFI_SPECIFICATION_VERSION SDL token).
// 
// 37    7/01/09 12:23p Rameshr
// Coding Standard and File header updated.
//
// 36    6/22/09 11:38a Rameshr
// Odd Type information Saved in Atapi Device Structure.
// EIP:21548
//
// 35    5/01/09 11:01a Rameshr
// Symptom: Disconnect the IDE controller, make system to hang on debug
// mode
// Solution: IdeBlockIoDev pointer has wrong address, that make Freepool
// to hang the system. Corrected the IdeBlockIoDev address
//
// 34    4/28/09 7:17p Rameshr
// HDD password support in RAID mode
// EIP:20421
//
// 33    4/14/09 1:01p Rameshr
// When INTEL_IDE_PROTOCOL = 1, the IdeBus driver does not check if modes
// are valid in the SupportedModes data before assigning them to
// IdeBusInterface
// EIP 21195
//
// 32    11/02/09 11:16a Anandakrishnanl
// BUGFIX: Removed ASSERT Since AhciBus Driver presence may return Status
// Other than Success
//
// 31    12/31/08 3:07p Rameshraju
// BugFix- Validate the PIO mode before programming the PIO mode into the
// device EIP:17885
//
// 30    14/08/08 10:52a Anandakrishnanl
// Compatible Mode AHCI Support Added and Sdl Token Added in IdeBusSrc.sdl
//
// 29    8/06/08 10:37a Rameshraju
// Corrected problem in debug info print.
//
// 28    5/14/08 4:43p Rameshraju
// Error code added if error happens while configuring device or
// controller.
//
// 27    4/22/08 2:02p Felixp
// DXE_IDE_DETECT progress code moved from ATA.c to IdeBus.c
// DXE_IDE_ENABLE progress code added
//
// 26    3/27/08 11:21a Srinin
// CreateIdeDevicePath() modified to create a devicepath
// even if Remaining devicepath is not NULL.
//
// 25    7/03/08 5:45p Anandakrishnanl
// Added Smart related Changes since Smart is a seperate driver now and
// smart calls are now made protocol driven. Removed Sdl tokens that are
// used previously
//
// 24    3/06/08 5:20p Ambikas
//
// 23    3/06/08 4:41p Ambikas
//
// 22    3/04/08 7:51p Felixp
//
// 20    28/02/08 7:07p Anandakrishnanl
// Added HddSecurity Protocol to support security module as a separate
// driver.
//
// 19    10/23/07 4:17p Felixp
// IDE Security support moved from Sources to Binary
//
// 18    22/06/07 12:40p Anandakrishnanl
// HardDisk Security Support Module Added.
// Need ACPI Module and SB Module and under Core\Include we updated
// Setup.h.
// Also New IdeBus bin module.
//
// 17    5/04/07 12:53p Srinin
// In AHCI and RAID mode, PI reg is ignored. Always controller is in
// Native mode.
//
// 16    4/19/07 12:55p Felixp
//  - Minor bug fix: initialize block size by default with
// CDROM_BLOCK_SIZE for ATAPI devices (along with DiskIo.c changes
// resolves SCT failure)
//  - File reformatted to comply with AMI coding standards
//
// 13    4/16/07 6:29p Felixp
// Minor bug fix: initialize block size by default with CDROM_BLOCK_SIZE
// for ATAPI devices
//
// 12    13/04/07 3:01p Anandakrishnanl
// Ide Bus Module - Update source files to comply with AMI coding
// standard"!!!
//
// 11    12/19/06 6:12p Srinin
// Software setting Preserve bit set for SATA devices.
//
// 10    11/17/06 3:05p Ambikas
//
// 9     10/27/06 4:20p Felixp
// enable IDE interrupts at the exit boot services event handler
// (required to boot EFI vista)
//
// 8     8/09/06 3:34p Pavell
//
// 7     5/19/06 10:30p Felixp
// Device Path code updated to use NODE_LENGTH macros to remove direct
// access to the Length field
//
// 6     3/21/06 4:42p Srinin
// Build error Fixed.
//
// 5     3/13/06 2:20a Felixp
//
// 4     1/09/06 11:36a Felixp
//
// 2     12/14/05 3:04p Srinin
// CallBack added to support HDD password support during S3 Resume.
//
// 1     12/01/05 9:43a Felixp
//
// 16    11/03/05 10:55a Srinin
// For Busmaster transfer, Buffer should be DWORD aligned.
//
// 15    10/21/05 1:39p Srinin
// Removed Media detection for Atapi devices during Detection process.
//
// 14    8/22/05 4:31p Srinin
// ATA/ATAPI identification changed.
//
// 13    2/11/05 6:16p Felixp
// - Cleanup (duplication of library functions removed)
// - Code optimized by using DPAddNode instead of DPAdd
// - AllocatePool + ZeroMem replaced with MallocZ
//
// 12    2/01/05 12:58p Srinin
// IDE HotPlug Support added.
//
// 11    1/31/05 11:14a Srinin
// Fixed ComponentName display issue for IDE devices.
//
// 10    1/28/05 1:19p Felixp
// IdeBus is linked together with CORE_DXE
//
// 9     1/18/05 3:22p Felixp
// PrintDebugMessage renamed to Trace
//
// 8     1/13/05 4:23p Srinin
// Host Protection Area Support added.
//
// 7     1/11/05 2:26p Srinin
// IDE Power Management Support added.
//
// 5     1/10/05 11:29a Srinin
// SMART Support added.
//
// 4     1/05/05 3:55p Srinin
// Acoustic management Support added.
//
// 3     1/05/05 11:21a Srinin
// BusMaster and Password Support added.
//
// 2     12/21/04 4:57p Markw
// Modified device path defines for consistency.
//
// 1     12/10/04 1:01p Srinin
// Initial Checkin of IdeBus Driver.
//
//
//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name: IdeBus.c
//
// Description:	Provides IDE Block IO protocol
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>


#include "IdeBus.h"
#include <Protocol\IdeBusBoard.h>

static EFI_GUID     gEfiIdeBusInitProtocolGuid      = IDE_BUS_INIT_PROTOCOL_GUID;
static EFI_GUID     gIdeBusDriverBindingProtocolGuid = EFI_DRIVER_BINDING_PROTOCOL_GUID;
static EFI_GUID     gEfiDiskInfoProtocolGuid        = EFI_DISK_INFO_PROTOCOL_GUID;
static EFI_GUID     gEfiIdeDiskInfoProtocolGuid     = EFI_DISK_INFO_IDE_INTERFACE_GUID;
static EFI_GUID     gIdeSetupProtocolguid           = IDE_SETUP_PROTOCOL_GUID;
static EFI_GUID     gEfiBootScriptSaveGuid          = EFI_BOOT_SCRIPT_SAVE_GUID;
static EFI_GUID     gDevicePathProtocolGuid         = EFI_DEVICE_PATH_PROTOCOL_GUID;
static EFI_GUID     gEfiBlockIoProtocolGuid         = EFI_BLOCK_IO_PROTOCOL_GUID;
static EFI_GUID     gHddSecurityInitProtocolGuid    = HDD_SECURITY_INIT_PROTOCOL_GUID;
static EFI_GUID     gHddSmartInitProtocolGuid       = HDD_SMART_INIT_PROTOCOL_GUID;
static EFI_GUID     gHddSecurityEndProtocolGuid     = HDD_SECURITY_END_PROTOCOL_GUID;
static EFI_GUID     gPlatformIdeProtocolGuid        = PLATFORM_IDE_PROTOCOL_GUID;
static EFI_GUID     gOpalSecInitProtocolGuid        = OPAL_SEC_INIT_PROTOCOL_GUID;
static EFI_GUID     gSMARTProtocolGuid              = IDE_SMART_INTERFACE_GUID;
static EFI_GUID     gAtaPassThruInitProtocolGuid    = ATA_PASS_THRU_INIT_PROTOCOL_GUID; 
static EFI_GUID     gScsiPassThruAtapiInitProtocolGuid = SCSI_PASS_THRU_ATAPI_INIT_PROTOCOL_GUID;

EFI_GUID            gSecurityModeProtocolGuid       = IDE_SECURITY_INTERFACE_GUID;
EFI_GUID            gPowerMgmtProtocolGuid          = IDE_POWER_MGMT_INTERFACE_GUID;
EFI_GUID            gHPAProtocolGuid                = IDE_HPA_INTERFACE_GUID;


EFI_EVENT                          gIDEBusEvtBootScript      = NULL;
EFI_EVENT                          gIDEBusEvtMiscSmmFeatures = NULL;

SCSI_PASS_THRU_ATAPI_INIT_PROTOCOL   *gScsiPassThruAtapiInitProtocol; 
ATA_PASS_THRU_INIT_PROTOCOL        *AtaPassThruInitProtocol;  
OPAL_SECURITY_INIT_PROTOCOL        *OpalSecInitProtocol;
HDD_SECURITY_INIT_PROTOCOL         *HddSecurityInitProtocol;
HDD_SMART_INIT_PROTOCOL            *HddSmartInitProtocol;
IDE_SETUP_PROTOCOL		           *gIdeSetupProtocol;
PLATFORM_IDE_PROTOCOL              *gPlatformIdeProtocol;

extern EFI_COMPONENT_NAME_PROTOCOL gIdeBusControllerDriverName;

//
// Instantiate PLATFORM_IDE_PROTOCOL with default SDL Token values 
//

PLATFORM_IDE_PROTOCOL        gPlatformIdeProtocolInstance = {
    2,                                       //Protocol Revision
    1,                                       //MasterSlaveEnumeration
    1,                                       //IdeBusMasterSupport
    1,                                       //AtapiBusMasterSupport
    1,                                       //AcousticManagementSupport
    0,                                       //IdePowerManagementSupport
    5,                                       //StandbyTimeout
    0,                                       //AdvPowerManagementSupport
    1,                                       //AdvPowerManagementLevel
    0,                                       //PowerupInStandbySupport
    0,                                       //PowerupInStandbyMode
    0,                                       //IdePwrManagementInterfaceSupport
    0,                                       //HostProtectedAreaSupport
    0,                                       //IdeHPSupport
    1,                                       //EfiIdeProtocol
    0,                                       //AhciCompatibleMode
    0,                                       //SBIdeSupport
    1,                                       //HddPowerLossInS3
    0,                                       //DiPMSupport
    0,                                       //DisableSoftSetPrev
    0,                                       //ForceHddPasswordPrompt
    EFI_IDE_CONTROLLER_INIT_PROTOCOL_GUID,   //gIdeControllerProtocolGuid
    EFI_COMPONENT_NAME_PROTOCOL_GUID,        //gComponentNameProtocolGuid
    10000,                                   //S3BusyClearTimeout
    5000,                                    //DmaAtaCompleteCommandTimeout
    16000,                                   //DmaAtaPiCompleteCommandTimeout
    5000,                                    //AtaPiResetCommandTimeout
    16000,                                   //AtaPiBusyClearTimeout
    10000                                    //PoweonBusyClearTimeout 
};

EFI_DRIVER_BINDING_PROTOCOL        gIdeBusDriverBinding = {
    IdeBusSupported,
    IdeBusStart,
    IdeBusStop,
    IDE_BUS_DRIVER_VERSION,  // version
    NULL,                    // ImageHandle
    NULL                     // DriverBindingHandle
};

// Global Buffer pointer used for Bus Mastering
VOID                               *gDescriptorBuffer = NULL;

VOID InitMiscConfig (
    IN IDE_BUS_PROTOCOL    *IdeBusInterface
);

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	IdeBusExitBootServices
//
// Description:	  Enables IDE controller interrupt on ExitBootServices
//
// Input:
//      Event   - The Event that is being processed
//      Context - Event Context
//
// Output: None
//
// Modified:
//
// Referrals:
//
// Notes:
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID EFIAPI IdeBusExitBootServices(
    IN EFI_EVENT Event,
    IN VOID      *Context )
{
    EFI_STATUS            Status;
    UINTN                 Count;
    EFI_HANDLE            Buffer[0x100];
    UINTN                 BufferSize = sizeof(Buffer);
    UINT8                 i;
    UINT8                 j;
    UINT8                 k;
    IDE_BUS_INIT_PROTOCOL *IdeBusInitProtocol;
    IDE_BUS_PROTOCOL      *pIdeBusProtocol;
    UINT64                IdeDevControlReg;
    UINT64                IdeDevReg;
    UINT8                 Data8 = 0;

    Status = pBS->LocateHandle(
        ByProtocol,
        &gEfiIdeBusInitProtocolGuid,
        NULL,
        &BufferSize,
        Buffer
        );

    if ( !EFI_ERROR( Status )) {
        Count = BufferSize / sizeof(EFI_HANDLE);

        for ( i = 0; i < Count; i++ )
        {
            Status = pBS->HandleProtocol( Buffer[i], &gEfiIdeBusInitProtocolGuid, &IdeBusInitProtocol );

            if ( !Status ) {
                for ( j = 0; j < 2; j++ )
                {
                    for ( k = 0; k < 2; k++ )
                    {
                        if ( IdeBusInitProtocol->pIdeBusProtocol[j][k] ) {
                            if ( IdeBusInitProtocol->IdeBusInitData[j][k] == DEVICE_CONFIGURED_SUCCESSFULLY ) {
                                pIdeBusProtocol = IdeBusInitProtocol->pIdeBusProtocol[j][k];

                                //
                                //Dev select
                                //  
                                Data8     = pIdeBusProtocol->IdeDevice.Device << 4;
                                IdeDevReg = (UINT64)pIdeBusProtocol->IdeDevice.Regs.CommandBlock.DeviceReg;
                                pIdeBusProtocol->PciIO->Io.Write(
                                    pIdeBusProtocol->PciIO,
                                    EfiPciIoWidthUint8,
                                    EFI_PCI_IO_PASS_THROUGH_BAR,
                                    IdeDevReg,
                                    1,
                                    &Data8
                                    );


                                Data8 = 0;
                                //  
                                //Enable IDE Controller interrupt
                                //
                                IdeDevControlReg = (UINT64)pIdeBusProtocol->IdeDevice.Regs.ControlBlock.AlternateStatusReg;
                                pIdeBusProtocol->PciIO->Io.Write(
                                    pIdeBusProtocol->PciIO,
                                    EfiPciIoWidthUint8,
                                    EFI_PCI_IO_PASS_THROUGH_BAR,
                                    IdeDevControlReg,
                                    1,
                                    &Data8
                                    );
                            }
                        }
                    }
                }
            }
        }
    }
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	IdeBusEntryPoint
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
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS IdeBusEntryPoint(
    IN EFI_HANDLE       ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable )
{
    EFI_STATUS Status;
    EFI_EVENT  ExitBootServicesNotifyEvent;

    gIdeBusDriverBinding.DriverBindingHandle = NULL;
    gIdeBusDriverBinding.ImageHandle         = ImageHandle;

    InitAmiLib( ImageHandle, SystemTable );
    //
    //Register our ExitBootServices () callback function
    //  
    Status = pBS->CreateEvent(
        EFI_EVENT_SIGNAL_EXIT_BOOT_SERVICES,
        TPL_CALLBACK,
        IdeBusExitBootServices,
        NULL,
        &ExitBootServicesNotifyEvent
        );
    ASSERT_EFI_ERROR( Status );

    Status = pBS->LocateProtocol(
                    &gPlatformIdeProtocolGuid,
                    NULL,
                    &gPlatformIdeProtocol
                    );
    if (EFI_ERROR (Status)) {
        //
        // if EFI_ERROR then Assign Default values Instance to gPlatformIdeProtocol.
        //
        gPlatformIdeProtocol = (PLATFORM_IDE_PROTOCOL *)&gPlatformIdeProtocolInstance;
    }
    //
    // Assert when PLATFORM_IDE_PROTOCOL's revision is not supported 
    //
    ASSERT(!(gPlatformIdeProtocol->Revision > PLATFORM_IDE_PROTOCOL_SUPPORTED_REVISION))

    Status = pBS->InstallMultipleProtocolInterfaces(
        &gIdeBusDriverBinding.DriverBindingHandle,
        &gIdeBusDriverBindingProtocolGuid, &gIdeBusDriverBinding,
        &(gPlatformIdeProtocol->gComponentNameProtocolGuid), &gIdeBusControllerDriverName,
        NULL
        );

#ifdef Debug_Level_1
    EfiDebugPrint( -1, "IdeBusEntryPoint Exit Status %x\n", Status );
#endif

    return Status;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	IdeBusSupported
//
// Description:	Checks whether IDE_PROTOCOL_INTERFACE is installed on the controller.
//				If 'yes', return SUCCESS else ERROR
//
// Input:
//	IN EFI_DRIVER_BINDING_PROTOCOL    *This,
//	IN EFI_HANDLE                     Controller,
//	IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
//
// Output:
//	EFI_STATUS
//
// Modified:
//
// Referrals: OpenProtocol CloseProtocol
//
// Notes:
//  Here is the control flow of this function:
// 1. If Devicepath is NULL, check "gEfiIdeControllerProtocolGuid" is installed by IdeController device driver,
// if yes, it is the IDE controller that this Bus will manage. Then return Success.
// 2. If Devicepath is valid, check if "gEfiIdeBusInitProtocolGuid" is already installed by this BUS driver,
// if yes, check whether it is OK to configure this device. if not installed goto step 1.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS IdeBusSupported(
    IN EFI_DRIVER_BINDING_PROTOCOL *This,
    IN EFI_HANDLE                  Controller,
    IN EFI_DEVICE_PATH_PROTOCOL    *RemainingDevicePath )
{
    EFI_STATUS                       Status;

    VOID                             *IdeControllerInterface = NULL ;
    ATAPI_DEVICE_PATH                *AtapiRemainingDevicePath = (ATAPI_DEVICE_PATH*) RemainingDevicePath;
    IDE_BUS_INIT_PROTOCOL            *IdeBusInitInterface;
    EFI_PCI_IO_PROTOCOL              *PciIO;
    UINT8 PciConfig[256];

#ifdef Debug_Level_1
    EfiDebugPrint( -1, "IdeBusSupported Entry\n" );
#endif

    //
    //Check for Valid ATAPI Device Path. If no return UNSUPPORTED
    //
    if ( !(AtapiRemainingDevicePath == NULL)) {

        //
        // RemainingDevicePath is not NULL and begins with the End of Device Path node, 
        // then the driver must not enumerate any of the children of Controller nor create any child device handle. 
        // Only the controller initialization should be performed. UEFI specification V 2.3.1, P. 10.1
        //
        if(isEndNode(RemainingDevicePath)) {
            return EFI_SUCCESS;
        }

        //
        // Check if the AtapiRemainingDevicePath is valid 8.3.4.1
        //
        if ( AtapiRemainingDevicePath->Header.Type != MESSAGING_DEVICE_PATH
             || AtapiRemainingDevicePath->Header.SubType != MSG_ATAPI_DP
             && NODE_LENGTH( &AtapiRemainingDevicePath->Header ) != ATAPI_DEVICE_PATH_LENGTH ) {
#ifdef Debug_Level_3
            EfiDebugPrint( -1, "AtapiRemainingDevicePath not Valid\n" );
#endif
            return EFI_UNSUPPORTED;
        }

        //
        //Now check whether it is OK to enumerate the specified device.
        //
        Status = pBS->OpenProtocol( Controller,
                                    &gEfiIdeBusInitProtocolGuid,
                                    (VOID**)&IdeBusInitInterface,
                                    This->DriverBindingHandle,
                                    Controller,
                                    EFI_OPEN_PROTOCOL_BY_DRIVER );

        if ( Status == EFI_SUCCESS || Status == EFI_ALREADY_STARTED ) {
            pBS->CloseProtocol(
                Controller,
                &gEfiIdeBusInitProtocolGuid,
                This->DriverBindingHandle,
                Controller
                );

            if ( AtapiRemainingDevicePath->PrimarySecondary == PRIMARY_CHANNEL && AtapiRemainingDevicePath->SlaveMaster == MASTER_DRIVE ) {
                if ( IdeBusInitInterface->IdeBusInitData[PRIMARY_CHANNEL][MASTER_DRIVE] >= DEVICE_DETECTION_FAILED ) {
                    return EFI_ALREADY_STARTED;
                }
            }

            if ( AtapiRemainingDevicePath->PrimarySecondary == PRIMARY_CHANNEL && AtapiRemainingDevicePath->SlaveMaster == SLAVE_DRIVE ) {
                if ( IdeBusInitInterface->IdeBusInitData[PRIMARY_CHANNEL][SLAVE_DRIVE] >= DEVICE_DETECTION_FAILED ) {
                    return EFI_ALREADY_STARTED;
                }
            }

            if ( AtapiRemainingDevicePath->PrimarySecondary == SECONDARY_CHANNEL && AtapiRemainingDevicePath->SlaveMaster == MASTER_DRIVE ) {
                if ( IdeBusInitInterface->IdeBusInitData[SECONDARY_CHANNEL][MASTER_DRIVE] >= DEVICE_DETECTION_FAILED ) {
                    return EFI_ALREADY_STARTED;
                }
            }

            if ( AtapiRemainingDevicePath->PrimarySecondary == SECONDARY_CHANNEL && AtapiRemainingDevicePath->SlaveMaster == SLAVE_DRIVE ) {
                if ( IdeBusInitInterface->IdeBusInitData[SECONDARY_CHANNEL][SLAVE_DRIVE] >= DEVICE_DETECTION_FAILED ) {
                    return EFI_ALREADY_STARTED;
                }
            }
        }
    }

    //
    //Check whether IDE_CONTROLLER_PROTOCOL  has been installed on this controller
    //
    Status = pBS->OpenProtocol( Controller,
                                &(gPlatformIdeProtocol->gIdeControllerProtocolGuid),
                                (VOID**)&IdeControllerInterface,
                                This->DriverBindingHandle,
                                Controller,
                                EFI_OPEN_PROTOCOL_BY_DRIVER );

#ifdef Debug_Level_3

    if ( EFI_ERROR( Status )) {
        if ( gPlatformIdeProtocol->EfiIdeProtocol )
            EfiDebugPrint( -1, "Error opening gEfiIdeControllerInitProtocolGuid\n" );
        else
            EfiDebugPrint( -1, "Error opening gEfiIdeControllerProtocolGuid\n" );
    }
#endif

    //
    //IDE_CONTROLLER_PROTOCOL will be opened by each device. So EFI_ALREADY_STARTED is not an error
    //
    if  ( !(Status == EFI_SUCCESS || Status == EFI_ALREADY_STARTED)) {
        return EFI_UNSUPPORTED;
    }

    //
    //Close IDE_CONTROLLER_PROTOCOL
    //
    pBS->CloseProtocol(
        Controller,
        &(gPlatformIdeProtocol->gIdeControllerProtocolGuid),
        This->DriverBindingHandle,
        Controller
        );

#ifdef Debug_Level_1
    EfiDebugPrint( -1, "IdeBusSupported Exit Success\n" );
#endif
    //
    // Check if Controller is in AHCI mode or not?
    //
    Status = pBS->OpenProtocol( Controller,
                                &gEfiPciIoProtocolGuid,
                                (VOID**)&PciIO,
                                This->DriverBindingHandle,
                                Controller,
                                EFI_OPEN_PROTOCOL_GET_PROTOCOL );

    if ( EFI_ERROR( Status )) {
        return EFI_UNSUPPORTED;
    }

    Status = PciIO->Pci.Read( PciIO,
                              EfiPciIoWidthUint8,
                              0,
                              sizeof (PciConfig),
                              PciConfig
                              );

    if ((PciConfig [IDE_SUB_CLASS_CODE] == SCC_AHCI_CONTROLLER) || (PciConfig [IDE_SUB_CLASS_CODE] == SCC_RAID_CONTROLLER)) {
        if ( !(gPlatformIdeProtocol->AhciCompatibleMode) )
            return EFI_UNSUPPORTED;
    }

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	IdeBusStart
//
// Description:	Installs IDE Block IO Protocol
//
// Input:
//	IN EFI_DRIVER_BINDING_PROTOCOL    *This,
//	IN EFI_HANDLE                     Controller,
//	IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
//
// Output:
//	EFI_STATUS
//
// Modified:
//
// Referrals: OpenProtocol CloseProtocol InstallProtocolInterface AllocatePool
//
// Notes:
//  Here is the control flow of this function:
// 1.  Check if "gEfiIdeBusInitProtocolGuid" is already installed. If not, install it "InstallBusInitProtocol".
// 2.  If Devicepath is valid, initialize so that only particular device will be detected and
//	   confgiured, else all devices will be detected and configured.
// 3.  check whether the device has not been already detected. If yes, skip it and go for next device
// 4.  IdeBusInterface is initialized for this device. Update Base address.
// 5.  Do the detection "DetectIdeDevice". Update the status in "IdeBusInitProtocol". If failure undo the process "IdeBusInterface".
// 6.  Repeat for all devices from step 3.
// 7.  Start the configuration process for devices which are detected successfully "DEVICE_DETECTED_SUCCESSFULLY".
// 8.  "ConfigureIdeDeviceAndController" will do the configuration.
// 9.  If above step is success, build Devicepath "CreateIdeDevicePath"
// 10. Create the Block_io_Protocol"InitIdeBlockIO". Install it only if Device is not Password protected.
// 11. Create the DISK_INFO_PROTOCOL "InitIdeDiskInfo". Install it only if Device is not Password protected.
// 12. Install a child device with the above three protocols.
// 13. Open "gEfiIdeControllerProtocolGuid" with the child handle.
// 14. Repeat from step 8 for the remaining devices.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS IdeBusStart(
    IN EFI_DRIVER_BINDING_PROTOCOL *This,
    IN EFI_HANDLE                  Controller,
    IN EFI_DEVICE_PATH_PROTOCOL    *RemainingDevicePath )
{
    EFI_STATUS                       Status;
    EFI_PCI_IO_PROTOCOL              *PciIO;

    IDE_BLK_IO_DEV                   *IdeBlockIoDev = NULL;
    VOID                             *IdeControllerInterface = NULL ;
    IDE_BUS_INIT_PROTOCOL            *IdeBusInitInterface;
    IDE_BUS_PROTOCOL                 *IdeBusInterface;
    UINT8 Enumeration_Process = ENUMERATE_ALL;
    ATAPI_DEVICE_PATH                *AtapiRemainingDevicePath = (ATAPI_DEVICE_PATH*)RemainingDevicePath;

    UINT8 Start_Channel = PRIMARY_CHANNEL;
    UINT8 End_Channel   = SECONDARY_CHANNEL;
    UINT8 Start_Device  = MASTER_DRIVE;
    UINT8 End_Device    = SLAVE_DRIVE;

    INT8 TotalDevice = 0;
    INT8 Current_Channel;
    INT8 Current_Device;
    UINT16                           SecurityStatus = 0;

#ifdef Debug_Level_1
    EfiDebugPrint( -1, "IdeBusStart Entry\n" );
#endif

    PROGRESS_CODE( DXE_IDE_BEGIN );

    //
    //Open IDE_CONTROLLER_PROTOCOL. If success or Already opened, It is OK to proceed.
    //
    Status = pBS->OpenProtocol( Controller,
                                &(gPlatformIdeProtocol->gIdeControllerProtocolGuid),
                                (VOID**)&IdeControllerInterface,
                                This->DriverBindingHandle,
                                Controller,
                                EFI_OPEN_PROTOCOL_BY_DRIVER );

    if  ( !(Status == EFI_SUCCESS || Status == EFI_ALREADY_STARTED)) {
        return EFI_DEVICE_ERROR;
    }

    //
    //Get the PciIO interface
    //
    Status = pBS->OpenProtocol( Controller,
                                &gEfiPciIoProtocolGuid,
                                (VOID**)&PciIO,
                                This->DriverBindingHandle,
                                Controller,
                                EFI_OPEN_PROTOCOL_GET_PROTOCOL );


    //
    //Check if IDE_BUS_INIT_PROTOCOL installed.
    //
    Status = pBS->OpenProtocol( Controller,
                                &gEfiIdeBusInitProtocolGuid,
                                (VOID**)&IdeBusInitInterface,
                                This->DriverBindingHandle,
                                Controller,
                                EFI_OPEN_PROTOCOL_BY_DRIVER );


    if  ( !(Status == EFI_SUCCESS || Status == EFI_ALREADY_STARTED)) {
        Status = pBS->AllocatePool( EfiBootServicesData,
                                    sizeof(IDE_BUS_INIT_PROTOCOL),
                                    (VOID**)&IdeBusInitInterface
                                    );

        if ( EFI_ERROR( Status )) {
            return EFI_OUT_OF_RESOURCES; 
        }
        Status = InstallBusInitProtocol( Controller, IdeBusInitInterface, IdeControllerInterface );

        if ( EFI_ERROR( Status )) {
            if ( Status == EFI_OUT_OF_RESOURCES) {
                return EFI_OUT_OF_RESOURCES;
            } else {
                return EFI_DEVICE_ERROR;
            }
        }
    }

    //
    //	Check if AtapiRemainingDevicePath is valid or not
    //
    if ( !(AtapiRemainingDevicePath == NULL)) {

        //
        // RemainingDevicePath is not NULL and begins with the End of Device Path node, 
        // then the driver must not enumerate any of the children of Controller nor create any child device handle. 
        // Only the controller initialization should be performed. UEFI specification V 2.3.1, P. 10.1
        //
        if(isEndNode(RemainingDevicePath)) {
            return EFI_SUCCESS;
        }

        //
        // Check if the AtapiRemainingDevicePath is valid 8.3.4.1
        //
        if ( AtapiRemainingDevicePath->Header.Type != MESSAGING_DEVICE_PATH
             || AtapiRemainingDevicePath->Header.SubType != MSG_ATAPI_DP
             && NODE_LENGTH( &AtapiRemainingDevicePath->Header ) != ATAPI_DEVICE_PATH_LENGTH ) {
#ifdef Debug_Level_3
            EfiDebugPrint( -1, "AtapiRemainingDevicePath not Valid\n" );
#endif
            return EFI_DEVICE_ERROR;
        }

        if ( AtapiRemainingDevicePath->PrimarySecondary == PRIMARY_CHANNEL
             && AtapiRemainingDevicePath->SlaveMaster == MASTER_DRIVE ) {
            Enumeration_Process = ENUMERATE_PRIMARY_MASTER;
        }

        if ( AtapiRemainingDevicePath->PrimarySecondary == PRIMARY_CHANNEL
             && AtapiRemainingDevicePath->SlaveMaster == SLAVE_DRIVE ) {
            Enumeration_Process = ENUMERATE_PRIMARY_SLAVE;
        }

        if ( AtapiRemainingDevicePath->PrimarySecondary == SECONDARY_CHANNEL
             && AtapiRemainingDevicePath->SlaveMaster == MASTER_DRIVE ) {
            Enumeration_Process = ENUMERATE_SECONDARY_MASTER;
        }

        if ( AtapiRemainingDevicePath->PrimarySecondary == SECONDARY_CHANNEL
             && AtapiRemainingDevicePath->SlaveMaster == SLAVE_DRIVE ) {
            Enumeration_Process = ENUMERATE_SECONDARY_SLAVE;
        }

        switch ( Enumeration_Process )
        {
        case ENUMERATE_PRIMARY_MASTER:
            Start_Channel = PRIMARY_CHANNEL;
            End_Channel   = PRIMARY_CHANNEL;
            Start_Device  = MASTER_DRIVE;
            End_Device    = MASTER_DRIVE;
            break;
        case ENUMERATE_PRIMARY_SLAVE:
            Start_Channel = PRIMARY_CHANNEL;
            End_Channel   = PRIMARY_CHANNEL;
            Start_Device  = SLAVE_DRIVE;
            End_Device    = SLAVE_DRIVE;
            break;
        case ENUMERATE_SECONDARY_MASTER:
            Start_Channel = SECONDARY_CHANNEL;
            End_Channel   = SECONDARY_CHANNEL;
            Start_Device  = MASTER_DRIVE;
            End_Device    = MASTER_DRIVE;
            break;
        case ENUMERATE_SECONDARY_SLAVE:
            Start_Channel = SECONDARY_CHANNEL;
            End_Channel   = SECONDARY_CHANNEL;
            Start_Device  = SLAVE_DRIVE;
            End_Device    = SLAVE_DRIVE;
            break;
        default:
            break;
        }
    }


#ifdef Debug_Level_3
            EfiDebugPrint( -1, "Enumerate = %x\n", Enumeration_Process );
#endif

    //---------------------------------------------------------------------------------------------------------
    //	Device Detection Begins
    //---------------------------------------------------------------------------------------------------------
    PROGRESS_CODE( DXE_IDE_DETECT );

    for ( Current_Channel = Start_Channel; Current_Channel <= End_Channel; Current_Channel++ )
    {

        if ( gPlatformIdeProtocol->EfiIdeProtocol ) {
            ( (EFI_IDE_CONTROLLER_INIT_PROTOCOL*)IdeControllerInterface )->NotifyPhase( (EFI_IDE_CONTROLLER_INIT_PROTOCOL*)IdeControllerInterface, EfiIdeBeforeChannelEnumeration, Current_Channel );
        }
        //
        // Calculate the Number of Devices to be detected in single Channel 
        //
        TotalDevice = ( End_Device - Start_Device ) + 1;

        if ( gPlatformIdeProtocol->MasterSlaveEnumeration ) {
            Current_Device = Start_Device;
        } else {
            Current_Device = End_Device;
        }

        while ( TotalDevice ) 
        {
            //
            // Check whether the given device is disabled by USER OR already processed
            //
            if ( IdeBusInitInterface->IdeBusInitData[Current_Channel][Current_Device] == DEVICE_DISABLED
                 || IdeBusInitInterface->IdeBusInitData[Current_Channel][Current_Device] == DEVICE_DETECTED_SUCCESSFULLY
                 || IdeBusInitInterface->IdeBusInitData[Current_Channel][Current_Device] == DEVICE_CONFIGURED_SUCCESSFULLY
                 || IdeBusInitInterface->IdeBusInitData[Current_Channel][Current_Device] == DEVICE_DETECTION_FAILED
                 || IdeBusInitInterface->IdeBusInitData[Current_Channel][Current_Device] == DEVICE_REMOVED ) {

                if ( gPlatformIdeProtocol->MasterSlaveEnumeration ) {
                    Current_Device++;
                } else {
                    Current_Device--;
                }
                TotalDevice--;
                continue;
            }

            //
            // Allocate memory for IDE_BUS_PROTOCOL
            //
            if ( gPlatformIdeProtocol->EfiIdeProtocol ) {
                IdeBlockIoDev = MallocZ( sizeof(IDE_BLK_IO_DEV));

                if ( !IdeBlockIoDev ) {
                    return EFI_OUT_OF_RESOURCES;
                }
                IdeBlockIoDev->Signature = IDE_BLK_IO_DEV_SIGNATURE;
                IdeBusInterface          = (IDE_BUS_PROTOCOL*)&(IdeBlockIoDev->BlkIo);
            } else {
                IdeBusInterface = MallocZ( sizeof(IDE_BUS_PROTOCOL));

                if ( !IdeBusInterface ) {
                    return EFI_OUT_OF_RESOURCES;
                }
            }

            //
            // Initialize the fields
            //

            if ( gPlatformIdeProtocol->EfiIdeProtocol ) { 
                IdeBusInterface->EfiIdeControllerInterface =(EFI_IDE_CONTROLLER_INIT_PROTOCOL*) IdeControllerInterface;
                IdeBusInterface->IdeControllerInterfaceHandle = Controller;
            } else {
                IdeBusInterface->IdeControllerInterface =(IDE_CONTROLLER_PROTOCOL*) IdeControllerInterface;
            }
            IdeBusInterface->IdeBusInitInterface  = IdeBusInitInterface;
            IdeBusInterface->PciIO                = PciIO;
            IdeBusInterface->IdeDevice.PciIO      = PciIO;
            IdeBusInterface->IdeDevice.Channel    = Current_Channel;
            IdeBusInterface->IdeDevice.Device     = Current_Device;
            IdeBusInterface->AtaReadWritePio      = AtaReadWritePio;
            IdeBusInterface->AtaPioDataIn         = AtaPioDataIn;
            IdeBusInterface->AtaPioDataOut        = AtaPioDataOut;
            IdeBusInterface->IdeNonDataCommand    = IdeNonDataCommandExp;
            IdeBusInterface->WaitForCmdCompletion = WaitForCmdCompletion;
            IdeBusInterface->GeneralAtapiCommandAndData = GeneralAtapiCommandAndData;
            Status = UpdateBaseAddress( IdeBusInterface );

            if ( Status == EFI_SUCCESS ) {
                Status = DetectIdeDevice( IdeBusInterface );
            }

            if ( EFI_ERROR( Status ) ) {
                //
                // Update IdeBusInitInterface
                //
                IdeBusInitInterface->IdeBusInitData[Current_Channel][Current_Device] = DEVICE_DETECTION_FAILED;
                if ( gPlatformIdeProtocol->EfiIdeProtocol )
                    pBS->FreePool( IdeBlockIoDev );
                else
                    pBS->FreePool( IdeBusInterface );
 
                if ( gPlatformIdeProtocol->MasterSlaveEnumeration ) {
                    Current_Device++;
                } else {
                    Current_Device--;
                }
                TotalDevice--;
                continue;
            } else {
                IdeBusInitInterface->IdeBusInitData[Current_Channel][Current_Device]  = DEVICE_DETECTED_SUCCESSFULLY;
                IdeBusInitInterface->pIdeBusProtocol[Current_Channel][Current_Device] = IdeBusInterface; // Save the Pointer
            }

            if ( gPlatformIdeProtocol->MasterSlaveEnumeration ) {
                Current_Device++;
            } else {
                Current_Device--;
            }
            TotalDevice--;
        }                                                               // Loop for Master/Slave
    }                                                                   // Loop for Primary/Secondary

    //---------------------------------------------------------------------------------------------------------
    //	Device Detection Ends
    //---------------------------------------------------------------------------------------------------------
    //	Configuration Starts
    //---------------------------------------------------------------------------------------------------------
    PROGRESS_CODE( DXE_IDE_ENABLE );

    for ( Current_Channel = Start_Channel; Current_Channel <= End_Channel; Current_Channel++ )
    {
        for ( Current_Device = Start_Device; Current_Device <= End_Device; Current_Device++ )
        {

            //  
            //Check whether the given device is detected successfully
            //
            if ( IdeBusInitInterface->IdeBusInitData[Current_Channel][Current_Device] == DEVICE_DETECTED_SUCCESSFULLY ) {
                IdeBusInterface = IdeBusInitInterface->pIdeBusProtocol[Current_Channel][Current_Device];

                Status = ConfigureIdeDeviceAndController( IdeBusInterface, IdeControllerInterface, IdeBusInitInterface );

                if ( EFI_ERROR( Status )) {
                    ERROR_CODE( DXE_IDE_DEVICE_FAILURE, EFI_ERROR_MAJOR );

                    if ( gPlatformIdeProtocol->EfiIdeProtocol )
                        pBS->FreePool( IdeBlockIoDev );
                    else
                        pBS->FreePool( IdeBusInterface );

                    IdeBusInitInterface->pIdeBusProtocol[Current_Channel][Current_Device] = NULL;
                    continue;
                }

                //
                //Device has been successfully detected and configured.
                //

                //
                //Create the Devicepath
                //  
                Status = CreateIdeDevicePath( This, Controller, IdeBusInitInterface, IdeBusInterface, RemainingDevicePath, Current_Channel, Current_Device );

                if ( EFI_ERROR( Status )) {
                    if ( gPlatformIdeProtocol->EfiIdeProtocol )
                        pBS->FreePool( IdeBlockIoDev );
                    else
                        pBS->FreePool( IdeBusInterface );
                    continue;
                }

                //
                //Initialize Block_IO Protocol
                //
                Status = InitIdeBlockIO( IdeBusInterface );

                if ( EFI_ERROR( Status )) {
                    if ( gPlatformIdeProtocol->EfiIdeProtocol )
                        pBS->FreePool( IdeBlockIoDev );
                    else
                        pBS->FreePool( IdeBusInterface );
                    continue;
                }

                //
                //Initialize IDE EFI_DISK_INFO_PROTOCOL
                //
                Status = InitIdeDiskInfo( IdeBusInterface );

                if ( EFI_ERROR( Status )) {
                    if ( gPlatformIdeProtocol->EfiIdeProtocol )
                        pBS->FreePool( IdeBlockIoDev );
                    else
                        pBS->FreePool( IdeBusInterface );
                    continue;
                }

                //
                //Install Devicepath
                //
                Status = pBS->InstallMultipleProtocolInterfaces(
                                            &(IdeBusInterface->IdeDeviceHandle),
                                            &gDevicePathProtocolGuid, IdeBusInterface->DevicePathProtocol,
                                            NULL );

                if ( EFI_ERROR( Status )) {
                    IdeBusInitInterface->IdeBusInitData[Current_Channel][Current_Device] = DEVICE_DETECTION_FAILED;
                    if ( gPlatformIdeProtocol->EfiIdeProtocol )
                        pBS->FreePool( IdeBlockIoDev );
                    else
                        pBS->FreePool( IdeBusInterface );
                    continue;
                }

                //
                //Open IdeControllerProtocol
                //
                Status = pBS->OpenProtocol( Controller,
                                            &(gPlatformIdeProtocol->gIdeControllerProtocolGuid),
                                            (VOID**)&IdeControllerInterface,
                                            This->DriverBindingHandle,
                                            IdeBusInterface->IdeDeviceHandle,
                                            EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER );


                //
                //Install other optional Protocols - Hdd Security
                //
                Status = pBS->LocateProtocol(
                                &gHddSecurityInitProtocolGuid,
                                 NULL,
                                 &HddSecurityInitProtocol
                                );

                if ( !EFI_ERROR( Status )) {
                    if ( HddSecurityInitProtocol != NULL ) {
                        HddSecurityInitProtocol->InstallSecurityInterface( IdeBusInterface, FALSE );
                    }
                } else {
                    //
                    // If Security Feature support is not enabled, always freeze lock the security feature
                    //
                    if ( IdeBusInterface->IdeDevice.IdentifyData.Command_Set_Supported_82 & 0x2 ) {
                        Status = IdeNonDataCommand( IdeBusInterface, 0, 0,
                                                    0, 0, 0,
                                                    IdeBusInterface->IdeDevice.Device << 4,
                                                    SECURITY_FREEZE_LOCK );
                        //
                        // if Device Configuration Overlay feature set supported then issue the
                        // Dev config Free lock command.
                        //
                        if ( IdeBusInterface->IdeDevice.IdentifyData.Command_Set_Supported_83 & 0x800 ) {
                            Status = IdeNonDataCommand( IdeBusInterface, DEV_CONFIG_FREEZE_LOCK_FEATURES, 0,
                                                        0, 0, 0,
                                                        IdeBusInterface->IdeDevice.Device << 4,
                                                        DEV_CONFIG_FREEZE_LOCK );
                        }
                        // Update the Identify device buffer
                        GetIdentifyData( IdeBusInterface, &(IdeBusInterface->IdeDevice));
                    }
                }

                //
                // Install other optional Protocols - OpalSecurity
                //

                Status = pBS->LocateProtocol (
                                    &gOpalSecInitProtocolGuid,
                                    NULL,
                                    &OpalSecInitProtocol
                                );

                if(!EFI_ERROR(Status)) {
                    if(OpalSecInitProtocol != NULL) {
                        OpalSecInitProtocol->InstallOpalSecurityInterface(IdeBusInterface, FALSE);
                    }
                }

                //
                //Install other optional Protocols - SMART
                //
                Status = pBS->LocateProtocol(
                                    &gHddSmartInitProtocolGuid,
                                    NULL,
                                    &HddSmartInitProtocol
                                    );

                if ( !EFI_ERROR( Status )) {
                    if ( HddSmartInitProtocol != NULL ) {
                        HddSmartInitProtocol->InitSMARTSupport( IdeBusInterface, FALSE );
                        //
                        //Get the updated IdentifyData
                        //
                        GetIdentifyData( IdeBusInterface, &(IdeBusInterface->IdeDevice));
                        if ( HddSmartInitProtocol->SmartDiagonasticFlag ) {
                            HddSmartInitProtocol->InstallSMARTInterface( IdeBusInterface, FALSE );
                        }
                    }
                }

                if ( gPlatformIdeProtocol->IdePwrManagementInterfaceSupport ) {
                    InstallIDEPowerMgmtInterface( IdeBusInterface );
                }

                if ( gPlatformIdeProtocol->HostProtectedAreaSupport ) {
                    InstallHPAInterface( IdeBusInterface );
                }

#ifdef Debug_Level_3
                PrintIdeDeviceInfo( IdeBusInterface );
#endif
            }                                               // DEVICE_CONFIGURED_SUCCESSFULLY

            //Before installing BlockIO and DiskInfo protocol, check whether the device has been
            //password protected. If yes, BlockIO and DiskInfo will not be installed.
            IdeBusInterface = IdeBusInitInterface->pIdeBusProtocol[Current_Channel][Current_Device];

            if ( IdeBusInitInterface->IdeBusInitData[Current_Channel][Current_Device] == DEVICE_CONFIGURED_SUCCESSFULLY ) {
                //
                //Check BlockIO has been installed or not.
                //
                Status = pBS->OpenProtocol( IdeBusInterface->IdeDeviceHandle,
                                            &gEfiBlockIoProtocolGuid,
                                            NULL,
                                            This->DriverBindingHandle,
                                            IdeBusInterface->IdeDeviceHandle,
                                            EFI_OPEN_PROTOCOL_TEST_PROTOCOL );

                if ( EFI_ERROR( Status )) {
                    //
                    //BLOCKIO not installed and device has been configured successfully
                    //  
                    Status = EFI_UNSUPPORTED;
                    Status = pBS->InstallMultipleProtocolInterfaces(
                                        &(IdeBusInterface->IdeDeviceHandle),
                                        &gEfiBlockIoProtocolGuid, (EFI_BLOCK_IO_PROTOCOL*)(IdeBusInterface->IdeBlkIo),
                                        &gEfiDiskInfoProtocolGuid, (EFI_DISK_INFO_PROTOCOL*)(IdeBusInterface->IdeDiskInfo),
                                        NULL );
                }                                                       // If BlockIO not Installed
            }                                                           // End of installing BlockIO and DiskInfo
        }                                                               // Loop for Master/Slave
    }                                                                   // Loop for Primary/Secondary

    //---------------------------------------------------------------------------------------------------------
    //	Configuration Ends
    //---------------------------------------------------------------------------------------------------------

    // Check HP Support and Ide Controller protocol to create an HP event
    if ( gPlatformIdeProtocol->IdeHPSupport == 1 && gPlatformIdeProtocol->EfiIdeProtocol == 0 ) {

        // 
        // Check whether already HP Event has been created and also HP is supported
        //  
        if ( IdeBusInitInterface->HPEvent == NULL && IdeBusInitInterface->HPMask ) {
            //
            // Create and Event
            //
            Status = pBS->CreateEvent( EFI_EVENT_TIMER | EFI_EVENT_NOTIFY_SIGNAL,
                                   TPL_CALLBACK,
                                   IdeHPTimer,
                                   IdeBusInitInterface,
                                   &(IdeBusInitInterface->HPEvent));

            if ( Status == EFI_SUCCESS ) {
                pBS->SetTimer( IdeBusInitInterface->HPEvent, TimerPeriodic, 20000000 ); // 2sec
            }
        }
    }

    Status = pBS->LocateProtocol (
                                &gAtaPassThruInitProtocolGuid,
                                NULL,
                                &AtaPassThruInitProtocol
                        );

    if(!EFI_ERROR(Status)) {
        if(AtaPassThruInitProtocol != NULL) {
            AtaPassThruInitProtocol->InstallAtaPassThru(Controller, FALSE);
        }
    }

    // SCSIPassThruAtapi install
    Status = pBS->LocateProtocol (
                                &gScsiPassThruAtapiInitProtocolGuid,
                                NULL,
                                &gScsiPassThruAtapiInitProtocol
                        );

    if(!EFI_ERROR(Status)) {
        if(gScsiPassThruAtapiInitProtocol != NULL) {
            gScsiPassThruAtapiInitProtocol->InstallScsiPassThruAtapi(Controller, FALSE);
        }
    }

    //
    // This will notify AMITSE to invoke the HDD password Screen
    //
    Status = pBS->InstallProtocolInterface(
        &Controller,
        &gHddSecurityEndProtocolGuid, EFI_NATIVE_INTERFACE, NULL
        );

#ifdef Debug_Level_1
    EfiDebugPrint( -1, "IdeBusStart Exit Success\n" );
#endif

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	IdeBusStop
//
// Description:	Uninstall all devices installed in start procedure.
//
// Input:
//	IN EFI_DRIVER_BINDING_PROTOCOL    *This,
//	IN EFI_HANDLE                     Controller,
//	IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
//
// Output:
//	EFI_STATUS
//
// Modified:
//
// Referrals: OpenProtocol CloseProtocol
//
// Notes:
//  Here is the control flow of this function:
// 1.  Check whether "gEfiIdeBusInitProtocolGuid" is installed on this controller. If not exit with error.
// 2.  If "NumberOfChildren" is zero, check wether all child devices have been stopped. If not exit with error.
//                      if all child devices have been stopped, then close "gEfiIdeControllerProtocolGuid" and "gEfiIdeBusInitProtocolGuid",
//		        uninstall "gEfiIdeBusInitProtocolGuid" and then exit with success.
// 3.  If "NumberOfChildren" is non-zero,	close "gEfiIdeControllerProtocolGuid" opened by the child device in start function.
//			uninstall all protocols installed on this child device in start function,
//			free up all resources allocated in start function. Repeat step	3 for all child devices and	return success at the end.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS IdeBusStop(
    IN EFI_DRIVER_BINDING_PROTOCOL *This,
    IN EFI_HANDLE                  Controller,
    IN UINTN                       NumberOfChildren,
    IN EFI_HANDLE                  *ChildHandleBuffer )
{
    IDE_BUS_INIT_PROTOCOL            *IdeBusInitInterface;
    IDE_BUS_PROTOCOL                 *IdeBusInterface = NULL;
    EFI_STATUS                       Status;
    IDE_BLK_IO_DEV                   *IdeBlockIoDev = NULL;
    VOID                             *IdeControllerInterface = NULL ;
 
    UINT8 Current_Channel                 = 0xff;
    UINT8 Current_Device                  = 0xff;
    UINT8 Index                           = 0;
    BOOLEAN                          Flag = TRUE;
    EFI_DEVICE_PATH_PROTOCOL         *DevicePath;

    //
    //Check if IDE_BUS_INIT_PROTOCOL is installed on the Controller.
    //
    Status = pBS->OpenProtocol( Controller,
                                &gEfiIdeBusInitProtocolGuid,
                                (VOID**)&IdeBusInitInterface,
                                This->DriverBindingHandle,
                                Controller,
                                EFI_OPEN_PROTOCOL_GET_PROTOCOL );

    if ( EFI_ERROR( Status )) {
        return EFI_DEVICE_ERROR;
    }

    //
    //Check if ChildHandleBuffer is valid
    //
    if ( NumberOfChildren ) {
        while ( NumberOfChildren )
        {
            Status = pBS->OpenProtocol(
                ChildHandleBuffer[Index],
                &gDevicePathProtocolGuid,
                (VOID**)&DevicePath,
                This->DriverBindingHandle,
                Controller,
                EFI_OPEN_PROTOCOL_GET_PROTOCOL );

            //Lookout for ATAPI device path
            //ACPI_DEVICE path, PCI Device path and then ATAPI device path will be the sequence
            do
            {
                if ((DevicePath->Type == MESSAGING_DEVICE_PATH) && (DevicePath->SubType == MSG_ATAPI_DP)) {
                    Current_Channel = ((ATAPI_DEVICE_PATH*)DevicePath)->PrimarySecondary;
                    Current_Device  = ((ATAPI_DEVICE_PATH*)DevicePath)->SlaveMaster;
                    break;
                } else {
                    DevicePath = NEXT_NODE( DevicePath );
                }
            } while ( DevicePath->Type != END_DEVICE_PATH );

            if ( Current_Channel == 0xff || Current_Device == 0xff ) {
                return EFI_DEVICE_ERROR;
            }

            //
            //Get the pointer to IDE_BUS_PROTOCOL
            //
            IdeBusInterface = IdeBusInitInterface->pIdeBusProtocol[Current_Channel][Current_Device];

            //
            //Close all the protocols opened by this Child Device
            //
            pBS->CloseProtocol(
                        Controller,
                        &(gPlatformIdeProtocol->gIdeControllerProtocolGuid),
                        This->DriverBindingHandle,
                        ChildHandleBuffer[Index] );

            //Before uninstalling BLOCKIO check whether it is installed or not
            Status = pBS->OpenProtocol( ChildHandleBuffer[Index],
                                        &gEfiBlockIoProtocolGuid,
                                        NULL,
                                        This->DriverBindingHandle,
                                        ChildHandleBuffer[Index],
                                        EFI_OPEN_PROTOCOL_TEST_PROTOCOL );

            if ( Status == EFI_SUCCESS ) {
                Status = pBS->UninstallMultipleProtocolInterfaces(
                                    ChildHandleBuffer[Index],
                                    &gEfiBlockIoProtocolGuid, (EFI_BLOCK_IO_PROTOCOL*)(IdeBusInterface->IdeBlkIo),
                                    &gEfiDiskInfoProtocolGuid, (EFI_DISK_INFO_PROTOCOL*)(IdeBusInterface->IdeDiskInfo),
                                    NULL );
            }

            Status = pBS->    UninstallMultipleProtocolInterfaces(
                ChildHandleBuffer[Index],
                &gDevicePathProtocolGuid, IdeBusInterface->DevicePathProtocol,
                NULL );

            if ( EFI_ERROR( Status )) {
                pBS->OpenProtocol( Controller,
                                   &(gPlatformIdeProtocol->gIdeControllerProtocolGuid),
                                   (VOID**)&IdeControllerInterface,
                                   This->DriverBindingHandle,
                                   ChildHandleBuffer[Index],
                                   EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER );

                return EFI_DEVICE_ERROR;
            }  else {
                //
                //Now free up all resources allocated.
                //
                if ( IdeBusInterface->IdeDevice.AtapiDevice != NULL ) {
                    pBS->FreePool( IdeBusInterface->IdeDevice.AtapiDevice->PacketBuffer );
                    pBS->FreePool( IdeBusInterface->IdeDevice.AtapiDevice->InquiryData );
                    pBS->FreePool( IdeBusInterface->IdeDevice.AtapiDevice );
                }

                //
                //Freeup resources allocated for component names
                //
                if ( IdeBusInterface->IdeDevice.UDeviceName != NULL ) {
                    pBS->FreePool( IdeBusInterface->IdeDevice.UDeviceName->Language );
                    pBS->FreePool( IdeBusInterface->IdeDevice.UDeviceName->UnicodeString );
                    pBS->FreePool( IdeBusInterface->IdeDevice.UDeviceName );
                }

                // Uninstall optional protocols

                //
                //Before uninstalling HDD security check whether it is installed or not
                //
                Status = pBS->OpenProtocol( ChildHandleBuffer[Index],
                                            &gHddSecurityInitProtocolGuid,
                                            (VOID**)&HddSecurityInitProtocol,
                                            This->DriverBindingHandle,
                                            ChildHandleBuffer[Index],
                                            EFI_OPEN_PROTOCOL_TEST_PROTOCOL );

                if ( !EFI_ERROR( Status )) {
                    if ( HddSecurityInitProtocol != NULL ) {
                        HddSecurityInitProtocol->StopSecurityModeSupport( IdeBusInterface, FALSE );
                    }
                }

                //
                //Before uninstalling Hdd Smart check whether it is installed or not
                //
                Status = pBS->OpenProtocol( ChildHandleBuffer[Index],
                                            &gHddSmartInitProtocolGuid,
                                            (VOID**)&HddSmartInitProtocol,
                                            This->DriverBindingHandle,
                                            ChildHandleBuffer[Index],
                                            EFI_OPEN_PROTOCOL_TEST_PROTOCOL );

                if ( !EFI_ERROR( Status )) {
                    if ( HddSmartInitProtocol != NULL ) {
                        if ( HddSmartInitProtocol->SmartDiagonasticFlag ) {
                            HddSmartInitProtocol->UnInstallSMARTInterface( IdeBusInterface, FALSE );
                        }
                    }
                }

                //
                //Before uninstalling OPAL security Interface check whether it is installed or not.
                //
                Status = pBS->OpenProtocol( ChildHandleBuffer[Index],
                                            &gOpalSecInitProtocolGuid,
                                            (VOID**)&OpalSecInitProtocol,
                                            This->DriverBindingHandle,
                                            ChildHandleBuffer[Index],
                                            EFI_OPEN_PROTOCOL_TEST_PROTOCOL );

                if ( !EFI_ERROR( Status )) {
                    if ( OpalSecInitProtocol != NULL ) {
                        OpalSecInitProtocol->UnInstallOpalSecurityInterface( IdeBusInterface, FALSE );
                    }
                }

	            if ( gPlatformIdeProtocol->IdePwrManagementInterfaceSupport ) {
	                StopIDEPowerMgmtInterface( IdeBusInterface );
	            }

	            if ( gPlatformIdeProtocol->HostProtectedAreaSupport ) {
	                StopHPAInterface( IdeBusInterface );
	            }

	            if ( gPlatformIdeProtocol->EfiIdeProtocol ) {
	                IdeBlockIoDev = IDE_BLOCK_IO_DEV_FROM_THIS( &(IdeBusInterface->IdeBlkIo));
                }
                pBS->FreePool( IdeBusInterface->IdeBlkIo->BlkIo.Media );
                pBS->FreePool( IdeBusInterface->IdeBlkIo );
                pBS->FreePool( IdeBusInterface->IdeDiskInfo );
                Current_Channel = IdeBusInterface->IdeDevice.Channel;
                Current_Device  = IdeBusInterface->IdeDevice.Device;
                IdeBusInitInterface->IdeBusInitData[Current_Channel][Current_Device] = DEVICE_IN_RESET_STATE;
                pBS->FreePool( IdeBusInterface->DevicePathProtocol );

	            if ( gPlatformIdeProtocol->EfiIdeProtocol )
	                pBS->FreePool( IdeBlockIoDev );
	            else
	                pBS->FreePool( IdeBusInterface );
            }
            NumberOfChildren--;
            Index++;
        }

        return EFI_SUCCESS;
    } else {
        //   
        //Check if IDE_BUS_INIT_PROTOCOL can be removed
        //
        for ( Current_Channel = PRIMARY_CHANNEL; Current_Channel <= SECONDARY_CHANNEL; Current_Channel++ )
        {
            for ( Current_Device = MASTER_DRIVE; Current_Device <= SLAVE_DRIVE; Current_Device++ )
            {
                if ( IdeBusInitInterface->IdeBusInitData[Current_Channel][Current_Device] == DEVICE_CONFIGURED_SUCCESSFULLY ) {
                    Flag = FALSE;
                }
            }
        }

        //
        // Can't uninstall IDE_BUS_INIT_PROTOCOL if any one of the IDE devices are in "CONFIGURED" state.
        //
        if ( Flag == TRUE ) {
            if ( gPlatformIdeProtocol->IdeHPSupport ) {

	            //
	            // Check whether already HP Event has been created and also HP is supported
	            //    
	            if ( IdeBusInitInterface->HPEvent != NULL ) {
	                pBS->CloseEvent( IdeBusInitInterface->HPEvent );
                }
            }
            //    
            //Close all the protocols opened in Start Function
            //
            Status = pBS->CloseProtocol( Controller,
                                         &(gPlatformIdeProtocol->gIdeControllerProtocolGuid),
                                         This->DriverBindingHandle,
                                         Controller );
            //
            // AtaPass Thru uninstall
            //
            Status = pBS->LocateProtocol (
                                &gAtaPassThruInitProtocolGuid,
                                NULL,
                                &AtaPassThruInitProtocol
                        );

            if(!EFI_ERROR(Status)) {
                 if(AtaPassThruInitProtocol != NULL) {
                     AtaPassThruInitProtocol->StopAtaPassThruSupport(Controller, FALSE);
                 }
             }
            //
            // ScsiPassThruAtapi uninstall
            //
            Status = pBS->LocateProtocol (
                                &gScsiPassThruAtapiInitProtocolGuid,
                                NULL,
                                &gScsiPassThruAtapiInitProtocol);

             if(!EFI_ERROR(Status)) {
                 if(gScsiPassThruAtapiInitProtocol != NULL) {
                     gScsiPassThruAtapiInitProtocol->StopScsiPassThruAtapiSupport(Controller, FALSE);
                 }
             }


            Status = pBS->CloseProtocol( Controller,
                                         &gEfiIdeBusInitProtocolGuid,
                                         This->DriverBindingHandle,
                                         Controller );

            Status = pBS->UninstallProtocolInterface( Controller,
                                                      &gEfiIdeBusInitProtocolGuid,
                                                      IdeBusInitInterface );

            if ( EFI_ERROR( Status ))  {
                Status = pBS->OpenProtocol( Controller,
                                            &gEfiIdeBusInitProtocolGuid,
                                            (VOID**)&IdeBusInitInterface,
                                            This->DriverBindingHandle,
                                            Controller,
                                            EFI_OPEN_PROTOCOL_BY_DRIVER );

                Status = pBS->OpenProtocol( Controller,
                                            &(gPlatformIdeProtocol->gIdeControllerProtocolGuid),
                                            (VOID**)&IdeControllerInterface,
                                            This->DriverBindingHandle,
                                            Controller,
                                            EFI_OPEN_PROTOCOL_BY_DRIVER );

                return EFI_DEVICE_ERROR;
            }

	        if ( gPlatformIdeProtocol->EfiIdeProtocol )
	            pBS->FreePool( IdeBlockIoDev );
	        else
	            pBS->FreePool( IdeBusInterface );

            if ( gDescriptorBuffer != NULL ) {
                pBS->FreePool( gDescriptorBuffer );
            }
            gDescriptorBuffer = NULL;
            return EFI_SUCCESS;
        } else {
            return EFI_DEVICE_ERROR;
        }
    }
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	InstallBusInitProtocol
//
// Description:	Installs BUS Init Protocol on the IDE controller Handle
//
// Input:
//	IN EFI_HANDLE                     Controller,
//	IDE_BUS_INIT_PROTOCOL			*IdeBusInitInterface;
//	IDE_CONTROLLER_PROTOCOL			*IdeControllerInterface
//
// Output:
//	EFI_STATUS
//
// Modified:
//
// Referrals: AllocatePool, InstallProtocolInterface, IdeGetControllerInfo
//
// Notes:
//  Here is the control flow of this function:
//	1. Call "IdeGetControllerInfo", to get channel information from IdeController driver.
//  2. Install "gEfiIdeBusInitProtocolGuid" on the IDE controller.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS InstallBusInitProtocol(
    IN EFI_HANDLE                Controller,
    IN OUT IDE_BUS_INIT_PROTOCOL *IdeBusInitInterface,
    IN VOID *IdeControllerInterfaceIn
    )
{
    CONTROLLER_INFO *ControllerInfo;
    EFI_IDE_CONTROLLER_INIT_PROTOCOL    *EfiIdeControllerInterface = NULL ;
    IDE_CONTROLLER_PROTOCOL             *IdeControllerInterface = NULL ;
    EFI_STATUS      Status;

    //
    // Initialize IdeControllerInterface
    //
    if ( gPlatformIdeProtocol->EfiIdeProtocol )
        EfiIdeControllerInterface = ( EFI_IDE_CONTROLLER_INIT_PROTOCOL *) IdeControllerInterfaceIn;
    else
        IdeControllerInterface = ( IDE_CONTROLLER_PROTOCOL *) IdeControllerInterfaceIn;

    //
    //Initialize the default Values
    //
    ZeroMemory( IdeBusInitInterface, sizeof(IDE_BUS_INIT_PROTOCOL));

    Status = pBS->AllocatePool( EfiBootServicesData,
                                sizeof(CONTROLLER_INFO),
                                (VOID**)&ControllerInfo
                                );

    if ( EFI_ERROR( Status )) {
        return Status;
    }

    ZeroMemory( ControllerInfo, sizeof(CONTROLLER_INFO));

    if ( gPlatformIdeProtocol->EfiIdeProtocol ) {
        ControllerInfo->Flags = 0; // ACOUSTIC_SUPPORT_DISABLE

        if ( gPlatformIdeProtocol->SBIdeSupport ) {
            Status = pBS->LocateProtocol(&gIdeSetupProtocolguid, NULL, &gIdeSetupProtocol);

            if ( gPlatformIdeProtocol->AcousticManagementSupport ) {  

                if (!EFI_ERROR(Status)) {

                    if(gIdeSetupProtocol->AcousticPwrMgmt)
                        ControllerInfo->Flags |= ACOUSTIC_SUPPORT_ENABLE;
                    else
                        ControllerInfo->Flags &= ~ACOUSTIC_SUPPORT_ENABLE;
                    ControllerInfo->Acoustic_Management_Level   = gIdeSetupProtocol->AcousticLevel;
                } else {
                    ControllerInfo->Flags &= ~ACOUSTIC_SUPPORT_ENABLE ;
                    ControllerInfo->Acoustic_Management_Level   = ACOUSTIC_LEVEL_BYPASS;
                }
            } //End of ACOUSTIC_MANAGEMENT_SUPPORT   
        } //End of SBIDE_SUPPORT

        if ( gPlatformIdeProtocol->HddPowerLossInS3 ) {
            ControllerInfo->Flags |= S3_RESUME_UNLOCK_HDD_PASSWORD;
        }

        ControllerInfo->PrimaryChannel        = PRIMARY_CHANNEL_ENABLE;
        ControllerInfo->PrimaryMasterDevice   = PRIMARY_MASTER_DRIVE_ENABLE;
        ControllerInfo->PrimarySlaveDevice    = PRIMARY_SLAVE_DRIVE_ENABLE;
        ControllerInfo->SecondaryChannel      = SECONDARY_CHANNEL_ENABLE;
        ControllerInfo->SecondaryMasterDevice = SECONDARY_MASTER_DRIVE_ENABLE;
        ControllerInfo->SecondarySlaveDevice  = SECONDARY_SLAVE_DRIVE_ENABLE;
        ControllerInfo->BusMasterEnable       = BUSMASTER_ENABLE;
        ControllerInfo->HPMask                = 0;           // Hot Plug Mask

    } else {
		IdeControllerInterface->IdeGetControllerInfo( Controller, ControllerInfo );
    }

    if ( ControllerInfo->PrimaryChannel == DEVICE_DISABLED ) {
        IdeBusInitInterface->IdeBusInitData[PRIMARY_CHANNEL][MASTER_DRIVE] = DEVICE_DISABLED;
        IdeBusInitInterface->IdeBusInitData[PRIMARY_CHANNEL][SLAVE_DRIVE]  = DEVICE_DISABLED;
    } else {
        IdeBusInitInterface->IdeBusInitData[PRIMARY_CHANNEL][MASTER_DRIVE] = ControllerInfo->PrimaryMasterDevice;
        IdeBusInitInterface->IdeBusInitData[PRIMARY_CHANNEL][SLAVE_DRIVE]  = ControllerInfo->PrimarySlaveDevice;
    }

    if ( ControllerInfo->SecondaryChannel == DEVICE_DISABLED ) {
        IdeBusInitInterface->IdeBusInitData[SECONDARY_CHANNEL][MASTER_DRIVE] = DEVICE_DISABLED;
        IdeBusInitInterface->IdeBusInitData[SECONDARY_CHANNEL][SLAVE_DRIVE]  = DEVICE_DISABLED;
    } else {
        IdeBusInitInterface->IdeBusInitData[SECONDARY_CHANNEL][MASTER_DRIVE] = ControllerInfo->SecondaryMasterDevice;
        IdeBusInitInterface->IdeBusInitData[SECONDARY_CHANNEL][SLAVE_DRIVE]  = ControllerInfo->SecondarySlaveDevice;
    }

    IdeBusInitInterface->BusMasterSelection        = ControllerInfo->BusMasterEnable;
    IdeBusInitInterface->HPMask                    = ControllerInfo->HPMask;
    if ( gPlatformIdeProtocol->EfiIdeProtocol )
        IdeBusInitInterface->EfiIdeControllerInterface = EfiIdeControllerInterface;
    else
        IdeBusInitInterface->IdeControllerInterface   	 = IdeControllerInterface;

    IdeBusInitInterface->Flags                     = ControllerInfo->Flags;
    IdeBusInitInterface->Acoustic_Management_Level = ControllerInfo->Acoustic_Management_Level;

    Status = pBS->FreePool( ControllerInfo );

    // Initialize PrevPortNum and PrevPortMultiplierPortNum for AtaPassThru to 0xFFFF

    IdeBusInitInterface->PrevPortNum = 0xffff;
    IdeBusInitInterface->PrevPortMultiplierPortNum = 0xffff;

    Status = pBS->InstallProtocolInterface(
        &Controller,
        &gEfiIdeBusInitProtocolGuid,
        EFI_NATIVE_INTERFACE,
        IdeBusInitInterface );

    if ((IdeBusInitInterface->BusMasterSelection) &&  gDescriptorBuffer == NULL ) {
        //Since the PRD table need to be aligned at 64KB to create maximum # of tables
        //allocate 128KB and use the 64KB aligned address,
        Status = pBS->AllocatePool( EfiBootServicesData,
                                    2 * 64 * 1024,
                                    (VOID**)&gDescriptorBuffer
                                    );

        if ( EFI_ERROR( Status )) {
            IdeBusInitInterface->BusMasterSelection = 0;
        }
    }

#ifdef Debug_Level_3
    EfiDebugPrint( -1, "Installed IDE_BUS_INIT_PROTOCOL\n" );
#endif

    return Status;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	ConfigureIdeDeviceAndController
//
// Description:	PIO and DMA mode programming both on the Controller as well as on the Device is done
//
// Input:
//	IDE_BUS_INIT_PROTOCOL			*IdeBusInitInterface
//	IDE_CONTROLLER_PROTOCOL			*IdeControllerInterface
//	IDE_BUS_INIT_PROTOCOL			*IdeBusInitInterface
//
// Output:
//	EFI_STATUS
//
// Modified:
//
// Referrals: ConfigureIdeDevice, GetIdentifyData
//
// Notes:
//  Here is the control flow of this function:
// 1. Get the Best PIO and DMA mode supported by the device from Identify Data
// 2. Set the PIO and DMA mode in the IDE controller.
// 3. Configure the IDE device with the PIO and DMA mode.
// 4. Update the Identify Data.
// 5. Based on the IDE device select the proper Read/Write commands.
// 6. Construct a unicode string for the IDE device.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ConfigureIdeDeviceAndController(
    IN IDE_BUS_PROTOCOL                 *IdeBusInterface,
    IN VOID              *IdeControllerInterfaceIn,
    IN IDE_BUS_INIT_PROTOCOL            *IdeBusInitInterface )
{
    EFI_STATUS              Status;
    UINT8                   Current_Channel = IdeBusInterface->IdeDevice.Channel;
    UINT8                   Current_Device  = IdeBusInterface->IdeDevice.Device;

    EFI_ATA_COLLECTIVE_MODE *SupportedModes = NULL;
    EFI_IDE_CONTROLLER_INIT_PROTOCOL       *EfiIdeControllerInterface = NULL ;
    IDE_CONTROLLER_PROTOCOL    *IdeControllerInterface = NULL ;


    if ( gPlatformIdeProtocol->EfiIdeProtocol )
        EfiIdeControllerInterface = (EFI_IDE_CONTROLLER_INIT_PROTOCOL*) IdeControllerInterfaceIn;
    else
        IdeControllerInterface = (IDE_CONTROLLER_PROTOCOL *) IdeControllerInterfaceIn;

    if ( gPlatformIdeProtocol->EfiIdeProtocol ) {
        GetIdentifyData( IdeBusInterface, &(IdeBusInterface->IdeDevice));
        Status = EfiIdeControllerInterface->SubmitData( EfiIdeControllerInterface, IdeBusInterface->IdeDevice.Channel,
                                                 IdeBusInterface->IdeDevice.Device, (EFI_IDENTIFY_DATA*)&(IdeBusInterface->IdeDevice.IdentifyData));

        if ( EFI_ERROR( Status )) {
            return Status;
        }

	    Status = EfiIdeControllerInterface->CalculateMode( EfiIdeControllerInterface, IdeBusInterface->IdeDevice.Channel,
                                                    IdeBusInterface->IdeDevice.Device, &SupportedModes );

    if ( EFI_ERROR( Status )) {
        return Status;
    }

	    Status = EfiIdeControllerInterface->SetTiming( EfiIdeControllerInterface, IdeBusInterface->IdeDevice.Channel,
                                                IdeBusInterface->IdeDevice.Device, SupportedModes );

        if ( EFI_ERROR( Status )) {
            return Status;
        }

	    IdeBusInterface->IdeDevice.PIOMode = 0xff;
	    IdeBusInterface->IdeDevice.SWDma   = 0xff;
	    IdeBusInterface->IdeDevice.MWDma   = 0xff;
	    IdeBusInterface->IdeDevice.UDma    = 0xff;

        if ( SupportedModes->PioMode.Valid ) {
            IdeBusInterface->IdeDevice.PIOMode = SupportedModes->PioMode.Mode;
        }

        if ( SupportedModes->SingleWordDmaMode.Valid ) {
            IdeBusInterface->IdeDevice.SWDma = SupportedModes->SingleWordDmaMode.Mode;
        }

        if ( SupportedModes->MultiWordDmaMode.Valid ) {
             IdeBusInterface->IdeDevice.MWDma = SupportedModes->MultiWordDmaMode.Mode;
        }

        if ( SupportedModes->UdmaMode.Valid ) {
            IdeBusInterface->IdeDevice.UDma = SupportedModes->UdmaMode.Mode;
        }

	    IdeBusInterface->IdeDevice.IORdy = ((EFI_IDENTIFY_DATA*)&(IdeBusInterface->IdeDevice.IdentifyData))->AtaData.capabilities & 0x800;

    } else {
        //    
        // Get the best PIO and DMA mode from the IDE device
        //    
	    IdeControllerInterface->GetbestPioDmaMode( &(IdeBusInterface->IdeDevice));

        //
        // Program PIO mode Timing in the controller
        //
	    IdeControllerInterface->IdeSetPioMode( &(IdeBusInterface->IdeDevice));

        // See if Bus Master has been enabled
	    IdeControllerInterface->IdeSetDmaMode( &(IdeBusInterface->IdeDevice)); 
    }

    //	Issue SET feature command to set the PIO and DMA mode
    Status = ConfigureIdeDevice( IdeBusInterface, IdeBusInitInterface );

    if ( EFI_ERROR( Status )) {
        return Status;
    } else {
        //
        //Get the updated IdentifyData
        //
        GetIdentifyData( IdeBusInterface, &(IdeBusInterface->IdeDevice));

        //
        //Check if UDMA and MWDMA are programmed successfully
        //    
        if ( IdeBusInterface->IdeDevice.UDma != 0xff ) {
            if ( !(ReturnMSBset((IdeBusInterface->IdeDevice.IdentifyData.UDMA_Mode_88 >> 8)) == IdeBusInterface->IdeDevice.UDma)) {
                IdeBusInterface->IdeDevice.UDma = ReturnMSBset((IdeBusInterface->IdeDevice.IdentifyData.UDMA_Mode_88 >> 8));
                if ( gPlatformIdeProtocol->EfiIdeProtocol ) {
                    SupportedModes->UdmaMode.Mode = IdeBusInterface->IdeDevice.UDma;
                    EfiIdeControllerInterface->SetTiming( EfiIdeControllerInterface, IdeBusInterface->IdeDevice.Channel,
                                                             IdeBusInterface->IdeDevice.Device, SupportedModes );
                } else {
                    IdeControllerInterface->IdeSetDmaMode( &(IdeBusInterface->IdeDevice));
                }
            }
        } else {
            if ( IdeBusInterface->IdeDevice.MWDma != 0xff ) {
                if ( !(ReturnMSBset( IdeBusInterface->IdeDevice.IdentifyData.MultiWord_DMA_63 >> 8 ) == IdeBusInterface->IdeDevice.MWDma)) {
                    IdeBusInterface->IdeDevice.MWDma = ReturnMSBset( (IdeBusInterface->IdeDevice.IdentifyData.MultiWord_DMA_63 >> 8));
                    if ( gPlatformIdeProtocol->EfiIdeProtocol ) {
                        SupportedModes->MultiWordDmaMode.Mode = IdeBusInterface->IdeDevice.MWDma;
                        EfiIdeControllerInterface-> SetTiming( EfiIdeControllerInterface, IdeBusInterface->IdeDevice.Channel,
                                                        IdeBusInterface->IdeDevice.Device, SupportedModes );
                    } else {
                        IdeControllerInterface->IdeSetDmaMode( &(IdeBusInterface->IdeDevice));
                    } 
                }
            }
        }

        //		Check for ATA
        if ( IdeBusInterface->IdeDevice.DeviceType == ATA ) {
            //			Update IDE Read/Write Command
            if  ((IdeBusInterface->IdeDevice.IdentifyData.Valid_Bits_59 & 0x100)
                 && (IdeBusInterface->IdeDevice.IdentifyData.Valid_Bits_59 & 0xff)) {  // Check if Multiple Read/Write
                if ( IdeBusInterface->IdeDevice.IdentifyData.Command_Set_Supported_83 & 0x400 ) {
                    //					48Bit LBA supported
                    IdeBusInterface->IdeDevice.ReadCommand  = READ_MULTIPLE_EXT;
                    IdeBusInterface->IdeDevice.WriteCommand = WRITE_MULTIPLE_EXT;
                } else {
                    IdeBusInterface->IdeDevice.ReadCommand  = READ_MULTIPLE;
                    IdeBusInterface->IdeDevice.WriteCommand = WRITE_MULTIPLE;
                }
            } else {                      // 1 Block = 1 Sector
                if ( IdeBusInterface->IdeDevice.IdentifyData.Command_Set_Supported_83 & 0x400 ) {
                    //					48Bit LBA supported
                    IdeBusInterface->IdeDevice.ReadCommand  = READ_SECTORS_EXT;
                    IdeBusInterface->IdeDevice.WriteCommand = WRITE_SECTORS_EXT;
                } else {
                    IdeBusInterface->IdeDevice.ReadCommand  = READ_SECTORS;
                    IdeBusInterface->IdeDevice.WriteCommand = WRITE_SECTORS;
                }
            }

            if ( DMACapable( IdeBusInterface )) {
                if ( gPlatformIdeProtocol->IdeBusMasterSupport ) {
                    IdeBusInterface->IdeDevice.ReadCommand  = READ_DMA;
                    IdeBusInterface->IdeDevice.WriteCommand = WRITE_DMA;

                    if ( IdeBusInterface->IdeDevice.IdentifyData.Command_Set_Supported_83 & 0x400 ) {
                    //
                    // 48Bit LBA supported
                    //
                        IdeBusInterface->IdeDevice.ReadCommand  = READ_DMA_EXT;
                        IdeBusInterface->IdeDevice.WriteCommand = WRITE_DMA_EXT;
	                }
 			    }
            }
        }    
        IdeBusInitInterface->IdeBusInitData[Current_Channel][Current_Device] = DEVICE_CONFIGURED_SUCCESSFULLY;
    }

    if ( gPlatformIdeProtocol->DisableSoftSetPrev || gPlatformIdeProtocol->ForceHddPasswordPrompt ) {

        //
        // Software settings preserved
        //
        if ((IdeBusInterface->IdeDevice.IdentifyData.Reserved_76_79[0] != 0xFFFF)
            && (IdeBusInterface->IdeDevice.IdentifyData.Reserved_76_79[2] & 0x0040)) {
            Status = IdeSetFeatureCommand( IdeBusInterface, DISABLE_SATA2_SOFTPREV, 6 );
            //
            // Get the updated IdentifyData
            //
            GetIdentifyData( IdeBusInterface, &(IdeBusInterface->IdeDevice));
        }
    }

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	InitIdeBlockIO
//
// Description:	Initializes IDE Block IO interface
//
// Input:
//
//	IDE_BUS_PROTOCOL				*IdeBusInterface,
//
// Output:
//	EFI_STATUS
//
// Modified:
//
// Referrals: AllocatePool, OpenProtocol, DetectAtapiMedia, AtapiInquiryData
//
// Notes:
//  Here is the control flow of this function:
//  1. Initialize EFI_BLOCK_IO_PROTOCOL Protocol.
//	2. In case of Removable devices, detect Media presence.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS InitIdeBlockIO(
    IN IDE_BUS_PROTOCOL *IdeBusInterface )
{
    EFI_STATUS            Status;
    EFI_BLOCK_IO_PROTOCOL *BlkIo;
    IDE_BLOCK_IO          *IdeBlkIo;
    EFI_BLOCK_IO_MEDIA    *BlkMedia;
    ATAPI_DEVICE          *AtapiDevice;
    UINT8                 *Data;
    UINT8                 *InquiryData;
    UINT16                InquiryDataSize;
    UINT8                 Current_Channel;
    UINT8                 Current_Device;
    UINT8                 bTemp;
    UINT16                OddType = 0;
    UINT8                 OddLoadingType =0xFF;
    UINT32                SectorSize = ATA_SECTOR_BYTES;

    Status = pBS->AllocatePool( EfiBootServicesData,
                                sizeof(IDE_BLOCK_IO),
                                (VOID**)&IdeBlkIo );

    if ( EFI_ERROR( Status )) {
        return Status;
    }


    BlkMedia = MallocZ( sizeof(EFI_BLOCK_IO_MEDIA));

    if ( !BlkMedia ) {
        pBS->FreePool( IdeBlkIo );
        return EFI_OUT_OF_RESOURCES;
    }

    //
    //Initialize the IdeBlkIo pointer in IDE_BUS_PROTOCOL (IdeBusInterface)
    //
    IdeBusInterface->IdeBlkIo = IdeBlkIo;

    //
    //Initialize the fields in IdeBlkIo (IDE_BLOCK_IO)
    //    
    IdeBlkIo->IdeBusInterface = IdeBusInterface;

    if ( IdeBusInterface->IdeDevice.DeviceType == ATA ) {
        //    
        //ATA
        //    
        BlkIo              = &(IdeBlkIo->BlkIo);
        //
        // UEFI2.3.1 Supports the BlockIo Revision 3
        //
        if(pST->Hdr.Revision >= 0x0002001F) {
            BlkIo->Revision    = EFI_BLOCK_IO_PROTOCOL_REVISION3;
        } else {
            BlkIo->Revision    = BLKIO_REVISION;
        }
        BlkIo->Media       = BlkMedia;
        BlkIo->Reset       = AtaReset;
        BlkIo->ReadBlocks  = AtaBlkRead;
        BlkIo->WriteBlocks = AtaBlkWrite;
        BlkIo->FlushBlocks = AtaBlkFlush;

        BlkMedia->MediaId        = 0;
        BlkMedia->RemovableMedia = (IdeBusInterface->IdeDevice.IdentifyData.General_Config_0 & 0x80) == 0x80 ? TRUE : FALSE;

        //Check if Hot plug supported for this device
        Current_Channel = IdeBusInterface->IdeDevice.Channel;
        Current_Device  = IdeBusInterface->IdeDevice.Device;
        bTemp           = Current_Channel == 0 ? 1 : 4;       // BIT MASK

        if ( Current_Device ) {
            bTemp <<= 1;
        }

        if ( bTemp & IdeBusInterface->IdeBusInitInterface->HPMask ) {
            BlkMedia->RemovableMedia = TRUE;
        }

        BlkMedia->MediaPresent     = TRUE;
        BlkMedia->LogicalPartition = FALSE;
        BlkMedia->ReadOnly         = FALSE;
        BlkMedia->WriteCaching     = FALSE;


        if((IdeBusInterface->IdeDevice.IdentifyData.Reserved_104_126[2] & BIT14) && // WORD 106 valid? - BIT 14 - 1
           (!(IdeBusInterface->IdeDevice.IdentifyData.Reserved_104_126[2] & BIT15)) && // WORD 106 valid? - BIT 15 - 0
           (IdeBusInterface->IdeDevice.IdentifyData.Reserved_104_126[2] & BIT12)) { // WORD 106 bit 12 - Sectorsize > 256 words
            // The sector size is in words 117-118.
            SectorSize = (UINT32)(IdeBusInterface->IdeDevice.IdentifyData.Reserved_104_126[13] + \
                                  (IdeBusInterface->IdeDevice.IdentifyData.Reserved_104_126[14] << 16)) * 2;
        }

        BlkMedia->BlockSize = SectorSize;

        //If BusMaster Support is Enabled for the device, IO Alignment should be DWORD

        if ( DMACapable( IdeBusInterface )) {
            BlkMedia->IoAlign = 4;
        } else {
            BlkMedia->IoAlign = 0;
        }

        if ( IdeBusInterface->IdeDevice.IdentifyData.Command_Set_Supported_83 & 0x400 ) {
            BlkMedia->LastBlock = IdeBusInterface->IdeDevice.IdentifyData.LBA_48 - 1;
        } else {
            BlkMedia->LastBlock = IdeBusInterface->IdeDevice.IdentifyData.Addressable_Sector_60 - 1;
        }

        if(pST->Hdr.Revision >= 0x0002001F) {

            BlkMedia->OptimalTransferLengthGranularity=BlkMedia->BlockSize;
            //
            // bit 14 of word 106 is set to one and bit 15 of word 106 is cleared to zero, 
            // then the contents of word 106 contain valid information . 
            // Otherwise, information is not valid in this word.
            //
            if ( (IdeBusInterface->IdeDevice.IdentifyData.Reserved_104_126[2] & 0xC000) == 0x4000 ) {
                //
                // If bit 13 of word 106 is set to one, then the device has more than one 
                // logical sector per physical sector and bits (3:0) of word 106 are valid
                //
                if ( IdeBusInterface->IdeDevice.IdentifyData.Reserved_104_126[2] & 0x2000 ) {
    
                    BlkMedia->LogicalBlocksPerPhysicalBlock = 1 << 
                                    (IdeBusInterface->IdeDevice.IdentifyData.Reserved_104_126[2] & 0xF);
    
                    //
                    // Bits 13:0 of word 209 indicate the Logical sector offset within the first physical 
                    // sector where the first logical sector is placed
                    //
                    BlkMedia->LowestAlignedLba =IdeBusInterface->IdeDevice.IdentifyData.Reserved_206_254[3] & 0x3FFF;
    
                } else {
                    //
                    // Default set the 1 logical blocks per PhysicalBlock
                    //
                    BlkMedia->LogicalBlocksPerPhysicalBlock=1;
    
                    //
                    // Default value set to 0 for Lowest Aligned LBA
                    //
                    BlkMedia->LowestAlignedLba=0;
                }
            } else {
                    //
                    // Default set the 1 logical blocks per PhysicalBlock
                    //
                    BlkMedia->LogicalBlocksPerPhysicalBlock=1;
                    //
                    // Default value set to 0 for Lowest Aligned LBA
                    //
                    BlkMedia->LowestAlignedLba=0;
            }
        }
    } else {
        //
        //If it is an ATAPI device, check whether it is a CDROM or not. Currently only CDROM/Direct access Devices are supported.
        //
        if ((IdeBusInterface->IdeDevice.IdentifyData.General_Config_0 & 0x1f00) == (CDROM_DEVICE << 8)
            || (IdeBusInterface->IdeDevice.IdentifyData.General_Config_0 & 0x1f00) == (DIRECT_ACCESS_DEVICE << 8)
            || (IdeBusInterface->IdeDevice.IdentifyData.General_Config_0 & 0x1f00) == (OPTICAL_MEMORY_DEVICE << 8)) {
            AtapiDevice = MallocZ( sizeof (ATAPI_DEVICE));

            if ( !AtapiDevice ) {
                return EFI_OUT_OF_RESOURCES;
            }

            IdeBusInterface->IdeDevice.AtapiDevice = AtapiDevice;

            Status = pBS->AllocatePool( EfiBootServicesData,
                                        16,
                                        (VOID**)&Data
                                        );

            if ( EFI_ERROR( Status )) {
                return Status;
            }

            AtapiDevice->PacketBuffer = Data;
            AtapiDevice->DeviceType   = (IdeBusInterface->IdeDevice.IdentifyData.General_Config_0 & 0x1f00) >> 8;
            AtapiDevice->PacketSize   = (IdeBusInterface->IdeDevice.IdentifyData.General_Config_0 & 3) == 1 ? 16 : 12;

            BlkIo              = &(IdeBlkIo->BlkIo);
            //
            // UEFI2.3.1 Supports the BlockIo Revision 3
            //
            if(pST->Hdr.Revision >= 0x0002001F) {
                BlkIo->Revision    = EFI_BLOCK_IO_PROTOCOL_REVISION3;
            } else {
                BlkIo->Revision    = BLKIO_REVISION;
            }
            BlkIo->Media       = BlkMedia;
            BlkIo->Reset       = AtapiReset;
            BlkIo->ReadBlocks  = AtapiBlkRead;
            BlkIo->WriteBlocks = AtapiBlkWrite;
            BlkIo->FlushBlocks = AtapiBlkFlush;
            //
            //Initialize with default value. Later on it will be updated if needed.
            //
            BlkMedia->BlockSize = CDROM_BLOCK_SIZE;


            //
            //Update Inquiry Data
            //
            Status = pBS->AllocatePool( EfiBootServicesData,
                                        INQUIRY_DATA_LENGTH,
                                        (VOID**)&InquiryData );

            if ( EFI_ERROR( Status )) {
                return Status;
            }
            InquiryDataSize = INQUIRY_DATA_LENGTH;
            AtapiInquiryData( IdeBusInterface, InquiryData, &InquiryDataSize );
            AtapiDevice->InquiryData     = InquiryData;
            AtapiDevice->InquiryDataSize = InquiryDataSize;

            //
            // Get the ATAPI drive Type information and save it ATAPI_DEVICE
            //
            Status = GetOddType( IdeBusInterface, &OddType );

            if ( !EFI_ERROR( Status )) {
                AtapiDevice->OddType = GetEnumOddType( OddType );
            }

            //
            // Get the ATAPI drive Loading information and save it ATAPI_DEVICE
            //
            Status = GetOddLoadingType( IdeBusInterface, &OddLoadingType );

            if ( !EFI_ERROR( Status )) {
                AtapiDevice->OddLoadingType = (ODD_LOADING_TYPE)OddLoadingType;
            } else {
                AtapiDevice->OddLoadingType = (ODD_LOADING_TYPE)0xFF;
            }

            BlkMedia->RemovableMedia   = (IdeBusInterface->IdeDevice.IdentifyData.General_Config_0 & 0x80) == 0x80 ? TRUE : FALSE;
            BlkMedia->LogicalPartition = FALSE;
            BlkMedia->WriteCaching     = FALSE;

            //
            //If BusMaster Support is Enabled for the device, IO Alignment should be DWORD
            //
            if ( DMACapable( IdeBusInterface )) {
                BlkMedia->IoAlign = 4;
            } else {
                BlkMedia->IoAlign = 0;
            }
        }
    }
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	GetEnumOddType
//
// Description:	Get the Enum value for ODD type found on profile
//
// Input:
//
//      UINT16      Oddtype
// Output:
//      ODD_TYPE    EnumValue
//
// Modified:
//
// Referrals:
//
// Notes:
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
ODD_TYPE GetEnumOddType(
    UINT16 OddType )
{
    switch ( OddType )
    {
    case 1:
    case 3:
    case 4:
    case 5:
        return Obsolete;

    case 2:
        return Removabledisk;

    case 8:
        return CDROM;

    case 9:
        return CDR;

    case 0xa:
        return CDRW;

    case 0x10:
        return DVDROM;

    case 0x11:
        return DVDRSequentialrecording;

    case 0x12:
        return DVDRAM;

    case 0x13:
        return DVDRWRestrictedOverwrite;

    case 0x15:
        return DVDRWSequentialrecording;

    case 0x16:
        return DVDRDualLayerJumprecording;

    case 0x17:
        return DVDRWDualLayer;

    case 0x18:
        return DVDDownloaddiscrecording;

    case 0x1a:
        return DVDRW;

    case 0x1b:
        return DVDR;

    case 0x40:
        return BDROM;

    case 0x41:
        return BDRSequentialRecording;

    case 0x42:
        return BDRRandomRecordingMode;

    case 0x43:
        return BDRE;

    case 0x50:
        return HDDVDROM;

    case 0x51:
        return HDDVDR;

    case 0x52:
        return HDDVDRAM;

    case 0x53:
        return HDDVDRW;

    case 0x58:
        return HDDVDRDualLayer;

    case 0x5a:
        return HDDVDRWDualLayer;

    default:
        return UnknownType;
    }
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	InitIdeDiskInfo
//
// Description:	Initializes IDE DiskInfo Interface
//
// Input:
//
//	IDE_BUS_PROTOCOL		*IdeBusInterface,
//
// Output:
//	EFI_STATUS
//
// Modified:
//
// Referrals: AllocatePool OpenProtocol
//
// Notes:
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS InitIdeDiskInfo(
    IN IDE_BUS_PROTOCOL *IdeBusInterface )
{
    EFI_STATUS    Status;
    IDE_DISK_INFO *IdeDiskInfo;

    Status = pBS->AllocatePool( EfiBootServicesData,
                                sizeof(IDE_DISK_INFO),
                                (VOID**)&IdeDiskInfo );

    if ( EFI_ERROR( Status )) {
        return Status;
    }

    //
    //Initialize the IdeBlkIo pointer in IDE_BUS_PROTOCOL (IdeBusInterface)
    //
    IdeBusInterface->IdeDiskInfo = IdeDiskInfo;

    //
    //Initialize the fields in IdeDiskInfo (IDE_DISK_INFO)
    //
    IdeDiskInfo->IdeBusInterface = IdeBusInterface;

    pBS->CopyMem( &(IdeDiskInfo->DiskInfo.Interface), &gEfiIdeDiskInfoProtocolGuid, sizeof (EFI_GUID));
    IdeDiskInfo->DiskInfo.Inquiry   = DiskInfoInquiry;
    IdeDiskInfo->DiskInfo.Identify  = DiskInfoIdentify;
    IdeDiskInfo->DiskInfo.SenseData = DiskInfoSenseData;
    IdeDiskInfo->DiskInfo.WhichIde  = DiskInfoWhichIDE;
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	CreateIdeDevicePath
//
// Description:	Creates a IDE device devicepath and adds it to IdeBusInterface
//
// Input:
//	IN EFI_DRIVER_BINDING_PROTOCOL  *This,
//	IN EFI_HANDLE                   Controller,
//	IDE_BUS_INIT_PROTOCOL			*IdeBusInitInterface;
//	IN EFI_DEVICE_PATH_PROTOCOL     *RemainingDevicePath
//	UINT8							Current_Channel
//	UINT8							Current_Device
//
// Output:
//	EFI_STATUS
//
// Modified:
//
// Referrals: AllocatePool, OpenProtocol, IdeBusStart
//
// Notes:
//  Here is the control flow of this function:
//  1.  If Remaining Devicepath is not NULL, we have already verified that it is a
//			valid Atapi device path in IdeBusStart. So nothing to do. Just exit.
//	2.	Build a Atapi devicepath and a End devce path.
//	3.  Get the Devicepath for the IDE controller.
//	3.  Append Atapi devicepath to  IDE controller devicepath.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS CreateIdeDevicePath(
    IN EFI_DRIVER_BINDING_PROTOCOL  *This,
    IN EFI_HANDLE                   Controller,
    IDE_BUS_INIT_PROTOCOL           *IdeBusInitInterface,
    IDE_BUS_PROTOCOL                *IdeBusInterface,
    IN OUT EFI_DEVICE_PATH_PROTOCOL *RemainingDevicePath,
    IN UINT8                        Current_Channel,
    IN UINT8                        Current_Device )
{
    EFI_STATUS               Status;
    ATAPI_DEVICE_PATH        NewDevicePath;
    EFI_DEVICE_PATH_PROTOCOL *TempDevicePath;

    NewDevicePath.Header.Type    = MESSAGING_DEVICE_PATH;
    NewDevicePath.Header.SubType = MSG_ATAPI_DP;
    SET_NODE_LENGTH( &NewDevicePath.Header, ATAPI_DEVICE_PATH_LENGTH );
    NewDevicePath.PrimarySecondary = Current_Channel;
    NewDevicePath.SlaveMaster      = Current_Device;
    NewDevicePath.Lun              = 0;

    //
    //Append the Device Path
    //
    Status = pBS->OpenProtocol( Controller,
                                &gDevicePathProtocolGuid,
                                (VOID**)&TempDevicePath,
                                This->DriverBindingHandle,
                                Controller,
                                EFI_OPEN_PROTOCOL_GET_PROTOCOL );

    IdeBusInterface->DevicePathProtocol = DPAddNode( TempDevicePath, &NewDevicePath.Header );
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	ConfigureIdeDevice
//
// Description:	Issues SET FEATURE Command
//
// Input:
//		IDE_BUS_PROTOCOL			*IdeBusInterface,
//		IDE_BUS_INIT_PROTOCOL		*IdeBusInitInterface
//
// Output:
//	EFI_STATUS
//
// Modified:
//
// Referrals: ConfigureIdeDeviceAndController, IdeSetFeatureCommand
//
// Notes:
//  Here is the control flow of this function:
//  1. Issue Set feature commend to set PIO mode if needed.
//	2. Set Multiple Mode command for ATA devices if needed.
//  3. Issue Set feature commend to set UDMA/MWDMA. If it fails, disable Busmaster support.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS ConfigureIdeDevice(
    IN IDE_BUS_PROTOCOL      *IdeBusInterface,
    IN IDE_BUS_INIT_PROTOCOL *IdeBusInitInterface )
{
    EFI_STATUS               Status= EFI_SUCCESS;
    UINT8                    DMACapability;
    UINT8                    Data8;
    IO_REGS                  Regs = IdeBusInterface->IdeDevice.Regs;
    UINT16                   DeviceName[41];
    UINT16                   Index;

    EFI_UNICODE_STRING_TABLE *tempUnicodeTable;
    CHAR8                    Language[] = "Eng";

    //
    //Check if Device need spin-up
    //
    if ((IdeBusInterface->IdeDevice.IdentifyData.General_Config_0 & 4)
        && (IdeBusInterface->IdeDevice.IdentifyData.Special_Config_2 == SPIN_UP_REQUIRED1
            || IdeBusInterface->IdeDevice.IdentifyData.Special_Config_2 == SPIN_UP_REQUIRED2)) {
        Status = IdeSetFeatureCommand( IdeBusInterface, SET_DEVICE_SPINUP, 0 );

        if ( EFI_ERROR( Status )) {    
            //
            //Some HDD may take a long time to spin up. Wait for additional time
            //
            Status = WaitforBitClear( IdeBusInterface->PciIO, Regs.ControlBlock.AlternateStatusReg, BSY | DRQ, gPlatformIdeProtocol->PoweonBusyClearTimeout );
        }
        //
        //Get the Identify Command once more
        //
        GetIdentifyData( IdeBusInterface, &(IdeBusInterface->IdeDevice));
    }

    //
    //	Check if PIO mode needs to be programmed
    //    
    if ((IdeBusInterface->IdeDevice.IdentifyData.Valid_Bits_53 & 0x2) && (IdeBusInterface->IdeDevice.PIOMode != 0xff)) {
        Status = IdeSetFeatureCommand( IdeBusInterface, SET_TRANSFER_MODE, PIO_FLOW_CONTROL | IdeBusInterface->IdeDevice.PIOMode );
    }

    if ( EFI_ERROR( Status )) {
        return EFI_DEVICE_ERROR;
    }

    //
    //Issue Set Multiple Mode Command only for ATA device
    //
    if  ( IdeBusInterface->IdeDevice.DeviceType == ATA ) {
        Data8 = IdeBusInterface->IdeDevice.IdentifyData.Maximum_Sector_Multiple_Command_47 & 0xff;

        if ( Data8 & 0x2 ) {
            Data8 = 2;
        }

        if ( Data8 & 0x4 ) {
            Data8 = 0x4;
        }

        if ( Data8 & 0x8 ) {
            Data8 = 0x8;
        }

        if ( Data8 & 0x10 ) {
            Data8 = 0x10;
        }

        if ( Data8 & 0x20 ) {
            Data8 = 0x20;
        }

        if ( Data8 & 0x40 ) {
            Data8 = 0x40;
        }

        if ( Data8 & 0x80 ) {
            Data8 = 0x80;
        }

        if ( Data8 > 1 ) {
            Status = IdeNonDataCommand(
                IdeBusInterface,
                0,              // Features
                Data8,          // Sector Count
                0,              // LBA Low
                0,              // LBA Mid
                0,              // LBA High
                IdeBusInterface->IdeDevice.Device << 4, // Device
                SET_MULTIPLE_MODE );                     // Command
        }
    }

    //Check if Busmaster Enabled
    //Status = EFI_NOT_FOUND;
    //Check if  UDMA is supported
    if  ( IdeBusInterface->IdeDevice.UDma != 0xff ) {
        Status =     IdeSetFeatureCommand( IdeBusInterface, SET_TRANSFER_MODE, UDMA_MODE | IdeBusInterface->IdeDevice.UDma );
    } else {
        if ( IdeBusInterface->IdeDevice.MWDma != 0xff ) {
            Status = IdeSetFeatureCommand( IdeBusInterface, SET_TRANSFER_MODE, MWDMA_MODE | IdeBusInterface->IdeDevice.MWDma );
        }
    }

    if ( EFI_ERROR( Status )) {
        //
        //No DMA support
        //
        IdeBusInterface->IdeDevice.UDma  = 0xff;
        IdeBusInterface->IdeDevice.MWDma = 0xff;
    } else {
        //
        //Enable DMA capable bit
        //
        DMACapability = 0x20;

        if ( IdeBusInterface->IdeDevice.Device ) {
            DMACapability = 0x40;
        }

        if ( DMACapable( IdeBusInterface )) {
            IdeReadByte( IdeBusInterface->PciIO,
                         IdeBusInterface->IdeDevice.Regs.BusMasterBlock.BMStatusRegister,
                         &Data8 );
            Data8 |= DMACapability;
            IdeWriteByte( IdeBusInterface->PciIO,
                          IdeBusInterface->IdeDevice.Regs.BusMasterBlock.BMStatusRegister,
                          Data8 );
        }
    }

    //
    //Convert the Device string from Engligh to Unicode
    //
    IdeBusInterface->IdeDevice.UDeviceName = NULL;
	if ( gPlatformIdeProtocol->EfiIdeProtocol ) {
	    IdeBusInterface->ControllerNameTable = IdeBusInterface->IdeDevice.UDeviceName;
	} 

    for ( Index = 0; Index < 40; Index += 2 ) {

            DeviceName[Index]     = ((UINT8*)IdeBusInterface->IdeDevice.IdentifyData.Model_Number_27)[Index + 1];
            DeviceName[Index + 1] = ((UINT8*)IdeBusInterface->IdeDevice.IdentifyData.Model_Number_27)[Index];
    }

    for ( Index = 39; Index >= 0; Index-- ) {
        if ( DeviceName[Index] == 0x20 )
            continue;
        else 
            break;
    }

    DeviceName[Index + 1] = 0;        // Terminate string
    Index += 2;

    //
    //This is a patch to make it work for both in Aptio and Alaska
    //
    tempUnicodeTable = MallocZ( sizeof (EFI_UNICODE_STRING_TABLE) * 2 );

    Status = pBS->AllocatePool( EfiBootServicesData,
                                sizeof (Language),
                                (VOID**)&tempUnicodeTable[0].Language
                                );

    Status = pBS->AllocatePool( EfiBootServicesData,
                                Index * (sizeof (UINT16)),
                                (VOID**)&tempUnicodeTable[0].UnicodeString
                                );


    pBS->CopyMem( tempUnicodeTable[0].Language, &Language,  sizeof(Language));
    pBS->CopyMem( tempUnicodeTable[0].UnicodeString, DeviceName, Index * (sizeof (UINT16)));
    tempUnicodeTable[1].Language           = NULL;
    tempUnicodeTable[1].UnicodeString      = NULL;
    IdeBusInterface->IdeDevice.UDeviceName = tempUnicodeTable;
	if ( gPlatformIdeProtocol->EfiIdeProtocol ) {
	    IdeBusInterface->ControllerNameTable = IdeBusInterface->IdeDevice.UDeviceName;
	} 
    if ( gPlatformIdeProtocol->SBIdeSupport ) {
        InitMiscConfig(IdeBusInterface);
    }

	if ( gPlatformIdeProtocol->IdePowerManagementSupport ) {
	    Status = InitIDEPowerManagement( IdeBusInterface );
	}

    return EFI_SUCCESS;
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:	InitMiscConfig
//
// Description:	Initialize misc IDE configurations.
//
// Input:
//	IN SATA_DEVICE_INTERFACE	*SataDevInterface	
//
// Output:
//	None
//
//<AMI_PHDR_END>
//**********************************************************************
VOID InitMiscConfig (
    IN IDE_BUS_PROTOCOL    *IdeBusInterface
)
{
    if ( gPlatformIdeProtocol->DiPMSupport ) {

        if(IdeBusInterface->IdeDevice.IdentifyData.Reserved_76_79[2] & \
                IDENTIFY_DiPM__SUPPORT) { // DiPM supported?
            //
            // Always disable DiPM in IDE mode
            //
            IdeSetFeatureCommand (IdeBusInterface, DiPM_DISABLE, DiPM_SUB_COMMAND);
        }
    }
    if ( gPlatformIdeProtocol->AcousticManagementSupport ) {
    	InitAcousticSupport (IdeBusInterface);
	}

}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	InitAcousticSupport
//
// Description:	Initializes Acoustic Management Support functionality
//
// Input:
//		IDE_BUS_PROTOCOL			*IdeBusInterface,
//
// Output:
//	EFI_STATUS
//
// Modified:
//
// Referrals: IdeSetFeatureCommand
//
// Notes:
// 1. Check if the device support Acoustic management.
// 2. Check the desired state Vs the current state.
// 3. If both are equal nothing to do exit else program the desired level
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS InitAcousticSupport(
    IN IDE_BUS_PROTOCOL *IdeBusInterface )
{
    UINT8 Data8;

    //
    //	Check if the device supports Acoustic Management
    //
    if  ( IdeBusInterface->IdeDevice.IdentifyData.Command_Set_Supported_83 & 0x200 ) {
        //
        //Check if Acoustic Level need to be enabled or Disabled
        //
        if ( IdeBusInterface->IdeBusInitInterface->Flags & ACOUSTIC_SUPPORT_ENABLE ) {
            Data8 = IdeBusInterface->IdeBusInitInterface->Acoustic_Management_Level;

            //
            // Do we need to program the recommended value
            //
			if ( Data8 == ACOUSTIC_LEVEL_BYPASS ) {
                //
                // Get the rcommended value
                //
				Data8 = (UINT8)(IdeBusInterface->IdeDevice.IdentifyData.Acoustic_Level_94 >> 8);
			}

				IdeSetFeatureCommand (IdeBusInterface, ACOUSTIC_MANAGEMENT_ENABLE, Data8);
		} else {
                //
                // If already disabled, nothing to do
                //
			if	(IdeBusInterface->IdeDevice.IdentifyData.Command_Set_Enabled_86 & 0x200) 			
				IdeSetFeatureCommand (IdeBusInterface, ACOUSTIC_MANAGEMENT_DISABLE, 0);
		}
	}
	return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	UpdateBaseAddress
//
// Description:	Updates Command and Control reg address.
//
// Input:
//	IDE_BUS_PROTOCOL			*IdeBusInterface;
//
// Output:
//	EFI_STATUS
//
// Modified:
//
// Referrals: IdeBusStart
//
// Notes:
//  Here is the control flow of this function:
//  1. Using PCI_IO_PROTOCOL, update the Command, control and Busmaster reg address.
//	Make use of Channel number while updating. Also check whether controller is running in Legacy/Native mode
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS UpdateBaseAddress(
    IN IDE_BUS_PROTOCOL *IdeBusInterface )
{
    EFI_PCI_IO_PROTOCOL *PciIO;
    UINT8               PciConfig[0x40];
    UINT16              CommandReg;
    UINT16              ControlReg;
    UINT16              BusMasterReg;


    PciIO = IdeBusInterface->PciIO;
    PciIO->Pci.Read(
        PciIO,
        EfiPciIoWidthUint8,
        0,
        sizeof (PciConfig),
        PciConfig );

    if ((PciConfig [PROGRAMMING_INTERFACE_OFFSET] & (IdeBusInterface->IdeDevice.Channel == 0 ? 1 : 4))
        || (PciConfig [IDE_SUB_CLASS_CODE] == SCC_AHCI_CONTROLLER)
        || (PciConfig [IDE_SUB_CLASS_CODE] == SCC_RAID_CONTROLLER)) {
        //   
        //Native Mode Secondary
        //    
        if ( IdeBusInterface->IdeDevice.Channel ) {
            CommandReg   =    (*(UINT16*)(PciConfig + SECONDARY_COMMAND_BLOCK_OFFSET)) & 0xfffe;
            ControlReg   =   ((*(UINT16*)(PciConfig + SECONDARY_CONTROL_BLOCK_OFFSET)) & 0xfffe) + 2;
            BusMasterReg = ((*(UINT16*)(PciConfig + LEGACY_BUS_MASTER_OFFSET)) & 0xfffe) + 8;
        } else {  
            //
            // Native mode Primary
            //   
            CommandReg   =   (*(UINT16*)(PciConfig + PRIMARY_COMMAND_BLOCK_OFFSET)) & 0xfffe;
            ControlReg   =  ((*(UINT16*)(PciConfig + PRIMARY_CONTROL_BLOCK_OFFSET)) & 0xfffe) + 2;
            BusMasterReg = (*(UINT16*)(PciConfig + LEGACY_BUS_MASTER_OFFSET)) & 0xfffe;
        }
    } else {
        //
        //Legacy Mode Secondary
        //
        if ( IdeBusInterface->IdeDevice.Channel ) {
            CommandReg   = SECONDARY_COMMAND_BLOCK;
            ControlReg   = SECONDARY_CONTROL_BLOCK;
            BusMasterReg = (*(UINT16*)(PciConfig + LEGACY_BUS_MASTER_OFFSET) & 0xfffe) + 8;
        } else {      
            //
            //Legacy mode Primary
            //
            CommandReg   = PRIMARY_COMMAND_BLOCK;
            ControlReg   = PRIMARY_CONTROL_BLOCK;
            BusMasterReg = (*(UINT16*)(PciConfig + LEGACY_BUS_MASTER_OFFSET) & 0xfffe);
        }
    }

    //
    //	Validate the Address
    //
    if ( CommandReg == 0 || ControlReg == 0 ) {
        return EFI_DEVICE_ERROR;
    }

    if ( CommandReg == 0xfffe || ControlReg == 0xfffe ) {
        return EFI_DEVICE_ERROR;
    }

    //
    //Update the Command block registers
    //
    IdeBusInterface->IdeDevice.Regs.CommandBlock.DataReg        = CommandReg;
    IdeBusInterface->IdeDevice.Regs.CommandBlock.FeatureReg     = CommandReg + 1;
    IdeBusInterface->IdeDevice.Regs.CommandBlock.ErrorReg       = CommandReg + 1;
    IdeBusInterface->IdeDevice.Regs.CommandBlock.SectorCountReg = CommandReg + 2;
    IdeBusInterface->IdeDevice.Regs.CommandBlock.LBALowReg      = CommandReg + 3;
    IdeBusInterface->IdeDevice.Regs.CommandBlock.LBAMidReg      = CommandReg + 4;
    IdeBusInterface->IdeDevice.Regs.CommandBlock.LBAHighReg     = CommandReg + 5;
    IdeBusInterface->IdeDevice.Regs.CommandBlock.DeviceReg      = CommandReg + 6;
    IdeBusInterface->IdeDevice.Regs.CommandBlock.CommandReg     = CommandReg + 7;
    IdeBusInterface->IdeDevice.Regs.CommandBlock.StatusReg      = CommandReg + 7;

    //
    //Update the Control Block Register address
    //
    IdeBusInterface->IdeDevice.Regs.ControlBlock.DeviceControlReg   = ControlReg;
    IdeBusInterface->IdeDevice.Regs.ControlBlock.AlternateStatusReg = ControlReg;


    //
    //Update the Bus Master register address
    //
    IdeBusInterface->IdeDevice.Regs.BusMasterBlock.BMCommandRegister           = BusMasterReg;
    IdeBusInterface->IdeDevice.Regs.BusMasterBlock.BMStatusRegister            = BusMasterReg + 2;
    IdeBusInterface->IdeDevice.Regs.BusMasterBlock.BMDescriptorTablePointerReg = BusMasterReg + 4;

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	DMACapable
//
// Description:	Check if DMA is supported
//
// Input:
//	IN IDE_BUS_PROTOCOL				*IdeBusInterface,
//
// Output:
//		TRUE : DMA Capable
//
// Modified:
//
// Referrals:
//
// Notes:
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN DMACapable(
    IN IDE_BUS_PROTOCOL *IdeBusInterface )
{
    if ( IdeBusInterface->IdeDevice.DeviceType == ATAPI ) {
        //
        // For Atapi Devices check Bit 8 in Word 49 =  DMA	Supported or not
        //
        if ((IdeBusInterface->IdeDevice.IdentifyData.Capabilities_49 & 0x100) == 0 ) {
            return FALSE;
        }
    }

    if ((IdeBusInterface->IdeDevice.UDma != 0xff)
        || (IdeBusInterface->IdeDevice.MWDma != 0xff)) {
        return TRUE;
    } else {
        return FALSE;
    }
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	DiskInfoInquiry
//
// Description:
//
// Input:
//	IN EFI_DISK_INFO_PROTOCOL	*This,
//	IN OUT VOID					*InquiryData,
//	IN OUT UINT32				*InquiryDataSize
//
// Output:
//	EFI_STATUS
//
// Modified:
//
// Referrals: InitIdeDiskInfo
//
// Notes:
//	1. Check for Atapi Device. If not exit
//	2. COpy the Inquiry Data from AtapiDevice->InquiryData to the input pointer.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS DiskInfoInquiry(
    IN EFI_DISK_INFO_PROTOCOL *This,
    IN OUT VOID               *InquiryData,
    IN OUT UINT32             *InquiryDataSize )
{
    IDE_BUS_PROTOCOL *IdeBusInterface = ((IDE_BLOCK_IO*)This)->IdeBusInterface;
    ATAPI_DEVICE     *AtapiDevice     = IdeBusInterface->IdeDevice.AtapiDevice;


    //
    //	Check for ATAPI device. If not return EFI_NOT_FOUND
    //
    if ( IdeBusInterface->IdeDevice.DeviceType == ATA ) {
        return EFI_NOT_FOUND;               
    } else {
        if ( *InquiryDataSize < AtapiDevice->InquiryDataSize ) {
            *InquiryDataSize = AtapiDevice->InquiryDataSize;
            return EFI_BUFFER_TOO_SMALL;
        }

        if ( AtapiDevice->InquiryData != NULL ) {
            pBS->CopyMem( InquiryData, AtapiDevice->InquiryData, AtapiDevice->InquiryDataSize );
            *InquiryDataSize = AtapiDevice->InquiryDataSize;
            return EFI_SUCCESS;
        } else {
            return EFI_NOT_FOUND;
        }
    }
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	DiskInfoIdentify
//
// Description:	Return Identify Data
//
// Input:
//	EFI_DISK_INFO_PROTOCOL			*This,
//	IN OUT VOID						*IdentifyData,
//	IN OUT UINT32					*IdentifyDataSize
//
// Output:
//	EFI_STATUS
//
// Modified:
//
// Referrals: InitIdeDiskInfo
//
// Notes:
//	1. Return the Identify command data.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS DiskInfoIdentify(
    EFI_DISK_INFO_PROTOCOL *This,
    IN OUT VOID            *IdentifyData,
    IN OUT UINT32          *IdentifyDataSize )
{
    IDE_BUS_PROTOCOL *IdeBusInterface = ((IDE_BLOCK_IO*)This)->IdeBusInterface;

    if ( *IdentifyDataSize < sizeof (IDENTIFY_DATA)) {
        *IdentifyDataSize = sizeof (IDENTIFY_DATA);
        return EFI_BUFFER_TOO_SMALL;
    }

    pBS->CopyMem( IdentifyData, &(IdeBusInterface->IdeDevice.IdentifyData), sizeof (IDENTIFY_DATA));
    *IdentifyDataSize =  sizeof (IDENTIFY_DATA);
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	DiskInfoSenseData
//
// Description:	Return InfoSenseData.
//
// Input:
//	EFI_DISK_INFO_PROTOCOL          *This,
//	VOID						*SenseData,
//	UINT32						*SenseDataSize,
//	UINT8						*SenseDataNumber
//
// Output:
//	EFI_STATUS
//
// Modified:
//
// Referrals: InitIdeDiskInfo
//
// Notes:
//	1. Return the Sense data for the Atapi device.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS DiskInfoSenseData(
    IN EFI_DISK_INFO_PROTOCOL *This,
    OUT VOID                  *SenseData,
    OUT UINT32                *SenseDataSize,
    OUT UINT8                 *SenseDataNumber )
{
    return EFI_NOT_FOUND;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	DiskInfoWhichIDE
//
// Description:	Returns whether the device is PM/PS/SM/SS
//
// Input:
//	IN EFI_DISK_INFO_PROTOCOL	*This,
//	OUT UINT32					*IdeChannel,
//	OUT UINT32					*IdeDevice
//
// Output:
//	EFI_STATUS
//
// Modified:
//
// Referrals: InitIdeDiskInfo
//
// Notes:
//	1. Return information about the Primary/Secondary channel and Master/Slave information.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS DiskInfoWhichIDE(
    IN EFI_DISK_INFO_PROTOCOL *This,
    OUT UINT32                *IdeChannel,
    OUT UINT32                *IdeDevice )
{
    IDE_BUS_PROTOCOL *IdeBusInterface = ((IDE_BLOCK_IO*)This)->IdeBusInterface;

    *IdeChannel = IdeBusInterface->IdeDevice.Channel;
    *IdeDevice  = IdeBusInterface->IdeDevice.Device;
    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	IdeHPTimer
//
// Description:	Checks for any HP IDE device
//
// Input:
//	IN EFI_EVENT            Event,
//	IN VOID                         *Context
//
// Output:
//	EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID IdeHPTimer(
    IN EFI_EVENT Event,
    IN VOID      *Context )
{
    EFI_STATUS                       Status;
    UINT8                            DeviceStatus;
    UINT8                            CurrentState;
    UINT8                            Current_Channel;
    UINT8                            Current_Device;
    IDE_BUS_INIT_PROTOCOL            *IdeBusInitInterface = (IDE_BUS_INIT_PROTOCOL*)Context;

    IDE_BUS_PROTOCOL                 *IdeBusInterface;
    IN IDE_CONTROLLER_PROTOCOL       *IdeControllerInterface = IdeBusInitInterface->IdeControllerInterface;

    IdeControllerInterface->HPCheckForDeviceChange( IdeControllerInterface->PciIO,
                                                    IdeBusInitInterface->HPMask,
                                                    &DeviceStatus );

    for ( Current_Channel = PRIMARY_CHANNEL; Current_Channel <= SECONDARY_CHANNEL; Current_Channel++ )
    {
        for ( Current_Device = MASTER_DRIVE; Current_Device <= SLAVE_DRIVE; Current_Device++ )
        {
            CurrentState    = IdeBusInitInterface->IdeBusInitData[Current_Channel][Current_Device];
            IdeBusInterface = IdeBusInitInterface->pIdeBusProtocol[Current_Channel][Current_Device];

            if ((CurrentState == DEVICE_CONFIGURED_SUCCESSFULLY) && ((DeviceStatus & 01) == 0)) {
                //
                //Handle Device Removal
                //
                    Status = pBS->DisconnectController( IdeControllerInterface->ControllerHandle, NULL, IdeBusInterface->IdeDeviceHandle );


                if ( Status == EFI_SUCCESS ) {
                    IdeBusInitInterface->IdeBusInitData[Current_Channel][Current_Device] = DEVICE_IN_RESET_STATE;
                }
            }

            if ((CurrentState != DEVICE_CONFIGURED_SUCCESSFULLY) && ((DeviceStatus & 01) == 1)) {
                //Handle device insertion
                //Force IdeBusStart to Enumerate this device.
                IdeBusInitInterface->IdeBusInitData[Current_Channel][Current_Device] = DEVICE_IN_RESET_STATE;
             
                pBS->ConnectController( IdeControllerInterface->ControllerHandle, NULL, NULL, TRUE );
            }
            DeviceStatus >>= 1;
        }
    }
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	CheckHPControllerPresence
//
// Description:	A quick check to see if ports are still decoded.
//
// Input:
//	IN IDE_BUS_PROTOCOL			*IdeBusInterface
//
// Output:
//	EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS CheckHPControllerPresence(
    IN IDE_BUS_PROTOCOL *IdeBusInterface )
{
    UINT8   Device = IdeBusInterface->IdeDevice.Device;
    IO_REGS Regs   = IdeBusInterface->IdeDevice.Regs;
    UINT8   Data8;

    //
    //Select the drive
    //
    IdeWriteByte( IdeBusInterface->PciIO, Regs.CommandBlock.DeviceReg, Device << 4 );

    //
    //Read the status Register
    //
    IdeReadByte( IdeBusInterface->PciIO, Regs.CommandBlock.StatusReg, &Data8 );

    if ( Data8 == 0xff ) {
        return EFI_NOT_FOUND;
    }

    if ( Data8 == 0x7f ) {
        return EFI_NOT_FOUND;
    }

    return EFI_SUCCESS;
}

                         // IDE_HP_SUPPORT
//---------------------------------------------------------------------------

#ifdef Debug_Level_3
//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	PrintIdeDeviceInfo
//
// Description:	Prints Debug Level 3 Trace Messages
//
// Input:
//	IN IDE_BUS_PROTOCOL			*IdeBusInterface
//
// Output:
//	EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
void PrintIdeDeviceInfo(
    IDE_BUS_PROTOCOL *IdeBusInterface )
{
    UINT16 Data8;
    UINT16 *pIdentifyData;

    //		Print the Channel and Device Number
    EfiDebugPrint( -1, "-----------------IDE Device Info Start-----------------\n" );
    EfiDebugPrint( -1, "Channel   : %x   Device    : %x\n", IdeBusInterface->IdeDevice.Channel, IdeBusInterface->IdeDevice.Device );
    EfiDebugPrint( -1, "PIOMode   : %x   UDMAMode  : %x\n", IdeBusInterface->IdeDevice.PIOMode, IdeBusInterface->IdeDevice.UDma );
    EfiDebugPrint( -1, "SWDMAMode : %x   MWDMAMode : %x\n", IdeBusInterface->IdeDevice.SWDma,   IdeBusInterface->IdeDevice.MWDma );
    EfiDebugPrint( -1, "IORDY		: %x   \n",                  IdeBusInterface->IdeDevice.IORdy );
    pIdentifyData = (UINT16*) &(IdeBusInterface->IdeDevice.IdentifyData);

    for ( Data8 = 0; Data8 < 0xff; Data8 += 4 )
    {
        EfiDebugPrint( -1, "%X %X %X %X\n", pIdentifyData[Data8 + 0], pIdentifyData[Data8 + 1], pIdentifyData[Data8 + 2], pIdentifyData[Data8 + 3] );
    }
        EfiDebugPrint( -1, "-----------------IDE Device Info End-------------------\n" );
}

#endif          /* Debug_Level_3 */

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	CheckAhciMode
//
// Description:	Checks If the controller is in AHCI MODE.
//
// Input:
//	IDE_BUS_PROTOCOL			*IdeBusInterface;
//
// Output:
//	BOOLEAN                     TRUE  - AHCI Mode
//                              FALSE - IDE Mode
//
// Modified:
//
// Referrals:
//
// Notes:
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN CheckAhciMode(
    IN IDE_BUS_PROTOCOL *IdeBusInterface )
{
    EFI_PCI_IO_PROTOCOL *PciIO;
    UINT8               PciConfig[0x40];
    BOOLEAN             AhciFlag = FALSE;

    PciIO = IdeBusInterface->PciIO;
    PciIO->Pci.Read(
        PciIO,
        EfiPciIoWidthUint8,
        0,
        sizeof (PciConfig),
        PciConfig );

    AhciFlag = (BOOLEAN)((PciConfig [IDE_SUB_CLASS_CODE] & SCC_AHCI_CONTROLLER) ? TRUE : FALSE );

    return AhciFlag;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	IssueFreezeLockCommand
//
// Description:	Issue the Freeze lock command.
//
// Input:
//	IDE_BUS_PROTOCOL			*IdeBusInterface;
//
// Output:
//
// Modified:
//
// Referrals:
//
// Notes:
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS IssueFreezeLockCommand(
    IN IDE_BUS_PROTOCOL *IdeBusInterface )
{
    EFI_STATUS Status = EFI_SUCCESS;

    if ( IdeBusInterface->IdeDevice.IdentifyData.Command_Set_Supported_82 & 0x2 ) {
        Status = IdeNonDataCommand( IdeBusInterface, 0, 0,
                                    0, 0, 0,
                                    IdeBusInterface->IdeDevice.Device << 4,
                                    SECURITY_FREEZE_LOCK );
        //    
        //Update the Identify device buffer
        //
        GetIdentifyData( IdeBusInterface, &(IdeBusInterface->IdeDevice));
    }
    return Status;
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
