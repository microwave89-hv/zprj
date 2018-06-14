;*************************************************************************
;*************************************************************************
;**                                                                     **
;**        (C)Copyright 1985-2009, American Megatrends, Inc.            **
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
; $Header: /Alaska/SOURCE/Core/Modules/x64Core/x64AsmLib/IoWrite8.asm 1     10/01/10 5:07p Felixp $
;
; $Revision: 1 $
;
; $Date: 10/01/10 5:07p $
;*************************************************************************
; Revision History
; ----------------
; $Log: /Alaska/SOURCE/Core/Modules/x64Core/x64AsmLib/IoWrite8.asm $
; 
; 1     10/01/10 5:07p Felixp
; 
; 1     8/24/06 12:57p Felixp
; 
;*************************************************************************
;<AMI_FHDR_START>
;
; Name:
;
; Description:
;
;<AMI_FHDR_END>
;*************************************************************************
.code

;*************************************************************************
;<AMI_PHDR_START>
;
; Name: IoWrite8
;
; Description:
;  VOID IoWrite8(IN UINT16 Port, IN UINT8 Value) writes the 8-bit Value to
; the I/O port defined by Port.
;
; Input:
;  IN UINT16 Port
; I/O port to write 8-bits to.
;
;  IN UINT8 Value
; 8-bits to write to the I/O Port.
;
; Output:
;  VOID.
;
; Modified:
;
; Referrals:
;
; Notes:
;
;<AMI_PHDR_END>
;*************************************************************************
IoWrite8 proc
    mov al, dl
    mov dx, cx
    out dx, al
    ret
IoWrite8 endp

END
;*************************************************************************
;*************************************************************************
;**                                                                     **
;**        (C)Copyright 1985-2009, American Megatrends, Inc.            **
;**                                                                     **
;**                       All Rights Reserved.                          **
;**                                                                     **
;**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
;**                                                                     **
;**                       Phone: (770)-246-8600                         **
;**                                                                     **
;*************************************************************************
