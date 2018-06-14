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
# $Header: /Alaska/SOURCE/Modules/SecureFlashPkg/SecureMod.mak 35    9/10/14 5:13p Alexp $
#
# $Revision: 35 $
#
# $Date: 9/10/14 5:13p $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SecureFlashPkg/SecureMod.mak $
# 
# 35    9/10/14 5:13p Alexp
# restore generation of make_sign_capsule.bat file 
# 
# 34    5/28/14 12:34p Alexp
# update format of make_sign_capsule_readme.txt
# 
# 32    3/21/14 12:30p Alexp
# 1. Eliminate generation of a .bat file. Instead provide capsule build
#  instructions inside make_sign_capsule_readme file
#  2. Split the cryptocon command line to 2 sets: 
#      1. for preparing BIOS ROM image with mapping of capsule 
#          signing instructions and an extended ROM map layout
#       2. Actual capsule signing command line. 
# 
# 
# 30    11/11/13 9:43a Alexp
# file is inlcuded only when create_capsule switch is non-0
# updated displayed warning messages and content of generated readme
# file.
# 
# 29    10/17/13 4:50p Alexp
# moved FwKey build rules and Guuid defines to a separare FwKey module
# 
# 28    10/14/13 4:11p Alexp
# [TAG]	              EIP139208
# [Description]	Build FwCapsule with Pkcs7 sig fails. 
# 1. Fix Cryptocon.exe to provide proper input line for generation of
# detached signatures 
# Cryptocon.exe ver 4.10.10
# 2. Fix mak scripts to invoke msft signtool along with cryptocon if .pfx
# password is to be provided
# 
# 27    8/21/13 3:24p Alexp
# 
# 22    7/12/13 12:41p Alexp
# Redesigned make file to accommodate more SDL defined build options and
# generate user friendly messages to deal with different build warnings
# 
# 21    4/19/13 4:52p Alexp
# -removed rules to generate igned image. will use external signing
# ToolKit (e.g. VEB project) 
# -add build rules to generate emptu placeholder for FwKey and FwSig
# header. 
# -Insert RomLayoutEX into FwSig hdr after AMI.ROM is generated
# 
# 20    4/10/13 7:04p Alexp
# Removed all FwCapsule signing build instructions
# 
# 19    11/13/12 3:11p Alexp
# add x509 Key format to list of supported FwKey file formats
# 
# 18    11/12/12 6:09p Alexp
# Add CREATE_FWCAPSULE token to be able to control Fw Capsule make rules
# Add FWCAPSULE_CERT_FORMAT to choose format for the digital certificate:
# PKCS1_v1.5 or PKCS7
# 
# 17    8/22/12 5:03p Alexp
# Added  FWSIG_KEY_ROOT flag to select which Key is used to sign
# FwCapsule's FwSig signature.
# 
# 15    7/26/12 3:03p Alexp
# Make token:FWSIG_PADDING relevant only if FWSIG_SIGNHDR = 1. 
# 
# 14    6/06/12 9:31a Alexp
#  -New FWSIG_SIGNHDR and FWSIG_PADDING Tokens control input arguments -q
#   and -p in CryptoCon.exe. 
#  -New flags control format of signing FwCapHdr and Signature padding
#   scheme
#  -Fix for the issue of backward compatibility when flashing BIOS with
#   SecFlash 008 to new one with label 009 and onwards.
# 
# 12    5/21/12 4:51p Alexp
# keep name of signed BIOS image as .CAP. Should match to the default
# recovery file name.
# 
# 11    5/18/12 4:13p Alexp
# 1. Add  rebuild dependency on .mak file
# 2. pass SIGPAD flag to indicate current padding scheme
# 3. Create rules to translete SDL defined GUID strings to .MAK and .H
# acceprtable formats
# 
# 10    4/17/12 4:46p Alexp
# EIP87889: Signed Aptio Flash Update binary image
# Supporting new output file format of the BIOS.ROM with 
# embeded FwCapsule Hdr inside the FFS File Section with the special GUID
# 
# 9     2/29/12 4:06p Alexp
# Use FWKEY_FORMAT to switch between RSA2048 and SH256 FW Key formats
# 
# 8     1/05/12 4:19p Alexp
# Add switch to generate FW Capsule output files based on SDL tokens : 
# FWCAPSULE_FILE_FORMAT and FWCAPSULE_HDR_FILE
# 
# 6     1/03/12 4:21p Alexp
# Rearrange build rules, clarify build steps, allow for FW Key to change
# location from default.
# Display error if FW Key file is not present
# 
# 4     12/20/11 5:09p Alexp
# Use ROM_LAYOUT_EX macro as a name for RomLayout table. New SDL Token is
# defined by Core.sdl starting from Label:4.6.5.3
# 
# 3     11/08/11 3:07p Alexp
# Change names and fix FWCAPSULE_IMAGE_SIZE vallue to depend on
# FWCAPSULE_IMAGE_ALLIGN
# 
# 2     11/03/11 6:36p Alexp
# added FWCAPSULE_ROM_ALLIGN token to control alignment size of generated
# FW Capsule
# use new CryptoCon.exe with support for -l key for alignment
# 
# 1     7/01/11 4:37p Alexp
# 
#*************************************************************************
#<AMI_FHDR_START>
#
# Name: SecureMod.mak
#
# Description: Includes main build module for Secure sub-components
# 
# Create signed BIOS image (Aptio FW Capsule)
#
#<AMI_FHDR_END>
#*************************************************************************
all: SecureModule
!INCLUDE $(BUILD_DIR)\timestamp.mak

