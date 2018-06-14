//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.            **
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
// $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/PchWrap/SmBusMemoryDown.c 1     12/11/12 1:09a Scottyang $
//
// $Date: 12/11/12 1:09a $
//*************************************************************************
// Revision History
// ----------------
// $Log:
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name: SmBusMemoryDown.c
//
// Description: SmBus support MemoryDown functions implementation
//
//<AMI_FHDR_END>
//*************************************************************************

#include <efi.h>
#include <AmiDxeLib.h>
#include <AmiCspLib.h>
#include <Protocol\SmBus.h>

EFI_SMBUS_HC_PROTOCOL   *SmBusProtocol = NULL; 
static EFI_SMBUS_HC_EXECUTE_OPERATION    PchSmBusExecute = NULL;
EFI_EVENT           gSmBusMemoryDownEvent;
VOID                *gSmBusMemoryDownEventReg;
UINT8               IsRunMemoryDown = 0;
EFI_GUID        gEfiSMBusProtocolGuid = EFI_SMBUS_HC_PROTOCOL_GUID;

#ifndef AMI_OVERRIDE_FOR_MEMORY_DOWN
#if defined(NB_OEM_DIMM1_STATUS) && (NB_OEM_DIMM1_STATUS == 0x02)
static UINT8 Dimm1SpdTbl[] = NB_OEM_DIMM1_SPD_DATA;
#endif
#if defined(NB_OEM_DIMM2_STATUS) && (NB_OEM_DIMM2_STATUS == 0x02)
static UINT8 Dimm2SpdTbl[] = NB_OEM_DIMM2_SPD_DATA;
#endif
#if defined(NB_OEM_DIMM3_STATUS) && (NB_OEM_DIMM3_STATUS == 0x02)
static UINT8 Dimm3SpdTbl[] = NB_OEM_DIMM3_SPD_DATA;
#endif
#if defined(NB_OEM_DIMM4_STATUS) && (NB_OEM_DIMM4_STATUS == 0x02)
static UINT8 Dimm4SpdTbl[] = NB_OEM_DIMM4_SPD_DATA;
#endif
#endif // AMI_OVERRIDE_FOR_MEMORY_DOWN

VOID OverrideSmBusNotify (
    IN EFI_EVENT        Event,
    IN VOID             *Context 
);


//*************************************************************************
//<AMI_PHDR_START>
//
// Procedure:   OverrideSmBusExecute
//
// Description: Init SmBus MemoryDown Protocol Execute..
//
// Input:
//
// Output:
//
//<AMI_PHDR_END>
//*************************************************************************
EFI_STATUS
EFIAPI
OverrideSmBusExecute (
  IN      EFI_SMBUS_HC_PROTOCOL         *This,
  IN      EFI_SMBUS_DEVICE_ADDRESS      SlaveAddress,
  IN      EFI_SMBUS_DEVICE_COMMAND      Command,
  IN      EFI_SMBUS_OPERATION           Operation,
  IN      BOOLEAN                       PecCheck,
  IN OUT  UINTN                         *Length,
  IN OUT  VOID                          *Buffer
  )
{
  UINT8 *DimmSpd = NULL;
  UINT8 *BufferPoint = Buffer;
  UINT16 i = 0;

  if (IsRunMemoryDown) {
#ifdef NB_OEM_DIMM1_SPD_DATA
     if(SlaveAddress.SmbusDeviceAddress == DIMM1_SMBUS_ADDRESS >> 1) {
        DimmSpd = Dimm1SpdTbl;
     }
#endif
#ifdef NB_OEM_DIMM2_SPD_DATA
     if(SlaveAddress.SmbusDeviceAddress == DIMM2_SMBUS_ADDRESS >> 1) {
        DimmSpd = Dimm2SpdTbl;
     }
#endif
#ifdef NB_OEM_DIMM3_SPD_DATA
     if(SlaveAddress.SmbusDeviceAddress == DIMM3_SMBUS_ADDRESS >> 1) {
        DimmSpd = Dimm3SpdTbl;
     }
#endif
#ifdef NB_OEM_DIMM4_SPD_DATA
     if(SlaveAddress.SmbusDeviceAddress == DIMM4_SMBUS_ADDRESS >> 1) {
        DimmSpd = Dimm4SpdTbl;
     }
#endif
     if (DimmSpd != NULL) {
        for (i=0; i <= *Length; i++) {
           *BufferPoint = DimmSpd[Command + i];
           BufferPoint++;
        }
        return EFI_SUCCESS;
     }
  }

  return PchSmBusExecute (
          This,
          SlaveAddress,
          Command,
          Operation,
          PecCheck,
          Length,
          Buffer
          );

}
//*************************************************************************
//<AMI_PHDR_START>
//
// Procedure:   OverrideSmBusNotify
//
// Description: Override SmBus Protocol Execute.
//
// Input:
//  IN EFI_LEGACY_REGION_PROTOCOL   *This,
//  IN UINT32                       Start,
//  IN UINT32                       Length,
//  OUT UINT32                      *Granularity,
//  IN BOOLEAN                      *On
//
// Output:
//  Status of the operation
//
//<AMI_PHDR_END>
//*************************************************************************
VOID OverrideSmBusNotify (
    IN EFI_EVENT        Event,
    IN VOID             *Context )
{
  EFI_STATUS  Status;

  Status = pBS->LocateProtocol (&gEfiSmbusProtocolGuid, NULL, (VOID**) &SmBusProtocol);
  if (!EFI_ERROR (Status)) {

     PchSmBusExecute = SmBusProtocol->Execute;
     SmBusProtocol->Execute = OverrideSmBusExecute;
  }
  // Kill event
  pBS->CloseEvent(Event);
}
//*************************************************************************
//<AMI_PHDR_START>
//
// Procedure:   InitSmBusMemoryDown
//
// Description: Override the SmBus protocol.
//
// Input:
//  IN EFI_HANDLE        ImageHandle,
//  IN EFI_SYSTEM_TABLE  *SystemTable
//
// Output:
//  Status of the operation
//
// Notes:
//  Here is the control flow of this function:
//  1. Get SmBus protocol.
//  2.  Override the SmBus protocol.
//
//<AMI_PHDR_END>
//*************************************************************************
EFI_STATUS InitSmBusMemoryDown(
    IN EFI_HANDLE        ImageHandle,
    IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
    EFI_STATUS  Status;
    NB_SETUP_DATA           *NBSetupData = NULL;
    UINTN                   VariableSize = sizeof(NB_SETUP_DATA);


    InitAmiLib(ImageHandle, SystemTable);
    
    Status = pBS->AllocatePool( EfiBootServicesData, \
                                VariableSize, \
                                &NBSetupData );
    ASSERT_EFI_ERROR(Status);

    GetNbSetupData( pRS, NBSetupData, FALSE );
 
    if (NBSetupData->IsRunMemoryDown) {
       IsRunMemoryDown = NBSetupData->IsRunMemoryDown;

    
    //NbSetupdata Pass to SaGlobalNvsArea.
       Status = pBS->CreateEvent (
                       EFI_EVENT_NOTIFY_SIGNAL,
                       TPL_CALLBACK,
                       OverrideSmBusNotify,
                       NULL,
                       &gSmBusMemoryDownEvent
                       );

       if (!EFI_ERROR (Status)) {
         Status = pBS->RegisterProtocolNotify (
                         &gEfiSMBusProtocolGuid,
                         gSmBusMemoryDownEvent,
                         &gSmBusMemoryDownEventReg
                         );
       }

    }
    // Free memory used for setup data
    pBS->FreePool( NBSetupData );

    return Status;

}

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
