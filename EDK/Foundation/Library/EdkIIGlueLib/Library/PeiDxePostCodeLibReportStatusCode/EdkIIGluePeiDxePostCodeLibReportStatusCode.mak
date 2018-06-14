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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/EdkIIGlue/EdkIIGluePeiDxePostCodeLibReportStatusCode/EdkIIGluePeiDxePostCodeLibReportStatusCode.mak 1     1/20/12 3:56a Jeffch $
#
# $Revision: 1 $
#
# $Date: 1/20/12 3:56a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/EdkIIGlue/EdkIIGluePeiDxePostCodeLibReportStatusCode/EdkIIGluePeiDxePostCodeLibReportStatusCode.mak $
# 
# 1     1/20/12 3:56a Jeffch
# Create Intel EDK 1117 Patch 7.
# 
# 1     9/27/11 6:18a Wesleychen
# Intel EDK initially releases.
# 
# 1     9/18/09 1:56a Iminglin
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	EdkIIGluePeiDxePostCodeLibReportStatusCode.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************


$(EdkIIGluePeiDxePostCodeLibReportStatusCode_LIB) : EdkIIGluePeiDxePostCodeLibReportStatusCode

EdkIIGluePeiDxePostCodeLibReportStatusCode : $(BUILD_DIR)\EdkIIGluePeiDxePostCodeLibReportStatusCode.mak EdkIIGluePeiDxePostCodeLibReportStatusCodeBin

$(BUILD_DIR)\EdkIIGluePeiDxePostCodeLibReportStatusCode.mak : $(EdkIIGluePeiDxePostCodeLibReportStatusCode_DIR)\$(@B).cif $(EdkIIGluePeiDxePostCodeLibReportStatusCode_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(EdkIIGluePeiDxePostCodeLibReportStatusCode_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)
		
EdkIIGluePeiDxePostCodeLibReportStatusCodeBin : 
!IF "$(x64_BUILD)"=="1"
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		BUILD_DIR=$(BUILD_DIR)\
		/f $(BUILD_DIR)\EdkIIGluePeiDxePostCodeLibReportStatusCode.mak all\
		TYPE=LIBRARY "PARAMETERS=LIBRARY_NAME=$$(EdkIIGluePeiDxePostCodeLibReportStatusCode_LIB)"
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		BUILD_DIR=$(BUILD_DIR)\IA32\
		/f $(BUILD_DIR)\EdkIIGluePeiDxePostCodeLibReportStatusCode.mak all\
		TYPE=PEI_LIBRARY "PARAMETERS=LIBRARY_NAME=$$(EdkIIGluePeiDxePostCodeLibReportStatusCode_LIB)"
!ELSE
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		BUILD_DIR=$(BUILD_DIR)\
		/f $(BUILD_DIR)\EdkIIGluePeiDxePostCodeLibReportStatusCode.mak all\
		TYPE=LIBRARY "PARAMETERS=LIBRARY_NAME=$$(EdkIIGluePeiDxePostCodeLibReportStatusCode_LIB)"
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
