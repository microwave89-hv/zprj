//****************************************************************************
//****************************************************************************
//**                                                                        **
//**             (C)Copyright 1985-2009, American Megatrends, Inc.          **
//**                                                                        **
//**                          All Rights Reserved.                          **
//**                                                                        **
//**                 5555 Oakbrook Pkwy, Norcross, GA 30093                 **
//**                                                                        **
//**                          Phone (770)-246-8600                          **
//**                                                                        **
//****************************************************************************
//****************************************************************************

//****************************************************************************
// $Header: /Alaska/SOURCE/Modules/USB/ALASKA/Int13/UsbBbs.c 1     7/03/13 5:25a Ryanchou $
//
// $Revision: 1 $
//
// $Date: 7/03/13 5:25a $
//
//****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/USB/ALASKA/Int13/UsbBbs.c $
// 
// 1     7/03/13 5:25a Ryanchou
// [TAG]  		EIP123988
// [Category]  	Improvement
// [Description]  	Move the code creating BBS table to end of POST.
// [Files]  		UsbBbs.c, UsbInt13.c, UsbInt13.cif, UsbInt13.h,
// UsbInt13.mak, UsbInt13.sdl, efiusbmass.c, uhcd.c, uhcd.h,
// AmiUsbController.h
// 
//****************************************************************************

//<AMI_FHDR_START>
//****************************************************************************
//
//  Name:           UsbBbs.c
//  Description:    
//
//****************************************************************************
//<AMI_FHDR_END>

#include <AmiDxeLib.h>
#include <Protocol\AmiUsbController.h>

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:  CollectUsbBbsDevices
//
// Description: Create BBS table for each USB mass storage device.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
CollectUsbBbsDevices (
    VOID
)
{
    EFI_STATUS  Status;
    EFI_USB_PROTOCOL        *AmiUsb;

    Status = pBS->LocateProtocol(&gEfiUsbProtocolGuid, NULL, &AmiUsb);
    if (EFI_ERROR(Status)) {
        return;
    }

    AmiUsb->InstallUsbLegacyBootDevices();
}

//****************************************************************************
//****************************************************************************
//**                                                                        **
//**             (C)Copyright 1985-2009, American Megatrends, Inc.          **
//**                                                                        **
//**                          All Rights Reserved.                          **
//**                                                                        **
//**                 5555 Oakbrook Pkwy, Norcross, GA 30093                 **
//**                                                                        **
//**                          Phone (770)-246-8600                          **
//**                                                                        **
//****************************************************************************
//****************************************************************************
