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
; $Header: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Core/EM/SMM/SmmEntry.asm 2     10/31/12 10:26a Wesleychen $
;
; $Revision: 2 $
;
; $Date: 10/31/12 10:26a $
;**********************************************************************
; Revision History
; ----------------
; $Log: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Core/EM/SMM/SmmEntry.asm $
; 
; 2     10/31/12 10:26a Wesleychen
; Update SMM to 4.6.3_SMM_46.
; 
; 1     10/22/12 7:08a Wesleychen
; Support Intel PFAT.
; 
; 58    4/01/11 10:33a Markw
; [TAG]  		EIP57440
; [Category]  	New Feature
; [Description]  	Add PI 1.1 SMM support for reading/writing floating
; point/smm save state.
; 
; [Files]  		CpuCspLib.h, CpuCspLib.c, SmmPiSmst.c,  SmmPrivateShared.h,
; SmmHdr.equ, SmmInit.c, SmmEntry.asm
; 
; 57    11/23/09 11:20a Markw
; Update fxsave and fxrstor for 64-bit.
; 
; 56    8/11/09 11:49a Markw
; Removed Legacy registration. This is removed from latest PI and not
; used by projects. Also, update clearing upper 32-bits of 64-bit
; registers.
; 
; 55    7/08/09 8:13p Markw
; Update headers.
; 
; 54    5/12/09 7:02p Markw
; EIP #22087 - Always reinialize IDT in SMM even with AMI Debugger. Some
; processors place junk value in IDT.
; 
; 53    12/23/08 2:18p Markw
; EIP #17900  Set up TSS. Borland C in DOS hangs otherwise.
; 
; 52    11/21/08 4:57p Markw
; Add SmmInit into SMM_ENTRY_STRUCT.
; 
; 51    9/07/08 12:51a Markw
; 
; 50    9/07/08 12:43a Markw
; Separate SMM Private structure into inside SMM and outside SMM
; structure.
; 
; 49    8/27/08 9:05p Markw
; Nehalem SMRR is now WB. Fix SMM Thunk Stack bug.
; 
; 48    5/23/08 11:14a Markw
; Don't load idt if AMI Debugger. Debugger won't work in SMM if idt is
; reloaded.
; 
; 47    4/04/08 6:22p Markw
; User Smm Msr from SMM_BASE_PRIVATE_STRUCT instead of token.
; 
; 46    3/03/08 6:36p Markw
; Added 32-bit register for smm thunk.
; 
; 45    1/07/08 1:58p Markw
; For SMM thunk, read cs in 16-bit real mode instead of undefined CPU
; execution between real and protected mode.
; cs was invalid when read.
; 
; 44    11/26/07 6:00p Markw
; Fix bug in previous bug fix.
; 
; 43    11/26/07 5:51p Markw
; Fix smm thunk bug - store return address.
; 
; 42    11/21/07 3:38p Markw
; Update checking MKF_SMM_THUNK_IN_CSM condition from 1 to -1.
; 
; 41    11/14/07 2:02p Markw
; Added SMRR support and updated SMM Cache for non-SMRR.
; 
; 40    10/29/07 3:24p Markw
; 
; 39    10/29/07 10:58a Markw
; Smm Thunk:
; * Code and data different segments.
; * Code position independent.
; * Switch for CSM for code and EBDA for data.
; 
; 38    10/24/07 12:02p Markw
; SMM Thunk code position independent. Data in a separate segment than
; code in Smm Thunk.
; Combined BSP and AP SmmEntry.
; 
; 37    9/10/07 1:39p Markw
; Add Interrupt Handling in SMM.
; 
; 36    6/14/07 10:54a Markw
; In SmmThunk, jump condition is incorrect. pushf wasn't occurring before
; iret call.
; 
; 35    6/08/07 6:51p Markw
; Save/Restore XMM.
; 
; 34    4/13/07 11:04a Markw
; Update header.
; 
; 33    3/22/07 5:37p Markw
; Set stack before calling legacy_handler.
; 
; 32    3/12/07 11:24a Markw
; Enable XMM for 32-bit. Guarantee 16-byte stack alignment.
; 
; 31    3/06/07 10:40a Markw
; Fix legacy handler calling entry point.
; 
; 30    2/08/07 10:49a Markw
; Preserve stack on legacy_handler.
; 
; 29    1/11/07 12:31p Markw
; Use switch to enable/disable legacy code during build.
; 
; 28    1/10/07 2:12p Markw
; Move legacy only code to end. Otherwise, if 64-bit BSP entry in TSEG,
; APs will overlap part of smm bsp entry code.
; 
; 27    1/09/07 6:47p Markw
; Store fixup addresses in SmmEntry for locations that have to fixed-up
; during BIOS.
; 
; 26    1/09/07 11:47a Markw
; Removed using MKF_SMM_BSP_BASE in memory access and segment changes.
; Uses indexing or retf.
; 
; 25    12/29/06 4:46p Markw
; Update CPU syncronization.
; 
; 24    12/11/06 5:53p Markw
; Commented out initializing the flags because of potentional errors, and
; using flags as input would be unusual.
; 
; 23    11/13/06 7:15p Markw
; Combine more common code between 32 and 64 bit.
; 
; 22    11/10/06 3:18p Markw
; Combined x32 and x64 where it is the same.
; 
; 21    10/17/06 11:23a Davidd
; Change made to not setting the Page Global Enable bit in CR4 to correct
; the system reset problem when installing / booting Vista 32.
; 
; 20    9/22/06 6:07p Markw
; In 32-bit fix stack after calling dispatcher.
; 
; 19    9/18/06 3:21p Markw
; Updated 32 bit part for BSP an AP sync.
; 
; 18    9/18/06 11:44a Markw
; Add a check to guarentee that BSP and Ap can't get out of sync. Also
; clear WT bit in cr0 in 64-bit.
; 
; 17    8/25/06 10:49a Markw
; Enable XMM for 64-bit.
; 
; 16    8/24/06 3:28p Felixp
; Preliminary x64 support (work in progress)
; 
; 15    4/20/06 1:50p Markw
; Fixed SmmThunk to use token for BSP SMM Base.
; For SmmThunk calls that don't pass arguments on stack, added 3f to
; emulate INT calls.
; 
; 14    2/03/06 10:27a Markw
; Moved Smm Base change to PEI CPU.
; Added a token for SMM BSP Base Address.
; Added IED support. 
; 
; 13    1/13/06 11:28a Markw
; Added SMM Thunk support.
; 
; 12    1/10/06 2:57p Markw
; Add support for multi-threadding and sync all CPUs during entry/exit of
; SMM.
; 
; 11    11/03/05 5:35p Markw
; Added entries to GDT for addional descriptors that Intel uses.
; 
; 10    7/21/05 11:28a Srinin
; Fixed Legacy SMI handler support.
; 
; 8     7/19/05 8:00p Markw
; Add support for calling real mode handlers.
; 
; 7     7/12/05 3:14p Markw
; Moved BSP entry from 0xa8000 to 0xa0000.
; 
; 6     7/11/05 12:04p Markw
; Removed setting isCallback. This simplified the dispatcher.
; 
; 5     7/06/05 2:15p Markw
; Commented out unused code.
; 
; 4     4/07/05 4:05p Sivagarn
; Corrected the make token issue
; 
; 3     4/04/05 5:18p Sivagarn
; Converted hard coded S/W SMI port to generic SDL token
; 
; 1     1/28/05 4:32p Sivagarn
; SMM Dispatcher Component - Initial check in
; 
; 
;**********************************************************************

