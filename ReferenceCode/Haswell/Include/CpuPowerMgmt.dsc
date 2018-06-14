## @file
#  Build description file for building the power management ACPI tables
#
#@copyright
#  Copyright (c)  1999 - 2012 Intel Corporation. All rights reserved
#  This software and associated documentation (if any) is furnished
#  under a license and may only be used or copied in accordance
#  with the terms of the license. Except as permitted by such
#  license, no part of this software or documentation may be
#  reproduced, stored in a retrieval system, or transmitted in any
#  form or by any means without the express written consent of
#  Intel Corporation.
#
#  This file contains an 'Intel Peripheral Driver' and uniquely
#  identified as "Intel Reference Module" and is
#  licensed for Intel CPUs and chipsets under the terms of your
#  license agreement with Intel or your vendor.  This file may
#  be modified by the user, subject to additional terms of the
#  license agreement
#

[=============================================================================]
#
# Instructions for building the power management ACPI table storage file
#
[=============================================================================]
[Build.Ia32.ACPITABLE,Build.x64.ACPITABLE]
#
# Check if we have any source to work with.
#
!IFNDEF SECTIONS
!IFNDEF ASL_FILES
!ERROR No ASL source files to build were defined in the INF file
!ENDIF
!ENDIF

#
# Define some macros to simplify changes
#
TARGET_FFS_FILE   = $(BIN_DIR)\$(FILE_GUID)-$(BASE_NAME).ffs

#
# Build CST SSDT sections for processor 0
#
$(DEST_DIR)\SsdtCpu0Cst.sec : $(ASL_SOURCE_FILES) $(ASL_FILES)
    $(ASL) $(ASL_FLAGS) $(DEST_DIR)\Ssdt\Cpu0Cst.asl
    -copy $(DEST_DIR)\Ssdt\Cpu0Cst.aml $(DEST_DIR)\SsdtCpu0Cst.acpi
    $(GENSECTION) -I $(DEST_DIR)\SsdtCpu0Cst.acpi -O $(DEST_DIR)\SsdtCpu0Cst.sec -S EFI_SECTION_RAW

#
# Build IST SSDT sections for processor 0
#
$(DEST_DIR)\SsdtCpu0Ist.sec : $(ASL_SOURCE_FILES) $(ASL_FILES)
    $(ASL) $(ASL_FLAGS) $(DEST_DIR)\Ssdt\Cpu0Ist.asl
    -copy $(DEST_DIR)\Ssdt\Cpu0Ist.aml $(DEST_DIR)\SsdtCpu0Ist.acpi
    $(GENSECTION) -I $(DEST_DIR)\SsdtCpu0Ist.acpi -O $(DEST_DIR)\SsdtCpu0Ist.sec -S EFI_SECTION_RAW
    
#
# Build TST SSDT sections for processor 0
#
$(DEST_DIR)\SsdtCpu0Tst.sec : $(ASL_SOURCE_FILES) $(ASL_FILES)
    $(ASL) $(ASL_FLAGS) $(DEST_DIR)\Ssdt\Cpu0Tst.asl
    -copy $(DEST_DIR)\Ssdt\Cpu0Tst.aml $(DEST_DIR)\SsdtCpu0Tst.acpi
    $(GENSECTION) -I $(DEST_DIR)\SsdtCpu0Tst.acpi -O $(DEST_DIR)\SsdtCpu0Tst.sec -S EFI_SECTION_RAW
    
    
#
# Build CST SSDT sections for processor 1
#
$(DEST_DIR)\SsdtApCst.sec : $(ASL_SOURCE_FILES) $(ASL_FILES)
    $(ASL) $(ASL_FLAGS) $(DEST_DIR)\Ssdt\ApCst.asl
    -copy $(DEST_DIR)\Ssdt\ApCst.aml $(DEST_DIR)\SsdtApCst.acpi
    $(GENSECTION) -I $(DEST_DIR)\SsdtApCst.acpi -O $(DEST_DIR)\SsdtApCst.sec -S EFI_SECTION_RAW

#
# Build IST SSDT sections for processor 1
#
$(DEST_DIR)\SsdtApIst.sec : $(ASL_SOURCE_FILES) $(ASL_FILES)
    $(ASL) $(ASL_FLAGS) $(DEST_DIR)\Ssdt\ApIst.asl
    -copy $(DEST_DIR)\Ssdt\ApIst.aml $(DEST_DIR)\SsdtApIst.acpi
    $(GENSECTION) -I $(DEST_DIR)\SsdtApIst.acpi -O $(DEST_DIR)\SsdtApIst.sec -S EFI_SECTION_RAW

