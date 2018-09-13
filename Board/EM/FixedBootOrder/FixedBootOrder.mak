#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************
# $Header: /Alaska/BIN/Modules/Template/FixedBootOrder Demo/Board/em/FixedBootOrder/FixedBootOrder.mak 13    10/08/14 1:46a Dukeyeh $
#
# $Revision: 13 $
#
# $Date: 10/08/14 1:46a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Modules/Template/FixedBootOrder Demo/Board/em/FixedBootOrder/FixedBootOrder.mak $
# 
# 13    10/08/14 1:46a Dukeyeh
# [TAG]  		EIP184538
# [Category]  	Improvement
# [Description]  	FixedBootOrder changes the values of variables in
# StdDefaults variable and updates their checksum also if need be. 
# [Files]  		FixedBootOrder.c
# FixedBootOrder.mak
# 
# 12    1/26/13 2:57a Easonchen
# [TAG]  		EIP112714
# [Category]  	Improvement
# [Description]  	Add include file elink
# [Files]  		
# FixedBootOrder.c
# FixedBootOrder.sdl
# FixedBootOrder.mak
# 
# 11    6/28/12 11:23a Easonchen
# Make a new FixedBootOrder module by utilizing 4.6.4.1 BDS
# functionality. 
# 
# 10    11/12/10 3:44a Easonchen
# remove $(EFICOMMONLIB)
# 
# 9     9/14/10 2:41a Easonchen
# TAG: EIP41634
# 1.Add file FBOHii.obj and $(EFICOMMONLIB) to SetupBin.
# 
# 8     4/15/09 3:46a Jameswang
# Added more include path for EDK.
# 
# 7     3/26/09 2:45a Jameswang
# Added include path to make all #include in source files not to use any
# directory path.
# 
# 6     3/02/09 3:21a Jameswang
# Improvement: Do not need to modify the TSE core files.
# Description: Separate OemFixedBootOrder to FBOSetOrder.c, this file
# will be linked with TSE source to use hook BeforeLegacyBootLaunchHook
# 
# 5     2/19/09 10:27p Jameswang
# TAG: EIP19207
# Bug fix: Fixed build error if x64_BUILD=1
# Root cause: memset() is defined and linked in
# AMIDXELIB:x64CLib.c:memset and
# EFIDRIVERLIB:EFICOMMONLIB:COMPILERSTUB:memset.c
# Solution: Avoid linking EFIDRIVERLIB
# 
# Also, use inference rules to make override working.
# 
# 4     3/21/08 5:09a Jameswang
# (EIP12255) Do not need to link with minisetup for hooking on eLinks
# because we do not use BOOT####.  BOOT#### can not control individual
# device boot order in each type.
# 
# 3     2/20/08 12:56a Jameswang
# Adds header.
# 
#**********************************************************************

# MAK file for the eModule:FixedBootOrder

#<AMI_FHDR_START>
#-----------------------------------------------------------------------
# Name:	FixedBootOrder.mak
#
# Description:	This is a make file used to build component
#
#-----------------------------------------------------------------------
#<AMI_FHDR_END>
all : FixedBootOrder 

CORE_DXE_LIBBin : $(BUILD_DIR)\FBOSetOrder.obj

FixedBootOrder : $(BUILD_DIR)\FixedBootOrder.mak $(BUILD_DIR)\FixedBootOrderStrTokens.h

#-----------------------------------------------------------------------
#			Generic dependencies
#-----------------------------------------------------------------------
$(BUILD_DIR)\FixedBootOrder.mak : $(@B).cif $(FixedBootOrder_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(@B).cif $(CIF2MAK_DEFAULTS)

#-----------------------------------------------------------------------
# Paths and other definitions
#-----------------------------------------------------------------------

#-----------------------------------------------------------------------
# AMICSP library files compilation
#-----------------------------------------------------------------------
{$(FixedBootOrder_DIR)}.c{$(BUILD_DIR)}.obj::
	$(CC) $(CFLAGS) /I $(TSEBIN_DIR)\inc /I $(FixedBootOrder_DIR) /I $(Foundation_DIR) /I $(CORE_DXE_DIR) /I $(NVRAM_DIR) /Fo$(BUILD_DIR)\ $<

AMITSEBin : $(BUILD_DIR)\FixedBootOrderTSE.obj
SetupBin :  $(BUILD_DIR)\FixedBootOrder.obj  $(BUILD_DIR)\FixedBootOrderHII.obj $(BUILD_DIR)\NVRAMDXE.lib

$(BUILD_DIR)\FixedBootOrder.obj : $(BUILD_DIR)\FixedBootOrderStrTokens.h

$(BUILD_DIR)\FixedBootOrderStrTokens.h : $(FIXEDBOOTORDER_STRTOKENS_INCLUDE_FILES)
   if exist $(BUILD_DIR)\FixedBootOrderStrTokens.h del $(BUILD_DIR)\FixedBootOrderStrTokens.h
   $(SILENT) for %%f in ($(**:"=)) do $(ECHO) #include "%%f" >> $@

#-----------------------------------------------------------------------
#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************
