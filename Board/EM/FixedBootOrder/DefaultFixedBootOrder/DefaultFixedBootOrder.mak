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
#**********************************************************************
# $Archive: /Alaska/BIN/Modules/Template/FixedBootOrder Demo/Board/em/FixedBootOrder/DefaultFixedBootOrder.mak $
#
# $Author: Walonli $
#
# $Revision: 2 $
#
# $Date: 8/13/14 11:20p $
#
#*****************************************************************
#*****************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Modules/Template/FixedBootOrder Demo/Board/em/FixedBootOrder/DefaultFixedBootOrder.mak $
# 
# 2     8/13/14 11:20p Walonli
# [TAG]  		EIP180632
# [Category]  	New Feature
# [Description]  	Add FixedBootOrder Protocol to change device/group
# name.
# [Files]  		DefaultFixedBootOrder.sdl
# DefaultFixedBootOrder.c
# DefaultFixedBootOrder.mak
# DefaultFixedBootOrder.cif
# 
# 1     6/28/12 11:41a Easonchen
# Make a new FixedBootOrder module by utilizing 4.6.4.1 BDS
# functionality.
# 
#
#*****************************************************************


# MAK file for the eModule:DefaultFixedBootOrder

#<AMI_FHDR_START>
#-----------------------------------------------------------------------
# Name:	DefaultFixedBootOrder.mak
#
# Description:	This is a make file used to build component
#
#-----------------------------------------------------------------------
#<AMI_FHDR_END>
all : DefaultFixedBootOrder 

CORE_DXE_LIBBin : $(BUILD_DIR)\DefaultFixedBootOrder.obj

DefaultFixedBootOrder : $(BUILD_DIR)\DefaultFixedBootOrder.mak

#-----------------------------------------------------------------------
#			Generic dependencies
#-----------------------------------------------------------------------
$(BUILD_DIR)\DefaultFixedBootOrder.mak : $(DefaultFixedBootOrder_DIR)\$(@B).cif $(DefaultFixedBootOrder_DIR)\$(@B).mak DefaultFixedBootOrderElink $(BUILD_RULES)
	$(CIF2MAK) $(DefaultFixedBootOrder_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

#-----------------------------------------------------------------------
# Paths and other definitions
#-----------------------------------------------------------------------

#-----------------------------------------------------------------------
# AMICSP library files compilation
#-----------------------------------------------------------------------
{$(DefaultFixedBootOrder_DIR)}.c{$(BUILD_DIR)}.obj::
	$(CC) $(CFLAGS) /I $(INCLUDE_DIR) /I $(TSEBIN_DIR)\inc /I $(FixedBootOrder_DIR) /I $(DefaultFixedBootOrder_DIR) /I $(Foundation_DIR) /I $(CORE_DXE_DIR) /Fo$(BUILD_DIR)\ $<

#-----------------------------------------------------------------------
#		Create OEM Boot Order Setup Screens
#-----------------------------------------------------------------------
SetupSdbs : $(BUILD_DIR)\DefaultFixedBootOrder.mak DefaultFixedBootOrderSDB

DefaultFixedBootOrderSDB :
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\DefaultFixedBootOrder.mak all\
		TYPE=SDB NAME=DefaultFixedBootOrder MAKEFILE=$(BUILD_DIR)\DefaultFixedBootOrder.mak STRING_CONSUMERS=$(DefaultFixedBootOrder_DIR)\DefaultFixedBootOrder.sd

DefaultFixedBootOrderElink :
	$(SILENT)type << >$(BUILD_DIR)\DefaultFixedBootOrder.h
#define FBO_CHANGE_DEVICE_NAME_FUNCS $(FBO_ChangeDeviceNameFunctions)$(EOL)
<<

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
