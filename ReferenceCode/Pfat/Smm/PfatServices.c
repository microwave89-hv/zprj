/**
  This file contains an 'Intel Peripheral Driver' and is        
  licensed for Intel CPUs and chipsets under the terms of your   
  license agreement with Intel or your vendor.  This file may   
  be modified by the user, subject to additional terms of the
  license agreement
**/
/**

Copyright (c) 2011 - 2012 Intel Corporation. All rights reserved
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.

@file:

  PfatServices.c

@brief:

  PFAT Driver implements the PFAT Host Controller Compatibility Interface.

**/

///
/// External include files do NOT need to be explicitly specified in real EDKII
/// environment
///
#if !defined(EDK_RELEASE_VERSION) || (EDK_RELEASE_VERSION < 0x00020000)
#include "EdkIIGlueDxe.h"
#include "CpuAccess.h"
#include "PfatServices.h"
#include "SmmIoLib.h"
#endif

#include <Token.h>
///
/// Global variables
///
EFI_SMM_SYSTEM_TABLE               *mSmst;
PFAT_PROTOCOL                      *mPfatProtocol;
PFAT_HOB                           *mPfatHobPtr;
EFI_SMM_IO_TRAP_DISPATCH_PROTOCOL  *mPchIoTrap;

VOID
PfatUpdateBios (
  IN  EFI_HANDLE                                 DispatchHandle,
  IN  EFI_SMM_IO_TRAP_DISPATCH_CALLBACK_CONTEXT  *CallbackContext
  )
/**

@brief

  This function is triggered by the BIOS update tool with an IO trap. It executres
  Pfat protocol execute with the true flag indicating that there is an update package
  in the DPR region of memory.

  @param[in] DispatchHandle      Not used
  @param[in] CallbackContext     Not used

**/
{
  ///
  /// Invoke PFAT Services for updating BIOS
  ///
  mPfatProtocol->Execute(mPfatProtocol, TRUE);
  CopyMem (mPfatUpdatePackagePtr, &mPfatFullStatus, sizeof (UINT64));

  return;
}

VOID
PfatToolsInterfaceInit (
  IN  EFI_HANDLE                                 DispatchHandle,
  IN  EFI_SMM_IO_TRAP_DISPATCH_CALLBACK_CONTEXT  *CallbackContext
  )
/**

@brief

  This method registers and sets up the IOTRAP and NVS area for the PFAT tools interface 

  @param[in] DispatchHandle      Not used
  @param[in] CallbackContext     Not used


**/
{
  EFI_STATUS                                 Status;
  EFI_GUID                                   EfiGlobalNvsAreaProtocolGuid = EFI_GLOBAL_NVS_AREA_PROTOCOL_GUID;
  EFI_GLOBAL_NVS_AREA_PROTOCOL               *GlobalNvsAreaProtocol;
  EFI_GLOBAL_NVS_AREA                        *GlobalNvsArea;
  EFI_HANDLE                                 PchIoTrapHandle;
  EFI_SMM_IO_TRAP_DISPATCH_REGISTER_CONTEXT  PchIoTrapContext;

  ///
  /// Locate Global NVS and update PFAT DPR size & Memory address for ACPI tables
  ///
  Status = gBS->LocateProtocol (&EfiGlobalNvsAreaProtocolGuid, NULL, &GlobalNvsAreaProtocol);
  ASSERT_EFI_ERROR (Status);
  GlobalNvsArea                     = GlobalNvsAreaProtocol->Area;
  GlobalNvsArea->PfatMemAddress     = 0;
  GlobalNvsArea->PfatMemSize        = 0;
  GlobalNvsArea->PfatIoTrapAddress  = 0;
  ///
  /// Locate PFAT SMM Protocol
  ///
  Status = gBS->LocateProtocol (&gSmmPfatProtocolGuid, NULL, &mPfatProtocol);
  ASSERT_EFI_ERROR (Status);
  if(mPfatProtocol != NULL)
  {
    ///
    /// Register PFAT IO TRAP handler
    ///
    PchIoTrapContext.Type         = WriteTrap;
    PchIoTrapContext.Length       = 4;
    PchIoTrapContext.Address      = 0;
    PchIoTrapContext.Context      = NULL;
    PchIoTrapContext.MergeDisable = FALSE;
    Status = mPchIoTrap->Register (
                          mPchIoTrap,
                          PfatUpdateBios,
                          &PchIoTrapContext,
                          &PchIoTrapHandle
                          );
    ASSERT_EFI_ERROR (Status);
    ///
    /// Initialize ASL manipulation library
    ///
    InitializeAslUpdateLib ();
    Status = UpdateAslCode (
               (EFI_SIGNATURE_32 ('I', 'O', '_', 'P')),
               PchIoTrapContext.Address,
               (UINT8) PchIoTrapContext.Length
             );
    ASSERT_EFI_ERROR (Status);
    GlobalNvsArea->PfatMemAddress     = mPfatMemAddress;
    GlobalNvsArea->PfatMemSize        = (UINT8) RShiftU64(mPfatMemSize, 20);
    GlobalNvsArea->PfatIoTrapAddress  = PchIoTrapContext.Address;
  }
}




