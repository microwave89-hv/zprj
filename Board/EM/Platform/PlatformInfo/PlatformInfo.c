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
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/Platform/PlatformInfo/PlatformInfo.c 4     10/31/12 4:28a Alanlin $
//
// $Revision: 4 $
//
// $Date: 10/31/12 4:28a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/Platform/PlatformInfo/PlatformInfo.c $
// 
// 4     10/31/12 4:28a Alanlin
// [TAG]         None
// [Category]    Improvement
// [Description] Fine tune Platform Board Information.
// 
// 3     7/03/12 1:27a Yurenlai
// [TAG]         None
// [Category]    Improvement
// [Description] Update Shark Bay Client ACPI Reference Code Alpha 2
// 0.6.0.
// [Files]       ReferenceCode\AcpiTables\*.*, GlobalNvsArea.h,
// AcpiPlatform.c, PlatformInfo.c, PlatformEC.asl
// 
// 2     4/05/12 7:45a Yurenlai
// [TAG]         None
// [Category]    Improvement
// [Severity]    Important
// [Description] Fixed building error for Intel System Agent
// Label:"4.6.5.3_Intel_SA-RC_055_004".
// [Files]       PlatformSetupInfo.c, PlatformSetupInfo.mak,
// AcpiPlatform.c, PlatformInfo.c
// 
// 1     2/09/12 12:33a Yurenlai
// Initial check in.
// 
//*************************************************************************
//<AMI_FHDR_START>
//---------------------------------------------------------------------------
//
// Name:        PlatformInfo.c
//
// Description: Installs EFI_PLATFORM_INFO_PROTOCOL_GUID
//
//---------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "PlatformInfo.h"
#include "Token.h"
#include <AmiCspLib.h>
#include <AmiDxeLib.h>
#include <Setup.h>
#include <PlatformSetup.h>
#include <PchRegs.h>

EFI_GUID gPlatformInfoProtocolGuid = EFI_PLATFORM_INFO_PROTOCOL_GUID;

PLATFORM_INFO_PROTOCOL mPlatformInfoProtocol;

EFI_STATUS
PlatformInfoInit (
  IN EFI_HANDLE                         ImageHandle,
  IN EFI_SYSTEM_TABLE                   *SystemTable
  )
/*++

Routine Description:
  Entry point for the driver.

  This routine gets info from the PlatformInfoHob and produces a protocol 
  to be consumed by DXE drivers to identify platforms.

Arguments:

  ImageHandle  -  Image Handle.
  SystemTable  -  EFI System Table.
  
Returns:

  EFI_SUCCESS  -  Function has completed successfully.
  Others       -  All other error conditions encountered result in an ASSERT.
  
--*/
{
  EFI_STATUS                  Status;
  UINT16                      McDeviceId;
  UINT16                      LpcDeviceId;
  PCH_SERIES                  PchSeries = GetPchSeries();

  InitAmiLib(ImageHandle,SystemTable);
  //
  // Get PlatformInfo from the HOB data, fill up the protocol
  //
  mPlatformInfoProtocol.RevisonId      = PlatformInfo_RevisonId;
  mPlatformInfoProtocol.BoardId        = PlatformInfo_BoardId;
  mPlatformInfoProtocol.BoardRev       = PlatformInfo_BoardRev;

  // Read MC device ID
  McDeviceId = READ_PCI16_NB(R_SA_MC_DEVICE_ID);
  // Read PCH device ID
  LpcDeviceId = READ_PCI16_SB(R_PCH_LPC_DEVICE_ID);

  if(IS_SA_DEVICE_ID_MOBILE(McDeviceId)) {
      mPlatformInfoProtocol.PlatformFlavor = FlavorMobile;
      if (PchSeries == PchLp) {
      mPlatformInfoProtocol.BoardId        = BoardIdhiteTipMountain1;
      }
      mPlatformInfoProtocol.BoardRev       = (mPlatformInfoProtocol.BoardId  & 0xF0) >> 4;  

  } else if(IS_SA_DEVICE_ID_DESKTOP (McDeviceId)) {
      if(IS_PCH_LPT_LPC_DEVICE_ID_WS (LpcDeviceId)) {
          mPlatformInfoProtocol.PlatformFlavor = FlavorWorkStation;
      } else if(IS_PCH_LPT_LPC_DEVICE_ID_SERVER (LpcDeviceId)) {
          mPlatformInfoProtocol.PlatformFlavor = FlavorUpServer;
      } else {
          mPlatformInfoProtocol.PlatformFlavor = FlavorDesktop;
          mPlatformInfoProtocol.BoardId        = BoardIdFlatheadCreek;
          mPlatformInfoProtocol.BoardRev       = 0;
      }
  } else if(IS_SA_DEVICE_ID_SERVER (McDeviceId)) {
      mPlatformInfoProtocol.PlatformFlavor = FlavorUpServer;
  } else {
      mPlatformInfoProtocol.PlatformFlavor = FlavorDesktop;
  }

  //
  // Install the PlatformInfo Protocol.
  //
  Status = pBS->InstallProtocolInterface (
                  &ImageHandle,
                  &gPlatformInfoProtocolGuid,
                  EFI_NATIVE_INTERFACE,
                  &mPlatformInfoProtocol
                  );
  ASSERT_EFI_ERROR (Status);

  return EFI_SUCCESS;
}

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