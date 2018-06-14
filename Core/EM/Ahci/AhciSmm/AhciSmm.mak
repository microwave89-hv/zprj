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
# $Header: /Alaska/SOURCE/Modules/AHCI/AhciSmm/AhciSmm.mak 4     2/11/11 4:11a Rameshr $
#
# $Revision: 4 $
#
# $Date: 2/11/11 4:11a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/AHCI/AhciSmm/AhciSmm.mak $
# 
# 4     2/11/11 4:11a Rameshr
# [TAG]  		EIP53704
# [Category]  	Improvement
# [Description]  	AMI headers update for Alaska Ahci Driver
# [Files]  		AhciSmm.mak
# AhciSmm.dxs
# AhciSmm.c
# AhciSmm.h
# 
# 3     9/29/10 1:20p Mirk
# [TAG]		EIP44641
# [Synopsis]	Calpella: Build error when Token INDEX_DATA_PORT_ACCESS = 1
# in AhciSrc.sdl
# [Category]	Defect
# [Severity]	Normal
# [Resolution]	Updated AhciSmm.h and AhciSmm.mak to resolve build errors.
# [Files]		AhciSmm.h, AhciSmm.mak
# 
# 2     5/07/10 11:59a Krishnakumarg
# Updated the AMI header.
# 
# 1     4/28/09 6:39p Rameshr
# Initial Check-in
# 
# 
#**********************************************************************
all : AhciSmm

AhciSmm : $(BUILD_DIR)\AhciSmm.mak AhciSmmBin

$(BUILD_DIR)\AhciSmm.mak : $(AHCI_SMM_DIR)\AhciSmm.cif $(AHCI_SMM_DIR)\$(@B).mak $(BUILD_RULES) 
    $(CIF2MAK) $(AHCI_SMM_DIR)\AhciSmm.cif $(CIF2MAK_DEFAULTS)  $(AHCI_CSP_DIR)\AhciAccess.cif

AHCI_SMM_INCLUDES=\
        /I$(AHCI_DIR)\

AhciSmmBin : $(AMIDXELIB) 
    $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
        /f $(BUILD_DIR)\AhciSmm.mak all\
        GUID=BC3245BD-B982-4f55-9F79-056AD7E987C5\
        ENTRY_POINT=AhciSmmDriverEntryPoint\
        "MY_INCLUDES=$(AHCI_SMM_INCLUDES)"\
        TYPE=BS_DRIVER\
        COMPRESS=1

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
