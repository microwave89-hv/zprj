//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

//*************************************************************************
// $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/SB Protocols/SBPlatformData.h 3     4/24/13 6:50a Scottyang $
//
// $Revision: 3 $
//
// $Date: 4/24/13 6:50a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/SB Protocols/SBPlatformData.h $
// 
// 3     4/24/13 6:50a Scottyang
// [TAG]  		EIP82149
// [Category]  	Improvement
// [Description]  	 Intel(R) 8 Series Chipset Family Deep Sx and CPU
// Soft-Strap BIOS Override Co-Existence Issue. If the soft-strap override
// feature is required and enabled, BIOS must disable Deep Sx
// functionality.
// [Files]  		SBDxe.c, SB.sd, SBPlatformData.h
// 
// 2     10/16/12 5:15a Scottyang
// [TAG] None
// 
// [Category] Improvement
// 
// [Description] One rom for two chip and one chip. 
// [Files] SPPEIBoard.c, SB.sd, SBDxe.c, SBPEI.c, PCH.asl,
// SBPlatformData.h
// 
// 1     2/08/12 8:26a Yurenlai
// Intel Lynx Point/SB eChipset initially releases.
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:	SBPlatformData.h
//
// Description:	SB Specific Setup Variables and Structures
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef _SB_PLATFORM_DATA_H_
#define _SB_PLATFORM_DATA_H_
#ifdef __cplusplus
extern "C" {
#endif

  #pragma pack(1)

  typedef struct _SB_PLATFORM_DATA
  {
    UINT8 PchHotLevelPresent;
    UINT8 GbePciePortNum;
    UINT8 PcieSBDE;
    UINT8 PchRid;
    UINT8 LPTType;
    UINT8 HideDeepSx;                   // [EIP82149]
  }SB_PLATFORM_DATA;

  #pragma pack()

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif
//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
