#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/Platform/AcpiPlatform.mak 5     12/18/12 11:03p Alanlin $
#
# $Revision: 5 $
#
# $Date: 12/18/12 11:03p $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/Platform/AcpiPlatform.mak $
# 
# 5     12/18/12 11:03p Alanlin
# [TAG] EIP107188
# [Category] Important
# [Severity] Important
# [Description] USB 3.0 port can't work when RTD3 is Enabled in setup
# menu.
# [Files] Acpiplatform.c, Acpiplatform.mak, Acpiplatform.sd,
# Acpiplatform.uni.
# 
# 4     10/15/12 11:41a Alanlin
# [TAG]           None
# [Category]      Spec Update
# [Severity]      Important
# [Description]   Updated for RC 0.7.1
# 
# 3     4/25/12 1:28p Yurenlai
# [TAG]         None
# [Category]    Improvement
# [Description] Initilize ACPI DXE Platform Policy.
# [Files]       AcpiPlatform.c, AcpiPlatform.mak
# 
# 1     2/09/12 12:30a Yurenlai
# Initial check in.
#
#*************************************************************************
#<AMI_FHDR_START>
#
# Name:         AcpiPlatform.mak
#
# Description:  This make file builds AcpiPlatform module PEI & DXE and SMI
#               components and link them to respective binary
#
#<AMI_FHDR_END>
#*************************************************************************

all : AcpiPlatformPei AcpiPlatform AcpiPlatformSmi

#---------------------------------------------------------------------------
#			Generic AcpiPlatform dependencies
#---------------------------------------------------------------------------

$(BUILD_DIR)\AcpiPlatform.mak : $(AcpiPlatform_DIR)\AcpiPlatform.cif $(BUILD_RULES)
	$(CIF2MAK) $(AcpiPlatform_DIR)\AcpiPlatform.cif $(CIF2MAK_DEFAULTS)

#----------------------------------------------------------------------------
#           Add files into CSP Library
#----------------------------------------------------------------------------
AMI_CSP_LIB_LIBRARY_PATH = $(AMI_CSP_LIB_LIBRARY_PATH);$(AcpiPlatform_DIR)

AMI_CSP_LIB_OBJS = $(AMI_CSP_LIB_OBJS) \
$(BUILD_DIR)\AcpiPlatformCspLib.obj

{$(AcpiPlatform_DIR)}.c{$(BUILD_DIR)}.obj::
    $(CC) $(CFLAGS) /I $(AcpiPlatform_DIR) /Fo$(BUILD_DIR)\ $<

$(BUILD_DIR)\AcpiPlatformCspLib.obj : $(AcpiPlatform_DIR)\AcpiPlatformCspLib.c

CORE_DXEBin: $(AMICSPLib)

#---------------------------------------------------------------------------
#		Create AcpiPlatform PEI Component
#---------------------------------------------------------------------------
AcpiPlatformPei : $(BUILD_DIR)\AcpiPlatform.mak AcpiPlatformPeiBin

AcpiPlatformPeiBin : $(AMIPEILIB) $(AMICSPLib)
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\AcpiPlatform.mak all\
		NAME=AcpiPlatformPei\
		MAKEFILE=$(BUILD_DIR)\AcpiPlatform.mak \
		"CFLAGS=$(CFLAGS)"\
		OBJECTS="$(AcpiPlatformPei_OBJECTS)" \
		GUID=333BB2A3-4F20-4c8b-AC38-0672D74315F8\
		ENTRY_POINT=AcpiPlatformPeiInit \
		TYPE=PEIM \
		DEPEX1=$(AcpiPlatform_DIR)\AcpiPlatformPei.DXS DEPEX1_TYPE=EFI_SECTION_PEI_DEPEX \
		COMPRESS=0

#{333BB2A3-4F20-4c8b-AC38-0672D74315F8}
#DEFINE_GUID(<<name>>, 
#0x333bb2a3, 0x4f20, 0x4c8b, 0xac, 0x38, 0x6, 0x72, 0xd7, 0x43, 0x15, 0xf8);
#---------------------------------------------------------------------------
#		Create AcpiPlatform DXE Component
#---------------------------------------------------------------------------
AcpiPlatform: $(BUILD_DIR)\AcpiPlatform.mak AcpiPlatformBin

AcpiPlatformBin :  $(AMIDXELIB) $(AMICSPLib) $(DxeKscLib_LIB) $(AcpiProtocolLib_LIB) $(INTEL_SA_PROTOCOL_LIB)
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\AcpiPlatform.mak all\
		GUID=8B5FBABD-F51F-4942-BF16-16AAA38AE52B\
		"MY_INCLUDES=$(INTEL_PLATFORM_PROTOCOL_INCLUDES) $(INTEL_PCH_INCLUDES) $(ACPI_PLATFORM_INCLUDES) $(AcpiProtocolLib_INCLUDES) $(PLATFORM_INFO_INCLUDES) $(DxeKscLib_INCLUDES) $(DPPM_DIR_INCLUDES) /I $(INTEL_SA_PROTOCOL_LIB_DIR)"\
		ENTRY_POINT=AcpiPlatformInit\
		OBJECTS="$(AcpiPlatform_OBJECTS)" \
		TYPE=BS_DRIVER \
		DEPEX1=$(AcpiPlatform_DIR)\AcpiPlatform.dxs\
		DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX\
		COMPRESS=1

#----------------------------------------------------------------------------
#       Create AcpiPlatform SMI Component
#----------------------------------------------------------------------------
AcpiPlatformSmi : $(BUILD_DIR)\AcpiPlatform.mak AcpiPlatformSmiBin

AcpiPlatformSmiBin : $(AMICSPLib) $(AMIDXELIB)
    $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
        /f $(BUILD_DIR)\AcpiPlatform.mak all\
        NAME=AcpiPlatformSmi\
        MAKEFILE=$(BUILD_DIR)\AcpiPlatform.mak \
        OBJECTS="$(AcpiPlatformSmi_OBJECTS)" \
        GUID=DFD8D5CC-5AED-4820-A2B6-5C55E4E640EF \
        ENTRY_POINT=InitializeAcpiPlatformSMISmm \
        "CFLAGS=$(CFLAGS) $(ACPI_PLATFORM_INCLUDES) $(PLATFORM_INFO_INCLUDES) $(SB_INCLUDES)"\
        "EXT_HEADERS=$(BUILD_DIR)\token.h"\
        TYPE=BS_DRIVER \
        DEPEX1=$(AcpiPlatform_DIR)\AcpiPlatformSmi.DXS DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX \
        COMPRESS=1

#{DFD8D5CC-5AED-4820-A2B6-5C55E4E640EF}
#DEFINE_GUID(<<name>>, 
#0xdfd8d5cc, 0x5aed, 0x4820, 0xa2, 0xb6, 0x5c, 0x55, 0xe4, 0xe6, 0x40, 0xef);

#---------------------------------------------------------------------------
#		Create IgdOpRegion Setup Screens
#---------------------------------------------------------------------------
SetupSdbs : $(BUILD_DIR)\AcpiPlatform.mak AcpiPlatformSDB


AcpiPlatformSDB :
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\AcpiPlatform.mak all \
		TYPE=SDB NAME=AcpiPlatform STRING_CONSUMERS=$(AcpiPlatform_DIR)\AcpiPlatform.sd


#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
#**                                                                     **
#**                       All Rights Reserved.                          **
#**                                                                     **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
#**                                                                     **
#**                       Phone: (770)-246-8600                         **
#**                                                                     **
#*************************************************************************
#*************************************************************************
