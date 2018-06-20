//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.            **
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
// $Header: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/CRB/CRBLib.h 2     4/16/13 5:30a Thomaschen $
//
// $Revision: 2 $
//
// $Date: 4/16/13 5:30a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/CRB/CRBLib.h $
// 
// 2     4/16/13 5:30a Thomaschen
// 
// 1     2/12/12 10:38p Victortu
// Intel SharkBay CRB initially releases.
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:        CRBLib.h
//
// Description: Custom Reference Board (or Demo Board) header file.
//              Defines all the CRB specific equates and structures in
//              this file. 
//
//<AMI_FHDR_END>
//*************************************************************************

#ifndef __CRBLIB_H__
#define __CRBLIB_H__

//---------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

UINT32                          CrbHdaVerbTbl8[];
UINT32                          CrbHdaVerbTbl9[];
UINT32                          CrbHdaVerbTbl10[];
UINT32                          ZprjHdaVerbTbl[];

BOOLEAN IsRecoveryJumper(
  IN EFI_PEI_SERVICES **PeiServices
);

#ifdef __cplusplus
}
#endif

#endif


//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
