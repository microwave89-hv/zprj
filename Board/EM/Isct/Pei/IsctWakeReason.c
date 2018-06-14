//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
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
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ISCT/IsctPeiWakeReason/IsctWakeReason.c 11    7/16/14 12:22a Mirayang $
//
// $Revision: 11 $
//
// $Date: 7/16/14 12:22a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ISCT/IsctPeiWakeReason/IsctWakeReason.c $
// 
// 11    7/16/14 12:22a Mirayang
// Add complete function with iRST.
// 
// 10    7/11/14 10:27a Mirayang
// iRST bulid error.
// 
// 9     7/08/14 5:07a Mirayang
// EIP 142924  iSCT 5.0 for Shark Bay Platform
// 
// 8     10/29/13 4:21a Joshchou
// [TAG]  		EIP138184
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	Panel will light up when entering into S0-iSCT from
// Rapid-Start-S4(iFFS)
// [RootCause]  	We only judge the boot mode of S3,but it will resume from
// S4 when enable iRST.
// [Solution]  	Add the judgement of S4 resume
// 
// 7     6/02/13 10:54a Joshchou
// [TAG]  		EIP125348
// [Category]  	Improvement
// [Description]  	[SBY] Intel Smart Connect Technology BIOS Sample Code
// 052413 Update
// 
// 6     5/15/13 8:31a Bensonlai
//
// 5     5/14/13 6:28a Bensonlai
// [TAG]  		EIP123328
// [Category]  	Spec Update
// [Severity]  	Normal
// [Description]  	[SBY] Intel Smart Connect Technology 4.x BIOS Reference
// Code
//
// 4     3/27/13 9:19a Bensonlai
// [TAG]  		EIP119288
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	When KB or mouse device plugged in P/S2, USB2.0 ports, it
// showed "PME Wake up event" by tool.
// [Solution]  	Change the USB2.0 wake reason to User pressed power button
// or HID event
// [Files]  		IsctWakeReason.c
//
// 3     1/11/13 5:09a Bensonlai
// [TAG]  		EIP112019
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	[ISCT] The wake up reason is incorrect for PME wake
// [RootCause]  	The PME status be cleared before IsctWakeReason.c.
// [Solution]  	Move the IsctGetWakeReason to gAmiPeiCompleteMRCGuid
// [Files]  		IsctWakeReason.c
//
// 2     9/26/12 2:10a Bensonlai
// [TAG]  		EIPNone
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	System hung up when ISCT enabled on the debug mode
// [RootCause]  	Because we don't check the EFI stauts and use the
// ASSERT_EFI_ERROR directly.
// [Solution]  	Added the EFI stauts for checking.
// [Files]  		IsctAcpi.c, IsctWakeReason.c and IsctWakeReason.c
//
// 1     9/02/12 11:18p Bensonlai
// Intel Smart Connect Technology initially releases.
//
//
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:  IsctWakeReason.c
//
// Description:	Provide Wake Reason for ISCT.
//
//<AMI_FHDR_END>
//**********************************************************************

#if !defined(EDK_RELEASE_VERSION) || (EDK_RELEASE_VERSION < 0x00020000)
#include "EdkIIGluePeim.h"
#endif
#include "PchAccess.h"
//#include "PeiPlatformHookLib.h"
#include "PchPlatformLib.h"
#include "Pci.h"
// ami override Start
//#include "SetupVariable.h"
#include <token.h>
#include <SetupDataDefinition.h>
#if defined (RapidStart_SUPPORT) && (RapidStart_SUPPORT == 1)
#include <Ppi\RapidStart\RapidStart.h>
#endif
#define SYSTEM_CONFIGURATION_GUID { 0xEC87D643, 0xEBA4, 0x4BB5, 0xA1, 0xE5, 0x3F, 0x3E, 0x36, 0xB2, 0x0D, 0xA9 }

#define KSC_D_PORT      0x62
#define KSC_C_PORT      0x66
#define KSC_S_IBF       0x02  /// Input buffer is full/empty
#define KSC_S_OBF       0x01  /// Output buffer is full/empty
#define KSC_TIME_OUT    0x20000

#if !defined(EDK_RELEASE_VERSION) || (EDK_RELEASE_VERSION < 0x00020000)
//
// GUID to AMI_ISCT Module
//

