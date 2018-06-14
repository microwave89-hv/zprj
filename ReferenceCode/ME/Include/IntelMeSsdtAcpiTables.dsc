## @file
#  Build description file for building the ME SSDT ACPI tables
#
#@copyright
#  Copyright (c)  2012 Intel Corporation. All rights reserved
#  This software and associated documentation (if any) is furnished
#  under a license and may only be used or copied in accordance
#  with the terms of the license. Except as permitted by such
#  license, no part of this software or documentation may be
#  reproduced, stored in a retrieval system, or transmitted in any
#  form or by any means without the express written consent of
#  Intel Corporation.
#
#  This file contains a 'Sample Driver' and is licensed as such
#  under the terms of your license agreement with Intel or your
#  vendor.  This file may be modified by the user, subject to
#  the additional terms of the license agreement
#

[=============================================================================]
#
# Instructions for building the ME SSDT ACPI table storage file
#
[=============================================================================]
[Build.Ia32.ME_SSDT_ACPITABLE,Build.x64.ME_SSDT_ACPITABLE]
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

$(DEST_DIR)\MeSsdt.sec : $(ASL_SOURCE_FILES) $(ASL_FILES)
    $(ASL) $(ASL_FLAGS) $(DEST_DIR)\MeSsdt.asl
    -copy $(DEST_DIR)\MeSsdt.aml $(DEST_DIR)\MeSsdt.acpi
    $(GENSECTION) -I $(DEST_DIR)\MeSsdt.acpi -O $(DEST_DIR)\MeSsdt.sec -S EFI_SECTION_RAW

#
# Build FFS file
#
$(TARGET_FFS_FILE) : $(SECTIONS) $(DEST_DIR)\MeSsdt.sec
  $(GENFFSFILE) -B $(DEST_DIR) -P1 $(DEST_DIR)\$(BASE_NAME).pkg -V

all : $(TARGET_FFS_FILE)

[=============================================================================]
[Package.ME_SSDT_ACPITABLE.Default]
PACKAGE.INF
\[.]
BASE_NAME                   = $(BASE_NAME)
FFS_FILEGUID                = $(FILE_GUID)
FFS_FILETYPE                = EFI_FV_FILETYPE_FREEFORM
FFS_ATTRIB_CHECKSUM         = TRUE

IMAGE_SCRIPT =
{
  Compress (Dummy) {
    $(DEST_DIR)\MeSsdt.sec
  }
}
