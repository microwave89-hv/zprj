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
// $Header: /Alaska/SOURCE/Modules/OFBD/OEMOAHandle/OEMOAHandle.c 1     10/24/11 3:03a Terrylin $
//
// $Revision: 1 $
//
// $Date: 10/24/11 3:03a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/OFBD/OEMOAHandle/OEMOAHandle.c $
// 
// 1     10/24/11 3:03a Terrylin
// Add for EIP 66385
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	OemOAHandle.c
//
// Description:
//
// This function is used for OEM can receive the OA data, and then decide what to do.
//
//<AMI_FHDR_END>
//**********************************************************************
#include "Efi.h"
#include <Protocol\SmiFlash.h>
#include <AmiLib.h>
#include <AmiDxeLib.h>
#include "OemOAHandle.h"
#include "..\OFBD.h"

//#define CONVERT_TO_STRING(a) #a
#define STR(a) CONVERT_TO_STRING(a)

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	OFBDOemOADataHandle
//
// Description:	OFBD Oem OA Data Handle
//
// Input:
//      IN OUT OFBD_HDR *pOFBDHdr
// Output:
//      EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
OFBDOemOADataHandle( 
    IN OUT OFBD_HDR *pOFBDHdr)
{
    EFI_STATUS Status = EFI_SUCCESS;

#if OEM_OA_DATA_HANDLE_SAMPLE_TEST

    char *TestOemOAStr = " [DBG] OA function is called !!";
    
    UINT8 *pOFBDTblEnd;
    OFBD_TC_5A_OA_HANDLE_STRUCT *OAStructPtr;
    
    pOFBDTblEnd = (UINT8 *)((UINT8 *)pOFBDHdr + (pOFBDHdr->OFBD_Size));
    OAStructPtr = (OFBD_TC_5A_OA_HANDLE_STRUCT *)((UINT8 *)pOFBDHdr + pOFBDHdr->OFBD_HDR_SIZE + sizeof(OFBD_EXT_HDR)); 
    
    //
    // OA Structure Description:
    //
    /*
    UINT8 	dbOASts;		// Bit 0: Notification BIOS, utility is now ready to update the OA data.                                - OFBD_TC_OA_UPDATE_NOTIFY
                            // Bit 1~7: Reserved
                            
    UINT8 	dbErrorID;		// 0~255 : Filled by O.E.M.
    
    UINT16 	dwRetSts;		// Bit 0: OA data is invalid, tell the utility stop the flash procedure                                 - OFBD_RS_OA_DATA_IS_INVALID
                            // Bit 1: OA data has been modified, tell the utility use the new data to update                        - OFBD_RS_OA_DATA_IS_MODIFIED
                            // Bit 2: BIOS has updated the OA, so tell the utility doesn't to update                                - OFBD_RS_OA_UPDATE_SKIPPED
                            // Bit 3: BIOS doesn't allow the OA update, tell the utility stop the flash procedure                   - OFBD_RS_OA_UPDATE_DECLINED
                            // Bit 4~14: Reserved
                            // Bit 15: Use dbErrorID field for utility return OEM specific error code, when this Bit is set to 1.   - OFBD_RS_OA_USE_OEM_ERROR_ID
	UINT32  ddOABlockAddr;  // OA Block Address of BIOS ROM (For NCB mode to use)
    UINT64  ddOADataBuffer; // OA Data Buffer
    UINT32  dwOADataSize;   // OA Data Buffer Size
    */
    
    //
    // Please add your code here +>>>
    //
    if (OAStructPtr->dbOASts == OFBD_TC_OA_UPDATE_NOTIFY)
    {
        //
        //  Please set the dwRetSts for utility to know the process is success or fail
        //
            
        //
        //  Case 1: OA Data is invalid
        //
        
        //      OAStructPtr->dwRetSts = OFBD_RS_OA_DATA_IS_INVALID;
        

        //
        //  Case 2: OA Data has been modified, tell the utility use the new data to update
        //
        
        //      OAStructPtr->dwRetSts = OFBD_RS_OA_DATA_IS_MODIFIED;
        
        
        //
        //  Case 3: BIOS has updated the OA, so tell the utility doesn't to update
        //
        
        //      OAStructPtr->dwRetSts = OFBD_RS_OA_UPDATE_SKIPPED;
        
        
        //
        //  Case 4: BIOS doesn't allow the OA update, tell the utility stop the flash procedure
        //
        
        //      OAStructPtr->dwRetSts = OFBD_RS_OA_UPDATE_DECLINED;
                
        
        //
        //  Case X: OEM want to use their error code definition for /A update command status
        //
        
        
        //      Step 1: Set Bit 15 to 1
        //
        //      OAStructPtr->dwRetSts = OFBD_RS_OA_USE_OEM_ERROR_ID;
        //
        //      Step 2: Use dbErrorID field for utility return OEM specific error code
        //
        //      OAStructPtr->dbErrorID = 0~255;
        
        
        //   
        //  Tell the utility to show the OEM message, if needed. +>>>
        //
        pOFBDHdr->OFBD_RS |= OFBD_RS_DIS_OEMSTR;
        Strcpy((char *)pOFBDTblEnd, TestOemOAStr);
        //
        // <<<+
        //
    
    }    
    
    //
    // Please add your code here <<<+
    //
    
#endif  // #ifdef OEM_OA_DATA_HANDLE_SAMPLE_TEST
    
    return(Status);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	OemOAHandleEntry
//
// Description:	OFBD Oem OA Data Handle Entry Point
//
// Input:
//      IN VOID             *Buffer
//      IN OUT UINT8        *pOFBDDataHandled
// Output:
//      VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID OemOAHandleEntry (
    IN VOID             *Buffer,
    IN OUT UINT8        *pOFBDDataHandled )
{
	OFBD_HDR *pOFBDHdr;
	OFBD_EXT_HDR *pOFBDExtHdr; 
	VOID *pOFBDTblEnd;
	OFBD_TC_5A_OA_HANDLE_STRUCT *OAStructPtr;  

	if(*pOFBDDataHandled == 0)
	{
		pOFBDHdr = (OFBD_HDR *)Buffer;
		pOFBDExtHdr = (OFBD_EXT_HDR *)((UINT8 *)Buffer + (pOFBDHdr->OFBD_HDR_SIZE));
		OAStructPtr = (OFBD_TC_5A_OA_HANDLE_STRUCT *)((UINT8 *)pOFBDExtHdr + sizeof(OFBD_EXT_HDR)); 
		pOFBDTblEnd = (VOID *)((UINT8 *)Buffer + (pOFBDHdr->OFBD_Size));    
		
		if(pOFBDHdr->OFBD_FS & OFBD_FS_OA)
		{   
			//Check Type Code ID
			if(pOFBDExtHdr->TypeCodeID == OFBD_EXT_TC_OA_HANDLE)
			{  
				if(OFBDOemOADataHandle(pOFBDHdr) == EFI_SUCCESS)
				{
					//Oem OA Data Handled.
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
