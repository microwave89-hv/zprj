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
// $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Board/SB.H 11    5/16/14 6:19a Barretlin $
//
// $Revision: 11 $
//
// $Date: 5/16/14 6:19a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Board/SB.H $
// 
// 11    5/16/14 6:19a Barretlin
// [TAG]  		EIP167087
// [Category]  	Improvement
// [Description]  	BIOS security improvement on Haswell CRB project
// [Files]  		SBGeneric.c SBDxe.c SBCspLib.h Sb.sdl Sb.sd Sb.h
// 
// 10    10/28/13 2:46a Barretlin
// [TAG]  		EIP N/A
// [Category]  	Improvement
// [Description]  	add programming serial IO device's SSID
// [Files]  		SB.sdl SB.H
// 
// 9     5/10/13 1:40a Scottyang
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Remover ULT_SUPPORT token at SB.h.
// [Files]  		SB.h
// 
// 8     4/24/13 2:14a Scottyang
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Porting GPI interrupt by LPT-LP EDS 1.5.
// [Files]  		SB.sdl, SB.H, SBPPI.h, SBPEI.c
// 
// 7     4/16/13 11:24p Wesleychen
// [TAG]       EIP120787
// [Category]  Bug Fix
// [Severity]  Normal
// [Symptom]   System might halts at CKP 0x55 with some specific
//             combinations. (Ex: i7-4770 / 4570 + Hynix 4G / 2G)
// [RootCause] All Reference codes are validated with Traditional and
//             ULT build flags enabled.
//             Having one of the flags disable may lead code execution
//             that is not validated by Intel and may cause system
//             instability. 
// [Solution]  Make "TRAD_FLAG" and "ULT_FLAG" are coexist.
// [Files]     MemoryInit.sdl; SB.h
// 
// 6     3/22/13 7:00a Scottyang
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Wireless LAN PHY use SLP_WLAN# pin
// [Files]  		SB.sdl, SBDxe.c, SB.H
// 
// 5     9/26/12 3:47a Victortu
// [TAG]           None
// [Category]      Improvement
// [Description]   Update for PCH LP GPIO compatible.
// [Files]         SB.sdl, SB.H, AcpiModeEnable.c, AcpiModeEnable.sdl,
// SBDxe.c, SBGeneric.c, SBPEI.c, SBSMI.c, SleepSmi.c,
// SmiHandlerPorting.c, SmiHandlerPorting2.c
// 
// 4     9/12/12 5:09a Victortu
// [TAG]           None
// [Category]      Improvement
// [Description]   Support OEM update VSCC table.
// [Files]         SB.H, SB.mak, SB.sdl, SBDXE.c
// 
// [TAG]           None
// [Category]      Improvement
// [Description]   Modify for ULT GPIO changed by PCH LPT-LP EDS 1.0.
// [Files]         SB.H, SB.sdl, AcpiModeEnable.c, AcpiModeEnable.sdl,
// SBPEI.c
// 
// 3     7/27/12 6:03a Victortu
// Update to support ULT Platform.
// 
// 2     6/13/12 11:33p Victortu
// [TAG]           None
// [Category]      Improvement
// [Description]   Implement Warm Boot function for Secure Flash feature.
// [Files]         SB.H, SB.mak, SB.sdl, SBDxe.c, SBGeneric.c, SBPEI.c,
// SBSMI.c
// 
// 1     2/08/12 8:22a Yurenlai
// Intel Lynx Point/SB eChipset initially releases.
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:        SB.h
//
// Description: South Bridge header file, define all the South Bridge
//              specific equates and structures in this file.
//
//<AMI_FHDR_END>
//*************************************************************************

#ifndef  _SB_H                  // To Avoid this header get compiled twice
#define  _SB_H

#include <Token.h>

#define SB_PCI_CFG_ADDRESS(bus, dev, func, reg) \
            (UINT64) ((((UINT8)(bus) << 24) + ((UINT8)(dev) << 16) + \
            ((UINT8)(func) << 8) + ((UINT8)(reg))) & 0xffffffff)

#ifdef PCIEX_BASE_ADDRESS 
#define SB_PCIE_CFG_ADDRESS(bus, dev, func, reg) \
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

// 8259 Hardware definitions

#define LEGACY_MODE_BASE_VECTOR_MASTER                    0x08
#define LEGACY_MODE_BASE_VECTOR_SLAVE                     0x10
#define LEGACY_8259_CONTROL_REGISTER_MASTER               0x20
#define LEGACY_8259_MASK_REGISTER_MASTER                  0x21
#define LEGACY_8259_CONTROL_REGISTER_SLAVE                0xa0
#define LEGACY_8259_MASK_REGISTER_SLAVE                   0xa1
#define LEGACY_8259_EDGE_LEVEL_TRIGGERED_REGISTER_MASTER  0x4d0
#define LEGACY_8259_EDGE_LEVEL_TRIGGERED_REGISTER_SLAVE   0x4d1
#define LEGACY_8259_EOI                                   0x20

// 8254 Timer definitions
#define LEGACY_TIMER_0_COUNT    0x40
#define LEGACY_TIMER_1_COUNT    0x41
#define LEGACY_TIMER_CTRL       0x43

#define SLP_S5                  7       // Porting Required.

#define NUM_BITS_IN_ACPI_TIMER  24      // Programmed to 24 not 32
// This is the maximum possible bits in the timer.
// Currently this is 32 according to the spec.
#define MAX_ACPI_TIMER_BITS     32

typedef struct DMA_INIT_tag{
  UINT8  PortAddr;
  UINT8  Value;
} DMA_INIT;

#define SB_ASL_BUFFER_PTR_GUID { 0x1f33c25, 0x764d, 0x43ea, 0xae, 0xea, 0x6b, \
                             0x5a, 0x41, 0xf3, 0xf3, 0xe8 }

#define SB_ASL_BUFFER_PTR_VARIABLE L"SbAslBufferPtrVar"

typedef struct {
    UINT8   SbAslByte0;
    UINT8   SbAslByte1;
    UINT8   SbAslByte2;
    UINT8   SbAslByte3;
    UINT8   SbAslByte4;
    UINT8   SbAslByte5;
    UINT8   SbAslByte6;
    UINT8   SbAslByte7;
    UINT8   SbAslByte8;
    UINT8   SbAslByte9;
    UINT8   SbAslByte10;
    UINT8   SbAslByte11;
    UINT8   SbAslByte12;
    UINT8   SbAslByte13;
    UINT8   SbAslByte14;
    UINT8   SbAslByte15;
} SB_ASL_BUFFER;

#define SB_WARM_RESET_GUID {0xb8cafa84, 0x4593, 0x4aa9, 0xae, 0xf7, 0x8e, \
                            0x68, 0x6e, 0xb0, 0x73, 0x20}

#define SB_WARM_RESET_VARIABLE L"SbWarmResetVar"

#define SB_WARM_RESET_TAG 'IsWR'

#define RESET_PORT        0x0CF9
#define CLEAR_RESET_BITS  0x0F9
#define COLD_RESET        0x02 // Set bit 1 for cold reset
#define RST_CPU           0x04 // Setting this bit triggers a reset of the CPU

typedef enum _SB_RESET_TYPE
{
    HardReset = 0,
    SoftReset,
    ShutDown,
    FullReset = 0x80,
    GlobalReset
} SB_RESET_TYPE;

