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
# $Header: /Alaska/SOURCE/Modules/PTT/FastBootPei.mak 1     11/02/10 1:47a Bibbyyeh $
#
# $Revision: 1 $
#
# $Date: 11/02/10 1:47a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/PTT/FastBootPei.mak $
# 
# 1     11/02/10 1:47a Bibbyyeh
# [TAG]  		EIP47280
# [Category]  	New Feature
# [Description]  	Currently, BIOS will copy FV_MAIN or FV_BB into memory
# in DXE phase.
# If BIOS copy rom before CPU disable flash cache in PEI phase.
# Some data are in cache already, don't need to read from physical ROM.
# It can help to save some time.
# [Files]  		FastBootPei.cif
# FastBootPei.mak
# FastBootPei.c
# FastBootPei.dxs
# 
# 
#*************************************************************************
#<AMI_FHDR_START>
#
# Name: FastBootPei.mak
#
# Description:
# Make file to build FastBootPei FFS
#
#<AMI_FHDR_END>
#*************************************************************************
# MAK file for the eModule:Platform

all : FastBootPei 

#---------------------------------------------------------------------------
#			Generic FastBootPei dependencies
#---------------------------------------------------------------------------

$(BUILD_DIR)\FastBootPei.mak : $(FastBoot_DIR)\FastBootPei.cif $(BUILD_RULES)
	$(CIF2MAK) $(FastBoot_DIR)\FastBootPei.cif $(CIF2MAK_DEFAULTS)


#---------------------------------------------------------------------------
#		Create FastBoot PEI Component
#---------------------------------------------------------------------------
FastBootPei : $(BUILD_DIR)\FastBootPei.mak FastBootPeiBin


FastBootPei_OBJECTS = $(BUILD_DIR)\$(FastBoot_DIR)\FastBootPei.obj

FastBootPeiBin : $(AMIPEILIB)
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\FastBootPei.mak all\
		NAME=FastBootPei\
		MAKEFILE=$(BUILD_DIR)\FastBootPei.mak \
       	"CFLAGS=$(CFLAGS) /I$(FastBoot_DIR)"\
		OBJECTS="$(FastBootPei_OBJECTS)" \
		GUID=333BB2A3-4F20-4CCC-AC38-0672D7412345\
		ENTRY_POINT=FastBootPeiEntry \
		TYPE=PEIM \
		DEPEX1=$(FastBoot_DIR)\FastBootPei.DXS DEPEX1_TYPE=EFI_SECTION_PEI_DEPEX \
		COMPRESS=0

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