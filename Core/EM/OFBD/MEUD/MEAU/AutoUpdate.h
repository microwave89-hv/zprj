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
// $Header: /Alaska/SOURCE/Modules/OFBD Intel ME Update/AutoUpdate.h 1     8/30/11 8:17a Klzhan $
//
// $Revision: 1 $
//
// $Date: 8/30/11 8:17a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/OFBD Intel ME Update/AutoUpdate.h $
// 
// 1     8/30/11 8:17a Klzhan
// 
//
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:    AutoUpdate.h
//
// Description: Header file for component
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __AUTOUPDATE__H__
#define __AUTOUPDATE__H__
#ifdef __cplusplus
extern "C"
{
#endif

#include <Token.h>

// {80E1202E-2697-4264-9CC9-80762C3E5863}
#define MEAU_VAR_GUID { 0xC87690DC, 0x9005, 0x47EA, 0xAC, 0x34, 0x12, 0xF, 0xD8, 0x36, 0x33, 0x7D}


#define MEUD_FILE_GUID \
{ 0xfeaaa7a6, 0xcb95, 0x4670, 0xb4, 0x99, 0x87, 0x7f, 0xa6, 0xca, 0x6b, 0xae }

#define ME_VERSION_VALUE(a) \
(UINT32)((a.CoreMajor << 16) + (a.CoreMinor))

#define ME_VERSION_VALUE1(a) \
(UINT32)((a.CoreBuild << 16) + (a.CorePatch))

#define FLASH_BASE_ADDRESS(a) (UINTN)(0xFFFFFFFF - GetFlashCapacity() + 1 + (UINTN)a)


#pragma pack(1)
typedef struct
{
    UINT8 UpdateGBE;
    UINT8 UpdateME;
    UINT8 UpdateMEDS;
    UINT8 ForceME;
} MEAUTOUpdate;

#pragma pack()

#define MEAUTOUPD_MAIN 1
#define MEAUTOUPD_FLASH 2

#define FLASH_PROGRESS_KEY 100
#define FLASH_START_KEY 101

#include <Setup.h>
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