;<AMI_FHDR_START>
;----------------------------------------------------------------------------
;
; Name:		SmmEntry.ASM
;
; Description:	File that contains the code for BSP SMM entry point
;
;----------------------------------------------------------------------------
;<AMI_FHDR_END>

.586p
.model small
.xmm

include token.equ
include SmmHdr.equ

IFNDEF MKF_SMM_THUNK_IN_CSM
MKF_SMM_THUNK_IN_CSM EQU 0
ENDIF

IFNDEF MKF_AMI_DEBUGGER_SUPPORT
MKF_AMI_DEBUGGER_SUPPORT EQU 0
ENDIF

IA32_HANDLER_LIST STRUCT
        Entry   dd ?
        Link    dd ?
IA32_HANDLER_LIST ENDS

;org 8000h
SMM SEGMENT USE16

;<AMI_PHDR_START>
;----------------------------------------------------------------------------
;
; Procedure:	SmmEntry
;
; Description:	Call any Legacy Handlers and call 32 bit protected Mode Dispatcher.
;
; Input: None
;
; Output: None
;
;----------------------------------------------------------------------------
;<AMI_PHDR_END>

;To make assembler happy.
; SmmThunkData will have an address of 0, but a different segment.
SmmThunkData equ $
SmmEntry:
        jmp SmmStart
align 4
SmmEntryData			label dword
        SmmEntryInit SMM_ENTRY_INIT_STRUCT < \
            1, \
            SmmEntryEnd - SmmEntry, \
            GDT_DESC_FIXUP - SmmEntry, \
            L_CODE_SEL_FIXUP - SmmEntry, \
            TSS_SEL_FIXUP - SmmEntry, \
            THUNK - SmmEntry, \
            SmmThunkEnd - THUNK, \
            -1  \
        >
