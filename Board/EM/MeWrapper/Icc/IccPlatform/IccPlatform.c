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
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/MeWrapper/Icc/IccPlatform/IccPlatform.c 9     5/14/14 9:56p Tristinchou $
//
// $Revision: 9 $
//
// $Date: 5/14/14 9:56p $
//
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/MeWrapper/Icc/IccPlatform/IccPlatform.c $
// 
// 9     5/14/14 9:56p Tristinchou
// [TAG]  		EIP167030
// [Category]  	Improvement
// [Description]  	Remove the variable runtime attribute and keep original
// attributes.
// 
// 8     4/19/13 4:08a Klzhan
// [TAG]  		EIPNone
// [Category]  	Improvement
// [Description]  	Check DIMM Changed, and update WDT Protocol for XTU
// 
// 7     1/28/13 5:01a Klzhan
// Improvement : System might not power on after changing CPU when
// Overclocking.
// 
// 6     1/14/13 3:15a Klzhan
// 
// 5     12/24/12 6:34a Klzhan
// [TAG]  		EIP109624
// [Category]  	New Feature
// [Description]  	Support Lock Icc registers.
// 
// 4     12/19/12 2:34a Klzhan
// Update for overclocking.
// 
// 3     9/19/12 5:54a Klzhan
// 1. Fix Build Error when Performance is on(IccPlatform.mak).
// 2. Avoid time-out in ICC setup Page when return from Shell.
// 3. Remove un-used wait for Fw Init Done.
// 
// 2     4/24/12 12:28a Klzhan
// 
// 1     2/08/12 1:06a Klzhan
// Initial Check in 
// 
// 5     7/27/11 3:21a Klzhan
// Add Elinks for PCIE and PCI config.
// Note: Don't List GBE port on this Elink.
// 
// 4     7/15/11 12:45a Klzhan
// 
// 3     7/08/11 4:22a Klzhan
// [TAG]  		EIP64189
// [Category]  	Spec Update
// [Severity]  	Important
// [Description]  	Update ME RC to 0.7
// 
// 2     6/27/11 8:39a Klzhan
// Support new ICC control library
// 
// 1     2/25/11 1:42a Klzhan
// Initial Check-in
// 
// 1     12/03/10 5:10a Klzhan
// Initial Check-in.
// 
//
//**********************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:            IccPlatform.c
//
// Description:     Platform-specific ICC code
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>
/*++
Copyright (c)  2009-2010 Intel Corporation. All rights reserved
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.

Module Name:

  IccPlatform.c

Abstract:

  Platform-specific ICC code

--*/
#define __EDKII_GLUE_MEMORY_ALLOCATION_LIB_H__
#define __EDKII_GLUE_BASE_MEMORY_LIB_H__
#if !defined(EDK_RELEASE_VERSION) || (EDK_RELEASE_VERSION < 0x00020000)
#include "EdkIIGlueDxe.h"
#endif
#include EFI_PROTOCOL_PRODUCER(IccOverClocking)
#include EFI_PROTOCOL_PRODUCER(MeBiosPayLoadData)
#ifdef CougarPoint_SUPPORT
#include EFI_PROTOCOL_PRODUCER (Wdt)
#endif
#if EFI_SPECIFICATION_VERSION>0x20000
#define __HII_CONFIG_ACCESS__H__
#else
#include EFI_PROTOCOL_DEFINITION (Hii)
#endif
#include "MeLib.h"
#include "PchAccess.h"
#include "IccSetup.h"
#include "EfiPerf.h"
//
// without these include guards, setup.h would include AMI EFI definitions conflicting with those from EDK
//
#define __UEFI_HII__H__
#define __HII_PROTOCOL_H__
#define _HII_H_
#define __FORM_CALLBACK_PROTOCOL_H__
#include "Setup.h"
#include "IccPlatform.h"
#include "Board\EM\Platform\PlatformSetup.h"
#if WdtPei_SUPPORT
#include "ppi\Wdt\Wdt.h"
#endif
UINT64     mNonce;
EFI_EVENT  mFeedEvent;
ICC_CONFIG mIccConfig;

ICC_OVERCLOCKING_PROTOCOL* gIccOverClockingProtocol;

typedef VOID (ICC_CLOCK_UPDATE) (PLATFORM_PCIE_SLOTS* PCIE_SLOT, PLATFORM_PCI_SLOTS* PCI_SLOT);
extern ICC_CLOCK_UPDATE OEM_CLOCK_UPDATE_FUNC EndOfOemClockUpdateFunc;
ICC_CLOCK_UPDATE* OemClockUpdate[] = {OEM_CLOCK_UPDATE_FUNC NULL};
DXE_MBP_DATA_PROTOCOL           *mBIOSPayLoad;
#if defined PERF_TUNE_SUPPORT && PERF_TUNE_SUPPORT == 1

#define __EFI__H__
#define __HOB__H__
#include <Protocol\PerfTuneProtocol.h>
EFI_GUID gPerfTune3xProtocolGuid           = PERF_TUNE_ASL_PROTOCOL_GUID;
EFI_GUID gPerfTuneDataHobGuid = AMI_PERF_TUNE_DATA_HOB_GUID;
EFI_GUID gHobListGuid         = EFI_HOB_LIST_GUID;
BOOLEAN	 gFound = FALSE;
BOOLEAN	 gBootCurrent = FALSE;
UINT16   gCurrentFrequency;
UINT16   gPEGDMIRatio;
ICC_CLOCK_SETTINGS	  gClocksetting;

