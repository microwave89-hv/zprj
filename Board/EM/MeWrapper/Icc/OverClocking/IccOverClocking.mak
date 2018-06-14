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
#**********************************************************************
#
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/MeWrapper/Icc/IccOverClocking/IccOverClocking.mak 2     1/18/13 12:31a Klzhan $
#
# $Revision: 2 $
#
# $Date: 1/18/13 12:31a $
#
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/MeWrapper/Icc/IccOverClocking/IccOverClocking.mak $
# 
# 2     1/18/13 12:31a Klzhan
# [TAG]  		EIPNone
# [Category]  	Bug Fix
# [Symptom]  	ICC library not loaded when ME 9.5
# [Files]  		IccOverClocking.sdl
# IccOverClocking.dxs
# IccOverClocking.mak
# IccOverClocking.efi
# IccOverClocking9_5.dxs
# IccOverClocking9_5.efi
# IccProtocol.h
# IccOverClocking.cif
# 
# 1     2/08/12 1:07a Klzhan
# Initial Check in 
# 
# 2     9/26/11 6:21a Klzhan
# Fix build error with New EDK
# 
# 1     2/25/11 1:42a Klzhan
# Initial Check-in
# 
# 2     12/03/10 5:37a Klzhan
# Fix Build Error.
# 
# 1     12/03/10 5:10a Klzhan
# Initial Check-in.
# 
#
#**********************************************************************
#
#<AMI_FHDR_START>
#----------------------------------------------------------------------------
#
# Name:            IccOverClocking.mak
#
# Description:     Setup hooks for ICC.
#
#----------------------------------------------------------------------------
#<AMI_FHDR_END>
all : $(BUILD_DIR)\IccOverClocking.ffs $(BUILD_DIR)\IccOverClocking9_5.ffs

IccOverClocking_INCLUDES=\
            $(INTEL_PCH_INCLUDES)\
            $(EDK_INCLUDES)\
            $(EdkIIGlueLib_INCLUDES)\
            $(ME_INCLUDES)\
            $(ICC_INCLUDES)\

$(BUILD_DIR)\IccOverClocking.ffs : $(IccOverClocking_DIR)\$(@B).efi $(IccOverClocking_DIR)\$(@B).mak Core\FFS.mak
            $(MAKE) /$(MAKEFLAGS) /f Core\FFS.mak \
            CPFLAGS="$(GLOBAL_DEFINES) /D TIANO_RELEASE_VERSION=0x00080006 $(EXTRA_DEFINES) $(IccOverClocking_INCLUDES)" \
            BUILD_DIR=$(BUILD_DIR) SOURCE_DIR=$(IccOverClocking_DIR) \
            GUID=5BBA83E5-F027-4ca7-BFD0-16358CC9E123\
            NAME=$(@B)\
            TYPE=EFI_FV_FILETYPE_DRIVER \
            DEPEX1=$(IccOverClocking_DIR)\IccOverClocking.dxs\
            DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX \
            PEFILE=$(IccOverClocking_DIR)\$(@B).efi FFSFILE=$@ COMPRESS=1 \


$(BUILD_DIR)\IccOverClocking9_5.ffs : $(IccOverClocking_DIR)\IccOverClocking9_5.efi $(IccOverClocking_DIR)\IccOverClocking.mak Core\FFS.mak
            $(MAKE) /$(MAKEFLAGS) /f Core\FFS.mak \
            CPFLAGS="$(GLOBAL_DEFINES) /D TIANO_RELEASE_VERSION=0x00080006 $(EXTRA_DEFINES) $(IccOverClocking_INCLUDES)" \
            BUILD_DIR=$(BUILD_DIR) SOURCE_DIR=$(IccOverClocking_DIR) \
            GUID=8e68e3c5-fc59-4280-8467-3800d31a8162\
            NAME=$(@B)\
            TYPE=EFI_FV_FILETYPE_DRIVER \
            DEPEX1=$(IccOverClocking_DIR)\IccOverClocking9_5.dxs\
            DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX \
            PEFILE=$(IccOverClocking_DIR)\$(@B).efi FFSFILE=$@ COMPRESS=1 \

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