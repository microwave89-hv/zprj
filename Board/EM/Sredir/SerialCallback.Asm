
        TITLE   SerialCallback.ASM - Oem callback function from sredir.bin

;****************************************************************************
;****************************************************************************
;**                                                                        **
;**             (C)Copyright 1985-2010, American Megatrends, Inc.          **
;**                                                                        **
;**                          All Rights Reserved.                          **
;**                                                                        **
;**                 5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093      **
;**                                                                        **
;**                          Phone (770)-246-8600                          **
;**                                                                        **
;****************************************************************************
;****************************************************************************

;****************************************************************************
; $Header: /Alaska/SOURCE/Modules/Legacy Serial Redirection/SerialCallback.ASM 1     5/03/10 1:53a Rameshr $
;
; $Revision: 1 $
;
; $Date: 5/03/10 1:53a $
;****************************************************************************
; Revision History
; ----------------
; $Log: /Alaska/SOURCE/Modules/Legacy Serial Redirection/SerialCallback.ASM $
; 
; 1     5/03/10 1:53a Rameshr
; Callback function added for read and write function of the Serial Port.
; EIP 37850
;
;****************************************************************************

;----------------------------------------------------------------------------
;       INCLUDE FILES
;----------------------------------------------------------------------------

;----------------------------------------------------------------------------
;       EXTERNS USED
;----------------------------------------------------------------------------
.586p
OEM16_CSEG SEGMENT PARA PUBLIC 'CODE' USE16
        ASSUME cs:OEM16_CSEG, ds:OEM16_CSEG
;-------------------------------------------------------------------------
        PUBLIC SerialCallBackApiModuleStart
SerialCallBackApiModuleStart LABEL BYTE
        jmp     SHORT SerialCallbackCsm16Api

;<AMI_PHDR_START>
;----------------------------------------------------------------------------
;
; Procedure:     SerialCsm16_API
;
; Description:    This routine is implementation of the CSM16 API #B 
;
; Input:         CX     00h   - Serial Read
;                     	01h   - Serial Write 
;
; Output:       
;
; Modified:         None
;
;----------------------------------------------------------------------------
;<AMI_PHDR_END>
SerialCallbackCsm16Api  PROC FAR PUBLIC
; Adjust current IP so that the data offsets are valid
        call    $+3                     ; Push curent IP
        pop     bx                      ; Get current IP in BX
        shr     bx, 4
        mov     ax, cs                  ; Always x000h
        add     ax, bx                  ; New CS
        push    ax
        push    newSerialOffset-SerialCallBackApiModuleStart
        retf                            ; Execute from new CS:IP

newSerialOffset:
        push    bp
        mov     bp, sp
        mov     dx,  ss:[bp+42h]    ; Serial Port Address
        mov     ax,  ss:[bp+40h]    ; Write Data, For read it's invalid 

        cmp     cx, 0
        je      SerialRead
        cmp     cx,1
        je      SerialWrite
        jmp     UnknownFunction
SerialRead:
        Call    ReadSerialPort 
        jmp     UnknownFunction
SerialWrite:
        Call    WriteSerialPort
        jmp     UnknownFunction

UnknownFunction:
        pop     bp

; Adjust sp as if we returned to csm16_func_ret
        add     sp, 4                   ; cs:ip of F000:csm16_func_ret

; Save AX, restore it after popad
        push    ax
        pop     ds

        popad

        push    ds
        pop     ax

        pop     gs
        pop     fs
        pop     es
        pop     ds

        popf
        pop     ds
        pop     si

        add     sp, 2                   ; Do not "pop ax", preserving return code

        pop     bp
        add     sp, 4

        clc
        retf        
SerialCallbackCsm16Api  ENDP

;<AMI_PHDR_START>
;----------------------------------------------------------------------------
;
; Procedure:  	WriteSerialPort
;
; Description:  Oem Function before serial Read 
;
; Input:      	None
;                
; Output:       None
;
; Modified:	None
;
;----------------------------------------------------------------------------
;<AMI_PHDR_END>
WriteSerialPort   PROC    NEAR     PUBLIC
        out     dx,al
        jmp     $+2
        ret
WriteSerialPort   ENDP

;<AMI_PHDR_START>
;----------------------------------------------------------------------------
;
; Procedure:  	ReadSerialPort
;
; Description:  Oem Function before serial Write 
;
; Input:      	None
;                
; Output:       None
;
; Modified:	None
;
;----------------------------------------------------------------------------
;<AMI_PHDR_END>
ReadSerialPort   PROC    NEAR     PUBLIC
        in      al,dx
        jmp     $+2
        ret
ReadSerialPort   ENDP

OEM16_CSEG ENDS

END
;****************************************************************************
;****************************************************************************
;**                                                                        **
;**             (C)Copyright 1985-2010, American Megatrends, Inc.          **
;**                                                                        **
;**                          All Rights Reserved.                          **
;**                                                                        **
;**                 5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093      **
;**                                                                        **
;**                          Phone (770)-246-8600                          **
;**                                                                        **
;****************************************************************************
;****************************************************************************
