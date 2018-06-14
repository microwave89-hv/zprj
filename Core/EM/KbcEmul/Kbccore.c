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
// $Header: /Alaska/SOURCE/Modules/KbcEmulation/ALASKA/KBCEMUL/Kbccore.c 9     1/09/12 1:30a Rameshr $
//
// $Revision: 9 $
//
// $Date: 1/09/12 1:30a $
//
//****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/KbcEmulation/ALASKA/KBCEMUL/Kbccore.c $
// 
// 9     1/09/12 1:30a Rameshr
// [TAG]  		EIP74128
// [Category]  	Improvement
// [Description]  	Disable the KbcEmulation Smi’s on ACPI enable and
// Disable SMI call
// [Files]  		Kbccore.c, KbcEmuulAcpi.c, KbcEmul.c, KbcEmul.cif,
// KbcEmul.h, KbcEmul.sdl
// 
// 8     1/06/12 3:51a Rameshr
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
// 7     1/06/12 3:21a Rameshr
// EIP78617 check-in removed.
// 
// 5     2/10/11 1:02a Rameshr
// [TAG]  		EIP53687
// [Category]  	Improvement
// [Description]  	AMI headers update for KbcEmulation Module 
// [Files]  		KbcEmul.mak,KbcEmul.dxs,KbcEmul.c,KbcEmul.h,KbcEmulLib.h,Kbc
// EmulLib.c,Kbc.h,KbcDevEmul.h,Kbccore.c,Legacykbc.c,Legacykbd.c,LegacyMo
// use.c,VirtualKbc.c,VirtualKbd.c,VirtualMouse.c,Ap4x.h,Ap4x.c,KbcUhci.c,
// KbcUhci.h,KbcEmulIrq.c, KbcOhci.c, Kbcohci.h
// 
// 4     7/08/10 1:56a Rameshr
// Ohci Emulation support Added.
// EIP 39712
// 
// 3     6/30/09 11:30a Rameshr
// Coding Standard and File header updated.
// 
// 2     2/05/09 9:35a Rameshr
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
//
// Name:        Kbccore.c
//
// Description: It has function for port 60 read, 60 write, 64 read and 64 write
//
//**********************************************************************
//<AMI_FHDR_END>

#include "KbcEmul.h"
#include "kbc.h"
#if UHCI_EMUL_SUPPORT
#include "KbcUhci.h"
#else 
#include "KbcOhci.h"
#endif

BOOLEAN         AcpiEmulationDisable=FALSE;
extern KBC*     gVirtualKBC;

#define SYNC_SMI_BIT  (1 << 0)

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   FindSMICpu
//
// Description: In a Multiprocessor environment, any logical CPU can generate
//              the SMI. This function finds the CPU that generates SMI by accessing
//              IO 60/64 Ports
//
// Input:       None
//
// Output:      UINT8 CpuIndex
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8 FindSMICpu ( ) {
  UINT8                   CpuIndex;
  UINT32                  SmmIoMiscInfo;
  UINT16                  IOAddress;
  UINT32                  Smbase=0;

  for (CpuIndex = 0; CpuIndex < gSmst->NumberOfCpus; CpuIndex++) {
    //
    // Find which CPU caused the SMI
    //    
    Smbase = gSmst->CpuSaveState[CpuIndex].Ia32SaveState.SMBASE;
    SmmIoMiscInfo = *(UINT32 *) (((UINT8 *) (UINTN) Smbase) + 0x8000 + 0x7FA4);
    IOAddress =     SmmIoMiscInfo >> 16;
    if (((IOAddress == 0x60) || (IOAddress == 0x64)) && (SmmIoMiscInfo & SYNC_SMI_BIT)) {
      return CpuIndex;
    }
  }

  return 0xFF;  
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   getTrapAL
//
// Description: Get the port 60 or 64 input value from the CPU save reg
//
// Input:       None
//
// Output:      UINT8 Value
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8 GetTrapAL()
{

#if UHCI_EMUL_SUPPORT	
	UINT8   CpuIndex;

	CpuIndex = FindSMICpu ();
	ASSERT (CpuIndex != 0xFF);
	return (UINT8)GET_CPUSAVESTATE_REG(CpuIndex, EAX);
#else
	return GetHceInput();
#endif

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   setTrapAL
//
// Description: Set the port 60 or 64 output value to the CPU save reg
//
// Input:       UINT8 Data
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
void SetTrapAL(UINT8 data)
{

#if UHCI_EMUL_SUPPORT
    UINT8   CpuIndex;

    CpuIndex = FindSMICpu();
    ASSERT (CpuIndex != 0xFF);
    *(UINT8*)&GET_CPUSAVESTATE_REG(CpuIndex, EAX) = data;
#endif

}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   trap64w
//
// Description: This function handles the Port64 write command
//
// Input:       None
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

void trap64w()
{
    (*gVirtualKBC->kbc_write_command)( gVirtualKBC,GetTrapAL() );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   setTrapAL
//
// Description: This function handles the Port60 write command
//
// Input:       None
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
void trap60w()
{
    (*gVirtualKBC->kbc_write_data)( gVirtualKBC,GetTrapAL() );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   setTrapAL
//
// Description: This function handles the Port64 Read command
//
// Input:       None
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
void trap64r()
{
    SetTrapAL((*gVirtualKBC->kbc_read_status)(gVirtualKBC));
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   setTrapAL
//
// Description: This function handles the Port60 Read command
//
// Input:       None
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
void trap60r()
{
    SetTrapAL((*gVirtualKBC->kbc_read_data)(gVirtualKBC));
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   hasTrapStatus
//
// Description: return the port 6064 trap status
//
// Input:       None
//
// Output:      TRUE: Trab enabled for port 6064
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN hasTrapStatus()
{
    BOOLEAN     TrapStatus=FALSE;
#if UHCI_EMUL_SUPPORT
    TrapStatus=Uhci_HasTrapStatus();
#endif
#if OHCI_EMUL_SUPPORT
    TrapStatus=Ohci_HasTrapStatus();
#endif
    return TrapStatus;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   TrapEnable
//
// Description: Enable/disable the port6064 trap
//
// Input:       TRUE : enable the trap.
//              FALSE: Disable the trap.
//
// Output:      TRUE : when suucessfully done else FALSE
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN TrapEnable(BOOLEAN b)
{

    if(AcpiEmulationDisable) {
        return FALSE;
    }

#if UHCI_EMUL_SUPPORT
    return Uhci_TrapEnable(b);
#endif
#if OHCI_EMUL_SUPPORT
    return Ohci_TrapEnable(b);
#endif
	return TRUE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   NonSmmTrapEnable
//
// Description: Enable/disable the port6064 trap in Non SMM 
//
// Input:       TRUE : enable the trap.
//              FALSE: Disable the trap.
//
// Output:      TRUE/FALSE
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN NonSmmTrapEnable(BOOLEAN b)
{
#if UHCI_EMUL_SUPPORT
    return NonSmmUhci_TrapEnable(b);
#endif
#if OHCI_EMUL_SUPPORT
    return NonSmmOhci_TrapEnable(b);
#endif
	return TRUE;
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