        TITLE NBSECInit.ASM -- North Bridge SEC initialization
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
; $Header: /Alaska/BIN/Chipset/Intel/NorthBridge/Haswell/Intel SystemAgent NB Board/NBSECInit.ASM 2     8/14/12 3:47a Yurenlai $
;
; $Revision: 2 $
;
; $Date: 8/14/12 3:47a $
;*************************************************************************
; Revision History
; ----------------
; $Log: /Alaska/BIN/Chipset/Intel/NorthBridge/Haswell/Intel SystemAgent NB Board/NBSECInit.ASM $
; 
; 2     8/14/12 3:47a Yurenlai
; [TAG]         None
; [Category]    Improvement
; [Description] If the PCIEXBAR register is enabled, it is INIT.
; [Files]       NBSECInit.ASM
; 
; 1     2/08/12 4:32a Yurenlai
; Intel Haswell/NB eChipset initially releases.
; 
;*************************************************************************
;<AMI_FHDR_START>
;
; Name:         NBSECInit.ASM
;
; Description:  Program any workaround or initialization needed before
;               enabling Cache as memory in the SEC stage
;
;<AMI_FHDR_END>
;*************************************************************************

;----------------------------------------------------------------------------
        INCLUDE token.equ
;----------------------------------------------------------------------------

.586P
.XMM
.MODEL SMALL

; Externs
EXTERN  SECNB_EarlyInitEnd:NEAR32

IFDEF MKF_ENABLE_NB_DMI_GEN2_IN_SEC
IF MKF_ENABLE_NB_DMI_GEN2_IN_SEC
EXTERN  SECSB_DmiGen2Init:NEAR32
PUBLIC	SECNB_DmiGen2Link
ENDIF
ENDIF


; Define the equates here
NB_BUS                          EQU     0
NB_DEV_FUN                      EQU     0
MSR_IA32_PLATFORM_ID            EQU 0017h

;----------------------------------------------------------------------------
;   STARTUP_SEG  S E G M E N T  STARTS
;----------------------------------------------------------------------------
STARTUP_SEG     SEGMENT     PARA PUBLIC 'CODE' USE32

;<AMI_PHDR_START>
;----------------------------------------------------------------------------
;
; Procedure:    SECNB_EarlyInit
;
; Description:  This routine initializes north bridge for PEI preparation
;
; Input:        ESP BIST Info
;               EBP Reset ID (EDX at reset)
;               Stack not available
;
; Output:       None
;
; Modified:     All, except EBP and ESP
;
; Notes:        None.
;
;----------------------------------------------------------------------------
;<AMI_PHDR_END>
SECNB_EarlyInit     PROC PUBLIC

        mov     al, 003h
        out     80h, al
      
        ; If the PCIEXBAR register is enabled, it is INIT.
        mov   eax,  (1 shl 31t) + (NB_BUS shl 16t) + (NB_DEV_FUN shl 8) + 60h     ; 0:0:0:60
        mov   dx,   0CF8h
        out   dx,   eax
        mov   dl,   0FCh
        in    al,   dx
        and   al,   1                            ; Zero?
        jz    NotInit                            ; JIf yes (PAM0 mapped to flash on cold reset)

        ; Do a hard Reset if INIT.
        mov  al, 6
        mov  dx, 0cf9h
        out  dx, al
        jmp  $

NotInit:

        ; Program PCI Express base address
        ; SNB bug [2992042]
        ; Programming of PCIEXBAR has to be done in two steps:
        ;  1. Program the length first - bits [2:1]
        ;  2. Program the base and enable bit (read / modify / write).
        mov   eax,  (1 shl 31t) + (NB_BUS shl 16t) + (NB_DEV_FUN shl 8) + 60h     ; 0:0:0:60                           ; 0:0:0:60
        mov   dx,   0CF8h
        out   dx,   eax
        mov   dl,   0FCh
        mov   eax,  MKF_PCIEX_LENGTH_BIT_SETTING        ; Program the length first.
        out   dx,   eax
        in    eax,  dx
        or    eax,  MKF_PCIEX_BASE_ADDRESS OR 1         ; Program the Base and Enable bit.
        out   dx,   eax

        ; Program PXPEPBAR address
        mov   eax,  (1 shl 31t) + (NB_BUS shl 16t) + (NB_DEV_FUN shl 8) + 40h     ; 0:0:0:40                           ; 0:0:0:60
        mov   dx,   0CF8h
        out   dx,   eax
        mov   dl,   0FCh
        mov   eax,  MKF_NB_EP_BASE_ADDRESS OR 1            ; Set the Enable bit.
        out   dx,   eax

        ; Program MCHBAR address
        mov   eax,  (1 shl 31t) + (NB_BUS shl 16t) + (NB_DEV_FUN shl 8) + 48h     ; 0:0:0:48                           ; 0:0:0:60
        mov   dx,   0CF8h
        out   dx,   eax
        mov   dl,   0FCh
        mov   eax,  MKF_NB_MCH_BASE_ADDRESS OR 1            ; Set the Enable bit.
        out   dx,   eax

        ; Program DMIBAR address
        mov   eax,  (1 shl 31t) + (NB_BUS shl 16t) + (NB_DEV_FUN shl 8) + 68h     ; 0:0:0:68                           ; 0:0:0:60
        mov   dx,   0CF8h
        out   dx,   eax
        mov   dl,   0FCh
        mov   eax,  MKF_NB_DMI_BASE_ADDRESS OR 1            ; Set the Enable bit.
        out   dx,   eax

