/*++
   Module Name:

   TcgDxe.c

   Abstract:

   DXE Driver that provides TCG services

   --*/
//*************************************************************************
// $Header: /Alaska/SOURCE/Modules/TCG2/Common/TcgDxe/TcgDxe20.c 3     6/14/14 12:29a Fredericko $
//
// $Revision: 3 $
//
// $Date: 6/14/14 12:29a $
//*************************************************************************
// Revision History
// ----------------
// $Log:
#include "TcgCommon.h"
#include <TcgMisc.h>
#include <Token.h>
#include <AmiDxeLib.h>
#include <Runtime.h>
#include <Tpm20Includes\Tpm20.h>
#include <Tpm20Includes\TrEEProtocol.h>
#include "protocol\TpmDevice\TpmDevice.h"
#include <Protocol\ComponentName.h>
#include <Protocol\ComponentName2.h>
#include <Protocol\DriverBinding.h>
#include <Protocol\AcpiSupport.h>
#include "TcgPlatformSetupPolicy.h"
#include <Acpi.h>
#include <AcpiRes.h>
#include "Tpm20CRBLib.h"

/*
  locates the TPM20 hob from Pei. If found we are processing TPM 20 devic
  need to install the TreeProtocol and do TPM20 binding measurements
*/
#define     MAX_LOG_AREA_SIZE (32 * 1024) // 32KB

static EFI_PHYSICAL_ADDRESS TreeEventLogLocation;
static EFI_PHYSICAL_ADDRESS LastEntry = NULL;
static EFI_PHYSICAL_ADDRESS LastEventPtr = 0;
static EFI_TPM_DEVICE_PROTOCOL *TpmDevice=NULL;

BOOLEAN IsTpm20Device();

typedef struct _AMI_INTERNAL_HLXE_PROTOCOL  AMI_INTERNAL_HLXE_PROTOCOL;

typedef
EFI_STATUS
(EFIAPI * INTERNAL_HASH_LOG_EXTEND_EVENT) (
  IN  UINT8                  *DataToHash,
  IN  UINT64                  Flags,
  IN  UINTN                   DataSize,
  IN OUT  TCG_PCR_EVENT_HDR   *NewEventHdr,
  IN      UINT8               *NewEventData
);


struct _AMI_INTERNAL_HLXE_PROTOCOL {
	INTERNAL_HASH_LOG_EXTEND_EVENT  InternalHashLogExtend;
};


static UINT16   *gDriverName=L"TPM Driver";
static BOOLEAN   Tpm20FwDevice = FALSE;


UINT8  GetHashPolicy()
{
    TCG_PLATFORM_SETUP_PROTOCOL     *ProtocolInstance;
    EFI_STATUS                      Status;
    EFI_GUID                        Policyguid = TCG_PLATFORM_SETUP_POLICY_GUID;

   Status = pBS->LocateProtocol (&Policyguid,  NULL, &ProtocolInstance);
   if (EFI_ERROR (Status)) {
      return 0;
   }

   return(ProtocolInstance->ConfigFlags.Reserved1);
}


