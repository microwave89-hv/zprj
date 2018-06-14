# /*++
# Copyright (c) 2009 Intel Corporation. All rights reserved.
# This software and associated documentation (if any) is furnished
# under a license and may only be used or copied in accordance
# with the terms of the license. Except as permitted by such
# license, no part of this software or documentation may be
# reproduced, stored in a retrieval system, or transmitted in any
# form or by any means without the express written consent of
# Intel Corporation.
# --*/
# MAK file for the ModulePart:AtDxeLib
all : PttDxeLib PttPeiLib


$(BUILD_DIR)\PttDxeLibrary.lib : PttDxeLib

PttDxeLib : $(BUILD_DIR)\PttLibrary.mak PttDxeLibBin

PttDxeLib_INCLUDES=\
  $(EDK_INCLUDES) \
  $(EdkIIGlueLib_INCLUDES) \
  $(ME_INCLUDES) \
  -IReferenceCode\ME\SampleCode\Include\IndustryStandard\

PttDxeLib_DEFINES=\
  -D __EDKII_GLUE_BASE_LIB__ \
  -D __EDKII_GLUE_UEFI_LIB__ \
  -D __EDKII_GLUE_BASE_MEMORY_LIB__ \
  -D __EDKII_GLUE_BASE_IO_LIB_INTRINSIC__ \
  -D __EDKII_GLUE_DXE_DEBUG_LIB_REPORT_STATUS_CODE__ \
  -D TIANO_RELEASE_VERSION=0x00080006\
  -D PTT_FLAG

$(BUILD_DIR)\PttLibrary.mak : $(MePttLibrary_DIR)\Common\PttHciDeviceLib.cif $(MePttLibrary_DIR)\PttLibrary.mak $(BUILD_RULES)
	$(CIF2MAK) $(MePttLibrary_DIR)\Common\PttHciDeviceLib.cif $(CIF2MAK_DEFAULTS)

PttDxeLib_LIBS=\
  $(EdkIIGlueBaseLib_LIB)\
  $(EdkIIGlueUefiLib_LIB)\
  $(EdkIIGlueBaseMemoryLib_LIB)\
  $(EdkIIGlueBaseIoLibIntrinsic_LIB)\
  $(EdkIIGlueBaseTimerLibLocalApic_LIB)\
  $(EdkIIGlueDxeDebugLibReportStatusCode_LIB)\

PttDxeLibBin : $(PttDxeLib_LIBS)
        $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS) \
        MAKEFILE=$(BUILD_DIR)\PttLibrary.mak \
        /f $(BUILD_DIR)\PttLibrary.mak all \
        "MY_INCLUDES=$(PttDxeLib_INCLUDES)" \
        "MY_DEFINES=$(PttDxeLib_DEFINES)"\
        LIBRARY_NAME=$(BUILD_DIR)\PttDxeLibrary.lib\
        TYPE=LIBRARY \

$(BUILD_DIR)\PttPeiLibrary.lib : PttPeiLib

PttPeiLib : $(BUILD_DIR)\PttLibrary.mak PttPeiLibBin

PttPeiLib_DEFINES=\
  -D __EDKII_GLUE_BASE_LIB__ \
  -D __EDKII_GLUE_UEFI_LIB__ \
  -D __EDKII_GLUE_BASE_MEMORY_LIB__ \
  -D __EDKII_GLUE_BASE_IO_LIB_INTRINSIC__ \
  -D __EDKII_GLUE_PEI_DEBUG_LIB_REPORT_STATUS_CODE__ \
  -D TIANO_RELEASE_VERSION=0x00080006\
  -D PTT_FLAG

PttPeiLib_LIBS=\
  $(EdkIIGlueBaseLib_LIB)\
  $(EdkIIGlueUefiLib_LIB)\
  $(EdkIIGlueBaseMemoryLib_LIB)\
  $(EdkIIGlueBaseIoLibIntrinsic_LIB)\
  $(EdkIIGlueBaseTimerLibLocalApic_LIB)\
  $(EdkIIGluePeiDebugLibReportStatusCode_LIB)\

PttPeiLibBin : $(PttPeiLib_LIBS)
!IF "$(x64_BUILD)"=="1" 
        $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS) BUILD_DIR=$(BUILD_DIR)\IA32\
!ELSE
        $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
!ENDIF
        MAKEFILE=$(BUILD_DIR)\PttLibrary.mak \
        /f $(BUILD_DIR)\PttLibrary.mak all \
        "MY_INCLUDES=$(PttDxeLib_INCLUDES)" \
        "MY_DEFINES=$(PttPeiLib_DEFINES)"\
        LIBRARY_NAME=$(BUILD_DIR)\PttPeiLibrary.lib\
        TYPE=PEI_LIBRARY \


#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2006, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************
