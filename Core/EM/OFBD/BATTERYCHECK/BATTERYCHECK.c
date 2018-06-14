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
// $Header: /Alaska/SOURCE/Modules/OFBD/BATTERYCHECK/BATTERYCHECK.c 1     10/11/12 2:27a Terrylin $
//
// $Revision: 1 $
//
// $Date: 10/11/12 2:27a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/OFBD/BATTERYCHECK/BATTERYCHECK.c $
// 
// 1     10/11/12 2:27a Terrylin
// Initial check-in for OEM can control AC/Battery status check rule
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	BATTERYCHECK.c
//
// Description:
//
// This function is used for OEM can decided AFU flash behavior, when 
// AC/Battery is under warning status and can output the OEM String message 
// to the flash utility.
//
//
//<AMI_FHDR_END>
//**********************************************************************
#include "Efi.h"
#include <AmiLib.h>
#include <AmiDxeLib.h>
#include "BATTERYCHECK.h"
#include "..\OFBD.h"

//#define CONVERT_TO_STRING(a) #a
#define STR(a) CONVERT_TO_STRING(a)


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	OFBDBATTERYCHECK
//
// Description:	OFBD AC/Battery check
//
// Input:
//      IN OUT OFBD_HDR *pOFBDHdr
// Output:
//      EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
OFBDBatteryCheck( 
    IN OUT OFBD_HDR *pOFBDHdr)
{
    EFI_STATUS Status = EFI_SUCCESS;

#if BATTERYCHECK_SAMPLE_TEST

	UINT8 *pOFBDTblEnd;
	OFBD_TC_5B_AC_BATTERY_STRUCT *AC_BatteryPtr;

	char *ErrorMsg_1 = "AC adapter is not connected.For an update, the AC adapter has to be connected.";
	char *ErrorMsg_2 = "There is no installed battery or the remaining charge level of the battery is lower than 60%%.Check your battery.";
	char *ErrorMsg_3 = "There is no installed battery or the remaining charge level of the battery is lower than 30%%.Check your battery.";
	char *ErrorMsg_4 = "No support this version of flash Common Interface.";

	pOFBDTblEnd = (UINT8 *)((UINT8 *)pOFBDHdr + (pOFBDHdr->OFBD_Size));
	AC_BatteryPtr = (OFBD_TC_5B_AC_BATTERY_STRUCT *)((UINT8 *)pOFBDHdr + pOFBDHdr->OFBD_HDR_SIZE + sizeof(OFBD_EXT_HDR)); 

	switch(AC_BatteryPtr->dbGetSts)
	{
	//
    // Please add your code here +>>>
    //
		case OFBD_TC_AC_BAT_INFO_REQ:
			/*
			//+>>>if AC/Battery has an issue please add your message here
				Strcpy (pOFBDTblEnd , ErrorMsg_1);
            	pOFBDHdr->OFBD_RS |= OFBD_RS_DIS_OEMSTR;
 				AC_BatteryPtr->dbRetSts |= OFBD_RS_AC_BAT_ERR ;
			//<<<
			*/
				AC_BatteryPtr->dbRetSts |= OFBD_RS_AC_BAT_OK;
		break;

		default:
			AC_BatteryPtr->dbRetSts |= OFBD_RS_AC_BAT_OK;
		break;
	//
    // Please add your code here <<<+
    //

	}

  
#endif  // #ifdef BATTERYCHECK_SAMPLE_TEST

    return(Status);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	BatteryCheckEntry
//
// Description:	OFBD Battery Check Header Handle Entry Point
//
// Input:
//      IN VOID             *Buffer
//      IN OUT UINT8        *pOFBDDataHandled
// Output:
//      VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID BatteryCheckEntry (
    IN VOID             *Buffer,
    IN OUT UINT8        *pOFBDDataHandled )
{
	OFBD_HDR *pOFBDHdr;
	OFBD_EXT_HDR *pOFBDExtHdr; 
	VOID *pOFBDTblEnd;

	if(*pOFBDDataHandled == 0)
	{
		pOFBDHdr = (OFBD_HDR *)Buffer;
		pOFBDExtHdr = (OFBD_EXT_HDR *)((UINT8 *)Buffer + (pOFBDHdr->OFBD_HDR_SIZE));
		pOFBDTblEnd = (VOID *)((UINT8 *)Buffer + (pOFBDHdr->OFBD_Size));    
		
		if(pOFBDHdr->OFBD_FS & OFBD_FS_AC_BAT)
		{   
			//Check Type Code ID
			if(pOFBDExtHdr->TypeCodeID == OFBD_EXT_TC_AC_BAT)
			{  
				if(OFBDBatteryCheck(pOFBDHdr) == EFI_SUCCESS)
				{
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
