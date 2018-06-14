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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/Haswell/AMI Cpu PKG/CPU Core/MiscX64Lib/MiscX64Lib.mak 1     5/15/12 5:41a Davidhsieh $
#
# $Revision: 1 $
#
# $Date: 5/15/12 5:41a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/Haswell/AMI Cpu PKG/CPU Core/MiscX64Lib/MiscX64Lib.mak $
# 
# 1     5/15/12 5:41a Davidhsieh
# 
# 1     5/08/12 6:02a Dukeyeh
# [TAG]  		EIP89382
# [Category]  	Improvement
# [Description]  	clear direction flag inside Timer callback function.
# [Files]  		MiscX64Lib.cif
# Misc.asm
# MiscX64Lib.sdl
# MiscX64Lib.mak
# 
# 1     10/13/06 8:37p Felixp
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	MiscX64Lib.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************
MiscX64Lib : $(BUILD_DIR)\MiscX64Lib.mak MiscX64LibBin

$(BUILD_DIR)\MiscX64Lib.mak : $(MiscX64Lib_DIR)\$(@B).cif $(MiscX64Lib_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(MiscX64Lib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

!IF "$(PROCESSOR)"=="x64"
AmiDxeLibBin : $(BUILD_DIR)\MiscX64Lib.lib
$(BUILD_DIR)\MiscX64Lib.lib : MiscX64Lib
!ENDIF

MiscX64LibBin :
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\MiscX64Lib.mak all\
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