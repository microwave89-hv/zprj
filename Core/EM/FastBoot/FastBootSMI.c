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
// $Header: /Alaska/SOURCE/Modules/PTT/FastBootSMI.c 1     3/11/11 10:07p Bibbyyeh $
//
// $Revision: 1 $
//
// $Date: 3/11/11 10:07p $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/PTT/FastBootSMI.c $
// 
// 1     3/11/11 10:07p Bibbyyeh
// [TAG]		EIP54993
// [Category]	Improvement
// [Description]
// 1.Sync with Fastboot_10
// 2.Remove token "SAVE_LAST_BOOT_DEVICE_CHECKSUM"
// 3.Add token "CALL_DISPATCHER_AGAIN_IN_FASTBOOT"
// 4.Use SimpleText protocol to detect mode change hotkey instead of
// pBS->ConIn.
// 5.Simplify the code about "AMILEGACY16_FASTBOOT_SOLUTION".
// 6.Fixed a bug that SATA device can't be found if keep TSE execution on
// fastboot path.
// [Files]		PPT.cif FastBoot.sdl FastBootRuntime.c FastBootTseHook.c
// FastBoot.c FastBoot.h FastBoot.sd FastBootProtocol.cif
// FastBootProtocol.h FastBootSMI.cif FastBootSMI.sdl FastBootSMI.c
// FastBootSMI.dxs FastBootSMI.mak
//
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:  FastBootSMI.c
//
// Description:
// Implementation of fast boot smi functionality
//
//<AMI_FHDR_END>
//*************************************************************************

#include <AmiDxeLib.h>
#include <Token.h>
#include <Protocol\SmiFlash.h>
#include <Protocol\SmmBase.h>
#include <Protocol\SmmSwDispatch.h>
#include <Protocol\SmmGpiDispatch.h>
#include <Protocol\DevicePath.h>
#include <Protocol\LoadedImage.h>
#include "AmiSmm.h"
#include <Setup.h>
#include <token.h>

EFI_GUID gSwSmiCpuTriggerGuid = SW_SMI_CPU_TRIGGER_GUID;
EFI_GUID SwDispatchProtocolGuid = EFI_SMM_SW_DISPATCH_PROTOCOL_GUID;

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SwSmiHandler
//
// Description: SwSmiHandler
//
// Input: 
// IN EFI_HANDLE                   DispatchHandle,
// IN EFI_SMM_SW_DISPATCH_CONTEXT  *DispatchContext
//
// Output:  
// VOID
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID SwSmiHandler(
	IN EFI_HANDLE					DispatchHandle,
	IN EFI_SMM_SW_DISPATCH_CONTEXT	*DispatchContext
)
{
	EFI_SMM_CPU_SAVE_STATE	*pCpuSaveState;
	SW_SMI_CPU_TRIGGER		*SwSmiCpuTrigger;
    EFI_GUID    EfiVariableGuid = EFI_GLOBAL_VARIABLE;        
	UINT8		SwSmiNum;
	UINTN		i;
	UINTN		Cpu = pSmst->CurrentlyExecutingCpu - 1;
    EFI_STATUS  Status;
    
	// Search for software SMI entry
  	for (i = 0; i < pSmst->NumberOfTableEntries; ++i) {
		if (guidcmp(&pSmst->SmmConfigurationTable[i].VendorGuid,&gSwSmiCpuTriggerGuid) == 0) {
			break;
		}
  	}
	
  	// If table found, check for the CPU that caused the software SMI.
  	if (i != pSmst->NumberOfTableEntries) {			// found?
		SwSmiCpuTrigger = pSmst->SmmConfigurationTable[i].VendorTable;
		Cpu = SwSmiCpuTrigger->Cpu;					// got cpu number		
  	}
	
	pCpuSaveState = pSmst->CpuSaveState;
		
	SwSmiNum = (UINT8)DispatchContext->SwSmiInputValue;
	
	// execute according to the software SMI value (from SW_SMI_IO_ADDRESS)
	switch(SwSmiNum)
	{
		case FAST_BOOT_ENABLE_SWSMI:    //enable fast boot
		case FAST_BOOT_DISABLE_SWSMI:   //disable fast boot

        {
            EFI_GUID    SetupGuid = SETUP_GUID;
       	    UINTN       SetupDataSize = sizeof(SETUP_DATA);    
            SETUP_DATA  SetupData;

            Status = pRS->GetVariable(
                            L"Setup", 
                            &SetupGuid, 
                            NULL, 
                            &SetupDataSize, 
                            &SetupData);

            if (SwSmiNum == FAST_BOOT_ENABLE_SWSMI)
                SetupData.FastBoot = 1;
            else if (SwSmiNum == FAST_BOOT_DISABLE_SWSMI)
                SetupData.FastBoot = 0;      

            Status = pRS->SetVariable(
                            L"Setup", 
                            &SetupGuid,
                            EFI_VARIABLE_NON_VOLATILE | \
                            EFI_VARIABLE_BOOTSERVICE_ACCESS | \
                            EFI_VARIABLE_RUNTIME_ACCESS,
                            SetupDataSize, 
                            &SetupData);
            break;
        }

   
      default:            
            break;

	}

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   InSmmFunction
//
// Description: InSmmFunction
//
// Input:
// IN EFI_HANDLE ImageHandle, 
// IN EFI_SYSTEM_TABLE *SystemTable
//
// Output:      
// EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS InSmmFunction( 
    IN EFI_HANDLE ImageHandle, 
    IN EFI_SYSTEM_TABLE *SystemTable
)
{

	EFI_SMM_SW_DISPATCH_PROTOCOL	*SwDispatch;
	EFI_SMM_SW_DISPATCH_CONTEXT 	SwSmiContext1;
	EFI_SMM_SW_DISPATCH_CONTEXT 	SwSmiContext2;
    EFI_GUID    EfiVariableGuid = EFI_GLOBAL_VARIABLE;    
	EFI_HANDLE	SwSmiHandle;
	EFI_STATUS	Status;

	SwSmiContext1.SwSmiInputValue	= FAST_BOOT_ENABLE_SWSMI;
	SwSmiContext2.SwSmiInputValue	= FAST_BOOT_DISABLE_SWSMI;    

	Status = pBS->LocateProtocol(&SwDispatchProtocolGuid, NULL, &SwDispatch);
	if (EFI_ERROR(Status)) 
	    return Status;

	Status = SwDispatch->Register(
		SwDispatch,
		SwSmiHandler,
		&SwSmiContext1,
		&SwSmiHandle
	);

	Status = SwDispatch->Register(
		SwDispatch,
		SwSmiHandler,
		&SwSmiContext2,
		&SwSmiHandle
	);
    
	return Status;
	
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   FastBootSMIEntryPoint
//
// Description: FastBootSMIEntryPoint
//
// Input:       	
// IN EFI_HANDLE		ImageHandle,
// IN EFI_SYSTEM_TABLE	*SystemTable
//
// Output:      
// EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS FastBootSMIEntryPoint(
	IN EFI_HANDLE		ImageHandle,
	IN EFI_SYSTEM_TABLE	*SystemTable
)
{
	InitAmiLib(ImageHandle,SystemTable);

	return InitSmmHandler(ImageHandle, SystemTable, InSmmFunction, NULL);
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


