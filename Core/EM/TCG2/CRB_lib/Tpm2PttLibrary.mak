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
Tpm2PttLibrary_Lib : $(BUILD_DIR)\Tpm2PttLibrary.mak Tpm2PttDxeLibBin Tpm2PttPeiLibBin
$(BUILD_DIR)\Tpm2PttLibrary.lib: Tpm2PttLibrary_Lib
$(BUILD_DIR)\IA32\Tpm2PttLibrary.lib: Tpm2PttLibrary_Lib

$(BUILD_DIR)\Tpm2PttLibrary.mak : $(Tpm2PttLibrary_DIR)\Tpm2PttLibrary.cif $(Tpm2PttLibrary_DIR)\Tpm2PttLibrary.mak $(BUILD_RULES)
    $(CIF2MAK) $(Tpm2PttLibrary_DIR)\Tpm2PttLibrary.cif $(CIF2MAK_DEFAULTS)

LIB_CFLAGS=$(CFLAGS)\
    /I$(TPM20_CRBLIB)\
    /I$(TCG_DIR)\Common\
    /I$(Tpm2PttLibrary_DIR)\
    /I$(TCG_DIR)\

Tpm2PttDxeLibBin : 
        $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
        /f $(BUILD_DIR)\Tpm2PttLibrary.mak all \
        "CFLAGS=$(LIB_CFLAGS) "\
        LIBRARY_NAME=$(BUILD_DIR)\Tpm2PttLibrary.lib\
        TYPE=LIBRARY 


Tpm2PttPeiLibBin : 
        $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)  BUILD_DIR=$(BUILD_DIR)\IA32\
        /f $(BUILD_DIR)\Tpm2PttLibrary.mak all \
        "CFLAGS=$(LIB_CFLAGS) "\
        TYPE=PEI_LIBRARY 


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
