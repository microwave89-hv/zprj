        TITLE    NBINT15.ASM -- OEM INTERRUPT NB IMPLEMENTATION
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
; $Header: /Alaska/BIN/Chipset/Intel/NorthBridge/Haswell/Intel SystemAgent NB Board/NbInt15.asm 1     2/08/12 4:33a Yurenlai $
;
; $Revision: 1 $
;
; $Date: 2/08/12 4:33a $
;*************************************************************************
; Revision History
; ----------------
; $Log: /Alaska/BIN/Chipset/Intel/NorthBridge/Haswell/Intel SystemAgent NB Board/NbInt15.asm $
; 
; 1     2/08/12 4:33a Yurenlai
; Intel Haswell/NB eChipset initially releases.
; 
;*************************************************************************
;<AMI_FHDR_START>
;
; Name: NbInt15.asm
;
; Description:   IGFX INT15 function hook
;
;<AMI_FHDR_END>
;*************************************************************************


include token.equ
.386

CSMOEM_CSEG SEGMENT PARA PUBLIC 'CODE' USE16
        ASSUME cs:CSMOEM_CSEG, ds:CSMOEM_CSEG

OldIntHandler   LABEL DWORD
        IntSegSav       dw      0
        IntOfsSav       dw      0

;<AMI_PHDR_START>
;----------------------------------------------------------------------------
;
; Procedure:   NBINT15
;
; Description: TIGD INT15 function implememtation.
;
; Input:       None
;
; Output:      None
;----------------------------------------------------------------------------
;<AMI_PHDR_END>
NBINT15 PROC   PUBLIC

        cmp             ah, 5fh
        je              igd_call
        jmp             DWORD PTR cs:[OldIntHandler]

igd_call:
;       we are going to handle this call
        cmp             al, 00
        jne             not_5f00

        mov             bx, 1302h
        jmp             exit_success

not_5f00:

IFDEF MKF_CRB_EC_SUPPORT
IF MKF_CRB_EC_SUPPORT
        cmp             al, 14h
        jne             not_5f14

        cmp             bx, 078Fh
        jne             exit_not_supported

        mov             cl, 00h
        call            read_ec_port
        jmp             exit_success
ENDIF
ENDIF

not_5f14:
        cmp             al,40h
        jne             not_5f40

        cmp             bl, 00h
        jne             get_sdvo_paneltype

;       Get LFP Panel Type
        mov             al, MKF_IGFX_LCD_PANEL_TYPE
        jmp             read_paneltype

get_sdvo_paneltype:
        cmp             bl, 01h
        jne             exit_fail
        mov             al, MKF_IGFX_SDVO_PANEL_TYPE

read_paneltype:
        call            get_igfx_setup_data
        mov             cl, al
        cmp             cl, 0
        jz              not_5f01
        jmp             exit_success

not_5f40:
        cmp             al, 34h
        jne             not_5f34

;       Get Panel Scaling feature
        mov             al, MKF_IGFX_LCD_PANEL_SCALING
        call            get_igfx_setup_data
        mov             cl, al
        jmp             exit_success

not_5f34:
        cmp             al,35h
        jne             not_5f35

;       Get IGD boot type
        mov             al,MKF_IGFX_BOOT_TYPE
        call            get_igfx_setup_data
        mov             cl, al
        cmp             cl, 00h
        jne             check_pipe_B_display
        mov             ch, 00h
        jmp             exit_success

check_pipe_B_display:

;       Get Pipe B device type
        mov             al,MKF_IGFX_DISPLAY_PIPE_B_TYPE
        call            get_igfx_setup_data
        mov             ch, al

;        Check Pipe A & Pipe B are same
        cmp             cl, ch
        jne             exit_success
        mov             ch, 00h
        jmp             exit_success

not_5f35:
        cmp             al,49h
        jne             not_5f49

; ----------------------------------------------------
; Int 15h, AX = 5F49h, Get backlight type and polarity
; ----------------------------------------------------
        mov             al,MKF_IGFX_BACKLIGHT_TYPE
        call            get_igfx_setup_data
        movzx           cx, al
        jmp             exit_success

not_5f49:
        cmp             al,50h
        jne             not_5f50

; ----------------------------------------------------
; Int 15h, AX = 5F50h, Program Squelch Register for eDP
; ----------------------------------------------------
        push            es
        push            0
        pop             es
        push            edi
        mov             edi,MKF_PCIEX_BASE_ADDRESS