EFI_STATUS
EFIAPI
InstallPfatProtocol (
  IN EFI_HANDLE            ImageHandle,
  IN EFI_SYSTEM_TABLE      *SystemTable
  )
/**

@brief

  Entry point for the PFAT protocol driver.
  
  @param[in] ImageHandle       Image handle of this driver.
  @param[in] SystemTable       Global system service table.

  @retval EFI_SUCCESS           Initialization complete.
  @retval EFI_OUT_OF_RESOURCES  Do not have enough resources to initialize the driver.
  @retval EFI_ERROR             Driver exits abnormally.

**/
{
  EFI_STATUS                                 Status;
  EFI_SMM_BASE_PROTOCOL                      *SmmBase;
  PFAT_INSTANCE                              *PfatInstance;
  VOID                                       *PfatProtocolAddr;
  EFI_HANDLE                                 PchIoTrapHandle;
  EFI_SMM_IO_TRAP_DISPATCH_REGISTER_CONTEXT  PchIoTrapContext;
  EFI_GUID                                   EfiSmmIoTrapDispatchProtocolGuid = EFI_SMM_IO_TRAP_DISPATCH_PROTOCOL_GUID;
#if defined (Pfat_Enable_Pei) && (Pfat_Enable_Pei==0)
  EFI_GUID                      	         PfatHobGuid     = PFAT_HOB_GUID;
  PFAT_HOB 		         	                *PfatModuleCheck;
  UINT8                                      Data8And = 0;
  UINT8                                      Data8Or = 0;
#endif

  ///
  /// Locate SMM Base Protocol
  ///
  Status = gBS->LocateProtocol (&gEfiSmmBaseProtocolGuid, NULL, &SmmBase);
  ASSERT_EFI_ERROR (Status);

  ///
  /// Initialize our module variables
  ///
  Status = SmmBase->GetSmstLocation (SmmBase, &mSmst);
  ASSERT_EFI_ERROR (Status);

  ///
  /// Allocate pool for PFAT protocol instance
  ///
  Status = mSmst->SmmAllocatePool (
                    EfiRuntimeServicesData,
                    sizeof (PFAT_INSTANCE),
                    &PfatInstance
                    );
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_INFO, "PFAT SmmAllocatePool failed\n"));
    return Status;
  }

  if (PfatInstance == NULL) {
    DEBUG ((EFI_D_INFO, "PfatInstance = NULL returning\n"));
    return EFI_OUT_OF_RESOURCES;
  }

#if defined (Pfat_Enable_Pei) && (Pfat_Enable_Pei==0)
      //pfat hob is created when pfat is enabled (pfatinit.c)
      //verify presence of pfat hob

     PfatModuleCheck = GetFirstGuidHob (&PfatHobGuid);

     if (PfatModuleCheck != NULL) {
	Data8And  = 0xFF;
	Data8Or   = (UINT8) (B_PCH_LPC_BIOS_CNTL_SMM_BWP + B_PCH_LPC_BIOS_CNTL_BLE);

	MmioAndThenOr8 (
      		MmPciAddress (0,
    		0,
    		PCI_DEVICE_NUMBER_PCH_LPC,
    		PCI_FUNCTION_NUMBER_PCH_LPC,
    		R_PCH_LPC_BIOS_CNTL),
    		Data8And,
    		Data8Or);
     }

