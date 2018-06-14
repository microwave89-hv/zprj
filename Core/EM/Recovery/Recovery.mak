#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
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
# $Header: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Core/EM/Recovery/Recovery.mak 1     5/17/13 8:01a Thomaschen $
#
# $Revision: 1 $
#
# $Date: 5/17/13 8:01a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Core/EM/Recovery/Recovery.mak $
# 
# 1     5/17/13 8:01a Thomaschen
# Update for EIP124189.
# 
# 8     8/09/12 11:11a Pats
# [TAG] - EIP 80780
# [Category] - Function Request
# [Description] - Support for recovery from media formatted with the
# EXT(x) file system.
# [Files] Recovery.c, Recovery.mak, Recovery.sdl, RecoveryCsp.h (bin),
# and FsRecovery.c (source)
# 
# 7     1/25/12 2:46p Pats
# [TAG] - EIP 26909
# [Category] - Function Request
# [Description] - Support for recovery from media formatted with the NTFS
# file system. This of necessity includes detection of GPT partitions,
# which may contain any file system.
# [Files] Recovery.c, Recovery.mak, Recovery.sdl, RecoveryCsp.h (bin),
# and FsRecovery.c (source)
# 
# 6     5/13/11 4:44p Artems
# Replaced GetFileName infrastructure with GetRecoveryFileInfo for
# clarification
# 
# 5     2/05/11 2:43p Artems
# EIP 39463: Integrated Core portion for secure update - eLink support
# for GetFileName
# 
# 4     6/11/10 11:42a Artems
# Added porting hooks for recovery file name and validation
# 
# 3     7/08/09 6:21p Artems
# Changed file header
# 
# 2     12/02/05 11:17a Felixp
# 
# 1     12/01/05 9:35a Felixp
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	Recovery.mak
#
# Description: Makefile for recovery module
#
#<AMI_FHDR_END>
#**********************************************************************
all : Recovery

AMI_CSP_LIB_INCLUDE_FILES = "$(Recovery_DIR)\RecoveryCsp.h" + \
$(AMI_CSP_LIB_INCLUDE_FILES)

RECOVERY_DEFINES =\
/DOemGetFileListFromPrimaryVolume=$(OemGetFileListFromPrimaryVolumeFunction) \
/DOemGetFileListFromFatVolume=$(OemGetFileListFromFatVolumeFunction) \
/DOemGetFileListFromNtfsVolume=$(OemGetFileListFromNtfsVolumeFunction) \
/DOemGetFileListFromExtVolume=$(OemGetFileListFromExtVolumeFunction) \
/DOemIsValidFile=$(OemIsValidFileFunction) \
!IF $(PfatServices_SUPPORT) == 1
/DOemGetRecoveryFileInfo=PfatImageInfo
!ELSE
/DOemGetRecoveryFileInfo=$(OemGetRecoveryFileInfoFunction)
!ENDIF

Recovery : $(BUILD_DIR)\Recovery.mak RecoveryBin

$(BUILD_DIR)\Recovery.mak : $(Recovery_DIR)\$(@B).cif $(Recovery_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(Recovery_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

RecoveryBin : $(AMIPEILIB) $(RECOVERYLIB)
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\Recovery.mak all\
		GUID=E008B434-0E73-440c-8612-A143F6A07BCB\
        "MY_DEFINES=$(RECOVERY_DEFINES)"\
		ENTRY_POINT=RecoveryEntry\
		"INIT_LIST=$(RecoveryInitialize)"\
		TYPE=PEIM COMPRESS=1

#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**             5555 Oakbrook Pkwy, Norcross, GA 30093               **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************
