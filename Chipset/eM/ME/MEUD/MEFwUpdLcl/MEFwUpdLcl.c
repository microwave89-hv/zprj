//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2015, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
#include <Token.h>
#include <AmiDxeLib.h>
#include <Protocol\Heci\Heci.h>
#include <Protocol\PchPlatformPolicy\PchPlatformPolicy.h>
#include <Protocol\PchReset\PchReset.h>
#include <Protocol\MeBiosPayloadData\MeBiosPayloadData.h>
#include <Protocol\Decompress.h>
#include <Protocol\GuidedSectionExtraction.h>
#include <Protocol\ConsoleControl.h>
#include <Protocol\AMIPostMgr.h>

#ifdef _HECI_PROTOCOL_H
//Broadwell RC
#include <Library\MeDxeLib.h>
#include <Library\MeChipsetLib.h>
#else
//Haswell RC
#undef EFI_PROTOCOL_DEFINITION
#define EFI_STRINGIZE(a)            #a
#define EFI_PROTOCOL_DEFINITION(a)  EFI_STRINGIZE (Protocol/a/a.h)
#include "HeciMsgLib.h"
#include "MeChipsetLib.h"
#endif

#include <Guid\FirmwareFileSystem2.h>


#include "IntelLib\FWUpdateLib.h"
#include "IntelLib\me_status.h"
#include "MeFwUpdLclProtocol.h"
#include "EdkIICommon.h"

