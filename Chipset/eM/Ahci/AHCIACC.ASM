
        TITLE   AHCIACC.ASM - AHCI Register/Memory Acccess Routines

;****************************************************************************
;****************************************************************************
;**                                                                        **
;**             (C)Copyright 1985-2014, American Megatrends, Inc.          **
;**                                                                        **
;**                          All Rights Reserved.                          **
;**                                                                        **
;**                 5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093      **
;**                                                                        **
;**                          Phone (770)-246-8600                          **
;**                                                                        **
;****************************************************************************
;****************************************************************************

;****************************************************************************
; $Header: /Alaska/SOURCE/Modules/AHCI/INT13/CSP/AHCIACC.ASM 14    12/08/14 5:58a Anbuprakashp $
;
; $Revision: 14 $
;
; $Date: 12/08/14 5:58a $
;****************************************************************************
; Revision History
; ----------------
; $Log: /Alaska/SOURCE/Modules/AHCI/INT13/CSP/AHCIACC.ASM $
; 
; 14    12/08/14 5:58a Anbuprakashp
; [TAG]  		EIP192297
; [Category]  	Improvement
; [Description]  	Replacing SmmGetMemoryType usage in AHCI driver with
; AmiBufferValidationLib
; [Files]  		AhciInt13Smm.c, AhciInt13Smm.mak, AHCIACC.ASM
; 
; 13    11/24/14 11:54p Kapilporwal
; [TAG]  		EIP191939
; [Category]  	Improvement
; [Description]  	Issue about BIG_REAL_MODE_MMIO_ACCESS of AHCI module
; [Files]  		AI13.bin
; AHCIACC.ASM
; AhciInt13Dxe.c
; AhciInt13Dxe.dxs
; AhciInt13Smm.c
; AhciInt13Smm.cif
; AhciInt13Smm.dxs
; AhciInt13Smm.h
; AhciInt13Smm.mak
; AhciInt13Smm.sdl
; AInt13.c
; Aint13.cif
; AInt13.h
; AhciSmm.c
; AhciSmm.h
; AhciSmmProtocol.h
; 
; 12    7/01/14 2:23a Nagadineshk
; [TAG]  		EIP172162 
; [Category]  	Bug Fix
; [Severity]  	Important
; [Symptom]  	Can't install legacy windows if achiacc.obj is not first
; one of CSM_OEM16_OBJS elink
; [RootCause]  	Wrong offset of Newly Hooked Interrupt(CPU Exception
; Interrupt) address loaded in Interrupt vector table.
; [Solution]  	Stored Correct Offset value in IVT
; [Files]  		AHCIACC.ASM
; 
; 11    6/20/14 6:54a Nimishsv
; Recheck-in
; 
; 10    12/17/13 7:06a Nimishsv
; [TAG]  		EIP131322 
; [Category]  	Improvement
; [Description] Improve S4 resume time with PCIE SSD
; under Win7, reported that if enable AHCIMMIOSMM_SUPPORT,
; and then S4 resume time is very long(about 50s) with win 7.
; (Add support for accessing MMIO region using BIG real mode)
; [Files]  		AhciMmioSmm.sdl, AHCIACC.asm
; 
; 9     8/02/12 8:14a Deepthins
; [TAG]  		EIP93480
; [Category]  	Bug Fix
; [Symptom]  	AHCI legacy support module is corrupting the memory.
; [RootCause]  	AHCI legacy support module is corrupting the memory as it
; was using wrong offset for storing the base address.
; [Solution]  	Properly calculating offset for storing the base address.
; [Files]  		AINT13.EQU, AInt13.c, AInt13.h and AHCIACC.ASM
; 
; 8     1/13/12 12:20a Deepthins
; [TAG]  		EIP78099
; [Category]  	Improvement
; [Description]  	Handle multiple AHCI controller in legacy.
; [Files]  		Aint13.sdl , AInt13.c , AInt13.h , AHCIACC.ASM , AHCI.EQU ,
; AINT13.bin (AHCIACC.ASM , AINT13.EQU)
; 
; 7     2/10/11 10:52a Rameshr
; [TAG]  		EIP53704
; [Category]  	Improvement
; [Description]  	AMI headers update for Alaska Ahci Driver
; [Files]  		AHCIACC.ASM
; HACCESS.EQU
; AHCI.EQU
; AINT13.EQU
; AInt13Csp.c
; 
; 6     6/21/10 5:34a Rameshr
; AHCI Legacy booting through MMIO reg.
; EIP 38444
; 
; 5     5/28/08 9:43a Rameshraju
; Updated the AMI Address.
; 
; 4     3/28/08 10:03a Olegi
; 
; 3     3/27/08 5:33p Olegi
; 
; 2     19/12/07 4:28p Anandakrishnanl
; Modified the relative offsets to be absolute.
; 
; 1     12/07/07 11:17a Olegi
;
;****************************************************************************

