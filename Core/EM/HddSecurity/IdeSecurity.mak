#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
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
# $Header: /Alaska/SOURCE/Modules/HddSecurity/IdeSecurity.mak 9     8/11/13 11:58p Srikantakumarp $
#
# $Revision: 9 $
#
# $Date: 8/11/13 11:58p $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/HddSecurity/IdeSecurity.mak $
# 
# 9     8/11/13 11:58p Srikantakumarp
# [TAG]  		EIP123442
# [Category]  	Improvement
# [Description]  	Create a new Plug-In way in the IdeSecurity Module for
# OEM append sd file into
# [Files]  		IdeSecurity.sdl, IdeSecurity.mak
# 
# 8     6/06/13 4:04a Rameshr
# [TAG]  		EIP106423
# [Category]  	Improvement
# [Description]  	HddPassword Support in UEFI Raid and Legacy Raid. And
# also taken care where there is no Conin Device avilable in the post
# [Files]  		IdeSecurity.cif,IdeSecurity.sdl,IdeSecurity.mak,IdeSecurityB
# dsCall.c,HddPassword.c, Ahcibus.c, Pidebus.h
# 
# 7     4/25/13 9:22a Kapilporwal
# [TAG]  		EIP108583
# [Category]  	New Feature
# [Description]  	support set HDD password in same page
# [Files]  		IdeSecurity.cif, IdeSecurity.mak, IdeSecurity.sdl,
# IdeSecurity.uni, IdeSecurityCommon.sd, IdeSecuritySetup.c,
# HddPassword.c, HddPassword.h, HddPassword.mak, HddPassword.sdl
# 
# 6     10/11/11 1:55a Rameshr
# [TAG]  		EIP69246
# [Category]  	Improvement
# [Description]  	Made the  SECURITY_SUPPORT as the Master token and
# removed the IdeSecurity_Support token.
# [Files]  		IdeSecurity.c, IdeSecurity.h, IdeSecurity.mak,
# IdeSecurity.sdl
# 
# 5     12/03/10 12:24a Rameshr
# [TAG] - EIP 48770
# [Category]- BUG FIX
# [Severity]- Minor
# [Symptom] - HddSecurity build error when disable the IDEBUS module..
# [RootCause]- IdebusLib used with IdeSecurity Module.
# [Solution] - Removed IdebusLib usage from source and mak file.
# [Files] - Idesecurity.c, IdeSecurity.mak
# 
# 4     12/09/09 12:17p Krishnakumarg
# EIP 31797 : IDE Security API documentation. Added comments whereever
# possible and modified files for coding standard
# 
# 3     3/18/09 11:26a Fredericko
# EIP19618 removed dependency on foundation.lib
# 
# 2     3/13/09 3:43p Fredericko
# 
# 1     28/02/08 6:40p Anandakrishnanl
# Created new HddSecurity module.  Isolated IdeSecurity and IdeSmm from
# IdeBus driver to be compatable with the AHCI Bus driver.
# 
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name: IdeSecurity_mak
#
# Description:  Make file to build IDESecurity Driver Sources.
#
#<AMI_FHDR_END>
#**********************************************************************
all : IdeSecurity

IdeSecurity : $(BUILD_DIR)\IdeSecurity.mak IdeSecurityBin

