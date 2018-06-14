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
// $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/SBCspLib.h 11    5/16/14 6:16a Barretlin $
//
// $Revision: 11 $
//
// $Date: 5/16/14 6:16a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/SBCspLib.h $
// 
// 11    5/16/14 6:16a Barretlin
// [TAG]  		EIP167087
// [Category]  	Improvement
// [Description]  	BIOS security improvement on Haswell CRB project
// [Files]  		SBGeneric.c SBDxe.c SBCspLib.h Sb.sdl Sb.sd
// 
// 10    4/19/13 6:36a Wesleychen
// [TAG]           None
// [Category]      Improvement
// [Description]   Update GbES02SxWorkaround() and add 
//                 UsbS02SxWorkaround() for SBPwrBtnHandler().
// [Files]         SBSMI.c; SBSMI.h; SBGeneric.c; SBCspLib.h
// 
// 9     3/19/13 8:33a Scottyang
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Improve alternate access mode enable/disable routine.
// [Files]  		SBGeneric.c, SBCspLib.h, SBSMI.c
// 
// 8     1/10/13 8:20a Scottyang
// [TAG]  		EIP111666
// [Category]  	New Feature
// [Description]  	Support OEM reset callback function Elink.
// [Files]  		SB.mak, SBCspLib.h, SBGeneric.c, SB.sdl, PchReset.c
// 
// 7     11/21/12 3:07a Scottyang
// 
// 5     9/12/12 5:17a Victortu
// [TAG]           None
// [Category]      Improvement
// [Description]   Remove useless HdmiVerbTable.
// [Files]         SB.sdl, SBCspLib.h, SBDxe.c, SBGeneric.c 
// 
// 4     8/24/12 6:49a Victortu
// [TAG]           None
// [Category]      Improvement
// [Description]   Remove useless SB_SHADOW_CONTROL.
// [Files]         SB.sdl, SBCspLib.h, SBGeneric.c
// 
// 3     8/13/12 10:25a Victortu
// [TAG]           None
// [Category]      Improvement
// [Description]   Implement BIOS Lock function.
// [Files]         SBCspLib.h, SBDxe.c, SBSMI.c, SBSMI.dxs, SBSMI.sdl
// 
// 2     7/02/12 10:18a Victortu
// [TAG]		None
// [Category]	Improvement
// [Description]	Updated and modified for PCH RC 0.6.0.
// [Files]		SBGeneric.c, SB.sdl, SBCspLib.h, SBDxe.c, SBPEI.c
// 
// 1     2/08/12 8:24a Yurenlai
// Intel Lynx Point/SB eChipset initially releases.
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:        SBCspLib.h
//
// Description: This file contains South Bridge chipset porting functions
//              and data structures definition for both PEI & DXE stage.
//
//<AMI_FHDR_END>
//*************************************************************************

#ifndef __SBLIB_H__
#define __SBLIB_H__

//---------------------------------------------------------------------------
#include <Token.h>
#include <Efi.h>
#include <Pei.h>
#include <AmiDxeLib.h>
#include <PciBus.h>
#include <ppi\ReadOnlyVariable2.h>
#include <Protocol\PciRootBridgeIo.h>
#include <Protocol\PciIo.h>
#include <Protocol\AmiSio.h>

#if ACPI_SUPPORT
 #if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x0001000A)
 #include <Protocol\S3SaveState.h>
 #else
 #include <Protocol\BootScriptSave.h>
 #endif
#endif


#if     CSM_SUPPORT
#include <Protocol\LegacyInterrupt.h>
#endif

#ifndef AMI_S3_SAVE_PROTOCOL
 #if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x0001000A)
#define AMI_S3_SAVE_PROTOCOL EFI_S3_SAVE_STATE_PROTOCOL
#define AMI_S3_SAVE_PROTOCOL_GUID &gEfiS3SaveStateProtocolGuid
 #else
#define AMI_S3_SAVE_PROTOCOL EFI_BOOT_SCRIPT_SAVE_PROTOCOL
#define AMI_S3_SAVE_PROTOCOL_GUID &gEfiBootScriptSaveGuid
 #endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifndef CORE_VERSION
#define CORE_VERSION ( CORE_MAJOR_VERSION * 1000 + \
                       CORE_MINOR_VERSION * 100 + \
                       CORE_REVISION * 10 + \
                       CORE_BUILD_NUMBER )
#endif

#ifndef PCIBUS_VERSION
#define PCIBUS_VERSION ( PCI_BUS_MAJOR_VER * 10000 + \
                         PCI_BUS_MINOR_VER * 100 + \
                         PCI_BUS_REVISION )
#endif 

#define COMPLETE_SAVE_RESTORE_STD_CMOS  0x00
#define ENABLE_NMI_BEFORE_SMI_EXIT      0x01
#define DISABLE_NMI_BEFORE_SMI_EXIT     0x02

#ifndef EFI_SIGNATURE_16
#define EFI_SIGNATURE_16(A, B)  ((A) | (B << 8))
#endif

#ifndef EFI_SIGNATURE_32
#define EFI_SIGNATURE_32(A, B, C, D)  (EFI_SIGNATURE_16 (A, B) | (EFI_SIGNATURE_16 (C, D) << 16))
#endif

#define  KBShift  10
#define  MBShift  20

typedef enum {
  PchH          = 1,
  PchLp,
  PchUnknownSeries
} PCH_SERIES;

// Type Definition(s)

typedef struct {
    UINT64                      Address;
    EFI_BOOT_SCRIPT_WIDTH       Width;
    UINT32                      Mask;
} BOOT_SCRIPT_SB_PCI_REG_SAVE;

typedef enum {
    SbResetFull,
    SbResetGlobal
} SB_EXT_RESET_TYPE;

typedef enum {
  AnyType,
  DescriptorType,
  BiosType,
  MeType,
  GbeType,
  PlatformDataType,
  DeviceExpansionType,
  SecondaryBiosType,
  BfpregType,
  PchSpiRangeTypeMax
} AMI_SB_SPI_RANGE_TYPE;

typedef struct{
  UINTN   ProtectedRangeType;
  BOOLEAN WriteProtectEnable;
  BOOLEAN ReadProtectEnable;
  UINTN   ProtectedRangeBase;
  UINTN   ProtectedRangeLength;
} SPI_PROTECTED_RANGE_CONIFG;

#if     CSM_SUPPORT

EFI_STATUS SBGen_InitializeRouterRegisters (
    IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *PciRBIo
);

UINT8 SBGen_GetPIRQIndex (
    IN UINT8       PIRQRegister
);

EFI_STATUS SBGen_ReadPirq (
    IN EFI_LEGACY_INTERRUPT_PROTOCOL    *This,
    IN UINT8                            PirqNumber,
    OUT UINT8                           *PirqData
);

EFI_STATUS SBGen_WritePirq (
    IN EFI_LEGACY_INTERRUPT_PROTOCOL    *This,
    IN UINT8                            PirqNumber,
    IN UINT8                            PirqData
);

#endif

EFI_STATUS SBProtectedPciDevice (
    IN PCI_DEV_INFO                     *PciDevice
);

EFI_STATUS SBProgramPciDevice (
    IN PCI_DEV_INFO                     *PciDevice
);

EFI_STATUS SBUpdatePciDeviceAttributes (
    IN PCI_DEV_INFO                     *PciDevice,
    IN OUT UINT64                       *Attributes,
    IN UINT64                           Capabilities,
    IN BOOLEAN                          Set
);

EFI_STATUS ReadSPIDescriptor (
  IN UINT8 FDSS,
  IN UINT8 FDSI,
  OUT UINT32 *FDOD
);

UINT32 GetTotalFlashRomSize( VOID );

EFI_STATUS SbGetSpiRangeAddresses(
  IN   AMI_SB_SPI_RANGE_TYPE    RangeType,
  OUT  UINT32                   *BaseAddress,
  OUT  UINT32                   *EndAddress
);

EFI_STATUS SbFlashProtectedRange( VOID );

UINT32 SbFindCapPtr(
 IN UINT64  PciAddress,
 IN UINT8   CapId
);

VOID SBSwSmiWriteToBootScript (
    IN AMI_S3_SAVE_PROTOCOL             *BootScriptSave
);

EFI_STATUS SBGen_WriteBootScript (
    IN AMI_S3_SAVE_PROTOCOL             *BootScriptSave
);

VOID WriteIo8IdxDataS3 (
    IN AMI_S3_SAVE_PROTOCOL             *mBootScriptSave,
    IN UINT16                           IoBase16,
    IN UINT8                            IoReg8,
    IN UINT8                            WriteValue8
);

VOID RwIo8IdxDataS3 (
    IN AMI_S3_SAVE_PROTOCOL             *mBootScriptSave,
    IN UINT16                           IoBase16,
    IN UINT8                            IoReg8,
    IN UINT8                            SetBit8,
    IN UINT8                            ResetBit8
);

VOID WriteIo8S3 (
    IN AMI_S3_SAVE_PROTOCOL             *mBootScriptSave,
    IN UINT16                           IoBaseReg16,
    IN UINT8                            WriteValue8
);

VOID WriteIo16S3 (
    IN AMI_S3_SAVE_PROTOCOL             *mBootScriptSave,
    IN UINT16                           IoBaseReg16,
    IN UINT16                           WriteValue16
);

VOID WriteIo32S3 (
    IN AMI_S3_SAVE_PROTOCOL             *mBootScriptSave,
    IN UINT16                           IoBaseReg16,
    IN UINT32                           WriteValue32
);

VOID RwIo8S3(
    IN AMI_S3_SAVE_PROTOCOL             *mBootScriptSave,
    IN UINT16                           IoBaseReg16,
    IN UINT8                            SetBit8,
    IN UINT8                            ResetBit8
);

VOID RwIo16S3(
    IN AMI_S3_SAVE_PROTOCOL             *mBootScriptSave,
    IN UINT16                           IoBaseReg16,
    IN UINT16                           SetBit16,
    IN UINT16                           ResetBit16
);

VOID RwIo32S3(
    IN AMI_S3_SAVE_PROTOCOL             *mBootScriptSave,
    IN UINT16                           IoBaseReg16,
    IN UINT32                           SetBit32,
    IN UINT32                           ResetBit32
);

VOID SBLib_BeforeShutdown ( VOID );

VOID SBLib_Shutdown ( VOID );
VOID GbES0ToS1Workaround(VOID);
VOID GbES0ToSxWorkaround(VOID);
VOID Enable_GbE_PME(VOID);
VOID ClearMeWakeSts(VOID);
VOID EHCIAdditionalRequirement(VOID);

BOOLEAN SBIsDefaultConfigMode (
    IN EFI_PEI_SERVICES                 **PeiServices,
    IN EFI_PEI_READ_ONLY_VARIABLE2_PPI  *ReadVariablePpi
);

UINT8 SBLib_CmosRead(
  IN UINT8 Index
);

VOID SBLib_CmosWrite(
  IN UINT8 Index,
  IN UINT8 Value
);

PCH_SERIES
EFIAPI
GetPchSeries (
  VOID
);

UINT8
EFIAPI
GetPchMaxPciePortNum (
  VOID
);

UINT8
EFIAPI
GetPchMaxSataPortNum (
  VOID
);

UINT8
EFIAPI
GetPchUsbMaxPhysicalPortNum (
  VOID
);

UINT8
EFIAPI
GetPchXhciMaxUsb3PortNum (
  VOID
);

UINT8
EFIAPI
GetPchEhciMaxControllerNum (
  VOID
);

EFI_STATUS
SbLib_RunTimeResetCallback(
  IN     EFI_RESET_TYPE           ResetType
  );

#if SB_RESET_PPI_SUPPORT
VOID SBLib_ResetSystem (
    IN EFI_RESET_TYPE  ResetType
);
#endif

VOID SBLib_ExtResetSystem (
    IN SB_EXT_RESET_TYPE    ResetType
);

#if SB_STALL_PPI_SUPPORT
EFI_STATUS CountTime (
    IN  UINTN           DelayTime,
    IN  UINT16          BaseAddr // only needs to be 16 bit for I/O address
);
#endif

#if SMM_SUPPORT
EFI_STATUS SBSmmSaveRestoreStates (
    IN BOOLEAN                      Save
);
#endif

//---------------------------------------------------------------------------
//  CMOS Manager Support
//
//  Southbridge should implement functions to support access to additional 
//  CMOS banks that exist beyond the first 128 bytes.
//---------------------------------------------------------------------------

#if CMOS_MANAGER_SUPPORT
#include <CmosAccess.h>

EFI_STATUS ReadWriteCmosBank2 (
    IN EFI_PEI_SERVICES             **PeiServices,  // NULL in DXE phase
    IN CMOS_ACCESS_TYPE             AccessType,
    IN UINT16                       CmosRegister,
    IN OUT UINT8                    *CmosParameterValue
);

BOOLEAN SbGetRtcPowerStatus (
    IN EFI_PEI_SERVICES             **PeiServices  // NULL in DXE phase
);

#endif  // #if CMOS_MANAGER_SUPPORT

//---------------------------------------------------------------------------

