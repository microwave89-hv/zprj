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
# $Header: /Alaska/SOURCE/Modules/SMM/SmmCommunicate/SmmCommunicate.mak 2     9/12/11 9:59a Markw $
#
# $Revision: 2 $
#
# $Date: 9/12/11 9:59a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SMM/SmmCommunicate/SmmCommunicate.mak $
# 
# 2     9/12/11 9:59a Markw
# [TAG]  		EIP64115
# [Category]  	Bug Fix
# [Severity]  	Normal
# [Symptom]  	SmmCommuncate hangs in OS.
# [RootCause]  	SmmCommunicate not supported in OS.
# [Solution]  	Update SMM Communicate to work under OS by making it a
# runtime driver and converting pointers to virtual points on
# EVT_SIGNAL_VIRTUAL_ADDRESS_CHANGE.
# 
# [Files]  		SmmCommunicate.c, SmmCommunicate.mak
# 
# 1     4/18/11 12:03p Markw
# [TAG]  		EIP57440
# [Category]  	New Feature
# [Description]  	Add SMM PI 1.1 Communicate Support.
# [Files]  		SmmCommunicate.cif
# SmmCommunicate.sdl
# SmmCommunicate.c
# SmmCommunicate.dxs
# SmmDxeCommunicate.dxs
# SmmCommunicate.mak
# 
#**********************************************************************

#<AMI_FHDR_START>
#---------------------------------------------------------------------------
#
# Name:			SmmCommunicate.mak
#
# Description:	Make file for the SMM Communicate code
#
#---------------------------------------------------------------------------
#<AMI_FHDR_END>

all : SmmCommunicate
SmmCommunicate : $(BUILD_DIR)\SmmCommunicate.mak SmmCommunicateBin

$(BUILD_DIR)\SmmCommunicate.mak : $(SMM_COMMUNICATE_DIR)\SmmCommunicate.cif $(SMM_COMMUNICATE_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(SMM_COMMUNICATE_DIR)\SmmCommunicate.cif $(CIF2MAK_DEFAULTS)

SmmCommunicateBin : $(AMIDXELIB) $(AMICSPLib)
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\SmmCommunicate.mak all\
		GUID=7E2D983F-F703-4a29-9761-77B51F5354ED\
		ENTRY_POINT=SmmCommunicateEntry\
        TYPE=DXESMM_DRIVER PE_TYPE=RT_DRIVER\
        DEPEX1=$(SMM_COMMUNICATE_DIR)\SmmCommunicate.dxs \
        DEPEX1_TYPE=EFI_SECTION_SMM_DEPEX \
        DEPEX2=$(SMM_COMMUNICATE_DIR)\SmmDxeCommunicate.dxs \
        DEPEX2_TYPE=EFI_SECTION_DXE_DEPEX \
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
