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
# $Header: /Alaska/SOURCE/Modules/OFBD/DEFCFG/DefCfg.mak 2     3/16/11 10:37p Terrylin $
#
# $Revision: 2 $
#
# $Date: 3/16/11 10:37p $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/OFBD/DEFCFG/DefCfg.mak $
# 
# 2     3/16/11 10:37p Terrylin
# [TAG]  		EIP51285
# [Category]  	Improvement
# [Description]  	Fill the description for user more clearly.
# [Files]  		DefCfg.mak
# DefCfg.h
# DefCfg.c
# 
# 1     5/06/10 2:21a Lawrencechang
# Initial check-in.
# 
#*************************************************************************
#<AMI_FHDR_START>
#
# Name:	DefCfg.mak
#
# Description:	Make file for the DefCfg.obj
#
#<AMI_FHDR_END>
#*************************************************************************
all : DEFCFG

DEFCFG : $(BUILD_DIR)\DEFCFG.mak DEFCFGBin

$(BUILD_DIR)\DEFCFG.mak : $(OFBD_DEFCFG_DIR)\$(@B).cif $(OFBD_DEFCFG_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(OFBD_DEFCFG_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

DEFCFGBin :
	@set INCLUDE=%%INCLUDE%%
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\DEFCFG.mak all\
        NAME=DEFCFG \
		TYPE=LIBRARY LIBRARY_NAME=$(DEFCFGLIB)

$(DEFCFGLIB) : DEFCFG

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


