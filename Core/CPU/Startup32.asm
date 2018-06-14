;*************************************************************************
;*************************************************************************
;**                                                                     **
;**        (C)Copyright 1987-2013, American Megatrends, Inc.            **
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
; $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/Haswell/AMI Cpu PKG/CPU Core/Startup32.asm 3     11/28/12 1:11a Davidhsieh $
;
; $Revision: 3 $
;
; $Date: 11/28/12 1:11a $
;**********************************************************************
; Revision History
; ----------------
; $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/Haswell/AMI Cpu PKG/CPU Core/Startup32.asm $
; 
; 3     11/28/12 1:11a Davidhsieh
; [TAG]  		EIP107763
; [Category]  	Bug Fix
; [Severity]  	Important
; [Symptom]  	UEFI SCT 2.3.1 Floating Point ABI Test fail
; [RootCause]  	According to UEFI 2.3.1 errata C, Floating-point control
; word must be initialized to 0x037F
; [Solution]  	Use 0x37f for Floating-point control word
; 
; 2     3/09/12 2:13a Davidhsieh
; Create BIST data
; 
; 1     2/07/12 3:58a Davidhsieh
; 
;**********************************************************************

;<AMI_FHDR_START>
;----------------------------------------------------------------------------
;
; Name:	StartUp32.asm
;
; Description:	Switch CPU to protected mode, INIT CAR and setup stack.
;
;----------------------------------------------------------------------------
;<AMI_FHDR_END>

.586P
.XMM
.model  small

include token.equ
include	cpu.equ

ifndef MKF_PI_SPECIFICATION_VERSION
MKF_PI_SPECIFICATION_VERSION EQU 0
endif

ifndef MKF_CSM_SUPPORT
MKF_CSM_SUPPORT EQU 0
endif

ifndef MKF_MPDTable_CREATED
MKF_MPDTable_CREATED EQU 0
endif

ifndef MKF_PACK_MICROCODE
MKF_PACK_MICROCODE EQU 0
endif

ifndef MKF_MICROCODE_SPLIT_BB_UPDATE
MKF_MICROCODE_SPLIT_BB_UPDATE EQU 0
endif

PhysMask equ (NOT (MKF_CAR_TOTAL_SIZE - 1))	;8k stack

WriteBack equ 6
ValidMask equ 1 SHL 11

IA32_MISC_ENABLE        EQU 1A0h
FAST_STRING_ENABLE_BIT  EQU 01h

MTRR_PHYS_BASE_0        EQU 0200h
MTRR_PHYS_MASK_0        EQU 0201h
MTRR_PHYS_BASE_1        EQU 0202h
MTRR_PHYS_MASK_1        EQU 0203h
MTRR_PHYS_BASE_2        EQU 0204h
MTRR_PHYS_MASK_2        EQU 0205h
MTRR_PHYS_BASE_3        EQU 0206h
MTRR_PHYS_MASK_3        EQU 0207h
MTRR_PHYS_BASE_4        EQU 0208h
MTRR_PHYS_MASK_4        EQU 0209h
MTRR_PHYS_BASE_5        EQU 020Ah
MTRR_PHYS_MASK_5        EQU 020Bh
MTRR_PHYS_BASE_6        EQU 020Ch
MTRR_PHYS_MASK_6        EQU 020Dh
MTRR_PHYS_BASE_7        EQU 020Eh
MTRR_PHYS_MASK_7        EQU 020Fh
MTRR_FIX_64K_00000      EQU 0250h
MTRR_FIX_16K_80000      EQU 0258h
MTRR_FIX_16K_A0000      EQU 0259h
MTRR_FIX_4K_C0000       EQU 0268h
MTRR_FIX_4K_C8000       EQU 0269h
MTRR_FIX_4K_D0000       EQU 026Ah
MTRR_FIX_4K_D8000       EQU 026Bh
MTRR_FIX_4K_E0000       EQU 026Ch
MTRR_FIX_4K_E8000       EQU 026Dh
MTRR_FIX_4K_F0000       EQU 026Eh
MTRR_FIX_4K_F8000       EQU 026Fh
MTRR_DEF_TYPE           EQU 02FFh

EFI_PEI_PPI_DESCRIPTOR_PPI				EQU 00000010h
EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST	EQU 80000000h

