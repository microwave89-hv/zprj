#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**             5555 Oakbrook Pkwy, Norcross, GA 30093               **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************
# $Header: /Alaska/BIN/Core/Modules/IdeBus/IdeBus.mak 8     8/25/10 5:35a Rameshr $
#
# $Revision: 8 $
#
# $Date: 8/25/10 5:35a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Core/Modules/IdeBus/IdeBus.mak $
# 
# 8     8/25/10 5:35a Rameshr
# New Feature: EIP 37748
# Description: Move all the IDEBus Source driver SDL token into IdeBus
# Bin Driver.
# FilesModified: Ata.c, Atapi.c, idebus.c, IdeBus.h,
# IdebuscomponentName.c, IdeBusmaster.c IdeBusSrc.mak IdebusSrc.sdl
# IdeHpa.c, IdePowerManagement.c
# 
# 7     7/01/09 12:25p Rameshr
# Coding Standard and File header updated.
# 
# 6     3/04/08 7:50p Felixp
# 
# 4     28/02/08 7:10p Anandakrishnanl
# Moved the files from IdeBus to the Security module. 
# 
# 3     10/24/07 2:53p Felixp
# 
# 2     10/23/07 4:18p Felixp
# IDE Security support moved from Sources to Binary
# IDE Security Setup screen added
# 
# 1     12/01/05 9:38a Felixp
# 
# 2     2/11/05 5:49p Felixp
# Binary files organization improved:
#   - extra layer of sub-component removed
#   - macros initialization moved to SDL tokens to eliminate undefined
# macros situation
#   - debug and release binaries have different names now (workaround for
# VeB limitation)
#   - binaries reside in the component home directory (eliminates
# hardcoded paths)
# 
# 1     1/28/05 12:45p Felixp
# 
# 4     1/18/05 3:22p Felixp
# PrintDebugMessage renamed to Trace
# 
# 3     12/24/04 3:25p Felixp
# 
# 2     12/24/04 3:24p Felixp
# 
# 1     12/10/04 1:01p Srinin
# Initial Checkin of IdeBus Driver.
# 
# 
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name: IDEBUS_mak
#
# Description:IdeBus BIN make file.	
#
#<AMI_FHDR_END>
#**********************************************************************

CORE_DXEBin : $(BUILD_DIR)\IdeBusBin.lib 

$(BUILD_DIR)\IdeBusBin.lib : IdeBusBin 

IdeBusBin : $(BUILD_DIR)\IdeBus.mak IdeBusBinBin

$(BUILD_DIR)\IdeBus.mak : $(IDEBUS_DIR)\IdeBus.cif Board\EM\IdeBusBoard\IdeBusBoard.cif $(IDEBUS_DIR)\IdeBus.mak $(BUILD_RULES)
	$(CIF2MAK) $(IDEBUS_DIR)\IdeBus.cif $(CIF2MAK_DEFAULTS) Board\EM\IdeBusBoard\IdeBusBoard.cif 

IDEBUS_BOARD_OBJECTS = $(BUILD_DIR)\Board\EM\IdeBusBoard\IdeBusBoard.obj

IdeBusBinBin : $(IdeBusSrc_LIB)
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\IdeBus.mak all\
		MAKEFILE=$(IDEBUS_DIR)\IdeBus.mak \
        OBJECTS="$(IDEBUS_BOARD_OBJECTS)" \
		"EXT_HEADERS=$(BUILD_DIR)\token.h"\
		TYPE=LIBRARY LIBRARY_NAME=$(BUILD_DIR)\IdeBusBin.lib LIBRARIES=\

#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**             5555 Oakbrook Pkwy, Norcross, GA 30093               **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************

