//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1987-2013, American Megatrends, Inc.         **
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
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/Haswell/AMI Cpu PKG/CPU Board/CpuRcPolicyWrap/CpuRcPolicyPei.c 16    6/11/15 10:30p Crystallee $
//
// $Revision: 16 $
//
// $Date: 6/11/15 10:30p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/Haswell/AMI Cpu PKG/CPU Board/CpuRcPolicyWrap/CpuRcPolicyPei.c $
// 
// 16    6/11/15 10:30p Crystallee
// [TAG]  		EIP207854
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	Txt test fail with TCG2 module
// [RootCause]  	Tokne TCG_SUPPORT was removed.
// [Solution]  	Add TCG2Support token.
// 
// 15    4/10/15 3:15a Crystallee
// 
// 14    1/22/15 3:59a Crystallee
// [TAG]  		EIPNone
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	PowerConv and TimeConv parameters in
// AmiInternalFactoryTdcTdp Hob is incorrect.
// [RootCause]  	Read from wrong MSR.
// [Solution]  	The data should read from MSR 0x606.
// 
// 13    8/28/13 5:54a Crystallee
// [TAG]  		EIP134339
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	[Sharkbay]Build error after update Haswell Cpu module
// [RootCause]  	If token TCG_SUPPORT is disabled, TpmSupport setup data
// will not define, then cause built error.
// [Solution]  	Add token TCG_SUPPORT condition when use TpmSupport setup
// data.
// 
// 12    7/23/13 7:44a Crystallee
// [TAG]  		EIP128089
// [Category]  	Improvement
// [Description]  	TXT will be disabled and grayed out in Setup when TPM
// Support is disabled.
// 
// 11    2/22/13 1:54a Crystallee
// [TAG]  		EIP112238
// [Category]  	Improvement
// [Description]  	Refer Intel BIOS and provide setup items for Intel
// Haswell RC policy.
// 
// 10    1/23/13 2:58a Crystallee
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Create setup item for BootInLfm
// 
// 9     12/12/12 1:23a Davidhsieh
// [TAG]  		EIP108401
// [Category]  	Improvement
// [Description]  	Create setup item for VrMiscIoutOffsetSign
// 
// 8     12/03/12 9:50p Davidhsieh
// [TAG]  		EIP108401
// [Category]  	Improvement
// [Description]  	Create setup items for VrMiscIoutOffset,
// VrMiscIoutSlope and LakeTiny
// 
// 7     11/23/12 2:05a Hsingyingchung
// [TAG]  		EIP99095
// [Category]  	Improvement
// [Description]  	Update by XTU 4.X
// 
// 6     7/19/12 2:22a Davidhsieh
// [TAG]  		EIP95485
// [Category]  	Improvement
// [Description]  	Enable VT when TXT is enabled
// 
// 5     7/02/12 8:23a Davidhsieh
// 
// 4     6/19/12 8:25a Davidhsieh
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Only enable TXT while TCG also enable
// 
// 3     6/15/12 3:34a Davidhsieh
// [TAG]  		EIP89941
// [Category]  	Improvement
// [Description]  	Add Intel TXT setup item
// 
// 2     3/16/12 3:45a Davidhsieh
// Setup items create for CPU RC policy
// 
// 1     2/07/12 3:57a Davidhsieh
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:  CpuPolicyInitPei.c
//
// Description: PeiCpuPolicyInitList eLink interface & its default child procedure
// for setting up PEI_CPU_PLATFORM_POLICY_PPI.
//
//<AMI_FHDR_END>
//**********************************************************************
#include "EdkIIGluePeim.h"
#include "CpuPlatformPolicy.h"

#define VFRCOMPILE
#include "Include\Setup.h"
#undef VFRCOMPILE

#include "token.h"

#define MSR_FLEX_RATIO                  0x194
#define MSR_TURBO_RATIO_LIMIT           0x1AD
#define MSR_VR_CURRENT_CONFIG           0x601
#define MSR_PACKAGE_POWER_SKU_UNIT		0x606
#define MSR_PACKAGE_POWER_LIMIT         0x610

#pragma pack(push,1)
#define AMI_INTERNAL_FACTORY_TDC_TDP_HOB_GUID \
    {0x982d8c6f, 0xf6f6, 0x4135, 0xa3, 0x9, 0xa4, 0x59, 0x3e, 0xa5, 0x64, 0x17}

