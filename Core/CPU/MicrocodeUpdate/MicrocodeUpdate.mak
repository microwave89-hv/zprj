#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1987-2013, American Megatrends, Inc.            **
#**                                                                     **
#**                       All Rights Reserved.                          **
#**                                                                     **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
#**                                                                     **
#**                       Phone: (770)-246-8600                         **
#**                                                                     **
#*************************************************************************
#*************************************************************************

#************************************************************************//
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/Haswell/AMI Cpu PKG/CPU Core/MicrocodeUpdate/MicrocodeUpdate.mak 1     2/07/12 3:59a Davidhsieh $
#
# $Revision: 1 $
#
# $Date: 2/07/12 3:59a $
#************************************************************************//
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/Haswell/AMI Cpu PKG/CPU Core/MicrocodeUpdate/MicrocodeUpdate.mak $
# 
# 1     2/07/12 3:59a Davidhsieh
# 
#************************************************************************//

all : MicrocodeUpdate

MicrocodeUpdate: $(BUILD_DIR)\MicrocodeUpdate.mak MicrocodeUpdateBin

$(BUILD_DIR)\MicrocodeUpdate.mak : $(MICROCODEUPDATE_PATH)\MicrocodeUpdate.cif $(MICROCODEUPDATE_PATH)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(MICROCODEUPDATE_PATH)\MicrocodeUpdate.cif $(CIF2MAK_DEFAULTS)

MicrocodeUpdateBin : $(AMIDXELIB) $(FLASHLIB) $(AMICSPLib)
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\MicrocodeUpdate.mak all\
		GUID=F3331DE6-4A55-44e4-B767-7453F7A1A021\
		ENTRY_POINT=InitializeMicrocodeSmm\
		TYPE=BS_DRIVER \
		COMPRESS=1


#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1987-2013, American Megatrends, Inc.            **
#**                                                                     **
#**                       All Rights Reserved.                          **
#**                                                                     **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
#**                                                                     **
#**                       Phone: (770)-246-8600                         **
#**                                                                     **
#*************************************************************************
#*************************************************************************
