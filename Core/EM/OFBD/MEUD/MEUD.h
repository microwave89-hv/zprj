//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/OFBD Intel ME Update/MEUD.h 7     5/16/13 2:00a Klzhan $
//
// $Revision: 7 $
//
// $Date: 5/16/13 2:00a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/OFBD Intel ME Update/MEUD.h $
// 
// 7     5/16/13 2:00a Klzhan
// [TAG]  		EIPNone
// [Category]  	Improvement
// [Description]  	Support OFBD_VERSION is 0x220.
// 
// 6     9/09/11 7:27a Klzhan
// Fix build Error when enable MEAU
// 
// 5     8/05/11 6:43a Klzhan
// [TAG]  		EIP63481
// [Category]  	New Feature
// [Description]  	AFU support commands for each regions update.
// 
// 4     2/10/11 5:52a Klzhan
// [TAG]  		EIP52968
// [Category]  	New Feature
// [Description]  	Update ME through OFBD not SMIFlash.
// [Files]  		MEUD.sdl
// MEUD.h
// MEUD.c
// 
// 3     12/27/10 4:42a Klzhan
// Improvement : ME auto update.
// 
// 2     10/13/09 3:33a Klzhan
// Updated for Aptio Source Enhancement.
// 
// 1     9/30/09 11:15p Lawrencechang
// Move Intel ME update module part to an independent SS path.
// 
// 3     8/31/09 9:03a Klzhan
// Update Procedure name to support Capella.
// 
// 2     7/02/09 8:25a Klzhan
// 
// 1     4/13/09 5:47a Lawrencechang
// Initial check-in.
// 
// 1     3/13/06 1:16a Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	MEUD.h
//
// Description:
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef _EFI_MEUD_H_
#define _EFI_MEUD_H_
#ifdef __cplusplus
extern "C" {
#endif
UINT32     GetFlashCapacity(VOID);
UINT32     GetHFS(VOID);
EFI_STATUS HMRFPO_LOCK_MSG(VOID);
EFI_STATUS HMRFPO_ENABLE_MSG(VOID);
VOID       CSP_MEUDInSmm(VOID);
EFI_STATUS CSP_ReportMEInfo(UINT8 Func_Num, UINT32* BASE_Address, UINT32* Length);
EFI_STATUS GET_FW_VERSION(UINT16* MeFwVersionData);
EFI_STATUS
GetRegionOffset( 
    IN UINT8    Region,
    IN OUT UINT32*  Offset,
    IN OUT UINT32*  Length
);
#if OFBD_VERSION >= 0x220
extern BOOLEAN DoNotConvert;
#endif

#define MEUD_ERROR_GUID \
{ 0x732BD39, 0xD6B0, 0x4039, 0xB6, 0xC2, 0x96, 0x54, 0x46, 0x6D, 0xE5, 0x25 }

#define MEUD_FILE_GUID \
{ 0xfeaaa7a6, 0xcb95, 0x4670, 0xb4, 0x99, 0x87, 0x7f, 0xa6, 0xca, 0x6b, 0xae }

#define ME_VERSION_VALUE(a) \
(UINT32)((a.CoreMajor << 16) + (a.CoreMinor))

#define ME_VERSION_VALUE1(a) \
(UINT32)((a.CoreBuild << 16) + (a.CorePatch))

// Override for new ME.
#if OFBD_VERSION >= 0x220
#define FLASH_BASE_ADDRESS(a) (UINTN)((UINT64)a)
#else
#define FLASH_BASE_ADDRESS(a) (UINTN)(0xFFFFFFFF - GetFlashCapacity() + 1 + (UINTN)a)
#endif

#ifdef PCIEX_BASE_ADDRESS 
#define PCIE_CFG_ADDRESS(bus, dev, func, reg) \
            ((UINTN)(PCIEX_BASE_ADDRESS + ((UINT8)(bus) << 20) + \
            ((UINT8)(dev) << 15) + ((UINT8)(func) << 12) + (reg)))
#endif
#define ME_BLK_PROTECT BIT00

typedef enum
{
   FDT_BLK,
   PDR_BLK,
   GBE_BLK,
   ME_BLK,
   ME_OPR_BLK,
   BIOS_BLK,
   MAX_BLK
}ME_BLOCK_TYPE;

#pragma pack(1)
typedef struct 
{
    CHAR8       Command[4];
    CHAR8       Description[64];
    UINT32	StartAddress;
    UINT32	BlockSize;
    UINT8	Type;
    UINT8	Status;
}ME_BLOCK_T;

typedef struct
{
    UINT8	bReturnStatus;
    UINT8	bSubFunction;
    UINT16	TotalBlocks;
    ME_BLOCK_T  BlockInfo[MAX_BLK];
}OFBD_TC_55_ME_INFO_STRUCT;

typedef struct
{
    UINT8	bReturnStatus;
    UINT8	bSubFunction;
    UINT32	TotalBlocks;
    UINT32	BlockIndex;
    UINT8	bHandleRequest;
    UINT8	bBlockType;
    UINT16	UpdateResult;
    UINT32	ddMeDataBuffer;
    UINT32	ddMeDataSize;
    UINT32	ddMeDataChecksum;
    UINT32	ddMessageBuffer;
}OFBD_TC_55_ME_PROCESS_STRUCT;

typedef struct
{
    UINT16    CoreMajor;
    UINT16    CoreMinor;
    UINT16    CoreBuild;
    UINT16    CorePatch;
}ME_FW_VERSION;
#pragma pack()
VOID
MEProcessHandler(
    IN OUT OFBD_TC_55_ME_PROCESS_STRUCT  **MEProcessStructPtr
);
    /****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
