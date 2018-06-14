#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ISCT/IsctGuidLib/IsctGuidLib.mak 1     9/02/12 11:20p Bensonlai $
#
# $Revision: 1 $
#
# $Date: 9/02/12 11:20p $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ISCT/IsctGuidLib/IsctGuidLib.mak $
# 
# 1     9/02/12 11:20p Bensonlai
# Intel Smart Connect Technology initially releases.
#
#
#**********************************************************************
#<AMI_FHDR_START>
#
# Name: IsctGuidLib.mak
#
# Description: Make file to build IsctSmm components.
#
#
#<AMI_FHDR_END>
#**********************************************************************

all : IsctGuidLib

$(IsctGuidLib_LIB) : IsctGuidLib

IsctGuidLib : $(BUILD_DIR)\IsctGuidLib.mak IsctGuidLibBin

$(BUILD_DIR)\IsctGuidLib.mak : $(IsctGuidLib_DIR)\$(@B).cif $(IsctGuidLib_DIR)\$(@B).mak $(BUILD_RULES)
  $(CIF2MAK) $(IsctGuidLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

IsctGuidLib_INCLUDES =\
            $(EDK_INCLUDES)\
            $(INTEL_PCH_INCLUDES)\
            $(EdkIIGlueLib_INCLUDES)\

IsctGuidLibBin :
            $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
            /f $(BUILD_DIR)\IsctGuidLib.mak all\
            "MY_INCLUDES=$(IsctGuidLib_INCLUDES)" \
            TYPE=LIBRARY
!IF "$(x64_BUILD)"=="1"
            $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS) BUILD_DIR=$(BUILD_DIR)\IA32\
            /f $(BUILD_DIR)\IsctGuidLib.mak all\
            "MY_INCLUDES=$(IsctGuidLib_INCLUDES)" \
            TYPE=PEI_LIBRARY
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
