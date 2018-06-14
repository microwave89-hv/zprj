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
//*************************************************************************
// $Header: /Alaska/SOURCE/Modules/OFBD Intel ME Update/CSP_MEUD/ME80/CSP_MEUD.h 2     5/16/13 6:30a Klzhan $
//
// $Revision: 2 $
//
// $Date: 5/16/13 6:30a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/OFBD Intel ME Update/CSP_MEUD/ME80/CSP_MEUD.h $
// 
// 2     5/16/13 6:30a Klzhan
// [TAG]  		EIPNone
// [Category]  	Improvement
// [Description]  	Add define for flash commands.
// 
// 1     4/22/11 2:47a Klzhan
// Initial check - in
// 
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	CSP_MEUD.h
//
// Description:
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef _EFI_CSP_MEUD_H_
#define _EFI_CSP_MEUD_H_
#ifdef __cplusplus
extern "C" {
#endif

VOID
FlashReadCommand    (
    IN  volatile UINT8*     pByteAddress,
    OUT UINT8               *Byte,
    IN  UINT32              Length
);

VOID
FlashProgramCommand (
    IN volatile UINT8*      pByteAddress,
    IN UINT8                *Byte,
    IN UINT32               Length
);

VOID
FlashEraseCommand   (
    IN volatile UINT8*      pBlockAddress
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
