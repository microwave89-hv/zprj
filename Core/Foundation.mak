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
# $Header: /Alaska/SOURCE/Core/EDK/Foundation.mak 5     3/05/10 5:30p Felixp $
#
# $Revision: 5 $
#
# $Date: 3/05/10 5:30p $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Core/EDK/Foundation.mak $
# 
# 5     3/05/10 5:30p Felixp
# Enhancement:
# Targets of types GUID_LIBRARY and PEI_GUID_LIBRARY are updated to
# reduce length of the command line.
# 
# 4     10/13/06 9:05p Felixp
# 
# 3     8/25/06 10:56a Felixp
# 
# 2     8/24/06 9:39a Felixp
# Preliminary x64 support (work in progress)
# 
# 1     5/19/06 11:28p Felixp
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	Foundation.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************
all : Foundation

!IF "$(x64_BUILD)"=="1"
FOUNDATION_PEI_GUID_LIB=$(BUILD_DIR)\FoundationPeiGuidLib.lib
!ELSE
FOUNDATION_PEI_GUID_LIB=$(BUILD_DIR)\FoundationGuidLib.lib
!ENDIF

!IF "$(PROCESSOR)"=="" || "$(PROCESSOR)"=="IA32"
FoundationCpu_DIR=$(FoundationIa32_DIR)
!ELSEIF "$(PROCESSOR)"=="x64"
FoundationCpu_DIR=$(Foundationx64_DIR)
!ELSEIF "$(PROCESSOR)"=="IPF"
FoundationCpu_DIR=$(FoundationIPF_DIR)
!ENDIF

Foundation : $(BUILD_DIR)\Foundation.mak FoundationBin FoundationPeiBin

$(BUILD_DIR)\Foundation.mak : $(Foundation_DIR)\$(@B).cif $(Foundation_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(Foundation_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

FoundationBin : $(BUILD_DIR)\FoundationProtocolLib.lib $(BUILD_DIR)\FoundationGuidLib.lib
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\Foundation.mak all\
		"CFLAGS=$(CFLAGS) /I$(Foundation_DIR) /I$(FoundationCpu_DIR)"\
		TYPE=LIBRARY NAME=Foundation

FoundationPeiBin : $(BUILD_DIR)\FoundationPpiLib.lib $(FOUNDATION_PEI_GUID_LIB)
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		BUILD_DIR=$(BUILD_DIR)\IA32\
		/f $(BUILD_DIR)\Foundation.mak all\
		"CFLAGS=$(CFLAGS) /I$(Foundation_DIR) /I$(FoundationCpu_DIR)"\
		TYPE=PEI_LIBRARY NAME=Foundation LIBRARY_NAME=$(BUILD_DIR)\FoundationPei.lib

$(BUILD_DIR)\Foundation.lib $(BUILD_DIR)\FoundationPei.lib : Foundation

$(BUILD_DIR)\FoundationProtocolLib.lib : $(Foundation_DIR)\Protocol\*.h
	$(MAKE) /$(MAKEFLAGS) $(NO_EXT_OBJS_BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\Core.mak all\
        "MY_INCLUDES=/I$(Foundation_DIR)"\
		TYPE=GUID_LIBRARY NAME=$(@B)\
        "HEADERS=$(Foundation_DIR)\Protocol\^*.h"

$(BUILD_DIR)\FoundationPpiLib.lib : $(Foundation_DIR)\Ppi\*.h
	$(MAKE) /$(MAKEFLAGS) $(NO_EXT_OBJS_BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\Core.mak all\
        "MY_INCLUDES=/I$(Foundation_DIR)"\
		TYPE=PEI_GUID_LIBRARY NAME=$(@B)\
        "HEADERS=$(Foundation_DIR)\Ppi\^*.h"

$(BUILD_DIR)\FoundationGuidLib.lib : $(Foundation_DIR)\Guid\*.h
	$(MAKE) /$(MAKEFLAGS) $(NO_EXT_OBJS_BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\Core.mak all\
        "MY_INCLUDES=/I$(Foundation_DIR)"\
		TYPE=GUID_LIBRARY NAME=$(@B)\
        "HEADERS=$(Foundation_DIR)\Guid\^*.h"

!IF "$(x64_BUILD)"=="1"
$(BUILD_DIR)\FoundationPeiGuidLib.lib : $(Foundation_DIR)\Guid\*.h
	$(MAKE) /$(MAKEFLAGS) $(NO_EXT_OBJS_BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\Core.mak all\
        "MY_INCLUDES=/I$(Foundation_DIR)"\
		TYPE=PEI_GUID_LIBRARY NAME=$(@B)\
        "HEADERS=$(Foundation_DIR)\Guid\^*.h"
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