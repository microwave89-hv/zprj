//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.            **
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
//
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/MeWrapper/MeSetup/NfcSupportDxe/NfcSupportDxe.h 1     11/02/14 9:43p Tristinchou $
//
// $Revision: 1 $
//
// $Date: 11/02/14 9:43p $
//
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/MeWrapper/MeSetup/NfcSupportDxe/NfcSupportDxe.h $
// 
// 1     11/02/14 9:43p Tristinchou
// [TAG]  		EIP189985
// [Category]  	Improvement
// [Description]  	For ME 9.1.20.1035, add NFC related option in setup
// [Files]  		NfcSupportDxe.cif
// NfcSupportDxe.c
// NfcSupportDxe.h
// NfcSupportDxe.sdl
// NfcSupportDxe.dxs
// NfcSupportDxe.mak
// 
//
//**********************************************************************
#ifndef _NfcSupportDxe_H_
#define _NfcSupportDxe_H_

#pragma pack(push, 1)
typedef struct {
  BOOLEAN       NFCCapability;
  BOOLEAN       NFCState;
  UINT8         NFCDeviceType;
  UINT8         MeSupportNFC;
  UINT8         NFCEnable;
  UINT8         NFCEnableUpdate;
} NFC_SUPPORT_DATA;
#pragma pack(pop)

//1E5ACFFE-ED4C-4BC0-AE51-511EFDA0522E
#define NFC_SUPPORT_DATA_GUID \
  {0x1E5ACFFE, 0xED4C, 0x4BC0, 0xAE, 0x51, 0x51, 0x1E, 0xFD, 0xA0, 0x52, 0x2E}

#endif
//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************