#endif

  ZeroMem ((VOID *) PfatInstance, sizeof (PFAT_INSTANCE));
  PfatInstance->Handle = NULL;
  PfatProtocolAddr     = NULL;

  if ((AsmReadMsr64 (MSR_PLATFORM_INFO)) & B_MSR_PLATFORM_INFO_PFAT_AVAIL) {
    if ((AsmReadMsr64 (MSR_PLAT_FRMW_PROT_CTRL)) & B_MSR_PLAT_FRMW_PROT_CTRL_EN) {
      ///
      /// Initialize the PFAT protocol instance
      ///
      Status = PfatProtocolConstructor (PfatInstance);
      if (EFI_ERROR (Status)) {
          DEBUG ((EFI_D_ERROR, "Error from Pfat Protocol Constructor\n"));
        return Status;
      }
      PfatProtocolAddr = &(PfatInstance->PfatProtocol);
      Status = gBS->LocateProtocol (&EfiSmmIoTrapDispatchProtocolGuid, NULL, &mPchIoTrap);
      ASSERT_EFI_ERROR (Status);

      PchIoTrapContext.Type         = ReadTrap;
      PchIoTrapContext.Length       = 4;
      PchIoTrapContext.Address      = 0;
      PchIoTrapContext.Context      = NULL;
      PchIoTrapContext.MergeDisable = FALSE;
      Status = mPchIoTrap->Register (
                            mPchIoTrap,
                            PfatToolsInterfaceInit,
                            &PchIoTrapContext,
                            &PchIoTrapHandle
                            );
      ASSERT_EFI_ERROR (Status);

      mPfatHobPtr->PfatToolsIntIoTrapAdd = PchIoTrapContext.Address;
    } else {
      DEBUG ((EFI_D_INFO, "PFAT Feature supported but disabled\n"));
    }
  } else {
    DEBUG ((EFI_D_WARN, "PFAT Feature is not supported\n"));
  }

  ///
  /// Install the SMM PFAT_PROTOCOL interface
  ///
  Status = gBS->InstallMultipleProtocolInterfaces (
                  &(PfatInstance->Handle),
                  &gSmmPfatProtocolGuid,
                  PfatProtocolAddr,
                  NULL
                  );
  if (EFI_ERROR (Status)) {
    mSmst->SmmFreePool (PfatInstance);
    DEBUG ((EFI_D_ERROR, "Failure Installing PFAT protocol\n"));
  }

  DEBUG ((EFI_D_ERROR, "PFAT protocol Installed\n"));
  return Status;
}




EFI_STATUS
PfatProtocolConstructor (
  PFAT_INSTANCE          *PfatInstance
  )
