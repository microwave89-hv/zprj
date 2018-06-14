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
# MAK file for the ModulePart:PowerManagementAcpiTables

#-----------------------------------------------------------------------
# ASL compiler definition
#-----------------------------------------------------------------------
MASL     = $(SILENT)asl.exe   # Microsoft ASL compiler
!IF "$(ACPIPLATFORM_ASL_COMPILER)"==""
!ERROR It is an invalid path, please check your ASL compiler path.
!ENDIF

IASL = $(ACPIPLATFORM_ASL_COMPILER)  
#-----------------------------------------------------------------------
ASL_COMPILER = IASL  # Default ASL compiler. Can be 'IASL' for Intel ASL and 'MASL' for Microsoft ASL compiler.
# Note. Msft. ASL compiler of version 1.0.14NT correctly process ACPI 2.0 extended ASL objects.
#-----------------------------------------------------------------------
EDK : PPMASL

ALLPPMSEC = $(BUILD_DIR)\CPUPM.sec\
  $(BUILD_DIR)\CPU0IST.sec\
  $(BUILD_DIR)\APIST.sec\
  $(BUILD_DIR)\CPU0TST.sec\
  $(BUILD_DIR)\APTST.sec\
  $(BUILD_DIR)\CPU0CST.sec\
  $(BUILD_DIR)\APCST.sec\
  $(BUILD_DIR)\LakeTiny.sec\
  $(BUILD_DIR)\Ctdp.sec

PPMASL:  $(BUILD_DIR)\PPMACPI.ffs

$(BUILD_DIR)\CPUPM.aml: $(INTEL_CPUPPM_ASL_FILE)
!if "$(ASL_COMPILER)" == "MASL"
  @$(MASL) /Fo=$@ $**
!elseif "$(ASL_COMPILER)" == "IASL"
  @cl /C /EP -I $(PROJECT_CPU_INCLUDES) $(INTEL_CPUPPM_ASL_FILE) > $(BUILD_DIR)\CpuPm.asl
  $(IASL) -p $(BUILD_DIR)\CPUPM.aml $(BUILD_DIR)\CpuPm.asl
!endif

$(BUILD_DIR)\CPU0IST.aml: $(INTEL_CPU0IST_ASL_FILE)
!if "$(ASL_COMPILER)" == "MASL"
  $(MASL) /Fo=$@ $**
!elseif "$(ASL_COMPILER)" == "IASL"
  @cl /C /EP -I $(PROJECT_CPU_INCLUDES) $(INTEL_CPU0IST_ASL_FILE) > $(BUILD_DIR)\Cpu0Ist.asl
  $(IASL) -p $(BUILD_DIR)\CPU0IST.aml $(BUILD_DIR)\Cpu0Ist.asl
!endif

$(BUILD_DIR)\APIST.aml: $(INTEL_APIST_ASL_FILE)
!if "$(ASL_COMPILER)" == "MASL"
  $(MASL) /Fo=$@ $**
!elseif "$(ASL_COMPILER)" == "IASL"
  $(IASL) -p $(BUILD_DIR)\APIST.aml $(INTEL_APIST_ASL_FILE)
!endif

$(BUILD_DIR)\CPU0CST.aml: $(INTEL_CPU0CST_ASL_FILE)
!if "$(ASL_COMPILER)" == "MASL"
  $(MASL) /Fo=$@ $**
!elseif "$(ASL_COMPILER)" == "IASL"
  @cl /C /EP $(PROJECT_CPU_INCLUDES) $(INTEL_CPU0CST_ASL_FILE) > $(BUILD_DIR)\Cpu0Cst.asl
  $(IASL) -p $(BUILD_DIR)\CPU0CST.aml $(BUILD_DIR)\Cpu0Cst.asl
!endif

$(BUILD_DIR)\CPU0TST.aml: $(INTEL_CPU0TST_ASL_FILE)
!if "$(ASL_COMPILER)" == "MASL"
  $(MASL) /Fo=$@ $**
!elseif "$(ASL_COMPILER)" == "IASL"
  @cl /C /EP $(PROJECT_CPU_INCLUDES) $(INTEL_CPU0TST_ASL_FILE) > $(BUILD_DIR)\Cpu0Tst.asl
  $(IASL) -p $(BUILD_DIR)\CPU0TST.aml $(BUILD_DIR)\Cpu0Tst.asl
!endif

$(BUILD_DIR)\APCST.aml: $(INTEL_APCST_ASL_FILE)
!if "$(ASL_COMPILER)" == "MASL"
  $(MASL) /Fo=$@ $**
!elseif "$(ASL_COMPILER)" == "IASL"
  $(IASL) -p $(BUILD_DIR)\APCST.aml $(INTEL_APCST_ASL_FILE)
!endif

$(BUILD_DIR)\CPU0TST.aml: $(INTEL_CPU0TST_ASL_FILE)
!if "$(ASL_COMPILER)" == "MASL"
  $(MASL) /Fo=$@ $**
