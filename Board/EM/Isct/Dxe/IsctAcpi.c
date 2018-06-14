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
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ISCT/IsctDxeAcpi/IsctAcpi.c 14    7/16/14 12:20a Mirayang $
//
// $Revision: 14 $
//
// $Date: 7/16/14 12:20a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ISCT/IsctDxeAcpi/IsctAcpi.c $
// 
// 14    7/16/14 12:20a Mirayang
// Add complete function with iRST.
// 
// 13    7/11/14 10:51a Mirayang
// 
// 12    7/11/14 10:30a Mirayang
// Fix iRST bulid error.
// 
// 11    7/08/14 5:10a Mirayang
// EIP142924 iSCT 5.0 for Shark Bay Platform
// 
// 10    5/13/14 4:51a Mirayang
// [TAG]  		EIP167033
// [Category]  	Improvement
// [Description]  	Variable's attribute needs to be reviewed by iSCT
// component driver
// [Files]  		IsctAcpi.c
// 
// 9     8/02/13 3:26a Joshchou
// 
// 8     6/02/13 10:52a Joshchou
// [TAG]  		EIP125348
// [Category]  	Improvement
// [Description]  	[SBY] Intel Smart Connect Technology BIOS Sample Code
// 052413 Update
// 
// 7     3/27/13 9:14a Bensonlai
// [TAG]  		EIP118307
// [Category]  	New Feature
// [Description]  	Implementation of the ISCT Platform Design
// Specification 0.8.
// [Files]  		Isct.asl, IsctAcpi.c, IsctAcpi.mak
// 
// 6     12/05/12 3:32a Bensonlai
// [TAG]  		EIP107708
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	RTC can't wake
// [RootCause]  	RTC didn't support Actual time yet.
// [Solution]  	RTC only supports "duration in seconds".
// [Files]  		IsctAcpi.c
// 
// 5     11/20/12 8:02a Bensonlai
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Because GlobalNvsArea.h has changed the ICNF to
// IsctCfg, we modified the ICNF to IsctCfg.
// 
// 4     10/29/12 2:32a Bensonlai
// [TAG]  		EIP105047
// [Category]  	Improvement
// [Description]  	ISCT build error when RapidStart_SUPPORT is Disabled in
// Sharkbay platform.
// 
// 3     10/15/12 6:55a Bensonlai
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	[Category] Improvement
// [Description] Rename the IFFS to RapidStart for updating the
// 4.6.5.3_iRST-RC_071_006
// [Files]        IsctAcpi.c
// 
// 2     9/26/12 2:04a Bensonlai
// [TAG]  		None
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	System hung up when ISCT enabled on the debug mode
// [RootCause]  	Because we don't check the EFI stauts and use the
// ASSERT_EFI_ERROR directly.
// [Solution]  	Added the EFI stauts for checking.
// [Files]  		IsctAcpi.c, IsctWakeReason.c and IsctWakeReason.c
// 
// 1     9/02/12 11:19p Bensonlai
// Intel Smart Connect Technology initially releases.
//
//
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:  IsctAcpi.c
//
// Description:	This Dxe driver will initialize ISCT Persistent Data Variable and also verify ISCT Store valid or not
//
//<AMI_FHDR_END>
//**********************************************************************

#if !defined(EDK_RELEASE_VERSION) || (EDK_RELEASE_VERSION < 0x00020000)
#include "EdkIIGlueDxe.h"


#include EFI_GUID_DEFINITION (AcpiVariable)
#include EFI_GUID_DEFINITION (IsctAcpiTableStorage)
#include EFI_GUID_DEFINITION (IsctPersistentData)

#include EFI_PROTOCOL_PRODUCER (IsctNvsArea)
#include EFI_PROTOCOL_CONSUMER (FirmwareVolume)
#include EFI_PROTOCOL_CONSUMER (IgdOpRegion)
#include EFI_PROTOCOL_DEPENDENCY (AcpiTable)

#endif

#include "IsctAcpi.h"
ISCT_NVS_AREA_PROTOCOL mIsctNvsAreaProtocol;

