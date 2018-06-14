//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
//*************************************************************************
//
// $Header: /Alaska/SOURCE/Modules/EcPs2Kbd/EcPs2Kbd.c 3     6/29/10 3:01p Stacyh $
//
// $Revision: 3 $
//
// $Date: 6/29/10 3:01p $
//
//*****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/EcPs2Kbd/EcPs2Kbd.c $
// 
// 3     6/29/10 3:01p Stacyh
// Added fix for EIP# 39388: SCT Execution test
// failed-4.6.3.5_VeB_0ABUC_004
// 
// 2     6/03/08 10:07a Stacyh
// Added code to install a device path for PS2 Mouse.
// Added code to create/update the SIO_DEV_STATUS EFI variable
// 
// 1     5/30/08 4:23p Stacyh
// 
//
//*****************************************************************************


//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:        EcPs2Kbd.C
//
// Description: This file contains code necessary to install the EC PS2 devices
//              for EFI, ACPI and DOS.
//
// Notes:       
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>
#include "token.h"
#include "EcPs2Kbd.h"

static EFI_GUID gSioDevStatusVarGuid = SIO_DEV_STATUS_VAR_GUID;

static PS2_KBD_DEVICE_PATH  mEcPs2KbdDevicePath[1][1] = {
    {
        ACPI_DEVICE_PATH,
        ACPI_DP,
        (UINT8) (sizeof (ACPI_HID_DEVICE_PATH)),
        (UINT8) ((sizeof (ACPI_HID_DEVICE_PATH)) >> 8),
        EISA_PNP_ID(0x303),
        0,
        END_DEVICE_PATH_TYPE,
        END_ENTIRE_DEVICE_PATH_SUBTYPE,
        END_DEVICE_PATH_LENGTH,
        0
    }
};
  
