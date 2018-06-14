//**********************************************************************//
//**********************************************************************//
//**                                                                  **//
//**        (C)Copyright 1985-2003, American Megatrends, Inc.         **//
//**                                                                  **//
//**                       All Rights Reserved.                       **//
//**                                                                  **//
//**             6145-F Northbelt Pkwy, Norcross, GA 30071            **//
//**                                                                  **//
//**                       Phone: (770)-246-8600                      **//
//**                                                                  **//
//**********************************************************************//
//**********************************************************************//

//**********************************************************************
// $Header: /Alaska/BIN/Core/Include/PPI/S3Resume.h 3     3/13/06 1:16a Felixp $
//
// $Revision: 3 $
//
// $Date: 3/13/06 1:16a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/PPI/S3Resume.h $
// 
// 3     3/13/06 1:16a Felixp
// 
// 2     3/25/05 4:02p Markw
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	S3Resume.h
//
// Description:
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __S3_RESUME_PPI__H__
#define __S3_RESUME_PPI__H__
#ifdef __cplusplus
extern "C" {
#endif
#include <PEI.h>

#define EFI_PEI_S3_RESUME_PPI_GUID \
	{0x4426CCB2,0xE684,0x4a8a,0xAE,0x40,0x20,0xD4,0xB0,0x25,0xB7,0x10}

GUID_VARIABLE_DECLARATION(gPeiS3ResumePpiGuid,EFI_PEI_S3_RESUME_PPI_GUID);

typedef struct _EFI_PEI_S3_RESUME_PPI EFI_PEI_S3_RESUME_PPI;

typedef EFI_STATUS (EFIAPI *EFI_PEI_S3_RESUME_PPI_RESTORE_CONFIG) (
	IN EFI_PEI_SERVICES **PeiServices
);

struct _EFI_PEI_S3_RESUME_PPI {
	EFI_PEI_S3_RESUME_PPI_RESTORE_CONFIG	S3RestoreConfig;
};

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif

//**********************************************************************//
//**********************************************************************//
//**                                                                  **//
//**        (C)Copyright 1985-2003, American Megatrends, Inc.         **//
//**                                                                  **//
//**                       All Rights Reserved.                       **//
//**                                                                  **//
//**             6145-F Northbelt Pkwy, Norcross, GA 30071            **//
//**                                                                  **//
//**                       Phone: (770)-246-8600                      **//
//**                                                                  **//
//**********************************************************************//
//**********************************************************************//