SecureModule : $(BUILD_DIR)\SecureMod.mak 

#---------------------------------------------------------------------------
#            Generic MAK dependencies
#---------------------------------------------------------------------------
$(BUILD_DIR)\SecureMod.mak : $(SecureMod_DIR)\SecureMod.mak $(SecureMod_DIR)\SecureMod.cif $(SecureMod_DIR)\SecureMod.sdl $(BUILD_RULES)
    $(CIF2MAK) $(SecureMod_DIR)\SecureMod.cif $(CIF2MAK_DEFAULTS)

#---------------------------------------------------------------------------
#            Generic GUID defines. Aptio Tools must support these GUIDs
#---------------------------------------------------------------------------
#GUID used to identify FW Capsule Hdr FFS file within the Firmware Volume.
FWCAPSULE_FFS_GUID          = 414D94AD-998D-47D2-BFCD-4E882241DE32
#Section GUID used to identify FW Capsule Hdr section within FwCap FFS file. 
FWCAPSULE_FFS_SECTION_GUID  = 5A88641B-BBB9-4AA6-80F7-498AE407C31F

#---------------------------------------------------------------------------
# Creating a placeholder FFS for embedded FwCapsule Hdr
#---------------------------------------------------------------------------
SecureModule: $(BUILD_DIR)\FwCapsuleHdr.ffs

$(BUILD_DIR)\FwCapsuleHdr.obj: $(BUILD_DIR)\SecureMod.mak
	$(SILENT)copy << $(BUILD_DIR)\FwCapsuleHdr.c > NUL
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
    $(CC) /Fo$@ $(CFLAGS) $(BUILD_DIR)\FwCapsuleHdr.c

