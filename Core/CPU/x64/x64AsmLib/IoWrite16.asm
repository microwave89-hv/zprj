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
; $Header: /Alaska/SOURCE/Core/Modules/x64Core/x64AsmLib/IoWrite16.asm 1     10/01/10 5:07p Felixp $
;
; $Revision: 1 $
;
; $Date: 10/01/10 5:07p $
;*************************************************************************
; Revision History
; ----------------
; $Log: /Alaska/SOURCE/Core/Modules/x64Core/x64AsmLib/IoWrite16.asm $
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
; Name: IoWrite16
;
; Description:
;  VOID IoWrite16(IN UINT16 Port, IN UINT16 Value) writes the 16-bit Value
; to the I/O port defined by Port.
;
; Input:
;  IN UINT16 Port
; I/O port to write 16-bits to.
;
;  IN UINT16 Value
; 16-bits to write to the I/O Port.
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
IoWrite16 proc
    mov ax, dx
    mov dx, cx
    out dx, ax
    ret
IoWrite16 endp

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
