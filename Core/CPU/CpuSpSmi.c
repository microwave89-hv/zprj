//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1987-2013, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/Haswell/AMI Cpu PKG/CpuSp SMI/CpuSpSmi.c 8     5/24/15 11:37p Davidhsieh $
//
// $Revision: 8 $
//
// $Date: 5/24/15 11:37p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/Haswell/AMI Cpu PKG/CpuSp SMI/CpuSpSmi.c $
// 
// 8     5/24/15 11:37p Davidhsieh
// [TAG]  		EIP215675
// [Category]  	New Feature
// [Description]  	Smm Access Check feautre support
// [Files]  	Cpu.sdl, CpuDxe.c, CpuSpSmi.sdl, CpuSpsmi.c
// 
// 7     10/08/13 3:10a Crystallee
// [TAG]  		EIP137873
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	CPU Security Configuration(MSR 4E0[0]) will be changed
// after S3 resume
// [RootCause]  	Didn't restore the Cpu MSR 4e0 while S3 resume.
// [Solution]  	Restore the Cpu MSR 0x4E0 while S3 resume.
// 
// 6     1/24/13 10:45p Davidhsieh
// [TAG]  		EIP112381
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	TBoot S3 resume fail
// [RootCause]  	MSR 0x2e7 is not restored
// [Solution]  	Save and restore MSR 0x2e7 for S3
// 
// 5     12/18/12 9:23p Davidhsieh
// [TAG]              None
// [Category]       Improvement
// [Description]    Check CPU before lock SMM_FEATURE_CONTROL MSR
// 
// 4     12/09/12 10:35p Davidhsieh
// [TAG]                None
// [Category]         Improvement
// [Description]     Lock SMM_FEATURE_CONTROL MSR 
// 
// 3     10/04/12 9:20a Davidhsieh
// Change the procedure of configuring MTRR
// 
// 2     7/10/12 2:51a Davidhsieh
// [TAG]  		EIP93180
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	The "Event Kernel-Power 137" error event log shows while
// resumed from S3
// [RootCause]  	The fixed and variable Mtrrs of BSP are not restored
// [Solution]  	Restore BPS's mtrss
// 
// 1     2/07/12 4:00a Davidhsieh
//
//
//**********************************************************************

//<AMI_FHDR_START>
//---------------------------------------------------------------------------
//
// Name:        CpuSpSmi.C
//
// Description:	Provide functions to CPU specific SMI
//
//---------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "CpuSpSmi.h"

UINT64	ReadMsr (UINT32 Msr);
VOID WriteMsr(UINT32 Msr, UINT64 Value);

UINTN MpMtrrSynchUpEntry (VOID);
VOID MpMtrrSynchUpExit (UINTN Cr4);

EFI_GUID              SwDispatchProtocolGuid = EFI_SMM_SW_DISPATCH_PROTOCOL_GUID;

EFI_SMM_SYSTEM_TABLE         *mSmst;
EFI_SMM_BASE_PROTOCOL        *pSmmBase;
EFI_SMM_SW_DISPATCH_PROTOCOL *gSwDispatch;

//
// MSR table for S3 resume
//
EFI_MSR_VALUES       mFixedMtrrValues[] = {
  { MTRR_FIX_64K_00000,          0 },
  { MTRR_FIX_16K_80000,          0 },
  { MTRR_FIX_16K_A0000,          0 },
  { MTRR_FIX_4K_C0000,           0 },
  { MTRR_FIX_4K_C8000,           0 },
  { MTRR_FIX_4K_D0000,           0 },
  { MTRR_FIX_4K_D8000,           0 },
  { MTRR_FIX_4K_E0000,           0 },
  { MTRR_FIX_4K_E8000,           0 },
  { MTRR_FIX_4K_F0000,           0 },
  { MTRR_FIX_4K_F8000,           0 },
  { 0,      0 }
};