//
// GUID to AMI_ISCT Module
//
#if !defined(EDK_RELEASE_VERSION) || (EDK_RELEASE_VERSION < 0x00020000)

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

#pragma pack ()\

EFI_STATUS
IsctDxeUpdateSetupVariableToACPIGNVS (
  IN OUT SETUP_DATA                        *gSetupData
  )
/*++

Routine Description:

  Update ISCT SetupVariable to ACPI GNVS

Arguments:

Returns:

  EFI_SUCCESS    Isct ACPI GNVS are updated successfully
  EFI_NOT_FOUND  Isct ACPI GNVS not found

--*/
{
  EFI_STATUS                    Status;
  EFI_GUID                      gEfiGlobalNvsAreaProtocolGuid = EFI_GLOBAL_NVS_AREA_PROTOCOL_GUID;
  EFI_GLOBAL_NVS_AREA_PROTOCOL  *GlobalNvsAreaProtocol;
  EFI_GLOBAL_NVS_AREA           *mGlobalNvsAreaPtr;

  Status = gBS->LocateProtocol( &gEfiGlobalNvsAreaProtocolGuid, NULL, &GlobalNvsAreaProtocol );
  if ( EFI_ERROR(Status) ) {
      return Status;
  }
  mGlobalNvsAreaPtr = GlobalNvsAreaProtocol->Area;

  //
  // Intel Smart Connect Technology 4.0 Spec (Document Number: 507302)
  //
  // Table 4-2. IAOE Control Method GABS
  // Bit0    Intel Smart Connect Technology Configured: 0 = Disabled, 1 = Enabled
  // Bit1    Intel Smart Connect Technology Notification Control: 0 = Unsupported, 1 = Supported
  // Bit2    Intel Smart Connect Technology WLAN Power Control:0 = Unsupported, 1 = Supported
  // Bit3    Intel Smart Connect Technology WWAN Power Control: 0 = Unsupported, 1 = Supported
  // Bit4    Must be set to 1
  // Bit5    Sleep duration value format: 0 = Actual time, 1 = duration in seconds (see SASD for actual format)
  // Bit6    RF Kill Support (Radio On/Off): 0 = Soft Switch, 1 = Physical Switch
  // Bit7    Reserved (must set to 0)
  //
  // ISCT configuration
  //
  mGlobalNvsAreaPtr->IsctCfg = 0;
  if (gSetupData->IsctConfiguration) {
    mGlobalNvsAreaPtr->IsctCfg                       = mGlobalNvsAreaPtr->IsctCfg | BIT0;

    if (gSetupData->ISCTNOTIFICATION) {
      mGlobalNvsAreaPtr->IsctCfg                     = mGlobalNvsAreaPtr->IsctCfg | BIT1;
    }
    if (gSetupData->ISCTWLAN) {
      mGlobalNvsAreaPtr->IsctCfg                     = mGlobalNvsAreaPtr->IsctCfg | BIT2;
    }
    if (gSetupData->ISCTWWAN) {
      mGlobalNvsAreaPtr->IsctCfg                     = mGlobalNvsAreaPtr->IsctCfg | BIT3;
    }
    mGlobalNvsAreaPtr->IsctCfg                       = mGlobalNvsAreaPtr->IsctCfg | BIT4;
    mGlobalNvsAreaPtr->IsctCfg                       = mGlobalNvsAreaPtr->IsctCfg | BIT5;  // Duration in seconds

    if (gSetupData->ISCTRFKillSwitch) {
      mGlobalNvsAreaPtr->IsctCfg                     = mGlobalNvsAreaPtr->IsctCfg | BIT6;
    }
// ami override start
    mGlobalNvsAreaPtr->IsctCfg                       |= BIT7;  // Isct Wake from S4 Supported
// ami override end
  }

  return Status;
}

STATIC
EFI_STATUS
InitializeIsctAcpiTables (
  VOID
  )
