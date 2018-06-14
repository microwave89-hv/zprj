#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************

#**********************************************************************
# $Header: /Alaska/BIN/Chipset/Template/CSPLibrary/CspLib.mak 25    3/15/11 5:24p Felixp $
#
# $Revision: 25 $
#
# $Date: 3/15/11 5:24p $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Chipset/Template/CSPLibrary/CspLib.mak $
# 
# 25    3/15/11 5:24p Felixp
# Include $(CSP_LIB_DIR)\CspLibGeneric.h at the beginning of
# AMICSPLIBINc.h
# 
# 24    2/22/11 3:48p Artems
# EIP 51548 - replaced TABs with spaces
# 
# 23    2/22/11 12:38p Artems
# Updated file header. Removed dependency of Fid.c from Fid.ffs (EIP
# 52936)
# 
# 20    5/25/10 6:06p Artems
# Fixed bug, use CORE_COMBINED_VERSION instead of CORE_REVISION
# 
# 19    5/21/10 4:38p Artems
# Changed backward compatibility token from CORE_REVISION to 
# CORE_COMBINED_VERSION
# 
# 18    5/07/10 3:57p Artems
# Build CSP library separately for PEI and DXE phase
# 
# 17    5/06/10 12:22p Artems
# EIP 38241 - $FID signature is absent
# 
# 16    4/05/10 5:50p Artems
# Added Core 4.6.3 backward compatibility fix
# 
# 15    3/25/10 3:07p Artems
# EIP 33953: Added eLink infrastructure to support runtime shadow ram
# writing
# 
# 14    12/02/09 4:52p Robert
# Added changes for support for Revision 2 of the Firmware Version
# Structure
# 
# 13    8/26/09 10:59a Robert
# Adding back the changes from checkin #11.  This was accidentally
# overwritten in checkin #12
# 
# 12    8/14/09 10:47a Robert
# Added FID.asm to the component for compliance with AMI Utility
# specification
# 
# 11    8/11/09 12:34p Felixp
# Improvement (EIP 24965). New method of contributing files to CspLib
# library. Modules that contribute files to CspLib should now use new
# notation.
# 1. AMI_CSP_LIB_INCLUDE_FILES is replaced with dependency from
# $(BUILD_DIR)\AMICSPLIBInc.H (no plus needed between files)
# 2. AMI_CSP_LIB_OBJS is replaced with dependency from AMICSPLibBin
# 3. AMI_CSP_LIB_LIBRARY_PATH should not be used
# Items #1 & #2 are improvements. Old macros based approach only worked
# for modules that are above than CspLib in the project tree.
# Item #3 is a cleanup.
# 
# 10    6/11/09 5:43p Robert
# Comment updates for CHM and coding standard
# 
# 9     10/13/07 11:41p Michaela
# Added CspLibGeneric.c to CSP library
# 
# 8     8/25/06 11:02a Felixp
# 
# 7     8/24/06 3:40p Felixp
# Preliminary x64 support (work in progress)
# 
# 6     12/08/05 11:19a Felixp
# 
# 5     11/21/05 6:51p Felixp
# dependency for $(BUILD_DIR)\AMICSPLIBInc.H added
# 
# 4     10/12/05 8:38p Felixp
# CspLibPei is no longer a separate FFS file. It is now linked with PEI
# Core
# CspLib.mak,CspLib.lib, and CspLib.cif modified. 
# CspLibPei.dxe removed
# 
# 3     4/19/05 2:52p Sivagarn
# Changed the dependency order
# 
# 2     3/25/05 11:44a Sivagarn
# Fixed a build issue related to wrong dependency
# 
# 1     1/21/05 12:46p Sivagarn
# Initial Checkin - Version 0.05
#
#**********************************************************************

#<AMI_FHDR_START>
#---------------------------------------------------------------------------
# Name:     CspLib.mak
#
# Description:  
#   Make file for the CSP Library. CSP library contains all library 
#   functions related to chipset and CPU. The main idea for this library is 
#   to consolidate porting hooks related to various components 
#   (like CSM, SMM etc) in respective chipset files say NB, SB, CPU etc.  
#   This library can be built us a LIB file or as various FFS files.  
#   The MACROS and library init functions mask the actual implementation
#   which is controlled by the SDL token
#
#---------------------------------------------------------------------------
#<AMI_FHDR_END>

all : AMICSPLib $(BUILD_DIR)\AMICSPLIBInc.H

!IF "$(CORE_COMBINED_VERSION)"==""
CORE_COMBINED_VERSION=0x40280
!ENDIF

!IF $(CORE_COMBINED_VERSION) >= 0x40280
$(AMICSPLib) : $(BUILD_DIR)\AMICSPLIBInc.H AMICSPLib $(BUILD_DIR)\Fid.ffs AMICspLibPei AMICspLibDxe
!ELSE
$(AMICSPLib) : $(BUILD_DIR)\AMICSPLIBInc.H AMICSPLib AMICspLibPei AMICspLibDxe
!ENDIF

CSP_LIB_DIR = Core\CspLib

AMICSPLib : $(BUILD_DIR)\AMICSPLib.mak AMICSPLibBin

