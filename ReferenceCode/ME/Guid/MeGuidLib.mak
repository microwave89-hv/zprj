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
all : MeGuidLib

$(MeGuidLib_LIB) : MeGuidLib

MeGuidLib : $(BUILD_DIR)\MeGuidLib.mak MeGuidLibBin

$(BUILD_DIR)\MeGuidLib.mak : $(MeGuidLib_DIR)\$(@B).cif $(MeGuidLib_DIR)\$(@B).mak $(BUILD_RULES)
        $(CIF2MAK) $(MeGuidLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)


MeGuidLib_INCLUDES=\
		$(ME_INCLUDES)\
		$(EDK_INCLUDES)\
		$(EdkIIGlueLib_INCLUDES)\
                
MeGuidLibBin :  
        $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
                /f $(BUILD_DIR)\MeGuidLib.mak all\
                "MY_INCLUDES=$(MeGuidLib_INCLUDES)" \
                TYPE=LIBRARY
!IF "$(x64_BUILD)"=="1" 
        $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS) BUILD_DIR=$(BUILD_DIR)\IA32\
                /f $(BUILD_DIR)\MeGuidLib.mak all\
                "MY_INCLUDES=$(MeGuidLib_INCLUDES)" \
                TYPE=PEI_LIBRARY
!ENDIF		
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