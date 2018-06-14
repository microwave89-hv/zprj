//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             5555 Oakbrook Pkwy, Norcross, GA 30093               **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
// $Header: /Alaska/BIN/Modules/ACPI/Template/Core/mptable.c 31    12/13/12 12:01p Oleksiyy $
//
// $Revision: 31 $
//
// $Date: 12/13/12 12:01p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/ACPI/Template/Core/mptable.c $
// 
// 31    12/13/12 12:01p Oleksiyy
// [TAG]  		EIP109290
// [Category]  	Improvement
// [Description]  	Issues found by CppCheck in ACPI eModule
// [Files]  		AcpiCore.c, mptable.c, AmlString.c, BootScriptSave.c and
// BootScriptExecuter.c
// 
// 30    1/12/12 4:51p Oleksiyy
// [TAG]  		EIP80870 
// [Category]  	Improvement
// [Description]  	MP table entry has a zero sized Address Length.
// [Files]  		mptable.c
// 
// 29    1/12/12 4:15p Oleksiyy
// [TAG]  		EIP79240
// [Category]  	Improvement
// [Description]  	Added Variable to handle the situation when MP table
// created multiple times.
// [Files]  		mptable.c
// 
// 28    11/29/11 12:20p Oleksiyy
// [TAG]  		EIP76814 
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	MP_TABLE_LEGACY_REGION_LOCATION = 0 causes build error
// [RootCause]  	Unreferenced variable: LegacyBiosProtocol
// [Solution]  	Variable declared only if MP_TABLE_LEGACY_REGION_LOCATION
// != 0
// [Files]  		mptable.c
// 
// 27    7/19/11 11:31a Oleksiyy
// [TAG]  		EIP64108 
// [Category]  	Improvement
// [Description]  	ACPI, convert or update all eModules to be compliant
// with PI 1.2, and UEFI 2.3.1 specifications. 
// [Files]  		AcpiCore.c, mptable.c, AcpiS3Save.c, S3Resume.dxs,
// S3Resume.c, AcpiPeiS3Func.c, BootScriptExecuter.c and DxeIpl.c
// 
// 26    5/25/10 5:07p Yakovlevs
// Fixed Issue when with Multiple IO APICs, upper IOAPIC's INT_IN 0 was
// excluded from the table.
// 
// 25    9/28/09 3:59p Yakovlevs
// 
// 24    5/27/09 5:41p Yakovlevs
// CSM Protocol definition moved in #if scope
// 
// 23    5/18/09 10:11a Yakovlevs
// Added support of IOAPIC discovery tokens. Some project don't want
// certain algorithms to be used.
// 
// 22    5/15/09 12:49p Yakovlevs
// Fixed logic in IOAPIC discovery ordering.
// 
// 21    5/14/09 5:39p Yakovlevs
// Added code to use "USE_BOARD_INFO_APIC_DATA" token
// 
// 20    5/08/09 1:16p Yakovlevs
// Made ACPI Driver use AMI Board  Info Protocol if available without
// breaking compatibility.
// 
// 19    5/07/09 5:46p Markw
// Use #ifdef ACPI_INFO2_PROTOCOL_PUBLISHED to exclude code that uses ACPI
// INFO 2 for CPUs that provide the header files.
// 
// 18    5/04/09 5:49p Markw
// EIP #17903 If AmiCpuInfo2 Protocol available, MP tables will use this
// instead of hobs.
// 
// 17    3/26/09 4:51p Oleksiyy
// New ACPI Core implementation - improves logic, execution time and
// memory usage of ACPI module.
// 
// 16    2/06/09 4:52p Yakovlevs
// Added Creating EFI Config Table Entry for MPS 14.
// 
// 15    10/06/08 3:07p Yakovlevs
// Restored accidentally removed fixes.
// 
// 14    9/25/08 4:14p Artems
// Solve problem with non-consecutive IO APIC IDs
// 
// 13    7/14/08 3:26p Markw
// In for loop count total number of local apics (hyper-threading) not
// just number of cores. Code already correctly skips hyper-treading in
// for loop.
// 
// 12    7/07/08 5:06p Artems
// Fixed bug in PCI IOAPIC detection
// 
// 11    6/11/08 5:58p Markw
// Update MpsTableAddCpuEntry function to multiple cores and threads to
// get total CPUs instead just cores.
// 
// 10    4/15/08 9:16p Yakovlevs
// Functions Headers added
// 
// 9     4/11/07 5:44p Artems
// Multi processor detection added
// 
// 8     3/28/07 10:42a Artems
// Fixed bug  - added System memory map entry for legacy video
// 
// 7     3/19/07 12:19p Felixp
// Clean up
// 
// 6     3/13/07 6:40p Yakovlevs
// 
// 5     3/13/07 5:41p Artems
// MPS 1.4 TABLE SUPPORT added
// 
// 3     2/06/07 5:38p Artems
// 
// 2     2/06/07 5:25p Artems
// 
// 1     2/06/07 4:54p Artems
// 

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:	mptable.c
//
// Description:	MPS table builder functions implementation
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include <Token.h>

//------------------------ Include files ------------------------------

#include <AmiDxeLib.h>
#include <AmiHobs.h>

#include <Protocol/LegacyBios.h>
#include <Protocol/AmiCpuInfo.h>

#ifdef ACPI_INFO2_PROTOCOL_PUBLISHED
#include <Protocol\AmiCpuInfo2.h>
#endif


#include "acpicore.h"
#include "mptable.h"


#include <Protocol\AmiBoardInfo.h>
extern AMI_BOARD_INFO_PROTOCOL     *gAmiBoardInfoProtocol;

//------------------------ Global variables ---------------------------

static EFI_GUID gMpsTableGuid = MPS_TABLE_GUID;
static EFI_GUID EfiLegacyBiosProtocolGuid = EFI_LEGACY_BIOS_PROTOCOL_GUID;
AMI_CPU_INFO_PROTOCOL *AmiCpuInfoProtocol = NULL;
static EFI_GUID AmiCpuInfoProtocolGuid = AMI_CPU_INFO_PROTOCOL_GUID;
static EFI_EVENT MpsTableReadyToBootEvent = 0;
static MP_FLOATING_POINTER MpsTableFloatingPointer;
static VOID *MpsTablePointer = NULL;
static VOID *MpsTableCurrentPointer = NULL;
static VOID *MpsExTablePointer = NULL;
static VOID *MpsExTableCurrentPointer = NULL;
static UINT16  BaseTableLength = 0;
static UINT16  BaseTableEntryCount = 0;
static UINT16  ExtendedTableLength = 0;
static UINT8   OemId[8] = CONVERT_TO_STRING(T_ACPI_OEM_TBL_ID);   //{ 0,1,2,3,4,5,6,7 };
static UINT8   ProductId[12] = CONVERT_TO_STRING(T_ACPI_OEM_ID);   //{ 0,1,2,3,4,5,6,7,8,9,0xA, 0xB };

static BUS_INFO BusEntry[MP_TABLE_MAX_BUS_ENTRIES];
static UINT8    MaxBusId = 0;
static UINT8    CurrentBusEntry = 0;
static UINT8    IsaBusId = 0;
static UINT8    *BusTypeString[] = {"CBUS  ", "CBUSII", "EISA  ", "FUTURE", "INTERN", "ISA   ",
                                    "MBI   ", "MBII  ", "MCA   ", "MPI   ", "MPSA  ", "NUBUS ",
                                    "PCI   ", "PCMCIA", "TC    ", "VL    ", "VME   ", "XPRESS" };
