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
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/Haswell/AMI Cpu PKG/CPU Core/CpuPei.c 9     8/05/14 2:21a Crystallee $
//
// $Revision: 9 $
//
// $Date: 8/05/14 2:21a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/Haswell/AMI Cpu PKG/CPU Core/CpuPei.c $
// 
// 9     8/05/14 2:21a Crystallee
// [TAG]  		EIPNone
// [Category]  	Improvement
// [Description]  	For backward compatible, add old MTRR setting method
// back. Change new MTRR setting method to Policy2.
// 
// 8     7/16/14 4:12a Crystallee
// [TAG]  		EIPNone
// [Category]  	Improvement
// [Description]  	Add WbMemMap and UcMemMap vectors size to prevent
// accessing out of bound.
// 
// 7     7/08/14 3:35a Crystallee
// [TAG]  		EIPNone
// [Category]  	Improvement
// [Description]  	Add all the possible methods to describing memory in
// MTRRS.
// [Files]  		CpuPei.c, CpuPei.h, CpuPeiFuncs.c
// 
// 6     6/25/14 2:15a Davidhsieh
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Add APIC version information in CpuInfoHob
// 
// 5     6/13/14 2:22a Davidhsieh
// [TAG]  		EIP173454
// [Category]  	Improvement
// [Description]  	Add TSEG address and size in CpuInfoHob
// 
// 4     9/05/12 1:40a Davidhsieh
// Rename PEI_IFFS_TRANSITION_START_PPI_GUID to
// PEI_RAPID_START_TRANSITION_START_PPI_GUID
// 
// 3     3/16/12 3:11a Davidhsieh
// Setup items create for CPU RC policy
// 
// 2     3/09/12 2:13a Davidhsieh
// Create BIST data
// 
// 1     2/07/12 3:58a Davidhsieh
// 
//**********************************************************************

//<AMI_FHDR_START>
//---------------------------------------------------------------------------
// Name:        CpuPei.c
//
// Description:
//  This file is the main CPU PEI component file. This component utilizes
//   CPU I/O & PCI CFG PPI to publish early CPU Init PPI which can be used
//   by NB PEI to load itself.  Also this file contains a CPU init routine
//   to be executed in permanent memory present environment. This is handled
//   by issuing a notifyPPI on permanent memory PPI.
//
//---------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "cpu.h"
#include "AmiCspLibInc.h"
#include <AmiPeiLib.h>
#include <core\PeiHob.h>
#include <token.h>
#include <Ppi\ReadOnlyVariable.h>
#include "CpuPei.h"

#define EFI_HT_BIST_HOB_GUID \
  { \
    0xbe644001, 0xe7d4, 0x48b1, 0xb0, 0x96, 0x8b, 0xa0, 0x47, 0xbc, 0x7a, 0xe7 \
  }

typedef struct _CPU_BIST_HOB {
    EFI_HOB_GENERIC_HEADER   Header;
    EFI_GUID                 Name;
    UINT32                   ApicId;
    UINT32                   BIST;    
} CPU_BIST_HOB;

// Setup GUID variables for installing, locating and notifying PPIs
EFI_GUID gPeiCachePpiGuid               = PEI_CACHE_PPI_GUID;
EFI_GUID gEfiPeiEndOfPeiPhasePpiGuid    = EFI_PEI_END_OF_PEI_PHASE_PPI_GUID;
EFI_GUID gAmiCpuinfoHobGuid             = AMI_CPUINFO_HOB_GUID;
EFI_GUID gEfiPeiReadOnlyVariablePpiGuid = EFI_PEI_READ_ONLY_VARIABLE_PPI_GUID;
EFI_GUID gAmiInternaluCodeHobGuid = AMI_INTERNAL_UCODE_HOB_GUID;
EFI_GUID gSmmHobGuid                    = SMM_HOB_GUID;
EFI_GUID gPeiRapidStartTransitionStartPpiGuid = PEI_RAPID_START_TRANSITION_START_PPI_GUID;
//EFI_GUID gCacheInstallGuid              = EFI_CACHE_INSTALL_PPI_GUID;
EFI_GUID gAmiStatusCodeCpuBistDataGuid  = AMI_STATUS_CODE_CPU_BIST_DATA_GUID;
EFI_GUID gEfiHtBistHobGuid              = EFI_HT_BIST_HOB_GUID; 

EFI_STATUS NotifyAtPeiEnd (
    IN EFI_PEI_SERVICES             **PeiServices,
    IN EFI_PEI_NOTIFY_DESCRIPTOR    *NotifyDescriptor,
    IN VOID                         *Ppi
);

EFI_PEI_NOTIFY_DESCRIPTOR CpuNotifyDescs = {
    EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
    &gEfiPeiEndOfPeiPhasePpiGuid,
    NotifyAtPeiEnd
};