SmmStart:
;Note use cs override on data access. This code may be executed above 1MB.
        mov     ax, cs
        mov     ds, ax
        mov     ss, ax
        cld

IF MKF_SMM_CACHE_SUPPORT
IFNDEF MKF_NEHALEM_CPU_MODULE
        ; *************** CACHE ENABLE **************
;-----------
;HT support
;-----------
        ;TODO: Move HT detection to SMM Base and out of SMM entry.

        mov     eax, -1
        cmp     cs:(SMM_ENTRY_INIT_STRUCT ptr [SmmEntryInit + 8000h]).Ht0, eax
        jne     ht0_flag_is_init

        mov     eax, 1  ;default true
        mov     cs:(SMM_ENTRY_INIT_STRUCT ptr [SmmEntryInit + 8000h]).Ht0, eax

    	mov		eax, 1
    	cpuid
    	test	edx, 1 SHL 28		;Set if hyper-threading support.
    	jz		ht0_flag_is_init
    	shr		ebx, 16				;After shift, bl = number of logical processors
    	movzx	esi, bl				;Store # local processors.
    
    	mov		eax, 4
    	xor		ecx, ecx
    	cpuid
    	shr		eax, 26
    	inc		eax					;Number of Cores.
    
        xor     edx, edx            ;clear for div.
    	xchg	esi, eax			;esi = NumCores, eax = num #logical CPUS
    	div		esi					;#logical CPUs / NumCores
    	cmp		eax, 1
    	jle		ht0_flag_is_init
        
        mov     ebx, MKF_LOCAL_APIC_BASE + MKF_APIC_ID_REGISTER
        mov     eax, es:[ebx]
        bt      eax, 24
        jnc     ht0_flag_is_init
        xor     eax, eax        ;This not Ht0 flag, so clear.
        mov     cs:(SMM_ENTRY_INIT_STRUCT ptr [SmmEntryInit + 8000h]).Ht0, eax
ht0_flag_is_init:

        mov     esi, dword ptr cs:(SMM_ENTRY_INIT_STRUCT ptr [SmmEntryInit + 8000h]).SmmDispatcherPrivateStruct

        mov     eax, cs:(SMM_ENTRY_INIT_STRUCT ptr [SmmEntryInit + 8000h]).Ht0
        or      eax, eax
        jz      cache_enable_end    ;skip if HT

        mov     al, 1
        cmp     es:(SMM_DISPATCHER_PRIVATE_STRUCT ptr [esi]).SmrrEnable, al
        jne     non_smrr_cache
        ;Disable SMRR.
        mov     ecx, es:(SMM_DISPATCHER_PRIVATE_STRUCT ptr [esi]).SmrrMsr
        inc     ecx
        rdmsr
        btr     ax, 11       ;Disable UC SMRR. This makes the region WT by overlapping MTRR.
        wrmsr
        jmp     cache_enable_end

non_smrr_cache:
        mov     ecx, es:(SMM_DISPATCHER_PRIVATE_STRUCT ptr [esi]).TsegMsr
        or      ecx, ecx
        jz      cache_enable_end    ;Not enough/or moved MTRR to support cache.

        rdmsr
        cmp     eax, dword ptr es:(SMM_DISPATCHER_PRIVATE_STRUCT ptr [esi]).TsegMsrBase
        je      @f
        ;---Disable future cache. Validation failed.
        xor     ecx, ecx
        mov     es:(SMM_DISPATCHER_PRIVATE_STRUCT ptr [esi]).TsegMsr, ecx
        jmp     cache_enable_end
@@:
        mov     al, 4
        wrmsr   ;Make MTRR WT.
;-----------------
cache_enable_end:
; ************** END CACHE ENABLE *************
ENDIF
ENDIF

IFDEF MKF_PfatServices_SUPPORT
IF MKF_PfatServices_SUPPORT
        mov     eax, cr0
        or      al, 20h                 ;Set NE bit
        mov     cr0, eax
ENDIF
ENDIF

        mov     esi, dword ptr cs:(SMM_ENTRY_INIT_STRUCT ptr [SmmEntryInit + 8000h]).SmmDispatcherPrivateStruct
        mov     edi, dword ptr cs:(SMM_ENTRY_INIT_STRUCT ptr [SmmEntryInit + 8000h]).SmmEntryStart
        mov     ebx, dword ptr cs:(SMM_ENTRY_INIT_STRUCT ptr [SmmEntryInit + 8000h]).SmmDispatcherAddr
        mov     edx, dword ptr cs:(SMM_ENTRY_INIT_STRUCT ptr [SmmEntryInit + 8000h]).CpuNo

        mov     byte ptr cs:TSS_SEL_FIXUP + 8000h + 3, 89h

        ;Switch to protected mode
        db      66h
        lgdt    fword ptr cs:GdtDescriptor + 8000h
        mov     eax, cr0
        or      al, 1                   ;Set PE bit
        mov     cr0, eax                ;Turn on Protected Mode
        
        ;In 16 bit protected mode
        jmp $+2                         ;Clear prefetch queue
        
        mov     ax, DATA_SEL
        mov     ds, ax
        mov     es, ax
        mov     ss, ax
        mov     fs, ax
        mov     gs, ax
        
        xor	    ax, ax
        lldt    ax

		str     ax
        or      ax, ax
        jz      @f
        mov     ax,TSS_SEL
        ltr     ax