FV_LENGTH		EQU (16 + 16)
FV_SIGNATURE    EQU (FV_LENGTH + 8)
FV_HDR_LENGTH	EQU (FV_SIGNATURE + 4 + 4)

FFS_LENGTH		EQU (16 + 2 + 1 + 1)
FFS_HDR_LENGTH	EQU (FFS_LENGTH + 3 + 1)

uCODE_CPU_SIGNATURE	EQU 12
uCODE_CPU_FLAGS		EQU	24
uCODE_DATA_SIZE		EQU	28
uCODE_TOTAL_SIZE	EQU	32

; Externs
EXTERN	SECCoreAtPowerOn:NEAR32
PUBLIC		SECCoreAtPowerOnEnd

;STARTUP_SEG SEGMENT USE32
;----------------------------------------------------------------------------
;	STARTUP_SEG  S E G M E N T  STARTS
;----------------------------------------------------------------------------
STARTUP_SEG		SEGMENT		PARA PUBLIC 'CODE' USE32

MICOCODE_FFS_GUID label dword
	dd	17088572h
	dw	377Fh
	dw	44efh
	db	8Fh,4Eh,0B0h,9Fh,0FFh,46h,0A0h,70h

AMI_BIST_GUID label dword
    dd 0A7E2CE72h
    dw 0DC32h
    dw 04BC0h
    db 9Eh, 35h, 0FEh, 0B3h, 0Ah, 0E5h, 0CCh, 47h

SEC_CORE_PPI_DESC STRUCT
    BIST_FLAGS          dd ?
    BIST_GUID           dd ?
    BIST_PPI            dd ?
SEC_CORE_PPI_DESC ends


SecCorePpiDesc SEC_CORE_PPI_DESC < \
    EFI_PEI_PPI_DESCRIPTOR_PPI + EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST, \
    offset AMI_BIST_GUID, \
    0 \
>


;<AMI_PHDR_START>
;----------------------------------------------------------------------------
; Procedure:	FindMicrocode
;
; Description:	This routine searches the file volume for a microcode update
;	and returns the address if found.
;
; Input: None
;
; Output: eax = Pointer to microcode. 0 if not found.
;
; Notes:
;	This routine can not use stack. It can be called from rom or ram.
;	If called from rom, a hard coded stack must be exist in rom.
;
;----------------------------------------------------------------------------
;<AMI_PHDR_END>

IF MKF_Microcode_SUPPORT
public FindMicrocode
extern FindMicrocodeEnd:NEAR32
FindMicrocode proc
IF  MKF_MICROCODE_SPLIT_BB_UPDATE
    mov     ebx, MKF_FV_MICROCODE_UPDATE_BASE
FindMicrocodeFv:
ELSE
    mov     ebx, MKF_FV_MICROCODE_BASE
ENDIF
    cmp     dword ptr [ebx + FV_SIGNATURE], 'HVF_'
    jne     Microcode_Not_Found             ;Corrupt FV?

	mov		edx, ebx
	mov		eax, [ebx + FV_HDR_LENGTH]
	and		eax, 0ffffh		;Get 16 bit FV header length
	add		ebx,  eax		;ebx = start of FFS
    jc      Microcode_Not_Found             ;Corrupt FV?
	add		edx, [edx + FV_LENGTH]
    jz      @f                              ;zf if Boot Block
    jc      Microcode_Not_Found             ;Corrupt FV?
@@:
    dec     edx                             ;edx = End of FFS    
;---Find File ---
;ebx = Start of FFS
;edx = End of FFS
Get_Next_File:
	cmp		dword ptr [ebx], -1		;Is in end of files, but not firmware volume.
	je		File_not_found
	mov		ecx, 4
	mov		esi, ebx
	mov		edi, offset MICOCODE_FFS_GUID
	;compare file guid
	repe 	cmpsd
	je		Found_File
;---get next file--
	;get file length and add to ebx
	mov		eax, [ebx + FFS_LENGTH]
	and		eax, 0ffffffh			;eax = File length (24 bits)
	add		ebx, eax				;next file
	;align file
	add		ebx, 7
    jc      Microcode_Not_Found     ;Check for wrap-around if bad data.
	and		ebx, not 7

	cmp		ebx, edx		        ;Is end of firmware volume?
	jb		Get_Next_file
