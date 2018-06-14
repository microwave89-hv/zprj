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
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/Haswell/AMI Cpu PKG/CPU Core/CpuPeiBeforeMem.c 8     10/16/13 4:03a Crystallee $
//
// $Revision: 8 $
//
// $Date: 10/16/13 4:03a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/Haswell/AMI Cpu PKG/CPU Core/CpuPeiBeforeMem.c $
// 
// 8     10/16/13 4:03a Crystallee
// [TAG]  		EIP138897
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Locate BIST ppi will fail after disable CAR.
// [RootCause]  	All SEC PPIs must be reinstalled outside of SEC,
// otherwise they will be lost when CAR is no longer used.
// [Solution]  	Reinstall BIST PPI outside of SEC.
// 
// 7     6/03/13 12:04a Hsingyingchung
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	
// 1. Fix PLL setting is invalid once PEG/DMI ratio is 1:1.
// 2. Modify IA core ratio minimun value. Use "max non turbo ratio(MSR
// CEh)" instead of "power on turbo default value".
// 
// 6     4/08/13 12:04a Hsingyingchung
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Limit CPU boot performance at Non-Turbo speed when add
// XTU.
// 
// 5     2/07/13 4:13a Hsingyingchung
// [TAG]  		EIP112631
// [Category]  	Improvement
// [Description]  	Add:
// 1. Support IA core and Ring voltage offset negative in OC mailbox.
// 2. Add Filter PLL function, please change
// "HASWELL_PERFTUNE_CPU_FILTER_PLL_SUPPORT" token if need to use this
// function.
// 
// Fixed:
// 1. TDP Time Window is now programmed to 8 seconds by default.
// 2. When cold reset, re-enabling FIVR faults and SVID control. 
// 3. Initialize OC mailbox for each boot.
// 
// 4     12/20/12 10:15a Hsingyingchung
// [TAG]  		EIP108128
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	"Max non-turbo ratio" can't show in BIOS setup when first
// boot after flashing BIOS
// [RootCause]  	Doesn't initialize max non-turbo ratio value when first
// boot after flashing BIOS.
// [Solution]  	Add initialize code for max non-turbo ratio.
// 
// 3     12/20/12 9:58a Hsingyingchung
// [TAG]  		EIP107712
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	Change core ratio limit is not effective for oc cpu.
// [RootCause]  	The IA core max ratio in mailbox is not same as active
// one core ratio limit in MSR 0x1AD
// [Solution]  	Update the IA core max ratio in mailbox according to
// active one core ratio limit in XTU setting data
// 
// 2     11/23/12 2:09a Hsingyingchung
// [TAG]  		EIP99095
// [Category]  	Improvement
// [Description]  	Update by XTU 4.X
// 
// 1     2/07/12 3:58a Davidhsieh
// 
//**********************************************************************

//<AMI_FHDR_START>
//---------------------------------------------------------------------------
// Name:		CpuPeiBeforeMem.c
//
// Description:	This file is the main contains Cpu code that must execute
// 	before memory.
//
//---------------------------------------------------------------------------
//<AMI_FHDR_END>

#include <Pei.h>
#include <AmiPeiLib.h>
#include "CPU.h"
#include "AmiCspLibInc.h"
#include "token.h"
#include <Ppi\AmiEarlyBistPpi.h>

#if PERF_TUNE_SUPPORT == 1
 #include <Ppi\PerfTunePpi.h>
 #include <PerfTune.h>
 #include "Ppi\CpuPlatformPolicy\CpuPlatformPolicy.h"
 #include <Setup.h>
 #include <PPI\Stall.h>
 #include "Board\EM\PerfTune\PerfTuneCpuSetup.h"
 typedef struct{
  UINT8         MeFirmwareInfo;
  UINT32        MeMajor;
  UINT32        MeMinor;
  UINT32        MeHotFix;
  UINT32        MeBuildNo;
 } ME_INFO_SETUP_DATA;
#define AMI_CPU_INTERNAL_ME_FW_VERSION_GUID \
 {0x9b875aac, 0x36ec, 0x4550, 0xa4, 0xae, 0x86, 0xc8, 0x4e, 0x96, 0x76, 0x7e}
EFI_GUID    gAmiCpuMEFwVerGuid = AMI_CPU_INTERNAL_ME_FW_VERSION_GUID;
#endif


#if PERF_TUNE_SUPPORT == 1

static EFI_GUID gPeiCpuPlatformPolicyGuid = PEI_CPU_PLATFORM_POLICY_PPI_GUID;
static EFI_GUID gPerfTunePpiGuid = PERF_TUNE_PPI_GUID;
static EFI_GUID gWdtPpiGuid = PERF_TUNE_WDT_PPI_GUID;
static EFI_GUID	gAmiOcConfigHobGuid = AMI_OVERCLOCK_CONFIG_HOB_GUID;    
static EFI_GUID	gAmiCpuRatioLimitHobGuid = AMI_INTERNAL_CPU_RATIO_LIMIT;     

EFI_STATUS CpuPeiPolicyNotify(
    IN EFI_PEI_SERVICES **PeiServices,
    IN EFI_PEI_NOTIFY_DESCRIPTOR *NotifyDescriptor,
    IN VOID *NullPpi
);

// PPI that are notified
static EFI_PEI_NOTIFY_DESCRIPTOR mNotifyList[] =
{
    {
        EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
        &gPeiCpuPlatformPolicyGuid,
        CpuPeiPolicyNotify
    }
};

