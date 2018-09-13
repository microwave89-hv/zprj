//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
//**                                                             **//
//**         (C)Copyright 2010, American Megatrends, Inc.        **//
//**                                                             **//
//**                     All Rights Reserved.                    **//
//**                                                             **//
//**   5555 Oakbrook Pkwy, Building 200,Norcross, Georgia 30093  **//
//**                                                             **//
//**                     Phone (770)-246-8600                    **//
//**                                                             **//
//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseAdvanced/Bbs.c $
//
// $Author: Arunsb $
//
// $Revision: 13 $
//
// $Date: 10/18/12 5:53a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseAdvanced/Bbs.c $
// 
// 13    10/18/12 5:53a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 13    10/10/12 12:35p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 12    5/29/12 3:44a Arunsb
// [TAG]  		EIP91109
// [Category]  	Improvement
// [Description]  	Sync the Aptio IV source for AptioV
// 
// 11    11/13/11 12:33p Arunsb
// [TAG]  		EIP70421
// [Category]  	New Feature
// [Description]  	Support for driver order in TSE
// [Files]  		AMITSE.SDL, CommonHelper.c, setup.ini, uefisetup.ini,
// boot.c,
// minisetup.h, bbs.c, special.c, special.h, tseadvanced.c,
// addbootoption.c,
// callback.c, minisetupext.c, minisetupext.h, popupsel.c, popupsel.h,
// TseLitehelper.c, variable.c, Uefi21Wapper.c, AMIVfr.h, boot.h,
// TseElink.h, variable.h, 
// setup.h, Boot.vfr and Setup.uni
// 
// 10    2/04/11 4:43p Mallikarjunanv
// added the UpdateBootVariables() fucntion to update BOOT and BBS order
// variables
// 
// 9     12/21/10 11:48a Mallikarjunanv
// 
// 9     9/21/10 11:26a Madhans
// EIP44542 changes
// 
// 7     9/20/10 6:47p Madhans
// [TAG]    	EIP44542
// [Category]	BUILD ISSUE FIX
// [Symptom]	Build issues with TSE label (INT)4.6.2_TSE_2_10_1207_TEST
// when IdeSecurity and FastBoot modules added to the project
// [RootCause] -
// [Solution]	Build issues resolved
// [Files]		CommonHelper.c, Tsecommon.h, Hiilib.h, Boot.h, minisetup.h,
// bbs.c, special.c, Bds.c TseLitehelp
// 
// 6     9/16/10 8:38p Madhans
// Update for TSE 2.10. Refer Changelog.log for more details.
// 
// 8     9/16/10 3:14p Madhans
// To Avoid build issues with TSE_USE_EDK_LIBRARY Building.
// 
// 7     9/13/10 4:35p Madhans
// To avoid build issue when EDK Build Support is turned off. Aptio 4.6.x
// does not define I2O_DEVICE_PATH structure.
// 
// 6     7/28/10 4:46a Mallikarjunanv
// EIP-29951: TSE Device Path Name support updated
// 
// 5     2/19/10 8:11a Mallikarjunanv
// updated year in copyright message
// 
// 4     1/09/10 4:47a Mallikarjunanv
// Updated TSE2.01 Release sources with coding standards
// 
// 3     6/23/09 7:09p Blaines
// Coding standard update, 
// Remove spaces from file header to allow proper chm function list
// creation.
// 
// 2     6/12/09 7:43p Presannar
// Initial implementation of coding standards for AMITSE2.0
// 
// 1     6/04/09 8:05p Madhans
// 
// 1     4/28/09 11:16p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 1     4/28/09 10:27p Madhans
// Tse 2.0 Code complete Checkin.
// 
//
//*****************************************************************//
//*****************************************************************//

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		bds.c
//
// Description:	This file contains code for legacy boot device handling
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "minisetup.h"



