//**********************************************************************//
//**********************************************************************//
//**                                                                  **//
//**        (C)Copyright 1985-2016, American Megatrends, Inc.         **//
//**                                                                  **//
//**                       All Rights Reserved.                       **//
//**                                                                  **//
//**        5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093         **//
//**                                                                  **//
//**                       Phone: (770)-246-8600                      **//
//**                                                                  **//
//**********************************************************************//
//**********************************************************************//

//**********************************************************************//
// $Header: /Alaska/SOURCE/Modules/SMBIOS/SmbiosDMIEditSupport/SmbiosDMIEdit.c 27    4/07/16 6:02p Davidd $
//
// $Revision: 27 $
//
// $Date: 4/07/16 6:02p $
//**********************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SMBIOS/SmbiosDMIEditSupport/SmbiosDMIEdit.c $
// 
// 27    4/07/16 6:02p Davidd
// [TAG]  		EIP231162
// [Category]  	New Feature
// [Description]  	Merge Aptio V Smbios -09 changes for Aptio 4
// 4.6.5.5_SMBIOS_40 release
// [Files]  		Smbios.c
// SmbiosDmiEdit.c
// SmbiosDmiEditFunc.c
//
// 26    4/04/16 11:43a Davidd
// [TAG]  		EIP262865
// [Category]  	Improvement
// [Description]  	[APTIO4][Smbios]DmiEdit needs changes as smiflash
// protocol is being changed to deny calls with Smm buffer
// [Files]  		SmbiosDMIEdit.mak
// SmbiosDMIEdit.h
// SmbiosDMIEdit.c
// SmbiosDMIEditFunc.c
//
// 25    2/17/15 1:15p Davidd
// [TAG]  		EIP205509
// [Category]  	Improvement
// [Description]  	Merge Aptio V Smbios EIP193807, 193858, 196901 changes
// into Aptio 4 Smbios
// [Files]  		SmbiosDmiEdit.sdl
// SmbiosDmiEdit.c
// SmbiosNvramFunc.c
// SmbiosGetFlashData.c
//
// 24    11/15/13 4:33p Davidd
// [TAG]           EIP143321
// [Category]      Improvement
// [Description]   Perform "CppCheck" on Smbios module for
// '4.6.5.1_SMBIOS_36' release
// [Files]         SmbiosBoard.c
//                 Smbios.c
//                 SmbiosDMIEdit.c
//                 SmbiosDMIEditFunc.c
//                 SmbiosNvramFunc.c
//
// 23    6/05/13 2:54p Davidd
// [TAG]  		EIP125802
// [Category]  	Improvement
// [Description]  	Privilege escalation into SMM via SMBIOS SMM driver -
// BugID 305325
// [Files]  		SmbiosDMIEdit.c
//
// 22    6/08/12 6:00p Davidd
// [TAG]  		EIP88664
// [Category]  	New Feature
// [Description]  	Need tool to update smbios information
// [Files]  		SmbiosDMIEdit.c
// SmbiosDMIEdit.h
// SmbiosDMIEdit.sdl
// SmbiosDMIEditFunc.c
//
// 21    6/06/12 3:07p Davidd
// [TAG]  		EIP81954
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	WriteOnceTable is not supported when
// SMBIOS_DMIEDIT_DATA_LOC is 2
// [RootCause]  	WriteOnce is not properly checked
// [Solution]  	Changes added to check for WriteOnce status
// [Files]  		SmbiosDMIEdit.c
// SmbiosDMIEditFunc.c
//
// 20    12/19/11 11:23a Davidd
// [TAG]  		EIP78619
// [Category]  	Improvement
// [Description]  	Customer and project name in SmbiosDMIEdit.c file
// [Files]  		SmbiosDMIEdit.c
//
// 19    10/06/11 4:48p Davidd
// EIP65648 extended change.
//
// 18    8/30/11 4:14p Davidd
// [TAG]           EIP65648
// [Category]      Improvement
// [Description]   Update SMBIOS eModules for uEFI 2.3.1 / PI 1.2
// compliance
// [Files]         Smbios.c
//                 Smbios.dxs
//                 SmbiosDMIEdit.c
//                 SmbiosDMIEditFunc.c
//                 SmbiosGetFlashData.c
//                 SmbiosGetFlashData.dxs
//
// 17    8/03/11 10:30a Davidd
// [TAG]           EIP63920
// [Category]      Bug Fix
// [Severity]      Non-Urgent
// [Symptom]       uEFI OS can't support DMI edit tool
// [RootCause]     UEFI OS runs in virtual memory mode. So call to
// GetVariale will crash.
// [Solution]      Added call to InitSmmHandle so pRS will be properly
// converted per Runtime Services Table in SMM mode.
// [Files]         SmbiosDMIEdit.c
//
// 16    3/16/11 3:35p Davidd
// [TAG]           EIP53939
// [Category]      Bug Fix
// [Severity]      Normal
// [Symptom]       SMBIOS DMIEdit Driver always assumes FLASH_BLOCK_SIZE =
// 64KB
// [RootCause]     Block size was assumed to be 64K
// [Solution]      Problem has been fixed with code changes
// [Files]         SmbiosDMIEdit.c
//                 SmbiosDMIEditFunc.c
//
// 15    5/18/10 5:11p Davidd
// Added PnP function 52h commands 3 and 4 support - EIP 38010.
//
// 14    6/02/09 11:18a Davidd
// Updated function headers. (EIP 22180)
//
// 13    1/28/09 11:52a Davidd
// New changes added to support DMIEdit data storage location in flash
// selectable via SMBIOS_DMIEDIT_DATA_LOC SDL token
//
// 12    9/26/08 10:43a Davidd
// Renamed shadow enable / disable functions.
//
// 11    11/27/07 10:26a Davidd
//
// 10    11/19/07 11:53a Robert
//
// 9     10/22/07 4:27p Davidd
// Fixed a hanging problem with DMIEdit running on server2003 64bit SP2 -
// EIP 10754
//
// 8     3/29/07 6:06p Davidd
// Changed the year in the AMI banner.
//
// 7     12/15/06 5:42p Davidd
// Code cleanup and reformatted to coding standard.
//
// 6     3/21/06 8:43p Fasihm
// Added the directives for DevicePath.h to build and changed the protocol
// names to be compatable with the new Aptio 4.5 Core and later.
//
// 5     3/02/06 1:55p Davidd
// Updated include path to SMBios.h. It has been moved to
// Include\Protocol
//
// 4     8/10/05 10:40a Davidd
// Added code to call porting hooks to enable/disable F000 shadow to allow
// updating the SMBIOS Entry Point header.
//
// 3     7/20/05 1:22p Davidd
// Corrected build error with the last change made to detect which CPU is
// running.
//
// 2     7/12/05 11:20a Markw
// Add code to detect which CPU is executing.
//
// 1     4/29/05 2:06p Davidd
// Initial checkin.
//
//**********************************************************************//

