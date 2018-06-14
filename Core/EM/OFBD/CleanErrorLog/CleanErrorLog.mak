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
# $Header: /Alaska/SOURCE/Modules/OFBD/CleanErrorLog/CleanErrorLog.mak 2     3/16/11 10:32p Terrylin $
#
# $Revision: 2 $
#
# $Date: 3/16/11 10:32p $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/OFBD/CleanErrorLog/CleanErrorLog.mak $
# 
# 2     3/16/11 10:32p Terrylin
# [TAG]  		EIP51285
# [Category]  	Improvement
# [Description]  	Fill the description for user more clearly.
# [Files]  		CleanErrorLog.mak
# CleanErrorLog.h
# CleanErrorLog.c
# 
# 1     1/17/11 3:56a Terrylin
#  
#*************************************************************************
#<AMI_FHDR_START>
#
# Name:	CleanErrorLog.mak
#
# Description:	Make file for the CleanErrorLog.obj
#
#<AMI_FHDR_END>
#*************************************************************************
all : CLEANERRORLOG

CLEANERRORLOG : $(BUILD_DIR)\CLEANERRORLOG.mak CLEANERRORLOGBin

$(BUILD_DIR)\CLEANERRORLOG.mak : $(OFBD_CLEANERRORLOG_DIR)\$(@B).cif $(OFBD_CLEANERRORLOG_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(OFBD_CLEANERRORLOG_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

CLEANERRORLOGBin :
	@set INCLUDE=%%INCLUDE%%
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\CLEANERRORLOG.mak all\
        NAME=CLEANERRORLOG \
		TYPE=LIBRARY LIBRARY_NAME=$(CLEANERRORLOGLIB)

$(CLEANERRORLOGLIB) : CLEANERRORLOG

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


