;****************************************************************************
;****************************************************************************
;**                                                                        **
;**           (C)Copyright 1985-2009, American Megatrends, Inc.            **
;**                                                                        **
;**                          All Rights Reserved.                          **
;**                                                                        **
;**            5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093           **
;**                                                                        **
;**                          Phone: (770)-246-8600                         **
;**                                                                        **
;****************************************************************************
;****************************************************************************

;****************************************************************************
; $Header: /Alaska/BIN/Modules/SMBIOS/SmbiosStaticData/SmbiosStaticDataEnd.asm 4     6/02/09 3:57p Davidd $
;
; $Revision: 4 $
;
; $Date: 6/02/09 3:57p $
;****************************************************************************
; Revision History
; ----------------
; $Log: /Alaska/BIN/Modules/SMBIOS/SmbiosStaticData/SmbiosStaticDataEnd.asm $
; 
; 4     6/02/09 3:57p Davidd
; Updated AMI headers (EIP 22180)
; 
; 3     3/29/07 4:53p Davidd
; Changed the year in the AMI banner and adjust indentation to coding
; standard.
; 
; 1     4/29/05 2:15p Davidd
; Initial checkin.
;
;****************************************************************************

;----------------------------------------------------------------------------

	    INCLUDE     token.equ
	    INCLUDE	smbhdr.equ
	    INCLUDE	smbmacro.aid
	    INCLUDE	smbstruc.def
	    INCLUDE	smb.equ
	    INCLUDE	smbdata.mac
	    INCLUDE	smbdesc.def

;----------------------------------------------------------------------------

SMBIOS_DSEG	SEGMENT	BYTE	PUBLIC	'DATA'
	    ASSUME	cs: SMBIOS_DSEG
.586p

;----------------------------------------------------------------------------

;----------------------------------------------------------------------------
;       END Of SMBIOS DATA STRUCTURE
;----------------------------------------------------------------------------

        handle = 0                      ; Dummy handle
        handle = CreateEndOfTable(handle)

        db      MKF_EXTRA_RESERVED_BYTES dup (0FFh)          ; Extra Space

SMBIOS_DSEG	ENDS			; End of Segment
END					; End of File
;----------------------------------------------------------------------------

;****************************************************************************
;****************************************************************************
;**                                                                        **
;**           (C)Copyright 1985-2009, American Megatrends, Inc.            **
;**                                                                        **
;**                          All Rights Reserved.                          **
;**                                                                        **
;**            5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093           **
;**                                                                        **
;**                          Phone: (770)-246-8600                         **
;**                                                                        **
;****************************************************************************
;****************************************************************************
