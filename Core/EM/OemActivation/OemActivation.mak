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
# $Header: /Alaska/SOURCE/Modules/OemActivation/OemActivation.mak 9     1/12/12 9:24a Vyacheslava $
#
# $Revision: 9 $
#
# $Date: 1/12/12 9:24a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/OemActivation/OemActivation.mak $
# 
# 9     1/12/12 9:24a Vyacheslava
# Removed dependency on SMM protocols. Changed type of module to
# BS_DRIVER
# 
# 8     10/18/11 10:00a Vyacheslava
# [TAG]  		EIP70134
# [Description]  	Changed GUID to let AFU know that SW SMI number is
# changed. 
# 
# 7     10/03/11 11:04a Vyacheslava
# [TAG]  		EIP64110 
# [Category]  	Spec Update
# [Severity]  	Normal
# [Description]  	(7) IsRoceveryOverSerial, NetBootHotkey, OpromTxT,
# SimpleBootFlag, SLP10, SlpSupport, SmiVariable
# 
# 6     9/22/11 11:22a Vyacheslava
# [TAG]  		EIP64110 
# [Category]  	Spec Update
# [Severity]  	Normal
# [Description]  	Changed according to Aptio 4.6.5.x Components Porting
# Guide. 
# 
# 5     7/07/11 11:18a Vyacheslava
# 
# 4     5/26/11 11:33a Vyacheslava
# 
# 3     4/29/11 12:42p Vyacheslava
# [TAG]  		EIP58139
# [Category]  	New Feature
# [Description]  	Added macros to place Oem Activation Key in NCB. 
# 
# 2     12/17/10 1:43p Vyacheslava
# [TAG]  		EIP48520 
# [Category]  	Improvement
# [Description]  	Added checking for version of the CSP Library. 
# 
# 1     11/18/10 1:15p Vyacheslava
# Initial creation
# 
# 
#*************************************************************************
#<AMI_FHDR_START>
#
# Name: OemActivation.mak
#
# Description: Make file for OemActivation eModule.
#
#<AMI_FHDR_END>
#*************************************************************************

!IF "$(OEM_ACTIVATION_TABLE_LOCATION)"=="0" && "$(CSP_LIB_MAJOR_VER)"=="00" && "$(CSP_LIB_MINOR_VER)"<"17"
!ERROR To use OEM Activation 3.0 CSP Library must have version 00.17 or newer. 
!ENDIF

!IFNDEF PI_SPECIFICATION_VERSION
PI_SPECIFICATION_VERSION = 0
!ENDIF

all : OemActivation

OemActivation : $(BUILD_DIR)\OemActivation.mak OemActivationBin

$(BUILD_DIR)\OemActivation.mak : $(OemActivation_DIR)\$(@B).cif $(OemActivation_DIR)\$(@B).mak $(BUILD_RULES)
    $(CIF2MAK) $(OemActivation_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)


!IF "$(OEM_ACTIVATION_TABLE_LOCATION)"=="0"

OemActivationBin : $(AMIDXELIB)
    $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
        /f $(BUILD_DIR)\OemActivation.mak all\
        GUID=76D5CF91-0C55-434E-97C2-D2825C82E610\
        ENTRY_POINT=OemActivation_EntryPoint\
        TYPE=BS_DRIVER\
        DEPEX1=$(OemActivation_DIR)\OemActivation.dxs\
        DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX\
        "EXT_HEADERS=$(BUILD_DIR)\Token.h"\
        COMPRESS=1

!ELSE 

OemActivationObjs = $(BUILD_DIR)\$(OemActivation_DIR)\OemActivation.obj

OemActivationBin : $(AMIDXELIB)
    $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
        /f $(BUILD_DIR)\OemActivation.mak all\
        OBJECTS="$(OemActivationObjs)" \
        GUID=76D5CF91-0C55-434E-97C2-D2825C82E610\
        ENTRY_POINT=OemActivation_EntryPoint\
        TYPE=BS_DRIVER\
        DEPEX1=$(OemActivation_DIR)\OemActivation.dxs\
        DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX\
        "EXT_HEADERS=$(BUILD_DIR)\Token.h"\
        COMPRESS=1

#---------------------------------------------------------------------------
#               Create Launch SCLEAN Pei Component
#---------------------------------------------------------------------------
OemActivationHook : $(BUILD_DIR)\OemActivation.mak OemActivationHookBin

OemActivationHookObjs = $(BUILD_DIR)\$(OemActivation_DIR)\OemActivationHook.obj

OemActivationHookBin : $(AMIDXELIB)
            $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
            /f $(BUILD_DIR)\OemActivation.mak all\
            "CFLAGS=$(CFLAGS:/W4=/W3) /I$(OFBD_DIR)" \
            OBJECTS="$(OemActivationHookObjs)" \
            NAME=OemActivation \
            TYPE=LIBRARY LIBRARY_NAME=$(OEM_ACTIVATION_LIB)

$(OEM_ACTIVATION_LIB) : OemActivationHook

OEM_ACTIVATION_DESCRIPTOR=HOLE(\
name=OEM_ACTIVATION, address=$(OEM_ACTIVATION_TABLE_ADDRESS),\
offset=$(OEM_ACTIVATION_TABLE_ADDRESS)-$(FLASH_BASE),\
size=$(OEM_ACTIVATION_TABLE_SIZE)\
)

!ENDIF

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
