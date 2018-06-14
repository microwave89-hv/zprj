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
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/Platform/PlatformSetup.h 4     1/15/13 5:47a Alanlin $
//
// $Revision: 4 $
//
// $Date: 1/15/13 5:47a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/Platform/PlatformSetup.h $
// 
// 4     1/15/13 5:47a Alanlin
// [TAG] None
// [Category] Normal
// [Severity] Normal
// [Description] Add setup item and setting for DPTF
// [Files] Acpiplatform.c, Acpiplatform.sd, Acpiplatform.uni,
// PlatformSetup.h
// 
// 3     10/31/12 4:43a Alanlin
// [TAG]         None
// [Category]    Improvement
// [Severity]    Normal
// [Description] Fine tune Platform Board Information.
// 
// 2     7/27/12 5:11a Yurenlai
// [TAG]         None
// [Category]    Improvement
// [Description] Create DPTF and CPPC setup item.
// [Files]       AcpiPlatform.c, AcpiPlatform.sd, AcpiPlatform.uni,
// PlatformSetup.h
// 
// 1     2/09/12 12:31a Yurenlai
// Initial check in.
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:	PlatformSetup.h
//
// Description:	OEM Specific Setup Variables and Structures
//
//<AMI_FHDR_END>
//*************************************************************************
#ifndef _OEMSETUP_H_
#define _OEMSETUP_H_
#ifdef __cplusplus
extern "C" {
#endif

  #pragma pack(1)

  typedef struct _SETUP_PLATFORM_DATA
  {

    UINT8 GbePciePortNum;
    UINT8 PlatformFlavor;
    UINT8 PcieSBDE;
    UINT8 PegPresent[4];
    UINT8 DimmPresent[4];
    UINT8 IGFXAvailable;
    UINT8 VTdAvailable;
    UINT8 PlatformSupportCppc;
    UINT8 PlatformSupportRtD3;
    UINT8 LPMSupport;
  }SETUP_PLATFORM_DATA;

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
