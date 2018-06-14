
    TITLE    MXMINT15.ASM -- OEM INTERRUPT IMPLEMENTATION

;**********************************************************************
;**********************************************************************
;**                                                                  **
;**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
;**                                                                  **
;**                       All Rights Reserved.                       **
;**                                                                  **
;**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
;**                                                                  **
;**                       Phone: (770)-246-8600                      **
;**                                                                  **
;**********************************************************************
;**********************************************************************
;**********************************************************************
; $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/SwitchableGraphics/Sg TPV/Sg nVidia API/MxmInt15.asm 2     9/09/12 11:12p Joshchou $
;
; $Revision: 2 $
;
; $Date: 9/09/12 11:12p $
;**********************************************************************
; Revision History
; ----------------
; $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/SwitchableGraphics/Sg TPV/Sg nVidia API/MxmInt15.asm $
; 
; 2     9/09/12 11:12p Joshchou
; [TAG]  		None
; [Category]  	Improvement
; [Description]  	Tpv module support for sharkbay.
; [Files]  		MXM30.mak
; Mxm30Dxe.dxs
; Mxm30Dxe.c
; Mxm30Efi.c
; NBCIEfi.c
; MxmInt15.asm
; MXM30.cif
; 
; 1     6/27/11 5:25a Alanlin
; [TAG]  		EIP61848
; [Category]  	New Feature
; [Description]  	Initial check-in.Integrated SwitchableGraphics Intel
; Reference code 0.6.0
; [Files]  		MXM30.cif
; MXM30.sdl
; MXM30.mak
; Mxm30Dxe.dxs
; Mxm30Dxe.c
; Mxm30Efi.c
; NBCIEfi.c
; MxmInt15.asm
; Mxm30ElkCreek4.mxm
; Mxm30ElkCreekIII.mxm
; 
; 
; 1     9/17/10 1:16p Alexp
; [TAG]    	  EIP43103 
; [Category]  Function Request
; [Severity]	  Normal
; [Symptom]    Initial check-in of SgTPV module
; [RootCause] Request to implement SG reference code .
; [Solution]	Initial check-in. 
; [Files]	
;         Mxm30.cif;*.sdl;*.mak;
;         Mxm30Dxe.c;*.dxs 
;         Mxm30efi.c
;         MxmInt15.asm
;         NbciEfi.c
;         Mxm30ElkCreek3(4).mxm
; 
; 2     6/03/10 3:07p Alexp
; 
; 1     6/03/10 2:54p Alexp
; 
; 
;**********************************************************************
INCLUDE    Token.equ
.386p

CSMOEM_CSEG SEGMENT PARA PUBLIC 'CODE' USE16
    ASSUME cs:CSMOEM_CSEG, ds:CSMOEM_CSEG

OldIntHandler    LABEL DWORD
    IntSegSav    dw    0
    IntOfsSav    dw    0

;<AMI_FHDR_START>
;---------------------------------------------------------------------------
;
; Name:        MXMINT15Proc
;
; Description:    MXM INT15 function implememtation
;                 + nVidia's NBCI Int15 supplement functions
;
;---------------------------------------------------------------------------
;<AMI_FHDR_END>

MXMINT15Proc PROC NEAR PUBLIC

    cmp        ax, 5f80h
    je        igd_mxmcall
;    cmp        ax, 5f14h   ; NVidia Vbios is calling this method. Keeping it commented out since the call is not documented 
;    je        igd_misccall
    jmp    DWORD PTR cs:[OldIntHandler]

;;igd_misccall:
;;    Output Spec Support Level
;;    BX    = 078Fh, Get Miscellaneous Status
;    cmp     bx, 078fh
;    jne     notSupported
;;    CL    = Bit map of dock, lid and AC status:
;;        Bits 7 - 3    = Reserved
;;        Bit 2    = 0, no AC power
;;            = 1, AC power active
;;        Bit 1    = 0, lid open
;;            = 1, lid closed
;;        Bit 0    = 0, not docked
;;            = 1, docked
;    mov        cl, 00000100b  ; Bitmap of supported functions.
;    jmp        short mxmExit

igd_mxmcall:

; MXM rev3.0 <=9
; NBCI      <=9
; Optimus   13
    cmp    bl, 13
    ja    short notSupported

    push    si
    movzx   si, bl
    shl     si, 1
    stc                                         ; default->not supported
    call    WORD PTR cs:[mxmFuncTable+si]        ; Call this function.
    pop     si
    jc      short notSupported
