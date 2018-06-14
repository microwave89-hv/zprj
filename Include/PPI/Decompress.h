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
// $Header: /Alaska/BIN/Core/Include/PPI/Decompress.h 2     3/09/11 5:41p Artems $
//
// $Revision: 2 $
//
// $Date: 3/09/11 5:41p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/PPI/Decompress.h $
// 
// 2     3/09/11 5:41p Artems
// Modified to comply with AMI coding standard
// 
//**********************************************************************

//<AMI_FHDR_START>
//---------------------------------------------------------------------------
//
// Name:	Decompress.h
//
// Description: Decompress PPI definition file
//
//---------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef __DECOMPRESS_PPI_H__
#define __DECOMPRESS_PPI_H__

#ifdef __cplusplus
extern "C" {
#endif

#define EFI_PEI_DECOMPRESS_PPI_GUID \
  { 0x1a36e4e7, 0xfab6, 0x476a, 0x8e, 0x75, 0x69, 0x5a, 0x5, 0x76, 0xfd, 0xd7 }

GUID_VARIABLE_DECLARATION(gEfiPeiDecompressPpiGuid, EFI_PEI_DECOMPRESS_PPI_GUID);

typedef struct _EFI_PEI_DECOMPRESS_PPI EFI_PEI_DECOMPRESS_PPI;

typedef EFI_STATUS
(EFIAPI *EFI_PEI_DECOMPRESS_DECOMPRESS)(
    IN  CONST EFI_PEI_DECOMPRESS_PPI   *This,
    IN  CONST EFI_COMPRESSION_SECTION  *InputSection,
    OUT VOID                           **OutputBuffer,
    OUT UINTN                          *OutputSize
);

struct _EFI_PEI_DECOMPRESS_PPI {
    EFI_PEI_DECOMPRESS_DECOMPRESS   Decompress;
};


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
