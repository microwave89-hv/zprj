## @file
#  Build description file for building ASL and ACT file types used in ACPI tables
#  You should not put platform details, like how to build DSDT, SSDT, or how to
#  package the ACPI tables into a data file in this build.  This should be platform 
#  neutral code only.
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
#  This file contains a 'Sample Driver' and is licensed as such
#  under the terms of your license agreement with Intel or your
#  vendor.  This file may be modified by the user, subject to
#  the additional terms of the license agreement
#

[=============================================================================]
[Compile.Ia32.act,Compile.x64.act]
#
# Instructions to create ACPI table sections out of ACPI table C source files.
#

#/*++
#
# If it already exists, then include the dependency list file for this
# source file. If it doesn't exist, then this is a clean build and the
# dependency file will get created below and the source file will get
# compiled. Don't do any of this if NO_MAKEDEPS is defined.
#
#--*/
!IF ("$(NO_MAKEDEPS)" == "")

!IF EXIST($(DEST_DIR)\$(FILE).dep)
!INCLUDE $(DEST_DIR)\$(FILE).dep
!ENDIF

#
# This is how to create the dependency file.
#
DEP_FILE = $(DEST_DIR)\$(FILE).dep

$(DEP_FILE) : $(SOURCE_FILE_NAME)
  $(MAKEDEPS) -ignorenotfound -f $(SOURCE_FILE_NAME) -q -target \
    $(DEST_DIR)\$(FILE).obj \
    -o $(DEP_FILE) $(INC)

!ENDIF

#
# Compile the file
#
$(DEST_DIR)\$(FILE).obj : $(SOURCE_FILE_NAME) $(INC_DEPS) $(DEP_FILE)
  $(CC) $(C_FLAGS) /TC $(SOURCE_FILE_NAME)

#
# Link it
#
$(DEST_DIR)\$(FILE).exe : $(DEST_DIR)\$(FILE).obj
  $(LINK) $(LINK_FLAGS_EXE) $(DEST_DIR)\$(FILE).obj /OUT:$(DEST_DIR)\$(FILE).exe /ENTRY:main

#
# Strip out the ACPI table
#
$(DEST_DIR)\$(FILE).acpi : $(DEST_DIR)\$(FILE).exe
  $(GENACPITABLE) $(DEST_DIR)\$(FILE).exe $(DEST_DIR)\$(FILE).acpi

#
# Create a section from the ACPI table
#
$(DEST_DIR)\$(FILE).sec : $(DEST_DIR)\$(FILE).acpi
  $(GENSECTION) -I $(DEST_DIR)\$(FILE).acpi -O $(DEST_DIR)\$(FILE).sec -S EFI_SECTION_RAW

#
# Add it to the targets to build
#
SECTIONS = $(SECTIONS) $(DEST_DIR)\$(FILE).sec

[=============================================================================]
[Compile.Ia32.asl,Compile.x64.asl]
#
# We run the ASL through the C Preprocessor to resolve definitions.
#
$(DEST_DIR)\$(FILE).asl : $(SOURCE_FILE_NAME)
  $(CC) $(ASL_CPP_FLAGS) /nologo /C /EP /TC $(INC) -oa $(SOURCE_FILE_NAME) > $(DEST_DIR)\$(FILE).asl

#
# Add it to the targets to build
#
ASL_FILES = $(ASL_FILES) $(DEST_DIR)\$(FILE).asl