#The FFS section with Fw Capsule Signature block should be left unsigned and uncompressed.
#Ignore FFS checksum as the file data will be updated by external utility
$(BUILD_DIR)\FwCapsuleHdr.ffs : $(BUILD_DIR)\FwCapsuleHdr.obj $(BUILD_DIR)\SecureMod.mak
    $(MAKE) /$(MAKEFLAGS) EXT_OBJS= $(BUILD_DEFAULTS)\
        /f $(BUILD_DIR)\SecureMod.mak bin\
        NAME=FwCapsuleHdr OBJECTS=$(BUILD_DIR)\FwCapsuleHdr.obj\
        MAKEFILE=$(BUILD_DIR)\SecureMod.mak \
        TYPE=BINARY
    $(MAKE) /f Core\FFS.mak \
        BUILD_DIR=$(BUILD_DIR) \
        GUID=$(FWCAPSULE_FFS_GUID) \
        TYPE=EFI_FV_FILETYPE_FREEFORM FFS_CHECKSUM=0\
        SECTION_GUID=$(FWCAPSULE_FFS_SECTION_GUID) \
        RESOURCE=$(BUILD_DIR)\FwCapsuleHdr.bin \
        FFSFILE=$@ COMPRESS=0 NAME=$(@B)

#---------------------------------------------------------------------------
# Only for PKCS1v2.1 Key files: re-assign FWpub = FWpriv only if
# following codition is true: FWpub file not defined but full RSA key FWpriv file is defined
#---------------------------------------------------------------------------
!IF "$(FWCAPSULE_CERT_FORMAT)"=="0"
!IF !EXIST($(FWpub))
!IF EXIST($(FWpriv))
FWpub = $(FWpriv)
!ENDIF
!ENDIF
!ENDIF

#---------------------------------------------------------------------------
#  Conditions when error log needs to be created
#---------------------------------------------------------------------------
!IF !EXIST($(FWpriv))
FWCAP_BUILD_ERROR_TXT = $(FWCAP_BUILD_ERROR_TXT)&\
WARNING!!! Missing RSA private key FWpriv="$(FWpriv)" to sign BIOS image.
!ENDIF

!IF "$(FWCAPSULE_CERT_FORMAT)" == "0" && !EXIST($(FWrootKey))
FWCAP_BUILD_ERROR_TXT = $(FWCAP_BUILD_ERROR_TXT)&\
WARNING!!! Missing RSA private key FWrootKey="$(FWrootKey)"
!ENDIF

!IF !EXIST($(FWpub))
FWCAP_BUILD_ERROR_TXT = $(FWCAP_BUILD_ERROR_TXT)&\
WARNING!!! Missing RSA public key FWpub="$(FWpub)" to verify Signed BIOS updates.&\
$(FWKEY_FILE_SIZE) byte dummy Key is inserted into BIOS RTU (FV_BB).&\
Flash Updates or Recovery will fail on "$(UNSIGNED_BIOS_ROM)" BIOS&\
unless the dummy Key is replaced with a valid Platform key during BIOS signing.
!ENDIF

!IFDEF CONFIG_PEI_PKCS7
!IF "$(FWCAPSULE_CERT_FORMAT)" == "1" && "$(CONFIG_PEI_PKCS7)" == "0"
FWCAP_BUILD_ERROR_TXT = $(FWCAP_BUILD_ERROR_TXT)&\
WARNING!!! Capsule or Recovery Flash updates are disabled for PKCS7 Signed Fw Capsules.&\
Enable support via SDL Token "CONFIG_PEI_PKCS7" in CryptoAPI.sdl
!ENDIF
!ENDIF

!IF "$(FWCAPSULE_FILE_FORMAT)" == "1"
FWCAP_SIG_HDR_TXT = Attached FW signature (Capsule)
!ELSE
FWCAP_SIG_HDR_TXT = Embedded FW signature
!ENDIF
!IF "$(FWKEY_FILE_FORMAT)"=="0"
FWCAP_KEY_STORE_TXT = RSA2048 modulus N
!ENDIF
!IF "$(FWKEY_FILE_FORMAT)"=="1"
FWCAP_KEY_STORE_TXT = SHA-256 digest of a public Key certificate
!ENDIF
!IF "$(FWKEY_FILE_FORMAT)"=="2"
FWCAP_KEY_STORE_TXT = DER-encoded X.509 public key certificate
!ENDIF

