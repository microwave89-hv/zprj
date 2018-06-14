;/*++
; This file contains an 'Intel Peripheral Driver' and is        
; licensed for Intel CPUs and chipsets under the terms of your  
; license agreement with Intel or your vendor.  This file may   
; be modified by the user, subject to additional terms of the   
; license agreement                                             
;--*/
;------------------------------------------------------------------------------
;
; Copyright (c) 2006 - 2011 Intel Corporation. All rights reserved
; This software and associated documentation (if any) is furnished
; under a license and may only be used or copied in accordance
; with the terms of the license. Except as permitted by such
; license, no part of this software or documentation may be
; reproduced, stored in a retrieval system, or transmitted in any
; form or by any means without the express written consent of
; Intel Corporation.
;
; Module Name:
;
;   Thunk.asm
;
; Abstract:
;
;   Real mode thunk
;
;------------------------------------------------------------------------------

    .686p
    .model  flat,C
    .const

EXTERNDEF   mCode16Size:DWORD
mCode16Size DD      _Code16End - _Code16Addr

    .data
    ALIGN   10h

NullSegSel  DQ      0
_16CsSegSel LABEL   QWORD
            DW      -1
            DW      0
            DB      0
            DB      9Bh
            DB      8Fh                 ; 16-bit segment, 4GB limit
            DB      0
;_16DsSegSel LABEL   QWORD
;            DW      -1
;            DW      0
;            DB      0
;            DB      93h
;            DB      8Fh                 ; 16-bit segment, 4GB limit
;            DB      0
_16Gdtr     LABEL   FWORD
            DW      $ - offset NullSegSel - 1
            DD      offset NullSegSel

    .code

IA32_REGS   STRUC   4t
_EDI        DD      ?
_ESI        DD      ?
_EBP        DD      ?
_ESP        DD      ?
_EBX        DD      ?
_EDX        DD      ?
_ECX        DD      ?
_EAX        DD      ?
_DS         DW      ?
_ES         DW      ?
_FS         DW      ?
_GS         DW      ?
_EFLAGS     DD      ?
_EIP        DD      ?
_CS         DW      ?
_SS         DW      ?
IA32_REGS   ENDS

_STK16      STRUC   1t
RetEip      DD      ?
RetCs       DW      ?
ThunkFlags  DW      ?
SavedGdtr   FWORD   ?
Resvd1      DW      ?
SavedCr0    DD      ?
SavedCr4    DD      ?
_STK16      ENDS

; IA32_REGISTER_SET *
; EFIAPI
; _Thunk16 (
;   IN OUT  IA32_REGISTER_SET         *RegisterSet,
;   IN      UINT32                    ThunkFlags,
;   IN      UINT32                    RealModeCs
;   );
_Thunk16    PROC    USES DS ES FS GS EDI ESI EBP EBX EDX ECX  ; 10 dwords will be pushed
    mov     ebp, esp
    add     ebp, 40
    mov     ORG_SS, ss                  ; preserve SS & ESP
    mov     ORG_ESP, esp

    mov     esi, [ebp + 4]              ; esi <- RegisterSet
    movzx   edx, (IA32_REGS ptr [esi])._SS ; find 16-bit stack linear address
    shl     edx, 4
    add     edx, (IA32_REGS ptr [esi])._ESP
    add     edx, - sizeof (IA32_REGS) - sizeof (_STK16) ; edx <- 16-bit stack linear address

    mov     edi, edx                    ; [RealMode.IA32_REGS] <- RegisterSet
    push    sizeof (IA32_REGS) / 4
    pop     ecx
    rep     movsd
    lea     eax, @F                     ; [RealMode._STK16.RetEip] <- ReturnOffset
    stosd
    mov     eax, cs                     ; [RealMode._STK16.RetCs] <- ReturnSegment
    stosw
    mov     eax, [ebp + 8]              ; [RealMode._STK16.ThunkFlags] <- ThunkFlags
    stosw
    sgdt    dword ptr [edi]             ; [RealMode._STK16.SavedGdtr] <- GDTR
    add     edi, 8
    mov     eax, cr0                    ; [RealMode._STK16.SavedCr0] <- CR0
    stosd
    mov     esi, eax                    ; esi <- CR0 to set
    and     esi, 07FFFFFFEh             ; clear BIT[24, 0]: PE & PG bits
    mov     eax, cr4                    ; [RealMode._STK16.SavedCr4] <- CR4
    stosd

    push    word ptr [ebp + 12]         ; [STACK] <- RealModeCs, far jump address for into RealMode
    pushw   0
    pushd   8                           ; transfer program control to a readable segment that has a limit of 64KB
    pushd   offset @16Bit
    mov     edi, edx                    ; edi <- 16-bit stack linear address

    sidt    fword ptr [ebp + 8]         ; save IDTR
    lgdt    _16Gdtr
    retf
