#//**********************************************************************
#//**********************************************************************
#//**                                                                  **
#//**        (C)Copyright 1985-2008, American Megatrends, Inc.         **
#//**                                                                  **
#//**                       All Rights Reserved.                       **
#//**                                                                  **
#//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
#//**                                                                  **
#//**                       Phone: (770)-246-8600                      **
#//**                                                                  **
#//**********************************************************************
#//**********************************************************************

#**********************************************************************
# $Header: /Alaska/BIN/Modules/Network/UEFINetworkStack II/Common/UefiPxeBc/UefiPxeBc.mak 2     5/01/12 9:49a Hari $
#
# Revision: $
#
# $Date: 5/01/12 9:49a $
#**********************************************************************
# Revision History
# ----------------
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	UefiPxeBc.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************
all : UefiPxeBc

UefiPxeBc : $(BUILD_DIR)\UefiPxeBc.ffs

!IF "$(x64_BUILD)"=="1"
$(BUILD_DIR)\UefiPxeBc.ffs : $(UefiPxeBc_DIR)\UefiPxeBcDxe.efi
!ELSE
$(BUILD_DIR)\UefiPxeBc.ffs : $(UefiPxeBc_DIR)\UefiPxeBcDxeIa32.efi
!ENDIF
	$(MAKE) /f Core\FFS.mak \
	BUILD_DIR=$(BUILD_DIR) \
	GUID=0EF8A3B1-388A-4b62-8BE6-C7877D50AEDF\
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