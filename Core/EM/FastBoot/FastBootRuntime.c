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

//*************************************************************************
// $Header: /Alaska/SOURCE/Modules/PTT/FastBootRuntime.c 9     7/11/13 10:17p Simonchen $
//
// $Revision: 9 $
//
// $Date: 7/11/13 10:17p $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/PTT/FastBootRuntime.c $
// 
// 9     7/11/13 10:17p Simonchen
// [TAG]  		EIP126196
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	If set two HDD password and use Raid mode, fastboot will
// fail.
// [RootCause]  	Because when AHCI driver unlock first HDD, Raid driver
// will try to read all HDD, but second HDD is still lock, so access will
// fail.
// [Solution]  	Make sure all HDD unlock then Raid can access HDD. 
// And add "Support Raid Driver" token to control fastboot support Raid
// feature or not.
// [Files]  		FastBoot.c
// FastBoot.sd
// FastBoot.sdl
// FastBootRuntime.c
// FastBoot.h
// 
// 8     4/18/13 5:39a Simonchen
// [TAG]  		EIP113454
// [Category]  	New Feature
// [Description]  	This eip is created for implement or experiment for
// Intel raid mode on fastboot.
// [Files]  		FastBoot.sdl
// FastBootRuntime.c
// FastBoot.c
// FastBoot.sd
// FastBoot.uni
// 
// 7     9/17/12 5:56a Bibbyyeh
// [TAG]           EIP100456
// [Category]      New Feature
// [Description]   If fast boot failure counter reach a
// MAX_LAST_BOOT_FAIL_COUNT, system will perform a full boot.
// [Files]         FastBoot.sdl FastBootRuntime.c
// 
// 6     8/20/12 2:22a Bibbyyeh
// [TAG]           EIP98617
// [Category]      New Feature
// [Description]   Add one token or other disable function to PTT enter
// Setup.
// [Files]         FastBoot.sdl FastBootRuntime.c
// 
// 5     8/10/12 3:25a Bibbyyeh
// [TAG]           EIP96276
// [Category]      New Feature
// [Description]   Function request for PTT_12
// EIP96276.2 Fixed USB skip table issue. 
// EIP96276.3 Add token ¡¥CONNECT_ALL_SATA_DEVICE_IN_FASTBOOT¡¦ to
// gFastBootPolicy.
// EIP96276.4 Add IsValidFBBootOptionPtr support by driver type. Exp : usb
// type skip or other type
// EIP96276.5 Add token ¡¥Test mode¡¨ to gFastBootPolicy Setup menu.
// EIP96276.6 Disable Tse Hotkey support in fastboot path.
// EIP96276.7 Modify TRACE message.
// [Files]         FastBoot.c FastBoot.sd FastBoot.sdl FastBoot.uni
// FastBootRuntime.c FastBootProtocol.c
// 
// 4     8/10/12 2:29a Bibbyyeh
// [TAG]           EIP97515
// [Category]      Improvement
// [Description]   According to the existence of user password, PTT can
// decide to skip "ProcessConInAvailability" automatically.
// [Files]         FastBoot.sdl FastBootRuntime.c
// 
// 3     6/01/12 6:55a Bibbyyeh
// [TAG]           EIP90455
// [Category]      New Feature
// [Description]   PTT improvement - fastboot policy protocol for dynamic
// control fast boot behavior.
// [Files]         FastBoot.c FastBoot.sdl FastBoot.sd FastBoot.uni
// FastBootRuntime.c FastBootTseHook.c FastBootProtocol.h FastBoot.h
// 
// 2     3/11/11 10:01p Bibbyyeh
// [TAG]		EIP54993
// [Category]	Improvement
// [Description]
// 1.Sync with Fastboot_10
// 2.Remove token "SAVE_LAST_BOOT_DEVICE_CHECKSUM"
// 3.Add token "CALL_DISPATCHER_AGAIN_IN_FASTBOOT"
// 4.Use SimpleText protocol to detect mode change hotkey instead of
// pBS->ConIn.
// 5.Simplify the code about "AMILEGACY16_FASTBOOT_SOLUTION".
// 6.Fixed a bug that SATA device can't be found if keep TSE execution on
// fastboot path.
// [Files]		PPT.cif FastBoot.sdl FastBootRuntime.c FastBootTseHook.c
// FastBoot.c FastBoot.h FastBoot.sd FastBootProtocol.cif
// FastBootProtocol.h FastBootSMI.cif FastBootSMI.sdl FastBootSMI.c
// FastBootSMI.dxs FastBootSMI.mak
// 
// 1     10/12/10 9:04a Bibbyyeh
// Initial check in
//
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:  FastBootRuntime.c
//
//  Description:
//  Implementation of callback when variable services is enabled
//
//<AMI_FHDR_END>
//*************************************************************************
//============================================================================
// Includes
//============================================================================

