//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
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
// $Header: /Alaska/BIN/Chipset/Intel/NorthBridge/Haswell/IntelGopDriver/IntelSaGopPolicy.c 5     5/13/14 10:42p Dennisliu $
//
// $Revision: 5 $
//
// $Date: 5/13/14 10:42p $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Chipset/Intel/NorthBridge/Haswell/IntelGopDriver/IntelSaGopPolicy.c $
// 
// 5     5/13/14 10:42p Dennisliu
// [TAG]           EIP167027
// [Category]      Improvement
// [Description]   [SharkBay Aptio4]Variable's attribute needs to be
// reviewed by SA component driver
// [Files]         NBDXEBoard.c; IntelSaGopSetup.c; IntelSaGopPolicy.c;
// NBDxe.c; NbPciCSP.c; PciHostBridge.c;
//
// 4     10/31/12 6:33a Jeffch
// [TAG]           None
// [Category]      Improvement
// [Description]  Add update GOP VBT address event.
//
// 3     8/14/12 5:42a Yurenlai
// [TAG]         None
// [Severity]    Important
// [Description] Implemented BIOS Integration Guide Rev 1.0 to Intel SA
// GOP driver.
// [Files]       IntelSaGopDriver.cif, IntelSaGopDriver.mak,
// IntelSaGopDriver.sdl,
//               IntelSaGopPolicy.c, IntelSaGopSetup.c, IntelSaGopSetup.h,
// IntelSaGopSetup.mak, IntelSaGopSetup.sd, IntelSaGopSetup.sdl,
//               IntelSaGopSetup.uni, IntelSaGopSwitch.c,
// IntelSaGopDriver.h,
//               NBPlatformData.h
//
// 2     7/27/12 7:42a Yurenlai
// [TAG]         None
// [Category]    Improvement
// [Description] Fix building error after update 4.6.5.4_Csm_OptOut_03.
// [Files]       IntelSaGopPolicy.c
//
// 1     3/08/12 10:54p Yurenlai
// [TAG]         None
// [Category]    Improvement
// [Description] Create Haswell Intel SA GOP Driver module part.
//               Notice : IntelGopDriver.efi and vbt.bin is dummy files.
//
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:        IntelSaGopPolicy.c
//
// Description: This file initialises and Installs TerminalPlatformPolicy Protocol.
//
//<AMI_FHDR_END>
//**********************************************************************
#include <Token.h>
#include <AmiDxeLib.h>
#include <KscLib.h>
#include <Setup.h>
#include <AmiCspLib.h>
#include <Protocol\IntelSaGopDriver.h>
#include <Protocol\NBPlatformData.h>
#if defined(CsmOptOut_SUPPORT) && (CsmOptOut_SUPPORT == 1)
#include <AmiLoadCsmPolicy.h>
#endif
#define _SA_COMMON_DEFINITIONS_H_
#include <Protocol\SaPlatformPolicy\SaPlatformPolicy.h>

EFI_GUID  gPlatformGOPPolicyGuid = EFI_PLATFORM_GOP_POLICY_PROTOCOL_GUID;
EFI_GUID  gDxePlatformSaPolicyGuid = DXE_PLATFORM_SA_POLICY_GUID;
EFI_GUID  gSetupGuid = SETUP_GUID;
#if defined(CsmOptOut_SUPPORT) && (CsmOptOut_SUPPORT == 1)
EFI_GUID  gAmiOpromPolicyProtocolGuid = AMI_OPROM_POLICY_PROTOCOL_GUID;
EFI_GUID  gAmiLoadCsmGuid = AMI_LOAD_CSM_GUID;
#endif

PLATFORM_GOP_POLICY_PROTOCOL  mPlatformGOPPolicy;
DXE_PLATFORM_SA_POLICY_PROTOCOL        *gDxePlatformSaPolicy;
#if defined(CsmOptOut_SUPPORT) && (CsmOptOut_SUPPORT == 1)
AMI_OPROM_POLICY_PROTOCOL     *gAmiOpRomPolicyProtocol = NULL;
VOID *gInterface = NULL;
#endif
//
// Function implementations
//