;----------------------------------------------------------------------------
;       INCLUDE FILES
;----------------------------------------------------------------------------
        include ahci.equ
        include haccess.equ
        include aint13.equ
        include token.equ

	FLAT_MODE_INDEX equ 08h
	REAL_MODE_INDEX equ 10h
;----------------------------------------------------------------------------
;       EXTERNS USED
;----------------------------------------------------------------------------
.586p
OEM16_CSEG SEGMENT PARA PUBLIC 'CODE' USE16
        ASSUME cs:OEM16_CSEG, ds:OEM16_CSEG
;-------------------------------------------------------------------------
        PUBLIC AhciApiModuleStart
AhciApiModuleStart LABEL BYTE
        jmp     SHORT AhciCsm16Api
        dw      AhciDataStart - AhciApiModuleStart 


;----------------------------------------------------------------------------
; IMPORTANT: Do not put any OEM/CHIPSET code above this, the above code and
;            and data are at fixed locations.
;----------------------------------------------------------------------------

;-------------------------------------------------------------------------
;                       AHCI_CSM16_API_Start
;----------------------------------------------------------------------------
; This routine is implementation of the CSM16 API #7.
; Input:        CX      80h   - ReadRegisterDword call
;                       00h   - WriteRegisterDword call
;                       01h   - WaitForFisRecRun call
;               For read/write functions:
;                   SS:SP+3Eh (originally ESI)  HBA Base Address
;                   SS:SP+42h (originally EBX)  Port#, Register Offset
;                       Bit31-16 = Port# (0-based)
;                                  FFFF for Generic Host Control Register
;                       Bit15-0  = Register offset
;                   SS:SP+46h  (originally EAX) Data to be written
;               For WaitForFisRecRun function:
;                   No input
; Output:       NC      Successful
;                       EAX     Data read
;               CY      Error
; Register Usage: Do not destroy any register except EAX
;
;----------------------------------------------------------------------------
;
AhciCsm16Api  PROC FAR PUBLIC
; Adjust current IP so that the data offsets are valid
        call    $+3     ; Push curent IP
        pop     bx		; Get current IP in BX
        shr     bx, 4
        mov     ax, cs      ; Always x000h
        add     ax, bx      ; New CS
        push    ax
        push    newOffset-AhciApiModuleStart
        retf            ; Execute from new CS:IP

newOffset:
        push    bp
        mov     bp, sp
        mov     eax, ss:[bp+48h]    ; Data to be written (ignored for Read function)
        mov     ebx, ss:[bp+44h]    ; Port#
        mov     esi, ss:[bp+40h]    ; HBA Base Address

        cmp     cx, 0
        jz      aca_WriteCall
        cmp     cx, 80h
        jnz     aca_WaitForFisRecRun
        call    ReadRegisterDword
        jmp     SHORT aca_Exit
aca_WaitForFisRecRun:
        call    WaitForFisRecRun
        jmp     SHORT aca_Exit
aca_WriteCall:
        call    WriteRegisterDword

aca_Exit:
        pop     bp

; Adjust sp as if we returned to csm16_func_ret
        add     sp, 4   ; cs:ip of F000:csm16_func_ret

; Save EAX, restore it after popad
        push    eax
        pop     ds
        pop     gs
;csm16_func_ret:
        popad
        push    gs
        push    ds
        pop     eax

        pop     gs
        pop     fs
        pop     es
        pop     ds

;csm16_exit:
        popf
        pop     ds
        pop     si
    
        add     sp, 2   ; Do not "pop ax", preserving return code

; Prepare for FAR return - fetch the CS and patch the segment for RETF
        mov     cx, WORD PTR ss:[bp+1ah]
        mov     WORD PTR ss:[bp+06h], cx