$(BUILD_DIR)\IdeSecurity.mak : $(IDESECURITY_DIR)\$(@B).cif $(IDESECURITY_DIR)\$(@B).mak $(BUILD_RULES)
    $(CIF2MAK) $(IDESECURITY_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

IdeSecurityBin: $(AMIDXELIB)
    $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
        /f $(BUILD_DIR)\IdeSecurity.mak all\
        GUID=A9B700CF-019E-4d8b-A3A7-88E1EA01699E\
        ENTRY_POINT=IdeSecurityEntryPoint \
        TYPE=BS_DRIVER \
        COMPRESS=1\
        "OBJECTS=$(BUILD_DIR)\$(IDESECURITY_DIR)\IdeSecurity.obj"

#---------------------------------------------------------------------------
#       Create IDE Bus Setup Screens
#---------------------------------------------------------------------------
SetupSdbs : $(BUILD_DIR)\IdeSecurity.Sdb
SetupBin : $(BUILD_DIR)\IdeSecuritySetup.obj

#IdeSecuritySdb :
#       $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
#       /f $(BUILD_DIR)\IdeSecurity.mak all\
#       MAKEFILE=$(IDESECURITY_DIR)\IdeSecurity.mak \
#       TYPE=SDB STRING_CONSUMERS=$(IDESECURITY_DIR)\IdeSecurity.sd
#$(BUILD_DIR)\IdeSecuritySetup.obj : $(IDESECURITY_DIR)\IdeSecuritySetup.c $(BUILD_DIR)\SetupStrTokens.h
#       $(CC) $(CFLAGS) /Fo$(BUILD_DIR)\ $(IDESECURITY_DIR)\IdeSecuritySetup.c

!IF (DEFINED(IDE_SECURITY_PLUG_IN) && "$(IDE_SECURITY_PLUG_IN)" == "1")

$(BUILD_DIR)\IdeSecurity.sdb : $(IDESECURITY_PLUG_IN_SD) $(IDESECURITY_DIR)\IdeSecurity.uni
    $(STRGATHER) -i INCLUDE -parse -newdb -db $(BUILD_DIR)\IdeSecurity.sdb $(IDESECURITY_DIR)\IdeSecurity.uni
    $(STRGATHER) -scan -db $(BUILD_DIR)\IdeSecurity.sdb -od $(BUILD_DIR)\IdeSecurity.sdb $(IDESECURITY_PLUG_IN_SD)

!ELSE # !IF (DEFINED(IDE_SECURITY_PLUG_IN) && "$(IDE_SECURITY_PLUG_IN)" == "1")

!IFNDEF "$(SECUITY_SETUP_ON_SAME_PAGE)"

!IF "$(SECUITY_SETUP_ON_SAME_PAGE)" == "1"

$(BUILD_DIR)\IdeSecurity.sdb : $(IDESECURITY_DIR)\IdeSecurityCommon.sd $(IDESECURITY_DIR)\IdeSecurity.uni
    $(STRGATHER) -i INCLUDE -parse -newdb -db $(BUILD_DIR)\IdeSecurity.sdb $(IDESECURITY_DIR)\IdeSecurity.uni
    $(STRGATHER) -scan -db $(BUILD_DIR)\IdeSecurity.sdb -od $(BUILD_DIR)\IdeSecurity.sdb $(IDESECURITY_DIR)\IdeSecurityCommon.sd

!ELSE

$(BUILD_DIR)\IdeSecurity.sdb : $(IDESECURITY_DIR)\IdeSecurity.sd $(IDESECURITY_DIR)\IdeSecurity.uni
    $(STRGATHER) -i INCLUDE -parse -newdb -db $(BUILD_DIR)\IdeSecurity.sdb $(IDESECURITY_DIR)\IdeSecurity.uni
    $(STRGATHER) -scan -db $(BUILD_DIR)\IdeSecurity.sdb -od $(BUILD_DIR)\IdeSecurity.sdb $(IDESECURITY_DIR)\IdeSecurity.sd

!ENDIF # !IF SECUITY_SETUP_ON_SAME_PAGE = "1"

!ELSE # !IFNDEF "$(SECUITY_SETUP_ON_SAME_PAGE)"

$(BUILD_DIR)\IdeSecurity.sdb : $(IDESECURITY_DIR)\IdeSecurity.sd $(IDESECURITY_DIR)\IdeSecurity.uni
    $(STRGATHER) -i INCLUDE -parse -newdb -db $(BUILD_DIR)\IdeSecurity.sdb $(IDESECURITY_DIR)\IdeSecurity.uni
    $(STRGATHER) -scan -db $(BUILD_DIR)\IdeSecurity.sdb -od $(BUILD_DIR)\IdeSecurity.sdb $(IDESECURITY_DIR)\IdeSecurity.sd

!ENDIF # !IFNDEF SECUITY_SETUP_ON_SAME_PAGE

!ENDIF # !IF (DEFINED(IDE_SECURITY_PLUG_IN) && "$(IDE_SECURITY_PLUG_IN)" == "1")

$(BUILD_DIR)\IdeSecuritySetup.obj : $(IDESECURITY_DIR)\IdeSecuritySetup.c $(BUILD_DIR)\SetupStrTokens.h
        $(CC) $(CFLAGS) /Fo$(BUILD_DIR)\ $(IDESECURITY_DIR)\IdeSecuritySetup.c

CORE_DXEBin : $(BUILD_DIR)\IdeSecurityBdsCall.obj

$(BUILD_DIR)\IdeSecurityBdsCall.obj : $(IDESECURITY_DIR)\IdeSecurityBdsCall.c
        $(CC) $(CFLAGS) /Fo$(BUILD_DIR)\ $(IDESECURITY_DIR)\IdeSecurityBdsCall.c

#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************
