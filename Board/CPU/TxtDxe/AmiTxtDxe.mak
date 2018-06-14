#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1987-2013, American Megatrends, Inc.            **
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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/Haswell/AMI Cpu PKG/AMI TXT DXE/AmiTxtDxe.mak 5     1/17/14 4:08a Crystallee $
#
# $Revision: 5 $
#
# $Date: 1/17/14 4:08a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/Haswell/AMI Cpu PKG/AMI TXT DXE/AmiTxtDxe.mak $
# 
# 5     1/17/14 4:08a Crystallee
# [TAG]  		None
# [Category]  	Improvement
# [Description]  	Show Txt information in setup->Advanced ->Intel Txt
# Information page.
# 
# 4     10/14/12 11:49p Davidhsieh
# [TAG]  		None
# [Category]  	Improvement
# [Description]  	Use SBLib_ExtResetSystem when pRS->ResetSystem does not
# support GlobaRest type in the project
# 
# 3     9/05/12 1:36a Davidhsieh
# [TAG]  		EIP97350
# [Category]  	Improvement
# [Description]  	Add AUX index define in TPM NVRAM to avoid system keep
# reset when TXT enabled
# 
# 2     8/14/12 5:06a Davidhsieh
# [TAG]  		EIP97190
# [Category]  	Improvement
# [Description]  	Changes in TXT Configuration require a Powercycle reset
# 
# 1     7/18/12 2:07a Davidhsieh
# [TAG]  		None
# [Category]  	Improvement
# [Description]  	AMI TXT Dxe module part create
# 
#
#**********************************************************************

#**********************************************************************
#<AMI_FHDR_START>
#
# Name: AmiTxtDxe.mak
#
# Description: Makefile for TxtWrapper.
#
#<AMI_FHDR_END>
#**********************************************************************

all : AmiTxtDxe

AmiTxtDxe: $(BUILD_DIR)\AmiTxtDxe.mak AmiTxtDxeBin

$(BUILD_DIR)\AmiTxtDxe.mak : $(AmiTxtDxe_DIR)\$(@B).cif $(AmiTxtDxe_DIR)\$(@B).mak $(BUILD_RULES)
        $(CIF2MAK) $(AmiTxtDxe_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

CPU_TXTDXE_INCLUDE = \
    $(PROJECT_CPU_INCLUDES)

AmiTxtDxeBin : $(AMIDXELIB) $(AMICSPLib)
                $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
                /f $(BUILD_DIR)\AmiTxtDxe.mak all\
                MAKEFILE=$(BUILD_DIR)\AmiTxtDxe.mak \
				"MY_INCLUDES=$(CPU_TXTDXE_INCLUDE)" \
				OBJECTS=$(BUILD_DIR)\$(AmiTxtDxe_DIR)\AmiTxtDxe.obj\
                GUID=87D402CD-8B07-4B93-B38B-F8799F28B033 \
                ENTRY_POINT=AmiTxtDxeEntry\
                TYPE=BS_DRIVER \
                DEPEX1=$(AmiTxtDxe_DIR)\AmiTxtDxe.dxs\
                DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX\
                COMPRESS=1

#---------------------------------------------------------------------------
#               TSE Elink component
#---------------------------------------------------------------------------
TXTTSE_CFLAGS = \
$(CFLAGS) \
-I $(TSEBIN_DIR)\Inc \
-I $(TSEBIN_DIR)\ \
/D _TSE_HOOK_

AMITSEBin : $(BUILD_DIR)\TXTTseHook.obj $(BUILD_DIR)\AmiTxtInfoHook.obj

$(BUILD_DIR)\TXTTseHook.obj : $(AmiTxtDxe_DIR)\TXTSetup.c
	$(CC) $(TXTTSE_CFLAGS) /Fo$(BUILD_DIR)\TXTTseHook.obj $(AmiTxtDxe_DIR)\TXTSetup.c

$(BUILD_DIR)\AmiTxtInfoHook.obj : $(AmiTxtDxe_DIR)\AmiTxtInfoHook.c
	$(CC) $(TXTTSE_CFLAGS) /Fo$(BUILD_DIR)\AmiTxtInfoHook.obj $(AmiTxtDxe_DIR)\AmiTxtInfoHook.c

#---------------------------------------------------------------------------
#               TSE Elink component
#---------------------------------------------------------------------------
SetupSdbs : $(BUILD_DIR)\AmiTxtDxe.mak AmiTxtInfoSetupSDB
SetupBin : $(BUILD_DIR)\AmiTxtInfoSetup.obj

AmiTxtInfoSetupSDB :
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\AmiTxtDxe.mak all\
		TYPE=SDB NAME=AmiTxtInfoSetup MAKEFILE=$(BUILD_DIR)\AmiTxtDxe.mak "STRING_CONSUMERS=$(AmiTxtDxe_DIR)\AmiTxtInfoSetup.sd $(AmiTxtDxe_DIR)\AmiTxtInfoSetup.c"

$(BUILD_DIR)\AmiTxtInfoSetup.obj: $(PROJECT_DIR)\$(AmiTxtDxe_DIR)\AmiTxtInfoSetup.c $(BUILD_DIR)\SetupStrTokens.h
	$(CC) $(CFLAGS) /Fo$@ $(PROJECT_DIR)\$(AmiTxtDxe_DIR)\AmiTxtInfoSetup.c
              
#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1987-2013, American Megatrends, Inc.            **
#**                                                                     **
#**                       All Rights Reserved.                          **
#**                                                                     **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
#**                                                                     **
#**                       Phone: (770)-246-8600                         **
#**                                                                     **
#*************************************************************************
#*************************************************************************
