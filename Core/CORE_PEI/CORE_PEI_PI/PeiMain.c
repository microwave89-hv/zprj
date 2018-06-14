/*++

Copyright (c) 2006 - 2007, Intel Corporation                                                         
All rights reserved. This program and the accompanying materials                          
are licensed and made available under the terms and conditions of the BSD License         
which accompanies this distribution.  The full text of the license may be found at        
http://opensource.org/licenses/bsd-license.php                                            
                                                                                          
THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,                     
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.             

Module Name:

  PeiMain.c

Abstract:

  Pei Core Main Entry Point

Revision History

--*/

#include "Tiano.h"
#include "PeiCore.h"
#include "PeiLib.h"
#include EFI_PPI_DEFINITION (MemoryDiscovered)
#include EFI_GUID_DEFINITION (StatusCodeDataTypeId)
#include EFI_GUID_DEFINITION (StatusCode)

//
// CAR is filled with this initial value during SEC phase
//
#define INIT_CAR_VALUE 0x5AA55AA5

#ifdef EFI_PEI_PERFORMANCE

EFI_STATUS
GetTimerValue (
  OUT UINT64    *TimerValue
  );

#endif

//*** AMI PORTING BEGIN ***//
VOID InitParts(VOID* p1, VOID*p2);
VOID InitPartsMem(VOID* p1, VOID*p2);
VOID ProcessLoadHob(EFI_PEI_SERVICES **PeiServices);
VOID AmiInitParts(IN EFI_PEI_SERVICES **PeiServices, VOID* InitFunction);
//*** AMI PORTING END *****//

