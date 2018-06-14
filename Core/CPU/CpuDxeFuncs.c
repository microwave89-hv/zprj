//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1987-2013, American Megatrends, Inc.            **
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
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/Haswell/AMI Cpu PKG/CPU Core/CpuDxeFuncs.c 10    5/06/14 12:03a Hsingyingchung $
//
// $Revision: 10 $
//
// $Date: 5/06/14 12:03a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/Haswell/AMI Cpu PKG/CPU Core/CpuDxeFuncs.c $
// 
// 10    5/06/14 12:03a Hsingyingchung
// [TAG]  		EIP167029
// [Category]  	Improvement
// [Description]  	1. keep the original attribute of "Setup" variable when
// use SetVariable().
// 2. remove the runtime attribute of variables that no access requirement
// in runtime.
// 
// 9     6/03/13 12:12a Hsingyingchung
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	
// 1. Change PLL defatul value to LCPLL
// 2. Modify IA core ratio minimun value. Use "max non turbo ratio(MSR
// CEh)" instead of "power on turbo default value".
// 3. Remove write MSR 620h due to RC have implemented  (EIP123446).
// 
// 8     4/07/13 11:58p Hsingyingchung
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Keep ring ratio default value in ACPI table when one
// core ratio has changed.
// 
// 7     3/05/13 1:10a Davidhsieh
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Use OcSetupData for EIST and Turbo status when
// PerformanceTunning enable
// 
// 6     2/07/13 4:08a Hsingyingchung
// [TAG]  		EIP112631
// [Category]  	Improvement
// [Description]  	
// Add:
// 1. Support IA core and Ring voltage offset negative in OC mailbox.
// 2. Add Filter PLL function, please change
// "HASWELL_PERFTUNE_CPU_FILTER_PLL_SUPPORT" token if need to use this
// function.
// 
// Fixed:
// 1. TDP Time Window is now programmed to 8 seconds by default.
// 2. When cold reset, re-enabling FIVR faults and SVID control. 
// 3. Assign max ring ratio in msr 0x620 with ring ratio max value
// support.
// 
// 5     1/14/13 1:54a Crystallee
// [TAG]  		EIP111199
// [Category]  	Improvement
// [Description]  	Provide variable data which constains number of P
// states support.
// 
// 4     12/20/12 10:25a Hsingyingchung
// 
// 3     12/20/12 10:21a Hsingyingchung
// [TAG]  		EIP108128
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	"Max non-turbo ratio" can't show in BIOS setup when first
// boot after flashing BIOS
// [RootCause]  	Doesn't initialize max non-turbo ratio value when first
// boot after flashing BIOS.
// [Solution]  	Add initialize code for max non-turbo ratio.
// 
// 2     11/23/12 2:09a Hsingyingchung
// [TAG]  		EIP99095
// [Category]  	Improvement
// [Description]  	Update by XTU 4.X
// 
// 1     2/07/12 3:58a Davidhsieh
//
//
//**********************************************************************

//<AMI_FHDR_START>
//---------------------------------------------------------------------------
//
// Name:        CpuDxeFuncs.c
//
// Description:
//  Installs CPU Architectural Protocol.
//  processor interrupt vector table. The CPU Architectural
//  Protocol enables/disables/get state of interrupts, set
//  memory range cache type, and installs/uninstalls
//  interrupt handlers.
//
//---------------------------------------------------------------------------
//<AMI_FHDR_END>

#include <Setup.h>
#include <token.h>
#include <AmiCspLib.h>
#include <Protocol\AmiCpuInfo.h>
#include "CpuDxe.h"

extern EFI_SYSTEM_TABLE         *pST;
extern EFI_BOOT_SERVICES 		*pBS;
extern EFI_RUNTIME_SERVICES 	*pRS;

extern EFI_GUID gHobListGuid;

#if PERF_TUNE_SUPPORT == 1
#include <Protocol\PerfTuneProtocol.h>
#include "Board\EM\PerfTune\PerfTuneCpuSetup.h"	

static EFI_GUID gAmiInternalFactoryTdcTdpHobGuid = AMI_INTERNAL_FACTORY_TDC_TDP_HOB_GUID;
static EFI_GUID gAmiCpuRatioLimitHobGuid = AMI_INTERNAL_CPU_RATIO_LIMIT;	

AMI_INTERNAL_FACTORY_TDC_TDP_HOB    *gTdcTdpHob = NULL;	
CPU_RATIO_LIMIT_DATA                *gCpuRatioLimitData = NULL;		

OVERCLOCKING_CONFIG_DATA    *gOcConfigData;
EFI_GUID	InternalWdtGuid = PERF_TUNE_WDT_PROTOCOL_GUID;

#if !defined(EDK_RELEASE_VERSION) || (EDK_RELEASE_VERSION < 0x00020000)
#define EFI_POWER_MGMT_INIT_DONE_PROTOCOL_GUID \
  { \
    0xd71db106, 0xe32d, 0x4225, 0xbf, 0xf4, 0xde, 0x6d, 0x77, 0x87, 0x17, 0x61 \
  }

#else
#define EFI_POWER_MGMT_INIT_DONE_PROTOCOL_GUID \
  { \
    0xd71db106, 0xe32d, 0x4225, \
    { \
      0xbf, 0xf4, 0xde, 0x6d, 0x77, 0x87, 0x17, 0x61 \
    } \
  }
#endif
EFI_GUID	gPowerMgmtInitDoneProtocolGuid = EFI_POWER_MGMT_INIT_DONE_PROTOCOL_GUID;
EFI_GUID	gSetupGuid = SETUP_GUID;

#define DXE_PLATFORM_ME_POLICY_GUID \
  { 0x69bf9e8a, 0x4ad6, 0x9a28, 0x87, 0xf3, 0x09, 0xa0, 0x71, 0x29, 0x2a, 0x00}
EFI_GUID    gDxePlatformMePolicyGuid = DXE_PLATFORM_ME_POLICY_GUID;

#define ME_INFO_SETUP_GUID \
  { 0x78259433, 0x7B6D, 0x4DB3, 0x9A, 0xE8, 0x36, 0xC4, 0xC2, 0xC3, 0xA1, 0x7D}
EFI_GUID    gMeSetupInfoGuid = ME_INFO_SETUP_GUID;

#define AMI_CPU_INTERNAL_ME_FW_VERSION_GUID \
  { 0x9b875aac, 0x36ec, 0x4550, 0xa4, 0xae, 0x86, 0xc8, 0x4e, 0x96, 0x76, 0x7e}
EFI_GUID    gAmiCpuMEFwVerGuid = AMI_CPU_INTERNAL_ME_FW_VERSION_GUID;
typedef struct{
    UINT8         MeFirmwareInfo;
    UINT32        MeMajor;
    UINT32        MeMinor;
    UINT32        MeHotFix;
    UINT32        MeBuildNo;
} ME_INFO_SETUP_DATA;

BIOS_SETTING_DATA   *gBiosSettingData;
#endif

