//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**        5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093         **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//*************************************************************************
// $Header: /Alaska/SOURCE/Modules/TCG2/Common/AmiTcgPlatform/AmiTcgPlatformDxe/AmiTcgPlatformDxeLib.c 2     6/09/14 4:58p Fredericko $
//
// $Revision: 2 $
//
// $Date: 6/09/14 4:58p $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/TCG2/Common/AmiTcgPlatform/AmiTcgPlatformDxe/AmiTcgPlatformDxeLib.c $
// 
// 2     6/09/14 4:58p Fredericko
// Changes for SetVariable vulnerability during Runtime
// 
// 1     4/21/14 2:17p Fredericko
// 
// 2     3/14/14 3:24p Fredericko
// 
// 1     10/08/13 12:04p Fredericko
// Initial Check-In for Tpm-Next module
// 
// 1     7/10/13 5:55p Fredericko
// [TAG]  		EIP120969
// [Category]  	New Feature
// [Description]  	TCG (TPM20)
// 
// 7     10/30/12 10:47a Fredericko
// 
// 6     5/20/12 2:14p Fredericko
// 
// 5     9/27/11 10:33p Fredericko
// [TAG]  		EIP67286
// [Category]  	Improvement
// [Description]  	changes for Tcg Setup policy
// [Files]  		Tcg.sdl
// TcgPei.cif
// TcgPei.mak
// xtcgPei.c
// xTcgPeiAfterMem.c
// TcgPeiAfterMem.mak
// TcgDxe.cif
// TcgDxe.mak
// xTcgDxe.c
// AmiTcgPlatformPeilib.c
// AmiTcgPlatformDxelib.c
// 
// 4     7/25/11 3:46a Fredericko
// [TAG]  		EIP65177
// [Category]  	Spec Update
// [Severity]  	Minor
// [Description]  	Tcg Ppi Spec ver 1.2 update
// 
// 3     3/29/11 5:52p Fredericko
// Changes for core 464 and ACPI tables support
// 
// 2     3/29/11 2:28p Fredericko
// [TAG]        EIP 54642
// [Category] Improvement
// [Description] 1. Checkin Files related to TCG function override 
// 2. Include TCM and TPM auto detection
// [Files] Affects all TCG files
//
//
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:	AmiTcgPlatformDxeLib.c
//
// Description:	Function file for AmiTcgPlatformDxe library
//
//<AMI_FHDR_END>
//*************************************************************************
#include "AmiTcgPlatformDxeLib.h"


EFI_GUID TcgBoardEfiGlobalVariableGuid = TCG_EFI_GLOBAL_VARIABLE_GUID;
EFI_GUID AmitcgefiOsVariableGuid       = AMI_TCG_EFI_OS_VARIABLE_GUID;


EFI_GUID  gSetupGuid = SETUP_GUID;
EFI_GUID  gTcgAcpiSupportGuid= EFI_ACPI_SUPPORT_GUID;
EFI_GUID  gEfiAmiboardTcgWakeEventDataHobGuid = EFI_TCG_WAKE_EVENT_DATA_HOB_GUID;
EFI_GUID  gEfiAmiboardHobListGuid = TCG_EFI_HOB_LIST_GUID;

static UINT8                     TcgAMLDATA;

EFI_SMM_SYSTEM_TABLE             *mSmst;
EFI_SMM_BASE_PROTOCOL            *pSmmBase;

EFI_GUID                         gDsdtGuid = DSDT_GUID;

EFI_STATUS getSetupData (
    SETUP_DATA** ppsd,
    UINT32    * pattr,
    UINTN     * psz );



#define GET_HOB_TYPE( Hob )     ((Hob).Header->HobType)
#define GET_HOB_LENGTH( Hob )   ((Hob).Header->HobLength)
#define GET_NEXT_HOB( Hob )     ((Hob).Raw + GET_HOB_LENGTH( Hob ))
#define END_OF_HOB_LIST( Hob )  (GET_HOB_TYPE( Hob ) == \
                                 EFI_HOB_TYPE_END_OF_HOB_LIST)
