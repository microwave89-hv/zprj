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
// $Header: /Alaska/BIN/Chipset/Intel/NorthBridge/Haswell/Intel SystemAgent NB Chipset/SystemAgentWrap/MiscSubclass/MiscSubclassDxe.c 1     2/08/12 4:36a Yurenlai $
//
// $Revision: 1 $
//
// $Date: 2/08/12 4:36a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Chipset/Intel/NorthBridge/Haswell/Intel SystemAgent NB Chipset/SystemAgentWrap/MiscSubclass/MiscSubclassDxe.c $
// 
// 1     2/08/12 4:36a Yurenlai
// Intel Haswell/NB eChipset initially releases.
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:        MiscSubclassDxe.c
//
// Description: This file for init Hii data base in BIOS id.
//             
//<AMI_FHDR_END>
//*************************************************************************

//---------------------------------------------------------------------------
// Include(s)
//---------------------------------------------------------------------------

#include <Efi.h>
#include <token.h>
#include <AmiLib.h>
#include <AmiDxeLib.h>
#include <Setup.h>
#include <Dxe.h>
#include <PCI.h>
#include <AmiHobs.h>
#include <AmiCspLib.h>

// Produced Protocols

// Consumed Protocols

#include <Protocol\DataHub.h>
#include <Include\DataHubSubClass.h>

#if EFI_SPECIFICATION_VERSION >= 0x2000A
#include "Include\UefiHii.h"
#include "Protocol\HiiDatabase.h"
#include "Protocol\HiiString.h"
#else
#include <Protocol/Hii.h>
#endif

//---------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//---------------------------------------------------------------------------
// Constant Definition(s)

// Macro Definition(s)
#define EFI_MISC_SUBCLASS_GUID \
{ 0x772484B2, 0x7482, 0x4b91, 0x9F, 0x9A, 0xAD, 0x43, 0xF8, 0x1C, 0x58, 0x81 }

#define EFI_MISC_SUBCLASS_DRIVER_GUID \
  { 0xF50E702C, 0x8653, 0x4CDE, 0xBB, 0xCE, 0x43, 0xB4, 0xD5, 0x5B, 0x34, 0xB8 }

// Type Definition(s)

#define EFI_MISC_SUBCLASS_VERSION     0x0100
#define EFI_DATA_RECORD_CLASS_DATA          0x0000000000000004
#define EFI_MISC_BIOS_VENDOR_RECORD_NUMBER  0x00000002

#define EFI_SUBCLASS_INSTANCE_NON_APPLICABLE 0xFFFF  //16 bit
// Function Prototype(s)

//---------------------------------------------------------------------------
// Variable and External Declaration(s)
//---------------------------------------------------------------------------
// Variable Declaration(s)

// GUID Definition(s)
EFI_GUID gEfiMiscSubClassGuid   = EFI_MISC_SUBCLASS_GUID;
EFI_GUID gEfiMiscSubClassDriverGuid = EFI_MISC_SUBCLASS_DRIVER_GUID;
EFI_GUID gEfiDataHubProtocolGuid = EFI_DATA_HUB_PROTOCOL_GUID;

// Protocol Definition(s)

// External Declaration(s)

// Function Definition(s)
EFI_STATUS InstallMiscSubClassData (
 IN EFI_HANDLE       ImageHandle
);


typedef struct {
  UINT8   LastPciBus;
} EFI_MISC_LAST_PCI_BUS;

