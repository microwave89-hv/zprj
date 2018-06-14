//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/HddAcoustic/AcousticSetup.c 7     3/05/12 3:14a Rameshr $
//
// $Revision: 7 $
//
// $Date: 3/05/12 3:14a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/HddAcoustic/AcousticSetup.c $
// 
// 7     3/05/12 3:14a Rameshr
// [TAG]  		EIP82971
// [Category]  	Improvement
// [Description]  	Added dynamich PCIe base Support in IdeAcoustic
// [Files]  		AcousticBoard.c, AcousticSetup.c
// 
// 6     1/24/12 1:42a Rameshr
// [TAG]  		EIP67652
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	Build error when token SB_SETUP_SUPPORT disabled
// [RootCause]  	Unresolved external symbol
// gEfiDiskInfoProtocolGuid,SwapEntries referenced in function
// InitAcousticStrings
// [Solution]  	Added gEfiDiskInfoProtocolGuid and SwapEntries function
// locally
// [Files]  		AcousticSetup.c
// 
// 5     2/10/11 11:28a Pats
// [TAG] - EIP 52920
// [Category]- Function Request
// [Severity]- Minor
// [Symptom] - The Acoustic mode (Bypass/Quiet/Max Performance) of port 5
// is invalid on AMD SB700.
// [RootCause] - Special case where 2nd controller counts by incrementing
// device number only not handled properly
// [Solution] - Modified functions that handle this case.
// [Files] - Acoustic.c, AcousticBoard.c, AcousticSetup.c
// 
// 4     1/07/11 5:52p Pats
// Added processing for SECOND_CONTROLLER_COUNTS_BY_DEVICE token.
// 
// 3     1/07/11 12:15p Pats
// Changed how devices on second controller are handled.
// 
// 2     1/05/11 6:33p Pats
// Made more generic. Removed all south bridge-specific references.
// 
// 1     1/05/11 12:22a Rameshr
// Initial check-in for Hdd Acoustic Management Support.
// 
//**********************************************************************

//**********************************************************************
//<AMI_FHDR_START>
//
// Name: AcousticSetup.c
//
// Description: This file contains functions used by the Acoustic module
//
//<AMI_FHDR_END>
//**********************************************************************

#include <SetupStrTokens.h>
#if (EFI_SPECIFICATION_VERSION >= 0x0002000A)
#include <UefiHii.h>
#else
#include <Protocol\HII.h>
#endif
#include <Protocol\DevicePath.h>
#include "Acoustic.h"

#if DYNAMIC_PCIEXBASE_SUPPORT
UINT32 GetPciBaseAddr(VOID);
#define PCIEX_BASE GetPciBaseAddr()
#else
#define PCIEX_BASE PCIEX_BASE_ADDRESS
#endif
#if LOCAL_ACOUSTIC_SETUP
#include <Protocol\PDiskInfo.h>

static EFI_GUID gEfiDiskInfoProtocolGuid = EFI_DISK_INFO_PROTOCOL_GUID;

UINT8 gIdeControllerLocation[] = IDE_CONTROLLER_LOCATION;
UINT8 gIdeControllerLocation2[] = SECOND_CONTROLLER_LOCATION;

