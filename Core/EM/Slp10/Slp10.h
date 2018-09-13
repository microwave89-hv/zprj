//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

//*****************************************************************************
// $Header: /Alaska/SOURCE/Modules/Slp10/Slp10.h 1     6/18/09 5:31p Vyacheslava $
//
// $Revision: 1 $
//
// $Date: 6/18/09 5:31p $
//*****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/Slp10/Slp10.h $
// 
// 1     6/18/09 5:31p Vyacheslava
// Initial Creation
// 
//
//*****************************************************************************
//<AMI_FHDR_START>
//
// Name: Slp10.h
//
// Description: Internal header file of the Slp10 eModule.
//
//<AMI_FHDR_END>
//*****************************************************************************

#ifndef _AMI_SLP10_MODULE_H
#define _AMI_SLP10_MODULE_H

#include <EFI.h>
#include <Token.h>

#ifdef __cplusplus
extern "C" {
#endif

// {2EBE0275-6458-4af9-91ED-D3F4EDB100AA}
#define BIOS_FEATURES_SECTION_GUID \
    {0x2ebe0275, 0x6458, 0x4af9, 0x91, 0xed, 0xd3, 0xf4, 0xed, 0xb1, 0x0, 0xaa}

#define OEM_DATA_LOCATION_BIT   0x80

#pragma pack(1)

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name: BIOS_OEM_DATA
//
// Description:	This structure comes out of the AMI Utility Specification.
//
// Fields:   
//  Name        Type        Description
// ---------------------------------------------------------------------------
//  Guid        EFI_GUID    Firmware Section GUID 
//	Identifier  CHAR8       Identifier String "$ODB$"
//  Flag        UINT16      Data Flag
//  Size        UINT16      Data Size
//  Data        UINT8       Data Buffer (SLP String)
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

typedef struct _BIOS_OEM_DATA {
    EFI_GUID Guid;
    CHAR8    Identifier[6];
    UINT16   Flag;
    UINT16   Size;
    UINT8    Data[OEM_DATA_SPACE_SIZE];
} BIOS_OEM_DATA;

#pragma pack()

#ifdef __cplusplus
}
#endif

#endif

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
