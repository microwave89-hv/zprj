#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
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
# $Header: /Alaska/SOURCE/Modules/AmiBufferValidationLib/AmiBufferValidationLib.mak 1     11/07/14 12:07p Aaronp $
#
# $Revision: 1 $
#
# $Date: 11/07/14 12:07p $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/AmiBufferValidationLib/AmiBufferValidationLib.mak $
# 
# 1     11/07/14 12:07p Aaronp
# Initial addition of AmiBufferValidationLib
#
#**********************************************************************

#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	AmiBufferValidationLib.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************
all : AmiBufferValidationLib

AmiBufferValidationLib : $(BUILD_DIR)\AmiBufferValidationLib.mak AmiBufferValidationLibBin

$(BUILD_DIR)\AmiBufferValidationLib.mak : $(LIBRARY_DIR)\$(@B).cif $(LIBRARY_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(LIBRARY_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

AmiBufferValidationLibBin : $(AMIDXELIB)
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\AmiBufferValidationLib.mak all\
		TYPE=LIBRARY

$(BUILD_DIR)\AmiBufferValidationLib.lib : AmiBufferValidationLib
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************