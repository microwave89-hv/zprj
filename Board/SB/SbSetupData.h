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
// $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Board/SbSetupData.h 27    8/01/13 4:32a Scottyang $
//
// $Revision: 27 $
//
// $Date: 8/01/13 4:32a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Board/SbSetupData.h $
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
// 22    2/09/13 12:13a Scottyang
// [TAG]  		EIP114922
// [Category]  	Improvement
// [Description]  	Update PCH RC 1.1.0.
// [Files]  		..\ReferenceCode\Chipset\LynxPoint\*.*, SBDxe.c, SBPEI.c,
// SB.sd, SB.uni, GetSetupData.c, SbSetupDara.h
// 
// 21    1/31/13 10:56a Scottyang
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Add Serial IO GNVS setup option. 
// [Files]  		SBDxe.c, SB.sd, SB.uni, SbSetupData.h, GetSetupData.c
// 
// 20    1/10/13 4:49a Scottyang
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Create DTIO value and DM value option
// [Files]  		SB.sd, SB.uni, SbSetupData.h, GetSetupData.c, SBDxe.c
// 
// 19    1/03/13 4:56a Scottyang
// [TAG]  		None
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Build error when set IDE mode as default.
// [RootCause]  	The ULT did not support IDE mode that made the value
// redefine.
// [Solution]  	Separate Sata inter face for 2 Chip and ULT.
// [Files]  		SB.sd, GetSetupData.c, SbSetupData.h
// 
// 18    12/24/12 5:42a Scottyang
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Add option for XHCI Idel L1 workaroung.
// [Files]  		GetSetupData.c, SbSetupData.h, SB.sd, SB.uni, SBDxe.c,
// SBPEI.c
// 
// 17    12/22/12 2:05a Scottyang
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Add PCIE "L1 Substates"setup option.
// [Files]  		GetSetupData.c, SbSetupData.h, SB.sd, SB.uni, SBDxe.c
// 
// 16    12/18/12 6:03a Scottyang
// [TAG] EIP109697
// [Category] Improvement
// [Description] Update PCH RC 0.8.1
// [Files] ReferenceCode\Chipset\LynxPoint\*.*, SBDxe.c, SBPEI.c, SB.sd,
// SbSetupData.c, GetSetupDate.c
// 
// 15    12/17/12 6:41a Scottyang
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Add setup menu for LPSS and ECTG.
// [Files]  		GetSetupData.c
// SbSetupData.h
// SB.sd
// SB.uni
// SBDxe.c
// 
// 14    12/13/12 10:34a Scottyang
// [TAG]  		EIP106687
// [Category]  	Improvement
// [Description]  	Add option for delay to detect PCIE card.
// [Files]  		SBPEI.c, SB.sd, SB.uni, GetSetupData.c, SbSetupData.h,
// PciBus.c
// 
// 13    11/20/12 9:45a Scottyang
// [TAG]  		EIP107014
// [Category]  	Improvement
// [Description]  	Update RC 0.8.0
// [Files]  		ReferenceCode\Chipset\LynxPoint\*.*, SBDxe.c, SBPEI.c,
// SB.sd, SbSetupData.c, GetSetupDate.c
// 
// 12    11/08/12 8:33a Scottyang
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Add device item that connect LPSS.
// [Files]  		GetSetupData.c, SbSetupData.h, SBDxe.c, SB.sd, SB.uni
// 
// 11    11/07/12 6:09a Scottyang
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Remove HDMI item.
// [Files]  		SB.sd, SB.uni, GetSetupData.c, SbSetupData.h
// 
// 10    10/25/12 7:18a Scottyang
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Create NFC item at setup
// [Files]  		SB.sd, SB.uni, SbSetupData.h
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
// 7     9/26/12 3:50a Victortu
// [TAG]           None
// [Category]      Improvement
// [Description]   Implement ULT platform LPSS and ADSP setup option.
// [Files]         GetSetupData.c, SB.sd, SB.uni, SbSetupData.h, SBDxe.c,
// SB.sdl
// 
// 6     9/12/12 5:13a Victortu
// [TAG]           None
// [Category]      Improvement
// [Description]   Modify for Thunderbolt support.
// [Files]         GetSetupData.c, SB.sdl, SB.sd, SB.uni, SbSetupData.h,
// PciHotPlug.c
// 
// 5     8/13/12 10:15a Victortu
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
// 4     7/27/12 6:05a Victortu
// [TAG]           None
// [Category]      Improvement
// [Description]   Update setup items and policies.
// [Files]         GetSetupData.c, SB.sdl, SB.sd, SB.uni, SbSetupData.h,
// SBPEI.c, SBDXE.c
// 
// 3     5/03/12 6:33a Victortu
// [TAG]           None 
// [Category]      Improvement 
// [Description]   Modify to support Thunderbolt. 
// [Files]         SB.sd; SB.uni; SB.sdl; SbSetupData.h; PciHotPlug.c 
// 
// 2     4/25/12 9:06a Victortu
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
// Name:        SbSetupData.h
//
// Description: South Bridge setup data header file, define all the South
//              Bridge setup items and a structures in this file. 
//
// Notes:       The context of the SB_SETUP_DATA may be able to copy from
//              SB.SD directly 
//
//<AMI_FHDR_END>
//*************************************************************************