//----------------------------------------------------------------------------
// INTEL PCH PCI Bus Number Equates
//----------------------------------------------------------------------------
#define SB_BUS                  0       // South Bridge Bus Number
#define LPC_BUS                 SB_BUS
#define SATA_BUS                0       // Serial ATA Controller Bus Number 1
#define SATA2_BUS               0       // Serial ATA Controller Bus Number 1
#define SMBUS_BUS               0       // SMBus Controller Bus Number
#define XHCI_BUS                0       // XHCI Controller 1 Bus Number
#define EHCI_BUS                0       // EHCI Controller 1 Bus Number
#define EHCI2_BUS               0       // EHCI Controller 2 Bus Number
#define THERMAL_BUS             0       // THERMAL Controller Bus Number
#define HDA_BUS                 0       // HD Audio Controller Bus Number
#define LAN_BUS                 0       // Ethernet GBE Controller Bus Num.
#define PCIBR_BUS               0       // South Bridge PCI Bus Bridge 
                                        // Bus Number
#define PCIEBRS_BUS             0       // South Bridge PCI Express Bridge 1
                                        // Bus Number
#define SBPCIE_BUS              PCIEBRS_BUS
#define PCIEBRS2_BUS            0       // South Bridge PCI Express Bridge 2
                                        // Bus Number
#define PCIEBRS3_BUS            0       // South Bridge PCI Express Bridge 3
                                        // Bus Number
#define PCIEBRS4_BUS            0       // South Bridge PCI Express Bridge 4
                                        // Bus Number
#define PCIEBRS5_BUS            0       // South Bridge PCI Express Bridge 5
                                        // Bus Number
#define PCIEBRS6_BUS            0       // South Bridge PCI Express Bridge 6
                                        // Bus Number
#define PCIEBRS7_BUS            0       // South Bridge PCI Express Bridge 7
                                        // Bus Number
#define PCIEBRS8_BUS            0       // South Bridge PCI Express Bridge 8
                                        // Bus Number
#define HECI_BUS                0       // ME HECI Controller 
                                        // Interface Bus Number
#ifndef HECI2_BUS
#define HECI2_BUS               0       // ME HECI 2 Controller 
                                        // Interface Bus Number
#endif

#define IDER_BUS                0       // ME IDER Controller
                                        // Interface Bus Number
#define KT_BUS                  0       // ME KT Controller
                                        // Interface Bus Number

#define SIO_DMA_BUS             0       // SIO DMA Controller
                                        // Interface Bus Number
#define SIO_I2C0_BUS            0       // SIO I2C 0 Controller
                                        // Interface Bus Number
#define SIO_I2C1_BUS            0       // SIO I2C 1 Controller
                                        // Interface Bus Number
#define SIO_GSPI0_BUS           0       // SIO GSPI 0 Controller
                                        // Interface Bus Number
#define SIO_GSPI1_BUS           0       // SIO GSPI 1 Controller
                                        // Interface Bus Number
#define SIO_UART0_BUS           0       // SIO UART 0 Controller
                                        // Interface Bus Number
#define SIO_UART1_BUS           0       // SIO UART 1 Controller
                                        // Interface Bus Number
#define SIO_SDIO_BUS            0       // SIO SDIO Controller
                                        // Interface Bus Number

//----------------------------------------------------------------------------
// INTEL PCH PCI Device Number Equates
//----------------------------------------------------------------------------
#define SB_DEV                  0x1f    // South Bridge Device Number
#define LPC_DEVICE              SB_DEV
#define SATA_DEV                SB_DEV  // Serial ATA Controller Device Num 1.
#define SATA2_DEV               SB_DEV  // Serial ATA Controller Device Num 1.
#define SMBUS_DEV               SB_DEV  // SMBus Controller Device Number.
#define XHCI_DEV                0x14    // XHCI Controller Device Number
#define EHCI_DEV                0x1d    // EHCI Controller 1 Device Number
#define EHCI2_DEV               0x1a    // EHCI Controller 2 Device Number
#define THERMAL_DEV             SB_DEV  // THERMAL Controller Device Number
#define LAN_DEV                 0x19    // Ethernet GBE Controller Device Num.
#define HDA_DEV                 0x1b    // HD Audio Controller Device Number
#define PCIBR_DEV               0x1e    // South Bridge PCI Bus Bridge 
                                        // Device Number
#define PCIEBRS_DEV             0x1c    // South Bridge PCI Express Bridge 1
                                        // Device Number
#define SBPCIE_DEV              PCIEBRS_DEV
#define PCIEBRS2_DEV            0x1c    // South Bridge PCI Express Bridge 2
                                        // Device Number
#define PCIEBRS3_DEV            0x1c    // South Bridge PCI Express Bridge 3
                                        // Device Number
#define PCIEBRS4_DEV            0x1c    // South Bridge PCI Express Bridge 4
                                        // Device Number
#define PCIEBRS5_DEV            0x1c    // South Bridge PCI Express Bridge 5
                                        // Device Number
#define PCIEBRS6_DEV            0x1c    // South Bridge PCI Express Bridge 6
                                        // Device Number
#define PCIEBRS7_DEV            0x1c    // South Bridge PCI Express Bridge 7
                                        // Device Number
#define PCIEBRS8_DEV            0x1c    // South Bridge PCI Express Bridge 8
                                        // Device Number
#define HECI_DEV                0x16    // ME HECI 2 Controller
                                        // Interface Device Number
#define ME_DEV                  HECI_DEV

#define HECI2_DEV               0x16    // ME HECI 2 Controller 
                                        // Interface Device Number
#define IDER_DEV                0x16    // ME IDER Controller
                                        // Interface Device Number
#define KT_DEV                  0x16    // ME KT Controller
                                        // Interface Device Number

#define SIO_DMA_DEV             0x15    // SIO DMA Controller
                                        // Interface Device Number
#define SIO_I2C0_DEV            0x15    // SIO I2C 0 Controller
                                        // Interface Device Number
#define SIO_I2C1_DEV            0x15    // SIO I2C 1 Controller
                                        // Interface Device Number
#define SIO_GSPI0_DEV           0x15    // SIO GSPI 0 Controller
                                        // Interface Device Number
#define SIO_GSPI1_DEV           0x15    // SIO GSPI 1 Controller
                                        // Interface Device Number
#define SIO_UART0_DEV           0x15    // SIO UART 0 Controller
                                        // Interface Device Number
#define SIO_UART1_DEV           0x15    // SIO UART 1 Controller
                                        // Interface Device Number
#define SIO_SDIO_DEV            0x17    // SIO SDIO Controller
                                        // Interface Device Number

//----------------------------------------------------------------------------
// INTEL PCH PCI Function Number Equates
//----------------------------------------------------------------------------
#define SB_FUN                  0x00    // South Bridge Function Number
#define LPC_FUNC                SB_FUN
#define SATA_FUN                0x02    // Serial ATA Controller Function Num.
#define SMBUS_FUN               0x03    // SMBus Controller Function Number.
#define SATA2_FUN               0x05    // Serial ATA Controller Function Num.
#define THERMAL_FUN             0x06    // THERMAL Controller Function Number
#define XHCI_FUN                0x00    // XHCI Controller Function Number
#define EHCI_FUN                0x00    // EHCI Controller 1 Function Number
#define EHCI2_FUN               0x00    // EHCI Controller 1 Function Number
#define HDA_FUN                 0x00    // HD Audio Controller Function Num.
#define LAN_FUN                 0x00    // Ethernet GBE Controller Function
                                        // Number
