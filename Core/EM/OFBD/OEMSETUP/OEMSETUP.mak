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
# $Header: /Alaska/SOURCE/Modules/OFBD/OEMSETUP/OEMSETUP.mak 3     3/16/11 10:33p Terrylin $
#
# $Revision: 3 $
#
# $Date: 3/16/11 10:33p $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/OFBD/OEMSETUP/OEMSETUP.mak $
# 
# 3     3/16/11 10:33p Terrylin
# [TAG]  		EIP51285
# [Category]  	Improvement
# [Description]  	Fill the description for user more clearly.
# [Files]  		OEMSETUP.mak
# OEMSETUP.h
# OEMSETUP.c
# 
# 2     5/06/10 2:15a Lawrencechang
# Add a different rule for storing DMI in NVRAM.
# 
# 1     4/13/09 5:47a Lawrencechang
# Initial check-in.
# 
# 1     3/18/07 5:23p Felixp
# 
#*************************************************************************
#<AMI_FHDR_START>
#
# Name:	OEMSETUP.mak
#
# Description:	Make file for the OEMSETUP.obj
#
#<AMI_FHDR_END>
#*************************************************************************
all : OEMSETUP

OEMSETUP : $(BUILD_DIR)\OEMSETUP.mak OEMSETUPBin

$(BUILD_DIR)\OEMSETUP.mak : $(OFBD_OEMSETUP_DIR)\$(@B).cif $(OFBD_OEMSETUP_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(OFBD_OEMSETUP_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

# EIP 37169
!IF "$(SMBIOS_DMIEDIT_DATA_LOC)"=="2" && "$(SMBIOS_PRESERVE_NVRAM)"!="1"
$(BUILD_DIR)\$(SMBIOS_DMIEDIT_DIR)\SmbiosNvramFunc.obj : $(SMBIOS_DMIEDIT_DIR)\SmbiosNvramFunc.c
		mkdir $(BUILD_DIR)\$(SMBIOS_DMIEDIT_DIR)
		$(CC) $(CFLAGS:/W4=/W3) /Fo$(BUILD_DIR)\$(SMBIOS_DMIEDIT_DIR)\ $(SMBIOS_DMIEDIT_DIR)\SmbiosNvramFunc.c 

OEMSETUPBin : $(BUILD_DIR)\$(SMBIOS_DMIEDIT_DIR)\SmbiosNvramFunc.obj
!ELSE
OEMSETUPBin :
!ENDIF
	@set INCLUDE=%%INCLUDE%%
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\OEMSETUP.mak all\
        NAME=OEMSETUP \
		TYPE=LIBRARY LIBRARY_NAME=$(OEMSETUPLIB)

$(OEMSETUPLIB) : OEMSETUP
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