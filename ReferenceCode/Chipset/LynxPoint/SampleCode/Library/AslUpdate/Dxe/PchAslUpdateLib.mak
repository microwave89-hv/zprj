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
# $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Refcode/PchSampleCode/Library/AslUpdate/Dxe/PchAslUpdateLib.mak 1     7/02/12 9:37a Victortu $
#
# $Revision: 1 $
#
# $Date: 7/02/12 9:37a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Refcode/PchSampleCode/Library/AslUpdate/Dxe/PchAslUpdateLib.mak $
# 
# 1     7/02/12 9:37a Victortu
# PchAslUpdateLib initially releases.
# 
# 6     1/13/10 2:13p Felixp
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	PchAslUpdateLib.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************
all : PchAslUpdateLib

$(PchAslUpdateLib_LIB) : PchAslUpdateLib

PchAslUpdateLib : $(BUILD_DIR)\PchAslUpdateLib.mak PchAslUpdateLibBin

$(BUILD_DIR)\PchAslUpdateLib.mak : $(PchAslUpdateLib_DIR)\$(@B).cif $(PchAslUpdateLib_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(PchAslUpdateLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

PchAslUpdateLib_INCLUDES=\
    $(EDK_INCLUDES) \
    $(EdkIIGlueLib_INCLUDES)\
    /I$(INTEL_PCH_DIR)\SampleCode\Include

PchAslUpdateLib_DEFINES = \
    $(MY_DEFINES)\
    /D __EDKII_GLUE_BASE_MEMORY_LIB__\
    /D __EDKII_GLUE_UEFI_BOOT_SERVICES_TABLE_LIB__\
    /D __EDKII_GLUE_UEFI_RUNTIME_SERVICES_TABLE_LIB__

PchAslUpdateLib_LIBS=\
    $(EdkIIGlueBaseMemoryLib_LIB)\
    $(EdkIIGlueUefiBootServicesTableLib_LIB)\
    $(EdkIIGlueUefiRuntimeServicesTableLib_LIB)\

PchAslUpdateLibBin: $(PchAslUpdateLib_LIBS)
	    $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS) \
            /f $(BUILD_DIR)\PchAslUpdateLib.mak all \
            "MY_INCLUDES=$(PchAslUpdateLib_INCLUDES)" \
            "MY_DEFINES=$(PchAslUpdateLib_DEFINES)"\
            TYPE=LIBRARY
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