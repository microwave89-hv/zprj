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
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/MeWrapper/Smbios131/Smbios131.c 7     3/06/13 4:12a Klzhan $
//
// $Revision: 7 $
//
// $Date: 3/06/13 4:12a $
//
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/MeWrapper/Smbios131/Smbios131.c $
// 
// 7     3/06/13 4:12a Klzhan
// Spec update : PlatformBrand = 5 means SBA
// 
// 6     2/18/13 2:25a Klzhan
// Improvement : Checking SBA Platform.
// 
// 5     1/25/13 4:27a Klzhan
// Return EFI_SUCCESS in entrypoint.
// 
// 4     12/18/12 2:29a Klzhan
// [TAG]  		EIP109707
// [Category]  	Spec Update
// [Severity]  	Important
// [Description]  	Update ME RC 0.81
// [Files]  		Smbios131.sdl
// Smbios131.mak
// Smbios131.c
// Smbios131.dxs
// Smbios131.h
// Smbios131.cif
// 
// 3     7/02/12 11:38p Klzhan
// [TAG]  		EIP94113
// [Category]  	Spec Update
// [Severity]  	Important
// [Description]  	Update ME RC0.6
// [Files]  		Smbios131.sdl
// Smbios131.mak
// Smbios131.c
// Smbios131.dxs
// Smbios131.h
// Smbios131.cif
// 
// 2     4/24/12 12:32a Klzhan
// Update modulepart to latest
// 
// 1     2/08/12 1:07a Klzhan
// Initial Check in 
// 
// 6     7/26/11 9:57a Klzhan
// Create token for some Bios capabilities parameters.
// 
// 5     7/26/11 8:37a Klzhan
// [TAG]  		EIP64542
// [Category]  	Improvement
// [Description]  	Replace Getvariable by GetNbSetupdata.
// [Files]  		Smbios131.sdl
// Smbios131.mak
// Smbios131.c
// Smbios131.dxs
// Smbios131.h
// Smbios131.cif
// 
// 4     7/11/11 5:40a Klzhan
// Close Event after SMBIOS 131 created.
// 
// 3     7/08/11 4:23a Klzhan
// [TAG]  		EIP64189
// [Category]  	Spec Update
// [Severity]  	Important
// [Description]  	Update ME RC to 0.7
// 
// 2     5/19/11 4:39a Klzhan
// Improvement : Fill MEBX version with EFI MEBX.
// 
// 1     2/25/11 1:40a Klzhan
// Initial Check-in
// 
// 2     12/16/10 4:00a Klzhan
// [TAG]  		EIP50237
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	Txt Support is not been set in SMBIOS type 131
// [RootCause]  	SETUP_CPU_FEATURES has been changed.
// [Solution]  	Include PlatformCPULib.h
// [Files]  		Smbios131.c and Smbios131.h
// 
// 1     12/03/10 5:09a Klzhan
// Initial Check-in.
// 
//
//**********************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:            Smbios131.c
//
// Description:     Create SMbios type 131.
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#define _SMBIOS_GUID_H_
#define __EDKII_GLUE_MEMORY_ALLOCATION_LIB_H__
#define __EDKII_GLUE_BASE_MEMORY_LIB_H__

#include "Smbios131.h"
#include <Protocol\GlobalNvsArea\GlobalNvsArea.h>
#include "MePlatformPolicy.h"
#if EFI_SPECIFICATION_VERSION>0x20000
#include "SaAccess.h"
#include "PchAccess.h"
#else
#include "Efi.h"
#include "EfiDriverLib.h"
#include "SaAccess.h"
#include "PchAccess.h"
#include "EdkIIGluePcd.h"
#include "EdkIIGluePcdPciExpressLib.h"
#include "EdkIIGlueConfig.h"
#include "EdkIIGlueIoLib.h"
#include "EdkIIGluePciExpressLib.h"
#include "EdkIIGlueUefiLib.h"
#define __UEFI_HII__H__
#define __HII_PROTOCOL_H__
#define _HII_H_
#define __FORM_CALLBACK_PROTOCOL_H__
#endif
#define SETUP_GUID { 0xEC87D643, 0xEBA4, 0x4BB5, 0xA1, 0xE5, 0x3F, 0x3E, 0x36, 0xB2, 0x0D, 0xA9 }


#define ME_INFO_SETUP_GUID \
  {0x78259433, 0x7B6D, 0x4DB3, 0x9A, 0xE8, 0x36, 0xC4, 0xC2, 0xC3, 0xA1, 0x7D}

#include EFI_PROTOCOL_CONSUMER (MebxProtocol)

