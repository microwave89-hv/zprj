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
; $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/Haswell/AMI Cpu PKG/CPU Core/ResetVector.asm 3     6/15/12 3:27a Davidhsieh $
;
; $Revision: 3 $
;
; $Date: 6/15/12 3:27a $
;**********************************************************************
; Revision History
; ----------------
; $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/Haswell/AMI Cpu PKG/CPU Core/ResetVector.asm $
; 
; 3     6/15/12 3:27a Davidhsieh
; [TAG]  		None
; [Category]  	New Feature
; [Description]  	For FIT module support
; 
; 2     3/16/12 3:11a Davidhsieh
; Setup items create for CPU RC policy
; 
; 1     2/07/12 3:58a Davidhsieh
; 
;**********************************************************************

;<AMI_FHDR_START>
;----------------------------------------------------------------------------
;
; Name:	ResetVector.asm
;
; Description:
;   Reset Vector. Fixup will update code to jump to EntryPoint of Startup32.asm.
;
;----------------------------------------------------------------------------
;<AMI_FHDR_END>

.586P
.XMM
.model tiny

include token.equ
        
RESET_SEG  SEGMENT PARA PUBLIC 'CODE' USE16 
        org     0			;offset 0xFFFFFFC0h
ifndef MKF_INTEL_FIT_TABLE_ADDRESS
        dd      0EEEEEEEEh
        dd      0EEEEEEEEh
else        
        dd      MKF_INTEL_FIT_TABLE_ADDRESS	;Reserve
        dd      0h
endif        
        org     10h         ;offset 0xFFFFFFD0h
        mov     di, "AP"    ;Actual AP startup (SIPI) is hardcoded to jump here.
        jmp     ApStartup

        org     20h         ;offset 0xFFFFFFE0
        dd      87654321h   ;Fixed up by tool to point to PEI CORE Entry.
        
        org     30h         ;offset 0xFFFFFFF0
        nop                 ;Place holder to maintain byte sequence for build tool fix-ups.
        nop                 ;Place holder to maintain byte sequence for build tool fix-ups.
ApStartup:                
        ; Use machine code directly in case of the assembler optimization
        ; SEC entry point relatvie address will be fixed up by some build tool.
        ; 
        db      0e9h        ;jmp Rel16
        dw      -3          ;SecFixup utility changes to point to flat32.asm Entry Point.
         
        org     3ch         ;offset 0xFFFFFFFC
		dd      012345678h  ;Fixed up by GenFvImage to Boot Firmware Volume Base.
RESET_SEG  ENDS
END

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

