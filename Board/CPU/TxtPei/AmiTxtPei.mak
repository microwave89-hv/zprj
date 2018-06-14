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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/Haswell/AMI Cpu PKG/AMI TXT PEI/AmiTxtPei.mak 1     7/18/12 2:09a Davidhsieh $
#
# $Revision: 1 $
#
# $Date: 7/18/12 2:09a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/Haswell/AMI Cpu PKG/AMI TXT PEI/AmiTxtPei.mak $
# 
# 1     7/18/12 2:09a Davidhsieh
# [TAG]  		None
# [Category]  	Improvement
# [Description]  	AMI TXT PEI module part create
# 
#
#**********************************************************************
#**********************************************************************
#<AMI_FHDR_START>
#
# Name: AmiTxtPei.mak
#
# Description: Makefile for AmiTxtPei module.
#
#<AMI_FHDR_END>
#**********************************************************************

all : AmiTxtPei

AmiTxtPei: $(BUILD_DIR)\AmiTxtPei.mak AmiTxtPeiBin

$(BUILD_DIR)\AmiTxtPei.mak : $(AmiTxtPei_DIR)\$(@B).cif $(AmiTxtPei_DIR)\$(@B).mak $(BUILD_RULES)
        $(CIF2MAK) $(AmiTxtPei_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

AmiTxtPeiBin : $(AMIPEILIB) $(AMICSPLib)
                $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
                /f $(BUILD_DIR)\AmiTxtPei.mak all\
                MAKEFILE=$(BUILD_DIR)\AmiTxtPei.mak \
                GUID=C7D4BBCF-EB0A-4C91-BD8B-FCA99F28B011 \
                ENTRY_POINT=AmiTxtPeiEntry\
                TYPE=PEIM \
                COMPRESS=0
                
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