EFI_GUID  gSetupGuid  = SETUP_GUID;
EFI_GUID  gMeSetupInfoGuid  = ME_INFO_SETUP_GUID;
EFI_GUID  gEfiSmbiosProtocolGuid  = EFI_SMBIOS_PROTOCOL_GUID;
EFI_GUID  gEfiEventReadyToBootGuid = EFI_EVENT_GROUP_READY_TO_BOOT;
EFI_GUID gEfiMeBiosExtensionSetupGuid 	= EFI_ME_BIOS_EXTENSION_SETUP_GUID;
CHAR16   gEfiMeBiosExtensionSetupName[] = EFI_ME_BIOS_EXTENSION_SETUP_VARIABLE_NAME;
EFI_GUID gEfiGlobalVariableGuid = EFI_GLOBAL_VARIABLE_GUID;
UINT8    METype = 0;
EFI_EVENT                       mLegacyBootEvent;
MEFWCAPS_SKU                    gMeFwCapsSkuData;
#if VA_SUPPORT
EFI_GUID gEfiVaNVMVariableGuid = EFI_VA_NVM_VARIABLE_GUID;
#endif
UINT8   TdtWwanSuport = 0;
EFI_RUNTIME_SERVICES  *gRT;
EFI_BOOT_SERVICES     *gBS;

EFI_STATUS
GetRawImage (
  IN      EFI_GUID       *NameGuid,
  IN OUT  VOID           **Buffer,
  IN OUT  UINTN          *Size
  )
