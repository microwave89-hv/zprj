#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2008, American Megatrends, Inc.            **
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
# $Header: /Alaska/SOURCE/Modules/SMM/SMMBase/SmmBase.mak 4     2/07/11 3:35p Markw $
#
# $Revision: 4 $
#
# $Date: 2/07/11 3:35p $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SMM/SMMBase/SmmBase.mak $
# 
# 4     2/07/11 3:35p Markw
# [TAG]  		EIP53481
# [Category]  	New Feature
# [Description]  	Add PIWG 1.1 SMM support
# [Files]  		Smm.sdl, SmmPrivateShared.h, SmmDispatcher.mak,
# SmmDispatcher.h, SmmDispatcher.c,
# Smst.c, SmmPiSmst.c, SmmInit.c, SmmBase.c, SmmBase2.c,
# SmmDriverDispatcher.c, Smm Framewwork Protocol files, SmmPi.h,
# Smm Pi Protocol files, SmmPciRbio files
# 
# 3     7/08/09 8:26p Markw
# Updated headers.
# 
# 2     12/02/05 11:48a Felixp
# 
# 1     1/28/05 4:31p Sivagarn
# SMM Base Component - Initial check in
# 
# 
#**********************************************************************

#<AMI_FHDR_START>
#---------------------------------------------------------------------------
#
# Name:			SmmBase.MAK
#
# Description:	Make file for the SMM base code
#
#---------------------------------------------------------------------------
#<AMI_FHDR_END>

all : SmmBase

SmmBase : $(BUILD_DIR)\SmmBase.mak SmmBaseBin

$(BUILD_DIR)\SmmBase.mak : $(SMM_BASE_DIR)\SmmBase.cif $(SMM_BASE_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(SMM_BASE_DIR)\SmmBase.cif $(CIF2MAK_DEFAULTS)

SmmBaseBin : $(AMIDXELIB) $(AMICSPLib)
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\SmmBase.mak all\
		GUID=D0632C90-AFD7-4492-B186-257C63143C61\
		ENTRY_POINT=SmmInitEntry\
   		TYPE=BS_DRIVER \
		COMPRESS=1

#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2008, American Megatrends, Inc.            **
#**                                                                     **
#**                       All Rights Reserved.                          **
#**                                                                     **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
#**                                                                     **
#**                       Phone: (770)-246-8600                         **
#**                                                                     **
#*************************************************************************
#*************************************************************************
