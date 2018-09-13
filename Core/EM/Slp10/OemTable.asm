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

;*****************************************************************************
; $Header: /Alaska/SOURCE/Modules/Slp10/OemTable.asm 1     6/18/09 5:31p Vyacheslava $
;
; $Revision: 1 $
;
; $Date: 6/18/09 5:31p $
;*****************************************************************************
; Revision History
; ----------------
; $Log: /Alaska/SOURCE/Modules/Slp10/OemTable.asm $
; 
; 1     6/18/09 5:31p Vyacheslava
; Initial Creation
; 
;*****************************************************************************
;<AMI_FHDR_START>
;
; Name: OemTable.asm
;
; Description: This is OEM table binary for Aptio Firmware Volume.
;
;<AMI_FHDR_END>
;*****************************************************************************

	INCLUDE token.equ

.686p
.model flat
.data

slp_string_size SIZESTR MKF_SLP_STRING

    DB '$ODB$', 0
    DW 001h
    DW MKF_OEM_DATA_SPACE_SIZE
    DB @CATSTR(<!'>,%MKF_SLP_STRING,<!'>)
    DB [MKF_OEM_DATA_SPACE_SIZE - slp_string_size] DUP (0)

end

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
