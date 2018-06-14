;**********************************************************************
;**********************************************************************
;**                                                                  **
;**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
;**                                                                  **
;**                       All Rights Reserved.                       **
;**                                                                  **
;**             5555 Oakbrook Pkwy, Norcross, GA 30093               **
;**                                                                  **
;**                       Phone: (770)-246-8600                      **
;**                                                                  **
;**********************************************************************
;**********************************************************************

;**********************************************************************
; $Header: /Alaska/BIN/Modules/ACPI/Template/S3Support/S3Restore/AcpiS3Wake.asm 1     2/03/11 4:09p Oleksiyy $
;
; $Revision: 1 $
;
; $Date: 2/03/11 4:09p $
;**********************************************************************
; Revision History
; ----------------
; $Log: /Alaska/BIN/Modules/ACPI/Template/S3Support/S3Restore/AcpiS3Wake.asm $
; 
; 1     2/03/11 4:09p Oleksiyy
; [TAG]  		EIP53402 
; [Category]  	Improvement
; [Description]  	Create new label of ACPI with separate S3 Functionality
; [Files]  		S3Restore.cif
; S3Restore.sdl
; S3Restore.mak
; S3Resume.dxs
; AcpiS3Wake.asm
; S3Resume.c
; AcpiPeiS3Func.c
; AcpiPeiS3Func.h
; BootScriptExecuter.c
; 
; 9     3/26/09 4:51p Oleksiyy
; New ACPI Core implementation - improves logic, execution time and
; memory usage of ACPI module.
; 
; 8     4/29/08 5:36p Yakovlevs
; 
; 7     4/15/08 12:28p Markw
; Add cs overrides. Option rom may change ds.
; 
; 6     1/23/07 4:24p Markw
; Added thunk support for a call for S3 video repost.
; 
; 5     5/27/05 4:18p Markw
; Added comment.
; 
; 4     5/10/05 3:00p Markw
; Corrected wakeup vector address. Uses 16 bit data selector and adjusts
; base of data selector to pointer to wake up vector.
; 
; 3     5/09/05 10:19a Markw
; Fixed cs and eip backwards. The OS is now given control.
; 
; 2     5/07/05 11:54p Markw
; Goes to real mode. But when resuming to windows cs and ip switched.
; Will fix.
; 
; 1     5/06/05 1:44p Markw
; 
;**********************************************************************
;<AMI_FHDR_START>
;
; Name:	AcpiS3Wake.asm
;
; Description: Provide the thunk S3 resume.
;
;<AMI_FHDR_END>
;**********************************************************************

.586P
.model small
include token.equ

ACPI_S3_SEG SEGMENT USE32 'CODE'
assume DS:ACPI_S3_SEG

public _RealModeThunkStart
public _RealModeThunkSize

align 16
;This code may be exexuted 

REAL_MODE_BASE equ (MKF_ACPI_THUNK_REAL_MODE_SEGMENT * 16)

;<AMI_PHDR_START>
;---------------------------------------------------------------------------
;
; Procedure: RealModeThunk
;
; Description: Switch to 16-bit to jump/call to an address.
;   This may be executed in place for a jump
;   or copied to a location if a call.
;
; Input: 
;       GdtDesc:DWORD       -- pointer descriptors with 16-bit.
;       JmpAddress: DWORD   -- Address to jump or call to.
;       IsCall:BYTE         -- TRUE - if call. FALSE - if jump.
;
;
; Output: None
;---------------------------------------------------------------------------
;<AMI_PHDR_END>
REAL_MODE_THUNK_START equ $
RealModeThunk	proc C	public, GdtDesc:DWORD, JmpAddress: DWORD, IsCall:BYTE
    pushad
    call    get_base_addr   ;push the eip.
