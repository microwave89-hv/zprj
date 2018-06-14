#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2013, American Megatrends, Inc.            **
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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/Haswell/AMI Cpu PKG/CPU Board/CpuRcPolicyWrap/CpuRcPolicyWrap.mak 1     2/07/12 3:57a Davidhsieh $
#
# $Revision: 1 $
#
# $Date: 2/07/12 3:57a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/Haswell/AMI Cpu PKG/CPU Board/CpuRcPolicyWrap/CpuRcPolicyWrap.mak $
# 
# 1     2/07/12 3:57a Davidhsieh
# 
#
#**********************************************************************
#<AMI_FHDR_START>
#
# Name: 
#
# Description: 
#
#<AMI_FHDR_END>
#**********************************************************************

#----------------------------------------------------------------------------
#       Link to CpuPolicyPeiBin (Pesudo target of CpuPolicyPei.ffs)
#----------------------------------------------------------------------------
CpuPolicyPeiBin: $(BUILD_DIR)\CpuRcPolicyPei.obj

MY_PEI_FLAGS =\
    $(CRC_PEI_POLICY_FLAGS)\
    /D\"PEI_CPU_POLICY_INIT_LIST=$(PeiCpuPolicyInitList)\"

$(BUILD_DIR)\CpuRcPolicyPei.obj: $(CpuRcPolicyWrap_DIR)\CpuRcPolicyPei.c
    $(CC) $(CFLAGS) $(MY_PEI_FLAGS) /I$(PROJECT_DIR)\include /I$(PROJECT_CPU_ROOT)\Include /Fo$(BUILD_DIR)\ $(CpuRcPolicyWrap_DIR)\CpuRcPolicyPei.c

#----------------------------------------------------------------------------
#       Link to CpuPolicyPeiBin (Pesudo target of CpuPolicyPei.ffs)
#----------------------------------------------------------------------------
CpuPolicyInitDxeBin: $(BUILD_DIR)\CpuRcPolicyDxe.obj

MY_DXE_FLAGS =\
    $(CRC_DXE_POLICY_FLAGS)\
    /D\"DXE_CPU_POLICY_INIT_LIST=$(DxeCpuPolicyInitList)\"

$(BUILD_DIR)\CpuRcPolicyDxe.obj: $(CpuRcPolicyWrap_DIR)\CpuRcPolicyDxe.c
    $(CC) $(CFLAGS) $(MY_DXE_FLAGS) /I$(PROJECT_DIR)\include /I$(UefiEfiIfrSupportLib_DIR) /Fo$(BUILD_DIR)\ $(CpuRcPolicyWrap_DIR)\CpuRcPolicyDxe.c

#---------------------------------------------------------------------------
#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2013, American Megatrends, Inc.            **
#**                                                                     **
#**                       All Rights Reserved.                          **
#**                                                                     **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
#**                                                                     **
#**                       Phone: (770)-246-8600                         **
#**                                                                     **
#*************************************************************************
#*************************************************************************