//UINT8   ReadCmos (IN UINT8 Index);
//VOID    WriteCmos (IN UINT8 Index, IN UINT8 Value);
BOOLEAN SbLib_GetSmiState (VOID);
VOID    SbLib_SmiDisable (VOID);
VOID    SbLib_SmiEnable (VOID);
VOID    CspLibCheckPowerLoss (VOID);

//---------------------------------------------------------------------------

VOID ChipsetFlashDeviceWriteEnable (VOID);
VOID ChipsetFlashDeviceWriteDisable (VOID);

//---------------------------------------------------------------------------

EFI_STATUS SbLib_SetLpcDeviceDecoding (
    IN EFI_PCI_IO_PROTOCOL      *LpcPciIo,
    IN UINT16                   Base,
    IN UINT8                    DevUid,
    IN SIO_DEV_TYPE             Type
);

EFI_STATUS SbLib_SetLpcGenericDecoding (
    IN EFI_PCI_IO_PROTOCOL      *LpcPciIo,
    IN UINT16                   Base,
    IN UINT16                   Length,
    IN BOOLEAN                  Enable
);

//---------------------------------------------------------------------------
UINT8 RtcRead (
    IN UINT8 Location
);

UINT8 ReadIo8IdxData (
    IN UINT16       IoBase16,
    IN UINT8        RegIdx8
);

VOID WriteIo8IdxData (
    IN UINT16       IoBase16,
    IN UINT8        RegIdx8,
    IN UINT8        WriteValue8
);

VOID RwIo8IdxData (
    IN UINT16       IoBase16,
    IN UINT8        RegIdx8,
    IN UINT8        SetBit8,
    IN UINT8        ResetBit8
);

VOID BiosLockEnableSMIFlashHook (
    IN UINT8            SwSmiNum,
    IN OUT UINT64       Buffer
);

VOID SwitchAlternateAccessMode				//Improve alternate access mode >>
(
  BOOLEAN Switch
);

UINT8 ReadPort70h ( VOID );					//Improve alternate access mode <<
//---------------------------------------------------------------------------
// Standard I/O Macros, No Porting Required.
//---------------------------------------------------------------------------
#define ReadIo8(IoAddr)           IoRead8(IoAddr)
#define READ_IO8(IoAddr)          IoRead8(IoAddr)
#define WriteIo8(IoAddr, bVal)    IoWrite8(IoAddr, bVal)
#define WRITE_IO8(IoAddr, bVal)   IoWrite8(IoAddr, bVal)
#define SET_IO8(IoAddr, bSet)     IoWrite8(IoAddr, IoRead8(IoAddr) | (bSet))
#define RESET_IO8(IoAddr, bRst)   IoWrite8(IoAddr, IoRead8(IoAddr) & ~(bRst))
#define RW_IO8(Bx, Set, Rst)      IoWrite8(Bx, IoRead8(Bx) & ~(Rst) | (Set))
#define ReadIo16(IoAddr)          IoRead16(IoAddr)
#define READ_IO16(IoAddr)         IoRead16(IoAddr)
#define WriteIo16(IoAddr, wVal)   IoWrite16(IoAddr, wVal)
#define WRITE_IO16(IoAddr, wVal)  IoWrite16(IoAddr, wVal)
#define SET_IO16(IoAddr, wSet)    IoWrite16(IoAddr, IoRead16(IoAddr) | (wSet))
#define RESET_IO16(IoAddr, Rst)   IoWrite16(IoAddr, IoRead16(IoAddr) & ~(Rst))
#define RW_IO16(Bx, Set, Rst)     IoWrite16(Bx, IoRead16(Bx) & ~(Rst) | (Set))
#define ReadIo32(IoAddr)          IoRead32(IoAddr)
#define READ_IO32(IoAddr)         IoRead32(IoAddr)
#define WriteIo32(IoAddr, dVal)   IoWrite32(IoAddr, dVal)
#define WRITE_IO32(IoAddr, dVal)  IoWrite32(IoAddr, dVal)
#define SET_IO32(IoAddr, dSet)    IoWrite32(IoAddr, IoRead32(IoAddr) | (dSet))
#define RESET_IO32(IoAddr, Rst)   IoWrite32(IoAddr, IoRead32(IoAddr) & ~(Rst))
#define RW_IO32(Bx, Set, Rst)     IoWrite32(Bx, IoRead32(Bx) & ~(Rst) | (Set))

#define WRITE_IO8_S3(mBtScSv, IoAddr16, bValue) \
                                    WriteIo8S3(mBtScSv, IoAddr16, bValue)
#define SET_IO8_S3(mBtScSv, IoAddr16, bSet) \
                                    RwIo8S3(mBtScSv, IoAddr16, bSet, 0)
#define RESET_IO8_S3(mBtScSv, IoAddr16, bReset) \
                                    RwIo8S3(mBtScSv, IoAddr16, 0, bReset) 
#define RW_IO8_S3(mBtScSv, IoAddr16, bSet, bReset) \
                                    RwIo8S3(mBtScSv, IoAddr16, bSet, bReset)
#define WRITE_IO16_S3(mBtScSv, IoAddr16, wValue) \
                                    WriteIo16S3(mBtScSv, IoAddr16, wValue)
#define SET_IO16_S3(mBtScSv, IoAddr16, wSet) \
                                    RwIo16S3(mBtScSv, IoAddr16, wSet, 0)
#define RESET_IO16_S3(mBtScSv, IoAddr16, wReset) \
                                    RwIo16S3(mBtScSv, IoAddr16, 0, wReset) 
#define RW_IO16_S3(mBtScSv, IoAddr16, wSet, wReset) \
                                    RwIo16S3(mBtScSv, IoAddr16, wSet, wReset)
#define WRITE_IO32_S3(mBtScSv, IoAddr16, dValue) \
                                    WriteIo32S3(mBtScSv, IoAddr16, dValue)
#define SET_IO32_S3(mBtScSv, IoAddr16, dSet) \
                                    RwIo32S3(mBtScSv, IoAddr16, dSet, 0)
#define RESET_IO32_S3(mBtScSv, IoAddr16, dReset) \
                                    RwIo32S3(mBtScSv, IoAddr16, 0, dReset) 
#define RW_IO32_S3(mBtScSv, IoAddr16, dSet, dReset) \
                                    RwIo32S3(mBtScSv, IoAddr16, dSet, dReset)

//---------------------------------------------------------------------------
// Chipset PCI Macros, Porting Required.
//---------------------------------------------------------------------------

#define READ_PCI8_SB(Rx)          READ_PCI8(SB_BUS, SB_DEV, SB_FUN, Rx)
#define WRITE_PCI8_SB(Rx, Val)    WRITE_PCI8(SB_BUS, SB_DEV, SB_FUN, Rx, Val)
#define SET_PCI8_SB(Rx, Set)      SET_PCI8(SB_BUS, SB_DEV, SB_FUN, Rx, Set)
#define RESET_PCI8_SB(Rx, Rst)    RESET_PCI8(SB_BUS, SB_DEV, SB_FUN, Rx, Rst)
#define RW_PCI8_SB(Rx, St, Rt)    RW_PCI8(SB_BUS, SB_DEV, SB_FUN, Rx, St, Rt)
#define READ_PCI16_SB(Rx)         READ_PCI16(SB_BUS, SB_DEV, SB_FUN, Rx)
#define WRITE_PCI16_SB(Rx, Val)   WRITE_PCI16(SB_BUS, SB_DEV, SB_FUN, Rx, Val)
#define SET_PCI16_SB(Rx, Set)     SET_PCI16(SB_BUS, SB_DEV, SB_FUN, Rx, Set)
#define RESET_PCI16_SB(Rx, Rst)   RESET_PCI16(SB_BUS, SB_DEV, SB_FUN, Rx, Rst)
#define RW_PCI16_SB(Rx, St, Rt)   RW_PCI16(SB_BUS, SB_DEV, SB_FUN, Rx, St, Rt)
#define READ_PCI32_SB(Rx)         READ_PCI32(SB_BUS, SB_DEV, SB_FUN, Rx)
#define WRITE_PCI32_SB(Rx, Val)   WRITE_PCI32(SB_BUS, SB_DEV, SB_FUN, Rx, Val)
#define SET_PCI32_SB(Rx, Set)     SET_PCI32(SB_BUS, SB_DEV, SB_FUN, Rx, Set)
#define RESET_PCI32_SB(Rx, Rst)   RESET_PCI32(SB_BUS, SB_DEV, SB_FUN, Rx, Rst)
#define RW_PCI32_SB(Rx, St, Rt)   RW_PCI32(SB_BUS, SB_DEV, SB_FUN, Rx, St, Rt)

//---------------------------------------------------------------------------

#define READ_PCI8_SATA(Rx) \
                         READ_PCI8(SATA_BUS, SATA_DEV, SATA_FUN, Rx)
#define WRITE_PCI8_SATA(Rx, Val) \
                         WRITE_PCI8(SATA_BUS, SATA_DEV, SATA_FUN, Rx, Val)
#define SET_PCI8_SATA(Rx, Set) \
                         SET_PCI8(SATA_BUS, SATA_DEV, SATA_FUN, Rx, Set)
#define RESET_PCI8_SATA(Rx, Rst) \
                         RESET_PCI8(SATA_BUS, SATA_DEV, SATA_FUN, Rx, Rst)
#define RW_PCI8_SATA(Rx, Set, Rst) \
                         RW_PCI8(SATA_BUS, SATA_DEV, SATA_FUN, Rx, Set, Rst)
#define READ_PCI16_SATA(Rx) \
                         READ_PCI16(SATA_BUS, SATA_DEV, SATA_FUN, Rx)
#define WRITE_PCI16_SATA(Rx, Val) \
                         WRITE_PCI16(SATA_BUS, SATA_DEV, SATA_FUN, Rx, Val)
#define SET_PCI16_SATA(Rx, Set) \
                         SET_PCI16(SATA_BUS, SATA_DEV, SATA_FUN, Rx, Set)
#define RESET_PCI16_SATA(Rx, Rst) \
                         RESET_PCI16(SATA_BUS, SATA_DEV, SATA_FUN, Rx, Rst)
#define RW_PCI16_SATA(Rx, Set, Rst) \
                         RW_PCI16(SATA_BUS, SATA_DEV, SATA_FUN, Rx, Set, Rst)
#define READ_PCI32_SATA(Rx) \
                         READ_PCI32(SATA_BUS, SATA_DEV, SATA_FUN, Rx)
#define WRITE_PCI32_SATA(Rx, Val) \
                         WRITE_PCI32(SATA_BUS, SATA_DEV, SATA_FUN, Rx, Val)
#define SET_PCI32_SATA(Rx, Set) \
                         SET_PCI32(SATA_BUS, SATA_DEV, SATA_FUN, Rx, Set)
#define RESET_PCI32_SATA(Rx, Rst) \
                         RESET_PCI32(SATA_BUS, SATA_DEV, SATA_FUN, Rx, Rst)
#define RW_PCI32_SATA(Rx, Set, Rst) \
                         RW_PCI32(SATA_BUS, SATA_DEV, SATA_FUN, Rx, Set, Rst)

//---------------------------------------------------------------------------

#define READ_PCI8_SATA2(Rx) \
                         READ_PCI8(SATA2_BUS, SATA2_DEV, SATA2_FUN, Rx)
#define WRITE_PCI8_SATA2(Rx, Val) \
                         WRITE_PCI8(SATA2_BUS, SATA2_DEV, SATA2_FUN, Rx, Val)
#define SET_PCI8_SATA2(Rx, Set) \
                         SET_PCI8(SATA2_BUS, SATA2_DEV, SATA2_FUN, Rx, Set)
#define RESET_PCI8_SATA2(Rx, Rst) \
                         RESET_PCI8(SATA2_BUS, SATA2_DEV, SATA2_FUN, Rx, Rst)
#define RW_PCI8_SATA2(Rx, Set, Rst) \
                         RW_PCI8(SATA2_BUS, SATA2_DEV, SATA2_FUN, Rx, Set, Rst)
#define READ_PCI16_SATA2(Rx) \
                         READ_PCI16(SATA2_BUS, SATA2_DEV, SATA2_FUN, Rx)
#define WRITE_PCI16_SATA2(Rx, Val) \
                         WRITE_PCI16(SATA2_BUS, SATA2_DEV, SATA2_FUN, Rx, Val)
#define SET_PCI16_SATA2(Rx, Set) \
                         SET_PCI16(SATA2_BUS, SATA2_DEV, SATA2_FUN, Rx, Set)
#define RESET_PCI16_SATA2(Rx, Rst) \
                         RESET_PCI16(SATA2_BUS, SATA2_DEV, SATA2_FUN, Rx, Rst)
#define RW_PCI16_SATA2(Rx, Set, Rst) \
                         RW_PCI16(SATA2_BUS, SATA2_DEV, SATA2_FUN, Rx, Set, Rst)
#define READ_PCI32_SATA2(Rx) \
                         READ_PCI32(SATA2_BUS, SATA2_DEV, SATA2_FUN, Rx)
#define WRITE_PCI32_SATA2(Rx, Val) \
                         WRITE_PCI32(SATA2_BUS, SATA2_DEV, SATA2_FUN, Rx, Val)
#define SET_PCI32_SATA2(Rx, Set) \
                         SET_PCI32(SATA2_BUS, SATA2_DEV, SATA2_FUN, Rx, Set)
