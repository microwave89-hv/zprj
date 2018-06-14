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
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/Platform/AcpiPlatformCspLib.c 1     2/09/12 12:30a Yurenlai $
//
// $Revision: 1 $
//
// $Date: 2/09/12 12:30a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/Platform/AcpiPlatformCspLib.c $
// 
// 1     2/09/12 12:30a Yurenlai
// Initial check in.
// 
//*************************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:        AcpiPlatformCspLib.c
//
// Description: This file will be build in CSP LIB
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

//----------------------------------------------------------------------------
// Include(s)
//----------------------------------------------------------------------------

#include <Token.h>
#include <AmiDxeLib.h>
#include <AmiCspLib.h>

// Produced Protocols
#if FAST_BOOT_SUPPORT
#include <Protocol/FastBootProtocol.h>
#endif

// Consumed Protocols

//----------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//----------------------------------------------------------------------------
// Constant Definition(s)


// Macro Definition(s)

#define EXIT_PM_AUTH_PROTOCOL_GUID \
  { \
    0xd088a413, 0xa70, 0x4217, 0xba, 0x55, 0x9a, 0x3c, 0xb6, 0x5c, 0x41, 0xb3 \
  }
// Type Definition(s)

// Function Prototype(s)

//----------------------------------------------------------------------------
// Variable and External Declaration(s)
//----------------------------------------------------------------------------
// Variable Declaration(s)


// GUID Definition(s)
EFI_GUID gExitPmAuthProtocolGuid = EXIT_PM_AUTH_PROTOCOL_GUID;

//----------------------------------------------------------------------------
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	AcpiPlatformSignalProtocolEvent
//
// Description:	Internal function that installs/uninstall protocol
//				with a specified GUID and NULL interface.
//              Such protocols can be used as event signaling mechanism.
//
// Input:		ProtocolGuid Pointer to the protocol GUID
//
// Output:		None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID AcpiPlatformSignalProtocolEvent(IN EFI_GUID *ProtocolGuid){
    EFI_HANDLE  Handle = NULL;
    pBS->InstallProtocolInterface (
        &Handle, ProtocolGuid, EFI_NATIVE_INTERFACE, NULL
    );
    pBS->UninstallProtocolInterface (
        Handle, ProtocolGuid, NULL
    );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SignalExitPmAuthProtocolEvent
//
// Description: The elink will signal gExitPmAuthProtocolGuid Event.
//
// Parameters:  VOID
//              
//
// Returns:     None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID SignalExitPmAuthProtocolEvent(VOID){
#if FAST_BOOT_SUPPORT
	EFI_STATUS Status;
	AMI_FAST_BOOT_PROTOCOL *FastBootProtocol = NULL;

    Status = pBS->LocateProtocol(&AmiFastBootProtocolGuid, NULL, &FastBootProtocol);

	if (EFI_ERROR(Status)) {
      // Signaling gExitPmAuthProtocolGuid Event before AmiFastBootProtocolGuid is 
      // installed to avoid this event signaled twice.
      AcpiPlatformSignalProtocolEvent(&gExitPmAuthProtocolGuid);
    }
#else
    // Signaling gExitPmAuthProtocolGuid Event
    AcpiPlatformSignalProtocolEvent(&gExitPmAuthProtocolGuid);
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
