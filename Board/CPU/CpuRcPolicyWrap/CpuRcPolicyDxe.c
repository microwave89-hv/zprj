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
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/Haswell/AMI Cpu PKG/CPU Board/CpuRcPolicyWrap/CpuRcPolicyDxe.c 26    4/10/15 4:08a Crystallee $
//
// $Revision: 26 $
//
// $Date: 4/10/15 4:08a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/Haswell/AMI Cpu PKG/CPU Board/CpuRcPolicyWrap/CpuRcPolicyDxe.c $
// 
// 26    4/10/15 4:08a Crystallee
// 
// 25    1/22/15 4:34a Crystallee
// 
// 24    12/19/13 3:38a Crystallee
// 
// 23    12/18/13 10:23p Crystallee
// [TAG]  		EIP145605
// [Category]  	Improvement
// [Description]  	Intel Workaround - custom TDP table implementation. Add
// a workaround for prevent Windows displays 2 different frequencies brand
// string within the My Computer -> Properties.
// 
// 22    8/28/13 5:45a Crystallee
// 
// 21    8/14/13 4:56a Davidhsieh
// [TAG]  		EIP131295
// [Category]  	Improvement
// [Description]  	Add token to force turbo mode is not supported for i3
// Cpu
// 
// 20    6/03/13 2:38a Hsingyingchung
// [TAG]  		EIP123835
// [Category]  	Spec Update
// [Severity]  	Important
// [Description]  	SBY Performance Tuning Guid rev. 1.1 update.
// 
// 19    4/07/13 11:52p Hsingyingchung
// [TAG]  		EIPNone
// [Category]  	Improvement
// [Description]  	Modify CustomPowerUnit of Haswell RC if add XTU
// 
// 18    4/03/13 4:58a Crystallee
// [TAG]  		EIP119880
// [Category]  	Improvement
// [Description]  	Provide setup items which is related to PowerLimit3.
// 
// 17    3/28/13 4:01a Davidhsieh
// [TAG]  		None
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	ACPI T state table is not reported
// [RootCause]  	T state function enable policy in Haswell RC is not
// correct.
// [Solution]  	Correct the T state function policy
// 
// 16    3/05/13 6:55a Davidhsieh
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Token RC_POLICY_POWER_UNIT create for Haswell RC
// CustomPowerUnit
// 
// 15    2/22/13 1:54a Crystallee
// [TAG]  		EIP112238
// [Category]  	Improvement
// [Description]  	Refer Intel BIOS and provide setup items for Intel
// Haswell RC policy.
// 
// 14    2/07/13 3:54a Hsingyingchung
// [TAG]  		EIP112631
// [Category]  	Improvement
// [Description]  	update for 4.6.5.0_XtuHswSetup_004
// 
// 13    1/24/13 5:18a Crystallee
// [TAG]           None
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	Change C state limit to C10, the system will hang.
// [RootCause]  	BIOS doesn't limit the C state to CPU support.
// [Solution]  	According to the CPU C state support, add C state limit to
// prevent system hanging and limit the setup item choice.
// 
// 12    1/15/13 1:56a Crystallee
// [TAG]  		EIP103130
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	SHB MB: Passive Trip Point is not Active
// [RootCause]  	BIOS doesn't correct to disable "AutoThermalReporting"
// variable in the CPU DXE Platform Policy.
// [Solution]  	Correct the "AutoThermalReporting" variable in
// ThermalFuncEnables in POWER_MGMT_CONFIG
// 
// 11    12/03/12 9:50p Davidhsieh
// [TAG]  		EIP108401
// [Category]  	Improvement
// [Description]  	Create setup items for VrMiscIoutOffset,
// VrMiscIoutSlope and LakeTiny
// 
// 10    11/23/12 2:04a Hsingyingchung
// 
// 9     11/18/12 9:36p Davidhsieh
// [TAG]  		EIP105980
// [Category]  	Improvement
// [Description]  	Setup items for Package C State Limit and Energy
// Performance
// 
// 8     10/28/12 11:37p Davidhsieh
// [TAG]  		EIP105017
// [Category]  	Improvement
// [Description]  	Implement Setup Options for Debug Interface Enable/Lock
// 
// 7     10/17/12 2:21a Davidhsieh
// [TAG]                None
// [Category]         Improvement
// [Description]      Setup items CTDP BIOS, C8, C9 and C10 created
// 
// 6     9/13/12 3:33a Davidhsieh
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Add DTS setup item
// 
// 5     8/06/12 10:48p Davidhsieh
// [TAG]  		EIP95485
// [Category]  	Improvement
// [Description]  	Configure TXT Feature via setup option
// 
// 4     7/19/12 2:22a Davidhsieh
// [TAG]  		EIP95485
// [Category]  	Improvement
// [Description]  	Enable VT when TXT is enabled
// 
// 3     5/22/12 3:00a Davidhsieh
// Setup page layout change
// 
// 2     3/16/12 3:45a Davidhsieh
// Setup items create for CPU RC policy
// 
// 1     2/07/12 3:57a Davidhsieh
// 
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:  CpuRcPolicyDxe.c
//
// Description: DxeCpuPolicyInitList eLink interface & its default child procedure
// for setting up DXE_CPU_PLATFORM_POLICY_PROTOCOL.
//
//<AMI_FHDR_END>
//**********************************************************************