#define RESET_PCI32_SATA2(Rx, Rst) \
                         RESET_PCI32(SATA2_BUS, SATA2_DEV, SATA2_FUN, Rx, Rst)
#define RW_PCI32_SATA2(Rx, Set, Rst) \
                         RW_PCI32(SATA2_BUS, SATA2_DEV, SATA2_FUN, Rx, Set, Rst)

//---------------------------------------------------------------------------

#define READ_PCI8_PCIEBRS(Rx) \
                 READ_PCI8(PCIEBRS_BUS, PCIEBRS_DEV, PCIEBRS_FUN, Rx)
#define WRITE_PCI8_PCIEBRS(Rx, Val) \
                 WRITE_PCI8(PCIEBRS_BUS, PCIEBRS_DEV, PCIEBRS_FUN, Rx, Val)
#define SET_PCI8_PCIEBRS(Rx, Set) \
                 SET_PCI8(PCIEBRS_BUS, PCIEBRS_DEV, PCIEBRS_FUN, Rx, Set)
#define RESET_PCI8_PCIEBRS(Rx, Rst) \
                 RESET_PCI8(PCIEBRS_BUS, PCIEBRS_DEV, PCIEBRS_FUN, Rx, Rst)
#define RW_PCI8_PCIEBRS(Rx, Set, Rst) \
                 RW_PCI8(PCIEBRS_BUS, PCIEBRS_DEV, PCIEBRS_FUN, Rx, Set, Rst)
#define READ_PCI16_PCIEBRS(Rx) \
                 READ_PCI16(PCIEBRS_BUS, PCIEBRS_DEV, PCIEBRS_FUN, Rx)
#define WRITE_PCI16_PCIEBRS(Rx, Val) \
                 WRITE_PCI16(PCIEBRS_BUS, PCIEBRS_DEV, PCIEBRS_FUN, Rx, Val)
#define SET_PCI16_PCIEBRS(Rx, Set) \
                 SET_PCI16(PCIEBRS_BUS, PCIEBRS_DEV, PCIEBRS_FUN, Rx, Set)
#define RESET_PCI16_PCIEBRS(Rx, Rst) \
                 RESET_PCI16(PCIEBRS_BUS, PCIEBRS_DEV, PCIEBRS_FUN, Rx, Rst)
#define RW_PCI16_PCIEBRS(Rx, Set, Rst) \
                 RW_PCI16(PCIEBRS_BUS, PCIEBRS_DEV, PCIEBRS_FUN, Rx, Set, Rst)
#define READ_PCI32_PCIEBRS(Rx) \
                 READ_PCI32(PCIEBRS_BUS, PCIEBRS_DEV, PCIEBRS_FUN, Rx)
#define WRITE_PCI32_PCIEBRS(Rx, Val) \
                 WRITE_PCI32(PCIEBRS_BUS, PCIEBRS_DEV, PCIEBRS_FUN, Rx, Val)
#define SET_PCI32_PCIEBRS(Rx, Set) \
                 SET_PCI32(PCIEBRS_BUS, PCIEBRS_DEV, PCIEBRS_FUN, Rx, Set)
#define RESET_PCI32_PCIEBRS(Rx, Rst) \
                 RESET_PCI32(PCIEBRS_BUS, PCIEBRS_DEV, PCIEBRS_FUN, Rx, Rst)
#define RW_PCI32_PCIEBRS(Rx, Set, Rst) \
                 RW_PCI32(PCIEBRS_BUS, PCIEBRS_DEV, PCIEBRS_FUN, Rx, Set, Rst)

//---------------------------------------------------------------------------

#define READ_PCI8_PCIBR(Rx) \
                      READ_PCI8(PCIBR_BUS, PCIBR_DEV, PCIBR_FUN, Rx)
#define WRITE_PCI8_PCIBR(Rx, Val) \
                      WRITE_PCI8(PCIBR_BUS, PCIBR_DEV, PCIBR_FUN, Rx, Val)
#define SET_PCI8_PCIBR(Rx, Set) \
                      SET_PCI8(PCIBR_BUS, PCIBR_DEV, PCIBR_FUN, Rx, Set)
#define RESET_PCI8_PCIBR(Rx, Rst) \
                      RESET_PCI8(PCIBR_BUS, PCIBR_DEV, PCIBR_FUN, Rx, Rst)
#define RW_PCI8_PCIBR(Rx, Set, Rst) \
                      RW_PCI8(PCIBR_BUS, PCIBR_DEV, PCIBR_FUN, Rx, Set, Rst)
#define READ_PCI16_PCIBR(Rx) \
                      READ_PCI16(PCIBR_BUS, PCIBR_DEV, PCIBR_FUN, Rx)
#define WRITE_PCI16_PCIBR(Rx, Val) \
                      WRITE_PCI16(PCIBR_BUS, PCIBR_DEV, PCIBR_FUN, Rx, Val)
#define SET_PCI16_PCIBR(Rx, Set) \
                      SET_PCI16(PCIBR_BUS, PCIBR_DEV, PCIBR_FUN, Rx, Set)
#define RESET_PCI16_PCIBR(Rx, Rst) \
                      RESET_PCI16(PCIBR_BUS, PCIBR_DEV, PCIBR_FUN, Rx, Rst)
#define RW_PCI16_PCIBR(Rx, Set, Rst) \
                      RW_PCI16(PCIBR_BUS, PCIBR_DEV, PCIBR_FUN, Rx, Set, Rst)
#define READ_PCI32_PCIBR(Rx) \
                      READ_PCI32(PCIBR_BUS, PCIBR_DEV, PCIBR_FUN, Rx)
#define WRITE_PCI32_PCIBR(Rx, Val) \
                      WRITE_PCI32(PCIBR_BUS, PCIBR_DEV, PCIBR_FUN, Rx, Val)
#define SET_PCI32_PCIBR(Rx, Set) \
                      SET_PCI32(PCIBR_BUS, PCIBR_DEV, PCIBR_FUN, Rx, Set)
#define RESET_PCI32_PCIBR(Rx, Rst) \
                      RESET_PCI32(PCIBR_BUS, PCIBR_DEV, PCIBR_FUN, Rx, Rst)
#define RW_PCI32_PCIBR(Rx, Set, Rst) \
                      RW_PCI32(PCIBR_BUS, PCIBR_DEV, PCIBR_FUN, Rx, Set, Rst)

//---------------------------------------------------------------------------

#define READ_PCI8_EHCI(Rx)       READ_PCI8(EHCI_BUS, EHCI_DEV, EHCI_FUN, Rx)
#define WRITE_PCI8_EHCI(Rx, Vx)  WRITE_PCI8(EHCI_BUS, EHCI_DEV, EHCI_FUN, Rx, Vx)
#define SET_PCI8_EHCI(Rx, Set)   SET_PCI8(EHCI_BUS, EHCI_DEV, EHCI_FUN, Rx, Set)
#define RESET_PCI8_EHCI(Rx, Rt)  RESET_PCI8(EHCI_BUS, EHCI_DEV, EHCI_FUN, Rx, Rt)
#define RW_PCI8_EHCI(Rx,St,Rt)   RW_PCI8(EHCI_BUS, EHCI_DEV, EHCI_FUN, Rx, St, Rt)
#define READ_PCI16_EHCI(Rx)      READ_PCI16(EHCI_BUS, EHCI_DEV, EHCI_FUN, Rx)
#define WRITE_PCI16_EHCI(Rx, Vx) WRITE_PCI16(EHCI_BUS, EHCI_DEV, EHCI_FUN, Rx, Vx)
#define SET_PCI16_EHCI(Rx, Set)  SET_PCI16(EHCI_BUS, EHCI_DEV, EHCI_FUN, Rx, Set)
#define RESET_PCI16_EHCI(Rx, Rt) RESET_PCI16(EHCI_BUS, EHCI_DEV, EHCI_FUN, Rx, Rt)
#define RW_PCI16_EHCI(Rx,St,Rt)  RW_PCI16(EHCI_BUS, EHCI_DEV, EHCI_FUN, Rx, St,Rt)
#define READ_PCI32_EHCI(Rx)      READ_PCI32(EHCI_BUS, EHCI_DEV, EHCI_FUN, Rx)
#define WRITE_PCI32_EHCI(Rx, Vx) WRITE_PCI32(EHCI_BUS, EHCI_DEV, EHCI_FUN, Rx, Vx)
#define SET_PCI32_EHCI(Rx, Set)  SET_PCI32(EHCI_BUS, EHCI_DEV, EHCI_FUN, Rx, Set)
#define RESET_PCI32_EHCI(Rx, Rt) RESET_PCI32(EHCI_BUS, EHCI_DEV, EHCI_FUN, Rx, Rt)
#define RW_PCI32_EHCI(Rx,St,Rt)  RW_PCI32(EHCI_BUS, EHCI_DEV, EHCI_FUN, Rx, St,Rt)

//---------------------------------------------------------------------------

#define READ_PCI8_EHCI2(Rx) \
                         READ_PCI8(EHCI2_BUS, EHCI2_DEV, EHCI2_FUN, Rx)
#define WRITE_PCI8_EHCI2(Rx, Val) \
                         WRITE_PCI8(EHCI2_BUS, EHCI2_DEV, EHCI2_FUN, Rx, Val)
#define SET_PCI8_EHCI2(Rx, Set) \
                         SET_PCI8(EHCI2_BUS, EHCI2_DEV, EHCI2_FUN, Rx, Set)
#define RESET_PCI8_EHCI2(Rx, Rst) \
                         RESET_PCI8(EHCI2_BUS, EHCI2_DEV, EHCI2_FUN, Rx, Rst)
#define RW_PCI8_EHCI2(Rx, Set, Rst) \
                         RW_PCI8(EHCI2_BUS, EHCI2_DEV, EHCI2_FUN, Rx, Set, Rst)
#define READ_PCI16_EHCI2(Rx) \
                         READ_PCI16(EHCI2_BUS, EHCI2_DEV, EHCI2_FUN, Rx)
#define WRITE_PCI16_EHCI2(Rx, Val) \
                         WRITE_PCI16(EHCI2_BUS, EHCI2_DEV, EHCI2_FUN, Rx, Val)
#define SET_PCI16_EHCI2(Rx, Set) \
                         SET_PCI16(EHCI2_BUS, EHCI2_DEV, EHCI2_FUN, Rx, Set)
#define RESET_PCI16_EHCI2(Rx, Rst) \
                         RESET_PCI16(EHCI2_BUS, EHCI2_DEV, EHCI2_FUN, Rx, Rst)
#define RW_PCI16_EHCI2(Rx, Set, Rst) \
                         RW_PCI16(EHCI2_BUS, EHCI2_DEV, EHCI2_FUN, Rx, Set, Rst)
#define READ_PCI32_EHCI2(Rx) \
                         READ_PCI32(EHCI2_BUS, EHCI2_DEV, EHCI2_FUN, Rx)
#define WRITE_PCI32_EHCI2(Rx, Val) \
                         WRITE_PCI32(EHCI2_BUS, EHCI2_DEV, EHCI2_FUN, Rx, Val)
#define SET_PCI32_EHCI2(Rx, Set) \
                         SET_PCI32(EHCI2_BUS, EHCI2_DEV, EHCI2_FUN, Rx, Set)
#define RESET_PCI32_EHCI2(Rx, Rst) \
                         RESET_PCI32(EHCI2_BUS, EHCI2_DEV, EHCI2_FUN, Rx, Rst)
#define RW_PCI32_EHCI2(Rx, Set, Rst) \
                         RW_PCI32(EHCI2_BUS, EHCI2_DEV, EHCI2_FUN, Rx, Set, Rst)

//---------------------------------------------------------------------------

#define READ_PCI8_LAN(Rx)       READ_PCI8(LAN_BUS, LAN_DEV, LAN_FUN, Rx)
#define WRITE_PCI8_LAN(Rx, Vx)  WRITE_PCI8(LAN_BUS, LAN_DEV, LAN_FUN, Rx, Vx)
#define SET_PCI8_LAN(Rx, Set)   SET_PCI8(LAN_BUS, LAN_DEV, LAN_FUN, Rx, Set)
#define RESET_PCI8_LAN(Rx, Rt)  RESET_PCI8(LAN_BUS, LAN_DEV, LAN_FUN, Rx, Rt)
#define RW_PCI8_LAN(Rx,St,Rt)   RW_PCI8(LAN_BUS, LAN_DEV, LAN_FUN, Rx, St, Rt)
#define READ_PCI16_LAN(Rx)      READ_PCI16(LAN_BUS, LAN_DEV, LAN_FUN, Rx)
#define WRITE_PCI16_LAN(Rx, Vx) WRITE_PCI16(LAN_BUS, LAN_DEV, LAN_FUN, Rx, Vx)
#define SET_PCI16_LAN(Rx, Set)  SET_PCI16(LAN_BUS, LAN_DEV, LAN_FUN, Rx, Set)
#define RESET_PCI16_LAN(Rx, Rt) RESET_PCI16(LAN_BUS, LAN_DEV, LAN_FUN, Rx, Rt)
#define RW_PCI16_LAN(Rx,St,Rt)  RW_PCI16(LAN_BUS, LAN_DEV, LAN_FUN, Rx, St,Rt)
#define READ_PCI32_LAN(Rx)      READ_PCI32(LAN_BUS, LAN_DEV, LAN_FUN, Rx)
#define WRITE_PCI32_LAN(Rx, Vx) WRITE_PCI32(LAN_BUS, LAN_DEV, LAN_FUN, Rx, Vx)
#define SET_PCI32_LAN(Rx, Set)  SET_PCI32(LAN_BUS, LAN_DEV, LAN_FUN, Rx, Set)
#define RESET_PCI32_LAN(Rx, Rt) RESET_PCI32(LAN_BUS, LAN_DEV, LAN_FUN, Rx, Rt)
#define RW_PCI32_LAN(Rx,St,Rt)  RW_PCI32(LAN_BUS, LAN_DEV, LAN_FUN, Rx, St,Rt)

