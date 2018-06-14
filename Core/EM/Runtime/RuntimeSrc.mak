#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
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
# $Header: /Alaska/SOURCE/Core/Runtime/RuntimeSrc.mak 5     6/24/09 4:22p Robert $
#
# $Revision: 5 $
#
# $Date: 6/24/09 4:22p $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Core/Runtime/RuntimeSrc.mak $
# 
# 5     6/24/09 4:22p Robert
# Updated copyright and file description
# 
# 4     8/24/06 9:28a Felixp
# NVRAM removed (separate NVRAM component is created)
# 
# 3     12/02/05 11:20a Felixp
# 
# 2     8/23/05 12:02p Felixp
# dependency from Token.h in debug mode added
# 
# 1     1/28/05 12:45p Felixp
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	RuntimeSrc.mak
#
# Description:	
#   This file contains the build commands to create the Runtime Library
#
#<AMI_FHDR_END>
#**********************************************************************
all : Runtime_LIB

$(Runtime_LIB) : Runtime_LIB

Runtime_LIB : $(BUILD_DIR)\RuntimeSrc.mak Runtime_LIBBin

$(BUILD_DIR)\RuntimeSrc.mak : $(RUNTIME_DIR)\$(@B).cif $(RUNTIME_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(RUNTIME_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

Runtime_LIBBin : 
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\RuntimeSrc.mak all\
		TYPE=LIBRARY LIBRARY_NAME=$(Runtime_LIB)
#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************