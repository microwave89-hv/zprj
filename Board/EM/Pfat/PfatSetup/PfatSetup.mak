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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelPfat/PfatSetup/PfatSetup.mak 1     9/17/12 4:49p Fredericko $
#
# $Revision: 1 $
#
# $Date: 9/17/12 4:49p $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelPfat/PfatSetup/PfatSetup.mak $
# 
# 1     9/17/12 4:49p Fredericko
# Added PfatSetup Module-part
#
#
#**********************************************************************
#<AMI_FHDR_START>
#
# Name: PfatSetup.mak
#
# Description: Make file for PfatSetup module part
#
#<AMI_FHDR_END>
#**********************************************************************
all : PfatSetupSDB

#---------------------------------------------------------------------------
# Generic AcpiPlatform dependencies
#---------------------------------------------------------------------------
$(BUILD_DIR)\PfatSetup.mak : $(PFAT_SETUP_PATH)\PfatSetup.cif $(BUILD_RULES)
  $(CIF2MAK) $(PFAT_SETUP_PATH)\PfatSetup.cif $(CIF2MAK_DEFAULTS)

#---------------------------------------------------------------------------
# Create PfatSetup Setup Screens
#---------------------------------------------------------------------------
SetupSdbs : $(BUILD_DIR)\PfatSetup.mak PfatSetupSDB

PfatSetupSDB :
  $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
  /f $(BUILD_DIR)\PfatSetup.mak all \
  TYPE=SDB NAME=PfatSetup STRING_CONSUMERS=$(PFAT_SETUP_PATH)\PfatSetup.sd

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
