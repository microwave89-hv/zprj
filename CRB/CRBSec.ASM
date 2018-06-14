        TITLE CRBSEC.ASM -- Chipset Reference Board SEC initialization
;*************************************************************************
;*************************************************************************
;**                                                                     **
;**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
;**                                                                     **
;**                       All Rights Reserved.                          **
;**                                                                     **
;**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
;**                                                                     **
;**                       Phone: (770)-246-8600                         **
;**                                                                     **
;*************************************************************************
;*************************************************************************

;*************************************************************************
; $Header: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/CRB/CRBSec.ASM 1     2/12/12 10:38p Victortu $
;
; $Revision: 1 $
;
; $Date: 2/12/12 10:38p $
;*************************************************************************
; Revision History
; ----------------
; $Log: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/CRB/CRBSec.ASM $
; 
; 1     2/12/12 10:38p Victortu
; Intel SharkBay CRB initially releases.
; 
;*************************************************************************
;<AMI_FHDR_START>
;
; Name:         SRBSEC.ASM
;
; Description:  Program any workaround or initialization needed before
;               enabling Cache as memory in the SEC stage for CRB.
;
;<AMI_FHDR_END>
;*************************************************************************

;---------------------------------------------------------------------------
        INCLUDE token.equ
;---------------------------------------------------------------------------

.586P
.XMM
.MODEL SMALL

; Externs
EXTERN  SECCRB_EarlyInitEnd:NEAR32

; Define the equates here

;---------------------------------------------------------------------------
;       STARTUP_SEG  S E G M E N T  STARTS
;---------------------------------------------------------------------------
STARTUP_SEG     SEGMENT     PARA PUBLIC 'CODE' USE32

;<AMI_PHDR_START>
;----------------------------------------------------------------------------
;
; Procedure:    SECCRB_EarlyInit
;
; Description:  This routine initializes CRB for PEI preparation
;
; Input:        ESP BIST Info
;               EBP Reset ID (EDX at reset)
;               Stack not available
;
; Output:       None
;
; Modified:     All, except EBP and ESP
;
; Notes:        NBSEC & SBSEC initialization is done at this point.
;----------------------------------------------------------------------------
;<AMI_PHDR_END>

SECCRB_EarlyInit     PROC PUBLIC


        jmp     SECCRB_EarlyInitEnd
SECCRB_EarlyInit     ENDP

;---------------------------------------------------------------------------
;       STARTUP_SEG  S E G M E N T  ENDS
;---------------------------------------------------------------------------
STARTUP_SEG     ENDS
END

;*************************************************************************
;*************************************************************************
;**                                                                     **
;**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
;**                                                                     **
;**                       All Rights Reserved.                          **
;**                                                                     **
;**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
;**                                                                     **
;**                       Phone: (770)-246-8600                         **
;**                                                                     **
;*************************************************************************
;*************************************************************************

