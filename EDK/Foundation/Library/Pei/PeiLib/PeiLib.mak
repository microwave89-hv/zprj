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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/PeiLib/PeiLib.mak 2     2/24/12 5:44a Jeffch $
#
# $Revision: 2 $
#
# $Date: 2/24/12 5:44a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/PeiLib/PeiLib.mak $
# 
# 2     2/24/12 5:44a Jeffch
# 
# 1     1/20/12 4:11a Jeffch
# Create Intel EDK 1117 Patch 7.
# 
# 1     9/27/11 6:32a Wesleychen
# Intel EDK initially releases.
# 
# 3     9/20/10 10:03p Iminglin
# Libary for IA32 and X64
# 
# 2     9/02/09 3:58a Iminglin
# EIP24919
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	PeiLib.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************
$(PEILIB) : PeiLib

PEI_LIB_OBJECTS=\
$$(BUILD_DIR)\$(PeiLib_DIR)\Debug.obj\
$$(BUILD_DIR)\$(PeiLib_DIR)\Decompress.obj\
$$(BUILD_DIR)\$(PeiLib_DIR)\FindFv.obj\
$$(BUILD_DIR)\$(PeiLib_DIR)\PeCoffLoader.obj\
$$(BUILD_DIR)\$(PeiLib_DIR)\PeiLib.obj\
$$(BUILD_DIR)\$(PeiLib_DIR)\Perf.obj\
$$(BUILD_DIR)\$(PeiLib_DIR)\Hob\Hob.obj\
$$(BUILD_DIR)\$(PeiLib_DIR)\Print\Print.obj

PEI_LIB_IA32_OBJECTS=\
$$(BUILD_DIR)\$(PeiLib_DIR)\IA32\PeCoffLoaderEx.obj\
$$(BUILD_DIR)\$(PeiLib_DIR)\IA32\PerformancePrimitives.obj\
$$(BUILD_DIR)\$(PeiLib_DIR)\IA32\Processor.obj\
$$(BUILD_DIR)\$(PeiLib_DIR)\IA32\ProcessorAsms.obj

PEI_LIB_x64_OBJECTS=\
$$(BUILD_DIR)\$(PeiLib_DIR)\x64\PeCoffLoaderEx.obj\
$$(BUILD_DIR)\$(PeiLib_DIR)\x64\PerformancePrimitives.obj\
$$(BUILD_DIR)\$(PeiLib_DIR)\x64\Processor.obj\
$$(BUILD_DIR)\$(PeiLib_DIR)\x64\ProcessorAsms.obj

PEI_LIB_IPF_OBJECTS=\
$$(BUILD_DIR)\$(PeiLib_DIR)\Ipf\PeCoffLoaderEx.obj\
$$(BUILD_DIR)\$(PeiLib_DIR)\Ipf\processor.obj\
$$(BUILD_DIR)\$(PeiLib_DIR)\Ipf\PerformancePrimitives.obj\
$$(BUILD_DIR)\$(PeiLib_DIR)\Ipf\pioflush.obj\
$$(BUILD_DIR)\$(PeiLib_DIR)\Ipf\setjmp.obj\
$$(BUILD_DIR)\$(PeiLib_DIR)\Ipf\SwitchStack.obj

!IF "$(PROCESSOR)"=="IA32"
PEI_LIB_OBJECTS =$(PEI_LIB_OBJECTS) $(PEI_LIB_IA32_OBJECTS)
!ELSEIF "$(PROCESSOR)"=="x64"
PEI_LIB_PEI_OBJECTS =$(PEI_LIB_OBJECTS) $(PEI_LIB_IA32_OBJECTS)
PEI_LIB_DXE_OBJECTS =$(PEI_LIB_OBJECTS) $(PEI_LIB_x64_OBJECTS)
!ELSEIF "$(PROCESSOR)"=="IPF"
PEI_LIB_OBJECTS =$(PEI_LIB_OBJECTS) $(PEI_LIB_IPF_OBJECTS)
!ENDIF

!IF "$(PROCESSOR)"=="x64"
PEI_LIB_PORCESSOR_PEI_CIF=$(PeiLib_DIR)\$(@B)IA32.cif
PEI_LIB_PORCESSOR_DXE_CIF=$(PeiLib_DIR)\$(@B)$(PROCESSOR).cif
!ELSE
PEI_LIB_PORCESSOR_CIF=$(PeiLib_DIR)\$(@B)$(PROCESSOR).cif
!ENDIF

$(BUILD_DIR)\PeiLib.lib : PeiLib

PeiLib : $(BUILD_DIR)\PeiLib.mak PeiLibBin

!IF "$(PROCESSOR)"=="x64"
$(BUILD_DIR)\PeiLib.mak : $(PeiLib_DIR)\$(@B).cif $(PeiLib_DIR)\$(@B).mak $(BUILD_RULES) $(PEI_LIB_PORCESSOR_PEI_CIF) $(PEI_LIB_PORCESSOR_DXE_CIF)
    $(CIF2MAK) $(PeiLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS) $(PEI_LIB_PORCESSOR_PEI_CIF) $(PEI_LIB_PORCESSOR_DXE_CIF)
!ELSE
$(BUILD_DIR)\PeiLib.mak : $(PeiLib_DIR)\$(@B).cif $(PeiLib_DIR)\$(@B).mak $(BUILD_RULES) $(PEI_LIB_PORCESSOR_CIF)
	$(CIF2MAK) $(PeiLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS) $(PEI_LIB_PORCESSOR_CIF)
!ENDIF

!IF "$(PROCESSOR)"!="IPF"
PeiLibBin : $(CPUIA32LIB)
!ENDIF

PeiLibBin : $(EDKGUIDLIB) $(EFICOMMONLIB) $(EDKFRAMEWORKPPILIB)
!IF "$(PROCESSOR)"=="x64"
    $(MAKE) /$(MAKEFLAGS) $(EDK_DEFAULTS)\
        /f $(BUILD_DIR)\PeiLib.mak all\
		"MY_INCLUDES=$(EDK_INCLUDES)"\
        TYPE=LIBRARY  "OBJECTS=$(PEI_LIB_DXE_OBJECTS)"
    $(MAKE) /$(MAKEFLAGS) $(EDK_DEFAULTS) BUILD_DIR=$(BUILD_DIR)\IA32\
        /f $(BUILD_DIR)\PeiLib.mak all\
		"MY_INCLUDES=$(EDK_INCLUDES)"\
        TYPE=PEI_LIBRARY "OBJECTS=$(PEI_LIB_PEI_OBJECTS)"
!ELSE
    $(MAKE) /$(MAKEFLAGS) $(EDK_DEFAULTS)\
        /f $(BUILD_DIR)\PeiLib.mak all\
		"MY_INCLUDES=$(EDK_INCLUDES)"\
        TYPE=PEI_LIBRARY "OBJECTS=$(PEI_LIB_OBJECTS)"
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