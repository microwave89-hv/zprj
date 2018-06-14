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
# $Header: /Alaska/SOURCE/Core/EDK/PeiMain/CORE_PEISrc.mak 11    2/05/11 3:41p Artems $
#
# $Revision: 11 $
#
# $Date: 2/05/11 3:41p $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Core/EDK/PeiMain/CORE_PEISrc.mak $
# 
# 11    2/05/11 3:41p Artems
# Added support to build source in PI 0.91 or PI 1.0 mode
# 
# 10    3/05/09 1:07p Felixp
# Minor improvements:
#  - Unconditional optimization (despite debug flag settings) is removed
#  - Headers updated
# 
# 9     8/25/06 10:58a Felixp
# 
# 8     8/25/06 10:57a Felixp
# 
# 7     8/25/06 10:56a Felixp
# 
# 6     8/24/06 9:43a Felixp
# Preliminary x64 support (work in progress)
# DXE Core interfaces are no longer passed from PEI Core.
# They are linked directly with DXE Core
# 
# 5     5/20/06 12:34a Felixp
# Optimization is always on 
# 
# 4     5/19/06 10:37p Felixp
# 
# 3     3/17/06 4:28p Felixp
# 
# 2     3/13/06 5:25p Felixp
# 
# 1     3/13/06 1:57a Felixp
# 
# 2     12/02/05 11:19a Felixp
# 
# 1     1/28/05 12:44p Felixp
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	CORE_PEISrc.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************
all : CORE_PEI_LIB

$(CORE_PEI_LIB) : CORE_PEI_LIB

CORE_PEI_LIB : $(BUILD_DIR)\CORE_PEISrc.mak CORE_PEI_LIBBin

$(BUILD_DIR)\CORE_PEISrc.mak : $(CORE_PEI_SRC_DIR)\$(@B).cif $(CORE_PEI_SRC_DIR)\$(@B).mak $(BUILD_RULES)
!IF $(PI_SPECIFICATION_VERSION)>=0x00010000
        $(CIF2MAK) $(CORE_PEI_SRC_DIR)\$(@B).cif $(CORE_PEI_SRC_DIR)\CORE_PEI_PI\$(@B)Pi.cif $(CIF2MAK_DEFAULTS)
!ELSE
	$(CIF2MAK) $(CORE_PEI_SRC_DIR)\$(@B).cif $(CORE_PEI_SRC_DIR)\CORE_PEI_FRAMEWORK\$(@B)Framework.cif $(CIF2MAK_DEFAULTS)
!ENDIF

CORE_PEI_LIBBin : $(BUILD_DIR)\FoundationPei.lib
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\CORE_PEISrc.mak all\
		TYPE=PEI_LIBRARY LIBRARY_NAME=$(CORE_PEI_LIB)\
        "MY_INCLUDES=/I$(Foundation_DIR)"\
!IF "$(x64_BUILD)"=="1"
		"MY_DEFINES=/Dx64_BUILD_SUPPORT"\
!ENDIF
		EXT_HEADERS=$(BUILD_DIR)\token.h NAME=CORE_PEISrc
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