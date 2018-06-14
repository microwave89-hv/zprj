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
# $Header: /Alaska/SOURCE/Modules/TCG2/Libraries/TisLib/TisLib.mak 1     4/21/14 2:14p Fredericko $
#
# $Revision: 1 $
#
# $Date: 4/21/14 2:14p $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/TCG2/Libraries/TisLib/TisLib.mak $
# 
# 1     4/21/14 2:14p Fredericko
# 
# 1     10/08/13 11:58a Fredericko
# Initial Check-In for Tpm-Next module
# 
# 2     10/03/13 12:31p Fredericko
# 
# 1     7/10/13 5:50p Fredericko
# [TAG]  		EIP120969
# [Category]  	New Feature
# [Description]  	TCG (TPM20)
# [Files]  		TisLib.cif
# TisLib.mak
# TcgTpm12.h
# TpmLib.h
# TcgCommon.h
# ZTEICTcmOrdinals.h
# TpmLib.c
# TcgCommon.c
# TisLib.sdl
# sha1.h
# INTTcgAcpi.h
# TcgPc.h
# TcmPc.h
# TcgEfiTpm.h
# TcgEFI12.h
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:		Tpm12lib.mak
#
# Description:	Make file for the tcglib component
#
#<AMI_FHDR_END>
#**********************************************************************
Tpm12_lib : $(BUILD_DIR)\TisLib.mak make_TisLib_lib make_TisLib_libPei
$(BUILD_DIR)\TisLib.lib: Tpm12_lib
$(BUILD_DIR)\IA32\TisLib.lib: Tpm12_lib

tcg_lib_lite: $(BUILD_DIR)\TisLib.mak tcg_lib_liteBin
$(tcgLibLite): tcg_lib_lite

$(BUILD_DIR)\TisLib.mak : $(TPM12_DIR)\TisLib.cif $(TPM12_DIR)\TisLib.mak $(BUILD_RULES)
	$(CIF2MAK) $(TPM12_DIR)\TisLib.cif $(CIF2MAK_DEFAULTS)

TCG12LIB_CFLAGS=$(CFLAGS)\
	/I$(TPM12_DIR)\
    /I$(TCG_DIR)\

TCG_LIB_LITE_OBJS = \
$(BUILD_DIR)\$(TPM12_DIR)\TpmLib.obj

tcg_lib_liteBin: $(BUILD_DIR)\AmiTcmlib.lib
        $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\TisLib.mak all\
		"CFLAGS=$(TCG12LIB_CFLAGS) "\
        "OBJECTS=$(TCG_LIB_LITE_OBJS)"\
		TYPE=LIBRARY \
        LIBRARY_NAME=$(tcgLibLite)

!IF "$(PROCESSOR)"=="x64"
make_TisLib_lib: $(BUILD_DIR)\AmiTcmlib.lib $(SHALIB)
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\TisLib.mak all\
		"CFLAGS=$(TCG12LIB_CFLAGS) "\
		TYPE=LIBRARY

make_TisLib_libPei: $(BUILD_DIR)\AmiTcmlib.lib $(SHALIBPEI)
		$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS) BUILD_DIR=$(BUILD_DIR)\IA32\
		/f $(BUILD_DIR)\TisLib.mak all\
		"CFLAGS=$(TCG12LIB_CFLAGS) "\
		TYPE=PEI_LIBRARY
!ELSE
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\TisLib.mak all\
		"CFLAGS=$(TCG12LIB_CFLAGS) "\
		TYPE=PEI_LIBRARY
!ENDIF
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