!IF "$(FWCAPSULE_CERT_FORMAT)" == "1"
FWCAP_SIGN_CERT_TYPE_TXT = PKCS7 Signed data
FWCAP_SIGN_KEY_TYPE_TXT = RSA, PKCS12 PFX(private) and X.509 DER(public)
!ELSE
FWCAP_SIGN_CERT_TYPE_TXT = RSASSA-PKCS1-v1.5 (-PSS)
FWCAP_SIGN_KEY_TYPE_TXT = RSA-2048, PKCS1-v2.1(DER or PEM)&\
"$(FWrootKey)" - Root Key Certificate key (full RSA key)
!ENDIF

#---------------------------------------------------------------------------
#        Prepare Signed Capsule : FWCAPSULE_FILE_NAME
#---------------------------------------------------------------------------
SecureModule: CLEAR_FWCAPSULE_FILES MAKE_FWCAPSULE_HELP_FILES

CLEAR_FWCAPSULE_FILES:
	$(SILENT)if exist $(FWCAPSULE_FILE_NAME) $(SILENT)del $(FWCAPSULE_FILE_NAME)
	$(SILENT)if exist make_sign_capsule*.* $(SILENT)del make_sign_capsule*.*

#---------------------------------------------------------------------------
#   1. Create error log and batch files with instructions to sign Fw Capsule 
#      using CryptoCon.exe
#---------------------------------------------------------------------------
#Create make_sign_capsule.bat - command line to sign BIOS image
#Create make_sign_capsule_error.log  - error log
#Create make_sign_capsule_readme.txt - simple instructions to create signed FwCapsule
#---------------------------------------------------------------------------
MAKE_FWCAPSULE_HELP_FILES:
#------------------------------------------------------------------------
#Create make_sign_capsule.bat - command line to sign BIOS image
#------------------------------------------------------------------------
    $(SILENT)copy << make_sign_capsule.bat > NUL
@echo ----update the rom map file $(ROM_LAYOUT_EX)
@echo ----if the BIOS ROM image was edited
@echo FWBUILD $(UNSIGNED_BIOS_ROM) /s /m $(ROM_LAYOUT_EX)
@echo ----sign BIOS image using external rom map
CRYPTCON -r $(ROM_LAYOUT_EX) $(CRYPTOCON_CMDLINE_SIG)
<< KEEP
    $(SILENT)copy << make_sign_capsule_readme.txt > NUL
#---------------------------------------------------------------------------
#Create make_sign_capsule_error.log  - error log
#---------------------------------------------------------------------------
!IFDEF FWCAP_BUILD_ERROR_TXT
    $(SILENT)copy << make_sign_capsule_error.log > NUL
$(FWCAP_BUILD_ERROR_TXT:& =^
           )

<<KEEP
!ENDIF
#---------------------------------------------------------------------------
#Create make_sign_capsule_readme.txt - simple instructions to create signed FwCapsule
#---------------------------------------------------------------------------
    $(SILENT)copy << make_sign_capsule_readme.txt > NUL
===============================================================
=== Un-signed Aptio FW Image
===============================================================
BIOS File name                : $(UNSIGNED_BIOS_ROM)
Project TAG                   : $(PROJECT_TAG)
Build Time                    : $(TODAY), $(NOW) 
BIOS Flash size               : $(FLASH_SIZE)
FW update Key store(FwKey ffs): $(FWCAP_KEY_STORE_TXT)
Embedded FwCapsule parameters : $(CRYPTOCON_CMDLINE_MAP)

===============================================================
=== Pre-defined Signed FwCapsule parameters
===============================================================
FwCapsule file name           : $(FWCAPSULE_FILE_NAME)
FwCapsule file package        : $(FWCAP_SIG_HDR_TXT)
FwCapsule Signature type      : $(FWCAP_SIGN_CERT_TYPE_TXT)
FwCapsule Sign Key format     : $(FWCAP_SIGN_KEY_TYPE_TXT:& =^
   )
   "$(FWpriv)" - Signing Certificate key (full RSA key)
   "$(FWpub)" - Signing Certificate key (public key part)

