#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**     5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093            **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************
#**********************************************************************
# $Header: /Alaska/SOURCE/Modules/TCG2/Libraries/Tpm20CRBLib/Tpm20CRBLib.mak 1     4/21/14 2:15p Fredericko $
#
# $Revision: 1 $
#
# $Date: 4/21/14 2:15p $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/TCG2/Libraries/Tpm20CRBLib/Tpm20CRBLib.mak $
# 
# 1     4/21/14 2:15p Fredericko
# 
# 3     3/14/14 3:20p Fredericko
# 
# 2     3/11/14 6:01p Fredericko
# [TAG]  		EIP151925
# [Category]  	New Feature
# [Description]  	Changes for TcgGeneric Regression Testing
# 
# 1     10/08/13 11:59a Fredericko
# Initial Check-In for Tpm-Next module
# 
# 2     10/03/13 1:48p Fredericko
# 
# 1     7/10/13 5:50p Fredericko
# [TAG]  		EIP120969
# [Category]  	New Feature
# [Description]  	TCG (TPM20)
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:		Tpm20CrbLib.mak
#
# Description:	Make file for the Tpm20CrbLib component
#
#<AMI_FHDR_END>
#**********************************************************************
Tpm20Crb_lib : $(BUILD_DIR)\Tpm20CRBLib.mak make_crb_lib make_crb_Peilib
$(BUILD_DIR)\Tpm20CRBLib.lib: Tpm20Crb_lib
$(BUILD_DIR)\IA32\Tpm20CRBLib.lib: Tpm20Crb_lib

$(BUILD_DIR)\Tpm20CRBLib.mak : $(TPM20_CRBLIB)\Tpm20CrbLib.cif $(TPM20_CRBLIB)\Tpm20CrbLib.mak $(BUILD_RULES)
	$(CIF2MAK) $(TPM20_CRBLIB)\Tpm20CrbLib.cif $(CIF2MAK_DEFAULTS)

LIB_CFLAGS=$(CFLAGS)\
	/I$(TPM20_CRBLIB)\
    /I$(TCG_DIR)\Common\
    /I$(TPM20_CRBLIB)\
    /I$(TCG_DIR)\

TCG_LIB_LITE_OBJS = \
$(BUILD_DIR)\$(TPM20_CRBLIB)\Tpm20CrbLib.obj


make_crb_lib: $(SHALIB) $(FWTPM20LIBx64)
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\Tpm20CrbLib.mak all\
		"CFLAGS=$(LIB_CFLAGS) "\
		TYPE=LIBRARY

make_crb_Peilib: $(SHALIBPEI) $(FWTPM20LIBx32)
!IF "$(PROCESSOR)"=="x64"
		$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS) BUILD_DIR=$(BUILD_DIR)\IA32\
		/f $(BUILD_DIR)\Tpm20CrbLib.mak all\
		"CFLAGS=$(LIB_CFLAGS) "\
		TYPE=PEI_LIBRARY
!ELSE
	    $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\TisLib.mak all\
		"CFLAGS=$(LIB_CFLAGS) "\
		TYPE=PEI_LIBRARY
!ENDIF