EFI_STATUS
GetPlatformLidStatus (
   OUT LID_STATUS *CurrentLidStatus
)
{
#if defined CRB_EC_SUPPORT && CRB_EC_SUPPORT == 1
   EFI_STATUS              Status;
   UINT8                   PortDataOut;
   Status = InitializeKscLib ();

   if (Status == EFI_SUCCESS) {
     Status = SendKscCommand(KSC_C_READ_MEM);
     if (Status == EFI_SUCCESS) {
       Status = SendKscData(0x03);
       if (Status == EFI_SUCCESS) {
         Status = ReceiveKscData (&PortDataOut);
         if (Status == EFI_SUCCESS) {
           //
           // Bit6 = Lid State (1 = Open, 0 = Closed)
           //
           if ((PortDataOut & BIT6) >> 6)
             *CurrentLidStatus = LidOpen;
           else
             *CurrentLidStatus = LidClosed;
           return EFI_SUCCESS;
         }
       }
     }
   }
#endif

   return EFI_UNSUPPORTED;
}

EFI_STATUS
GetVbtData (
   OUT EFI_PHYSICAL_ADDRESS *VbtAddress,
   OUT UINT32 *VbtSize
)
{
  EFI_STATUS                    Status;
  UINTN                         FvProtocolCount;
  EFI_HANDLE                    *FvHandles;
#if (PI_SPECIFICATION_VERSION < 0x00010000)
  EFI_FIRMWARE_VOLUME_PROTOCOL  *Fv;
#else
  EFI_FIRMWARE_VOLUME2_PROTOCOL *Fv;
#endif
  UINTN                         Index;
  UINT32                        AuthenticationStatus;
  EFI_FV_FILETYPE               FileType;
  EFI_FV_FILE_ATTRIBUTES        FileAttributes;

  UINT8                         *Buffer;
  UINTN                         VbtBufferSize;
  EFI_GUID  BmpImageGuid  = { 0x878AC2CC, 0x5343, 0x46F2, 0xB5, 0x63, 0x51, 0xF8, 0x9D, 0xAF, 0x56, 0xBA };

  Buffer          = NULL;
  FvHandles       = NULL;
  Status = pBS->LocateHandleBuffer (
                  ByProtocol,
                  #if (PI_SPECIFICATION_VERSION < 0x00010000)
                      &gEfiFirmwareVolumeProtocolGuid,
                  #else
                      &gEfiFirmwareVolume2ProtocolGuid,
                  #endif
                  NULL,
                  &FvProtocolCount,
                  &FvHandles
                  );
  if (!EFI_ERROR (Status)) {
    for (Index = 0; Index < FvProtocolCount; Index++) {
      Status = pBS->HandleProtocol (
                      FvHandles[Index],
                      #if (PI_SPECIFICATION_VERSION < 0x00010000)
                          &gEfiFirmwareVolumeProtocolGuid,
                      #else
                          &gEfiFirmwareVolume2ProtocolGuid,
                      #endif
                      (VOID **) &Fv
                      );

      Status = Fv->ReadFile (
                    Fv,
                    &BmpImageGuid,
                    &Buffer,
                    &VbtBufferSize,
                    &FileType,
                    &FileAttributes,
                    &AuthenticationStatus
                    );

      if (!EFI_ERROR (Status)) {
        *VbtAddress = (EFI_PHYSICAL_ADDRESS)Buffer;
        *VbtSize = (UINT32)VbtBufferSize;
        Status = EFI_SUCCESS;
        break;
      }
    }
  } else {
    Status = EFI_NOT_FOUND;
  }

  if (FvHandles != NULL) {
    pBS->FreePool (FvHandles);
    FvHandles = NULL;
  }

  return Status;
}

EFI_STATUS
GetPlatformDockStatus (
   OUT DOCK_STATUS CurrentDockStatus
)
{

  return EFI_UNSUPPORTED;
}

VOID IntelGopVbtUpdateNotify (
    IN EFI_EVENT        Event,
    IN VOID             *Context )
{
  EFI_STATUS  Status;
  EFI_PHYSICAL_ADDRESS          VbtAddress;
  UINT32                        VbtSize;

  Status = pBS->LocateProtocol (
                  &gDxePlatformSaPolicyGuid,
                  NULL,
                  (VOID **) &gDxePlatformSaPolicy
                  );
  if (!EFI_ERROR (Status)) {

   Status = GetVbtData(&VbtAddress, &VbtSize);
   if (!EFI_ERROR (Status)) {
      gDxePlatformSaPolicy->IgdConfig->VbtAddress = VbtAddress;
      gDxePlatformSaPolicy->IgdConfig->Size = VbtSize;
   }
  }
  // Kill event
  pBS->CloseEvent(Event);

}

EFI_STATUS
EFIAPI
IntelSaGopPolicyEntryPoint (
  IN EFI_HANDLE       ImageHandle,
  IN EFI_SYSTEM_TABLE *SystemTable
  )