File_not_found:
    jmp     Microcode_Not_Found
;---Found File---
Found_File:
;ebx = Start of Microcode FFS
;edx = End of FFS + 1

;---Search micocode for match.---
	mov		edi, ebx

	mov		eax, [ebx + FFS_LENGTH]
	and		eax, 0ffffffh			;eax = File length (24 bits)
	add		edi, eax				;edi = end of file
    jc      Microcode_Not_Found     ;Check for wrap-around if bad data.

IF MKF_MPDTable_CREATED
    movzx   eax, word ptr [edi-2]           ;eax = MPDT length
    sub     edi, eax                        ;edi = end of microcodes.
ENDIF

	add		ebx, FFS_HDR_LENGTH
    jc      Microcode_Not_Found     ;Check for wrap-around if bad data.

	mov		esi, ebx

    mov     eax, 1
    cpuid
    mov		ebx, eax	;ebx = CPU signature

	mov		ecx, 17h
	rdmsr				;read CPUS flags

	shr		edx, 18
	and		dl, 7		;dl = CPU FLAG
	mov		cl, dl
	mov		dl, 1
	shl		dl, cl		;dl = bit set for CPU flag

    xchg    ebx, esi    ;ebx = ptr, esi = signature
Next_Microcode:
	cmp		ebx, edi                ;Check to see if microcode at end of FFS File.
	jae		Microcode_Not_Found

	cmp		dword ptr [ebx], 1 ;Check if correct header revision
	jne		Microcode_Not_Found

	mov		ecx, 2048	;total size if data size in field = 0.
	cmp		dword ptr [ebx + uCODE_DATA_SIZE], 0
	jz		@f
	mov		ecx, [ebx + uCODE_TOTAL_SIZE]	;Get total size.
@@:

	cmp		esi, [ebx + uCODE_CPU_SIGNATURE]
	jne		Check_Ext_Sig

    mov     eax, ebx                        ;Store uC addr in eax, so if jnz succeeds.
	test	dl, [ebx + uCODE_CPU_FLAGS]     ;uC flags match?
	jnz		Exit_Find_Microcode

Check_Ext_Sig:
    mov     ebp, [ebx + uCODE_TOTAL_SIZE]	;Get total size.
    mov     eax, [ebx + uCODE_DATA_SIZE]    ;Get Data Size
    add     eax, 48
    cmp     ebp, eax
    jbe     Find_Next_Microcode             ;No extended signature.

    mov     ecx, [ebx + eax]                ;Get extended signature.
    cmp     ecx, 20
    jae     Microcode_Not_Found             ;Corrupt?
    lea     ebp, [ebx + eax + 20]           ;First Proc Signature.

@@:    
    cmp     [ebp], esi                      ;Check Signature
    jne     Next_Ext_Sig

    mov     eax, ebx
    test    dl, [ebp + 4]                   ;Check processor flags
    jnz     Exit_Find_Microcode
Next_Ext_Sig:
    add     ebp, 12
    loop    @b
    mov     ecx, [ebx + uCODE_TOTAL_SIZE]	;Get total size.
Find_Next_Microcode:
    ;align to next block size
IF MKF_PACK_MICROCODE
    add     ecx, 15
    and     ecx, 0fffffff0h
ELSE
    add     ecx, MKF_MICROCODE_BLOCK_SIZE - 1
    and     ecx, NOT (MKF_MICROCODE_BLOCK_SIZE - 1)
ENDIF
	add		ebx, ecx
    jc      Microcode_Not_Found             ;Overflow - bad data.
	jmp		Next_Microcode

Microcode_Not_Found:
IF  MKF_MICROCODE_SPLIT_BB_UPDATE
    cmp     ebx, MKF_FV_MICROCODE_BASE
    jae     @f
    mov     ebx, MKF_FV_MICROCODE_BASE
    jmp     FindMicrocodeFv
@@:
ENDIF
	xor		eax, eax
Exit_Find_Microcode:
	jmp FindMicrocodeEnd
FindMicrocode endp

ENDIF ;MKF_Microcode_SUPPORT

