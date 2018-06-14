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
// $Header: /Alaska/SOURCE/Modules/KbcEmulation/ALASKA/KBCEMUL/Ap4x.h 7     1/06/12 3:50a Rameshr $
//
// $Revision: 7 $
//
// $Date: 1/06/12 3:50a $
//
//****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/KbcEmulation/ALASKA/KBCEMUL/Ap4x.h $
// 
// 7     1/06/12 3:50a Rameshr
// [TAG]  		EIP78617
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	When KBCEmulation is enabled during OS runtime phase,
// system reboots
// [RootCause]  	if the SMI happens from AP, Kbcemulation driver unable to
// handle it.
// [Solution]  	Added logic in KbcCore.c to find the CPU that cause SMI
// and access the corresponding AL register.
// [Files]  		Ap4x.h, KbcCore.c
// 
// 6     1/06/12 3:21a Rameshr
// EIP78617 check-in removed.
// 
// 4     4/11/11 2:56a Rameshr
// [TAG]- EIP 57436
// [Category]-IMPROVEMENT
// [Description]- PI1.1 Support.
// [Files]- Ap4x.h, KbcEmul.c
// 
// 3     2/10/11 1:09a Rameshr
// [TAG]  		EIP53687
// [Category]  	Improvement
// [Description]  	AMI headers update for KbcEmulation Module 
// 
// [Files]  		KbcEmul.mak,KbcEmul.dxs,KbcEmul.c,KbcEmul.h,KbcEmulLib.h,Kbc
// EmulLib.c,Kbc.h,KbcDevEmul.h,Kbccore.c,Legacykbc.c,Legacykbd.c,LegacyMo
// use.c,VirtualKbc.c,VirtualKbd.c,VirtualMouse.c,Ap4x.h,Ap4x.c,KbcUhci.c,
// KbcUhci.h,KbcEmulIrq.c, KbcOhci.c, Kbcohci.h
// 
// 2     6/30/09 11:32a Rameshr
// Coding Standard and File header updated.
// 
// 1     12/14/07 10:26a Rameshraju
// Initial Check-in
//****************************************************************************

//<AMI_FHDR_START>
//****************************************************************************
// Name:        Ap4x.h
//
// Description: It has the Aptio4.x compatibility include files and headers
//
//****************************************************************************
//<AMI_FHDR_END>
#include <efi.h>
#include <AmiDxeLib.h>

#include <Protocol\SmmBase.h>
#include <Protocol\SmmUsbDispatch.h>
#include <Protocol\LoadedImage.h>
#include <Protocol\Emul6064MsInput.h>
#include <Protocol\Emul6064KbdInput.h>
#include <Protocol\Emul6064Trap.h>

extern EFI_GUID gEfiSmmUsbDispatchProtocolGuid;

#define EFI_DRIVER_ENTRY_POINT(x)


#define EfiInitializeSmmDriverLib(ImageHandle, SystemTable) InitAmiLib(ImageHandle, SystemTable)
#define EfiInitializeDriverLib(ImageHandle, SystemTable) InitAmiLib(ImageHandle,SystemTable)
#define gBS                                 pBS
#define gRT                                 pRS
#define EfiDuplicateDevicePath              DPCopy
#define AppendDevicePath                    DPAdd
#define dp_len(x)                           (x)
#define GET_CPUSAVESTATE_REG(x, y)             gSmst->CpuSaveState[x].Ia32SaveState.y

extern  EFI_SMM_BASE_PROTOCOL*               gSMM;
#define _CR(Record, TYPE, Field)  ((TYPE *) ((CHAR8 *) (Record) - (CHAR8 *) &(((TYPE *) 0)->Field)))

#define VA_LIST     va_list
#define VA_START    va_start
#define VA_ARG      va_arg
#define VA_END      va_end
#define EfiDebugVPrint(EFI_D_ERROR, Message, ArgList) PrintDebugMessageVaList(-1, Message, ArgList)

#define USBDEVPATH_END  0xFF, 0xFF

#ifdef TRACE
#undef TRACE
#endif

#ifdef EFI_DEBUG
void    PrintDebugMsg (char *, ...);
#define TRACE   PrintDebugMsg
#else
void    PrintDebugMsg (char *, ...);
#define TRACE       1?0:PrintDebugMsg
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
