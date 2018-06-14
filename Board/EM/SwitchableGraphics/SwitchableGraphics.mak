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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/SwitchableGraphics/SwitchableGraphics.mak 2     9/09/12 11:26p Joshchou $
#
# $Revision: 2 $
#
# $Date: 9/09/12 11:26p $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/SwitchableGraphics/SwitchableGraphics.mak $
# 
# 2     9/09/12 11:26p Joshchou
# [TAG]  		None
# [Category]  	Improvement
# [Description]  	Tpv module support for sharkbay.
# [Files]  		SwitchableGraphics.sdl
# SwitchableGraphics.mak
# SwitchableGraphics.sd
# SwitchableGraphics.uni
# SwitchableGraphics.chm
# SwitchableGraphics.cif
# 
# 1     6/27/11 5:13a Alanlin
# [TAG]  		EIP61848
# [Category]  	New Feature
# [Description]  	Initial check-in.Integrated SwitchableGraphics Intel
# Reference code 0.6.0
# [Files]  		SwitchableGraphics.cif
# SwitchableGraphics.sdl
# SwitchableGraphics.mak
# SwitchableGraphics.sd
# SwitchableGraphics.uni
# 
# 
# 4     9/17/10 3:21p Alexp
# 
# [TAG]          EIP43103 
# [Category]  Function Request
# [Severity]      Normal
# [Symptom]    Initial check-in of iIntel Switchable Graphics module
# [RootCause] Request to implement Intel Huron River SG reference code .
# [Solution]    Initial check-in. 
# [Files]    
#         SwitchableGraphics.cif; *.chm; *.sdl; *.mak; *.sd;*.uni
# 
#
#*************************************************************************
#<AMI_FHDR_START>
#
# Name: SwitchableGraphics.mak
#
# Description: Makfile for SG Setup menu.
# 
#
#<AMI_FHDR_END>
#*************************************************************************
all : SwitchableGraphics

SwitchableGraphics: $(BUILD_DIR)\SwitchableGraphics.mak

$(BUILD_DIR)\SwitchableGraphics.mak : $(SwitchableGraphics_DIR)\SwitchableGraphics.cif $(SwitchableGraphics_DIR)\SwitchableGraphics.mak $(BUILD_RULES)
    $(CIF2MAK) $(SwitchableGraphics_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

#---------------------------------------------------------------------------
#        Create Sg Setup Screen(s)
#---------------------------------------------------------------------------
SetupSdbs : SwitchableGraphicsSDB 

SwitchableGraphicsSDB : $(BUILD_DIR)\SwitchableGraphics.mak
        $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
        /f $** all\
        TYPE=SDB NAME=SwitchableGraphics STRING_CONSUMERS=$(SwitchableGraphics_DIR)\SwitchableGraphics.sd

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
