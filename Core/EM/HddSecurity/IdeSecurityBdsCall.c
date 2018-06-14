//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.            **
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
// $Header: /Alaska/SOURCE/Modules/HddSecurity/IdeSecurityBdsCall.c 2     6/09/14 9:53a Anbuprakashp $
//
// $Revision: 2 $
//
// $Date: 6/09/14 9:53a $
//
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/HddSecurity/IdeSecurityBdsCall.c $
// 
// 2     6/09/14 9:53a Anbuprakashp
// [TAG]  		EIP 172443  
// [Category]  	Improvement
// [Description]  	"RaidDriverBlockingStatus" is using
// gEfiGlobalVariableGuid that violates UEFI 2.4 spec in
// IdeSecurityBdsCall.c and Runtime attribute set of this variable need to
// be removed
// [Files]  		IdeSecurityBdsCall.c, AhciBus.c
// 
// 1     6/06/13 4:03a Rameshr
// [TAG]  		EIP106423
// [Category]  	Improvement
// [Description]  	HddPassword Support in UEFI Raid and Legacy Raid. And
// also taken care where there is no Conin Device avilable in the post
// [Files]  		IdeSecurity.cif
// IdeSecurity.sdl
// IdeSecurity.mak
// IdeSecurity.h
// IdeSecurity.c
// IdeSecuritySetup.c
// IdeSecurityBdsCall.c
// IdeSecurity.sd
// IdeSecurity.uni
// IdeSecurity.dxs
// IdeSecurity.chm
//
// 
//*************************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:        IdeSecurityBdsCall.c
//
// Description: This function will connect the handle's of RAID Controllers and
//  the IDE/AHCI Devices( the handle whose DiskIo was not opened by any one.)
//
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>


#include <PCI.h>
#include "Protocol\DiskIo.h"
#include <Protocol\IdeControllerInit.h>
#include <AmiDxeLib.h>
#include <Protocol\DevicePath.h>

static EFI_GUID  gAmiGlobalVariableGuid          = AMI_GLOBAL_VARIABLE_GUID;


extern EFI_STATUS GetPciHandlesByClass(
    UINT8 Class, UINT8 SubClass, UINTN *NumberOfHandles, EFI_HANDLE **HandleBuffer
);

// <AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name: IdeConnectControllerAfterConnectEverthing
//
// Description:
//  This function will connect the handle's of RAID Controllers and the IDE/AHCI
//  Devices( the handle whose DiskIo was not opened by any one.)
//
// Input:
//  VOID
//
// Output:
//  VOID  
//
// Modified:
//
// Referrals:
//
//
// Notes:
// If Conin Devices are not Present, RAID Option ROM will not be launched 
// by CSM BlockIo as RegisterHddNotification fucntion would get control after
// connectEverything() is called from BDS. Rather it would be launched by
// ShadowAllLegacyOproms() and UEFI Boot option for RAID will not be formed as
// blockIo will not be installed by csm BlockIo driver. So Connect the RAID handle
// so that CSM BlockIo starts. And also if Password is installed the above said case
// will happen when no con in device is present.
//
// Check for any device in IDE/AHCI mode not unlocked when no ConIn Device is not present.
// If found Connecting that Device using ConnectController() after the Device is unlocked.
// as read would fail and FileSystem would not be formedOpen gEfiIdeControllerInitProtocolGuid
// which will be installed on each controller. This will be opened as
// EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER by each device handle.Connect that Handle where
// DiskIo will be installed and not opened by another driver.
//
//--------------------------------------------------------------------------- 
// <AMI_PHDR_END>

