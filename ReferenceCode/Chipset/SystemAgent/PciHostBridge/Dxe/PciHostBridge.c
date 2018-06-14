/** @file
  Provides the basic interfaces to abstract a PCI Host Bridge Resource Allocation

@copyright
  Copyright (c) 1999 - 2012 Intel Corporation. All rights reserved
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
#include "Token.h"   // <<< AMI_OVERRIDE
#include "PciHostBridge.h"
#include "PciRootBridge.h"
#include "PchAccess.h" 			// <<< AMI_OVERRIDE - EIP# 42483 - Support for Multi-Monitor	>>>
#ifndef GUID_VARIABLE_DECLARATION // AMI_OVERRIDE ... EIP#42483: MemCeiling support	<<>>
#define GUID_VARIABLE_DECLARATION(Variable, Guid) extern EFI_GUID Variable
#endif
#include <Protocol\NBMemInfo.h> // AMI_OVERRIDE ... EIP#42483: MemCeiling support	<<>>
///
/// Support 64 K IO space
/// Moving RES_IO_BASE due to new ACPI Base address 0x1800
///
#define RES_IO_BASE   0x2000
#define RES_IO_LIMIT  0xFFFF

///
/// Support 4G address space
///
#define RES_MEM_LIMIT_1 ((UINTN) MmPciAddress (0,0,0,0,0) - 1)

///
/// Hard code: Root Bridge Number within the host bridge
///            Root Bridge's attribute
///            Root Bridge's device path
///            Root Bridge's resource aperture
///
static UINTN                              RootBridgeNumber[1] = { 1 };
///
/// Hard code EFI_PCI_HOST_BRIDGE_COMBINE_MEM_PMEM  0 to support prefetchable memory allocation
///
#ifdef AMI_COMBINE_MEM_PMEM_FLAG
static UINT64                             RootBridgeAttribute[1][1] = { EFI_PCI_HOST_BRIDGE_COMBINE_MEM_PMEM };
#else // AMI_COMBINE_MEM_PMEM_FLAG
static UINT64                             RootBridgeAttribute[1][1] = { 0 };
#endif // AMI_COMBINE_MEM_PMEM_FLAG
static EFI_PCI_ROOT_BRIDGE_DEVICE_PATH    mEfiPciRootBridgeDevicePath[1][1] = {
  {
    ACPI_DEVICE_PATH,
    ACPI_DP,
    (UINT8) (sizeof (ACPI_HID_DEVICE_PATH)),
    (UINT8) ((sizeof (ACPI_HID_DEVICE_PATH)) >> 8),
    EISA_PNP_ID(0x0A03),
    0,
    END_DEVICE_PATH_TYPE,
    END_ENTIRE_DEVICE_PATH_SUBTYPE,
    END_DEVICE_PATH_LENGTH,
    0
  }
};

static PCI_ROOT_BRIDGE_RESOURCE_APERTURE  mResAperture[1][1] = { { 0, ((UINT8)((PCIEX_LENGTH >> 20) - 1)), 0, 0xffffffff, 0, 1 << 16 } }; // <<< AMI_OVERRIDE
static EFI_HANDLE                         mDriverImageHandle;
CHAR16 gMemoryCeilingVariable[]     = L"MemCeil.";			// AMI_OVERRIDE ... EIP#42483: MemCeiling support	<<>>
EFI_GUID gEfiNbMrcS3DataGuid = EFI_NB_MRC_S3_DATA_GUID; // AMI_OVERRIDE ... EIP#42483: MemCeiling support	<<>>

// AMI_OVERRIDE ... Fixed GenericSio use 0x0 ~ 0xfff issue start.
// It will Override CoreAllocateIoSpace.
static EFI_ALLOCATE_IO_SPACE   gAmiCoreAllocateIoSpace;

EFI_STATUS
NbCspOverrideCoreAllocateIoSpace (
  IN     EFI_GCD_ALLOCATE_TYPE  GcdAllocateType,
  IN     EFI_GCD_IO_TYPE        GcdIoType,
  IN     UINTN                  Alignment,
  IN     UINT64                 Length,
  IN OUT EFI_PHYSICAL_ADDRESS   *BaseAddress,
  IN     EFI_HANDLE             ImageHandle,
  IN     EFI_HANDLE             DeviceHandle OPTIONAL
  )
{
  EFI_STATUS	Status;
  EFI_GCD_IO_SPACE_DESCRIPTOR  IoDescriptor;

  if (GcdIoType == EfiGcdIoTypeIo && *BaseAddress < RES_IO_BASE)
  {
     if(GcdAllocateType == EfiGcdAllocateAddress)
     {
         Status = gDS->GetIoSpaceDescriptor(*BaseAddress, &IoDescriptor);
         if(!EFI_ERROR(Status))
         {
            if(IoDescriptor.GcdIoType == EfiGcdIoTypeNonExistent)
            {
               Status = gDS->AddIoSpace (
                         EfiGcdIoTypeIo,
                         *BaseAddress,
                         Length
                         );
//               ASSERT_EFI_ERROR (Status);
            }
         }
     }
  }

  return gAmiCoreAllocateIoSpace (
                 GcdAllocateType,
                 GcdIoType,
                 Alignment,
                 Length,
                 BaseAddress,
                 ImageHandle,
                 DeviceHandle
                 );
}
// AMI_OVERRIDE ... Fixed GenericSio use 0x0 ~ 0xfff issue end.

//AMI_OVERRIDE START     // AMI_OVERRIDE ... EIP#42483: MemCeiling support   ...Start...
EFI_STATUS
HbCspAdjustMemoryMmioOverlap (
    PCI_ROOT_BRIDGE_INSTANCE          *RootBridgeInstance
 )
{
	EFI_STATUS	Status;
    EFI_GCD_MEMORY_SPACE_DESCRIPTOR *MemorySpaceMap;
    UINTN           NumberOfDescriptors;
	PCI_RES_NODE	res;
    UINTN           i;
    EFI_PHYSICAL_ADDRESS Highest4GMem    = 0;
    EFI_PHYSICAL_ADDRESS LowestMMIO      = 0xffffffff;
    EFI_PHYSICAL_ADDRESS LowestAllocMMIO = 0xffffffff;
	UINTN	        MemoryCeiling = 0;      //Init to zero incase variable doesn't exist.
    UINTN           NewMemoryCeiling = 0xffffffff;
    UINTN	        DataSize = sizeof(UINT32);
    EFI_PHYSICAL_ADDRESS NeededBottomMmio;
    UINT32          Attributes = 0;             // [ EIP167027 ]

//------------------------------------
    //Status = gRT->GetVariable (               // [ EIP167027 ]
    //                 gMemoryCeilingVariable,
    //                 &gEfiNbMrcS3DataGuid,
    //                 NULL,
    //                 &DataSize,
    //                 &MemoryCeiling );
    Status = gRT->GetVariable (
                     gMemoryCeilingVariable,
                     &gEfiNbMrcS3DataGuid,
                     &Attributes,
                     &DataSize,
                     &MemoryCeiling );

    DEBUG((-1, "OEM trace - GetVariable MemCeil Status = %r\n", Status));

    if (EFI_ERROR(Status))
        Attributes = EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS;

    if (Status == EFI_NOT_FOUND) {
      //Status = gRT->GetVariable (             // [ EIP167027 ]
      //                 gMemoryCeilingVariable,
      //                 &gEfiGlobalVariableGuid,
      //                 NULL,
      //                 &DataSize,
      //                 &MemoryCeiling
      //         );
      Status = gRT->GetVariable (
                       gMemoryCeilingVariable,
                       &gEfiGlobalVariableGuid,
                       &Attributes,
                       &DataSize,
                       &MemoryCeiling
               );

      if (!EFI_ERROR(Status)) {
        //gRT->SetVariable (                    // [ EIP167027 ]
        //        gMemoryCeilingVariable,
        //        &gEfiNbMrcS3DataGuid,
        //        EFI_VARIABLE_NON_VOLATILE
        //                + EFI_VARIABLE_BOOTSERVICE_ACCESS
        //                + EFI_VARIABLE_RUNTIME_ACCESS,
        //        DataSize,
        //        &MemoryCeiling
        //);
        gRT->SetVariable (
                gMemoryCeilingVariable,
                &gEfiNbMrcS3DataGuid,
                Attributes,
                DataSize,
                &MemoryCeiling
        );
      }
      else
        Attributes = EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS;
    }

    //Memory sizing uses memory ceiling to set top of memory.

    Status = gDS->GetMemorySpaceMap(&NumberOfDescriptors, &MemorySpaceMap);
    ASSERT_EFI_ERROR(Status);

    //Find the lowest MMIO and lowest allocated MMIO in GCD.
    for(i = 0; i < NumberOfDescriptors; ++i) {
        EFI_GCD_MEMORY_SPACE_DESCRIPTOR *Descr = &MemorySpaceMap[i];
        EFI_PHYSICAL_ADDRESS Base = Descr->BaseAddress;
        //Find highest system below 4GB memory.
        //Treat any non MMIO as system memory. Not all system memory is reported as system memory,
        //such as SMM.
        if (Descr->GcdMemoryType != EfiGcdMemoryTypeMemoryMappedIo && Base < LowestMMIO) {
            EFI_PHYSICAL_ADDRESS EndMem = Base + Descr->Length - 1;
            if (EndMem > Highest4GMem && EndMem <= 0xffffffff) Highest4GMem = EndMem;

        //Find Lowest mmio above system memory.
        } else if (Descr->GcdMemoryType == EfiGcdMemoryTypeMemoryMappedIo) {
            if (Base >= 0x100000) {
                if (Base < LowestMMIO) LowestMMIO = Base;
                //If ImageHandle, then MMIO is allocated.
                if (Base < LowestAllocMMIO && Descr->ImageHandle) LowestAllocMMIO = Base;
            }
        }
    }

    (gBS->FreePool)(MemorySpaceMap);

    if (Highest4GMem + 1 != LowestMMIO) {
        DEBUG((-1, "PciHostCSHooks: System Memory and MMIO are not consequitive.\n  Top of Below 4G Memory: %lX\n   Bottom of MMIO: %x%x\n",
            Highest4GMem, LowestMMIO ));
    }

    //Find any MMIO that could not be allocated due to small of MMIO region.
    NeededBottomMmio = LowestAllocMMIO;
	for(i = 0; i < TypeMax; ++i) {

		res=RootBridgeInstance->ResAllocNode[i];
        if ((res.Type == TypeMem32 && (res.Status != ResNone) && (res.Status != ResAllocated)) ||
                (res.Type == TypePMem32 && (res.Status != ResNone) && (res.Status != ResAllocated))) {
            //Determine new memory ceiling variable needed to allocate this memory.
            NeededBottomMmio = NeededBottomMmio - res.Length;
            NeededBottomMmio &= ~(res.Alignment);
            if (NeededBottomMmio < NewMemoryCeiling) NewMemoryCeiling = (UINTN) NeededBottomMmio;
        }
    }

    if (NewMemoryCeiling < 0xffffffff) {    //Check if a NewMemory Ceiling is needed.

        // Adjust the granularity
        NewMemoryCeiling &= (~(TOP_LOW_MEM_GRANULARITY - 1));

        if (MemoryCeiling == NewMemoryCeiling) return EFI_SUCCESS;  //No change in system configuration. Nothing more to do. Just exit.

        // Change in system config, so MMIO requirement changed. Update MemCeil and do reset.
		// Set memory ceiling variable.
		//gRT->SetVariable(                     // [ EIP167027 ]
		//	gMemoryCeilingVariable,
		//	&gEfiNbMrcS3DataGuid,
		//	EFI_VARIABLE_NON_VOLATILE
		//		+ EFI_VARIABLE_BOOTSERVICE_ACCESS
		//		+ EFI_VARIABLE_RUNTIME_ACCESS,
		//	DataSize,
		//	&NewMemoryCeiling
		//);
		gRT->SetVariable(
			gMemoryCeilingVariable,
			&gEfiNbMrcS3DataGuid,
			Attributes,
			DataSize,
			&NewMemoryCeiling
		);

        DEBUG((-1, "Adjusting maximum top of RAM.\n Resetting System.\n"));

#if (NV_SIMULATION != 1)
        //Reset only needed of type of physical memory overlaps with MMIO.
	gRT->ResetSystem (EfiResetCold, EFI_SUCCESS, 0, NULL);
#endif

    }

	return Status;
}
//AMI_OVERRIDE   ... // AMI_OVERRIDE ... EIP#42483: MemCeiling support ...END...

EFI_DRIVER_ENTRY_POINT (PciHostBridgeEntryPoint)
///
/// Implementation
///
/**
  Entry point of this driver

  @param[in] ImageHandle -
  @param[in] SystemTable -

  @retval EFI_SUCCESS       - Driver Start OK
  @retval EFI_DEVICE_ERROR  - Fail to install PCI_ROOT_BRIDGE_IO protocol.
**/
EFI_STATUS
EFIAPI
PciHostBridgeEntryPoint (
  IN EFI_HANDLE       ImageHandle,
  IN EFI_SYSTEM_TABLE *SystemTable
  )
{
  EFI_STATUS                Status;
  UINTN                     Loop1;
  UINTN                     Loop2;
  PCI_HOST_BRIDGE_INSTANCE  *HostBridge;
  PCI_ROOT_BRIDGE_INSTANCE  *PrivateData;
  EFI_PHYSICAL_ADDRESS      PciBaseAddress;
  EFI_PHYSICAL_ADDRESS      RemapBase;
  EFI_PHYSICAL_ADDRESS      RemapLimit;
  EFI_PHYSICAL_ADDRESS      MeSegMask;
  EFI_PHYSICAL_ADDRESS      MeStolenSize;
  BOOLEAN                   MeStolenEnable;
  UINT32                    Tolud;
  UINT64                    Length;
  EFI_PHYSICAL_ADDRESS      BaseAddress;
  CPU_FAMILY                CpuFamilyId;
  CPU_STEPPING              CpuSteppingId;
#ifndef AMI_OVERRIDE_FOR_REMAP_DISABLED
  EFI_PHYSICAL_ADDRESS      MeStolenBase;
#endif // AMI_OVERRIDE_FOR_REMAP_DISABLED

  INITIALIZE_SCRIPT (ImageHandle, SystemTable);

  mDriverImageHandle = ImageHandle;

  ///
  /// This system has one Host Bridge (one Root Bridge in this Host Bridge)
  ///
  ///
  /// Create Host Bridge Device Handle
  ///
  for (Loop1 = 0; Loop1 < HOST_BRIDGE_NUMBER; Loop1++) {
    Status = (gBS->AllocatePool) (EfiBootServicesData, sizeof (PCI_HOST_BRIDGE_INSTANCE), (VOID **) &HostBridge);
    ASSERT (!EFI_ERROR (Status));

    HostBridge->Signature         = PCI_HOST_BRIDGE_SIGNATURE;
    HostBridge->RootBridgeNumber  = RootBridgeNumber[Loop1];
    HostBridge->ResourceSubmited  = FALSE;
    HostBridge->CanRestarted      = TRUE;

    ///
    /// InitializeListHead (&HostBridge->Head);
    ///
    HostBridge->ResAlloc.NotifyPhase          = NotifyPhase;
    HostBridge->ResAlloc.GetNextRootBridge    = GetNextRootBridge;
    HostBridge->ResAlloc.GetAllocAttributes   = GetAttributes;
    HostBridge->ResAlloc.StartBusEnumeration  = StartBusEnumeration;
    HostBridge->ResAlloc.SetBusNumbers        = SetBusNumbers;
    HostBridge->ResAlloc.SubmitResources      = SubmitResources;
    HostBridge->ResAlloc.GetProposedResources = GetProposedResources;
    HostBridge->ResAlloc.PreprocessController = PreprocessController;
    HostBridge->HostBridgeHandle              = NULL;
    Status = gBS->InstallProtocolInterface (
                    &HostBridge->HostBridgeHandle,
                    &gEfiPciHostBridgeResourceAllocationProtocolGuid,
                    EFI_NATIVE_INTERFACE,
                    &HostBridge->ResAlloc
                    );
    if (EFI_ERROR (Status)) {
      (gBS->FreePool) (HostBridge);
      return EFI_DEVICE_ERROR;
    }
    ///
    /// Create Root Bridge Device Handle in this Host Bridge
    ///
    InitializeListHead (&HostBridge->Head);
    for (Loop2 = 0; Loop2 < HostBridge->RootBridgeNumber; Loop2++) {
      Status = (gBS->AllocatePool) (EfiBootServicesData, sizeof (PCI_ROOT_BRIDGE_INSTANCE), (VOID **) &PrivateData);
      ASSERT (!EFI_ERROR (Status));

      PrivateData->Signature  = PCI_ROOT_BRIDGE_SIGNATURE;
      PrivateData->DevicePath = (EFI_DEVICE_PATH_PROTOCOL *) &mEfiPciRootBridgeDevicePath[Loop1][Loop2];
      RootBridgeConstructor (
        &PrivateData->Io,
        HostBridge->HostBridgeHandle,
        RootBridgeAttribute[Loop1][Loop2],
        &mResAperture[Loop1][Loop2]
        );
      PrivateData->Handle = NULL;
      Status = gBS->InstallMultipleProtocolInterfaces (
                      &PrivateData->Handle,
                      &gEfiDevicePathProtocolGuid,
                      PrivateData->DevicePath,
                      &gEfiPciRootBridgeIoProtocolGuid,
                      &PrivateData->Io,
                      NULL
                      );
      if (EFI_ERROR (Status)) {
        (gBS->FreePool) (PrivateData);
        return EFI_DEVICE_ERROR;
      }

      InsertTailList (&HostBridge->Head, &PrivateData->Link);
    }
  }
  ///
  /// Allocate 60 KB of I/O space [0x1000..0xFFFF]
  ///
  Status = gDS->AddIoSpace (
                  EfiGcdIoTypeIo,
                  RES_IO_BASE,
                  RES_IO_LIMIT - RES_IO_BASE + 1
                  );
  ASSERT_EFI_ERROR (Status);

  // AMI_OVERRIDE ... Fixed GenericSio use 0x0 ~ 0xfff issue start.
  // It will Override CoreAllocateIoSpace.
  gAmiCoreAllocateIoSpace = gDS->AllocateIoSpace;
  gDS->AllocateIoSpace = NbCspOverrideCoreAllocateIoSpace;
  // AMI_OVERRIDE ... Fixed GenericSio use 0x0 ~ 0xfff issue end.

  ///
  /// Allocate PCI memory space.
  ///
  ///
  /// Read memory map registers
  ///
  RemapBase       = McD0PciCfg64 (R_SA_REMAPBASE) & B_SA_REMAPBASE_REMAPBASE_MASK;
  RemapLimit      = McD0PciCfg64 (R_SA_REMAPLIMIT) & B_SA_REMAPLIMIT_REMAPLMT_MASK;
  Tolud           = McD0PciCfg32 (R_SA_TOLUD) & B_SA_TOLUD_TOLUD_MASK;
  PciBaseAddress  = Tolud;
  MeSegMask       = McD0PciCfg64 (R_SA_MESEG_MASK);
  MeStolenEnable  = (BOOLEAN) ((MeSegMask & B_SA_MESEG_MASK_ME_STLEN_EN_MASK) != 0);

  ///
  /// First check if memory remap is used
  ///
  if ((RemapBase > RemapLimit) && (MeStolenEnable)) {
    MeStolenSize = MeSegMask & B_SA_MESEG_MASK_MEMASK_MASK;
    if (MeStolenSize != 0) {
      MeStolenSize = 0x8000000000L - MeStolenSize;
#ifndef AMI_OVERRIDE_FOR_REMAP_DISABLED
      // Remap is disabled -> if Me Stolen Base on PCI resume, PCI resume - MeStolenSize.
      MeStolenBase    = McD0PciCfg64 (R_SA_MESEG_BASE);
      if(MeStolenBase < RES_MEM_LIMIT_1) {
         //
         // Remap is disabled -> PCI starts at TOLUD + ME Stolen size
         //
         PciBaseAddress += MeStolenSize;
      }
#endif // AMI_OVERRIDE_FOR_REMAP_DISABLED
    }
    ///
    /// Remap is disabled -> PCI starts at TOLUD + ME Stolen size
    ///
#ifdef AMI_OVERRIDE_FOR_REMAP_DISABLED
    PciBaseAddress += MeStolenSize;
#endif // AMI_OVERRIDE_FOR_REMAP_DISABLED
  }

  Length = RES_MEM_LIMIT_1 - PciBaseAddress + 1;

  if (Length != 0) {
    DEBUG (
      (
      EFI_D_INFO, " Allocating PCI space from 0x%X to 0x%X\n", (UINT32) PciBaseAddress, (UINT32)
      (PciBaseAddress + Length - 1)
      )
      );
    Status = gDS->AddMemorySpace (
                    EfiGcdMemoryTypeMemoryMappedIo,
                    PciBaseAddress,
                    Length,
                    0
                    );
    ASSERT_EFI_ERROR (Status);
  }
  ///
  /// Get CPU Family and Stepping ID
  ///
  CpuFamilyId = GetCpuFamily();
  CpuSteppingId = GetCpuStepping();

  ///
  /// WA for HSW A0. To exclude the ranges 20000000-201FFFFF (2MB) and 0x40004000-0x40004FFF (4KB).
  ///
  if ((CpuFamilyId == EnumCpuHsw) && (CpuSteppingId == EnumHswA0)) {
    if (McD0PciCfg32 (R_SA_DEVEN) & B_SA_DEVEN_D2EN_MASK) {
      BaseAddress = 0x20000000;
      Status = (gBS->AllocatePages) (AllocateAddress, EfiReservedMemoryType, EFI_SIZE_TO_PAGES (0x00200000), &BaseAddress);

      BaseAddress = 0x40004000;
      Status = (gBS->AllocatePages) (AllocateAddress, EfiReservedMemoryType, EFI_SIZE_TO_PAGES (0x00001000), &BaseAddress);
    }
  }

  return EFI_SUCCESS;
}

