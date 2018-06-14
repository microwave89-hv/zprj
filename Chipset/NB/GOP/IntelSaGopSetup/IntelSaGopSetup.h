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
// $Header: /Alaska/BIN/Chipset/Intel/NorthBridge/Haswell/IntelGopDriver/IntelSaGopSetup/IntelSaGopSetup.h 3     4/23/13 8:01a Ireneyang $
//
// $Revision: 3 $
//
// $Date: 4/23/13 8:01a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Chipset/Intel/NorthBridge/Haswell/IntelGopDriver/IntelSaGopSetup/IntelSaGopSetup.h $
// 
// 3     4/23/13 8:01a Ireneyang
// [TAG]          None
// [Severity]     Improvement
// [Description]  Support for BIST (Built-In Self Test) Protocol.
// [Files]        IntelSaGopSetup.c; IntelSaGopSetup.h;
// IntelSaGopSetup.sd;
//                IntelSaGopSetup.sd; IntelSaGopSetup.sdl; 
//                IntelSaGopSetup.uni; IntelSaGopDriver.h;  
// 
// 2     8/14/12 5:47a Yurenlai
// [TAG]         None
// [Severity]    Important
// [Description] Implemented BIOS Integration Guide Rev 1.0 to Intel SA
// GOP driver.
// [Files]       IntelSaGopDriver.cif, IntelSaGopDriver.mak,
//               IntelSaGopDriver.sdl, IntelSaGopPolicy.c,
// IntelSaGopSetup.c,
//               IntelSaGopSetup.h, IntelSaGopSetup.mak,
// IntelSaGopSetup.sd,
//               IntelSaGopSetup.sdl, IntelSaGopSetup.uni, 
//               IntelSaGopSwitch.c, IntelSaGopDriver.h, NBPlatformData.h
// 
// 1     3/08/12 10:55p Yurenlai
// [TAG]         None
// [Category]    Improvement
// [Description] Create Haswell Intel SA GOP Driver module part.
//               Notice : IntelGopDriver.efi and vbt.bin is dummy files.
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:	IntelSaGopSetup.h
//
// Description:	GOP Specific Setup Variables and Structures
//
//<AMI_FHDR_END>
//*************************************************************************
#ifndef _NB_GOP_PLATFORM_DATA_H_
#define _NB_GOP_PLATFORM_DATA_H_
#ifdef __cplusplus
extern "C" {
#endif

  #pragma pack(1)

  typedef struct _NB_GOP_PLATFORM_DATA
  {
    UINT8   BrightnessAvailable;
    UINT8   GopBistAvailable;
  }NB_GOP_PLATFORM_DATA;

  #pragma pack()

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
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