VOID IdeConnectControllerAfterConnectEverthing( ) 
{

    UINT8               Index;
    UINT8               Index1;
    UINTN               DiskIoCount;
    UINTN               Count;
    UINTN               Count1;
    EFI_HANDLE          *HandleBuffer = NULL;
    UINTN               NumHandles;
    EFI_STATUS          Status;
    EFI_OPEN_PROTOCOL_INFORMATION_ENTRY *DiskIoEntries = NULL;
    EFI_OPEN_PROTOCOL_INFORMATION_ENTRY *Entries = NULL;
    BOOLEAN             RaidDriverBlocked=FALSE;
    UINTN               VarSize=sizeof(RaidDriverBlocked);

    

    // If Conin Devices are not Present, RAID Option ROM will not be launched 
    // by CSM BlockIo as RegisterHddNotification fucntion would get control after
    // connectEverything() is called from BDS. Rather it would be launched by
    // ShadowAllLegacyOproms() and UEFI Boot option for RAID will not be formed as
    // blockIo will not be installed by csm BlockIo driver. So Connect the RAID handle
    // so that CSM BlockIo starts. And also if Password is installed the above said case
    // will happen when no con in device is present.

    Status = GetPciHandlesByClass(PCI_CL_MASS_STOR,
                                        PCI_CL_MASS_STOR_SCL_RAID,
                                        &NumHandles,
                                        &HandleBuffer
                                        );

    // Connect the handle so that CSM BlockIo Launches RAID Option Rom.
    if(!EFI_ERROR(Status)){

        Status = pRS->GetVariable( L"RaidDriverBlockingStatus",
                                   &gAmiGlobalVariableGuid,
                                   NULL,
                                   &VarSize,
                                   &RaidDriverBlocked );


        if((EFI_ERROR(Status)) || (RaidDriverBlocked == FALSE)) {
            return;
        }
        
        for(Index=0; Index<NumHandles; Index++){

            // We have blocked the Raid driver until password verification is done. 
            // Now we need to un block and connect the Raid driver after HddPassword verification is done 
            Status = pBS->OpenProtocolInformation(HandleBuffer[Index], 
                                                &gEfiDevicePathProtocolGuid, 
                                                &Entries, 
                                                &Count1
                                                );

            if(!EFI_ERROR(Status)) {
                for(Index1=0; Index1 < Count1; Index1++) { 
                    if (Entries[Index1].Attributes!=EFI_OPEN_PROTOCOL_BY_DRIVER) {
                        continue;                    
                    }

                    Status = pBS->CloseProtocol (
                                    HandleBuffer[Index],
                                    &gEfiDevicePathProtocolGuid,
                                    Entries[Index1].AgentHandle,
                                    Entries[Index1].ControllerHandle
                                    );
                }
            }

            pBS->ConnectController(HandleBuffer[Index],NULL,NULL,TRUE);
        }

    } else {

        // Check for any device in IDE/AHCI mode not unlocked when no ConIn Device is not present.
        // If found Connecting that Device using ConnectController() after the Device is unlocked.
        // Open gEfiIdeControllerInitProtocolGuid which will be installed on each controller.
        // This will be opened as EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER by each device handle.
        // Connect that Handle where DiskIo will be installed and not opened by another driver.

        Status = pBS->LocateHandleBuffer(ByProtocol,
	                    &gEfiIdeControllerInitProtocolGuid,
	                    NULL,
	                    &Count,
	                    &HandleBuffer);

    	if(!EFI_ERROR(Status)){
            for(Index=0; Index < Count; Index++) {
                Status = pBS->OpenProtocolInformation(HandleBuffer[Index], 
                                                    &gEfiIdeControllerInitProtocolGuid, 
                                                    &Entries, 
                                                    &Count1
                                                    );
                if(!EFI_ERROR(Status)) {
                    for(Index1=0; Index1 < Count1; Index1++) { 
                        if (Entries[Index1].Attributes!=EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER) {
                            continue;                    
                        }                    
                        Status = pBS->OpenProtocolInformation(Entries[Index1].ControllerHandle, 
                                                    &gEfiDiskIoProtocolGuid, 
                                                    &DiskIoEntries, 
                                                    &DiskIoCount
                                                    );		                    
                        if(!EFI_ERROR(Status)) {        
                            if( DiskIoCount == 0 ) {
                                Status = pBS->ConnectController(Entries[Index1].ControllerHandle,
                                                            NULL,
                                                            NULL,
                                                            TRUE);			
                            }
                            pBS->FreePool(DiskIoEntries);
                        }
                    }
                    pBS->FreePool(Entries);
                }
            }
    	}
    }

    if(HandleBuffer) {
        pBS->FreePool(HandleBuffer);
    }

    return;
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
