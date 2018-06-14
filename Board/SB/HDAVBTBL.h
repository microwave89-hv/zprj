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
// $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Board/HDAVBTBL.h 1     2/08/12 8:22a Yurenlai $
//
// $Revision: 1 $
//
// $Date: 2/08/12 8:22a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Board/HDAVBTBL.h $
// 
// 1     2/08/12 8:22a Yurenlai
// Intel Lynx Point/SB eChipset initially releases.
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:        HDAVBTBL.h
//
// Description: HD Audio Verb Table
//
//<AMI_FHDR_END>
//*************************************************************************

#ifndef _HDAVBTBL_H // To Avoid this header get compiled twice
#define _HDAVBTBL_H
#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    UINT32                      CodecId32;
    UINT16                      CodecSubId16;
    UINT8                       RevisionId;    // 0xFF applies to all steppings
    UINT8                       FrontPanel;
    UINT16                      RearSideNo;
    UINT16                      frontSideNo;
    UINT32                      *VerbPtr;
} HDA_VERB_TABLE;

OEM_HDA_VERB_TABLE_CONTENT
HDA_VERB_TABLE                  HdaVerbTbl[] = { OEM_HDA_VERB_TABLE };


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
