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
# $Header: /Alaska/SOURCE/Modules/PEI Ram Boot/PeiRamBoot.mak 13    10/02/14 4:44a Calvinchen $
#
# $Revision: 13 $
#
# $Date: 10/02/14 4:44a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/PEI Ram Boot/PeiRamBoot.mak $
# 
# 13    10/02/14 4:44a Calvinchen
# [TAG]  		EIP184075
# [Category]  	Improvement
# [Description]  	[HWR]FtRecovery support for Intel Top Swap
# Modified PeiRamBoot module for multiple Boot Block Volumes support.
# [Files]  		PeiRamBoot.sdl
# PeiRamBoot.mak
# PeiRamBoot.c
# PeiRamBoot.chm
# PeiRamBoot.cif
# 
# 12    3/18/13 6:08a Calvinchen
# Bug Fixed : Build failed if Core 4.6.5.5.
# 
# 11    7/18/12 3:41a Calvinchen
# 
# 10    2/23/12 6:35a Calvinchen
# [TAG]  		EIP82264
# [Category]  	Improvement
# [Description]  	Need to do cold boot to get the correct data in rom
# hole when changing data in rom hole.
# [Files]  		PeiRamBoot.sdl
# PeiRamBoot.mak
# PeiRamBoot.h
# PeiRamBoot.c
# PeiRamBootDxe.c
# PeiRamBoot.chm
# PeiRamBoot.cif
# 
# 9     6/21/11 2:22a Calvinchen
# ¡P Bug Fixed: 
# Bug Fixed:
# 1. Build failed if Core 4.6.4.0. 
# 2. System could hang if SAVE_ENTIRE_FV_TO_MEM = 1with AMD platform. 
# 
# 8     4/22/11 1:27a Calvinchen
# 
# 7     2/11/11 3:16a Calvinchen
# Bug Fixed : System hangs after reflashed BIOS with warm reset if
# PEI_RAM_BOOT_S3_SUPPORT = 1 with fast warm boot support.
# 
# 6     12/21/10 2:24a Calvinchen
# Added an eLink "PeiRamBootObjectsList" for oem links their obj files
# for fast warm boot support. 
# 
# 5     12/14/10 2:25a Calvinchen
# Improvement : 
# 1. Added an eLink "PeiRamBootList" for fast warm boot support
# (PEI_RAM_BOOT_S3_SUPPORT = 1). If system boots in warm boot state, BIOS
# directly boot to previous copied ROM image in RAM to save time of
# copying ROM. 
# 2. Added "PEI_RAM_BOOT_S3_SUPPORT" = "2" for saving runtime memory, it
# only keep necessary PEIM FFS in runtime memory for S3 resume
# improvement. 
# 
# 4     12/02/10 6:18a Calvinchen
# Bug Fixed : Fixed Update SMBIOS Structures failed with DMI Utility.
# 
# 3     10/27/10 3:03a Calvinchen
# Initail check-in.
# 
#
#**********************************************************************
#<AMI_FHDR_START>
#
# Name: PeiRamBoot.mak 
#
# Description: Make file for PEI Ram Boot.
#
#<AMI_FHDR_END>
#**********************************************************************
!IFNDEF PI_SPECIFICATION_VERSION
PI_SPECIFICATION_VERSION = 0
!ENDIF

all : PeiRamBoot PeiRamBootCacheRdy

