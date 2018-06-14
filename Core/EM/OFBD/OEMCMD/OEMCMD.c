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
// $Header: /Alaska/SOURCE/Modules/OFBD/OEMCMD/OEMCMD.c 4     4/12/11 10:28p Terrylin $
//
// $Revision: 4 $
//
// $Date: 4/12/11 10:28p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/OFBD/OEMCMD/OEMCMD.c $
// 
// 4     4/12/11 10:28p Terrylin
// Fix sample code is wrong problem.
// 
// 3     3/16/11 10:36p Terrylin
// [TAG]  		EIP51285
// [Category]  	Improvement
// [Description]  	Fill the description for user more clearly.
// [Files]  		OEMCMD.mak
// OEMCMD.h
// OEMCMD.c
// 
// 2     1/26/11 3:52a Terrylin
// [Category]  	Improvement
// [Description]  	Add /CMD: command description and its sample code.
// 
// 1     5/06/10 2:23a Lawrencechang
// Initial check-in.
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	OEMCMD.c
//
// Description: 
//By OEMCMD module, OEM engineers define customized commands to extend AFU functions. AFU sends OEM defined commands
// to BIOS if user issued /oemcmd:<command>. Then BIOS reacts by these customized commands.
//
//<AMI_FHDR_END>
//**********************************************************************
#include "Efi.h"
#include "token.h"
#include <AmiLib.h>
#include <AmiDxeLib.h>
#include "OEMCMD.h"
#include "..\OFBD.h"