#define PCIBR_FUN               0x00    // South Bridge PCI Bus Bridge 
                                        // Function Number
#define PCIEBRS_FUN             0x00    // South Bridge PCI Express Bridge 1
                                        // Function Number
#define SBPCIE_FUNC_0           PCIEBRS_FUN
#define PCIEBRS2_FUN            0x01    // South Bridge PCI Express Bridge 2
                                        // Function Number
#define PCIEBRS3_FUN            0x02    // South Bridge PCI Express Bridge 3
                                        // Function Number
#define PCIEBRS4_FUN            0x03    // South Bridge PCI Express Bridge 4
                                        // Function Number
#define PCIEBRS5_FUN            0x04    // South Bridge PCI Express Bridge 5
                                        // Function Number
#define PCIEBRS6_FUN            0x05    // South Bridge PCI Express Bridge 6
                                        // Function Number
#define PCIEBRS7_FUN            0x06    // South Bridge PCI Express Bridge 7
                                        // Function Number
#define PCIEBRS8_FUN            0x07    // South Bridge PCI Express Bridge 8
                                        // Function Number
#define HECI_FUN                0x00    // ME HECI Controller
                                        // Interface Function Number
#define ME_FUNC0                HECI_FUN

#define HECI2_FUN               0x01    // ME HECI 2 Controller
                                        // Interface Function Number
#define ME_FUNC1                HECI2_FUN
#define IDER_FUN                0x02    // ME IDER Controller
                                        // Interface Function Number
#define KT_FUN                  0x03    // ME KT Controller
                                        // Interface Function Number

#define SIO_DMA_FUN             0x00    // SIO DMA Controller
                                        // Interface Function Number
#define SIO_I2C0_FUN            0x01    // SIO I2C 0 Controller
                                        // Interface Function Number
#define SIO_I2C1_FUN            0x02    // SIO I2C 1 Controller
                                        // Interface Function Number
#define SIO_GSPI0_FUN           0x03    // SIO GSPI 0 Controller
                                        // Interface Function Number
#define SIO_GSPI1_FUN           0x04    // SIO GSPI 1 Controller
                                        // Interface Function Number
#define SIO_UART0_FUN           0x05    // SIO UART 0 Controller
                                        // Interface Function Number
#define SIO_UART1_FUN           0x06    // SIO UART 1 Controller
                                        // Interface Device Number
#define SIO_SDIO_FUN            0x00    // SIO SDIO Controller
                                        // Interface Device Number

//----------------------------------------------------------------------------
// INTEL PCH PCI Bus/Device/Function/Register Number Macros
//----------------------------------------------------------------------------
#define SB_REG(Reg)             SB_PCI_CFG_ADDRESS(SB_BUS, SB_DEV, \
                                                   SB_FUN, Reg)
#define HECI_REG(Reg)           SB_PCI_CFG_ADDRESS(HECI_BUS, HECI_DEV, \
                                                   HECI_FUN, Reg)
#define HECI2_REG(Reg)          SB_PCI_CFG_ADDRESS(HECI2_BUS, HECI2_DEV, \
                                                   HECI2_FUN, Reg)
#define IDER_REG(Reg)           SB_PCI_CFG_ADDRESS(IDER_BUS, IDER_DEV, \
                                                   IDER_FUN, Reg)
#define KT_REG(Reg)             SB_PCI_CFG_ADDRESS(KT_BUS, KT_DEV, \
                                                   KT_FUN, Reg)
#define SB_REG(Reg)             SB_PCI_CFG_ADDRESS(SB_BUS, SB_DEV, \
                                                   SB_FUN, Reg)
#define SB_REG(Reg)             SB_PCI_CFG_ADDRESS(SB_BUS, SB_DEV, \
                                                   SB_FUN, Reg)
#define XHCI_REG(Reg)           SB_PCI_CFG_ADDRESS(XHCI_BUS, XHCI_DEV, \
                                                   XHCI_FUN, Reg)
#define EHCI_REG(Reg)           SB_PCI_CFG_ADDRESS(EHCI_BUS, EHCI_DEV, \
                                                   EHCI_FUN, Reg)
#define EHCI2_REG(Reg)          SB_PCI_CFG_ADDRESS(EHCI2_BUS, EHCI2_DEV, \
                                                   EHCI2_FUN, Reg)
#define SATA_REG(Reg)           SB_PCI_CFG_ADDRESS(SATA_BUS, SATA_DEV, \
                                                   SATA_FUN, Reg)
#define SATA2_REG(Reg)          SB_PCI_CFG_ADDRESS(SATA2_BUS, SATA2_DEV, \
                                                   SATA2_FUN, Reg)
#define SMBUS_REG(Reg)          SB_PCI_CFG_ADDRESS(SMBUS_BUS, SMBUS_DEV, \
                                                   SMBUS_FUN, Reg)
#define THERMAL_REG(Reg)        SB_PCI_CFG_ADDRESS(THERMAL_BUS, THERMAL_DEV, \
                                                   THERMAL_FUN, Reg)
#define HDA_REG(Reg)            SB_PCI_CFG_ADDRESS(HDA_BUS, HDA_DEV, \
                                                   HDA_FUN, Reg)
#define LAN_REG(Reg)            SB_PCI_CFG_ADDRESS(LAN_BUS, LAN_DEV, \
                                                   LAN_FUN, Reg)
#define PCIBR_REG(Reg)          SB_PCI_CFG_ADDRESS(PCIBR_BUS, PCIBR_DEV, \
                                                   PCIBR_FUN, Reg)
#define PCIEBRS_REG(Reg)        SB_PCI_CFG_ADDRESS(PCIEBRS_BUS, \
                                                   PCIEBRS_DEV, \
                                                   PCIEBRS_FUN, Reg)
#define PCIEBRS2_REG(Reg)       SB_PCI_CFG_ADDRESS(PCIEBRS2_BUS, \
                                                   PCIEBRS2_DEV, \
                                                   PCIEBRS2_FUN, Reg)
#define PCIEBRS3_REG(Reg)       SB_PCI_CFG_ADDRESS(PCIEBRS3_BUS, \
                                                   PCIEBRS3_DEV, \
                                                   PCIEBRS3_FUN, Reg)
#define PCIEBRS4_REG(Reg)       SB_PCI_CFG_ADDRESS(PCIEBRS4_BUS, \
                                                   PCIEBRS4_DEV, \
                                                   PCIEBRS4_FUN, Reg)
#define PCIEBRS5_REG(Reg)       SB_PCI_CFG_ADDRESS(PCIEBRS5_BUS, \
                                                   PCIEBRS5_DEV, \
                                                   PCIEBRS5_FUN, Reg)
#define PCIEBRS6_REG(Reg)       SB_PCI_CFG_ADDRESS(PCIEBRS6_BUS, \
                                                   PCIEBRS6_DEV, \
                                                   PCIEBRS6_FUN, Reg)
#define PCIEBRS7_REG(Reg)       SB_PCI_CFG_ADDRESS(PCIEBRS7_BUS, \
                                                   PCIEBRS7_DEV, \
                                                   PCIEBRS7_FUN, Reg)
#define PCIEBRS8_REG(Reg)       SB_PCI_CFG_ADDRESS(PCIEBRS8_BUS, \
                                                   PCIEBRS8_DEV, \
                                                   PCIEBRS8_FUN, Reg)