mxmExit:

    mov        ax, 05fh

notSupported:
;    sti
    clc
    retf    0002
;    iret

MXMINT15Proc    ENDP

mxmFuncTable::
    DW    OFFSET    mxmInt15Fun0
    DW    OFFSET    mxmInt15Fun1
    DW    OFFSET    mxmInt15Fun2
    DW    OFFSET    mxmInt15Fun3
    DW    OFFSET    mxmInt15Fun4
    DW    OFFSET    mxmnotSupported        ; mxmInt15Fun5
    DW    OFFSET    mxmnotSupported        ; mxmInt15Fun6
    DW    OFFSET    mxmInt15Fun7
    DW    OFFSET    mxmInt15Fun8
    DW    OFFSET    mxmInt15Fun9
    DW    OFFSET    mxmnotSupported        ; mxmInt15FunA
    DW    OFFSET    mxmnotSupported        ; mxmInt15FunB
    DW    OFFSET    mxmnotSupported        ; mxmInt15FunC
    DW    OFFSET    mxmInt15FunD            ; OptimusInt15FunD

mxmDODTable::           ; table must be consistent with _DOD method return in ASL
    DD  80000100h   ; CRT
    DD  80000400h   ; LVDS
    DD  80006300h   ; DP_B
    DD  80008301h   ; dP->HDMI B interop dongle
    DD  80008302h   ; dP->HDMI C interop dongle
    DD  80006303h   ; DP_D

DODCount      EQU (($ - mxmDODTable) / 4)

mxmFunc4String::
    DB  'MXM 3.0 VBIOS: AMI Int15 5F80 Interface', 0dh, 0ah, 0

;<AMI_PHDR_START>
;----------------------------------------------------------------------------
; Procedure:    mxmnotSupported
; Input:
; Output:
;----------------------------------------------------------------------------
;<AMI_PHDR_END>
mxmnotSupported PROC NEAR
    ret
mxmnotSupported ENDP

;<AMI_PHDR_START>
;----------------------------------------------------------------------------
; Procedure:           mxmInt15Fun0
; Description:    Function 0 Output Specification Support Level
; Input:
;    AX = 5F80h                                      ; MXM2.0, MXM2.1, MXM3.0
;    BL = 00h                                        ; MXM2.0, MXM2.1, MXM3.0
;    BH = Adapter Index                              ; MXM2.0, MXM2.1
;        0 = Primary MXM adapter (default)           ; MXM2.0, MXM2.1
;        1 = Secondary MXM adapter                   ; MXM2.0, MXM2.1
;    BH = FFh                                        ; MXM3.0
;    EBX[31:16] = Adapter ID                         ; MXM3.0
;        Bits [31:24] Bus                            ; MXM3.0
;        Bits [23:19] Device                         ; MXM3.0
;        Bits [18:16] Function                       ; MXM3.0
;    CL = Revision of the MXM software specification that is supported by the MXM module     ; MXM2.0, MXM2.1
;        Format is binary coded decimal, for example:
;        10h = 1.0, 11h = 1.1, 20h = 2.0, etc.
;    CX = Revision of the MXM software specification that is supported by the MXM module.    ; MXM3.0
;        Format is binary coded decimal, for example: 0030h = 3.0, etc
;    CX = 'OP' 4F50h Optimus Interface
;    CX = 'NB' 4E42h NBCI Interface
; Output:
;    AX =     005Fh    to indicate that the system bios supports this function               ; MXM2.0, MXM2.1, MXM3.0
;    BL  =     Revision of the MXM software specification that is supported by the system    ; MXM2.0, MXM2.1, MXM3.0
;        Format is binary coded decimal, for example:
;        10h = 1.0, 11h = 1.1, 20h = 2.0, etc.
;    CX = MXM functions supported                                            ; MXM2.0, MXM2.1, MXM3.0
;        Bit 0 = 1
;        Bit 1 = 1 if Function 1 is supported, 0 if not supported            ; MXM2.0, MXM2.1, MXM3.0
;        Bit 2 = 1 if Function 2 is supported, 0 if not supported            ; MXM2.0, MXM2.1, MXM3.0
;        Bit 3 = 1 if Function 3 is supported, 0 if not supported            ; MXM2.0, MXM2.1, MXM3.0
;        Bit 4 = 1 if Function 4 is supported, 0 if not supported            ; MXM2.1, MXM3.0
;        Bit 7 = 1 if Function 7 is supported, 0 if not supported            ; MXM3.0
;        Bit 8 = 1 if Function 8 is supported, 0 if not supported            ; MXM3.0
;        Bit 9 = 1 if Function 9 is supported, 0 if not supported            ; MXM3.0
;----------------------------------------------------------------------------
;<AMI_PHDR_END>