!elseif "$(ASL_COMPILER)" == "IASL"
  $(IASL) -p $(BUILD_DIR)\CPU0TST.aml $(INTEL_CPU0TST_ASL_FILE)
!endif

$(BUILD_DIR)\APTST.aml: $(INTEL_APTST_ASL_FILE)
!if "$(ASL_COMPILER)" == "MASL"
  $(MASL) /Fo=$@ $**
!elseif "$(ASL_COMPILER)" == "IASL"
  $(IASL) -p $(BUILD_DIR)\ApTst.aml $(INTEL_APTST_ASL_FILE)
!endif

$(BUILD_DIR)\LakeTiny.aml: $(INTEL_LAKETINY_ASL_FILE)
!if "$(ASL_COMPILER)" == "MASL"
  $(MASL) /Fo=$@ $**
!elseif "$(ASL_COMPILER)" == "IASL"
  $(IASL) -p $(BUILD_DIR)\LakeTiny.aml $(INTEL_LAKETINY_ASL_FILE)
!endif

$(BUILD_DIR)\Ctdp.aml: $(INTEL_CTDP_ASL_FILE)
!if "$(ASL_COMPILER)" == "MASL"
  $(MASL) /Fo=$@ $**
!elseif "$(ASL_COMPILER)" == "IASL"
  $(IASL) -p $(BUILD_DIR)\Ctdp.aml $(INTEL_CTDP_ASL_FILE)
!endif

$(BUILD_DIR)\CPUPM.sec: $(BUILD_DIR)\CPUPM.aml
  $(GENSECTION) -I $** -O $@ -S EFI_SECTION_RAW

$(BUILD_DIR)\CPU0IST.sec: $(BUILD_DIR)\CPU0IST.aml
  $(GENSECTION) -I $** -O $@ -S EFI_SECTION_RAW

$(BUILD_DIR)\APIST.sec: $(BUILD_DIR)\APIST.aml
  $(GENSECTION) -I $** -O $@ -S EFI_SECTION_RAW

$(BUILD_DIR)\CPU0TST.sec: $(BUILD_DIR)\CPU0TST.aml
  $(GENSECTION) -I $** -O $@ -S EFI_SECTION_RAW

$(BUILD_DIR)\APTST.sec: $(BUILD_DIR)\APTST.aml
  $(GENSECTION) -I $** -O $@ -S EFI_SECTION_RAW

$(BUILD_DIR)\CPU0CST.sec: $(BUILD_DIR)\CPU0CST.aml
  $(GENSECTION) -I $** -O $@ -S EFI_SECTION_RAW

$(BUILD_DIR)\APCST.sec: $(BUILD_DIR)\APCST.aml
  $(GENSECTION) -I $** -O $@ -S EFI_SECTION_RAW

$(BUILD_DIR)\LakeTiny.sec: $(BUILD_DIR)\LakeTiny.aml
  $(GENSECTION) -I $** -O $@ -S EFI_SECTION_RAW

$(BUILD_DIR)\Ctdp.sec: $(BUILD_DIR)\Ctdp.aml
  $(GENSECTION) -I $** -O $@ -S EFI_SECTION_RAW  

#.SUFFIXES: .aml
#{$(BUILD_DIR)}.aml{$(BUILD_DIR)}.sec:
#  $(GENSECTION) -I $< -O $@ -S EFI_SECTION_RAW

$(BUILD_DIR)\PPMACPI.ffs: $(ALLPPMSEC) $(PowerMgmtDxe_DIR)\PowerMgmtDxe.mak
  $(GENFFSFILE) -B $(BUILD_DIR) -V -o $@ -P1 <<$(BUILD_DIR)\PPMACPI.pkg
PACKAGE.INF
[.]
BASE_NAME                   = PPMACPI
FFS_FILEGUID                = 299141BB-211A-48a5-92C0-6F9A0A3A006E
FFS_FILETYPE                = EFI_FV_FILETYPE_FREEFORM
FFS_ATTRIB_CHECKSUM         = TRUE

IMAGE_SCRIPT =
{
  Compress (dummy) {
			$(PROJECT_DIR)\$(BUILD_DIR)\CPUPM.sec
			$(PROJECT_DIR)\$(BUILD_DIR)\CPU0IST.sec
			$(PROJECT_DIR)\$(BUILD_DIR)\APIST.sec
			$(PROJECT_DIR)\$(BUILD_DIR)\CPU0TST.sec
			$(PROJECT_DIR)\$(BUILD_DIR)\APTST.sec
			$(PROJECT_DIR)\$(BUILD_DIR)\CPU0CST.sec
			$(PROJECT_DIR)\$(BUILD_DIR)\APCST.sec
			$(PROJECT_DIR)\$(BUILD_DIR)\LakeTiny.sec
			$(PROJECT_DIR)\$(BUILD_DIR)\Ctdp.sec
  }
}
<<KEEP
