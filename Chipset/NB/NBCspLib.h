//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
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
// $Header: /Alaska/BIN/Chipset/Intel/NorthBridge/Haswell/Intel SystemAgent NB Chipset/NBCspLib.h 5     10/14/12 5:17a Jeffch $
//
// $Revision: 5 $
//
// $Date: 10/14/12 5:17a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Chipset/Intel/NorthBridge/Haswell/Intel SystemAgent NB Chipset/NBCspLib.h $
// 
// 5     10/14/12 5:17a Jeffch
// [TAG]          None
// [Severity]     Important
// [Description]  Follow SA RC 0.71.
// [Files]        NBPei.c, NBDxe.c; NBGeneric.c; NBCspLib.h; NBSetup.c;
// Nb.sd; GetSetupData.c;
// 
// 4     10/14/12 12:20a Jeffch
// [TAG]         None
// [Severity]    Important
// [Description] Update by XTU4.0.
// [Files]       NBPei.c, NBDxe.c, NBCspLib.h, NBGeneric.c
// 
// 2     4/26/12 2:39a Yurenlai
// [TAG]           None
// [Category]      Improvement
// [Severity]      Important
// [Description]   Fixed PeiRamBootSupport = 1 warm boot system is hang.
// [Description]   NBPEI.c, NBCspLib.h 
// 
// 1     2/08/12 4:34a Yurenlai
// Intel Haswell/NB eChipset initially releases.
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:        NbCspLib.h
//
// Description: This file contains North Bridge chipset porting functions
//              and data structures definition for both PEI & DXE stage.
//
//<AMI_FHDR_END>
//*************************************************************************

#ifndef __NBLIB_H__
#define __NBLIB_H__

#include <Efi.h>
#include <Pei.h>
#include <Token.h>
#include <Protocol\PciHostBridgeResourceAllocation.h>
#include <Protocol\PciRootBridgeIo.h>
#include <PciHostBridge.h>
#include <AmiDxeLib.h>
#include <PciBus.h>


#if ACPI_SUPPORT
 #if defined(PI_SPECIFICATION_VERSION) && (PI_SPECIFICATION_VERSION >= 0x0001000A)
 #include <Protocol\S3SaveState.h>
 #else
 #include <Protocol\BootScriptSave.h>
 #endif
#endif

#ifndef AMI_S3_SAVE_PROTOCOL
 #if defined(PI_SPECIFICATION_VERSION) && (PI_SPECIFICATION_VERSION >= 0x0001000A)
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

#if CSM_SUPPORT
#define LEGACY_REGION_LOCK          0
#define LEGACY_REGION_BOOT_LOCK     1
#define LEGACY_REGION_UNLOCK        2
#define LEGACY_REGION_DECODE_ROM    3
#endif

typedef struct {
    UINT8                   Bus;
    UINT8                   Dev;
    UINT8                   Fun;
    UINT8                   Reg;
    EFI_BOOT_SCRIPT_WIDTH   Width;
    UINT32                  Mask;
} BOOT_SCRIPT_NB_PCI_REG_SAVE;

typedef struct {
    UINT8   Register;
    UINT8   Mask;
    UINT32  StartAddress;
    UINT32  Length;
} NB_PAM_STRUCT;

UINT8
NbFrequencyToRatio (
  UINT32    Frequency,
  UINT8     RefClk,
  UINT32    RefBClk
);

UINT32
NbRatioToFrequency (
  UINT8   Ratio,
  UINT8   RefClk,
  UINT32  RefBClk
);

EFI_STATUS NBProgramPAMRegisters (
    EFI_BOOT_SERVICES       *pBS,
    EFI_RUNTIME_SERVICES    *pRS,
    UINT32                  StartAddress, 
    UINT32                  Length,
    UINT8                   Setting, 
    UINT32                  *Granularity
);

EFI_STATUS NBPeiProgramPAMRegisters (
    EFI_PEI_SERVICES        **PeiServices,
    UINT32                  StartAddress,
    UINT32                  Length,
    UINT8                   Setting,
    UINT32                  *Granularity OPTIONAL
);

VOID NBRetrainLinkPciDevice (
    IN UINT8                PciBus,
    IN UINT8                PciDev,
    IN UINT8                PciFun,
    IN UINT8                CapPtr
);

EFI_STATUS NBProtectedPciDevice (
    IN PCI_DEV_INFO                     *PciDevice
);

EFI_STATUS NBProgramPciDevice (
    IN PCI_DEV_INFO                     *PciDevice
);

EFI_STATUS NBUpdatePciDeviceAttributes (
    IN PCI_DEV_INFO                     *PciDevice,
    IN OUT UINT64                       *Attributes,
    IN UINT64                           Capabilities,
    IN BOOLEAN                          Set
);

EFI_STATUS NBPAMWriteBootScript(
    IN AMI_S3_SAVE_PROTOCOL             *BootScriptSave
);

VOID NbRuntimeShadowRamWrite(
    IN BOOLEAN Enable
);

BOOLEAN
CheckPeiFvCopyToRam (
    IN  EFI_PEI_SERVICES  **PeiServices
);

#if (CORE_COMBINED_VERSION >= 0x4027C) // 4.6.3.6
#if AMI_ROOT_BRIDGE_SUPPORT == 1
UINTN HbCspMapRootBrgToHost(
    IN PCI_BUS_XLAT_HDR    *RootBrgXlatHdr, 
    IN UINT64              *AllocationAttr,
    IN UINT64              *RbSuportedAttr
);

EFI_STATUS HbCspAllocateResources(
    IN PCI_HOST_BRG_DATA    *HostBrgData,
    IN PCI_ROOT_BRG_DATA    *RootBrgData,
    IN UINTN                RootBrgIndex
);
#endif
#else
UINTN HbCspMapRootBrgToHost(
    IN PCI_BUS_XLAT_HDR             *RootBrgXlatHdr
);
#endif

UINT32 NBGetTsegBase ( VOID );

VOID NBEnableEmrr(
     IN UINT32 IedStart, 
     IN UINT32 IedSize
);

UINT32 NbFindCapPtr(
 IN UINT64  PciAddress,
 IN UINT8   CapId
);


VOID
WritePci8S3(
    IN AMI_S3_SAVE_PROTOCOL             *mBootScriptSave,
    IN UINT8                            Bus, 
    IN UINT8                            Dev,
    IN UINT8                            Fun, 
    IN UINT16                           Reg,
    IN UINT8                            WriteValue8
);

VOID
WritePci16S3(
    IN AMI_S3_SAVE_PROTOCOL             *mBootScriptSave,
    IN UINT8                            Bus, 
    IN UINT8                            Dev,
    IN UINT8                            Fun, 
    IN UINT16                           Reg,
    IN UINT16                           WriteValue16
);

VOID
WritePci32S3(
    IN AMI_S3_SAVE_PROTOCOL             *mBootScriptSave,
    IN UINT8                            Bus, 
    IN UINT8                            Dev,
    IN UINT8                            Fun, 
    IN UINT16                           Reg,
    IN UINT32                           WriteValue32
);

VOID
RwPci8S3(
    IN AMI_S3_SAVE_PROTOCOL             *mBootScriptSave,
    IN UINT8                            Bus, 
    IN UINT8                            Dev,
    IN UINT8                            Fun, 
    IN UINT16                           Reg,
    IN UINT8                            SetBit8,
    IN UINT8                            ResetBit8
);

VOID
RwPci16S3(
    IN AMI_S3_SAVE_PROTOCOL             *mBootScriptSave,
    IN UINT8                            Bus, 
    IN UINT8                            Dev,
    IN UINT8                            Fun, 
    IN UINT16                           Reg,
    IN UINT16                           SetBit16,
    IN UINT16                           ResetBit16
);

VOID
RwPci32S3(
    IN AMI_S3_SAVE_PROTOCOL             *mBootScriptSave,
    IN UINT8                            Bus, 
    IN UINT8                            Dev,
    IN UINT8                            Fun, 
    IN UINT16                           Reg,
    IN UINT32                           SetBit32,
    IN UINT32                           ResetBit32
);

VOID
WriteMem8S3(
    IN AMI_S3_SAVE_PROTOCOL             *mBootScriptSave,
    IN UINT64                           Address,
    IN UINT8                            Value
);

VOID
WriteMem16S3(
    IN AMI_S3_SAVE_PROTOCOL             *mBootScriptSave,
    IN UINT64                           Address,
    IN UINT16                           Value
);

VOID
WriteMem32S3(
    IN AMI_S3_SAVE_PROTOCOL             *mBootScriptSave,
    IN UINT64                           Address,
    IN UINT32                           Value
);

VOID
RwMem8S3(
    IN AMI_S3_SAVE_PROTOCOL             *mBootScriptSave,
    IN UINT64                           Address,
    IN UINT8                            SetBit8,
    IN UINT8                            ResetBit8
);

VOID
RwMem16S3(
    IN AMI_S3_SAVE_PROTOCOL             *mBootScriptSave,
    IN UINT64                           Address,
    IN UINT16                           SetBit16,
    IN UINT16                           ResetBit16
);

VOID
RwMem32S3(
    IN AMI_S3_SAVE_PROTOCOL             *mBootScriptSave,
    IN UINT64                           Address,
    IN UINT32                           SetBit32,
    IN UINT32                           ResetBit32
);

UINT8
ReadPci8(
    IN UINT8    Bus, 
    IN UINT8    Dev,
    IN UINT8    Fun, 
    IN UINT16   Reg
);

UINT16
ReadPci16(
    IN UINT8    Bus, 
    IN UINT8    Dev,
    IN UINT8    Fun, 
    IN UINT16   Reg
);

UINT32
ReadPci32(
    IN UINT8    Bus, 
    IN UINT8    Dev,
    IN UINT8    Fun, 
    IN UINT16   Reg
);

VOID
WritePci8(
    IN UINT8    Bus, 
    IN UINT8    Dev,
    IN UINT8    Fun, 
    IN UINT16   Reg,
    IN UINT8    Value8
);

VOID
WritePci16(
    IN UINT8    Bus, 
    IN UINT8    Dev,
    IN UINT8    Fun, 
    IN UINT16   Reg,
    IN UINT16   Value16
);

