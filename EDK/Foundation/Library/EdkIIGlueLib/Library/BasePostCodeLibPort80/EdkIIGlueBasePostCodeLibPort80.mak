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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/EdkIIGlue/EdkIIGlueBasePostCodeLibPort80/EdkIIGlueBasePostCodeLibPort80.mak 1     1/20/12 3:54a Jeffch $
#
# $Revision: 1 $
#
# $Date: 1/20/12 3:54a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/EdkIIGlue/EdkIIGlueBasePostCodeLibPort80/EdkIIGlueBasePostCodeLibPort80.mak $
# 
# 1     1/20/12 3:54a Jeffch
# Create Intel EDK 1117 Patch 7.
# 
# 1     9/27/11 6:16a Wesleychen
# Intel EDK initially releases.
# 
# 1     9/18/09 1:53a Iminglin
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	EdkIIGlueBasePostCodeLibPort80.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************


$(EdkIIGlueBasePostCodeLibPort80_LIB) : EdkIIGlueBasePostCodeLibPort80

EdkIIGlueBasePostCodeLibPort80 : $(BUILD_DIR)\EdkIIGlueBasePostCodeLibPort80.mak EdkIIGlueBasePostCodeLibPort80Bin

$(BUILD_DIR)\EdkIIGlueBasePostCodeLibPort80.mak : $(EdkIIGlueBasePostCodeLibPort80_DIR)\$(@B).cif $(EdkIIGlueBasePostCodeLibPort80_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(EdkIIGlueBasePostCodeLibPort80_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

EdkIIGlueBasePostCodeLibPort80_LIB_LINKS=\
!IF "$(PROCESSOR)"=="IA32" || "$(PROCESSOR)"=="x64"
$(EdkIIGlueBaseIoLibIntrinsic_LIB)
!ELSEIF "$(PROCESSOR)"=="EBC"
$(EdkIIGlueDxeIoLibCpuIo_LIB)
!ENDIF	

EdkIIGlueBasePostCodeLibPort80Bin : $(EdkIIGlueBasePostCodeLibPort80_LIB_LINKS)
!IF "$(x64_BUILD)"=="1"
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		BUILD_DIR=$(BUILD_DIR)\
		/f $(BUILD_DIR)\EdkIIGlueBasePostCodeLibPort80.mak all\
		TYPE=LIBRARY "PARAMETERS=LIBRARY_NAME=$$(EdkIIGlueBasePostCodeLibPort80_LIB)"
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		BUILD_DIR=$(BUILD_DIR)\IA32\
		/f $(BUILD_DIR)\EdkIIGlueBasePostCodeLibPort80.mak all\
		TYPE=PEI_LIBRARY "PARAMETERS=LIBRARY_NAME=$$(EdkIIGlueBasePostCodeLibPort80_LIB)"
!ELSE
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		BUILD_DIR=$(BUILD_DIR)\
		/f $(BUILD_DIR)\EdkIIGlueBasePostCodeLibPort80.mak all\
		TYPE=LIBRARY "PARAMETERS=LIBRARY_NAME=$$(EdkIIGlueBasePostCodeLibPort80_LIB)"
!ENDIF	 
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