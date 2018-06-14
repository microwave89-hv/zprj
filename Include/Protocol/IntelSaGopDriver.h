//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.            **
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
// $Header: /Alaska/BIN/Chipset/Intel/NorthBridge/Haswell/IntelGopDriver/IntelSaGopDriverProtocol/IntelSaGopDriver.h 3     4/23/13 8:00a Ireneyang $
//
// $Revision: 3 $
//
// $Date: 4/23/13 8:00a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Chipset/Intel/NorthBridge/Haswell/IntelGopDriver/IntelSaGopDriverProtocol/IntelSaGopDriver.h $
// 
// 3     4/23/13 8:00a Ireneyang
// [TAG]          None
// [Severity]     Improvement
// [Description]  Support for BIST (Built-In Self Test) Protocol.
// [Files]        IntelSaGopSetup.c; IntelSaGopSetup.h;
// IntelSaGopSetup.sd;
//                IntelSaGopSetup.sd; IntelSaGopSetup.sdl; 
//                IntelSaGopSetup.uni; IntelSaGopDriver.h;  
// 
// 2     8/14/12 5:49a Yurenlai
// [TAG]         None
// [Severity]    Important
// [Description] Implemented BIOS Integration Guide Rev 1.0 to Intel SA
// GOP driver.
// [Files]       IntelSaGopDriver.cif, IntelSaGopDriver.mak,
//               IntelSaGopDriver.sdl, IntelSaGopPolicy.c, 
//               IntelSaGopSetup.c, IntelSaGopSetup.h,
// IntelSaGopSetup.mak,
//               IntelSaGopSetup.sd, IntelSaGopSetup.sdl,
// IntelSaGopSetup.uni, 
//               IntelSaGopSwitch.c, IntelSaGopDriver.h, NBPlatformData.h
// 
// 1     3/08/12 10:57p Yurenlai
// [TAG]         None
// [Category]    Improvement
// [Description] Create Haswell Intel SA GOP Driver module part.
//               Notice : IntelGopDriver.efi and vbt.bin is dummy files.
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:	IntelSaGopDriver.h
//
// Description:	GOP Specific Setup Variables and Structures
//
//<AMI_FHDR_END>
//*************************************************************************

#ifndef _PLATFORM_GOP_POLICY_PROTOCOL_H_
#define _PLATFORM_GOP_POLICY_PROTOCOL_H_

#define EFI_PLATFORM_GOP_POLICY_PROTOCOL_GUID \
  { 0xec2e931b, 0x3281, 0x48a5, 0x81, 0x7, 0xdf, 0x8a, 0x8b, 0xed, 0x3c, 0x5d }

#define GOP_DISPLAY_BRIGHTNESS_PROTOCOL_GUID \
  { 0x6ff23f1d, 0x877c, 0x4b1b, 0x93, 0xfc, 0xf1, 0x42, 0xb2, 0xee, 0xa6, 0xa7 }

#define GOP_DISPLAY_BIST_PROTOCOL_GUID \
  { 0xf51dd33a, 0xe57f, 0x4020, 0xb4, 0x66, 0xf4, 0xc1, 0x71, 0xc6, 0xe4, 0xf7 }

#define PLATFORM_GOP_POLICY_PROTOCOL_REVISION_01 0x01
#define PLATFORM_GOP_POLICY_PROTOCOL_REVISION_02 0x0222

#define GOP_DISPLAY_BRIGHTNESS_PROTOCOL_REVISION_01 0x01

#define GOP_DISPLAY_BIST_PROTOCOL_REVISION_01 0x01

#pragma pack(1)

typedef
struct _GOP_DISPLAY_BRIGHTNESS_PROTOCOL GOP_DISPLAY_BRIGHTNESS_PROTOCOL;

typedef
struct _GOP_DISPLAY_BIST_PROTOCOL GOP_DISPLAY_BIST_PROTOCOL;

typedef enum {
   LidClosed,
   LidOpen,
   LidStatusMax
} LID_STATUS;

typedef enum {
   Docked,
   UnDocked,
   DockStatusMax
} DOCK_STATUS;

typedef
EFI_STATUS
(EFIAPI *GET_PLATFORM_LID_STATUS) (
   OUT LID_STATUS *CurrentLidStatus
);

typedef
EFI_STATUS
(EFIAPI *GET_VBT_DATA) (
   OUT EFI_PHYSICAL_ADDRESS *VbtAddress,
   OUT UINT32 *VbtSize
);

typedef
EFI_STATUS
(EFIAPI *GET_PLATFORM_DOCK_STATUS) (
   OUT DOCK_STATUS CurrentDockStatus
);

typedef
EFI_STATUS
(EFIAPI *GET_MAXIMUM_BRIGHTNESS_LEVEL) (
   IN GOP_DISPLAY_BRIGHTNESS_PROTOCOL *This,
   OUT UINT32 *MaxBrightnessLevel
);

typedef
EFI_STATUS
(EFIAPI *GET_CURRENT_BRIGHTNESS_LEVEL) (
   IN GOP_DISPLAY_BRIGHTNESS_PROTOCOL *This,
   OUT UINT32 *CurrentBrightnessLevel
);

typedef
EFI_STATUS
(EFIAPI *SET_BRIGHTNESS_LEVEL) (
   IN GOP_DISPLAY_BRIGHTNESS_PROTOCOL *This,
   IN UINT32 BrightnessLevel
);

typedef
EFI_STATUS
(EFIAPI *ENABLE_BIST) (
   IN GOP_DISPLAY_BIST_PROTOCOL *This
);

typedef
EFI_STATUS
(EFIAPI *DISABLE_BIST) (
   IN GOP_DISPLAY_BIST_PROTOCOL *This
);

#pragma pack()

typedef struct _PLATFORM_GOP_POLICY_PROTOCOL {
  UINT32                             Revision;
  GET_PLATFORM_LID_STATUS            GetPlatformLidStatus;
  GET_VBT_DATA                       GetVbtData;
  GET_PLATFORM_DOCK_STATUS           GetPlatformDockStatus;
} PLATFORM_GOP_POLICY_PROTOCOL;

typedef struct _GOP_DISPLAY_BRIGHTNESS_PROTOCOL {
  UINT32                             Revision;
  GET_MAXIMUM_BRIGHTNESS_LEVEL       GetMaxBrightnessLevel;
  GET_CURRENT_BRIGHTNESS_LEVEL       GetCurrentBrightnessLevel;
  SET_BRIGHTNESS_LEVEL               SetBrightnessLevel;
} GOP_DISPLAY_BRIGHTNESS_PROTOCOL;

typedef struct _GOP_DISPLAY_BIST_PROTOCOL{
  UINT32                             Revision;
  ENABLE_BIST                        EnableBist;
  DISABLE_BIST                       DisableBist;
} GOP_DISPLAY_BIST_PROTOCOL;

#endif
//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
