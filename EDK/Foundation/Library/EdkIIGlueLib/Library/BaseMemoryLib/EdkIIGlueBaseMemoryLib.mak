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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/EdkIIGlue/EdkIIGlueBaseMemoryLib/EdkIIGlueBaseMemoryLib.mak 1     1/20/12 3:51a Jeffch $
#
# $Revision: 1 $
#
# $Date: 1/20/12 3:51a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/EdkIIGlue/EdkIIGlueBaseMemoryLib/EdkIIGlueBaseMemoryLib.mak $
# 
# 1     1/20/12 3:51a Jeffch
# Create Intel EDK 1117 Patch 7.
# 
# 1     1/20/12 3:30a Jeffch
# Create Intel EDK 1117 Patch 7.
# 
# 1     9/27/11 6:14a Wesleychen
# Intel EDK initially releases.
# 
# 1     9/18/09 1:51a Iminglin
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	EdkIIGlueBaseMemoryLib.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************

EdkIIGlueBaseMemoryLib_OBJECTS=\
$$(BUILD_DIR)\$(EdkIIGlueBaseMemoryLib_DIR)\ScanMem32Wrapper.obj \
$$(BUILD_DIR)\$(EdkIIGlueBaseMemoryLib_DIR)\ScanMem64Wrapper.obj \
$$(BUILD_DIR)\$(EdkIIGlueBaseMemoryLib_DIR)\SetMem16Wrapper.obj \
$$(BUILD_DIR)\$(EdkIIGlueBaseMemoryLib_DIR)\SetMem32Wrapper.obj \
$$(BUILD_DIR)\$(EdkIIGlueBaseMemoryLib_DIR)\SetMem64Wrapper.obj \
$$(BUILD_DIR)\$(EdkIIGlueBaseMemoryLib_DIR)\SetMemWrapper.obj \
$$(BUILD_DIR)\$(EdkIIGlueBaseMemoryLib_DIR)\ZeroMemWrapper.obj \
$$(BUILD_DIR)\$(EdkIIGlueBaseMemoryLib_DIR)\CompareMemWrapper.obj \
$$(BUILD_DIR)\$(EdkIIGlueBaseMemoryLib_DIR)\CopyMemWrapper.obj \
$$(BUILD_DIR)\$(EdkIIGlueBaseMemoryLib_DIR)\MemLibGuid.obj \
$$(BUILD_DIR)\$(EdkIIGlueBaseMemoryLib_DIR)\ScanMem8Wrapper.obj \
$$(BUILD_DIR)\$(EdkIIGlueBaseMemoryLib_DIR)\ScanMem16Wrapper.obj

EdkIIGlueBaseMemoryLib_IA32_OBJECTS=\
$$(BUILD_DIR)\$(EdkIIGlueBaseMemoryLib_DIR)\Ia32\ScanMem8.obj \
$$(BUILD_DIR)\$(EdkIIGlueBaseMemoryLib_DIR)\Ia32\ScanMem16.obj \
$$(BUILD_DIR)\$(EdkIIGlueBaseMemoryLib_DIR)\Ia32\ScanMem32.obj \
$$(BUILD_DIR)\$(EdkIIGlueBaseMemoryLib_DIR)\Ia32\ScanMem64.obj \
$$(BUILD_DIR)\$(EdkIIGlueBaseMemoryLib_DIR)\Ia32\SetMem.obj \
$$(BUILD_DIR)\$(EdkIIGlueBaseMemoryLib_DIR)\Ia32\SetMem16.obj \
$$(BUILD_DIR)\$(EdkIIGlueBaseMemoryLib_DIR)\Ia32\SetMem32.obj \
$$(BUILD_DIR)\$(EdkIIGlueBaseMemoryLib_DIR)\Ia32\SetMem64.obj \
$$(BUILD_DIR)\$(EdkIIGlueBaseMemoryLib_DIR)\Ia32\ZeroMem.obj \
$$(BUILD_DIR)\$(EdkIIGlueBaseMemoryLib_DIR)\Ia32\CompareMem.obj \
$$(BUILD_DIR)\$(EdkIIGlueBaseMemoryLib_DIR)\Ia32\CopyMem.obj

