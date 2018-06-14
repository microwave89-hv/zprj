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
# $Header: /Alaska/SOURCE/Core/EDK/IPF/FoundationIPF.mak 1     8/24/06 12:37p Felixp $
#
# $Revision: 1 $
#
# $Date: 8/24/06 12:37p $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Core/EDK/IPF/FoundationIPF.mak $
# 
# 1     8/24/06 12:37p Felixp
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	FoundationIPF.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************
FoundationIPF : $(BUILD_DIR)\FoundationIPF.mak FoundationIPFBin

$(BUILD_DIR)\FoundationIPF.mak : $(FoundationIPF_DIR)\$(@B).cif $(FoundationIPF_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(FoundationIPF_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

!IF "$(PROCESSOR)"=="IPF"
FoundationBin : $(BUILD_DIR)\FoundationIPF.lib
FoundationPeiBin : $(BUILD_DIR)\FoundationIPF.lib
$(BUILD_DIR)\FoundationIPF.lib : FoundationIPF
!ENDIF


FoundationIPFBin :
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\FoundationIPF.mak all\
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