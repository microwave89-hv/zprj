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

//****************************************************************************
// $Header: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Core/EM/CSM/CsmHwInfo.c 1     7/31/17 4:55a Chienhsieh $
//
// $Revision: 1 $
//
// $Date: 7/31/17 4:55a $
//
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Core/EM/CSM/CsmHwInfo.c $
// 
// 1     7/31/17 4:55a Chienhsieh
// [TAG]  		EIP184371
// [Description]  	Filter the DiskInfo protocols while creating HddInfo
// [Files]  		CsmHwInfo.c
// 
// 114   8/07/14 12:44p Fasihm
// [TAG]           EIP180683
// [Category]      Improvement
// [Severity]      Normal
// [Symptom]       Aptio 4 CSM: CSM build error when disabling
// X64_SUPPORT.
// [Solution]      Changed file to fix the build error.
// [Files]
//         Core\EM\CSM\CsmBsp.c
//         Core/EM/CSM/CsmHwInfo.c
// 
// 113   8/06/14 5:21p Fasihm
// [TAG]           EIP180688
// [Category]      Improvement
// [Severity]      Normal
// [Symptom]       Aptio 4 CSM: PMM high memory life cycle.
// [Solution]      Changed file to address the PMM high memory life cycle.
// [Files]
//         Core/EM/CSM/CsmHwInfo.c
// 
// 112   8/06/14 3:21p Fasihm
// [TAG]           EIP180674
// [Category]      Bug Fix
// [Severity]      Normal
// [Symptom]       Aptio 4 CSM: CSM16: RT PCI function find_device should
// skip buses that do not exist.
// [Solution]      find_device function in RT-PCI.ASM has been modified to
// look for the device on the buses that are physically present in the
// system.
// [Files]
//         Addon/AmiLegacy16.bin
//         Core/EM/CSM/CSM.h
//         Core/EM/CSM/CsmHwInfo.c
// 
// 111   8/06/14 12:31p Fasihm
// [TAG]           EIP180666
// [Category]      Bug Fix
// [Severity]      Normal
// [Symptom]       Aptio4: Sata boot options need to be distinguished when
// there are more than one controller.
// [Solution]      While displaying Boot option in the Set up screen,
// Proposed to display in format ( C<Controller Number> :: P<Port Number>
// - Model Number).
// [Files]
//         Core/EM/CSM/CSM.h
//         Core/EM/CSM/CsmHwInfo.c
// 
// 110   12/18/12 1:44p Olegi
// [TAG]  		EIP108682
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Invalid Error Code from CSM Functions
// [RootCause]  	BIT31 is used as error indication
// [Solution]  	use EFI_ERROR_BIT macro instead of BIT31
// [Files]  		CSM.c
// CsmHwInfo.c
// 
// 109   12/12/12 2:54p Olegi
// [TAG]  		EIP109283
// [Category]  	Bug Fix
// [Symptom]  	PCI RT32 last bus improperly reported
// [RootCause]  	The last PCI bus is reported based on the chipset
// specific PCI bus configuration.
// [Solution]  	Update RT32 binary with the last bus obtained from PCI Bus
// driver.
// [Files]  		CsmHwInfo.c, rt32core.asm
// 
// 108   6/25/12 3:59p Olegi
// [TAG]  		EIP90257
// [Category]  	Improvement
// [Description]  	In CSM, don't clear allocated memory below 640K - added
// ClearFreeMemory function
// [Files]  		CsmOpROM.c
// CSM.c
// CsmHwInfo.c
// 
// 107   2/09/12 10:19a Olegi
// [TAG]  		EIP71972
// Correction to the original EIP71972 resolution: Slave IDE device was
// not getting proper drive handle.
// 
// 106   11/04/11 12:39p Olegi
// [TAG]  		EIP74722
// [Category]  	Improvement
// [Description]  	IDE drive information is not displayed correctly in the
// Boot page in Setup when both Master and Slave drives are connected
// [Files]  		CsmHwInfo.c
// 
// 105   10/28/11 9:24a Olegi
// [TAG]  		EIP71972
// [Category]  	Improvement
// [Description]  	In some cases HddInfo information is not properly used
// to create BBS entry.
// Cases are:
// - slave drive appears before master in DisdInfo hanle array
// - higher controller PCI function appears before lower function in the
// DiskInfo list
// [Files]  		csmhwinfo.c
// 
// 104   5/04/11 2:15p Olegi
// [TAG]  		EIP59632
// [Category]  	Improvement
// [Description]  	Removed the break from for loop in
// UpdateCsm16Configuration; this allows to finish all COM data
// initialization.
// [Files]  		CsmHwInfo.c
// 
// 103   4/11/11 12:56p Olegi
// [TAG]  		EIP56926
// [Category]  	Improvement
// [Description]  	Added Primary/Secondary Master/Slave information in the
// drive string.
// [Files]  		csmhwinfo.c
// 
// 102   2/04/11 10:19a Olegi
// [TAG]  		EIP53139
// [Category]  	Improvement
// [Description]  	Typo corrected
// [Files]  		csmhwinfo.c
// 
// 101   12/03/10 12:43p Olegi
// [TAG]  		EIP48471
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	COM Port addresses are not filled in correctly in BDA when
// COM 0(First COM port) disabled in setup.
// [RootCause]  	For the COM port resource details in BDA, we should not
// depend on the UID of the Com port.
// [Solution]  	1) Get the 1st COM port details and fill the details in
// CSm16bootable , BDA 40:0 and increment Serial Port count in 40:0x10.
// 2) Get the 2nd Com port details and fill the details in CSm16bootable ,
// BDA 40:2 and increment Serial Port count in 40:0x10..Continue this for
// 4 com ports.
// [Files]  		CsmHwInfo.c
// CsmLib.c
// 
// 100   11/08/10 9:06a Olegi
// Added CloseEvent call in UpdateLastPciBus callback function.
// 
// 99    8/17/10 3:10p Olegi
// Fixes discovered by Klockwork II engine: EIP37977
// 
// 98    7/16/10 12:12p Olegi
// EIP39395: Update CSM16 header checksum after LastPciBus field of it has
// been changed.
// 
// 97    6/18/10 10:29a Olegi
// EIP39149: Bugfix in UpdatePciLastBusCallback function.
// 
// 96    5/07/10 5:04p Felixp
// Bug fix in GetSystemMemoryMap
// 
// 95    5/07/10 5:00p Felixp
// Minor improvement in GetSystemMemoryMap (EIP 38327): 
// use memory map descriptor size returned by the GetMemoryMap instead of
// hard-coded value.
// 
// 94    4/28/10 2:51p Oleksiyy
// EIP 35563  Fixed logic when looking for ACPI 1.1 only tables.
// 
// 93    1/12/10 11:46a Olegi
// Copyright message updated.
// 
// 92    12/28/09 7:46a Olegi
// Added GetLptResource function.
// 
// 91    12/28/09 7:33a Olegi
//
// 90    12/08/09 9:52a Olegi
//
// 89    12/01/09 11:38a Olegi
// Bugfix in EnableDisableNmi function.
//
// 88    8/18/09 2:02p Rameshr
// AhciBus driver doesn't work for Multi Entry.
// Ahci Int13 initilization code moved from AhciBus to CsmHwinfo.c
// EIP: 25369
//
// 87    8/06/09 11:42a Olegi
// MaxPciBus reporting change: do not report FF; this is XP limitation,
// EIP#24852.
//
// 86    6/16/09 4:11p Olegi
// Generic modifications to update LastPciBus field in
// EFI_COMPATIBILITY16_TABLE.
//
// 85    6/16/09 10:09a Olegi
// Resolved the incompatibility with the GenericSio.h definitions.
//
// 84    6/05/09 10:32a Olegi
// EIP20813 - make IRQ7 handler execute from E000 segment, this is the
// workaround for DOS problem, that will take over IRQ7 handler if it is
// located in F000.
//
// 83    4/02/09 2:12p Olegi
// Removed the hardcoding of COM port base address/interrupt.
//
// 82    3/13/09 5:23p Olegi
// Modifications in GetAtaAtapiInfo():
// - removed checking if ABAR (PciCfg[24h]) is 0: under the condition
// where Subclass code is 6 this checking does not make sense
// - added the clarification of checking for SATA device path vs. AE bit
//
// 81    12/02/08 10:20a Olegi
// Changed the logic of extended memory size calculation.
//
// 80    10/10/08 3:36p Olegi
//
// 79    6/04/08 11:09a Olegi
// Bugfix in the previous modification.
//
// 78    6/02/08 6:13p Olegi
// Modified GetAtaAtapiInfo to handle non-IDE mass storage controllers.
//
// 77    3/28/08 3:01p Olegi
// Bugfix in GetAtaAtapiInfo for AHCI enabled controller.
//
// 76    2/25/08 4:48p Olegi
// GetAtaAtapiInfo is modified to handle the situation when SATA
// controller is in RAID mode and RAID OpROM is not handling all connected
// devices (CDROM).
//
// 75    12/10/07 1:34p Olegi
// Bug in the previous checkin is fixed.
//
// 74    12/10/07 12:27p Olegi
// Modified AHCI controller checking.
//
// 73    12/04/07 11:07a Olegi
//
// 72    11/07/07 10:44a Olegi
// Fix in GetExtendedMemSize function: if the amount of memory is 4GB or
// more, some memory is remapped above 4GB by the chipset. In this case
// this function will return the amount of memory before the remapped
// area.
//
// 71    10/02/07 10:34a Olegi
// Modified GetFDDStatus() routine to properly use IsSioDevicePluggedIn().
//
// 2     7/17/07 6:17p Fasihm
//
// 69    6/26/07 9:59a Olegi
// MMIO regions with runtime attribute set will have the corresponding
// E820 reserved entry.
//
// 68    6/18/07 5:46p Olegi
//
// 67    6/06/07 8:16a Olegi
// Added CSM_CREATES_ATA_ATAPI_STRINGS dependency in CreateDriveString
// function.
//
// 66    6/04/07 12:34p Olegi
//
// 65    6/02/07 10:26a Olegi
// Shadow size correction.
//
// 64    5/18/07 11:46a Olegi
// Changed setting BIT2 in 410h (legacy mouse present bit) in
// UpdateCsm16Configuration to avoid clearing this bit if it is already
// set.
//
// 63    5/09/07 1:56p Olegi
//
// 62    4/27/07 5:13p Olegi
// CSM.CHM file preparation.
//
// 61    4/13/07 9:40a Olegi
//
// 60    3/29/07 5:44p Olegi
// Modification in UpdateE820Map function to accomodate Legacy Redirection
// data area.
//
// 59    12/15/06 2:09p Olegi
// Bugfix in DiskInfoHandles usage.
//
// 58    12/14/06 11:06a Olegi
// Adding AGGRESSIVELY_JOINED_E820_ENTRIES flag.
//
// 57    12/12/06 5:33p Olegi
// DiskInfo handles inserted in BBS table as IBV1/IBV2.
//
// 56    9/26/06 4:19p Olegi
// GetFDDStatus is modified to make default number of FDDs 0.
//
// 55    9/20/06 3:11p Olegi
//
// 54    9/13/06 9:34a Felixp
//
// 53    9/13/06 9:32a Felixp
//
// 52    9/12/06 6:10p Markw
// Update EFI_TO_COMPATIBILITY16_BOOT_TABLE structure to UINT32 instead of
// pointer. This structure is used for CSM16 which expects 4 byte
// pointers.
//
// 51    8/28/06 9:49a Olegi
// Bugfix in InstallLegacyMassStorageDevices routine.
//
// 50    8/14/06 11:24a Olegi
//
// 49    8/04/06 12:05p Olegi
// E820 table optimization added.
//
// 48    7/28/06 4:43p Olegi
//
// 47    5/16/06 1:57p Olegi
//
// 45    5/04/06 10:55a Robert
//
// 44    5/04/06 9:42a Olegi
// Removed the logic that fixes the location of PATA/SATA in BBS table.
//
// 43    5/03/06 3:42p Robert
// Added the code to sort out the DiskInfo handles so that PATA goes
// first, SATA next.
//
// 40    3/31/06 2:30p Olegi
//
// 39    3/13/06 2:32p Felixp
//
// 38    12/14/05 4:16p Olegi
// NMI enable/disable changes.
//
// 37    11/29/05 11:38a Olegi
// Bugfix - not all ATAPI devices are CDROMs, as it used to be considered
// in the GetAtaAtapi routine.
//
// 35    10/17/05 8:56a Olegi
//
// 34    10/13/05 6:25p Olegi
//
// 33    10/11/05 11:56a Olegi
//
// 32    10/10/05 7:27p Olegi
//
// 31    10/07/05 5:16p Olegi
//
// 30    10/06/05 8:11p Felixp
//
// 29    10/06/05 11:52a Felixp
//
// 28    9/30/05 6:27p Olegi
// VC7.1 compatibility issues solved.
//
// 27    9/29/05 5:20p Olegi
//
// 26    9/28/05 8:30a Olegi
//
// 25    9/21/05 3:56p Olegi
//
// 24    9/09/05 6:04p Olegi
//
// 23    9/09/05 11:19a Olegi
//
// 22    6/30/05 7:55p Olegi
// PS/2 mouse handling reported correctly.
//
// 21    6/21/05 12:12p Olegi
// LegacyBios and LegacyBiosPlatform are combined into one FFS.
//
// 20    5/12/05 5:15p Yakovlevs
//
// 19    4/22/05 2:10p Olegi
//
// 19    4/21/05 9:00a Olegi
// Modified the rule for inserting E820 entries for regions >4GB
//
// 18    4/19/05 11:12a Olegi
//
// 17    3/30/05 12:28p Olegi
// InstallIdePciHandler - IDE control port calculation corrected.
//
// 16    3/04/05 1:54p Mandal
//
//**********************************************************************
//<AMI_FHDR_START>
//
//  Name:           CsmHwInfo.c
//  Description:    Hardware Information routines
//
//<AMI_FHDR_END>
//****************************************************************************

