/** @file
**/

#include <Tiano.h>
#include <EfiDriverLib.h>

#include EFI_GUID_DEFINITION(DataHubRecords)
#include EFI_PROTOCOL_CONSUMER(DataHub)
#include EFI_PROTOCOL_CONSUMER(ExitPmAuth)
#include <RcFviDxeLib.h>

#include <Protocol\SMBios.h>


#pragma pack(1)

typedef struct {
    UINT8 Type;
    UINT8 Length;
    UINT16 Handle;
    UINT8 GroupName;
} SMBIOS_TYPE14_STRUCTURE_HDR;

typedef struct {
    UINT8 Type;
    UINT16 Handle;
} SMBIOS_TYPE14_STRUCTURE_ITEM;

#pragma pack()

VOID CreateFirmwareVerInfo(IN EFI_EVENT Event, IN VOID *Context);

EFI_SMBIOS_PROTOCOL *gSmbiosProtocol = NULL;

/**
  The user Entry Point for DXE driver. The user code starts with this function
  as the real entry point for the image goes into a library that calls this 
  function.

  @param[in] ImageHandle    The firmware allocated handle for the EFI image.  
  @param[in] SystemTable    A pointer to the EFI System Table.
  
  @retval EFI_SUCCESS       The entry point is executed successfully.
  @retval other             Some error occurs when executing this entry point.

**/
EFI_STATUS
EFIAPI
FirmwareVerInfoEntryPoint (
    IN EFI_HANDLE ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable
)
{
    EFI_STATUS Status;
    EFI_GUID gEfiSmbiosProtocolGuid = EFI_SMBIOS_PROTOCOL_GUID;
    EFI_EVENT Event;

    DxeInitializeDriverLib (ImageHandle, SystemTable);

    Status = gBS->LocateProtocol(&gEfiSmbiosProtocolGuid, NULL, &gSmbiosProtocol);
    ASSERT_EFI_ERROR(Status);
    if (!EFI_ERROR(Status))
    {
        Status = EfiCreateEventReadyToBoot(
                        EFI_TPL_CALLBACK,
                        CreateFirmwareVerInfo,
                        NULL,
                        &Event
                        );
        ASSERT_EFI_ERROR (Status);
    }

    return EFI_SUCCESS;
}


EFI_STATUS BuildFviStruct(BOOLEAN GroupAssociation, EFI_DATA_RECORD_HEADER *Record)
{
    static VOID *FviStructBuffer = NULL;
    static UINTN FviStructBufferSize = 0;
    static UINTN FviStructSize = 0;
    static UINTN ElementCount = 0;

    EFI_STATUS Status;
    EFI_SUBCLASS_TYPE1_HEADER *DataHeader = NULL;
    FVI_HEADER *FviHeader = NULL;
    UINT16 BufferSize = 0;
    SMBIOS_TYPE14_STRUCTURE_HDR *SmbiosHdr = NULL;
    SMBIOS_TYPE14_STRUCTURE_ITEM *ItemPtr = NULL;
    CHAR8 GroupName[] = "Firmware Version Info\0";

    if (GroupAssociation)
    {
        if ((FviStructBuffer == NULL) && (FviStructSize > sizeof(SMBIOS_TYPE14_STRUCTURE_HDR)))
        {
            return EFI_UNSUPPORTED;
        }

        SmbiosHdr = (SMBIOS_TYPE14_STRUCTURE_HDR *)FviStructBuffer;

        SmbiosHdr->Type = 14;
        SmbiosHdr->Length = (UINT8)FviStructSize;
        SmbiosHdr->Handle = 0xFFFF;

        SmbiosHdr->GroupName = 0x01;
        EfiAsciiStrCpy((CHAR8 *)((UINT8 *)FviStructBuffer+FviStructSize), GroupName);
        FviStructSize += sizeof(GroupName);

        Status = gSmbiosProtocol->SmbiosAddStructure((UINT8 *)SmbiosHdr, (UINT16)(FviStructSize));
        if (!EFI_ERROR(Status))
        {
            gBS->FreePool(FviStructBuffer);
            FviStructBuffer = NULL;
        }

        return Status;
    }

    if (Record == NULL)
    {
        return EFI_INVALID_PARAMETER;
    }

    if (FviStructBuffer == NULL)
    {
        FviStructBufferSize = 0x2000;
        FviStructBuffer = EfiLibAllocateZeroPool(FviStructBufferSize);
        FviStructSize = sizeof(SMBIOS_TYPE14_STRUCTURE_HDR);
    }

    SmbiosHdr = (SMBIOS_TYPE14_STRUCTURE_HDR *)FviStructBuffer;
    ItemPtr = (SMBIOS_TYPE14_STRUCTURE_ITEM *)(SmbiosHdr + 1);
    ItemPtr += ElementCount;

    if (EfiCompareGuid(&Record->DataRecordGuid, &gMiscSubClassName))
    {
        DataHeader = (EFI_SUBCLASS_TYPE1_HEADER *)(Record + 1);
        FviHeader = (FVI_HEADER *)(UINT8 *)(DataHeader + 1);

        if (FviHeader->Header.Type == FVI_SMBIOS_TYPE)
        {
            FviHeader->Header.Handle = 0xFFFF;
            BufferSize = (UINT16)(Record->RecordSize - sizeof(EFI_DATA_RECORD_HEADER) - sizeof(EFI_SUBCLASS_TYPE1_HEADER));
            Status = gSmbiosProtocol->SmbiosAddStructure((UINT8 *)FviHeader, BufferSize);
            if (!EFI_ERROR(Status))
            {
                ItemPtr->Type = FviHeader->Header.Type;
                ItemPtr->Handle = FviHeader->Header.Handle;
                FviStructSize += sizeof(SMBIOS_TYPE14_STRUCTURE_ITEM);
                ElementCount++;
            }
        }
    }

    return EFI_SUCCESS;
}


VOID CreateFirmwareVerInfo(IN EFI_EVENT Event, IN VOID *Context)
{
    EFI_STATUS Status;
    EFI_HANDLE DataHubHandle;
    UINTN HandleSize;
    EFI_DATA_HUB_PROTOCOL *DataHub = NULL;
    EFI_DATA_RECORD_HEADER *Record = NULL;
    UINT64 MonotonicCount = 0;

    HandleSize = sizeof (EFI_HANDLE);

    Status = gBS->LocateHandle (
                     ByProtocol,
                     &gEfiDataHubProtocolGuid,
                     NULL,
                     &HandleSize,
                     &DataHubHandle
                 );
    if (EFI_ERROR (Status))
    {
        return;
    }

    Status = gBS->HandleProtocol (
                     DataHubHandle,
                     &gEfiDataHubProtocolGuid,
                     &DataHub
                 );
    if (EFI_ERROR (Status))
    {
        return;
    }

    do {
        Status = DataHub->GetNextRecord (
                             DataHub,
                             &MonotonicCount,
                             NULL,
                             &Record);
        if (!EFI_ERROR (Status))
        {
            if (Record->DataRecordClass == EFI_DATA_RECORD_CLASS_DATA)
            {
                BuildFviStruct(FALSE, Record);
            }
        }
    } while (!EFI_ERROR (Status) && (MonotonicCount != 0));

    Status = BuildFviStruct(TRUE, NULL);
    if (EFI_ERROR(Status))
    {
        DEBUG((EFI_D_ERROR, "!!!Firmware Version Information Error!!!\n"));
        DEBUG((EFI_D_ERROR, "!!!Type 14 ¡V Group Associations Indicator!!!\n"));
    }

    if (Event != NULL)
    {
        gBS->CloseEvent(Event);
    }
}
