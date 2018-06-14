//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
//**********************************************************************
// $Archive: /Alaska/SOURCE/Modules/PTT/FastBootOption/FastBootOptionBds.c $
//
// $Author: Bibbyyeh $
//
// $Revision: 1 $
//
// $Date: 10/30/12 4:22a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/PTT/FastBootOption/FastBootOptionBds.c $
// 
// 1     10/30/12 4:22a Bibbyyeh
// [TAG]           EIP105177
// [Category]      New Feature
// [Description]   Report pseudo boot option for Windows 'Boot To Device'
// support
// [Files]         FastBootOption.cif FastBootOption.sdl
// FastBootOption.mak FastBootOption.h FastBootOption.c
// FastBootOptionBds.c FastBootOption.dxs
// 
// 
//*****************************************************************//

//<AMI_FHDR_START>
//----------------------------------------------------------------------
//
// Name: FastBootOptionBds.c
//
// Description:
//
//----------------------------------------------------------------------
//<AMI_FHDR_END>

//----------------------------------------------------------------------
// Include Files
//----------------------------------------------------------------------
#include <efi.h>
#include <amidxelib.h>
#include <protocol\blockio.h>
#include <protocol\devicepath.h>
#include <BootOptions.h>
#include "FastBootOption.h"
//---------------------------------------------------------------------------
// Global Variable declarations
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
// External functions
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
// Function Definitions
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
// Type definitions
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
// Constant and Variables declarations
//---------------------------------------------------------------------------
 BOOLEAN TempDeviceFound=FALSE;
 UINT16 BootDeviceType=0;

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetUefiDeviceType
//
// Description:	Function returns device type 
//
// Input:       EFI_DEVICE_PATH_PROTOCOL *Dp -
//
// Output:      UINT32 - device type
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT32 GetUefiDeviceType(
    IN EFI_DEVICE_PATH_PROTOCOL *Dp
)
{
    EFI_DEVICE_PATH_PROTOCOL *DpPtr = Dp;
    BOOLEAN IsUSB = FALSE;

    if( Dp == NULL )
	return 0xffff;

    for( ; !(isEndNode(DpPtr)); DpPtr = NEXT_NODE(DpPtr))
    {
        if(DpPtr->Type == MESSAGING_DEVICE_PATH)
        {
            if(DpPtr->SubType == MSG_USB_DP)
                IsUSB = TRUE;

            if(DpPtr->SubType == MSG_MAC_ADDR_DP)
                return TempUefiNetDevice;

            continue;
        }

        if(DpPtr->Type == MEDIA_DEVICE_PATH)
        {
            if(!IsUSB && DpPtr->SubType == MEDIA_HARDDRIVE_DP)
                return TempUefiHddDevice;
	    else
            if(!IsUSB && DpPtr->SubType == MEDIA_CDROM_DP)
                return TempUefiOddDevice;
	    else
            if(IsUSB && DpPtr->SubType == MEDIA_HARDDRIVE_DP)
	    {
		return TempUefiRemDevice;
	    }
            else
            if(IsUSB && DpPtr->SubType == MEDIA_CDROM_DP)
                return TempUefiOddDevice;
        }
    }
    return 0xffff;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SetBootNextBootOption
//
// Description:	Compare Boot device type and re-setting variable "BootNext"
//		
// Input: 
//	NONE
// Output: 
//	NONE
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
SetBootNextBootOption()
{
    EFI_STATUS Status;
    DLINK *Link;
    BOOT_OPTION *Option;
    UINT16 BootNext;
    UINTN Size;

    Size = sizeof(BootNext);

    if( TempDeviceFound )
    {
    	FOR_EACH_BOOT_OPTION(BootOptionList,Link,Option){

		if( GetUefiDeviceType(Option->FilePathList) == BootDeviceType )
		{
			BootNext = Option->BootOptionNumber;
			Status = pRS->SetVariable(L"BootNext", &EfiVariableGuid, BOOT_VARIABLE_ATTRIBUTES, Size, &BootNext);				
			TRACE((-1,"FastBootOptionBds.c:: SetVariable Status=%r BootNext=%d\n", Status, BootNext));
		}

	}
    }
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CheckBootNextTempBootOption
//
// Description:	Check BootNext device and find uefi device, adjust BootNext
//		number.
// Input: 
//
// Output: 
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
CheckBootNextTempBootOption()
{
    EFI_STATUS Status;
    DLINK *Link;
    BOOT_OPTION *Option;
    UINT16 BootNext;
    UINTN Size;

    Size = sizeof(BootNext);
    Status = pRS->GetVariable(L"BootNext", &EfiVariableGuid, NULL, &Size, &BootNext);

    TRACE((-1,"FastBootOptionBds.c:: Status=%r BootNext=%d\n", Status, BootNext));

    if( !EFI_ERROR( Status ) )
    {
    	FOR_EACH_BOOT_OPTION(BootOptionList,Link,Option){
		BBS_BBS_DEVICE_PATH *BBSdp;

		if( BootNext == Option->BootOptionNumber )
		{
			BBSdp=(BBS_BBS_DEVICE_PATH*)Option->FilePathList;
			if( BBSdp->Header.Type == BBS_DEVICE_PATH )
			{
				BootDeviceType = BBSdp->DeviceType;
				switch( BootDeviceType )
				{
					case TempUefiHddDevice:
					case TempUefiOddDevice:
					case TempUefiRemDevice:
					case TempUefiNetDevice:
						TempDeviceFound=TRUE;
						break;
				}
			}
		}
    	}
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   RemoveFastBootOption
//
// Description:	Remove all TempUefiDevice Bootoption.
//
// Input: 
//
// Output: 
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
RemoveFastBootOption()
{

    DLINK *Link;
    BOOT_OPTION *Option;

    CheckBootNextTempBootOption();

    FOR_EACH_BOOT_OPTION(BootOptionList,Link,Option){
	BBS_BBS_DEVICE_PATH *BBSdp;
	BBSdp=(BBS_BBS_DEVICE_PATH*)Option->FilePathList;
	
	if( BBSdp->Header.Type == BBS_DEVICE_PATH )
	{
		switch( BBSdp->DeviceType )
		{
			case TempUefiHddDevice:
			case TempUefiOddDevice:
			case TempUefiRemDevice:
			case TempUefiNetDevice:
				Option->FwBootOption = TRUE;
				break;
		}
	}

    }
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
