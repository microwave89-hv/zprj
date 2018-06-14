//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2007, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
// $Header: /Alaska/SOURCE/Core/CORE_DXE/DataHub.c 5     7/08/09 5:54p Vyacheslava $
//
// $Revision: 5 $
//
// $Date: 7/08/09 5:54p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Core/CORE_DXE/DataHub.c $
// 
// 5     7/08/09 5:54p Vyacheslava
// Updated according to the coding standards.
//
// 4     12/16/08 1:32a Iminglin
// The function value of FindNextFiltermatch for compliance.
//
// 3     11/07/07 12:13p Felixp
// Bug fixes in record filtering logic.
// Old code was treating FilterClass parameter passed into
// RegisterFilterDriver routine as requested class value.
// However, data hub specification defines this parameter as a bit map of
// requested data classes.
//
// 2     9/05/07 5:51p Felixp
// 1. LogData routine is updated.
//         Core that initializes RecordSize field of the data hub record
// header is updated to include header size (the header size was excluded
// in the previous Core verions).<br />
//         DataHub specification is vague regarding the RecordSize field.
//         It says RecordSize is "Size of the data in the record in
// bytes".
//         It's not clear if it should include or exclude the header size.
//         In EDK DataHub implenetation RecordSize includes the header.
//         Aptio implementation is updated to comply with EDK
// implementation.
// 2. When time is not available initialize time fields with default
// values
//
// 1     1/28/05 12:45p Felixp
//
// 2     1/18/05 3:22p Felixp
// PrintDebugMessage renamed to Trace
//
// 1     12/22/04 6:19p Admin
//
// 1     12/22/04 6:18p Admin
//
// 6     11/12/04 3:13p Markw
// Added signal event, to get previously logged data.
//
// 5     4/17/04 4:23p Felixp
//
// 4     3/24/04 10:17a Markw
// Using AmiDxeLib instead AmiLib.
//
// 3     3/23/04 5:45p Markw
// Added function and table headers (comments) to the file.
//
// 2     3/20/04 10:46a Felixp
//
// 1     3/16/04 2:38p Markw
//
//
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:    DataHub_c
//
// Description: Log data to be retrieved by functions or call events
//  for data matching filter.
//
//<AMI_FHDR_END>
//**********************************************************************

#include <AmiDxeLib.h>
#include <Protocol\DataHub.h>

EFI_GUID gDataHubProtocolGuid = EFI_DATA_HUB_PROTOCOL_GUID;

//**********************************************************************
//<AMI_THDR_START>
//
// Name:        DATA_RECORD
//
// Description: This structure describes the Data Record header and data.
//
// Fields:     
//  Name            Type                    Description
//  ------------------------------------------------------------
//  Link            DATA_RECORD*            Next link
//  RecordHeader    EFI_DATA_RECORD_HEADER  Log Record Header
///
//  Directly following Header (&RecordHeader + 1) is the data.
//
//<AMI_THDR_END>
//**********************************************************************

typedef struct _DATA_RECORD DATA_RECORD;
struct _DATA_RECORD {
    DATA_RECORD             *Link;
    EFI_DATA_RECORD_HEADER  RecordHeader;
};

//**********************************************************************
//<AMI_THDR_START>
//
// Name:        FILTER
//
// Description: This structure describes the filter link.
//
// Fields:     
//  Name            Type            Description
//  ------------------------------------------------------------
//  Link            FILTER*         Next link
//  Event           EFI_EVENT       Event
//  Class           UINT64          Class (0 if no class filtering)
//  DataRecordGuid  EFI_GUID        Guid (undefined in no guid filtering)
//  isGuid          BOOLEAN         TRUE if guid filtering.
//  LastRead        DATA_RECORD*    Last read record for the filter.
//
//<AMI_THDR_END>
//**********************************************************************

typedef struct _FILTER FILTER;
struct _FILTER {
    FILTER      *Link;
    EFI_EVENT   Event;
    UINT64      Class;
    EFI_GUID    DataRecordGuid;
    BOOLEAN     isGuid;
    DATA_RECORD *LastRead;
};


