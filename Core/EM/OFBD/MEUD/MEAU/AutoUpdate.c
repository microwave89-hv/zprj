//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
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
// $Header: /Alaska/SOURCE/Modules/OFBD Intel ME Update/AutoUpdate.c 3     10/04/11 5:08a Klzhan $
//
// $Revision: 3 $
//
// $Date: 10/04/11 5:08a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/OFBD Intel ME Update/AutoUpdate.c $
// 
// 3     10/04/11 5:08a Klzhan
// Support update OPR region with auto update.
// 
// 2     9/09/11 7:25a Klzhan
// Fix system hang issue.
// 
// 1     8/30/11 8:17a Klzhan
// 
//
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:    AutoUpdate.c
//
// Description:
//
//<AMI_FHDR_END>
//**********************************************************************
#include <AmiDxeLib.h>
#include <Protocol/ConsoleControl.h>
#include <Protocol/LoadedImage.h>
#include <Flash.h>
#include "AutoUpdate.h"
#include <Protocol/SimpleTextOut.h>
#include <Core\EM\OFBD\MEUD\MEUD.h>

UINT32 FlashCapacity;

EFI_GUID guidConsoleControl = EFI_CONSOLE_CONTROL_PROTOCOL_GUID;
EFI_GUID guidLoadedImage = EFI_LOADED_IMAGE_PROTOCOL_GUID;

//defined in Tokens.c
extern const UINT32 FlashBlockSize;

//defined in CSP_MEUD module
extern EFI_STATUS GET_FW_VERSION(
    UINT16 *MeFwVersionData
);
extern UINT32 GetHFS(VOID);

extern UINT32 GetFlashCapacity(VOID);

extern EFI_STATUS
GetRegionOffset(
    UINT8    Region,
    UINT32*  Offset,
    UINT32*  Length
);

extern OFBD_TC_55_ME_PROCESS_STRUCT  *StructPtr;

extern EFI_STATUS UpdateRegions(
    UINT8*    Buffer,
    BOOLEAN   InSmm
);

#define BDS_ALL_DRIVERS_CONNECTED_PROTOCOL_GUID \
 { 0xdbc9fd21, 0xfad8, 0x45b0, 0x9e, 0x78, 0x27, 0x15, 0x88, 0x67, 0xcc, 0x93 }
EFI_GUID    gBdsAllDriversConnectedProtocolGuid = \
                                    BDS_ALL_DRIVERS_CONNECTED_PROTOCOL_GUID;
