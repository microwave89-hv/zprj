//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2015, American Megatrends, Inc.         **
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
// $Header: /Alaska/SOURCE/Modules/NVMe/NvmeSetup.c 5     5/19/15 5:08a Ksudarsanan $
//
// $Revision: 5 $
//
// $Date: 5/19/15 5:08a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/NVMe/NvmeSetup.c $
// 
// 5     5/19/15 5:08a Ksudarsanan
// [TAG]  		EIP218818
// [Category]  	Improvement
// [Description]  	Aptio 4.x: When NVMe device is not connect then in BIOS
// Setup should display "No Nvme device found"
// [Files]  		Nvme.sd, Nvme.uni, NvmeSetup.c
// 
// 4     9/04/14 7:37a Anandakrishnanl
// [TAG]  		EIP180861
// [Category]  	Improvement
// [Description]  	Legacy Boot support in Aptio 4.x Nvme driver
// 
// [Files]  		
// Nvme.cif	
// Nvme.mak	
// Nvme.uni
// Nvme.chm	
// NvmeSetup.c
// NvmeBus.c
// NvmeComponentName.c
// NvmeIncludes.h
// NvmeBus.h
// [NvmeControllerLib]
// [NvmeSmm]
// [NVMEINT13]
// [NvmeProtocol]
// 
// 2     7/02/14 8:31a Anandakrishnanl
// [TAG]  		EIP175772
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	AMI Nvme Driver setup tries to display the devices detected
// by UEFI option rom
// [RootCause]  	Display to Nvme devices information did not chack for
// ontroller handle to confirm if gAmiNvmeControllerProtocol is present
// [Solution]  	Added checking in the controller handle to confirm if
// gAmiNvmeControllerProtocol is present or not.
// [Files]  		NvmeSetup.c
// 
// 1     6/20/14 6:27a Anandakrishnanl
// [TAG]  		EIP172958
// [Category]  	New Feature
// [Description]  	Nvme Driver Intial Checkin
// [Files]  		Nvme.cif
// Nvme.sdl
// Nvme.mak
// Nvme.sd
// Nvme.uni
// Nvme.chm
// NvmeSetup.c
// NvmeBus.c
// NvmeController.c
// NvmeComponentName.c
// NvmeIncludes.h
// NvmeBus.h
// NvmeController.h
// 
//**********************************************************************
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:        NvmeSetup.c
//
// Description:	Display the Nvme Controller and device information in the Setup
//
//<AMI_FHDR_END>
//**********************************************************************
#include <AmiLib.h>
#include <AmiDxeLib.h>
#include <Setup.h>
#include <SetupStrTokens.h>
#include <Protocol\DevicePath.h>
#include <Token.h>
#include "NvmeIncludes.h"
#include "NvmeBus.h"

#define     MSG_NVME_DP     23
#define     DRIVEMAXCOUNT   4

extern EFI_RUNTIME_SERVICES     *pRS;

typedef struct {
    STRING_REF  ControllerString;
    STRING_REF  DeviceString;
} NVME_SETUP_STRUC;

NVME_SETUP_STRUC   NVMeSetupStruc[] = {
    {STRING_TOKEN(STR_NVME0_CONTROLLER), STRING_TOKEN(STR_NVME0_NAME)},
    {STRING_TOKEN(STR_NVME1_CONTROLLER), STRING_TOKEN(STR_NVME1_NAME)},
    {STRING_TOKEN(STR_NVME2_CONTROLLER), STRING_TOKEN(STR_NVME2_NAME)},
    {STRING_TOKEN(STR_NVME3_CONTROLLER), STRING_TOKEN(STR_NVME3_NAME)},
};

static EFI_GUID gAmiNvmeControllerProtocolGuid 	= AMI_NVME_CONTROLLER_PROTOCOL_GUID;

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   UnicodeStrToAsciiStr
//
// Description: This function converts the content of the Unicode string Source
//              to the ASCII string Destination by copying the lower 8 bits of
//              each Unicode character and returns Destination
//
// Input:
//          Source        A pointer to a Null-terminated Unicode string.
//          Destination   A pointer to a Null-terminated ASCII string.
//
// Output:
//          NONE
//
// Modified:
//      
// Referrals: 
//
// Notes:  None  
//
//
//<AMI_PHDR_END>
//**********************************************************************
CHAR8* 
UnicodeStrToAsciiStr (
  IN      CONST CHAR16              *Source,
  OUT     CHAR8                     *Destination
  )
{
  CHAR8                               *ReturnValue;
  UINTN                               TempReturnValue;
  UINTN                               TempSource;

  ASSERT (Destination != NULL);

  //
  // ASSERT if Source is long than PcdMaximumUnicodeStringLength.
  // Length tests are performed inside StrLen().
  //
  TempSource = (Wcslen ((CHAR16 *)Source) + 1) * sizeof (*Source);
  ASSERT (TempSource != 0);

  //
  // Source and Destination should not overlap
  //
  ASSERT ((UINTN) ((CHAR16 *) Destination -  Source) > Wcslen ((CHAR16 *)Source));
  ASSERT ((UINTN) ((CHAR8 *) Source - Destination) > Wcslen ((CHAR16 *)Source));


  ReturnValue = Destination;
  while (*Source != '\0') {
    //
    // If any Unicode characters in Source contain 
    // non-zero value in the upper 8 bits, then ASSERT().
    //
    ASSERT (*Source < 0x100);
    *(Destination++) = (CHAR8) *(Source++);
  }

  *Destination = '\0';

  //
  // ASSERT Original Destination is less long than PcdMaximumAsciiStringLength.
  // Length tests are performed inside AsciiStrLen().
  //
  TempReturnValue = (Strlen((CHAR8 *)ReturnValue) + 1) * sizeof (*ReturnValue);
  ASSERT (TempReturnValue!= 0);

  return ReturnValue;
}