; Restore CX
        mov    cx, WORD PTR ss:[bp+18h] 
        mov    dx, WORD PTR ss:[bp+16h] ;Restore Dx

        pop     bp
        add     sp, 4
        clc
        retf    18

AhciCsm16Api  ENDP

;
;-------------------------------------------------------------------------
;                       ReadRegisterDword
;----------------------------------------------------------------------------
; This routine reads the register.
; Input:        ESI     HBA Base Address
;               EBX     Port#, Register Offset
;                       Bit31-16 = Port# (0-based)
;                                  FFFF for Generic Host Control Register
;                       Bit15-0  = Register offset
; Output:       NC      Successful
;                       EAX     Data read
;               CY      Error
; Register Usage: Do not destroy any register except EAX
;
;----------------------------------------------------------------------------
;
ReadRegisterDword_FAR   PROC    FAR     PUBLIC
        call    ReadRegisterDword       ; EAX = data read if read
        ret
ReadRegisterDword_FAR   ENDP

ReadRegisterDword       PROC    NEAR    PUBLIC
        push    esi
        call    CalculateRegisterOffset ; ESI = register offset from base

        push    dx                      ; Dx has the controller number
        cli
        push    bx                      ; Save bx value in stack
        push    ax                      ; Save ax value in stack
        mov     ax, 0
        mov     al, dl                  ; Move the controller no into al
        mov     bl, 8
        mul     bl                      ; Multiply it with 8 as AHCI_ACCESS\
                                        ; structure size is 8
        mov     bx, ax                  ; Move the offset into bx
        pop     ax                      ; Restore ax
IF (MKF_AHCI_INT13_SMM_SUPPORT)
        push    ebx
        push    ecx        
        mov     ebx, dword ptr cs:[AhciDataStart - AhciApiModuleStart +4+bx] ;ebx=Data
        add     esi,ebx
IF (MKF_BIG_REAL_MODE_MMIO_ACCESS)	
    	call	ReadDWORD
ELSE
        mov     cx,1                    ;Read Function
        call    AhciGenerateSwSMI
        cmp     ecx, 0                  ; if ECX == 0, MMIO read is Success
        jz      Read_Success
        stc
        jmp     Read_Return
Read_Success:
        clc
Read_Return:
ENDIF
        pop     ecx
        pop     ebx
        jmp     Read_done
ENDIF
        mov     dx, cs:[AhciDataStart - AhciApiModuleStart +bx]              ; DX = Index Port
        push    eax
        mov     eax, esi                ; EAX = register address
        out     dx, eax                 ; Write Address
        pop     eax

        mov     dx, cs:[AhciDataStart - AhciApiModuleStart +2+bx]              ; DX = Data Port
        in      eax, dx                 ; EAX = adat

        clc                             ; NC, Successful
Read_done:
        pop     bx
        pop     dx

        pop     esi
        ret
ReadRegisterDword       ENDP
;
;----------------------------------------------------------------------------
;                       WriteRegisterDword
;----------------------------------------------------------------------------
; This routine writes the register.
; Input:        ESI     HBA Base Address
;               EBX     Port#, Register Offset
;                       Bit31-16 = Port# (0-based)
;                                  FFFF for Generic Host Control Register
;                       Bit15-0  = Register offset
;               EAX     Data to be written
; Output:       NC      Successful
;               CY      Error
; Register Usage: Do not destroy any register
;
;----------------------------------------------------------------------------
;
WriteRegisterDword_FAR  PROC    FAR     PUBLIC
        call    WriteRegisterDword
        ret
WriteRegisterDword_FAR  ENDP

WriteRegisterDword      PROC    NEAR    PUBLIC
        push    esi
        call    CalculateRegisterOffset ; ESI = register offset from base

        push    dx                      ; Dx has the controller number
        cli
        push    bx                      ; Save bx value in stack
        push    ax                      ; Save ax value in stack
        mov     ax, 0
        mov     al, dl                  ; Move the controller no into al
        mov     bl, 8
        mul     bl                      ; Multiply it with 8 as AHCI_ACCESS\
                                        ; structure size is 8
        mov     bx, ax                  ; Move the offset into bx
        pop     ax                      ; Restore ax

