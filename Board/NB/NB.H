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
// $Header: /Alaska/BIN/Chipset/Intel/NorthBridge/Haswell/Intel SystemAgent NB Board/NB.H 3     10/14/12 12:42a Jeffch $
//
// $Revision: 3 $
//
// $Date: 10/14/12 12:42a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Chipset/Intel/NorthBridge/Haswell/Intel SystemAgent NB Board/NB.H $
// 
// 3     10/14/12 12:42a Jeffch
// [TAG]          None
// [Severity]     Important
// [Description]  Update by XTU4.0.
// [Files]        NB.h, GetSetupData.c, NbSetupData.h
// [TAG]          None
// [Severity]     Important
// [Description]  Follow Update by Mahobay.
// [Files]        NB.sdl, NB.mak.c; NBDXEBoard.c
// 
// 2     9/26/12 9:28a Yurenlai
// [TAG]           EIP101495
// [Category]      Improvement
// [Severity]      Important
// [Description]   Initialize SSID of B0:D3:F0 and B0:D2:F0/F1.
// [Files]         NB.h, NB.sdl, NBPEI.c
// 
// 1     2/08/12 4:32a Yurenlai
// Intel Haswell/NB eChipset initially releases.
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:        NB.h
//
// Description: North Bridge header file, define all the North Bridge
//              specific equates and structures in this file.
//
//<AMI_FHDR_END>
//*************************************************************************

#ifndef  _NB_H__   // To Avoid this header get compiled twice
#define  _NB_H__

#include <Token.h>
#include "ReferenceCode\Chipset\SystemAgent\Include\SaRegs.h"

// DO NOT REMOVE THE DEFINITION OF THIS STRUCTURE. THIS IS USED BY CSM ALSO
typedef struct ROOT_BRIDGE_MAPPING_TABLE {
    UINT32  rbUID;
    UINT8   rbDevFunc;
} ROOT_BRIDGE_MAPPING_ENTRY;

#define NB_PCI_CFG_ADDRESS(bus, dev, func, reg) \
            (UINT64) ((((UINT8)(bus) << 24) + ((UINT8)(dev) << 16) + \
            ((UINT8)(func) << 8) + ((UINT8)(reg))) & 0xffffffff)

#ifdef PCIEX_BASE_ADDRESS 
#define NB_PCIE_CFG_ADDRESS(bus, dev, func, reg) \
            ((UINTN)(PCIEX_BASE_ADDRESS + ((UINT8)(bus) << 20) + \
            ((UINT8)(dev) << 15) + ((UINT8)(func) << 12) + (reg)))
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

// For systems with config mechanism 1
#define NB_PCICFG_SPACE_INDEX_REG       0xcf8
#define NB_PCICFG_SPACE_DATA_REG        0xcfc

typedef struct {
    UINT16  MmioReg;
    UINT32  bAndMask;
    UINT32  bOrMask;
} AMI_NB_MMIO_INIT_TABLE_STRUCT;

typedef struct  {
    UINT64      PciAddr;
    UINT32      Sid;
} NB_PCI_SUBID_STRUCT;

#define GET_PRIMARY_VGA_PCI_INFO_GUID {0x2fcaa4e9, 0xdc14, 0x4644, 0xbe, 0x51\
                                       ,0xd2, 0x33, 0xd8, 0x20, 0xed, 0x4}

#define GET_PRIMARY_VGA_PCI_INFO_VARIABLE L"GetPriVideoPciInfo"

#define NB_ASL_BUFFER_PTR_GUID { 0x30bc0b91, 0x8106, 0x4f6b, 0xb8, 0x5d, \
                                 0x22, 0x47, 0x35, 0xd, 0x95, 0x38 }

#define NB_ASL_BUFFER_PTR_VARIABLE L"NbAslBufferPtrVar"

//-----------------------------------------------------------------------
// NB : MRC Details
//-----------------------------------------------------------------------

//#define EFI_NB_MRC_INFO_GUID \
//    {0xd7bd52b0, 0xb2dc, 0x4f08, 0xb4, 0x67, 0xde, 0x50, 0xd7, 0x28, 0xf6, 0xbd}

//#define ALING_1GB_PCI_MMIO_MASK 0xC0000000
//#define ALING_64M_PCI_MMIO_MASK 0xF0000000

//-----------------------------------------------------------------------
// NB : Platform Details
//-----------------------------------------------------------------------

typedef union {
    UINT32 Data;
    struct 
    {
        UINT32 CPUType:4;
        UINT32 ExtCPUType:4;
        UINT32 Reserved:24;
    } Fields;
} NB_PLATFORM_INFO;


typedef struct {
    UINT8   NbAslByte0;
    UINT8   NbAslByte1;
    UINT8   NbAslByte2;
    UINT8   NbAslByte3;
    UINT8   NbAslByte4;
    UINT8   NbAslByte5;
    UINT8   NbAslByte6;
    UINT8   NbAslByte7;
    UINT8   NbAslByte8;
    UINT8   NbAslByte9;
    UINT8   NbAslByte10;
    UINT8   NbAslByte11;
    UINT8   NbAslByte12;
    UINT8   NbAslByte13;
    UINT8   NbAslByte14;
    UINT8   NbAslByte15;
} NB_ASL_BUFFER;

