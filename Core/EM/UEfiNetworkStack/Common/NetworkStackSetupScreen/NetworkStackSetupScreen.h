//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
// $Header: /Alaska/BIN/Modules/Network/UEFINetworkStack II/Common/NetworkStackSetupScreen/NetworkStackSetupScreen.h 7     1/08/14 5:27a Anushav $
//
// $Revision: 7 $
//
// $Date: 1/08/14 5:27a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/Network/UEFINetworkStack II/Common/NetworkStackSetupScreen/NetworkStackSetupScreen.h $
// 
// 7     1/08/14 5:27a Anushav
// [TAG]  		EIP148764 
// [Category]  	Improvement
// [Description]  	Add Media Detect Time setup option.
// [Files]  		PxeBcImpl.c,
// PxeBcDriver.c,
// NetworkStackSetupScreen.uni,
// NetworkStackSetupScreen.sd,
// NetworkStackSetup.h,
// NetworkStackSetupScreen.c.
// 
// 6     3/01/13 3:29a Nareshk
// [TAG]-EIP113577
// [Category]-IMPROVEMENT
// [Description]-Support to Handle ESC key to abort PXE boot.
// [Files]-SnpDxe.efi, SnpDxeIa32.efi, UefiPxeBcDxe.efi,
// UefiPxeBcDxeIa32.efi, NetworkStackSetupScreen.h,
// NetworkStackSetupScreen.sd and NetworkStackSetupScreen.uni
// 
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:  NetworkStackSetupScreen.h
//
// Description:	Network stack setup data structure definintion
//
//<AMI_FHDR_END>
//**********************************************************************

#pragma  pack (1)
typedef struct{
  UINT8             Enable;
  UINT8             Ipv4Pxe;
  UINT8             Ipv6Pxe;
  UINT8             IpsecCertificate;
  UINT8             PxeBootWaitTime;
  UINT8             MediaDetectTime;
} NETWORK_STACK;
#pragma  pack ()

#define NETWORK_STACK_GUID \
  { 0xD1405D16, 0x7AFC, 0x4695, 0xBB, 0x12, 0x41, 0x45, 0x9D, 0x36, 0x95, 0xA2 }

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************