#include <AmiDxeLib.h>
#include <Token.h>
#include <AmiHobs.h>
#include <Smm.h>
#include <AmiSmm.h>
#if PI_SPECIFICATION_VERSION >= 0x0001000a && SMM_MINOR_VER >= 43
    #include <Protocol\SmmCpu.h>
    #include <Protocol\SmmBase2.h>
    EFI_SMM_SYSTEM_TABLE2           *mSmst;
#else
    #include <Protocol\SmmBase.h>
    EFI_SMM_SYSTEM_TABLE            *mSmst;
#endif
#include <Protocol\SmmSwDispatch.h>
#include <Protocol\LoadedImage.h>
#include "Protocol\Smbios.h"
#include "SmbiosDMIEdit.h"

#define SMBIOS_SIG (UINT32)'_MS_'

extern  SMBIOS_TABLE_ENTRY_POINT    *SmbiosTableEntryPoint;
extern  UINT8                       *ScratchBufferPtr;
extern  UINT16                      MaximumBufferSize;
extern  BOOLEAN                     SwSmiMethod;

extern VOID EnableShadowWrite();
extern VOID DisableShadowWrite();

EFI_GUID gSwSmiCpuTriggerGuid = SW_SMI_CPU_TRIGGER_GUID;

#if !defined(SMBIOS_DMIEDIT_DATA_LOC) || (SMBIOS_DMIEDIT_DATA_LOC != 2)
#include <Protocol\SmbiosGetFlashDataProtocol.h>
#include <Protocol\SmiFlash.h>
#include <Protocol\FlashProtocol.h>

