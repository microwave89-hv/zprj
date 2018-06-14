        TITLE SBSECInit.ASM -- South Bridge SEC initialization
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
; $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Board/SBSECInit.asm 2     10/23/12 8:18a Scottyang $
;
; $Revision: 2 $
;
; $Date: 10/23/12 8:18a $
;*************************************************************************
; Revision History
; ----------------
; $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Board/SBSECInit.asm $
; 
; 2     10/23/12 8:18a Scottyang
; [TAG]         EIP73607
; [Category]    Bug Fix
; [Severity]    Normal
; [Symptom]     Intruder Detect state is cleaned by BIOS POST.
; [Files]       SBDXE.c; SBSECInit.asm
; 
; 1     2/08/12 8:22a Yurenlai
; Intel Lynx Point/SB eChipset initially releases.
; 
;*************************************************************************
;<AMI_FHDR_START>
;
; Name:         SBSECInit.ASM
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
EXTERN  SECSB_EarlyInitEnd:NEAR32

IFDEF MKF_ENABLE_NB_DMI_GEN2_IN_SEC
IF MKF_ENABLE_NB_DMI_GEN2_IN_SEC
EXTERN  SECNB_DmiGen2Link:NEAR32
ENDIF
ENDIF

; Define the equates here
SB_BUS                          EQU     0
SB_DEV_FUN                      EQU     0F8h

SB_REG_RCBA                     EQU     0F0h

RCRB_MMIO_GCS                   EQU     3410h   ; General Control and Status 
RCRB_RTC_CONF                   EQU     3400h   ; RTC Configuration register 

TCO_IOREG_STS2                  EQU     6       ; TCO Status 2 Register
TCO_IOREG_CNT1                  EQU     8       ; TCO Control 1 Register

;----------------------------------------------------------------------------
;       STARTUP_SEG  S E G M E N T  STARTS
;----------------------------------------------------------------------------
STARTUP_SEG     SEGMENT     PARA PUBLIC 'CODE' USE32

;<AMI_PHDR_START>
;----------------------------------------------------------------------------
;
; Procedure:    SECSB_EarlyInit
;
; Description:  This routine initializes South bridge for PEI preparation
;
; Input:        ESP BIST Info
;               EBP Reset ID (EDX at reset)
;               Stack not available
;
; Output:       None
;
; Modified:     All, except EBP and ESP
;
; Notes:        None of the chipset initialization is done at this point.
;               System is exactly as if came out of RESET.
;               1. Enable Top of 4GB flash ROM access
;----------------------------------------------------------------------------
;<AMI_PHDR_END>

SECSB_EarlyInit     PROC PUBLIC

        mov     al, 004h
        out     80h, al
; Program 8259 Interrupt Controller to disable all interrupts

        mov     al, 0FFh
        out     021h, al
        out     0EDh, al                ; I/O Delay
        out     0A1h, al
        out     0EDh, al                ; I/O Delay
        mov     al, 00h
        out     92h, al

; Determine if INIT or Hard Reset

;        mov     eax, (1 shl 31t) + (SB_BUS shl 16t) + (SB_DEV_FUN shl 8) + 44h
;        mov     dx, 0CF8h
;        out     dx, eax
;        mov     dl, 0FCh
;        in      al, dx
;        and     al, 87h                 ; PM Base address had been enabled?
;        jz      isPowerOn               ; No, is Power on.

; Do a hard Reset if INIT.

;        mov     dx, 0CF9h               ; load dx with reset control reg
;        in      al, dx                  ; read its content
;        or      al, 02h                 ; set bit 1
;        out     dx, al                  ; write it
;        out     0edh, al                ; I/O delay 
;        out     0edh, al                ; I/O delay 
;        or      al, 04h                 ; for HRST set bit 2
;        out     dx, al                  ; write it
;        jmp     $

;isPowerOn:

; Program PCH RCBA Base

        mov     dx, 0CF8h
        mov     eax, (1 shl 31t) + (SB_BUS shl 16t) + (SB_DEV_FUN shl 8) + 0F0h
        out     dx, eax
        mov     dl, 0FCh
        mov     eax, MKF_SB_RCRB_BASE_ADDRESS or 1
        out     dx, eax

; Program SPI prefetching and caching
        mov     dl, 0F8h
        mov     eax, (1 shl 31t) + (SB_BUS shl 16t) + (SB_DEV_FUN shl 8) + 0DCh
        out     dx, eax
        mov     dl, 0FCh
        in      eax, dx
        or      eax, (MKF_SPI_READ_CONFIG shl 2)
        out     dx, eax

