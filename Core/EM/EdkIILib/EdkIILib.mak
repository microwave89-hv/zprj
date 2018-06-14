#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2008, American Megatrends, Inc.            **
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
# $Header: /Alaska/SOURCE/Core/EdkIICompLib/EdkIILib.mak 1     5/05/11 5:06p Artems $
#
# $Revision: 1 $
#
# $Date: 5/05/11 5:06p $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Core/EdkIICompLib/EdkIILib.mak $
# 
# 1     5/05/11 5:06p Artems
# EdkII compatibility library
# 
#*************************************************************************
#<AMI_FHDR_START>
#
# Name: EdkIILib.mak
#
# Description:
# 
#
#<AMI_FHDR_END>
#*************************************************************************

#CORE_DXEBin : 


$(EDK_II_LIB) : $(BUILD_DIR)\EdkIILib.mak EdkIILibBin

$(BUILD_DIR)\EdkIILib.mak : $(EdkIILib_DIR)\EdkIILib.cif $(BUILD_RULES)
    $(CIF2MAK) $(EdkIILib_DIR)\EdkIILib.cif $(CIF2MAK_DEFAULTS)

EdkIILibBin : 
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
	/f $(BUILD_DIR)\EdkIILib.mak all\
	NAME=EdkIILib\
        MAKEFILE=$(BUILD_DIR)\EdkIILib.mak\
        TYPE=LIBRARY
