//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
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
// $Header: /Alaska/SOURCE/Modules/Intel Fast Flash Standby/iRST_SharkBay/RapidStartWrapper/RapidStartPeiLib/RapidStartPeiLib.c 5     7/15/13 6:32a Joshchou $
//
// $Revision: 5 $
//
// $Date: 7/15/13 6:32a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/Intel Fast Flash Standby/iRST_SharkBay/RapidStartWrapper/RapidStartPeiLib/RapidStartPeiLib.c $
// 
// 5     7/15/13 6:32a Joshchou
// [TAG]  		EIP129090
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	Platform automatically wakes itself after entering S4 when
// doing Rapid Start flow
// [RootCause]  	The Update of PCH RC 1.6.0 in PchSmmSx.c will put XHCI
// into incorrect state on ULT platfrom.
// [Solution]  	Added code in the Rapid Start Entry phase, to put XHCI
// into the correct state i.e. D3 to fix the auto wake-up issue.
// 
// 4     6/21/13 6:03a Joshchou
// [TAG]  		EIP126792
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	Can't do AMI capsule when Intel Rapid Start eanble
// [RootCause]  	CMOS RapidStartFlag does not clear.
// [Solution]  	Clear RapidStartFlag when cold boot.
// 
// 3     3/14/13 11:41p Bensonlai
// [TAG]  		EIP118122
// [Category]  	Spec Update
// [Severity]  	Normal
// [Description]  	[SBY] Intel Rapid Start Technology Framework Reference
// Code Production Version 1.3.0
// [Files]  		RapidStartPeiLib.c
// 
// 2     12/18/12 12:19a Bensonlai
// [TAG]  		EIP109701
// [Category]  	Spec Update
// [Severity]  	Normal
// [Description]  	Updated to Shark Bay Rapid Start Reference Code
// Version 0.8.1
// [Files]  		RapidStartPeiLib.c, RapidStartPeiLib.h
// 
// 1     10/15/12 4:41a Bensonlai
// [TAG]  		EIPNone
// [Category]  	Improvement
// [Description]  	[Category] Improvement
// [Severity] Important
// [Description] Rename all IFFS sting to Rapid Start.
// [Files] Board\EM\RapidStartWrapper\*.*, ReferenceCode\RapidStart\*.*
// [Files]  		RapidStartPeiLib.cif
// RapidStartPeiLib.sdl
// RapidStartPeiLib.mak
// RapidStartPeiLib.c
// RapidStartPeiLib.h
// RapidStartPeiLib.inf
// RapidStartPeiLib.lib
// PeiCryptLib.lib
// OpensslLib.lib
//
//**********************************************************************
//<AMI_FHDR_START>
//
// Name: RapidStartPeiLib.c
//
// Description: RapidStart Platform PEI library.
//
//<AMI_FHDR_END>
//**********************************************************************

#if !defined(EDK_RELEASE_VERSION) || (EDK_RELEASE_VERSION < 0x00020000)
#include "EdkIIGluePeim.h"
#include "RapidStartConfig.h"
#include "RapidStartPeiLib.h"
#include "RapidStartCommonLib.h"
#include <SaAccess.h>
#include <PchRegs.h>
#include <PchPlatformLib.h>
#endif
#ifndef SW_SMI_IO_ADDRESS
#define SW_SMI_IO_ADDRESS 0xB2
#endif

#ifndef SW_SMI_ACPI_ENABLE
#define SW_SMI_ACPI_ENABLE  0xA0
#endif

//AMI_OVERRIDE_FOR_RAPID_START
#ifndef FFS_NV_CONFIG_REG
#define FFS_NV_CONFIG_REG 0x47
#endif
//AMI_OVERRIDE_FOR_RAPID_START

#define HDD_PWD_ENCRYPTION_KEY      "H?p1mA*k920_84o3d^!z@L.x4$kY64"

#pragma pack(1)
typedef struct _HDDSECDATA
{
    UINT16 UserMaster;
    UINT32 PasswordLength;
    UINT8  HddUserPassword[ATA_PASSWORD_LEN];
    UINT8  HddMasterPassword[ATA_PASSWORD_LEN];
} HDDSECDATA;
#pragma pack()

#define DEFAULT_PCI_BUS_NUMBER_PCH  0
#define PCI_DEVICE_NUMBER_PCH_SATA          31
#define PCI_FUNCTION_NUMBER_PCH_SATA        2

#define IDE_SECURITY_PWNV_GUID \
{ 0x69967a8c, 0x1159, 0x4522, 0xaa, 0x89, 0x74, 0xcd, 0xc6, 0xe5, 0x99, 0xa0}

