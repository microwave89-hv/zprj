;**********************************************************************
;**********************************************************************
;**                                                                  **
;**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
;**                                                                  **
;**                       All Rights Reserved.                       **
;**                                                                  **
;**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
;**                                                                  **
;**                       Phone: (770)-246-8600                      **
;**                                                                  **
;**********************************************************************
;**********************************************************************

;**********************************************************************
; $Header: /Alaska/SOURCE/Modules/SMBIOS/SmbiosFlashData/SmbiosFlashData.asm 4     6/02/09 11:28a Davidd $
;
; $Revision: 4 $
;
; $Date: 6/02/09 11:28a $
;**********************************************************************
; Revision History
; ----------------
; $Log: /Alaska/SOURCE/Modules/SMBIOS/SmbiosFlashData/SmbiosFlashData.asm $
; 
; 4     6/02/09 11:28a Davidd
; Updated AMI headers (EIP 22180)
; 
; 3     3/29/07 6:13p Davidd
; Changed the year in the AMI banner.
; 
; 2     12/15/06 5:48p Davidd
; Code cleanup and reformatted to coding standard.
; 
; 1     4/29/05 2:06p Davidd
; Initial checkin.
;
;**********************************************************************

	INCLUDE token.equ

.686p
.model  flat
.data
	dd '_ASB'
_FlashDataSize label dword
	dd offset FlashDataEnd - offset FlashDataStart
;align 4
FlashDataStart EQU $
        db MKF_FLASHDATA_SIZE dup (0FFh)
FlashDataEnd label byte
	db 4 dup (0FFh)	;Mark end of table. Same size as each flash data entry.
end

;**********************************************************************
;**********************************************************************
;**                                                                  **
;**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
;**                                                                  **
;**                       All Rights Reserved.                       **
;**                                                                  **
;**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
;**                                                                  **
;**                       Phone: (770)-246-8600                      **
;**                                                                  **
;**********************************************************************
;**********************************************************************