get_base_addr:
    pop     ebx             ;ebx = eip.
    sub     ebx, offset get_base_addr -  REAL_MODE_THUNK_START ;ebx = Start address

    cmp     IsCall, 0
    je      @f

    ;If call, this function will return, so save original state.
	;Save 32 bit stack address of this module.
	;mov		[ebx + offset StackSave - REAL_MODE_THUNK_START], esp
        db 89h, 0a3h
        dd offset StackSave - REAL_MODE_THUNK_START
	;sgdt	fword ptr [ebx + offset GdtSave - REAL_MODE_THUNK_START]
        db 0fh, 1, 83h
        dd offset GdtSave - REAL_MODE_THUNK_START
	;sidt	fword ptr [ebx + offset IdtSave - REAL_MODE_THUNK_START]
        db 0fh, 1, 8bh
        dd offset IdtSave - REAL_MODE_THUNK_START
@@:

;--Switch to real mode--	
	;lidt fword ptr [ebx + offset LegacyLdtDescriptor - REAL_MODE_THUNK_START]
        db 0fh, 1, 9bh
        dd offset LegacyLdtDescriptor - REAL_MODE_THUNK_START
	
	mov	edx, GdtDesc        ;Get discriptor table with 16-bit descriptors.
	mov ecx, [edx + 2]		;ecx = GDT Base

    ;---Set the code selector base address of the memory location
    ;   to jump to 16-bit protected mode above 1MB for execute in place.
	mov	eax, offset Next
	mov	ebx, eax
	and	eax, 00ffffffh		;eax = [23:00] of next
	shr	ebx, 24				;ebx = [31:24] of next

	or [ecx + 8 + 2], eax		;GDT[1] (Code segment) base [23:00] of next
	or [ecx + 8 + 7], bl		;GDT[1] base [24:31] of next

    ;---Set the data selector base address of the memory location
    ;   that contains the location to jump to for thunking.
    ;   This is so 16-bit protected mode can read the jump address
    ;   on the caller stack above 1MB. This is needed because the
    ;   jump code will be executed in place.
    ;   For call code, this will not do anything useful.
	lea	edx, JmpAddress
	mov	ebx, edx
	and	edx, 00ffffffh		;edx = [23:00] address of wakeup vector
	shr	ebx, 24				;ebx = [31:24] address of wakeup vector

	or [ecx + 16 + 2], edx		;GDT[2] (Data segment) base [23:00] of next
	or [ecx + 16 + 7], bl		;GDT[2] base [24:31] of next
    ;---


    xor esp, esp            ;esp will be set to a non-zero if a call.
                            ;This will also to be used to determine
                            ; if call or not call. This is because
                            ; IsCall is not available in 16-bit mode.
    cmp IsCall, 0
    je  @f

    ;Set real mode stack except the linear stack address.
    mov esp, REAL_MODE_BASE + MKF_ACPI_THUNK_STACK_TOP

    ;-------------------------------------------------
    ;Setup the stack to simulate a int xx or call.
    ;-------------------------------------------------

    mov eax, offset ReturnFromPtr
    sub eax, REAL_MODE_THUNK_START  ;ax = return address.

    ;push the flags and return address to simulate the
    ; return address on the stack for int xx or call.
    pushf       ;push flags in case intxx
    push word ptr MKF_ACPI_THUNK_REAL_MODE_SEGMENT
    push ax     ;ax = return ip

    ;push to stack the cs:ip of the address to call to
    push JmpAddress     ;push cs:eip to jump to.

    ;-------------------------------------------------
    ;Now the stack is setup, so that a retf will jump
    ;to the address on stack.
    ;-------------------------------------------------

    ;Adjust the stack address, so it will be relative to ss.
    sub esp, REAL_MODE_BASE 
@@:

	;---Switch to 16-bit protected mode---
	mov     edx, GdtDesc
	lgdt    fword ptr [edx]

	;ITP doesn't display disassembly correctly until jump to 16 bit code.
	mov	ax, 10h			;16 bit data segment
	mov	ds, ax
	mov	es, ax
	mov	ss, ax
	mov	fs, ax
	mov	gs, ax

	;jmp	08:next
		db	0eah
		dd	0			;offset of next with new selector
		dw	08			;16 bit code selector
