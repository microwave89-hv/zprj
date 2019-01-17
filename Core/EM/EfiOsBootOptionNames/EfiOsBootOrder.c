//***********************************************************************
//#**********************************************************************
//#**                                                                  **
//#**        (C)Copyright 1985-2015, American Megatrends, Inc.         **
//#**                                                                  **
//#**                       All Rights Reserved.                       **
//#**                                                                  **
//#**              5555 Oak brook Pkwy, Norcorss, GA 30093             **
//#**                                                                  **
//#**                       Phone: (770)-246-8600                      **
//#**                                                                  **
//#**********************************************************************
//***********************************************************************

//**********************************************************************
// $Header: /Alaska/BIN/Modules/BootOptionPolicies/EfiOsBootOptionNames/EfiOsBootOrder.c 24    6/11/15 2:42a Dukeyeh $
//
// $Revision: 24 $
//
// $Date: 6/11/15 2:42a $
//***********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/BootOptionPolicies/EfiOsBootOptionNames/EfiOsBootOrder.c $
// 
// 24    6/11/15 2:42a Dukeyeh
// Change IsSpecifiedUefiOsBootOptions function's comment header style
// from AptioV to 4
// 
// 23    4/28/15 4:55a Dukeyeh
// [TAG]  		EIP213903
// [Category]  	Bug Fix
// [Severity]  	Normal
// [RootCause]  	"UEFI OS" boot option's name/device path being
// renormalized.
// [Solution]  	"UEFI OS" boot option needs to escape name/device path
// normalization when token CREATE_BOOT_OPTION_WITH_UEFI_FILE_NAME_POLICY
// is enabled (create "UEFI OS" boot option if can't find any other boot
// file paths in table).
// [Files]  		EfiOsBootOrder.c
// 
// 22    3/11/15 6:48a Dukeyeh
// [TAG]  		EIP178808
// [Category]  	New Feature
// [Description]  	Implement the selection of
// NEW_UEFI_OS_OPTION_ORDER_POLICY item in Setup.
// [Files]  		EfiOsBootOptionNames.sdl
// EfiOsBootOptionNames.mak
// EfiOsBootOrder.c
// EfiOsBootOptionNames.cif
// 
// 21    3/11/15 3:47a Dukeyeh
// [TAG]  		EIP204138
// [Category]  	Improvement
// [Description]  	Add a CREATE_BOOT_OPTION_WITH_UEFI_FILE_NAME_POLICY
// token to control whether create
// "UEFI OS" boot option if can't find any other in specified file paths
// (default) or just create it.
// [Files]  		EfiOsBootOptionNames.sdl
// EfiOsBootOptionNames.mak
// EfiOsBootOrder.c
// 
// 20    12/24/14 1:11a Dukeyeh
// [TAG]  		EIP_NO
// [Category]  	Improvement
// [Description]  	When deleting the duplicate boot options, synchronized
// with FIXED_BOOT_ORDER module. 
// [Files]  		EfiOsBootOrder.c
// 
// 19    12/23/14 5:45a Dukeyeh
// [TAG]  		EIP_NO
// [Category]  	Improvement
// [Description]  	Add KeepDuplicateNonFWBootOption token to determine
// whether deletes the duplicated NON-FW boot options or not.
// [Files]  		EfiOsBootOptionNames.sdl
// EfiOsBootOrder.c
// 
// 18    12/04/14 4:51a Dukeyeh
// [TAG]  		EIP194753 
// [Category]  	Bug Fix
// [RootCause]  	Compiler makes CHAR8 into signed value of 4 bytes in
// comparison statement, so it fails to comparison with immediate value.
// [Solution]  	Change the variable declarations of CHAR8 into UINT8.
// [Files]  		EfiOsBootOrder.c
// 
// 17    12/03/14 10:59p Dukeyeh
// [TAG]  		EIP_NO
// [Category]  	Improvement
// [Description]  	For CppCheck error in AdjustNewUefiOsOptionPriority
// function that Priority variable didn't have default/initialized value.
// [Files]  		EfiOsBootOrder.c
// 
// 16    11/19/14 2:22a Klzhan
// [TAG]  		EIPNone
// [Category]  	Improvement
// [Description]  	Add a token to set boot option created by this module
// is Fw Boot Option or not.
// [Files]  		EfiOsBootOptionNames.sdl
// EfiOsBootOptionNames.mak
// EfiOsBootOptionNames.chm
// EfiOsBootOptionNames.c
// EfiOsBootOrder.c
// EfiOsBootOptionNames.cif
// 
// 15    9/03/14 10:41p Dukeyeh
// [TAG]  		EIP_NO
// [Category]  	Improvement
// [Description]  	1. Add new token for eLink dependency of
// BcpBootOrder_SUPPORT.
// 2. CHM file for version 10.
// 3. Change NewEfiOsOptionDpListCount variable to zero when return.
// [Files]  		EfiOsBootOptionNames.sdl
// EfiOsBootOptionNames.chm
// EfiOsBootOrder.c
// 
// 14    9/03/14 1:59a Dukeyeh
// [TAG]  		EIP180447
// [Category]  	Improvement
// [Description]  	Create a token to set the priority of the boot option
// created by Efi Os Boot Option Name.
// [Files]  		EfiOsBootOptionNames.sdl
// EfiBootOrder.c
// 
// 13    9/02/14 10:27p Dukeyeh
// [TAG]  		EIP178318 
// [Category]  	Improvement
// [Description]  	Sync Boot priority after remove FW Boot Option.
// [Files]  		EfiOsBootOrder.c
// 
// 12    8/13/14 11:14p Walonli
// [TAG]  		EIP180632
// [Category]  	New Feature
// [Description]  	Support FixedBootOrder to display Uefi OS full name
// "Windows Boot Manager(Px: DeviceName)".
// [Files]  		EfiOsBootOptionNames.c
// EfiOsBootOrder.c
// EfiOsBootOptionNames.cif
// 
// 11    7/07/14 4:40a Klzhan
// [TAG]  		EIPNone
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	Duplicated boot option created by module
// [RootCause]  	FwBootOption check is incorrect.
// 
// 10    5/23/14 5:08a Dukeyeh
// [TAG]  		EIP167957 
// [Category]  	Bug Fix
// [RootCause]  	EIP147262 - The "EFI OS BootOptionNames" module can't
// support the "FixedBootOrder" module Boot option strings. 
// EIP159984 - Linux UEFI OS boot issue. 
// EIP168792 - Possible heap corruption - EFI OS BootOptionNames 
// [Solution]  	EIP147262 =>A new token
// "DISPLAY_FULL_OPTION_NAME_WITH_FBO" is added to control this.
// EIP159984 =>Should NOT kill the UEFI OS boot option that created by OS.
// EIP168792 =>NEW_STRING_BUFFER_LENGTH is replaced with the actual size
// of the allocated memory, NewStringLength. 
// 
// [Files]  		EfiOsBootOptionNames.sdl
// EfiOsBootOptionNames.mak
// EfiOsBootOptionNames.chm
// EfiOsBootOptionNames.c
// EfiOsBootOrder.c
// EfiOsBootOptionNames.cif
// 
//***********************************************************************
//***********************************************************************
//<AMI_FHDR_START>
//
// Name: EfiOsBootOrder.c
//
// Description:	Deal with UEFI Boot Devices that contain UEFI OS.
//              Create boot option if device is existed, delete 
//              boot option if there is a duplicated one and then 
//              adjust the BootOrder.
//
//<AMI_FHDR_END>
//***********************************************************************

#include <BootOptions.h>
#include "EfiOsNamesFilePathMaps.h"
#include <Protocol\PDiskinfo.h>
#include <Token.h>
#include <AmiDxeLib.h>
#include <Setup.h>

