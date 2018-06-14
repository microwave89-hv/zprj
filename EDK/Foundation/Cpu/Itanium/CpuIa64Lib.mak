#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/CpuIa64Lib/CpuIa64Lib.mak 1     1/20/12 4:00a Jeffch $
#
# $Revision: 1 $
#
# $Date: 1/20/12 4:00a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/CpuIa64Lib/CpuIa64Lib.mak $
# 
# 1     1/20/12 4:00a Jeffch
# Create Intel EDK 1117 Patch 7.
# 
# 1     9/27/11 6:23a Wesleychen
# Intel EDK initially releases.
# 
# 2     9/02/09 3:08a Iminglin
# EIP24919
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	CpuIa64Lib.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************
!IF "$(PROCESSOR)"=="IPF"
$(CPUIA64LIB) : CpuIa64Lib

$(BUILD_DIR)\CpuIa64Lib.lib : CpuIa64Lib

CpuIa64Lib : $(BUILD_DIR)\CpuIa64Lib.mak CpuIa64LibBin

$(BUILD_DIR)\CpuIa64Lib.mak : $(CpuIa64Lib_DIR)\$(@B).cif $(CpuIa64Lib_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(CpuIa64Lib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

CpuIa64LibBin : 
	$(MAKE) /$(MAKEFLAGS) $(EDK_DEFAULTS)\
		/f $(BUILD_DIR)\CpuIa64Lib.mak all\
		TYPE=LIBRARY
!ENDIF
#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************