//
// PPI that represents memory being discoverd in PEI.
//
static EFI_PEI_PPI_DESCRIPTOR mMemoryDiscoveredPpi = {
  (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gPeiMemoryDiscoveredPpiGuid,
  NULL
};

static EFI_PEI_SERVICES  mPS = {
  {
    PEI_SERVICES_SIGNATURE,
    PEI_SERVICES_REVISION,
    sizeof (EFI_PEI_SERVICES),
    0,
    0
  },
  PeiInstallPpi,
  PeiReInstallPpi,
  PeiLocatePpi,
  PeiNotifyPpi,

  PeiGetBootMode,
  PeiSetBootMode,

  PeiGetHobList,
  PeiCreateHob,

  PeiFfsFindNextVolume,
  PeiFfsFindNextFile,
  PeiFfsFindSectionData,

  PeiInstallPeiMemory,
  PeiAllocatePages,
  PeiAllocatePool,
  PeiCoreCopyMem,
  PeiCoreSetMem,

  PeiReportStatusCode,
  PeiResetSystem,

  NULL,
  NULL,

  PeiFfsFindFileByName,
  PeiFfsGetFileInfo,
  PeiFfsGetVolumeInfo,
  PeiRegisterForShadow
};


//
// Main entry point to the PEI Core
//
EFI_PEI_CORE_ENTRY_POINT (PeiMain)

EFI_STATUS
EFIAPI
PeiMain (
  IN CONST EFI_SEC_PEI_HAND_OFF   *SecCoreData,
  IN CONST EFI_PEI_PPI_DESCRIPTOR *PpList
  )
/*++

Routine Description:

  Main entry point to Pei Core.

Arguments:

  SecCoreData   - Information about the PEI core's operating environment.
  PpList        - Points to a list of one or more PPI descriptors to be 
                  installed initially by the PEI core.

Returns:

  This function never returns

--*/
{
  return PeiCore (SecCoreData,PpList, NULL);
}

EFI_STATUS
EFIAPI
PeiCore (
  IN CONST EFI_SEC_PEI_HAND_OFF        *SecCoreData,
  IN CONST EFI_PEI_PPI_DESCRIPTOR      *PpList,
  IN       PEI_CORE_INSTANCE           *OldCoreData
  )
/*++

Routine Description:

  The entry routine to Pei Core, invoked by PeiMain during transition
  from SEC to PEI. After switching stack in the PEI core, it will restart
  with the old core data.

Arguments:

  SecCoreData        - Information and services provided by SEC phase.
  PpList             - Pointer to Ppi list provided by SEC phase.
  OldCoreData        - Pointer to old core data that is used to initialize the
                         core's data areas.

Returns:

  This function never returns
  EFI_NOT_FOUND        - Never reach

--*/
{
  PEI_CORE_INSTANCE     PrivateData;
  EFI_PEI_SERVICES      **PeiServices;
  EFI_STATUS            Status;
  EFI_DXE_IPL_PPI       *DxeIpl;
  EFI_PEI_CPU_IO_PPI    *CpuIo;
  EFI_PEI_PCI_CFG2_PPI  *PciCfg;

#ifdef EFI_PEI_PERFORMANCE
  UINT64              mTick;

  mTick = 0;
  if (OldCoreData == NULL) {
    GetTimerValue (&mTick);
  }
#endif

  
  //
  // For IPF in CAR mode the real memory access is uncached,in InstallPeiMemory()
  //  the 63-bit of address is set to 1.
  //
  SWITCH_TO_CACHE_MODE (OldCoreData);

  if (OldCoreData != NULL) {

    //
    // 2nd time through we are using System Memory and we restore a previous
    // state by copying the OldCoreData into PrivateData. A lot of the 
    // init code will note initialize PrivateData on the 2nd pass. 
    //
    PeiCoreCopyMem (&PrivateData, OldCoreData, sizeof (PEI_CORE_INSTANCE));

    //
    // 2nd time through Pei Core has been shadowed. To Pei Services, 
    // CpuIo and PciCfg services may have been updated by some Pei Modules. So before
    // update PrivateData.ServiceTableShadow with memory version, save the CpuIo
    // PciCfg and restore them then.
    //
    CpuIo = (VOID*)PrivateData.ServiceTableShadow.CpuIo;
    PciCfg = (VOID*)PrivateData.ServiceTableShadow.PciCfg;
    PeiCoreCopyMem (&(PrivateData.ServiceTableShadow), &mPS, sizeof (EFI_PEI_SERVICES));
    PrivateData.ServiceTableShadow.CpuIo  = CpuIo;
    PrivateData.ServiceTableShadow.PciCfg = PciCfg;
  } else {

    //
    // 1st time through we are using Temp memory
    //
    PeiCoreSetMem (&PrivateData, sizeof (PEI_CORE_INSTANCE),0);
    PrivateData.Signature = PEI_CORE_HANDLE_SIGNATURE;
    
    //
    // Copy PeiServices from ROM to Temp memory in PrivateData
    //
    PeiCoreCopyMem (&(PrivateData.ServiceTableShadow), &mPS, sizeof (EFI_PEI_SERVICES));
  }

  PrivateData.PS = &PrivateData.ServiceTableShadow;
  PeiServices = &PrivateData.PS;

  InitializeMemoryServices (&PrivateData, SecCoreData, OldCoreData);
 
  InitializePpiServices (&PrivateData, OldCoreData);

  //
  // Save PeiServicePointer so that it can be retrieved anywhere.
  //
  SetPeiServicesTablePointer(PeiServices);

  if (OldCoreData != NULL) {
    
    PEI_PERF_END (&PrivateData.PS,L"PreMem", NULL, 0);
    PEI_PERF_START (&PrivateData.PS,L"PostMem", NULL, 0);

    //
    // The following code dumps out interesting cache as RAM usage information
    // so we can keep tabs on how the cache as RAM is being utilized.  The
    // PEI_DEBUG_CODE macro is used to prevent this code from being compiled
    // on a debug build.
    //
    PEI_DEBUG_CODE (
      {
        UINTN  *StackPointer;
        UINTN  StackValue;

        StackValue = INIT_CAR_VALUE;
      for (StackPointer = (UINTN *) OldCoreData->TopOfCarHeap;
           ((UINTN) StackPointer < ((UINTN) OldCoreData->BottomOfCarHeap + OldCoreData->SizeOfCacheAsRam)) 
           && StackValue == INIT_CAR_VALUE;
           StackPointer++) {
        StackValue = *StackPointer;
      }

      PEI_DEBUG ((&PrivateData.PS, EFI_D_INFO, "Total Cache as RAM:    %d bytes.\n", OldCoreData->SizeOfCacheAsRam));
      PEI_DEBUG (
        (
        &PrivateData.PS, EFI_D_INFO, "  CAR stack ever used: %d bytes.\n",
        ((UINTN) OldCoreData->MaxTopOfCarHeap - (UINTN) StackPointer)
        )
        );
        PEI_DEBUG (
        (
        &PrivateData.PS, EFI_D_INFO, "  CAR heap used:       %d bytes.\n",
        ((UINTN) OldCoreData->HobList.HandoffInformationTable->EfiFreeMemoryBottom -
         (UINTN) OldCoreData->HobList.Raw)
        )
        );
      }
    )

//*** AMI PORTING BEGIN ***//
    PrivateData.LoadedImage->Ppi = &PrivateData.LoadedImagePpi;
//*** AMI PORTING END *****//    

    //
    // Alert any listeners that there is permanent memory available
    //
    PEI_PERF_START (&PrivateData.PS,L"DisMem", NULL, 0);
    Status = PeiInstallPpi (&PrivateData.PS, &mMemoryDiscoveredPpi);
    PEI_PERF_END (&PrivateData.PS,L"DisMem", NULL, 0);

  } else {

    //
    // Report Status Code EFI_SW_PC_INIT
    //
    PEI_REPORT_STATUS_CODE (
      &(PrivateData.PS),
      EFI_PROGRESS_CODE,
      EFI_SOFTWARE_PEI_CORE | EFI_SW_PC_INIT,
      0,
      NULL,
      NULL
      );
    
    //
    // If first pass, start performance measurement.
    //
    PEI_PERF_START (&PrivateData.PS,L"PreMem", NULL, mTick);
    
    //
    // If SEC provided any PPI services to PEI, install them.
    //
    if (PpList != NULL) {
      Status = PeiInstallPpi (&PrivateData.PS, PpList);
      ASSERT_PEI_ERROR (&PrivateData.PS, Status);
    }
//*** AMI PORTING BEGIN ***//
{
  static EFI_GUID gEfiPeiLoadedImagePpiGuid = EFI_PEI_LOADED_IMAGE_PPI_GUID;
  static EFI_PEI_PPI_DESCRIPTOR LoadedImagePpiDesc =
  { 
    EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
    &gEfiPeiLoadedImagePpiGuid, NULL 
  };
  PeiAllocatePool(&PrivateData.PS,sizeof(EFI_PEI_PPI_DESCRIPTOR),&PrivateData.LoadedImage);
  *PrivateData.LoadedImage = LoadedImagePpiDesc;
  PrivateData.LoadedImage->Ppi = &PrivateData.LoadedImagePpi;
  PeiInstallPpi (&PrivateData.PS, PrivateData.LoadedImage);
}
//*** AMI PORTING END *****//    
  }
  
  InitializeSecurityServices (&PrivateData, OldCoreData);
  
  InitializeDispatcherData (&PrivateData, OldCoreData, SecCoreData);

  //
  // Install Pei Load File PPI. 
  //
  InitializeImageServices (&PrivateData, OldCoreData);

  //
  // Call PEIM dispatcher
  //
//*** AMI PORTING BEGIN ***//
  if (OldCoreData != NULL) {
    AmiInitParts(PeiServices, InitPartsMem);
    ProcessLoadHob(PeiServices);
  } else {
    AmiInitParts(PeiServices, InitParts);
  }
//*** AMI PORTING END *****//
  PeiDispatcher (SecCoreData, &PrivateData);

  //
  // Check if InstallPeiMemory service was called.
  //
//*** AMI PORTING BEGIN ***//
  //report MEMORY_NOT_INSTALLED error
  if (!PrivateData.PeiMemoryInstalled)
    PEI_ERROR_CODE(&PrivateData.PS, PEI_MEMORY_NOT_INSTALLED, EFI_ERROR_MAJOR);
//  PEI_ASSERT(&PrivateData.PS, PrivateData.PeiMemoryInstalled == TRUE);
//*** AMI PORTING END *****//      

  PEI_PERF_END (&PrivateData.PS, L"PostMem", NULL, 0);

  DxeIpl = PeiReturnPpi (&PrivateData.PS, &gEfiDxeIplPpiGuid);
//*** AMI PORTING BEGIN ***//
  //report DXEIPL_NOT_FOUND error
  if (DxeIpl==NULL)
    PEI_ERROR_CODE(&PrivateData.PS, PEI_DXEIPL_NOT_FOUND, EFI_ERROR_MAJOR);
//  PEI_ASSERT (&PrivateData.PS, DxeIpl != NULL);
//*** AMI PORTING END *****//      

  PEI_DEBUG ((&PrivateData.PS, EFI_D_INFO, "DXE IPL Entry\n"));

//*** AMI PORTING BEGIN ***//
  //DxeIpl->Entry (DxeIpl, &PrivateData.PS, PrivateData.HobList);
  DxeIpl->Entry (DxeIpl, &PrivateData.PS, PrivateData.HobList.Raw);
//*** AMI PORTING END *****//      
//*** AMI PORTING BEGIN ***//
  // If DXE IPL returned control, let's call dispatcher again
  // DXE IPL might have dicovered new FV or have changed a boot mode

  // reset previous bitmap so that the dispatcher will attempt to execute any new PEIMs
  // dispatch
  PeiDispatcher (SecCoreData, &PrivateData);
  // DXE IPL
  DxeIpl->Entry (DxeIpl, &PrivateData.PS, PrivateData.HobList.Raw);
//*** AMI PORTING END *****//
  PEI_ASSERT (&PrivateData.PS,FALSE);
  return EFI_NOT_FOUND;

}

//*** AMI PORTING BEGIN ***//
VOID UpdatedLoadedImagePpi(
  IN EFI_PEI_SERVICES         **PeiServices,
  EFI_PHYSICAL_ADDRESS        ImageAddress,
  UINT64                      ImageSize,
  EFI_PEI_FILE_HANDLE         FileHandle
)
{
  PEI_CORE_INSTANCE *Private = PEI_CORE_INSTANCE_FROM_PS_THIS(PeiServices);
  Private->LoadedImagePpi.ImageAddress = ImageAddress;
  Private->LoadedImagePpi.ImageSize = ImageSize;
  Private->LoadedImagePpi.FileHandle = FileHandle;
  PeiReInstallPpi(PeiServices,Private->LoadedImage,Private->LoadedImage);
}
//*** AMI PORTING END *****//