EFI_GUID                        gSmbiosFlashDataProtocolGuid = EFI_SMBIOS_FLASH_DATA_PROTOCOL_GUID;
EFI_SMBIOS_FLASH_DATA_PROTOCOL  *mSmbiosFlashDataProtocol;
EFI_SMI_FLASH_PROTOCOL          *mSmiFlash;
FLASH_PROTOCOL 					*mFlash = NULL;

#if defined(NonSmiDmiEdit_Support) && (NonSmiDmiEdit_Support == 1)
EFI_GUID                        FlashProtocolGuid = FLASH_PROTOCOL_GUID;
FLASH_PROTOCOL                  *FlashProtocol;
#endif                                  // NonSmiDmiEdit_Support
#endif                                  // SMBIOS_DMIEDIT_DATA_LOC

#if AmiBufferValidationLib_SUPPORT
	#include <Include/AmiBufferValidationLib.h>

    extern EFI_STATUS EFIAPI InitAmiBufferValidationLib(IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable);
    extern EFI_STATUS        AmiValidateMemoryBuffer(VOID* Buffer, UINTN BufferSize);
#else
    EFI_PHYSICAL_ADDRESS        TsegStart = 0;
    EFI_PHYSICAL_ADDRESS        TsegEnd = 0;
#endif

#if defined(NonSmiDmiEdit_Support) && (NonSmiDmiEdit_Support == 1)
EFI_GUID    gEfiAmiDmieditSmbiosProtocolGuid = AMI_DMIEDIT_SMBIOS_GUID;

EFI_SMBIOS_DMIEDIT_PROTOCOL     SmbiosDmieditProtocol = {DmiEditNonSmiHandler};
#endif                                  // NonSmiDmiEdit_Support

