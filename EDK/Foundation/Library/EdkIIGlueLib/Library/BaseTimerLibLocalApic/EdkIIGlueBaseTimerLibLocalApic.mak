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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/EdkIIGlue/EdkIIGlueBaseTimerLibLocalApic/EdkIIGlueBaseTimerLibLocalApic.mak 1     1/20/12 3:54a Jeffch $
#
# $Revision: 1 $
#
# $Date: 1/20/12 3:54a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/EdkIIGlue/EdkIIGlueBaseTimerLibLocalApic/EdkIIGlueBaseTimerLibLocalApic.mak $
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
# Name:	EdkIIGlueBaseTimerLibLocalApic.mak
#
# Description:	
#
#<AMI_FHDR_END>
#***************************************************************s*******


$(EdkIIGlueBaseTimerLibLocalApic_LIB) : EdkIIGlueBaseTimerLibLocalApic

$(EdkIIGlueBaseTimerLibLocalApic_LIB) : EdkIIGlueBaseTimerLibLocalApic

EdkIIGlueBaseTimerLibLocalApic : $(BUILD_DIR)\EdkIIGlueBaseTimerLibLocalApic.mak EdkIIGlueBaseTimerLibLocalApicBin

$(BUILD_DIR)\EdkIIGlueBaseTimerLibLocalApic.mak : $(EdkIIGlueBaseTimerLibLocalApic_DIR)\$(@B).cif $(EdkIIGlueBaseTimerLibLocalApic_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(EdkIIGlueBaseTimerLibLocalApic_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

EdkIIGlueBaseTimerLibLocalApic_LIB_LINKS=$(EdkIIGlueBaseLib_LIB)\
!IF "$(PROCESSOR)"=="IA32" || "$(PROCESSOR)"=="x64"
$(EdkIIGlueBaseIoLibIntrinsic_LIB)
!ENDIF	

EdkIIGlueBaseTimerLibLocalApicBin : $(EdkIIGlueBaseTimerLibLocalApic_LIB_LINKS)
!IF "$(x64_BUILD)"=="1"
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		BUILD_DIR=$(BUILD_DIR)\
		/f $(BUILD_DIR)\EdkIIGlueBaseTimerLibLocalApic.mak all\
		TYPE=LIBRARY "PARAMETERS=LIBRARY_NAME=$$(EdkIIGlueBaseTimerLibLocalApic_LIB)"
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		BUILD_DIR=$(BUILD_DIR)\IA32\
		/f $(BUILD_DIR)\EdkIIGlueBaseTimerLibLocalApic.mak all\
		TYPE=PEI_LIBRARY "PARAMETERS=LIBRARY_NAME=$$(EdkIIGlueBaseTimerLibLocalApic_LIB)"
!ELSE
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		BUILD_DIR=$(BUILD_DIR)\
		/f $(BUILD_DIR)\EdkIIGlueBaseTimerLibLocalApic.mak all\
		TYPE=LIBRARY "PARAMETERS=LIBRARY_NAME=$$(EdkIIGlueBaseTimerLibLocalApic_LIB)"
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
