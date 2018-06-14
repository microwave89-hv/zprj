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
// $Header: /Alaska/BIN/Core/Include/PPI/FirmwareVolumeInfo.h 1     2/05/11 2:15p Artems $
//
// $Revision: 1 $
//
// $Date: 2/05/11 2:15p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/PPI/FirmwareVolumeInfo.h $
// 
// 1     2/05/11 2:15p Artems
// EFI_PEI_FIRMWARE_VOLUME_INFO definition
// 
// 6     1/13/10 2:13p Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:  <This File's Name>
//
// Description:	
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __FIRMWARE_VOLUME_INFO__H__
#define __FIRMWARE_VOLUME_INFO__H__
#ifdef __cplusplus
extern "C" {
#endif

#define EFI_PEI_FIRMWARE_VOLUME_INFO_PPI_GUID \
  { 0x49edb1c1, 0xbf21, 0x4761, { 0xbb, 0x12, 0xeb, 0x0, 0x31, 0xaa, 0xbb, 0x39 } }

GUID_VARIABLE_DECLARATION(gEfiFirmwareVolumeInfoPpiGuid, EFI_PEI_FIRMWARE_VOLUME_INFO_PPI_GUID);

typedef struct _EFI_PEI_FIRMWARE_VOLUME_INFO_PPI {
  EFI_GUID            FvFormat;
  VOID                *FvInfo;
  UINT32              FvInfoSize;
  EFI_GUID            *ParentFvName;
  EFI_GUID            *ParentFileName;
} EFI_PEI_FIRMWARE_VOLUME_INFO_PPI;

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