@@:

        ;Stack starts near bottom of Smm TSEG after BSP/AP entries
        mov     esp, dword ptr cs:(SMM_ENTRY_INIT_STRUCT ptr [SmmEntryInit + 8000h]).SmmStack
        and     esp, 0fffffff0h     ;guarentee 16-byte stack.

	;set cs segment
        lea     eax, [edi + offset P32Mode]
        pushd   CODE32_SEL
        push    eax
        db      66h
        retf
P32Mode::
        mov     eax, cr4
        ;or     eax, 0620h		;Enable XMM.
           db   0dh
           dd   0600h
        mov     cr4, eax

        ;mov eax, dword ptr  (SMM_DISPATCHER_PRIVATE_STRUCT ptr [esi]).SmmXmmSave
        db 8bh, 46h, SMM_DISPATCHER_PRIVATE_STRUCT.SmmXmmSave
IFNDEF EFIx64
        ;mov edx, [eax + 4 * edx]
        db 8bh, 14h, 90h
ELSE
        ;mov edx, [eax + 8 * edx]
        db 8bh, 14h, 0d0h
ENDIF

IFNDEF EFIx64
        ;lidt fword ptr (SMM_DISPATCHER_PRIVATE_STRUCT ptr [esi]).Idt
           db 0fh, 1, 5eh
           db SMM_DISPATCHER_PRIVATE_STRUCT.IDT

        ;fxsave [edx]
           db 0fh, 0aeh, 2
        push    dx      ;push edx
        sub     sp, 12  ;sub esp, 12 -- make stack 16 byte aligned
        ;Call Dispatcher

        add     di, 4   ;edi = SmmEntryInit
        push    di      ;push edi       ;Optimization will modify this stack location.
        call    bx      ;call ebx       ;SmmDispatcherAddr
        add     sp, 12 + 4  ;add esp, 12 + 4
        pop     dx      ;pop edx
        ;fxrstor [edx]
           db 0fh, 0aeh, 0ah
ELSE
        push    dx  ;push   edx  This is read later directly from [esp]

        ;mov    eax, dword ptr (SMM_DISPATCHER_PRIVATE_STRUCT ptr [esi]).PageDirectories
           db 8bh, 86h
           dd SMM_DISPATCHER_PRIVATE_STRUCT.PageDirectories
        mov     cr3, eax		;Set CR3 to first page directory pointer table

        mov     eax, cr4
        or      al, 20h		;Enable PAE.
        mov     cr4, eax

	;Enable long mode in msr register. Doesn't actually enter long mode yet.

        ;mov    ecx, 0c0000080h
           db   0b9h
           dd   0C0000080h
        rdmsr
        ;bts    eax, 8	
           db 0Fh, 0BAh, 0E8h, 08h
        wrmsr

        ;Enable paging
        mov     eax, cr0
        ;bts    eax, 31
           db 0Fh, 0BAh, 0E8h, 1fh
        ;btr    eax, 16                 ;Clear WT bit. This affects paging.
           db 0fh, 0bah, 0f0h, 10h
        mov     cr0, eax                ;Now in long mode compatiblity.
        jmp     @f
@@:

	;set cs segment
        ;lea     eax, [edi + offset long_mode_64]
           db 8dh, 87h
           dd offset long_mode_64
        ;push   CODE64_SEL
		   db 68h
		   dd CODE64_SEL
        push    ax      ;push eax
        retf

