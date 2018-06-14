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
# $Header: /Alaska/SOURCE/Modules/TCG2/Common/TcgDxeplatform/TcgDxeplatform.mak 1     4/21/14 2:17p Fredericko $
#
# $Revision: 1 $
#
# $Date: 4/21/14 2:17p $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/TCG2/Common/TcgDxeplatform/TcgDxeplatform.mak $
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
# 3     3/29/11 1:20p Fredericko
# [TAG]        EIP 54642
# [Category] Improvement
# [Description] 1. Checkin Files related to TCG function override 
# 2. Include TCM and TPM auto detection
# [Files] Affects all TCG files
#
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:		TcgDxeplatform.mak
#
# Description:	Make file for the TcgDxeplatform component
#
#<AMI_FHDR_END>
#**********************************************************************
all: $(BUILD_DIR)\TcgDxeplatform.mak TcgDxeplatformBin 

$(BUILD_DIR)\TcgDxeplatform.mak : $(TCG_DXE_PLATFORM_DIR)\$(@B).cif $(TCG_DXE_PLATFORM_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(TCG_DXE_PLATFORM_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

TcgDxeplatform_CFLAGS=$(CFLAGS)\
    /I$(TCG_DIR)\
	/I$(TPM12_DIR)\
    /I$(TCG_DIR)\Common\
	/I$(TCG_DXE_PLATFORM_DIR)\
    /I$(TCG_DIR)\protocol\TcgService\
    /I$(TCG_DIR)\protocol\TpmDevice\
    /I$(PROJECT_DIR)\Include\Protocol
    
TcgDxeplatformBin : $(AMIDXELIB) $(BUILD_DIR)\AmiTcgLibDxe.lib 
	    $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\TcgDxeplatform.mak all\
		"CFLAGS=$(TcgDxeplatform_CFLAGS) "\
		"CPFLAGS=$(TcgDxeplatform_CFLAGS) "\
		GUID=2688B232-9C02-4c12-BE1F-857C0FF2AAE3\
		ENTRY_POINT=TcgDxeplatformEntry \
		TYPE=BS_DRIVER \
		DEPEX1=$(TCG_DXE_PLATFORM_DIR)\TcgDxeplatform.dxs \
		DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX \
		EXT_HEADERS=$(BUILD_DIR)\token.h \
   		COMPRESS=1\
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