#if DISPLAY_FULL_OPTION_NAME_WITH_FBO
#include "Board\em\FixedBootOrder\FixedBootOrder.h"
#endif

#ifdef BootOption_x64
#define EFI_BOOT_FILE_NAME L"\\EFI\\BOOT\\BOOTX64.EFI"
#else
#define EFI_BOOT_FILE_NAME L"\\EFI\\BOOT\\BOOTIA32.EFI"
#endif

#define EFI_OS_BOOT_OPTION_NAMES_GUID \
    {0x69ECC1BE, 0xA981, 0x446D, 0x8E, 0xB6, 0xAF, 0x0E, 0x53, 0xD0, 0x6C, 0xE8}

#define TstrW(s) L#s							//(EIP103672+)

#pragma pack(1)
typedef struct _PARTITION_ENTRY {
    UINT8 ActiveFlag;               	// Bootable or not
    UINT8 StartingTrack;            	// Not used
    UINT8 StartingCylinderLsb;      	// Not used
    UINT8 StartingCylinderMsb;      	// Not used
    UINT8 PartitionType;            	// 12 bit FAT, 16 bit FAT etc.
    UINT8 EndingTrack;              	// Not used
    UINT8 EndingCylinderLsb;        	// Not used
    UINT8 EndingCylinderMsb;        	// Not used
    UINT32 StartSector;          	// Relative sectors
    UINT32 PartitionLength;         	// Sectors in this partition
} PARTITION_ENTRY;

typedef struct
{
	CHAR16 *FilePath;
	CHAR16 *BootOptionName;
}NAME_MAP;
#pragma pack()

typedef EFI_STATUS (DEAL_WITH_EFI_OS_BOOT_OPTION) (EFI_HANDLE Handle);
extern DEAL_WITH_EFI_OS_BOOT_OPTION DEAL_WITH_EFI_OS_BOOT_OPTION_FUNC_PTR;
DEAL_WITH_EFI_OS_BOOT_OPTION *DealWithEfiOsBootOptionFuncPtr = DEAL_WITH_EFI_OS_BOOT_OPTION_FUNC_PTR;

typedef BOOLEAN (CREATE_TARGET_EFI_OS_BOOT_OPTION) (EFI_HANDLE Handle, NAME_MAP* NameMap);
extern CREATE_TARGET_EFI_OS_BOOT_OPTION CREATE_TARGET_EFI_OS_BOOT_OPTION_FUNC_PTR;
CREATE_TARGET_EFI_OS_BOOT_OPTION *CreateTargetEfiOsBootOptionFuncPtr = CREATE_TARGET_EFI_OS_BOOT_OPTION_FUNC_PTR;

/**
    Arrary of eLinks that contain many OS image paths and their corresponding OS names.
*/
NAME_MAP FILE_NAME_MAPS[] = { EfiOsFilePathMaps {NULL,NULL} };	//(EIP103672+)

extern BOOLEAN NormalizeBootOptionName ;
extern BOOLEAN NormalizeBootOptionDevicePath ;

#if DISPLAY_FULL_OPTION_NAME_WITH_FBO
extern EFI_HANDLE GetPhysicalBlockIoHandle (IN EFI_HANDLE BlockIoHandle) ;
extern UINTN RemoveTrailingSpaces(CHAR16 *Name, UINTN NumberOfCharacters);
extern UINT16 gSATA[3][2] ;
#endif

EFI_DEVICE_PATH_PROTOCOL **NewEfiOsOptionDpList = NULL ;
UINTN NewEfiOsOptionDpListCount = 0 ;

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name: GetHdNode
//
// Description:	
//  Locates HD node in DevicePath associated with Handle.
//
// Input:
//  IN EFI_HANDLE Handle - Handle with DevicePath protocol for which HD
//      node should be located.
//
// Output:
//  OUT EFI_DEVICE_PATH_PROTOCOL** DevPath - Pointer to HD node, if found.
//
// Returns: 
//  EFI_SUCCESS - HD node was found and returned.
//  EFI_NOT_FOUND - No HD node was found.
//  Other errors possible if Handle does not have DevicePath protocol.
//
// Modified:
//  None.
//
// Referrals:
//  HandleProtocol()
//  isEndNode()
//  NEXT_NODE()
//
// Notes:	
//  None.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS GetHdNode (
    IN EFI_HANDLE Handle,
    OUT EFI_DEVICE_PATH_PROTOCOL** DevPath
)
{
    EFI_STATUS Status;
    EFI_DEVICE_PATH_PROTOCOL* DevicePath;

    *DevPath = NULL;

    // Get DevicePath attached to handle.
    Status = pBS->HandleProtocol (
        Handle,
        &gEfiDevicePathProtocolGuid,
        &DevicePath
    );
    if (EFI_ERROR(Status)) {
        TRACE((-1, "HandleProtocol: %r\n", Status));
        return Status;
    }

    // Find hard drive node.
    while (!isEndNode(DevicePath)) {

        if ((DevicePath->Type == MEDIA_DEVICE_PATH) &&
            (DevicePath->SubType == MEDIA_HARDDRIVE_DP)) {

            *DevPath = DevicePath;
            return EFI_SUCCESS;
        }

        DevicePath = NEXT_NODE(DevicePath);
    }
            
    // HD node was not found.  Return error.
    return EFI_NOT_FOUND;
}