;<AMI_PHDR_START>
;----------------------------------------------------------------------------
;
; Procedure:	CPU_START
;
; Description:	Switch CPU to protected mode, INIT CAR and setup stack.
;
; Input: None
;
; Output: None
;
;----------------------------------------------------------------------------
;<AMI_PHDR_END>

public _CPU_START
_CPU_START:
	;---16 bit in 32 bit assembler--
	;---Some 16-bit and 32-bit assmebly is the same, others are not.---
	;---Need to use some machine code.---

    fninit              ;Clear any pending Floating point exceptions
    movd    mm0, eax    ;Save BIST state in MM0

	cli

if MKF_CSM_SUPPORT EQ -1
    db      0B8h, 00h, 0F0h     ;mov     ax, 0F000h
    db      8Eh, 0D8h           ;mov     ds, ax
    db      0BEh, 0F0h, 0FFh    ;mov     si, 0FFF0h
    db      80h, 3Ch, 0EAh      ;cmp     BYTE PTR [si], 0EAh   ; Is it warm reset ?
    jne     NotWarmReset                                    ; If not.

    db      0EAh                ;DB      0EAh                  ; Far jump to F000:E05B (legacy BIOS warm reset entry)
    dw      0E05Bh              ;DW      0E05Bh
    dw      0F000h              ;DW      0F000h
NotWarmReset:
endif

	;Switch to protected mode
	;lgdt	fword ptr cs:[GdtDescriptor]	;Relative to 4G.
;		db	66h,2eh,0fh,1,16h
;		dw	offset GdtDescriptor    ;<-------Problem------<
 
    db   66h
    mov  ebx, offset GdtDescriptor
    ;lgdt fword ptr cs:[bx]
	    db	66h, 2eh,0fh,1,17h

	mov		eax, cr0
	or      al, 1			;Set PE bit
	mov		cr0, eax      	;Turn on Protected Mode

	;In 16 bit protected mode

	cld
	db	0b8h		;mov	ax, DATA_SEL
	dw	DATA_SEL
	db	8eh, 0d8h	;mov	ds, ax
	db	8eh, 0c0h	;mov	es, ax
	db	8eh, 0d0h	;mov	ss, ax
	db	8eh, 0e0h	;mov	fs, ax
	db	8eh, 0e8h	;mov	gs, ax

	;set cs segment
	;jmp 10:CHANGE_CS
		db	66h, 0eah
    dd	CHANGE_CS				;Relative to 4G.
		dw	CODE_SEL
CHANGE_CS:
   ;---If Limit CPU ID enabled because of soft reset, disable.
    mov     ecx, 01a0h
    rdmsr
    btr     eax, 22     ;Reset bit
    jnc     @f          ;If already reset, don't write to 1a0.
    wrmsr
@@:
	;---Change APIC Address---
    mov     ecx, MSR_XAPIC_BASE		; Enable local APIC
	rdmsr
	and		edx, NOT 0fh			;Mask local APIC address
	and		eax, NOT 0fffff000h		;Mask local APIC address
	or		eax, MKF_LOCAL_APIC_BASE
	wrmsr

;--------------------------------------------------------------------

	;In CR4, set OSFXSR bit 9 and OSXMMEXCPT bit 10
	mov		eax, cr4
	or  	ax, 1 SHL 9 + 1 SHL 10
	mov		cr4, eax

;---------------------------------------------
;---------------------------------------------
;---------------------------------------------

; Invoke the SECCore Init hook for other components to hook functions
; This also executes referece code.
	jmp	SECCoreAtPowerOn
SECCoreAtPowerOnEnd::

    ; This stores the BIST for SBSP.
    ; The PBSPs BIST is stored in MM0. The value will preserved across INIT-SIPI and captured
    ; in CPU PEI.
    movd    eax, mm0
    pushd   eax         ;Bist0

    ;Get Apic ID
    mov     eax, MKF_LOCAL_APIC_BASE + 20h
    mov     ebx, [eax]
    shr     ebx, 24
    pushd   ebx         ;ApicId0
    pushd   1           ;Num BISTS

    mov     ebx, esp    ;points to AMI_BIST_PPI_STRUCT

    sub esp, size SEC_CORE_PPI_DESC
    mov esi, offset SecCorePpiDesc
    mov edi, esp
    mov ecx, size SEC_CORE_PPI_DESC / 4
    rep movsd

    mov (SEC_CORE_PPI_DESC PTR [esp]).BIST_PPI, ebx
    mov ebx, esp