VOID
WritePci32(
    IN UINT8    Bus, 
    IN UINT8    Dev,
    IN UINT8    Fun, 
    IN UINT16   Reg,
    IN UINT32   Value32
);

VOID
RwPci8(
    IN UINT8    Bus, 
    IN UINT8    Dev,
    IN UINT8    Fun, 
    IN UINT16   Reg,
    IN UINT8    SetBit8,
    IN UINT8    ResetBit8
);

VOID
RwPci16(
    IN UINT8    Bus, 
    IN UINT8    Dev,
    IN UINT8    Fun, 
    IN UINT16   Reg,
    IN UINT16   SetBit16,
    IN UINT16   ResetBit16
);

VOID
RwPci32(
    IN UINT8    Bus, 
    IN UINT8    Dev,
    IN UINT8    Fun, 
    IN UINT16   Reg,
    IN UINT32   SetBit32,
    IN UINT32   ResetBit32
);

VOID
WriteMem8 (
    IN UINT64       Address,
    IN UINT8        Value8
);

VOID
WriteMem16 (
    IN UINT64       Address,
    IN UINT16       Value16
);

VOID
WriteMem32 (
    IN UINT64       Address,
    IN UINT32       Value32
);

VOID
RwMem8(
    IN UINT64   Address,
    IN UINT8    SetBit8,
    IN UINT8    ResetBit8
);

VOID
RwMem16(
    IN UINT64   Address,
    IN UINT16   SetBit16,
    IN UINT16   ResetBit16
);

VOID
RwMem32(
    IN UINT64   Address,
    IN UINT32   SetBit32,
    IN UINT32   ResetBit32
);

//----------------------------------------------------------------------------
// Standard PCI Macros, No Porting Required.
//----------------------------------------------------------------------------

#define READ_PCI8(Bx, Dx, Fx, Rx)           ReadPci8(Bx, Dx, Fx, Rx)
#define READ_PCI16(Bx, Dx, Fx, Rx)          ReadPci16(Bx, Dx, Fx, Rx)
#define READ_PCI32(Bx, Dx, Fx, Rx)          ReadPci32(Bx, Dx, Fx, Rx)
#define WRITE_PCI8(Bx, Dx, Fx, Rx, bVal)    WritePci8(Bx, Dx, Fx, Rx, bVal)
#define WRITE_PCI16(Bx, Dx, Fx, Rx, wVal)   WritePci16(Bx, Dx, Fx, Rx, wVal)
#define WRITE_PCI32(Bx, Dx, Fx, Rx, dVal)   WritePci32(Bx, Dx, Fx, Rx, dVal)
#define RW_PCI8(Bx, Dx, Fx, Rx, Set, Rst) \
          WritePci8(Bx, Dx, Fx, Rx, ReadPci8(Bx, Dx, Fx, Rx) & ~(Rst) | (Set))
#define RW_PCI16(Bx, Dx, Fx, Rx, Set, Rst) \
          WritePci16(Bx, Dx, Fx, Rx, ReadPci16(Bx, Dx, Fx, Rx) & ~(Rst)|(Set))
#define RW_PCI32(Bx, Dx, Fx, Rx, Set, Rst) \
          WritePci32(Bx, Dx, Fx, Rx, ReadPci32(Bx, Dx, Fx, Rx) & ~(Rst)|(Set))
#define SET_PCI8(Bx, Dx, Fx, Rx, bSet) \
                WritePci8(Bx, Dx, Fx, Rx, ReadPci8(Bx, Dx, Fx, Rx) | (bSet))
#define SET_PCI16(Bx, Dx, Fx, Rx, wSet) \
                WritePci16(Bx, Dx, Fx, Rx, ReadPci16(Bx, Dx, Fx, Rx) | (wSet))
#define SET_PCI32(Bx, Dx, Fx, Rx, dSet) \
                WritePci32(Bx, Dx, Fx, Rx, ReadPci32(Bx, Dx, Fx, Rx) | (dSet))
#define RESET_PCI8(Bx, Dx, Fx, Rx, bReset) \
               WritePci8(Bx, Dx, Fx, Rx, ReadPci8(Bx, Dx, Fx, Rx) & ~(bReset))
#define RESET_PCI16(Bx, Dx, Fx, Rx, wRst) \
               WritePci16(Bx, Dx, Fx, Rx, ReadPci16(Bx, Dx, Fx, Rx) & ~(wRst))
#define RESET_PCI32(Bx, Dx, Fx, Rx, dRst) \
               WritePci32(Bx, Dx, Fx, Rx, ReadPci32(Bx, Dx, Fx, Rx) & ~(dRst))

#define WRITE_PCI8_S3(mBtScSv, Bx, Dx, Fx, Rx, bValue) \
                                WritePci8S3(mBtScSv, Bx, Dx, Fx, Rx, bValue)
#define SET_PCI8_S3(mBtScSv, Bx, Dx, Fx, Rx, bSet) \
                                RwPci8S3(mBtScSv, Bx, Dx, Fx, Rx, bSet, 0)
#define RESET_PCI8_S3(mBtScSv, Bx, Dx, Fx, Rx, bReset) \
                                RwPci8S3(mBtScSv, Bx, Dx, Fx, Rx, 0, bReset)
#define RW_PCI8_S3(mBtScSv, Bx, Dx, Fx, Rx, bSet, bRst) \
                                RwPci8S3(mBtScSv, Bx, Dx, Fx, Rx, bSet, bRst)
#define WRITE_PCI16_S3(mBtScSv, Bx, Dx, Fx, Rx, wValue) \
                                WritePci16S3(mBtScSv, Bx, Dx, Fx, Rx, wValue)
#define SET_PCI16_S3(mBtScSv, Bx, Dx, Fx, Rx, wSet) \
                                RwPci16S3(mBtScSv, Bx, Dx, Fx, Rx, wSet, 0)
#define RESET_PCI16_S3(mBtScSv, Bx, Dx, Fx, Rx, wReset) \
                                RwPci16S3(mBtScSv, Bx, Dx, Fx, Rx, 0, wReset)
#define RW_PCI16_S3(mBtScSv, Bx, Dx, Fx, Rx, wSet, wRst) \
                                RwPci16S3(mBtScSv, Bx, Dx, Fx, Rx, wSet, wRst)
#define WRITE_PCI32_S3(mBtScSv, Bx, Dx, Fx, Rx, dValue) \
                                WritePci32S3(mBtScSv, Bx, Dx, Fx, Rx, dValue)
#define SET_PCI32_S3(mBtScSv, Bx, Dx, Fx, Rx, dSet) \
                                RwPci32S3(mBtScSv, Bx, Dx, Fx, Rx, dSet, 0) 
#define RESET_PCI32_S3(mBtScSv, Bx, Dx, Fx, Rx, dReset) \
                                RwPci32S3(mBtScSv, Bx, Dx, Fx, Rx, 0, dReset) 
#define RW_PCI32_S3(mBtScSv, Bx, Dx, Fx, Rx, dSet, dRst) \
                                RwPci32S3(mBtScSv, Bx, Dx, Fx, Rx, dSet, dRst)

//----------------------------------------------------------------------------
// Standard Memory Macros, No Porting Required.
//----------------------------------------------------------------------------

#define READ_MEM8(Addr64)               MMIO_READ8(Addr64)
#define MEM_READ8(Addr64)               MMIO_READ8(Addr64)
#define READ_MMIO8(Addr64)              MMIO_READ8(Addr64)
#define WRITE_MEM8(Addr64, bValue)      WriteMem8(Addr64, bValue)
#define MEM_WRITE8(Addr64, bValue)      WriteMem8(Addr64, bValue)
#define WRITE_MMIO8(Addr64, bValue)     WriteMem8(Addr64, bValue)
#define SET_MEM8(Addr64, bSet)          RwMem8(Addr64, bSet, 0)
#define MEM_SET8(Addr64, bSet)          RwMem8(Addr64, bSet, 0)
#define SET_MMIO8(Addr64, bSet)         RwMem8(Addr64, bSet, 0)
#define MMIO_SET8(Addr64, bSet)         RwMem8(Addr64, bSet, 0)
#define RESET_MEM8(Addr64, bReset)      RwMem8(Addr64, 0, bReset)
#define MEM_RESET8(Addr64, bReset)      RwMem8(Addr64, 0, bReset)
#define RESET_MMIO8(Addr64, bReset)     RwMem8(Addr64, 0, bReset)
#define MMIO_RESET8(Addr64, bReset)     RwMem8(Addr64, 0, bReset)
#define RW_MEM8(Addr64, bSet, bReset)   RwMem8(Addr64, bSet, bReset)
#define MEM_RW8(Addr64, bSet, bReset)   RwMem8(Addr64, bSet, bReset)
#define RW_MMIO8(Addr64, bSet, bReset)  RwMem8(Addr64, bSet, bReset)
#define MMIO_RW8(Addr64, bSet, bReset)  RwMem8(Addr64, bSet, bReset)

#define READ_MEM16(Addr64)              MMIO_READ16(Addr64)
#define MEM_READ16(Addr64)              MMIO_READ16(Addr64)
#define READ_MMIO16(Addr64)             MMIO_READ16(Addr64)
#define WRITE_MEM16(Addr64, wValue)     WriteMem16(Addr64, wValue)
#define MEM_WRITE16(Addr64, wValue)     WriteMem16(Addr64, wValue)
#define WRITE_MMIO16(Addr64, wValue)    WriteMem16(Addr64, wValue)
#define SET_MEM16(Addr64, wSet)         RwMem16(Addr64, wSet, 0)
#define MEM_SET16(Addr64, wSet)         RwMem16(Addr64, wSet, 0)
#define SET_MMIO16(Addr64, wSet)        RwMem16(Addr64, wSet, 0)
#define MMIO_SET16(Addr64, wSet)        RwMem16(Addr64, wSet, 0)
#define RESET_MEM16(Addr64, wReset)     RwMem16(Addr64, 0, wReset)
#define MEM_RESET16(Addr64, wReset)     RwMem16(Addr64, 0, wReset)
#define RESET_MMIO16(Addr64, wReset)    RwMem16(Addr64, 0, wReset)
#define MMIO_RESET16(Addr64, wReset)    RwMem16(Addr64, 0, wReset)
#define RW_MEM16(Addr64, wSet, wReset)  RwMem16(Addr64, wSet, wReset)
#define MEM_RW16(Addr64, wSet, wReset)  RwMem16(Addr64, wSet, wReset)
#define RW_MMIO16(Addr64, wSet, wReset) RwMem16(Addr64, wSet, wReset)
#define MMIO_RW16(Addr64, wSet, wReset) RwMem16(Addr64, wSet, wReset)