IFDEF MKF_ENABLE_NB_DMI_GEN2_IN_SEC
IF MKF_ENABLE_NB_DMI_GEN2_IN_SEC
        ; Check CPU Support Gen 2?
        mov   eax,  (1 shl 31t) + (NB_BUS shl 16t) + (NB_DEV_FUN shl 8) + 0E4h    ; 0:0:0:E4                           ; 0:0:0:E4
        mov   dx,   0CF8h
        out   dx,   eax
        mov   dl,   0FCh
        in    eax,  dx
        and   eax,  (1 SHL 22)                               
        jnz   SECNB_Init_Exit                               ; if Gen 1, jmp exit    

        ; Check SNB or IVB ?
        mov   eax,  (1 shl 31t) + (NB_BUS shl 16t) + (NB_DEV_FUN shl 8) + 00h     ; 0:0:0:00                           ; 0:0:0:00
        mov   dx,   0CF8h
        out   dx,   eax
        mov   dl,   0FEh
        in    ax,   dx
        and   al,   0F0h
        cmp   al,   50h
        jne   not_IVB                                       ; if SNB, jmp not_IVB
        jmp SECSB_DmiGen2Prog
not_IVB:

        ; Set DMIBAR Offset BC0[8:6] = 000 before enabling Gen2, for SNB only
        mov   esi, MKF_NB_DMI_BASE_ADDRESS + 0BC0h
        mov   eax, dword ptr [esi]
        and   eax, NOT ((1 SHL 8) + (1 SHL 7) + (1 SHL 6))        
        mov   dword ptr [esi], eax

SECSB_DmiGen2Prog:
        jmp SECSB_DmiGen2Init
SECNB_DmiGen2Link::

        ; Program CPU Max Link Speed to Gen 2
        mov   esi, MKF_NB_DMI_BASE_ADDRESS + 84h
        mov   eax, dword ptr [esi]
        and   eax, NOT (0Fh)  
        or    eax, (1 SHL 1)      
        mov   dword ptr [esi], eax

        jmp   SECNB_Retrainlink
SECNB_Init_Exit::
ENDIF
ENDIF
        jmp     SECNB_EarlyInitEnd
SECNB_EarlyInit     ENDP

IFDEF MKF_ENABLE_NB_DMI_GEN2_IN_SEC
IF MKF_ENABLE_NB_DMI_GEN2_IN_SEC
SECNB_Retrainlink     PROC PUBLIC

        ; Retrain link
        mov   esi, MKF_NB_DMI_BASE_ADDRESS + 88h
        or    byte ptr [esi], (1 SHL 5)

        mov   esi, MKF_NB_DMI_BASE_ADDRESS + 8Ah
waitLoop0:
        mov   ax, word ptr [esi]
        and   ax, (1 SHL 11)
	    jnz   waitLoop0

        ; Retrain link again
        mov   esi, MKF_NB_DMI_BASE_ADDRESS + 88h
        or    byte ptr [esi], (1 SHL 5)

        mov   esi, MKF_NB_DMI_BASE_ADDRESS + 8Ah
waitLoop1:
        mov   ax, word ptr [esi]
        and   ax, (1 SHL 11)
	    jnz   waitLoop1

        jmp   SECNB_Init_Exit
SECNB_Retrainlink     ENDP
ENDIF
ENDIF
;----------------------------------------------------------------------------
;   STARTUP_SEG  S E G M E N T  ENDS
;----------------------------------------------------------------------------
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
