#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
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
# $Header: /Alaska/BIN/Modules/StatusCode/StatusCode.mak 17    10/07/10 4:39p Oleksiyy $
#
# $Revision: 17 $
#
# $Date: 10/07/10 4:39p $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Modules/StatusCode/StatusCode.mak $
# 
# 17    10/07/10 4:39p Oleksiyy
# Minor fix of StatusCodeRuntime support.
# 
# 16    10/06/10 4:31p Oleksiyy
# Issue Number:  39752 
# 
# Category:  Improvement
# 
# Description:  Runtime Staus Code support is added.
# 
# Files:  Uart1.asl, Tokens.c, Runtime.c, GenericSio.c, EfiLib.c,
# CsmLib.c, AmiDxeLib.h and StatusCode eModule.
# 
# 15    3/05/09 1:41p Felixp
# Major update of the StatusCode module. 
# See Label Comments and Release Notes in StatusCode.chm for more
# details.
# 
# 14    4/22/08 5:56p Felixp
# Bug fix (project did not compile in IA32 mode).
# 
# 8     3/06/08 4:12p Felixp
# Differences in IA32 and x64 build rules has been removed.
# 
# 6     4/20/07 5:10p Felixp
# Updated to use new Status Code infrastructure
# 
# 2     6/16/05 11:10a Felixp
# module reallocated to RAM once it is available
# 
# 22    6/08/05 5:59p Felixp
# Beep Codes added
# SerialStatusCode.c moved to StatusCode component
# 
# 21    6/07/05 7:23p Felixp
# Moving toward generic Status Code module
# 
# 20    1/18/05 3:21p Felixp
# PrintDebugMessage renamed to Trace
# 
# 19    11/01/04 8:44a Felixp
# 
# 18    10/22/04 10:24a Felixp
# Status Code updated to use PEIM_HOB to pass status code pointer to DXE
# 
# 17    9/21/04 10:50a Robert
# added standard library support in the build process
# 
# 16    7/13/04 10:42a Felixp
# 
# 15    4/10/04 2:17p Felixp
# 
# 14    4/09/04 11:49a Robert
# Adding string support for displaying, Type, Severity, Class, and
# SubClass for unknown error types
# 
# 13    4/07/04 5:21p Robert
# fixed up DXE part of status Code Protocol, the mak file should now make
# the available to both DXE and PEI.  In addition, it should add a
# dependency expression
# 
# 12    3/29/04 12:41p Markw
# Moved EfiStatusCode.h into include component. Deleted this reference in
# makefile.
# 
# 4     2/06/04 2:46a Felixp
#  - Support for VC6 tools
#  - bug fixes
# - component AddOn added
# 
# 2     1/18/04 8:32a Felixp
# From now on, OBJ files are created in a component specific subdirectory
# of $(BUILD_DIR)
# 
# 1     1/15/04 5:18p Robert
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	StatusCode.mak
#
# Description: 
#       Builds PEI and DXE StatusCode modules.
#       Two libraries StatusCodePei.lib and StatusCodeDxe.lib 
#       are built and these are linked with CORE_PEI and CORE_DXE
#       respectively.
#
#<AMI_FHDR_END>
#**********************************************************************
all : StatusCode

STATUS_CODE_COMMON_OBJECTS=\
$$(BUILD_DIR)\$(STATUS_CODE_DIR)\StatusCodeCommon.obj\
$$(BUILD_DIR)\$(STATUS_CODE_DIR)\StatusCodeMap.obj\
$$(BUILD_DIR)\$(STATUS_CODE_DIR)\SerialStatusCode.obj\

STATUS_CODE_PEI_OBJECTS=\
$(STATUS_CODE_COMMON_OBJECTS)\
$$(BUILD_DIR)\$(STATUS_CODE_DIR)\StatusCodePei.obj