#ifndef FVID_MAX_STATES
#define FVID_MAX_STATES 16
#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: NumberOfPStatesSupport
//
// Description: Provide variable data which constains number of P states support
//
// Input:  VOID
//
// Output: VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID NumberOfPStatesSupport(VOID)
{
	EFI_STATUS      Status;
	EFI_GUID        gSetupGuid = SETUP_GUID;
#if PERF_TUNE_SUPPORT == 1
	UINTN           SetupDataSize = sizeof(OC_SETUP_DATA);
	OC_SETUP_DATA	SetupData;
#else
	UINTN           SetupDataSize = sizeof(SETUP_DATA);
	SETUP_DATA		SetupData;
#endif
	P_STATES_DATA 	PStatesData;
	UINT16  mMaxBusRatio;
    UINT16  mMinBusRatio;
    UINT16  BusRatioRange;
    UINT64  MsrPlatformInfo;

#if PERF_TUNE_SUPPORT == 1
	Status = pRS->GetVariable(L"OcSetupData",&gSetupGuid, NULL, &SetupDataSize, &SetupData);
#else
	Status = pRS->GetVariable(L"Setup",&gSetupGuid, NULL, &SetupDataSize, &SetupData);
#endif
	if(EFI_ERROR(Status)) {
		TRACE((-1,"Get Setup variable fail!!\n"));
		return;
	}
	
	if (!EFI_ERROR(Status)) {
		if (!SetupData.EIST) {
			PStatesData.NumberOfPStates = 0;
		}
		else {
			MsrPlatformInfo = ReadMsr(0xce);
			mMaxBusRatio = (UINT16)(Shr64(MsrPlatformInfo, 8) & 0xff);
			mMinBusRatio = (UINT16)(Shr64(MsrPlatformInfo, 40) & 0xff);
			BusRatioRange = mMaxBusRatio - mMinBusRatio;
			
			PStatesData.NumberOfPStates = ((BusRatioRange + 1) < FVID_MAX_STATES ? (BusRatioRange + 1) : FVID_MAX_STATES);
			
			if (SetupData.TurboMode & isTurboModeSupported()) {
				if (PStatesData.NumberOfPStates == FVID_MAX_STATES)
					PStatesData.NumberOfPStates--;            
			}
		}

		Status = pRS->SetVariable(
                    L"NumOfPState",
                    &gSetupGuid,
                    (EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_NON_VOLATILE),
                    sizeof(P_STATES_DATA),
                    &PStatesData
                    );
		if(EFI_ERROR(Status)) {
			TRACE((-1,"Set number of P states variable fail!!\n"));
		}
	}
}

#if PERF_TUNE_SUPPORT == 1




