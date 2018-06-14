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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/EdkIIGlue/EdkIIGlueBaseLib/EdkIIGlueBaseLib.mak 1     1/20/12 3:48a Jeffch $
#
# $Revision: 1 $
#
# $Date: 1/20/12 3:48a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/EdkIIGlue/EdkIIGlueBaseLib/EdkIIGlueBaseLib.mak $
# 
# 1     1/20/12 3:48a Jeffch
# Create Intel EDK 1117 Patch 7.
# 
# 1     1/20/12 3:28a Jeffch
# Create Intel EDK 1117 Patch 7.
# 
# 1     9/27/11 6:10a Wesleychen
# Intel EDK initially releases.
# 
# 1     9/18/09 1:50a Iminglin
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	EdkIIGlueBaseLib.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************


!IF "$(PROCESSOR)"=="IA32"
EdkIIGlueBaseLib_PORCESSOR_CIF=$(EdkIIGlueBaseLib_DIR)\EdkIIGlueBaseLibIa32.cif
!ELSEIF "$(PROCESSOR)"=="x64"
EdkIIGlueBaseLib_PORCESSOR_PEI_CIF=$(EdkIIGlueBaseLib_DIR)\EdkIIGlueBaseLibIa32.cif
EdkIIGlueBaseLib_PORCESSOR_DXE_CIF=$(EdkIIGlueBaseLib_DIR)\EdkIIGlueBaseLibX64.cif
!ENDIF

$(EdkIIGlueBaseLib_LIB) : EdkIIGlueBaseLib

!IF "$(x64_BUILD)"=="1"
EdkIIGlueBaseLib : $(BUILD_DIR)\EdkIIGlueBaseLib.mak $(BUILD_DIR)\EdkIIGlueBaseLibPei.mak EdkIIGlueBaseLibBin

$(BUILD_DIR)\EdkIIGlueBaseLib.mak : $(EdkIIGlueBaseLib_DIR)\EdkIIGlueBaseLib.cif $(EdkIIGlueBaseLib_DIR)\EdkIIGlueBaseLib.mak $(BUILD_RULES) $(EdkIIGlueBaseLib_PORCESSOR_DXE_CIF)
	$(CIF2MAK) $(EdkIIGlueBaseLib_DIR)\EdkIIGlueBaseLib.cif $(CIF2MAK_DEFAULTS) $(EdkIIGlueBaseLib_PORCESSOR_DXE_CIF)

$(BUILD_DIR)\EdkIIGlueBaseLibPei.mak : $(EdkIIGlueBaseLib_DIR)\EdkIIGlueBaseLib.cif $(EdkIIGlueBaseLib_DIR)\EdkIIGlueBaseLib.mak $(BUILD_RULES) $(EdkIIGlueBaseLib_PORCESSOR_PEI_CIF)
	$(CIF2MAK) $(EdkIIGlueBaseLib_DIR)\EdkIIGlueBaseLib.cif $(CIF2MAK_DEFAULTS) $(EdkIIGlueBaseLib_PORCESSOR_PEI_CIF)
!ELSE
EdkIIGlueBaseLib : $(BUILD_DIR)\EdkIIGlueBaseLib.mak EdkIIGlueBaseLibBin

$(BUILD_DIR)\EdkIIGlueBaseLib.mak : $(EdkIIGlueBaseLib_DIR)\EdkIIGlueBaseLib.cif $(EdkIIGlueBaseLib_DIR)\EdkIIGlueBaseLib.mak $(BUILD_RULES) $(EdkIIGlueBaseLib_PORCESSOR_CIF)
	$(CIF2MAK) $(EdkIIGlueBaseLib_DIR)\EdkIIGlueBaseLib.cif $(CIF2MAK_DEFAULTS) $(EdkIIGlueBaseLib_PORCESSOR_CIF)
!ENDIF

EdkIIGlueBaseLibBin :
!IF "$(x64_BUILD)"=="1"
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		BUILD_DIR=$(BUILD_DIR)\
		/f $(BUILD_DIR)\EdkIIGlueBaseLib.mak all\
		"MY_INCLUDES=/I$(EdkIIGlueBaseLib_DIR)"\
		"MY_DEFINES=/D"CPU_STACK_ALIGNMENT=2""\
		TYPE=LIBRARY "PARAMETERS=LIBRARY_NAME=$$(EdkIIGlueBaseLib_LIB)"
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		BUILD_DIR=$(BUILD_DIR)\IA32\
		/f $(BUILD_DIR)\EdkIIGlueBaseLibPei.mak all\
		"MY_INCLUDES=/I$(EdkIIGlueBaseLib_DIR)"\
		"MY_DEFINES=/D"CPU_STACK_ALIGNMENT=2""\
		TYPE=PEI_LIBRARY "PARAMETERS=LIBRARY_NAME=$$(EdkIIGlueBaseLib_LIB)"
!ELSE
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		BUILD_DIR=$(BUILD_DIR)\
		/f $(BUILD_DIR)\EdkIIGlueBaseLib.mak all\
		"MY_INCLUDES=/I$(EdkIIGlueBaseLib_DIR)"\
		"MY_DEFINES=/D"CPU_STACK_ALIGNMENT=2""\
		TYPE=LIBRARY "PARAMETERS=LIBRARY_NAME=$$(EdkIIGlueBaseLib_LIB)"
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
