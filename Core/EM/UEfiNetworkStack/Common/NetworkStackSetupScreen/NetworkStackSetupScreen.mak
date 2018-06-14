# #**********************************************************************#
#**********************************************************************#
#**                                                                  **#
#**        (C)Copyright 1985-2008, American Megatrends, Inc.         **#
#**                                                                  **#
#**                       All Rights Reserved.                       **#
#**                                                                  **#
#**             6145-F Northbelt Pkwy, Norcross, GA 30071            **#
#**                                                                  **#
#**                       Phone: (770)-246-8600                      **#
#**                                                                  **#
#**********************************************************************#
#**********************************************************************#
#**********************************************************************#
# $Header: /Alaska/BIN/Modules/Network/UEFINetworkStack II/COMMON/NetworkStackSetupScreen/NetworkStackSetupScreen.mak 1     6/02/11 11:47a Hari $ 
#
# $Revision: 1 $
#
# $Date: 6/02/11 11:47a $(BUILD_DIR)\NetworkStackSetupScreen.mak NETWORKSTACKSETUPSCREENSDB
#**********************************************************************#
# Revision History
# ----------------

#<AMI_FHDR_START>
#---------------------------------------------------------------------------
# Name:			NetworkStackSetupScreen.mak
#
# Description:	Make file for the NetworkStackSetupScreen component
#
#---------------------------------------------------------------------------
#<AMI_FHDR_END>
all : NetworkStackSetupScreen

NetworkStackSetupScreen : $(BUILD_DIR)\NetworkStackSetupScreen.mak NetworkStackSetupScreenBin

SetupSdbs : $(BUILD_DIR)\NetworkStackSetupScreen.mak NETWORKSTACKSETUPSCREENSDB

$(BUILD_DIR)\NetworkStackSetupScreen.mak : $(NETWORK_STACK_SETUP_SCREEN_DIR)\NetworkStackSetupScreen.cif $(NETWORK_STACK_SETUP_SCREEN_DIR)\NetworkStackSetupScreen.mak $(BUILD_RULES)
	$(CIF2MAK) $(NETWORK_STACK_SETUP_SCREEN_DIR)\NetworkStackSetupScreen.cif $(CIF2MAK_DEFAULTS)

NETWORKSTACKSETUPSCREENSDB :
        copy $(NETWORK_STACK_SETUP_SCREEN_DIR)\NetworkStackSetupScreen.h $(BUILD_DIR)
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\NetworkStackSetupScreen.mak all\
		TYPE=SDB NAME=NETWORKSTACKSETUPSCREEN MAKEFILE=$(BUILD_DIR)\NetworkStackSetupScreen.mak STRING_CONSUMERS=$(NETWORK_STACK_SETUP_SCREEN_DIR)\NetworkStackSetupScreen.sd

NetworkStackSetupScreenBin : $(AMIDXELIB)
        copy $(NETWORK_STACK_SETUP_SCREEN_DIR)\NetworkStackSetupScreen.h $(BUILD_DIR)
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\NetworkStackSetupScreen.mak all\
		GUID=0029DE6A-E024-4eb8-A91D-9F23AA1F4E92\
		ENTRY_POINT=InitNetworkStackVar\
		TYPE=BS_DRIVER\
		COMPRESS=1

#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2008, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************
