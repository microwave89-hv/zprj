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
#**********************************************************************
# $Header: /Alaska/SOURCE/Core/Modules/IdeBus/IdeBusSrc.mak 5     8/25/10 4:11a Rameshr $
#
# $Revision: 5 $
#
# $Date: 8/25/10 4:11a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Core/Modules/IdeBus/IdeBusSrc.mak $
# 
# 5     8/25/10 4:11a Rameshr
# New Feature: EIP 37748
# Description: Move all the IDEBus Source driver SDL token into IdeBus
# Bin Driver.
# FilesModified: Ata.c, Atapi.c, idebus.c, IdeBus.h,
# IdebuscomponentName.c, IdeBusmaster.c IdeBusSrc.mak IdebusSrc.sdl
# IdeHpa.c, IdePowerManagement.c
# 
# 4     7/01/09 12:22p Rameshr
# Coding Standard and File header updated.
# 
# 3     12/02/05 11:21a Felixp
# 
# 2     12/02/05 11:21a Felixp
# 
# 1     12/01/05 9:43a Felixp
# 
# 3     11/22/05 12:56p Felixp
# dependency from token.h added
# 
# 2     2/01/05 1:02p Srinin
# Idebus.mak changed to Idebussrc.mak
# 
# 1     1/28/05 12:45p Felixp
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	IdeBusSrc.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************
all : IDEBus


IDEBus : $(BUILD_DIR)\IdeBusSrc.mak IDEBusSrcBin

$(BUILD_DIR)\IdeBusSrc.mak : $(IDEBUS_DIR)\$(@B).cif $(IDEBUS_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(IDEBUS_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

$(IdeBusSrc_LIB) : IDEBus

IDEBusSrcBin: 
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\IDEBusSrc.mak all\
		"EXT_HEADERS=$(BUILD_DIR)\token.h"\
		TYPE=LIBRARY LIBRARY_NAME=$(IdeBusSrc_LIB)

# to build as a separete binary:
# 1. Uncomment next block
# 2. Disable IdeBusEntryPoint eLink
# 3. Enable $(BUILD_DIR)\IDEBus.ffs eLink
#IDEBusSrcBin: $(AMIDXELIB)
#	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
#		/f $(BUILD_DIR)\IdeBusSrc.mak all\
#		GUID=59B90A53-461B-4C50-A79F-A32773C319AE\
#		ENTRY_POINT=IdeBusEntryPoint \
#		TYPE=BS_DRIVER \
#		COMPRESS=1\
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
