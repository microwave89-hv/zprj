;**********************************************************************
;**********************************************************************
;**                                                                  **
;**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
;**                                                                  **
;**                       All Rights Reserved.                       **
;**                                                                  **
;**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
;**                                                                  **
;**                       Phone: (770)-246-8600                      **
;**                                                                  **
;**********************************************************************
;**********************************************************************

;**********************************************************************
; $Header: /Alaska/SOURCE/Modules/Legacy Serial Redirection/SerialBootCall.asm 3     6/16/14 7:39a Divyac $
;
; $Revision: 3 $
;
; $Date: 6/16/14 7:39a $
;**********************************************************************
; Revision History
; ----------------
; $Log: /Alaska/SOURCE/Modules/Legacy Serial Redirection/SerialBootCall.asm $
; 
; 3     6/16/14 7:39a Divyac
; [TAG]  		EIP172120
; [Category]  	Bug Fix
; [Severity]  	Important
; [Symptom]  	 Redirection After BIOS POST feature is not working.
; [RootCause]  	The flag Indicating whether redirection can happen or not
; is not updated.
; 1)The way of Defining signatures and Comparing Signatures are
; different.
; 2)The variables defined in CSM16 files( SreDirBin_Base_Segadd,
; SreDirBin_Base_Offadd, Flag ) are accessed wrongly.
; 
; [Solution]  	a) The pointer used to check for signatures must be
; UINT32* or we should define signatures byte by byte (db
; '$','S','B','F', db '$','S','B','C'). so changed the way of defining
; Signatures in CSM16 files from dd '$SBF' to db '$','S','B','F'.
; b) Variables should be accessed using OFFSET Keyword.
; [Files]  		SerialBootCall.asm, SerialBootFail.asm
; 
; 2     5/29/13 8:53a Srikantakumarp
; [TAG]  		EIP122394
; [Category]  	Bug Fix
; [Severity]  	Normal
; [Symptom]  	0xE0000~0xEFFFF was overwrite by Legacy Serial Redirection
; module.
; [RootCause]  	LegacySerialRedirection driver assumed that
; SerialBootcall.asm will be the first entry in CsmOem16Functions which
; was wrong.
; [Solution]  	Added a Signature check code for SerialBootCall.asm and
; SredirBootFail.asm before it writes to the memory location
; 0xE0000~0xEFFFF.
; [Files]  		LegacySredir.c, SerialBootCall.asm, SredirBootFail.asm
; 
; 1     2/27/12 5:57a Jittenkumarp
; [TAG]  		EIP81401
; [Category]  	New Feature
; [Description]  	Select Redirection After BIOS POST as BootLoader in
; serial redirection, the behaviour is made same as Core8. 
; [Files]  		LegacySredir.c, LegacySredir.mak, LegacySredir.sdl,
; LegacySredir_Setup.c, LegacySredir.h ,SerialBootCall.asm,
; SredirBootFail.asm,GRAPHREDIR.ASM, INT10REDIR.ASM, OR_MOD.EQU,
; SREDIR.ASM
; 
;**********************************************************************
;<AMI_FHDR_START>
;
; Name: SerialBootCall.asm
;
; Description:  Call Back function registered for 
;               CSM16_OEM_BEFORE_CALL_BOOT_VECTOR 
;
;<AMI_FHDR_END>
;**********************************************************************


;----------------------------------------------------------------------------
;       INCLUDE FILES
;----------------------------------------------------------------------------

        include token.equ
       
;----------------------------------------------------------------------------
;       EXTERNS USED
;----------------------------------------------------------------------------

.586p
OEM16_CSEG SEGMENT PARA PUBLIC 'CODE' USE16
        ASSUME cs:OEM16_CSEG, ds:OEM16_CSEG
;-------------------------------------------------------------------------
        PUBLIC LegcaySredirModuleStart
LegcaySredirModuleStart LABEL BYTE
        jmp     SHORT LegcaySredirCsm16Api
        db      '$','S','B','C'
SreDirBin_Base_Segadd       dw      0000h ;SreDirBin Segement Address
SreDirBin_Base_Offadd       dw      0000h ;SreDirbin offset Address
Flag                        dw      0000h

;----------------------------------------------------------------------------
; IMPORTANT: Do not put any OEM/CHIPSET code above this, the above code and
;            and data are at fixed locations.
;----------------------------------------------------------------------------

;-------------------------------------------------------------------------
;                       LEGACYSREDIR_CSM16_API_Start
;----------------------------------------------------------------------------
; This routine is implementation of the CSM16 API #8.
;         
; Input:        BX - SreDirBin Segment add
;               BX - SreDirBin  Offset add
;               AX - Flag offset value
;
; Output:       None
;
; Register Usage: Do not destroy any register 
;
;----------------------------------------------------------------------------

LegcaySredirCsm16Api  PROC FAR PUBLIC
; Adjust current IP so that the data offsets are valid
          
        call    $+3             ; Push curent IP
        pop     bx              ; Get current IP in BX
        shr     bx, 4
        mov     ax, cs          ; Always x000h
        add     ax, bx          ; New CS
        push    ax
        push    newOffset-LegcaySredirModuleStart
        retf                    ; Execute from new CS:IP

newOffset:
 
        push    bx
        push    si
        push    ax
        push    es
        push    0
        pop     es
        mov     si, offset SreDirBin_Base_Segadd
        mov     bx, word ptr cs:[si]
        mov     es, bx
        mov     si, offset SreDirBin_Base_Offadd
        mov     bx, word ptr cs:[si]
        mov     si, offset Flag
        mov     ax, word ptr cs:[si]
        mov     si, ax
        add     si, bx
        mov     al, 01h
        mov     byte ptr es:[si], al 

        pop     es
        pop     ax
        pop     si
        pop     bx

        retf

LegcaySredirCsm16Api  ENDP

OEM16_CSEG ENDS

END

;**********************************************************************
;**********************************************************************
;**                                                                  **
;**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
;**                                                                  **
;**                       All Rights Reserved.                       **
;**                                                                  **
;**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
;**                                                                  **
;**                       Phone: (770)-246-8600                      **
;**                                                                  **
;**********************************************************************
;**********************************************************************