//---------------------------------------------------------------------------

#define READ_PCI8_HDA(Rx)       READ_PCI8(HDA_BUS, HDA_DEV, HDA_FUN, Rx)
#define WRITE_PCI8_HDA(Rx, Vx)  WRITE_PCI8(HDA_BUS, HDA_DEV, HDA_FUN, Rx, Vx)
#define SET_PCI8_HDA(Rx, Set)   SET_PCI8(HDA_BUS, HDA_DEV, HDA_FUN, Rx, Set)
#define RESET_PCI8_HDA(Rx, Rt)  RESET_PCI8(HDA_BUS, HDA_DEV, HDA_FUN, Rx, Rt)
#define RW_PCI8_HDA(Rx,St,Rt)   RW_PCI8(HDA_BUS, HDA_DEV, HDA_FUN, Rx, St, Rt)
#define READ_PCI16_HDA(Rx)      READ_PCI16(HDA_BUS, HDA_DEV, HDA_FUN, Rx)
#define WRITE_PCI16_HDA(Rx, Vx) WRITE_PCI16(HDA_BUS, HDA_DEV, HDA_FUN, Rx, Vx)
#define SET_PCI16_HDA(Rx, Set)  SET_PCI16(HDA_BUS, HDA_DEV, HDA_FUN, Rx, Set)
#define RESET_PCI16_HDA(Rx, Rt) RESET_PCI16(HDA_BUS, HDA_DEV, HDA_FUN, Rx, Rt)
#define RW_PCI16_HDA(Rx,St,Rt)  RW_PCI16(HDA_BUS, HDA_DEV, HDA_FUN, Rx, St,Rt)
#define READ_PCI32_HDA(Rx)      READ_PCI32(HDA_BUS, HDA_DEV, HDA_FUN, Rx)
#define WRITE_PCI32_HDA(Rx, Vx) WRITE_PCI32(HDA_BUS, HDA_DEV, HDA_FUN, Rx, Vx)
#define SET_PCI32_HDA(Rx, Set)  SET_PCI32(HDA_BUS, HDA_DEV, HDA_FUN, Rx, Set)
#define RESET_PCI32_HDA(Rx, Rt) RESET_PCI32(HDA_BUS, HDA_DEV, HDA_FUN, Rx, Rt)
#define RW_PCI32_HDA(Rx,St,Rt)  RW_PCI32(HDA_BUS, HDA_DEV, HDA_FUN, Rx, St,Rt)

//---------------------------------------------------------------------------

#define READ_PCI8_SMBUS(Rx) \
                       READ_PCI8(SMBUS_BUS, SMBUS_DEV, SMBUS_FUN, Rx)
#define WRITE_PCI8_SMBUS(Rx, Val) \
                       WRITE_PCI8(SMBUS_BUS, SMBUS_DEV, SMBUS_FUN, Rx, Val)
#define SET_PCI8_SMBUS(Rx, Set) \
                       SET_PCI8(SMBUS_BUS, SMBUS_DEV, SMBUS_FUN, Rx, Set)
#define RESET_PCI8_SMBUS(Rx, Rst) \
                       RESET_PCI8(SMBUS_BUS, SMBUS_DEV, SMBUS_FUN, Rx, Rst)
#define RW_PCI8_SMBUS(Rx, Set, Rst) \
                       RW_PCI8(SMBUS_BUS, SMBUS_DEV, SMBUS_FUN, Rx, Set, Rst)
#define READ_PCI16_SMBUS(Rx) \
                       READ_PCI16(SMBUS_BUS, SMBUS_DEV, SMBUS_FUN, Rx)
#define WRITE_PCI16_SMBUS(Rx, Val) \
                       WRITE_PCI16(SMBUS_BUS, SMBUS_DEV, SMBUS_FUN, Rx, Val)
#define SET_PCI16_SMBUS(Rx, Set) \
                       SET_PCI16(SMBUS_BUS, SMBUS_DEV, SMBUS_FUN, Rx, Set)
#define RESET_PCI16_SMBUS(Rx, Rst) \
                       RESET_PCI16(SMBUS_BUS, SMBUS_DEV, SMBUS_FUN, Rx, Rst)
#define RW_PCI16_SMBUS(Rx, Set, Rst) \
                       RW_PCI16(SMBUS_BUS, SMBUS_DEV, SMBUS_FUN, Rx, Set, Rst)
#define READ_PCI32_SMBUS(Rx) \
                       READ_PCI32(SMBUS_BUS, SMBUS_DEV, SMBUS_FUN, Rx)
#define WRITE_PCI32_SMBUS(Rx, Val) \
                       WRITE_PCI32(SMBUS_BUS, SMBUS_DEV, SMBUS_FUN, Rx, Val)
#define SET_PCI32_SMBUS(Rx, Set) \
                       SET_PCI32(SMBUS_BUS, SMBUS_DEV, SMBUS_FUN, Rx, Set)
#define RESET_PCI32_SMBUS(Rx, Rst) \
                       RESET_PCI32(SMBUS_BUS, SMBUS_DEV, SMBUS_FUN, Rx, Rst)
#define RW_PCI32_SMBUS(Rx, Set, Rst) \
                       RW_PCI32(SMBUS_BUS, SMBUS_DEV, SMBUS_FUN, Rx, Set, Rst)

//---------------------------------------------------------------------------

#define READ_PCI8_HECI(Rx) \
                         READ_PCI8(HECI_BUS, HECI_DEV, HECI_FUN, Rx)
#define WRITE_PCI8_HECI(Rx, Val) \
                         WRITE_PCI8(HECI_BUS, HECI_DEV, HECI_FUN, Rx, Val)
#define SET_PCI8_HECI(Rx, Set) \
                         SET_PCI8(HECI_BUS, HECI_DEV, HECI_FUN, Rx, Set)
#define RESET_PCI8_HECI(Rx, Rst) \
                         RESET_PCI8(HECI_BUS, HECI_DEV, HECI_FUN, Rx, Rst)
#define RW_PCI8_HECI(Rx, Set, Rst) \
                         RW_PCI8(HECI_BUS, HECI_DEV, HECI_FUN, Rx, Set, Rst)
#define READ_PCI16_HECI(Rx) \
                         READ_PCI16(HECI_BUS, HECI_DEV, HECI_FUN, Rx)
#define WRITE_PCI16_HECI(Rx, Val) \
                         WRITE_PCI16(HECI_BUS, HECI_DEV, HECI_FUN, Rx, Val)
#define SET_PCI16_HECI(Rx, Set) \
                         SET_PCI16(HECI_BUS, HECI_DEV, HECI_FUN, Rx, Set)
#define RESET_PCI16_HECI(Rx, Rst) \
                         RESET_PCI16(HECI_BUS, HECI_DEV, HECI_FUN, Rx, Rst)
#define RW_PCI16_HECI(Rx, Set, Rst) \
                         RW_PCI16(HECI_BUS, HECI_DEV, HECI_FUN, Rx, Set, Rst)
#define READ_PCI32_HECI(Rx) \
                         READ_PCI32(HECI_BUS, HECI_DEV, HECI_FUN, Rx)
#define WRITE_PCI32_HECI(Rx, Val) \
                         WRITE_PCI32(HECI_BUS, HECI_DEV, HECI_FUN, Rx, Val)
#define SET_PCI32_HECI(Rx, Set) \
                         SET_PCI32(HECI_BUS, HECI_DEV, HECI_FUN, Rx, Set)
#define RESET_PCI32_HECI(Rx, Rst) \
                         RESET_PCI32(HECI_BUS, HECI_DEV, HECI_FUN, Rx, Rst)
#define RW_PCI32_HECI(Rx, Set, Rst) \
                         RW_PCI32(HECI_BUS, HECI_DEV, HECI_FUN, Rx, Set, Rst)

//---------------------------------------------------------------------------

#define READ_PCI8_HECI2(Rx) \
                         READ_PCI8(HECI2_BUS, HECI2_DEV, HECI2_FUN, Rx)
#define WRITE_PCI8_HECI2(Rx, Val) \
                         WRITE_PCI8(HECI2_BUS, HECI2_DEV, HECI2_FUN, Rx, Val)
#define SET_PCI8_HECI2(Rx, Set) \
                         SET_PCI8(HECI2_BUS, HECI2_DEV, HECI2_FUN, Rx, Set)
#define RESET_PCI8_HECI2(Rx, Rst) \
                         RESET_PCI8(HECI2_BUS, HECI2_DEV, HECI2_FUN, Rx, Rst)
#define RW_PCI8_HECI2(Rx, Set, Rst) \
                         RW_PCI8(HECI2_BUS, HECI2_DEV, HECI2_FUN, Rx, Set, Rst)
#define READ_PCI16_HECI2(Rx) \
                         READ_PCI16(HECI2_BUS, HECI2_DEV, HECI2_FUN, Rx)
#define WRITE_PCI16_HECI2(Rx, Val) \
                         WRITE_PCI16(HECI2_BUS, HECI2_DEV, HECI2_FUN, Rx, Val)
#define SET_PCI16_HECI2(Rx, Set) \
                         SET_PCI16(HECI2_BUS, HECI2_DEV, HECI2_FUN, Rx, Set)
#define RESET_PCI16_HECI2(Rx, Rst) \
                         RESET_PCI16(HECI2_BUS, HECI2_DEV, HECI2_FUN, Rx, Rst)
#define RW_PCI16_HECI2(Rx, Set, Rst) \
                         RW_PCI16(HECI2_BUS, HECI2_DEV, HECI2_FUN, Rx, Set, Rst)
#define READ_PCI32_HECI2(Rx) \
                         READ_PCI32(HECI2_BUS, HECI2_DEV, HECI2_FUN, Rx)
#define WRITE_PCI32_HECI2(Rx, Val) \
                         WRITE_PCI32(HECI2_BUS, HECI2_DEV, HECI2_FUN, Rx, Val)
#define SET_PCI32_HECI2(Rx, Set) \
                         SET_PCI32(HECI2_BUS, HECI2_DEV, HECI2_FUN, Rx, Set)
#define RESET_PCI32_HECI2(Rx, Rst) \
                         RESET_PCI32(HECI2_BUS, HECI2_DEV, HECI2_FUN, Rx, Rst)
#define RW_PCI32_HECI2(Rx, Set, Rst) \
                         RW_PCI32(HECI2_BUS, HECI2_DEV, HECI2_FUN, Rx, Set, Rst)

//---------------------------------------------------------------------------

#define WRITE_PCI8_SB_S3(mBoot, Rx, Val) \
                     WRITE_PCI8_S3(mBoot, SB_BUS, SB_DEV, SB_FUN, Rx, Val)
#define SET_PCI8_SB_S3(mBoot, Rx, Set) \
                     SET_PCI8_S3(mBoot, SB_BUS, SB_DEV, SB_FUN, Rx, Set)
#define RESET_PCI8_SB_S3(mBoot, Rx, Reset) \
                     RESET_PCI8_S3(mBoot, SB_BUS, SB_DEV, SB_FUN, Rx, Reset)
#define RW_PCI8_SB_S3(mBoot, Rx, Set, Rst) \
                     RW_PCI8_S3(mBoot, SB_BUS, SB_DEV, SB_FUN, Rx, Set, Rst)
#define WRITE_PCI16_SB_S3(mBoot, Rx, Val) \
                     WRITE_PCI16_S3(mBoot, SB_BUS, SB_DEV, SB_FUN, Rx, Val)
#define SET_PCI16_SB_S3(mBoot, Rx, Set) \
                     SET_PCI16_S3(mBoot, SB_BUS, SB_DEV, SB_FUN, Rx, Set)
#define RESET_PCI16_SB_S3(mBoot, Rx, Reset) \
                     RESET_PCI16_S3(mBoot, SB_BUS, SB_DEV, SB_FUN, Rx, Reset)
#define RW_PCI16_SB_S3(mBoot, Rx, Set, Rst) \
                     RW_PCI16_S3(mBoot, SB_BUS, SB_DEV, SB_FUN, Rx, Set, Rst)
#define WRITE_PCI32_SB_S3(mBoot, Rx, Val) \
                     WRITE_PCI32_S3(mBoot, SB_BUS, SB_DEV, SB_FUN, Rx, Val)
#define SET_PCI32_SB_S3(mBoot, Rx, Set) \
                     SET_PCI32_S3(mBoot, SB_BUS, SB_DEV, SB_FUN, Rx, Set)
