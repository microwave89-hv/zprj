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
// $Header: /Alaska/SOURCE/Modules/TCG2/Libraries/TisLib/INTTcgAcpi.h 1     4/21/14 2:15p Fredericko $
//
// $Revision: 1 $
//
// $Date: 4/21/14 2:15p $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/TCG2/Libraries/TisLib/INTTcgAcpi.h $
// 
// 1     4/21/14 2:15p Fredericko
// 
// 1     10/08/13 11:58a Fredericko
// Initial Check-In for Tpm-Next module
// 
// 1     7/10/13 5:50p Fredericko
// [TAG]  		EIP120969
// [Category]  	New Feature
// [Description]  	TCG (TPM20)
// [Files]  		TisLib.cif
// TisLib.mak
// TcgTpm12.h
// TpmLib.h
// TcgCommon.h
// ZTEICTcmOrdinals.h
// TpmLib.c
// TcgCommon.c
// TisLib.sdl
// sha1.h
// INTTcgAcpi.h
// TcgPc.h
// TcmPc.h
// TcgEfiTpm.h
// TcgEFI12.h
// 
// 2     5/19/10 5:24p Fredericko
// Included File Header
// Included File Revision History 
// Code Beautification
// EIP 37653
//
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:  INTTcgAcpi.h
//
// Description: Acpi definitions for TCG module
//
//<AMI_FHDR_END>
//*************************************************************************
#ifndef _TCG_ACPI_3_0_H_
#define _TCG_ACPI_3_0_H_


#define EFI_ACPI_30_TABLE_GUID EFI_ACPI_20_TABLE_GUID

extern EFI_GUID gEfiAcpiTableGuid;
extern EFI_GUID gEfiAcpi20TableGuid;
extern EFI_GUID gEfiAcpi30TableGuid;


#pragma pack(1)

typedef struct
{
    UINT32 Signature;
    UINT32 Length;
    UINT8  Revision;
    UINT8  Checksum;
    UINT8  OemId[6];
    UINT64 OemTableId;
    UINT32 OemRevision;
    UINT32 CreatorId;
    UINT32 CreatorRevision;
} EFI_ACPI_DESCRIPTION_HEADER;


//
// "TCPA" Trusted Computing Platform Alliance Capabilities Table
//
#define\
    EFI_ACPI_3_0_TRUSTED_COMPUTING_PLATFORM_ALLIANCE_CAPABILITIES_TABLE_SIGNATURE \
    0x41504354


#pragma pack()

#endif
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
