#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelPfat/PfatRecovery/PfatRecovery.mak 1     4/05/13 5:36p Fredericko $
#
# $Revision: 1 $
#
# $Date: 4/05/13 5:36p $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelPfat/PfatRecovery/PfatRecovery.mak $
# 
# 1     4/05/13 5:36p Fredericko
# [TAG]  		EIP119706
# [Category]  	Improvement
# [Description]  	Support Recovery in pfat module
# [Files]  		PfatRecovery.cif
# PfatRecovery.sdl
# PfatRecovery.mak
# PfatRecovery.dxs
# PfatRecovery.c
# PfatRecoveryHook.c
# 
#
#
#**********************************************************************
#<AMI_FHDR_START>
#
# Name: PfatRecovery.mak
#
# Description: Make file for PfatRecovery module part
#
#<AMI_FHDR_END>
#**********************************************************************
all : PfatRecovery

PFAT_RECOVERY_BUILD_DIR = $(BUILD_DIR)\$(PFAT_RECOVERY_PATH)
#---------------------------------------------------------------------------
# Create Fault Tolerant BootBlock Update dependencies
#---------------------------------------------------------------------------
$(BUILD_DIR)\PfatRecovery.mak : $(PFAT_RECOVERY_PATH)\$(@B).cif $(PFAT_RECOVERY_PATH)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(PFAT_RECOVERY_PATH)\$(@B).cif $(CIF2MAK_DEFAULTS)
#---------------------------------------------------------------------------
# Create Fault Tolerant BootBlock Update DXE Component
#---------------------------------------------------------------------------
PfatRecovery: $(BUILD_DIR)\PfatRecovery.mak PfatRecoveryBin

PfatRecoveryIncludes =\
/I$(PROJECT_CPU_ROOT)\Include

PfatRecoveryObjs = \
$(PFAT_RECOVERY_BUILD_DIR)\PfatRecovery.obj

PfatRecoveryBin : $(AMIPEILIB)
                $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
                /f $(BUILD_DIR)\PfatRecovery.mak all\
                OBJECTS="$(PfatRecoveryObjs)" \
                NAME=PfatRecovery\
                MAKEFILE=$(BUILD_DIR)\PfatRecovery.mak \
                "CFLAGS=$(CFLAGS) $(PfatRecoveryIncludes)"\
                GUID=c2bcc635-779e-46f0-9e1b-b83db1ca4690 \
                ENTRY_POINT=PfatRecoveryEntry \
                TYPE=PEIM \
                DEPEX1=$(PFAT_RECOVERY_PATH)\PfatRecovery.DXS \
                DEPEX1_TYPE=EFI_SECTION_PEI_DEPEX \
                COMPRESS=1

#---------------------------------------------------------------------------
#               Create Launch SCLEAN Pei Component
#---------------------------------------------------------------------------
PfatRecoveryHook : $(BUILD_DIR)\PfatRecovery.mak PfatRecoveryHookBin

PfatRecoveryHookObjs = \
$(PFAT_RECOVERY_BUILD_DIR)\PfatRecoveryHook.obj

PfatRecoveryHookBin :
            $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
            /f $(BUILD_DIR)\PfatRecovery.mak all\
            OBJECTS="$(PfatRecoveryHookObjs)" \
            NAME=PfatRecovery \
            TYPE=PEI_LIBRARY LIBRARY_NAME=$(PfatRecoveryPeiLib)

$(PfatRecoveryPeiLib) : PfatRecoveryHook

RecoveryBin : $(PfatRecoveryPeiLib)
FwCapsuleRecoveryPPIBin : $(PfatRecoveryPeiLib)

#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2012, American Megatrends, Inc.            **
#**                                                                     **
#**                       All Rights Reserved.                          **
#**                                                                     **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
#**                                                                     **
#**                       Phone: (770)-246-8600                         **
#**                                                                     **
#*************************************************************************
#*************************************************************************