#define RESET_PCI32_SB_S3(mBoot, Rx, Reset) \
                     RESET_PCI32_S3(mBoot, SB_BUS, SB_DEV, SB_FUN, Rx, Reset)
#define RW_PCI32_SB_S3(mBoot, Rx, Set, Rst) \
                     RW_PCI32_S3(mBoot, SB_BUS, SB_DEV, SB_FUN, Rx, Set, Rst)

//---------------------------------------------------------------------------

#define WRITE_PCI8_SATA_S3(mBoot, Rx, Val) \
                WRITE_PCI8_S3(mBoot, SATA_BUS, SATA_DEV, SATA_FUN, Rx, Val)
#define SET_PCI8_SATA_S3(mBoot, Rx, Set) \
                SET_PCI8_S3(mBoot, SATA_BUS, SATA_DEV, SATA_FUN, Rx, Set)
#define RESET_PCI8_SATA_S3(mBoot, Rx, Rst) \
                RESET_PCI8_S3(mBoot, SATA_BUS, SATA_DEV, SATA_FUN, Rx, Rst)
#define RW_PCI8_SATA_S3(mBoot, Rx, Set, Rst) \
                RW_PCI8_S3(mBoot, SATA_BUS, SATA_DEV, SATA_FUN, Rx, Set, Rst)
#define WRITE_PCI16_SATA_S3(mBoot, Rx, Val) \
                WRITE_PCI16_S3(mBoot, SATA_BUS, SATA_DEV, SATA_FUN, Rx, Val)
#define SET_PCI16_SATA_S3(mBoot, Rx, Set) \
                SET_PCI16_S3(mBoot, SATA_BUS, SATA_DEV, SATA_FUN, Rx, Set)
#define RESET_PCI16_SATA_S3(mBoot, Rx, Rst) \
                RESET_PCI16_S3(mBoot, SATA_BUS, SATA_DEV, SATA_FUN, Rx, Rst)
#define RW_PCI16_SATA_S3(mBoot, Rx, Set, Rst) \
                RW_PCI16_S3(mBoot, SATA_BUS, SATA_DEV, SATA_FUN, Rx, Set, Rst)
#define WRITE_PCI32_SATA_S3(mBoot, Rx, Val) \
                WRITE_PCI32_S3(mBoot, SATA_BUS, SATA_DEV, SATA_FUN, Rx, Val)
#define SET_PCI32_SATA_S3(mBoot, Rx, Set) \
                SET_PCI32_S3(mBoot, SATA_BUS, SATA_DEV, SATA_FUN, Rx, Set)
#define RESET_PCI32_SATA_S3(mBoot, Rx, Rst) \
                RESET_PCI32_S3(mBoot, SATA_BUS, SATA_DEV, SATA_FUN, Rx, Rst)
#define RW_PCI32_SATA_S3(mBoot, Rx, Set, Rst) \
                RW_PCI32_S3(mBoot, SATA_BUS, SATA_DEV, SATA_FUN, Rx, Set, Rst)

//---------------------------------------------------------------------------

#define WRITE_PCI8_SATA2_S3(mBoot, Rx, Val) \
                WRITE_PCI8_S3(mBoot, SATA2_BUS, SATA2_DEV, SATA2_FUN, Rx, Val)
#define SET_PCI8_SATA2_S3(mBoot, Rx, Set) \
                SET_PCI8_S3(mBoot, SATA2_BUS, SATA2_DEV, SATA2_FUN, Rx, Set)
#define RESET_PCI8_SATA2_S3(mBoot, Rx, Rst) \
                RESET_PCI8_S3(mBoot, SATA2_BUS, SATA2_DEV, SATA2_FUN, Rx, Rst)
#define RW_PCI8_SATA2_S3(mBoot, Rx, Set, Rst) \
                RW_PCI8_S3(mBoot, SATA2_BUS, SATA2_DEV, SATA2_FUN, Rx, Set, Rst)
#define WRITE_PCI16_SATA2_S3(mBoot, Rx, Val) \
                WRITE_PCI16_S3(mBoot, SATA2_BUS, SATA2_DEV, SATA2_FUN, Rx, Val)
#define SET_PCI16_SATA2_S3(mBoot, Rx, Set) \
                SET_PCI16_S3(mBoot, SATA2_BUS, SATA2_DEV, SATA2_FUN, Rx, Set)
#define RESET_PCI16_SATA2_S3(mBoot, Rx, Rst) \
                RESET_PCI16_S3(mBoot, SATA2_BUS, SATA2_DEV, SATA2_FUN, Rx, Rst)
#define RW_PCI16_SATA2_S3(mBoot, Rx, Set, Rst) \
                RW_PCI16_S3(mBoot, SATA2_BUS, SATA2_DEV, SATA2_FUN, Rx, Set, Rst)
#define WRITE_PCI32_SATA2_S3(mBoot, Rx, Val) \
                WRITE_PCI32_S3(mBoot, SATA2_BUS, SATA2_DEV, SATA2_FUN, Rx, Val)
#define SET_PCI32_SATA2_S3(mBoot, Rx, Set) \
                SET_PCI32_S3(mBoot, SATA2_BUS, SATA2_DEV, SATA2_FUN, Rx, Set)
#define RESET_PCI32_SATA2_S3(mBoot, Rx, Rst) \
                RESET_PCI32_S3(mBoot, SATA2_BUS, SATA2_DEV, SATA2_FUN, Rx, Rst)
#define RW_PCI32_SATA2_S3(mBoot, Rx, Set, Rst) \
                RW_PCI32_S3(mBoot, SATA2_BUS, SATA2_DEV, SATA2_FUN, Rx, Set, Rst)

//---------------------------------------------------------------------------

#define WRITE_PCI8_PCIEBRS_S3(mBoot, Rx, Val) \
         WRITE_PCI8_S3(mBoot, PCIEBRS_BUS, PCIEBRS_DEV, PCIEBRS_FUN, Rx, Val)
#define SET_PCI8_PCIEBRS_S3(mBoot, Rx, Set) \
         SET_PCI8_S3(mBoot, PCIEBRS_BUS, PCIEBRS_DEV, PCIEBRS_FUN, Rx, Set)
#define RESET_PCI8_PCIEBRS_S3(mBoot, Rx, Rst) \
         RESET_PCI8_S3(mBoot, PCIEBRS_BUS, PCIEBRS_DEV, PCIEBRS_FUN, Rx, Rst)
#define RW_PCI8_PCIEBRS_S3(mBoot, Rx, St, Rt) \
         RW_PCI8_S3(mBoot, PCIEBRS_BUS, PCIEBRS_DEV, PCIEBRS_FUN, Rx, St, Rt)
#define WRITE_PCI16_PCIEBRS_S3(mBoot, Rx, Val) \
         WRITE_PCI16_S3(mBoot, PCIEBRS_BUS, PCIEBRS_DEV, PCIEBRS_FUN, Rx, Val)
#define SET_PCI16_PCIEBRS_S3(mBoot, Rx, Set) \
         SET_PCI16_S3(mBoot, PCIEBRS_BUS, PCIEBRS_DEV, PCIEBRS_FUN, Rx, Set)
#define RESET_PCI16_PCIEBRS_S3(mBoot, Rx, Rst) \
         RESET_PCI16_S3(mBoot, PCIEBRS_BUS, PCIEBRS_DEV, PCIEBRS_FUN, Rx, Rst)
#define RW_PCI16_PCIEBRS_S3(mBoot, Rx, St, Rt) \
         RW_PCI16_S3(mBoot, PCIEBRS_BUS, PCIEBRS_DEV, PCIEBRS_FUN, Rx, St, Rt)
#define WRITE_PCI32_PCIEBRS_S3(mBoot, Rx, Val) \
         WRITE_PCI32_S3(mBoot, PCIEBRS_BUS, PCIEBRS_DEV, PCIEBRS_FUN, Rx, Val)
#define SET_PCI32_PCIEBRS_S3(mBoot, Rx, Set) \
         SET_PCI32_S3(mBoot, PCIEBRS_BUS, PCIEBRS_DEV, PCIEBRS_FUN, Rx, Set)
#define RESET_PCI32_PCIEBRS_S3(mBoot, Rx, Rst) \
         RESET_PCI32_S3(mBoot, PCIEBRS_BUS, PCIEBRS_DEV, PCIEBRS_FUN, Rx, Rst)
#define RW_PCI32_PCIEBRS_S3(mBoot, Rx, St, Rt) \
         RW_PCI32_S3(mBoot, PCIEBRS_BUS, PCIEBRS_DEV, PCIEBRS_FUN, Rx, St, Rt)

//---------------------------------------------------------------------------

#define WRITE_PCI8_PCIBR_S3(mBoot, Rx, Val) \
               WRITE_PCI8_S3(mBoot, PCIBR_BUS, PCIBR_DEV, PCIBR_FUN, Rx, Val)
#define SET_PCI8_PCIBR_S3(mBoot, Rx, Set) \
               SET_PCI8_S3(mBoot, PCIBR_BUS, PCIBR_DEV, PCIBR_FUN, Rx, Set)
#define RESET_PCI8_PCIBR_S3(mBoot, Rx, Rst) \
               RESET_PCI8_S3(mBoot, PCIBR_BUS, PCIBR_DEV, PCIBR_FUN, Rx, Rst)
#define RW_PCI8_PCIBR_S3(mBoot, Rx, St, Rt) \
               RW_PCI8_S3(mBoot, PCIBR_BUS, PCIBR_DEV, PCIBR_FUN, Rx, St, Rt)
#define WRITE_PCI16_PCIBR_S3(mBoot, Rx, Val) \
               WRITE_PCI16_S3(mBoot, PCIBR_BUS, PCIBR_DEV, PCIBR_FUN, Rx, Val)
#define SET_PCI16_PCIBR_S3(mBoot, Rx, Set) \
               SET_PCI16_S3(mBoot, PCIBR_BUS, PCIBR_DEV, PCIBR_FUN, Rx, Set)
#define RESET_PCI16_PCIBR_S3(mBoot, Rx, Rst) \
               RESET_PCI16_S3(mBoot, PCIBR_BUS, PCIBR_DEV, PCIBR_FUN, Rx, Rst)
#define RW_PCI16_PCIBR_S3(mBoot, Rx, St, Rt) \
               RW_PCI16_S3(mBoot, PCIBR_BUS, PCIBR_DEV, PCIBR_FUN, Rx, St, Rt)
#define WRITE_PCI32_PCIBR_S3(mBoot, Rx, Val) \
               WRITE_PCI32_S3(mBoot, PCIBR_BUS, PCIBR_DEV, PCIBR_FUN, Rx, Val)
#define SET_PCI32_PCIBR_S3(mBoot, Rx, Set) \
               SET_PCI32_S3(mBoot, PCIBR_BUS, PCIBR_DEV, PCIBR_FUN, Rx, Set)
#define RESET_PCI32_PCIBR_S3(mBoot, Rx, Rst) \
               RESET_PCI32_S3(mBoot, PCIBR_BUS, PCIBR_DEV, PCIBR_FUN, Rx, Rst)
#define RW_PCI32_PCIBR_S3(mBoot, Rx, St, Rt) \
               RW_PCI32_S3(mBoot, PCIBR_BUS, PCIBR_DEV, PCIBR_FUN, Rx, St, Rt)

//---------------------------------------------------------------------------

#define WRITE_PCI8_EHCI_S3(mBoot, Rx, Val) \
                   WRITE_PCI8_S3(mBoot, EHCI_BUS, EHCI_DEV, EHCI_DEV, Rx, Val)
#define SET_PCI8_EHCI_S3(mBoot, Rx, Set) \
                   SET_PCI8_S3(mBoot, EHCI_BUS, EHCI_DEV, EHCI_DEV, Rx, Set)
#define RESET_PCI8_EHCI_S3(mBoot, Rx, Rst) \
                   RESET_PCI8_S3(mBoot, EHCI_BUS, EHCI_DEV, EHCI_DEV, Rx, Rst)
#define RW_PCI8_EHCI_S3(mBoot, Rx, Set, Rst) \
                   RW_PCI8_S3(mBoot, EHCI_BUS, EHCI_DEV, EHCI_DEV, Rx, Set, Rst)
#define WRITE_PCI16_EHCI_S3(mBoot, Rx, Val) \
                   WRITE_PCI16_S3(mBoot, EHCI_BUS, EHCI_DEV, EHCI_DEV, Rx, Val)
#define SET_PCI16_EHCI_S3(mBoot, Rx, Set) \
                   SET_PCI16_S3(mBoot, EHCI_BUS, EHCI_DEV, EHCI_DEV, Rx, Set)
#define RESET_PCI16_EHCI_S3(mBoot, Rx, Rst) \
                   RESET_PCI16_S3(mBoot, EHCI_BUS, EHCI_DEV, EHCI_DEV, Rx, Rst)
#define RW_PCI16_EHCI_S3(mBoot, Rx, Set, Rst) \
                   RW_PCI16_S3(mBoot, EHCI_BUS, EHCI_DEV, EHCI_DEV, Rx, Set, Rst)
#define WRITE_PCI32_EHCI_S3(mBoot, Rx, Val) \
                   WRITE_PCI32_S3(mBoot, EHCI_BUS, EHCI_DEV, EHCI_DEV, Rx, Val)
