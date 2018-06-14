#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1987-2013, American Megatrends, Inc.         **
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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/Haswell/AMI Cpu PKG/CpuSp SMI/CpuSpSmi.mak 1     2/07/12 4:00a Davidhsieh $
#
# $Revision: 1 $
#
# $Date: 2/07/12 4:00a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/Haswell/AMI Cpu PKG/CpuSp SMI/CpuSpSmi.mak $
# 
# 1     2/07/12 4:00a Davidhsieh
# 
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name: CpuSpSmi.mak
#
# Description:  Make file for the CpuSpSMI component
#
#<AMI_FHDR_END>
#**********************************************************************
all : CPUSPSMI

CPUSPSMI : $(BUILD_DIR)\CpuSpSmi.mak CpuSpSmiBin

$(BUILD_DIR)\CpuSpSmi.mak : $(CPUSPSMI_DIR)\$(@B).cif $(CPUSPSMI_DIR)\$(@B).mak $(BUILD_RULES)
    $(CIF2MAK) $(CPUSPSMI_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

CpuSpSmiBin : $(AMIDXELIB)
    @set INCLUDE=%%INCLUDE%%
    $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
        /f $(BUILD_DIR)\CpuSpSmi.mak all\
        GUID=116e1acf-2533-4cc2-820a-bbc10a2aB07c\
        ENTRY_POINT=CpuSpSmiInit\
        TYPE=BS_DRIVER \
        COMPRESS=1\
#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1987-2013, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************