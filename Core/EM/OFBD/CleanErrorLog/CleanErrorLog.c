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
// $Header: /Alaska/SOURCE/Modules/OFBD/CleanErrorLog/CleanErrorLog.c 3     10/06/11 1:28a Terrylin $
//
// $Revision: 3 $
//
// $Date: 10/06/11 1:28a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/OFBD/CleanErrorLog/CleanErrorLog.c $
// 
// 3     10/06/11 1:28a Terrylin
// Fix the build error, when Gpnv Error Logging module didn't enable.
// 
// 2     3/16/11 10:32p Terrylin
// [TAG]  		EIP51285
// [Category]  	Improvement
// [Description]  	Fill the description for user more clearly.
// [Files]  		CleanErrorLog.mak
// CleanErrorLog.h
// CleanErrorLog.c
// 
// 1     1/17/11 3:56a Terrylin
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	CleanErrorLog.c
//
// Description:
// This function is used to Clean Error Log. For example,AFU will call this function to clean error log when
// /CLNEVNLOG is issued.
//
//<AMI_FHDR_END>
//**********************************************************************
#include "Efi.h"
#include <Protocol\SmiFlash.h>
#include <AmiLib.h>
#include <AmiDxeLib.h>
#include "CleanErrorLog.h"
#include "..\OFBD.h"

//#define CONVERT_TO_STRING(a) #a
#define STR(a) CONVERT_TO_STRING(a)