//----------------------------CPU Ratio GACI DATA----------------------------
//	   GACI_DATA	DevNameGaciData {					   ControlID,NumberOfValues,Precision,Flags,DefaultDataValue,MinDataValue,MaxDataValue,MinDisplayValue,MaxDisplayValue}
static GACI_DATA	IccFreqGaciData	= {BIOS_HOST_CLOCK_IMPLEMENTATION,		  8001,		2,	  0,		   10000,		10000,		 18000,			10000,			 18000};

static GACI_DATA	IccPegDmiGaciData	= {BIOS_PEG_DMI_RATIO_IMPLEMENTATION,		  0xFFFF,		2,	  0,		   0,		0,		 0,			0,			 0};
#endif

#define ICC_CLOCK_COUNT 8
UINT8   ClockID;
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) > (b) ? (b) : (a))
#ifndef TRACE_ALWAYS
#define TRACE_ALWAYS -1
#endif
typedef struct _CLOCK_DISPLAY_VALUES {
  UINT16 ClkFreqMax;
  UINT16 ClkFreqMin;
  UINT16 ClkFreqCurrent;
  UINT16 SscPercentMax;
  UINT16 SscPercentCurrent;
  UINT16 ClockUsage;
  UINT8  SscChangeAllowed;
  UINT8  SscModeUpAvailable;
  UINT8  SscModeCenterAvailable;
  UINT8  SscModeDownAvailable;
  UINT8  SscModeCurrent;
} CLOCK_DISPLAY_VALUES;

typedef struct _ICC_CLK_REQUEST {
  UINT16 Frequency;
  UINT16 SscPercent;
  UINT8  SscAllowed;
  UINT8  SscMode;
  UINT8  EveryBoot;
} ICC_CLK_REQUEST;

#define IMMEDIATE 0
#define TEMPORARY 1
#define PERMANENT 2

#define SSC_MODE_UP     2
#define SSC_MODE_CENTER 1
#define SSC_MODE_DOWN   0

#if defined PERF_TUNE_SUPPORT && PERF_TUNE_SUPPORT == 1
VOID PerfTuneIcc(
  IN EFI_HANDLE       ImageHandle,
  IN EFI_SYSTEM_TABLE *SystemTable)
{
  VOID	*pPerfTuneDataHobList = NULL;
  PERF_TUNE_DATA_HOB	*pBiosSettingData;
  BIOS_SETTING_DATA  	BiosSettingData;
  UINT16            	RequestFrequency,PEGDMIRatio,bPEGDMIRatio;
  ICC_CLOCK_SETTINGS    RequestSetting;
  EFI_GUID              SetupGuid = SETUP_GUID;
  EFI_STATUS        	Status;
  BOOLEAN               freqConsolidationBypass = TRUE;
  ICC_LIB_STATUS 	IccStatus;
  EFI_PEI_HOB_POINTERS  GuidHob;
  WDT_PROTOCOL *InternalWdtProtocol;
  UINTN				VarSize = sizeof(BIOS_SETTING_DATA);
  BIOS_SETTING_DATA	DefaultData;
  EFI_GUID			EfiSetupGuid = SETUP_GUID;

  //
  // Get Hob list
  //
  Status = EfiLibGetSystemConfigurationTable (&gEfiHobListGuid, &GuidHob.Raw);
  if (EFI_ERROR (Status)) {
    return;
  }

  for (Status = EFI_NOT_FOUND; EFI_ERROR (Status);) {
    if (END_OF_HOB_LIST (GuidHob)) {
      Status = EFI_NOT_FOUND;
      break;
    }
    if (GET_HOB_TYPE (GuidHob) == EFI_HOB_TYPE_GUID_EXTENSION) {
      if (EfiCompareGuid (&gPerfTuneDataHobGuid, &GuidHob.Guid->Name)) {
        Status     = EFI_SUCCESS;
        pBiosSettingData = (PERF_TUNE_DATA_HOB *)(GuidHob.Raw);
        break;
      }
    }
    GuidHob.Raw = GET_NEXT_HOB (GuidHob);
  }

  if (EFI_ERROR(Status)) return;

  if(pBiosSettingData->IsCpuChanged || pBiosSettingData->IsDimmChanged){
	Status = gRT->GetVariable(
					L"OcDefault",
					&EfiSetupGuid,
					NULL,
					&VarSize,
					&DefaultData
					);

	BiosSettingData = pBiosSettingData->PerfTuneDataHob;
  	RequestFrequency = DefaultData.HostClockFreq;
  	PEGDMIRatio = DefaultData.PEGDMIRatio;
  }else{	
  	BiosSettingData = pBiosSettingData->PerfTuneDataHob;
  	RequestFrequency = BiosSettingData.HostClockFreq;
  	PEGDMIRatio = BiosSettingData.PEGDMIRatio;
  }

  if ( (PEGDMIRatio == 100) || (PEGDMIRatio == 0) || (PEGDMIRatio == 0xFFFF)){
	bPEGDMIRatio = 0;
  }else if ( (PEGDMIRatio == 125) || (PEGDMIRatio == 1)){
    bPEGDMIRatio = 1;
  }else if ( (PEGDMIRatio == 167) || (PEGDMIRatio == 2) ){
    bPEGDMIRatio = 2;
  }else if ( (PEGDMIRatio == 250) || (PEGDMIRatio == 3) ){
    bPEGDMIRatio = 3;
  }else{
	bPEGDMIRatio = 0;
  }

  // Return if Overclocking Bclk not found
  if((!gFound) || ((RequestFrequency == gCurrentFrequency) && 
     (bPEGDMIRatio == gPEGDMIRatio) && !(pBiosSettingData->IsCpuChanged || pBiosSettingData->IsDimmChanged)) ) return;

  if (bPEGDMIRatio == gPEGDMIRatio){
    gBootCurrent = FALSE;
    RequestSetting.Frequency  = RequestFrequency * 10000;
    RequestSetting.SscMode    = gClocksetting.SscMode;
    if (bPEGDMIRatio==0){
      RequestSetting.SscPercent = 0x32;
    }else{
      RequestSetting.SscPercent = 0;
    }
  RequestSetting.DmiPegRatio = bPEGDMIRatio;
  gIccOverClockingProtocol->SetCurrentClockSettings(ClockID, 
                                                    RequestSetting,
                                                    &IccStatus);
  gIccOverClockingProtocol->GetCurrentClockSettings
                                    (ClockID, &RequestSetting, &IccStatus);


  RequestFrequency = RequestSetting.Frequency/10000;
  PEGDMIRatio = RequestSetting.DmiPegRatio;
  }else{
    gBootCurrent = TRUE;
    RequestSetting.Frequency  = RequestFrequency * 10000;
    RequestSetting.SscMode    = gClocksetting.SscMode;
    if (bPEGDMIRatio==0){
      RequestSetting.SscPercent = 0x32;
    }else{
      RequestSetting.SscPercent = 0;
    }
  RequestSetting.DmiPegRatio = bPEGDMIRatio;
  gIccOverClockingProtocol->SetBootClockSettings(ClockID, 
                                                    RequestSetting,
                                                    &IccStatus);

  gIccOverClockingProtocol->GetBootClockSettings
                                    (ClockID, &RequestSetting, &IccStatus);


  RequestFrequency = RequestSetting.Frequency/10000;
  PEGDMIRatio = RequestSetting.DmiPegRatio;
  }

  if(IccStatus == ICC_LIB_STATUS_SUCCESS)
  {
      // OverClocking Success
      // ReStore back to OcCurrent
      BiosSettingData.HostClockFreq = RequestFrequency;
      IccFreqGaciData.DefaultDataValue = RequestFrequency;
		  if ( PEGDMIRatio == 0 ){
		  				 BiosSettingData.PEGDMIRatio = 100;
               IccPegDmiGaciData.DefaultDataValue = 100;
          }else if ( PEGDMIRatio == 1 ){
          		 BiosSettingData.PEGDMIRatio = 125;
               IccPegDmiGaciData.DefaultDataValue = 125;
          }else if ( PEGDMIRatio == 2 ){
          		 BiosSettingData.PEGDMIRatio = 167;
               IccPegDmiGaciData.DefaultDataValue = 167;
          }else if ( PEGDMIRatio == 3 ){
          		 BiosSettingData.PEGDMIRatio = 250;
               IccPegDmiGaciData.DefaultDataValue = 250;
          }

      Status = gRT->SetVariable(
                    L"OcCurrent",
                    &SetupGuid,
                    EFI_VARIABLE_NON_VOLATILE |
                    EFI_VARIABLE_BOOTSERVICE_ACCESS,
                    sizeof(BIOS_SETTING_DATA),
                    &BiosSettingData );	
	  ASSERT_EFI_ERROR (Status);
  }

  if (gBootCurrent == TRUE){
	Status = gBS->LocateProtocol(&gWdtProtocolGuid, NULL, &InternalWdtProtocol);
        if(!EFI_ERROR(Status))
        { 
			InternalWdtProtocol->AllowKnownReset();  
		}  
	IoWrite8 (0xCF9,0x06);//Setting REG/DMI ratio have to reset.
	EFI_DEADLOOP();
  }

  return;
}

