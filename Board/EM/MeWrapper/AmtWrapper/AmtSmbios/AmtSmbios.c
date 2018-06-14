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
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/AmtWrapper/AmtSmbios/AmtSmbios.c 4     6/21/13 3:39a Klzhan $
//
// $Revision: 4 $
//
// $Date: 6/21/13 3:39a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/AmtWrapper/AmtSmbios/AmtSmbios.c $
// 
// 4     6/21/13 3:39a Klzhan
// [TAG]  		EIPNone
// [Category]  	Spec Update
// [Severity]  	Minor
// [Description]  	ME FW drop support of type 129
// 
// 3     9/19/12 6:57a Klzhan
// Update IDER secure boot flag.
// 
// 2     4/24/12 12:43a Klzhan
// Update module to latest
// 
// 1     2/08/12 1:09a Klzhan
// Initial Check in 
// 
// 3     7/11/11 5:32a Klzhan
// Close Event after SMBIOS 129 130 created.
// 
// 2     5/03/11 6:19a Klzhan
// [TAG]  		EIP59457
// [Category]  	Bug Fix
// [RootCause]  	Copy wrong size in SMBios type 129.
// [Files]  		AmtSmbios.c
// 
// 1     2/25/11 1:44a Klzhan
// Initial Check-in
// 
// 1     12/03/10 5:11a Klzhan
// Initial Check-in.
//
//**********************************************************************
//
//<AMI_FHDR_START>
//---------------------------------------------------------------------------
// Name:		AMTSmbios.c
//
// Description:	AMT Smbios Functions.
//
//---------------------------------------------------------------------------
//<AMI_FHDR_END>
#include "AMTSmbios.h"
#include "Tiano.h"
#include "EfiDriverLib.h"
#include "SaAccess.h"
#include "PchAccess.h"
#include "EdkIIGluePcd.h"
#include "EdkIIGluePcdPciExpressLib.h"
#include "EdkIIGlueConfig.h"
#include "EdkIIGlueIoLib.h"
#include "EdkIIGluePciExpressLib.h"
#include "EdkIIGlueUefiLib.h"
#include "SbSetupData.h"
#include EFI_PROTOCOL_CONSUMER (MeBiosPayloadData)
EFI_GUID  gEfiSmbiosProtocolGuid  = EFI_SMBIOS_PROTOCOL_GUID;
EFI_GUID  gEfiEventReadyToBootGuid = EFI_EVENT_GROUP_READY_TO_BOOT;
EFI_GUID gEfiMeBiosExtensionSetupGuid 	= EFI_ME_BIOS_EXTENSION_SETUP_GUID;
CHAR16   gEfiMeBiosExtensionSetupName[] = EFI_ME_BIOS_EXTENSION_SETUP_VARIABLE_NAME;
EFI_GUID gEfiGlobalVariableGuid = EFI_GLOBAL_VARIABLE_GUID;

EFI_EVENT                       mLegacyBootEvent;

#if VA_SUPPORT
EFI_GUID gEfiVaNVMVariableGuid = EFI_VA_NVM_VARIABLE_GUID;
#endif

