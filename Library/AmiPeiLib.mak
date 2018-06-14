#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2006, American Megatrends, Inc.         **
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
# $Header: /Alaska/SOURCE/Core/Library/AmiPeiLib.mak 7     8/25/06 10:55a Felixp $
#
# $Revision: 7 $
#
# $Date: 8/25/06 10:55a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Core/Library/AmiPeiLib.mak $
# 
# 7     8/25/06 10:55a Felixp
# 
# 6     8/24/06 9:27a Felixp
# Preliminary x64 support (work in progress)
# 
# 5     3/17/06 4:24p Felixp
# 
# 4     12/02/05 11:19a Felixp
# 
# 3     1/28/05 1:09p Felixp
# 
# 2     1/18/05 3:22p Felixp
# PrintDebugMessage renamed to Trace
# 
# 1     12/23/04 9:42a Felixp
# 
# 6     12/15/04 9:06p Felixp
# LegacyBoot application added
# Minor build process improvements
# 
# 5     11/05/04 7:55p Felixp
# 
# 4     11/01/04 7:59a Felixp
# 
# 3     10/05/04 5:39p Felixp
# 
# 1     10/04/04 4:34p Felixp
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	AmiPeiLib.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************
all : AmiPeiLib

AmiPeiLib_DIR=$(LIBRARY_DIR)

AmiPeiLib : $(BUILD_DIR)\AmiPeiLib.mak AmiPeiLibBin

$(BUILD_DIR)\AmiPeiLib.mak : $(AmiPeiLib_DIR)\$(@B).cif $(AmiPeiLib_DIR)\$(@B).mak $(BUILD_RULES) $(LIBRARY_DIR)\AmiLib.cif
	$(CIF2MAK) $(AmiPeiLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS) $(LIBRARY_DIR)\AmiLib.cif

AmiPeiLibBin :
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
!IF "$(x64_BUILD)"=="1"
		BUILD_DIR=$(BUILD_DIR)\IA32\
		"CFLAGS=$(CFLAGS) /D\"PE_LOADER_SUPPORT_ALL=1\""\
!ELSE
		BUILD_DIR=$(BUILD_DIR)\
!ENDIF
		/f $(BUILD_DIR)\AmiPeiLib.mak all\
		TYPE=PEI_LIBRARY LIBRARY_NAME=$(BUILD_DIR)\AmiPeiLib.lib

$(BUILD_DIR)\AmiPeiLib.lib : AmiPeiLib
#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2006, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************