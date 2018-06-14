//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
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
// $Header: /Alaska/SOURCE/Modules/CSM/Generic/Core/CsmLib.c 69    1/10/14 12:21p Olegi $
//
// $Revision: 69 $
//
// $Date: 1/10/14 12:21p $
//
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/CSM/Generic/Core/CsmLib.c $
// 
// 69    1/10/14 12:21p Olegi
// EIP149769: LegacyToEfi boot management
// Changed default setting, added new token to extend the functionality
// 
// 68    10/31/13 9:45a Olegi
// Typo in Csm16ResetFeature case.
// 
// 67    10/18/13 12:38p Olegi
// EIP139866
// Create interface to manage LegacyToEfi CSM feature
// 
// 66    10/07/13 10:21a Olegi
// [TAG]  		EIP138427
// [Category]  	New Feature
// [Description]  	Create interface to let OEM customers change CSM16
// variables
// [Files] csm.c, csm.h, csmlib.c, legacybiosext.h
// 
// 65    5/17/13 10:28a Olegi
// [TAG]  		EIP123915
// [Category]  	Improvement
// [Description]  	BBS table update in CSM should be atomic operation
// (extra reentrance guards added)
// 
// 64    5/15/13 3:32p Olegi
// [TAG]  		EIP123915
// [Category]  	Improvement
// [Description]  	BBS table update in CSM should be atomic operation
// [Files]  		CsmOpROM.c
// CsmLib.c
// 
// 63    4/09/13 9:25a Olegi
// [TAG]  		EIP118727
// [Category]  	New Feature
// [Description]  	Onboard PCI Option ROM loading is moved outside CSM
// [Files]  		CSM.mak
// CSM.dxs
// CSM.c
// PciInterrupts.c
// CsmBsp.c
// CsmLib.c
// 
// 62    11/06/12 10:02a Olegi
// [TAG]  		EIP105801
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	CSM: FindEmbeddedRom improperly calls Check30ROM
// [RootCause]  	Check30ROM updates Size parameter with the runtime size
// of the ROM. FindEmbeddedRom passes the Init size, so after calling
// Check30ROM init size value is lost
// [Solution]  	Use dummy size variable to pass to Check30ROM
// [Files]  		CsmLib.c
// 
// 61    12/23/11 3:09p Olegi
// [TAG]  		EIP78921
// [Category]  	Improvement
// [Description]  	CsmBlockIo should create device handle in BBS table
// [Files]  		CSM.h
// CSM.c
// CsmLib.c
// 
// 60    11/11/11 1:00p Olegi
// [TAG]  		EIP71556
// [Category]  	Improvement
// [Description]  	Support for 6 IDE Controllers
// [Files]  		CSM.h
// CsmLib.c
// 
// 59    10/12/11 3:16p Olegi
// 
// 58    8/10/11 4:26p Olegi
// [TAG]  		EIP65882
// [Category]  	Improvement
// [Description]  	Added checking for OPROM_MULTIPLE_MODULEID in
// FindEmbeddedRom, PCI3.0 Option ROM section.
// [Files]  		CsmLib.c
// 
// 57    8/03/11 4:27p Olegi
// [TAG]  		EIP61035, EIP65224
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	When AMIDebugger is using COM port, system halts in
// DisconnectSerialIO().
// [RootCause]  	DisconnectSerialIO() Function present in CsmLib.c
// disconnects all SerialIO controllers including the AMI Debugger's
// DebugPort driver.
// [Solution]  	Before disconnecting SerialIo validate the controller by
// checking if device path protocol is installed on it.
// [Files]  		csmlib.c
// 
// 56    5/05/11 10:18a Olegi
// [TAG]  		EIP59628
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	BDA is not initialized correctly, reporting the maximum of
// 2 comports in the system with 4 comports.
// [RootCause]  	aPnP table did not have entries for COM3 and COM4
// [Solution]  	added COM3/COM4 entries in the aPnP table.
// [Files]  		csmlib.c
// 
// 55    1/31/11 4:31p Olegi
// [TAG]  		EIP50327 
// [Category]  	Improvement
// 
// 54    1/18/11 11:30a Olegi
// [TAG]  		EIP52322
// [Category]  	Improvement
// [Description]  	Projects with two or more PCI 3.0 embedded ROMs: if
// ROM's Device List all support one device, only one option ROM would be
// invoked.
// [Files]  		Changed the search method of FindEmbeddedRom()
// 
// 53    12/22/10 9:07a Olegi
// Added code to clear BBS entry before setting the BBS_IGNORE priority in
// RemoveBbsEntryAt function.
// 
// 52    12/03/10 12:43p Olegi
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
// 51    10/07/10 9:07a Olegi
// EIP44674: Reverted changes in GetComResource function.
// 
// 50    10/06/10 4:42p Olegi
// Finalized changes related to EIP35156.
// 
// 49    10/01/10 4:43p Oleksiyy
// Issue Number:  39752
// 
// Category:  Improvement
// 
// Description:  functuanality to hide Com1 from legacy OS if we are using
// Trace in Runtime is added.
// 
// Files:  Uart1.asl, Tokens.c, Runtime.c, GenericSio.c, EfiLib.c,
// CsmLib.c, AmiDxeLib.h and StatusCode eModule.
// 
// 48    10/01/10 4:30p Olegi
// A call GetPlatformEmbeddedRom is replaced with the ELINK; this serves
// the purpose of OEM function portability. EIP35156.
// 
// 47    9/20/10 1:04p Olegi
// EIP42722: Corrected GetComResource function.
// 
// 46    9/01/10 10:37a Olegi
// EIP42523: Added VendorId checking for PCI3.0 Option ROMs.
// Background: CSM would check Device List to find the correct ROM image
// if option ROM is PCI 3.0. But there was a lack of VendorID checking in
// the search rule, this may cause FindEmbeddedRom return incorrect ROM
// image.
// 
// 45    8/30/10 4:56p Olegi
// Added EFI_NOT_FOUND output to RemoveBbsEntryAt function.
// 
// 44    7/16/10 12:08p Olegi
// ConnectSerialIO/DisconnectSerialIO functions moved here from CSM.C.
// 
// 43    7/08/10 11:31a Olegi
// Added SignalAmiLegacyBootEvent function. EIP39089
// 
// 42    5/21/10 2:29p Olegi
// Modification in GetComPortResource: removed unneeded typecasting to
// SIO_DEV.
// 
// 41    1/28/10 9:27a Olegi
// Bugfix in GetComPortResource::EIP33931.
// 
// 40    1/12/10 11:46a Olegi
// Copyright message updated.
// 
// 39    12/28/09 8:49a Olegi
// Modification in LockShadow, remove decoding of the unused shadow area.
// EIP#29087
// 
// 38    12/28/09 7:46a Olegi
// Added GetLptResource function.
// 
// 37    8/05/09 5:56p Olegi
// FindEmbeddedRom() is modified to implement the feature of PCI3.0 OpROM
// that handles multiple devices. EIP#24327
// 
// 36    4/02/09 2:12p Olegi
// Added GetComPortResource function.
// 
// 35    12/22/08 5:27p Olegi
// Added GetPlatformEmbeddedRom function. This allows different packing of
// the OpROM, can be used to pack it as FFS file.
// 
// 34    10/22/08 6:22p Robert
// In UnlockShadow, moved the assignment of LockUnlockAddr and
// LockUnlockSize outside the if (size) scope to cover the case where size
// = 0
// 
// 33    10/10/08 11:56a Olegi
// 
// 32    10/10/08 11:54a Olegi
// UnlockShadow: calculation of size adjustment is changed.
// 
// 31    9/23/08 2:18p Olegi
// 
// 30    6/30/08 3:53p Olegi
// Added AddBbsEntryAt and RemoveBbsEntryAt functions.
// 
// 29    6/10/08 11:05a Olegi
// Bugfix in RemoveDecodingForShadow, the size of the region was not
// calculated correctly.
// 
// 28    5/19/08 12:37p Olegi
// Removed EBDA size limitation.
// 
// 27    5/08/08 6:03p Olegi
// Modified FindEmbeddedRom routine to support multiple DID for one OpROM
// for PCI onboard devices
// 
// 26    4/14/08 2:46p Rameshraju
// Removed the decoding for the remaining Shadow region
// 
// 25    1/31/08 11:53a Olegi
// AllocateEbda definition changed.
// 
// 24    1/16/08 2:17p Olegi
// Modified AllocateEbda function.
// 
// 23    12/04/07 11:07a Olegi
// 
// 22    10/08/07 5:24p Olegi
// Bugfix in AllocateEbda() - after allocation all EBDA pointers
// associated with already executed OpROMs must be updated.
// 
// 21    10/02/07 10:42a Olegi
// Modified IsSioDevicePluggedIn() function.
// 
// 1     7/08/07 5:19p Fasihm
// 
// 19    4/27/07 5:13p Olegi
// CSM.CHM file preparation.
//
// 18    4/20/07 4:41p Olegi
// AllocateEbda function is modified so that it properly updates 40:13
//
// 17    12/13/06 11:09a Olegi
// AllocateEbda function introduction (not tested).
//
// 16    8/29/06 5:48p Olegi
//
// 15    8/28/06 11:11a Olegi
// IsConnected[] array data is corrected.
//
// 14    8/24/06 6:57p Felixp
//
// 13    8/24/06 6:49p Felixp
// x64 support (warnings/errors fixed)
//
// 12    8/16/06 2:38p Olegi
// Previous typecast changes undone.
//
// 11    8/11/06 4:54p Olegi
//
// 10    5/19/06 11:22p Felixp
// Device Path code updated to use NEXT_NODE/NODE_LENGTH/SET_NODE_LENGTH
// macros to remove direct access to the Length field
//
// 9     3/13/06 2:33p Felixp
//
// 8     11/23/05 11:22a Felixp
// dev_status renamed to DEV_STATUS.
// 
// 7     11/23/05 9:40a Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	CsmLib.c
//
// Description:	Functions and variables used in different CSM modules
//
//<AMI_FHDR_END>
//**********************************************************************
#include "csm.h"
#include "AmiDxeLib.h"
#include "AcpiRes.h"
#include <Protocol\AmiSio.h>
#include <Protocol\SimplePointer.h>
#include <Protocol\BlockIo.h>
#include "token.h"
#include "pci.h"
#include <Protocol/SerialIo.h>
#include <Protocol/AmiBoardInfo.h>

