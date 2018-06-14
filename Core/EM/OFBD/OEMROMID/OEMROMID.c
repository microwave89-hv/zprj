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
// $Header: /Alaska/SOURCE/Modules/OFBD/OEMROMID/OEMROMID.c 2     3/16/11 10:35p Terrylin $
//
// $Revision: 2 $
//
// $Date: 3/16/11 10:35p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/OFBD/OEMROMID/OEMROMID.c $
// 
// 2     3/16/11 10:35p Terrylin
// [TAG]  		EIP51285
// [Category]  	Improvement
// [Description]  	Fill the description for user more clearly.
// [Files]  		OEMROMID.mak
// OEMROMID.h
// OEMROMID.c
// 
// 1     4/13/09 5:46a Lawrencechang
// Initial check-in.
// 
// 1     3/25/05 5:37p Markw
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	OEMROMID.c
//
// Description: 
// OEM Rom ID Check protocol is for Flash utility to send customer defined specific ROM ID for BIOS to ID version
// checking uses. 
//
// BIOS should provide inserted ROM file's specific ROM ID location and then check it, when ID is given by Flash
// Utility after OFBD_EXT_TBL_END.
//
// Moreover, Flash utility will have corresponding action, either stop flashing BIOS.
//<AMI_FHDR_END>
//**********************************************************************
#include "Efi.h"
#include "token.h"
#include <AmiLib.h>
#include <AmiDxeLib.h>
#include "OEMROMID.h"
#include "..\OFBD.h"


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	OFBDORIGetHandle
//
// Description:	OFBD OEM ROM ID Get Handle
//
// Input:
//      IN OUT OFBD_HDR *pOFBDHdr
// Output:
//      EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
OFBDORIGetHandle( 
    IN OUT OFBD_HDR *pOFBDHdr)
{
    EFI_STATUS Status = EFI_SUCCESS;

#if OEM_ROM_ID_SAMPLE_TEST
	OFBD_TC_53_ORI_STRUCT *ORIStructPtr;   
	ORIStructPtr = (OFBD_TC_53_ORI_STRUCT *)((UINT8 *)pOFBDHdr + pOFBDHdr->OFBD_HDR_SIZE + sizeof(OFBD_EXT_HDR)); 
	ORIStructPtr->dwRetSts = OFBD_TC_ORI_REQ + OFBD_TC_ORI_ROM;
	ORIStructPtr->ddStartAddrLow = OEM_ROM_ID_Address;
	ORIStructPtr->ddSize = OEM_ROM_ID_SIZE;
#endif

    return(Status);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	OFBDORICheckHandle
//
// Description:	OFBD OEM ROM ID Check Handle
//
// Input:
//      IN OUT OFBD_HDR *pOFBDHdr
// Output:
//      EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
OFBDORICheckHandle(
    IN OUT OFBD_HDR *pOFBDHdr)
{
    EFI_STATUS Status = EFI_SUCCESS;

#if OEM_ROM_ID_SAMPLE_TEST
	UINT8 *pOFBDTblEnd;
    char *DisOemStrOK = "Sample Message: OEM ROM ID Check OK";
    char *DisOemStrFail = "Sample Message: OEM ROM ID Check Fail";
    UINT32 OIDLengthMajMin = 0x0c; // hard coded 

	pOFBDTblEnd = (UINT8 *)((UINT8 *)pOFBDHdr + (pOFBDHdr->OFBD_Size));
	if(*(UINT32 *)(pOFBDTblEnd + OIDLengthMajMin) >= OEM_ROM_ID_SUB)
	{
		pOFBDHdr->OFBD_RS |= OFBD_RS_DIS_OEMSTR;
		//pOFBDHdr->OFBD_RS |= 0;	//comparison passed and do nothing
		Strcpy((char *)pOFBDTblEnd, DisOemStrOK);
	}
	else
	{
		pOFBDHdr->OFBD_RS |= OFBD_RS_ERR_OUT + OFBD_RS_DIS_OEMSTR;
		//pOFBDHdr->OFBD_RS |= 0;	//comparison failed and do nothing
		Strcpy((char *)pOFBDTblEnd, DisOemStrFail);
	}
#endif

    return(Status);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	OFBDEntryPoint
//
// Description:	OFBD OEM ROMID CHECK Entry Point
//
// Input:
//      IN VOID             *Buffer
//      IN OUT UINT8        *pOFBDDataHandled
// Output:
//      VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID OEMROMIDEntry (
    IN VOID             *Buffer,
    IN OUT UINT8        *pOFBDDataHandled )
{
    OFBD_HDR *pOFBDHdr;
    OFBD_EXT_HDR *pOFBDExtHdr; 
    VOID *pOFBDTblEnd;
    OFBD_TC_53_ORI_STRUCT *ORIStructPtr;    

    if(*pOFBDDataHandled == 0)
    {
        pOFBDHdr = (OFBD_HDR *)Buffer;
        pOFBDExtHdr = (OFBD_EXT_HDR *)((UINT8 *)Buffer + (pOFBDHdr->OFBD_HDR_SIZE));
        ORIStructPtr = (OFBD_TC_53_ORI_STRUCT *)((UINT8 *)pOFBDExtHdr + sizeof(OFBD_EXT_HDR)); 
        pOFBDTblEnd = (VOID *)((UINT8 *)Buffer + (pOFBDHdr->OFBD_Size));    

        //TRACE((-1,"pOFBDHdr address is:%x ------\n",pOFBDHdr));
        //TRACE((-1,"pOFBDTblEnd address is:%x ------\n",*(UINT64 *)((UINT8 *)pOFBDTblEnd -sizeof(OFBD_END))));
        
        if(pOFBDHdr->OFBD_FS & OFBD_FS_ORI)
        {   
            //Check Type Code ID
            if(pOFBDExtHdr->TypeCodeID == OFBD_EXT_TC_ORI)
            {  
                //IoWrite32(0x300, *(UINT32 *)((UINT8 *)pOFBDTblEnd -4)); //debug
				if(ORIStructPtr->dwGetCkSts == OFBD_TC_ORI_GET)
				{
					if(OFBDORIGetHandle(pOFBDHdr) == EFI_SUCCESS)
					{
						//OEM ROM ID Data Handled.
                    	*pOFBDDataHandled = 0xFF;      
                    	return;
                	}
				}
				else if(ORIStructPtr->dwGetCkSts == OFBD_TC_ORI_CHECK)
				{
					if(OFBDORICheckHandle(pOFBDHdr) == EFI_SUCCESS)
					{
						//OEM ROM ID Data Handled.
                    	*pOFBDDataHandled = 0xFF;      
                    	return;
                	}
				}
                /*//Not OEM ROM ID Data.
                *pOFBDDataHandled = 0;          
                return;*/
            } 
            //else
           //{
                 //Error occured
                *pOFBDDataHandled = 0xFE;          
                return;
            //}
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
