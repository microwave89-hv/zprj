#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************

#**********************************************************************
# $Header: /Alaska/SOURCE/Modules/OFBD Intel ME Update/CSP_MEUD/ME80/MEFwUpdLcl/MEFwUpdLcl.mak 2     5/14/15 4:28a Tristinchou $
#
# $Revision: 2 $
#
# $Date: 5/14/15 4:28a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/OFBD Intel ME Update/CSP_MEUD/ME80/MEFwUpdLcl/MEFwUpdLcl.mak $
# 
# 2     5/14/15 4:28a Tristinchou
# [TAG]  		EIP215437
# [Category]  	New Feature
# [Description]  	ME capsule update support on SharkBay
# [Files]  		MEFwUpdLcl.c
# MeFwUpdLclProtocol.h
# MEFwUpdLcl.sdl
# MEFwUpdLcl.dxs
# MEFwUpdLcl.mak
# MEFwUpdLcl.cif
# 
# 1     3/05/14 3:16a Tristinchou
# [TAG]  		EIP147099
# [Category]  	Improvement
# [Description]  	Support ME FWUpdate API
# [Files]  		MEFwUpdLcl.cif
# MEFwUpdLcl.c
# MeFwUpdLclProtocol.h
# MEFwUpdLcl.sdl
# MEFwUpdLcl.dxs
# MEFwUpdLcl.mak
# IntelLib\FWUpdateLib.h
# IntelLib\me_status.h
# IntelLib\FWUpdateLib.lib
# 
# 6     1/13/10 2:13p Felixp
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	<ComponentName>.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************
all : MEFwUpdLcl

MEFwUpdLcl_LIBS=\
	$(EFIPROTOCOLLIB)\
	$(INTEL_FWUPDATE_LIB)\
	$(AMIDXELIB)\
	$(MeChipsetDxeLib_LIB)\
	$(MeLibDxe_LIB)\
	$(PchPlatformLib_LIB)\
	$(PchPlatformDxeLib_LIB)\
	$(EdkIIGlueBaseDebugLibNull_LIB)

MEFwUpdLcl_INCLUDES=\
	$(ME_INCLUDES)\
	/I Core\

MEFwUpdLcl_OBJ = \
	$(BUILD_DIR)\$(MEFwUpdLcl_DIR)\MEFwUpdLcl.obj

MEFwUpdLcl : $(BUILD_DIR)\MEFwUpdLcl.mak MEFwUpdLclBin

$(BUILD_DIR)\MEFwUpdLcl.mak : $(MEFwUpdLcl_DIR)\$(@B).cif $(MEFwUpdLcl_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(MEFwUpdLcl_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

MEFwUpdLclBin : $(MEFwUpdLcl_LIBS)
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\MEFwUpdLcl.mak all\
		"MY_INCLUDES=$(MEFwUpdLcl_INCLUDES)"\
		GUID=a11585b7-8fa2-4f1c-aa6f-dd6309469613\
		OBJECTS="$(MEFwUpdLcl_OBJ)" \
		ENTRY_POINT=MEFwUpdLclEntry\
		TYPE=BS_DRIVER \
!IF "$(MEFWUPDLCL_ON_SHARKBAY_PLATFORM)"=="0"
		DEPEX1=$(MEFwUpdLcl_DIR)\MEFwUpdLcl.dxs \
!ELSE
		DEPEX1=$(MEFwUpdLcl_DIR)\MEFwUpdLcl_SBY.dxs \
!ENDIF
		DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX \
		COMPRESS=1\

ReFlashBin : $(BUILD_DIR)\MEFwUpdLclUpdateHooks.obj

$(BUILD_DIR)\MEFwUpdLclUpdateHooks.obj : $(MEFwUpdLcl_DIR)\MEFwUpdLclUpdateHooks.c
    $(CC) /Fo$(BUILD_DIR)\MEFwUpdLclUpdateHooks.obj $(CFLAGS) $(MEFwUpdLcl_DIR)\MEFwUpdLclUpdateHooks.c
#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************