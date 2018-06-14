#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2013, American Megatrends, Inc.            **
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
# $Header: /Alaska/BIN/Chipset/Intel/NorthBridge/Haswell/Intel SystemAgent NB Chipset/LegacyRegion/LegacyRegion.mak 1     4/02/13 6:27a Ireneyang $
#
# $Revision: 1 $
#
# $Date: 4/02/13 6:27a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Chipset/Intel/NorthBridge/Haswell/Intel SystemAgent NB Chipset/LegacyRegion/LegacyRegion.mak $
# 
# 1     4/02/13 6:27a Ireneyang
# Support CSM Label 80.
# 
# 2     12/26/12 6:05a Abelwu
# Move LegacyRegion from CSM to NB eChipset.
# 
# 1     12/25/12 3:03a Abelwu
# Move Legacy Region from CSM to NB eChipset
# 
# 1     12/20/12 12:35p Olegi
# 
# 6     3/17/06 6:03p Felixp
# 
# 5     12/02/05 11:44a Felixp
# 
# 4     4/04/05 4:20p Sivagarn
# Included CSP Library in the build process
# 
# 2     2/22/05 10:00a Sivagarn
# - Updated to latest labeled CSM & Core
# 
# 3     1/18/05 3:22p Felixp
# PrintDebugMessage renamed to Trace
# 
# 2     12/17/04 9:12a Olegi
# 
# 1     10/26/04 9:48a Olegi
# 
# 1     8/30/04 8:17p Markw
# 
# 1     8/13/04 2:39p Markw
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name: LegacyRegion_mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************
all : LegacyRegion

LegacyRegion : $(BUILD_DIR)\NBLegacyRegion.mak LegacyRegionBin

$(BUILD_DIR)\NBLegacyRegion.mak : $(LEGACY_REGION_DIR)\LegacyRegion.cif $(LEGACY_REGION_DIR)\LegacyRegion.mak $(BUILD_RULES)
	$(CIF2MAK) $(LEGACY_REGION_DIR)\LegacyRegion.cif $(CIF2MAK_DEFAULTS)

LegacyRegionBin : $(AMIDXELIB) $(AMICSPLib)
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\NBLegacyRegion.mak all\
		GUID=59242DD8-E7CF-4979-B60E-A6067E2A185F \
		ENTRY_POINT=InitializeLegacyRegion \
		DEPEX1=$(LEGACY_REGION_DIR)\LegacyRegion.dxs\
		DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX \
		TYPE=BS_DRIVER \
		COMPRESS=1\

#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2013, American Megatrends, Inc.            **
#**                                                                     **
#**                       All Rights Reserved.                          **
#**                                                                     **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
#**                                                                     **
#**                       Phone: (770)-246-8600                         **
#**                                                                     **
#*************************************************************************
#*************************************************************************
