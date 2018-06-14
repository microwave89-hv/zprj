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
// $Header: /Alaska/SOURCE/Modules/TCG2/Common/TcgLegacy/TcgLegacy.c 2     6/14/14 12:35a Fredericko $
//
// $Revision: 2 $
//
// $Date: 6/14/14 12:35a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/TCG2/Common/TcgLegacy/TcgLegacy.c $
// 
// 2     6/14/14 12:35a Fredericko
// 
// 1     4/21/14 2:17p Fredericko
// 
// 1     10/08/13 12:04p Fredericko
// Initial Check-In for Tpm-Next module
// 
// 2     10/03/13 3:07p Fredericko
// 
// 1     7/10/13 5:56p Fredericko
// [TAG]  		EIP120969
// [Category]  	New Feature
// [Description]  	TCG (TPM20)
// 
// 7     4/05/11 8:06p Fredericko
// TCG Legacy IO support changes
// 
// 6     3/31/11 4:58p Fredericko
// Changes for TCG_LEGACY support
// 
// 5     3/29/11 1:28p Fredericko
// 
// 4     3/28/11 3:38p Fredericko
// [TAG]        EIP 54642
// [Category] Improvement
// [Description] 1. Checkin Files related to TCG function override 
// 2. Include TCM and TPM auto detection
// [Files] Affects all TCG files
// 
// 3     7/14/10 2:56p Fredericko
// Included logic to update the CSM16 Table checksum.
// 
// 2     5/20/10 8:56a Fredericko
// Included File Header
// Code Beautification
// EIP 37653
//
// 1     3/23/10 7:57p Fredericko
//
// 21    3/19/10 4:20p Fredericko
// modified for legacy IO interface support
//
// 20    12/31/09 2:36p Fredericko
// Update Location of BevBcv function after legacy init call
//
// 19    11/19/09 4:13p Fredericko
// Update last event for legacy efi aspect of boot
//
// 18    11/09/09 5:26p Fredericko
// Changes for Memory Leak EIP 28575
//
// 17    6/02/09 2:38p Fredericko
//
// 16    6/01/09 4:15p Fredericko
// Changes added for TCM_SUPPORT
//
// 15    4/30/09 6:15p Fredericko
// Updated Header Date
//
// 14    4/30/09 5:32p Fredericko
//  AMI company Header Address changes
//
// 13    4/03/09 6:13p Fredericko
// Coding standard changes
//
// 12    3/05/09 2:59p Fredericko
//
// 11    2/05/09 5:23p Fredericko
// Use Trace instead of Debug for debug messages, Removed EDK headers
// included and "gbs" changed to "pBS"
//
// 10    2/27/08 5:52p Fredericko
// Tcg Specification Compliance changes
//
// 9     9/26/07 2:45p Fredericko
// Build in TRACE mode fixes
//
// 8     9/04/07 6:07p Fredericko
// Changes made for new compiler swtich "\W4" to work
//
// 7     9/04/07 10:19a Fredericko
// Measuring Embedded PciROM pointer fixes.
//
// 6     6/13/07 5:17p Fredericko
// Function to read embedded option ROMS
//
// 5     11/03/06 6:34p Andriyn
//
// 4     8/15/06 9:28a Andriyn
//
// 3     6/22/06 3:03p Andriyn
//
// 2     6/20/06 7:13p Andriyn
// Changes due to protocols moved to MiscFramework
//
// 1     6/20/06 5:58p Andriyn
//**********************************************************************
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:  TcgLegacy.c
//
// Description:
// Contains functions that handle setting up the handoff between EFI and Legacy
//
//<AMI_FHDR_END>
//*************************************************************************
#include <EFI.h>
#include "TcgLegacy.h"
#include "token.h"
#include "TCGMisc.h"
#include <Protocol\LegacyRegion.h>
#include "TcgCommon.h"
#include "protocol\TcgService\TcgTcmService.h"
#include "protocol\TcgService\TcgService.h"
#include "protocol\TpmDevice\TpmDevice.h"
#include <Protocol\FirmwareVolume.h>
#include <Protocol\LegacyBios.h>
#include <AmiDxeLib.h>
#include <Tpm20Includes\TrEEProtocol.h>