#define READ_MEM32(Addr64)              MMIO_READ32(Addr64)
#define MEM_READ32(Addr64)              MMIO_READ32(Addr64)
#define READ_MMIO32(Addr64)             MMIO_READ32(Addr64)
#define WRITE_MEM32(Addr64, dValue)     WriteMem32(Addr64, dValue)
#define MEM_WRITE32(Addr64, dValue)     WriteMem32(Addr64, dValue)
#define WRITE_MMIO32(Addr64, dValue)    WriteMem32(Addr64, dValue)
#define SET_MEM32(Addr64, dSet)         RwMem32(Addr64, dSet, 0)
#define MEM_SET32(Addr64, dSet)         RwMem32(Addr64, dSet, 0)
#define SET_MMIO32(Addr64, dSet)        RwMem32(Addr64, dSet, 0)
#define MMIO_SET32(Addr64, dSet)        RwMem32(Addr64, dSet, 0)
#define RESET_MEM32(Addr64, dReset)     RwMem32(Addr64, 0, dReset)
#define MEM_RESET32(Addr64, dReset)     RwMem32(Addr64, 0, dReset)
#define RESET_MMIO32(Addr64, dReset)    RwMem32(Addr64, 0, dReset)
#define MMIO_RESET32(Addr64, dReset)    RwMem32(Addr64, 0, dReset)
#define RW_MEM32(Addr64, dSet, dReset)  RwMem32(Addr64, dSet, dReset)
#define MEM_RW32(Addr64, dSet, dReset)  RwMem32(Addr64, dSet, dReset)
#define RW_MMIO32(Addr64, dSet, dReset) RwMem32(Addr64, dSet, dReset)
#define MMIO_RW32(Addr64, dSet, dReset) RwMem32(Addr64, dSet, dReset)

//----------------------------------------------------------------------------

#define WRITE_MEM8_S3(mBtScSv, Addr64, bValue) \
                                    WriteMem8S3(mBtScSv, Addr64, bValue) 
#define MEM_WRITE8_S3(mBtScSv, Addr64, bValue) \
                                    WriteMem8S3(mBtScSv, Addr64, bValue) 
#define WRITE_MMIO8_S3(mBtScSv, Addr64, bValue) \
                                    WriteMem8S3(mBtScSv, Addr64, bValue) 
#define MMIO_WRITE8_S3(mBtScSv, Addr64, bValue) \
                                    WriteMem8S3(mBtScSv, Addr64, bValue) 
#define SET_MEM8_S3(mBtScSv, Addr64, bSet) \
                                    RwMem8S3(mBtScSv, Addr64, bSet, 0) 
#define MEM_SET8_S3(mBtScSv, Addr64, bSet) \
                                    RwMem8S3(mBtScSv, Addr64, bSet, 0) 
#define SET_MMIO8_S3(mBtScSv, Addr64, bSet) \
                                    RwMem8S3(mBtScSv, Addr64, bSet, 0) 
#define MMIO_SET8_S3(mBtScSv, Addr64, bSet) \
                                    RwMem8S3(mBtScSv, Addr64, bSet, 0) 
#define RESET_MEM8_S3(mBtScSv, Addr64, bReset) \
                                    RwMem8S3(mBtScSv, Addr64, 0, bReset) 
#define MEM_RESET8_S3(mBtScSv, Addr64, bReset) \
                                    RwMem8S3(mBtScSv, Addr64, 0, bReset) 
#define RESET_MMIO8_S3(mBtScSv, Addr64, bReset) \
                                    RwMem8S3(mBtScSv, Addr64, 0, bReset) 
#define MMIO_RESET8_S3(mBtScSv, Addr64, bReset) \
                                    RwMem8S3(mBtScSv, Addr64, 0, bReset) 
#define RW_MEM8_S3(mBtScSv, Addr64, bSet, bReset) \
                                    RwMem8S3(mBtScSv, Addr64, bSet, bReset) 
#define MEM_RW8_S3(mBtScSv, Addr64, bSet, bReset) \
                                    RwMem8S3(mBtScSv, Addr64, bSet, bReset) 
#define RW_MMIO8_S3(mBtScSv, Addr64, bSet, bReset) \
                                    RwMem8S3(mBtScSv, Addr64, bSet, bReset) 
#define MMIO_RW8_S3(mBtScSv, Addr64, bSet, bReset) \
                                    RwMem8S3(mBtScSv, Addr64, bSet, bReset) 
#define WRITE_MEM16_S3(mBtScSv, Addr64, wValue) \
                                    WriteMem16S3(mBtScSv, Addr64, wValue) 
#define MEM_WRITE16_S3(mBtScSv, Addr64, wValue) \
                                    WriteMem16S3(mBtScSv, Addr64, wValue) 
#define WRITE_MMIO16_S3(mBtScSv, Addr64, wValue) \
                                    WriteMem16S3(mBtScSv, Addr64, wValue) 
#define MMIO_WRITE16_S3(mBtScSv, Addr64, wValue) \
                                    WriteMem16S3(mBtScSv, Addr64, wValue) 
#define SET_MEM16_S3(mBtScSv, Addr64, wSet) \
                                    RwMem16S3(mBtScSv, Addr64, wSet, 0) 
#define MEM_SET16_S3(mBtScSv, Addr64, wSet) \
                                    RwMem16S3(mBtScSv, Addr64, wSet, 0) 
#define SET_MMIO16_S3(mBtScSv, Addr64, wSet) \
                                    RwMem16S3(mBtScSv, Addr64, wSet, 0) 
#define MMIO_SET16_S3(mBtScSv, Addr64, wSet) \
                                    RwMem16S3(mBtScSv, Addr64, wSet, 0) 
#define RESET_MEM16_S3(mBtScSv, Addr64, wReset) \
                                    RwMem16S3(mBtScSv, Addr64, 0, wReset) 
#define MEM_RESET16_S3(mBtScSv, Addr64, wReset) \
                                    RwMem16S3(mBtScSv, Addr64, 0, wReset) 
#define RESET_MMIO16_S3(mBtScSv, Addr64, wReset) \
                                    RwMem16S3(mBtScSv, Addr64, 0, wReset) 
#define MMIO_RESET16_S3(mBtScSv, Addr64, wReset) \
                                    RwMem16S3(mBtScSv, Addr64, 0, wReset) 
#define RW_MEM16_S3(mBtScSv, Addr64, wSet, wReset) \
                                    RwMem16S3(mBtScSv, Addr64, wSet, wReset) 
#define MEM_RW16_S3(mBtScSv, Addr64, wSet, wReset) \
                                    RwMem16S3(mBtScSv, Addr64, wSet, wReset) 
#define RW_MMIO16_S3(mBtScSv, Addr64, wSet, wReset) \
                                    RwMem16S3(mBtScSv, Addr64, wSet, wReset) 
#define MMIO_RW16_S3(mBtScSv, Addr64, wSet, wReset) \
                                    RwMem16S3(mBtScSv, Addr64, wSet, wReset) 
#define WRITE_MEM32_S3(mBtScSv, Addr64, dValue) \
                                    WriteMem32S3(mBtScSv, Addr64, dValue) 
#define MEM_WRITE32_S3(mBtScSv, Addr64, dValue) \
                                    WriteMem32S3(mBtScSv, Addr64, dValue) 
#define WRITE_MMIO32_S3(mBtScSv, Addr64, dValue) \
                                    WriteMem32S3(mBtScSv, Addr64, dValue) 
#define MMIO_WRITE32_S3(mBtScSv, Addr64, dValue) \
                                    WriteMem32S3(mBtScSv, Addr64, dValue) 
#define SET_MEM32_S3(mBtScSv, Addr64, dSet) \
                                    RwMem32S3(mBtScSv, Addr64, dSet, 0) 
#define MEM_SET32_S3(mBtScSv, Addr64, dSet) \
                                    RwMem32S3(mBtScSv, Addr64, dSet, 0) 
#define SET_MMIO32_S3(mBtScSv, Addr64, dSet) \
                                    RwMem32S3(mBtScSv, Addr64, dSet, 0) 
#define MMIO_SET32_S3(mBtScSv, Addr64, dSet) \
                                    RwMem32S3(mBtScSv, Addr64, dSet, 0) 
#define RESET_MEM32_S3(mBtScSv, Addr64, dReset) \
                                    RwMem32S3(mBtScSv, Addr64, 0, dReset) 
#define MEM_RESET32_S3(mBtScSv, Addr64, dReset) \
                                    RwMem32S3(mBtScSv, Addr64, 0, dReset) 
#define RESET_MMIO32_S3(mBtScSv, Addr64, dReset) \
                                    RwMem32S3(mBtScSv, Addr64, 0, dReset) 
#define MMIO_RESET32_S3(mBtScSv, Addr64, dReset) \
                                    RwMem32S3(mBtScSv, Addr64, 0, dReset) 
#define RW_MEM32_S3(mBtScSv, Addr64, dSet, dReset) \
                                    RwMem32S3(mBtScSv, Addr64, dSet, dReset) 
#define MEM_RW32_S3(mBtScSv, Addr64, dSet, dReset) \
                                    RwMem32S3(mBtScSv, Addr64, dSet, dReset) 
#define RW_MMIO32_S3(mBtScSv, Addr64, dSet, dReset) \
                                    RwMem32S3(mBtScSv, Addr64, dSet, dReset) 
#define MMIO_RW32_S3(mBtScSv, Addr64, dSet, dReset) \
                                    RwMem32S3(mBtScSv, Addr64, dSet, dReset) 

