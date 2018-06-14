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
# $Header: /Alaska/SOURCE/Core/Modules/x64Core/AmiX64Lib.mak 1     10/13/06 8:37p Felixp $
#
# $Revision: 1 $
#
# $Date: 10/13/06 8:37p $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Core/Modules/x64Core/AmiX64Lib.mak $
# 
# 1     10/13/06 8:37p Felixp
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	AmiX64Lib.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************
AmiX64Lib : $(BUILD_DIR)\AmiX64Lib.mak AmiX64LibBin

$(BUILD_DIR)\AmiX64Lib.mak : $(AmiX64Lib_DIR)\$(@B).cif $(AmiX64Lib_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(AmiX64Lib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

!IF "$(PROCESSOR)"=="x64"
AmiDxeLibBin : $(BUILD_DIR)\AmiX64Lib.lib
$(BUILD_DIR)\AmiX64Lib.lib : AmiX64Lib
!ENDIF

AmiX64LibBin :
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\AmiX64Lib.mak all\
		TYPE=LIBRARY
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