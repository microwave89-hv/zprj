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
# MAK file for the ModulePart:AmtLibPei
all : AmtLibPei

$(BUILD_DIR)\AmtLibPei.lib : AmtLibPei

AmtLibPei : $(BUILD_DIR)\AmtLibPei.mak AmtLibPeiBin

$(BUILD_DIR)\AmtLibPei.mak : $(AmtLibPei_DIR)\$(@B).cif $(AmtLibPei_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(AmtLibPei_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

AmtLibPei_INCLUDES=\
	$(EDK_INCLUDES) \
	$(EdkIIGlueLib_INCLUDES)\
	$(ME_INCLUDES) \

AmtLibPei_DEFINES=\
  /D __EDKII_GLUE_PEI_SERVICES_LIB__

AmtLibPei_LIBS=\
   $(EdkIIGluePeiServicesLib_LIB)\
   
AmtLibPeiBin :  $(AmtLibPei_LIBS) $(MeLibPei_LIBS)
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS) \
		/f $(BUILD_DIR)\AmtLibPei.mak all \
		"MY_INCLUDES=$(AmtLibPei_INCLUDES)" \
		"CFLAGS=$(CFLAGS) $(AmtLibPei_DEFINES)"\
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