IF (MKF_AHCI_INT13_SMM_SUPPORT)
        push    ebx
        push    ecx
        mov     ebx, dword ptr cs:[AhciDataStart - AhciApiModuleStart +4+bx]
        add     esi,ebx
IF (MKF_BIG_REAL_MODE_MMIO_ACCESS)	
    	call	WriteDWORD
ELSE
        mov     ebx,eax                 ;Write Value
        mov     cx,2                    ;Write Function
        call    AhciGenerateSwSMI
        cmp     ecx, 0                  ; if ECX == 0, MMIO write is Success
        jz      Write_Success
        stc
        jmp     Write_Return
Write_Success:
        clc
Write_Return:
ENDIF
        pop     ecx
        pop     ebx
        jmp     Write_done
ENDIF
        mov     dx, cs:[AhciDataStart - AhciApiModuleStart +bx]              ; DX = Index Port
        push    eax
        mov     eax, esi                ; EAX = register address
        out     dx, eax                 ; Write Address
        pop     eax

        mov     dx, cs:[AhciDataStart - AhciApiModuleStart +2+bx]              ; DX = Data Port
        out     dx, eax                 ; Write dword data
        clc                             ; NC, Successful
Write_done:
        pop     bx
        pop     dx

        pop     esi
        ret
WriteRegisterDword      ENDP
;
;----------------------------------------------------------------------------
;                       CalculateRegisterOffset
;----------------------------------------------------------------------------
; This routine calculates the register offset from HBA Base.
; Input:        EBX     Port#, Register Offset within Port
;                       Bit31-16 = Port# (0-based)
;                                  FFFF for Generic Host Control Register
;                       Bit15-0  = Register offset
; Output:       ESI     Register Offset from HBA Base
; Register Usage: Do not destroy any register except ESI
;
;----------------------------------------------------------------------------
;
CalculateRegisterOffset PROC    NEAR    PRIVATE
        push    cx
        push    ebx
        mov     cx, bx                  ; CX = register offset
        shr     ebx, 16                 ; BX = Port# (0-based)
        inc     bx                      ; Port# valid?
        jz      short cro_00            ; No
        dec     bx                      ; BX = Port# (0-based)
        shl     bx, PORT_REGISTER_SET_SIZE_N
        add     bx, PORT_REGISTER_START
cro_00:
        add     bx, cx                  ; BX = Port register offset from HBA base address
        movzx   esi, bx                 ; ESI = Port register offset from HBA base address
        pop     ebx
        pop     cx
        ret
CalculateRegisterOffset ENDP

;
;----------------------------------------------------------------------------
;                       WaitForFisRecRun
;----------------------------------------------------------------------------
; This routine executes HBA wait for FIS rec run code. If not
; implemented (just ret), AHCI INT13 code will execute the default routine.
; Implement this routine for different OEM/Chipset vendor and return 0 in AL
; to override the default routine execution.
;
; Output:       AH     0 if implemented
;
;----------------------------------------------------------------------------
;
WaitForFisRecRun    PROC NEAR PUBLIC
        ret
WaitForFisRecRun    ENDP

;<AMI_PHDR_START>
;----------------------------------------------------------------------------
;
; Procedure:    AhciGenerateSwSMI 
;
; Description:  Generate the Sw SMI to read the MMIO space.
;               if the system is in big real mode, read/write the MMIO space without 
;               SwSMI  
;
; Input:        Cx = 1 - Read MMIO
;               Cx=  2 - Write MMIO 
;               Eax= Value to write in MMIO for write MMIO 
;                    
; Output:       Eax- for Read MMIO 
;
; Modified:     Ds
;
;----------------------------------------------------------------------------
;<AMI_PHDR_END>
IF (MKF_AHCI_INT13_SMM_SUPPORT)
AhciGenerateSwSMI    PROC NEAR PUBLIC
        call    Check_Big_Real_mode
        jc      NotBigReadMode
        push    es
        push    0
        pop     es

        cmp     cx,1
        je      ReadMmio
        mov     dword ptr es:[esi],eax  ;Write MMIO  
        pop     es
        ret
ReadMmio:
        mov     eax,dword ptr es:[esi]  ;Read MMIO
        pop     es
        ret
NotBigReadMode:

        mov     dx,MKF_SW_SMI_IO_ADDRESS     
        mov     al,MKF_AHCI_INT13_SMM_SWSMI_VALUE
        out     dx,al                   ;Generate Sw SMI to Read/Write MMIO
        jmp     $+2
        ret