EFI_GUID  gEfiAmiTcgWakeEventDataHobGuid = EFI_TCG_WAKE_EVENT_DATA_HOB_GUID;
EFI_GUID  gEfiAmiHobListGuid     = TCG_EFI_HOB_LIST_GUID;
EFI_GUID  gEfiAmiTcgLogHobGuid   = EFI_TCG_LOG_HOB_GUID;
EFI_GUID  gEfiIntTcgProtocolGuid = EFI_TCG_PROTOCOL_GUID;



#define  GUID_VARIABLE_DECLARATION( Variable, Guid ) extern EFI_GUID Variable
EFI_GUID gEfiAmiTHobListGuid = TCG_EFI_HOB_LIST_GUID;

#include "TcgPc.h"

void* AllocateRTMemory (
    UINTN size );

EFI_GUID  TCGLEGX16_FILE_GUID
 = {0x142204e2, 0xc7b1, 0x4af9, 0xa7, 0x29, 0x92, 0x37, 0x58, 0xd9, 0x6d, 0x3};

EFI_GUID  TPM32_FILE_GUID = 
   {0xaa31bc6, 0x3379, 0x41e8, 0x82, 0x5a, 0x53, 0xf8, 0x2c, 0xc0, 0xf2, 0x54};

EFI_GUID  MPTPM_FILE_GUID
  ={0x7d113aa9, 0x6280, 0x48c6, 0xba, 0xce, 0xdf, 0xe7, 0x66, 0x8e, 0x83, 0x7};

EFI_GUID  TCMLEGX16_FILE_GUID
 = {0x1E753E16, 0xDCEF, 0x47d0, 0x9A, 0x38, 0x7A, 0xDE, 0xCD, 0xB9, 0x83, 0xED};

EFI_GUID  TCM32_FILE_GUID = 
   {0xB74E676E,0x3B2E, 0x483f, 0x94, 0x58, 0xC3, 0x78, 0xFE, 0x0A, 0xC6, 0x9F};


EFI_GUID  gEfiLegacyRegionProtocol = EFI_LEGACY_REGION_PROTOCOL_GUID;

#define GET_HOB_TYPE( Hob )     ((Hob).Header->HobType)
#define GET_HOB_LENGTH( Hob )   ((Hob).Header->HobLength)
#define GET_NEXT_HOB( Hob )     ((Hob).Raw + GET_HOB_LENGTH( Hob ))
#define END_OF_HOB_LIST( Hob )  (GET_HOB_TYPE( Hob ) == \
                                 EFI_HOB_TYPE_END_OF_HOB_LIST)

static TPM32HEADER      * installedTpm32 = 0;
static EFI_TCG_PROTOCOL * gTcgProtocol   = 0;
extern TCG_ACPI_TABLE   mTcgAcpiTableTemplate;
UINT8                   Tpm20Support = 0;


#define _CR( Record, TYPE,\
       Field )((TYPE*) ((CHAR8*) (Record) - (CHAR8*) &(((TYPE*) 0)->Field)))

#define TCG_DXE_PRIVATE_DATA_FROM_THIS( This )  \
    _CR( This, TCG_DXE_PRIVATE_DATA, TcgServiceProtocol )

#define TCM_DXE_PRIVATE_DATA_FROM_THIS( This )  \
    _CR( This, TCM_DXE_PRIVATE_DATA, TcgServiceProtocol )

typedef struct _TCG_DXE_PRIVATE_DATA
{
    EFI_TCG_PROTOCOL        TcgServiceProtocol;
    EFI_TPM_DEVICE_PROTOCOL *TpmDevice;
} TCG_DXE_PRIVATE_DATA;

typedef struct _TCM_DXE_PRIVATE_DATA
{
    EFI_TCM_PROTOCOL        TcgServiceProtocol;
    EFI_TPM_DEVICE_PROTOCOL *TpmDevice;
} TCM_DXE_PRIVATE_DATA;

