//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1987-2013, American Megatrends, Inc.            **
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
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/Haswell/AMI Cpu PKG/AMI TXT DXE/AmiTxtDxe.h 1     1/17/14 3:45a Crystallee $
//
// $Revision: 1 $
//
// $Date: 1/17/14 3:45a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/Haswell/AMI Cpu PKG/AMI TXT DXE/AmiTxtDxe.h $
// 
// 1     1/17/14 3:45a Crystallee
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Show Txt information in setup->Advanced ->Intel Txt
// Information page.
// 

//**********************************************************************

//<AMI_FHDR_START>
//---------------------------------------------------------------------------
//
// Name:	AmiTxtDxe.h
//
// Description:	AmiTxt Dxe header file.
//
//---------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef __AMI_TXT_DXE_H__
#define __AMI_TXT_DXE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <token.h>
#include <AmiDxeLib.h>
#include "TxtTcgService.h"
#include <Setup.h>
#include <hob.h>
#include <Guid/TxtInfoHob/TxtInfoHob.h>
#include "Include/Protocol/AmiTxtInfo.h"
//#include <Protocol/CpuPlatformPolicy.h>

VOID    CPULib_CpuID(UINT32 CpuIDIndex, UINT32 * RegEAX, UINT32 * RegEBX, 
                UINT32 * RegECX, UINT32 * RegEDX);

typedef struct _ACM_HEADER {
  UINT32 ModuleType; ///< Module type
  UINT32 HeaderLen;  ///< 4 4 Header length (in multiples of four bytes)
  /// (161 for version 0.0)
  ///
  UINT32 HeaderVersion; ///< 8 4 Module format version
  UINT32 ModuleID;      ///< 12 4 Module release identifier
  UINT32 ModuleVendor;  ///< 16 4 Module vendor identifier
  UINT32 Date;          ///< 20 4 Creation date (BCD format:
  /// year.month.day)
  ///
  UINT32 Size;            ///< 24 4 Module size (in multiples of four bytes)
  UINT32 Reserved1;       ///< 28 4 Reserved for future extensions
  UINT32 CodeControl;     ///< 32 4 Authenticated code control flags
  UINT32 ErrorEntryPoint; ///< 36 4 Error response entry point offset (bytes)
  UINT32 GDTLimit;        ///< 40 4 GDT limit (defines last byte of GDT)
  UINT32 GDTBasePtr;      ///< 44 4 GDT base pointer offset (bytes)
  UINT32 SegSel;          ///< 48 4 Segment selector initializer
  UINT32 EntryPoint;      ///< 52 4 Authenticated code entry point offset (bytes)
  UINT32 Reserved2;       ///< 56 64 Reserved for future extensions
  UINT32 KeySize;         ///< 120 4 Module public key size less the exponent
  /// (in multiples of four bytes
  /// - 64 for version 0.0)
  ///
  UINT32 ScratchSize; ///< 124 4 Scratch field size (in multiples of four bytes)
  /// (2 * KeySize + 15 for version 0.0)
  ///
  UINT8 RSAPubKey[65 * 4]; ///< 128 KeySize * 4 + 4 Module public key
  UINT8 RSASig[256];       ///< 388 256 PKCS #1.5 RSA Signature.
} ACM_HEADER;
/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1987-2013, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
