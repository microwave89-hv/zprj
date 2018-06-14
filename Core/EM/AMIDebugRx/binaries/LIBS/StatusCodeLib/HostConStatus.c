//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
//**                                                             **//
//**         (C)Copyright 2010, American Megatrends, Inc.        **//
//**                                                             **//
//**                     All Rights Reserved.                    **//
//**                                                             **//
//**   5555 Oakbrook Pkwy, Building 200,Norcross, Georgia 30093  **//
//**                                                             **//
//**                     Phone (770)-246-8600                    **//
//**                                                             **//
//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
// $Header: /Alaska/BIN/Modules/AMIDebugRx/binaries/LIBS/StatusCodeLib/HostConStatus.c 2     4/15/11 7:09p Madhans $
//
// $Revision: 2 $
//
// $Date: 4/15/11 7:09p $
//
//*********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/AMIDebugRx/binaries/LIBS/StatusCodeLib/HostConStatus.c $
// 
// 2     4/15/11 7:09p Madhans
// [TAG]  		EIP58122
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	IsAMIDebugRxConnected() CSPLIB function used in PEI gives
// build issues.
// [RootCause]  	IsAMIDebugRxConnected in PEI case code is incomplete.
// [Solution]  	IsAMIDebugRxConnected fixed.
// [Files]  		HostConStatus.c
// 
// 1     3/14/11 9:13p Madhans
// To contribute CSPLib tO check if DebugRx is connected or Not.
//
//*********************************************************************
//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:          HostConStatus.C
//
// Description:   Checks whether the target is connected with host or not.
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "efi.h"
#include "pei.h"
#include "amidxelib.h"
#include "Hob.h"
#ifndef	EFIx64
#include "AMIPeiDebug.h"
#else
#include "AMIPeiDebugX64.h"
#endif


BOOLEAN CheckForHostConnectedinPEI (EFI_PEI_SERVICES **PeiServices);
#define PEI_DBGSUPPORT_DATA_GUID  \
	{0x41cac730, 0xe64e, 0x463b, 0x89, 0x72, 0x25, 0x5e, 0xec, 0x55, 0x55, 0xc2}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: GetEfiConfigurationTableLocal
//
// Description: Gets the efi configuration table
//
// Input: EFI_SYSTEM_TABLE *, EFI_GUID			*
//
// Output: void *
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID * GetEfiConfigurationTableLocal(
	IN EFI_SYSTEM_TABLE *SystemTable,
	IN EFI_GUID			*Guid
	)
{
	EFI_CONFIGURATION_TABLE	*Table = SystemTable->ConfigurationTable;
	UINTN i = SystemTable->NumberOfTableEntries;

	for (;i;--i,++Table)
	{
		if (guidcmp(&Table->VendorGuid,Guid)==0) return Table->VendorTable;
	}
	return 0;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: IsAMIDebugRxConnected
//
// Description: checks whether the target is connected with host or not.
//
// Input: EFI_PEI_SERVICES **, EFI_SYSTEM_TABLE *
//
// Output: BOOLEAN  
//              TRUE: If host is connected
//              FALSE : If host is not connected
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN IsAMIDebugRxConnected (EFI_PEI_SERVICES **PeiServices, EFI_SYSTEM_TABLE *ST)
{
	EFI_STATUS	Status = EFI_NOT_FOUND;
    BOOLEAN     RetStatus = FALSE;
    EFI_GUID    HobListGuid	= HOB_LIST_GUID;
    EFI_GUID    mPeiDebugDataGuid = PEI_DBGSUPPORT_DATA_GUID;
    EFI_HOB_MEMORY_ALLOCATION *MemoryHob = NULL;
    PEIDebugData_T	        *pPeiDbgDataSection;
    EFI_PHYSICAL_ADDRESS 	DSMemoryBaseAddress = 0;
    SerXPortGblData_T       *pSerXPortGblData_T = NULL;

    if (PeiServices == NULL)        //For DXE check
    {
    	MemoryHob = (EFI_HOB_MEMORY_ALLOCATION*)GetEfiConfigurationTableLocal (ST,&HobListGuid);
    	if (MemoryHob)
    	{
    		//Status = FindNextHobByGuid(&mPeiDebugDataGuid,(VOID**)&MemoryHob);
    	    for(;;){
    	        Status = FindNextHobByType (EFI_HOB_TYPE_MEMORY_ALLOCATION,&MemoryHob);
    	        if (EFI_ERROR(Status)) break;
    	        if (!guidcmp(&MemoryHob->AllocDescriptor.Name,&mPeiDebugDataGuid)) {
            		DSMemoryBaseAddress = MemoryHob->AllocDescriptor.MemoryBaseAddress;
		            pPeiDbgDataSection = (PEIDebugData_T*) DSMemoryBaseAddress;
                    pSerXPortGblData_T = (SerXPortGblData_T *)pPeiDbgDataSection->XportLocalVar;
                    if (pSerXPortGblData_T->m_IsHostConnected)
                    {
                        RetStatus = TRUE;
                        break;
                    }
       	        }
    	    }
    	}
    }
    else            //For PEI Check
    {
        RetStatus = CheckForHostConnectedinPEI (PeiServices);
    }
	return RetStatus;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: CheckForHostConnectedinPEI
//
// Description: checks whether the target is connected with host in PEI
//
// Input: void
//
// Output: BOOLEAN  
//              TRUE: If host is connected
//              FALSE : If host is not connected
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN CheckForHostConnectedinPEI (EFI_PEI_SERVICES **PeiServices)
{
	PEIDebugData_T *pData;	
	SerXPortGblData_T *SerData;
	VOID						*FirstHob = NULL;
	EFI_HOB_MEMORY_ALLOCATION	*Hob = NULL;
    EFI_GUID    mPeiDebugDataGuid = PEI_DBGSUPPORT_DATA_GUID;

	//Find PEI Debugger Data section by HOB
	for((*PeiServices)->GetHobList(PeiServices,&FirstHob); 
		!EFI_ERROR(FindNextHobByType(EFI_HOB_TYPE_MEMORY_ALLOCATION,&FirstHob));
	)
	{
		Hob = (EFI_HOB_MEMORY_ALLOCATION *) FirstHob;

		if (guidcmp (&mPeiDebugDataGuid, &Hob->AllocDescriptor.Name) == 0)  {
			pData = (PEIDebugData_T *)Hob->AllocDescriptor.MemoryBaseAddress;
			break;
		}
	}
	if(pData == NULL)
		return FALSE;

	SerData = (SerXPortGblData_T *)(pData->XportLocalVar); 

	if(SerData->m_IsHostConnected)
	{
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
//**                                                             **//
//**         (C)Copyright 2010, American Megatrends, Inc.        **//
//**                                                             **//
//**                     All Rights Reserved.                    **//
//**                                                             **//
//**   5555 Oakbrook Pkwy, Building 200,Norcross, Georgia 30093  **//
//**                                                             **//
//**                     Phone (770)-246-8600                    **//
//**                                                             **//
//*****************************************************************//
//*****************************************************************//
//*****************************************************************//