#---------------------------------------------------------------------------
# Create PEI RAM BOOT dependencies
#---------------------------------------------------------------------------
$(BUILD_DIR)\PeiRamBoot.mak : $(PeiRamBoot_DIR)\$(@B).cif $(PeiRamBoot_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(PeiRamBoot_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)
#---------------------------------------------------------------------------
# Create PeiRamBoot PEI Component
#---------------------------------------------------------------------------
PeiRamBoot: $(BUILD_DIR)\$(PeiRamBoot_DIR)\RomLayout.obj $(BUILD_DIR)\PeiRamBoot.mak PeiRamBootBin

PEI_RAM_BOOT_INCLUDES =\
/I$(PeiRamBoot_DIR)\
/I$(CORE_PEI_DIR)\
!IF $(PI_SPECIFICATION_VERSION) >= 65546
/I$(CORE_PEI_DIR)\CORE_PEI_PI\
!ELSE
/I$(CORE_PEI_DIR)\CORE_PEI_FRAMEWORK\
!ENDIF
/I$(CORE_DXE_DIR)\
/I$(CORE_DIR)

PeiRamBootObjects =\
$(BUILD_DIR)\$(PeiRamBoot_DIR)\RomLayout.obj\
$(BUILD_DIR)\$(PeiRamBoot_DIR)\PeiRamBoot.obj\
$(BUILD_DIR)\$(PeiRamBoot_DIR)\PeiRamBootHook.obj\
$(PeiRamBootObjectsList)

PEI_RAM_BOOT_LISTS = \
/D\"PEI_RAM_BOOT_LIST=$(PeiRamBootList)\"\
/D\"PEI_RAM_BOOT_FV_BOOTBLOCK_LIST=$(PeiRamBootFvBootBlockList)\"\
/D\"PEI_RAM_BOOT_FFS_GUID_LIST=$(PeiRamBootFfsGuidList)\"

PeiRamBootBin : $(AMIPEILIB) $(AMICSPLib)
            $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
            /f $(BUILD_DIR)\PeiRamBoot.mak all\
            NAME=PeiRamBoot\
            MAKEFILE=$(BUILD_DIR)\PeiRamBoot.mak \
            "CFLAGS=$(CFLAGS) $(PEI_RAM_BOOT_LISTS)"\
            GUID=08efd15d-ec55-4023-b648-7ba40df7d05d \
            OBJECTS="$(PeiRamBootObjects)" \
            ENTRY_POINT=PeiRamBootEntry \
            TYPE=PEIM \
            "MY_INCLUDES=$(PEI_RAM_BOOT_INCLUDES)" \
            "MY_DEFINES=$(PEI_CORE_DEFINES)"\
            DEPEX1=$(PeiRamBoot_DIR)\PeiRamBoot.DXS \
            DEPEX1_TYPE=EFI_SECTION_PEI_DEPEX \
            COMPRESS=0

$(BUILD_DIR)\$(PeiRamBoot_DIR)\RomLayout.obj : $(BUILD_DIR)\RomLayout.c
    $(CC) /Fo$@ $(CFLAGS) $(BUILD_DIR)\RomLayout.c
#---------------------------------------------------------------------------
# Create PeiRamBoot DXE Component
#---------------------------------------------------------------------------
Runtime_LIBBin : $(BUILD_DIR)\PeiRamBootDxe.lib

$(BUILD_DIR)\PeiRamBootDxe.lib : PeiRamBootDxe

PeiRamBootDxe: $(BUILD_DIR)\PeiRamBoot.mak PeiRamBootDxeBin

PeiRamBootDxeObjs =\
$(BUILD_DIR)\$(PeiRamBoot_DIR)\PeiRamBootDxe.obj

PeiRamBootDxeBin : $(AMIDXELIB) $(AMICSPLib)
            $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
            /f $(BUILD_DIR)\PeiRamBoot.mak all\
            NAME=PeiRamBoot\
            "CFLAGS=$(CFLAGS) /I$(PeiRamBoot_DIR)"\
            OBJECTS="$(PeiRamBootDxeObjs)" \
            TYPE=LIBRARY \
            LIBRARY_NAME=$(BUILD_DIR)\PeiRamBootDxe.lib                

#---------------------------------------------------------------------------
# Create PEIRamBoot OFBD Lib Component
#---------------------------------------------------------------------------
!IF "$(PEI_RAM_BOOT_S3_SUPPORT)"=="1"
PeiRamBootOfbd : $(BUILD_DIR)\PeiRamBoot.mak PeiRamBootOfbdBin

PeiRamBootOfbdObjs = $(BUILD_DIR)\$(PeiRamBoot_DIR)\PeiRamBootOfbd.obj

PeiRamBootOfbdBin : $(AMIDXELIB)
            $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
            /f $(BUILD_DIR)\PeiRamBoot.mak all\
            "CFLAGS=$(CFLAGS:/W4=/W3) /I$(OFBD_DIR)" \
            OBJECTS="$(PeiRamBootOfbdObjs)" \
            NAME=PeiRamBoot \
            TYPE=LIBRARY LIBRARY_NAME=$(PEIRAMBOOT_OFBD_LIB)

$(PEIRAMBOOT_OFBD_LIB) : PeiRamBootOfbd
!ENDIF
#---------------------------------------------------------------------------
# Create PeiRamBoot PEI Component
#---------------------------------------------------------------------------
!IF "$(SAVE_ENTIRE_FV_IN_MEM)"=="1"
PeiRamBootCacheRdy: $(BUILD_DIR)\PeiRamBoot.mak PeiRamBootCacheRdyBin

PeiRamBootCacheRdyObjects =\
$(BUILD_DIR)\$(PeiRamBoot_DIR)\PeiRamBootCacheRdy.obj

PeiRamBootCacheRdyBin : $(AMIPEILIB) $(AMICSPLib)
            $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
            /f $(BUILD_DIR)\PeiRamBoot.mak all\
            NAME=PeiRamBootCacheRdy\
            MAKEFILE=$(BUILD_DIR)\PeiRamBoot.mak \
            "CFLAGS=$(CFLAGS) /I$(PeiRamBoot_DIR)"\
            GUID=a6a3a962-c591-4701-9d25-73d0226d89dc\
            OBJECTS="$(PeiRamBootCacheRdyObjects)" \
            ENTRY_POINT=PeiRamBootCacheRdyEntry \
            TYPE=PEIM \
            DEPEX1=$(PeiRamBoot_DIR)\PeiRamBootCacheRdy.DXS \
            DEPEX1_TYPE=EFI_SECTION_PEI_DEPEX \
            COMPRESS=1
!ELSE
PeiRamBootCacheRdy:
!ENDIF
#---------------------------------------------------------------------------
!IF "$(PRESERVE_NESTED_FV_IN_MEM)"=="1"
$(BUILD_DIR)\$(PeiRamBoot_DIR)\PeiRamBootFvHook.obj : $(PeiRamBoot_DIR)\PeiRamBootFvHook.c
!IF !EXIST($(BUILD_DIR)\$(PeiRamBoot_DIR))
	mkdir $(BUILD_DIR)\$(PeiRamBoot_DIR)
!ENDIF
    $(CC) /Fo$@ $(CFLAGS) /I$(PeiRamBoot_DIR) $(PeiRamBoot_DIR)\PeiRamBootFvHook.c

CORE_PEIBin : $(BUILD_DIR)\$(PeiRamBoot_DIR)\PeiRamBootFvHook.obj
RecoveryBin : $(BUILD_DIR)\$(PeiRamBoot_DIR)\PeiRamBootFvHook.obj
FwCapsuleRecoveryPPIBin : $(BUILD_DIR)\$(PeiRamBoot_DIR)\PeiRamBootFvHook.obj
!ENDIF

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