typedef struct {
    EFI_HOB_GUID_TYPE   EfiHobGuidType;
    UINT8   Revision;
    BOOLEAN IsSandyBridge;
    BOOLEAN IsHasWell;
    UINT64  Reserved0;
    UINT8   PowerConv;
    UINT8   CurConv;
    UINT8   TimeConv;
    UINT16  Tdc;
    UINT16  Tdp;                    
    UINT8   TdpLimitTime;           
    UINT8   Vid;
//Used for PERF_TUNE_SUPPORT Start
    UINT8   OneCoreRatioLimit;
    UINT8   TwoCoreRatioLimit;
    UINT8   ThreeCoreRatioLimit;
    UINT8   FourCoreRatioLimit;
    UINT8   FiveCoreRatioLimit;
    UINT8   SixCoreRatioLimit;
	UINT16	IaCoreCurrentMax;
	UINT16  IGfxCoreCurrentMax;
	UINT8	OneCoreRatioMax;
	UINT8	TwoCoreRatioMax;
	UINT8	ThreeCoreRatioMax;
	UINT8	FourCoreRatioMax;
	UINT8	FiveCoreRatioMax;
	UINT8	SixCoreRatioMax;
//Used for PERF_TUNE_SUPPORT End
} AMI_INTERNAL_FACTORY_TDC_TDP_HOB;
#pragma pack(pop)

// Type Definition(s)
typedef VOID (CPU_POLICY_INIT_FUNC) (
    IN EFI_PEI_SERVICES     **PeiServices,
    IN SETUP_DATA           *SetupData,
    IN OUT PEI_CPU_PLATFORM_POLICY_PPI       *PeiCpuPolicyPpi);

//VOID PeiCpuPolicyInit (
//    IN EFI_PEI_SERVICES         **PeiServices,
//    IN SETUP_DATA               *SetupData,
//    IN OUT PEI_CPU_PLATFORM_POLICY_PPI       *PeiCpuPolicyPpi );

VOID CallPeiCpuPolicyInitList(
    IN EFI_PEI_SERVICES                 **PeiServices,
    IN OUT PEI_CPU_PLATFORM_POLICY_PPI  *PeiCpuPolicyPpi);

// External Declaration(s)
extern CPU_POLICY_INIT_FUNC PEI_CPU_POLICY_INIT_LIST EndOfList;

CPU_POLICY_INIT_FUNC* PeiCpuPolicyInitListTable[] = \
                                            {PEI_CPU_POLICY_INIT_LIST NULL};

EFI_GUID gAmiInternalFactoryTdcTdpHobGuid = AMI_INTERNAL_FACTORY_TDC_TDP_HOB_GUID;
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   CallPeiCpuPolicyInitList
//
// Description: This function orderly calls functions in PeiCpuPolicyInitListTable 
// for OEM or Custom to override PEI_CPU_PLATFORM_POLICY_PPI.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID CallPeiCpuPolicyInitList (
    IN EFI_PEI_SERVICES                      **PeiServices,
    IN OUT PEI_CPU_PLATFORM_POLICY_PPI       *PeiCpuPolicyPpi )
{

  EFI_PEI_READ_ONLY_VARIABLE_PPI        *ReadOnlyVariable;
  EFI_GUID                              gEfiSetupGuid = SETUP_GUID;
  SETUP_DATA                            SetupData;
  SETUP_DATA                            *SetupDataPtr = NULL;
  UINTN                                 VariableSize= sizeof (SETUP_DATA);
  UINTN                                 i;
  EFI_STATUS                            Status;
      
  //
  // Get AMI setup variable to setup PEI CPU Policy
  //
  Status = (*PeiServices)->LocatePpi (
                          PeiServices,
                          &gPeiReadOnlyVariablePpiGuid,
                          0,
                          NULL,
                          &ReadOnlyVariable
                          );
//  ASSERT_EFI_ERROR (Status);

  if (!EFI_ERROR(Status)) {
    Status = ReadOnlyVariable->PeiGetVariable (
                            PeiServices,
                            L"Setup",
                            &gEfiSetupGuid,
                            NULL,
                            &VariableSize,
                            &SetupData
                            );
  }    
//SetupData variable is always exist in Aptio BIOS even it's the 1st time boot.
//  ASSERT_EFI_ERROR (Status); 
  if(!EFI_ERROR(Status)) SetupDataPtr = &SetupData; 
  else return;  
// Call PeiCpuPolicyInitListTable(eLink:PeiCpuPolicyInitList)
  for (i = 0; PeiCpuPolicyInitListTable[i] != NULL; i++) 
      PeiCpuPolicyInitListTable[i](PeiServices, SetupDataPtr, PeiCpuPolicyPpi);     
  
}