;
; set PCIEXBAR + 0x8dfc[1]=1b
;
        mov             al, BYTE PTR es:[edi + 08dfch]
        or              al,02h
        mov             BYTE PTR es:[edi + 08dfch],al
;
; set PCIEXBAR + 0x8f88[31]=1b
; set PCIEXBAR + 0x8f88[26]=0b
;
        mov             al, BYTE PTR es:[edi + 08f8bh]
        or              al,080h
        and             al,NOT (04h)
        mov             BYTE PTR es:[edi + 08f8bh],al
;
; set PCIEXBAR + 0x8fa8[31]=1b
; set PCIEXBAR + 0x8fa8[26]=0b
;
        mov             al, BYTE PTR es:[edi + 08fabh]
        or              al,080h
        and             al,NOT (04h)
        mov             BYTE PTR es:[edi + 08fabh],al
;
; set PCIEXBAR + 0x8fc8[31]=1b
; set PCIEXBAR + 0x8fc8[26]=0b
;
        mov             al, BYTE PTR es:[edi + 08fcbh]
        or              al,080h
        and             al,NOT (04h)
        mov             BYTE PTR es:[edi + 08fcbh],al
;
; set PCIEXBAR + 0x8fe8[31]=1b
; set PCIEXBAR + 0x8fe8[26]=0b
;
        mov             al, BYTE PTR es:[edi + 08febh]
        or              al,080h
        and             al,NOT (04h)
        mov             BYTE PTR es:[edi + 08febh],al
        pop             edi
        pop             es
        jmp             exit_success
not_5f50:
        cmp             al,51h
        jne             not_5f51
; ----------------------------------------------------
; Int 15h, AX = 5F51h, Select Active LFP Configuration
; ----------------------------------------------------
        mov             al,MKF_IGFX_EDP_ACTIVE_LFP_CONFIG_TYPE
        call            get_igfx_setup_data
        movzx           cx, al
        jmp             exit_success
not_5f51:
        cmp             al,52h
        jne             not_5f52
; -----------------------------------------------------
; Int 15h, AX = 5F52h, Hook to select Panel Color Depth
; -----------------------------------------------------
        mov             al,MKF_IGFX_LFP_PANEL_COLOR_DEPTH_TYPE
        call            get_igfx_setup_data
        movzx           cx, al
        jmp             exit_success
not_5f52:
        cmp             al,21h
        jne             not_5f21
; --------------------------------------------------
; Int 15h, AX = 5F21h, Get Actual display core clock
; --------------------------------------------------
        call            GetCDClock
        cmp             cx, 0
        je              exit_fail
        jmp             exit_success

not_5f21:
        cmp             al,22h
        jne             not_5f22
; --------------------------------------------------
; Int 15h, AX = 5F22h, Get FSB frequency
; --------------------------------------------------
        call            GetFsbFreq
        cmp             cx, 0
        je              exit_fail
        jmp             exit_success

not_5f22:
        .386
        cmp             al,01h
        jnz             not_5f01
        INT             10h
        mov             eax,ebx
        shr             ebx,16
        mov             dx,bx
        mov             bx,ax
        jmp             exit_success

not_5f01:
        cmp             al, 70h
        jnz             not_5f70
        call            Func_70h_handler
        jmp             exit

exit_not_supported:
        mov             ax, 0000h
        jmp             exit

exit_fail:
not_5f70:
        mov             ax, 15fh
        jmp             exit


exit_success:
        mov             ax, 05fh

exit:
        retf            2
NBINT15    ENDP

;<AMI_PHDR_START>
;---------------------------------------------------------------------------;
;
; Procedure:      Func_70h_handler
;
; Description:    Get/Set MUX State Hook 
;
; Input:  AX          = 5F70h, Get/Set MUX State
;         CH          = 00h - Get MUX State
;                     = 01h - Set MUX State
;                     = 02h - Get SG/Non-SG Mode
;                     
;
;           For CH=01h Set MUX State,
;           CL         = MUX state, 
;                      = 0 - Set all MUXs to iGPU
;                      = 1 - Set all MUXs to dGPU
;
; Output: AX        = Return Status(function not supported if AL !=5FH)
;                                   005Fh,Function Supported and successful
;                                   015Fh,Function Supported but failed
;                      For CH=00h in Input, CL =  MUX State (0 = iGPU, 1= dGPU)
;                          Bit 0 = CRT
;                          Bit 3 = LFP
;                      For CH=02h in Input, Get SG/Non-SG Mode 
;                            CL =  SG Mode (0 = SG Enabled, 1= SG Disabled)
;
;---------------------------------------------------------------------------;
;<AMI_PHDR_END>
Func_70h_handler PROC NEAR PUBLIC
.386
    