VOID
IccXtuHandler(
  IN EFI_HANDLE       ImageHandle,
  IN EFI_SYSTEM_TABLE *SystemTable
  )
{
  UINT8              i;
  EFI_STATUS         Status;
  PERF_TUNE_ASL_PROTOCOL *PerfTune3xProtocol;
  UINTN              Len = 0;
  UINT8              *Buffer = NULL;
  EFI_GUID           IccOverClockingProtocolGuid = ICC_OVERCLOCKING_PROTOCOL_GUID;

  Status = gBS->LocateProtocol(&IccOverClockingProtocolGuid, NULL, &gIccOverClockingProtocol);
  if(EFI_ERROR(Status)) return;
  Status = gBS->LocateProtocol(&gPerfTune3xProtocolGuid, NULL, &PerfTune3xProtocol);
  if(EFI_ERROR(Status)) return;

  for(i = 0; i < ICC_CLOCK_COUNT ; i++)
  {
    ICC_LIB_STATUS     IccStatus;
    ICC_CLOCK_RANGES   ClockRange;

    gIccOverClockingProtocol->GetClockRanges(i, &ClockRange, &IccStatus);

    if ( (ClockRange.UsageMask & (1<<ICC_CLOCK_USAGE_BCLK) ) &&
	     (ClockRange.UsageMask & (1<<ICC_CLOCK_USAGE_DMI) ) &&
         (ClockRange.UsageMask & (1<<ICC_CLOCK_USAGE_PEG) ) &&
	     (IccStatus == ICC_LIB_STATUS_SUCCESS)
    ) {
     if (ClockRange.FrequencyMax != ClockRange.FrequencyMin)
          gIccOverClockingProtocol->GetCurrentClockSettings
                                    (i, &gClocksetting, &IccStatus);
          if(IccStatus != ICC_LIB_STATUS_SUCCESS)
              break;


          gCurrentFrequency = gClocksetting.Frequency/10000;

          // Init GACI Data
          IccFreqGaciData.MinDataValue = ClockRange.FrequencyMin/10000;
		  IccFreqGaciData.MinDisplayValue = ClockRange.FrequencyMin/10000;

		  IccFreqGaciData.MaxDataValue = ClockRange.FrequencyMax/10000;
          IccFreqGaciData.MaxDisplayValue = ClockRange.FrequencyMax/10000;
		  
          IccFreqGaciData.DefaultDataValue = gCurrentFrequency;//ClockRange.FrequencyMin/10000;
		  IccFreqGaciData.NumberOfValues = IccFreqGaciData.MaxDataValue - IccFreqGaciData.MinDataValue + 1;
          gFound = TRUE;
          ClockID = i;

          gPEGDMIRatio = gClocksetting.DmiPegRatio;

		  if ( gPEGDMIRatio == 0 ){
               IccPegDmiGaciData.DefaultDataValue = 100;
          }else if ( gPEGDMIRatio == 1 ){
               IccPegDmiGaciData.DefaultDataValue = 125;
          }else if ( gPEGDMIRatio == 2 ){
               IccPegDmiGaciData.DefaultDataValue = 167;
          }else if ( gPEGDMIRatio == 3 ){
               IccPegDmiGaciData.DefaultDataValue = 250;
          }
          break;
    }
  }
  PerfTuneIcc(ImageHandle,SystemTable);
  // reference clock frequency
  Len = sizeof(IccFreqGaciData);
  Status = gBS->AllocatePool(EfiBootServicesData, Len, &Buffer);
  gBS->SetMem(Buffer, Len, 0 );

  gBS->CopyMem(Buffer, &IccFreqGaciData, sizeof(IccFreqGaciData));
  gBS->CopyMem(Buffer + sizeof(IccFreqGaciData), &IccFreqGaciData, sizeof(IccFreqGaciData));
  Status = PerfTune3xProtocol->SetGaciData(Buffer, Len);
  //PEG/DMI Ratio
  Len = sizeof(IccPegDmiGaciData);
  Status = gBS->AllocatePool(EfiBootServicesData, Len, &Buffer);
  gBS->SetMem(Buffer, Len, 0 );

  gBS->CopyMem(Buffer, &IccPegDmiGaciData, sizeof(IccPegDmiGaciData));
  Status = PerfTune3xProtocol->SetGaciData(Buffer, Len);
  return;
}
#endif