VOID PeiCpuPolicyInit (
    IN EFI_PEI_SERVICES         **PeiServices,
    IN SETUP_DATA               *SetupData,
    IN OUT PEI_CPU_PLATFORM_POLICY_PPI       *PeiCpuPolicyPpi )
{

  UINT32	                  RegEax, RegEbx, RegEcx, RegEdx;
  UINT8                       TotLogicalCpus = 0;
  UINT8                       LogicalCpusPerCore = 0;
  UINT8                       CpuSupportedCores = 0;
  UINT64                      TempMsr;
  EFI_STATUS                  Status;
  CPU_CONFIG_PPI              *CpuConfig = PeiCpuPolicyPpi->CpuConfig;
//  SECURITY_CONFIG_PPI         *SecurityConfig = PeiCpuPolicyPpi->SecurityConfig;
  POWER_MGMT_CONFIG_PPI           *PowerMgmtConfig = PeiCpuPolicyPpi->PowerMgmtConfig;
  TXT_CONFIG                  *TxtConfig = PeiCpuPolicyPpi->SecurityConfig->TxtConfig;
  AMI_INTERNAL_FACTORY_TDC_TDP_HOB      *TdcTdpHob;
#if TCG_SUPPORT || TCG2Support 
  UINT8       				  *TpmBaseAddr = (UINT8*)0xfed40000;
#endif

//
// Create Cpu Tdc and Tdp HOB
//  
  Status = (*PeiServices)->CreateHob(
            PeiServices,
            EFI_HOB_TYPE_GUID_EXTENSION,
            sizeof(AMI_INTERNAL_FACTORY_TDC_TDP_HOB),
            &TdcTdpHob
        );

  if ( !EFI_ERROR(Status) ) {
	  TdcTdpHob->EfiHobGuidType.Name = gAmiInternalFactoryTdcTdpHobGuid; 
	  TdcTdpHob->Revision = 1; 
	  
	  TempMsr = AsmReadMsr64 (MSR_PACKAGE_POWER_LIMIT); 
	  
	  TdcTdpHob->IsSandyBridge = FALSE;
	  TdcTdpHob->IsHasWell = TRUE;
	  TdcTdpHob->Tdc = (UINT16)(RShiftU64 (TempMsr, 32) & 0x7fff);
	  TdcTdpHob->Tdp = (UINT16)(TempMsr & 0x7fff);
	  TdcTdpHob->TdpLimitTime = (UINT8)(RShiftU64 (TempMsr, 17) & 0x7f);
	  
	  TempMsr = AsmReadMsr64 (MSR_PACKAGE_POWER_SKU_UNIT);
	  TdcTdpHob->PowerConv = 1 << ((UINT8)(TempMsr & 0xf));
	  TdcTdpHob->TimeConv = RShiftU64(TempMsr, 16) & 0xf ;   // 1 / (2 ^ TIME_UINT)
	  
	  TempMsr = AsmReadMsr64 (MSR_TURBO_RATIO_LIMIT);  
	  TdcTdpHob->OneCoreRatioLimit = (UINT8)TempMsr;
	  TdcTdpHob->TwoCoreRatioLimit = (UINT8)(RShiftU64 (TempMsr, 8));
	  TdcTdpHob->ThreeCoreRatioLimit = (UINT8)(RShiftU64 (TempMsr, 16));
	  TdcTdpHob->FourCoreRatioLimit = (UINT8)(RShiftU64 (TempMsr, 24));
	  TdcTdpHob->FiveCoreRatioLimit = (UINT8)(RShiftU64 (TempMsr, 32));
	  TdcTdpHob->SixCoreRatioLimit = (UINT8)(RShiftU64 (TempMsr, 40));
			
	  TdcTdpHob->Vid = (UINT8)(AsmReadMsr64(MSR_FLEX_RATIO));
	  TdcTdpHob->IaCoreCurrentMax = (UINT16)(AsmReadMsr64(MSR_VR_CURRENT_CONFIG) & 0xfff);
  }
  // CPU policy configure by setup questions
  if (SetupData != NULL) {
//
// CPU feature policyoverwrite 
//
#if CPU_SETUP_SET_MAX_RATIO
    CpuConfig->CpuRatioOverride     = CPU_FEATURE_ENABLE;
    CpuConfig->CpuRatio             = SetupData->CpuMaxRatio;;
#endif     
    CpuConfig->HyperThreading = SetupData->HTD; 
    CpuConfig->VmxEnable = SetupData->VT;
    CpuConfig->MlcStreamerPrefetcher = SetupData->MlcStreamerPrefetcher;
    CpuConfig->MlcSpatialPrefetcher = SetupData->MlcSpatialPrefetcher;
    
    //Do not set ActiveCoreCount more than CPU supported Cores
    AsmCpuidEx (0xb, 1, &RegEax, &RegEbx, &RegEcx, &RegEdx);
    TotLogicalCpus  = (UINT8)RegEbx;
    
    AsmCpuidEx (0xb, 0, &RegEax, &RegEbx, &RegEcx, &RegEdx);    
    LogicalCpusPerCore  = (UINT8)RegEbx;

    CpuSupportedCores = TotLogicalCpus / LogicalCpusPerCore;    

    if (SetupData->ActiveCoreCount != 0 && SetupData->ActiveCoreCount <= CpuSupportedCores)
        CpuConfig->ActiveCoreCount = SetupData->ActiveCoreCount;
    else
        CpuConfig->ActiveCoreCount = 0;

//
// Power Managment policy overwrite 
//

    PowerMgmtConfig->VrCurrentLimitLock     = SetupData->VrCurrentLimitLock;
    
    if(SetupData->CpuTccActOffset != 0)
        PowerMgmtConfig->TccActivationOffset = SetupData->CpuTccActOffset;
        
    if(SetupData->Cpu1CoreRatioLimit != 0){
        PowerMgmtConfig->Xe = CPU_FEATURE_ENABLE; 
        PowerMgmtConfig->RatioLimit[0] = SetupData->Cpu1CoreRatioLimit;
    }    
    
    if(SetupData->Cpu2CoreRatioLimit != 0){
        PowerMgmtConfig->Xe = CPU_FEATURE_ENABLE; 
        PowerMgmtConfig->RatioLimit[1] = SetupData->Cpu2CoreRatioLimit;
    }
    
    if(SetupData->Cpu3CoreRatioLimit != 0){
        PowerMgmtConfig->Xe = CPU_FEATURE_ENABLE; 
        PowerMgmtConfig->RatioLimit[2] = SetupData->Cpu3CoreRatioLimit;
    }
        
    if(SetupData->Cpu4CoreRatioLimit != 0){
        PowerMgmtConfig->Xe = CPU_FEATURE_ENABLE; 
        PowerMgmtConfig->RatioLimit[3] = SetupData->Cpu4CoreRatioLimit;
    }    
    
    if (SetupData->VrCurrentLimit != 0)
        PowerMgmtConfig->VrCurrentLimit = SetupData->VrCurrentLimit;
    
    PowerMgmtConfig->VrMiscIoutOffset       = SetupData->IoutOffset;    
    PowerMgmtConfig->VrMiscIoutSlope        = SetupData->IoutSlope;    
    PowerMgmtConfig->VrMiscIoutOffsetSign   = SetupData->IoutOffsetSign;
	
	PowerMgmtConfig->BootInLfm				= SetupData->BootInLfm;

//
//  TXT Policy overwrite
//  
#if TCG_SUPPORT || TCG2Support
    if (SetupData->TxtSupport && SetupData->TpmSupport && (*TpmBaseAddr != 0xff)) {     
        CpuConfig->Txt = CPU_FEATURE_ENABLE;        
        TxtConfig->TxtDprMemorySize = TXT_TOTAL_STOLEN_MEMORY_SIZE;
    }
#else
    CpuConfig->Txt = CPU_FEATURE_DISABLE;
#endif        
    if (SetupData->TxtSupport)
        CpuConfig->VmxEnable = CPU_FEATURE_ENABLE;  // VMX must enable when TXT enable
  }
}
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1987-2013, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
