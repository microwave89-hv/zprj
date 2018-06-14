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
// $Header: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Include/Capsule.h 2     4/16/13 5:42a Thomaschen $
//
// $Revision: 2 $
//
// $Date: 4/16/13 5:42a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Include/Capsule.h $
// 
// 2     4/16/13 5:42a Thomaschen
// Fixed for EIP106722.
//
// 5     2/07/13 5:16p Artems
// [TAG]  		EIP106722
// [Category]  	Bug Fix
// [Severity]  	Critical
// [Symptom]  	Win8 firmware update doesn't work
// [RootCause]  	For Win8 update capsule CapsuleRecovery device didn't
// skip capsule header
// [Solution]  	Added unique GUID to distinguish between AFU and Win8
// capsule update
// [Files]  		Capsule2_0.c CapsuleRecovery.c Capsule.h
// 
// 4     7/20/12 10:06a Artems
// [TAG]  		EIP93520
// [Category]  	New Feature
// [Description]  	Support of Microsoft ESRT spec
// Added new capsule guids and header definitions
// [Files]  		Capsule.h
// 
// 3     5/19/12 2:27p Artems
// [TAG]  		EIP74625
// [Category]  	Improvement
// [Description]  	Capsule PPI. Need to update Capsule PEI driver to
// comply with Intel MRC reference code calling convention
// [Files]  		Capsule.h Capsule.dxs Capsule.mak Capsule.sdl CapsuleDefs.h
// 
// 2     10/28/11 1:17p Artems
// Moved header from Capsule module to Core
// 
// 5     1/28/10 2:51p Artems
// Replaced TABs with Spaces
// 
// 4     7/09/09 5:10p Artems
// Changed file header
// 
// 3     3/05/09 7:09p Artems
// EIP 20013 Modified code according to code standard
// 
// 2     3/05/09 5:29p Artems
// EIP 20013 Modified according to coding standard
// 
// 1     4/03/07 4:21p Robert
// 
// 1     1/12/07 12:23p Artems
// 

//<AMI_FHDR_START>
//----------------------------------------------------------------------
//
// Name:        Capsule.h
//
// Description: UEFI capsule data structure definition
//
//----------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef __CAPSULE__H__
#define __CAPSULE__H__
#ifdef __cplusplus
extern "C" {
#endif

#include <Efi.h>

//Capsule vendor-specific GUID and variable name
#define EFI_CAPSULE_AMI_GUID \
    { 0xfac2efad, 0x8511, 0x4e34, 0x9c, 0xae, 0x16, 0xa2, 0x57, 0xba, 0x94, 0x88 }

#ifndef APTIO_FW_CAPSULE_GUID   //AMI flash update capsule
#define APTIO_FW_CAPSULE_GUID \
    { 0x4A3CA68B, 0x7723, 0x48FB, 0x80, 0x3d, 0x57, 0x8c, 0xc1, 0xfe, 0xc4, 0x4d }
#endif

#define W8_SCREEN_IMAGE_CAPSULE_GUID \
    { 0x3b8c8162, 0x188c, 0x46a4, 0xae, 0xc9, 0xbe, 0x43, 0xf1, 0xd6, 0x56, 0x97 }

#define W8_FW_UPDATE_IMAGE_CAPSULE_GUID \
    { 0x7039436b, 0x6acf, 0x433b, 0x86, 0xa1, 0x36, 0x8e, 0xc2, 0xef, 0x7e, 0x1f }


#define CAPSULE_UPDATE_VAR          L"AmiCapUp"


#define MAX_SUPPORT_CAPSULE_NUM               50

typedef struct {
    EFI_EVENT CapsuleExitBootServiceEvent;
    BOOLEAN IsRuntimeMode;
} EFI_CAPSULE_RUNTIME_DATA;

#pragma pack(push, 1)
typedef struct {
    EFI_CAPSULE_HEADER Header;
    UINT8 Version;
    UINT8 Checksum;
    UINT8 ImageType;
    UINT8 Reserved;
    UINT32 Mode;
    UINT32 ImageOffsetX;
    UINT32 ImageOffsetY;
    UINT8 Image[1];
} W8_IMAGE_CAPSULE;

#pragma pack(pop)



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