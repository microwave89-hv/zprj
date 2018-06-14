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
# $Header: /Alaska/BIN/Modules/ACPI/Template/S3Support/S3Save/S3Save.mak 2     3/18/11 3:56p Oleksiyy $
#
# $Revision: 2 $
#
# $Date: 3/18/11 3:56p $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Modules/ACPI/Template/S3Support/S3Save/S3Save.mak $
# 
# 2     3/18/11 3:56p Oleksiyy
# [TAG]  		EIP53402 
# [Category]  	Improvement
# [Description]  	Improving backward computability and architecture.
# [Files]  		ACPI.mak, AcpiCore.cif, S3Save.cif, S3Save.mak,
# S3Restore.mak, BootScriptExecutor.c, S3Common.cif, S3SaveState.h,
# S3smmSaveState.h
# 
# 1     2/03/11 4:08p Oleksiyy
# [TAG]  		EIP53402 
# [Category]  	Improvement
# [Description]  	Create new label of ACPI with separate S3 Functionality
# [Files]  		S3Save.cif
# S3Save.sdl
# S3Save.mak
# AcpiS3.h
# AcpiS3Save.c
# BootScriptPrivate.h
# BootScriptSave.c
# AcpiS3Save.dxs
# SmmS3Save.dxs
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
all : S3Save

!IFNDEF PI_SPECIFICATION_VERSION
PI_SPECIFICATION_VERSION = 0
!ENDIF

S3Save : $(BUILD_DIR)\S3Save.mak S3SaveBin

$(BUILD_DIR)\S3Save.mak : $(S3Save_DIR)\$(@B).cif $(S3Save_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(S3Save_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

S3SaveBin : $(AMIDXELIB) 
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\S3Save.mak all\
		GUID=26A2481E-4424-46a2-9943-CC4039EAD8F8 \
		ENTRY_POINT=AcpiS3SaveEntryPoint\
        "MY_INCLUDES=/I$(ACPI_CORE_DIR)" \
!IF $(PI_SPECIFICATION_VERSION) >= 0x00001000A
		TYPE=DXESMM_DRIVER \
        DEPEX1=$(S3Save_DIR)\SmmS3Save.dxs \
        DEPEX1_TYPE=EFI_SECTION_SMM_DEPEX \
        DEPEX2=$(S3Save_DIR)\AcpiS3Save.dxs \
        DEPEX2_TYPE=EFI_SECTION_DXE_DEPEX \
!ELSE
        DEPEX1=$(S3Save_DIR)\AcpiS3Save.dxs \
		TYPE=BS_DRIVER \
!ENDIF
		COMPRESS=1\
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