mxmInt15Fun0 PROC NEAR
; Check signature if Optimus, Mxm or NBCI
    cmp    cx, 'OP'
    je     OptimusFun1
; MXM rev3.0
    mov    bl, 030h             ; Support 3.0
    mov    cx, 0000010011b       ; Support funcion 0,1,4
    jmp    short    @F
;    mov    cx, 1100001011b      ; Support funcion 0,1,3,8,9
;  mov    cx, 11 0001 1011b      ; Support funcion 0,1,3,4,8,9
;   mov    cx, 1110011111b       ; Support funcion 0,1,2,3,4,7,8,9.
OptimusFun1:
    mov    bl, 011h              ; rev 1.1
    mov    cx, 2001h             ; Support funcion 0,13
@@:
    clc
    ret
mxmInt15Fun0 ENDP

;<AMI_PHDR_START>
;----------------------------------------------------------------------------
; Procedure:    mxmInt15Fun1
; Description:    Function 1 Output a Pointer to the MXM Structure
; Input:
;    AX = 5F80h                                      ; MXM2.0, MXM2.1, MXM3.0
;    BL = 01h                                        ; MXM2.0, MXM2.1, MXM3.0
;    BH = FFh                                        ; MXM3.0
;    EBX[31:16] = Adapter ID                         ; MXM3.0
;        Bits [31:24] Bus                            ; MXM3.0
;        Bits [23:19] Device                         ; MXM3.0
;        Bits [18:16] Function                       ; MXM3.0
;    CL = Revision of the MXM software specification  that is supported by the MXM module    ; MXM2.0, MXM2.1
;    CX = Identifier for the data block to return    ; MXM3.0
; Output:
;    AX = 005Fh    to indicate that the system bios supports this function   ; MXM2.0, MXM2.1, MXM3.0
;    BX = Vendor ID of data block if CX = 0x80-0x8F, else 0.                 ; MXM3.0
;    ES:DI = Pointer to the MXM structure in real mode memory (< 1MB)        ; MXM2.0, MXM2.1, MXM3.0
;----------------------------------------------------------------------------
;<AMI_PHDR_END>

mxmInt15Fun1 PROC NEAR

; MXM rev3.0
    mov    di, OFFSET mxm30Struc
    cmp    cl, 030h                         ; Assume this DI for 3.0 MXM.
    jz    short returnMxmStruc

    jmp    short exit

returnMxmStruc:
    mov    bx, 0
    mov    ax, cs                           ; Get ES for MXM structure.
    mov    es, ax
    clc
exit:
    ret
mxmInt15Fun1 ENDP

;<AMI_PHDR_START>
;----------------------------------------------------------------------------
; Procedure:    mxmInt15Fun2
; Description:    Function 2 Output a Pointer to the EDID Structure for the Internal Panel
; Input:
;    AX = 5F80h                                      ; MXM2.0, MXM2.1, MXM3.0
;    BL = 02h                                        ; MXM2.0, MXM2.1, MXM3.0
;    BH = Adapter Index                              ; MXM2.0, MXM2.1
;        0 = Primary MXM adapter (default)
;        1 = Secondary MXM adapter
;    BH = FFh                                        ; MXM3.0
;    EBX[31:16] = Adapter ID                         ; MXM3.0
;        Bits [31:24] Bus
;        Bits [23:19] Device
;        Bits [18:16] Function
;    EDX = Display device identifier (32-bit value as used in _DOD)           ; MXM3.0
; Output:
;    AX = 005Fh    to indicate that the system bios supports this function    ; MXM2.0, MXM2.1, MXM3.0
;    BL = EDID structures returned                                            ; MXM2.1, MXM3.0
;        00 = 128byte EDID 1.3 followed by a 128byte DI-EXT block.
;        02 = 128byte EDID 1.3 structure only
;    ES:DI = Pointer to the EDID structure in real mode memory (< 1MB)        ; MXM2.0, MXM2.1, MXM3.0
;----------------------------------------------------------------------------
;<AMI_PHDR_END>

mxmInt15Fun2 PROC NEAR
    ret
mxmInt15Fun2 ENDP

