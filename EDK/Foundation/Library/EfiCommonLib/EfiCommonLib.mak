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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/EfiCommonLib/EfiCommonLib.mak 1     1/20/12 4:10a Jeffch $
#
# $Revision: 1 $
#
# $Date: 1/20/12 4:10a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/EfiCommonLib/EfiCommonLib.mak $
# 
# 1     1/20/12 4:10a Jeffch
# Create Intel EDK 1117 Patch 7.
# 
# 1     9/27/11 6:31a Wesleychen
# Intel EDK initially releases.
# 
# 3     11/06/09 4:28a Iminglin
# Edk-Dev-Snapshot-20090928
# 
# 2     9/02/09 3:56a Iminglin
# EIP24919
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	EfiCommonLib.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************
$(EFICOMMONLIB) : EfiCommonLib

EFI_COMMON_LIB_OBJECTS=\
$$(BUILD_DIR)\$(EfiCommonLib_DIR)\EfiCompareGuid.obj\
$$(BUILD_DIR)\$(EfiCommonLib_DIR)\EfiCompareMem.obj\
$$(BUILD_DIR)\$(EfiCommonLib_DIR)\linkedlist.obj\
$$(BUILD_DIR)\$(EfiCommonLib_DIR)\PostCode.obj\
$$(BUILD_DIR)\$(EfiCommonLib_DIR)\ReportStatusCode.obj\
$$(BUILD_DIR)\$(EfiCommonLib_DIR)\String.obj\
$$(BUILD_DIR)\$(EfiCommonLib_DIR)\ValueToString.obj\
$$(BUILD_DIR)\$(EfiCommonLib_DIR)\Misc.obj

EFI_COMMON_LIB_IA32_OBJECTS=\
$$(BUILD_DIR)\$(EfiCommonLib_DIR)\Ia32\EfiCopyMemSSE2.obj\
$$(BUILD_DIR)\$(EfiCommonLib_DIR)\Ia32\EfiSetMemSSE2.obj\
$$(BUILD_DIR)\$(EfiCommonLib_DIR)\Ia32\EfiZeroMemSSE2.obj\
$$(BUILD_DIR)\$(EfiCommonLib_DIR)\Ia32\LShiftU64.obj\
$$(BUILD_DIR)\$(EfiCommonLib_DIR)\Ia32\RShiftU64.obj\
$$(BUILD_DIR)\$(EfiCommonLib_DIR)\Ia32\MultU64x32.obj\
$$(BUILD_DIR)\$(EfiCommonLib_DIR)\Ia32\DivU64x32.obj\
$$(BUILD_DIR)\$(EfiCommonLib_DIR)\Ia32\Power10U64.obj\
$$(BUILD_DIR)\$(EfiCommonLib_DIR)\Ia32\Log2.obj\
$$(BUILD_DIR)\$(EfiCommonLib_DIR)\Ia32\GetPowerOfTwo.obj

!IF "$(PROCESSOR)"=="IA32"
EFI_COMMON_LIB_OBJECTS=$(EFI_COMMON_LIB_OBJECTS) $(EFI_COMMON_LIB_IA32_OBJECTS)
!ELSEIF "$(PROCESSOR)"=="x64"
EFI_COMMON_LIB_PEI_OBJECTS=$(EFI_COMMON_LIB_OBJECTS) $(EFI_COMMON_LIB_IA32_OBJECTS)
EFI_COMMON_LIB_DXE_OBJECTS=$(EFI_COMMON_LIB_OBJECTS)\
$$(BUILD_DIR)\$(EfiCommonLib_DIR)\x64\EfiCopyMemRep4.obj\
$$(BUILD_DIR)\$(EfiCommonLib_DIR)\EfiSetMem.obj\
$$(BUILD_DIR)\$(EfiCommonLib_DIR)\EfiZeroMem.obj\
$$(BUILD_DIR)\$(EfiCommonLib_DIR)\Math.obj
!ELSEIF "$(PROCESSOR)"=="IPF" || "$(PROCESSOR)"=="EBC"
EFI_COMMON_LIB_OBJECTS=$(EFI_COMMON_LIB_OBJECTS)\
$$(BUILD_DIR)\$(EfiCommonLib_DIR)\EfiCopyMem.obj\
$$(BUILD_DIR)\$(EfiCommonLib_DIR)\EfiSetMem.obj\
$$(BUILD_DIR)\$(EfiCommonLib_DIR)\EfiZeroMem.obj\
$$(BUILD_DIR)\$(EfiCommonLib_DIR)\Math.obj
!ENDIF

$(EFICOMMONLIB) : EfiCommonLib

EfiCommonLib : $(BUILD_DIR)\EfiCommonLib.mak EfiCommonLibBin

$(BUILD_DIR)\EfiCommonLib.mak : $(EfiCommonLib_DIR)\$(@B).cif $(EfiCommonLib_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(EfiCommonLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

EfiCommonLibBin : $(EDKFRAMEWORKGUIDLIB) $(COMPILERSTUB)
!IF "$(PROCESSOR)"=="x64"
	$(MAKE) /$(MAKEFLAGS) $(EDK_DEFAULTS)\
		/f $(BUILD_DIR)\EfiCommonLib.mak all\
		"MY_INCLUDES=/I$(EDK_SOURCE)\Foundation\Framework\Ppi\CpuIo" \
		TYPE=LIBRARY "OBJECTS=$(EFI_COMMON_LIB_DXE_OBJECTS)"
	$(MAKE) /$(MAKEFLAGS) $(EDK_DEFAULTS) BUILD_DIR=$(BUILD_DIR)\IA32\
		/f $(BUILD_DIR)\EfiCommonLib.mak all\
		"MY_INCLUDES=/I$(EDK_SOURCE)\Foundation\Framework\Ppi\CpuIo" \
		TYPE=PEI_LIBRARY "OBJECTS=$(EFI_COMMON_LIB_PEI_OBJECTS)"
!ELSE
	$(MAKE) /$(MAKEFLAGS) $(EDK_DEFAULTS)\
		/f $(BUILD_DIR)\EfiCommonLib.mak all\
		"MY_INCLUDES=/I$(EDK_SOURCE)\Foundation\Framework\Ppi\CpuIo" \
		TYPE=LIBRARY "OBJECTS=$(EFI_COMMON_LIB_OBJECTS)"
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