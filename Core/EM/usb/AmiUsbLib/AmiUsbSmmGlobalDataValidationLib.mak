#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2016, American Megatrends, Inc.         **
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
#<AMI_FHDR_START>
#
# Name:	AmiUsbSmmGlobalDataValidationLib.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************

all : AmiUsbSmmGlobalDataValidationLib

AmiUsbSmmGlobalDataValidationLib : $(BUILD_DIR)\AmiUsbSmmGlobalDataValidationLib.mak AmiUsbSmmGlobalDataValidationLibBin

$(BUILD_DIR)\AmiUsbSmmGlobalDataValidationLib.mak : $(AMIUSBLIB_DIR)\$(@B).cif $(AMIUSBLIB_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(AMIUSBLIB_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

AmiUsbSmmGlobalDataValidationLibBin : $(AMIDXELIB) $(BUILD_DIR)\AmiBufferValidationLib.lib
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\AmiUsbSmmGlobalDataValidationLib.mak all\
		TYPE=LIBRARY

$(BUILD_DIR)\AmiUsbSmmGlobalDataValidationLib.lib : AmiUsbSmmGlobalDataValidationLib
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2016, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************