#include "token.h"

#include "EdkIIGlueDxe.h"
//#include EFI_PROTOCOL_DEFINITION (CpuInfo)
#include "CpuPolicyInitDxe.h"

#define VFRCOMPILE
#include "Include\Setup.h"
#undef VFRCOMPILE

#if PERF_TUNE_SUPPORT == 1 
#define AMI_PERF_TUNE_DATA_HOB_GUID \
 {0x4d6c0496, 0x8de4, 0x4af2, 0x9a, 0x2e, 0x9b, 0xe5, 0xb9, 0x15, 0x6a, 0xc5}
#include <PerfTuneSetup.h>
typedef struct _PERF_TUNE_DATA_HOB2{
	EFI_HOB_GUID_TYPE   EfiHobGuidType;
	OC_SETUP_DATA       PerfTuneDataHob;
	BOOLEAN				IsRunDefault;
	BOOLEAN				IsCpuChanged;
	BOOLEAN				IsWdtTimeOut;
}PERF_TUNE_DATA_HOB2;
#endif

#define AMI_INTERNAL_UCODE_HOB_GUID \
    {0x94567c6f, 0xf7a9, 0x4229, 0x13, 0x30, 0xfe, 0x11, 0xcc, 0xab, 0x3a, 0x11}

typedef struct {
    EFI_HOB_GUID_TYPE   EfiHobGuidType;    
	UINT32  uCodeAddr;
} AMI_INTERNAL_UCODE_HOB;

// Type Definition(s)
typedef VOID (CPU_POLICY_INIT_FUNC) (
    IN EFI_SYSTEM_TABLE *SystemTable,
    IN SETUP_DATA           *SetupData,
    IN OUT DXE_CPU_PLATFORM_POLICY_PROTOCOL       *mCpuPolicyDataPtr);

VOID DxeCpuPolicyInit (
    IN EFI_SYSTEM_TABLE *SystemTable,
    IN SETUP_DATA   *SetupData,
    IN OUT DXE_CPU_PLATFORM_POLICY_PROTOCOL       *mCpuPolicyDataPtr);

VOID CallDxeCpuPolicyInitList(
    IN EFI_SYSTEM_TABLE *SystemTable,
    IN OUT DXE_CPU_PLATFORM_POLICY_PROTOCOL       *mCpuPolicyDataPtr);

// External Declaration(s)
extern CPU_POLICY_INIT_FUNC DXE_CPU_POLICY_INIT_LIST EndOfList;

CPU_POLICY_INIT_FUNC* DxeCpuPolicyInitListTable[] = \
                                            {DXE_CPU_POLICY_INIT_LIST NULL};

EFI_GUID gAmiInternaluCodeHobGuid = AMI_INTERNAL_UCODE_HOB_GUID;   
UINT32   gMicrocodeStart = 0;

//Cstate
#define C3_SUB_STATES_MASK	  0x00000f00
#define	C6_SUB_STATES_MASK	  0x0000f000
#define	C7_SUB_STATES_MASK	  0x000f0000
#define	C8_SUB_STATES_MASK	  0x00f00000
#define	C9_SUB_STATES_MASK	  0x0f000000
#define	C10_SUB_STATES_MASK	  0xf0000000

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   CallDxeCpuPolicyInitList
//
// Description: Get the microcode patch.
//
//
// Input:
//      IN DXE_CPU_PLATFORM_POLICY_PROTOCOL      *This
//      IN UINT8                                 **MicrocodeData
//
// Output:
//      EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
AmiPlatformCpuRetrieveMicrocode (
  IN  DXE_CPU_PLATFORM_POLICY_PROTOCOL      *This,
  OUT UINT8                                 **MicrocodeData
  )
/*++
  
Routine Description:

  Get the microcode patch.

Arguments:

  This          - Driver context.
  MicrocodeData - Retrieved image of the microcode.

Returns:

  EFI_SUCCESS - Image found.

--*/

