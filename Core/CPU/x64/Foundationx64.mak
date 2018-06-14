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
# $Header: /Alaska/SOURCE/Core/EDK/x64/Foundationx64.mak 1     8/24/06 12:36p Felixp $
#
# $Revision: 1 $
#
# $Date: 8/24/06 12:36p $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Core/EDK/x64/Foundationx64.mak $
# 
# 1     8/24/06 12:36p Felixp
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	Foundationx64.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************
Foundationx64 : $(BUILD_DIR)\Foundationx64.mak Foundationx64Bin

$(BUILD_DIR)\Foundationx64.mak : $(Foundationx64_DIR)\$(@B).cif $(Foundationx64_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(Foundationx64_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

!IF "$(PROCESSOR)"=="x64"
FoundationBin : $(BUILD_DIR)\Foundationx64.lib
$(BUILD_DIR)\Foundationx64.lib : Foundationx64
!ENDIF


Foundationx64Bin :
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\Foundationx64.mak all\
		"CFLAGS=$(CFLAGS) /I$(Foundation_DIR)"\
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