EFI_STATUS
IccPlatformEntryPoint (
  IN EFI_HANDLE       ImageHandle,
  IN EFI_SYSTEM_TABLE *SystemTable
  )
{
  EFI_STATUS           Status;
  UINT8                OldProfile;
#ifdef CougarPoint_SUPPORT
  UINT8                WdtStatus = V_PCH_OC_WDT_CTL_STATUS_OK;
  WDT_PROTOCOL         *WdtProtocol;
#endif


  DEBUG ((EFI_D_INFO, "(ICC) Entry Point to ICC_Platform\n"));

  Status = ReadMainSetupData (&mIccConfig);

  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "(ICC) Failed to read setup data! Status = %r\n", Status));
    return Status;
  }
  Status = HeciGetIccProfile (&OldProfile);
  Status = gBS->LocateProtocol(&gMeBiosPayloadDataProtocolGuid, NULL, &mBIOSPayLoad);
  if(EFI_ERROR(Status))
  {
    DEBUG ((EFI_D_ERROR, "(ICC) Get BIOS PayLoad Data Protocol fail !! Status = %r \n", Status));
    mBIOSPayLoad = NULL;
  }
#ifdef CougarPoint_SUPPORT
  Status = gBS->LocateProtocol(&gWdtProtocolGuid, NULL, &WdtProtocol);
  if ( EFI_ERROR(Status) ) {
    DEBUG ((EFI_D_ERROR, "(ICC) Failed to locate Wdt protocol, Status = %r\n",Status));
    return EFI_SUCCESS;
  }
  WdtStatus = WdtProtocol->CheckStatus();
  
  if (mIccConfig.ClocksModified != ICC_SETTINGS_NOT_MODIFIED && WdtStatus == V_PCH_OC_WDT_CTL_STATUS_FAILURE) {
    IccFailureNotification();
  }
#endif

  ASSERT_EFI_ERROR (Status);

  if (mIccConfig.ProfileSelection != OPTION_DISABLED) {
    ProfileSelection(mIccConfig.SelectedIccProfile);
  };

  IccMessages();

#if defined PERF_TUNE_SUPPORT && PERF_TUNE_SUPPORT == 1
  IccXtuHandler(ImageHandle,SystemTable);
#endif
  return EFI_SUCCESS;
}

EFI_STATUS
ClockFailureReport (
  IN EFI_EVENT Event,
  IN VOID      *Context
  )
