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
#**********************************************************************
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/AmtWrapper/AsfTable/AsfTable.mak 1     2/08/12 1:09a Klzhan $
#
# $Revision: 1 $
#
# $Date: 2/08/12 1:09a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/AmtWrapper/AsfTable/AsfTable.mak $
# 
# 1     2/08/12 1:09a Klzhan
# 
# 1     2/25/11 1:44a Klzhan
# Initial Check-in
# 
# 1     12/03/10 5:10a Klzhan
# Initial Check-in.
# 
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	AsfTable.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************
EDK : AsfTable

AsfTable : $(BUILD_DIR)\AsfTable.mak AsfTableBin

$(BUILD_DIR)\AsfTable.mak : $(AsfTable_DIR)\$(@B).cif $(AsfTable_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(AsfTable_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

ASF_TABLE_INCLUDES=\
	$(EDK_INCLUDES)\
	$(MISCFRAMEWORK_INCLUDES)\
	$(ME_INCLUDES)\
	$(IndustryStandard_INCLUDES)\

AsfTableBin : $(EFIDRIVERLIB) $(EFICOMMONLIB) $(PRINTLIB)
	$(MAKE) /$(MAKEFLAGS) $(EDK_DEFAULTS)\
		/f $(BUILD_DIR)\AsfTable.mak all\
		GUID=E72527CF-505B-4b50-99CD-A32467FA4AA4\
		"MY_INCLUDES=$(ASF_TABLE_INCLUDES)" \
		ENTRY_POINT=AsfTableEntryPoint \
		TYPE=BS_DRIVER LIBRARIES= \
		DEPEX1=$(AsfTable_DIR)\AsfTable.dxs\
		DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX\
		COMPRESS=1\

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