//----------------------------------------------------------------------------
// Chipset PCI Macros, Porting Required.
//----------------------------------------------------------------------------

#define READ_PCI8_NB(Rx)          READ_PCI8(NB_BUS, NB_DEV, NB_FUN, Rx)
#define WRITE_PCI8_NB(Rx, Val)    WRITE_PCI8(NB_BUS, NB_DEV, NB_FUN, Rx, Val)
#define SET_PCI8_NB(Rx, Set)      SET_PCI8(NB_BUS, NB_DEV, NB_FUN, Rx, Set)
#define RESET_PCI8_NB(Rx, Rst)    RESET_PCI8(NB_BUS, NB_DEV, NB_FUN, Rx, Rst)
#define RW_PCI8_NB(Rx, St, Rt)    RW_PCI8(NB_BUS, NB_DEV, NB_FUN, Rx, St, Rt)
#define READ_PCI16_NB(Rx)         READ_PCI16(NB_BUS, NB_DEV, NB_FUN, Rx)
#define WRITE_PCI16_NB(Rx, Val)   WRITE_PCI16(NB_BUS, NB_DEV, NB_FUN, Rx, Val)
#define SET_PCI16_NB(Rx, Set)     SET_PCI16(NB_BUS, NB_DEV, NB_FUN, Rx, Set)
#define RESET_PCI16_NB(Rx, Rst)   RESET_PCI16(NB_BUS, NB_DEV, NB_FUN, Rx, Rst)
#define RW_PCI16_NB(Rx, St, Rt)   RW_PCI16(NB_BUS, NB_DEV, NB_FUN, Rx, St, Rt)
#define READ_PCI32_NB(Rx)         READ_PCI32(NB_BUS, NB_DEV, NB_FUN, Rx)
#define WRITE_PCI32_NB(Rx, Val)   WRITE_PCI32(NB_BUS, NB_DEV, NB_FUN, Rx, Val)
#define SET_PCI32_NB(Rx, Set)     SET_PCI32(NB_BUS, NB_DEV, NB_FUN, Rx, Set)
#define RESET_PCI32_NB(Rx, Rst)   RESET_PCI32(NB_BUS, NB_DEV, NB_FUN, Rx, Rst)
#define RW_PCI32_NB(Rx, St, Rt)   RW_PCI32(NB_BUS, NB_DEV, NB_FUN, Rx, St, Rt)

//----------------------------------------------------------------------------

#define READ_PCI8_PCIEBRN(Rx) \
                    READ_PCI8(PCIEBRN_BUS, PCIEBRN_DEV, PCIEBRN_FUN, Rx)
#define WRITE_PCI8_PCIEBRN(Rx, Val) \
                    WRITE_PCI8(PCIEBRN_BUS, PCIEBRN_DEV, PCIEBRN_FUN, Rx, Val)
#define SET_PCI8_PCIEBRN(Rx, Set) \
                    SET_PCI8(PCIEBRN_BUS, PCIEBRN_DEV, PCIEBRN_FUN, Rx, Set)
#define RESET_PCI8_PCIEBRN(Rx, Rst) \
                    RESET_PCI8(PCIEBRN_BUS, PCIEBRN_DEV, PCIEBRN_FUN, Rx, Rst)
#define RW_PCI8_PCIEBRN(Rx, St, Rt) \
                    RW_PCI8(PCIEBRN_BUS, PCIEBRN_DEV, PCIEBRN_FUN, Rx, St, Rt)
#define READ_PCI16_PCIEBRN(Rx) \
                    READ_PCI16(PCIEBRN_BUS, PCIEBRN_DEV, PCIEBRN_FUN, Rx)
#define WRITE_PCI16_PCIEBRN(Rx, Vx) \
                    WRITE_PCI16(PCIEBRN_BUS, PCIEBRN_DEV, PCIEBRN_FUN, Rx, Vx)
#define SET_PCI16_PCIEBRN(Rx, Set) \
                    SET_PCI16(PCIEBRN_BUS, PCIEBRN_DEV, PCIEBRN_FUN, Rx, Set)
#define RESET_PCI16_PCIEBRN(Rx, Rt) \
                    RESET_PCI16(PCIEBRN_BUS, PCIEBRN_DEV, PCIEBRN_FUN, Rx, Rt)
#define RW_PCI16_PCIEBRN(Rx, St, Rt) \
                    RW_PCI16(PCIEBRN_BUS, PCIEBRN_DEV, PCIEBRN_FUN, Rx, St,Rt)
#define READ_PCI32_PCIEBRN(Rx) \
                    READ_PCI32(PCIEBRN_BUS, PCIEBRN_DEV, PCIEBRN_FUN, Rx)
#define WRITE_PCI32_PCIEBRN(Rx, Vx) \
                    WRITE_PCI32(PCIEBRN_BUS, PCIEBRN_DEV, PCIEBRN_FUN, Rx, Vx)
#define SET_PCI32_PCIEBRN(Rx, Set) \
                    SET_PCI32(PCIEBRN_BUS, PCIEBRN_DEV, PCIEBRN_FUN, Rx, Set)
#define RESET_PCI32_PCIEBRN(Rx, Rt) \
                    RESET_PCI32(PCIEBRN_BUS, PCIEBRN_DEV, PCIEBRN_FUN, Rx, Rt)
#define RW_PCI32_PCIEBRN(Rx, St, Rt) \
                    RW_PCI32(PCIEBRN_BUS, PCIEBRN_DEV, PCIEBRN_FUN, Rx, St,Rt)

//----------------------------------------------------------------------------

#define READ_PCI8_IGD(Rx)       READ_PCI8(IGD_BUS, IGD_DEV, IGD_FUN, Rx)
#define WRITE_PCI8_IGD(Rx, Val) WRITE_PCI8(IGD_BUS, IGD_DEV, IGD_FUN, Rx, Val)
#define SET_PCI8_IGD(Rx, Set)   SET_PCI8(IGD_BUS, IGD_DEV, IGD_FUN, Rx, Set)
#define RESET_PCI8_IGD(Rx, Rst) RESET_PCI8(IGD_BUS, IGD_DEV, IGD_FUN, Rx, Rst)
#define RW_PCI8_IGD(Rx, St, Rt) RW_PCI8(IGD_BUS, IGD_DEV, IGD_FUN, Rx, St, Rt)
#define READ_PCI16_IGD(Rx)      READ_PCI16(IGD_BUS, IGD_DEV, IGD_FUN, Rx)
#define WRITE_PCI16_IGD(Rx, Vx) WRITE_PCI16(IGD_BUS, IGD_DEV, IGD_FUN, Rx, Vx)
#define SET_PCI16_IGD(Rx, Set)  SET_PCI16(IGD_BUS, IGD_DEV, IGD_FUN, Rx, Set)
#define RESET_PCI16_IGD(Rx, Rt) RESET_PCI16(IGD_BUS, IGD_DEV, IGD_FUN, Rx, Rt)
#define RW_PCI16_IGD(Rx, St,Rt) RW_PCI16(IGD_BUS, IGD_DEV, IGD_FUN, Rx, St,Rt)
#define READ_PCI32_IGD(Rx)      READ_PCI32(IGD_BUS, IGD_DEV, IGD_FUN, Rx)
#define WRITE_PCI32_IGD(Rx, Vx) WRITE_PCI32(IGD_BUS, IGD_DEV, IGD_FUN, Rx, Vx)
#define SET_PCI32_IGD(Rx, Set)  SET_PCI32(IGD_BUS, IGD_DEV, IGD_FUN, Rx, Set)
#define RESET_PCI32_IGD(Rx, Rt) RESET_PCI32(IGD_BUS, IGD_DEV, IGD_FUN, Rx, Rt)
#define RW_PCI32_IGD(Rx, St,Rt) RW_PCI32(IGD_BUS, IGD_DEV, IGD_FUN, Rx, St,Rt)

//----------------------------------------------------------------------------

#define WRITE_PCI8_NB_S3(mBoot, Rx, Val) \
                     WRITE_PCI8_S3(mBoot, NB_BUS, NB_DEV, NB_FUN, Rx, Val)
#define SET_PCI8_NB_S3(mBoot, Rx, Set) \
                     SET_PCI8_S3(mBoot, NB_BUS, NB_DEV, NB_FUN, Rx, Set)
#define RESET_PCI8_NB_S3(mBoot, Rx, Reset) \
                     RESET_PCI8_S3(mBoot, NB_BUS, NB_DEV, NB_FUN, Rx, Reset)
#define RW_PCI8_NB_S3(mBoot, Rx, Set, Rst) \
                     RW_PCI8_S3(mBoot, NB_BUS, NB_DEV, NB_FUN, Rx, Set, Rst)
#define WRITE_PCI16_NB_S3(mBoot, Rx, Val) \
                     WRITE_PCI16_S3(mBoot, NB_BUS, NB_DEV, NB_FUN, Rx, Val)
#define SET_PCI16_NB_S3(mBoot, Rx, Set) \
                     SET_PCI16_S3(mBoot, NB_BUS, NB_DEV, NB_FUN, Rx, Set)
#define RESET_PCI16_NB_S3(mBoot, Rx, Reset) \
                     RESET_PCI16_S3(mBoot, NB_BUS, NB_DEV, NB_FUN, Rx, Reset)
#define RW_PCI16_NB_S3(mBoot, Rx, Set, Rst) \
                     RW_PCI16_S3(mBoot, NB_BUS, NB_DEV, NB_FUN, Rx, Set, Rst)
#define WRITE_PCI32_NB_S3(mBoot, Rx, Val) \
                     WRITE_PCI32_S3(mBoot, NB_BUS, NB_DEV, NB_FUN, Rx, Val)
#define SET_PCI32_NB_S3(mBoot, Rx, Set) \
                     SET_PCI32_S3(mBoot, NB_BUS, NB_DEV, NB_FUN, Rx, Set)
#define RESET_PCI32_NB_S3(mBoot, Rx, Reset) \
                     RESET_PCI32_S3(mBoot, NB_BUS, NB_DEV, NB_FUN, Rx, Reset)
