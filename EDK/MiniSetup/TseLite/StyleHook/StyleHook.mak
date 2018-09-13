#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2010, American Megatrends, Inc.            **
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
# $Header: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/StyleHook/StyleHook.mak 2     10/18/12 6:20a Arunsb $
#
# $Revision: 2 $
#
# $Date: 10/18/12 6:20a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/StyleHook/StyleHook.mak $
# 
# 2     10/18/12 6:20a Arunsb
# Updated for 2.16.1235 QA submission
## 
## 3     10/10/12 12:40p Arunsb
## Synched the source for v2.16.1232, backup with Aptio
# 
# 1     1/06/11 7:24p Madhans
# [TAG] - EIP 51678 
# [Category]- Enhancment
# [Severity]- Mordarate
# [Symptom]-  If OEMs override the style module parts, If new tse adds
# new style hook then 
# if the OEM has different style module, even if they don't need use the
# hook to avoid 
# compilation issue they need touch their style module to add the new
# hook.
# [RootCause] - The Original Style Hooks are part of Style module itself.
# [Solution]- To create Empty style Hook List in TSE core. This will
# allows the OEM not 
# to change their style module to update newer TSE.
# [Files] - StyleHook Module Part under TSE lite sources. StyleHook.lib
# StyleHookx64.lib tselitebin.sdl
# 
#
#*************************************************************************
#<AMI_FHDR_START>
#
# Name: StyleHook.mak
#
# Description:
# Empty Style Hooks Module part makefile
#
#<AMI_FHDR_END>
#*************************************************************************

STYLEHOOK_INCLUDES = \
	-I $(TSESRC_DIR) \
!if "$(TSE_STYLE_SOURCES_SUPPORT)" == "1"
	-I $(TSE_STYLE_DIR) \
!endif
!if "$(TSE_BOARD_SOURCE_SUPPORT)" == "1"
	-I $(TSE_BOARD_DIR)\
!endif
	-I $(TSESRC_DIR)\AMILOGO \
	-I $(TSELITESRC_DIR) \
	-I $(UEFISRC_DIR) \
	-I $(TSEBIN_DIR) \
	-I $(TSEBIN_DIR)\Inc \
	-I $(PROJECT_DIR)\Include\Protocol \
	-I $(PROJECT_DIR) \
	-I $(PROJECT_DIR)\Include \
	-I $(BUILD_DIR) \

$(BUILD_DIR)\StyleHook.lib : StyleHook

StyleHook : $(BUILD_DIR)\StyleHook.mak StyleHookBin

$(BUILD_DIR)\StyleHook.mak : $(TSESTYLEHOOK_DIR)\$(@B).cif $(TSESTYLEHOOK_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(TSESTYLEHOOK_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

!if "$(TSE_USE_EDK_LIBRARY)" == "1"
TSE_DEFAULTS = $(EDK_DEFAULTS)
!else
TSE_DEFAULTS = $(BUILD_DEFAULTS)
!endif

StyleHookBin : 
	$(MAKE) /$(MAKEFLAGS) $(TSE_DEFAULTS)\
		/f $(BUILD_DIR)\StyleHook.mak all\
		"MY_INCLUDES=$(STYLEHOOK_INCLUDES)"\
		"UNI_INCLUDE_PATH=$(TSEBIN_DIR)"\
		TYPE=LIBRARY \
        "EXT_HEADERS=$(BUILD_DIR)\token.h"\
		LIBRARY_NAME=$(BUILD_DIR)\StyleHook.lib\
		"CFLAGS=$(CFLAGS) /DTSE_FOR_APTIO_4_50"

#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2010, American Megatrends, Inc.            **
#**                                                                     **
#**                       All Rights Reserved.                          **
#**                                                                     **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
#**                                                                     **
#**                       Phone: (770)-246-8600                         **
#**                                                                     **
#*************************************************************************
#*************************************************************************