#include "token.h"
#include "csm.h"
#include <Protocol/PciIo.h>
#include <Protocol/PDiskInfo.h>
#include <Protocol/DevicePath.h>
#include <Protocol/PciRootBridgeIo.h>
#include <Protocol/PIdeController.h>
#include <Protocol/BlockIo.h>
#include <AmiDxeLib.h>
#include "pci.h"
#include "biosdata.h"
#include <Protocol/CsmPlatform.h>
#include <AcpiRes.h>
#ifdef AhciSrc_SUPPORT
#if AhciSrc_SUPPORT
#include <Protocol/LegacyAhci.h>
#endif
#endif

#define MASTER_DRIVE        0
#define SLAVE_DRIVE         1
#define PRIMARY_CHANNEL     0
#define SECONDARY_CHANNEL   1
#define MAX_IDE_PCI_CONTROLLER (MAX_IDE_CONTROLLER << 1)

// Controller information where IDE devices are connected
IDE_CONTROLLER_INFO_STRUC          IdeControllerInfo[MAX_IDE_PCI_CONTROLLER];
UINT8                              gIdeController = 0;

UINT16 aInstalledPciIrq[MAX_IDE_PCI_CONTROLLER];

EFI_GUID    gDiskInfoProtocol = EFI_DISK_INFO_PROTOCOL_GUID;
EFI_GUID    gSataControllerProtocol = SATA_CONTROLLER_PROTOCOL_GUID;
EFI_GUID    gAcpiRsdtPtr = ACPI_20_TABLE_GUID;
EFI_GUID    gAcpiRsdtPtr1_0 = ACPI_10_TABLE_GUID;
EFI_GUID    gSmbiosTable = SMBIOS_TABLE_GUID;

typedef struct {
  ATAPI_IDENTIFY    *IdentifyPtr;
  EFI_HANDLE        DriveHandle;            
} CSM_DRIVE_HANDLE_LIST;

CSM_DRIVE_HANDLE_LIST DriveHandle[MAX_IDE_CONTROLLER*2] ;

EFI_STATUS UpdateCsm16Configuration(EFI_TO_COMPATIBILITY16_BOOT_TABLE*);
VOID GetExtendedMemSize(UINT32*);
VOID GetSioDeviceStatus(SIO_DEV_STATUS *devices);
BOOLEAN IsSioDevicePluggedIn(SIO_DEV_STATUS *plugged_devices, EFI_HANDLE *Handle);