#define SIO_DMA_REG(Reg)        SB_PCI_CFG_ADDRESS(SIO_DMA_BUS, \
                                                   SIO_DMA_DEV, \
                                                   SIO_DMA_FUN, Reg)
#define SIO_I2C0_REG(Reg)       SB_PCI_CFG_ADDRESS(SIO_I2C0_BUS, \
                                                   SIO_I2C0_DEV, \
                                                   SIO_I2C0_FUN, Reg)
#define SIO_I2C1_REG(Reg)       SB_PCI_CFG_ADDRESS(SIO_I2C1_BUS, \
                                                   SIO_I2C1_DEV, \
                                                   SIO_I2C1_FUN, Reg)
#define SIO_GSPI0_REG(Reg)      SB_PCI_CFG_ADDRESS(SIO_GSPI0_BUS, \
                                                   SIO_GSPI0_DEV, \
                                                   SIO_GSPI0_FUN, Reg)
#define SIO_GSPI1_REG(Reg)      SB_PCI_CFG_ADDRESS(SIO_GSPI1_BUS, \
                                                   SIO_GSPI1_DEV, \
                                                   SIO_GSPI1_FUN, Reg)
#define SIO_UART0_REG(Reg)      SB_PCI_CFG_ADDRESS(SIO_UART0_BUS, \
                                                   SIO_UART0_DEV, \
                                                   SIO_UART0_FUN, Reg)
#define SIO_UART1_REG(Reg)      SB_PCI_CFG_ADDRESS(SIO_UART1_BUS, \
                                                   SIO_UART1_DEV, \
                                                   SIO_UART1_FUN, Reg)
#define SIO_SDIO_REG(Reg)       SB_PCI_CFG_ADDRESS(SIO_SDIO_BUS, \
                                                   SIO_SDIO_DEV, \
                                                   SIO_SDIO_FUN, Reg)

#ifdef PCIEX_BASE_ADDRESS
#define HECI_PCIE_REG(Reg)      SB_PCIE_CFG_ADDRESS(HECI_BUS, HECI_DEV, \
                                                       HECI_FUN, Reg)
#define HECI2_PCIE_REG(Reg)     SB_PCIE_CFG_ADDRESS(HECI2_BUS, HECI2_DEV, \
                                                       HECI2_FUN, Reg)
#define SATA_PCIE_REG(Reg)      SB_PCIE_CFG_ADDRESS(SATA_BUS, SATA_DEV, \
                                                       SATA_FUN, Reg)
#define SATA2_PCIE_REG(Reg)     SB_PCIE_CFG_ADDRESS(SATA2_BUS, SATA2_DEV, \
                                                       SATA2_FUN, Reg)
#endif


//----------------------------------------------------------------------------
// INTEL PCH PCI Bus/Device/Function Number Macros
//----------------------------------------------------------------------------
#define HECI_BUS_DEV_FUN        HECI_REG(0)
#define HECI2_BUS_DEV_FUN       HECI2_REG(0)
#define IDER_BUS_DEV_FUN        IDER_REG(0)
#define KT_BUS_DEV_FUN          KT_REG(0)
#define SB_BUS_DEV_FUN          SB_REG(0)
#define XHCI_BUS_DEV_FUN        XHCI_REG(0)
#define EHCI_BUS_DEV_FUN        EHCI_REG(0)
#define EHCI2_BUS_DEV_FUN       EHCI2_REG(0)
#define SATA_BUS_DEV_FUN        SATA_REG(0)
#define SATA2_BUS_DEV_FUN       SATA2_REG(0)
#define SMBUS_BUS_DEV_FUN       SMBUS_REG(0)
#define THERMAL_BUS_DEV_FUN     THERMAL_REG(0)
#define HDA_BUS_DEV_FUN         HDA_REG(0)
#define LAN_BUS_DEV_FUN         LAN_REG(0)
#define PCIBR_BUS_DEV_FUN       PCIBR_REG(0)
#define PCIEBRS_BUS_DEV_FUN     PCIEBRS_REG(0)
#define PCIEBRS2_BUS_DEV_FUN    PCIEBRS2_REG(0)
#define PCIEBRS3_BUS_DEV_FUN    PCIEBRS3_REG(0)
#define PCIEBRS4_BUS_DEV_FUN    PCIEBRS4_REG(0)
#define PCIEBRS5_BUS_DEV_FUN    PCIEBRS5_REG(0)
#define PCIEBRS6_BUS_DEV_FUN    PCIEBRS6_REG(0)
#define PCIEBRS7_BUS_DEV_FUN    PCIEBRS7_REG(0)
#define PCIEBRS8_BUS_DEV_FUN    PCIEBRS8_REG(0)

#define SIO_DMA_BUS_DEV_FUN     SIO_DMA_REG(0)
#define SIO_I2C0_BUS_DEV_FUN    SIO_I2C0_REG(0)
#define SIO_I2C1_BUS_DEV_FUN    SIO_I2C1_REG(0)
#define SIO_GSPI0_BUS_DEV_FUN   SIO_GSPI0_REG(0)
#define SIO_GSPI1_BUS_DEV_FUN   SIO_GSPI1_REG(0)
#define SIO_UART0_BUS_DEV_FUN   SIO_UART0_REG(0)
#define SIO_UART1_BUS_DEV_FUN   SIO_UART1_REG(0)
#define SIO_SDIO_BUS_DEV_FUN    SIO_SDIO_REG(0)

//----------------------------------------------------------------------------
// INTEL PCH RCRB Equates
//----------------------------------------------------------------------------
#define R_ICH_HPET_CONFIG       0x3404
//----------------------------------------------------------------------------
// INTEL PCH ME HECIx Controller (D22:F0/F1/F2/F3) Equates
//----------------------------------------------------------------------------
#define ME_REG_VID              0x00    // PCI Vendor ID Register
#define ICH_REG_ME_VID          ME_REG_VID
#define ME_REG_PCICMD           0x04    // PCI Command Register
#define ICH_REG_ME_PCICMD       ME_REG_PCICMD
#define ME_REG_HECI_MBAR        0x10    // HECI MMIO Base Address Register
#define ICH_REG_ME_HECI0_BAR     ME_REG_HECI_MBAR
#define ME_REG_HECI_EXT_BAR     0x14
#define ICH_REG_ME_HECI0_EXT_BAR ME_REG_HECI_EXT_BAR
#define ME_REG_SVID             0x2c    // Sub-Vendor/SubSystem IDs Register
#define ME_REG_HIDM             0xA0
#define ICH_REG_ME_HIDM         ME_REG_HIDM

//----------------------------------------------------------------------------
// INTEL PCH LPC Bridge (D31:F0) Equates
//----------------------------------------------------------------------------
#define ICH_REG_LPC_VID         0x00
#define SB_REG_PMBASE           0x40    // ACPI Base Address Reg.
#define SB_REG_ACPI_CNTL        0x44    // ACPI Control Reg.
#define SB_REG_GPIOBASE         0x48    // GPIO Base Address Reg.
#define SB_REG_GC               0x4c    // GPIO Control Reg.
#define SB_REG_PIRQ_A           0x60    // PCI IRQ Route Control A Reg.
#define SB_REG_PIRQ_B           0x61    // PCI IRQ Route Control B Reg.
#define SB_REG_PIRQ_C           0x62    // PCI IRQ Route Control C Reg.
#define SB_REG_PIRQ_D           0x63    // PCI IRQ Route Control D Reg.
#define SB_REG_SIRQ_CNTL        0x64    // Serial IRQ Control Reg.
#define SB_REG_PIRQ_E           0x68    // PCI IRQ Route Control E Reg.
#define SB_REG_PIRQ_F           0x69    // PCI IRQ Route Control F Reg.
#define SB_REG_PIRQ_G           0x6a    // PCI IRQ Route Control G Reg.
#define SB_REG_PIRQ_H           0x6b    // PCI IRQ Route Control H Reg.
#define SB_REG_LPC_IO_DEC       0x80    // I/O Decode Ranges Reg.
#define SB_REG_LPC_EN           0x82    // LPC Interface Enables Reg.
#define SB_REG_GEN1_DEC         0x84    // LPC Interface Generic Decode 
                                        // Range 1 Reg.
