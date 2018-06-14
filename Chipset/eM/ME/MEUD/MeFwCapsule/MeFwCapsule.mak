#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2014, American Megatrends, Inc.            **
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
# $Header: /Alaska/SOURCE/Modules/OFBD Intel ME Update/CSP_MEUD/ME80/MeFwCapsule/MeFwCapsule.mak 3     6/03/15 7:22a Tristinchou $
#
# $Revision: 3 $
#
# $Date: 6/03/15 7:22a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/OFBD Intel ME Update/CSP_MEUD/ME80/MeFwCapsule/MeFwCapsule.mak $(BUILD_DIR)\MeFwCapsulePei.mak MeFwCapsulePeiBin
# 
# 3     6/03/15 7:22a Tristinchou
# [TAG]  		EIPNone
# [Category]  	Improvement
# [Description]  	Fix ME update capsule can't be generated.
# 
# 2     5/14/15 5:08a Tristinchou
# 
# 1     5/14/15 4:24a Tristinchou
# [TAG]  		EIP215437
# [Category]  	New Feature
# [Description]  	ME capsule update support
# [Files]  		MeFwCapsule.cif
# MeFwCapsule.sdl
# MeFwCapsule.mak
# MeFwCapsulePei.c
# MeFwCapsulePei.dxs
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
all : MeFwCapsulePei MeFwCapsule

MeFwCapsulePei : $(BUILD_DIR)\MeFwCapsulePei.mak MeFwCapsulePeiBin

MeFwCapsulePei_OBJ = \
	$(BUILD_DIR)\$(MeFwCapsule_DIR)\MeFwCapsulePei.obj

$(BUILD_DIR)\MeFwCapsulePei.mak : $(MeFwCapsule_DIR)\MeFwCapsule.mak $(MeFwCapsule_DIR)\MeFwCapsule.cif $(BUILD_RULES)
	$(CIF2MAK) $(MeFwCapsule_DIR)\MeFwCapsule.cif $(CIF2MAK_DEFAULTS)

MeFwCapsulePeiBin : $(AMIPEILIB)
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS) \
	/f $(BUILD_DIR)\MeFwCapsulePei.mak all \
	NAME=MeFwCapsulePei \
	MAKEFILE=$(BUILD_DIR)\MeFwCapsulePei.mak \
	GUID=FD27652D-F758-4EFC-B1A9-283EFE51F4E9 \
	ENTRY_POINT=MeFwCapsulePeiEntry \
	OBJECTS="$(MeFwCapsulePei_OBJ)" \
	DEPEX1="$(MeFwCapsule_DIR)\MeFwCapsulePei.dxs" DEPEX1_TYPE=EFI_SECTION_PEI_DEPEX \
	TYPE=PEIM \
	COMPRESS=0\

MeFwCapsule : MeFwExt MeFwCapsuleHdr MeFwCapFid MeFwVer MeFwLayout MeFwRegion MeFwFv

MeFwExt : $(BUILD_DIR)\MeFwExt.ffs

$(BUILD_DIR)\MeFwExt.obj: $(BUILD_DIR)\MeFwCapsule.mak
    $(SILENT)copy << $(BUILD_DIR)\MeFwExt.c > NUL
#include <EFI.h>

#define ME_CAPSULE_GUID \
	{ 0x9F8B1DEF, 0xB62B, 0x45F3, 0x82, 0x82, 0xBF, 0xD7, 0xEA, 0x19, 0x80, 0x1B}

static EFI_GUID MeCapsuleGuid = ME_CAPSULE_GUID;
static UINT32   Length = 0x14;
static UINT32   Pad = 0xFFFFFFFF;
<<KEEP
	$(CC) /Fo$@ $(CFLAGS) $(BUILD_DIR)\MeFwExt.c

$(BUILD_DIR)\MeFwExt.ffs : $(BUILD_DIR)\MeFwExt.obj
	$(MAKE) /$(MAKEFLAGS) EXT_OBJS= $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\MeFwCapsule.mak bin\
		NAME=MeFwExt OBJECTS=$(BUILD_DIR)\MeFwExt.obj\
		MAKEFILE=$(BUILD_DIR)\MeFwCapsule.mak \
		TYPE=BINARY
	$(MAKE) /f Core\FFS.mak \
		BUILD_DIR=$(BUILD_DIR) \
		GUID=FFFFFFFF-FFFF-FFFF-FFFF-FFFFFFFFFFFF \
		TYPE=EFI_FV_FILETYPE_RAW FFS_CHECKSUM=0\
		RAWFILE=$(BUILD_DIR)\MeFwExt.bin\
		FFSFILE=$@ COMPRESS=0 NAME=$(@B)

