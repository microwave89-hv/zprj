#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1987-2013, American Megatrends, Inc.            **
#**                                                                     **
#**                       All Rights Reserved.                          **
#**                                                                     **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30071           **
#**                                                                     **
#**                       Phone: (770)-246-8600                         **
#**                                                                     **
#*************************************************************************
#*************************************************************************

#**********************************************************************
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/FIT/Fit.mak 16    6/04/13 3:48a Bensonlai $
#
# $Revision: 16 $
#
# $Date: 6/04/13 3:48a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/FIT/Fit.mak $
# 
# 16    6/04/13 3:48a Bensonlai
# [TAG]  		EIP125148
# [Category]  	Spec Update
# [Severity]  	Normal
# [Description]  	[SBY ULT] Boot Guard for 4th Gen Intel Core Processor
# based on Mobile U-Processor Line - BIOS Writer's Guide - Rev 1.0
#
# 15    5/23/13 4:41a Bensonlai
# [TAG]  		EIP124550
# [Category]  	New Feature
# [Description]  	Support signing server for Boot Guard
#
# 14    5/13/13 4:42a Bensonlai
#
# 13    3/27/13 1:19a Bensonlai
# [TAG]  		EIP118856
# [Category]  	Spec Update
# [Severity]  	Critical
# [Description]  	[SBY ULT] Boot Guard ACM SDK Rev 1.0 PV Release for
# Shark Bay ULT Platforms
# [Files]  		Boot_Guard_ACM_Rev1_0_ES.bin, Boot_Guard_ACM_Rev1_0_QS.bin,
# Boot_Guard_ACM_Rev1_0_PV.bin, BpmKmGen.exe, Fit.cif, Fit.sdl, Fit.mak
#
# 12    3/20/13 12:02a Bensonlai
# [TAG]  		EIP118400
# [Category]  	Improvement
# [Description]  	Add a token for attribution of FV_DATA
# [Files]  		Fit.mak, Fit.sdl
#
# 11    3/06/13 2:49a Bensonlai
# [TAG]  		EIP116907
# [Category]  	Improvement
# [Description]  	BpmKmGen.exe generates KM / BPM tables and
# BootGuardFvMainHash key separately
# [Files]  		BpmKmGen.exe, Fit.sdl, Fit.mak, BootGuardPei.sdl,
# BootGuardDxe.sdl
#
# 10    2/27/13 4:39a Bensonlai
# [TAG]  		None
# [Category]  	Improvement
# [Description]  	Removing the FV_BLANK
#
# 9     2/25/13 1:21a Bensonlai
# [TAG]  		EIP114386
# [Category]  	Spec Update
# [Severity]  	Important
# [Description]  	[SBY] Ultrabook for Shark Bay Platform - : Boot Guard
# for 4th Gen Intel Core Processor based on Mobile U-Processor Line -
# BIOS Writer's Guide - Rev 0.8.1
# [Files]  		FIT\*.*
#
# 8     1/14/13 1:57a Bensonlai
# [TAG]  		EIP110952
# [Category]  	New Feature
# [Description]  	[SBY] Anchor Cove function to continue chain of trust
# for verification
# [Files]  		AnchorCovePei.cif, AnchorCovePei.c, AnchorCovePei.h,
# AnchorCovePei.dxs, AnchorCovePei.sdl, AnchorCovePei.mak,
# PeiCryptLib.lib, OpensslLib.lib
# AnchorCoveDxe.c, AnchorCoveDxe.h, AnchorCoveDxe.sdl, AnchorCoveDxe.dxs,
# AnchorCoveDxe.mak
# FITUtil.exe, BpmKmGen.exe, Fit.mak, ReserveAnchorCoveFvMainHashKey.bin
#
# 7     1/04/13 5:56a Bensonlai
# [TAG] EIP110784
# [Category] Improvement
# [Description] Anchor Cove ACM SDK Rev0.8 Beta Release for Shark Bay ULT
# Platforms.
# [Files] AnC_ACM_Rev0_8.bin, FitTable.asm, Fit.sdl, FITUtil.exe,
# BpmKmGen.exe, ReserveBpmTable.bin
#
# 6     12/21/12 4:08a Bensonlai
# [TAG]  		EIP110217
# [Category]  	New Feature
# [Description]  	Support Fault Tolerant Boot Block Update for Intel FIT
# [Files]  		Fit.mak, Fit.sdl, FITUtil.exe
#
# 5     12/12/12 6:15a Bensonlai
# [TAG]  		EIP108904
# [Category]  	Improvement
# [Description]  	GenFFS utility is not PI 1.2 compliant.
# Please use FWBuild to generate FFS for FIT.
#
# GenFFS utility will populate signature "5A" for FFS with fixed
# checksum.
# PI 1.2 requires this signature to be "AA". GenFFS does not support
# passing PI version.Please check the attachment to change Genffs usage
# to FWBuild.
# [Files]  		Fit.mak, Fit.sdl
#
# 4     11/12/12 1:03a Bensonlai
# [TAG]  		None
# [Category]  	Bug Fix
# [Severity]  	Critical
# [Symptom]  	Fixed build error when disabled ULT_SUPPORT
# [RootCause]  	We don't detect the Anchor Cove flag.
# [Solution]  	Add Anchor Cove flag.
#
# 3     11/09/12 3:34a Bensonlai
# [TAG]  		EIP104159
# [Category]  	New Feature
# [Description]  	Supported ULT Anchor Cove BIOS Writer's Guide - Rev
# 0.7.1
#
# 2     10/04/12 1:42a Bensonlai
# [TAG]  		None
# [Category]  	New Feature
# [Description]  	1. Implementation of the Intel Anchor Cove for mobile
# platforms.
# 2. Implementation of FIT table using FFS.
# 3. Updated the FITUtil.exe to support the ACM, KM and BPM for Intel
# Anchor Cove.
# [Files]  		Fit.sdl
# Fit.mak
# FitTable.asm
# BpmTable.asm
# KmTable.asm
# FITUtil.exe
# Fit.cif
#
# 1     6/19/12 11:26p Davidhsieh
#
#**********************************************************************
#<AMI_FHDR_START>
#
# Name: Fit.mak
#
# Description:	MAK file for Intel FIT module building
#
#<AMI_FHDR_END>
#**********************************************************************
!IF "$(INTEL_BOOT_GUARD_SUPPORT)"=="1"
!IF "$(IS_FV_DATA_ALIGNMENT64K)"!="0"
!ERROR The FV_DATA_BASE needs to align 64K, please check your FV_BB_BASE or FV_DATA_BASE for Boot Guard
!ENDIF
!ENDIF

