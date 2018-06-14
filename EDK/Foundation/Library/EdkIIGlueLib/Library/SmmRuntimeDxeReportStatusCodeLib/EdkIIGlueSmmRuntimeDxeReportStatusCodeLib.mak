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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/EdkIIGlue/EdkIIGlueSmmRuntimeDxeReportStatusCodeLib/EdkIIGlueSmmRuntimeDxeReportStatusCodeLib.mak 1     1/20/12 3:58a Jeffch $
#
# $Revision: 1 $
#
# $Date: 1/20/12 3:58a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/EdkIIGlue/EdkIIGlueSmmRuntimeDxeReportStatusCodeLib/EdkIIGlueSmmRuntimeDxeReportStatusCodeLib.mak $
# 
# 1     1/20/12 3:58a Jeffch
# 
# 1     9/27/11 6:20a Wesleychen
# Intel EDK initially releases.
# 
# 2     1/23/11 10:01p Iminglin
# EIP52651
# EdkIIGlueSMMRuntimeDxeReportStatusCodeLib includes
# $(EdkIIGlueUefiBootServicesTableLib_LIB) which will be a problem if
# there are any DEBUG messages in SMM code after booting to OS. Instead
# of this library EdkIIGlueUefiRuntimeServicesTableLib_LIB is used.
# 
# 1     9/18/09 1:58a Iminglin
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	EdkIIGlueSmmRuntimeDxeReportStatusCodeLib.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************
#all : EdkIIGlueSmmRuntimeDxeReportStatusCodeLib

$(EdkIIGlueSmmRuntimeDxeReportStatusCodeLib_LIB) : EdkIIGlueSmmRuntimeDxeReportStatusCodeLib

EdkIIGlueSmmRuntimeDxeReportStatusCodeLib : $(BUILD_DIR)\EdkIIGlueSmmRuntimeDxeReportStatusCodeLib.mak EdkIIGlueSmmRuntimeDxeReportStatusCodeLibBin

$(BUILD_DIR)\EdkIIGlueSmmRuntimeDxeReportStatusCodeLib.mak : $(EdkIIGlueSmmRuntimeDxeReportStatusCodeLib_DIR)\$(@B).cif $(EdkIIGlueSmmRuntimeDxeReportStatusCodeLib_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(EdkIIGlueSmmRuntimeDxeReportStatusCodeLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)
	

#EdkIIGlueSmmRuntimeDxeReportStatusCodeLibBin : $(EdkIIGlueBaseLib_LIB) $(EdkIIGlueBaseMemoryLib_LIB) $(EdkIIGlueUefiBootServicesTableLib_LIB) $(EdkIIGlueUefiRuntimeServicesTableLib_LIB) $(EFIPROTOCOLLIB) $(EDKGUIDLIB) $(ARCHPROTOCOLLIB)
EdkIIGlueSmmRuntimeDxeReportStatusCodeLibBin : $(EdkIIGlueUefiRuntimeServicesTableLib_LIB) $(EDKGUIDLIB) $(ARCHPROTOCOLLIB) $(EdkIIGlueBaseIoLibIntrinsic_LIB) $(EFIGUIDLIB)
!IF "$(x64_BUILD)"=="1"
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		BUILD_DIR=$(BUILD_DIR)\
		/f $(BUILD_DIR)\EdkIIGlueSmmRuntimeDxeReportStatusCodeLib.mak all\
		TYPE=LIBRARY "PARAMETERS=LIBRARY_NAME=$$(EdkIIGlueSmmRuntimeDxeReportStatusCodeLib_LIB)"
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		BUILD_DIR=$(BUILD_DIR)\IA32\
		/f $(BUILD_DIR)\EdkIIGlueSmmRuntimeDxeReportStatusCodeLib.mak all\
		TYPE=PEI_LIBRARY "PARAMETERS=LIBRARY_NAME=$$(EdkIIGlueSmmRuntimeDxeReportStatusCodeLib_LIB)"
!ELSE
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		BUILD_DIR=$(BUILD_DIR)\
		/f $(BUILD_DIR)\EdkIIGlueSmmRuntimeDxeReportStatusCodeLib.mak all\
		TYPE=LIBRARY "PARAMETERS=LIBRARY_NAME=$$(EdkIIGlueSmmRuntimeDxeReportStatusCodeLib_LIB)"
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