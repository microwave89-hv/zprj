//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
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
// $Header: /Alaska/BIN/Core/Include/PPI/TemporaryRamSupport.h 3     3/25/11 12:50p Felixp $
//
// $Revision: 3 $
//
// $Date: 3/25/11 12:50p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/PPI/TemporaryRamSupport.h $
// 
// 3     3/25/11 12:50p Felixp
// Identifiers are renamed based on PI errata (EFI_PEI_ prefix is added.)
// 
// 2     3/09/11 5:42p Artems
// Modified to comply with AMI coding standard
// 
//**********************************************************************

//<AMI_FHDR_START>
//---------------------------------------------------------------------------
//
// Name:	TemporaryRamSupport.h
//
// Description: In SEC-to-PEI Handoff phase, this copies memory content 
//              from temporary RAM to permanent RAM.
//
//---------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef __TEMPORARY_RAM_SUPPORT_H__
#define __TEMPORARY_RAM_SUPPORT_H__

#ifdef __cplusplus
extern "C" {
#endif

// {DBE23AA9-A345-4B97-85B6-B226F1617389}
#define EFI_PEI_TEMPORARY_RAM_SUPPORT_PPI_GUID \
    { 0xdbe23aa9, 0xa345, 0x4b97, 0x85, 0xb6, 0xb2, 0x26, 0xf1, 0x61, 0x73, 0x89 }

GUID_VARIABLE_DECLARATION(gEfiTemporaryRamSupportPpiGuid, EFI_PEI_TEMPORARY_RAM_SUPPORT_PPI_GUID);

typedef EFI_STATUS (EFIAPI *TEMPORARY_RAM_MIGRATION)
(
    IN CONST EFI_PEI_SERVICES       **PeiServices,
    IN EFI_PHYSICAL_ADDRESS         TemporaryMemoryBase,
    IN EFI_PHYSICAL_ADDRESS         PermanentMemoryBase,
    IN UINTN                        CopySize
);

typedef struct  
{
    TEMPORARY_RAM_MIGRATION TemporaryRamMigration;
} EFI_PEI_TEMPORARY_RAM_SUPPORT_PPI;


/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
