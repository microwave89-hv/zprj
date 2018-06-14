//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

//*************************************************************************
// $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/SB.ASL 7     7/15/13 3:19a Scottyang $
//
// $Revision: 7 $
//
// $Date: 7/15/13 3:19a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/SB.ASL $
// 
// 7     7/15/13 3:19a Scottyang
// [TAG]  		EIP129089
// [Category]  	Improvement
// [Description]  	Update PCH RC 1.6.1.
// [Files]  		SBDxe.c, SB.asl, ..\ReferenceCode\Chipset\LynxPoint\*.*
// 
// 6     4/24/13 6:00a Scottyang
// [TAG]  		EIP121262
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	WOL BSOD
// [RootCause]  	When resume to OS hardware signal not ready. That made a
// dead loop in OS.
// [Solution]  	Remove while loop and add sychnorized the object in asl
// code.
// [Files]  		SB.asl, PchPcie.asl
// 
// 5     4/08/13 2:51a Wesleychen
// [TAG]           EIP118045
// [Category]      Improvement
// [Description]   Creat tokens to support Power Button Notify
//                 for misc events.
// [Files]         SB.SDL; SB.ASL
// 
// 4     1/11/13 5:10a Scottyang
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Remove EIP105442 temp solution.
// [Files]  		SB.ASL, Pch.asl
// 
// 3     11/26/12 12:39a Scottyang
// [TAG]  		EIP105442
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	After S3 resum cannot use FPT win64
// [RootCause]  	The SPI HSFS register "Access Error Log" bit has been
// set.
// [Solution]  	Clear "Access Error Log" bit after resume.
// [Files]  		SB.ASL, Pch.asl
// 
// 2     8/13/12 10:24a Victortu
// [TAG]           None
// [Category]      Improvement
// [Description]   Update definition in ASL code for building when
// disabled PCI objects.
// [Files]         SB.ASL
// 
// 1     2/08/12 8:24a Yurenlai
// Intel Lynx Point/SB eChipset initially releases.
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:        SB.asl
//
// Description: The ASL file is for South Bridge specific function.
//
//<AMI_FHDR_END>
//*************************************************************************
Scope(\_SB.PCI0.LPCB)
{

    OperationRegion(CPSB, SystemMemory, 0xC0000000, 16)  // Relocatable
    Field(CPSB, AnyAcc, NoLock, Preserve) //Field
    {
        RTCX, 1,
        SBB0, 7,
        SBB1, 8,
        SBB2, 8,
        SBB3, 8,
        SBB4, 8,
        SBB5, 8,
        SBB6, 8,
        SBB7, 8,
        SBB8, 8,
        SBB9, 8,
        SBBA, 8,
        SBBB, 8,
        SBBC, 8,
        SBBD, 8,
        SBBE, 8,
        SBBF, 8,
	}

/*
;<AMI_PHDR_START>
;------------------------------------------------------------------------
;
; Procedure:    SPTS
; Description:  METHOD IS CALLED BY OS PRIOR TO ENTER ANY SLEEP STATE
; Input: Arg0 = Arg0 = Sleep state System about to enter
; Output: Nothing
;
;-------------------------------------------------------------------------
;<AMI_PHDR_END>
*/
    Method (SPTS, 1) {
        Store(One, SLPX)        // Clear SLP_SMI Status
        Store(One, SLPE)        // Enable SLP_SMI

#if defined(ASL_RC_PORT_0) && (ASL_RC_PORT_0==1)
        Store(Zero, \_SB.PCI0.RP01.RPAV)
#endif
#if defined(ASL_RC_PORT_1) && (ASL_RC_PORT_1==1)
        Store(Zero, \_SB.PCI0.RP02.RPAV)
#endif
#if defined(ASL_RC_PORT_2) && (ASL_RC_PORT_2==1)
        Store(Zero, \_SB.PCI0.RP03.RPAV)
#endif
#if defined(ASL_RC_PORT_3) && (ASL_RC_PORT_3==1)
        Store(Zero, \_SB.PCI0.RP04.RPAV)
#endif
#if defined(ASL_RC_PORT_4) && (ASL_RC_PORT_4==1)
        Store(Zero, \_SB.PCI0.RP05.RPAV)
#endif
#if defined(ASL_RC_PORT_5) && (ASL_RC_PORT_5==1)
        Store(Zero, \_SB.PCI0.RP06.RPAV)
#endif
#if defined(ASL_RC_PORT_6) && (ASL_RC_PORT_6==1)
        Store(Zero, \_SB.PCI0.RP07.RPAV)
#endif
#if defined(ASL_RC_PORT_7) && (ASL_RC_PORT_7==1)
        Store(Zero, \_SB.PCI0.RP08.RPAV)
#endif
    }

/*
;<AMI_PHDR_START>
;------------------------------------------------------------------------
;
; Procedure:    SWAK
; Description:  METHOD CALLED ON WAKE UP FROM ANY SLEEP STATE
; Input: Arg0 = Sleep state System is resuming from
; Output: Nothing
;
;------------------------------------------------------------------------
;<AMI_PHDR_END>
*/
    Method (SWAK, 1) {
        Store(Zero, SLPE)       // Disable SLP_SMI
#if defined ASL_SX_NOTIFY_PWRB && ASL_SX_NOTIFY_PWRB == 1
        If (RTCS) {}
             Else {Notify(\_SB.PWRB, 0x02)}
#endif
    }

    OperationRegion (SMIE, SystemIO, PMBS, 4)
    Field (SMIE, ByteAcc,NoLock,Preserve) {
        ,10,
        RTCS, 1,
        , 3,
        PEXS, 1,
        WAKS, 1,
        , 8,
        PWBT, 1,
        , 7,
    }

    OperationRegion (SLPR, SystemIO, SMCR, 8)
    Field (SLPR, ByteAcc,NoLock,Preserve) {
        , 4,
        SLPE,1,
        ,31,
        SLPX,1,
        ,27,
    }
}//Scope(\_SB.PCI0.LPCB)

