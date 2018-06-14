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
# $Header: /Alaska/SOURCE/Modules/SMM/PowerButton/PowerButton.mak 5     9/20/11 3:12p Markw $
#
# $Revision: 5 $
#
# $Date: 9/20/11 3:12p $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SMM/PowerButton/PowerButton.mak $
# 
# 5     9/20/11 3:12p Markw
# [TAG]  		EIP67890
# [Category]  	Spec Update
# [Severity]  	Normal
# [Description]  	Support power button handler in PI 1.1
# 
# [Files]  		PowerButton.c, PowerButton.mak, PowerButton. dxs
# 
# 4     7/08/09 8:24p Markw
# Update header.
# 
# 3     5/30/07 5:29p Markw
# Use library function to shutdown.
# 
# 2     12/02/05 11:48a Felixp
# 
# 1     1/28/05 4:33p Sivagarn
# Power Button SMM Component - Initial check in
# 
# 
#**********************************************************************



#<AMI_FHDR_START>
#---------------------------------------------------------------------------
#
# Name:			PowerButton.MAK
#
# Description:	Make file for the SMM power button handler code
#
#---------------------------------------------------------------------------
#<AMI_FHDR_END>
!IFNDEF PI_SPECIFICATION_VERSION
PI_SPECIFICATION_VERSION=0
!ENDIF

all : PowerButton

PowerButton : $(BUILD_DIR)\PowerButton.mak PowerButtonBin

$(BUILD_DIR)\PowerButton.mak : $(POWER_BUTTON_DIR)\PowerButton.cif $(POWER_BUTTON_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(POWER_BUTTON_DIR)\PowerButton.cif $(CIF2MAK_DEFAULTS)

PowerButtonBin : $(AMIDXELIB) $(AMICSPLib)
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\PowerButton.mak all\
		GUID=E566B097-4378-485f-91D0-1C097C190CE2\
		ENTRY_POINT=InitPowerButton\
!IF $(PI_SPECIFICATION_VERSION) < 0x1000A
		TYPE=BS_DRIVER\
!ELSE
		TYPE=SMM_DRIVER\
!ENDIF
		COMPRESS=1

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