/**
  Enables ACPI mode after RapidStart resume.

  @param[in] PeiServices   - Pointer to PEI Services Table.

  @retval EFI_SUCCESS   - enabled ACPI mode
**/
EFI_STATUS
RapidStartEnableAcpi (
  IN      EFI_PEI_SERVICES          **PeiServices
  )
{
#ifdef RAPID_START_WHOLE_MEMORY_CHECK
  DEBUG ((EFI_D_INFO, "[RapidStart] SMI port=%X, RapidStart SWSMI cmd=%X\n", SW_SMI_IO_ADDRESS, SW_SMI_WHOLE_MEMORY_CHECK));
  IoWrite8 (SW_SMI_IO_ADDRESS, SW_SMI_WHOLE_MEMORY_CHECK);
#endif
  DEBUG ((EFI_D_INFO, "[RapidStart] SMI port=%X, ACPI_ENABLE cmd=%X\n", SW_SMI_IO_ADDRESS, SW_SMI_ACPI_ENABLE));
  IoWrite8 (SW_SMI_IO_ADDRESS, SW_SMI_ACPI_ENABLE);
  return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   ConvertHddDataIdToString
//
// Description: Converts Integer HDD Data Id to String.
//
// Input:
//           IN  UINT32          DataId,
//           OUT CHAR16          *String
// Output:
//	        None
//
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID ConvertHddDataIdToString(
    IN UINT32  DataId,
    OUT CHAR16 *String )
{
    UINTN Num, i;
    Num = EfiValueToString (String, DataId, 0, 0);

      for ( i = 0; i < Num; i++ )
      {
          DEBUG((EFI_D_ERROR, "HDD Passowrd: String[%x] = %x. \n", i,  String[i]));
      }

    return;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	EncodeDecodePassword
//
// Description:	Encodes/Decodes Password.
//
// Input:
//           IN   UINT8        *InputString,
//           OUT  UINT8        *OutputString,
//           IN   UINT32       StringLen
// Output:
//          None
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID EncodeDecodePassword(
  IN      EFI_PEI_SERVICES          **PeiServices,
  IN      UINT8                     *InputString,
  OUT     UINT8                     *OutputString,
  IN      UINT32                    StringLength )
{
    UINT8  *Key;
    UINT32 i;
    UINT32 KeyIndex;
    UINT32 KeyLength;

    if ((InputString == NULL) || (StringLength == 0))
    {
        return;
    }

    KeyLength = (UINT32)(EfiAsciiStrLen( HDD_PWD_ENCRYPTION_KEY));

    Key = AllocateZeroPool (KeyLength);
    CopyMem ((VOID *) Key, (VOID *) HDD_PWD_ENCRYPTION_KEY, (UINTN) KeyLength);
    ASSERT (Key != NULL);

    for ( i = 0, KeyIndex = 0; i < StringLength; i++, KeyIndex++ )
    {
        if ( KeyIndex == (KeyLength - 1))
        {
            KeyIndex = 0;
        }
        OutputString[i] = (UINT8) ( InputString[i] ^ Key[KeyIndex] );
    }

    return;
}

/**
  This callback is provided to support drive password locking interoperability with RapidStart.
  It is called before RapidStart transition is to occur. If SSD partiotion is located on password
  locked drive this function must copy the password to the output buffer.
  Size of the buffer equals ATA_PASSWORD_LEN.

  Normally the drive password is kept in SMRAM so it can be used to unlock the drive at S3 resume,
  thus during RapidStartEntry the password from SMRAM shall be returned. However at RapidStartExit the content
  of SMRAM is not yet available so the password has to be preserved in a non-volatile memory
  during RapidStartEntry (in RapidStartAfterTransition callback) and retrieved by this function.

  For security reasons the password must be scrubbed from non-volatile memory on RapidStartExit before
  returning from this function. On RapidStartEntry the password must not be stored to non-volatile memory
  sooner than RapidStartAfterTransition is called (that is after RapidStart non-volatile flag is set).

  @param[in] PeiServices   - Pointer to PEI Services Table
  @param[in] Transition    - RapidStart transition being performed
  @param[in] SataPort      - locked SATA port
  @param[out] Password     - output buffer to place the password in
  @param[out] FreezeLock   - set to TRUE to freeze drive lock, set to FALSE otherwise

  @retval EFI_SUCCESS   - Unlock password copied to the buffer
  @retval EFI_NOT_FOUND - No password provided (will break the transition)
**/
EFI_STATUS
RapidStartGetDriveUnlockPassword (
  IN      EFI_PEI_SERVICES          **PeiServices,
  IN      RAPID_START_TRANSITION    Transition,
  IN      UINT8                     SataPort,
  OUT     UINT8                     *Password,
  OUT     BOOLEAN                   *FreezeLock
  )
{
  EFI_STATUS                      Status;
  EFI_PEI_READ_ONLY_VARIABLE_PPI  *ReadOnlyVariable;
  UINT16                          wBDF;
  UINT16                          wPortPMModeFlag;
  UINT8                           DeviceorPMPort = 0xff;
  BOOLEAN                         ModeFlag = TRUE; //TRUE is AHCI mode, FALSE is IDE mode.
  UINT32                          HddDataId;
  CHAR16                          *HddSecutiyData = NULL;
  UINTN                           HddSecDataSize = sizeof (HDDSECDATA);
  HDDSECDATA                      *HddSecData;
  UINT16                          Control;
  UINTN                           i;
  UINT8                           CryptBuffer[ATA_PASSWORD_LEN];
  EFI_GUID                        gIdeSecurityPwNvguid = IDE_SECURITY_PWNV_GUID;

  Status = PeiServicesLocatePpi (&gEfiPeiReadOnlyVariablePpiGuid, 0, NULL, &ReadOnlyVariable);
  ASSERT_EFI_ERROR (Status);

  wBDF            = (UINT16)((DEFAULT_PCI_BUS_NUMBER_PCH << 8) \
                             | (PCI_DEVICE_NUMBER_PCH_SATA << 3) \
                             | PCI_FUNCTION_NUMBER_PCH_SATA );
  wPortPMModeFlag = (UINT16)((SataPort << 12)   \
                             | (DeviceorPMPort << 4)   \
                             | ((UINT8)ModeFlag));

  HddDataId = (UINT32)(((UINT16)wBDF << 16) + ((UINT16)wPortPMModeFlag));
  DEBUG ((EFI_D_ERROR, "[RapidStart] HddDataId=%X\n", HddDataId));

  HddSecutiyData = AllocateZeroPool(ATA_PASSWORD_LEN);

  ConvertHddDataIdToString (HddDataId, HddSecutiyData);

  HddSecData = AllocateZeroPool(HddSecDataSize);

  Status = ReadOnlyVariable->PeiGetVariable (
                              GetPeiServicesTablePointer (),
                              HddSecutiyData,
                              &gIdeSecurityPwNvguid,
                              NULL,
                              &HddSecDataSize,
                              HddSecData
                              );
  DEBUG ((EFI_D_ERROR, "[RapidStart] PeiGetVariable Status=%r\n", Status));
  if (EFI_ERROR (Status)) {
    return EFI_NOT_FOUND;
  }

  Control = HddSecData->UserMaster;

  DEBUG ((EFI_D_ERROR, "[RapidStart] Control=%x\n", Control));

  if ( Control & 0x01 )
  {
      for ( i = 0; i < sizeof (HddSecData->HddMasterPassword); i++ )
      {
          CryptBuffer[i] = HddSecData->HddMasterPassword[i];
      }

      EncodeDecodePassword (PeiServices, CryptBuffer, Password, HddSecData->PasswordLength);
  }
  else {
      for ( i = 0; i < sizeof (HddSecData->HddUserPassword); i++ )
      {
          DEBUG ((EFI_D_ERROR, "[RapidStart] HddSecData->HddUserPassword[%x]= %x.\n", i, HddSecData->HddUserPassword[i]));
          CryptBuffer[i] = HddSecData->HddUserPassword[i];
      }

      EncodeDecodePassword (PeiServices, CryptBuffer, Password, HddSecData->PasswordLength);
  }

  *FreezeLock = TRUE;

  return EFI_SUCCESS;
}

/**
  This callback is executed before RapidStart transition is performed, but after RapidStart transition conditions has been met.

  @param[in] PeiServices   - Pointer to PEI Services Table
  @param[in] Transition    - RapidStart transition being performed
  @param[in] SataPort      - SATA port of RapidStart storage drive

  @retval EFI_SUCCESS   - RapidStart transition will follow
  @retval EFI_ABORTED   - RapidStart transition will not be performed
**/
EFI_STATUS
RapidStartBeforeTransition (
  IN      EFI_PEI_SERVICES          **PeiServices,
  IN      RAPID_START_TRANSITION    Transition,
  IN      UINT8                     SataPort
  )
{
  return EFI_SUCCESS;
}

/**
  This callback is executed at the end of RapidStart transition whether succesfull ot not.

  If RapidStart partition is located on password locked drive the drive password must be
  copied to non-volatile memory during RapidStartEntry in this function, so it is available
  on RapidStartExit (see RapidStartGetDriveUnlockPassword).

  @param[in] PeiServices      - Pointer to PEI Services Table
  @param[in] Transition       - RapidStart transition being performed
  @param[in] TransitionStatus - Status of the RapidStart transition
  @param[in] SataPort         - SATA port of RapidStart storage drive
**/
VOID
RapidStartAfterTransition (
  IN      EFI_PEI_SERVICES          **PeiServices,
  IN      RAPID_START_TRANSITION    Transition,
  IN      EFI_STATUS                TransitionStatus,
  IN      UINT8                     SataPort
  )
{
  //AMI_OVERRIDE_FOR_RAPID_START
  //Clear CMOS RapidStartFlag in PEI
  RtcWrite (FFS_NV_CONFIG_REG, 0);
  //AMI_OVERRIDE_FOR_RAPID_START
}

#ifndef RAPID_START_NO_SMRAM_INTEGRITY_CHECK
/**
  Saves SMRAM Secure Hash to non-volatile secure location.

  @param[in] Hash[]   - hash value

  @retval EFI_SUCCESS   - Hash value saved successfully
  @retval EFI_NOT_FOUND - Hash value not found
**/
EFI_STATUS
RapidStartSaveSecureHash (
  IN  UINT8 Hash[RAPID_START_SECURE_HASH_LENGTH]
  )
{
  UINT8 Index;

  DEBUG ((EFI_D_ERROR, "RapidStartSaveSecureHash()\n"));

  for (Index = 0; Index < RAPID_START_SECURE_HASH_LENGTH; Index++) {
    // Save SMRAM hash value
    RtcWrite (FFS_SMRAM_HASH_DATA_REG + Index, Hash[Index]);
  }

  return EFI_SUCCESS;
}

/**
  Retrieves and removes SMRAM hash from non-volatile memory

  @param[out] Hash[]   - hash value

  @retval EFI_SUCCESS   - Hash value has been restored and cleared successfully
  @retval EFI_NOT_FOUND - Hash value not found
**/
EFI_STATUS
RapidStartRestoreAndClearSecureHash (
  OUT UINT8 Hash[RAPID_START_SECURE_HASH_LENGTH]
  )
{
  UINT8 Index;

  DEBUG ((EFI_D_ERROR, "RapidStartRestoreAndClearSecureHash()\n"));

  for (Index = 0; Index < RAPID_START_SECURE_HASH_LENGTH; Index++) {
    // Retrieve SMRAM hash value
    Hash[Index] = RtcRead (FFS_SMRAM_HASH_DATA_REG + Index);
    // Remove SMRAM value
    RtcWrite (FFS_SMRAM_HASH_DATA_REG + Index, 0);
  }
  return EFI_SUCCESS;
}

#endif

/**
  Provide a hook for OEM to cancel RapidStart flow.
  This function may impact RapidStart Entry performance since it's polled frequently.

  @retval FALSE     - Do not cancel RapidStart flow
  @retval TRUE      - The RapidStart Entry flow should be canceled and do S3 resume back to OS
**/
BOOLEAN
RapidStartShouldCancelEntry (
  VOID
  )
{
  return FALSE;
}

///
/// Device IDs for WLAN RSR Workaround
///
UINT16  mWlanSkusDeviceIdsTable[] = {
  0x422B, 0x4238,  // 6300 - Puma Peak 3
  0x0082, 0x0085,  // 6205 - Taylor Peak
  0x0890, 0x0891,  // 2200 - Marble Peak
  0x0887, 0x0888,  // 2230 - Jackson Peak 1
  0x088F, 0x088E,  // 6235 - Jackson Peak 2
  0x008A, 0x008B,  // 1030 - Rainbow Peak 1
  0x0091, 0x0090,  // 6230 - Rainbow Peak 2
  0x0885, 0x0886,  // 6150 - Kelsey Peak
  0x0087, 0x0089,  // 6250 - Kilmer Peak
};

///
/// Device IDs for WLAN D3 Workaround
///
UINT16  mWlanSkusDeviceIdsTable2[] = {
  0x08B3, 0x08B4, // 3160 - Wilkins Peak 1 
  0x08B1, 0x08B2, // 7260 - Wilkins Peak 2
};

/**
  This function is work around for NetDetect and WakeOnLan when RapidStart enabled.

  @retval EFI_SUCCESS           - Operation successfully performed
**/
EFI_STATUS
RapidStartWANetDetect (
  IN      EFI_PEI_SERVICES          **PeiServices,
  IN      UINT32                    WlanMmioSpace
  )
{
  UINT8                   RpFunction;
  UINTN                   RpBase;
  UINT8                   SecBusNum;
  UINT8                   SecSubBusNum;
  UINT8                   EpBusNum;
  UINTN                   EpBase;
  UINTN                   WlanSkusDeviceIdIndex;
  UINT8                   CapPtr;
  UINT8                   NxtPtr;
  UINT8                   CapID;
  UINT8                   PMCreg;
  UINT8                   PMCSR;
  UINT32                  Timeout;
  PEI_STALL_PPI           *StallPpi;
  EFI_STATUS              Status;

  DEBUG ((EFI_D_INFO, "RapidStartWANetDetect Start\n"));

  Status = PeiServicesLocatePpi (&gPeiStallPpiGuid, 0, NULL, (VOID **) &StallPpi);
  ASSERT_EFI_ERROR (Status);

  //
  // Scan PCH PCI-EX slots (Root Port) : Device 28 Function 0~7
  //
  for (RpFunction = 0; RpFunction < GetPchMaxPciePortNum (); RpFunction ++) {
    RpBase = MmPciAddress (0, DEFAULT_PCI_BUS_NUMBER_PCH, PCI_DEVICE_NUMBER_PCH_PCIE_ROOT_PORTS, RpFunction, 0);
    DEBUG ((EFI_D_INFO, "RapidStartWANetDetect: PCI-EX slot %x ...\n", RpFunction));

    if ((MmioRead16 (RpBase + R_PCH_PCIE_SLSTS) & B_PCH_PCIE_SLSTS_PDS) != 0 && MmioRead16 (RpBase + R_PCH_PCIE_VENDOR_ID) == V_PCH_PCIE_VENDOR_ID) {

      ///
      /// Set WLAN PortBus = 1 to Read Endpoint.
      ///
      MmioAndThenOr32(RpBase + R_PCH_PCIE_BNUM, 0xFF0000FF, 0x00010100);

      //
      // Get the downstream Bus number
      //
      SecBusNum = (UINT8) (MmioRead32 (RpBase + R_PCH_PCIE_BNUM) >> 8);
      SecSubBusNum = (UINT8) (MmioRead32 (RpBase + R_PCH_PCIE_BNUM) >> 16);

      for (EpBusNum = SecBusNum; EpBusNum <= SecSubBusNum; EpBusNum++) {
        EpBase = MmPciAddress (0, EpBusNum, 0, 0, 0);
        DEBUG ((EFI_D_INFO, "RapidStartWANetDetect: downstream Bus %x\n", EpBusNum));

        ///
        /// A config write is required in order for the device to re-capture the Bus number,
        /// according to PCI Express Base Specification, 2.2.6.2
        /// Write to a read-only register VendorID to not cause any side effects.
        ///
        MmioWrite16 (EpBase + R_PCH_PCIE_VENDOR_ID, 0);

        //
        // WLAN RSR Workaround
        //
        for (WlanSkusDeviceIdIndex = 0; WlanSkusDeviceIdIndex < sizeof (mWlanSkusDeviceIdsTable) / sizeof (mWlanSkusDeviceIdsTable[0]); WlanSkusDeviceIdIndex++) {
          if (mWlanSkusDeviceIdsTable[WlanSkusDeviceIdIndex] == MmioRead16 (EpBase + R_PCH_PCIE_DEVICE_ID)) {
            DEBUG ((EFI_D_INFO, "RapidStartWANetDetect: Found a device to support RSR and device ID is %x\n", MmioRead16 (EpBase + R_PCH_PCIE_DEVICE_ID)));

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
              // Check whether PME enabled
              //
              if (MmioRead16 (EpBase + PMCSR) & BIT8) {
                DEBUG ((EFI_D_INFO, "RapidStartWANetDetect: This device PME has been enabled\n"));

                //
                // Disabled PME
                //
                MmioAnd16 ((UINTN) (EpBase + PMCSR), (UINT16) (~BIT8));

                //
                // Set the WLAN device to D0
                //
                MmioAnd8 ((UINTN) (EpBase + PMCSR), (UINT8)(~(BIT0 + BIT1)));
                StallPpi->Stall (PeiServices, StallPpi, STALL_1_MICROSECONDS * 30);

                //
                // Disable PCIE memory map access
                //
                MmioAnd16 ((UINTN) (RpBase + R_PCH_PCIE_PCICMD), (UINT16) (~B_PCH_PCIE_PCICMD_MSE));

                //
                // Define PCIE MMIO BAR contains a valid address value
                //
                MmioWrite32 (RpBase + R_PCH_PCIE_MBL, (WlanMmioSpace & B_PCH_PCIE_MBL_ML) + ((WlanMmioSpace & B_PCH_PCIE_MBL_ML) >> 16));
                MmioWrite32 (RpBase + R_PCH_PCIE_PMBL, 0x0001FF1);

                //
                // Enable PCIE memory map access
                //
                MmioOr16 ((UINTN) (RpBase + R_PCH_PCIE_PCICMD), (UINT16) B_PCH_PCIE_PCICMD_MSE);
                DEBUG ((EFI_D_INFO, "RapidStartWANetDetect: Enabled PCIE memory map and MMIO Bar is %x\n", MmioRead32 (RpBase + R_PCH_PCIE_MBL)));

                //
                // Disable WLAN memory map access
                //
                MmioAnd16 ((UINTN) (EpBase + R_PCH_LAN_CMD), (UINT16) (~B_PCH_LAN_CMD_MSE));

                //
                // Define WLAN MMIO BAR contains a valid address value
                //
                MmioWrite32 (EpBase + R_PCH_LAN_MEM_BASE_A, WlanMmioSpace);

                //
                // Enable WLAN memory map access
                //
                MmioOr16 ((UINTN) (EpBase + R_PCH_LAN_CMD), (UINT16) B_PCH_LAN_CMD_MSE);

                WlanMmioSpace = MmioRead32 (EpBase + R_PCH_LAN_MEM_BASE_A) & B_PCH_LAN_MBARA_BA;

                DEBUG ((EFI_D_INFO, "RapidStartWANetDetect: Enabled memory map and MMIO Bar is %x\n", WlanMmioSpace));
                //
                // BIOS notify the uCode that RSR flow is needed
                //
                MmioWrite32 ((WlanMmioSpace + 0x58), 0x40);
                //
                // BIOS waiting for uCode to do the all necessary preparation and set a timer of 100 ms.
                //
                Timeout = 0;
                while ((MmioRead32 (WlanMmioSpace + 0x54) & BIT7) == 0 && Timeout < MAX_UCODE_TIMEOUT) {
                  StallPpi->Stall (PeiServices, StallPpi, STALL_1_MICROSECONDS);
                  Timeout++;
                }

                DEBUG ((EFI_D_INFO, "RapidStartWANetDetect: The Timeout value is %x and Register 0x54 is %x\n", Timeout, MmioRead32 (WlanMmioSpace + 0x54)));
                if (Timeout < MAX_UCODE_TIMEOUT) {
                  StallPpi->Stall (PeiServices, StallPpi, STALL_1_MICROSECONDS * 100);
                  //
                  // Perform WLAN Shared HW reset
                  //
                  MmioWrite32 ((WlanMmioSpace + 0x20), BIT7);
                  StallPpi->Stall (PeiServices, StallPpi, STALL_1_MICROSECONDS * 50);
                  //
                  // Re-Enable MAC Clock
                  //
                  MmioWrite32 ((WlanMmioSpace + 0x24), BIT2);
                  StallPpi->Stall (PeiServices, StallPpi, STALL_1_MICROSECONDS * 50000);
                  //
                  // De-Reset the MAC
                  //
                  MmioAnd32 ((UINTN) (WlanMmioSpace + 0x20), (UINT32) (~BIT0));
                  StallPpi->Stall (PeiServices, StallPpi, STALL_1_MICROSECONDS * 50);

                  //
                  // Enabled PME again
                  //
                  MmioOr16 ((EpBase + PMCSR), BIT8);
                  //
                  // Persistence ON
                  //
                  MmioOr32 ((WlanMmioSpace + 0x00), BIT30);

                  //
                  // Set the WLAN device to D3
                  //
                  MmioOr8 ((UINTN) (EpBase + PMCSR), BIT0 + BIT1);

                  DEBUG ((EFI_D_INFO, "RapidStartWANetDetect: RSR is successfully\n"));
                }
              }
            }
          }
        }
        
        //
        // WLAN D3 Workaround
        //
        for (WlanSkusDeviceIdIndex = 0; WlanSkusDeviceIdIndex < sizeof (mWlanSkusDeviceIdsTable2) / sizeof (mWlanSkusDeviceIdsTable2[0]); WlanSkusDeviceIdIndex++) {
          if (mWlanSkusDeviceIdsTable2[WlanSkusDeviceIdIndex] == MmioRead16 (EpBase + R_PCH_PCIE_DEVICE_ID)) {
            DEBUG ((EFI_D_INFO, "RapidStartWANetDetect: Found a device to support D3 and device ID is %x\n", MmioRead16 (EpBase + R_PCH_PCIE_DEVICE_ID)));

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
              // Check whether PME enabled 
              //
              if (MmioRead16 (EpBase + PMCSR) & BIT8) {
                DEBUG ((EFI_D_INFO, "RapidStartWANetDetect: This device PME has been enabled\n"));

                //
                // Set the WLAN device to D3
                //
                MmioOr8 ((UINTN) (EpBase + PMCSR), BIT0 + BIT1);

                DEBUG ((EFI_D_INFO, "RapidStartWANetDetect: D3 is successfully\n"));
              }
            }
          }
        }

        ///
        /// Restore bus numbers on the WLAN bridge.
        ///
        MmioAnd32(RpBase + R_PCH_PCIE_BNUM, 0xFF0000FF);
      }
    }
  }
  DEBUG ((EFI_D_INFO, "RapidStartWANetDetect End\n"));

  return EFI_SUCCESS;
}