//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   InitNvmeStrings
//
// Description: This function initializes the SB related setup option values
//
// Input:
//           IN EFI_HII_HANDLE HiiHandle - Handle to HII database
//           IN UINT16 Class - Indicates the setup class
//
// Output:
//          NONE
//
// Modified:
//      
// Referrals: 
//
// Notes:  None  
//
//
//<AMI_PHDR_END>
//**********************************************************************
VOID 
InitNvmeStrings(
    IN EFI_HII_HANDLE   HiiHandle, 
    IN UINT16           Class
)
{
    EFI_STATUS                          Status;
    UINTN                               Index;
    UINTN                               HandleCount;
    EFI_HANDLE                          *HandleBuffer;
    UINTN                               HandleCountPciIo;
    EFI_HANDLE                          *HandleBufferPciIo;
    EFI_DEVICE_PATH_PROTOCOL            *DevicePath;
    EFI_DEVICE_PATH_PROTOCOL            *DevicePathNode;
    EFI_PCI_IO_PROTOCOL                 *PciIO;
    AMI_NVME_CONTROLLER_PROTOCOL    	*NvmeController = NULL;
    EFI_OPEN_PROTOCOL_INFORMATION_ENTRY *OpenInfo;
    UINTN                               OpenInfoCount;
    UINTN                               IndexPciIo;
    UINTN                               IndexOpenInfo;
    EFI_HANDLE                          DeviceHandle;
    EFI_HANDLE                          ControllerHandle;
    EFI_HANDLE                          DriverBindingHandle;
    EFI_COMPONENT_NAME2_PROTOCOL        *ComponentName2Protocol;
    CHAR16                              *DriveNameUni;
    CHAR8                               *NewString;
    UINTN                               SegmentNumber;
    UINTN                               BusNumber;
    UINTN                               DeviceNumber;
    UINTN                               FunctionNumber;
    UINT8                               DrivePresence[DRIVEMAXCOUNT] = {0};
    UINT8                               DriveIndex = 0;
    SETUP_DATA                          *SetupData;
    EFI_GUID                            SetupGuid = SETUP_GUID;
    UINTN                               SetupSize = sizeof(SETUP_DATA);
    UINT32                              Attribute = 0;

    
    if (Class == ADVANCED_FORM_SET_CLASS) { 
        // Collect all DevicePath protocol and check for NVMe Controller
        Status = pBS->LocateHandleBuffer(
                      ByProtocol,
                      &gEfiDevicePathProtocolGuid,
                      NULL,
                      &HandleCount,
                      &HandleBuffer
                     );
        
        if (EFI_ERROR(Status)) return;
        
        for (Index = 0; Index < HandleCount; Index++) {
            
            Status = pBS->HandleProtocol(
                          HandleBuffer[Index],
                          &gEfiDevicePathProtocolGuid,
                          (VOID *)&DevicePath
                          );
            
             ASSERT_EFI_ERROR(Status);
             if(EFI_ERROR(Status)) {
                 continue;
             }
             
             DevicePathNode = DevicePath;
             while (!isEndNode (DevicePathNode)) {
                 if ((DevicePathNode->Type == MESSAGING_DEVICE_PATH) &&
                         (DevicePathNode->SubType == MSG_NVME_DP)) {
                     break;
                 }

                 DevicePathNode = NEXT_NODE(DevicePathNode);
            }
             
            if (DevicePathNode == NULL || isEndNode (DevicePathNode)) {
                continue;
            }
            
            // NVMe Device Handle is found.
            DeviceHandle = HandleBuffer[Index];
            
            // NVMe device is found. Now get the CONTROLLER. Check all the PCIio handles.
            Status = pBS->LocateHandleBuffer(
                         ByProtocol,
                         &gEfiPciIoProtocolGuid,
                         NULL,
                         &HandleCountPciIo,
                         &HandleBufferPciIo
                         );
            
            for (IndexPciIo = 0; IndexPciIo < HandleCountPciIo; IndexPciIo++) {
                Status = pBS->HandleProtocol(
                              HandleBufferPciIo[IndexPciIo],
                              &gEfiPciIoProtocolGuid,
                              (VOID *)&PciIO
                              );
                        
                ASSERT_EFI_ERROR(Status);
                if(EFI_ERROR(Status)) {
                    continue;
                }

                Status = pBS->HandleProtocol(
                              HandleBufferPciIo[IndexPciIo],
                              &gAmiNvmeControllerProtocolGuid,
                              (VOID *)&NvmeController
                              );
                
                // If Ami Nvme Controller Protocol not found on the Controller handle ( PciIo handle)
                // do not process the Pci Io Handle
                if(EFI_ERROR(Status)) {
                    continue;
                }
                
                OpenInfoCount = 0;
                Status = pBS->OpenProtocolInformation(
                              HandleBufferPciIo[IndexPciIo],
                              &gEfiPciIoProtocolGuid,
                              &OpenInfo,
                              &OpenInfoCount
                              );
                
                ASSERT_EFI_ERROR(Status);
                if(EFI_ERROR(Status)) {
                    continue;
                }                
                
                for (IndexOpenInfo = 0; IndexOpenInfo < OpenInfoCount; IndexOpenInfo++) {
                    
                    //Check if the handle is opened BY_CHILD and also comnpare the device handle.
                    if ((OpenInfo[IndexOpenInfo].Attributes & EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER) &&
                            (OpenInfo[IndexOpenInfo].ControllerHandle == DeviceHandle)){
                    
                        DriverBindingHandle = OpenInfo[IndexOpenInfo].AgentHandle;
                        // Get the handle for the Controller
                        ControllerHandle = HandleBufferPciIo[IndexPciIo]; 
                        
                        // Now PCI controller and DriverBinding handle is found. Get the Component2Protocol now.
                        Status = pBS->HandleProtocol(
                                      DriverBindingHandle,
                                      &gEfiComponentName2ProtocolGuid,
                                      (VOID *)&ComponentName2Protocol
                                      );
                        ASSERT_EFI_ERROR(Status);
                        if(EFI_ERROR(Status)) {
                            continue;
                        }     
                        
                        Status = ComponentName2Protocol->GetControllerName (
                                                         ComponentName2Protocol,
                                                         ControllerHandle,
                                                         DeviceHandle,
                                                         LANGUAGE_CODE_ENGLISH,
                                                         &DriveNameUni
                                                         );
                        
                        ASSERT_EFI_ERROR(Status);
                        if(EFI_ERROR(Status)) {
                            continue;
                        }     
                        
                        Status = pBS->AllocatePool(
                                      EfiBootServicesData, 
                                      256,
                                      (VOID *) &NewString);
                        ASSERT_EFI_ERROR (Status);
                                              
                        UnicodeStrToAsciiStr (DriveNameUni, NewString);
                                            
                        InitString(
                                HiiHandle,
                                NVMeSetupStruc[DriveIndex].DeviceString,
                                L"%S", 
                                NewString
                                );
                                             
                         Status = PciIO->GetLocation (
                                         PciIO,
                                         &SegmentNumber,
                                         &BusNumber,
                                         &DeviceNumber,
                                         &FunctionNumber
                                         );
                                              
                         Sprintf(NewString, "Bus:%X Dev:%x Func:%x", BusNumber, DeviceNumber, FunctionNumber);
                         
                         InitString(
                                 HiiHandle,
                                 NVMeSetupStruc[DriveIndex].ControllerString,
                                 L"%S", 
                                 NewString
                                 );
                                              
                         //Enable the string to be displayed in setup
                         DrivePresence[DriveIndex] = 1;
                         DriveIndex++;
                                              
                         pBS->FreePool(NewString);
                    }
                }
                pBS->FreePool(OpenInfo);              
            }
            pBS->FreePool(HandleBufferPciIo);
        }
        
        pBS->FreePool(HandleBuffer);
        
        // Update setupdata to show whether strings need to be displayed or not
        Status = pBS->AllocatePool(EfiBootServicesData, sizeof (SETUP_DATA),(VOID *) &SetupData);
        ASSERT_EFI_ERROR (Status);
    
        SetupSize = sizeof (SETUP_DATA);
        
        Status = pRS->GetVariable (
                      L"Setup",
                      &SetupGuid,
                      &Attribute,
                      &SetupSize,
                      SetupData
                      );

        if(!EFI_ERROR(Status)){
            SetupData->DeviceCount = DriveIndex;        
            for (DriveIndex = 0; DriveIndex < DRIVEMAXCOUNT; DriveIndex++){
                SetupData->ShowNVMeDrive[DriveIndex] = DrivePresence[DriveIndex];
            }
        
            Status = pRS->SetVariable (
                          L"Setup",
                          &SetupGuid,
                          Attribute,
                          sizeof (SETUP_DATA),
                          SetupData
                          );
            
            ASSERT_EFI_ERROR (Status);
            
        }
        pBS->FreePool(SetupData);
    }

    return;
}


//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2015, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
