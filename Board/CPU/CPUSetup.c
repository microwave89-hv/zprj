//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1987-2013, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/Haswell/AMI Cpu PKG/CPU Board/CPUSetup.c 6     4/10/15 2:37a Crystallee $
//
// $Revision: 6 $
//
// $Date: 4/10/15 2:37a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/Haswell/AMI Cpu PKG/CPU Board/CPUSetup.c $
// 
// 6     4/10/15 2:37a Crystallee
// 
// 5     5/09/13 10:54p Crystallee
// [TAG]  		EIP123326
// [Category]  	Improvement
// [Description]  	Show "Processor family" and "FSB speed" on CPU
// Configuration in BIOS setup menu.
// 
// 4     11/07/12 4:37a Davidhsieh
// [TAG]                None
// [Category]         Improvement
// [Description]      L4 Cache support improve
// 
// 3     10/17/12 1:57a Davidhsieh
// [TAG]                     None
// [Category]  	Improvement
// [Description]  	L4 cache support
// 
// 2     3/16/12 3:35a Davidhsieh
// Setup items create for CPU RC policy
// 
// 1     2/07/12 3:57a Davidhsieh
// 
//
//**********************************************************************

//<AMI_FHDR_START>
//---------------------------------------------------------------------------
//
// Name:	CPUSetup.c
//
// Description:	CPU Setup Rountines
//
//---------------------------------------------------------------------------
//<AMI_FHDR_END>

#include <Setup.h>
#include "AmiCspLibInc.h"
#include <SetupStrTokens.h>
#include <AmiDxeLib.h>
#include <Protocol\AmiCpuInfo.h>
#include <Protocol\AmiCpuInfo2.h>
#include <AmiHobs.h>
#include "token.h"

#define SANDY_BRIDGE    0x206a0
#define JAKETOWN        0x206d0
#define PlatformInfoMsr   0xce

typedef struct {
    STRING_REF Ver;
    STRING_REF Id;
	STRING_REF Family;
    STRING_REF Microcode;
    STRING_REF MaxSpeed;
    STRING_REF MinSpeed;
    STRING_REF L1DataSize;
    STRING_REF L1CodeSize;
    STRING_REF L2Size;
    STRING_REF L3Size;
    STRING_REF NumCores;
    STRING_REF HyperThreading;
    STRING_REF Vtx;
    STRING_REF Smx;
    STRING_REF Eist;
    STRING_REF CpuC3;
    STRING_REF CpuC6;
    STRING_REF CpuC7;
} SKT_STR_TOK;

static SKT_STR_TOK gSktStrTok[] = {
{   STRING_TOKEN(STR_CPU_SKT0_VERSION_VALUE),
    STRING_TOKEN(STR_CPU_SKT0_CPUID_VALUE),
	STRING_TOKEN(STR_PROCESSOR_FAMILY_VALUE),
    STRING_TOKEN(STR_CPU_SKT0_MICROCODE_VALUE),
    STRING_TOKEN(STR_CPU_SKT0_MAXSPEED_VALUE),
    STRING_TOKEN(STR_CPU_SKT0_MINSPEED_VALUE),
    STRING_TOKEN(STR_CPU_SKT0_L1_DATA_CACHE_VALUE),
    STRING_TOKEN(STR_CPU_SKT0_L1_CODE_CACHE_VALUE),
    STRING_TOKEN(STR_CPU_SKT0_L2_CACHE_VALUE),
    STRING_TOKEN(STR_CPU_SKT0_L3_CACHE_VALUE),
    STRING_TOKEN(STR_CPU_SKT0_NUMCORE_VALUE),
    STRING_TOKEN(STR_CPU_SKT0_HT_VALUE),
    STRING_TOKEN(STR_CPU_SKT0_VTX_VALUE),
    STRING_TOKEN(STR_CPU_SKT0_SMX_VALUE),
    STRING_TOKEN(STR_CPU_SKT0_EIST_VALUE),
    STRING_TOKEN(STR_CPU_SKT0_C3_VALUE),
    STRING_TOKEN(STR_CPU_SKT0_C6_VALUE),
    STRING_TOKEN(STR_CPU_SKT0_C7_VALUE)
}};

