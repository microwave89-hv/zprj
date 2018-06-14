#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/EdkIIGlue/EdkIIGlueBaseTimerLibTsc/EdkIIGlueBaseTimerLibTsc.mak 1     1/20/12 3:59a Jeffch $
#
# $Revision: 1 $
#
# $Date: 1/20/12 3:59a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/EdkIIGlue/EdkIIGlueBaseTimerLibTsc/EdkIIGlueBaseTimerLibTsc.mak $
# 
# 1     1/20/12 3:59a Jeffch
# 
# 1     9/27/11 6:21a Wesleychen
# Intel EDK initially releases.
# 
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	EdkIIGlueBaseTimerLibTsc.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************


$(EdkIIGlueBaseTimerLibTsc_LIB) : EdkIIGlueBaseTimerLibTsc

EdkIIGlueBaseTimerLibTsc : $(BUILD_DIR)\EdkIIGlueBaseTimerLibTsc.mak EdkIIGlueBaseTimerLibTscBin

$(BUILD_DIR)\EdkIIGlueBaseTimerLibTsc.mak : $(EdkIIGlueBaseTimerLibTsc_DIR)\$(@B).cif $(EdkIIGlueBaseTimerLibTsc_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(EdkIIGlueBaseTimerLibTsc_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)
	
EdkIIGlueBaseTimerLibTscBin : $(EFIPROTOCOLLIB) $(EDKGUIDLIB) $(ARCHPROTOCOLLIB)
!IF "$(x64_BUILD)"=="1"
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		BUILD_DIR=$(BUILD_DIR)\
		/f $(BUILD_DIR)\EdkIIGlueBaseTimerLibTsc.mak all\
		TYPE=LIBRARY "PARAMETERS=LIBRARY_NAME=$$(EdkIIGlueBaseTimerLibTsc_LIB)"
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		BUILD_DIR=$(BUILD_DIR)\IA32\
		/f $(BUILD_DIR)\EdkIIGlueBaseTimerLibTsc.mak all\
		TYPE=PEI_LIBRARY "PARAMETERS=LIBRARY_NAME=$$(EdkIIGlueBaseTimerLibTsc_LIB)"
!ELSE
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		BUILD_DIR=$(BUILD_DIR)\
		/f $(BUILD_DIR)\EdkIIGlueBaseTimerLibTsc.mak all\
		TYPE=LIBRARY "PARAMETERS=LIBRARY_NAME=$$(EdkIIGlueBaseTimerLibTsc_LIB)"
!ENDIF
#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************