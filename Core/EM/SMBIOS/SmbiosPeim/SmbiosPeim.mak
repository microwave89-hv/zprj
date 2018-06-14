#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
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
# $Header: /Alaska/SOURCE/Modules/SMBIOS/SmbiosPeim/SmbiosPeim.mak 1     5/27/14 1:44p Davidd $
#
# $Revision: 1 $
#
# $Date: 5/27/14 1:44p $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SMBIOS/SmbiosPeim/SmbiosPeim.mak $
# 
# 1     5/27/14 1:44p Davidd
# [TAG]  		EIP103526
# [Category]  	Improvement
# [Files]  		SmbiosPeim.cif
# SmbiosPeim.sdl
# SmbiosPeim.mak
# SmbiosPeim.dxs
# SmbiosPei.c
# 
# 1     4/29/14 4:44p Davidd
# [TAG]  		EIP103526
# [Category]  	Improvement
# [Description]  	We should update Wake-up Type in SMBIOS type 1
# dynamically
# [Files]  		Core\EM\SMBios\SmbiosPeim\SmbiosPeim.cif
# Core\EM\SMBios\SmbiosPeim\SmbiosPeim.sdl
# Core\EM\SMBios\SmbiosPeim\SmbiosPeim.mak
# Core\EM\SMBios\SmbiosPeim\SmbiosPeim.dxs
# Core\EM\SMBios\SmbiosPeim\SmbiosPei.c
# 
# 6     1/13/10 2:13p Felixp
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	<SmbiosPeim>.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************
all : SmbiosPeim

SmbiosPeim : $(BUILD_DIR)\SmbiosPeim.mak SmbiosPeimBin

$(BUILD_DIR)\SmbiosPeim.mak : $(SMBIOS_PEIM_DIR)\$(@B).cif $(SMBIOS_PEIM_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(SMBIOS_PEIM_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

SMBIOS_PEIM_OBJECTS = $$(BUILD_DIR)\$(SMBIOS_PEIM_DIR)\SmbiosPei.obj

SmbiosPeimBin : $(AMIPEILIB) $(AMICSPLib)
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\SmbiosPeim.mak all\
		NAME=SmbiosPeim\
        OBJECTS="$(SMBIOS_PEIM_OBJECTS)" \
		GUID=AC836A8E-B69A-470b-BECF-912A01B794F4\
		ENTRY_POINT=SmbiosPeiEntryPoint\
		DEPEX1=$(SMBIOS_PEIM_DIR)\SmbiosPeim.dxs DEPEX1_TYPE=EFI_SECTION_PEI_DEPEX \
		TYPE=PEIM \
		COMPRESS=0

#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************