AhciGenerateSwSMI    ENDP

;-------------------------------------------------------------------------
;			ReadDWORD
;-------------------------------------------------------------------------
; This routine reads DWORD from MMIO.
; Input:	ESI	HBA Base Address
;
; Output:	NC	Successful
;			EAX	Data read
;			CY	Error
; Register Usage: Do not destroy any register except EAX
;
;-------------------------------------------------------------------------
ReadDWORD	PROC	NEAR	PUBLIC

	push	ds

	push	0
	pop	ds

	push	esi

; Save original values of registers in stack	
	push	ebx
	push	es
	push	di
	
; Save a dword from 5000h
	mov	bx, 5000h
	mov	es, bx
	mov	di, 00h
	mov	ebx, dword ptr es:[di]

	push	ebx

	mov	byte ptr es:[di], 00h
; Switching to Big Real Mode
	call	Switch_Big_Real_Mode
	
; Reading DWORD from Hba_base_address and store in EAX
	mov	eax, dword ptr ds:[esi]

	push	eax
	movzx	eax, byte ptr es:[di]
	and	eax, 01h
	jz	rdw_done
; Switch back from Big Real mode
	call	Switch_Original_Mode

rdw_done:
	pop	eax

	push	eax
	movzx	eax, byte ptr es:[di]
	and	eax, 10b
	jz	org_g20
	call	DisblGateA20
org_g20:
	pop	eax

	pop	ebx
; Restore the original values stored in stack
	mov	dword ptr es:[di], ebx

	pop	di
	pop	es
	pop	ebx

	pop	esi

	pop	ds
	clc

	ret
ReadDWORD	ENDP

;-------------------------------------------------------------------------
;			WriteDWORD
;-------------------------------------------------------------------------
; This routine writes DWORD in MMIO space.
; Input:	EAX	Data to be written
;
; Output:	ESI	HBA Base Address
;			NC	Successful
;			CY	Error
;
; Register Usage: Do not destroy any register except EAX
;
;-------------------------------------------------------------------------
WriteDWORD	PROC	NEAR	PUBLIC
	push	ds

	push	0
	pop	ds

	push	esi

; Save original values of registers in stack
	push	ebx
	push	es
	push	di
	
; Save a dword from 5000h
	mov	bx, 5000h
	mov	es, bx
	mov	di, 00h
	mov	ebx, dword ptr es:[di]

	push	ebx

	mov	byte ptr es:[di], 00h
; Switching to Big Real Mode
	call	Switch_Big_Real_Mode
	
; Writing DWORD stored in EAX into Hba_base_address
	mov	dword ptr ds:[esi],eax

	push	eax
	movzx	eax, byte ptr es:[di]
	and	eax, 01h
	jz	wdw_done
	
; Switch back from Big Real mode
	call	Switch_Original_Mode
	
wdw_done:
	pop	eax

	push	eax
	movzx	eax, byte ptr es:[di]
	and	eax, 10b
	jz	org_g201
	call	DisblGateA20
org_g201:
	pop	eax
	pop	ebx

; Restore the original values stored in stack
	mov	dword ptr es:[di], ebx

	pop	di
	pop	es
	pop	ebx

	pop	esi

	pop	ds
	clc

	ret
WriteDWORD	ENDP

;----------------------------------------------------------------------------
;<AMI_PHDR_START>
;----------------------------------------------------------------------------
;
; Procedure:    Switch_Big_Real_Mode
;
; Description:  Switch to Big real Mode. 
;
; Input:        None 
;                    
; Output:       
;
; Modified:     DS, ES
;
;----------------------------------------------------------------------------
;<AMI_PHDR_END>
;----------------------------------------------------------------------------
Switch_Big_Real_Mode PROC NEAR PUBLIC

	push	di
	call    Check_Big_Real_mode
	jnc     InBigRealMode
	mov	byte ptr es:[di], 01h

InBigRealMode:

	mov	di, FLAT_MODE_INDEX                          ;Index for flat mode
	call	GotoProtectedMode

	pop	di
    ret

Switch_Big_Real_Mode ENDP

