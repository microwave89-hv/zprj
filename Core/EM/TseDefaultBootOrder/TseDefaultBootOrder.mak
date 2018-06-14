#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
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
# $Header: /Alaska/BIN/Modules/BootOptionPolicies/TseDefaultBootOrder/TseDefaultBootOrder.mak 1     1/20/11 10:52a Felixp $
#
# $Revision: 1 $
#
# $Date: 1/20/11 10:52a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Modules/BootOptionPolicies/TseDefaultBootOrder/TseDefaultBootOrder.mak $
# 
# 1     1/20/11 10:52a Felixp
# 
# 6     1/13/10 2:13p Felixp
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	TseDefaultBootOrder.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************

CORE_DXEBin : $(BUILD_DIR)\TseDefaultBootOrder.lib

$(BUILD_DIR)\TseDefaultBootOrder.lib : TseDefaultBootOrder

TseDefaultBootOrder : $(BUILD_DIR)\TseDefaultBootOrder.mak TseDefaultBootOrderBin

$(BUILD_DIR)\TseDefaultBootOrder.mak : $(TseDefaultBootOrder_DIR)\$(@B).cif $(TseDefaultBootOrder_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(TseDefaultBootOrder_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

TseDefaultBootOrderBin : $(AMIDXELIB)
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\TseDefaultBootOrder.mak all\
        "MY_INCLUDES=/I$(CORE_DXE_DIR)"\
		TYPE=LIBRARY

#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************