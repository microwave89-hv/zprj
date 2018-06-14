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
// $Header: /Alaska/SOURCE/Modules/HddSecurity/IdeSecuritySetup.c 4     4/25/13 9:22a Kapilporwal $
//
// $Revision: 4 $
//
// $Date: 4/25/13 9:22a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/HddSecurity/IdeSecuritySetup.c $
// 
// 4     4/25/13 9:22a Kapilporwal
// [TAG]  		EIP108583
// [Category]  	New Feature
// [Description]  	support set HDD password in same page
// [Files]  		IdeSecurity.cif, IdeSecurity.mak, IdeSecurity.sdl,
// IdeSecurity.uni, IdeSecurityCommon.sd, IdeSecuritySetup.c,
// HddPassword.c, HddPassword.h, HddPassword.mak, HddPassword.sdl
// 
// 3     1/15/10 10:22a Yul
// Coding Standard
//
// 2     12/09/09 12:18p Krishnakumarg
// EIP 31797 : IDE Security API documentation. Added comments whereever
// possible and modified files for coding standard
//
// 1     28/02/08 6:40p Anandakrishnanl
// Created new HddSecurity module.  Isolated IdeSecurity and IdeSmm from
// IdeBus driver to be compatable with the AHCI Bus driver.
//
//
//
//**********************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:        IdeSecuritySetup.c
//
// Description: Ide Security Setup Routines
//
// NOTE: Use this hook to dynamically change Ide Security Driver Setup screen
// Strings.
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include <AmiLib.h>
#include <AmiDxeLib.h>
#include <Setup.h>
#include <SetupStrTokens.h>
#if defined(SECUITY_SETUP_ON_SAME_PAGE) && SECUITY_SETUP_ON_SAME_PAGE
#include "Protocol\PciIo.h"
#include "Protocol\BlockIo.h"
#include "Protocol\PDiskInfo.h"
#include "Protocol\PIDEController.h"
#include "Protocol\PIDEBus.h"
#include "Protocol\PAhciBus.h"
#include "Protocol\DevicePath.h"
#include "Protocol\HiiString.h"
#endif

#if defined(SECUITY_SETUP_ON_SAME_PAGE) && SECUITY_SETUP_ON_SAME_PAGE

EFI_GUID   gDiskInfoProtocolGuid       = EFI_DISK_INFO_PROTOCOL_GUID;
EFI_GUID   gDevicePathProtocolGuid     = EFI_DEVICE_PATH_PROTOCOL_GUID;  
EFI_GUID   gIDESecurityProtocolGuid    = IDE_SECURITY_INTERFACE_GUID;

// Store the names of HDDs present in the system. Dynamically updated.
STRING_REF gHddSecurityName[6] =
{
    STRING_TOKEN(STR_SECURITY_HDD_ONE), STRING_TOKEN(STR_SECURITY_HDD_TWO),
    STRING_TOKEN(STR_SECURITY_HDD_THREE), STRING_TOKEN(STR_SECURITY_HDD_FOUR),
    STRING_TOKEN(STR_SECURITY_HDD_FIVE), STRING_TOKEN(STR_SECURITY_HDD_SIX)
};

static EFI_HII_STRING_PROTOCOL *HiiString      = NULL;
static EFI_GUID                EfiVariableGuid = EFI_GLOBAL_VARIABLE;