/*++
Routine Description: 
  Displays error message just below the "press DEL to enter setup" message
  and forces user to enter setup. This is used when BIOS-initiated changes
  to ICC registers caused platform instability and need to be cancelled
Arguments:
  Event - not used
  Context - not used 
Returns: 
  EFI_SUCCESS if everything's OK
--*/
{
  EFI_STATUS    Status;
  EFI_INPUT_KEY Key;
  UINT32        VarAttr;
  UINTN         VarSize;
  UINT32        BootFlow;
  EFI_GUID      guidBootFlow = BOOT_FLOW_VARIABLE_GUID;

  Status        = EFI_SUCCESS;
 
  DEBUG ((EFI_D_INFO, "(ICC) ClockFailureReport\n"));

  gST->ConOut->OutputString (
                gST->ConOut,
                L"Boot attempt failed after platform clock settings were modified by BIOS!\r\n"
                );
  gST->ConOut->OutputString (gST->ConOut, L"Press any key to enter SETUP.\r\n");
  do {
    Status = gBS->CheckEvent (gST->ConIn->WaitForKey);
  } while (Status == EFI_NOT_READY);
  Status    = gST->ConIn->ReadKeyStroke (gST->ConIn, &Key);

  VarAttr = 0;
  VarSize = sizeof(BootFlow);
  Status = gRT->GetVariable(
                    L"BootFlow",
                    &guidBootFlow,
                    &VarAttr,
                    &VarSize,
                    &BootFlow );
  if( EFI_ERROR(Status) )
  {
    VarAttr = EFI_VARIABLE_BOOTSERVICE_ACCESS;
    VarSize = sizeof(BootFlow);
  }

  BootFlow  = BOOT_FLOW_CONDITION_FIRST_BOOT;
  gRT->SetVariable(
        L"BootFlow",
        &guidBootFlow,
        VarAttr,
        VarSize,
        &BootFlow );

  return Status;
}

EFI_STATUS
DetectUsedClocks (
  OUT UINT32*UsedClocks,
  OUT UINT32*AllClocks
  )
/*++
Routine Description: 
  Detects which PCI/PCIE clocks are not needed and can be turned off.
  For PCIE, PCIE bridge is accessed, one of its registers knows if there are cards
  present in slots
  For PCI, this function tries to access PCI devices that would exist if PCI
  cards were put into slots. If such access fails, then slot must be empty and
  its clock can be turned off
Arguments:
  UsedClocks: bitmask for Clock Enable: 1 = enable, 0 = disable
  AllClocks: bitmask for Clock Enable Mask: 1 = Clock Enable bit is valid, 0 = ignore Clock Enable bit
Returns: 
  EFI_SUCCESS in all circumstances except when required protocols can't be located
--*/
{
  UINT32                          i;
  UINT8                           PciQnt;
  UINT8                           PciExpressQnt;
//  UINT32                          BusNumberRegister;
  UINT8                           BusNumber = 0;
  UINT8                           FunctionNumber;
  UINT16                          VendorID;
  UINT16                          SlotStatus;
  UINT32                          Rcba;
  UINT32                          RootPortFunctionNumber = 0;
  UINT8                           SkipPciDetection = 0;
  EFI_STATUS                      Status;
  EFI_GUID                        SetupGuid = SETUP_GUID;
  SETUP_DATA                      SetupData;
  UINTN                           VariableSize;
  PLATFORM_PCIE_SLOTS             PciExpressSlots[] = {PCIE_CLOCK_CONFIG{0,0,0}};
  PLATFORM_PCI_SLOTS              PciSlots[] = {PCI_CLOCK_CONFIG{0,0,0}};
  //
  // all PCI/PCIE-related clocks are turned off by default and only turned on when needed
  // such negative logic covers situation where two or more slots share one clock
  //
  for (i = 0; OemClockUpdate[i] != NULL; i++) 
    OemClockUpdate[i](PciExpressSlots, PciSlots);


  *UsedClocks = 0xFFFFFFFF;
  *AllClocks  = 0x0;

  PciQnt          = (sizeof (PciSlots) / sizeof (PLATFORM_PCI_SLOTS)) - 1;
  PciExpressQnt   = (sizeof (PciExpressSlots) / sizeof (PLATFORM_PCIE_SLOTS)) - 1;

  for (i = 0; i < PciQnt; i++) {
    *UsedClocks &= ~(PciSlots[i].Clock);
    *AllClocks |= PciSlots[i].Clock;
  }
  
  for (i = 0; i < PciExpressQnt; i++) {
    *UsedClocks &= ~(PciExpressSlots[i].Clock);
    *AllClocks |= PciExpressSlots[i].Clock;
  }

  // PCI Express
  //
  //
  // read RootPortFunctionNumber register, it knows (pcie bridge's function number) - to - (physical slot) mapping
  //
  if (PciExpressQnt > 0) {

    Rcba = MmioRead32 (
             MmPciAddress (
               0,
               DEFAULT_PCI_BUS_NUMBER_PCH,
               PCI_DEVICE_NUMBER_PCH_LPC,
               PCI_FUNCTION_NUMBER_PCH_LPC,
               R_PCH_LPC_RCBA
             )
           );

    Rcba &= B_PCH_LPC_RCBA_BAR;
    RootPortFunctionNumber = MmioRead32 ((UINTN) (Rcba + R_PCH_RCRB_RPFN));
  }
  //
  // detect cards in PCIE slots
  //
  for (i = 0; i < PciExpressQnt; i++) {
    FunctionNumber =
      (
        RootPortFunctionNumber >>
        (S_PCH_RCRB_PRFN_RP_FIELD * PciExpressSlots[i].RootPortNumber)
      ) & 0x00000007;


    VendorID = MmioRead16 (
                 MmPciAddress (
                   0,
                   DEFAULT_PCI_BUS_NUMBER_PCH,
                   PCI_DEVICE_NUMBER_PCH_PCIE_ROOT_PORTS,
                   FunctionNumber,
                   R_PCH_PCIE_VENDOR_ID
                 )
               );

    SlotStatus = MmioRead16 (
                   MmPciAddress (
                     0,
                     DEFAULT_PCI_BUS_NUMBER_PCH,
                     PCI_DEVICE_NUMBER_PCH_PCIE_ROOT_PORTS,
                     FunctionNumber,
                     R_PCH_PCIE_SLSTS
                   )
                 );   
//********************************************************************************
	VariableSize = sizeof (SETUP_DATA);
	Status = gRT->GetVariable (
    				L"Setup",
    				&SetupGuid,
    				NULL,
    				&VariableSize,
    				&SetupData
    				); 
	ASSERT_EFI_ERROR (Status);
	
	PciExpressSlots[i].HotPlugSupport = SetupData.PcieRootPortHPE[i];
//*********************************************************************************
    if (PciExpressSlots[i].HotPlugSupport == 1 ||
        (VendorID != 0xFFFF && ((SlotStatus & B_PCH_PCIE_SLSTS_PDS) != 0))
        ) {
      *UsedClocks |= PciExpressSlots[i].Clock;
    }
  }

  DEBUG ((EFI_D_INFO, "(ICC) PCI(E) Clocks Disabled: 0x%08x\n", (*AllClocks & ~(*UsedClocks)) ));
  DEBUG ((EFI_D_INFO, "(ICC) PCI(E) Clocks Enabled:  0x%08x\n", (*AllClocks &   *UsedClocks ) ));
  DEBUG ((EFI_D_INFO, "(ICC) Clocks left alone:      0x%08x\n", ~(*AllClocks) ));
    
  return EFI_SUCCESS;

}