#define AMI_ISCT_HOB_GUID \
  { \
    0x1af7b744, 0xcdfc, 0x4825, 0xa1, 0x77, 0xca, 0x48, 0xd2, 0xdf, 0xe2, 0xc6 \
  }
#else
#define AMI_ISCT_HOB_GUID \
  { \
    0x1af7b744, 0xcdfc, 0x4825, \
    { \
      0xa1, 0x77, 0xca, 0x48, 0xd2, 0xdf, 0xe2, 0xc6 \
    } \
  }
#endif

#pragma pack (1)

typedef struct {
    EFI_HOB_GUID_TYPE EfiHobGuidType;
    UINT16            ISCT_PM1_STS;
    UINT8             WakeReason;
} AMI_ISCT_HOB;

#pragma pack ()
// ami override End

#include EFI_GUID_DEFINITION (IsctPersistentData)
#include EFI_PPI_DEFINITION  (EndOfPeiSignal)
//#include EFI_PPI_DEFINITION  (MemoryDiscovered)

EFI_GUID  gEfiPeiEndOfPeiPhasePpiGuid = EFI_PEI_END_OF_PEI_PHASE_PPI_GUID;


#define KSC_GETWAKE_STATUS    0x35
#define KSC_CLEARWAKE_STATUS  0x36

EFI_STATUS
IsctGetWakeReason (
  IN EFI_PEI_SERVICES           **PeiServices,
  IN EFI_PEI_NOTIFY_DESCRIPTOR  *NotifyDesc,
  IN VOID                       *Ppi
  );

