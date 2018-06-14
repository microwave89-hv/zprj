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

#*************************************************************************
# $Header: /Alaska/SOURCE/Modules/OFBD/OEMOAHandle/OEMOAHandle.mak 1     10/24/11 3:02a Terrylin $
#
# $Revision: 1 $
#
# $Date: 10/24/11 3:02a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/OFBD/OEMOAHandle/OEMOAHandle.mak $
# 
# 1     10/24/11 3:02a Terrylin
# Add for EIP 66385
#  
#*************************************************************************
#<AMI_FHDR_START>
#
# Name:	OemOAHandle.mak
#
# Description:	Make file for the OemOAHandle.obj
#
#<AMI_FHDR_END>
#*************************************************************************
all : OEMOAHANDLE

OEMOAHANDLE : $(BUILD_DIR)\OEMOAHANDLE.mak OEMOAHANDLEBin

$(BUILD_DIR)\OEMOAHANDLE.mak : $(OFBD_OEM_OA_HANDLE_DIR)\$(@B).cif $(OFBD_OEM_OA_HANDLE_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(OFBD_OEM_OA_HANDLE_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

OEMOAHANDLEBin :
	@set INCLUDE=%%INCLUDE%%
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\OEMOAHANDLE.mak all\
        NAME=OEMOAHANDLE \
		TYPE=LIBRARY LIBRARY_NAME=$(OEMOAHANDLELIB)

$(OEMOAHANDLELIB) : OEMOAHANDLE

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


