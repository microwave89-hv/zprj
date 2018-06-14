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

#*************************************************************************
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/SwitchableGraphics/Sg TPV/Sg Acpi Tables/SgTpvAcpiTables.mak 5     1/15/13 6:07a Joshchou $
#
# $Revision: 5 $
#
# $Date: 1/15/13 6:07a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/SwitchableGraphics/Sg TPV/Sg Acpi Tables/SgTpvAcpiTables.mak $
# 
# 5     1/15/13 6:07a Joshchou
# [TAG]  		EIP107237
# [Category]  	New Feature
# [Description]  	Modify for support SG on ULT platform.
# 
# 4     12/22/12 2:39a Joshchou
# [TAG]  		None
# [Category]  	Improvement
# [Description]  	Update for SA RC 081,rename the name for corrcet make.
# 
# 3     11/20/12 3:46a Joshchou
# [TAG]  		None
# [Category]  	Improvement
# [Description]  	Create Token for OEM clone
# 
# 2     9/09/12 10:57p Joshchou
# 
# 1     6/27/11 5:26a Alanlin
# [TAG]  		EIP61848
# [Category]  	New Feature
# [Description]  	Initial check-in.Integrated SwitchableGraphics Intel
# Reference code 0.6.0
# [Files]  		SgTpvAcpiTables.cif
# SgTpvAcpiTables.sdl
# SgTpvAcpiTables.mak
# SgTpvAcpiTables.c
# 
# 
# 3     11/12/10 1:17p Alexp
# include the token.h in command line to CL preprocessor
# 
# 2     10/05/10 7:07p Alexp
# change the default build target
# 
# 1     9/17/10 1:18p Alexp
# [TAG]    	  EIP43103 
# [Category]  Function Request
# [Severity]	  Normal
# [Symptom]    Initial check-in of SgTPV module
# [RootCause] Request to implement SG reference code .
# [Solution]	Initial check-in. 
# [Files]	
#         SgTpvAcpiTables.cif;*.sdl;*.mak;*.c
# 
#*************************************************************************
#<AMI_FHDR_START>
#
# Name: SgTpvAcpiTables.mak
#
# Description: Make file to build SG TPV ACPI components
# 
#
#<AMI_FHDR_END>
#*************************************************************************
BUILD_SGTPV_DIR = $(BUILD_DIR)\$(SGTPV_DIR)

SaInitDxeBin: $(BUILD_SGTPV_DIR)\SgTpvAcpiTables.obj



$(BUILD_SGTPV_DIR)\SgTpvAcpiTables.obj: $(SGTPV_ACPI_DIR)\SgTpvAcpiTables.c
    $(CC) $(CFLAGS) /I$(INCLUDE_DIR)/ /DTIANO_RELEASE_VERSION=$(TIANO_RELEASE_VERSION) $(SgTpvDxe_INCLUDES) /Fo$@ $**

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
