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
// $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/SB PPI/SBPPI.h 3     4/24/13 2:16a Scottyang $
//
// $Revision: 3 $
//
// $Date: 4/24/13 2:16a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/SB PPI/SBPPI.h $
// 
// 3     4/24/13 2:16a Scottyang
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Porting GPI interrupt by LPT-LP EDS 1.5.
// [Files]  		SB.sdl, SB.H, SBPPI.h, SBPEI.c
// 
// 2     7/27/12 6:14a Victortu
// [TAG]           None
// [Category]      Improvement
// [Description]   Update to support ULT Platform.
// [Files]         SB.H, SB.mak, SB.sdl, SB.sd, SBSetup.c,
// AcpiModeEnable.c, SBDxe.c, SBPEI.c, SBSMI.c, SleepSmi.c,
// SmiHandlerPorting.c, SmiHandlerPorting2.c, SBPPI.h, Pch.sdl
// 
// 1     2/08/12 8:25a Yurenlai
// Intel Lynx Point/SB eChipset initially releases.
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:        SBPPI.h
//
// Description: This header file contains the PPI definition for the SB.
//
//<AMI_FHDR_END>
//*************************************************************************

#ifndef FILE_PEI_SBINIT_POLICY_PPI_H_
#define FILE_PEI_SBINIT_POLICY_PPI_H_

// {95E8152B-1B98-4f11-8A77-DB26583EBC42}
#define AMI_PEI_SBINIT_POLICY_PPI_GUID  \
 {0x95e8152b, 0x1b98, 0x4f11, 0x8a, 0x77, 0xdb, 0x26, 0x58, 0x3e, 0xbc, 0x42}

#define AMI_PEI_SB_OEM_PLATFORM_POLICY_OVERRIDE_PPI_GUID  \
 {0x61187967, 0x9a77, 0x419d, 0xaa, 0xea, 0x64, 0xdd, 0x56, 0x19, 0x08, 0x15}

// {38965BB5-8097-40f5-B742-8CC14A649B64}
#define AMI_PEI_SB_CUSTOM_PPI_GUID  \
 {0x38965bb5, 0x8097, 0x40f5, 0xb7, 0x42, 0x8c, 0xc1, 0x4a, 0x64, 0x9b, 0x64}
GUID_VARIABLE_DECLARATION(gAmiPeiSBCustomPpiGuid, AMI_PEI_SB_CUSTOM_PPI_GUID);

typedef struct _AMI_PEI_SBINIT_POLICY_PPI   AMI_PEI_SBINIT_POLICY_PPI;

typedef struct _AMI_PEI_SBINIT_POLICY_PPI {
    UINTN                       unFlag;
} AMI_PEI_SBINIT_POLICY_PPI;

typedef struct _AMI_SB_PCI_SSID_TABLE_STRUCT AMI_SB_PCI_SSID_TABLE_STRUCT;

typedef struct _AMI_SB_PCI_DEVICES_TABLE_STRUCT {
    UINT64                      PciAddr;
    UINT8                       PciSidReg;
} AMI_SB_PCI_DEVICES_TABLE_STRUCT;

typedef struct _AMI_SB_PCI_SSID_TABLE_STRUCT {
    UINT64                      PciAddr;
    UINT32                      Sid;
} AMI_SB_PCI_SSID_TABLE_STRUCT;

typedef struct _AMI_GPIO_INIT_TABLE_STRUCT  AMI_GPIO_INIT_TABLE_STRUCT;

typedef union _AMI_GPIO_STRUCT
{
 UINT16 Dword;
 struct
 {
   UINT16 USE:1;
   UINT16 IO :1;
   UINT16 LVL:1;
   UINT16 INV:1;
   UINT16 BLK:1;
   UINT16 RST:1;
   UINT16 OWN:1;
   UINT16 LEB:1;
   UINT16 DIS:1;
   UINT16 WP :2;
   UINT16 INT:1;   
   UINT16 RESERVED:4;
  } Fileds;
} AMI_GPIO_STRUCT;

typedef struct _AMI_GPIO_INIT_TABLE_STRUCT {
    UINT16                      GpioNo;
    AMI_GPIO_STRUCT             GpioCfg;
} AMI_GPIO_INIT_TABLE_STRUCT;

typedef struct _AMI_GPIO_INIT_PPI           AMI_GPIO_INIT_PPI;

typedef struct _AMI_GPIO_INIT_PPI {
    UINT32                      GpioBaseAddr;
    AMI_GPIO_INIT_TABLE_STRUCT  *GpioTable;
    BOOLEAN                     InitDefaultGpioSetting;
} AMI_GPIO_INIT_PPI;

typedef struct _AMI_PEI_SB_CUSTOM_PPI       AMI_PEI_SB_CUSTOM_PPI;

typedef struct _AMI_PEI_SB_CUSTOM_PPI {
    AMI_GPIO_INIT_PPI            *GpioInit;
    AMI_SB_PCI_SSID_TABLE_STRUCT *SsidTable;
} AMI_PEI_SB_CUSTOM_PPI;

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
