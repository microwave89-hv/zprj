#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**     5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093            **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#*************************************************************************
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelPfat/PfatBinary/PfatBinary.mak 4     10/29/12 3:45p Fredericko $
#
# $Revision: 4 $
#
# $Date: 10/29/12 3:45p $
#
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelPfat/PfatBinary/PfatBinary.mak $
# 
# 4     10/29/12 3:45p Fredericko
# [TAG]  		EIP84115
# [Category]  	Improvement
# [Description]  	Implementing PFAT function for Shark Bay
# define and use Pfat Binary macro
# [Files]  		pfatBinary.mak
# PfatBinary.sdl
# 
# 3     9/25/12 6:15p Fredericko
# 
# 2     9/17/12 4:25p Fredericko
# Removed UnNeeded make definitions
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name: PfatBinary.mak
#
# Description: Make file PfatBinary
#
#<AMI_FHDR_END>
#**********************************************************************
all: $(BUILD_DIR)\PfatBinary.ffs $(PfatBinary_DIR)\PfatBinary.mak

$(BUILD_DIR)\PfatBinary.bin : 
  copy $(PfatBinary) $(BUILD_DIR)\PfatBinary.bin $(SILENT_OUT)

$(BUILD_DIR)\PfatBinary.ffs : $(BUILD_DIR)\PfatBinary.bin 
  $(GENFFSFILE) -B $(BUILD_DIR) -V -o $@ -P1 <<$(BUILD_DIR)\PfatBinary.pkg
PACKAGE.INF
[.]
BASE_NAME                   = DummyName
FFS_FILEGUID                = 7934156D-CFCE-460E-92F5-A07909A59ECA
FFS_FILETYPE                = EFI_FV_FILETYPE_RAW
FFS_ATTRIB_CHECKSUM         = FALSE
FFS_ALIGNMENT               = 5

IMAGE_SCRIPT =
{
  		$(PROJECT_DIR)\$(BUILD_DIR)\PfatBinary.bin
}
<<KEEP
#-----------------------------------------------------------------------
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**     5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093            **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************