EFI_STATUS
EFIAPI
IccFailureNotification (
  VOID
  )
/*++
Routine Description: 
  This function should only be called if Watchdog timer expiration was detected 
  after BIOS changes ICC settings. Error message is displayed and BIOS setup is entered.
Arguments:
  none
Returns: 
  EFI_SUCCESS if everything's OK
--*/
{
  EFI_EVENT   Event;
  VOID        *EventPointer;
  EFI_GUID    AllDriversConnectedProtocolGuid = BDS_ALL_DRIVERS_CONNECTED_PROTOCOL_GUID;
  EFI_STATUS  Status;

  Status = gBS->CreateEvent (
                  EFI_EVENT_NOTIFY_SIGNAL,
                  EFI_TPL_CALLBACK,
                  ClockFailureReport,
                  NULL,
                  &Event
                  );
  if (!EFI_ERROR (Status)) {
    Status = gBS->RegisterProtocolNotify (
                    &AllDriversConnectedProtocolGuid,
                    Event,
                    &EventPointer
                    );
  }

  DEBUG ((EFI_D_INFO, "(ICC) ClockFailureReport event registration; Status = 0x%02x\n", Status));
  return Status;
}

EFI_STATUS
OnReadyToBoot (
IN EFI_EVENT Event,
IN VOID      *Context
)
{
  EFI_GUID   IccSetupDataGuid = ICC_VOLATILE_SETUP_DATA_GUID;
  UINT8      ReadyToBoot = 1;
  EFI_STATUS Status;

  Status = gRT->SetVariable (
                  L"AfterReadyToBoot",
                  &IccSetupDataGuid,
                  EFI_VARIABLE_BOOTSERVICE_ACCESS,
                  sizeof(UINT8),
                  &ReadyToBoot
                  );

  return EFI_SUCCESS;
}
EFI_STATUS
IccMessages (
  VOID
  )
/*++
Routine Description: 
  Schedules SetClockEnables and LockRegisters Icc heci messages to be executed after PCI enumeration is done
Arguments:
  none
Returns: 
  EFI_SUCCESS if everything's OK
--*/
{
  EFI_EVENT   Event;
  VOID        *EventPointer;
  EFI_GUID    AllDriversConnectedProtocolGuid = BDS_ALL_DRIVERS_CONNECTED_PROTOCOL_GUID;
  EFI_STATUS  Status;
  EFI_EVENT    ReadytoBootEvent;
  EFI_GUID     EfiEventReadyToBootGuid = EFI_EVENT_GROUP_READY_TO_BOOT;

  Status = gBS->CreateEvent (
                  EFI_EVENT_NOTIFY_SIGNAL,
                  EFI_TPL_CALLBACK,
                  SendIccMessages,
                  NULL,
                  &Event
                  );
  if (!EFI_ERROR (Status)) {
    Status = gBS->RegisterProtocolNotify (
                    &AllDriversConnectedProtocolGuid,
                    Event,
                    &EventPointer
                    );
  }

  DEBUG ((EFI_D_INFO, "(ICC) IccMessages event registration; Status = 0x%02x\n", Status));
#if (EFI_SPECIFICATION_VERSION < 0x00020000) 
  gBS->CreateEvent (
                  EFI_EVENT_SIGNAL_READY_TO_BOOT | EFI_EVENT_NOTIFY_SIGNAL_ALL,
                  TPL_CALLBACK,
                  OnReadyToBoot,
                  NULL,
                  &ReadytoBootEvent
                  );
#else
  gBS->CreateEventEx (
                  EFI_EVENT_NOTIFY_SIGNAL,
                  TPL_CALLBACK,
                  OnReadyToBoot,
                  NULL,
                  &EfiEventReadyToBootGuid,
                  &ReadytoBootEvent
                  );
#endif
  return Status;
}


UINT8
ReadIccSoftStraps (
  VOID
  )
