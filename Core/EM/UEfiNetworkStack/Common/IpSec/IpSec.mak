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
# $Header: /Alaska/BIN/Modules/Network/UEFINetworkStack II/Common/IpSec/IpSec.mak 2     5/01/12 9:57a Hari $
#
# Revision: $
#
# $Date: 5/01/12 9:57a $
#**********************************************************************
# Revision History
# ----------------
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	IpSec.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************
all : IpSec

IpSec : $(BUILD_DIR)\IpSec.ffs

!IF "$(x64_BUILD)"=="1"
$(BUILD_DIR)\IpSec.ffs : $(IpSec_DIR)\IpSecDxe.efi
!ELSE
$(BUILD_DIR)\IpSec.ffs : $(IpSec_DIR)\IpSecDxeIa32.efi
!ENDIF
	$(MAKE) /f Core\FFS.mak \
	BUILD_DIR=$(BUILD_DIR) \
	GUID=FCF94301-9763-4a64-AA84-7892C4712367\
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