//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
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
// $Header: /Alaska/BIN/Core/Include/Flash.h 9     11/14/11 5:43p Artems $
//
// $Revision: 9 $
//
// $Date: 11/14/11 5:43p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/Flash.h $
// 
// 9     11/14/11 5:43p Artems
// Added guid for flash write lock event
// 
// 8     8/27/10 1:21p Felixp
// The prototype of the FlashInit function is added. The function is
// implemented by the Flash module.
// 
// 7     5/21/09 4:30p Felixp
// Declaration of FlashRead function is added.
// 
// 6     12/29/06 2:56p Felixp
// Flash Interface Updated
// 
// 5     12/18/06 10:50a Robert
// Updated prototype to allow Is Program complete function to check an
// entire block of data not just one byte at a time
// 
// 4     11/01/06 5:49p Robert
// updated for use with newest Flash module code
// 
// 3     10/27/06 10:35a Felixp
// FlashVirtualFixup declaration added
// 
// 2     3/04/05 10:22a Mandal
// 
// 1     2/01/05 11:23a Felixp
// 
// 1     1/28/05 12:57p Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	Flash.h
//
// Description:	
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __FLASH__H__
#define __FLASH__H__
#ifdef __cplusplus
extern "C" {
#endif
#include <EFI.h>


#define AMI_EVENT_FLASH_WRITE_LOCK \
    { 0x49D34AE7, 0x9454, 0x4551, 0x8F, 0x71, 0x46, 0x7D, 0x8C, 0x0E, 0x4E, 0xF5 }

VOID FlashDeviceWriteEnable();
VOID FlashDeviceWriteDisable();
BOOLEAN FlashWriteBlock(UINT8* BlockAddress, UINT8 *Data);
EFI_STATUS FlashInit(volatile UINT8* pBlockAddress);

VOID FlashVirtualFixup(EFI_RUNTIME_SERVICES *pRS);

BOOLEAN FlashEraseBlock(volatile UINT8* BlockAddress);
VOID FlashBlockWriteEnable(UINT8* BlockAddress);
VOID FlashBlockWriteDisable(UINT8* BlockAddress);
BOOLEAN FlashProgram(volatile UINT8* Address, UINT8 *Data, UINT32 Length);
BOOLEAN  FlashRead(volatile UINT8* Address, UINT8 *Data, UINT32 Length);

#define BLOCK(adr) ( (UINTN)(adr) -  (((UINTN)(adr) - FlashDeviceBase)%FlashBlockSize) )

extern const UINT32 FlashBlockSize;
extern const UINTN FlashDeviceBase;
/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************