#define RW_PCI32_NB_S3(mBoot, Rx, Set, Rst) \
                     RW_PCI32_S3(mBoot, NB_BUS, NB_DEV, NB_FUN, Rx, Set, Rst)

//----------------------------------------------------------------------------

#define WRITE_PCI8_PCIEBRN_S3(mBoot, Rx, Val) \
         WRITE_PCI8_S3(mBoot, PCIEBRN_BUS, PCIEBRN_DEV, PCIEBRN_FUN, Rx, Val)
#define SET_PCI8_PCIEBRN_S3(mBoot, Rx, Set) \
         SET_PCI8_S3(mBoot, PCIEBRN_BUS, PCIEBRN_DEV, PCIEBRN_FUN, Rx, Set)
#define RESET_PCI8_PCIEBRN_S3(mBoot, Rx, Rst) \
         RESET_PCI8_S3(mBoot, PCIEBRN_BUS, PCIEBRN_DEV, PCIEBRN_FUN, Rx, Rst)
#define RW_PCI8_PCIEBRN_S3(mBoot, Rx, St, Rt) \
         RW_PCI8_S3(mBoot, PCIEBRN_BUS, PCIEBRN_DEV, PCIEBRN_FUN, Rx, St, Rt)
#define WRITE_PCI16_PCIEBRN_S3(mBoot, Rx, Val) \
         WRITE_PCI16_S3(mBoot, PCIEBRN_BUS, PCIEBRN_DEV, PCIEBRN_FUN, Rx, Val)
#define SET_PCI16_PCIEBRN_S3(mBoot, Rx, Set) \
         SET_PCI16_S3(mBoot, PCIEBRN_BUS, PCIEBRN_DEV, PCIEBRN_FUN, Rx, Set)
#define RESET_PCI16_PCIEBRN_S3(mBoot, Rx, Rst) \
         RESET_PCI16_S3(mBoot, PCIEBRN_BUS, PCIEBRN_DEV, PCIEBRN_FUN, Rx, Rst)
#define RW_PCI16_PCIEBRN_S3(mBoot, Rx, St, Rt) \
         RW_PCI16_S3(mBoot, PCIEBRN_BUS, PCIEBRN_DEV, PCIEBRN_FUN, Rx, St, Rt)
#define WRITE_PCI32_PCIEBRN_S3(mBoot, Rx, Val) \
         WRITE_PCI32_S3(mBoot, PCIEBRN_BUS, PCIEBRN_DEV, PCIEBRN_FUN, Rx, Val)
#define SET_PCI32_PCIEBRN_S3(mBoot, Rx, Set) \
         SET_PCI32_S3(mBoot, PCIEBRN_BUS, PCIEBRN_DEV, PCIEBRN_FUN, Rx, Set)
#define RESET_PCI32_PCIEBRN_S3(mBoot, Rx, Reset) \
         RESET_PCI32_S3(mBoot, PCIEBRN_BUS, PCIEBRN_DEV, PCIEBRN_FUN, Rx, Rst)
#define RW_PCI32_PCIEBRN_S3(mBoot, Rx, St, Rt) \
         RW_PCI32_S3(mBoot, PCIEBRN_BUS, PCIEBRN_DEV, PCIEBRN_FUN, Rx, St, Rt)

//----------------------------------------------------------------------------

#define WRITE_PCI8_IGD_S3(mBoot, Rx, Val) \
                   WRITE_PCI8_S3(mBoot, IGD_BUS, IGD_DEV, IGD_FUN, Rx, Val)
#define SET_PCI8_IGD_S3(mBoot, Rx, Set) \
                   SET_PCI8_S3(mBoot, IGD_BUS, IGD_DEV, IGD_FUN, Rx, Set)
#define RESET_PCI8_IGD_S3(mBoot, Rx, Reset) \
                   RESET_PCI8_S3(mBoot, IGD_BUS, IGD_DEV, IGD_FUN, Rx, Reset)
#define RW_PCI8_IGD_S3(mBoot, Rx, Set, Rst) \
                   RW_PCI8_S3(mBoot, IGD_BUS, IGD_DEV, IGD_FUN, Rx, Set, Rst)
#define WRITE_PCI16_IGD_S3(mBoot, Rx, Val) \
                   WRITE_PCI16_S3(mBoot, IGD_BUS, IGD_DEV, IGD_FUN, Rx, Val)
#define SET_PCI16_IGD_S3(mBoot, Rx, Set) \
                   SET_PCI16_S3(mBoot, IGD_BUS, IGD_DEV, IGD_FUN, Rx, Set)
#define RESET_PCI16_IGD_S3(mBoot, Rx, Reset) \
                   RESET_PCI16_S3(mBoot, IGD_BUS, IGD_DEV, IGD_FUN, Rx, Reset)
#define RW_PCI16_IGD_S3(mBoot, Rx, Set, Rst) \
                   RW_PCI16_S3(mBoot, IGD_BUS, IGD_DEV, IGD_FUN, Rx, Set, Rst)
#define WRITE_PCI32_IGD_S3(mBoot, Rx, Val) \
                   WRITE_PCI32_S3(mBoot, IGD_BUS, IGD_DEV, IGD_FUN, Rx, Val)
#define SET_PCI32_IGD_S3(mBoot, Rx, Set) \
                   SET_PCI32_S3(mBoot, IGD_BUS, IGD_DEV, IGD_FUN, Rx, Set)
#define RESET_PCI32_IGD_S3(mBoot, Rx, Reset) \
                   RESET_PCI32_S3(mBoot, IGD_BUS, IGD_DEV, IGD_FUN, Rx, Reset)
#define RW_PCI32_IGD_S3(mBoot, Rx, Set, Rst) \
                   RW_PCI32_S3(mBoot, IGD_BUS, IGD_DEV, IGD_FUN, Rx, Set, Rst)

//----------------------------------------------------------------------------
// Chipset MMIO Macros, Porting Required.
//----------------------------------------------------------------------------

#define READ_MEM8_EP(wReg)          READ_MEM8(NB_EP_BASE_ADDRESS | wReg)
#define READ_MMIO8_EP(wReg)         READ_MEM8(NB_EP_BASE_ADDRESS | wReg)
#define WRITE_MEM8_EP(wReg, bVal)   WRITE_MEM8(NB_EP_BASE_ADDRESS | wReg,bVal)
#define WRITE_MMIO8_EP(wReg, bVal)  WRITE_MEM8(NB_EP_BASE_ADDRESS | wReg,bVal)
#define SET_MEM8_EP(wReg, Set)      RW_MEM8(NB_EP_BASE_ADDRESS | wReg, Set, 0)
#define SET_MMIO8_EP(wReg, Set)     RW_MEM8(NB_EP_BASE_ADDRESS | wReg, Set, 0)
#define RESET_MEM8_EP(wReg, Rst)    RW_MEM8(NB_EP_BASE_ADDRESS | wReg, 0, Rst)
#define RESET_MMIO8_EP(wReg, Rst)   RW_MEM8(NB_EP_BASE_ADDRESS | wReg, 0, Rst)
#define RW_MEM8_EP(wReg, Set, Rst)  RW_MEM8(NB_EP_BASE_ADDRESS|wReg, Set, Rst)
#define RW_MMIO8_EP(wReg, Set, Rst) RW_MEM8(NB_EP_BASE_ADDRESS|wReg, Set, Rst)
#define READ_MEM16_EP(wReg)         READ_MEM16(NB_EP_BASE_ADDRESS | wReg)
#define READ_MMIO16_EP(wReg)        READ_MEM16(NB_EP_BASE_ADDRESS | wReg)
#define WRITE_MEM16_EP(wReg, wVal)  WRITE_MEM16(NB_EP_BASE_ADDRESS|wReg, wVal)
#define WRITE_MMIO16_EP(wReg, wVal) WRITE_MEM16(NB_EP_BASE_ADDRESS|wReg, wVal)
#define SET_MEM16_EP(wReg, Set)     RW_MEM16(NB_EP_BASE_ADDRESS|wReg, Set, 0)
#define SET_MMIO16_EP(wReg, Set)    RW_MEM16(NB_EP_BASE_ADDRESS|wReg, Set, 0)
#define RESET_MEM16_EP(wReg, Rst)   RW_MEM16(NB_EP_BASE_ADDRESS | wReg, 0,Rst)
#define RESET_MMIO16_EP(wReg, Rst)  RW_MEM16(NB_EP_BASE_ADDRESS | wReg, 0,Rst)
#define RW_MEM16_EP(wReg, Set, Rst) RW_MEM16(NB_EP_BASE_ADDRESS|wReg, Set,Rst)
#define RW_MMIO16_EP(wReg, Set,Rst) RW_MEM16(NB_EP_BASE_ADDRESS|wReg, Set,Rst)
#define READ_MEM32_EP(wReg)         READ_MEM32(NB_EP_BASE_ADDRESS | wReg)
#define READ_MMIO32_EP(wReg)        READ_MEM32(NB_EP_BASE_ADDRESS | wReg)
#define WRITE_MEM32_EP(wReg, dVal)  WRITE_MEM32(NB_EP_BASE_ADDRESS|wReg, dVal)
#define WRITE_MMIO32_EP(wReg, dVal) WRITE_MEM32(NB_EP_BASE_ADDRESS|wReg, dVal)
#define SET_MEM32_EP(wReg, Set)     RW_MEM32(NB_EP_BASE_ADDRESS|wReg, Set, 0)
#define SET_MMIO32_EP(wReg, Set)    RW_MEM32(NB_EP_BASE_ADDRESS|wReg, Set, 0)
#define RESET_MEM32_EP(wReg, Rst)   RW_MEM32(NB_EP_BASE_ADDRESS|wReg, 0, Rst)
#define RESET_MMIO32_EP(wReg, Rst)  RW_MEM32(NB_EP_BASE_ADDRESS|wReg, 0, Rst)
#define RW_MEM32_EP(wReg, Set, Rst) RW_MEM32(NB_EP_BASE_ADDRESS|wReg, Set,Rst)
#define RW_MMIO32_EP(wReg, Set,Rst) RW_MEM32(NB_EP_BASE_ADDRESS|wReg, Set,Rst)