long_mode_64:
        ;in 64-bit long mode
        
        ;mov    rax, 0ffffffffh
            db 48h, 0b8h
            dq 0ffffffffh

        db 48h
        and     bx, ax         ;and rbx, rax
        db 48h
        and     dx, ax         ;and rdx, rax
        db 48h
        and     si, ax         ;and rsi, rax
        db 48h
        and     di, ax         ;and rdi, rax
        db 48h
        and sp, ax             ;and esp, rax

        ;mov    edx, [rsp]
            db 8bh, 14h, 24h
        ;fxsave [rdx]
            db 48h, 0fh, 0aeh, 2

        ;align stack by 16-bytes, sub 0ch and reserve stack for caller.
        sub     sp, 0ch + 20h      ;sub    esp, 12 + 20

        ;Call Dispatcher

        ;lidt fword ptr (SMM_DISPATCHER_PRIVATE_STRUCT ptr [rsi]).Idt
           db 0fh, 1, 5eh
           db SMM_DISPATCHER_PRIVATE_STRUCT.IDT

        add     di, 4       ;di = SmmEntryInit

        db      48h
        mov     cx, di      ;mov rcx, rdi

        call    bx          ;call rbx

        ;restore stack
        add     sp, 0ch + 20h

        ;mov    edx, [rsp]
            db 8bh, 14h, 24h

        ;fxrstor [rdx]
            db  48h, 0fh, 0aeh, 0ah

        ;lea rax, [@f];
            db 48h, 8Dh, 05
            dd offset @f - $ - 4
        ;push CODE32_SEL
			db 68h
			dd CODE32_SEL
        db      48h
        push    ax      ;push rax
        db      48h
        retf            ;retq       ;switch to compatibility mode.
@@:
        pop     dx      ;pop edx
endif
;---We are in 32-bit protected or 32-bit compatibility mode.---
;C calls preserve ESI, EDI, EBX, and EBP.
;esi = SMM_DISPATCHER_PRIVATE_STRUCT
;edi = SMM_ENTRY_INIT_STRUCT

IFDEF MKF_PfatServices_SUPPORT
IF MKF_PfatServices_SUPPORT
        mov     eax, cr0
        and     al, 0DFh                 ;Clear NE bit
        mov     cr0, eax
ENDIF
ENDIF

IF MKF_SMM_CACHE_SUPPORT
IFNDEF MKF_NEHALEM_CPU_MODULE
; **************** CACHE DISABLE ****************
        ;mov     al, byte ptr (SMM_ENTRY_INIT_STRUCT ptr [edi]).Ht0
            db 8Ah, 47h
            db SMM_ENTRY_INIT_STRUCT.Ht0
        or      al, al              ;or al, al
        jz      cache_disable_end   ;skip if HT

        mov     al, 1
        ;cmp     (SMM_DISPATCHER_PRIVATE_STRUCT ptr [esi]).SmrrEnable, al
            db 38h, 46h
            db  SMM_DISPATCHER_PRIVATE_STRUCT.SmrrEnable
        jne     non_smrr_cache2
        ;Disable SMRR.

        ;mov     ecx, (SMM_DISPATCHER_PRIVATE_STRUCT ptr [esi]).SmrrMsr
            db  08bh, 4eh
            db  SMM_DISPATCHER_PRIVATE_STRUCT.SmrrMsr
        inc     cx    ;inc ecx

        rdmsr
        bts     eax, 11       ;Disable UC SMRR. This makes the region WT by overlapping MTRR.
        wrmsr
        jmp     cache_disable_end

non_smrr_cache2:
        ;mov     ecx, (SMM_DISPATCHER_PRIVATE_STRUCT ptr [esi]).TsegMsr
            db  8bh, 4eh
            db  SMM_DISPATCHER_PRIVATE_STRUCT.TsegMsr
        or      cx, cx      ;or ecx, ecx
        jz      cache_disable_end    ;Not enough/or moved MTRR to support cache.

        rdmsr
        xor     al, al
        wrmsr   ;Make MTRR UC
;-----------------
cache_disable_end:
; ************** END OF CACHE DISABLE ************
ENDIF
ENDIF
    rsm

align 16
GDT_BASE:
NULL_SEL equ	$-GDT_BASE	 ;NULL Selector 0
        dd 0, 0

DATA_SEL equ	$-GDT_BASE     	; Selector 8, Data 0-ffffffff 32 bit
        dd 0000ffffh
        dd 00cf9300h

CODE32_SEL equ	$-GDT_BASE     	; Selector 10h, CODE 0-ffffffff 32 bit
        dd 0000ffffh
        dd 00cf9b00h

; We only need this because Intel DebugSupport driver
; (RegisterPeriodicCallback function) assumes that selector 0x20 is valid
; The funciton sets 0x20 as a code selector in IDT
;
; System data segment descriptor
;
SYS_DATA_SEL equ     $ - GDT_BASE       ; Selector [0x18]
        dd 0000FFFFh	;0 - f_ffff
        dd 00cf9300h	;data, expand-up, notwritable, 32-bit

; System code segment descriptor
SYS_CODE_SEL equ     $ - GDT_BASE       ; Selector [0x20]
        dd 0000FFFFh	;0 - f_ffff
        dd 00cf9b00h	;data, expand-up, writable, 32-bit
SPARE3_SEL  equ $-GDT_BASE              ; Selector [0x28]
        dd 0, 0
