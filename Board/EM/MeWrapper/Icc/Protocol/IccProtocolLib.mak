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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/MeWrapper/Icc/IccProtocolLib/IccProtocolLib.mak 1     2/08/12 1:05a Klzhan $
#
# $Revision: 1 $
#
# $Date: 2/08/12 1:05a $
#
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/MeWrapper/Icc/IccProtocolLib/IccProtocolLib.mak $
# 
# 1     2/08/12 1:05a Klzhan
# Initial Check in 
# 
# 1     2/25/11 1:41a Klzhan
# Initial Check-in
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
# Name:            IccProtocolLib.mak
#
# Description:     MakeFile for IccProtocolLib
#
#----------------------------------------------------------------------------
#<AMI_FHDR_END>
all : IccProtocolLib

$(IccProtocol_LIB) : IccProtocolLib

IccProtocolLib : $(BUILD_DIR)\IccProtocolLib.mak IccProtocolLibBin

$(BUILD_DIR)\IccProtocolLib.mak : $(IccProtocol_DIR)\$(@B).cif $(IccProtocol_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(IccProtocol_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

IccProtocolLib_INCLUDES =\
            $(EDK_INCLUDES)\
            $(INTEL_PCH_INCLUDES)\

IccProtocolLibBin : 
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		/f $(BUILD_DIR)\IccProtocolLib.mak all\
		"MY_INCLUDES=$(IccProtocolLib_INCLUDES)" \
		TYPE=LIBRARY \
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