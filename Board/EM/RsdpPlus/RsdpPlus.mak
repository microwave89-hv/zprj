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
# $Header: /Alaska/SOURCE/Modules/RsdpPlus/RsdpPlus.mak 5     8/17/12 8:13a Norlwu $
#
# $Revision: 5 $
#
# $Date: 8/17/12 8:13a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/RsdpPlus/RsdpPlus.mak $
# 
# 5     8/17/12 8:13a Norlwu
# [TAG]  		EIP98247
# [Category]  	Improvement
# [Description]  	[RsdpPlus]Add alignment support in
# MANAGE_SHADOW_RAM_PROTOCOL
# [Files]  		RsdpPlus.sdl
# RsdpPlus.mak
# RsdpPlus.c
# ManageShadowRam.c
# ManageShadowRam.h
# 
# 4     2/09/12 3:15a Norlwu
# [TAG]  		EIP81756
# [Category]  	New Feature
# [Description]  	Enhance RspdPlus module.
# [Files]  		RsdpPlus.sdl
# RsdpPlus.mak
# RsdpPlus.c
# RsdpPlusLInk.c
# RsdpPlus.cif
# 
# 3     12/14/11 2:05a Norlwu
# [TAG]  		EIP77341
# [Category]  	Improvement
# [Description]  	V110 can't running ATI_DIAG problem.
# [Files]  		RsdpPlus.sdl
# RsdpPlus.mak
# RsdpPlus.c
# RsdpPlus.chm
# RsdpPlus.cif
# 
# 2     9/22/11 3:23a Norlwu
# [TAG]  		EIP67948
# [Category]  	New Feature
# [Description]  	EFI boot need to create the RSDT table
# [Files]  		RsdpPlus.cif
# RsdpPlus.sdl
# RsdpPlus.mak
# RsdpPlus.c
# RsdpPlusLInk.c
# RsdpPlus.dxs
# RsdpPlus.chm
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:			RsdpPlus.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************
#all : RsdpPlus

#RsdpPlus : $(BUILD_DIR)\RsdpPlus.mak


#---------------------------------------------------------------------------
#		Complier EFI boot function
#---------------------------------------------------------------------------
RSDPPLUS_CFLAGS=$(CFLAGS) \
	-I $(TSEBIN_DIR)\Inc \
	-I $(TSEBIN_DIR)

AMITSEBin : $(BUILD_DIR)\RsdpPlusLink.obj $(BUILD_DIR)\RsdpPlus.obj

$(BUILD_DIR)\RsdpPlusLink.obj : $(RsdpPlus_DIR)\RsdpPlusLink.c
	$(CC) $(RSDPPLUS_CFLAGS) /Fo$(BUILD_DIR)\RsdpPlusLink.obj $(RsdpPlus_DIR)\RsdpPlusLink.c

$(BUILD_DIR)\RsdpPlus.obj : $(RsdpPlus_DIR)\RsdpPlus.c
	$(CC) $(RSDPPLUS_CFLAGS) /Fo$(BUILD_DIR)\RsdpPlus.obj $(RsdpPlus_DIR)\RsdpPlus.c

CORE_DXEBin : $(BUILD_DIR)\ManageShadowRam.obj

$(BUILD_DIR)\ManageShadowRam.obj : $(RsdpPlus_DIR)\ManageShadowRam.c
    $(CC) $(CFLAGS) \
	/D\"UPDATE_E000_SHADOW_RAM_HOOK_LIST=$(UpdateE000ShadowRamHook)\" \
	/D\"UPDATE_F000_SHADOW_RAM_HOOK_LIST=$(UpdateF000ShadowRamHook)\" \
	/Fo$(BUILD_DIR)\ManageShadowRam.obj $(RsdpPlus_DIR)\ManageShadowRam.c

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