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
// $Header: /Alaska/SOURCE/Modules/TCG2/CommonHeaders/AmiTcgPlatformPpi/AmiTcgPlatformPpi.h 1     4/21/14 2:16p Fredericko $
//
// $Revision: 1 $
//
// $Date: 4/21/14 2:16p $
//**********************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/TCG2/CommonHeaders/AmiTcgPlatformPpi/AmiTcgPlatformPpi.h $
// 
// 1     4/21/14 2:16p Fredericko
// 
// 1     10/08/13 12:02p Fredericko
// Initial Check-In for Tpm-Next module
// 
// 1     7/10/13 6:00p Fredericko
// [TAG]  		EIP120969
// [Category]  	New Feature
// [Description]  	TCG (TPM20)
// 
// 1     12/12/11 3:06p Fredericko
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
// 1     12/12/11 2:58p Fredericko
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
#ifndef _AMI_TCG_PLATFORM_PPI_H_
#define _AMI_TCG_PLATFORM_PPI_H_
#include <PEI.h>


#ifdef __cplusplus
extern "C" {
#endif

#define AMI_TCG_PLATFORM_PPI_GUID \
	{0x5687f4a, 0x3ca7, 0x4d19, 0x9b, 0xc5, 0xe1, 0x80, 0xce, 0xa3, 0x56, 0x9f}

typedef struct _AMI_TCG_PLATFORM_PPI AMI_TCG_PLATFORM_PPI;

// for now all it does is return the platform security support type
typedef UINT8 (EFIAPI *GET_TCG_SUPPORT_TYPE)();

struct _AMI_TCG_PLATFORM_PPI {
    GET_TCG_SUPPORT_TYPE                GetPlatformSecurityType;
};

typedef struct _AMI_TPM20SUPPORTTYPE_PPI AMI_TPM20SUPPORTTYPE_PPI;

// for now all it does is return the platform security support type
struct _AMI_TPM20SUPPORTTYPE_PPI {
    GET_TCG_SUPPORT_TYPE                Tpm20SupportType;
};

#ifdef __cplusplus
}
#endif
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
