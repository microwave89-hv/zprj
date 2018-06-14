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
//*************************************************************************
// $Header: /Alaska/SOURCE/Modules/TCG2/Common/Tpm20PlatformDxe/Tpm20Acpi/Tpm20Acpi.c 2     4/21/14 3:18p Fredericko $
//
// $Revision: 2 $
//
// $Date: 4/21/14 3:18p $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/TCG2/Common/Tpm20PlatformDxe/Tpm20Acpi/Tpm20Acpi.c $
// 
// 2     4/21/14 3:18p Fredericko
// 
// 1     4/21/14 2:19p Fredericko
// 
// 1     10/08/13 12:06p Fredericko
// Initial Check-In for Tpm-Next module
// 
// 2     10/03/13 3:01p Fredericko
// 
// 1     7/10/13 5:58p Fredericko
// [TAG]  		EIP120969
// [Category]  	New Feature
// [Description]  	TCG (TPM20)
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:  
//
// Description:
//
//<AMI_FHDR_END>
//*************************************************************************

#include "Tpm20Acpi.h"
#include <Token.h>
#include <AmiDxeLib.h>
#include "Tpm20CRBLib.h"


EFI_TPM2_ACPI_TABLE  mTpm2AcpiTemplate = {
  {
    EFI_ACPI_5_0_TRUSTED_COMPUTING_PLATFORM_2_TABLE_SIGNATURE,
    sizeof (mTpm2AcpiTemplate),
    EFI_TPM2_ACPI_TABLE_REVISION,
    //
    // initialize to 0
    // 
    //
  },
  0, // Flags
  (EFI_PHYSICAL_ADDRESS)(UINTN)0xFFFFFFFF, // Control Area
  EFI_TPM2_ACPI_TABLE_START_METHOD_ACPI,
};