EFI_MSR_VALUES       mVariableMtrrValues[] = {
  { MTRR_PHYS_BASE_0,             0 },
  { MTRR_PHYS_MASK_0,             0 },
  { MTRR_PHYS_BASE_1,             0 },
  { MTRR_PHYS_MASK_1,             0 },
  { MTRR_PHYS_BASE_2,             0 },
  { MTRR_PHYS_MASK_2,             0 },
  { MTRR_PHYS_BASE_3,             0 },
  { MTRR_PHYS_MASK_3,             0 },
  { MTRR_PHYS_BASE_4,             0 },
  { MTRR_PHYS_MASK_4,             0 },
  { MTRR_PHYS_BASE_5,             0 },
  { MTRR_PHYS_MASK_5,             0 },
  { MTRR_PHYS_BASE_6,             0 },
  { MTRR_PHYS_MASK_6,             0 },
  { MTRR_PHYS_BASE_7,             0 },
  { MTRR_PHYS_MASK_7,             0 },
  { MTRR_PHYS_BASE_8,             0 },
  { MTRR_PHYS_MASK_8,             0 },
  { MTRR_PHYS_BASE_9,             0 },
  { MTRR_PHYS_MASK_9,             0 }
};

#define MiscMsrCount 1

EFI_MSR_VALUES       mMiscMsrValues[] = {
  { 0x2e7,          0 }
};

