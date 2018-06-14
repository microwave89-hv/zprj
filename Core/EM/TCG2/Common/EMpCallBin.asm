;**********************************************************************
;**********************************************************************
;**                                                                  **
;**        (C)Copyright 1985-2005, American Megatrends, Inc.         **
;**                                                                  **
;**                       All Rights Reserved.                       **
;**                                                                  **
;**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
;**                                                                  **
;**                       Phone: (770)-246-8600                      **
;**                                                                  **
;**********************************************************************
;*************************************************************************
; $Header: /Alaska/SOURCE/Modules/TCG2/Common/TcgDxe/EMpCallBin.asm 1     4/21/14 2:16p Fredericko $
;
; $Revision: 1 $
;
; $Date: 4/21/14 2:16p $
;*************************************************************************
; Revision History
; ----------------
; $Log: /Alaska/SOURCE/Modules/TCG2/Common/TcgDxe/EMpCallBin.asm $
; 
; 1     4/21/14 2:16p Fredericko
; 
; 1     10/08/13 12:03p Fredericko
; Initial Check-In for Tpm-Next module
; 
; 1     7/10/13 5:51p Fredericko
; [TAG]  		EIP120969
; [Category]  	New Feature
; [Description]  	TCG (TPM20)
; 
; 13    5/09/12 6:38p Fredericko
; Fix for possible Tcm hang issues during reboot cycles. 
; 
; 12    1/20/12 9:13p Fredericko
; Added code to work around RTC issue when using legacy IO support.
; 
; 11    4/22/11 8:53p Fredericko
; Token to enable stack workaround for binaries that don't return
; properly.
; 
; 10    3/29/11 1:13p Fredericko
; 
; [TAG]        EIP 54642
; [Category] Improvement
; [Description] 1. Checkin Files related to TCG function override 
; 2. Include TCM and TPM auto detection
; [Files] Affects all TCG files
; 
; 9     3/28/11 2:22p Fredericko
; [TAG]        EIP 54642
; [Category] Improvement
; [Description] 1. Checkin Files related to TCG function override
; 2. Include TCM and TPM auto detection
; [Files] Affects all TCG files
; 
; 8     5/19/10 5:38p Fredericko
; Included File Header
; Included File Revision History 
; Updated AMI Function Headers
; Code Beautification
; EIP 37653
; 
; 7     4/16/10 10:36a Fredericko
; Function Headers updated
; 
; 6     3/23/10 9:21p Fredericko
; 
; 5     3/23/10 6:56p Fredericko
; 
; 4     3/19/10 4:27p Fredericko
; Modified the way Driver calls into legacy TCG Binary.
; 
; 3     6/02/09 1:12p Fredericko
; 
; 2     5/18/09 6:04p Fredericko
; 
; 1     5/18/09 6:03p Fredericko
; Initial check-in for EMpCallBin.asm for CTPM support infrastructure
;**********************************************************************
;<AMI_FHDR_START>
;
; Name: EMpCallBin.asm  
;
; Description:
;    Contains functions for legacy TCG calls in 32 bit Binaries 
;
;<AMI_FHDR_END>
;**********************************************************************
.code
    INCLUDE token.equ

;Global variable for MpLoc
    public MpLoc
 MpLoc label dword
    FWORD    ?

public TPMRTCSave
 TPMRTCSave label dword
    WORD    ?

TPMTransmitEntryStruct STRUC
    pbInBuf    DD  ? ;[IN] Pointer to input data for the data transfers to TPM
    dwInLen    DD  ? ; [IN] Length of the input data record
    pbOutBuf   DD  0 ; [OUT] Pointer to output buffer for the data from the TPM
    dwOutLen   DD  0 ; [IN/OUT] DWORD to store the length info of the
                     ; output data record.
TPMTransmitEntryStruct ENDS






;<AMI_PHDR_START>
;-----------------------------------------------------------------------------
; 
; Procedure:    Prepare2Thunkproc
; 
; Description: 
; Function to setup location of Mp Driver as a local variable
; 
; Input: 
; ecx - Location of MP Driver
; dx  - Segment for MP Driver 
;
; Output: 
; 
; Modified: 
; 
; Referrals:	
; 
; Notes:      
;---------------------------------------------------------------------------
;<AMI_PHDR_END>
Prepare2Thunkproc proc
        push     rax
        push     rcx
        push     rdx
        mov      dword ptr [MpLoc],ecx
        mov      word  ptr [MpLoc + 4],dx
        pop      rdx
        pop      rcx
        pop      rax
        ret
