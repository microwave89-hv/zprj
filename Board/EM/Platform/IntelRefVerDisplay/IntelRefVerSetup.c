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
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/Platform/IntelRefVerDisplay/IntelRefVerSetup.c 5     7/11/12 4:01a Yurenlai $
//
// $Revision: 5 $
//
// $Date: 7/11/12 4:01a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/Platform/IntelRefVerDisplay/IntelRefVerSetup.c $
// 
// 5     7/11/12 4:01a Yurenlai
// [TAG]         None
// [Category]    Improvement
// [Description] Corrected Setup RefCcode Version info.
// [Files]       IntelRefVerSetup.cm IntelRefVerDisplay.sd
// 
// 4     6/13/12 8:51a Yurenlai
// [TAG]         None
// [Description] 01. Implement Intel Rapid Start Technology RC version
// info.
//               02. Remove DPTF and TxT RefCode version in setup, because
// they are not separate components.
// [Files]       IntelRefVerDisplay.mak, IntelRefVerDisplay.sd,
// IntelRefVerDisplay.uni, IntelRefVerSetup.c
// 
// 3     4/25/12 1:22p Yurenlai
// [TAG]         None
// [Category]    Improvement
// [Description] Corrected Setup RC Version info.
// [Files]       IntelRefVerDisplay.mak, IntelRefVerSetup.c, AcpiAsl.sdl
// 
// 2     2/24/12 1:28a Yurenlai
// Initial IntelRefVerDisplay midule part.
// 
// 1     2/09/12 12:39a Yurenlai
// Initial check in.
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:  IntelRefVerSetup.c
//
// Description:	Display the verison of Intel RC drivers
//
//<AMI_FHDR_END>
//*************************************************************************

