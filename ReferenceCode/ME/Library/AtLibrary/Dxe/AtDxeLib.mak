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
all : AtDxeLib

$(BUILD_DIR)\AtDxeLib.lib : AtDxeLib

AtDxeLib : $(BUILD_DIR)\AtDxeLib.mak AtDxeLibBin

$(BUILD_DIR)\AtDxeLib.mak : $(AtDxeLib_DIR)\$(@B).cif $(AtDxeLib_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(AtDxeLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

AtDxeLib_INCLUDES=\
  $(EDK_INCLUDES) \
  $(EdkIIGlueLib_INCLUDES) \
  $(ME_INCLUDES)\

AtDxeLib_DEFINES=\
  $(MY_DEFINES)\
  /D __EDKII_GLUE_BASE_MEMORY_LIB__\
  /D __EDKII_GLUE_EDK_DXE_RUNTIME_DRIVER_LIB__\
  /D __EDKII_GLUE_UEFI_BOOT_SERVICES_TABLE_LIB__\

AtDxeLib_LIBS=\
  $(MeProtocolLib_LIB)\
  $(MeLibDxe_LIB)

AtDxeLibBin : $(AtDxeLib_LIBS)
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS) \
		/f $(BUILD_DIR)\AtDxeLib.mak all \
		"MY_INCLUDES=$(AtDxeLib_INCLUDES)" \
		"MY_DEFINES=$(AtDxeLib_DEFINES)"\
		TYPE=LIBRARY \
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