//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: FillXtuGaciData
//
// Description: Fill CPU information for xtu 3.0 specification
//
// Input: VOID
//
// Output:  VOID
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS FillXtuGaciData(
    IN PERF_TUNE_ASL_PROTOCOL		*PerfTuneAslProtocol
)
{
    EFI_STATUS          Status = EFI_UNSUPPORTED;
    UINT8               *Buffer = NULL;
    UINT8               *ptr = NULL;
    UINTN               Len = 0;
    UINT64              PlatformInfo = ReadMsr(MSR_PLATFORM_INFO);    
    UINT16              Bins = Shr64(ReadMsr(MSR_FLEX_RATIO),17) & 0x7;  //overclocking bins supported 
    UINT16              MNTR = gBiosSettingData->ProcessorMul;
    
    //----------------------------CPU Ratio GACI DATA----------------------------
	//	   GACI_DATA	DevNameGaciData {					   ControlID,NumberOfValues,Precision,Flags,DefaultDataValue,MinDataValue,MaxDataValue,MinDisplayValue,MaxDisplayValue}
	static GACI_DATA	CpuMulGaciData	= {BIOS_PROC_MULT_IMPLEMENTATION,			0x0,		0,	  0,			   0,		   0,			0,			   0,				 0};

	//----------------------------CPU TDC GACI DATA----------------------------
	//	   GACI_DATA	DevNameGaciData {					   ControlID,NumberOfValues,Precision,Flags,DefaultDataValue,MinDataValue,MaxDataValue,MinDisplayValue,MaxDisplayValue}
	static GACI_DATA	CpuTdcGaciData	= {BIOS_TDC_VALUE_IMPLEMENTATION,			4096,		3,	  0,			   0,		   0,		  4095,			   0,			 511875};

	//----------------------------CPU TDP GACI DATA----------------------------
	//	   GACI_DATA	DevNameGaciData {					   ControlID,NumberOfValues,Precision,Flags,DefaultDataValue,MinDataValue,MaxDataValue,MinDisplayValue,MaxDisplayValue}
	static GACI_DATA	CpuTdpGaciData	= {BIOS_TDP_VALUE_IMPLEMENTATION,			4096,		3,	  0,			   0,		   0,		  4095,			   0,			 511875};

	//-------------------TOTAL DESIGN POWER LOCK SWITCH DATA----------------------------
	//	   GACI_DATA	DevNameGaciData {								   ControlID,NumberOfValues,Precision,Flags,DefaultDataValue,MinDataValue,MaxDataValue,MinDisplayValue,MaxDisplayValue}
	static GACI_DATA	ExtTDPSwGaciData= {BIOS_EXTENDED_TDP_ENABLE_IMPLEMENTATION,				0x2,		0,	  0,			   0,		   0,			1,			   0,				 1};

	//----------------------------CPU Core Ratio Limit GACI DATA----------------------------
	//	   GACI_DATA	DevNameGaciData {								   ControlID,NumberOfValues,Precision,Flags,DefaultDataValue,MinDataValue,MaxDataValue,MinDisplayValue,MaxDisplayValue}
	static GACI_DATA	Cpu1CoreRatioLimGaci	=  {BIOS_1_CORE_RATIO_IMPLEMENTATION,			0x1,		0,	  0,			   0,		   0,			0,			   0,				 0};
	//	   GACI_DATA	DevNameGaciData {								   ControlID,NumberOfValues,Precision,Flags,DefaultDataValue,MinDataValue,MaxDataValue,MinDisplayValue,MaxDisplayValue}
	static GACI_DATA	Cpu2CoreRatioLimGaci	=  {BIOS_2_CORE_RATIO_IMPLEMENTATION,			0x1,		0,	  0,			   0,		   0,			0,			   0,				 0};
	//	   GACI_DATA	DevNameGaciData {								   ControlID,NumberOfValues,Precision,Flags,DefaultDataValue,MinDataValue,MaxDataValue,MinDisplayValue,MaxDisplayValue}
	static GACI_DATA	Cpu3CoreRatioLimGaci	=  {BIOS_3_CORE_RATIO_IMPLEMENTATION,			0x1,		0,	  0,			   0,		   0,			0,			   0,				 0};
	//	   GACI_DATA	DevNameGaciData {								   ControlID,NumberOfValues,Precision,Flags,DefaultDataValue,MinDataValue,MaxDataValue,MinDisplayValue,MaxDisplayValue}
	static GACI_DATA	Cpu4CoreRatioLimGaci	=  {BIOS_4_CORE_RATIO_IMPLEMENTATION,			0x1,		0,	  0,			   0,		   0,			0,			   0,				 0};
	//	   GACI_DATA	DevNameGaciData {								   ControlID,NumberOfValues,Precision,Flags,DefaultDataValue,MinDataValue,MaxDataValue,MinDisplayValue,MaxDisplayValue}
	static GACI_DATA	Cpu5CoreRatioLimGaci	=  {BIOS_5_CORE_RATIO_IMPLEMENTATION,			0x1,		0,	  0,			   0,		   0,			0,			   0,				 0};
	//	   GACI_DATA	DevNameGaciData {								   ControlID,NumberOfValues,Precision,Flags,DefaultDataValue,MinDataValue,MaxDataValue,MinDisplayValue,MaxDisplayValue}
	static GACI_DATA	Cpu6CoreRatioLimGaci	=  {BIOS_6_CORE_RATIO_IMPLEMENTATION,			0x1,		0,	  0,			   0,		   0,			0,			   0,				 0};
	
	//----------------------------CPU Turbo Mode GACI DATA----------------------------
	//	   GACI_DATA	DevNameGaciData {								   ControlID,NumberOfValues,Precision,Flags,DefaultDataValue,MinDataValue,MaxDataValue,MinDisplayValue,MaxDisplayValue}
	static GACI_DATA	TurboModeGaciData	=	{BIOS_TURBO_ENABLE_IMPLEMENTATION,				0x2,		0,	  0,			   1,		   0,			1,			   0,				 1};

	//----------------------------CPU Max Turbo Mode Cpu Voltage GACI DATA----------------------------
	//	   GACI_DATA	DevNameGaciData {								   ControlID,NumberOfValues,Precision,Flags,DefaultDataValue,MinDataValue,MaxDataValue,MinDisplayValue,MaxDisplayValue}
	static GACI_DATA	TMCpuVoltGaci	= {BIOS_MAX_TURBO_MODE_CPU_VOLTAGE_IMPLEMENTATION,		256,		5,	  0,			   0,		   0,		  255,			   0,		 99609375};

	//----------------------------CPU EIST GACI DATA----------------------------
	//	   GACI_DATA	DevNameGaciData {								   ControlID,NumberOfValues,Precision,Flags,DefaultDataValue,MinDataValue,MaxDataValue,MinDisplayValue,MaxDisplayValue}
	static GACI_DATA	EistGaciData		= {BIOS_EIST_IMPLEMENTATION,						0x2,		0,	  0,			   1,		   0,			1,			   0,				 1};

	//----------------------------CPU TDP Related GACI DATA----------------------------
	//	   GACI_DATA	DevNameGaciData {								   ControlID,NumberOfValues,Precision,Flags,DefaultDataValue,MinDataValue,MaxDataValue,MinDisplayValue,MaxDisplayValue}
	static GACI_DATA	ShortTDPSwGaciData= {BIOS_SHORT_TDP_ENABLE_IMPLEMENTATION,				0x2,		0,	  0,			   1,		   0,			1,			   0,				 1};

	//	   GACI_DATA	DevNameGaciData {								   ControlID,NumberOfValues,Precision,Flags,DefaultDataValue,MinDataValue,MaxDataValue,MinDisplayValue,MaxDisplayValue}
	static GACI_DATA	ShortTdpGaci	= {BIOS_SHORT_TDP_IMPLEMENTATION,						513,		0,	  0,			   0,		    0,		   512,			     0,			   512};
	//	   GACI_DATA	DevNameGaciData {								   ControlID,NumberOfValues,Precision,Flags,DefaultDataValue,MinDataValue,MaxDataValue,MinDisplayValue,MaxDisplayValue}
	//static GACI_DATA	ExtTdpGaci	= {BIOS_EXTENDED_TDP_IMPLEMENTATION,						4096,		3,	  0,			   0,		   0,		  4095,			   0,			 511875};
	static GACI_DATA	ExtTdpGaci	= {BIOS_EXTENDED_TDP_IMPLEMENTATION,					    513,		0,	  0,			   0,		    0,		   512,			     0,			   512};

	//	   GACI_DATA	DevNameGaciData {								   ControlID,NumberOfValues,Precision,Flags,DefaultDataValue,MinDataValue,MaxDataValue,MinDisplayValue,MaxDisplayValue}
	static GACI_DATA	ExtTdpTimeGaci	= {BIOS_EXTENDED_TIME_WINDOW_IMPLEMENTATION,		 0xFFFF,		0,	  0,			   1,		    0,           0,	             0,              0};

	//----------------------------IA CORE CURRENT MAX--------------------------
	//	   GACI_DATA	DevNameGaciData {				  ControlID,		  NumberOfValues,Precision,Flags,DefaultDataValue,MinDataValue,MaxDataValue,MinDisplayValue,MaxDisplayValue}
	static GACI_DATA	IACoreAmpGaci	= {BIOS_PACKAGE_CURRENT_LIMIT_IMPLEMENTATION, 	8192,		3,	   0,		   0,			0,			8191,			0,		 1023875};

	//----------------------------IGFX CORE CURRENT MAX--------------------------
	//	   GACI_DATA	DevNameGaciData {								ControlID,NumberOfValues,Precision,Flags,DefaultDataValue,MinDataValue,MaxDataValue,MinDisplayValue,MaxDisplayValue}
	//static GACI_DATA	iGFXCoreAmpGaci = {BIOS_IGFX_CORE_CURRENT_MAX_IMPLEMENTATION,		8192,		3,	  0,			   0,		   0,		   8191,			  0,	 1023875};


	//----------------------------INTERNAL PLL Overvoltage Enable--------------------------	
	//	   GACI_DATA	DevNameGaciData {								   ControlID,NumberOfValues,Precision,Flags,DefaultDataValue,MinDataValue,MaxDataValue,MinDisplayValue,MaxDisplayValue}
	static GACI_DATA	iPLLOvGaci = {BIOS_CPU_PLL_VOLTAGE_UNLOCK_ENABLE_IMPLEMENTATION, 		 0x2,		 0,	  0,			   0,		    0,		     1,			     0,		         1};

	//----------------------------Overclocking Lock GACI DATA----------------------------
	//	   GACI_DATA	DevNameGaciData {								   ControlID,NumberOfValues,Precision,Flags,DefaultDataValue,MinDataValue,MaxDataValue,MinDisplayValue,MaxDisplayValue}
	static GACI_DATA	OverclockingGaciData	=	{BIOS_OVERCLOCKING_ENABLE_IMPLEMENTATION,	0x2,		0,	  0,			   1,		   0,			1,			   0,				 1};

	//----------------------------Overclocking Related GACI DATA----------------------------
    //IA core
	//	   GACI_DATA	DevNameGaciData {								   ControlID,NumberOfValues,Precision,Flags,DefaultDataValue,MinDataValue,MaxDataValue,MinDisplayValue,MaxDisplayValue}
	static GACI_DATA	CPUVoltOverrideGaci	= {BIOS_CPU_VOLTAGE_IMPLEMENTATION,	               2001,	    3,	  0,	           0,	        0,        2000,			     0,           2000};
	//	   GACI_DATA	DevNameGaciData {								   ControlID,NumberOfValues,Precision,Flags,DefaultDataValue,MinDataValue,MaxDataValue,MinDisplayValue,MaxDisplayValue}
	static GACI_DATA	CPUVoltModeGaci	= {BIOS_IA_CORE_VOLTAGE_MODE_IMPLEMENTATION,		      2,		0,	  0,			   0,		    0,		     1,			     0,				 1};
	//	   GACI_DATA	DevNameGaciData {								   ControlID,NumberOfValues,Precision,Flags,DefaultDataValue,MinDataValue,MaxDataValue,MinDisplayValue,MaxDisplayValue}
	static GACI_DATA	CPUVoltOffsetGaci = {BIOS_CPU_VOLTAGE_OFFSET_IMPLEMENTATION,		   2001,	    0,	  0,			1000,           0,	      2000,	    0xFFFFFc18,           1000};

    //RING
	//	   GACI_DATA	DevNameGaciData {								   ControlID,NumberOfValues,Precision,Flags,DefaultDataValue,MinDataValue,MaxDataValue,MinDisplayValue,MaxDisplayValue}
	static GACI_DATA	RINGRatioGaci	= { BIOS_RING_RATIO_IMPLEMENTATION,	        	          1,	    0,	  0,			   0,		    0,		     0,			     0,		         0};
	//	   GACI_DATA	DevNameGaciData {								   ControlID,NumberOfValues,Precision,Flags,DefaultDataValue,MinDataValue,MaxDataValue,MinDisplayValue,MaxDisplayValue}
	static GACI_DATA	RINGVoltOverrideGaci	= {BIOS_RING_VOLTAGE_OVERRIDE_IMPLEMENTATION,  2001,	    3,	  0,	           0,	        0,        2000,			     0,           2000};
	//	   GACI_DATA	DevNameGaciData {								   ControlID,NumberOfValues,Precision,Flags,DefaultDataValue,MinDataValue,MaxDataValue,MinDisplayValue,MaxDisplayValue}
	static GACI_DATA	RINGVoltModeGaci	=	{BIOS_RING_VOLTAGE_MODE_IMPLEMENTATION, 	      2,		0,	  0,			   0,		    0,			 1,			     0,				 1};
	//	   GACI_DATA	DevNameGaciData {								   ControlID,NumberOfValues,Precision,Flags,DefaultDataValue,MinDataValue,MaxDataValue,MinDisplayValue,MaxDisplayValue}
	static GACI_DATA	RINGVoltOffsetGaci	= {BIOS_RING_VOLTAGE_OFFSET_IMPLEMENTATION,		   2001,	    0,	  0,			1000,           0,	      2000,	    0xFFFFFc18,           1000};

    //SVID and FIVR
	//	   GACI_DATA	DevNameGaciData {								   ControlID,NumberOfValues,Precision,Flags,DefaultDataValue,MinDataValue,MaxDataValue,MinDisplayValue,MaxDisplayValue}
	static GACI_DATA	SVIDControlGaci	=	{BIOS_DYNAMIC_SVID_CONTROL_IMPLEMENTATION,			0x2,		0,	  0,			   1,		    0,			1,			     0,				 1};
	//	   GACI_DATA	DevNameGaciData {								   ControlID,NumberOfValues,Precision,Flags,DefaultDataValue,MinDataValue,MaxDataValue,MinDisplayValue,MaxDisplayValue}
	static GACI_DATA	SVIDVoltOverrideGaci	= {BIOS_SVID_VOLTAGE_OVERRIDE_IMPLEMENTATION,  2501,	     3,   0,	           0,	        0,        2500,			     0,          2500};
	//	   GACI_DATA	DevNameGaciData {								   ControlID,NumberOfValues,Precision,Flags,DefaultDataValue,MinDataValue,MaxDataValue,MinDisplayValue,MaxDisplayValue}
	static GACI_DATA	FivrFaultsGaciData	=	{BIOS_FIVR_FAULTS_IMPLEMENTATION,				0x2,		0,	  0,			   1,		    0,		     1,			     0,				 1};
	//	   GACI_DATA	DevNameGaciData {								        ControlID,NumberOfValues,Precision,Flags,DefaultDataValue,MinDataValue,MaxDataValue,MinDisplayValue,MaxDisplayValue}
	static GACI_DATA	FivrEfficiencyGaciData	=	{BIOS_FIVR_EFFICIENCY_MANAGEMENT_IMPLEMENTATION, 0x2,		 0,	   0,			    1,		     0,			  1,		      0,	    	  1};

#if HASWELL_PERFTUNE_CPU_FILTER_PLL_SUPPORT == 1    
	//Filter PLL Frequency
	static GACI_DATA	FilterPLLGaciData	=	{BIOS_FILTER_PLL_FREQUENCY_IMPLEMENTATION, 0x2,		 0,	   0,			    1,		     0,			  1,		      0,	    	  1};
#endif
    
	TRACE((-1, "XTU Fill XTU Cpu Gaci data\n"));
	
	//--1. CPU ratio GACI DATA--------------------------------------------
	//CpuMulGaciData.MinDataValue = (UINT16)(Shr64(PlatformInfo, 40) & 0xFF);
	//CpuMulGaciData.MaxDataValue = (UINT16)(Shr64(PlatformInfo, 8) & 0xFF);

	//CpuMulGaciData.MinDisplayValue = (UINT16)(Shr64(PlatformInfo, 40) & 0xFF);
	//CpuMulGaciData.MaxDisplayValue = (UINT16)(Shr64(PlatformInfo, 8) & 0xFF);

	//CpuMulGaciData.NumberOfValues = CpuMulGaciData.MaxDataValue - CpuMulGaciData.MinDataValue + 1;
	//CpuMulGaciData.DefaultDataValue = (UINT16)(Shr64(PlatformInfo, 8) & 0xFF);

	//Len = sizeof(GACI_DATA);
	//Buffer = MallocZ(Len);
	//if(!Buffer) return EFI_OUT_OF_RESOURCES;

	//MemCpy(Buffer, &CpuMulGaciData, sizeof(CpuMulGaciData));
	//Status = PerfTuneAslProtocol->SetGaciData(Buffer, Len);
	//pBS->FreePool(Buffer);
    CpuMulGaciData.MinDataValue = (UINT16)(Shr64(PlatformInfo, 40) & 0xFF);
    CpuMulGaciData.MaxDataValue = (UINT16)gCpuRatioLimitData->MaxNonTurboRatio;
 	CpuMulGaciData.MinDisplayValue = (UINT16)(Shr64(PlatformInfo, 40) & 0xFF);
  	CpuMulGaciData.MaxDisplayValue = (UINT16)gCpuRatioLimitData->MaxNonTurboRatio;
   	CpuMulGaciData.NumberOfValues = CpuMulGaciData.MaxDataValue - CpuMulGaciData.MinDataValue + 1;
   	CpuMulGaciData.DefaultDataValue = (UINT16)gCpuRatioLimitData->MaxNonTurboRatio;
   	Len = sizeof(GACI_DATA);
   	Buffer = MallocZ(Len);
   	if(!Buffer) return EFI_OUT_OF_RESOURCES;
   	MemCpy(Buffer, &CpuMulGaciData, sizeof(CpuMulGaciData));
   	Status = PerfTuneAslProtocol->SetGaciData(Buffer, Len);
   	pBS->FreePool(Buffer);


    //--2. CPU TDC GACI DATA--------------------------------------------
	CpuTdcGaciData.DefaultDataValue = (UINT16)(gTdcTdpHob->Tdc);
	Len = sizeof(GACI_DATA);
	Buffer = MallocZ(Len);
	if(!Buffer) return EFI_OUT_OF_RESOURCES;

	MemCpy(Buffer, &CpuTdcGaciData, Len);
	Status = PerfTuneAslProtocol->SetGaciData(Buffer, Len);
	pBS->FreePool(Buffer);


	//--3. CPU TDP GACI DATA--------------------------------------------
	CpuTdpGaciData.DefaultDataValue = (UINT16)(gTdcTdpHob->Tdp);
	Len = sizeof(GACI_DATA);
	Buffer = MallocZ(Len);
	if(!Buffer) return EFI_OUT_OF_RESOURCES;

	MemCpy(Buffer, &CpuTdpGaciData, sizeof(GACI_DATA));
	Status = PerfTuneAslProtocol->SetGaciData(Buffer, Len);
	pBS->FreePool(Buffer);

	//--4. TOTAL DESIGN POWER LOCK SWITCH DATA----------------------------
	Len = sizeof(GACI_DATA);
	Buffer = MallocZ(Len);
	if(!Buffer) return EFI_OUT_OF_RESOURCES;

	MemCpy(Buffer, &ExtTDPSwGaciData, sizeof(GACI_DATA));
	Status = PerfTuneAslProtocol->SetGaciData(Buffer, Len);
	pBS->FreePool(Buffer);	

	//--5. CPU Cores ratio limit GACI DATA--------------------------------------------
	Cpu1CoreRatioLimGaci.MinDataValue = MNTR;
	Cpu1CoreRatioLimGaci.MinDisplayValue = MNTR;

	MemCpy(&(Cpu2CoreRatioLimGaci.NumberOfValues), &(Cpu1CoreRatioLimGaci.NumberOfValues), sizeof(GACI_DATA) - sizeof(UINT32));
	MemCpy(&(Cpu3CoreRatioLimGaci.NumberOfValues), &(Cpu1CoreRatioLimGaci.NumberOfValues), sizeof(GACI_DATA) - sizeof(UINT32));
	MemCpy(&(Cpu4CoreRatioLimGaci.NumberOfValues), &(Cpu1CoreRatioLimGaci.NumberOfValues), sizeof(GACI_DATA) - sizeof(UINT32));
	MemCpy(&(Cpu5CoreRatioLimGaci.NumberOfValues), &(Cpu1CoreRatioLimGaci.NumberOfValues), sizeof(GACI_DATA) - sizeof(UINT32));
	MemCpy(&(Cpu6CoreRatioLimGaci.NumberOfValues), &(Cpu1CoreRatioLimGaci.NumberOfValues), sizeof(GACI_DATA) - sizeof(UINT32));		

    Cpu1CoreRatioLimGaci.MaxDataValue = (Bins == 0x7)? 80 : (UINT16)gTdcTdpHob->OneCoreRatioLimit + (UINT16)Bins;
    Cpu1CoreRatioLimGaci.MaxDisplayValue = (Bins == 0x7)? 80 : (UINT16)gTdcTdpHob->OneCoreRatioLimit + (UINT16)Bins;
    Cpu1CoreRatioLimGaci.NumberOfValues = Cpu1CoreRatioLimGaci.MaxDataValue - Cpu1CoreRatioLimGaci.MinDataValue + 1;

    Cpu2CoreRatioLimGaci.MaxDataValue = (Bins == 0x7)? 80 : (UINT16)gTdcTdpHob->TwoCoreRatioLimit + (UINT16)Bins;
    Cpu2CoreRatioLimGaci.MaxDisplayValue = (Bins == 0x7)? 80 : (UINT16)gTdcTdpHob->TwoCoreRatioLimit + (UINT16)Bins;
    Cpu2CoreRatioLimGaci.NumberOfValues = Cpu2CoreRatioLimGaci.MaxDataValue - Cpu2CoreRatioLimGaci.MinDataValue + 1;

    Cpu3CoreRatioLimGaci.MaxDataValue = (Bins == 0x7)? 80 : (UINT16)gTdcTdpHob->ThreeCoreRatioLimit + (UINT16)Bins;
    Cpu3CoreRatioLimGaci.MaxDisplayValue = (Bins == 0x7)? 80 : (UINT16)gTdcTdpHob->ThreeCoreRatioLimit + (UINT16)Bins;
    Cpu3CoreRatioLimGaci.NumberOfValues = Cpu3CoreRatioLimGaci.MaxDataValue - Cpu3CoreRatioLimGaci.MinDataValue + 1;

    Cpu4CoreRatioLimGaci.MaxDataValue = (Bins == 0x7)? 80 : (UINT16)gTdcTdpHob->FourCoreRatioLimit + (UINT16)Bins;
    Cpu4CoreRatioLimGaci.MaxDisplayValue = (Bins == 0x7)? 80 : (UINT16)gTdcTdpHob->FourCoreRatioLimit + (UINT16)Bins;
    Cpu4CoreRatioLimGaci.NumberOfValues = Cpu4CoreRatioLimGaci.MaxDataValue - Cpu4CoreRatioLimGaci.MinDataValue + 1;

    Cpu5CoreRatioLimGaci.MaxDataValue = (Bins == 0x7)? 80 : (UINT16)gTdcTdpHob->FiveCoreRatioLimit + (UINT16)Bins;
    Cpu5CoreRatioLimGaci.MaxDisplayValue = (Bins == 0x7)? 80 : (UINT16)gTdcTdpHob->FiveCoreRatioLimit + (UINT16)Bins;
    Cpu5CoreRatioLimGaci.NumberOfValues = Cpu5CoreRatioLimGaci.MaxDataValue - Cpu5CoreRatioLimGaci.MinDataValue + 1;

    Cpu6CoreRatioLimGaci.MaxDataValue = (Bins == 0x7)? 80 : (UINT16)gTdcTdpHob->SixCoreRatioLimit + (UINT16)Bins;
    Cpu6CoreRatioLimGaci.MaxDisplayValue = (Bins == 0x7)? 80 : (UINT16)gTdcTdpHob->SixCoreRatioLimit + (UINT16)Bins;
    Cpu6CoreRatioLimGaci.NumberOfValues = Cpu6CoreRatioLimGaci.MaxDataValue - Cpu6CoreRatioLimGaci.MinDataValue + 1;

	gTdcTdpHob->OneCoreRatioMax = Cpu1CoreRatioLimGaci.MaxDataValue;
	gTdcTdpHob->TwoCoreRatioMax = Cpu2CoreRatioLimGaci.MaxDataValue;
	gTdcTdpHob->ThreeCoreRatioMax = Cpu3CoreRatioLimGaci.MaxDataValue;
	gTdcTdpHob->FourCoreRatioMax = Cpu4CoreRatioLimGaci.MaxDataValue;
	gTdcTdpHob->FiveCoreRatioMax = Cpu5CoreRatioLimGaci.MaxDataValue;
	gTdcTdpHob->SixCoreRatioMax = Cpu6CoreRatioLimGaci.MaxDataValue;


	Cpu1CoreRatioLimGaci.DefaultDataValue = (UINT16)(gTdcTdpHob->OneCoreRatioLimit);
	Cpu2CoreRatioLimGaci.DefaultDataValue = (UINT16)(gTdcTdpHob->TwoCoreRatioLimit);
	Cpu3CoreRatioLimGaci.DefaultDataValue = (UINT16)(gTdcTdpHob->ThreeCoreRatioLimit);
	Cpu4CoreRatioLimGaci.DefaultDataValue = (UINT16)(gTdcTdpHob->FourCoreRatioLimit);
	Cpu5CoreRatioLimGaci.DefaultDataValue = (UINT16)(gTdcTdpHob->FiveCoreRatioLimit);
	Cpu6CoreRatioLimGaci.DefaultDataValue = (UINT16)(gTdcTdpHob->SixCoreRatioLimit);

	Len = sizeof(GACI_DATA);
	Buffer = MallocZ(Len);
	if(!Buffer) return EFI_OUT_OF_RESOURCES;

	MemCpy(Buffer, &Cpu1CoreRatioLimGaci, sizeof(GACI_DATA));
	Status = PerfTuneAslProtocol->SetGaciData(Buffer, Len);
    if (MNTR > gBiosSettingData->CoreRatioLimit1)
    	Status = PerfTuneAslProtocol->SyncHwValue(Buffer, MNTR);

	MemCpy(Buffer, &Cpu2CoreRatioLimGaci, sizeof(GACI_DATA));
	Status = PerfTuneAslProtocol->SetGaciData(Buffer, Len);
    if (MNTR > gBiosSettingData->CoreRatioLimit2)
    	Status = PerfTuneAslProtocol->SyncHwValue(Buffer, MNTR);

	MemCpy(Buffer, &Cpu3CoreRatioLimGaci, sizeof(GACI_DATA));
	Status = PerfTuneAslProtocol->SetGaciData(Buffer, Len);
    if (MNTR > gBiosSettingData->CoreRatioLimit3)
    	Status = PerfTuneAslProtocol->SyncHwValue(Buffer, MNTR);

	MemCpy(Buffer, &Cpu4CoreRatioLimGaci, sizeof(GACI_DATA));
	Status = PerfTuneAslProtocol->SetGaciData(Buffer, Len);
    if (MNTR > gBiosSettingData->CoreRatioLimit4)
    	Status = PerfTuneAslProtocol->SyncHwValue(Buffer, MNTR);

	MemCpy(Buffer, &Cpu5CoreRatioLimGaci, sizeof(GACI_DATA));
	Status = PerfTuneAslProtocol->SetGaciData(Buffer, Len);
    if (MNTR > gBiosSettingData->CoreRatioLimit5)
    	Status = PerfTuneAslProtocol->SyncHwValue(Buffer, MNTR);

	MemCpy(Buffer, &Cpu6CoreRatioLimGaci, sizeof(GACI_DATA));
	Status = PerfTuneAslProtocol->SetGaciData(Buffer, Len);  
    if (MNTR > gBiosSettingData->CoreRatioLimit6)
    	Status = PerfTuneAslProtocol->SyncHwValue(Buffer, MNTR);

	pBS->FreePool(Buffer);
  	pBS->FreePool(gBiosSettingData);   

	//--6. Turbo Mode GACI DATA--------------------------------------------
	Len = sizeof(TurboModeGaciData);
	Buffer = MallocZ(Len);
	if(!Buffer) return EFI_OUT_OF_RESOURCES;

	MemCpy(Buffer, &TurboModeGaciData, sizeof(GACI_DATA));
	Status = PerfTuneAslProtocol->SetGaciData(Buffer, Len);
	pBS->FreePool(Buffer);

	//--7. Max Turbo Mode CPU Voltage-------------------------------------
	Len = sizeof(TMCpuVoltGaci);
	Buffer = MallocZ(Len);
	if(!Buffer) return EFI_OUT_OF_RESOURCES;

	MemCpy(Buffer, &TMCpuVoltGaci, sizeof(GACI_DATA));
	Status = PerfTuneAslProtocol->SetGaciData(Buffer, Len);
	pBS->FreePool(Buffer);

	//--8. CPU EIST GACI DATA-------------------------------------
	Len = sizeof(EistGaciData);
	Buffer = MallocZ(Len);
	if(!Buffer) return EFI_OUT_OF_RESOURCES;

	MemCpy(Buffer, &EistGaciData, sizeof(GACI_DATA));
	Status = PerfTuneAslProtocol->SetGaciData(Buffer, Len);
	pBS->FreePool(Buffer);

	//--9. ShortTdpGaci------------------------------------------
	//ShortTdpGaci.DefaultDataValue = (UINT16)(gTdcTdpHob->Tdc);
	ShortTdpGaci.DefaultDataValue = (UINT16)(gTdcTdpHob->Tdc / 8 );      
	Len = sizeof(ShortTdpGaci);
	Buffer = MallocZ(Len);
	if(!Buffer) return EFI_OUT_OF_RESOURCES;
	MemCpy(Buffer, &ShortTdpGaci, sizeof(GACI_DATA));
	Status = PerfTuneAslProtocol->SetGaciData(Buffer, Len);
	pBS->FreePool(Buffer);

	//--   ShortTDPSwGaci------------------------------------------
	Len = sizeof(ShortTDPSwGaciData);
	Buffer = MallocZ(Len);
	if(!Buffer) return EFI_OUT_OF_RESOURCES;
	MemCpy(Buffer, &ShortTDPSwGaciData, sizeof(GACI_DATA));
	Status = PerfTuneAslProtocol->SetGaciData(Buffer, Len);
	pBS->FreePool(Buffer);

	//--10.ExtTdpGaci------------------------------------------
	//ExtTdpGaci.DefaultDataValue = (UINT16)(gTdcTdpHob->Tdp);
	ExtTdpGaci.DefaultDataValue = (UINT16)(gTdcTdpHob->Tdp / 8 );      
	Len = sizeof(ExtTdpGaci);
	Buffer = MallocZ(Len);
	if(!Buffer) return EFI_OUT_OF_RESOURCES;
	MemCpy(Buffer, &ExtTdpGaci, sizeof(GACI_DATA));
	Status = PerfTuneAslProtocol->SetGaciData(Buffer, Len);
	pBS->FreePool(Buffer);

	//--   ExtTdpTimeGaci------------------------------------------
	ExtTdpTimeGaci.DefaultDataValue = 8;	// For desktop, default is 8.
 	Len = sizeof(ExtTdpTimeGaci);
	Buffer = MallocZ(Len);
	if(!Buffer) return EFI_OUT_OF_RESOURCES;
	MemCpy(Buffer, &ExtTdpTimeGaci, sizeof(GACI_DATA));
	Status = PerfTuneAslProtocol->SetGaciData(Buffer, Len);
	pBS->FreePool(Buffer);


	//11.IA CORE CRUUENT MAX----------------------------------------------------
	IACoreAmpGaci.DefaultDataValue = (UINT16)(gTdcTdpHob->IaCoreCurrentMax);
	Len = sizeof(IACoreAmpGaci);
	Buffer = MallocZ(Len);
	if(!Buffer) return EFI_OUT_OF_RESOURCES;

	MemCpy(Buffer, &IACoreAmpGaci, sizeof(GACI_DATA));
	Status = PerfTuneAslProtocol->SetGaciData(Buffer, Len);
	pBS->FreePool(Buffer);

	//12.iGFX CORE CURRENT MAX--------------------------------------------------		
	//iGFXCoreAmpGaci.DefaultDataValue = (UINT16)(gTdcTdpHob->IGfxCoreCurrentMax);
	//Len = sizeof(iGFXCoreAmpGaci);
	//Buffer = MallocZ(Len);
	//if(!Buffer) return EFI_OUT_OF_RESOURCES;

	//MemCpy(Buffer, &iGFXCoreAmpGaci, sizeof(GACI_DATA));
	//Status = PerfTuneAslProtocol->SetGaciData(Buffer, Len);
	//pBS->FreePool(Buffer);


	//13.INTERNAL PLL OVERVOLTAGE ENABLE---------------------------
	Len = sizeof(iPLLOvGaci);
	Buffer = MallocZ(Len);
	if(!Buffer) return EFI_OUT_OF_RESOURCES;
     
	MemCpy(Buffer, &iPLLOvGaci, sizeof(GACI_DATA));
	Status = PerfTuneAslProtocol->SetGaciData(Buffer, Len);
	pBS->FreePool(Buffer);

	//--14. Overclocking Enable GACI DATA-------------------------------------
	Len = sizeof(OverclockingGaciData);
	Buffer = MallocZ(Len);
	if(!Buffer) return EFI_OUT_OF_RESOURCES;

	MemCpy(Buffer, &OverclockingGaciData, sizeof(GACI_DATA));
	Status = PerfTuneAslProtocol->SetGaciData(Buffer, Len);
	pBS->FreePool(Buffer);
	//--15. Overclocking Feature GACI DATA-------------------------------------
//IA core
    //CPU voltage override
	Len = sizeof(CPUVoltOverrideGaci);
	Buffer = MallocZ(Len);
	if(!Buffer) return EFI_OUT_OF_RESOURCES;
	MemCpy(Buffer, &CPUVoltOverrideGaci, sizeof(GACI_DATA));
	Status = PerfTuneAslProtocol->SetGaciData(Buffer, Len);
    pBS->FreePool(Buffer);

    //IA core voltage mode
	Len = sizeof(CPUVoltModeGaci);
	Buffer = MallocZ(Len);
	if(!Buffer) return EFI_OUT_OF_RESOURCES;
	MemCpy(Buffer, &CPUVoltModeGaci, sizeof(GACI_DATA));
	Status = PerfTuneAslProtocol->SetGaciData(Buffer, Len);
    pBS->FreePool(Buffer);

    //Dynamic CPU Voltage Offset
	Len = sizeof(CPUVoltOffsetGaci);
	Buffer = MallocZ(Len);
	if(!Buffer) return EFI_OUT_OF_RESOURCES;
	MemCpy(Buffer, &CPUVoltOffsetGaci, sizeof(GACI_DATA));
	Status = PerfTuneAslProtocol->SetGaciData(Buffer, Len);
    pBS->FreePool(Buffer);

//CLR/RING
    //Ring Ratio
    RINGRatioGaci.MaxDataValue = (UINT16)gOcConfigData->OCCap[RING].MaxOcRatioLimit;     
    RINGRatioGaci.MaxDisplayValue = (UINT16)gOcConfigData->OCCap[RING].MaxOcRatioLimit;  
  	RINGRatioGaci.NumberOfValues = RINGRatioGaci.MaxDataValue - RINGRatioGaci.MinDataValue + 1;
  	RINGRatioGaci.DefaultDataValue = (UINT16)gTdcTdpHob->OneCoreRatioLimit;
  	Len = sizeof(RINGRatioGaci);
  	Buffer = MallocZ(Len);
  	if(!Buffer) return EFI_OUT_OF_RESOURCES;
  	MemCpy(Buffer, &RINGRatioGaci, sizeof(GACI_DATA));
  	Status = PerfTuneAslProtocol->SetGaciData(Buffer, Len);
    pBS->FreePool(Buffer);

    //Ring Voltage Override
    Len = sizeof(RINGVoltOverrideGaci);
	Buffer = MallocZ(Len);
	if(!Buffer) return EFI_OUT_OF_RESOURCES;
	MemCpy(Buffer, &RINGVoltOverrideGaci, sizeof(GACI_DATA));
	Status = PerfTuneAslProtocol->SetGaciData(Buffer, Len);
    pBS->FreePool(Buffer);

    //Ring Voltage Mode
	Len = sizeof(RINGVoltModeGaci);
	Buffer = MallocZ(Len);
	if(!Buffer) return EFI_OUT_OF_RESOURCES;
	MemCpy(Buffer, &RINGVoltModeGaci, sizeof(GACI_DATA));
	Status = PerfTuneAslProtocol->SetGaciData(Buffer, Len);
    pBS->FreePool(Buffer);

    //Ring Voltage Offset
	Len = sizeof(RINGVoltOffsetGaci);
	Buffer = MallocZ(Len);
	if(!Buffer) return EFI_OUT_OF_RESOURCES;
	MemCpy(Buffer, &RINGVoltOffsetGaci, sizeof(GACI_DATA));
	Status = PerfTuneAslProtocol->SetGaciData(Buffer, Len);
    pBS->FreePool(Buffer);

//SVID and FIVR
	//SVID Voltage Override
	Len = sizeof(SVIDVoltOverrideGaci);
	Buffer = MallocZ(Len);
	if(!Buffer) return EFI_OUT_OF_RESOURCES;
	MemCpy(Buffer, &SVIDVoltOverrideGaci, sizeof(GACI_DATA));
	Status = PerfTuneAslProtocol->SetGaciData(Buffer, Len);
    pBS->FreePool(Buffer);

	//SVID Control Enable/Disable
	Len = sizeof(SVIDControlGaci);
	Buffer = MallocZ(Len);
	if(!Buffer) return EFI_OUT_OF_RESOURCES;
	MemCpy(Buffer, &SVIDControlGaci, sizeof(GACI_DATA));
	Status = PerfTuneAslProtocol->SetGaciData(Buffer, Len);
	if(gOcConfigData->IsPowerCycle)					
		Status = PerfTuneAslProtocol->SyncHwValue(Buffer, (UINT16)1);	// Re-Enable SVID Control if cold boot 
    pBS->FreePool(Buffer);

    //FIVR FAULTS DISABLE
	Len = sizeof(FivrFaultsGaciData);
	Buffer = MallocZ(Len);
	if(!Buffer) return EFI_OUT_OF_RESOURCES;
	MemCpy(Buffer, &FivrFaultsGaciData, sizeof(GACI_DATA));
	Status = PerfTuneAslProtocol->SetGaciData(Buffer, Len);
	if(gOcConfigData->IsPowerCycle)					
		Status = PerfTuneAslProtocol->SyncHwValue(Buffer, (UINT16)1);	// Re-Enable FIVR FAULTS if cold boot 
	pBS->FreePool(Buffer);

    //FIVR EFFICIENCY DISABLE
	Len = sizeof(FivrEfficiencyGaciData);
	Buffer = MallocZ(Len);
	if(!Buffer) return EFI_OUT_OF_RESOURCES;
	MemCpy(Buffer, &FivrEfficiencyGaciData, sizeof(GACI_DATA));
	Status = PerfTuneAslProtocol->SetGaciData(Buffer, Len);
	pBS->FreePool(Buffer);
	
    pBS->FreePool(gCpuRatioLimitData);

#if HASWELL_PERFTUNE_CPU_FILTER_PLL_SUPPORT == 1
    //Filter PLL
	Len = sizeof(FilterPLLGaciData);
	Buffer = MallocZ(Len);
	if(!Buffer) return EFI_OUT_OF_RESOURCES;
	MemCpy(Buffer, &FilterPLLGaciData, sizeof(GACI_DATA));
	Status = PerfTuneAslProtocol->SetGaciData(Buffer, Len);
	pBS->FreePool(Buffer);
#endif

	return EFI_SUCCESS;

}
//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: IntelXtuFillCpuDataCallBack
//
// Description: Callback function for Intel XTU data init
//
// Input: 
//  IN EFI_EVENT Event
//  IN VOID *Context
//
// Output:  EFI_STATUS
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS IntelXtuFillCpuDataCallBack(
    IN EFI_EVENT Event,
    IN VOID *Context
)
{    
    EFI_STATUS          Status = EFI_UNSUPPORTED;
    EFI_GUID     PerfTuneAslProtocolGuid = PERF_TUNE_ASL_PROTOCOL_GUID;    
	PERF_TUNE_ASL_PROTOCOL	*PerfTuneAslProtocol = NULL;
	
	TRACE((-1, "XTU Fill Cpu Data Callback\n"));
    
    Status = pBS->LocateProtocol(&PerfTuneAslProtocolGuid, NULL, &PerfTuneAslProtocol);
    if(!EFI_ERROR(Status))
        FillXtuGaciData(PerfTuneAslProtocol);
    
    return Status;    
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: CpuPllOverVoltageProgress
//
// Description: CPU pll over voltage initialize code in DXE phase
//
// Input: 
//  IN EFI_EVENT Event
//  IN VOID *Context
//
// Output:  EFI_STATUS
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS CpuPllOverVoltageProgress(    
    IN EFI_EVENT Event,
    IN VOID *Context
)
{
    EFI_GUID    AmiPllOvFlagHobGuid = AMI_PLL_OVER_VOTAGE_FLAG_HOB_GUID;
    EFI_GUID    AmiPllOvFlagDataGuid = AmiPllOvFlagHobGuid;
    EFI_GUID    gHobListGuid    = HOB_LIST_GUID;
    PLL_OV_FLAG_DATA_HOB    *PllOvFlagDataHob;
    UINT64      CoreRatioLimits = ReadMsr(0x1ad);
    EFI_STATUS  Status = EFI_NOT_STARTED;
    VOID        *FirstHob;
    PERF_TUNE_WDT_PROTOCOL *InternalWdtProtocol;
 
    TRACE((-1,"CpuPllOverVoltageProgress Start\n"));

    // Get Hob List
    FirstHob = GetEfiConfigurationTable(pST, &gHobListGuid);
    if (!FirstHob) return EFI_NOT_READY;

    PllOvFlagDataHob = (PLL_OV_FLAG_DATA_HOB*)FirstHob;

    while (!EFI_ERROR(Status = FindNextHobByType(EFI_HOB_TYPE_GUID_EXTENSION,&PllOvFlagDataHob))) {
        if (guidcmp(&PllOvFlagDataHob->EfiHobGuidType.Name,&AmiPllOvFlagHobGuid) == 0) break;
    }
    if (EFI_ERROR(Status)) return EFI_NOT_FOUND;

    Status = EFI_ALREADY_STARTED;

    if((PllOvFlagDataHob->PllOvData.PLLOvFlag == 0x1) && (CoreRatioLimits = 0x060606))
    {        
        //Delay for 1.5 ms
        pBS->Stall(150);        

        PllOvFlagDataHob->PllOvData.PLLOvFlag = 0x2;

        //write back original Core Ratio Limits.
        WriteMsr(0x1ad, PllOvFlagDataHob->PllOvData.OriTurboRatio);

        Status = pRS->SetVariable(
                     L"PLLOvFlag",
                     &AmiPllOvFlagDataGuid,
                     (EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_NON_VOLATILE),
                     sizeof(PLL_OV_FLAG_DATA),
                     &PllOvFlagDataHob->PllOvData
                     );
                     
        ASSERT_EFI_ERROR(Status);

        Status = pBS->LocateProtocol(&InternalWdtGuid, NULL, &InternalWdtProtocol);
        if(!EFI_ERROR(Status))
        {     
            TRACE((-1,"Internal PLL Over Voltage Reset Requirement.\n"));
            //reset
            InternalWdtProtocol->AllowKnownReset();
            IoWrite8 (0xCF9,0x02);
            IoWrite8 (0xCF9,0x06);
            EFI_DEADLOOP();
        }
    }else if(PllOvFlagDataHob->PllOvData.PLLOvFlag== 0x2) {
        //Clear Flag to Zero
        PllOvFlagDataHob->PllOvData.PLLOvFlag = 0x0;
        Status = pRS->SetVariable(
                     L"PLLOvFlag",
                     &AmiPllOvFlagDataGuid,
                     (EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_NON_VOLATILE),
                     sizeof(PLL_OV_FLAG_DATA),
                     &PllOvFlagDataHob->PllOvData
                     );
        ASSERT_EFI_ERROR(Status);

        TRACE((-1,"Clear Pll Overvoltage Flag %r.\n",Status));
    }   

    TRACE((-1,"CpuPllOverVoltageProgress End\n"));

    return Status;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: SaveMEFWVersion
//
// Description: CPU pll over voltage initialize code in DXE phase
//
// Input: 
//  IN EFI_EVENT Event
//  IN VOID *Context
//
// Output:  EFI_STATUS
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS SaveMEFWVersion(    
    IN EFI_EVENT Event,
    IN VOID *Context
)
{
    EFI_STATUS          Status;
    ME_INFO_SETUP_DATA  MeInfoSetupData;
    UINTN               DataSize = sizeof(ME_INFO_SETUP_DATA);

    TRACE((-1,"SaveMEFWVersion start!!\n"));

    pBS->CloseEvent( Event);
    Status = pRS->GetVariable(
                    L"MeInfoSetup",
                    &gMeSetupInfoGuid,
                    NULL,
                    &DataSize,
                    &MeInfoSetupData
                    );
    if(EFI_ERROR(Status)){
        TRACE((-1,"Get ME firmware version fail!!\n"));
        return Status;
    }

    Status = pRS->SetVariable(
                    L"MEFWVersion",
                    &gAmiCpuMEFwVerGuid,
                    (EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_NON_VOLATILE),
                    sizeof(ME_INFO_SETUP_DATA),
                    &MeInfoSetupData
                    );
    if(EFI_ERROR(Status)){
        TRACE((-1,"Set ME firmware version fail!!\n"));
        return Status;
    }

    TRACE((-1,"SaveMEFWVersion end!!\n"));

    return Status;
}
#endif
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: CpuDxeMiscFuncs
//
// Description: 
//
// Input:
//      None
//
// Output:
//      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID CpuDxeMiscFuncs(VOID)
{
    EFI_STATUS  Status;
    
    Status = EFI_SUCCESS;
    
#if PERF_TUNE_SUPPORT == 1
    {    
        
    	EFI_GUID 	PerfTuneAslProtocolGuid = PERF_TUNE_ASL_PROTOCOL_GUID;
        EFI_EVENT   IntelXtuCpuCallbackEvt;
        VOID        *IntelXtuCpuCallbackReg;
        VOID                *FirstHob;	
        EFI_EVENT   PllOvCallbackEvt;
        VOID        *PllOvCallbackReg;
        EFI_EVENT   MEFWCallbackEvt;
        VOID        *MEFWCallbackReg;	
		EFI_GUID    gAmiPerfTuneDataHobGuid    = AMI_PERF_TUNE_DATA_HOB_GUID;
        EFI_GUID    gAmiOcConfigHobGuid = AMI_OVERCLOCK_CONFIG_HOB_GUID;
        UINTN       DataSize;
        OVERCLOCKING_CONFIG_HOB     *OcConfigHob = NULL;	
        CPU_RATIO_LIMIT_HOB         *CpuRatioLimitHob = NULL;	
        UINT32      Attributes = 0;
        
        FirstHob = GetEfiConfigurationTable(pST, &gHobListGuid);

        //If First boot or CPU change is detected, record new MaxNonTurboRatio.
        CpuRatioLimitHob = (CPU_RATIO_LIMIT_HOB*)FirstHob;
        while (!EFI_ERROR(Status = FindNextHobByType(EFI_HOB_TYPE_GUID_EXTENSION, &CpuRatioLimitHob))) {
            if (guidcmp(&CpuRatioLimitHob->EfiHobGuidType.Name, &gAmiCpuRatioLimitHobGuid) == 0){
               if(CpuRatioLimitHob->IsChangeCpu){
                   Status = pRS->SetVariable(
                                L"CpuRatioLimit",
                                &gAmiCpuRatioLimitHobGuid,
                                (EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_NON_VOLATILE),
                                sizeof(CPU_RATIO_LIMIT_DATA),
                                &CpuRatioLimitHob->CpuRatioLimitData );
                   ASSERT_EFI_ERROR(Status);
               }
               break;
            }    
        }

        // get TdcTdpHob.
        gTdcTdpHob = (AMI_INTERNAL_FACTORY_TDC_TDP_HOB*)FirstHob;
        while (!EFI_ERROR(Status = FindNextHobByType(EFI_HOB_TYPE_GUID_EXTENSION, &gTdcTdpHob))) {
            if (guidcmp(&gTdcTdpHob->EfiHobGuidType.Name, &gAmiInternalFactoryTdcTdpHobGuid) == 0){
                
                Status = RegisterProtocolCallback(
                                &PerfTuneAslProtocolGuid,
                                IntelXtuFillCpuDataCallBack,
                                NULL,
                                &IntelXtuCpuCallbackEvt,
                                &IntelXtuCpuCallbackReg
                        );
                        
                ASSERT_EFI_ERROR(Status);
                break;            
            }    
        }
        if(!EFI_ERROR(Status)){
            // get overclocking config HOB
            OcConfigHob = (OVERCLOCKING_CONFIG_HOB*)FirstHob;
            while (!EFI_ERROR(Status = FindNextHobByType(EFI_HOB_TYPE_GUID_EXTENSION, &OcConfigHob))) {
                if (guidcmp(&OcConfigHob->EfiHobGuidType.Name, &gAmiOcConfigHobGuid) == 0){
                    break;            
                }    
            }
   			gOcConfigData = NULL;
            if(!EFI_ERROR(Status))
                gOcConfigData = &OcConfigHob->OverclockData;
     		else
                ASSERT_EFI_ERROR(Status);

            // get Cpu ratio limit default value.
            DataSize = sizeof(CPU_RATIO_LIMIT_DATA);
            Status = pBS->AllocatePool(EfiBootServicesData, DataSize, &gCpuRatioLimitData);
            Status = pRS->GetVariable(
                         L"CpuRatioLimit",
                         &gAmiCpuRatioLimitHobGuid,
                         NULL,
                         &DataSize,
                         gCpuRatioLimitData );
            ASSERT_EFI_ERROR(Status);

            // Restores default value when Cpu change or watch dog timeout.
            if( gOcConfigData->IsCpuRunDefault ){
            SETUP_DATA  *SetupData;
            DataSize = sizeof(SETUP_DATA);
            Status = pBS->AllocatePool(EfiBootServicesData, DataSize, &SetupData);
            Status = pRS->GetVariable(
                        L"Setup",
                        &gSetupGuid,
                        &Attributes,
                        &DataSize,
                        SetupData
                     );
            ASSERT_EFI_ERROR(Status);

            SetupData->LcSbSelect = 0;
            SetupData->PackageCurrentLock = 0;

            Status = pRS->SetVariable(
                        L"Setup",
                        &gSetupGuid,
                        Attributes,
                        sizeof(SETUP_DATA),
                        SetupData
                     );
            ASSERT_EFI_ERROR(Status);
         	pBS->FreePool(SetupData);
            }
        
            // get current setting data of XTU
            DataSize = sizeof(BIOS_SETTING_DATA);
            Status = pBS->AllocatePool(EfiBootServicesData, DataSize, &gBiosSettingData);
         	Status = pRS->GetVariable(
        					L"OcCurrent",
		      		      	&gSetupGuid,
        					NULL,
		      		    	&DataSize,
			         		gBiosSettingData);
        }

        Status = RegisterProtocolCallback(
                            &InternalWdtGuid,
                            CpuPllOverVoltageProgress,
                            NULL,
                            &PllOvCallbackEvt,
                            &PllOvCallbackReg );
        ASSERT_EFI_ERROR(Status);

        Status = RegisterProtocolCallback(
                    &gDxePlatformMePolicyGuid,
                    SaveMEFWVersion,
                    NULL,
                    &MEFWCallbackEvt,
                    &MEFWCallbackReg);
        ASSERT_EFI_ERROR(Status);
    }    
#endif

	NumberOfPStatesSupport();

    return;
}    