SYS_DATA64_SEL    equ $-GDT_BASE        ; Selector [0x30]
        dd 0000FFFFh
        dd 00cf9300h
CODE64_SEL    equ $-GDT_BASE        	; Selector [0x38]
        dd 0000FFFFh
        dd 00af9b00h
TSS_SEL  equ $-GDT_BASE              	; Selector [0x40]
        dw 0067h 
TSS_SEL_FIXUP:
        dw 0000h 
        dd 00008900h
L_DATA_SEL equ	$-GDT_BASE
        dd 0000ffffh
        dd 008f9300h
L_CODE_SEL equ	$-GDT_BASE
        dw 0ffffh
L_CODE_SEL_FIXUP:
        dd 09a000000h       ;Fix up by adding SMM BASE + 8000h
        dw 0
GDT_SIZE equ     $-GDT_BASE		;Size of Descriptor Table

GdtDescriptor:
        dw GDT_SIZE - 1                ;GDT limit
GDT_DESC_FIXUP:
        dd offset GDT_BASE             ;Fix up by adding SMM BASE + 8000h
SmmEntryEnd:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;<AMI_PHDR_START>
;---------------------------------------------------------------------------
;
; Procedure: Thunk
;
; Description: The thunk code is copied to below 1MB and used in SMM to thunk to
;  16-bit mode.
;
; Input: None
;
; Output: None
;---------------------------------------------------------------------------
;<AMI_PHDR_END>

THUNK:
    jmp short skip_thunk_fixup_data
    dw offset thunk_data_fixup - offset THUNK
    dw offset thunk_data_fixup2 - offset THUNK
skip_thunk_fixup_data:
IFDEF EFIx64
;Starts in 64-bit mode. Need to turn this into machine code.
        push    dx      ;rdx
;---Jump from long mode to compatiblity mode---
        push    10h
        ;push   eip  (call next instruction)
            db  0e8h
            dd  0
        ;add    dword ptr [rsp], 6  ;rip = ComMode.
            db 83h, 04h, 24h
            db 6
        db 48h
        retf
ComMode:
;---Go to protected mode---
        mov     eax, cr0
        btr     ax, 31          ;btr eax, 31
        mov     cr0, eax        ;Now in protected mode.
        jmp     $+2

        ;mov    ecx, 0c0000080h
           db 0b9h
           dd 0c0000080h
        rdmsr
        btr     ax, 8   ;btr eax, 8
        wrmsr
ENDIF
;Starts in protected mode. Need to turn this into machine code.
        db      60h     ;pushad
        db      9ch     ;pushfd

        ;mov ebx, ThunkData
            db 0bbh
thunk_data_fixup:
            dd 0

if MKF_SMM_THUNK_IN_CSM EQ -1
        ;movzx   eax, word ptr [40eh]   ;Get segment of ebda.
            db  0Fh, 0B7h, 05
            dd  40eh
        shl     ax, 4                   ;shl eax, 4     ;Get address ebda
        add     bx, ax                  ;add ebx, eax
endif

;--Save Data--
        ;mov     ds:(SMM_THUNK_DATA ptr [ebx]).StackSave, esp       ;Save 32 bit stack address of this module.
            db  89h, 63h
            db  SMM_THUNK_DATA.StackSave
        ;sgdt    ds:(SMM_THUNK_DATA ptr [ebx]).GdtSave
            db  0Fh, 01h, 43h
            db  SMM_THUNK_DATA.GdtSave
	    ;sidt    ds:(SMM_THUNK_DATA ptr [ebx]).IdtSave
            db  0Fh, 01h, 4Bh
            db  SMM_THUNK_DATA.IdtSave
;---Copy Stack parameters of LegacyBiosFarCall---
	    ;mov    ecx, ds:(SMM_THUNK_DATA ptr [ebx]).StackParm.StackSize
            db  8Bh, 4Bh
            db  SMM_THUNK_DATA.StackParm.StackSize

        or      cx, cx	                                        ;32-bit or ecx, ecx
        jz      no_stack_to_copy

        ;movzx   edi, ds:(SMM_THUNK_DATA ptr [ebx]).Below1MStack
            db  0Fh, 0B7h, 7Bh
            db  SMM_THUNK_DATA.Below1MStack
        add     di, bx  ;32-bit add edi, ebx
        sub     di, cx	;32-bit sub edi, ecx

        ;mov     esi, ds:(SMM_THUNK_DATA ptr [ebx]).StackParm.StackPtr
            db  8Bh, 73h
            db SMM_THUNK_DATA.StackParm.StackPtr


        rep movsb
no_stack_to_copy:

;--Get Real mode address to switch to--
        ;call    get_eip  ;push eip
            db  0E8h
            dd  0h