/**

@brief

  Initialize PFAT protocol instance.

  @param[in] PfatInstance           Pointer to PfatInstance to initialize

  @retval EFI_SUCCESS               The protocol instance was properly initialized
  @retval EFI_NOT_FOUND             PFAT Binary module was not found.

**/
{
  EFI_STATUS                    Status;
  PPDT                          *Ppdt;
  UINTN                         i;
  UINTN                         NumHandles;
  EFI_HANDLE                    *Buffer;
  UINTN                         Size;
  UINT32                        FvStatus;
  EFI_FV_FILETYPE               FileType;
  EFI_FIRMWARE_VOLUME_PROTOCOL  *FwVol;
  EFI_FV_FILE_ATTRIBUTES        Attributes;
  UINTN                         NumPages;
  EFI_PHYSICAL_ADDRESS          Addr;
  EFI_PHYSICAL_ADDRESS          PfatModule;
  SA_DATA_HOB                   *SaDataHobPtr;
  EFI_GUID                      PfatModuleGuid  = PFAT_MODULE_GUID;
  EFI_GUID                      PfatHobGuid     = PFAT_HOB_GUID;
  EFI_GUID                      SaDataHobGuid   = SA_DATA_HOB_GUID;

  FwVol           = NULL;
  Size            = 0;
  FvStatus        = 0;
  NumPages        = 0;
  Addr            = 0;

  IoWrite8(0x80, 0xAA);
  Status = gBS->LocateHandleBuffer (
                  ByProtocol,
                  &gEfiFirmwareVolumeProtocolGuid,
                  NULL,
                  &NumHandles,
                  &Buffer
                  );
  ASSERT_EFI_ERROR (Status);

  for (i = 0; i < NumHandles; i++) {
    Status = gBS->HandleProtocol (
                    Buffer[i],
                    &gEfiFirmwareVolumeProtocolGuid,
                    &FwVol
                    );
    ASSERT_EFI_ERROR (Status);

    ///
    /// Locate PFAT Binary.
    ///
    Status = FwVol->ReadFile (
                      FwVol,
                      &PfatModuleGuid,
                      NULL,
                      &Size,
                      &FileType,
                      &Attributes,
                      &FvStatus
                      );
    if (Status == EFI_SUCCESS) {
      break;
    }
  }

  FreePool (Buffer);
  ASSERT (Size);
  if ((FwVol == NULL) || (Size == 0)) {
    return EFI_NOT_FOUND;
  }
  NumPages = PFAT_MEMORY_PAGES + ALIGNMENT_IN_PAGES;

  ///
  /// Allocate memory buffer for PFAT Module
  ///
  Status = (mSmst->SmmAllocatePages) (AllocateAnyPages, EfiRuntimeServicesData, NumPages, &Addr);
  ASSERT_EFI_ERROR (Status);

  ///
  /// Align address to 256K.
  ///
  PfatModule  = Addr &~(ALIGN_256KB - 1);
  PfatModule  = PfatModule < Addr ? (PfatModule + ALIGN_256KB) : PfatModule;

  ///
  /// Read PFAT Module into prepared buffer.
  ///
  Status = FwVol->ReadFile (
                    FwVol,
                    &PfatModuleGuid,
                    &((VOID *) PfatModule),
                    &Size,
                    &FileType,
                    &Attributes,
                    &FvStatus
                    );
  ASSERT (Size);
  if ((FwVol == NULL) || (Size == 0)) {
    return EFI_NOT_FOUND;
  }

  mPfatHobPtr = GetFirstGuidHob (&PfatHobGuid);
  if (mPfatHobPtr == NULL) {
    DEBUG ((EFI_D_ERROR, "PFAT HOB not available\n"));
    return EFI_NOT_FOUND;
  }

  SaDataHobPtr = GetFirstGuidHob (&SaDataHobGuid);
  if (SaDataHobPtr == NULL) {
    DEBUG ((EFI_D_ERROR, "SA Data HOB not available\n"));
    return EFI_NOT_FOUND;
  }

  ///
  /// Allocate pool for PPDT Data
  ///
  Status = mSmst->SmmAllocatePool (
                    EfiRuntimeServicesData,
                    mPfatHobPtr->Ppdt.PpdtSize,
                    &Ppdt
                    );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  CopyMem (Ppdt, &mPfatHobPtr->Ppdt, mPfatHobPtr->Ppdt.PpdtSize);

  mPfatMemAddress        = SaDataHobPtr->DprDirectory[EnumDprDirectoryPfat].PhysBase;
  mPfatMemSize           = (UINT32) LShiftU64(SaDataHobPtr->DprDirectory[EnumDprDirectoryPfat].Size, 20);
  mPfatUpdatePackagePtr  = (PUP *) mPfatMemAddress;
  mPupCertificate        = (EFI_PHYSICAL_ADDRESS) (mPfatMemAddress + mPfatMemSize - PUPC_MEMORY_OFFSET);
  mPfatLogPtr            = (PFAT_LOG *) (mPfatMemAddress + mPfatMemSize - PFAT_LOG_MEMORY_OFFSET);

  CopyMem (&mPfatLogTemp, &mPfatHobPtr->PfatLog, sizeof (PFAT_LOG));
  CopyMem (&mPfatUpdatePackagePtr->PupHeader, &mPfatHobPtr->PupHeader, sizeof (PUP_HEADER));
  ZeroMem (mPfatUpdatePackagePtr->PupBuffer, PUP_BUFFER_SIZE);
  mPfatUpdatePackagePtr->PupHeader.ScriptSectionSize  = 0;
  mPfatUpdatePackagePtr->PupHeader.DataSectionSize    = 0;
  mPfatUpdateCounter = 0;

  ///
  /// Set Begin command
  ///
  mPfatUpdatePackagePtr->PupBuffer[mPfatUpdateCounter++] = PFAT_COMMAND_BEGIN;

  ///
  /// Initialize the PFAT protocol instance
  ///
  PfatInstance->Signature             = PFAT_SIGNATURE;
  PfatInstance->PfatProtocol.Write    = PfatProtocolWrite;
  PfatInstance->PfatProtocol.Erase    = PfatProtocolBlockErase;
  PfatInstance->PfatProtocol.Execute  = PfatProtocolExecute;
  PfatInstance->AddrMask              = 0;
  for (i = 0; i < mPfatHobPtr->NumSpiComponents; i++) {
    PfatInstance->AddrMask += (SPI_SIZE_BASE_512KB << mPfatHobPtr->ComponentSize[i]);
  }
  PfatInstance->AddrMask -= 1;

  PfatInstance->PfatDirectory[EnumPfatModule]        = PfatModule;
  PfatInstance->PfatDirectory[EnumPfatModule]       |= LShiftU64 (PFAT_DIRECTORY_PFAT_MODULE_ENTRY, 56);
  PfatInstance->PfatDirectory[EnumPpdt]              = (EFI_PHYSICAL_ADDRESS) Ppdt;
  PfatInstance->PfatDirectory[EnumPpdt]             |= LShiftU64 (PFAT_DIRECTORY_PPDT_ENTRY, 56);
  PfatInstance->PfatDirectory[EnumPup]               = (EFI_PHYSICAL_ADDRESS) mPfatUpdatePackagePtr;
  PfatInstance->PfatDirectory[EnumPup]              |= LShiftU64(PFAT_DIRECTORY_PUP_ENTRY, 56);
  PfatInstance->PfatDirectory[EnumPupCertificate]    = 0;
  PfatInstance->PfatDirectory[EnumPupCertificate]   |= LShiftU64(PFAT_DIRECTORY_UNDEFINED_ENTRY, 56);
  PfatInstance->PfatDirectory[EnumPfatLog]           = 0;
  PfatInstance->PfatDirectory[EnumPfatLog]          |= LShiftU64(PFAT_DIRECTORY_UNDEFINED_ENTRY, 56);
  PfatInstance->PfatDirectory[EnumPfatDirectoryEnd]  = 0;
  PfatInstance->PfatDirectory[EnumPfatDirectoryEnd] |= LShiftU64 (PFAT_DIRECTORY_END_MARKER, 56);

  return EFI_SUCCESS;
}