/*++

Routine Description:

  Entry point for the Platform GOP Policy Driver.

Arguments:

  ImageHandle       Image handle of this driver.
  SystemTable       Global system service table.

Returns:

  EFI_SUCCESS           Initialization complete.
  EFI_OUT_OF_RESOURCES  Do not have enough resources to initialize the driver.

--*/
{
  EFI_STATUS  Status;
  NB_PLATFORM_DATA                NBPlatformData = {0};
  UINTN                           VariableSize;
  SETUP_DATA                      *SetupData = NULL;
  EFI_EVENT                       DxePlatformSaPolicyEvent;
  VOID                            *DxePlatformSaPolicyReg;
  UINT32                          Attributes = 0;   // [ EIP167027 ]


  InitAmiLib (ImageHandle, SystemTable);

  // Read the NB Platform Data
  VariableSize = sizeof (NB_PLATFORM_DATA);
  //Status = pRS->GetVariable (                 // [ EIP167027 ]
  //          L"NBPlatformData",
  //          &gSetupGuid,
  //          NULL,
  //          &VariableSize,
  //          &NBPlatformData
  //          );
  Status = pRS->GetVariable (
            L"NBPlatformData",
            &gSetupGuid,
            &Attributes,
            &VariableSize,
            &NBPlatformData
            );
  if (EFI_ERROR(Status))
    Attributes = EFI_VARIABLE_BOOTSERVICE_ACCESS;

  VariableSize = sizeof(SETUP_DATA);
  Status = GetEfiVariable(
                 L"Setup",
                 &gSetupGuid,
                 NULL,
                 &VariableSize,
                 &SetupData
                 );

#if (defined(CSM_SUPPORT) && (CSM_SUPPORT != 0))
#if defined(CsmOptOut_SUPPORT) && (CsmOptOut_SUPPORT == 1)

   Status = pBS->LocateProtocol( &gAmiLoadCsmGuid, \
                                 NULL, \
                                 &gInterface );
   if(!EFI_ERROR(Status))
   {
      if ((SetupData->VideoOpRom == 0) || (SetupData->VideoOpRom == 2)) return EFI_UNSUPPORTED;
   }

#else

#if defined(CORE_COMBINED_VERSION) && (CORE_COMBINED_VERSION <= 0x4028b)
{
 if ((SetupData->VideoOpRom) == 1) return EFI_UNSUPPORTED;
}
#else
 return EFI_UNSUPPORTED;
#endif // CORE_COMBINED_VERSION
#endif // CsmOptOut_SUPPORT
#endif // CSM_SUPPORT

  pBS->SetMem (&mPlatformGOPPolicy, sizeof (PLATFORM_GOP_POLICY_PROTOCOL), 0);

  mPlatformGOPPolicy.Revision                = PLATFORM_GOP_POLICY_PROTOCOL_REVISION_02;
  mPlatformGOPPolicy.GetPlatformLidStatus    = GetPlatformLidStatus;
  mPlatformGOPPolicy.GetVbtData              = GetVbtData;
  mPlatformGOPPolicy.GetPlatformDockStatus   = GetPlatformDockStatus;

  //
  // Install protocol to allow access to this Policy.
  //
  Status = pBS->InstallMultipleProtocolInterfaces (
                  &ImageHandle,
                  &gPlatformGOPPolicyGuid,
                  &mPlatformGOPPolicy,
                  NULL
                  );

  //NbSetupdata Pass to SaGlobalNvsArea.
  Status = pBS->CreateEvent (
                  EFI_EVENT_NOTIFY_SIGNAL,
                  TPL_CALLBACK,
                  IntelGopVbtUpdateNotify,
                  NULL,
                  &DxePlatformSaPolicyEvent
                  );

  if (!EFI_ERROR (Status)) {
    Status = pBS->RegisterProtocolNotify (
                    &gDxePlatformSaPolicyGuid,
                    DxePlatformSaPolicyEvent,
                    &DxePlatformSaPolicyReg
                    );
  }


  NBPlatformData.IGFXGopAvailable = 1;

  // Save SETUP variables.
  //Status = pRS->SetVariable (                 // [ EIP167027 ]
  //  L"NBPlatformData",
  //  &gSetupGuid,
  //  EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS,
  //  sizeof (NB_PLATFORM_DATA),
  //  &NBPlatformData
  //  );
  Status = pRS->SetVariable (
    L"NBPlatformData",
    &gSetupGuid,
    Attributes,
    sizeof (NB_PLATFORM_DATA),
    &NBPlatformData
    );

  ASSERT_EFI_ERROR (Status);

  return Status;
}
//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