extern BIOS_INFO *CoreBiosInfo;
extern UINTN gMaxOpRomAddress;

VOID        *EmbeddedRom;
UINTN       EmbeddedRomSize;

VOID        UpdateEbdaMap(UINT32);

extern AMI_BOARD_INFO_PROTOCOL *gAmiBoardInfo;
extern BOOLEAN gBbsUpdateInProgress;

BOOLEAN
Check30ROM(
    IN VOID         *RomLocation,
    IN OUT UINTN    *Size,
    IN  EFI_HANDLE  PciHandle
);

static UINT16 aPnP[16] = {
    0x0501, // 0 - UART1
    0x0501, // 1 - UART2
    0x0400, // 2 - LPT1
    0x0604, // 3 - FDC
    0, 0, 0, 0, 0, 0,
    0x0303, // A - KBC
    0,      // B - EC
    0x0501, //C - UART3
    0x0501, // D - UART4
    0x0F03, // E - PS/2 Mouse
    0       // F - Reserved
};

typedef EFI_STATUS (*IsConnectedFunc)(EFI_HANDLE);

EFI_STATUS IsConnectedDummy(EFI_HANDLE);
EFI_STATUS IsConnectedPS2MS(EFI_HANDLE);
EFI_STATUS IsConnectedFloppy(EFI_HANDLE);

static
IsConnectedFunc IsConnected[] = {
    IsConnectedDummy,   // 0 - UART1
    IsConnectedDummy,   // 1 - UART2
    IsConnectedDummy,   // 2 - LPT1
    IsConnectedFloppy,  // 3 - FDC
    IsConnectedDummy,   // 4 - SB16
    IsConnectedDummy,   // 5 - MIDI
    IsConnectedDummy,   // 6 - MSS AUDIO
    IsConnectedDummy,   // 7 - FM Synthesizer
    IsConnectedDummy,   // 8 - Game Port1
    IsConnectedDummy,   // 9 - Game Port2
    IsConnectedDummy,   // A - KBC
    IsConnectedDummy,   // B - EC
    IsConnectedDummy,   // C - reserved
    IsConnectedDummy,   // D - reserved
    IsConnectedPS2MS,   // E - PS/2 Mouse
    IsConnectedDummy    // F - reserved
};

typedef struct _ACPI_PNPID {
    UINT32  Signature   :16;
    UINT32  PnpID       :16;
} ACPI_PNPID;

EFI_HANDLE  *gSerialIoHandleBuffer=NULL;
UINTN       gSerialIoHandleCount=0;

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:  FindEmbeddedRom
//
// Description: This function searches for ROM within the data previously loaded
//              from the main FV image and returns its pointer and size.
//
// Output:      EFI_SUCCESS or EFI_NOT_FOUND
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
typedef EFI_STATUS (*CSM_GET_EMBEDDED_PCI_ROM) (
    UINT16 VendorId, UINT16 DeviceId, VOID **ImageStart, UINTN *ImageSize);

