#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/SwitchableGraphics/Sg TPV/Sg nVidia Optimus SMM/NvOptimusSMM.mak 3     10/16/12 4:26a Joshchou $
#
# $Revision: 3 $
#
# $Date: 10/16/12 4:26a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/SwitchableGraphics/Sg TPV/Sg nVidia Optimus SMM/NvOptimusSMM.mak $
# 
# 3     10/16/12 4:26a Joshchou
# [TAG]  		None
# [Category]  	Improvement
# [Description]  	Update for SA and ACPI RC 0.7.1
# [Files]  		NvOptimusSMM.mak
# 
# 2     9/09/12 11:07p Joshchou
# [TAG]  		EIPNone
# [Category]  	Improvement
# [Description]  	Tpv module support for sharkbay.
# [Files]  		NvOptimusSMM.mak
# NvOptimusSMM.c
# NvOptimusSMM.dxs
# NvOptimusSMM.ssp
# NvOptimusSMM.asl
# NvOptimusSMM.cif
# 
# 1     6/27/11 5:26a Alanlin
# [TAG]  		EIP61848
# [Category]  	New Feature
# [Description]  	Initial check-in.Integrated SwitchableGraphics Intel
# Reference code 0.6.0
# [Files]  		NvOptimusSMM.cif
# NvOptimusSMM.sdl
# NvOptimusSMM.mak
# NvOptimusSMM.c
# NvOptimusSMM.dxs
# NvOptimusSMM.ssp
# NvOptimusSMM.asl
# 
# 
# 1     3/17/11 6:14p Alexp
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	NvOptimusSMM.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************
SgTpv : NvOptimusSMM

NvOptimusSMM : $(BUILD_DIR)\NvOptimusSMM.mak NvOptimusSMMBin

$(BUILD_DIR)\NvOptimusSMM.mak : $(NvOptimusSMM_DIR)\$(@B).cif $(NvOptimusSMM_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(NvOptimusSMM_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

NvOptimusSMM_INCLUDES=\
    $(INTEL_MPG_INCLUDES)\
    $(ACPI_PLATFORM_INCLUDES)\
    /DTIANO_RELEASE_VERSION=$(TIANO_RELEASE_VERSION)\
    /I $(INTEL_SA_PROTOCOL_LIB_DIR)\

#    /I$(NvOptimusSMM_DIR) \
#    $(PROJECT_INCLUDES)\
#    $(Foundation_INCLUDES)\
#    /FIinclude\CompilerDirective.h\

NvOptimusSMMBin :$(AMIDXELIB) $(INTEL_SA_PROTOCOL_LIB)
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\NvOptimusSMM.mak all\
		GUID=8A4E8240-74F8-4024-AE2B-B39221C9FA59\
        "MY_INCLUDES= $(NvOptimusSMM_INCLUDES)"\
        DEPEX1=$(NvOptimusSMM_DIR)\NvOptimusSMM.dxs\
		ENTRY_POINT=NvSwSmiEntry \
		TYPE=BS_DRIVER \
		COMPRESS=1\

#        OBJECTS="$(BUILD_DIR)\$(NvOptimusSMM_DIR)\NvOptimusSMM.obj" \
#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************
