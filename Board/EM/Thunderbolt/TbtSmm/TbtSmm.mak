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
#**********************************************************************
# $Header: /Alaska/SOURCE/Modules/Thunderbolt/TbtSmm/TbtSmm.mak 3     6/21/13 7:44a Barretlin $
#
# $Revision: 3 $
#
# $Date: 6/21/13 7:44a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/Thunderbolt/TbtSmm/TbtSmm.mak $
# 
# 3     6/21/13 7:44a Barretlin
# [TAG]  		EIP N/A
# [Category]  	Improvement
# [Description]  	Fix build error with non Intel RC project
# [Files]  		TbtSmm.mak
# 
# 2     6/13/13 11:36p Barretlin
# [TAG]  		EIP None
# [Category]  	Improvement
# [Description]  	change obj file name to avoid ambiguous
# [Files]  		TbtSmm.mak
# 
# 1     1/10/13 4:56a Barretlin
# Change SS path and update module for Thunderbolt Spec 1.6 for Cactus
# Ridge chip and Thunderbolt Spec 0.5 for Redwood Ridge chip
# 
# 3     10/04/12 11:53a Barretlin
# [TAG]  		EIP N/A
# [Category]  	Improvement
# [Description]  	Use global definition for genernic
# [Files]  		TbtSmm.c TbtSmm.mak
# 
# 2     9/03/12 6:27a Barretlin
# [TAG]  		EIP N/A
# [Category]  	Improvement
# [Description]  	Change driver type and dependence for SharkBay platform
# [Files]  		TbtSmm.mak TbtSmm.c TbtSmm.dxs
# 
# 1     12/08/11 4:09a Wesleychen
# Thunderbolt eModule initially releases.
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	TbtSmm.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************
all : TbtSmm

TbtSmm: $(BUILD_DIR)\TbtSmm.mak TbtSmmBin

TBT_SMM_OBJECTS = \
!IF $(TBT_INTEL_RC_CONFIG) == 1
$(BUILD_SB_BOARD_DIR)\GetSetupData.obj \
!ENDIF
$(BUILD_DIR)\$(TbtSmm_DIR)\TbtSmm.obj

$(BUILD_DIR)\TbtSmm.mak : $(TbtSmm_DIR)\TbtSmm.cif $(TbtSmm_DIR)\$(@B).mak $(BUILD_RULES)
    $(CIF2MAK) $(TbtSmm_DIR)\TbtSmm.cif $(CIF2MAK_DEFAULTS)

TbtSmm_INCLUDES=\
    $(TBT_OEMBOARD_INCLUDES)\
!IF $(TBT_INTEL_RC_CONFIG) == 1
    $(INTEL_PCH_INCLUDES)\
!ENDIF

TbtSmmBin : $(AMIDXELIB) $(AMICSPLib)
    $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
        /f $(BUILD_DIR)\TbtSmm.mak all\
        "CFLAGS=$(CFLAGS)"\
        OBJECTS="$(TBT_SMM_OBJECTS)" \
        GUID=B7D9F0D7-EBDB-4EE4-AB77-B30C4B9093CC\
        ENTRY_POINT=TbtSmm_Init\
        "MY_INCLUDES=$(TbtSmm_INCLUDES)"\
!IF $(PI_SPECIFICATION_VERSION) >= 0x1000A && $(CORE_COMBINED_VERSION) >= 0x4028B
        TYPE=DXESMM_DRIVER PE_TYPE=RT_DRIVER \
        DEPEX1=$(TbtSmm_DIR)\TbtSmm.DXS DEPEX1_TYPE=EFI_SECTION_SMM_DEPEX \
        DEPEX2=$(TbtSmm_DIR)\TbtSmm.DXS DEPEX2_TYPE=EFI_SECTION_DXE_DEPEX \
!ELSE
        TYPE=BS_DRIVER \
        DEPEX1=$(TbtSmm_DIR)\TbtSmm.DXS DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX \
!ENDIF
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