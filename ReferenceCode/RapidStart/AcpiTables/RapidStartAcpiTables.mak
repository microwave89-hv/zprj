#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
#**                                                                     **
#**                       All Rights Reserved.                          **
#**                                                                     **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
#**                                                                     **
#**                       Phone: (770)-246-8600                         **
#**                                                                     **
#*************************************************************************
#*************************************************************************

#*************************************************************************
# $Header: /Alaska/SOURCE/Modules/Intel Fast Flash Standby/iRST_SharkBay/RapidStartAcpiTables/RapidStartAcpiTables.mak 3     6/02/13 8:23a Joshchou $
#
# $Revision: 3 $
#
# $Date: 6/02/13 8:23a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/Intel Fast Flash Standby/iRST_SharkBay/RapidStartAcpiTables/RapidStartAcpiTables.mak $
# 
# 3     6/02/13 8:23a Joshchou
# [TAG]  		None
# [Category]  	Improvement
# [Description]  	Change IASL compiler path to
# $(ACPIPLATFORM_ASL_COMPILER) in SharkBay project.
# 
# 2     11/20/12 2:22a Bensonlai
# [TAG]  		EIP107013
# [Category]  	Improvement
# [Description]  	Update Shark Bay Rapid Start Reference Code Version
# 0.8.0.0
# [Files]  		RapidStartAcpiTables.sdl
# RapidStartAcpiTables.mak
# RapidStartAcpiTables.inf
# Ssdt\RapidStart.asl
# RapidStartAcpiTables.cif
# 
# 1     4/19/12 7:50a Yurenlai
# Initial check in.
#
#*************************************************************************
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
EDK : RapidStartASL

ALLRapidStartSEC = $(BUILD_DIR)\RapidStart.sec\

RapidStartASL:  $(BUILD_DIR)\RapidStartAcpiTables.ffs

$(BUILD_DIR)\RapidStart.aml: $(INTEL_RAPIDSTART_ASL_FILE)
!if "$(ASL_COMPILER)" == "MASL"
  @$(MASL) /Fo=$@ $**
!elseif "$(ASL_COMPILER)" == "IASL"
  @cl /C /EP $(INTEL_RAPIDSTART_ASL_FILE) > $(BUILD_DIR)\RapidStart.asl
  $(IASL) -p $(BUILD_DIR)\RapidStart.aml $(BUILD_DIR)\RapidStart.asl
!endif

$(BUILD_DIR)\RapidStart.sec: $(BUILD_DIR)\RapidStart.aml
  $(GENSECTION) -I $** -O $@ -S EFI_SECTION_RAW

$(BUILD_DIR)\RapidStartAcpiTables.ffs: $(ALLRapidStartSEC) $(RapidStartAcpiTables_DIR)\RapidStartAcpiTables.mak
  $(GENFFSFILE) -B $(BUILD_DIR) -V -o $@ -P1 <<$(BUILD_DIR)\RapidStartAcpiTables.pkg
PACKAGE.INF
[.]
BASE_NAME                   = RapidStartAcpiTables
FFS_FILEGUID                = 60AC3A8F-4D66-4CD4-895A-C3F06E6665EE
FFS_FILETYPE                = EFI_FV_FILETYPE_FREEFORM
FFS_ATTRIB_CHECKSUM         = TRUE

IMAGE_SCRIPT =
{
  Compress (dummy) {
			$(PROJECT_DIR)\$(BUILD_DIR)\RapidStart.sec
  }
}
<<KEEP
#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
#**                                                                     **
#**                       All Rights Reserved.                          **
#**                                                                     **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
#**                                                                     **
#**                       Phone: (770)-246-8600                         **
#**                                                                     **
#*************************************************************************
#*************************************************************************
