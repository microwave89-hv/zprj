//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ISCT/IsctProtocolLib/IsctNvsArea/IsctNvsArea.c 1     9/02/12 11:20p Bensonlai $
//
// $Revision: 1 $
//
// $Date: 9/02/12 11:20p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ISCT/IsctProtocolLib/IsctNvsArea/IsctNvsArea.c $
// 
// 1     9/02/12 11:20p Bensonlai
// Intel Smart Connect Technology initially releases.
//
//
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:  IsctNvsArea.c
//
// Description:	Isct NVS Area description protocol implementation.
//
//<AMI_FHDR_END>
//**********************************************************************

#include "EdkIIGlueDxe.h"

#include "IsctNvsArea.h"

EFI_GUID  gIsctNvsAreaProtocolGuid = ISCT_NVS_AREA_PROTOCOL_GUID;

EFI_GUID_STRING
  (
    &gIsctNvsAreaProtocolGuid, "ISCT NVS Area Protocol",
      "Protocol describing ISCT ACPI NVS memory region used by ACPI subsystem."
  );

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
