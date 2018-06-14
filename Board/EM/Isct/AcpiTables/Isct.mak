#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************

#**********************************************************************
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ISCT/IsctAcpiTables/Isct.mak 2     5/27/13 10:54p Bensonlai $
#
# $Revision: 2 $
#
# $Date: 5/27/13 10:54p $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ISCT/IsctAcpiTables/Isct.mak $
# 
# 2     5/27/13 10:54p Bensonlai
# [TAG]  		EIP125007
# [Category]  	Improvement
# [Description]  	[ISCT] Change IASL compiler path
# 
# 1     9/02/12 11:18p Bensonlai
# Intel Smart Connect Technology initially releases.
#
#
#**********************************************************************
#<AMI_FHDR_START>
#
# Name: Isct.mak
#
# Description: Make file to build Isct ASL components
#
#
#<AMI_FHDR_END>
#**********************************************************************
all : BuildIsct

BuildIsct : $(BUILD_DIR)\Isct.ffs

#---------------------------------------------------------------------------
# Generic AcpiPlatform dependencies
#---------------------------------------------------------------------------
$(BUILD_DIR)\Isct.mak : $(INTEL_ISCT_DIR)\Isct.cif $(BUILD_RULES)
  $(CIF2MAK) $(INTEL_ISCT_DIR)\Isct.cif $(CIF2MAK_DEFAULTS)

#---------------------------------------------------------------------------
# Create ISCT Setup Screens
#---------------------------------------------------------------------------
SetupSdbs : $(BUILD_DIR)\Isct.mak ISCTSDB

ISCTSDB :
  $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
  /f $(BUILD_DIR)\Isct.mak all \
  TYPE=SDB NAME=Isct STRING_CONSUMERS=$(INTEL_ISCT_DIR)\Isct.sd

#-----------------------------------------------------------------------
# ASL compiler definition
#-----------------------------------------------------------------------
!IF "$(ACPIPLATFORM_ASL_COMPILER)"==""
!ERROR It is an invalid path, please check your ASL compiler path.
!ENDIF

IASL = $(ACPIPLATFORM_ASL_COMPILER) 
#-----------------------------------------------------------------------
$(BUILD_DIR)\Isct.aml : $(ISCT_ASL_FILE)
  @cl /C /EP $(ISCT_ASL_FILE) > $(BUILD_DIR)\Isct.asl
  $(IASL) -p $(BUILD_DIR)\Isct.aml $(BUILD_DIR)\Isct.asl

$(BUILD_DIR)\Isct.sec: $(BUILD_DIR)\Isct.aml
  $(GENSECTION) -I $*.aml -O $@ -S EFI_SECTION_RAW

#Note. Expand the package with Isct tables.
# DXE phase will load the tables
# and update Aml contents if provided in IsctAcpi.c

$(BUILD_DIR)\Isct.ffs: $(BUILD_DIR)\Isct.sec
  $(GENFFSFILE) -B $(BUILD_DIR) -V -o $@ -P1 <<$(BUILD_DIR)\Isct.pkg

PACKAGE.INF
[.]
BASE_NAME                   = Isct
FFS_FILEGUID                = FA2DDC38-3F19-4218-B53E-D9D79D626767
FFS_FILETYPE                = EFI_FV_FILETYPE_FREEFORM
FFS_ATTRIB_CHECKSUM         = TRUE

IMAGE_SCRIPT =
{
  Compress (dummy) {
	$(PROJECT_DIR)\$(BUILD_DIR)\Isct.sec
  }
}
<<KEEP

#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2012, American Megatrends, Inc.            **
#**                                                                     **
#**                       All Rights Reserved.                          **
#**                                                                     **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
#**                                                                     **
#**                       Phone: (770)-246-8600                         **
#**                                                                     **
#*************************************************************************
#*************************************************************************
