#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
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
# $Header: /Alaska/SOURCE/Modules/NvramSmi/NvramSmi.mak 4     11/28/12 3:37p Oleksiyy $
#
# $Revision: 4 $
#
# $Date: 11/28/12 3:37p $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/NvramSmi/NvramSmi.mak $
# 
# 4     11/28/12 3:37p Oleksiyy
# [TAG]  		EIP106304
# [Category]  	Improvement
# [Description]  	Separate dxs file added for
# PI_SPECIFICATION_VERSION<0x1000A scenario.
# [Files]  		NvramSmi.mak
# 
# 3     4/04/12 5:27p Oleksiyy
# [TAG]  		EIP86730
# [Category]  	Improvement
# [Description]  	Update chm file for NvramSmi module - Header
# description added.
# [Files]  		NvramSmi.dxs, NvramSmiDxe.dxs and NvramSmi.mak.
# 
# 2     12/09/11 4:01p Oleksiyy
# [TAG]  		EIP77762 
# [Category]  	Improvement
# [Description]  	Create a initial label for a created NvramSmi eModule.
# [Files]  		All files in eModule.
# 
# 1     11/11/11 3:41p Oleksiyy
# Initial CheckIn
# 
# 1     11/11/11 3:33p Oleksiyy
# 
# 2     8/12/11 12:19p Alexp
# 
# 1     6/10/11 1:01p Alexp
# 
#
#**********************************************************************
#<AMI_FHDR_START>
#
# Name: NvramSmi.mak 
#
# Description: Make file to build NvramSmi module
#
#<AMI_FHDR_END>
#**********************************************************************

all: NvramSmi

NvramSmi: $(BUILD_DIR)\NvramSmi.mak NvramSmiBin

#---------------------------------------------------------------------------
# Create PEI RAM BOOT dependencies
#---------------------------------------------------------------------------
$(BUILD_DIR)\NvramSmi.mak : $(NvramSmi_DIR)\$(@B).cif $(NvramSmi_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(NvramSmi_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)
#---------------------------------------------------------------------------

NvramSmiBin : $(AMIDXELIB)
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\NvramSmi.mak all\
		GUID=842A454A-75E5-408B-8B1C-36420E4E3F21\
		ENTRY_POINT=NvramSmiEntry\
        "CFLAGS=$(CFLAGS) /I$(NvramSmi_DIR) /I$(NVRAM_DIR)"\
        "EXT_HEADERS=$(BUILD_DIR)\token.h"\
!IF $(PI_SPECIFICATION_VERSION)<0x1000A
        DEPEX1=$(NvramSmi_DIR)\NvramSmiPi1.DXS \
        TYPE=RT_DRIVER \
!ELSE
        TYPE=DXESMM_DRIVER PE_TYPE=RT_DRIVER \
        DEPEX1=$(NvramSmi_DIR)\NvramSmi.DXS \
        DEPEX1_TYPE=EFI_SECTION_SMM_DEPEX \
        DEPEX2=$(NvramSmi_DIR)\NvramSmiDxe.DXS \
        DEPEX2_TYPE=EFI_SECTION_DXE_DEPEX \
!ENDIF
		COMPRESS=1\
#---------------------------------------------------------------------------
#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
#**                                                                     **
#**                       All Rights Reserved.                          **
#**                                                                     **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
#**                                                                     **
#**                       Phone: (770)-246-8600                         **
#**                                                                     **
#*************************************************************************
#*************************************************************************