static UINT8    BridgeBusTypes[] = { 12, 5, 2, 8, 12, 13, 11 }; //each number represents corresponding
                                                                //number in BusTypeString array, i.e.
                                                                //bridge subclass 0 - PCI host has number
                                                                //12 in array, subclass 1 - ISA bridge -
                                                                //number 5 etc.
static IO_APIC_INFO IoApicEntry[MP_TABLE_MAX_IO_APIC_ENTRIES];
static UINT8    CurrentIoApicEntry = 0;

#ifdef ACPI_INFO2_PROTOCOL_PUBLISHED
extern AMI_CPU_INFO_2_PROTOCOL* gAmiCpu2Info;
#endif


extern ISO_PARAMETER_TABLE IsoTbl[];
EFI_STATUS MpsTableCreateStatus =  EFI_NO_RESPONSE;
EFI_STATUS MpsTableFloatPointerModifyStatus = EFI_NO_RESPONSE;
BOOLEAN MpsTableWasCreated = FALSE;
//------------------------ Functions ----------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:    MpsTableBuilderInit
// 
// Description:  MPS table builder entry point 
//
// Input:
// IN EFI_HANDLE ImageHandle    - MPS table builder image handle
// IN EFI_SYSTEM_TABLE *SystemTaple    - pointer to system table
//               
// Output:
// EFI_SUCCESS    - Initialization completed successfully
// EFI_ERROR      - Initialization failed
//
// Modified:    MpsTableReadyToBootEvent
// 
//--------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS MpsTableBuilderInit(
	IN EFI_HANDLE ImageHandle,
	IN EFI_SYSTEM_TABLE *SystemTable)
{
    EFI_STATUS Status;

	InitAmiLib(ImageHandle,SystemTable);

    Status = CreateReadyToBootEvent(TPL_CALLBACK,
                                    MpsTableReadyToBootNotify,
                                    NULL,
                                    &MpsTableReadyToBootEvent);
	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:    MpsTableReadyToBootNotify
// 
// Description:  MPS table builder ReadyToBoot notification function 
//
// Input:
// IN EFI_EVENT Event      - signalled event
// IN VOID *Context    - pointer to calling context
//    
// Output:           
// VOID
//
//--------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID MpsTableReadyToBootNotify(
	IN EFI_EVENT Event, 
    IN VOID *Context)
{
    EFI_STATUS Status;
    
    if(EFI_ERROR(MpsTableCreateStatus)) 
    {
        MpsTableCreateStatus = MpsTableCreate();
        if(EFI_ERROR(MpsTableCreateStatus))
            return;
    }
    if(EFI_ERROR(MpsTableFloatPointerModifyStatus)) 
        MpsTableFloatPointerModifyStatus = MpsTableFloatPointerModify();

    //Install a Configuration table  Entry
    Status=pBS->InstallConfigurationTable(&gMpsTableGuid,MpsTablePointer);
    ASSERT_EFI_ERROR(Status);
    if(EFI_ERROR(Status)) return;
    //After we did everything needed 
    pBS->CloseEvent(Event);

    return;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:    MpsTableFloatPointerModify
// 
// Description:  Fills MP_FLOATING_POINTER structure with actual data
//               and places it into F000 segment 
//
// Input:
// VOID
//            
// Output:   
// EFI_SUCCESS    - Pointer created and placed successfully
// EFI_ERROR      - Some error occurs
//
// Modified:    MpsTableFloatingPointer
// 
//--------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS MpsTableFloatPointerModify(VOID)
{
    EFI_STATUS Status;
    EFI_LEGACY_BIOS_PROTOCOL *LegacyBiosProtocol;
    VOID *LegacyRegionAddress;

    MpsTableFloatingPointer.Signature = MP_FLOATING_POINTER_SIGNATURE;

//at this point we have address of MPS table
    MpsTableFloatingPointer.PhysicalAddresPointer = (UINT32) MpsTablePointer;
 
//length in 16-byte paragraphs  
    MpsTableFloatingPointer.Length = sizeof(MP_FLOATING_POINTER)/16;  

//here must be token  
    MpsTableFloatingPointer.VersionNumber = MP_TABLE_VERSION_1_4;

//force checksum to zero before calculate actual checksum
    MpsTableFloatingPointer.CheckSum = 0;

//here must be token
    MpsTableFloatingPointer.DefaultConfiguration = 0;

//here must be token
    MpsTableFloatingPointer.IMCRflag = 0;

    MpsTableFloatingPointer.Reserved[0] = 0;
    MpsTableFloatingPointer.Reserved[1] = 0;
    MpsTableFloatingPointer.Reserved[2] = 0;

//now we are ready to calculate checksum
    MpsTableFloatingPointer.CheckSum = ChsumTbl((UINT8 *)&MpsTableFloatingPointer,
                                                sizeof(MP_FLOATING_POINTER));

    Status = pBS->LocateProtocol(&EfiLegacyBiosProtocolGuid,
                                 NULL,
                                 &LegacyBiosProtocol);
    if(EFI_ERROR(Status))
        return Status;

    Status = LegacyBiosProtocol->GetLegacyRegion(LegacyBiosProtocol,
                                        (UINTN)sizeof(MP_FLOATING_POINTER),
                                        F0000_BIT,
                                        0x10,
                                        &LegacyRegionAddress);
    if(EFI_ERROR(Status))
        return Status;

    Status = LegacyBiosProtocol->CopyLegacyRegion(LegacyBiosProtocol,
                                        (UINTN) sizeof(MP_FLOATING_POINTER),
                                        LegacyRegionAddress,
                                        (VOID *) &MpsTableFloatingPointer);
    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:    MpsTableCreate
// 
// Description:  Allocates space and creates MPS table 
//
// Input:
// VOID
//               
// Output:
// EFI_SUCCESS    - function executed successfully
// EFI_ERROR      - some error occured
//
//--------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS MpsTableCreate(VOID)
{
    EFI_STATUS Status;
    UINT16 EntryCount;

    if (MpsTableWasCreated)
        return MpsTableAddHeader();    

    Status = pBS->AllocatePool(EfiBootServicesData,
                               MP_TBL_TMP_BUFFER_SIZE,
                               &MpsTablePointer);
    if(EFI_ERROR(Status))
        return Status;

    MpsTableCurrentPointer = MpsTablePointer;

//split buffer onto two parts for base and extended tables
    MpsExTablePointer = MpsTablePointer;
    (UINT8 *)MpsExTablePointer += ((MP_TBL_TMP_BUFFER_SIZE)/2);
    MpsExTableCurrentPointer = MpsExTablePointer;

//Leave placeholder for header
    (UINT8 *)MpsTableCurrentPointer += sizeof(MP_CONFIGURATION_TABLE_HEADER);
    BaseTableLength += sizeof(MP_CONFIGURATION_TABLE_HEADER);

//add CPU Entry
    EntryCount = MpsTableAddCpuEntry();
    (UINT8 *)MpsTableCurrentPointer += sizeof(MP_TABLE_CPU_ENTRY) * EntryCount;
    BaseTableLength += sizeof(MP_TABLE_CPU_ENTRY) * EntryCount;
    BaseTableEntryCount += EntryCount;    

//add Bus Entry
    EntryCount = MpsTableAddBusEntry();
    (UINT8 *)MpsTableCurrentPointer += sizeof(MP_TABLE_BUS_ENTRY) * EntryCount;
    BaseTableLength += sizeof(MP_TABLE_BUS_ENTRY) * EntryCount;
    BaseTableEntryCount += EntryCount;

//add IO Apic Entry
    EntryCount = MpsTableAddIoApicEntry();
    (UINT8 *)MpsTableCurrentPointer += sizeof(MP_TABLE_IO_APIC_ENTRY) * EntryCount;
    BaseTableLength += sizeof(MP_TABLE_IO_APIC_ENTRY) * EntryCount;
    BaseTableEntryCount += EntryCount;

//add Interrupt assignment Entry
    EntryCount = MpsTableAddIntAssignEntry();
    (UINT8 *)MpsTableCurrentPointer += sizeof(MP_TABLE_INT_ASSIGN_ENTRY) * EntryCount;
    BaseTableLength += sizeof(MP_TABLE_INT_ASSIGN_ENTRY) * EntryCount;
    BaseTableEntryCount += EntryCount;

//add Local interrupt assignment Entry
    EntryCount = MpsTableAddLocalIntAssignEntry();
    (UINT8 *)MpsTableCurrentPointer += sizeof(MP_TABLE_LOCAL_INT_ASSIGN_ENTRY) * EntryCount;
    BaseTableLength += sizeof(MP_TABLE_LOCAL_INT_ASSIGN_ENTRY) * EntryCount;
    BaseTableEntryCount += EntryCount;

    MpsTableAddExtendedTable();
    
    MpsTableWasCreated = TRUE;
    
    return MpsTableAddHeader();
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:    MpsTableAddHeader
// 
// Description:  Creates MPS table header, allocates space and copies entire
//               table into RuntimeServicesData memory
//
// Input:
// VOID
//               
// Output:
// EFI_SUCCESS - function executed successfully
//
// Modified:    MpsTablePointer
// 
//--------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS MpsTableAddHeader(VOID)
{
    EFI_STATUS Status;
    MP_CONFIGURATION_TABLE_HEADER *HeaderPointer;
    VOID *AllocationPointer;
#if MP_TABLE_LEGACY_REGION_LOCATION != 0
    EFI_LEGACY_BIOS_PROTOCOL *LegacyBiosProtocol;
#endif
    HeaderPointer = (MP_CONFIGURATION_TABLE_HEADER *) MpsTablePointer;

    HeaderPointer->Signature = MP_CONFIGURATION_TABLE_SIGNATURE;
    HeaderPointer->BaseTableLength = BaseTableLength;
    HeaderPointer->VersionNumber = MP_TABLE_VERSION_1_4;
    HeaderPointer->CheckSum = 0;    //force checksum to zero before calculating

    MemCpy((VOID *)HeaderPointer->OemId, (VOID *)OemId, 8);
    MemCpy((VOID *)HeaderPointer->ProductId, (VOID *)ProductId, 12);

    HeaderPointer->OemTablePointer = 0;
    HeaderPointer->OemTableSize = 0;
    HeaderPointer->BaseTableEntryCount = BaseTableEntryCount;
    HeaderPointer->LocalApicAddress = LOCAL_APIC_BASE;                //sdl token
    HeaderPointer->ExtendedTableLength = ExtendedTableLength;
    HeaderPointer->ExtendedCheckSum = 0;
    HeaderPointer->Reserved = 0;

    HeaderPointer->ExtendedCheckSum = ChsumTbl(MpsExTablePointer, ExtendedTableLength);
    HeaderPointer->CheckSum = ChsumTbl(MpsTablePointer, BaseTableLength);

#if MP_TABLE_LEGACY_REGION_LOCATION == 0

//publish table in high memory
    Status = pBS->AllocatePool(EfiRuntimeServicesData,
                               BaseTableLength + ExtendedTableLength,
                               &AllocationPointer);

    if(EFI_ERROR(Status))  
        return Status; 
    MemCpy(AllocationPointer, //memory allocated - copy MPS table to new location
            MpsTablePointer, 
            (UINTN) (BaseTableLength + ExtendedTableLength));
    
#else

//publish table in F0000 segment
    Status = pBS->LocateProtocol(&EfiLegacyBiosProtocolGuid,
                                 NULL,
                                 &LegacyBiosProtocol);
    if(EFI_ERROR(Status))
        return Status;

    Status = LegacyBiosProtocol->GetLegacyRegion(LegacyBiosProtocol,
                                        (UINTN)(BaseTableLength + ExtendedTableLength),
                                        F0000_BIT,
                                        0x10,
                                        &AllocationPointer);
    if(EFI_ERROR(Status))
        return Status;

    Status = LegacyBiosProtocol->CopyLegacyRegion(LegacyBiosProtocol,
                                        (UINTN) (BaseTableLength + ExtendedTableLength),
                                        AllocationPointer,
                                        MpsTablePointer);
#endif

    pBS->FreePool(MpsTablePointer);
    MpsTablePointer = AllocationPointer;

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:    MpsTableAddCpuEntryByHob
// 
// Description:  Adds CPU entries to MPS table from HOB.
//
// Input:
// VOID
//     
// Output:          
// UINT16 - Number of entries added
//
//--------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT16 MpsTableAddCpuEntryByHob(VOID)
{
    MP_TABLE_CPU_ENTRY *EntryPointer;
    UINT16 EntryCount = 0;
	static EFI_GUID CpuInfoHobGuid	= AMI_CPUINFO_HOB_GUID;
	static EFI_GUID HobListGuid	= HOB_LIST_GUID;
	CPUINFO_HOB	*pCpuInfoHob;
	CPUINFO		CpuInfo;
	VOID		*pHobList;
	EFI_STATUS 	Status;
  	INTN           i;
    UINTN       CpuIndex = 0;
    UINT8       NumberOfCores;
    UINT8       NumberOfThreads;


    EntryPointer = (MP_TABLE_CPU_ENTRY *)MpsTableCurrentPointer;

	pHobList = GetEfiConfigurationTable(pST, &HobListGuid);
	if(pHobList == NULL)
		Status = EFI_NOT_FOUND;
	else 
		Status = FindNextHobByGuid(&CpuInfoHobGuid, &pHobList);

	//If no CPU info available, we've got a UniProccessor System
  	if (EFI_ERROR(Status))
	{
		EntryPointer->EntryType = MP_TABLE_CPU_ENTRY_TYPE;
		EntryPointer->LocalApicId = 0;
		EntryPointer->LocalApicVersion = 0;
		EntryPointer->CpuFlags.CpuEnable = 1;
		EntryPointer->CpuFlags.CpuBootStrap = 1;
        EntryPointer->CpuFlags.Reserved = 0;
        EntryPointer->CpuSignature = 0;
        EntryPointer->FeatureFlags = 0;
        EntryPointer->Reserved[0] = 0;
        EntryPointer->Reserved[1] = 0;

		return 1; //just one CPU entry
	}

	pCpuInfoHob = (CPUINFO_HOB *)pHobList;

    while(!EFI_ERROR(GetCpuInfo(CpuIndex, &NumberOfCores, &NumberOfThreads)))
    {
    	for(i = 0; i < NumberOfCores * NumberOfThreads; i += NumberOfThreads)
	    {
		    CpuInfo = pCpuInfoHob->Cpuinfo[i + CpuIndex];

		    EntryPointer->EntryType = MP_TABLE_CPU_ENTRY_TYPE;
		    EntryPointer->LocalApicId = CpuInfo.ApicId;
		    EntryPointer->LocalApicVersion = CpuInfo.ApicVer;
		    EntryPointer->CpuFlags.CpuEnable = (CpuInfo.Disabled) ? 0 : 1;
		    EntryPointer->CpuFlags.CpuBootStrap = ((i + CpuIndex) == pCpuInfoHob->BspNo) ? 1 : 0;
            EntryPointer->CpuFlags.Reserved = 0;
            EntryPointer->CpuSignature = CpuInfo.CpuSignature;
            EntryPointer->FeatureFlags = (UINT32) CpuInfo.CpuFeatureInfo;
            EntryPointer->Reserved[0] = 0;
            EntryPointer->Reserved[1] = 0;

            EntryPointer++;
            EntryCount++;
	    }
        CpuIndex += NumberOfCores * NumberOfThreads;
    }
    return EntryCount;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:    MpsTableAddCpuEntryByProtocol.
// 
// Description:  Adds CPU entries to MPS table from protocol.
//
// Input:
// VOID
//     
// Output:          
// UINT16 - Number of entries added
//
//--------------------------------------------------------------------------
//<AMI_PHDR_END>

#ifdef ACPI_INFO2_PROTOCOL_PUBLISHED
UINT16 MpsTableAddCpuEntryByProtocol(VOID)
{
    MP_TABLE_CPU_ENTRY *EntryPointer;
	EFI_STATUS 	Status;
    ACPI_PROCESSOR_INFO *AcpiProcInfo;
    UINT32  NumEntries;
    UINT32  EntryCount = 0;
    UINT32  Index;

    if (gAmiCpu2Info->ProtocolVer < 1) return 0;

    Status = gAmiCpu2Info->GetAcpiInfo(
	    gAmiCpu2Info, (VOID**) &AcpiProcInfo, &NumEntries
    );
    if (EFI_ERROR(Status)) return 0;

    EntryPointer = (MP_TABLE_CPU_ENTRY *)MpsTableCurrentPointer;

    for (Index = 0; Index < NumEntries; ++Index) {
    //Note: Only some ACPI_PROCESSOR_INFO fields may only valid for some minimum ACPI_PROCESSOR_INFO.Length.
    //The ACPI_PROCESSOR_INFO may have additional fields added in later version. Please see comments in
    //AmiCpuInfo2.h file.
        if (AcpiProcInfo->Type == ACPI_PROCESSOR_INFO_TYPE
            && AcpiProcInfo->Thread == 0
        ) {
		    EntryPointer->EntryType = MP_TABLE_CPU_ENTRY_TYPE;
		    EntryPointer->LocalApicId = AcpiProcInfo->ApicId;
		    EntryPointer->LocalApicVersion = AcpiProcInfo->ApicVer;
		    EntryPointer->CpuFlags.CpuEnable = AcpiProcInfo->Enable;
		    EntryPointer->CpuFlags.CpuBootStrap = AcpiProcInfo->Bsp;
            EntryPointer->CpuFlags.Reserved = 0;
            EntryPointer->CpuSignature = AcpiProcInfo->CpuSignature;
            EntryPointer->FeatureFlags = AcpiProcInfo->FeatureFlags;
            EntryPointer->Reserved[0] = 0;
            EntryPointer->Reserved[1] = 0;
            EntryPointer++;
            EntryCount++;
        }         

        AcpiProcInfo = (ACPI_PROCESSOR_INFO*)((UINT8*)AcpiProcInfo + AcpiProcInfo->Length);
    }

    return (UINT16)EntryCount;
}
#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:    MpsTableAddCpuEntry.
// 
// Description:  Adds CPU entries to MPS table.
//
// Input:
// VOID
//     
// Output:          
// UINT16 - Number of entries added
//
//--------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT16 MpsTableAddCpuEntry(VOID)
{
    UINT16 EntryCount = 0;
    //First try to build Local APIC information from the protocol.
#ifdef ACPI_INFO2_PROTOCOL_PUBLISHED
    if (gAmiCpu2Info != NULL) EntryCount = MpsTableAddCpuEntryByProtocol();
    //If protocol fails, try CPU INFO HOB.
#endif
    if (!EntryCount) EntryCount = MpsTableAddCpuEntryByHob();
    return EntryCount;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:    MpsTableAddBusEntry
// 
// Description:  Adds Bus entries to MPS table
//
// Input:
// VOID
//     
// Output:          
// UINT16 - Number of entries added
// 
//--------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16 MpsTableAddBusEntry(VOID)
{
    MP_TABLE_BUS_ENTRY *EntryPointer;
    UINT16 EntryCount = 0;
    UINT16 i;

    EntryPointer = (MP_TABLE_BUS_ENTRY *)MpsTableCurrentPointer;

    QueryBusInfo();

    for(i = 0; i < CurrentBusEntry; i++)
    {
        EntryPointer->EntryType = MP_TABLE_BUS_ENTRY_TYPE;
        EntryPointer->BusId = BusEntry[i].BusId;

        MemCpy((VOID *)EntryPointer->BusTypeString, (VOID *)BusTypeString[(BusEntry[i].BusType)], 6);

        EntryPointer++;
        EntryCount++;
    }
    return EntryCount;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:    MpsTableAddIoApicEntry
// 
// Description:  Adds IO Apic entries to MPS table
//
// Input:
// VOID
//     
// Output:          
// UINT16 - Number of entries added
// 
//--------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16 MpsTableAddIoApicEntry(VOID)
{
    MP_TABLE_IO_APIC_ENTRY *EntryPointer;
    UINT16 EntryCount = 0;
    UINT8 i=0;
#if FEC00000_APIC_AUTODETECT == 1  
	UINT64 SearchAddress=0;
#endif
    EntryPointer = (MP_TABLE_IO_APIC_ENTRY *)MpsTableCurrentPointer;

#if FEC00000_APIC_AUTODETECT == 1  
//first we detect IO APICS mapped into default address range
	for(SearchAddress = IO_APIC_BASE_ADDRESS_BOTTOM;
	    SearchAddress < IO_APIC_BASE_ADDRESS_TOP;
	    SearchAddress += IO_APIC_SEARCH_STEP)

		if(*((UINT8 *)SearchAddress) != 0xFF)             //we have something
            CollectIoApicInfo(NULL, (UINT32)SearchAddress);

//second we arrange IO APIC in their ID ascending order (if there more than one)
#endif


//Check also SDL ceated Structures they might address very none standard IOAPICS.
//-------------------------------------------------------------------------------------------

#if USE_BOARD_INFO_APIC_DATA == 1
{
    AMI_APIC_INFO   *BrdApicInfo;
    BOOLEAN         Present;  
    UINTN           j; 
    //-----------------        
    for(i=0; i<(gAmiBoardInfoProtocol->ApicInfoLength/sizeof(AMI_APIC_INFO)); i++){
        BrdApicInfo=&gAmiBoardInfoProtocol->ApicInfoTable[i];
        //This is a special case it could be a duplicate entries in MadtTblEntries[]
        //if other options of IOAPIC/IOsAPIC detection was on. 
        //So check if IOAPIC/IOsAPIC entries with the same properties already present in DB.
        for(j=0,Present=FALSE; j < CurrentIoApicEntry; j++){
            if(BrdApicInfo->ApicAddress.ADDRESS == IoApicEntry[j].IoApicAddress){
                Present = TRUE;
                break;
            } 
        }
        //Entry with this address already present in IoApicEntry[] array
        if(Present) continue;
        
        //Looks like it is a new IOAPIC/IOSAPIC entry!
        //Check if something alive at this address
        CollectIoApicInfo(NULL, BrdApicInfo->ApicAddress.ADDRESS);
    } // for(...i<(gAmiBoardInfoProtocol->ApicInfoLength/sizeof(AMI_APIC_INFO))
}
#endif //USE_BOARD_INFO_APIC_DATA ==1

//-------------------------------------------------------------------------------------------

    if(CurrentIoApicEntry > 1)
        ArrangeIoApicEntries();


//now we are ready to create MPS table IO APIC entries
    for(i = 0; i < CurrentIoApicEntry; i++)
    {
        EntryPointer->EntryType = MP_TABLE_IO_APIC_ENTRY_TYPE;
		EntryPointer->IoApicId = IoApicEntry[i].IoApicId;
		EntryPointer->IoApicVersion = IoApicEntry[i].IoApicVersion;
        EntryPointer->Flags = IoApicEntry[i].IoApicFlags;
        EntryPointer->IoApicAddress = IoApicEntry[i].IoApicAddress;

        EntryPointer++;
        EntryCount++;
    }
    return EntryCount;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:    MpsTableAddIntAssignEntry
// 
// Description:  Adds Interrupt assignment entries to MPS table
//
// Input:
// VOID
//     
// Output:          
// UINT16 - Number of entries added
// 
//--------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16 MpsTableAddIntAssignEntry(VOID)
{

    MP_TABLE_INT_ASSIGN_ENTRY *EntryPointer;
    UINT16 EntryCount = 0;
    UINT16 Dummy;
    PCI_IRQ_APIC_ROUTE *RouteTable;
    UINT8   i, j;

    EntryPointer = (MP_TABLE_INT_ASSIGN_ENTRY *)MpsTableCurrentPointer;

//First assign ISA IRQ interrupts
    AmiIsaIrqMask(&Dummy, TRUE);

    for(i = 0; i < 16; i++)
    {
        if((Dummy & 1) && (i != 2))    //create entry only if IRQ is used
        {                                   //and it isn't IRQ2
            EntryPointer->EntryType = MP_TABLE_INT_ASSIGN_ENTRY_TYPE;
            EntryPointer->InterruptType = INT_TYPE_INT;
            EntryPointer->Flags = (UINT16)IsoTbl[i].Flags;
            EntryPointer->SourceBusId = IsaBusId;
            EntryPointer->SourceBusIrq.IsaBusIrq = i;
//define Apic ID and Itin depends of GLobal sys vector
            GetIoApicId(IsoTbl[i].ApicInt, 
                        &EntryPointer->DestIoApicId,
                        &EntryPointer->DestIoApicItin);

            EntryPointer++;
            EntryCount++;
        }
        Dummy >>= 1;
    }

//Second assign PCI IRQ Entries
    
    Dummy = (UINT16)gAmiBoardInfoProtocol->ApicRoutLength/sizeof(PCI_IRQ_APIC_ROUTE);        
    RouteTable = gAmiBoardInfoProtocol->ApicRoutTable;
    
    for(i = 0; i < Dummy; i++)
    {
//define runtime bus number from build bus number                

        for(j = 0; j < 4; j++)
        {
            if((RouteTable[i].Intn[j].IoApicItin != 0) || (RouteTable[i].Intn[j].IoApicId != 0))
            {
                EntryPointer->EntryType = MP_TABLE_INT_ASSIGN_ENTRY_TYPE;
                EntryPointer->InterruptType = INT_TYPE_INT;
                EntryPointer->Flags = 0;    //always conforms PCI bus specs
                EntryPointer->SourceBusId = RouteTable[i].PciBusNumber;
                EntryPointer->SourceBusIrq.PciBusIrq.PciIntSignal = j;
                EntryPointer->SourceBusIrq.PciBusIrq.PciDeviceNumber = RouteTable[i].DeviceNumber;
                EntryPointer->SourceBusIrq.PciBusIrq.Reserved = 0;
                EntryPointer->DestIoApicId = RouteTable[i].Intn[j].IoApicId;  
                EntryPointer->DestIoApicItin = RouteTable[i].Intn[j].IoApicItin;

                EntryPointer++;
                EntryCount++;
            }
        }
    }    

    return EntryCount;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:    MpsTableAddLocalIntAssignEntry
// 
// Description:  Adds Local interrupt assignment entries to MPS table
//
// Input:
// VOID
//     
// Output:          
// UINT16 - Number of entries added
// 
//--------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16 MpsTableAddLocalIntAssignEntry(VOID)
{
    MP_TABLE_LOCAL_INT_ASSIGN_ENTRY *EntryPointer;
    UINT16 EntryCount = 0;

    EntryPointer = (MP_TABLE_LOCAL_INT_ASSIGN_ENTRY *)MpsTableCurrentPointer;

    EntryPointer->EntryType = MP_TABLE_LOCAL_INT_ASSIGN_ENTRY_TYPE;
    EntryPointer->InterruptType = INT_TYPE_EXT_INT;
    EntryPointer->InterruptSignal.Polarity = POLARITY_CONFORM_SPEC;
    EntryPointer->InterruptSignal.TriggerMode = TRIGGER_MODE_CONFORM_SPEC;
    EntryPointer->InterruptSignal.Reserved = 0;
    EntryPointer->SourceBusId = 0;
    EntryPointer->SourceBusIrq = 0;
    EntryPointer->DestLocalApicId = 0xFF;
    EntryPointer->DestLocalApicItin = 0;

    EntryPointer++;
    EntryCount++;

    EntryPointer->EntryType = MP_TABLE_LOCAL_INT_ASSIGN_ENTRY_TYPE;
    EntryPointer->InterruptType = INT_TYPE_NMI;
    EntryPointer->InterruptSignal.Polarity = POLARITY_CONFORM_SPEC;
    EntryPointer->InterruptSignal.TriggerMode = TRIGGER_MODE_CONFORM_SPEC;
    EntryPointer->InterruptSignal.Reserved = 0;
    EntryPointer->SourceBusId = 0;
    EntryPointer->SourceBusIrq = 0;
    EntryPointer->DestLocalApicId = 0xFF;
    EntryPointer->DestLocalApicItin = 1;

    EntryPointer++;
    EntryCount++;

    return EntryCount;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:    MpsTableAddExtendedTable
// 
// Description:  Adds Extended table entries to base table
//
// Input:
// VOID
//     
// Output:          
// VOID
// 
//--------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID MpsTableAddExtendedTable(VOID)
{
    MemCpy(MpsTableCurrentPointer, MpsExTablePointer, ExtendedTableLength);
    MpsExTablePointer = MpsTableCurrentPointer;
    return;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:    MpsExTableAddSysAddressMapEntry
// 
// Description:  Creates Extended MPS table system address space map entryies
//
// Input:
// IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *pPciRootBridgeIoProtocol
// IN UINT8 BusId - PCI bus number
// IN UINT8 BusAttributes - PCI bus attributes
//     
// Output:          
// VOID
//
// Modified:    MpsExTableCurrentPointer
//              ExtendedTableLength
// 
//--------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID MpsExTableAddSysAddressMapEntry(
    IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *pPciRootBridgeIoProtocol,
    IN UINT8 BusId,
    IN UINT8 BusAttributes)
{
    MP_EX_TABLE_SYS_ADDRESS_MAP_ENTRY *EntryPointer;
	ACPI_ADDRESS_SPACE_DESC *Resources;
    BOOLEAN  VgaMemoryAdded = FALSE;

    EntryPointer = (MP_EX_TABLE_SYS_ADDRESS_MAP_ENTRY *)MpsExTableCurrentPointer;

    pPciRootBridgeIoProtocol->Configuration(pPciRootBridgeIoProtocol, &Resources);

//add entries to ISA decode
    if(BusAttributes & 0x3)                     //support ISA I/O space
    {
        EntryPointer->EntryType = MP_EX_TABLE_SYS_ADDRESS_MAP_ENTRY_TYPE;
        EntryPointer->EntryLength = sizeof(MP_EX_TABLE_SYS_ADDRESS_MAP_ENTRY);
        EntryPointer->BusId = BusId;
        EntryPointer->AddressType = 0;    //IO descriptor
        EntryPointer->AddressBase = 0;
        EntryPointer->AddressLength = 0x1000;
        EntryPointer++;
        ExtendedTableLength += sizeof(MP_EX_TABLE_SYS_ADDRESS_MAP_ENTRY);
    }

    while(Resources->Signature == 0x8A)
    {
        if(Resources->ResourceType != 2  && Resources->AddressLength)
        {
            if(Resources->ResourceType == 1)    //IO descriptor
                EntryPointer->AddressType = 0;
            else if(Resources->TypeSpecificFlags & 6)   //bits 1 and 2 set
                EntryPointer->AddressType = 2;          //memory prefetch address
            else
                EntryPointer->AddressType = 1;          //memory descriptor

//          VGA region should be at the beginning of Memory range
            if ((EntryPointer->AddressType == 1) && (BusAttributes & 0x1C) && (!(VgaMemoryAdded))) {
                EntryPointer->EntryType = MP_EX_TABLE_SYS_ADDRESS_MAP_ENTRY_TYPE;
                EntryPointer->EntryLength = sizeof(MP_EX_TABLE_SYS_ADDRESS_MAP_ENTRY);
                EntryPointer->BusId = BusId;
                EntryPointer->AddressType = 1;    //memory descriptor
                EntryPointer->AddressBase = 0xA0000;
                EntryPointer->AddressLength = 0x20000;
                EntryPointer++;
                ExtendedTableLength += sizeof(MP_EX_TABLE_SYS_ADDRESS_MAP_ENTRY);
                VgaMemoryAdded = TRUE;
                EntryPointer->AddressType = 1;          //memory descriptor
            }

            EntryPointer->EntryType = MP_EX_TABLE_SYS_ADDRESS_MAP_ENTRY_TYPE;
            EntryPointer->EntryLength = sizeof(MP_EX_TABLE_SYS_ADDRESS_MAP_ENTRY);
            EntryPointer->BusId = BusId;
            EntryPointer->AddressBase = Resources->AddressRangeMin;
            EntryPointer->AddressLength = Resources->AddressLength;

            EntryPointer++;
            ExtendedTableLength += sizeof(MP_EX_TABLE_SYS_ADDRESS_MAP_ENTRY);
        }
        Resources++;
    }

    MpsExTableCurrentPointer = (VOID *)EntryPointer;

    return;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:    MpsExTableAddBusHierarchyEntry
// 
// Description:  Creates Extended MPS table bus hierarchy entryies
//
// Input:
// VOID
//     
// Output:          
// VOID
//
// Modified:    MpsExTableCurrentPointer
//              ExtendedTableLength
// 
//--------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID MpsExTableAddBusHierarchyEntry(VOID)
{
    MP_EX_TABLE_BUS_HIERARCHY_ENTRY *EntryPointer;
    UINT8 i;

    EntryPointer = (MP_EX_TABLE_BUS_HIERARCHY_ENTRY *)MpsExTableCurrentPointer;

    for(i = 0; i < CurrentBusEntry; i++)
    {
        if(BusEntry[i].ParentBusId != 0xFF && BusEntry[i].BusType != 12)    //skip root bridge and P2P bridge
        {
            EntryPointer->EntryType = MP_EX_TABLE_BUS_HIERARCHY_ENTRY_TYPE;
            EntryPointer->EntryLength = sizeof(MP_EX_TABLE_BUS_HIERARCHY_ENTRY);
            EntryPointer->BusId = BusEntry[i].BusId;
            EntryPointer->BusInfo = BusEntry[i].Flags;
            EntryPointer->ParentBusId = BusEntry[i].ParentBusId;
            EntryPointer->Reserved[0] = 0;
            EntryPointer->Reserved[1] = 0;
            EntryPointer->Reserved[2] = 0;

            EntryPointer++;
            ExtendedTableLength += sizeof(MP_EX_TABLE_BUS_HIERARCHY_ENTRY);
        }
    }
    MpsExTableCurrentPointer = (VOID *)EntryPointer;        
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:    MpsExTableAddCompatBusAddressModifierEntry
// 
// Description:  Creates Extended MPS table compatibility bus address space
//               modifier entryies
//
// Input:
// VOID
//     
// Output:          
// VOID
//
// Modified:    MpsExTableCurrentPointer
//              ExtendedTableLength
// 
//--------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID MpsExTableAddCompatBusAddressModifierEntry(VOID)
{
    MP_EX_TABLE_COMPAT_BUS_ADDRESS_MODIFIER_ENTRY *EntryPointer;
    UINT8 i;

    EntryPointer = (MP_EX_TABLE_COMPAT_BUS_ADDRESS_MODIFIER_ENTRY *)MpsExTableCurrentPointer;

    for(i = 0; i < CurrentBusEntry; i++)
    {
        if(BusEntry[i].ParentBusId == 0xFF)
        {
        //add/subtract ISA predefined range
            EntryPointer->EntryType = MP_EX_TABLE_COMPAT_BUS_ADDRESS_MODIFIER_ENTRY_TYPE;
            EntryPointer->EntryLength = sizeof(MP_EX_TABLE_COMPAT_BUS_ADDRESS_MODIFIER_ENTRY);
            EntryPointer->BusId = BusEntry[i].BusId;
            EntryPointer->RangeList = 0;    //isa range list
            EntryPointer->AddressModifier = (BusEntry[i].Flags & 0x3) ? 0 : 1;

            EntryPointer++;
            ExtendedTableLength += sizeof(MP_EX_TABLE_COMPAT_BUS_ADDRESS_MODIFIER_ENTRY);

        //add/subtract VGA predefined range
            EntryPointer->EntryType = MP_EX_TABLE_COMPAT_BUS_ADDRESS_MODIFIER_ENTRY_TYPE;
            EntryPointer->EntryLength = sizeof(MP_EX_TABLE_COMPAT_BUS_ADDRESS_MODIFIER_ENTRY);
            EntryPointer->BusId = BusEntry[i].BusId;
            EntryPointer->RangeList = 1;    //vga range list
            EntryPointer->AddressModifier = (BusEntry[i].Flags & 0x1C) ? 0 : 1;

            EntryPointer++;
            ExtendedTableLength += sizeof(MP_EX_TABLE_COMPAT_BUS_ADDRESS_MODIFIER_ENTRY);
        }
    }
    MpsExTableCurrentPointer = (VOID *)EntryPointer;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:    QueryBusInfo
// 
// Description:  Retreive system info about buses and bus ierarchy and fills
//               BUS_INFO structure. Also creates MPS table extended entries
//
// Input:
// VOID
//     
// Output:          
// VOID
//
// Modified:    BusEntry
//              MaxBusId
//              CurrentBusEntry
//              IsaBusId
// 
//--------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID QueryBusInfo(VOID)
{
	EFI_STATUS Status;
	EFI_HANDLE *pHandleBuffer;
	UINTN	NumberOfHandles;
    UINTN  i;

	EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *pPciRootBridgeIoProtocol;
	static EFI_GUID PciRootBridgeIoProtocolGuid = EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_GUID;
	ACPI_ADDRESS_SPACE_DESC *pAddressDescriptor;

	EFI_PCI_IO_PROTOCOL *pPciIoProtocol;
	static EFI_GUID PciIoProtocolGuid = EFI_PCI_IO_PROTOCOL_GUID;
    UINT8   PciData[4];
    UINTN   BusNumber;
    UINTN   dummy[3];
    UINT64  SupportedAttributes;

//First detect and retreive bus Id for PCI host (root) buses
	Status = pBS->LocateHandleBuffer(ByProtocol, &PciRootBridgeIoProtocolGuid,
					 NULL, &NumberOfHandles, &pHandleBuffer);
	if(EFI_ERROR(Status))
		return;

	for(i = 0; i < NumberOfHandles; i++)
    {
	    Status = pBS->HandleProtocol(pHandleBuffer[i], &PciRootBridgeIoProtocolGuid,
					                (VOID**)&pPciRootBridgeIoProtocol);
		ASSERT_EFI_ERROR(Status);
	    Status = pPciRootBridgeIoProtocol->Configuration(pPciRootBridgeIoProtocol,
							        &pAddressDescriptor);
		ASSERT_EFI_ERROR(Status);
        Status = pPciRootBridgeIoProtocol->GetAttributes(pPciRootBridgeIoProtocol,
                                    &SupportedAttributes,
                                    NULL);
		ASSERT_EFI_ERROR(Status);
//find bus range decoding - the min will be host PCI bus Id
        while((pAddressDescriptor->Signature == 0x8A) && \
              (pAddressDescriptor->ResourceType != 2))
                pAddressDescriptor++;

        BusEntry[CurrentBusEntry].BusId = (UINT8)pAddressDescriptor->AddressRangeMin;
        BusEntry[CurrentBusEntry].ParentBusId = 0xFF; //host bus has no parent
        BusEntry[CurrentBusEntry].BusType = BridgeBusTypes[0];
        BusEntry[CurrentBusEntry].Flags = (UINT8)SupportedAttributes;    //for host we save ISA/VGA support values

        MaxBusId = (MaxBusId > BusEntry[CurrentBusEntry].BusId) ? \
                    MaxBusId : BusEntry[CurrentBusEntry].BusId;

        MpsExTableAddSysAddressMapEntry(pPciRootBridgeIoProtocol, 
                                        BusEntry[CurrentBusEntry].BusId,
                                        BusEntry[CurrentBusEntry].Flags);
        CurrentBusEntry++;
    }
    pBS->FreePool(pHandleBuffer);

//Second detect all other buses via PCI bridges
	Status = pBS->LocateHandleBuffer(ByProtocol, &PciIoProtocolGuid,
					 NULL, &NumberOfHandles, &pHandleBuffer);
	if(EFI_ERROR(Status))
		return;

	for(i = 0; i < NumberOfHandles; i++)
    {
	    Status = pBS->HandleProtocol(pHandleBuffer[i], &PciIoProtocolGuid,
					                (VOID**)&pPciIoProtocol);
		if(EFI_ERROR(Status))
			continue;

    //read class code information at 0x8 offset in PCI header
		Status = pPciIoProtocol->Pci.Read(pPciIoProtocol, EfiPciIoWidthUint32,
					 	                  0x8, 1, (VOID*)PciData);
		if(EFI_ERROR(Status)) //problem
			continue;
#if PCI_BUS_APIC_AUTODETECT == 1
//if IO APIC device collect info, we will need it later
        if((PciData[3] == 0x8) && (PciData[2] == 0) && (PciData[1] >= 0x10))
        {
            UINT64  Attr=0, OldAttr=0;
        //----------------------
            //1. make sure it is Enabled and Decoding it's resources
            Status=pPciIoProtocol->Attributes(pPciIoProtocol,EfiPciIoAttributeOperationGet, Attr, &OldAttr);
            ASSERT_EFI_ERROR(Status);
            if(EFI_ERROR(Status)) continue;
                                
            Status=pPciIoProtocol->Attributes(pPciIoProtocol,EfiPciIoAttributeOperationSupported, 0, &Attr);
            ASSERT_EFI_ERROR(Status);
            if(EFI_ERROR(Status)) continue;

            Status=pPciIoProtocol->Attributes(pPciIoProtocol,EfiPciIoAttributeOperationSet, Attr&(EFI_PCI_DEVICE_ENABLE), NULL);
            ASSERT_EFI_ERROR(Status);
  		    if(EFI_ERROR(Status)) continue;

            CollectIoApicInfo(pPciIoProtocol, NULL);

#if PCI_BUS_APIC_LEAVE_ENABLE != 0
            //Restore attributes of the device
            Status=pPciIoProtocol->Attributes(pPciIoProtocol,EfiPciIoAttributeOperationSet, OldAttr, NULL);
            ASSERT_EFI_ERROR(Status);
            if(EFI_ERROR(Status)) continue;
#endif//PCI_BUS_APIC_LEAVE_ENABLE

            continue;
        }
#endif//PCI_BUS_APIC_AUTODETECT

        if(PciData[3] != 0x6)   //not bridge device
            continue;

        if((PciData[2] == 0) || (PciData[2] > 6))     //PCI host bridge we already know, so skip it
            continue;                                 //or unknown bridge - skip it also

        BusEntry[CurrentBusEntry].BusType = BridgeBusTypes[(PciData[2])];

        if(PciData[2] == 4)     // PCI to PCI bridge
        {
            BusEntry[CurrentBusEntry].Flags = PciData[1];
        //read primary and secondary bus numbers
		    Status = pPciIoProtocol->Pci.Read(pPciIoProtocol, EfiPciIoWidthUint32,
					 	                      0x18, 1, (VOID*)PciData);

            BusEntry[CurrentBusEntry].BusId = PciData[1]; //bus Id prodused by this bridge
            BusEntry[CurrentBusEntry].ParentBusId = PciData[0];
            MaxBusId = (MaxBusId > BusEntry[CurrentBusEntry].BusId) ? \
                        MaxBusId : BusEntry[CurrentBusEntry].BusId;
        }
        else        //any other bridge
        {
            BusEntry[CurrentBusEntry].Flags = 1;  //all other buses has this feature
            BusEntry[CurrentBusEntry].BusId = 0xFF;     //we will assign Id after enumerating PCI buses
        //get bridge location to determine parent bus Id        
		    Status = pPciIoProtocol->GetLocation(pPciIoProtocol, &dummy[0], &BusNumber,
                                                 &dummy[1], &dummy[2]);

            BusEntry[CurrentBusEntry].ParentBusId = (UINT8)BusNumber;
        }
        CurrentBusEntry++;
    }
    pBS->FreePool(pHandleBuffer);

// Third enumerate all other buses
    for(i = 0; i < CurrentBusEntry; i++)
    {
        if(BusEntry[i].BusId == 0xFF)
        {
            BusEntry[i].BusId = MaxBusId + 1;
            MaxBusId++;
            if(BusEntry[i].BusType == BUS_TYPE_ISA) //save ISA bus Id for interrupt assign procedure
                IsaBusId = MaxBusId;
        }
    }
    MpsExTableAddBusHierarchyEntry();
    MpsExTableAddCompatBusAddressModifierEntry();
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:    CollectIoApicInfo
// 
// Description:  Retreive system info about IO APIC 
//
// Input:
// IN OPTIONAL EFI_PCI_IO_PROTOCOL *pPciIoProtocol 
// IN OPTIONAL UINT32 BaseAddress - base address of IO APIC
//     
// Output:          
// VOID
//
// Modified:    IoApicEntry
//              CurrentIoApicEntry
// 
//--------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID CollectIoApicInfo(
    IN EFI_PCI_IO_PROTOCOL *pPciIoProtocol OPTIONAL,
    IN UINT32 BaseAddress OPTIONAL)
{
    UINT32 IoApicAddress;
    EFI_STATUS Status;
	UINT32 volatile *IoApicMemory32;
	UINT8  volatile *IoApicMemory8;
	UINT32 data;

    if(BaseAddress == NULL)     //IO APIC visible as PCI device
    {
	    Status = pPciIoProtocol->Pci.Read(pPciIoProtocol, EfiPciIoWidthUint32,
			    		 	              0x10, 1, (VOID*)&IoApicAddress);
	    if(EFI_ERROR(Status) || (IoApicAddress == 0)) //problem or mapped to default address range
		    return;
    }
    else                        // IO APIC mapped to default range
        IoApicAddress = BaseAddress;
    
	IoApicMemory32 = (UINT32 *)IoApicAddress;
	IoApicMemory8 = (UINT8 *)IoApicAddress;

	IoApicMemory8[IO_APIC_INDEX_REG] = IO_APIC_MAP_ID_REG;
	data = IoApicMemory32[IO_APIC_DATA_REG];

    IoApicEntry[CurrentIoApicEntry].IoApicId = (UINT8)((data & 0x0F000000) >> 24);

	IoApicMemory8[IO_APIC_INDEX_REG] = IO_APIC_MAP_VERSION_REG;
	data = IoApicMemory32[IO_APIC_DATA_REG];

    IoApicEntry[CurrentIoApicEntry].IoApicVersion = (UINT8)(data & 0xFF);
    IoApicEntry[CurrentIoApicEntry].MaxRedirectionEntries = (UINT8)((data & 0x00FF0000) >> 16);
    IoApicEntry[CurrentIoApicEntry].IoApicFlags = 1;
    IoApicEntry[CurrentIoApicEntry].IoApicAddress = IoApicAddress;

    CurrentIoApicEntry++;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:    ArrangeIoApicEntries
// 
// Description:  Arranges IO APIC Entries in their ID ascending order
//
// Input:
// VOID
//     
// Output:          
// VOID
//
// Modified:    IoApicEntry
//              CurrentIoApicEntry
// 
//--------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID ArrangeIoApicEntries(VOID)
{
    UINT8 i;
    BOOLEAN Swap = TRUE;
    IO_APIC_INFO Temp;

    while(Swap)
    {
        Swap = FALSE;
        for(i = 0; i < CurrentIoApicEntry - 1; i++)
        {
            if(IoApicEntry[i].IoApicId > IoApicEntry[i+1].IoApicId)
            {
                Swap = TRUE;
                MemCpy(&Temp, &IoApicEntry[i], sizeof(IO_APIC_INFO));
                MemCpy(&IoApicEntry[i], &IoApicEntry[i+1], sizeof(IO_APIC_INFO));
                MemCpy(&IoApicEntry[i+1], &Temp, sizeof(IO_APIC_INFO));
            }
        }
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:    GetIoApicId
// 
// Description:  Returns IO APIC ID and Pin number assosiated with given SysVectorNumber
//
// Input:
// IN UINT16   SysVectorNumber - system interrupt vector number
// OUT UINT8 *IoApicId - Id of IO APIC which handles that vector
// OUT UINT8 *IoApicItin - IO APIC Pin number associated with given vector number
//     
// Output:          
// VOID
//
// Modified:    IoApicEntry
//              CurrentIoApicEntry
// 
//--------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID GetIoApicId(
    IN UINT16   SysVectorNumber,
    OUT UINT8 *IoApicId,
    OUT UINT8 *IoApicItin)
{
    UINT8 i;

    for(i = 0; i < CurrentIoApicEntry; i++)
    {
        if(SysVectorNumber < IoApicEntry[i].MaxRedirectionEntries) //this is Apic we need
        {
            *IoApicId = IoApicEntry[i].IoApicId;
            *IoApicItin = (UINT8)SysVectorNumber;
            return;
        }
        SysVectorNumber -= IoApicEntry[i].MaxRedirectionEntries;
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:    GetCpuInfo
// 
// Description:  Returns number of cores and threads of given CPU
//
// Input:
// IN UINTN Cpu - Cpu number
// OUT UINT8 *Cores - number of cores in given Cpu
// OUT UINT8 *Threads - number of threads in given Cpu
//   
// Output:
// EFI_SUCCESS - function executed successfully
//
//--------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS GetCpuInfo(
    IN UINTN Cpu,
    OUT UINT8 *Cores,
    OUT UINT8 *Threads)
{
    EFI_STATUS Status;
    AMI_CPU_INFO *Info;

//find AMICpuInfo protocol
    if(AmiCpuInfoProtocol == NULL)
    {
        Status = pBS->LocateProtocol(&AmiCpuInfoProtocolGuid,
                                    NULL,
                                    &AmiCpuInfoProtocol);
        if(EFI_ERROR(Status))
            return Status;
    }

    Status = AmiCpuInfoProtocol->GetCpuInfo(AmiCpuInfoProtocol, Cpu, &Info);
    if(EFI_ERROR(Status))
        return Status;

    *Cores = Info->NumCores;
    *Threads = (Info->NumHts == 0) ? 1 : Info->NumHts;
    
    return EFI_SUCCESS;
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             5555 Oakbrook Pkwy, Norcross, GA 30093               **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************