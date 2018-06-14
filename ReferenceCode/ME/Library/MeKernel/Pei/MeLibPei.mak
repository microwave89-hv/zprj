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
# MAK file for the ModulePart:MeLibPei
all : MeLibPei

$(BUILD_DIR)\MeLibPei.lib : MeLibPei

MeLibPei : $(BUILD_DIR)\MeLibPei.mak MeLibPeiBin

$(BUILD_DIR)\MeLibPei.mak : $(MeLibPei_DIR)\$(@B).cif $(MeLibPei_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(MeLibPei_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

MeLibPei_INCLUDES=\
        $(EDK_INCLUDES) \
        $(EdkIIGlueLib_INCLUDES)\
        $(ME_INCLUDES) \
        /I$(NB_BOARD_DIR)\
        -I$(INTEL_COUGAR_POINT_DIR)\

MeLibPei_DEFINES=\
  /D __EDKII_GLUE_PEI_SERVICES_LIB__

MeLibPei_LIBS=\
   $(EdkIIGluePeiServicesLib_LIB)\
   $(MeLibPpi_LIB)
   
MeLibPeiBin :  $(MeLibPei_LIBS)
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS) \
		/f $(BUILD_DIR)\MeLibPei.mak all \
		"MY_INCLUDES=$(MeLibPei_INCLUDES)" \
		"CFLAGS=$(CFLAGS) $(MeLibPei_DEFINES)"\
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
