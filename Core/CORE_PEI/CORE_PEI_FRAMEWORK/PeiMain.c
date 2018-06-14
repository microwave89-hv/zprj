/*++

Copyright (c) 2004 - 2005, Intel Corporation                                                         
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
#include EFI_PPI_DEFINITION (FindFv)
#include EFI_GUID_DEFINITION (StatusCodeDataTypeId)
#include EFI_GUID_DEFINITION (StatusCode)

//
//CAR is filled with this initial value during SEC phase
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

static EFI_PEI_PPI_DESCRIPTOR mMemoryDiscoveredPpi = {
  (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gPeiMemoryDiscoveredPpiGuid,
  NULL
};

//
// Pei Core Module Variables
// 
//
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

  PeiFvFindNextVolume,
  PeiFfsFindNextFile,
  PeiFfsFindSectionData,

  PeiInstallPeiMemory,
  PeiAllocatePages,
  PeiAllocatePool,
  PeiCoreCopyMem,
  PeiCoreSetMem,

  PeiReportStatusCode,

//*** AMI PORTING BEGIN ***//
// This is a bug fix.
// In accordance with PEI CIS 0.91 
// this structure has been extended with two more pointers.
//  PeiCoreResetSystem
  PeiCoreResetSystem,
  NULL,
  NULL
//*** AMI PORTING END *****//
};

VOID
EFIAPI
AsmWriteMm7 (
  IN UINT64   Value
  );

EFI_STATUS
EFIAPI
PeiCore (
  IN EFI_PEI_STARTUP_DESCRIPTOR  *PeiStartupDescriptor,
  IN PEI_CORE_INSTANCE           *OldCoreData
  );

//
// Main entry point to the PEI Core
//
EFI_PEI_CORE_ENTRY_POINT (PeiMain)

EFI_STATUS
EFIAPI
PeiMain (
  IN EFI_PEI_STARTUP_DESCRIPTOR  *PeiStartupDescriptor
  )
/*++

Routine Description:

  Main entry point to Pei Core.

Arguments:

  PeiStartupDescriptor - Information and services provided by SEC phase.

Returns:

  This function never returns

--*/
{
  return PeiCore (PeiStartupDescriptor, NULL);
}

EFI_STATUS
EFIAPI
PeiCore (
  IN EFI_PEI_STARTUP_DESCRIPTOR  *PeiStartupDescriptor,
  IN PEI_CORE_INSTANCE           *OldCoreData
  )
/*++

Routine Description:

  The entry routine to Pei Core, invoked by PeiMain during transition
  from SEC to PEI. After switching stack in the PEI core, it will restart
  with the old core data.

Arguments:

  PeiStartupDescriptor - Information and services provided by SEC phase.
  OldCoreData          - Pointer to old core data that is used to initialize the
                         core's data areas.

Returns:

  This function never returns
  EFI_NOT_FOUND        - Never reach

--*/
{
  PEI_CORE_INSTANCE                                     PrivateData;
  EFI_STATUS                                            Status;
  PEI_CORE_TEMP_POINTERS                                TempPtr;
  PEI_CORE_DISPATCH_DATA                                *DispatchData;
  
 
#ifdef EFI_PEI_PERFORMANCE
  UINT64                      mTick;

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
    PeiCoreCopyMem (&PrivateData, OldCoreData, sizeof (PEI_CORE_INSTANCE));
  } else {
    PeiCoreSetMem (&PrivateData, sizeof (PEI_CORE_INSTANCE), 0);
  }

  PrivateData.Signature = PEI_CORE_HANDLE_SIGNATURE;
  PrivateData.PS = &mPS;
  
  //
  //  Mm7 stored PeiServicesTablePointer in EdkII Glue Library
  //  Update Mm7 now
  //
//*** AMI PORTING BEGIN ***//
//#if (defined(EFI32)) || (defined(EFIX64))
#ifndef EFI64
//*** AMI PORTING END *****//
  AsmWriteMm7 ((UINT64)(UINTN)(&PrivateData.PS));
