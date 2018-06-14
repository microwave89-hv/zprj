#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2005, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************

#**********************************************************************
# $Header: /Alaska/SOURCE/Modules/HddSecurity/IdeSmm/IDESMM.mak 4     12/09/14 1:41a Anbuprakashp $
#
# $Revision: 4 $
#
# $Date: 12/09/14 1:41a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/HddSecurity/IdeSmm/IDESMM.mak $
# 
# 4     12/09/14 1:41a Anbuprakashp
# [TAG]  		EIP193600
# [Category]  	Improvement
# [Description]  	Security Enhancement for SMIHandler in HddSecurity
# module
# [Files]  		IDESMM.mak, IDESMM.h, IDESMM.c
# 
# 3     6/06/13 2:24a Rameshr
# [TAG]  		EIP122239
# [Category]  	Improvement
# [Description]  	IdeSmm should be part of the SMM driver
# [Files]  		IdeSmm.mak
# 
# 2     6/01/10 12:28p Krishnakumarg
# Removed Tab spaces
# 
# 1     28/02/08 6:40p Anandakrishnanl
# Created new HddSecurity module.  Isolated IdeSecurity and IdeSmm from
# IdeBus driver to be compatable with the AHCI Bus driver.
# 
# 2     13/04/07 3:08p Anandakrishnanl
# Ide Bus Module - Update source files to comply with “AMI coding
# standard"!!!
# 
# 1     12/14/05 2:57p Srinin
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name: IDESMM.mak
#
# Description:  Make file for the Idesmm component
#
#<AMI_FHDR_END>
#**********************************************************************
all : IdeSMM

IdeSMM : $(BUILD_DIR)\IdeSMM.mak IdeSMMBin

$(BUILD_DIR)\IdeSMM.mak : $(IDESMM_DIR)\$(@B).cif $(IDESMM_DIR)\$(@B).mak $(BUILD_RULES)
    $(CIF2MAK) $(IDESMM_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

IDE_SMM_INCLUDES = $(AMIDXELIB) \
                   $(BUILD_DIR)\AmiBufferValidationLib.lib

IdeSMMBin : $(IDE_SMM_INCLUDES)
    @set INCLUDE=%%INCLUDE%%
    $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
        /f $(BUILD_DIR)\IdeSMM.mak all\
        GUID=316B1230-0500-4592-8C09-EABA0FB6B07F\
        ENTRY_POINT=IdeHDDPasswordSMMInit\
!IF $(PI_SPECIFICATION_VERSION)<0x00001000A
        TYPE=BS_DRIVER\
!ELSE
        TYPE=SMM_DRIVER\
!ENDIF
        COMPRESS=1\
#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2005, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************