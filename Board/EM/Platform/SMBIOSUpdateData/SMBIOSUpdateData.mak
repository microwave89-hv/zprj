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

#*************************************************************************
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/Platform/SMBIOSUpdateData/SMBIOSUpdateData.mak 1     2/09/12 12:35a Yurenlai $
#
# $Revision: 1 $
#
# $Date: 2/09/12 12:35a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/Platform/SMBIOSUpdateData/SMBIOSUpdateData.mak $
# 
# 1     2/09/12 12:35a Yurenlai
# Initial check in.
#
#*************************************************************************
#<AMI_FHDR_START>
#
# Name: SMBIOSUpdateData.mak
#
# Description:  This make file builds SMBIOSUpdateData module PEI & DXE
#               components and link them to respective binary
#
#<AMI_FHDR_END>
#*************************************************************************


all : SMBIOSUpdateData

SMBIOSUpdateData : $(BUILD_DIR)\SMBIOSUpdateData.mak SMBIOSUpdateDataBin

$(BUILD_DIR)\SMBIOSUpdateData.mak : $(SMBIOSUpdateData_DIR)\SMBIOSUpdateData.CIF $(SMBIOSUpdateData_DIR)\$(@B).mak $(BUILD_RULES)
       $(CIF2MAK) $(SMBIOSUpdateData_DIR)\SMBIOSUpdateData.CIF $(CIF2MAK_DEFAULTS)

SMBIOSUpdateData_INCLUDES =  \
                         $(EDK_INCLUDES)\
                         /I$(PROJECT_DIR)\
                         /IInclude\
                       
SMBIOSUpdateDataBin : $(EFIDRIVERLIB) 
       $(MAKE) /$(MAKEFLAGS) $(EDK_DEFAULTS)\
               /f $(BUILD_DIR)\SMBIOSUpdateData.mak all\
               NAME=SMBIOSUpdateData\
               "MY_INCLUDES=$(SMBIOSUpdateData_INCLUDES)"\
               GUID=B98999A4-E96F-475a-99FC-762126F50F5A\
               ENTRY_POINT=SMBIOSUpdateDataDriverEntryPoint\
               DEPEX1=$(SMBIOSUpdateData_DIR)\SMBIOSUpdateData.dxs \
               DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX \
               TYPE=BS_DRIVER\
               COMPRESS=1\

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
