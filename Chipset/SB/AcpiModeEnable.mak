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
# $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/AcpiModeEnable/AcpiModeEnable.mak 2     7/02/12 10:16a Victortu $
#
# $Revision: 2 $
#
# $Date: 7/02/12 10:16a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/AcpiModeEnable/AcpiModeEnable.mak $
# 
# 2     7/02/12 10:16a Victortu
# [TAG]		None
# [Category]	Bug Fix
# [Severity]	Normal
# [Symptom]	System may hang at 0xB1 when boot to UEFI Windows 8.
# [Solution]	Set Driver type to SMM_DRIVER.
# [Files]		AcpiModeEnable.mak
# 
# 1     2/08/12 8:29a Yurenlai
# Intel Lynx Point/SB eChipset initially releases.
#
#*************************************************************************
#<AMI_FHDR_START>
#
# Name:         AcpiModeEnable.MAK
#
# Description:  Make file to enable/disable ACPI mode
#
#<AMI_FHDR_END>
#*************************************************************************
!IFNDEF PI_SPECIFICATION_VERSION
PI_SPECIFICATION_VERSION = 0
!ENDIF

all : AcpiModeEnable

AcpiModeEnable : $(BUILD_DIR)\AcpiModeEnable.mak AcpiModeEnableBin

$(BUILD_DIR)\AcpiModeEnable.mak : $(ACPI_MODE_ENABLE_DIR)\AcpiModeEnable.cif $(ACPI_MODE_ENABLE_DIR)\$(@B).mak $(BUILD_RULES)
    $(CIF2MAK) $(ACPI_MODE_ENABLE_DIR)\AcpiModeEnable.cif $(CIF2MAK_DEFAULTS)

AcpiModeEnable_INCLUDES=\
    /I$(Foundation_DIR)\
    /I$(PROJECT_DIR)\
    $(INTEL_PCH_INCLUDES)\

AcpiModeEnableBin : $(AMIDXELIB) $(AMICSPLib)
    $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
        /f $(BUILD_DIR)\AcpiModeEnable.mak all\
        "CFLAGS=$(CFLAGS) /I$(SB_BOARD_DIR) /D\"OEM_HDA_VERB_TABLE=$(OEM_HDA_VERB_TABLE)\" /D\"OEM_HDA_VERB_TABLE_CONTENT=$(OEM_HDA_VERB_TABLE_CONTENT)\""\
        GUID=750890A6-7ACF-4f4f-81BD-B400C2BEA95A\
        ENTRY_POINT=AcpiModeEnableInit\
        "MY_INCLUDES=$(AcpiModeEnable_INCLUDES)"\
!IF $(PI_SPECIFICATION_VERSION) >= 0x1000A && $(CORE_COMBINED_VERSION) >= 0x4028B
        TYPE=SMM_DRIVER \
        DEPEX1=$(ACPI_MODE_ENABLE_DIR)\AcpiModeEnable.DXS \
!ELSE
        TYPE=BS_DRIVER \
        DEPEX1=$(ACPI_MODE_ENABLE_DIR)\AcpiModeEnable.DXS DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX \
!ENDIF
        COMPRESS=1\
        "INIT_LIST=$(AcpiEnableCallbackList)"\
        "INIT_LIST2=$(AcpiDisableCallbackList)"

AcpiModeEnableBin : $(CSP_ACPI_OBJ_FILES)

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
