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
// $Header: /Alaska/SOURCE/Modules/CSM/Generic/Core/CsmBsp.c 39    8/06/14 4:40p Fasihm $
//
// $Revision: 39 $
//
// $Date: 8/06/14 4:40p $
//
//****************************************************************************

//**********************************************************************
//<AMI_FHDR_START>
//
//  Name:           CsmBsp.c
//
//  Description:
//    Compatibility Support Module - Board Support Package.
//    This driver implements LEGACY_BIOS_PLATFORM_PTOTOCOL interface functions.
//
//<AMI_FHDR_END>
//****************************************************************************

#include "Efi.h"
#include <Protocol/DevicePath.h>
#include <Protocol/LegacyBios.h>
#include <Protocol/LoadedImage.h>
#include "csm.h"
#include <AmiDxeLib.h>
#include <Protocol/LegacyBiosPlatform.h>
#include <Protocol/FirmwareVolumeBlock.h>
#include "token.h"
#include "setup.h"
#include "CsmElinkFunctions.h"

typedef EFI_STATUS (CSM_GET_OPROM_VIDEO_SWITCHING_MODE)(
    IN EFI_PCI_IO_PROTOCOL  *PciIo  OPTIONAL,
    IN UINT16               TextSwitchingMode,
    OUT UINTN               *SetTxtSwitchingMode);
extern CSM_GET_OPROM_VIDEO_SWITCHING_MODE CSM_GET_OPROM_VIDEO_SWITCHING_MODE_FUNCTIONS EndOfGetOpRomVideoModeFunctions;
CSM_GET_OPROM_VIDEO_SWITCHING_MODE *CsmGetOpRomVideoModeSwitchingFunctions[] = { CSM_GET_OPROM_VIDEO_SWITCHING_MODE_FUNCTIONS NULL };

typedef EFI_STATUS (CSM_GET_CUSTOM_PCI_PIRQ_MASK)(
    IN EFI_PCI_IO_PROTOCOL  *PciIo,
    IN UINT16               IrqMask,
    OUT UINTN               *ModifiedIrqMask);
extern CSM_GET_CUSTOM_PCI_PIRQ_MASK CSM_GET_CUSTOM_PCI_PIRQ_MASK_FUNCTIONS EndOfGetCustomPciPirqMaskFunctions;
CSM_GET_CUSTOM_PCI_PIRQ_MASK *CsmGetCustomPciPirqMaskFunctions[] = { CSM_GET_CUSTOM_PCI_PIRQ_MASK_FUNCTIONS NULL };

typedef EFI_STATUS (CSM_GET_GATE_A20_INFORMATION)(OUT UINTN *GateA20Info);
extern CSM_GET_GATE_A20_INFORMATION CSM_GET_GATE_A20_INFORMATION_FUNCTIONS EndOfGetGateA20InformationFunctions;
CSM_GET_GATE_A20_INFORMATION *CsmGetGateA20InformationFunctions[] = { CSM_GET_GATE_A20_INFORMATION_FUNCTIONS NULL };

typedef EFI_STATUS (CSM_GET_NMI_INFORMATION)(OUT UINTN   *NmiInfo);
extern CSM_GET_NMI_INFORMATION CSM_GET_NMI_INFORMATION_FUNCTIONS EndOfGetNmiInformationFunctions;
CSM_GET_NMI_INFORMATION *CsmGetNmiInformationFunctions[] = { CSM_GET_NMI_INFORMATION_FUNCTIONS NULL };

// Get Platform Handle ELINK function list
typedef EFI_STATUS (CSM_GET_PLATFORM_HANDLE)(
    EFI_LEGACY_BIOS_PLATFORM_PROTOCOL *This,
    EFI_GET_PLATFORM_HANDLE_MODE      Mode,
    UINT16                            Type,
    EFI_HANDLE                        **HandleBuffer,
    UINTN                             *HandleCount,
    VOID                              OPTIONAL **AdditionalData);
extern CSM_GET_PLATFORM_HANDLE CSM_GET_PLATFORM_HANDLE_FUNCTIONS EndOfPlatformHandleFunctions;
CSM_GET_PLATFORM_HANDLE *CsmGetPlatformFunctions[] = { CSM_GET_PLATFORM_HANDLE_FUNCTIONS NULL };

typedef EFI_STATUS (CSM_GET_PLATFORM_EMBEDDED_ROM)(UINT16 ModuleId, UINT16 VendorId, UINT16 DeviceId, VOID **ImageStart, UINTN *ImageSize);
extern CSM_GET_PLATFORM_EMBEDDED_ROM CSM_GET_PLATFORM_EMBEDDED_ROM_FUNCTIONS EndOfGetPlatformEmbeddedRomFunctions;
CSM_GET_PLATFORM_EMBEDDED_ROM *CsmGetPlatformEmbeddedRomFunctions[] = { CSM_GET_PLATFORM_EMBEDDED_ROM_FUNCTIONS NULL };

typedef EFI_STATUS (CSM_GET_PLATFORM_PCI_EMBEDDED_ROM)(IN EFI_PCI_IO_PROTOCOL *PciIo, OUT VOID **PciRom, OUT UINTN *PciRomSize);
extern CSM_GET_PLATFORM_PCI_EMBEDDED_ROM CSM_GET_PLATFORM_PCI_EMBEDDED_ROM_FUNCTIONS EndOfGetPlatformPciEmbeddedRomFunctions;
CSM_GET_PLATFORM_PCI_EMBEDDED_ROM *CsmGetPlatformPciEmbeddedRomFunctions[] = { CSM_GET_PLATFORM_PCI_EMBEDDED_ROM_FUNCTIONS NULL };

typedef EFI_STATUS (CSM_CHECK_OEM_PCI_SIBLINGS)(EFI_PCI_IO_PROTOCOL *PciIo, EXECUTED_PCI_ROM *ExecutedRom);
extern CSM_CHECK_OEM_PCI_SIBLINGS CSM_CHECK_OEM_PCI_SIBLINGS_FUNCTIONS EndOfCheckOemPciSiblingsFunctions;
CSM_CHECK_OEM_PCI_SIBLINGS *CsmCheckOemPciSiblingsFunctions[] = { CSM_CHECK_OEM_PCI_SIBLINGS_FUNCTIONS NULL };