; Program PM I/O Base Address
        mov     dl, 0F8h
        mov     eax, (1 shl 31t) + (SB_BUS shl 16t) + (SB_DEV_FUN shl 8) + 040h
        out     dx, eax
        mov     dl, 0FCh
        mov     ax, MKF_PM_BASE_ADDRESS
        out     dx, ax

        mov     dl, 0F8h
        mov     eax, (1 shl 31t) + (SB_BUS shl 16t) + (SB_DEV_FUN shl 8) + 044h
        out     dx, eax
        mov     dl, 0FCh
        mov     al, 80h
        out     dx, al

; Enable ROM Decode for SEC stage.
        mov     dl, 0F8h
        mov     eax, (1 shl 31t) + (SB_BUS shl 16t) + (SB_DEV_FUN shl 8) + 0D8h
        out     dx, eax
        mov     dl, 0FDh
        mov     al, 0FFh                ; Decode 4MB Always
        out     dx, al

; Disable Auto-Reset Function
        mov     dx, MKF_TCO_BASE_ADDRESS + TCO_IOREG_CNT1
        in      ax, dx
        out     0edh, al                ; I/O delay 
        or      ah, 08t                 ; Set Bit[11] to disable TCO timer
        out     dx, ax
        out     0edh, al                ; I/O delay 

        mov     dx, MKF_TCO_BASE_ADDRESS + TCO_IOREG_STS2
        in      ax, dx
        out     0edh, al                ; I/O delay 
        and     al, 0FEh                ; Skip Intrusion, [EIP73607]
        or      al, 02t                 ; Set Bit[1] to clear SECOND_TO_STS
        out     dx, ax
        out     0edh, al                ; I/O delay 

        mov     esi, MKF_SB_RCRB_BASE_ADDRESS + RCRB_RTC_CONF   ; Enable Upper CMOS
        mov     byte ptr [esi], 04h

        mov     esi, MKF_SB_RCRB_BASE_ADDRESS + RCRB_MMIO_GCS
        mov     byte ptr [esi], 60h or (MKF_RESERVED_PAGE_ROUTE shl 2)

; Intel 6 Series Chipset/Intelr C200 Series Chipset/Patsburg Platform Controller Hub(PCH)
; BIOS Specification Update
; Revision 1.0.1
; The System BIOS must perform the steps below early in the POST before
; generating any I/O or MMIO cycles that could be decoded by the PCI bridge
; device.
; 1. System BIOS must determine if the PCH supports the PCI Bridge device
;    via the FVEC0 - Feature Vector Register 0 by following the steps below:
;    a. Set D31:F0:Reg E4h[5:2] (Feature Vector Index) to "0".
;    b. Read D31:F0:Reg E8h[31:0] (Feature Vector Data)
;    c. If
;        FVEC0[1] = 0b, PCI bridge device is enabled.
;       else
;        FVEC0[1] = 1b, PCI bridge device is disabled.
        mov     dx, 0CF8h
        mov     eax, (1 shl 31t) + (SB_BUS shl 16t) + (SB_DEV_FUN shl 8) + 0E4h
        out     dx, eax
        mov     dl, 0FCh
        mov     eax, 0                  ; Set the Enable bit.
        out     dx, eax

        mov     dx, 0CF8h
        mov     eax, (1 shl 31t) + (SB_BUS shl 16t) + (SB_DEV_FUN shl 8) + 0E8h
        out     dx, eax
        mov     dl, 0FCh
        in      eax, dx                 ; Read 0:1F:0:E8
        and     eax, 02h                ; Check if FVECT[1] == 1
        jz      SkipDisableP2P          ; No then leave PCI bridge
                                        ; device enabled

; 2. System BIOS must set the FD - Function disable register offset RCBA +
;    3418h bit 1 PCI Bridge Disable to 1b if the PCI bridge device is not
;    supported by the PCH.
        mov     edi, MKF_SB_RCRB_BASE_ADDRESS + 3418h
        or      DWORD PTR [edi], 02h    ; Else disabled the PCI
                                        ; bridge device
SkipDisableP2P:


; Enable IO Decode range in SEC.
IF MKF_SB_IO_DECODE_IN_SEC
        ;Enable LPC IO decoding
        mov     dx, 0CF8h
        mov     eax, (1 shl 31t) + (SB_BUS shl 16t) + (SB_DEV_FUN shl 8) + 80h
        out     dx, eax
        add     dx, 04h
        mov     eax, 370F0010h
 IFDEF MKF_EC_SUPPORT
        or      eax, (MKF_EC_SUPPORT shl 27t) ; Enable MC_LPC_EN
 ENDIF
        out     dx, eax

 IFDEF MKF_SIO1_CONFIG_INDEX
  IF ((MKF_SIO1_CONFIG_INDEX NE 2Eh) AND (MKF_SIO1_CONFIG_INDEX NE 4Eh))
        mov     dx, 0CF8h
        mov     eax, (1 shl 31t) + (SB_BUS shl 16t) + (SB_DEV_FUN shl 8) + 88h
        out     dx, eax
        add     dx, 04h
        mov     eax, (MKF_SIO1_CONFIG_INDEX and 0FFFCh) or 1;
        out     dx, eax
  ENDIF
 ENDIF

 IF MKF_SB_GEN_DECODE_RANGE_1
