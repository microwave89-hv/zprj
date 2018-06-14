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
# $Header: /Alaska/SOURCE/Modules/OFBD/OEMROMID/OEMROMID.mak 2     3/16/11 10:35p Terrylin $
#
# $Revision: 2 $
#
# $Date: 3/16/11 10:35p $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/OFBD/OEMROMID/OEMROMID.mak $
# 
# 2     3/16/11 10:35p Terrylin
# [TAG]  		EIP51285
# [Category]  	Improvement
# [Description]  	Fill the description for user more clearly.
# [Files]  		OEMROMID.mak
# OEMROMID.h
# OEMROMID.c
# 
# 1     4/13/09 5:46a Lawrencechang
# Initial check-in.
# 
# 1     3/18/07 5:23p Felixp
# 
#*************************************************************************
#<AMI_FHDR_START>
#
# Name:	OEMROMID.mak
#
# Description:	Make file for the OEMROMID.obj
#
#<AMI_FHDR_END>
#**********************************************************************
all : OEMROMID

OEMROMID : $(BUILD_DIR)\OEMROMID.mak OEMROMIDBin

$(BUILD_DIR)\OEMROMID.mak : $(OFBD_OEMROMID_DIR)\$(@B).cif $(OFBD_OEMROMID_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(OFBD_OEMROMID_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

OEMROMIDBin :
	@set INCLUDE=%%INCLUDE%%
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\OEMROMID.mak all\
        NAME=OEMROMID \
		TYPE=LIBRARY LIBRARY_NAME=$(OEMROMIDLIB)

$(OEMROMIDLIB) : OEMROMID
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
