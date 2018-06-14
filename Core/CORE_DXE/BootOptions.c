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
// $Header: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Core/CORE_DXE/BootOptions.c 7     7/08/15 4:30a Chienhsieh $
//
// $Revision: 7 $
//
// $Date: 7/08/15 4:30a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Core/CORE_DXE/BootOptions.c $
// 
// 7     7/08/15 4:30a Chienhsieh
// [EIP210170] Improved BootOption DevicePath match algorithm.
// 
// 6     7/15/14 9:55p Chienhsieh
// Update to rev.39 for EIP172950, Core updates for UEFI Variable
// Technical Advisory implement.
// 
// 39    6/03/14 5:11p Artems
// [TAG]  		EIP166565
// [Category]  	Improvement
// [Description]  	Runtime attribute for LegacyDevOrder variable is
// modified depending on
// token value, to support SCE tool
// [Files]  		BootOptions.c
// 
// 38    5/12/14 5:12p Artems
// [TAG]  		EIP166565
// [Category]  	Improvement
// [Description]  	Variables LegacyDevOrder and OldLegacyDevOrder removed
// runtime access attribute
// [Files]  		BootOptions.c
// 
// 5     10/30/13 6:53a Ireneyang
// - Fix Setup menu erroneously shows multiple instances of 
//   the same bootable device for EIP139412 
// 
// 36    6/21/13 2:54p Felixp
// Bug fix(EIP 124559):
//   Symptom: When MATCH_BOOT_OPTION_BY_LOCATION was zero, off-board
// legacy mass storage device
//     was mistakenly matched with on-board legacy boot options.
//   Root cause: DeviceTypeDevicePathTest was matching unrelated device
// paths. 
//   Solution: DeviceTypeDevicePathTest function is updated to return
// FALSE (no-match) when
//     device interface type is unknown.
//     MatchBootOptionsToDevices is updated disable multiple boot option
// matching for legacy devices.
//     Legacy device can't be matched with more than one boot option. 
//   Files: BootOptions.c
// 
// 35    5/20/13 4:33p Artems
// [TAG]  		EIP N/A
// [Category]  	Improvement
// [Description]  	Implement ORPHAN_BOOT_POLICY_KEEP for legacy groups
// [Files]  		BootOptions.h BootOptions.c BdsBoard.c
// 
// 4     9/17/13 10:11p Thomaschen
// Add EIP 134220 solution to fix boot option doesn't change 
// in special test step.
// 
// 34    4/26/13 2:32p Felixp
// [TAG]  		EIP109955
// [Category]  	Improvement
// [Description]  	Support USB device identification by serial number.
// 
// 33    2/18/13 10:54a Felixp
// Minor improvements:
//  - ConstructBootOptionName: unused variable is removed.
//  - BuildNameFilePath: check for out-of-memory condiftion.
// 
// 32    2/18/13 10:52a Felixp
// Improvement(EIP 115148): ReadBootOptions is updated to delete
// ill-formed boot option variables.
// 
// 31    2/07/13 2:18p Artems
// [TAG]  		EIP111307
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	After insert two floppies into system and change Boot Mode
// from ''UEFI'' to ''Legacy'' in BIOS setup utility, check it will show
// two Floppy Drive BBS Priorites in BIOS Setup Utility
// [RootCause]  	UEFI boot option was mistakingly matched to legacy boot
// device
// [Solution]  	Added specific matching function to eliminate mistaken
// matches
// [Files]  		BootOptions.c Core_Dxe.sdl
// 
// 30    11/28/12 4:53p Felixp
// Bug fix: The Bds was not building when CSM was not in the project.
// Root cause: the MaskFilePathList function, which is used in BdsBoard.c,
// was declared in BootOptions.c under #ifdef CSM_SUPPORT.
// Solution: The definition of MaskFilePathList is moved outside of #ifdef
// CSM_SUPPORT.
// 
// 29    11/09/12 4:37p Artems
// [TAG]  		EIP N/A
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	ill-formed bootoption can get control
// [RootCause]  	Function ValidateBootOption was returning BOOLEAN value,
// while ReadBootOption was checked EFI_STATUS value
// [Solution]  	Replaced function ValidateBootOption with
// IsBootOptionValid function
// Updated ReadBootOption function to perform correct check
// [Files]  		BootOptions.c
// 
// 28    7/19/12 6:28p Felixp
// Enhacement:
// Validate boot option NVRAM variables before processing (make sure all
// the fields contain valid data).
// The validation is performed by the new ValidateBootOption function.
// 
// 27    7/19/12 4:29p Felixp
// Enhacement:
// The implementation of the MatchBootOptionsToDevices function is
// changed.
// The old implementation was always matching boot device to a single boot
// option.
// The new implementation allows matching of multiple boot options to the
// same boot device.
// 
// 26    7/02/12 4:40p Felixp
// [TAG]  		EIP83692
// [Category]  	Improvement
// [Description]  	The implementation from previous check in is updated to
// use BootOptionDpMatchingFunctions eLinks instead of
// BootOptionMatchingFunctions.
// It is more appropriate as this is a device path test. 
// MatchUsbClassOptionToUsbDevice is renamed to UsbClassDevicePathTest.
// [Files]  		Core_Dxe.sdl, BootOptions.c
// 
// 25    6/21/12 4:58p Artems
// [TAG]  		EIP83692
// [Category]  	Improvement
// [Description]  	Added function to match existing UEFI boot option with
// USB class to available USB boot device
// [Files]  		Core_Dxe.sdl BootOptions.c
// 
// 24    6/01/12 3:59p Artems
// [TAG]  		EIP N/A
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	Dump boot options doesn't print "hidden" attribute
// [RootCause]  	Incorrect bit check
// [Solution]  	Corrected bit check
// [Files]  		BootOptions.c
// 
// 23    4/12/12 6:12p Felixp
// [TAG]  		EIP84716
// [Category]  	Improvement
// [Description]  	PXE boot item doesn't show particular IPV4 / IPV6 in
// boot menu
// 
// 22    4/09/12 5:56p Artems
// Implementation of NON_FW_BOOT_OPTION_HIDE functionality
// 
// 21    12/05/11 3:58p Felixp
// [TAG]  		EIP72485
// [Category]  	Improvement
// [Description]  	Handling of the UEFI HDD boot devices has changed. 
// Old implementation: UEFI HDD boot devices were filtered out using
// IsUefiHddBootDevice filter function prior to the boot option matching.
// New implementation: UEFI HDD boot devices participate in the boot
// option matching. Unmatched UEFI HDD devices are deleted by the
// DeleteUnmatchedUefiHddBootDevices function.
// The problems with the implementation is that UEFI HDD boot options have
// always been orphan boot options, 
// which caused customer's confusion and side effects in the custom boot
// option maintenance code.
// 
// [Files]  		BootOptions.c
// CORE_DXE.sdl
// 
// 20    10/31/11 10:10a Felixp
// Follow up to previous check in(EIP 69507): Bug fix
// GetPhysicalNetworkCardHandle: 
// wrong pointer was passed to pBS->FreePool
// 
// 19    10/24/11 5:45p Felixp
// [TAG]  		EIP69507 
// [Category]  	Improvement
// Improvement is the handling of the boot options associated with
// the network devices in ConstructBootOptionNameByHandle function .
// The name is now constructed using physical network card handle 
// (as opposed to a handle associated with the IP connection). 
// 
// 18    10/19/11 12:54p Felixp
// [TAG]  		EIP71102
// [Category]  	Improvement
// SaveBootOptions is updated to validate the boot option before saving
// it.
// The boot option can be invalid due to:
//   - a hot plug boot device disconnected in the middle of the BDS
// processing
//   - bug in the boot option processing eLink function from other eModule
// 
// 17    9/20/11 12:39p Felixp
// [TAG]  		EIP70093
// [Category]  	Improvement
// [Description]  	BuildLegacyDevOrderBuffer is updated.
// The code that creates a dummy LegacyDevOrder variable 
// containing just a header when no legacy devices are found is removed.
// The code was required to support old versions of TSE.
// It is no longer required.
// 
// 16    9/20/11 12:28p Felixp
// DumpBootOptionList function that prints debug messages is updated to
// print hidden attribute.
// 
// 15    6/16/11 8:55a Felixp
// Bug fix in FindLegacyDeviceGroupByBbsIndex to prevent premature
// matching of a BBS index 
// to the Type of the next group in the LegacyDevOrder structure.
// 
// 14    11/18/10 3:31p Felixp
// Clean up
// 
// 13    11/18/10 8:11a Felixp
// Masking of legacy devices is added.
// 
// 12    11/15/10 5:15p Felixp
// LocateDevicePathTest: function is updated to perform a full device path
// match 
// (earlier implementation could match boot option with the handle of the
// parent device)
// DeviceTypeDevicePathTest: code that handles removable device without a
// media is removed
// (it may have unintended consequences)
// NormalizeBootOptions: the order of normalization is changed to
// normalize device path 
// prior to the name (to make sure name reflects updated device path)
// 
// 11    10/07/10 1:35p Felixp
// Make sure code compiles without CSM.
// 
// 10    10/07/10 12:58p Felixp
// BuildLegacyDevOrderBuffer function is added
// 
// 9     10/06/10 5:33p Felixp
// Bug fix in DeviceTypeDevicePathTest function.
// 
// 8     10/01/10 8:07a Felixp
// NormalizeBootOptions function is added.
// 
// 7     9/29/10 9:23a Felixp
// 1. Enhancement(EIP 39464) : Implementation of the BdsEntry function is
// changed. 
//  The BdsEntry is now a dispatching function that calls a collection of
// functions 
//  formed by the BDS_CONTROL_FLOW eLink.
// 2. Minor Imrpvement in ConstructBootOptionName function.
// 
// 6     9/22/10 12:41p Felixp
// Bug fix in AdjustLegacyBootOptionPriorities: the disabled boot option
// was not  enabled based on LagacyDevOrder status
// 
// 5     9/21/10 3:33p Felixp
// Boot Option Infrastructure Improvements: 
// - NORMALIZE_BOOT_OPTIONS SDL token is replaced with 
//   NORMALIZE_BOOT_OPTION_NAME and NORMALIZE_BOOT_OPTION_DEVICE_PATH
// - MATCH_BOOT_OPTION_BY_LOCATION and MATCH_BOOT_OPTION_BY_DEVICE 
//   SDL tokens and the supporting code are added.
// 
// 4     8/27/10 9:32a Felixp
// Function headers added
// 
//**********************************************************************

//<AMI_FHDR_START>
//---------------------------------------------------------------------------
// Name:        BootOptions.c
//
// Description: Contains the code for dealing with boot options and their maintance
//
////---------------------------------------------------------------------------
//<AMI_FHDR_END>
#include "BootOptions.h"
#include <Protocol/PDiskInfo.h>
#include <Protocol/UsbIo.h>

EFI_HII_HANDLE HiiHandle=0;
EFI_GUID AmiBbsDevicePathGuid = AMI_BBS_DEVICE_PATH_GUID;
EFI_GUID AmiMaskedDevicePathGuid = AMI_MASKED_DEVICE_PATH_GUID;
EFI_GUID AmiDeviceNameDevicePathGuid = AMI_DEVICE_NAME_DEVICE_PATH_GUID;
#ifdef CSM_SUPPORT
EFI_GUID LegacyDevOrderGuid = LEGACY_DEV_ORDER_GUID;
#endif