#define SET_PCI32_EHCI_S3(mBoot, Rx, Set) \
                   SET_PCI32_S3(mBoot, EHCI_BUS, EHCI_DEV, EHCI_DEV, Rx, Set)
#define RESET_PCI32_EHCI_S3(mBoot, Rx, Rst) \
                   RESET_PCI32_S3(mBoot, EHCI_BUS, EHCI_DEV, EHCI_DEV, Rx, Rst)
#define RW_PCI32_EHCI_S3(mBoot, Rx, Set, Rst) \
                   RW_PCI32_S3(mBoot, EHCI_BUS, EHCI_DEV, EHCI_DEV, Rx, Set, Rst)

//---------------------------------------------------------------------------

#define WRITE_PCI8_EHCI2_S3(mBoot, Rx, Val) \
                WRITE_PCI8_S3(mBoot, EHCI2_BUS, EHCI2_DEV, EHCI2_FUN, Rx, Val)
#define SET_PCI8_EHCI2_S3(mBoot, Rx, Set) \
                SET_PCI8_S3(mBoot, EHCI2_BUS, EHCI2_DEV, EHCI2_FUN, Rx, Set)
#define RESET_PCI8_EHCI2_S3(mBoot, Rx, Rst) \
                RESET_PCI8_S3(mBoot, EHCI2_BUS, EHCI2_DEV, EHCI2_FUN, Rx, Rst)
#define RW_PCI8_EHCI2_S3(mBoot, Rx, Set, Rst) \
                RW_PCI8_S3(mBoot, EHCI2_BUS, EHCI2_DEV, EHCI2_FUN, Rx, Set, Rst)
#define WRITE_PCI16_EHCI2_S3(mBoot, Rx, Val) \
                WRITE_PCI16_S3(mBoot, EHCI2_BUS, EHCI2_DEV, EHCI2_FUN, Rx, Val)
#define SET_PCI16_EHCI2_S3(mBoot, Rx, Set) \
                SET_PCI16_S3(mBoot, EHCI2_BUS, EHCI2_DEV, EHCI2_FUN, Rx, Set)
#define RESET_PCI16_EHCI2_S3(mBoot, Rx, Rst) \
                RESET_PCI16_S3(mBoot, EHCI2_BUS, EHCI2_DEV, EHCI2_FUN, Rx, Rst)
#define RW_PCI16_EHCI2_S3(mBoot, Rx, Set, Rst) \
                RW_PCI16_S3(mBoot, EHCI2_BUS, EHCI2_DEV, EHCI2_FUN, Rx, Set, Rst)
#define WRITE_PCI32_EHCI2_S3(mBoot, Rx, Val) \
                WRITE_PCI32_S3(mBoot, EHCI2_BUS, EHCI2_DEV, EHCI2_FUN, Rx, Val)
#define SET_PCI32_EHCI2_S3(mBoot, Rx, Set) \
                SET_PCI32_S3(mBoot, EHCI2_BUS, EHCI2_DEV, EHCI2_FUN, Rx, Set)
#define RESET_PCI32_EHCI2_S3(mBoot, Rx, Rst) \
                RESET_PCI32_S3(mBoot, EHCI2_BUS, EHCI2_DEV, EHCI2_FUN, Rx, Rst)
#define RW_PCI32_EHCI2_S3(mBoot, Rx, Set, Rst) \
                RW_PCI32_S3(mBoot, EHCI2_BUS, EHCI2_DEV, EHCI2_FUN, Rx, Set, Rst)

//---------------------------------------------------------------------------

#define WRITE_PCI8_LAN_S3(mBoot, Rx, Val) \
                   WRITE_PCI8_S3(mBoot, LAN_BUS, LAN_DEV, LAN_FUN, Rx, Val)
#define SET_PCI8_LAN_S3(mBoot, Rx, Set) \
                   SET_PCI8_S3(mBoot, LAN_BUS, LAN_DEV, LAN_FUN, Rx, Set)
#define RESET_PCI8_LAN_S3(mBoot, Rx, Rst) \
                   RESET_PCI8_S3(mBoot, LAN_BUS, LAN_DEV, LAN_FUN, Rx, Rst)
#define RW_PCI8_LAN_S3(mBoot, Rx, Set, Rst) \
                   RW_PCI8_S3(mBoot, LAN_BUS, LAN_DEV, LAN_FUN, Rx, Set, Rst)
#define WRITE_PCI16_LAN_S3(mBoot, Rx, Val) \
                   WRITE_PCI16_S3(mBoot, LAN_BUS, LAN_DEV, LAN_FUN, Rx, Val)
#define SET_PCI16_LAN_S3(mBoot, Rx, Set) \
                   SET_PCI16_S3(mBoot, LAN_BUS, LAN_DEV, LAN_FUN, Rx, Set)
#define RESET_PCI16_LAN_S3(mBoot, Rx, Rst) \
                   RESET_PCI16_S3(mBoot, LAN_BUS, LAN_DEV, LAN_FUN, Rx, Rst)
#define RW_PCI16_LAN_S3(mBoot, Rx, Set, Rst) \
                   RW_PCI16_S3(mBoot, LAN_BUS, LAN_DEV, LAN_FUN, Rx, Set, Rst)
#define WRITE_PCI32_LAN_S3(mBoot, Rx, Val) \
                   WRITE_PCI32_S3(mBoot, LAN_BUS, LAN_DEV, LAN_FUN, Rx, Val)
#define SET_PCI32_LAN_S3(mBoot, Rx, Set) \
                   SET_PCI32_S3(mBoot, LAN_BUS, LAN_DEV, LAN_FUN, Rx, Set)
#define RESET_PCI32_LAN_S3(mBoot, Rx, Rst) \
                   RESET_PCI32_S3(mBoot, LAN_BUS, LAN_DEV, LAN_FUN, Rx, Rst)
#define RW_PCI32_LAN_S3(mBoot, Rx, Set, Rst) \
                   RW_PCI32_S3(mBoot, LAN_BUS, LAN_DEV, LAN_FUN, Rx, Set, Rst)

//---------------------------------------------------------------------------

#define WRITE_PCI8_HDA_S3(mBoot, Rx, Val) \
                   WRITE_PCI8_S3(mBoot, HDA_BUS, HDA_DEV, HDA_FUN, Rx, Val)
#define SET_PCI8_HDA_S3(mBoot, Rx, Set) \
                   SET_PCI8_S3(mBoot, HDA_BUS, HDA_DEV, HDA_FUN, Rx, Set)
#define RESET_PCI8_HDA_S3(mBoot, Rx, Rst) \
                   RESET_PCI8_S3(mBoot, HDA_BUS, HDA_DEV, HDA_FUN, Rx, Rst)
#define RW_PCI8_HDA_S3(mBoot, Rx, Set, Rst) \
                   RW_PCI8_S3(mBoot, HDA_BUS, HDA_DEV, HDA_FUN, Rx, Set, Rst)
#define WRITE_PCI16_HDA_S3(mBoot, Rx, Val) \
                   WRITE_PCI16_S3(mBoot, HDA_BUS, HDA_DEV, HDA_FUN, Rx, Val)
#define SET_PCI16_HDA_S3(mBoot, Rx, Set) \
                   SET_PCI16_S3(mBoot, HDA_BUS, HDA_DEV, HDA_FUN, Rx, Set)
#define RESET_PCI16_HDA_S3(mBoot, Rx, Rst) \
                   RESET_PCI16_S3(mBoot, HDA_BUS, HDA_DEV, HDA_FUN, Rx, Rst)
#define RW_PCI16_HDA_S3(mBoot, Rx, Set, Rst) \
                   RW_PCI16_S3(mBoot, HDA_BUS, HDA_DEV, HDA_FUN, Rx, Set, Rst)
#define WRITE_PCI32_HDA_S3(mBoot, Rx, Val) \
                   WRITE_PCI32_S3(mBoot, HDA_BUS, HDA_DEV, HDA_FUN, Rx, Val)
#define SET_PCI32_HDA_S3(mBoot, Rx, Set) \
                   SET_PCI32_S3(mBoot, HDA_BUS, HDA_DEV, HDA_FUN, Rx, Set)
#define RESET_PCI32_HDA_S3(mBoot, Rx, Rst) \
                   RESET_PCI32_S3(mBoot, HDA_BUS, HDA_DEV, HDA_FUN, Rx, Rst)
#define RW_PCI32_HDA_S3(mBoot, Rx, Set, Rst) \
                   RW_PCI32_S3(mBoot, HDA_BUS, HDA_DEV, HDA_FUN, Rx, Set, Rst)

//---------------------------------------------------------------------------

#define WRITE_PCI8_SMBUS_S3(mBoot, Rx, Val) \
               WRITE_PCI8_S3(mBoot, SMBUS_BUS, SMBUS_DEV, SMBUS_FUN, Rx, Val)
#define SET_PCI8_SMBUS_S3(mBoot, Rx, Set) \
               SET_PCI8_S3(mBoot, SMBUS_BUS, SMBUS_DEV, SMBUS_FUN, Rx, Set)
#define RESET_PCI8_SMBUS_S3(mBoot, Rx, Rst) \
               RESET_PCI8_S3(mBoot, SMBUS_BUS, SMBUS_DEV, SMBUS_FUN, Rx, Rst)
#define RW_PCI8_SMBUS_S3(mBoot, Rx, St, Rt) \
               RW_PCI8_S3(mBoot, SMBUS_BUS, SMBUS_DEV, SMBUS_FUN, Rx, St, Rt)
#define WRITE_PCI16_SMBUS_S3(mBoot, Rx, Val) \
               WRITE_PCI16_S3(mBoot, SMBUS_BUS, SMBUS_DEV, SMBUS_FUN, Rx, Val)
#define SET_PCI16_SMBUS_S3(mBoot, Rx, Set) \
               SET_PCI16_S3(mBoot, SMBUS_BUS, SMBUS_DEV, SMBUS_FUN, Rx, Set)
#define RESET_PCI16_SMBUS_S3(mBoot, Rx, Rst) \
               RESET_PCI16_S3(mBoot, SMBUS_BUS, SMBUS_DEV, SMBUS_FUN, Rx, Rst)
#define RW_PCI16_SMBUS_S3(mBoot, Rx, St, Rt) \
               RW_PCI16_S3(mBoot, SMBUS_BUS, SMBUS_DEV, SMBUS_FUN, Rx, St, Rt)
#define WRITE_PCI32_SMBUS_S3(mBoot, Rx, Val) \
               WRITE_PCI32_S3(mBoot, SMBUS_BUS, SMBUS_DEV, SMBUS_FUN, Rx, Val)
#define SET_PCI32_SMBUS_S3(mBoot, Rx, Set) \
               SET_PCI32_S3(mBoot, SMBUS_BUS, SMBUS_DEV, SMBUS_FUN, Rx, Set)
#define RESET_PCI32_SMBUS_S3(mBoot, Rx, Rst) \
               RESET_PCI32_S3(mBoot, SMBUS_BUS, SMBUS_DEV, SMBUS_FUN, Rx, Rst)
#define RW_PCI32_SMBUS_S3(mBoot, Rx, St, Rt) \
               RW_PCI32_S3(mBoot, SMBUS_BUS, SMBUS_DEV, SMBUS_FUN, Rx, St, Rt)

//---------------------------------------------------------------------------

#define WRITE_PCI8_HECI_S3(mBoot, Rx, Val) \
                WRITE_PCI8_S3(mBoot, HECI_BUS, HECI_DEV, HECI_FUN, Rx, Val)
#define SET_PCI8_HECI_S3(mBoot, Rx, Set) \
                SET_PCI8_S3(mBoot, HECI_BUS, HECI_DEV, HECI_FUN, Rx, Set)
#define RESET_PCI8_HECI_S3(mBoot, Rx, Rst) \
                RESET_PCI8_S3(mBoot, HECI_BUS, HECI_DEV, HECI_FUN, Rx, Rst)
#define RW_PCI8_HECI_S3(mBoot, Rx, Set, Rst) \
                RW_PCI8_S3(mBoot, HECI_BUS, HECI_DEV, HECI_FUN, Rx, Set, Rst)
#define WRITE_PCI16_HECI_S3(mBoot, Rx, Val) \
                WRITE_PCI16_S3(mBoot, HECI_BUS, HECI_DEV, HECI_FUN, Rx, Val)
#define SET_PCI16_HECI_S3(mBoot, Rx, Set) \
                SET_PCI16_S3(mBoot, HECI_BUS, HECI_DEV, HECI_FUN, Rx, Set)
#define RESET_PCI16_HECI_S3(mBoot, Rx, Rst) \
                RESET_PCI16_S3(mBoot, HECI_BUS, HECI_DEV, HECI_FUN, Rx, Rst)
#define RW_PCI16_HECI_S3(mBoot, Rx, Set, Rst) \
                RW_PCI16_S3(mBoot, HECI_BUS, HECI_DEV, HECI_FUN, Rx, Set, Rst)
#define WRITE_PCI32_HECI_S3(mBoot, Rx, Val) \
                WRITE_PCI32_S3(mBoot, HECI_BUS, HECI_DEV, HECI_FUN, Rx, Val)