#if HASWELL_PERFTUNE_CPU_FILTER_PLL_SUPPORT == 1
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   PLLFilterFunction
//
// Description: Filter PLL setting High(3.2GHz) or lower(1.6GHz)
//
// Input:
//      EFI_PEI_SERVICES    **PeiServices
//      BIOS_SETTING_DATA   *SettingData
//
// Output:
//      EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PLLFilterFunction (
    IN EFI_PEI_SERVICES **PeiServices,
    IN BIOS_SETTING_DATA *SettingData
)
{
  	UINT8 GpioSel;
  	UINT8 GpRstSel;
  	UINT32 RcbaAddress;
  	UINT8 PmCFG2;
	PERF_TUNE_WDT_PPI       *WdtPpi;  
   
  	//
  	// Set GPIO_USE_SEL[8] to `0'
  	//
  	GpioSel = READ_IO8(GPIO_BASE_ADDRESS + GP_IOREG_USE_SEL); // 0x00
  	GpioSel = GpioSel & 0x7F;
  	WriteIo8 ((GPIO_BASE_ADDRESS + GP_IOREG_USE_SEL), GpioSel);

	//
  	// Set GP_RST_SEL[8] is `1'
  	//
  	GpRstSel = READ_IO8 (GPIO_BASE_ADDRESS + GP_IOREG_GP_RST_SEL1); // 0x60
  	GpRstSel |= BIT8;
  	WriteIo8 ((GPIO_BASE_ADDRESS + GP_IOREG_GP_RST_SEL1), GpRstSel);

  	//
  	//
  	// Set PCH_RCRB_PM_CFG 0x3318 bit 5
  	RcbaAddress = (READ_PCI32 (00, 0x1F, 0x0, 0xF0)) & 0xFFFFF000;
  	PmCFG2 = READ_MEM8 (RcbaAddress + 0x3318);
  	if (SettingData->FilterPLLFrequency){
  		PmCFG2 |= BIT5; //Bit5 set 1
  	}else{
		PmCFG2 &= 0xDF; //Bit5 set 0
  	}
  	WRITE_MEM8 (RcbaAddress + 0x3318, PmCFG2);


  	//
  	//  Issue a CF9h with a power cycle
  	//
    //Let WDT know this is a normal reset.
    (*PeiServices)->LocatePpi(
     				PeiServices,
       				&gWdtPpiGuid,
       				0,
       				NULL,
       				&WdtPpi
       				);
    WdtPpi->AllowKnowReset(PeiServices);
    IoWrite8 (0xCF9,0x0e);
    EFI_DEADLOOP();

  	return EFI_SUCCESS;

}
#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   OverrideNonTurboRatio
//
// Description: Override CPU NonTurbo Ratio Maximum value
//
// Input:
//      EFI_PEI_SERVICES    **PeiServices
//      UINT8               ProcessorMul
//      CPU_CONFIG_PPI      *CpuConfig
//
// Output:
//      EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS OverrideNonTurboRatio(
    IN EFI_PEI_SERVICES **PeiServices,
    IN UINT16 ProcessorMul,
    IN CPU_CONFIG_PPI *CpuConfig
)
{
	EFI_STATUS	Status = EFI_SUCCESS;
	EFI_GUID	PeiReadOnlyVariable2PpiGuid = EFI_PEI_READ_ONLY_VARIABLE2_PPI_GUID;
    EFI_GUID gAmiCpuRatioLimitHobGuid = AMI_INTERNAL_CPU_RATIO_LIMIT;	
	EFI_PEI_READ_ONLY_VARIABLE2_PPI	*ReadOnlyVariable2;
	CPU_RATIO_LIMIT_DATA	CpuRatioLimitData;
	UINTN		VarSize = sizeof(CPU_RATIO_LIMIT_DATA);

    PEI_TRACE((-1, PeiServices, "OverrideNonTurboRatio start!!\n"));

	Status = (*PeiServices)->LocatePpi(
					PeiServices,
					&PeiReadOnlyVariable2PpiGuid,
					0,
					NULL,
					&ReadOnlyVariable2		
					);
	if(EFI_ERROR(Status))return Status;

	Status = ReadOnlyVariable2->GetVariable(
                         ReadOnlyVariable2,
                         L"CpuRatioLimit",
                         &gAmiCpuRatioLimitHobGuid,
                         NULL,
                         &VarSize,
                         &CpuRatioLimitData
                         );
	if(EFI_ERROR(Status))return Status;
	
    //check if cpuratio in PurfTuneCPUSetup is not default Max Non Turbo Ratio.
    if((UINT8)(ProcessorMul & 0xFF) != ((CpuRatioLimitData.MaxNonTurboRatio) & 0xFF)){
        CpuConfig->CpuRatioOverride     = CPU_FEATURE_ENABLE;
        CpuConfig->CpuRatio             = (UINT8)(ProcessorMul & 0xFF);
    }

    PEI_TRACE((-1, PeiServices, "OverrideNonTurboRatio end!!\n"));
	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   PEGDMIRatio
//
// Description: Modify PEG/DMI Ratio for CPU
//
// Input:
//      EFI_PEI_SERVICES    **PeiServices
//      BIOS_SETTING_DATA   *SettingData
//
// Output:
//      EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PEGDMIRatio(
    IN EFI_PEI_SERVICES **PeiServices,
    IN BIOS_SETTING_DATA *SettingData
)
{
	EFI_STATUS	    Status = EFI_SUCCESS;
	UINT32          PciAddress, PciRegData;
    UINT64          PCIEPLLRatio, MsrData;
    EFI_BOOT_MODE   BootMode = (EFI_BOOT_MODE)-1;
	UINT8           Ratio = 0xFF;
	EFI_GUID	    PeiReadOnlyVariable2PpiGuid = EFI_PEI_READ_ONLY_VARIABLE2_PPI_GUID;
    EFI_GUID	    SetupGuid = SETUP_GUID;
	EFI_PEI_READ_ONLY_VARIABLE2_PPI	*ReadOnlyVariable2;
	UINTN		    VarSize = sizeof(SETUP_DATA);
	SETUP_DATA	    SetupData;
    PERF_TUNE_WDT_PPI       *WdtPpi;
    ME_INFO_SETUP_DATA      mMeInfoSetupData;
  	UINTN		            MeVarSize = sizeof(ME_INFO_SETUP_DATA);

    PEI_TRACE((-1, PeiServices, "Change PEGDMIRatio start!!\n"));

    //is SBPLL desired
    //MSR 0x61E , bit2: SBPLL(1) or LCPLL(0).
	Status = (*PeiServices)->LocatePpi(
					PeiServices,
					&PeiReadOnlyVariable2PpiGuid,
					0,
					NULL,
					&ReadOnlyVariable2		
					);
 	if(EFI_ERROR(Status))return Status;
	Status = ReadOnlyVariable2->GetVariable(
                         ReadOnlyVariable2,
                         L"Setup",
                         &SetupGuid,
                         NULL,
                         &VarSize,
                         &SetupData
                         );
	if(EFI_ERROR(Status)){
        PEI_TRACE((-1, PeiServices, " Get SetupData fail!!\n"));
        return Status;
    }
    MsrData = ReadMsr(0x61E);
    PEI_TRACE((-1, PeiServices, "SetupData.LcSbSelect: %x !!\n",SetupData.LcSbSelect));
    MsrData = (SetupData.LcSbSelect)? MsrData | BIT2 : (MsrData & ~(BIT2));
    WriteMsr(0x61E,MsrData);
        
    //read ICC PEG/DMI ratio setting
    PciAddress = (0x1) << 31 | ((0x0) << 16) | ((0x16) << 11) | ((0x0) << 8) | 0x60;
    IoWrite32(0x0cf8,PciAddress);
    PciRegData = IoRead32(0x0cfc);

    //B0:D22:F0, FWstatus3[2:0]
    //000b = 5/5, 1 - Used when BCLK at 100MHz
    //001b = 5/4, 1.25 - Used when BCLK around 125MHz
    //010b = 5/3, 1.66 - Used when BCLK around 166MHz
    //011b = 5/2, 2.5  - Used when BCLK around 250MHz
    //100b~111b = Reserved
    switch(SettingData->PEGDMIRatio){
        case 100: Ratio = 0x0; break;
        case 125: Ratio = 0x1; break;
        case 167: Ratio = 0x2; break;
        case 250: Ratio = 0x3; break;
    }
    if((PciRegData & 0x3) == (ReadMsr(0x61E)& 0x3) || (PciRegData & 0x3) != Ratio){
        PEI_TRACE((-1, PeiServices, "Change PEGDMIRatio suspend!!\n"));
        return EFI_UNSUPPORTED;
    }

    //read CMOS and check if need to set bootmode = BOOT_ON_S3_RESUME
    IoWrite8(0x70,0x50);
    PEI_TRACE((-1, PeiServices, "S3 resume request: %x\n",IoRead8(0x71)));
    if(IoRead8(0x71) == 0xA5){
        (*PeiServices)->SetBootMode(PeiServices, BOOT_ON_S3_RESUME);	//restore BootMode after set BCLK over ratio and generate warm reset.
        IoWrite8(0x71,0x5A);    //clear scratch
    }
	
    PCIEPLLRatio = ReadMsr(0x61E) & ~(BIT0 | BIT1 | BIT3);  //clear PCIE_Ratio & Long_Reset bit

    //PCIE_Ratio bit
    MsrData = 0;
    switch(Ratio){
        case 0x0: MsrData = 0; break;
        case 0x1: MsrData = 0 | BIT0; break;
        case 0x2: MsrData = 0 | BIT1; break;
        case 0x3: MsrData = 0 | BIT0 | BIT1; break;
    }
    //long reset bit
    MsrData |= BIT3;

    PCIEPLLRatio |= MsrData;
    WriteMsr(0x61E,PCIEPLLRatio);

    //Record current BootMode for restore after warm reset
    (*PeiServices)->GetBootMode(PeiServices, &BootMode);
    if (BootMode == BOOT_ON_S3_RESUME)
        IoWrite8(0x71,0xA5);
    PEI_TRACE((-1, PeiServices, "S3scratchpad value: %x\n",IoRead8(0x71)));

    //Is Memory in Self refresh?(B0:D31:F0, REG:0xa2)
    PciAddress = (0x1) << 31 | ((0x0) << 16) | ((0x1f) << 11) | ((0x0) << 8) | 0xa0;
    IoWrite32(0x0cf8,PciAddress);
    PciRegData = IoRead32(0x0cfc);
    PEI_TRACE((-1, PeiServices, "Read GEN_PMCON2 value: %x\n",PciRegData));
    if(!((PciRegData >> 16) & BIT5)){	//is memory in self-refresh
        //clear GEN_PMCON2 bit7(DRAM Initialization Bit)
        IoWrite32(0x0cfc,PciRegData & ~(BIT7 << 16));
    }

    //Need to send ICC message to enable Ramp when ME Firmware build no. is above 1221.
   	Status = ReadOnlyVariable2->GetVariable(
                             ReadOnlyVariable2,
                             L"MEFWVersion",
                             &gAmiCpuMEFwVerGuid,
                             NULL,
                             &MeVarSize,
                             &mMeInfoSetupData
                             );
  	if(!EFI_ERROR(Status)){
        PEI_TRACE((-1, PeiServices, "ME FW Build No %d\n",mMeInfoSetupData.MeBuildNo));
        if(mMeInfoSetupData.MeBuildNo >= 1221){
            //Write a value of 0x60000001 to PCI 0:22:0 offset 0x4C.
            PciAddress = (0x1) << 31 | ((0x0) << 16) | ((0x16) << 11) | ((0x0) << 8) | 0x4c;
            IoWrite32(0x0cf8,PciAddress);
            //Bits 31:28 - Message Type:
            //      0x06 - ICC BIOS Message
            //Bit      0 - BCLK Ramp Enable
            //      0x01 - BCLK Ramp Enable
            IoWrite32(0x0cfc,0x60000001);   

            //Wait for FW ACK by reading FWStatus PCI 0:22:0 offset 0x40 for ICC FW ACK
            //type and success status.
            PciAddress = (0x1) << 31 | ((0x0) << 16) | ((0x16) << 11) | ((0x0) << 8) | 0x40;
            IoWrite32(0x0cf8,PciAddress);
            //Bits 31:28 - Message Type:
            //      0x06 - ICC BIOS Message
            //Bits 27:25 - ICC BIOS Ack Data
            //         0 - ICC Success
            //         1 - ICC BIOS Request Failed
            while((Shr64(IoRead32(0x0cfc),25) & 0x7) != 0){}    //wait for BCLK Ramp Enable success
        }
    }
    else
        PEI_TRACE((-1, PeiServices, "Get Me Fw Version fail!!\n"));

    //warm reset
    PEI_TRACE((-1, PeiServices, "Warmreset!!\n"));
    //Let WDT know this is a normal reset.
    Status = (*PeiServices)->LocatePpi(
     				PeiServices,
       				&gWdtPpiGuid,
       				0,
       				NULL,
       				&WdtPpi
       				);
    WdtPpi->AllowKnowReset(PeiServices);
    IoWrite8 (0xCF9,0x06);
    EFI_DEADLOOP();

    PEI_TRACE((-1, PeiServices, "Change PEGDMIRatio end!!\n"));

	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   EnablePLLOverVoltage
//
// Description: Enable PLL over voltage for CPU
//
// Input:
//      EFI_PEI_SERVICES    **PeiServices
//      UINT8               NumOfCpuCore
//      UINT16              *pCoreRatioData
//
// Output:
//      EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS EnablePLLOverVoltage(
	IN EFI_PEI_SERVICES **PeiServices,
	IN UINT8	NumOfCpuCore,
	IN UINT16	*pCoreRatioData
	)
{
	EFI_STATUS	Status = EFI_SUCCESS;
	EFI_GUID	gAmiPllOvFlagHobGuid = AMI_PLL_OVER_VOTAGE_FLAG_HOB_GUID;
	EFI_GUID	gPeiReadOnlyVariable2PpiGuid = EFI_PEI_READ_ONLY_VARIABLE2_PPI_GUID;
	EFI_GUID	gAmiPllOvFlagDataGuid = gAmiPllOvFlagHobGuid;
	EFI_PEI_READ_ONLY_VARIABLE2_PPI	*ReadOnlyVariable2;
	UINTN		VarSize = sizeof(PLL_OV_FLAG_DATA);
	PLL_OV_FLAG_DATA_HOB	*PllOvFlagHob;
	UINT16		i;
	UINT8		*OriRatioLimit;

    PEI_TRACE((-1, PeiServices, "EnablePLLOverVoltage Start\n")); 
	Status = (*PeiServices)->CreateHob(PeiServices,
                                       EFI_HOB_TYPE_GUID_EXTENSION,
                                       sizeof(PLL_OV_FLAG_DATA_HOB),
                                       &PllOvFlagHob);
	if (EFI_ERROR(Status))return Status;

	PllOvFlagHob->EfiHobGuidType.Name = gAmiPllOvFlagHobGuid;
	OriRatioLimit = (UINT8*)&PllOvFlagHob->PllOvData.OriTurboRatio;	

	Status = (*PeiServices)->LocatePpi(
					PeiServices,
					&gPeiReadOnlyVariable2PpiGuid,
					0,
					NULL,
					&ReadOnlyVariable2		
					);
	if(EFI_ERROR(Status))return Status;

	Status = ReadOnlyVariable2->GetVariable(
                         ReadOnlyVariable2,
                         L"PLLOvFlag",
                         &gAmiPllOvFlagDataGuid,
                         NULL,
                         &VarSize,
                         &PllOvFlagHob->PllOvData
                         );

	if(!(EFI_ERROR(Status)) && (PllOvFlagHob->PllOvData.PLLOvFlag== 0x2)) return EFI_ALREADY_STARTED;

	for(i = 0; i < sizeof(UINT64); i++){
		if( i < NumOfCpuCore)
			OriRatioLimit[i] = (UINT8)pCoreRatioData[i];
		else
			OriRatioLimit[i] = 0x00;

		if( i < 3)
			pCoreRatioData[i] = 0x06;
		else
			pCoreRatioData[i] = 0x00;
	}

	PllOvFlagHob->PllOvData.PLLOvFlag = 0x1;
    WriteMsr(MSR_TURBO_RATIO_LIMIT,0x60606);
	
    PEI_TRACE((-1, PeiServices, "EnablePLLOverVoltage End\n")); 

	return EFI_SUCCESS;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CollectOcConfig
//
// Description: Collect Overclocking Config data from MSR 0x150.
//
// Input:
//      EFI_PEI_SERVICES            **PeiServices
//      OVERCLOCKING_CONFIG_HOB     *OverclockConfig
//
// Output:
//      VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID CollectOcConfig(
    EFI_PEI_SERVICES        **PeiServices,
    OVERCLOCKING_CONFIG_DATA *OverclockConfig
){
    EFI_STATUS Status;
    UINT64  MsrData;
    UINT8   i;
    PERF_TUNE_PPI		            *PerfTunePpi;
    PERF_TUNE_WDT_PPI	            *WdtPpi;

    PEI_TRACE((-1, PeiServices, "Collect Overclocking config data(MSR 0x150) Start\n")); 

    OverclockConfig->OcSupport = 0;
	OverclockConfig->IsPowerCycle = IsPowerCycle();
	OverclockConfig->IsCpuRunDefault = TRUE;
	
    //collect CPU overclocking config data
    for(i=0;i<DOMAIN_MAX_NUM;++i){
        //1. Overclocking Capability
        MsrData = 0;
        Status = GetOcCapability(i, &MsrData);
        if(!EFI_ERROR(Status)){
            OverclockConfig->OCCap[i].MaxOcRatioLimit = (UINT8)MsrData;
            OverclockConfig->OCCap[i].RatioOcSupported = (MsrData & BIT8)?1:0;
            OverclockConfig->OCCap[i].VoltageOverridesSupported = (MsrData & BIT9)?1:0;
            OverclockConfig->OCCap[i].VoltageOffsetSupported = (MsrData & BIT10)?1:0;
            if (!OverclockConfig->OcSupport) 
                OverclockConfig->OcSupport = OverclockConfig->OCCap[i].RatioOcSupported ||
                                             OverclockConfig->OCCap[i].VoltageOverridesSupported||
                                             OverclockConfig->OCCap[i].VoltageOffsetSupported ;
        }
        else{
            PEI_TRACE((-1, PeiServices, "Domain %x GetOcCapability fail [0x%x]\n",i,Shr64(MsrData,32) & 0xFF)); 
        }
        
        //2. Overclocking Voltage/Frequency 
        MsrData = 0;
        Status = GetVoltFreq(i, &MsrData);
        if(!EFI_ERROR(Status)){
            OverclockConfig->VFDef[i].MaxOcRatio = (UINT8)MsrData;
            OverclockConfig->VFDef[i].VoltageTargetMode = (UINT8)(Shr64(MsrData,20) & 0x1);
            OverclockConfig->VFDef[i].VoltageTarget = (UINT16)(Shr64(MsrData,8) & 0xFFF);
            OverclockConfig->VFDef[i].VoltageOffset = (INT16)(Shr64(MsrData,21) & 0x7FF);
        }
        else{
            PEI_TRACE((-1, PeiServices, "Domain %x GetVoltFreq fail [0x%x]\n",i,Shr64(MsrData,32) & 0xFF)); 
        }
    }
    //3. SVID Config 
    MsrData = 0;
    Status = GetSVIDConfig(&MsrData);
    if(!EFI_ERROR(Status)){
        OverclockConfig->SvidDisable = (MsrData & BIT31)?1:0;
        OverclockConfig->SvidVoltageOverride = (UINT16)(MsrData & 0xFFF);
    }
    else{
        PEI_TRACE((-1, PeiServices, "GetSVIDConfig fail [0x%x]\n",Shr64(MsrData,32) & 0xFF)); 
    }

    //4. Misc Global Config
    MsrData = 0;
    Status = GetFIVRConfig(&MsrData);
    if(!EFI_ERROR(Status)){
        OverclockConfig->FivrFaultsDisable = (MsrData & BIT0)?1:0;
        OverclockConfig->FivrEfficiencyDisable = (MsrData & BIT1)?1:0;
    }
    else{
        PEI_TRACE((-1, PeiServices, "GetMiscConfig fail [0x%x]\n",Shr64(MsrData,32) & 0xFF)); 
    }

    PEI_TRACE((-1, PeiServices, "Collect Overclocking config data(MSR 0x150) end\n"));

    Status = (*PeiServices)->LocatePpi(
					PeiServices,
					&gPerfTunePpiGuid,
					0,
					NULL,
					&PerfTunePpi
					);
	if(EFI_ERROR(Status)) return;
	
	Status = (*PeiServices)->LocatePpi(
				PeiServices,
				&gWdtPpiGuid,
				0,
				NULL,
				&WdtPpi
				);
	if(EFI_ERROR(Status)) return;
		
    if ( !(PerfTunePpi->IsChangeCpu(PeiServices) && PerfTunePpi->IsRunDefault(PeiServices)) && !(WdtPpi->QueryTimeOut(PeiServices))){
        OverclockConfig->IsCpuRunDefault = FALSE;
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   InitOcMailbox
//
// Description: Initialize Overclocking Config data.
//
// Input:
//      EFI_PEI_SERVICES            **PeiServices
//      OVERCLOCKING_CONFIG_PPI     *OverclockingConfig
//
// Output:
//      VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS InitOcMailbox(
    IN EFI_PEI_SERVICES         **PeiServices,
    IN OVERCLOCKING_CONFIG_PPI  *OverclockingConfig
){
	EFI_STATUS	Status = EFI_SUCCESS;
    VOID        *FirstHob;
	OVERCLOCKING_CONFIG_HOB     *OverclockConfigHob;
	OVERCLOCKING_CONFIG_DATA    *OverclockData;

    PEI_TRACE((-1, PeiServices, "InitOcMailbox start!!\n"));

    Status = (*PeiServices)->GetHobList(PeiServices, &FirstHob);
    ASSERT_PEI_ERROR(PeiServices, Status);
    OverclockConfigHob = (OVERCLOCKING_CONFIG_HOB*) FirstHob;
    while (!EFI_ERROR(Status = FindNextHobByType(EFI_HOB_TYPE_GUID_EXTENSION, &OverclockConfigHob))) {
        if (guidcmp(&((EFI_HOB_GUID_TYPE*)OverclockConfigHob)->Name, &gAmiOcConfigHobGuid) == 0) {
            break;
        }
    }
    if(EFI_ERROR(Status)){
        PEI_TRACE((-1, PeiServices, "Get OC config HOB fail!!\n"));
        return Status;
    }
    OverclockData = &OverclockConfigHob->OverclockData;

    //
    // Initialize Overclocking Data
    //
    if(OverclockData->OCCap[IA].RatioOcSupported){
        OverclockingConfig->CoreMaxOcTurboRatio = ReadMsr(0x1AD) & 0xFF;
    }

    if(OverclockData->OCCap[RING].RatioOcSupported){
        OverclockingConfig->ClrMaxOcTurboRatio = ReadMsr(0x1AD) & 0xFF;											// read core one max ratio limit
    }

	OverclockingConfig->SvidEnable = 1;             // 1: Enable
   	OverclockingConfig->FivrFaultsEnable = 1;	    // 1: Enable
   	OverclockingConfig->FivrEfficiencyEnable = 1;	// 1: Enable

    OverclockingConfig->OcSupport = 1;      // 0: Disable, 1: Enable

    PEI_TRACE((-1, PeiServices, "InitOcMailbox End!!\n"));
    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   OverlockingConfigUpdate
//
// Description: Update Overclocking Config data.
//
// Input:
//      EFI_PEI_SERVICES            **PeiServices
//      BIOS_SETTING_DATA           *SettingData
//      OVERCLOCKING_CONFIG_PPI     *OverclockingConfig
//
// Output:
//      EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS OverlockingConfigUpdate(
    IN EFI_PEI_SERVICES         **PeiServices,
    IN BIOS_SETTING_DATA        *SettingData,
    IN OVERCLOCKING_CONFIG_PPI  *OverclockingConfig
){
	EFI_STATUS	Status = EFI_SUCCESS;
    VOID        *FirstHob;
	OVERCLOCKING_CONFIG_HOB     *OverclockConfigHob;
	OVERCLOCKING_CONFIG_DATA    *OverclockData;

    PEI_TRACE((-1, PeiServices, "OverlockingConfigUpdate start!!\n"));

    Status = (*PeiServices)->GetHobList(PeiServices, &FirstHob);
    ASSERT_PEI_ERROR(PeiServices, Status);
    OverclockConfigHob = (OVERCLOCKING_CONFIG_HOB*) FirstHob;
    while (!EFI_ERROR(Status = FindNextHobByType(EFI_HOB_TYPE_GUID_EXTENSION, &OverclockConfigHob))) {
        if (guidcmp(&((EFI_HOB_GUID_TYPE*)OverclockConfigHob)->Name, &gAmiOcConfigHobGuid) == 0) {
            break;
        }
    }
    if(EFI_ERROR(Status)){
        PEI_TRACE((-1, PeiServices, "Get OC config HOB fail!!\n"));
        return Status;
    }
    OverclockData = &OverclockConfigHob->OverclockData;


    //Overwrite OverclockingConfig data in Intel reference code
    if(OverclockData->OcSupport){
    //IA core
        // Core Max overclocking turbo ratio
        if(OverclockData->OCCap[IA].RatioOcSupported){
            OverclockingConfig->CoreMaxOcTurboRatio = (SettingData->CoreRatioLimit1)?SettingData->CoreRatioLimit1:ReadMsr(0x1AD) & 0xFF;
            if (SettingData->CoreRatioLimit1 < SettingData->ProcessorMul ) 
                OverclockingConfig->CoreMaxOcTurboRatio = SettingData->ProcessorMul;
        }

        if(OverclockData->OCCap[IA].VoltageOverridesSupported){
            // Voltage Mode, 0: Adaptive, 1: Override(Static)
            OverclockingConfig->CoreVoltageMode = (UINT8)SettingData->IACoreVoltageMode;

            if(SettingData->IACoreVoltageMode == 0x1){
                // Override(Static) mode
                OverclockingConfig->CoreVoltageOverride = SettingData->CPUVoltage;				
                if(SettingData->CPUVoltage == 0xFFFF)
                    OverclockingConfig->CoreVoltageOverride = 0;       
                OverclockingConfig->CoreExtraTurboVoltage = 0;
            }
            else{
                // Adaptive mode
                OverclockingConfig->CoreExtraTurboVoltage = SettingData->CPUVoltage;
                if(SettingData->CPUVoltage == 0xFFFF)
                    OverclockingConfig->CoreExtraTurboVoltage = 0;  
                OverclockingConfig->CoreVoltageOverride = 0;
            }
        }

        if(OverclockData->OCCap[IA].VoltageOffsetSupported){
            if (SettingData->DynamicCPUVoltage >=0 && \
                SettingData->DynamicCPUVoltage <= 999){
                    OverclockingConfig->CoreVoltageOffset = ~(1000 - SettingData->DynamicCPUVoltage) + 1;
            }else if (SettingData->DynamicCPUVoltage >=1000 && \
                        SettingData->DynamicCPUVoltage <= 1998){            
                    OverclockingConfig->CoreVoltageOffset = SettingData->DynamicCPUVoltage - 1000;
            }

        }

    //RING
        // Ring Max overclocking turbo ratio
        if(OverclockData->OCCap[RING].RatioOcSupported){
            if(SettingData->RingRatio){
                OverclockingConfig->ClrMaxOcTurboRatio = SettingData->RingRatio;
            }
            else{            	
                // first boot                 
                OverclockingConfig->ClrMaxOcTurboRatio = ReadMsr(0x1AD) & 0xFF;											// read core one max ratio limit
            }
        }

        if(OverclockData->OCCap[RING].VoltageOverridesSupported){
            // Voltage Mode, 0: Adaptive, 1: Override(Static)
            OverclockingConfig->ClrVoltageMode = (UINT8)SettingData->RingVoltageMode;

            if(SettingData->RingVoltageMode == 0x1){     
                // Override(Static) mode
                OverclockingConfig->ClrVoltageOverride = SettingData->RingVoltageOverride;
                if(SettingData->RingVoltageOverride == 0xFFFF)
                    OverclockingConfig->ClrVoltageOverride = 0;
                OverclockingConfig->ClrExtraTurboVoltage = 0;
            }
            else{
                // Adaptive mode
                OverclockingConfig->ClrExtraTurboVoltage = SettingData->RingVoltageOverride;
                if(SettingData->RingVoltageOverride == 0xFFFF)
                    OverclockingConfig->ClrExtraTurboVoltage = 0;
                OverclockingConfig->ClrVoltageOverride = 0;
            }
        }

        if(OverclockData->OCCap[RING].VoltageOffsetSupported){
            if (SettingData->RingVoltageOffset >=0 && \
                SettingData->RingVoltageOffset <= 999){
                    OverclockingConfig->ClrVoltageOffset = ~(1000 - SettingData->RingVoltageOffset) + 1;
            }else if (SettingData->RingVoltageOffset >=1000 && \
                        SettingData->RingVoltageOffset <= 1998){            
                    OverclockingConfig->ClrVoltageOffset = SettingData->RingVoltageOffset - 1000;
            }
        }

    //SVID and FIVR
        if(SettingData->DynamicSVIDControl != 0xFFFF)
            OverclockingConfig->SvidEnable = (UINT8)(SettingData->DynamicSVIDControl);                      // 0: Disable,  1: Enable
		if(OverclockData->IsPowerCycle)
			OverclockingConfig->SvidEnable = 1;  															// When cold boot, reset to the default value '1'.
        if(SettingData->DynamicSVIDControl != 0xFFFF && SettingData->SVIDVoltageOverride != 0xFFFF)
            OverclockingConfig->SvidVoltageOverride = (SettingData->DynamicSVIDControl)? SettingData->SVIDVoltageOverride : 0;      // External VR voltage override			

        if(SettingData->FIVRFaults != 0xFFFF)
            OverclockingConfig->FivrFaultsEnable = (UINT8)(SettingData->FIVRFaults);                        // 0: Disable, 1: Enable
		if(OverclockData->IsPowerCycle)
			OverclockingConfig->FivrFaultsEnable = 1;														// When cold boot, reset to the default value '1'.
        if(SettingData->FIVREfficiencyManagenment != 0xFFFF)
            OverclockingConfig->FivrEfficiencyEnable = (UINT8)(SettingData->FIVREfficiencyManagenment);     // 0: Disable, 1: Enable

        //Enable orDisable Reference code execute Cpu Overclocking Initialize(CpuOcInit).
        OverclockingConfig->OcSupport = 1;      // 0: Disable, 1: Enable
        OverclockingConfig->BitReserved = 0;
    }
    PEI_TRACE((-1, PeiServices, "OverlockingConfigUpdate end!!\n"));
	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CpuPeiPolicyOverWrite
//
// Description: This function over writes the CPU PEI RC policy
//
// Input:
//      EFI_PEI_SERVICES **PeiServices
//
// Output:
//      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
CpuPeiPolicyOverWrite (
  IN EFI_PEI_SERVICES **PeiServices
  )
{
   
    //UINT8         MaxNonTurboRatio;
    //UINT8         NumBinsSupport;  
    UINT8       CpuCores = NumCpuCores();
    UINT16      i;
    UINT16      Xtu_CoreRatioArray[6];
    UINT32	    CpuSignature = GetCpuSignature();
	UINT32      CpuSigNoVer = CpuSignature & 0xfffffff0;
	//UINT64        MsrData;
    
    EFI_STATUS                      Status;
    PEI_CPU_PLATFORM_POLICY_PPI     *PeiCpuPolicyPpi;
    //PPI_CPU_POWER_FEATURE_CONFIG    *PeiCpuPowerFeatureConfig;  
	POWER_MGMT_CONFIG_PPI    		*PeiCpuPowerFeatureConfig;
    PERF_TUNE_PPI		            *PerfTunePpi;
    //PERF_TUNE_WDT_PPI	            *WdtPpi;
    BIOS_SETTING_DATA	            SettingData;
	OVERCLOCKING_CONFIG_HOB         *OverclockConfigHob;
	OVERCLOCKING_CONFIG_DATA        *OverclockData;
    CPU_RATIO_LIMIT_HOB             *CpuRatioLimitHob;
   	CPU_RATIO_LIMIT_DATA            *CpuRatioLimitData;
	EFI_GUID	                    PeiReadOnlyVariable2PpiGuid = EFI_PEI_READ_ONLY_VARIABLE2_PPI_GUID;
    EFI_GUID	                    SetupGuid = SETUP_GUID;
	EFI_PEI_READ_ONLY_VARIABLE2_PPI	*ReadOnlyVariable2;
	SETUP_DATA	                    SetupData;
	UINTN		                    VarSize = sizeof(SETUP_DATA);
    
    PEI_TRACE((-1, PeiServices, "Start CPU PEI RC policy overwrite\n"));

	Status = (*PeiServices)->LocatePpi(
					PeiServices,
					&PeiReadOnlyVariable2PpiGuid,
					0,
					NULL,
					&ReadOnlyVariable2		
					);
 	if(EFI_ERROR(Status)) return;
	Status = ReadOnlyVariable2->GetVariable(
                         ReadOnlyVariable2,
                         L"Setup",
                         &SetupGuid,
                         NULL,
                         &VarSize,
                         &SetupData
                         );
	if(EFI_ERROR(Status)) return;

    Status = (*PeiServices)->LocatePpi(
                    PeiServices, 
                    &gPeiCpuPlatformPolicyGuid, 
                    0, 
                    NULL, 
                    &PeiCpuPolicyPpi
                    );
    if(EFI_ERROR(Status)) return;                    

    Status = (*PeiServices)->LocatePpi(
					PeiServices,
					&gPerfTunePpiGuid,
					0,
					NULL,
					&PerfTunePpi
					);
	if(EFI_ERROR(Status)) return;
	PEI_TRACE((-1, PeiServices, "Perfmorance tunning PPI located\n"));

    // collect OcMailbox data
	Status = (*PeiServices)->CreateHob(PeiServices,
                                       EFI_HOB_TYPE_GUID_EXTENSION,
                                       sizeof(OVERCLOCKING_CONFIG_HOB),
                                       &OverclockConfigHob);
	if (EFI_ERROR(Status)){
        PEI_TRACE((-1, PeiServices, "Create OverclockConfigHob fail\n"));
        return;
    }
    OverclockConfigHob->EfiHobGuidType.Name = gAmiOcConfigHobGuid;
    OverclockData = &OverclockConfigHob->OverclockData;
    CollectOcConfig(PeiServices,OverclockData);
    InitOcMailbox(PeiServices,PeiCpuPolicyPpi->OverclockingConfig);
    
    if(PerfTunePpi->IsChangeCpu(PeiServices)){
       	Status = (*PeiServices)->CreateHob(PeiServices,
                                           EFI_HOB_TYPE_GUID_EXTENSION,
                                           sizeof(CPU_RATIO_LIMIT_HOB),
                                           &CpuRatioLimitHob);
       	if (EFI_ERROR(Status)){
            PEI_TRACE((-1, PeiServices, "Create NonTurboRatioMax HOB fail\n"));
            return;
        }
        CpuRatioLimitHob->EfiHobGuidType.Name = gAmiCpuRatioLimitHobGuid;
        CpuRatioLimitData = &CpuRatioLimitHob->CpuRatioLimitData;
        CpuRatioLimitData->MaxNonTurboRatio = (UINT8)(Shr64(ReadMsr(0x0ce), 8) & 0xFF);
        CpuRatioLimitHob->IsChangeCpu = PerfTunePpi->IsChangeCpu(PeiServices);
    }
	/*
	Status = (*PeiServices)->LocatePpi(
				PeiServices,
				&gWdtPpiGuid,
				0,
				NULL,
				&WdtPpi
				);
	if(EFI_ERROR(Status)) return;
	PEI_TRACE((-1, PeiServices, "watch dogger timer PPI located\n"));
    */
    Status = PerfTunePpi->GetSettingData(
                PeiServices, 
                &SettingData
                );
                
	if(EFI_ERROR(Status)) return;
	PEI_TRACE((-1, PeiServices, "Got Perfmorance tunning setting data\n"));
    
    if(!((PerfTunePpi->IsChangeCpu(PeiServices) && PerfTunePpi->IsRunDefault(PeiServices)))){
    //if(!(WdtPpi->QueryTimeOut(PeiServices))){
        
        PEI_TRACE((-1, PeiServices, "ReConfig XE policy from XTU\n"));
        //PeiCpuPowerFeatureConfig = PeiCpuPolicyPpi->PpiCpuPowerFeatureConfig;
		PeiCpuPowerFeatureConfig = PeiCpuPolicyPpi->PowerMgmtConfig;        
        //PeiCpuPowerFeatureConfig->PrimaryPlaneCurrentLimit = (SettingData.IACoreCurrentMax & 0x1fff);
        PeiCpuPowerFeatureConfig->VrCurrentLimit = (SettingData.PackageCurrentLimit & 0x1fff);
        //PeiCpuPowerFeatureConfig->SecondaryPlaneCurrentLimit = (SettingData.IGFXCoreCurrentMax & 0x1fff);
        PeiCpuPowerFeatureConfig->VrCurrentLimitLock = (!OverclockData->IsCpuRunDefault)? SetupData.PackageCurrentLock : CPU_FEATURE_DISABLE ;
		// CPU boot with Maximum Non-Turbo speed. 
		PeiCpuPowerFeatureConfig->BootInLfm = CPU_FEATURE_DISABLE;

        if (isXECoreRatioLimitSupported())
        {
            PEI_TRACE((-1, PeiServices, "XE part CPU found\n"));           
            
            PeiCpuPowerFeatureConfig->Xe = CPU_FEATURE_ENABLE;  
            Xtu_CoreRatioArray[0] = SettingData.CoreRatioLimit1;
            Xtu_CoreRatioArray[1] = SettingData.CoreRatioLimit2;
            Xtu_CoreRatioArray[2] = SettingData.CoreRatioLimit3;
            Xtu_CoreRatioArray[3] = SettingData.CoreRatioLimit4;
            Xtu_CoreRatioArray[4] = SettingData.CoreRatioLimit5;
            Xtu_CoreRatioArray[5] = SettingData.CoreRatioLimit6;            
                                                                    
            for(i = 0; i < CpuCores; ++i)
                if(SettingData.ProcessorMul > Xtu_CoreRatioArray[i])
                    Xtu_CoreRatioArray[i] = SettingData.ProcessorMul; 
 
            /*Force Runtime Turbo not suuport now
            if (CpuSigNoVer == SANDY_BRIDGE && SettingData.RuntimeTurboEanble)
            {
                PEI_TRACE((-1, PeiServices, "SnadyBridge Runtime Turbo ratio change\n"));
                MsrData = ReadMsr(MSR_FLEX_RATIO);
		        NumBinsSupport = (UINT8)((UINT32)MsrData >> 17) & 0x7;
		        
		        //Read Max_Non turbo ratio.
                MsrData = ReadMsr(MSR_PLATFORM_INFO);
                MaxNonTurboRatio = ((UINT32) MsrData >> MAX_NON_TURBO_RATIO_OFFSET) & MAX_NON_TURBO_RATIO_MASK;
		        
		        MsrData = ReadMsr(MSR_TURBO_RATIO_LIMIT);
		        for(i = 0; i < CpuCores; i++)
		        {
                    if((NumBinsSupport > 0)&&(NumBinsSupport < 7))
                    {
                        PeiCpuPowerFeatureConfig->RatioLimit[i] = MsrData & 0xff + NumBinsSupport;
                    } else {
                        PeiCpuPowerFeatureConfig->RatioLimit[i] = 0x39;
                    }
                    MsrData = Shr64(MsrData, 8);    
                }
                
            } else {*/
                PEI_TRACE((-1, PeiServices, "CPU core ratio limit change\n"));
                for(i = 0; i < CpuCores; i++){                
                    PeiCpuPowerFeatureConfig->RatioLimit[i] = (UINT8)(Xtu_CoreRatioArray[i]);
                    PEI_TRACE((-1, PeiServices, "XTU for %x core ratio limit = %x \n", (i + 1, Xtu_CoreRatioArray[i])));
                }        
            //}
            
            //PeiCpuPowerFeatureConfig->OverClockExtraVoltage = SettingData.MaxTurboModeCPUVoltage;

            // Change Cpu Max Non-Tubro Ratio
            if(SettingData.ProcessorMul != 0xFFFF){
                Status = OverrideNonTurboRatio(PeiServices,SettingData.ProcessorMul,PeiCpuPolicyPpi->CpuConfig);
            }
        }

#if HASWELL_PERFTUNE_CPU_FILTER_PLL_SUPPORT == 1    
	    if(SettingData.FilterPLLFrequency != 0xFFFF){
            UINT32 RcbaAdd;
			UINT8 PmCFG;

  		    RcbaAdd = (READ_PCI32 (00, 0x1F, 0x0, 0xF0)) & 0xFFFFF000;
  			PmCFG = READ_MEM8 (RcbaAdd + 0x3318);
            if ( SettingData.FilterPLLFrequency != ( (PmCFG & BIT5) >> 5)){
  				PLLFilterFunction(PeiServices,&SettingData);
			}
		}
#endif

        // Change PEG/DMI Ratio
        if(SettingData.PEGDMIRatio != 0xFFFF){
            if(isBCLKRatioSuuported()){
                PEGDMIRatio(PeiServices,&SettingData);
            }
        }
        // Enable PLL Over Voltage feature
        if(SettingData.CpuPllVoltageUnlockEnable == 0x1){
            Status = EnablePLLOverVoltage(PeiServices,CpuCores,(UINT16*)Xtu_CoreRatioArray);
        }

        // Updata OC config data in CpuOcInit.c                             
        Status = OverlockingConfigUpdate(PeiServices,&SettingData,PeiCpuPolicyPpi->OverclockingConfig);
    }
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CpuPeiPolicyNotify
//
// Description: CPU PEI pollicy PPI notify function
//
// Input:
//      EFI_PEI_SERVICES **PeiServices
//      EFI_PEI_NOTIFY_DESCRIPTOR *NotifyDescriptor
//      VOID *NullPpi
//
// Output:
//      EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS CpuPeiPolicyNotify(
    IN EFI_PEI_SERVICES **PeiServices,
    IN EFI_PEI_NOTIFY_DESCRIPTOR *NotifyDescriptor,
    IN VOID *NullPpi
)
{    
    CpuPeiPolicyOverWrite(PeiServices);
    return EFI_SUCCESS;    
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	CpuPeiXtuInitBeforeMem
//
// Description:	CPU XTU init code in PEI phase
//
// Input:
//  IN EFI_FFS_FILE_HEADER		*FfsHeader,
//  IN EFI_PEI_SERVICES 		**PeiServices
//
// Output:	
//  EFI_STATUS 
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS CpuPeiXtuInitBeforeMem(
	IN EFI_PEI_SERVICES 		**PeiServices
)
{
    
    EFI_STATUS                      Status;
    PEI_CPU_PLATFORM_POLICY_PPI     *PeiCpuPolicyPpi;
    
    Status = (*PeiServices)->LocatePpi (PeiServices, &gPeiCpuPlatformPolicyGuid, 0, NULL, &PeiCpuPolicyPpi);
    if (Status == EFI_SUCCESS) {
        CpuPeiPolicyOverWrite(PeiServices);
    } else {
        Status = (*PeiServices)->NotifyPpi(PeiServices, mNotifyList);
    }
    
    return Status;

}    
#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ReinstallSecPpis
//
// Description:
//  Reinstall PPIs from stack because stack will be lost when cache-as-ram is turned off.
//
// Input:
//  IN EFI_PEI_SERVICES 		**PeiServices
//
// Output:	
//  EFI_STATUS 
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

//Sec Core Descriptors on stack will be lost when cache-as-ram is turned off.
VOID ReinstallSecPpis(IN EFI_PEI_SERVICES **PeiServices)
{
    EFI_STATUS Status;
	EFI_GUID gAmiEarlyBistGuid = AMI_EARLY_BIST_PPI_GUID;

    AMI_EARLY_BIST_PPI *OldAmiBistPpi;
    AMI_EARLY_BIST_PPI *NewAmiBistPpi;

    EFI_PEI_PPI_DESCRIPTOR *OldPpiDesc;
    EFI_PEI_PPI_DESCRIPTOR *NewPpiDesc;

   	Status = (*PeiServices)->LocatePpi(
        PeiServices,
        &gAmiEarlyBistGuid,
        0,&OldPpiDesc,
		&OldAmiBistPpi
	);
	if (!EFI_ERROR(Status)) {

        //Create new PPI in allocated memory because the location in stack from Sec Core
        //will not be available after memory.
        Status = (*PeiServices)->AllocatePool(PeiServices,
            sizeof(AMI_EARLY_BIST_PPI) + (OldAmiBistPpi->NumBists - 1) * sizeof(CPU_BIST),
            &NewAmiBistPpi
        );
        ASSERT_PEI_ERROR(PeiServices, Status);
        MemCpy(
            NewAmiBistPpi,
            OldAmiBistPpi,
            sizeof(AMI_EARLY_BIST_PPI) + (OldAmiBistPpi->NumBists - 1) * sizeof(CPU_BIST)
        );
        
        //Create new Descriptor
        Status = (*PeiServices)->AllocatePool(PeiServices,
            sizeof(EFI_PEI_PPI_DESCRIPTOR),
            &NewPpiDesc
        );
        ASSERT_PEI_ERROR(PeiServices, Status);
        MemCpy(NewPpiDesc, OldPpiDesc, sizeof(EFI_PEI_PPI_DESCRIPTOR));
        NewPpiDesc->Ppi = NewAmiBistPpi;

        (*PeiServices)->ReInstallPpi(
            PeiServices,
            (EFI_PEI_PPI_DESCRIPTOR*)OldPpiDesc,
            (EFI_PEI_PPI_DESCRIPTOR*)NewPpiDesc
        );
    }
} 
    
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	CpuPeiBeforeMemEntry
//
// Description:	CPU PEI functions before memory ready
//
// Input:
//  IN EFI_FFS_FILE_HEADER		*FfsHeader,
//  IN EFI_PEI_SERVICES 		**PeiServices
//
// Output:	
//  EFI_STATUS 
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS CpuPeiBeforeMemEntry(
	IN EFI_FFS_FILE_HEADER		*FfsHeader,
	IN EFI_PEI_SERVICES 		**PeiServices
)
{
#if PERF_TUNE_SUPPORT == 1    
    EFI_STATUS                      Status;    
    Status = CpuPeiXtuInitBeforeMem(PeiServices);
#endif

	ReinstallSecPpis(PeiServices);

	return EFI_SUCCESS;
}

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