next:
	;---16 bit mode. Must use 16 bit instructions from here on.---
	;-------------------------------------------------------------

	;---Switch to real mode---
	mov	eax, cr0
	and	al, 0feh
	mov	cr0, eax				;switch to real mode
	;---In real mode---

    db  66h
    or  esp, esp                ;IsCall?
    jnz @f

    ;jmp far ptr [0]            ;Jump to the address stored in ds:0. 
        db 0ffh, 2eh            ;The descriptor's base is in stack.
        dw 0
    ;Does not return.
@@:

    ; jmp REAL_MODE_SEGMENT:real_mode_adr
        db 0eah
        dw offset real_mode_adr - REAL_MODE_THUNK_START
        dw MKF_ACPI_THUNK_REAL_MODE_SEGMENT

real_mode_adr:
	db 8ch, 0c8h	;mov	ax, cs
	db 8eh, 0d8h	;mov    ds, ax
	db 8eh, 0c0h	;mov    es, ax
	db 8eh, 0d0h	;mov    ss, ax
	db 8eh, 0e0h	;mov    fs, ax
	db 8eh, 0e8h	;mov    gs, ax

   retf     ;call JmpAddress on stack.

ReturnFromPtr:
;--------------End Real Mode operations---------

	;--Switch to protected mode--
    
	;mov	esp, cs:[offset StackSave - REAL_MODE_THUNK_START]			;Get original stack back.
        db 	2eh, 66h, 8bh, 26h
        dw	offset StackSave - REAL_MODE_THUNK_START

	;lgdt	fword ptr cs:[offset GdtSave - REAL_MODE_THUNK_START]
	db	2eh, 66h, 0fh, 1, 16h
	dw	offset GdtSave - REAL_MODE_THUNK_START

	mov	eax, cr0
	or      al, 1			;Set PE bit
	mov	cr0, eax      		;Turn on Protected Mode

	;jmp 10:P32MODE
        db 66h, 0eah
        dd  REAL_MODE_BASE + offset P32Mode - REAL_MODE_THUNK_START
        dw  10h
P32Mode::
	mov     ax, 08
	mov     ds, ax
	mov     es, ax
	mov     ss, ax
	mov     fs, ax
	mov     gs, ax
	
	;lidt	fword ptr [REAL_MODE_BASE + offset IdtSave - REAL_MODE_THUNK_START]
        db 0fh, 1, 1dh
        dd REAL_MODE_BASE + offset IdtSave - REAL_MODE_THUNK_START
    popad
	ret
RealModeThunk	endp

align 8
	public LegacyLdtDescriptor
LegacyLdtDescriptor label fword
	dw	3ffh
	dd	0

;Note: The following below is only used in a call when this is copied to below 1MB.
;The data below can not be changed when this is executed from ROM.

	public StackSave
StackSave label dword
	dd	0

align 8
	public GdtSave
GdtSave	label fword
	dw	0
	dd	0

align 8
	public IdtSave
IdtSave label fword	
	dw	0
	dd	0

REAL_MODE_THUNK_END EQU $

_RealModeThunkStart label dword
    dd REAL_MODE_THUNK_START 

_RealModeThunkSize label dword
    dd REAL_MODE_THUNK_END - REAL_MODE_THUNK_START

ACPI_S3_SEG ENDS
end

;**********************************************************************
;**********************************************************************
;**                                                                  **
;**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
;**                                                                  **
;**                       All Rights Reserved.                       **
;**                                                                  **
;**             5555 Oakbrook Pkwy, Norcross, GA 30093               **
;**                                                                  **
;**                       Phone: (770)-246-8600                      **
;**                                                                  **
;**********************************************************************
;**********************************************************************