//----------------------------------------------------------------------------

#define READ_MEM8_MCH(wReg)         READ_MEM8(NB_MCH_BASE_ADDRESS | wReg)
#define READ_MMIO8_MCH(wReg)        READ_MEM8(NB_MCH_BASE_ADDRESS | wReg)
#define WRITE_MEM8_MCH(wReg, bVal)  WRITE_MEM8(NB_MCH_BASE_ADDRESS| wReg,bVal)
#define WRITE_MMIO8_MCH(wReg, bVal) WRITE_MEM8(NB_MCH_BASE_ADDRESS| wReg,bVal)
#define SET_MEM8_MCH(wReg, Set)     RW_MEM8(NB_MCH_BASE_ADDRESS | wReg, Set,0)
#define SET_MMIO8_MCH(wReg, Set)    RW_MEM8(NB_MCH_BASE_ADDRESS | wReg, Set,0)
#define RESET_MEM8_MCH(wReg, Rst)   RW_MEM8(NB_MCH_BASE_ADDRESS | wReg,0, Rst)
#define RESET_MMIO8_MCH(wReg, Rst)  RW_MEM8(NB_MCH_BASE_ADDRESS | wReg,0, Rst)
#define RW_MEM8_MCH(wReg, Set, Rst) RW_MEM8(NB_MCH_BASE_ADDRESS|wReg, Set,Rst)
#define RW_MMIO8_MCH(wReg, Set,Rst) RW_MEM8(NB_MCH_BASE_ADDRESS|wReg, Set,Rst)
#define READ_MEM16_MCH(wReg)        READ_MEM16(NB_MCH_BASE_ADDRESS | wReg)
#define READ_MMIO16_MCH(wReg)       READ_MEM16(NB_MCH_BASE_ADDRESS | wReg)
#define WRITE_MEM16_MCH(wReg, wVal) WRITE_MEM16(NB_MCH_BASE_ADDRESS|wReg,wVal)
#define WRITE_MMIO16_MCH(wReg,wVal) WRITE_MEM16(NB_MCH_BASE_ADDRESS|wReg,wVal)
#define SET_MEM16_MCH(wReg, Set)    RW_MEM16(NB_MCH_BASE_ADDRESS|wReg,Set, 0)
#define SET_MMIO16_MCH(wReg, Set)   RW_MEM16(NB_MCH_BASE_ADDRESS|wReg,Set, 0)
#define RESET_MEM16_MCH(wReg, Rst)  RW_MEM16(NB_MCH_BASE_ADDRESS | wReg,0,Rst)
#define RESET_MMIO16_MCH(wReg, Rst) RW_MEM16(NB_MCH_BASE_ADDRESS | wReg,0,Rst)
#define RW_MEM16_MCH(wReg, Set,Rst) RW_MEM16(NB_MCH_BASE_ADDRESS|wReg,Set,Rst)
#define RW_MMIO16_MCH(wReg,Set,Rst) RW_MEM16(NB_MCH_BASE_ADDRESS|wReg,Set,Rst)
#define READ_MEM32_MCH(wReg)        READ_MEM32(NB_MCH_BASE_ADDRESS | wReg)
#define READ_MMIO32_MCH(wReg)       READ_MEM32(NB_MCH_BASE_ADDRESS | wReg)
#define WRITE_MEM32_MCH(wReg, dVal) WRITE_MEM32(NB_MCH_BASE_ADDRESS|wReg,dVal)
#define WRITE_MMIO32_MCH(wReg,dVal) WRITE_MEM32(NB_MCH_BASE_ADDRESS|wReg,dVal)
#define SET_MEM32_MCH(wReg, Set)    RW_MEM32(NB_MCH_BASE_ADDRESS|wReg, Set, 0)
#define SET_MMIO32_MCH(wReg, Set)   RW_MEM32(NB_MCH_BASE_ADDRESS|wReg, Set, 0)
#define RESET_MEM32_MCH(wReg, Rst)  RW_MEM32(NB_MCH_BASE_ADDRESS|wReg, 0, Rst)
#define RESET_MMIO32_MCH(wReg, Rst) RW_MEM32(NB_MCH_BASE_ADDRESS|wReg, 0, Rst)
#define RW_MEM32_MCH(wReg, Set,Rst) RW_MEM32(NB_MCH_BASE_ADDRESS|wReg,Set,Rst)
#define RW_MMIO32_MCH(wReg,Set,Rst) RW_MEM32(NB_MCH_BASE_ADDRESS|wReg,Set,Rst)

//----------------------------------------------------------------------------

#define READ_MEM8_DMI(wReg)         READ_MEM8(NB_DMI_BASE_ADDRESS | wReg)
#define READ_MMIO8_DMI(wReg)        READ_MEM8(NB_DMI_BASE_ADDRESS | wReg)
#define WRITE_MEM8_DMI(wReg, bVal)  WRITE_MEM8(NB_DMI_BASE_ADDRESS| wReg,bVal)
#define WRITE_MMIO8_DMI(wReg, bVal) WRITE_MEM8(NB_DMI_BASE_ADDRESS| wReg,bVal)
#define SET_MEM8_DMI(wReg, Set)     RW_MEM8(NB_DMI_BASE_ADDRESS | wReg, Set,0)
#define SET_MMIO8_DMI(wReg, Set)    RW_MEM8(NB_DMI_BASE_ADDRESS | wReg, Set,0)
#define RESET_MEM8_DMI(wReg, Rst)   RW_MEM8(NB_DMI_BASE_ADDRESS | wReg,0, Rst)
#define RESET_MMIO8_DMI(wReg, Rst)  RW_MEM8(NB_DMI_BASE_ADDRESS | wReg,0, Rst)
#define RW_MEM8_DMI(wReg, Set, Rst) RW_MEM8(NB_DMI_BASE_ADDRESS|wReg, Set,Rst)
#define RW_MMIO8_DMI(wReg, Set,Rst) RW_MEM8(NB_DMI_BASE_ADDRESS|wReg, Set,Rst)
#define READ_MEM16_DMI(wReg)        READ_MEM16(NB_DMI_BASE_ADDRESS | wReg)
#define READ_MMIO16_DMI(wReg)       READ_MEM16(NB_DMI_BASE_ADDRESS | wReg)
#define WRITE_MEM16_DMI(wReg, wVal) WRITE_MEM16(NB_DMI_BASE_ADDRESS|wReg,wVal)
#define WRITE_MMIO16_DMI(wReg,wVal) WRITE_MEM16(NB_DMI_BASE_ADDRESS|wReg,wVal)
#define SET_MEM16_DMI(wReg, Set)    RW_MEM16(NB_DMI_BASE_ADDRESS|wReg,Set, 0)
#define SET_MMIO16_DMI(wReg, Set)   RW_MEM16(NB_DMI_BASE_ADDRESS|wReg,Set, 0)
#define RESET_MEM16_DMI(wReg, Rst)  RW_MEM16(NB_DMI_BASE_ADDRESS | wReg,0,Rst)
#define RESET_MMIO16_DMI(wReg, Rst) RW_MEM16(NB_DMI_BASE_ADDRESS | wReg,0,Rst)
#define RW_MEM16_DMI(wReg, Set,Rst) RW_MEM16(NB_DMI_BASE_ADDRESS|wReg,Set,Rst)
#define RW_MMIO16_DMI(wReg,Set,Rst) RW_MEM16(NB_DMI_BASE_ADDRESS|wReg,Set,Rst)
#define READ_MEM32_DMI(wReg)        READ_MEM32(NB_DMI_BASE_ADDRESS | wReg)
#define READ_MMIO32_DMI(wReg)       READ_MEM32(NB_DMI_BASE_ADDRESS | wReg)
#define WRITE_MEM32_DMI(wReg, dVal) WRITE_MEM32(NB_DMI_BASE_ADDRESS|wReg,dVal)
#define WRITE_MMIO32_DMI(wReg,dVal) WRITE_MEM32(NB_DMI_BASE_ADDRESS|wReg,dVal)
#define SET_MEM32_DMI(wReg, Set)    RW_MEM32(NB_DMI_BASE_ADDRESS|wReg, Set, 0)
#define SET_MMIO32_DMI(wReg, Set)   RW_MEM32(NB_DMI_BASE_ADDRESS|wReg, Set, 0)
#define RESET_MEM32_DMI(wReg, Rst)  RW_MEM32(NB_DMI_BASE_ADDRESS|wReg, 0, Rst)
#define RESET_MMIO32_DMI(wReg,Rst)  RW_MEM32(NB_DMI_BASE_ADDRESS|wReg, 0, Rst)
#define RW_MEM32_DMI(wReg, Set,Rst) RW_MEM32(NB_DMI_BASE_ADDRESS|wReg,Set,Rst)
#define RW_MMIO32_DMI(wReg,Set,Rst) RW_MEM32(NB_DMI_BASE_ADDRESS|wReg,Set,Rst)

//----------------------------------------------------------------------------

#define WRITE_MEM8_EP_S3(mBoot, wReg, bVal) \
                          WRITE_MEM8_S3(mBoot, NB_EP_BASE_ADDRESS | wReg,bVal)
#define WRITE_MMIO8_EP_S3(mBoot, wReg, bVal) \
                          WRITE_MEM8_S3(mBoot, NB_EP_BASE_ADDRESS | wReg,bVal)
#define SET_MEM8_EP_S3(mBoot, wReg, Set) \
                          RW_MEM8_S3(mBoot, NB_EP_BASE_ADDRESS | wReg, Set, 0)
#define SET_MMIO8_EP_S3(mBoot, wReg, Set) \
                          RW_MEM8_S3(mBoot, NB_EP_BASE_ADDRESS | wReg, Set, 0)
#define RESET_MEM8_EP_S3(mBoot, wReg, Rst) \
                          RW_MEM8_S3(mBoot, NB_EP_BASE_ADDRESS | wReg, 0, Rst)
#define RESET_MMIO8_EP_S3(mBoot, wReg, Rst) \
                          RW_MEM8_S3(mBoot, NB_EP_BASE_ADDRESS | wReg, 0, Rst)