#---------------------------------------------------------------------------
#            Generic MAK dependencies
#---------------------------------------------------------------------------
$(BUILD_DIR)\MeFwCapsule.mak : $(MeFwCapsule_DIR)\MeFwCapsule.mak $(MeFwCapsule_DIR)\MeFwCapsule.cif $(BUILD_RULES)
    $(CIF2MAK) $(MeFwCapsule_DIR)\MeFwCapsule.cif $(CIF2MAK_DEFAULTS)

#---------------------------------------------------------------------------
#            Generic GUID defines. Aptio Tools must support these GUIDs
#---------------------------------------------------------------------------
#GUID used to identify FW Capsule Hdr FFS file within the Firmware Volume.
FWCAPSULE_FFS_GUID          = 414D94AD-998D-47D2-BFCD-4E882241DE32
#Section GUID used to identify FW Capsule Hdr section within FwCap FFS file. 
FWCAPSULE_FFS_SECTION_GUID  = 5A88641B-BBB9-4AA6-80F7-498AE407C31F

MeFwCapsuleHdr : $(BUILD_DIR)\MeFwCapsule.mak $(BUILD_DIR)\MeFwCapsuleHdr.ffs

$(BUILD_DIR)\MeFwCapsuleHdr.obj: $(BUILD_DIR)\MeFwCapsule.mak
    $(SILENT)copy << $(BUILD_DIR)\MeFwCapsuleHdr.c > NUL
#include <AmiCertificate.h>
#pragma pack(1)
APTIO_FW_CAPSULE_HEADER dummyHdr = 
    {  { APTIO_FW_CAPSULE_GUID,
        $(FWCAPSULE_MAX_HDR_SIZE), 
        CAPSULE_FLAGS_PERSIST_ACROSS_RESET | 
           CAPSULE_FLAGS_FWCERTBLOCK_VALID, // 1 - sig is invalid
        $(FWCAPSULE_MAX_HDR_SIZE)},
        $(FWCAPSULE_MAX_HDR_SIZE),      // Rom Offs
        sizeof(APTIO_FW_CAPSULE_HEADER) // RomLayout Offs
    };
char pad[$(FWCAPSULE_MAX_HDR_SIZE)-sizeof(APTIO_FW_CAPSULE_HEADER)] = {0x55, 0xAA};
<<KEEP
    $(CC) /Fo$@ $(CFLAGS) $(BUILD_DIR)\MeFwCapsuleHdr.c

$(BUILD_DIR)\MeFwCapsuleHdr.ffs : $(BUILD_DIR)\MeFwCapsuleHdr.obj $(BUILD_DIR)\MeFwCapsule.mak
	$(MAKE) /$(MAKEFLAGS) EXT_OBJS= $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\MeFwCapsule.mak bin\
		NAME=MeFwCapsuleHdr OBJECTS=$(BUILD_DIR)\MeFwCapsuleHdr.obj\
		MAKEFILE=$(BUILD_DIR)\MeFwCapsule.mak \
		TYPE=BINARY
	$(MAKE) /f Core\FFS.mak \
		BUILD_DIR=$(BUILD_DIR) \
		GUID=$(FWCAPSULE_FFS_GUID) \
		TYPE=EFI_FV_FILETYPE_FREEFORM FFS_CHECKSUM=0\
		SECTION_GUID=$(FWCAPSULE_FFS_SECTION_GUID) \
		RESOURCE=$(BUILD_DIR)\MeFwCapsuleHdr.bin \
		FFSFILE=$@ COMPRESS=0 NAME=$(@B)

CSP_LIB_DIR = Core\CspLib

MeFwCapFid : $(BUILD_DIR)\MeFwCapsule.mak $(BUILD_DIR)\MeFwCapFid.ffs

