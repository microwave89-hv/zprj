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
# $Header: /Alaska/SOURCE/Core/EDK/IA32/FoundationIa32.mak 1     8/24/06 12:35p Felixp $
#
# $Revision: 1 $
#
# $Date: 8/24/06 12:35p $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Core/EDK/IA32/FoundationIa32.mak $
# 
# 1     8/24/06 12:35p Felixp
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	FoundationIa32.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************
FoundationIa32 : $(BUILD_DIR)\FoundationIa32.mak FoundationIa32Bin

$(BUILD_DIR)\FoundationIa32.mak : $(FoundationIa32_DIR)\$(@B).cif $(FoundationIa32_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(FoundationIa32_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

!IF "$(PROCESSOR)"=="" || "$(PROCESSOR)"=="IA32"
FoundationBin : $(BUILD_DIR)\FoundationIa32.lib
FoundationPeiBin : $(BUILD_DIR)\FoundationIa32.lib
$(BUILD_DIR)\FoundationIa32.lib : FoundationIa32
!ELSEIF "$(PROCESSOR)"=="x64"
FoundationPeiBin : $(BUILD_DIR)\FoundationIa32.lib
$(BUILD_DIR)\FoundationIa32.lib : FoundationIa32
!ENDIF


FoundationIa32Bin :
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\FoundationIa32.mak all\
		"CFLAGS=$(CFLAGS) /I$(Foundation_DIR)"\
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