#include <AmiDxeLib.h>
#include <Setup.h>
#include <Protocol/Variable.h>
#include "FastBoot.h"
#include <Protocol/FastBootProtocol.h>
#include <Protocol/AmiUsbController.h>
#include <token.h>
#include <AMIVfr.h>

//============================================================================
// Define
//============================================================================

//============================================================================
// External Golbal Variable Declaration
//============================================================================

//============================================================================
// External Function Definitions
//============================================================================

//============================================================================
// Golbal Variable Declaration
//============================================================================
static EFI_GUID EfiVariableGuid = EFI_GLOBAL_VARIABLE;
static EFI_GUID FastBootVariableGuid = FAST_BOOT_VARIABLE_GUID;
static EFI_GUID FastBootPolicyGuid = FAST_BOOT_POLICY_PROTOCOL_GUID;
FAST_BOOT_POLICY    gFastBootPolicy;
#if (((USB_DRIVER_MAJOR_VER*100 ) + (USB_DRIVER_MINOR_VER*10) + (USB_DRIVER_BUILD_VER)) >= 920)
USB_SKIP_LIST DefaultSkipTable[] = USB_SKIP_TABLE;
#endif

SKIP_PCI_LIST DeafultSkipPciList[]=FAST_BOOT_PCI_SKIP_LIST;
#if SUPPORT_RAID_DRIVER
SATA_DEVICE_DATA    SataDeviceData[MAX_SATA_DEVICE_COUNT];
#endif
//============================================================================
// Function Definitions
//============================================================================

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetSataPortPresentHOB
//
// Description: Get Sata port present HOB
//
// Input:		
//  IN OUT SATA_PRESENT_HOB **SataPresentHob  
//
// Output:      EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
#if SUPPORT_RAID_DRIVER
EFI_STATUS GetSataPortPresentHOB (
  IN OUT SATA_PRESENT_HOB **SataPresentHob    
)
{
    EFI_STATUS  Status;
    VOID        *pHobList = NULL;
    EFI_GUID    guidHob = HOB_LIST_GUID;    
    EFI_GUID    SataPresentHobGuid = AMI_SATA_PRESENT_HOB_GUID;
    
    pHobList = GetEfiConfigurationTable(pST, &guidHob);
    if (!pHobList) return EFI_NOT_READY;

    *SataPresentHob = (SATA_PRESENT_HOB*)pHobList;

    while (!EFI_ERROR(Status = FindNextHobByType(EFI_HOB_TYPE_GUID_EXTENSION, SataPresentHob)))
    {
        if (guidcmp(&(*SataPresentHob)->EfiHobGuidType.Name, &SataPresentHobGuid) == 0)
            break;
    }


    if (EFI_ERROR(Status)) return EFI_NOT_FOUND;

    return  EFI_SUCCESS;
}
#endif
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   IsSataPortPresentChanged
//
// Description: Check whether Sata Port Present status is changed.
//
// Input:		
//  IN FAST_BOOT *FbVariable - Fast Boot Variable pointer
//
// Output:      BOOLEAN TRUE - Sata port present status is changed.
//                      FALSE - Sata port present status is NOT changed. 
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
#if SUPPORT_RAID_DRIVER
BOOLEAN IsSataPortPresentChanged(FAST_BOOT *FbVariable)
{
    SATA_PRESENT_HOB *pSataPresentHob;
    EFI_STATUS  Status;
    UINT8   i;
    Status = GetSataPortPresentHOB(&pSataPresentHob);
    
    if (EFI_ERROR(Status) && FbVariable->ControllerCount == 0)
    {
        TRACE((-1,"FB: Sata port present HOB is not found, need CSP porting for it\n"));
        return FALSE; //CSP didn't report Sata port present HOB, Sata support policy would not work.
    }
   
    // check whether Sata port present HOB is as same as previous boot totally.
    if(!MemCmp(&pSataPresentHob->ControllerCount,&FbVariable->ControllerCount,sizeof(SATA_PRESENT_HOB)-sizeof(EFI_HOB_GUID_TYPE)))
        return FALSE;

    TRACE((-1,"FB: Sata port present is changed\n"));
    TRACE((-1,"Current: Controller count %x\n",pSataPresentHob->ControllerCount));
    for(i=0;i<4;i++)
        TRACE((-1,"ClassCode %x,SataInfo %x\n",pSataPresentHob->SataInfo[i].ClassCode,pSataPresentHob->SataInfo[i].PresentPortBitMap));

    
    TRACE((-1,"Last: Controller count %x\n",FbVariable->ControllerCount));
    for(i=0;i<4;i++)
        TRACE((-1,"ClassCode %x,SataInfo %x\n",FbVariable->SataInfo[i].ClassCode,FbVariable->SataInfo[i].PresentPortBitMap));


    return TRUE;
}
#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SetDefaultFastBootPolicy
//
// Description: Fill default Fast Boot Plicy 
//
// Input:		
//  IN SETUP_DATA *SetupData - pointer to SetupData
//  IN FAST_BOOT *FbVariable - pointer to FastBoot variable
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID SetDefaultFastBootPolicy(SETUP_DATA *SetupData,FAST_BOOT *FbVariable)
{
    EFI_STATUS  Status;
    UINT8 *BootOption = NULL;
    UINTN Size = 0;
    AMITSESETUP AmiTseData;    
    EFI_GUID AmiTseSetupGuid = AMITSESETUP_GUID;
    UINTN    VariableSize = 0;
#if SUPPORT_RAID_DRIVER	
    SATA_PRESENT_HOB *pSataPresentHob = NULL;
#endif

    gFastBootPolicy.TestMode = SetupData->FbTestMode;   //(EIP96276.5)    

    //
    //Informatoin for pervious boot
    //
    gFastBootPolicy.UEfiBoot = FbVariable->BootType;
    gFastBootPolicy.BootOptionNumber = FbVariable->BootOptionNumber;
    gFastBootPolicy.CheckBootOptionNumber = TRUE;
    gFastBootPolicy.DevStrCheckSum = FbVariable->DevStrCheckSum;    
    gFastBootPolicy.CheckDevStrCheckSum = TRUE;
    gFastBootPolicy.BootCount = FbVariable->BootCount;

    Status = GetEfiVariable(L"FastBootOption", &FastBootVariableGuid, NULL, &Size, &BootOption);         
    gFastBootPolicy.FastBootOption = (EFI_DEVICE_PATH_PROTOCOL*)BootOption;
#if SUPPORT_RAID_DRIVER
    MemCpy(SataDeviceData,FbVariable->SataDevice,sizeof(SATA_DEVICE_DATA)*MAX_SATA_DEVICE_COUNT);
    gFastBootPolicy.SataDevice = SataDeviceData;
#endif
    //
    //Config Behavior in fastboot path
    //
    gFastBootPolicy.SataSupport = SetupData->FbSata;   
    gFastBootPolicy.VGASupport = SetupData->FbVga;
    
    gFastBootPolicy.UsbSupport = SetupData->FbUsb;    
#if (((USB_DRIVER_MAJOR_VER*100 ) + (USB_DRIVER_MINOR_VER*10) + (USB_DRIVER_BUILD_VER)) >= 920)    
    gFastBootPolicy.UsbSkipTable = DefaultSkipTable;    
    gFastBootPolicy.UsbSkipTableSize = sizeof(DefaultSkipTable)/sizeof(USB_SKIP_LIST);  //(EIP96276.2)
#endif

    gFastBootPolicy.Ps2Support = SetupData->FbPs2;
    gFastBootPolicy.NetWorkStackSupport = SetupData->FbNetWrokStack;

    gFastBootPolicy.SkipPciList = DeafultSkipPciList;
    gFastBootPolicy.SkipPciListSize = sizeof(DeafultSkipPciList);
    gFastBootPolicy.SkipTSEHandshake = SKIP_TSE_HANDSHAKE;
    gFastBootPolicy.FirstFastBootInS4 = ALLOW_FIRST_FASTBOOT_IN_S4;
//    gFastBootPolicy.ConnectAllSata = CONNECT_ALL_SATA_DEVICE_IN_FASTBOOT;   //(EIP113454)-
    
    //
    //Check User and Amdin password
    //
    VariableSize = sizeof(AMITSESETUP);
    Status = pRS->GetVariable ( L"AMITSESetup", \
    	                        &AmiTseSetupGuid, \
    	                        NULL, \
    	                        &VariableSize, \
    	                        &AmiTseData );    

    if (!EFI_ERROR(Status)) {   
        if (AmiTseData.UserPassword[0] != 0) {
            TRACE((-1,"FB: User PW is set\n"));
            //user password is set
            gFastBootPolicy.CheckPassword = TRUE;
        }
        
        if (AmiTseData.AdminPassword[0] != 0) {
            TRACE((-1,"FB: Admin PW is set\n"));                        
            //Admin password is set, don't do anything now.
        }        	
    }

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   FastBootGetVarCallback
//
// Description: FastBoot runtime callback
//
// Input:		
//  IN EFI_EVENT Event - Callback event
//  IN VOID *Context - pointer to calling context
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID FastBootGetVarCallback(
    IN EFI_EVENT Event, 
    IN VOID *Context
)
{
    EFI_STATUS Status;
    UINT32 Variable = 0;
    FAST_BOOT FbVariable;
    UINTN Size = sizeof(SETUP_DATA);
    static EFI_GUID SetupVariableGuid = SETUP_GUID;
    SETUP_DATA SetupData;
    EFI_HANDLE  Handle = NULL;

    static UINT32 BootFlow = BOOT_FLOW_CONDITION_FIRST_BOOT;
    static EFI_GUID guidBootFlow = BOOT_FLOW_VARIABLE_GUID;

    //Initial fast boot policy 
    
    pBS->SetMem(&gFastBootPolicy,sizeof(FAST_BOOT_POLICY),0);
    
    Status=pBS->InstallProtocolInterface(
                                &Handle, 
                                &FastBootPolicyGuid, 
                                EFI_NATIVE_INTERFACE,
                                &gFastBootPolicy
                                );   
    ASSERT(!EFI_ERROR(Status));

	Status = pRS->GetVariable(L"Setup", &SetupVariableGuid, NULL, &Size, &SetupData);
	if (EFI_ERROR(Status) || SetupData.FastBoot == 0) 
        gFastBootPolicy.FastBootEnable = FALSE;
    else if (SetupData.FastBoot == 1)
        gFastBootPolicy.FastBootEnable = TRUE;

    Size = sizeof(FbVariable);
    Status = pRS->GetVariable(L"LastBoot", &FastBootVariableGuid, NULL, &Size, (VOID *)&FbVariable);
    if(EFI_ERROR(Status))
        gFastBootPolicy.LastBootVarPresence = FALSE;
    else 
        gFastBootPolicy.LastBootVarPresence = TRUE;
    
    SetDefaultFastBootPolicy(&SetupData,&FbVariable);

#if SUPPORT_RAID_DRIVER
    if(gFastBootPolicy.LastBootVarPresence == TRUE && IsSataPortPresentChanged(&FbVariable))
    {
        pRS->SetVariable(L"LastBoot", 
                         &FastBootVariableGuid,
                         EFI_VARIABLE_NON_VOLATILE,
                         0,
                         &Variable);

        gFastBootPolicy.LastBootVarPresence = FALSE;

    }
#endif


    if (gFastBootPolicy.FastBootEnable == FALSE ||gFastBootPolicy.LastBootVarPresence == FALSE)
        return;    

                                        //(EIP98617)>>

    Size = sizeof(UINT32);
    Status = pRS->GetVariable(L"LastBootFailed", &FastBootVariableGuid, NULL, &Size, &Variable);
    if(EFI_ERROR(Status)) {
        Variable = 0x55aa55aa;
        Status = pRS->SetVariable(L"LastBootFailed", 
                                  &FastBootVariableGuid, 
                                  EFI_VARIABLE_NON_VOLATILE |
                                  EFI_VARIABLE_BOOTSERVICE_ACCESS |
                                  EFI_VARIABLE_RUNTIME_ACCESS,
                                  Size,
                                  &Variable);
    } else {
#if LAST_BOOT_FAIL_MECHANISM    
        //reset LastBootFailed variable
        Status = pRS->SetVariable(L"LastBootFailed", 
                                  &FastBootVariableGuid, 
                                  EFI_VARIABLE_NON_VOLATILE,
                                  0,
                                  &Variable);
        //force setup
        Status = pRS->SetVariable(L"BootFlow", 
                                  &guidBootFlow, 
                                  EFI_VARIABLE_BOOTSERVICE_ACCESS,
                                  sizeof(BootFlow),
                                  &BootFlow);

        gFastBootPolicy.LastBootFailure = TRUE;
#else
        //check the fail count, if reach max count then perform a full boot
        if (Variable == 0x55aa55aa) 
            Variable = 0x01;
        else
            Variable++;

        if (Variable == MAX_LAST_BOOT_FAIL_COUNT) {

            pRS->SetVariable(L"LastBoot", 
                             &FastBootVariableGuid,
                             EFI_VARIABLE_NON_VOLATILE,
                             0,
                             &FbVariable);

            gFastBootPolicy.LastBootVarPresence = FALSE;

            Variable = 0x55aa55aa;
        }

        Status = pRS->SetVariable(L"LastBootFailed", 
                                  &FastBootVariableGuid, 
                                  EFI_VARIABLE_NON_VOLATILE |
                                  EFI_VARIABLE_BOOTSERVICE_ACCESS |
                                  EFI_VARIABLE_RUNTIME_ACCESS,
                                  Size,
                                  &Variable);
#endif
    }

                                        //<<(EIP98617)
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   FastBootEntry
//
// Description: FastBoot runtime callback entry point
//
// Input:		
//  IN EFI_HANDLE ImageHandle - Image handle
//  IN EFI_SYSTEM_TABLE *SystemTable - pointer to system table
//
// Output:      EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS FastBootEntry(
	IN EFI_HANDLE ImageHandle,
	IN EFI_SYSTEM_TABLE *SystemTable
)
{
    EFI_EVENT Event;
    VOID *Registration;
    static EFI_GUID VariableArchProtocolGuid = EFI_VARIABLE_ARCH_PROTOCOL_GUID;

    RegisterProtocolCallback(&VariableArchProtocolGuid, FastBootGetVarCallback, NULL, &Event, &Registration);
    return EFI_SUCCESS;   
}

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