;<AMI_PHDR_START>
;----------------------------------------------------------------------------
; Procedure:    mxmInt15Fun3
; Description:    Function 3 Select Output Device Channel
; Input:
;    AX = 5F80h                                      ; MXM2.0, MXM2.1, MXM3.0
;    BL = 03h                                        ; MXM2.0, MXM2.1, MXM3.0
;    BH =    Adapter Index                           ; MXM2.0, MXM2.1
;        0 = Primary MXM adapter (default)
;        1 = Secondary MXM adapter
;    BH = FFh                                        ; MXM3.0
;    EBX[31:16] = Adapter ID                         ; MXM3.0
;        Bits [31:24] Bus
;        Bits [23:19] Device
;        Bits [18:16] Function
;    CL = Selection                                  ; MXM2.0, MXM2.1, MXM3.0
;        0 - Acquire shared Display DDC
;        1 - Display Output
;        3 - Both
;        4 - Release shared Display DDC
;    CH = Device index (range 0 - 7)                 ; MXM2.0, MXM2.1
;        according to the order in which the MXM Output Device Structure 
;        for this device appears in the MXM Data Structure. 
;    EDX = Display device identifier (32-bit value as used in _DOD)            ; MXM3.0
; Output:
;    AX = 005Fh    to indicate that the SBIOS supports this function            ; MXM2.0, MXM2.1, MXM3.0
;    BL    For CL=0 the SBIOS shall return a 0h if the mutex was successfully acquired.    ; MXM2.0, MXM2.1, MXM3.0
;        When non-zero the mutex was not aquired.
;----------------------------------------------------------------------------
;<AMI_PHDR_END>

mxmInt15Fun3 PROC NEAR
;;    mov    bl, 0                ; Display DDC acquired
;;    mov    cl, 0                ; Display DDC acquired
    mov bl, cl  ; temp fix. actual mutex lock implementation is needed
    clc
    ret
mxmInt15Fun3 ENDP

;<AMI_PHDR_START>
;----------------------------------------------------------------------------
; Procedure:    mxmInt15Fun4
; Description:    Function 4 Boot Message
; Input:
;    AX = 5F80h                                      ; MXM2.1, MXM3.0
;    BL = 04h                                        ; MXM2.1, MXM3.0
; Output:
;    AX = 005Fh    to indicate that the SBIOS supports this function                      ; MXM2.1, MXM3.0
;    BL = Mode    If zero then the Pointer is a (zero-terminated) Sign-On Text String.    ; MXM2.1
;    BX = Mode    If zero then the Pointer is a (zero-terminated) Sign-On Text String.    ; MXM3.0
;    ES:DI = Pointer String/Image in real mode memory (< 1MB).                            ; MXM2.1, MXM3.0
;    A zero length string indicates the normal sign-on message should be suppressed
;    e.g. to support a graphical splash screen.
;----------------------------------------------------------------------------
;<AMI_PHDR_END>

mxmInt15Fun4 PROC NEAR
; Note. Nvidia Vbios replaces normal Vbios POST messages with the boot string
    mov    di, OFFSET mxmFunc4String
    mov    bx, 0
    mov    ax, cs                                ; Get ES for MXM structure.
    mov    es, ax
    clc
    ret
mxmInt15Fun4 ENDP

;<AMI_PHDR_START>
;----------------------------------------------------------------------------
; Procedure:    mxmInt15Fun7
; Description:    Function 7 Returns a Pointer to the VBIOS Image for ROM-Less Adapters
; Input:
;    AX = 5F80h                                      ; MXM3.0
;    BL = 07h                                        ; MXM3.0
;    BH = FFh                                        ; MXM3.0
;    EBX[31:16] = Adapter ID                         ; MXM3.0
;        Bits [31:24] Bus
;        Bits [23:19] Device
;        Bits [18:16] Function
; Output:
;    AX = 005Fh    to indicate that the SBIOS supports this function                ; MXM3.0
;    ES:DI = Pointer    to the requested VBIOS image in real mode memory (< 1MB).   ; MXM3.0
;----------------------------------------------------------------------------
;<AMI_PHDR_END>

mxmInt15Fun7 PROC NEAR
    ret
mxmInt15Fun7 ENDP