/*++

Routine Description:

  Initialize ISCT ACPI tables

Arguments:

Returns:

  EFI_SUCCESS    Isct ACPI tables are initialized successfully
  EFI_NOT_FOUND  Isct ACPI tables not found

--*/
{
  EFI_STATUS                    Status;
  EFI_HANDLE                    *HandleBuffer;
  UINTN                         NumberOfHandles;
  EFI_FV_FILETYPE               FileType;
  UINT32                        FvStatus;
  EFI_FV_FILE_ATTRIBUTES        Attributes;
  UINTN                         Size;
  UINTN                         Index;
  EFI_FIRMWARE_VOLUME_PROTOCOL  *FwVol;
  INTN                          Instance;
  EFI_ACPI_COMMON_HEADER        *CurrentTable;
  UINT8                         *CurrPtr;
  UINT8                         *EndPtr;
  UINT32                        *Signature;
  EFI_ACPI_DESCRIPTION_HEADER   *IsctAcpiTable;
  BOOLEAN                       LoadTable;
  UINTN                         TableHandle;
  EFI_ACPI_TABLE_VERSION        Version;
  EFI_ACPI_TABLE_PROTOCOL       *AcpiTable;

  FwVol         = NULL;
  IsctAcpiTable = NULL;

  Status = gBS->LocateProtocol (&gEfiAcpiTableProtocolGuid, NULL, &AcpiTable);
  if ( EFI_ERROR(Status) ) {
      DEBUG((EFI_D_INFO, "ISCT :gBS->LocateProtocol -> AcpiTable Status = %x\n", Status));
      return Status;
  }

  //
  // Locate protocol.
  // There is little chance we can't find an FV protocol
  //
  Status = gBS->LocateHandleBuffer (
                  ByProtocol,
                  &gEfiFirmwareVolumeProtocolGuid,
                  NULL,
                  &NumberOfHandles,
                  &HandleBuffer
                  );
  if ( EFI_ERROR(Status) ) {
      DEBUG((EFI_D_INFO, "ISCT :gBS->LocateHandleBuffer Status = %x\n", Status));
      return Status;
  }

  //
  // Looking for FV with ACPI storage file
  //
  for (Index = 0; Index < NumberOfHandles; Index++) {
    //
    // Get the protocol on this handle
    // This should not fail because of LocateHandleBuffer
    //
    Status = gBS->HandleProtocol (
                    HandleBuffer[Index],
                    &gEfiFirmwareVolumeProtocolGuid,
                    &FwVol
                    );
    if ( EFI_ERROR(Status) ) {
        DEBUG((EFI_D_INFO, "ISCT :gBS->HandleProtocol Status = %x\n", Status));
        return Status;
    }

    //
    // See if it has the ACPI storage file
    //
    Size      = 0;
    FvStatus  = 0;
    Status = FwVol->ReadFile (
                      FwVol,
                      &gIsctAcpiTableStorageGuid,
                      NULL,
                      &Size,
                      &FileType,
                      &Attributes,
                      &FvStatus
                      );
    DEBUG((EFI_D_INFO, "ISCT :FwVol->ReadFile Status = %x\n", Status));
    //
    // If we found it, then we are done
    //
    if (Status == EFI_SUCCESS) {
      break;
    }
  }
  //
  // Free any allocated buffers
  //
  FreePool (HandleBuffer);

  //
  // Sanity check that we found our data file
  //
  if (FwVol == NULL) {
    return EFI_NOT_FOUND;
  }
  //
  // By default, a table belongs in all ACPI table versions published.
  //
  Version = EFI_ACPI_TABLE_VERSION_1_0B | EFI_ACPI_TABLE_VERSION_2_0 | EFI_ACPI_TABLE_VERSION_3_0;

  //
  // Our exit status is determined by the success of the previous operations
  // If the protocol was found, Instance already points to it.
  // Read tables from the storage file.
  //
  Instance      = 0;
  CurrentTable  = NULL;
  while (Status == EFI_SUCCESS) {
    Status = FwVol->ReadSection (
                      FwVol,
                      &gIsctAcpiTableStorageGuid,
                      EFI_SECTION_RAW,
                      Instance,
                      &CurrentTable,
                      &Size,
                      &FvStatus
                      );
    DEBUG((EFI_D_INFO, "ISCT :FwVol->ReadSection Status = %x\n", Status));

    if (!EFI_ERROR (Status)) {
      LoadTable = FALSE;
      //
      // Check the table ID to modify the table
      //
      if (((EFI_ACPI_DESCRIPTION_HEADER *) CurrentTable)->OemTableId == EFI_SIGNATURE_64 ('I', 's', 'c', 't', 'T', 'a', 'b', 'l')) {
        IsctAcpiTable = (EFI_ACPI_DESCRIPTION_HEADER *) CurrentTable;
        DEBUG((EFI_D_ERROR, "ISCT :Find out IsctTabl\n"));
        //
        // Locate the SSDT package
        //
        CurrPtr = (UINT8 *) IsctAcpiTable;
        EndPtr  = CurrPtr + IsctAcpiTable->Length;

        for (; CurrPtr <= EndPtr; CurrPtr++) {
          Signature = (UINT32 *) (CurrPtr + 3);
          if (*Signature == EFI_SIGNATURE_32 ('I', 'S', 'C', 'T')) {
            LoadTable = TRUE;
            if((*(UINT32 *) (CurrPtr + 3 + sizeof (*Signature) + 2) == 0xFFFF0008)) {
            //
            // ISCT NVS Area address
            //
            *(UINT32 *) (CurrPtr + 3 + sizeof (*Signature) + 2) = (UINT32) (UINTN) mIsctNvsAreaProtocol.Area;
            DEBUG((EFI_D_INFO, "ISCT :Modify OpRegion Address to %x\n", (*(UINT32 *) (CurrPtr + 3 + sizeof (*Signature) + 2))));
            }

            if((*(UINT16 *) (CurrPtr + 3 + sizeof (*Signature) + 2 + sizeof (UINT32) + 1) == 0xAA58)) {
            //
            // ISCT NVS Area size
            //
            *(UINT16 *) (CurrPtr + 3 + sizeof (*Signature) + 2 + sizeof (UINT32) + 1) = sizeof (ISCT_NVS_AREA);
            DEBUG((EFI_D_INFO, "ISCT :Modify OpRegion Size to %x\n", *(UINT16 *) (CurrPtr + 3 + sizeof (*Signature) + 2 + sizeof (UINT32) + 1)));
            }

            ///
            /// Add the table
            ///
            if (LoadTable) {
              TableHandle = 0;
              Status = AcpiTable->InstallAcpiTable (
                                  AcpiTable,
                                  CurrentTable,
                                  CurrentTable->Length,
                                  &TableHandle
                                  );
              if ( EFI_ERROR(Status) ) {
                  return Status;
              }
            }
            return EFI_SUCCESS;
          }
        }
      }
      //
      // Increment the instance
      //
      Instance++;
      CurrentTable = NULL;
    }
  }

  return Status;
}

