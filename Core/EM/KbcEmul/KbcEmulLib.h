//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/KbcEmulation/ALASKA/KBCEMUL/KbcEmulLib.h 4     2/10/11 12:59a Rameshr $
//
// $Revision: 4 $
//
// $Date: 2/10/11 12:59a $
//
//****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/KbcEmulation/ALASKA/KBCEMUL/KbcEmulLib.h $
// 
// 4     2/10/11 12:59a Rameshr
// [TAG]  		EIP53687
// [Category]  	Improvement
// [Description]  	AMI headers update for KbcEmulation Module 
// [Files]  		KbcEmul.mak,KbcEmul.dxs,KbcEmul.c,KbcEmul.h,KbcEmulLib.h,Kbc
// EmulLib.c,Kbc.h,KbcDevEmul.h,Kbccore.c,Legacykbc.c,Legacykbd.c,LegacyMo
// use.c,VirtualKbc.c,VirtualKbd.c,VirtualMouse.c,Ap4x.h,Ap4x.c,KbcUhci.c,
// KbcUhci.h,KbcEmulIrq.c, KbcOhci.c, Kbcohci.h
// 
// 3     6/30/09 11:29a Rameshr
// Coding Standard and File header updated.
// 
// 2     2/05/09 9:41a Rameshr
// Symptom : With Latest CSM Emulation doesn't work.
// Solution: Added Emulation enable code in outside SMM. This is called
// from Uhcd.c when ever USB mode changes to Legacy
// EIP:18730
// 
// 1     12/14/07 10:26a Rameshraju
// Initial Check-in
//****************************************************************************

//<AMI_FHDR_START>
//**********************************************************************
// Name:        KbcEmullib.h
//
// Description:	KBC emulation Lib header file used in other files
//
//**********************************************************************
//<AMI_FHDR_END>

#ifndef _EMUL6064LIB_H_INC_

UINT8       ByteReadIO(UINT16 wIOAddr);
void        ByteWriteIO (UINT16 wIOAddr, UINT8 bValue);
UINT16      WordReadIO(UINT16 wIOAddr);
void        WordWriteIO (UINT16 wIOAddr, UINT16 wValue);
UINT32      DwordReadIO(UINT16 wIOAddr);
void        DwordWriteIO(UINT16 wIOAddr, UINT32 dValue);
UINT32      ReadPCIConfig(UINT16 BusDevFunc, UINT8 Register);
void        ByteWritePCIConfig(UINT16 BusDevFunc, UINT8 Register, UINT8 Value);
void        WordWritePCIConfig(UINT16 BusDevFunc, UINT8 Register, UINT16 Value);
void        DwordWritePCIConfig(UINT16 BusDevFunc, UINT8 Register, UINT32 Value);
UINT32      ReadPCIConfig(UINT16 BusDevFunc, UINT8 Register);

UINT8       NonSmmByteReadIO(UINT16 wIOAddr);
void        NonSmmByteWriteIO (UINT16 wIOAddr, UINT8 bValue);
UINT16      NonSmmWordReadIO(UINT16 wIOAddr);
void        NonSmmWordWriteIO (UINT16 wIOAddr, UINT16 wValue);
UINT32      NonSmmDwordReadIO(UINT16 wIOAddr);
void        NonSmmDwordWriteIO(UINT16 wIOAddr, UINT32 dValue);
UINT32      NonSmmReadPCIConfig(UINT16 BusDevFunc, UINT8 Register);
void        NonSmmByteWritePCIConfig(UINT16 BusDevFunc, UINT8 Register, UINT8 Value);
void        NonSmmWordWritePCIConfig(UINT16 BusDevFunc, UINT8 Register, UINT16 Value);
void        NonSmmDwordWritePCIConfig(UINT16 BusDevFunc, UINT8 Register, UINT32 Value);
UINT32      NonSmmReadPCIConfig(UINT16 BusDevFunc, UINT8 Register);

#endif

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************