//
// Add more elements if there are more than 6 SATA ports
//
STRING_REF DevStrings[] = {
STRING_TOKEN( STR_ACHDD_0 ),
STRING_TOKEN( STR_ACHDD_1 ),
STRING_TOKEN( STR_ACHDD_2 ),
STRING_TOKEN( STR_ACHDD_3 ),
STRING_TOKEN( STR_ACHDD_4 ),
STRING_TOKEN( STR_ACHDD_5 ),
};


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   Swap_Entries
//
// Description: 
//
// Inpuut:      IN CHAR8    *Data,
//              IN UINT16   Size
//
// Output:      None
//
// Notes:       
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID Swap_Entries (
  IN CHAR8    *Data,
  IN UINT16   Size
)
{
  UINT16  Index;
  CHAR8   Temp8;

  for (Index = 0; (Index+1) < Size; Index+=2) {
    Temp8           = Data[Index];
    Data[Index]     = Data[Index + 1];
    Data[Index + 1] = Temp8;
  }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   InitAcousticStrings
//
// Description: Initialize Acoustic misc configuration strings.
//
// Input:
//              IN EFI_HII_HANDLE   HiiHandle
//              IN UINT16           Class
//
// Output:
//              VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID 
InitAcousticStrings(
    EFI_HII_HANDLE      HiiHandle, 
    UINT16              Class
)
{
    EFI_STATUS                      Status;
    PCI_DEVICE_PATH                 *PciDevicePath;
    CHAR8                           *NewString;
    UINT8                           Index;
    UINT8                           SataMode;
    UINTN                           HandleCount;
    EFI_HANDLE                      *HandleBuffer;
    EFI_DEVICE_PATH_PROTOCOL        *DevicePath;
    EFI_DEVICE_PATH_PROTOCOL        *DevicePathNode;
    EFI_DISK_INFO_PROTOCOL          *DiskInfo;
    UINT32                          IdeDevice, IdeChannel;
    IDENTIFY_DATA                   *IdentifyDriveInfo = NULL;
    UINT32                          BufferSize = 0;
    STRING_REF                      Token;
    CHAR8                           ModelNumber[43];
    UINTN                           PciAddress;
    UINT8                           IdeControllerLocation[] = IDE_CONTROLLER_LOCATION;

    if (Class == ADVANCED_FORM_SET_CLASS) {
        Status = pBS->AllocatePool(EfiBootServicesData, 43, &NewString);
        ASSERT_EFI_ERROR(Status);

        PciDevicePath = NULL;

        PciAddress = MmPciAddress(PCIEX_BASE, 
                                  IdeControllerLocation[0], 
                                  IdeControllerLocation[1], 
                                  IdeControllerLocation[2], 
                                  PCI_SCC);

        SataMode = *((volatile UINT8 *)(UINTN)(PciAddress));

        Status = pBS->LocateHandleBuffer (
                                          ByProtocol,
                                          &gEfiDiskInfoProtocolGuid,
                                          NULL,
                                          &HandleCount,
                                          &HandleBuffer
                                          );
        if (EFI_ERROR(Status)) {
            HandleCount = 0;
        }

        for (Index = 0; Index < HandleCount; Index++) {
            Status = pBS->HandleProtocol (
                                          HandleBuffer[Index],
                                          &gEfiDevicePathProtocolGuid,
                                          (VOID *) &DevicePath
                                          );
            ASSERT_EFI_ERROR(Status);

            DevicePathNode = DevicePath;
            while (!isEndNode (DevicePathNode)) {
                if ((DevicePathNode->Type == HARDWARE_DEVICE_PATH) &&
                    (DevicePathNode->SubType == HW_PCI_DP)) {
                    PciDevicePath = (PCI_DEVICE_PATH *) DevicePathNode;
                    break;
                }

                DevicePathNode = NEXT_NODE (DevicePathNode);
            }

            if (PciDevicePath == NULL) {
                continue;
            }

            if ( ((PciDevicePath->Device == gIdeControllerLocation[1]) && \
                  (PciDevicePath->Function == gIdeControllerLocation[2])) || \
                 ((PciDevicePath->Device == gIdeControllerLocation2[1]) && \
                  (PciDevicePath->Function == gIdeControllerLocation2[2])) ) {
                Status = pBS->HandleProtocol (
                                              HandleBuffer[Index],
                                              &gEfiDiskInfoProtocolGuid,
                                              &DiskInfo
                                              );
                ASSERT_EFI_ERROR (Status);

                Status = DiskInfo->WhichIde (
                                            DiskInfo,
                                            &IdeChannel,
                                            &IdeDevice
                                            );
                if (SataMode == PCI_CL_MASS_STOR_SCL_IDE) {   // IDE MODE

                    IdeDevice = (IdeChannel * 2) + IdeDevice;

#if SECOND_CONTROLLER_COUNTS_BY_DEVICE
                    if ( (PciDevicePath->Device == gIdeControllerLocation2[1]) && \
                         (PciDevicePath->Function == gIdeControllerLocation2[2]) ) { //Port 4, 5 in SATA2
                        IdeDevice += 4;
                    }
#endif
                    if (IdeDevice == 1 || IdeDevice == 2) {   // SINDX ¡V Serial ATA Index (D31:F2)
                        IdeDevice ^= 3;                       // Port 0 = Primary Master
                    }                                         // Port 2 = Primary Slave
#if !SECOND_CONTROLLER_COUNTS_BY_DEVICE
                    if ( (PciDevicePath->Device == gIdeControllerLocation2[1]) && \
                         (PciDevicePath->Function == gIdeControllerLocation2[2]) ) { //Port 4, 5 in SATA2
                        IdeDevice += 4;
                    }
#endif
                    IdeChannel = IdeDevice;
                }                                             // SATA MODE
                Token = DevStrings[IdeChannel];

                Status = pBS->AllocatePool(EfiBootServicesData, sizeof (IDENTIFY_DATA), &IdentifyDriveInfo);
                ASSERT_EFI_ERROR (Status);

                pBS->SetMem(IdentifyDriveInfo, sizeof (IDENTIFY_DATA), 0);

                BufferSize = sizeof (IDENTIFY_DATA);
                Status = DiskInfo->Identify (
                                            DiskInfo,
                                            IdentifyDriveInfo,
                                            &BufferSize
                                            );
                ASSERT_EFI_ERROR (Status);

            } else {
                //
                // Off board
                //
                continue;
            }

            pBS->SetMem(ModelNumber, 42, 0x20);
            pBS->CopyMem (ModelNumber+2, IdentifyDriveInfo->Model_Number_27, 40);
            Swap_Entries (ModelNumber+2, 40);
            ModelNumber[42] = '\0';

            Sprintf(NewString, "%a", ModelNumber);

            InitString(
                       HiiHandle,
                       Token,
                       L"%a",
                       NewString
                       );

            if (IdentifyDriveInfo) {
                pBS->FreePool (IdentifyDriveInfo);
                IdentifyDriveInfo = NULL;
            }
        }

        if (HandleBuffer) {
            pBS->FreePool (HandleBuffer);
        }

        pBS->FreePool (NewString);
    }
}
#endif

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
