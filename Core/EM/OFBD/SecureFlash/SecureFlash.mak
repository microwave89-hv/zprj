#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
#**                                                                     **
#**                       All Rights Reserved.                          **
#**                                                                     **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
#**                                                                     **
#**                       Phone: (770)-246-8600                         **
#**                                                                     **
#*************************************************************************
#*************************************************************************

#*************************************************************************
# $Header: /Alaska/SOURCE/Modules/OFBD Secure Flash/SecureFlash.mak 4     1/04/12 7:11a Lawrencechang $
#
# $Revision: 4 $
#
# $Date: 1/04/12 7:11a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/OFBD Secure Flash/SecureFlash.mak $
# 
# 4     1/04/12 7:11a Lawrencechang
# Remove SMIFlash related make rules.
# 
# 3     10/29/11 5:30a Lawrencechang
# Modified for adding SMIFlash protocol compatibility.
# 
# 2     10/03/11 2:36a Lawrencechang
# Modify path of SecSMIFlashHook.obj to adapt the latest version
# SecureFlashPkg.
# 
# 1     9/16/11 4:25a Lawrencechang
# Initial check-in.
# 
#*************************************************************************
#<AMI_FHDR_START>
#
# Name:	SecureFlash.mak
#
# Description:	Make file for OFBD Secure Flash module.
#
#<AMI_FHDR_END>
#*************************************************************************

$(OFBD_SECUREFLASH_LIB) : $(BUILD_DIR)\SecureFlash.mak OFBD_SECUREFLASH_BIN

OFBD_SECFLASH_EXT_INCLUDES = \
	/I $(OFBD_DIR)\
	/I $(OFBD_SECURE_FLASH_DIR)

$(BUILD_DIR)\SecureFlash.mak : $(OFBD_SECURE_FLASH_DIR)\$(@B).cif
	$(CIF2MAK) $(OFBD_SECURE_FLASH_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

OFBD_SECUREFLASH_BIN : $(AMIDXELIB) $(FLASHLIB) $(OFBD_EXT_OBJS)
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
	/f $(BUILD_DIR)\SecureFlash.mak all\
	"MY_INCLUDES=$(OFBD_SECFLASH_EXT_INCLUDES)"\
	NAME=SecureFlash TYPE=LIBRARY LIBRARY_NAME=$(OFBD_SECUREFLASH_LIB)

#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
#**                                                                     **
#**                       All Rights Reserved.                          **
#**                                                                     **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
#**                                                                     **
#**                       Phone: (770)-246-8600                         **
#**                                                                     **
#*************************************************************************
#*************************************************************************