;----------------------------------------------------------------------------
;<AMI_PHDR_START>
;----------------------------------------------------------------------------
;
; Procedure:    Switch_Original_Mode
;
; Description:  Switch to Original Mode. 
;
; Input:        None 
;                    
; Output:       
;
; Modified:     DS, ES
;
;----------------------------------------------------------------------------
;<AMI_PHDR_END>
;----------------------------------------------------------------------------
Switch_Original_Mode PROC NEAR PUBLIC

	push	di
	mov	di,	REAL_MODE_INDEX			;Real mode index
	call	GotoProtectedMode
	pop	di

    ret

Switch_Original_Mode ENDP

;<AMI_PHDR_START>
;----------------------------------------------------------------------------
;
; Procedure:	GotoProtectedMode
;
; Description:	This function jumps to protected mode for 4GB limit access
;
; Input:	None
;
; Output:	None
;
; Modified:	None
;
;----------------------------------------------------------------------------
;<AMI_PHDR_END>

GotoProtectedMode PROC NEAR PUBLIC
	push	es
	pusha
	cli				; Disable interrupts.
;  Check the GA20 status..
;  Compare 256bytes at 0:0 with FFFF:10
;  If match, GA20 is disabled else GA20 is enabled.
	push	di
	push	es
	push	ds
	push	0000h
	pop	ds			; DS = 0000.
	push	0FFFFh
	pop	es			; ES = FFFF.
	mov	cx, 100h / 4		; Number of Dwords in 256bytes.
	xor	si, si
	mov	di, 0010h
	repz	cmpsd
	pop	ds
	pop	es
	pop	di                  ;Descriptor table index in di 

	pushf				; Save GA20 status
					; ZR/NZ = disabled/enabled.
	jnz	short gtbrm_00		; GA20 is already enabled.
	
	push	di
	mov	di, 00h
	or	byte ptr es:[di], 10b
	pop	di
	call	EnblGateA20		; Enable GateA20.

gtbrm_00:
	call	go_big_mode		; Go to protected mode and comeback
					; to real mode.
	popf				; ZR/NZ = GA20 status.
	stc				; Routine went to big real mode.

gtbrm_01:
	popa
	pop	es
	ret				; Return to caller.
GotoProtectedMode ENDP

;<AMI_PHDR_START>
;----------------------------------------------------------------------------
;
; Procedure:	EnblGateA20
;
; Description:	This function enables GateA20
;
; Input:	None
;
; Output:	None
;
; Modified:	None
;
;----------------------------------------------------------------------------
;<AMI_PHDR_END>

EnblGateA20 PROC NEAR PUBLIC

	push	ax
	mov	al,02h
	out	92h, al

;  Check the GA20 status..
;  Compare 256bytes at 0:0 with FFFF:10
;  If match, GA20 is disabled else GA20 is enabled.
	push	di
	push	es
	push	ds
	push	0000h
	pop	ds			; DS = 0000.
	push	0FFFFh
	pop	es			; ES = FFFF.
	mov	cx, 100h / 4		; Number of Dwords in 256bytes.
	xor	si, si
	mov	di, 0010h
	repz	cmpsd
	pop	ds
	pop	es
	pop	di                  ;Descriptor table index in di 

	jnz	eg20_end

    mov	al, 0DFh		; Data for output port to enable A20.
	out	60h, al
	mov	al, 0D1h		
	out	64h, al

eg20_end:
	pop	ax

	ret
EnblGateA20 ENDP

;<AMI_PHDR_START>
;----------------------------------------------------------------------------
;
; Procedure:	go_big_mode
;
; Description:	This routine goes to protected mode, sets the DS, ES to the
;		given selector, comes back to real mode and sets DS, ES to 0000.
;
; Input:	DX	- Selector.
;
; Output:	Selector 00 can be used to access 4GB.
;
; Modified:	EAX.
;
; Referrals:	big_gdt.
;
;----------------------------------------------------------------------------
;<AMI_PHDR_END>

go_big_mode PROC NEAR PRIVATE

	jmp	Executable_code

;<AMI_SHDR_START>
;----------------------------------------------------------------------------
; Name:		big_gdt
;
; Type:		BYTE Array
;
; Description:	Global Descriptor Table to switch the system to/from FLAT Mode.
;		Since these routines will be called from non-shadowed system
;		ROM, the GDT must be on a QWORD boundary or else the bytes
;		will get CORRUPTED!
;
;----------------------------------------------------------------------------
;<AMI_SHDR_END>

