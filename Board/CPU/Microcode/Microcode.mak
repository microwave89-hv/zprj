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
# $Header: /Alaska/SOURCE/CPU/Intel/NehalemMicrocode/Microcode.mak 5     12/20/11 2:43p Markw $
#
# $Revision: 5 $
#
# $Date: 12/20/11 2:43p $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/CPU/Intel/NehalemMicrocode/Microcode.mak $
# 
# 5     12/20/11 2:43p Markw
# [TAG]  		EIPNone
# [Category]  	Improvement
# [Description]  	Don't build MPDT binary when SDL token MPDTable_CREATED
# is disable.
# Type binary is not supported by 4.6.3 and earlier, and most projects if
# any using 4.6.3 don't support MPDT.
# [Files]  		Microcode.mak
# 
# 4     7/28/11 5:20p Markw
# [TAG]  		EIP65726
# [Category]  	Improvement
# [Description]  	Support MPDT - Microcode Patch Description Table. This
# table provides a header for AMI utilities.
# 
# [Files]  		Microcode.cif, Microcode.sdl, Microcode.mak, MPDTable.asm,
# MPDTableBB.asm, Startup32.asm, CpuCspLib.c , MicrocodeUpdate.c
# 
# 3     8/27/10 10:49a Markw
# Update microcode to support pack microcode without padding, and support
# microcode in the bootblock and updates in main FV.
# 
# 2     6/15/10 1:45p Markw
# Update the microcode.bin path in the build process.
# 
# 1     9/29/09 2:51p Markw
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name: MicroCode.mak
#
# Description:	Build the microcode file.
#
#<AMI_FHDR_END>
#**********************************************************************

MICROCODE_BUILD_DIR = $(BUILD_DIR)\$(MICROCODE_DIR)

all : MICROCODE

MICROCODE : MICROCODE_CREATE_BUILD_DIR $(BUILD_DIR)\Microcode.ffs \
!if "$(MICROCODE_SPLIT_BB_UPDATE)"=="1"
  $(BUILD_DIR)\Microcode_Blank.ffs
!ENDIF



$(BUILD_DIR)\Microcode.mak : $(MICROCODE_DIR)\Microcode.mak $(MICROCODE_DIR)\Microcode.cif $(BUILD_RULES)
	$(CIF2MAK) $(MICROCODE_DIR)\Microcode.cif $(CIF2MAK_DEFAULTS)

  
$(BUILD_DIR)\MPDTable.bin : $(MICROCODE_DIR)\MPDTable.asm $(BUILD_DIR)\Microcode.mak
	$(MAKE) /$(MAKEFLAGS)\
        /f $(BUILD_DIR)\Microcode.mak bin\
        OBJECTS=$(BUILD_DIR)\$(MICROCODE_DIR)\MPDTable.obj\
        NAME=MPDTable\
        MAKEFILE=$(BUILD_DIR)\Microcode.mak \
        TYPE=BINARY

$(BUILD_DIR)\MPDTableBB.bin : $(MICROCODE_DIR)\MPDTableBB.asm $(BUILD_DIR)\Microcode.mak
	$(MAKE) /$(MAKEFLAGS)\
        /f $(BUILD_DIR)\Microcode.mak bin\
        OBJECTS=$(BUILD_DIR)\$(MICROCODE_DIR)\MPDTableBB.obj\
        NAME=MPDTableBB\
        MAKEFILE=$(BUILD_DIR)\Microcode.mak \
        TYPE=BINARY

MICROCODE_GUID       = 17088572-377F-44ef-8F4E-B09FFF46A070

MICROCODE_CREATE_BUILD_DIR:
    if not exist $(MICROCODE_BUILD_DIR) md $(MICROCODE_BUILD_DIR)

