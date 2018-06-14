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
# $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/SB SMI/SBSMI.mak 1     2/08/12 8:31a Yurenlai $
#
# $Revision: 1 $
#
# $Date: 2/08/12 8:31a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/SB SMI/SBSMI.mak $
# 
# 1     2/08/12 8:31a Yurenlai
# Intel Lynx Point/SB eChipset initially releases.
#
#*************************************************************************
#<AMI_FHDR_START>
#
# Name:         SBSMI.MAK
#
# Description:  Make file for the SB SMI handler code
#
#<AMI_FHDR_END>
#*************************************************************************
!IFNDEF PI_SPECIFICATION_VERSION
PI_SPECIFICATION_VERSION = 0
!ENDIF

all : SBSMI

SBSMI: $(BUILD_DIR)\SBSMI.mak SBSMIBin

$(BUILD_DIR)\SBSMI.mak : $(SB_SMI_PATH)\SBSMI.cif $(SB_SMI_PATH)\$(@B).mak $(BUILD_RULES)
    $(CIF2MAK) $(SB_SMI_PATH)\SBSMI.cif $(CIF2MAK_DEFAULTS)

SBSMIBin : $(AMIDXELIB) $(AMICSPLib)
    $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
        /f $(BUILD_DIR)\SBSMI.mak all\
        "CFLAGS=$(CFLAGS) $(SB_INCLUDES) $(INTEL_PCH_INCLUDES)"\
        OBJECTS="$(SB_SMI_OBJECTS)" \
        GUID=7B8DB049-C7C7-4d3b-809F-926DEE47CCA2\
        ENTRY_POINT=InitializeSBSmm\
!IF $(PI_SPECIFICATION_VERSION) >= 0x1000A && $(CORE_COMBINED_VERSION) >= 0x4028B
        TYPE=BS_DRIVER \
        DEPEX1=$(SB_SMI_PATH)\SBSmi.DXS \
!ELSE
        TYPE=BS_DRIVER \
        DEPEX1=$(SB_SMI_PATH)\SBSmi.DXS DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX \
!ENDIF
        COMPRESS=1

# {7B8DB049-C7C7-4d3b-809F-926DEE47CCA2}
# {0x7b8db049, 0xc7c7, 0x4d3b, 0x80, 0x9f, 0x92, 0x6d, 0xee, 0x47, 0xcc, 0xa2}

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
