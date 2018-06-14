//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
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
// $Header: /Alaska/SOURCE/Modules/OFBD/OEMSETUP/OEMSETUP.c 3     3/16/11 10:33p Terrylin $
//
// $Revision: 3 $
//
// $Date: 3/16/11 10:33p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/OFBD/OEMSETUP/OEMSETUP.c $
// 
// 3     3/16/11 10:33p Terrylin
// [TAG]  		EIP51285
// [Category]  	Improvement
// [Description]  	Fill the description for user more clearly.
// [Files]  		OEMSETUP.mak
// OEMSETUP.h
// OEMSETUP.c
// 
// 2     5/06/10 2:12a Lawrencechang
// Add the DMI store/restore function sample code.
// 
// 1     4/13/09 5:47a Lawrencechang
// Initial check-in.
// 
// 1     3/25/05 5:37p Markw
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	OEMSETUP.c
//
// Description: 
// Basically this function is not always necessary for all projects, because there is a more direct method to achieve
// the same target. Two E-Links exposed by SMIFlash module, SMIFlashPreUpdateList and SMIFlashEndUpdateList, are made
// for doing the same thing as this OFBD module.
//
// We prefer you make use of E-Links than this OFBD module. The only advantage of this OFBD module is you don't have
// to link your code with SMIFlash module.If DMI data is stored in the NVRAM, you have two ways to preserve DMI data
// when updating NVRAM.
//
// 1. Controlled by SMBIOS module: SMBIOS module can set SMBIOS_PRESERVE_NVRAM token to preserves DMI data through
// e-Link PreserveDmiEditData and RestoreDmiEditData.
//
// 2. Controlled By Flash utility: AFU will call into OEMSETUP.c only when user issues /r or /sp command. When
// SMBIOS_PRESERVE_NVRAM token is disable, OEM enginner can set OEMSETUP_SUPPORT token to handle the duty of DMI data
// preservation through OEM NVRAM/Setup Variable Preserve module. Thus user can decide to clear DMI data or not.
// In this case, /n parameter will clear NVRAM, and /r parameter is required to preserve DMI data in NVRAM. When /n is
// triggered, without /r all DMI data in NVRAM will be cleared. 
//
//<AMI_FHDR_END>
//**********************************************************************
#include "Efi.h"
#include "token.h"
#include <AmiLib.h>
#include <AmiDxeLib.h>
#include "OEMSETUP.h"
#include "..\OFBD.h"