$(BUILD_DIR)\MeFwCapFid.ffs : $(BUILD_DIR)\AMICspLib.mak
    $(MAKE) /$(MAKEFLAGS) EXT_OBJS= $(BUILD_DEFAULTS)\
        /f $(BUILD_DIR)\AMICspLib.mak bin\
        NAME=MeFwCapFid OBJECTS=$(BUILD_DIR)\$(CSP_LIB_DIR)\Fid.obj\
        MAKEFILE=$(BUILD_DIR)\AMICspLib.mak \
        TYPE=BINARY
    $(MAKE) /f Core\FFS.mak \
        BUILD_DIR=$(BUILD_DIR) \
        GUID=3FD1D3A2-99F7-420b-BC69-8BB1D492A332 \
        TYPE=EFI_FV_FILETYPE_FREEFORM \
        FFSFILE=$@ COMPRESS=0 NAME=$(@B)\
        RESOURCE=$(BUILD_DIR)\Fid.bin \
        SECTION_GUID=2EBE0275-6458-4AF9-91ED-D3F4EDB100AA \

MeFwVer : $(BUILD_DIR)\MeFwCapsule.mak $(BUILD_DIR)\MeFwVer.ffs

$(BUILD_DIR)\MeFwVer.obj: $(BUILD_DIR)\MeFwCapsule.mak
    $(SILENT)copy << $(BUILD_DIR)\MeFwVer.c > NUL
#include <EFI.h>
#include <Token.h>

typedef struct _FW_VERSION_NAME {
  UINT32  MajorVersion : 16;
  UINT32  MinorVersion : 16;
  UINT32  HotfixVersion : 16;
  UINT32  BuildVersion : 16;
} ME_FW_UPD_VERSION;

const ME_FW_UPD_VERSION  MeFwVersion[] = ME_FW_IMAGE_VERSION;
<<KEEP
	$(CC) /Fo$@ $(CFLAGS) $(BUILD_DIR)\MeFwVer.c

$(BUILD_DIR)\MeFwVer.ffs : $(BUILD_DIR)\MeFwVer.obj
	$(MAKE) /$(MAKEFLAGS) EXT_OBJS= $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\MeFwCapsule.mak bin\
		NAME=MeFwVer OBJECTS=$(BUILD_DIR)\MeFwVer.obj\
		MAKEFILE=$(BUILD_DIR)\MeFwCapsule.mak \
		TYPE=BINARY
	$(MAKE) /f Core\FFS.mak \
		BUILD_DIR=$(BUILD_DIR) \
		GUID=0B4AE6BE-6DA6-4908-8A71-7E6A8A33B11C \
		TYPE=EFI_FV_FILETYPE_FREEFORM FFS_CHECKSUM=0\
		SECTION_GUID=6A6D576A-8F38-45E7-97C0-8ACD9E992674 \
		RESOURCE=$(BUILD_DIR)\MeFwVer.bin \
		FFSFILE=$@ COMPRESS=0 NAME=$(@B)

MeFwLayout : $(BUILD_DIR)\MeFwCapsule.mak $(BUILD_DIR)\MeFwLayout.ffs

$(BUILD_DIR)\MeFwLayout.obj: $(BUILD_DIR)\MeFwCapsule.mak
    $(SILENT)copy << $(BUILD_DIR)\MeFwLayout.c > NUL
#include <Token.h>
#include <RomLayout.h>

ROM_AREA  MeLayout[2] = {\
    { 0, 0, FV_MEFWCAP_SIZE, 0, 0x20A}, 
    { 0, 0, 0, 0, 0}
};
<<KEEP
    $(CC) /Fo$@ $(CFLAGS) $(BUILD_DIR)\MeFwLayout.c

$(BUILD_DIR)\MeFwLayout.ffs : $(BUILD_DIR)\MeFwLayout.obj
	$(MAKE) /$(MAKEFLAGS) EXT_OBJS= $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\MeFwCapsule.mak bin\
		NAME=MeFwLayout OBJECTS=$(BUILD_DIR)\MeFwLayout.obj\
		MAKEFILE=$(BUILD_DIR)\MeFwCapsule.mak \
		TYPE=BINARY
	$(MAKE) /f Core\FFS.mak \
		BUILD_DIR=$(BUILD_DIR) \
		GUID=0DCA793A-EA96-42d8-BD7B-DC7F684E38C1 \
		TYPE=EFI_FV_FILETYPE_FREEFORM FFS_CHECKSUM=0\
		SECTION_GUID=88A15A4F-977D-4682-B17C-DA1F316C1F32 \
		RESOURCE=$(BUILD_DIR)\MeFwLayout.bin \
		FFSFILE=$@ COMPRESS=0 NAME=$(@B)