EFI_STATUS FindEmbeddedRom(
    UINT16 ModuleId, UINT16 VendorId, UINT16 DeviceId,
    VOID **ImageStart, UINTN *ImageSize
)
{
    OPROM_HEADER *Header;
    EFI_STATUS Status;
    PARTIAL_OPROM_HEADER *PartialHeader = NULL;
    UINT8 NumAdditionalDevicesWithSameOpRom = 0;
    UINT32 SizeOfPartialHeaders = 0;
    UINT32 i = 0;
    PCI_DATA_STRUCTURE *pcir;
    UINT16 *DeviceIDList;
    CSM_GET_EMBEDDED_PCI_ROM GetEmbeddedPciRom = (CSM_GET_EMBEDDED_PCI_ROM)gAmiBoardInfo->BoardOemInfo;

    Status = GetPlatformEmbeddedRom(ModuleId, VendorId, DeviceId, ImageStart, ImageSize);
    if (!EFI_ERROR(Status)) return Status;

    if ((ModuleId == OPROM_MODULEID) && (gAmiBoardInfo->BoardOemInfo != NULL))
    {
        GetEmbeddedPciRom = (CSM_GET_EMBEDDED_PCI_ROM)gAmiBoardInfo->BoardOemInfo;
        Status = GetEmbeddedPciRom(
            VendorId, DeviceId, ImageStart, ImageSize);
        return Status;
    }


    for(  Header = (OPROM_HEADER*)EmbeddedRom
        ; (UINT8*)Header<(UINT8*)EmbeddedRom+EmbeddedRomSize
        ; Header = (OPROM_HEADER*)((UINT8*)(Header+1)+
                                    SizeOfPartialHeaders+
                                    Header->Size)
    )
    {
        if (   Header->ModuleId==ModuleId
            && Header->VendorId==VendorId
            && Header->DeviceId==DeviceId
        )
        {
            *ImageStart = Header+1;
            *ImageSize=Header->Size;
            return EFI_SUCCESS;
        }
        else
        {
            // try LinkDid/LinkVid for OpROMs
            //If there is more than 1 device using an option rom,
            //the header of the first device has a module id with the follow format:
            //  0xA0XX
            //where the least significant byte is the additional number of devices using the option ROM.
            // e.g. If there are 2 devices using the option rom, then the header of the
            //first device has module id 0xA001.
            //The first device device has a complete header, and the remaining devices have partial headers.
            //A partial header is the complete header without the 'Size' field.
            if ((Header->ModuleId & 0xFF00) == OPROM_MULTIPLE_MODULEID)
            {
                NumAdditionalDevicesWithSameOpRom = (UINT8) (Header->ModuleId & 0xFF);
                SizeOfPartialHeaders = sizeof(PARTIAL_OPROM_HEADER) *
                                        NumAdditionalDevicesWithSameOpRom;
                //check the first header
                //we do not check the module id
                if ((Header->VendorId == VendorId) &&
                    (Header->DeviceId==DeviceId)) {
                    *ImageStart = (UINT8 *)(Header+1)+SizeOfPartialHeaders;
                    *ImageSize=Header->Size;
                    return EFI_SUCCESS;
                }
                //Check the partial headers of the remaining devices using this option rom.
                //The first partial header directly follows the regular header.
                PartialHeader = (PARTIAL_OPROM_HEADER *)(Header+1);
                for (i = 0; i < NumAdditionalDevicesWithSameOpRom; i++) {
                    if ((PartialHeader->ModuleId == ModuleId) &&
                        (PartialHeader->VendorId == VendorId) &&
                        (PartialHeader->DeviceId == DeviceId)) {
                        *ImageStart = (UINT8 *)(Header+1)+SizeOfPartialHeaders;
                        *ImageSize=Header->Size;
                        return EFI_SUCCESS;
                    }
                    PartialHeader++;
                }
            } else {
                SizeOfPartialHeaders = 0;
            }
        }
        *ImageStart = 0;
        *ImageSize = 0;
    }

    // Linked List failed. So check if it is a PCI 3.0 Option and has a valid Device List pointer
    for(  Header = (OPROM_HEADER*)EmbeddedRom
        ; (UINT8*)Header<(UINT8*)EmbeddedRom+EmbeddedRomSize
        ; Header = (OPROM_HEADER*)((UINT8*)(Header+1)+
                                    SizeOfPartialHeaders+
                                    Header->Size)
    )
    {
        UINTN DummyImageSize;

        if ((Header->ModuleId & 0xFF00) == OPROM_MULTIPLE_MODULEID)
        {
            NumAdditionalDevicesWithSameOpRom = (UINT8) (Header->ModuleId & 0xFF);
            SizeOfPartialHeaders = sizeof(PARTIAL_OPROM_HEADER) * NumAdditionalDevicesWithSameOpRom;
            PartialHeader = (PARTIAL_OPROM_HEADER *)(Header+1);
            for (i = 0; i < NumAdditionalDevicesWithSameOpRom; i++) {
                PartialHeader++;
            }
        } else {
            SizeOfPartialHeaders = 0;
        }

        *ImageStart = (UINT8 *)(Header+1)+SizeOfPartialHeaders;
        *ImageSize = Header->Size;
        if (Check30ROM(*ImageStart, &DummyImageSize, NULL)){
            // Check for valid Device List Pointer
            pcir = (PCI_DATA_STRUCTURE *)((UINT8*)*ImageStart + *(UINT16*)((UINT8*)*ImageStart + 0x18));
            if ((pcir->VendorId == VendorId) && (pcir->Reserved0)) { //(EIP42523)
                DeviceIDList = (UINT16 *)((UINT8 *)pcir +  pcir->Reserved0);
                for (;*DeviceIDList; DeviceIDList++ ){
                    if (*DeviceIDList == DeviceId) {
                        return EFI_SUCCESS;
                    }
                }
            }
        }
        *ImageStart = 0;
        *ImageSize = 0;
    }

    return EFI_NOT_FOUND;
}


EFI_STATUS IsConnectedDummy(EFI_HANDLE handle)
{
    return EFI_UNSUPPORTED;
}

EFI_STATUS IsConnectedPS2MS(EFI_HANDLE handle)
{
    EFI_STATUS Status;
    EFI_SIMPLE_POINTER_PROTOCOL *spp;
    EFI_SIMPLE_POINTER_STATE state;

    Status = pBS->HandleProtocol(handle,&gEfiSimplePointerProtocolGuid,&spp);
    if (!EFI_ERROR(Status)) {
        Status = spp->GetState(spp, &state);
        // ask A. to fix this if - should return DEVICE_ERROR, not NO_READY
        //if (Status != EFI_DEVICE_ERROR) {
        if (Status != EFI_NOT_READY) {
            Status = EFI_SUCCESS;
        }
    }
    return Status;
}