static UINT32 gL1DataCacheSize;
static UINT32 gL1CodeCacheSize;
static UINT32 gL2CacheSize;
static UINT32 gL3CacheSize;
static UINT32 gL4CacheSize;

static BOOLEAN gL1Shared;
static BOOLEAN gL2Shared;
static BOOLEAN gL3Shared;
static BOOLEAN gL4Shared;

static EFI_GUID gAmiSetupGuid = SETUP_GUID;
static EFI_GUID gAmiCpuInfoProtocolGuid    = AMI_CPU_INFO_PROTOCOL_GUID;
static EFI_GUID gAmiCpuInfo2ProtocolGuid   = AMI_CPU_INFO_2_PROTOCOL_GUID;
static EFI_GUID gHobListGuid               = HOB_LIST_GUID;
//static EFI_GUID gAmiInternalFactoryTdcTdpHobGuid = AMI_INTERNAL_FACTORY_TDC_TDP_HOB_GUID;
//static EFI_GUID gSetupNvramUpdateGuid      = { \
//    0xd84beff0, 0x159a, 0x4b60, 0x9a, 0xb9, 0xac, 0x5c, 0x47, 0x4b, 0xd3, 0xb1
//};
static EFI_GUID gCpuInfoHobGuid = AMI_CPUINFO_HOB_GUID;
static EFI_HII_HANDLE  gHiiHandle;
static CPUINFO_HOB *gCpuInfoHob;
//static AMI_INTERNAL_FACTORY_TDC_TDP_HOB *gTdcTdpHob; //May not be present.

static AMI_CPU_INFO_PROTOCOL   *gCpuInfoProt;
static AMI_CPU_INFO_2_PROTOCOL *gCpuInfo2Prot;

static VOID InitCpuInfo();

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   GetBoardSocketNumber
//
// Description: Get socket number from Apic ID.
//
// Input:
//  IN UINT32 ApicId
//
// Output:  UINT32 - Physical Socket Id
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

