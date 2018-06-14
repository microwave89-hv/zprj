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
# $Header: /Alaska/SOURCE/Modules/TCG2/Common/Tpm20PlatformDxe/Tpm20PlatformDxe.mak 2     4/25/14 4:44p Fredericko $
#
# $Revision: 2 $
#
# $Date: 4/25/14 4:44p $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/TCG2/Common/Tpm20PlatformDxe/Tpm20PlatformDxe.mak $
# 
# 2     4/25/14 4:44p Fredericko
# when secureboot is disabled
# 
# 1     4/21/14 2:18p Fredericko
# 
# 1     10/08/13 12:06p Fredericko
# Initial Check-In for Tpm-Next module
# 
# 2     7/11/13 6:16p Fredericko
# [TAG]  		EIP120969
# [Category]  	New Feature
# [Description]  	TCG (TPM20).
# 
# 1     7/10/13 5:57p Fredericko
# [TAG]  		EIP120969
# [Category]  	New Feature
# [Description]  	TCG (TPM20)
# 
#*************************************************************************
#<AMI_FHDR_START>
#
# Name:	
#
# Description:	
#
#<AMI_FHDR_END>
#************************************************************************
all : Tpm20PlatformDxe

Tpm20PlatformDxe : $(BUILD_DIR)\Tpm20PlatformDxe.mak Tpm20PlatformDxeBin 

$(BUILD_DIR)\Tpm20PlatformDxe.mak : $(TPM_20_PLATFORM_DXE_DIR)\$(@B).cif $(TPM_20_PLATFORM_DXE_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(TPM_20_PLATFORM_DXE_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

Tpm20PlatformFlags=$(CFLAGS) \
	/I$(TCG_DIR)\
	/I$(TPM12_DIR)\
    /I$(CORE_DIR)\
    /I$(TCG_DIR)\Common\
	/I$(PROJECT_DIR)\Include\Protocol\
    /I$(TCG_DIR)\Protocol\
    /I$(TcgPlatformSetupPolicy_DIR)\
!IF "$(SecureBoot_SUPPORT)" == "1"
    /I$(ImageVerificationLib_DIR)\
!ENDIF

TCG20PLTFM_OBJECTS = \
$(BUILD_DIR)\$(TPM_20_PLATFORM_DXE_DIR)\Tpm20PlatformDxe.obj \

#---------------------------------------------------------------------------
#			Making AmiTcgPlatformDxe
#---------------------------------------------------------------------------

Tpm20PlatformDxeBin : $(AMIDXELIB) $(SHALIB)
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\Tpm20PlatformDxe.mak all\
        "CFLAGS=$(Tpm20PlatformFlags)"\
        "CPFLAGS=$(Tpm20PlatformFlags)"\
		GUID=0718AD81-F26A-4850-A6EC-F268E309D707 \
		ENTRY_POINT=Tpm20PlatformEntry \
		TYPE=BS_DRIVER \
        "OBJECTS=$(TCG20PLTFM_OBJECTS)"\
		DEPEX1=$(TPM_20_PLATFORM_DXE_DIR)\Tpm20PlatformDxe.dxs \
		DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX \
		COMPRESS=1 HAS_RESOURCES=1\
        "STRGATHER_FLAGS=-db $(BUILD_DIR)\$(TPM_20_PLATFORM_DXE_DIR)\Tpm20PlatformDxeString.sdb"\
#---------------------------------------------------------------------------

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
