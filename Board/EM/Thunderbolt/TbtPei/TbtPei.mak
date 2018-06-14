#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************

#**********************************************************************
# $Header: /Alaska/SOURCE/Modules/Thunderbolt/TbtPei/TbtPei.mak 1     1/10/13 4:55a Barretlin $
#
# $Revision: 1 $
#
# $Date: 1/10/13 4:55a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/Thunderbolt/TbtPei/TbtPei.mak $
# 
# 1     1/10/13 4:55a Barretlin
# Change SS path and update module for Thunderbolt Spec 1.6 for Cactus
# Ridge chip and Thunderbolt Spec 0.5 for Redwood Ridge chip
# 
# 2     3/05/12 1:21a Barretlin
# [TAG]  		EIP83266
# [Category]  	Spec Update
# [Description]  	Specificatoin Update 0.90
# [Files]  		TbtSetup.sdl
# TbtSetup.sd
# TbtSetup.uni
# TbtSetup.cif
# TbtOemBoard.h
# TbtOemLib.c
# TbtOemLib.h
# TbtSmm.c
# TbtPei..
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	TbtPei.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************
all : TbtPei

TbtPei : $(BUILD_DIR)\TbtPei.mak TbtPeiBin

$(BUILD_DIR)\TbtPei.mak : $(TbtPei_DIR)\$(@B).cif $(TbtPei_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(TbtPei_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

TbtPeiBin : $(AMICSPLib) $(AMIPEILIB) 
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\TbtPei.mak all\
		GUID=1A8E9D96-66E6-461B-95D6-882C984D0B00\
		ENTRY_POINT=TbtPeiEntry\
        "MY_INCLUDES=$(TBT_OEMBOARD_INCLUDES)"\
		TYPE=PEIM \
		DEPEX1=$(TbtPei_DIR)\TbtPei.dxs \
		DEPEX1_TYPE=EFI_SECTION_PEI_DEPEX \
		COMPRESS=0\
#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************