#define SET_PCI32_HECI_S3(mBoot, Rx, Set) \
                SET_PCI32_S3(mBoot, HECI_BUS, HECI_DEV, HECI_FUN, Rx, Set)
#define RESET_PCI32_HECI_S3(mBoot, Rx, Rst) \
                RESET_PCI32_S3(mBoot, HECI_BUS, HECI_DEV, HECI_FUN, Rx, Rst)
#define RW_PCI32_HECI_S3(mBoot, Rx, Set, Rst) \
                RW_PCI32_S3(mBoot, HECI_BUS, HECI_DEV, HECI_FUN, Rx, Set, Rst)

//---------------------------------------------------------------------------

#define WRITE_PCI8_HECI2_S3(mBoot, Rx, Val) \
                WRITE_PCI8_S3(mBoot, HECI2_BUS, HECI2_DEV, HECI2_FUN, Rx, Val)
#define SET_PCI8_HECI2_S3(mBoot, Rx, Set) \
                SET_PCI8_S3(mBoot, HECI2_BUS, HECI2_DEV, HECI2_FUN, Rx, Set)
#define RESET_PCI8_HECI2_S3(mBoot, Rx, Rst) \
                RESET_PCI8_S3(mBoot, HECI2_BUS, HECI2_DEV, HECI2_FUN, Rx, Rst)
#define RW_PCI8_HECI2_S3(mBoot, Rx, Set, Rst) \
                RW_PCI8_S3(mBoot, HECI2_BUS, HECI2_DEV, HECI2_FUN, Rx, Set, Rst)
#define WRITE_PCI16_HECI2_S3(mBoot, Rx, Val) \
                WRITE_PCI16_S3(mBoot, HECI2_BUS, HECI2_DEV, HECI2_FUN, Rx, Val)
#define SET_PCI16_HECI2_S3(mBoot, Rx, Set) \
                SET_PCI16_S3(mBoot, HECI2_BUS, HECI2_DEV, HECI2_FUN, Rx, Set)
#define RESET_PCI16_HECI2_S3(mBoot, Rx, Rst) \
                RESET_PCI16_S3(mBoot, HECI2_BUS, HECI2_DEV, HECI2_FUN, Rx, Rst)
#define RW_PCI16_HECI2_S3(mBoot, Rx, Set, Rst) \
                RW_PCI16_S3(mBoot, HECI2_BUS, HECI2_DEV, HECI2_FUN, Rx, Set, Rst)
#define WRITE_PCI32_HECI2_S3(mBoot, Rx, Val) \
                WRITE_PCI32_S3(mBoot, HECI2_BUS, HECI2_DEV, HECI2_FUN, Rx, Val)
#define SET_PCI32_HECI2_S3(mBoot, Rx, Set) \
                SET_PCI32_S3(mBoot, HECI2_BUS, HECI2_DEV, HECI2_FUN, Rx, Set)
#define RESET_PCI32_HECI2_S3(mBoot, Rx, Rst) \
                RESET_PCI32_S3(mBoot, HECI2_BUS, HECI2_DEV, HECI2_FUN, Rx, Rst)
#define RW_PCI32_HECI2_S3(mBoot, Rx, Set, Rst) \
                RW_PCI32_S3(mBoot, HECI2_BUS, HECI2_DEV, HECI2_FUN, Rx, Set, Rst)

//---------------------------------------------------------------------------
// Chipset MMIO Macros, Porting Required.
//---------------------------------------------------------------------------

#define READ_MEM8_RCRB(wReg)        READ_MEM8(SB_RCRB_BASE_ADDRESS | wReg)
#define WRITE_MEM8_RCRB(wReg, bVal) WRITE_MEM8(SB_RCRB_BASE_ADDRESS | wReg,bVal)
#define SET_MEM8_RCRB(wReg, Set)    RW_MEM8(SB_RCRB_BASE_ADDRESS | wReg, Set, 0)
#define RESET_MEM8_RCRB(wReg, Rst)  RW_MEM8(SB_RCRB_BASE_ADDRESS | wReg,0,Rst)
#define RW_MEM8_RCRB(wReg,Set,Rst)  RW_MEM8(SB_RCRB_BASE_ADDRESS|wReg,Set,Rst)
#define READ_MEM16_RCRB(wReg)       READ_MEM16(SB_RCRB_BASE_ADDRESS | wReg)
#define WRITE_MEM16_RCRB(wReg,Val)  WRITE_MEM16(SB_RCRB_BASE_ADDRESS|wReg,Val)
#define SET_MEM16_RCRB(wReg, Set)   RW_MEM16(SB_RCRB_BASE_ADDRESS|wReg, Set,0)
#define RESET_MEM16_RCRB(wReg, Rst) RW_MEM16(SB_RCRB_BASE_ADDRESS|wReg, 0,Rst)
#define RW_MEM16_RCRB(Reg,Set,Rst)  RW_MEM16(SB_RCRB_BASE_ADDRESS|Reg,Set,Rst)
#define READ_MEM32_RCRB(wReg)       READ_MEM32(SB_RCRB_BASE_ADDRESS | wReg)
#define WRITE_MEM32_RCRB(wReg,Val)  WRITE_MEM32(SB_RCRB_BASE_ADDRESS|wReg,Val)
#define SET_MEM32_RCRB(wReg,Set)    RW_MEM32(SB_RCRB_BASE_ADDRESS|wReg, Set,0)
#define RESET_MEM32_RCRB(wReg,Rst)  RW_MEM32(SB_RCRB_BASE_ADDRESS|wReg,0,Rst)
#define RW_MEM32_RCRB(Reg,Set,Rst)  RW_MEM32(SB_RCRB_BASE_ADDRESS|Reg,Set,Rst)

//---------------------------------------------------------------------------
#define WRITE_MEM8_RCRB_S3(mBoot, wReg, bVal) \
                         WRITE_MEM8_S3(mBoot, SB_RCRB_BASE_ADDRESS|wReg, bVal)
#define SET_MEM8_RCRB_S3(mBoot, wReg, Set) \
                         SET_MEM8_S3(mBoot, SB_RCRB_BASE_ADDRESS|wReg, Set)
#define RESET_MEM8_RCRB_S3(mBoot, wReg, Rst) \
                         RESET_MEM8_S3(mBoot, SB_RCRB_BASE_ADDRESS|wReg, Rst)
#define RW_MEM8_RCRB_S3(mBoot, wReg, Set, Rst) \
                         RW_MEM8_S3(mBoot, SB_RCRB_BASE_ADDRESS|wReg, Set,Rst)
#define WRITE_MEM16_RCRB_S3(mBoot, wReg, wVal) \
                         WRITE_MEM16_S3(mBoot, SB_RCRB_BASE_ADDRESS|wReg,wVal)
#define SET_MEM16_RCRB_S3(mBoot, wReg, Set) \
                         SET_MEM16_S3(mBoot, SB_RCRB_BASE_ADDRESS|wReg, Set)
#define RESET_MEM16_RCRB_S3(mBoot, wReg, Rst) \
                         RESET_MEM16_S3(mBoot, SB_RCRB_BASE_ADDRESS|wReg, Rst)
#define RW_MEM16_RCRB_S3(mBoot, wReg, Set, Rst) \
                         RW_MEM16_S3(mBoot,SB_RCRB_BASE_ADDRESS|wReg, Set,Rst)
#define WRITE_MEM32_RCRB_S3(mBoot, wReg, dVal) \
                         WRITE_MEM32_S3(mBoot, SB_RCRB_BASE_ADDRESS|wReg,dVal)
#define SET_MEM32_RCRB_S3(mBoot, wReg, Set) \
                         SET_MEM32_S3(mBoot, SB_RCRB_BASE_ADDRESS|wReg, Set)
#define RESET_MEM32_RCRB_S3(mBoot, wReg, Rst) \
                         RESET_MEM32_S3(mBoot, SB_RCRB_BASE_ADDRESS|wReg, Rst)
#define RW_MEM32_RCRB_S3(mBoot, wReg, Set, Rst) \
                         RW_MEM32_S3(mBoot,SB_RCRB_BASE_ADDRESS|wReg, Set,Rst)

//---------------------------------------------------------------------------
// SPI MMIO Macros, Porting Required.
//---------------------------------------------------------------------------

#define READ_MEM8_SPI(wReg)        READ_MEM8(SB_RCRB_BASE_ADDRESS + SPI_BASE_ADDRESS| wReg)
#define WRITE_MEM8_SPI(wReg, bVal) WRITE_MEM8(SB_RCRB_BASE_ADDRESS + SPI_BASE_ADDRESS | wReg,bVal)
#define SET_MEM8_SPI(wReg, Set)    RW_MEM8(SB_RCRB_BASE_ADDRESS + SPI_BASE_ADDRESS | wReg, Set, 0)
#define RESET_MEM8_SPI(wReg, Rst)  RW_MEM8(SB_RCRB_BASE_ADDRESS + SPI_BASE_ADDRESS | wReg,0,Rst)
#define RW_MEM8_SPI(wReg,Set,Rst)  RW_MEM8(SB_RCRB_BASE_ADDRESS + SPI_BASE_ADDRESS|wReg,Set,Rst)
#define READ_MEM16_SPI(wReg)       READ_MEM16(SB_RCRB_BASE_ADDRESS + SPI_BASE_ADDRESS | wReg)
#define WRITE_MEM16_SPI(wReg,Val)  WRITE_MEM16(SB_RCRB_BASE_ADDRESS + SPI_BASE_ADDRESS|wReg,Val)
#define SET_MEM16_SPI(wReg, Set)   RW_MEM16(SB_RCRB_BASE_ADDRESS + SPI_BASE_ADDRESS|wReg, Set,0)
#define RESET_MEM16_SPI(wReg, Rst) RW_MEM16(SB_RCRB_BASE_ADDRESS + SPI_BASE_ADDRESS|wReg, 0,Rst)
#define RW_MEM16_SPI(Reg,Set,Rst)  RW_MEM16(SB_RCRB_BASE_ADDRESS + SPI_BASE_ADDRESS|Reg,Set,Rst)
#define READ_MEM32_SPI(wReg)       READ_MEM32(SB_RCRB_BASE_ADDRESS + SPI_BASE_ADDRESS | wReg)
#define WRITE_MEM32_SPI(wReg,Val)  WRITE_MEM32(SB_RCRB_BASE_ADDRESS + SPI_BASE_ADDRESS|wReg,Val)
#define SET_MEM32_SPI(wReg,Set)    RW_MEM32(SB_RCRB_BASE_ADDRESS + SPI_BASE_ADDRESS|wReg, Set,0)
#define RESET_MEM32_SPI(wReg,Rst)  RW_MEM32(SB_RCRB_BASE_ADDRESS + SPI_BASE_ADDRESS|wReg,0,Rst)
#define RW_MEM32_SPI(Reg,Set,Rst)  RW_MEM32(SB_RCRB_BASE_ADDRESS + SPI_BASE_ADDRESS|Reg,Set,Rst)

//---------------------------------------------------------------------------
// Chipset I/O Macros, Porting Required.
//---------------------------------------------------------------------------

#define READ_IO8_PM(bReg)           READ_IO8(PM_BASE_ADDRESS+bReg)
#define WRITE_IO8_PM(bReg, bVal)    WRITE_IO8(PM_BASE_ADDRESS+bReg, bVal)
#define SET_IO8_PM(bReg, Set)       SET_IO8(PM_BASE_ADDRESS+bReg, Set)
#define RESET_IO8_PM(bReg, Reset)   RESET_IO8(PM_BASE_ADDRESS+bReg, Reset)
#define RW_IO8_PM(bReg, Set, Rst)   RW_IO8(PM_BASE_ADDRESS+bReg, Set, Rst)
#define READ_IO16_PM(bReg)          READ_IO16(PM_BASE_ADDRESS+bReg)
#define WRITE_IO16_PM(bReg, wVal)   WRITE_IO16(PM_BASE_ADDRESS+bReg, wVal)
#define SET_IO16_PM(bReg, Set)      SET_IO16(PM_BASE_ADDRESS+bReg, Set)
#define RESET_IO16_PM(bReg, Reset)  RESET_IO16(PM_BASE_ADDRESS+bReg, Reset)
#define RW_IO16_PM(bReg, Set, Rst)  RW_IO16(PM_BASE_ADDRESS+bReg, Set, Rst)
#define READ_IO32_PM(bReg)          READ_IO32(PM_BASE_ADDRESS+bReg)
#define WRITE_IO32_PM(bReg, dVal)   WRITE_IO32(PM_BASE_ADDRESS+bReg, dVal)
#define SET_IO32_PM(bReg, Set)      SET_IO32(PM_BASE_ADDRESS+bReg, Set)
#define RESET_IO32_PM(bReg, Reset)  RESET_IO32(PM_BASE_ADDRESS+bReg, Reset)
#define RW_IO32_PM(bReg, Set, Rst)  RW_IO32(PM_BASE_ADDRESS+bReg, Set, Rst)

//---------------------------------------------------------------------------

