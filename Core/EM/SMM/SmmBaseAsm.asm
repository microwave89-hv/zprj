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

;**********************************************************************
; $Header: /Alaska/SOURCE/Modules/SMM/SMMBase/SmmBaseAsm.asm 2     7/14/09 12:16p Markw $
;
; $Revision: 2 $
;
; $Date: 7/14/09 12:16p $
;**********************************************************************
; Revision History
; ----------------
; $Log: /Alaska/SOURCE/Modules/SMM/SMMBase/SmmBaseAsm.asm $
; 
; 2     7/14/09 12:16p Markw
; Update headers.
; 
; 1     9/26/08 4:48p Markw
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

public EfiSmmInSmm

public InSmmFuncOffset
public InSmmFuncLength

InSmmFuncOffset dd InSmmFixup - InSmmStart
InSmmFuncLength dd InSmmEnd - InSmmStart

;<AMI_PHDR_START>
;----------------------------------------------------------------------------
;
; Procedure:	InSmm
;
; Description:	Updates if *InSmm if in SMM.
;
; Input:
;	IN EFI_SMM_BASE_PROTOCOL	*This,
;	OUT BOOLEAN					*InSmm
;
; Output:	EFI_STATUS
;
; Modified:	Nothing
;
;----------------------------------------------------------------------------
;<AMI_PHDR_END>

EfiSmmInSmm proc
InSmmStart EQU $
    or      rdx, rdx
    jnz     @f
    mov     rax, 8000000000000002h
    ret
@@:
    ;mov     al, 0
    db      0b0h
InSmmFixup EQU $
    db      0
    mov     [rdx], al
    mov     rax, 0
    ret
InSmmEnd EQU $
EfiSmmInSmm endp

ELSE    ;32-bits
.586p
.model small
.code

public _InSmmFuncOffset
public _InSmmFuncLength

_InSmmFuncOffset dd InSmmFixup - InSmmStart
_InSmmFuncLength dd InSmmEnd - InSmmStart

_EfiSmmInSmm proc public
InSmmStart EQU $
    or      dword ptr [esp + 8], 0
    jnz     @f
    mov     eax, 80000002h
    ret
@@:
    ;mov     al, 0
    db      0b0h
InSmmFixup EQU $
    db      0
    push    ebx
    mov     ebx, [esp + 12]
    mov     [ebx], al
    pop     ebx
    xor     eax, eax
    ret
InSmmEnd EQU $
_EfiSmmInSmm endp
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
