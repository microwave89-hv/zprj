#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2012, American Megatrends, Inc.            **
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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/SwitchableGraphics/Sg TPV/Sg nVidia API/MXM30.mak 2     9/09/12 11:12p Joshchou $
#
# $Revision: 2 $
#
# $Date: 9/09/12 11:12p $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/SwitchableGraphics/Sg TPV/Sg nVidia API/MXM30.mak $
# 
# 2     9/09/12 11:12p Joshchou
# [TAG]  		None
# [Category]  	Improvement
# [Description]  	Tpv module support for sharkbay.
# [Files]  		MXM30.mak
# Mxm30Dxe.dxs
# Mxm30Dxe.c
# Mxm30Efi.c
# NBCIEfi.c
# MxmInt15.asm
# MXM30.cif
# 
# 1     6/27/11 5:25a Alanlin
# [TAG]  		EIP61848
# [Category]  	New Feature
# [Description]  	Initial check-in.Integrated SwitchableGraphics Intel
# Reference code 0.6.0
# [Files]  		MXM30.cif
# MXM30.sdl
# MXM30.mak
# Mxm30Dxe.dxs
# Mxm30Dxe.c
# Mxm30Efi.c
# NBCIEfi.c
# MxmInt15.asm
# Mxm30ElkCreek4.mxm
# Mxm30ElkCreekIII.mxm
# 
# 
# 2     9/23/10 1:04p Alexp
# change the build target
# 
# 1     9/17/10 1:15p Alexp
# [TAG]    	  EIP43103 
# [Category]  Function Request
# [Severity]	  Normal
# [Symptom]    Initial check-in of SgTPV module
# [RootCause] Request to implement SG reference code .
# [Solution]	Initial check-in. 
# [Files]	
#         Mxm30.cif;*.sdl;*.mak;
#         Mxm30Dxe.c;*.dxs 
#         Mxm30efi.c
#         MxmInt15.asm
#         NbciEfi.c
#         Mxm30ElkCreek3(4).mxm
# 
#*************************************************************************
#<AMI_FHDR_START>
#
# Name: MXM30.mak
#
# Description: Make file to build Switchable Graphics MXM component
#
#<AMI_FHDR_END>
#*************************************************************************
SgTpv: MXM30

MXM30 : $(BUILD_DIR)\MXM30.mak Mxm30DxeBin $(BUILD_DIR)\MXMdat.ffs

$(BUILD_DIR)\MXM30.mak : $(MXM30_DIR)\MXM30.cif $(MXM30_DIR)\MXM30.mak $(BUILD_RULES)
	$(CIF2MAK) $(MXM30_DIR)\MXM30.cif $(CIF2MAK_DEFAULTS)

#--------------------------------------------------------------------------
# 1.
#--------------------------------------------------------------------------
BUILD_MXM_DIR = $(BUILD_DIR)\$(MXM30_DIR)

##SGDxeBin :  $(BUILD_MXM_DIR)\Mxm30Efi.obj $(BUILD_MXM_DIR)\NbciEfi.obj
#SGDxeBin :  $(BUILD_MXM_DIR)\Mxm30Efi.obj

##$(BUILD_MXM_DIR)\Mxm30Efi.obj $(BUILD_MXM_DIR)\NbciEfi.obj: $(MXM30_DIR)\Mxm30Efi.c $(MXM30_DIR)\NbciEfi.c
#$(BUILD_MXM_DIR)\Mxm30Efi.obj: $(MXM30_DIR)\Mxm30Efi.c
#    $(CC) $(CFLAGS) $(MXM_INCLUDES) /I$(MXM30_DIR) /Fo$@ $(MXM30_DIR)\$(@F)

MXM_DXE_OBJECTS = \
$(BUILD_MXM_DIR)\Mxm30Dxe.obj\
$(BUILD_MXM_DIR)\Mxm30Efi.obj\

#$(BUILD_MXM_DIR)\Nbci.obj\

MXM_INCLUDES= \
    /I $(MXM30_DIR)\
    /I$(CORE_DIR)\
    $(INTEL_MPG_INCLUDES)\
    $(INTEL_MCH_INCLUDES)\
    $(INTEL_PCH_INCLUDES)\
    /I$(NB_BOARD_DIR)\
    /I$(SB_BOARD_DIR)

Mxm30DxeBin : $(AMIDXELIB) $(AMICSPLib)
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\MXM30.mak all\
		NAME=Mxm30Dxe\
		MAKEFILE=$(BUILD_DIR)\MXM30.mak \
		GUID=31A0B6EF-A400-4419-8327-0FB134AA59E7 \
		ENTRY_POINT=MxmDriverEntryPoint\
		DEPEX1=$(MXM30_DIR)\Mxm30Dxe.DXS DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX\
    	"MY_INCLUDES=$(MXM_INCLUDES)"\
		"OBJECTS=$(MXM_DXE_OBJECTS)"\
		TYPE=RT_DRIVER\
		COMPRESS=1

#--------------------------------------------------------------------------
# 2.
#--------------------------------------------------------------------------
$(BUILD_DIR)\MXMint15.obj: $(MXM30_DIR)\MXMint15.asm
    $(ASM16) $(AFLAGS16) /Fo$(BUILD_DIR)\ $(MXM30_DIR)\$(@B).asm

#--------------------------------------------------------------------------
# 3.
#---------------------------------------------------------------------------
# Build Mxm block file. In case external utils want to update Mxm 
# Don't change the GUID. LocateMXMffs expects this GUID.
#---------------------------------------------------------------------------
$(BUILD_DIR)\MXMdat.ffs : $(MXM30_DIR)\$(MXM_FILE_NAME)
    $(MAKE) /f Core\FFS.mak \
		NAME=$(@B) \
        BUILD_DIR=$(BUILD_DIR)  SOURCE_DIR=$(MXM30_DIR) \
        GUID=6707536E-46AF-42d3-8F6C-15F2F202C234 \
        TYPE=EFI_FV_FILETYPE_FREEFORM \
        BINFILE=$** FFSFILE=$@ COMPRESS=1 NAME=$(**B)

#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2012, American Megatrends, Inc.            **
#**                                                                     **
#**                       All Rights Reserved.                          **
#**                                                                     **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
#**                                                                     **
#**                       Phone: (770)-246-8600                         **
#**                                                                     **
#*************************************************************************
#*************************************************************************