/**
  Enter a certain phase of the PCI enumeration process

  @param[in] This  - The EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL instance
  @param[in] Phase - The phase during enumeration

  @retval EFI_SUCCESS            -  Succeed.
  @retval EFI_INVALID_PARAMETER  -  Wrong phase parameter passed in.
  @retval EFI_NOT_READY          -  Resources have not been submitted yet.
**/
EFI_STATUS
EFIAPI
NotifyPhase (
  IN EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL *This,
  IN EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PHASE    Phase
  )
{
  PCI_HOST_BRIDGE_INSTANCE  *HostBridgeInstance;
  PCI_ROOT_BRIDGE_INSTANCE  *RootBridgeInstance;
  PCI_RESOURCE_TYPE         Index;
  LIST_ENTRY                *List;
  EFI_PHYSICAL_ADDRESS      BaseAddress;
  UINT64                    AddrLen;
  UINTN                     BitsOfAlignment;
  UINT64                    Alignment;
  EFI_STATUS                Status;
  EFI_STATUS                ReturnStatus;

  HostBridgeInstance = INSTANCE_FROM_RESOURCE_ALLOCATION_THIS (This);
  switch (Phase) {
  case EfiPciHostBridgeBeginEnumeration:
    if (HostBridgeInstance->CanRestarted) {
      ///
      /// Reset the Each Root Bridge
      ///
      List = HostBridgeInstance->Head.ForwardLink;
      while (List != &HostBridgeInstance->Head) {
        RootBridgeInstance = DRIVER_INSTANCE_FROM_LIST_ENTRY (List);
        for (Index = TypeIo; Index < TypeMax; Index++) {
          RootBridgeInstance->ResAllocNode[Index].Type    = Index;
          RootBridgeInstance->ResAllocNode[Index].Base    = 0;
          RootBridgeInstance->ResAllocNode[Index].Length  = 0;
          RootBridgeInstance->ResAllocNode[Index].Status  = ResNone;
        }

        List = List->ForwardLink;
      }

      HostBridgeInstance->ResourceSubmited  = FALSE;
      HostBridgeInstance->CanRestarted      = TRUE;
    } else {
      ///
      /// Can not restart
      ///
      return EFI_NOT_READY;
    }
    break;

  case EfiPciHostBridgeBeginBusAllocation:
    ///
    /// No specific action is required here, can perform any chipset specific programing
    ///
    HostBridgeInstance->CanRestarted = FALSE;
    return EFI_SUCCESS;
    break;

  case EfiPciHostBridgeEndBusAllocation:
    ///
    /// No specific action is required here, can perform any chipset specific programing
    ///
    return EFI_SUCCESS;
    break;

  case EfiPciHostBridgeBeginResourceAllocation:
    ///
    /// No specific action is required here, can perform any chipset specific programing
    ///
    return EFI_SUCCESS;
    break;

  case EfiPciHostBridgeAllocateResources:
    ReturnStatus = EFI_SUCCESS;
    if (HostBridgeInstance->ResourceSubmited) {
      ///
      /// Take care of the resource dependencies between the root bridges
      ///
      List = HostBridgeInstance->Head.ForwardLink;
      while (List != &HostBridgeInstance->Head) {
        RootBridgeInstance = DRIVER_INSTANCE_FROM_LIST_ENTRY (List);

        Status = HbCspAdjustMemoryMmioOverlap(RootBridgeInstance);        //  <<< AMI_OVERRIDE - EIP# 42483 - Support for Multi-Monitor	>>>

        for (Index = TypeIo; Index < TypeBus; Index++) {
          if (RootBridgeInstance->ResAllocNode[Index].Status != ResNone) {
            AddrLen   = RootBridgeInstance->ResAllocNode[Index].Length;
            Alignment = RootBridgeInstance->ResAllocNode[Index].Alignment;

            ///
            /// Get the number of '1' in Alignment.
            ///
            for (BitsOfAlignment = 0; Alignment != 0; BitsOfAlignment++) {
              Alignment = RShiftU64 (Alignment, 1);
            }

            switch (Index) {
            case TypeIo:
              ///
              /// It is impossible for this chipset to align 0xFFFF for IO16
              /// So clear it
              ///
              if (BitsOfAlignment >= 16) {
                BitsOfAlignment = 0;
              }

#ifndef AMI_ORIGINAL_FOR_MMIO_4G_TOLUD
              // Support MaxAddressSearchTopDown for Gcd Io
              BaseAddress = 0xFFFF;
#endif // AMI_ORIGINAL_FOR_MMIO_4G_TOLUD

              Status = gDS->AllocateIoSpace (
#ifdef AMI_ORIGINAL_FOR_MMIO_4G_TOLUD
                              EfiGcdAllocateAnySearchBottomUp,
#else // AMI_ORIGINAL_FOR_MMIO_4G_TOLUD
                              EfiGcdAllocateMaxAddressSearchTopDown,
#endif // AMI_ORIGINAL_FOR_MMIO_4G_TOLUD
                              EfiGcdIoTypeIo,
                              BitsOfAlignment,
                              AddrLen,
                              &BaseAddress,
                              mDriverImageHandle,
                              NULL
                              );
              if (!EFI_ERROR (Status)) {
                RootBridgeInstance->ResAllocNode[Index].Base    = (UINTN) BaseAddress;
                RootBridgeInstance->ResAllocNode[Index].Status  = ResAllocated;
              } else {
                ///
                /// Not able to allocate enough I/O memory - critical stop
                ///
                DEBUG ((EFI_D_ERROR, "Out of I/O space! AllocateIoSpace() returned %r\n", Status));
                DEBUG ((EFI_D_ERROR, "Size requested: 0x%lX bytes\n", AddrLen));
                ReturnStatus = Status;
              }
              break;

            case TypeMem32:
            case TypePMem32:
              ///
              /// It is impossible for this chipset to align 0xFFFFFFFF for Mem32
              /// So clear it
              ///
              if (BitsOfAlignment >= 32) {
                BitsOfAlignment = 0;
              }

#ifndef AMI_ORIGINAL_FOR_MMIO_4G_TOLUD
              // Support MMIO 4G to Tolud for EfiGcdAllocateMaxAddressSearchTopDown
			  BaseAddress = 0xFFFFFFFF;
#endif // AMI_ORIGINAL_FOR_MMIO_4G_TOLUD
            ///
            /// Fall through to TypeMem64 / TypePMem64...
            ///
            case TypeMem64:
            case TypePMem64:
              Status = gDS->AllocateMemorySpace (
#ifdef AMI_ORIGINAL_FOR_MMIO_4G_TOLUD
                              EfiGcdAllocateAnySearchBottomUp,
#else // AMI_ORIGINAL_FOR_MMIO_4G_TOLUD
                              EfiGcdAllocateMaxAddressSearchTopDown,
#endif // AMI_ORIGINAL_FOR_MMIO_4G_TOLUD
                              EfiGcdMemoryTypeMemoryMappedIo,
                              BitsOfAlignment,
                              AddrLen,
                              &BaseAddress,
                              mDriverImageHandle,
                              NULL
                              );
              if (!EFI_ERROR (Status)) {
                ///
                /// We were able to allocate the PCI memory
                ///
                RootBridgeInstance->ResAllocNode[Index].Base    = (UINTN) BaseAddress;
                RootBridgeInstance->ResAllocNode[Index].Status  = ResAllocated;
              } else {
                ///
                /// Not able to allocate enough PCI memory - critical stop
                ///
                DEBUG ((EFI_D_ERROR, "Out of PCI memory! AllocateMemorySpace() returned %r\n", Status));
                DEBUG ((EFI_D_ERROR, "Size requested: 0x%lX bytes\n", AddrLen));
                ReturnStatus = Status;
              }
              break;
            default:
              break;
            }
            ///
            /// end switch
            ///
          }
        }

        List = List->ForwardLink;
      }

      return ReturnStatus;
    } else {
      return EFI_NOT_READY;
    }
    break;

  case EfiPciHostBridgeSetResources:
    break;

  case EfiPciHostBridgeFreeResources:
    ReturnStatus  = EFI_SUCCESS;

    List          = HostBridgeInstance->Head.ForwardLink;
    while (List != &HostBridgeInstance->Head) {
      RootBridgeInstance = DRIVER_INSTANCE_FROM_LIST_ENTRY (List);
      for (Index = TypeIo; Index < TypeBus; Index++) {
        if (RootBridgeInstance->ResAllocNode[Index].Status == ResAllocated) {
          AddrLen     = RootBridgeInstance->ResAllocNode[Index].Length;
          BaseAddress = RootBridgeInstance->ResAllocNode[Index].Base;
          switch (Index) {
          case TypeIo:
            Status = gDS->FreeIoSpace (BaseAddress, AddrLen);
            break;

          case TypeMem32:
          case TypePMem32:
          case TypeMem64:
          case TypePMem64:
            Status = gDS->FreeMemorySpace (BaseAddress, AddrLen);
            break;

          default:
            Status = EFI_INVALID_PARAMETER;

          }

          if (EFI_ERROR (Status)) {
            ReturnStatus = Status;
          }
          ///
          /// end switch
          ///
          RootBridgeInstance->ResAllocNode[Index].Type    = Index;
          RootBridgeInstance->ResAllocNode[Index].Base    = 0;
          RootBridgeInstance->ResAllocNode[Index].Length  = 0;
          RootBridgeInstance->ResAllocNode[Index].Status  = ResNone;
        }
      }

      List = List->ForwardLink;
    }

    HostBridgeInstance->ResourceSubmited  = FALSE;
    HostBridgeInstance->CanRestarted      = TRUE;
    return ReturnStatus;
    break;

  case EfiPciHostBridgeEndResourceAllocation:
    HostBridgeInstance->CanRestarted = FALSE;
    break;

  default:
    return EFI_INVALID_PARAMETER;
  }
  ///
  /// end switch
  ///
  return EFI_SUCCESS;
}