EFI_STATUS IsConnectedFloppy(EFI_HANDLE handle)
{
    EFI_STATUS Status;
    EFI_BLOCK_IO_PROTOCOL *blkiop;

    Status = pBS->HandleProtocol(handle,&gEfiBlockIoProtocolGuid,&blkiop);

    return Status;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Function:    IsSioDevicePluggedIn
//
// Description: Returns connect status of certain SIO device.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN IsSioDevicePluggedIn(
    IN SIO_DEV_STATUS *dev_plugged_in,
    OUT EFI_HANDLE    *hDevice
)
{
    EFI_STATUS          Status;
    UINT16              dev;
    UINTN               i,j,cnt;
    ACPI_HID_DEVICE_PATH    *siodp;
    ACPI_PNPID          *pnpid;
    EFI_HANDLE          *hbuff = NULL;
    EFI_DEVICE_PATH_PROTOCOL        *dp;
    BOOLEAN             bIsConnected = FALSE;

    dev = dev_plugged_in->DEV_STATUS;
    Status = pBS->LocateHandleBuffer(ByProtocol,&gEfiAmiSioProtocolGuid, NULL, &cnt, &hbuff);
//  ASSERT_EFI_ERROR(Status);

    if (EFI_ERROR(Status)) return FALSE;

    //
    // Find the device index. Note, that this function does not support multiple devices.
    //
    for (j=0; j<16; j++, dev>>=1) {
        if (dev & 1) break;
    }
    if (j==16) {
        pBS->FreePool(hbuff);
        return FALSE;
    }

    for(i=0; i<cnt; i++){
        Status=pBS->HandleProtocol(hbuff[i],&gEfiDevicePathProtocolGuid,&dp);
        if(EFI_ERROR(Status)) continue;

        siodp=DPGetLastNode(dp);
        if(siodp->Header.Type!=ACPI_DEVICE_PATH
            || siodp->Header.SubType!=ACPI_DP
            || NODE_LENGTH(&siodp->Header) != ACPI_DEVICE_PATH_LENGTH) continue;

        pnpid=(ACPI_PNPID*)&siodp->HID;
        if (pnpid->PnpID == aPnP[j]) {
            bIsConnected = (BOOLEAN) (IsConnected[j](hbuff[i]) == EFI_SUCCESS);
            *hDevice = hbuff[i];
            break;
        }
    }
    pBS->FreePool(hbuff);
    return bIsConnected;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Function:    GetSioDeviceStatus
//
// Description: Returns present/absent status of SIO device.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
GetSioDeviceStatus(
    IN OUT SIO_DEV_STATUS *devsts
)
{
    static EFI_GUID  SioDevStatusVarGuid = SIO_DEV_STATUS_VAR_GUID;
    SIO_DEV_STATUS      siost;
    UINTN               i, j, cnt;
    EFI_STATUS          Status;
    ACPI_HID_DEVICE_PATH    *siodp;
    ACPI_PNPID          *pnpid;
    EFI_HANDLE          *hbuff = NULL;
    UINT16              shifty;
    EFI_DEVICE_PATH_PROTOCOL        *dp;

    siost.DEV_STATUS = 0;
    i = sizeof(siost);
    Status = pRS->GetVariable(
                SIO_DEV_STATUS_VAR_NAME,
                &SioDevStatusVarGuid,
                NULL,
                &i,
                &siost.DEV_STATUS);
    if (EFI_ERROR(Status)) {
    //
    // NVRAM variable is not found, let us try to get status directly.
    //
        Status = pBS->LocateHandleBuffer(ByProtocol,&gEfiAmiSioProtocolGuid, NULL, &cnt, &hbuff);
//      ASSERT_EFI_ERROR(Status);
        if(EFI_ERROR(Status)) return;

        for (shifty=1,j=0; j<16; j++, shifty<<=1) { // 16 is the number of device types
            if (!(devsts->DEV_STATUS | shifty)) continue;   // not this device
            for(i=0; i<cnt; i++){
                Status=pBS->HandleProtocol(hbuff[i],&gEfiDevicePathProtocolGuid,&dp);
                if(EFI_ERROR(Status)) continue;

                siodp=DPGetLastNode(dp);
                if(siodp->Header.Type!=ACPI_DEVICE_PATH
                || siodp->Header.SubType!=ACPI_DP
                || NODE_LENGTH(&siodp->Header) != ACPI_DEVICE_PATH_LENGTH) continue;

                pnpid=(ACPI_PNPID*)&siodp->HID;
                if (pnpid->PnpID == aPnP[j]) {
                    siost.DEV_STATUS |= shifty;
                    break;
                }
            }
        }
        pBS->FreePool(hbuff);
    }

    *devsts = siost;

}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Function:    GetComPortResource
//
// Description: Returns COM port base address and interrupt
//
// Input:       ComNo - COM port number, 0-based.
//
// Output:      EFI_NOT_FOUND - COM port is not found.
//              EFI_SUCCESS - COM port found, the output variables are updated:
//                  Address - IO base address
//                  Irq     - IRQ number
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
GetComPortResource(
    IN UINT8    ComNo,
    OUT UINT16  *Address,
    OUT UINT8   *Irq
)
{
    EFI_HANDLE          *Handle = NULL;
    UINTN               Count;
    UINTN               i;
    EFI_STATUS          Status;
    UINT8               ComNumber = (UINT8)-1;
    AMI_SIO_PROTOCOL    *AmiSio;
    SPIO_DEV            *SpIoDev;

    // Hide COM1 from legacy OS if we are using Trace in Runtime
    if (ComNo == 0) {
#if RUNTIME_TRACE_SUPPORT
        return EFI_NOT_FOUND;
#endif
    }

    Status = pBS->LocateHandleBuffer(
        ByProtocol, &gEfiAmiSioProtocolGuid, NULL, &Count, &Handle);
    if(EFI_ERROR(Status)) return Status;

    for (i = 0; i < Count; i++)
    {
        Status = pBS->HandleProtocol(Handle[i],&gEfiAmiSioProtocolGuid, &AmiSio);
        if (EFI_ERROR(Status)) continue;

        Status = EFI_NOT_FOUND;

        SpIoDev = (SPIO_DEV*)(UINTN)AmiSio;

        if (SpIoDev->DeviceInfo->Type != dsUART) continue;  // not COM port
        if (SpIoDev->VlData.DevImplemented == 0)
        {
            continue;
        }
        ComNumber++;
        //
        // Check if we have reached "ComNo" th instance of UART devices
        // 
        if(ComNumber!=ComNo)continue;


        *Address = (UINT16)SpIoDev->VlData.DevBase1;
        *Irq = (UINT8)SpIoDev->VlData.DevIrq1;

        Status = EFI_SUCCESS;
        break;
    }

    pBS->FreePool(Handle);

    return Status;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Function:    GetLptResource
//
// Description: Returns LPT base address and interrupt
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
GetLptResource(
    OUT UINT16  *Address,
    OUT UINT8   *Irq
)
{
    EFI_HANDLE  *Handle = NULL;
    UINTN       Count;
    UINTN       i;
    EFI_STATUS  Status;

    AMI_SIO_PROTOCOL    *AmiSio;
    SPIO_DEV            *SpIoDev;

    Status = pBS->LocateHandleBuffer(
        ByProtocol, &gEfiAmiSioProtocolGuid, NULL, &Count, &Handle);
    if(EFI_ERROR(Status)) return Status;

    for (i = 0; i < Count; i++) {
        Status = pBS->HandleProtocol(Handle[i],&gEfiAmiSioProtocolGuid, &AmiSio);
        if (EFI_ERROR(Status)) continue;

        SpIoDev = (SPIO_DEV*)(UINTN)AmiSio;

        if (SpIoDev->DeviceInfo->Type != dsLPT) continue;  // not LPT
        if (SpIoDev->VlData.DevImplemented == 0) continue;

        *Address = (UINT16)SpIoDev->VlData.DevBase1;
        *Irq = (UINT8)SpIoDev->VlData.DevIrq1;

        Status = EFI_SUCCESS;
        break;
    }

    pBS->FreePool(Handle);

    Status = (i == Count)? EFI_NOT_FOUND : EFI_SUCCESS;

    return Status;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// FUNCTION:    AllocateEbda
//
// DESCRIPTION: This function attempts to allocate EBDA.
//
// INPUT:       EBDA size in kilo Bytes
//
// RETURN:      32-bit pointer of the allocated memory block inside EBDA
//              The allocated address offset off the beginning of EBDA
//              EFI_OUT_OF_RESOURCES if EBDA can not be allocated
//              EFI_SUCCESS if memory is successfully allocated
//
// NOTE:        - This routine can be called multiple times and every time EBDA
//              data is copied to a different location. It is the caller
//              responsibility to obtain the current EBDA segment and its size
//              and adjust the offsets before accessing the data.
//              - NewEbdaAddress could be used immediately after allocation. If
//              the allocated block is not used immediately, - any successive
//              call moves the existing data - then the caller should use
//              EbdaStartOffset to calculate the correct address of the previously
//              allocated data.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
AllocateEbda(
    IN EFI_LEGACY_BIOS_EXT_PROTOCOL *This,
    IN UINT8    RequestedSizeKB,
    OUT UINT32  *NewEbdaAddress,
    OUT UINT32  *EbdaStartOffset
)
{
    UINT16 CurEbdaSeg = *(UINT16*)(UINTN)0x40E;
    UINTN  CurEbdaLocation, NewEbdaLocation;
    UINT8  CurEbdaSizeKB;
    UINTN  CurEbdaSize, EbdaSize;
    UINTN  MinEbdaAddress = 0xA0000-PMM_EBDA_LOMEM_SIZE;

    //
    // Check the current EBDA allocation and see if there is still room in it
    //
    CurEbdaLocation = (UINTN)CurEbdaSeg<<4;
    ASSERT(CurEbdaLocation > MinEbdaAddress);   // either not allocated or already full

    EbdaSize = (UINTN)RequestedSizeKB << 10;
    NewEbdaLocation = CurEbdaLocation - EbdaSize;

    if (NewEbdaLocation < MinEbdaAddress) {
        return EFI_OUT_OF_RESOURCES;
    }

    //
    // Do the allocation:
    // - copy old EBDA
    // - clear the allocated EBDA
    // - update EBDA pointer and EBDA size
    //
    CurEbdaSizeKB = *(UINT8*)CurEbdaLocation;
    CurEbdaSize = (UINTN)CurEbdaSizeKB<<10;

    pBS->CopyMem((VOID*)NewEbdaLocation, (VOID*)CurEbdaLocation, CurEbdaSize);

    pBS->SetMem((UINT8*)(NewEbdaLocation+CurEbdaSize), EbdaSize, 0);

    *(UINT16*)(UINTN)0x40E = (UINT16)(NewEbdaLocation>>4);
    *(UINT8*)NewEbdaLocation = CurEbdaSizeKB + RequestedSizeKB;

    //
    // Update 40:13 with the new size of available base memory
    //
    *(UINT16*)(UINTN)0x413 = (*(UINT16*)(UINTN)0x413) - RequestedSizeKB;

    //
    // Update the EBDA information for the saved OpROMs
    //
    UpdateEbdaMap((UINT32)EbdaSize);

    *NewEbdaAddress = (UINT32)(NewEbdaLocation+CurEbdaSize);
    *EbdaStartOffset = (UINT32)CurEbdaSizeKB << 10;

    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:        UnlockShadow
//
// Description: Opens the shadow region(s) for writing.
//
// Input:   Address - starting address
//          Size    - size of the region
//
// Output:  LockUnlockAddr - address of the first unlocked block
//          LockUnlockSize - unlocked address space
//          Function returns EFI_OUT_OF_RESOURCES if there is not enough room
//          in the shadow.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
UnlockShadow(
    IN UINT8    *Address,
    IN UINTN    Size,
    OUT OPTIONAL UINT32  *LockUnlockAddr,
    OUT OPTIONAL UINT32  *LockUnlockSize
)
{
    UINT32 Granularity;
    UINT32 addr, size;
    UINT32 addr_adjustment;
    UINT32 size_adjustment = 0;
    EFI_STATUS Status;

    addr = (UINT32)(UINTN)Address;
    size = (UINT32)Size;
    if (size) {
        Status = CoreBiosInfo->iRegion->UnLock (CoreBiosInfo->iRegion,
                    addr, size, &Granularity);
        ASSERT_EFI_ERROR(Status);
        if (EFI_ERROR(Status)) return Status;

        addr_adjustment = addr % Granularity;

        if (((addr+size) % Granularity) != 0) {
            size_adjustment = Granularity - ((addr+size) % Granularity);
        }

        // Adjust the address to align with the granularity
        addr -= addr_adjustment;
        // Adjust the size to align with the granularity
        size += addr_adjustment;    // Align left
        size += size_adjustment;

    }

    // moved these outside the if (size) for case when size = 0
    if (LockUnlockAddr != NULL) *LockUnlockAddr = addr;
    if (LockUnlockSize != NULL) *LockUnlockSize = size;

    //
    // Finally make CSM16 area writable for the cases where
    // CSM16 area needs to be updated during DispatchOptionRom
    // call, e.g. for non-BBS OpROMs.
    //
    Status = CoreBiosInfo->iRegion->UnLock (
        CoreBiosInfo->iRegion,
        (UINT32)gMaxOpRomAddress+1,
        0xFFFFF-(UINT32)gMaxOpRomAddress,
        NULL
    );
    ASSERT_EFI_ERROR(Status);

    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:        LockShadow
//
// Description: Locks the shadow region(s).
//
// Input:   LockAddr    - Starting address of the area to be locked
//          LockSize    - Size of the area to be locked
//
// Output:  Status of the lock operation.
//
// Notes:   This function will also clear the R/W attribute for the region
//          from LockAddr+LockSize to gMaxOpRomAddress; this is needed for
//          some OS drivers to be loaded properly (Win PCMCIA driver)
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
LockShadow(
    IN UINT32  LockAddr,
    IN UINT32  LockSize
)
{
    UINT32      Granularity;
    EFI_STATUS  Status = EFI_SUCCESS;

    if (LockSize && ((LockAddr+LockSize) < gMaxOpRomAddress)) {
        Status = CoreBiosInfo->iRegion->Lock (CoreBiosInfo->iRegion, LockAddr, LockSize, &Granularity);
        ASSERT_EFI_ERROR(Status);
        //
        // Disable Shadow W/R for the unused shadow regions
        // Take care of the boundary conditions: LockAddr+LockSize is not nesessarily
        // within Granularity boundaries. For example, if LockAddr is 0xC0000, LockSize
        // is 0x1400 and Granularity is 0x1000, then area from 0xC0000 to 0xC2000 is
        // locked. The next call must not use 0xC0000+LockSize, otherwise part of the
        // OpROM becomes unreadable.
        //
        if (LockSize % Granularity) LockSize += Granularity;
        LockSize = (LockSize/Granularity)*Granularity;
    }
	
	if( LockAddr!=0 && LockSize!=0 ) {
		BOOLEAN On=FALSE;
		if ((LockAddr+LockSize) < gMaxOpRomAddress) {
			Status = CoreBiosInfo->iRegion->Decode (CoreBiosInfo->iRegion,
													LockAddr+LockSize,
													(UINT32)gMaxOpRomAddress-LockSize-LockAddr+1,
													&On);
			ASSERT_EFI_ERROR(Status);
		}
	}

    CoreBiosInfo->iRegion->Lock (
        CoreBiosInfo->iRegion,
        (UINT32)gMaxOpRomAddress+1,
        0xFFFFF-(UINT32)gMaxOpRomAddress,
        NULL
    );

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:        RemoveDecodingForShadow
//
// Description: This function will clear the R/W attribute for the region
//              from DecodeAddr to gMaxOpRomAddress; this is needed for
//              some OS drivers to be loaded properly (Win PCMCIA driver).
//
// Input:       DecodeAddr    - Starting address of the area to remove the decoding
//
// Output:      Status of the decoding operation.
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
RemoveDecodingForShadow(
    IN UINT32  DecodeAddr
)
{
    BOOLEAN     On=FALSE;
    EFI_STATUS  Status=EFI_SUCCESS;
    UINT32      Granularity;
    UINT32      addr, size=1;
    UINT32      addr_adjustment, size_adjustment;

    addr = DecodeAddr;

    //
    //Find the nearest starting address
    //
    if (size) {
TRACE((TRACE_ALWAYS, "RemoveDecoding: addr %x\n", addr));
        Status = CoreBiosInfo->iRegion->UnLock (CoreBiosInfo->iRegion,
                    addr, size, &Granularity);
        ASSERT_EFI_ERROR(Status);
        if (EFI_ERROR(Status)) return Status;

        addr_adjustment = addr % Granularity;
        size_adjustment = Granularity - ((addr+size) % Granularity);
        // Adjust the address to align with the granularity
        addr -= addr_adjustment;
        // Adjust the size to align with the granularity
        size += addr_adjustment;    // Align left
        size += size_adjustment;
    }

    Status = CoreBiosInfo->iRegion->Lock (CoreBiosInfo->iRegion, addr, size, &Granularity);

    if(addr == DecodeAddr) {
        DecodeAddr=addr;
    } else {
        DecodeAddr=addr+size;
    }

    if (DecodeAddr < gMaxOpRomAddress) {

        Status = CoreBiosInfo->iRegion->Decode (CoreBiosInfo->iRegion,
                     DecodeAddr,
                    (UINT32)((gMaxOpRomAddress+1)-DecodeAddr),
                    &On);
        ASSERT_EFI_ERROR(Status);
    }

    return Status;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        GetBbsTable
//
// Description: This function returns a pointer to the BBS table and the
//              number of entries.
//
// Output:      BbsTable - Pointer to BBS table.
//              BbsCount - Number of entries in table.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
GetBbsTable (
    IN OUT BBS_TABLE **BbsTable,
    IN OUT UINT8 *BbsCount
)
{
    if ((BbsTable == NULL) || (BbsCount == NULL)) 
        return EFI_INVALID_PARAMETER;

    if (CoreBiosInfo == NULL) 
        return EFI_NOT_READY;

    if (CoreBiosInfo->BbsTable == NULL)
        return EFI_NOT_READY;

    *BbsTable = CoreBiosInfo->BbsTable;
    *BbsCount = CoreBiosInfo->BbsEntriesNo;

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        AddBbsEntry
//
// Description: This function adds given BBS entry to a BBS table.
//
// Input:       BbsEntry - BBS table entry to be added to a table.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
AddBbsEntry (
    IN BBS_TABLE *BbsEntry
)
{
    if (gBbsUpdateInProgress) return EFI_NOT_READY;

    gBbsUpdateInProgress = TRUE;

    CoreBiosInfo->BbsTable[CoreBiosInfo->BbsEntriesNo] = *BbsEntry;
    CoreBiosInfo->BbsTable[CoreBiosInfo->BbsEntriesNo].BootPriority = BBS_UNPRIORITIZED_ENTRY;
    CoreBiosInfo->BbsEntriesNo++;

    gBbsUpdateInProgress = FALSE;

    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        InsertBbsEntryAt
//
// Description: This function is an extension of AddBbsEntry function; it
//              allows to add a BBS_ENTRY at a particular location or add
//              a new entry and return its new location.
//
// Input:       This        - Instance of LegacyBiosExt protocol.
//              EntryNumber - Pointer to 0-based index in BBS table. The
//                            value of 0xFF will generate a new entry.
//
// Output:      EFI_INVALID_PARAMETER - EntryNumber is NULL.
//              EFI_SUCCESS - EntryNumber is updated with the index of updated
//                            BBS entry.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
InsertBbsEntryAt (
    IN EFI_LEGACY_BIOS_EXT_PROTOCOL *This,
    IN BBS_TABLE *BbsEntry,
    IN OUT UINT8 *EntryNumber
)
{
    UINT8 EntryNo;

    if (gBbsUpdateInProgress) return EFI_NOT_READY;

    if (EntryNumber == NULL) return EFI_INVALID_PARAMETER;

    gBbsUpdateInProgress = TRUE;

    if (*EntryNumber != 0xff) {
        EntryNo = *EntryNumber;
    } else {
        //
        // Find an empty entry within MAX_IDE_CONTROLLER*2+1..BbsEntriesNo-1
        //
        for (EntryNo = MAX_IDE_CONTROLLER*2+1; EntryNo < CoreBiosInfo->BbsEntriesNo; EntryNo++)
        {
            if (CoreBiosInfo->BbsTable[EntryNo].BootPriority == BBS_IGNORE_ENTRY)
            {
                break;
            }
        }
        //
        // If not found, EntryNo will be equal BbsEntriesNo
        //
    }
    CoreBiosInfo->BbsTable[EntryNo] = *BbsEntry;
    CoreBiosInfo->BbsTable[EntryNo].BootPriority = BBS_UNPRIORITIZED_ENTRY;

    //
    // BbsEntriesNo should not be incremented for the BBS entries
    // with indexes from 0 to CoreBiosInfo->BbsEntriesNo-1
    //
    if (EntryNo >= CoreBiosInfo->BbsEntriesNo) {
        CoreBiosInfo->BbsEntriesNo++;
    }
    *EntryNumber = EntryNo;

    gBbsUpdateInProgress = FALSE;

    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        RemoveBbsEntryAt
//
// Description: This function removes BBS entry from BBS table.
//
// Input:       This        - Instance of LegacyBiosExt protocol.
//              EntryNumber - Entry index to be removed.
//
// Output:      EFI_INVALID_PARAMETER - EntryNumber exceeds the current table.
//              EFI_NOT_FOUND - Entry does not exist.
//              EFI_SUCCESS - Entry has been successfully removed.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
RemoveBbsEntryAt (
    IN EFI_LEGACY_BIOS_EXT_PROTOCOL *This,
    IN UINT8 EntryNumber
)
{
    EFI_STATUS Status = EFI_SUCCESS;

    if (gBbsUpdateInProgress) return EFI_NOT_READY;

    gBbsUpdateInProgress = TRUE;

    //
    // Can only remove a particular entry within 0..CoreBiosInfo->BbsEntriesNo-1 range;
    //
    if (EntryNumber >= CoreBiosInfo->BbsEntriesNo) Status = EFI_INVALID_PARAMETER;

    if (!EFI_ERROR(Status)) {
        if (CoreBiosInfo->BbsTable[EntryNumber].BootPriority == BBS_IGNORE_ENTRY) {
            Status = EFI_NOT_FOUND;
        }
    }

    if (!EFI_ERROR(Status)) {
        //
        // Decrement CoreBiosInfo->BbsEntriesNo only if requested index equals
        // CoreBiosInfo->BbsEntriesNo-1
        //
        if (EntryNumber == (CoreBiosInfo->BbsEntriesNo-1)) {
            CoreBiosInfo->BbsEntriesNo--;
        }
    
        pBS->SetMem(&CoreBiosInfo->BbsTable[EntryNumber], sizeof(BBS_TABLE), 0);
        CoreBiosInfo->BbsTable[EntryNumber].BootPriority = BBS_IGNORE_ENTRY;
    }

    gBbsUpdateInProgress = FALSE;

    return Status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	SignalProtocolEvent
//
// Description:	Internal function that installs/uninstall protocol
//				with a specified GUID and NULL interface.
//              Such protocols can be used as event signaling mechanism.
//
// Input:		ProtocolGuid Pointer to the protocol GUID
//
// Output:		None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
SignalAmiLegacyBootEvent()
{
    EFI_HANDLE  Handle = NULL;
    static EFI_GUID ProtocolGuid = EFI_AMI_LEGACYBOOT_PROTOCOL_GUID;
    pBS->InstallProtocolInterface (
        &Handle, &ProtocolGuid, EFI_NATIVE_INTERFACE, NULL
    );
    pBS->UninstallProtocolInterface (
        Handle, &ProtocolGuid, NULL
    );
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        ConnectSerialIO
//
// Description: Connect all the serial IO that was disconnected before.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID ConnectSerialIO()
{
    UINTN       n; 

    for (n = 0; n < gSerialIoHandleCount; n++) {
        pBS->ConnectController(gSerialIoHandleBuffer[n],NULL,NULL,TRUE);
    }

    return;

}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        DisconnectSerialIO
//
// Description: Disconnect the All the Serial io Handles
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID DisconnectSerialIO()
{
    UINTN       n; 
    EFI_STATUS  Status;
    EFI_DEVICE_PATH_PROTOCOL    *DevicePath;
  
    //
    // Locate all Serial IO handles
    //
    Status = pBS->LocateHandleBuffer (
        ByProtocol,
        &gEfiSerialIoProtocolGuid,
        NULL,
        &gSerialIoHandleCount,
        &gSerialIoHandleBuffer);

    if (EFI_ERROR (Status)) {
        return ;
    }

    for (n = 0; n < gSerialIoHandleCount; n++) {
        //
        // Check if we have DevicePath Protocol installed on Controller handle.
        // If not, do not disconnect the controller because it may not be handled
        // by the Serial IO drvier. 
        // 
        Status = pBS->HandleProtocol (
                        gSerialIoHandleBuffer[n],
                        &gEfiDevicePathProtocolGuid,
                        &DevicePath);

        if (!EFI_ERROR (Status)) {
            pBS->DisconnectController(gSerialIoHandleBuffer[n],NULL,NULL);
        }
    }

    return;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        IsAMICSM16
//
// Description:
//  This function checks whether the CSM16 image is made by AMI.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN
IsAMICSM16(
    EFI_COMPATIBILITY16_TABLE* Csm16Header
)
{
    // Check for "AMIBIOS(" at F000:F500
    return (*(UINT32*)0xff500 == 0x42494d41 &&
            *(UINT32*)0xff504 == 0x28534f49);
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:        ChecksumCSM16Header
//
// Description:
//  Calculates and updates a checksum field of $EFI header.
//
// Input:
//  Csm16Header Pointer to the EFI_COMPATIBILITY16_TABLE structure
//
// Output:
//  Checksum byte
//
// Notes:
//  Shadow region must be open for writing
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
ChecksumCSM16Header (
    EFI_COMPATIBILITY16_TABLE   *Csm16Header
)
{
    UINT8   i;
    UINT8   chksum;
    UINT8   *p;

    Csm16Header->TableChecksum = 0;
    p = (UINT8*)CoreBiosInfo->Csm16Header;
    for (chksum = 0, i = 0; i < Csm16Header->TableLength; i++) {
        chksum += *p++;
    }
    Csm16Header->TableChecksum = ~(--chksum);

    return Csm16Header->TableChecksum;
}

typedef struct {
    CSM16_FEATURE Feature;
    UINT8 Bit;
    UINT8 InfoByteOfs;
} CSM16_FEATURE_LOOKUP;


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        Csm16Configuration
//
// Description:
//  This is LegacyBiosExt interface function that manages CSM16 configuration
//  settings.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
Csm16Configuration(
    IN CSM16_CONFIGURATION_ACTION ConfigAction,
    IN CSM16_FEATURE Param,
    OUT OPTIONAL UINT32 *Data
)
{
    LEGACY16_TO_EFI_DATA_TABLE_STRUC *Csm16Data;
    UINT8 MiscInfo;
    UINT8 RtCmosByte;
    volatile UINT8 ProbeData = *(UINT8*)0xf0000;
    UINT32 Granularity;
    EFI_STATUS Status;
    BOOLEAN F000WasOpen;
    UINT32 i;
    UINT32 Count;

    static CSM16_FEATURE_LOOKUP Csm16Feature[] = {
        { Csm16HeadlessI19Retry, CSM16_HEADLESS_INT19_RETRY_BIT, 0 },
        { Csm16I13MbrWriteProtect, CSM16_I13_HDD_MBR_WP_BIT, 0 },
        { Csm16LegacyFree, CSM16_NO_KBC_PRESENT_BIT, 0 },
        { Csm16ZipHddEmulation, CSM16_ZIP_HDD_EMUL_BIT, 0 },
        { Csm16NoUsbBoot, CSM16_NO_USB_BOOT_BIT, 0 },
        { Csm16I19Trap, CSM16_I19_TRAP_BIT, 0 },
        { Csm16Flexboot, CSM16_FLEXBOOT_ENABLE_BIT, 0 },
        { Csm16GA20, CSM16_FAST_GATE_A20_BIT, 0 },
        { Csm16SkipGA20Deactivation, CSM_RT_CMOS_SKIP_GA20_DEACTIVATION_BIT, 1 },
        { Csm16Nmi, CSM_RT_CMOS_PARITY_BIT, 1 },
        { Csm16CpuRealModeOnBoot, CSM_RT_CPU_RM_ONBOOT_BIT, 1 },
        { Csm16PS2, CSM_RT_CMOS_PS2_BIT, 1 },
        { Csm16LegacyToEfi, CSM_RT_CMOS_LTE_BIT, 1 },
        { Csm16LegacyToEfiPonr, CSM_RT_CMOS_LTE_PONR_BIT, 1 }
    };

    Csm16Data = (LEGACY16_TO_EFI_DATA_TABLE_STRUC*)(UINTN)(0xf0000 + *(UINT16*)0xfff4c);
    MiscInfo = *(UINT8*)(UINTN)Csm16Data->MiscInfoAddress;
    RtCmosByte = *(UINT8*)(UINTN)Csm16Data->RtCmosByteAddress;
    
    // see if F000 needs to be made writable
    *(UINT8*)0xf0000 = ProbeData + 1;
    F000WasOpen = *(UINT8*)0xf0000 != ProbeData;
    if (F000WasOpen) {
        *(UINT8*)0xf0000 = ProbeData;    // restore byte
    } else {
        Status = CoreBiosInfo->iRegion->UnLock (CoreBiosInfo->iRegion, 0xf0000, 0x10000, &Granularity);
        ASSERT_EFI_ERROR(Status);
        if (EFI_ERROR(Status)) return EFI_ACCESS_DENIED;
    }

    // Find parameter in the lookup table
    Count = sizeof(Csm16Feature)/sizeof(CSM16_FEATURE_LOOKUP);
    for (i = 0; i < Count; i++) {
        if (Csm16Feature[i].Feature == Param) break;
    }
    
    if (i == Count) {
        Status = EFI_INVALID_PARAMETER;
        goto Done;
    }

    Status = EFI_SUCCESS;
    
    switch (ConfigAction) {
        case Csm16FeatureGet:
            if (Data == NULL) {
                Status = EFI_INVALID_PARAMETER; break;
            }
            if (Csm16Feature[i].InfoByteOfs == 0)
                *Data = (MiscInfo & Csm16Feature[i].Bit)? 1 : 0;
            else
                *Data = (RtCmosByte & Csm16Feature[i].Bit)? 1 : 0;
            break;

        case Csm16FeatureSet:
            if (Csm16Feature[i].InfoByteOfs == 0) {
                MiscInfo |= Csm16Feature[i].Bit;
                *(UINT8*)(UINTN)Csm16Data->MiscInfoAddress = MiscInfo;
            } else {
                RtCmosByte |= Csm16Feature[i].Bit;
                *(UINT8*)(UINTN)Csm16Data->RtCmosByteAddress = RtCmosByte;
            }
            break;

        case Csm16FeatureReset:
            if (Csm16Feature[i].InfoByteOfs == 0) {
                MiscInfo &= ~Csm16Feature[i].Bit;
                *(UINT8*)(UINTN)Csm16Data->MiscInfoAddress = MiscInfo;
            } else {
                RtCmosByte &= ~Csm16Feature[i].Bit;
                *(UINT8*)(UINTN)Csm16Data->RtCmosByteAddress = RtCmosByte;
            }
            break;

        default: ASSERT(FALSE); Status = EFI_INVALID_PARAMETER;
    }

Done:

    if (!F000WasOpen) {
        CoreBiosInfo->iRegion->Lock (CoreBiosInfo->iRegion, 0xf0000, 0x10000, &Granularity);
    }

    return Status;
}

//****************************************************************************
//****************************************************************************
//**                                                                        **
//**             (C)Copyright 1985-2009, American Megatrends, Inc.          **
//**                                                                        **
//**                          All Rights Reserved.                          **
//**                                                                        **
//**                  5555 Oakbrook Pkwy, Norcross, GA 30093                **
//**                                                                        **
//**                          Phone (770)-246-8600                          **
//**                                                                        **
//****************************************************************************
//****************************************************************************