MeFwRegion : $(BUILD_DIR)\MeFwRegion.ffs

$(BUILD_DIR)\MeFwRegion.ffs : $(ME_BIN_FILE)
	$(MAKE) /f Core\FFS.mak \
	BUILD_DIR=$(BUILD_DIR) \
	GUID=DE90FFA8-B985-4575-AB8D-ADE52C362CA3 \
	TYPE=EFI_FV_FILETYPE_FREEFORM \
	BINFILE=$** FFSFILE=$@ COMPRESS=1 NAME=$(**B)

MeFwFv : MeFwExt MeFwCapsuleHdr MeFwCapFid MeFwVer MeFwLayout MeFwRegion $(BUILD_DIR)\FWkey.ffs
!IF EXIST ($(BUILD_DIR)\FV_MEFWCAP_VOL.inf )
	del $(BUILD_DIR)\FV_MEFWCAP_VOL.inf 
!ENDIF
	echo [options]													>>	$(BUILD_DIR)\FV_MEFWCAP_VOL.inf 
# This is a dummy base address to store logos in ROMHOLE.This address has no effect in ROMHOLE.
	echo EFI_BASE_ADDRESS		=	$(FV_MEFWCAP_BASE)				>>	$(BUILD_DIR)\FV_MEFWCAP_VOL.inf 
	echo EFI_FILE_NAME			=	$(BUILD_DIR)\FV_MEFWCAP_VOL.FV	>>	$(BUILD_DIR)\FV_MEFWCAP_VOL.inf 
	echo EFI_NUM_BLOCKS			=	$(FV_MEFWCAP_NUMBER_OF_BLOCK)	>>	$(BUILD_DIR)\FV_MEFWCAP_VOL.inf 
	echo EFI_BLOCK_SIZE			=	$(FV_MEFWCAP_BLOCK_SIZE) 		>>	$(BUILD_DIR)\FV_MEFWCAP_VOL.inf 
	echo IGNORE_COMPRESSION		=	FALSE 	>>	$(BUILD_DIR)\FV_MEFWCAP_VOL.inf
	echo [attributes] 						>>	$(BUILD_DIR)\FV_MEFWCAP_VOL.inf
	echo EFI_READ_DISABLED_CAP	=	TRUE 	>>	$(BUILD_DIR)\FV_MEFWCAP_VOL.inf
	echo EFI_READ_ENABLED_CAP	=	TRUE 	>>	$(BUILD_DIR)\FV_MEFWCAP_VOL.inf
	echo EFI_READ_STATUS		=	TRUE 	>>	$(BUILD_DIR)\FV_MEFWCAP_VOL.inf
	echo EFI_WRITE_DISABLED_CAP	=	TRUE	>>	$(BUILD_DIR)\FV_MEFWCAP_VOL.inf
	echo EFI_WRITE_ENABLED_CAP	=	TRUE	>>	$(BUILD_DIR)\FV_MEFWCAP_VOL.inf
	echo EFI_WRITE_STATUS		=	TRUE	>>	$(BUILD_DIR)\FV_MEFWCAP_VOL.inf
	echo EFI_LOCK_CAP			=	TRUE	>>	$(BUILD_DIR)\FV_MEFWCAP_VOL.inf
	echo EFI_LOCK_STATUS		=	TRUE	>>	$(BUILD_DIR)\FV_MEFWCAP_VOL.inf
	echo EFI_STICKY_WRITE		=	TRUE	>>	$(BUILD_DIR)\FV_MEFWCAP_VOL.inf
	echo EFI_MEMORY_MAPPED		=	TRUE	>>	$(BUILD_DIR)\FV_MEFWCAP_VOL.inf
	echo EFI_ERASE_POLARITY		=	1		>>	$(BUILD_DIR)\FV_MEFWCAP_VOL.inf
	echo EFI_ALIGNMENT_CAP		=	TRUE	>>	$(BUILD_DIR)\FV_MEFWCAP_VOL.inf
	echo EFI_ALIGNMENT_2		=	TRUE	>>	$(BUILD_DIR)\FV_MEFWCAP_VOL.inf
	echo EFI_ALIGNMENT_4		=	TRUE	>>	$(BUILD_DIR)\FV_MEFWCAP_VOL.inf
	echo EFI_ALIGNMENT_8		=	TRUE	>>	$(BUILD_DIR)\FV_MEFWCAP_VOL.inf
	echo EFI_ALIGNMENT_16		=	TRUE	>>	$(BUILD_DIR)\FV_MEFWCAP_VOL.inf
	echo EFI_ALIGNMENT_32		=	TRUE	>>	$(BUILD_DIR)\FV_MEFWCAP_VOL.inf
	echo EFI_ALIGNMENT_64		=	TRUE	>>	$(BUILD_DIR)\FV_MEFWCAP_VOL.inf
	echo EFI_ALIGNMENT_128		=	TRUE	>>	$(BUILD_DIR)\FV_MEFWCAP_VOL.inf
	echo EFI_ALIGNMENT_256		=	TRUE	>>	$(BUILD_DIR)\FV_MEFWCAP_VOL.inf
	echo EFI_ALIGNMENT_512		=	TRUE	>>	$(BUILD_DIR)\FV_MEFWCAP_VOL.inf
	echo EFI_ALIGNMENT_1K		=	TRUE	>>	$(BUILD_DIR)\FV_MEFWCAP_VOL.inf
	echo EFI_ALIGNMENT_2K		=	TRUE	>>	$(BUILD_DIR)\FV_MEFWCAP_VOL.inf
	echo EFI_ALIGNMENT_4K		=	TRUE	>>	$(BUILD_DIR)\FV_MEFWCAP_VOL.inf
	echo EFI_ALIGNMENT_8K		=	TRUE	>>	$(BUILD_DIR)\FV_MEFWCAP_VOL.inf
	echo EFI_ALIGNMENT_16K		=	TRUE	>>	$(BUILD_DIR)\FV_MEFWCAP_VOL.inf
	echo EFI_ALIGNMENT_32K		=	TRUE	>>	$(BUILD_DIR)\FV_MEFWCAP_VOL.inf
	echo EFI_ALIGNMENT_64K		=	TRUE	>>	$(BUILD_DIR)\FV_MEFWCAP_VOL.inf
	echo EFI_READ_LOCK_CAP		=	TRUE	>>	$(BUILD_DIR)\FV_MEFWCAP_VOL.inf
	echo EFI_READ_LOCK_STATUS	=	TRUE 	>> 	$(BUILD_DIR)\FV_MEFWCAP_VOL.inf
	echo EFI_WRITE_LOCK_CAP		=	TRUE 	>>	$(BUILD_DIR)\FV_MEFWCAP_VOL.inf
	echo EFI_WRITE_LOCK_STATUS	=	TRUE	>> 	$(BUILD_DIR)\FV_MEFWCAP_VOL.inf
	echo EFI_FVB2_ALIGNMENT		=	8		>>	$(BUILD_DIR)\FV_MEFWCAP_VOL.inf
	echo [files]							>>	$(BUILD_DIR)\FV_MEFWCAP_VOL.inf
	echo EFI_FILE_NAME	=	$(BUILD_DIR)\MeFwExt__.pkg			>>	$(BUILD_DIR)\FV_MEFWCAP_VOL.inf
	echo EFI_FILE_NAME	=	$(BUILD_DIR)\MeFwCapsuleHdr__.pkg	>>	$(BUILD_DIR)\FV_MEFWCAP_VOL.inf
	echo EFI_FILE_NAME	=	$(BUILD_DIR)\MeFwCapFid__.pkg		>>	$(BUILD_DIR)\FV_MEFWCAP_VOL.inf
	echo EFI_FILE_NAME	=	$(BUILD_DIR)\MeFwVer__.pkg			>>	$(BUILD_DIR)\FV_MEFWCAP_VOL.inf
	echo EFI_FILE_NAME	=	$(BUILD_DIR)\MeFwLayout__.pkg		>>	$(BUILD_DIR)\FV_MEFWCAP_VOL.inf
