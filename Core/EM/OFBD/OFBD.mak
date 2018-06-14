#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2013, American Megatrends, Inc.            **
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
# $Header: /Alaska/SOURCE/Modules/OFBD/OFBD.mak 6     8/15/13 5:35a Terrylin $
#
# $Revision: 6 $
#
# $Date: 8/15/13 5:35a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/OFBD/OFBD.mak $
# 
# 6     8/15/13 5:35a Terrylin
# [Category]  	Bug Fix
# [Severity]  	Important
# [Symptom]  	Build Error
# [Files]  		OFBD.mak
# OFBD.c
# 
# 5     6/14/13 3:54a Terrylin
# [Category]  	Improvement
# [Description]  	Add the Not InSmmFuncList support.
# [Files]  		OFBD.sdl
# OFBD.mak
# OFBD.c
# 
# 4     3/16/11 10:39p Terrylin
# Correct Copyright information.
# 
# 3     3/16/11 10:13p Terrylin
# [TAG]  		EIP51285
# [Category]  	Improvement
# [Description]  	Fill the description of each file for user more
# clearly.
# [Files]  		OFBD.mak
# OFBD.dxs
# OFBD.c
# OFBD.h
# 
# 2     7/02/09 5:53a Klzhan
# Improvement:    Add an E-Link in SMM.
# 
# 1     4/13/09 5:46a Lawrencechang
# Initial check-in.
# 
# 1     3/18/07 5:23p Felixp
# 
#*************************************************************************
#<AMI_FHDR_START>
#
# Name:	OFBD.mak
#
# Description:	Make file for the OFBD.obj
#
#<AMI_FHDR_END>
#*************************************************************************
all : OFBD

OFBD : $(BUILD_DIR)\OFBD.mak OFBDBin

$(BUILD_DIR)\OFBD.mak : $(OFBD_DIR)\$(@B).cif $(OFBD_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(OFBD_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

OFBD_ELINK_LISTS = \
/D\"OFBD_SMM_FUNC_LIST=$(OFBDInSmmFuncList)\"\
/D\"OFBD_NOT_SMM_FUNC_LIST=$(OFBDNotInSmmFuncList)\"

OFBDBin : $(AMIDXELIB) $(OFBDLISTLIB)
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\OFBD.mak all\
        NAME=OFBD\
		GUID=57E56594-CE95-46ad-9531-3C49310CA7CE\
		ENTRY_POINT=OFBDEntryPoint\
        "INIT_LIST=$(OFBDPartsList)"\
!IF $(PI_SPECIFICATION_VERSION) >= 0x1000A
        TYPE=DXESMM_DRIVER\
        DEPEX1=$(OFBD_DIR)\OFBD.dxs \
        DEPEX1_TYPE=EFI_SECTION_SMM_DEPEX \
!ELSE
        TYPE=BS_DRIVER\
        DEPEX1=$(OFBD_DIR)\OFBD.dxs \
        DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX \
!ENDIF		 
        "CFLAGS=$(CFLAGS) /DVFRCOMPILE $(OFBD_ELINK_LISTS)"\
		COMPRESS=1\
#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2013, American Megatrends, Inc.            **
#**                                                                     **
#**                       All Rights Reserved.                          **
#**                                                                     **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
#**                                                                     **
#**                       Phone: (770)-246-8600                         **
#**                                                                     **
#*************************************************************************
#*************************************************************************
