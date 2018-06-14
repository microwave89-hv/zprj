#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**             5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093    **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************

#**********************************************************************
# $Header: /Alaska/SOURCE/Modules/AHCI/AhciSrc.mak 6     2/10/11 10:35a Rameshr $
#
# $Revision: 6 $
#
# $$
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/AHCI/AhciSrc.mak $
# 
# 6     2/10/11 10:35a Rameshr
# [TAG]  		EIP53704
# [Category]  	Improvement
# [Description]  	AMI headers update for Alaska Ahci Driver
# [Files]  		AhciSrc.mak
# AhciBus.c
# AhciController.c
# AhciComponentName.c
# AhciBus.h
# AhciController.h
# 
# 5     5/07/10 11:42a Krishnakumarg
# Coding standard update
# 
# 4     5/28/08 9:36a Rameshraju
# Based on the SDL token index/data or MMIO method used to access the
# AHCI configuration space.
# 
# 3     3/28/08 12:13p Michaela
# Fixed build issue related to component name change
# 
# 2     3/02/08 8:16p Fasihm
# Removed the code not to build the cod files.
# 
# 1     28/02/08 6:03p Anandakrishnanl
# AHCI Bus Driver initial check-in.
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	AhciSrc.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************
all : Ahci

Ahci : $(BUILD_DIR)\AhciSrc.mak AhciBin

!IF "$(INDEX_DATA_PORT_ACCESS)"=="1"
$(BUILD_DIR)\AhciSrc.mak : $(AHCI_DIR)\$(@B).cif $(AHCI_DIR)\$(@B).mak $(BUILD_RULES) $(AHCI_CSP_DIR)\AhciAccess.cif
    $(CIF2MAK) $(AHCI_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS) $(AHCI_CSP_DIR)\AhciAccess.cif
!ELSE
$(BUILD_DIR)\AhciSrc.mak : $(AHCI_DIR)\$(@B).cif $(AHCI_DIR)\$(@B).mak $(BUILD_RULES)
    $(CIF2MAK) $(AHCI_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)
!ENDIF


#        "CFLAGS = $(CFLAGS) /FAscu /O1 /Fd$(BUILD_DIR)\ /Zi /Gm" \
#        "LFLAGS = $(LFLAGS) /MAP /DEBUG /PDB:$*.pdb" \         
#        "CFLAGS = $(CFLAGS:/O1=) /FAscu /Fd$(BUILD_DIR)\ /Zi /Gm" \
#        "LFLAGS= $(LFLAGS) /MAP /DEBUG /PDB:$(BUILD_DIR)\AhciSrc.pdb "\

AhciBin: $(AMIDXELIB)
    $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
        /f $(BUILD_DIR)\AhciSrc.mak all\
        MAKEFILE=$(BUILD_DIR)\AhciSrc.mak \
                NAME=AHCI \
        GUID=8F5A2E02-538C-4D59-B920-C4786ACBC552\
        ENTRY_POINT=AhciBusEntryPoint \
        TYPE=BS_DRIVER \
        COMPRESS=1\

#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**             5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093    **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************
