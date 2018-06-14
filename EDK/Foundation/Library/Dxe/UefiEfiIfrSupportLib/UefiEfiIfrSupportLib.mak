#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************

#**********************************************************************
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/UefiEfiIfrSupportLib/UefiEfiIfrSupportLib.mak 1     1/20/12 4:13a Jeffch $
#
# $Revision: 1 $
#
# $Date: 1/20/12 4:13a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/UefiEfiIfrSupportLib/UefiEfiIfrSupportLib.mak $
# 
# 1     1/20/12 4:13a Jeffch
# Create Intel EDK 1117 Patch 7.
# 
# 1     9/27/11 6:35a Wesleychen
# Intel EDK initially releases.
# 
# 2     9/02/09 3:55a Iminglin
# EIP24919
# 
#**********************************************************************
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	UefiEfiIfrSupportLib.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************
$(UEFIEFIIFRSUPPORTLIB) : UefiEfiIfrSupportLib

$(BUILD_DIR)\UefiEfiIfrSupportLib.lib : UefiEfiIfrSupportLib

UefiEfiIfrSupportLib : $(BUILD_DIR)\UefiEfiIfrSupportLib.mak UefiEfiIfrSupportLibBin

$(BUILD_DIR)\UefiEfiIfrSupportLib.mak : $(UefiEfiIfrSupportLib_DIR)\$(@B).cif $(UefiEfiIfrSupportLib_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(UefiEfiIfrSupportLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

UefiEfiIfrSupportLibBin : $(EFIGUIDLIB) $(EDKFRAMEWORKPROTOCOLLIB)
	$(MAKE) /$(MAKEFLAGS) $(EDK_DEFAULTS)\
		/f $(BUILD_DIR)\UefiEfiIfrSupportLib.mak all\
		TYPE=LIBRARY \
#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************