#define READ_IO8_TCO(bReg)          READ_IO8(TCO_BASE_ADDRESS+bReg)
#define WRITE_IO8_TCO(bReg, bVal)   WRITE_IO8(TCO_BASE_ADDRESS+bReg, bVal)
#define SET_IO8_TCO(bReg, Set)      SET_IO8(TCO_BASE_ADDRESS+bReg, Set)
#define RESET_IO8_TCO(bReg, Reset)  RESET_IO8(TCO_BASE_ADDRESS+bReg, Reset)
#define RW_IO8_TCO(bReg, Set, Rst)  RW_IO8(TCO_BASE_ADDRESS+bReg, Set, Rst)
#define READ_IO16_TCO(bReg)         READ_IO16(TCO_BASE_ADDRESS+bReg)
#define WRITE_IO16_TCO(bReg, wVal)  WRITE_IO16(TCO_BASE_ADDRESS+bReg, wVal)
#define SET_IO16_TCO(bReg, Set)     SET_IO16(TCO_BASE_ADDRESS+bReg, Set)
#define RESET_IO16_TCO(bReg, Reset) RESET_IO16(TCO_BASE_ADDRESS+bReg, Reset)
#define RW_IO16_TCO(bReg, Set, Rst) RW_IO16(TCO_BASE_ADDRESS+bReg, Set, Rst)
#define READ_IO32_TCO(bReg)         READ_IO32(TCO_BASE_ADDRESS+bReg)
#define WRITE_IO32_TCO(bReg, dVal)  WRITE_IO32(TCO_BASE_ADDRESS+bReg, dVal)
#define SET_IO32_TCO(bReg, Set)     SET_IO32(TCO_BASE_ADDRESS+bReg, Set)
#define RESET_IO32_TCO(bReg, Reset) RESET_IO32(TCO_BASE_ADDRESS+bReg, Reset)
#define RW_IO32_TCO(bReg, Set, Rst) RW_IO32(TCO_BASE_ADDRESS+bReg, Set, Rst)

//---------------------------------------------------------------------------

#define WRITE_IO8_PM_S3(mBoot, bReg, bVal) \
                            WRITE_IO8_S3(mBoot, PM_BASE_ADDRESS+bReg, bVal)
#define RW_IO8_PM_S3(mBoot, bReg, Set, Reset) \
                            RW_IO8_S3(mBoot, PM_BASE_ADDRESS+bReg, Set, Reset)
#define SET_IO8_PM_S3(mBoot, bReg, Set) \
                            RW_IO8_S3(mBoot, PM_BASE_ADDRESS+bReg, Set, 0)
#define RESET_IO8_PM_S3(mBoot, bReg, Reset) \
                            RW_IO8_S3(mBoot, PM_BASE_ADDRESS+bReg, 0, Reset)

#define WRITE_IO16_PM_S3(mBoot, bReg, bVal) \
                            WRITE_IO16_S3(mBoot, PM_BASE_ADDRESS+bReg, bVal)
#define RW_IO16_PM_S3(mBoot, bReg, Set, Rst) \
                            RW_IO16_S3(mBoot, PM_BASE_ADDRESS+bReg, Set, Rst)
#define SET_IO16_PM_S3(mBoot, bReg, Set) \
                            RW_IO16_S3(mBoot, PM_BASE_ADDRESS+bReg, Set, 0)
#define RESET_IO16_PM_S3(mBoot, bReg, Reset) \
                            RW_IO16_S3(mBoot, PM_BASE_ADDRESS+bReg, 0, Reset)

#define WRITE_IO32_PM_S3(mBoot, bReg, bVal) \
                            WRITE_IO32_S3(mBoot, PM_BASE_ADDRESS+bReg, bVal)
#define RW_IO32_PM_S3(mBoot, bReg, Set, Rst) \
                            RW_IO32_S3(mBoot, PM_BASE_ADDRESS+bReg, Set, Rst)
#define SET_IO32_PM_S3(mBoot, bReg, Set) \
                            RW_IO32_S3(mBoot, PM_BASE_ADDRESS+bReg, Set, 0)
#define RESET_IO32_PM_S3(mBoot, bReg, Reset) \
                            RW_IO32_S3(mBoot, PM_BASE_ADDRESS+bReg, 0, Reset)

//---------------------------------------------------------------------------

#define WRITE_IO8_TCO_S3(mBoot, bReg, bVal) \
                            WRITE_IO8_S3(mBoot, TCO_BASE_ADDRESS+bReg, bVal)
#define RW_IO8_TCO_S3(mBoot, bReg, Set, Rst) \
                            RW_IO8_S3(mBoot, TCO_BASE_ADDRESS+bReg, Set, Rst)
#define SET_IO8_TCO_S3(mBoot, bReg, Set) \
                            RW_IO8_S3(mBoot, TCO_BASE_ADDRESS+bReg, Set, 0)
#define RESET_IO8_TCO_S3(mBoot, bReg, Reset) \
                            RW_IO8_S3(mBoot, TCO_BASE_ADDRESS+bReg, 0, Reset)

#define WRITE_IO16_TCO_S3(mBoot, bReg, bVal) \
                            WRITE_IO16_S3(mBoot, TCO_BASE_ADDRESS+bReg, bVal)
#define RW_IO16_TCO_S3(mBoot, bReg, Set, Rst) \
                            RW_IO16_S3(mBoot, TCO_BASE_ADDRESS+bReg, Set, Rst)
#define SET_IO16_TCO_S3(mBoot, bReg, Set) \
                            RW_IO16_S3(mBoot, TCO_BASE_ADDRESS+bReg, Set, 0)
#define RESET_IO16_TCO_S3(mBoot, bReg, Reset) \
                            RW_IO16_S3(mBoot, TCO_BASE_ADDRESS+bReg, 0, Reset)

#define WRITE_IO32_TCO_S3(mBoot, bReg, bVal) \
                            WRITE_IO32_S3(mBoot, TCO_BASE_ADDRESS+bReg, bVal)
#define RW_IO32_TCO_S3(mBoot, bReg, Set, Rst) \
                            RW_IO32_S3(mBoot, TCO_BASE_ADDRESS+bReg, Set, Rst)
#define SET_IO32_TCO_S3(mBoot, bReg, Set) \
                            RW_IO32_S3(mBoot, TCO_BASE_ADDRESS+bReg, Set, 0)
#define RESET_IO32_TCO_S3(mBoot, bReg, Reset) \
                            RW_IO32_S3(mBoot, TCO_BASE_ADDRESS+bReg, 0, Reset)

//---------------------------------------------------------------------------

#define READ_IO8_RTC(bReg)          ReadIo8IdxData(CMOS_ADDR_PORT, bReg)
#define WRITE_IO8_RTC(bReg, bVal)   WriteIo8IdxData(CMOS_ADDR_PORT, bReg, bVal)
#define RW_IO8_RTC(bReg, Set, Rst)  RwIo8IdxData(CMOS_ADDR_PORT, bReg, Set, Rst)
#define SET_IO8_RTC(bReg, Set)      RwIo8IdxData(CMOS_ADDR_PORT, bReg, Set, 0)
#define RESET_IO8_RTC(bReg, Reset)  RwIo8IdxData(CMOS_ADDR_PORT, bReg, 0, Reset)

//---------------------------------------------------------------------------

#define WRITE_IO8_RTC_S3(mBoot, bReg, bVal) \
                            WriteIo8IdxDataS3(mBoot, CMOS_ADDR_PORT, bReg, bVal)
#define RW_IO8_RTC_S3(mBoot, bReg, Set, Rst) \
                            RwIo8IdxDataS3(mBoot, CMOS_ADDR_PORT, bReg, Set,Rst)
#define SET_IO8_RTC_S3(mBoot, bReg, Set) \
                            RwIo8IdxDataS3(mBoot, CMOS_ADDR_PORT, bReg, Set, 0)
#define RESET_IO8_RTC_S3(mBoot, bReg, Rst) \
                            RwIo8IdxDataS3(mBoot, CMOS_ADDR_PORT, bReg, 0, Rst)

//---------------------------------------------------------------------------

//-----------------------------------------------------------------------
#ifndef _EFI_MMIO_ACCESS_H_
#define _EFI_MMIO_ACCESS_H_

#define MmioAddress(BaseAddr, Register) \
    ( (UINTN)BaseAddr + (UINTN)(Register) )

// 32-bit
#define Mmio32Ptr(BaseAddr, Register) \
    ( (volatile UINT32 *)MmioAddress(BaseAddr, Register) )

#define Mmio32(BaseAddr, Register) \
    *Mmio32Ptr(BaseAddr, Register)

#define MmioRead32(Addr) \
    Mmio32(Addr, 0)

#define MmioWrite32(Addr, Value) \
    (Mmio32(Addr, 0) = (UINT32)Value)

#define MmioRW32(Addr, set, reset) \
    (Mmio32(Addr, 0) = ((Mmio32(Addr, 0) & (UINT32)~(reset)) | (UINT32)set))

// 16-bit
#define Mmio16Ptr(BaseAddr, Register) \
    ( (volatile UINT16 *)MmioAddress(BaseAddr, Register) )

#define Mmio16(BaseAddr, Register) \
    *Mmio16Ptr(BaseAddr, Register)

#define MmioRead16(Addr) \
    Mmio16(Addr, 0)

#define MmioWrite16(Addr, Value) \
    (Mmio16(Addr, 0) = (UINT16)Value)

#define MmioRW16(Addr, set, reset) \
    (Mmio16(Addr, 0) = ((Mmio16(Addr, 0) & (UINT16)~(reset)) | (UINT16)set))

// 8-bit
#define Mmio8Ptr(BaseAddr, Register) \
    ( (volatile UINT8 *)MmioAddress(BaseAddr, Register) )

#define Mmio8(BaseAddr, Register) \
    *Mmio8Ptr(BaseAddr, Register)

#define MmioRead8(Addr) \
    Mmio8(Addr, 0)

#define MmioWrite8(Addr, Value) \
    (Mmio8(Addr, 0) = (UINT8)Value)

#define MmioRW8(Addr, set, reset) \
    (Mmio8(Addr, 0) = ((Mmio8(Addr, 0) & (UINT8)~(reset)) | (UINT8)set))

#endif
//-----------------------------------------------------------------------


//-----------------------------------------------------------------------
//
//-----------------------------------------------------------------------
#ifndef _EFI_PCI_ACCESS_H_
#define _EFI_PCI_ACCESS_H_

#ifndef MmPciAddress
#define MmPciAddress(Base, Bus, Device, Function, Register) \
    ( (UINTN)(Base) + \
    (UINTN)(Bus << 20) + \
    (UINTN)(Device << 15) + \
    (UINTN)(Function << 12) + \
    (UINTN)(Register) )
#endif

// 32-bit
#define MmPci32Ptr(Bus, Device, Function, Register) \
    ( (volatile UINT32 *)MmPciAddress(PCIEX_BASE_ADDRESS, Bus, Device, Function, Register) )

#define MmPci32(Bus, Device, Function, Register) \
    *MmPci32Ptr(Bus, Device, Function, Register)

#define MmPciRead32(Bus, Device, Function, Register) \
    MmPci32(Bus, Device, Function, Register)

#define MmPciWrite32(Bus, Device, Function, Register, Value) \
    (MmPci32(Bus, Device, Function, Register) = (UINT32)Value)

#define MmPciRW32(Bus, Device, Function, Register, set, reset) \
    (MmPci32(Bus, Device, Function, Register) = ((MmPci32(Bus, Device, Function, Register) & (UINT32)~(reset)) | (UINT32)set))

// 16-bit
#define MmPci16Ptr(Bus, Device, Function, Register) \
    ( (volatile UINT16 *)MmPciAddress(PCIEX_BASE_ADDRESS, Bus, Device, Function, Register) )

#define MmPci16(Bus, Device, Function, Register) \
    *MmPci16Ptr(Bus, Device, Function, Register)

#define MmPciRead16(Bus, Device, Function, Register) \
    MmPci16(Bus, Device, Function, Register)

#define MmPciWrite16(Bus, Device, Function, Register, Value) \
    (MmPci16(Bus, Device, Function, Register) = (UINT16)Value)

#define MmPciRW16(Bus, Device, Function, Register, set, reset) \
    (MmPci16(Bus, Device, Function, Register) = ((MmPci16(Bus, Device, Function, Register) & (UINT16)~(reset)) | (UINT16)set))

// 8-bit
#define MmPci8Ptr(Bus, Device, Function, Register) \
    ( (volatile UINT8 *)MmPciAddress(PCIEX_BASE_ADDRESS, Bus, Device, Function, Register) )

#define MmPci8(Bus, Device, Function, Register) \
    *MmPci8Ptr(Bus, Device, Function, Register)

#define MmPciRead8(Bus, Device, Function, Register) \
    MmPci8(Bus, Device, Function, Register)

#define MmPciWrite8(Bus, Device, Function, Register, Value) \
    (MmPci8(Bus, Device, Function, Register) = (UINT8)Value)

#define MmPciRW8(Bus, Device, Function, Register, set, reset) \
    (MmPci8(Bus, Device, Function, Register) = ((MmPci8(Bus, Device, Function, Register) & (UINT8)~(reset)) | (UINT8)set))

#endif
//-----------------------------------------------------------------------

UINT32 DummyVerbTable[];

#ifdef __cplusplus
}
#endif
#endif


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
