#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**     5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093            **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelPfat/Pfatflashlib/HandlePfatLegacy/HandlePfatLegacy.mak 1     11/02/12 8:23p Fredericko $
#
# $Revision: 1 $
#
# $Date: 11/02/12 8:23p $
#
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelPfat/Pfatflashlib/HandlePfatLegacy/HandlePfatLegacy.mak $
# 
# 1     11/02/12 8:23p Fredericko
# [TAG]  		EIP105153
# [Files]  		HandlePfatLegacy.cif
# HandlePfatLegacy.sdl
# HandlePfatLegacy.mak
# HandlePfatLegacy.c
# 
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	HandlePfatLegacy.mak
#
# Description:	Make file for HandlePfatLegacy
#
#<AMI_FHDR_END>
#**********************************************************************
all : HandlePfatLegacy

HandlePfatLegacy : $(BUILD_DIR)\HandlePfatLegacy.mak HandlePfatLegacyBin

#---------------------------------------------------------------------------
#			
#---------------------------------------------------------------------------
$(BUILD_DIR)\HandlePfatLegacy.mak : $(HandlePfatLegacy_DIR)\$(@B).cif $(HandlePfatLegacy_DIR)\$(@B).mak $(BUILD_RULES)
    $(CIF2MAK) $(HandlePfatLegacy_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

#---------------------------------------------------------------------------
#			
#---------------------------------------------------------------------------
HandlePfatLegacyBin :  $(AMIDXELIB) 
                $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
                /f $(BUILD_DIR)\HandlePfatLegacy.mak all\
                GUID=767BECBC-7E71-4c1e-B9BD-89193022E64E\
        		ENTRY_POINT=HandlePfatLegacyBoot\
                TYPE=BS_DRIVER \
		        COMPRESS=1\
#-----------------------------------------------------------------------
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**     5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093            **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************
