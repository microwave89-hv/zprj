/** @file
  Processor Cache data records.

@copyright
  Copyright (c) 1999 - 2012 Intel Corporation. All rights reserved
  This software and associated documentation (if any) is furnished
  under a license and may only be used or copied in accordance
  with the terms of the license. Except as permitted by such
  license, no part of this software or documentation may be
  reproduced, stored in a retrieval system, or transmitted in any
  form or by any means without the express written consent of
  Intel Corporation.

  This file contains an 'Intel Peripheral Driver' and is
  licensed for Intel CPUs and chipsets under the terms of your
  license agreement with Intel or your vendor.  This file may
  be modified by the user, subject to additional terms of the
  license agreement

**/

///
/// External include files do NOT need to be explicitly specified in real EDKII
/// environment
///
#if !defined(EDK_RELEASE_VERSION) || (EDK_RELEASE_VERSION < 0x00020000)
#include "EdkIIGlueDxe.h"
#include "CpuAccess.h"
#include "CacheData.h"
#endif
///
/// This is the VFR compiler generated header file which defines the
/// string identifiers.
///
#include "CpuInitDxeStrDefs.h"

extern EFI_DATA_HUB_PROTOCOL     *mDataHub;
extern EFI_SUBCLASS_TYPE1_HEADER mCpuDataRecordHeader;

EFI_CACHE_CONVERTER mCacheConverter[] = {
  {
    1,
    0x09,
    32,
    EfiCacheAssociativity4Way,
    EfiCacheTypeInstruction
  },
  {
    1,
    0x0D,
    16,
    EfiCacheAssociativity4Way,
    EfiCacheTypeData
  },
  {
    2,
    0x21,
    256,
    EfiCacheAssociativity8Way,
    EfiCacheTypeUnified
  },
  {
    1,
    0x2C,
    32,
    EfiCacheAssociativity8Way,
    EfiCacheTypeData
  },
  {
    2,
    0x40,
    0,
    EfiCacheAssociativityUnknown,
    EfiCacheTypeUnknown
  },
  {
    3,
    0xD0,
    512,
    EfiCacheAssociativity4Way,
    EfiCacheTypeUnified
  },
  {
    3,
    0xD1,
    1024,
    EfiCacheAssociativity4Way,
    EfiCacheTypeUnified
  },
  {
    3,
    0xD2,
    2048,
    EfiCacheAssociativity4Way,
    EfiCacheTypeUnified
  },
  {
    3,
    0xD3,
    4096,
    EfiCacheAssociativity4Way,
    EfiCacheTypeUnified
  },
  {
    3,
    0xD4,
    8192,
    EfiCacheAssociativity4Way,
    EfiCacheTypeUnified
  },
  {
    3,
    0xD6,
    1024,
    EfiCacheAssociativity8Way,
    EfiCacheTypeUnified
  },
  {
    3,
    0xD7,
    2048,
    EfiCacheAssociativity8Way,
    EfiCacheTypeUnified
  },
  {
    3,
    0xD8,
    4096,
    EfiCacheAssociativity8Way,
    EfiCacheTypeUnified
  },
  {
    3,
    0xD9,
    8192,
    EfiCacheAssociativity8Way,
    EfiCacheTypeUnified
  },
  {
    3,
    0xDA,
    12288,
    EfiCacheAssociativity8Way,
    EfiCacheTypeUnified
  },
  {
    3,
    0xDC,
    1536,
    EfiCacheAssociativity12Way,
    EfiCacheTypeUnified
  },
  {
    3,
    0xDD,
    3072,
    EfiCacheAssociativity12Way,
    EfiCacheTypeUnified
  },
  {
    3,
    0xDE,
    6144,
    EfiCacheAssociativity12Way,
    EfiCacheTypeUnified
  },
  {
    3,
    0xDF,
    12288,
    EfiCacheAssociativity12Way,
    EfiCacheTypeUnified
  },
  {
    3,
    0xE0,
    18432,
    EfiCacheAssociativity12Way,
    EfiCacheTypeUnified
  },
  {
    3,
    0xE2,
    2048,
    EfiCacheAssociativity16Way,
    EfiCacheTypeUnified
  },
  {
    3,
    0xE3,
    4096,
    EfiCacheAssociativity16Way,
    EfiCacheTypeUnified
  },
  {
    3,
    0xE4,
    8192,
    EfiCacheAssociativity16Way,
    EfiCacheTypeUnified
  },
  {
    3,
    0xE5,
    16384,
    EfiCacheAssociativity16Way,
    EfiCacheTypeUnified
  },
  {
    3,
    0xE6,
    24576,
    EfiCacheAssociativity16Way,
    EfiCacheTypeUnified
  },
  {
    3,
    0xEA,
    12288,
    EfiCacheAssociativity24Way,
    EfiCacheTypeUnified
  },
  {
    3,
    0xEB,
    18432,
    EfiCacheAssociativity24Way,
    EfiCacheTypeUnified
  },
  {
    3,
    0xEC,
    24567,
    EfiCacheAssociativity24Way,
    EfiCacheTypeUnified
  },
  {
    0,
    0xFF,
    0,
    0,
    0
  }
};