extern
BOOLEAN
__stdcall AutoSupportType ();


//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   GetHob
//
// Description: Find instance of a HOB type in a HOB list
//
//
// Input:       IN UINT16  Type,
//              IN VOID    *HobStart
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
VOID* GetHob(
    IN UINT16 Type,
    IN VOID   *HobStart )
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
//
// Input:       IN    EFI_GUID *G1,
//              IN    EFI_GUID *G2
//
// Output:      BOOLEAN
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************
BOOLEAN CompareGuid(
    IN EFI_GUID *G1,
    IN EFI_GUID *G2 )
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




//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   LocateATcgHob
//
// Description: Finds a Tcg HOB
//
//
// Input:       IN    UINTN NoTableEntries,
//              IN    EFI_CONFIGURATION_TABLE   *ConfigTable,
//              IN    EFI_GUID    *HOB_guid
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
VOID* LocateATcgHob(
    IN UINTN                   NoTableEntries,
    IN EFI_CONFIGURATION_TABLE *ConfigTable,
    IN EFI_GUID                *HOB_guid )
{
    VOID *HobStart;
    VOID *PtrHob;

    while ( NoTableEntries > 0 )
    {
        NoTableEntries--;

        if ((!MemCmp(
                 &ConfigTable[NoTableEntries].VendorGuid,
                 &gEfiAmiboardHobListGuid, sizeof(EFI_GUID)
                 )))
        {
            HobStart = ConfigTable[NoTableEntries].VendorTable;

            if ( !EFI_ERROR(
                     GetNextGuidHob( &HobStart, HOB_guid, &PtrHob, NULL )
                     ))
            {
                return PtrHob;
            }
        }
    }
    return NULL;
}




//*******************************************************************************
//<AMI_PHDR_START>
//
// Procedure:   GetTcgWakeEventType
//
// Description: Reads and Reports the source of the wake-up event.
//
// Input:       IN OUT UINT8   *pWake   - output parameter returns the indication of the
//                                        type of the wakup source:
//                              one of the following:
//                              SMBIOS_WAKEUP_TYPE_OTHERS
//                              SMBIOS_WAKEUP_TYPE_UNKNOWN
//                              SMBIOS_WAKEUP_TYPE_APM_TIMER
//                              SMBIOS_WAKEUP_TYPE_MODEM_RING
//                              SMBIOS_WAKEUP_TYPE_LAN_REMOTE
//                              SMBIOS_WAKEUP_TYPE_POWER_SWITCH
//                              SMBIOS_WAKEUP_TYPE_PCI_PME
//                              SMBIOS_WAKEUP_TYPE_AC_POWER_RESTORED
//
// Output:      EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//******************************************************************************
EFI_STATUS GetTcgWakeEventType(
    IN OUT UINT8 *pWake  )
{
    EFI_BOOT_MODE           *BootMode = NULL;
    UINTN                   NoTableEntries;
    EFI_CONFIGURATION_TABLE *ConfigTable;
    VOID                    *HobStart;

    *pWake = SMBIOS_WAKEUP_TYPE_UNKNOWN;

    NoTableEntries = pST->NumberOfTableEntries,
    ConfigTable    = pST->ConfigurationTable;

    while ( NoTableEntries > 0 )
    {
        NoTableEntries--;

        if ( !MemCmp(
                 &ConfigTable[NoTableEntries].VendorGuid,
                 &gEfiAmiboardHobListGuid, sizeof(EFI_GUID)
                 ))
        {
            HobStart = ConfigTable[NoTableEntries].VendorTable;

            if ( !EFI_ERROR(
                     GetNextGuidHob( &HobStart,
                                     &gEfiAmiboardTcgWakeEventDataHobGuid,
                                     &BootMode, NULL )
                     ))
            {
                break;
            }
        }
    }

    if ( BootMode != NULL )
    {
        if ( *BootMode == BOOT_ON_S4_RESUME || *BootMode == BOOT_ON_S5_RESUME  
              || *BootMode == BOOT_WITH_FULL_CONFIGURATION )
        {
            *pWake = (UINT8)SMBIOS_WAKEUP_TYPE_POWER_SWITCH;
        }
    }
    return EFI_SUCCESS;
}


