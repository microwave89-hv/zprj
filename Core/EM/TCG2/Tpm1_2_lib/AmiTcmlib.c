//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**        5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093         **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//*************************************************************************
// $Header: /Alaska/SOURCE/Modules/TCG2/Libraries/TisLib/AmiTcmlib/AmiTcmlib.c 1     4/21/14 2:15p Fredericko $
//
// $Revision: 1 $
//
// $Date: 4/21/14 2:15p $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/TCG2/Libraries/TisLib/AmiTcmlib/AmiTcmlib.c $
// 
// 1     4/21/14 2:15p Fredericko
// 
// 1     10/08/13 11:59a Fredericko
// Initial Check-In for Tpm-Next module
// 
// 1     7/10/13 5:50p Fredericko
// [TAG]  		EIP120969
// [Category]  	New Feature
// [Description]  	TCG (TPM20)
// 
// 6     4/01/11 9:32a Fredericko
// Updated function Header
// 
// 5     3/31/11 4:48p Fredericko
// Changes for TCG_Legacy support 
// 
// 4     3/29/11 4:51p Fredericko
// Moved TCM device ID and Vendor ID check to tokens. 
// 
// 3     3/29/11 12:52p Fredericko
// 
// 2     3/29/11 12:07p Fredericko
// [TAG]        EIP 54642
// [Category] Improvement
// [Description] 1. Checkin Files related to TCG function override 
// 2. Include TCM and TPM auto detection
// [Files] Affects all TCG files
//
//
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:  AmiTcmlib.c  
//
// Description: 
//  AmiTcmlibrary functions
//
//<AMI_FHDR_END>
//**********************************************************************
#include "AmiTcmlib.h"
#include "token.h"


TCM_ID_STRUC  TCMSupportedArray[NUMBER_OF_SUPPORTED_TCM_DEVICES]={
    {SUPPORTED_TCM_DEVICE_1_VID,SUPPORTED_TCM_DEVICE_1_DID},  //ZTEIC
    {SUPPORTED_TCM_DEVICE_2_VID,SUPPORTED_TCM_DEVICE_2_DID}  //ZTEIC2
};




//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   AutoSupportType
//
// Description: verifies support for a TCM module on a platform
//
// Input:       NONE
//
// Output:      BOOLEAN
//
// Modified:
//
// Referrals:   
//
// Notes:       
//<AMI_PHDR_END>
//**********************************************************************
extern
BOOLEAN
__stdcall AutoSupportType ()
{
#if TCG_LEGACY == 0
  UINTN i=0;

   for(i=0;i<(sizeof(TCMSupportedArray)/sizeof(TCM_ID_STRUC));i++){
     if((TCMSupportedArray[i].VID == *(UINT16 *)(UINTN)(PORT_TPM_IOMEMBASE + 0xF00)) &&
        (TCMSupportedArray[i].DID == *(UINT16 *)(UINTN)(PORT_TPM_IOMEMBASE + 0xF02))){
         return TRUE;
      }
    }
#endif
    return FALSE;
}




//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**     5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
