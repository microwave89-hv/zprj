#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2007, American Megatrends, Inc.         **
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
# $Header: /Alaska/BIN/Core/Modules/PciBus/PciBus.mak 13    4/05/11 11:08a Yakovlevs $
#
# $Revision: 13 $
#
# $Date: 4/05/11 11:08a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Core/Modules/PciBus/PciBus.mak $
# 
# 13    4/05/11 11:08a Yakovlevs
# [TAG]  		EIP38174
# [Category]  	New Feature
# [Description]  	Added generic support to handle
# [Files]  		PciBus.c; PciHostBridge.c;  PciBus.h;  PciHostBridge.c;
# PciPort.c;
# 
# 12    1/28/11 2:58p Yakovlevs
# [TAG]  		EIP43879
# [Category]  	New Feature
# [Description]  	Added PciPortOemGetOptRom() OEM Hook to override
# content of the PCI Device Option ROM.
# [Files]  		PciBus.c; PciPort.c; PciPort.h; PciBus.mak; PciBus.sdl
# 
# 11    8/16/10 1:11p Yakovlevs
# Added OEM_PCI_DEVICE_SET_ASPM for custom Aspm Programming.
# 
# 10    9/22/09 6:01p Yakovlevs
# 1.	Added Definitions for OEM_PCI_PROGRAM_DEVICE_CALLBACK_LIST;
# OEM_PCI_SKIP_DEVICE_CALLBACK_LIST and OEM_PCI_DEVICE_ATTRIBUTES_LIST to
# support addingh porting hooks trough eLinks
# 
# 9     4/28/09 3:49p Yakovlevs
# Changes related to AmiBoardInfo protocol and Multiplatform support.
# 
# 8     11/14/08 1:31p Yakovlevs
# Added unconditionaly PciRoot it installs AMI Board Info Protocol
# 
# 7     10/01/08 7:09p Yakovlevs
# Updated AMI FUNC HEADER information.
# 
# 6     9/25/08 11:45a Yakovlevs
# Changes in build structure  to support new features.
# 
# 5     10/18/07 11:22a Felixp
# PciPort.c added
# 
# 4     8/22/07 6:56p Felixp
# Exlude PciBusSetup.c from the list of files compiled during PciBus and
# PciRootBridge build (set OBJECTS to blank string).
# 
# 3     4/18/07 11:11p Felixp
# 
# 2     4/12/07 3:53p Yakovlevs
# Removed unused libraryes from module link process.
# 
# 1     3/12/07 12:07p Yakovlevs
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	PciBus.mak
#
# Description:	Make file to build PciBus Driver
#
#<AMI_FHDR_END>
#**********************************************************************
all : PciBus

PciBus : $(BUILD_DIR)\PciBus.mak PciBusBin

!IF "$(AMI_ROOT_BRIDGE_SUPPORT)"=="1"
PciBus : PciRootBridgeBin
!ENDIF

$(BUILD_DIR)\PciBus.mak : $(PCIBUS_DIR)\$(@B).cif $(PCIBUS_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(PCIBUS_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

PciBusBin : $(AMIDXELIB) $(AMICSPLib) $(PCIBUSSRCLIB)
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
        /f $(BUILD_DIR)\PciBus.mak all\
        MAKEFILE=$(PCIBUS_DIR)\PciBus.mak \
        GUID=3C1DE39F-D207-408a-AACC-731CFB7F1DD7\
        ENTRY_POINT=PciBusEntryPoint\
        TYPE=BS_DRIVER DEPEX1= LIBRARIES=\
        "CFLAGS=$(CFLAGS) /D\"OEM_PCI_PROGRAM_DEVICE_CALLBACK_LIST=$(OEM_PROGRAM_PCI_DEVICE)\" \
                /D\"OEM_PCI_SKIP_DEVICE_CALLBACK_LIST=$(OEM_SKIP_PCI_DEVICE)\" \
                /D\"OEM_PCI_DEVICE_SET_ASPM_CALLBACK_LIST=$(OEM_PCI_DEVICE_SET_ASPM)\" \
                /D\"OEM_PCI_DEVICE_SET_LNK_SPEED_CALLBACK_LIST=$(OEM_PCI_DEVICE_SET_LNK_SPEED)\" \
                /D\"OEM_PCI_DEVICE_GET_OPT_ROM_CALLBACK_LIST=$(OEM_PCI_DEVICE_GET_OPT_ROM)\" \
                /D\"OEM_PCI_DEVICE_OUT_OF_RESOURCES_CALLBACK_LIST=$(OEM_PCI_DEVICE_OUT_OF_RESOURCES)\" \
                /D\"OEM_PCI_DEVICE_ATTRIBUTE_CALLBACK_LIST=$(OEM_PCI_ATTRIBUTES)\"" \
        "OBJECTS=$(BUILD_DIR)\$(PCIBUS_DIR)\PciPort.obj"\
		COMPRESS=1\

!IF "$(AMI_ROOT_BRIDGE_SUPPORT)"=="1"
PciRootBridgeBin : $(AMIDXELIB) $(AMICSPLib) $(PCIBUSSRCLIB)
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\PciBus.mak all\
		NAME=PciRootBridge\
		MAKEFILE=$(PCIBUS_DIR)\PciBus.mak \
		GUID=80E66E0A-CCD1-43fa-A7B1-2D5EE0F13910 \
		ENTRY_POINT=InitializePCIHostBridge \
		DEPEX1=$(PCIBUS_DIR)\PciRootBridge.DXS \
		TYPE=BS_DRIVER LIBRARIES= \
        "OBJECTS=$(BUILD_DIR)\$(PCIBUS_DIR)\PciPort.obj"\
		COMPRESS=1\
!ENDIF

#---------------------------------------------------------------------------
#		Create PCI Bus Setup Screens
#---------------------------------------------------------------------------
SetupSdbs : $(BUILD_DIR)\PciBus.mak PCIBUSSDB
SetupBin : $(BUILD_DIR)\PciBusSetup.obj

PCIBUSSDB :
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\PciBus.mak all\
		TYPE=SDB NAME=PciBus MAKEFILE=$(BUILD_DIR)\PciBus.Mak STRING_CONSUMERS=$(PCIBUS_DIR)\PciBus.sd
$(BUILD_DIR)\PciBusSetup.obj : $(PCIBUS_DIR)\PciBusSetup.c $(BUILD_DIR)\SetupStrTokens.h
	$(CC) $(CFLAGS) /Fo$(BUILD_DIR)\ $(PCIBUS_DIR)\PciBusSetup.c
#---------------------------------------------------------------------------


#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2007, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************