//
// GC_TODO:    EFI_NOT_FOUND - add return value to function comment
// GC_TODO:    EFI_NOT_FOUND - add return value to function comment
//
{

    if (*MicrocodeData == NULL && gMicrocodeStart != 0) {	        
        *MicrocodeData = (UINT8 *) (UINTN) gMicrocodeStart;
    } else{
        return EFI_NOT_FOUND;
    }
    
    return EFI_SUCCESS;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   CallDxeCpuPolicyInitList
//
// Description: This function orderly calls functions in DxeCpuPolicyOemInitList 
// for OEM or Custom to override PEI_CPU_PLATFORM_POLICY_PPI.
//
//
// Input:
//      IN EFI_SYSTEM_TABLE                     *SystemTable
//      IN OUT DXE_CPU_PLATFORM_POLICY_PROTOCOL *mCpuPolicyDataPtr
//
// Output:
//      None

//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID CallDxeCpuPolicyInitList (
    IN EFI_SYSTEM_TABLE *SystemTable,
    IN OUT DXE_CPU_PLATFORM_POLICY_PROTOCOL *mCpuPolicyDataPtr)
{

  EFI_STATUS  Status;
                
  EFI_GUID      guidSetup = SETUP_GUID;
  SETUP_DATA    SetupData;
  SETUP_DATA    *SetupDataPtr = NULL;
  UINTN         Size = sizeof(SETUP_DATA);
  UINTN         i;                
                    
  Status = gRT->GetVariable(L"Setup",&guidSetup, NULL, &Size, &SetupData);
    
//SetupData variable is always exist in Aptio BIOS even it's the 1st time boot.
//  ASSERT_EFI_ERROR (Status); 
  if(!EFI_ERROR(Status)) SetupDataPtr = &SetupData; 
    
// Call DxeCpuPolicyInitListTable(eLink:DxeCpuPolicyInitList)
  for (i = 0; DxeCpuPolicyInitListTable[i] != NULL; i++) 
      DxeCpuPolicyInitListTable[i](SystemTable, SetupDataPtr, mCpuPolicyDataPtr);     
  
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   CallDxeCpuPolicyInitList
//
// Description: This function overrides DXE_CPU_PLATFORM_POLICY_PROTOCOL.
//
//
// Input:
//      IN EFI_SYSTEM_TABLE                     *SystemTable
//      IN SETUP_DATA                           *SetupData
//      IN OUT DXE_CPU_PLATFORM_POLICY_PROTOCOL *mCpuPolicyDataPtr
//
// Output:
//      None

//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID DxeCpuPolicyInit (
    IN EFI_SYSTEM_TABLE *SystemTable,
    IN SETUP_DATA   *SetupData,
    IN OUT DXE_CPU_PLATFORM_POLICY_PROTOCOL       *mCpuPolicyData)
{
  
    EFI_STATUS                 Status;
    CPU_CONFIG                 *CpuConfig = mCpuPolicyData->CpuConfig;
    POWER_MGMT_CONFIG          *CpuPmConfig = mCpuPolicyData->PowerMgmtConfig;

    UINT32	                	RegEax, RegEbx, RegEcx, RegEdx;
	UINT8						CStateSupport = 0;
    VOID                      *HobList;
    AMI_INTERNAL_UCODE_HOB    *uCodeHob = NULL;    

#if BRAND_STRING_WORKAROUND == 1 
	PPM_CUSTOM_CTDP_TABLE	   *CustomConfigTdpTable;
	UINT16 CustomPowerLimit1;
	UINT8 mPowerUnitPowerOfTwo;
	UINT8 mPowerUnit;
	UINT16 mCustomPowerUnit;
	UINT16 mPackageTdp;
	UINTN PackageTdp;
	UINTN NoOfOverrides = 0;
	UINTN Index;
	UINT64 PakagePowerLimitMsr = 0;
	UINTN mHswUltPpmCtdpOverideTable[] = {
	///  TDP  Icc  MSR PL1  MSR PL2   TdpUp   TdpUp   TdpNominal  TdpNominal  TdpDown   TdpDown
	///       Max                     PL1     PL2     PL1         PL2         PL1       PL2
	     5700, 0,  6700,    8375,     0,      8375,   0,          8375,       0,        8375 ,  /// 57W Sku Overrides
	     1500, 0,  2500,    2500,     0,      2500,   0,          2500,       0,        2500 ,  /// 15W Sku Overrides
	     1150, 0,  0,       2500,     0,      2500,   0,          2500,       0,        2500 ,  /// 11.5W Sku Overrides
	     2800, 40,  0,      3500,     0,      3500,   0,          3500,       0,        3500    /// 28W 40A Sku Overrides  
		};
#endif

#if PERF_TUNE_SUPPORT == 1 
    EFI_GUID gAmiPerfTuneDataHobGuid = AMI_PERF_TUNE_DATA_HOB_GUID;
    PERF_TUNE_DATA_HOB2     *XtuPerfTuneDataHob;
    OC_SETUP_DATA           *SettingData;
#endif

#if defined(I3_CPU_NON_TURBO) && (I3_CPU_NON_TURBO == 1)       	
    
    BOOLEAN IsI3Cpu = FALSE;
{    
    CHAR8   BrandStrBuff[49];
	CHAR8  *BrandString = BrandStrBuff;	
	
	AsmCpuid(0x80000002, &RegEax, &RegEbx, &RegEcx, &RegEdx);
    *(UINT32*)BrandString = RegEax; BrandString +=4;
    *(UINT32*)BrandString = RegEbx; BrandString +=4;
    *(UINT32*)BrandString = RegEcx; BrandString +=4;
    *(UINT32*)BrandString = RegEdx; BrandString +=4;
    
    AsmCpuid(0x80000003, &RegEax, &RegEbx, &RegEcx, &RegEdx);
    *(UINT32*)BrandString = RegEax; BrandString +=4;
    *(UINT32*)BrandString = RegEbx; BrandString +=4;
    *(UINT32*)BrandString = RegEcx; BrandString +=4;
    *(UINT32*)BrandString = RegEdx; BrandString +=4;
    
    AsmCpuid(0x80000004, &RegEax, &RegEbx, &RegEcx, &RegEdx);
    *(UINT32*)BrandString = RegEax; BrandString +=4;
    *(UINT32*)BrandString = RegEbx; BrandString +=4;
    *(UINT32*)BrandString = RegEcx; BrandString +=4;
    *(UINT32*)BrandString = RegEdx; BrandString +=4;
    *BrandString = '\0';\
     
    BrandString = BrandStrBuff;
    
    while(*BrandString) {
        if ( *((CHAR16*)BrandString) == '3i') {        
            IsI3Cpu = TRUE;            
            break;
        }    
        ++BrandString;
    }    


}
#endif
      
    //
    // Get the start of the HOBs.
    //
    Status = EfiGetSystemConfigurationTable (&gEfiHobListGuid, &HobList);  
    //
    // Get the Compatible BIOS structure BDAT from the HOB.
    //
    if (!EFI_ERROR(Status)){
        uCodeHob = GetNextGuidHob (&gAmiInternaluCodeHobGuid, HobList);
        if (uCodeHob != NULL) {
            gMicrocodeStart = uCodeHob->uCodeAddr;
            DEBUG ((EFI_D_ERROR, "CPU ID in uCode = %x\n", ((EFI_CPU_MICROCODE_HEADER *)gMicrocodeStart)->ProcessorId)); 
            // uCode in memory is already found, change the RetriveveMicrocode funciton      
            mCpuPolicyData->CpuConfig->RetrieveMicrocode  = AmiPlatformCpuRetrieveMicrocode;           
        }
    }
    
    CpuConfig->RetrieveMicrocode = AmiPlatformCpuRetrieveMicrocode;  
    
    CpuPmConfig->CustomPowerUnit = RC_POLICY_POWER_UNIT;
    if(SetupData != NULL){
    //
    //CPU config overwrite
    //    
        CpuConfig->LimitCpuidMaximumValue = SetupData->LimitCpuid;
        CpuConfig->HtState = SetupData->HTD;
        CpuConfig->ExecuteDisableBit = SetupData->XDBit;
        CpuConfig->VmxEnable = SetupData->VT;

        if (SetupData->TxtSupport) {    
            CpuConfig->VmxEnable = CPU_FEATURE_ENABLE;  //Enable VMX when TXT enable
            CpuConfig->SmxEnable = CPU_FEATURE_ENABLE;
        } else {
            CpuConfig->SmxEnable = CPU_FEATURE_DISABLE;
        }            
        //CpuConfig->SmxEnable = CPU_FEATURE_ENABLE;
    
        CpuConfig->MlcStreamerPrefetcher  = SetupData->MlcStreamerPrefetcher;
        CpuConfig->MlcSpatialPrefetcher   = SetupData->MlcSpatialPrefetcher;
        CpuConfig->AesEnable              = SetupData->AesEnable;
        //CpuConfig->MachineCheckEnable     = CPU_FEATURE_ENABLE;
        CpuConfig->EnableDts              = SetupData->DtsEnable;
        CpuConfig->DebugInterfaceEnable     = SetupData->DebugInterfaceEnable;
        CpuConfig->DebugInterfaceLockEnable = SetupData->DebugInterfaceLock;
        
    //
    //Power management config overwrite        
    //  
        CpuPmConfig->pFunctionEnables->Eist                     = SetupData->EIST;
        CpuPmConfig->pFunctionEnables->TurboMode                = SetupData->TurboMode;
#if defined(I3_CPU_NON_TURBO) && (I3_CPU_NON_TURBO == 1)           
        if (IsI3Cpu)
            CpuPmConfig->pFunctionEnables->TurboMode = PPM_DISABLE;
#endif            
        //CpuPmConfig->pFunctionEnables->Cx                     = PPM_ENABLE;
        if (SetupData->CxEnable){
            CpuPmConfig->pFunctionEnables->C1e                    = SetupData->C1E;
            CpuPmConfig->pFunctionEnables->C3                     = SetupData->C3Enable;
            CpuPmConfig->pFunctionEnables->C6                     = SetupData->C6Enable;
            CpuPmConfig->pFunctionEnables->DeepCState             = SetupData->C7Enable;        
            CpuPmConfig->pFunctionEnables->C1AutoDemotion         = SetupData->C1AutoDemotion;
            CpuPmConfig->pFunctionEnables->C3AutoDemotion         = SetupData->C3AutoDemotion;
			CpuPmConfig->pFunctionEnables->PkgCStateDemotion	  = SetupData->PkgCStateDemotion;
            CpuPmConfig->pFunctionEnables->C1UnDemotion           = SetupData->C1UnDemotion;
            CpuPmConfig->pFunctionEnables->C3UnDemotion           = SetupData->C3UnDemotion;
			CpuPmConfig->pFunctionEnables->PkgCStateUnDemotion	  = SetupData->PkgCStateUnDemotion;
            CpuPmConfig->pFunctionEnables->CStatePreWake          = SetupData->CxPreWake;            
            CpuPmConfig->pFunctionEnables->LongLatencyC6          = SetupData->C6Latency;
            CpuPmConfig->pFunctionEnables->LongLatencyC7          = SetupData->C7Latency;
            CpuPmConfig->pFunctionEnables->LakeTiny               = SetupData->LakeTiny;
#if ULT_SUPPORT
            CpuPmConfig->pFunctionEnables->C8                     = SetupData->C8Enable;
            CpuPmConfig->pFunctionEnables->C9                     = SetupData->C9Enable;
            CpuPmConfig->pFunctionEnables->C10                    = SetupData->C10Enable;
#endif            
        } else {
            CpuPmConfig->pFunctionEnables->Cx                     = PPM_DISABLE;
            CpuPmConfig->pFunctionEnables->C3                     = PPM_DISABLE;
            CpuPmConfig->pFunctionEnables->C6                     = PPM_DISABLE;
            CpuPmConfig->pFunctionEnables->DeepCState             = PPM_DISABLE;
#if ULT_SUPPORT            
            CpuPmConfig->pFunctionEnables->C8                     = PPM_DISABLE;
            CpuPmConfig->pFunctionEnables->C9                     = PPM_DISABLE;
            CpuPmConfig->pFunctionEnables->C10                    = PPM_DISABLE;
#endif            
        }
        CpuPmConfig->ThermalFuncEnables->TStates                = SetupData->CpuTstate;
        //CpuPmConfig->pFunctionEnables->CStatePreWake          = PPM_ENABLE;
        //CpuPmConfig->pFunctionEnables->EnergyEfficientPState  = PPM_ENABLE;
        //CpuPmConfig->pFunctionEnables->CStatePreWake          = PPM_ENABLE;
#if SB_SETUP_SUPPORT        
        CpuPmConfig->ThermalFuncEnables->AutoThermalReporting   = SetupData->AutoThermalReport;
#endif        
        //CpuPmConfig->pFunctionEnables->LongLatencyC6          = PPM_DISABLE;
        //CpuPmConfig->pFunctionEnables->LongLatencyC7          = PPM_ENABLE;
        //CpuPmConfig->pFunctionEnables->ThermalMonitor         = PPM_ENABLE;
        //CpuPmConfig->pFunctionEnables->LakeTiny               = PPM_DISABLE;
        
        if (SetupData->PowerLimit1)
            CpuPmConfig->pTurboSettings->PowerLimit1              = SetupData->PowerLimit1;
        if (SetupData->PowerLimit2)    
            CpuPmConfig->pTurboSettings->PowerLimit2              = SetupData->PowerLimit2;
        if (SetupData->PowerLimit1Time)    
            CpuPmConfig->pTurboSettings->PowerLimit1Time          = SetupData->PowerLimit1Time;
			
        CpuPmConfig->pTurboSettings->PowerLimit3Lock              = SetupData->PowerLimit3Lock;    
		if (SetupData->PowerLimit3)    
            CpuPmConfig->pTurboSettings->PowerLimit3              = SetupData->PowerLimit3;
		if (SetupData->PowerLimit3Time)    
            CpuPmConfig->pTurboSettings->PowerLimit3Time          = SetupData->PowerLimit3Time;
		if (SetupData->PowerLimit3DutyCycle)    
            CpuPmConfig->pTurboSettings->PowerLimit3DutyCycle     = SetupData->PowerLimit3DutyCycle;
        
        if (SetupData->DdrPowerLimit1)
            CpuPmConfig->pTurboSettings->DdrPowerLimit1           = SetupData->DdrPowerLimit1;        
        if (SetupData->DdrPowerLimit2)
            CpuPmConfig->pTurboSettings->DdrPowerLimit2           = SetupData->DdrPowerLimit2;        
        if (SetupData->DdrPowerLimit1Time)
            CpuPmConfig->pTurboSettings->DdrPowerLimit1Time       = SetupData->DdrPowerLimit1Time;
        
        CpuPmConfig->pTurboSettings->ConfigTdpBios            = SetupData->CtdpBios;
        CpuPmConfig->pTurboSettings->ConfigTdpLevel           = SetupData->cTDPLevel;
        CpuPmConfig->pTurboSettings->ConfigTdpLock            = SetupData->cTDPLock;
        CpuPmConfig->pTurboSettings->EnergyPolicy             = SetupData->CpuEngPerfBias;

		CpuPmConfig->pTurboSettings->TurboPowerLimitLock	  = SetupData->TurboPowerLimitLock;

#if BRAND_STRING_WORKAROUND == 1 
		//Configure custom cTdp table
        CpuPmConfig->pCustomCtdpSettings->ConfigTdpCustom     = PPM_ENABLE;
		CpuPmConfig->pCustomCtdpSettings->CustomTdpCount	  = 2;
		CpuPmConfig->pCustomCtdpSettings->CustomBootModeIndex = 0;

		CustomConfigTdpTable = CpuPmConfig->pCustomCtdpSettings->CustomConfigTdpTable;
		mPowerUnitPowerOfTwo = (UINT8)(AsmReadMsr64 (MSR_PACKAGE_POWER_SKU_UNIT) & 0xf);
		mPowerUnit = (UINT8) 1 << mPowerUnitPowerOfTwo;
#if RC_POLICY_POWER_UNIT == 0
		mCustomPowerUnit = 1;
#else
		mCustomPowerUnit = (UINT8) 1 << mPowerUnitPowerOfTwo;
#endif
		mPackageTdp = (UINT16)(AsmReadMsr64(MSR_PACKAGE_POWER_SKU) & 0x7fff);

#if RC_POLICY_POWER_UNIT == 0
		CustomConfigTdpTable[0].CustomPowerLimit1 = mPackageTdp / mPowerUnit;
		CustomConfigTdpTable[0].CustomPowerLimit2 = mPackageTdp * 125 / 100 / mPowerUnit;
#else
		CustomConfigTdpTable[0].CustomPowerLimit1 = mPackageTdp;
		CustomConfigTdpTable[0].CustomPowerLimit2 = mPackageTdp * 125 / 100;
#endif
		CustomConfigTdpTable[0].CustomPowerLimit1Time = 0x1c; //MB_POWER_LIMIT1_TIME_DEFAULT
		CustomConfigTdpTable[0].CustomTurboActivationRatio = (UINT8)(AsmReadMsr64 (MSR_CONFIG_TDP_NOMINAL) & 0xff) - 1;
		CustomConfigTdpTable[0].CustomConfigTdpControl = 1;

		CustomPowerLimit1 = (UINT16)(AsmReadMsr64(MSR_CONFIG_TDP_LVL1) & 0x7fff);
#if RC_POLICY_POWER_UNIT == 0
		CustomConfigTdpTable[1].CustomPowerLimit1 = CustomPowerLimit1 / mPowerUnit;
		CustomConfigTdpTable[1].CustomPowerLimit2 = CustomPowerLimit1 * 125 / 100 / mPowerUnit;
#else
		CustomConfigTdpTable[1].CustomPowerLimit1 = CustomPowerLimit1;
		CustomConfigTdpTable[1].CustomPowerLimit2 = CustomPowerLimit1 * 125 / 100;
#endif
		CustomConfigTdpTable[1].CustomPowerLimit1Time = CustomConfigTdpTable[0].CustomPowerLimit1Time;
		CustomConfigTdpTable[1].CustomTurboActivationRatio = (UINT8)((AsmReadMsr64(MSR_CONFIG_TDP_LVL1) >> 16) & 0xff) - 1;
		CustomConfigTdpTable[1].CustomConfigTdpControl = 0;

		AsmCpuid(0x1, &RegEax, &RegEbx, &RegEcx, &RegEdx);
		RegEax = RegEax & CPUID_FULL_FAMILY_MODEL;
		if(RegEax == EnumCpuHswUlt) NoOfOverrides = 1;
		PackageTdp = ((mPackageTdp / mPowerUnit) * 100);
		if((mPackageTdp % mPowerUnit) !=0) 
			PackageTdp += ((mPackageTdp % mPowerUnit)* 100) / mPowerUnit;

		Index = 0;
		while(NoOfOverrides != 0 && Index < sizeof(mHswUltPpmCtdpOverideTable)) {
		  if(mHswUltPpmCtdpOverideTable[0 + Index] == PackageTdp) {
			PakagePowerLimitMsr = AsmReadMsr64(MSR_PACKAGE_POWER_LIMIT);

			if(mHswUltPpmCtdpOverideTable[2 + Index]) {
			  PakagePowerLimitMsr &= ~POWER_LIMIT_MASK;
			  PakagePowerLimitMsr |= ((mHswUltPpmCtdpOverideTable[2 + Index] * mPowerUnit)/100) & POWER_LIMIT_MASK;
			}

			if(mHswUltPpmCtdpOverideTable[3 + Index]) {
			  PakagePowerLimitMsr &= ~(0x7FFF00000000);	//MSR_PACKAGE_POWER_LIMIT[46:32]
			  PakagePowerLimitMsr |=((mHswUltPpmCtdpOverideTable[3 + Index] * mPowerUnit)/100) & 0x7FFF00000000;
			}
		    AsmWriteMsr64 (MSR_PACKAGE_POWER_LIMIT, PakagePowerLimitMsr);

			if(mHswUltPpmCtdpOverideTable[6 + Index]) //CtdpNominalPowerLimit1
			  CustomConfigTdpTable[0].CustomPowerLimit1 = \
					((UINT16)(mHswUltPpmCtdpOverideTable[6 + Index]) / 100) * mCustomPowerUnit;

			if(mHswUltPpmCtdpOverideTable[7 + Index]) //CtdpNominalPowerLimit2
			  CustomConfigTdpTable[0].CustomPowerLimit2 =  \
					((UINT16)(mHswUltPpmCtdpOverideTable[7 + Index]) / 100) * mCustomPowerUnit;

			if(mHswUltPpmCtdpOverideTable[8 + Index]) //CtdpDownPowerLimit1
			  CustomConfigTdpTable[1].CustomPowerLimit1 =  \
					((UINT16)(mHswUltPpmCtdpOverideTable[8 + Index]) / 100) * mCustomPowerUnit;

			if(mHswUltPpmCtdpOverideTable[9 + Index]) //CtdpDownPowerLimit2
			  CustomConfigTdpTable[1].CustomPowerLimit2 =  \
					((UINT16)(mHswUltPpmCtdpOverideTable[9 + Index]) / 100) * mCustomPowerUnit;

			break;
		  }
		  Index += 10;
		}
#endif

        //if (RShiftU64(AsmReadMsr64(0xce), 33) & 0x03)
        //    CpuPmConfig->pTurboSettings->TurboPowerLimitLock      = PPM_DISABLE;
        //else
        //    CpuPmConfig->pTurboSettings->TurboPowerLimitLock      = PPM_ENABLE;    
        //CpuPmConfig->pTurboSettings->DdrPowerLimitLock        = PPM_DISABLE;
        //CpuPmConfig->pTurboSettings->EnergyPolicy             = 0;
        //         
        CpuPmConfig->pPpmLockEnables->PmgCstCfgCtrlLock         = SetupData->PmgCstCfgCtrlLock;
        CpuPmConfig->pPpmLockEnables->OverclockingLock        	= SetupData->OverclockingLock;
        //CpuPmConfig->pPpmLockEnables->ProcHotLock             = PPM_DISABLE;
        CpuPmConfig->S3RestoreMsrSwSmiNumber                    = SW_SMI_S3_RESTORE_MSR_FROM_SDL;

		AsmCpuid(5, &RegEax, &RegEbx, &RegEcx, &RegEdx);
		if (!!(RegEdx & C10_SUB_STATES_MASK))						CStateSupport = 8;	//C10 support
		if (!!(RegEdx & C9_SUB_STATES_MASK) && (!CStateSupport))	CStateSupport = 7;	//C9  support
		if (!!(RegEdx & C8_SUB_STATES_MASK) && (!CStateSupport))	CStateSupport = 6;	//C8  support
		if (!!(RegEdx & C7_SUB_STATES_MASK) && (!CStateSupport))	CStateSupport = 5;	//C7  support
		if (!!(RegEdx & C6_SUB_STATES_MASK) && (!CStateSupport))	CStateSupport = 3;	//C6  support
		if (!!(RegEdx & C3_SUB_STATES_MASK) && (!CStateSupport))	CStateSupport = 2;	//C3  support
		
        if (SetupData->PackageCState != 0xFF && SetupData->PackageCState > CStateSupport)
			CpuPmConfig->PkgCStateLimit = CStateSupport;
		else
			CpuPmConfig->PkgCStateLimit = SetupData->PackageCState;

        //CpuPmConfig->PkgCStateLimit = PkgAuto;
        //
#if CPU_SETUP_SET_LATENCY_CONTROL
        CpuPmConfig->CstateLatencyControl0TimeUnit = SetupData->CstateLatencyControl0TimeUnit;
        CpuPmConfig->CstateLatencyControl1TimeUnit = SetupData->CstateLatencyControl1TimeUnit;
        CpuPmConfig->CstateLatencyControl2TimeUnit = SetupData->CstateLatencyControl2TimeUnit;
        CpuPmConfig->CstateLatencyControl0Irtl = SetupData->CstateLatencyControl0Irtl;
        CpuPmConfig->CstateLatencyControl1Irtl = SetupData->CstateLatencyControl1Irtl;
        CpuPmConfig->CstateLatencyControl2Irtl = SetupData->CstateLatencyControl2Irtl;
#endif
        //CpuPmConfig->RfiFreqTunningOffsetIsNegative = 0;
        //CpuPmConfig->RfiFreqTunningOffset = 0;

#if PERF_TUNE_SUPPORT == 1 
    Status = EfiGetSystemConfigurationTable (&gEfiHobListGuid, &HobList);  
    if (!EFI_ERROR(Status)){
        XtuPerfTuneDataHob = GetNextGuidHob (&gAmiPerfTuneDataHobGuid, HobList);
        if (XtuPerfTuneDataHob != NULL) {
            SettingData = &XtuPerfTuneDataHob->PerfTuneDataHob;
        }
    }
    SettingData = &XtuPerfTuneDataHob->PerfTuneDataHob;

    if (!(EFI_ERROR(Status) /*|| XtuPerfTuneDataHob->IsWdtTimeOut*/ || (XtuPerfTuneDataHob->IsCpuChanged && XtuPerfTuneDataHob->IsRunDefault)))
    {    
        if (SettingData->EIST)
        {
            CpuPmConfig->pFunctionEnables->Eist = PPM_ENABLE;
            
            if (SettingData->TurboMode){
                CpuPmConfig->pFunctionEnables->TurboMode = PPM_ENABLE;                
            }    
            else
                CpuPmConfig->pFunctionEnables->TurboMode = PPM_DISABLE;
                
        }    
        else{  
            CpuPmConfig->pFunctionEnables->Eist = PPM_DISABLE;
            CpuPmConfig->pFunctionEnables->TurboMode = PPM_DISABLE;
        }    
        
	    if(!(SettingData->OverclockingEnable))
	        CpuPmConfig->pPpmLockEnables->OverclockingLock = PPM_ENABLE;	// 1, disable overclocking lock; 0, enable overclocking lock

        // Skus that support Config TDP are not able to change power limit(MSR 0x610) in real time, 
        // and don't lock cTDP CTC(MSR 0x64B) and cTDP TAR(MSR 0x64C).
        if ((AsmReadMsr64(MSR_PLATFORM_INFO) & (BIT33 | BIT34))){
            CpuPmConfig->pTurboSettings->PowerLimit2 = AUTO;
            CpuPmConfig->pTurboSettings->PowerLimit1 = AUTO; 
            CpuPmConfig->pTurboSettings->PowerLimit1Time = AUTO;
            CpuPmConfig->pTurboSettings->TurboPowerLimitLock = PPM_DISABLE;
            CpuPmConfig->pFunctionEnables->PowerLimit2 = PPM_ENABLE;
            CpuPmConfig->pTurboSettings->ConfigTdpLock = PPM_DISABLE;
            
        }else{
            CpuPmConfig->pTurboSettings->PowerLimit2 = SettingData->ShortPowerLimit;
            CpuPmConfig->pTurboSettings->PowerLimit1 = SettingData->ExtendedPowerLimit; 
            CpuPmConfig->pTurboSettings->PowerLimit1Time = SettingData->ExtendedTimeWindow;
            CpuPmConfig->pTurboSettings->TurboPowerLimitLock = (UINT8)SettingData->PowerLockSwitch;
            CpuPmConfig->pFunctionEnables->PowerLimit2 = (UINT8)SettingData->ShortPowerLockSwitch;
        }
        CpuPmConfig->CustomPowerUnit = PowerUnitWatts;  
    }
#endif
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
