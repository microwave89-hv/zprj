#//**********************************************************************//
#//**********************************************************************//
#//**                                                                  **//
#//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **//
#//**                                                                  **//
#//**                       All Rights Reserved.                       **//
#//**                                                                  **//
#//**             5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093    **//
#//**                                                                  **//
#//**                       Phone: (770)-246-8600                      **//
#//**                                                                  **//
#//**********************************************************************//
#//**********************************************************************//

#************************************************************************//
# $Header: /Alaska/SOURCE/Modules/AHCI/INT13/Aint13.mak 7     8/28/13 12:38a Rameshr $
#
# $Revision: 7 $
#
# $Date: 8/28/13 12:38a $
#************************************************************************//
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/AHCI/INT13/Aint13.mak $
# 
# 7     8/28/13 12:38a Rameshr
# [TAG]  		EIP134204
# [Category]  	Improvement
# [Description]  	Build Error resolved if token INDEX_DATA_PORT_ACCESS is
# enabled.
# [Files]  		Aint13.mak
# 
# 6     6/07/11 12:02p Olegi
# [TAG]  		EIP61801
# [Category]  	Improvement
# [Description]  	Added dependency on LegacyBios protocol.
# 
# 5     2/10/11 10:49a Rameshr
# [TAG]  		EIP53704
# [Category]  	Improvement
# [Description]  	AMI headers update for Alaska Ahci Driver
# [Files]  		Aint13.mak
# AInt13.h
# AInt13.c
# 
# 4     5/28/08 9:41a Rameshraju
# Updated the AMI Address.
# 
# 3     3/28/08 12:14p Michaela
# updated copyright
# 
# 2     28/02/08 6:12p Anandakrishnanl
# Added the flags in the Build process.
# 
# 1     12/07/07 11:17a Olegi
# 
#************************************************************************//

all: AHCIINT13 AHCIINT13CSP

!IF "$(INDEX_DATA_PORT_ACCESS)"=="1"
$(BUILD_DIR)\aint13.mak : $(AINT13_DIR)\aint13.cif $(AHCI_CSP_DIR)\ahcicsp.cif $(AHCI_CSP_DIR)\AhciAccess.cif $(AINT13_DIR)\$(@B).mak $(BUILD_RULES) 
    	$(CIF2MAK) $(CIF2MAK_DEFAULTS) $(AINT13_DIR)\aint13.cif $(AHCI_CSP_DIR)\ahcicsp.cif $(AHCI_CSP_DIR)\AhciAccess.cif
!ELSE
$(BUILD_DIR)\aint13.mak: $(AINT13_DIR)\aint13.cif $(AHCI_CSP_DIR)\ahcicsp.cif $(AINT13_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(CIF2MAK_DEFAULTS) $(AINT13_DIR)\aint13.cif $(AHCI_CSP_DIR)\ahcicsp.cif
!ENDIF

AHCIINT13: $(BUILD_DIR)\aint13.mak AHCIINT13BIN

AHCI_OBJECTS = \
$(BUILD_DIR)\$(AINT13_DIR)\aint13.obj \
!IF "$(INDEX_DATA_PORT_ACCESS)"=="1"
$(BUILD_DIR)\$(AHCI_CSP_DIR)\AhciAccess.obj \
!ENDIF
$(BUILD_DIR)\$(AHCI_CSP_DIR)\aint13csp.obj

AHCIINT13BIN: $(AMIDXELIB)
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\aint13.mak all\
		GUID=67820532-7613-4dd3-9ED7-3D9BE3A7DA63\
		"OBJECTS=$(AHCI_OBJECTS)"\
		ENTRY_POINT=Ai13EntryPoint\
		TYPE=BS_DRIVER\
		COMPRESS=1\
		DEPEX1=$(AINT13_DIR)\aint13.dxs \

AHCIINT13CSP: $(BUILD_DIR)\ahciacc.obj

$(BUILD_DIR)\ahciacc.obj: $(AHCI_CSP_DIR)\ahciacc.asm
	$(ASM) /c /nologo /Fo$(BUILD_DIR)\ /Fl$(BUILD_DIR)\ $(AHCI_CSP_DIR)\ahciacc.asm

#//**********************************************************************//
#//**********************************************************************//
#//**                                                                  **//
#//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **//
#//**                                                                  **//
#//**                       All Rights Reserved.                       **//
#//**                                                                  **//
#//**             5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093    **//
#//**                                                                  **//
#//**                       Phone: (770)-246-8600                      **//
#//**                                                                  **//
#//**********************************************************************//
#//**********************************************************************//
