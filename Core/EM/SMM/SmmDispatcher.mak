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
# $Header: /Alaska/SOURCE/Modules/SMM/SMMDispatcher/SmmDispatcher.mak 9     2/07/11 3:29p Markw $
#
# $Revision: 9 $
#
# $Date: 2/07/11 3:29p $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SMM/SMMDispatcher/SmmDispatcher.mak $
# 
# 9     2/07/11 3:29p Markw
# [TAG]  		EIP53481
# [Category]  	New Feature
# [Description]  	Add PIWG 1.1 SMM support
# [Files]  		Smm.sdl, SmmPrivateShared.h, SmmDispatcher.mak,
# SmmDispatcher.h, SmmDispatcher.c,
# Smst.c, SmmPiSmst.c, SmmInit.c, SmmBase.c, SmmBase2.c,
# SmmDriverDispatcher.c, Smm Framewwork Protocol files, SmmPi.h,
# Smm Pi Protocol files, SmmPciRbio files
# 
# 8     7/08/09 9:28p Markw
# Update headers.
# 
# 7     3/05/09 5:20p Fasihm
# Rolled back accidental check-in.
# 
# 5     8/28/08 3:52p Markw
# 
# 4     6/09/08 5:48p Markw
# Add SmmDispatcherBoard.obj and SmmDispatcherAsm.obj to be linked.
# 
# 3     10/24/07 12:01p Markw
# Combined BSP and AP SmmEntry.
# 
# 2     8/24/06 3:28p Felixp
# Preliminary x64 support (work in progress)
# 
# 1     1/28/05 4:32p Sivagarn
# SMM Dispatcher Component - Initial check in
# 
# 
#**********************************************************************

#<AMI_FHDR_START>
#---------------------------------------------------------------------------
#
# Name:			SmmDispatcher.mak
#
# Description:	Make file for the SMM Dispatcher
#
#---------------------------------------------------------------------------
#<AMI_FHDR_END>
SMM_DISPATCHER_BUILD_DIR = $(BUILD_DIR)\$(SMM_DISPATCHER_DIR)

all : SmmDispatcher SmmEntry

SMM_DISPATCHER_OBJECTS = \
	$(SMM_DISPATCHER_BUILD_DIR)\SmmDispatcher.obj \
	$(SMM_DISPATCHER_BUILD_DIR)\Smst.obj \
	$(SMM_DISPATCHER_BUILD_DIR)\SmmPiSmst.obj \
	$(SMM_DISPATCHER_BUILD_DIR)\SmmMemoryManager.obj \
	$(SMM_DISPATCHER_BUILD_DIR)\SmmDispatcherAsm.obj

SmmDispatcher : $(BUILD_DIR)\SmmDispatcher.mak SmmDispatcherBin
SmmEntry : $(BUILD_DIR)\SmmDispatcher.mak SmmEntryBin

$(BUILD_DIR)\SmmDispatcher.mak : $(SMM_DISPATCHER_DIR)\$(@B).cif $(SMM_DISPATCHER_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(SMM_DISPATCHER_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

!IFNDEF PI_SPECIFICATION_VERSION
PI_SPECIFICATION_VERSION = 0
!ENDIF

SmmDispatcherBin : $(AMIDXELIB) $(AMICSPLib)
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\SmmDispatcher.mak all\
# Don't change the GUID. SmmBase driver expects this GUID.
		GUID=4A37320B-3FB3-4365-9730-9E89C600395D\
		ENTRY_POINT=InitializeDispatcher \
!IF $(PI_SPECIFICATION_VERSION) >= 0x00001000A
		TYPE=SMM_CORE \
!ELSE
   		TYPE=BS_DRIVER \
!ENDIF
		"OBJECTS=$(SMM_DISPATCHER_OBJECTS)"\
		"EXT_HEADERS=$(SMM_DISPATCHER_DIR)\SmmPrivateShared.h"\
		"CFLAGS=$(CFLAGS) /D\"SmmSaveRestoreEnvironment=$(SmmSaveRestoreEnvironment)\""\
		COMPRESS=1\

SmmEntryBin : 
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\SmmDispatcher.mak all\
# Don't change the GUID. SmmBase driver expects this GUID.
		GUID=D2596F82-F0E1-49fa-95BC-62012C795728\
		MAKEFILE=$(SMM_DISPATCHER_DIR)\SmmDispatcher.mak \
		TYPE=LEGACY16 NAME=SmmEntry DEPEX1= \
		"OBJECTS=$(SMM_DISPATCHER_BUILD_DIR)\SmmEntry.obj"\
		COMPRESS=1\

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
