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
# $Header: /Alaska/SOURCE/Modules/PTT/FastBoot.mak 7     4/10/12 8:48a Bibbyyeh $
#
# $Revision: 7 $
#
# $Date: 4/10/12 8:48a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/PTT/FastBoot.mak $
# 
# 7     4/10/12 8:48a Bibbyyeh
# [TAG]           EIP87452
# [Category]      Improvement
# [Description]   1. Create an elink "ReturnNormalMode", OEM/ODM can link
# their procedure to handle the fastboot failure case. 2. Disconnect USB
# controller when return to normal mode.
# [Files]         FastBoot.c FastBoot.h FastBoot.mak FastBoot.sdl
# 
# 6     8/04/11 8:11a Bibbyyeh
# [TAG]         EIP62845
# [Category]    New Feature
# [Description] Connect all Sata devices in fastboot path.
# [Files]       FastBoot.c FastBoot.mak FastBoot.sdl
# 
# 5     7/07/11 10:04a Bibbyyeh
# [TAG]           EIP63924
# [Category]      Improvement
# [Description]   
# 1. Add elink for FastBoot mode change, default checking rule is check
# post hotkey.
# 2. Timer call back for check hotkey is not necessary. Create a protocol
# for calling checkforkey in TSE.
# 3. Since EIP68383 improve the performance of ps2 keyboard, we don't
# need to exchange the initial order of ConIn/ConOut for getting more
# time to detect hotkey.
# [Files]         FastBoot.sdl FastBoot.mak FastBoot.c FastBootTseHook.c
# FastBoot.h FastBootProtocol.h
# 
# 4     6/22/11 11:44p Bibbyyeh
# [TAG]           EIP62683
# [Category]      New Feature
# [Description]   Add an Elink after AllDriverConnect in fastboot path
# [Files]         FastBoot.c FastBoot.sdl FastBoot.mak
# 
# 3     3/02/11 2:22a Bibbyyeh
# [TAG]  		EIP51391
# [Category]  	Bug Fix
# [Severity]  	Normal
# [Symptom]  	In windows, use DmiEdit to change SMBIOS data, and update.
# SMBIOS will update failure in next boot.
# [RootCause]  	The reason cause this issue is, ROM will copy to ram in
# end of PEI phase. When SMBIOS Dxe driver update modified data to flash,
# the firmware volume block protocol is pointer to RAM, not flash. So it
# will cause update failure.
# [Solution]  	Before SMBIOS Dxe driver, restore the Base Address of
# Firmware Volume Block Protocol from RAM to ROM.
# [Files]         FastBoot.sdl FastBoot.mak FastBoot.cif
# 
# 2     2/22/11 4:04a Bibbyyeh
# [TAG]  		EIP54286
# [Category]  	Improvement
# [Description]  	Add elink for IsFastBoot Function to overwirte it, it
# can help OEM/ODM to implement their "FAST BOOT" feature easily.
# [Files]  		FastBoot.sdl FastBoot.mak FastBoot.c
# 
# 1     10/12/10 9:04a Bibbyyeh
# Initial check in
# 
#
#*************************************************************************
#<AMI_FHDR_START>
#
# Name: FastBoot.mak
#
# Description:
# Make file to build Fastboot library part
#
#<AMI_FHDR_END>
#*************************************************************************

CORE_DXEBin : $(BUILD_DIR)\FastBoot.obj $(BUILD_DIR)\FastBootDxe.obj

RUNTIMEBin : $(BUILD_DIR)\FastBootRuntime.obj

AMITSEBin : $(BUILD_DIR)\FastBootTseHook.obj

#(EIP62683)(EIP63924)(EIP62845)>
{$(FastBoot_DIR)}.c{$(BUILD_DIR)}.obj::
	$(CC) $(CFLAGS) /I $(FastBoot_DIR)  \
    /D\"IS_FAST_BOOT_LIST=$(IsFastBootList)\" \
    /D\"AFTER_ALL_DRIVER_CONNECT_HOOK=$(FastBootAfterAllDriverConnctHook)\" \
    /D\"FAST_BOOT_CHECK_MODE_CHANGE_HOOK=$(FastBootCheckModeChangeList)\" \
    /D\"BEFORE_CONNECT_FAST_BOOT_DEVICE_HOOK=$(BeforeConnectFastBootDeviceHook)\" \
    /D\"RETURN_NORMAL_MODE_HOOK=$(ReturnNormalMode)\" \
    /Fo$(BUILD_DIR)\ $<
#<(EIP62683)(EIP63924)(EIP62845)
$(BUILD_DIR)\FastBoot.obj : $(FastBoot_DIR)\FastBoot.c

$(BUILD_DIR)\FastBootRuntime.obj : $(FastBoot_DIR)\FastBootRuntime.c

$(BUILD_DIR)\FastBootTseHook.obj : $(FastBoot_DIR)\FastBootTseHook.c

$(BUILD_DIR)\FastBootDxe.obj : $(FastBoot_DIR)\FastBootDxe.c
$(BUILD_DIR)\FastBoot.mak : $(FastBoot_DIR)\FastBoot.cif $(BUILD_RULES)
    $(CIF2MAK) $(FastBoot_DIR)\FastBoot.cif $(CIF2MAK_DEFAULTS)

#---------------------------------------------------------------------------
# Create FastBoot Setup Component
#---------------------------------------------------------------------------
SetupSdbs : FastBootSDB

FastBootSDB : $(BUILD_DIR)\FastBoot.mak 
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
	/f $(BUILD_DIR)\FastBoot.mak all\
	TYPE=SDB NAME=FastBoot STRING_CONSUMERS=$(FastBoot_DIR)\FastBoot.sd

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