/*++
Routine Description: 
  Reads soft straps from flash to check who is responsible for selecting ICC clock profile.
Arguments: 
Returns: 
  PROFILE_SELECTED_BY_BIOS
  PROFILE_SELECTED_BY_ME
--*/
{
  UINT32                          PchRootComplexBar;
  UINT32                          Softstrap10;

  PchRootComplexBar = MmioRead32 (
                 MmPciAddress (
                   0,
                   DEFAULT_PCI_BUS_NUMBER_PCH,
                   PCI_DEVICE_NUMBER_PCH_LPC,
                   PCI_FUNCTION_NUMBER_PCH_LPC,
                   R_PCH_LPC_RCBA
                 ) 
               );

  PchRootComplexBar &= ~BIT0;

  MmioAndThenOr32 (
    PchRootComplexBar + R_PCH_SPI_FDOC,
    (UINT32) (~(B_PCH_SPI_FDOC_FDSS_MASK | B_PCH_SPI_FDOC_FDSI_MASK)),
    (UINT32) (V_PCH_SPI_FDOC_FDSS_PCHS | SOFTSTRAP10)
    );

  Softstrap10 = MmioRead32 (PchRootComplexBar + R_PCH_SPI_FDOD);

  if (Softstrap10 & CLOCK_PROFILE_SELECTOR) {
    return PROFILE_SELECTED_BY_ME;
  }
  return PROFILE_SELECTED_BY_BIOS;
}

EFI_STATUS
ReadMainSetupData (
  OUT ICC_CONFIG* IccConfig
  )
/*++
Routine Description: 
  reads SETUP_DATA and creates IccConfig with all Icc-related setup informations
Arguments: 
Returns: 
  filled SETUP_DATA struct
--*/
{
  EFI_STATUS              Status;
  UINT32                  SetupVarAttr;
  UINTN                   VariableSize;
  UINT32                  Attributes;
  EFI_GUID                SetupGuid = SETUP_GUID;
  EFI_GUID                IccPersistentDataGuid = ICC_PERSISTENT_DATA_GUID;
  SETUP_DATA              SetupData;
  ICC_PERSISTENT_DATA     IccPersistentData;

  DEBUG ((EFI_D_ERROR, "(ICC) ReadMainSetupData\n"));
  
  SetupVarAttr = 0;
  VariableSize = sizeof (SETUP_DATA);

  Status = gRT->GetVariable(
                  L"Setup",
                  &SetupGuid,
                  &SetupVarAttr,
                  &VariableSize,
                  &SetupData );
  if( EFI_ERROR(Status) ) {
    DEBUG ((EFI_D_ERROR, "Failed to read SETUP_DATA!  Status = %r\n", Status));
    return Status;
  }

  VariableSize  = sizeof (ICC_PERSISTENT_DATA);
  
  Status = gRT->GetVariable (
                  L"IccPersistentData",
                  &IccPersistentDataGuid,
                  &Attributes,
                  &VariableSize,
                  &IccPersistentData
                  );
  if (EFI_ERROR (Status)) {
    IccPersistentData.ClocksModified = ICC_SETTINGS_NOT_MODIFIED;
  }

  IccConfig->ClocksModified = IccPersistentData.ClocksModified;

  IccConfig->SelectedIccProfile = SetupData.IccSelectedProfile;

  if (  ReadIccSoftStraps () != PROFILE_SELECTED_BY_BIOS ) {
    IccConfig->ProfileSelection = OPTION_DISABLED;
  } else {
    IccConfig->ProfileSelection = OPTION_ENABLED;
  }

  IccConfig->LockIccRegisters = OPTION_ENABLED;

  //
  // in LockMask, 0 means lock and 1 means don't lock this particular register
  //
  if (SetupData.IccLockRegisters == OPTION_LOCK_STATIC) {
    IccConfig->LockMask[2] = STATIC_REGISTERS_MASK2;
    IccConfig->LockMask[1] = STATIC_REGISTERS_MASK1;
    IccConfig->LockMask[0] = STATIC_REGISTERS_MASK0;
  } else {
    IccConfig->LockMask[2] = 0;
    IccConfig->LockMask[1] = 0;
    IccConfig->LockMask[0] = 0;
  }

  if (SetupData.IccSetClockEnables == OPTION_ENABLED) {
    IccConfig->SetClkEnables = OPTION_ENABLED;
  } else {
    IccConfig->SetClkEnables = OPTION_DISABLED;
  }

  if (IccConfig->ProfileSelection != SetupData.IccDisplayProfile) {
    SetupData.IccDisplayProfile = IccConfig->ProfileSelection;
    Status = gRT->SetVariable(
                    L"Setup",
                    &SetupGuid,
                    SetupVarAttr,
                    sizeof(SETUP_DATA),
                    &SetupData );
  }

  return EFI_SUCCESS;
}

EFI_STATUS
ProfileSelection (
  IN UINT8 NewProfile
  )
/*++
Routine Description: 
  Chooses ICC clock profile to be used by platform for future boots.
Arguments: 
  NewProfile - requested clock profile
Returns: 
  nothing (and the platform reboots) if profile was changed
  EFI_SUCCESS if there was no need to change profile
  other result if HECI communication failed
--*/
{
  EFI_STATUS Status;
  UINT8      OldProfile;

  Status = HeciGetIccProfile (&OldProfile);
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "(ICC) Failed to read clock profile, status = %r.\n", Status));
    return Status;
  }
  
  if (NewProfile != OldProfile) {
    Status = HeciSetIccProfile (NewProfile);
    if (EFI_ERROR (Status)) {
      DEBUG ((EFI_D_ERROR, "(ICC) Failed to change clock profile, status = %r.\n", Status));
      return Status;
    }

    DEBUG ((EFI_D_INFO, "(ICC) Clock Profile was changed, rebooting platform.\n"));
    Status = HeciSendCbmResetRequest(CBM_RR_REQ_ORIGIN_BIOS_POST, CBM_HRR_GLOBAL_RESET);
    if (EFI_ERROR (Status)) {
      DEBUG ((EFI_D_ERROR, "(ICC) Failed to trigger reset, status = %r.\n", Status));
      return Status;
    }
    
    EFI_DEADLOOP();
  }

  return EFI_SUCCESS;
}