;<AMI_PHDR_START>
;----------------------------------------------------------------------------
; Procedure:    mxmInt15Fun8
; Description:    Function 8 Check Availability of Output Device
; Input:
;    AX = 5F80h                                      ; MXM3.0
;    BL = 08h                                        ; MXM3.0
;    BH = FFh                                        ; MXM3.0
;    EBX[31:16] = Adapter ID                         ; MXM3.0
;        Bits [31:24] Bus
;        Bits [23:19] Device
;        Bits [18:16] Function
;    EDX = Display device identifier (32-bit value as used in _DOD)            ; MXM3.0
; Output:
;    AX = 005Fh    to indicate that the SBIOS supports this function           ; MXM3.0
;    BL = Available                                                            ; MXM3.0
;        BL = 0    indicates the connector is currently available.
;        BL = 1    indicates the connector is not currently available 
;            and no display detection should occur on it.
;----------------------------------------------------------------------------
;<AMI_PHDR_END>

mxmInt15Fun8 PROC NEAR

    cmp bh, 0ffh
    jne invalidDOD
    mov si, 0
    mov cx, DODCount ; no of entries
@@: cmp edx, DWORD PTR cs:[mxmDODTable+si]      ; Call this function.
    je  goodDOD
    add si, 4    ; dword offset
    loop  @B

invalidDOD:
    stc                                         ; default->not supported
    mov bl, 1                                   ; connector is not currently available
    ret

goodDOD:
    mov bl, 0                                   ; connector is available
    clc 
    ret
mxmInt15Fun8 ENDP

;<AMI_PHDR_START>
;----------------------------------------------------------------------------
; Procedure:    mxmInt15Fun9
; Description:    Function 9 Identify Output Devices
; Input:
;    AX = 5F80h                                      ; MXM3.0
;    BL = 09h                                        ; MXM3.0
;    BH = 00h                                        ; MXM3.0
; Output:
;    AX = 005Fh    to indicate that the SBIOS supports this function; MXM3.0
;    BL = Number of entries in table.                               ; MXM3.0
;    ES:DI = Pointer to the table.                                  ; MXM3.0
;        This is a table of 32-bit values identical to the buffer returned by _DOD.    ; MXM3.0
;----------------------------------------------------------------------------
;<AMI_PHDR_END>

mxmInt15Fun9 PROC NEAR

    cmp    bh, 0
    jne    invalidFunc9
    mov    di, OFFSET mxmDODTable
    mov    bl, DODCount ; number of entries
    mov    ax, cs 
    mov    es, ax
    clc
invalidFunc9:
    ret
mxmInt15Fun9 ENDP

;<AMI_PHDR_START>
;----------------------------------------------------------------------------
; Procedure:    mxmInt15FunD
; Description:    Optimus: Discrete graphics subsystem power control
; Input:
;    AX = 5F80h
;    BL = 0Dh
;    BH = FFh
;    EBX[31:16] = Adapter ID
;        Bits [31:24] Bus
;        Bits [23:19] Device
;        Bits [18:16] Function
;    CL = Request GPU subsystem state (0 = Powered off/1 = Powered on)
; Output:
;    AX = 005Fh    to indicate that the system bios supports this function and it completed successfully
;    BL = GPU power state which has been set
;----------------------------------------------------------------------------
;<AMI_PHDR_END>
mxmInt15FunD PROC NEAR
;!!!! EmeraldLake specific
	mov	    dx, 0538h	; DX = mux register
    cmp     cl, 0
    je      dGPU_off
    cmp     cl, 1
    je      dGPU_on
    ret
    
dGPU_off:
    in       eax, dx
    or       eax, 00400000h
    out      dx, eax
    mov      bl, cl
    jmp      short OK_FuncD              
    
dGPU_on:
    in       eax, dx
    and      eax, NOT (00400000h)
    out      dx, eax
    mov      bl, cl
;!!!! EmeraldLake specific
   
OK_FuncD:
    clc
    ret
mxmInt15FunD ENDP

    PUBLIC mxmStrucSrart
mxmStrucSrart:

;----------------------------------------------------------------------------
; MXM rev3.0 data structure
;----------------------------------------------------------------------------
mxm30Struc:
;    include    MXM30.INC                    ; First SIS is for first MXM in single MXM config (instance index 0)    
    MxmTbl    db    MKF_MXM_ROM_MAX_SIZE dup (0dbh)

    PUBLIC mxmStrucEnd
mxmStrucEnd:


CSMOEM_CSEG ENDS
END


;**********************************************************************
;**********************************************************************
;**                                                                  **
;**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
;**                                                                  **
;**                       All Rights Reserved.                       **
;**                                                                  **
;**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
;**                                                                  **
;**                       Phone: (770)-246-8600                      **
;**                                                                  **
;**********************************************************************
;**********************************************************************
