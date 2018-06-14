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
// $Header: /Alaska/SOURCE/Modules/SMIFlash/smiflash.h 9     3/06/12 1:43a Klzhan $
//
// $Revision: 9 $
//
// $Date: 3/06/12 1:43a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SMIFlash/smiflash.h $
// 
// 9     3/06/12 1:43a Klzhan
// Don't update another NVRam region.
// 
// 8     8/29/11 7:10a Klzhan
// 
// 7     5/16/11 4:39a Klzhan
// [TAG]  		EIP58139
// [Category]  	Improvement
// [Description]  	Support  OA3.0.
// [Files]  		SMIFlash.h
// 
// 6     12/21/09 4:40a Klzhan
// Improvement : Updated for Aptio Source Enhancement.
//
// 5     7/02/09 8:34a Klzhan
// Improvement:   Add a parameter for ME FW Update.
//
// 4     3/05/09 1:17p Felixp
//  - Bug fix. EIP 17632.
//   Flash Blocks that do not belong to FV_BB, FV_MAIN, and FV_NVRAM
//   have been reported as boot block.
//   The SmiFlash.c is updated to report these blocks as non critical
// blocks.
//   The SmiFlash.h header is updated to define non critical block type
// (NC_BLOCK ).
//  - Headers updated.
//
// 3     12/29/06 3:11p Felixp
// Embedded Controller support added
//
// 2     3/02/06 10:31a Davidd
// Updated BLOCK_DESC array in INFO_BLOCK structure to correct the
// data corruption problem when calling GetFlashInfo.
//
// 1     4/05/05 3:48p Sivagarn
// Initial Checkin
//
//**********************************************************************

#ifndef _EFI_SMI_FLASH_H_
#define _EFI_SMI_FLASH_H_

#include <token.h>

// {6F2C06A8-D4B4-4a93-9F78-2B480BE80E0F}
#define EFI_SMI_FLASH_GUID \
    {0x6f2c06a8,0xd4b4,0x4a93,0x9f,0x78,0x2b,0x48,0xb,0xe8,0xe,0xf}

#define NUMBER_OF_BLOCKS (FLASH_SIZE/FLASH_BLOCK_SIZE)

#define SMIFLASH_ENABLE_FLASH      0x20
#define SMIFLASH_READ_FLASH        0x21
#define SMIFLASH_ERASE_FLASH       0x22
#define SMIFLASH_WRITE_FLASH       0x23
#define SMIFLASH_DISABLE_FLASH     0x24
#define SMIFLASH_GET_FLASH_INFO    0x25

#pragma pack(1)
typedef struct {
    UINT64      BufAddr;
    UINT32      BlockAddr;      //0 starts at 0xfff0_0000
    UINT32      BlockSize;
    UINT8       ErrorCode;
} FUNC_BLOCK;

typedef struct {
    UINT32      StartAddress;
    UINT32      BlockSize;
    UINT8       Type;
} BLOCK_DESC;

typedef enum {
    BOOT_BLOCK
    ,MAIN_BLOCK
    ,NV_BLOCK
#if SMI_FLASH_INTERFACE_VERSION > 10
    ,EC_BLOCK
#endif
    ,NVB_BLOCK
    ,OA3_FLASH_BLOCK_DESC_TYPE = 0x4A
    ,NC_BLOCK = 0x80 //Types from NC_BLOCK to 0xFF are reserved for non critical blocks
} FLASH_BLOCK_TYPE;

typedef struct  {
    UINT32      Length;
    UINT8       Implemented;
    UINT8       Version;
    UINT16      TotalBlocks;
#if SMI_FLASH_INTERFACE_VERSION > 10
    UINT32      ECVersionOffset;
    UINT32      ECVersionMask;
#endif
    BLOCK_DESC  Blocks[NUMBER_OF_BLOCKS];
} INFO_BLOCK;
#pragma pack()

typedef struct _EFI_SMI_FLASH_PROTOCOL EFI_SMI_FLASH_PROTOCOL;

typedef EFI_STATUS (*GET_FLASH_INFO) (
    IN OUT INFO_BLOCK           *InfoBlock
);

typedef EFI_STATUS (*ENABLE_FLASH) (
    IN OUT FUNC_BLOCK           *FuncBlock
);

typedef EFI_STATUS (*DISABLE_FLASH) (
    IN OUT FUNC_BLOCK           *FuncBlock
);

typedef EFI_STATUS (*READ_FLASH) (
    IN OUT FUNC_BLOCK           *FuncBlock
);

typedef EFI_STATUS (*WRITE_FLASH) (
    IN OUT FUNC_BLOCK           *FuncBlock
);

typedef EFI_STATUS (*ERASE_FLASH) (
    IN OUT FUNC_BLOCK           *FuncBlock
);

struct _EFI_SMI_FLASH_PROTOCOL {
    GET_FLASH_INFO  GetFlashInfo;
    ENABLE_FLASH    EnableFlashWrite;
    DISABLE_FLASH   DisableFlashWrite;
    READ_FLASH      ReadFlash;
    WRITE_FLASH     WriteFlash;
    ERASE_FLASH     EraseFlash;
    UINT32          FlashCapacity;
};


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
