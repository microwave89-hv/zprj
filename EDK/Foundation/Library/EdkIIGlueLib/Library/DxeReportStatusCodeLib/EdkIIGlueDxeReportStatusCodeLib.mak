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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/EdkIIGlue/EdkIIGlueDxeReportStatusCodeLib/EdkIIGlueDxeReportStatusCodeLib.mak 1     1/20/12 3:55a Jeffch $
#
# $Revision: 1 $
#
# $Date: 1/20/12 3:55a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/EdkIIGlue/EdkIIGlueDxeReportStatusCodeLib/EdkIIGlueDxeReportStatusCodeLib.mak $
# 
# 1     1/20/12 3:55a Jeffch
# Create Intel EDK 1117 Patch 7.
# 
# 1     9/27/11 6:17a Wesleychen
# Intel EDK initially releases.
# 
# 1     9/18/09 1:55a Iminglin
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	EdkIIGlueDxeReportStatusCodeLib.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************


$(EdkIIGlueDxeReportStatusCodeLib_LIB) : EdkIIGlueDxeReportStatusCodeLib

EdkIIGlueDxeReportStatusCodeLib : $(BUILD_DIR)\EdkIIGlueDxeReportStatusCodeLib.mak EdkIIGlueDxeReportStatusCodeLibBin

$(BUILD_DIR)\EdkIIGlueDxeReportStatusCodeLib.mak : $(EdkIIGlueDxeReportStatusCodeLib_DIR)\$(@B).cif $(EdkIIGlueDxeReportStatusCodeLib_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(EdkIIGlueDxeReportStatusCodeLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

EdkIIGlueDxeReportStatusCodeLib_LIB_LINKS=$(EdkIIGlueBaseLib_LIB)\
$(EdkIIGlueBaseMemoryLib_LIB)\
$(EdkIIGlueUefiBootServicesTableLib_LIB)\
$(EdkIIGlueUefiRuntimeServicesTableLib_LIB)\
$(EFIPROTOCOLLIB)\
$(EDKGUIDLIB)\
$(ARCHPROTOCOLLIB)\
!IF "$(PROCESSOR)"=="IA32" || "$(PROCESSOR)"=="x64"
$(EdkIIGlueBaseIoLibIntrinsic_LIB)
!ENDIF	

EdkIIGlueDxeReportStatusCodeLibBin : $(EdkIIGlueDxeReportStatusCodeLib_LIB_LINKS)
!IF "$(x64_BUILD)"=="1"
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		BUILD_DIR=$(BUILD_DIR)\
		/f $(BUILD_DIR)\EdkIIGlueDxeReportStatusCodeLib.mak all\
		TYPE=LIBRARY "PARAMETERS=LIBRARY_NAME=$$(EdkIIGlueDxeReportStatusCodeLib_LIB)"
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		BUILD_DIR=$(BUILD_DIR)\IA32\
		/f $(BUILD_DIR)\EdkIIGlueDxeReportStatusCodeLib.mak all\
		TYPE=PEI_LIBRARY "PARAMETERS=LIBRARY_NAME=$$(EdkIIGlueDxeReportStatusCodeLib_LIB)"
!ELSE
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		BUILD_DIR=$(BUILD_DIR)\
		/f $(BUILD_DIR)\EdkIIGlueDxeReportStatusCodeLib.mak all\
		TYPE=LIBRARY "PARAMETERS=LIBRARY_NAME=$$(EdkIIGlueDxeReportStatusCodeLib_LIB)"
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
