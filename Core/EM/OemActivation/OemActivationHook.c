//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

//*****************************************************************************
// $Header: /Alaska/SOURCE/Modules/OemActivation/OemActivationHook.c 3     6/10/11 10:57a Vyacheslava $
//
// $Revision: 3 $
//
// $Date: 6/10/11 10:57a $
//*****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/OemActivation/OemActivationHook.c $
// 
// 3     6/10/11 10:57a Vyacheslava
// 
// 2     5/26/11 11:34a Vyacheslava
// 
// 1     4/29/11 12:39p Vyacheslava
// [TAG]  		EIP58139 
// [Category]  	New Feature
// [Description]  	Added SW SMI hook to place Oem Activation Key in NCB.
// 
//
//*****************************************************************************
//<AMI_FHDR_START>
//
// Name:    OemActivationHook.c
//
// Description: SW SMI hook. 
//
//<AMI_FHDR_END>
//*****************************************************************************


#include <AmiDxeLib.h>
#include <Protocol/SmiFlash.h>
#include "OemActivation.h"

//----------------------------------------------------------------------------


#if OEM_ACTIVATION_TABLE_LOCATION == 1

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   OemActivationUpdateBlockTypeId
//
// Description: This function is SW SMI hook that sets Flash Block Description
//              type for AMI AFU utility. (EIP#58139)
//
// Input:
//  SwSmiNum    - SW SMI value number
//  Buffer      - Flash descriptor address
//
// Output:  VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID OemActivationUpdateBlockTypeId (
    IN UINT8  SwSmiNum,
    IN UINT64 Buffer )
{
    BLOCK_DESC *BlockDesc;
    UINTN  i;

    // return if SW SMI value is not "Get Flash Info"
    if (SwSmiNum != SMIFLASH_GET_FLASH_INFO) 
        return;
    
    BlockDesc = (BLOCK_DESC*)&((INFO_BLOCK*)Buffer)->Blocks;
    
    for (i = 0; i < ((INFO_BLOCK*)Buffer)->TotalBlocks; i++) {
    
        TRACE((TRACE_ALWAYS,"OemActivationUpdateBlockTypeId: %08X(%08X), Block %08X\n",OEM_ACTIVATION_BLOCK_ADDRESS,OEM_ACTIVATION_BLOCK_END,BlockDesc[i].StartAddress));
        
        if (BlockDesc[i].StartAddress < OEM_ACTIVATION_BLOCK_ADDRESS) 
            continue;
        
        if (BlockDesc[i].StartAddress >= OEM_ACTIVATION_BLOCK_END) 
            continue;
        
        TRACE((TRACE_ALWAYS,"OemActivationUpdateBlockTypeId: Found Blocks %08X\n",BlockDesc[i].StartAddress));
        
        BlockDesc[i].Type = OA3_FLASH_BLOCK_DESC_TYPE;
    }
}

#endif

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************