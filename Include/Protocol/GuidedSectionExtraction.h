//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2005, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
//**********************************************************************
// $Header: /Alaska/BIN/Core/Include/Protocol/GuidedSectionExtraction.h 2     3/13/06 1:40a Felixp $
//
// $Revision: 2 $
//
// $Date: 3/13/06 1:40a $
//*****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/Protocol/GuidedSectionExtraction.h $
// 
// 2     3/13/06 1:40a Felixp
// 
// 1     1/28/05 12:44p Felixp
// 
// 2     1/18/05 3:22p Felixp
// PrintDebugMessage renamed to Trace
// 
// 1     12/23/04 9:41a Felixp
// 
// 2     12/31/03 2:53p Markw
// Added S-Header.
// 
// 1     12/24/03 1:59p Markw
// 
// 
//*****************************************************************************
//<AMI_FHDR_START>
//
// Name:	GuidedSectionExtraction.h
//
// Description:	This file is an include file used to define the Protocol for the
//		        Guided Section Extraction Protocol. It is used for GUID processing
//               for the Firmware Volume.
//
//<AMI_FHDR_END>
//*****************************************************************************

#ifndef __GUIDED_SECTION_EXTRACTION_PROTOCOL_H__
#define __GUIDED_SECTION_EXTRACTION_PROTOCOL_H__
#ifdef __cplusplus
extern "C" {
#endif
#include <EFI.h>

typedef struct _EFI_GUIDED_SECTION_EXTRACTION_PROTOCOL EFI_GUIDED_SECTION_EXTRACTION_PROTOCOL;

typedef EFI_STATUS (EFIAPI *EFI_EXTRACT_GUIDED_SECTION)(
    IN EFI_GUIDED_SECTION_EXTRACTION_PROTOCOL   *This,
    IN VOID                                     *InputSection,
    OUT VOID                                    **OutputBuffer,
    OUT UINTN                                   *OutputSize,
    OUT UINT32                                  *AuthenticationStatus);

//**********************************************************************
//<AMI_SHDR_START>
//
// Name:        EFI_GUIDED_SECTION_EXTRACTION_PROTOCOL
//
// Description: Provide proccessing for extracting a Guided Section.
//
// Fields:     Name        Type        Description
//        ------------------------------------------------------------
//        ExtractSection    EFI_EXTRACT_GUIDED_SECTION
//
//<AMI_SHDR_END>
//**********************************************************************
typedef struct _EFI_GUIDED_SECTION_EXTRACTION_PROTOCOL {
    EFI_EXTRACT_GUIDED_SECTION ExtractSection;
} EFI_GUIDED_SECTION_EXTRACTION_PROTOCOL;


/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2005, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
