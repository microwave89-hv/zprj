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
// $Header: /Alaska/BIN/Chipset/Intel/NorthBridge/Haswell/Intel SystemAgent NB Chipset/NB Protocols/NBPlatformData.h 5     1/28/13 3:36a Jeffch $
//
// $Revision: 5 $
//
// $Date: 1/28/13 3:36a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Chipset/Intel/NorthBridge/Haswell/Intel SystemAgent NB Chipset/NB Protocols/NBPlatformData.h $
// 
// 5     1/28/13 3:36a Jeffch
// [TAG]          None
// [Severity]     Important
// [Description]  Update SA RC 1.0.
// [Files]        NBPei.c; GetSetupData.c; NbSetupData.h; NBDXE.c; NB.sd;
// NB.uni;
// 
// 4     12/24/12 2:53a Jeffch
// [TAG]         None
// [Category]    Improvement
// [Description] added ULT SKU auto disable PEG.
// [Files]        NBPei.c; NBDxe.c; NbPlatform.h; NB.sd;
// 
// 3     11/29/12 2:30a Jeffch
// [TAG]         None
// [Category]    Improvement
// [Description] added bootime check IGFX Available.
// [Files]        NBDxe.c; NbPlatform.h; NB.sd;
// 
// 2     8/14/12 4:42a Yurenlai
// [TAG]         None
// [Severity]    Important
// [Description] Implemented BIOS Integration Guide Rev 1.0 to Intel SA
// GOP driver.
// [Files]       IntelSaGopDriver.cif, IntelSaGopDriver.mak,
// IntelSaGopDriver.sdl, 
//               IntelSaGopPolicy.c, IntelSaGopSetup.c, IntelSaGopSetup.h,
// IntelSaGopSetup.mak, IntelSaGopSetup.sd, IntelSaGopSetup.sdl, 
//               IntelSaGopSetup.uni, IntelSaGopSwitch.c,
// IntelSaGopDriver.h, 
//               NBPlatformData.h
// 
// 1     2/08/12 4:35a Yurenlai
// Intel Haswell/NB eChipset initially releases.
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:	NBPlatformData.h
//
// Description:	NB Specific Setup Variables and Structures
//
//<AMI_FHDR_END>
//*************************************************************************
#ifndef _NB_PLATFORM_DATA_H_
#define _NB_PLATFORM_DATA_H_
#ifdef __cplusplus
extern "C" {
#endif

#ifndef EXIT_PM_AUTH_PROTOCOL_GUID
#define EXIT_PM_AUTH_PROTOCOL_GUID \
    { 0xd088a413, 0xa70, 0x4217, 0xba, 0x55, 0x9a, 0x3c, 0xb6, 0x5c, 0x41, 0xb3 };
#endif

  #pragma pack(1)

  typedef struct _NB_PLATFORM_DATA
  {
    UINT8 DimmPresent[4];
    UINT8 IGFXCapability;
    UINT8 IGFXAvailable;
    UINT8 IGFXGopAvailable;
    UINT8 PegAvailable;
    UINT8 VTdAvailable;
    UINT8 UserBoard;
    UINT8 PresentCPU;
    UINT8 XmpProfile1;
    UINT8 XmpProfile2;
    UINT8 DDR3Type;
  }NB_PLATFORM_DATA;

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