; check if function 0 of handler is being called
        push            dx
        push            eax
        cmp             ch, 0h                 
        jne             check_INTEL_HG_F1
            
; Function 0       - Get MUX State
        mov             dx, 0538h
        mov             cl, 09h        ; assume DGPU
        in              eax, dx
        and             eax, 00100000h
        jz              OK_70
        mov             cl, 0h
        jmp             OK_70         

; Function 1                                           
; check if function 1 of handler is being called
check_INTEL_HG_F1:
        cmp             ch, 01h
        jne             check_INTEL_HG_F2

        mov             dx, 0538h        ; DX = mux register
        cmp             cl, 0
        je              ProgramMuxIGPU_Intel
        cmp             cl, 1
        je              ProgramMuxDGPU_Intel
        jmp             notOK_70
    
ProgramMuxIGPU_Intel:
        in             eax, dx
        or             eax, 00180000h
        out            dx, eax
        jmp            OK_70
    
ProgramMuxDGPU_Intel:
        in             eax, dx
        and            eax, NOT (00180000h)
        out            dx, eax
        jmp            OK_70
    
; Function 2
; Check if function 2 of handler is being called

check_INTEL_HG_F2:
        cmp            ch, 02h
        jne            notOK_70

;Get PrimaryDisplay
        mov            al, MKF_IGFX_PRIMARY_DISPLAY_TYPE
        call           get_igfx_setup_data
        cmp            al,4h
        je             PrimaryDisplay_SG

        mov            cl,01h
        jmp            OK_70

PrimaryDisplay_SG:
        mov            cl,00h

OK_70:
        pop            eax              ; restore EAX before setting return value
        mov            ax, 005fh
        jmp            Func_70h_exit

notOK_70:        
        pop            eax              ; restore EAX before setting return value
        mov            ax, 015Fh

Func_70h_exit:
        pop            dx
        ret

Func_70h_handler ENDP

;<AMI_PHDR_START>
;---------------------------------------------------------------------------;
;
; Procedure:      read_ec_port
;
; Description:    procedure to read status values from EC ports
;
; Input:          N/A
;
; Output:         data in CL register
;
;---------------------------------------------------------------------------;
;<AMI_PHDR_END>

read_ec_port    proc    near

        push           eax

        mov            al, 0Ah
        out            66h, al
ec_read_loop1:
        in             al, 66h
        and            al, 01h
        jz             ec_read_loop1
        in             al, 62h
        mov            ah, al

        mov            al, 8Ah
        out            66h, al
ec_read_loop2:
        in             al, 66h
        and            al, 01h
        jz             ec_read_loop2
        in             al, 62h

; SS Docking status
        and            al, 01h
        jz             check_lid_status
        or             cl, 01h

;Lid status
check_lid_status:
        mov            al, ah
        and            al, 01h
        jnz            check_AC_status
        or             cl, 02h

;AC power status
check_AC_status:
        mov            al, ah
        and            al, 10h
        jz             exit_read_ec_port
        or             cl, 04h

exit_read_ec_port:
        pop            eax
        ret

read_ec_port    endp

;<AMI_PHDR_START>
;---------------------------------------------------------------------------;
;
; Procedure:      get_igfx_setup_data
;
; Description:    get IGFX setup data after call NB SMI 
;
; Input:          AL  - INDEX
;
; Output:         data in reg al
;
;---------------------------------------------------------------------------;
;<AMI_PHDR_END>
get_igfx_setup_data        proc    near

        push           bx
;       save index to bl
        mov            bl, al

;       NB SW SMI
        mov            al, MKF_NB_SWSMI_IGFX_GET_SETUP
        out            0b2h, al

;       setup data move to al
        mov            al, bl

        pop            bx

        ret

get_igfx_setup_data        endp