#define RW_MEM8_EP_S3(mBoot, wReg, Set, Rst) \
                          RW_MEM8_S3(mBoot, NB_EP_BASE_ADDRESS|wReg, Set, Rst)
#define RW_MMIO8_EP_S3(mBoot, wReg, Set, Rst) \
                          RW_MEM8_S3(mBoot, NB_EP_BASE_ADDRESS|wReg, Set, Rst)
#define WRITE_MEM16_EP_S3(mBoot, wReg, wVal) \
                          WRITE_MEM16_S3(mBoot, NB_EP_BASE_ADDRESS|wReg, wVal)
#define WRITE_MMIO16_EP_S3(mBoot, wReg, wVal) \
                          WRITE_MEM16_S3(mBoot, NB_EP_BASE_ADDRESS|wReg, wVal)
#define SET_MEM16_EP_S3(mBoot, wReg, Set) \
                          RW_MEM16_S3(mBoot, NB_EP_BASE_ADDRESS|wReg, Set, 0)
#define SET_MMIO16_EP_S3(mBoot, wReg, Set) \
                          RW_MEM16_S3(mBoot, NB_EP_BASE_ADDRESS|wReg, Set, 0)
#define RESET_MEM16_EP_S3(mBoot, wReg, Rst) \
                          RW_MEM16_S3(mBoot, NB_EP_BASE_ADDRESS | wReg, 0,Rst)
#define RESET_MMIO16_EP_S3(mBoot, wReg, Rst) \
                          RW_MEM16_S3(mBoot, NB_EP_BASE_ADDRESS | wReg, 0,Rst)
#define RW_MEM16_EP_S3(mBoot, wReg, Set, Rst) \
                          RW_MEM16_S3(mBoot, NB_EP_BASE_ADDRESS|wReg, Set,Rst)
#define RW_MMIO16_EP_S3(mBoot, wReg, Set, Rst) \
                          RW_MEM16_S3(mBoot, NB_EP_BASE_ADDRESS|wReg, Set,Rst)
#define WRITE_MEM32_EP_S3(mBoot, wReg, dVal) \
                          WRITE_MEM32_S3(mBoot, NB_EP_BASE_ADDRESS|wReg, dVal)
#define WRITE_MMIO32_EP_S3(mBoot, wReg, dVal) \
                          WRITE_MEM32_S3(mBoot, NB_EP_BASE_ADDRESS|wReg, dVal)
#define SET_MEM32_EP_S3(mBoot, wReg, Set) \
                          RW_MEM32_S3(mBoot, NB_EP_BASE_ADDRESS|wReg, Set, 0)
#define SET_MMIO32_EP_S3(mBoot, wReg, Set) \
                          RW_MEM32_S3(mBoot, NB_EP_BASE_ADDRESS|wReg, Set, 0)
#define RESET_MEM32_EP_S3(mBoot, wReg, Rst) \
                          RW_MEM32_S3(mBoot, NB_EP_BASE_ADDRESS|wReg, 0, Rst)
#define RESET_MMIO32_EP_S3(mBoot, wReg, Rst) \
                          RW_MEM32_S3(mBoot, NB_EP_BASE_ADDRESS|wReg, 0, Rst)
#define RW_MEM32_EP_S3(mBoot, wReg, Set, Rst) \
                          RW_MEM32_S3(mBoot, NB_EP_BASE_ADDRESS|wReg, Set,Rst)
#define RW_MMIO32_EP_S3(mBoot, wReg, Set, Rst) \
                          RW_MEM32_S3(mBoot, NB_EP_BASE_ADDRESS|wReg, Set,Rst)

//----------------------------------------------------------------------------

#define WRITE_MEM8_MCH_S3(mBoot, wReg, bVal) \
                         WRITE_MEM8_S3(mBoot, NB_MCH_BASE_ADDRESS | wReg,bVal)
#define WRITE_MMIO8_MCH_S3(mBoot, wReg, bVal) \
                         WRITE_MEM8_S3(mBoot, NB_MCH_BASE_ADDRESS | wReg,bVal)
#define SET_MEM8_MCH_S3(mBoot, wReg, Set) \
                         RW_MEM8_S3(mBoot, NB_MCH_BASE_ADDRESS | wReg, Set, 0)
#define SET_MMIO8_MCH_S3(mBoot, wReg, Set) \
                         RW_MEM8_S3(mBoot, NB_MCH_BASE_ADDRESS | wReg, Set, 0)
#define RESET_MEM8_MCH_S3(mBoot, wReg, Rst) \
                         RW_MEM8_S3(mBoot, NB_MCH_BASE_ADDRESS | wReg, 0, Rst)
#define RESET_MMIO8_MCH_S3(mBoot, wReg, Rst) \
                         RW_MEM8_S3(mBoot, NB_MCH_BASE_ADDRESS | wReg, 0, Rst)
#define RW_MEM8_MCH_S3(mBoot, wReg, Set, Rst) \
                         RW_MEM8_S3(mBoot, NB_MCH_BASE_ADDRESS|wReg, Set, Rst)
#define RW_MMIO8_MCH_S3(mBoot, wReg, Set, Rst) \
                         RW_MEM8_S3(mBoot, NB_MCH_BASE_ADDRESS|wReg, Set, Rst)
#define WRITE_MEM16_MCH_S3(mBoot, wReg, wVal) \
                         WRITE_MEM16_S3(mBoot, NB_MCH_BASE_ADDRESS|wReg, wVal)
#define WRITE_MMIO16_MCH_S3(mBoot, wReg, wVal) \
                         WRITE_MEM16_S3(mBoot, NB_MCH_BASE_ADDRESS|wReg, wVal)
#define SET_MEM16_MCH_S3(mBoot, wReg, Set) \
                         RW_MEM16_S3(mBoot, NB_MCH_BASE_ADDRESS|wReg, Set, 0)
#define SET_MMIO16_MCH_S3(mBoot, wReg, Set) \
                         RW_MEM16_S3(mBoot, NB_MCH_BASE_ADDRESS|wReg, Set, 0)
#define RESET_MEM16_MCH_S3(mBoot, wReg, Rst) \
                         RW_MEM16_S3(mBoot, NB_MCH_BASE_ADDRESS | wReg, 0,Rst)
#define RESET_MMIO16_MCH_S3(mBoot, wReg, Rst) \
                         RW_MEM16_S3(mBoot, NB_MCH_BASE_ADDRESS | wReg, 0,Rst)
#define RW_MEM16_MCH_S3(mBoot, wReg, Set, Rst) \
                         RW_MEM16_S3(mBoot, NB_MCH_BASE_ADDRESS|wReg, Set,Rst)
#define RW_MMIO16_MCH_S3(mBoot, wReg, Set, Rst) \
                         RW_MEM16_S3(mBoot, NB_MCH_BASE_ADDRESS|wReg, Set,Rst)
#define WRITE_MEM32_MCH_S3(mBoot, wReg, dVal) \
                         WRITE_MEM32_S3(mBoot, NB_MCH_BASE_ADDRESS|wReg, dVal)
#define WRITE_MMIO32_MCH_S3(mBoot, wReg, dVal) \
                         WRITE_MEM32_S3(mBoot, NB_MCH_BASE_ADDRESS|wReg, dVal)
#define SET_MEM32_MCH_S3(mBoot, wReg, Set) \
                         RW_MEM32_S3(mBoot, NB_MCH_BASE_ADDRESS|wReg, Set, 0)
#define SET_MMIO32_MCH_S3(mBoot, wReg, Set) \
                         RW_MEM32_S3(mBoot, NB_MCH_BASE_ADDRESS|wReg, Set, 0)
#define RESET_MEM32_MCH_S3(mBoot, wReg, Rst) \
                         RW_MEM32_S3(mBoot, NB_MCH_BASE_ADDRESS|wReg, 0, Rst)
#define RESET_MMIO32_MCH_S3(mBoot, wReg, Rst) \
                         RW_MEM32_S3(mBoot, NB_MCH_BASE_ADDRESS|wReg, 0, Rst)
#define RW_MEM32_MCH_S3(mBoot, wReg, Set, Rst) \
                         RW_MEM32_S3(mBoot, NB_MCH_BASE_ADDRESS|wReg, Set,Rst)
#define RW_MMIO32_MCH_S3(mBoot, wReg, Set, Rst) \
                         RW_MEM32_S3(mBoot, NB_MCH_BASE_ADDRESS|wReg, Set,Rst)

//----------------------------------------------------------------------------

#define WRITE_MEM8_DMI_S3(mBoot, wReg, bVal) \
                         WRITE_MEM8_S3(mBoot, NB_DMI_BASE_ADDRESS | wReg,bVal)
#define WRITE_MMIO8_DMI_S3(mBoot, wReg, bVal) \
                         WRITE_MEM8_S3(mBoot, NB_DMI_BASE_ADDRESS | wReg,bVal)
#define SET_MEM8_DMI_S3(mBoot, wReg, Set) \
                         RW_MEM8_S3(mBoot, NB_DMI_BASE_ADDRESS | wReg, Set, 0)
#define SET_MMIO8_DMI_S3(mBoot, wReg, Set) \
                         RW_MEM8_S3(mBoot, NB_DMI_BASE_ADDRESS | wReg, Set, 0)
#define RESET_MEM8_DMI_S3(mBoot, wReg, Rst) \
                         RW_MEM8_S3(mBoot, NB_DMI_BASE_ADDRESS | wReg, 0, Rst)
#define RESET_MMIO8_DMI_S3(mBoot, wReg, Rst) \
                         RW_MEM8_S3(mBoot, NB_DMI_BASE_ADDRESS | wReg, 0, Rst)
#define RW_MEM8_DMI_S3(mBoot, wReg, Set, Rst) \
                         RW_MEM8_S3(mBoot, NB_DMI_BASE_ADDRESS|wReg, Set, Rst)
#define RW_MMIO8_DMI_S3(mBoot, wReg, Set, Rst) \
                         RW_MEM8_S3(mBoot, NB_DMI_BASE_ADDRESS|wReg, Set, Rst)
#define WRITE_MEM16_DMI_S3(mBoot, wReg, wVal) \
                         WRITE_MEM16_S3(mBoot, NB_DMI_BASE_ADDRESS|wReg, wVal)