#if defined (ASL_RC_PORT_0) && (ASL_RC_PORT_0==1)
Scope(\_SB.PCI0.RP01)
{
  //
  // Pass LTRx to LTRE so PchPcie.asl can be reused for PCIes.
  //
  Method(_INI)
  {
    Store (LTR1, LTRE)
    Store (PML1, LMSL)
    Store (PNL1, LNSL)
    Store (OBF1, OBFF)
  }
  Method(_PRW, 0) { Return(GPRW(0x09, 4)) }
}//Scope(\_SB.PCI0.RP01)
#endif

#if defined (ASL_RC_PORT_1) && (ASL_RC_PORT_1==1)
Scope(\_SB.PCI0.RP02)
{
  //
  // Pass LTRx to LTRE so PchPcie.asl can be reused for PCIes.
  //
  Method(_INI)
  {
    Store (LTR2, LTRE)
    Store (PML2, LMSL)
    Store (PNL2, LNSL)
    Store (OBF2, OBFF)
  }
  Method(_PRW, 0) { Return(GPRW(0x09, 4)) }
}//Scope(\_SB.PCI0.RP02)
#endif

#if defined (ASL_RC_PORT_2) && (ASL_RC_PORT_2==1)
Scope(\_SB.PCI0.RP03)
{
  //
  // Pass LTRx to LTRE so PchPcie.asl can be reused for PCIes.
  //
  Method(_INI)
  {
    Store (LTR3, LTRE)
    Store (PML3, LMSL)
    Store (PNL3, LNSL)
    Store (OBF3, OBFF)
  }
  Method(_PRW, 0) { Return(GPRW(0x09, 4)) }
}//Scope(\_SB.PCI0.RP03)
#endif

#if defined (ASL_RC_PORT_3) && (ASL_RC_PORT_3==1)
Scope(\_SB.PCI0.RP04)
{
  //
  // Pass LTRx to LTRE so PchPcie.asl can be reused for PCIes.
  //
  Method(_INI)
  {
    Store (LTR4, LTRE)
    Store (PML4, LMSL)
    Store (PNL4, LNSL)
    Store (OBF4, OBFF)
  }
  Method(_PRW, 0) { Return(GPRW(0x09, 4)) }
}//Scope(\_SB.PCI0.RP04)
#endif

#if defined (ASL_RC_PORT_4) && (ASL_RC_PORT_4==1)
Scope(\_SB.PCI0.RP05)
{
  //
  // Pass LTRx to LTRE so PchPcie.asl can be reused for PCIes.
  //
  Method(_INI)
  {
    Store (LTR5, LTRE)
    Store (PML5, LMSL)
    Store (PNL5, LNSL)
    Store (OBF5, OBFF)
  }
  Method(_PRW, 0) { Return(GPRW(0x09, 4)) }
}//Scope(\_SB.PCI0.RP05)
#endif

#if defined (ASL_RC_PORT_5) && (ASL_RC_PORT_5==1)
Scope(\_SB.PCI0.RP06)
{
  //
  // Pass LTRx to LTRE so PchPcie.asl can be reused for PCIes.
  //
  Method(_INI)
  {
    Store (LTR6, LTRE)
    Store (PML6, LMSL)
    Store (PNL6, LNSL)
    Store (OBF6, OBFF)
  }
  Method(_PRW, 0) { Return(GPRW(0x09, 4)) }
}//Scope(\_SB.PCI0.RP06)
#endif

#if defined (ASL_RC_PORT_6) && (ASL_RC_PORT_6==1)
Scope(\_SB.PCI0.RP07)
{
  //
  // Pass LTRx to LTRE so PchPcie.asl can be reused for PCIes.
  //
  Method(_INI)
  {
    Store (LTR7, LTRE)
    Store (PML7, LMSL)
    Store (PNL7, LNSL)
    Store (OBF7, OBFF)
  }
  Method(_PRW, 0) { Return(GPRW(0x09, 4)) }
}//Scope(\_SB.PCI0.RP07)
#endif

#if defined (ASL_RC_PORT_7) && (ASL_RC_PORT_7==1)
Scope(\_SB.PCI0.RP08)
{
  //
  // Pass LTRx to LTRE so PchPcie.asl can be reused for PCIes.
  //
  Method(_INI)
  {
    Store (LTR8, LTRE)
    Store (PML8, LMSL)
    Store (PNL8, LNSL)
    Store (OBF8, OBFF)
  }
  Method(_PRW, 0) { Return(GPRW(0x09, 4)) }
}//Scope(\_SB.PCI0.RP08)
#endif
//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