!IF "$(PROCESSOR)"=="IA32"
EdkIIGlueBaseMemoryLib_OBJECTS =$(EdkIIGlueBaseMemoryLib_OBJECTS) $(EdkIIGlueBaseMemoryLib_IA32_OBJECTS)
!ELSEIF "$(PROCESSOR)"=="x64"
EdkIIGlueBaseMemoryLib_PEI_OBJECTS =$(EdkIIGlueBaseMemoryLib_OBJECTS) $(EdkIIGlueBaseMemoryLib_IA32_OBJECTS)
EdkIIGlueBaseMemoryLib_DXE_OBJECTS =$(EdkIIGlueBaseMemoryLib_OBJECTS)\
$$(BUILD_DIR)\$(EdkIIGlueBaseMemoryLib_DIR)\X64\CompareMem.obj\
$$(BUILD_DIR)\$(EdkIIGlueBaseMemoryLib_DIR)\X64\CopyMem.obj\
$$(BUILD_DIR)\$(EdkIIGlueBaseMemoryLib_DIR)\X64\ScanMem16.obj\
$$(BUILD_DIR)\$(EdkIIGlueBaseMemoryLib_DIR)\X64\ScanMem32.obj\
$$(BUILD_DIR)\$(EdkIIGlueBaseMemoryLib_DIR)\X64\ScanMem64.obj\
$$(BUILD_DIR)\$(EdkIIGlueBaseMemoryLib_DIR)\X64\ScanMem8.obj\
$$(BUILD_DIR)\$(EdkIIGlueBaseMemoryLib_DIR)\X64\SetMem.obj\
$$(BUILD_DIR)\$(EdkIIGlueBaseMemoryLib_DIR)\X64\SetMem16.obj\
$$(BUILD_DIR)\$(EdkIIGlueBaseMemoryLib_DIR)\X64\SetMem32.obj\
$$(BUILD_DIR)\$(EdkIIGlueBaseMemoryLib_DIR)\X64\SetMem64.obj\
$$(BUILD_DIR)\$(EdkIIGlueBaseMemoryLib_DIR)\X64\ZeroMem.obj
!ENDIF

!IF "$(PROCESSOR)"=="IA32"
EdkIIGlueBaseMemoryLib_PORCESSOR_CIF=$(EdkIIGlueBaseMemoryLib_DIR)\Ia32\EdkIIGlueBaseMemoryLibIa32.cif
!ELSEIF "$(PROCESSOR)"=="x64"
EdkIIGlueBaseMemoryLib_PORCESSOR_PEI_CIF=$(EdkIIGlueBaseMemoryLib_DIR)\Ia32\EdkIIGlueBaseMemoryLibIa32.cif
EdkIIGlueBaseMemoryLib_PORCESSOR_DXE_CIF=$(EdkIIGlueBaseMemoryLib_DIR)\X64\EdkIIGlueBaseMemoryLibX64.cif
!ENDIF

$(EdkIIGlueBaseMemoryLib_LIB) : EdkIIGlueBaseMemoryLib

EdkIIGlueBaseMemoryLib : $(BUILD_DIR)\EdkIIGlueBaseMemoryLib.mak EdkIIGlueBaseMemoryLibBin

!IF "$(PROCESSOR)"=="x64"
$(BUILD_DIR)\EdkIIGlueBaseMemoryLib.mak : $(EdkIIGlueBaseMemoryLib_DIR)\$(@B).cif $(EdkIIGlueBaseMemoryLib_DIR)\$(@B).mak $(BUILD_RULES) $(EdkIIGlueBaseMemoryLib_PORCESSOR_PEI_CIF) $(EdkIIGlueBaseMemoryLib_PORCESSOR_DXE_CIF)
	$(CIF2MAK) $(EdkIIGlueBaseMemoryLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS) $(EdkIIGlueBaseMemoryLib_PORCESSOR_PEI_CIF) $(EdkIIGlueBaseMemoryLib_PORCESSOR_DXE_CIF)
!ELSE
$(BUILD_DIR)\EdkIIGlueBaseMemoryLib.mak : $(EdkIIGlueBaseMemoryLib_DIR)\$(@B).cif $(EdkIIGlueBaseMemoryLib_DIR)\$(@B).mak $(BUILD_RULES) $(EdkIIGlueBaseMemoryLib_PORCESSOR_CIF)
	$(CIF2MAK) $(EdkIIGlueBaseMemoryLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS) $(EdkIIGlueBaseMemoryLib_PORCESSOR_CIF)
!ENDIF

EdkIIGlueBaseMemoryLibBin : $(EdkIIGlueBaseLib_LIB)
!IF "$(x64_BUILD)"=="1"
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		BUILD_DIR=$(BUILD_DIR)\
		/f $(BUILD_DIR)\EdkIIGlueBaseMemoryLib.mak all\
		TYPE=LIBRARY "PARAMETERS=LIBRARY_NAME=$$(EdkIIGlueBaseMemoryLib_LIB)"\
		"OBJECTS=$(EdkIIGlueBaseMemoryLib_DXE_OBJECTS)"
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		BUILD_DIR=$(BUILD_DIR)\IA32\
		/f $(BUILD_DIR)\EdkIIGlueBaseMemoryLib.mak all\
		TYPE=PEI_LIBRARY "PARAMETERS=LIBRARY_NAME=$$(EdkIIGlueBaseMemoryLib_LIB)"\
		"OBJECTS=$(EdkIIGlueBaseMemoryLib_PEI_OBJECTS)"
!ELSE
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		BUILD_DIR=$(BUILD_DIR)\
		/f $(BUILD_DIR)\EdkIIGlueBaseMemoryLib.mak all\
		TYPE=LIBRARY "PARAMETERS=LIBRARY_NAME=$$(EdkIIGlueBaseMemoryLib_LIB)"\
		"OBJECTS=$(EdkIIGlueBaseMemoryLib_OBJECTS)"
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