///
/// Convert Cache Type Field to SMBIOS format
///
#define SMBIOS_CACHE_TYPE_MAX 5
UINT8 SmbiosCacheTypeFieldConverter[SMBIOS_CACHE_TYPE_MAX] = {
  EfiCacheTypeUnknown,
  EfiCacheTypeData,
  EfiCacheTypeInstruction,
  EfiCacheTypeUnified,
  EfiCacheTypeOther
};

UINT8 mCacheInstance[EFI_CACHE_LMAX] = { 0, 0, 0, 0 };

EFI_SUBCLASS_TYPE1_HEADER mCacheDataRecordHeader = {
  EFI_CACHE_SUBCLASS_VERSION,         ///< Version
  sizeof (EFI_SUBCLASS_TYPE1_HEADER), ///< Header Size
  0,                                  ///< Instance, Initialize later
  0,                                  ///< SubInstance, Initialize later to Cache Level
  0                                   ///< RecordType, Initialize later
};

/**
  This function gets called with the processor number and will log all cache data to data hub
  pertaining to this processor.

  @param[in] CpuNumber - Processor Number
  @param[in] CacheInformation - Cache information get from cpuid instruction

  @retval EFI_OUT_OF_RESOURCES - Failed to allocate required POOL for record buffer.
  @retval EFI_SUCCESS - successful to update cache data
**/
EFI_STATUS
InitializeCacheData (
  IN UINTN              CpuNumber,
  IN EFI_CPUID_REGISTER *CacheInformation
  )
{
  EFI_STATUS                   Status;
  UINT32                       HeaderSize;
  UINT32                       TotalSize;
  CPU_CACHE_DATA_RECORD_BUFFER RecordBuffer;
  UINT8                        Index1;
  UINT8                        CacheLevel;
  UINT8                        LxCacheType;
  UINT32                       Ways;
  UINT32                       Partitions;
  UINT32                       LineSets;
  UINT32                       Sets;
  UINT32                       LxCacheSize;
  EFI_CPUID_REGISTER           CpuidRegisters;

  ///
  /// Only log CPU socket level information.
  ///
  if (CpuNumber != 0) {
    return EFI_SUCCESS;
  }

  mCacheDataRecordHeader.Instance = (UINT16) (CpuNumber + 1);

  HeaderSize                      = sizeof (EFI_SUBCLASS_TYPE1_HEADER);
  RecordBuffer.Raw                = AllocatePool (HeaderSize + CPU_CACHE_DATA_MAXIMUM_LENGTH);
  if (RecordBuffer.Raw == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  for (Index1 = 0;; Index1++) {
    EfiCpuidExt (CPUID_CACHE_PARAMS, Index1, &CpuidRegisters);
    if ((CpuidRegisters.RegEax & V_CPUID_CACHE_TYPE_MASK) == 0) {
      break;
    }

    Ways        = ((CpuidRegisters.RegEbx >> B_CPUID_CACHE_PARAMS_WAYS_SHIFT) & 0x3FF) + 1;
    Partitions  = ((CpuidRegisters.RegEbx >> B_CPUID_CACHE_PARAMS_PARTITIONS_SHIFT) & 0x3FF) + 1;
    LineSets    = (CpuidRegisters.RegEbx & 0xFFF) + 1;
    Sets        = CpuidRegisters.RegEcx + 1;

    CacheLevel  = (UINT8) (CpuidRegisters.RegEax & V_CPUID_CACHE_LEVEL_MASK) >> B_CPUID_CACHE_LEVEL_SHIFT;
    LxCacheSize = (Ways * Partitions * LineSets * Sets) / 1024;
    LxCacheType = (UINT8) (CpuidRegisters.RegEax & V_CPUID_CACHE_TYPE_MASK);

    CopyMem (RecordBuffer.Raw, &mCacheDataRecordHeader, HeaderSize);

    mCacheInstance[CacheLevel - 1]++;
    RecordBuffer.DataRecord->DataRecordHeader.Instance    = mCacheInstance[CacheLevel - 1];
    RecordBuffer.DataRecord->DataRecordHeader.SubInstance = CacheLevel;

    ///
    ///  Record Type 1
    ///
    RecordBuffer.DataRecord->DataRecordHeader.RecordType        = CacheSizeRecordType;
    TotalSize = HeaderSize + sizeof (EFI_CACHE_SIZE_DATA);
    RecordBuffer.DataRecord->VariableRecord.CacheSize.Value = (UINT16) LxCacheSize;
    RecordBuffer.DataRecord->VariableRecord.CacheSize.Exponent = 10;
    Status = LogCacheData (mDataHub, RecordBuffer.Raw, TotalSize);

    ///
    ///  Record Type 2
    ///
    RecordBuffer.DataRecord->DataRecordHeader.RecordType              = MaximumSizeCacheRecordType;
    TotalSize = HeaderSize + sizeof (EFI_MAXIMUM_CACHE_SIZE_DATA);
    RecordBuffer.DataRecord->VariableRecord.MaximumCacheSize.Value = (UINT16) LxCacheSize;
    RecordBuffer.DataRecord->VariableRecord.MaximumCacheSize.Exponent = 10;
    Status = LogCacheData (mDataHub, RecordBuffer.Raw, TotalSize);

    ///
    ///  Record Type 3
    ///
    RecordBuffer.DataRecord->DataRecordHeader.RecordType        = CacheSpeedRecordType;
    TotalSize = HeaderSize + sizeof (EFI_CACHE_SPEED_DATA);
    RecordBuffer.DataRecord->VariableRecord.CacheSpeed.Exponent = 0;
    RecordBuffer.DataRecord->VariableRecord.CacheSpeed.Value = 0;
    Status = LogCacheData (mDataHub, RecordBuffer.Raw, TotalSize);

    ///
    ///  Record Type 4
    ///
    RecordBuffer.DataRecord->DataRecordHeader.RecordType  = CacheSocketRecordType;
    TotalSize = HeaderSize + sizeof (EFI_CACHE_SOCKET_DATA);
    RecordBuffer.DataRecord->VariableRecord.CacheSocket = 0;
    ///
    /// CacheDesignation[Index1];
    ///
    Status = LogCacheData (mDataHub, RecordBuffer.Raw, TotalSize);

    ///
    ///  Record Type 5
    ///
    RecordBuffer.DataRecord->DataRecordHeader.RecordType  = CacheSramTypeRecordType;
    TotalSize = HeaderSize + sizeof (EFI_CACHE_SRAM_TYPE_DATA);
    ZeroMem (
            &RecordBuffer.DataRecord->VariableRecord.CacheSramType,
            sizeof (EFI_CACHE_SRAM_TYPE_DATA)
            );
    RecordBuffer.DataRecord->VariableRecord.CacheSramType.Synchronous = TRUE;
    Status = LogCacheData (mDataHub, RecordBuffer.Raw, TotalSize);

    ///
    ///  Record Type 6, since record same as Type 5
    ///
    RecordBuffer.DataRecord->DataRecordHeader.RecordType  = CacheInstalledSramTypeRecordType;
    Status = LogCacheData (mDataHub, RecordBuffer.Raw, TotalSize);

    ///
    ///  Record Type 7
    ///
    RecordBuffer.DataRecord->DataRecordHeader.RecordType    = CacheErrorTypeRecordType;
    TotalSize = HeaderSize + sizeof (EFI_CACHE_ERROR_TYPE_DATA);
    RecordBuffer.DataRecord->VariableRecord.CacheErrorType = EfiCacheErrorSingleBit;
    Status = LogCacheData (mDataHub, RecordBuffer.Raw, TotalSize);

    ///
    ///  Record Type 8
    ///
    RecordBuffer.DataRecord->DataRecordHeader.RecordType  = CacheTypeRecordType;
    TotalSize = HeaderSize + sizeof (EFI_CACHE_TYPE_DATA);
    ///
    /// If cache type is larger or equal than 5, this is undefined type so mark it as "Other" Cache type.
    ///
    if (LxCacheType >= SMBIOS_CACHE_TYPE_MAX) {
      LxCacheType = SMBIOS_CACHE_TYPE_MAX - 1;
    }
    RecordBuffer.DataRecord->VariableRecord.CacheType = SmbiosCacheTypeFieldConverter[LxCacheType];
    Status = LogCacheData (mDataHub, RecordBuffer.Raw, TotalSize);

    ///
    ///  Record Type 9
    ///
    RecordBuffer.DataRecord->DataRecordHeader.RecordType        = CacheAssociativityRecordType;
    TotalSize = HeaderSize + sizeof (EFI_CACHE_ASSOCIATIVITY_DATA);
    ///
    /// Convert Associativity Ways to SMBIOS format
    ///
    switch (Ways) {
      case 2:
        Ways = EfiCacheAssociativity2Way;
        break;
      case 4:
        Ways = EfiCacheAssociativity4Way;
        break;
      case 8:
        Ways = EfiCacheAssociativity8Way;
        break;
      case 12:
        Ways = EfiCacheAssociativity12Way;
        break;
      case 16:
        Ways = EfiCacheAssociativity16Way;
        break;
      case 24:
        Ways = EfiCacheAssociativity24Way;
        break;
      case 32:
        Ways = EfiCacheAssociativity32Way;
        break;
      case 48:
        Ways = EfiCacheAssociativity48Way;
        break;
      case 64:
        Ways = EfiCacheAssociativity64Way;
        break;
      default:
        Ways = EfiCacheAssociativityOther;
        break;
    }
    RecordBuffer.DataRecord->VariableRecord.CacheAssociativity = Ways;
    Status = LogCacheData (mDataHub, RecordBuffer.Raw, TotalSize);

    ///
    ///  Record Type 10
    ///
    RecordBuffer.DataRecord->DataRecordHeader.RecordType                = CacheConfigRecordType;
    TotalSize = HeaderSize + sizeof (EFI_CACHE_CONFIGURATION_DATA);
    RecordBuffer.DataRecord->VariableRecord.CacheConfig.Level = CacheLevel;
    RecordBuffer.DataRecord->VariableRecord.CacheConfig.Socketed = EFI_CACHE_NOT_SOCKETED;
    RecordBuffer.DataRecord->VariableRecord.CacheConfig.Reserved2 = 0;
    RecordBuffer.DataRecord->VariableRecord.CacheConfig.Location = EfiCacheInternal;
    RecordBuffer.DataRecord->VariableRecord.CacheConfig.Enable = EFI_CACHE_ENABLED;
    RecordBuffer.DataRecord->VariableRecord.CacheConfig.OperationalMode = EfiCacheWriteBack;
    RecordBuffer.DataRecord->VariableRecord.CacheConfig.Reserved1 = 0;
    Status = LogCacheData (mDataHub, RecordBuffer.Raw, TotalSize);

    ///
    /// Cache Association. Processor Record Type 17
    ///
    TotalSize = HeaderSize + sizeof (EFI_CACHE_ASSOCIATION_DATA);
    RecordBuffer.DataRecord->VariableRecord.CacheAssociation.ProducerName = gEfiProcessorProducerGuid;
    ///
    /// RecordBuffer.DataRecord->VariableRecord.CacheAssociation.ProducerInstance = (UINT16)Instance;
    ///
    RecordBuffer.DataRecord->VariableRecord.CacheAssociation.Instance = RecordBuffer.DataRecord->DataRecordHeader.Instance;
    RecordBuffer.DataRecord->VariableRecord.CacheAssociation.SubInstance = RecordBuffer.DataRecord->DataRecordHeader.SubInstance;
    CopyMem (RecordBuffer.Raw, &mCpuDataRecordHeader, HeaderSize);
    RecordBuffer.DataRecord->DataRecordHeader.RecordType  = CacheAssociationRecordType;
    Status = LogCpuData (mDataHub, RecordBuffer.Raw, TotalSize);
  }

  FreePool (RecordBuffer.Raw);
  return EFI_SUCCESS;
}

/**
  Log cache data into data hub

  @param[in] DataHub - Pointer to the DataHub protocol that will be updated
  @param[in] Buffer  - Data buffer which will be updated into DataHub
  @param[in] Size    - The size of data buffer

  @retval EFI_STATUS - status code for logging data into dat hub
**/
EFI_STATUS
LogCacheData (
  EFI_DATA_HUB_PROTOCOL *DataHub,
  UINT8                 *Buffer,
  UINT32                Size
  )
{
  EFI_STATUS Status;

  Status = DataHub->LogData (
                  DataHub,
                  &gEfiCacheSubClassGuid,
                  &gEfiProcessorProducerGuid,
                  EFI_DATA_RECORD_CLASS_DATA,
                  Buffer,
                  Size
                  );
  return Status;
}
