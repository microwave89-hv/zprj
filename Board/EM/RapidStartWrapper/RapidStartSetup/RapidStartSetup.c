//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
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
// $Header: /Alaska/SOURCE/Modules/Intel Fast Flash Standby/iRST_SharkBay/RapidStartWrapper/RapidStartSetup/RapidStartSetup.c 4     7/16/14 5:14a Joshchou $
//
// $Revision: 4 $
//
// $Date: 7/16/14 5:14a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/Intel Fast Flash Standby/iRST_SharkBay/RapidStartWrapper/RapidStartSetup/RapidStartSetup.c $
// 
// 4     7/16/14 5:14a Joshchou
// [TAG]  		EIP177828
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	Restore Defaults on setup cannot set the SATA mode to
// default.
// [RootCause]  	When action == EFI_BROWSER_ACTION_DEFAULT_STANDARD.
// Need to return unsupported.
// [Solution]  	Add the judgement when action ==
// EFI_BROWSER_ACTION_DEFAULT_STANDARD.
// 
// 3     7/11/14 4:08a Joshchou
// [TAG]  		EIP176979
// [Category]  	Improvement
// [Description]  	Change "#else if" to "#elif".
// 
// 2     1/13/13 7:48a Bensonlai
// [TAG]  		EIPNone
// [Category]  	Improvement
// [Description]  	Disabling the RapidStart while STAT mode in the IDE
// mode
// [Files]  		RapidStartDxePolicyInit.c, RapidStartDxePolicyInit.h,
// RapidStartDxePolicyInit.mak, RapidStartSetup.c, RapidStartSetup.mak,
// RapidStartSetup.sd, RapidStartSetup.sdl
// 
// 1     10/15/12 4:42a Bensonlai
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	[Category] Improvement
// [Severity] Important
// [Description] Rename all IFFS sting to Rapid Start.
// [Files] Board\EM\RapidStartWrapper\*.*, ReferenceCode\RapidStart\*.*
// [Files]  		RapidStartSetup.cif
// RapidStartSetup.sdl
// RapidStartSetup.mak
// RapidStartSetup.sd
// RapidStartSetup.uni
// RapidStartSetup.c
// RapidStartSetup.h
// RapidStartSetupReset.c
//
//**********************************************************************
//<AMI_FHDR_START>
//
// Name: RapidStartSetup.c
//
// Description: Create the setup item for RapidStart.
//
//<AMI_FHDR_END>
//**********************************************************************

#include <token.h>
#include <Setup.h>
#include <SetupStrTokens.h>
#include "RapidStartSetup.h"
#include <AmiCspLib.h>
#include <AmiDxeLib.h>
#if EFI_SPECIFICATION_VERSION>0x20000
#include <Protocol\HiiDatabase.h>
#include <Protocol\HiiString.h>
#else
#include <Protocol/Hii.h>
#endif

#if defined RAPID_START_PARTITION_DETECT_MODE && RAPID_START_PARTITION_DETECT_MODE == 1

#define RAPID_START_PARTITION_STATUS_PROTOCOL_GUID \
  { \
    0x65639144, 0xd492, 0x4328, 0xa4, 0x98, 0xf4, 0xb5, 0x54, 0x5e, 0x4a, 0x30 \
  }

#else

#define RAPID_START_PERSISTENT_DATA_GUID \
  { \
    0xf9f0b131, 0xf346, 0x4f16, 0x80, 0xdd, 0xf9, 0x41, 0x07, 0x2b, 0x3a, 0x7d \
  }

EFI_GUID gRapidStartPersistentDataGuid = RAPID_START_PERSISTENT_DATA_GUID;

typedef struct {
    UINT32  RapidStartMem;
    UINT32  MmioSpace;
    UINT32  RapidStartGlobalNvsPtr;
    UINT32  StoreSectors;
    UINT64  StoreLbaAddr;
    UINT8   StoreSataPort;
    UINT8   SataPortConfiguration;
    UINT32  Tolm;
    UINT64  Tohm;
    UINT64  TotalMem;
    UINT32  RapidStartMemSize;
    UINT32  ZeroBitmapSize;
    UINT32  WlanMmioSpace;
    UINT64  SystemMemoryLengthBelow4GB;
    UINT64  SystemMemoryLengthAbove4GB;
    UINT64  AcpiReservedMemoryBase;
    UINT32  AcpiReservedMemorySize;
    UINT32  Crc32RecordSize;
    UINT64  RapidStartStoreUid;
    UINT32  ActivePageThresholdSizeInSector;
} RAPID_START_PERSISTENT_DATA;

