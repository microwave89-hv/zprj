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
# $Header: /Alaska/SOURCE/Modules/OFBD/OEMPWDCK/OEMPwdCk.mak 2     3/16/11 10:34p Terrylin $
#
# $Revision: 2 $
#
# $Date: 3/16/11 10:34p $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/OFBD/OEMPWDCK/OEMPwdCk.mak $
# 
# 2     3/16/11 10:34p Terrylin
# [TAG]  		EIP51285
# [Category]  	Improvement
# [Description]  	Fill the description for user more clearly.
# [Files]  		OEMPwdCk.mak
# OEMPwdCk.c
# OEMPwdCk.h
# 
# 1     4/13/09 5:47a Lawrencechang
# Initial check-in.
# 
# 1     3/18/07 5:23p Felixp
# 
#*************************************************************************
#<AMI_FHDR_START>
#
# Name:	OEMPwdCk.mak
#
# Description:	Make file for the OEMPwdCk.obj
#
#<AMI_FHDR_END>
#*************************************************************************
all : OEMPWDCK

OEMPWDCK : $(BUILD_DIR)\OEMPwdCk.mak OEMPWDCKBin

$(BUILD_DIR)\OEMPwdCk.mak : $(OFBD_OEMPWDCK_DIR)\$(@B).cif $(OFBD_OEMPWDCK_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(OFBD_OEMPWDCK_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

OEMPWDCKBin :
	@set INCLUDE=%%INCLUDE%%
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\OEMPwdCk.mak all\
        NAME=OEMPWDCK \
		TYPE=LIBRARY LIBRARY_NAME=$(OEMPWDCKLIB)

$(OEMPWDCKLIB) : OEMPWDCK
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

