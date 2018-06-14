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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/EfiDriverLib/EfiDriverLib.mak 1     1/20/12 4:06a Jeffch $
#
# $Revision: 1 $
#
# $Date: 1/20/12 4:06a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/EfiDriverLib/EfiDriverLib.mak $
# 
# 1     1/20/12 4:06a Jeffch
# Create Intel EDK 1117 Patch 7.
# 
# 1     9/27/11 6:30a Wesleychen
# Intel EDK initially releases.
# 
# 2     9/02/09 3:44a Iminglin
# EIP24919
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	EfiDriverLib.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************
$(EFIDRIVERLIB) : EfiDriverLib

$(BUILD_DIR)\EfiDriverLib.lib : EfiDriverLib

EfiDriverLib : $(BUILD_DIR)\EfiDriverLib.mak EfiDriverLibBin

$(BUILD_DIR)\EfiDriverLib.mak : $(EfiDriverLib_DIR)\$(@B).cif $(EfiDriverLib_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(EfiDriverLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

!IF "$(PROCESSOR)"!="IPF"
EfiDriverLibBin : $(CPUIA32LIB)
!ELSE
EfiDriverLibBin : $(CPUIA64LIB)
!ENDIF

EfiDriverLibBin : $(EDKGUIDLIB) $(EDKPROTOCOLLIB) $(EDKFRAMEWORKPROTOCOLLIB) $(EFIGUIDLIB) $(EFIPROTOCOLLIB) $(ARCHPROTOCOLLIB) $(EFICOMMONLIB)
	$(MAKE) /$(MAKEFLAGS) $(EDK_DEFAULTS)\
		/f $(BUILD_DIR)\EfiDriverLib.mak all\
		TYPE=LIBRARY
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