#if DISPLAY_FULL_OPTION_NAME_WITH_FBO
//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name: GetHDDPort
//
// Description:	
//  Use handle and EFI_DISK_INFO_PROTOCOL to get sata hard disk port.
//
// Input:
//  IN EFI_HANDLE - Use in locating EFI_DISK_INFO_PROTOCOL.
//
// Output:
//  None.
//
// Returns: 
//  UINT16 - Sata port number.
//
// Modified:
//  None.
//
// Referrals:
//  HandleProtocol().
// 
// Notes:	
//  None.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16 GetHDDPort( IN EFI_HANDLE Handle )
{
    EFI_STATUS Status;
    EFI_GUID gEfiDiskInfoProtocolGuid = EFI_DISK_INFO_PROTOCOL_GUID;
    EFI_DISK_INFO_PROTOCOL *DiskInfo;
    EFI_DEVICE_PATH_PROTOCOL *DevicePath;
    UINT32 IdeChannel;
    UINT32 IdeDevice;

    Status = pBS->HandleProtocol (
                 Handle,
                 &gEfiDevicePathProtocolGuid,
                 (VOID *) &DevicePath );

    if ( !EFI_ERROR( Status ))
    {
        EFI_DEVICE_PATH_PROTOCOL *DevicePathNode;
        EFI_DEVICE_PATH_PROTOCOL *MessagingDevicePath;
        PCI_DEVICE_PATH *PciDevicePath;

        DevicePathNode = DevicePath;
        while (!isEndNode (DevicePathNode))
        {
            if ((DevicePathNode->Type == HARDWARE_DEVICE_PATH)
                    && (DevicePathNode->SubType == HW_PCI_DP))
                PciDevicePath = (PCI_DEVICE_PATH *) DevicePathNode;
            else if (DevicePathNode->Type == MESSAGING_DEVICE_PATH)
                MessagingDevicePath = DevicePathNode;

            DevicePathNode = NEXT_NODE (DevicePathNode);
        }

        Status = pBS->HandleProtocol ( Handle, &gEfiDiskInfoProtocolGuid, &DiskInfo );
        if ( !EFI_ERROR(Status) )
        {
            Status = DiskInfo->WhichIde ( DiskInfo, &IdeChannel, &IdeDevice );
            if ( !EFI_ERROR(Status) )
            {
                if ( MessagingDevicePath->SubType == MSG_ATAPI_DP ) //IDE mode?
                {
                    if (PciDevicePath->Function == 5)
                        return gSATA[IdeDevice+2][IdeChannel];
                    else
                        return gSATA[IdeDevice][IdeChannel];
                }
                else
                    return IdeChannel;  //AHCI Port Number
            }
        }
    }
    return 0xff;
}
#endif

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name: GetGptPartitionHandle
//
// Description:	Search GPT HDD and return Hard disk handle.
//
// Input:
//  IN EFI_DEVICE_PATH_PROTOCOL *DevicePath - Search GPT HDD and return Hard disk handle.
//
// Output:
//  None.
//
// Returns: 
//  EFI_HANDLE - Hard Disk handle or NULL.
//
// Modified:
//  None.
//
// Referrals:
//  LocateHandleBuffer(),
//  HandleProtocol().
// 
// Notes:	
//  None.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_HANDLE GetGptPartitionHandle(EFI_DEVICE_PATH_PROTOCOL *DevicePath)
{
    EFI_STATUS	Status;
    EFI_HANDLE	*Handle, TempHandle = NULL;
    UINTN	Count, i;

    HARDDRIVE_DEVICE_PATH* BootParitionDevicePath  = (HARDDRIVE_DEVICE_PATH*)DevicePath;

    //get list of available Block I/O devices
    Status = pBS->LocateHandleBuffer(ByProtocol,&gEfiBlockIoProtocolGuid,NULL,&Count,&Handle);
    if (EFI_ERROR(Status)) return NULL;

    for( i=0; i<Count; i++ )
    {
        EFI_BLOCK_IO_PROTOCOL		*BlockIo;
        EFI_DEVICE_PATH_PROTOCOL	*PartitionDevicePath, *TmpDevicePath;
        HARDDRIVE_DEVICE_PATH*		PartitionNode;

        Status = pBS->HandleProtocol(Handle[i],&gEfiBlockIoProtocolGuid,&BlockIo);
        if (EFI_ERROR(Status))
			continue;

        // if this is not partition, continue
        if (!BlockIo->Media->LogicalPartition)
			continue;

        Status = pBS->HandleProtocol(Handle[i],&gEfiDevicePathProtocolGuid,&PartitionDevicePath);
        if (EFI_ERROR(Status))
			continue;

        // Get last node of the device path. It should be partition node
        PartitionNode = (HARDDRIVE_DEVICE_PATH*)PartitionDevicePath;

        for( TmpDevicePath = PartitionDevicePath;
             !isEndNode(TmpDevicePath);
             TmpDevicePath=NEXT_NODE(TmpDevicePath) )
		{
			PartitionNode = (HARDDRIVE_DEVICE_PATH*)TmpDevicePath;
		}

        //Check if our partition matches Boot partition
        if (PartitionNode->Header.Type!=MEDIA_DEVICE_PATH || PartitionNode->Header.SubType!=MEDIA_HARDDRIVE_DP)
			continue;

        if ( PartitionNode->PartitionNumber==BootParitionDevicePath->PartitionNumber &&
             PartitionNode->SignatureType==BootParitionDevicePath->SignatureType &&
             !MemCmp(PartitionNode->Signature,BootParitionDevicePath->Signature,16) )
        {
            //Match found
            TempHandle = Handle[i];
            break;
        }
    }

    pBS->FreePool(Handle);
    return TempHandle;
}
                                                              //(EIP126686+)>