//----------------------------------------------------------------------------
// INTEL Ivy Bridge Processor Host Bridge PCI Bus Number Equates
//----------------------------------------------------------------------------
#define NB_BUS                  0x00    // North Bridge Bus Number
#define PCIEBRN_BUS             0x00    // North Bridge PCI Express Bridge 
                                        // Bus Number
#define IGD_BUS                 0x00    // Integrated Graphics Device 
                                        // Device Number
#define SA_HDA_BUS              0x00    // 
//----------------------------------------------------------------------------
// INTEL Ivy Bridge Processor Host Bridge Device Number Equates
//----------------------------------------------------------------------------
#define NB_DEV                  0x00    // North Bridge Device Number
#define PCIEBRN_DEV             0x01    // North Bridge PCI Express Bridge
                                        // Device Number
#define IGD_DEV                 0x02    // Integrated Graphics Device 
                                        // Device Number
#define SA_HDA_DEV              0x03    //
                                        //
#define PCIEBRN_DEV6            0x06    // North Bridge PCI Express Bridge
                                        // Device Number
//----------------------------------------------------------------------------
// INTEL Ivy Bridge Processor Host Bridge Function Number Equates
//----------------------------------------------------------------------------
#define NB_FUN                  0x00    // North Bridge Function Number
#define PCIEBRN_FUN             0x00    // North Bridge PCI Express Bridge 
                                        // Function Number
#define PCIEBRN_FUN1            0x01   // North Bridge PCI Express Bridge  
                                        // Function Number
#define PCIEBRN_FUN2            0x02   // North Bridge PCI Express Bridge 
                                        // Function Number
#define IGD_FUN                 0x00    // Integrated Graphics Device 
                                        // Function Number 0
#define IGD_FUN1                0x01    // Integrated Graphics Device 
                                        // Function Number 1
#define SA_HDA_FUN              0x0     // 
                                        // 
//----------------------------------------------------------------------------
// INTEL Ivy Bridge Processor - PCI Bus/Device/Function/Register Number Macros
//----------------------------------------------------------------------------
#define NB_REG(Reg)             NB_PCI_CFG_ADDRESS(NB_BUS, NB_DEV, \
                                                   NB_FUN, Reg)
#define PCIEBRN_REG(Reg)        NB_PCI_CFG_ADDRESS(PCIEBRN_BUS, PCIEBRN_DEV, \
                                                   PCIEBRN_FUN, Reg)
#define PCIEBRNx16_REG(Reg)     NB_PCI_CFG_ADDRESS(PCIEBRN_BUS, PCIEBRN_DEV, \
                                                   PCIEBRN_FUN, Reg)
#define PCIEBRNx8_REG(Reg)      NB_PCI_CFG_ADDRESS(PCIEBRN_BUS, PCIEBRN_DEV, \
                                                   PCIEBRN_FUN1, Reg)
#define PCIEBRNx4_REG(Reg)      NB_PCI_CFG_ADDRESS(PCIEBRN_BUS, PCIEBRN_DEV, \
                                                   PCIEBRN_FUN2, Reg)
#define PCIED6BRN_REG(Reg)      NB_PCI_CFG_ADDRESS(PCIEBRN_BUS, PCIEBRN_DEV6, \
                                                   PCIEBRN_FUN, Reg)
#define IGD_REG(Reg)            NB_PCI_CFG_ADDRESS(IGD_BUS, IGD_DEV, \
                                                   IGD_FUN, Reg)
#define IGD1_REG(Reg)           NB_PCI_CFG_ADDRESS(IGD_BUS, IGD_DEV, \
                                                   IGD_FUN1, Reg)
#define SA_HDA_REG(Reg)         NB_PCI_CFG_ADDRESS(SA_HDA_BUS, SA_HDA_DEV, \
                                                   SA_HDA_FUN, Reg)

//----------------------------------------------------------------------------
// INTEL Ivy Bridge Processor - PCI Bus/Device/Function Number Macros
//----------------------------------------------------------------------------
#define NB_BUS_DEV_FUN             NB_REG(0)
#define NB_IGD_BUS_DEV_FUN         IGD_REG(0)
#define NB_IGD_BUS_DEV_FUN1        IGD1_REG(0)
#define NB_HDA_BUS_DEV_FUN         SA_HDA_REG(0)
#define NB_PCIEBRN_BUS_DEV_FUN     PCIEBRNx16_REG(0)
#define NB_PCIEBRNx16_BUS_DEV_FUN  PCIEBRNx16_REG(0)
#define NB_PCIEBRNx8_BUS_DEV_FUN   PCIEBRNx8_REG(0)
#define NB_PCIEBRNx4_BUS_DEV_FUN   PCIEBRNx4_REG(0)
#define NB_PCIEBRN_BUS_DEV6_FUN    PCIED6BRN_REG(0)
//----------------------------------------------------------------------------
// INTEL Ivy Bridge Processor - PCI Device/Vendor IDs Equates
//----------------------------------------------------------------------------
#define NB_VENID                0x8086  // North Bridge Vendor ID
#define NB_DEVID                0x0002  // North Bridge Device ID
#define PCIEBRN_VENID           0x8086  // North Bridge PCI Express Bridge
                                        // Vendor ID
