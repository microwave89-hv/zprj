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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/EdkIIGlue/EdkIIGlueRules.mak 1     1/20/12 3:47a Jeffch $
#
# $Revision: 1 $
#
# $Date: 1/20/12 3:47a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/EdkIIGlue/EdkIIGlueRules.mak $
# 
# 1     1/20/12 3:47a Jeffch
# Create Intel EDK 1117 Patch 7.
# 
# 1     1/20/12 3:26a Jeffch
# Create Intel EDK 1117 Patch 7.
# 
# 1     9/27/11 6:08a Wesleychen
# Intel EDK initially releases.
# 
# 3     11/12/10 1:16a Iminglin
# EIP47829
# 
# 2     6/02/10 4:06a Iminglin
# For backward compatiblity.
# 
# 1     9/18/09 1:43a Iminglin
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	<ComponentName>.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************
!INCLUDE $(EDK_DIR)\EdkRules.mak
#EXTRA_CFLAGS=$(EXTRA_CFLAGS) /X
#EXTRA_INCLUDES=$(EDK_INCLUDES) $(EXTRA_INCLUDES)
#EXTRA_DEFINES=$(EXTRA_DEFINES) /DEFI_S3_RESUME /DTIANO_RELEASE_VERSION=$(TIANO_RELEASE_VERSION)

!IF "$(PROCESSOR)"=="x64"
MDE_PROCESSOR=MDE_CPU_X64
!ELSE
MDE_PROCESSOR=MDE_CPU_$(PROCESSOR)
!ENDIF

EXTRA_DEFINES=$(EXTRA_DEFINES)  /D EdkII_GLUE_LIBRARY_IMPLEMENTATION\
                                /D $(MDE_PROCESSOR)\
                                /D EFI_BUILD_IN_GLUE_LIB
  
EXTRA_INCLUDES=$(EXTRA_INCLUDES)    $(MISCFRAMEWORK_INCLUDES)\
                                    $(EdkIIGlueLib_INCLUDES)

!IFDEF EDKIIModule
!IF "$(EDKIIModule)"=="DXEDRIVER"
EXTRA_LFLAGS = $(EXTRA_LFLAGS) $(DEST_DIR)\EdkIIGlueDxeDriverEntryPoint.obj
$(BUILD_DIR)\$(NAME).dll : $(DEST_DIR)\EdkIIGlueDxeDriverEntryPoint.obj
$(DEST_DIR)\EdkIIGlueDxeDriverEntryPoint.obj : $(EdkIIGlueLib_DIR)\EntryPoints\EdkIIGlueDxeDriverEntryPoint.c $(BUILD_DIR)\token.h
    $(CC) $(FINAL_CFLAGS) $(EXTRA_DEFINES) $(EXTRA_INCLUDES) /Fo$@ $(EdkIIGlueLib_DIR)\EntryPoints\EdkIIGlueDxeDriverEntryPoint.c
!ENDIF

!IF "$(EDKIIModule)"=="PEIM"
EXTRA_LFLAGS = $(EXTRA_LFLAGS) $(DEST_DIR)\EdkIIGluePeimEntryPoint.obj
$(BUILD_DIR)\$(NAME).dll : $(DEST_DIR)\EdkIIGluePeimEntryPoint.obj
$(DEST_DIR)\EdkIIGluePeimEntryPoint.obj : $(EdkIIGlueLib_DIR)\EntryPoints\EdkIIGluePeimEntryPoint.c $(BUILD_DIR)\token.h
    $(CC) $(FINAL_CFLAGS) $(EXTRA_DEFINES) $(EXTRA_INCLUDES) /Fo$@ $(EdkIIGlueLib_DIR)\EntryPoints\EdkIIGluePeimEntryPoint.c
!ENDIF

!IF "$(EDKIIModule)"=="SMMDRIVER"
EXTRA_LFLAGS = $(EXTRA_LFLAGS) $(DEST_DIR)\EdkIIGlueSmmDriverEntryPoint.obj
$(BUILD_DIR)\$(NAME).dll : $(DEST_DIR)\EdkIIGlueSmmDriverEntryPoint.obj
$(DEST_DIR)\EdkIIGlueSmmDriverEntryPoint.obj : $(EdkIIGlueLib_DIR)\EntryPoints\EdkIIGlueSmmDriverEntryPoint.c $(BUILD_DIR)\token.h
    $(CC) $(FINAL_CFLAGS) $(EXTRA_DEFINES) $(EXTRA_INCLUDES) /Fo$@ $(EdkIIGlueLib_DIR)\EntryPoints\EdkIIGlueSmmDriverEntryPoint.c
!ENDIF
!ENDIF

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