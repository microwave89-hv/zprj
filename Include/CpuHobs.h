//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.            **
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
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/Haswell/AMI Cpu PKG/CPU Core/CPU Hobs/CpuHobs.h 2     11/23/12 2:10a Hsingyingchung $
//
// $Revision: 2 $
//
// $Date: 11/23/12 2:10a $
//*****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/Haswell/AMI Cpu PKG/CPU Core/CPU Hobs/CpuHobs.h $
// 
// 2     11/23/12 2:10a Hsingyingchung
// [TAG]  		EIP99095
// [Category]  	Improvement
// [Description]  	Update by XTU 4.X
// 
// 1     2/07/12 3:58a Davidhsieh
// 
// 1     5/06/11 6:07a Davidhsieh
// First release
// 
// 11    10/09/10 11:29p Markw
// Fix Label 33.
// 
// 10    10/09/10 10:04p Markw
// Fix Label 32.
// 
// 9     10/06/10 7:52p Markw
// Issue Number:  45131
// 
// Category:  Spec Update
// 
// Severity:  Normal
// 
// Description:  Support for IA core current limit and iGfx core current
// limit for XTU on Sandy Bridge.
// 
// Files:  CpuPeiBoard.c, CpuDxeBoard.c, Cpu.h, CpuHobs.h
// 
// 8     8/09/10 10:52a Markw
// Add XTU 2.1 support.
// 
// 7     4/02/10 11:35a Markw
// Update HOB for Sandy Bridge VID support.
// 
// 6     3/08/10 3:13p Markw
// Add XE support for Sandy Bridge.
// 
// 5     1/08/10 2:29p Markw
// Add HOB definition for saving TDC/TDP.
// 
// 4     10/28/09 5:24p Markw
// 
// 3     3/04/09 10:39a Markw
// Update copyright header.
// 
// 2     7/16/08 6:09p Markw
// Add DCA Hob.
// 
// 1     11/02/07 1:59p Markw
// 
//
//*****************************************************************************

//<AMI_FHDR_START>
//---------------------------------------------------------------------------
//
// Name:		CpuHobs.h
//
// Description:	Collection of CPU Hobs.
//
//---------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef _CPU_HOBS_H__
#define _CPU_HOBS_H__

#include <pei.h>
#include <hob.h>

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(push,1)

//This HOB is intended to be temporary until a better solution is available.

// {6865C455-8626-40d8-90F4-A69460A4AB5A}
#define DCA_HOB_GUID \
    {0x6865c455, 0x8626, 0x40d8, 0x90, 0xf4, 0xa6, 0x94, 0x60, 0xa4, 0xab, 0x5a}

typedef struct {
    EFI_HOB_GUID_TYPE   EfiHobGuidType;
    BOOLEAN Supported;
} DCA_HOB;

/////////////////////////////
////////////////////////////

//This HOB is subject to change at any CPU label and is only for the CPU module.

// {982D8C6F-F6F6-4135-A309-A4593EA56417}
#define AMI_INTERNAL_FACTORY_TDC_TDP_HOB_GUID \
    {0x982d8c6f, 0xf6f6, 0x4135, 0xa3, 0x9, 0xa4, 0x59, 0x3e, 0xa5, 0x64, 0x17}

typedef struct {
    EFI_HOB_GUID_TYPE   EfiHobGuidType;
    UINT8   Revision;		
    BOOLEAN IsSandyBridge;
    BOOLEAN IsHasWell;		
    UINT64  Reserved0;		
    UINT8   PowerConv;
    UINT8   CurConv;
    UINT8   TimeConv;
    UINT16  Tdc;
    UINT16  Tdp;                    //For Sandy Bridge, this also POWER_LIMIT_1
    UINT8   TdpLimitTime;           //For Sandy Bridge, this is POWER_LIMIT_1_TIME
    UINT8   Vid;
//Used for PERF_TUNE_SUPPORT Start
    UINT8   OneCoreRatioLimit;
    UINT8   TwoCoreRatioLimit;
    UINT8   ThreeCoreRatioLimit;
    UINT8   FourCoreRatioLimit;
    UINT8   FiveCoreRatioLimit;
    UINT8   SixCoreRatioLimit;
	UINT16	IaCoreCurrentMax;
	UINT16  IGfxCoreCurrentMax;
	UINT8	OneCoreRatioMax;	
	UINT8	TwoCoreRatioMax;	
	UINT8	ThreeCoreRatioMax;	
	UINT8	FourCoreRatioMax;	
	UINT8	FiveCoreRatioMax;	
	UINT8	SixCoreRatioMax;	
//Used for PERF_TUNE_SUPPORT End
} AMI_INTERNAL_FACTORY_TDC_TDP_HOB;

#pragma pack(pop)
/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