GraphicsCoreClock      LABEL    WORD
;
; VCO = 3200MHz (MCHBAR+0C0Fh[2:0] = 000b)
;
        DW             0228
        DW             0320
;
; VCO = 4000MHz (MCHBAR+0C0Fh[2:0] = 001b)
;
        DW             0222
        DW             0333
;
; Reserved
;
        DW             0222
        DW             0333
;
; Reserved
;
        DW             0
        DW             0
;
; VCO = 2666MHz (MCHBAR+0C0Fh[2:0] = 100b)
;
        DW             0222
        DW             0333

SaveCoreClock   DW      05555h

;<AMI_PHDR_START>
;---------------------------------------------------------------------------;
;
; Procedure:      GetCDClock
;
; Description:    This function gets the Cantiga IGD display core clock value 
;                 and return it in CX.
;
; Input:          N/A
;
; Output:         N/A
;
;---------------------------------------------------------------------------;
;<AMI_PHDR_END>
GetCDClock             PROC
        mov            cx, cs:[SaveCoreClock]
        cmp            cx, 05555h
        jne            ExitGetCDClock

        push            ax
        push            bx
        push            edi
;
; Read MCHBAR + 0C0Fh[2:0] = HPLL VCO frequency
;
        push            es                        ; Save previous ES
        push            0                         ; 
        pop             es
        mov             edi, MKF_NB_MCH_BASE_ADDRESS
        movzx           bx, BYTE PTR es:[edi + 0C0Fh]
        and             bx, 7                     ; HPLL VCO Freq, Bits[2:0]

        push            bx                        ; Save in BX
;
; Read B0:D2:F0:Offset F0h[12] = Graphics Core Display Clock Select
;
        mov             edi, MKF_PCIEX_BASE_ADDRESS + (2 SHL 15) + (0 SHL 12)
        mov             ax, WORD PTR es:[edi + 0F0h]
        pop             es                        ; Restore ES
        and             ax, 01000h                ; GCFGC Bit[12]
        shr             ax, 12 - 1                ; Bit[12] * (sizeof WORD)
        pop             bx                        ; Restore HPLL VCO Freq
        imul            bx, 4
        add             bx, ax
;
; Get Actual Core Display Frequency from Table
;
        mov             cx, cs:GraphicsCoreClock[bx]
        mov             cs:[SaveCoreClock], cx
        pop             edi
        pop             bx
        pop             ax

ExitGetCDClock:
        ret
GetCDClock      ENDP

;<AMI_PHDR_START>
;---------------------------------------------------------------------------;
;
; Procedure:      GetFsbFreq
;
; Description:    This function gets the Cantiga Front Side Bus (FSB) Frequency 
;                 and return it in CX.
;
; Input:          N/A
;
; Output:         N/A
;
;---------------------------------------------------------------------------;
;<AMI_PHDR_END>

SaveFsbFreq             DW        05555h

GetFsbFreq              PROC    NEAR
        mov             cx, cs:[SaveFsbFreq]
        cmp             cx, 05555h
        jne             Exit

        push            ax
        push            edi
;
; Read MCHBAR + 0C00h[2:0] = FSB Frequency
;
        push            es                ; Save previous ES
        push            0                 ; 
        pop             es
        mov             edi, MKF_NB_MCH_BASE_ADDRESS
        mov             al, BYTE PTR es:[edi + 0C00h]
        and             al, 7             ; FSB Freq, Bits[2:0]

;
; Get actual Front Side Bus Frequency
;
        mov             cx, 800
        cmp             al, 2
        je              GotFsbFreq
        mov             cx, 667
        cmp             al, 3
        je              GotFsbFreq
        mov             cx, 1066
        cmp             al, 6
        je              GotFsbFreq   
        mov             cx, 0             ; Not supported

GotFsbFreq:
        mov             cs:[SaveFsbFreq], cx
        pop             es                ; Restore ES
        pop             edi
        pop             ax

Exit:
        ret
GetFsbFreq      ENDP


CSMOEM_CSEG ENDS

END
;**********************************************************************
;**********************************************************************
;**                                                                  **
;**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
;**                                                                  **
;**                       All Rights Reserved.                       **
;**                                                                  **
;**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
;**                                                                  **
;**                       Phone: (770)-246-8600                      **
;**                                                                  **
;**********************************************************************
;**********************************************************************