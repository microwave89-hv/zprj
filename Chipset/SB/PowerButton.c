//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/SMM/PowerButton/PowerButton.c 9     9/20/11 3:12p Markw $
//
// $Revision: 9 $
//
// $Date: 9/20/11 3:12p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SMM/PowerButton/PowerButton.c $
// 
// 9     9/20/11 3:12p Markw
// [TAG]  		EIP67890
// [Category]  	Spec Update
// [Severity]  	Normal
// [Description]  	Support power button handler in PI 1.1
// 
// [Files]  		PowerButton.c, PowerButton.mak, PowerButton. dxs
//
// 8     7/08/09 7:56p Markw
// Update headers.
//
// 7     1/07/08 4:26p Robert
// Updated for coding standard
//
// 6     5/30/07 5:29p Markw
// Use library function to shutdown.
//
// 5     3/28/07 1:27p Markw
// Update headers.
//
// 4     2/26/07 11:44a Yakovlevs
// Added arming PwrButton Smi when registering SMI handler.
// In event handler added check for Sleep SMI enable and disabling it.
//
// 3     11/11/05 11:46a Markw
// Renamed IntallSmmHandler to InitSmmHandler because of build errors
// because another driver used InstallSmmHandler.
//
// 2     11/08/05 6:05p Markw
// Using InstallSmiHandler library function.
//
// 1     1/28/05 4:33p Sivagarn
// Power Button SMM Component - Initial check in
//
//
//**********************************************************************

//<AMI_FHDR_START>
//---------------------------------------------------------------------------
//
// Name:        PowerButton.C
//
// Description: Provide functions to register and handle Powerbutton
//              functionality.  This code is generic and as long as PM
//              base address SDL token is defined properly this should
//              work fine.
//
//---------------------------------------------------------------------------
//<AMI_FHDR_END>


#include <Token.h>
#include <AmiDxeLib.h>
#include <AMICSPLIBInc.h>
#if PI_SPECIFICATION_VERSION < 0x1000A
#include <Protocol\SmmPowerButtonDispatch.h>
#else
#include <Protocol\SmmPowerButtonDispatch2.h>
#endif

EFI_GUID gThisFileGuid =
    {0xe566b097,0x4378,0x485f,0x91,0xd0,0x1c,0x09,0x7c,0x19,0x0c,0xe2};
    //E566B097-4378-485f-91D0-1C097C190CE2

#if PI_SPECIFICATION_VERSION < 0x1000A
EFI_SMM_POWER_BUTTON_DISPATCH_CONTEXT	DispatchContext = {PowerButtonEntry};
#else
EFI_SMM_POWER_BUTTON_REGISTER_CONTEXT	DispatchContext = {EfiPowerButtonExit};
EFI_SMM_BASE2_PROTOCOL					*pSmmBase2;
EFI_SMM_SYSTEM_TABLE2					*pSmst2;
#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   PowerButtonActivated
//
// Description: If the power button is pressed, then this function is called.
//
// Input:
//  IN EFI_HANDLE                               DispatchHandle
//  IN EFI_SMM_POWER_BUTTON_DISPATCH_CONTEXT    *DispatchContext
//
// Output: VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
#if PI_SPECIFICATION_VERSION < 0x1000A
VOID PowerButtonActivated(
    IN EFI_HANDLE                               DispatchHandle,
    IN EFI_SMM_POWER_BUTTON_DISPATCH_CONTEXT    *DispatchContext
    )
#else
EFI_STATUS
EFIAPI
PowerButtonActivated(
	IN EFI_HANDLE	DispatchHandle,
	IN CONST VOID	*Context OPTIONAL,
	IN OUT VOID		*CommBuffer OPTIONAL,
	IN OUT UINTN	*CommBufferSize OPTIONAL)
#endif
{
    SBLib_Shutdown();

#if PI_SPECIFICATION_VERSION >= 0x1000A
	return EFI_SUCCESS;
#endif
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   InSmmFunction
//
// Description: This function is called from SMM during SMM registration.
//
// Input:
//  IN EFI_HANDLE       ImageHandle
//  IN EFI_SYSTEM_TABLE *SystemTable
//
// Output: EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS InSmmFunction(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
#if PI_SPECIFICATION_VERSION >= 0x1000A
    EFI_SMM_POWER_BUTTON_DISPATCH2_PROTOCOL	*PowerButton;
#else
    EFI_SMM_POWER_BUTTON_DISPATCH_PROTOCOL  *PowerButton;
#endif
    EFI_HANDLE  hPowerButton;
    EFI_STATUS  Status;

#if PI_SPECIFICATION_VERSION >= 0x1000A
    Status = pSmmBase2->GetSmstLocation(pSmmBase2, &pSmst2);
    if (EFI_ERROR(Status)) return Status;

    Status = pSmst2->SmmLocateProtocol(
        &gEfiSmmPowerButtonDispatch2ProtocolGuid,
        NULL,
        &PowerButton
    );
#else
    Status = pBS->LocateProtocol(
        &gEfiSmmPowerButtonDispatchProtocolGuid,
        NULL,
        &PowerButton
    );
#endif
    if (EFI_ERROR(Status)) return Status;

    Status = PowerButton->Register(
        PowerButton,
        PowerButtonActivated,
        &DispatchContext,
        &hPowerButton
    );
    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   NotInSmmFunction
//
// Description: This function is called from outside of SMM during SMM registration.
//
// Input:
//  IN EFI_HANDLE       ImageHandle
//  IN EFI_SYSTEM_TABLE *SystemTable
//
// Output: EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS NotInSmmFunction(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
    UINT16  Value;
    //Clear All PM  Statuses
    Value = IoRead16(PM_BASE_ADDRESS);
    IoWrite16(PM_BASE_ADDRESS,Value);

    //Enable PowerButton and Global Enable
    IoWrite16(PM_BASE_ADDRESS + 0x02, BIT05 + BIT08);
    return EFI_SUCCESS;
}



//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   InitPowerButton
//
// Description: This is the entrypoint of the Power button driver.
//
// Input:
//  IN EFI_HANDLE       ImageHandle
//  IN EFI_SYSTEM_TABLE *SystemTable
//
// Output: EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS InitPowerButton(
    IN EFI_HANDLE       ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable
    )
{
#if PI_SPECIFICATION_VERSION >= 0x0001000a
    EFI_STATUS    Status;
#endif

    InitAmiLib(ImageHandle, SystemTable);

#if PI_SPECIFICATION_VERSION >= 0x0001000a
    Status = pBS->LocateProtocol(&gEfiSmmBase2ProtocolGuid, NULL, &pSmmBase2);
    if (EFI_ERROR(Status)) return Status;

    return InitSmmHandler(ImageHandle, SystemTable, InSmmFunction, NULL);
#else
    return InitSmmHandler(ImageHandle, SystemTable, InSmmFunction, NotInSmmFunction);
#endif
}

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
