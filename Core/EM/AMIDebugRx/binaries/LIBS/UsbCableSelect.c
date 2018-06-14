//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
//**                                                             **//
//**         (C)Copyright 2009, American Megatrends, Inc.        **//
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
// $Header: /Alaska/BIN/Modules/AMIDebugRx/binaries/LIBS/UsbCableSelect.c 3     9/29/11 3:21p Madhans $
//
// $Revision: 3 $
//
// $Date: 9/29/11 3:21p $
//*****************************************************************
//*****************************************************************
//
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/AMIDebugRx/binaries/LIBS/UsbCableSelect.c $
// 
// 3     9/29/11 3:21p Madhans
// File revision # 2 Comments corrected.
// 
// 2     7/17/09 7:15p Madhans
// DebugRx 1.30.0022
// 
// 2     7/13/09 2:43p Sudhirv
// Updated with Coding Standards
// 
// 1     7/07/09 4:46p Sudhirv
// Restructure Binaries Created
// 
// 1     5/01/09 7:48p Madhans
// AMIDebug Rx Module. Intial Checkin.
// 
// 1     4/29/09 7:51a Sudhirv
// AMI Debug Rx module created
// 
// 8     3/27/09 8:24a Sudhirv
// Updated Coding Standards.
// 
// 7     8/29/07 12:45p Madhans
// Common code for 4.x and 3.x
// 
// 6     6/13/07 3:16p Madhans
// Copyright Year updated.
// 
// 5     1/22/07 11:36a Madhans
// Modification made for Binary Release 1.04.0003.
// 
// 3     1/05/07 1:05p Ashrafj
// Latest version 1.04.0001 Beta
// Known issues from previous 1.04.000 Beta release has been fixed.
// 
// 2     9/21/06 6:40p Ashrafj
// Remove the specific changes made previously to support for the USB File transfer
// Cable, which was provided by means of SDL token support
// and instead provided the USB Device Request command interface to the
// DbgrUsbCableSelectLib, so any new cables support can be added through
// this library.
// 
// 1     9/13/06 6:54p Ashrafj
// New Usb Cable support (Multi-LinQ Usb 2.0 cable) added. The usage of
// this cable is based on new SDL token named USE_ALI_5632_CTRL_USB2_CABLE is
// added, along with new library named DbgrUsbCableSelectLib. This library
// is common for both PEI and DXE Transport modules to select between 2
// USB cables.
//
//*****************************************************************

//<AMI_FHDR_START>
//--------------------------------------------------------------------
//
// Name:	UsbCableSelect.c
//
// Description:	DbgrUsbCableSelectLib library source file.
//				
//--------------------------------------------------------------------
//<AMI_FHDR_END>

//--------------------------------------------------------------------
#include <Efi.h>
#ifdef ALASKA_SUPPORT
#include "token.h"
#else
#include "tokens.h"
#endif
//--------------------------------------------------------------------
//
// The following functions are from the USB Transport module, to INIT USB
// Cable Device.
//
EFI_STATUS	InitUsb2DebugCableDevice();
EFI_STATUS	SetFeature(UINT16 FeatureSelector);
EFI_STATUS	SetAddress(UINT8 Addr);
EFI_STATUS	SetConfiguration(UINT16 ConfigValue);
void		UpdateBulkTransferEndpoints(UINT8	InEndpoint, UINT8	OutEndpoint);
//--------------------------------------------------------------------

//<AMI_PHDR_START>
//--------------------------------------------------------------------
// Procedure:	Init_ALi5632Ctrl_Usb2Cable
//
// Description:	Sets ALi 5632 Controller USB Cable device address
//				and issues configuration commands.
//				This is left as an example for porting engineer.
//
// Input:		UINT8	Addr
//
// Output:		EFI_STATUS
//
//--------------------------------------------------------------------
//<AMI_PHDR_END>

#if	USE_ALI_5632_CTRL_USB2_CABLE

EFI_STATUS	Init_ALi5632Ctrl_Usb2Cable(UINT8	Addr)
{
	EFI_STATUS	Status = EFI_NOT_FOUND;
	Status = SetAddress(Addr);
	if(Status == EFI_SUCCESS){

		Status = SetConfiguration(1);

		//update the globals for bulk transfer endpoints
		UpdateBulkTransferEndpoints(1,2);
	}
	
	return Status;
}

#endif

//<AMI_PHDR_START>
//--------------------------------------------------------------------
// Procedure:	InitUsbCableDevice()
//
// Description:	To select between Usb 2.0 Debug Cable device or any
//				other OEM specific USB 2.0 USB cable like ALi 5632 Usb2.0 Cable.
//
// Input:		None
//
// Output:		EFI_STATUS
//
//--------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS InitUsbCableDevice()
{
#if	USE_ALI_5632_CTRL_USB2_CABLE
	//
	//This is just left as an example to porting Engineer
	//
	return Init_ALi5632Ctrl_Usb2Cable(MULTI_LINQ_USB2_DEVICE_ADDRESS);
#else
	return InitUsb2DebugCableDevice();
#endif
}
//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
//**                                                             **//
//**         (C)Copyright 2009, American Megatrends, Inc.        **//
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