extern  BIOS_INFO *CoreBiosInfo;
extern  BOOLEAN gIsMassStorageInstalled;
extern  UINTN gMaxOpRomAddress;


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:        UpdateCsm16Configuration
//
// Description:
//  This function updates Csm16BootTable and BDA. It can be called multiple
//  times during POST as the new hardware is discovered and configured.
//
// Input:
//  Csm16BootTable  pointer to EFI_TO_COMPATIBILITY16_BOOT_TABLE
//
// Output:
//  EFI_SUCCESS Table is updated successfully.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
UpdateCsm16Configuration(
    IN OUT EFI_TO_COMPATIBILITY16_BOOT_TABLE    *Csm16BootTable
)
{
    SIO_DEV_STATUS sio_devices;
    SIO_DEV_STATUS sio_devices_plugged_in;
    BDA_DATA    *bda;
    UINT16      machineconfig = 0;
    EFI_HANDLE  Handle;
    EFI_STATUS  Status;
    UINT16      Address;
    UINT8       Irq;
    UINT8       ComPortIndex;
    
    //
    // Fill in EFI_TO_COMPATIBILITY16_BOOT_TABLE
    // Note: CSM specification 0.96 defines the pointer as UINT32 - it is
    //       assumed BbsTable pointer is within 4GB address space.
    Csm16BootTable->BbsTable = (UINT32)CoreBiosInfo->BbsTable;
    Csm16BootTable->NumberBbsEntries = CoreBiosInfo->BbsEntriesNo;

    //
    // Updade SIO status in Csm16BootTable->SioData and in BDA
    //
    bda = (BDA_DATA*)((UINTN) 0x400);

// The following definitions are from the up-to-date GenericSio.h
// they can be used after GenericSio.h will be labeled with these changes.
//#define SIO_DEV_COM3        0x1000
//#define SIO_DEV_COM4        0x2000

    sio_devices.DEV_STATUS = SIO_DEV_COM1 | SIO_DEV_COM2 | 0x1000 | 0x2000 |
                            SIO_DEV_LPT  | SIO_DEV_FDC | SIO_DEV_PS2MS;
    GetSioDeviceStatus(&sio_devices);

    if (sio_devices.Fdd) {
        Csm16BootTable->SioData.Floppy.NumberOfFloppy = 1;
        machineconfig |= 1;
    }

    for(ComPortIndex = 0; ComPortIndex < 4; ComPortIndex ++){
        Status = GetComPortResource(ComPortIndex, &Address, &Irq);
        if (!EFI_ERROR(Status))
        {
            Csm16BootTable->SioData.Serial[ComPortIndex].Address = Address;
            Csm16BootTable->SioData.Serial[ComPortIndex].Irq = Irq;
            Csm16BootTable->SioData.Serial[ComPortIndex].Mode = DEVICE_SERIAL_MODE_NORMAL;
            bda->rs_232_address[ComPortIndex] = Address;
            machineconfig += 0x200;
        }
    }
    // Note that SIO_DEV_STATUS limits the number of LPT to one
    if (sio_devices.Lpt) {
        Status = GetLptResource(&Address, &Irq);
        if (!EFI_ERROR(Status)){
           Csm16BootTable->SioData.Parallel[0].Address = Address;
           Csm16BootTable->SioData.Parallel[0].Irq = Irq;
           Csm16BootTable->SioData.Parallel[0].Mode = DEVICE_PARALLEL_MODE_MODE_OUTPUT_ONLY;
           bda->printer_address[0] = Address;
           machineconfig |= 0x4000;
       }
    }

    if ((bda->machine_config & 4) || sio_devices.Ps2Mouse) {
        machineconfig |= 0x4;

        sio_devices_plugged_in.DEV_STATUS = 0;
        sio_devices_plugged_in.Ps2Mouse = 1;
        if (IsSioDevicePluggedIn(&sio_devices_plugged_in, &Handle)) {
            Csm16BootTable->SioData.MousePresent = 1;
        }
    }

    machineconfig |= 2; // coprocessor is always reported present

    bda->machine_config = machineconfig;

    GetExtendedMemSize(&Csm16BootTable->OsMemoryAbove1Mb);
    Csm16BootTable->NumberE820Entries = CoreBiosInfo->NumberE820Entries;

    //
    // Get ACPI&SMBIOS pointers
    //
//TODOx64: What is these pointers are more the 4G in 64 bit mode?
//CSM specification 0.96 defines the pointers as UINT32
    Csm16BootTable->AcpiTable = (UINT32)GetEfiConfigurationTable(pST, &gAcpiRsdtPtr);
    if (Csm16BootTable->AcpiTable == 0)
         Csm16BootTable->AcpiTable = (UINT32)GetEfiConfigurationTable(pST, &gAcpiRsdtPtr1_0);

    TRACE((-1,"CSM - GetEfiConfigurationTable: ACPI table is at %x\n", Csm16BootTable->AcpiTable));

    Csm16BootTable->SmbiosTable = (UINT32)GetEfiConfigurationTable(pST, &gSmbiosTable);

    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// FUNCTION:  GetFDDStatus
//
// DESCRIPTION: This function returns the status of the floppy drive.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

FDD_STATUS GetFDDStatus()
{
    SIO_DEV_STATUS      sio_devices;
    EFI_STATUS          Status;
    FDD_STATUS          DriveStatus = NO_FLOPPY_DRIVE;
    EFI_HANDLE          Handle;
    EFI_BLOCK_IO_PROTOCOL *blkiop;

    sio_devices.DEV_STATUS = 0;
    sio_devices.Fdd = 1;

    if (!IsSioDevicePluggedIn(&sio_devices, &Handle)) return NO_FLOPPY_DRIVE;

    Status = pBS->HandleProtocol(Handle,&gEfiBlockIoProtocolGuid, &blkiop);
    ASSERT_EFI_ERROR(Status);

    if (!EFI_ERROR(Status)) {
        DriveStatus = blkiop->Media->MediaPresent? FLOPPY_INSERTED : NO_FLOPPY_DISK;
    }

    return DriveStatus;

}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// FUNCTION:  InstallIdePciHandler
//
// DESCRIPTION: This function makes InstallPciHandler CSM16 call
//
// PARAMETERS:  PCI IDE controller data needed for the IRQ installation
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
InstallIdePciHandler(
    HDD_INFO* HddInfo1,
    HDD_INFO* HddInfo2
)
{
    EFI_IA32_REGISTER_SET RegSet;
    EFI_STATUS Status;
    UINT8 i;
    EFI_LEGACY_INSTALL_PCI_HANDLER *PciHandlerData = &CoreBiosInfo->Thunk->PciHandler;
    UINT16 wPciDev = 0xFFFF;
    BOOLEAN IsNativeMode;
    //
    // Check whether PCI IRQ handler for this PCI device has been installed, exit if so.
    //
    for (i = 0; i < MAX_IDE_PCI_CONTROLLER; i++) {
        wPciDev = (UINT16)((HddInfo1->Bus << 8) | (HddInfo1->Device << 3) | HddInfo1->Function);
        if (!aInstalledPciIrq[i]) break;    // New entry found
        if (wPciDev == aInstalledPciIrq[i]) return EFI_SUCCESS;
    }
    ASSERT(i < MAX_IDE_PCI_CONTROLLER);
    if (i == MAX_IDE_PCI_CONTROLLER) return EFI_OUT_OF_RESOURCES;   // Error - no free entries

    //
    // Prepare PCI handler data in Thunk memory
    //
    PciHandlerData->PciBus = (UINT8)HddInfo1->Bus;
    PciHandlerData->PciDeviceFun = (UINT8)((HddInfo1->Device << 3) | HddInfo1->Function);
    PciHandlerData->PciSegment = 0;
    PciHandlerData->PciClass = PCI_CL_MASS_STOR;
    PciHandlerData->PciSubclass = PCI_CL_MASS_STOR_SCL_IDE;
    IsNativeMode = HddInfo1->HddIrq != 14;
    PciHandlerData->PciInterface = (IsNativeMode)?0x8F:0x8A;

    //
    // Primary section
    //
    PciHandlerData->PrimaryIrq = HddInfo1->HddIrq;
    PciHandlerData->PrimaryReserved = 0;
    PciHandlerData->PrimaryControl = HddInfo1->ControlBaseAddress;
    PciHandlerData->PrimaryBase = HddInfo1->CommandBaseAddress;
    PciHandlerData->PrimaryBusMaster = HddInfo1->BusMasterAddress;
    //
    // Secondary section
    //
    PciHandlerData->SecondaryIrq = HddInfo2->HddIrq;
    PciHandlerData->SecondaryReserved = 0;
    PciHandlerData->SecondaryControl = HddInfo2->ControlBaseAddress;
    PciHandlerData->SecondaryBase = HddInfo2->CommandBaseAddress;
    PciHandlerData->SecondaryBusMaster = HddInfo2->BusMasterAddress;

    pBS->SetMem(&RegSet, sizeof (EFI_IA32_REGISTER_SET), 0);
    RegSet.X.AX = Compatibility16InstallPciHandler;
    RegSet.X.ES = EFI_SEGMENT (PciHandlerData);
    RegSet.X.BX = EFI_OFFSET (PciHandlerData);

    Status = CoreBiosInfo->iRegion->UnLock (CoreBiosInfo->iRegion,
        (UINT32)gMaxOpRomAddress+1,
        0xFFFFF-(UINT32)gMaxOpRomAddress,
        NULL
    );
    ASSERT_EFI_ERROR(Status);

    FarCall86 (&CoreBiosInfo->iBios,
                CoreBiosInfo->Csm16EntrySeg,
                CoreBiosInfo->Csm16EntryOfs,
                &RegSet,
                NULL,
                0);
    Status = (RegSet.X.AX)? ((RegSet.X.AX & 0x7FFF) | EFI_ERROR_BIT) : EFI_SUCCESS;
    ASSERT_EFI_ERROR(Status);
    if (!EFI_ERROR(Status)) {
        aInstalledPciIrq[i] = wPciDev;  // Save the new PCI device entry
    }

    Status = CoreBiosInfo->iRegion->Lock (CoreBiosInfo->iRegion,
        (UINT32)gMaxOpRomAddress+1,
        0xFFFFF-(UINT32)gMaxOpRomAddress,
        NULL
    );
    ASSERT_EFI_ERROR(Status);

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure:    UpdateIdeControllerInfo
//
// Description:  This function will check if the BusDevFunc is existing in 
//               Idecontrollerinfo structure array,if it exist then it return. 
//               If it is not exist, it will add BusDevFunc into IdeControllerInfo structure.
//
// Input:        IdeBusDevFun  - It contain the BusDevFunc number for a device
//
// Output:       VOID
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

void UpdateIdeControllerInfo(UINT16 IdeBusDevFun)
{
    UINTN   i;
    
    for(i=0; i < gIdeController ; i++) {
        if(IdeControllerInfo[i].BusDevFun == IdeBusDevFun) {
            /// Controller detected 
            return;
        }
    }

    //
    // A new controller is found so BusDevFunc and ControllerNo is added
    // into the array of structure.
    //
    IdeControllerInfo[gIdeController].BusDevFun = IdeBusDevFun;
    IdeControllerInfo[gIdeController].ControllerNo = gIdeController++;
    
    return;
    
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// FUNCTION:  GetAtaAtapiInfo
//
// DESCRIPTION: This function collects the information about currently connected
//              ATA/ATAPI devices. It stores this information in the HDD_INFO data
//              structure and installs legacy interrupt handlers.
//
// PARAMETERS:  DiskInfoHandles - array of handles with DiskInfo protocol
//              Info - pointer to HDD_INFO array to be updated
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS GetAtaAtapiInfo(
    IN OUT  EFI_HANDLE  **DiskInfoHandles,
    OUT HDD_INFO* Info
)
{
    EFI_STATUS  Status;
    UINTN       i, j, HandlesNo;
    EFI_DISK_INFO_PROTOCOL      *pDiskInfo;
    EFI_DEVICE_PATH_PROTOCOL    *pDevicePath;
    EFI_PCI_IO_PROTOCOL         *pPciIo;
    EFI_HANDLE  Handle;
    UINTN       Seg, Bus, Dev, Func;
    HDD_INFO    *HddInfo;
    UINT32      PriSec, MasterSlave;
    UINT8       pciCfg[0x40];
    UINT16      priCmdIoAddr, secCmdIoAddr;
    UINT16      priCtlIoAddr, secCtlIoAddr;
    UINT16      bmIoAddr;
    UINT8       priIrq, secIrq;
    BOOLEAN     IsNativeMode, IsAtapiDevice, IsSataDevice;
    ATAPI_IDENTIFY  *pAtapiIdentifyBuffer;
    UINT32      DataCount = sizeof (ATAPI_IDENTIFY);
    CSM_DRIVE_HANDLE_LIST *pDriveHandle = DriveHandle;
	
    // Clear drive handles list
    pBS->SetMem(pDriveHandle, sizeof(CSM_DRIVE_HANDLE_LIST)*MAX_IDE_CONTROLLER*2, 0);

    //
    // Get the list of DiskInfo handles
    //
    Status = pBS->LocateHandleBuffer(
                    ByProtocol,
                    &gDiskInfoProtocol,
                    NULL,
                    &HandlesNo,
                    DiskInfoHandles);
    if (EFI_ERROR(Status)) return EFI_NOT_FOUND;


    for (i = 0; i < HandlesNo; i++) {
// [ EIP184371 ]+>
        // Check DiskInfo.Interface field
        static EFI_GUID DiIntrfGuid = EFI_DISK_INFO_IDE_INTERFACE_GUID;

        Status = pBS->HandleProtocol (
            (*DiskInfoHandles)[i],
            &gDiskInfoProtocol,
            &pDiskInfo);    // Get DiskInfo protocol
        ASSERT_EFI_ERROR (Status);

        
        if (guidcmp(&pDiskInfo->Interface, &DiIntrfGuid)) continue;
// [ EIP184371 ]+<
        
        Status = pBS->HandleProtocol ((*DiskInfoHandles)[i],
            &gEfiDevicePathProtocolGuid,
            (VOID*)&pDevicePath);
        ASSERT_EFI_ERROR(Status);

        //
        // Get PCI device/function info out of DiskInfo device path
        //
        Status = pBS->LocateDevicePath(
            &gEfiPciIoProtocolGuid,    // Search key
            &pDevicePath,       // Will be updated with PCI device path
            &Handle);           // Will be updated with PCI device handle
        if (EFI_ERROR(Status)) continue;    // PCI device path is not found

        // check if SataController protocol is installed
        Status = pBS->HandleProtocol (
            Handle,
            &gSataControllerProtocol,
            &pPciIo);           //Dummy. Interface is null.
        IsSataDevice = !(BOOLEAN)EFI_ERROR(Status);

        Status = pBS->HandleProtocol (
            Handle,
            &gEfiPciIoProtocolGuid,
            &pPciIo);           // Get PciIo protocol
        ASSERT_EFI_ERROR (Status);

// [ EIP184371 ]+>
//        Status = pBS->HandleProtocol (
//            (*DiskInfoHandles)[i],
//            &gDiskInfoProtocol,
//            &pDiskInfo);    // Get DiskInfo protocol
//        ASSERT_EFI_ERROR (Status);
// [ EIP184371 ]+<

        pDiskInfo->WhichIde(pDiskInfo, &PriSec, &MasterSlave);  // Device/Channel info
        Status = pPciIo->GetLocation(pPciIo, &Seg, &Bus, &Dev, &Func);   // Location on PCI bus      
        ASSERT_EFI_ERROR(Status);                         
       
        /// Update controller Number for the IDE device
        UpdateIdeControllerInfo(((UINT16)Bus<<8) + ((UINT16)Dev<<3) + (UINT16)Func);
                
        pPciIo->Pci.Read(
            pPciIo,
            EfiPciIoWidthUint32,
            0,
            0x10,
            &pciCfg);   // Get 40h bytes of PCI device configuration registers

        if (pciCfg[0xB] != PCI_CL_MASS_STOR) continue;

        if (pciCfg[0xA] == PCI_CL_MASS_STOR_SCL_RAID) continue;

        if (pciCfg[0xA] == 6) {

            EFI_DEVICE_PATH_PROTOCOL *DevicePath;
            //
            // SATA controller is in AHCI mode; we can only handle it if
            // AE bit is not set and controller is operated using legacy ATA/ATAPI
            // mechanisms, not AHCI descriptors. Verify this by checking if
            // SATA device path is installed on this device.
            //
            // Note: previously we were checking for the status of AE in controller's
            // MMIO (ABAR at PciCfg[0x24]+4, Bit31). It was found that for some
            // controllers it is not safe to access MMIO directly. Example: Intel
            // ESB2 controller loses index/data access functionality after any
            // AHCI MMIO register is read directly.
            //
            DevicePath = DPGetLastNode(pDevicePath);
            if (DevicePath->Type == MESSAGING_DEVICE_PATH &&
                DevicePath->SubType == MSG_USB_SATA_DP) {
                continue;
            }
        }

        IsNativeMode = pciCfg[9] & 1;

        if (IsNativeMode) { // for native mode get data from PCI config space
            priCmdIoAddr = *(UINT16*)&pciCfg[0x10] & 0xFFFE;
            secCmdIoAddr = *(UINT16*)&pciCfg[0x18] & 0xFFFE;
            priCtlIoAddr = (*(UINT16*)&pciCfg[0x14] & 0xFFFE) + 2;
            secCtlIoAddr = (*(UINT16*)&pciCfg[0x1C] & 0xFFFE) + 2;
            priIrq = secIrq = pciCfg[0x3C];
        }
        else {  // for legacy mode use hardcoded data
            priCmdIoAddr = 0x1F0;
            secCmdIoAddr = 0x170;
            priCtlIoAddr = 0x3F6;
            secCtlIoAddr = 0x376;
            priIrq = 0xE;
            secIrq = 0xF;
        }
        bmIoAddr =  *(UINT16*)&pciCfg[0x20] & 0xFFFE;

        //
        // All necessary HW data is received; the following loop searches for the
        // next available HddInfo, fills in HDD_INFO structure and installs legacy
        // PCI interrupt if needed.
        //
        for (j = 0, HddInfo = Info; j < MAX_IDE_CONTROLLER; j++, HddInfo++) {
            if (!HddInfo->Bus && !HddInfo->Device && !HddInfo->Function) {
                HddInfo->Status = HDD_PRIMARY;
                HddInfo->Bus = (UINT32)Bus;
                HddInfo->Device = (UINT32)Dev;
                HddInfo->Function = (UINT32)Func;
                HddInfo->CommandBaseAddress = priCmdIoAddr;
                HddInfo->ControlBaseAddress = priCtlIoAddr;
                HddInfo->BusMasterAddress = bmIoAddr;
                HddInfo->HddIrq = priIrq;
                HddInfo++;
                HddInfo->Status = HDD_SECONDARY;
                HddInfo->Bus = (UINT32)Bus;
                HddInfo->Device = (UINT32)Dev;
                HddInfo->Function = (UINT32)Func;
                HddInfo->CommandBaseAddress = secCmdIoAddr;
                HddInfo->ControlBaseAddress = secCtlIoAddr;
                HddInfo->BusMasterAddress = bmIoAddr+8;
                HddInfo->HddIrq = secIrq;
                if (PriSec == PRIMARY_CHANNEL) HddInfo--;
                break;
            }
            if (Bus == HddInfo->Bus && Dev == HddInfo->Device && Func == HddInfo->Function) {
                if (PriSec == SECONDARY_CHANNEL) HddInfo++;
                break;
            }
        }

        //
        // Copy the IDENTIFY_DRIVE information into appropriate HDD_INFO field
        //
        pAtapiIdentifyBuffer = HddInfo->IdentifyDrive;
        if (MasterSlave != MASTER_DRIVE) pAtapiIdentifyBuffer++;
        pDiskInfo->Identify(pDiskInfo, pAtapiIdentifyBuffer, &DataCount);
        pDriveHandle->IdentifyPtr = pAtapiIdentifyBuffer;
        pDriveHandle->DriveHandle = (*DiskInfoHandles)[i];
        pDriveHandle++;
        //
        // Check whether device is ATA or ATAPI - WORD 0 bits 14 and 15
        //
        IsAtapiDevice = (BOOLEAN)((*(UINT16*)pAtapiIdentifyBuffer & 0xC000) == 0x8000);
        //
        // Update HDD_INFO status
        //
        if (PriSec == PRIMARY_CHANNEL) {
            HddInfo->Status |= HDD_PRIMARY;
        } else {
            HddInfo->Status |= HDD_SECONDARY;
        }
        if (MasterSlave == MASTER_DRIVE) {
            if (IsAtapiDevice) {
                HddInfo->Status |= HDD_MASTER_ATAPI;
            } else {
                HddInfo->Status |= HDD_MASTER_IDE;
            }
        } else {    // SLAVE_DRIVE
            if (IsAtapiDevice) {
                HddInfo->Status |= HDD_SLAVE_ATAPI;
            } else {
                HddInfo->Status |= HDD_SLAVE_IDE;
            }
        }
        if (IsSataDevice) HddInfo->Status |= HDD_SATA_PATA;
        CoreBiosInfo->HddCount++;
    }

    return EFI_SUCCESS;
}

            //(EIP20813+)>
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:        SetINT0F_E0000
//
// Description: Change INT0F Vector To E000 Segment
//
// Output:      EFI_STATUS Success of failure of the operation.
//
// Notes:       If the IRQ7 vector is in F000 segment, MS-DOS will take over
//              the IRQ7 ISR and cause HDDs not working. This routine places IRQ7
//              handler in E000 segment to avoid this problem.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

#pragma pack(1)
typedef struct
{
    UINT8  Far_JMP;
    UINT32 Address;
}E0000_Int0f;
#pragma pack()

EFI_STATUS
SetINT0F_E0000()
{
    EFI_STATUS  Status;
    E0000_Int0f *P_E0000_Int0f;
    UINT32      LockUnlockAddr, LockUnlockSize;
    UINT32      *PInt15;

    PInt15=(UINT32*)(0x0f*4);

    //
    // Allocate legacy region in E000 segment; store SEG:OFS of the allocated
    // memory in global variables
    //
    Status =GetLegacyRegion(&CoreBiosInfo->iBios, sizeof(E0000_Int0f), E0000_BIT, 0x10, &P_E0000_Int0f);

    if(EFI_ERROR(Status)) return Status;

    UnlockShadow((UINT8*)P_E0000_Int0f, sizeof(E0000_Int0f), &LockUnlockAddr, &LockUnlockSize);

    P_E0000_Int0f->Far_JMP=0xEA;        //far jump
    P_E0000_Int0f->Address=*PInt15;     //save original vector
    *PInt15= EFI_SEGMENT(P_E0000_Int0f) * 0x10000 | EFI_OFFSET (P_E0000_Int0f); //Set New INT0F Vector

    LockShadow(LockUnlockAddr, LockUnlockSize);

    return EFI_SUCCESS;
}

            //<(EIP20813+)

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// FUNCTION:  InstallIdeInterrupts
//
// DESCRIPTION: This function installs PCI interrupts for all PATA and SATA
//              controllers.
//
// PARAMETERS:  HDD_INFO
//
// NOTES:       HDD_INFO is expected to be populated before this call.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS  InstallIdeInterrupts(
    IN HDD_INFO *HddInfo
)
{
    UINT8 j;
    UINT8 hdd_irq7_set=0;
    HDD_INFO *HddInfo1 = HddInfo;
    HDD_INFO *HddInfo2 = HddInfo;
    EFI_STATUS Status;

    for (j = 0; j < (MAX_IDE_CONTROLLER/2); j++) {
        HddInfo2 = HddInfo1+1;
        if ((HddInfo1->Status &
                (HDD_MASTER_ATAPI | HDD_SLAVE_ATAPI |
                    HDD_MASTER_IDE | HDD_SLAVE_IDE))||
            (HddInfo2->Status &
                (HDD_MASTER_ATAPI | HDD_SLAVE_ATAPI |
                    HDD_MASTER_IDE | HDD_SLAVE_IDE)))
        {
            Status = InstallIdePciHandler(HddInfo1, HddInfo2);
            ASSERT_EFI_ERROR(Status);

            //if (EFI_ERROR(Status)) return Status; //(EIP20813-)

                        //(EIP20813+)>

            if( HddInfo1->HddIrq==0x07 || HddInfo2->HddIrq==0x07)
                hdd_irq7_set=1;

            if (EFI_ERROR(Status)) break;

                        //<(EIP20813+)
        }
        HddInfo1+=2;
    }
                        //(EIP20813+)>
    if(hdd_irq7_set)
        SetINT0F_E0000();

                        //<(EIP20813+)
    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// FUNCTION:  CreateDriveString
//
// DESCRIPTION: This function prepares the description string for the ATA/ATAPI
//              drive and places its pointer in the BBS entry.
//
// PARAMETERS:  IdentifyDriveData - IDENTIFY_DRIVE data for this device
//              DriveDisplayName - pointer to the string to be updated
//              BbsDescStringOffset - pointer to the string description offset
//              in the corresponding BBS entry
//
// NOTE:        1) DriveDisplayName must be located below 1MB
//              2) BbsDescStringSegment is UINT16 followed by BbsDescStringOffset
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
CreateDriveString (
    IN UINT16   *IdentifyDriveData,
    IN UINT16   ChannelInfo,
    OUT DRIVE_DISPLAY_NAME  *DriveDisplayName,
    OUT UINT16  *BbsDescStringOffset,
    UINTN       DeviceAddress
)
{
#if CSM_CREATES_ATA_ATAPI_STRINGS
    UINT8   i, data8;
    UINT16  data16 = IdentifyDriveData[76];	
    UINT8   s[MAX_DRIVE_NAME] = {0};
    // Temp variable introduced in order to reduce the Code length
    UINTN    Temp = 0;

    if(gIdeController > 1) {
        pBS->CopyMem(&s[0], "xC::APAT     :",14);          // "PATA: "
        Temp = 4;
      
        /// find and replace the Controller Number in String
        for(i=0;i<gIdeController;i++) {
            if(IdeControllerInfo[i].BusDevFun == DeviceAddress) {            
                //// Controller for the AHCI Device found            
                s[0] = IdeControllerInfo[i].ControllerNo + 0x30; 
                break;
            }
        }  
    }    
    else {
        pBS->CopyMem(&s[0], "APAT     :",10);               // "PATA: "   
    }
      
    // Check Word76 for BIT1 and BIT2; set for SATA drives
    if ((data16 != 0xFFFF) && (data16 & 6)) {
        s[1 + Temp] = 'S';
    }

    if(ChannelInfo & HDD_PRIMARY) {
        s[7 + Temp]='P';
        if(ChannelInfo & (HDD_MASTER_IDE | HDD_MASTER_ATAPI )) {
            s[6 + Temp]='M';
        } else {
            s[6 + Temp]='S';
        }
    } else if(ChannelInfo & HDD_SECONDARY) {
        s[7 + Temp]='S';
        if(ChannelInfo & (HDD_MASTER_IDE | HDD_MASTER_ATAPI )) {
            s[6 + Temp]='M';
        } else {
            s[6 + Temp]='S';
        }
    }
    
    // Get the drive name out of IdentifyDrive data word 27..46 (upto 40 chars)
    pBS->CopyMem(&s[10 + Temp], IdentifyDriveData+27, MAX_DRIVE_NAME- (11+Temp) );
    // Swap the bytes
    for (i=0; i<MAX_DRIVE_NAME; i+=2) {
        data8=s[i];
        s[i]=s[i+1];
        s[i+1]=data8;
    }

    pBS->CopyMem(DriveDisplayName, s, MAX_DRIVE_NAME);
    // Update string pointer in BBS after converting it to SEG:OFS format
    *BbsDescStringOffset = (UINT16)(UINTN)DriveDisplayName;
    *(BbsDescStringOffset+1) = (UINT16)(((UINTN)DriveDisplayName >> 4) & 0xF000);
#endif
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// FUNCTION:  GetAtapiDeviceType
//
// DESCRIPTION: This function returns ATAPI device type depending on the information
//              provided by IDENDIFY_DRIVE data. It could call CSM platform functions
//              to return platform specific ATAPI device type or if the type is
//              selectable in System Setup.
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT16
GetAtapiDeviceType(
    IN ATAPI_IDENTIFY *IdentifyDriveData
)
{
    UINT16      DevType;
    EFI_STATUS  Status;
    CSM_PLATFORM_PROTOCOL *CsmPlatformProtocol;

    pBS->LocateProtocol(&gCsmPlatformProtocolGuid, NULL, &CsmPlatformProtocol);
    //
    // LocateProtocol will return CsmPlatformProtocol = NULL if protocol is not found.
    //
    if (CsmPlatformProtocol) {
        Status = CsmPlatformProtocol->GetAtapiDeviceType(CsmPlatformProtocol, IdentifyDriveData, &DevType);
        if (!EFI_ERROR(Status)) return DevType; // Identified
    }
    //
    // Use default, "generic" method of device identification
    //
    DevType = BBS_FLOPPY;

    if ((IdentifyDriveData->Raw[0] & 0x1F00) == 0x500)
    {
        DevType = BBS_CDROM;
    }
    return DevType;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:  GetDriveHandle
//
// Description:
//  This function searches for the IDE mass storage device handle in the list
//  of handles and returns the one that matches with the given IdentifyDrive
//  information.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_HANDLE  GetDriveHandle(ATAPI_IDENTIFY *IdentifyPtr)
{
    UINT8   i;
    for (i=0; i<MAX_IDE_CONTROLLER*2; i++){
        if (DriveHandle[i].IdentifyPtr == IdentifyPtr)
            return DriveHandle[i].DriveHandle;
    }

    return NULL;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// FUNCTION:  InstallLegacyMassStorageDevices
//
// DESCRIPTION: This function prepares BBS table, inserts FDD/IDE/SATA entries
//              in the table and calls CSM16->UpdateBbs function to bring up
//              non-BBS compliant entries as well.
//
// NOTE:        This function should be executed only once, when DiskInfo handles
//              are ready.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID InstallLegacyMassStorageDevices()
{
    HDD_INFO    *AtaAtapiInfo;
    UINT8       IdeCtl, Indx;
    EFI_STATUS  Status;
    UINT8       count = 0;
    EFI_HANDLE  *DiskInfoHandles = 0;

    BBS_TABLE   *BbsEntry = CoreBiosInfo->BbsTable;

    //
    // Insert ATA/ATAPI devices into CoreBiosInfo->Thunk->Csm16BootTable.HddInfo
    //
    for (Indx = 0; Indx < MAX_IDE_PCI_CONTROLLER; Indx++) aInstalledPciIrq[Indx] = 0;
    AtaAtapiInfo = CoreBiosInfo->Thunk->Csm16BootTable.HddInfo;

    Status = GetAtaAtapiInfo(&DiskInfoHandles, AtaAtapiInfo);

    if (!EFI_ERROR(Status)) {   // some IDE device are connected
        InstallIdeInterrupts(AtaAtapiInfo);
        //
        // Update BBS table with controller/device information
        //
        for (IdeCtl = 0; IdeCtl < MAX_IDE_CONTROLLER; IdeCtl++) {
            if (!(AtaAtapiInfo[IdeCtl].Status &
                ( HDD_MASTER_ATAPI | HDD_SLAVE_ATAPI | HDD_MASTER_IDE | HDD_SLAVE_IDE ))) {
                continue;
            }
            Indx = IdeCtl*2 + 1;    // 1st entry is taken for floppy

            BbsEntry[Indx].Bus = BbsEntry[Indx+1].Bus = AtaAtapiInfo[IdeCtl].Bus;
            BbsEntry[Indx].Device = BbsEntry[Indx+1].Device = AtaAtapiInfo[IdeCtl].Device;
            BbsEntry[Indx].Function = BbsEntry[Indx+1].Function = AtaAtapiInfo[IdeCtl].Function;
            BbsEntry[Indx].Class = BbsEntry[Indx+1].Class = 1;
            BbsEntry[Indx].SubClass = BbsEntry[Indx+1].SubClass = 1;

            if (AtaAtapiInfo[IdeCtl].CommandBaseAddress) {  // real controller
                //
                // Create entry for master device connected to this controller
                //
                if (AtaAtapiInfo[IdeCtl].Status & (HDD_MASTER_IDE | HDD_MASTER_ATAPI)) {
                    BbsEntry[Indx].BootPriority = BBS_UNPRIORITIZED_ENTRY;
                    if (AtaAtapiInfo[IdeCtl].Status & HDD_MASTER_ATAPI) {
                        BbsEntry[Indx].DeviceType = GetAtapiDeviceType(&AtaAtapiInfo[IdeCtl].IdentifyDrive[0]);
                    } else {
                        BbsEntry[Indx].DeviceType = BBS_HARDDISK;
                    }
                    CreateDriveString(
                        AtaAtapiInfo[IdeCtl].IdentifyDrive[0].Raw,
                        AtaAtapiInfo[IdeCtl].Status & ~(HDD_SLAVE_IDE | HDD_SLAVE_ATAPI),
                        &CoreBiosInfo->Thunk->DriveDisplayName[count++],
                        &BbsEntry[Indx].DescStringOffset,                        
                        ((UINT16)AtaAtapiInfo[IdeCtl].Bus << 8) +((UINT16)AtaAtapiInfo[IdeCtl].Device<<3)\
                          + ((UINT16) AtaAtapiInfo[IdeCtl].Function )                      
                    );
                    //TRACE((-1, "i=%d, bbsentry=%x, diskinfo=%x\n", Indx, &BbsEntry[Indx], *DiskInfoHandles));
                    *(UINTN*)(&BbsEntry[Indx].IBV1) = (UINTN)GetDriveHandle(AtaAtapiInfo[IdeCtl].IdentifyDrive);//(EIP71972)
                }
                //
                // Create entry for slave device connected to this controller
                //
                if (AtaAtapiInfo[IdeCtl].Status & (HDD_SLAVE_IDE | HDD_SLAVE_ATAPI)) {
                    BbsEntry[Indx+1].BootPriority = BBS_UNPRIORITIZED_ENTRY;
                    if (AtaAtapiInfo[IdeCtl].Status & HDD_SLAVE_ATAPI) {
                        BbsEntry[Indx+1].DeviceType = GetAtapiDeviceType(&AtaAtapiInfo[IdeCtl].IdentifyDrive[1]);
                    } else {
                        BbsEntry[Indx+1].DeviceType = BBS_HARDDISK;
                    }
                    CreateDriveString(
                        AtaAtapiInfo[IdeCtl].IdentifyDrive[1].Raw,
                        AtaAtapiInfo[IdeCtl].Status & ~(HDD_MASTER_IDE | HDD_MASTER_ATAPI),
                        &CoreBiosInfo->Thunk->DriveDisplayName[count++],
                        &BbsEntry[Indx+1].DescStringOffset,                       
                        ((UINT16)AtaAtapiInfo[IdeCtl].Bus << 8) +((UINT16)AtaAtapiInfo[IdeCtl].Device<<3)\
                          + ((UINT16) AtaAtapiInfo[IdeCtl].Function )                   
                    );
                    //TRACE((-1, "i=%d, bbsentry=%x, diskinfo=%x\n", Indx, &BbsEntry[Indx+1], *DiskInfoHandles));
                    *(UINTN*)(&BbsEntry[Indx+1].IBV1) = (UINTN)GetDriveHandle(&AtaAtapiInfo[IdeCtl].IdentifyDrive[1]);//(EIP71972)
                }
            }
        }
    }

#ifdef AhciSrc_SUPPORT
#if AhciSrc_SUPPORT
{
    EFI_AHCI_INT13_INIT_PROTOCOL    *Aint13;

    //
    // Initialize legacy AHCI support
    //
    Status = pBS->LocateProtocol(&gAint13ProtocolGuid, NULL, &Aint13);
    if (!EFI_ERROR(Status)) {
        Aint13->InitAhciInt13Support();
    }

}
#endif
#endif

    gIsMassStorageInstalled = TRUE;

    return;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// FUNCTION:  GetSystemMemoryMap
//
// DESCRIPTION: This function returns system memory map and count of the memory
//              entries in the map.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS GetSystemMemoryMap(
    OUT EFI_MEMORY_DESCRIPTOR **MemMap,
    OUT UINTN *MemDescSize,
    OUT UINTN *MemEntriesCount
)
{
    EFI_STATUS Status;
    UINTN MemMapSize, MemMapKey;
    UINT32 MemDescVer;

    if (MemMap == NULL || MemDescSize == NULL || MemEntriesCount == NULL)
    {
        ASSERT(FALSE);
        return EFI_INVALID_PARAMETER;
    }

    *MemMap = NULL;
    MemMapSize = 0; // GetMemoryMap will return the size needed for the map
    Status = pBS->GetMemoryMap(&MemMapSize, *MemMap,
                    &MemMapKey, MemDescSize, &MemDescVer);

    ASSERT(Status == EFI_BUFFER_TOO_SMALL);
    if (Status != EFI_BUFFER_TOO_SMALL) {
        *MemEntriesCount = 0;
        return EFI_INVALID_PARAMETER;
    }

    // The following memory allocation may alter memory map.
    // Let's add space for 5 more descriptors to be sure buffer is big enough
    MemMapSize += 5 * *MemDescSize;
    Status = pBS->AllocatePool(EfiBootServicesData, MemMapSize, MemMap);
    ASSERT_EFI_ERROR(Status);

    Status = pBS->GetMemoryMap(&MemMapSize, *MemMap,
                    &MemMapKey, MemDescSize, &MemDescVer);
    ASSERT_EFI_ERROR(Status);

    *MemEntriesCount = (UINT16)(MemMapSize / *MemDescSize);

    return Status;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// FUNCTION:  GetExtendedMemSize
//
// DESCRIPTION: This function looks through the system memory map, finds the
//              available memory regions and returns the size in bytes of the
//              system memory above 1 MB.
// NOTE:        If there is more than 4 GB of memory installed, then function
//              will return 4GB-1MB.
//              If the amount of memory is 4GB or more, some memory is remapped
//              above 4GB by the chipset. In this case this function will return
//              the amount of memory before the remapped area.
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID GetExtendedMemSize(UINT32* ExtMemSize)
{
    UINTN MemDescSize;
    EFI_MEMORY_DESCRIPTOR *MemMap;
    EFI_MEMORY_DESCRIPTOR *mm;
    UINTN count = 0;
    UINTN MemEntriesCount;
    UINT64 cs = 0x100000;

    GetSystemMemoryMap(&MemMap, &MemDescSize, &MemEntriesCount);

    for (mm = MemMap; count < MemEntriesCount; mm=(EFI_MEMORY_DESCRIPTOR*)((UINT8*)mm+MemDescSize), count++) {
        if (mm->PhysicalStart < 0x100000) continue; // skip low memory entries

        if (mm->Type == EfiReservedMemoryType ||
            mm->Type == EfiMemoryMappedIO ||
            mm->Type == EfiMemoryMappedIOPortSpace ||
            mm->Type == EfiRuntimeServicesCode ||
            mm->Type == EfiRuntimeServicesData ||
            mm->Type == EfiUnusableMemory ||
            mm->Type == EfiPalCode ||
            mm->Type == EfiACPIReclaimMemory ||
            mm->Type == EfiACPIMemoryNVS)
        {
            break;
        }

        cs = mm->PhysicalStart + Shl64(mm->NumberOfPages, EFI_PAGE_SHIFT);
    }
    pBS->FreePool(MemMap);

    *ExtMemSize = (UINT32)cs - 0x100000;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// FUNCTION:  InsertE820Entry
//
// DESCRIPTION: This function fills in the E820 table entry and adjusts
//              the input entry pointer. If the new entry is the extension of
//              the previous one, then entry is "extended".
// PARAMETERS:  Pointer to E820 entry to be filled.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
InsertE820Entry (
    E820_ENTRY **Entry,
    UINT64 Address,
    UINT64 Size,
    E820_MEMORY_TYPE Type,
    UINT16 *Count)
{
    E820_ENTRY *E820Entry = *Entry;
    E820_ENTRY *PrevE820Entry = E820Entry - 1;

    if (((PrevE820Entry->Adr + PrevE820Entry->Len) == Address) &&
        ((PrevE820Entry->Type == Type)
#if AGGRESSIVELY_JOINED_E820_ENTRIES
        || ((Type == MemRangeAvl) && (Address != 0x100000))
#endif
))
    {
        // extend the current entry without touching Adr and Type
        E820Entry = PrevE820Entry;
        E820Entry->Len += Size;
    } else {    // new entry
        E820Entry->Adr = Address;
        E820Entry->Len = Size;
        E820Entry->Type = Type;
        (*Count)++;
    }
    E820Entry->ExtendedAttr = E820_EXTATTR_ADDRESS_RANGE_ENABLED;
    *Entry = ++E820Entry;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// FUNCTION:  UpdateE820Map
//
// DESCRIPTION: This function retrieves the system memory map and converts it
//              into E820 map format.
// PARAMETERS:  Pointer to the 1st E820 entry in BIOS_INFO data structure
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT32
UpdateE820Map(E820_ENTRY *e820_entry)
{
    UINT16 Count = 0;
    UINTN MemDescSize;
    EFI_MEMORY_DESCRIPTOR *MemMap;
    EFI_MEMORY_DESCRIPTOR *mm;
    UINTN MemEntriesCount;
    UINTN i;
    E820_ENTRY *E820Entry = e820_entry;
    E820_MEMORY_TYPE MemType;
    UINT32                  EbdaAddress;
    BDA_DATA                *bda;

    GetSystemMemoryMap(&MemMap, &MemDescSize, &MemEntriesCount);

    bda = (BDA_DATA*)((UINTN) 0x400);   // 40:0

    EbdaAddress = (bda->ext_bios_data_seg)<<4; // 40:0e
    //
    // Start creating E820 table entries
    //
    InsertE820Entry(&E820Entry, 0,  (640 - ((UINT8)((0xA0000 - EbdaAddress) >> 10)) )<< 10, MemRangeAvl, &Count);
    InsertE820Entry(&E820Entry, (640 - ((UINT8)((0xA0000 - EbdaAddress) >> 10)) ) << 10, ((UINT8)((0xA0000 - EbdaAddress) >> 10)) << 10, MemRangeRes, &Count);
    InsertE820Entry(&E820Entry, 0xE0000, 0x20000, MemRangeRes, &Count);     // E0000..FFFFF
    //
    // Insert entries according to memory map; EFI memory types are mapped to ACPI address
    // range types according to ACPI 3.0 Specification, Chapter 14.3.
    //
    for (mm = MemMap, i = 0; i < MemEntriesCount; i++, mm=(EFI_MEMORY_DESCRIPTOR*)((UINT8*)mm+MemDescSize)) {
        if (mm->PhysicalStart < 0x100000) continue; // skip low memory entries
        switch (mm->Type) {
            case EfiMemoryMappedIO:
                    if (!(mm->Attribute & EFI_MEMORY_RUNTIME)) continue;
            case EfiReservedMemoryType:
            case EfiRuntimeServicesCode:
            case EfiRuntimeServicesData:
            case EfiUnusableMemory:
            case EfiMemoryMappedIOPortSpace:
            case EfiPalCode:
                    MemType = MemRangeRes;
                    break;
            case EfiACPIReclaimMemory:
                    MemType = MemRangeAcpiReclaim;
                    break;
            case EfiACPIMemoryNVS:
                    MemType = MemRangeAcpiNVS;
                    break;
            default: MemType = MemRangeAvl;
        }
        InsertE820Entry(&E820Entry,
                        mm->PhysicalStart,
                        Shl64(mm->NumberOfPages, EFI_PAGE_SHIFT),
                        MemType,
                        &Count);
        if (Count == MAX_E820_ENTRIES) break;
    }
    pBS->FreePool(MemMap);
    return Count;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// FUNCTION:  CmosRW
//
// DESCRIPTION: CMOS access helper
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS CmosRW(
    BOOLEAN rw,
    UINT32 reg,
    UINT8 *data
)
{
    UINT32 reg_;
    UINT8 data_;
    EFI_STATUS Status;
    EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *PciRB;

    Status = pBS->LocateProtocol (&gEfiPciRootBridgeIoProtocolGuid,
        NULL,
        &PciRB
    );
    ASSERT_EFI_ERROR(Status);
    if (EFI_ERROR (Status)) return Status;

    reg_ = reg;

    PciRB->Io.Write (PciRB, EfiPciWidthUint8, 0x70, 1, &reg_);  // Set index

    if (rw) {   // read
        PciRB->Io.Read (PciRB, EfiPciWidthUint8, 0x71, 1, &data_);
        *data = data_;
    } else {        // write
        data_ = *data;
        PciRB->Io.Write (PciRB, EfiPciWidthUint8, 0x71, 1, &data_);
    }
    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// FUNCTION:    UpdateCmos
//
// DESCRIPTION: This function updates CMOS before booting to Legacy OS
//
// NOTE:        This function enables NMI
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS UpdateCmos()
{
//  UINT8 reg;
    UINT8 data;
    //
    // Clear bits 0..3 on the CMOS ofs 0xE
    //
    CmosRW(TRUE, 0xE, &data);   // Read register E
    data &= 0xF0;
    CmosRW(FALSE, 0xE, &data);

    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// FUNCTION:  NmiToBeEnabled
//
// DESCRIPTION: This function returns the current selection of NMI to be
//              enabled/disabled.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN NmiToBeEnabled()
{
    return TRUE;    // TODO::Currently hardcoded, could be setup driven
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// FUNCTION:  EnableDisableNmi
//
// DESCRIPTION: This function enables or disables NMI according to setup
//              question.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
EnableDisableNmi()
{
    UINT16 data16;
    UINT8 data8;
    EFI_STATUS Status;
    EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *PciRB;

    Status = pBS->LocateProtocol (&gEfiPciRootBridgeIoProtocolGuid,
        NULL,
        &PciRB
    );
    ASSERT_EFI_ERROR(Status);
    if (EFI_ERROR (Status)) return Status;

    //
    // Update IO reg 61h - NMI_SC-NMI Status and Control Register
    //
    PciRB->Io.Read (PciRB, EfiPciWidthUint8, 0x61, 1, &data8);
    data8 &= 0xF3;
    data16 = NmiToBeEnabled()? 0xD : 0xC8D;
    data8 |= (data16 >> 8);
    PciRB->Io.Write (PciRB, EfiPciWidthUint8, 0x61, 1, &data8);
    //
    // Update IO reg 70h - NMI_EN-NMI Enable(and Real Time Clock Index)
    //
    data8 = (UINT8)data16;
    PciRB->Io.Write (PciRB, EfiPciWidthUint8, 0x70, 1, &data8);

    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//------------------------------------------------------------------------------------
//
//  Name:       UpdatePciLastBusCallback
//
// Description: This callback function then will process the list of root bridges
//              and will update the LastPciBus field of EFI_COMPATIBILITY16_TABLE
//              accordingly.
//
//------------------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
UpdatePciLastBusCallback (
    IN EFI_EVENT        Event,
    IN VOID             *Context
)
{
    EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL   *RBProtocol;
    ASLR_QWORD_ASD      *Descriptors;
    UINTN               Count=0,i=0;
    EFI_HANDLE          *Buffer;
    UINT8               MaxBus=0;
    EFI_STATUS          Status;

    LEGACY16_TO_EFI_DATA_TABLE_EXT *Csm16Data;
    UINT8               *NextRootBridgeBus;
    UINT8               CsmRbCount = 0;
    BOOLEAN             Csm16Is75Plus;
    //
    // UnLock E000 and F000 segments
    //
    Status = CoreBiosInfo->iRegion->UnLock (
             CoreBiosInfo->iRegion,
             (UINT32)0xe0000,
             (UINT32)0x20000,
             NULL
             );
    ASSERT_EFI_ERROR(Status);

    //
    //Locate the RootBridge protocol
    //
    Status = pBS->LocateHandleBuffer (
                  ByProtocol,
                  &gEfiPciRootBridgeIoProtocolGuid,
                  NULL,
                  &Count,
                  &Buffer
                  );
    ASSERT_EFI_ERROR(Status);
    if (EFI_ERROR(Status)) return;

    Csm16Is75Plus = *(UINT8*)0xf0019 > 0x75;   // CSM version 76 or later

    if (Csm16Is75Plus) {
        Csm16Data = (LEGACY16_TO_EFI_DATA_TABLE_EXT*)(UINTN)(0xf0000 + *(UINT16*)0xfff4c);
        NextRootBridgeBus = (UINT8*)((UINTN)Csm16Data->RbMinBusArrayOfs + 0xf0000);
    }

    for (i = 0; i < Count; i++) {
        Status = pBS->HandleProtocol (
                    Buffer[i],
                    &gEfiPciRootBridgeIoProtocolGuid,
                    &RBProtocol
                    );

        if (EFI_ERROR(Status)) continue;
        //
        // Get the Configuration
        //
        RBProtocol->Configuration(
                  RBProtocol,
                  &Descriptors
                  );

        if ((Descriptors)->Hdr.HDR != ASLV_END_TAG_HDR) {
            //
            // go till we get the Resource type = Bus Number range
            //
            while (Descriptors->Hdr.HDR != ASLV_END_TAG_HDR) {

                if (Descriptors->Type == ASLRV_SPC_TYPE_BUS) {
                    //
                    // We got the type;update the LastPCiBus of csm16header
                    //
                    if (Csm16Is75Plus) {
                        if (++CsmRbCount < Csm16Data->RbArrayCount) {
                            *NextRootBridgeBus++ = (UINT8)Descriptors->_MIN;
                        }
                    }
                    if((UINT8)Descriptors->_MAX > MaxBus ) {
                        MaxBus =(UINT8)Descriptors->_MAX;
                    }
                }
                Descriptors++;
            }
        }
    }

    // Update Pci Last Bus in Csm16 header
    // Note: do not report FF; this is XP limitation, EIP#24852
    CoreBiosInfo->Csm16Header->LastPciBus = (MaxBus == 0xff)? 0xfe : MaxBus;

    // Update CSM16 header checksum as LastPciBus field of it has been changed
    ChecksumCSM16Header(CoreBiosInfo->Csm16Header);

    // Look for _32_ structure and update offset 16 (0x10) with the MaxBus
    {
        UINTN Adr = 0xe0000;

        TRACE((-1,"CSM - Attempting to update RT32 binary with the MaxBus (0x%x)\n", MaxBus));

        for (; Adr < 0x100000; Adr += 0x10) {
            if (*(UINT32*)Adr == 0x5f32335f) {
                // found '_32_', verify checksum
                UINT8 i;
                UINT8 CheckSum = 0;
                TRACE((-1,"_32_ signature is found at %x,", Adr));
                for (i=0; i<0x10; i++) {
                    CheckSum += *((UINT8*)Adr+i);
                }
                if (CheckSum == 0) {
                    TRACE((-1,"checksum is OK\n"));
                    *((UINT8*)Adr+0x10) = MaxBus;
                }
                else {
                    TRACE((-1,"checksum is invalid.\n"));
                }
            }
        }
    }
    
    //
    // Lock E000 and F000 segments
    //
    Status = CoreBiosInfo->iRegion->Lock (
            CoreBiosInfo->iRegion,
            (UINT32)0xe0000,
            (UINT32)0x20000,
            NULL
            );
    ASSERT_EFI_ERROR (Status);

    // Close event, this function is to be executed once.
    if (Event != NULL) {
        pBS->CloseEvent(Event);
    }
}

/**
 * Goes through memory map looking for the requested memory block within 1MB..2GB range
 * 
 * @param[in] MemDesc   Starting memory descriptor of the memory map
 * @param[in] MemEntriesCount   Count of the memory map entries
 * @param[in] MemDescSize       Size of the memory descriptor
 * @param[in] DesiredBlockSize  Number of pages requested to be found
 * @param[out] MemAddress       Found memory block
 * @param[out] NumberOfPages    Found memory block size
 * @retval EFI_SUCCESS          Memory block is found
 * @retval EFI_NOT_FOUND        Memory block is not found
 */
EFI_STATUS FindMemoryBlockForHiPmm(
    EFI_MEMORY_DESCRIPTOR *MemMap,
    UINTN MemEntriesCount,
    UINTN MemDescSize,
    UINTN DesiredBlockSize,
    EFI_PHYSICAL_ADDRESS *MemAddress,
    UINT64 *NumberOfPages
)
{
    EFI_MEMORY_DESCRIPTOR *mm;
    UINTN count = 0;
    
    for (mm = MemMap; count < MemEntriesCount; mm=(EFI_MEMORY_DESCRIPTOR*)((UINT8*)mm+MemDescSize), count++) {
        if (mm->PhysicalStart < 0x100000) continue; // skip low memory entries
        // Skip above 2GB memory entries:
        // CORE0292.1 - value above 2GB will be assumed a negative number in find_free_memory algorithm
        if (mm->PhysicalStart > 0x7fffffff) continue; 

        if (mm->Type == EfiConventionalMemory && (mm->NumberOfPages >= DesiredBlockSize))
        {
            *MemAddress = mm->PhysicalStart;
            *NumberOfPages = mm->NumberOfPages;
            break;
        }
    }

    return (count == MemEntriesCount)? EFI_NOT_FOUND : EFI_SUCCESS;
}

/**
  Allocates the memory at 1MB..2GB that can be used for high memory PMM allocations.

  This EfiBootServicesData memory block should be outside the "main" BS memory
  so that it can be freed during READY_TO_BOOT. For that we go through EFI memory
  map looking for unallocated region of a given size.

  @param[in]    BlockSize     The number of pages to be allocated.
  @param[out]   BlockAddr     The address of the allocated block.

  @retval EFI_SUCCESS   Memory block is allocated.
  @retval Error Value   Memory can not be allocated.

*/
EFI_STATUS AllocateHiMemPmmBlock(
    IN  UINTN   BlockSize,
    OUT UINTN   *BlockAddr
)
{
    UINTN MemDescSize;
    EFI_MEMORY_DESCRIPTOR *MemMap;
    EFI_MEMORY_DESCRIPTOR *mm;
    UINTN count = 0;
    UINTN MemEntriesCount;
    EFI_PHYSICAL_ADDRESS HiPmmMemory;
    EFI_STATUS Status;
    UINT64 NumberOfPages;
    
    GetSystemMemoryMap(&MemMap, &MemDescSize, &MemEntriesCount);

    // print memory map
    for (mm = MemMap; count < MemEntriesCount; mm=(EFI_MEMORY_DESCRIPTOR*)((UINT8*)mm+MemDescSize), count++) {
        TRACE((-1, "%02d: %08x, %05x, ", count, mm->PhysicalStart, mm->NumberOfPages));
        switch (mm->Type) {
            case EfiReservedMemoryType: TRACE((-1, "EfiReservedMemoryType\n")); break;
            case EfiLoaderCode: TRACE((-1, "EfiLoaderCode\n")); break;
            case EfiLoaderData: TRACE((-1, "EfiLoaderData\n")); break;
            case EfiBootServicesCode: TRACE((-1, "EfiBootServicesCode\n")); break;
            case EfiBootServicesData: TRACE((-1, "EfiBootServicesData\n")); break;
            case EfiRuntimeServicesCode: TRACE((-1, "EfiRuntimeServicesCode\n")); break;
            case EfiRuntimeServicesData: TRACE((-1, "EfiRuntimeServicesData\n")); break;
            case EfiConventionalMemory: TRACE((-1, "EfiConventionalMemory\n")); break;
            case EfiUnusableMemory: TRACE((-1, "EfiUnusableMemory\n")); break;
            case EfiACPIReclaimMemory: TRACE((-1, "EfiACPIReclaimMemory\n")); break;
            case EfiACPIMemoryNVS: TRACE((-1, "EfiACPIMemoryNVS\n")); break;
            case EfiMemoryMappedIO: TRACE((-1, "EfiMemoryMappedIO\n")); break;
            case EfiMemoryMappedIOPortSpace: TRACE((-1, "EfiMemoryMappedIOPortSpace\n")); break;
            case EfiPalCode: TRACE((-1, "EfiPalCode\n")); break;
            default: TRACE((-1, "%x\n", mm->Type));
        }
    }

    // Try to allocate Size*4 block and use the middle of it; if not found, then try to allocate Size*2
    // and use the end
    Status = FindMemoryBlockForHiPmm(MemMap, MemEntriesCount, MemDescSize, BlockSize*4, &HiPmmMemory, &NumberOfPages);
    if (!EFI_ERROR(Status)) {
        HiPmmMemory += Shl64(NumberOfPages, 11); // Middle of the block
    } else {
        Status = FindMemoryBlockForHiPmm(MemMap, MemEntriesCount, MemDescSize, BlockSize*2, &HiPmmMemory, &NumberOfPages);
        HiPmmMemory += Shl64(NumberOfPages, 12); // End of the block
    }
    ASSERT_EFI_ERROR(Status);
    

    pBS->FreePool(MemMap);


    Status = pBS->AllocatePages(AllocateMaxAddress, EfiBootServicesData, BlockSize*2, &HiPmmMemory);
    *BlockAddr = (UINTN)HiPmmMemory;

    return Status;
}

// TODO: The following definition is from DebugLib.h; currently it can not be included
// as it clashes with AmiDxeLib.h definitions
#define DEBUG_PROPERTY_CLEAR_MEMORY_ENABLED       0x08
BOOLEAN
ClearMemoryEnabled (
  VOID
  )
{
  // In AptioV this feature is controlled by DEBUG_PROPERTY_CLEAR_MEMORY_ENABLED bit of PcdDebugPropertyMask
  // In Aptio4 this is project specific. By default we will return TRUE
  return TRUE;
}

/**
  READY_TO_BOOT notification callback that frees high memory PMM allocations.
  
  Hi memory PMM is a double buffer. First half is a real PMM memory, second half is
  a backup. Before freeing make a backup copy, then free the first block, then restore
  memory, then free the backup block. This is done to prevent clearing memory while
  executing FreePages.
  Note: double buffering is only needed when DEBUG_PROPERTY_CLEAR_MEMORY_ENABLED is 
  set in PcdDebugPropertyMask.
*/
VOID  FreePmmBeforeBoot (  
    IN EFI_EVENT            Event,
    IN VOID                 *Context
)
{
    EFI_STATUS Status;
    UINTN   NumberOfPages = (CoreBiosInfo->Thunk->Csm16InitTable.HiPmmMemorySizeInBytes >> 12) + 1;
    UINTN   Size = NumberOfPages << 12;
    UINTN   Address = CoreBiosInfo->Thunk->Csm16InitTable.HiPmmMemory;

    if (ClearMemoryEnabled ())
    {
        pBS->CopyMem((VOID*)(Address+Size), (VOID*)Address, Size);
        Status = pBS->FreePages(Address, NumberOfPages);
        ASSERT_EFI_ERROR(Status);
        pBS->CopyMem((VOID*)Address, (VOID*)(Address+Size), Size);
        Status = pBS->FreePages(Address+Size, NumberOfPages);
        ASSERT_EFI_ERROR(Status);
    }
    else 
    {
        Status = pBS->FreePages(Address, NumberOfPages*2);
        ASSERT_EFI_ERROR(Status);
    }
    pBS->CloseEvent(Event);

    TRACE((-1, "Free HI PMM memory: %r\n", Status));

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