//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name: CompareHddDevicePath
//
// Description:	Compare whether two HDD device paths are the same.
//
// Input:
//  IN EFI_DEVICE_PATH_PROTOCOL *DevDp1 - Device path in comparison.
//  IN EFI_DEVICE_PATH_PROTOCOL *DevDp2 - Device path in comparison.
//
// Output:
//  None.
//
// Returns: 
//  EFI_STATUS
//
// Modified:
//  None.
//
// Referrals:
//  MemCmp(),
//  NEXT_NODE().
// 
// Notes:	
//  None.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS CompareHddDevicePath( EFI_DEVICE_PATH_PROTOCOL *DevDp1, EFI_DEVICE_PATH_PROTOCOL *DevDp2 )
{
                                                              
    if ( DevDp1->Type == MEDIA_DEVICE_PATH &&
         DevDp1->SubType == MEDIA_HARDDRIVE_DP )
    {
        if (MemCmp(DevDp1+1, DevDp2+1, sizeof(HARDDRIVE_DEVICE_PATH)-sizeof(EFI_DEVICE_PATH_PROTOCOL)) == 0) //Skip Header EFI_DEVICE_PATH_PROTOCOL.
        {
            DevDp1 = NEXT_NODE(DevDp1);
            if( DevDp1->Type == MEDIA_DEVICE_PATH &&
                DevDp1->SubType == MEDIA_FILEPATH_DP ) Wcsupr( (CHAR16*)DevDp1+1 );

            DevDp2 = NEXT_NODE(DevDp2);
            if( DevDp2->Type == MEDIA_DEVICE_PATH &&
                DevDp2->SubType == MEDIA_FILEPATH_DP ) Wcsupr( (CHAR16*)DevDp2+1 );

	        if (MemCmp(DevDp1, DevDp2, DPLength(DevDp2)) == 0)
                return EFI_SUCCESS;
        }
    }  

    return EFI_NOT_FOUND;
}
                                                               //<(EIP126686+)

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	CheckBootOptionMatch
//
// Description:	Search all BootOptionList and found out the matched HDD device path.
//
// Input:		EFI_DEVICE_PATH_PROTOCOL *HdDevPath
//
// Output:		EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS CheckBootOptionMatch (
    IN EFI_DEVICE_PATH_PROTOCOL* HdDevPath
)
{
    DLINK *Link;
    BOOT_OPTION *Option;

    FOR_EACH_BOOT_OPTION(BootOptionList,Link,Option){

                                                     //(EIP126686+)>
     	if( CompareHddDevicePath(Option->FilePathList, HdDevPath) == EFI_SUCCESS )
            return EFI_SUCCESS;
                                                     //<(EIP126686+)
    }
    return EFI_NOT_FOUND;
}

									//(EIP103672+)>
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	GetEfiOsBootNameItemCount
//
// Description:	Count the elements in eLink FILE_NAME_MAPS.
//
// Input:		EFI_DEVICE_PATH_PROTOCOL *DevicePath
//
// Output:		EFI_HANDLE
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16 GetEfiOsBootNameItemCount(void)
{
    UINT16 ItemCount=0;

	do{

        if( FILE_NAME_MAPS[ItemCount].FilePath == NULL )
            break;

	    ItemCount++;	

	}while(1);

	return ItemCount;
}
									//<(EIP103672+)

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CreateTargetEfiOsBootOption	
//
// Description:	Create target efi os boot option
//
// Input:       EFI_HANDLE  FileSystemHandle - Handle to get file system
//              NAME_MAP*   DevicePath - Contain boot file name and boot option name
//
// Output:      TRUE  - if find any matched boot option / create boot option successfully
//              FALSE - if one of inputs is invalid / fail to allocate pool / fail to get hdd node 
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN CreateTargetEfiOsBootOption(EFI_HANDLE FileSystemHandle, NAME_MAP* NameMap)
{
    EFI_STATUS Status;
    UINTN OptionSize;
    UINT8* BytePtr;
    EFI_DEVICE_PATH_PROTOCOL *DevicePath = NULL;
    EFI_DEVICE_PATH_PROTOCOL *HdDevPath = NULL;
    FILEPATH_DEVICE_PATH *FpDevPath = NULL;
    BOOT_OPTION *Option;

    if(!FileSystemHandle || !NameMap)
        return FALSE;

    // Find total size of new boot option.
    OptionSize = 	sizeof(HARDDRIVE_DEVICE_PATH) + // Partition node
                  sizeof(FILEPATH_DEVICE_PATH) + // FilePath node
                  ((Wcslen(NameMap->FilePath) ) * sizeof(CHAR16)) +	//(EIP120976)
                  sizeof(EFI_DEVICE_PATH_PROTOCOL); //+ // End node			//(EIP103870)

    Status = pBS->AllocatePool (
                 EfiBootServicesData,
                 OptionSize,
                 &DevicePath);

    if (EFI_ERROR(Status)) {
        TRACE((-1, "AllocatePool %r\n", Status));
        return FALSE;
    }

    // Get HD node of device path associated with handle.
    Status = GetHdNode (
                 FileSystemHandle,
                 &HdDevPath );

    if (EFI_ERROR(Status)) {
        TRACE((-1, "GetHdNode: %r\n", Status));
        pBS->FreePool(DevicePath);
        return FALSE;
    }

    BytePtr = (UINT8*)DevicePath;
    // Copy to FilePath.
    MemCpy(BytePtr, HdDevPath, NODE_LENGTH(HdDevPath));

    // Point to next node.
    BytePtr += NODE_LENGTH(HdDevPath);
    FpDevPath = (FILEPATH_DEVICE_PATH*)BytePtr;

    // Set Filepath node.
    FpDevPath->Header.Type = MEDIA_DEVICE_PATH;
    FpDevPath->Header.SubType = MEDIA_FILEPATH_DP;
    SET_NODE_LENGTH(&(FpDevPath->Header), 4 + (UINT16)((Wcslen(NameMap->FilePath) + 1) * sizeof(CHAR16)));

    // Set Filepath PathName.
    MemCpy(FpDevPath->PathName, NameMap->FilePath, (Wcslen(NameMap->FilePath) + 1) * sizeof(CHAR16));

    // Point to next node.
    BytePtr += NODE_LENGTH(&(FpDevPath->Header));
    ((EFI_DEVICE_PATH_PROTOCOL*)BytePtr)->Type = END_DEVICE_PATH;
    ((EFI_DEVICE_PATH_PROTOCOL*)BytePtr)->SubType = END_ENTIRE_SUBTYPE;
    SET_NODE_LENGTH((EFI_DEVICE_PATH_PROTOCOL*)BytePtr, END_DEVICE_PATH_LENGTH);

    // Point to signature.
    BytePtr += END_DEVICE_PATH_LENGTH;

#if DISPLAY_FULL_OPTION_NAME_WITH_FBO
    //
    // Uefi OS in Setup as style "OS Name(PX: DeviceName)" because of 
    // EfiOsBootOptionNames module creates it by ChangeUefiBootNames
    // eLink to change bootData->Name, however, FixedBootOrder module
    // creates its oneof items with BootXXXX variable's description 
    // which saved according to Option->Description, that makes only
    // "OS Name" appear in setup, hence we need to use FixedBootOrder
    // protocol to set new description.
    //
    {
        CHAR16 *ControllerName ;
        CHAR16 *DeviceName ;
        UINT16 PortNumber = 0xff ;
        UINTN  NumberOfCharacters = 0, DeviceNameLength = 0;
        EFI_HANDLE Handle ;
        EFI_FIXED_BOOT_ORDER_PROTOCOL *Fbo = NULL ;
        EFI_GUID FixedBootOrderGuid = FIXED_BOOT_ORDER_GUID ;
        
        Status = pBS->LocateProtocol(&FixedBootOrderGuid, NULL, &Fbo);
        Handle = GetPhysicalBlockIoHandle(FileSystemHandle);
        if (GetControllerName(Handle, &ControllerName) && !EFI_ERROR(Status)) 
        {   
            DeviceNameLength = (Wcslen(ControllerName)+1)*sizeof(CHAR16) ;
            DeviceName = MallocZ(DeviceNameLength) ;
            PortNumber = GetHDDPort( Handle );
            NumberOfCharacters = Swprintf_s(DeviceName, DeviceNameLength, L"%s", ControllerName);
            DeviceNameLength = RemoveTrailingSpaces(DeviceName, NumberOfCharacters);
            if ( DeviceNameLength )
            {
                FBO_DEVICE_INFORM *inform ;
                CHAR16 *String ;
                UINTN StringLength = DeviceNameLength*sizeof(CHAR16)
                                     + Wcslen(NameMap->BootOptionName)*sizeof(CHAR16)
                                     + 0xf ;
                String = MallocZ(StringLength) ;
                if ( PortNumber != 0xff )
                {
                    Swprintf_s ( String,
                                StringLength,
                                L"%s (P%d: %s)",
                                NameMap->BootOptionName,
                                PortNumber,
                                DeviceName );
                    TRACE((-1, "EfiOsBootOrder.c Reset the Boot Option Name:%S \n", String)) ;
                }
                else  // It don't have port number
                {
                    Swprintf_s ( String,
                                StringLength,
                                L"%s (%s)",
                                NameMap->BootOptionName,
                                DeviceName );
                    TRACE((-1, "EfiOsBootOrder.c Reset the Boot Option Name:%S \n", String)) ;
                }
                
                inform = MallocZ(sizeof(FBO_DEVICE_INFORM)) ;
                inform->DevName = String ;
                inform->DevPath = MallocZ(DPLength(DevicePath)) ;
                MemCpy(inform->DevPath, DevicePath, DPLength(DevicePath)) ;
                Status = Fbo->SetNewDescription(inform) ;
                if (EFI_ERROR(Status))
                    TRACE((-1, "Can't set new description with fbo protocol")) ;
            }
            pBS->FreePool(DeviceName) ;
        }
    }
#endif

    if ( CheckBootOptionMatch( DevicePath ) == EFI_SUCCESS )
    {
        TRACE((-1,"CheckBootOptionMatch Matched.....\n" ));
        pBS->FreePool(DevicePath);
        return TRUE;
    }

    Option = CreateBootOption(BootOptionList);
    Option->Attributes = LOAD_OPTION_ACTIVE;           //(EIP138397)
    Option->FwBootOption = DefaultFwBootOption;

    pBS->AllocatePool (
        EfiBootServicesData,
        ((Wcslen(NameMap->BootOptionName) + 1) * sizeof(CHAR16)),
        &Option->Description);

    MemCpy(Option->Description,
           NameMap->BootOptionName,
           ((Wcslen(NameMap->BootOptionName) + 1) * sizeof(CHAR16)) );

    
    Option->FilePathList = DevicePath;
    Option->FilePathListLength = OptionSize;
           
    {
        VOID **ptr = NULL ;
        ptr = MallocZ(sizeof(VOID**)
                      * (NewEfiOsOptionDpListCount+1)) ;
        if (ptr)
        {
            MemCpy(ptr, NewEfiOsOptionDpList, sizeof(VOID**)
                                          * NewEfiOsOptionDpListCount) ;
            *(ptr+NewEfiOsOptionDpListCount) = Option->FilePathList ;

            NewEfiOsOptionDpListCount++ ;
            pBS->FreePool(NewEfiOsOptionDpList) ;
            NewEfiOsOptionDpList = (EFI_DEVICE_PATH_PROTOCOL**)ptr ;
        }
    }

    return TRUE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CreateBootOptionWithUefiFileName
//
// Description:	Create boot option with uefi file name if there is no other matched path.
//
// Input:       EFI_HANDLE Handle - Handle to locate file system
//              UINT16 MatchedBootablePathCount - Count of matched bootable files
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID CreateBootOptionWithUefiFileName(EFI_HANDLE Handle)
{
    EFI_STATUS Status;
    EFI_FILE_PROTOCOL *FileProtocol;
    EFI_SIMPLE_FILE_SYSTEM_PROTOCOL* SimpleFileSystem;

    if(!Handle)
        return;

    Status = pBS->HandleProtocol (
                 Handle,
                 &gEfiSimpleFileSystemProtocolGuid,
                 &SimpleFileSystem
             );

    if(!EFI_ERROR(Status))
    {
        Status = SimpleFileSystem->OpenVolume (
                     SimpleFileSystem,
                     &FileProtocol
                 );
        if(!EFI_ERROR(Status))
        {
            EFI_FILE_PROTOCOL* NewFileProtocol;
            Status = FileProtocol->Open (
                         FileProtocol,
                         &NewFileProtocol,
                         EFI_BOOT_FILE_NAME,
                         EFI_FILE_MODE_READ,
                         0
                     );
            if(!EFI_ERROR(Status))
            {
                static NAME_MAP NameMap = {EFI_BOOT_FILE_NAME, NAME_OF_UEFI_OS};
                CreateTargetEfiOsBootOptionFuncPtr(Handle, &NameMap);

                NewFileProtocol->Close(NewFileProtocol);
            }
        }
    }
}

/**
    Search bootable path then create boot option.

    @param  Handle   Handle to locate file system.

    @retval  EFI_SUCCESS   Do not encounter any errors.
    @retval  !=EFI_SUCESS  Any errors.
**/
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SearchBootablePathAndCreateBootOption
//
// Description:	Search bootable path then create boot option.
//
// Input:       EFI_HANDLE Handle - Handle to locate file system
//
// Output:      EFI_SUCCESS   -  Do not encounter any errors
//              !=EFI_SUCCESS -  Any errors
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS SearchBootablePathAndCreateBootOption(EFI_HANDLE Handle)
{
    EFI_STATUS Status;
    UINT16 MatchedBootablePathCount = 0;
    UINT16 AUTO_BOOT_ENTRY_COUNT = GetEfiOsBootNameItemCount();
    EFI_SIMPLE_FILE_SYSTEM_PROTOCOL* SimpleFileSystem;
    EFI_FILE_PROTOCOL *FileProtocol;

    UINTN j;

    if(!Handle) return EFI_INVALID_PARAMETER;

    Status = pBS->HandleProtocol (
                 Handle,
                 &gEfiSimpleFileSystemProtocolGuid,
                 &SimpleFileSystem
             );
    if (EFI_ERROR(Status)) {
        TRACE((-1, "HandleProtocol(SimpleFileSystem): %r\n", Status));
        return Status;
    }

    Status = SimpleFileSystem->OpenVolume (
                 SimpleFileSystem,
                 &FileProtocol
             );
    if (EFI_ERROR(Status)) {
        TRACE((-1, "OpenVolume: %r\n", Status));
        return Status;
    }

    for (j = 0; j < AUTO_BOOT_ENTRY_COUNT; j++) {

        EFI_FILE_PROTOCOL* NewFileProtocol;

        Status = FileProtocol->Open (
                     FileProtocol,
                     &NewFileProtocol,
                     FILE_NAME_MAPS[j].FilePath,
                     EFI_FILE_MODE_READ,
                     0
                 );

        TRACE((-1, "Open(%S): %r\n", FILE_NAME_MAPS[j].FilePath, Status));
        if (EFI_ERROR(Status)) continue;

        if(CreateTargetEfiOsBootOptionFuncPtr(Handle, &FILE_NAME_MAPS[j]))
            MatchedBootablePathCount++;

        NewFileProtocol->Close(NewFileProtocol);
    }

#if CREATE_BOOT_OPTION_WITH_UEFI_FILE_NAME_POLICY == 1
    if(!MatchedBootablePathCount)
        CreateBootOptionWithUefiFileName(Handle);
#endif

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CreateEfiOsBootOption
//
// Description:	Try to find UEFI OSs and create the boot options for them if 
//              they haven't been listed in BootOptionList.
//
// Input:       None
//
// Output:      EFI_SUCCESS   -  Do not encounter any errors
//              !=EFI_SUCCESS -  Any errors
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS CreateEfiOsBootOption(VOID)
{
    EFI_STATUS Status;
    EFI_HANDLE* HandleBuffer = NULL;
    UINTN HandleCount;
    UINTN i;
    EFI_BLOCK_IO_PROTOCOL *BlkIo;

    Status = pBS->LocateHandleBuffer (
                 ByProtocol,
                 &gEfiSimpleFileSystemProtocolGuid,
                 NULL,
                 &HandleCount,
                 &HandleBuffer
             );
    if (EFI_ERROR(Status)) {
        TRACE((-1, "LocateHandleBuffer: %r\n", Status));
        return Status;
    }
    // For each handle found, check if eLink files exist.
    for (i = 0; i < HandleCount; i++) {

        Status=pBS->HandleProtocol( HandleBuffer[i], &gEfiBlockIoProtocolGuid, &BlkIo );
        if ( EFI_ERROR(Status) || BlkIo->Media->RemovableMedia ) continue;	//skip removable device

        DealWithEfiOsBootOptionFuncPtr(HandleBuffer[i]);
    }

    if ( HandleBuffer )
        pBS->FreePool(HandleBuffer);

    return EFI_SUCCESS;
}

                                                                 //(EIP138397+)>
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	RemoveAmiMaskDevicePath
//
// Description: Remove the AMI specific device path from SrcDevicePath.	
//              
// Input:		EFI_DEVICE_PATH_PROTOCOL *SrcDevicePath - Device Path that has AMI
//                                                        mask device path.
//              UINT16 DevicePathSize - Size of SrcDevicePath.
//
// Output:		None.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
RemoveAmiMaskDevicePath( EFI_DEVICE_PATH_PROTOCOL **SrcDevicePath, UINT16 DevicePathSize)
{
    EFI_DEVICE_PATH_PROTOCOL *TmpDevicePath = *SrcDevicePath;
    EFI_GUID AmiMaskedDevicePathGuid = AMI_MASKED_DEVICE_PATH_GUID;

    if(  TmpDevicePath->Type == HARDWARE_DEVICE_PATH
     && TmpDevicePath->SubType == HW_VENDOR_DP 
     && guidcmp(&AmiMaskedDevicePathGuid, &((VENDOR_DEVICE_PATH*)TmpDevicePath)->Guid) == 0 )
    {

        do{
 
            if( TmpDevicePath->Type == MEDIA_DEVICE_PATH 
             && TmpDevicePath->SubType == MEDIA_HARDDRIVE_DP )
            {
                *(SrcDevicePath) = TmpDevicePath;
                break;
            }
            else
            {
                DevicePathSize -= (*(UINT16*)&(TmpDevicePath)->Length[0]);
                TmpDevicePath = NEXT_NODE( TmpDevicePath );
            }

        }while( DevicePathSize > 0 );
    }
}
                                                                 //<(EIP138397+)

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	IsOsCreatedBootOption
//
// Description: Check whether input boot option number is created by OS.
//              
// Input:		UINT16 BootOptionNumber - Number to check.
//
// Output:		BOOLEAN
//                  TRUE    Created by OS.
//                  FALSE   Isn't created by OS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN IsOsCreatedBootOption(UINT16 BootOptionNumber)
{
    EFI_STATUS Status;
    EFI_GUID   EfiOsBootOptionNamesGuid = EFI_OS_BOOT_OPTION_NAMES_GUID;
    UINT16*    EfiOsBootOrder = NULL;
    UINTN      Size = 0;
    BOOLEAN    Ret = TRUE;

    Status = GetEfiVariable(
                L"EfiOsBootOrder",
                &EfiOsBootOptionNamesGuid,
                NULL,
                &Size,
                &EfiOsBootOrder);

    if(!EFI_ERROR(Status))
    {
        UINTN      i;

        Size = Size/sizeof(UINT16);
        for(i = 0; i < Size; i++)
        {
            if(EfiOsBootOrder[i] == BootOptionNumber)
            {
                Ret = FALSE;
                break;
            }
        }

        pBS->FreePool(EfiOsBootOrder);
    }

    return Ret;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	AdjustEfiOsBootOrder
//
// Description: Remove the AMI specific device path from SrcDevicePath.	
//              
// Description: if UEFI OS is existed, kill the duplicated UEFI OS boot options
//              into one and move it to one of their boot order position, and kill
//              all UEFI OS boot options if deivces are disappeared in system.
//
// Input:		None.
//             
// Output:		None.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID AdjustEfiOsBootOrder(VOID)
{
	UINT16 *NewBootOrder = NULL;    //(EIP138397)
	UINT16 BootIndex=0;
	UINT16 *BootOrder_Flag = NULL;  //(EIP138397)
	UINT16 *BootOrder = NULL;
	UINTN BootOrderSize = 0; 
	EFI_STATUS Status;
    BOOLEAN UpdateBootOrder=FALSE, FwBootOption = FALSE;
	UINTN i, j;
	EFI_LOAD_OPTION *NvramOption = NULL;
	UINTN NvramOptionSize;

	TRACE((-1,"EfiOsBootOrder.....\n"));

	Status=GetEfiVariable(
		L"BootOrder", &EfiVariableGuid, NULL, &BootOrderSize, &BootOrder);

	if (EFI_ERROR(Status)) return;
                                                            //(EIP138397)>
    NewBootOrder = MallocZ( BootOrderSize );
    if( NewBootOrder == NULL ) return;
    BootOrder_Flag = MallocZ( BootOrderSize );
    if( BootOrder_Flag == NULL ) return;
                                                            //<(EIP138397)                    
	for(i=0; i<BootOrderSize/sizeof(UINT16); i++)
	{	
		UINTN DescriptionSize;
		EFI_DEVICE_PATH_PROTOCOL *ScrDevicePath;
		CHAR16 BootStr[9];
        UINT32                      *OptionalData;
        UINTN                       OptionalDataSize;
#if RemoveBootOptionWithoutFile
        EFI_HANDLE  DevHandle;
#endif

		TRACE((-1,"Get Boot Option Boot%04X\n", BootOrder[i]));
		if( BootOrder_Flag[i] ) continue;                   //(EIP138397)   
        FwBootOption = FALSE;

		// Get Boot Option
		NvramOption = NULL;
		NvramOptionSize =0;
		Swprintf(BootStr,L"Boot%04X",BootOrder[i]);
		Status=GetEfiVariable(
			BootStr, &EfiVariableGuid, NULL, &NvramOptionSize, &NvramOption
		);
		if (EFI_ERROR(Status)) continue;

		DescriptionSize = (Wcslen((CHAR16*)(NvramOption+1))+1)*sizeof(CHAR16);
		ScrDevicePath =(EFI_DEVICE_PATH_PROTOCOL*)((UINT8*)(NvramOption+1)+DescriptionSize);		

        OptionalData =  (UINT32*)( (UINT8*)ScrDevicePath + NvramOption->FilePathListLength);  //(EIP138397+)
        OptionalDataSize =  (UINT8*)NvramOption + NvramOptionSize - (UINT8*)OptionalData; //(EIP138397+)

        // Check is this a non FW boot option
        if(OptionalDataSize == sizeof(UINT32) &&
           (*OptionalData == AMI_SIMPLE_BOOT_OPTION_SIGNATURE) ||
           (*OptionalData == AMI_GROUP_BOOT_OPTION_SIGNATURE) )
            FwBootOption = TRUE;
                                                              //(EIP138397+)>
        RemoveAmiMaskDevicePath(&ScrDevicePath, NvramOption->FilePathListLength);
                                                              //<(EIP138397+)
#if RemoveBootOptionWithoutFile
        // Check the File exist in EfiOsBootOptionNamesFilePathItem or not.
        // If not exist , remove the variable.
        if(FwBootOption)
        {
            DevHandle = GetGptPartitionHandle(ScrDevicePath);

            if(DevHandle)
            {
                EFI_SIMPLE_FILE_SYSTEM_PROTOCOL* SimpleFileSystem = NULL;
                EFI_FILE_PROTOCOL *FileProtocol = NULL;

                Status = pBS->HandleProtocol (
                        DevHandle,
                        &gEfiSimpleFileSystemProtocolGuid,
                        &SimpleFileSystem);


                if(!EFI_ERROR(Status))
                {
                    UINTN   j;
                    UINT16    AUTO_BOOT_ENTRY_COUNT = GetEfiOsBootNameItemCount();
                    Status = SimpleFileSystem->OpenVolume (
                        SimpleFileSystem,
                        &FileProtocol);

                    if (EFI_ERROR(Status))
                        continue;

                    for (j = 0; j < AUTO_BOOT_ENTRY_COUNT; j++) 
                    {
                        EFI_FILE_PROTOCOL* NewFileProtocol = NULL;
                        Status = FileProtocol->Open (
                                      FileProtocol,
                                      &NewFileProtocol,
                                      EFI_BOOT_FILE_NAME,
                                      EFI_FILE_MODE_READ,
                                      NULL );


                        if(!EFI_ERROR(Status))
                            NewFileProtocol->Close(NewFileProtocol);

                        if(Status == EFI_NOT_FOUND)
                        {
                            //Clear variable Boot####
                            Status = pRS->SetVariable(
                                BootStr, &EfiVariableGuid,
                                BOOT_VARIABLE_ATTRIBUTES, 0, NULL);				
                            BootOrder_Flag[i] = 1;
                            pBS->FreePool(NvramOption);
                            continue;
                        }
                    }
                }
            }
        }
#endif
		if( ScrDevicePath->Type == MEDIA_DEVICE_PATH 
	  	 && ScrDevicePath->SubType == MEDIA_HARDDRIVE_DP ) 
		{
			EFI_HANDLE GptHandle;
			TRACE((-1,"EfiOsBootOrder.c :: BootOrder[%x]=%x %S\n", i, BootOrder[i], (CHAR16*)(NvramOption+1) ));
			GptHandle = GetGptPartitionHandle(ScrDevicePath);
			TRACE((-1,"EfiOsBootOrder.c :: GptHandle=%d\n", GptHandle));
	    
			if( GptHandle != NULL)
			{
                // Only Non Fw Boot Option Kill Other Boot Option
                // This module check duplicate Boot Option exist or not when create boot option
                // So, ignore Fw Boot Option
                if(FwBootOption)
                    continue;
				for(j=0; j<BootOrderSize/sizeof(UINT16); j++)
				{
					CHAR16 BootStr2[9];
					UINTN NvramOptionSize2 = 0;
					EFI_LOAD_OPTION *NvramOption2 = NULL;
                    EFI_DEVICE_PATH_PROTOCOL *DevicePath = NULL;

                    if( BootOrder_Flag[j] || (i == j)) continue;

					TRACE((-1,"EfiOsBootOrder.c :: Search BootOrder[%x]=%x\n", j, BootOrder[j]));
					// Get Boot Option
					NvramOption2 = NULL;
					NvramOptionSize2 =0;
					Swprintf(BootStr2,L"Boot%04X",BootOrder[j]);
					Status=GetEfiVariable(
						BootStr2, &EfiVariableGuid, NULL, &NvramOptionSize2, &NvramOption2
					);
					if (EFI_ERROR(Status)) continue;

					DescriptionSize = (Wcslen((CHAR16*)(NvramOption2+1))+1)*sizeof(CHAR16);
					DevicePath =(EFI_DEVICE_PATH_PROTOCOL*)((UINT8*)(NvramOption2+1)+DescriptionSize);
#if KeepDuplicateNonFWBootOption
                    OptionalData =  (UINT32*)( (UINT8*)DevicePath + NvramOption2->FilePathListLength);
                    OptionalDataSize =  (UINT8*)NvramOption2 + NvramOptionSize2 - (UINT8*)OptionalData;
                    TRACE((-1, "OptionalDataSize(%X)\n", (UINT8*)NvramOption2 + NvramOptionSize2 - (UINT8*)OptionalData));
                    // Skip if this is a non FW boot option
                    if(OptionalDataSize != sizeof(UINT32) || 
                       ((*OptionalData != AMI_SIMPLE_BOOT_OPTION_SIGNATURE) &&
                       (*OptionalData != AMI_GROUP_BOOT_OPTION_SIGNATURE)))
                    {
                        pBS->FreePool(NvramOption2);
                        continue;
                    }
#endif
                                                              //(EIP138397+)>
                    RemoveAmiMaskDevicePath(&DevicePath, NvramOption2->FilePathListLength);
                                                              //<(EIP138397+)
									
                    if( CompareHddDevicePath(ScrDevicePath, DevicePath) == EFI_SUCCESS )         //(EIP126686+)
					{
                        UINTN  ReserveIndex;
                        UINTN  DeleteIndex; 
                        CHAR16 *DeletedStr;

						TRACE((-1,"EfiOsBootOrder.c :: Matched BootOrder[%x]=%x %S\n", j, BootOrder[j], (CHAR16*)(NvramOption2+1) ));

                        if(!DefaultFwBootOption && !IsOsCreatedBootOption(BootOrder[i]))
                        {
                            //
                            //  BootOrder[i] is not created by OS, but BootOrder[j]
                            //
                            ReserveIndex = j;
                            DeleteIndex = i;
                            DeletedStr =  BootStr;
                        }
                        else
                        {
                            ReserveIndex = i;
                            DeleteIndex = j;
                            DeletedStr =  BootStr2;
                        }
                        //Delete EfiOsBootOptionNames boot option.												
                        //Clear variable Boot####
                        pRS->SetVariable(
                            DeletedStr, &EfiVariableGuid,
                            BOOT_VARIABLE_ATTRIBUTES, 0, NULL);

                        BootOrder_Flag[DeleteIndex] = 1;
                        UpdateBootOrder = TRUE;

#if FIXED_BOOT_ORDER_SUPPORT
                        // Handle Fixed Boot Order Priority issue.
                        {
                            UINTN               DevOrderSize = 0;
                            UEFI_DEVICE_ORDER   *DevOrder = NULL, *DevOrder2 = NULL;
                            EFI_GUID            gFixedBootOrderGuid = FIXED_BOOT_ORDER_GUID;
                            UINTN               k = 0;
                            UINT32              Attrib = 0;
                            
                            Status = GetEfiVariable(L"UefiDevOrder", &gFixedBootOrderGuid, &Attrib, &DevOrderSize, &DevOrder);
                            if(!EFI_ERROR(Status))
                            {
                                DevOrder2 = DevOrder;
                                
                                for (DevOrder = DevOrder2
                                    ; (UINT8*)DevOrder < (UINT8*)DevOrder2 + DevOrderSize
                                    ; DevOrder = (UEFI_DEVICE_ORDER*)((UINT8*)DevOrder + DevOrder->Length + sizeof(DevOrder->Type)))
                                {
                                    for (k = 0; k < DEVORDER_COUNT(DevOrder); k++)
                                    {
                                        TRACE((-1,"DevOrder->Device[%x] %x,BootOrder[DeleteIndex] = %x \n",k,DevOrder->Device[k], BootOrder[DeleteIndex]));
                                        if(DevOrder->Device[k] == BootOrder[DeleteIndex])
                                        {
                                            DevOrder->Device[k] = BootOrder[ReserveIndex];
                                            TRACE((-1,"BootOrder[ReserveIndex] %x \n",BootOrder[ReserveIndex]));
                                        }
                                    }
                                }
                                Status = pRS->SetVariable(L"UefiDevOrder", &gFixedBootOrderGuid, Attrib, DevOrderSize, DevOrder2);
                                pBS->FreePool(DevOrder2); 
                            }
                        }
#endif         
                    }

                    pBS->FreePool(NvramOption2);
                } //for (j=0; j<BootOrderSize/sizeof(UINT16); j++)
            } //if ( GptHandle != NULL)
            else
             //GPT HDD NOT FOUND, Remove This BootOrder
            {
                if ( (((HARDDRIVE_DEVICE_PATH*)ScrDevicePath)->MBRType == MBR_TYPE_EFI_PARTITION_TABLE_HEADER) &&
                        FwBootOption)
				{
					//Clear variable Boot####
					Status = pRS->SetVariable(
						BootStr, &EfiVariableGuid,
						BOOT_VARIABLE_ATTRIBUTES, 0, NULL);				
		
                    UpdateBootOrder = TRUE;
                    BootOrder_Flag[i] = 1;
                }
            }
        }

		pBS->FreePool(NvramOption);
	}

	if( UpdateBootOrder )
	{
        TRACE((-1,"EfiOsBootOrder.c :: Update BootOrder, Dump New BootOrder \n" ));
        for(i = 0 ; i < BootOrderSize/sizeof(UINT16) ; i++)
        {
            if(BootOrder_Flag[i])
                continue;
            
            TRACE((-1,"%x ",BootOrder[i]));
            NewBootOrder[BootIndex++] = BootOrder[i];
        }
        TRACE((-1,"\n "));
		pRS->SetVariable(
			L"BootOrder", &EfiVariableGuid,
			BOOT_VARIABLE_ATTRIBUTES, BootIndex * sizeof(UINT16), NewBootOrder);	
	}

    pBS->FreePool(NewBootOrder);
	pBS->FreePool(BootOrder);

}

#if (CSM_SUPPORT == 1) && (RemoveLegacyGptHddDevice == 1)
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	RemoveLegacyGptHdd
//
// Description: Determine whether boot device is a UEFI HDD(GPT format).
//             
// Input:		BOOT_DEVICE Device - Boot device to be checked.
//             
// Output:		TRUE  - Boot Device is a UEFI HDD..
//              FALSE - Boot Device is not a UEFI HDD.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN RemoveLegacyGptHdd(BOOT_DEVICE *Device){
//    EFI_BLOCK_IO_PROTOCOL *BlkIo;
//    EFI_STATUS Status;
//    UINT8 *Buffer = NULL;
//    UINTN index;
//    PARTITION_ENTRY *pEntries;
//
//    if (   Device->DeviceHandle == INVALID_HANDLE
//        || Device->BbsEntry == NULL
//    ) return FALSE;
//     
//    if( Device->BbsEntry->DeviceType != BBS_HARDDISK ) return FALSE;
//
//    Status=pBS->HandleProtocol(
//        Device->DeviceHandle, &gEfiBlockIoProtocolGuid, &BlkIo
//    );
//
//    if (EFI_ERROR(Status) || BlkIo->Media->RemovableMedia) return FALSE;	//USB device?
//
//    Status = pBS->AllocatePool( EfiBootServicesData, BlkIo->Media->BlockSize, &Buffer );
//    if( Buffer == NULL ) return FALSE;
//    
//    // read the first sector
//    BlkIo->ReadBlocks ( BlkIo,
//                        BlkIo->Media->MediaId,
//                        0,
//                        BlkIo->Media->BlockSize,
//  	                (VOID*)Buffer);	
//			
//    if(Buffer[0x1fe]==(UINT8)0x55 && Buffer[0x1ff]==(UINT8)0xaa)	//MBR Signature
//    {
//        pEntries=(PARTITION_ENTRY *)(Buffer+0x1be);
//
//        for(index=0;index<4;index++)
//        {
//            if( pEntries[index].PartitionType==0xee) 	//Check GPT Partition?
//            {
//                pBS->FreePool( Buffer );
//                return TRUE;			//Set Can't Boot.
//            }
//        } //for(index=0;index<4;index++)					
//    }//if(Buffer[0x1fe]==0x55 && Buffer[0x1ff]==0xaa)
//
//    pBS->FreePool( Buffer );
//    return FALSE;

    EFI_STATUS Status;
    SETUP_DATA SetupData;
    UINTN Size = sizeof(SETUP_DATA);
    EFI_GUID SetupGuid = SETUP_GUID;

    Status = pRS->GetVariable(L"Setup", &SetupGuid, NULL, &Size, &SetupData);

//    if( Device->BbsEntry->DeviceType != BBS_HARDDISK && SetupData.OnlyBootHDD == 1 ) return TRUE;
    if( Device->BbsEntry->Class != PCI_CL_MASS_STOR && SetupData.OnlyBootHDD == 1 ) return TRUE;
    return FALSE;
}
#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	IsSpecifiedUefiOsBootOption
//
// Description: Check whether specified uefi os boot option.
//             
// Input:		BOOT_OPTION Option - boot option to check.
//             
// Output:		TRUE  - Is specified uefi os boot option
//              FALSE - Isn't specified uefi os boot option
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN IsSpecifiedUefiOsBootOption(BOOT_OPTION *Option)
{
    UINTN i, j;
    NAME_MAP  UefiOsNameMap[] = {{EFI_BOOT_FILE_NAME, NAME_OF_UEFI_OS}, {NULL, NULL}};
    NAME_MAP* NameMaps[] = {
                            FILE_NAME_MAPS, 
#if CREATE_BOOT_OPTION_WITH_UEFI_FILE_NAME_POLICY == 1
                            UefiOsNameMap,
#endif
                            NULL
                            };

    if(!Option) return FALSE;
	
	if(IsLegacyBootOption(Option)) return FALSE;

    for(i = 0; NameMaps[i]; i++)
    {
        NAME_MAP *NameMapWalker = NameMaps[i];
        for (j = 0; NameMapWalker[j].FilePath; j++) 
        {
            // check option name length, if OptionName < FileNameMaps, don't skip boot option
            if ( Wcslen(Option->Description) < Wcslen(NameMapWalker[j].BootOptionName))
                continue ;
            // check option string
            if ( !MemCmp( Option->Description, NameMapWalker[j].BootOptionName, 
                          Wcslen(NameMapWalker[j].BootOptionName)*sizeof(CHAR16)))
            {
                // check option device path.
                EFI_DEVICE_PATH_PROTOCOL *Dp = Option->FilePathList ;
                BOOLEAN HardDriveFlag=FALSE, MediaFilePathFlag=FALSE ;
                while(!isEndNode(Dp))
                {
                    if (Dp->Type == MEDIA_DEVICE_PATH && Dp->SubType == MEDIA_HARDDRIVE_DP)
                        HardDriveFlag = TRUE ;
                    if (Dp->Type == MEDIA_DEVICE_PATH && Dp->SubType == MEDIA_FILEPATH_DP)
                        MediaFilePathFlag = TRUE ;
                    Dp = NEXT_NODE(Dp) ;
                }
                
                if (HardDriveFlag && MediaFilePathFlag)
                {
                    TRACE((-1,"%S don't normalize.\n", Option->Description )) ;
                    return TRUE;
                }
            }
        }
    } 

    return FALSE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	EfiOsName_NormalizeBootOptions
//
// Description: If normalization is enabled, regenerates all the description strings
//              and/or file path lists. This function override BDS kernel, because Uefi
//              Os Boot Option can't be normalize file path and names.
//             
// Input:		None.
//             
// Output:		None.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID EfiOsName_NormalizeBootOptions(){
    DLINK *Link;
    BOOT_OPTION *Option;

    // Normalize boot options 
    //(regenerate the description string and the file path list)
    FOR_EACH_BOOT_OPTION(BootOptionList,Link,Option){

        if (   !Option->FwBootOption || !IsBootOptionWithDevice(Option)
            || Option->BootOptionNumber == INVALID_BOOT_OPTION_NUMBER
        ) continue;
        
        // Skip Uefi Hdd Os boot option
        if (IsSpecifiedUefiOsBootOption(Option)) continue ;
        
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
// Procedure:	AdjustNewUefiOsOptionPriority
//
// Description: Adjust new UEFI OS boot option priority.
//              Follow the policy NEW_UEFI_OS_OPTION_ORDER_POLICY
//              to change priority with new UEFI OS boot option.
//             
// Input:		None.
//             
// Output:		None.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
AdjustNewUefiOsOptionPriority()
{
    EFI_STATUS  Status;
    DLINK       *Link;   
    BOOT_OPTION *Option;
    UINTN     Size;
    UINTN     x = 0;
    UINT32    Priority = 0;
    UINT8     NewOptionPolicy;
    EFI_GUID  EfiOsBootOptionNamesGuid = EFI_OS_BOOT_OPTION_NAMES_GUID;
    
    TRACE((-1,"EfiOsBootOrder.c : Update new Uefi OS option priority\n")) ;
   
    // if no new EFI OS boot option added, just return. 
    if (!NewEfiOsOptionDpListCount) return ;
	
	Size = sizeof (UINT8);
    Status = pRS->GetVariable (
              L"NewOptionPolicy",
              &EfiOsBootOptionNamesGuid,
              NULL,
              &Size,
              (VOID *) &NewOptionPolicy
              );
    
    if(EFI_ERROR(Status))
    {
        pBS->FreePool(NewEfiOsOptionDpList) ;
        return;
    }
        
    if (NewOptionPolicy == 0)
    {
        pBS->FreePool(NewEfiOsOptionDpList) ;
        return;
    }
    else if (NewOptionPolicy == 1)
    {
        Priority = LOWEST_BOOT_OPTION_PRIORITY ;
        FOR_EACH_BOOT_OPTION(BootOptionList,Link,Option)
        {
            if (Option->Priority < Priority)
                Priority = Option->Priority ;
            Option->Priority += (UINT32)NewEfiOsOptionDpListCount ;
        }   
    }
    else if (NewOptionPolicy == 2)
    {
        Priority = 0 ;
        FOR_EACH_BOOT_OPTION(BootOptionList,Link,Option)
        {
            if (Option->Priority > Priority)
                Priority = Option->Priority + 1  ;
        }
    }
    
    for ( x=0 ; x<NewEfiOsOptionDpListCount ; x++ )
    {
        EFI_DEVICE_PATH_PROTOCOL *Dp;
        
        Dp = *(NewEfiOsOptionDpList+x);
        FOR_EACH_BOOT_OPTION(BootOptionList,Link,Option)
        {
            if (Option->FilePathList == Dp)
                Option->Priority = Priority++ ;
        }
    } 
    NewEfiOsOptionDpListCount = 0 ;
    pBS->FreePool(NewEfiOsOptionDpList) ;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	SaveEfiOsBootOrder
//
// Description: Save the boot order to check later, 
//              then we can know which one is created by OS.
//             
// Input:		None.
//             
// Output:		None.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID SaveEfiOsBootOrder()
{
    EFI_STATUS Status;
    UINTN      BootOrderSize = 0;
    UINT16*    BootOrder = NULL;

    Status = GetEfiVariable(
                L"BootOrder", 
                &EfiVariableGuid, 
                NULL, 
                &BootOrderSize, 
                &BootOrder);

    if(!EFI_ERROR(Status))
    {
        EFI_GUID  EfiOsBootOptionNamesGuid = EFI_OS_BOOT_OPTION_NAMES_GUID;

        pRS->SetVariable(
            L"EfiOsBootOrder", 
            &EfiOsBootOptionNamesGuid,
            EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS,
            BootOrderSize, 
            (VOID*)BootOrder);

        pBS->FreePool(BootOrder);
    }
}

//***********************************************************************
//#**********************************************************************
//#**                                                                  **
//#**        (C)Copyright 1985-2015, American Megatrends, Inc.         **
//#**                                                                  **
//#**                       All Rights Reserved.                       **
//#**                                                                  **
//#**              5555 Oak brook Pkwy, Norcorss, GA 30093             **
//#**                                                                  **
//#**                       Phone: (770)-246-8600                      **
//#**                                                                  **
//#**********************************************************************
