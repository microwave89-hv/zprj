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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/EfiRuntimeLib/EfiRuntimeLib.mak 1     1/20/12 4:12a Jeffch $
#
# $Revision: 1 $
#
# $Date: 1/20/12 4:12a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/EfiRuntimeLib/EfiRuntimeLib.mak $
# 
# 1     1/20/12 4:12a Jeffch
# Create Intel EDK 1117 Patch 7.
# 
# 1     9/27/11 6:34a Wesleychen
# Intel EDK initially releases.
# 
# 3     12/03/09 4:29a Iminglin
# Change "ArchProtocolLib" to "ARCHPROTOCOL".
# 
# 2     9/02/09 4:00a Iminglin
# EIP24919
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	EfiRuntimeLib.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************
$(EFIRUNTIMELIB) : EfiRuntimeLib

EFIRUNTIMELIB_OBJECTS=\
$(BUILD_DIR)\$(EfiRuntimeLib_DIR)\Debug.obj\
$(BUILD_DIR)\$(EfiRuntimeLib_DIR)\Event.obj\
$(BUILD_DIR)\$(EfiRuntimeLib_DIR)\Io.obj\
$(BUILD_DIR)\$(EfiRuntimeLib_DIR)\LibGlobals.obj\
$(BUILD_DIR)\$(EfiRuntimeLib_DIR)\GetImage.obj\
$(BUILD_DIR)\$(EfiRuntimeLib_DIR)\RtDevicePath.obj\
$(BUILD_DIR)\$(EfiRuntimeLib_DIR)\$(PROCESSOR)\RuntimeLib.obj
!IF "$(PROCESSOR)"=="IA32"
EFIRUNTIMELIB_OBJECTS=$(EFIRUNTIMELIB_OBJECTS)\
$(BUILD_DIR)\$(EfiRuntimeLib_DIR)\Ia32\Fvb.obj\
$(BUILD_DIR)\$(EfiRuntimeLib_DIR)\Ia32\Lock.obj\
$(BUILD_DIR)\$(EfiRuntimeLib_DIR)\Ia32\IoLib.obj\
$(BUILD_DIR)\$(EfiRuntimeLib_DIR)\Ia32\PlatformIoLib.obj
!ELSEIF "$(PROCESSOR)"=="x64"
EFIRUNTIMELIB_OBJECTS=$(EFIRUNTIMELIB_OBJECTS)\
$(BUILD_DIR)\$(EfiRuntimeLib_DIR)\x64\Fvb.obj\
$(BUILD_DIR)\$(EfiRuntimeLib_DIR)\x64\Lock.obj\
$(BUILD_DIR)\$(EfiRuntimeLib_DIR)\x64\IoLib.obj\
$(BUILD_DIR)\$(EfiRuntimeLib_DIR)\x64\PlatformIoLib.obj\
$(BUILD_DIR)\$(EfiRuntimeLib_DIR)\x64\RuntimeLibAsm.obj
!ELSEIF "$(PROCESSOR)"=="IPF"
EFIRUNTIMELIB_OBJECTS=$(EFIRUNTIMELIB_OBJECTS)\
$(BUILD_DIR)\$(EfiRuntimeLib_DIR)\Ipf\Fvb.obj\
$(BUILD_DIR)\$(EfiRuntimeLib_DIR)\Ipf\Lock.obj\
$(BUILD_DIR)\$(EfiRuntimeLib_DIR)\Ipf\EsalLib.s\
$(BUILD_DIR)\$(EfiRuntimeLib_DIR)\Ipf\IpfCpuCache.s
!ENDIF

$(BUILD_DIR)\EfiRuntimeLib.lib : EfiRuntimeLib

EfiRuntimeLib : $(BUILD_DIR)\EfiRuntimeLib.mak EfiRuntimeLibBin

$(BUILD_DIR)\EfiRuntimeLib.mak : $(EfiRuntimeLib_DIR)\$(@B).cif $(EfiRuntimeLib_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(EfiRuntimeLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

EfiRuntimeLibBin : $(EFIGUIDLIB) $(EDKGUIDLIB) $(EDKPROTOCOLLIB) $(EDKFRAMEWORKPROTOCOLLIB) $(ARCHPROTOCOLLIB) $(EFICOMMONLIB) $(EFIPROTOCOLLIB)
	$(MAKE) /$(MAKEFLAGS) $(EDK_DEFAULTS)\
		/f $(BUILD_DIR)\EfiRuntimeLib.mak all\
		TYPE=LIBRARY "OBJECTS=$(EFIRUNTIMELIB_OBJECTS)"
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