typedef struct {
  UINT32  Reserved1                         :2;
  UINT32  Unknown                           :1;
  UINT32  BiosCharacteristicsNotSupported   :1;
  UINT32  IsaIsSupported                    :1;
  UINT32  McaIsSupported                    :1;
  UINT32  EisaIsSupported                   :1;
  UINT32  PciIsSupported                    :1;
  UINT32  PcmciaIsSupported                 :1;
  UINT32  PlugAndPlayIsSupported            :1;
  UINT32  ApmIsSupported                    :1;
  UINT32  BiosIsUpgradable                  :1;
  UINT32  BiosShadowingAllowed              :1;
  UINT32  VlVesaIsSupported                 :1;
  UINT32  EscdSupportIsAvailable            :1;
  UINT32  BootFromCdIsSupported             :1;
  UINT32  SelectableBootIsSupported         :1;
  UINT32  RomBiosIsSocketed                 :1;
  UINT32  BootFromPcmciaIsSupported         :1;
  UINT32  EDDSpecificationIsSupported       :1;
  UINT32  JapaneseNecFloppyIsSupported      :1;
  UINT32  JapaneseToshibaFloppyIsSupported  :1;
  UINT32  Floppy525_360IsSupported          :1;
  UINT32  Floppy525_12IsSupported           :1;
  UINT32  Floppy35_720IsSupported           :1;
  UINT32  Floppy35_288IsSupported           :1;
  UINT32  PrintScreenIsSupported            :1;
  UINT32  Keyboard8042IsSupported           :1;
  UINT32  SerialIsSupported                 :1;
  UINT32  PrinterIsSupported                :1;
  UINT32  CgaMonoIsSupported                :1;
  UINT32  NecPc98                           :1;
  UINT32  AcpiIsSupported                   :1;
  UINT32  UsbLegacyIsSupported              :1;
  UINT32  AgpIsSupported                    :1;
  UINT32  I20BootIsSupported                :1;
  UINT32  Ls120BootIsSupported              :1;
  UINT32  AtapiZipDriveBootIsSupported      :1;
  UINT32  Boot1394IsSupported               :1;
  UINT32  SmartBatteryIsSupported           :1;
  UINT32  BiosBootSpecIsSupported           :1;
  UINT32  FunctionKeyNetworkBootIsSupported :1;
  UINT32  TargetContentDistributionEnabled  :1; 
  UINT32  Reserved                          :21;
} EFI_MISC_BIOS_CHARACTERISTICS;

typedef struct {
  UINT32  BiosReserved                      :16;
  UINT32  SystemReserved                    :16;
  UINT32  Reserved                          :32;
} EFI_MISC_BIOS_CHARACTERISTICS_EXTENSION;

typedef struct {
  STRING_REF                      BiosVendor;
  STRING_REF                      BiosVersion;
  STRING_REF                      BiosReleaseDate;
  EFI_PHYSICAL_ADDRESS            BiosStartingAddress;
  EFI_EXP_BASE2_DATA              BiosPhysicalDeviceSize;
  EFI_MISC_BIOS_CHARACTERISTICS   BiosCharacteristics1;
  EFI_MISC_BIOS_CHARACTERISTICS_EXTENSION  BiosCharacteristics2;
  UINT8                           BiosMajorRelease;
  UINT8                           BiosMinorRelease;
  UINT8                           BiosEmbeddedFirmwareMajorRelease;
  UINT8                           BiosEmbeddedFirmwareMinorRelease;
} EFI_MISC_BIOS_VENDOR;   

typedef union {
  EFI_MISC_LAST_PCI_BUS                         LastPciBus;
  EFI_MISC_BIOS_VENDOR                          MiscBiosVendor;
} EFI_MISC_SUBCLASS_RECORDS;

typedef struct {
  EFI_SUBCLASS_TYPE1_HEADER       Header;
  EFI_MISC_SUBCLASS_RECORDS       Record;
} EFI_MISC_SUBCLASS_DRIVER_DATA;

extern UINT8           MiscSubclass[];
    
//---------------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   MiscSubclassDxe_Init
//
// Description: This function is the entry point for MiscSubclass DXE driver.
//              This function initializes the MiscSubclass in DXE phase.
//
// Input:       ImageHandle - Image handle
//              SystemTable - Pointer to the system table
//
// Output:      EFI_SUCCESS
//
// Notes:       
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS MiscSubclassDxe_Init (
    IN EFI_HANDLE       ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable )
{
    EFI_STATUS              Status = EFI_SUCCESS;

    InitAmiLib(ImageHandle, SystemTable);

    Status = InstallMiscSubClassData (ImageHandle);
    ASSERT_EFI_ERROR(Status);

    return EFI_SUCCESS;
}


