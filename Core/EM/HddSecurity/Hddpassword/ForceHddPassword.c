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
// $Header: /Alaska/SOURCE/Modules/HddSecurity/HddPassword/ForceHddPassword.c 2     10/11/10 6:19p Krishnakumarg $
//
// $Revision: 2 $
//
// $Date: 10/11/10 6:19p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/HddSecurity/HddPassword/ForceHddPassword.c $
// 
// 2     10/11/10 6:19p Krishnakumarg
// [TAG] - EIP 45593
// [Category] - IMPROVEMENT
// [Severity] - Minor
// [Symptom]  - Build Errors in ForceHDDPassword.c on new core 4.6.4.1
// label
// [RootCause]- IDE_CONTROLLER_PROTOCOL structure defined header not
// included
// [Solution] - Include the respective header(PIDEController.h)
// [Files] - ForceHddPassword.c
// 
// 1     8/19/10 2:44a Rameshr
// Issue:Need do HDD PSW reset when warmboot
// EIP 40528
//
//
//**********************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:        ForceHddPassword.c
//
// Description: Send Disable Software Preservation command when the 
//              FORCE_HDD_PASSWORD_PROMPT token is set to 1
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

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


EFI_RUNTIME_SERVICES  *gRT;
EFI_BOOT_SERVICES     *gBS;

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   DisableSoftwarePreservation
//
// Description: Send the Disable software Preservation 
//
// Input:       None
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
DisableSoftwarePreservation ( )
{
#if FORCE_HDD_PASSWORD_PROMPT
    UINTN               HandleCount;
    EFI_HANDLE          *HandleBuffer;
    UINT8               i;
    AHCI_BUS_PROTOCOL   *AhciBusInterface;
    EFI_GUID gEfiAhciBusProtocolGuid = AHCI_BUS_INIT_PROTOCOL_GUID;
    SATA_DEVICE_INTERFACE   *SataDeviceInterface;
    DLINK                   *dlink;
    COMMAND_STRUCTURE       CommandStructure = {0};
    EFI_STATUS              Status;    


    Status = gBS->LocateHandleBuffer (
                                      ByProtocol,
                                      &gEfiAhciBusProtocolGuid,
                                      NULL,
                                      &HandleCount,
                                      &HandleBuffer
                                      );

    if(EFI_ERROR(Status) || HandleCount == 0 ) {
        return;
    }

    //
    // Issue Disable Software Preservation command all the Sata Devices connected.
    //
    for (i = 0; i < HandleCount; i++) {
        Status = gBS->HandleProtocol (HandleBuffer[i], &gEfiAhciBusProtocolGuid, &AhciBusInterface);
        if (!EFI_ERROR(Status)) {
            dlink = AhciBusInterface->SataDeviceList.pHead; 
            if (dlink){ 
                do {
                    SataDeviceInterface = OUTTER(dlink, SataDeviceLink, SATA_DEVICE_INTERFACE);
 
                    if ((SataDeviceInterface->IdentifyData.Reserved_76_79[0] != 0xFFFF )&&
                        (SataDeviceInterface->IdentifyData.Reserved_76_79[2] & 0x0040)&&           // Software Preservation support
                        (SataDeviceInterface->IdentifyData.Security_Status_128 & 0x0002)&&         // Security enabled
                        (!(SataDeviceInterface->IdentifyData.Security_Status_128 & 0x0004))) {     // Security not locked
 
                            //
                            // Send Disable Software Preservation command.
                            //
                            CommandStructure.Features = DISABLE_SATA2_SOFTPREV;
                            CommandStructure.SectorCount = 6;
                            CommandStructure.Command = SET_FEATURE_COMMAND;
                            Status = AhciBusInterface->ExecuteNonDataCommand(SataDeviceInterface, CommandStructure);
                    }
                    dlink = dlink-> pNext;
                }while (dlink);    
            }
         }
     }
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
//**********************************************************************