_UUID   mOemId = {0x00000000, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

// Last Reset Types
#define NORESET 0
#define HOSTRESET  1
#define MERESET  2
#define GLOBALRESET 3

// Get Interface
#define FW_UPDATE_DISABLED 0
#define FW_UPDATE_ENABLED 1
#define FW_UPDATE_PASSWORD_PROTECTED 2

#ifdef _HECI_PROTOCOL_H
//Broadwell RC
typedef struct _PCH_PLATFORM_POLICY PRIVATE_PCH_PLATFORM_POLICY_PROTOCOL;
#else
//Haswell RC
typedef struct _DXE_PCH_PLATFORM_POLICY_PROTOCOL PRIVATE_PCH_PLATFORM_POLICY_PROTOCOL;
#define HECI_PROTOCOL EFI_HECI_PROTOCOL
#define MBP_DATA_PROTOCOL DXE_MBP_DATA_PROTOCOL
#define PCH_PLATFORM_POLICY_PROTOCOL_GUID DXE_PCH_PLATFORM_POLICY_PROTOCOL_GUID
#endif

#ifndef MAX_ADDRESS
#define MAX_ADDRESS 0xFFFFFFFF
#endif
#define ME_UPD_LCL_SIGNATURE SIGNATURE_32 ('_', 'M', 'U', 'L')

EFI_GUID mAmiGlobalVariableGuid = AMI_GLOBAL_VARIABLE_GUID;

EFI_GUID mEfiHeciProtocolGuid = HECI_PROTOCOL_GUID;
EFI_GUID mMeFwUpdLclProtocolGuid = ME_FW_UPD_LOCAL_PROTOCOL_GUID;
EFI_GUID mPchPlatformPolicyProtocolGuid = PCH_PLATFORM_POLICY_PROTOCOL_GUID;
EFI_GUID mPchResetProtocolGuid = PCH_RESET_PROTOCOL_GUID;
EFI_GUID mMeBiosPayloadDataProtocolGuid = ME_BIOS_PAYLOAD_DATA_PROTOCOL_GUID;
EFI_GUID mConOutStartedProtocolGuid = CONSOLE_OUT_DEVICES_STARTED_PROTOCOL_GUID;

EFI_GUID mMeRegionFfsGuid = \
{0xDE90FFA8, 0xB985, 0x4575, 0xAB, 0x8D, 0xAD, 0xE5, 0x2C, 0x36, 0x2C, 0xA3};

ME_FW_UPDATE_LOCAL_PROTOCOL             *mMeFwUpdateLclProtocol = NULL;
PRIVATE_PCH_PLATFORM_POLICY_PROTOCOL    *mPchPlatformPolicy = NULL;

EFI_BOOT_SERVICES   *BS = NULL;
EFI_RESET_SYSTEM    mSavedResetSystem = NULL;

ME_FW_UPD_VERSION   mMeFwImgVersion[] = ME_FW_IMAGE_VERSION;

void _fltused()
{
}

VOID *
SetMem (
    OUT VOID *Buffer,
    IN UINTN Length,
    IN UINT8 Value
)
{
    MemSet( Buffer, Length, Value);
    return Buffer;
}

INTN
EFIAPI
CompareMem (
  IN VOID  *DestinationBuffer,
  IN VOID  *SourceBuffer,
  IN UINTN       Length
  )
{
  return MemCmp( DestinationBuffer, SourceBuffer, Length );
}

VOID* AllocatePool(
    IN UINTN  AllocationSize)
{
    VOID *p;
    EFI_STATUS Status;

    Status = BS->AllocatePool(EfiBootServicesData, AllocationSize, &p);
    return (EFI_ERROR(Status)) ? NULL : p;
}

VOID FreePool(
    IN VOID   *Buffer)
{
    BS->FreePool(Buffer);
}

VOID *
EFIAPI
CopyMem (
  OUT     VOID                *Destination,
  IN      VOID                *Source,
  IN      UINTN               Length
  )
{
    MemCpy( Destination, Source, Length);
    return Destination;
}

VOID *
EFIAPI
ZeroMem (
  OUT VOID  *Buffer,
  IN UINTN  Length
  )
{
  ASSERT (!(Buffer == NULL && Length > 0));
  ASSERT (Length <= (MAX_ADDRESS - (UINTN)Buffer + 1));
  return SetMem (Buffer, Length, 0);
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   MeUpdPlatformUnlock
//
// Description:
//
// Input:
//
// Output:
//
// Returns:
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
MeUpdPlatformUnlock (
  IN ME_FW_UPDATE_LOCAL_PROTOCOL *This,
  IN UINT32                      UnlockType
)
{
    if( mPchPlatformPolicy != NULL )
#ifdef _HECI_PROTOCOL_H
        //Broadwell RC
        mPchPlatformPolicy->LockDownConfig.BiosLock = 0;
#else
        //Haswell RC
        mPchPlatformPolicy->LockDownConfig->BiosLock = 0;
#endif

    // Patch disabling IDE_R if ME is Disabled for system assert if DEBUG_MODE is ON.
    // The IDE-R device will be disabled if ME is in Normal state (HeciInit.c), 
    // Here ME is in ME_MODE_SECOVER, the IDE-R is active and could cause assert error
    // in IdeBus.Start proceduce.
    MeDeviceControl( IDER, Disabled );

    return EFI_SUCCESS;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   MeUpdPlatformReset
//
// Description:
//
// Input:
//
// Output:
//
// Returns:
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
MeUpdPlatformReset (
  IN ME_FW_UPDATE_LOCAL_PROTOCOL    *This,
  IN EFI_RESET_TYPE                 ResetType
)
{
    EFI_STATUS          Status;
    PCH_RESET_PROTOCOL  *PchReset;
    // Reset system to re-start ME FW..
    Status = pBS->LocateProtocol(
                    &mPchResetProtocolGuid,
                    NULL,
                    (VOID**)&PchReset);
    if( !EFI_ERROR(Status) )
        PchReset->Reset(PchReset, EfiResetCold);

    return EFI_SUCCESS;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   MeCheckFwState
//
// Description:
//
// Input:
//
// Output:
//
// Returns:
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
MeCheckFwState(
  IN ME_FW_UPDATE_LOCAL_PROTOCOL *This,
  IN ME_FW_STATE                 MeFwState
)
{
    EFI_STATUS          Status;
    UINT32              MeMode;
    HECI_PROTOCOL       *Heci = NULL;

    Status = pBS->LocateProtocol(
                    &mEfiHeciProtocolGuid, NULL, (VOID**)&Heci);
    if (EFI_ERROR(Status)) return EFI_UNSUPPORTED;
    Status = Heci->GetMeMode (&MeMode);
    if (EFI_ERROR(Status)) return EFI_UNSUPPORTED;
    if (((MeFwState == MeModeNormal) && (MeMode == ME_MODE_NORMAL)) || \
        ((MeFwState == MeModeDebug) && (MeMode == ME_MODE_DEBUG)) || \
        ((MeFwState == MeModeTempDisabled) && (MeMode == ME_MODE_TEMP_DISABLED)) || \
        ((MeFwState == MeModeSecOver) && (MeMode == ME_MODE_SECOVER)) || \
        ((MeFwState == MeModeFailed) && (MeMode == ME_MODE_FAILED))) return EFI_SUCCESS;
    return EFI_UNSUPPORTED;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   MeGetFwVersion
//
// Description:
//
// Input:
//
// Output:
//
// Returns:
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
MeGetFwVersion (
  IN     ME_FW_UPDATE_LOCAL_PROTOCOL *This,
  IN OUT ME_FW_UPD_VERSION           *MeFwVersion
)
{
    EFI_STATUS          Status;
    MBP_DATA_PROTOCOL   *MbpData;

    // Get ME Firmware Version from MBP, then save for future used.
    Status = pBS->LocateProtocol ( \
                &mMeBiosPayloadDataProtocolGuid, NULL, (VOID **)&MbpData);
    if (!EFI_ERROR (Status)) {
        MemCpy(MeFwVersion, \
                &MbpData->MeBiosPayload.FwVersionName, sizeof(ME_FW_UPD_VERSION)); 
    }    
    return Status;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   MeUpdHmrfpoEnable
//
// Description:
//
// Input:
//
// Output:
//
// Returns:
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
MeUpdHmrfpoEnable (
    ME_FW_UPDATE_LOCAL_PROTOCOL *This
)
{
    EFI_STATUS          Status;
    UINT8               HeciHmrfpoEnableResult;
    HeciHmrfpoEnableResult  = HMRFPO_ENABLE_UNKNOWN_FAILURE;
    Status                  = HeciHmrfpoEnable (0, &HeciHmrfpoEnableResult);
    if ((Status == EFI_SUCCESS) && (HeciHmrfpoEnableResult == HMRFPO_ENABLE_SUCCESS)) {
        /// (A6) The BIOS sends the GLOBAL RESET MEI message
        HeciSendCbmResetRequest (CBM_RR_REQ_ORIGIN_BIOS_POST, CBM_HRR_GLOBAL_RESET);
        MeUpdPlatformReset(This, EfiResetCold);
        //CpuDeadLoop();
        while(1);
    }    
    return Status;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   DisplaySendStatus
//
// Description:
//
// Input:
//      float     BytesSent
//      float     BytestobeSent
// Output:
//      None
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
void
DisplaySendStatus (
  float     BytesSent,
  float     BytestobeSent
  )
{
//    float   value = (BytesSent / BytestobeSent) * 100;
//    UINT32  pValue = (UINT32)value;
//
//    if (pValue != 100)
//    {
//        DEBUG ((D_ERROR, "Sending the update image to FW for verification:  [ %d%% ]\r", pValue));
//    }
//    else
//    {
//        DEBUG ((D_ERROR, "Sending the update image to FW for verification:  [ COMPLETE ] \n"));
//    }
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   FwUpdLclFunc
//
// Description: The main function to update ME firmware.
//              It will call Intel's API to update ME firmware.
//
// Input:
//      IN  ME_FW_UPDATE_LOCAL_PROTOCOL *This
//      IN  UINT8   *FileBuffer
//      IN  UINTN   FileLength
// Output:
//      None
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
FwUpdLclFunc (
    IN  ME_FW_UPDATE_LOCAL_PROTOCOL *This,
    IN  UINT8   *FileBuffer,
    IN  UINTN   FileLength
)
{
    EFI_STATUS          Status;
    UINTN               ImageLength = 0;
    UINT8               *ImageBuffer = NULL;
    UPDATE_FLAGS_LIB    update_flags;
    CHAR8               Password[9];
    UINT32              FWUpdateStatus;
    UINT32              QueryStatus;
    UINT32              UpdateStatus = 0;
    UINT32              TotalStages = 0;
    UINT32              PercentWritten = 0;
    UINT32              LastStatus;
    UINT32              LastResetType;
    UINT16              Interfaces;
    UINT8               Symbol;
    UINT32              Index;
    UINT32              CheckPolicyStatus = 0;
    BOOLEAN             AllowSV = FALSE;
    UPDATE_TYPE         UpdType;
    VersionLib          Ver;
    VOID                *DisplayHandle;
    AMI_POST_MGR_KEY    OutKey;

    BS = pBS;

    ImageBuffer = FileBuffer;
    ImageLength = FileLength;

    ZeroMem( &update_flags, sizeof(UPDATE_FLAGS_LIB) );

    Status = GetLastStatus( &LastStatus );
    if( EFI_ERROR(Status) )
    {
        return Status;
    }

    if( LastStatus == STATUS_UPDATE_HOST_RESET_REQUIRED )
    {
        //DEBUG ((D_ERROR, "PLEASE REBOOT YOUR SYSTEM. "));
        //DEBUG ((D_ERROR, "Firmware update cannot be initiated without a reboot.\n"));
        return EFI_SUCCESS;
    }

    if( IsUpdateStatusPending(LastStatus) )
    {
        //DEBUG ((D_ERROR, "Firmware Update operation not initiated "));
        //DEBUG ((D_ERROR, "because a firmware update is already in progress\n"));
        return EFI_SUCCESS;
    }

    Status = GetLastUpdateResetType( &LastResetType );
    if( EFI_ERROR(Status) ) return Status;
    switch( LastResetType )
    {
        case HOSTRESET:
        case GLOBALRESET:
            //DEBUG ((D_ERROR, "PLEASE REBOOT YOUR SYSTEM. "));
            //DEBUG ((D_ERROR, "Firmware update cannot be initiated without a reboot.\n"));
            return EFI_SUCCESS;
            break;
        default:
            break;
	}

    Status = GetInterfaces( &Interfaces );
    if( EFI_ERROR(Status) ) return Status;
    switch( Interfaces )
    {
        case FW_UPDATE_DISABLED:
            //DEBUG ((D_ERROR, "Local FWUpdate is Disabled\n"));
            return EFI_SUCCESS;
        case FW_UPDATE_PASSWORD_PROTECTED:
            //DEBUG ((D_ERROR, "Local FWUpdate is Password Protected\n"));
            break;
        case FW_UPDATE_ENABLED:
            break;
        default:
            break;
    }

    //DEBUG ((D_ERROR, "Checking firmware parameters...\n"));

    CheckPolicyStatus = CheckPolicyBuffer( (char *)ImageBuffer,
                                           (INT32)ImageLength,
                                           (INT32)AllowSV,
                                           &UpdType,
                                           &Ver );
    switch( UpdType )
    {
        case DOWNGRADE_SUCCESS:
        case SAMEVERSION_SUCCESS:
        case UPGRADE_SUCCESS:
            break;

        case DOWNGRADE_FAILURE:
            //DEBUG ((D_ERROR, "FW Update downgrade not allowed\n"));
            return EFI_SUCCESS;
            break;

        case SAMEVERSION_FAILURE:
            //DEBUG ((D_ERROR, "FW Update same version not allowed, specify /s on command line\n"));
            return EFI_SUCCESS;

        default:
            break;
    }

    ZeroMem( &Password, sizeof(Password) );

    if( This->AmiPostMgr != NULL )
    {
        This->AmiPostMgr->DisplayProgress(
                            AMI_PROGRESS_BOX_INIT,
                            L"ME FW update",
                            L"Flash New ME Firmware",
                            NULL,
                            0,
                            &DisplayHandle,
                            &OutKey );
    }
    
    FWUpdateStatus = FwUpdateFullBuffer(
                        (char*)ImageBuffer,
                        (unsigned int)ImageLength,
                        Password,
                        0,
                        FWU_ENV_MANUFACTURING,
                        mOemId,
                        update_flags,
                        &DisplaySendStatus );
    if( FWUpdateStatus != FWU_ERROR_SUCCESS )
    {
        //DEBUG ((D_ERROR, "FWUpdateStatus: %x\n", FWUpdateStatus));
        //if( ImageBuffer )
        //    FreePool( ImageBuffer );
        return EFI_SUCCESS;
    }

    //if( ImageBuffer )
    //{
    //    Status = FreePool( ImageBuffer );
    //}

    Index = 0;
    do
    {
        Symbol = (++Index % 2 == 0) ? '|':'-';
    
        QueryStatus = FWUpdate_QueryStatus_Get_Response(
                            &UpdateStatus,
                            &TotalStages,
                            &PercentWritten,
                            &LastStatus,
                            &LastResetType );
        if( QueryStatus == FWU_ERROR_SUCCESS )
        {
            //DEBUG ((D_ERROR, "FW Update:  [ %d%% (Stage: %d of %d) (%c)]\r",	PercentWritten, UpdateStatus, TotalStages, Symbol));
            if( This->AmiPostMgr != NULL )
            {
                This->AmiPostMgr->DisplayProgress(
                                    AMI_PROGRESS_BOX_UPDATE,
                                    L"ME FW update",
                                    L"Flash New ME Firmware",
                                    NULL,
                                    PercentWritten,
                                    &DisplayHandle,
                                    &OutKey );
            }
        }
        else if ( LastStatus != STATUS_UPDATE_NOT_READY )
        {
            //DEBUG ((D_ERROR, "\nLastStatus: %x\n", LastStatus));
            break;
        }
        BS->Stall(100000);
    } while( (PercentWritten != 100) && (QueryStatus == FWU_ERROR_SUCCESS) );

    if( This->AmiPostMgr != NULL )
    {
        This->AmiPostMgr->DisplayProgress(
                            AMI_PROGRESS_BOX_CLOSE,
                            L"ME FW update",
                            L"Flash New ME Firmware",
                            NULL,
                            0,
                            &DisplayHandle,
                            &OutKey );
    }

    return EFI_SUCCESS;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   MeFwUpdateProtocolEvent
//
// Description: The driver entry
//
// Input:
//
// Output:
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
MeFwUpdateProtocolEvent  (
    IN EFI_EVENT        Event,
    IN EFI_HANDLE       ImageHandle
    )
{
    UINT32              Dummy = 0;                            
    UINTN               VariableSize = sizeof(UINT8);   
    EFI_STATUS          Status;
    ME_FW_UPD_VERSION   MeFwVersion;

    if (mMeFwImgVersion->MajorVersion != 0) {
        Status = MeGetFwVersion(mMeFwUpdateLclProtocol, &MeFwVersion);
        if (!EFI_ERROR (Status)) {
            VariableSize = sizeof(ME_FW_UPD_VERSION);
            // Set MbpMeFwVersion to "NV+BS", because MBP could be not available if
            // Capsule Update mode.
            pRS->SetVariable(L"MbpMeFwVersion", \
                              &mAmiGlobalVariableGuid, \
                              EFI_VARIABLE_NON_VOLATILE | \
                              EFI_VARIABLE_BOOTSERVICE_ACCESS, \
                              sizeof(ME_FW_UPD_VERSION), \
                              &MeFwVersion);
        }
    }
    // Check "MeAutoUpdateReq" variable if ME Auto Update is requested. 
    VariableSize = sizeof(UINT32);
    Status = pRS->GetVariable(L"MeAutoUpdateReq", \
                    &mAmiGlobalVariableGuid, NULL, &VariableSize, &Dummy);
    if (EFI_ERROR(Status)) return EFI_SUCCESS;

    return EFI_SUCCESS;                                    
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   MEFwUpdLclEntry
//
// Description: The driver entry
//
// Input:
//      IN EFI_HANDLE           ImageHandle
//      OUT EFI_SYSTEM_TABLE    *SystemTable
// Output:
//      None
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
MEFwUpdLclEntry (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
    UINT32      Dummy;                            
    UINTN       VariableSize = sizeof(UINT32);
    EFI_HANDLE  pHandle = NULL;
    EFI_STATUS  Status;

    InitAmiLib( ImageHandle, SystemTable );

    Status = pBS->LocateProtocol(
                    &mPchPlatformPolicyProtocolGuid,
                    NULL,
                    &mPchPlatformPolicy );
    if( EFI_ERROR(Status) ) return EFI_SUCCESS;

    //Prepare ME firmware update local protocol
    Status = pBS->AllocatePool(
                    EfiBootServicesData,
                    sizeof(ME_FW_UPDATE_LOCAL_PROTOCOL),
                    (VOID**)&mMeFwUpdateLclProtocol );
    if( EFI_ERROR(Status) )
        return Status;

    mMeFwUpdateLclProtocol->FwUpdBufferAddress  = 0;
    mMeFwUpdateLclProtocol->FwUpdBufferLength   = 0;
    mMeFwUpdateLclProtocol->FwUpdLcl            = FwUpdLclFunc;
    mMeFwUpdateLclProtocol->MeFwCheckMode       = MeCheckFwState;
    mMeFwUpdateLclProtocol->MeFwGetVersion      = MeGetFwVersion;
    mMeFwUpdateLclProtocol->HmrfpoEnable        = MeUpdHmrfpoEnable;
    mMeFwUpdateLclProtocol->PlatformReset       = MeUpdPlatformReset;
    mMeFwUpdateLclProtocol->PlatformUnlock      = MeUpdPlatformUnlock;
    mMeFwUpdateLclProtocol->AmiPostMgr          = NULL;

    Status = pBS->InstallProtocolInterface( 
                    &pHandle,
                    &mMeFwUpdLclProtocolGuid,
                    EFI_NATIVE_INTERFACE,
                    mMeFwUpdateLclProtocol );

    MeFwUpdateProtocolEvent( NULL, NULL );

	Status = pRS->GetVariable(
                    L"MeAutoUpdateReq",
                    &mAmiGlobalVariableGuid,
                    NULL,
                    &VariableSize,
                    &Dummy );
    if( EFI_ERROR(Status) || (Dummy == ME_UPD_LCL_SIGNATURE) )
        return EFI_SUCCESS;

    return EFI_SUCCESS;
}
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2015, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
