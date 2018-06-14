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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/CompilerStub/CompilerStub.mak 1     1/20/12 3:59a Jeffch $
#
# $Revision: 1 $
#
# $Date: 1/20/12 3:59a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/CompilerStub/CompilerStub.mak $
# 
# 1     1/20/12 3:59a Jeffch
# 
# 1     9/27/11 6:22a Wesleychen
# Intel EDK initially releases.
# 
# 3     11/06/09 4:27a Iminglin
# Edk-Dev-Snapshot-20090928
# 
# 2     9/02/09 3:24a Iminglin
# EIP24919
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	CompilerStub.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************

$(COMPILERSTUB) : CompilerStub

CompilerStub : $(BUILD_DIR)\CompilerStub.mak CompilerStubBin

$(BUILD_DIR)\CompilerStub.mak : $(CompilerStub_DIR)\$(@B).cif $(CompilerStub_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(CompilerStub_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

CompilerStubBin :
!IF "$(PROCESSOR)"=="x64"
	$(MAKE) /$(MAKEFLAGS) $(EDK_DEFAULTS)\
		/f $(BUILD_DIR)\CompilerStub.mak all\
		TYPE=LIBRARY
	$(MAKE) /$(MAKEFLAGS) $(EDK_DEFAULTS) BUILD_DIR=$(BUILD_DIR)\IA32\
		/f $(BUILD_DIR)\CompilerStub.mak all\
		TYPE=PEI_LIBRARY 
!ELSE
	$(MAKE) /$(MAKEFLAGS) $(EDK_DEFAULTS)\
		/f $(BUILD_DIR)\CompilerStub.mak all\
		TYPE=LIBRARY 
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