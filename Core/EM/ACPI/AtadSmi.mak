#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
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
# $Header: /Alaska/BIN/Modules/ACPI/Template/Core/AtadSmi.mak 1     1/23/14 5:47p Oleksiyy $
#
# $Revision: 1 $
#
# $Date: 1/23/14 5:47p $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Modules/ACPI/Template/Core/AtadSmi.mak $
# 
# 1     1/23/14 5:47p Oleksiyy
# [TAG]  		EIP113941
# [Category]  	New Feature
# [Description]  	Time and Alarm ACPI device implemented.
# [Files]  		AtadSmi.cif
# AtadSmi.sdl
# AtadSmi.mak
# AtadSmi.dxs
# AtadSmi.h
# AtadSmi.c
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
all: AtadSmi

AtadSmi: $(BUILD_DIR)\AtadSmi.mak AtadSmiBin

$(BUILD_DIR)\AtadSmi.mak : $(AtadSmi_DIR)\$(@B).cif $(AtadSmi_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(AtadSmi_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

AtadSmiBin : $(AMIDXELIB)
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\AtadSmi.mak all\
		GUID=88F34ACA-3A7B-FF3C-D401-16A3B6834F2A\
		ENTRY_POINT=AtadSmiEntry\
!IF $(PI_SPECIFICATION_VERSION)<0x00001000A
        TYPE=BS_DRIVER\
!ELSE
        TYPE=SMM_DRIVER\
!ENDIF
        DEPEX1=$(AtadSmi_DIR)\AtadSmi.dxs\
        DEPEX1_TYPE=EFI_SECTION_SMM_DEPEX\
        "EXT_HEADERS=$(BUILD_DIR)\Token.h"\
        COMPRESS=1

#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************