; Enable decoding of PME & GPIO Runtime Registers as Generic Decode Range 1
        mov     dx, 0CF8h
        mov     eax, (1 shl 31t) + (SB_BUS shl 16t) + (SB_DEV_FUN shl 8) + 84h
        out     dx, eax
        add     dx, 04h
        mov     eax, ((MKF_SB_GEN_DECODE_RANGE_1 AND 0FFFFh) OR (0FCh SHL 16))
        bts     eax, 0
        out     dx, eax
 ENDIF

 IF MKF_SB_GEN_DECODE_RANGE_2
; Enable decoding of PME & GPIO Runtime Registers as Generic Decode Range 2
        mov     dx, 0CF8h
        mov     eax, (1 shl 31t) + (SB_BUS shl 16t) + (SB_DEV_FUN shl 8) + 88h
        out     dx, eax
        add     dx, 04h
        mov     eax, ((MKF_SB_GEN_DECODE_RANGE_2 AND 0FFFFh) OR (0FCh SHL 16))
        bts     eax, 0
        out     dx, eax
 ENDIF

 IF MKF_SB_GEN_DECODE_RANGE_3
; Enable decoding of PME & GPIO Runtime Registers as Generic Decode Range 3
        mov     dx, 0CF8h
        mov     eax, (1 shl 31t) + (SB_BUS shl 16t) + (SB_DEV_FUN shl 8) + 8Ch
        out     dx, eax
        add     dx, 04h
        mov     eax, ((MKF_SB_GEN_DECODE_RANGE_3 AND 0FFFFh) OR (0FCh SHL 16))
        bts     eax, 0
        out     dx, eax
 ENDIF

 IF MKF_SB_GEN_DECODE_RANGE_4
; Enable decoding of PME & GPIO Runtime Registers as Generic Decode Range 4
        mov     dx, 0CF8h
        mov     eax, (1 shl 31t) + (SB_BUS shl 16t) + (SB_DEV_FUN shl 8) + 90h
        out     dx, eax
        add     dx, 04h
        mov     eax, ((MKF_SB_GEN_DECODE_RANGE_4 AND 0FFFFh) OR (0FCh SHL 16))
        bts     eax, 0
        out     dx, eax
 ENDIF

ENDIF  ; IF MKF_SB_IO_DECODE_IN_SEC


        jmp     SECSB_EarlyInitEnd
SECSB_EarlyInit     ENDP

IFDEF MKF_ENABLE_NB_DMI_GEN2_IN_SEC
IF MKF_ENABLE_NB_DMI_GEN2_IN_SEC
;<AMI_PHDR_START>
;----------------------------------------------------------------------------
;
; Procedure:    SECSB_DmiGen2Init
;
; Description:  This routine initializes South bridge DMI for PEI preparation
;
; Input:        ESP BIST Info
;               EBP Reset ID (EDX at reset)
;               Stack not available
;
; Output:       None
;
; Modified:     All, except EBP and ESP
;
; Notes:        None of the chipset initialization is done at this point.
;               System is exactly as if came out of RESET.
;               1. Enable Top of 4GB flash ROM access
;----------------------------------------------------------------------------
;<AMI_PHDR_END>

SECSB_DmiGen2Init     PROC PUBLIC

        ; Step 1
        ; RCBA + Offset 21A4h[3:0] = 0010b
        mov   esi, MKF_SB_RCRB_BASE_ADDRESS + 21A4h    
        mov   al, byte ptr [esi]
        and   al, 0Fh
        cmp   al, 02h
        jne   SECSB_DmiGen2_Exit              ; if SB DMI Gen != 0010b, jmp SECSB_DmiGen2_Exit

        ; Step 1.2.1
        ; Set RCBA + Offset 2340h[23:16] = 3Ah, Set Gen 2 Common Clock N_FTS
        mov   esi, MKF_SB_RCRB_BASE_ADDRESS + 2340h   
        mov   eax, dword ptr [esi]
        and   eax, 0FF00FFFFh
        or    eax, (3ah SHL 16)
        mov   dword ptr [esi], eax

        ; Step 1.2.2
        ; Set RCBA + Offset 21B0h[3:0] = 0010b, Set target link speed as DMI Gen 2
        mov   esi, MKF_SB_RCRB_BASE_ADDRESS + 21B0h   
        mov   al, byte ptr [esi]
        and   al, NOT (0Fh)
        or    al, (1 SHL 1)
        mov   byte ptr [esi], al

SECSB_DmiGen2_Exit:
        jmp     SECNB_DmiGen2Link
SECSB_DmiGen2Init     ENDP
ENDIF
ENDIF
;----------------------------------------------------------------------------
;       STARTUP_SEG  S E G M E N T  ENDS
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