static UINT32 GetBoardSocketNumber(IN UINT32 ApicId)
{
    UINT32 RegEax, RegEbx, RegEcx, RegEdx;
    UINT8  MaxThreadsPackage;

    CPULib_CpuID(1, &RegEax, &RegEbx, &RegEcx, &RegEdx);

    MaxThreadsPackage = (UINT8)(RegEbx >> 16);
    
    return ApicId / MaxThreadsPackage;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   GetMaxSpeedFromBrandString
//
// Description: Get the max speed from the brand string.
//
// Input:
//  IN CHAR8    *CpuBrandString - Pointer to CPU brand string. 
//  OUT CHAR8   *CpuMaxSpeedString -Pointer to string with format "9999 MHz"; 9999 can be any 4 digit number.
//
// Output:  BOOLEAN - TRUE if frequency found.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN GetMaxSpeedFromBrandString(IN CHAR8 *CpuBrandString, OUT CHAR8 *CpuMaxSpeedString)
{
    UINT32  i;
    UINT8   CharCount;
    BOOLEAN TransToMHz = FALSE;
    BOOLEAN FreqStringFound;

    while (*CpuBrandString != 0) {
        if (*CpuBrandString == 'G' && *(CpuBrandString + 1) == 'H' && *(CpuBrandString + 2) == 'z') {
            FreqStringFound = TRUE;
            TransToMHz = TRUE;
            break;
        } else if (*CpuBrandString == 'M' && *(CpuBrandString+1) == 'H' && *(CpuBrandString + 2) == 'z') {
            FreqStringFound = TRUE;
            break;
        } else ++CpuBrandString;
    }

    --CpuBrandString;   //first numeric char

    //search numeric char
    CharCount = 0;
    for(i = 0 ; i < 4; ++i) {
        if (*CpuBrandString >= '0' && *CpuBrandString <= '9') {
            --CpuBrandString;
            ++CharCount;
        } else if (*CpuBrandString == '.') {
            --CpuBrandString;
            ++CharCount;
        } else break;
    }

    ++CpuBrandString;   //first numeric char

    if (FreqStringFound && CharCount > 0) {
        for(i = 0; i < CharCount; ++i) {
            if (TransToMHz && *CpuBrandString == '.') CpuBrandString++;

            CpuMaxSpeedString[i] = *CpuBrandString;
            ++CpuBrandString;
        }
        if (TransToMHz) CpuMaxSpeedString[3] = '0';
    } else FreqStringFound = FALSE;

    return FreqStringFound;
}
//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   FillCacheData
//
// Description: Init global cache data varilable
//
// Input:
//  IN AMI_CPU_INFO_2_CACHE_DESCR *CacheDesc
//  IN UINT32 NumCacheEntries
//
// Output:  VOID
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID FillCacheData(IN AMI_CPU_INFO_2_CACHE_DESCR *CacheDesc, IN UINT32 NumCacheEntries)
{
    AMI_CPU_INFO_2_CACHE_DESCR *ptr = CacheDesc;
    while (NumCacheEntries--) {
        switch(ptr->Level) {
        case 1:
            switch(ptr->Type) {
            case AMI_CPU_INFO_2_CACHE_TYPE_DATA: gL1DataCacheSize = ptr->Size; break;
            case AMI_CPU_INFO_2_CACHE_TYPE_CODE: gL1CodeCacheSize = ptr->Size; break;
            default: ASSERT(FALSE); // Not valid cache for setup display.
            }
            gL1Shared = ptr->Shared != AMI_CPU_INFO_2_CACHE_SHARED_CORE;
            break;
        case 2:
            switch(ptr->Type) {
            case AMI_CPU_INFO_2_CACHE_TYPE_UNIFIED: gL2CacheSize = ptr->Size; break;
            default: ASSERT(FALSE); //Not valid cache for setup display.
            }
            gL2Shared = ptr->Shared != AMI_CPU_INFO_2_CACHE_SHARED_CORE;
            break;
        case 3:
            switch(ptr->Type) {
            case AMI_CPU_INFO_2_CACHE_TYPE_UNIFIED: gL3CacheSize = ptr->Size; break;
            default: ASSERT(FALSE); //Not valid cache for setup display.
            }
            gL3Shared = ptr->Shared != AMI_CPU_INFO_2_CACHE_SHARED_CORE;
            break;
        case 4:
            switch(ptr->Type) {
            case AMI_CPU_INFO_2_CACHE_TYPE_UNIFIED: gL4CacheSize = ptr->Size; break;
            default: ASSERT(FALSE); //Not valid cache for setup display.
            }
            gL4Shared = ptr->Shared != AMI_CPU_INFO_2_CACHE_SHARED_CORE;
            break;
        default:
            ASSERT(FALSE);  //Invalid entry;
        }

        ptr = (AMI_CPU_INFO_2_CACHE_DESCR*)((UINT8*)ptr + ptr->LengthDesc);
    }
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   LocateCpuInfoProt
//
// Description: Callback on AMI CPU INFO protocol. Then call to init strings.
//
// Input:
//  IN EFI_EVENT Event - Not used
//  IN VOID *Context - Not Used
//
// Output:  VOID
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID LocateCpuInfoProt(IN EFI_EVENT Event, IN VOID *Context)
{
    pBS->LocateProtocol (&gAmiCpuInfoProtocolGuid, NULL, &gCpuInfoProt);
    InitCpuInfo();
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   LocateCpuInfoProt
//
// Description: Callback on AMI CPU INFO 2 protocol. Then call to init strings.
//
// Input:
//  IN EFI_EVENT Event - Not used
//  IN VOID *Context - Not Used
//
// Output:  VOID
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID LocateCpuInfo2Prot(IN EFI_EVENT Event, IN VOID *Context)
{
    pBS->LocateProtocol (&gAmiCpuInfo2ProtocolGuid, NULL, &gCpuInfo2Prot);
    InitCpuInfo();
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	InitCpuInfo
//
// Description:	Initialize CPU strings.
//
// Input: VOID
//
// Output:
//      VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

static VOID InitCpuInfo()
{
	UINTN                   CpuNumber = 0;
	AMI_CPU_INFO            *GetCpuInfo = NULL;
    CHAR8	                CpuMaxSpeedString[] = "9999 MHz";
    OUT AMI_CPU_INFO_2_CACHE_DESCR   *CacheDesc;
    OUT UINT32              NumCacheEntries;
    UINT32                  Bclk;
    UINT32                  i = 0;
    BOOLEAN                 FreqStringFound = FALSE;
    UINT32                  RegEax, RegEbx, RegEcx, RegEdx;
    BOOLEAN                 EistSupported = FALSE;
    BOOLEAN                 C3Supported = FALSE;
    BOOLEAN                 C6Supported = FALSE;
    BOOLEAN                 C7Supported = FALSE;
    EFI_STATUS              Status;

    if (gCpuInfoProt == NULL) return;
    if (gCpuInfo2Prot == NULL) return;    
    
    Bclk = 100; //Bclk = 100 for SandyBridge and IvyBridge
    
    CPULib_CpuID(1, &RegEax, &RegEbx, &RegEcx, &RegEdx);
    if (RegEcx & 0x80) EistSupported = TRUE;
    CPULib_CpuID(5, &RegEax, &RegEbx, &RegEcx, &RegEdx);
    if ((RegEdx >> 8) & 0xf) C3Supported = TRUE;
    if ((RegEdx >> 12) & 0xf) C6Supported = TRUE;
    if ((RegEdx >> 16) & 0xf) C7Supported = TRUE;

	gCpuInfoProt->GetCpuInfo(gCpuInfoProt, CpuNumber, &GetCpuInfo);    

#if CPU_SETUP_SET_MAX_RATIO
{    
    BOOLEAN HasTurbo;

    CPULib_CpuID(6, &RegEax, &RegEbx, &RegEcx, &RegEdx);
    HasTurbo = !!(RegEax & 2);

    if (HasTurbo) {
        InitString(
            gHiiHandle,
            STRING_TOKEN(STR_CPU_MAX_RATIO_HELP),
    		L"Non Turbo Range: %d - %d. Turbo ratio: %d. If out of range ratio, maximum or minimum ratio is used. This sets the maximum ratio.",
            Shr64(ReadMsr(PlatformInfoMsr),40) & 0xff,     //Get Max and Min ratio from MSR
            Shr64(ReadMsr(PlatformInfoMsr),8) & 0xff,
            (Shr64(ReadMsr(PlatformInfoMsr),8) & 0xff )+ 1
    	);
    } else {
        InitString(
            gHiiHandle,
            STRING_TOKEN(STR_CPU_MAX_RATIO_HELP),
    		L"Range: %d - %d. If out of range ratio, maximum or minimum ratio is used. This sets the maximum ratio.",
            Shr64(ReadMsr(PlatformInfoMsr),40) & 0xff,
            Shr64(ReadMsr(PlatformInfoMsr),8) & 0xff
    	);
    }
}
#endif
#if CPU_SETUP_SET_BOOT_RATIO
    InitString(
        gHiiHandle,
        STRING_TOKEN(STR_CPU_SET_BOOT_RATIO_HELP),
		L"Range: %d - %d.  If out of range ratio, maximum ratio is used. This sets the boot ratio. Non-ACPI OSes will use this ratio.",
        Shr64(ReadMsr(PlatformInfoMsr),40) & 0xff,
        Shr64(ReadMsr(PlatformInfoMsr),8) & 0xff
	);
#endif

    if (GetCpuInfo->X64Supported == 0) {
    	InitString(
    		gHiiHandle,
    		STRING_TOKEN(STR_CPU_EMT64_VALUE),
    		L"%a",
    		"Not Supported"
    	);
    }

	InitString(
		gHiiHandle,
		STRING_TOKEN(STR_PROCESSOR_SPEED_VALUE),
		L"%d MHz",
		(Shr64(ReadMsr(0x198),8) & 0xff) * Bclk
	);

    {
        UINT32 PhysSocket;        
        UINT32 NumCores;
        UINT32 NumThreads;
		CHAR8  *CpuBrandString;
        
        PhysSocket = 0;

        Status = gCpuInfo2Prot->GetNumCoresThreads(gCpuInfo2Prot, i,
                &NumCores, &NumThreads, NULL, NULL
        );
        ASSERT_EFI_ERROR(Status);

        InitString(
    		gHiiHandle,
    		gSktStrTok[PhysSocket].Ver,
    		L"%a",
    		GetCpuInfo->BrandString
    	);
    
    	InitString(
    		gHiiHandle,
    		gSktStrTok[PhysSocket].Id,
    		L"%x",
    		GetCpuInfo->Version
    	);

		InitString(
    		gHiiHandle,
    		gSktStrTok[PhysSocket].Family,
    		L"%x",
    		((GetCpuInfo->Version >> 8) & 0xf)
    	);
    	
    	if(GetCpuInfo->MicroCodeVers != 0) {
    		InitString(
    			gHiiHandle,
    			gSktStrTok[PhysSocket].Microcode,
    			L"%x",
    			GetCpuInfo->MicroCodeVers
    		);
    	}

        CpuBrandString = GetCpuInfo->BrandString;
        FreqStringFound = GetMaxSpeedFromBrandString(CpuBrandString, CpuMaxSpeedString);

        if (FreqStringFound) {
            InitString(
                gHiiHandle,
                gSktStrTok[PhysSocket].MaxSpeed,
                L"%a",
                CpuMaxSpeedString
            );
        } else {
            InitString(
                gHiiHandle,
                gSktStrTok[PhysSocket].MaxSpeed,
                L"%d MHz",
                (Shr64(ReadMsr(PlatformInfoMsr),8) & 0xff )* Bclk
            );
        }
        
        InitString(
            gHiiHandle,
            gSktStrTok[PhysSocket].MinSpeed,
            L"%d MHz",
            (Shr64(ReadMsr(PlatformInfoMsr),40) & 0xff )* Bclk //Get MinRatio from MSR
        );        

        gL1DataCacheSize = 0;
        gL1CodeCacheSize = 0;
        gL2CacheSize = 0;
        gL3CacheSize = 0;
        
        //Get cache data
        Status = gCpuInfo2Prot->GetCoreCacheDesc(gCpuInfo2Prot, i, 0, &CacheDesc, &NumCacheEntries);
        ASSERT_EFI_ERROR(Status);
        
        //Fill cache data
        if (!EFI_ERROR(Status)) {
            FillCacheData(CacheDesc, NumCacheEntries);
        }
       
        if (gL1DataCacheSize) {
            if (gL1Shared) {
                InitString(
                    gHiiHandle,
                    gSktStrTok[PhysSocket].L1DataSize,
                    L"%d kB",
                    gL1DataCacheSize
                );
            } else {
                InitString(
                    gHiiHandle,
                    gSktStrTok[PhysSocket].L1DataSize,
                    L"%d kB x %i",
                    gL1DataCacheSize,
                    NumCores
                );
            }
        }        

        if (gL1CodeCacheSize) {
            if (gL1Shared) {
                InitString(
                    gHiiHandle,
                    gSktStrTok[PhysSocket].L1CodeSize,
                    L"%d kB",
                    gL1CodeCacheSize
                );
            } else {
                InitString(
                    gHiiHandle,
                    gSktStrTok[PhysSocket].L1CodeSize,
                    L"%d kB x %i",
                    gL1CodeCacheSize,
                    NumCores
                );
            }
        }

        if (gL2CacheSize) {
            if (gL2Shared) {
                InitString(
                    gHiiHandle,
                    gSktStrTok[PhysSocket].L2Size,
                    L"%d kB",
                    gL2CacheSize
                );
            } else {
                InitString(
                    gHiiHandle,
                    gSktStrTok[PhysSocket].L2Size,
                    L"%d kB x %i",
                    gL2CacheSize,
                    NumCores
                );
            }
        }

        if (gL3CacheSize) {
            if (gL3Shared) {
                InitString(
                    gHiiHandle,
                    gSktStrTok[PhysSocket].L3Size,
                    L"%d kB",
                    gL3CacheSize
                );
            } else {
                InitString(
                    gHiiHandle,
                    gSktStrTok[PhysSocket].L3Size,
                    L"%d kB x %i",
                    gL3CacheSize,
                    NumCores
                );
            }
        }

        InitString(
            gHiiHandle,
            gSktStrTok[PhysSocket].NumCores,
            L"%i",
            GetCpuInfo->NumCores
        );

        if(GetCpuInfo->NumHts > 1) {
            InitString(
                gHiiHandle,
                gSktStrTok[PhysSocket].HyperThreading,
                L"%a",
                "Supported"
            );
        }
        
        if (GetCpuInfo->Features & (UINT64)1 << (32 + 5)) {   //CPUID eax=1 ecx[5]
            InitString(
                gHiiHandle,
                gSktStrTok[PhysSocket].Vtx,
                L"%a",
                "Supported"
            );
        }

        if (GetCpuInfo->Features & (UINT64)1 << (32 + 6)) {   //CPUID eax=1 ecx[6]
            InitString(
                gHiiHandle,
                gSktStrTok[PhysSocket].Smx,
                L"%a",
                "Supported"
            );
        }
        
        if (EistSupported) {
            InitString(
                gHiiHandle,
                gSktStrTok[PhysSocket].Eist,
                L"%a",
                "Supported"
            );    
        }
                    
        if (C3Supported) {
            InitString(
                gHiiHandle,
                gSktStrTok[PhysSocket].CpuC3,
                L"%a",
                "Supported"
            );
        }
        
        if (C6Supported) {
            InitString(
                gHiiHandle,
                gSktStrTok[PhysSocket].CpuC6,
                L"%a",
                "Supported"
            );
        }
        
        if (C7Supported) {
            InitString(
                gHiiHandle,
                gSktStrTok[PhysSocket].CpuC7,
                L"%a",
                "Supported"
            );
        }        
        
        CpuNumber += GetCpuInfo->NumCores * (GetCpuInfo->NumHts == 0 ? 1 : 2);
    	gCpuInfoProt->GetCpuInfo(gCpuInfoProt, CpuNumber, &GetCpuInfo);
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	InitCpuInfo
//
// Description:	Initialize CPU strings.
//
// Input:
//      IN EFI_HII_HANDLE   HiiHandle
//      IN UINT16           Class
//
// Output:
//      VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID InitCPUStrings(EFI_HII_HANDLE HiiHandle, UINT16 Class)
{
    EFI_EVENT   AmiCpuInfoEvt;
    EFI_STATUS  Status;
    VOID        *CpuNotifyReg;
    VOID        *FirstHob;
    
    if (Class != ADVANCED_FORM_SET_CLASS) return;
    gHiiHandle = HiiHandle;

    FirstHob = GetEfiConfigurationTable(pST, &gHobListGuid);
    ASSERT(FirstHob);
    if (FirstHob == NULL) return;

    gCpuInfoHob = (CPUINFO_HOB*)FirstHob;
    //Find CpuInfo Info Hob.
    while (!EFI_ERROR(Status = FindNextHobByType(EFI_HOB_TYPE_GUID_EXTENSION, &gCpuInfoHob))) {
        if (guidcmp(&gCpuInfoHob->EfiHobGuidType.Name, &gCpuInfoHobGuid) == 0) break;
    }
    ASSERT_EFI_ERROR(Status);
    if (EFI_ERROR(Status)) return;

    Status = pBS->LocateProtocol (&gAmiCpuInfoProtocolGuid, NULL, &gCpuInfoProt);
    if (EFI_ERROR(Status)) gCpuInfoProt = NULL;

    Status = pBS->LocateProtocol (&gAmiCpuInfo2ProtocolGuid, NULL, &gCpuInfo2Prot);
    if (EFI_ERROR(Status)) gCpuInfo2Prot = NULL;


    InitCpuInfo();

    if (gCpuInfoProt == NULL) {
        Status = RegisterProtocolCallback(
            &gAmiCpuInfoProtocolGuid,
            LocateCpuInfoProt,
            NULL,
            &AmiCpuInfoEvt,
            &CpuNotifyReg
        );
        ASSERT_EFI_ERROR(Status);
    }
    if (gCpuInfoProt == NULL) {
        Status = RegisterProtocolCallback(
            &gAmiCpuInfo2ProtocolGuid,
            LocateCpuInfo2Prot,
            NULL,
            &AmiCpuInfoEvt,
            &CpuNotifyReg
        );
        ASSERT_EFI_ERROR(Status);
    }
}

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1987-2013, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