!IF $(CREATE_FWCAPSULE) == 1
	echo EFI_FILE_NAME	=	$(BUILD_DIR)\FWkey__.pkg			>>	$(BUILD_DIR)\FV_MEFWCAP_VOL.inf
!ENDIF
	echo EFI_FILE_NAME	=	$(BUILD_DIR)\MeFwRegion__.pkg		>>	$(BUILD_DIR)\FV_MEFWCAP_VOL.inf
!IF $(PI_SPECIFICATION_VERSION) >= 0x00010000
	$(FWBUILD) $(UNSIGNED_MEFW_CAPSULE) /f $(BUILD_DIR)\FV_MEFWCAP_VOL.inf /p 1.0
!ELSE
	$(FWBUILD) $(UNSIGNED_MEFW_CAPSULE) /f $(BUILD_DIR)\FV_MEFWCAP_VOL.inf
!ENDIF
	if exist $(BIOS_MEFW_CAPSULE_FILE) @del $(BIOS_MEFW_CAPSULE_FILE)
	if exist $(MEFW_CAPSULE_FILE) @del $(MEFW_CAPSULE_FILE)

End : CombineFwCapsule
BUILD_ME : SignMeFwCapsule

ME_FW_LAYOUT_EX = $(BUILD_DIR)\MeFwLayoutEx.bin

