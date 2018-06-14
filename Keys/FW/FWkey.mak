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

#*************************************************************************
# $Header: /Alaska/SOURCE/Modules/SecureFlashPkg/PlatformKey/FWkey.mak 5     3/18/14 3:09p Alexp $
#
# $Revision: 5 $
#
# $Date: 3/18/14 3:09p $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SecureFlashPkg/PlatformKey/FWkey.mak $
# 
# 5     3/18/14 3:09p Alexp
# year 2014 in hdr & ftr
# 
# 4     1/07/14 6:28p Alexp
# use silent macro in front of "copy"
# 
# 3     11/11/13 9:33a Alexp
# 
# 2     10/17/13 4:47p Alexp
# New file with rules to generate FwKey ffs. 
# Relevant Make scripts moved form SecureMod.nmak
# 
#*************************************************************************
#<AMI_FHDR_START>
#
# Name: Fwkey.mak
#
# Description: Includes build rules for Platform Root Key(PR) ffs file(s)
# 
#<AMI_FHDR_END>
#*************************************************************************

SecureModule : $(BUILD_DIR)\FWKey.mak $(BUILD_DIR)\FWkey.ffs

#---------------------------------------------------------------------------
#            Generic MAK dependencies
#---------------------------------------------------------------------------
$(BUILD_DIR)\FWKey.mak : $(FWKey_DIR)\FWKey.mak $(FWKey_DIR)\FWKey.cif $(FWKey_DIR)\FWKey.sdl $(BUILD_RULES)
    $(CIF2MAK) $(FWKey_DIR)\FWKey.cif $(CIF2MAK_DEFAULTS)

#---------------------------------------------------------------------------
#GUID used to identify FW Key FFS file within the Firmware Volume
#---------------------------------------------------------------------------
#RSA n-modulus (e-exponent is hardwired to 0x10001)
!IF "$(FWKEY_FILE_FORMAT)"=="0"
PR_KEY_PUB_FFS_FILE_GUID = 3FEEC852-F14C-4E7F-97FD-4C3A8C5BBECC
!ENDIF

#SHA256 Hash of an n-modulus of RSA Key
!IF "$(FWKEY_FILE_FORMAT)"=="1"
PR_KEY_PUB_FFS_FILE_GUID = 5B85965C-455D-4CC6-9C4C-7F086967D2B0
!ENDIF

#x509 Key Cerificate
!IF "$(FWCAPSULE_CERT_FORMAT)"=="1" || "$(FWKEY_FILE_FORMAT)" == "2"
PR_KEY_PUB_FFS_FILE_GUID = 3A666558-43E3-4D25-9169-DB81F5DB42E1
!ENDIF

!IF !EXIST($(FWpub))
#---------------------------------------------------------------------------
#   Create a scratchpad Key buf if no Key file is provided
#---------------------------------------------------------------------------
#Merge64 FwKey pad.
$(BUILD_DIR)\FWKEY.BIN: $(FWKey_DIR)\FWKey.mak
	$(SILENT)copy << $(BUILD_DIR)\FWkey.ini > NUL 
output
    FWKEY_FILE($@)
end
group FWKEY_FILE
    upper=0xffffffff
components
blank MICROCODE_PAD
    size=$(FWKEY_FILE_SIZE)
    pattern=(0xff)
end
end end
<<
	$(MERGE) /s $(BUILD_DIR)\Fwkey.ini
#
#$(BUILD_DIR)\FWkey.obj: $(BUILD_DIR)\FWkey.mak
#	$(SILENT)copy << $(BUILD_DIR)\FWkey.c > NUL
##include <Token.h>
##pragma pack(1)
#char pad[$(FWKEY_FILE_SIZE)] = {0xFF,0xFF,0xFF,0xFF};
#<<KEEP
#    $(CC) /Fo$@ $(CFLAGS) $(BUILD_DIR)\FWkey.c

#$(BUILD_DIR)\FWkey.bin : $(BUILD_DIR)\FWkey.obj $(BUILD_DIR)\FWkey.mak
#    $(MAKE) /$(MAKEFLAGS) EXT_OBJS= $(BUILD_DEFAULTS)\
#        /f $(BUILD_DIR)\FWkey.mak bin\
#        NAME=FWkey OBJECTS=$(BUILD_DIR)\FWkey.obj\
#        MAKEFILE=$(BUILD_DIR)\FWkey.mak \
#        TYPE=BINARY

!ELSE
#---------------------------------------------------------------------------
#   Prepare Platform Firmware Root Key (FWKey) bin file
#---------------------------------------------------------------------------
$(BUILD_DIR)\FWkey.bin: $(FWpub)
!IF "$(FWCAPSULE_CERT_FORMAT)"=="1" || "$(FWKEY_FILE_FORMAT)" == "2"
#x509 Cert Key
    $(SILENT)copy $** $@
!ELSE
#Extract 256byte n-modulus from x509 DER or PKCS#1v2 ASN.1 encoded RSA Key
# n-modulus can be extracted either from Public Key FWpub or full RSA Key FWpriv files
    $(CRYPTCON) -w -k $** -o $@
!IF "$(FWKEY_FILE_FORMAT)"=="1"
#get SHA256 Hash of n-modulus of RSA Key
    $(CRYPTCON) -h2 -f $@ -o $@
!ENDIF
!ENDIF
 
!ENDIF #!IF !EXIST($(FWpub))

#---------------------------------------------------------------------------
#   Include public portion of Platform Firmware Root Key (FWKey) as .FFS
#---------------------------------------------------------------------------
#Warning: don't compress the data. Raw key buffer is expected by Recovery module.
#Key data won't be compressed much anyway.
#Ignore FFS checksum as the file data may be updated by cryptocon utility
$(BUILD_DIR)\FWkey.ffs: $(BUILD_DIR)\FWkey.bin
    $(MAKE) /f Core\FFS.mak \
        BUILD_DIR=$(BUILD_DIR) \
        GUID=$(PR_KEY_PUB_FFS_FILE_GUID) \
        TYPE=EFI_FV_FILETYPE_FREEFORM FFS_CHECKSUM=0 \
        BINFILE=$(BUILD_DIR)\FWkey.bin FFSFILE=$@ COMPRESS=0 NAME=FWkey

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
