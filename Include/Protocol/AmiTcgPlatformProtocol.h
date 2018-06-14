//**********************************************************************//
//**********************************************************************//
//**                                                                  **//
//**        (C)Copyright 1985-2012, American Megatrends, Inc.         **//
//**                                                                  **//
//**                       All Rights Reserved.                       **//
//**                                                                  **//
//**        5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093         **//
//**                                                                  **//
//**                       Phone: (770)-246-8600                      **//
//**                                                                  **//
//**********************************************************************//
//**********************************************************************//
//**********************************************************************//
// $Header: /Alaska/SOURCE/Modules/TCG2/CommonHeaders/AmiTcgPlatformProtocol/AmiTcgPlatformProtocol.h 1     4/21/14 2:15p Fredericko $
//
// $Revision: 1 $
//
// $Date: 4/21/14 2:15p $
//**********************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/TCG2/CommonHeaders/AmiTcgPlatformProtocol/AmiTcgPlatformProtocol.h $
// 
// 1     4/21/14 2:15p Fredericko
// 
// 1     10/08/13 12:01p Fredericko
// Initial Check-In for Tpm-Next module
// 
// 1     7/10/13 5:59p Fredericko
// [TAG]  		EIP120969
// [Category]  	New Feature
// [Description]  	TCG (TPM20)
// 
// 1     12/12/11 3:03p Fredericko
// [TAG]  		EIP76865
// [Category]  	Improvement
// [Description]  	Dual Support for TCM and TPM. System could hang in TXT
// if txt is enabled in setup
// [Files]  		AmiTcgPlatfompeilib.c, AmiTcgPlatformPpi.cif,
// AmiTcgPlatformPpi.h, AmiTcgPlatformProtocol.cif,
// AmiTcgPlatformProtocol.h,
// EMpTcmPei.c, TcgDxe.cif, TcgPei.cif, TcgPeiAfterMem.cif,
// TcgPeiAfterMem.mak, TcgTcmPeiAfterMem.c, xTcgDxe.c, xTcgPei.c, 
// xTcgPeiAfterMem.c 
// 
// 1     12/12/11 2:59p Fredericko
// [TAG]  		EIP76865
// [Category]  	Improvement
// [Description]  	Dual Support for TCM and TPM. System could hang in TXT
// if txt is enabled in setup
// [Files]  		AmiTcgPlatfompeilib.c, AmiTcgPlatformPpi.cif,
// AmiTcgPlatformPpi.h, AmiTcgPlatformProtocol.cif,
// AmiTcgPlatformProtocol.h,
// EMpTcmPei.c, TcgDxe.cif, TcgPei.cif, TcgPeiAfterMem.cif,
// TcgPeiAfterMem.mak, TcgTcmPeiAfterMem.c, xTcgDxe.c, xTcgPei.c, 
// xTcgPeiAfterMem.c 
//
//**********************************************************************//

#ifndef _AMI_TCG_PLATFORM_PROTOCOL_H_
#define _AMI_TCG_PLATFORM_PROTOCOL_H_

#include <token.h>

#define AMI_TCG_PLATFORM_PROTOCOL_GUID \
	{0x320bdc39, 0x3fa0, 0x4ba9, 0xbf, 0x2d, 0xb3, 0x3f, 0x72, 0xba, 0x9c, 0xa1}

typedef struct _AMI_TCG_PLATFORM_PROTOCOL AMI_TCG_PLATFORM_PROTOCOL;

// for now all it does is return the platform security support type
typedef UINT8 (*GET_TCG_SUPPORT_TYPE)();

struct _AMI_TCG_PLATFORM_PROTOCOL {
    GET_TCG_SUPPORT_TYPE                GetPlatformSecurityType;
};

#endif

//**********************************************************************//
//**********************************************************************//
//**                                                                  **//
//**        (C)Copyright 1985-2012, American Megatrends, Inc.         **//
//**                                                                  **//
//**                       All Rights Reserved.                       **//
//**                                                                  **//
//**        5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093         **//
//**                                                                  **//
//**                       Phone: (770)-246-8600                      **//
//**                                                                  **//
//**********************************************************************//
//**********************************************************************//
