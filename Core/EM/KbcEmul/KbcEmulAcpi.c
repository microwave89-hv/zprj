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

//*************************************************************************
// $Header: /Alaska/SOURCE/Modules/KbcEmulation/ALASKA/KBCEMUL/KbcEmulAcpi.c 2     4/10/14 2:28a Rameshr $
//
// $Revision: 2 $
//
// $Date: 4/10/14 2:28a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/KbcEmulation/ALASKA/KBCEMUL/KbcEmulAcpi.c $
// 
// 2     4/10/14 2:28a Rameshr
// [TAG]  		EIP160392
// [Category]  	Improvement
// [Description]  	Junk Character from check-in History removed. 
// [Files]  		KbcEmulAcpi.c
// 
// 1     1/09/12 1:22a Rameshr
// [TAG]  		EIP74128
// [Category]  	Improvement
// [Description]  	Disable the KbcEmulation Smis on ACPI enable and
// Disable SMI call
// [Files]  		Kbccore.c, KbcEmuulAcpi.c, KbcEmul.c, KbcEmul.cif,
// KbcEmul.h, KbcEmul.sdl
// 
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:        KbcEmulAcpi.c
//
// Description: This file contains Emulation SMI disable function on ACPI 
//              enable/Disable SMI 
//
//<AMI_FHDR_END>
//*************************************************************************

//----------------------------------------------------------------------------
// Include(s)
//----------------------------------------------------------------------------

#include <Token.h>
#include <AmiDxeLib.h>
#include <AmiCspLib.h>
#include <Protocol\SmmSwDispatch.h>
#include "KbcEmul.h"

#ifdef EMULATION_ACPI_ENABLE_DISPATCH
#include    <Chipset\SB\AcpiModeEnable.h>
EFI_GUID	gEfiAcpiEnDispatchProtocolGuid = EFI_ACPI_EN_DISPATCH_PROTOCOL_GUID;
EFI_GUID    gEfiAcpiDisDispatchProtocolGuid = EFI_ACPI_DIS_DISPATCH_PROTOCOL_GUID;
#endif

extern BOOLEAN  AcpiEmulationDisable;

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   KbcEmulationDisable
//
// Description: This routine will be called when ACPI enabled or disabled SMI happens.
//
// Input:       DispatchHandle  - Handle to the Dispatcher
//
// Output:      None
//
// Notes:       None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID KbcEmulationDisable (
	IN EFI_HANDLE   DispatchHandle
)
{
    AcpiEmulationDisable=TRUE;
    TrapEnable(FALSE);
    return;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   RegisterAcpiEnableCallBack
//
// Description: This routine will be called by KbcEmulation Init 
//              to register the callback function on Acpi Enable/Disable SMI.
//
// Input:       None 
//
// Output:      None
//
// Notes:       None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
RegisterAcpiEnableCallBack(
)
{
#ifdef EMULATION_ACPI_ENABLE_DISPATCH
	EFI_STATUS          Status;
	EFI_HANDLE	        EnableHandle;
	EFI_HANDLE	        DisableHandle;
	EFI_ACPI_DISPATCH_PROTOCOL	*AcpiEnDispatch;
	EFI_ACPI_DISPATCH_PROTOCOL	*AcpiDisDispatch;

	Status = pBS->LocateProtocol(&gEfiAcpiEnDispatchProtocolGuid, NULL, &AcpiEnDispatch);
	if (EFI_ERROR(Status)) { 
        return Status;
    }

	Status = AcpiEnDispatch->Register(AcpiEnDispatch, KbcEmulationDisable, &EnableHandle);
	ASSERT_EFI_ERROR(Status);

	Status = pBS->LocateProtocol(&gEfiAcpiDisDispatchProtocolGuid, NULL, &AcpiDisDispatch);
	if (EFI_ERROR(Status)) { 
        return Status;
    }

	Status = AcpiDisDispatch->Register(AcpiDisDispatch, KbcEmulationDisable, &DisableHandle);
	ASSERT_EFI_ERROR(Status);

	return Status;
#else
    return EFI_SUCCESS;
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
