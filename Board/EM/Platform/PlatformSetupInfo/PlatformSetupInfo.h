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
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/Platform/PlatformSetupInfo/PlatformSetupInfo.h 7     3/15/13 6:57a Alanlin $
//
// $Revision: 7 $
//
// $Date: 3/15/13 6:57a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/Platform/PlatformSetupInfo/PlatformSetupInfo.h $
// 
// 7     3/15/13 6:57a Alanlin
// [TAG] None
// [Category] Normal
// [Severity] Normal
// [Description] Add PCH Lan version information.
// [Files] PlatformSetupInfo.c, PlatformSetupInfo.h.
// 
// 6     1/15/13 5:49a Alanlin
// [TAG] None
// [Category] Normal
// [Severity] Normal
// [Description] Update to support Haswell C0 and ULT C1 setup info
// [Files] PlatformSetupInfo.c, PlatformSetupInfo.h
// 
// 5     11/26/12 6:02a Alanlin
// [TAG] None
// [Category] Improvement
// [Severity] Normal
// [Description] Fixed that Setup menu shows incorrect CPU informaion for
// Sharkbay ULT.
// [Files] PlatformSetupInfo.c, PlatformSetupInfo.h
// 
// 
// 4     8/14/12 8:56a Yurenlai
// [TAG]         None
// [Category]    Improvement
// [Severity]    Important
// [Description] Update to support Haswell B0 and ULT A0 setup info.
// [Files]       PlatformSetupInfo.c, PlatformSetupInfo.h
// 
// 3     7/11/12 3:55a Yurenlai
// [TAG]         None
// [Category]    Improvement
// [Description] Correct Lan PHY Revision in BIOS Setup info.
// [Files]       PlatformSetupInfo.c, PlatformSetupInfo.h
// 
// 2     4/25/12 1:23p Yurenlai
// [TAG]         None
// [Category]    Improvement
// [Description] Correct Graphics Technology (GT) Displays (GT Info) in
// BIOS Setup.
// [Files]       PlatformSetupInfo.c, PlatformSetupInfo.h
// 
// 1     2/24/12 1:02a Yurenlai
// Add PlatformSetupInfo module part.
// 
//*************************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:            PlatformSetupInfo.h
//
// Description:     Header file for PlatformSetupInfo module.
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef __PLATFORM_SETUP_INFO_H__
#define __PLATFORM_SETUP_INFO_H__

#ifdef __cplusplus
extern "C" {
#endif

#define CPUID_FULL_FAMILY_MODEL_HASWELL_A0      0x000306C1  // Haswell
#define CPUID_FULL_FAMILY_MODEL_HASWELL_B0      0x000306C2  // Haswell
#define CPUID_FULL_FAMILY_MODEL_HASWELL_C0      0x000306C3  // Haswell C-0
#define CPUID_FULL_FAMILY_MODEL_HASWELL_ULT     0x00040650  // Haswell ULT
#define CPUID_FULL_FAMILY_MODEL_HASWELL_ULT_C0  0x00040651  // Haswell ULT C-1
#define CPUID_FULL_FAMILY_MODEL_CRYSTALWELL     0x00040660  // CRYSTALWELL

#define PciD31F0RegBase           PCIEX_BASE_ADDRESS + (UINT32) (31 << 15)
#define PciNBD0F0RegBase          PCIEX_BASE_ADDRESS 
#define PCIE_Revision_Identification   0x08
//
// LAN PHY Revision definitions
//
#define PHY_CONFIG_REG            0x00000020
#define PHY_SEMAPHORE_REG         0x00000F00
#define PHY_PAGE769_SET_REG       0x43f6020
#define PHY_SLOW_MDIO_MODE_REG    0x4302580
#define PHY_READ_PHY_OFFSET3_REG  0x8430000
#define PHY_FAST_MDIO_MODE_REG    0x4302180
#define LAN_PHY_REV_A0            0xA1
#define LAN_PHY_REV_A1            0xA2
#define LAN_PHY_REV_A2            0xA3
#define LAN_PHY_REV_A3            0xA4
#define LAN_PHY_REV_B0            0xA6
#define LAN_PHY_REV_C0            0xA7

// Max loop value for GBE check
#define GBE_MAX_LOOP_TIME         4000

#pragma pack(1)
typedef struct {
  UINT32  CPUID;
  UINT8   Stepping;
  CHAR8   String[16];
} CPU_REV;

typedef struct _LAN_PHY_INFO {
  UINT16  LanPhyRev;
  char    *LanPhyString;
} LAN_PHY_INFO;
#pragma pack()

/****** DO NOT WRITE BELOW THIS LINE *******/
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