typedef EFI_STATUS (CSM_ENABLE_OEM_PCI_SIBLINGS)(EFI_PCI_IO_PROTOCOL *PciIo);
extern CSM_ENABLE_OEM_PCI_SIBLINGS CSM_ENABLE_OEM_PCI_SIBLINGS_FUNCTIONS EndOfEnableOemPciSiblingsFunctions;
CSM_ENABLE_OEM_PCI_SIBLINGS *CsmEnableOemPciSiblingsFunctions[] = { CSM_ENABLE_OEM_PCI_SIBLINGS_FUNCTIONS NULL };

typedef EFI_STATUS (CSM_GET_ROUTING_TABLE)(
  IN  EFI_LEGACY_BIOS_PLATFORM_PROTOCOL   *This,
  OUT VOID                                **RoutingTable,
  OUT UINTN                               *RoutingTableEntries,
  OUT VOID                                **LocalPirqTable, OPTIONAL
  OUT UINTN                               *PirqTableSize, OPTIONAL
  OUT VOID                                **LocalIrqPriorityTable, OPTIONAL
  OUT UINTN                               *IrqPriorityTableEntries OPTIONAL);
extern CSM_GET_ROUTING_TABLE CSM_GET_ROUTING_TABLE_FUNCTIONS EndOfGetRoutingTableFunctions;
CSM_GET_ROUTING_TABLE *CsmGetRoutingTableFunctions[] = { CSM_GET_ROUTING_TABLE_FUNCTIONS NULL };

typedef EFI_STATUS (CSM_BSP_UPDATE_PRT)(IN EFI_LEGACY_BIOS_PROTOCOL *This, IN  VOID *RoutingTable);
extern CSM_BSP_UPDATE_PRT CSM_BSP_UPDATE_PRT_FUNCTIONS EndOfBspUpdatePrtFunctions;
CSM_BSP_UPDATE_PRT *CsmBspUpdatePrtFunctions[] = { CSM_BSP_UPDATE_PRT_FUNCTIONS NULL };

typedef EFI_STATUS (CSM_BSP_PREPARE_TO_BOOT)(   IN  EFI_LEGACY_BIOS_PLATFORM_PROTOCOL     *This,
                                                IN  BBS_BBS_DEVICE_PATH *BbsDevicePath,
                                                IN  VOID                *BbsTable,
                                                IN  UINT32              LoadOptionsSize,
                                                IN  VOID                *LoadOptions,
                                                IN  VOID                *EfiToLegacyBootTable);
extern CSM_BSP_PREPARE_TO_BOOT CSM_BSP_PREPARE_TO_BOOT_FUNCTIONS EndOfBspPrepareToBootFunctions;
CSM_BSP_PREPARE_TO_BOOT *CsmBspPrepareToBootFunctions[] = { CSM_BSP_PREPARE_TO_BOOT_FUNCTIONS NULL };

// end of CSM elink functions


PLATFORM_BIOS_INFO  *BspBiosInfo;


extern EFI_LEGACY_PIRQ_TABLE_HEADER *MsPrt;

//AMIIRQ_HEADER                 *AmiPrt;
extern EFI_LEGACY_IRQ_ROUTING_ENTRY *Prt;
BOOLEAN                         IsValidPrt;

EFI_STATUS InitPrt(EFI_LEGACY_BIOS_PLATFORM_PROTOCOL*);
EFI_STATUS Intx2Pirq (EFI_LEGACY_BIOS_PLATFORM_PROTOCOL*,
                UINTN, UINTN, UINTN, UINT8*, UINT8*, UINT16*);

extern VOID *EmbeddedRom;
extern UINTN EmbeddedRomSize;
extern UINT16 CurrentIrqMask;
extern UINTN    gUsedPciEntries;
extern SETUP_DATA   gSetup;

//
// The following table has a list of interrupts to be saved after
// CSM Init call and restored before LegacyBoot. The default list
// is defined in CSM.SDL and contains three interrups: int13, int15,
// and int40.
// This list can be expanded according to the project needs. Only
// MAX_NUM_IRQS_SAVERESTORE entries will be processed, others will
// be ignored.
//
UINT8 gInterruptsToPreserve[] = INTERRUPTS_TO_PRESERVE;

