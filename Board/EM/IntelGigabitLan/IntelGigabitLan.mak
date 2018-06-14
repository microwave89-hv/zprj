#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2004, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************

#**********************************************************************
# $Header: /Alaska/BIN/Modules/Network/Intel/INTELGIGABITLAN/IntelGigabitLan.mak 1     6/11/09 5:24p Hari $
#
# Revision: 1 $
#
# $Date: 6/11/09 5:24p $
#**********************************************************************
# Revision History
# ----------------
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	Zoar.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************
all : IntelGigabitLan

IntelGigabitLan : $(BUILD_DIR)\IntelGigabitLan.ffs

!IF "$(x64_BUILD)"=="1"
$(BUILD_DIR)\IntelGigabitLan.ffs : $(IntelGigabitLan_DIR)\IntelGigabitLanx64.efi
!ELSE
$(BUILD_DIR)\IntelGigabitLan.ffs : $(IntelGigabitLan_DIR)\IntelGigabitLanIa32.efi
!ENDIF
	$(MAKE) /f Core\FFS.mak \
	BUILD_DIR=$(BUILD_DIR) \
	GUID=4953F720-006D-41f5-990D-0AC7742ABB60 \
	TYPE=EFI_FV_FILETYPE_DRIVER \
	PEFILE=$** FFSFILE=$@ COMPRESS=1 NAME=$(**B)
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2004, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************