/*EFI_PEI_PPI_DESCRIPTOR     CacheInstallPpi[] = {
  (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gCacheInstallGuid,
  NULL
};*/

EFI_PEI_PPI_DESCRIPTOR IffsTransitionStartPpiDescriptor = {
    (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST), \
    &gPeiRapidStartTransitionStartPpiGuid,
    NULL
};

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   ReportBistStatusCodes
//
// Description: Report the BIST Status Code.
//
// Input:   VOID
//
// Output:  VOID
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID ReportBistStatusCodes(IN EFI_PEI_SERVICES **PeiServices, IN CPUINFO_HOB *CpuInfoHob, IN UINT32 NumCpus)
{
    UINT32 i;
    AMI_STATUS_CODE_CPU_BIST_DATA BistData;

    BistData.DataHeader.HeaderSize = sizeof(EFI_STATUS_CODE_DATA);
    BistData.DataHeader.Size = sizeof(UINT32);
    MemCpy(&BistData.DataHeader.Type, &gAmiStatusCodeCpuBistDataGuid, sizeof(EFI_GUID));

    for (i = 0; i < NumCpus; ++i) {        
        if (CpuInfoHob->Cpuinfo[i].BIST != 0) {
            PEI_TRACE((-1, PeiServices, "CpuInfo[%x].BIST = %x \n", i, CpuInfoHob->Cpuinfo[i].BIST));
            BistData.Bist = CpuInfoHob->Cpuinfo[i].BIST;

            (*PeiServices)->ReportStatusCode(
                PeiServices,
                EFI_ERROR_CODE| EFI_ERROR_MAJOR,
                PEI_CPU_SELF_TEST_FAILED,
                CpuInfoHob->Cpuinfo[i].ApicId,
                NULL,
                (EFI_STATUS_CODE_DATA*)&BistData
            );
        }
    }
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: CreateCpuHobWithDefaults
//
// Description: Create CPU Hob and fill in default data.
//
// Input:
//      IN EFI_PEI_SERVICES **PeiServices
//      IN UINT8            NumCpus
//
// Output:
//      CPUINFO_HOB *
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

CPUINFO_HOB * CreateCpuHobWithDefaults(EFI_PEI_SERVICES **PeiServices, UINT8 NumCpus)
{
    CPUINFO_HOB *CpuinfoHob;
    EFI_STATUS  Status;
    UINT32      RegEax;
    UINT32      RegEbx;
    UINT32      RegEcx;
    UINT32      RegEdx;
    UINT8       i;
    VOID        *FirstHob;
    CPU_BIST_HOB *SecBistHob;

    //Create hob for storing Cpu Data
    Status = (**PeiServices).CreateHob(PeiServices,
        EFI_HOB_TYPE_GUID_EXTENSION,
        //NOTE: sizeof(CPUINFO_HOB) already includes size of one CPUINFO structure
        sizeof(CPUINFO_HOB) + (NumCpus - 1) * sizeof(CPUINFO),
        &CpuinfoHob
    );
    ASSERT_PEI_ERROR(PeiServices, Status);

    CpuinfoHob->EfiHobGuidType.Name = gAmiCpuinfoHobGuid;
    CpuinfoHob->CpuCount = NumCpus;
    CpuinfoHob->NodeCount = NUMBER_CPU_SOCKETS;
    CpuinfoHob->CacheLineSize = 64;
    
    CpuinfoHob->TsegAddress = NBGetTsegBase();
    CpuinfoHob->TsegSize = TSEG_SIZE;


    for(i = 0; i < NumCpus; ++i) {
        CpuinfoHob->Cpuinfo[i].Valid    = FALSE;
        CpuinfoHob->Cpuinfo[i].Disabled = FALSE;
        CpuinfoHob->Cpuinfo[i].BIST     = 0;
		CpuinfoHob->Cpuinfo[i].ApicVer = (UINT8)MemRead32((UINT32*)(UINTN)(LOCAL_APIC_BASE + APIC_VERSION_REGISTER));
    }
//Save BSP features to CpuinfoHob
    CPULib_CpuID(0x01, &RegEax, &RegEbx, &RegEcx, &RegEdx);
    CpuinfoHob->CpuFeatures.FeatureEcx = RegEcx;
    CpuinfoHob->CpuFeatures.FeatureEdx = RegEdx;

    CPULib_CpuID(0x80000001, &RegEax, &RegEbx, &RegEcx, &RegEdx);
    CpuinfoHob->CpuFeatures.ExtFeatureEax = RegEax;
    CpuinfoHob->CpuFeatures.ExtFeatureEbx = RegEbx;
    CpuinfoHob->CpuFeatures.ExtFeatureEcx = RegEcx;
    CpuinfoHob->CpuFeatures.ExtFeatureEdx = RegEdx;
    
    (*PeiServices)->GetHobList(PeiServices, &FirstHob);
    if (!FirstHob) ASSERT_PEI_ERROR(PeiServices, EFI_NOT_FOUND);
    
    (VOID*)SecBistHob = FirstHob;
	while (!EFI_ERROR(Status = FindNextHobByType(EFI_HOB_TYPE_GUID_EXTENSION, &SecBistHob))) {
		if (guidcmp(&((EFI_HOB_GUID_TYPE*)SecBistHob)->Name, &gEfiHtBistHobGuid) == 0) {
			break;
		}
	}
	
	if (!EFI_ERROR(Status)) {
        CpuinfoHob->Cpuinfo[SecBistHob->ApicId].BIST = SecBistHob->BIST;    
    }
    
    return CpuinfoHob;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure: UpdateOrCreateCpuHob
//
// Description: Finds or Create Cpu Hob and initialize it.
//
// Input:
//      IN EFI_PEI_SERVICES **PeiServices
//
// Output:
//      VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID UpdateOrCreateCpuHob(EFI_PEI_SERVICES **PeiServices) 
{
    VOID        *FirstHob;
    EFI_HOB_CPU *CpuHob;
    UINT32      RegEax;
    UINT32      RegEbx;
    UINT32      RegEcx;
    UINT32      RegEdx;
    EFI_STATUS  Status;

    (*PeiServices)->GetHobList(PeiServices, &FirstHob);
    if (!FirstHob) ASSERT_PEI_ERROR(PeiServices, EFI_NOT_FOUND);

    CpuHob = (EFI_HOB_CPU*) FirstHob;
    Status = FindNextHobByType(EFI_HOB_TYPE_CPU, &CpuHob);
    if (EFI_ERROR(Status)) {
        Status = (**PeiServices).CreateHob(PeiServices,
            EFI_HOB_TYPE_CPU,
            sizeof(CpuHob),
            &CpuHob
        );
        ASSERT_PEI_ERROR(PeiServices, Status);

        CpuHob->SizeOfMemorySpace = 0xff;
        MemSet(CpuHob->Reserved, 6, 0);
    }

    CPULib_CpuID(0x80000008, &RegEax, &RegEbx, &RegEcx, &RegEdx);
    RegEax &= 0xff;
    if (RegEax < CpuHob->SizeOfMemorySpace) CpuHob->SizeOfMemorySpace = RegEax;
    CpuHob->SizeOfIoSpace = 16; 
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure: NotifyAtPeiEnd
//
// Description: According to resource descriptor HOBs to config system cache.
//
// Input:
//      IN EFI_PEI_SERVICES **PeiServices
//      IN EFI_PEI_NOTIFY_DESCRIPTOR    *NotifyDescriptor
//      IN VOID                         *Ppi
//
// Output:
//      EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS NotifyAtPeiEnd (
    IN EFI_PEI_SERVICES             **PeiServices,
    IN EFI_PEI_NOTIFY_DESCRIPTOR    *NotifyDescriptor,
    IN VOID                         *Ppi
)
{
    EFI_STATUS          Status;
    PEI_CACHE_PPI       *CachePpi;
    UINT64              MaxMemoryLength;
    EFI_BOOT_MODE       BootMode;

#if MTRR_POLICY == 1    
    EFI_PEI_HOB_POINTERS    Hob;
    UINT64                  Above4GMemoryLength = 0;
    MEMORY_MAP              WbMemMap[12];           //Memory map of wb regions.
    MEMORY_MAP              UcMemMap[12];           //Memory map of uc regions.
    UINTN                   i;
#endif    
    //
    //Get bootmode
    //
    Status = (*PeiServices)->GetBootMode(PeiServices, &BootMode);
    PEI_TRACE((-1, PeiServices, "CPUPEI Get boot mode in end of PEI\n"));
    
    if (BootMode == BOOT_ON_S3_RESUME){   
        PEI_TRACE((-1, PeiServices, "CPUPEI boot mode is S3 in end of PEI\n"));
         //Trigger SWSMI to save CPU fixed & varible MTRRs
        IoWrite8(SW_SMI_IO_ADDRESS, SW_SMI_RESTORE_MSR);
        IoWrite8(SW_SMI_IO_ADDRESS, SW_SMI_S3_RESTORE_MSR_FROM_SDL);
    }else{
        //
        // Load Cache PPI
        //      
        Status = (*PeiServices)->LocatePpi(
                    PeiServices,
                    &gPeiCachePpiGuid,
                    0,
                    NULL,
                    &CachePpi
                    ) ;
        ASSERT_PEI_ERROR (PeiServices, Status);
#if MTRR_POLICY == 1
        //if MTRR_POLICY = 1, init MTRR above4G here
        Above4GMemoryLength = 0;        
        (*PeiServices)->GetHobList(PeiServices, &Hob.Raw);        
        //Get above 4G memory length
        while (!END_OF_HOB_LIST (Hob)) {
            if (Hob.Header->HobType == EFI_HOB_TYPE_RESOURCE_DESCRIPTOR) {
                if ((Hob.ResourceDescriptor->ResourceType == EFI_RESOURCE_SYSTEM_MEMORY) ||
                    ((Hob.ResourceDescriptor->ResourceType == EFI_RESOURCE_MEMORY_RESERVED))
                ) {
                    if (Hob.ResourceDescriptor->PhysicalStart >= SIZE_4G 
                        && Hob.ResourceDescriptor->ResourceType == EFI_RESOURCE_SYSTEM_MEMORY) {
                        Above4GMemoryLength += (Hob.ResourceDescriptor->ResourceLength);
                    }
                }
            }
            Hob.Raw = GET_NEXT_HOB (Hob);
        }        
        //
        // Program the MTRR for above 4G memory range if it exist
        // or just disable cache flash range
        //        
        if (Above4GMemoryLength > 0) {
            Status = InitMtrrPolicy1(PeiServices, WbMemMap, UcMemMap, Above4GMemoryLength);
			if(EFI_ERROR(Status))
				Status = InitMtrrPolicy2(PeiServices, WbMemMap, UcMemMap, Above4GMemoryLength);
			
            //If cache map init successful, start program MTRR
            if(!EFI_ERROR(Status)){
                CachePpi->ResetCache(
                            PeiServices,
                            CachePpi);
                //WB region start first            
                for(i = 0; i < 10 ;i++){
                    CachePpi->SetCache(
                                PeiServices, 
                                CachePpi, 
                                WbMemMap[i].Base, 
                                WbMemMap[i].Len, 
                                EfiCacheTypeWriteBack);
                    if(WbMemMap[i + 1].Len == 0) break;            
                }
                //UC region start 
                if(UcMemMap[0].Len != 0){
                    for(i = 0; i < 10 ;i++){
                        CachePpi->SetCache(
                                    PeiServices,
                                    CachePpi,
                                    UcMemMap[i].Base,
                                    UcMemMap[i].Len,
                                    EfiCacheTypeUncacheable);
                        if(UcMemMap[i + 1].Len == 0) break;
                    }                    
                }
                //
                // Programm fix MTRRs WB from 0 to A0000
                //
                CachePpi->SetCache(
                                PeiServices,
                                CachePpi,
                                0,
                                640*1024,
                                EfiCacheTypeWriteBack );
            } else{ //Get MTRR setting fail, still need disable cache flash range
                MaxMemoryLength = GetPowerOfTwo64 (FLASH_SIZE);
                if (MaxMemoryLength < FLASH_SIZE) {
                    MaxMemoryLength = Shl64 (MaxMemoryLength, 1);
                }            
                PEI_TRACE((-1, PeiServices, "WP Memory Length = %08lx at %09lx.\n", MaxMemoryLength, (SIZE_4G - MaxMemoryLength)));
                Status = CachePpi->SetCache (
                            PeiServices,
                            CachePpi,
                            (SIZE_4G - MaxMemoryLength),
                            MaxMemoryLength,
                            EfiCacheTypeUncacheable
                         );
                    
                if (Status) PEI_TRACE((-1, PeiServices, "Disabling Flash Area Cache Error!!\n"));
            }        
        } else{ // if (Above4GMemoryLength > 0) 
            MaxMemoryLength = GetPowerOfTwo64 (FLASH_SIZE);
            if (MaxMemoryLength < FLASH_SIZE) {
                MaxMemoryLength = Shl64 (MaxMemoryLength, 1);
            }           
            PEI_TRACE((-1, PeiServices, "WP Memory Length = %08lx at %09lx.\n", MaxMemoryLength, (SIZE_4G - MaxMemoryLength)));
            Status = CachePpi->SetCache (
                        PeiServices,
                        CachePpi,
                        (SIZE_4G - MaxMemoryLength),
                        MaxMemoryLength,
                        EfiCacheTypeUncacheable
                    );
                    
            if (Status) PEI_TRACE((-1, PeiServices, "Disabling Flash Area Cache Error!!\n"));
        }
        //
        //Disable NEM, Update MTRR setting from MTRR buffer
        //
        CachePpi->ActivateCache (PeiServices, CachePpi);
#else   
        //
        // MTRR for above 4G memory range is already done at this point,
        // only disable cache flash range is required
        //
                
        MaxMemoryLength = GetPowerOfTwo64 (FLASH_SIZE);
        if (MaxMemoryLength < FLASH_SIZE) {
            MaxMemoryLength = Shl64 (MaxMemoryLength, 1);
        }
            
        PEI_TRACE((-1, PeiServices, "WP Memory Length = %08lx at %09lx.\n", MaxMemoryLength, (SIZE_4G - MaxMemoryLength)));
        Status = CachePpi->SetCache (
                            PeiServices,
                            CachePpi,
                            (SIZE_4G - MaxMemoryLength),
                            MaxMemoryLength,
                            EfiCacheTypeUncacheable );
                        
        if (Status) PEI_TRACE((-1, PeiServices, "Disabling Flash Area Cache Error!!\n"));
        
        //
        //Disable NEM, Update MTRR setting from MTRR buffer
        //
        CachePpi->ActivateCache (PeiServices, CachePpi);
#endif        
    }        

    return Status;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure: SetupCache
//
// Description: According to resource descriptor HOBs to config system cache.
//
// Input:
//      IN EFI_PEI_SERVICES **PeiServices
//      IN EFI_BOOT_MODE BootMode
//
// Output:
//      VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID SetupCache ( IN EFI_PEI_SERVICES **PeiServices, IN EFI_BOOT_MODE BootMode)
{
    EFI_STATUS  Status;   
    PEI_CACHE_PPI *CachePpi;    
    UINT64 MemoryLength;
    UINT64 MemoryLengthUc;
    UINT64 MaxMemoryLength;
    UINT64 CurrentBaseAddress;
    UINT64 Above4GMemoryLength;
    UINT64 PowerTwo;
    UINT64 PowerTwoEnd;
    UINT8 MtrrCount = 0;
#if MTRR_POLICY == 0
    EFI_PEI_HOB_POINTERS Hob;
#endif    
    //
    // Load Cache PPI
    //    
    Status = (*PeiServices)->LocatePpi(
                PeiServices,
                &gPeiCachePpiGuid,
                0,
                NULL,
                &CachePpi
                ) ;
    ASSERT_PEI_ERROR (PeiServices, Status);
           
    //
    // Clear the CAR Settings
    //
    CachePpi->ResetCache(
                PeiServices,
                CachePpi
                );
                
                
    //
    // Parse the HOB list and determine the amount of memory installed
    // The first 1MB will be set until overridden by the CSM.
    // The above 4G memory length will be calculated separately.
    //   
    
    MemoryLength = SIZE_1M;
    Above4GMemoryLength = 0;
    
    MemoryLength = (UINT64)NBGetTsegBase() + TSEG_SIZE;
    PEI_TRACE((-1, PeiServices, "Memory Length below 4G= %lx.\n", MemoryLength));
    
    //
    // Record the current address
    //
    CurrentBaseAddress = 0;
    //
    // Set WB loop first
    //

    for (PowerTwo = SIZE_2G, PowerTwoEnd = SIZE_64M; PowerTwo >= PowerTwoEnd; PowerTwo = Shr64 (PowerTwo, 1)) {
        if (MemoryLength >= PowerTwo && MtrrCount < 8) {
            PEI_TRACE((-1, PeiServices, "WB Memory Length = %08lx at %09lx.\n", PowerTwo, CurrentBaseAddress));
            CachePpi->SetCache (PeiServices, CachePpi, CurrentBaseAddress, PowerTwo, EfiCacheTypeWriteBack);
            MtrrCount++;
            CurrentBaseAddress += PowerTwo;
            MemoryLength -= PowerTwo;
        }
    }
    //
    // Get Max Address for WB/UC
    //
    if (MemoryLength == GetPowerOfTwo64 (MemoryLength)) {
        MaxMemoryLength = MemoryLength;
    } else {
        MaxMemoryLength = GetPowerOfTwo64 (Shl64 (MemoryLength, 1));
    }
    //
    // Set the MAX memory range as WB
    //
    if (MaxMemoryLength != 0 && MtrrCount < 8) {
        PEI_TRACE((-1, PeiServices, "WB Memory Length = %08lx at %09lx.\n", MaxMemoryLength, CurrentBaseAddress));
        CachePpi->SetCache (PeiServices, CachePpi, CurrentBaseAddress, MaxMemoryLength, EfiCacheTypeWriteBack);
        MtrrCount++;
    }
    //
    // Start Setting UC here
    //
    while (MaxMemoryLength != MemoryLength) {
        if (MtrrCount == 8) break;
        MemoryLengthUc = GetPowerOfTwo64 (MaxMemoryLength - MemoryLength);
        PEI_TRACE((-1, PeiServices, "UC Memory Length = %08lx at %09lx.\n", MemoryLengthUc, CurrentBaseAddress + MaxMemoryLength - MemoryLengthUc));
        CachePpi->SetCache (
                    PeiServices,
                    CachePpi,
                    CurrentBaseAddress + MaxMemoryLength - MemoryLengthUc,
                    MemoryLengthUc,
                    EfiCacheTypeUncacheable
                    );
        MtrrCount++;
        MaxMemoryLength -= MemoryLengthUc;
    }    
    
#if MTRR_POLICY == 0    
    //
    // Program the MTRR for above 4G memory range
    // if MTRR_POLICY = 1, program the MTRR for above 4G memory range at end of PEI
    //       
    if (BootMode != BOOT_ON_S3_RESUME){
        (*PeiServices)->GetHobList(PeiServices, &Hob.Raw);
        while (!END_OF_HOB_LIST (Hob)) {
            if (Hob.Header->HobType == EFI_HOB_TYPE_RESOURCE_DESCRIPTOR) {
                if ((Hob.ResourceDescriptor->ResourceType == EFI_RESOURCE_SYSTEM_MEMORY) ||
                    ((Hob.ResourceDescriptor->ResourceType == EFI_RESOURCE_MEMORY_RESERVED))
                ) {
                //
                // Calculate the memory above 4G
                //
                    if (Hob.ResourceDescriptor->PhysicalStart >= SIZE_4G 
                        && Hob.ResourceDescriptor->ResourceType == EFI_RESOURCE_SYSTEM_MEMORY) {
                        Above4GMemoryLength += (Hob.ResourceDescriptor->ResourceLength);
                    }
                }
            }
            Hob.Raw = GET_NEXT_HOB (Hob);
        }
    }
    PEI_TRACE((-1, PeiServices, "Memory Length Above 4G= %lx.\n", Above4GMemoryLength));
    if (Above4GMemoryLength > 0) {
        CurrentBaseAddress = SIZE_4G;
        while (Above4GMemoryLength >= SIZE_4G) {
            if (MtrrCount == 10) break;
            PEI_TRACE((-1, PeiServices, "WB Memory Length = %08lx at %09lx.\n", SIZE_4G, CurrentBaseAddress));
            CachePpi->SetCache (PeiServices, CachePpi, CurrentBaseAddress, SIZE_4G, EfiCacheTypeWriteBack);
            MtrrCount++;
            Above4GMemoryLength -= SIZE_4G;
            CurrentBaseAddress += SIZE_4G;
        }
        //
        // Set WB loop first
        //
        for (PowerTwo = SIZE_2G, PowerTwoEnd = SIZE_256M; PowerTwo >= PowerTwoEnd; PowerTwo = Shr64 (PowerTwo, 1)) {
            if (MtrrCount == 10) break;
            if (Above4GMemoryLength >= PowerTwo) {
                PEI_TRACE((-1, PeiServices, "WB Memory Length = %08lx at %09lx.\n", PowerTwo, CurrentBaseAddress));
                CachePpi->SetCache (PeiServices, CachePpi, CurrentBaseAddress, PowerTwo, EfiCacheTypeWriteBack);
                MtrrCount++;
                CurrentBaseAddress += PowerTwo;
                Above4GMemoryLength -= PowerTwo;
            }
        }
        //
        // Get Max Address for WB/UC
        //
        if (Above4GMemoryLength == GetPowerOfTwo64 (Above4GMemoryLength)) {
            MaxMemoryLength = Above4GMemoryLength;
        } else {
            MaxMemoryLength = GetPowerOfTwo64 (Shl64(Above4GMemoryLength, 1));
        }
        //
        // Set the MAX memory range as WB
        //
        if (MaxMemoryLength != 0 && MtrrCount < 10) {
            //PEI_TRACE((-1, PeiServices, "WB Memory Length = %08lx at %09lx.\n", MaxMemoryLength, CurrentBaseAddress));
            CachePpi->SetCache (PeiServices, CachePpi, CurrentBaseAddress, MaxMemoryLength, EfiCacheTypeWriteBack);
            MtrrCount++;
        }
        //
        // Start Setting UC here
        //
        while (MaxMemoryLength != Above4GMemoryLength) {
            if (MtrrCount == 10) break;
            MemoryLengthUc = GetPowerOfTwo64 (MaxMemoryLength - Above4GMemoryLength);
            if (MtrrCount == 9 && (MaxMemoryLength - Above4GMemoryLength) != MemoryLengthUc) {
                MemoryLengthUc = Shl64 (MemoryLengthUc, 1);
            }
            PEI_TRACE((-1, PeiServices, "UC Memory Length = %08lx at %09lx.\n", MemoryLengthUc, CurrentBaseAddress + MaxMemoryLength - MemoryLengthUc));
            CachePpi->SetCache (
                        PeiServices,
                        CachePpi,
                        (CurrentBaseAddress+ MaxMemoryLength - MemoryLengthUc),
                        MemoryLengthUc,
                        EfiCacheTypeUncacheable
                    );
            MtrrCount++;
            MaxMemoryLength -= MemoryLengthUc;
        }
    }
#endif    
    //
    // Programm fix MTRRs WB from 0 to A0000
    //
    PEI_TRACE((-1, PeiServices, "WB Memory Length = %08x at %09x.\n", 640*1024, 0));
    CachePpi->SetCache(
                PeiServices,
                CachePpi,
                0,
                640*1024,
                EfiCacheTypeWriteBack
            );

#if PEI_CACHE_FLASH_ENABLED
    //
    // Cache Flash Area
    //
    MaxMemoryLength = GetPowerOfTwo64 (FLASH_SIZE);
    if (MaxMemoryLength < FLASH_SIZE) {
        MaxMemoryLength = Shl64 (MaxMemoryLength, 1);
    }
        
    PEI_TRACE((-1, PeiServices, "WP Memory Length = %08lx at %09lx.\n", MaxMemoryLength, (SIZE_4G - MaxMemoryLength)));
    Status = CachePpi->SetCache (
                        PeiServices,
                        CachePpi,
                        (SIZE_4G - MaxMemoryLength),
                        MaxMemoryLength,
                        EfiCacheTypeWriteProtected
                    );
                    
    if (Status) PEI_TRACE((-1, PeiServices, "Flash Area Caching Error!!\n"));
#endif
    //
    //Disable NEM, Update MTRR setting from MTRR buffer
    //
    CachePpi->ActivateCache (PeiServices, CachePpi);
    
    //Call back to disable caching flash at end of PEI.
    (*PeiServices)->NotifyPpi(
        PeiServices,
        &CpuNotifyDescs
    );
    //
    // Install EFI_CACHE_INSTALL_PPI_GUID to indicate memory and CPU cache are initialzed.
    //
    /*Status = (*PeiServices)->InstallPpi (
                 PeiServices,
                 CacheInstallPpi);
    ASSERT_PEI_ERROR(PeiServices, Status);*/
}       
//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure: CpuPeiEntry
//
// Description: AMI CPU PEI driver entry
//
// Input:
//      IN EFI_FFS_FILE_HEADER      *FfsHeader
//      IN EFI_PEI_SERVICES         **PeiServices
//
// Output:
//      EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS CpuPeiEntry(
    IN EFI_FFS_FILE_HEADER      *FfsHeader,
    IN EFI_PEI_SERVICES         **PeiServices
)
{
    EFI_PEI_READ_ONLY_VARIABLE_PPI  *ReadOnlyVariable;
    EFI_BOOT_MODE       BootMode;
    EFI_STATUS          Status;
    CPUINFO_HOB         *CpuinfoHob;
    UINT32              NumCpus;
    BOOLEAN             X2ApicEnabled = FALSE;   
    BOOLEAN             Serialize = FALSE;
    UINT32  CpuSignature = GetCpuSignature();
    UINT32  CpuSigNoVer  = CpuSignature & 0xfffffff0;    
    VOID    *MicrocodeAddr = NULL;
    UINT32  MicrocodeSize = 0;
    EFI_PHYSICAL_ADDRESS  	MicrocodeBuffer;
    AMI_INTERNAL_UCODE_HOB *uCodeHob;    
    UINT32      Tseg = (UINT32)NBGetTsegBase();
    SMM_HOB     *SmmHob;
    UINT32 SmmBspBase;
    UINT32 SmmCpuBase;
    UINT32 SmmBase;
    UINT32 LargestSmmBase;
    UINT32 MaxCpusBeforeOverlap;
    UINT32 BeforeOverlapCount;
    UINT32 NextUnoverlapSmmBase;
    UINT32 i;
    
    PEI_PROGRESS_CODE(PeiServices, PEI_CPU_INIT);

    Status = (*PeiServices)->LocatePpi(
        PeiServices, &gEfiPeiReadOnlyVariablePpiGuid, 0, NULL, &ReadOnlyVariable       
    );
    ASSERT_PEI_ERROR(PeiServices, Status);

    Status = (*PeiServices)->GetBootMode(PeiServices, &BootMode);
    ASSERT_PEI_ERROR(PeiServices, Status);

    SetupCache(PeiServices, BootMode);
    UpdateOrCreateCpuHob(PeiServices);

    Status = (*PeiServices)->InstallPpi( PeiServices, \
                                         &IffsTransitionStartPpiDescriptor);

	//After initialized, APs are in holding loop until halted.
	NumCpus = (UINT32)((UINT8)ReadMsr(MSR_CORE_THREAD_COUNT));
	
	PEI_TRACE((-1, PeiServices, "Cpu Pei - number of Cpus %x\n",NumCpus ));
    CpuinfoHob = CreateCpuHobWithDefaults(PeiServices, NumCpus);

    CpuinfoHob->BspNo = 0;

    ReportBistStatusCodes(PeiServices, CpuinfoHob, NumCpus);
    //Create Smm Hob
    Status = (*PeiServices)->CreateHob(
        PeiServices,
        EFI_HOB_TYPE_GUID_EXTENSION,
        sizeof(SMM_HOB)+ (NumCpus - 1) * sizeof(VOID*),
        &SmmHob
    );
    ASSERT_PEI_ERROR(PeiServices, Status);
    MemCpy(&SmmHob->EfiHobGuidType.Name, &gSmmHobGuid, sizeof(EFI_GUID));

    SmmHob->Tseg = Tseg;
    SmmHob->TsegLength = TSEG_SIZE;
    PEI_ASSERT(PeiServices, (SmmHob->Tseg & 0x7fffff)==0);      //Must be 8MB boundary.
    PEI_ASSERT(PeiServices, TSEG_SIZE >= 0x800000);             //Must be >= 8MB.

    SmmHob->IedStart = Tseg + TSEG_SIZE - IED_SIZE;
    SmmHob->IedSize = IED_SIZE;

    SmmHob->NumCpus = NumCpus;
    SmmHob->Bsp = 0;

    SmmBspBase = (UINTN)Tseg - 0x8000;  //Get bottom of TSEG - 0x8000
    SmmBase = SmmBspBase + MAX_SMM_SAVE_STATE_SIZE;

    MaxCpusBeforeOverlap = 0x8000 / MAX_SMM_SAVE_STATE_SIZE - 1;
    BeforeOverlapCount = 0;
    NextUnoverlapSmmBase = (UINTN)Tseg - 0x8000 + 0x10000 - 2 * MAX_SMM_SAVE_STATE_SIZE;
    LargestSmmBase = 0;

    for (i = 0; i < NumCpus; ++i)
    {
        if (i == SmmHob->Bsp)
        {
            SmmCpuBase =  SmmBspBase;
            if (SmmCpuBase >= ((UINTN)Tseg - 0x8000)) ++BeforeOverlapCount; //Only increment count if BSP in TSEG.
        }
        else
        {
            SmmCpuBase = SmmBase;
            ++BeforeOverlapCount;
            if (BeforeOverlapCount < MaxCpusBeforeOverlap)
            {
                SmmBase += MAX_SMM_SAVE_STATE_SIZE;
            }
            else
            {
                SmmBase = NextUnoverlapSmmBase;
                NextUnoverlapSmmBase += 0x10000 - 2 * MAX_SMM_SAVE_STATE_SIZE;
                BeforeOverlapCount = 0;
            }
        }

        SmmHob->SmmBase[i] = SmmCpuBase;

        if (SmmCpuBase > LargestSmmBase) LargestSmmBase = SmmCpuBase;
    }

    if (LargestSmmBase < 0xC0000)
        SmmHob->ManagedMemStart = Tseg;
    else
        SmmHob->ManagedMemStart = LargestSmmBase + 0x10000; //+ 0x10000 = end of save state.

    SmmHob->ManagedMemSize = Tseg + TSEG_SIZE - SmmHob->ManagedMemStart;
    SmmHob->ManagedMemSize -= SmmHob->IedSize;

    PEI_TRACE((-1, PeiServices, "TSEG Base %x\n", SmmHob->Tseg));
    PEI_TRACE((-1, PeiServices, "TSEG Size %x\n", SmmHob->TsegLength));
    PEI_TRACE((-1, PeiServices, "ManagedMemStart %x\n", SmmHob->ManagedMemStart));

    if (BootMode != BOOT_ON_S3_RESUME){
        //Copy CPU microcode from ROM to RAM, when flash ragne is still cached
        //and create hob to record the microcode address
        //Create CPU microcode HOB
        MicrocodeAddr = CPULib_FindMicrocode();
    
        if(MicrocodeAddr != NULL){
            PEI_TRACE((-1, PeiServices, "Cpu uCode ID - %x\n",((MICROCODE_HEADER*)MicrocodeAddr)->CpuSignature ));
            MicrocodeSize = ((MICROCODE_HEADER*)MicrocodeAddr)->TotalSize;
                
            Status = (*PeiServices)->AllocatePages (
										PeiServices,
										EfiBootServicesData, 
										EFI_SIZE_TO_PAGES (MicrocodeSize),
										&MicrocodeBuffer );
            if(!EFI_ERROR(Status)){
                // Copy Microcode from ROM to RAM
	    	    (*PeiServices)->CopyMem (
	                      		(VOID*)MicrocodeBuffer, 
	                      		(VOID*)MicrocodeAddr,
	                      		(UINTN)MicrocodeSize );

                Status = (*PeiServices)->CreateHob(
                                        PeiServices,
                                        EFI_HOB_TYPE_GUID_EXTENSION,
                                        sizeof(AMI_INTERNAL_UCODE_HOB),
                                        &uCodeHob );
                if (!EFI_ERROR(Status)){
                    MemCpy(&uCodeHob->EfiHobGuidType.Name, &gAmiInternaluCodeHobGuid, sizeof(EFI_GUID));                        
                    uCodeHob->uCodeAddr = (UINT32)MicrocodeBuffer;                                            
                }    
            }							 
        }
    }
    
    CpuPeiMiscFuncs(PeiServices, ReadOnlyVariable, BootMode);
    
    return EFI_SUCCESS;

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