VOID WriteOnceStatusInit(VOID);

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetSmbiosTableF000
//
// Description: Searches 0x0F0000 for the SMBIOS signature and fills in the
//              SmbiosTableEntryPoint once it has been found
//
// Input:       None
//
// Output:      None
//
// Modified: SmbiosTableEntryPoint -is modified if table entry point found
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
GetSmbiosTableF000 (VOID)
{
    UINT32              *ptr32;
    UINT16              i;
    static BOOLEAN      NotDone = TRUE;

    if (NotDone) {
        ptr32 = (UINT32*)0xF0000;
        for (i = 0; i < (0x10000 / 16); i++) {
            if (*ptr32 == SMBIOS_SIG) {
                SmbiosTableEntryPoint = (SMBIOS_TABLE_ENTRY_POINT*)ptr32;
                NotDone = FALSE;
                break;
            }

            ptr32 += 4;
        }
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CheckAddress
//
// Description: Check address to avoid TSEG area.
//
// Input:
//  Address     - starting address
//  Function    - DMIEdit function
//
// Output:
//  EFI_SUCCESS         - Access granted
//  DMI_BAD_PARAMETER   - Access denied!
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16
CheckAddress (
    IN UINT8 *Address,
    IN UINT8 Function
)
{
    UINT16  Status = EFI_SUCCESS;

#if AmiBufferValidationLib_SUPPORT
{
	if (AmiValidateMemoryBuffer(Address, 1)) {
		Status = DMI_BAD_PARAMETER;
	}
	else {
		switch(Function) {
			case 0x50:  {
							if (AmiValidateMemoryBuffer((UINT8*)((GET_SMBIOS_INFO*)Address)->DmiBiosRevision32BitAddr, 1) |
								AmiValidateMemoryBuffer((UINT8*)((GET_SMBIOS_INFO*)Address)->NumStructures32BitAddr, 1) |
								AmiValidateMemoryBuffer((UINT8*)((GET_SMBIOS_INFO*)Address)->StructureSize32BitAddr, 1) |
								AmiValidateMemoryBuffer((UINT8*)((GET_SMBIOS_INFO*)Address)->DmiStorageBase32BitAddr, 1) |
								AmiValidateMemoryBuffer((UINT8*)((GET_SMBIOS_INFO*)Address)->DmiStorageSize32BitAddr, 1)) {
								Status = DMI_BAD_PARAMETER;
							}
							break;
						}
			case 0x51:  {
							if (AmiValidateMemoryBuffer((UINT8*)((GET_SMBIOS_STRUCTURE*)Address)->Handle32BitAddr, 1)) {
								Status = DMI_BAD_PARAMETER;
							}
							if (AmiValidateMemoryBuffer((UINT8*)((GET_SMBIOS_STRUCTURE*)Address)->Buffer32BitAddr, 1)) {
								Status = DMI_BAD_PARAMETER;
							}
						}
		}
	}

    return Status;
}
#else
{
    if (TsegStart != 0) {
        //
        // Check address against TSEG
        //
        if ((EFI_PHYSICAL_ADDRESS)Address >= TsegStart &&
            (EFI_PHYSICAL_ADDRESS)Address <= TsegEnd) {
            Status = DMI_BAD_PARAMETER;
        }
        else {
            switch(Function) {
                case 0x50:  {
                                if ((EFI_PHYSICAL_ADDRESS)(((GET_SMBIOS_INFO*)Address)->DmiBiosRevision32BitAddr) >= TsegStart &&
                                    (EFI_PHYSICAL_ADDRESS)(((GET_SMBIOS_INFO*)Address)->DmiBiosRevision32BitAddr) <= TsegEnd) {
                                    Status = DMI_BAD_PARAMETER;
                                }
                                if ((EFI_PHYSICAL_ADDRESS)(((GET_SMBIOS_INFO*)Address)->NumStructures32BitAddr) >= TsegStart &&
                                    (EFI_PHYSICAL_ADDRESS)(((GET_SMBIOS_INFO*)Address)->NumStructures32BitAddr) <= TsegEnd) {
                                    Status = DMI_BAD_PARAMETER;
                                }
                                if ((EFI_PHYSICAL_ADDRESS)(((GET_SMBIOS_INFO*)Address)->StructureSize32BitAddr) >= TsegStart &&
                                    (EFI_PHYSICAL_ADDRESS)(((GET_SMBIOS_INFO*)Address)->StructureSize32BitAddr) <= TsegEnd) {
                                    Status = DMI_BAD_PARAMETER;
                                }
                                if ((EFI_PHYSICAL_ADDRESS)(((GET_SMBIOS_INFO*)Address)->DmiStorageBase32BitAddr) >= TsegStart &&
                                    (EFI_PHYSICAL_ADDRESS)(((GET_SMBIOS_INFO*)Address)->DmiStorageBase32BitAddr) <= TsegEnd) {
                                    Status = DMI_BAD_PARAMETER;
                                }
                                if ((EFI_PHYSICAL_ADDRESS)(((GET_SMBIOS_INFO*)Address)->DmiStorageSize32BitAddr) >= TsegStart &&
                                    (EFI_PHYSICAL_ADDRESS)(((GET_SMBIOS_INFO*)Address)->DmiStorageSize32BitAddr) <= TsegEnd) {
                                    Status = DMI_BAD_PARAMETER;
                                }
                                break;
                            }
                case 0x51:  {
                                if ((EFI_PHYSICAL_ADDRESS)(((GET_SMBIOS_STRUCTURE*)Address)->Handle32BitAddr) >= TsegStart &&
                                    (EFI_PHYSICAL_ADDRESS)(((GET_SMBIOS_STRUCTURE*)Address)->Handle32BitAddr) <= TsegEnd) {
                                    Status = DMI_BAD_PARAMETER;
                                }
                                if ((EFI_PHYSICAL_ADDRESS)(((GET_SMBIOS_STRUCTURE*)Address)->Buffer32BitAddr) >= TsegStart &&
                                    (EFI_PHYSICAL_ADDRESS)(((GET_SMBIOS_STRUCTURE*)Address)->Buffer32BitAddr) <= TsegEnd) {
                                    Status = DMI_BAD_PARAMETER;
                                }
                            }
            }
        }
    }

    return Status;
}
#endif
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SmiHandler
//
// Description: Handles the SMI
//
// Input:       IN EFI_HANDLE                    DispatchHandle
//              IN EFI_SMM_SW_DISPATCH_CONTEXT   *DispatchContext
//
// Output:      None
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
SmiHandler (
    IN  EFI_HANDLE                    DispatchHandle,
    IN  EFI_SMM_SW_DISPATCH_CONTEXT   *DispatchContext
)
{
    SW_SMI_CPU_TRIGGER      *SwSmiCpuTrigger;
    UINT8                   Data;
    VOID                    *pInterface;
    UINTN                   i;
    UINT16                  RetStatus;
#if PI_SPECIFICATION_VERSION >= 0x0001000a && SMM_MINOR_VER >= 43
    UINTN                   Cpu = mSmst->CurrentlyExecutingCpu;   // For PI 1.1
    EFI_GUID                SmmCpuProtocolGuid = EFI_SMM_CPU_PROTOCOL_GUID;
    EFI_SMM_CPU_PROTOCOL    *SmmCpuProtocol;
#else
	EFI_SMM_CPU_SAVE_STATE	*pCpuSaveState;
    UINTN                   Cpu = mSmst->CurrentlyExecutingCpu - 1;
#endif

    GetSmbiosTableF000();

 	for (i = 0; i < mSmst->NumberOfTableEntries; ++i) {
		if (guidcmp(&mSmst->SmmConfigurationTable[i].VendorGuid,&gSwSmiCpuTriggerGuid) == 0) {
			break;
		}
 	}

    // If found table, check for the CPU that caused the software Smi.
 	if (i != mSmst->NumberOfTableEntries) {
		SwSmiCpuTrigger = mSmst->SmmConfigurationTable[i].VendorTable;
		Cpu = SwSmiCpuTrigger->Cpu;
 	}

#if PI_SPECIFICATION_VERSION >= 0x0001000a && SMM_MINOR_VER >= 43
    mSmst->SmmLocateProtocol(
                        &SmmCpuProtocolGuid,
                        NULL,
                        &SmmCpuProtocol
                        );

    pInterface = 0;         // Clear upper 64-bits.
    SmmCpuProtocol->ReadSaveState(
                            SmmCpuProtocol,
                            4,
                            EFI_SMM_SAVE_STATE_REGISTER_RBX,
                            Cpu,
                            &pInterface
                            );
#else
	pCpuSaveState = mSmst->CpuSaveState;
	pInterface = (void*)pCpuSaveState[Cpu].Ia32SaveState.EBX;
#endif

    SwSmiMethod = TRUE;

	Data = (UINT8)DispatchContext->SwSmiInputValue;

    RetStatus = CheckAddress(pInterface, Data);

    if (RetStatus == EFI_SUCCESS) {
        switch(Data) {
            case 0x50:
                        RetStatus = GetSmbiosInfo(pInterface);
                        break;
            case 0x51:
                        RetStatus = GetSmbiosStructure(pInterface);
                        break;
            case 0x52:
                        EnableShadowWrite();
                        RetStatus = SetSmbiosStructure(pInterface);
                        DisableShadowWrite();
        }
    }

#if PI_SPECIFICATION_VERSION >= 0x0001000a && SMM_MINOR_VER >= 43
    SmmCpuProtocol->WriteSaveState(
                            SmmCpuProtocol,
                            2,
                            EFI_SMM_SAVE_STATE_REGISTER_RAX,
                            Cpu,
                            &RetStatus
                            );
#else
   (UINT16)pCpuSaveState[Cpu].Ia32SaveState.EAX = RetStatus;
#endif
}

#if defined(NonSmiDmiEdit_Support) && (NonSmiDmiEdit_Support == 1)
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   DmiEditNonSmiHandler
//
// Description: Handles the SMI
//
// Input:       IN UINT8    Data
//              IN UINT64   pCommBuff
//
// Output:      None
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT32
DmiEditNonSmiHandler(
    IN UINT8    Data,
    IN UINT64   pCommBuff
)
{
    UINT32      eax;
    VOID        *pInterface;

	TRACE((-1, "SMISMBIOSHandler Data: 0x%X \n",Data));
	pInterface = (void*)pCommBuff;

    GetSmbiosTableF000();

    SwSmiMethod = FALSE;

    switch(Data) {
        case 0x50:
                    eax = GetSmbiosInfo(pInterface);
	TRACE((-1, "eax : 0x%X \n",eax));
                    break;
        case 0x51:
                    eax = GetSmbiosStructure(pInterface);
	TRACE((-1, "eax : 0x%X \n",eax));
                    break;
        case 0x52:
                    EnableShadowWrite();
                    eax = SetSmbiosStructure(pInterface);
                    DisableShadowWrite();
	TRACE((-1, "eax : 0x%X \n",eax));
    }
    return eax;
}
#endif                                  // NonSmiDmiEdit_Support

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   NotInSmmFunction
//
// Description: Performs non-smi initialization
//
// Input:       IN EFI_HANDLE           ImageHandle,
//              IN EFI_SYSTEM_TABLE     *SystemTable
//
// Output:      EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
NotInSmmFunction(
    IN EFI_HANDLE           ImageHandle,
    IN EFI_SYSTEM_TABLE     *SystemTable
)
{
#if defined(NonSmiDmiEdit_Support) && (NonSmiDmiEdit_Support == 1)
    EFI_STATUS  Status;

#if !defined(SMBIOS_DMIEDIT_DATA_LOC) || SMBIOS_DMIEDIT_DATA_LOC != 2
    Status = pBS->LocateProtocol (&FlashProtocolGuid, NULL, &FlashProtocol);
    ASSERT_EFI_ERROR(Status);
#endif                                  // SMBIOS_DMIEDIT_DATA_LOC

	Status = pBS->InstallMultipleProtocolInterfaces(
                 &ImageHandle,
                 &gEfiAmiDmieditSmbiosProtocolGuid,&SmbiosDmieditProtocol,
                 NULL
                 );

    return Status;
#endif                                  // NonSmiDmiEdit_Support

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   InSmmFunction
//
// Description: Initialize pointers and register SW SMI handlers for
//              DMIEdit support.
//
// Input:       IN EFI_HANDLE           ImageHandle,
//              IN EFI_SYSTEM_TABLE     *SystemTable
//
// Output:      EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
InSmmFunction(
    IN EFI_HANDLE           ImageHandle,
    IN EFI_SYSTEM_TABLE     *SystemTable
)
{
    EFI_STATUS                      Status;
	EFI_GUID                        gEfiSmmSwDispatchProtocolGuid = EFI_SMM_SW_DISPATCH_PROTOCOL_GUID;
    EFI_SMM_SW_DISPATCH_PROTOCOL    *SwDispatch;
#if REGISTER_SW_SMI_FN50 || REGISTER_SW_SMI_FN51 || REGISTER_SW_SMI_FN52
    EFI_HANDLE                      SwHandle;
    EFI_SMM_SW_DISPATCH_CONTEXT     SwContext;
#endif

#if PI_SPECIFICATION_VERSION >= 0x0001000a && SMM_MINOR_VER >= 43
    EFI_SMM_BASE2_PROTOCOL          *SmmBase;
	EFI_GUID						gEfiSmmBaseProtocolGuid = EFI_SMM_BASE2_PROTOCOL_GUID;
#else
    EFI_SMM_BASE_PROTOCOL           *SmmBase;
	EFI_GUID						gEfiSmmBaseProtocolGuid = EFI_SMM_BASE_PROTOCOL_GUID;
#endif

#if !defined(SMBIOS_DMIEDIT_DATA_LOC) || SMBIOS_DMIEDIT_DATA_LOC != 2
    EFI_GUID                        gEfiSmiFlashProtocolGuid = EFI_SMI_FLASH_GUID;
    EFI_GUID                        gFlashSmmProtocolGuid = FLASH_SMM_PROTOCOL_GUID;

    Status = pBS->LocateProtocol (&gEfiSmiFlashProtocolGuid, NULL, &mSmiFlash);
    ASSERT_EFI_ERROR(Status);
    if (EFI_ERROR(Status)) {
        return Status;
    }

    Status = pBS->LocateProtocol (&gFlashSmmProtocolGuid, NULL, &mFlash);
    ASSERT_EFI_ERROR(Status);
    if (EFI_ERROR(Status)) {
        return Status;
    }
#endif                                  // SMBIOS_DMIEDIT_DATA_LOC

#if AmiBufferValidationLib_SUPPORT
    Status = InitAmiBufferValidationLib(ImageHandle, SystemTable);
    ASSERT_EFI_ERROR(Status);
    if (EFI_ERROR(Status)) {
        return Status;
    }
#endif

    Status = pBS->LocateProtocol (&gEfiSmmBaseProtocolGuid, NULL, &SmmBase);
    ASSERT_EFI_ERROR(Status);
    if(EFI_ERROR(Status)) {
        return Status;
    }

    SmmBase->GetSmstLocation (SmmBase, &mSmst);   // Save the system table pointer

    // Register the SW SMI handler
    Status = pBS->LocateProtocol (&gEfiSmmSwDispatchProtocolGuid, NULL, &SwDispatch);
    ASSERT_EFI_ERROR(Status);

#if REGISTER_SW_SMI_FN50
    SwContext.SwSmiInputValue = 0x50;
    Status = SwDispatch->Register (SwDispatch, SmiHandler, &SwContext, &SwHandle);

    if (EFI_ERROR (Status)) {
        return Status;
    }
#endif

#if REGISTER_SW_SMI_FN51
    SwContext.SwSmiInputValue = 0x51;
    Status = SwDispatch->Register (SwDispatch, SmiHandler, &SwContext, &SwHandle);

    if (EFI_ERROR (Status)) {
        return Status;
    }
#endif

#if REGISTER_SW_SMI_FN52
    SwContext.SwSmiInputValue = 0x52;
    Status = SwDispatch->Register (SwDispatch, SmiHandler, &SwContext, &SwHandle);

    if (EFI_ERROR (Status)) {
        return Status;
    }
#endif

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SmbiosDmiEditSupportInstall
//
// Description: DMIEdit support driver entry point
//
// Input:       IN EFI_HANDLE           ImageHandle,
//              IN EFI_SYSTEM_TABLE     *SystemTable
//
// Output:      EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
SmbiosDmiEditSupportInstall(
    IN EFI_HANDLE           ImageHandle,
	IN EFI_SYSTEM_TABLE     *SystemTable
)
{
    EFI_STATUS              Status;
    EFI_GUID                gEfiSmbiosProtocolGuid  = EFI_SMBIOS_PROTOCOL_GUID;
    EFI_SMBIOS_PROTOCOL     *SmbiosProtocol;

    InitAmiLib(ImageHandle, SystemTable);

    WriteOnceStatusInit();

    Status = pBS->LocateProtocol (&gEfiSmbiosProtocolGuid, NULL, &SmbiosProtocol);
    ASSERT_EFI_ERROR(Status);
    if(EFI_ERROR(Status)) {
        return Status;
    }

    SmbiosTableEntryPoint = SmbiosProtocol->SmbiosGetTableEntryPoint();
    ScratchBufferPtr = SmbiosProtocol->SmbiosGetScratchBufferPtr();
	MaximumBufferSize = SmbiosProtocol->SmbiosGetBufferMaxSize();

#if !defined(AmiBufferValidationLib_SUPPORT) || (AmiBufferValidationLib_SUPPORT == 0)
{
    CPUINFO_HOB             *CpuInfoHob = NULL;
    EFI_GUID                CpuInfoHobGuid = AMI_CPUINFO_HOB_GUID;
    EFI_GUID                HobListGuid = HOB_LIST_GUID;

    CpuInfoHob = (CPUINFO_HOB*)GetEfiConfigurationTable(pST, &HobListGuid);
    if (CpuInfoHob != NULL) {
        Status = FindNextHobByGuid(&CpuInfoHobGuid,(VOID**)&CpuInfoHob);
        if (Status == EFI_SUCCESS) {
            TsegStart = CpuInfoHob->TsegAddress;
            TsegEnd = CpuInfoHob->TsegAddress + CpuInfoHob->TsegSize;
        }
    }
}
#endif

#if !defined(SMBIOS_DMIEDIT_DATA_LOC) || SMBIOS_DMIEDIT_DATA_LOC != 2
    Status = pBS->LocateProtocol (&gSmbiosFlashDataProtocolGuid, NULL, &mSmbiosFlashDataProtocol);
    ASSERT_EFI_ERROR(Status);
    mSmbiosFlashDataProtocol->GetFlashTableInfo(mSmbiosFlashDataProtocol, &gFlashData, &gFlashDataSize);
#endif                                  // SMBIOS_DMIEDIT_DATA_LOC

    InitSmmHandler(ImageHandle, SystemTable, InSmmFunction, NotInSmmFunction);

    return EFI_SUCCESS;
}

//**********************************************************************//
//**********************************************************************//
//**                                                                  **//
//**        (C)Copyright 1985-2016, American Megatrends, Inc.         **//
//**                                                                  **//
//**                       All Rights Reserved.                       **//
//**                                                                  **//
//**        5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093         **//
//**                                                                  **//
//**                       Phone: (770)-246-8600                      **//
//**                                                                  **//
//**********************************************************************//
//**********************************************************************//