// EIP 37169 ->
#if (SMBIOS_DMIEDIT_DATA_LOC == 2) && (SMBIOS_PRESERVE_NVRAM != 1)
VOID PreserveDmiEditData (VOID);
VOID RestoreDmiEditData (VOID);
#endif
// <- EIP 37169


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	OFBDSETUPSupportHandle
//
// Description:	OFBD SETUP Store/Restore Support Handle
//
// Input:
//      IN OUT OFBD_HDR *pOFBDHdr
// Output:
//      EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
OFBDSETUPSupportHandle( 
    IN OUT OFBD_HDR *pOFBDHdr)
{
    EFI_STATUS Status = EFI_SUCCESS;

#if OEM_SETUP_SAMPLE_TEST
	OFBD_TC_56_SETUP_STRUCT *SETUPStructPtr;     
	SETUPStructPtr = (OFBD_TC_56_SETUP_STRUCT *)((UINT8 *)pOFBDHdr + pOFBDHdr->OFBD_HDR_SIZE + sizeof(OFBD_EXT_HDR)); 
	SETUPStructPtr->dbRetSts =  OFBD_TC_SETUP_OK;
#endif

    return(Status);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	OFBDSETUPStoreHandle
//
// Description:	OFBD SETUP Store Handle
//
// Input:
//      IN OUT OFBD_HDR *pOFBDHdr
// Output:
//      EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
OFBDSETUPStoreHandle(
    IN OUT OFBD_HDR *pOFBDHdr)
{
    EFI_STATUS Status = EFI_SUCCESS;

#if OEM_SETUP_SAMPLE_TEST || OEM_DMI_SAMPLE_TEST
    OFBD_TC_56_SETUP_STRUCT *SETUPStructPtr;     
	SETUPStructPtr = (OFBD_TC_56_SETUP_STRUCT *)((UINT8 *)pOFBDHdr + pOFBDHdr->OFBD_HDR_SIZE + sizeof(OFBD_EXT_HDR)); 

    //OEM add ...
    
	if (!EFI_ERROR(Status))
		SETUPStructPtr->dbRetSts =  OFBD_TC_SETUP_OK;
	else
    	SETUPStructPtr->dbRetSts =  OFBD_TC_SETUP_STORE_ERROR;
#endif

    return(Status);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	OFBDSETUPRestoreHandle
//
// Description:	OFBD SETUP Restore Handle
//
// Input:
//      IN OUT OFBD_HDR *pOFBDHdr
// Output:
//      EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
OFBDSETUPRestoreHandle(
    IN OUT OFBD_HDR *pOFBDHdr)
{
    EFI_STATUS Status = EFI_SUCCESS;

#if OEM_SETUP_SAMPLE_TEST
    OFBD_TC_56_SETUP_STRUCT *SETUPStructPtr;     
	SETUPStructPtr = (OFBD_TC_56_SETUP_STRUCT *)((UINT8 *)pOFBDHdr + pOFBDHdr->OFBD_HDR_SIZE + sizeof(OFBD_EXT_HDR)); 

    //OEM add ...

    if (!EFI_ERROR(Status))
		SETUPStructPtr->dbRetSts =  OFBD_TC_SETUP_OK;
	else
    	SETUPStructPtr->dbRetSts =  OFBD_TC_SETUP_RESTORE_ERROR;
#endif

    return(Status);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	OFBDDMIStoreHandle
//
// Description:	OFBD DMI Data Store Handle
//
// Input:
//      IN OUT OFBD_HDR *pOFBDHdr
// Output:
//      EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
OFBDDMIStoreHandle(
    IN OUT OFBD_HDR *pOFBDHdr)
{
    EFI_STATUS Status = EFI_SUCCESS;

#if OEM_DMI_SAMPLE_TEST
    OFBD_TC_56_SETUP_STRUCT *SETUPStructPtr;     
	SETUPStructPtr = (OFBD_TC_56_SETUP_STRUCT *)((UINT8 *)pOFBDHdr + pOFBDHdr->OFBD_HDR_SIZE + sizeof(OFBD_EXT_HDR)); 

    // OEM add ...
    // Store the DMI data
// EIP 37169 ->
#if (SMBIOS_DMIEDIT_DATA_LOC == 2) && (SMBIOS_PRESERVE_NVRAM != 1)
    PreserveDmiEditData ();
#endif
// <- EIP 37169
    
	if (!EFI_ERROR(Status))
		SETUPStructPtr->dbRetSts =  OFBD_TC_SETUP_OK;
	else
    	SETUPStructPtr->dbRetSts =  OFBD_TC_DMI_STORE_ERROR;
#endif

    return(Status);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	OFBDDMIRestoreHandle
//
// Description:	OFBD DMI Data Restore Handle
//
// Input:
//      IN OUT OFBD_HDR *pOFBDHdr
// Output:
//      EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
OFBDDMIRestoreHandle(
    IN OUT OFBD_HDR *pOFBDHdr)
{
    EFI_STATUS Status = EFI_SUCCESS;

#if OEM_DMI_SAMPLE_TEST
    OFBD_TC_56_SETUP_STRUCT *SETUPStructPtr;     
	SETUPStructPtr = (OFBD_TC_56_SETUP_STRUCT *)((UINT8 *)pOFBDHdr + pOFBDHdr->OFBD_HDR_SIZE + sizeof(OFBD_EXT_HDR)); 

    // OEM add ...
    // Restore the DMI data
// EIP 37169 ->
#if (SMBIOS_DMIEDIT_DATA_LOC == 2) && (SMBIOS_PRESERVE_NVRAM != 1)
    RestoreDmiEditData ();
#endif
// <- EIP 37169

    if (!EFI_ERROR(Status))
		SETUPStructPtr->dbRetSts =  OFBD_TC_SETUP_OK;
	else
    	SETUPStructPtr->dbRetSts =  OFBD_TC_DMI_RESTORE_ERROR;
#endif

    return(Status);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	OEMSETUPEntry
//
// Description:	OFBD NVRAM/SETUP Store/Restore Entry point
//
// Input:
//      IN VOID             *Buffer
//      IN OUT UINT8        *pOFBDDataHandled
// Output:
//      VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID OEMSETUPEntry (
    IN VOID             *Buffer,
    IN OUT UINT8        *pOFBDDataHandled )
{
    OFBD_HDR *pOFBDHdr;
    OFBD_EXT_HDR *pOFBDExtHdr; 
    VOID *pOFBDTblEnd;
    OFBD_TC_56_SETUP_STRUCT *SETUPStructPtr;    

    if(*pOFBDDataHandled == 0)
    {
        pOFBDHdr = (OFBD_HDR *)Buffer;
        pOFBDExtHdr = (OFBD_EXT_HDR *)((UINT8 *)Buffer + (pOFBDHdr->OFBD_HDR_SIZE));
        SETUPStructPtr = (OFBD_TC_56_SETUP_STRUCT *)((UINT8 *)pOFBDExtHdr + sizeof(OFBD_EXT_HDR)); 
        pOFBDTblEnd = (VOID *)((UINT8 *)Buffer + (pOFBDHdr->OFBD_Size));    
        
        if(pOFBDHdr->OFBD_FS & OFBD_FS_SETUP)
        {   
            //Check Type Code ID
            if(pOFBDExtHdr->TypeCodeID == OFBD_EXT_TC_SETUP)
            {  
                //IoWrite32(0x300, *(UINT32 *)((UINT8 *)pOFBDTblEnd -4)); //debug
				if(SETUPStructPtr->dbGetSts == OFBD_TC_SETUP_SUPPORT)
				{
					if(OFBDSETUPSupportHandle(pOFBDHdr) == EFI_SUCCESS)
					{
						//OEM SETUP SUPPORT Handled.
                    	*pOFBDDataHandled = 0xFF;      
                    	return;
                	}
				}
				else if(SETUPStructPtr->dbGetSts == OFBD_TC_SETUP_STORE)
				{
					if(OFBDSETUPStoreHandle(pOFBDHdr) == EFI_SUCCESS)
					{
						//OEM SETUP STORE Handled.
                    	*pOFBDDataHandled = 0xFF;      
                    	return;
                	}
				}
                else if(SETUPStructPtr->dbGetSts == OFBD_TC_SETUP_RESTORE)
				{
					if(OFBDSETUPRestoreHandle(pOFBDHdr) == EFI_SUCCESS)
					{
						//OEM SETUP RESTORE Handled.
                    	*pOFBDDataHandled = 0xFF;      
                    	return;
                	}
				}
				else if(SETUPStructPtr->dbGetSts == OFBD_TC_DMI_STORE)
				{
					if(OFBDDMIStoreHandle(pOFBDHdr) == EFI_SUCCESS)
					{
						//OEM DMI STORE Handled.
                    	*pOFBDDataHandled = 0xFF;      
                    	return;
                	}
				}
                else if(SETUPStructPtr->dbGetSts == OFBD_TC_DMI_RESTORE)
				{
					if(OFBDDMIRestoreHandle(pOFBDHdr) == EFI_SUCCESS)
					{
						//OEM DMI RESTORE Handled.
                    	*pOFBDDataHandled = 0xFF;      
                    	return;
                	}
				}
            } 
            //Error occured
            *pOFBDDataHandled = 0xFE;          
            return;
        }  
    }

    return;
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
