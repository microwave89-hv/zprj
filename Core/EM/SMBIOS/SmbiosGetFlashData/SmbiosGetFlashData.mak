#//**********************************************************************//
#//**********************************************************************//
#//**                                                                  **//
#//**        (C)Copyright 1985-2009, American Megatrends, Inc.         **//
#//**                                                                  **//
#//**                       All Rights Reserved.                       **//
#//**                                                                  **//
#//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **//
#//**                                                                  **//
#//**                       Phone: (770)-246-8600                      **//
#//**                                                                  **//
#//**********************************************************************//
#//**********************************************************************//

#************************************************************************//
# $Header: /Alaska/SOURCE/Modules/SMBIOS/SmbiosGetFlashData/SmbiosGetFlashData.mak 6     8/04/10 2:45p Davidd $
#
# $Revision: 6 $
#
# $Date: 8/04/10 2:45p $
#************************************************************************//
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SMBIOS/SmbiosGetFlashData/SmbiosGetFlashData.mak $
# 
# 6     8/04/10 2:45p Davidd
# Remove environment variables "MAKEFILE" and "INCLUDE" - EIP 40634.
# 
# 5     6/02/09 11:23a Davidd
# Updated AMI header section (EIP 22180)
# 
# 4     1/28/09 11:54a Davidd
# New changes added to support DMIEdit data storage location in flash
# selectable via SMBIOS_DMIEDIT_DATA_LOC SDL token
# 
# 3     12/30/08 3:24p Davidd
# Changes added for x32 and x64 binary support.
# 
# 2     3/29/07 6:08p Davidd
# Changed the year in the AMI banner.
# 
# 1     4/29/05 2:07p Davidd
# Initial checkin.
#
#************************************************************************//

!IF "$(SMBIOS_DMIEDIT_DATA_LOC)"!="2"
all : SMBIOS_GETFLASHDATA_SUPPORT

SMBIOS_GETFLASHDATA_SUPPORT : $(BUILD_DIR)\SmbiosGetFlashData.mak SmbiosGetFlashDataBin

$(BUILD_DIR)\SmbiosGetFlashData.mak : $(SMBIOS_GETFLASHDATA_DIR)\$(@B).cif $(SMBIOS_GETFLASHDATA_DIR)\$(@B).mak $(BUILD_RULES)
        $(CIF2MAK) $(SMBIOS_GETFLASHDATA_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

SmbiosGetFlashDataBin : $(AMIDXELIB)
        $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
                /f $(BUILD_DIR)\SmbiosGetFlashData.mak all\
!IF "$(x64_BUILD)"=="1"
                NAME=SmbiosGetFlashData64 \
!ELSE
                NAME=SmbiosGetFlashData32 \
!ENDIF
                MAKEFILE=$(BUILD_DIR)\SmbiosGetFlashData.mak\
                GUID=DED7956D-7E20-4f20-91A1-190439B04D5B \
                ENTRY_POINT=SmbiosGetFlashDataInstall \
                TYPE=BS_DRIVER \
                COMPRESS=1\
!ENDIF

#//**********************************************************************//
#//**********************************************************************//
#//**                                                                  **//
#//**        (C)Copyright 1985-2009, American Megatrends, Inc.         **//
#//**                                                                  **//
#//**                       All Rights Reserved.                       **//
#//**                                                                  **//
#//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **//
#//**                                                                  **//
#//**                       Phone: (770)-246-8600                      **//
#//**                                                                  **//
#//**********************************************************************//
#//**********************************************************************//