ALIGN	8
big_gdt		LABEL	WORD
	db	8 dup (0)			;00 - Null descriptor	
	db	0FFh,0FFh,000h,000h,000h,093h,08Fh,000h	; 08h - DS descriptor for flat mode
big_gdt_end	LABEL	WORD

big_gdt_real	LABEL	WORD
	db	8 dup (0)			;00 - Null descriptor	
	db	0FFh,0FFh,000h,000h,000h,093h,000h,000h	; 08h - DS descriptor for real mode
big_gdt_real_end	LABEL	WORD

GDT_DESC	LABEL	BYTE
	dw	010h				; Length of GDT
	db	00,00h				; ptr to GDT
	db	05h,00h
GDT_DESC_END	LABEL	BYTE

Executable_code:
	
	push	ds
	push	es
	push	eax
	push	ebx
	push	ecx
	push	edx
	push	si
	push	di

; Changed for CSM - need to save SS, reload SS Limit to 64K selector and restore it
	push	bp
	mov	bp, ss

	mov	al, 8Dh			; Disable NMI
	out	70h, al
	
;;; Copy contents from 5000:00(16 bytes) into registers
	mov	ax, 5000h
	mov	es, ax
	mov	si, 00h
	mov	eax, dword ptr es:[si]
	add	si, 4
	mov	ebx, dword ptr es:[si]
	add	si, 4
	mov	ecx, dword ptr es:[si]
	add	si, 4
	mov	edx, dword ptr es:[si]
	push	eax
	push	ebx
	push	ecx
	push	edx

;;; Copy GDT to 5000h:00h 		
	mov	ax, cs
	mov	ds, ax
	cmp	di, 08h
	jne gbm_real
	mov	si, offset cs:big_gdt
	jmp gbm_flat
gbm_real:
	mov	si, offset cs:big_gdt_real
gbm_flat:
	mov	ax, 5000h
	mov	es, ax
	mov	di, 00h
	xor	cx, cx
	mov	cx, 08h 
	rep	movsw	

	lgdt	fword ptr cs:GDT_DESC
	mov	eax, cr0
	or	al, 01h
	mov	cr0, eax		; In protected mode.
	jmp	gbm_00			; Flush instruction queue - JMP (NEAR)
					; to next instruction.

gbm_00:
	mov	ax, 08h			; Selector
        mov     ds, ax                  ; DS = selector.
        mov     es, ax                  ; ES = selector.

	mov	eax, cr0		; Come back into real mode with DS,ES
	and	al, 0FEh
	mov	cr0, eax		
	jmp	gbm_01			; Flush instruction queue - JMP (NEAR)
					; to next instruction.
gbm_01:

	xor	ax, ax
	mov	ds, ax
	mov	es, ax

	pop	edx
	pop	ecx
	pop	ebx
;;; Restore contents of 5000:00h(16 bytes) from registers	
	mov	ax, 5000h
	mov	es, ax
	mov	si, 00h
	pop	eax
	mov	dword ptr es:[si], eax
	add	si, 4
	mov	dword ptr es:[si], ebx
	add	si, 4
	mov	dword ptr es:[si], ecx
	add	si, 4
	mov	dword ptr es:[si], edx

	pop	bp
	pop	di
	pop	si
	pop	edx
	pop	ecx
	pop	ebx
	pop	eax
	pop	es
	pop	ds
	ret
go_big_mode ENDP

;<AMI_PHDR_START>
;----------------------------------------------------------------------------
;
; Procedure:	DisblGateA20
;
; Description:	This function disables GateA20
;
; Input:	None
;
; Output:	None
;
; Modified:	None
;
;----------------------------------------------------------------------------
;<AMI_PHDR_END>

DisblGateA20 PROC NEAR PUBLIC

	push	ax
	mov	al,00h
	out	92h, al

;  Check the GA20 status..
;  Compare 256bytes at 0:0 with FFFF:10
;  If match, GA20 is disabled else GA20 is enabled.
	push	di
	push	es
	push	ds
	push	0000h
	pop	ds			; DS = 0000.
	push	0FFFFh
	pop	es			; ES = FFFF.
	mov	cx, 100h / 4		; Number of Dwords in 256bytes.
	xor	si, si
	mov	di, 0010h
	repz	cmpsd
	pop	ds
	pop	es
	pop	di                  ;Descriptor table index in di 

	jz	dg20_end

	mov	al, 0DDh		; Data for output port to disables A20.
	out	60h, al
	mov	al, 0D1h		
	out	64h, al