//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   TcgGetDSDTTable
//
// Description: Gets Acpi DSDT table
//
//
// Input:
//
// Output:      VOID *
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************
VOID* TcgGetDSDTTable(EFI_ACPI_SUPPORT_PROTOCOL * mTcgAcpiSupport )
{
    INTN                   Index;
    PACPI_HDR              Table;
    UINTN                  Handle;
    EFI_STATUS             Status;
    EFI_ACPI_TABLE_VERSION Version;
    

    if(mTcgAcpiSupport == NULL)return NULL;

    for ( Index = 0;; ++Index )
    {
        Status = mTcgAcpiSupport->GetAcpiTable(
            mTcgAcpiSupport,
            Index,
            &Table,
            &Version,
            &Handle
            );

        if ( EFI_ERROR( Status ))
        {
            return 0;
        }

        if (((PACPI_HDR)Table)->Signature == FACP_SIG )
        {
            return (VOID*)(UINTN)((PFACP32)Table )->DSDT;
        }
    }
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   TcgConvertAslName
//
// Description: converts String a to ASL string NAME
//
//
// Input:       IN UINT8 *AslName
//
// Output:      UINT32
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************
UINT32 TcgConvertAslName(
    IN UINT8 *AslName )
{
    AML_NAME_SEG n;
    //Limit to 4 characters
    UINTN        l = Strlen( AslName );

    //-------------------------
    n.NAME = 0x5F5F5F5F;
    MemCpy( &n.Name[0], AslName, l );
    return n.NAME;
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   TcgFindAslObjectName
//
// Description: converts String a to ASL string NAME
//
//
// Input:       IN      UINT8 *Start,
//              IN      UINT8 *ObjName,
//              IN      UINTN Len
//
// Output:      VOID    *
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************
VOID* TcgFindAslObjectName(
    IN UINT8 *Start,
    IN UINT8 *ObjName,
    IN UINTN Len )
{
    unsigned int i;
    UINT8        *p;
    AML_NAME_SEG *obj, nm;

    //------------------------------
    nm.NAME = TcgConvertAslName( ObjName );

    p = Start;

    for ( i = 0; i < Len; i++ )
    {
        obj = (AML_NAME_SEG*)(&p[i]);

        if ( obj->NAME != nm.NAME )
        {
            continue;
        }
        return &p[i];
    }
    return NULL;
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   TcgCheckOpCode
//
// Description: converts String a to ASL string NAME
//
//
// Input:       IN         UINT8 *NameStart,
//              IN         UINT8 OpCode,
//              IN         UINT8 ExtOpCode,
//              IN  OUT    ASL_OBJ_INFO *ObjInfo
//
// Output:      BOOLEAN
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************
BOOLEAN TcgCheckOpCode(
    IN UINT8            *NameStart,
    IN UINT8            OpCode,
    IN UINT8            ExtOpCode,
    IN OUT ASL_OBJ_INFO *ObjInfo )
{
    UINT8 *p;

    //---------------------
    //Maximum number of bytes in PackageLength is 4
    if ((*(NameStart - 1)) == TCGAML_PR_ROOT || (*(NameStart - 1)) ==
        TCGAML_PR_PARENT )
    {
        NameStart--;
    }

    //if we Looking For ASL Name Object its a special case.
    if ( OpCode == TCGAML_OP_NAME && !ExtOpCode )
    {
        p = NameStart - 1;

        if ( *p == OpCode )
        {
            ObjInfo->Object  = p;
            ObjInfo->ObjName = NameStart;
            ObjInfo->Length  = 0;
            return TRUE;
        }
        return FALSE;
    }

    //if we Looking For ASL Name Object its a special case.
    if ( OpCode == TCGAML_OP_OPREG && ExtOpCode )
    {
        p = NameStart - 2;

        if ( *p == ExtOpCode && *(p + 1) == OpCode )
        {
            ObjInfo->Object  = p;
            ObjInfo->ObjName = NameStart;
            ObjInfo->Length  = 0;
            return TRUE;
        }
        return FALSE;
    }
    return FALSE;
}


EFI_STATUS TcgSetVariableWithNewAttributes(
    IN CHAR16 *Name, IN EFI_GUID *Guid, IN UINT32 Attributes,
    IN UINTN DataSize, IN VOID *Data    
)
{
    EFI_STATUS Status;
    
    Status = pRS->SetVariable(Name, Guid, Attributes, DataSize, Data);
    if (!EFI_ERROR(Status) || Status != EFI_INVALID_PARAMETER) return Status;

    Status = pRS->SetVariable(Name, Guid, 0, 0, NULL);
    if (EFI_ERROR(Status)) return Status;

    return pRS->SetVariable(Name, Guid, Attributes, DataSize, Data);
}



//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   TcgGetAslObj
//
// Description: converts String a to ASL string NAME
//
//
// Input:       IN      UINT8 *Start,
//              IN      UINTN Length,
//              IN      UINT8 *Name,
//              IN      ASL_OBJ_TYPE ObjType,
//              IN      ASL_OBJ_INFO *ObjInfo
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
EFI_STATUS TcgGetAslObj(
    IN UINT8        *Start,
    IN UINTN        Length,
    IN UINT8        *Name,
    IN ASL_OBJ_TYPE ObjType,
    IN ASL_OBJ_INFO *ObjInfo )
{
    UINT8   *pn, *s, eop, op;
    UINTN   l, i;
    BOOLEAN objfound = FALSE;

    s = Start;
    l = Length;

    while ( !objfound )
    {
        pn = TcgFindAslObjectName( s, Name, l );

        if ( !pn )
        {
            return EFI_NOT_FOUND;
        }

        //If we found the name let's check if it is the Object we are looking for
        //it could be just object referance, or field definition inside the object,
        //or double name, or multiple name definition we must filter such situations
        // and make sure we have got the actual object but not its reference instance
        switch ( ObjType )
        {
        case    otScope:
            i   = 0;
            eop = 0;
            op  = TCGAML_OP_SCOPE;
            break;
        case    otName:
            i   = 0;
            eop = 0;
            op  = TCGAML_OP_NAME;
            break;
        case    otProc:
            i   = 6;
            eop = TCGAML_PR_EXTOP;
            op  = TCGAML_OP_PROC;
            break;
        case    otTermal:
            i   = 0;
            eop = TCGAML_PR_EXTOP;
            op  = TCGAML_OP_THERMAL;
            break;
        case    otDevice:
            i   = 0;
            eop = TCGAML_PR_EXTOP;
            op  = TCGAML_OP_DEVICE;
            break;
        case    otMethod:
            i   = 1;
            eop = 0;
            op  = TCGAML_OP_METHOD;
            break;
        case    otPwrRes:
            i   = 3;
            eop = TCGAML_PR_EXTOP;
            op  = TCGAML_OP_PWRRES;
            break;
        case    otOpReg:
            i   = 0;
            eop = TCGAML_PR_EXTOP;
            op  = TCGAML_OP_OPREG;
            break;

        default: return EFI_NOT_FOUND;
        } //switch

        objfound = TcgCheckOpCode( pn, op, eop, ObjInfo );

        if ( !objfound )
        {
            l -= (UINTN)( pn - s ) - 4;
            s  = pn + 4;
            continue;
        }
        ObjInfo->ObjType   = ObjType;
        ObjInfo->DataStart = pn + i + 4;

        return EFI_SUCCESS;
    }

    return EFI_NOT_FOUND;
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   LocateACPITableProtocol
//
// Description: Locates ACPI Table Protocol
//
//
// Input:       IN   EFI_GUID *Protocol,
//              OUT  VOID **Instance
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
#if !defined(AmiBoardInfo_SUPPORT) || (AmiBoardInfo_SUPPORT==0)
EFI_STATUS LocateACPITableProtocol(
    IN EFI_GUID *Protocol,
    OUT VOID    **Instance )
{
    EFI_STATUS             Status;
    EFI_HANDLE             *HandleBuffer;
    UINTN                  NumberOfHandles;
    EFI_FV_FILETYPE        FileType;
    UINT32                 FvStatus = 0;
    EFI_FV_FILE_ATTRIBUTES Attributes;
    UINTN                  Size;
    UINTN                  i;


    Status = pBS->LocateHandleBuffer( ByProtocol,
                                      Protocol,
                                      NULL,
                                      &NumberOfHandles,
                                      &HandleBuffer );

    if ( EFI_ERROR( Status ))
    {
        return Status;
    }


    for ( i = 0; i < NumberOfHandles; i++ )
    {
        Status = pBS->HandleProtocol( HandleBuffer[i], Protocol, Instance );

        if ( EFI_ERROR( Status ))
        {
            return Status;
        }

        Status = ((EFI_FIRMWARE_VOLUME_PROTOCOL*)(*Instance))->ReadFile(
            *Instance,
            &
            gDsdtGuid,
            NULL,
            &Size,
            &FileType,
            &Attributes,
            &FvStatus );

        if ( Status == EFI_SUCCESS )
        {
            break;
        }
    }
    pBS->FreePool( HandleBuffer );
    return Status;
}
#endif



//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:  read_PPI_request
//
// Description: Reads and returns TCG PPI requests Value
//
//
// Input:
//
// Output:      UINT8
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************
UINT8 ReadPpiRequest( )
{
    UINTN          Size = sizeof(AMI_PPI_NV_VAR);
    AMI_PPI_NV_VAR Temp;
    EFI_STATUS     Status;

    Status = pRS->GetVariable( L"AMITCGPPIVAR", \
                               &AmitcgefiOsVariableGuid, \
                               NULL, \
                               &Size, \
                               &Temp );

    if(Status == EFI_NOT_FOUND)
    {
        Temp.RQST    = 0;
        Temp.RCNT    = 0;
        Temp.ERROR   = 0;
        Temp.Flag    = 0;
        Temp.AmiMisc = 0;

       Status =  TcgSetVariableWithNewAttributes(L"AMITCGPPIVAR", &AmitcgefiOsVariableGuid, \
                                        EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS,\
                                        Size, &Temp );
    }

    return Temp.RQST;
}





//****************************************************************************************
//<AMI_PHDR_START>
//
// Procedure: write_PPI_result
//
// Description: Updates TCG PPI variable in NVRAM
//
//
// Input:       IN  UINT8 last_op,
//              IN  UINT16 status
//
// Output:      VOID
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//****************************************************************************************
void WritePpiResult(
    IN UINT8  last_op,
    IN UINT16 status )
{
    UINTN          Size = sizeof(AMI_PPI_NV_VAR);
    AMI_PPI_NV_VAR Temp;
    EFI_STATUS     Status;
    UINT8          Manip = 0;

    Status = pRS->GetVariable( L"AMITCGPPIVAR", \
                               &AmitcgefiOsVariableGuid, \
                               NULL, \
                               &Size, \
                               &Temp );

    //now set variable to data
    Temp.RQST  = Manip;
    Manip      = (UINT8)( status & 0xFFFF );
    Temp.ERROR = Manip;

    if(status>0xFF && status<0xFFFF)
    {
        Temp.AmiMisc = (UINT8)(status >> 8);
    }else{
        Temp.AmiMisc = 0;
    }

    if ( EFI_ERROR( Status ))
    {
        TRACE((TRACE_ALWAYS, "Error Setting Return value\n"));
        return;
    }

    Status =  TcgSetVariableWithNewAttributes(L"AMITCGPPIVAR", &AmitcgefiOsVariableGuid, \
                                        EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS,\
                                        Size, &Temp );
}



//****************************************************************************************
//<AMI_PHDR_START>
//
// Procedure: getSetupData
//
// Description: Retrieved SETUP_DATA structure from NVRAM
//
//
// Input:       IN  OUT   SETUP_DATA** ppsd,
//              IN  UINT32* pattr,
//              IN  UINTN* psz
//
// Output:      EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//****************************************************************************************
EFI_STATUS getSetupData(
    IN OUT SETUP_DATA** ppsd,
    IN UINT32        * pattr,
    IN UINTN         * psz )
{
    EFI_STATUS Status;
    UINTN      sz = 0;

    *ppsd  = NULL;
    Status = pRS->GetVariable( L"Setup", &gSetupGuid, pattr, &sz, *ppsd );

    if ( !EFI_ERROR( Status ))
    {
        return Status;
    }

    if ( Status == EFI_BUFFER_TOO_SMALL )
    {
        Status = pBS->AllocatePool( EfiBootServicesData, sz, ppsd );

        if ( !(*ppsd))
        {
            return EFI_OUT_OF_RESOURCES;
        }
        Status = pRS->GetVariable( L"Setup", &gSetupGuid, pattr, &sz, *ppsd );
    }

    if ( psz != NULL )
    {
        *psz = sz;
    }
    return Status;
}



//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   GetDsdt
//
// Description: Locates ACPI Table Protocol
//
//
// Input:       IN   OUT  mem_in *dsdt
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
#if !defined(AmiBoardInfo_SUPPORT) || (AmiBoardInfo_SUPPORT==0)
EFI_STATUS GetDsdt(
    IN OUT mem_in *dsdt )
{
    EFI_FIRMWARE_VOLUME_PROTOCOL *fv;
    EFI_STATUS                   Status;
    UINT32                       FvStatus;

    //---------------------------------------------
    Status = pBS->LocateProtocol( &gEfiFirmwareVolumeProtocolGuid, NULL, &fv );
    Status = LocateACPITableProtocol( &gEfiFirmwareVolumeProtocolGuid, &fv );

    if ( EFI_ERROR( Status ))
    {
        return EFI_ABORTED;
    }

    dsdt->address = 0;
    Status
        = fv->ReadSection( fv,
                           &gDsdtGuid,
                           EFI_SECTION_RAW,
                           0,
                           (VOID**)&dsdt->address,
                           &((UINTN)dsdt->size),
                           &FvStatus );


    if ( EFI_ERROR( Status ))
    {
        dsdt->address = 0;
        dsdt->datat   = 3;
        dsdt->size    = 0;
    }
    else {
        dsdt->datat = 2;
    }


    return EFI_SUCCESS;
}
#endif




//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   TcgUpdateAslNameObject
//
// Description: Locates ACPI Table Protocol
//
//
// Input:       IN   PACPI_HDR PDsdt,
//              IN   UINT8 *ObjName,
//              IN   UINT64 Value
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
EFI_STATUS TcgUpdateAslNameObject(
    IN PACPI_HDR PDsdt,
    IN UINT8     *ObjName,
    IN UINT64    Value )
{
    EFI_STATUS   Status;
    ASL_OBJ_INFO obj;
    UINT32       Length;
    UINT8        *ptr;


    Length = PDsdt->Length - sizeof(ACPI_HDR);
    ptr    = (UINT8*)PDsdt + sizeof(ACPI_HDR);

    Status = TcgGetAslObj( ptr, Length, ObjName, otName, &obj );


    switch ( *((UINT8*)obj.DataStart))
    {
    case TCGAML_PR_BYTE: {
        UINT8 *p = (UINT8*)((UINT8*)obj.DataStart + 1);
        //----------------------------------
        *p = (UINT8)Value;
    } break;

    case TCGAML_PR_WORD: {
        UINT16 *p = (UINT16*)((UINT8*)obj.DataStart + 1);
        //----------------------------------
        *p = (UINT16)Value;
    } break;

    case TCGAML_PR_DWORD: {
        UINT32 *p = (UINT32*)((UINT8*)obj.DataStart + 1);
        //----------------------------------
        *p = (UINT32)Value;
    } break;

    case TCGAML_PR_QWORD: {
        UINT64 *p = (UINT64*)((UINT8*)obj.DataStart + 1);
        //----------------------------------
        *p = (UINT64)Value;
    } break;

    case TCGAML_ZERO_OP: case TCGAML_ONE_OP: {
        if ((Value == 0) || (Value == 1))
        {
            UINT8 *p = (UINT8*)((UINT8*)obj.DataStart);
            *p = (UINT8)Value;
        }
        else {
            return EFI_INVALID_PARAMETER;
        }
    } break;
    default: {
        return EFI_INVALID_PARAMETER;
    }
    }
    return EFI_SUCCESS;
}




//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   TcgUpdateAslObj
//
// Description: Updates TPM acpi variable for TPM support
//
//
// Input:       IN   EFI_EVENT ev,
//              IN   VOID *ctx,
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
EFI_STATUS TcgUpdateAslObj(
    IN EFI_EVENT ev,
    IN VOID      *ctx )
{
    EFI_STATUS Status;
    PACPI_HDR  DsdtTable;
    EFI_ACPI_SUPPORT_PROTOCOL  *mTcgAcpiSupport;

    Status = pBS->LocateProtocol( &gTcgAcpiSupportGuid, NULL, &mTcgAcpiSupport );

    if ( EFI_ERROR( Status ))
    {
        TRACE((TRACE_ALWAYS, "TcgBoard_c:Unable to locate AcpiSupport\n"));
        return Status;
    }

     DsdtTable = TcgGetDSDTTable(mTcgAcpiSupport);

    if ( !DsdtTable )
    {
        TRACE((TRACE_ALWAYS, "TcgBoard.c::DSDT Table not found.\n"));
        return EFI_NOT_FOUND;
    }

    Status = TcgUpdateAslNameObject( DsdtTable, "TPMF", TcgAMLDATA );
    
    //also update TCM flags
    if(AutoSupportType()){
        TcgAMLDATA  = 0x1;
        Status = TcgUpdateAslNameObject( DsdtTable, "TCMF", TcgAMLDATA );      
     }else{
        TcgAMLDATA  = 0x0;
        Status = TcgUpdateAslNameObject( DsdtTable, "TCMF", TcgAMLDATA );
     }

    TRACE((TRACE_ALWAYS, "TcgBoard_c:TCGUpdateAslNameOpject_DONE\n"));

    return Status;
}





//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   UpDateASL
//
// Description: Update TCG ASL Support in ACPI base
//
//
// Input:       IN    UINT8    TcgSupport
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
EFI_STATUS UpDateASL(
    IN UINT8 TcgSupport )
{
    EFI_EVENT                  ev;
    static VOID                *reg;
    EFI_STATUS                 Status;
    VOID                       *ctx;
    EFI_ACPI_SUPPORT_PROTOCOL  *mTcgAcpiSupport;

    TcgAMLDATA = TcgSupport;

    Status = pBS->LocateProtocol( &gTcgAcpiSupportGuid, NULL, &mTcgAcpiSupport );

    if ( EFI_ERROR( Status ))
    {
        Status = pBS->CreateEvent( EFI_EVENT_NOTIFY_SIGNAL,
                                   EFI_TPL_DRIVER, TcgUpdateAslObj, &reg, &ev );
        ASSERT( !EFI_ERROR( Status ));
        Status = pBS->RegisterProtocolNotify( &gTcgAcpiSupportGuid, ev, &reg );

        return Status;
    }
    ev  = NULL;
    ctx = NULL;

    Status = TcgUpdateAslObj( ev, ctx );
    return Status;
}
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**     5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
