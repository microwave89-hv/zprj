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
// $Header: /Alaska/BIN/Core/Include/PPI/S3Resume2.h 1     5/27/11 5:50p Felixp $
//
// $Revision: 1 $
//
// $Date: 5/27/11 5:50p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/PPI/S3Resume2.h $
// 
// 1     5/27/11 5:50p Felixp
// 
// 6     1/13/10 2:13p Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:  S3Resume2.h
//
// Description:	S3Resume2 PPI definition
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __S3_RESUME2_PPI__H__
#define __S3_RESUME2_PPI__H__
#ifdef __cplusplus
extern "C" {
#endif
#include <PEI.h>

#define EFI_PEI_S3_RESUME2_PPI_GUID \
  { 0x6D582DBC, 0xDB85, 0x4514, 0x8F, 0xCC, 0x5A, 0xDF, 0x62, 0x27, 0xB1, 0x47 }

GUID_VARIABLE_DECLARATION(gEfiPeiS3Resume2PpiGuid,EFI_PEI_S3_RESUME2_PPI_GUID);

typedef struct _EFI_PEI_S3_RESUME2_PPI  EFI_PEI_S3_RESUME2_PPI;

typedef EFI_STATUS (EFIAPI *EFI_PEI_S3_RESUME_PPI_RESTORE_CONFIG2)(
    IN EFI_PEI_S3_RESUME2_PPI  *This
);

struct _EFI_PEI_S3_RESUME2_PPI {
    EFI_PEI_S3_RESUME_PPI_RESTORE_CONFIG2  S3RestoreConfig2;
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