#endif


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   InitRapidStartInfo
//
// Description: Initializes Intel Rapid Start Technology (RapidStart) Setup String
//
// Input:       HiiHandle - Handle to HII database
//              Class - Indicates the setup class
//
// Output:      None
//
// Notes:       PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
InitRapidStartInfo(
    IN EFI_HII_HANDLE   HiiHandle,
    IN UINT16           Class
)
{
    return;
}

EFI_STATUS
EFIAPI
RapidStartMenuEntry (
    IN EFI_HII_HANDLE HiiHandle,
    IN UINT16         Class,
    IN UINT16         SubClass,
    IN UINT16         Key
)
{
    EFI_STATUS            Status;
    CALLBACK_PARAMETERS   *pCallbackData = NULL;
    SETUP_DATA            *SetupData = NULL;
    UINTN                 BufferSize = sizeof(SETUP_DATA);
    EFI_GUID              SetupGuid = SETUP_GUID;
#if defined RAPID_START_PARTITION_DETECT_MODE && RAPID_START_PARTITION_DETECT_MODE == 1
    VOID                  *Empty;
    EFI_GUID              RapidStartPartitionProtocolGuid = RAPID_START_PARTITION_STATUS_PROTOCOL_GUID;
#else
    UINTN                 VariableSize = sizeof(RAPID_START_PERSISTENT_DATA);
    RAPID_START_PERSISTENT_DATA  RapidStartData;
#endif
    PCH_SERIES            PchSeries = GetPchSeries();;

    pCallbackData = GetCallbackParameters();
    if (pCallbackData == NULL) return EFI_SUCCESS;

    if(pCallbackData->Action == EFI_BROWSER_ACTION_DEFAULT_STANDARD) return EFI_UNSUPPORTED;

    if (pCallbackData->Action == EFI_BROWSER_ACTION_FORM_OPEN) {
#if defined RAPID_START_PARTITION_DETECT_MODE && RAPID_START_PARTITION_DETECT_MODE == 1
        Status = pBS->LocateProtocol ( &RapidStartPartitionProtocolGuid,
                                       NULL,
                                       &Empty );
#else
        Status = pRS->GetVariable ( L"RapidStartData",
                                    &gRapidStartPersistentDataGuid,
                                    NULL,
                                    &VariableSize,
                                    &RapidStartData );
#endif
        if (!EFI_ERROR(Status)) {
            // If RapidStart Persistent Data or RAPID_START_PARTITION_STATUS_PROTOCOL_GUID is exist,
            // hidng the warning message.
            InitString( HiiHandle, \
                        STRING_TOKEN(STR_RAPIDSTART_PAR_STATUS_PROMPT), \
                        L"");
        }
    }

    // Check callback action
#if ((TSE_BUILD >= 0x1224) && (EFI_SPECIFICATION_VERSION >= 0x2000A))
    if (pCallbackData->Action != EFI_BROWSER_ACTION_CHANGED)
        return EFI_SUCCESS;
#elif ((TSE_BUILD > 0x1208) && (EFI_SPECIFICATION_VERSION >= 0x2000A))
    if (pCallbackData->Action != EFI_BROWSER_ACTION_CHANGING)
        return EFI_SUCCESS;
#endif

    Status = pBS->AllocatePool(EfiBootServicesData, BufferSize, &SetupData);

    Status = HiiLibGetBrowserData( &BufferSize, SetupData, &SetupGuid, L"Setup" );

    if (PchSeries == PchLp) {
        if (SetupData->ULTSataInterfaceMode == 0) {
             SetupData->RapidStartEnabled = 0;
        }
    } else {
        if (SetupData->SataInterfaceMode == 0) {
            SetupData->RapidStartEnabled = 0;
        }
    }

    Status = HiiLibSetBrowserData( BufferSize, SetupData, &SetupGuid, L"Setup" );

    pBS->FreePool(SetupData);


    return EFI_SUCCESS;
}
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