IFDEF EFIx64
    pushd 37fh
ELSE
    pushd 27fh
ENDIF
    fldcw word ptr [esp]    ;Set FP control word according UEFI
    add   esp, 4

    ; Pass NEM address into the PEI Core
    push    MKF_CAR_BASE_ADDRESS

    ; Dispatch table
    push  ebx

IF MKF_PI_SPECIFICATION_VERSION GE 00010000h
    ; Initialize EFI_SEC_PEI_HAND_OFF data structure in CAR
    mov     ebx, MKF_CAR_BASE_ADDRESS
    mov     (EFI_SEC_PEI_HAND_OFF ptr [ebx]).DataSize, sizeof EFI_SEC_PEI_HAND_OFF
    mov     (EFI_SEC_PEI_HAND_OFF ptr [ebx]).Reserved1, 0

    ; Report the Boot Firmware Volume that PEI should search for PEIMS (FV_BB)
    mov     (EFI_SEC_PEI_HAND_OFF ptr [ebx]).BootFirmwareVolumeBase, MKF_FV_BB_BASE
    
    ; Report the Size of the Boot Firmware Volume, in Bytes
    mov      eax, MKF_FV_BB_BASE + 32
    mov      eax, [eax]
    mov     (EFI_SEC_PEI_HAND_OFF ptr [ebx]).BootFirmwareVolumeSize, eax

    ; Report the start the CAR Base address and size (based on SDL tokens)
    mov     (EFI_SEC_PEI_HAND_OFF ptr [ebx]).TemporaryRamBase, MKF_CAR_BASE_ADDRESS
    mov     (EFI_SEC_PEI_HAND_OFF ptr [ebx]).TemporaryRamSize, MKF_CAR_TOTAL_SIZE

    ; Report the starting address of the CAR that PEI Core can use
    mov     (EFI_SEC_PEI_HAND_OFF ptr [ebx]).PeiTemporaryRamBase, MKF_CAR_BASE_ADDRESS + sizeof EFI_SEC_PEI_HAND_OFF + EFI_PEI_SERVICES_DOUBLE_POINTER_SIZE
    mov     (EFI_SEC_PEI_HAND_OFF ptr [ebx]).PeiTemporaryRamSize, MKF_CAR_TOTAL_SIZE - sizeof EFI_SEC_PEI_HAND_OFF - EFI_PEI_SERVICES_DOUBLE_POINTER_SIZE

    ; Report the start of the stack and its size (should point into top of CAR region)
    mov     (EFI_SEC_PEI_HAND_OFF ptr [ebx]).StackBase, MKF_CAR_BASE_ADDRESS + MKF_CAR_TOTAL_SIZE
    mov     (EFI_SEC_PEI_HAND_OFF ptr [ebx]).StackSize, MKF_CAR_TOTAL_SIZE

    ; In CAR, reserve 8 bytes space before IDT Base Address for a pointer to a pointer 
    ; of the PEI Services Table (EFI_PEI_SERVICES**) which will be initialized in PEI

    ; IDT Base Address = MKF_CAR_BASE_ADDRESS + sizeof EFI_SEC_PEI_HAND_OFF + EFI_PEI_SERVICES_DOUBLE_POINTER_SIZE
    ; IDT Size is 0 because it will be initalized in PEI.  Here, it is only 
    ; used to reserved 8 bytes space for (EFI_PEI_SERVICES**)
    sub     esp, sizeof IDTR32
    mov     (IDTR32 ptr [esp]).BaseAddress, MKF_CAR_BASE_ADDRESS + sizeof EFI_SEC_PEI_HAND_OFF + EFI_PEI_SERVICES_DOUBLE_POINTER_SIZE
    mov     (IDTR32 ptr [esp]).Limit, 0
    lidt    FWORD PTR [esp]
    add     esp, sizeof IDTR32

    ; Push a pointer to the the EFI_PEI_PPI_DESCRIPTOR AMI_PI_TODO: 
    ;push    0

    ; Push a pointer to the EFI_SEC_PEI_HAND_OFF data structure onto the stack
    push 	MKF_CAR_BASE_ADDRESS

