#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2014, American Megatrends, Inc.            **
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
# $Header: /Alaska/SOURCE/Modules/SecureFlashPkg/FlashUpdate/SecFlashUpd.mak 17    9/30/14 3:34p Alexp $
#
# $Revision: 17 $
#
# $Date: 9/30/14 3:34p $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SecureFlashPkg/FlashUpdate/SecFlashUpd.mak $
# 
# 17    9/30/14 3:34p Alexp
# EIP185686:Build error with Recovery_SUPPORT = 0
# 
# 16    3/18/14 3:02p Alexp
# year '2014' in file hdr & ftr
# 
# 15    4/19/13 4:48p Alexp
# add external define 
# 
# 14    11/21/12 10:36a Alexp
# don not link cryptolib
# 
# 13    10/31/12 10:09a Alexp
# EIP#100418: Make SecureFlashPkg build independent 
# from Core's ReFlash driver Support
# 
# 12    9/06/12 6:15p Alexp
# EIP#100418: Make SecureFlashPkg build independant from ReFlash-Support
# 
# 11    7/13/12 12:11p Alexp
# Replace custom _EFI_CAPSULE_BLOCK_DESCRIPTOR_ with 
# generic EFI_CAPSULE_BLOCK_DESCRIPTOR
# 
# 10    5/18/12 4:22p Alexp
# 1. Link Crypto Library with VerifyFwCap in Recovery boot flow.Use Hash
# functions only
# 2. Pass SEC_FLASH_GUID_DEFINES containing unique FwCap Ffs Guid and
# Section guids
# 
# 9     12/08/11 4:51p Alexp
# Change method of calling IsSecRecovery init routine ->
# ->Replaced IsSecRecovery PEI with function call IsFlashUpdateRecovery
# from PeiCoreInitialize
# 
# 8     11/10/11 4:36p Alexp
# Add build rules to generate SecFlashDxe driver
# 
# 7     11/03/11 6:38p Alexp
# create build rules for IsSecRecovery.ffs PEI module
# 
# 6     10/17/11 11:33a Alexp
# Replace old method to detect FlashUpd with single IsFlashUpdate() hook
# to be called from SbPei.c ->GetBootMode
# 
# 5     8/22/11 5:22p Alexp
# removed build rules for SecFlash Setup pages 
# 
# 4     8/18/11 4:45p Alexp
# removed unused build target:SecFlashUpdDxeBin
# 
# 3     8/05/11 3:18p Alexp
# removed Flash Policy driver, files, Protocol; Flash Policy is hardwired
# via SDL
# 
# 2     7/20/11 7:16p Alexp
# remove dependency on Capsule module
# 
# 1     7/01/11 4:39p Alexp
# 
# 
#*************************************************************************
#<AMI_FHDR_START>
#
# Name: SecFlashUpd.mak
#
# Description:
#
#
#<AMI_FHDR_END>
#*************************************************************************
SecureModule: SecureFlashUpdate

SecureFlashUpdate : $(BUILD_DIR)\SecFlashUpd.mak SecFlashUpdDxeBin \
!IF $(Recovery_SUPPORT) == 1
FwCapsuleRecoveryPPIBin
!ENDIF

$(BUILD_DIR)\SecFlashUpd.mak : $(SecFlashUpd_DIR)\SecFlashUpd.cif $(SecFlashUpd_DIR)\SecFlashUpd.mak $(BUILD_RULES)
    $(CIF2MAK) $(SecFlashUpd_DIR)\SecFlashUpd.cif $(CIF2MAK_DEFAULTS)

BUILD_SecFlashUpd_DIR = $(BUILD_DIR)\$(SecFlashUpd_DIR)

!IFDEF ReFlash_SUPPORT
SecFlashUpd_DEFINES= \
    /D ReFlash_SUPPORT=$(ReFlash_SUPPORT)
!ENDIF

SecFlashUpd_INCLUDES= \
    /I $(SecFlashUpd_DIR)\
    $(SEC_FLASH_GUID_DEFINES)\
!IFDEF ReFlash_DIR
    /I $(ReFlash_DIR)\
!ENDIF
    /I$(CORE_DIR)

AMI_CSP_LIB_INCLUDE_FILES = "Include\FlashUpd.h" + \
$(AMI_CSP_LIB_INCLUDE_FILES)

AMI_CSP_LIB_OBJS = $(AMI_CSP_LIB_OBJS) \
$(BUILD_DIR)\IsSecRecovery.obj
#-----------------------------------------------------------------------
# Auxilary library files compilation
#-----------------------------------------------------------------------
RecoveryBin FwCapsuleRecoveryPPIBin : $(BUILD_DIR)\VerifyFwCapsule.obj $(CRYPTOLIBPEI)

{$(SecFlashUpd_DIR)}.c{$(BUILD_DIR)}.obj::
	$(CC) $(CFLAGS) $(SEC_FLASH_GUID_DEFINES) /I $(SecFlashUpd_DIR) /Fo$(BUILD_DIR)\ $< 

SecFlashUpdDxeBin : $(AMIDXELIB)
    $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
        /f $(BUILD_DIR)\SecFlashUpd.mak all\
        NAME=SecFlashUpdDxe\
        MAKEFILE=$(BUILD_DIR)\SecFlashUpd.mak \
        GUID=A0EF80E3-F9AB-4CBA-98FD-704620F4048D \
        ENTRY_POINT=SecFlashUpdDxe_Init\
        DEPEX1=$(SecFlashUpd_DIR)\SecFlashUpdDxe.DXS DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX\
        "MY_INCLUDES=$(SecFlashUpd_INCLUDES) "\
        "CFLAGS=$(CFLAGS) $(SecFlashUpd_DEFINES)" \
        OBJECTS="$(BUILD_SecFlashUpd_DIR)\SecFlashUpdDxe.obj" \
        TYPE=RT_DRIVER COMPRESS=1

!IF $(CORE_COMBINED_VERSION) < 0x4028e
FwCapsuleRecoveryPPIBin : $(AMIPEILIB) $(BUILD_DIR)\$(BOARD_DIR)\ReportFV2.obj
!ELSE
FwCapsuleRecoveryPPIBin : $(AMIPEILIB)
!ENDIF
    $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
        /f $(BUILD_DIR)\SecFlashUpd.mak all\
        NAME=FwCapsuleRecoveryPPI\
        MAKEFILE=$(BUILD_DIR)\SecFlashUpd.mak \
        GUID=83FA5AED-5171-4949-BDC9-0CBC9E123663 \
        ENTRY_POINT=EFICapsuleRecoveryPeimEntry \
#        "MY_INCLUDES=$(SecFlashUpd_INCLUDES) /I $(Recovery_DIR)"\
        "MY_INCLUDES=$(SecFlashUpd_INCLUDES)"\
        OBJECTS="$(BUILD_SecFlashUpd_DIR)\EfiCapsuleRecovery.obj" \
        DEPEX1=$(SecFlashUpd_DIR)\EfiCapsuleRecovery.DXS DEPEX1_TYPE=EFI_SECTION_PEI_DEPEX \
        TYPE=PEIM COMPRESS=1

#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2014, American Megatrends, Inc.            **
#**                                                                     **
#**                       All Rights Reserved.                          **
#**                                                                     **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
#**                                                                     **
#**                       Phone: (770)-246-8600                         **
#**                                                                     **
#*************************************************************************
#*************************************************************************
