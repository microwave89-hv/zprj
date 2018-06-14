//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
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
// $Header: /Alaska/SOURCE/Modules/RsdpPlus/RsdpPlusLInk.c 4     7/27/12 7:00a Norlwu $
//
// $Revision: 4 $
//
// $Date: 7/27/12 7:00a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/RsdpPlus/RsdpPlusLInk.c $
// 
// 4     7/27/12 7:00a Norlwu
// [TAG]  		EIP94704
// [Category]  	Bug Fix
// [Symptom]  	Cause the system hatl at the post time.
// [RootCause]  	ManageShasdow protocl is not able to installed, when
// monitor was disconnected.So change the register event to
// BdsAllDeriverConnectGuid and if locate protocl failure return status
// continue.
// [Solution]  	[HP_DTO_emodule] token DEFAULT_CSM_LAUNCH_POLICY=0 and
// BIOS hang with FastBoot enable when monitor was disconnected
// [Files]  		RsdpPlusLInk.c
// ManageShadowRam.c
// 
// 3     2/09/12 3:15a Norlwu
// [TAG]  		EIP81756
// [Category]  	New Feature
// [Description]  	Enhance RspdPlus module.
// [Files]  		RsdpPlus.sdl
// RsdpPlus.mak
// RsdpPlus.c
// RsdpPlusLInk.c
// RsdpPlus.cif
// 
// 2     9/28/11 4:01a Norlwu
// Bug Fix - Solved locate RSDP protocol failure.
// 
// 1     9/19/11 2:05a Norlwu
// [TAG]  		EIP67948
// [Category]  	New Feature
// [Description]  	EFI boot need to create the RSDT table
// [Files]  		RsdpPlus.cif
// RsdpPlus.sdl
// RsdpPlus.mak
// RsdpPlus.c
// RsdpPlusLInk.c
// RsdpPlus.dxs
// RsdpPlus.chm
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:  		RsdpPlusLink.c
//
// Description:	
//
//<AMI_FHDR_END>
//**********************************************************************

#include <AmiDxeLib.h>
#include "ShadowRamProtocol.h"

extern EFI_BOOT_SERVICES *gBS;
extern EFI_SYSTEM_TABLE *gST;
extern EFI_RUNTIME_SERVICES *gRT;

EFI_GUID gShdowRamProtocolGuid = SHADOW_RAM_PROTOCOL_GUID;
SHADOW_RAM_PROTOCOL	*gShadowRamProtocol;

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: 	UpdateShadow
//
// Description: BeforeEfiBootLaunchHook eLink function.
//				
// Input:	VOID
//
// Output:	VOID
//      
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID UpdateShadow(VOID)
{
	EFI_STATUS	Status;
	
	Status = gBS->LocateProtocol(&gShdowRamProtocolGuid,NULL,&gShadowRamProtocol);
    if(!EFI_ERROR(Status))
	    gShadowRamProtocol->UpdateShadowBeforEfiBoot();
		
	return;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: 	EraseShadow
//
// Description: AfterEfiBootLaunchHook eLink function.
//				
// Input:	VOID
//
// Output:	VOID
//      
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID EraseShadow(VOID)
{
	EFI_STATUS	Status;

	Status = gBS->LocateProtocol(&gShdowRamProtocolGuid,NULL,&gShadowRamProtocol);
    if(!EFI_ERROR(Status))
	    gShadowRamProtocol->EraseShadowAfterEfiBoot();
	
	return;
}
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
