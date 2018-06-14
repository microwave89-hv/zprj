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
// $Header: /Alaska/SOURCE/Modules/KbcEmulation/ALASKA/KBCEMUL/KbcEmulIrq.c 5     2/10/11 1:13a Rameshr $
//
// $Revision: 5 $
//
// $Date: 2/10/11 1:13a $
//
//****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/KbcEmulation/ALASKA/KBCEMUL/KbcEmulIrq.c $
// 
// 5     2/10/11 1:13a Rameshr
// [TAG]  		EIP53687
// [Category]  	Improvement
// [Description]  	AMI headers update for KbcEmulation Module
// [Files]  		KbcEmul.mak,KbcEmul.dxs,KbcEmul.c,KbcEmul.h,KbcEmulLib.h,Kbc
// EmulLib.c,Kbc.h,KbcDevEmul.h,Kbccore.c,Legacykbc.c,Legacykbd.c,LegacyMo
// use.c,VirtualKbc.c,VirtualKbd.c,VirtualMouse.c,Ap4x.h,Ap4x.c,KbcUhci.c,
// KbcUhci.h,KbcEmulIrq.c, KbcOhci.c, Kbcohci.h
// 
// 4     7/08/10 2:00a Rameshr
// Ohci Emulation support Added.
// EIP 39712
// 
// 3     6/30/09 11:37a Rameshr
// Coding Standard and File header updated.
// 
// 2     8/07/08 10:20a Rameshraju
// IRQ1 enabled before generating IRQ1
// 
// 1     12/14/07 10:26a Rameshraju
// Initial Check-in
//****************************************************************************

//<AMI_FHDR_START>
//****************************************************************************
// Name:        KbcEmulIrq.c
//
// Description: Handles the IRQ1 and IRQ12 generation
//
//****************************************************************************
//<AMI_FHDR_END>

#ifdef FRAMEWORK_AP4
#include "token.h"
#else
#include "tokens.h"
#endif
#include "KbcEmul.h"
#include "KbcEmulLib.h"
#include "KbcDevEmul.h"
#if OHCI_EMUL_SUPPORT
#include "KbcOhci.h"
#endif

VOID GenerateIRQ12(VIRTKBC*);
VOID GenerateIRQ1(VIRTKBC*);

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GenerateIRQ12
//
// Description: Generate IRQ1
//
// Input:       None
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
GenerateIRQ12(VIRTKBC* vkbc)
{

#if UHCI_EMUL_SUPPORT
    UINT8       Value8;

    Value8=ByteReadIO(SW_IRQ_GENERATION_REG);
    ByteWriteIO(SW_IRQ_GENERATION_REG, 0);
    ByteWriteIO(SW_IRQ_GENERATION_REG,  2);
    return;

#else

    if (GetHceStatus() & HCE_STS_OUTPUTFULL ){
        SetHceControl((GetHceControl() | HCE_CNTRL_IRQ_ENABLE));  
    } else {
        SetHceStatus((GetHceStatus() | HCE_STS_OUTPUTFULL | HCE_STS_AUXOUTPUTFULL));
        SetHceControl((GetHceControl() | HCE_CNTRL_IRQ_ENABLE));  
    }
    return;
#endif

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GenerateIRQ1
//
// Description: Generate IRQ1
//
// Input:       None
//
// Output:      None    
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
GenerateIRQ1(VIRTKBC* vkbc)
{

#if UHCI_EMUL_SUPPORT
    UINT8       Value8;
    UINT8       IrqMask;

    //
    //Enable IRQ1 before generating the IRQ1.
    //
    IrqMask = ByteReadIO(0x21);
    if (IrqMask & 0x02) {
      IrqMask &= 0xFD;
      ByteWriteIO (0x21, IrqMask);
    }

    Value8=ByteReadIO(SW_IRQ_GENERATION_REG);
    ByteWriteIO(SW_IRQ_GENERATION_REG, 0);
    ByteWriteIO(SW_IRQ_GENERATION_REG,  1);
    return;

#else
    UINT8       IrqMask;
    //
    //Enable IRQ1 before generating the IRQ1.
    //
    IrqMask = ByteReadIO(0x21);
    if (IrqMask & 0x02) {
      IrqMask &= 0xFD;
      ByteWriteIO (0x21, IrqMask);
    }

    if (GetHceStatus() & HCE_STS_OUTPUTFULL ){
        SetHceControl((GetHceControl() | HCE_CNTRL_IRQ_ENABLE));  
    } else {
        vkbc->st_ |= KBC_STATUS_OBF;
        SetHceStatus((GetHceStatus() | KBC_STATUS_OBF));  
        SetHceControl((GetHceControl() | HCE_CNTRL_IRQ_ENABLE));  
    }
    return;
#endif

}

//****************************************************************************
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
