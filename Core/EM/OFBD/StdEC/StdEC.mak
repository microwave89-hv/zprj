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
# $Header: /Alaska/SOURCE/Modules/OFBD/StdEC/StdEC.mak 2     3/16/11 10:35p Terrylin $
#
# $Revision: 2 $
#
# $Date: 3/16/11 10:35p $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/OFBD/StdEC/StdEC.mak $
# 
# 2     3/16/11 10:35p Terrylin
# [TAG]  		EIP51285
# [Category]  	Improvement
# [Description]  	Fill the description for user more clearly.
# [Files]  		StdEC.mak
# StdEC.c
# StdEC.h
# 
# 1     4/13/09 5:46a Lawrencechang
# Initial check-in.
# 
# 1     3/18/07 5:23p Felixp
# 
#*************************************************************************
#<AMI_FHDR_START>
#
# Name:	StdEC.mak
#
# Description:	Make file for the StdEC.obj
#
#<AMI_FHDR_END>
#*************************************************************************
all : StdEC

StdEC : $(BUILD_DIR)\StdEC.mak StdECBin

$(BUILD_DIR)\StdEC.mak : $(OFBD_StdEC_DIR)\$(@B).cif $(OFBD_StdEC_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(OFBD_StdEC_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

StdECBin :
	@set INCLUDE=%%INCLUDE%%
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\StdEC.mak all\
        NAME=StdEC \
		TYPE=LIBRARY LIBRARY_NAME=$(STDECLIB)

$(STDECLIB) : StdEC
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
