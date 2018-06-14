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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/Haswell/AMI Cpu PKG/AMI CPU S3 Pei/AmiCpuS3Pei.mak 1     9/26/12 10:45a Davidhsieh $
#
# $Revision: 1 $
#
# $Date: 9/26/12 10:45a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/Haswell/AMI Cpu PKG/AMI CPU S3 Pei/AmiCpuS3Pei.mak $
# 
# 1     9/26/12 10:45a Davidhsieh
# 
#
#**********************************************************************
#**********************************************************************
#<AMI_FHDR_START>
#
# Name: AmiCpuS3Pei.mak
#
# Description: Makefile for AmiCpuS3Pei module.
#
#<AMI_FHDR_END>
#**********************************************************************

all : AmiCpuS3Pei

AmiCpuS3Pei: $(BUILD_DIR)\AmiCpuS3Pei.mak AmiCpuS3PeiBin

$(BUILD_DIR)\AmiCpuS3Pei.mak : $(AmiCpuS3Pei_DIR)\$(@B).cif $(AmiCpuS3Pei_DIR)\$(@B).mak $(BUILD_RULES)
        $(CIF2MAK) $(AmiCpuS3Pei_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

AmiCpuS3PeiBin : $(AMIPEILIB) $(AMICSPLib)
                $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
                /f $(BUILD_DIR)\AmiCpuS3Pei.mak all\
                MAKEFILE=$(BUILD_DIR)\AmiCpuS3Pei.mak \
                GUID=F7D22BCA-1BCA-5591-CC8B-1CA98F2890FE \
                ENTRY_POINT=AmiCpuS3PeiEntry\
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