EFI_GUID gEfiSmiFlashProtocolGuid = EFI_SMI_FLASH_GUID;
EFI_SMI_FLASH_PROTOCOL *mSmiFlash = NULL;

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	CleanErrorLogCallback
//
// Description:	Locate SmiFlash protocol callback
//
// Input:
//      IN EFI_EVENT    Event
//      IN VOID         *Context
//
// Output:
//      VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID CleanErrorLogCallback(
    IN EFI_EVENT Event,
    IN VOID *Context
)
{
    EFI_GUID       gEfiSmiFlashProtocolGuid = EFI_SMI_FLASH_GUID;

    pBS->LocateProtocol (&gEfiSmiFlashProtocolGuid, NULL, &mSmiFlash);
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	CleanErrorLogInSmm
//
// Description:	OFBD Clear event log InSmm Function
//
// Input:
//      VOID
//
// Output:
//      VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID CleanErrorLogInSmm(VOID)
{
    EFI_STATUS     Status;
    EFI_GUID       gEfiSmiFlashProtocolGuid = EFI_SMI_FLASH_GUID;

    Status = pBS->LocateProtocol (&gEfiSmiFlashProtocolGuid, NULL, &mSmiFlash);
    if (EFI_ERROR(Status)){
        EFI_EVENT   SmiFlashCallbackEvt;
        VOID        *Reg;
        RegisterProtocolCallback(
             &gEfiSmiFlashProtocolGuid, CleanErrorLogCallback,
             NULL,&SmiFlashCallbackEvt, &Reg
        );
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	OFBDCleanErrorLogHandle
//
// Description:	OFBD Clean Gpnv Error Log Handle
//
// Input:
//      IN OUT OFBD_HDR *pOFBDHdr
// Output:
//      EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
OFBDCleanErrorLogHandle( 
    IN OUT OFBD_HDR *pOFBDHdr)
{
    EFI_STATUS Status = EFI_SUCCESS;

#if CLEAN_GPNV_ERROR_LOG_SAMPLE_TEST

	UINT8 *pOFBDTblEnd;
	OFBD_TC_58_CEL_STRUCT *CELStructPtr;
    #if defined(FV_ERROR_LOGGING_BASE) && defined(FV_ERROR_LOGGING_SIZE)
	FUNC_BLOCK FuncBlock;
	UINT8      pType1Header[16];
    #endif
	
	pOFBDTblEnd = (UINT8 *)((UINT8 *)pOFBDHdr + (pOFBDHdr->OFBD_Size));
	CELStructPtr = (OFBD_TC_58_CEL_STRUCT *)((UINT8 *)pOFBDHdr + pOFBDHdr->OFBD_HDR_SIZE + sizeof(OFBD_EXT_HDR)); 
	
    // Is need to Clean Gpnv Error Log
	if (CELStructPtr->dwFunSts == OFBD_TC_CEL_FUNC_REQ)
	{
		// Check Gpnv Error Logging module whether support or not
    #if !defined(FV_ERROR_LOGGING_BASE) || !defined(FV_ERROR_LOGGING_SIZE)
		CELStructPtr->dwRetSts = OFBD_TC_CEL_BIOS_NOT_SUPPORT;
    #else
		//
		// Reference from "ErrorLogging/SmiGpnv/SmiGpnv.c" file code +>>>
		//
		// SS: Alaska;$/Alaska/SOURCE/Modules/ErrorLogging;
		//
		// Label 4.6.3.6_GPNV_ERRLOG_2.1a
		//    
		// Enable Flash Write.    
        Status = mSmiFlash->EnableFlashWrite(&FuncBlock);
        // Read flash to preserve EFI_GPNV_ERROR_HEADER_TYPE1 header.
        FuncBlock.BufAddr = (UINTN)&pType1Header;
        FuncBlock.BlockSize = 0x10; // EFI_GPNV_ERROR_HEADER_TYPE1
        FuncBlock.BlockAddr = ((UINT32)FV_ERROR_LOGGING_BASE & \
                               (FLASH_SIZE - 1)); //0 starts at 0xfff0_0000
        FuncBlock.ErrorCode = 0;
        Status = mSmiFlash->ReadFlash(&FuncBlock);
        // Erase Error Logging GPNV.
        FuncBlock.BlockSize = FV_ERROR_LOGGING_SIZE; //max size 0xffff
        FuncBlock.BufAddr = 0;
        Status = mSmiFlash->EraseFlash(&FuncBlock); // Write Flash
        // Restore EFI_GPNV_ERROR_HEADER_TYPE1 header.
        FuncBlock.BlockSize = 0x10; //EFI_GPNV_ERROR_HEADER_TYPE1
        FuncBlock.BufAddr = (UINTN)&pType1Header;
        Status = mSmiFlash->WriteFlash(&FuncBlock); // Write Flash
        // Disable Flash Write.    
        Status = mSmiFlash->DisableFlashWrite(&FuncBlock);
        //
        // <<<+
        //
        if (EFI_ERROR (Status))
            CELStructPtr->dwRetSts = OFBD_TC_CEL_ERROR;
        else
            CELStructPtr->dwRetSts = OFBD_TC_CEL_OK;
    #endif
	}
		
#endif

    return(Status);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	CleanErrorLogEntry
//
// Description:	OFBD Clean Gpnv Error Log Entry Point
//
// Input:
//      IN VOID             *Buffer
//      IN OUT UINT8        *pOFBDDataHandled
// Output:
//      VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID CleanErrorLogEntry (
    IN VOID             *Buffer,
    IN OUT UINT8        *pOFBDDataHandled )
{
	OFBD_HDR *pOFBDHdr;
	OFBD_EXT_HDR *pOFBDExtHdr; 
	VOID *pOFBDTblEnd;
	OFBD_TC_58_CEL_STRUCT *CELStructPtr;  

	if(*pOFBDDataHandled == 0)
	{
		pOFBDHdr = (OFBD_HDR *)Buffer;
		pOFBDExtHdr = (OFBD_EXT_HDR *)((UINT8 *)Buffer + (pOFBDHdr->OFBD_HDR_SIZE));
		CELStructPtr = (OFBD_TC_58_CEL_STRUCT *)((UINT8 *)pOFBDExtHdr + sizeof(OFBD_EXT_HDR)); 
		pOFBDTblEnd = (VOID *)((UINT8 *)Buffer + (pOFBDHdr->OFBD_Size));    
		
		if(pOFBDHdr->OFBD_FS & OFBD_FS_ERR_LOG)
		{   
			//Check Type Code ID
			if(pOFBDExtHdr->TypeCodeID == OFBD_EXT_TC_CLN_ERR_LOG)
			{  
				if(OFBDCleanErrorLogHandle(pOFBDHdr) == EFI_SUCCESS)
				{
					//OEM Default Command Configuration Handled.
					*pOFBDDataHandled = 0xFF;      
					return;
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