static PS2_KBD_DEVICE_PATH  mEcPs2MsDevicePath[1][1] = {
    {
        ACPI_DEVICE_PATH,
        ACPI_DP,
        (UINT8) (sizeof (ACPI_HID_DEVICE_PATH)),
        (UINT8) ((sizeof (ACPI_HID_DEVICE_PATH)) >> 8),
        EISA_PNP_ID(0xF03),
        0,
        END_DEVICE_PATH_TYPE,
        END_ENTIRE_DEVICE_PATH_SUBTYPE,
        END_DEVICE_PATH_LENGTH,
        0
    }
};

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ConnectDevicePath
//
// Description: This function connects the EFI device to its parent device.
//
// Input:       pPath - Pointer to an EFI device path.
//
// Output:      VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID ConnectDevicePath (
    IN EFI_DEVICE_PATH_PROTOCOL *pPath)
{
    EFI_HANDLE Handle;
    EFI_STATUS Status;

    while (TRUE)
    {
        EFI_DEVICE_PATH_PROTOCOL *pLastPath = NULL;
        EFI_DEVICE_PATH_PROTOCOL *pFirstNode = pPath;

        if (isEndNode(pPath))
        {
            if (pPath->SubType == END_ENTIRE_SUBTYPE) break;
            pPath++;
            continue;
        }

        while (TRUE) {
            EFI_DEVICE_PATH_PROTOCOL *Dp;
            UINT8 SubType;

            pPath = pFirstNode;

            // LocateDevicePath can not work with multi-instance device paths.
            // Prepare single instance device path and call LocateDevicePath.

            Dp = DPGetEndNode(pPath);
            SubType = Dp->SubType;
            Dp->SubType = END_ENTIRE_SUBTYPE;
            Status = pBS->LocateDevicePath(&gEfiDevicePathProtocolGuid, \
                                                            &pPath, &Handle);
            Dp->SubType = SubType;
            if (EFI_ERROR(Status)) break;

            if (isEndNode(pPath))
            {
                // Last time let's do it recursively.

                pBS->ConnectController(Handle, NULL, NULL, TRUE);  
                break;
            }
            if (pPath == pLastPath) break;
            pLastPath = pPath;
            if (EFI_ERROR(pBS->ConnectController(Handle, NULL, pPath, FALSE)))
                break;
        }

        while (!isEndNode(pPath))
            pPath = NEXT_NODE(pPath);
    }
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   EcPs2KbdEntry
//
// Description: This function installs the Device Path for the EC Ps2.
//
// Input:       ImageHandle Image handle
//              SystemTable Pointer to the system table
//
// Output:      EFI_STATUS      Returned from PCI read call
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS  EcPs2KbdEntry (
    IN EFI_HANDLE       ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable)
{
    EFI_STATUS Status;
    EFI_DEVICE_PATH_PROTOCOL    *KbTmpDp = NULL;
    EFI_DEVICE_PATH_PROTOCOL    *MsTmpDp = NULL;
    ACPI_HID_DEVICE_PATH        RbDp;
    PCI_DEVICE_PATH             PciDp;
    PS2KBD_DEV                  *PrivateData;
    SIO_DEV_STATUS              SioDevStatusVar;
    UINTN                       SioDevStatusVarSize = sizeof(SIO_DEV_STATUS);
    UINT32                      SioDevStatusVarAttributes = 0;
    
    InitAmiLib(ImageHandle,SystemTable);

    // Get root bridge device path
    RbDp.Header.Type = ACPI_DEVICE_PATH;
    RbDp.Header.SubType = ACPI_DP;
    SET_NODE_LENGTH(&RbDp.Header, ACPI_DEVICE_PATH_LENGTH);
    RbDp.HID = EISA_PNP_ID(0x0A03);
    RbDp.UID = 0;
    KbTmpDp = DPAddNode(KbTmpDp, &RbDp.Header);
    MsTmpDp = DPAddNode(MsTmpDp, &RbDp.Header);
    ConnectDevicePath(KbTmpDp);
    ConnectDevicePath(MsTmpDp);

    // Get PCI device path
    PciDp.Header.SubType = HW_PCI_DP;
    PciDp.Header.Type = HARDWARE_DEVICE_PATH;
    SET_NODE_LENGTH(&PciDp.Header, HW_PCI_DEVICE_PATH_LENGTH);
    PciDp.Function = SB_FUN_NUMBER;
    PciDp.Device = SB_DEV_NUMBER;
    KbTmpDp = DPAddNode(KbTmpDp, &PciDp.Header);
    MsTmpDp = DPAddNode(MsTmpDp, &PciDp.Header);
    ConnectDevicePath(KbTmpDp);
    ConnectDevicePath(MsTmpDp);


    // Install PS2 Keyboard Device Path
    Status = pBS->AllocatePool (EfiBootServicesData, sizeof (PS2KBD_DEV), \
        &PrivateData);
    ASSERT (!EFI_ERROR (Status));
    
    KbTmpDp = DPAddNode(KbTmpDp, (EFI_DEVICE_PATH_PROTOCOL *) \
                                                &mEcPs2KbdDevicePath [0][0]);
    ConnectDevicePath(KbTmpDp);
    PrivateData->DevicePath = KbTmpDp;
    PrivateData->Handle = NULL;

    Status = pBS->InstallProtocolInterface (&PrivateData->Handle, \
        &gEfiDevicePathProtocolGuid, EFI_NATIVE_INTERFACE, \
        PrivateData->DevicePath);

    if (EFI_ERROR (Status)) {
        pBS->FreePool (PrivateData);
        return EFI_DEVICE_ERROR;
    }

    // Install PS2 Mouse Device Path
    Status = pBS->AllocatePool (EfiBootServicesData, sizeof (PS2KBD_DEV), \
        &PrivateData);
    ASSERT (!EFI_ERROR (Status));
    
    MsTmpDp = DPAddNode(MsTmpDp, (EFI_DEVICE_PATH_PROTOCOL *) \
                                                 &mEcPs2MsDevicePath [0][0]);
    ConnectDevicePath(MsTmpDp);
    PrivateData->DevicePath = MsTmpDp;
    PrivateData->Handle = NULL;

    Status = pBS->InstallProtocolInterface (&PrivateData->Handle, \
        &gEfiDevicePathProtocolGuid, EFI_NATIVE_INTERFACE, \
        PrivateData->DevicePath);

    if (EFI_ERROR (Status)) {
        pBS->FreePool (PrivateData);
        return EFI_DEVICE_ERROR;
    }

    // Create/Update SIO_DEV_STATUS EFI variable
    Status = pRS->GetVariable(SIO_DEV_STATUS_VAR_NAME, &gSioDevStatusVarGuid, 
        &SioDevStatusVarAttributes, &SioDevStatusVarSize, 
        &SioDevStatusVar.DEV_STATUS);
    
    if (EFI_ERROR(Status)) {
        SioDevStatusVar.DEV_STATUS = 0;
        SioDevStatusVarAttributes = EFI_VARIABLE_BOOTSERVICE_ACCESS;
    }   

    SioDevStatusVar.Key60_64 = 1;
    SioDevStatusVar.Ps2Mouse = 1;

    Status = pRS->SetVariable(SIO_DEV_STATUS_VAR_NAME, &gSioDevStatusVarGuid, 
        SioDevStatusVarAttributes, SioDevStatusVarSize, 
        &SioDevStatusVar);

    return Status;
}

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
