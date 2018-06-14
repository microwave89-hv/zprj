#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**           5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093      **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************

#**********************************************************************
# $Header: /Alaska/SOURCE/Modules/CSM/Generic/Thunk/x86/x86thunk.mak 7     1/12/10 11:47a Olegi $
#
# $Revision: 7 $
#
# $Date: 1/12/10 11:47a $
#**********************************************************************

#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	x86Thunk.mak
#
# Description:	This file has a set of rules to create a binary that will
#				be copied into lower memory that will give control to CSM16
#				code.
#
#<AMI_FHDR_END>
#**********************************************************************

all: CREATE_THUNK_FFS

CREATE_THUNK_FFS: $(BUILD_DIR)\x86Thunk.ffs 

$(BUILD_DIR)\x86Thunk.ffs : $(BUILD_DIR)\x86Thunk.bin
	$(MAKE) /f Core\FFS.mak \
	BUILD_DIR=$(BUILD_DIR) SOURCE_DIR=$(CSM_THUNKASM_DIR) \
	GUID=A08276EC-A0FE-4e06-8670-385336C7D093 \
	TYPE=EFI_FV_FILETYPE_FREEFORM \
	BINFILE=$** FFSFILE=$@ COMPRESS=0 NAME=$(**B)

$(BUILD_DIR)\x86Thunk.bin: $(X86THUNK_DIR)\x86Thunk.asm
!IF "$(x64_BUILD)"=="1"
  $(ASM) /c /nologo /DEFIx64 /Fo$(BUILD_DIR)\x86thunk.obj $(X86THUNK_DIR)\x86Thunk.asm
!ELSE
  $(ASM) /c /nologo /Fo$(BUILD_DIR)\x86thunk.obj $(X86THUNK_DIR)\x86Thunk.asm
!ENDIF
  $(ASMLINK) /MAP $(BUILD_DIR)\x86thunk.obj, $(BUILD_DIR)\x86thunk.exe, $(BUILD_DIR)\x86thunk.map,,,
  exe2bin $(BUILD_DIR)\x86thunk.exe $(BUILD_DIR)\x86Thunk.bin

#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**           5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093      **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************
