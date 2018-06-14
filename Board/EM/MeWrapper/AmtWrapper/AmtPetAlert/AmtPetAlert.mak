#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2010, American Megatrends, Inc.            **
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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/AmtWrapper/AmtPetAlert/AmtPetAlert.mak 1     2/08/12 1:10a Klzhan $
#
# $Revision: 1 $
#
# $Date: 2/08/12 1:10a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/AmtWrapper/AmtPetAlert/AmtPetAlert.mak $
# 
# 1     2/08/12 1:10a Klzhan
# Initial Check in 
# 
# 1     2/25/11 1:45a Klzhan
# Initial Check-in
# 
# 1     12/03/10 5:11a Klzhan
# Initial Check-in.
#
#**********************************************************************
#
#<AMI_FHDR_START>
#---------------------------------------------------------------------------
# Name:		AmtPetAlert.mak
#
# Description:	Makefile for AMT Pet Alert Module.
#
#---------------------------------------------------------------------------
#<AMI_FHDR_END>
#---------------------------------------------------------------------------
#		Create AMT PET Alert Screens
#---------------------------------------------------------------------------
All : AmtPetAlert

AmtPetAlert : $(BUILD_DIR)\AmtPetAlert.mak AmtPetAlertBin

$(BUILD_DIR)\AmtPetAlert.mak : $(AMT_PET_ALERT_DIR)\$(@B).cif $(AMT_PET_ALERT_DIR)\$(@B).mak $(BUILD_RULES)
  $(CIF2MAK) $(AMT_PET_ALERT_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

AmtPetAlert_INCLUDES= \
  $(EDK_INCLUDES) \
  $(MISCFRAMEWORK_INCLUDES) \
  $(ME_INCLUDES) \
  $(IndustryStandard_INCLUDES)\

AmtPetAlertBin : $(EFIDRIVERLIB) $(EDKFRAMEWORKPROTOCOLLIB) $(PRINTLIB) $(EFICOMMONLIB)
  $(MAKE) /$(MAKEFLAGS) $(EDK_DEFAULTS)\
		/f $(BUILD_DIR)\AmtPetAlert.mak all \
		"MY_INCLUDES=$(AmtPetAlert_INCLUDES)"\
		GUID=290EA249-6E88-423c-B0DA-75CDDE7920CC \
		TYPE=BS_DRIVER \
		ENTRY_POINT=InitializeAmtPetAlert \
		DEPEX1=$(AMT_PET_ALERT_DIR)\AmtPetAlert.dxs \
		DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX \
		COMPRESS=1		
#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2010, American Megatrends, Inc.            **
#**                                                                     **
#**                       All Rights Reserved.                          **
#**                                                                     **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
#**                                                                     **
#**                       Phone: (770)-246-8600                         **
#**                                                                     **
#*************************************************************************
#*************************************************************************