#if EFI_SPECIFICATION_VERSION >= 0x2000A
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   PreparePackageList
//
// Description: 
//          Assemble EFI_HII_PACKAGE_LIST according to the passed in packages.    
//
// Input:   NumberOfPackages  -  Number of packages.
//          GuidId            -  Package GUID.      
//              
//
// Output:  Pointer of EFI_HII_PACKAGE_LIST_HEADER.    
//       
// Notes:       
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_HII_PACKAGE_LIST_HEADER *
PreparePackageList (
  IN UINTN                    NumberOfPackages,
  IN EFI_GUID                 *GuidId,
  IN ...
)
{
  va_list                     Marker;
  EFI_HII_PACKAGE_LIST_HEADER *PackageListHeader = NULL;
  UINT8                       *PackageListData;
  UINT32                      PackageListLength;
  UINT32                      PackageLength;
  EFI_HII_PACKAGE_HEADER      PackageHeader;
  UINT8                       *PackageArray;
  UINTN                       Index;

  PackageListLength = sizeof (EFI_HII_PACKAGE_LIST_HEADER);

  va_start (Marker, GuidId);
  for (Index = 0; Index < NumberOfPackages; Index++) {
    pBS->CopyMem (&PackageLength, va_arg (Marker, VOID *), sizeof (UINT32));
    PackageListLength += (PackageLength - sizeof (UINT32));
  }
  va_end (Marker);

  //
  // Include the lenght of EFI_HII_PACKAGE_END
  //
  PackageListLength += sizeof (EFI_HII_PACKAGE_HEADER);
  //PackageListHeader = EfiLibAllocateZeroPool (PackageListLength);

 // PackageListHeader = EfiLibAllocatePool (PackageListLength);
  pBS->AllocatePool (EfiBootServicesData, PackageListLength, &PackageListHeader);

  if (PackageListHeader != NULL) {
    pBS->SetMem (PackageListHeader, PackageListLength, 0);
  }

  ASSERT (PackageListHeader != NULL);
  pBS->CopyMem (&PackageListHeader->PackageListGuid, GuidId, sizeof (EFI_GUID));
  PackageListHeader->PackageLength = PackageListLength;

  PackageListData = ((UINT8 *) PackageListHeader) + sizeof (EFI_HII_PACKAGE_LIST_HEADER);

  va_start (Marker, GuidId);
  for (Index = 0; Index < NumberOfPackages; Index++) {
    PackageArray = (UINT8 *) va_arg (Marker, VOID *);
    pBS->CopyMem (&PackageLength, PackageArray, sizeof (UINT32));
    PackageLength  -= sizeof (UINT32);
    PackageArray += sizeof (UINT32);
    pBS->CopyMem (PackageListData, PackageArray, PackageLength);
    PackageListData += PackageLength;
  }
  va_end (Marker);

  //
  // Append EFI_HII_PACKAGE_END
  //
  PackageHeader.Type = EFI_HII_PACKAGE_END;
  PackageHeader.Length = sizeof (EFI_HII_PACKAGE_HEADER);
  pBS->CopyMem (PackageListData, &PackageHeader, PackageHeader.Length);

  return PackageListHeader;
}

#else
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   PreparePackages
//
// Description: 
//          Assemble EFI_HII_PACKAGE_LIST according to the passed in packages.    
//
// Input:   NumberOfPackages  -  Number of packages.
//          GuidId            -  Package GUID.      
//              
//
// Output:  Pointer of EFI_HII_PACKAGE_LIST_HEADER.    
//       
// Notes:       
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_HII_PACKAGES *
PreparePackages (
  IN      UINTN               NumberOfPackages,
  IN      EFI_GUID            *GuidId,
  IN      ...
)
{
  va_list           args;
  EFI_HII_PACKAGES  *HiiPackages;
  VOID              **Package;
  UINTN             Index;
  EFI_STATUS        Status;
  ASSERT (NumberOfPackages > 0);

  Status = pBS->AllocatePool(EfiBootServicesData, (sizeof (EFI_HII_PACKAGES)) + NumberOfPackages * sizeof (VOID *), &HiiPackages);
  HiiPackages->GuidId           = GuidId;
  HiiPackages->NumberOfPackages = NumberOfPackages;
  Package                       = (VOID **) (((UINT8 *) HiiPackages) + sizeof (EFI_HII_PACKAGES));

  va_start (args, GuidId);

  for (Index = 0; Index < NumberOfPackages; Index++) {
    *Package = va_arg (args, VOID *);
    Package++;
  }

  va_end (args);

  return HiiPackages;
}

