#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2007, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************
#**********************************************************************
# $Header: /Alaska/SOURCE/Core/CORE_DXE/FloppyCtrl/FloppyCtrl.mak 6     4/13/07 1:36p Ambikas $
#
# $Revision: 6 $
#
# $Date: 4/13/07 1:36p $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Core/CORE_DXE/FloppyCtrl/FloppyCtrl.mak $
# 
# 6     4/13/07 1:36p Ambikas
# Coding standards changes: Updated year in AMI copyright header and
# footer; 
# 
# changed AMI_FHDR a bit.
# 
# 5     10/13/06 4:40p Felixp
# 
# 4     9/13/06 10:08a Felixp
# x64 support
# 
#**********************************************************************


#<AMI_FHDR_START>
#----------------------------------------------------------------------
#
# Name:	FloppyCtrl.mak
#
# Description:	Floppy Controller component make file
#
#----------------------------------------------------------------------
#<AMI_FHDR_END>


all : FloppyCtrl 

FloppyCtrl : $(BUILD_DIR)\FloppyCtrl.mak FloppyCtrlBin

$(BUILD_DIR)\FloppyCtrl.mak : $(FLOPPY_CTRL_DIR)\$(@B).cif $(FLOPPY_CTRL_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(FLOPPY_CTRL_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

!IF "$(x64_BUILD)"!="1"
FloppyCtrlBin : $(AMIDXELIB) $(AMIPEILIB)
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\FloppyCtrl.mak all\
		GUID=8B9D3EE0-4BA4-433b-9C48-4E830B3B40FD\
		ENTRY_POINT=FloppyCtrlEntryPoint\
		DEPEX1_TYPE=EFI_SECTION_PEI_DEPEX\
		TYPE=COMBINED COMPRESS=1\
!ELSE

RecoverySrcPeiBin : $(BUILD_DIR)\FloppyCtrlPei.lib
CORE_DXE_LIBBin : $(BUILD_DIR)\FloppyCtrlDxe.lib

$(BUILD_DIR)\FloppyCtrlPei.lib $(BUILD_DIR)\FloppyCtrlDxe.lib : FloppyCtrl

FloppyCtrlBin :
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\FloppyCtrl.mak all\
		BUILD_DIR=$(BUILD_DIR)\IA32\
		"CFLAGS=$(CFLAGS) /DPEI_FLOPPY_CTRL"\
		TYPE=PEI_LIBRARY LIBRARY_NAME=$(BUILD_DIR)\FloppyCtrlPei.lib
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\FloppyCtrl.mak all\
		"CFLAGS=$(CFLAGS) /DDXE_FLOPPY_CTRL"\
		TYPE=LIBRARY LIBRARY_NAME=$(BUILD_DIR)\FloppyCtrlDxe.lib
!ENDIF
#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2007, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************