$(MICROCODE_BUILD_DIR)\Microcode.bin : $(MICROCODE_DIR)\Microcode.mak $(BUILD_DIR)\token.mak \
!IF "$(MPDTable_CREATED)"=="1"
    $(BUILD_DIR)\MPDTable.bin $(BUILD_DIR)\MPDTableBB.bin
!ELSE
    #BLANK line for line continuation. 
!ENDIF
  copy << $(BUILD_DIR)\Microcode.ini
output
	MICROCODE_FILES($(MICROCODE_BUILD_DIR)\Microcode.bin)
end
group MICROCODE_FILES
    upper=0xffffffff
components
!IF "$(MPDTable_CREATED)"=="1"
!IF "$(MICROCODE_SPLIT_BB_UPDATE)"=="0"
    file $(BUILD_DIR)\MPDTable.bin binfile=$(BUILD_DIR)\MPDTable.bin end
!ELSE
    file $(BUILD_DIR)\MPDTableBB.bin binfile=$(BUILD_DIR)\MPDTableBB.bin end
!ENDIF
!ENDIF

!IF "$(MICROCODE_SPLIT_BB_UPDATE)"=="0"
blank MICROCODE_PAD
	size=$(MICROCODE_PAD_SIZE)
!IF "$(FLASH_ERASE_POLARITY)"=="0"
	pattern=(0)
!ELSE
	pattern=(0xFF)
!ENDIF
end
!ENDIF
<<KEEP

    for %%F IN ($(MICROCODE_FILES)) DO \
        echo file %%F binfile=%%F align=$(MICROCODE_ALIGNMENT) end >> $(BUILD_DIR)\Microcode.ini
    echo end end >> $(BUILD_DIR)\Microcode.ini
    $(MERGE) /s $(BUILD_DIR)\Microcode.ini

$(BUILD_DIR)\Microcode.ffs : $(MICROCODE_BUILD_DIR)\microcode.bin
	$(MAKE) /f Core\FFS.mak \
		BUILD_DIR=$(BUILD_DIR) \
        GUID=17088572-377F-44ef-8F4E-B09FFF46A070\
		TYPE=EFI_FV_FILETYPE_RAW \
        FFS_ALIGNMENT=1 FFS_CHECKSUM=1\
		RAWFILE=$** FFSFILE=$@ COMPRESS=0 NAME=$(**B)

!if "$(MICROCODE_SPLIT_BB_UPDATE)"=="1"
$(MICROCODE_BUILD_DIR)\Microcode_Blank.bin : $(MICROCODE_DIR)\Microcode.mak $(BUILD_DIR)\token.mak
    copy << $(BUILD_DIR)\Microcode_Blank.ini
output
	MICROCODE_EMPTY($(MICROCODE_BUILD_DIR)\Microcode_Blank.bin)
end
group MICROCODE_EMPTY
    upper=0xffffffff

components 

!IF "$(MPDTable_CREATED)"=="1"
   file $(BUILD_DIR)\MPDTable.bin binfile=$(BUILD_DIR)\MPDTable.bin end
!ENDIF

blank MICROCODE_PAD
	size=$(MICROCODE_PAD_SIZE)
!IF "$(FLASH_ERASE_POLARITY)"=="0"
	pattern=(0)
!ELSE
	pattern=(0xFF)
!ENDIF
end
end
end
<<KEEP
    $(MERGE) /s $(BUILD_DIR)\Microcode_Blank.ini


$(BUILD_DIR)\Microcode_Blank.ffs : $(MICROCODE_BUILD_DIR)\Microcode_Blank.bin
	$(MAKE) /f Core\FFS.mak \
		BUILD_DIR=$(BUILD_DIR) \
        GUID=17088572-377F-44ef-8F4E-B09FFF46A070\
		TYPE=EFI_FV_FILETYPE_RAW \
        FFS_ALIGNMENT=1 FFS_CHECKSUM=0 \
		RAWFILE=$** FFSFILE=$@ COMPRESS=0 NAME=$(**B)
!ENDIF

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
