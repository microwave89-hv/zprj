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
# MAK file for the ModulePart:MeLibDxe
all : MeLibDxe

$(BUILD_DIR)\MeLibDxe.lib : MeLibDxe

MeLibDxe : $(BUILD_DIR)\MeLibDxe.mak MeLibDxeBin

$(BUILD_DIR)\MeLibDxe.mak : $(MeLibDxe_DIR)\$(@B).cif $(MeLibDxe_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(MeLibDxe_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

MeLibDxe_INCLUDES=\
  $(EDK_INCLUDES) \
  $(EdkIIGlueLib_INCLUDES) \
  $(ME_INCLUDES) \
  -I$(INTEL_COUGAR_POINT_DIR)\
  $(INTEL_PCH_INCLUDES)

MeLibDxe_DEFINES=\
  $(MY_DEFINES)/D __EDKII_GLUE_BASE_MEMORY_LIB__\
  /D __EDKII_GLUE_EDK_DXE_RUNTIME_DRIVER_LIB__\
  /D __EDKII_GLUE_UEFI_BOOT_SERVICES_TABLE_LIB__\
  /D __EDKII_GLUE_BASE_PCI_LIB_PCI_EXPRESS__	

MeLibDxe_LIBS=\
  $(MeProtocolLib_LIB)\
  $(EdkIIGlueBasePciLibPciExpress_LIB)\
  $(COMPILERSTUB)\
  $(EdkIIGlueSmmFirmwarePerformanceLib_LIB)\
  $(EDKFRAMEWORKGUIDLIB)\
  

MeLibDxeBin : $(MeLibDxe_LIBS)
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS) \
		/f $(BUILD_DIR)\MeLibDxe.mak all \
		"MY_INCLUDES=$(MeLibDxe_INCLUDES)" \
		"MY_DEFINES=$(MeLibDxe_DEFINES)"\
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