EFI_STATUS
EFIAPI
Tpm20ComponentNameGetDriverName (
  IN  EFI_COMPONENT_NAME_PROTOCOL  *This,
  IN  CHAR8                        *Language,
  OUT CHAR16                       **DriverName
  )
{
    //Supports only English
	if(!Language || !DriverName) return EFI_INVALID_PARAMETER;

	if (!LanguageCodesEqual( Language, "en-US") &&
        !LanguageCodesEqual( Language, "eng"))
        return EFI_UNSUPPORTED;
	else 
        *DriverName=gDriverName;
	
	return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
Tpm20ComponentNameGetControllerName (
  IN  EFI_COMPONENT_NAME_PROTOCOL                     *This,
  IN  EFI_HANDLE                                      ControllerHandle,
  IN  EFI_HANDLE                                      ChildHandle        OPTIONAL,
  IN  CHAR8                                           *Language,
  OUT CHAR16                                          **ControllerName
  )
{
  return EFI_UNSUPPORTED;
}

EFI_STATUS
EFIAPI
Tpm20ComponentNameGetDriverName2 (
  IN  EFI_COMPONENT_NAME2_PROTOCOL  *This,
  IN  CHAR8                        *Language,
  OUT CHAR16                       **DriverName
  )
{
    //Supports only English
	if(!Language || !DriverName) return EFI_INVALID_PARAMETER;
//LANGUAGE_CODE_ENGLISH
	if (!LanguageCodesEqual( Language, "en-US") &&
        !LanguageCodesEqual( Language, "eng"))
        return EFI_UNSUPPORTED;
	else 
        *DriverName=gDriverName;
	
	return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
Tpm20ComponentNameGetControllerName2 (
  IN  EFI_COMPONENT_NAME2_PROTOCOL                     *This,
  IN  EFI_HANDLE                                      ControllerHandle,
  IN  EFI_HANDLE                                      ChildHandle        OPTIONAL,
  IN  CHAR8                                           *Language,
  OUT CHAR16                                          **ControllerName
  )
{
  return EFI_UNSUPPORTED;
}


static EFI_COMPONENT_NAME_PROTOCOL gComponentName = {
  Tpm20ComponentNameGetDriverName,
  Tpm20ComponentNameGetControllerName,
  LANGUAGE_CODE_ENGLISH
};


static EFI_COMPONENT_NAME2_PROTOCOL gComponentName2 = {
  Tpm20ComponentNameGetDriverName2,
  Tpm20ComponentNameGetControllerName2,
  LANGUAGE_CODE_ENGLISH
};


EFI_STATUS
EFIAPI
Tpm20DriverBindingSupported (
  IN EFI_DRIVER_BINDING_PROTOCOL  *This,
  IN EFI_HANDLE                   Controller,
  IN EFI_DEVICE_PATH_PROTOCOL     *RemainingDevicePath   OPTIONAL
  )
{
  EFI_STATUS          Status      =  EFI_SUCCESS;
  static BOOLEAN      Initialized = FALSE;

  if(Initialized == FALSE){
        Initialized = TRUE;
    if(IsTpm20Device()){
        return EFI_SUCCESS;
    }else if(Tpm20FwDevice)return EFI_SUCCESS;
  }
 
  return EFI_UNSUPPORTED;
}


EFI_STATUS
EFIAPI
Tpm20DriverBindingStart (
  IN EFI_DRIVER_BINDING_PROTOCOL  *This,
  IN EFI_HANDLE                   Controller,
  IN EFI_DEVICE_PATH_PROTOCOL     *RemainingDevicePath   OPTIONAL
  )
{
  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
Tpm20DriverBindingStop (
  IN  EFI_DRIVER_BINDING_PROTOCOL     *This,
  IN  EFI_HANDLE                      Controller,
  IN  UINTN                           NumberOfChildren,
  IN  EFI_HANDLE                      *ChildHandleBuffer   OPTIONAL
  )
{
	return EFI_UNSUPPORTED;
}

EFI_DRIVER_BINDING_PROTOCOL Tpm20DriverBinding = {
  Tpm20DriverBindingSupported,
  Tpm20DriverBindingStart,
  Tpm20DriverBindingStop,
  0xa,
  NULL,
  NULL
};



EFI_STATUS
__stdcall Tcg20CommonExtend(
    IN VOID         *CallbackContext,
    IN TPM_PCRINDEX PcrIndex,
    IN TCG_DIGEST   *Digest,
    OUT TCG_DIGEST  *NewPCRValue );



BOOLEAN IsTpm20Device()
{
   EFI_GUID gTpm20Supporthobguid = TPM20_HOB_GUID;
   UINT8    *TpmSupport = NULL;

   TpmSupport = LocateATcgHob( pST->NumberOfTableEntries,
                  pST->ConfigurationTable,
                  &gTpm20Supporthobguid);

   if(TpmSupport != NULL){
      if((*(volatile UINT8 *)((UINTN)(0xfed40000))!=0xff)){
         if(*TpmSupport == 1)
           return TRUE;
      }
   }    
   
   return FALSE;
}


EFI_STATUS
TreeGetCapability (
  IN EFI_TREE_PROTOCOL                *This,
  IN OUT TREE_BOOT_SERVICE_CAPABILITY *ProtocolCapability
  )
{
  EFI_STATUS  Status = EFI_SUCCESS;
  UINT8       HashAlg = GetHashPolicy();
  
  if((ProtocolCapability == NULL) || (This == NULL)){
    Status = EFI_INVALID_PARAMETER;
  }
  else {
    if(ProtocolCapability->Size < (sizeof(UINT8) + sizeof(TREE_VERSION) + sizeof(TREE_VERSION))){
      Status = EFI_BUFFER_TOO_SMALL;
		}
    else {
      ProtocolCapability->StructureVersion.Major = 1;
      ProtocolCapability->StructureVersion.Minor = 0;
      ProtocolCapability->ProtocolVersion.Major  = 1;
      ProtocolCapability->ProtocolVersion.Minor  = 0;

      if (ProtocolCapability->Size < sizeof(TREE_BOOT_SERVICE_CAPABILITY)){
        ProtocolCapability->Size = sizeof(TREE_BOOT_SERVICE_CAPABILITY);
        Status = EFI_BUFFER_TOO_SMALL;
      }
      else {

        if( HashAlg == 0){
            ProtocolCapability->HashAlgorithmBitmap = TREE_BOOT_HASH_ALG_SHA1;
        }else if(HashAlg == 1){
            ProtocolCapability->HashAlgorithmBitmap = TREE_BOOT_HASH_ALG_SHA256;
        }

        ProtocolCapability->SupportedEventLogs  = TREE_EVENT_LOG_FORMAT_TCG_1_2;
        ProtocolCapability->TrEEPresentFlag     = TRUE;
        ProtocolCapability->MaxCommandSize      = 0x0F80;   
        ProtocolCapability->MaxResponseSize     = 0x0F80;   
        ProtocolCapability->ManufacturerID      = *(UINT16 *)(UINTN)(PORT_TPM_IOMEMBASE + 0xF00);  
      }
    }
  }

  return Status;
}


EFI_STATUS
TreeGetEventLog (
  IN  EFI_TREE_PROTOCOL     *This,
  IN  TREE_EVENTLOGTYPE     EventLogFormat,
  OUT EFI_PHYSICAL_ADDRESS  *EventLogLocation,
  OUT EFI_PHYSICAL_ADDRESS  *EventLogLastEntry,
  OUT BOOLEAN               *EventLogTruncated
	)
{
	EFI_STATUS Status = EFI_SUCCESS;

	if(EventLogFormat != TREE_EVENT_LOG_FORMAT_TCG_1_2)
	{
		Status = EFI_INVALID_PARAMETER;
	}

    *EventLogLocation  = TreeEventLogLocation;
	*EventLogLastEntry = LastEventPtr;
	*EventLogTruncated = FALSE;  

	return Status;
}


EFI_STATUS
InternalTcg20CommonExtend(
    IN VOID         *CallbackContext,
    IN TPM_PCRINDEX PcrIndex,
    IN TCG_DIGEST   *Digest,
    OUT TCG_DIGEST  *NewPCRValue )
{
    TPM2_PCRExtend_cmd_t  Cmd;
    TPM2_PCRExtend_res_t  Res;
    TPM2_PCRExtend_res_t  Tmpres;
    UINT32                CmdSize;
    UINT8                 *Buffer;
    UINT8                 *AuthSizeOffset;
    UINT8                 *ResultBuf = NULL;
    UINT32                ResultBufSize = 0;
    UINT32                DigestSize;
    EFI_STATUS            Status;
    TPM_TRANSMIT_BUFFER   InBuffer[1], OutBuffer[1];

    Cmd.Tag          = (TPMI_ST_COMMAND_TAG)TPM_H2NS(TPM_ST_SESSIONS);
    Cmd.CommandSize  = TPM_H2NL(sizeof(Cmd));
    Cmd.CommandCode  = TPM_H2NL(TPM_CC_PCR_Extend);

    Buffer = (UINT8 *)&Cmd.inputParameters;
    *(UINT32 *)Buffer = TPM_H2NL(PcrIndex);
    Buffer += sizeof(UINT32);

    AuthSizeOffset = Buffer;
    *(UINT32 *)Buffer = 0;
    Buffer += sizeof(UINT32);

    //  pcr authHandle
    *(UINT32 *)Buffer = TPM_H2NL(TPM_RS_PW);
    Buffer += sizeof(UINT32);

    // nonce = nullNonce
    *(UINT16 *)Buffer = 0;
    Buffer += sizeof(UINT16);

    // sessionAttributes = 0
    *(UINT8 *)Buffer = 0;
    Buffer += sizeof(UINT8);

    // auth = nullAuth
    *(UINT16 *)Buffer = 0;
    Buffer += sizeof(UINT16);

    // authorizationSize
    *(UINT32 *)AuthSizeOffset = TPM_H2NL((UINT32)(Buffer - AuthSizeOffset - sizeof(UINT32)));

	//Digest count
	*(UINT32 *)Buffer = TPM_H2NL(1);
    Buffer += sizeof(UINT32);


	// Get the digest size based on Hash Alg
    if(GetHashPolicy()==0){
        //Hash alg
	    *(UINT16 *)Buffer = TPM_H2NS(TPM2_ALG_SHA1);
        Buffer += sizeof(UINT16);
        DigestSize = 0x14;
        TcgCommonCopyMem(CallbackContext, Buffer, &Digest->digest, DigestSize);
    }else{
	    //Hash alg
	    /**(UINT16 *)Buffer = TPM_H2NS(TPM2_ALG_SHA256);
        Buffer += sizeof(UINT16);
        DigestSize = 0x20;
        TcgCommonCopyMem(CallbackContext, Buffer, &Digest->digestSha2, DigestSize);*/
        return EFI_UNSUPPORTED;
    }

    Buffer += DigestSize;

    CmdSize = (UINT32)(Buffer - (UINT8 *)&Cmd);
    Cmd.CommandSize = TPM_H2NL(CmdSize);

    ResultBuf     = (UINT8 *) &Tmpres;
    ResultBufSize = sizeof(Res);
    
    if(Tpm20FwDevice ==FALSE)
    {
        TRACE(( TRACE_ALWAYS," Tpm20FwDevice = FALSE \n"));
        if(TpmDevice==NULL)return EFI_NOT_FOUND;

        InBuffer[0].Buffer = &Cmd;
        InBuffer[0].Size   = CmdSize;
        OutBuffer[0].Buffer = ResultBuf;
        OutBuffer[0].Size   = ResultBufSize;

        TpmDevice->Init(TpmDevice );

        Status = TpmDevice->Transmit(TpmDevice,
                   sizeof (InBuffer) / sizeof (*InBuffer),
                   InBuffer,
                   sizeof (OutBuffer) / sizeof (*OutBuffer),
                   OutBuffer);

        TpmDevice->Close(TpmDevice );
    }else{
        Status = CrbSubmitCmd((UINT8 *)&Cmd, CmdSize, ResultBuf, &ResultBufSize);
    }

    return Status;
}


#pragma optimize("",off)
EFI_STATUS
TpmHashLogExtendEventI(
  IN  UINT8                   *DataToHash,
  IN  UINT64                  Flags,
  IN  UINTN                   DataSize,
  IN OUT  TCG_PCR_EVENT_HDR   *NewEventHdr,
  IN      UINT8               *NewEventData
)
{
  EFI_STATUS                Status;
  TCG_DIGEST                Out_Digest;
  BOOLEAN                   isSha1 = GetHashPolicy();
  UINT32                    TempSize;
  UINTN                     RequiredSpace=0;


  TRACE(( TRACE_ALWAYS," TpmHashLogExtendEvent Entry \n"));
#if defined LOG_EV_EFI_ACTION && LOG_EV_EFI_ACTION == 0 
  if(NewEventHdr->EventType == EV_EFI_ACTION)
    {
      return EFI_SUCCESS;
  }
#endif

   if(DataToHash!=NULL)
   {
    if(isSha1==0){
         RequiredSpace = sizeof(TCG_PCR_EVENT_HDR) - sizeof(NewEventHdr->Digest)\
                         + sizeof(NewEventHdr->Digest.digest) + NewEventHdr->EventSize;
        Status = SHA1HashAll( NULL, DataToHash, DataSize, &NewEventHdr->Digest );        
        TRACE(( TRACE_ALWAYS," SHA1HashAll Status = %r \n", Status));
        if(EFI_ERROR(Status))return Status;
    }else{
       /*  RequiredSpace = sizeof(TCG_PCR_EVENT_HDR) - sizeof(NewEventHdr->Digest)\
                         + sizeof(NewEventHdr->Digest.digestSha2) + NewEventHdr->EventSize;
        Status = SHA2HashAll( NULL, DataToHash, DataSize, &NewEventHdr->Digest );
        TRACE(( TRACE_ALWAYS," SHA2HashAll Status = %r \n", Status));
        if(EFI_ERROR(Status))return Status;*/
    }
   }



   if((RequiredSpace + LastEventPtr) > \
                (TreeEventLogLocation  + MAX_LOG_AREA_SIZE))return EFI_OUT_OF_RESOURCES;

   Status = InternalTcg20CommonExtend(NULL,
                     NewEventHdr->PCRIndex,
                     &NewEventHdr->Digest,
                     &Out_Digest);

   TRACE(( TRACE_ALWAYS," InternalTcg20CommonExtend Status = %r \n", Status));
   if(EFI_ERROR(Status))return Status;

   TRACE(( TRACE_ALWAYS," LastEntry = %x \n", LastEntry));
   if(LastEntry == NULL) return EFI_ABORTED;
    
   LastEventPtr = LastEntry;

   if(isSha1 == 0){ //log event record
        pBS->CopyMem(
            (VOID*)(UINTN)LastEntry,
            NewEventHdr,
            sizeof(TCG_PCR_EVENT_HDR) -sizeof(NewEventHdr->Digest) - sizeof(UINT32));   
        
        TempSize =  sizeof(TCG_PCR_EVENT_HDR) -sizeof(NewEventHdr->Digest) - sizeof(UINT32);

        pBS->CopyMem(
            (VOID*)(UINTN)(LastEntry + TempSize) ,
            (UINT8 *)&NewEventHdr->Digest.digest,
            sizeof(NewEventHdr->Digest.digest));

        TempSize+=sizeof(NewEventHdr->Digest.digest);
       
    }else{

      /*  pBS->CopyMem(
            (VOID*)(UINTN)LastEntry,
            NewEventHdr,
            sizeof(TCG_PCR_EVENT_HDR) -sizeof(NewEventHdr->Digest) - sizeof(UINT32));   
        
        TempSize =  sizeof(TCG_PCR_EVENT_HDR) -sizeof(NewEventHdr->Digest) - sizeof(UINT32);

        pBS->CopyMem(
            (VOID*)(UINTN)(LastEntry + TempSize) ,
            (UINT8 *)&NewEventHdr->Digest.digestSha2,
            sizeof(NewEventHdr->Digest.digestSha2));

        TempSize+=sizeof(NewEventHdr->Digest.digestSha2);*/
        return EFI_UNSUPPORTED;
    }


    pBS->CopyMem(
    (VOID*)(UINTN)(LastEntry + TempSize) ,
    (UINT8 *)&NewEventHdr->EventSize,
    sizeof(UINT32));

    pBS->CopyMem(
    (VOID*)(UINTN)(LastEntry + TempSize + sizeof(UINT32)) ,
    NewEventData,
    NewEventHdr->EventSize);
  
    TempSize+=sizeof(UINT32);
    LastEntry = LastEventPtr + ((EFI_PHYSICAL_ADDRESS)(UINTN)(NewEventHdr->EventSize \
                              + TempSize));
    
    return EFI_SUCCESS;   
}


EFI_STATUS
TreeHashLogExtentEvent (
  IN  EFI_TREE_PROTOCOL     *This,
  IN  UINT64                Flags,
  IN  EFI_PHYSICAL_ADDRESS  DataToHash,
  IN  UINT64                DataToHashLen,
  IN  TrEE_EVENT            *TreeEvent
  )
{
  EFI_STATUS            Status     = EFI_SUCCESS;
  TCG_PCR_EVENT_HDR     TcgEvent;
  
  if((This == NULL ) || (DataToHash == 0) || (TreeEvent == NULL)) {
    Status = EFI_INVALID_PARAMETER;
    goto Exit;
  }
  else if(TreeEvent->Size < (TreeEvent->Header.HeaderSize + sizeof(UINT32))\
                                 || (TreeEvent->Header.PCRIndex > 23)){
   Status = EFI_INVALID_PARAMETER;
   goto Exit;
  }

  TcgEvent.PCRIndex  = TreeEvent->Header.PCRIndex;
  TcgEvent.EventType = TreeEvent->Header.EventType;
  TcgEvent.EventSize = TreeEvent->Size - sizeof(TrEE_EVENT_HEADER) \
                        -sizeof(UINT32);

  Status = TpmHashLogExtendEventI(
             (UINT8 *)(UINTN)DataToHash,
                      Flags,
             (UINTN)  DataToHashLen,
                      &TcgEvent,
             (UINT8 *)&TreeEvent->Event
                      );

Exit:

	return Status;
}


EFI_STATUS
TreeSubmitCommand (
IN  EFI_TREE_PROTOCOL   *This,
IN  UINT32              InputParameterBlockSize,
IN  UINT8               *InputParameterBlock,
IN  UINT32              OutputParameterBlockSize,
IN  UINT8               *OutputParameterBlock
  )
{
    EFI_STATUS            Status     = EFI_SUCCESS;
    UINT32                ReturnSize = 0;
    UINT32                Size = 0;
    TPM_TRANSMIT_BUFFER   InBuffer[1], OutBuffer[1];

    if (This == NULL || InputParameterBlock == NULL || OutputParameterBlock == NULL) {
        return EFI_INVALID_PARAMETER;
    }

    if(Tpm20FwDevice ==FALSE)
    {
         ReturnSize = OutputParameterBlockSize;

         Status = TpmDevice->Init( TpmDevice );
 
         InBuffer[0].Buffer  = InputParameterBlock;
         InBuffer[0].Size    = InputParameterBlockSize;
         OutBuffer[0].Buffer = OutputParameterBlock;
         OutBuffer[0].Size   = OutputParameterBlockSize;


         TpmDevice->Transmit(TpmDevice,
                  sizeof (InBuffer) / sizeof (*InBuffer),
                   InBuffer,
                   sizeof (OutBuffer) / sizeof (*OutBuffer),
                   OutBuffer);

         TpmDevice->Close(TpmDevice );
    }else{

        Size = OutputParameterBlockSize;
        Status = CrbSubmitCmd(InputParameterBlock,
                       InputParameterBlockSize,
                       OutputParameterBlock,
                       &Size);
    }

    return Status;
}



static EFI_STATUS CopyTcgLog(
    void )
{
    TCG_LOG_HOB     *TcgLog = NULL;
    void**          DummyPtr;
    EFI_GUID        gEfiPeiLogHobGuid = EFI_TCG_LOG_HOB_GUID;

    TcgLog = (TCG_LOG_HOB*)                   LocateATcgHob(
        pST->NumberOfTableEntries,
        pST->ConfigurationTable,
        &gEfiPeiLogHobGuid );

    DummyPtr = &TcgLog;

    if ( *DummyPtr == NULL )
    {
        return EFI_NOT_FOUND;
    }

    TcgLog->TableMaxSize = MAX_LOG_AREA_SIZE;

    pBS->CopyMem(
        (UINT8 *)(UINTN)TreeEventLogLocation,
        (((UINT8 *)TcgLog) + sizeof(TCG_LOG_HOB)),
        TcgLog->TableSize
        );

    LastEntry = TreeEventLogLocation + TcgLog->TableSize;

    return EFI_SUCCESS;
}




EFI_TREE_PROTOCOL mTreeProtocol = {
  TreeGetCapability,
  TreeGetEventLog,
  TreeHashLogExtentEvent,
  TreeSubmitCommand
};

AMI_INTERNAL_HLXE_PROTOCOL  InternalLogProtocol = {
  TpmHashLogExtendEventI
};



EFI_STATUS
InstallTrEEProtocol(
  IN EFI_HANDLE Handle
  )
{    
  EFI_STATUS Status;
  EFI_GUID  gEfiTrEEProtocolGuid =  EFI_TREE_PROTOCOL_GUID;
  EFI_GUID  gEfiAmiHLXEGuid =  AMI_PROTOCOL_INTERNAL_HLXE_GUID;

  TRACE(( TRACE_ALWAYS," InstallTrEEProtocol \n"));
  Status =  pBS->InstallProtocolInterface (
                &Handle,
                &gEfiTrEEProtocolGuid,
                EFI_NATIVE_INTERFACE,
                &mTreeProtocol
                );

  Status =  pBS->InstallProtocolInterface (
                &Handle,
                &gEfiAmiHLXEGuid,
                EFI_NATIVE_INTERFACE,
                &InternalLogProtocol
                );

  Status = pBS->AllocatePages(AllocateAnyPages,
                    EfiRuntimeServicesData,
                    EFI_SIZE_TO_PAGES(MAX_LOG_AREA_SIZE),
                    (UINT64*)(UINTN)&TreeEventLogLocation);

  pBS->SetMem(
            (VOID*)((UINTN)TreeEventLogLocation),
            (UINTN)MAX_LOG_AREA_SIZE,
            0x00);  

  //locate PEI hob and copy to the TreeLogArea
  Status = CopyTcgLog();
    
  TRACE(( TRACE_ALWAYS," InstallTrEEProtocol Exit Status = %r \n", Status));
  return Status;
}




VOID UpdateTpmDeviceASL(    
    IN EFI_EVENT ev,
    IN VOID      *ctx)
{   
    ACPI_HDR                    *dsdt;
    EFI_PHYSICAL_ADDRESS        dsdtAddress=0;
    static VOID                 *reg;
    EFI_EVENT                   Event;
    EFI_STATUS                  Status;
    UINT64                      Value;


    //locate AcpiProtocol

    Status = LibGetDsdt(&dsdtAddress, EFI_ACPI_TABLE_VERSION_ALL);
    if (EFI_ERROR(Status)){
        TRACE((TRACE_ALWAYS, "UpdateTpmDeviceASL::DSDT not found\n"));
        if(Status == EFI_NOT_AVAILABLE_YET){
            //set callback
            Status = pBS->CreateEvent( EFI_EVENT_NOTIFY_SIGNAL,
                                   EFI_TPL_DRIVER, UpdateTpmDeviceASL, &reg, &Event );

            if(EFI_ERROR(Status)){
                TRACE((TRACE_ALWAYS, "Unable to create Event..Exit(1)\n"));
                return;
            }
            Status = pBS->RegisterProtocolNotify( &gEfiAcpiSupportGuid, Event, &reg );   
        }
        return;
    }

    TRACE((TRACE_ALWAYS, "UpdateTpmDeviceASL::dsdtAddress %x \n", dsdtAddress));
    dsdt = (ACPI_HDR*)dsdtAddress;

    TRACE((TRACE_ALWAYS, "dsdt->Signature =  %x \n", dsdt->Signature));
    
    Value = 1;
    Status=UpdateAslNameObject(dsdt, "TTDP", (UINT64)Value);
    if (EFI_ERROR(Status)){
        TRACE((TRACE_ALWAYS, "UpdateTpmDeviceASL::Failure setting ASL TTDP %r \n", Status));
        return;
    }    

    if(isTpm20CrbPresent()){
        Value = 0;
    }else{
        Value = 1;
    }

    Status=UpdateAslNameObject(dsdt, "TTPF", (UINT64)Value);
    if (EFI_ERROR(Status)){
        TRACE((TRACE_ALWAYS, "UpdateTpmDeviceASL::Failure setting ASL value %r \n", Status));
    }
    return;
}

VOID ReadMORValue( );


EFI_STATUS
EFIAPI Tcg20DxeEntry(
    IN EFI_HANDLE       ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable )
{
    EFI_STATUS          Status;
    TCG_PLATFORM_SETUP_PROTOCOL     *PolicyInstance;
    EFI_GUID            gPolicyguid = TCG_PLATFORM_SETUP_POLICY_GUID;
    TCG_CONFIGURATION   Config;
    
    TRACE(( TRACE_ALWAYS," Tcg20DxeEntry \n"));
    if(!IsTpm20Device()){
        if(!isTpm20CrbPresent()){
          TRACE(( TRACE_ALWAYS," isTpm20CrbPresent returned false \n"));
          return EFI_UNSUPPORTED;
        }
        TRACE(( TRACE_ALWAYS," Tpm20FwDevice = TRUE \n"));
        Tpm20FwDevice = TRUE;
    }

    if(Tpm20FwDevice == FALSE)
    {
            Status = pBS->LocateProtocol(
                &gEfiTpmDeviceProtocolGuid,
                NULL,
                &TpmDevice); 
    }
    
    Status = pBS->LocateProtocol (&gPolicyguid,  NULL, &PolicyInstance);
    if (EFI_ERROR (Status)) {
      return Status;
    }

    ReadMORValue();

    MemCpy(&Config, &PolicyInstance->ConfigFlags, sizeof(TCG_CONFIGURATION));

    if(Config.TpmSupport != 0){
        Config.Tpm20Device = 1;
    }else{
        Config.Tpm20Device = 0;        
        PolicyInstance->UpdateStatusFlags(&Config, TRUE); 
        return EFI_SUCCESS;
    }

    PolicyInstance->UpdateStatusFlags(&Config, TRUE); 

    Status = InstallTrEEProtocol(ImageHandle);
    if(EFI_ERROR(Status))return EFI_ABORTED;

     //install binding protocol TrEE binding protocol
    Tpm20DriverBinding.DriverBindingHandle = ImageHandle;
    Tpm20DriverBinding.ImageHandle = ImageHandle;

     Status = pBS->InstallMultipleProtocolInterfaces (
                               &Tpm20DriverBinding.DriverBindingHandle,
                               &gEfiDriverBindingProtocolGuid, &Tpm20DriverBinding,
                               &gEfiComponentNameProtocolGuid, &gComponentName,
                               &gEfiComponentName2ProtocolGuid, &gComponentName2,
                                NULL);

    UpdateTpmDeviceASL(NULL, NULL);

    return EFI_SUCCESS;
}