EFI_GUID    gMEAUVariableGuid = MEAU_VAR_GUID;
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	NeedtoUpdate
//
// Description:	Check ME version.
//
// Input:
//      VOID
//
// Output:
//      TRUE - Update ME in this BOOT.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN
NeedtoUpdate(
    VOID
)
{
    ME_FW_VERSION   Image_MEversion = IMAGE_ME_FW_VERSION, CurrentMEVersion;
    EFI_STATUS      Status;

    if(REFLASH_UPDATE_FORCE)
    {
        UINTN    SetupVariableSize = 1;
        UINT8    Data8;
        Status = pRS->GetVariable (
                             L"MEAU",
                             &gMEAUVariableGuid,
                             NULL,
                             &SetupVariableSize,
                             &Data8);

        // Flag Not Found, just return TRUE
        if(Status == EFI_NOT_FOUND)
            return TRUE;
    }
    Status = GET_FW_VERSION((UINT16*)&CurrentMEVersion);

    if(EFI_ERROR(Status))
        return FALSE;

    // Check version
#if ME_UPDATE_DOWNGRADE
    // Downgrade allow, update when the version is different.
    if(MemCmp(&Image_MEversion, &CurrentMEVersion, sizeof(ME_FW_VERSION)) == 0)
        return FALSE;
    else
        return TRUE;
#else
    // Because parameters in ME verions are words
    // so check version in 2 parts
    if(ME_VERSION_VALUE(CurrentMEVersion) < ME_VERSION_VALUE(Image_MEversion))
        return TRUE;

    if((ME_VERSION_VALUE(CurrentMEVersion) == ME_VERSION_VALUE(Image_MEversion))
 && (ME_VERSION_VALUE1(CurrentMEVersion) < ME_VERSION_VALUE1(Image_MEversion)))
        return TRUE;

#endif

    return FALSE;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	GetRawImage
//
// Description:	Find ME binary in FV_MAIN.
//
// Input:
//      NameGuid - Guid of FFS need to find.
//      Buffer   - Input buffer
//      Size     - Size of Input buffer
//
// Output:
//      Status
//      Buffer   - FFS data
//      Size     - Size of Output buffer
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
GetRawImage (
  IN      EFI_GUID       *NameGuid,
  IN OUT  VOID           **Buffer,
  IN OUT  UINTN          *Size
  )

{
  EFI_STATUS                    Status;
  UINTN                         HandleCount;
  UINTN                         Index;
  EFI_FIRMWARE_VOLUME_PROTOCOL  *Fv;
  EFI_HANDLE                    *HandleBuff;
  UINT32                        AuthenticationStatus;

  Status = pBS->LocateHandleBuffer (
                  ByProtocol,
                  &gEfiFirmwareVolumeProtocolGuid,
                  NULL,
                  &HandleCount,
                  &HandleBuff
                  );

  if (EFI_ERROR (Status) || HandleCount == 0) {
    return EFI_NOT_FOUND;
  }
  //
  // Find desired image in all Fvs
  //
  for (Index = 0; Index < HandleCount; Index++) {
    Status = pBS->HandleProtocol (
                    HandleBuff[Index],
                    &gEfiFirmwareVolumeProtocolGuid,
                    &Fv
                    );

    if (EFI_ERROR (Status)) {
      if (HandleBuff != NULL) {
        pBS->FreePool (HandleBuff);
      }

      return EFI_LOAD_ERROR;
    }
    //
    // Try a raw file
    //
    Status = Fv->ReadSection (
                  Fv,
                  NameGuid,
                  EFI_SECTION_RAW,
                  0,
                  Buffer,
                  Size,
                  &AuthenticationStatus
                  );

    if (!EFI_ERROR (Status)) {
      break;
    }
  }

  if (HandleBuff != NULL) {
    pBS->FreePool (HandleBuff);
  }

  if (Index >= HandleCount) {

    return EFI_NOT_FOUND;
  }

  return EFI_SUCCESS;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ProgressMEUpdate
//
// Description:	Do ME update
//
// Input:
//      NameGuid - Guid of FFS need to find.
//      Buffer   - Input buffer
//      Size     - Size of Input buffer
//
// Output:
//      Status
//      Buffer   - FFS data
//      Size     - Size of Output buffer
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
ProgressMEUpdate(
    IN UINT8*  Buffer,
    IN UINTN   Size
)
{
    EFI_STATUS Status;
    UINTN    SetupVariableSize;
    UINT8    Data8 = 0;
    UINT32   TempReg, i;
    OFBD_TC_55_ME_PROCESS_STRUCT  MEProcessStructPtr;
    CHAR8    String[256];
    CHAR8*   StringBuffer = String;
    CHAR16   wString[256];

    // Init Global variable
    MEProcessStructPtr.ddMessageBuffer = (UINT32)StringBuffer;
    StructPtr = &MEProcessStructPtr;

    FlashCapacity = GetFlashCapacity();
    if((Size) != FlashCapacity)
        return;

#ifdef CSP_MEUD_SUPPORT
#if CSP_MEUD_SUPPORT == 1
    // For Desktop and Mobile
    if (((GetHFS() >> 16) & 0x0F) == 0)
        IoWrite8(SW_SMI_IO_ADDRESS, Disable_ME_SW_SMI);
    // Comes here, System should be in Disabled mode.
    // If not, just return
    if (((GetHFS() >> 16) & 0x0F) != 5)
        return;
#endif
#endif

    // Get ME Region.
    if(REFLASH_UPDATE_ME)
    {
        // Prepare Buffer
        if(DIRECT_FW_UPDATE)
            StructPtr->bBlockType = ME_OPR_BLK;
        else
            StructPtr->bBlockType = ME_BLK;

        StructPtr->bHandleRequest = BIT02;

        pST->ConOut->OutputString (pST->ConOut,
                    L"ME is updated now ... \r\n");

        pST->ConOut->OutputString (pST->ConOut,
                    L"Please don't shut down or reset system \r\n");

        do{
            Status = UpdateRegions(Buffer, FALSE);
            // Request to continue
            if((StructPtr->UpdateResult & BIT01))
                StructPtr->bHandleRequest = BIT03;

            // Show string
            if((StructPtr->UpdateResult & BIT02))
            {
                StructPtr->bHandleRequest = BIT03;
                MemSet(wString, 512, 0);
                for(i = 0 ; String[i] ; (CHAR8)wString[i] = String[i], i++);
                wString[i] = 0;
                pST->ConOut->OutputString (pST->ConOut,wString);
                pST->ConOut->OutputString (pST->ConOut,L"\r\n");
            }
            // End
            if((StructPtr->UpdateResult & BIT03))
                break;
            // TODO : Error Handle
        }while(1);
    }

    if(REFLASH_UPDATE_GBE)
    {
        // Prepare Buffer
        StructPtr->bBlockType = GBE_BLK;
        StructPtr->bHandleRequest = BIT02;

        pST->ConOut->OutputString (pST->ConOut,
                    L"GBE region is updated now ... \r\n");

        Status = UpdateRegions(Buffer, FALSE);

        // Show string
        if((StructPtr->UpdateResult & BIT02))
        {
            StructPtr->bHandleRequest = BIT03;
            MemSet(wString, 512, 0);
            for(i = 0 ; String[i] ; (CHAR8)wString[i] = String[i], i++);
            wString[i] = 0;
            pST->ConOut->OutputString (pST->ConOut,wString);
            pST->ConOut->OutputString (pST->ConOut,L"\r\n");
        }
    }

    if(REFLASH_UPDATE_MEDS)
    {
        // Prepare Buffer
        StructPtr->bBlockType = GBE_BLK;
        StructPtr->bHandleRequest = BIT02;

        pST->ConOut->OutputString (pST->ConOut,
                    L"GBE region is updated now ... \r\n");

        Status = UpdateRegions(Buffer, FALSE);

        // Show string
        if((StructPtr->UpdateResult & BIT02))
        {
            StructPtr->bHandleRequest = BIT03;
            MemSet(wString, 512, 0);
            for(i = 0 ; String[i] ; (CHAR8)wString[i] = String[i], i++);
            wString[i] = 0;
            pST->ConOut->OutputString (pST->ConOut,wString);
            pST->ConOut->OutputString (pST->ConOut,L"\r\n");
        }
    }

    // Update Finish, update Flag
    if(REFLASH_UPDATE_FORCE)
    {
        SetupVariableSize = 1;
        Status = pRS->SetVariable (
                             L"MEAU",
                             &gMEAUVariableGuid,
                             EFI_VARIABLE_NON_VOLATILE
                             | EFI_VARIABLE_BOOTSERVICE_ACCESS
                             | EFI_VARIABLE_RUNTIME_ACCESS,
                             SetupVariableSize,
                             &Data8);
    }
    // Reset System and ME
    IoWrite32(0xCF8, 0x8000F8AC);
    TempReg = IoRead32(0xCFC);

    if(!(TempReg & BIT20))
    {
        IoWrite32(0xCF8, 0x8000F8AC);
        IoWrite32(0xCFC, TempReg | BIT20);
    }

    pRS->ResetSystem( EfiResetCold, EFI_SUCCESS, 0, NULL );
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MEAutoUpdate
//
// Description:	System updaete ME in POST.
//
// Input:
//      VOID
//
// Output:
//      VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
MEAutoUpdate(
    VOID
)
{
    UINTN                     Size;
    EFI_PHYSICAL_ADDRESS      ImageLocation;
    UINT8*                    ImageBuffer;
    EFI_STATUS                Status;
    EFI_GUID                  gMEUDfileguid = MEUD_FILE_GUID;

    if(!NeedtoUpdate())
        return EFI_SUCCESS;


    Size = ME_UPDATE_BINARY_SIZE * 0x100000 / 0x1000;
    Status = pBS->AllocatePages (
              AllocateAnyPages,
              EfiBootServicesData, 
              Size,
              &ImageLocation );

    ImageBuffer = (UINT8*)ImageLocation;

    if(EFI_ERROR(Status))
      return Status;

    Size = Size * 0x1000;
    Status = GetRawImage (&gMEUDfileguid, &ImageBuffer, &Size);

    ProgressMEUpdate(ImageBuffer, Size);

    pBS->FreePages(ImageLocation, Size );

    return EFI_SUCCESS;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   AllDriverConnectEvent
//
// Description: This routine for reset the TPM Establishment flag.
//
// Input:       EFI_EVENT   - Efi event.
//              VOID*       - Image handle.
//
// Output:      None.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
MEAUAllDriverConnectEvent  (
    IN EFI_EVENT Event,
    IN VOID      *Context
)
{
    MEAutoUpdate();
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ReFlashEntry
//
// Description: This is the standard EFI driver entry point called for
//              Recovery flash module initlaization
// Input:       IN EFI_HANDLE ImageHandle - ImageHandle of the loaded driver
//              IN EFI_SYSTEM_TABLE SystemTable - Pointer to the System Table
//
// Output:      EFI_SUCCESS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS AUTOUPDEntry (IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable)
{
    EFI_STATUS   Status;
    EFI_EVENT    AllDriverConnectEvent;
    VOID         *Registration;


    InitAmiLib(ImageHandle,SystemTable);

    //---Set up Callback----------------
    Status = RegisterProtocolCallback ( &gBdsAllDriversConnectedProtocolGuid, \
                                        MEAUAllDriverConnectEvent, \
                                        NULL, \
                                        &AllDriverConnectEvent, \
                                        &Registration   );

    return EFI_SUCCESS;
}
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************