//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	GetDevStr
//
// Description:	function to get the device strings
//
// Input:	UINT16 DevType
//
// Output:	device string
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
CHAR16 *GetDevStr(UINT16 DevType)
{
    CHAR16 *DevText=NULL;

    switch ( DevType )
	{
		case BBS_TYPE_FLOPPY:
			DevText = HiiGetString(gHiiHandle, STRING_TOKEN(STR_FDD));
		break;

		case BBS_TYPE_HARDDRIVE:
			DevText = HiiGetString(gHiiHandle, STRING_TOKEN(STR_HDD));
		break;

		case BBS_TYPE_CDROM:
			DevText = HiiGetString(gHiiHandle, STRING_TOKEN(STR_CDROM));
		break;

		case BBS_TYPE_USB:
			DevText = HiiGetString(gHiiHandle, STRING_TOKEN(STR_USB));
		break;

		case BBS_TYPE_EMBEDDED_NETWORK:
			DevText = HiiGetString(gHiiHandle, STRING_TOKEN(STR_NETWORK));
		break;

		case BBS_TYPE_DEV:
			DevText = HiiGetString(gHiiHandle, STRING_TOKEN(STR_BEV));
		break;
	}

    return DevText;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	IsSATADevice
//
// Description:	function to check for SATA Devices
//
// Input:	UINT16 *IdentifyDriveData - 512 bytes of device information
//
// Output:	TRUE/FALSE
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN IsSATADevice(UINT16 *IdentifyDriveData)
{
    UINT16 data16;

    if(NULL == IdentifyDriveData)
        return FALSE;

    // Check Word76 for BIT1 and BIT2; set for SATA drives
    data16 = IdentifyDriveData[76];
	if ((data16 != 0xFFFF) && (data16 & 6))
    {
		return TRUE;
	}

    return FALSE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	GetBusStr
//
// Description:	function to get the bus type string
//
// Input:	EFI_HANDLE Handle, UINTN index, HDD_INFO *HDDInfo
//
// Output:	Bus string
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
CHAR16 *GetBusStr(EFI_HANDLE Handle, UINTN index, HDD_INFO *HDDInfo)
{
    EFI_STATUS Status;
    EFI_DEVICE_PATH_PROTOCOL    *DevPath = NULL;
    UINT8 PortNo;
    CHAR16 *Format = NULL;
    CHAR16 *BusText = NULL;

    //Right now generate names only for internal devices (index 1 to
    //16). Devices reported by option ROMs will show string provided
    //by Option ROMs. Later this may be extended for all devices.
//    if((index<1) || (index>16))
//        return NULL;

    if (!Handle)
        return NULL;

    Status = gBS->HandleProtocol(Handle, &gEfiDevicePathProtocolGuid, &DevPath);

    if(EFI_ERROR(Status))
        return NULL;

    while( !(IsDevicePathEnd(DevPath)) )
    {
        if(MESSAGING_DEVICE_PATH == DevPath->Type)
        {
            switch(DevPath->SubType)
            {
                case MSG_ATAPI_DP:
                    PortNo = (((ATAPI_DEVICE_PATH*)DevPath)->PrimarySecondary<<1)|((ATAPI_DEVICE_PATH*)DevPath)->SlaveMaster;
                    if(IsSATADevice(HDDInfo[(index-1)/2].IdentifyDrive[(index-1)%2].Raw))
                    {
                        BusText = (CHAR16 *)EfiLibAllocatePool(MAX_DRIVE_NAME * sizeof(CHAR16));
                        Format = HiiGetString(gHiiHandle, STRING_TOKEN(STR_SATA_X));
                        SPrint(BusText, MAX_DRIVE_NAME, Format, PortNo);
                    }
                    else
                    {
                        switch(PortNo)
                        {
                            case 0:
                                BusText = HiiGetString(gHiiHandle, STRING_TOKEN(STR_PRI_MAS));
                            break;
                            case 1:
                                BusText = HiiGetString(gHiiHandle, STRING_TOKEN(STR_PRI_SLA));
                            break;
                            case 2:
                                BusText = HiiGetString(gHiiHandle, STRING_TOKEN(STR_SEC_MAS));
                            break;
                            case 3:
                                BusText = HiiGetString(gHiiHandle, STRING_TOKEN(STR_SEC_SLA));
                            break;
                        }
                    }
                break;
                //EIP-29951: extended for all devices.
                case MSG_SCSI_DP:
                { //Showing the SCSI device with Physical and Logical unit numbers
                    UINT16 PhyUnitNum, LogclUnitNum;
                    PhyUnitNum = ((SCSI_DEVICE_PATH*)DevPath)->Pun;
                    LogclUnitNum = ((SCSI_DEVICE_PATH*)DevPath)->Lun;

                    BusText = (CHAR16 *)EfiLibAllocatePool(MAX_DRIVE_NAME * sizeof(CHAR16));
                    Format = HiiGetString(gHiiHandle, STRING_TOKEN(STR_SCSI_DP));
                    SPrint(BusText, MAX_DRIVE_NAME, Format, PhyUnitNum, LogclUnitNum);
                }
                break;

                case MSG_FIBRECHANNEL_DP:
                {// showing Fibre channel with Logical unit number and WWN
                    UINT64	WWN,Lun;
                    WWN = ((FIBRECHANNEL_DEVICE_PATH*)DevPath)->WWN;
                    Lun = ((FIBRECHANNEL_DEVICE_PATH*)DevPath)->Lun;

                    BusText = (CHAR16 *)EfiLibAllocatePool(MAX_DRIVE_NAME * sizeof(CHAR16));
                    Format = HiiGetString(gHiiHandle, STRING_TOKEN(STR_FIBRE_CHANNEL_DP));
                    SPrint(BusText, MAX_DRIVE_NAME, Format, Lun, WWN);
                }
                break;

                case MSG_1394_DP:
                    //For 1394 device support			
                    BusText = (CHAR16 *)EfiLibAllocatePool(MAX_DRIVE_NAME * sizeof(CHAR16));
                    Format = HiiGetString(gHiiHandle, STRING_TOKEN(STR_1394_DP));
                    SPrint(BusText, MAX_DRIVE_NAME, Format);
                break;

                case MSG_USB_DP:
		{
                    // usb device with port number
                    PortNo = ((USB_DEVICE_PATH*)DevPath)->ParentPortNumber;

                    BusText = (CHAR16 *)EfiLibAllocatePool(MAX_DRIVE_NAME * sizeof(CHAR16));
                    Format = HiiGetString(gHiiHandle, STRING_TOKEN(STR_USB_DP));
                    SPrint(BusText, MAX_DRIVE_NAME, Format, PortNo);
		}
                break;

                case MSG_I2O_DP:
                { // I2O device with Tid
                    UINT32	Tid;

                    Tid = ((AMITSE_I2O_DEVICE_PATH*)DevPath)->Tid;
                    BusText = (CHAR16 *)EfiLibAllocatePool(MAX_DRIVE_NAME * sizeof(CHAR16));
                    Format = HiiGetString(gHiiHandle, STRING_TOKEN(STR_I20_DP));
                    SPrint(BusText, MAX_DRIVE_NAME, Format, Tid);
                }
                break;

                case MSG_INFINIBAND_DP:	//Need to know what type of device is this..
                { // InfiniBand device with Device Id
                    UINT64	DeviceId;

                    DeviceId = ((INFINIBAND_DEVICE_PATH*)DevPath)->DeviceId;
                    BusText = (CHAR16 *)EfiLibAllocatePool(MAX_DRIVE_NAME * sizeof(CHAR16));
                    Format = HiiGetString(gHiiHandle, STRING_TOKEN(STR_INFINIBAND_DP));
                    SPrint(BusText, MAX_DRIVE_NAME, Format, DeviceId);
                }
                break;

                case MSG_VENDOR_DP:
                    // for vendor specific device
                    BusText = (CHAR16 *)EfiLibAllocatePool(MAX_DRIVE_NAME * sizeof(CHAR16));
                    Format = HiiGetString(gHiiHandle, STRING_TOKEN(STR_VENDOR_DP));
                    SPrint(BusText, MAX_DRIVE_NAME, Format);
                break;

                case MSG_MAC_ADDR_DP:
                { // network device with mac address
                    UINT8	Mac[32];

                    MemCopy( Mac, (UINT8*)&(((AMITSE_MAC_ADDR_DEVICE_PATH*)DevPath)->MacAddress),32*sizeof(UINT8));
                    BusText = (CHAR16 *)EfiLibAllocatePool(MAX_DRIVE_NAME * sizeof(CHAR16));
                    Format = HiiGetString(gHiiHandle, STRING_TOKEN(STR_MAC_DP));
                    SPrint(BusText, MAX_DRIVE_NAME, Format, Mac);
                }

                break;

                case MSG_IPv4_DP:
                { //IPv4 Device with Logical Port number
                    UINT16	LocalPort;

                    LocalPort = ((IPv4_DEVICE_PATH*)DevPath)->LocalPort;

                    BusText = (CHAR16 *)EfiLibAllocatePool(MAX_DRIVE_NAME * sizeof(CHAR16));
                    Format = HiiGetString(gHiiHandle, STRING_TOKEN(STR_NETWORK_IPV4_DP));
                    SPrint(BusText, MAX_DRIVE_NAME, Format, LocalPort);
                }
                break;

                case MSG_IPv6_DP:
                { //IPv6 Device with Logical Port number
                    UINT16	LocalPort;

                    LocalPort = ((IPv6_DEVICE_PATH*)DevPath)->LocalPort;

                    BusText = (CHAR16 *)EfiLibAllocatePool(MAX_DRIVE_NAME * sizeof(CHAR16));
                    Format = HiiGetString(gHiiHandle, STRING_TOKEN(STR_NETWORK_IPV6_DP));
                    SPrint(BusText, MAX_DRIVE_NAME, Format, LocalPort);
                }

                break;

                case MSG_UART_DP:
                { //UART device with Baud Rate
                    UINT64	BaudRate;

                    BaudRate = ((UART_DEVICE_PATH*)DevPath)->BaudRate;

                    BusText = (CHAR16 *)EfiLibAllocatePool(MAX_DRIVE_NAME * sizeof(CHAR16));
                    Format = HiiGetString(gHiiHandle, STRING_TOKEN(STR_UART_DP));
                    SPrint(BusText, MAX_DRIVE_NAME, Format, BaudRate);
                }
                break;

                case MSG_USB_CLASS_DP:
                { ////for UBS Class id specific devices.
                    UINT8	DeviceClass;

                    DeviceClass = ((USB_CLASS_DEVICE_PATH*)DevPath)->DeviceClass;
                    BusText = (CHAR16 *)EfiLibAllocatePool(MAX_DRIVE_NAME * sizeof(CHAR16));
                    switch(DeviceClass)
                    { //To show the type of device based on the class
                    	case USB_PHY_DEV_CLASS:
                    		Format = HiiGetString(gHiiHandle, STRING_TOKEN(STR_USB_CLASS_PHY_DP));
			break;

                    	case USB_MASS_DEV_CLASS:
                    		Format = HiiGetString(gHiiHandle, STRING_TOKEN(STR_USB_CLASS_MASS_DP));
			break;

                    	default:
                    		Format = HiiGetString(gHiiHandle, STRING_TOKEN(STR_USB_CLASS_DP));
	
                    }
                    SPrint(BusText, MAX_DRIVE_NAME, Format, DeviceClass);
                }
                break;

                case MSG_USB_WWID_CLASS_DP:
                    //need the info about USB WWID devices...
                break;

                case MSG_USB_LOGICAL_UNIT_CLASS_DP:
                { //for USB logical unit class devices with Logical Unit Numnber
                    UINT8	Lun;

#if TSE_USE_EDK_LIBRARY
                    Lun = ((DEVICE_LOGICAL_UNIT_DEVICE_PATH*)DevPath)->Lun;
#else
                    Lun = ((LOGICAL_UNIT_DEVICE_PATH*)DevPath)->Lun; 
#endif
                    BusText = (CHAR16 *)EfiLibAllocatePool(MAX_DRIVE_NAME * sizeof(CHAR16));
                    Format = HiiGetString(gHiiHandle, STRING_TOKEN(STR_USB_LOGICAL_DP));
                    SPrint(BusText, MAX_DRIVE_NAME, Format, Lun);
                }
                break;

                case MSG_USB_SATA_DP:
                { // for USB SATA devices with Port Number
                    UINT16	PortNumber;
                    PortNumber = ((AMITSE_SATA_DEVICE_PATH*)DevPath)->HBAPortNumber;
                    BusText = (CHAR16 *)EfiLibAllocatePool(MAX_DRIVE_NAME * sizeof(CHAR16));
                    Format = HiiGetString(gHiiHandle, STRING_TOKEN(STR_USB_SATA_DP));
                    SPrint(BusText, MAX_DRIVE_NAME, Format, PortNumber);
                }
                break;

                case MSG_USB_ISCSI_DP:
                { // for USB iSCSI devices with Logical Unit Number
                    UINT64	Lun;
                    Lun = ((AMITSE_ISCSI_DEVICE_PATH*)DevPath)->Lun;
                    BusText = (CHAR16 *)EfiLibAllocatePool(MAX_DRIVE_NAME * sizeof(CHAR16));
                    Format = HiiGetString(gHiiHandle, STRING_TOKEN(STR_USB_ISCSI_DP));
                    SPrint(BusText, MAX_DRIVE_NAME, Format, Lun);
                }
                break;
            }
        }

        DevPath = NextDevicePathNode(DevPath);
    }

    MemFreePointer((VOID **) &Format);
    return BusText;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	BBSBuildDevicePathName
//
// Description:	function to build the bbs device path
//
// Input:	CHAR16 *String, BBS_TABLE *info, UINTN index, HDD_INFO *HDDInfo
//
// Output:	None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID BBSBuildDevicePathName( CHAR16 *String, BBS_TABLE *info, UINTN index, HDD_INFO *HDDInfo )
{
    EFI_HANDLE Handle;
    CHAR16 *BusText, *DevText;
    UINT8 *StringDesc;
    UINTN i;

    Handle = *(VOID**)(&info->IBV1);

    BusText = GetBusStr(Handle, index, HDDInfo);
    DevText = GetDevStr(info->DeviceType);

    if(BusText && DevText)
    {
        SPrint(String, MAX_DRIVE_NAME, L"%s %s", BusText, DevText);
    }
    else
    {
        StringDesc = (UINT8*)(UINTN)((info->DescStringSegment << 4) +
			info->DescStringOffset);
    	if ( StringDesc != NULL )
    	{
    		for ( i = 0; (i < (MAX_DRIVE_NAME - 1)) && (StringDesc[i] != '\0'); i++ )
    			String[i] = (CHAR16)StringDesc[i];
    		String[i] = L'\0';
    	}
        else
        {
            SPrint(String, MAX_DRIVE_NAME, L"%s %s", BusText ? BusText : L"Unknown", DevText ? DevText : L"Unknown");
        }
    }

    MemFreePointer((VOID **)&BusText);
    MemFreePointer((VOID **)&DevText);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	UpdateLegacyDevVariable
//
// Description:	
//
// Input:	UINT16 NoOfLegacyGroups
//
// Output:	None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID UpdateLegacyDevVariable(UINT16 NoOfLegacyGroups)
{
	VarSetNvramName( L"LegacyDev", &gLegacyDevGuid, EFI_VARIABLE_BOOTSERVICE_ACCESS, &NoOfLegacyGroups, sizeof(NoOfLegacyGroups) );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	BBSUpdateOrder
//
// Description:	function to update Bbs device order
//
// Input:	UINT16 *newOption,UINT32 *offset,UINTN *size, VOID **buffer
//
// Output:	None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID BBSUpdateOrder(UINT16 *newOption,UINT32 *offset,UINTN *size, VOID **buffer)
{
    UINT8 *pDevOrder;
    UINT16 count = 0, *optionList = NULL, oldOption;
    UINTN i,j,optionNumber;

    *size = 0;

	pDevOrder = VarGetVariable( VARIABLE_ID_BBS_ORDER, size );

    *offset -= (sizeof(UINT32) + sizeof(UINT16));

    count = gCurrLegacyBootData->LegacyDevCount;
    *offset -= (UINT32)gCurrLegacyBootData->LegacyEntryOffset;
    optionList = (UINT16 *)(pDevOrder + gCurrLegacyBootData->LegacyEntryOffset + sizeof(UINT32) + sizeof(UINT16));
    optionNumber = *offset / sizeof(UINT16);
    
    *offset = 0;
    *buffer = (VOID *)pDevOrder;

    oldOption = optionList[optionNumber];

    if ( *newOption == oldOption )
		return;

    if(DISABLED_BOOT_OPTION == *newOption)
    {
        for(i = optionNumber; i < count; i++)
        {
            if((i+1) < count)
                optionList[i] = optionList[i + 1];
            else
                optionList[i] = *newOption; // or DISABLED_BOOT_OPTION
        }
    }
    else if(DISABLED_BOOT_OPTION == oldOption)
    {
        //Find newOption's position
        for(i=0;i<count;i++)
        {
            if(*newOption == optionList[i])
                break;
        }

        if(i < count)//New option found
        {
            //Move new option to the last of enabled devices
            for(j=i; j<count; j++)
            {
                if( DISABLED_BOOT_OPTION != optionList[j+1])
                    optionList[j] = optionList[j+1];
                else
                {
                    optionList[j] = *newOption;
                    break;
                }
            }
        }
        else//New option not enabled
        {
            //Replace first disabled with new one
            for(i=0;i<count;i++)
            {
                if(DISABLED_BOOT_OPTION == optionList[i])
                    break;
            }
            optionList[i] = *newOption;
        }
    }
    else
    {
        optionList[optionNumber] = *newOption;
        for(i=0;i<count;i++)
        {
            if(i == optionNumber)
                continue;
            if(*newOption == optionList[i])
            {
                optionList[i] = oldOption;
                break;
            }
        }
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	GetUefiDevPathString
//
// Description:	function to get the device string using device path for UEFI options.
//
// Input:	EFI_DEVICE_PATH_PROTOCOL *DevPath
//
// Output:	Device string.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
CHAR16 *GetUefiDevPathString(EFI_DEVICE_PATH_PROTOCOL *DevPath)
{
    UINT8 PortNo;
    CHAR16 *Format = NULL;
    CHAR16 *BusText = NULL;
    CHAR16 *DevText = NULL;
    CHAR16 *String = NULL;

    while( !(IsDevicePathEnd(DevPath)) )
    {
        if(MESSAGING_DEVICE_PATH == DevPath->Type)
        {
            switch(DevPath->SubType)
            {
                case MSG_ATAPI_DP:
                    PortNo = (((ATAPI_DEVICE_PATH*)DevPath)->PrimarySecondary<<1)|((ATAPI_DEVICE_PATH*)DevPath)->SlaveMaster;
                    switch(PortNo)
                    {
                        case 0:
                            BusText = HiiGetString(gHiiHandle, STRING_TOKEN(STR_PRI_MAS));
                        break;
                        case 1:
                            BusText = HiiGetString(gHiiHandle, STRING_TOKEN(STR_PRI_SLA));
                        break;
                        case 2:
                            BusText = HiiGetString(gHiiHandle, STRING_TOKEN(STR_SEC_MAS));
                        break;
                        case 3:
                            BusText = HiiGetString(gHiiHandle, STRING_TOKEN(STR_SEC_SLA));
                        break;
                    }
                break;
                //Later this may be extended for all devices.
                case MSG_SCSI_DP:
                { //Showing the SCSI device with Physical and Logical unit numbers
                    UINT16 PhyUnitNum, LogclUnitNum;
                    PhyUnitNum = ((SCSI_DEVICE_PATH*)DevPath)->Pun;
                    LogclUnitNum = ((SCSI_DEVICE_PATH*)DevPath)->Lun;

                    BusText = (CHAR16 *)EfiLibAllocatePool(MAX_DRIVE_NAME * sizeof(CHAR16));
                    Format = HiiGetString(gHiiHandle, STRING_TOKEN(STR_SCSI_DP));
                    SPrint(BusText, MAX_DRIVE_NAME, Format, PhyUnitNum, LogclUnitNum);
                }
                break;

                case MSG_FIBRECHANNEL_DP:
                {// showing Fibre channel with Logical unit number and WWN
                    UINT64	WWN,Lun;
                    WWN = ((FIBRECHANNEL_DEVICE_PATH*)DevPath)->WWN;
                    Lun = ((FIBRECHANNEL_DEVICE_PATH*)DevPath)->Lun;

                    BusText = (CHAR16 *)EfiLibAllocatePool(MAX_DRIVE_NAME * sizeof(CHAR16));
                    Format = HiiGetString(gHiiHandle, STRING_TOKEN(STR_FIBRE_CHANNEL_DP));
                    SPrint(BusText, MAX_DRIVE_NAME, Format, Lun, WWN);
                }
                break;

                case MSG_1394_DP:
                    //For 1394 device support			
                    BusText = (CHAR16 *)EfiLibAllocatePool(MAX_DRIVE_NAME * sizeof(CHAR16));
                    Format = HiiGetString(gHiiHandle, STRING_TOKEN(STR_1394_DP));
                    SPrint(BusText, MAX_DRIVE_NAME, Format);
                break;

                case MSG_USB_DP:
		{
                    // usb device with port number
                    PortNo = ((USB_DEVICE_PATH*)DevPath)->ParentPortNumber;

                    BusText = (CHAR16 *)EfiLibAllocatePool(MAX_DRIVE_NAME * sizeof(CHAR16));
                    Format = HiiGetString(gHiiHandle, STRING_TOKEN(STR_USB_DP));
                    SPrint(BusText, MAX_DRIVE_NAME, Format, PortNo);
		}
                break;

                case MSG_I2O_DP:
                { // I2O device with Tid
                    UINT32	Tid;

                    Tid = ((AMITSE_I2O_DEVICE_PATH*)DevPath)->Tid;
                    BusText = (CHAR16 *)EfiLibAllocatePool(MAX_DRIVE_NAME * sizeof(CHAR16));
                    Format = HiiGetString(gHiiHandle, STRING_TOKEN(STR_I20_DP));
                    SPrint(BusText, MAX_DRIVE_NAME, Format, Tid);
                }
                break;

                case MSG_INFINIBAND_DP:	//Need to know what type of device is this..
                { // InfiniBand device with Device Id
                    UINT64	DeviceId;

                    DeviceId = ((INFINIBAND_DEVICE_PATH*)DevPath)->DeviceId;
                    BusText = (CHAR16 *)EfiLibAllocatePool(MAX_DRIVE_NAME * sizeof(CHAR16));
                    Format = HiiGetString(gHiiHandle, STRING_TOKEN(STR_INFINIBAND_DP));
                    SPrint(BusText, MAX_DRIVE_NAME, Format, DeviceId);
                }
                break;

                case MSG_VENDOR_DP:
                    // for vendor specific device
                    BusText = (CHAR16 *)EfiLibAllocatePool(MAX_DRIVE_NAME * sizeof(CHAR16));
                    Format = HiiGetString(gHiiHandle, STRING_TOKEN(STR_VENDOR_DP));
                    SPrint(BusText, MAX_DRIVE_NAME, Format);
                break;

                case MSG_MAC_ADDR_DP:
                { // network device with mac address
                    UINT8	Mac[32];

                    MemCopy( Mac, (UINT8*)&(((AMITSE_MAC_ADDR_DEVICE_PATH*)DevPath)->MacAddress),32*sizeof(UINT8));
                    BusText = (CHAR16 *)EfiLibAllocatePool(MAX_DRIVE_NAME * sizeof(CHAR16));
                    Format = HiiGetString(gHiiHandle, STRING_TOKEN(STR_MAC_DP));
                    SPrint(BusText, MAX_DRIVE_NAME, Format, Mac);
                }

                break;

                case MSG_IPv4_DP:
                { //IPv4 Device with Logical Port number
                    UINT16	LocalPort;

                    LocalPort = ((IPv4_DEVICE_PATH*)DevPath)->LocalPort;

                    BusText = (CHAR16 *)EfiLibAllocatePool(MAX_DRIVE_NAME * sizeof(CHAR16));
                    Format = HiiGetString(gHiiHandle, STRING_TOKEN(STR_NETWORK_IPV4_DP));
                    SPrint(BusText, MAX_DRIVE_NAME, Format, LocalPort);
                }
                break;

                case MSG_IPv6_DP:
                { //IPv6 Device with Logical Port number
                    UINT16	LocalPort;

                    LocalPort = ((IPv6_DEVICE_PATH*)DevPath)->LocalPort;

                    BusText = (CHAR16 *)EfiLibAllocatePool(MAX_DRIVE_NAME * sizeof(CHAR16));
                    Format = HiiGetString(gHiiHandle, STRING_TOKEN(STR_NETWORK_IPV6_DP));
                    SPrint(BusText, MAX_DRIVE_NAME, Format, LocalPort);
                }

                break;

                case MSG_UART_DP:
                { //UART device with Baud Rate
                    UINT64	BaudRate;

                    BaudRate = ((UART_DEVICE_PATH*)DevPath)->BaudRate;

                    BusText = (CHAR16 *)EfiLibAllocatePool(MAX_DRIVE_NAME * sizeof(CHAR16));
                    Format = HiiGetString(gHiiHandle, STRING_TOKEN(STR_UART_DP));
                    SPrint(BusText, MAX_DRIVE_NAME, Format, BaudRate);
                }
                break;

                case MSG_USB_CLASS_DP:
                { ////for UBS Class id specific devices.
                    UINT8	DeviceClass;

                    DeviceClass = ((USB_CLASS_DEVICE_PATH*)DevPath)->DeviceClass;
                    BusText = (CHAR16 *)EfiLibAllocatePool(MAX_DRIVE_NAME * sizeof(CHAR16));
                    switch(DeviceClass)
                    { //To show the type of device based on the class
                    	case USB_PHY_DEV_CLASS:
                    		Format = HiiGetString(gHiiHandle, STRING_TOKEN(STR_USB_CLASS_PHY_DP));
			break;

                    	case USB_MASS_DEV_CLASS:
                    		Format = HiiGetString(gHiiHandle, STRING_TOKEN(STR_USB_CLASS_MASS_DP));
			break;

                    	default:
                    		Format = HiiGetString(gHiiHandle, STRING_TOKEN(STR_USB_CLASS_DP));
	
                    }
                    SPrint(BusText, MAX_DRIVE_NAME, Format, DeviceClass);
                }
                break;

                case MSG_USB_LOGICAL_UNIT_CLASS_DP:
                { //for USB logical unit class devices with Logical Unit Numnber
                    UINT8	Lun;

#if TSE_USE_EDK_LIBRARY
                    Lun = ((DEVICE_LOGICAL_UNIT_DEVICE_PATH*)DevPath)->Lun;
#else
                    Lun = ((LOGICAL_UNIT_DEVICE_PATH*)DevPath)->Lun; 
#endif
                    BusText = (CHAR16 *)EfiLibAllocatePool(MAX_DRIVE_NAME * sizeof(CHAR16));
                    Format = HiiGetString(gHiiHandle, STRING_TOKEN(STR_USB_LOGICAL_DP));
                    SPrint(BusText, MAX_DRIVE_NAME, Format, Lun);
                }
                break;

                case MSG_USB_SATA_DP:
                { // for USB SATA devices with Port Number
                    UINT16	PortNumber;
                    PortNumber = ((AMITSE_SATA_DEVICE_PATH*)DevPath)->HBAPortNumber;
                    BusText = (CHAR16 *)EfiLibAllocatePool(MAX_DRIVE_NAME * sizeof(CHAR16));
                    Format = HiiGetString(gHiiHandle, STRING_TOKEN(STR_USB_SATA_DP));
                    SPrint(BusText, MAX_DRIVE_NAME, Format, PortNumber);
                }
                break;

                case MSG_USB_ISCSI_DP:
                { // for USB iSCSI devices with Logical Unit Number
                    UINT64	Lun;
                    Lun = ((AMITSE_ISCSI_DEVICE_PATH*)DevPath)->Lun;
                    BusText = (CHAR16 *)EfiLibAllocatePool(MAX_DRIVE_NAME * sizeof(CHAR16));
                    Format = HiiGetString(gHiiHandle, STRING_TOKEN(STR_USB_ISCSI_DP));
                    SPrint(BusText, MAX_DRIVE_NAME, Format, Lun);
                }
                break;
            }
        }

        if(MEDIA_DEVICE_PATH == DevPath->Type)
        {
            switch(DevPath->SubType)
            {
		case MEDIA_HARDDRIVE_DP:
			DevText = HiiGetString(gHiiHandle, STRING_TOKEN(STR_HDD));
		break;

		case MEDIA_CDROM_DP:
			DevText = HiiGetString(gHiiHandle, STRING_TOKEN(STR_CDROM));
		break;

		case MEDIA_VENDOR_DP:
			DevText = HiiGetString(gHiiHandle, STRING_TOKEN(STR_VENDOR));
		break;

		case MEDIA_FILEPATH_DP:
			DevText = HiiGetString(gHiiHandle, STRING_TOKEN(STR_FILEPATH));
		break;

		case MEDIA_PROTOCOL_DP:
			DevText = HiiGetString(gHiiHandle, STRING_TOKEN(STR_PROTOCOL));
		break;

		case MEDIA_FV_FILEPATH_DP:
			DevText = HiiGetString(gHiiHandle, STRING_TOKEN(STR_FV_FILEPATH));
		break;

            }
	}

        DevPath = NextDevicePathNode(DevPath);
    }

    if(BusText && DevText)
    {
        String = (CHAR16 *)EfiLibAllocatePool((MAX_DRIVE_NAME+10) * sizeof(CHAR16));
        SPrint(String, MAX_DRIVE_NAME, L"%s %s", BusText, DevText);

        MemFreePointer((VOID **) &BusText);
        MemFreePointer((VOID **) &DevText);
    }

    MemFreePointer((VOID **) &Format);

    return String;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	UpdateBootVariables
//
// Description:	Update the BootOrder,BBSOrder Cache From the NVRAM.
//
// Input:	VOID
//
// Output:	VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID UpdateBootVariables ()
{
    VarUpdateVariable(VARIABLE_ID_BOOT_ORDER);
    VarUpdateVariable(VARIABLE_ID_BBS_ORDER);
}

//EIP70421 starts
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	UpdateDriverVariables
//
// Description:	Update the DriverOrder Cache From the NVRAM.
//
// Input:	VOID
//
// Output:	VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID UpdateDriverVariables()
{
	VarUpdateVariable (VARIABLE_ID_DRIVER_ORDER);
}
//EIP70421 ends

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**     5555 Oakbrook Pkwy, Building 200,Norcross, Georgia 30093     **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