/**
  Return the device handle of the next PCI root bridge that is associated with
  this Host Bridge

  @param[in] This              - The EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_ PROTOCOL instance
  @param[in] RootBridgeHandle  - Returns the device handle of the next PCI Root Bridge.
                      On input, it holds the RootBridgeHandle returned by the most
                      recent call to GetNextRootBridge().The handle for the first
                      PCI Root Bridge is returned if RootBridgeHandle is NULL on input

  @retval EFI_SUCCESS            -  Succeed.
  @retval EFI_NOT_FOUND          -  Next PCI root bridge not found.
  @retval EFI_INVALID_PARAMETER  -  Wrong parameter passed in.
**/
EFI_STATUS
EFIAPI
GetNextRootBridge (
  IN EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL *This,
  IN OUT EFI_HANDLE                                   *RootBridgeHandle
  )
{
  BOOLEAN                   NoRootBridge;
  LIST_ENTRY                *List;
  PCI_HOST_BRIDGE_INSTANCE  *HostBridgeInstance;
  PCI_ROOT_BRIDGE_INSTANCE  *RootBridgeInstance;

  NoRootBridge        = TRUE;
  HostBridgeInstance  = INSTANCE_FROM_RESOURCE_ALLOCATION_THIS (This);
  List                = HostBridgeInstance->Head.ForwardLink;

  while (List != &HostBridgeInstance->Head) {
    NoRootBridge        = FALSE;
    RootBridgeInstance  = DRIVER_INSTANCE_FROM_LIST_ENTRY (List);
    if (*RootBridgeHandle == NULL) {
      ///
      /// Return the first Root Bridge Handle of the Host Bridge
      ///
      *RootBridgeHandle = RootBridgeInstance->Handle;
      return EFI_SUCCESS;
    } else {
      if (*RootBridgeHandle == RootBridgeInstance->Handle) {
        ///
        /// Get next if have
        ///
        List = List->ForwardLink;
        if (List != &HostBridgeInstance->Head) {
          RootBridgeInstance  = DRIVER_INSTANCE_FROM_LIST_ENTRY (List);
          *RootBridgeHandle   = RootBridgeInstance->Handle;
          return EFI_SUCCESS;
        } else {
          return EFI_NOT_FOUND;
        }
      }
    }

    List = List->ForwardLink;
  }
  ///
  /// end while
  ///
  if (NoRootBridge) {
    return EFI_NOT_FOUND;
  } else {
    return EFI_INVALID_PARAMETER;
  }
}

