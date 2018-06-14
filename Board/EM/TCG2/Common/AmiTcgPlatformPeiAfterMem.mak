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
# $Header: /Alaska/SOURCE/Modules/TCG2/Common/AmiTcgPlatform/AmiTcgPlatformPei/AmiTcgPlatformPeiAfterMem/AmiTcgPlatformPeiAfterMem.mak 1     4/21/14 2:17p Fredericko $
#
# $Revision: 1 $
#
# $Date: 4/21/14 2:17p $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/TCG2/Common/AmiTcgPlatform/AmiTcgPlatformPei/AmiTcgPlatformPeiAfterMem/AmiTcgPlatformPeiAfterMem.mak $
# 
# 1     4/21/14 2:17p Fredericko
# 
# 1     10/08/13 12:04p Fredericko
# Initial Check-In for Tpm-Next module
# 
# 2     10/03/13 2:13p Fredericko
# 
# 1     7/10/13 5:54p Fredericko
# [TAG]  		EIP120969
# [Category]  	New Feature
# [Description]  	TCG (TPM20)
# 
# 2     3/29/11 2:24p Fredericko
# [TAG]        EIP 54642
# [Category] Improvement
# [Description] 1. Checkin Files related to TCG function override 
# 2. Include TCM and TPM auto detection
# [Files] Affects all TCG files
#
#
# 
#*************************************************************************
#<AMI_FHDR_START>
#
# Name:		AmiTcgPlatformPeiAfterMem.mak
#
# Description:	Make file for AmiTcgPlatformPeiAfterMem
#
#<AMI_FHDR_END>
#************************************************************************
all :  AmiTcgPlatformPeiAfterMem 

AmiTcgPlatformPeiAfterMem : $(BUILD_DIR)\AmiTcgPlatformPeiAfterMem.mak AmiTcgPlatformPeiAfterMembin

$(BUILD_DIR)\AmiTcgPlatformPeiAfterMem.mak : $(AMI_TCG_PLATFORM_PEI_DIR)\$(@B).cif $(AMI_TCG_PLATFORM_PEI_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(AMI_TCG_PLATFORM_PEI_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)


#---------------------------------------------------------------------------
#			Making AmiTcgPlatformPei
#---------------------------------------------------------------------------
AMI_TCG_PEI_PLATFORM_OBJECTS_AFTER_MEM = \
	$(BUILD_DIR)\$(AMI_TCG_PLATFORM_PEI_DIR)\AmiTcgPlatformPeiAfterMem.obj \

TCGPEIOVERRIDE_CFLAGS=$(CFLAGS)\
	/I$(TCG_DIR)\
	/I$(TPM12_DIR)\
    /I$(TCG_DIR)\Common\
    /I$(AMI_TCG_PLATFORM_PEI_DIR)\

AmiTcgPlatformPeiAfterMembin : $(AMIPEILIB)  $(BUILD_DIR)\AmiTcgLibPei.lib 
	    $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\AmiTcgPlatformPeiAfterMem.mak  all \
		"CFLAGS=$(TCGPEIOVERRIDE_CFLAGS) "\
        "CPFLAGS=$(TCGPEIOVERRIDE_CFLAGS) "\
		GUID=9B3F28D5-10A6-46c8-BA72-BD40B847A71A\
   		"OBJECTS=$(AMI_TCG_PEI_PLATFORM_OBJECTS_AFTER_MEM)" \
		ENTRY_POINT=AmiTcgPlatformPEI_EntryAfterMem \
		TYPE=PEIM \
		DEPEX1=$(AMI_TCG_PLATFORM_PEI_DIR)\AmiTcgPlatformPei.dxs \
		DEPEX1_TYPE=EFI_SECTION_PEI_DEPEX \
		COMPRESS=1
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
