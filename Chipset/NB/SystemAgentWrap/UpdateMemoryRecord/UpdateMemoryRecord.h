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
// $Header: /Alaska/BIN/Chipset/Intel/NorthBridge/Haswell/Intel SystemAgent NB Chipset/SystemAgentWrap/UpdateMemoryRecord/UpdateMemoryRecord.h 1     2/08/12 4:37a Yurenlai $
//
// $Revision: 1 $
//
// $Date: 2/08/12 4:37a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Chipset/Intel/NorthBridge/Haswell/Intel SystemAgent NB Chipset/SystemAgentWrap/UpdateMemoryRecord/UpdateMemoryRecord.h $
// 
// 1     2/08/12 4:37a Yurenlai
// Intel Haswell/NB eChipset initially releases.
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:  UpdateMemoryRecord.h
//
// Description:
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __UPDATE_MEMORY_RECORD_H__
#define __UPDATE_MEMORY_RECORD_H__

#include <Tiano.h>
#include <Protocol\SMBios.h>
#include <Protocol\SmbiosGetFlashDataProtocol.h>
#include "EfiDriverLib.h"
#include "Guid\DataHubRecords\DataHubSubClassMemory.h"
#include "SmbiosUpdateDataProtocol.h"

#if (EFI_SPECIFICATION_VERSION >= 0x0002000A)
#include "UefiIfrLibrary.h"
#include EFI_PROTOCOL_DEPENDENCY (HiiDatabase)
#include EFI_PROTOCOL_DEPENDENCY (HiiString)
#else
#include "Library\Dxe\EfiIfrSupportLib\IfrLibrary.h"
#include EFI_PROTOCOL_DEPENDENCY (Hii)
#endif

#define SMBIOS_NOT_FOUND        0xFFFF
#define SMBIOS_UNKNOW           0xFFFF
#define SMBIOS_NOT_PROVIDE      0xFFFE
#define MAX_HANDLES             0x10
#define SMBIOS_FOR_ALL          0xFF

VOID
SMBIOS_FixHandleLink(
    IN SMBIOS_TABLE_ENTRY_POINT    *SmbiosBuffer
);

EFI_STATUS
ExtractDataFromHiiHandle (
    IN      EFI_HII_HANDLE    HiiHandle,
    IN OUT  UINT16            *ImageLength,
    OUT     UINT8             *DefaultImage,
    OUT     EFI_GUID          *Guid
);


UINT8
TransferHiiStringToSmbios (
    IN    UINT8         *Structure,
    IN    STRING_REF    Token
);

UINT16
SMBIOS_GetStructureTotalSize(
    IN UINT8 *BufferStart
);

UINTN 
SMBIOS_DeleteStructureByType (
    SMBIOS_TABLE_ENTRY_POINT *SmbiosBuffer,
    UINT8 Type, 
    UINT8 Index
);

#endif
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