// Function Definitions

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CheckSecurityStatus
//
// Description: return the Security Status Information
//
// Input:       IN IDE_SECURITY_PROTOCOL *IDEPasswordSecurity,
//              IN OUT BOOLEAN               *ReqStatus,
//              IN UINT16                Mask
//
// Output:      BOOLEAN      status in ReqStatus is valid
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN CheckSecurityStatus(
    IN IDE_SECURITY_PROTOCOL *IDEPasswordSecurity,
    IN OUT BOOLEAN               *ReqStatus,
    IN UINT16                Mask )
{
    UINT16     SecurityStatus = 0;
    EFI_STATUS Status;

    //
    //get the security status of the device
    //
    Status = IDEPasswordSecurity->ReturnSecurityStatus( IDEPasswordSecurity, &SecurityStatus );

    if ( EFI_ERROR( Status ))
        return FALSE; // Unable to get IDE security status
    // Mask security status based on supplied mask data
    *ReqStatus = (BOOLEAN)((SecurityStatus & Mask) ? TRUE : FALSE );
    return TRUE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   HiiGetString
//
// Description: return the String based on StringId
//
// Input:       IN EFI_HII_HANDLE  HiiHandle,
//              IN EFI_STRING_ID   StringId,
//
// Output:      EFI_STRING
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STRING HiiGetString(
    IN EFI_HII_HANDLE  HiiHandle,
    IN EFI_STRING_ID   StringId)
{
    EFI_STRING String = NULL;
    UINTN StringSize = 0;
    EFI_STATUS Status;
    CHAR8* PlatformLang = NULL;
    UINTN Size = 0;

    if(HiiString == NULL) {
        Status = pBS->LocateProtocol(&gEfiHiiStringProtocolGuid, NULL, (VOID **) &HiiString);
        if(EFI_ERROR(Status))
            return NULL;
    }

//language not provided - try platform language
    Status = GetEfiVariable(L"PlatformLang", &EfiVariableGuid, NULL, &Size, &PlatformLang);
    if(!EFI_ERROR(Status)) {
        Status = HiiString->GetString(HiiString, PlatformLang, HiiHandle, StringId, String, &StringSize, NULL);
        if(Status == EFI_BUFFER_TOO_SMALL) {
            Status = pBS->AllocatePool(EfiBootServicesData, StringSize, &String);
            if(!EFI_ERROR(Status))
                Status = HiiString->GetString(HiiString, PlatformLang, HiiHandle, StringId, String, &StringSize, NULL);
        }
        pBS->FreePool(PlatformLang);
    }
    return (EFI_ERROR(Status)) ? NULL : String;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   HddPasswordGetDeviceName
//
// Description: Return the Drive String Name
//
// Input:   IN EFI_HANDLE Controller - the handle of the drive
//          OUT CHAR16 **wsName - Pointer to the drive string
//
// Output:  BOOLEAN - TRUE - drive string has been found and is in wsName
//                  - FALSE - drive string has not been found
//
//  Notes: it is the caller's responsibility to deallocate the space used for
//      wsName
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN HddPasswordGetDeviceName(IN EFI_HANDLE Controller, OUT CHAR16 **wsName)
{
    EFI_STATUS Status;
    SECURITY_PROTOCOL *Security = NULL;
    CHAR16 *DeviceName;
    BOOLEAN ReturnStatus = FALSE;

    // Get the SECURITY_PROTOCOL (actually getting the IDE_SECURITY_PROTOCOL, but
    //  the SECURITY_PROTOCOL is an extended version with more information)
    Status = pBS->HandleProtocol(Controller, &gIDESecurityProtocolGuid, &Security);
    if ( !EFI_ERROR(Status) ) {
        // Check the SATA controller operating mode, and based on the mode, get the UnicodeString
        //  name of the device
        if ( Security->ModeFlag ) {
            DeviceName = ((SATA_DEVICE_INTERFACE*)Security->BusInterface)->UDeviceName->UnicodeString;
        } else {
            DeviceName = ((IDE_BUS_PROTOCOL*)Security->BusInterface)->IdeDevice.UDeviceName->UnicodeString;
        }

        // Allocate space to copy the unicode device name string
        *wsName = MallocZ(sizeof(CHAR16)*(Wcslen(DeviceName)+1));
        if ( *wsName!=NULL ) {
              Wcscpy( *wsName, DeviceName);
            ReturnStatus = TRUE;
        }
    }

    // Return true to signify that a device name was discovered
    return ReturnStatus;
}

#endif

// Function Definitions


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   InitIdeSecurityStrings
//
// Description: This function initializes the IdeSecurity setup option values
//
// Input:       HiiHandle   Handle to HII database
//              Class       Indicates the setup class
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID InitIdeSecurityStrings(
    EFI_HII_HANDLE HiiHandle,
    UINT16         Class )
{
#if defined(SECUITY_SETUP_ON_SAME_PAGE) && SECUITY_SETUP_ON_SAME_PAGE
    EFI_STATUS                      Status;
    EFI_HANDLE                      *HandleBuffer = NULL;
    UINT16                          i, HDDCount = 0;
    UINTN                           Count;
    CHAR16                          * Name, *Temp1;
    BOOLEAN                         Locked;
    IDE_SECURITY_PROTOCOL           *IDEPasswordSecurity = NULL;
    EFI_DEVICE_PATH_PROTOCOL        *DevicePath;
    EFI_DEVICE_PATH_PROTOCOL        *DevicePathNode;
    PCI_DEVICE_PATH                 *PciDevicePath;
    SECURITY_PROTOCOL               *Security = NULL;
    UINT32                          HddPortNumber;
    CHAR16                          *Buff=L"P";
    EFI_DISK_INFO_PROTOCOL          *DiskInfoPtr=NULL;
    UINT32                          PortNumber;
    UINT32                          PMPortNumber;
    BOOLEAN                         Flag = FALSE;

    // Locate all handles with IDE_SECURITY_PROTOCOL installled
    Status = pBS->LocateHandleBuffer(   ByProtocol,
                                        &gIDESecurityProtocolGuid,
                                        NULL,
                                        &Count,
                                        &HandleBuffer);
    if ( EFI_ERROR( Status )) {
        return;
    }

    // For each handle in HandleBuffer
    for ( i = 0; i < Count; i++ ) {
        //
        // Get the PasswordSecurity Protocol
        //
        Status = pBS->OpenProtocol( HandleBuffer[i],
                                    &gIDESecurityProtocolGuid,
                                    (VOID**) &IDEPasswordSecurity,
                                    NULL,
                                    HandleBuffer[i],
                                    EFI_OPEN_PROTOCOL_GET_PROTOCOL);
        if ( EFI_ERROR( Status ))
            continue;
        //
        // Get the DiskInfo Protocol
        //   
        Status = pBS->OpenProtocol( HandleBuffer[i],
                                    &gDiskInfoProtocolGuid,
                                    (VOID**) &DiskInfoPtr,
                                    NULL,
                                    HandleBuffer[i],
                                    EFI_OPEN_PROTOCOL_GET_PROTOCOL);
        if ( EFI_ERROR( Status )){
            continue;
        }
        //
        // Locate the device path Protocol
        //
        Status = pBS->OpenProtocol( HandleBuffer[i],
                                    &gDevicePathProtocolGuid,
                                    (VOID**)&DevicePath,
                                    NULL,
                                    HandleBuffer[i],
                                    EFI_OPEN_PROTOCOL_GET_PROTOCOL);
        if ( EFI_ERROR( Status )){
            continue;
        }

        DevicePathNode = DevicePath;

        //
        // Traverse the Device Path structure till we reach HARDWARE_DEVICE_PATH
        //
        while (!isEndNode (DevicePathNode)) {

            if ((DevicePathNode->Type == HARDWARE_DEVICE_PATH) &&
                (DevicePathNode->SubType == HW_PCI_DP)){

                PciDevicePath = (PCI_DEVICE_PATH *) DevicePathNode;
                break;
            }

            DevicePathNode = NEXT_NODE (DevicePathNode);
        }
        // Check whether valid DevicePath found
        if (PciDevicePath == NULL) continue;

        Security=(SECURITY_PROTOCOL *)IDEPasswordSecurity;

        if(Security->ModeFlag){
            //
            //  Controller is in Ahci Mode, Call WhichIde function to find out Port Number
            //
            DiskInfoPtr->WhichIde(DiskInfoPtr,&PortNumber,&PMPortNumber);
            //
            //  Assign the PortNumber to HddPortNumber.This Port Number is displayed in Setup.
            //  
            HddPortNumber=PortNumber;
            Flag=TRUE;

        }else{

#ifdef SB_TEMPLATE_VER
#if SB_TEMPLATE_VER > 6
{
            UINT32      IdeChannel;
            UINT32      IdeDevice;

            if(gSbHddPolicyPtr==NULL){
                Status=gBS->LocateProtocol(&gSbHddPolicyProtocolGuid,
                                            NULL, \
                                            &gSbHddPolicyPtr);
            }

            if(gSbHddPolicyPtr!=NULL){

                //
                //  Find out the Primary/Secondary,Master/Slave Info from WhichIde function  
                //
                DiskInfoPtr->WhichIde(DiskInfoPtr,&IdeChannel,&IdeDevice);
                //
                //  Get the Port Number to which the HDD is connected
                //
                gSbHddPolicyPtr->GeneratePortNumber(PciDevicePath->Device,PciDevicePath->Function,
                                                    IdeChannel,IdeDevice,&PortNumber);

                HddPortNumber=PortNumber;
                Flag=TRUE;

            }else{
                //
                // SB HDD Policy Protocol is not Present. 
                //
                Flag=FALSE;
            }
}
#endif
#endif
            
        }

        if ( CheckSecurityStatus( IDEPasswordSecurity, &Locked, 0x0004 )) {
            if ( HddPasswordGetDeviceName( HandleBuffer[i], &Name )) {
                Name[12] = 0;
                if(Flag){
                    //
                    //  Display the the Port Number in Setup
                    // 
                    InitString(HiiHandle, gHddSecurityName[i], L"%s%d:%s", L"P", HddPortNumber, Name);     
                }else{
                    //
                    //  If SB HDD Policy Protocol is not Installed Use STR_IDE_SECURITY_PROMPT
                    //  token to display the String Information.
                    //
                    Temp1 = HiiGetString( HiiHandle, STRING_TOKEN( STR_IDE_SECURITY_PROMPT ));
                    InitString(HiiHandle, gHddSecurityName[i], L"%s%d:%s",Temp1,HDDCount,Name);
                }
            } else {
                if(Flag){
                    //
                    //  Display the the Port Number in Setup
                    //   
                    InitString(HiiHandle, gHddSecurityName[i], L"%s%d", L"P", HddPortNumber);     
                }else{
                    //
                    //  If SB HDD Policy Protocol is not Installed Use STR_IDE_SECURITY_PROMPT
                    //  token to display the String Information.
                    //
                    Temp1 = HiiGetString( HiiHandle, STRING_TOKEN( STR_IDE_SECURITY_PROMPT ));
                    InitString(HiiHandle, gHddSecurityName[i], L"%s%d", Temp1, HDDCount);
                }
            }
            HDDCount++;
         }// end if

    }// end of for   
#endif
    return;
}

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