VOID
PfatModuleExecute (
  IN PFAT_INSTANCE          *PfatInstance
  )
/**

@brief
  
  Set MSR 0x115 with PFAT DIRECTORY Address.
  Trigger MSR 0x116 to invoke PFAT Binary.
  Read MSR 0x115 to get PFAT Binary Status.
  
  @param[in] PfatInstance              Pointer to PfatInstance to initialize

**/
{
  AsmWriteMsr64 (MSR_PLAT_FRMW_PROT_TRIG_PARAM, (UINT64) PfatInstance->PfatDirectory);
  AsmWriteMsr64 (MSR_PLAT_FRMW_PROT_TRIGGER, 0);
  ///
  /// Read MSR_PLAT_FRMW_PROT_TRIG_PARAM to get PFAT Binary status
  ///
  PfatInstance->MsrValue = AsmReadMsr64 (MSR_PLAT_FRMW_PROT_TRIG_PARAM);
  return ;
}

EFI_STATUS
EFIAPI
PfatProtocolExecute (
  IN     PFAT_PROTOCOL  *This,
  IN     BOOLEAN        BiosUpdate
  )
/**

@brief
  
  Set PFAT DIRECTORY Address and triggers MSR to pass control to PFAT Binary module to execute command script.
  This function would be called by runtime driver, please do not use any MMIO macro here
  
  @param[in] This                   Pointer to the PFAT_PROTOCOL instance.
  @param[in] BiosUpdate             Flag to indicate flash update is requested by the Tool

  @retval EFI_SUCCESS               Command succeed.
  @retval EFI_INVALID_PARAMETER     The parameters specified are not valid.
  @retval EFI_UNSUPPORTED           The CPU or SPI memory is not supported.
  @retval EFI_DEVICE_ERROR          Device error, command aborts abnormally.

**/
{
  EFI_STATUS            Status;
  PFAT_INSTANCE         *PfatInstance;
  UINT16                PfatStatus;
  UINT16                PfatAdditionalData;
  UINT16                PfatTerminalLine;
  UINT8                 PfatSE;
  UINTN                 Index;
  UINT8                 RetryIteration;
  UINTN                 i=0;

  PfatInstance = PFAT_INSTANCE_FROM_PFATPROTOCOL (This);

  ///
  /// If Update Package has been created during runtime then complete the script
  /// and create update Pkg
  ///
  if (BiosUpdate == FALSE) {
    ///
    /// End command
    ///
    mPfatUpdatePackagePtr->PupBuffer[mPfatUpdateCounter++]  = PFAT_COMMAND_END;
    mPfatUpdatePackagePtr->PupHeader.ScriptSectionSize      = (mPfatUpdateCounter * 8);
    CopyMem (
      &mPfatUpdatePackagePtr->PupBuffer[mPfatUpdateCounter],
      &mPfatUpdateData,
      (mPfatUpdatePackagePtr->PupHeader.DataSectionSize)
    );
    PfatInstance->PfatDirectory[EnumPfatLog]          = (EFI_PHYSICAL_ADDRESS) mPfatLogPtr;
    PfatInstance->PfatDirectory[EnumPfatLog]         |= LShiftU64(PFAT_DIRECTORY_PFAT_LOG_ENTRY, 56);

  } else {
    CopyMem (mPfatLogPtr, &mPfatLogTemp, sizeof (PFAT_LOG));
    if (mPfatUpdatePackagePtr->PupHeader.PkgAttributes) {
      PfatInstance->PfatDirectory[EnumPupCertificate]   = mPupCertificate;
      PfatInstance->PfatDirectory[EnumPupCertificate]  |= LShiftU64(PFAT_DIRECTORY_PUP_CERTIFICATE_ENTRY, 56);
      PfatInstance->PfatDirectory[EnumPfatLog]          = (EFI_PHYSICAL_ADDRESS) mPfatLogPtr;
      PfatInstance->PfatDirectory[EnumPfatLog]         |= LShiftU64(PFAT_DIRECTORY_PFAT_LOG_ENTRY, 56);
    } else {
      PfatInstance->PfatDirectory[EnumPupCertificate]   = 0;
      PfatInstance->PfatDirectory[EnumPupCertificate]  |= LShiftU64(PFAT_DIRECTORY_UNDEFINED_ENTRY, 56);
      PfatInstance->PfatDirectory[EnumPfatLog]          = (EFI_PHYSICAL_ADDRESS) mPfatLogPtr;
      PfatInstance->PfatDirectory[EnumPfatLog]         |= LShiftU64(PFAT_DIRECTORY_PFAT_LOG_ENTRY, 56);
    }
  }

  PfatInstance->MsrValue = ERR_LAUNCH_FAIL;

  for (Index = 1; Index < mSmst->NumberOfCpus; Index++) {
    Status = EFI_NOT_READY;
    for (RetryIteration = 0; (RetryIteration < PFAT_AP_SAFE_RETRY_LIMIT) && (Status != EFI_SUCCESS); RetryIteration++) {

      Status = mSmst->SmmStartupThisAp (PfatModuleExecute, Index, PfatInstance);

      if (Status != EFI_SUCCESS) {
        ///
        /// SmmStartupThisAp might return failure if AP is busy executing some other code. Let's wait for sometime and try again.
        ///
        PchPmTimerStall (PFAT_WAIT_PERIOD);
      }
    }
  }

  PfatModuleExecute (PfatInstance);

  if (BiosUpdate == FALSE) {
    PfatStatus = (UINT16) RShiftU64 (
                            (PfatInstance->MsrValue & LShiftU64 (V_MSR_PLAT_FRMW_PROT_TRIG_PARAM_STATUS_MASK,
                             N_MSR_PLAT_FRMW_PROT_TRIG_PARAM_STATUS_OFFSET)),
                             N_MSR_PLAT_FRMW_PROT_TRIG_PARAM_STATUS_OFFSET
                            );
    switch (PfatStatus) {
    case ERR_OK:
      Status = EFI_SUCCESS;
      break;

    case ERR_RANGE_VIOLATION:
    case ERR_SFAM_VIOLATION:
    case ERR_EXEC_LIMIT:
    case ERR_INTERNAL_ERROR:
      Status = EFI_DEVICE_ERROR;
      break;

    case ERR_UNSUPPORTED_CPU:
    case ERR_UNDEFINED_FLASH_OBJECT:
    case ERR_LAUNCH_FAIL:
      Status = EFI_UNSUPPORTED;
      break;

    default:

    case ERR_BAD_DIRECTORY:
    case ERR_BAD_PPDT:
    case ERR_BAD_PUP:
    case ERR_SCRIPT_SYNTAX:
    case ERR_INVALID_LINE:
    case ERR_BAD_PUPC:
    case ERR_BAD_SVN:
    case ERR_UNEXPECTED_OPCODE:
    case ERR_OVERFLOW:
      Status = EFI_INVALID_PARAMETER;
      break;
    }

    if (EFI_ERROR (Status)) {
      PfatAdditionalData = (UINT16) RShiftU64 (
                                      (PfatInstance->MsrValue & LShiftU64 (V_MSR_PLAT_FRMW_PROT_TRIG_PARAM_DATA_MASK,
                                       N_MSR_PLAT_FRMW_PROT_TRIG_PARAM_DATA_OFFSET)),
                                       N_MSR_PLAT_FRMW_PROT_TRIG_PARAM_DATA_OFFSET
                                      );
      PfatTerminalLine = (UINT16) RShiftU64 (
                                    (PfatInstance->MsrValue & LShiftU64 (V_MSR_PLAT_FRMW_PROT_TRIG_PARAM_TERMINAL_MASK,
                                     N_MSR_PLAT_FRMW_PROT_TRIG_PARAM_TERMINAL_OFFSET)),
                                     N_MSR_PLAT_FRMW_PROT_TRIG_PARAM_TERMINAL_OFFSET
                                    );
      PfatSE = (UINT8) RShiftU64 (
                         (PfatInstance->MsrValue & B_MSR_PLAT_FRMW_PROT_TRIG_PARAM_SE),
                          N_MSR_PLAT_FRMW_PROT_TRIG_PARAM_SE_OFFSET
                         );
      DEBUG ((EFI_D_ERROR, "PFAT Status          = 0x%X\n", PfatStatus));
      DEBUG ((EFI_D_ERROR, "PFAT Additional Data = 0x%X\n", PfatAdditionalData));
      DEBUG ((EFI_D_ERROR, "PFAT Terminal Line   = 0x%X\n", PfatTerminalLine));
      DEBUG ((EFI_D_ERROR, "PFAT SE              = 0x%X\n", PfatSE));
    }

    ZeroMem (mPfatUpdatePackagePtr->PupBuffer, PUP_BUFFER_SIZE);
    mPfatUpdatePackagePtr->PupHeader.ScriptSectionSize  = 0;
    mPfatUpdatePackagePtr->PupHeader.DataSectionSize    = 0;
    mPfatUpdateCounter = 0;

    ///
    /// Begin command
    ///
    mPfatUpdatePackagePtr->PupBuffer[mPfatUpdateCounter++] = PFAT_COMMAND_BEGIN;
  } else {
    IoWrite16(0x80, (UINT16)(PfatInstance->MsrValue >> 16));
    mPfatFullStatus = PfatInstance->MsrValue;
    Status = EFI_SUCCESS;
  }  

  return Status;
}


