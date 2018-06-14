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
; $Header: /Alaska/SOURCE/Core/Modules/x64Core/x64AsmLib/IoRead16.asm 1     10/01/10 5:07p Felixp $
;
; $Revision: 1 $
;
; $Date: 10/01/10 5:07p $
;*************************************************************************
; Revision History
; ----------------
; $Log: /Alaska/SOURCE/Core/Modules/x64Core/x64AsmLib/IoRead16.asm $
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
; Name: IoRead16
;
; Description:
;  UINT16 IoRead16(IN UINT16 Port) reads the 16-bit value stored at the I/O
; port defined by Port.
;
; Input:
;  IN UINT16 Port
; I/O port to read 16-bits from.
;
; Output:
;  UINT16 value stored at I/O Port.
;
; Modified:
;
; Referrals:
;
; Notes:
;
;<AMI_PHDR_END>
;*************************************************************************
IoRead16 proc
    mov dx, cx
    in  ax, dx
    ret
IoRead16 endp

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
