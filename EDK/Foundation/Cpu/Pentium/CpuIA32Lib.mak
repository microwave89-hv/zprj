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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/CpuIA32Lib/CpuIA32Lib.mak 1     1/20/12 4:00a Jeffch $
#
# $Revision: 1 $
#
# $Date: 1/20/12 4:00a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/CpuIA32Lib/CpuIA32Lib.mak $
# 
# 1     1/20/12 4:00a Jeffch
# Create Intel EDK 1117 Patch 7.
# 
# 1     9/27/11 6:22a Wesleychen
# Intel EDK initially releases.
# 
# 3     4/29/11 2:30a Iminglin
# [TAG]  		EIP59360
# [Category]  	Improvement
# [Description]  	EDK- link error:unresolved external EfiCpuVersion
# When a driver uses the function EfiCpuVersion, below link error will
# happen.
# 
# error LNK2001: unresolved external symbol EfiCpuVersion
# 
# [Files]  		CpuIA32Lib.mak
# 
# 2     9/02/09 3:10a Iminglin
# EIP24919
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	CpuIA32Lib.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************

$(CPUIA32LIB) : CpuIA32Lib

!IF "$(PROCESSOR)"=="IA32"
CpuIA32Lib_OBJECTS=\
$$(BUILD_DIR)\$(CpuIA32Lib_DIR)\CpuIA32Lib\IA32\CpuIA32.obj
!ELSEIF "$(PROCESSOR)"=="x64"
CpuIA32Lib_OBJECTS_DXE=\
$$(BUILD_DIR)\$(CpuIA32Lib_DIR)\CpuIA32Lib\x64\Cpu.obj\
$$(BUILD_DIR)\$(CpuIA32Lib_DIR)\CpuIA32Lib\EfiCpuVersion.obj
CpuIA32Lib_OBJECTS_PEI=\
$$(BUILD_DIR)\$(CpuIA32Lib_DIR)\CpuIA32Lib\IA32\CpuIA32.obj
!ENDIF

CpuIA32Lib : $(BUILD_DIR)\CpuIA32Lib.mak CpuIA32LibBin

$(BUILD_DIR)\CpuIA32Lib.mak : $(CpuIA32Lib_DIR)\$(@B).cif $(CpuIA32Lib_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(CpuIA32Lib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

CpuIA32LibBin : 
!IF "$(PROCESSOR)"=="x64"
	$(MAKE) /$(MAKEFLAGS) $(EDK_DEFAULTS)\
		/f $(BUILD_DIR)\CpuIA32Lib.mak all\
		TYPE=LIBRARY\
		"OBJECTS=$(CpuIA32Lib_OBJECTS_DXE)"
	$(MAKE) /$(MAKEFLAGS) $(EDK_DEFAULTS) BUILD_DIR=$(BUILD_DIR)\IA32\
		/f $(BUILD_DIR)\CpuIA32Lib.mak all\
		TYPE=PEI_LIBRARY\
		"OBJECTS=$(CpuIA32Lib_OBJECTS_PEI)"
!ELSE
	$(MAKE) /$(MAKEFLAGS) $(EDK_DEFAULTS)\
		/f $(BUILD_DIR)\CpuIA32Lib.mak all\
		TYPE=LIBRARY\
		"OBJECTS=$(CpuIA32Lib_OBJECTS)"
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