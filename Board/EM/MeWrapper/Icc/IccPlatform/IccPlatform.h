//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
//**********************************************************************
//
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/MeWrapper/Icc/IccPlatform/IccPlatform.h 1     2/08/12 1:06a Klzhan $
//
// $Revision: 1 $
//
// $Date: 2/08/12 1:06a $
//
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/MeWrapper/Icc/IccPlatform/IccPlatform.h $
// 
// 1     2/08/12 1:06a Klzhan
// Initial Check in 
// 
// 4     7/27/11 3:21a Klzhan
// Add Elinks for PCIE and PCI config.
// Note: Don't List GBE port on this Elink.
// 
// 3     7/15/11 12:45a Klzhan
// 
// 2     6/27/11 8:38a Klzhan
// Remove un-use define.
// 
// 1     2/25/11 1:42a Klzhan
// Initial Check-in
// 
// 1     12/03/10 5:10a Klzhan
// Initial Check-in.
// 
//
//**********************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:            IccPlatform.h
//
// Description:     Platform-specific ICC code
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

/*++
Copyright (c)  2009 Intel Corporation. All rights reserved
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.

Module Name:

  IccPlatform.h

Abstract:

  Platform-specific ICC code

--*/

#ifdef CougarPoint_SUPPORT
#define SOFTSTRAP10 R_PCH_SPI_STRP10
#else
#define SOFTSTRAP10 R_PCH_SPI_PCHSTRP10
#endif

#define ICC_INIT_TIMEOUT 5000     // ms

#define RETAIN_CLOCK_ENABLES_AT_RESUME_FROM_S3  0x1
#define CLOCK_PROFILE_SELECTOR                  BIT22

#define PROFILE_SELECTED_BY_BIOS  0
#define PROFILE_SELECTED_BY_ME    1

//
// 96-bit mask of registers to be locked by LockIccRegister heci message
// 0 = lock, 1 = don't
// see CPT c-spec for register names
//
#define STATIC_REGISTERS_MASK2    0x00000000
#define STATIC_REGISTERS_MASK1    0x0F0f0013
#define STATIC_REGISTERS_MASK0    0x00000000

#define OPTION_DISABLED           0
#define OPTION_ENABLED            1
#define OPTION_MANUAL             2
#define OPTION_AUTO               3
#define OPTION_LOCK_STATIC        4
#define OPTION_LOCK_ALL           5
#define OPTION_USE_OEM            6
#define OPTION_OVERRIDE           7
//
// OCLKEN (ICC clock enables) register bit definitions
//
#define CLOCK_Flex0       BIT0
#define CLOCK_Flex1       BIT1
#define CLOCK_Flex2       BIT2
#define CLOCK_Flex3       BIT3
#define CLOCK_PCI_Clock0  BIT7
#define CLOCK_PCI_Clock1  BIT8
#define CLOCK_PCI_Clock2  BIT9
#define CLOCK_PCI_Clock3  BIT10
#define CLOCK_PCI_Clock4  BIT11
#define CLOCK_SRC0        BIT16
#define CLOCK_SRC1        BIT17
#define CLOCK_SRC2        BIT18
#define CLOCK_SRC3        BIT19
#define CLOCK_SRC4        BIT20
#define CLOCK_SRC5        BIT21
#define CLOCK_SRC6        BIT22
#define CLOCK_SRC7        BIT23
#define CLOCK_CSI_SRC8    BIT24
#define CLOCK_CSI_DP      BIT25
#define CLOCK_PEG_A       BIT26
#define CLOCK_PEG_B       BIT27
#define CLOCK_DMI         BIT28

#define BDS_ALL_DRIVERS_CONNECTED_PROTOCOL_GUID \
  {0xdbc9fd21, 0xfad8, 0x45b0, 0x9e, 0x78, 0x27, 0x15, 0x88, 0x67, 0xcc, 0x93}

typedef struct {
  UINT32  Clock;
  UINT8   DeviceNumber;
  BOOLEAN HotPlugSupport;
} PLATFORM_PCI_SLOTS;

typedef struct {
  UINT32  Clock;
  UINT8   RootPortNumber;
  BOOLEAN HotPlugSupport;
} PLATFORM_PCIE_SLOTS;

typedef struct _ICC_CONFIG {
  UINT8   LockIccRegisters;
  UINT8   SetClkEnables;
  UINT8   ProfileSelection;
  UINT8   SelectedIccProfile;
  UINT32  LockMask[3];
  UINT32  ClkEnables;
  UINT32  ClkEnablesMask;
  UINT8   ClocksModified;
} ICC_CONFIG;

VOID
DisableProfileSelection (
  VOID
  );

EFI_STATUS
ProfileSelection (
  IN UINT8 NewProfile
  );

EFI_STATUS
DetectUsedClocks (
  OUT UINT32 *UsedClocks,
  OUT UINT32 *AllClocks
  );

EFI_STATUS
CallSetClockEnables (
  IN EFI_EVENT Event,
  IN VOID      *Context
  );

EFI_STATUS
ReadMainSetupData (
  ICC_CONFIG* IccConfig
  );

UINT8
ReadIccSoftStraps (
  VOID
  );

EFI_STATUS
WaitForFwInitComplete (
  UINT32 uSeconds
  );

EFI_STATUS
IccFailureNotification (
  VOID
  );

EFI_STATUS 
SendIccMessages (
  IN EFI_EVENT Event,
  IN VOID      *Context
  );

EFI_STATUS
IccMessages (
  VOID
  );

#ifdef CougarPoint_SUPPORT

EFI_STATUS
WdtSupport (
  VOID
  );

EFI_STATUS
FeedWatchdog (
  IN EFI_EVENT Event,
  IN VOID      *Context
  );

EFI_STATUS
StopFeedingWatchdog (
  IN EFI_EVENT Event,
  IN VOID      *Context
  );

#endif;

#if defined PERF_TUNE_SUPPORT && PERF_TUNE_SUPPORT == 1
typedef struct _ACPI_HDR {
    UINT32      Signature;
    UINT32      Length;
    UINT8       Revision;
    UINT8       Checksum;
    UINT8       OemId[6]; 
    UINT8       OemTblId[8];
    UINT32      OemRev;
    UINT32      CreatorId;
    UINT32      CreatorRev;
} ACPI_HDR,*PACPI_HDR;
#endif;
//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************