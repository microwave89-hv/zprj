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
// $Header: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/CRB/CRBTse.c 1     3/17/14 2:36a Chaseliu $Revision:
//
// $Date: 3/17/14 2:36a $Log:
// 
//*************************************************************************
#include "Efi.h"
#include "token.h"
#include <AmiLib.h>
#include <AmiDxeLib.h>
#include "Protocol\PciIo.h"
#include "Protocol\DevicePath.h"
#include "protocol\DriverBinding.h"
#include "protocol\BlockIo.h"
#include "Protocol\PDiskInfo.h"
#include "Protocol\PIDEController.h"
#include "Protocol\PIDEBus.h"
#include "Protocol\PAhciBus.h"
#include "Protocol\PIDEBus.h"
#include <Setup.h>


#define     SecurityEnabledMask         0x0002


EFI_RUNTIME_SERVICES  *gRT;
EFI_BOOT_SERVICES     *gBS;

UINT8   Satamode=0;
UINT8   GetVariableError=0;

// Produced Protocols

// Consumed Protocols

//---------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//---------------------------------------------------------------------------
// Constant Definition(s)

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetSetupSataMode
//
// Description: Gets the sata mode before entering Setup and Store in Satamode.
//              Global Variable.
//
// Input:       VOID
//
// Output:      VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
GetSetupSataMode( )
{

    UINT32      SetupDataAttributes = 0;
    UINTN       SetupDataSize = sizeof(SETUP_DATA);
    SETUP_DATA  SetupData;
    EFI_GUID    gSetupGuid = SETUP_GUID;
    EFI_STATUS  Status;

    Status = gRT->GetVariable(L"Setup", &gSetupGuid, &SetupDataAttributes,
                                &SetupDataSize, &SetupData);

    if(EFI_ERROR(Status)){
        GetVariableError = 1;
        return;
    }
    //
    // Store the SataMode before going to setup.
    //    
    Satamode = SetupData.SataInterfaceMode;

    return;

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   IssueColdReset
//
// Description: Issues cold reset.
//
// Input:       VOID
//
// Output:      VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
IssueColdReset( )
{
    IoWrite8(0xcf9, 0xE);
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CheckForChangeinSataMode
//
// Description: Gets the sata mode when exiting and resetting from
//              setup and checks whether sata mode is changed. If changed it
//              issues cold reset. Satamode(Value got before entering setup) is 
//              Stored in Satamode_Before_Setup.
//
// Input:       VOID
//
// Output:      VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
CheckForChangeinSataMode( )
{

    UINT32      SetupDataAttributes = 0;
    UINTN       SetupDataSize = sizeof(SETUP_DATA);
    EFI_GUID    gSetupGuid = SETUP_GUID;
    UINTN       Count;
    EFI_HANDLE  *HandleBuffer = NULL;
    UINT16      SecurityStatus = 0;
    EFI_STATUS  Status;
    UINT8       i;
    IDE_SECURITY_PROTOCOL *Security = NULL;
    EFI_GUID    gIDESecurityProtocolGuid    = IDE_SECURITY_INTERFACE_GUID;
    UINT8       Satamode_Before_Setup = Satamode;

    
    if(GetVariableError) {
        return;
    }

    //
    // Get the Setupdata.
    //
    GetSetupSataMode();
    
    //
    // Check for change in the satamode selection in  setup.if yes, issue cold reset.
    //
    if( Satamode_Before_Setup != Satamode) {
        //
        // Check all HDD, if Password is installed in anyone of the HDD, issue cold reset.
        //
        Status = gBS->LocateHandleBuffer(ByProtocol,
                                         &gIDESecurityProtocolGuid,
                                         NULL,
                                         &Count,
                                         &HandleBuffer);

        if(EFI_ERROR(Status)) {
            return;
        }

        for(i = 0; i < Count; i++) {

            Status = gBS->HandleProtocol(HandleBuffer[i], &gIDESecurityProtocolGuid, &Security);
            if(EFI_ERROR(Status)) {
                return;
            }

            //
            // Get the security status of the device, to check whether password is installed.
            //
            Status = Security->ReturnSecurityStatus( Security, &SecurityStatus );
            if(EFI_ERROR(Status)) {
                return;
            }

            if( SecurityStatus & SecurityEnabledMask ) {
                //
                // Issue Cold Reset.
                //
                IssueColdReset();
            }
        }

        gBS->FreePool(HandleBuffer);
    }

    return;
}

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