DLIST BootOptionListStructure;
DLIST BootDeviceListStructure;
DLIST *BootOptionList = &BootOptionListStructure;
DLIST *BootDeviceList = &BootDeviceListStructure;


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SortList
//
// Description: Sort the list of DLIST items using the passed COMPARE_FUNCTION to 
//              determine the correct ordering of items
//
// Input:       DLIST *List - list of items to sort
//              COMPARE_FUNCTION Compare - function to use to to sort the list
//
// Output:      DLIST *List
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID SortList(DLIST *List,  COMPARE_FUNCTION Compare){
    DLIST MergeList;
    DLINK *p, *q, *e;
    UINTN pSize, qSize, inSize;
    UINT32 NoMerges;
    UINTN i;

    if(List->Size <= 1)  //nothing to sort
        return;

    inSize = 1;
    MergeList = *List;

    while(1)
    {
        p = MergeList.pHead;
        DListInit(&MergeList);      //clear list
        NoMerges = 0;

        while(p != NULL)
        {
            NoMerges++;
            q = p;
            for(i = 0, pSize = 0; i < inSize; i++)
            {
                pSize++;
                q = q->pNext;
                if(q == NULL)
                    break;
            }

            qSize = inSize;
            while(pSize > 0 || (qSize > 0 && q != NULL))
            {
               if(pSize == 0)
                {
                    e = q;
                    q = q->pNext;
                    DListAdd(&MergeList, e);
                    qSize--;
                }
                else if(qSize == 0 || q == NULL)
                {
                    e = p;
                    p = p->pNext;
                    DListAdd(&MergeList, e);
                    pSize--;
                }
                else if(Compare(p, q) > 0)
                {
                    e = q;
                    q = q->pNext;
                    DListAdd(&MergeList, e);
                    qSize--;
                }
                else
                {
                    e = p;
                    p = p->pNext;
                    DListAdd(&MergeList, e);
                    pSize--;
                }
            }
            p = q;
        }
        if(NoMerges <= 1)
            break;
        inSize *= 2;
    }
    *List = MergeList;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CompareTagThenPriority
//
// Description: Compare the two boot options passed and determine the priority of
//              the first parameter in relation to the second parameter
//              Try to compare based on the following parameters in order, 
//              Tag, then Group Header, then Priority
//
// Input:       DLINK *Link1 - boot option 1
//              DLINK *Link2 - boot option 2
//
// Output:      INT32 - the comparison result
//              Less than zero - Boot option 1 is lower priority than boot option 2
//              zero - boot option 1 is same priority as boot option 2
//              greater than zero - boot option 1 is a higher priority than boot option 2
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
INT32 CompareTagThenPriority(DLINK *Link1, DLINK *Link2){
	BOOT_OPTION *Option1 = (BOOT_OPTION*)Link1;
	BOOT_OPTION *Option2 = (BOOT_OPTION*)Link2;
	if (Option1->Tag < Option2->Tag) return -1;
	else if (Option1->Tag > Option2->Tag) return 1;
    if (Option1->GroupHeader != Option2->GroupHeader) 
        return (Option1->GroupHeader) ? -1 : 1;
	if (Option1->Priority < Option2->Priority) return -1;
	else if (Option1->Priority > Option2->Priority) return 1;
    return 0;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ComparePriorityThenBootOptionNumber
//
// Description: Compare the two passed boot options first by their priority
//              if their priorities are equal, compare them based on their
//              boot option number
//
// Input:       DLINK *Link1 - boot option 1
//              DLINK *Link2 - boot option 2
//
// Output:      INT32 - the comparison result
//              Less than zero - Boot option 1 is lower priority than boot option 2
//              zero - boot option 1 is same priority as boot option 2
//              greater than zero - boot option 1 is a higher priority than boot option 2
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
INT32 ComparePriorityThenBootOptionNumber(DLINK *Link1, DLINK *Link2){
	BOOT_OPTION *Option1 = (BOOT_OPTION*)Link1;
	BOOT_OPTION *Option2 = (BOOT_OPTION*)Link2;
	if (Option1->Priority < Option2->Priority) return -1;
	else if (Option1->Priority > Option2->Priority) return 1;
	if (Option1->BootOptionNumber < Option2->BootOptionNumber) return -1;
	else if (Option1->BootOptionNumber > Option2->BootOptionNumber) return 1;
    if (Option1->GroupHeader != Option2->GroupHeader) 
        return (Option1->GroupHeader) ? -1 : 1;
    return 0;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CreateBootOption
//
// Description: Create a BOOT_OPTION for the first entry in the passed BootOptionList
//
// Input:       DLIST *BootOptionList - the list entry that needs a BOOT_OPTION 
//                  structure created
//
// Output:      BOOT_OPTION * - pointer to the created BOOT_OPTION
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOT_OPTION* CreateBootOption(DLIST *BootOptionList){
    static BOOT_OPTION BootOptionTemplate = {
    	{NULL,NULL}, LOAD_OPTION_ACTIVE, NULL, NULL, 0, NULL, 0,
        INVALID_BOOT_OPTION_NUMBER, LOWEST_BOOT_OPTION_PRIORITY,
        UNASSIGNED_HIGHEST_TAG,
        INVALID_HANDLE, INVALID_BBS_INDEX, NULL, FALSE, FALSE
    };

	BOOT_OPTION *Option = Malloc(sizeof(BOOT_OPTION));
    ASSERT(Option!=NULL);
    *Option = BootOptionTemplate;
	DListAdd(BootOptionList, &Option->Link);
    return Option;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   DeleteBootOption
//
// Description: Delete the passed BOOT_OPTION from the BootOptionList
//
// Input:       DLIST *BootOptionList - the master boot option list
//              BOOT_OPTION *Option - the option that should be deleted from the
//                  master boot option list
//
// Output:      none
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID DeleteBootOption(DLIST *BootOptionList, BOOT_OPTION *Option){
	DListDelete(BootOptionList,&Option->Link);
	if (Option->Description!=NULL) pBS->FreePool(Option->Description);
	if (Option->FilePathList!=NULL) pBS->FreePool(Option->FilePathList);
	if (Option->OptionalDataSize!=0) pBS->FreePool(Option->OptionalData);
	pBS->FreePool(Option);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CreateBootDevice
//
// Description: Create a boot device entry and add it to the BootDeviceList
//              fill the entry with the information from the passed parameters
//
// Input:       DLIST *BootDeviceList - The master boot device list to add the
//                  new boot device entry
//              EFI_HANDLE DeviceHandle - the handle of the device
//              UINT16 BbsIndex - the index in the bbs table of the device
//              BBS_TABLE *BbsEntry - the entire bbs table
//
// Output:      BOOT_DEVICE * - the new boot device
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOT_DEVICE* CreateBootDevice(
    DLIST *BootDeviceList, EFI_HANDLE DeviceHandle, 
	UINT16 BbsIndex, BBS_TABLE *BbsEntry
){
	BOOT_DEVICE *Device = Malloc(sizeof(BOOT_DEVICE));
    ASSERT(Device!=NULL);
	Device->BbsEntry = BbsEntry;
	Device->BbsIndex = BbsIndex;
	Device->DeviceHandle = DeviceHandle;
 	DListAdd(BootDeviceList, &Device->Link);
    return Device;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   DeleteBootDevice
//
// Description: Delete the boot device out of the master boot device list
//
// Input:       DLIST *BootDeviceList - the master boot device list
//              BOOT_DEVICE *Device - the boot device to delete from the master
//                  boot device list
//
// Output:      none
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID DeleteBootDevice(DLIST *BootDeviceList, BOOT_DEVICE* Device){
    DListDelete(BootDeviceList, &Device->Link);
    pBS->FreePool(Device);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   UpdateBootOptionWithBootDeviceInfo
//
// Description: Update the boot option with the information from the passed
//              boot device information
//
// Input:       BOOT_OPTION *Option - the boot option that needs updated
//              BOOT_DEVICE *Device - the boot device that contains the information
//                  that the boot option needs updated with
//
// Output:      none
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID UpdateBootOptionWithBootDeviceInfo(
    BOOT_OPTION *Option, BOOT_DEVICE* Device
){
	Option->BbsEntry = Device->BbsEntry;
	Option->BbsIndex = Device->BbsIndex;
	Option->DeviceHandle = Device->DeviceHandle;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CreateBootOptionsFromNvramOption
//
// Description: Create a boot option using the nvram information
//
// Input:       DLIST *BootOptionList - the master boot option list
//              UINT16 BootOptionNumber - the XXXX of the BootXXXX boot option
//              EFI_LOAD_OPTION NvramOption - the associated EFI_LOAD_OPTION
//              UINTN NvramOptionSize - the sizeof the nvram option
//              UINT32 Priority - the priority of the boot option
//
// Output:      BOOT_OPTION * - the created boot option
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOT_OPTION* CreateBootOptionsFromNvramOption(
	DLIST *BootOptionList, UINT16 BootOptionNumber,
	EFI_LOAD_OPTION *NvramOption, UINTN NvramOptionSize,
	UINT32 *Priority
){
	BOOT_OPTION *Option;
	UINTN DescriptionSize;
	UINT32 *OptionalData;
	UINT8 *FilePathList;
	UINTN OptionalDataSize;

	Option = CreateBootOption(BootOptionList);
	Option->Attributes=NvramOption->Attributes;
	DescriptionSize = (Wcslen((CHAR16*)(NvramOption+1))+1)*sizeof(CHAR16);
	Option->Description = Malloc(DescriptionSize);
	MemCpy(Option->Description, NvramOption+1, DescriptionSize);

	FilePathList = (UINT8*)(NvramOption+1)+DescriptionSize;
	Option->FilePathListLength = NvramOption->FilePathListLength;
	Option->FilePathList = Malloc(Option->FilePathListLength);
	MemCpy(
		Option->FilePathList, FilePathList, Option->FilePathListLength
	);

	OptionalData =  (UINT32*)(FilePathList + NvramOption->FilePathListLength);
    OptionalDataSize =  (UINT8*)NvramOption 
							  + NvramOptionSize 
							  - (UINT8*)OptionalData;
	Option->BootOptionNumber = BootOptionNumber;
	Option->Priority = *Priority;
	*Priority = GetNextBootOptionPriority(*Priority);
	if ( OptionalDataSize >= sizeof(UINT32) ){
		if (*OptionalData==AMI_SIMPLE_BOOT_OPTION_SIGNATURE){
			OptionalDataSize -= sizeof(UINT32);
			OptionalData++;
			Option->FwBootOption = TRUE;
		}else if (*OptionalData==AMI_GROUP_BOOT_OPTION_SIGNATURE){
			Option->FwBootOption = TRUE;
            Option->GroupHeader = TRUE;
			OptionalDataSize -= sizeof(UINT32);
			OptionalData++;
			while (    OptionalDataSize > AMI_NESTED_BOOT_OPTION_HEADER_SIZE){
				NESTED_BOOT_OPTION *NestedBootOption = (NESTED_BOOT_OPTION*)OptionalData;
				if (   NestedBootOption->Signature != AMI_NESTED_BOOT_OPTION_SIGNATURE
					|| NestedBootOption->Size > OptionalDataSize
				) break;
				CreateBootOptionsFromNvramOption(
					BootOptionList, BootOptionNumber, &NestedBootOption->Option,
					NestedBootOption->Size-AMI_NESTED_BOOT_OPTION_HEADER_SIZE,
					Priority
				);
				OptionalDataSize -= NestedBootOption->Size;
				OptionalData = (UINT32*)((UINT8*)OptionalData+NestedBootOption->Size);
			}
		}
	}

	if (OptionalDataSize==0){
		Option->OptionalData = NULL;
		Option->OptionalDataSize = 0;
	}else{
		Option->OptionalData = Malloc(OptionalDataSize);
		MemCpy(
			Option->OptionalData, OptionalData, OptionalDataSize
		);
		Option->OptionalDataSize = OptionalDataSize;
	}
	return Option;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   IsBootOptionValid
//
// Description: The function checks if boot option is well-formed
//
// Input:       EFI_LOAD_OPTION NvramOption, UINTN NvramOptionSize
//
// Output:      TRUE - boot option is valid, FALSE otherwise
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN IsBootOptionValid(EFI_LOAD_OPTION *NvramOption, UINTN NvramOptionSize){
    CHAR16 *Char;
    CHAR16 *EndOfDescription;
    EFI_DEVICE_PATH_PROTOCOL *Dp;
    UINTN DevicePathSize;

    // The boot option must have at least the header, 
    // an empty (just the NULL-terminator) description,
    // and an empty device path (End-of-Device-Path node).
    if (NvramOption->FilePathListLength<sizeof(EFI_DEVICE_PATH_PROTOCOL)) return FALSE;
    if (NvramOptionSize < sizeof(*NvramOption)+sizeof(CHAR16)) return FALSE;
    NvramOptionSize -= sizeof(*NvramOption);

    if (  NvramOption->FilePathListLength >= NvramOptionSize ) return FALSE;
    NvramOptionSize -= NvramOption->FilePathListLength;

    // The description must include at least the NULL-terminator
    if (NvramOptionSize < sizeof(CHAR16)) return FALSE;

    // The description must be NULL-terminated
    Char = (CHAR16*)(NvramOption+1);
    EndOfDescription = (CHAR16*)((CHAR8*)Char+NvramOptionSize);
    while( *Char && Char < EndOfDescription) Char++;
    if (Char==EndOfDescription) return FALSE;

    // Validate the device path;
    Dp = (EFI_DEVICE_PATH_PROTOCOL*)(Char+1); // skip the terminating zero.
    if (EFI_ERROR(IsValidDevicePath(Dp))) return FALSE;
    // NvramOption->FilePathListLength can't be zero. 
    // We checked that at the start of the funciton.
    DevicePathSize = NvramOption->FilePathListLength;
    while (TRUE) {
        UINTN Length = NODE_LENGTH(Dp);
        if (Length>DevicePathSize) return FALSE;
        // We are not making sure that Length is not equal to zero.
        // This has already been verified by the IsValidDevicePath above.
        DevicePathSize -= Length;
        if (DevicePathSize < sizeof(EFI_DEVICE_PATH_PROTOCOL)){
            if (DevicePathSize != 0 ) return FALSE;
            //The last node must be an End-of-Device-Path node.
            return 
                   isEndNode(Dp) 
                && Dp->SubType == END_ENTIRE_SUBTYPE
                && Length == sizeof(EFI_DEVICE_PATH_PROTOCOL)
            ;
        }
        Dp = (EFI_DEVICE_PATH_PROTOCOL*)((UINT8*)Dp+Length);
    }
    //Should never reach this point.
    return FALSE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ReadBootOption
//
// Description: Read the boot options from NVRAM and create associated 
//              boot options in the master boot option list for each valid
//              option
//
// Input:       DLIST *BootOptionList - the list to update with the nvram options
//
// Output:      none 
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID ReadBootOptions(){
	UINT16 *BootOrder = NULL;
	UINTN BootOrderSize = 0; 
	EFI_STATUS Status;
	UINTN i;
	EFI_LOAD_OPTION *NvramOption = NULL;
	UINT32 Priority=IndexToBootPriority(0);
	UINTN NvramOptionSize;
    UINT16 MaxBootOptionNumber=0;

	Status=GetEfiVariable(
		L"BootOrder", &EfiVariableGuid, NULL, &BootOrderSize, &BootOrder
	);
	if (EFI_ERROR(Status)) return;
	for(i=0; i<BootOrderSize/sizeof(UINT16); i++){	
		CHAR16 BootStr[9];

		// Get Boot Option
		Swprintf(BootStr,L"Boot%04X",BootOrder[i]);
		Status=GetEfiVariable(
			BootStr, &EfiVariableGuid, NULL, &NvramOptionSize, &NvramOption
		);
		if (EFI_ERROR(Status)) continue;
        //Let's verify if boot option is well-formed
        if (!IsBootOptionValid(NvramOption, NvramOptionSize)){
            TRACE((TRACE_DXE_CORE,"The boot option Boot%04X is ill-formed. Deleting...\n",
                   BootOrder[i]
            ));
			pRS->SetVariable(BootStr, &EfiVariableGuid, 0, 0, NULL);
            continue;
        }
		CreateBootOptionsFromNvramOption(
			BootOptionList, BootOrder[i], NvramOption, NvramOptionSize, &Priority
		);
        if (BootOrder[i] > MaxBootOptionNumber)
            MaxBootOptionNumber = BootOrder[i];
	}
	pBS->FreePool(NvramOption);
	pBS->FreePool(BootOrder);
}

VOID MaskFilePathList(BOOT_OPTION *Option){
    static struct {
		VENDOR_DEVICE_PATH vendor;
		EFI_DEVICE_PATH_PROTOCOL end;
	} MaskedDp = {
		{
          {HARDWARE_DEVICE_PATH, HW_VENDOR_DP, {sizeof(VENDOR_DEVICE_PATH), 0}},
		  AMI_MASKED_DEVICE_PATH_GUID
        },
		{END_DEVICE_PATH,END_ENTIRE_SUBTYPE,sizeof(EFI_DEVICE_PATH_PROTOCOL)}
	};
    static MaskedDpLength = sizeof(MaskedDp);
    UINT8 *NewDp;

    NewDp = Malloc(Option->FilePathListLength + MaskedDpLength);
    if (NewDp==NULL) return;
    MemCpy(NewDp, &MaskedDp, MaskedDpLength);
    MemCpy(
        NewDp+MaskedDpLength, Option->FilePathList,
        Option->FilePathListLength
    );
    pBS->FreePool(Option->FilePathList);
    Option->FilePathList = (EFI_DEVICE_PATH_PROTOCOL*)NewDp;
    Option->FilePathListLength += MaskedDpLength;
}

#ifdef CSM_SUPPORT
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetBbsIndexByPositionInTheGroup
//
// Description: Using the passed position, return the BBS index from the legacy dev
//              order group
//
// Input:       LEGACY_DEVICE_ORDER *Group - The legacy device order
//              UINT16 Position - the index into the legacy dev order to return
//
// Output:      UINT32 - the bbs index from the the legacy dev order
//
// Note: function only available, and used, if CSM_SUPPORT token is defined and enabled
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT32 GetBbsIndexByPositionInTheGroup(
	LEGACY_DEVICE_ORDER *Group, UINT16 Position
){
	UINT16* EndOfGroup = (UINT16*)(
        (UINT8*)Group + Group->Length + sizeof(UINT32)
    );
	UINT16 *IndexPtr = &Group->Device[0];
    UINT32 Counter = 0;

	while(IndexPtr<EndOfGroup){
		if (Counter == Position)
			return *IndexPtr;
		IndexPtr++;
        Counter++;
	}
	return 0;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   FindPositionInTheGroupByBbsIndex
//
// Description: Get the corresponding device index in the LEGACY_DEV_ORDER based on
//              the bbs index number.  Legacy dev order organizes the boot priorities
//              of a class of devices (Cdrom, hdd, bev, etc) and the individual indexes
//              of the device are the relative priorities in which they should be used
//              to attempt a legacy boot.
//
// Input:       LEGACY_DEVICE_ORDER *Group - pointer to the legacy dev order group
//              UINT16 BbsIndex - index of the device trying to be matched
//
// Output:      UINT32 - the index of the device inside of the LEGACY_DEV_ORDER
//
// Note: function only available, and used, if CSM_SUPPORT token is defined and enabled
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT32 FindPositionInTheGroupByBbsIndex(
	LEGACY_DEVICE_ORDER *Group, UINT16 BbsIndex
){
	UINT16* EndOfGroup = (UINT16*)(
        (UINT8*)Group + Group->Length + sizeof(UINT32)
    );
	UINT16 *IndexPtr = &Group->Device[0];
    UINT32 Counter = 0;

	while(IndexPtr<EndOfGroup){
		if (*(UINT8*)IndexPtr == *(UINT8*)&BbsIndex)
			return Counter;
		IndexPtr++;
        Counter++;
	}
	return 0;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   FindLegacyDeviceGroupByBbsIndex
//
// Description: Go through the legacy device order structure and find the legacy dev order
//              index that matches the bss index.
//
// Input:       LEGACY_DEVICE_ORDER *DevOrder - pointer to the legacy device order
//              UINTN DevOrderSize - size of the legacy dev order structure
//              UINT16 BbsIndex - index of the bbs device to match
//
// Output:      LEGACY_DEVICE_ORDER *
//
// Note: function only available, and used, if CSM_SUPPORT token is defined and enabled
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
LEGACY_DEVICE_ORDER* FindLegacyDeviceGroupByBbsIndex(
	LEGACY_DEVICE_ORDER *DevOrder, UINTN DevOrderSize, UINT16 BbsIndex
){
	UINT16 *EndOfDevOrder = (UINT16*)((UINT8*)DevOrder+DevOrderSize);
	LEGACY_DEVICE_ORDER* EndOfGroup = DevOrder;
	LEGACY_DEVICE_ORDER* GroupStart = DevOrder;
	UINT16 *IndexPtr = (UINT16*)EndOfGroup;				  

	while(IndexPtr<EndOfDevOrder){
		if (IndexPtr==(UINT16*)EndOfGroup){
			IndexPtr = &EndOfGroup->Device[0];
            GroupStart = EndOfGroup;
			EndOfGroup = (LEGACY_DEVICE_ORDER*)(
				(UINT8*)EndOfGroup + EndOfGroup->Length + sizeof(UINT32)
			);
		}
		if (*(UINT8*)IndexPtr == *(UINT8*)&BbsIndex) return GroupStart;
        IndexPtr++;
	}
	return NULL;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   AdjustLegacyBootOptionPriorities
//
// Description: Go through the legacy dev order structure and adjust it ot match the
//              current boot priorities
//
// Input:       DLIST *BootOptionList - the master boot option list
//
// Output:      none
//
// Note: function only available, and used, if CSM_SUPPORT token is defined and enabled
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID AdjustLegacyBootOptionPriorities(){
	EFI_STATUS Status;
	UINTN DevOrderSize, OldDevOrderSize;
	LEGACY_DEVICE_ORDER *DevOrder=NULL, *OldDevOrder=NULL;
	DLINK *Link;
	UINT16 BootOptionNumber;
	UINT16 *IndexPtr;
	UINT16 *EndOfDeviceList;
    BOOT_OPTION *Option;
    UINT16 GroupSize=0;
    INT32 IndexInTheGroup=0;
    LEGACY_DEVICE_ORDER *CurrentGroup;

	Status = GetEfiVariable(
		L"LegacyDevOrder", &LegacyDevOrderGuid, NULL, 
		&DevOrderSize, &DevOrder
	);
	if(EFI_ERROR(Status) || DevOrderSize < sizeof(LEGACY_DEVICE_ORDER)) return ;
	Status = GetEfiVariable(
		L"OldLegacyDevOrder", &LegacyDevOrderGuid, NULL, 
		&OldDevOrderSize, &OldDevOrder
	);
	if(    EFI_ERROR(Status) 
		|| OldDevOrderSize!=DevOrderSize
		|| MemCmp(DevOrder,OldDevOrder, DevOrderSize)==0
	){
		pBS->FreePool(DevOrder);
		if (!EFI_ERROR(Status)) pBS->FreePool(OldDevOrder);
		return ;
	}

	BootOptionNumber = INVALID_BOOT_OPTION_NUMBER;
	IndexPtr = (UINT16*)DevOrder;
	EndOfDeviceList = (UINT16*)((UINT8*)IndexPtr+DevOrderSize);

	FOR_EACH_BOOT_OPTION(BootOptionList,Link,Option){
        INT32 NewIndexInTheGroup;
        LEGACY_DEVICE_ORDER *OldGroup;
        UINT16 BbsIndex;

        if ( !IsLegacyBootOption(Option) || Option->GroupHeader) continue;
		// this should never happen during the normal course of operation
		if (IndexPtr>=EndOfDeviceList) break; 
		// during the normal course of operation both conditions should
		// happen simultaneously 
		if (BootOptionNumber != Option->BootOptionNumber || GroupSize==0){
			BootOptionNumber = Option->BootOptionNumber;
			IndexPtr += GroupSize;
            CurrentGroup = (LEGACY_DEVICE_ORDER*)IndexPtr;
			GroupSize = (CurrentGroup->Length)/sizeof(UINT16)-1;
			IndexPtr = &CurrentGroup->Device[0];
            IndexInTheGroup = 0;
		}
        OldGroup = FindLegacyDeviceGroupByBbsIndex(OldDevOrder,DevOrderSize,*IndexPtr);
        BbsIndex = GetBbsIndexByPositionInTheGroup(OldGroup,IndexInTheGroup);
        NewIndexInTheGroup = FindPositionInTheGroupByBbsIndex(CurrentGroup,BbsIndex);

        Option->Priority += 
            (NewIndexInTheGroup-IndexInTheGroup)*DEFAULT_PRIORITY_INCREMENT;
		if ((CurrentGroup->Device[NewIndexInTheGroup] & 0xff00)!=0)
            Option->Attributes &= ~LOAD_OPTION_ACTIVE;
        else
            Option->Attributes |= LOAD_OPTION_ACTIVE;
		IndexPtr++;
		GroupSize--;
        IndexInTheGroup++;
	}
	pBS->FreePool(DevOrder);
	pBS->FreePool(OldDevOrder);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   UnmaskOrphanDevices
//
// Description: This function unmasks orphan devices.
//              The orphan legacy devices are masked by the MaskOrphanDevices function.
//              TSE does not like legacy boot options for devices that are not in the system.
//              To trick TSE we we are camouflaging such boot options by adding GUIDed device path.
//              The device path is added by MaskOrphanDevices function rigth before saving
//              and removed by UnmaskOrphanDevices right after reading
//
//
// Input:       DLIST *BootOptionList - the master boot option list
//
// Output:      none
//
// Note: function only available, and used, if CSM_SUPPORT token is defined and enabled
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID UnmaskOrphanDevices(){
	DLINK *Link;
    BOOT_OPTION *Option;
    VENDOR_DEVICE_PATH *MaskedDp;
    UINTN MaskedDpLength;

	FOR_EACH_BOOT_OPTION(BootOptionList,Link,Option){
        MaskedDp = (VENDOR_DEVICE_PATH*)Option->FilePathList;
        if (   MaskedDp->Header.Type != HARDWARE_DEVICE_PATH
            || MaskedDp->Header.SubType != HW_VENDOR_DP
            || guidcmp(&AmiMaskedDevicePathGuid, &MaskedDp->Guid) != 0
        ) continue;
        MaskedDpLength = DPLength(&MaskedDp->Header);
        if (Option->FilePathListLength <= MaskedDpLength) continue;
        Option->FilePathListLength -=MaskedDpLength;
        MemCpy(
            Option->FilePathList, (UINT8*)Option->FilePathList+MaskedDpLength,
            Option->FilePathListLength
        );
        if(!IsLegacyBootOption(Option) || Option->GroupHeader)
            Option->Attributes &= ~LOAD_OPTION_HIDDEN;
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   BuildLegacyDevOrderBuffer
//
// Description: Go through the master boot option list and create
//              memory representation of the legacy dev order variable
//
// Input:       DLIST *BootOptionList - the master boot option list
//
// Output:      none
//
// Note: function only available, and used, if CSM_SUPPORT token is defined and enabled
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID BuildLegacyDevOrderBuffer(
    LEGACY_DEVICE_ORDER **DevOrderBuffer, UINTN *BufferSize
){
	UINTN DevOrderSize;
	LEGACY_DEVICE_ORDER *DevOrder, *GroupPtr;
    UINT16 *DevPtr;
	DLINK *Link;
    UINT16 BootOptionNumber = INVALID_BOOT_OPTION_NUMBER;
    BOOT_OPTION *Option;

    if (DevOrderBuffer == NULL || BufferSize == NULL) return;
    if (BootOptionList->Size == 0)
        DevOrder = Malloc(sizeof(LEGACY_DEVICE_ORDER));
    else
        DevOrder = Malloc(BootOptionList->Size*sizeof(LEGACY_DEVICE_ORDER));
    GroupPtr = DevOrder;
    DevPtr = (UINT16*)DevOrder;

    FOR_EACH_BOOT_OPTION(BootOptionList,Link,Option){
		if ( !IsLegacyBootOption(Option) || Option->GroupHeader) continue;
        if (Option->BootOptionNumber!=BootOptionNumber){
            GroupPtr->Length = (UINT16)((UINT8*)DevPtr - (UINT8*)&GroupPtr->Length);
            GroupPtr = (LEGACY_DEVICE_ORDER*)DevPtr;
            BootOptionNumber = Option->BootOptionNumber;
            GroupPtr->Type = GetLegacyDevOrderType(Option);
            DevPtr = GroupPtr->Device;
        }
        if ((Option->Attributes&LOAD_OPTION_ACTIVE)==0)
            *DevPtr = Option->BbsIndex | 0xff00;
        else
            *DevPtr = Option->BbsIndex;
        DevPtr++;
    }
    GroupPtr->Length = (UINT16)((UINT8*)DevPtr - (UINT8*)&GroupPtr->Length);
    DevOrderSize = (UINT8*)DevPtr - (UINT8*)DevOrder;

	*DevOrderBuffer = DevOrder;
    *BufferSize = DevOrderSize;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   MaskOrphanDevices
//
// Description: This function masks orphan devices before saving them.
//              TSE does not like legacy boot options for devices that are not in the system.
//              To trick TSE we we are camouflaging such boot options by adding GUIDed device path.
//              The device path is added by MaskOrphanDevices function rigth before saving
//              and removed by UnmaskOrphanDevices right after reading
//
//
// Input:       DLIST *BootOptionList - the master boot option list
//
// Output:      none
//
// Note: function only available, and used, if CSM_SUPPORT token is defined and enabled
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID MaskOrphanDevices(){
	DLINK *Link;
    BOOT_OPTION *Option;
    BOOT_OPTION *GroupHeader = NULL;

    SortList(BootOptionList, ComparePriorityThenBootOptionNumber);
	FOR_EACH_BOOT_OPTION(BootOptionList,Link,Option){
        if (!IsLegacyBootOption(Option))
            continue;
        if (Option->GroupHeader){
            if (GroupHeader!=NULL) MaskFilePathList(GroupHeader);
            GroupHeader=Option;
            continue;
        }
        if (IsBootOptionWithDevice(Option)){
            if (Option->BootOptionNumber==GroupHeader->BootOptionNumber)
                GroupHeader=NULL;
            continue;
        }
        MaskFilePathList(Option);
    }
    if (GroupHeader!=NULL) MaskFilePathList(GroupHeader);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SaveLegacyDevOrder
//
// Description: Go through the master boot option list and use it to update the
//              legacy dev order variable
//
// Input:       DLIST *BootOptionList - the master boot option list
//
// Output:      none
//
// Note: function only available, and used, if CSM_SUPPORT token is defined and enabled
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID SaveLegacyDevOrder(){
	UINTN DevOrderSize;
	LEGACY_DEVICE_ORDER *DevOrder;

    SortList(BootOptionList, ComparePriorityThenBootOptionNumber);
    BuildLegacyDevOrderBuffer(&DevOrder, &DevOrderSize);
	pRS->SetVariable(
		L"LegacyDevOrder", 
        &LegacyDevOrderGuid,
		EFI_VARIABLE_NON_VOLATILE | 
#if RT_ACCESS_SUPPORT_IN_HPKTOOL
        EFI_VARIABLE_RUNTIME_ACCESS |
#endif
        EFI_VARIABLE_BOOTSERVICE_ACCESS,
        DevOrderSize,
        DevOrder
	);
	pRS->SetVariable(
		L"OldLegacyDevOrder", 
        &LegacyDevOrderGuid,
		EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS,
        DevOrderSize,
        DevOrder
	);
	pBS->FreePool(DevOrder);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CollectBbsDevice
//
// Description: Go through the bbs table and create a entry in the master boot order
//              list for each bbs table entry
//
// Input:       DLIST *BootDeviceList - the master boot list
//
// Output:       none
//
// Note: function only available, and used, if CSM_SUPPORT token is defined and enabled
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID CollectBbsDevices(DLIST *BootDeviceList){
    EFI_STATUS Status;
    EFI_LEGACY_BIOS_PROTOCOL *LegacyBios;
    UINT16 HddCount;
    UINT16 BbsCount;
    HDD_INFO *HddInfo;
    BBS_TABLE *BbsTable;
    UINT16 i;

    Status = pBS->LocateProtocol(&gEfiLegacyBiosProtocolGuid, NULL, &LegacyBios);
    if(EFI_ERROR(Status)) return ;
	LegacyBios->ShadowAllLegacyOproms(LegacyBios);
	LegacyBios->GetBbsInfo(LegacyBios, &HddCount, &HddInfo, &BbsCount, &BbsTable);

    for(i = 0; i < BbsCount; i++){
		if(BbsTable[i].BootPriority == 0xffff) continue;
        CreateBootDevice(
            BootDeviceList,
            (EFI_HANDLE)*(UINTN*)&BbsTable[i].IBV1,
            i,&BbsTable[i]
        );
    }
}

#endif //#ifdef CSM_SUPPORT

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CollectProtocolDevices
//
// Description: Collect a list of all handles with a particular protocol installed
//              on them and create a boot device for each handle.
//
// Input:       DLIST *BootDeviceList - the master boot list that needs boot devices
//              added to it.
//              EFI_GUID *ProtocolGuid - the protocol to use when getting a list of
//              device handles
//
// Output:      none
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID CollectProtocolDevices(DLIST *BootDeviceList, EFI_GUID *ProtocolGuid){
    EFI_HANDLE *Devices;
    UINTN NumberOfDevices;
	EFI_STATUS Status;
	UINTN i;

    Status = pBS->LocateHandleBuffer(
        ByProtocol,ProtocolGuid, NULL, 
        &NumberOfDevices, &Devices
    );
    if (EFI_ERROR(Status)) return;
	for(i=0; i<NumberOfDevices; i++){
		CreateBootDevice(BootDeviceList,Devices[i],INVALID_BBS_INDEX,NULL);
	}
	pBS->FreePool(Devices);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CollectBootDevices
//
// Description: Helper function to generate a master boot list based on the
//              load file protocol, the simple file system protocol and, if
//              CSM support is enabled, the legacy bbs table
//
// Input:       DLIST *BootDeviceList
//
// Output:      
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID CollectBootDevices(){
	CollectProtocolDevices(BootDeviceList,&gEfiLoadFileProtocolGuid);
	CollectProtocolDevices(BootDeviceList,&gEfiSimpleFileSystemProtocolGuid);
#ifdef CSM_SUPPORT
	CollectBbsDevices(BootDeviceList);
#endif
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   IsUefiHddBootDevice
//
// Description: Determine if this boot device is a UEFI HDD 
//
// Input:       BOOT_DEVICE *Device - the device in question
//
// Output:      BOOLEAN - TRUE - Device is a UEFI HDD Boot Device and it should
//                              be removed from the boot order list
//                        FALSE - Device is not a UEFI hdd and it should be left
//                              in the boot order
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN IsUefiHddBootDevice(BOOT_DEVICE *Device){
    EFI_BLOCK_IO_PROTOCOL *BlkIo;
    EFI_STATUS Status;

    if (   Device->DeviceHandle == INVALID_HANDLE
        || Device->BbsEntry != NULL
    ) return FALSE;


    Status=pBS->HandleProtocol(
        Device->DeviceHandle, &gEfiBlockIoProtocolGuid, &BlkIo
    );
    if (EFI_ERROR(Status)) return FALSE;
    return !BlkIo->Media->RemovableMedia;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   FilterBootDeviceList
//
// Description: Master filter handler.  Function will call all ELINK functions
//              linked into the BootOptionBootDeviceFilteringFunctions list.
//              If any ELINK function returns FALSE, the device will be removed
//              from the function list
//
// Input:       DLIST *BootDeviceList - the full boot order list
//
// Output:      none
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID FilterBootDeviceList(){
// Filter Devices 
    BOOT_DEVICE *Device;
    DLINK *Link;

    FOR_EACH_BOOT_DEVICE(BootDeviceList, Link, Device){
	    UINT32 i;
	    for(i=0; FilteringFunction[i]!=NULL; i++)
		    if (FilteringFunction[i](Device)){
                DeleteBootDevice(BootDeviceList, Device);
                break;
            }
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   LocateDevicePathTest
//
// Description: 
//
// Input:       EFI_DEVICE_PATH_PROTOCOL *OptionalDevicePath -
//              BOOT_DEVICE *Device - the device
//
// Output:      
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN LocateDevicePathTest(EFI_DEVICE_PATH_PROTOCOL *OptionDevicePath, BOOT_DEVICE *Device){
	EFI_STATUS Status;
	EFI_HANDLE Handle;

	if (Device->DeviceHandle==INVALID_HANDLE) return FALSE;
    Status=pBS->LocateDevicePath(
		&gEfiDevicePathProtocolGuid, &OptionDevicePath, &Handle
	);
	if (EFI_ERROR(Status)) return FALSE;
    if (Handle != Device->DeviceHandle) return FALSE;
    if (isEndNode(OptionDevicePath)) return TRUE;
    if (OptionDevicePath->Type != MEDIA_DEVICE_PATH) return FALSE;
    return    OptionDevicePath->SubType==MEDIA_FILEPATH_DP
           || OptionDevicePath->SubType==MEDIA_FV_FILEPATH_DP;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   PartitionDevicePathtest
//
// Description: 
//
// Input:       EFI_DEVICE_PATH_PROTOCOL *OptionDevicePath - 
//              BOOT_DEVICE *Device - 
//
// Output:      
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN PartitionDevicePathTest(
	EFI_DEVICE_PATH_PROTOCOL *OptionDevicePath, BOOT_DEVICE *Device
){
	EFI_STATUS Status;
	EFI_BLOCK_IO_PROTOCOL *BlockIo;
	EFI_DEVICE_PATH_PROTOCOL *PartitionDevicePath;
	HARDDRIVE_DEVICE_PATH* BootParitionDevicePath;
	HARDDRIVE_DEVICE_PATH* PartitionNode;

	if (Device->DeviceHandle==INVALID_HANDLE) return FALSE;
	if (    OptionDevicePath->Type!=MEDIA_DEVICE_PATH 
         || OptionDevicePath->SubType!=MEDIA_HARDDRIVE_DP
    ) return FALSE;
	BootParitionDevicePath  = (HARDDRIVE_DEVICE_PATH*)OptionDevicePath;
	Status = pBS->HandleProtocol(
		Device->DeviceHandle,&gEfiBlockIoProtocolGuid,&BlockIo
	);
	if (EFI_ERROR(Status)) return FALSE;
    // if this is not partition, continue
	if (!BlockIo->Media->LogicalPartition) return FALSE;
	Status = pBS->HandleProtocol(
		Device->DeviceHandle,&gEfiDevicePathProtocolGuid,&PartitionDevicePath
	);
    if (EFI_ERROR(Status)) return FALSE;
	// Get last node of the device path. It should be partition node
	PartitionNode = (HARDDRIVE_DEVICE_PATH*)DPGetLastNode(PartitionDevicePath);
	//Check if our partition matches Boot partition
	if (   PartitionNode->Header.Type!=MEDIA_DEVICE_PATH 
		|| PartitionNode->Header.SubType!=MEDIA_HARDDRIVE_DP
	) return FALSE;
	if (   PartitionNode->PartitionNumber==BootParitionDevicePath->PartitionNumber 
		&& PartitionNode->SignatureType==BootParitionDevicePath->SignatureType 
		&& !MemCmp(PartitionNode->Signature,BootParitionDevicePath->Signature,16) 
	){
		return TRUE;
	}
	return FALSE;
}

UINT8 GetDevicePathSubtype(EFI_DEVICE_PATH_PROTOCOL *Dp, UINT8 Type){
    UINT8 SubType;

    if (Dp == NULL) return 0;
    SubType = 0;

    for( ; !(isEndNode(Dp)); Dp=NEXT_NODE(Dp))
        if (Dp->Type == Type) SubType = Dp->SubType;
    return SubType;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   DeviceTypeDevicePathTest
//
// Description: 
//
// Input:       EFI_DEVICE_PATH_PROTOCOL *Dp - The device path to search
//              Type Device - The type of node to search for
//
// Output:      EFI_DEVICE_PATH_PROTOCOL*
//                  NULL - No node was found
//                  Non-null - A node was found, and the pointer was returned
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_DEVICE_PATH_PROTOCOL* GetDevicePathNodeOfType(EFI_DEVICE_PATH_PROTOCOL *Dp, UINT8 Type){
	EFI_DEVICE_PATH_PROTOCOL *Node = NULL;

    if (Dp == NULL) return NULL;

    for( ; !(isEndNode(Dp)); Dp=NEXT_NODE(Dp))
        if (Dp->Type == Type) Node = Dp;
    return Node;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   DeviceTypeDevicePathTest
//
// Description: 
//
// Input:       EFI_DEVICE_PATH_PROTOCOL *OptionalDevicePath -
//              BOOT_DEVICE *Device - the device
//
// Output:      
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN DeviceTypeDevicePathTest(EFI_DEVICE_PATH_PROTOCOL *OptionDevicePath, BOOT_DEVICE *Device){
	EFI_STATUS Status;
    EFI_DEVICE_PATH_PROTOCOL *Dp;
    UINT8 DeviceInterface, OptionInterface;
    EFI_DEVICE_PATH_PROTOCOL *DeviceMedia, *OptionMedia;

	if (Device->DeviceHandle==INVALID_HANDLE) return FALSE;

    Status=pBS->HandleProtocol(
        Device->DeviceHandle, &gEfiDevicePathProtocolGuid, &Dp
    );
    if (EFI_ERROR(Status)) return FALSE;

    DeviceInterface = GetDevicePathSubtype(
        Dp, MESSAGING_DEVICE_PATH
    );
    //If DeviceInterface is 0, the interface type is unknown.
    //Can't do the matching.
    if (DeviceInterface == 0) return FALSE;
    if (DeviceInterface == MSG_SATA_DP)
        DeviceInterface = MSG_ATAPI_DP;
    OptionInterface = GetDevicePathSubtype(
        OptionDevicePath, MESSAGING_DEVICE_PATH
    );
    if (OptionInterface == MSG_SATA_DP)
        OptionInterface = MSG_ATAPI_DP;
    if (DeviceInterface != OptionInterface) return FALSE;

    DeviceMedia = GetDevicePathNodeOfType(Dp,MEDIA_DEVICE_PATH);
    OptionMedia = GetDevicePathNodeOfType(OptionDevicePath,MEDIA_DEVICE_PATH);
    if (   DeviceMedia != NULL && OptionMedia != NULL
    	&& NODE_LENGTH(DeviceMedia) == NODE_LENGTH(OptionMedia)
    	&& MemCmp(DeviceMedia,OptionMedia,NODE_LENGTH(DeviceMedia)) == 0
    ){
        NormalizeBootOptionDevicePath = TRUE;
        return TRUE;
    }

    return FALSE;
}

#define MSG_USB_DP_PRESENT            0x1
#define MSG_USB_CLASS_DP_PRESENT      0x2
#define MSG_USB_WWID_CLASS_DP_PRESENT 0x4

BOOLEAN IsUsbDp(
    IN EFI_DEVICE_PATH_PROTOCOL *Dp,
    OUT UINT32 *AvailableNodes OPTIONAL
)
{
    UINT32 Flags = 0;

    for( ; !(isEndNode(Dp)); Dp = NEXT_NODE(Dp)) {
        if(Dp->Type == MESSAGING_DEVICE_PATH) {
            if(Dp->SubType == MSG_USB_DP) {
                Flags |= MSG_USB_DP_PRESENT;
                continue;
            }
            if(Dp->SubType == MSG_USB_CLASS_DP) {
                Flags |= MSG_USB_CLASS_DP_PRESENT;
                continue;
            }
            if(Dp->SubType == MSG_USB_WWID_CLASS_DP) {
                Flags |= MSG_USB_WWID_CLASS_DP_PRESENT;
            }
        }
    }
    if(AvailableNodes != NULL)
        *AvailableNodes = Flags;

    return (Flags != 0) ? TRUE : FALSE;
}

BOOLEAN UsbClassDevicePathTest(
    IN EFI_DEVICE_PATH_PROTOCOL *OptionDevicePath, 
    IN BOOT_DEVICE *Device
)
{
    EFI_STATUS Status;
    USB_CLASS_DEVICE_PATH *UsbDp;
    EFI_DEVICE_PATH_PROTOCOL *DevDp;
    UINT32 AvailableNodes;

    if(OptionDevicePath->Type != MESSAGING_DEVICE_PATH ||
       OptionDevicePath->SubType != MSG_USB_CLASS_DP)
        return FALSE;           //boot option is not USB class boot option

    Status = pBS->HandleProtocol(Device->DeviceHandle, &gEfiDevicePathProtocolGuid, &DevDp);
    if(EFI_ERROR(Status))
        return FALSE;           //device doesn't support EFI_DEVICE_PATH protocol

    if(!IsUsbDp(DevDp, &AvailableNodes))
        return FALSE;           //device is not a USB device

    UsbDp = (USB_CLASS_DEVICE_PATH *)OptionDevicePath;
    return (UsbDp->VendorId == 0xffff &&
                UsbDp->ProductId == 0xffff &&
                UsbDp->DeviceClass == 0xff &&
                UsbDp->DeviceSubClass == 0xff &&
                UsbDp->DeviceProtocol == 0xff) ? TRUE : FALSE;

//TODO
//add USB class specific comparison, once USB driver produces required device path node
}

#ifdef CSM_SUPPORT
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   BbsDevicePathTest
//
// Description: 
//
// Input:       EFI_DEVICE_PATH_PROTOCOL *OptionDevicePath -
//              BOOT_DEVICE *Device - 
//
// Output:      
//
// Note: function only available, and used, if CSM_SUPPORT token is defined and enabled
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN BbsDevicePathTest(
	EFI_DEVICE_PATH_PROTOCOL *OptionDevicePath, BOOT_DEVICE *Device
){
    BBS_BBS_DEVICE_PATH *BbsDp;
	if (OptionDevicePath->Type!=BBS_DEVICE_PATH) return FALSE;
	if (Device->BbsEntry==NULL) return FALSE;
    BbsDp = (BBS_BBS_DEVICE_PATH*)OptionDevicePath;
	return     BbsDp->DeviceType == GetBbsEntryDeviceType(Device->BbsEntry);

}

UINT8 GetBbsDeviceInstance(	UINT16 BbsIndex, BBS_TABLE *BbsEntry){
	UINT8 Bus;
	UINT8 Device;
	UINT8 Function;
	UINT8 Class;
    UINT8 SubClass;
    UINT16 Index;

    if (BbsIndex==0) return 0;
    Bus = BbsEntry->Bus;
    Device = BbsEntry->Device;
    Function = BbsEntry->Function;
    Class = BbsEntry->Class;
    SubClass = BbsEntry->SubClass;
    BbsEntry -= BbsIndex;

    for(  Index = BbsIndex-1
        ; Index != 0xFFFF
        ; Index--
    ){
        if(    Bus != BbsEntry[Index].Bus
            || Device != BbsEntry[Index].Device
            || Function != BbsEntry[Index].Function
            || Class != BbsEntry[Index].Class
            || SubClass != BbsEntry[Index].SubClass
        ) return BbsIndex - 1 - Index;
    }
    return BbsIndex - 1 - Index;
}

BOOLEAN AmiBbsDevicePathTest(
	EFI_DEVICE_PATH_PROTOCOL *OptionDevicePath, BOOT_DEVICE *Device
){
    AMI_BBS_DEVICE_PATH *AmiBbsDp;

	if (Device->BbsEntry==NULL) return FALSE;
    AmiBbsDp = (AMI_BBS_DEVICE_PATH*)OptionDevicePath;
    return AmiBbsDp->Header.Header.Type == HARDWARE_DEVICE_PATH
        && AmiBbsDp->Header.Header.SubType == HW_VENDOR_DP
        && guidcmp(&AmiBbsDevicePathGuid, &AmiBbsDp->Header.Guid) == 0
        && AmiBbsDp->Bus == Device->BbsEntry->Bus
        && AmiBbsDp->Device == Device->BbsEntry->Device
        && AmiBbsDp->Function == Device->BbsEntry->Function
        && AmiBbsDp->Class == Device->BbsEntry->Class
        && AmiBbsDp->SubClass == Device->BbsEntry->SubClass
        && AmiBbsDp->Instance == GetBbsDeviceInstance(Device->BbsIndex,Device->BbsEntry);
    ;
}
#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   MatchDevicePathToDevice
//
// Description: 
//
// Input:       EFI_DEVICE_PATH_PROTOCOL *OptionDp -
//              BOOT_DEVICE *Device - 
//
// Output:      
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN MatchDevicePathToDevice(EFI_DEVICE_PATH_PROTOCOL *OptionDp, BOOT_DEVICE *Device){
	UINT32 i;
	for(i=0; DpMatchingFunction[i]!=NULL; i++)
		if (DpMatchingFunction[i](OptionDp,Device)) return TRUE;
	return FALSE;
}

BOOLEAN MatchUefiFloppyDrive(BOOT_OPTION *Option, BOOT_DEVICE *Device){
    // This function makes sure that UEFI boot option is not matched
    // with the legacy boot device.
    // A legacy boot device is a device with a valid BbsIndex.
    // A UEFI boot option is a boot option with FilePathList does not start 
    // with the BBS device path.
    // When this funciton returns FALSE, the matching process fails.
    // The function is executed via the BootOptionMatchingFunctions eLink.
    return Device->BbsIndex==INVALID_BBS_INDEX || IsLegacyBootOption(Option);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   
//
// Description: 
//
// Input:       
//
// Output:      
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN MatchBootOpionToDevice(BOOT_OPTION *Option, BOOT_DEVICE *Device){
	UINT32 i;
    //all the functions have to return TRUE
	for(i=0; MatchingFunction[i]!=NULL; i++)
		if (!MatchingFunction[i](Option,Device)) return FALSE;
	return TRUE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   MatchBootOptionsToDevices
//
// Description: 
//
// Input:       DLIST *BootOptionList - 
//              DLIST *BootDeviceList - 
//
// Output:      
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID MatchBootOptionsToDevices(){
	DLINK *OptionLink, *DeviceLink;
    BOOT_OPTION *Option;
    BOOT_DEVICE *Device;

    FOR_EACH_BOOT_DEVICE(BootDeviceList,DeviceLink,Device){
        BOOLEAN DeviceIsMatched = FALSE;
        FOR_EACH_BOOT_OPTION(BootOptionList,OptionLink,Option){
			EFI_DEVICE_PATH_PROTOCOL *OptionDp = Option->FilePathList;
			EFI_DEVICE_PATH_PROTOCOL *DpInstance;
            //Skip the group headers and the options that have already been matched.
            if (Option->GroupHeader || IsBootOptionWithDevice(Option)) continue;
			do {
                EFI_DEVICE_PATH_PROTOCOL *TmpDp = OptionDp;
				while(   (DpInstance = DPNextInstance(&TmpDp,NULL))!=NULL
					  && MatchDevicePathToDevice(DpInstance,Device)
				) pBS->FreePool(DpInstance);

				OptionDp = (EFI_DEVICE_PATH_PROTOCOL*)((UINT8*)OptionDp+DPLength(OptionDp));
			} while(   Option->FwBootOption && DpInstance==NULL 
				    && (UINT8*)OptionDp<(UINT8*)Option->FilePathList+Option->FilePathListLength
			);
			if (DpInstance == NULL && MatchBootOpionToDevice(Option,Device)){
				UpdateBootOptionWithBootDeviceInfo(Option,Device);
                DeviceIsMatched = TRUE;
                // Legacy device can't be matched with more than one boot option.
                if (IsLegacyBootOption(Option)) break;
			}else{
				if (DpInstance!=NULL) pBS->FreePool(DpInstance);
			}
		}
        if (DeviceIsMatched) DeleteBootDevice(BootDeviceList, Device);
	}
}

VOID DeleteUnmatchedUefiHddBootDevices(){
    BOOT_DEVICE *Device;
    DLINK *Link;

    FOR_EACH_BOOT_DEVICE(BootDeviceList, Link, Device){
        if (IsUefiHddBootDevice(Device)){
            DeleteBootDevice(BootDeviceList, Device);
        }
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetPhysicalBlockIoHandle
//
// Description: 
//
// Input:       EFI_HANDLE *BlockIoHandle - 
//
// Output:      
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_HANDLE GetPhysicalBlockIoHandle(EFI_HANDLE BlockIoHandle){
    EFI_BLOCK_IO_PROTOCOL *BlkIo;
    EFI_DEVICE_PATH_PROTOCOL *DevicePath, *Dp;
    EFI_STATUS Status;
    EFI_HANDLE Handle = BlockIoHandle;

    Status=pBS->HandleProtocol(
        Handle, &gEfiBlockIoProtocolGuid, &BlkIo
    );
    if (EFI_ERROR(Status)) return Handle;
    if (!BlkIo->Media->LogicalPartition) return Handle;
    Status=pBS->HandleProtocol(
        Handle, &gEfiDevicePathProtocolGuid, &DevicePath
    );
    if (EFI_ERROR(Status)) return Handle;
    Dp=DevicePath;
    while(BlkIo->Media->LogicalPartition){
        EFI_DEVICE_PATH_PROTOCOL *PrevDp=Dp;
        //We need to cut Devicepath node to get Phisycal Partition
        Dp=DPCut(PrevDp);
        if (PrevDp!=DevicePath) pBS->FreePool(PrevDp);
        if (Dp == NULL) break;
        PrevDp=Dp;
        Status=pBS->LocateDevicePath(
            &gEfiBlockIoProtocolGuid,&PrevDp,&Handle
        );
        if(EFI_ERROR(Status)) break;
        Status=pBS->HandleProtocol(
            Handle, &gEfiBlockIoProtocolGuid, &BlkIo
        );
        if(EFI_ERROR(Status)) break;
    } 
    if (Dp!=NULL && Dp!=DevicePath) pBS->FreePool(Dp);
    //if physical Block I/O handle is not found, return original handle
    return (BlkIo->Media->LogicalPartition) ? BlockIoHandle : Handle;
}

EFI_HANDLE GetPhysicalNetworkCardHandle(EFI_HANDLE Handle, UINT8 *IpType){
    EFI_LOAD_FILE_PROTOCOL *LoadFile;
    EFI_DEVICE_PATH_PROTOCOL *DevicePath, *Dp;
    EFI_STATUS Status;

    Status=pBS->HandleProtocol(
        Handle, &gEfiLoadFileProtocolGuid, &LoadFile
    );
    if (EFI_ERROR(Status)) return Handle;

    Status=pBS->HandleProtocol(
        Handle, &gEfiDevicePathProtocolGuid, &DevicePath
    );
    if (EFI_ERROR(Status)) return Handle;
    for(Dp=DevicePath; !(isEndNode(Dp)); Dp=NEXT_NODE(Dp)){
        if (Dp->Type == MESSAGING_DEVICE_PATH && Dp->SubType == MSG_MAC_ADDR_DP){
            EFI_HANDLE NewHandle;
            EFI_DEVICE_PATH_PROTOCOL *TmpDevicePath, *TmpDp;

            Dp=NEXT_NODE(Dp);
            if (isEndNode(Dp)) break;
            if ( IpType != NULL) *IpType = GetDevicePathSubtype(Dp, MESSAGING_DEVICE_PATH);
            TmpDevicePath = TmpDp = DPCopy(DevicePath);
            Dp = (EFI_DEVICE_PATH_PROTOCOL*)((UINT8*)Dp - (UINT8*)DevicePath + (UINT8*)TmpDp);
            Dp->Type = END_DEVICE_PATH;
	        Dp->SubType = END_ENTIRE_SUBTYPE;
            SET_NODE_LENGTH(Dp,sizeof(*Dp));
            Status = pBS->LocateDevicePath(&gEfiDevicePathProtocolGuid, &TmpDp, &NewHandle);
            if (!EFI_ERROR(Status) && TmpDp==Dp) Handle = NewHandle;
            pBS->FreePool(TmpDevicePath);
            break;
        }
    }
    return Handle;    
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   RemoveTrailingSpaces
//
// Description: 
//
// Input:       CHAR16 *Name - 
//              UINTN NumberOfCharacters -
//
// Output:      
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINTN RemoveTrailingSpaces(CHAR16 *Name, UINTN NumberOfCharacters){
    //remove trailing spaces
    while(NumberOfCharacters>0 && Name[NumberOfCharacters-1]==L' ') 
        NumberOfCharacters--;
    Name[NumberOfCharacters]=0;
    return NumberOfCharacters;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ConstructBootOptionNameByHandle
//
// Description: 
//
// Input:       BOOT_OPTION *Option - 
//              CHAR16 *Name -
//              UINTN NameSize - 
//
// Output:      
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINTN ConstructBootOptionNameByHandle(
    BOOT_OPTION *Option, CHAR16 *Name, UINTN NameSize
){
    EFI_HANDLE Handle;
    CHAR16 *ControllerName;
    CHAR16 *Prefix = L"";
    UINTN  NumberOfCharacters;
    UINT8  IpType;

    if (Option->DeviceHandle == INVALID_HANDLE) return 0;

    //Name from Controller Handle
    Handle = GetPhysicalBlockIoHandle(Option->DeviceHandle);
    if (Handle==Option->DeviceHandle){
        EFI_HANDLE OldHandle = Handle;
        Handle = GetPhysicalNetworkCardHandle(Option->DeviceHandle,&IpType);
        if (Handle != OldHandle) {
            //TODO: use string token
            if (IpType == MSG_IPv4_DP) Prefix=L"IP4 ";
            else if (IpType == MSG_IPv6_DP) Prefix=L"IP6 ";
        }
    }
    if (!GetControllerName(Handle, &ControllerName)) return 0;
    NumberOfCharacters = Swprintf_s(Name, NameSize, L"%s%s",Prefix,ControllerName);
    return RemoveTrailingSpaces(Name, NumberOfCharacters);
}

#ifdef CSM_SUPPORT
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ConstructBootOptionNameByBbsDescription
//
// Description: 
//
// Input:       BOOT_OPTION *Option -
//              CHAR16 *Name - 
//              UINTN NameSize - 
//
// Output:      
//
// Note: function only available, and used, if CSM_SUPPORT token is defined and enabled
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINTN ConstructBootOptionNameByBbsDescription(
    BOOT_OPTION *Option, CHAR16 *Name, UINTN NameSize
){
    CHAR8 *AsciiNameStr;
    UINTN  NumberOfCharacters;

    if (Option->BbsEntry == NULL) return 0;

    //Name from BBS table
    AsciiNameStr = (CHAR8*)(UINTN)(
          (Option->BbsEntry->DescStringSegment<<4)
        + Option->BbsEntry->DescStringOffset
    );
    if (AsciiNameStr == NULL) return 0;
    for(  NumberOfCharacters = 0
        ; NumberOfCharacters < NameSize-1
        ; NumberOfCharacters++
    ){
        if (!AsciiNameStr[NumberOfCharacters]) break;
        Name[NumberOfCharacters] = AsciiNameStr[NumberOfCharacters];
    }
    Name[NumberOfCharacters]=0;
    return RemoveTrailingSpaces(Name, NumberOfCharacters);
}
#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   DevicePathToNameString
//
// Description: 
//
// Input:       EFI_DEVICE_PATH_PROTOCOL *DevicePath - 
//              CHAR16 *Name - 
//              UINTN NameSize - 
//
// Output:      
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINTN DevicePathToNameString(
    EFI_DEVICE_PATH_PROTOCOL *DevicePath, CHAR16 *Name, UINTN NameSize
){
    STRING_REF StrToken;
    EFI_DEVICE_PATH_PROTOCOL *Dp;
    UINTN BufferSize;
    UINTN NumberOfCharacters = 0;

    for(  Dp = DevicePath; !(isEndNode(Dp)); Dp=NEXT_NODE(Dp)){ 
        StrToken = DevicePathNodeToStrRef(Dp);
        BufferSize = (NameSize-NumberOfCharacters)*sizeof(CHAR16);
        if (   StrToken!= INVALID_STR_TOKEN
            && !EFI_ERROR(HiiLibGetString(
                    HiiHandle,StrToken,&BufferSize, &Name[NumberOfCharacters]
                ))
            && BufferSize != 0
        ){
            NumberOfCharacters += (BufferSize-1)/sizeof(CHAR16);
            if (NumberOfCharacters < NameSize - 1){
                Name[NumberOfCharacters++]=L' ';
            }
        }
    }//for ;
    if (NumberOfCharacters !=0 ) Name[NumberOfCharacters]=0;
    return NumberOfCharacters;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ConstructBootOptionNameByHandleDevicePath
//
// Description: 
//
// Input:       BOOT_OPTION *Option -
//              CHAR16 *Name -
//              UINTN NameSize -
//
// Output:      
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINTN ConstructBootOptionNameByHandleDevicePath(
    BOOT_OPTION *Option, CHAR16 *Name, UINTN NameSize
){
    EFI_DEVICE_PATH_PROTOCOL *DevicePath;

    if (Option->DeviceHandle == INVALID_HANDLE) return 0;
     //Name from Device Path

    if (!EFI_ERROR(pBS->HandleProtocol(
        Option->DeviceHandle, &gEfiDevicePathProtocolGuid, &DevicePath
    ))) return DevicePathToNameString(DevicePath, Name, NameSize);
    return 0;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ConstructBootOptionNameByFilePathList
//
// Description: 
//
// Input:       BOOT_OPTION *Option -
//              CHAR16 *Name -
//              UINTN NameSize -
//
// Output:      
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINTN ConstructBootOptionNameByFilePathList(
    BOOT_OPTION *Option, CHAR16 *Name, UINTN NameSize
){
    if (Option->FilePathList == NULL) return 0;
    return DevicePathToNameString(Option->FilePathList, Name, NameSize);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ConstructBootOptionBaseName
//
// Description: 
//
// Input:       BOOT_OPTION *Option - 
//              CHAR16 *Name -
//              UINTN NameSize -
//
// Output:      
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINTN ConstructBootOptionBaseName(BOOT_OPTION *Option, CHAR16 *Name, UINTN NameSize){
    UINTN NumberOfCharacters;
	UINT32 i;

	for(i=0; BuildNameFunctions[i]!=NULL; i++){
        NumberOfCharacters = BuildNameFunctions[i](Option, Name, NameSize);
        if ( NumberOfCharacters!=0 ) return NumberOfCharacters;
    }

    return 0;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ConstructBootOptionName
//
// Description: 
//
// Input:       BOOT_OPTION *Option -
//
// Output:      
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINTN ConstructBootOptionName(BOOT_OPTION *Option){
    CHAR16 Name[1024];
    UINTN Length = sizeof(Name)/sizeof(CHAR16);
    UINTN NumberOfCharacters, BaseNameLength;

    NumberOfCharacters = ConstructBootOptionNamePrefix(Option,Name,Length);
    Length -= NumberOfCharacters;
    BaseNameLength = ConstructBootOptionBaseName(
        Option, &Name[NumberOfCharacters], Length
    );
    NumberOfCharacters += BaseNameLength;
    if (BaseNameLength==0){
        //Unknown Device
        UINTN BufferSize = Length*sizeof(CHAR16);
        if (EFI_ERROR(
                HiiLibGetString(
                    HiiHandle, UnknownDeviceToken, &BufferSize, &Name[NumberOfCharacters]
                )
        )){
            NumberOfCharacters += Swprintf_s(
                &Name[NumberOfCharacters], Length, L"Unknown Device"
            );
        }else{
            NumberOfCharacters += (BufferSize-1)/sizeof(CHAR16);
        }
        Length -= NumberOfCharacters;
    }
    NumberOfCharacters += ConstructBootOptionNameSuffix(
        Option, &Name[NumberOfCharacters], Length
    );
    //convert number of characters into string buffer size
    Length = (NumberOfCharacters+1)*sizeof(CHAR16);    
    Option->Description = Malloc(Length);
    MemCpy(Option->Description,Name,Length);
    return NumberOfCharacters;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ConstructBootOptionNameBySerialNumber
//
// Description: 
//
// Input:       BOOT_OPTION *Option - 
//              CHAR16 *Name -
//              UINTN NameSize - 
//
// Output:      
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINTN ConstructAtaBootOptionNameBySerialNumber(
    BOOT_OPTION *Option, CHAR16 *Name, UINTN NameSize
){
    static EFI_GUID DiskInfoGuid = EFI_DISK_INFO_PROTOCOL_GUID;
    EFI_HANDLE Handle;
    UINTN  NumberOfCharacters;
    EFI_DISK_INFO_PROTOCOL *DiskInfo;
    EFI_STATUS Status;
    UINT16 IdentifyData[256];
    UINT32 Size;
    CHAR8 SerialNumber[21];

    if (Option->DeviceHandle == INVALID_HANDLE) return 0;

    Handle = GetPhysicalBlockIoHandle(Option->DeviceHandle);
    Status = pBS->HandleProtocol(
        Handle, &DiskInfoGuid, &DiskInfo
    );
    if (EFI_ERROR(Status)) return 0;
    Size = sizeof(IdentifyData);
    Status = DiskInfo->Identify ( DiskInfo, IdentifyData, &Size );
    if (EFI_ERROR(Status)) return 0;
    MemCpy(SerialNumber, IdentifyData+10, 20);
    SerialNumber[20] = 0;
    NumberOfCharacters = Swprintf_s(Name, NameSize, L"%S", SerialNumber);
    return NumberOfCharacters;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ConstructUsbBootOptionNameBySerialNumber
//
// Description: 
//
// Input:       BOOT_OPTION *Option - 
//              CHAR16 *Name -
//              UINTN NameSize - 
//
// Output:      
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINTN ConstructUsbBootOptionNameBySerialNumber(
    BOOT_OPTION *Option, CHAR16 *Name, UINTN NameSize
){

    EFI_HANDLE Handle;
    UINTN  NumberOfCharacters;
    EFI_STATUS Status;

	EFI_USB_IO_PROTOCOL *UsbIo = NULL;
	EFI_USB_DEVICE_DESCRIPTOR DevDesc = {0};
	CHAR16 *UsbSerialNumber=NULL;
	EFI_DEVICE_PATH_PROTOCOL *DevicePath=NULL;

    if (Option->DeviceHandle == INVALID_HANDLE) return 0;

    Handle = GetPhysicalBlockIoHandle(Option->DeviceHandle);

	Status = pBS->HandleProtocol(Handle, &gEfiUsbIoProtocolGuid, &UsbIo);
	if(EFI_ERROR(Status)) return 0;
	Status = UsbIo->UsbGetDeviceDescriptor(UsbIo, &DevDesc);
	if(EFI_ERROR(Status)) return 0;

    if (DevDesc.StrSerialNumber) {
            Status = UsbIo->UsbGetStringDescriptor(UsbIo, 0x0409, DevDesc.StrSerialNumber, &UsbSerialNumber);      
			if(EFI_ERROR(Status)) return 0;
			pBS->CopyMem( Name, UsbSerialNumber, (Wcslen(UsbSerialNumber)+1)*2 );
			NumberOfCharacters = Wcslen(UsbSerialNumber);
    		return NumberOfCharacters;
	}
	return 0;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ConstructInternalBootOptionName
//
// Description: 
//
// Input:       BOOT_OPTION *Option -
//
// Output:      
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINTN ConstructInternalBootOptionName(
    BOOT_OPTION *Option, CHAR16 *Name, UINTN NameSize
){
    static CONSTRUCT_BOOT_OPTION_NAME *IntBuildNameFunctions[] = {
        ConstructAtaBootOptionNameBySerialNumber,
		ConstructUsbBootOptionNameBySerialNumber,
        ConstructBootOptionNameByHandle,
#ifdef CSM_SUPPORT
        ConstructBootOptionNameByBbsDescription,
#endif
        NULL
    };
    UINTN NumberOfCharacters;
	UINT32 i;

	for(i=0; IntBuildNameFunctions[i]!=NULL; i++){
        NumberOfCharacters = IntBuildNameFunctions[i](Option, Name, NameSize);
        if ( NumberOfCharacters!=0 ) return NumberOfCharacters;
    }

    return 0;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ConstructInternalDeviceName
//
// Description: 
//
// Input:       BOOT_OPTION *Option -
//
// Output:      
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINTN ConstructInternalDeviceName(
    BOOT_DEVICE *Device, CHAR16 *Name, UINTN NameSize
){
    static BOOT_OPTION BootOption = {
    	{NULL,NULL}, LOAD_OPTION_ACTIVE, NULL, NULL, 0, NULL, 0,
        INVALID_BOOT_OPTION_NUMBER, LOWEST_BOOT_OPTION_PRIORITY,
        UNASSIGNED_HIGHEST_TAG,
        INVALID_HANDLE, INVALID_BBS_INDEX, NULL, TRUE, FALSE
    };
	UpdateBootOptionWithBootDeviceInfo(&BootOption,Device);
	return ConstructInternalBootOptionName(&BootOption, Name, NameSize);
}

BOOLEAN AmiDeviceNameDevicePathTest(
	EFI_DEVICE_PATH_PROTOCOL *OptionDevicePath, BOOT_DEVICE *Device
){
    AMI_DEVICE_NAME_DEVICE_PATH *NameDp;
    CHAR16 Name[1024];
    UINTN Size = sizeof(Name)/sizeof(CHAR16);
    UINTN NumberOfCharacters;

    NameDp = (AMI_DEVICE_NAME_DEVICE_PATH*)OptionDevicePath;
    if(    NameDp->Header.Header.Type != HARDWARE_DEVICE_PATH
        || NameDp->Header.Header.SubType != HW_VENDOR_DP
        || guidcmp(
                &AmiDeviceNameDevicePathGuid, 
                &NameDp->Header.Guid
           ) != 0
    ) return FALSE;

    NumberOfCharacters = ConstructInternalDeviceName(
        Device, Name, Size
    );
    if (NumberOfCharacters==0) return FALSE;
    //convert number of charcters into string buffer size
    Size = (NumberOfCharacters+1)*sizeof(CHAR16);    
    return  
           Size == NODE_LENGTH(&NameDp->Header.Header)-sizeof(*NameDp)
        && !MemCmp(Name,NameDp+1,Size);
}

//*************************************************************************
//<AMI_PHDR_START>
//
// Name: AddDevicePathToFilePathList
//
// Description:
//   Adds another device path to an array of boot option device paths
//
// Input:
//   IN OUT EFI_DEVICE_PATH_PROTOCOL **FilePathListPtr
//      On input, pointer to the current boot option FilePathList
//      On output, pointer to the new FilePathList. Memory used by original FilePathList is deallocated.
//
//   IN OUT UINTN *FilePathListLength,
//      On input, pointer to the length of the current FilePathList
//      On output, pointer to the length of the new FilePathList
//
//   IN EFI_DEVICE_PATH_PROTOCOL *DevicePath
//      Device path to add to the FilePathList
//
// Output:
//  VOID
//
//<AMI_PHDR_END>
//*************************************************************************
VOID AddDevicePathToFilePathList(
    EFI_DEVICE_PATH_PROTOCOL **FilePathListPtr, UINTN *FilePathListLength,
    EFI_DEVICE_PATH_PROTOCOL *DevicePath
)
{
	UINTN DevicePathLength;
	EFI_DEVICE_PATH_PROTOCOL *NewFilePathList;

    if (   FilePathListPtr == NULL 
        || FilePathListLength == NULL 
        || DevicePath == NULL
    ) return;

    DevicePathLength = DPLength(DevicePath);
    if (*FilePathListPtr == NULL) *FilePathListLength = 0;
    
	NewFilePathList = Malloc(*FilePathListLength + DevicePathLength);
    if ( *FilePathListPtr != NULL ){
	    MemCpy(NewFilePathList, *FilePathListPtr, *FilePathListLength);
        pBS->FreePool(*FilePathListPtr);
    }
	MemCpy(
        (UINT8*)NewFilePathList+*FilePathListLength, 
        DevicePath, DevicePathLength
    );
    *FilePathListLength += DevicePathLength;
	*FilePathListPtr = NewFilePathList;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   BuildEfiFilePath
//
// Description: 
//
// Input:       BOOT_OPTION *Option - 
//
// Output:      
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN BuildEfiFilePath(BOOT_OPTION *Option){
	EFI_DEVICE_PATH_PROTOCOL *Dp;
	EFI_STATUS Status;

    if (   Option->FilePathList!=NULL 
        || Option->BbsEntry != NULL
        || Option->DeviceHandle == INVALID_HANDLE
    ) return FALSE;
	Status = pBS->HandleProtocol(Option->DeviceHandle, &gEfiDevicePathProtocolGuid, &Dp);
    if (EFI_ERROR(Status)) return FALSE;
	Option->FilePathList = DPCopy(Dp);
	Option->FilePathListLength = DPLength(Dp);
    return TRUE;
}

#ifdef CSM_SUPPORT
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   BuildLegacyFilePath
//
// Description: 
//
// Input:       BOOT_OPTION *Option - 
//
// Output:      
//
// Note: function only available, and used, if CSM_SUPPORT token is defined and enabled
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN BuildLegacyFilePath(BOOT_OPTION *Option){
    static struct {
		BBS_BBS_DEVICE_PATH bbs;
		EFI_DEVICE_PATH_PROTOCOL end;
	} BbsDpTemplate =  {
		{
            {BBS_DEVICE_PATH,BBS_BBS_DP,sizeof(BBS_BBS_DEVICE_PATH)},
            BBS_HARDDISK,0,0
        },
		{END_DEVICE_PATH,END_ENTIRE_SUBTYPE,sizeof(EFI_DEVICE_PATH_PROTOCOL)}
	};

    if (Option->FilePathList!=NULL || Option->BbsEntry == NULL) return FALSE;
    BbsDpTemplate.bbs.DeviceType=GetBbsEntryDeviceType(Option->BbsEntry);
	Option->FilePathList = DPCopy(&BbsDpTemplate.bbs.Header);
	Option->FilePathListLength = DPLength(Option->FilePathList);

	return TRUE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   BuildLegacyLocationFilePath
//
// Description: 
//
// Input:       BOOT_OPTION *Option - 
//
// Output:      
//
// Note: function only available, and used, if CSM_SUPPORT token is defined and enabled
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN BuildLegacyLocationFilePath(BOOT_OPTION *Option){
    static struct {
		AMI_BBS_DEVICE_PATH amibbs;
		EFI_DEVICE_PATH_PROTOCOL end;
	} AmiBbsDpTemplate = {
		{
		    { 
              { HARDWARE_DEVICE_PATH, HW_VENDOR_DP, sizeof(AMI_BBS_DEVICE_PATH) },
		      AMI_BBS_DEVICE_PATH_GUID
            },
            0, 0, 0, 0, 0, 0
        },
		{END_DEVICE_PATH,END_ENTIRE_SUBTYPE,sizeof(EFI_DEVICE_PATH_PROTOCOL)}
	};

    EFI_DEVICE_PATH_PROTOCOL *Dp;

    if (Option->BbsEntry == NULL) return FALSE;    
	if (   Option->DeviceHandle == INVALID_HANDLE 
        || EFI_ERROR(pBS->HandleProtocol(Option->DeviceHandle, &gEfiDevicePathProtocolGuid, &Dp))
    ){
        Dp = &AmiBbsDpTemplate.amibbs.Header.Header;
        AmiBbsDpTemplate.amibbs.Bus = (UINT8)Option->BbsEntry->Bus;
    	AmiBbsDpTemplate.amibbs.Device = (UINT8)Option->BbsEntry->Device;
    	AmiBbsDpTemplate.amibbs.Function = (UINT8)Option->BbsEntry->Function;
    	AmiBbsDpTemplate.amibbs.Class = (UINT8)Option->BbsEntry->Class;
        AmiBbsDpTemplate.amibbs.SubClass = (UINT8)Option->BbsEntry->SubClass;
        AmiBbsDpTemplate.amibbs.Instance = GetBbsDeviceInstance(Option->BbsIndex,Option->BbsEntry);
    }
    AddDevicePathToFilePathList(
        &Option->FilePathList, &Option->FilePathListLength, Dp
    );
	return TRUE;
}
#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   BuildNameFilePath
//
// Description: 
//
// Input:       BOOT_OPTION *Option - 
//
// Output:      
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN BuildNameFilePath(BOOT_OPTION *Option){
	static AMI_DEVICE_NAME_DEVICE_PATH AmiNameDpTemplate = {
        { 
            { HARDWARE_DEVICE_PATH, HW_VENDOR_DP, sizeof(AMI_DEVICE_NAME_DEVICE_PATH) },
            AMI_DEVICE_NAME_DEVICE_PATH_GUID
        }
	};
    static EFI_DEVICE_PATH_PROTOCOL EndOfDevicePathNode = {
        END_DEVICE_PATH, END_ENTIRE_SUBTYPE,
        {sizeof(EFI_DEVICE_PATH_PROTOCOL),0}
    };

    CHAR16 Name[1024];
    UINTN Size = sizeof(Name)/sizeof(CHAR16);
    UINTN NumberOfCharacters;
    AMI_DEVICE_NAME_DEVICE_PATH *NameDp;
    EFI_DEVICE_PATH_PROTOCOL    *Dp;

    NumberOfCharacters = ConstructInternalBootOptionName(
        Option, Name, Size
    );
    if (NumberOfCharacters==0) return FALSE;
    //convert number of charcters into string buffer size
    Size = (NumberOfCharacters+1)*sizeof(CHAR16);    

    Dp = Malloc(sizeof(AmiNameDpTemplate)+Size+sizeof(EndOfDevicePathNode));
    ASSERT(Dp!=NULL)
    if (Dp==NULL) return FALSE;
    NameDp = (AMI_DEVICE_NAME_DEVICE_PATH*)Dp;

    *NameDp = AmiNameDpTemplate;
    SET_NODE_LENGTH(Dp,(UINT16)(sizeof(AmiNameDpTemplate)+Size));
    MemCpy(NameDp+1, Name, Size);
    MemCpy(NEXT_NODE(Dp), &EndOfDevicePathNode, sizeof(EndOfDevicePathNode));
    AddDevicePathToFilePathList(
        &Option->FilePathList, &Option->FilePathListLength, Dp
    );
    pBS->FreePool(Dp);
    return TRUE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   BuildBootOptionFilePath
//
// Description: 
//
// Input:       BOOT_OPTION *Option - 
//
// Output:      
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN BuildBootOptionFilePath(BOOT_OPTION *Option){
	UINT32 i;
    BOOLEAN FilePathCreated = FALSE;

	for(i=0; BuildFilePathFunctions[i]!=NULL; i++){
        FilePathCreated |= BuildFilePathFunctions[i](Option);
    }
    return FilePathCreated;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CreateBootOptionsForNewBootDevices
//
// Description: 
//
// Input:       DLIST *BootOptionList - 
//              DLIST *BootDeviceList -
//
// Output:      
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID CreateBootOptionsForNewBootDevices(){
	DLINK *Link;
    BOOT_DEVICE *Device;

    FOR_EACH_BOOT_DEVICE(BootDeviceList,Link,Device){
		BOOT_OPTION *Option = CreateBootOption(BootOptionList);
		UpdateBootOptionWithBootDeviceInfo(Option,Device);
        DeleteBootDevice(BootDeviceList, Device);
		Option->FwBootOption = TRUE;
		ConstructBootOptionName(Option);
		if (!BuildBootOptionFilePath(Option)){
			Option->FilePathList=NULL;
			Option->FilePathListLength=0;
		}
	}
    DUMP_BOOT_OPTION_LIST(BootOptionList,"Before Processing");
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   NormalizeBootOptions
//
// Description: If normalization is enabled, regenerates all the description strings
//              and/or file path lists
//
// Input:       none
//
// Output:      none
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID NormalizeBootOptions(){
    DLINK *Link;
    BOOT_OPTION *Option;

    // Normalize boot options 
	//(regenerate the description string and the file path list)
    FOR_EACH_BOOT_OPTION(BootOptionList,Link,Option){
		if (   !Option->FwBootOption || !IsBootOptionWithDevice(Option)
            || Option->BootOptionNumber == INVALID_BOOT_OPTION_NUMBER
        ) continue;
        if (NormalizeBootOptionDevicePath){
        	EFI_DEVICE_PATH_PROTOCOL *OldFilePathList = Option->FilePathList;
            UINTN OldFilePathListLength = Option->FilePathListLength;
            Option->FilePathList = NULL;
            Option->FilePathListLength = 0;
		    BuildBootOptionFilePath(Option);
            if (Option->FilePathList == NULL){
                Option->FilePathList = OldFilePathList;
                Option->FilePathListLength = OldFilePathListLength;
            }else if (OldFilePathList != NULL){
                pBS->FreePool(OldFilePathList);
            }
        }
        if (NormalizeBootOptionName){
	        CHAR16 *OldDescription = Option->Description;
            Option->Description = NULL;
		    ConstructBootOptionName(Option);
            if (Option->Description == NULL) 
                Option->Description = OldDescription;
            else if (OldDescription != NULL) 
                pBS->FreePool(OldDescription);
        }
	}
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   DumpBootOptionList
//
// Description: 
//
// Input:       DLIST *BootOptionList -
//              CHAR8 *ListCaption - 
//
// Output:      
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID DumpBootOptionList(DLIST *BootOptionList, CHAR8 *ListCaption){
	DLINK *Link;
    BOOT_OPTION *Option;
    if (ListCaption!=NULL)
        TRACE((TRACE_DXE_CORE,"%s:\n",ListCaption));
    FOR_EACH_BOOT_OPTION(BootOptionList,Link,Option){
        CHAR8 *Details1, *Details2, *Details3;
        if (Option->GroupHeader) Details1="(group header)";
        else if (!IsBootOptionWithDevice(Option)) Details1 ="(orphan)";
        else Details1="";
        if ((Option->Attributes&LOAD_OPTION_ACTIVE)!=LOAD_OPTION_ACTIVE) Details2="(disabled)";
        else Details2="";
        if ((Option->Attributes&LOAD_OPTION_HIDDEN)==LOAD_OPTION_HIDDEN) Details3="(hidden)";
        else Details3="";
        TRACE((TRACE_DXE_CORE,
               "%X(%X/%X).%S%s%s%s\n",
               Option->BootOptionNumber,Option->Priority,Option->Tag,Option->Description,
               Details1,Details2,Details3
        ));
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetBootOptionPackedSize
//
// Description: 
//
// Input:       BOOT_OPTION *Option - 
//
// Output:      
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINTN GetBootOptionPackedSize(BOOT_OPTION *Option){
	return
		  sizeof(EFI_LOAD_OPTION)
		+ (Wcslen(Option->Description)+1)*sizeof(CHAR16)
		+ Option->FilePathListLength
		+ Option->OptionalDataSize;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   PackBootOption
//
// Description: 
//
// Input:       BOOT_OPTION *Option - 
//              EFI_LOAD_OPTION *NvramOption - 
//
// Output:      
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID* PackBootOption(BOOT_OPTION *Option, EFI_LOAD_OPTION *NvramOption){
		UINTN DescriptionSize;
		UINT8 *Ptr;

		DescriptionSize = (Wcslen(Option->Description)+1)*sizeof(CHAR16);
		NvramOption->Attributes = Option->Attributes;
		NvramOption->FilePathListLength = (UINT16)Option->FilePathListLength;
		MemCpy(NvramOption+1,Option->Description,DescriptionSize);
		Ptr = (UINT8*)(NvramOption+1)+DescriptionSize;
		MemCpy(Ptr, Option->FilePathList, Option->FilePathListLength);
		Ptr += Option->FilePathListLength;
		return Ptr;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SaveBootOptions
//
// Description: 
//
// Input:       DLIST *BootOptionList - 
//
// Output:      
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID SaveBootOptions(){
	UINTN BootOrderSize;
	UINT16 *BootOrder;
	DLINK *Link;
	UINTN BootOrderIndex = 0;
    BOOT_OPTION *Option;

    //PRECONDITION: All Boot Option Numbers are set
    SortList(BootOptionList, ComparePriorityThenBootOptionNumber);
    DUMP_BOOT_OPTION_LIST(BootOptionList, "Before Saving");
	BootOrderSize = BootOptionList->Size*sizeof(UINT16);
	if (BootOrderSize==0) return;
	BootOrder = Malloc(BootOrderSize);

    FOR_EACH_BOOT_OPTION(BootOptionList,Link,Option){
		EFI_LOAD_OPTION *NvramOption;
        BOOT_OPTION *NestedOption;
		DLINK *TmpLink;
		UINTN NvramOptionSize;
		UINT8 *Ptr;
		CHAR16 BootStr[9];
		EFI_STATUS Status;
		BOOLEAN HasNestedOptions = FALSE;

        //Meke sure the boot option is well-formed
        if(    Option->FilePathListLength == 0 
            || Option->FilePathList == NULL
            || Option->BootOptionNumber == INVALID_BOOT_OPTION_NUMBER
        ){
            TRACE((TRACE_DXE_CORE,
                   "SaveBootOptions: skipping invalid boot option '%X.%S'\n",
                   Option->BootOptionNumber,Option->Description
            ));
            continue;
        }

		NvramOptionSize =  GetBootOptionPackedSize(Option);
		if (Option->FwBootOption){
			NvramOptionSize += sizeof(UINT32); //signature
            //TRACE((-1,"(%X) before size loop: size=%X\n",Option->BootOptionNumber,NvramOptionSize));
            FOR_EACH_LIST_ELEMENT(Option->Link.pNext, TmpLink, NestedOption, BOOT_OPTION){
				if (Option->BootOptionNumber != NestedOption->BootOptionNumber)
                    break;
				NvramOptionSize +=   AMI_NESTED_BOOT_OPTION_HEADER_SIZE + 
				                   + GetBootOptionPackedSize(NestedOption)
                                   + sizeof(UINT32); //signature;
                //TRACE((-1,"Nested(%X) size loop: size=%X\n",Option->BootOptionNumber,NvramOptionSize));
				HasNestedOptions = TRUE;
			}
		}
		NvramOption = Malloc(NvramOptionSize);
		Ptr = PackBootOption(Option,NvramOption);
		if (Option->FwBootOption){
			if (HasNestedOptions)
				*(UINT32*)Ptr = AMI_GROUP_BOOT_OPTION_SIGNATURE;
			else
				*(UINT32*)Ptr = AMI_SIMPLE_BOOT_OPTION_SIGNATURE;
			Ptr += sizeof(UINT32);
            //TRACE((-1,"(%X) before save loop: size=%X\n",Option->BootOptionNumber,Ptr-(UINT8*)NvramOption));
            if (HasNestedOptions){
                FOR_EACH_LIST_ELEMENT(Option->Link.pNext, TmpLink, NestedOption, BOOT_OPTION){
    				NESTED_BOOT_OPTION *NestedPackedOption;
    
    				if (Option->BootOptionNumber != NestedOption->BootOptionNumber)
                        break;
    				NestedPackedOption = (NESTED_BOOT_OPTION*)Ptr;
    				NestedPackedOption->Signature = AMI_NESTED_BOOT_OPTION_SIGNATURE;
    				Ptr = PackBootOption(NestedOption,&NestedPackedOption->Option);
    				*(UINT32*)Ptr = AMI_SIMPLE_BOOT_OPTION_SIGNATURE;
    				Ptr += sizeof(UINT32);
    				if (NestedOption->OptionalDataSize!=0){
    					MemCpy(
    						Ptr, NestedOption->OptionalData, NestedOption->OptionalDataSize
    					);
    				    Ptr += NestedOption->OptionalDataSize;
    				}
    				NestedPackedOption->Size = (UINT32)(Ptr - (UINT8*)NestedPackedOption);
                    //delete nested option
                    DeleteBootOption(BootOptionList,NestedOption);
                    //TRACE((-1,"Nested(%X) save loop: size=%X\n",Option->BootOptionNumber,Ptr-(UINT8*)NvramOption));
    			}
            }
		}
		if (Option->OptionalDataSize!=0){
			MemCpy(
				Ptr, Option->OptionalData, Option->OptionalDataSize
			);
		}
        //TRACE((-1,"Saving %d: %X; %X; ods=%d\n",Option->BootOptionNumber,Ptr+Option->OptionalDataSize,(UINT8*)NvramOption+NvramOptionSize,Option->OptionalDataSize));
		ASSERT(Ptr+Option->OptionalDataSize == (UINT8*)NvramOption+NvramOptionSize) 
		Swprintf(BootStr,L"Boot%04X",Option->BootOptionNumber);
		Status = pRS->SetVariable(
			BootStr, &EfiVariableGuid,
			BOOT_VARIABLE_ATTRIBUTES, NvramOptionSize, NvramOption
		);
        BootOrder[BootOrderIndex]=Option->BootOptionNumber;
        Link = Option->Link.pNext;
        DeleteBootOption(BootOptionList,Option);
		pBS->FreePool(NvramOption);
		if (EFI_ERROR(Status)) continue;
        BootOrderIndex++;
	}
	pRS->SetVariable(
		L"BootOrder", &EfiVariableGuid,
		BOOT_VARIABLE_ATTRIBUTES, BootOrderIndex*sizeof(UINT16), BootOrder
	);
	pBS->FreePool(BootOrder);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   UpdateBootOptionVariables
//
// Description: This function initializes the global variables.
//              Must be called before any other boot option processing function can be used.
//
// Input:       none
//
// Output:      none
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID UpdateBootOptionVariables(){
    LoadStrings(TheImageHandle, &HiiHandle);
	DListInit(BootOptionList);
	DListInit(BootDeviceList);
}

BOOLEAN IsGroupOrphan(BOOT_OPTION *Option)
{
    BOOT_OPTION *Current;

    Current = (BOOT_OPTION *)BootOptionList->pHead;
    while(Current != NULL) {
        if(Current == Option)
            break;
        Current = (BOOT_OPTION *)Current->Link.pNext;
    }

    if(Current == NULL)     //shouldn't be here - input parameter is not found in boot options
        return TRUE;

    Current = (BOOT_OPTION *)Current->Link.pNext;   //get next boot option
    if(Current == NULL || Current->Tag != Option->Tag)  //group option is alone (next either NULL or different tag)
        return TRUE;

    while(Current != NULL && Current->Tag == Option->Tag) {
        if(IsBootOptionWithDevice(Current))            //one of physical boot options in group has device
            return FALSE;
        Current = (BOOT_OPTION *)Current->Link.pNext;
    }
    return TRUE;
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