EFI_STATUS
WaitForFwInitComplete (
  UINT32 mSeconds
)
/*++
Routine Description: 
  waits for Fw init complete - safety measure to prevent sending Heci messages 
  while FW can't receive them.
Arguments: 
  mSeconds - limit for wait time, in miliseconds
Returns: 
  EFI_SUCCESS if Fw init is complete
  EFI_TIMEOUT if init is still not complete after allocated time
  other errors when something's wrong with Heci protocol 
--*/
{
  EFI_HECI_PROTOCOL *Heci;
  UINT32            MeStatus;
  UINT32            MeMode;
  UINT32            RetryCount;
  EFI_STATUS        Status;
  
  RetryCount = 0;
  
  Status = gBS->LocateProtocol (
                &gEfiHeciProtocolGuid,
                NULL,
                &Heci
                );
                
  if (EFI_ERROR(Status)) {
    DEBUG ((EFI_D_ERROR, "(ICC) Failed to locate Heci protocol! Status = %r\n", Status));
    return Status;
  }
  
  Status = Heci->GetMeMode (&MeMode);
  if (EFI_ERROR (Status) || (MeMode != ME_MODE_NORMAL)) {
    return EFI_UNSUPPORTED;
  }

  PERF_START (0, L"Icc waiting for FwInitComplete", NULL, 0) ;
  while (1) {
    Heci->GetMeStatus (&MeStatus);
    if (ME_STATUS_IS_ME_FW_INIT_COMPLETE (MeStatus)) {
      PERF_END (0, L"Icc waiting for FwInitComplete", NULL, 0) ;
      DEBUG ((EFI_D_INFO, "(ICC) Waited %d ms for FwInitComplete.\n", RetryCount));
      return EFI_SUCCESS;
    }
    if (RetryCount > mSeconds) {
      PERF_END (0, L"Icc waiting for FwInitComplete", NULL, 0) ;
      DEBUG ((EFI_D_ERROR, "(ICC) Time out! Waited %d ms for FwInitComplete.\n", RetryCount));
      return EFI_TIMEOUT;
    }
    RetryCount++;
    gBS->Stall (1000);//1ms
  }
}

EFI_STATUS 
SendIccMessages (
IN EFI_EVENT Event,
IN VOID      *Context
)
/*++
Routine Description: 
  Sends SetClockEnables and LockRegisters Icc Heci messages
Arguments: 
  none
Returns: 
  nothing
--*/
{
  EFI_STATUS Status;
  UINT8      ResponseMode = 1, AccessMode = 0;/*0 - set, 1 - get*/
  ICC_LOCK_REGS_INFO  IccLockRegs;
  EFI_GUID            SetupGuid = SETUP_GUID;
  SETUP_DATA          SetupData;
  UINTN               VariableSize;

  DEBUG ((EFI_D_INFO, "(ICC) Send Icc Heci Messages\n"));

  if (mIccConfig.ProfileSelection != OPTION_DISABLED) {
    ProfileSelection(mIccConfig.SelectedIccProfile);
  };

  VariableSize = sizeof (SETUP_DATA);
  Status = gRT->GetVariable (
                            L"Setup",
                            &SetupGuid,
                            NULL,
                            &VariableSize,
                            &SetupData); 

  ASSERT_EFI_ERROR (Status);

  if (mIccConfig.SetClkEnables == OPTION_ENABLED) {
    DetectUsedClocks (&mIccConfig.ClkEnables, 
                      &mIccConfig.ClkEnablesMask
                     );

    Status = HeciSetIccClockEnables (mIccConfig.ClkEnables, 
                            mIccConfig.ClkEnablesMask, 
                            ResponseMode 
                            );
  }

  if(mBIOSPayLoad)
  {
    gBS->CopyMem(&(IccLockRegs.RegBundles), 
                 &(mBIOSPayLoad->MeBiosPayload.IccProfile.IccLockRegInfo.RegBundles), 
                 sizeof(ICC_REG_BUNDLES));

    gBS->CopyMem((IccLockRegs.RegMask), 
                 (mBIOSPayLoad->MeBiosPayload.IccProfile.IccLockRegInfo.RegMask), 
                 sizeof(UINT32) * IccLockRegs.RegBundles.BundlesCnt);

    VariableSize = sizeof(UINT32) * 3;
    Status = gRT->GetVariable(
                    L"IccLockDefault",
                    &SetupGuid,
                    NULL,
                    &VariableSize,
                    IccLockRegs.RegMask ); 
    if( Status == EFI_NOT_FOUND )
    {
      Status = gRT->SetVariable(
                        L"IccLockDefault",
                        &SetupGuid,
                        EFI_VARIABLE_NON_VOLATILE | 
                        EFI_VARIABLE_BOOTSERVICE_ACCESS,
                        VariableSize,
                        IccLockRegs.RegMask ); 
    }
    if(SetupData.IccLockRegisters == 3)
    {
      IccLockRegs.RegBundles.AU = 0;
      IccLockRegs.RegBundles.BundlesCnt = 3;
    }

    if(SetupData.IccLockRegisters == 4)
    {
      IccLockRegs.RegBundles.BundlesCnt = 0;
      IccLockRegs.RegBundles.AU = 0;
    }
  
    if(SetupData.IccLockRegisters == 5)
    {
      IccLockRegs.RegBundles.BundlesCnt = 0;
      IccLockRegs.RegBundles.AU = 1;
    }

    Status = HeciLockIccRegisters (AccessMode, ResponseMode, &IccLockRegs);

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