FILTER      *gFilHead   = 0;    //Filter Head
DATA_RECORD *gHead      = 0;    //Data Record Head
DATA_RECORD *gTail      = 0;    //Data Record Count
UINT64      gLogCount   = 0;    //Unique log count.
DATA_RECORD *gCache     = 0;    //Last reocrd cache.


//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure: FindNextFilterMatch
//
// Description: Search log to find next record that matches filter.
//
// Input:
//  DATA_RECORD *Record
//  FILTER      *Filter
//
// Output: DATA_RECORD*
//
// Referrals: guidcmp
//
// Notes:
//  Here is the control flow of this function:
//  1. Starting at the current record for filter matching.
//  2. If Class and Class doesn't match continue at step 1 for next record.
//  3. If guid and DataRecordGuid doesn't match continue at step 1 for next record.
//  4. Match, return record.
//  5. If Steps 1-4, doesn't find any matching filter, return 0.
//
//<AMI_PHDR_END>
//**********************************************************************

DATA_RECORD* FindNextFilterMatch(
    DATA_RECORD *Record, 
    FILTER *Filter)
{
    for (; Record; Record=Record->Link) {
        if ( Filter->Class && 
             !(Filter->Class & Record->RecordHeader.DataRecordClass) ) 
            continue;
        
        if ( Filter->isGuid && 
             guidcmp(&Filter->DataRecordGuid,&Record->RecordHeader.DataRecordGuid) != 0 ) 
            continue;
        
        return Record;
    }
    
    return NULL;
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure: LogData
//
// Description: Log the record. If matching event, signal it.
//
// Input:
//  IN EFI_DATA_HUB_PROTOCOL    *This
//  IN EFI_GUID                 *DataRecordGuid
//  IN EFI_GUID                 *ProducerName
//  IN UINT64                   DataRecordClass
//  IN VOID                     *RawData
//  IN UINT32                   RawDataSize
//
// Output:
//  EFI_STATUS
//      * EFI_SUCCESS - Event logged.
//      * EFI_OUT_OF_RESOUCES - Not enough resources to log data.
//
// Modified: gHead gTail
//
// Referrals: AllocatePool
//
// Notes:
//  Here is the control flow of this function:
//  1. Allocate memory enough for data record. If not enough memory, return EFI_OUT_OF_RESOURCES.
//  2. Fill data record header and increase log count.
//  3. Fill data to log.
//  4. Add record to log.
//  5. Check for a matching filter.
//  6. If matching filter, signal event.
//  7. Return EFI_SUCCESS.
//
//<AMI_PHDR_END>
//**********************************************************************

EFI_STATUS LogData(
    IN EFI_DATA_HUB_PROTOCOL    *This,
    IN EFI_GUID                 *DataRecordGuid,
    IN EFI_GUID                 *ProducerName,
    IN UINT64                   DataRecordClass,
    IN VOID                     *RawData,
    IN UINT32                   RawDataSize
)
{
    EFI_DATA_RECORD_HEADER  *RcdHdr;
    DATA_RECORD             *Record;
    FILTER                  *Filter;
    UINT8                   *Data;
    EFI_STATUS              Status;
    
    //16 dummy bytes to make sure struct alignment isn't an issue in platform.
    if ( pBS->AllocatePool(
            EfiBootServicesData,
            sizeof(DATA_RECORD) + RawDataSize + 16,
            &Record ) != EFI_SUCCESS )
        return EFI_OUT_OF_RESOURCES;
    
    RcdHdr = &Record->RecordHeader;
    
    Record->Link                = 0;
    RcdHdr->Version             = EFI_DATA_RECORD_HEADER_VERSION;
    RcdHdr->HeaderSize          = sizeof(EFI_DATA_RECORD_HEADER);
//DataHub specification is vague regarding the RecordSize field.
//It says RecordSize is "Size of the data in the record in bytes".
//It's not clear if it should include or exclude the header size.
//It's sounds more like it should not, however,
//in EDK DataHub implenetation RecordSize includes the header.
//For the sake of compatibility let's do the same.
    RcdHdr->RecordSize          = RawDataSize+sizeof(EFI_DATA_RECORD_HEADER);
    RcdHdr->DataRecordGuid      = *DataRecordGuid;
    RcdHdr->ProducerName        = *ProducerName;
    RcdHdr->DataRecordClass     = DataRecordClass;
    RcdHdr->LogMonotonicCount   = ++gLogCount;  //Each log  count must be unique.
    Status = pRS->GetTime(&(RcdHdr->LogTime),NULL);
    
    if (EFI_ERROR(Status)) {    //time not available, set default values
        RcdHdr->LogTime.Year   = 0;
        RcdHdr->LogTime.Month  = 1;
        RcdHdr->LogTime.Day    = 1;
        RcdHdr->LogTime.Hour   = 0;
        RcdHdr->LogTime.Minute = 0;
        RcdHdr->LogTime.Second = 0;
    }
    
    //Store data to be logged.
    Data = (UINT8*)(RcdHdr + 1);
    MemCpy(
        Data, 
        RawData, 
        RawDataSize
    );
    
    //Add record to log.
    if (!gHead) 
        gHead = Record;
    else 
        gTail->Link = Record;
    
    gTail = Record;
    
    //Check for matching filter.
    for (Filter = gFilHead; Filter; Filter = Filter->Link) {
        if ( Filter->Class && 
             !(Filter->Class & DataRecordClass) ) 
            continue;
        
        if ( Filter->isGuid && 
             guidcmp(&Filter->DataRecordGuid, DataRecordGuid) != 0 ) 
            continue;
        
        pBS->SignalEvent(Filter->Event);
    }
    
    return EFI_SUCCESS;
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure: GetNextDataRecord
//
// Description: Search log to find next record that matches Count or filter.
//  Return next record or if Filter, next record matching filter.
//
// Input:
//  IN EFI_DATA_HUB_PROTOCOL    *This
//  IN OUT UINT64               *MonotonicCount
//  IN EFI_EVENT                *FilterDriver OPTIONAL
//  OUT EFI_DATA_RECORD_HEADER  **Record
//
// Output:
//  EFI_STATUS
//  * EFI_SUCCESS - If Data Record returned.
//  * EFI_NOT_FOUND - Data Record not found.
//  * EFI_INVALID_PARAMETER - *FilterDriver doesn't match registered filters.
//
// Modified: gCache
//
// Referrals: FindNextFilterMatch
//
// Notes:
//  Here is the control flow of this function:
//  1. If no logged records, return EFI_NOT_FOUND.
//  2. If using FilterDriver, find filter. If filter not found, return EFI_INVALID_PARAMETER;
//  3. If *MonotonicCount != 0, go to step 14.
//  ---*MonotonicCount = 0---
//  4. If no filter driver, set *MonotonicCount = 1, go to step 14.
//  ---Filter Driver---
//  5. If no last read, start at Head.
//  6. If last read, start at the next. If no next, return EFI_NOT_FOUND.
//  7. Find record matching filter.
//  8. If no match, set last read to tail, and return EFI_NOT_FOUND.
//  9. Set *Record to found record, and set LastRead to record.
//  10. Find next match, to get *MonotonicCount.
//  11. If not found, set *MonotonicCount = 0.
//  12. Set cache to link.
//  13. Return EFI_SUCCESS.
//  ---MontonicCount exists---
//  14. Get starting link. If after cache, use cache, otherwise use head.
//  15. Search until log count is found, regardless of filter.
//  16. If not found, return EFI_NOT_FOUND.
//  17. If filter set LastRead.
//  18. If last link, *MontonicCount = 0. Go to step 21.
//  ---If not last link,---
//  19. If FilterDriver, find next match for *MonotonicCounter.
//  20. If no next match, set *MonotonicCounter = 0.
//  -------
//  21. Set cache. Return EFI_SUCCESS.
//
//<AMI_PHDR_END>
//**********************************************************************

EFI_STATUS GetNextDataRecord(
    IN EFI_DATA_HUB_PROTOCOL    *This,
    IN OUT UINT64               *MonotonicCount,
    IN EFI_EVENT                *FilterDriver OPTIONAL,
    OUT EFI_DATA_RECORD_HEADER  **Record
)
{
    DATA_RECORD *Link;
    FILTER      *Filter;
    
    if (!gHead) 
        return EFI_NOT_FOUND;   //Any records logged?
    
    //Find Matching filter
    if (FilterDriver) {
        //In future, binary search may be more efficient, or some caching.
        for (Filter = gFilHead; Filter && Filter->Event != *FilterDriver; Filter = Filter->Link)
            ; //Find matching Filter for Event.
        
        if (!Filter) 
            return EFI_INVALID_PARAMETER;
    }
    
    //If monotonic count is zero?
    if (!*MonotonicCount) {
        //If filter driver, get first unread record matching filter.
        if (!FilterDriver) {
            *MonotonicCount = 1;    //If not filter driver, get first record.
            
        } else {
            //Get the record after the last read record. If not, get the first record.
            if (Filter->LastRead) 
                Link = Filter->LastRead->Link;
            else 
                Link = gHead;
            
            if (!Link) 
                return EFI_NOT_FOUND;    //If record doesn't exist, return EFI_NOT_FOUND.
            
            if ( !(Link = FindNextFilterMatch(Link, Filter)) ) { //Get record matching filter, zero if no match.
                //No matching record. Set LastRead to tail, and return EFI_NOT_FOUND.
                Filter->LastRead = gTail;
                return EFI_NOT_FOUND;
            }
            
            //Save pointer to matching record, and last read record.
            *Record = &Link->RecordHeader;
            Filter->LastRead = Link;
            
            //Find the next matching record to return the next Monotonic Count.
            if ( Link = FindNextFilterMatch(Link->Link, Filter) ) //zero if no match.
                *MonotonicCount = Link->RecordHeader.LogMonotonicCount;
            else 
                *MonotonicCount = 0;                   //If no matching record, set last read to end.
            
            gCache = Link;  //Set cache to find the next record.
            return EFI_SUCCESS;
        }
    }
    
    //Find a specific MonotonicCount.
    //If Count is same or after cache, start with cache. Otherwise start at beginning.
    if (gCache && gCache->RecordHeader.LogMonotonicCount <= *MonotonicCount)
        Link = gCache;
    else 
        Link = gHead;
    
    //Search for Log.
    for (; Link; Link = Link->Link) {
        if (Link->RecordHeader.LogMonotonicCount == *MonotonicCount) {
            *Record = &Link->RecordHeader;      //Save pointer to matching record.
            
            if (Link == gTail) {                //If last log, Count = 0.
                *MonotonicCount = 0;
                
                if (FilterDriver) 
                    Filter->LastRead = Link;    //If filter, store last read.
                
            } else {                            //If not last log.
                if (FilterDriver) {
                    Filter->LastRead = Link;    //Set last read.
                    
                    if ( Link = FindNextFilterMatch(Link->Link, Filter) )
                        *MonotonicCount = Link->RecordHeader.LogMonotonicCount; //Get count of next matching record.
                    else 
                        *MonotonicCount = 0;   //If no more matching record, set count to 0.
                    
                } else 
                    ++*MonotonicCount;         //If not filter driver, increase count.
            }
            
            gCache = Link;                     //Set cache.
            return EFI_SUCCESS;
        }
    }
    
    return EFI_NOT_FOUND;                      //Record does't exist.
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure: RegisterFilterDriver
//
// Description: Register new filter driver.
//
// Input:
//  IN EFI_DATA_HUB_PROTOCOL    *This
//  IN EFI_EVENT                FilterEvent
//  IN EFI_TPL                  FilterTpl
//  IN UINT64                   FilterClass
//  IN EFI_GUID                 *FilterDataRecordGuid OPTIONAL
//
// Output:
//  EFI_STATUS
//  * EFI_SUCCESS - Filter driver registered.
//  * EFI_ALREADY_STARTED - Filter driver was already registered.
//  * EFI_OUT_OF_RESOURCES - Not enough resources to allocate Link.
//
// Modified: gFilHead
//
// Referrals: AllocatePool
//
// Notes:
//  Here is the control flow of this function:
//  1. Search filters for matching Event. If Event return return EFI_ALREADY_STARTED.
//  2. Allocate Link for filter. If out of resources, return EFI_OUT_OF_RESOURCES.
//  3. Fill in filter data.
//  4. Add link to end.
//  5. Return EFI_SUCCESS.
//
//<AMI_PHDR_END>
//**********************************************************************

EFI_STATUS RegisterFilterDriver(
    IN EFI_DATA_HUB_PROTOCOL    *This,
    IN EFI_EVENT                FilterEvent,
    IN EFI_TPL                  FilterTpl,
    IN UINT64                   FilterClass,
    IN EFI_GUID                 *FilterDataRecordGuid OPTIONAL
)
{
    FILTER      *Filter;
    FILTER      *Link, *PLink;
    FILTER      **Ptr;
    
    if (gFilHead) {
        for (Link = gFilHead; Link; Link = Link->Link) {
            if (Link->Event == FilterEvent) 
                return EFI_ALREADY_STARTED;
            
            PLink = Link;
        }
        
        Ptr = &PLink->Link;
        
    } else
        Ptr = &gFilHead;
    
    if ( pBS->AllocatePool(
            EfiBootServicesData,
            sizeof(FILTER),
            &Filter) != EFI_SUCCESS )
        return EFI_OUT_OF_RESOURCES;
        
    Filter->Link        = 0;
    Filter->Event       = FilterEvent;
    Filter->Class       = FilterClass;
    Filter->LastRead    = NULL;
    
    if (FilterDataRecordGuid) { //Guid is optional. isGuid, determines if to test Guid.
        Filter->DataRecordGuid = *FilterDataRecordGuid;
        Filter->isGuid = TRUE;
        
    } else
        Filter->isGuid = FALSE;
    
    *Ptr = Filter;
    
    // Signal the Filter driver to get all the previous logged data. Otherwise,
    // One must wait until the next signal to get the previous logged data.
    pBS->SignalEvent(FilterEvent);
    
    return EFI_SUCCESS;
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure: UnregisterFilterDriver
//
// Description: Unregister a filter driver.
//
// Input:
//  IN EFI_DATA_HUB_PROTOCOL    *This
//  IN EFI_EVENT                FilterEvent
//
// Output:
//  EFI_STATUS
//  * EFI_SUCCESS - Filter driver removed.
//  * EFI_NOT_FOUND - Filter driver not found.
//
// Modified: gFilHead
//
// Referrals: FreePool
//
// Notes:
//  Here is the control flow of this function:
//  1. If no filter drivers, return EFI_NOT_FOUND.
//  2. If filter stored in Filter Driver Head, free filter driver
//     and set Head to next link.
//  3. Find filter driver.
//  4. If found, remove link, then free link. Return EFI_SUCCESS.
//  5. If not found, return EFI_NOT_FOUND.
//
//<AMI_PHDR_END>
//**********************************************************************

EFI_STATUS UnregisterFilterDriver(
    IN EFI_DATA_HUB_PROTOCOL    *This,
    IN EFI_EVENT                FilterEvent
)
{
    FILTER  *Link, *PLink;
    
    PLink = gFilHead;
    
    if (!gFilHead) 
        return EFI_NOT_FOUND;
    
    if (gFilHead->Event == FilterEvent) {
        gFilHead = gFilHead->Link;
        pBS->FreePool(PLink);
        return EFI_SUCCESS;
    }
    
    for (Link = gFilHead->Link; Link; Link = Link->Link) {
        if (Link->Event == FilterEvent) {
            PLink->Link = Link->Link;
            pBS->FreePool(Link);
            return EFI_SUCCESS;
        }
        
        PLink = Link;
    }
    
    return EFI_NOT_FOUND;
}

EFI_DATA_HUB_PROTOCOL gDataHub = {
    LogData,
    GetNextDataRecord,
    RegisterFilterDriver,
    UnregisterFilterDriver
};

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure: InitDataHub
//
// Description: Install Data Hub Protocol.
//
// Input:
//  IN EFI_HANDLE       ImageHandle
//  IN EFI_SYSTEM_TABLE *SystemTable
//
// Output: EFI_STATUS
//
// Referrals: InstallMultipleProtocolInterfaces
//
// Notes:
//  Here is the control flow of this function:
//  1. Install Data Hub Protocol.
//
//<AMI_PHDR_END>
//**********************************************************************

EFI_STATUS InitDataHub(
    IN EFI_HANDLE       ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable
)
{
    InitAmiLib(ImageHandle, SystemTable);
    
    return pBS->InstallMultipleProtocolInterfaces(
               &ImageHandle,
               &gDataHubProtocolGuid, 
               &gDataHub,
               NULL
           );
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2007, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
