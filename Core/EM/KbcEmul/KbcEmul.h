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
// $Header: /Alaska/SOURCE/Modules/KbcEmulation/ALASKA/KBCEMUL/KbcEmul.h 6     1/09/12 1:25a Rameshr $
//
// $Revision: 6 $
//
// $Date: 1/09/12 1:25a $
//
//****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/KbcEmulation/ALASKA/KBCEMUL/KbcEmul.h $
// 
// 6     1/09/12 1:25a Rameshr
// [TAG]  		EIP74128
// [Category]  	Improvement
// [Description]  	Disable the KbcEmulation Smi’s on ACPI enable and
// Disable SMI call
// [Files]  		Kbccore.c, KbcEmuulAcpi.c, KbcEmul.c, KbcEmul.cif,
// KbcEmul.h, KbcEmul.sdl
// 
// 5     2/10/11 12:58a Rameshr
// [TAG]  		EIP53687
// [Category]  	Improvement
// [Description]  	AMI headers update for KbcEmulation Module 
// [Files]  		KbcEmul.mak,KbcEmul.dxs,KbcEmul.c,KbcEmul.h,KbcEmulLib.h,Kbc
// EmulLib.c,Kbc.h,KbcDevEmul.h,Kbccore.c,Legacykbc.c,Legacykbd.c,LegacyMo
// use.c,VirtualKbc.c,VirtualKbd.c,VirtualMouse.c,Ap4x.h,Ap4x.c,KbcUhci.c,
// KbcUhci.h,KbcEmulIrq.c, KbcOhci.c, Kbcohci.h
// 
// 4     7/08/10 1:57a Rameshr
// Ohci Emulation support Added.
// EIP 39712
// 
// 3     6/30/09 11:28a Rameshr
// Coding Standard and File header updated.
// 
// 2     2/05/09 9:38a Rameshr
// Symptom : With Latest CSM Emulation doesn't work.
// Solution: Added Emulation enable code in outside SMM. This is called
// from Uhcd.c when ever USB mode changes to Legacy
// EIP:18730
// 
// 1     12/14/07 10:26a Rameshraju
// Initial Check-in
//****************************************************************************

//<AMI_FHDR_START>
//****************************************************************************
// Name:   KbcEmul.h
//
// Description: KBC emulation header file
//****************************************************************************
//<AMI_FHDR_END>

#ifdef FRAMEWORK_AP4
#include "Ap4x.h"
#include "token.h"
#else
#include "Ap3x.h"
#include "tokens.h"
#endif

#include <protocol\devicepath.h>
#include <Protocol\Cpuio.h>

initializeLib(IN EFI_HANDLE ImageHandle,
                            IN EFI_SYSTEM_TABLE *SystemTable);


#define  MAX_DEBUG_LEVEL        8

#define DEBUG_LEVEL_8           8
#define DEBUG_LEVEL_7           7
#define DEBUG_LEVEL_6           6
#define DEBUG_LEVEL_5           5
#define DEBUG_LEVEL_4           4
#define DEBUG_LEVEL_3           3
#define DEBUG_LEVEL_2           2
#define DEBUG_LEVEL_1           1
#define DEBUG_LEVEL_0           0


typedef struct _HC_DEV_STRUC {
    UINT16          wPCIDev;
    UINT16          wHCType;
} HC_DEV_STRUC;

extern EFI_SMM_SYSTEM_TABLE *gSmst;
extern EFI_CPU_IO_PROTOCOL *CpuIo;

//
//Checks if Trap status is set
//
BOOLEAN     hasTrapStatus();
BOOLEAN     TrapEnable(BOOLEAN );
BOOLEAN     NonSmmTrapEnable(BOOLEAN );

#if OHCI_EMUL_SUPPORT == 1
void    SetHceOutput (UINT8);
#endif

EFI_STATUS
RegisterAcpiEnableCallBack();

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