get_eip:pop dx      ;pop     edx
        ;add     edx, offset RealMode - offset get_eip
            db  83h, 0C2h
            db  offset RealMode - offset get_eip

;--Switch to real mode--	
       ;lidt   fword ptr ds:(SMM_THUNK_DATA ptr [ebx]).LegacyIdtDesc
            db 0Fh, 01h, 5Bh
            db SMM_THUNK_DATA.LegacyIdtDesc
       ;Jump to L_CODE_SEL:next
        ;push  L_CODE_SEL
           db 6ah
           db L_CODE_SEL
        ;push   offset next - offset THUNK
           db   68h
           dd   offset next - offset THUNK
        retf
next:
        mov     ax, L_DATA_SEL
        mov     ds, ax
        mov     es, ax
        mov     ss, ax
        mov     fs, ax
        mov     gs, ax

        mov     eax, cr0
        and     al, 0feh
        mov     cr0, eax
        shr     ebx, 4
        mov     ds, bx
        mov     ss, bx
;---------------Real mode operations-----------
        movzx   esp, ds:(SMM_THUNK_DATA ptr [SmmThunkData]).Below1MStack
        sub     sp, word ptr ds:(SMM_THUNK_DATA ptr [SmmThunkData]).StackParm.StackSize

        ;--jump to real mode--
        mov     eax, edx
        shr     edx, 4      ;edx = segment
        and     eax, 0fh    ;eax = ip
        push    dx
        push    ax
        retf
RealMode:
        mov     ax, cs
        mov     es, ax
        mov     fs, ax
        mov     gs, ax

        ;---copy registers for FarCall---
        mov     eax, ds:(SMM_THUNK_DATA ptr [SmmThunkData]).regs.reg_eax
        mov     ebx, ds:(SMM_THUNK_DATA ptr [SmmThunkData]).regs.reg_ebx
        mov     ecx, ds:(SMM_THUNK_DATA ptr [SmmThunkData]).regs.reg_ecx
        mov     edx, ds:(SMM_THUNK_DATA ptr [SmmThunkData]).regs.reg_edx
        mov     esi, ds:(SMM_THUNK_DATA ptr [SmmThunkData]).regs.reg_esi
        mov     edi, ds:(SMM_THUNK_DATA ptr [SmmThunkData]).regs.reg_edi
        mov     ebp, ds:(SMM_THUNK_DATA ptr [SmmThunkData]).regs.reg_ebp
        
        push    ds:(SMM_THUNK_DATA ptr [SmmThunkData]).regs.reg_es
        pop     es
        push    ds:(SMM_THUNK_DATA ptr [SmmThunkData]).regs.reg_fs
        pop     fs
        push    ds:(SMM_THUNK_DATA ptr [SmmThunkData]).regs.reg_gs
        pop     gs

    ;Generally, flags are not used to pass information as a parameter only to return information.
    ;Uninialized flags in the parameters may cause an exception if they are set.

        cmp     word ptr ds:(SMM_THUNK_DATA ptr [SmmThunkData]).StackParm.StackSize, 0
        jne     @f
        ;If no stack, push flags to imitate INT xx, in case of using call to emulate interrupt.
        pushf
@@:
    ;---Push return cs:ip---
        push    cs
        call    store_ret_ptr       ;push ip
store_ret_ptr:
        push    bp                  ;save bp for temp use.
        mov     bp, sp
        
        add     word ptr [bp + 2], ret_from_16bit - store_ret_ptr  ;Change return address in stack.
        pop     bp                  ;restore bp

    ;----------------------
    ;---Call 16-bit code---
    ;----------------------

        ;push the function to stack.
        push    ds:(SMM_THUNK_DATA ptr [SmmThunkData]).FarCallPtr16.seg_offset
        push    ds:(SMM_THUNK_DATA ptr [SmmThunkData]).FarCallPtr16.ptr_offset

        ;This is done last because of ds is used.
        push    ds:(SMM_THUNK_DATA ptr [SmmThunkData]).regs.reg_ds
        pop     ds

        ;---Execute 16-bit call---
        retf    ;Execute far call
ret_from_16bit:
        push    ds      ;Save orginal ds
if MKF_SMM_THUNK_IN_CSM EQ -1
        push    ax
        xor     ax, ax
        mov     fs, ax
        movzx   eax, word ptr fs:[40eh]
        
        ;add   ax, thunk_data_fixup2
            db     5
thunk_data_fixup2:
            dw 0
        mov     ds, ax        
        pop     ax
else
        ;push    ThunkData2  ;ds = thunk data >> 4
            db 68h
thunk_data_fixup2:
            dw 0
        pop     ds 