#endif

  InitializeMemoryServices (&PrivateData.PS, PeiStartupDescriptor, OldCoreData);

  InitializePpiServices (&PrivateData.PS, OldCoreData);

  InitializeSecurityServices (&PrivateData.PS, OldCoreData);

  InitializeDispatcherData (&PrivateData.PS, OldCoreData, PeiStartupDescriptor);

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
      for (StackPointer = (UINTN *) OldCoreData->MaxTopOfCarHeap;
           ((UINTN) StackPointer < ((UINTN) OldCoreData->BottomOfCarHeap + OldCoreData->SizeOfCacheAsRam)) 
           && StackValue == INIT_CAR_VALUE;
           StackPointer++) {
        StackValue = *StackPointer;
      }

      PEI_DEBUG ((&PrivateData.PS, EFI_D_INFO, "Total Cache as RAM:    %d bytes.\n", OldCoreData->SizeOfCacheAsRam));
      PEI_DEBUG (
        (
        &PrivateData.PS, EFI_D_INFO, "  CAR stack ever used: %d bytes.\n",
        ((UINTN) OldCoreData->TopOfCarHeap - (UINTN) StackPointer)
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
    if (PeiStartupDescriptor->DispatchTable != NULL) {
      Status = PeiInstallPpi (&PrivateData.PS, PeiStartupDescriptor->DispatchTable);

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

  DispatchData = &PrivateData.DispatchData;

  //
  // Call PEIM dispatcher
  //
//*** AMI PORTING BEGIN ***//
  if (OldCoreData != NULL) {
    AmiInitParts(&PrivateData.PS, InitPartsMem);
    ProcessLoadHob(&PrivateData.PS);
  } else {
    AmiInitParts(&PrivateData.PS, InitParts);
  }
//*** AMI PORTING END *****//
  PeiDispatcher (PeiStartupDescriptor, &PrivateData, DispatchData);

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

  Status = PeiLocatePpi (
            &PrivateData.PS,
            &gEfiDxeIplPpiGuid,
            0,
            NULL,
            &TempPtr.DxeIpl
            );
//*** AMI PORTING BEGIN ***//
  //report DXEIPL_NOT_FOUND error
  if (EFI_ERROR(Status))
    PEI_ERROR_CODE(&PrivateData.PS, PEI_DXEIPL_NOT_FOUND, EFI_ERROR_MAJOR);
//   ASSERT_PEI_ERROR (&PrivateData.PS, Status);
//*** AMI PORTING END *****//      

  PEI_DEBUG ((&PrivateData.PS, EFI_D_INFO, "DXE IPL Entry(%X)\n",TempPtr.DxeIpl->Entry));
  Status = TempPtr.DxeIpl->Entry (
                             TempPtr.DxeIpl,
                             &PrivateData.PS,
//*** AMI PORTING BEGIN ***//
// PEI CIS defines parameter as EFI_PEI_HOB_POINTERS, but
// EFI_PEI_HOB_POINTERS is not defined in PEI CIS.
// Until this is fixed PEI.h defines this parameter as VOID*
//                             PrivateData.HobList
                             PrivateData.HobList.Raw
//*** AMI PORTING END *****//
                             );
//*** AMI PORTING BEGIN ***//
  // If DXE IPL returned control, let's call dispatcher again
  // DXE IPL might have dicovered new FV or have changed a boot mode

  // reset previous bitmap so that the dispatcher will attempt to execute any new PEIMs
  DispatchData->PreviousPeimBitMap = 0;
  // dispatch
  PeiDispatcher (PeiStartupDescriptor, &PrivateData, DispatchData);
  // DXE IPL
  Status = TempPtr.DxeIpl->Entry (
                             TempPtr.DxeIpl,
                             &PrivateData.PS,
                             PrivateData.HobList.Raw
                             );
//*** AMI PORTING END *****//
  ASSERT_PEI_ERROR (&PrivateData.PS, Status);
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