#ifndef __SB_SETUP_DATA_H__ // To Avoid this header get compiled twice
#define __SB_SETUP_DATA_H__

#include <Efi.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct  _SB_SETUP_DATA  SB_SETUP_DATA;

#pragma pack(push, 1)

typedef struct _SB_SETUP_DATA {
    UINT8   PchLan;
    UINT8   PchWakeOnLan;
    UINT8   SlpLanLow;
    UINT8   BoardCapability;
    UINT8   DeepSxBattMode;
    UINT8   DeepSxMode;
    UINT8   Gp27Wake;
    UINT8   PcieWake;
    UINT8   PchAzalia;
    UINT8   AzaliaDs;
    UINT8   AzaliaPme;
    UINT8   PchPciClockRun;
    UINT8   SirqMode;
    UINT8   PchDisplay;
    UINT8   PchEnableCrid;
    UINT8   SmiLock;
    UINT8   BiosLock;
    UINT8   GpioLock;
    UINT8   BiosInterfaceLock;
    UINT8   RtcLock;
    // PCH DMI
    UINT8   PchDmiAspm;
    UINT8   PchDmiExtSync;
    // PCI_EXPRESS_CONFIG, 8 ROOT PORTS
    UINT8   PcieUsbWa;
    UINT8   PcieClockGating;
    UINT8   PcieRootPortSBDE;
    UINT8   PcieSBDEPort;
    UINT8   RootPortFunctionSwapping;
    UINT8   PcieRootPortEn[8];
    UINT8   PcieRootPortAspm[8]; 
    UINT8   PcieRootPortURE[8];  
    UINT8   PcieRootPortFEE[8];  
    UINT8   PcieRootPortNFE[8];  
    UINT8   PcieRootPortCEE[8];  
    UINT8   PcieRootPortCTD[8];  
    UINT8   PcieRootPortPIE[8];  
    UINT8   PcieRootPortSFE[8];  
    UINT8   PcieRootPortSNE[8];  
    UINT8   PcieRootPortSCE[8];  
    UINT8   PcieRootPortL1S[8]; 
    UINT8   PcieRootPortPMCE[8]; 
    UINT8   PcieRootPortHPE[8];
    UINT8   PcieRootPortSpeed[8];
    UINT8   PcieRPDetectNonComplaint[8];

    UINT8   PcieLtrEnable[8];
    UINT8   PcieLtrConfigLock[8];
    UINT8   PcieSnoopLatencyOverrideMode[8];
    UINT8   PcieSnoopLatencyOverrideMultiplier[8];
    UINT8   PcieSnoopLatencyOverrideValue[8];
    UINT8   PcieNonSnoopLatencyOverrideMode[8];
    UINT8   PcieNonSnoopLatencyOverrideMultiplier[8];
    UINT8   PcieNonSnoopLatencyOverrideValue[8];

    // PCI Bridge Resources
    UINT8   ExtraBusRsvd[8];
    UINT16  PcieMemRsvd[8];
    UINT8   PcieMemRsvdalig[8];
    UINT16  PciePFMemRsvd[8];
    UINT8   PciePFMemRsvdalig[8];
    UINT8   PcieIoRsvd[8];
//    UINT8   ExtraBusRsv2[8];

#if HPET_SUPPORT
    UINT8   Hpet;
#endif
    UINT8   SlpS4AssW;
    UINT8   LastState;
    UINT8   Port80Route;
    // Usb Config
    UINT8   UsbPrecondition;
    UINT8   PchUsb30Mode;
//    UINT8   PchUsb30HsPortSwitchable[4];
    UINT8   PchEnableRmh1;
    UINT8   PchUsb20[2];
    UINT8   PchUsbPerPortCtl;
    UINT8   EhciConDisConWakeUp;
    UINT8   PchUsbPort[14];
    UINT8   PchUsb30Port[6];
    UINT8   PchUsb30PreBootSupport;
    UINT8   PchUsb30IdleL1;
    UINT8   PchUsb30Btcg;
    UINT8   PchUsb20PinRoute;
    UINT8   ManualModeUsb20PerPinRoute[14];
    UINT8   PchUsb30PinEnable;
    UINT8   ManualModeUsb30PerPinEnable[6];
//    UINT8   XhciStreams;
    // Sata CONFIG
    UINT8   PchSata;
    UINT8   SataInterfaceMode;
    UINT8   ULTSataInterfaceMode;
    UINT8   SataTestMode;
#if SataDriver_SUPPORT
    UINT8   SataRaidRom;
#endif
    UINT8   SalpSupport;
    UINT8   SataControllerSpeed;
    UINT8   SataPort[6];
    UINT8   SataHotPlug[6];
    UINT8   ExternalSata[6];
    UINT8   SataMechanicalSw[6];
    UINT8   SolidStateDrive[6];
    UINT8   SataSpinUp[6];
    UINT8   SataDevSlp[4];
    UINT8   EnableDitoConfig[4];
    UINT8   DmVal[4];
    UINT16  DitoVal[4];
    UINT8   SataRaidR0;
    UINT8   SataRaidR1;
    UINT8   SataRaidR10;
    UINT8   SataRaidR5;
    UINT8   SataRaidIrrt;
    UINT8   SataRaidOub;
    UINT8   SataHddlk;
    UINT8   SataLedl;
    UINT8   SataRaidIooe;
    UINT8   SmartStorage;
    UINT8   OromUiDelay;
    UINT8   SataAlternateId;

    // PCH Thermal
    UINT8   AutoThermalReport;
    UINT8   Ac1TripPoint;
    UINT8   Ac0TripPoint;
    UINT8   Ac0FanSpeed;
    UINT8   Ac1FanSpeed;
    UINT8   PassiveThermalTripPoint;
    UINT8   CriticalThermalTripPoint;
    UINT8   PassiveTc1Value;
    UINT8   PassiveTc2Value;
    UINT8   PassiveTspValue;

    UINT8   CPUTempReadEnable;
    UINT8   CPUEnergyReadEnable;
    UINT8   ThermalDeviceEnable;
    UINT8   PchCrossThrottling;
    UINT8   PCHTempReadEnable;
    UINT8   AlertEnableLock;
    UINT8   PchAlert;
    UINT8   DimmAlert;

    UINT8   PchHotLevel;
    UINT8   TPV_Restrict_Enable;

    UINT8   TrEnabled;
    UINT8   TsOnDimm1;
    UINT8   TsOnDimm2;
    UINT8   TsOnDimm3;
    UINT8   TsOnDimm4;
    UINT8   SMBusECMsgLen;
    UINT8   SMBusECMsgPEC;
    // EC turbo control test mode 
    UINT8   ECTurboControlMode;
    UINT8   ACBrickCapacity;
    UINT8   ECPollingPeriod;
    UINT8   ECGuardBandValue;
    UINT8   ECAlgorithmSel;
    UINT8   ECHybridPowerBoost;
    UINT16  ECHybridCurrent;
	UINT8	ECTG;
    // CORE Setup
    UINT8   AspmMode;
    // PchLp LPSS
    UINT8   LpssDmaEnable;
    UINT8   LpssI2c0Enable;
    UINT8   LpssI2c1Enable;
    UINT8   LpssSpi0Enable;
    UINT8   LpssSpi1Enable;
    UINT8   LpssUart0Enable;
    UINT8   LpssUart1Enable;
    UINT8   LpssSdioEnable;
    UINT8   LpssMode;
    UINT8   LpssIntMode;
    UINT8   I2C0VoltageSelect;
    UINT8   I2C1VoltageSelect;
    UINT8   SensorHub;
    UINT8   TPD4;
    UINT8   AtmelTPL;
    UINT8   ElanTPL;
    UINT8   ElanTPD;
    UINT8   SynaTPD;
    UINT8   NtriTPL;
    UINT8   EetiTPL;
    UINT8   AlpsTPD;
    UINT8   CyprTPD;
    UINT8   Bluetooth0;
    UINT8   Bluetooth1;

    UINT16  I2C0SSH;
    UINT16  I2C0SSL;
    UINT16  I2C0SSD;
    UINT16  I2C0FMH;
    UINT16  I2C0FML;
    UINT16  I2C0FMD;
    UINT16  I2C0FPH;
    UINT16  I2C0FPL;
    UINT16  I2C0FPD;
    UINT16  I2C0M0C0;
    UINT16  I2C0M1C0;
    UINT16  I2C0M2C0;

    UINT16  I2C1SSH;
    UINT16  I2C1SSL;
    UINT16  I2C1SSD;
    UINT16  I2C1FMH;
    UINT16  I2C1FML;
    UINT16  I2C1FMD;
    UINT16  I2C1FPH;
    UINT16  I2C1FPL;
    UINT16  I2C1FPD;
    UINT16  I2C1M0C1;
    UINT16  I2C1M1C1;
    UINT16  I2C1M2C1;

    UINT16  SPI0M0C2;
    UINT16  SPI0M1C2;

    UINT16  SPI1M0C3;
    UINT16  SPI1M1C3;

    UINT16  UAR0M0C4;
    UINT16  UAR0M1C4;

    UINT16  UAR1M0C5;
    UINT16  UAR1M1C5;

    // PchLp Audio DSP
    UINT8   ADspEnable;
    UINT8   ADspD3PG;
    UINT8   ADspCodecSelect;
    UINT8   ADspBluetooth;
    UINT8   ADspMode;

    UINT8   NFCE;
} SB_SETUP_DATA;

#pragma pack(pop)

VOID GetSbSetupData (
    IN VOID                 *Service,
    IN OUT SB_SETUP_DATA    *SbSetupData,
    IN BOOLEAN              Pei
);

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
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