/*++

Routine Description:

  Loads binary from RAW section of main firwmare volume

Arguments:

  NameGuid  - The guid of binary file
  Buffer    - Returns a pointer to allocated memory. Caller must free it when done.
  Size      - Returns the size of the binary loaded into the buffer.

Returns:

  EFI_NOT_FOUND  - Can't found the binary.
  EFI_LOAD_ERROR - Load fail.
  EFI_SUCCESS    - Load success.

--*/
{
  EFI_STATUS                    Status;
  UINTN                         HandleCount;
  UINTN                         Index;
  EFI_FIRMWARE_VOLUME_PROTOCOL  *Fv;
  EFI_HANDLE                    *HandleBuff;
  UINT32                        AuthenticationStatus;

  Status = gBS->LocateHandleBuffer (
                  ByProtocol,
                  &gEfiFirmwareVolumeProtocolGuid,
                  NULL,
                  &HandleCount,
                  &HandleBuff
                  );
  if (EFI_ERROR (Status) || HandleCount == 0) {
    return EFI_NOT_FOUND;
  }
  //
  // Find desired image in all Fvs
  //
  for (Index = 0; Index < HandleCount; Index++) {
    Status = gBS->HandleProtocol (
                    HandleBuff[Index],
                    &gEfiFirmwareVolumeProtocolGuid,
                    &Fv
                    );

    if (EFI_ERROR (Status)) {
      if (HandleBuff != NULL) {
        gBS->FreePool (HandleBuff);
      }

      return EFI_LOAD_ERROR;
    }
    //
    // Try a raw file
    //
    Status = Fv->ReadSection (
                  Fv,
                  NameGuid,
                  EFI_SECTION_RAW,
                  0,
                  Buffer,
                  Size,
                  &AuthenticationStatus
                  );

    if (!EFI_ERROR (Status)) {
      break;
    }
  }

  if (HandleBuff != NULL) {
    gBS->FreePool (HandleBuff);
  }

  if (Index >= HandleCount) {
    return EFI_NOT_FOUND;
  }

  return EFI_SUCCESS;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   UpdateSmbios131Table
//
// Description: SMBIOS tables 83 are filled here
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
VOID
MePlatformCapabilities (
  EFI_MISC_OEM_TYPE_0x83    *Type131
)
{
  ME_INFO_SETUP_DATA        MeInfoSetupData;
  PLATFORM_TYPE_RULE_DATA   PlatformTypeDate;   
  EFI_STATUS                Status;
  UINTN                     DataSize;

  DataSize = sizeof (ME_INFO_SETUP_DATA);
  Status = gRT->GetVariable (
                    L"MeInfoSetup",
                    &gMeSetupInfoGuid,
                    NULL,
                    &DataSize,
                    &MeInfoSetupData
                    );
  if (EFI_ERROR(Status)) return ;
  Type131->MeCapabilities.MeEnabled = 1;
  Type131->MeCapabilities.MeMajorVer = MeInfoSetupData.MeMajor;
  Type131->MeCapabilities.MeMinorVer = MeInfoSetupData.MeMinor;
  Type131->MeCapabilities.MeBuildNo = MeInfoSetupData.MeBuildNo;
  Type131->MeCapabilities.MeHotFixNo = MeInfoSetupData.MeHotFix;
  Type131->MeCapabilities.AtSupported = gMeFwCapsSkuData.Fields.IntelAT;
  Type131->MeCapabilities.IntelKVM = gMeFwCapsSkuData.Fields.KVM;
  Status = HeciGetPlatformType(&PlatformTypeDate);
  if (EFI_ERROR(Status)) return ;
  if (PlatformTypeDate.Fields.PlatformBrand == 1) {
    Type131->MeCapabilities.IntelAmtFw = 1;
    Type131->MeCapabilities.LocalWakeupTimer = 1;
  }
  if (PlatformTypeDate.Fields.PlatformBrand == 2) 
    Type131->MeCapabilities.IntelAmtFwStandard = 1;

  if (PlatformTypeDate.Fields.PlatformBrand == 5) 
    Type131->MeCapabilities.IntelSmallBusiness = 1;

  METype = (UINT8)PlatformTypeDate.Fields.IntelMeFwImageType;
}
  
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   UpdateSmbios131Table
//
// Description: SMBIOS tables 83 are filled here
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
UpdateSmbios131Table(
        EFI_EVENT           Event,
        VOID                *ParentImageHandle
)
{
  EFI_STATUS                Status;
  EFI_MISC_OEM_TYPE_0x83    Data83;
  EFI_SMBIOS_PROTOCOL       *mSmbiosProtocol;
  UINT64                    Ia32FeatureControl;
  EFI_CPUID_REGISTER        CpuidRegs ;
#if VA_SUPPORT
  EFI_VA_NVM_VAR            VaNVMVar; 
#endif

  mSmbiosProtocol = NULL;
  Status = gBS->LocateProtocol(
    &gEfiSmbiosProtocolGuid,
    NULL,
    &mSmbiosProtocol
  );
  if (EFI_ERROR(Status)) return Status;

  //Clear all data
  gBS->SetMem (&Data83, sizeof(EFI_MISC_OEM_TYPE_0x83), 0);

// Data83

  Data83.Header.Type = 0x83;
  Data83.Header.Length = 0x40;
  Data83.Header.Handle = 0;
  gBS->CopyMem (
      Data83.vProSignature,
      vPro_Signature,
      sizeof (UINT32)
  );

  Ia32FeatureControl = EfiReadMsr(EFI_MSR_IA32_FEATURE_CONTROL);
  EfiCpuid (1, &CpuidRegs) ;  

//CPU
  Data83.CpuCapabilities.VMXState = (UINT32)(RShiftU64(Ia32FeatureControl, 2));
  Data83.CpuCapabilities.SMXState = (UINT32)(RShiftU64(Ia32FeatureControl, 1));

  if (CpuidRegs.RegEcx & BIT6) {
    Data83.CpuCapabilities.LtTxtCap = 1;
  } else {
    Data83.CpuCapabilities.LtTxtCap = 0;  
  }
  
  if ((Ia32FeatureControl & TXT_OPT_IN_VMX_AND_SMX_MSR_VALUE) == TXT_OPT_IN_VMX_AND_SMX_MSR_VALUE) {
    Data83.CpuCapabilities.LtTxtEnabled = 1;
  } else {
    Data83.CpuCapabilities.LtTxtEnabled = 0;
  }

  if (CpuidRegs.RegEcx & BIT5) {
    Data83.CpuCapabilities.VTxCap = 1;
  } else {
    Data83.CpuCapabilities.VTxCap = 0;
  }
  Data83.CpuCapabilities.VTxEnabled = (UINT32)(RShiftU64(Ia32FeatureControl, 2));

//Pch
  Data83.PchCapabilities.FunctionNumber = PCI_FUNCTION_NUMBER_PCH_LPC;
  Data83.PchCapabilities.DeviceNumber = PCI_DEVICE_NUMBER_PCH_LPC;
  Data83.PchCapabilities.BusNumber = DEFAULT_PCI_BUS_NUMBER_PCH;
  Data83.PchCapabilities.DeviceID = PchLpcPciCfg16(R_PCH_LPC_DEVICE_ID);
  Data83.PchCapabilities.Reserved = 0;

//Me
//Filled above along with Data82 table
  MePlatformCapabilities(&Data83);

// MEBX Version
  // Fill MEBX Version when ME FW is 5MB
  if(METype == 4)
  {
    EFI_MEBX_PROTOCOL *MebxProtocol;
    Status = gBS->LocateProtocol (&gEfiMebxProtocolGuid, NULL, &MebxProtocol);
    if (!EFI_ERROR (Status)) {
      Data83.vMEBX_Major = MebxProtocol->MebxVersion.Major;
      Data83.vMEBX_Minor = MebxProtocol->MebxVersion.Minor;
      Data83.vMEBX_HotFix = MebxProtocol->MebxVersion.Hotfix;
      Data83.vMEBX_Build = MebxProtocol->MebxVersion.Build;
    } else {
      Data83.vMEBX_Major = 0;
      Data83.vMEBX_Minor = 0;
      Data83.vMEBX_HotFix = 0;
      Data83.vMEBX_Build = 0;
    }
  }

//NetworkDevice
  Data83.NetworkDevice.FunctionNumber = PCI_FUNCTION_NUMBER_PCH_LAN;	//[2:0] PCI Device Function Number of Wired LAN
  Data83.NetworkDevice.DeviceNumber =	PCI_DEVICE_NUMBER_PCH_LAN;      //[7:3] PCI Device Device Number of Wired LAN
  Data83.NetworkDevice.BusNumber = PCI_BUS_NUMBER_PCH_LAN;		//[15:8] PCI Device Bus Number of Wired LAN
  Data83.NetworkDevice.DeviceID =   MmPci16( 0, DEFAULT_PCI_BUS_NUMBER_PCH, PCI_DEVICE_NUMBER_PCH_LAN, PCI_FUNCTION_NUMBER_PCH_LAN, R_PCH_LAN_DEVICE_ID );

//BIOS
  if(SetupSupportItem & BIT3)
     Data83.BiosCapabilities.VTxSupport = 1;

  if(SetupSupportItem & BIT1)
     Data83.BiosCapabilities.TxtSupport = 1;

  Data83.BiosCapabilities.Reserved1   = 0;
  Data83.BiosCapabilities.Reserved2   = 0;

  if(SetupSupportItem & BIT0)
     Data83.BiosCapabilities.VTdSupport = 1;

  if(SetupSupportItem & BIT2)
     Data83.BiosCapabilities.MeSupport = 0;

#if VA_SUPPORT
  //
  // Set Default Value for VA
  //
  Data83.BiosCapabilities.MaxVASupported = 7;   //None. Means BIOS do not support VA.

  //
  // Get VA Info
  //
  DataSize = sizeof(EFI_VA_NVM_VAR);
  Status = gRT->GetVariable (
        EFI_VA_NVM_VARIABLE_NAME,
        &gEfiVaNVMVariableGuid,
        NULL,
        &DataSize,
        &VaNVMVar
        );

  if (!EFI_ERROR(Status)) {
    if (VaNVMVar.VAVersion == EFI_VA30_VERSION) {
      Data83.BiosCapabilities.MaxVASupported = 1;
    } else if (VaNVMVar.VAVersion == EFI_VA26_VERSION) {
      Data83.BiosCapabilities.MaxVASupported = 0;
    }
  }
#endif

 // Get TDT Info
  if(Data83.MeCapabilities.AtSupported){
     Data83.BiosCapabilities.TdtPbaSupport = 1;
     Data83.BiosCapabilities.TdtWwanSuport = TdtWwanSuport;
  }
  Status = mSmbiosProtocol->SmbiosAddStructure((UINT8 *)&Data83, sizeof(EFI_MISC_OEM_TYPE_0x83));
  gBS->CloseEvent(Event);
  return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   AmtSmbios131EntryPoint
//
// Description: iAMT SMBIOS Type 131 driver entry point
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
AmtSmbios131EntryPoint(
	IN EFI_HANDLE           ImageHandle,
	IN EFI_SYSTEM_TABLE     *SystemTable
)
{
  EFI_STATUS                Status;
  DXE_MBP_DATA_PROTOCOL     *mBIOSPayLoad = NULL;

  EfiInitializeDriverLib (ImageHandle, SystemTable);

  Status = HeciGetFwCapsSku(&gMeFwCapsSkuData);
  if (EFI_ERROR(Status)) return Status;
  Status = EfiCreateEventReadyToBootEx(
                       EFI_TPL_CALLBACK,
                       UpdateSmbios131Table,
                       (VOID *)&ImageHandle,
                       &mLegacyBootEvent
      );
  ASSERT_EFI_ERROR (Status);
  Status = gBS->LocateProtocol (
               &gMeBiosPayloadDataProtocolGuid,
               NULL,
               &mBIOSPayLoad
               );
  if(!EFI_ERROR(Status))
  {
#if 0
    if(mBIOSPayLoad->MeBiosPayload.AtState.flags.WWAN3GPresent &&
      mBIOSPayLoad->MeBiosPayload.AtState.flags.WWAN3GOOB)
      TdtWwanSuport = 1;
#endif
  }
  return EFI_SUCCESS;
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