ELSE
    ; Pass stack size into the PEI Core
    push    MKF_CAR_TOTAL_SIZE

    ; Pass BFV into the PEI Core
  	push 	DWORD PTR ds:[0FFFFFFFCh]
ENDIF
   
	;mov  	edi, 0FFFFFFE0h
    call 	DWORD PTR ds:[0FFFFFFE0h]
;---Does not return---

align 16
MTRR_TABLE	label byte
	dw      MTRR_DEF_TYPE
	dw      MTRR_PHYS_BASE_0, MTRR_PHYS_MASK_0
	dw      MTRR_PHYS_BASE_1, MTRR_PHYS_MASK_1
	dw      MTRR_PHYS_BASE_2, MTRR_PHYS_MASK_2
	dw      MTRR_PHYS_BASE_3, MTRR_PHYS_MASK_3
	dw      MTRR_PHYS_BASE_4, MTRR_PHYS_MASK_4
	dw      MTRR_PHYS_BASE_5, MTRR_PHYS_MASK_5
	dw      MTRR_PHYS_BASE_6, MTRR_PHYS_MASK_6
	dw      MTRR_PHYS_BASE_7, MTRR_PHYS_MASK_7
	dw      MTRR_FIX_64K_00000
	dw      MTRR_FIX_16K_80000
	dw      MTRR_FIX_16K_A0000
	dw      MTRR_FIX_4K_C0000, MTRR_FIX_4K_C8000
	dw      MTRR_FIX_4K_D0000, MTRR_FIX_4K_D8000
	dw      MTRR_FIX_4K_E0000, MTRR_FIX_4K_E8000
	dw      MTRR_FIX_4K_F0000, MTRR_FIX_4K_F8000
MTRR_TABLE_END 	label byte

;----------------------------------------------
align 16
GDT_BASE:
NULL_SEL	equ	$-GDT_BASE	 ;NULL Selector 0
		dd	0, 0

DATA_SEL	equ	$-GDT_BASE     	; Selector 8, Data 0-ffffffff 32 bit
	dd 0000ffffh
	dd 00cf9300h

CODE_SEL	equ	$-GDT_BASE     	; Selector 10h, CODE 0-ffffffff 32 bit
	dd 0000ffffh
	dd 00cf9b00h

; We only need this because Intel DebugSupport driver
; (RegisterPeriodicCallback function) assumes that selector 0x20 is valid
; The funciton sets 0x20 as a code selector in IDT
;
; To switch to 16 bit, Selectors SYS16_CODE_SEL and SYS16_DATA_SEL are used.
;
; System data segment descriptor
;
SYS_DATA_SEL        equ     $ - GDT_BASE               ; Selector [0x18]
	dd 0000FFFFh	;0 - f_ffff
	dd 00cf9300h	;data, expand-up, notwritable, 32-bit

; System code segment descriptor
SYS_CODE_SEL        equ     $ - GDT_BASE               ; Selector [0x20]
	dd 0000FFFFh	;0 - f_ffff
	dd 00cf9b00h	;data, expand-up, writable, 32-bit
SPARE3_SEL  equ $-GDT_BASE            ; Selector [0x28]
	dd 0, 0
SYS_DATA64_SEL    equ $-GDT_BASE          ; Selector [0x30]
	dd 0000FFFFh
	dd 00cf9300h
SYS_CODE64_SEL    equ $-GDT_BASE          ; Selector [0x38]
	dd 0000FFFFh
	dd 00af9b00h
SPARE4_SEL  equ $-GDT_BASE            ; Selector [0x40]
	dd 0, 0
GDT_SIZE	equ     $-GDT_BASE		;Size of Descriptor Table

GdtDescriptor:
	dw	GDT_SIZE - 1			; GDT limit
	dd  offset GDT_BASE	; GDT base	Relative to 4G.

STARTUP_SEG ENDS

end

;*************************************************************************
;*************************************************************************
;**                                                                     **
;**        (C)Copyright 1987-2013, American Megatrends, Inc.            **
;**                                                                     **
;**                       All Rights Reserved.                          **
;**                                                                     **
;**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
;**                                                                     **
;**                       Phone: (770)-246-8600                         **
;**                                                                     **
;*************************************************************************
;*************************************************************************