#define SB_REG_GEN2_DEC         0x88    // LPC Interface Generic Decode 
                                        // Range 2 Reg.
#define SB_REG_GEN3_DEC         0x8c    // LPC Interface Generic Decode 
                                        // Range 3 Reg.
#define SB_REG_GEN4_DEC         0x90    // LPC Interface Generic Decode 
                                        // Range 4 Reg.
#define SB_REG_GEN_PMCON_1      0xa0    // General Power Management
                                        // Configuration 1 Reg. 
#define SB_REG_GEN_PMCON_2      0xa2    // General Power Management
                                        // Configuration 2 Reg. 
#define SB_REG_GEN_PMCON_3      0xa4    // General Power Management
                                        // Configuration 3 Reg. 
#define SB_REG_LPC_PMIR         0xac    // 
#define ICH_REG_LPC_PMIR        SB_REG_LPC_PMIR
#define B_ICH_LPC_PMIR_CF9GR    BIT20   // CF9h Global Reset
#define B_ICH_LPC_PMIR_CF9LOCK  BIT31   // CF9h Lockdown
#define SB_REG_GPI_ROUT         0xb8    // GPI Route Control Reg.
#define SB_REG_BIOS_CNTL        0xdc    // BIOS Control Reg.
#define SB_REG_RCBA             0xf0    // Root Complex Base Address Reg.
#define ICH_REG_LPC_RCBA        SB_REG_RCBA

//----------------------------------------------------------------------------
// INTEL PCH Serial ATA Controller (D31:F2/F5) Equates
//----------------------------------------------------------------------------
#define SATA_REG_DEVID          0x02    // Device ID Reg.
#define SATA_REG_PCICMD         0x04    // Command Register
#define SATA_REG_RID            0x08    // Revision ID Reg.
#define SATA_REG_PCIPI          0x09    // Programming Interface Register
#define SATA_REG_MLT            0x0d    // Primary Master Latnecy Timer Reg.
#define SATA_REG_PCMD_BAR       0x10    // Primary Command Block Base Address Register
#define SATA_REG_PCNL_BAR       0x14    // Primary Control Block Base Address Register
#define SATA_REG_SCMD_BAR       0x18    // Secondary Command Block Base Address Register
#define SATA_REG_SCNL_BAR       0x1C    // Secondary Control Block Base Address Register
#define SATA_REG_BM_BASE        0x20    // Bus Master Base Address Register
#define SATA_REG_ABAR           0x24    // AHCI Base Address Register
#define SATA_REG_SVID           0x2C    // Sub-Vendor/SubSystem IDs register
#define SATA_REG_INTR_LN        0x3C    // Interrupt Line Register
#define SATA_REG_IDETIM         0x40    // Primary & Secondary drive timings register
#define SATA_REG_SIDETIM        0x44    // Slave Primary & Secondary drive timings register
#define SATA_REG_SDMACTL        0x48    // Synchronous DMA Control register
#define SATA_REG_SDMATIM        0x4A    // Synchronous DMA Timing register
#define SATA_REG_IDE_CONFIG     0x54    // IDE I/O Configuration register
#define SATA_REG_PID            0x70    // PCI Power Management Capability ID register
#define SATA_REG_PC             0x72    // PCI Power Management Capability register
#define SATA_REG_PMCS           0x74    // PCI Power Management Control & Status register
#define SATA_REG_MSICI          0x80    // Message Signaled Interrupt Identifiers register
#define SATA_REG_MSIMC          0x82    // Message Signaled Interrupt Message Control register
#define SATA_REG_MSIMA          0x84    // Message Signaled Interrupt Message Address register
#define SATA_REG_MSIMD          0x88    // Message Signaled Interrupt Message Data register
#define SATA_REG_MAP            0x90    // Address Map register
#define SATA_REG_PCS            0x92    // Port Status & Control register
#define SATA_REG_SIR            0x94    // Initialization register
#define SATA_REG_SIRI           0xA0    // S-ATA Register Index register
#define SATA_REG_STRD           0xA4    // S-ATA Register Data register

//----------------------------------------------------------------------------
// INTEL PCH SMBus Controller (D31:F3) Equates             
//----------------------------------------------------------------------------
#define SMBUS_REG_DEVID         0x02    // Device ID Reg.
#define SMBUS_REG_PCICMD        0x04    // PCI Command Register
#define SMBUS_REG_RID           0x08    // Revision Identification Register
#define SMBUS_REG_MBASE0_ADDR   0x10    // SMBus Memory base 0 address register 
#define SMBUS_REG_MBASE1_ADDR   0x14    // SMBus Memory base 1 address register 
#define SMBUS_REG_BASE_ADDR     0x20    // SMBus I/O base address register
#define SMBUS_REG_SVID          0x2c    // SMBus System Vendor ID register
#define SMBUS_REG_INTR_LN       0x3c    // Interrupt Line Register
#define SMBUS_REG_HOST_CONFIG   0x40    // SMBUS Host Configuration register

//----------------------------------------------------------------------------
// INTEL PCH THERMAL Controller (D31:F6) Equates
//----------------------------------------------------------------------------
#define THERMAL_REG_PCICMD      0x04    // PCI Command Register
#define THERMAL_REG_TBAR        0x10    // Thermal Memory Base Address Register
#define THERMAL_REG_INTR_LN     0x3c    // Interrupt Line Register

//----------------------------------------------------------------------------
// INTEL PCH USB 3.0 Controller (D20:F0) Equates             
//----------------------------------------------------------------------------
#define XHCI_REG_VID            0x00    // Vendor ID Reg.
#define XHCI_REG_DEVID          0x02    // Device ID Reg.
#define XHCI_REG_PCICMD         0x04    // PCI Command Register
#define XHCI_REG_RID            0x08    // Revision Identification Register
#define XHCI_REG_SVID           0x2c    // USB 3.0 System Vendor ID register

//----------------------------------------------------------------------------
// INTEL PCH USB 2.0 Controller (D26/29:F0) Equates             
//----------------------------------------------------------------------------
#define EHCI_REG_VID            0x00    // Vendor ID Reg.
#define EHCI_REG_DEVID          0x02    // Device ID Reg.
#define EHCI_REG_PCICMD         0x04    // PCI Command Register
#define EHCI_REG_RID            0x08    // Revision Identification Register
#define EHCI_REG_MBASE_ADDR     0x10    // USB 2.0 Memory base address register
#define EHCI_REG_SVID           0x2c    // USB 2.0 System Vendor ID register
#define EHCI_REG_INTR_LN        0x3c    // Interrupt Line Register
#define EHCI_REG_LEG_EXT_CAP    0x68    // USB EHCI Legacy Support Extended
                                        // Capability Register
