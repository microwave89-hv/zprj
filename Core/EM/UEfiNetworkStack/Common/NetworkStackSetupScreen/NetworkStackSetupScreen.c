//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
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
// $Header: /Alaska/BIN/Modules/Network/UEFINetworkStack II/Common/NetworkStackSetupScreen/NetworkStackSetupScreen.c 3     6/09/14 4:10a Anushav $Revision:
//
// $Date:
//**********************************************************************
// Revision History
// ----------------
// 
//**********************************************************************

#include <AmiDxeLib.h>
#include <NetworkStackSetupScreen.h>

NETWORK_STACK  	mNetworkStackData;
EFI_GUID  	mNetworkStackGuid = NETWORK_STACK_GUID;



//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:        InitNetworkStackVar
//
// Description: Entry point of the  network stack setup driver. This entry point is 
//  necessary to initlialize the NetworkStack setup driver.
//
// Input:
//  ImageHandle   EFI_HANDLE: A handle for the image that is initializing this driver
//  SystemTable   EFI_SYSTEM_TABLE: A pointer to the EFI system table  
// 
// Output:
//  EFI_SUCCESS:              Driver initialized successfully
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS InitNetworkStackVar (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{

  UINTN                Size;
  EFI_STATUS           Status;

  InitAmiLib(ImageHandle,SystemTable);

  Size = sizeof(NETWORK_STACK);
  Status = pRS->GetVariable(L"NetworkStackVar",&mNetworkStackGuid, NULL, &Size, &mNetworkStackData);

  if (Status == EFI_NOT_FOUND) {

    pBS->SetMem(&mNetworkStackData, 
                    sizeof(NETWORK_STACK), 
                    0);

    pRS->SetVariable(
         L"NetworkStackVar",&mNetworkStackGuid,
         EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS,
         sizeof(NETWORK_STACK), &mNetworkStackData
     );

  } 

  return EFI_SUCCESS;

}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

