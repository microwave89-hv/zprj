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
// $Header: /Alaska/BIN/Modules/BootOptionPolicies/TseDefaultBootOrder/TseDefaultBootOrder.c 6     1/03/13 10:51a Vyacheslava $
//
// $Revision: 6 $
//
// $Date: 1/03/13 10:51a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/BootOptionPolicies/TseDefaultBootOrder/TseDefaultBootOrder.c $
// 
// 6     1/03/13 10:51a Vyacheslava
// Added modification to check for LOAD_OPTION_HIDDEN and ignore hidden
// boot options in creating "DefaultBootOrder" variable. 
// 
// 5     10/15/12 10:31a Vyacheslava
// [TAG]  		EIP103603 
// [Category]  	Bug Fix
// [Severity]  	Critical
// [Symptom]  	DefaultLegacyDevOrder is corrupted
// [RootCause]  	SetDefaultTseBootOrder () corrupts the data which is not
// the Boot Order.
// [Solution]  	for( i = 0; i < (Order->Length / (sizeof (UINT16)) - 1);
// i++ )
// [Files]  		TseDefaultBootOrder.c
// 
// 4     9/13/11 9:09a Vyacheslava
// 
// 3     4/27/11 11:26a Vyacheslava
// [TAG]  		EIP58592
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	Restore Defaults in the Setup will work incorrect after
// second HDD has been disabled.
// 
// 2     2/02/11 2:00p Vyacheslava
// [TAG]  		EIP52313
// [Category]  	New Feature
// 
// 1     1/20/11 10:52a Felixp
// 
// 6     1/13/10 2:13p Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:  TseDefaultBootOrder.c
//
// Description: This is main file of the TseDefaultBootOrder eModule.
//
//<AMI_FHDR_END>
//**********************************************************************

#include <BootOptions.h>
#include "TseDefaultBootOrder.h"

//----------------------------------------------------------------------------


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   CompareTagThenBbsIndex
//
// Description: This function returns result of compairing two DLINK tags.
//
// Input:       
//  Link1 - pointer to the first tag for compare
//  Link1 - pointer to the second tag for compare
//
// Output:  INT32 - result of comparing. 
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

INT32 CompareTagThenBbsIndex( IN DLINK *Link1, IN DLINK *Link2 )
{
    BOOT_OPTION *Option1 = (BOOT_OPTION*)Link1;
    BOOT_OPTION *Option2 = (BOOT_OPTION*)Link2;
    
    // Compare Tags first
    if (Option1->Tag < Option2->Tag) 
        return -1;
    else if (Option1->Tag > Option2->Tag) 
        return 1;

    // Compare by BBS index
    if (Option1->BbsIndex < Option2->BbsIndex) 
        return -1;
    else if (Option1->BbsIndex > Option2->BbsIndex) 
        return 1;

    return 0;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SetDefaultTseBootOrder
//
// Description: 
//  This function sets variables: DefaultLegacyDevOrder and DefaultBootOrder.
//
// Input:       VOID
//
// Output:      VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID SetDefaultTseBootOrder(VOID)
{
    UINTN DevOrderSize;
    LEGACY_DEVICE_ORDER *DevOrder;
    UINTN BootOrderSize;
    UINT16 *BootOrder;
    UINT16 PreviousBootOptionNumber;
    DLINK *Link;
    UINTN BootOrderIndex;
    BOOT_OPTION *Option;
    EFI_GUID DefaultLegacyDevOrderGuid = DEFAULT_LEGACY_DEV_ORDER_VARIABLE_GUID;
    EFI_GUID DefaultBootOrderGuid = DEFAULT_BOOT_ORDER_VARIABLE_GUID;
    LEGACY_DEVICE_ORDER *Order;
    UINTN  i;

    // PRECONDITION: All Boot Option Numbers are set
    BootOrderSize = BootOptionList->Size * sizeof(UINT16);
    if (BootOrderSize == 0) 
        return;

    // Build DefaultLegacyDevOrder variable
    SortList(BootOptionList, CompareTagThenBbsIndex);
    BuildLegacyDevOrderBuffer(&DevOrder, &DevOrderSize);

    // Remove disable mask from buffer DevOrder
    for( Order = DevOrder; (UINT8*)Order < (UINT8*)DevOrder + DevOrderSize; 
         Order = (LEGACY_DEVICE_ORDER*)((UINT8*)Order + Order->Length + sizeof(Order->Type)) ) 
    {
        // The order length includes their own length
        for( i = 0; i < (Order->Length / sizeof(UINT16) - 1); i++ )
            Order->Device[i] &= 0x00FF;
    }

    // Store "DefaultLegacyDevOrder" EFI variable
    pRS->SetVariable(
        L"DefaultLegacyDevOrder", 
        &DefaultLegacyDevOrderGuid,
        BOOT_VARIABLE_ATTRIBUTES,
        DevOrderSize,
        DevOrder
    );
    pBS->FreePool(DevOrder);

    // Build DefaultBootOrder variable
    BootOrder = Malloc(BootOrderSize);
    PreviousBootOptionNumber = INVALID_BOOT_OPTION_NUMBER;
    BootOrderIndex = 0;

    // Set boot option number for each boot option
    FOR_EACH_BOOT_OPTION(BootOptionList,Link,Option)
    {
        if ( (PreviousBootOptionNumber == Option->BootOptionNumber) || 
             (Option->Attributes & LOAD_OPTION_HIDDEN) )
            continue;
        BootOrder[BootOrderIndex++] = Option->BootOptionNumber;
        PreviousBootOptionNumber = Option->BootOptionNumber;
    }
    
    // Store "DefaultBootOrder" EFI variable
    pRS->SetVariable(
        L"DefaultBootOrder", 
        &DefaultBootOrderGuid,
        BOOT_VARIABLE_ATTRIBUTES, 
        BootOrderIndex * sizeof(UINT16), 
        BootOrder
    );
    pBS->FreePool(BootOrder);
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