VOID
IsctOnReadyToBoot (
  IN EFI_EVENT  Event,
  IN VOID       *Context
  )
/*++

Routine Description:

  Install Isct ACPI tables only when Isct is enabled

Arguments:

  Event    - The event that triggered this notification function
  Context  - Pointer to the notification functions context

Returns:

  None

--*/
{
  EFI_STATUS  Status;
  IGD_OPREGION_PROTOCOL         *IgdOpRegionProtocol;

  DEBUG ((EFI_D_INFO, "IsctOnReadyToBoot()\n"));

  Status = InitializeIsctAcpiTables ();
  if ( EFI_ERROR(Status) ) {
      DEBUG((EFI_D_INFO, "Initializes ISCT SSDT tables Status = %x\n", Status));
      return;
  }

  gBS->CloseEvent (Event);

  //
  // Notify the Graphics Driver that Isct is enabled
  //
  Status = gBS->LocateProtocol (
                &gIgdOpRegionProtocolGuid,
                NULL,
                &IgdOpRegionProtocol
                );
  if (Status == EFI_SUCCESS) {
    IgdOpRegionProtocol->OpRegion->Header.PCON |= 0x60;
    DEBUG((EFI_D_INFO, "IsctOnReadyToBoot() PCON = 0x%x\n", IgdOpRegionProtocol->OpRegion->Header.PCON));
  } else {
    DEBUG ((EFI_D_ERROR, "IsctOnReadyToBoot() Unable to locate IgdOpRegionProtocol"));
  }
}

