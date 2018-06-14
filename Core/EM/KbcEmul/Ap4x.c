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
// $Header: /Alaska/SOURCE/Modules/KbcEmulation/ALASKA/KBCEMUL/Ap4x.c 3     2/10/11 1:09a Rameshr $
//
// $Revision: 3 $
//
// $Date: 2/10/11 1:09a $
//
//****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/KbcEmulation/ALASKA/KBCEMUL/Ap4x.c $
// 
// 3     2/10/11 1:09a Rameshr
// [TAG]  		EIP53687
// [Category]  	Improvement
// [Description]  	AMI headers update for KbcEmulation Module 
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
// Name:        Ap4x.c
//
// Description: It has the Aptio4.x compatibility function
//
//****************************************************************************
//<AMI_FHDR_END>

#include "KbcEmul.h"

EFI_SMM_CPU_IO_INTERFACE*       gCpuIo = 0;
EFI_SMM_BASE_PROTOCOL*          gSMM = 0;
EFI_SMM_SYSTEM_TABLE*               gSmst = 0;

extern EFI_GUID gEfiSmmBaseProtocolGuid;

initializeLib(IN EFI_HANDLE ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable)
{

    EfiInitializeSmmDriverLib (ImageHandle, SystemTable);

    gBS->LocateProtocol (&gEfiSmmBaseProtocolGuid, NULL, &gSMM);
    gSMM->GetSmstLocation (gSMM, &gSmst);
    gCpuIo = &gSmst->SmmIo;
}

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