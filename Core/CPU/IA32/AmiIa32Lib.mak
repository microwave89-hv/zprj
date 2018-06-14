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
# $Header: /Alaska/SOURCE/Core/Modules/IA32Core/AmiIa32Lib.mak 1     10/13/06 8:36p Felixp $
#
# $Revision: 1 $
#
# $Date: 10/13/06 8:36p $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Core/Modules/IA32Core/AmiIa32Lib.mak $
# 
# 1     10/13/06 8:36p Felixp
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	AmiIa32Lib.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************
AmiIa32Lib : $(BUILD_DIR)\AmiIa32Lib.mak AmiIa32LibBin

$(BUILD_DIR)\AmiIa32Lib.mak : $(AmiIa32Lib_DIR)\$(@B).cif $(AmiIa32Lib_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(AmiIa32Lib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

!IF "$(PROCESSOR)"=="" || "$(PROCESSOR)"=="IA32"
AmiDxeLibBin : $(BUILD_DIR)\AmiIa32Lib.lib
AmiPeiLibBin : $(BUILD_DIR)\AmiIa32Lib.lib
$(BUILD_DIR)\AmiIa32Lib.lib : AmiIa32Lib
!ELSEIF "$(PROCESSOR)"=="x64"
AmiPeiLibBin : $(BUILD_DIR)\AmiIa32Lib.lib
$(BUILD_DIR)\AmiIa32Lib.lib : AmiIa32Lib
!ENDIF

AmiIa32LibBin :
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\AmiIa32Lib.mak all\
		TYPE=PEI_LIBRARY
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