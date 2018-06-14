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
# $Header: /Alaska/BIN/Modules/ACPI/Template/S3Support/S3Restore/S3Restore.mak 2     3/18/11 3:51p Oleksiyy $
#
# $Revision: 2 $
#
# $Date: 3/18/11 3:51p $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Modules/ACPI/Template/S3Support/S3Restore/S3Restore.mak $
# 
# 2     3/18/11 3:51p Oleksiyy
# [TAG]  		EIP53402 
# [Category]  	Improvement
# [Description]  	Improving backward computability and architecture.
# [Files]  		ACPI.mak, AcpiCore.cif, S3Save.cif, S3Save.mak,
# S3Restore.mak, BootScriptExecutor.c, S3Common.cif, S3SaveState.h,
# S3smmSaveState.h
# 
# 1     2/03/11 4:09p Oleksiyy
# [TAG]  		EIP53402 
# [Category]  	Improvement
# [Description]  	Create new label of ACPI with separate S3 Functionality
# [Files]  		S3Restore.cif
# S3Restore.sdl
# S3Restore.mak
# S3Resume.dxs
# AcpiS3Wake.asm
# S3Resume.c
# AcpiPeiS3Func.c
# AcpiPeiS3Func.h
# BootScriptExecuter.c
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
all : S3Restore

S3Restore : $(BUILD_DIR)\S3Restore.mak S3RestoreBin

$(BUILD_DIR)\S3Restore.mak : $(S3Restore_DIR)\$(@B).cif $(S3Restore_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(S3Restore_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

S3RestoreBin : $(AMIPEILIB) $(AMICSPLib)
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\S3Restore.mak all\
		GUID=EFD652CC-0E99-40f0-96C0-E08C089070FC \
		ENTRY_POINT=S3ResumeEntryPoint\
        "MY_INCLUDES=/I$(ACPI_CORE_DIR)" \
		DEPEX1=$(S3Restore_DIR)\S3Resume.DXS \
        DEPEX1_TYPE=EFI_SECTION_PEI_DEPEX \
		TYPE=PEIM \
		COMPRESS=0
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
