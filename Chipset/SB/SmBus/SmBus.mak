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

#**********************************************************************
# $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/SmBus/SmBus.mak 1     6/06/12 8:00a Victortu $
#
# $Revision: 1 $
#
# $Date: 6/06/12 8:00a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/SmBus/SmBus.mak $
# 
# 1     6/06/12 8:00a Victortu
# Implement EFI_PEI_SMBUS2_PPI Support.
# 
# 6     7/19/11 8:28a Abelwu
# [TAG]  		EIP63768
# [Category]  	Improvement
# [Description]  	Supported Core 4.6.5.x PI 1.2 / uEFI 2.3.1 compliance
# [Files]  		SmBus.mak
# 
# 5     6/17/11 5:52p Artems
# EIP 53378: Replaced tabs with spaces, formatted to follow coding
# standard
# 
# 4     5/18/11 11:50a Artems
# 
# 3     1/27/11 9:48p Abelwu
# Supports SMBUS Protocol in early DXE phase. (EIP#40778)
# 
# 2     10/16/09 7:06p Artems
# Updated copyright header
# 
# 1     1/09/09 6:53p Artems
# New implementation of SMBus EIP 16730
# 
# 1     3/18/07 5:23p Felixp
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:         SmBus.mak
#
# Description:  This make file builds SMBus PEI and DXE components 
#               and link them to respective binary.
#
#<AMI_FHDR_END>
#**********************************************************************
!IFNDEF PI_SPECIFICATION_VERSION
PI_SPECIFICATION_VERSION = 0
!ENDIF

all : SmBusPei #SmBusDxe

SMBUS_PEI_OBJECTS=\
$$(BUILD_DIR)\$(SmBus_DIR)\SmBusCommon.obj\
$$(BUILD_DIR)\$(SmBus_DIR)\SmBusPorting.obj\
$$(BUILD_DIR)\$(SmBus_DIR)\SmBusPei.obj

#SMBUS_DXE_OBJECTS=\
#$$(BUILD_DIR)\$(SmBus_DIR)\SmBusCommon.obj\
#$$(BUILD_DIR)\$(SmBus_DIR)\SmBusPorting.obj\
#$$(BUILD_DIR)\$(SmBus_DIR)\SmBusDxe.obj

SMBUS_PCI_OBJECTS=\
$$(BUILD_DIR)\$(SmBus_DIR)\SmBusPciHooks.obj\

$(BUILD_DIR)\SmBus.mak : $(SmBus_DIR)\$(@B).cif $(SmBus_DIR)\$(@B).mak $(BUILD_RULES)
    $(CIF2MAK) $(SmBus_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

#SmBusDxe : $(BUILD_DIR)\SmBus.mak SmBusDxeBin
SmBusPei : $(BUILD_DIR)\SmBus.mak SmBusPeiBin
#PciBusSrc : $(BUILD_DIR)\SmBus.mak SmBusPciHooksBin
$(BUILD_DIR)\AMISmBusLib.lib : $(BUILD_DIR)\SmBus.mak SmBusPciHooksBin

#SmBusDxeBin : $(AMIDXELIB)
#    $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
#        /f $(BUILD_DIR)\SmBus.mak all\
#        NAME=SmBusDxe\
#        MAKEFILE=$(BUILD_DIR)\SmBus.mak \
#        "OBJECTS=$(SMBUS_DXE_OBJECTS)" \
#        GUID=4B680E2D-0D63-4f62-B930-7AE995B9B3A3\
#        ENTRY_POINT=SmBusDxeEntryPoint\
#!IF $(PI_SPECIFICATION_VERSION) >= 0x1000A
#        TYPE=DXESMM_DRIVER \
#        DEPEX1=$(SmBus_DIR)\SmBusSmm.DXS DEPEX1_TYPE=EFI_SECTION_SMM_DEPEX \
#        DEPEX2=$(SmBus_DIR)\SmBusDxe.DXS DEPEX2_TYPE=EFI_SECTION_DXE_DEPEX \
#!ELSE
#		TYPE=BS_DRIVER \
#        DEPEX1=$(SmBus_DIR)\SmBusDxe.DXS DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX \
#!ENDIF
#        COMPRESS=1\

SmBusPeiBin : $(AMICSPLib) $(AMIPEILIB)
    $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
        /f $(BUILD_DIR)\SmBus.mak all\
        NAME=SmBusPei\
        MAKEFILE=$(BUILD_DIR)\SmBus.mak \
!IF "$(x64_BUILD)"=="1"
        BUILD_DIR=$(BUILD_DIR)\IA32\
!ELSE
        BUILD_DIR=$(BUILD_DIR)\
!ENDIF
        "OBJECTS=$(SMBUS_PEI_OBJECTS)" \
        GUID=9EA28D33-0175-4788-BEA8-6950516030A5 \
        ENTRY_POINT=SmBusPeiEntryPoint \
        TYPE=PEIM \
        "MY_INCLUDES=$(INTEL_PCH_INCLUDES)" \
        DEPEX1=$(SmBus_DIR)\SmBusPei.DXS DEPEX1_TYPE=EFI_SECTION_PEI_DEPEX \
        COMPRESS=0

SmBusPciHooksBin :
    $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
        /f $(BUILD_DIR)\SmBus.mak all\
        NAME=AMISmBusLib\
        MAKEFILE=$(BUILD_DIR)\SmBus.mak\
        OBJECTS="$(SMBUS_PCI_OBJECTS)"\
        TYPE=LIBRARY\
        "CFLAGS=$(CFLAGS)" 

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
#**********************************************************************
