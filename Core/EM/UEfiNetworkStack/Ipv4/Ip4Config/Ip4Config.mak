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
# $Header: /Alaska/BIN/Modules/Network/UEFINetworkStack II/IPV4/Ip4Config/Ip4Config.mak 2     5/01/12 10:13a Hari $
#
# Revision: $
#
# $Date: 5/01/12 10:13a $
#**********************************************************************
# Revision History
# ----------------
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	Ip6.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************
all : Ip4Config

Ip4Config : $(BUILD_DIR)\Ip4Config.ffs

!IF "$(x64_BUILD)"=="1"
$(BUILD_DIR)\Ip4Config.ffs : $(Ip4Config_DIR)\Ip4ConfigDxe.efi
!ELSE
$(BUILD_DIR)\Ip4Config.ffs : $(Ip4Config_DIR)\Ip4ConfigDxeIa32.efi
!ENDIF
	$(MAKE) /f Core\FFS.mak \
	BUILD_DIR=$(BUILD_DIR) \
	GUID=8F9296EF-2880-4659-B857-915A8901BDC8\
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