#define EHCI_REG_LEG_EXT_CS     0x6c    // USB EHCI Legacy Support Extended
                                        // Control/Status Register
#define EHCI_REG_SPECIAL_SMI    0x70    // INTEL Specific USB 2.0 SMI register
#define EHCI_REG_IR2            0xfc

//----------------------------------------------------------------------------
// INTEL PCH GBE Controller (D25:F0) Equates
//----------------------------------------------------------------------------
#define LAN_REG_MBARA           0x10    // Memory Base Address Register A
#define LAN_REG_MBARB           0x14    // Memory Base Address Register B
#define LAN_REG_SVID            0x2C    // Subsystem Vendor ID register
#define LAN_REG_PMCS            0xCC    // PCI Power Management Control and Status

//----------------------------------------------------------------------------
// INTEL PCH PCI Express Bridge (D28:F0/1/2/3/4/5) Equates
//----------------------------------------------------------------------------
#define PCIEBRS_REG_SVID        0x94    // Subsystem Vendor IDs Reg.
#define ICH_REG_PCIE_BNUM       0x018
#define ICH_REG_PCIE_PCICMD     0x004
#define ICH_REG_PCIE_SLCAP      0x054
//----------------------------------------------------------------------------
// INTEL PCH AZALIA Controller (D27:F0) Equates
//----------------------------------------------------------------------------
#define HDA_REG_SVID            0x2c    // Subsystem Vendor ID Reg.

//----------------------------------------------------------------------------
// INTEL PCH PCI Bus P2P Bridge (D30:F0) Equates
//----------------------------------------------------------------------------
#define PCIBR_REG_PCICMD        0x04    // Command Reg.
#define PCIBR_REG_IOBASE        0x1c    // I/O base Reg.
#define PCIBR_REG_PBUSN         0x18    // Primary Bus Number Reg.
#define PCIBR_REG_SBUSN         0x19    // Secondary Bus Number Reg.
#define PCIBR_REG_SUBUSN        0x1a    // Subordinate Bus Number Reg.
#define PCIBR_REG_MBASE         0x20    // Memory Base Reg.
#define PCIBR_REG_PMBASE        0x24    // Prefretchable memory Base Reg.
#define PCIBR_REG_PMBASEU       0x28    // Prefretchable memory Base
#define PCIBR_REG_INTR_LN       0x3c    // Interrupt Line Reg.
#define PCIBR_REG_SPDH          0x40    // Secondary PCI Device Hiding Register.
#define PCIBR_REG_DTC           0x44    // Delayed Transaction Control Register.
#define PCIBR_REG_BPC           0x4c    // Bridge Policy Configuration Register.
#define PCIBR_REG_SVID          0x54    // Subsystem Vendor IDs Reg.

//----------------------------------------------------------------------------
// INTEL PCH RCRB Mmemory Mapped I/O Registers
//----------------------------------------------------------------------------
#define RCRB_MMIO_TRSR          0x1e00  // Trap Status Register
#define RCRB_MMIO_TRCR          0x1e10  // Trapped Cycle Register
#define RCRB_MMIO_TWDR          0x1e18  // Trap Write Data Register
#define RCRB_MMIO_IO_TRAP_0     0x1e80  // Trap Configuration Register 0
#define RCRB_MMIO_IO_TRAP_1     0x1e88  // Trap Configuration Register 1
#define RCRB_MMIO_IO_TRAP_2     0x1e90  // Trap Configuration Register 2
#define RCRB_MMIO_IO_TRAP_3     0x1e98  // Trap Configuration Register 3
#define ICH_RCRB_PRSTS          0x3310  // Power and Reset Srtatus Register
#define ICH_RCRB_PMCFG          0x3318  // Power Management Configuration Register
#define RCRB_MMIO_HPTC          0x3404  // High Precision Timer Configuration
                                        // Register
#define RCRB_MMIO_GCS           0x3410  // General Control and Status Register
#define RCRB_MMIO_BUC           0x3414  // Backed Up Control Register
#define RCRB_MMIO_FD            0x3418  // Function Disable Register
#define ICH_RCRB_FD2            0x3428  // Function Disable Register 2
#define RCRB_MMIO_RMHWKCTL      0x35B0  // Rate Matching Hub Wake Control Register


//----------------------------------------------------------------------------
// INTEL PCH ACPI Power Management I/O Registers
//----------------------------------------------------------------------------
#define ACPI_IOREG_PM1_STS      0x00    // Power Management 1 Status Reg.
#define ACPI_IOREG_PM1_EN       0x02    // Power Management 1 Enables Reg.
#define ACPI_IOREG_PM1_CNTL     0x04    // Power Management 1 Control Reg.
#define ACPI_IOREG_PM1_TMR      0x08    // Power Management 1 Timer Reg.
#define ACPI_IOREG_PROC_CNTL    0x10    // Processor Control Reg.

#define ACPI_PCHLP_IOREG_GPE0_STS   0x80    // General Purpose Event 0 Status Reg for PchLp.
#define ACPI_PCHLP_IOREG_GPE0_EN    0x90    // General Purpose Event 0 Enable Reg for PchLp.
#define ACPI_IOREG_GPE0_STS     0x20    // General Purpose Event 0 Status Reg.
#define ACPI_IOREG_GPE0_EN      0x28    // General Purpose Event 0 Enable Reg.


#define ICH_LP_IOREG_GPE0_STS      ACPI_PCHLP_IOREG_GPE0_STS + 0x0c
#define ICH_LP_IOREG_GPE0_EN       ACPI_PCHLP_IOREG_GPE0_EN + 0x0c

#define ICH_IOREG_GPE0_STS      ACPI_IOREG_GPE0_STS
#define ICH_IOREG_GPE0_EN       ACPI_IOREG_GPE0_EN


#define ACPI_IOREG_SMI_EN       0x30    // SMI Control and Enable Reg.
#define ICH_IOREG_SMI_EN        ACPI_IOREG_SMI_EN
#define ACPI_IOREG_SMI_STS      0x34    // SMI status Reg.
#define ICH_IOREG_SMI_STS       ACPI_IOREG_SMI_STS

#define ACPI_IOREG_ALTGP_SMI_EN 0x38    // Alternate GPI SMI Enable Reg.
#define ACPI_IOREG_ALTGP_SMI_STS 0x3a   // Alternate GPI SMI Status Reg.
#define ACPI_IOREG_UPRWC        0x3c    // USB Per-Port Regs Write Control.
#define ACPI_IOREG_GPE_CNTL     0x42    // General Purpose Event Control Reg.
#define ACPI_IOREG_DEVACT_STS   0x44    // Device Activity Status Reg.
#define ACPI_IOREG_PM2_CNTL     0x50    // Power Management 2 Control Reg.

//----------------------------------------------------------------------------
// INTEL PCH System Management TCO I/O Registers
//----------------------------------------------------------------------------
#define TCO_IOREG_RLD           0x00    // TCO Timer Reload and Current Value
#define TCO_IOREG_DAT_IN        0x02    // TCO Data In Reg.
#define TCO_IOREG_DAT_OUT       0x03    // TCO Data Out Reg.
#define TCO_IOREG_STS1          0x04    // TCO Status 1 Reg.
#define ICH_IOREG_TCO1_STS      TCO_IOREG_STS1
#define TCO_IOREG_STS2          0x06    // TCO Status 2 Reg.
#define TCO_IOREG_CNT1          0x08    // TCO Control 1 Reg.
#define TCO_IOREG_CNT2          0x0a    // TCO Control 2 Reg.
#define TCO_IOREG_MESSAGE1      0x0c    // TCO Message 1 Reg.
#define TCO_IOREG_MESSAGE2      0x0d    // TCO Message 2 Reg.
#define TCO_IOREG_WDCNT         0x0e    // TCO Watchdog Control Reg.
#define TCO_IOREG_SWIRQ_GEN     0x10    // Software IRQ Generation Reg.
#define TCO_IOREG_TMR           0x12    // TCO Timer Initial Value Reg

