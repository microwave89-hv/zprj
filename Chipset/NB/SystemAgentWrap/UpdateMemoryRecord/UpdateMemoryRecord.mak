# /*++
# Copyright (c) 2011 Intel Corporation. All rights reserved.
# This software and associated documentation (if any) is furnished
# under a license and may only be used or copied in accordance
# with the terms of the license. Except as permitted by such
# license, no part of this software or documentation may be
# reproduced, stored in a retrieval system, or transmitted in any
# form or by any means without the express written consent of
# Intel Corporation.
# --*/
all : UpdateMemoryRecord

UpdateMemoryRecord : $(BUILD_DIR)\UpdateMemoryRecord.mak UpdateMemoryRecordBin

$(BUILD_DIR)\UpdateMemoryRecord.mak : $(UpdateMemroyRecord_DIR)\UpdateMemoryRecord.CIF $(UpdateMemroyRecord_DIR)\$(@B).mak $(BUILD_RULES)
       $(CIF2MAK) $(UpdateMemroyRecord_DIR)\UpdateMemoryRecord.CIF $(CIF2MAK_DEFAULTS)

MemoryRecord_INCLUDES =  \
                         $(EDK_INCLUDES)\
                         $(INTEL_MCH_INCLUDES) \
                         /I$(SMBIOSUpdateData_DIR)\
                         /I$(UefiEfiIfrSupportLib_DIR)\
                         /I$(PROJECT_DIR)\
                         /IInclude\

MemoryRecord_LIB_LINKS =\
               $(EFIDRIVERLIB)\
!IF $(EFI_SPECIFICATION_VERSION) >= 0x2000A
               $(UEFIEFIIFRSUPPORTLIB)
!ELSE
               $(EFIIFRSUPPORTLIB)\
!ENDIF
                       
UpdateMemoryRecordBin : $(MemoryRecord_LIB_LINKS)
       $(MAKE) /$(MAKEFLAGS) $(EDK_DEFAULTS)\
               /f $(BUILD_DIR)\UpdateMemoryRecord.mak all\
               NAME=UpdateMemoryRecord\
               "MY_INCLUDES=$(MemoryRecord_INCLUDES)"\
               GUID=24CCD374-3DF6-4181-86F6-E3C66920A145\
               ENTRY_POINT=SMIBiosUpdateMemoryRecordDriverEntryPoint\
               DEPEX1=$(UpdateMemroyRecord_DIR)\UpdateMemoryRecord.dxs \
               DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX \
               TYPE=BS_DRIVER\
               COMPRESS=1\