#define PCIEBRN_DEVID           0x0045  // North Bridge PCI Express Bridge
                                        // Device ID
#define IGD_VENID               0x8086  // Integrated Graphics Device
                                        // Vendor ID 
#define IGD_DT_DEVID            0x0102  // Integrated Graphics Device
                                        // Device ID 
#define IGD_MB_DEVID            0x0106  // Integrated Graphics Device
                                        // Device ID 

//----------------------------------------------------------------------------
// INTEL Ivy Bridge Processor - DRAM Controller Register Equates (D0:F0)
//----------------------------------------------------------------------------
#define NB_REG_VID              0x00    // Vendor ID Reg.
#define NB_REG_DID              0x02    // Device ID Reg.
#define NB_REG_SVID             0x2c    // Subsystem Vendor ID Reg.
//#define NB_REG_DEVEN            0x54    // Device Enable Reg.
//#define NB_REG_TSEGMB           0xac    // TSEG Memory Base Reg.
//#define NB_REG_LAC              0x97    // Legacy Access Control Reg.
//#define NB_REG_CAPID0           0xe0    // Capability Identifier 0 Reg.
//#define NB_REG_CAPID1           0xe4    // Capability Identifier 1 Reg.

//----------------------------------------------------------------------------
// INTEL Ivy Bridge Processor - MCH BAR Memory Mapped IO Register Equates
//----------------------------------------------------------------------------
#define MCH_MMIO_C0REFRCTRL     0x0269  // Channel 0 DRAM Refersh Control
#define MCH_MMIO_C1REFRCTRL     0x0669  // Channel 1 DRAM Refersh Control

//----------------------------------------------------------------------------
// INTEL Ivy Bridge Processor -  PCI-Express Bridge Register Equates (D1:F0)
//----------------------------------------------------------------------------
#define PCIEBRN_REG_VID         0x00    // Vendor ID Reg.
#define PCIEBRN_REG_SBUSN       0x19    // Secondary Bus Number Reg. 
#define PCIEBRN_REG_SUBUSN      0x1a    // Subordinate Bus Number Reg.
#define PCIEBRN_REG_SVID        0x8c    // Vendor ID Reg.

//----------------------------------------------------------------------------
// INTEL Ivy Bridge Processor - Integrated Graphics Device Register Equates (D2:F0)
//----------------------------------------------------------------------------
#define IGD_REG_VID             0x00    // Vendor ID Reg.
#define IGD_REG_SVID            0x2c    // Subsystem Vendor ID Reg.

//----------------------------------------------------------------------------
// INTEL Ivy Bridge Processor - System Address Decoder Register Equates (D0:F1)
//----------------------------------------------------------------------------

#define MC_REG_PAM0            0x80    // Programmable Attribute Map 0 Reg.
#define MC_REG_PAM1            0x81    // Programmable Attribute Map 1 Reg.
#define MC_REG_PAM2            0x82    // Programmable Attribute Map 2 Reg.
#define MC_REG_PAM3            0x83    // Programmable Attribute Map 3 Reg.
#define MC_REG_PAM4            0x84    // Programmable Attribute Map 4 Reg.
#define MC_REG_PAM5            0x85    // Programmable Attribute Map 5 Reg.
#define MC_REG_PAM6            0x86    // Programmable Attribute Map 6 Reg.
#define MC_REG_SMRAM           0x88

//----------------------------------------------------------------------------
// INTEL Ivy Bridge Processor - MAX TOLUD Type
//----------------------------------------------------------------------------
#define NB_MAX_TOLUD_DYNAMIC    0
#define NB_MAX_TOLUD_0_5G       1
#define NB_MAX_TOLUD_0_75G      2
#define NB_MAX_TOLUD_1G         3
#define NB_MAX_TOLUD_1_25G      4
#define NB_MAX_TOLUD_1_5G       5
#define NB_MAX_TOLUD_1_75G      6
#define NB_MAX_TOLUD_2G         7
#define NB_MAX_TOLUD_2_25G      8
#define NB_MAX_TOLUD_2_5G       9
#define NB_MAX_TOLUD_2_75G      10
#define NB_MAX_TOLUD_3G         11
#define NB_MAX_TOLUD_3_25G      12
#define NB_MAX_TOLUD_3_5G       13
#define NB_MAX_TOLUD_3_75G      14
//----------------------------------------------------------------------------
// INTEL Ivy Bridge GTTMMADR
//----------------------------------------------------------------------------
#define GTT_MEM_ALIGN     22
#define GTTMMADR_SIZE_4MB 0x400000

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
