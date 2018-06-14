#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2006, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************

#**********************************************************************
# $Header: /Alaska/SOURCE/Modules/MPG/Calpella/MiscFramework/SmmControlLib/SmmControlLib.mak 1     10/15/08 2:20p Fasihm $
#
# $Revision: 1 $
#
# $Date: 10/15/08 2:20p $
#**********************************************************************
# Revision History
# ----------------
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	FrameworkPpiLib.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************
all : SmmControlLib

$(SmmControlLib_LIB) : SmmControlLib

SmmControlLib : $(BUILD_DIR)\SmmControlLib.mak SmmControlLibBin

$(BUILD_DIR)\SmmControlLib.mak : $(SmmControlLib_DIR)\$(@B).cif $(SmmControlLib_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(SmmControlLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

SmmControlLibBin :
  	$(MAKE) /$(MAKEFLAGS) $(EDK_DEFAULTS)\
!IF "$(x64_BUILD)"=="1"
		/f $(BUILD_DIR)\SmmControlLib.mak all\
		"MY_INCLUDES=$(EDK_INCLUDES) /I$(MISCFRAMEWORK_DIR) /I$(EDK_INCLUDES) /I$(PROJECT_DIR)\Include\IndustryStandard" \
    	TYPE=LIBRARY
    $(MAKE) /$(MAKEFLAGS) $(EDK_DEFAULTS)\
    	BUILD_DIR=$(BUILD_DIR)\IA32\
		/f $(BUILD_DIR)\SmmControlLib.mak all\
		"MY_INCLUDES=$(EDK_INCLUDES) /I$(MISCFRAMEWORK_DIR) /I$(EDK_INCLUDES) /I$(PROJECT_DIR)\Include\IndustryStandard" \
    	TYPE=PEI_LIBRARY
!ELSE
		/f $(BUILD_DIR)\SmmControlLib.mak all\
		"MY_INCLUDES=$(EDK_INCLUDES) /I$(MISCFRAMEWORK_DIR) /I$(EDK_INCLUDES) /I$(PROJECT_DIR)\Include\IndustryStandard" \
    	TYPE=PEI_LIBRARY
!ENDIF
		
#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2006, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************