EFI_MSR_VALUES		mSmmFeatureCtrl = { 0x4e0, 0};

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SaveCpuMsr
//
// Description: This function saves the CPU MSRs for S3 resume usage.
//
// Input:       DispatchHandle      Handle to the Dispatcher
//              DispatchContext     SW SMM dispatcher context
//
// Output:      None
//
// Modified:
//      
// Referrals: 
//
// Notes:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID 
SaveCpuMsr(
    IN EFI_HANDLE                   DispatchHandle,
    IN EFI_SMM_SW_DISPATCH_CONTEXT  *DispatchContext
 )
{
    UINT32  i;    
    
    if (Shr64(ReadMsr(0x17d),57)  & 0x03){
        if (!(ReadMsr(mSmmFeatureCtrl.Index) && 0x01))
            WriteMsr(mSmmFeatureCtrl.Index, ReadMsr(mSmmFeatureCtrl.Index) | 0x01);
		mSmmFeatureCtrl.Value = ReadMsr(mSmmFeatureCtrl.Index);
    }

    //Save Fixed MTRR
    for(i=0; i < NUM_OF_FIXED_MTRRS; i++)
    {
        mFixedMtrrValues[i].Value = ReadMsr(mFixedMtrrValues[i].Index);
    }
    
    //Save variable MTRR
    for (i = 0; i < ((UINT8)(ReadMsr(MSR_IA32_MTRR_CAP) & VCNT_MASK)); i++)
    {
        mVariableMtrrValues[i * 2].Value = ReadMsr(mVariableMtrrValues[i * 2].Index);        
        mVariableMtrrValues[i * 2 + 1].Value = ReadMsr(mVariableMtrrValues[i * 2 + 1].Index);
	}
	
	mMiscMsrValues[0].Value = ReadMsr(mMiscMsrValues[0].Index);
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   RestoreMsrOnCpu
//
// Description: This function restores the CPU MSRs during S3 resume.
//
// Input:       None
//
// Output:      None
//
// Modified:
//      
// Referrals: 
//
// Notes:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID 
RestoreMsrOnCpu(IN VOID *data)
{
    UINT32  i;
    UINTN   Cr4;
    
    Cr4 = MpMtrrSynchUpEntry();
    
    //Restore Fixed MTRR
    for(i=0; i < NUM_OF_FIXED_MTRRS; i++)
    {
        WriteMsr(mFixedMtrrValues[i].Index, mFixedMtrrValues[i].Value );
    }
    
    //Restore variable MTRR
    for (i = 0; i < ((UINT8)(ReadMsr(MSR_IA32_MTRR_CAP) & VCNT_MASK)); i++)
    {
        WriteMsr(mVariableMtrrValues[i * 2].Index, mVariableMtrrValues[i * 2].Value );
        WriteMsr(mVariableMtrrValues[i * 2 + 1].Index, mVariableMtrrValues[i * 2 + 1].Value );     
	}
    
    MpMtrrSynchUpExit (Cr4);
     
    WriteMsr(mMiscMsrValues[0].Index, mMiscMsrValues[0].Value);
    
}   

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   RestoreCpuMsr
//
// Description: This function restores the CPU MSRs during S3 resume.
//
// Input:       DispatchHandle      Handle to the Dispatcher
//              DispatchContext     SW SMM dispatcher context
//
// Output:      None
//
// Modified:
//      
// Referrals: 
//
// Notes:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID 
RestoreCpuMsr(
    IN EFI_HANDLE                   DispatchHandle,
    IN EFI_SMM_SW_DISPATCH_CONTEXT  *DispatchContext
 )
{
    UINT32  i;
    UINTN   Cr4;

	if (Shr64(ReadMsr(0x17d),57)  & 0x03){
        if (!(ReadMsr(mSmmFeatureCtrl.Index) && 0x01)){
            WriteMsr(mSmmFeatureCtrl.Index, (mSmmFeatureCtrl.Value & ~0x01));
			WriteMsr(mSmmFeatureCtrl.Index, ReadMsr(mSmmFeatureCtrl.Index) | 0x01);
		}
    }

    for (i = 0; i < pSmst->NumberOfCpus; ++i) {
        pSmst->SmmStartupThisAp(RestoreMsrOnCpu, i, NULL);
    }
    
    Cr4 = MpMtrrSynchUpEntry();
    RestoreMsrOnCpu(NULL);    
    MpMtrrSynchUpExit (Cr4);
}

#define SMRAM_CPU_DATA_VARIABLE_GUID \
  { \
    0x429501d9, 0xe447, 0x40f4, 0x86, 0x7b, 0x75, 0xc9, 0x3a, 0x1d, 0xb5, 0x4e \
  }

#define SMRAM_CPU_DATA_VARIABLE L"SmramCpuDataVar"

#define SMM_FROM_CPU_DRIVER_SAVE_INFO 0x81

EFI_GUID mSmramCpuDataVariableGuid = SMRAM_CPU_DATA_VARIABLE_GUID;
BOOLEAN mLocked = FALSE;

/**
  Dispatch function for a Software SMI handler.

  @param  DispatchHandle        The handle of this dispatch function.
  @param  DispatchContext       The pointer to the dispatch function's context.
                                The SwSmiInputValue field is filled in
                                by the software dispatch driver prior to
                                invoking this dispatch function.
                                The dispatch function will only be called
                                for input values for which it is registered.

  @return None

**/
VOID
EFIAPI
SmramSaveInfoHandler (
  IN  EFI_HANDLE                    DispatchHandle,
  IN  EFI_SMM_SW_DISPATCH_CONTEXT   *DispatchContext
  )
/**

@brief

  Dispatch function for a Software SMI handler

  @param[in] DispatchHandle  - The handle of this dispatch function.
  @param[in] DispatchContext - The pointer to the dispatch function's context.


**/
{
  EFI_STATUS  Status;
  UINT64      VarData[3];
  UINTN       VarSize;

  if (!mLocked && IoRead8 (SW_SMI_IO_ADDRESS+1) == SMM_FROM_CPU_DRIVER_SAVE_INFO) {
    VarSize = sizeof (VarData);
    Status = pRS->GetVariable (
                    SMRAM_CPU_DATA_VARIABLE,
                    &mSmramCpuDataVariableGuid,
                    NULL,
                    &VarSize,
                    VarData
                    );
    if (!EFI_ERROR (Status) && VarSize == sizeof (VarData)) {
      MemCpy (
        (VOID *) (UINTN) (VarData[0]),
        (VOID *) (UINTN) (VarData[1]),
        (UINTN) (VarData[2])
        );
    }

    mLocked = TRUE;
  }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CpuSmmFeatureEn
//
// Description: 
//
// Input:       DispatchHandle      Handle to the Dispatcher
//              DispatchContext     SW SMM dispatcher context
//
// Output:      None
//
// Modified:
//      
// Referrals: 
//
// Notes:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID 
CpuSmmFeatureEn(
    IN EFI_HANDLE                   DispatchHandle,
    IN EFI_SMM_SW_DISPATCH_CONTEXT  *DispatchContext
 )
{

    UINT64 MsrData;
    
    if (Shr64(ReadMsr(0x17d),58)  & 0x01){
        if (!(ReadMsr(0x4e0) && 0x01)){
            MsrData = ReadMsr(0x4e0);
            MsrData |= 0x4;
            WriteMsr(0x4e0, MsrData);			
		}
    }
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   InSmmFunction
//
// Description: Called from InstallSmiHandler
//
// Input:
//
//
// Output:      None
//
// Modified:
//      
// Referrals: 
//
// Notes:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS InSmmFunction(
    IN EFI_HANDLE          ImageHandle,
    IN EFI_SYSTEM_TABLE    *SystemTable
 )
{
    
    EFI_STATUS  Status;
    EFI_HANDLE  Handle;
    
    EFI_SMM_SW_DISPATCH_CONTEXT Save_CPU_MSR = {SW_SMI_SAVE_MSR};
    EFI_SMM_SW_DISPATCH_CONTEXT Restore_CPU_MSR = {SW_SMI_RESTORE_MSR};    
    EFI_SMM_SW_DISPATCH_CONTEXT CpuDriverSaveInfo = { SMM_FROM_SMBASE_DRIVER };
    EFI_SMM_SW_DISPATCH_CONTEXT CpuSmmFeatureEnable = {SW_SMI_ENABLE_SMM_FEATURE};

    Status = pBS->LocateProtocol(&SwDispatchProtocolGuid,NULL,&gSwDispatch);
    if (EFI_ERROR(Status)) {
        ASSERT_EFI_ERROR(Status);
        return Status;	
    }

    Status = gSwDispatch->Register(
        gSwDispatch,
        SaveCpuMsr,
        &Save_CPU_MSR,
        &Handle
    );
    if (EFI_ERROR(Status)) {
        ASSERT_EFI_ERROR(Status);
        return Status;	
    }

    Status = gSwDispatch->Register(
        gSwDispatch,
        RestoreCpuMsr,
        &Restore_CPU_MSR,
        &Handle
    );
    
    if (EFI_ERROR(Status)) {
        ASSERT_EFI_ERROR(Status);
        return Status;	
    }

    Status = gSwDispatch->Register(
        gSwDispatch,
        SmramSaveInfoHandler,
        &CpuDriverSaveInfo,
        &Handle
    );
    
    if (EFI_ERROR(Status)) {
        ASSERT_EFI_ERROR(Status);
        return Status;	
    }
    
    Status = gSwDispatch->Register(
        gSwDispatch,
        CpuSmmFeatureEn,
        &CpuSmmFeatureEnable,
        &Handle
    );
    
    Status = pBS->LocateProtocol(&gEfiSmmBaseProtocolGuid, NULL, &pSmmBase);
    if (EFI_ERROR(Status)) {
        return Status;
    }

    /*Status = pBS->LocateProtocol (&gEfiSmmThunkProtocolGuid, NULL, &mSmmThunk);
    if (EFI_ERROR(Status)) {
        TRACE_IDESMM(((UINTN)TRACE_ALWAYS, "SMM Thunk Protocol not located.\n"));
    } else {
        TRACE_IDESMM(((UINTN)TRACE_ALWAYS, "SMM Thunk Protocol located.\n"));
    }*/

    pSmmBase->GetSmstLocation (pSmmBase, &mSmst);

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   NotInSmmFunction
//
// Description: If Not In Smm Function
//
// Input:
//
//
// Output:      None
//
// Modified:
//      
// Referrals: 
//
// Notes:   
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS NotInSmmFunction(
 )
{
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CpuSpSmiInit
//
// Description: Initializes CPU specific SMM Drivers.
//
// Input:
//
// Output:
//      EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//  Here is the control flow of this function:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS CpuSpSmiInit(
    IN EFI_HANDLE       ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable
 )
{
    //EFI_STATUS Status;

    InitAmiLib(ImageHandle,SystemTable);

    //Status = pBS->LocateProtocol(&SwDispatchProtocolGuid,NULL,&gSwDispatch);
    //if (EFI_ERROR(Status)) return Status;
//InitSmmHandler
    
   // return InitSmmHandler(ImageHandle, SystemTable, InSmmFunction, NonSmmElinkFunctions);
    
    return InitSmmHandler(ImageHandle, SystemTable, InSmmFunction, NULL);

    
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1987-2013, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