VOID
EFIAPI
PfatProtocolWrite (
  IN     PFAT_PROTOCOL  *This,
  IN     UINTN          Address,
  IN     UINT32         DataByteCount,
  IN OUT UINT8          *Buffer
  )
/**

@brief
  
  Fill up Write script data into the PFAT Script buffer.
  This function would be called by runtime driver, please do not use any MMIO macro here
  
  @param[in] This                      Pointer to the PFAT_PROTOCOL instance.
  @param[in] Address                   This value specifies the offset from the start of the SPI Flash component where
                                       BIOS Image is located.
  @param[in] DataByteCount             Number of bytes in the data portion.
  @param[in] Buffer                    Pointer to caller-allocated buffer containing the data to be sent.


**/
{
  PFAT_INSTANCE *PfatInstance;

  PfatInstance = PFAT_INSTANCE_FROM_PFATPROTOCOL (This);

  ///
  /// Set Buffer Offset Index immediate command
  ///
  mPfatUpdatePackagePtr->PupBuffer[mPfatUpdateCounter++] =
    (LShiftU64 ((UINTN) mPfatUpdatePackagePtr->PupHeader.DataSectionSize, 32)) |
    (LShiftU64 (PFAT_B0_INDEX, 16)) |
    PFAT_COMMAND_SET_BUFFER_INDEX;
  ///
  /// Set Flash Index immediate command
  ///
  mPfatUpdatePackagePtr->PupBuffer[mPfatUpdateCounter++] = (LShiftU64 ((Address & PfatInstance->AddrMask), 32)) | (LShiftU64 (PFAT_F0_INDEX, 16)) | PFAT_COMMAND_SET_FLASH_INDEX;
  ///
  /// Write to Flash Index from Buffer Offset Index with specific Size command
  ///
  mPfatUpdatePackagePtr->PupBuffer[mPfatUpdateCounter++] = (LShiftU64 (DataByteCount, 32)) | (LShiftU64 (PFAT_B0_INDEX, 24)) | (LShiftU64 (PFAT_F0_INDEX, 16)) | PFAT_COMMAND_WRITE_IMM;

  CopyMem (&mPfatUpdateData[mPfatUpdatePackagePtr->PupHeader.DataSectionSize], Buffer, DataByteCount);

  mPfatUpdatePackagePtr->PupHeader.DataSectionSize += DataByteCount;

  return ;
}

