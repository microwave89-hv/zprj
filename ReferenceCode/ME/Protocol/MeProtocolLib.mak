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
# MAK file for the ModulePart:MeProtocolLib
all : MeProtocolLib

$(MeProtocolLib_LIB): MeProtocolLib

MeProtocolLib : $(BUILD_DIR)\MeProtocolLib.mak MeProtocolLibBin

$(BUILD_DIR)\MeProtocolLib.mak : $(MeProtocolLib_DIR)\$(@B).cif $(MeProtocolLib_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(MeProtocolLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

MeProtocolLib_INCLUDES=\
		$(EDK_INCLUDES) \
		$(EdkIIGlueLib_INCLUDES) \
		$(ME_INCLUDES)
		
MeProtocolLibBin : 
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		/f $(BUILD_DIR)\MeProtocolLib.mak all\
		"MY_INCLUDES=$(MeProtocolLib_INCLUDES)" \
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