all : $(BUILD_DIR)\Fit.mak FitTableBin

$(BUILD_DIR)\Fit.mak : $(FIT_DIR)\$(@B).cif $(FIT_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(FIT_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

!IF "$(INTEL_BOOT_GUARD_SUPPORT)"=="1"
!IF "$(INTEL_BOOT_GUARD_SIGNING_SERVER_SUPPROT)"=="1"
FitTableBin : $(BUILD_DIR)\FitTable.ffs $(BUILD_DIR)\BootGuardBpmBinary.ffs $(BUILD_DIR)\BootGuardKmBinary.ffs $(BUILD_DIR)\BootGuardAcmBinary.ffs $(BUILD_DIR)\ReserveBootGuardFvMainHashKey.ffs $(BUILD_DIR)\ReserveBootGuardSigningServer.ffs
!ELSE
FitTableBin : $(BUILD_DIR)\FitTable.ffs $(BUILD_DIR)\BootGuardBpmBinary.ffs $(BUILD_DIR)\BootGuardKmBinary.ffs $(BUILD_DIR)\BootGuardAcmBinary.ffs $(BUILD_DIR)\ReserveBootGuardFvMainHashKey.ffs
!ENDIF
!ELSE
FitTableBin : $(BUILD_DIR)\FitTable.ffs
!ENDIF

$(BUILD_DIR)\FitTable.bin : $(FIT_DIR)\FitTable.asm $(BUILD_DIR)\Fit.mak
    $(MAKE) /$(MAKEFLAGS)\
    /f $(BUILD_DIR)\Fit.mak bin\
    OBJECTS=$(BUILD_DIR)\$(FIT_DIR)\FitTable.obj\
    NAME=FitTable\
    MAKEFILE=$(BUILD_DIR)\Fit.mak \
    TYPE=BINARY

$(BUILD_DIR)\FitTable.ffs : $(BUILD_DIR)\FitTable.bin
    $(MAKE) /f Core\FFS.mak \
    BUILD_DIR=$(BUILD_DIR) \
    GUID=B52282EE-9B66-44B9-B1CF-7E5040F787C1\
    TYPE=EFI_FV_FILETYPE_RAW \
    FFS_ALIGNMENT=1 FFS_CHECKSUM=0\
    RAWFILE=$(BUILD_DIR)\FitTable.bin FFSFILE=$(BUILD_DIR)\FitTable.ffs COMPRESS=0 NAME=FitTable

$(BUILD_DIR)\$(BootGuardBpmBinary) :
    copy $(FIT_DIR)\$(BootGuardBpmBinary) $(BUILD_DIR)\$(BootGuardBpmBinary) $(SILENT_OUT)

$(BUILD_DIR)\BootGuardBpmBinary.ffs : $(BUILD_DIR)\$(BootGuardBpmBinary)
    $(MAKE) /f Core\FFS.mak \
    BUILD_DIR=$(BUILD_DIR) \
    GUID=C30FFF4A-10C6-4C0F-A454-FD319BAF6CE6\
    TYPE=EFI_FV_FILETYPE_RAW \
    FFS_ALIGNMENT=1 FFS_CHECKSUM=0\
    RAWFILE=$(BUILD_DIR)\$(BootGuardBpmBinary) FFSFILE=$(BUILD_DIR)\BootGuardBpmBinary.ffs COMPRESS=0 NAME=BootGuardBpmBinary

$(BUILD_DIR)\$(BootGuardKmBinary) :
    copy $(FIT_DIR)\$(BootGuardKmBinary) $(BUILD_DIR)\$(BootGuardKmBinary) $(SILENT_OUT)

$(BUILD_DIR)\BootGuardKmBinary.ffs : $(BUILD_DIR)\$(BootGuardKmBinary)
    $(MAKE) /f Core\FFS.mak \
    BUILD_DIR=$(BUILD_DIR) \
    GUID=7C9A98F8-2B2B-4027-8F16-F7D277D58025\
    TYPE=EFI_FV_FILETYPE_RAW \
    FFS_ALIGNMENT=1 FFS_CHECKSUM=0\
    RAWFILE=$(BUILD_DIR)\$(BootGuardKmBinary) FFSFILE=$(BUILD_DIR)\BootGuardKmBinary.ffs COMPRESS=0 NAME=BootGuardKmBinary

$(BUILD_DIR)\$(BootGuardAcmBinary) :
    copy $(FIT_DIR)\$(BootGuardAcmBinary) $(BUILD_DIR)\$(BootGuardAcmBinary) $(SILENT_OUT)

$(BUILD_DIR)\BootGuardAcmBinary.ffs : $(BUILD_DIR)\$(BootGuardAcmBinary)
    $(MAKE) /f Core\FFS.mak \
    BUILD_DIR=$(BUILD_DIR) \
    GUID=6520F532-2A27-4195-B331-C0854683E0BA\
    TYPE=EFI_FV_FILETYPE_RAW \
    FFS_ALIGNMENT=7 FFS_CHECKSUM=1\
    RAWFILE=$(BUILD_DIR)\$(BootGuardAcmBinary) FFSFILE=$(BUILD_DIR)\BootGuardAcmBinary.ffs COMPRESS=0 NAME=BootGuardAcmBinary

RESERVE_BOOT_GUARD_FV_MAIN_HASH_KEY_FFS_FILE_RAW_GUID = CBC91F44-A4BC-4a5b-8696-703451D0B053

$(BUILD_DIR)\ReserveBootGuardFvMainHashKey.ffs : $(FIT_DIR)\ReserveBootGuardFvMainHashKey.bin
    $(MAKE) /f Core\FFS.mak \
    BUILD_DIR=$(BUILD_DIR) \
    GUID=$(RESERVE_BOOT_GUARD_FV_MAIN_HASH_KEY_FFS_FILE_RAW_GUID)\
    TYPE=EFI_FV_FILETYPE_FREEFORM \
    FFS_ALIGNMENT=1 FFS_CHECKSUM=0\
    BINFILE=$** FFSFILE=$@ COMPRESS=0 NAME=ReserveBootGuardFvMainHashKey

RESERVE_BOOT_GUARD_SIGNING_SERVER_FFS_FILE_RAW_GUID = 1068E0ED-5C8E-4724-B011-2C5F95065DF2

$(BUILD_DIR)\ReserveBootGuardSigningServer.ffs : $(FIT_DIR)\ReserveBootGuardSigningServer.bin
    $(MAKE) /f Core\FFS.mak \
    BUILD_DIR=$(BUILD_DIR) \
    GUID=$(RESERVE_BOOT_GUARD_SIGNING_SERVER_FFS_FILE_RAW_GUID)\
    TYPE=EFI_FV_FILETYPE_FREEFORM \
    FFS_ALIGNMENT=1 FFS_CHECKSUM=0\
    BINFILE=$** FFSFILE=$@ COMPRESS=0 NAME=ReserveBootGuardSigningServer

AFTER_FV:
FV_DATA_DESCRIPTOR=FV(\
    name=FV_DATA, address=$(FV_DATA_BASE),\
    offset=$(FV_DATA_BASE)-$(FLASH_BASE),\
    size=$(FV_DATA_SIZE), file_list=$(FV_DATA),\
    attr=$(FV_DATA_ATTR),\
)

FIT_UCODE_FIXUP:
!IF "$(INTEL_BOOT_GUARD_SUPPORT)"=="1"
    if not exist $(BOOT_GUARD_BPM_PRIVATE_KEY_FILENAME)     $(FIT_DIR)\keygen.exe $(BOOT_GUARD_BPM_PRIVATE_KEY_FILENAME) $(BOOT_GUARD_BPM_PUBLIC_KEY_FILENAME) $(BOOT_GUARD_PBULIC_KEY_EXPONENT)
    if not exist $(BOOT_GUARD_KM_PRIVATE_KEY_FILENAME)      $(FIT_DIR)\keygen.exe $(BOOT_GUARD_KM_PRIVATE_KEY_FILENAME) $(BOOT_GUARD_KM_PUBLIC_KEY_FILENAME) $(BOOT_GUARD_PBULIC_KEY_EXPONENT)
    if exist $(BOOT_GUARD_BPM_PUBLIC_KEY_FILENAME)          del $(BOOT_GUARD_BPM_PUBLIC_KEY_FILENAME)
    if exist $(BOOT_GUARD_KM_PUBLIC_KEY_FILENAME)           del $(BOOT_GUARD_KM_PUBLIC_KEY_FILENAME)
!ENDIF
    $(FIT_DIR)\FITUtil.exe $(AMI_ROM) $(FITEntryPointToOtherFVBBRomAddress)
!IF "$(INTEL_BOOT_GUARD_SUPPORT)"=="1"

!IF "$(INTEL_BOOT_GUARD_CHAIN_OF_TRUST_SUPPORT)"=="1"
    $(FIT_DIR)\BpmKmGen.exe -PFVMAIN $(AMI_ROM) $(FIT_DIR) $(BIOS_STARTING_ADDRESS) $(DXE_SEGMENT_BASE) $(DXE_SEGMENT_SIZE)
!ENDIF

!IF "$(INTEL_BOOT_GUARD_SIGNING_SERVER_SUPPROT)"=="1"
    $(FIT_DIR)\BpmKmGen.exe -SDATA $(AMI_ROM) $(BootGuardTokens)
    $(FIT_DIR)\BpmKmGen.exe -SBPMKM $(AMI_ROM) $(FIT_DIR) $(BOOT_GUARD_BPM_PRIVATE_KEY_FILENAME) $(BOOT_GUARD_KM_PRIVATE_KEY_FILENAME)
!ELSE
    $(FIT_DIR)\BpmKmGen.exe -PBPMKM $(AMI_ROM) $(FIT_DIR) $(BOOT_GUARD_BPM_PRIVATE_KEY_FILENAME) $(BOOT_GUARD_KM_PRIVATE_KEY_FILENAME) $(BootGuardTokens)
!ENDIF

!ENDIF

AFTER_ROM: FIT_UCODE_FIXUP

#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1987-2013, American Megatrends, Inc.            **
#**                                                                     **
#**                       All Rights Reserved.                          **
#**                                                                     **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30071           **
#**                                                                     **
#**                       Phone: (770)-246-8600                         **
#**                                                                     **
#*************************************************************************
#*************************************************************************
