#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
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
# $Header: /Alaska/SOURCE/Modules/OpalSecurity/OPALSECURITY/OpalSecurity.mak 1     5/19/11 2:07a Anandakrishnanl $
#
# $Revision: 1 $
#
# $Date: 5/19/11 2:07a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/OpalSecurity/OPALSECURITY/OpalSecurity.mak $
# 
# 1     5/19/11 2:07a Anandakrishnanl
# Opal Security Module Initial Check In
# 
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:           OpalSecurity.mak
#
# Description:    Make file to build OpalSecurity module
#
#<AMI_FHDR_END>
#**********************************************************************
all : OpalSecurity

OpalSecurity : $(BUILD_DIR)\OpalSecurity.mak OpalSecurityBin

$(BUILD_DIR)\OpalSecurity.mak : $(OpalSecurity_DIR)\$(@B).cif $(OpalSecurity_DIR)\$(@B).mak $(BUILD_RULES)
    $(CIF2MAK) $(OpalSecurity_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

OpalSecurityBin : $(AMIDXELIB)
    $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
        /f $(BUILD_DIR)\OpalSecurity.mak all\
        GUID=59AF16B0-661D-4865-A381-38DE68385D8D\
        ENTRY_POINT=OpalSecEntryPoint\
        TYPE=BS_DRIVER \
        COMPRESS=1\

#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************