===============================================================
=== Cryptocon.exe script to generate signed FwCapsule
===============================================================
Cryptocon.exe $(CRYPTOCON_CMDLINE_SIG)

===============================================================
=== Common Cryptocon FwCapsule build instructions 
===============================================================
 -c'FWrootPriv' -k'FWsignPriv' Create PKCS#1v1.5 signed FwCapsule (Note1)
 -c2 -x 'FWpriv'[,'pswd']      Create PKCS#7 signed FwCapsule (Note2, Note3)
 -f'file' input, un-signed BIOS image
 -o'file' output, signed FwCapsule image
 -y update an embedded FwCapsule Header, default-Hdr attached on top of BIOS
 -l'value' max size of a FwCapsule Header (file alignment)
 -n -k'key' insert Signer public 'key' into a signed image
 -r'rom.map' use a rom map from the external file
 -m embed the FwCapsule sign parameters without creating a signed image

Note1. -c'key1'-k'key2'    :take PKCS#1v2.1 DER(PEM) encoded RSA2048 keys
Note2. -c2 -x'key1'-k'key2':key1-PKCS#12(PFX) with optional PFX password;
                            key2-X.509(DER) with public 'key1'
Note3. -c2 -x command invokes external Msft signtool.exe

===============================================================
=== Extended Cryptocon FwCapsule build instructions
===============================================================
 -c2 -s Create serialized data block based on the rom map info
 -c2 -s -x'p7.sig' import PKCS#7 signed data from file into a FwCapsule
 -r2 use embedded rom map data 
<< KEEP

#---------------------------------------------------------------------------
# Should be the last step after creating of the ROM image. All fixups to the .ROM must be made prior to this step.
# check END target in the CORE.MAK and all .MAK files to make sure this step is not overriden
# Use AFTER_ROM as alternative target.
#---------------------------------------------------------------------------
End: $(FWCAPSULE_FILE_NAME)

#------------------------------------------------------------------------
# 1. Creating Signing descriptor table (RomLayout map) file
#------------------------------------------------------------------------

#--------------------
# Older Cores 4.6.3.x didn't generate RomLayout map file
# 1. Add rules to generate RomLayout.c file. Rules to generate RomLayout.c file are defined in newer versions of Core.mak (4.6.5.x)
# 2. Create binary file. Build rule is also defined in newer versions of Board.mak (4.6.5.0_Board_27)
#$(AMI_ROM_TABLE): $(BUILD_DIR)\RomLayout.c $(BUILD_DIR)\RomLayout.obj
#    @CL /Fo$(BUILD_DIR)\ $(CFLAGS) /TC $(BUILD_DIR)\RomLayout.c
#    @LINK /OUT:$(BUILD_DIR)\RomLayout.dll /DLL /SUBSYSTEM:NATIVE /NODEFAULTLIB /NOENTRY $(BUILD_DIR)\RomLayout.obj
#    pe2bin $(BUILD_DIR)\RomLayout.dll $@
#--------------------
!IFNDEF ROM_LAYOUT_EX
ROM_LAYOUT_EX = $(BUILD_DIR)\RomLayoutEx.bin
!ENDIF

$(ROM_LAYOUT_EX): $(UNSIGNED_BIOS_ROM) $(BUILD_DIR)\RomLayout.bin
	@if not exist $@ $(FWBUILD) $(UNSIGNED_BIOS_ROM) /s /m $@

#---------------------------------------------------------------------------
# 3. Embed Signing descriptor table "$(ROM_LAYOUT_EX)" inside "$(UNSIGNED_BIOS_ROM)"
#--------------------------------------------------------------------------
MOD_FWCAPSULE_HDR_FFS: $(ROM_LAYOUT_EX) $(UNSIGNED_BIOS_ROM)
	@echo ----Update "$(UNSIGNED_BIOS_ROM)" with Extended BIOS Rom Map "$(ROM_LAYOUT_EX)" and FwCapsule signing parameters
	$(CRYPTCON) $(CRYPTOCON_CMDLINE_MAP)

