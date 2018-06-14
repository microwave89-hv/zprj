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

#**********************************************************************
# $Header: /Alaska/SOURCE/Modules/HddSmart/IdeSMART.mak 8     12/22/11 4:36a Lavanyap $
#
# $Revision: 8 $
#
# $Date: 12/22/11 4:36a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/HddSmart/IdeSMART.mak $
# 
# 8     12/22/11 4:36a Lavanyap
# [TAG]  		EIP77259
# [Category]  	Improvement
# [Description]  	Included rollbacked check-ins from ver 5, 6 and made it
# compatible with core 4.6.5.3.
# [Files]  		IdeSMART.c, IdeSMART.h, IdeSMART.mak, IdeSMART.uni,
# IdeSMART.dxs
# 
# 7     3/17/11 10:37a Krishnakumarg
# [TAG] - EIP 55534
# [Category]- Defect
# [Symptom] - Component HddSmart not labeled for CORE 4.6.4.1
# [Solution] - IdeSmart is updated for Core 4.6.4.1
# [Files] - IdeSmart.c,Idesmart.h,IdeSmart.mak,IdeSmart.dxs,IdeSmart.uni,
# IdeSmart.chm
# 
# 4     5/07/10 11:23a Krishnakumarg
# Added ELINK for OEM to override SMART error handling. EIP#31559
# 
# 3     3/18/09 11:32a Fredericko
# EIP19618 removed dependency on foundation.lib
# 
# 2     3/11/09 6:48p Fredericko
# EIP19618 removed dependency on foundation.lib functions
# 
# 1     7/03/08 5:19p Anandakrishnanl
# Added IdeSmart Module after removing IdeSmart.c from Idebus Src Module
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name: IdeSMART_mak
#
# Description: Make file to build IdeSmart module
#
#<AMI_FHDR_END>
#**********************************************************************
all : IdeSMART

IdeSMART : $(BUILD_DIR)\IdeSMART.mak IdeSMARTBin

$(BUILD_DIR)\IdeSMART.mak : $(IDESMART_DIR)\$(@B).cif $(IDESMART_DIR)\$(@B).mak $(BUILD_RULES)
    $(CIF2MAK) $(IDESMART_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

!IF "$(OemReportSmartFailureFunction: =X)"!="$(OemReportSmartFailureFunction)"
!MESSAGE +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!MESSAGE +  Multiple items detected for ELINK OemReportSmartFailureFunction  +
!MESSAGE +      Only one function name should be present for this ELINK      +
!MESSAGE +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

!ERROR Too many function names: $(OemReportSmartFailureFunction)
!ENDIF

IDESMART_DEFINES = /DOemReportSmartFailureFunction=$(OemReportSmartFailureFunction)

IdeSMARTBin:  $(AMIDXELIB)
    $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
        /f $(BUILD_DIR)\IdeSmart.mak all\
        GUID=D57C852E-809F-45cf-A377-D77BC0CB78EE\
        ENTRY_POINT=IdeSMARTEntryPoint \
        TYPE=BS_DRIVER \
        "MY_DEFINES=$(IDESMART_DEFINES)"\
        COMPRESS=1 HAS_RESOURCES=1\
        "OBJECTS=$(BUILD_DIR)\$(IDESMART_DIR)\IdeSMART.obj"

SetupSdbs : IdeSmartSDB

IdeSmartSDB : $(BUILD_DIR)\IdeSMART.mak
    $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
        /f $(BUILD_DIR)\IdeSMART.mak all\
        TYPE=SDB NAME=IdeSmart 

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

