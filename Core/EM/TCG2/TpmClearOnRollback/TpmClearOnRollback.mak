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
# $Header: /Alaska/SOURCE/Modules/TCG2/Common/TpmClearOnRollback/TpmClearOnRollback.mak 1     4/21/14 2:18p Fredericko $
#
# $Revision: 1 $
#
# $Date: 4/21/14 2:18p $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/TCG2/Common/TpmClearOnRollback/TpmClearOnRollback.mak $
# 
# 1     4/21/14 2:18p Fredericko
# 
# 1     10/08/13 12:06p Fredericko
# Initial Check-In for Tpm-Next module
# 
# 2     10/03/13 2:48p Fredericko
# 
# 1     7/10/13 5:57p Fredericko
# [TAG]  		EIP120969
# [Category]  	New Feature
# [Description]  	TCG (TPM20)
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
all : BuildTpmClearOnRollbackWrapperLib TPMCLEARONROLLBACK 

TPMCLEARONROLLBACK : $(BUILD_DIR)\TpmClearOnRollback.mak  TpmClearRollBackSmmBin 

BuildTpmClearOnRollbackWrapperLib: $(BUILD_DIR)\TpmClearOnRollback.mak TpmClearOnRollbackWrapperLibBin
$(TpmClearOnRollbackWrapperLib): BuildTpmClearOnRollbackWrapperLib

$(BUILD_DIR)\TpmClearOnRollback.mak : $(TPMCLEARONROLLBACK_DIR)\$(@B).cif $(TPMCLEARONROLLBACK_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(TPMCLEARONROLLBACK_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

TCGCLEAR_CFLAGS=$(CFLAGS) \
	/I$(TCG_DIR)\
    /I$(TCG_DIR)\Common\
	/I$(PROJECT_DIR)\Include\Protocol\
    /I$(TCG_DIR)\Protocol


TPM_CLEAR_ON_ROLLBACK_WRAPPEER_OBJS = \
$(BUILD_DIR)\$(TPMCLEARONROLLBACK_DIR)\TpmClearOnRollbackWrapperLib.obj

TpmClearOnRollbackWrapperLibBin: $(tcgLibLite)
        $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\TpmClearOnRollback.mak all\
		"CFLAGS=$(TCGCLEAR_CFLAGS)" \
        "OBJECTS=$(TPM_CLEAR_ON_ROLLBACK_WRAPPEER_OBJS)"\
		TYPE=LIBRARY \
        LIBRARY_NAME=$(TpmClearOnRollbackWrapperLib)

TCGCLEAR_OBJECTS = \
$(BUILD_DIR)\$(TPMCLEARONROLLBACK_DIR)\TpmClearOnRollbackSmiFlash.obj 

ReFlashBin: $(BUILD_DIR)\$(TCG)\TpmClearOnRollback.obj $(TpmClearOnRollbackWrapperLib)

$(BUILD_DIR)\$(TCG)\TpmClearOnRollback.obj : $(TPMCLEARONROLLBACK_DIR)\TpmClearOnRollback.obj 
	$(CC) $(TCGCLEAR_CFLAGS) /Fo$(BUILD_DIR)\$(TCG)\TpmClearOnRollback.obj $(TPMCLEARONROLLBACK_DIR)\TpmClearOnRollback.c

TpmClearRollBackSmmBin : $(TpmClearOnRollbackWrapperLib) $(AMIDXELIB) 
            	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS) \
        		/f $(BUILD_DIR)\TpmClearOnRollback.mak all \
        		GUID=FD2CB3F1-9520-4c24-BCB3-2C73F0C2B7EC \
                "CFLAGS=$(TCGCLEAR_CFLAGS)" \
        		ENTRY_POINT=TpmClearRollBackSmmInit \
        		TYPE=BS_DRIVER \
                "OBJECTS=$(TCGCLEAR_OBJECTS)"\
                DEPEX1=$(TPMCLEARONROLLBACK_DIR)\TpmClearOnRollback.DXS \
                COMPRESS=1 \

#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2010, American Megatrends, Inc.            **
#**                                                                     **
#**                       All Rights Reserved.                          **
#**                                                                     **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
#**                                                                     **
#**                       Phone: (770)-246-8600                         **
#**                                                                     **
#*************************************************************************
#*************************************************************************
