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
// $Header: /Alaska/SOURCE/Modules/AmiGopPolicy/AmiGopPolicy.h 3     5/15/14 2:39a Jameswang $
//
// $Revision: 3 $
//
// $Date: 5/15/14 2:39a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AmiGopPolicy/AmiGopPolicy.h $
// 
// 3     5/15/14 2:39a Jameswang
// [TAG]  		EIP168961
// [Category]  	New Feature
// [Description]  	Added AMI_GOP_POLICY_VARIABLE_GUID.
// 
// 2     7/26/12 7:30a Josephlin
// Update File Header.
// 
// 1     6/29/12 3:43a Josephlin
// [TAG]  		EIP91970
// [Category]  	New Feature
// [Description]  	Initial Release for Display Switch with UEFI GOP driver
// support.
// [Files]  		AmiGopPolicy.cif
// AmiGopPolicy.c
// AmiGopPolicy.h
// AmiGopPolicy.mak
// AmiGopPolicy.sd
// AmiGopPolicy.sdl
// AmiGopPolicy.uni
// AmiGopPolicyLib.c
// AmiGopPolicySetup.c
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:        AmiGopPolicy.h
//
// Description:	AmiGopPolicy Header File.
//
//<AMI_FHDR_END>
//**********************************************************************

#ifndef _AMI_GOP_POLICY_H_
#define _AMI_GOP_POLICY_H_
#ifdef __cplusplus
extern "C" {
#endif

#define AMI_GOP_POLICY_VARIABLE_GUID \
    {0xc143929c, 0xbf5d, 0x423b, 0x99, 0x9b, 0xf, 0x2d, 0xd2, 0xb6, 0x1f, 0xf7}

#pragma pack(1)

typedef struct _AMI_GOP_POLICY_SETUP_DATA
{
    UINT8   GopDeviceCount;
    UINT8   GopOutputCount;
} AMI_GOP_POLICY_SETUP_DATA;

#pragma pack()

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
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