#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   InstallMiscSubClassData
//
// Description: 
//          Install MiscSubClassData for IgdOpRegion.    
//
// Input:   ImageHandle  
//               
//
// Output:  Status.    
//       
// Notes:       
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS InstallMiscSubClassData (
  IN EFI_HANDLE       ImageHandle
)
{
  EFI_STATUS                      Status;
  EFI_DATA_HUB_PROTOCOL           *DataHub;
  EFI_MISC_SUBCLASS_DRIVER_DATA   MiscSubClassData;
  EFI_STRING                      StringBuffer;
  EFI_HII_HANDLE                  HiiHandle;
#if EFI_SPECIFICATION_VERSION >= 0x2000A
  CHAR8                           Language[]="en-US";
  EFI_HII_DATABASE_PROTOCOL       *HiiDatabase;
  EFI_HII_STRING_PROTOCOL         *HiiString;
  EFI_HII_PACKAGE_LIST_HEADER     *PackageList;
#else
  EFI_HII_PROTOCOL                *Hii;
  EFI_HII_PACKAGES                *PackageList;
#endif

  Status = pBS->LocateProtocol (&gEfiDataHubProtocolGuid, NULL, &DataHub);
  ASSERT_EFI_ERROR (Status);

#if EFI_SPECIFICATION_VERSION >= 0x2000A
  // There should only be one HII Database protocol
  Status = pBS->LocateProtocol (&gEfiHiiDatabaseProtocolGuid, NULL, &HiiDatabase);
  ASSERT_EFI_ERROR (Status);

  Status = pBS->LocateProtocol (&gEfiHiiStringProtocolGuid, NULL, &HiiString);
  ASSERT_EFI_ERROR (Status);

#else
  // There should only be one HII protocol
  Status = pBS->LocateProtocol (&gEfiHiiProtocolGuid, NULL, &Hii);
  ASSERT_EFI_ERROR (Status);
#endif

  MiscSubClassData.Header.Version     = EFI_MISC_SUBCLASS_VERSION;
  MiscSubClassData.Header.HeaderSize  = sizeof (EFI_SUBCLASS_TYPE1_HEADER);
  MiscSubClassData.Header.Instance    = 1;
  MiscSubClassData.Header.SubInstance = EFI_SUBCLASS_INSTANCE_NON_APPLICABLE;
  MiscSubClassData.Header.RecordType  = EFI_MISC_BIOS_VENDOR_RECORD_NUMBER;

  Status = pBS->AllocatePool(EfiBootServicesData, (sizeof (CHAR16)) * 100, &StringBuffer);
  pBS->SetMem(StringBuffer, (sizeof(CHAR16)) * 100, 0);

  Strcpy ((char*)StringBuffer, CONVERT_TO_STRING(BIOSID));

#if EFI_SPECIFICATION_VERSION >= 0x2000A

  PackageList = PreparePackageList (1, &gEfiMiscSubClassDriverGuid, MiscSubclass);

  Status = HiiDatabase->NewPackageList (
                          HiiDatabase,
                          PackageList,
                          ImageHandle,
                          &HiiHandle
                          );

#else
  PackageList = PreparePackages (1, &gEfiMiscSubClassDriverGuid, MiscSubclass);
  Status      = Hii->NewPack (Hii, PackageList, &HiiHandle);
#endif
  ASSERT_EFI_ERROR (Status);
  pBS->FreePool (PackageList);

  MiscSubClassData.Record.MiscBiosVendor.BiosVersion = (STRING_REF)0;
#if EFI_SPECIFICATION_VERSION >= 0x2000A
  Status = HiiString->NewString (HiiString, HiiHandle, &MiscSubClassData.Record.MiscBiosVendor.BiosVersion, Language, NULL, StringBuffer, NULL);

//  Status = HiiLibSetString(HiiHandle, MiscSubClassData.Record.MiscBiosVendor.BiosVersion, StringBuffer);
  if (EFI_ERROR(Status)) return Status;
#else
  Hii->NewString (
    Hii,
    NULL,
    HiiHandle,
    &MiscSubClassData.Record.MiscBiosVendor.BiosVersion,
    StringBuffer
  );
#endif


  Status = DataHub->LogData (
             DataHub,
             &gEfiMiscSubClassGuid,
             &gEfiMiscSubClassDriverGuid,
             EFI_DATA_RECORD_CLASS_DATA,
             &MiscSubClassData,
             sizeof (EFI_SUBCLASS_TYPE1_HEADER) + sizeof (EFI_MISC_BIOS_VENDOR)
           );

  pBS->FreePool(StringBuffer);

  return Status;
}

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