//#define CONVERT_TO_STRING(a) #a
#define STR(a) CONVERT_TO_STRING(a)

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	OFBDOEMCMDHandle
//
// Description:	OFBD OEM CMD Handle
//
// Input:
//      IN OUT OFBD_HDR *pOFBDHdr
// Output:
//      EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
OFBDOEMCMDHandle( 
    IN OUT OFBD_HDR *pOFBDHdr)
{
    EFI_STATUS Status = EFI_SUCCESS;

#if OEM_CMD_CHECKING_SAMPLE_TEST

	UINT8 *pOFBDTblEnd;
	UINT8 *pCMDBufferStr;
	UINT32 ddCMDLength = 0;
	char *DisOemBFStr = "Sample Message: OEM CMD Before Flash Run is OK !!";
	char *DisOemAFStr = "Sample Message: OEM CMD After Flash Run is OK !!";
	char *DisOemBEStr = "Sample Message: OEM CMD Before End Run is OK !!";
	char *DisOemSFStr = "Sample Message: OEM CMD Start to Flash Run is OK !!";
	
	OFBD_TC_57_OEM_CMD_STRUCT *OCStructPtr;   
	
	pOFBDTblEnd = (UINT8 *)((UINT8 *)pOFBDHdr + (pOFBDHdr->OFBD_Size));
	OCStructPtr = (OFBD_TC_57_OEM_CMD_STRUCT *)((UINT8 *)pOFBDHdr + pOFBDHdr->OFBD_HDR_SIZE + sizeof(OFBD_EXT_HDR)); 
	
	//
	// OEM add start here >>>+
	//
	
	//--------------------------------------------------------------------------------------
	//
	// OEM Notice : 
	//
	// case 1:
	// 		OCStructPtr->ddCMD is parse by AFU, according "/OEMCMD:x" to given Hex value.
	//
	// case 2:
	// 		OCStructPtr->ddCMD is "/CMD:{xxx}" command string offset.
	// 		OCStructPtr->ddReserve is command string length.
	//
	//--------------------------------------------------------------------------------------

	// IoWrite32(0x1080, OCStructPtr->ddCMD); //debug
	
	//------------------------------------------------------------------------------------------
	// Case 1
	//------------------------------------------------------------------------------------------
	
	// 01. Before Flash
	if (OCStructPtr->dwFlaSts == OFBD_TC_OEM_CMD_BF) {	 
		//--------------------------------------------------------------------------------------
		//
		// OEM Command sample definition:
		//
		//--------------------------------------------------------------------------------------
		// Bit 0  : Restart
		// Bit 1  : Shutdown
		// Bit 2  : Wait
		// ...
		// Bit 5 : No Check AC adapter
		// Bit 6 : OEM function 01
		// Bit 7 : OEM function 02
		// ...
		// 
		// 01. /OEMCMD:1	, OCStructPtr->ddCMD = 0x1  (Hex). ("Restart")
		// 02. /OEMCMD:5	, OCStructPtr->ddCMD = 0x5  (Hex). ("Restart" + "Wait")
		// 03. /OEMCMD:11	, OCStructPtr->ddCMD = 0x11 (Hex). ("No Check AC adapter" + "Restart")
		// 04. /OEMCMD:A2	, OCStructPtr->ddCMD = 0xA2 (Hex). ("OEM function 02" + "No Check AC adapter" + "Shutdown")
		// 05. /OEMCMD:123	, OCStructPtr->ddCMD = 0x123(Hex). ...
		// 06. /OEMCMD:AABB	, OCStructPtr->ddCMD = 0xAABB(Hex). ...
		//--------------------------------------------------------------------------------------
		
		//
		// OCStructPtr->ddCMD
		// 
		
		// Check Bit 0
		if (OCStructPtr->ddCMD & 0x1) {
			// Restart code
		}
		
		// Check Bit 1
		if (OCStructPtr->ddCMD >> 1 & 0x1) {
			// Shutdown code
		}
		
		// Check Bit 2
		if (OCStructPtr->ddCMD >> 2 & 0x1) {
			// Wait code
		}
		
		// Check Bit 5
		if (OCStructPtr->ddCMD >> 5 & 0x1) {
			// No Check AC adapter code
		}
		
		// Check Bit 7
		if (OCStructPtr->ddCMD >> 7 & 0x1) {
			// OEM function 02 code
		}
		
		// << debug >>	
		// set oem string flag for AFU to know
	    pOFBDHdr->OFBD_RS |= OFBD_RS_DIS_OEMSTR;
	    // copy the oem string ptr for AFU
	    Strcpy((char *)pOFBDTblEnd, DisOemBFStr);
	    
	    
	// 02. After Flash
	} else if (OCStructPtr->dwFlaSts == OFBD_TC_OEM_CMD_AF) {
		
		// 
		// Display OEM String Usage +>>>
		// 
		
		// set oem string flag for AFU to know
	    pOFBDHdr->OFBD_RS |= OFBD_RS_DIS_OEMSTR;
	    // copy the oem string ptr for AFU
	    Strcpy((char *)pOFBDTblEnd, DisOemAFStr);
	    
	    //
	    // Display OEM String Usage <<<+
	    //
	    
	// 03. Before End
	} else if (OCStructPtr->dwFlaSts == OFBD_TC_OEM_CMD_BE) {
	
		// OEM add ...
		
		// << debug >>
		// set oem string flag for AFU to know
	    pOFBDHdr->OFBD_RS |= OFBD_RS_DIS_OEMSTR;
	    // copy the oem string ptr for AFU
	    Strcpy((char *)pOFBDTblEnd, DisOemBEStr);
	    
	} else if (OCStructPtr->dwFlaSts == OFBD_TC_OEM_CMD_SF) {
                // << debug >>	
		// set oem string flag for AFU to know
	    pOFBDHdr->OFBD_RS |= OFBD_RS_DIS_OEMSTR;
	    // copy the oem string ptr for AFU
	    Strcpy((char *)pOFBDTblEnd, DisOemSFStr);
	    
    }
			   
	//------------------------------------------------------------------------------------------
	// Case 2
	//------------------------------------------------------------------------------------------
	// 05. Before Flash
	if (OCStructPtr->dwFlaSts == OFBD_TC_OEM_CMD_BUF) {	 
		//--------------------------------------------------------------------------------------
		//
		// OEM Command sample definition:
		//
		//--------------------------------------------------------------------------------------
		// 
		// 01. /CMD:{123}	    , OCStructPtr->ddCMD = 0x400(Hex), OCStructPtr->ddReserve = 3 (Bytes)
		// 02. /CMD:{Reset}	    , OCStructPtr->ddCMD = 0x400(Hex), OCStructPtr->ddReserve = 5 (Bytes)
		// 03. /CMD:{NoVer}     , OCStructPtr->ddCMD = 0x400(Hex), OCStructPtr->ddReserve = 5 (Bytes)
		// 04. /CMD:{NoAC}	    , OCStructPtr->ddCMD = 0x400(Hex), OCStructPtr->ddReserve = 4 (Bytes)
		// 05. /CMD:{Battery}	, OCStructPtr->ddCMD = 0x400(Hex), OCStructPtr->ddReserve = 7 (Bytes)
		// 06. /CMD:{NoAc Battery NoVer}	, OCStructPtr->ddCMD = 0x400(Hex), OCStructPtr->ddReserve = 18 (Bytes)
		//--------------------------------------------------------------------------------------
		
		//
		// Get Command String Offset
		// 
		
		pCMDBufferStr = (UINT8 *)((UINT8 *)pOFBDHdr + (OCStructPtr->ddCMD));
		
		
		//
		// Get Command String Length
		//
		
		ddCMDLength = OCStructPtr->ddReserve;
		
		// << debug >>	
		// set oem string flag for AFU to know
	    pOFBDHdr->OFBD_RS |= OFBD_RS_DIS_OEMSTR;
	    // copy the oem string ptr for AFU
	    Strcpy((char *)pOFBDTblEnd, DisOemBFStr);
	    
	    
	// 06. After Flash
	} else if (OCStructPtr->dwFlaSts == OFBD_TC_OEM_CMD_BUF_AF) {
		
		// 
		// Display OEM String Usage +>>>
		// 
		
		// set oem string flag for AFU to know
	    pOFBDHdr->OFBD_RS |= OFBD_RS_DIS_OEMSTR;
	    // copy the oem string ptr for AFU
	    Strcpy((char *)pOFBDTblEnd, DisOemAFStr);
	    
	    //
	    // Display OEM String Usage <<<+
	    //
	    
	// 07. Before End
	} else if (OCStructPtr->dwFlaSts == OFBD_TC_OEM_CMD_BUF_BE) {
	
		// OEM add ...
		
		// << debug >>
		// set oem string flag for AFU to know
	    pOFBDHdr->OFBD_RS |= OFBD_RS_DIS_OEMSTR;
	    // copy the oem string ptr for AFU
	    Strcpy((char *)pOFBDTblEnd, DisOemBEStr);
	    
	} else if (OCStructPtr->dwFlaSts == OFBD_TC_OEM_CMD_BUF_SF) {
                // << debug >>	
		// set oem string flag for AFU to know
	    pOFBDHdr->OFBD_RS |= OFBD_RS_DIS_OEMSTR;
	    // copy the oem string ptr for AFU
	    Strcpy((char *)pOFBDTblEnd, DisOemSFStr);
	    
    }
    
	//
	// OEM add start here <<<+
	//
		
	// Setting Return Status is '1' for AFU to know OFBD has supported OEM CMD module.
	OCStructPtr->dwRetSts = 1;

#endif

    return(Status);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	OEMCMDEntry
//
// Description:	OFBD OEM CMD CHECKING Entry Point
//
// Input:
//      IN VOID             *Buffer
//      IN OUT UINT8        *pOFBDDataHandled
// Output:
//      VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID OEMCMDEntry (
    IN VOID             *Buffer,
    IN OUT UINT8        *pOFBDDataHandled )
{
	OFBD_HDR *pOFBDHdr;
	OFBD_EXT_HDR *pOFBDExtHdr; 
	VOID *pOFBDTblEnd;
	OFBD_TC_57_OEM_CMD_STRUCT *OCStructPtr;    

	if(*pOFBDDataHandled == 0)
	{
		pOFBDHdr = (OFBD_HDR *)Buffer;
		pOFBDExtHdr = (OFBD_EXT_HDR *)((UINT8 *)Buffer + (pOFBDHdr->OFBD_HDR_SIZE));
		OCStructPtr = (OFBD_TC_57_OEM_CMD_STRUCT *)((UINT8 *)pOFBDExtHdr + sizeof(OFBD_EXT_HDR)); 
		pOFBDTblEnd = (VOID *)((UINT8 *)Buffer + (pOFBDHdr->OFBD_Size));    
		
		if(pOFBDHdr->OFBD_FS & OFBD_FS_OEM_CMD)
		{   
			//Check Type Code ID
			if(pOFBDExtHdr->TypeCodeID == OFBD_EXT_TC_OEM_CMD)
			{  
				if(OFBDOEMCMDHandle(pOFBDHdr) == EFI_SUCCESS)
				{
					//OEM CMD CHECKING Data Handled.
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