#pragma pack (1)
typedef struct _TCG_PCR_EVENT_HDR2 {
  TCG_PCRINDEX                      PCRIndex;
  TCG_EVENTTYPE                     EventType;
} TCG_PCR_EVENT_HDR2;
#pragma pack()

EFI_TREE_PROTOCOL          *TrEEProtocolInstance = NULL;
#define                     MAX_LOG_AREA_SIZE (32 * 1024) 


#define SEG_ALIGNMENT    0x10


void TcgLogEventProxy(
    TCG_PCR_EVENT* data )
{
    UINT32 n;

    gTcgProtocol->LogEvent( gTcgProtocol, data, &n, 0x01 );
}

void TreeLogEventProxy(
    TCG_PCR_EVENT* data )
{
    return; //unsupported   
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   linkTPMDriver
//
// Description: Establishes link used to synchronize change to the
//              LOG when done through the INT1A interface while DXE is still in
//              control.
//
//
// Input:       IN     EFI_PEI_SERVICES  **PeiServices,
//
// Output:      EFI STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************
void linkTPMDriver(
    IN OUT TPM32HEADER  * tpm32,
    IN EFI_TCG_PROTOCOL *tcgProtocol )
{
    TCG_LOG_HOB                         *TcgLog;
    TCG_EFI_BOOT_SERVICE_CAPABILITY     Cap;
    EFI_PHYSICAL_ADDRESS                EventLogLoc;
    EFI_PHYSICAL_ADDRESS                LastEv;
    BOOLEAN                             IsTrancated;
    EFI_STATUS                          Status;

    gTcgProtocol = tcgProtocol;

    tpm32->lastEventShadow   = 0;
    tpm32->ptrOnTPMFailue    = 0;

    if(Tpm20Support == 0)
    {
        tpm32->efi_log_event_ptr =  (UINTN) (void*)(UINTN)TcgLogEventProxy;

        gTcgProtocol->StatusCheck( gTcgProtocol, &Cap, NULL, &EventLogLoc, &LastEv );
        TcgLog = (TCG_LOG_HOB*)(UINTN)EventLogLoc;
        TcgLog--;

        TRACE((TRACE_ALWAYS, "\n\n linkTPMDriver: TCGLOG( %x )\n", TcgLog));


        tpm32->log.memptr      = (UINT32)( UINTN ) EventLogLoc;
        tpm32->log.dwSize      = TcgLog->TableMaxSize;
        tpm32->lastEventShadow = 0;
    }else{
        if(TrEEProtocolInstance ==NULL) return;

        tpm32->efi_log_event_ptr =  (UINTN) (void*)(UINTN)TreeLogEventProxy;
        
        Status = TrEEProtocolInstance->GetEventLog(TrEEProtocolInstance, TREE_BOOT_HASH_ALG_SHA1,\
                                           &EventLogLoc, &LastEv, &IsTrancated);
        tpm32->lastEventShadow   = 0;
        tpm32->ptrOnTPMFailue    = 0;
        
        tpm32->log.memptr      = (UINT32)( UINTN ) EventLogLoc;
        tpm32->log.dwSize      = MAX_LOG_AREA_SIZE;
        tpm32->lastEventShadow = 0;
        
    }
}


UINT32 CountEvents(EFI_PHYSICAL_ADDRESS  TcgLog, UINTN Eventlast, UINT8 HashPolicy)
{
    TCG_PCR_EVENT_HDR2 *TcgLogNext = (TCG_PCR_EVENT_HDR2 *)TcgLog;
    UINTN   NextLoc =0;
    UINT32  EventSize=0;
    UINTN  *ValidCheck;
    UINTN  *ValidCheckNext;
    UINT32  EventCount=0;
    UINTN i=0;

    ValidCheck = (UINTN *)TcgLog;
    ValidCheckNext = ValidCheck + 1;

    if(TcgLogNext == NULL) return EventCount;
    if((UINTN)ValidCheck > Eventlast) return EventCount;
    if(*ValidCheck == 0 && *ValidCheckNext == 0)return EventCount;
    
    if(HashPolicy == 0)
    {
        //return the location of the next log
        while((UINTN)ValidCheck <= Eventlast)
        {   
            
            ValidCheckNext = ValidCheck + 1;
            if(*ValidCheck == 0 && *ValidCheckNext == 0)break;     

            if(TcgLogNext->PCRIndex < 0)break;   
            EventSize = *(UINT32 *)(((UINTN)TcgLogNext) + TPM_SHA1_160_HASH_LEN + sizeof(TCG_PCR_EVENT_HDR2));
            NextLoc =  (UINTN)(((UINTN)TcgLogNext)+ EventSize + sizeof(EventSize)+\
                            + TPM_SHA1_160_HASH_LEN + sizeof(TCG_PCR_EVENT_HDR2));

            TcgLogNext = (TCG_PCR_EVENT_HDR2  *)NextLoc;
            ValidCheck = (UINTN *)NextLoc;
            EventCount+=1;
        
        }
    }else{
        //unsupported SHA1 only for now        
    }

    return (EventCount);
}




//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   UnlinkTPM32fromEFI
//
// Description: Breaks the link that exist between TPM32 code and DXE TCG
//              driver. The established link was used to synchronize change to the
//              LOG when done through the INT1A interface while DXE is still in
//              control. Need to break this link one DXE driver is stoped or EFI
//              boots OS ( including calling INT19)
//
//
// Input:       IN     EFI_EVENT  Event,
//              IN       VOID     *Context
//
// Output:      EFI STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS EFIAPI UnlinkTPM32fromEFI(
    IN EFI_EVENT Event,
    IN VOID      *Context )
{
    TCG_LOG_HOB                     *TcgLog;
    TPM32HEADER                     * tpm32 = (TPM32HEADER*)Context;
    EFI_PHYSICAL_ADDRESS            logStart,         logLast;
    TCG_EFI_BOOT_SERVICE_CAPABILITY TcgCapability;
    BOOLEAN                         IsTrancated;
    EFI_STATUS                      Status;
    UINT32                          FreeLogSize;
    SHA1_PCR_EVENT                   *PtrtoLastEvent;

    if ( installedTpm32 == 0 )
    {
      return EFI_SUCCESS; 
    }
    
    if(Tpm20Support == 0)
    {
        ASSERT( installedTpm32 == tpm32 );
        TRACE((TRACE_ALWAYS, "UnlinkTPM32fromEFI: TPM32( %x )\n", tpm32));
        installedTpm32 = 0;

        tpm32->lastEventShadow   = 0;
        tpm32->efi_log_event_ptr = 0;
        Status                   = gTcgProtocol->StatusCheck( gTcgProtocol,
                                                          &TcgCapability,
                                                          NULL,
                                                          &logStart,
                                                          &logLast );

        if ( EFI_ERROR( Status ))
        {
            tpm32->last    = 0;
            tpm32->freelog = 0;
            return Status;
        }
        TcgLog = (TCG_LOG_HOB*)(UINTN)logStart;
        TcgLog--;

        tpm32->last       = (UINT32)( UINTN ) ( logLast - logStart );
        tpm32->TPMAcDeact = TcgCapability.TPMDeactivatedFlag;
        tpm32->freelog    = TcgLog->TableSize;
        tpm32->nextevent  = TcgLog->EventNum + 1;

        tpm32->Tpm20Enabled = 0;
    }else{

        ASSERT( installedTpm32 == tpm32 );
        TRACE((TRACE_ALWAYS, "UnlinkTPM32fromEFI: TPM32( %x )\n", tpm32));
        installedTpm32 = 0;

        if(TrEEProtocolInstance ==NULL) return EFI_SUCCESS;
       
        Status = TrEEProtocolInstance->GetEventLog(TrEEProtocolInstance, TREE_BOOT_HASH_ALG_SHA1,\
                                           &logStart, &logLast, &IsTrancated);
        tpm32->lastEventShadow   = 0;
        tpm32->ptrOnTPMFailue    = 0;
       
        tpm32->lastEventShadow   = 0;
        tpm32->efi_log_event_ptr = 0;
        
        tpm32->last       = (UINT32)( UINTN ) ( logLast );
        tpm32->TPMAcDeact = 0;
        FreeLogSize = (UINT32)(logLast - logStart);
        FreeLogSize += (sizeof(SHA1_PCR_EVENT)- 1);
        PtrtoLastEvent = (SHA1_PCR_EVENT *)(logLast);
        FreeLogSize += PtrtoLastEvent->EventSize;
        tpm32->freelog    = FreeLogSize;
        tpm32->nextevent  = CountEvents(logStart,logLast,0);
        tpm32->Tpm20Enabled = 1;

    }

    return EFI_SUCCESS;
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   GetRawImage
//
// Description: Loads binary from RAW section of main firwmare volume
//
//
// Input:       IN     EFI_GUID   *NameGuid,
//              IN OUT VOID   **Buffer,
//              IN OUT UINTN  *Size
//
// Output:      EFI STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS GetRawImage(
    IN EFI_GUID  *NameGuid,
    IN OUT VOID  **Buffer,
    IN OUT UINTN *Size  )
{
    EFI_STATUS                   Status;
    EFI_HANDLE                   *HandleBuffer = 0;
    UINTN                        HandleCount   = 0;
    UINTN                        i;
    EFI_FIRMWARE_VOLUME_PROTOCOL *Fv;
    UINT32                       AuthenticationStatus;

    Status = pBS->LocateHandleBuffer(
        ByProtocol,
        &gEfiFirmwareVolumeProtocolGuid,
        NULL,
        &HandleCount,
        &HandleBuffer
        );

    if ( EFI_ERROR( Status ) || HandleCount == 0 )
    {
        return EFI_NOT_FOUND;
    }

    //
    // Find desired image in all Fvs
    //
    for ( i = 0; i < HandleCount; i++ )
    {
        Status = pBS->HandleProtocol(
            HandleBuffer[i],
            &gEfiFirmwareVolumeProtocolGuid,
            &Fv
            );

        if ( EFI_ERROR( Status ))
        {
            pBS->FreePool( HandleBuffer );
            return EFI_LOAD_ERROR;
        }

        //
        // Try a raw file
        //
        *Buffer = NULL;
        *Size   = 0;
        Status  = Fv->ReadSection(
            Fv,
            NameGuid,
            EFI_SECTION_RAW,
            0,
            Buffer,
            Size,
            &AuthenticationStatus
            );

        if ( !EFI_ERROR( Status ))
        {
            break;
        }
    }
    pBS->FreePool( HandleBuffer );

    if ( i >= HandleCount )
    {
        return EFI_NOT_FOUND;
    }

    return EFI_SUCCESS;
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   AllocateRTMemory
//
// Description: Allocates memory used by TCG Legacy code during run-time
//
//
// Input:       IN  UINTN size
//
// Output:      VOID*
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************
void* AllocateRTMemory(
    IN UINTN size )
{
    EFI_STATUS Status;
    void       * addr = 0;

    Status = pBS->AllocatePool( EfiRuntimeServicesCode, size, &addr );
    return addr;
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   FindCompatibility16Table
//
// Description: This function identifies the validity of CSM16 binary by
//                searching "$EFI" and verifying table checksum and returs the
//                location of $EFI table
//
// Input:
//
// Output:      EFI_COMPATIBILITY16_TABLE*
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************
EFI_COMPATIBILITY16_TABLE* FindCompatibility16Table( )
{
    UINT8    *p = NULL, *p1 = NULL;
    UINT32   *data32;
    UINT32   count32;
    UINT8    chksum, count8, tablelength;

    //
    // Find CSM16 entry point; "$EFI" is in E0000..FFFFF, 16 bytes aligned.
    //
    data32 = (UINT32*)(UINTN)0xE0000;

    for ( count32 = 0; count32 < 0x8000; count32 += 4 )
    {
        if ( data32[count32] != 0x24454649 )
        {
            continue;
        }
        p = (UINT8*)((UINTN)data32 + (count32 << 2));    // Pointer to "$EFI"

        //
        // Verify the checksum
        //
        tablelength = ((EFI_COMPATIBILITY16_TABLE*)p)->TableLength;

        for ( chksum = 0, count8 = 0, p1 = p; count8 < tablelength; count8++ )
        {
            chksum = chksum + *p1++;
        }

        if ( chksum == 0 )
        {
            break;
        }
    }

    if ( count32 == 0x8000 )
    {
        return 0;
    }

    return ((EFI_COMPATIBILITY16_TABLE*)p);
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   GetTCGLegacyInterface
//
// Description: Loads legacy BIOS binary extensions (TcgLegX16,
//                TPM32 and MPTPM ) and initializes the TCG Legacy support.
//
// Input:       IN EFI_HANDLE        ImageHandle,
//              IN EFI_SYSTEM_TABLE *SystemTable
//
// Output:      EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS InitTCGLegacyInterface(
    IN EFI_HANDLE       ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable )
{
    EFI_STATUS                 Status;
    TCG_LEGX16_HEADER          *legX16header;
    void                       * legX16dest;
    UINTN                      legX16size;
    EFI_LEGACY_BIOS_PROTOCOL   *legBios;
    void                       * rawPtr;
    static TpmBinaryStruct     tpmBinary;
    UINT16                     segLegX16;
    TPM32HEADER                * tpm32hdr;
    UINTN                      tpm32size;
    TPMBIOSDriverHeader        * mptpmHdr;
#if TCG_LEGACY == 0
    UINTN                      mpTpmSize;
#endif
    EFI_TCG_PROTOCOL           *tcgProtocol;
    EFI_EVENT                  event;
    EFI_LEGACY_REGION_PROTOCOL * iRegion;
    EFI_GUID                   gMpDriverHobGuid = EFI_TCG_MPDriver_HOB_GUID;
    FAR32LOCALS                *LegFill         =    NULL;
    void                       *Table           = NULL;
    UINTN                      TableSize        = 0;
    UINTN                      Location         = 0;
    UINTN                      Alignment        = 0;
    EFI_GUID                   gEfiTrEEProtocolGuid = EFI_TREE_PROTOCOL_GUID;

    InitAmiLib( ImageHandle, SystemTable );

    if ( installedTpm32 != 0 )
    {
        ASSERT( installedTpm32 == 0 );
        return EFI_UNSUPPORTED;
    }

    //
    // Access EFI TPM driver
    //
    Status = pBS->LocateProtocol( &gEfiIntTcgProtocolGuid, NULL,
                                  &tcgProtocol );

    if ( EFI_ERROR( Status ))
    {
        TRACE((TRACE_ALWAYS, "TCG Service is not found: error=%x\n",  Status));
        tcgProtocol = 0;
        Status = pBS->LocateProtocol( &gEfiTrEEProtocolGuid, NULL, &TrEEProtocolInstance );
        if(EFI_ERROR(Status))return Status;
        Tpm20Support = 1;
    }


    //
    // Access legacyBios internals
    //
    EFI_VERIFY(
        Status = pBS->LocateProtocol(
            &gEfiLegacyBiosProtocolGuid,
            NULL,
            &legBios
            ));

    if ( EFI_ERROR( Status ))
    {
        return Status;
    }

#if TCG_LEGACY == 0
    if(AutoSupportType()){
        TCGLEGX16_FILE_GUID = TCMLEGX16_FILE_GUID;
        TPM32_FILE_GUID = TCM32_FILE_GUID;
    }
#else
	TCGLEGX16_FILE_GUID = TCMLEGX16_FILE_GUID;
        TPM32_FILE_GUID = TCM32_FILE_GUID;
#endif


    //
    // Load LEGX16 into legacy region
    //
    rawPtr = 0;
    Status = GetRawImage( &TCGLEGX16_FILE_GUID, &rawPtr, &legX16size    );

    if ( EFI_ERROR( Status ))
    {
        TRACE((TRACE_ALWAYS, "Failed to load LEGX16: error=%x\n",  Status));
        return Status;
    }
    legX16header = (TCG_LEGX16_HEADER* )rawPtr;
    EFI_VERIFY(
        legBios->GetLegacyRegion( legBios, legX16size + SEG_ALIGNMENT, 0,
                                  SEG_ALIGNMENT, &legX16dest ));
    segLegX16 = (UINT16)((UINTN)legX16dest >> 4 );

    //
    // Load TPM32 into runtime-code memory
    //
    Status = GetRawImage( &TPM32_FILE_GUID, &rawPtr, &tpm32size    );

    if ( EFI_ERROR( Status ))
    {
        TRACE((TRACE_ALWAYS, "Failed to load TPM32: error=%x\n",  Status));
        return Status;
    }
    tpm32hdr = AllocateRTMemory( tpm32size );
    MemCpy( tpm32hdr, rawPtr, tpm32size );

    //
    // Load MPTPM into runtime-code memory
    //
#if TCG_LEGACY == 0
    if(!(AutoSupportType())){
      Status = GetRawImage( &MPTPM_FILE_GUID, &rawPtr, &mpTpmSize );

      if ( EFI_ERROR( Status )){
            TRACE((TRACE_ALWAYS, "Failed to load MPTPM: error=%x\n",  Status));
            return Status;
        }
        mptpmHdr = AllocateRTMemory( mpTpmSize );
        MemCpy( mptpmHdr, rawPtr, mpTpmSize );
    }else{
        LegFill = (FAR32LOCALS*)LocateATcgHob( pST->NumberOfTableEntries,
                                               pST->ConfigurationTable,
                                               &gMpDriverHobGuid );
        mptpmHdr = (TPMBIOSDriverHeader*)(UINTN)( LegFill->Offset - LegFill->Codep );
    }
#else
    LegFill = (FAR32LOCALS*)LocateATcgHob( pST->NumberOfTableEntries,
                                               pST->ConfigurationTable,
                                               &gMpDriverHobGuid );
    mptpmHdr = (TPMBIOSDriverHeader*)(UINTN)( LegFill->Offset - LegFill->Codep );
#endif



    //
    // Link pointers from TPM32 to MPTPM
    //
    tpm32hdr->MP_HDR         = (UINT32)( UINTN ) mptpmHdr;
    tpm32hdr->scratch.memptr =  (UINT32)( UINTN ) AllocateRTMemory(
        TPM32_SCRATCHMEM_SIZE );
    tpm32hdr->scratch.dwSize = TPM32_SCRATCHMEM_SIZE;
    {
        UINT32 * p
            =  (UINT32*)((UINT8*)legX16header + legX16header->wTpm32entryPtr);
        *p  = (UINT32)( UINTN ) tpm32hdr + tpm32hdr->entryPoint;
    }
    legX16header->wTpm32hdr = (UINT32)( UINTN ) tpm32hdr;
    linkTPMDriver( tpm32hdr, tcgProtocol );
    legX16header->regMOR = ((TCG_MOR_REG) << 8);

    //
    // Copy final LegX16 to dest (F000-E000 area)
    //
    legBios->CopyLegacyRegion( legBios, legX16size, legX16dest, legX16header );
    legX16header = (TCG_LEGX16_HEADER* )legX16dest;


    //
    // Unlock E000-F000: Init will update variable inside LEGX16
    //
    Status = pBS->LocateProtocol( &gEfiLegacyRegionProtocol, NULL, &iRegion );

    if ( EFI_ERROR( Status ))
    {
        TRACE((TRACE_ALWAYS,
               "Failed to locate Legacy Region Protocol to unlock E000: %r\n",
               Status));
        return Status;
    }
    Status = iRegion->UnLock( iRegion, 0xE0000, 0x20000, NULL );

    //
    // Init LEGX16
    //
    {
        EFI_IA32_REGISTER_SET Regs;

        if ( EFI_ERROR( Status ))
        {
            TRACE((TRACE_ALWAYS, "Failed to unlock Legacy region E000: %r\n",
                   Status));
            return Status;
        }

        MemSet( &Regs, sizeof (EFI_IA32_REGISTER_SET), 0 );
        legBios->FarCall86(
            legBios,
            segLegX16,
            legX16header->InitCode,
            &Regs,
            NULL,
            0
            );
    }

    //
    // Lock E000-F000
    //
    iRegion->Lock( iRegion, 0xE0000, 0x20000, NULL );

    //
    // Fills TpmBinaryStruct : Setup int1Ahook, int19Hook, and osloaderHook
    //
    tpmBinary.wLegX16Seg     = segLegX16;
    tpmBinary.int1a_dispatch = legX16header->int1a_dispatch;
    tpmBinary.int19Ev        = legX16header->int19Ev;
    tpmBinary.intLoaderEv    = legX16header->intLoaderEv;
    tpmBinary.BevBcvEv       = legX16header->BevBcvEv;

    //
    // Hookup for BootimeServices shutdown: need to strip *installedTpm32 off the
    // pointers to BootTime data
    //
    installedTpm32 = tpm32hdr;

    #if defined(EFI_EVENT_SIGNAL_READY_TO_BOOT) && EFI_SPECIFICATION_VERSION <\
    0x20000
    EFI_VERIFY(
        Status = gBS->CreateEvent( EFI_EVENT_SIGNAL_LEGACY_BOOT,
                                   EFI_TPL_CALLBACK, UnlinkTPM32fromEFI,
                                   tpm32hdr, &event ));
    #else
    EFI_VERIFY(
        Status = CreateLegacyBootEvent(
            EFI_TPL_CALLBACK,
            UnlinkTPM32fromEFI,
            tpm32hdr,
            &event
            ));
    #endif
    TRACE((TRACE_ALWAYS, "\tLEGX16: %x:%x, %x, %x\n",
           tpmBinary.wLegX16Seg, tpmBinary.int1a_dispatch, tpmBinary.int19Ev,
           tpmBinary.intLoaderEv));
    TRACE((TRACE_ALWAYS, "\tTPM32: header:%x entry:%x log:%x logsize:%x\n",
           (UINT32)( UINTN ) tpm32hdr, (UINT32)( UINTN ) tpm32hdr
           + tpm32hdr->entryPoint));
    TRACE((TRACE_ALWAYS, "\tMPTPM: %x\n", (UINT32)( UINTN ) mptpmHdr));

    //
    // Returns table pointing to TpmBinaryStruct
    //
    if ( Table != NULL && TableSize != NULL )
    {
        Table     = &tpmBinary;
        TableSize = (UINTN)sizeof(tpmBinary);

        if ( Location )
        {
            Location = 0;
        }

        if ( Alignment )
        {
            Alignment = SEG_ALIGNMENT;
        }
    }
    else {
        //
        // Put them int Leg Segment on our own
        //
        void                      * legPtr = 0;
        EFI_COMPATIBILITY16_TABLE * bfi16  = 0;
		UINT8					  * p;
    	UINT8   				  chksum;
		UINT8					  i=0;

        EFI_VERIFY(
            legBios->GetLegacyRegion( legBios, sizeof(tpmBinary)
                                      + SEG_ALIGNMENT, 0,
                                      SEG_ALIGNMENT, &legPtr ));
        Status = iRegion->UnLock( iRegion, 0xE0000, 0x20000, NULL );
        MemCpy( legPtr, &tpmBinary, sizeof(tpmBinary));
        bfi16 = FindCompatibility16Table( );

        if ( bfi16 != 0 )
        {
            TRACE((TRACE_ALWAYS, "\tFound BFI at 0x%x\n", bfi16));
            bfi16->TpmSegment =  (UINT16)((UINTN)legPtr >> 4 );
            bfi16->TpmOffset  = 0;

			bfi16->TableChecksum = 0;
   			p = (UINT8*)bfi16;
    		for (chksum=0, i=0; i<bfi16->TableLength; i++) {
        	chksum+=*p++;
    		}
    		bfi16->TableChecksum = ~(--chksum);
        }
				
		
        else {
                 TRACE((TRACE_ALWAYS, "\t!!!Not Found BFI\n"));
        }
        iRegion->Lock( iRegion, 0xE0000, 0x20000, NULL );
    }


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