dg20_end:
	pop	ax

	ret

DisblGateA20 ENDP

;<AMI_PHDR_START>
;----------------------------------------------------------------------------
;
; Procedure:    Get_EBDA
;
; Description:  Get the EBDA Segment Address 
;
; Input:        None 
;                    
; Output:       DS: Ebda Segment 
;
; Modified:     Ds
;
;----------------------------------------------------------------------------
;<AMI_PHDR_END>
Get_EBDA PROC NEAR PUBLIC

    push    40h
    pop     ds
    mov     ds, ds:[0Eh]                ; DS - EBDA segment.
    ret

get_EBDA ENDP

;<AMI_PHDR_START>
;----------------------------------------------------------------------------
;
; Procedure:    Int0DHandler
;
; Description:  Exception 0D handler 
;
; Input:        None 
;                    
; Output:       Exception_flag Set
;
; Modified:     None
;
;----------------------------------------------------------------------------
;<AMI_PHDR_END>
Int0DHandler PROC NEAR PUBLIC
        push    ds
        call    Get_EBDA
        mov     byte ptr ds:[102h],1    ;Set the Flag in Ebda:102
        pop     ds
        pop     ax
        add     ax, 5                   ; Go to Next instruction that doesn't 
                                        ; cause Exception 
        push    ax
        iret
Int0DHandler  ENDP

;<AMI_PHDR_START>
;----------------------------------------------------------------------------
;
; Procedure:    Check_Big_Real_mode
;
; Description:  This function checks wheather system is in Big real mode
;
; Input:        None 
;                    
; Output:       Carry Set - Not in Big Real mode 
;               Carry Not Set- System is in Big Real mode                 
;
; Modified:     None
;
;----------------------------------------------------------------------------
;<AMI_PHDR_END>
Check_Big_Real_mode  PROC NEAR PUBLIC
        push    eax
        push    edi
        push    ebx
        push    es
        push    ds
        pushf
        cli

        call    Get_EBDA

        mov     byte ptr ds:[102h],0    ;EBDA:102

        push    0
        pop     es

        mov     eax, dword ptr es:[0Dh*4]
        push    eax
               
        push    cs                      ; Runtime segment
        push    offset cs:Int0DHandler-AhciApiModuleStart
        pop     eax
        mov     dword ptr es:[0Dh*4], eax


        mov     edi,0100000h
        mov     eax,dword ptr es:[edi]
        cmp     byte ptr ds:[102h],1    ;Check the exception
        je      Real_mode

        mov     edi,0
        mov     ebx,dword ptr es:[edi]
        cmp     eax,ebx
        je      Real_mode

                                        ;Read ,Write test for above 1Mb area
        mov     edi,0100000h
        mov     ebx,dword ptr es:[edi]
        mov     eax,055AA55AAh
        mov     dword ptr es:[edi],eax
        mov     eax,dword ptr es:[edi]
        mov     dword ptr es:[edi],ebx
        cmp     eax,055AA55AAh
        jne     Real_mode
        pop     eax
        mov     dword ptr es:[0Dh*4], eax
        popf    
        clc                             ;System is in Big Real Mode
        jmp     Exit_Ret

Real_mode:
        pop     eax
        mov     dword ptr es:[0Dh*4], eax
        popf
        stc                             ;System is in Real Mode
Exit_Ret:
        pop     ds
        pop     es
        pop     ebx
        pop     edi
        pop     eax
        ret        
Check_Big_Real_mode  ENDP

ENDIF

AhciDataStart   label word
AhciAccess AHCI_ACCESS (MKF_AHCI_CONTROLLER_COUNT) dup (<>)

OEM16_CSEG ENDS

END
;****************************************************************************
;****************************************************************************
;**                                                                        **
;**             (C)Copyright 1985-2014, American Megatrends, Inc.          **
;**                                                                        **
;**                          All Rights Reserved.                          **
;**                                                                        **
;**                 5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093      **
;**                                                                        **
;**                          Phone (770)-246-8600                          **
;**                                                                        **
;****************************************************************************
;****************************************************************************