//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   GetHob
//
// Description: Find instance of a HOB type in a HOB list
//
// Input:
//      Type          The HOB type to return.
//      HobStart      The first HOB in the HOB list.
//
// Output:
//      Pointer to the Hob matching the type or NULL
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************
VOID* GetHob(
    IN UINT16 Type,
    IN VOID   *HobStart  )
{
    EFI_PEI_HOB_POINTERS Hob;

    Hob.Raw = HobStart;

    //
    // Return input if not found
    //
    if ( HobStart == NULL )
    {
        return HobStart;
    }

    //
    // Parse the HOB list, stop if end of list or matching type found.
    //
    while ( !END_OF_HOB_LIST( Hob ))
    {
        if ( Hob.Header->HobType == Type )
        {
            break;
        }

        Hob.Raw = GET_NEXT_HOB( Hob );
    }

    //
    // Return input if not found
    //
    if ( END_OF_HOB_LIST( Hob ))
    {
        return HobStart;
    }

    return (VOID*)(Hob.Raw);
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   CompareGuid
//
// Description: Compares two input GUIDs
//
// Input:       Comparision status
//
// Output:      None
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************
BOOLEAN CompareGuid(
    EFI_GUID *G1,
    EFI_GUID *G2 )
{
    UINT32 *p1 = (UINT32*)G1, *p2 = (UINT32*)G2;
    UINTN  i;

    for ( i = 0; i < 4; ++i )
    {
        if ( p1[i] != p2[i] )
        {
            return FALSE;
        }
    }
    return TRUE;
    ;
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   GetNextGuidHob
//
// Description: Find GUID HOB
//
// Input:       HobStart    A pointer to the start hob.
//              Guid        A pointer to a guid.
// Output:
//              Buffer          A pointer to the buffer.
//              BufferSize      Buffer size.
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS GetNextGuidHob(
    IN OUT VOID          **HobStart,
    IN EFI_GUID          * Guid,
    OUT VOID             **Buffer,
    OUT UINTN            *BufferSize OPTIONAL )
{
    EFI_STATUS           Status;
    EFI_PEI_HOB_POINTERS GuidHob;

    if ( Buffer == NULL )
    {
        return EFI_INVALID_PARAMETER;
    }

    for ( Status = EFI_NOT_FOUND; EFI_ERROR( Status );)
    {
        GuidHob.Raw = *HobStart;

        if ( END_OF_HOB_LIST( GuidHob ))
        {
            return EFI_NOT_FOUND;
        }

        GuidHob.Raw = GetHob( EFI_HOB_TYPE_GUID_EXTENSION, *HobStart );

        if ( GuidHob.Header->HobType == EFI_HOB_TYPE_GUID_EXTENSION )
        {
            if ( CompareGuid( Guid, &GuidHob.Guid->Name ))
            {
                Status  = EFI_SUCCESS;
                *Buffer = (VOID*)((UINT8*)(&GuidHob.Guid->Name) 
                          + sizeof (EFI_GUID));

                if ( BufferSize != NULL )
                {
                    *BufferSize = GuidHob.Header->HobLength
                                  - sizeof (EFI_HOB_GUID_TYPE);
                }
            }
        }

        *HobStart = GET_NEXT_HOB( GuidHob );
    }

    return Status;
}



VOID* FindHob(
    IN UINTN                   NoTableEntries,
    IN EFI_CONFIGURATION_TABLE *ConfigTable,
    IN EFI_GUID                *HOB_guid )
{
    VOID *HobStart;
    VOID *PtrHob;
    EFI_GUID Hoblistguid = HOB_LIST_GUID;

    while ( NoTableEntries > 0 )
    {
        NoTableEntries--;

        if ((!MemCmp(
                 &ConfigTable[NoTableEntries].VendorGuid,
                 &Hoblistguid, sizeof(EFI_GUID)
                 )))
        {
            HobStart = ConfigTable[NoTableEntries].VendorTable;

            if ( !EFI_ERROR(
                     GetNextGuidHob( &HobStart, HOB_guid, &PtrHob, NULL )
                     ))
            {
                TRACE ((TRACE_ALWAYS, "Hob found = %x \n", PtrHob));
                return PtrHob;
            }
        }
    }
    return NULL;
}



EFI_STATUS
Tpm20PublishAcpiTable (
  VOID
  )
{
  EFI_STATUS    Status;
  UINTN         TableKey = 0;
  EFI_ACPI_TABLE_PROTOCOL     *AcpiTable;
  EFI_TPM2_ACPI_CONTROL_AREA  *CtrlAreaMap = NULL;
  EFI_GUID      Meguid = ME_DATA_HOB_GUID;
  INTEL_PTT_HOB_DATA  *StolenAddress = NULL;

  mTpm2AcpiTemplate.Header.OemRevision     = TPM20TABLEOEMREVISION;
  mTpm2AcpiTemplate.Header.CreatorId  = CREATOR_ID_AMI;
  mTpm2AcpiTemplate.Header.OemTableId = EFI_SIGNATURE_64 ('T', 'p', 'm', '2', 'T', 'a', 'b', 'l');
  
  //
  // Publish the TPM ACPI table
  //
  Status = pBS->LocateProtocol (&gEfiAcpiTableProtocolGuid, NULL, (VOID **) &AcpiTable);
  if(EFI_ERROR(Status))return Status;

  if(!isTpm20CrbPresent())
  {
    mTpm2AcpiTemplate.AddressOfControlArea = 0;
    mTpm2AcpiTemplate.StartMethod = 6;
   }else{
    
     StolenAddress = (INTEL_PTT_HOB_DATA  *)FindHob ( pST->NumberOfTableEntries,
                               pST->ConfigurationTable,
                               &Meguid);

     if(StolenAddress != 0){
        if(((UINTN)((UINT64 *)StolenAddress->BufferAddress)) != 0){
            mTpm2AcpiTemplate.AddressOfControlArea = StolenAddress->BufferAddress;
        }else{
            mTpm2AcpiTemplate.AddressOfControlArea = TPM20_CRBBASE;
        }
     }else{
         mTpm2AcpiTemplate.AddressOfControlArea = TPM20_CRBBASE;
     }

     mTpm2AcpiTemplate.StartMethod = 2;
     CtrlAreaMap = (EFI_TPM2_ACPI_CONTROL_AREA *)(UINTN) mTpm2AcpiTemplate.AddressOfControlArea;
     MemSet (CtrlAreaMap, sizeof(EFI_TPM2_ACPI_CONTROL_AREA), 0);
     CtrlAreaMap->CommandSize  = 0xF80;
     CtrlAreaMap->ResponseSize = 0xF80;
     CtrlAreaMap->Command      = (UINTN)mTpm2AcpiTemplate.AddressOfControlArea + 0x80;
     CtrlAreaMap->Response     = (UINTN)mTpm2AcpiTemplate.AddressOfControlArea + 0x80;
      
     TRACE ((TRACE_ALWAYS, "Ftpm Windows Buffer Control Area Address = %x\n", mTpm2AcpiTemplate.AddressOfControlArea));
     TRACE ((TRACE_ALWAYS, "Ftpm Windows Command/Response Buffer Address = %x\n", CtrlAreaMap->Command));
   }
   
   TRACE ((TRACE_ALWAYS, " Before Installation of ACPI table \n"));
   Status = AcpiTable->InstallAcpiTable (AcpiTable,
                            &mTpm2AcpiTemplate,
                            sizeof(EFI_TPM2_ACPI_TABLE),
                            &TableKey);

  if(EFI_ERROR(Status))return Status;

  return Status;
}


EFI_STATUS
EFIAPI
Tpm20AcpiInitEntry (
  IN EFI_HANDLE                  ImageHandle,
  IN EFI_SYSTEM_TABLE            *SystemTable
)
{ 
   EFI_STATUS Status;

   InitAmiLib( ImageHandle, SystemTable );

   Status = Tpm20PublishAcpiTable ();

   return Status;
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