#
# Build TST SSDT sections for processor 1
#
$(DEST_DIR)\SsdtApTst.sec : $(ASL_SOURCE_FILES) $(ASL_FILES)
    $(ASL) $(ASL_FLAGS) $(DEST_DIR)\Ssdt\ApTst.asl
    -copy $(DEST_DIR)\Ssdt\ApTst.aml $(DEST_DIR)\SsdtApTst.acpi
    $(GENSECTION) -I $(DEST_DIR)\SsdtApTst.acpi -O $(DEST_DIR)\SsdtApTst.sec -S EFI_SECTION_RAW

#
# Build SSDT sections for processor power management
#
$(DEST_DIR)\SsdtCpuPm.sec : $(ASL_SOURCE_FILES) $(ASL_FILES)
    $(ASL) $(ASL_FLAGS) $(DEST_DIR)\Ssdt\CpuPm.asl
    -copy $(DEST_DIR)\Ssdt\CpuPm.aml $(DEST_DIR)\SsdtCpuPm.acpi
    $(GENSECTION) -I $(DEST_DIR)\SsdtCpuPm.acpi -O $(DEST_DIR)\SsdtCpuPm.sec -S EFI_SECTION_RAW

#
# Build SSDT sections for processor power management
#
$(DEST_DIR)\SsdtCtdp.sec : $(ASL_SOURCE_FILES) $(ASL_FILES)
    $(ASL) $(ASL_FLAGS) $(DEST_DIR)\Ssdt\Ctdp.asl
    -copy $(DEST_DIR)\Ssdt\Ctdp.aml $(DEST_DIR)\SsdtCtdp.acpi
    $(GENSECTION) -I $(DEST_DIR)\SsdtCtdp.acpi -O $(DEST_DIR)\SsdtCtdp.sec -S EFI_SECTION_RAW

#
# Build LakeTiny SSDT sections for processor power management
#
$(DEST_DIR)\SsdtLakeTiny.sec : $(ASL_SOURCE_FILES) $(ASL_FILES)
    $(ASL) $(ASL_FLAGS) $(DEST_DIR)\Ssdt\LakeTiny.asl
    -copy $(DEST_DIR)\Ssdt\LakeTiny.aml $(DEST_DIR)\SsdtLakeTiny.acpi
    $(GENSECTION) -I $(DEST_DIR)\SsdtLakeTiny.acpi -O $(DEST_DIR)\SsdtLakeTiny.sec -S EFI_SECTION_RAW

#
# Build FFS file
#
$(TARGET_FFS_FILE) : $(SECTIONS) $(DEST_DIR)\SsdtCpu0Cst.sec $(DEST_DIR)\SsdtCpu0Ist.sec $(DEST_DIR)\SsdtCpu0Tst.sec $(DEST_DIR)\SsdtApCst.sec $(DEST_DIR)\SsdtApIst.sec $(DEST_DIR)\SsdtApTst.sec $(DEST_DIR)\SsdtCpuPm.sec $(DEST_DIR)\SsdtCtdp.sec $(DEST_DIR)\SsdtLakeTiny.sec
  $(GENFFSFILE) -B $(DEST_DIR) -P1 $(DEST_DIR)\$(BASE_NAME).pkg -V

all : $(TARGET_FFS_FILE)

[=============================================================================]
[Package.ACPITABLE.Default]
PACKAGE.INF
\[.]
BASE_NAME                   = $(BASE_NAME)
FFS_FILEGUID                = $(FILE_GUID)
FFS_FILETYPE                = EFI_FV_FILETYPE_FREEFORM
FFS_ATTRIB_CHECKSUM         = TRUE

IMAGE_SCRIPT =
{
  Compress (Dummy) {
    $(DEST_DIR)\SsdtCpu0Cst.sec
    $(DEST_DIR)\SsdtCpu0Ist.sec
    $(DEST_DIR)\SsdtCpu0Tst.sec
    $(DEST_DIR)\SsdtApCst.sec
    $(DEST_DIR)\SsdtApIst.sec
    $(DEST_DIR)\SsdtApTst.sec
    $(DEST_DIR)\SsdtCpuPm.sec
    $(DEST_DIR)\SsdtCtdp.sec
    $(DEST_DIR)\SsdtLakeTiny.sec    
  }
}
