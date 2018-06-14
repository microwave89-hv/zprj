/** @file
  This driver will determine memory configuration information from the chipset
  and memory and create SMBIOS memory structures appropriately.

@copyright
  Copyright (c) 1999 - 2013 Intel Corporation. All rights reserved
  This software and associated documentation (if any) is furnished
  under a license and may only be used or copied in accordance
  with the terms of the license. Except as permitted by such
  license, no part of this software or documentation may be
  reproduced, stored in a retrieval system, or transmitted in any
  form or by any means without the express written consent of
  Intel Corporation.
  This file contains an 'Intel Peripheral Driver' and uniquely
  identified as "Intel Reference Module" and is
  licensed for Intel CPUs and chipsets under the terms of your
  license agreement with Intel or your vendor.  This file may
  be modified by the user, subject to additional terms of the
  license agreement

**/
#include "SmbiosMemory.h"
EFI_DRIVER_ENTRY_POINT (SmbiosMemoryEntryPoint)

extern UINT8                    SmBiosMemoryStrings[];
MEMORY_MODULE_MANUFACTURE_LIST  MemoryModuleManufactureList[] = {
  {
    0,
    0x2c,
    L"Micron"
  },
  {
    0,
    0xad,
    L"Hynix/Hyundai"
  },
  {
    0,
    0xce,
    L"Samsung"
  },
  {
    1,
    0x4f,
    L"Transcend"
  },
  {
    1,
    0x98,
    L"Kingston"
  },
  {
    2,
    0xfe,
    L"Elpida"
  },
  {
    0xff,
    0xff,
    0
  }
};

///
/// Even SPD Addresses only as we read Words
///
const UINT8
  SpdAddress[] = { 2, 8, 116, 118, 122, 124, 126, 128, 130, 132, 134, 136, 138, 140, 142, 144 };