CombineFwCapsule :
	$(SILENT)copy /b $(UNSIGNED_BIOS_ROM)+$(UNSIGNED_MEFW_CAPSULE) $(UNSIGNED_MEFW_CAPSULE)2

$(ME_FW_LAYOUT_EX) : $(UNSIGNED_MEFW_CAPSULE)
	@if not exist $@ $(FWBUILD) $(UNSIGNED_MEFW_CAPSULE) /s /m $(ME_FW_LAYOUT_EX)

!IF "$(MEFWUPDLCL_ON_SHARKBAY_PLATFORM)"=="0"
SignMeFwCapsule : $(UNSIGNED_BIOS_ROM) $(ROM_LAYOUT_EX) MeFwFv $(ME_FW_LAYOUT_EX)
!ELSE
SignMeFwCapsule : $(UNSIGNED_BIOS_ROM) $(ROM_LAYOUT_EX) MeFwFv $(ME_FW_LAYOUT_EX) CombineFwCapsule
!ENDIF
	@echo ----------------------------------------------------------------
	@echo ----- create Signed BIOS + ME FW Capsule : "$(BIOS_MEFW_CAPSULE_FILE)" ------
	@echo ----------------------------------------------------------------
!IF !EXIST($(FWpriv)) || ("$(FWCAPSULE_CERT_FORMAT)"=="0" && !EXIST($(FWrootKey)))
	@echo ----- WARNING!!! Missing RSA private key FWpriv=$(FWpriv) to sign BIOS + ME FW Capsule image.
!ELSE
	$(CRYPTCON) -c2 -y -r$(ROM_LAYOUT_EX) -l$(FWCAPSULE_MAX_HDR_SIZE) -f $(UNSIGNED_MEFW_CAPSULE)2 -o $(UNSIGNED_MEFW_CAPSULE)2
	$(CRYPTCON) $(CRYPTOCON_CMDLINE_MEFWCAP) -f $(UNSIGNED_MEFW_CAPSULE)2 -o $(BIOS_MEFW_CAPSULE_FILE)
!ENDIF
	@echo ----------------------------------------------------------------
	@echo ----- create Signed ME FW Capsule : "$(MEFW_CAPSULE_FILE)" -------------
	@echo ---------------------------------------------------------------- 
!IF !EXIST($(FWpriv)) || ("$(FWCAPSULE_CERT_FORMAT)"=="0" && !EXIST($(FWrootKey)))
	@echo ----- WARNING!!! Missing RSA private key FWpriv=$(FWpriv) to sign ME FW Capsule image.
!ELSE
	$(CRYPTCON) -c2 -y -r$(ME_FW_LAYOUT_EX) -l$(FWCAPSULE_MAX_HDR_SIZE) -f $(UNSIGNED_MEFW_CAPSULE) -o $(UNSIGNED_MEFW_CAPSULE).Sig
	$(CRYPTCON) $(CRYPTOCON_CMDLINE_MEFWCAP) -f $(UNSIGNED_MEFW_CAPSULE).Sig -o $(MEFW_CAPSULE_FILE)
!ENDIF

#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2014, American Megatrends, Inc.            **
#**                                                                     **
#**                       All Rights Reserved.                          **
#**                                                                     **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
#**                                                                     **
#**                       Phone: (770)-246-8600                         **
#**                                                                     **
#*************************************************************************
#*************************************************************************