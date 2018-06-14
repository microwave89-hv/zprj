;*************************************************************************
;*************************************************************************
;**                                                                     **
;**        (C)Copyright 1985-2009, American Megatrends, Inc.            **
;**                                                                     **
;**                       All Rights Reserved.                          **
;**                                                                     **
;**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
;**                                                                     **
;**                       Phone: (770)-246-8600                         **
;**                                                                     **
;*************************************************************************
;*************************************************************************

;**********************************************************************
; $Header: /Alaska/SOURCE/Modules/SMM/SMMDispatcher/SmmDispatcherAsm.asm 4     10/03/11 2:53p Markw $
;
; $Revision: 4 $
;
; $Date: 10/03/11 2:53p $
;**********************************************************************
; Revision History
; ----------------
; $Log: /Alaska/SOURCE/Modules/SMM/SMMDispatcher/SmmDispatcherAsm.asm $
; 
; 4     10/03/11 2:53p Markw
; Add SMM Machine Check handler.
; Files: SmmDispatcher.c, SmmDispatcherAsm.asm
; 
; 3     7/08/09 8:18p Markw
; Update headers.
; 
; 2     11/21/08 5:00p Markw
; Add LockInc32 and LockDec32.
; 
; 1     6/09/08 5:56p Markw
; Assembly functions for Dispatcher.
; 
;**********************************************************************

;<AMI_FHDR_START>
;----------------------------------------------------------------------------
;
; Name:		SmmDispatcher.asm
;
; Description:	File that contains assembly for Smm Dispatcher.
;
;----------------------------------------------------------------------------
;<AMI_FHDR_END>

IFDEF EFIx64
.code
include token.equ

;<AMI_PHDR_START>
;----------------------------------------------------------------------------
;
; Procedure:	Xchg8
;
; Description:	Exchange a value with a pointer and return the exchanged value.
;
; Input:
;   IN OUT volatile UINT8 *     Pointer to value to exchange.
;   IN UINT8                    Value to exchange.
;
; Output:	UINT8   Exchanged Value
;
; Modified:	Nothing
;
;----------------------------------------------------------------------------
;<AMI_PHDR_END>
Xchg8 proc public
    xchg    dl, [rcx]
    mov     al, dl
    ret
Xchg8 endp

;<AMI_PHDR_START>
;---------------------------------------------------------------------------
;
; Procedure: LockInc32
;
; Description: Increment value at pointer locking address.
;
; Input: IN OUT UINT32 *ptr
;
; Output: None
;---------------------------------------------------------------------------
;<AMI_PHDR_END>

LockInc32 proc public
  	lock inc dword ptr [rcx]
	ret
LockInc32 endp

;<AMI_PHDR_START>
;---------------------------------------------------------------------------
;
; Procedure: LockDec32
;
; Description: Decrement value at pointer locking address.
;
; Input: IN OUT UINT32 *ptr
;
; Output: None
;---------------------------------------------------------------------------
;<AMI_PHDR_END>

LockDec32 proc public
	lock dec dword ptr [rcx]
	ret
LockDec32 endp

;<AMI_PHDR_START>
;---------------------------------------------------------------------------
;
; Procedure: MachineCheckHandler
;
; Description: SMM Machine Check Handler
;
; Input: VOID
;
; Output: VOID
;---------------------------------------------------------------------------
;<AMI_PHDR_END>

MachineCheckHandler proc public
    push rax
    push rcx
    push rdx
    mov ecx, 17ah   ;IA32_MCG_STATUS
    rdmsr
    btr eax, 2      ;MCIP
    wrmsr
    pop rdx
    pop rcx
    pop rax
	iretq
MachineCheckHandler endp

ELSE    ;32-bits
.586p
.model small
.code

_Xchg8 proc public
    mov al, [esp + 8]
    mov edx, [esp + 4]
    xchg al, [edx]
    ret
_Xchg8 endp

_LockInc32 proc public
    mov eax, [esp + 4] 
  	lock inc dword ptr [eax]
	ret
_LockInc32 endp


_LockDec32 proc public
    mov	eax, [esp + 4]
	lock dec dword ptr [eax]
	ret
_LockDec32 endp

_MachineCheckHandler proc public
    push eax
    push ecx
    push edx
    mov ecx, 17ah   ;IA32_MCG_STATUS
    rdmsr
    btr eax, 2   ;MCIP
    wrmsr
    pop edx
    pop ecx
    pop eax
	iretd
_MachineCheckHandler endp

ENDIF

end

;*************************************************************************
;*************************************************************************
;**                                                                     **
;**        (C)Copyright 1985-2008, American Megatrends, Inc.            **
;**                                                                     **
;**                       All Rights Reserved.                          **
;**                                                                     **
;**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
;**                                                                     **
;**                       Phone: (770)-246-8600                         **
;**                                                                     **
;*************************************************************************
;*************************************************************************
