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
// $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/PchWrap/PchSpiWrap/PchSpiWrap.c 2     11/17/14 7:31a Mirayang $
//
// $Revision: 2 $
//
// $Date: 11/17/14 7:31a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/PchWrap/PchSpiWrap/PchSpiWrap.c $
// 
// 2     11/17/14 7:31a Mirayang
// [TAG]  		EIP191661
// [Category]  	Improvement
// [Description]  	SUT can't generate UEFI SCT2.3.1 report completely.
// 
// 1     2/08/12 8:33a Yurenlai
// Intel Lynx Point/SB eChipset initially releases.
// 
//*************************************************************************
//----------------------------------------------------------------------
// Includes
#include <AmiDxeLib.h>
#include <Protocol\LoadPe32Image.h>
#include "token.h"


static EFI_GUID gDxeSvcTblGuid = DXE_SERVICES_TABLE_GUID;
EFI_GUID gPchSpiRuntimeFFsGuid = \
    {0xC194C6EA,0xB68C,0x4981,0xB6,0x4B,0x9B,0xD2,0x71,0x47,0x4B,0x20};

EFI_STATUS
FFsLoaderToRuntime( 
   IN  EFI_HANDLE    ImageHandle
);

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   PchSpiWrapEntry
//
// Description: This function load PchSpi and execute it.
//
// Input:       ImageHandle       Image handle of this driver.
//              SystemTable       Global system service table.
//
// Output:      EFI_SUCCESS       Load and execute complete.
//              EFI_UNSUPPORTED       Image type is unsupported by this driver.
//              EFI_OUT_OF_RESOURCES  Do not have enough resources to initialize the driver.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
PchSpiWrapEntry(
  IN EFI_HANDLE       ImageHandle,
  IN EFI_SYSTEM_TABLE *SystemTable
  )
{
  EFI_STATUS                Status;
  
  InitAmiLib(ImageHandle, SystemTable);

  Status = FFsLoaderToRuntime( ImageHandle);
  ASSERT_EFI_ERROR (Status);

  return Status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   FFsLoaderToRuntime
//
// Description: Load FFs to Runtime.
//
// Input:       ImageHandle       Image handle of this driver.
//
// Output:      EFI_SUCCESS       FFs Load to Runtime complete.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
FFsLoaderToRuntime(
   IN  EFI_HANDLE    ImageHandle 
){
  EFI_STATUS                Status;
  EFI_PHYSICAL_ADDRESS      Dst;
  EFI_PHYSICAL_ADDRESS      EntryPoint;
  EFI_PE32_IMAGE_PROTOCOL   *LoadPeImageEx;
  VOID                      *Buffer;
  UINTN                     BufferSize;
  UINT32                    AuthenticationStatus;
  UINTN                     Pages;
  EFI_HANDLE                FFsImageHandle;
  EFI_DEVICE_PATH_PROTOCOL  EndOfDp = { 0x7F, 0xFF, 0x4 , 0x0 };

  Buffer = 0;

  Status = FvReadPe32Image (
             &gPchSpiRuntimeFFsGuid,
             &Buffer,
             &BufferSize,
             &AuthenticationStatus
             );

  if (EFI_ERROR (Status)) {
    return Status;
  }

  Pages = EFI_SIZE_TO_PAGES (BufferSize) + 2;
  Status = pBS->AllocatePages (
                  AllocateAnyPages,
                  EfiRuntimeServicesCode,
                  Pages,
                  &Dst
                  );

  Status = pBS->LocateProtocol (&gEfiLoadPeImageGuid, NULL, &LoadPeImageEx);
  if (EFI_ERROR (Status)) {
    pBS->FreePool (&Dst);
    return Status;
  }

  Status = LoadPeImageEx->LoadPeImage(
                            LoadPeImageEx,
                            ImageHandle,
//                            NULL,
                            &EndOfDp,
                            Buffer,
                            BufferSize,
                            Dst,
                            &Pages,
                            &FFsImageHandle,
                            &EntryPoint,
                            EFI_LOAD_PE_IMAGE_ATTRIBUTE_NONE
                            );
  if (EFI_ERROR (Status)) {
    pBS->FreePool (&Dst);
    return Status;
  }

  Status = pBS->StartImage(FFsImageHandle, NULL, NULL);
  pBS->FreePool(Buffer);

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