#---------------------------------------------------------------------------
# 4. Invoke cryptocon.exe to create Signed FwCapsule if CREATE_FWCAPSULE == 1
#---------------------------------------------------------------------------
$(FWCAPSULE_FILE_NAME): MOD_FWCAPSULE_HDR_FFS $(UNSIGNED_BIOS_ROM) $(ROM_LAYOUT_EX)
!IF "$(CREATE_FWCAPSULE)" == "1"
	@echo ----Create signed BIOS image "$(FWCAPSULE_FILE_NAME)"
	-$(CRYPTCON) $(CRYPTOCON_CMDLINE_SIG)
	@if not exist $@ @echo ERROR!!! Failed to create signed BIOS Image.
!IF "$(FWCAPSULE_FILE_FORMAT)" == "0"
# Target FWCAPSULE_FILE_NAME file is an original unsigned UNSIGNED_BIOS_ROM with Fw Signature block embedded as Ffs file
# Replace original UNSIGNED_BIOS_ROM with the signed one if this file will be used as input to Intel fitc or other Flash image packaging tool
	@if exist $@ @COPY $@ $(UNSIGNED_BIOS_ROM)
!ENDIF
!ENDIF #$(CREATE_FWCAPSULE) == 1
#---------------------------------------------------------------------------
# Display error log
#---------------------------------------------------------------------------
	@if exist make_sign_capsule_error.log @type make_sign_capsule_error.log
#---------------------------------------------------------------------------
# Display warning
#---------------------------------------------------------------------------
	@if not exist $@ @echo WARNING!!! Do not use un-signed "$(UNSIGNED_BIOS_ROM)" file as a BIOS update image.
#---------------------------------------------------------------------------
#
#####
#Example of an alternative way to build PKCS#7 signed Fw Capsule using Cryptocon.exe as a packaging tool and signing done by a msft signtool.exe
#Make sure to use the version of Microsoft SignTool.exe that supports /p7 switch
#Latest tool version can be downloaded as part of Win8 SDK from http://msdn.microsoft.com/en-us/windows/hardware/hh852363.aspx. 
#
#1. Optional step if new BIOS verification key $(FWpub) needs to be embedded into $(UNSIGNED_BIOS_ROM)
#$(CRYPTCON) -c2 -n -k $(FWpub) -f $(UNSIGNED_BIOS_ROM) -o $(UNSIGNED_BIOS_ROM)
#
#2. Create serialized data stream "fwcap_serialized" to be signed in step 3.
#$(CRYPTCON) -c2 -s -f $(UNSIGNED_BIOS_ROM) -o $(BUILD_DIR)\fwcap_serialized
#
#3. Create .p7 detached certificate file by signing of "fwcap_serialized":
#    3.1 sign using a certificate whose private key information is protected by a hardware cryptography module (e.g. HSM). 
#        A computer store is specified for the certification authority (CA) store; Certificate is identified by a Subject Name "My High Value Certificate" .
#Signtool sign /fd sha256 /p7 $(BUILD_DIR) /p7co 1.2.840.113549.1.7.1 /p7ce DetachedSignedData /sm /n "My High Value Certificate" $(BUILD_DIR)\fwcap_serialized
#    3.2 sign using a certificate stored in a password-protected PFX file "$(FWpriv)"
#Signtool sign /fd sha256 /p7 $(BUILD_DIR) /p7co 1.2.840.113549.1.7.1 /p7ce DetachedSignedData /f $(FWpriv) /p$(FW_PFX_Password) $(BUILD_DIR)\fwcap_serialized
#
#4. Creating Fw Capsule image $(FWCAPSULE_FILE_NAME) with .p7 signature embedded into a FwCap header
#$(CRYPTCON) -c2 -s -x $(BUILD_DIR)\fwcap_serialized.p7 -f $(UNSIGNED_BIOS_ROM) -o $(FWCAPSULE_FILE_NAME)
#####
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
