//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2016, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/OFBD/OFBD.c 10    1/22/16 12:52a Terrylin $
//
// $Revision: 10 $
//
// $Date: 1/22/16 12:52a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/OFBD/OFBD.c $
// 
// 10    1/22/16 12:52a Terrylin
// [TAG]  		EIP253222
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	Update for AMISV035 SMM vulnerability
// [RootCause]  	BufAddr is an embedded input pointer which has not been
// validated to be outside of SMRAM.
// [Solution]  	Change the SMRAM corruption validation rules to use
// AmiBufferValidationLib module.
// [Files]  		OFBD.sdl
// OFBD.c
// OFBD_Help.chm
// 
// 9     8/15/13 5:35a Terrylin
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	Build Error
// [Files]  		OFBD.mak
// OFBD.c
// 
// 8     8/06/13 6:32a Terrylin
// [TAG]  		EIP131682
// [Category]  	Bug Fix
// [Severity]  	Critical
// [Symptom]  	System BIOS will hang up, when AFU run in Windows or Linux.
// 
// 7     7/31/13 4:55a Terrylin
// [TAG]  		EIP125898
// [Category]  	Improvement
// [Description]  	1. Update modules to compliant with PI 1.2 and UEFI
// 2.3.1 specifications. 
// 2. Add OFBD_TC_51_DC_EXT_STRUCT new structure definition.
// [Files]  		OFBD.c
// OFBD.h
// 
// 6     7/02/13 3:18a Terrylin
// [TAG]  		EIP126656
// [Category]  	Improvement
// [Description]  	Limited write into SMRAM via OFBD SMM driver - BugID
// 305380 
// 
// 5     6/14/13 3:54a Terrylin
// [Category]  	Improvement
// [Description]  	Add the Not InSmmFuncList support.
// [Files]  		OFBD.sdl
// OFBD.mak
// OFBD.c
// 
// 4     3/16/11 10:39p Terrylin
// Correct Copyright information.
// 
// 3     3/16/11 10:13p Terrylin
// [TAG]  		EIP51285
// [Category]  	Improvement
// [Description]  	Fill the description of each file for user more
// clearly.
// [Files]  		OFBD.mak
// OFBD.dxs
// OFBD.c
// OFBD.h
// 
// 2     7/02/09 5:54a Klzhan
// Improvement:    Add an E-Link in SMM.
// 
// 1     4/13/09 5:46a Lawrencechang
// Initial check-in.
// 
// 1     3/25/05 5:37p Markw
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	OFBD.c
//
// Description: 
// This is the main file of OFBD module. We setup OFBD SMI handler here. Please also refer to Aptio SMM Module Porting
// guide.
//
//<AMI_FHDR_END>
//**********************************************************************
#include "Efi.h"
#include "token.h"
#include <AmiLib.h>
#include <AmiDxeLib.h>
#if PI_SPECIFICATION_VERSION >= 0x1000A
#include <Protocol\SmmCpu.h>
#include <Protocol\SmmBase2.h>
#include <Protocol\SmmSwDispatch2.h>
#define RETURN(status) {return status;}
#else
#include <Protocol\SmmBase.h>
#include <Protocol\SmmSwDispatch.h>
#endif
#include <Protocol\DevicePath.h>
#include <AmiHobs.h>
#include <AmiSmm.h>
#include <Include\AmiBufferValidationLib.h>
#include "OFBD.h"

EFI_GUID gSwSmiCpuTriggerGuid = SW_SMI_CPU_TRIGGER_GUID;
#if PI_SPECIFICATION_VERSION >= 0x1000A
EFI_GUID gEfiSmmSwDispatchProtocolGuid = EFI_SMM_SW_DISPATCH2_PROTOCOL_GUID;
EFI_GUID gEfiSmmBase2ProtocolGuid = EFI_SMM_BASE2_PROTOCOL_GUID;
EFI_GUID gEfiSmmCpuProtocolGuid = EFI_SMM_CPU_PROTOCOL_GUID;
EFI_SMM_BASE2_PROTOCOL          *gSmmBase2;
EFI_SMM_CPU_PROTOCOL            *gSmmCpu;
#else
EFI_GUID gEfiSmmSwDispatchProtocolGuid = EFI_SMM_SW_DISPATCH_PROTOCOL_GUID;
#endif

SMM_HOB     gSmmHob;

VOID InitParts(VOID *pOFBDBuffer, UINT8 *pOFBDDataHandled);