#define WRITE_MMIO16_DMI_S3(mBoot, wReg, wVal) \
                         WRITE_MEM16_S3(mBoot, NB_DMI_BASE_ADDRESS|wReg, wVal)
#define SET_MEM16_DMI_S3(mBoot, wReg, Set) \
                         RW_MEM16_S3(mBoot, NB_DMI_BASE_ADDRESS|wReg, Set, 0)
#define SET_MMIO16_DMI_S3(mBoot, wReg, Set) \
                         RW_MEM16_S3(mBoot, NB_DMI_BASE_ADDRESS|wReg, Set, 0)
#define RESET_MEM16_DMI_S3(mBoot, wReg, Rst) \
                         RW_MEM16_S3(mBoot, NB_DMI_BASE_ADDRESS | wReg, 0,Rst)
#define RESET_MMIO16_DMI_S3(mBoot, wReg, Rst) \
                         RW_MEM16_S3(mBoot, NB_DMI_BASE_ADDRESS | wReg, 0,Rst)
#define RW_MEM16_DMI_S3(mBoot, wReg, Set, Rst) \
                         RW_MEM16_S3(mBoot, NB_DMI_BASE_ADDRESS|wReg, Set,Rst)
#define RW_MMIO16_DMI_S3(mBoot, wReg, Set, Rst) \
                         RW_MEM16_S3(mBoot, NB_DMI_BASE_ADDRESS|wReg, Set,Rst)
#define WRITE_MEM32_DMI_S3(mBoot, wReg, dVal) \
                         WRITE_MEM32_S3(mBoot, NB_DMI_BASE_ADDRESS|wReg, dVal)
#define WRITE_MMIO32_DMI_S3(mBoot, wReg, dVal) \
                         WRITE_MEM32_S3(mBoot, NB_DMI_BASE_ADDRESS|wReg, dVal)
#define SET_MEM32_DMI_S3(mBoot, wReg, Set) \
                         RW_MEM32_S3(mBoot, NB_DMI_BASE_ADDRESS|wReg, Set, 0)
#define SET_MMIO32_DMI_S3(mBoot, wReg, Set) \
                         RW_MEM32_S3(mBoot, NB_DMI_BASE_ADDRESS|wReg, Set, 0)
#define RESET_MEM32_DMI_S3(mBoot, wReg, Rst) \
                         RW_MEM32_S3(mBoot, NB_DMI_BASE_ADDRESS|wReg, 0, Rst)
#define RESET_MMIO32_DMI_S3(mBoot, wReg, Rst) \
                         RW_MEM32_S3(mBoot, NB_DMI_BASE_ADDRESS|wReg, 0, Rst)
#define RW_MEM32_DMI_S3(mBoot, wReg, Set, Rst) \
                         RW_MEM32_S3(mBoot, NB_DMI_BASE_ADDRESS|wReg, Set,Rst)
#define RW_MMIO32_DMI_S3(mBoot, wReg, Set, Rst) \
                         RW_MEM32_S3(mBoot, NB_DMI_BASE_ADDRESS|wReg, Set,Rst)

//----------------------------------------------------------------------------
// Chipset I/O Macros, Porting Required if needed.
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

//To Exclude AMI Native Root Bridge Driver HOOKS from CSP LIB
#if AMI_ROOT_BRIDGE_SUPPORT == 1

//----------------------------------------------------------------------------
//Function Prototypes for PciRootBridgeIo
//----------------------------------------------------------------------------

extern DXE_SERVICES     *gDxeSvcTbl;

EFI_STATUS HbResAllocNotifyPhase (
    IN EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL     *This,
    IN EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PHASE        Phase
);

EFI_STATUS HbResAllocGetNextRootBridge (
    IN EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL     *This,
    IN OUT EFI_HANDLE                                       *RootBridgeHandle
);

EFI_STATUS HbResAllocGetAllocAttributes (
    IN EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL     *This,
    IN EFI_HANDLE                                           RootBridgeHandle,
    OUT UINT64                                              *Attributes
);

EFI_STATUS HbResAllocStartBusEnumeration (
    IN EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL     *This,
    IN EFI_HANDLE                                           RootBridgeHandle,
    OUT VOID                                                **Configuration
);

EFI_STATUS HbResAllocSetBusNumbers (
    IN EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL     *This,
    IN EFI_HANDLE                                           RootBridgeHandle,
    IN VOID                                                 *Configuration
);

EFI_STATUS HbResAllocSubmitResources (
    IN EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL     *This,
    IN EFI_HANDLE                                           RootBridgeHandle,
    IN VOID                                                 *Configuration
);

EFI_STATUS HbResAllocGetProposedResources (
    IN EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL     *This,
    IN EFI_HANDLE                                           RootBridgeHandle,
    OUT VOID                                                **Configuration
);

EFI_STATUS HbResAllocPreprocessController (
    IN EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL     *This,
    IN EFI_HANDLE                                           RootBridgeHandle,
    IN EFI_PCI_CONFIGURATION_ADDRESS                        PciAddress,
    IN EFI_PCI_CONTROLLER_RESOURCE_ALLOCATION_PHASE         Phase
);

EFI_STATUS HbNotifyCspBeforeEnumeration (
    EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL    *ResAllocProtocol,
    EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL                     **RbIoProtocolBuffer,
    UINTN                                               RbCount
);

EFI_STATUS HbNotifyCspBeginBusAllocation (
    EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL    *ResAllocProtocol,
    EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL                     **RbIoProtocolBuffer,
    UINTN                                               RbCount
);

EFI_STATUS HbNotifyCspEndBusAllocation (
    EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL    *ResAllocProtocol,
    EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL                     **RbIoProtocolBuffer,
    UINTN                                               RbCount
);

EFI_STATUS HbNotifyCspBeginResourceAllocation (
    EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL    *ResAllocProtocol,
    EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL                     **RbIoProtocolBuffer,
    UINTN                                               RbCount
);

EFI_STATUS HbNotifyCspAllocateResources (
    EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL    *ResAllocProtocol,
    EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL                     **RbIoProtocolBuffer,
    UINTN                                               RbCount
);

EFI_STATUS HbNotifyCspSetResources (
    EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL    *ResAllocProtocol,
    EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL                     **RbIoProtocolBuffer,
    UINTN                                               RbCount
);

EFI_STATUS HbNotifyCspEndResourceAllocation (
    EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL    *ResAllocProtocol,
    EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL                     **RbIoProtocolBuffer,
    UINTN                                               RbCount
);

EFI_STATUS HbCspStartBusEnumeration (
    PCI_HOST_BRG_DATA       *HostBrgData,
    PCI_ROOT_BRG_DATA       *RootBrgData,
    UINTN RootBrgIndex
);

EFI_STATUS HbCspSetBusNnumbers (
    PCI_HOST_BRG_DATA       *HostBrgData,
    PCI_ROOT_BRG_DATA       *RootBrgData,
    UINTN RootBrgIndex
);

EFI_STATUS HbCspSubmitResources (
    PCI_HOST_BRG_DATA       *HostBrgData,
    PCI_ROOT_BRG_DATA       *RootBrgData,
    UINTN RootBrgIndex
);

EFI_STATUS HbCspAdjustMemoryMmioOverlap (
    PCI_HOST_BRG_DATA       *HostBrgData,
    PCI_ROOT_BRG_DATA       *RootBrgData,
    UINTN RootBrgIndex
);

EFI_STATUS HbCspBasicChipsetInit (
    PCI_HOST_BRG_DATA       *HostBrg0
);

UINTN HbCspGetPciSegment (
    UINTN                   HostBridgeNumber,
    UINTN                   RootBridgeNumber
);

EFI_STATUS HbCspPreprocessController (
    PCI_HOST_BRG_DATA                               *HostBrgData,
    PCI_ROOT_BRG_DATA                               *RootBrgData, 
    UINTN                                           RootBrgNumber,
    EFI_PCI_CONFIGURATION_ADDRESS                   PciAddress,
    EFI_PCI_CONTROLLER_RESOURCE_ALLOCATION_PHASE    Phase
);

EFI_STATUS RbCspIoPciMap (
    IN PCI_ROOT_BRG_DATA                            *RbData,
    IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_OPERATION    Operation,
    IN EFI_PHYSICAL_ADDRESS                         HostAddress,
    IN OUT UINTN                                    *NumberOfBytes,
    OUT EFI_PHYSICAL_ADDRESS                        *DeviceAddress,
    OUT VOID                                        **Mapping
);

EFI_STATUS RbCspIoPciUnmap (
    IN PCI_ROOT_BRG_DATA                            *RbData,
    IN PCI_ROOT_BRIDGE_MAPPING                      *Mapping
);

EFI_STATUS RbCspIoPciAttributes( 
    IN PCI_ROOT_BRG_DATA                            *RbData,
    IN UINT64                                       Attributes,
    IN OUT UINT64                                   *ResourceBase OPTIONAL,
    IN OUT UINT64                                   *ResourceLength OPTIONAL
);

EFI_STATUS RootBridgeIoPciRW (
    IN PCI_ROOT_BRG_DATA                        *RbData,
    IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH    Width,
    IN UINT64                                   Address,
    IN UINTN                                    Count,
    IN OUT VOID                                 *Buffer,
    IN BOOLEAN                                  Write
);

EFI_STATUS RbCspIoPciUnmap (
    IN  PCI_ROOT_BRG_DATA                           *RbData, 
    OUT PCI_ROOT_BRIDGE_MAPPING                     *Mapping
);

EFI_STATUS RbCspIoPciMap (
    IN PCI_ROOT_BRG_DATA                            *RbData,
    IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_OPERATION    Operation,
    IN EFI_PHYSICAL_ADDRESS                         HostAddress,
    IN OUT UINTN                                    *NumberOfBytes,
    OUT EFI_PHYSICAL_ADDRESS                        *DeviceAddress,
    OUT VOID                                        **Mapping
);

//--------------------------------------
//#if AMI_ROOT_BRIDGE_SUPPORT == 1
#endif 

#ifdef __cplusplus
}
#endif
#endif

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