VOID
EFIAPI
PfatProtocolBlockErase (
  IN     PFAT_PROTOCOL  *This,
  IN     UINTN          Address
  )
/**

@brief
  
  Fill up Erase script data into the PFAT Script buffer.
  This function would be called by runtime driver, please do not use any MMIO macro here
  
  @param[in] This                      Pointer to the PFAT_PROTOCOL instance.
  @param[in] Address                   This value specifies the offset from the start of the SPI Flash component where
                                       BIOS Image is located.

**/
{
  PFAT_INSTANCE *PfatInstance;

  PfatInstance = PFAT_INSTANCE_FROM_PFATPROTOCOL (This);

  ///
  /// Set Flash Index immediate command
  ///
  mPfatUpdatePackagePtr->PupBuffer[mPfatUpdateCounter++] = (LShiftU64 ((Address & PfatInstance->AddrMask), 32)) | (LShiftU64 (PFAT_F0_INDEX, 16)) | PFAT_COMMAND_SET_FLASH_INDEX;
  ///
  /// Erase Flash Index command
  ///
  mPfatUpdatePackagePtr->PupBuffer[mPfatUpdateCounter++] = (LShiftU64 (PFAT_F0_INDEX, 16)) | PFAT_COMMAND_ERASE_BLK;

  mPfatUpdatePackagePtr->PupHeader.DataSectionSize += 0;

  return ;
}
