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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/EdkIIGlue/EdkIIGlueDxeDebugLibReportStatusCode/EdkIIGlueDxeDebugLibReportStatusCode.mak 1     1/20/12 3:55a Jeffch $
#
# $Revision: 1 $
#
# $Date: 1/20/12 3:55a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/EdkIIGlue/EdkIIGlueDxeDebugLibReportStatusCode/EdkIIGlueDxeDebugLibReportStatusCode.mak $
# 
# 1     1/20/12 3:55a Jeffch
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
# Name:	EdkIIGlueDxeDebugLibReportStatusCode.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************


$(EdkIIGlueDxeDebugLibReportStatusCode_LIB) : EdkIIGlueDxeDebugLibReportStatusCode

EdkIIGlueDxeDebugLibReportStatusCode : $(BUILD_DIR)\EdkIIGlueDxeDebugLibReportStatusCode.mak EdkIIGlueDxeDebugLibReportStatusCodeBin

$(BUILD_DIR)\EdkIIGlueDxeDebugLibReportStatusCode.mak : $(EdkIIGlueDxeDebugLibReportStatusCode_DIR)\$(@B).cif $(EdkIIGlueDxeDebugLibReportStatusCode_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(EdkIIGlueDxeDebugLibReportStatusCode_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)
		
EdkIIGlueDxeDebugLibReportStatusCodeBin : $(EdkIIGlueBaseLib_LIB) $(EdkIIGlueBaseMemoryLib_LIB) $(EDKFRAMEWORKGUIDLIB) $(EFIPROTOCOLLIB)
!IF "$(x64_BUILD)"=="1"
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		BUILD_DIR=$(BUILD_DIR)\
		/f $(BUILD_DIR)\EdkIIGlueDxeDebugLibReportStatusCode.mak all\
		TYPE=LIBRARY "PARAMETERS=LIBRARY_NAME=$$(EdkIIGlueDxeDebugLibReportStatusCode_LIB)"
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		BUILD_DIR=$(BUILD_DIR)\IA32\
		/f $(BUILD_DIR)\EdkIIGlueDxeDebugLibReportStatusCode.mak all\
		TYPE=PEI_LIBRARY "PARAMETERS=LIBRARY_NAME=$$(EdkIIGlueDxeDebugLibReportStatusCode_LIB)"
!ELSE
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		BUILD_DIR=$(BUILD_DIR)\
		/f $(BUILD_DIR)\EdkIIGlueDxeDebugLibReportStatusCode.mak all\
		TYPE=LIBRARY "PARAMETERS=LIBRARY_NAME=$$(EdkIIGlueDxeDebugLibReportStatusCode_LIB)"
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
