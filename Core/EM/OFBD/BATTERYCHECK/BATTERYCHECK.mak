#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2012, American Megatrends, Inc.            **
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
# $Header: /Alaska/SOURCE/Modules/OFBD/BATTERYCHECK/BATTERYCHECK.mak 1     10/11/12 2:27a Terrylin $
#
# $Revision: 1 $
#
# $Date: 10/11/12 2:27a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/OFBD/BATTERYCHECK/BATTERYCHECK.mak $
# 
# 1     10/11/12 2:27a Terrylin
# Initial check-in for OEM can control AC/Battery status check rule
#  
#*************************************************************************
#<AMI_FHDR_START>
#
# Name:	BATTERYCHECK.mak
#
# Description:	Make file for the BatteryCheck.obj
#
#<AMI_FHDR_END>
#*************************************************************************
all : BATTERYCHECK

BATTERYCHECK : $(BUILD_DIR)\BATTERYCHECK.mak BATTERYCHECKBin

$(BUILD_DIR)\BATTERYCHECK.mak : $(OFBD_BATTERYCHECK_DIR)\$(@B).cif $(OFBD_BATTERYCHECK_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(OFBD_BATTERYCHECK_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

BATTERYCHECKBin :
	@set INCLUDE=%%INCLUDE%%
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\BATTERYCHECK.mak all\
        NAME=BATTERYCHECK \
		TYPE=LIBRARY LIBRARY_NAME=$(BATTERYCHECKLIB)

$(BATTERYCHECKLIB) : BATTERYCHECK

#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2012, American Megatrends, Inc.            **
#**                                                                     **
#**                       All Rights Reserved.                          **
#**                                                                     **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
#**                                                                     **
#**                       Phone: (770)-246-8600                         **
#**                                                                     **
#*************************************************************************
#*************************************************************************