@16Bit:
    mov     cr0, esi                    ; disable PE & PG
;    db      066h
;    mov     ecx, 0C0000080h
;    rdmsr
;    and     ah, NOT 1
;    wrmsr                               ; clear LME bit
    mov     eax, cr4
    and     al, not 030h                ; clear PAE & PSE
    mov     cr4, eax
    retf
@@:
    xor     eax, eax
    mov     eax, ss
    shl     eax, 4
    add     eax, esp                    ; [EAX] <- RegisterSet after x86 call..to return the execution result
    mov     ss, cs:word ptr [ORG_SS]    ; restore SS & ESP
    mov     esp, cs:dword ptr [ORG_ESP]
    lidt    fword ptr [ebp + 8]         ; restore IDTR

    ret

ORG_SS      DW      ?
ORG_ESP     DD      ?

_Thunk16    ENDP

    ALIGN   10h

; VOID
; EFIAPI
; _Code16Addr (
;   VOID
;   );
_Code16Addr PROC
_Code16Addr ENDP

; Input:  EDI <- 16-bit stack linear address
RealMode    PROC
    db      066h                        ; movzx   esp, di
    movzx   esp, di
    db      033h, 0FFh                  ; xor     di, di
    db      066h                        ; shr     edi, 4
    shr     edi, 4
    mov     ss, di                      ; mov     ss, di

    db      02Eh, 00Fh, 001, 01Eh       ; lidt    cs:[_16Idtr]
    dw      (_16Idtr - _Code16Addr)
    db      066h                        ; popad
    popa
    pop     ds
    pop     es
    pop     fs
    pop     gs
    add     esp, 4                      ; skip EFLAGS

    ; test if EFLAGS with _THUNK_INTERRUPT
    db      067h, 00F7h, 044h, 024h, 00Eh, 001h, 000h ; test [esp + 0Eh]
    jz      @F
    db      09Ch                        ; pushf
@@:
    push    cs
    db      068h                        ; pushw
    dw      (@FarCallRet - _Code16Addr)
    jz      @F
    db      066h,  067h
    jmp     fword ptr [esp + 6]
@@:
    db      066h, 067h
    jmp     fword ptr [esp + 4]
@FarCallRet:
    pushf                               ; pushfd actually
    push    gs
    push    fs
    push    es
    push    ds
    db      066h                        ; pushad
    pusha
    cli

    db      066h, 067h
    lgdt    (_STK16 ptr [esp + sizeof(IA32_REGS)]).SavedGdtr
    db      066h, 067h
    mov     eax, (_STK16 ptr [esp + sizeof(IA32_REGS)]).SavedCr4
    mov     cr4, eax
;    db      066h
;    mov     ecx, 0C0000080h
;    rdmsr
;    or      ah, 1
;    wrmsr                               ; set LME
    db      066h, 067h
    mov     eax, (_STK16 ptr [esp + sizeof(IA32_REGS)]).SavedCr0
    mov     cr0, eax
    db      066h, 067h
    jmp     fword ptr (_STK16 ptr [esp + sizeof(IA32_REGS)]).RetEip

RealMode    ENDP

_16Idtr     FWORD   (1 shl 10) - 1

_Code16End:

    END