STATIC EFI_PEI_NOTIFY_DESCRIPTOR mIsctGetWakeReasonNotifyDesc = {
  (EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gEfiPeiEndOfPeiPhasePpiGuid,
  IsctGetWakeReason
};




/**
  Checks for a PCIe Network Device attached to the root ports to see if it caused the PME

  @retval   1 An attached PCIe Network device caused a PME.
  @retval   0 No PME caused by network device
**/
UINT8
IsNetworkDevicePME (
  )
/*++

Routine Description:

  Checks for a PCIe Network Device attached to the root ports to see if it caused the PME

Arguments:

  None

Returns:

  UINT8 NetworkWakePME - 1 An attached PCIe Network device caused a PME.
                         0 No PME caused by network device

--*/
{
  UINT8                   NetworkWakePME;
  UINT8                   RpFunction;
  UINTN                   RpBase;
  UINTN                   EpBase;
  UINT8                   CapPtr;
  UINT8                   NxtPtr;
  UINT8                   CapID;
  UINT8                   PMCreg;
  UINT8                   PMCSR;
// ami override Start
  UINT8                   SecBusNum;
// ami override End
  NetworkWakePME = 0;

  //
  // Scan PCH PCI-EX slots (Root Port) : Device 28 Function 0~7
  //
  for (RpFunction = 0; RpFunction < GetPchMaxPciePortNum (); RpFunction ++) {
    RpBase = MmPciAddress (0, DEFAULT_PCI_BUS_NUMBER_PCH, PCI_DEVICE_NUMBER_PCH_PCIE_ROOT_PORTS, RpFunction, 0);
    DEBUG ((EFI_D_INFO, "IsctPei: PCI-EX Root Port: 0x%x ...\n", RpFunction));

    if ((MmioRead16 (RpBase + R_PCH_PCIE_SLSTS) & B_PCH_PCIE_SLSTS_PDS) != 0 && MmioRead16 (RpBase + R_PCH_PCIE_VENDOR_ID) == V_PCH_PCIE_VENDOR_ID) {
// ami override Start
      //
      // Set WLAN PortBus = 1 to Read Endpoint.
      //
//      MmioAndThenOr32(RpBase + R_PCH_PCIE_BNUM, 0xFF0000FF, 0x00010100);
      SecBusNum = (UINT8) (MmioRead32 (RpBase + R_PCH_PCIE_BNUM) >> 8);
//      EpBase = MmPciAddress (0, 1, 0, 0, 0);
      EpBase = MmPciAddress (0, SecBusNum, 0, 0, 0);
// ami override End

      //
      // A config write is required in order for the device to re-capture the Bus number,
      // according to PCI Express Base Specification, 2.2.6.2
      // Write to a read-only register VendorID to not cause any side effects.
      //
      MmioWrite16 (EpBase + R_PCH_PCIE_VENDOR_ID, 0);

      //
      // Check to see if the Device is a Network Device
      //
      if ((MmioRead16 (EpBase + PCI_CLASSCODE_OFFSET + 0x01) & 0xFF00) == (PCI_CLASS_NETWORK << 8)) { //PCI_CLASS_NETWORK_OTHER
        DEBUG ((EFI_D_INFO, "IsctPei: Found a network device on Root Port - 0x%x and device ID is - 0x%x\n", RpFunction, MmioRead16 (EpBase + R_PCH_PCIE_DEVICE_ID)));

        //
        // Find out PMCSR register
        //
        CapPtr = MmioRead8 (EpBase + R_PCH_PCIE_CAPP);
        CapID = MmioRead8 (EpBase + CapPtr);
        NxtPtr = (UINT8) (MmioRead16 (EpBase + CapPtr) >> 8);
        PMCreg = CapPtr;

        while (CapID != 0x01) {
          CapID = MmioRead8 (EpBase + NxtPtr);
          if (CapID == 0x01) {
            PMCreg = NxtPtr;
            break;
          }
          NxtPtr = (UINT8) (MmioRead16 (EpBase + NxtPtr) >> 8);

          if (NxtPtr == 0){
            PMCreg = 0;
            break;
          }
        }

        if (PMCreg != 0) {
          PMCSR = PMCreg + 0x04;

          //
          // Check whether PME enabled. Set NetworkWakePME to 1 if device caused PME.
          //
          if (MmioRead16 (EpBase + PMCSR) & BIT15) {
            NetworkWakePME = 1;
            DEBUG ((EFI_D_INFO, "IsctPei: The network device 0x%x caused the PME\n", MmioRead16 (EpBase + R_PCH_PCIE_DEVICE_ID)));
// ami override Start
            //
            // Restore bus numbers on the WLAN bridge.
            //
//            MmioAnd32(RpBase + R_PCH_PCIE_BNUM, 0xFF0000FF);
// ami override End
            break;
          }
        }
// ami override Start
        //
        // Restore bus numbers on the WLAN bridge.
        //
//        MmioAnd32(RpBase + R_PCH_PCIE_BNUM, 0xFF0000FF);
// ami override End
      }
    }
  }

  return NetworkWakePME;
}

EFI_STATUS
IsctGetWakeReason (
  IN EFI_PEI_SERVICES           **PeiServices,
  IN EFI_PEI_NOTIFY_DESCRIPTOR  *NotifyDesc,
  IN VOID                       *Ppi
  )
/*++

Routine Description:

  Get system Wake Reason and save into CMOS 72/73 for ACPI ASL to use.

Arguments:

  PeiServices       General purpose services available to every PEIM.

Returns:

--*/
{
  EFI_STATUS                  Status;
  UINT32                      PmBase;
  UINT16                      PM1STS;
  UINT16                      USB29VID;
  UINT16                      USB29STS;
  UINT16                      USB26VID;
  UINT16                      USB26STS;
  UINT16                      xHCIVID;
  UINT16                      xHCISTS;
  UINT16                      LanVID;
  UINT16                      LanSTS;
  UINT8                       WakeReason;
  UINT8                       KscStatus;
  UINT8                       WakeStatus;
  UINTN                       Count;
  UINTN                       Size;
  UINT8                       PcieWake;
  ISCT_PERSISTENT_DATA        IsctData;
  PEI_READ_ONLY_VARIABLE_PPI  *ReadOnlyVariable;
  UINT8                       *IsctNvsPtr;
  PCH_SERIES                  PchSeries;
// ami override Start  
  AMI_ISCT_HOB                *AmiIsctHobPtr;
  EFI_GUID                    AmiIsctHobGuid = AMI_ISCT_HOB_GUID;
  EFI_GUID                    gIsctPersistentDataGuid = ISCT_PERSISTENT_DATA_GUID;

#if defined(RapidStart_SUPPORT) && (RapidStart_SUPPORT == 1)
  RAPID_START_PPI                  *RapidStartPpi;
  BOOLEAN                          RapidStartWake;
  EFI_GUID                         gRapidStartPpiGuid = RAPID_START_PPI_GUID;
  //
  // Get Rapid Start wake info
  //  
  RapidStartPpi = NULL;
  RapidStartWake = FALSE;
  Status = PeiServicesLocatePpi (
                  &gRapidStartPpiGuid,
                  0,
                  NULL,
                  (VOID **) &RapidStartPpi
                  );
  if (Status == EFI_SUCCESS) {
    DEBUG ((EFI_D_INFO, "IsctPeiME: RapidStartPpi Found\n"));
    if (RapidStartPpi->GetMode (RapidStartPpi) == RapidStartEntry) {
      DEBUG ((EFI_D_INFO, "IsctPei: RapidStart Transition Wake\n"));
      RapidStartWake = TRUE;
    } else {
      DEBUG ((EFI_D_INFO, "IsctPei: Not RapidStart Transition Wake\n"));
    }
  }
#endif
// ami override End
  
  //
  // Locate PEI Read Only Variable PPI.
  //
  Status = (*PeiServices)->LocatePpi (
                            PeiServices,
                            &gPeiReadOnlyVariablePpiGuid,
                            0,
                            NULL,
                            &ReadOnlyVariable
                            );

  if ( EFI_ERROR(Status) ) {
      return Status;
  }

  Size = sizeof (ISCT_PERSISTENT_DATA);
  Status = ReadOnlyVariable->PeiGetVariable (
                              PeiServices,
                              ISCT_PERSISTENT_DATA_NAME,
                              &gIsctPersistentDataGuid,
                              NULL,
                              &Size,
                              &IsctData
                              );

  if ( EFI_ERROR(Status) ) {
      DEBUG ((EFI_D_INFO, "IsctPei: GetVariable for IsctData Status = %x \n", Status));
      return Status;
  }

  DEBUG ((EFI_D_INFO, "IsctPei: IsctNvsPtr = %x \n", IsctData.IsctNvsPtr));

  //
  // Clear Isct Wake Reason
  //
  DEBUG ((EFI_D_INFO, "IsctPei: Previous Isct Wake Reason = %x \n", *(UINT8 *) IsctData.IsctNvsPtr));
  IsctNvsPtr  = (UINT8 *) IsctData.IsctNvsPtr;
  *IsctNvsPtr = 0;
  WakeReason = 0;
  PcieWake = 0;

  DEBUG ((EFI_D_INFO, "IsctPei: Address for Isct Nvs Region = %x \n", IsctNvsPtr));
  DEBUG ((EFI_D_INFO, "IsctPei: Timer Value saved for RTC timer = %x \n", *(UINT32 *)(IsctData.IsctNvsPtr + 0x8)));

  PchSeries = GetPchSeries();
  //
  // Initialize base address for Power Management
  //
  PmBase = PchLpcPciCfg16 (R_PCH_LPC_ACPI_BASE)  & B_PCH_LPC_ACPI_BASE_BAR;

// ami override Start
  AmiIsctHobPtr = GetFirstGuidHob (&AmiIsctHobGuid);
  if (AmiIsctHobPtr == NULL) {
      DEBUG ((EFI_D_ERROR, "IsctPei: AmiIsctHobPtr not available\n"));
      return  EFI_NOT_FOUND;
  }

//  PM1STS  = IoRead16(PmBase + R_PCH_ACPI_PM1_STS);
  PM1STS = AmiIsctHobPtr->ISCT_PM1_STS;
//ami override End//
  PM1STS &= (B_PCH_ACPI_PM1_STS_PWRBTN | B_PCH_ACPI_PM1_STS_RTC | BIT14);

  //
  // Check PM1_STS
  //
  DEBUG ((EFI_D_INFO, "IsctPei: PM1_STS Value= %x \n", PM1STS));
  DEBUG ((EFI_D_INFO, "  Bit set in PM1_STS: \n"));
  switch (PM1STS){
    case B_PCH_ACPI_PM1_STS_PWRBTN:
      WakeReason |= 0x01; //User event
  DEBUG ((EFI_D_INFO, "    PowerButton\n"));
      break;
    case B_PCH_ACPI_PM1_STS_RTC:
      WakeReason |= 0x04; //RTC Timer
  DEBUG ((EFI_D_INFO, "    RTC Timer\n"));
      break;
    case BIT14: //PCIe Wake
      PcieWake = 1;
      WakeReason |= 0x08; //PME
      DEBUG ((EFI_D_INFO, "    PCIe PME\n"));
      break;
    default:
      WakeReason = 0;
  DEBUG ((EFI_D_INFO, "    Unknown\n"));
      break;
  }
  DEBUG ((EFI_D_INFO, "IsctPei: PCIe Wake: %x\n", PcieWake));

  //
  // EHCI PME : Offset 0x54(15)
  //
  USB29VID = MmioRead16 (
             MmPciAddress (
               0,
               DEFAULT_PCI_BUS_NUMBER_PCH,
               PCI_DEVICE_NUMBER_PCH_USB,
               PCI_FUNCTION_NUMBER_PCH_EHCI,
               R_PCH_USB_VENDOR_ID
               ));

  USB29STS = MmioRead16 (
             MmPciAddress (
               0,
               DEFAULT_PCI_BUS_NUMBER_PCH,
               PCI_DEVICE_NUMBER_PCH_USB,
               PCI_FUNCTION_NUMBER_PCH_EHCI,
               R_PCH_EHCI_PWR_CNTL_STS
               )) & (B_PCH_EHCI_PWR_CNTL_STS_PME_STS | B_PCH_EHCI_PWR_CNTL_STS_PME_EN);

  if (USB29VID != 0xFFFF && USB29VID != 0){
    if (USB29STS == 0x8100){
      DEBUG ((EFI_D_INFO, "IsctPei: EHCI Wake\n"));
      WakeReason |= 0x01; //User event
    }
  }

  if (PchSeries == PchH) {
    USB26VID = MmioRead16 (
                 MmPciAddress (
                   0,
                   DEFAULT_PCI_BUS_NUMBER_PCH,
                   PCI_DEVICE_NUMBER_PCH_USB_EXT,
                   PCI_FUNCTION_NUMBER_PCH_EHCI,
                   R_PCH_USB_VENDOR_ID
                 ));

    USB26STS = MmioRead16 (
                 MmPciAddress (
                   0,
                   DEFAULT_PCI_BUS_NUMBER_PCH,
                   PCI_DEVICE_NUMBER_PCH_USB_EXT,
                   PCI_FUNCTION_NUMBER_PCH_EHCI,
                   R_PCH_EHCI_PWR_CNTL_STS
                 )) & (B_PCH_EHCI_PWR_CNTL_STS_PME_STS | B_PCH_EHCI_PWR_CNTL_STS_PME_EN);

    if (USB26VID != 0xFFFF && USB26VID != 0){
      if (USB26STS == 0x8100){
        DEBUG ((EFI_D_INFO, "IsctPei: EHCI Wake\n"));
        WakeReason |= 0x01; //User Event
      }
    }
  }

  //
  // Intel GigaLAN PME : Offset 0xCC(15)
  //
  LanVID = MmioRead16 (
           MmPciAddress (
             0,
             PCI_BUS_NUMBER_PCH_LAN,
             PCI_DEVICE_NUMBER_PCH_LAN,
             PCI_FUNCTION_NUMBER_PCH_LAN,
             R_PCH_LAN_VENDOR_ID
             ));

  LanSTS = MmioRead16 (
           MmPciAddress (
             0,
             PCI_BUS_NUMBER_PCH_LAN,
             PCI_DEVICE_NUMBER_PCH_LAN,
             PCI_FUNCTION_NUMBER_PCH_LAN,
             R_PCH_LAN_PMCS
             )) & (B_PCH_LAN_PMCS_PMES | B_PCH_LAN_PMCS_PMEE);


  if (LanVID != 0xFFFF && LanVID != 0){
     if (LanSTS == 0x8100){
        DEBUG ((EFI_D_INFO, "IsctPei: LAN PME Wake\n"));
        WakeReason |= 0x08; //PME
     }
  }

  //
  // xHCI PME : Offset 0x74(15)
  //
  xHCIVID = MmioRead16 (
           MmPciAddress (
             0,
             DEFAULT_PCI_BUS_NUMBER_PCH,
             PCI_DEVICE_NUMBER_PCH_XHCI,
             PCI_FUNCTION_NUMBER_PCH_XHCI,
             R_PCH_USB_VENDOR_ID
             ));

  xHCISTS = MmioRead16 (
           MmPciAddress (
             0,
             DEFAULT_PCI_BUS_NUMBER_PCH,
             PCI_DEVICE_NUMBER_PCH_XHCI,
             PCI_FUNCTION_NUMBER_PCH_XHCI,
             R_PCH_XHCI_PWR_CNTL_STS
             )) & (B_PCH_XHCI_PWR_CNTL_STS_PME_STS | B_PCH_XHCI_PWR_CNTL_STS_PME_EN);


  if (xHCIVID != 0xFFFF && xHCIVID != 0){
     if (xHCISTS == 0x8100){
        DEBUG ((EFI_D_INFO, "IsctPei: xHCI Wake\n"));
        WakeReason |= 0x08; //PME
     }
  }

  //
  // Check if IsctTimerChoice is set to EC timer
  //
  if (*(UINT8 *)((UINTN)(IsctData.IsctNvsPtr + 0x3)) == 0) {
    DEBUG ((EFI_D_INFO, "IsctPei: EC timer is being used\n"));
    //
    // Check KSC Input Buffer
    //
    Count     = 0;
    KscStatus = IoRead8 (KSC_C_PORT);

    while (((KscStatus & KSC_S_IBF) != 0) && (Count < KSC_TIME_OUT)) {
      KscStatus = IoRead8 (KSC_C_PORT);
      Count++;
    }

    //
    // Send EC GetWakeStatus command
    //
    IoWrite8(KSC_C_PORT, KSC_GETWAKE_STATUS);

    //
    // Check KSC Output Buffer
    //
    Count     = 0;
    KscStatus = IoRead8 (KSC_C_PORT);

    while (((KscStatus & KSC_S_OBF) == 0) && (Count < KSC_TIME_OUT)) {
      KscStatus = IoRead8 (KSC_C_PORT);
      Count++;
    }

    //
    // Receive wake reason
    //
    WakeStatus = IoRead8 (KSC_D_PORT);

    //
    // Check KSC Input Buffer
    //
    Count     = 0;
    KscStatus = IoRead8 (KSC_C_PORT);

    while (((KscStatus & KSC_S_IBF) != 0) && (Count < KSC_TIME_OUT)) {
      KscStatus = IoRead8 (KSC_C_PORT);
      Count++;
    }

    //
    // Send EC ClearWakeStatus command
    //
    IoWrite8(KSC_C_PORT, KSC_CLEARWAKE_STATUS);
    DEBUG ((EFI_D_INFO, "IsctPei: EC Wake Status: %x\n", WakeStatus));
    switch (WakeStatus){
      case BIT1:  // Lid Wake
        WakeReason |= 0x01; //Bit0 is user event wake
        break;
      case BIT2:  // Keyboard/Mouse Wake
        WakeReason |= 0x01; //Bit0 is user event wake
        break;
      case BIT3: // EC Timer Wake
        WakeReason |= 0x02; //Bit1 is EC timer wake
        break;
      case BIT4: // PCIe Wake
        WakeReason |= 0x08; //Wake due to PME
        break;
      default: // Unknown
        WakeReason |= 0x00;
        break;
    }
    //
    // Override because of EC timer wake from FFS_S3 or S4 (Need EC support it!)
    //
    if ((PM1STS == B_PCH_ACPI_PM1_STS_PWRBTN) && (WakeStatus == BIT3)) {
      WakeReason = 0x02;
    }
  }

// ami override Start
#if defined(RapidStart_SUPPORT) && (RapidStart_SUPPORT == 1)
    DEBUG ((EFI_D_INFO, "IsctPei: IsctData.IsctOverWrite : %d \n",IsctData.IsctOverWrite));
                                                                  
    DEBUG ((EFI_D_INFO, "IsctPei: RapidStartWake : %d \n",RapidStartWake));
    
    if ((WakeReason & 0x04) == 0x04) {
      if ((RapidStartWake == FALSE) && (IsctData.IsctOverWrite == TRUE)) {
        DEBUG ((EFI_D_INFO, "IsctPei: RapidStartWake == FALSE && IsctData.IsctOverWrite == TRUE. \n"));
        WakeReason |= 0x0002;
        WakeReason &= ~0x04;
      }
    }
#else
  //
  //If RTC wake, check if IsctOverWrite is set to OS
  //
  if (WakeReason == 0x04) {
    if ((IsctData.IsctOverWrite)) == 0) {
      WakeReason = 0x04;
    } else {
      WakeReason = 0x02;
    }
  }
#endif
// ami override End

  //
  // Check for Network Device PME from PCIe if PME wake reason
  //
  if(PcieWake == 1) //PME
  {
    DEBUG ((EFI_D_INFO, "IsctPei: PME wake reason- check if from network device\n"));
    if(IsNetworkDevicePME())
    {
      WakeReason |= BIT4;
      DEBUG ((EFI_D_INFO, "IsctPei: IsNetworkDevicePME() returned Yes\n"));
    }
  }

  //
  // Set Isct Wake Reason
  //
  DEBUG ((EFI_D_INFO, "IsctPei: Wake Reason reported to Agent= %x \n", WakeReason));
  *(UINT8 *)IsctData.IsctNvsPtr = WakeReason;
  AmiIsctHobPtr->WakeReason = WakeReason;
  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
IsctPeiEntryPoint (
    IN  EFI_FFS_FILE_HEADER  *FfsHeader,
    IN  EFI_PEI_SERVICES     **PeiServices
  )
/*++

Routine Description:

  Set up

Arguments:

  PeiServices       General purpose services available to every PEIM.

Returns:

--*/
{
  EFI_STATUS                      Status;
  UINT8                           IsctEnabled;
  EFI_GUID SetupGuid = SYSTEM_CONFIGURATION_GUID;
  PEI_READ_ONLY_VARIABLE_PPI      *ReadOnlyVariable;
  SETUP_DATA                      SetupData;
  UINTN                           VariableSize;
// ami override Start

  EFI_BOOT_MODE                   BootMode;
  AMI_ISCT_HOB                    *AmiIsctHobPtr;
  EFI_GUID                        AmiIsctHobGuid = AMI_ISCT_HOB_GUID;
  UINT32                          PmBase;

  DEBUG ((EFI_D_ERROR, "IsctPei Entry Point\n"));
  IsctEnabled = 0;

  //
  // Locate PEI Read Only Variable PPI.
  //
  Status = (**PeiServices).LocatePpi (
                              PeiServices,
                              &gPeiReadOnlyVariablePpiGuid,
                              0,
                              NULL,
                              &ReadOnlyVariable
                              );
  if ( EFI_ERROR(Status) ) {
      DEBUG ((EFI_D_ERROR, "IsctPei: LocatePpi is fail\n"));
      return Status;
  }

  //
  // Get Setup Variable
  //
  VariableSize = sizeof (SETUP_DATA);
  Status = ReadOnlyVariable->PeiGetVariable (
                              PeiServices,
                              L"Setup",
                              &SetupGuid,
                              NULL,
                              &VariableSize,
                              &SetupData
                              );
  if ( EFI_ERROR(Status) ) {
      DEBUG ((EFI_D_ERROR, "IsctPei: Setup is fail\n"));
      return Status;
  }

  IsctEnabled = SetupData.IsctConfiguration;

  if (IsctEnabled == 0) {
    DEBUG ((EFI_D_INFO, "Isct Disabled\n"));
    return EFI_SUCCESS;
  }
  else {
// ami override Start
    Status = PeiServicesGetBootMode (&BootMode);
    if ( EFI_ERROR( Status ) ) {
        DEBUG ((EFI_D_ERROR, "IsctPei: Get Boot Mode is fail\n"));
        return   Status;
    }


        Status = (*PeiServices)->CreateHob (PeiServices, EFI_HOB_TYPE_GUID_EXTENSION, sizeof (AMI_ISCT_HOB), (VOID **) &AmiIsctHobPtr);
        if ( EFI_ERROR( Status ) ) {
            DEBUG ((EFI_D_ERROR, "IsctPei: CreateHob is fail for AmiIsctHobPtr\n"));
            return   Status;
        }

        //
        // Initialize base address for Power Management
        //
        PmBase = PchLpcPciCfg16 (R_PCH_LPC_ACPI_BASE)  & B_PCH_LPC_ACPI_BASE_BAR;

        AmiIsctHobPtr->EfiHobGuidType.Name = AmiIsctHobGuid;
        AmiIsctHobPtr->ISCT_PM1_STS = IoRead16(PmBase + R_PCH_ACPI_PM1_STS);
        DEBUG ((EFI_D_ERROR, "IsctPei: AmiIsctHobPtr->ISCT_PM1_STS = %x \n", AmiIsctHobPtr->ISCT_PM1_STS));

        
     //
      // Get Rapid Start wake info
      //
    if ( (BootMode == BOOT_ON_S3_RESUME) || (BootMode == BOOT_ON_S4_RESUME) ) {
              
        Status = PeiServicesNotifyPpi (&mIsctGetWakeReasonNotifyDesc);
        if ( EFI_ERROR(Status) ) {
           DEBUG ((EFI_D_INFO, "IsctPei: Notify  EFI_PEI_END_OF_PEI_PHASE_PPI_GUID Status = %x \n", Status));
           return Status;
        }

        return   Status;
    }
// ami override end 
  }

  return EFI_SUCCESS;
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
