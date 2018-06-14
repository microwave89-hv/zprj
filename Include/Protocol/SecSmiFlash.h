//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
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
// $Header: /Alaska/SOURCE/Modules/SecureFlashPkg/SecureSmiFlash/SecSmiFlash.h 8     3/18/14 3:10p Alexp $
//
// $Revision: 8 $
//
// $Date: 3/18/14 3:10p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SecureFlashPkg/SecureSmiFlash/SecSmiFlash.h $
// 
// 8     3/18/14 3:10p Alexp
// change year to 2014 in ftr & hdr
// 
// 7     6/12/13 3:53p Alexp
// CapsuleValidate() made external function in SecSmiFlash API
// 
// 6     5/18/12 3:55p Alexp
// Add pointer to local copy of *RomLayout table inside Sec Smi Flash
// Protocol table
// 
// 5     2/03/12 2:41p Alexp
// Use SHA256 Hash for Hash table
// 
// 4     1/18/12 5:39p Alexp
// add defines SEC_FLASH_HASH_TBL_BLOCK_COUNT/SEC_FLASH_HASH_TBL_SIZE
// 
// 3     1/13/12 4:29p Alexp
// cleaned up comments
// 
// 2     11/03/11 6:45p Alexp
// define Afu Flash page as SDL token: AFU_FLASH_PAGE_SIZE
// 
// 4     5/25/11 8:32p Alexp
// change FSHandle from *UINT32 to UINT32 
// 
// 8     4/22/11 4:36p Alexp
// hardwire sw smi codes for Sec SMI. 
// 
// 6     4/18/11 7:20p Alexp
// change HashTable to Sha1. Temp solution. may remove table as not
// practical
// 
// 5     4/13/11 7:09p Alexp
// enhanced Protocol with local poijters to HashTbl, Capsule, FSHandle 
// 
// 3     4/11/11 2:11p Alexp
// -Revision 12 and upper to support "Installed" field in Flash Info as
// bit mask
// -Add support for new CApsule SigningCert header
// - Replace PKpub with new FW Sign key as a root Platform key to verify
// Capsule Sig with
//**********************************************************************

#ifndef _EFI_SEC_SMI_FLASH_H_
#define _EFI_SEC_SMI_FLASH_H_

#include <RomLayout.h>
#include <Protocol/Hash.h>
#include <Protocol/AmiDigitalSignature.h>
#include <BaseCryptLib.h>
#include <FlashUpd.h>
#include <Protocol/SmiFlash.h>
#include "AmiCertificate.h"

// {3BF4AF16-AB7C-4b43-898D-AB26AC5DDC6C}
#define EFI_SEC_SMI_FLASH_GUID \
{ 0x3bf4af16, 0xab7c, 0x4b43, { 0x89, 0x8d, 0xab, 0x26, 0xac, 0x5d, 0xdc, 0x6c } }

GUID_VARIABLE_DECLARATION(gSecureSMIFlashProtocolGuid, EFI_SEC_SMI_FLASH_GUID);

typedef struct _EFI_SEC_SMI_FLASH_PROTOCOL EFI_SEC_SMI_FLASH_PROTOCOL;

// SMI Flash INFO_BLOCK->Implemented bit mask flags
//typedef enum {SMIflash=0, noSMIflash=1, SecuredSMIflash=2};
#ifndef SwSmi_LoadFwImage 
#define SwSmi_LoadFwImage    0x1D
#define SwSmi_GetFlashPolicy 0x1E
#define SwSmi_SetFlashMethod 0x1F
#endif
// SMI Flash Command API
typedef enum {
 SecSMIflash_Load     =SwSmi_LoadFwImage,
 SecSMIflash_GetPolicy=SwSmi_GetFlashPolicy,
 SecSMIflash_SetFlash =SwSmi_SetFlashMethod,
    SMIflash_Enable  =0x20, 
    SMIflash_Read    =0x21,
    SMIflash_Erase   =0x22,
    SMIflash_Write   =0x23,
    SMIflash_Disable =0x24, 
    SMIflash_Info    =0x25
};

#define SEC_FLASH_HASH_TBL_BLOCK_COUNT  (FLASH_SIZE/FLASH_BLOCK_SIZE)
#define SEC_FLASH_HASH_TBL_SIZE (sizeof(EFI_SHA256_HASH)*SEC_FLASH_HASH_TBL_BLOCK_COUNT)

typedef struct {
    FLASH_UPD_POLICY	FlUpdPolicy;
    UINT8				PKpub[DEFAULT_RSA_KEY_MODULUS_LEN];
    UINT8  				ErrorCode;
} FLASH_POLICY_INFO_BLOCK;

typedef struct {
    AMI_FLASH_UPDATE_BLOCK	FlUpdBlock;
    UINT8  				ErrorCode;
    UINT32 				FSHandle;
} FUNC_FLASH_SESSION_BLOCK;

typedef EFI_STATUS (*LOAD_FLASH_IMAGE) (
  IN OUT FUNC_BLOCK           *FuncBlock
);

typedef EFI_STATUS (*GET_FLASH_UPD_POLICY) (
  IN OUT FLASH_POLICY_INFO_BLOCK  *InfoBlock
);

typedef EFI_STATUS (*SET_FLASH_UPD_METHOD) (
  IN OUT FUNC_FLASH_SESSION_BLOCK  *InfoBlock
);

typedef EFI_STATUS (*CAPSULE_VALIDATE) (
  IN OUT UINT8                      **pFWCapsule,
  IN OUT APTIO_FW_CAPSULE_HEADER    **pFWCapsuleHdr
);

struct _EFI_SEC_SMI_FLASH_PROTOCOL {
  LOAD_FLASH_IMAGE        LoadFwImage;  // SW SMI Port 0x1d
  GET_FLASH_UPD_POLICY GetFlUpdPolicy;	// SW SMI Port 0x1e
  SET_FLASH_UPD_METHOD SetFlUpdMethod;	// SW SMI Port 0x1f
  CAPSULE_VALIDATE    CapsuleValidate;
  UINT32                  *pFwCapsule;  // Local buffer for FwCapsule
  ROM_AREA                  *RomLayout; // Local copy of Rom Layout table 
  EFI_SHA256_HASH            *HashTbl;  // ptr to Fw image Hash table
  UINT32                     FSHandle;  // SetFlash Session handle 
};

#endif

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
