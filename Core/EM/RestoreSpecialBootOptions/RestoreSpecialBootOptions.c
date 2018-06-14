//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
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
// $Header: /Alaska/BIN/Modules/BootOptionPolicies/RestoreSpecialBootOptions/RestoreSpecialBootOptions.c 3     9/10/13 8:14a Dukeyeh $
//
// $Revision: 3 $
//
// $Date: 9/10/13 8:14a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/BootOptionPolicies/RestoreSpecialBootOptions/RestoreSpecialBootOptions.c $
// 
// 3     9/10/13 8:14a Dukeyeh
// [TAG]  		EIP135544 
// [Category]  	Bug Fix
// [RootCause]  	RestoreSpecialOrphanBootOptions don't compare multi ELINK
// names
// [Solution]  	Change to be able to compare multi ELINKs for target boot
// options
// [Files]  		RestoreSpecialBootOptions.sdl
// RestoreSpecialBootOptions.chm
// RestoreSpecialBootOptions.c
// 
// 2     7/12/13 12:40a Dukeyeh
// [TAG]  		EIP127111 
// [Category]  	New Feature
// [Description]  	1. Initial Release
//                                 2. This module restores some special
// boot options that have been applied orphan boot options policy on.
// [Files]  		RestoreSpecialBootOptions.c
// 
//**********************************************************************
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:  RestoreSpecialBootOptions.c
//
// Description:	Restore some special boot options.
//
//<AMI_FHDR_END>
//**********************************************************************

#include <AmiDxeLib.h>
#include <RestoreSpecialBootOptions.h>
#include <BootOptions.h>

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   UnMaskFilePathList
//
// Description: Unmask the file path that was masked before.
//
// Input:       BOOT_OPTION *Option - the boot option's file path to be unmasked
//
// Output:      none
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID UnMaskFilePathList(BOOT_OPTION *Option) {
    VENDOR_DEVICE_PATH *MaskedDp;
    UINTN MaskedDpLength;

    MaskedDp = (VENDOR_DEVICE_PATH*)Option->FilePathList;
    MaskedDpLength = DPLength(&MaskedDp->Header);
    if (Option->FilePathListLength <= MaskedDpLength) return;
    Option->FilePathListLength -=MaskedDpLength;
    MemCpy(
        Option->FilePathList, (UINT8*)Option->FilePathList+MaskedDpLength,
        Option->FilePathListLength
    );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   RestoreBootOptionByPolicy
//
// Description: Restore the orphan boot option by policy.
//
// Input:       DLIST *BootOptionList - the master boot option list
//              BOOT_OPTION *Option - The orphaned boot option
//              UINTN Policy - the policy to follow, valid values are
//                  ORPHAN_BOOT_OPTIONS_POLICY_DELETE
//                  ORPHAN_BOOT_OPTIONS_POLICY_DISABLE
//                  ORPHAN_BOOT_OPTIONS_POLICY_KEEP
//
// Output:      none
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID RestoreBootOptionByPolicy(
    DLIST *BootOptionList, BOOT_OPTION *Option, const int Policy
) {
    /*if (Policy==ORPHAN_BOOT_OPTIONS_POLICY_DELETE){
     }else*/
    if (Policy==ORPHAN_BOOT_OPTIONS_POLICY_DISABLE) {
        Option->Attributes |= LOAD_OPTION_ACTIVE;
    } else if (Policy==ORPHAN_BOOT_OPTIONS_POLICY_HIDE) {
        Option->Attributes &= ~LOAD_OPTION_HIDDEN;
        UnMaskFilePathList(Option);
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   RestoreSpecialOrphanBootOptions
//
// Description: This function restores the target orphan boot options that
//              have been applied policy on.
//
// Input:       none
//
// Output:      none
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID RestoreSpecialOrphanBootOptions() {
    DLINK *Link;
    BOOT_OPTION *Option;
    CHAR16 *RestoreBootOptionsByName[] = {RESTORED_BOOT_OPTION_NAMES NULL};
    UINT8 RegisteredBootOptionNames = sizeof(RestoreBootOptionsByName)/sizeof(CHAR16*) - 1; // minus NULL
    UINT8 NameIndex;

    if (0 == RegisteredBootOptionNames)
        return;

    FOR_EACH_BOOT_OPTION(BootOptionList,Link,Option) {

        if (RegisteredBootOptionNames) {

            for (NameIndex = 0; NULL != RestoreBootOptionsByName[NameIndex]; NameIndex++) {

                if (!Wcscmp(Option->Description, RestoreBootOptionsByName[NameIndex])) {

                    if (Option->FwBootOption) {
                        RestoreBootOptionByPolicy(
                            BootOptionList, Option, FW_ORPHAN_BOOT_OPTIONS_POLICY
                        );
                    }
                    else {
                        RestoreBootOptionByPolicy(
                            BootOptionList, Option, NON_FW_ORPHAN_BOOT_OPTIONS_POLICY
                        );
                    }

                    --RegisteredBootOptionNames;
                    if (0 == RegisteredBootOptionNames)
                        return;

                    break;
                }
            }
        }
    }
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
