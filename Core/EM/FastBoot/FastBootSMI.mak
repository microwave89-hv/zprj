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
#*************************************************************************
# $Header: /Alaska/SOURCE/Modules/PTT/FastBootSMI.mak 1     3/11/11 10:07p Bibbyyeh $
#
# $Revision: 1 $
#
# $Date: 3/11/11 10:07p $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/PTT/FastBootSMI.mak $
# 
# 1     3/11/11 10:07p Bibbyyeh
# [TAG]		EIP54993
# [Category]	Improvement
# [Description]
# 1.Sync with Fastboot_10
# 2.Remove token "SAVE_LAST_BOOT_DEVICE_CHECKSUM"
# 3.Add token "CALL_DISPATCHER_AGAIN_IN_FASTBOOT"
# 4.Use SimpleText protocol to detect mode change hotkey instead of
# pBS->ConIn.
# 5.Simplify the code about "AMILEGACY16_FASTBOOT_SOLUTION".
# 6.Fixed a bug that SATA device can't be found if keep TSE execution on
# fastboot path.
# [Files]		PPT.cif FastBoot.sdl FastBootRuntime.c FastBootTseHook.c
# FastBoot.c FastBoot.h FastBoot.sd FastBootProtocol.cif
# FastBootProtocol.h FastBootSMI.cif FastBootSMI.sdl FastBootSMI.c
# FastBootSMI.dxs FastBootSMI.mak
# 
#
#*************************************************************************
#<AMI_FHDR_START>
#
# Name: FastBootSMI.mak 
#
# Description: Make file for FastBoot SMI.
#
#<AMI_FHDR_END>
#*************************************************************************

all : FastBootSMI

FastBootSMI:$(BUILD_DIR)\FastBootSMI.mak FastBootSMIBin

$(BUILD_DIR)\FastBootSMI.mak : $(FastBootSMI_DIR)\FastBootSMI.cif $(FastBootSMI_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(FastBootSMI_DIR)\FastBootSMI.cif $(CIF2MAK_DEFAULTS)


FastBootSMIBin : $(AMIDXELIB) $(AMICSPLib)
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\FastBootSMI.mak all\
		GUID=D122882C-DA73-438B-A6B3-E07B7D18DB6F\
		ENTRY_POINT=FastBootSMIEntryPoint\
		TYPE=BS_DRIVER \
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