//----------------------------------------------------------------------------
// Include(s)
//----------------------------------------------------------------------------
#include <Setup.h>
#include <SetupStrTokens.h>
#include <AmiDxeLib.h>
#include <Token.h>
#if defined (INTEL_CPURC_SUPPORT) && INTEL_CPURC_SUPPORT
#include <CpuInfo\CpuInfo.h>
#endif
#include <SaInfo\SaInfo.h>
#include <PchInfo\PchInfo.h>
#include <AcpiInfo\AcpiInfo.h>
#if defined (iME_SUPPORT) && iME_SUPPORT
#include <MeRcInfo\MeRcInfo.h>
#endif
#if defined (IntelTXT_SUPPORT) && IntelTXT_SUPPORT
#include <TxtInfo\TxtInfo.h>
#endif
#if defined (DigitalThermalSensor_SUPPORT) && DigitalThermalSensor_SUPPORT
#include <DtsInfo\DtsInfo.h>
#endif
#if defined (RapidStart_SUPPORT) && RapidStart_SUPPORT
#include <RapidStartInfo\RapidStartInfo.h>
#endif

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        UpdateStringValue
//
// Description: Update the value of Intel RC drivers string 
//
// Input:       UINT32      RCVersion - Intel RC driver version
//              STRING_REF  StrRef - String Token defining which string in the database
//
// Output:      VOID
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
UpdateStringValue(
    EFI_HII_HANDLE      HiiHandle,
    UINT32              RCVersion,
    STRING_REF          StrRef
)
{
  UINT8  x, y, z, w;

  x = (UINT8) ((RCVersion & 0xFF000000) >> 24);
  y = (UINT8) ((RCVersion & 0xFF0000) >> 16);
  z = (UINT8) ((RCVersion & 0xFF00) >> 8);
  w = (UINT8) ((RCVersion & 0xFF));

  InitString ( HiiHandle,
               StrRef,
               L"%d.%d.%d.%d",
               x, y, z, w);
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        InitIntelVersionInfo
//
// Description: This function will fullfill the puspose to retrive the version 
//              of Intel RC Drivers and put into variables of IntelRefVerDisplay.uni file.
//
// Input:       EFI_HII_HANDLE HiiHandle
//
// Output:      VOID
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
InitIntelVersionInfo(
    EFI_HII_HANDLE      HiiHandle,
    UINT16              Class
)
{
  EFI_STATUS                Status;
#if defined (INTEL_CPURC_SUPPORT) && INTEL_CPURC_SUPPORT
  EFI_GUID                  gDxeCpuInfoProtocolGuid  = DXE_CPU_INFO_PROTOCOL_GUID;
  DXE_CPU_INFO_PROTOCOL     *CpuInfo;
#endif
  EFI_GUID                  gEfiSaInfoProtocolGuid   = EFI_SA_INFO_PROTOCOL_GUID;
  EFI_SA_INFO_PROTOCOL      *SaInfo;
  EFI_GUID                  gEfiPchInfoProtocolGuid  = EFI_PCH_INFO_PROTOCOL_GUID;
  EFI_PCH_INFO_PROTOCOL     *PchInfo;
  EFI_GUID                  gEfiAcpiInfoProtocolGuid = EFI_ACPI_INFO_PROTOCOL_GUID;
  EFI_ACPI_INFO_PROTOCOL    *AcpiInfo;
#if defined (iME_SUPPORT) && iME_SUPPORT
  EFI_GUID                  gEfiMeRcInfoProtocolGuid = EFI_ME_RC_INFO_PROTOCOL_GUID;
  EFI_ME_RC_INFO_PROTOCOL   *MeInfo;
#endif
#if defined (DigitalThermalSensor_SUPPORT) && DigitalThermalSensor_SUPPORT
  EFI_GUID                  gEfiDtsInfoProtocolGuid  = EFI_DTS_INFO_PROTOCOL_GUID;
  EFI_DTS_INFO_PROTOCOL     *DtsInfo;
#endif
#if defined (RapidStart_SUPPORT) && RapidStart_SUPPORT
  EFI_GUID                  gRapidStartInfoProtocolGuid    = RAPID_START_INFO_PROTOCOL_GUID;
  RAPID_START_INFO_PROTOCOL *RSTInfo;
#endif

  if (Class != ADVANCED_FORM_SET_CLASS) {
      return;
  }

#if defined (INTEL_CPURC_SUPPORT) && INTEL_CPURC_SUPPORT
  Status = pBS->LocateProtocol(&gDxeCpuInfoProtocolGuid,
                               NULL,
                               &CpuInfo);
  if (!EFI_ERROR (Status)) {
    UpdateStringValue(HiiHandle,
                      CpuInfo->RcVersion, 
                      STRING_TOKEN (STR_INTEL_CPU_RC_VER_VALUE));
  }
#endif

  // System Agent RefCode Version.
  Status = pBS->LocateProtocol(&gEfiSaInfoProtocolGuid,
                               NULL,
                               &SaInfo);
  if (!EFI_ERROR (Status)) {
    UpdateStringValue(HiiHandle, 
                      SaInfo->RCVersion, 
                      STRING_TOKEN (STR_INTEL_SA_RC_VER_VALUE));
  }

  // Pch RefCode Version.
  Status = pBS->LocateProtocol(&gEfiPchInfoProtocolGuid,
                               NULL,
                               &PchInfo);
  if (!EFI_ERROR (Status)) {
    UpdateStringValue(HiiHandle,
                      PchInfo->RCVersion,
                      STRING_TOKEN (STR_INTEL_PCH_RC_VER_VALUE));
  }

  // ACPI RefCode Version.
  Status = pBS->LocateProtocol(&gEfiAcpiInfoProtocolGuid,
                               NULL,
                               &AcpiInfo);
  if (!EFI_ERROR (Status)) {
    UpdateStringValue(HiiHandle,
                      AcpiInfo->RCVersion, 
                      STRING_TOKEN (STR_INTEL_ACPI_RC_VER_VALUE));
  };

#if defined (iME_SUPPORT) && iME_SUPPORT
  Status = pBS->LocateProtocol(&gEfiMeRcInfoProtocolGuid,
                               NULL,
                               &MeInfo);
  if (!EFI_ERROR (Status)) {
    UpdateStringValue(HiiHandle,
                      MeInfo->RCVersion, 
                      STRING_TOKEN (STR_INTEL_ME_RC_VER_VALUE));
  }
#endif

#if defined (DigitalThermalSensor_SUPPORT) && DigitalThermalSensor_SUPPORT
  Status = pBS->LocateProtocol(&gEfiDtsInfoProtocolGuid,
                               NULL,
                               &DtsInfo);
  if (!EFI_ERROR (Status)) {
    UpdateStringValue(HiiHandle,
                      DtsInfo->RCVersion, 
                      STRING_TOKEN (STR_INTEL_DTS_RC_VER_VALUE));
  }
#endif

#if defined (RapidStart_SUPPORT) && RapidStart_SUPPORT
  Status = pBS->LocateProtocol(&gRapidStartInfoProtocolGuid,
                               NULL,
                               &RSTInfo);
  if (!EFI_ERROR (Status)) {
    UpdateStringValue(HiiHandle,
                      RSTInfo->RCVersion, 
                      STRING_TOKEN (STR_INTEL_RST_RC_VER_VALUE));
  }
#endif

  return;
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
