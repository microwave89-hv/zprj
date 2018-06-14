#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
#**                                                                     **
#**                       All Rights Reserved.                          **
#**                                                                     **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
#**                                                                     **
#**                       Phone: (770)-246-8600                         **
#**                                                                     **
#*************************************************************************
#*************************************************************************

#*************************************************************************
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/Platform/PlatformInfo/PlatformInfo.mak 1     2/09/12 12:33a Yurenlai $
#
# $Revision: 1 $
#
# $Date: 2/09/12 12:33a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/Platform/PlatformInfo/PlatformInfo.mak $
# 
# 1     2/09/12 12:33a Yurenlai
# Initial check in.
#
#*************************************************************************
#<AMI_FHDR_START>
#
# Name:         PlatformInfo.mak
#
# Description:  This make file builds AcpiPlatform module DXE 
#               components and link them to respective binary
#
#<AMI_FHDR_END>
#*************************************************************************

#---------------------------------------------------------------------------
#   Create PLATFORMINFO DXE Component
#---------------------------------------------------------------------------
all : PlatformInfo

PlatformInfo : $(BUILD_DIR)\PlatformInfo.mak PlatformInfoBin

$(BUILD_DIR)\PlatformInfo.mak : $(PlatformInfo_DIR)\PlatformInfo.cif $(PlatformInfo_DIR)\$(@B).mak $(BUILD_RULES)
 $(CIF2MAK) $(PlatformInfo_DIR)\PlatformInfo.cif $(CIF2MAK_DEFAULTS)

PLATFORM_INFO_INCLUDES = \
        $(ACPI_PLATFORM_INCLUDES)\
        $(INTEL_MCH_INCLUDES)\
        $(INTEL_PCH_INCLUDES)

PLATFORM_INFO_DEFINES = $(MY_DEFINES) $(MCH_DEFINES)\


PlatformInfoBin: $(AMIDXELIB) $(AMICSPLib)
		$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
            	/f $(BUILD_DIR)\PlatformInfo.mak all \
        	"MY_INCLUDES=$(PLATFORM_INFO_INCLUDES)"\
    		GUID=1314216C-CB8D-421c-B854-06231386E642\
    		ENTRY_POINT=PlatformInfoInit \
    		TYPE=BS_DRIVER\
    		DEPEX1=$(PlatformInfo_DIR)\PlatformInfo.dxs\
    		DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX\
    		COMPRESS=1


#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
#**                                                                     **
#**                       All Rights Reserved.                          **
#**                                                                     **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
#**                                                                     **
#**                       Phone: (770)-246-8600                         **
#**                                                                     **
#*************************************************************************
#*************************************************************************