Prepare2Thunkproc ENDP




;<AMI_PHDR_START>
;-----------------------------------------------------------------------------
; 
; Procedure:    TcgDxeCallMPDriver (TCM_support eq 0)
; 
; Description: 
; Makes a function call into MP Driver
; 
; Input: 
; rcx - Call type: 4-Buffer Transmission call
; rsi - Buffer to be tansmitted
;
; Output: 
; rax - TCG return code
; 
; Modified: 
; 
; Referrals:	
; 
; Notes:      
;---------------------------------------------------------------------------
;<AMI_PHDR_END>
TpmDxeCallMPDriver proc
        push    rbp
        push    rax
        push    rcx
        push    rdx
        mov     rbp,rsp
        cmp     rcx, 04h
        jnz     Empty_Buff
        MOV     rsi,  rdx
Empty_Buff:
        mov     rax, rcx
        push    rcx
        mov     rcx, offset next
IF MKF_Stack_Work_Around
        mov     dword ptr [IP_Offset], ecx
ENDIF
IF MKF_PMBASE_RTC_WKAround
        push     rax
        push     rdx
        mov      dx, MKF_PM_BASE_ADDRESS
        in       ax, dx 
        mov      word ptr [TPMRTCSave],ax
        pop      rdx
        pop      rax
ENDIF
        pop     rcx
        call    fword ptr [MpLoc]
IF MKF_Stack_Work_Around
        db      0eah
IP_Offset:
        dd      0
        dw      038h
ENDIF
next:
IF MKF_PMBASE_RTC_WKAround
        push  rax
        push  rdx
        mov   dx,MKF_PM_BASE_ADDRESS
        in    ax, dx 
        test  ax, dx
        jz    RtcNotSet      
        mov   ax, word ptr [TPMRTCSave]
        and   ax,0FBFEh
        or    ax,0400h
        out   dx, ax
RtcNotSet:
        pop   rdx
        pop   rax
ENDIF
        mov     rsp,rbp
        pop     rdx
        pop     rcx
        pop     rax
        pop     rbp
        ret
TpmDxeCallMPDriver ENDP



TcmIoDelay proc
    push rax
    mov al, 80h
    out 080h, al
    in  al, 080h
    pop rax
    ret
TcmIoDelay ENDP

;<AMI_PHDR_START>
;-----------------------------------------------------------------------------
; 
; Procedure:    TcgDxeCallMPDriver (TCM_support eq 1)
; 
; Description: 
; Makes a function call into MP Driver
; 
; Input: 
; rcx - Call type: 4-Buffer Transmission call
; rsi - Buffer to be tansmitted
;
; Output: 
; rax - TCG return code
; 
; Modified: 
; 
; Referrals:	
; 
; Notes:      
;---------------------------------------------------------------------------
;<AMI_PHDR_END>
TcmDxeCallMPDriver proc
        push     rax
        push     rcx
        push     rdx
        push     rsi
        cmp      rcx, 04h
        jnz      Empty_Buff
        MOV      rsi,  rdx
Empty_Buff:
        mov      rax, rcx
        call    TcmIoDelay
        call     fword ptr [MpLoc]
        call    TcmIoDelay
        pop      rsi
        pop      rdx
        pop      rcx
        pop      rax
        ret
TcmDxeCallMPDriver ENDP





;<AMI_PHDR_START>
;-----------------------------------------------------------------------------
; 
; Procedure:    TcgThunk32
; 
; Description: 
; Go to compatibility mode for MP driver
; 
; Input: 
;
; Output: 
; 
; Modified: 
; 
; Referrals:	
; 
; Notes:      
;---------------------------------------------------------------------------
;<AMI_PHDR_END>
TcgThunk32 proc
TcgThunk32 ENDP





;<AMI_PHDR_START>
;-----------------------------------------------------------------------------
; 
; Procedure:    TcgThunkSwitchback
; 
; Description: 
; Switch back to 64bit mode
; 
; Input: 
;
; Output: 
; 
; Modified: 
; 
; Referrals:	
; 
; Notes:      
;---------------------------------------------------------------------------
;<AMI_PHDR_END>
TcgThunkSwitchback proc
TcgThunkSwitchback ENDP

END
