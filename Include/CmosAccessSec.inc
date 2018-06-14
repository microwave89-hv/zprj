;**********************************************************************
;**********************************************************************
;**                                                                  **
;**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
;**                                                                  **
;**                       All Rights Reserved.                       **
;**                                                                  **
;**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
;**                                                                  **
;**                       Phone: (770)-246-8600                      **
;**                                                                  **
;**********************************************************************
;**********************************************************************
; $Header: /Alaska/SOURCE/Modules/CMOS Manager/CMOS Core/CMOS Interfaces/CmosAccessSec.inc 7     12/04/09 7:32p Michaela $
;
; $Revision: 7 $
;
; $Date: 12/04/09 7:32p $
;
;****************************************************************************
; Revision History
; ----------------
; $Log: /Alaska/SOURCE/Modules/CMOS Manager/CMOS Core/CMOS Interfaces/CmosAccessSec.inc $
; 
; 7     12/04/09 7:32p Michaela
; 
; 6     9/17/09 10:03a Michaela
; updated jump macros for PE32 SEC binaries
; 
; 5     7/29/09 9:58a Michaela
; updates Aptio Enhancement EIP 22205
; (no code changes)
; 
; 4     7/23/09 2:28p Michaela
; 
; 3     7/23/09 1:35p Michaela
; Fixed build issue related to PE32 binaries
; 
; 2     6/02/09 3:27p Michaela
; For label: 4.6.3_CMOSMGR_11
; 
; 1     11/25/08 3:33p Michaela
; Updates for Label 4.6.3_CMOSMGR_08
; - Assembly macro fixes
; - Added assembly macros
; - Moved loading defaults into DXE phase
; - Updated help file example
; 
; 2     11/25/08 3:29p Michaela
; Updates for Label 4.6.3_CMOSMGR_08
; - Assembly macro fixes
; - Added assembly macros
; - Moved loading defaults into DXE phase
; - Updated help file example
; 
; 1     11/25/08 3:17p Michaela
; Moved to CMOS Interfaces
; 
; 1     11/14/08 9:06a Michaela
; Include file for CMOS access in SEC phase
; 
; 2     11/07/08 5:31p Michaela
; Added SS header
; 

;*************************************************************************
;<AMI_FHDR_START>
;
; Name: CmosAccessSec.inc
;
; Description:
;   This file contains macros, constants, procedure definitions and structure 
;   declarations to be used in SEC phase assembly code.
;
;<AMI_FHDR_END>
;*************************************************************************

IFNDEF  _CMOSACCESS_SEC_INC_
_CMOSACCESS_SEC_INC_   EQU 1

INCLUDE TokenEqu.equ
INCLUDE Token.equ

IFDEF  MKF_SEC_CREATE_PE32               ; cannot use LAST_ADDRESS in PE32 files
    IF MKF_SEC_CREATE_PE32
        SEC_LAST_ADDRESS_VALID = 0
    ELSE
        SEC_LAST_ADDRESS_VALID = 1
    ENDIF
ELSE
    SEC_LAST_ADDRESS_VALID = 1
ENDIF

IF SEC_LAST_ADDRESS_VALID
jmp_edi macro dummy                 ; goto routine & back (via EDI)
        local   llll                ; local label
        mov     edi, LAST_ADDRESS
        sub     edi, OFFSET llll
        neg     edi
        jmp     dummy
llll:
endm

jmp_edx macro dummy                 ; goto routine & back (via EDX)
        local   llll                ; local label
        mov     edx, LAST_ADDRESS
        sub     edx, OFFSET llll
        neg     edx
        jmp     dummy
llll:
endm

;------- The following macros can be used in PE32 SEC
ELSE
jmp_edi macro dummy                 ; goto routine & back (via EDI)
        local   llll                ; local label
        mov     edi, OFFSET llll
        jmp     dummy
llll:
endm

jmp_edx macro dummy                 ; goto routine & back (via EDX)
        local   llll                ; local label
        mov     edx, OFFSET llll
        jmp     dummy
llll:
endm
ENDIF

CMOS_WRITE_ACCESS   = 0
CMOS_READ_ACCESS    = 1

CMOS_BATTERY_ERR    = 012h
CMOS_BITSIZE_ERR    = 013h
CMOS_OVERFLOW_ERR   = 014h

IFNDEF CMOS_NO_EXTERNS
EXTERN  CmosReadWrite:NEAR32
ENDIF

IF SEC_LAST_ADDRESS_VALID
EXTERN  LAST_ADDRESS:ABS
ENDIF

ENDIF

;**********************************************************************
;**********************************************************************
;**                                                                  **
;**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
;**                                                                  **
;**                       All Rights Reserved.                       **
;**                                                                  **
;**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
;**                                                                  **
;**                       Phone: (770)-246-8600                      **
;**                                                                  **
;**********************************************************************
;**********************************************************************
