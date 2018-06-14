//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2006, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
//**********************************************************************
//
// $Header: /Alaska/SOURCE/Modules/USBRecovery/PeiGetUCtrl.h 3     7/10/08 6:34p Michaela $
//
// $Revision: 3 $
//
// $Date: 7/10/08 6:34p $
//
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/USBRecovery/PeiGetUCtrl.h $
// 
// 3     7/10/08 6:34p Michaela
// Updated to support OHCI controllers
//
// 2     9/22/06 12:25p Sivagarn
// - Included appropriate headers for flies and functions
// - Updated copyright messages
//
//*****************************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:        PeiGetUCtrl.H
//
// Description: This header file contains PPI information for the Get UHCI
//              controller PPI
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef __PEIGETUCTRL__H__
#define __PEIGETUCTRL__H__
#ifdef __cplusplus
extern "C" {
#endif

// {C12DAA49-A061-47fc-955E-EAE34513511D}
#define EFI_PEI_GET_UHCI_CTRLER_GUID \
    {0x3bc1f6de, 0x693e, 0x4547, 0xa3, 0x0, 0x21, 0x82, 0x3c, 0xa4, 0x20,\
     0xb2}


typedef struct _EFI_PEI_USB_CONTROLLER_PPI EFI_PEI_USB_CONTROLLER_PPI;

#define PEI_UHCI_CONTROLLER  0x01
#define PEI_OHCI_CONTROLLER  0x02

typedef EFI_STATUS (EFIAPI * EFI_PEI_GET_UHCI_CTRLER)(
    IN EFI_PEI_SERVICES           **PeiServices,
    IN EFI_PEI_USB_CONTROLLER_PPI *This,
    IN UINT8                      UsbControllerId,
    IN UINTN                      *ControllerType,
    IN UINTN                      *IoBaseAddress
);

struct _EFI_PEI_USB_CONTROLLER_PPI
{
    EFI_PEI_GET_UHCI_CTRLER GetUhciControllerPpi;
};

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2006, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
//**********************************************************************