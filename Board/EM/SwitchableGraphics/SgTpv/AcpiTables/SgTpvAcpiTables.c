//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**        5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093         **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/SwitchableGraphics/Sg TPV/Sg Acpi Tables/SgTpvAcpiTables.c 7     3/21/13 3:48a Joshchou $
//
// $Revision: 7 $
//
// $Date: 3/21/13 3:48a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/SwitchableGraphics/Sg TPV/Sg Acpi Tables/SgTpvAcpiTables.c $
// 
// 7     3/21/13 3:48a Joshchou
// [TAG]  		EIPEIP116106
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	ACPI error in Win8 event viewer on ULT platform
// [RootCause]  	We use the PCI_config to save/restore registers,and the
// value of EBAS is wrong.
// [Solution]  	Save the correct value of EBAS in "SgTpvAcpiTables.c"
// Use the MMIO to save/restore registers
// 
// 6     1/15/13 6:06a Joshchou
// [TAG]  		EIP107237
// [Category]  	Improvement
// [Description]  	Modify for support SG on ULT platform.
// 
// 5     12/22/12 2:38a Joshchou
// [TAG]  		None
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Did not get the correct Endpoint Link Contol Register Value
// [RootCause]  	Give the wrong address.
// [Solution]  	Fix the address.
// 
// 4     12/18/12 6:21a Joshchou
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Update for SA RC 081
// 
// 3     10/16/12 4:41a Joshchou
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Update for SA and ACPI RC 0.7.1
// [Files]  		SgTpvAcpiTables.c
// 
// 2     9/09/12 10:57p Joshchou
// 
// 3     12/12/11 9:17p Alanlin
// [TAG]  		EIP74169
// [Category]  	Improvement
// [Description]  	Add OEMSSDT module part. Token "SGOEMSSDT_SUPPORT" to
// create OEM SSDT 
// for discrete VGA card.When Primarydisplay = Auto or PEG, it can report
// OEM SSDT 
// talbes for AMD or nVidia dGPU VGA card.
// [Files]  		SgTpvAcpiTables.c
// SgTpvAcpiTables.cif
// 
// 2     12/02/11 5:38a Alanlin
// [TAG]  		EIP75211
// [Category]  	Improvement
// [Description]  	Changeing VBIOS size to 128k for _ROM method for nVidia
// chip.
// 
// 1     6/27/11 5:26a Alanlin
// [TAG]  		EIP61848
// [Category]  	New Feature
// [Description]  	Initial check-in.Integrated SwitchableGraphics Intel
// Reference code 0.6.0
// [Files]  		SgTpvAcpiTables.cif
// SgTpvAcpiTables.sdl
// SgTpvAcpiTables.mak
// SgTpvAcpiTables.c
// 
// 
// 10    3/17/11 6:15p Alexp
// Optimus:Add code to preserve HD AudioCodec enable flag in CMOS
// 
// 9     1/03/11 12:35p Alexp
// [TAG]  		EIP50104
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Nvidia GPU device disappears after S3 resume
// [RootCause]  	PEG bridge controller was not restoring secondary and
// subiordinate bus numbers on S3 resume
// [Solution]  	add code to save/restore PCI context using S3_resume
// Scripts
// [Files]  		SgTpvAcpiTables.c
// 
// 8     11/12/10 1:19p Alexp
// rearrange the code for Amd and Nvidia tables. 
// Add WiDi DID number if WiDi support is selected in GlobalAcpiNvs flags
// 
// 7     11/11/10 3:09p Alexp
// Add debug messages
// 
// 6     10/06/10 4:17p Alexp
// comments chnage for NvidiaOpRegion header
// 
// 5     10/05/10 7:08p Alexp
// added new field in NVH OpRegion to pass MXM3 data block.
// 
// 4     9/29/10 1:23p Alexp
// [TAG]    	  EIP43103 --->change code to update dGPU SVID registers
// 
// 3     9/23/10 1:12p Alexp
// BUG fix in disable logic for Func1 on PEG endpoint (HDA) for Optimus 
// 
// 2     9/21/10 5:09p Alexp
// [TAG]    	  EIP43103 --->fix debug messages
// 
// 1     9/17/10 1:18p Alexp
// [TAG]    	  EIP43103 
// [Category]  Function Request
// [Severity]	  Normal
// [Symptom]    Initial check-in of SgTPV module
// [RootCause] Request to implement SG reference code .
// [Solution]	Initial check-in. 
// [Files]	
//         SgTpvAcpiTables.cif;*.sdl;*.mak;*.c
// 
//**********************************************************************
//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		SgTpvAcpiTables.c
//
// Description:	This file contains the routine LoadTpvAcpiTables which installs 
//              Acpi Tables for Tpv's Switchable Graphics. 
//              File is linked with Intel's SwitchableGraphicsDxe module
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "SgTpvAcpitables.h"
//<AMI_THDR_START>
//----------------------------------------------------------------------------
// Procedure: NvidiaOpRegion & AmdOpRegion
//
// Description: Gfx Vendor specific OperationRegion data structures. 
//              Must match ones defined in Asl code
//
//----------------------------------------------------------------------------
//<AMI_THDR_END>
NVIDIA_OPREGION             NvidiaOpRegion;
AMD_OPREGION                AmdOpRegion;

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: LoadTpvAcpiTables
//
// Description:   Load Third part graphics vendor support SSDT Tables
//
// Input: VOID
//
// Output:   
//      EFI_SUCCESS     - SSDT Table load successful. 
//      EFI_UNSUPPORTED - Supported SSDT not found.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
LoadTpvAcpiTables (
  VOID
  )
{
  EFI_STATUS                    Status;
  EFI_HANDLE                    *HandleBuffer;
  BOOLEAN                       LoadTable;
  INTN                          Instance;
  UINTN                         NumberOfHandles;
  UINTN                         Index;
  UINTN                         Size;
  UINTN                         TableHandle;
//UINT16                        Data16;
//UINT32                        Data32;
  UINT32                        FvStatus;
#if (PI_SPECIFICATION_VERSION < 0x00010000)
  EFI_FIRMWARE_VOLUME_PROTOCOL  *FwVol;
#else
  EFI_FIRMWARE_VOLUME2_PROTOCOL *FwVol;
#endif
  EFI_FV_FILETYPE               FileType;
  EFI_FV_FILE_ATTRIBUTES        Attributes;
  EFI_ACPI_DESCRIPTION_HEADER   *TableHeader;
  EFI_ACPI_TABLE_VERSION        Version;
//  EFI_GUID                      SGTPV_AcpiTableGuid= SGTPV_ACPI_SSDT_GUID;
  EFI_GUID                      SGTPV_AcpiTableGuid;
  EFI_GUID                      gSgtpvAcpiSsdtGuid= SGTPV_ACPI_SSDT_GUID;
  EFI_GUID                      gSgtpvAcpiPchSsdtGuid= SGTPV_ACPIPCH_SSDT_GUID;

#if SGOEMSSDT_SUPPORT
  EFI_GUID                      SGOEM_AcpiTableGuid = SGOEM_ACPI_SSDT_GUID;
#endif
  EFI_ACPI_SUPPORT_PROTOCOL     *AcpiSupport;
  EFI_ACPI_COMMON_HEADER        *Table;

  UINT16                        VendorId;


  FwVol = NULL;
  Table = NULL;

  DEBUG ((EFI_D_ERROR, "CpuFamilyId ==0x%X\n", CpuFamilyId));
    SGTPV_AcpiTableGuid = gSgtpvAcpiSsdtGuid;
  if (CpuFamilyId == EnumCpuHswUlt) {
    SGTPV_AcpiTableGuid = gSgtpvAcpiPchSsdtGuid;
  }



  VendorId = McDevFunPciCfg16 (EndpointBus, 0, 0, PCI_VID); // DEBUG
  DEBUG ((EFI_D_ERROR, "SG TPV Vendor ID %X\n", VendorId));

  switch(VendorId){
    case NVIDIA_VID:
        //
        // Set VendorId if PEG is NVIDIA and supports HG
        //
        VendorId = NVIDIA_VID;
    break;
    case AMD_VID:
        //
        // Set VendorId if PEG is AMD and supports HG
        //
        VendorId = AMD_VID;
    break;
    default:
        //
        // either means the Device ID is not on the list of devices we know - we return from this function
        //
        DEBUG ((EFI_D_ERROR, "SG TPV Unsupported Vendor ID\n"));
        return EFI_UNSUPPORTED;
  }


  ///
  ///  Locate the SA Global NVS Protocol.
  ///
  Status = gBS->LocateProtocol (
                  &gSaGlobalNvsAreaProtocolGuid,
                  NULL,
                  (VOID **) &SaGlobalNvsArea
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }
    SaGlobalNvsArea->Area->EndpointBaseAddress = (UINT32) (MmPciAddress (0, EndpointBus, 0, 0, 0x0));

  //
  // Locate FV protocol.
  //
  Status = gBS->LocateHandleBuffer (
                  ByProtocol,
              #if (PI_SPECIFICATION_VERSION < 0x00010000) 
                  &gEfiFirmwareVolumeProtocolGuid,
              #else
                  &gEfiFirmwareVolume2ProtocolGuid,
              #endif
                  NULL,
                  &NumberOfHandles,
                  &HandleBuffer
                  );
  ASSERT_EFI_ERROR (Status);

  //
  // Look for FV with ACPI storage file
  //
  for (Index = 0; Index < NumberOfHandles; Index++) {
    //
    // Get the protocol on this handle
    // This should not fail because of LocateHandleBuffer
    //
    Status = gBS->HandleProtocol (
                    HandleBuffer[Index],
              #if (PI_SPECIFICATION_VERSION < 0x00010000) 
                  &gEfiFirmwareVolumeProtocolGuid,
              #else
                  &gEfiFirmwareVolume2ProtocolGuid,
              #endif
                    &FwVol
                    );
    ASSERT_EFI_ERROR (Status);

    //
    // See if it has the ACPI storage file
    //
    Size      = 0;
    FvStatus  = 0;
    Status = FwVol->ReadFile (
                      FwVol,
                      &SGTPV_AcpiTableGuid,
                      NULL,
                      &Size,
                      &FileType,
                      &Attributes,
                      &FvStatus
                      );

    //
    // If we found it, then we are done
    //
    if (!EFI_ERROR (Status)) {
      break;
    }
  }

  //
  // Our exit status is determined by the success of the previous operations
  // If the protocol was found, Instance already points to it.
  //
  //
  // Free any allocated buffers
  //
  (gBS->FreePool) (HandleBuffer);

  //
  // Sanity check that we found our data file
  //
  ASSERT (FwVol);

  //
  // By default, a table belongs in all ACPI table versions published.
  //
  Version = EFI_ACPI_TABLE_VERSION_1_0B | EFI_ACPI_TABLE_VERSION_2_0 | EFI_ACPI_TABLE_VERSION_3_0;

  //
  // Locate ACPI tables
  //
  Status = gBS->LocateProtocol (
                  &gEfiAcpiSupportGuid,
                  NULL,
                  &AcpiSupport
                  );


  ASSERT_EFI_ERROR (Status);

  //
  // Read tables from the storage file.
  //
  Instance = 0;

  while (Status == EFI_SUCCESS) {
    //
    // Read the ACPI tables
    //
    Status = FwVol->ReadSection (
                      FwVol,
                      &SGTPV_AcpiTableGuid,
                      EFI_SECTION_RAW,
                      Instance,
                      &Table,
                      &Size,
                      &FvStatus
                      );
    if (!EFI_ERROR (Status)) {
      //
      // check for SwitchableGraphics tables and decide which SSDT should be loaded
      //
      LoadTable   = FALSE;
      TableHeader = (EFI_ACPI_DESCRIPTION_HEADER *) Table;

      DEBUG ((EFI_D_ERROR, "SG TPV SSDT TblID %X\n", TableHeader->OemTableId));

      switch (((EFI_ACPI_DESCRIPTION_HEADER *) TableHeader)->OemTableId) {

      case EFI_SIGNATURE_64 ('N', 'v', 'd', 'T', 'a', 'b', 'l', 0):
        if(VendorId != NVIDIA_VID || 
            SaGlobalNvsArea->Area->SgMode != SgModeMuxed)
                break;

            DEBUG ((EFI_D_ERROR, "SG TPV Nvidia SG Table\n"));
        //
        // This is Nvidia SSDT
        //
        LoadTable = TRUE;
        Status    = InstallNvidiaOpRegion ();
        if (EFI_ERROR (Status)) {
          return Status;
        }

        break;

      case EFI_SIGNATURE_64 ('O', 'p', 't', 'T', 'a', 'b', 'l', 0):
        if(VendorId != NVIDIA_VID || 
            SaGlobalNvsArea->Area->SgMode != SgModeMuxless)
                break;
        
        DEBUG ((EFI_D_ERROR, "SG TPV Nvidia Optimus Table\n"));
        //
        // This is nVidia Optimus SSDT
        //
        LoadTable = TRUE;
        Status = InstallNvidiaOpRegion();
        if (EFI_ERROR(Status)) {
          return Status;
        }

        break;

      case EFI_SIGNATURE_64 ('A', 'm', 'd', 'T', 'a', 'b', 'l', 0):
        if(VendorId != AMD_VID) 
            break;
        //
        // This is Amd SSDT
        //
        LoadTable = TRUE;
        Status    = InstallAmdOpRegion ();
        if (EFI_ERROR (Status)) {
          return Status;
        }

        break;

      default:
            DEBUG ((EFI_D_ERROR, "WARNING: SG TPV Unsupported SSDT Signature...\n"));
        break;
      }

      //
      // Add the table
      //
      if (LoadTable) {
        TableHandle = 0;
        Status = AcpiSupport->SetAcpiTable (
                                AcpiSupport,
                                TableHeader,
                                TRUE,
                                Version,
                                &TableHandle
                                );
        ASSERT_EFI_ERROR (Status);
        Status = AcpiSupport->PublishTables (
                                AcpiSupport,
                                Version
                                );
        ASSERT_EFI_ERROR (Status);
//        if (EFI_ERROR(Status)) break;
        break;  // only one ACPI SG/Optimus table should be loaded
      }
      //
      // Increment the instance
      //
      Instance++;
      Table = NULL;
    }
  }

#if SGOEMSSDT_SUPPORT
  //
  // Locate ACPI tables
  //
  Status = gBS->LocateProtocol (
                  &gEfiAcpiSupportGuid,
                  NULL,
                  &AcpiSupport
                  );
  ASSERT_EFI_ERROR (Status);

  //
  // Read tables from the storage file.
  //
  Instance = 0;

  while (Status == EFI_SUCCESS) {
    //
    // Read the ACPI tables
    //
    Status = FwVol->ReadSection (
                      FwVol,
                      &SGOEM_AcpiTableGuid,
                      EFI_SECTION_RAW,
                      Instance,
                      &Table,
                      &Size,
                      &FvStatus
                      );
    if (!EFI_ERROR (Status)) {
      //
      // check for SwitchableGraphics tables and decide which SSDT should be loaded
      //
      LoadTable   = FALSE;
      TableHeader = (EFI_ACPI_DESCRIPTION_HEADER *) Table;

      DEBUG ((EFI_D_ERROR, "SG TPV SSDT TblID %X\n", TableHeader->OemTableId));

      switch (((EFI_ACPI_DESCRIPTION_HEADER *) TableHeader)->OemTableId) {

        //
        // Set OEM SSDT 
        //

      case SGOEM_ACPI_SSDT_TABLE:
            if(SaGlobalNvsArea->Area->SgMode != SgModeDgpu)                 
                break;

            DEBUG ((EFI_D_ERROR, "OEM SSDT Table\n"));
        //
        // This is OEM SSDT
        //
        LoadTable = TRUE;
        if(VendorId == NVIDIA_VID)
        Status    = InstallNvidiaOpRegion ();
        else 
        Status    = InstallAmdOpRegion();

        if (EFI_ERROR (Status)) {
          return Status;
        }

        break;

      default:
            DEBUG ((EFI_D_ERROR, "WARNING: SG OEM Unsupported SSDT Signature...\n"));
        break;
      }

      //
      // Add the table
      //
      if (LoadTable) {
        TableHandle = 0;
        Status = AcpiSupport->SetAcpiTable (
                                AcpiSupport,
                                TableHeader,
                                TRUE,
                                Version,
                                &TableHandle
                                );
        ASSERT_EFI_ERROR (Status);
        Status = AcpiSupport->PublishTables (
                                AcpiSupport,
                                Version
                                );
        ASSERT_EFI_ERROR (Status);
//        if (EFI_ERROR(Status)) break;
        break;  // only one ACPI SG/Optimus table should be loaded
      }
      //
      // Increment the instance
      //
      Instance++;
      Table = NULL;
    }
  }
#endif

  DEBUG ((EFI_D_ERROR, "SGtpv:: NDID:0x%x\n", SaGlobalNvsArea->Area->NumberOfValidDeviceId));
  DEBUG ((EFI_D_ERROR, "SGtpv:: DID1:0x%x\n", SaGlobalNvsArea->Area->DeviceId1));
  DEBUG ((EFI_D_ERROR, "SGtpv:: DID2:0x%x\n", SaGlobalNvsArea->Area->DeviceId2));
  DEBUG ((EFI_D_ERROR, "SGtpv:: DID3:0x%x\n", SaGlobalNvsArea->Area->DeviceId3));
  DEBUG ((EFI_D_ERROR, "SGtpv:: DID4:0x%x\n", SaGlobalNvsArea->Area->DeviceId4));
  DEBUG ((EFI_D_ERROR, "SGtpv:: DID5:0x%x\n", SaGlobalNvsArea->Area->DeviceId5));
  DEBUG ((EFI_D_ERROR, "SGtpv:: DID6:0x%x\n", SaGlobalNvsArea->Area->DeviceId6));
  DEBUG ((EFI_D_ERROR, "SGtpv:: DID7:0x%x\n", SaGlobalNvsArea->Area->DeviceId7));
  DEBUG ((EFI_D_ERROR, "SGtpv:: DID8:0x%x\n", SaGlobalNvsArea->Area->DeviceId8));

  DEBUG ((EFI_D_ERROR, "SG TPV Gfx acpi UPDATE - COMPLETED\n"));
  return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
//Procedure: InstallNvidiaOpRegion
//
//Description: Nvidia SG specific Asl OpRegion installation function.
//
//Input:
//
//  ImageHandle     Handle for this drivers loaded image protocol.
//  SystemTable     EFI system table.
//
//Output:
//
//  EFI_SUCCESS     The driver installed without error.
//  EFI_ABORTED     The driver encountered an error and could not complete
//                  installation of the ACPI tables.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
InstallNvidiaOpRegion (
  VOID
  )
{
    EFI_STATUS                    Status;
    UINTN                         Size;
// Locate MXM3 protocol and get Mxm data pointer from function->MxmReturnStructure
    EFI_GUID  EfiMxm3ProtocolGuid = MXM3_EFI_GUID;
#if MXM30_SUPPORT == 1
    MXM3_EFI_PROTOCOL           *Mxm30Protocol;
    VOID                        *MxmLegMemAddr = NULL;
    UINT32                       MxmLegMemSize = 0;
#endif  
    //
    // Allocate an ACPI NVS memory buffer as the Nvidia NVIG OpRegion, zero initialize
    // the entire 1K, and set the Nvidia NVIG OpRegion pointer in the Global NVS
    // area structure.
    //
    Size    = sizeof (NVIG_OPREGION);
    Status  = (gBS->AllocatePool) (EfiACPIMemoryNVS, Size, &NvidiaOpRegion.NvIgOpRegion);
    if (EFI_ERROR (Status)) {
        return Status;
    }

    (gBS->SetMem) (NvidiaOpRegion.NvIgOpRegion, Size, 0);
    
    //
    // Set up DeviceID values for _DOD.
    // Note that Display Subtype bits[15-12] and Port index bits[7:4] are set as per NV Switchable 3.0 spec.
        // Not used by Intel driver.
        //
        //
    // Display Type - CRT
    //
    SaGlobalNvsArea->Area->DeviceId1 = 0x80010100;
    
    if (SaGlobalNvsArea->Area->ActiveLFP == 3) {
      //
      // If Active LFP = EDP_A
      //
      // Display type - LFP Device Sub Type - eDP
      //
      SaGlobalNvsArea->Area->DeviceId2 = 0x8001A420;
    } else {
      //
      // Display Type - LFP Device Sub Type - LVDS
      //
      SaGlobalNvsArea->Area->DeviceId2 = 0x80010410;
    }
    //
    // Display type - EFP  Device Sub type - DisplayPort 1.1
    //
    SaGlobalNvsArea->Area->DeviceId3 = 0x80016330 | ((SaGlobalNvsArea->Area->SgMuxDid3 & 0xFF00) << 10);
    
    //
    // Display type - EFP  Device Sub type - HDMI 1.2 or 1.3a
    //
    SaGlobalNvsArea->Area->DeviceId4 = 0x80017331 | ((SaGlobalNvsArea->Area->SgMuxDid4 & 0xFF00) << 10);
    
    //
    // Display type - EFP  Device Sub type - HDMI 1.2 or 1.3a
    //
    SaGlobalNvsArea->Area->DeviceId5 = 0x80017342 | ((SaGlobalNvsArea->Area->SgMuxDid5 & 0xFF00) << 10);
    
    //
    // Display type - EFP  Device Sub type - DisplayPort 1.1
    //
    SaGlobalNvsArea->Area->DeviceId6 = 0x80016353 | ((SaGlobalNvsArea->Area->SgMuxDid6 & 0xFF00) << 10);
    
    //
    // Display type - EFP  Device Sub type - HDMI 1.2 or 1.3a
    //
    SaGlobalNvsArea->Area->DeviceId7 = 0x80017354 | ((SaGlobalNvsArea->Area->SgMuxDid7 & 0xFF00) << 10);
    
    //
    // DeviceId8 is not being used on HuronRiver SG
    //
    SaGlobalNvsArea->Area->DeviceId8              = 0x0;
    
    //
    // NDID
    //
    SaGlobalNvsArea->Area->NumberOfValidDeviceId  = VALIDDIDS;//0x7;
    
    //
    // NVIG
    //
    SaGlobalNvsArea->Area->NvIgOpRegionAddress = (UINT32)(UINTN)(NvidiaOpRegion.NvIgOpRegion);
    
    //
    // NVIG Header
    //
    (gBS->CopyMem) (NvidiaOpRegion.NvIgOpRegion->NISG, NVIG_HEADER_SIGNATURE, sizeof (NVIG_HEADER_SIGNATURE));
    NvidiaOpRegion.NvIgOpRegion->NISZ = NVIG_OPREGION_SIZE;
    NvidiaOpRegion.NvIgOpRegion->NIVR = NVIG_OPREGION_VER;
    
    //
    // Panel Scaling Preference
    //
    NvidiaOpRegion.NvIgOpRegion->GPSP = SaGlobalNvsArea->Area->IgdPanelScaling;
    

    // Save Link Control register
    NvidiaOpRegion.NvIgOpRegion->ELCL= MemoryRead16((UINTN)SaGlobalNvsArea->Area->EndpointPcieCapOffset + 0x10);

    
    //
    // Allocate an ACPI NVS memory buffer as the Nvidia NVHM OpRegion, zero initialize
    // the entire 62K, and set the Nvidia NVHM OpRegion pointer in the Global NVS
    // area structure.
    //
    Size    = sizeof (NVHM_OPREGION);
    Status  = (gBS->AllocatePool) (EfiACPIMemoryNVS, Size, &NvidiaOpRegion.NvHmOpRegion);

    if (EFI_ERROR (Status)) {
        (gBS->FreePool) (NvidiaOpRegion.NvIgOpRegion);
        return Status;
    }

    (gBS->SetMem) (NvidiaOpRegion.NvHmOpRegion, Size, 0);
    
    //
    // NVHM
    //
    SaGlobalNvsArea->Area->NvHmOpRegionAddress = (UINT32) (UINTN) (NvidiaOpRegion.NvHmOpRegion);
    
    //
    // NVHM Header Signature, Size, Version
    //
    (gBS->CopyMem) (NvidiaOpRegion.NvHmOpRegion->NVSG, NVHM_HEADER_SIGNATURE, sizeof (NVHM_HEADER_SIGNATURE));
    NvidiaOpRegion.NvHmOpRegion->NVSZ = NVHM_OPREGION_SIZE;
        NvidiaOpRegion.NvHmOpRegion->NVVR = NVHM_OPREGION_VER;
        
        //
        // NVHM opregion address
        //
        NvidiaOpRegion.NvHmOpRegion->NVHO = (UINT32) (UINTN) (NvidiaOpRegion.NvHmOpRegion);
        
        //
        // Copy Oprom to allocated space in NV Opregion
        //
        NvidiaOpRegion.NvHmOpRegion->RVBS = VbiosSize;
        (gBS->CopyMem) ((VOID *) (UINTN) NvidiaOpRegion.NvHmOpRegion->RBUF, VbiosAddress, NvidiaOpRegion.NvHmOpRegion->RVBS);
        
        //
        //  Locate the MXM3 Protocol and update Mxm struct pointers
        //
#if MXM30_SUPPORT == 1
        Status = gBS->LocateProtocol (
                  &EfiMxm3ProtocolGuid,
                  NULL,
                  &Mxm30Protocol
                  );
        if (!EFI_ERROR(Status))
        {
            Status = Mxm30Protocol->MxmReturnStructure(
                        Mxm30Protocol, 
                        NULL,
                        (CHAR16*)&MxmLegMemSize,
                        (CHAR16)EFI30_DataBlockID, 
                        (CHAR8**)&MxmLegMemAddr
                        );
            ASSERT_EFI_ERROR (Status);
            //
            // Copy MXM3 data structure to allocated space in NV Opregion
            //
            NvidiaOpRegion.NvHmOpRegion->MXML = MxmLegMemSize;
            (gBS->CopyMem) ((VOID *) (UINTN) NvidiaOpRegion.NvHmOpRegion->MXM3, MxmLegMemAddr, MxmLegMemSize);
    }
#endif        
    if (Status != EFI_SUCCESS) {
        (gBS->FreePool) (NvidiaOpRegion.NvIgOpRegion);
        (gBS->FreePool) (NvidiaOpRegion.NvHmOpRegion);
    }
    
    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
//Procedure: InstallAmdOpRegion
//
//Description: Amd(ATI) SG specific Asl Graphics OpRegion installation function.
//
//Input:
//
//  ImageHandle     Handle for this drivers loaded image protocol.
//  SystemTable     EFI system table.
//
//Output:
//
//  EFI_SUCCESS     The driver installed without error.
//  EFI_ABORTED     The driver encountered an error and could not complete
//                  installation of the ACPI tables.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
InstallAmdOpRegion (
  VOID
  )
{
    EFI_STATUS                    Status;
    UINTN                         Size;
    
    //
    // Allocate an ACPI NVS memory buffer as the Amd APXM OpRegion, zero initialize
    // the entire 1K, and set the Amd APXM OpRegion pointer in the Global NVS
    // area structure.
    //
    Size    = sizeof (APXM_OPREGION);
    Status  = (gBS->AllocatePool) (EfiACPIMemoryNVS, Size, &AmdOpRegion.ApXmOpRegion);
    if (EFI_ERROR (Status)) {
        return Status;
    }

    (gBS->SetMem) (AmdOpRegion.ApXmOpRegion, Size, 0);

    //
    // APXM address
    //
    SaGlobalNvsArea->Area->ApXmOpRegionAddress  = (UINT32) (UINTN) (AmdOpRegion.ApXmOpRegion);
    AmdOpRegion.ApXmOpRegion->APXA            = (UINT32) (UINTN) (AmdOpRegion.ApXmOpRegion);

    //
    // Note. All fields in Amd OpRegion will be initialized with Zeroes. 
    //       Only update those that differ from 0.

    // Set up DIDx values for _DOD
    //
    // Device ID - CRT on IGPU
    //
    SaGlobalNvsArea->Area->DeviceId1 = 0x80010100;

    //
    // Device ID - LFP (LVDS or eDP)
    //
    SaGlobalNvsArea->Area->DeviceId2 = 0x80010400;

    //
    // Display type - EFP  Device Sub type - DisplayPort 1.1
    //
    SaGlobalNvsArea->Area->DeviceId3 = 0x80010300;

    //
    // Display type - EFP  Device Sub type - HDMI 1.2 or 1.3a
    //
    SaGlobalNvsArea->Area->DeviceId4 = 0x80010301;

    //
    // Display type - EFP  Device Sub type - HDMI 1.2 or 1.3a
    //
    SaGlobalNvsArea->Area->DeviceId5 = 0x80010302;

    //
    // Display type - EFP  Device Sub type - DisplayPort 1.1
    //
    SaGlobalNvsArea->Area->DeviceId6 = 0x80010303;

    //
    // Display type - EFP  Device Sub type - HDMI 1.2 or 1.3a
    //

    //
    // SG Feature List for ASL usage
    //
    if(SaGlobalNvsArea->Area->SgFeatureList & 1)  // WIRELESSDISPLAY
        SaGlobalNvsArea->Area->DeviceId7 = 0x80010306;
    else
        SaGlobalNvsArea->Area->DeviceId7 = 0x80010304;
    //
    // DeviceId8 is not being used on HuronRiver SG
    //
    SaGlobalNvsArea->Area->DeviceId8              = 0x0;

    //
    // NDID
    //
    SaGlobalNvsArea->Area->NumberOfValidDeviceId  = VALIDDIDS;//0x7;

    //
    // APXM Header
    //
    (gBS->CopyMem) (AmdOpRegion.ApXmOpRegion->APSG, APXM_HEADER_SIGNATURE, sizeof (APXM_HEADER_SIGNATURE));
    AmdOpRegion.ApXmOpRegion->APSZ = APXM_OPREGION_SIZE;
    AmdOpRegion.ApXmOpRegion->APVR = APXM_OPREGION_VER;

    //
    // Total number of toggle list entries
    //
    AmdOpRegion.ApXmOpRegion->NTLE = 15;

    //
    // The display combinations in the list...
    //
    //
    // CRT
    //
    AmdOpRegion.ApXmOpRegion->TLEX[0] = 0x0002;
    //
    // LFP
    //
    AmdOpRegion.ApXmOpRegion->TLEX[1] = 0x0001;
    //
    // DP_B
    //
    AmdOpRegion.ApXmOpRegion->TLEX[2] = 0x0008;
    //
    // HDMI_B
    //
    AmdOpRegion.ApXmOpRegion->TLEX[3] = 0x0080;
    //
    // HDMI_C
    //
    AmdOpRegion.ApXmOpRegion->TLEX[4] = 0x0200;
    //
    // DP_D
    //
    AmdOpRegion.ApXmOpRegion->TLEX[5] = 0x0400;
    //
    // HDMI_D
    //
    AmdOpRegion.ApXmOpRegion->TLEX[6] = 0x0800;
    //
    // LFP+CRT
    //
    AmdOpRegion.ApXmOpRegion->TLEX[7] = 0x0003;
    //
    // LFP+DP_B
    //
    AmdOpRegion.ApXmOpRegion->TLEX[8] = 0x0009;
    //
    // LFP+HDMI_B
    //
    AmdOpRegion.ApXmOpRegion->TLEX[9] = 0x0081;
    //
    // LFP+HDMI_C
    //
    AmdOpRegion.ApXmOpRegion->TLEX[10] = 0x0201;
    //
    // LFP+DP_D
    //
    AmdOpRegion.ApXmOpRegion->TLEX[11] = 0x0401;
    //
    // LFP+HDMI_D
    //
    AmdOpRegion.ApXmOpRegion->TLEX[12] = 0x0801;
    //
    // Dummy 1
    //
    AmdOpRegion.ApXmOpRegion->TLEX[13] = 0x0;
    //
    // Dummy 2
    //
    AmdOpRegion.ApXmOpRegion->TLEX[14] = 0x0;

    //
    // Panel Scaling Preference
    //
    AmdOpRegion.ApXmOpRegion->EXPM = SaGlobalNvsArea->Area->IgdPanelScaling;


    // Save Link Control register
    AmdOpRegion.ApXmOpRegion->ELCL= MemoryRead16((UINTN)SaGlobalNvsArea->Area->EndpointPcieCapOffset + 0x10);


    //
    // Copy Oprom to allocated space in ATI Opregion
    //
    AmdOpRegion.ApXmOpRegion->RVBS = VbiosSize;
    (gBS->CopyMem) ((VOID *) (UINTN) AmdOpRegion.ApXmOpRegion->RBUF, VbiosAddress, AmdOpRegion.ApXmOpRegion->RVBS);

    if (Status != EFI_SUCCESS) {
      (gBS->FreePool) (AmdOpRegion.ApXmOpRegion);
    }

  return Status;
}
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**        5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093         **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
