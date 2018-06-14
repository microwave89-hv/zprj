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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/Platform/EfiCombineImage/EfiCombineImage.mak 1     12/18/12 11:10p Alanlin $
#
# $Revision: 1 $
#
# $Date: 12/18/12 11:10p $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/Platform/EfiCombineImage/EfiCombineImage.mak $
# 
# 1     12/18/12 11:10p Alanlin
# 
# 
#*************************************************************************
#<AMI_FHDR_START>
#
# Name:
#
# Description:
#
#<AMI_FHDR_END>
#*************************************************************************
all : EfiCombineImage EfiCombineImage1 EfiCombineImage2

EfiCombineImage: \
!IF "$(NVidia_Optimus_dGPU)" == "1"
$(BUILD_DIR)\EfiCombineImageFile.ffs 
!ENDIF

EfiCombineImage1: \
!IF "$(AMD_PX_CHELSEA_dGPU)" == "1"
$(BUILD_DIR)\EfiCombineImageFile1.ffs 
!ENDIF

EfiCombineImage2: \
!IF "$(AMD_PX_THAMES_dGPU)" == "1"
$(BUILD_DIR)\EfiCombineImageFile2.ffs 
!ENDIF

$(BUILD_DIR)\EfiCombineImage.mak : $(EfiCombineImage_DIR)\$(@B).cif $(EfiCombineImage_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(EfiCombineImage_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

AMI_CSP_LIB_OBJS = $(AMI_CSP_LIB_OBJS) \
$(BUILD_DIR)\EfiCombineImage.obj 

{$(EfiCombineImage_DIR)}.c{$(BUILD_DIR)}.obj::
    $(CC) $(CFLAGS) /Fo$(BUILD_DIR)\ $<

$(BUILD_DIR)\EfiCombineImage.obj : $(EfiCombineImage_DIR)\EfiCombineImage.c

!IF "$(NVidia_Optimus_dGPU)" == "1"
$(BUILD_DIR)\EfiCombineImageFile.ffs : $(EfiCombineImageFile)
	$(MAKE) /f Core\FFS.mak \
	BUILD_DIR=$(BUILD_DIR) \
	GUID=$(NVidia_dGPU_MAKFILE_GUID) \
	TYPE=EFI_FV_FILETYPE_FREEFORM \
	BINFILE=$** FFSFILE=$@ COMPRESS=1 NAME=$(**B)
!ENDIF

!IF "$(AMD_PX_CHELSEA_dGPU)" == "1"
$(BUILD_DIR)\EfiCombineImageFile1.ffs : $(EfiCombineImageFile1)
	$(MAKE) /f Core\FFS.mak \
	BUILD_DIR=$(BUILD_DIR) \
	GUID=$(AMD_CHELSEA_MAKFILE_GUID) \
	TYPE=EFI_FV_FILETYPE_FREEFORM \
	BINFILE=$** FFSFILE=$@ COMPRESS=1 NAME=$(**B)
!ENDIF

!IF "$(AMD_PX_THAMES_dGPU)" == "1"
$(BUILD_DIR)\EfiCombineImageFile2.ffs : $(EfiCombineImageFile2)
	$(MAKE) /f Core\FFS.mak \
	BUILD_DIR=$(BUILD_DIR) \
	GUID=$(AMD_THAMES_MAKFILE_GUID) \
	TYPE=EFI_FV_FILETYPE_FREEFORM \
	BINFILE=$** FFSFILE=$@ COMPRESS=1 NAME=$(**B)
!ENDIF

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
