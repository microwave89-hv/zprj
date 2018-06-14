#************************************************************************
#************************************************************************
#**                                                                    **
#**         (C)Copyright 1985-2009, American Megatrends, Inc.          **
#**                                                                    **
#**                        All Rights Reserved.                        **
#**                                                                    **
#**          5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093         **
#**                                                                    **
#**                        Phone: (770)-246-8600                       **
#**                                                                    **
#************************************************************************
#************************************************************************

#************************************************************************
# $Header: /Alaska/BIN/Modules/SMBIOS/SmbiosDMIEdit/SmbiosDMIEditBoard.mak 7     4/08/16 12:59p Davidd $
#
# $Revision: 7 $
#
# $Date: 4/08/16 12:59p $
#************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Modules/SMBIOS/SmbiosDMIEdit/SmbiosDMIEditBoard.mak $
# 
# 7     4/08/16 12:59p Davidd
# [TAG]  		EIP231162
# [Category]  	New Feature
# [Description]  	Merge Aptio V Smbios -09 changes for Aptio 4
# 4.6.5.5_SMBIOS_40 release
# [Files]  		SmbiosGetFlashData32.ffs
# SmbiosGetFlashData64.ffs
# Smbios32.ffs
# Smbios64.ffs
# SmbiosDmiEditBoard.mak
# SmbiosDmiEdit32.obj
# SmbiosDmiEdit64.obj
# SmbiosDmiEditFunc32.obj
# SmbiosDmiEditFunc64.obj
# 
# 6     4/20/10 12:53p Davidd
# 
# 5     6/02/09 4:49p Davidd
# Updated AMI headers (EIP 22180)
# 
# 4     12/30/08 3:17p Davidd
# Changes added for x32 and x64 binary support.
# 
# 3     3/29/07 5:18p Davidd
# Changed the year in the AMI banner.
# 
# 2     12/02/05 11:47a Felixp
# 
# 1     8/10/05 11:31a Davidd
# Initial checkin. To be used with SMBIOS Core ALPHA_01.04.
# 
# 1     8/10/05 11:18a Davidd
# New SmbiosDMIEditBoard component.
#
#************************************************************************

!IF !DEFINED(SMBIOS_CORE_SRC_SUPPORT) || "$(SMBIOS_CORE_SRC_SUPPORT)" == "0"

all : SMBIOS_DMIEDIT_BOARD_SUPPORT

SMBIOS_DMIEDIT_BOARD_SUPPORT : $(BUILD_DIR)\SmbiosDMIEditBoard.mak SmbiosDMIEditBoardBin

!IF "$(x64_BUILD)"=="1"
$(BUILD_DIR)\SmbiosDMIEditBoard.mak : $(SMBIOS_DMIEDIT_BOARD_DIR)\$(@B).cif $(SMBIOS_DMIEDIT_BOARD_DIR)\$(@B).mak $(BUILD_RULES)
        $(CIF2MAK) $(SMBIOS_DMIEDIT_BOARD_DIR)\$(@B).c64 $(CIF2MAK_DEFAULTS)
!ELSE
$(BUILD_DIR)\SmbiosDMIEditBoard.mak : $(SMBIOS_DMIEDIT_BOARD_DIR)\$(@B).cif $(SMBIOS_DMIEDIT_BOARD_DIR)\$(@B).mak $(BUILD_RULES)
        $(CIF2MAK) $(SMBIOS_DMIEDIT_BOARD_DIR)\$(@B).c32 $(CIF2MAK_DEFAULTS)
!ENDIF

SmbiosDMIEditBoardBin : $(AMIDXELIB) $(AMICSPLib) $(BUILD_DIR)\AmiBufferValidationLib.lib
        $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
                /f $(BUILD_DIR)\SmbiosDMIEditBoard.mak all\
                GUID=AF382531-52E6-4cc4-B247-DB8E320CBBA3 \
                ENTRY_POINT=SmbiosDmiEditSupportInstall \
                TYPE=BS_DRIVER \
                COMPRESS=1\

!ENDIF

#************************************************************************
#************************************************************************
#**                                                                    **
#**         (C)Copyright 1985-2009, American Megatrends, Inc.          **
#**                                                                    **
#**                        All Rights Reserved.                        **
#**                                                                    **
#**          5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093         **
#**                                                                    **
#**                        Phone: (770)-246-8600                       **
#**                                                                    **
#************************************************************************
#************************************************************************
