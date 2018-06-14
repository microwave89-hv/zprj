#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2005, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************

#**********************************************************************
# $Header: /Alaska/SOURCE/Core/Library/AmiDxeLib.mak 7     8/24/06 9:27a Felixp $
#
# $Revision: 7 $
#
# $Date: 8/24/06 9:27a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Core/Library/AmiDxeLib.mak $
# 
# 7     8/24/06 9:27a Felixp
# Preliminary x64 support (work in progress)
# 
# 6     3/17/06 4:24p Felixp
# 
# 5     12/02/05 11:19a Felixp
# 
# 4     7/28/05 3:56p Yul
# dependecy deom token.h added
# 
# 3     1/28/05 1:09p Felixp
# 
# 2     1/18/05 3:22p Felixp
# PrintDebugMessage renamed to Trace
# 
# 1     12/23/04 9:42a Felixp
# 
# 5     12/15/04 9:06p Felixp
# LegacyBoot application added
# Minor build process improvements
# 
# 4     11/05/04 7:55p Felixp
# 
# 3     11/01/04 7:59a Felixp
# 
# 2     10/05/04 5:36p Felixp
# 
# 1     10/04/04 4:34p Felixp
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	AmiDxeLib.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************
all : AmiDxeLib

AmiDxeLib_DIR=$(LIBRARY_DIR)

AmiDxeLib : $(BUILD_DIR)\AmiDxeLib.mak AmiDxeLibBin

$(BUILD_DIR)\AmiDxeLib.mak : $(AmiDxeLib_DIR)\$(@B).cif $(AmiDxeLib_DIR)\$(@B).mak $(BUILD_RULES) $(LIBRARY_DIR)\AmiLib.cif
	$(CIF2MAK) $(AmiDxeLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS) $(LIBRARY_DIR)\AmiLib.cif

AmiDxeLibBin :
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\AmiDxeLib.mak all\
!IF $(DEBUG_MODE)!=0
		EXT_HEADERS=$(BUILD_DIR)\token.h\
!ENDIF
		TYPE=LIBRARY

$(BUILD_DIR)\AmiDxeLib.lib : AmiDxeLib
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2005, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************