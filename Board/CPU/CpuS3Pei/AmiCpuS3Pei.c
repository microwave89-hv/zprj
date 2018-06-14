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
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/Haswell/AMI Cpu PKG/AMI CPU S3 Pei/AmiCpuS3Pei.c 2     9/28/12 5:40a Davidhsieh $
//
// $Revision: 2 $
//
// $Date: 9/28/12 5:40a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/Haswell/AMI Cpu PKG/AMI CPU S3 Pei/AmiCpuS3Pei.c $
// 
// 2     9/28/12 5:40a Davidhsieh
// Wait APIC idle after sending SMM IPI
// 
// 1     9/26/12 10:45a Davidhsieh
//
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:    AmiCpuS3Pei.c
//
// Description:
//
//<AMI_FHDR_END>
//**********************************************************************
//
#include <PEI.h>
#include <AmiPeiLib.h>
#include <AmiCspLib.h>
#include <Ppi\Stall.h>
#include <Ppi\ReadOnlyVariable.h>
#include <Setup.h>
#include <token.h>
#include "Core/CPU/CPU.h"
#include "Core/CPU/CpuCspLib.h"

EFI_GUID gSmmHobGuid = SMM_HOB_GUID;
EFI_GUID gPeiReadOnlyVariablePpiGuid = EFI_PEI_READ_ONLY_VARIABLE_PPI_GUID;
EFI_GUID gEfiPeiStallPpiGuid            = EFI_PEI_STALL_PPI_GUID;
EFI_GUID gMpCpuApicIdDataGuid = MP_CPU_APIC_ID_DATA_GUID;

#define SMM_ASM_FIXUP_SMM_BASE                  0x38002
#define SMM_ASM_FIXUP_IED_ZERO_MEM              0x38029
#define SMM_ASM_BASE_CHANGE_FLAG                0x3808f
#define APIC_SMI                (2 << 8)
#define APIC_DELIVERY_STATUS    (1 << 12)
#define APIC_LEVEL_ASSERT	    (1 << 14)
#define APIC_NO_SHORT_HAND      (0 << 18)


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   AmiCpuS3PeiEntry
//
// Description: PEI Entry Point for Intel TXT Driver.
//
// Input:       EFI_HANDLE          - ImageHandle
//              EFI_SYSTEM_TABLE*   - SystemTable
//
// Output:      None.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
AmiCpuS3PeiEntry (
    IN EFI_FFS_FILE_HEADER  *FfsHeader,
    IN EFI_PEI_SERVICES     **PeiServices
)
{
    EFI_STATUS          Status;
    EFI_BOOT_MODE       BootMode;
    VOID                *FirstHob;
    SMM_HOB             *SmmHob;
    EFI_PEI_READ_ONLY_VARIABLE_PPI  *ReadOnlyVariable;
    EFI_PEI_STALL_PPI   *PeiStall;
    MP_CPU_APICID_DATA  MpCpuApicIdData;
    UINTN               VariableSize = sizeof(MP_CPU_APICID_DATA);
    BOOLEAN             ApicIdFromVariable = FALSE;
    VOID                *SaveBuffer;
    UINT8               ApicId;
    UINT8               i, j=0;
    
    (*PeiServices)->GetBootMode(PeiServices, &BootMode);
    
	if (BootMode != BOOT_ON_S3_RESUME) 
        return EFI_SUCCESS;
    
    Status = (*PeiServices)->LocatePpi (
        PeiServices, &gPeiReadOnlyVariablePpiGuid, 0, NULL, &ReadOnlyVariable
    );
    ASSERT_PEI_ERROR(PeiServices, Status);
    
    Status = (*PeiServices)->LocatePpi(
        PeiServices, &gEfiPeiStallPpiGuid, 0, NULL, &PeiStall
    );
    ASSERT_PEI_ERROR(PeiServices, Status);
    
    if(!EFI_ERROR(Status)){
        Status = ReadOnlyVariable->GetVariable (
                        PeiServices,
                        L"CPUS3APICID",
                        &gMpCpuApicIdDataGuid,
                        NULL,
                        &VariableSize,
                        &MpCpuApicIdData
                    );
        if(Status == EFI_SUCCESS)
            ApicIdFromVariable = TRUE;  //If CPU S3 APIC ID data found, use local data as CPU APIC ID
    }
    
    (*PeiServices)->GetHobList(PeiServices, &FirstHob);
    SmmHob = (SMM_HOB*)FirstHob;
    while (!EFI_ERROR(Status = FindNextHobByType(EFI_HOB_TYPE_GUID_EXTENSION, &SmmHob)))
    {
        if (guidcmp(&SmmHob->EfiHobGuidType.Name, &gSmmHobGuid) == 0)
            break;
    }
        
    if (!EFI_ERROR(Status))
    {            
        //Allocate memory for temporarly perserve the 3000:8000 data.
        Status = (*PeiServices)->AllocatePool(
                        PeiServices,
                        SmmGetBaseSaveBufferSize(),
                        &SaveBuffer
                        );
        ASSERT_PEI_ERROR(PeiServices, Status);

        SmmSetupDefaultHandler(SaveBuffer, SmmHob);

        for (i = 0; i < SmmHob->NumCpus; ++i)
        {
            *(UINT32*)SMM_ASM_FIXUP_SMM_BASE = (UINT32)SmmHob->SmmBase[i];
            *(volatile UINT8*)SMM_ASM_BASE_CHANGE_FLAG = 0;  //Initialize Flag

            if (ApicIdFromVariable) ApicId = MpCpuApicIdData.ApicId[i];
            else ApicId = j;            
            
            MemReadWrite32((UINT32*)(LOCAL_APIC_BASE + APIC_ICR_HIGH_REGISTER), ApicId << 24, 0x00ffffff);
            MemReadWrite32((UINT32*)(LOCAL_APIC_BASE + APIC_ICR_LOW_REGISTER),  APIC_NO_SHORT_HAND + APIC_LEVEL_ASSERT + APIC_SMI, 0);

            while (!(*(volatile UINT8*)SMM_ASM_BASE_CHANGE_FLAG))
            {
                    CPULib_Pause();    //Wait on Flag
            }
            ++*(UINT16*)SMM_ASM_FIXUP_IED_ZERO_MEM; //Only 0, for first thread to clear IED memory.
            PeiStall->Stall(PeiServices, PeiStall, 50);
            //Wait until IPI is Idle
            while(
                MemRead32((UINT32*)(LOCAL_APIC_BASE + APIC_ICR_LOW_REGISTER)) & APIC_DELIVERY_STATUS
            );            
            
            if (!ApicIdFromVariable){
                if (IsHtEnabled())  j++;
                else j += 2;
            } 
        }

        SmmRemoveDefaultHandler(SaveBuffer);
    }
                    
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
