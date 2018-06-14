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
#*************************************************************************
# $Header: /Alaska/SOURCE/Modules/TCG2/Common/TcgPeiplatform/TcgPeiplatform.mak 1     4/21/14 2:17p Fredericko $
#
# $Revision: 1 $
#
# $Date: 4/21/14 2:17p $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/TCG2/Common/TcgPeiplatform/TcgPeiplatform.mak $
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
# 4     3/29/11 1:18p Fredericko
# [TAG]        EIP 54642
# [Category] Improvement
# [Description] 1. Checkin Files related to TCG function override 
# 2. Include TCM and TPM auto detection
# [Files] Affects all TCG files
#
#
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:		TcgPeiplatform.mak
#
# Description:	Make file for the TcgPeiplatform component
#
#<AMI_FHDR_END>
#**********************************************************************
all: $(BUILD_DIR)\TcgPeiplatform.mak TcgPeiplatformBin 

$(BUILD_DIR)\TcgPeiplatform.mak : $(TCG_PEI_PLATFORM_DIR)\$(@B).cif $(TCG_PEI_PLATFORM_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(TCG_PEI_PLATFORM_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

TcgPeiplatform_CFLAGS=$(CFLAGS)\
    /I$(TCG_DIR)\
	/I$(TPM12_DIR)\
    /I$(TCG_DIR)\Common\
	/I$(TCG_PEI_PLATFORM_DIR)

TcgPeiplatformBin : $(AMIPEILIB)
	    $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\TcgPeiplatform.mak all\
		"CFLAGS=$(TcgPeiplatform_CFLAGS) "\
		GUID=6B844C5B-6B75-42ca-8E8E-1CB94412B59B\
		ENTRY_POINT=TcgPeiplatformEntry \
		TYPE=PEIM \
		DEPEX1=$(TCG_PEI_PLATFORM_DIR)\TcgPeiplatform.dxs \
		DEPEX1_TYPE=EFI_SECTION_PEI_DEPEX \
		EXT_HEADERS=$(BUILD_DIR)\token.h \
   		COMPRESS=0\
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
