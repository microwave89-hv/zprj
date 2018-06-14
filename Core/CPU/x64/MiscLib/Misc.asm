;**********************************************************************
;**********************************************************************
;**                                                                  **
;**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
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
; $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/Haswell/AMI Cpu PKG/CPU Core/MiscX64Lib/Misc.asm 2     10/04/12 9:17a Davidhsieh $
;
; $Revision: 2 $
;
; $Date: 10/04/12 9:17a $
;**********************************************************************
; Revision History
; ----------------
; $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/Haswell/AMI Cpu PKG/CPU Core/MiscX64Lib/Misc.asm $
; 
; 2     10/04/12 9:17a Davidhsieh
; Add MpMtrrSynchUpEntry and MpMtrrSynchUpExit procedures
; 
; 1     5/15/12 5:41a Davidhsieh
; 
; 1     5/08/12 6:02a Dukeyeh
; [TAG]  		EIP89382
; [Category]  	Improvement
; [Description]  	clear direction flag inside Timer callback function.
; [Files]  		MiscX64Lib.cif
; Misc.asm
; MiscX64Lib.sdl
; MiscX64Lib.mak
; 
; 6     1/13/10 2:13p Felixp
; 
;**********************************************************************
;<AMI_FHDR_START>
;
; Name: Misc
;
; Description:	
;
;<AMI_FHDR_END>
;**********************************************************************

.code

ClearDirectionFlag Proc
    cld
    ret
ClearDirectionFlag endp

MpMtrrSynchUpEntry  PROC        PUBLIC
    ;
    ; Enter no fill cache mode, CD=1(Bit30), NW=0 (Bit29)
    ;
    mov rax, cr0
    and rax, 0DFFFFFFFh
    or  rax, 040000000h
    mov cr0, rax
    ;
    ; Flush cache
    ;
    wbinvd
    ;
    ; Clear PGE flag Bit 7
    ;
    mov rax, cr4
    mov rdx, rax
    and rax, 0FFFFFF7Fh
    mov cr4, rax
    ;
    ; Flush all TLBs
    ;
    mov rax, cr3
    mov cr3, rax
    
    mov rax, rdx
    
    ret
    
MpMtrrSynchUpEntry  ENDP
    
MpMtrrSynchUpExit  PROC        PUBLIC
    ;
    ; Flush all TLBs the second time
    ;
    mov rax, cr3
    mov cr3, rax
    ;
    ; Enable Normal Mode caching CD=NW=0, CD(Bit30), NW(Bit29)
    ;
    mov rax, cr0
    and rax, 09FFFFFFFh
    mov cr0, rax
    ;
    ; Set PGE Flag in CR4 if set
    ;
    mov cr4, rcx
    ret

MpMtrrSynchUpExit  ENDP

END

;**********************************************************************
;**********************************************************************
;**                                                                  **
;**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
;**                                                                  **
;**                       All Rights Reserved.                       **
;**                                                                  **
;**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
;**                                                                  **
;**                       Phone: (770)-246-8600                      **
;**                                                                  **
;**********************************************************************
;**********************************************************************