//
// The following table is the list of VID/DID (combined into DWORDs)
// that will have problems with BCV executed during early POST right
// after Option ROM is initialized, or problems with BCV executed
// multiple times during POST. The examples of such "problematic"
// BCVs would be trapping BIOS interrupts that are not BCV specific,
// allocating blocks of memory, etc.
// Note that for these devices BCV will be executed during PrepareToBoot;
// drivers that require BCV execution before that (CsmBlockIo) will not
// support these devices.
//
UINT32 gSkipBcvDeviceList[] = SKIP_EARLY_BCV_DEVICES;


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:        GetOpromVideoSwitchingMode
//
// Description: This function is called from LEGACY_BIOS.InstallPciRom()
//              before and after OpROM execution. It allows OEM override the
//              default video mode switching policy during OpROM execution.
//
// Input:
//
//  PciIo               PciIo protocol of the device associated with the OpROM;
//                      This is an optional field, if NULL then it is ignored.
//
//  TextSwitchingMode   The current text switching mode. Possible values are:
//                          0 - switching to text mode is needed;
//                          1 - switching is needed, restoration is not;
//                          2 - neither switching nor restoration is needed.
// Output:
//
//  SetTxtSwitchingMode The mode that will be used for this OpROM. The valid
//                      values are 0, 1, and 2. The meaning is the same as
//                      TextSwitchingMode (above).
//
//  EFI_SUCCESS         The value of SetTxtSwithcingMode is updated according
//                      to the platform policy and will be used for video mode
//                      switching for the given PciIo's Option ROM.
//
//  EFI_UNSUPPORTED     The value of SetTxtSwitchingMode is not valid.
//
//
// Notes:   This function can change the policy of video switching for selected
//          Option ROMs by looking up the PCI VID/DID. It also can change this
//          policy for all OpROMs.
//
//          Use SetTxtSwitchingMode value to adjust the platform policy. For
//          example, value equal to 1 probably indicates the end of the boot
//          process, when system is already in text mode and switching back
//          is not desired. In this case platform may choose not to interfere
//          with the default policy. This can be done by either returning
//          EFI_UNSUPPORTED or returning EFI_SUCCESS with SetTxtSwitchingMode
//          equal to TextSwitchingMode.
//
//          Returning EFI_SUCCESS must be carefully considered. If function
//          returns EFI_SUCCESS, please make sure SetTxtSwitchingMode is
//          assigned the valid values: 0, 1, 2 and 3. If the wrong value is
//          assigned, then video switching policy will fail.
//
//          The default implementation simply returns EFI_SUCCESS with the
//          SetTxtSwitchingMode set to the value passed in TextSwitchingMode.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
GetOpromVideoSwitchingMode(
    IN EFI_PCI_IO_PROTOCOL  *PciIo  OPTIONAL,
    IN UINT16               TextSwitchingMode,
    OUT UINTN               *SetTxtSwitchingMode
)
{
/*
// Here is an example of the platform implementation of this function.
    UINT32      VidDid;
    EFI_STATUS  Status;

    if (TextSwitchingMode == 1) return EFI_UNSUPPORTED; // see the notes

    if (PciIo == NULL) return EFI_UNSUPPORTED;

    //
    // Force mode switching for certaing PCI cards
    //
    Status = PciIo->Pci.Read(PciIo, EfiPciIoWidthUint32,
        0,  // offset
        1,  // width
        &VidDid);
    ASSERT_EFI_ERROR(Status);

    if (VidDid == 0x12345678) {
        *SetTxtSwitchingMode = 0;
        return EFI_SUCCESS;
    }
    return EFI_UNSUPPORTED;
*/

    EFI_STATUS Status;
    UINTN i = 0;

    // default value
    *SetTxtSwitchingMode = (UINTN)TextSwitchingMode;

    for(i = 0; CsmGetOpRomVideoModeSwitchingFunctions[i] != NULL; i++)
    {
        Status = CsmGetOpRomVideoModeSwitchingFunctions[i](PciIo, TextSwitchingMode, SetTxtSwitchingMode);
        if(!EFI_ERROR(Status)) break;
    }

    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:        GetCustomPciIrqMask
//
// Description: This function is called from PciInterrupts.ProgramPciIrq()
//              before programming PCI register 3C. This function is given
//              the PciIo of the device and a list of possible IRQ choices
//              for this device.
//              The possible IRQs are given in a form of UINT16 IRQ mask,
//              where 1 is a masked IRQ level.
//              This function can modify this list and return EFI_SUCCESS.
//              A caller then will AND the existing mask with the one returned
//              by this function. Note that this way the existing list can
//              only be shrunk, not extended.
//
// Input:
//
//  PciIo       PciIo protocol of the device
//
//  IrqMask     The current bit mask of IRQ levels available for this device
//
// Output:
//
//  ModifiedIrqMask     The value that a caller will use to OR with the existing
//                      mask.
//
//  EFI_SUCCESS         Function is returning a valid ModifiedIrqMask
//
//  EFI_UNSUPPORTED     Function is not ported for this PciIo, value returned
//                      in ModifiedIrqMask will be ignored.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
GetCustomPciIrqMask (
    IN EFI_PCI_IO_PROTOCOL  *PciIo,
    IN UINT16               IrqMask,
    OUT UINTN               *ModifiedIrqMask
)
{
/* Implementation example - force IRQ11 for device 0x12345678

    UINT32      VidDid;
    EFI_STATUS  Status;

    Status = PciIo->Pci.Read(PciIo, EfiPciIoWidthUint32,
        0,  // offset
        1,  // width
        &VidDid);
    ASSERT_EFI_ERROR(Status);

    if (VidDid == 0x12345678) {
        if (IrqMask & 0xF7FF) {
            *ModifiedIrqMask = 0xF7FF;  // leave only IRQ11 unmaksed
            return EFI_SUCCESS;
        }
    }

    return EFI_UNSUPPORTED;
*/

    EFI_STATUS Status = EFI_UNSUPPORTED;
    UINTN i = 0;

    // Set a default value
    *ModifiedIrqMask = IrqMask;

    for(i = 0; CsmGetCustomPciPirqMaskFunctions[i] != NULL; i++)
    {
        Status = CsmGetCustomPciPirqMaskFunctions[i](PciIo, IrqMask, ModifiedIrqMask);
        if(!EFI_ERROR(Status)) break;
    }

    return Status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:        GetGateA20Information
//
// Description: This function is called from LegacyBios entry point and it
//              returns the board specific information related to the way of
//              controlling GateA20. Two different aspects of GateA20 control
//              can be returned by this function:
//              1) Line GA20 can be activated/deactivated through KBC's GPIO
//                 (command D1), or through Port92 (Bit2).
//              2) Deactivation of GA20 is be desirable at all, any CSM16
//                 function related to deactivation will be skipped.
//
// Input:       None
//
// Output:      GateA20Info:
//                  BIT0    0 - GA20 controlled through KBC
//                          1 - GA20 controlled through Port92
//                  BIT1    0 - Do not skip GA20 deactivation
//                          1 - Skip GA20 deactivation
//  EFI_SUCCESS         GateA20Info has valid bits 0 and 1
//
//  EFI_UNSUPPORTED     Function is not supported, GateA20Info information
//                      is invalid; CSM core will use the default GA20 policy.
//
//  Note:       Skipping GA20 deactivation is needed when APs are running above
//              1MB; if GA20 is inactive, then any access >1MB may be invalid.
//              At the same time, keeping GA20 active all the time may fail the
//              applications that test GA20 enable/disable functionality. It may
//              also affect some applications that rely on GA20 being inactive
//              after legacy boot.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
GetGateA20Information(
    OUT UINTN   *GateA20Info
)
{
    EFI_STATUS Status;
    UINTN i = 0;

    // Set BIT0 if using Port92, Set BIT1 to skip GA20 deactivation
    if (gSetup.KeepGA20Active == 1) *GateA20Info = 3;
    else *GateA20Info = 1;

    for(i = 0; CsmGetGateA20InformationFunctions[i] != NULL; i++)
    {
        Status = CsmGetGateA20InformationFunctions[i](GateA20Info);
        if(!EFI_ERROR(Status)) break;
    }

    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:        GetNmiInformation
//
// Description:
//  This function is called from LegacyBios entry point and it returns the board
//  specific information related to NMI.
//
// Input:
//  None
//
// Output:
//  NMI information:
//      BIT0    0 - NMI should be kept disabled
//              1 - enable NMI
//  EFI_SUCCESS         GateA20Info has valid bits 0 and 1
//  EFI_UNSUPPORTED     Function is not supported, NMI information is invalid; CSM
//                      will use the default NMI policy.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
GetNmiInformation(
    OUT UINTN   *NmiInfo
)
{
    EFI_STATUS Status;
    UINTN i = 0;

    // prime the return value to enabled
    *NmiInfo = 1;

    for(i = 0; CsmGetNmiInformationFunctions[i] != NULL; i++)
    {
        Status = CsmGetNmiInformationFunctions[i](NmiInfo);
        if(!EFI_ERROR(Status)) break;
    }

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:    GetPlatformInfo
//
// Description: Finds the binary data or other platform information.
//              Refer to the subfunctions for additional information.
//
// Input:
//  This    Indicates the EFI_LEGACY_BIOS_PLATFORM_PROTOCOL instance.
//  Mode    Specifies what data to return:
//                EfiGetPlatformBinaryMpTable
//                EfiGetPlatformBinaryOemIntData
//                EfiGetPlatformBinaryOem16Data
//                EfiGetPlatformBinaryOem32Data
//                EfiGetPlatformBinaryTpmBinary
//                EfiGetPlatformBinarySystemRom
//                EfiGetPlatformPciExpressBase
//                EfiGetPlatformPmmSize
//                EfiGetPlatformEndRomShadowAddr
//                EfiGetPlatformOpromVideoMode
//                EfiGetPlatformIntSaveRestoreTable
//                EfiGetPlatformPciIrqMask
//                EfiGetPlatformGateA20Information
//
//  Table       Pointer to OEM legacy 16-bit code or data.
//  TableSize   Size of data.
//  Location    Location to place table.
//                  Bit 0 = 1 0xF0000 64 KB block.
//                  Bit 1 = 1 0xE0000 64 KB block.
//                  Note: Multiple bits can be set.
//  Alignment   Bit-mapped address alignment granularity. The first 
//                  nonzero bit from the right is the address granularity.
//  LegacySegment   Segment where EfiCompatibility code will place the 
//                  table or data.
//  LegacyOffset    Offset where EfiCompatibility code will place the 
//                  table or data.
//
// Output:
//      EFI_SUCCESS     The data was returned successfully.
//      EFI_UNSUPPORTED Mode is not supported on this platform.
//      EFI_NOT_FOUND   Binary image not found.
//
// Referrals: EFI_GET_PLATFORM_INFO_MODE
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
GetPlatformInfo (
  IN  EFI_LEGACY_BIOS_PLATFORM_PROTOCOL           *This,
  IN  EFI_GET_PLATFORM_INFO_MODE                  Mode,
  IN OUT VOID                                     **Table,
  IN OUT UINTN                                    *TableSize,
  IN OUT UINTN                                    *Location,
  OUT UINTN                                       *Alignment,
  IN UINT16                                       LegacySegment,
  IN UINT16                                       LegacyOffset
  )
{
    switch (Mode) {
        case EfiGetPlatformPmmSize:
            //
            // Return PMM area size below 1MB to be allocated in bytes.
            // This size should be a multiple of 32K
            //
            *TableSize = PMM_LOMEM_SIZE;
            //
            // Return PMM area size above 1MB to be allocated in bytes.
            // This size should be a multiple of 64k.
            // Note: This field is not bit-mapped for this function.
            //
            *Alignment = PMM_HIMEM_SIZE;
            return EFI_SUCCESS;

        case EfiGetPlatformEndRomShadowAddr:
            *Location = OPROM_MAX_ADDRESS;
            return EFI_SUCCESS;

        case EfiGetPlatformBinarySystemRom:
            return FindEmbeddedRom(CSM16_MODULEID, CSM16_VENDORID, CSM16_DEVICEID,
                    Table, TableSize);

        case EfiGetPlatformPciExpressBase:
            *(UINT64*)Location = PCIEX_BASE_ADDRESS;
            return EFI_SUCCESS;

        case EfiGetPlatformOpromVideoMode:
            return GetOpromVideoSwitchingMode((EFI_PCI_IO_PROTOCOL*)(*Table),
                    LegacySegment, TableSize);

        case EfiGetPlatformIntSaveRestoreTable:
            *Table = gInterruptsToPreserve;
            *TableSize = sizeof(gInterruptsToPreserve);
            return EFI_SUCCESS;

        case EfiGetPlatformPciIrqMask:
            return GetCustomPciIrqMask((EFI_PCI_IO_PROTOCOL*)(*Table),
                LegacySegment, Alignment);

        case EfiGetPlatformGateA20Information:
            return GetGateA20Information(Alignment);

        case EfiGetPlatformNmiInformation:
            return GetNmiInformation(Alignment);

        case EfiGetBcvSkipDeviceList:
            *Table = gSkipBcvDeviceList;
            *TableSize = sizeof(gSkipBcvDeviceList)/4;
            return EFI_SUCCESS;
    }

    return EFI_UNSUPPORTED;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:    GetPlatformHandle
//
// Description: Returns a buffer of handles for the requested subfunction.
//
// Input:
//  This            Indicates the EFI_LEGACY_BIOS_PLATFORM_PROTOCOL instance.
//  Mode            Specifies what handle to return.
//                      GetVgaHandle
//                      GetIdeHandle
//                      GetIsaBusHandle
//                      GetUsbHandle
//  Type            Handle Modifier - Mode specific
//  HandleBuffer    Pointer to buffer containing all Handles matching the 
//                  specified criteria. Handles are sorted in priority order.
//                  Type EFI_HANDLE is defined in InstallProtocolInterface()
//                  in the EFI 1.10 Specification.
//  HandleCount     Number of handles in HandleBuffer.
//  AdditionalData  Pointer to additional data returned - mode specific..
//
// Output:
//  EFI_SUCCESS The handle is valid.
//  EFI_UNSUPPORTED Mode is not supported on this platform.
//  EFI_NOT_FOUND   The handle is not known.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
GetPlatformHandle (
  IN  EFI_LEGACY_BIOS_PLATFORM_PROTOCOL     *This,
  IN  EFI_GET_PLATFORM_HANDLE_MODE          Mode,
  IN  UINT16                                Type,
  OUT EFI_HANDLE                            **HandleBuffer,
  OUT UINTN                                 *HandleCount,
  OUT VOID                                  OPTIONAL **AdditionalData
  )
{
    EFI_STATUS Status = EFI_UNSUPPORTED;
    UINT16 i = 0;

    for(i = 0; CsmGetPlatformFunctions[i] != NULL; i++)
    {
        // Call all ELINK functions until one returns EFI_SUCCESS
        Status = CsmGetPlatformFunctions[i](This, Mode, Type, HandleBuffer, HandleCount, AdditionalData);
        if(!EFI_ERROR(Status)) break;
    }
    return Status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:        GetPlatformPciEmbeddedRom
//
// Description: This function is called from CheckPciRom and allows OEM to
//              have a custom code that looks for a binary. 
//
// Input:       Same as in FindEmbeddedRom function.
//
// Output:      EFI_UNSUPPORTED - Function is not implemented
//              EFI_NOT_FOUND   - No ROM found
//              EFI_SUCCESS     - ROM is found, output is the same as
//                                in FindEmbeddedRom function.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
GetPlatformPciEmbeddedRom (
    IN EFI_PCI_IO_PROTOCOL  *PciIo,
	OUT VOID    **PciRom,
    OUT UINTN   *PciRomSize
)
{
    EFI_STATUS Status = EFI_UNSUPPORTED;
    UINTN i = 0;

    for(i = 0; CsmGetPlatformPciEmbeddedRomFunctions[i] != NULL; i++)
    {
        Status = CsmGetPlatformPciEmbeddedRomFunctions[i](PciIo, PciRom, PciRomSize);
        if(!EFI_ERROR(Status)) break;
    }
    return Status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:        GetPlatformEmbeddedRom
//
// Description:
//  This function is called from FindEmbeddedRom and allows OEM to have a custom
//  code that looks for a binary. By default all addon ROMs are packed as BINFILE
//  section. This function may be needed if binary is packed in a way that is
//  different from default (for example it can be FFS file, etc.).
//
// Input:
//  Same as in FindEmbeddedRom function.
//
// Output:
//  EFI_NOT_FOUND   No ROM found, or function is not implemented.
//  EFI_SUCCESS     ROM is found, output is the same as in FindEmbeddedRom
//                  function.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS GetPlatformEmbeddedRom(
    UINT16 ModuleId, UINT16 VendorId, UINT16 DeviceId, 
    VOID **ImageStart, UINTN *ImageSize)
{
    EFI_STATUS Status = EFI_NOT_FOUND;
    UINTN i = 0;

    for(i = 0; CsmGetPlatformEmbeddedRomFunctions[i] != NULL; i++)
    {
        Status = CsmGetPlatformEmbeddedRomFunctions[i](ModuleId, VendorId, DeviceId, ImageStart, ImageSize);
        if(!EFI_ERROR(Status)) break;
    }

    return Status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:        CheckOemPciSiblings
//
// Description:
//  This function checks whether a given PCI device can be controlled by one of
//  the Option ROMs that have been already executed.
//
// Input:
//  PciIo           PCI I/O protocol of the device whose Option ROM is about to
//                  execute
//  ExecutedRom     Pointer to the last element of EXECUTED_PCI_ROM structure
//
// Output:
//  EFI_UNSUPPORTED Function is not implemented, use the default 
//                  device match criteria
//  EFI_SUCCESS     Device can be managed by one of the loaded ROMs
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
CheckOemPciSiblings(
    EFI_PCI_IO_PROTOCOL *PciIo,
    EXECUTED_PCI_ROM *ExecutedRom
)
{
/* By default this function returns EFI_UNSUPPORTED to make every Option ROM execute
    One of the possible implementation is to execute only one Option ROM for all functions
    of the PCI device. The sample below implements this kind of policy. Uncomment if needed.

    EFI_STATUS  Status;
    UINTN       Seg, Bus, Dev, Func;
    EXECUTED_PCI_ROM    *er;

    // Go through ExecutedRoms and search for the ROM that has been executed for
    // similar device (PCI Bus/Dev match)
    Status = PciIo->GetLocation(PciIo, &Seg, &Bus, &Dev, &Func);
    ASSERT_EFI_ERROR(Status);

    for (er = ExecutedRom; er->Seg | er->Bus | er->Dev | er->Fun; er--) {
        if (er->Bus == Bus && er->Dev == Dev) {
            TRACE((TRACE_ALWAYS, "CSM OPROM: skip OpROM execution for device B%x/d%x/F%x.\n",
                Bus, Dev, Func));
            return EFI_SUCCESS;
        }
    }
*/
    EFI_STATUS Status = EFI_UNSUPPORTED;
    UINTN i = 0;

    for(i = 0; CsmCheckOemPciSiblingsFunctions[i] != NULL; i++)
    {
        Status = CsmCheckOemPciSiblingsFunctions[i](PciIo, ExecutedRom);
        if(!EFI_ERROR(Status)) break;
    }
    return Status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:        EnableOemPciSiblings
//
// Description:
//  This function enables devices on PCI bus that can be controlled by the Option
//  ROM associated with the given PCI device.
//
// Input:
//  PciIo   PCI I/O protocol of the device whose Option ROM is about to execute
//
// Output:
//  EFI_UNSUPPORTED     Function is not implemented
//  EFI_SUCCESS         Function has enabled all related devices
//
// Notes:
//  If OEM code can not decide for ALL related devices, it may enable only devices
//  it knows about, and still return EFI_UNSUPPORTED. In this case CSM Core will
//  finish the job.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
EnableOemPciSiblings(
    EFI_PCI_IO_PROTOCOL *PciIo
)
{
    EFI_STATUS Status = EFI_UNSUPPORTED;
    UINTN i = 0;

    for(i = 0; CsmEnableOemPciSiblingsFunctions[i] != NULL; i++)
    {
        Status = CsmEnableOemPciSiblingsFunctions[i](PciIo);
        if(!EFI_ERROR(Status)) break;
    }

    return Status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:    SmmInit
//
// Description: Loads and registers the Compatibility16 handler with the EFI SMM code.
//              In also updates EFI_TO_COMPATIBILITY16_BOOT_TABLE.SmmTable.
//
// Input:
// This     Indicates the EFI_LEGACY_BIOS_PLATFORM_PROTOCOL instance.
// EfiToCompatibility16BootTable    The boot table passed to the Compatibility16.
//
// Output:
//  EFI_SUCCESS         The SMM code loaded.
//  EFI_DEVICE_ERROR    The SMM code failed to load.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
SmmInit(
  IN  EFI_LEGACY_BIOS_PLATFORM_PROTOCOL   *This,
  IN  VOID                                *EfiToCompatibility16BootTable
  )
{
    SMM_TABLE *SmmTable;
    SMM_ENTRY *SmmEntry;
    EFI_STATUS Status;
    //
    // Currently this function is implemented for two SW SMI handlers: INT15_D042 and USB
    // change NUMBER_OF_CSM_SUPPORTED_SW_SMIS and add the new SMM_ENTRYs if needed
    //
    #define NUMBER_OF_CSM_SUPPORTED_SW_SMIS 2

    Status = pBS->AllocatePool(EfiBootServicesData,
        sizeof (SMM_TABLE) + NUMBER_OF_CSM_SUPPORTED_SW_SMIS * sizeof(SMM_ENTRY),
        &SmmTable);
    ASSERT_EFI_ERROR (Status);
    pBS->SetMem(SmmTable,
        sizeof(SMM_TABLE) + NUMBER_OF_CSM_SUPPORTED_SW_SMIS * sizeof(SMM_ENTRY), 0);

    //
    // Fill in two SMM entries - one for INT15 func D042, another for USB
    //
    SmmTable->NumSmmEntries = NUMBER_OF_CSM_SUPPORTED_SW_SMIS;

    SmmEntry = &SmmTable->SmmEntry;

    SmmEntry->SmmAttributes.Type = STANDARD_IO;
    SmmEntry->SmmAttributes.PortGranularity = PORT_SIZE_16;
    SmmEntry->SmmAttributes.DataGranularity = DATA_SIZE_8;
    SmmEntry->SmmFunction.Function = INT15_D042;
    SmmEntry->SmmFunction.Owner = STANDARD_OWNER;
    SmmEntry->SmmPort = SW_SMI_IO_ADDRESS;
    SmmEntry->SmmData = INT15_D042_SWSMI;
    SmmEntry++;
    //
    // SmmPort and SmmData are UINT16 data fields, in our case SmmEntry data is UINT8.
    // We need to adjust the pointer to the next SmmEntry accofdingly so that CSM16 will
    // find it correctly.
    //
    (UINT8*)SmmEntry = (UINT8*)SmmEntry - 1;

    SmmEntry->SmmAttributes.Type = STANDARD_IO;
    SmmEntry->SmmAttributes.PortGranularity = PORT_SIZE_16;
    SmmEntry->SmmAttributes.DataGranularity = DATA_SIZE_8;
    SmmEntry->SmmFunction.Function = GET_USB_BOOT_INFO;
    SmmEntry->SmmFunction.Owner = STANDARD_OWNER;
    SmmEntry->SmmPort = SW_SMI_IO_ADDRESS;
    SmmEntry->SmmData = USB_SWSMI;

//TODOx64: What is SmmTable pointer is more the 4G in 64 bit mode?
//CSM specification 0.96 defines the pointer as UINT32
    ((EFI_TO_COMPATIBILITY16_BOOT_TABLE*)EfiToCompatibility16BootTable)->SmmTable = (UINT32)SmmTable;

    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:    ShadowServiceRoms
//
// Description: Executes Option ROMs that are not associated with PCI device,
//              e.g. PXE base code image.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
ShadowServiceRoms (
  IN  EFI_LEGACY_BIOS_PLATFORM_PROTOCOL *This
)
{
    void    *RomImageStart;
    UINTN   RomImageSize;
    EFI_STATUS  Status;
    EFI_LEGACY_BIOS_PROTOCOL *iLegacyBios;
    UINTN   Flags;
    UINTN       NoHandles;
    EFI_HANDLE  *HandleBuffer;

#pragma pack(push,1)
    typedef struct{
        UINT16 ModuleId, VendorId, DeviceId;
        UINT32 Size;
    } OPROM_HEADER;
#pragma pack(pop)
    OPROM_HEADER *Header;

    Status = pBS->LocateHandleBuffer (
        ByProtocol,
        &gEfiLegacyBiosProtocolGuid,
        NULL,
        &NoHandles,
        &HandleBuffer);
    if (EFI_ERROR(Status)) return Status;

    Status = pBS->HandleProtocol(
            HandleBuffer[0],
            &gEfiLegacyBiosProtocolGuid,
            &iLegacyBios
            );
    pBS->FreePool(HandleBuffer);
    if (EFI_ERROR(Status)) return Status;

    Status = FindEmbeddedRom(SERVICEROM_MODULEID, 0, 0, &RomImageStart, &RomImageSize);
    if (EFI_ERROR(Status)) return Status;

    //
    // Execute InstallPciRom for service ROMs: the 1st service ROM is pointed by
    // RomImageStart; install this ROM and all consequent service ROMs
    //
    do {
        TRACE((-1, "CsmBsp: Installing service ROM, %x...", RomImageStart));
        Status = iLegacyBios->InstallPciRom(
                    iLegacyBios,
                    NULL,   // PciHandle;
                    &RomImageStart,
                    &Flags,
                    NULL, NULL, NULL, NULL);
        ASSERT_EFI_ERROR(Status);
        if (EFI_ERROR(Status)) return Status;

        Header = (OPROM_HEADER*)RomImageStart-1;
        TRACE((-1, "...OK, size %x\n", Header->Size));
        Header = (OPROM_HEADER*)((UINT8*)RomImageStart+Header->Size);
        RomImageStart = Header+1;
    } while(Header->ModuleId == SERVICEROM_MODULEID);

    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:    PlatformHooks
//
// Description: Allows platform to perform any required action after a LegacyBios
//              operation.
// Input:
//  DeviceHandle    List of PCI devices in the system. Type EFI_HANDLE is defined in
//                  InstallProtocolInterface() in the EFI 1.10 Specification.
//  ShadowAddress   First free OpROM area, after other OpROMs have been dispatched..
//  Compatibility16Table    Pointer to the Compatibility16 Table.
//  AdditionalData          Pointer to additional data returned - mode specific..
//
// Output:
//  EFI_SUCCESS     The operation performed successfully.
//  EFI_UNSUPPORTED Mode is not supported on this platform.
//  EFI_SUCCESS     Mode specific.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
PlatformHooks (
  IN  EFI_LEGACY_BIOS_PLATFORM_PROTOCOL *This,
  IN  EFI_GET_PLATFORM_HOOK_MODE        Mode,
  IN  UINT16                            Type,
  IN  EFI_HANDLE                        OPTIONAL DeviceHandle,
  IN OUT UINTN                          OPTIONAL *ShadowAddress,
  IN EFI_COMPATIBILITY16_TABLE          OPTIONAL *Compatibility16Table,
  OUT VOID                              OPTIONAL **AdditionalData
  )
{
    switch (Mode) {
        case EfiPlatformHookPrepareToScanRom:
            return EFI_UNSUPPORTED;
        case EfiPlatformHookShadowServiceRoms:
            return ShadowServiceRoms(This);
        case EfiPlatformHookAfterRomInit:
            return EFI_UNSUPPORTED;
    }
    return EFI_UNSUPPORTED;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:    GetRoutingTable
//
// Description: Returns information associated with PCI IRQ routing.
//
// Input:
//  This            Indicates the EFI_LEGACY_BIOS_PLATFORM_PROTOCOL instance.
//  RoutingTable    Pointer to the PCI IRQ routing table. This location is
//                  the $PIR table minus the header. The contents is defined
//                  by the PCI IRQ Routing Table Specification; it has the 
//                  number of RoutingTableEntries of EFI_LEGACY_IRQ_ROUTING_ENTRY.
//  RoutingTableEntries     Number of entries in the PCI IRQ routing table.
//  LocalPirqTable          $PIR table. It contains EFI_LEGACY_PIRQ_TABLE_HEADER,
//                          immediately followed by RoutingTable.
//  PirqTableSize           Size of $PIR table.
//  LocalIrqPriorityTable   A priority table of IRQs to assign to PCI. This table 
//                          has IrqPriorityTableEntries entries of
//                          EFI_LEGACY_IRQ_PRIORITY_TABLE_ENTRY type and is used to 
//                          prioritize the allocation of IRQs to PCI.
//  IrqPriorityTableEntries Number of entries in the priority table.
//
// Output:
//  EFI_SUCCESS Data was returned successfully.
//
// Referrals:
//  EFI_LEGACY_BIOS_PLATFORM_PROTOCOL, EFI_LEGACY_IRQ_ROUTING_ENTRY,
//  EFI_LEGACY_PIRQ_TABLE_HEADER, EFI_LEGACY_IRQ_PRIORITY_TABLE_ENTRY
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
GetRoutingTable(
  IN  EFI_LEGACY_BIOS_PLATFORM_PROTOCOL   *This,
  OUT VOID                                **RoutingTable,
  OUT UINTN                               *RoutingTableEntries,
  OUT VOID                                **LocalPirqTable, OPTIONAL
  OUT UINTN                               *PirqTableSize, OPTIONAL
  OUT VOID                                **LocalIrqPriorityTable, OPTIONAL
  OUT UINTN                               *IrqPriorityTableEntries OPTIONAL
  )
{
    UINTN i = 0;
    EFI_STATUS Status = EFI_NOT_READY;

    if(IsValidPrt)
    {
        *RoutingTable = Prt;
    //  *RoutingTableEntries = AmiPrt->bUsedEntries;
        *RoutingTableEntries = gUsedPciEntries;
        if (LocalPirqTable != NULL) *LocalPirqTable = MsPrt;
        if (PirqTableSize != NULL) *PirqTableSize = MsPrt->TableSize;
        if (LocalIrqPriorityTable != NULL || IrqPriorityTableEntries != NULL) return EFI_UNSUPPORTED;
        Status = EFI_SUCCESS;

        for(i = 0; CsmGetRoutingTableFunctions[i] != NULL; i++)
        {
            // Do not check the return status incase there are multiple functions that update
            //  each of the tables individually.
            Status = CsmGetRoutingTableFunctions[i](This, 
                                                    RoutingTable, 
                                                    RoutingTableEntries, 
                                                    LocalPirqTable, 
                                                    PirqTableSize, 
                                                    LocalIrqPriorityTable, 
                                                    IrqPriorityTableEntries);
        }
    }
    return Status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:    BspUpdatePrt
//
// Description: This function is called from PciInterrupts.c when PCI Interrupt
//              routing table is ready for copying to shadow memory. Do the final
//              updates of the routing information. 
//
// Input:
//  This            Indicates the EFI_LEGACY_BIOS_PLATFORM_PROTOCOL instance.
//  RoutingTable    Pointer to the PCI IRQ routing table. This location is
//                  the $PIR table. The contents is defined by the PCI IRQ 
//                  Routing Table Specification; it has the  number of
//                  RoutingTableEntries of EFI_LEGACY_IRQ_ROUTING_ENTRY.
//
// Output:
//  EFI_SUCCESS Data was updated successfully.
//
// Notes:           Checksum of the table is not required in this routine, it will
//                  be done after this call is executed.
//
// Referrals:
//  EFI_LEGACY_BIOS_PLATFORM_PROTOCOL, EFI_LEGACY_IRQ_ROUTING_ENTRY,
//  EFI_LEGACY_PIRQ_TABLE_HEADER, EFI_LEGACY_IRQ_PRIORITY_TABLE_ENTRY
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
BspUpdatePrt(
  IN  EFI_LEGACY_BIOS_PROTOCOL   *This,
  IN  VOID                       *RoutingTable
)
{
    UINTN i = 0;
    EFI_STATUS Status = EFI_UNSUPPORTED;

    for(i = 0; CsmBspUpdatePrtFunctions[i] != NULL; i++)
    {
        Status = CsmBspUpdatePrtFunctions[i](This, RoutingTable);
        if(!EFI_ERROR(Status)) break;
    }

    return Status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:        TranslatePirq
//
// Description: This function translates the given PIRQ back through all
//              buses, if required, and returns the true PIRQ and associated IRQ.
// Input:
//  This        Indicates the EFI_LEGACY_BIOS_PLATFORM_PROTOCOL instance.
//  PciBus      PCI bus number for this device.
//  PciDevice   PCI device number for this device.
//  PciFunction PCI function number for this device.
//  Pirq        The PIRQ. PIRQ A = 0, PIRQ B = 1, and so on.
//  PirqIrq     IRQ assigned to the indicated PIRQ.
//
// Output:
//  EFI_SUCCESS The PIRQ was translated.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
TranslatePirq (
  IN  EFI_LEGACY_BIOS_PLATFORM_PROTOCOL  *This,
  IN  UINTN                              PciBus,
  IN  UINTN                              PciDevice,
  IN  UINTN                              PciFunction,
  IN  OUT UINT8                          *Pirq,
  OUT UINT8                              *PciIrq
  )
{
    return  Intx2Pirq(
                This,
                PciBus, PciDevice, PciFunction,
                Pirq, PciIrq, NULL);
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:        BspPrepareToBoot
//
// Description: Prepares the attempt to boot a traditional OS.
//
// Input:
//  This            Indicates the EFI_LEGACY_BIOS_PLATFORM_PROTOCOL instance.
//  BbsDevicePath   EFI Device Path from BootXXXX variable. Type 
//                  BBS_BBS_DEVICE_PATH is defined in EFI_LEGACY_BIOS_PROTOCOL.LegacyBoot().
//  BbsTable        A list of BBS entries of type BBS_TABLE. Type BBS_TABLE is 
//                  defined in Compatibility16PrepareToBoot().
//  LoadOptionsSize Size of LoadOption in bytes.
//  LoadOptions     LoadOption from BootXXXX variable.
//  EfiToLegacyBootTable    Pointer to EFI_TO_COMPATIBILITY16_BOOT_TABLE. Type
//                  EFI_TO_COMPATIBILITY16_BOOT_TABLE is defined
//                  in Compatibility16PrepareToBoot().
// Output:
//  EFI_SUCCESS Ready to boot.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
BspPrepareToBoot (
  IN  EFI_LEGACY_BIOS_PLATFORM_PROTOCOL     *This,
  IN  BBS_BBS_DEVICE_PATH                   *BbsDevicePath,
  IN  VOID                                  *BbsTable,
  IN  UINT32                                LoadOptionsSize,
  IN  VOID                                  *LoadOptions,
  IN  VOID                                  *EfiToLegacyBootTable
  )
{
    EFI_STATUS Status = EFI_UNSUPPORTED;
    UINTN i = 0;

    for(i = 0; CsmBspPrepareToBootFunctions[i] != NULL; i++)
    {
        Status = CsmBspPrepareToBootFunctions[i](This, BbsDevicePath, BbsTable, LoadOptionsSize, LoadOptions, EfiToLegacyBootTable);
        if(!EFI_ERROR(Status)) break;
    }
    return Status;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:  InitCsmBoard
//
// Description: CSM BSP driver entry point, it will instantinate
//              LEGACY_BIOS_PLATFORM_PTOTOCOL interface
//
// Input:       Standard EFI Image entry - EFI_IMAGE_ENTRY_POINT
//
// Output:      The status of CSM board initalization
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
InitCsmBoard (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
    EFI_STATUS          Status;
    EFI_LOADED_IMAGE_PROTOCOL   *LoadedImage;
    EFI_GUID            gFile;
    EFI_FIRMWARE_VOLUME_PROTOCOL    *pFV;
    UINT32              Authentication;

//  InitAmiLib(ImageHandle, SystemTable);
    Status = pBS->AllocatePool(
        EfiBootServicesData,
        sizeof(PLATFORM_BIOS_INFO),
        &BspBiosInfo);
    if (EFI_ERROR(Status)) return Status;

    pBS->SetMem(BspBiosInfo, sizeof(PLATFORM_BIOS_INFO), 0);

    //
    // Get LOADED_IMAGE protocol in order to get to the file name GUID
    //
    Status = pBS->HandleProtocol(
        ImageHandle, &gEfiLoadedImageProtocolGuid, &LoadedImage);
    if (EFI_ERROR(Status)) return Status;

    //
    // Now we have EFI_DEVICE_PATH_PROTOCOL *LoadedImage->FilePath
    //
    gFile = ((MEDIA_FW_VOL_FILEPATH_DEVICE_PATH*)(LoadedImage->FilePath))->NameGuid;

    //
    // Get the Firmware Volume Protocol
    //
    Status = pBS->HandleProtocol (
                LoadedImage->DeviceHandle,
                &gEfiFirmwareVolumeProtocolGuid,
                &pFV
    );
    if (EFI_ERROR(Status)) return Status;

    //
    // Read section with Legacy ROMs
    //
    EmbeddedRom = NULL;     // make ReadSection allocate memory
    EmbeddedRomSize = 0;
    Status = pFV->ReadSection (
                 pFV,
                 &gFile,
                 EFI_SECTION_RAW,
                 0,
                 &EmbeddedRom,
                 &EmbeddedRomSize,
                 &Authentication);
    if (EFI_ERROR(Status)) return Status;

    BspBiosInfo->hImage = ImageHandle;
    BspBiosInfo->iBiosPlatform.GetPlatformInfo      = GetPlatformInfo;
    BspBiosInfo->iBiosPlatform.GetPlatformHandle    = GetPlatformHandle;
    BspBiosInfo->iBiosPlatform.SmmInit              = SmmInit;
    BspBiosInfo->iBiosPlatform.PlatformHooks        = PlatformHooks;
    BspBiosInfo->iBiosPlatform.GetRoutingTable      = GetRoutingTable;
    BspBiosInfo->iBiosPlatform.TranslatePirq        = TranslatePirq;
    BspBiosInfo->iBiosPlatform.PrepareToBoot        = BspPrepareToBoot;

    InitPrt(&BspBiosInfo->iBiosPlatform);

    //
    // Make a new handle and install the protocol
    //
    BspBiosInfo->hBios = NULL;
    Status = pBS->InstallProtocolInterface (
                &BspBiosInfo->hBios,
                &gEfiLegacyBiosPlatformProtocolGuid,
                EFI_NATIVE_INTERFACE,
                &BspBiosInfo->iBiosPlatform
    );

    return EFI_SUCCESS;
}


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