/**
  Returns the attributes of a PCI Root Bridge.

  @param[in] This              - The EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_ PROTOCOL instance.
  @param[in] RootBridgeHandle  - The device handle of the PCI Root Bridge
                      that the caller is interested in
  @param[in] Attributes        - The pointer to attributes of the PCI Root Bridge

  @retval EFI_SUCCESS            -  Succeed.
  @retval EFI_INVALID_PARAMETER  -  Attributes parameter passed in is NULL or
                            RootBridgeHandle is not an EFI_HANDLE
                            that was returned on a previous call to
                            GetNextRootBridge().
**/
EFI_STATUS
EFIAPI
GetAttributes (
  IN EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL *This,
  IN EFI_HANDLE                                       RootBridgeHandle,
  OUT UINT64                                          *Attributes
  )
{
  LIST_ENTRY                *List;
  PCI_HOST_BRIDGE_INSTANCE  *HostBridgeInstance;
  PCI_ROOT_BRIDGE_INSTANCE  *RootBridgeInstance;

  if (Attributes == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  HostBridgeInstance  = INSTANCE_FROM_RESOURCE_ALLOCATION_THIS (This);
  List                = HostBridgeInstance->Head.ForwardLink;
  while (List != &HostBridgeInstance->Head) {
    RootBridgeInstance = DRIVER_INSTANCE_FROM_LIST_ENTRY (List);
    if (RootBridgeHandle == RootBridgeInstance->Handle) {
      *Attributes = RootBridgeInstance->RootBridgeAttrib;
      return EFI_SUCCESS;
    }

    List = List->ForwardLink;
  }
  ///
  /// RootBridgeHandle is not an EFI_HANDLE
  /// that was returned on a previous call to GetNextRootBridge()
  ///
  return EFI_INVALID_PARAMETER;
}

/**
  This is the request from the PCI enumerator to set up
  the specified PCI Root Bridge for bus enumeration process.

  @param[in] This              - The EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_ PROTOCOL instance.
  @param[in] RootBridgeHandle  - The PCI Root Bridge to be set up.
  @param[in] Configuration     - Pointer to the pointer to the PCI bus resource descriptor.

  @retval EFI_SUCCESS            -  Succeed.
  @retval EFI_OUT_OF_RESOURCES   -  Not enough pool to be allocated.
  @retval EFI_INVALID_PARAMETER  -  RootBridgeHandle is not a valid handle.
**/
EFI_STATUS
EFIAPI
StartBusEnumeration (
  IN EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL *This,
  IN EFI_HANDLE                                       RootBridgeHandle,
  OUT VOID                                            **Configuration
  )
{
  LIST_ENTRY                *List;
  PCI_HOST_BRIDGE_INSTANCE  *HostBridgeInstance;
  PCI_ROOT_BRIDGE_INSTANCE  *RootBridgeInstance;
  VOID                      *Buffer;
  UINT8                     *Temp;
  EFI_STATUS                Status;
  UINT64                    BusStart;
  UINT64                    BusEnd;

  HostBridgeInstance  = INSTANCE_FROM_RESOURCE_ALLOCATION_THIS (This);
  List                = HostBridgeInstance->Head.ForwardLink;

  while (List != &HostBridgeInstance->Head) {
    RootBridgeInstance = DRIVER_INSTANCE_FROM_LIST_ENTRY (List);
    if (RootBridgeHandle == RootBridgeInstance->Handle) {
      ///
      /// Set up the Root Bridge for Bus Enumeration
      ///
      BusStart  = RootBridgeInstance->BusBase;
      BusEnd    = RootBridgeInstance->BusLimit;

      ///
      /// Program the Hardware(if needed) if error return EFI_DEVICE_ERROR
      ///
      Status = (gBS->AllocatePool) (
          EfiBootServicesData, sizeof (EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR) + sizeof (EFI_ACPI_END_TAG_DESCRIPTOR), &Buffer
        );
      if (EFI_ERROR (Status)) {
        return EFI_OUT_OF_RESOURCES;
      }

      Temp  = (UINT8 *) Buffer;
      ((EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR *) Temp)->Desc                  = ACPI_ADDRESS_SPACE_DESCRIPTOR;
      ((EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR *) Temp)->Len                   = 0x2B;
      ((EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR *) Temp)->ResType               = ACPI_ADDRESS_SPACE_TYPE_BUS;
      ((EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR *) Temp)->GenFlag               = 0;
      ((EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR *) Temp)->SpecificFlag          = 0;
      ((EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR *) Temp)->AddrSpaceGranularity  = 0;
      ((EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR *) Temp)->AddrRangeMin          = BusStart;
      ((EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR *) Temp)->AddrRangeMax          = 0;
      ((EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR *) Temp)->AddrTranslationOffset = 0;
      ((EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR *) Temp)->AddrLen               = BusEnd - BusStart + 1;

      Temp = Temp + sizeof (EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR);

      ((EFI_ACPI_END_TAG_DESCRIPTOR *) Temp)->Desc = ACPI_END_TAG_DESCRIPTOR;
      ((EFI_ACPI_END_TAG_DESCRIPTOR *) Temp)->Checksum = 0x0;
      *Configuration = Buffer;
      return EFI_SUCCESS;
    }

    List = List->ForwardLink;
  }

  return EFI_INVALID_PARAMETER;
}

/**
  This function programs the PCI Root Bridge hardware so that
  it decodes the specified PCI bus range

  @param[in] This              - The EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_ PROTOCOL instance
  @param[in] RootBridgeHandle  - The PCI Root Bridge whose bus range is to be programmed
  @param[in] Configuration     - The pointer to the PCI bus resource descriptor

  @retval EFI_SUCCESS            -  Succeed.
  @retval EFI_INVALID_PARAMETER  -  Wrong parameters passed in.
**/
EFI_STATUS
EFIAPI
SetBusNumbers (
  IN EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL *This,
  IN EFI_HANDLE                                       RootBridgeHandle,
  IN VOID                                             *Configuration
  )
{
  LIST_ENTRY                *List;
  PCI_HOST_BRIDGE_INSTANCE  *HostBridgeInstance;
  PCI_ROOT_BRIDGE_INSTANCE  *RootBridgeInstance;
  UINT8                     *Ptr;
  UINTN                     BusStart;
  UINTN                     BusEnd;
  UINTN                     BusLen;

  if (Configuration == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  Ptr = Configuration;

  ///
  /// Check the Configuration is valid
  ///
  if (*Ptr != ACPI_ADDRESS_SPACE_DESCRIPTOR) {
    return EFI_INVALID_PARAMETER;
  }

  if (((EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR *) Ptr)->ResType != ACPI_ADDRESS_SPACE_TYPE_BUS) {
    return EFI_INVALID_PARAMETER;
  }

  Ptr += sizeof (EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR);
  if (*Ptr != ACPI_END_TAG_DESCRIPTOR) {
    return EFI_INVALID_PARAMETER;
  }

  HostBridgeInstance  = INSTANCE_FROM_RESOURCE_ALLOCATION_THIS (This);
  List                = HostBridgeInstance->Head.ForwardLink;
  Ptr                 = Configuration;
  while (List != &HostBridgeInstance->Head) {
    RootBridgeInstance = DRIVER_INSTANCE_FROM_LIST_ENTRY (List);
    if (RootBridgeHandle == RootBridgeInstance->Handle) {
      BusStart  = (UINTN) ((EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR *) Ptr)->AddrRangeMin;
      BusLen    = (UINTN) ((EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR *) Ptr)->AddrLen;
      BusEnd    = BusStart + BusLen - 1;
      if (BusStart > BusEnd) {
        return EFI_INVALID_PARAMETER;
      }

      if ((BusStart < RootBridgeInstance->BusBase) || (BusEnd > RootBridgeInstance->BusLimit)) {
        return EFI_INVALID_PARAMETER;
      }
      ///
      /// Update the Bus Range
      ///
      RootBridgeInstance->ResAllocNode[TypeBus].Base    = BusStart;
      RootBridgeInstance->ResAllocNode[TypeBus].Length  = BusLen;
      RootBridgeInstance->ResAllocNode[TypeBus].Status  = ResAllocated;

      ///
      /// Program the Root Bridge Hardware
      ///
      return EFI_SUCCESS;
    }

    List = List->ForwardLink;
  }

  return EFI_INVALID_PARAMETER;
}

/**
  Submits the I/O and memory resource requirements for the specified PCI Root Bridge

  @param[in] This              - The EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_ PROTOCOL instance
  @param[in] RootBridgeHandle  - The PCI Root Bridge whose I/O and memory resource requirements
                      are being submitted
  @param[in] Configuration     - The pointer to the PCI I/O and PCI memory resource descriptor

  @retval EFI_SUCCESS            -  Succeed.
  @retval EFI_INVALID_PARAMETER  -  Wrong parameters passed in.
**/
EFI_STATUS
EFIAPI
SubmitResources (
  IN EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL *This,
  IN EFI_HANDLE                                       RootBridgeHandle,
  IN VOID                                             *Configuration
  )
{
  LIST_ENTRY                        *List;
  PCI_HOST_BRIDGE_INSTANCE          *HostBridgeInstance;
  PCI_ROOT_BRIDGE_INSTANCE          *RootBridgeInstance;
  UINT8                             *Temp;
  EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR *ptr;
  UINT64                            AddrLen;
  UINT64                            Alignment;

  ///
  /// Check the input parameter: Configuration
  ///
  if (Configuration == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  HostBridgeInstance  = INSTANCE_FROM_RESOURCE_ALLOCATION_THIS (This);
  List                = HostBridgeInstance->Head.ForwardLink;
  Temp                = (UINT8 *) Configuration;
  while (*Temp == ACPI_ADDRESS_SPACE_DESCRIPTOR) {
    Temp += sizeof (EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR);
  }

  if (*Temp != ACPI_END_TAG_DESCRIPTOR) {
    return EFI_INVALID_PARAMETER;
  }

  Temp = (UINT8 *) Configuration;
  while (List != &HostBridgeInstance->Head) {
    RootBridgeInstance = DRIVER_INSTANCE_FROM_LIST_ENTRY (List);
    if (RootBridgeHandle == RootBridgeInstance->Handle) {
      while (*Temp == ACPI_ADDRESS_SPACE_DESCRIPTOR) {
        ptr = (EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR *) Temp;

        ///
        /// Check address range alignment
        ///
        if (ptr->AddrRangeMax >= (UINT64) 0xffffffff ||
            ptr->AddrRangeMax != (Power2MaxMemory (ptr->AddrRangeMax + 1) - 1)
            ) {
          return EFI_INVALID_PARAMETER;
        }

        switch (ptr->ResType) {
        case ACPI_ADDRESS_SPACE_TYPE_MEM:
          ///
          /// check the memory resource request is supported by PCI root bridge
          ///
          /// Hard code EFI_PCI_HOST_BRIDGE_COMBINE_MEM_PMEM  0 to support prefetchable memory allocation
          ///
          if (RootBridgeInstance->RootBridgeAttrib == 0 && ptr->SpecificFlag == 0x06) {
            return EFI_INVALID_PARAMETER;
          }

          AddrLen   = (UINT64) ptr->AddrLen;
          Alignment = (UINT64) ptr->AddrRangeMax;
          if (ptr->AddrSpaceGranularity == 32) {
            if ((ptr->SpecificFlag & 0x06) == 0x06) {
              ///
              /// Apply from GCD
              ///
              RootBridgeInstance->ResAllocNode[TypePMem32].Length     = AddrLen;
              RootBridgeInstance->ResAllocNode[TypePMem32].Alignment  = Alignment;
              RootBridgeInstance->ResAllocNode[TypePMem32].Status     = ResRequested;
              HostBridgeInstance->ResourceSubmited                    = TRUE;

            } else {
              RootBridgeInstance->ResAllocNode[TypeMem32].Length    = AddrLen;
              RootBridgeInstance->ResAllocNode[TypeMem32].Alignment = Alignment;
              RootBridgeInstance->ResAllocNode[TypeMem32].Status    = ResRequested;
              HostBridgeInstance->ResourceSubmited                  = TRUE;
            }
          }

          if (ptr->AddrSpaceGranularity == 64) {
            if ((ptr->SpecificFlag & 0x06) == 0x06) {
              RootBridgeInstance->ResAllocNode[TypePMem64].Length     = AddrLen;
              RootBridgeInstance->ResAllocNode[TypePMem64].Alignment  = Alignment;
              RootBridgeInstance->ResAllocNode[TypePMem64].Status     = ResSubmitted;
              HostBridgeInstance->ResourceSubmited                    = TRUE;

            } else {
              RootBridgeInstance->ResAllocNode[TypeMem64].Length    = AddrLen;
              RootBridgeInstance->ResAllocNode[TypeMem64].Alignment = Alignment;
              RootBridgeInstance->ResAllocNode[TypeMem64].Status    = ResSubmitted;
              HostBridgeInstance->ResourceSubmited                  = TRUE;
            }
          }
          break;

        case ACPI_ADDRESS_SPACE_TYPE_IO:
          AddrLen   = (UINT64) ptr->AddrLen;
          Alignment = (UINT64) ptr->AddrRangeMax;
          RootBridgeInstance->ResAllocNode[TypeIo].Length     = AddrLen;
          RootBridgeInstance->ResAllocNode[TypeIo].Alignment  = Alignment;
          RootBridgeInstance->ResAllocNode[TypeIo].Status     = ResRequested;
          HostBridgeInstance->ResourceSubmited                = TRUE;
          break;

        default:
          break;
        }

        Temp += sizeof (EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR);
      }

      return EFI_SUCCESS;
    }

    List = List->ForwardLink;
  }

  return EFI_INVALID_PARAMETER;
}

/**
  This function returns the proposed resource settings for the specified
  PCI Root Bridge

  @param[in] This              - The EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_ PROTOCOL instance
  @param[in] RootBridgeHandle  - The PCI Root Bridge handle
  @param[in] Configuration     - The pointer to the pointer to the PCI I/O
                      and memory resource descriptor

  @retval EFI_SUCCESS            -  Succeed.
  @retval EFI_OUT_OF_RESOURCES   -  Not enough pool to be allocated.
  @retval EFI_INVALID_PARAMETER  -  RootBridgeHandle is not a valid handle.
**/
EFI_STATUS
EFIAPI
GetProposedResources (
  IN EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL *This,
  IN EFI_HANDLE                                       RootBridgeHandle,
  OUT VOID                                            **Configuration
  )
{
  LIST_ENTRY                        *List;
  PCI_HOST_BRIDGE_INSTANCE          *HostBridgeInstance;
  PCI_ROOT_BRIDGE_INSTANCE          *RootBridgeInstance;
  UINTN                             Index;
  UINTN                             Number;
  VOID                              *Buffer;
  UINT8                             *Temp;
  EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR *ptr;
  EFI_STATUS                        Status;
  UINT64                            ResStatus;

  Buffer  = NULL;
  Number  = 0;

  ///
  /// Get the Host Bridge Instance from the resource allocation protocol
  ///
  HostBridgeInstance  = INSTANCE_FROM_RESOURCE_ALLOCATION_THIS (This);
  List                = HostBridgeInstance->Head.ForwardLink;

  ///
  /// Enumerate the root bridges in this host bridge
  ///
  while (List != &HostBridgeInstance->Head) {
    RootBridgeInstance = DRIVER_INSTANCE_FROM_LIST_ENTRY (List);
    if (RootBridgeHandle == RootBridgeInstance->Handle) {
      for (Index = 0; Index < TypeBus; Index++) {
        if (RootBridgeInstance->ResAllocNode[Index].Status != ResNone) {
          Number++;
        }
      }

      if (Number > 0) {
        Status = (gBS->AllocatePool)
          (
            EfiBootServicesData, Number * sizeof (EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR) +
            sizeof (EFI_ACPI_END_TAG_DESCRIPTOR), &Buffer
          );
        if (EFI_ERROR (Status)) {
          return EFI_OUT_OF_RESOURCES;
        }

        ZeroMem (Buffer, sizeof (EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR) * Number + sizeof (EFI_ACPI_END_TAG_DESCRIPTOR));

        Temp = Buffer;
        for (Index = 0; Index < TypeBus; Index++) {
          if (RootBridgeInstance->ResAllocNode[Index].Status != ResNone) {
            ptr       = (EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR *) Temp;
            ResStatus = RootBridgeInstance->ResAllocNode[Index].Status;
            switch (Index) {
            case TypeIo:
              ///
              /// Io
              ///
              ptr->Desc                   = 0x8A;
              ptr->Len                    = 0x2B;
              ptr->ResType                = 1;
              ptr->GenFlag                = 0;
              ptr->SpecificFlag           = 0;
              ptr->AddrRangeMin           = RootBridgeInstance->ResAllocNode[Index].Base;
              ptr->AddrRangeMax           = 0;
              ptr->AddrTranslationOffset  = (ResStatus == ResAllocated) ? EFI_RESOURCE_SATISFIED : EFI_RESOURCE_LESS;
              ptr->AddrLen                = RootBridgeInstance->ResAllocNode[Index].Length;
              break;

            case TypeMem32:
              ///
              /// Memory 32
              ///
              ptr->Desc                   = 0x8A;
              ptr->Len                    = 0x2B;
              ptr->ResType                = 0;
              ptr->GenFlag                = 0;
              ptr->SpecificFlag           = 0;
              ptr->AddrSpaceGranularity   = 32;
              ptr->AddrRangeMin           = RootBridgeInstance->ResAllocNode[Index].Base;
              ptr->AddrRangeMax           = 0;
              ptr->AddrTranslationOffset  = (ResStatus == ResAllocated) ? EFI_RESOURCE_SATISFIED : EFI_RESOURCE_LESS;
              ptr->AddrLen                = RootBridgeInstance->ResAllocNode[Index].Length;
              break;

            case TypePMem32:
              ///
              /// Prefetch memory 32
              ///
              ptr->Desc                   = 0x8A;
              ptr->Len                    = 0x2B;
              ptr->ResType                = 0;
              ptr->GenFlag                = 0;
              ptr->SpecificFlag           = 6;
              ptr->AddrSpaceGranularity   = 32;
              ptr->AddrRangeMin           = 0;
              ptr->AddrRangeMax           = 0;
              ptr->AddrTranslationOffset  = (ResStatus == ResAllocated) ? EFI_RESOURCE_SATISFIED : EFI_RESOURCE_LESS;
              ptr->AddrLen                = RootBridgeInstance->ResAllocNode[Index].Length;
              break;

            case TypeMem64:
              ///
              /// Memory 64
              ///
              ptr->Desc                   = 0x8A;
              ptr->Len                    = 0x2B;
              ptr->ResType                = 0;
              ptr->GenFlag                = 0;
              ptr->SpecificFlag           = 0;
              ptr->AddrSpaceGranularity   = 64;
              ptr->AddrRangeMin           = 0;
              ptr->AddrRangeMax           = 0;
              ptr->AddrTranslationOffset  = (ResStatus == ResAllocated) ? EFI_RESOURCE_SATISFIED : EFI_RESOURCE_LESS;
              ptr->AddrLen                = RootBridgeInstance->ResAllocNode[Index].Length;
              break;

            case TypePMem64:
              ///
              /// Prefetch memory 64
              ///
              ptr->Desc                   = 0x8A;
              ptr->Len                    = 0x2B;
              ptr->ResType                = 0;
              ptr->GenFlag                = 0;
              ptr->SpecificFlag           = 6;
              ptr->AddrSpaceGranularity   = 64;
              ptr->AddrRangeMin           = 0;
              ptr->AddrRangeMax           = 0;
              ptr->AddrTranslationOffset  = (ResStatus == ResAllocated) ? EFI_RESOURCE_SATISFIED : EFI_RESOURCE_LESS;
              ptr->AddrLen                = RootBridgeInstance->ResAllocNode[Index].Length;
              break;
            }

            Temp += sizeof (EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR);
          }
        }

        ((EFI_ACPI_END_TAG_DESCRIPTOR *) Temp)->Desc      = 0x79;
        ((EFI_ACPI_END_TAG_DESCRIPTOR *) Temp)->Checksum  = 0x0;
        *Configuration = Buffer;
      }

      return EFI_SUCCESS;
    }

    List = List->ForwardLink;
  }

  return EFI_INVALID_PARAMETER;
}

/**
  This function is called for all the PCI controllers that the PCI
  bus driver finds. Can be used to Preprogram the controller.

  @param[in] This              - The EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_ PROTOCOL instance
  @param[in] RootBridgeHandle  - The PCI Root Bridge handle
  @param[in] PciAddress        - Address of the controller on the PCI bus
  @param[in] Phase             - The Phase during resource allocation

  @retval EFI_SUCCESS            -  Succeed.
  @retval EFI_INVALID_PARAMETER  -  RootBridgeHandle is not a valid handle.
**/
EFI_STATUS
EFIAPI
PreprocessController (
  IN  EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL          *This,
  IN  EFI_HANDLE                                                RootBridgeHandle,
  IN  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_PCI_ADDRESS               PciAddress,
  IN  EFI_PCI_CONTROLLER_RESOURCE_ALLOCATION_PHASE              Phase
  )
{
  PCI_HOST_BRIDGE_INSTANCE  *HostBridgeInstance;
  PCI_ROOT_BRIDGE_INSTANCE  *RootBridgeInstance;
  LIST_ENTRY                *List;

  HostBridgeInstance  = INSTANCE_FROM_RESOURCE_ALLOCATION_THIS (This);
  List                = HostBridgeInstance->Head.ForwardLink;

  ///
  /// Enumerate the root bridges in this host bridge
  ///
  while (List != &HostBridgeInstance->Head) {
    RootBridgeInstance = DRIVER_INSTANCE_FROM_LIST_ENTRY (List);
    if (RootBridgeHandle == RootBridgeInstance->Handle) {
      return EFI_SUCCESS;
    }

    List = List->ForwardLink;
  }

  return EFI_INVALID_PARAMETER;
}

/**
  Calculate max memory of power 2

  @param[in] MemoryLength  -  Input memory length.

  @retval Returned Maximum length.
**/
UINT64
Power2MaxMemory (
  IN UINT64                     MemoryLength
  )
{
  UINT64  Result;

  if (RShiftU64 (MemoryLength, 32)) {
    Result = LShiftU64 ((UINT64) GetPowerOfTwo64 (RShiftU64 (MemoryLength, 32)), 32);
  } else {
    Result = (UINT64) GetPowerOfTwo64 (MemoryLength);
  }

  return Result;
}
