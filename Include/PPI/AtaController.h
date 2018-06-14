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
// $Header: /Alaska/BIN/Core/Modules/Recovery/AtaController.h 2     4/10/06 9:52a Ambikas $
//
// $Revision: 2 $
//
// $Date: 4/10/06 9:52a $
//*****************************************************************************
// Revision	History
// ----------------
// $Log: /Alaska/BIN/Core/Modules/Recovery/AtaController.h $
// 
// 2     4/10/06 9:52a Ambikas
// 
// 1     12/01/05 9:35a Felixp
// 
// 1     10/10/05 11:40a Radhikav
// Initial Release.
// 
// 
// 
//
//*****************************************************************************




#ifndef _PEI_ATA_CONTROLLER_PPI_H
#define _PEI_ATA_CONTROLLER_PPI_H
#ifdef __cplusplus
extern "C" {
#endif

#include "EFI.h"
#include "PEI.h"

#define PEI_ATA_CONTROLLER_PPI_GUID \
  { 0xa1e2176f, 0xcbda, 0x4f32, 0x87, 0x56, 0x7d, 0x7a, 0xe5, 0x22, 0xd6, 0x93 }

typedef struct _PEI_ATA_CONTROLLER_PPI	PEI_ATA_CONTROLLER_PPI;

typedef 
EFI_STATUS
(EFIAPI *PEI_ENABLE_ATA) (
  IN EFI_PEI_SERVICES               **PeiServices,
  IN PEI_ATA_CONTROLLER_PPI			 *This,
  IN UINT8                          ChannelMask
  );

typedef struct _PEI_ATA_CONTROLLER_PPI {
  PEI_ENABLE_ATA                    EnableAtaChannel;
} PEI_ATA_CONTROLLER_PPI;


#define PEI_ICH_IDE_PRIMARY     0x01
#define PEI_ICH_IDE_SECONDARY   0x02

#define PEI_IDE_RECOVERY_NATIVE_MODE_PPI_GUID \
  { 0x7e13637a, 0xc3f8, 0x43d1, 0xb0, 0x51, 0xed, 0x19, 0xd7, 0x8, 0xec, 0x7a }

typedef struct {
	UINT16 PCMDBarAddress;
	UINT16 PCNLBarAddress;
	UINT16 SCMDBarAddress;
	UINT16 SCNLBarAddress;
} PEI_IDE_RECOVERY_NATIVE_MODE_PPI;

#ifdef __cplusplus
}
#endif
#endif



