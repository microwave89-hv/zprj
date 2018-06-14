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
# $Header: /Alaska/SOURCE/Core/Modules/PciBus/PciBusSrc.mak 5     1/13/10 3:25p Felixp $
#
# $Revision: 5 $
#
# $Date: 1/13/10 3:25p $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Core/Modules/PciBus/PciBusSrc.mak $
# 
# 5     1/13/10 3:25p Felixp
# Dependency from token.h is added
# 
# 4     4/28/09 5:51p Yakovlevs
# 
# 3     11/14/08 1:16p Yakovlevs
# Changed the way PciRootBridge Module gets build.
# 
# 2     10/01/08 7:12p Yakovlevs
# Updated AMI FUNC HEADER information
# 
# 1     3/12/07 12:02p Yakovlevs
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	PsiBusSrc.mak
#
# Description:	Make file to build PciBus Driver Sources.
#
#<AMI_FHDR_END>
#**********************************************************************
PCIBUS_SOURCE_OBJECTS=\
$(BUILD_DIR)\$(PCIBUS_DIR)\PciBus.obj\
!IF "$(AMI_ROOT_BRIDGE_SUPPORT)"=="1"
$(BUILD_DIR)\$(PCIBUS_DIR)\PciHostBridge.obj\
$(BUILD_DIR)\$(PCIBUS_DIR)\DeviceIo.obj\
!ENDIF

$(PCIBUSSRCLIB) : PciBusSrc

PciBusSrc : $(BUILD_DIR)\PciBusSrc.mak PciBusSrcBin

$(BUILD_DIR)\PciBusSrc.mak : $(PCIBUS_DIR)\$(@B).cif $(PCIBUS_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(PCIBUS_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

PciBusSrcBin :
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\PciBusSrc.mak all\
		MAKEFILE=$(PCIBUS_DIR)\PciBusSrc.mak\
		"OBJECTS=$(PCIBUS_SOURCE_OBJECTS)"\
        "EXT_HEADERS=$(BUILD_DIR)\token.h"\
		TYPE=LIBRARY

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