EFI_RUNTIME_SERVICES  *gRT;
EFI_BOOT_SERVICES     *gBS;
DXE_MBP_DATA_PROTOCOL MbpData;

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetMeFwInfoFromMBP
//
// Description: Get ME Fw Info From MBP data
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
GetMeFwInfoFromMBP (
  IN OUT ME_CAP *MECapability
  )
{
  MEFWCAPS_SKU            FwCapsSku;

  MECapability->MeEnabled = 1;

  FwCapsSku.Data          = MbpData.MeBiosPayload.FwCapsSku.FwCapabilities.Data;

  if (FwCapsSku.Fields.IntelAT) {
    MECapability->AtSupported = 1;
  }

  if (FwCapsSku.Fields.KVM) {
    MECapability->IntelKVM = 1;
  }

  switch (MbpData.MeBiosPayload.FwPlatType.RuleData.Fields.PlatformBrand) {
    case INTEL_AMT_BRAND:
      MECapability->IntelAmtFw        = 1;
      MECapability->LocalWakeupTimer  = 1;
      break;

    case INTEL_STAND_MANAGEABILITY_BRAND:
      MECapability->IntelAmtFwStandard = 1;
      break;

    case INTEL_SMALL_BUSINESS_TECHNOLOGY_BRAND:
      MECapability->IntelSmallBusiness = 1;
      break;
  }

  MECapability->MeMajorVer  = MbpData.MeBiosPayload.FwVersionName.MajorVersion;
  MECapability->MeMinorVer  = MbpData.MeBiosPayload.FwVersionName.MinorVersion;
  MECapability->MeBuildNo   = MbpData.MeBiosPayload.FwVersionName.BuildVersion;
  MECapability->MeHotFixNo  = MbpData.MeBiosPayload.FwVersionName.HotfixVersion;

  return EFI_SUCCESS;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   UpdateAmtSmbiosTable
//
// Description: SMBIOS tables 81, 82 and 83 are filled here
//
// Input:       EFI_EVENT           Event,
//              VOID                *ParentImageHandle
//
// Output:      EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
UpdateAmtSmbiosTable(
        EFI_EVENT           Event,
        VOID                *ParentImageHandle
)
{
  EFI_STATUS                Status;
  EFI_MISC_OEM_TYPE_0x81    Data81;
  EFI_MISC_OEM_TYPE_0x82    Data82;
  EFI_SMBIOS_PROTOCOL       *mSmbiosProtocol;
  UINT32                    Attributes;
  UINTN                     DataSize;
  ME_BIOS_EXTENSION_SETUP   MeBiosExtensionSetup;
  UINT32                    MeEnabled;
  ME_CAP                    MeCapabilities;
#if VA_SUPPORT
  EFI_VA_NVM_VAR            VaNVMVar; 
#endif


  Status = MePolicyLibInit();
  ASSERT_EFI_ERROR(Status);

  Status = AmtPolicyLibInit();
  ASSERT_EFI_ERROR(Status);

  mSmbiosProtocol = NULL;
  Status = gBS->LocateProtocol(
    &gEfiSmbiosProtocolGuid,
    NULL,
    &mSmbiosProtocol
  );
  ASSERT_EFI_ERROR(Status);

  //Clear all data
  gBS->SetMem (&Data81, sizeof(EFI_MISC_OEM_TYPE_0x81), 0);
  gBS->SetMem (&Data82, sizeof(EFI_MISC_OEM_TYPE_0x82), 0);
  gBS->SetMem (&MeCapabilities, sizeof(ME_CAP), 0);

  //fill
  Data81.Header.Type = 0x81;
  Data81.Header.Length = 8;
  Data81.Header.Handle = 0;
  Data81.DescString = 1;
  Data81.StructureVersion = 1;
  Data81.SystemId = 2;
  if(AsfSupported())
    Data81.Attribute = 1;
  else
    Data81.Attribute = 0;

  gBS->CopyMem (
      Data81.DescStringAscii,
      EFI_OEM_ASF_DESCRIPTIONSTRING,
      sizeof (EFI_OEM_ASF_DESCRIPTIONSTRING)
  );
    
  gBS->CopyMem (
      Data81.SystemIdAscii,
      EFI_OEM_ASF_SYSTEMIDSTRING,
      (sizeof (EFI_OEM_ASF_SYSTEMIDSTRING) - 1)
  );
  //
  Data82.Header.Type = 0x82;
  Data82.Header.Length = 0x14;
  Data82.Header.Handle = 0;
  gBS->CopyMem (
      Data82.AmtSignature,
      AMT_Signature,
      sizeof (UINT32)
  );

// Data82  
  
  if(AmtSupported()){
    MeEnabled = *((volatile UINT32 *)(UINTN)((PciMeRegBase) + FW_STATUS_REGISTER));
    //
    // Make sure Me is in normal mode & hasn't any error
    //
    if ((MeEnabled & 0xFF000) == 0) {
      Status = GetMeFwInfoFromMBP(&MeCapabilities);
      if (EFI_ERROR (Status)) {
        return Status;
      }
    }
   
    if( MeCapabilities.IntelAmtFw ==1) {
      Data82.AmtSupported = 1; 
    }

    Attributes  = EFI_VARIABLE_NON_VOLATILE;
    DataSize = sizeof (ME_BIOS_EXTENSION_SETUP);
    Status = gRT->GetVariable (
      gEfiMeBiosExtensionSetupName,
      &gEfiMeBiosExtensionSetupGuid,
      &Attributes,
      &DataSize,
      &MeBiosExtensionSetup
    );

    if (!EFI_ERROR(Status)) {
      if(MeCapabilities.IntelAmtFw == 1) {
        if(MeBiosExtensionSetup.PlatformMngSel & MNT_ON) {
          Data82.AmtEnabled    =  1;
        } else {
          Data82.AmtEnabled    =  0;
        }
        
        if(MeBiosExtensionSetup.AmtSolIder & IDER_ENABLE) {
          Data82.IderEnabled    =  1;
        } else {
          Data82.IderEnabled    =  0;
        }
  
        if (MeBiosExtensionSetup.AmtSolIder & SOL_ENABLE) {
          Data82.SolEnabled    =  1;
        } else {
          Data82.SolEnabled    =  0;
        }
        Data82.NetworkEnabled = 1;  // If AMT enabled, LAN is always enabled

      } 

      if(MeCapabilities.IntelKVM) {
        if (MeBiosExtensionSetup.KvmEnable & KVM_ENABLE) {
          Data82.KvmEnabled    =  1;
        } else {
          Data82.KvmEnabled    =  0;
        }
      } 
    }
  }
  else  {
    Data82.AmtEnabled = 0;
    Data82.IderEnabled = 0;
    Data82.SolEnabled = 0;
    Data82.KvmEnabled = 0;
    Data82.NetworkEnabled = 0;
  }
	
  Data82.ExtendedData = 0xA5;
  Data82.OemCapabilities1 = 0x2F;
  Data82.OemCapabilities2 = 0x02;
#if defined(SecureBoot_SUPPORT) && (SecureBoot_SUPPORT == 1)
  Data82.OemCapabilities3 = 1;
#else
  Data82.OemCapabilities3 = 0;
#endif
  Data82.OemCapabilities4 = 0;

  Status = mSmbiosProtocol->SmbiosAddStructure((UINT8 *)&Data82, sizeof(EFI_MISC_OEM_TYPE_0x82));
  gBS->CloseEvent(Event);
  return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   iAMTSMBiosDriverEntryPoint
//
// Description: iAMT SMBIOS driver entry point
//
// Input:       EFI_HANDLE           ImageHandle,
//              EFI_SYSTEM_TABLE     *SystemTable
//
// Output:      EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
AmtSmbiosEntryPoint(
	IN EFI_HANDLE           ImageHandle,
	IN EFI_SYSTEM_TABLE     *SystemTable
)
{
  EFI_STATUS                Status;
  DXE_MBP_DATA_PROTOCOL     *MbpDataBuf;
  EfiInitializeDriverLib (ImageHandle, SystemTable);

  Status = gBS->LocateProtocol (&gMeBiosPayloadDataProtocolGuid, NULL, &MbpDataBuf);

  gBS->CopyMem (
      &MbpData,
      MbpDataBuf,
      sizeof (DXE_MBP_DATA_PROTOCOL)
  );
  Status = EfiCreateEventReadyToBootEx(
                       EFI_TPL_CALLBACK,
                       UpdateAmtSmbiosTable,
                       (VOID *)&ImageHandle,
                       &mLegacyBootEvent
      );
  ASSERT_EFI_ERROR (Status);

  return Status;
}
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