/**
    This driver will determine memory configuration information from the chipset
    and memory and report the memory configuration info to the DataHub.

    @param[in] ImageHandle   - Handle for the image of this driver
    @param[in] SystemTable   - Pointer to the EFI System Table

    @retval EFI_SUCCESS          - if the data is successfully reported
    @retval EFI_NOT_FOUND        - if the HOB list could not be located.
    @retval EFI_OUT_OF_RESOURCES - if not able to get resouces.
**/
EFI_STATUS
SmbiosMemoryEntryPoint (
  IN EFI_HANDLE       ImageHandle,
  IN EFI_SYSTEM_TABLE *SystemTable
  )
{
  BOOLEAN                         Populated;
  CHAR16                          StringBuffer2[64];
  EFI_DATA_HUB_PROTOCOL           *DataHub;
  DDR_ROW_CONFIG                  RowConfArray[SA_MC_MAX_SOCKETS];
  EFI_MEMORY_SUBCLASS_DRIVER_DATA MemorySubClassData;
  EFI_SMBUS_DEVICE_ADDRESS        SmbusSlaveAddress;
  EFI_SMBUS_HC_PROTOCOL           *SmbusController;
  EFI_STATUS                      Status;
  EFI_STRING                      StringBuffer;
  EFI_PHYSICAL_ADDRESS            BaseAddress;
  UINT8                           Index;
  UINT8                           *SmbusBuffer;
  UINT16                          ArrayInstance;
  UINT64                          DimmMemorySize;
  UINT64                          TotalMemorySize;
  UINT8                           Dimm;
  UINTN                           SmbusBufferSize;
  UINTN                           SmbusLength;
  UINTN                           SmbusOffset;
  UINTN                           StringBufferSize;
  UINT8                           IndexCounter;
  UINTN                           IdListIndex;
  MEM_INFO_PROTOCOL               *MemInfoHob;
  EFI_GUID                        MemInfoProtocolGuid = MEM_INFO_PROTOCOL_GUID;
  UINT8                           ChannelASlotMap;
  UINT8                           ChannelBSlotMap;
  UINT8                           BitIndex;
  UINT16                          MaxSockets;
  UINT8                           WidthCount=0;  //AMI_OVERRIDE [EIP344598]
  UINT8                           ChannelASlotNum;
  UINT8                           ChannelBSlotNum;
  BOOLEAN                         SlotPresent;
  UINT16                          MemoryTotalWidth;
  UINT16                          MemoryDataWidth;
  UINT8                           i;

#if (EFI_SPECIFICATION_VERSION >= 0x0002000A)
  EFI_HANDLE                      DriverHandle;
  EFI_HII_DATABASE_PROTOCOL       *HiiDatabase;
  EFI_HII_PACKAGE_LIST_HEADER     *PackageList;
  EFI_HII_HANDLE                  StringPackHandle;
#else
  EFI_HII_PROTOCOL                *Hii;
  EFI_HII_HANDLE                  HiiHandle;
  EFI_HII_PACKAGES                *PackageList;
#endif
  STRING_REF                      DimmToDevLocator[] = {
    STRING_TOKEN (STR_MEMORY_SUBCLASS_DEVICE_LOCATOR_0),
    STRING_TOKEN (STR_MEMORY_SUBCLASS_DEVICE_LOCATOR_1),
    STRING_TOKEN (STR_MEMORY_SUBCLASS_DEVICE_LOCATOR_2),
    STRING_TOKEN (STR_MEMORY_SUBCLASS_DEVICE_LOCATOR_3)
  };

  STRING_REF                      DimmToBankLocator[] = {
    STRING_TOKEN (STR_MEMORY_SUBCLASS_BANK_LOCATOR_0),
    STRING_TOKEN (STR_MEMORY_SUBCLASS_BANK_LOCATOR_1),
    STRING_TOKEN (STR_MEMORY_SUBCLASS_BANK_LOCATOR_2),
    STRING_TOKEN (STR_MEMORY_SUBCLASS_BANK_LOCATOR_3)
  };

  EFI_GUID                        gEfiMemorySubClassDriverGuid = EFI_MEMORY_SUBCLASS_DRIVER_GUID;
  DXE_PLATFORM_SA_POLICY_PROTOCOL *DxePlatformSaPolicy;

  DxePlatformSaPolicy           = NULL;

  ///
  /// Get the platform setup policy.
  ///
  Status = gBS->LocateProtocol (&gDxePlatformSaPolicyGuid, NULL, (VOID **) &DxePlatformSaPolicy);
  ASSERT_EFI_ERROR (Status);

  StringBufferSize  = (sizeof (CHAR16)) * 100;
  StringBuffer      = AllocateZeroPool (StringBufferSize);
  if (StringBuffer == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  SmbusBuffer     = NULL;
  SmbusBufferSize = 0x100;
  SmbusBuffer     = AllocatePool (SmbusBufferSize);
  if (SmbusBuffer == NULL) {
    (gBS->FreePool) (StringBuffer);
    return EFI_OUT_OF_RESOURCES;
  }

  Status = gBS->LocateProtocol (&gEfiDataHubProtocolGuid, NULL, (VOID **) &DataHub);
  ASSERT_EFI_ERROR (Status);

  Status = gBS->LocateProtocol (&gEfiSmbusProtocolGuid, NULL, (VOID **) &SmbusController);
  ASSERT_EFI_ERROR (Status);

#if (EFI_SPECIFICATION_VERSION >= 0x0002000A)

  Status = gBS->LocateProtocol (
                  &gEfiHiiDatabaseProtocolGuid,
                  NULL,
                  (VOID **) &HiiDatabase
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }
  ///
  /// Create driver handle used by HII database
  ///
  Status = CreateHiiDriverHandle (&DriverHandle);
  if (EFI_ERROR (Status)) {
    return Status;
  }
  ///
  /// Publish our HII data
  ///
  PackageList = PreparePackageList (1, &gEfiMemorySubClassDriverGuid, SmBiosMemoryStrings);
  if (PackageList == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  Status = HiiDatabase->NewPackageList (
                          HiiDatabase,
                          PackageList,
                          DriverHandle,
                          &StringPackHandle
                          );
  ASSERT_EFI_ERROR (Status);

#else
  ///
  /// There should only be one HII protocol
  ///
  Status = gBS->LocateProtocol (&gEfiHiiProtocolGuid, NULL, (VOID **) &Hii);
  ASSERT_EFI_ERROR (Status);

  ///
  /// Add our default strings to the HII database. They will be modified later.
  ///
  PackageList = PreparePackages (1, &gEfiMemorySubClassDriverGuid, SmBiosMemoryStrings);
  Status      = Hii->NewPack (Hii, PackageList, &HiiHandle);

#endif

  (gBS->FreePool) (PackageList);

  Status = gBS->LocateProtocol (&MemInfoProtocolGuid, NULL, (VOID **) &MemInfoHob);
  ASSERT_EFI_ERROR (Status);
  ///
  /// Data for TYPE 16 SMBIOS Structure
  ///
  ///
  /// Create physical array and associated data for all mainboard memory
  ///
  ArrayInstance                         = 1;
  TotalMemorySize                       = 0;
  MemorySubClassData.Header.Version     = EFI_MEMORY_SUBCLASS_VERSION;
  MemorySubClassData.Header.HeaderSize  = sizeof (EFI_SUBCLASS_TYPE1_HEADER);
  MemorySubClassData.Header.Instance    = ArrayInstance;
  MemorySubClassData.Header.SubInstance = EFI_SUBCLASS_INSTANCE_NON_APPLICABLE;
  MemorySubClassData.Header.RecordType  = EFI_MEMORY_ARRAY_LOCATION_RECORD_NUMBER;

  MemorySubClassData.Record.ArrayLocationData.MemoryArrayLocation = EfiMemoryArrayLocationSystemBoard;
  MemorySubClassData.Record.ArrayLocationData.MemoryArrayUse      = EfiMemoryArrayUseSystemMemory;

  ///
  /// Detect ECC
  ///
  if (MemInfoHob->MemInfoData.EccSupport) {
    MemorySubClassData.Record.ArrayLocationData.MemoryErrorCorrection = EfiMemoryErrorCorrectionSingleBitEcc;
  } else {
    MemorySubClassData.Record.ArrayLocationData.MemoryErrorCorrection = EfiMemoryErrorCorrectionNone;
  }
  ///
  /// Get the Memory DIMM info from platform policy protocols
  ///
  ChannelASlotMap = DxePlatformSaPolicy->MemoryConfig->ChannelASlotMap;
  ChannelBSlotMap = DxePlatformSaPolicy->MemoryConfig->ChannelBSlotMap;
  ChannelASlotNum = 0;
  ChannelBSlotNum = 0;
  for (BitIndex = 0; BitIndex < 8; BitIndex++) {
    if ((ChannelASlotMap >> BitIndex) & BIT0) {
      ChannelASlotNum++;
    }

    if ((ChannelBSlotMap >> BitIndex) & BIT0) {
      ChannelBSlotNum++;
    }
  }

  MaxSockets  = ChannelASlotNum + ChannelBSlotNum;
  MemorySubClassData.Record.ArrayLocationData.MaximumMemoryCapacity = MAX_RANK_CAPACITY * SA_MC_MAX_SIDES * MaxSockets;
  MemorySubClassData.Record.ArrayLocationData.NumberMemoryDevices   = (UINT16) (MaxSockets);

  ///
  /// Report top level physical array to datahub
  /// This will translate into a Type 16 SMBIOS Record
  ///
  Status = DataHub->LogData (
                      DataHub,
                      &gEfiMemorySubClassGuid,
                      &gEfiMemorySubClassDriverGuid,
                      EFI_DATA_RECORD_CLASS_DATA,
                      &MemorySubClassData,
                      sizeof (EFI_SUBCLASS_TYPE1_HEADER) + sizeof (EFI_MEMORY_ARRAY_LOCATION_DATA)
                      );
  if (EFI_ERROR (Status)) {
    goto CleanAndExit;
  }
  ///
  /// Get Memory size parameters for each rank
  ///
  ///
  /// We start from a base address of 0 for rank 0. We calculate the base address based on the DIMM size.
  ///
  BaseAddress = 0;

  for (Dimm = 0; Dimm < SA_MC_MAX_SLOTS; Dimm++) {
    ///
    /// Channel 0
    ///
    RowConfArray[Dimm].BaseAddress  = BaseAddress;
    RowConfArray[Dimm].RowLength    = LShiftU64 (MemInfoHob->MemInfoData.dimmSize[Dimm], 20);
    BaseAddress += RowConfArray[Dimm].RowLength;
    ///
    /// Channel 1
    ///
    RowConfArray[Dimm + SA_MC_MAX_SLOTS].BaseAddress  = BaseAddress;
    RowConfArray[Dimm + SA_MC_MAX_SLOTS].RowLength    = LShiftU64 (MemInfoHob->MemInfoData.dimmSize[Dimm + SA_MC_MAX_SLOTS], 20);
    BaseAddress += RowConfArray[Dimm + SA_MC_MAX_SLOTS].RowLength;

  }
  ///
  /// For each existed socket whether it is populated or not generate Type 17.
  /// Type 20 is optional for existed and populated socket.
  ///
  /// The Desktop and mobile only support 2 channels * 2 slots per channel = 4 sockets totally
  /// So there is rule here for Desktop and mobile that there are no more 4 DIMMS totally in a system:
  ///  Channel A/ Slot 0 --> SpdAddressTable[0] --> DimmToDevLocator[0] --> MemInfoHobProtocol.MemInfoData.dimmSize[0]
  ///  Channel A/ Slot 1 --> SpdAddressTable[1] --> DimmToDevLocator[1] --> MemInfoHobProtocol.MemInfoData.dimmSize[1]
  ///  Channel B/ Slot 0 --> SpdAddressTable[2] --> DimmToDevLocator[2] --> MemInfoHobProtocol.MemInfoData.dimmSize[2]
  ///  Channel B/ Slot 1 --> SpdAddressTable[3] --> DimmToDevLocator[3] --> MemInfoHobProtocol.MemInfoData.dimmSize[3]
  ///
  for (Dimm = 0; Dimm < SA_MC_MAX_SOCKETS; Dimm++) {
    ///
    /// Use channel slot map to check whether the Socket is supported in this SKU, some SKU only has 2 Sockets totally
    ///
    SlotPresent = FALSE;
    if (Dimm < 2) {
      if (ChannelASlotMap & (1 << Dimm)) {
        SlotPresent = TRUE;
      }
    } else {
      if (ChannelBSlotMap & (1 << (Dimm - 2))) {
        SlotPresent = TRUE;
      }
    }
    ///
    /// Don't create Type 17 and Type 20 items for non-existing socket
    ///
    if (!SlotPresent) {
      continue;
    }
    ///
    /// Generate Memory Device info (Type 17)
    ///
    ZeroMem (SmbusBuffer, SmbusBufferSize);
    ///
    /// Only read the SPD data if the DIMM is populated in the slot.
    ///
    Populated = MemInfoHob->MemInfoData.DimmExist[Dimm];
    if (Populated) {
      WidthCount++;           //AMI_OVERRIDE [EIP344598]
      ///
      /// Read the SPD for this DIMM
      ///
      SmbusSlaveAddress.SmbusDeviceAddress = (DxePlatformSaPolicy->MemoryConfig->SpdAddressTable[Dimm]) >> 1;

      ///
      /// Read only needed values from SMBus or DimmsSpdData pointer to improve performance.
      ///
      for (i = 0; i < sizeof SpdAddress; i++) {
        SmbusOffset = SpdAddress[i];
        if (MemInfoHob->MemInfoData.DimmsSpdData[Dimm] == NULL) {
          SmbusLength = 2;
          Status = SmbusController->Execute (
                                      SmbusController,
                                      SmbusSlaveAddress,
                                      SmbusOffset,
                                      EfiSmbusReadWord,
                                      FALSE,
                                      &SmbusLength,
                                      &SmbusBuffer[SmbusOffset]
                                      );
          if (EFI_ERROR (Status)) {
            Populated = FALSE;
            break;
          }
        } else {
          *(UINT16 *) (SmbusBuffer + SmbusOffset) = *(UINT16 *) (MemInfoHob->MemInfoData.DimmsSpdData[Dimm] + SmbusOffset);
        }
      }
    }

    ZeroMem (&MemorySubClassData, sizeof (EFI_MEMORY_SUBCLASS_DRIVER_DATA));

    ///
    /// Use SPD data to generate Device Type info
    ///
    MemorySubClassData.Header.Version                       = EFI_MEMORY_SUBCLASS_VERSION;
    MemorySubClassData.Header.HeaderSize                    = sizeof (EFI_SUBCLASS_TYPE1_HEADER);
    MemorySubClassData.Header.Instance                      = ArrayInstance;
    MemorySubClassData.Header.SubInstance                   = (UINT16) (Dimm + 1);
    MemorySubClassData.Header.RecordType                    = EFI_MEMORY_ARRAY_LINK_RECORD_NUMBER;

    MemorySubClassData.Record.ArrayLink.MemoryDeviceLocator = DimmToDevLocator[Dimm];
    MemorySubClassData.Record.ArrayLink.MemoryBankLocator   = DimmToBankLocator[Dimm];

#ifdef MEMORY_ASSET_TAG
    StrCpy (StringBuffer, MEMORY_ASSET_TAG);
    MemorySubClassData.Record.ArrayLink.MemoryAssetTag = (STRING_REF) 0;

#if (EFI_SPECIFICATION_VERSION >= 0x0002000A)
    Status = IfrLibNewString (StringPackHandle, &MemorySubClassData.Record.ArrayLink.MemoryAssetTag, StringBuffer);
    ASSERT_EFI_ERROR (Status);
#else
    Status = Hii->NewString (
                    Hii,
                    NULL,
                    HiiHandle,
                    &MemorySubClassData.Record.ArrayLink.MemoryAssetTag,
                    StringBuffer
                    );
    ASSERT_EFI_ERROR (Status);
#endif

#else
    MemorySubClassData.Record.ArrayLink.MemoryAssetTag = STRING_TOKEN (STR_MEMORY_SUBCLASS_DEFAULT_ASSET_TAG);
#endif

    MemorySubClassData.Record.ArrayLink.MemoryArrayLink.ProducerName    = gEfiMemorySubClassDriverGuid;
    MemorySubClassData.Record.ArrayLink.MemoryArrayLink.Instance        = ArrayInstance;
    MemorySubClassData.Record.ArrayLink.MemoryArrayLink.SubInstance     = EFI_SUBCLASS_INSTANCE_NON_APPLICABLE;
    MemorySubClassData.Record.ArrayLink.MemorySubArrayLink.ProducerName = gEfiMemorySubClassDriverGuid;
    MemorySubClassData.Record.ArrayLink.MemorySubArrayLink.SubInstance  = EFI_SUBCLASS_INSTANCE_NON_APPLICABLE;
    ///
    /// Set MemoryType value to DDR3 (0x18)
    ///
    MemorySubClassData.Record.ArrayLink.MemoryType = EfiMemoryTypeDdr3;

    ///
    /// According to SMBIOS 2.6.1 Specification - Appendix A Conformance Guidelines
    /// 4.8.7:  Form Factor is not 00h (Reserved) or 02h (Unknown).
    ///
    if (Populated) {
      switch (SmbusBuffer[DDR_MTYPE_SPD_OFFSET] & DDR_MTYPE_SPD_MASK) {
      case DDR_MTYPE_SODIMM:
        MemorySubClassData.Record.ArrayLink.MemoryFormFactor = EfiMemoryFormFactorSodimm;
        break;

      case DDR_MTYPE_RDIMM:
      case DDR_MTYPE_MINI_RDIMM:
        MemorySubClassData.Record.ArrayLink.MemoryFormFactor = EfiMemoryFormFactorRimm;
        break;

      case DDR_MTYPE_UDIMM:
      case DDR_MTYPE_MICRO_DIMM:
      case DDR_MTYPE_MINI_UDIMM:
      default:
        MemorySubClassData.Record.ArrayLink.MemoryFormFactor = EfiMemoryFormFactorDimm;
      }
      ///
      /// Show name for known manufacturer or ID for unknown manufacturer
      ///
      StrCpy (StringBuffer, L"");

      ///
      /// Calculate index counter
      /// Clearing Bit7 as it is the Parity Bit for Byte 117
      ///
      IndexCounter = SmbusBuffer[117] & (~0x80);

      ///
      /// Converter memory manufacturer ID to string
      ///
      for (IdListIndex = 0; MemoryModuleManufactureList[IdListIndex].Index != 0xff; IdListIndex++) {
        if (MemoryModuleManufactureList[IdListIndex].Index == IndexCounter &&
            MemoryModuleManufactureList[IdListIndex].ManufactureId == SmbusBuffer[118]
            ) {
          StrCpy (StringBuffer, MemoryModuleManufactureList[IdListIndex].ManufactureName);
          break;
        }
      }
      ///
      /// Use original data if no conversion information in conversion table
      ///
      if (!(*StringBuffer)) {
        for (Index = 117; Index < 119; Index++) {
          ///
          /// --cr--         EfiValueToHexStr(StringBuffer2, SmbusBuffer[Index], PREFIX_ZERO, 2);
          ///
          UnicodeValueToString (StringBuffer2, PREFIX_ZERO, SmbusBuffer[Index], 2);
          StrCat (StringBuffer, StringBuffer2);
        }
      }

      MemorySubClassData.Record.ArrayLink.MemoryManufacturer = (STRING_REF) 0;
#if (EFI_SPECIFICATION_VERSION >= 0x0002000A)
      Status = IfrLibNewString (
                StringPackHandle,
                &MemorySubClassData.Record.ArrayLink.MemoryManufacturer,
                StringBuffer
                );
      ASSERT_EFI_ERROR (Status);
#else
      Status = Hii->NewString (
                      Hii,
                      NULL,
                      HiiHandle,
                      &MemorySubClassData.Record.ArrayLink.MemoryManufacturer,
                      StringBuffer
                      );
      ASSERT_EFI_ERROR (Status);
#endif
      StrCpy (StringBuffer, L"");
      for (Index = 122; Index < 126; Index++) {
        EfiValueToHexStr(StringBuffer2, SmbusBuffer[Index], PREFIX_ZERO, 2);
        StrCat (StringBuffer, StringBuffer2);
      }

      MemorySubClassData.Record.ArrayLink.MemorySerialNumber = (STRING_REF) 0;
#if (EFI_SPECIFICATION_VERSION >= 0x0002000A)
      Status = IfrLibNewString (
                StringPackHandle,
                &MemorySubClassData.Record.ArrayLink.MemorySerialNumber,
                StringBuffer
                );
      ASSERT_EFI_ERROR (Status);
#else
      Status = Hii->NewString (
                      Hii,
                      NULL,
                      HiiHandle,
                      &MemorySubClassData.Record.ArrayLink.MemorySerialNumber,
                      StringBuffer
                      );
      ASSERT_EFI_ERROR (Status);
#endif
      StrCpy (StringBuffer, L"");
      for (Index = 128; Index < 146; Index++) {
        UnicodeSPrint (
          StringBuffer2,
          4,
          L"%c",
          SmbusBuffer[Index]
          );
        StrCat (StringBuffer, StringBuffer2);
      }

      MemorySubClassData.Record.ArrayLink.MemoryPartNumber = (STRING_REF) 0;
#if (EFI_SPECIFICATION_VERSION >= 0x0002000A)
      Status = IfrLibNewString (StringPackHandle, &MemorySubClassData.Record.ArrayLink.MemoryPartNumber, StringBuffer);
      ASSERT_EFI_ERROR (Status);
#else
      Status = Hii->NewString (
                      Hii,
                      NULL,
                      HiiHandle,
                      &MemorySubClassData.Record.ArrayLink.MemoryPartNumber,
                      StringBuffer
                      );
      ASSERT_EFI_ERROR (Status);
#endif
      ///
      /// Get the Memory TotalWidth and DataWidth info for DDR3
      /// refer to DDR3 SPD 1.0 spec, Byte 8: Module Memory Bus Width
      /// SPD Offset 8 Bits [2:0] DataWidth aka Primary Bus Width
      /// SPD Offset 8 Bits [4:3] Bus Width extension for ECC
      ///
      MemoryDataWidth   = 8 * (1 << (SmbusBuffer[8] & 0x07));
      MemoryTotalWidth  = MemoryDataWidth + 8 * (SmbusBuffer[8] & 0x18);
      MemorySubClassData.Record.ArrayLink.MemoryTotalWidth  = MemoryTotalWidth;
      MemorySubClassData.Record.ArrayLink.MemoryDataWidth   = MemoryDataWidth;
      DimmMemorySize = RowConfArray[Dimm].RowLength;

      TotalMemorySize += DimmMemorySize;
      MemorySubClassData.Record.ArrayLink.MemoryDeviceSize              = DimmMemorySize;
      MemorySubClassData.Record.ArrayLink.MemoryTypeDetail.Synchronous  = 1;
      if (MemorySubClassData.Record.ArrayLink.MemoryFormFactor == EfiMemoryFormFactorRimm) {
        MemorySubClassData.Record.ArrayLink.MemoryTypeDetail.Rambus = 1;
      }

      MemorySubClassData.Record.ArrayLink.MemorySpeed       = MemInfoHob->MemInfoData.ddrFreq;
      MemorySubClassData.Record.ArrayLink.MemoryAttributes  = MemInfoHob->MemInfoData.RankInDimm[Dimm] & 0x0F;
    } else {
      ///
      /// Memory is not Populated in this slot.
      ///
      StrCpy (StringBuffer, L"");
      MemorySubClassData.Record.ArrayLink.MemoryManufacturer = (STRING_REF) 0;
#if (EFI_SPECIFICATION_VERSION >= 0x0002000A)
      Status = IfrLibNewString (
                StringPackHandle,
                &MemorySubClassData.Record.ArrayLink.MemoryManufacturer,
                StringBuffer
                );
      ASSERT_EFI_ERROR (Status);
#else
      Status = Hii->NewString (
                      Hii,
                      NULL,
                      HiiHandle,
                      &MemorySubClassData.Record.ArrayLink.MemoryManufacturer,
                      StringBuffer
                      );
      ASSERT_EFI_ERROR (Status);
#endif
      MemorySubClassData.Record.ArrayLink.MemorySerialNumber = (STRING_REF) 0;
#if (EFI_SPECIFICATION_VERSION >= 0x0002000A)
      Status = IfrLibNewString (
                StringPackHandle,
                &MemorySubClassData.Record.ArrayLink.MemorySerialNumber,
                StringBuffer
                );
      ASSERT_EFI_ERROR (Status);
#else
      Status = Hii->NewString (
                      Hii,
                      NULL,
                      HiiHandle,
                      &MemorySubClassData.Record.ArrayLink.MemorySerialNumber,
                      StringBuffer
                      );
      ASSERT_EFI_ERROR (Status);
#endif

      MemorySubClassData.Record.ArrayLink.MemoryPartNumber = (STRING_REF) 0;
#if (EFI_SPECIFICATION_VERSION >= 0x0002000A)
      Status = IfrLibNewString (StringPackHandle, &MemorySubClassData.Record.ArrayLink.MemoryPartNumber, StringBuffer);
      ASSERT_EFI_ERROR (Status);
#else
      Status = Hii->NewString (
                      Hii,
                      NULL,
                      HiiHandle,
                      &MemorySubClassData.Record.ArrayLink.MemoryPartNumber,
                      StringBuffer
                      );
      ASSERT_EFI_ERROR (Status);
#endif
      DimmMemorySize  = 0;
      MemorySubClassData.Record.ArrayLink.MemorySpeed       = 0;
      MemorySubClassData.Record.ArrayLink.MemoryDeviceSize  = 0;
      MemorySubClassData.Record.ArrayLink.MemoryType        = EfiMemoryTypeUnknown;
      MemorySubClassData.Record.ArrayLink.MemoryFormFactor  = EfiMemoryFormFactorDimm;
    }
    ///
    /// Generate Memory Device info (Type 17)
    ///
    Status = DataHub->LogData (
                        DataHub,
                        &gEfiMemorySubClassGuid,
                        &gEfiMemorySubClassDriverGuid,
                        EFI_DATA_RECORD_CLASS_DATA,
                        &MemorySubClassData,
                        sizeof (EFI_SUBCLASS_TYPE1_HEADER) + sizeof (EFI_MEMORY_ARRAY_LINK)
                        );
    if (EFI_ERROR (Status)) {
      goto CleanAndExit;
    }
    ///
    /// Memory Device Mapped Address (Type 20) is optional and it will not be generated by RC
    ///
// ...AMI_OVERRIDE... support Type 20
    if ((Populated) && (DimmMemorySize != 0)) {
      ///
      /// Generate Memory Device Mapped Address info (Type 20)
      ///
      MemorySubClassData.Header.Instance    = ArrayInstance;
      MemorySubClassData.Header.SubInstance = (UINT16) (Dimm + 1);
      MemorySubClassData.Header.RecordType  = EFI_MEMORY_DEVICE_START_ADDRESS_RECORD_NUMBER;

      MemorySubClassData.Record.DeviceStartAddress.MemoryDeviceStartAddress = RowConfArray[Dimm].BaseAddress;
      MemorySubClassData.Record.DeviceStartAddress.MemoryDeviceEndAddress = MemorySubClassData.Record.
          DeviceStartAddress.MemoryDeviceStartAddress +
        DimmMemorySize -
        1;
      ///
      /// 1 or 2 will be applicable for lock step mode
      ///
      MemorySubClassData.Record.DeviceStartAddress.MemoryDevicePartitionRowPosition       = 0xFF;

      MemorySubClassData.Record.DeviceStartAddress.PhysicalMemoryDeviceLink.ProducerName  = gEfiMemorySubClassDriverGuid;
      MemorySubClassData.Record.DeviceStartAddress.PhysicalMemoryDeviceLink.Instance      = ArrayInstance;
      MemorySubClassData.Record.DeviceStartAddress.PhysicalMemoryDeviceLink.SubInstance   = (UINT16) (Dimm + 1);
      MemorySubClassData.Record.DeviceStartAddress.PhysicalMemoryArrayLink.ProducerName   = gEfiMemorySubClassDriverGuid;
      MemorySubClassData.Record.DeviceStartAddress.PhysicalMemoryArrayLink.Instance       = ArrayInstance;
      MemorySubClassData.Record.DeviceStartAddress.PhysicalMemoryArrayLink.SubInstance = EFI_SUBCLASS_INSTANCE_NON_APPLICABLE;

      ///
      /// Set Interleave Data Depth and Position.
      ///
      if (((Dimm >= SA_MC_MAX_SLOTS) && (MemInfoHob->MemInfoData.DimmExist[Dimm - SA_MC_MAX_SLOTS])) ||
          ((Dimm < SA_MC_MAX_SLOTS) && (MemInfoHob->MemInfoData.DimmExist[Dimm + SA_MC_MAX_SLOTS]))
          ) {
        ///
        /// If DIMMs on both channels are populated then Interleaved Data Depth is 2 and Interleave Position is 1 or 2
        ///
        MemorySubClassData.Record.DeviceStartAddress.MemoryDeviceInterleaveDataDepth = (UINT8) (MaxSockets >> 1);
        MemorySubClassData.Record.DeviceStartAddress.MemoryDeviceInterleavePosition = (UINT8) (1 << (Dimm >= (MaxSockets >> 1)));
      } else {
        ///
        /// Interleaved Data Depth and Position is 1
        ///
        MemorySubClassData.Record.DeviceStartAddress.MemoryDeviceInterleaveDataDepth  = 1;
        MemorySubClassData.Record.DeviceStartAddress.MemoryDeviceInterleavePosition   = 1;
      }
      ///
      /// Generate Memory Device Mapped Address info (Type 20)
      ///
      Status = DataHub->LogData (
                          DataHub,
                          &gEfiMemorySubClassGuid,
                          &gEfiMemorySubClassDriverGuid,
                          EFI_DATA_RECORD_CLASS_DATA,
                          &MemorySubClassData,
                          sizeof (EFI_SUBCLASS_TYPE1_HEADER) + sizeof (EFI_MEMORY_DEVICE_START_ADDRESS)
                          );
      if (EFI_ERROR (Status)) {
        goto CleanAndExit;
      }
    }
// ...AMI_OVERRIDE... support Type 20 end
  }
  ///
  /// Generate Memory Array Mapped Address info (TYPE 19)
  ///
  MemorySubClassData.Header.Instance    = ArrayInstance;
  MemorySubClassData.Header.SubInstance = EFI_SUBCLASS_INSTANCE_NON_APPLICABLE;
  MemorySubClassData.Header.RecordType  = EFI_MEMORY_ARRAY_START_ADDRESS_RECORD_NUMBER;

  MemorySubClassData.Record.ArrayStartAddress.MemoryArrayStartAddress               = 0;
  MemorySubClassData.Record.ArrayStartAddress.MemoryArrayEndAddress                 = TotalMemorySize - 1;
  MemorySubClassData.Record.ArrayStartAddress.PhysicalMemoryArrayLink.ProducerName  = gEfiMemorySubClassDriverGuid;
  MemorySubClassData.Record.ArrayStartAddress.PhysicalMemoryArrayLink.Instance      = ArrayInstance;
  MemorySubClassData.Record.ArrayStartAddress.PhysicalMemoryArrayLink.SubInstance = EFI_SUBCLASS_INSTANCE_NON_APPLICABLE;
  //MemorySubClassData.Record.ArrayStartAddress.MemoryArrayPartitionWidth = (UINT16) (MaxSockets);  //AMI_OVERRIDE [EIP344598]
  MemorySubClassData.Record.ArrayStartAddress.MemoryArrayPartitionWidth = WidthCount;  //AMI_OVERRIDE [EIP344598]
  ///
  /// Generate Memory Array Mapped Address info (TYPE 19)
  ///
  Status = DataHub->LogData (
                      DataHub,
                      &gEfiMemorySubClassGuid,
                      &gEfiMemorySubClassDriverGuid,
                      EFI_DATA_RECORD_CLASS_DATA,
                      &MemorySubClassData,
                      sizeof (EFI_SUBCLASS_TYPE1_HEADER) + sizeof (EFI_MEMORY_ARRAY_START_ADDRESS)
                      );
CleanAndExit:
  (gBS->FreePool) (SmbusBuffer);
  (gBS->FreePool) (StringBuffer);
  return Status;
}