/**
  This callback is executed to clear all PEM events before Rapid Start enter S4.

  @retval EFI_SUCCESS           - Operation successfully performed
**/
EFI_STATUS
RapidStartClearOemPmeEvent (
  VOID
  )
{
  UINT16          EhciPme, Ehci2Pme, xHciPme;
  UINT8           Index;
  UINT16          PCIePme[8];
  UINT16          GigaLanPme;

  DEBUG ((EFI_D_INFO, "RapidStartClearOemPmeEvent Start\n"));

  //
  // Save Ehci, Ehci2 and xHci Power Control Status register
  //
  EhciPme = MmioRead16 (
              MmPciAddress (
                0,
                DEFAULT_PCI_BUS_NUMBER_PCH,
                PCI_DEVICE_NUMBER_PCH_USB,
                PCI_FUNCTION_NUMBER_PCH_EHCI,
                R_PCH_EHCI_PWR_CNTL_STS)
                );
  Ehci2Pme = MmioRead16 (
               MmPciAddress (
                 0,
                 DEFAULT_PCI_BUS_NUMBER_PCH,
                 PCI_DEVICE_NUMBER_PCH_USB_EXT,
                 PCI_FUNCTION_NUMBER_PCH_EHCI2,
                 R_PCH_EHCI_PWR_CNTL_STS)
                 );
  xHciPme = MmioRead16 (
              MmPciAddress (
                0,
                DEFAULT_PCI_BUS_NUMBER_PCH,
                PCI_DEVICE_NUMBER_PCH_XHCI,
                PCI_FUNCTION_NUMBER_PCH_XHCI,
                R_PCH_XHCI_PWR_CNTL_STS)
                );
  //
  // Disabled Ehci, Ehcu2 and xHci PME & Clear PME status
  //
  MmioWrite16 (
    MmPciAddress (
      0,
      DEFAULT_PCI_BUS_NUMBER_PCH,
      PCI_DEVICE_NUMBER_PCH_USB,
      PCI_FUNCTION_NUMBER_PCH_EHCI,
      R_PCH_EHCI_PWR_CNTL_STS),
    ((EhciPme & ~B_PCH_EHCI_PWR_CNTL_STS_PME_EN) | B_PCH_EHCI_PWR_CNTL_STS_PME_STS)
    );
  MmioWrite16 (
    MmPciAddress (
      0,
      DEFAULT_PCI_BUS_NUMBER_PCH,
      PCI_DEVICE_NUMBER_PCH_USB_EXT,
      PCI_FUNCTION_NUMBER_PCH_EHCI2,
      R_PCH_EHCI_PWR_CNTL_STS),
    ((Ehci2Pme & ~B_PCH_EHCI_PWR_CNTL_STS_PME_EN) | B_PCH_EHCI_PWR_CNTL_STS_PME_STS)
    );
  MmioWrite16 (
    MmPciAddress (
      0,
      DEFAULT_PCI_BUS_NUMBER_PCH,
      PCI_DEVICE_NUMBER_PCH_XHCI,
      PCI_FUNCTION_NUMBER_PCH_XHCI,
      R_PCH_XHCI_PWR_CNTL_STS),
    ((xHciPme & ~B_PCH_XHCI_PWR_CNTL_STS_PME_EN) | B_PCH_XHCI_PWR_CNTL_STS_PME_STS)
    );

  for (Index = 0; Index <= PCI_FUNCTION_NUMBER_PCH_PCIE_ROOT_PORT_8; Index++) {
    //
    // Save PCIEs Power Control Status register
    //
    PCIePme[Index] = MmioRead16 (
                       MmPciAddress (
                         0,
                         DEFAULT_PCI_BUS_NUMBER_PCH,
                         PCI_DEVICE_NUMBER_PCH_PCIE_ROOT_PORTS,
                         (PCI_FUNCTION_NUMBER_PCH_PCIE_ROOT_PORT_1 + Index),
                         R_PCH_PCIE_PMCS)
                         );
    //
    // Disabled PCIEs PME & Clear PME status
    //
    MmioWrite16 (
      MmPciAddress (
        0,
        DEFAULT_PCI_BUS_NUMBER_PCH,
        PCI_DEVICE_NUMBER_PCH_PCIE_ROOT_PORTS,
        (PCI_FUNCTION_NUMBER_PCH_PCIE_ROOT_PORT_1 + Index),
        R_PCH_PCIE_PMCS),
      ((PCIePme[Index] & ~B_PCH_PCIE_PMCS_PMEE) | B_PCH_PCIE_PMCS_PMES)
      );
  }

  //
  // Save Giga Lan Power Control Status register
  //
  GigaLanPme = MmioRead16 (
                 MmPciAddress (
                   0,
                   DEFAULT_PCI_BUS_NUMBER_PCH,
                   PCI_DEVICE_NUMBER_PCH_LAN,
                   PCI_FUNCTION_NUMBER_PCH_LAN,
                   R_PCH_LAN_PMCS)
                  );
  //
  // Disabled Giga Lan PME & Clear PME status
  //
  MmioWrite16 (
    MmPciAddress (
      0,
      DEFAULT_PCI_BUS_NUMBER_PCH,
      PCI_DEVICE_NUMBER_PCH_LAN,
      PCI_FUNCTION_NUMBER_PCH_LAN,
      R_PCH_LAN_PMCS),
    ((GigaLanPme & ~B_PCH_LAN_PMCS_PMEE) | B_PCH_LAN_PMCS_PMES)
    );

  //
  // Restore Ehci, Ehci2 and xHci Power Control Status register
  //
  MmioWrite16 (
    MmPciAddress (
      0,
      DEFAULT_PCI_BUS_NUMBER_PCH,
      PCI_DEVICE_NUMBER_PCH_USB,
      PCI_FUNCTION_NUMBER_PCH_EHCI,
      R_PCH_EHCI_PWR_CNTL_STS),
    EhciPme
    );
  MmioWrite16 (
    MmPciAddress (
      0,
      DEFAULT_PCI_BUS_NUMBER_PCH,
      PCI_DEVICE_NUMBER_PCH_USB_EXT,
      PCI_FUNCTION_NUMBER_PCH_EHCI2,
      R_PCH_EHCI_PWR_CNTL_STS),
    Ehci2Pme
    );
  MmioWrite16 (
    MmPciAddress (
      0,
      DEFAULT_PCI_BUS_NUMBER_PCH,
      PCI_DEVICE_NUMBER_PCH_XHCI,
      PCI_FUNCTION_NUMBER_PCH_XHCI,
      R_PCH_XHCI_PWR_CNTL_STS),
    xHciPme
    );

  //
  // XHCI's previous state is D3(this is woken from S3). In the RapidStartEntry,
  // when preparing to enter into S4, put XHCI into D3(fix the auto wake-up issue).
  //
  MmioWrite16 (
    MmPciAddress (
      0,
      DEFAULT_PCI_BUS_NUMBER_PCH,
      PCI_DEVICE_NUMBER_PCH_XHCI,
      PCI_FUNCTION_NUMBER_PCH_XHCI,
      R_PCH_XHCI_PWR_CNTL_STS),
    (xHciPme | V_PCH_XHCI_PWR_CNTL_STS_PWR_STS_D3)
    );

  //
  // Restore PCIEs Power Control Status register
  //

  for (Index = 0; Index <= PCI_FUNCTION_NUMBER_PCH_PCIE_ROOT_PORT_8; Index++) {
    MmioWrite16 (
      MmPciAddress (
        0,
        DEFAULT_PCI_BUS_NUMBER_PCH,
        PCI_DEVICE_NUMBER_PCH_PCIE_ROOT_PORTS,
        (PCI_FUNCTION_NUMBER_PCH_PCIE_ROOT_PORT_1 + Index),
        R_PCH_PCIE_PMCS),
      PCIePme[Index]
      );
  }

  //
  // Restore Giga Lan Power Control Status register
  //
  MmioWrite16 (
    MmPciAddress (
      0,
      DEFAULT_PCI_BUS_NUMBER_PCH,
      PCI_DEVICE_NUMBER_PCH_LAN,
      PCI_FUNCTION_NUMBER_PCH_LAN,
      R_PCH_LAN_PMCS),
    GigaLanPme
    );

  DEBUG ((EFI_D_INFO, "RapidStartClearOemPmeEvent End\n"));

  return EFI_SUCCESS;
}

/**
  Provide a hook for OEM to cancel RapidStart Instant-On function.
  This function may impact RapidStart Resume performance since it's polled frequently.

  @retval FALSE     - Do not cancel RapidStart Instant-On
  @retval TRUE      - The RapidStart Resume will have no Instant-On function
**/
BOOLEAN
RapidStartUnattendedWake (
  VOID
  )
{

  return FALSE;
}
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
