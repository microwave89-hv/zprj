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
// $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Board/GetSetupData.c 28    3/13/14 11:06a Barretlin $
//
// $Revision: 28 $
//
// $Date: 3/13/14 11:06a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Board/GetSetupData.c $
// 
// 28    3/13/14 11:06a Barretlin
// [TAG]  		EIP153695
// [Category]  	Improvement
// [Description]  	USB Per port control is not reasonable when
// OEM_USBPREPORT_DISABLE_SUPPORT token is Enabled and USB devices are
// behind hubs
// [Files]  		Sb.sdl Sb.sd Sb.uni GetSetupData.c SbDxe.c PchUsbCommon.c
// PchRegsUsb.h
// 
// 27    8/01/13 4:32a Scottyang
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Add PCIE LTR setup items.
// [Files]  		SB.sd, SB.uni, SBDxe.c, GetSetupData.c, SbSetupData.h
// 
// 26    7/09/13 5:16a Scottyang
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Create "PCH Cross Throttling" setup item.(Only ULT
// support)
// [Files]  		SBDxe.c, SB.sd, SB.uni, GetSetupData.c, SB.sd 
// 
// 25    5/13/13 8:58a Scottyang
// [TAG]  		EIP123496
// [Category]  	Improvement
// [Description]  	Update PCH RC 1.5.0.
// [Files]  		..\ReferenceCode\Chipset\LynxPoint\*.* , SBDxe.C, SBPEI.c,
// SB.sd, SB.uni, SbSetupData.h, GetSetupData.c
// 
// 24    3/15/13 3:40a Scottyang
// [TAG]  		EIP118121
// [Category]  	Improvement
// [Description]  	Update PCH RC 1.3.0.
// [Files]  		..\ReferenceCode\Chipset\LynxPoint\*.*, SBDxe.c, SBPEI.c,
// SB.sd, SB.uni, GetSetupData.c, SbSetupData.h
// 
// 23    3/04/13 10:08p Scottyang
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Add Solid State Drive item to port 6.
// [Files]  		GetSetupData.c, SbSetupData.h, SB.sd
// 
// 22    2/19/13 9:59p Scottyang
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Add setup buffer for NFC.
// [Files]  		GetSetupData.c
// 
// 21    2/09/13 12:13a Scottyang
// [TAG]  		EIP114922
// [Category]  	Improvement
// [Description]  	Update PCH RC 1.1.0.
// [Files]  		..\ReferenceCode\Chipset\LynxPoint\*.*, SBDxe.c, SBPEI.c,
// SB.sd, SB.uni, GetSetupData.c, SbSetupDara.h
// 
// 20    1/31/13 10:56a Scottyang
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Add Serial IO GNVS setup option. 
// [Files]  		SBDxe.c, SB.sd, SB.uni, SbSetupData.h, GetSetupData.c
// 
// 19    1/10/13 4:49a Scottyang
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Create DTIO value and DM value option
// [Files]  		SB.sd, SB.uni, SbSetupData.h, GetSetupData.c, SBDxe.c
// 
// 18    1/03/13 4:56a Scottyang
// [TAG]  		None
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Build error when set IDE mode as default.
// [RootCause]  	The ULT did not support IDE mode that made the value
// redefine.
// [Solution]  	Separate Sata inter face for 2 Chip and ULT.
// [Files]  		SB.sd, GetSetupData.c, SbSetupData.h
// 
// 17    12/24/12 5:42a Scottyang
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Add option for XHCI Idel L1 workaroung.
// [Files]  		GetSetupData.c, SbSetupData.h, SB.sd, SB.uni, SBDxe.c,
// SBPEI.c
// 
// 16    12/22/12 2:05a Scottyang
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Add PCIE "L1 Substates"setup option.
// [Files]  		GetSetupData.c, SbSetupData.h, SB.sd, SB.uni, SBDxe.c
// 
// 15    12/18/12 6:03a Scottyang
// [TAG] EIP109697
// [Category] Improvement
// [Description] Update PCH RC 0.8.1
// [Files] ReferenceCode\Chipset\LynxPoint\*.*, SBDxe.c, SBPEI.c, SB.sd,
// SbSetupData.c, GetSetupDate.c
// 
// 14    12/17/12 6:41a Scottyang
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Add setup menu for LPSS and ECTG.
// [Files]  		GetSetupData.c
// SbSetupData.h
// SB.sd
// SB.uni
// SBDxe.c
// 
// 13    12/13/12 10:34a Scottyang
// [TAG]  		EIP106687
// [Category]  	Improvement
// [Description]  	Add option for delay to detect PCIE card.
// [Files]  		SBPEI.c, SB.sd, SB.uni, GetSetupData.c, SbSetupData.h,
// PciBus.c
// 
// 12    11/20/12 9:45a Scottyang
// [TAG]  		EIP107014
// [Category]  	Improvement
// [Description]  	Update RC 0.8.0
// [Files]  		ReferenceCode\Chipset\LynxPoint\*.*, SBDxe.c, SBPEI.c,
// SB.sd, SbSetupData.c, GetSetupDate.c
// 
// 11    11/08/12 8:33a Scottyang
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Add device item that connect LPSS.
// [Files]  		GetSetupData.c, SbSetupData.h, SBDxe.c, SB.sd, SB.uni
// 
// 10    11/07/12 6:09a Scottyang
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Remove HDMI item.
// [Files]  		SB.sd, SB.uni, GetSetupData.c, SbSetupData.h
// 
// 9     10/23/12 8:27a Scottyang
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Create Device Sleep at setup menu
// [Files]  		SB.sd, SB.uni, SBDxe.c, GetSetupData.c, SbSetupData.h
// 
// 8     10/16/12 2:15a Scottyang
// [TAG]  		EIP103924
// [Category]  	Improvement
// [Description]  	Update RC 0.7.1
// [Files]  		ReferenceCode\Chipset\LynxPoint\*.*, SBDxe.c, SB.sd,
// SbSetupData.c, GetSetupDate.c
// 
// 7     9/26/12 3:46a Victortu
// [TAG]           None
// [Category]      Improvement
// [Description]   Implement ULT platform LPSS and ADSP setup option.
// [Files]         GetSetupData.c, SB.sd, SB.uni, SbSetupData.h, SBDxe.c,
// SB.sdl
// 
// 6     9/12/12 5:08a Victortu
// [TAG]           None
// [Category]      Improvement
// [Description]   Modify for Thunderbolt support.
// [Files]         GetSetupData.c, SB.sdl, SB.sd, SB.uni, SbSetupData.h,
// PciHotPlug.c
// 
// 5     8/13/12 10:12a Victortu
// [TAG]           None
// [Category]      Improvement
// [Description]   Remove useless Dppm items.
// [Files]         GetSetupData.c, SB.sd, SbSetupData.h, SBDxe.c
// 
// [TAG]           None
// [Category]      Improvement
// [Description]   Implement USB Precondition option for policy
// "UsbPrecondition".
// [Files]         GetSetupData.c, SB.sd, SB.uni, SbSetupData.h, SBDxe.c,
// SBPEI.c
// 
// 4     7/27/12 6:04a Victortu
// Update setup items and policies.
// 
// 3     7/02/12 10:21a Victortu
// [TAG]		None
// [Category]	Improvement
// [Description]	Change default setup of USB 3.0 mode and Pre-Boot
// Support.
// [Files]		GetSetupData.c, SB.sd
// 
// 2     4/25/12 9:07a Victortu
// [TAG]         None
// [Category]    Improvement
// [Description] Relayout PCH USB Setup.
// [Files]       GetSetupData.c; SB.sd; SB.uni; SbSetupData.h; SBDxe.c
// 
// 1     2/08/12 8:22a Yurenlai
// Intel Lynx Point/SB eChipset initially releases.
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:        GetSetupData.c
//
// Description: Custom South Bridge setup data behavior implementation
//
//<AMI_FHDR_END>
//*************************************************************************

//---------------------------------------------------------------------------
// Include(s)
//---------------------------------------------------------------------------

#include <AmiCspLib.h>
#include <Setup.h>
#include <Ppi\ReadOnlyVariable2.h>

//---------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//---------------------------------------------------------------------------
// Constant Definition(s)

// Macro Definition(s)

// Type Definition(s)

typedef VOID (SB_OEM_SETUP_CALLBACK) (
    IN VOID                 *Services,
    IN OUT SB_SETUP_DATA    *SbSetupData,
    IN SETUP_DATA           *SetupData,
    IN BOOLEAN              Pei
);

// Function Prototype(s)
VOID SbSetupCallbacks (
    IN VOID                 *Services,
    IN OUT SB_SETUP_DATA    *SbSetupData,
    IN SETUP_DATA           *SetupData,
    IN BOOLEAN              Pei 
);

//---------------------------------------------------------------------------
// Variable and External Declaration(s)
//---------------------------------------------------------------------------

// GUID Definition(s)

static EFI_GUID gSetupGuid = SETUP_GUID;
static EFI_GUID gPeiReadOnlyVarPpiGuid = EFI_PEI_READ_ONLY_VARIABLE2_PPI_GUID;

// Protocol/Ppi Definition(s)

// External Declaration(s)

extern SB_OEM_SETUP_CALLBACK SB_OEM_SETUP_CALLBACK_LIST EndOfList;

// Variable Declaration(s)

SB_OEM_SETUP_CALLBACK* SbOemSetupCallbackList[] = \
                                            {SB_OEM_SETUP_CALLBACK_LIST NULL};
// Function Definition(s)

//---------------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SbOemSetupCallbacks
//
// Description: This function calls registered callbacks for OEM/custom setup.
//
// Input:       *Services    - Pointer to PeiServices or RuntimeServices
//                             structure  
//              *SbSetupData - Pointer to custom setup data to return
//              *SetupData   - Pointer to system setup data.
//              Pei          - Pei flag. If TRUE we are in PEI phase
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID SbOemSetupCallbacks (
    IN VOID              *Services,
    IN OUT SB_SETUP_DATA *SbSetupData,
    IN SETUP_DATA        *SetupData,
    IN BOOLEAN           Pei )
{
    UINTN   i;

    for (i = 0; SbOemSetupCallbackList[i] != NULL; i++) 
        SbOemSetupCallbackList[i]( Services, SbSetupData, SetupData, Pei);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetSbSetupData
//
// Description: This function returns custom setup data from system SetupData
//              variable 
//
// Input:       *Services         - Pointer to PeiServices or RuntimeServices
//                                  structure  
//              *SbSetupData      - Pointer to custom setup data to return
//              Pei               - Pei flag. If TRUE we are in PEI phase
//
// Output:      None
//
// Notes:       PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID GetSbSetupData (
  IN VOID                 *Services,
  IN OUT SB_SETUP_DATA    *SbSetupData,
  IN BOOLEAN              Pei )
{
  EFI_STATUS                      Status;
  SETUP_DATA                      SetupData;
  EFI_PEI_SERVICES                **PeiServices;
  EFI_RUNTIME_SERVICES            *RunServices;
  EFI_PEI_READ_ONLY_VARIABLE2_PPI *ReadOnlyVariable = NULL;
  UINTN                           VariableSize = sizeof( SETUP_DATA );
  UINT8                           i;
  UINT32                          Buffer32;
  PCH_SERIES 					  PchSeries = GetPchSeries();

  // Porting Start
  //  Update SB_SETUP_DATA according to the default values.
  SbSetupData->PchLan                   = 1;
  SbSetupData->PchWakeOnLan             = 1; 
  SbSetupData->SlpLanLow                = 1;
  SbSetupData->BoardCapability          = 0;
  SbSetupData->DeepSxBattMode           = 0;
  SbSetupData->DeepSxMode               = 0;
  SbSetupData->Gp27Wake                 = 1;
  SbSetupData->PcieWake                 = 0;
  SbSetupData->PchAzalia                = 2;
  SbSetupData->AzaliaDs                 = 0; 
  SbSetupData->AzaliaPme                = 0;
  SbSetupData->PchPciClockRun           = 1;
  SbSetupData->SirqMode                 = 0;
  SbSetupData->PchEnableCrid            = 1;
  SbSetupData->PchDisplay               = 1;
  SbSetupData->Hpet                     = 1;
  SbSetupData->SlpS4AssW                = 3;
  SbSetupData->LastState                = 2;
  SbSetupData->Port80Route              = RESERVED_PAGE_ROUTE;
  SbSetupData->AspmMode                 = 0;
  SbSetupData->SmiLock                  = 0;
  SbSetupData->BiosLock                 = 0;
  SbSetupData->GpioLock                 = 0;
  SbSetupData->BiosInterfaceLock        = 0;
  SbSetupData->RtcLock                  = 1;
  SbSetupData->PchDmiAspm               = 1;
  SbSetupData->PchDmiExtSync            = 0;
  SbSetupData->PcieClockGating          = 1;
  SbSetupData->RootPortFunctionSwapping = 1;
  SbSetupData->PcieUsbWa                = 0;
  SbSetupData->PchUsbPerPortCtl         = 0;

#if EHCI_CON_DISCON_WAKE_UP_SUPPORT
  SbSetupData->EhciConDisConWakeUp      = 0;
#endif

  SbSetupData->PchSata                  = 1;
  if(PchSeries == PchLp){
  	SbSetupData->ULTSataInterfaceMode   = 1;
  }else{
  	SbSetupData->SataInterfaceMode      = 0;
  }
  SbSetupData->SataTestMode             = 0;
#if SataDriver_SUPPORT
  SbSetupData->SataRaidRom              = 0;
#endif
  SbSetupData->SalpSupport              = 1;
  SbSetupData->SataControllerSpeed      = 3;
  SbSetupData->SataAlternateId          = 0;
  SbSetupData->PcieRootPortSBDE         = 0;
  SbSetupData->PcieSBDEPort             = 0;
  //do not use i[8] 
  for(i   = 0; i < 8; i++) {
    SbSetupData->PcieRootPortEn[i]      = 1;
    SbSetupData->PcieRootPortAspm[i]    = 4; 
    SbSetupData->PcieRootPortURE[i]     = 0;  
    SbSetupData->PcieRootPortFEE[i]     = 0;  
    SbSetupData->PcieRootPortNFE[i]     = 0;  
    SbSetupData->PcieRootPortCEE[i]     = 0;  
    SbSetupData->PcieRootPortCTD[i]     = 0;  
    SbSetupData->PcieRootPortPIE[i]     = 0;  
    SbSetupData->PcieRootPortSFE[i]     = 0;  
    SbSetupData->PcieRootPortSNE[i]     = 0;  
    SbSetupData->PcieRootPortSCE[i]     = 0;  
    SbSetupData->PcieRootPortL1S[i]     = 0; 
    SbSetupData->PcieRootPortPMCE[i]    = 1; 
    SbSetupData->PcieRootPortHPE[i]     = 0;
    SbSetupData->PcieRootPortSpeed[i]   = 0;
    SbSetupData->PcieRPDetectNonComplaint[i] = 0;
    SbSetupData->PcieLtrEnable[i]       = 1;
    SbSetupData->PcieLtrConfigLock[i]       = 1;
    SbSetupData->PcieSnoopLatencyOverrideMode[i]          = 2;
    SbSetupData->PcieSnoopLatencyOverrideMultiplier[i]    = 2;
    SbSetupData->PcieSnoopLatencyOverrideValue[i]         = 60;
    SbSetupData->PcieNonSnoopLatencyOverrideMode[i]       = 2;
    SbSetupData->PcieNonSnoopLatencyOverrideMultiplier[i] = 2;
    SbSetupData->PcieNonSnoopLatencyOverrideValue[i]      = 60;

#if Thunderbolt_SUPPORT
    if (i == TBT_UP_PORT_FUNC){
       SbSetupData->PcieMemRsvdalig[i]     = 26;
       SbSetupData->PciePFMemRsvdalig[i]   = 28;
    }
    else{
       SbSetupData->PcieMemRsvdalig[i]     = 1;
       SbSetupData->PciePFMemRsvdalig[i]   = 1;
    }
#else
    SbSetupData->PcieMemRsvdalig[i]     = 1;
    SbSetupData->PciePFMemRsvdalig[i]   = 1;
#endif
  }

  //do not use i[14] 
  for(i   = 0; i < 14; i++) {
     SbSetupData->PchUsbPort[i]         = 1;
  }

  //do not use i[6] 
  for(i   = 0; i < 6; i++) {
     SbSetupData->PchUsb30Port[i]       = 1;
  }

  //do not use i[6] 
  for(i   = 0; i < 6; i++) {
    SbSetupData->SataPort[i]            = 0;
    SbSetupData->SataHotPlug[i]         = 0;
    SbSetupData->SataMechanicalSw[i]    = 0;
    SbSetupData->ExternalSata[i]        = 0;
    SbSetupData->SataSpinUp[i]          = 0;
    SbSetupData->SataDevSlp[i]          = 0;
    SbSetupData->EnableDitoConfig[i]    = 0;
    SbSetupData->DmVal[i]               = 15;
    SbSetupData->DitoVal[i]             = 625;
    SbSetupData->SolidStateDrive[i]     = 0;
  }

  SbSetupData->UsbPrecondition          = 0;
  SbSetupData->PchUsb30Mode             = 3;
//  for(i   = 0; i < 4; i++) {
//    SbSetupData->PchUsb30HsPortSwitchable[i]   = 1;
//  }
  SbSetupData->PchEnableRmh1            = 1;

  //do not use i[2] 
  for(i   = 0; i < 2; i++) {
    SbSetupData->PchUsb20[i]            = 1;
  }
  SbSetupData->PchUsb30PreBootSupport   = 1;
  SbSetupData->PchUsb30IdleL1			      = 1;
  SbSetupData->PchUsb30Btcg			        = 0;
  SbSetupData->PchUsb20PinRoute         = 1;
  SbSetupData->PchUsb30PinEnable        = 1;
  for(i   = 0; i < 14; i++) {
    SbSetupData->ManualModeUsb20PerPinRoute[i]  = 0;
  }
  for(i   = 0; i < 6; i++) {
    SbSetupData->ManualModeUsb30PerPinEnable[i] = 0;
  }
//  SbSetupData->XhciStreams              = 1;

  SbSetupData->SataRaidR0               = 1;
  SbSetupData->SataRaidR1               = 1;
  SbSetupData->SataRaidR10              = 1;
  SbSetupData->SataRaidR5               = 1;
  SbSetupData->SataRaidIrrt             = 1;
  SbSetupData->SataRaidOub              = 1;
  SbSetupData->SataHddlk                = 1;
  SbSetupData->SataLedl                 = 1;
  SbSetupData->SataRaidIooe             = 1;
  SbSetupData->SmartStorage             = 1;
  SbSetupData->OromUiDelay              = 0;

  //  PCH Thermal
  SbSetupData->AutoThermalReport        = 1;
  SbSetupData->Ac1TripPoint             = 55;
  SbSetupData->Ac0TripPoint             = 71;
  SbSetupData->Ac0FanSpeed              = 100;
  SbSetupData->Ac1FanSpeed              = 75;
  SbSetupData->PassiveThermalTripPoint    = 95;
  SbSetupData->CriticalThermalTripPoint   = 100;
  SbSetupData->PassiveTc1Value          = 1;
  SbSetupData->PassiveTc2Value          = 5;
  SbSetupData->PassiveTspValue          = 10;
        
  SbSetupData->ThermalDeviceEnable      = 0; 
  SbSetupData->PchCrossThrottling       = 0; 
  SbSetupData->CPUTempReadEnable        = 1;
  SbSetupData->CPUEnergyReadEnable      = 1;
  SbSetupData->PCHTempReadEnable        = 1;
        
  SbSetupData->AlertEnableLock          = 0;
  SbSetupData->PchAlert                 = 0;
  SbSetupData->DimmAlert                = 0;

  SbSetupData->PchHotLevel              = 0;
  SbSetupData->TPV_Restrict_Enable      = 0;

  SbSetupData->TsOnDimm1                = 0;
  SbSetupData->TsOnDimm2                = 0;
  SbSetupData->TsOnDimm3                = 0;
  SbSetupData->TsOnDimm4                = 0;

  SbSetupData->SMBusECMsgLen            = 0;
  SbSetupData->SMBusECMsgPEC            = 0;

  SbSetupData->ECTurboControlMode       = 0;
  SbSetupData->ACBrickCapacity          = 1;
  SbSetupData->ECPollingPeriod          = 1;
  SbSetupData->ECGuardBandValue         = 0;
  SbSetupData->ECAlgorithmSel           = 1;
  SbSetupData->ECHybridPowerBoost       = 0;
  SbSetupData->ECHybridCurrent          = 0x1284;
  SbSetupData->ECTG        				= 0;

  // PchLp LPSS
  SbSetupData->LpssDmaEnable            = 1;
  SbSetupData->LpssI2c0Enable           = 1;
  SbSetupData->LpssI2c1Enable           = 1;
  SbSetupData->LpssSpi0Enable           = 1;
  SbSetupData->LpssSpi1Enable           = 1;
  SbSetupData->LpssUart0Enable          = 1;
  SbSetupData->LpssUart1Enable          = 1;
  SbSetupData->LpssSdioEnable           = 1;
  SbSetupData->LpssMode                 = 1;
  SbSetupData->LpssIntMode              = 1;
  SbSetupData->I2C0VoltageSelect        = 1;
  SbSetupData->I2C1VoltageSelect        = 0;
  SbSetupData->SensorHub         		    = 0;
  SbSetupData->TPD4		         		      = 0;
  SbSetupData->AtmelTPL        			    = 0;
  SbSetupData->ElanTPL        			    = 0;
  SbSetupData->ElanTPD        			    = 0;
  SbSetupData->SynaTPD                  = 0;
  SbSetupData->NtriTPL               	  = 0;
  SbSetupData->EetiTPL                	= 0;
  SbSetupData->AlpsTPD                 	= 0;
  SbSetupData->CyprTPD                 	= 0;
  SbSetupData->Bluetooth0              	= 0;
  SbSetupData->Bluetooth1        			  = 0;

  SbSetupData->I2C0SSH                  = 432;
  SbSetupData->I2C0SSL                  = 507;
  SbSetupData->I2C0SSD                  = 9;
  SbSetupData->I2C0FMH                  = 72;
  SbSetupData->I2C0FML                  = 160;
  SbSetupData->I2C0FMD                  = 9;
  SbSetupData->I2C0FPH                  = 29;
  SbSetupData->I2C0FPL                  = 50;
  SbSetupData->I2C0FPD                  = 5;
  SbSetupData->I2C0M0C0                 = 500;
  SbSetupData->I2C0M1C0                 = 2000;
  SbSetupData->I2C0M2C0                 = 0;

  SbSetupData->I2C1SSH                  = 432;
  SbSetupData->I2C1SSL                  = 507;
  SbSetupData->I2C1SSD                  = 9;
  SbSetupData->I2C1FMH                  = 72;
  SbSetupData->I2C1FML                  = 160;
  SbSetupData->I2C1FMD                  = 9;
  SbSetupData->I2C1FPH                  = 29;
  SbSetupData->I2C1FPL                  = 50;
  SbSetupData->I2C1FPD                  = 5;
  SbSetupData->I2C1M0C1                 = 500;
  SbSetupData->I2C1M1C1                 = 2000;
  SbSetupData->I2C1M2C1                 = 0;

  SbSetupData->SPI0M0C2                 = 500;
  SbSetupData->SPI0M1C2                 = 2000;

  SbSetupData->SPI1M0C3                 = 500;
  SbSetupData->SPI1M1C3                 = 2000;

  SbSetupData->UAR0M0C4                 = 500;
  SbSetupData->UAR0M1C4                 = 2000;

  SbSetupData->UAR1M0C5                 = 500;
  SbSetupData->UAR1M1C5                 = 2000;

  // PchLp Audio DSP
  SbSetupData->ADspEnable               = 0;
  SbSetupData->ADspD3PG                 = 1;
  SbSetupData->ADspCodecSelect          = 0;
  SbSetupData->ADspBluetooth            = 0;
  SbSetupData->ADspMode                 = 1;
  // Porting End
  SbSetupData->NFCE                 	= 0;

  if (Pei) {
    PeiServices = (EFI_PEI_SERVICES **)Services;
    Status = (*PeiServices)->LocatePpi( PeiServices, \
                                        &gPeiReadOnlyVarPpiGuid, \
                                        0, \
                                        NULL, \
                                        &ReadOnlyVariable );

    if (!EFI_ERROR(Status)) {
      Status = ReadOnlyVariable->GetVariable( ReadOnlyVariable, \
                                              L"Setup", \
                                              &gSetupGuid, \
                                              NULL, \
                                              &VariableSize, \
                                              &SetupData );
    }
  } else {
    RunServices = (EFI_RUNTIME_SERVICES *)Services;
    Status = RunServices->GetVariable( L"Setup", \
                                       &gSetupGuid, \
                                       NULL, \
                                       &VariableSize, \
                                       &SetupData );
  }

  if (EFI_ERROR(Status)) {
    SbOemSetupCallbacks( Services, SbSetupData, NULL, Pei );
  } else {
    SbOemSetupCallbacks( Services, SbSetupData, &SetupData, Pei );
  }

  // Thermal reporting policy is based on strap settings (PCH Strap 15 [14])
  if ((READ_MEM16_SPI (0x04) & BIT14) == BIT14) {  // Check Flash Descriptor Valid
    Buffer32 = READ_MEM32_SPI(R_RCRB_SPI_FDOC) & (~(B_PCH_SPI_FDOC_FDSS_MASK | B_PCH_SPI_FDOC_FDSI_MASK));
    Buffer32 |= (UINT32) (V_PCH_SPI_FDOC_FDSS_PCHS | R_PCH_SPI_STRP15);
    MMIO_WRITE32(SB_RCRB_BASE_ADDRESS + SPI_BASE_ADDRESS|R_RCRB_SPI_FDOC, Buffer32);
    Buffer32 = READ_MEM32_SPI(R_RCRB_SPI_FDOD);
    if ((Buffer32 & BIT14) == 0) {
      SbSetupData->TrEnabled = 1;
    } else {
      SbSetupData->TrEnabled = 0;
    }
  }
}

#if defined SB_SETUP_SUPPORT && SB_SETUP_SUPPORT == 1
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SbSetupCallbacks
//
// Description: This function returns SB Chipset setup data from system SetupData
//              variable 
//
// Input:       *Services    - Pointer to PeiServices or RuntimeServices
//                             structure  
//              *SbSetupData - Pointer to custom setup data to return
//              *SetupData   - Pointer to system setup data.
//              Pei          - Pei flag. If TRUE we are in PEI phase
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID SbSetupCallbacks (
  IN VOID              *Services,
  IN OUT SB_SETUP_DATA *SbSetupData,
  IN SETUP_DATA        *SetupData,
  IN BOOLEAN           Pei )
{
  UINT8 i;
  PCH_SERIES 	PchSeries = GetPchSeries();

  if (SetupData != NULL) {
    // Porting Start
    //  Update SB_SETUP_DATA according to the setup datas.
    SbSetupData->PchLan                 = SetupData->PchLan;
    SbSetupData->PchWakeOnLan           = SetupData->PchWakeOnLan;
    SbSetupData->SlpLanLow              = SetupData->SlpLanLow;
    SbSetupData->BoardCapability        = SetupData->BoardCapability;
    SbSetupData->DeepSxBattMode         = SetupData->DeepSxBattMode;
    SbSetupData->DeepSxMode             = SetupData->DeepSxMode;
    SbSetupData->Gp27Wake               = SetupData->Gp27Wake;
    SbSetupData->PcieWake               = SetupData->PcieWake;
    SbSetupData->PchAzalia              = SetupData->PchAzalia;
    SbSetupData->AzaliaDs               = SetupData->AzaliaDs; 
    SbSetupData->AzaliaPme              = SetupData->AzaliaPme;
    SbSetupData->Hpet                   = SetupData->Hpet;
    SbSetupData->PchPciClockRun         = SetupData->PchPciClockRun;
    SbSetupData->SirqMode               = SetupData->SirqMode;
    SbSetupData->PchEnableCrid          = SetupData->PchEnableCrid;
    SbSetupData->PchDisplay             = SetupData->PchDisplay;
    SbSetupData->SlpS4AssW              = SetupData->SlpS4AssW;
    SbSetupData->Port80Route            = SetupData->Port80Route;
    SbSetupData->LastState              = SetupData->LastState;
#if PCI_EXPRESS_SUPPORT
    SbSetupData->AspmMode               = SetupData->AspmMode;
#else 
    SbSetupData->AspmMode               = 0;
#endif

    SbSetupData->SmiLock                = SetupData->SmiLock;
    SbSetupData->BiosLock               = SetupData->BiosLock;
    SbSetupData->GpioLock               = SetupData->GpioLock;
    SbSetupData->BiosInterfaceLock      = SetupData->BiosInterfaceLock;
    SbSetupData->RtcLock                = SetupData->RtcLock;

    SbSetupData->PchDmiAspm             = SetupData->PchDmiAspm;
    SbSetupData->PchDmiExtSync          = SetupData->PchDmiExtSync;
    SbSetupData->PcieClockGating        = SetupData->PcieClockGating;
    SbSetupData->RootPortFunctionSwapping = SetupData->RootPortFunctionSwapping;
    SbSetupData->PcieUsbWa              = SetupData->PcieUsbWa;
    SbSetupData->PchUsbPerPortCtl       = SetupData->PchUsbPerPortCtl;

#if EHCI_CON_DISCON_WAKE_UP_SUPPORT
    SbSetupData->EhciConDisConWakeUp    = SetupData->EhciConDisConWakeUp;
#endif

    SbSetupData->PchSata                = SetupData->PchSata;
  	if(PchSeries == PchLp){
      SbSetupData->SataInterfaceMode    = SetupData->ULTSataInterfaceMode;
    }else{
      SbSetupData->SataInterfaceMode    = SetupData->SataInterfaceMode;
    }
    SbSetupData->SataTestMode           = SetupData->SataTestMode;
#if SataDriver_SUPPORT
    SbSetupData->SataRaidRom            = SetupData->SataRaidRom;
#endif
    SbSetupData->SalpSupport            = SetupData->SalpSupport;
    SbSetupData->SataControllerSpeed    = SetupData->SataControllerSpeed;
    SbSetupData->SataAlternateId        = SetupData->SataAlternateId;
    SbSetupData->PcieRootPortSBDE       = SetupData->PcieRootPortSBDE;
    SbSetupData->PcieSBDEPort           = SetupData->PcieSBDEPort;
    //do not use i[8] 
    for(i = 0; i < 8; i++) {
      SbSetupData->PcieRootPortEn[i]    = SetupData->PcieRootPortEn[i];
      SbSetupData->PcieRootPortAspm[i]  = SetupData->PcieRootPortAspm[i]; 
      SbSetupData->PcieRootPortURE[i]   = SetupData->PcieRootPortURE[i];  
      SbSetupData->PcieRootPortFEE[i]   = SetupData->PcieRootPortFEE[i];  
      SbSetupData->PcieRootPortNFE[i]   = SetupData->PcieRootPortNFE[i];  
      SbSetupData->PcieRootPortCEE[i]   = SetupData->PcieRootPortCEE[i];  
      SbSetupData->PcieRootPortCTD[i]   = SetupData->PcieRootPortCTD[i];  
      SbSetupData->PcieRootPortPIE[i]   = SetupData->PcieRootPortPIE[i];  
      SbSetupData->PcieRootPortSFE[i]   = SetupData->PcieRootPortSFE[i];  
      SbSetupData->PcieRootPortSNE[i]   = SetupData->PcieRootPortSNE[i];  
      SbSetupData->PcieRootPortSCE[i]   = SetupData->PcieRootPortSCE[i];
      SbSetupData->PcieRootPortL1S[i]   = SetupData->PcieRootPortL1S[i];    
      SbSetupData->PcieRootPortPMCE[i]  = SetupData->PcieRootPortPMCE[i]; 
      SbSetupData->PcieRootPortHPE[i]   = SetupData->PcieRootPortHPE[i];
      SbSetupData->PcieRootPortSpeed[i] = SetupData->PcieRootPortSpeed[i];
      SbSetupData->PcieMemRsvdalig[i]   = SetupData->PcieMemRsvdalig[i];
      SbSetupData->PciePFMemRsvdalig[i] = SetupData->PciePFMemRsvdalig[i];
      SbSetupData->PcieRPDetectNonComplaint[i] = SetupData->PcieRPDetectNonComplaint[i];
      SbSetupData->PcieLtrEnable[i]       = SetupData->PcieLtrEnable[i];;
      SbSetupData->PcieLtrConfigLock[i]       = SetupData->PcieLtrConfigLock[i];;
      SbSetupData->PcieSnoopLatencyOverrideMode[i]          = SetupData->PcieSnoopLatencyOverrideMode[i];;
      SbSetupData->PcieSnoopLatencyOverrideMultiplier[i]    = SetupData->PcieSnoopLatencyOverrideMultiplier[i];;
      SbSetupData->PcieSnoopLatencyOverrideValue[i]         = SetupData->PcieSnoopLatencyOverrideValue[i];;
      SbSetupData->PcieNonSnoopLatencyOverrideMode[i]       = SetupData->PcieNonSnoopLatencyOverrideMode[i];;
      SbSetupData->PcieNonSnoopLatencyOverrideMultiplier[i] = SetupData->PcieNonSnoopLatencyOverrideMultiplier[i];;
      SbSetupData->PcieNonSnoopLatencyOverrideValue[i]      = SetupData->PcieNonSnoopLatencyOverrideValue[i];;
    }

    //do not use i[14] 
    for(i = 0; i < 14; i++) {
       SbSetupData->PchUsbPort[i]       = SetupData->PchUsbPort[i];
    }

    //do not use i[6] 
    for(i = 0; i < 6; i++) {
       SbSetupData->PchUsb30Port[i]     = SetupData->PchUsbPort[i];
    }

    //do not use i[6] 
    for(i = 0; i < 6; i++) {
      SbSetupData->SataPort[i]          = SetupData->SataPort[i];
      SbSetupData->SataHotPlug[i]       = SetupData->SataHotPlug[i];

      if (SbSetupData->SataHotPlug[i] == 1)
        SbSetupData->SataMechanicalSw[i]= SetupData->SataMechanicalSw[i];
      else
        SbSetupData->SataMechanicalSw[i]= 0;

      SbSetupData->ExternalSata[i]      = SetupData->ExternalSata[i];

      SbSetupData->SataSpinUp[i]        = SetupData->SataSpinUp[i];
      SbSetupData->SataDevSlp[i]        = SetupData->SataDevSlp[i];
      SbSetupData->EnableDitoConfig[i]  = SetupData->SataEnableDitoConfig[i];
      SbSetupData->DitoVal[i]           = SetupData->SataDitoVal[i];
      SbSetupData->DmVal[i]             = SetupData->SataDmVal[i];
      SbSetupData->SolidStateDrive[i]   = SetupData->SolidStateDrive[i];
    }

    SbSetupData->UsbPrecondition        = SetupData->UsbPrecondition;
    SbSetupData->PchUsb30Mode           = SetupData->PchUsb30Mode;
//    for(i = 0; i < 4; i++) {
//      SbSetupData->PchUsb30HsPortSwitchable[i] = SetupData->PchUsb30HsPortSwitchable[i];
//    }
    SbSetupData->PchEnableRmh1          = SetupData->PchEnableRmh1;

    SbSetupData->PchUsb30PreBootSupport = SetupData->PchUsb30PreBootSupport;
    SbSetupData->PchUsb30IdleL1 		= SetupData->PchUsb30IdleL1;
    SbSetupData->PchUsb30Btcg 		  = SetupData->PchUsb30Btcg;

    SbSetupData->PchUsb20PinRoute         = SetupData->PchUsb20PinRoute;
    SbSetupData->PchUsb30PinEnable        = SetupData->PchUsb30PinEnable;
    for(i   = 0; i < 14; i++) {
      SbSetupData->ManualModeUsb20PerPinRoute[i]    = SetupData->ManualModeUsb20PerPinRoute[i];
    }
    for(i   = 0; i < 6; i++) {
      SbSetupData->ManualModeUsb30PerPinEnable[i]   = SetupData->ManualModeUsb30PerPinEnable[i];
    }
//    SbSetupData->XhciStreams            = SetupData->XhciStreams;

    //do not use i[2] 
    for(i = 0; i < 2; i++) {
      SbSetupData->PchUsb20[i]          = SetupData->PchUsb20[i];
    }

    SbSetupData->SataRaidR0             = SetupData->SataRaidR0;
    SbSetupData->SataRaidR1             = SetupData->SataRaidR1;
    SbSetupData->SataRaidR10            = SetupData->SataRaidR10;
    SbSetupData->SataRaidR5             = SetupData->SataRaidR5;
    SbSetupData->SataRaidIrrt           = SetupData->SataRaidIrrt;
    SbSetupData->SataRaidOub            = SetupData->SataRaidOub;
    SbSetupData->SataHddlk              = SetupData->SataHddlk;
    SbSetupData->SataLedl               = SetupData->SataLedl;
    SbSetupData->SataRaidIooe           = SetupData->SataRaidIooe;
    SbSetupData->SmartStorage           = SetupData->SmartStorage;
    SbSetupData->OromUiDelay            = SetupData->OromUiDelay;

    //  PCH Thermal
    SbSetupData->AutoThermalReport      = SetupData->AutoThermalReport;
    SbSetupData->Ac1TripPoint           = SetupData->Ac1TripPoint;
    SbSetupData->Ac0TripPoint           = SetupData->Ac0TripPoint;
    SbSetupData->Ac0FanSpeed            = SetupData->Ac0FanSpeed;
    SbSetupData->Ac1FanSpeed            = SetupData->Ac1FanSpeed;
    SbSetupData->PassiveThermalTripPoint  = SetupData->PassiveThermalTripPoint;
    SbSetupData->CriticalThermalTripPoint = SetupData->CriticalThermalTripPoint;
    SbSetupData->PassiveTc1Value        = SetupData->PassiveTc1Value;
    SbSetupData->PassiveTc2Value        = SetupData->PassiveTc2Value;
    SbSetupData->PassiveTspValue        = SetupData->PassiveTspValue;

    SbSetupData->AlertEnableLock        = SetupData->AlertEnableLock;
    SbSetupData->PchAlert               = SetupData->PchAlert;
    SbSetupData->DimmAlert              = SetupData->DimmAlert;

    SbSetupData->CPUTempReadEnable      = SetupData->CPUTempReadEnable;
    SbSetupData->CPUEnergyReadEnable    = SetupData->CPUEnergyReadEnable;
    SbSetupData->ThermalDeviceEnable    = SetupData->ThermalDeviceEnable; 
    SbSetupData->PchCrossThrottling     = SetupData->PchCrossThrottling;
    SbSetupData->PCHTempReadEnable      = SetupData->PCHTempReadEnable;

    SbSetupData->PchHotLevel            = SetupData->PchHotLevel;
    SbSetupData->TPV_Restrict_Enable    = SetupData->TPV_Restrict_Enable;

    SbSetupData->TsOnDimm1              = SetupData->TsOnDimm1;
    SbSetupData->TsOnDimm2              = SetupData->TsOnDimm2;
    SbSetupData->TsOnDimm3              = SetupData->TsOnDimm3;
    SbSetupData->TsOnDimm4              = SetupData->TsOnDimm4;

    SbSetupData->SMBusECMsgLen          = SetupData->SMBusECMsgLen;
    SbSetupData->SMBusECMsgPEC          = SetupData->SMBusECMsgPEC;

    SbSetupData->ECTurboControlMode     = SetupData->ECTurboControlMode;
    SbSetupData->ACBrickCapacity        = SetupData->ACBrickCapacity;
    SbSetupData->ECPollingPeriod        = SetupData->ECPollingPeriod;
    SbSetupData->ECGuardBandValue       = SetupData->ECGuardBandValue;
    SbSetupData->ECAlgorithmSel         = SetupData->ECAlgorithmSel;
    SbSetupData->ECHybridPowerBoost     = SetupData->ECHybridPowerBoost;
    SbSetupData->ECHybridCurrent        = SetupData->ECHybridCurrent;
    SbSetupData->ECTG        			= SetupData->ECTG;

    // PchLp LPSS
    SbSetupData->LpssDmaEnable          = SetupData->LpssDmaEnable;
    SbSetupData->LpssI2c0Enable         = SetupData->LpssI2c0Enable;
    SbSetupData->LpssI2c1Enable         = SetupData->LpssI2c1Enable;
    SbSetupData->LpssSpi0Enable         = SetupData->LpssSpi0Enable;
    SbSetupData->LpssSpi1Enable         = SetupData->LpssSpi1Enable;
    SbSetupData->LpssUart0Enable        = SetupData->LpssUart0Enable;
    SbSetupData->LpssUart1Enable        = SetupData->LpssUart1Enable;
    SbSetupData->LpssSdioEnable         = SetupData->LpssSdioEnable;
    SbSetupData->LpssMode               = SetupData->LpssMode;
    SbSetupData->LpssIntMode            = SetupData->LpssIntMode;
    SbSetupData->I2C0VoltageSelect      = SetupData->I2C0VoltageSelect;
    SbSetupData->I2C1VoltageSelect      = SetupData->I2C1VoltageSelect;
    SbSetupData->SensorHub         		  = SetupData->SensorHub;
    SbSetupData->TPD4	         		      = SetupData->TPD4;
    SbSetupData->AtmelTPL        		    = SetupData->AtmelTPL;
    SbSetupData->ElanTPL        		    = SetupData->ElanTPL;
    SbSetupData->ElanTPD        		    = SetupData->ElanTPD;
    SbSetupData->SynaTPD               	= SetupData->SynaTPD;
  	SbSetupData->NtriTPL               	= SetupData->NtriTPL;
  	SbSetupData->EetiTPL               	= SetupData->EetiTPL;
  	SbSetupData->AlpsTPD               	= SetupData->AlpsTPD;
  	SbSetupData->CyprTPD               	= SetupData->CyprTPD;
    SbSetupData->Bluetooth0            	= SetupData->Bluetooth0;
    SbSetupData->Bluetooth1      		    = SetupData->Bluetooth1;

    SbSetupData->I2C0SSH                  = SetupData->I2C0SSH;
    SbSetupData->I2C0SSL                  = SetupData->I2C0SSL;
    SbSetupData->I2C0SSD                  = SetupData->I2C0SSD;
    SbSetupData->I2C0FMH                  = SetupData->I2C0FMH;
    SbSetupData->I2C0FML                  = SetupData->I2C0FML;
    SbSetupData->I2C0FMD                  = SetupData->I2C0FMD;
    SbSetupData->I2C0FPH                  = SetupData->I2C0FPH;
    SbSetupData->I2C0FPL                  = SetupData->I2C0FPL;
    SbSetupData->I2C0FPD                  = SetupData->I2C0FPD;
    SbSetupData->I2C0M0C0                 = SetupData->I2C0M0C0;
    SbSetupData->I2C0M1C0                 = SetupData->I2C0M1C0;
    SbSetupData->I2C0M2C0                 = SetupData->I2C0M2C0;

    SbSetupData->I2C1SSH                  = SetupData->I2C1SSH;
    SbSetupData->I2C1SSL                  = SetupData->I2C1SSL;
    SbSetupData->I2C1SSD                  = SetupData->I2C1SSD;
    SbSetupData->I2C1FMH                  = SetupData->I2C1FMH;
    SbSetupData->I2C1FML                  = SetupData->I2C1FML;
    SbSetupData->I2C1FMD                  = SetupData->I2C1FMD;
    SbSetupData->I2C1FPH                  = SetupData->I2C1FPH;
    SbSetupData->I2C1FPL                  = SetupData->I2C1FPL;
    SbSetupData->I2C1FPD                  = SetupData->I2C1FPD;
    SbSetupData->I2C1M0C1                 = SetupData->I2C1M0C1;
    SbSetupData->I2C1M1C1                 = SetupData->I2C1M1C1;
    SbSetupData->I2C1M2C1                 = SetupData->I2C1M2C1;

    SbSetupData->SPI0M0C2                 = SetupData->SPI0M0C2;
    SbSetupData->SPI0M1C2                 = SetupData->SPI0M1C2;

    SbSetupData->SPI1M0C3                 = SetupData->SPI1M0C3;
    SbSetupData->SPI1M1C3                 = SetupData->SPI1M1C3;

    SbSetupData->UAR0M0C4                 = SetupData->UAR0M0C4;
    SbSetupData->UAR0M1C4                 = SetupData->UAR0M1C4;

    SbSetupData->UAR1M0C5                 = SetupData->UAR1M0C5;
    SbSetupData->UAR1M1C5                 = SetupData->UAR1M1C5;

    // PchLp Audio DSP
    SbSetupData->ADspEnable             = SetupData->ADspEnable;
    SbSetupData->ADspD3PG               = SetupData->ADspD3PG;
    SbSetupData->ADspCodecSelect        = SetupData->ADspCodecSelect;
    SbSetupData->ADspBluetooth          = SetupData->ADspBluetooth;
    SbSetupData->ADspMode               = SetupData->ADspMode;
    // Porting End
    SbSetupData->NFCE                 	= SetupData->NFCE;
  }
}

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
