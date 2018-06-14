//****************************************************************************
//****************************************************************************
//**                                                                        **
//**             (C)Copyright 1985-2010, American Megatrends, Inc.          **
//**                                                                        **
//**                          All Rights Reserved.                          **
//**                                                                        **
//**              5555 Oakbrook Pkwy, Suite 200 Norcross, GA 30093          **
//**                                                                        **
//**                          Phone (770)-246-8600                          **
//**                                                                        **
//****************************************************************************
//****************************************************************************

//****************************************************************************
// $Header: /Alaska/SOURCE/Modules/USB/ALASKA/Protocol/Emul6064Trap.h 5     4/04/11 5:34a Ryanchou $
//
// $Revision: 5 $
//
// $Date: 4/04/11 5:34a $
//
//****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/USB/ALASKA/Protocol/Emul6064Trap.h $
// 
// 5     4/04/11 5:34a Ryanchou
// [TAG]  		EIP57534
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	BIOS rom image build process may stopped with error.
// [RootCause]  	Has unnecessary semi-colon (;).
// [Solution]  	Remove the unnecessary semi-colon.
// [Files]  		Emul6064Trap.h
// 
// 4     7/08/10 2:22a Rameshr
// Ohci Emulation support Added.
// EIP 39712
// 
// 3     6/28/10 5:24p Olegi
// EIP22197: Corrected headers/footers.
// 
// 2     2/04/09 12:48p Olegi
// Added NONSMMEMUL6064TRAP definitions.
// 
// 1     12/17/07 2:46p Olegi
//****************************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
//  Name:           Emul6064Trap.h
//
//  Description:    Protocol used for 6064 port trapping
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>


#ifndef _EMUL6064TRAP_PROTOCOL_H_
#define _EMUL6064TRAP_PROTOCOL_H_

EFI_FORWARD_DECLARATION (EFI_EMUL6064TRAP_PROTOCOL);

#define EFI_EMUL6064TRAP_PROTOCOL_GUID \
    { 0x6ea0f71c, 0x614a, 0x437e, 0x8f, 0x49, 0x24, 0x3a, 0xd4, 0xe8, 0x32, 0x68 }

#define EFI_NONSMMEMUL6064TRAP_PROTOCOL_GUID \
    { 0x68b81e51, 0x2583, 0x4582, 0x95, 0xdb, 0xc5, 0x72, 0x32, 0x36, 0xc4, 0xf1 }

#define IRQ_SUPPORTED       0x0001		

typedef
BOOLEAN
(EFIAPI *EFI_EMUL6064TRAP_PROTOCOL_ENABLE) (
  IN EFI_EMUL6064TRAP_PROTOCOL           * This
  );

typedef
BOOLEAN
(EFIAPI *EFI_EMUL6064TRAP_PROTOCOL_DISABLE) (
  IN EFI_EMUL6064TRAP_PROTOCOL           * This
  );

typedef
UINT32
(EFIAPI *EFI_EMUL6064TRAP_PROTOCOL_FEATURE) (
  IN EFI_EMUL6064TRAP_PROTOCOL           * This
  );


typedef struct _EFI_EMUL6064TRAP_PROTOCOL {
    EFI_EMUL6064TRAP_PROTOCOL_ENABLE TrapEnable;
    EFI_EMUL6064TRAP_PROTOCOL_DISABLE TrapDisable;
    EFI_EMUL6064TRAP_PROTOCOL_FEATURE FeatureSupported;
} EFI_EMUL6064TRAP_PROTOCOL;

extern EFI_GUID gEmul6064TrapProtocolGuid;
extern EFI_GUID gNonSmmEmul6064TrapProtocolGuid;

#endif

//****************************************************************************
//****************************************************************************
//**                                                                        **
//**             (C)Copyright 1985-2010, American Megatrends, Inc.          **
//**                                                                        **
//**                          All Rights Reserved.                          **
//**                                                                        **
//**              5555 Oakbrook Pkwy, Suite 200 Norcross, GA 30093          **
//**                                                                        **
//**                          Phone (770)-246-8600                          **
//**                                                                        **
//****************************************************************************
//****************************************************************************