STATUS_CODE_DXE_OBJECTS=\
$(STATUS_CODE_COMMON_OBJECTS)\
$(BUILD_DIR)\$(STATUS_CODE_DIR)\StatusCodeDxe.obj

STATUS_CODE_RUNTIME_OBJECTS=\
$(BUILD_DIR)\$(STATUS_CODE_DIR)\StatusCodeRuntime.obj

STATUS_CODE_EXT_HEADERS=\
$(BUILD_DIR)\token.h\
$(BUILD_DIR)\StatusCodeELinks.h

StatusCode : StatusCodePei StatusCodeDxe StatusCodeRuntime

StatusCodePei : $(BUILD_DIR)\StatusCodeELinks.h StatusCodePeiBin
StatusCodeDxe : $(BUILD_DIR)\StatusCodeELinks.h StatusCodeDxeBin
StatusCodeRuntime : $(BUILD_DIR)\StatusCodeELinks.h StatusCodeRuntimeBin

$(BUILD_DIR)\StatusCode.mak : $(STATUS_CODE_DIR)\$(@B).cif $(STATUS_CODE_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(STATUS_CODE_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

CORE_PEIBin : $(BUILD_DIR)\StatusCodePei.lib
CORE_DXEBin : $(BUILD_DIR)\StatusCodeDxe.lib
RUNTIMEBin : $(BUILD_DIR)\StatusCodeRuntime.lib

$(BUILD_DIR)\StatusCodePei.lib : StatusCodePei
$(BUILD_DIR)\StatusCodeDxe.lib : StatusCodeDxe
$(BUILD_DIR)\StatusCodeRuntime.lib : StatusCodeRuntime

$(BUILD_DIR)\StatusCodeELinks.h : $(BUILD_DIR)\token.h $(BUILD_DIR)\StatusCode.mak
    $(ECHO) #define INIT_LIST $(StatusCodeInitialize) > $@
    $(ECHO) #define STRING_LIST $(ReportStringStatus) >> $@
    $(ECHO) #define SIMPLE_LIST $(ReportSimpleStatus) >> $@
    $(ECHO) #define MISC_LIST $(ReportMiscStatus) >> $@
    $(ECHO) #define CHECKPOINT_LIST $(ReportCheckpoint) >> $@
    $(ECHO) #define PEI_ERROR_CODE_ACTIONS $(PeiErrorCodeActions) >> $@
    $(ECHO) #define DXE_ERROR_CODE_ACTIONS $(DxeErrorCodeActions) >> $@

StatusCodePeiBin : $(AMIPEILIB)
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\StatusCode.mak all\
		BUILD_DIR=$(BUILD_DIR)\IA32\
        "OBJECTS=$(STATUS_CODE_PEI_OBJECTS)"\
		"EXT_HEADERS=$(STATUS_CODE_EXT_HEADERS)"\
		"MY_DEFINES=/DPEI_STATUS_CODE"\
		TYPE=PEI_LIBRARY LIBRARY_NAME=$(BUILD_DIR)\StatusCodePei.lib

StatusCodeDxeBin: $(AMIDXELIB)
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\StatusCode.mak all\
        "OBJECTS=$(STATUS_CODE_DXE_OBJECTS)"\
		"EXT_HEADERS=$(STATUS_CODE_EXT_HEADERS)"\
		"MY_DEFINES=/DDXE_STATUS_CODE"\
		TYPE=LIBRARY LIBRARY_NAME=$(BUILD_DIR)\StatusCodeDxe.lib

StatusCodeRuntimeBin: $(BUILD_DIR)\StatusCodeDxe.lib
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\StatusCode.mak all\
        "OBJECTS=$(STATUS_CODE_RUNTIME_OBJECTS)"\
		"EXT_HEADERS=$(STATUS_CODE_EXT_HEADERS)"\
		"MY_DEFINES=/DRUNTIME_STATUS_CODE"\
		TYPE=LIBRARY LIBRARY_NAME=$(BUILD_DIR)\StatusCodeRuntime.lib

#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************