typedef VOID (OFBD_SMM) (VOID);
extern OFBD_SMM OFBD_SMM_FUNC_LIST EndOfOFBDSMMList;
extern OFBD_SMM OFBD_NOT_SMM_FUNC_LIST EndOfOFBDSMMList;
OFBD_SMM* OFBDInSMMFunc[] = {OFBD_SMM_FUNC_LIST NULL};
OFBD_SMM* OFBDNotInSMMFunc[] = {OFBD_NOT_SMM_FUNC_LIST NULL};

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CheckAddressRange
//
// Description: Check address to avoid TSEG area.
//
// Input:
//  Address     - starting address
//  Range       - length of the area
//
// Output:
//  EFI_SUCCESS         - Access granted
//  EFI_ACCESS_DENIED   - Access denied!
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS CheckAddressRange( IN UINT8 *Address, IN UINTN Range )
{
    // Check the size and range
    if ( ((EFI_PHYSICAL_ADDRESS)Address >= gSmmHob.Tseg) && 
         ((EFI_PHYSICAL_ADDRESS)Address <= (gSmmHob.Tseg + gSmmHob.TsegLength)) )
        return EFI_ACCESS_DENIED;

    if ( (((EFI_PHYSICAL_ADDRESS)Address + Range) >= gSmmHob.Tseg) && 
         (((EFI_PHYSICAL_ADDRESS)Address + Range) <= (gSmmHob.Tseg + gSmmHob.TsegLength)) )
        return EFI_ACCESS_DENIED;

    return EFI_SUCCESS;
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   OFBDSMIHandler
//
// Description: OFBD SMI Handlers.
//
// Input:
//      IN	EFI_HANDLE					DispatchHandle,
//      IN	EFI_SMM_SW_DISPATCH_CONTEXT	*DispatchContext
// Output:
//      EFI_STATUS
//
//<AMI_PHDR_END>
//**********************************************************************
#if PI_SPECIFICATION_VERSION >= 0x1000A
EFI_STATUS 
OFBDSMIHandler (
        IN  EFI_HANDLE                  DispatchHandle,
		IN CONST VOID                   *Context OPTIONAL,
		IN OUT VOID                     *CommBuffer OPTIONAL,
		IN OUT UINTN                    *CommBufferSize OPTIONAL
)
#else
VOID OFBDSMIHandler (
    IN  EFI_HANDLE                  DispatchHandle,
    IN  EFI_SMM_SW_DISPATCH_CONTEXT *DispatchContext
)
#endif
{
#if PI_SPECIFICATION_VERSION < 0x1000A    
    EFI_SMM_CPU_SAVE_STATE	*pCpuSaveState = NULL;
    SW_SMI_CPU_TRIGGER		*SwSmiCpuTrigger = NULL;
    UINTN		i;
#endif
    UINT8		Data;
    UINT64		BuffAddr;
    UINT32		HighBufferAddress = 0;
    UINT32		LowBufferAddress = 0;
    UINTN		Cpu = pSmst->CurrentlyExecutingCpu - 1;
    OFBD_HDR    *OFBDHeader;
    UINT8       OFBDDataHandled = 0;
    EFI_STATUS  Status = EFI_SUCCESS;

#if PI_SPECIFICATION_VERSION >= 0x1000A

	Cpu = ((EFI_SMM_SW_CONTEXT*)CommBuffer)->SwSmiCpuIndex;
    //
    // Found Invalid CPU number, return 
    //
    if(Cpu == (UINTN)-1) RETURN(Status);

    Status = gSmmCpu->ReadSaveState ( gSmmCpu, \
                                      4, \
                                      EFI_SMM_SAVE_STATE_REGISTER_RBX, \
                                      Cpu, \
                                      &LowBufferAddress );
    Status = gSmmCpu->ReadSaveState ( gSmmCpu, \
                                      4, \
                                      EFI_SMM_SAVE_STATE_REGISTER_RCX, \
                                      Cpu, \
                                      &HighBufferAddress );
                                                                                                      
    Data = ((EFI_SMM_SW_CONTEXT*)CommBuffer)->CommandPort;
    	
#else
    for (i = 0; i < pSmst->NumberOfTableEntries; ++i) {
        if (guidcmp(&pSmst->SmmConfigurationTable[i].VendorGuid, \
                                        &gSwSmiCpuTriggerGuid) == 0) {
            break;
        }
    }

    //If found table, check for the CPU that caused the software Smi.
    if (i != pSmst->NumberOfTableEntries) {
        SwSmiCpuTrigger = pSmst->SmmConfigurationTable[i].VendorTable;
        Cpu = SwSmiCpuTrigger->Cpu;
    }

    Data = (UINT8)DispatchContext->SwSmiInputValue;

    pCpuSaveState = pSmst->CpuSaveState;
    HighBufferAddress = pCpuSaveState[Cpu].Ia32SaveState.ECX;
    LowBufferAddress = pCpuSaveState[Cpu].Ia32SaveState.EBX;
#endif    
    BuffAddr = HighBufferAddress;
    BuffAddr = Shl64(BuffAddr, 32);
    BuffAddr += LowBufferAddress;

    //TRACE((-1,"\nOFBD address is:%x ------\n",BuffAddr));

    OFBDHeader = (OFBD_HDR *)BuffAddr;
    if ((Data == OFBD_SW_SMI_VALUE) && (OFBDHeader->OFBD_SIG == 'DBFO'))
    {
        //Status = CheckAddressRange((UINT8*)(UINTN)OFBDHeader, OFBDHeader->OFBD_Size);
        if(EFI_ERROR(AmiValidateMemoryBuffer ((UINT8*)(UINTN)OFBDHeader, \
                                                OFBDHeader->OFBD_Size))) return EFI_ACCESS_DENIED;
        //if (!EFI_ERROR(Status)) {
            OFBDHeader->OFBD_VER = OFBD_VERSION;
            OFBDHeader->OFBD_RS |= OFBD_RS_SUPPORT;
    
            InitParts((VOID *)BuffAddr,&OFBDDataHandled);
        //}
    }

#if PI_SPECIFICATION_VERSION >= 0x1000A
    RETURN(Status);
#endif
}
//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   InSmmFunction
//
// Description: Install OFBD SMI Handlers.
//
// Input:
//      IN EFI_HANDLE           ImageHandle
//      OUT EFI_SYSTEM_TABLE    *SystemTable
// Output:
//      EFI_STATUS
//
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS InSmmFunction(
    IN EFI_HANDLE ImageHandle, 
    IN EFI_SYSTEM_TABLE *SystemTable)
{

#if PI_SPECIFICATION_VERSION >= 0x1000A
    EFI_SMM_SW_DISPATCH2_PROTOCOL    *pSwDispatch = NULL;
    EFI_SMM_SW_REGISTER_CONTEXT      SwContext = {OFBD_SW_SMI_VALUE};
#else
    EFI_SMM_SW_DISPATCH_PROTOCOL    *pSwDispatch;
    EFI_SMM_SW_DISPATCH_CONTEXT     SwContext = {OFBD_SW_SMI_VALUE};
#endif
    
    EFI_STATUS  Status;
    EFI_HANDLE  Handle;
    UINT8 i;
    SMM_HOB     *SmmHob;
    EFI_GUID    SmmHobGuid = SMM_HOB_GUID;
    EFI_GUID    HobListGuid = HOB_LIST_GUID;

    Status = InitAmiBufferValidationLib(ImageHandle, SystemTable);

#if PI_SPECIFICATION_VERSION >= 0x1000A
    Status = InitAmiSmmLib( ImageHandle, SystemTable );
    
    Status = pBS->LocateProtocol(&gEfiSmmBase2ProtocolGuid, NULL, &gSmmBase2);
    if (EFI_ERROR(Status)) return EFI_SUCCESS;

    Status = pSmmBase->GetSmstLocation (gSmmBase2, &pSmst);
    if (EFI_ERROR(Status)) return EFI_SUCCESS;

    Status = pSmst->SmmLocateProtocol( \
                        &gEfiSmmSwDispatch2ProtocolGuid, NULL, &pSwDispatch);
    if (EFI_ERROR(Status)) return EFI_SUCCESS;

    Status = pSmst->SmmLocateProtocol(&gEfiSmmCpuProtocolGuid, NULL, &gSmmCpu);
    if (EFI_ERROR(Status)) return EFI_SUCCESS;
#else
    VERIFY_EFI_ERROR(pBS->LocateProtocol(
                          &gEfiSmmSwDispatchProtocolGuid, NULL, &pSwDispatch));
#endif

    SmmHob = (SMM_HOB*)GetEfiConfigurationTable(pST, &HobListGuid);
    if (SmmHob == NULL) return EFI_NOT_FOUND;
    
    Status = FindNextHobByGuid(&SmmHobGuid,(VOID**)&SmmHob);
    if (EFI_ERROR(Status)) return Status;
        
    MemCpy( &gSmmHob, SmmHob, sizeof(SMM_HOB) );
    
    Status = pSwDispatch->Register(pSwDispatch, OFBDSMIHandler, &SwContext, \
                                                                     &Handle);
    ASSERT_EFI_ERROR(Status);

    for (i = 0; OFBDInSMMFunc[i] != NULL; i++) OFBDInSMMFunc[i]();
    return Status;
}
//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   NotInSmmFunction
//
// Description: Install OFBD SMI Handlers.
//
// Input:
//      IN EFI_HANDLE           ImageHandle
//      OUT EFI_SYSTEM_TABLE    *SystemTable
// Output:
//      EFI_STATUS
//
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS NotInSmmFunction(
    IN EFI_HANDLE ImageHandle, 
    IN EFI_SYSTEM_TABLE *SystemTable)
{
    UINT8 i;
    for (i = 0; OFBDNotInSMMFunc[i] != NULL; i++) OFBDNotInSMMFunc[i]();
    return EFI_SUCCESS;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	OFBDEntryPoint
//
// Description: The main entry point of OFBD module.
//
// Input:
//      IN EFI_HANDLE           ImageHandle
//      OUT EFI_SYSTEM_TABLE    *SystemTable
// Output:
//      EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS OFBDEntryPoint (
    IN EFI_HANDLE         ImageHandle,
    IN EFI_SYSTEM_TABLE   *SystemTable )
{
    InitAmiLib(ImageHandle, SystemTable);
    
    return InitSmmHandler(ImageHandle, SystemTable, InSmmFunction, NotInSmmFunction);
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2016, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