EFI_STATUS
IsctDxeEntryPoint (
  IN EFI_HANDLE       ImageHandle,
  IN EFI_SYSTEM_TABLE *SystemTable
  )
/*++

Routine Description:

  ISCT DXE driver entry point function

Arguments:

  ImageHandle - Image handle for this driver image
  SystemTable - Pointer to the EFI System Table

Returns:

  EFI_OUT_OF_RESOURCES - no enough memory resource when installing reference code information protocol
  EFI_SUCCESS          - function completed successfully

--*/
{
  EFI_STATUS                    Status;
  EFI_EVENT                     Event;
  PLATFORM_INFO_PROTOCOL        *PlatformInfoProtocol;
  ISCT_NVS_AREA                 *IsctNvs;
  ISCT_PERSISTENT_DATA          mIsctData;
  UINT8                         IsctEnabled;
  AMI_ISCT_HOB                  *IsctDataHob;
  EFI_GUID                      SetupGuid = SYSTEM_CONFIGURATION_GUID;
  SETUP_DATA                    SetupData;
  UINTN                         VarSize;
  VOID                          *HobList;
  EFI_GUID                      gIsctDataHobGuid = AMI_ISCT_HOB_GUID;   
                                   
  DEBUG ((EFI_D_INFO, "IsctDxe: Entry Point...\n"));

  VarSize = sizeof (SETUP_DATA);
  Status = gRT->GetVariable (
                  L"Setup",
                  &SetupGuid,
                  NULL,
                  &VarSize,
                  &SetupData
                  );
  if ( EFI_ERROR(Status) ) {
      DEBUG ((EFI_D_INFO, "ISCT: Get Variable Status = %x\n", Status));
      return Status;
  }

  IsctEnabled = SetupData.IsctConfiguration;

  if(IsctEnabled == 0) {
    DEBUG ((EFI_D_INFO, "ISCT is Disabled \n"));
    return EFI_SUCCESS;
  }

  Status = gBS->LocateProtocol (
                  &gPlatformInfoProtocolGuid, 
                  NULL, 
                  &PlatformInfoProtocol
                  );
  if ( EFI_ERROR(Status) ) {
      return Status;
  }

  //
  // Allocate pools for ISCT Global NVS area
  //
  Status = (gBS->AllocatePool) (EfiReservedMemoryType, sizeof (ISCT_NVS_AREA), &mIsctNvsAreaProtocol.Area);
  if ( EFI_ERROR (Status) ) {
    DEBUG ((EFI_D_ERROR, "Error to allocate pool for ISCT_NVS_AREA"));
    ASSERT_EFI_ERROR (Status);
    return Status;
  }
  ZeroMem ((VOID *) mIsctNvsAreaProtocol.Area, sizeof (ISCT_NVS_AREA));

//ami override start
//  Status = (gBS->AllocatePool) (EfiReservedMemoryType, sizeof (ISCT_PERSISTENT_DATA), &mIsctNvsAreaProtocol.IsctData);
//  if ( EFI_ERROR (Status) ) {
//    DEBUG ((EFI_D_ERROR, "Error to allocate pool for ISCT_PERSISTENT_DATA"));
//    ASSERT_EFI_ERROR (Status);
//    return Status;
//  }
//  ZeroMem ((VOID *) mIsctNvsAreaProtocol.IsctData, sizeof (ISCT_PERSISTENT_DATA));
//ami override end

  IsctNvs = mIsctNvsAreaProtocol.Area;
  
//ami override start
//  IsctNvs->IsctNvsPtr = (UINT32) (UINTN) IsctNvs;
//ami override end
  //
  // Isct WA: Add option for use of RTC timer on Mobile systems until EC wake through GP27 is working
  //
  IsctNvs->IsctTimerChoice = SetupData.IsctTimerChoice; //get timer choice from setup options
  if(PlatformInfoProtocol->PlatformFlavor == FlavorDesktop) {
    IsctNvs->IsctTimerChoice = 1; //use RTC timer for Desktop
  }
#if defined (LVC_BOARD) && (LVC_BOARD == 1)
    IsctNvs->IsctTimerChoice = 1; //use RTC timer for Lava Cayon Crb
#endif

  
  IsctNvs->IsctEnabled = 1;
#ifdef RAPID_START_FLAG
  IsctNvs->RapidStartEnabled = SetupData.RapidStartEnabled;
#else
  IsctNvs->RapidStartEnabled = 0;
#endif

//ami override start
  //
  // Assign IsctData pointer to GlobalNvsArea
  //  
  mIsctData.IsctNvsPtr = (UINT32) (UINTN) IsctNvs;
  mIsctData.IsctOverWrite = FALSE;   
//ami override end

  //
  // Look for Isct Data Hob
  //
  IsctDataHob = NULL;
  Status = EfiGetSystemConfigurationTable (&gEfiHobListGuid,  &HobList);
  DEBUG ((EFI_D_INFO, "Get Isct Data HOB, Guid:%g \n", gIsctDataHobGuid));
  IsctDataHob = (AMI_ISCT_HOB*)GetNextGuidHob (&gIsctDataHobGuid, HobList);
  if (IsctDataHob == NULL) {
    DEBUG ((EFI_D_ERROR, "Isct Data HOB not available\n"));
    return EFI_NOT_FOUND;
  }

  //
  // Populate wake reason with hob data. Will be 0 for S5.
  //

 IsctNvs->IsctWakeReason = IsctDataHob->WakeReason;
 DEBUG ((EFI_D_INFO, "Isct Data HOB found- Update Isct NVS with Wake Reason: %x\n", IsctNvs->IsctWakeReason));


    
  //
  // Install ISCT Global NVS protocol
  //
  Status = gBS->InstallMultipleProtocolInterfaces (
                  &ImageHandle,
                  &gIsctNvsAreaProtocolGuid,
                  &mIsctNvsAreaProtocol,
                  NULL
                  );
  DEBUG((EFI_D_INFO, "Install IsctNvsAreaProtocolGuid = 0x%x\n", Status));

  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "Error to install ISCT_NVS_AREA_PROTOCOL"));
    ASSERT_EFI_ERROR (Status);
    return Status;
  }  
                
  //
  // Save ISCT Data to Variable
  //
  Status = gRT->SetVariable (
                  ISCT_PERSISTENT_DATA_NAME,
                  &gIsctPersistentDataGuid,
                  EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS,
                  sizeof (ISCT_PERSISTENT_DATA),
                  &mIsctData
                  );
  if (EFI_ERROR (Status)) {
    DEBUG((EFI_D_INFO, "ISCT DXE: Save ISCT Data to Variable Status = %x\n", Status));
    return Status;
  }

  //
  // Update SetupVariable to ACPI GNVS
  //
  Status = IsctDxeUpdateSetupVariableToACPIGNVS (&SetupData);
  if ( EFI_ERROR(Status) ) {
      return Status;
  }

  //
  // Register ready to boot event for ISCT
  //
   
  Status = EfiCreateEventReadyToBootEx (
            EFI_TPL_NOTIFY,
            IsctOnReadyToBoot,
            NULL,
            &Event
            );
  DEBUG((EFI_D_INFO, "Create ReadyToBoot event for ISCT Status = %x\n", Status));  
  if (EFI_ERROR (Status)) {                   
    ASSERT_EFI_ERROR (Status);
    return Status;
  }   


  DEBUG ((EFI_D_INFO, "(IsctDxe) entry End...\n"));
  
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
