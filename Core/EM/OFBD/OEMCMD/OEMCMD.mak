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
# $Header: /Alaska/SOURCE/Modules/OFBD/OEMCMD/OEMCMD.mak 2     3/16/11 10:36p Terrylin $
#
# $Revision: 2 $
#
# $Date: 3/16/11 10:36p $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/OFBD/OEMCMD/OEMCMD.mak $
# 
# 2     3/16/11 10:36p Terrylin
# [TAG]  		EIP51285
# [Category]  	Improvement
# [Description]  	Fill the description for user more clearly.
# [Files]  		OEMCMD.mak
# OEMCMD.h
# OEMCMD.c
# 
# 1     5/06/10 2:23a Lawrencechang
# Initial check-in.
# 
#*************************************************************************
#<AMI_FHDR_START>
#
# Name:	OEMCMD.mak
#
# Description:	Make file for the OEMCMD.obj
#
#<AMI_FHDR_END>
#*************************************************************************
all : OEMCMD

OEMCMD : $(BUILD_DIR)\OEMCMD.mak OEMCMDBin

$(BUILD_DIR)\OEMCMD.mak : $(OFBD_OEMCMD_DIR)\$(@B).cif $(OFBD_OEMCMD_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(OFBD_OEMCMD_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

OEMCMDBin :
	@set INCLUDE=%%INCLUDE%%
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\OEMCMD.mak all\
        NAME=OEMCMD \
		TYPE=LIBRARY LIBRARY_NAME=$(OEMCMDLIB)

$(OEMCMDLIB) : OEMCMD
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

