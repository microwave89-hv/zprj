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
#*************************************************************************
# $Header: /Alaska/SOURCE/Modules/TCG2/Common/TcgLegacy/TcgLegacy.mak 1     4/21/14 2:17p Fredericko $
#
# $Revision: 1 $
#
# $Date: 4/21/14 2:17p $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/TCG2/Common/TcgLegacy/TcgLegacy.mak $
# 
# 1     4/21/14 2:17p Fredericko
# 
# 1     10/08/13 12:04p Fredericko
# Initial Check-In for Tpm-Next module
# 
# 1     7/10/13 5:56p Fredericko
# [TAG]  		EIP120969
# [Category]  	New Feature
# [Description]  	TCG (TPM20)
# 
# 5     4/22/11 8:54p Fredericko
# Changes for x32bit mode build
# 
# 4     3/29/11 1:28p Fredericko
# 
# 3     3/28/11 3:38p Fredericko
# [TAG]        EIP 54642
# [Category] Improvement
# [Description] 1. Checkin Files related to TCG function override 
# 2. Include TCM and TPM auto detection
# [Files] Affects all TCG files
# 
# 2     5/20/10 8:55a Fredericko
# Included File Header
# Included File Revision History 
# EIP 37653
# 
#*************************************************************************
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:		tcgLegacy.MAK
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************
all: TcgLegacy

TcgLegacy : $(BUILD_DIR)\TcgLegacy.mak TcgLegacyBIN

$(BUILD_DIR)\TcgLegacy.mak : $(TCGLEG_DIR)\TcgLegacy.cif $(TCGLEG_DIR)\TcgLegacy.mak $(BUILD_RULES)
	$(CIF2MAK) $(TCGLEG_DIR)\TcgLegacy.cif $(CIF2MAK_DEFAULTS)

TcgLegacyCflags=$(CFLAGS)\
    /I$(TCG_DIR)\
	/I$(TPM12_DIR)\
    /I$(TCG_DIR)\Common\

!IFNDEF LIB_BUILD_DIR
!IF "$(PROCESSOR)"=="x64"
AMITCMLIB = $(BUILD_DIR)\IA32\AmiTcmlib.lib
!ELSE
AMITCMLIB = $(BUILD_DIR)\AmiTcmlib.lib
!ENDIF
!ENDIF #LIB_BUILD_DIR

			
TcgLegacyBIN: $(AMIDXELIB) $(AMITCMLIB) $(BUILD_DIR)\AmiTcgLibDxe.lib
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\TcgLegacy.mak all\
        "CFLAGS=$(TcgLegacyCflags)"\
        "CPFLAGS=$(TcgLegacyCflags)"\
		GUID=858EBE6F-360F-415b-B7DC-463AAEB03412 \
		ENTRY_POINT=InitTCGLegacyInterface\
		TYPE=BS_DRIVER \
		COMPRESS=1\
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
