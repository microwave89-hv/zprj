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
# $Header: /Alaska/SOURCE/Modules/OFBD/OEMROMHOLE/OEMROMHOLE.mak 2     3/16/11 10:33p Terrylin $
#
# $Revision: 2 $
#
# $Date: 3/16/11 10:33p $
##*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/OFBD/OEMROMHOLE/OEMROMHOLE.mak $
# 
# 2     3/16/11 10:33p Terrylin
# [TAG]  		EIP51285
# [Category]  	Improvement
# [Description]  	Fill the description for user more clearly.
# [Files]  		OEMROMHOLE.mak
# OEMROMHOLE.c
# OEMROMHOLE.h
# 
# 1     12/16/09 12:50a Lawrencechang
# Initial check-in.
# 
#*************************************************************************
#<AMI_FHDR_START>
#
# Name:	OEMROMHOLE.mak
#
# Description:	Make file for the OEMROMHOLE.obj
#
#<AMI_FHDR_END>
#*************************************************************************
all : OEMROMHOLE

OEMROMHOLE : $(BUILD_DIR)\OEMROMHOLE.mak OEMROMHOLEBin

$(BUILD_DIR)\OEMROMHOLE.mak : $(OFBD_OEMROMHOLE_DIR)\$(@B).cif $(OFBD_OEMROMHOLE_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(OFBD_OEMROMHOLE_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

OEMROMHOLEBin :
	@set INCLUDE=%%INCLUDE%%
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\OEMROMHOLE.mak all\
        NAME=OEMROMHOLE \
		TYPE=LIBRARY LIBRARY_NAME=$(OEMROMHOLELIB)

$(OEMROMHOLELIB) : OEMROMHOLE
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