//----------------------------------------------------------------------------
// INTEL PCH System Management Bus I/O Space Equates
//----------------------------------------------------------------------------
#define SMB_IOREG_HST_STS        0x00   // Host Status Reg.
#define     HST_STS_HOST_BUSY        0x01    // R/WC
#define     HST_STS_INTR             0x02    // R/WC
#define     HST_STS_DEV_ERR          0x04    // R/WC
#define     HST_STS_BUS_ERR          0x08    // R/WC
#define     HST_STS_FAILED           0x10    // R/WC
#define     HST_STS_SMBALERT_STS     0x20    // R/WC
#define     HST_STS_INUSE_STS        0x40    // R/WC
#define     HST_STS_BDS              0x80    // R/WC
#define     HST_STS_ALL              0xff    // R/WC
#define     HST_STS_ERROR            0x1c    // R/WC
#define SMB_IOREG_HST_CNT        0x02   // Host Control Reg.
#define     HST_CNT_INTREN           0x01    // RW
#define     HST_CNT_KILL             0x02    // RW
#define     HST_CNT_SMB_CMD          0x1C    // RW
#define         SMB_CMD_BYTE             0x04
#define         SMB_CMD_BYTE_DATA        0x08
#define         SMB_CMD_WORD_DATA        0x0c
#define         SMB_CMD_BLOCK            0x14
#define     HST_CNT_LAST_BYTE        0x20    // RW
#define     HST_CNT_START            0x40    // RW
#define     HST_CNT_PEC_EN           0x80    // RW
#define SMB_IOREG_HST_CMD        0x03   // Host Command Reg.
#define SMB_IOREG_XMIT_SLVA      0x04   // Transmit Slave Address Reg.
#define     XMIT_SLVA_RW             0x01    // RW
#define SMB_IOREG_HST_D0         0x05   // Host Data 0
#define SMB_IOREG_HST_D1         0x06   // Host Data 1
#define SMB_IOREG_HOST_BLOCK_DB  0x07   // Host Block Data Byte Reg.
#define SMB_IOREG_PEC            0x08   // Packet Error Check Reg.
#define SMB_IOREG_RCV_SLVA       0x09   // Receive Slave Address Reg.
#define SMB_IOREG_SLV_DATA0      0x0a   // Receive Slave Data 0 Reg.
#define SMB_IOREG_SLV_DATA1      0x0b   // Receive Slave Data 1 Reg.
#define SMB_IOREG_AUX_STS        0x0c   // Auxiliary Status Reg.
#define     AUX_STS_CRC_ERR          0x01    // R/WC
#define     AUX_STS_STCO             0x02    // RO
#define SMB_IOREG_AUX_CTL        0x0d   // Auxiliary Control Reg.
#define     AUX_CTL_AAC              0x01    // R/W
#define     AUX_CTL_E32B             0x02    // R/W
#define SMB_IOREG_SMLINK_PIN_CTL 0x0e   // SMLink Pin Control Reg.
#define SMB_IOREG_SMBUS_PIN_CTL  0x0f   // SMBus Pin Control Reg.
#define SMB_IOREG_SLV_STS        0x10   // Slave Status Reg.
#define SMB_IOREG_SLV_CMD        0x11   // Slave Command Reg.
#define SMB_IOREG_NOTIFY_DADDR   0x14   // Notify Device Address Reg.
#define SMB_IOREG_NOTIFY_DLOW    0x16   // Notify Data Low Reg.
#define SMB_IOREG_NOTIFY_DHIGH   0x17   // Notify Data High Reg.

#define SMBUS_NUM_RESERVED      21      // Number of device addresses
                                        // that are reserved by the
                                        // SMBus spec.

#define SMBUS_DEVICE_DEFAULT_ADDRESS    0xc2 >> 1
#define PREPARE_TO_ARP                  0x01
#define GET_UDID_DIRECTED               0x01
#define RESET_DEVICE_GENERAL            0x02
#define GET_UDID_GENERAL                0x03
#define ASSIGN_ADDRESS                  0x04
#define GET_UDID_DATA_LENGTH            0x11    // 16 byte UDID + 1 byte address

//----------------------------------------------------------------------------
// INTEL PCH GP I/O Register Equates
//----------------------------------------------------------------------------
#define GP_IOREG_GP_OWN1        0x00    // GPIO determines the appropriate status for PchLp
#define GP_IOREG_GP_OWN2        0x04    // GPIO determines the appropriate status for PchLp
#define GP_IOREG_GP_OWN3        0x08    // GPIO determines the appropriate status for PchLp
#define GPI_IRQ_2_IOAPIC        0x10    // enables the corresponding GPIO PIRQ[X:I] pin to generate IOxAPIC interrupt for PchLp
#define GP_IOREG_GPI_ROUT       0x30    // GPI Route Control Reg for PchLp
#define GP_IOREG_GPI_ROUT2      0x34    // GPI Route Control Reg for PchLp
#define GP_IOREG_GPI_ROUT3      0x38    // GPI Route Control Reg for PchLp
#define GP_IOREG_USE_SEL        0x00    // GPIO Use Select register
#define GP_IOREG_IO_SEL         0x04    // GPIO Input/Output select
#define GP_IOREG_GP_LVL         0x0c    // GPIO Level for Input/Ouput
#define GP_IOREG_GPI_INV        0x2c    // GPI Invert register
#define GP_IOREG_USE_SEL2       0x30    // GPIO Use Select 2 register
#define GP_IOREG_IO_SEL2        0x34    // GPIO Input/Output select 2
#define GP_IOREG_GP_LVL2        0x38    // GPIO Level 2 for Input/Ouput
#define GP_IOREG_USE_SEL3       0x40    // GPIO Use Select 3 register
#define GP_IOREG_IO_SEL3        0x44    // GPIO Input/Output select 3
#define GP_IOREG_GP_LVL3        0x48    // GPIO Level 3 for Input/Ouput

#define GP_IOREG_GPO_BLINK      0x18    // GPIO Blink Register
#define GP_IOREG_GP_SER_BLINK   0x1c    // GP Serial Blink Register
#define GP_IOREG_GP_SB_CMDTST   0x20    // GP Serial Blink Command Status Reg.
#define GP_IOREG_GP_SB_DATA     0x24    // GP Serial Blink Data Register
#define GP_IOREG_GPI_NMI_EN     0x28    // GPI NMI Enable Register
#define GP_IOREG_GPI_NMI_STS    0x2a    // GPI NMI Status Register

#define GP_IOREG_GP_RST_SEL1    0x60    // GPIO Reset Select 1 register
#define GP_IOREG_GP_RST_SEL2    0x64    // GPIO Reset Select 2 register
#define GP_IOREG_GP_RST_SEL3    0x68    // GPIO Reset Select 3 register