endif

        pop     ds:(SMM_THUNK_DATA ptr [SmmThunkData]).regs.reg_ds


        mov     ds:(SMM_THUNK_DATA ptr [SmmThunkData]).regs.reg_eax, eax
        mov     ds:(SMM_THUNK_DATA ptr [SmmThunkData]).regs.reg_ebx, ebx
        mov     ds:(SMM_THUNK_DATA ptr [SmmThunkData]).regs.reg_ecx, ecx
        mov     ds:(SMM_THUNK_DATA ptr [SmmThunkData]).regs.reg_edx, edx
        mov     ds:(SMM_THUNK_DATA ptr [SmmThunkData]).regs.reg_esi, esi
        mov     ds:(SMM_THUNK_DATA ptr [SmmThunkData]).regs.reg_edi, edi
        mov     ds:(SMM_THUNK_DATA ptr [SmmThunkData]).regs.reg_ebp, ebp

       	pushfd
       	pop     ds:(SMM_THUNK_DATA ptr [SmmThunkData]).regs.reg_flags

        mov     ax, es
        mov     ds:(SMM_THUNK_DATA ptr [SmmThunkData]).regs.reg_es, ax

        mov     ax, fs
        mov     ds:(SMM_THUNK_DATA ptr [SmmThunkData]).regs.reg_fs, ax

        mov     ax, gs
        mov     ds:(SMM_THUNK_DATA ptr [SmmThunkData]).regs.reg_gs, ax

;--------------End Real Mode operations---------

        xor     ebx, ebx
        mov     bx, ds
        shl     ebx, 4

        xor     edx,edx
        mov     dx, cs
        shl     edx, 4      ;edx+ already 0

        ;--Switch to protected mode--
        db      66h
        lgdt    fword ptr ds:(SMM_THUNK_DATA ptr [SmmThunkData]).GdtSave
        
        mov     eax, cr0
        or      al, 1			;Set PE bit
        mov     cr0, eax      		;Turn on Protected Mode
        
;---Switch into protected mode---
        ;jmp 10:TP32MODE to set cs segment

        mov     eax, edx
        call    get_eip2  ;push ip
get_eip2:
        xor     edx, edx
        pop     dx
        add     edx, offset TP32Mode - offset get_eip2
        add     edx, eax    ;eip = cs * 10h + offset
        pushd   10h
        push    edx
        db 66h
        retf
TP32Mode::
;---In protected mode.---
        ;mov    ax, DATA_SEL
           db 66h, 0b8h
           dw DATA_SEL
        db 66h, 8eh, 0d8h	;mov     ds, ax
        db 66h, 8eh, 0c0h	;mov     es, ax
        db 66h, 8eh, 0d0h	;mov     ss, ax
        db 66h, 8eh, 0e0h	;mov     fs, ax
        db 66h, 8eh, 0e8h	;mov     gs, ax
        
        ;lidt	fword ptr ds:(SMM_THUNK_DATA ptr [ebx]).IdtSave
            db 0Fh, 01h, 5Bh
            db SMM_THUNK_DATA.IdtSave

        ;mov    esp, ds:(SMM_THUNK_DATA ptr [ebx]).StackSave	;Get original stack back.
            db  8Bh, 63h
            db  SMM_THUNK_DATA.StackSave

        xor	    ax, ax			;xor eax, eax  short/quick way to set EAX = 0
        lldt    ax			    ;(source operand == 0) => LDTR is invalid
        db 9dh		;popfd
        db 61h		;popad

IFDEF EFIx64
;---Switch to long mode---
        ;mov ecx, 0c0000080h
           db 0b9h
           dd 0c0000080h
        rdmsr
        bts     ax, 8           ;bts eax, 8
        wrmsr

        mov     eax, cr0
        bts     ax, 31          ;bts eax, 31
        mov     cr0, eax        ;Now in compatibility mode.
        jmp $+2

        ;jmp 38:LongModeThk to set cs segment
        ;call    get_eip3  ;push eip
            db  0E8h
            dd  0h
get_eip3:
        pop     dx        ;pop  edx (edx = eip)
        ;add     edx, offset LongModeThk - offset get_eip3
            db  83h, 0C2h
            db  offset LongModeThk - offset get_eip3
        push    38h
        push    dx  ;push edx
        retf
LongModeThk:
        ;mov    ax, DATA_SEL
           db 66h, 0b8h
           dw DATA_SEL
        db 66h, 8eh, 0d8h	;mov     ds, ax
        db 66h, 8eh, 0c0h	;mov     es, ax
        db 66h, 8eh, 0d0h	;mov     ss, ax
        db 66h, 8eh, 0e0h	;mov     fs, ax
        db 66h, 8eh, 0e8h	;mov     gs, ax

        pop     dx      ;pop rdx
ENDIF
        ret
SmmThunkEnd:
SMM ENDS

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