$(BUILD_DIR)\AMICspLib.mak : $(CSP_LIB_DIR)\CSPLib.cif $(CSP_LIB_CIF_FILES) $(CSP_LIB_DIR)\CspLib.mak $(BUILD_RULES)
    $(CIF2MAK) $(CSP_LIB_DIR)\CSPLib.cif $(CIF2MAK_DEFAULTS) $(CSP_LIB_CIF_FILES)

#---------------------------------------------------------------------------
#       Add Generic Functions to CSP Library
#---------------------------------------------------------------------------

AMICSPLibBin : $(BUILD_DIR)\CspLibGeneric.obj 

{$(CSP_LIB_DIR)}.c{$(BUILD_DIR)}.obj::
    $(CC) $(CFLAGS) /D\"RUNTIME_SHADOW_RAM_WRITE_LIST=$(RuntimeShadowRamWrite)\" /I $(CSP_LIB_DIR) /Fo$(BUILD_DIR)\ $<
    
$(BUILD_DIR)\CspLibGeneric.obj : $(CSP_LIB_DIR)\CspLibGeneric.c

#---------------------------------------------------------------------------
#       Generate CSP Library
#---------------------------------------------------------------------------
$(BUILD_DIR)\AMICSPLIBInc.H : $(AMI_CSP_LIB_INCLUDE_FILES:+= )
   $(ECHO) #include"$(BUILD_DIR)\token.h" > $@
   $(ECHO) #include"$(CSP_LIB_DIR)\CspLibGeneric.h" >> $@
   $(SILENT) for %%f in ($(**:"=)) do $(ECHO) #include"%%f" >> $@

AMICSPLibBin : $(AMI_CSP_LIB_OBJS) 
    $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
        /f $(BUILD_DIR)\AMICSPLib.mak all\
        NAME=AMICSPLib\
        OBJECTS=\
        TYPE=LIBRARY
    $(MAKE) /$(MAKEFLAGS) BUILD_ROOT=$(BUILD_DIR) "EXT_OBJS=$(**:Build\=Build\IA32\)" PROJECT_DIR=$(PROJECT_DIR)\
        /f $(BUILD_DIR)\AMICSPLib.mak all\
        BUILD_DIR=$(BUILD_DIR)\IA32\
        NAME=AMICSPLib\
        OBJECTS=\
        TYPE=PEI_LIBRARY

#---------------------------------------------------------------------------
#       Generate CSP Library PEI
#---------------------------------------------------------------------------
CORE_PEIBin : $(BUILD_DIR)\CspLibPei.lib

$(BUILD_DIR)\CspLibPei.lib : $(BUILD_DIR)\AMICSPLib.mak AMICspLibPei

CSP_LIB_PEI_OBJECTS =\
$$(BUILD_DIR)\$(CSP_LIB_DIR)\CspLibPei.obj

!IF $(CORE_COMBINED_VERSION) >= 0x40280

$(BUILD_DIR)\Fid.ffs : $(BUILD_DIR)\AMICspLib.mak
    $(MAKE) /$(MAKEFLAGS) EXT_OBJS= $(BUILD_DEFAULTS)\
        /f $(BUILD_DIR)\AMICspLib.mak bin\
        NAME=Fid OBJECTS=$(BUILD_DIR)\$(CSP_LIB_DIR)\Fid.obj\
        MAKEFILE=$(BUILD_DIR)\AMICspLib.mak \
        TYPE=BINARY
    $(MAKE) /f Core\FFS.mak \
        BUILD_DIR=$(BUILD_DIR) \
        GUID=3FD1D3A2-99F7-420b-BC69-8BB1D492A332 \
        TYPE=EFI_FV_FILETYPE_FREEFORM \
        FFSFILE=$@ COMPRESS=0 NAME=$(@B)\
        RESOURCE=$(BUILD_DIR)\Fid.bin \
        SECTION_GUID=2EBE0275-6458-4AF9-91ED-D3F4EDB100AA \

!ELSE

CSP_LIB_PEI_OBJECTS =\
$(CSP_LIB_PEI_OBJECTS)\
$$(BUILD_DIR)\$(CSP_LIB_DIR)\Fid.obj

!ENDIF

AMICspLibPei : $(AMIPEILIB)
    $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
        /f $(BUILD_DIR)\AMICspLib.mak all\
        NAME=CspLibPei\
        MAKEFILE=$(BUILD_DIR)\AMICspLib.mak \
        OBJECTS="$(CSP_LIB_PEI_OBJECTS)" \
        TYPE=PEI_LIBRARY


#---------------------------------------------------------------------------
#       Generate CSP Library DXE
#---------------------------------------------------------------------------
AMICspLibDxe :
    $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
        /f $(BUILD_DIR)\AMICspLib.mak all\
        NAME=CspLibDxe\
        MAKEFILE=$(BUILD_DIR)\AMICspLib.mak \
        GUID=CD84562C-6864-40a3-A081-C8D35E82B920 \
        OBJECTS=$(BUILD_DIR)\$(CSP_LIB_DIR)\CspLibDxe.obj \
        DEPEX1=$(CSP_LIB_DIR)\CspLibDxe.DXS DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX \
        ENTRY_POINT=CspLibDxe_Init \
        TYPE=BS_DRIVER \
        COMPRESS=1

#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************