#define GP_IOREG_PCHLP_GPI_NMI_EN     GP_IOREG_GPI_NMI_EN    // GPI NMI Enable Reg for PchLp.
#define GP_IOREG_PCHLP_GPI_NMI_STS    GP_IOREG_GPI_NMI_STS    // GPI NMI Status Reg for PchLp.
#define GP_IOREG_ALTGP_SMI_STS  0x50    // Alternate GPI SMI Status Reg for PchLp.
#define GP_IOREG_ALTGP_SMI_EN   0x54    // Alternate GPI SMI Enable Reg for PchLp.

#define GP_IOREG_GP_INT_SEL1    0x90    // GPIO Interrupt Select 1 register
#define GP_IOREG_GP_INT_SEL2    0x94    // GPIO Interrupt Select 2 register
#define GP_IOREG_GP_INT_SEL3    0x98    // GPIO Interrupt Select 3 register

#define GP_IOREG_GP_GPN_CFG1    0x100   // GPIOn Config [31:0] register for PchLp
#define GP_IOREG_GP_GPN_CFG2    0x104   // GPIOn Config [64:32] register for PchLp
#define GP_GPIO_CONFIG_SIZE     0x08    // GPIO Config register size  for PchLp

//----------------------------------------------------------------------------
// INTEL PCH USB 2.0 Memory Mapped I/O Registers
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// INTEL PCH HD Audio Memory Mapped I/O Registers
//----------------------------------------------------------------------------
         
//----------------------------------------------------------------------------
// INTEL PCH SPI Registers (Porting Required)
//----------------------------------------------------------------------------
#define R_SB_RCRB_SPI_BFPR      0x00    // BIOS Flash Primary Region Register(32bits), which is RO and contains the same value from FREG1
#define B_SB_SPI_BFPR_PRL       0x7FFF0000     // BIOS Flash Primary Region Limit mask
#define B_SB_SPI_BFPR_PRB       0x00007FFF     // BIOS Flash Primary Region Base mask
#define R_RCRB_SPI_FADDR        0x08    // Flash Address Register
#define R_RCRB_SPI_FDATA0       0x10    // Flash Data 0 Register
#define R_RCRB_SPI_FDOC         0xB0    // Flash Descriptor Observability Control Register
#define R_RCRB_SPI_FDOD         0xB4    // Flash Descriptor Observability Data Register
#define R_SB_RCRB_SPI_FREG0_FLASHD 0x54    // Flash Region 0(Flash Descriptor)(32bits)
#define R_SB_RCRB_SPI_FREG1_BIOS   0x58    // Flash Region 1(BIOS)(32bits)
#define R_SB_RCRB_SPI_FREG2_ME     0x5C    // Flash Region 2(ME)(32bits)
#define R_SB_RCRB_SPI_FREG3_GBE    0x60    // Flash Region 3(GbE)(32bits)
#define R_SB_RCRB_SPI_FREG4_PLATFORM_DATA  0x64   // Flash Region 4(Platform Data)(32bits)
#define S_SB_SPI_FREGX             4       // Size of Flash Region register
#define B_SB_SPI_FREGX_LIMIT_MASK  0x7FFF0000     // Size, [30:16] here represents limit[26:12]
#define B_SB_SPI_FREGX_BASE_MASK   0x00007FFF     // Base, [14:0]  here represents base [26:12]
#define R_SB_RCRB_SPI_PR0          0x74    // Protected Region 0 Register
#define R_SB_RCRB_SPI_PR1          0x78    // Protected Region 1 Register
#define R_SB_RCRB_SPI_PR2          0x7C    // Protected Region 2 Register
#define R_SB_RCRB_SPI_PR3          0x80    // Protected Region 3 Register
#define R_SB_RCRB_SPI_PR4          0x84    // Protected Region 4 Register
#define B_SB_SPI_PRx_WPE           BIT31   // Write Protection Enable
#define B_SB_SPI_PRx_RPE           BIT15   // Read Protection Enable
#define R_RCRB_SPI_SSFSTS       0x90    // Software Squencing Flash Status
#define R_RCRB_SPI_SSFCTL       0x91    // Software Squencing Flash Control
#define R_RCRB_SPI_PREOP        0x94    // Prefix Opcode Configuration
#define R_RCRB_SPI_OPTYPE       0x96    // Opcode Type Configuration
#define R_RCRB_SPI_OPMENU       0x98    // Opcode Menu Configuration
#define R_RCRB_SPI_LVSCC        0xC4    // Host Lower Vendor Specific Component Capabilities Register
#define R_RCRB_SPI_UVSCC        0xC8    // Host Upper Vendor Specific Component Capabilities Register

#define B_PCH_SPI_FDOC_FDSS_MASK      (BIT14 | BIT13 | BIT12)       // Flash Descritor Section Select
#define V_PCH_SPI_FDOC_FDSS_PCHS      0x4000                        // ICH soft straps
#define B_PCH_SPI_FDOC_FDSI_MASK      0x0FFC                        // Flash Descriptor Section Index
#define R_PCH_SPI_STRP15              0x3C

//----------------------------------------------------------------------------
// INTEL PCH Legacy Power Management I/O Registers
//----------------------------------------------------------------------------
#define ICH_IOREG_APMC          0xb2    // APM Control I/O Address
#define ICH_IOREG_APMS          0xb3    // APM Status I/O Address

//----------------------------------------------------------------------------
// INTEL PCH Misc. I/O Registers
//----------------------------------------------------------------------------
#define KBC_IO_DATA             0x60    // Keyboard Controller Data Port
#define PORTB_IO_CNTL           0x61    // Port B control Register
#define KBC_IO_STS              0x64    // Keyboard Controller Status Port
#define CMOS_IO_EXT_INDEX       0x72    // CMOS I/O Extended Index Port
#define CMOS_IO_EXT_DATA        0x73    // CMOS I/O Extended Data Port
#define CMOS_IO_INDEX_BACKDOOR  0x74    // RTC I/O Index Port (Back Door)
#define CMOS_IO_DATA_BACKDOOR   0x75    // RTC I/O Data Port (Back Door)
#define RESET_PORT              0x0CF9
#define     COLD_RESET          0x02    // Set bit 1 for cold reset.
#define     RST_CPU             0x04    // Setting this bit triggers a
                                        // reset of the CPU.
#define     FULL_RESET          0x08    // Set bit 3 for full reset.
#define IO_DELAY_PORT           0xed    // Use for I/O delay

//----------------------------------------------------------------------------
// INTEL PCH Internal Device Interrupt Pin Definition
//----------------------------------------------------------------------------

#define RCRB_IRQ0               0x00    // No Interrupt
#define RCRB_IRQA               0x01    // INTA#
#define RCRB_IRQB               0x02    // INTB#
#define RCRB_IRQC               0x03    // INTC#
#define RCRB_IRQD               0x04    // INTD#
#define RCRB_PIRQA              0x00    // PIRQA#
#define RCRB_PIRQB              0x01    // PIRQB#
#define RCRB_PIRQC              0x02    // PIRQC#
#define RCRB_PIRQD              0x03    // PIRQD#
#define RCRB_PIRQE              0x04    // PIRQE#
#define RCRB_PIRQF              0x05    // PIRQF#
#define RCRB_PIRQG              0x06    // PIRQG#
#define RCRB_PIRQH              0x07    // PIRQH#


#define ONE_SECOND              1000000 // The stall PPI is defined in 
                                        // microseconds, this should be
                                        // one second in microseconds.
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
