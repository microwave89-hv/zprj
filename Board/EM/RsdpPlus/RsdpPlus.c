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
// $Header: /Alaska/SOURCE/Modules/RsdpPlus/RsdpPlus.c 8     9/17/12 11:33p Norlwu $
//
// $Revision: 8 $
//
// $Date: 9/17/12 11:33p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/RsdpPlus/RsdpPlus.c $
// 
// 8     9/17/12 11:33p Norlwu
// [TAG]  		EIP92735
// [Category]  	Improvement
// [Description]  	Please help to return the pointer and offset of
// HeapToF000 in MANAGE_SHADOW_RAM_PROTOCOL
// [Files]  		RsdpPlus.c
// ManageShadowRam.c
// ManageShadowProtocol.h
// 
// 7     8/17/12 8:12a Norlwu
// [TAG]  		EIP98247
// [Category]  	Improvement
// [Description]  	[RsdpPlus]Add alignment support in
// MANAGE_SHADOW_RAM_PROTOCOL
// [Files]  		RsdpPlus.sdl
// RsdpPlus.mak
// RsdpPlus.c
// ManageShadowRam.c
// ManageShadowRam.h
// 
// 6     2/09/12 3:15a Norlwu
// [TAG]  		EIP81756
// [Category]  	New Feature
// [Description]  	Enhance RspdPlus module.
// [Files]  		RsdpPlus.sdl
// RsdpPlus.mak
// RsdpPlus.c
// RsdpPlusLInk.c
// RsdpPlus.cif
// 
// 5     12/14/11 4:53a Norlwu
// Change "NbRuntimeShadowsRamWrite" to "OemRuntimShadowRamWrite" routine.
// 
// 4     12/14/11 2:05a Norlwu
// [TAG]  		EIP77341
// [Category]  	Improvement
// [Description]  	V110 can't running ATI_DIAG problem.
// [Files]  		RsdpPlus.sdl
// RsdpPlus.mak
// RsdpPlus.c
// RsdpPlus.chm
// RsdpPlus.cif
// 
// 3     10/21/11 2:36a Norlwu
// [TAG]  		EIP73307 
// [Category]  	Improvement
// [Description]  	The system will hang up or reset during POST when RSDP
// module and SG function support
// [Files]  		RsdpPlus.c
// 
// 2     9/28/11 3:59a Norlwu
// Bug Fix - Twice into  SHELL environment will cause the RSDP address
// failure.
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
// Name:  		RsdpPlus.c
//
// Description:	
//
//<AMI_FHDR_END>
//**********************************************************************

#include <AmiDxeLib.h>
#include <Acpi30.h>
#include <AmiCspLib.h>
#include <Protocol\ManageShadowProtocol.h>

EFI_GUID gManageShadowRamProtocolGuid = MANAGE_SHADOW_RAM_PROTOCOL_GUID;
EFI_GUID gAcpi20TableGuid		= ACPI_20_TABLE_GUID;
EFI_GUID gAcpi11TAbleGuid 	    = ACPI_10_TABLE_GUID;

RSDT_PTR_20 *RSDP = NULL;

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: 	RsdpPlusEntryPoint
//
// Description: Entry point for RsdpPlus initialization.
//				Register a ConOutStarted protocol call back function.
//				 
//				
// Input:	EFI_HANDLE			ImageHandle
//			EFI_SYSTEM_TABLE 	*SystemTable
//
// Output:	EFI_STATUS	Status
//      
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS RsdpPlusEntryPoint(
	IN EFI_HANDLE ImageHandle,
	IN EFI_SYSTEM_TABLE *SystemTable
)
{
	EFI_STATUS	Status = EFI_NOT_FOUND;
	MANAGE_SHADOW_RAM_PROTOCOL	*ManageShadowRamProtocol;
	
	InitAmiLib(ImageHandle,SystemTable);

	RSDP = GetEfiConfigurationTable(pST,&gAcpi20TableGuid);
    if (!RSDP) 
    {
        RSDP = GetEfiConfigurationTable(pST,&gAcpi11TAbleGuid);
    }
    if (!RSDP) return Status; 

	TRACE((-1,"Rsdp Sig [%lx] \n",RSDP->Signature));
	TRACE((-1,"Rsdp XSDT addr [%x] \n",RSDP->XsdtAddr));
	TRACE((-1,"Rsdp RSDT addr [%x] \n",RSDP->RsdtAddr));

	Status = pBS->LocateProtocol(&gManageShadowRamProtocolGuid,NULL,&ManageShadowRamProtocol);
	ASSERT_EFI_ERROR(Status);
	
	Status = ManageShadowRamProtocol->HeapToF000((UINT8*)RSDP,0,(UINTN)sizeof(RSDT_PTR_20), NULL);

/* Sample
	{
		DATA_BUFF_STRUC	DataBuff;
		Status = ManageShadowRamProtocol->HeapToF000((UINT8*)RSDP,0,(UINTN)sizeof(RSDT_PTR_20), &DataBuff);
		TRACE((-1,"Norl Dbg : DataBuff Address [0x%x], Length of Used [0x%x] \n",DataBuff.BuffAddress, DataBuff.UsedLength));
		
	}
*/
	ASSERT_EFI_ERROR(Status);

	return Status;
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
