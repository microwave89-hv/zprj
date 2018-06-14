#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************
#
# $Header: /Alaska/SOURCE/Modules/USBRecovery/UsbRecov.mak 12    10/17/12 5:06a Roberthsu $
#
# $Revision: 12 $
#
# $Date: 10/17/12 5:06a $
#
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/USBRecovery/UsbRecov.mak $
# 
# 12    10/17/12 5:06a Roberthsu
# [TAG]				EIP77332
# [Category]		Improvement
# [Description]		Implement pei loadfirmware.
# [Files]				LoadFirmware.cif,LoadFirmware.sdl,LoadFirmware.mak,PeiRenesa
# s.c,PeiRenesas.h,DxeRenesas.c,DxeRenesas.h,UsbRecov.mak
# 
# 11    10/14/10 2:42p Olegi
# 
# 10    10/11/10 4:51p Olegi
# XHCI support added.
# 
# 9     3/03/09 7:24p Olegi
# Added EHCI support.
# 
# 8     10/21/08 5:56p Michaela
# Added EHCI-related fixes for issues 
# that may occur if EHCI is used before 
# USB Recovery is invoked:
#   Added SDL Tokens: 
#     PEI_EHCI_PCI_BDFS and 
#     PEI_EHCI_MEM_BASE_ADDRESSES. 
# 
# Removed/modified some debugging 
# development code:
#   Removed SDL Tokens: 
#     USBR_DEBUG_SUPPORT and 
#     USBR_SERIAL_PORT_AVAILABLE 
#   Removed Elinks: 
#     UsbRecoveryDebug_DIR and 
#     $(BUILD_DIR)\UsbRecoveryDebugDxe.ffs 
#   Modified SDL Token: 
#     FORCE_RECOVERY to default value of 0. 
# 
# (See this module's Help documentation 
# for more information.)
# 
# 7     7/29/08 5:50p Michaela
# 1) Updated code to move most porting tasks to SDL
# 2) Added more debug break points and improved interactive
#     debugging capability for when a serial port is not available.
# 3) Updated help files
# 
# 6     7/18/08 5:03p Michaela
# 1  File-level debugging is now available
# 2  AMI_USB_DEBUG_INTERFACE.WaitConsoleKey() now returns
#    the keypress so that conditional debugging can
#    be dynamic (alphanumeric keys only)
# 3  Added more function headers.
# 4  Removed code that will never be used (I.e., Bala?).
# 5  Moved typedef, contants and extern declarations
#    into header files.
# 6  Now all controller blocks are enabled for SB700
#    (EHCI controllers route to companion controller
#    by default)
# 7  Removed unused constants and typedefs n OhciPei.h
#    (also reorganized the file to make it more 
#    readable.)
# 8  Renamed many functions/variables according to
#    coding standard.
# 9  Removed code initializing data structures for
#    periodic lists, as this is not needed.
# 10 Removed the CONTROLLER_TYPE SDL token to
#    allow UHCI and OHCI controllers to supported
#    simultaneously. (modified MAKE files 
#    accordingly)
# 
# 5     7/10/08 6:33p Michaela
# Updated to support OHCI controllers
# 
# 4     8/17/07 4:29p Ambikas
# 
# 3     3/28/07 3:06a Meenakshim
# Removed dependency on core source files..Added amimapping file.
# 
# 2     9/22/06 4:07p Sivagarn
# - Initial Check-in
# - Included Recovery code in Source
# - Included appropriate headers for flies and functions
# - Updated copyright messages
# - Merged multiple MAK and SDL files into one MAK and SDL file
# - Removed unnecessary files
#
#**********************************************************************


#<AMI_FHDR_START>
#-----------------------------------------------------------------------
#
# Name:			UsbRecov.mak
#
# Description:	Contains make script to build USB Recovery related
#               PEIM.  This script file generates UhciPeiUsb, OhciPei,
#               UhcPeim, UsbPeim and UsbBotPeim
#
#-----------------------------------------------------------------------
#<AMI_FHDR_END>

# Define the target list based the RECOVERY_DEBUG_SUPPORT SDL token 
# which enables/disables generic USB console debugging routines.

USB_RECOVERY_TARGETS = \
    UsbBotPeimSrc 

all :  $(USB_RECOVERY_TARGETS)


#-----------------------------------------------------------------------
# Build script for UhciPeiUsb.lib
#-----------------------------------------------------------------------
UhciPeiUsb : $(BUILD_DIR)\UhcipeiUsb.mak UhcipeiUsbBin

#~~~~~~~~~~~~~~~~~~~~~~~ Generate UhcipeiUsb.mak

UHCI_PEI_USB_MAK_DEPS = \
    $(UhcipeiUsb_DIR)\UhcipeiUsb.cif \
    $(UsbRecovery_DIR)\UsbRecov.mak \
    $(BUILD_RULES)

UHCI_PEI_USB_CIF2MAK_ARGS = \
    $(UhcipeiUsb_DIR)\UhcipeiUsb.cif \
    $(CIF2MAK_DEFAULTS) \
    $(UsbRecovery_DIR)\UsbRecovery.cif

$(BUILD_DIR)\UhcipeiUsb.mak :  $(UHCI_PEI_USB_MAK_DEPS)
	$(CIF2MAK)  $(UHCI_PEI_USB_CIF2MAK_ARGS) 

#~~~~~~~~~~~~~~~~~~~~~~~ Generate UhciPeiUsb.lib

UHCI_PEI_USB_LIB_CFLAGS = $(CFLAGS) \
    /I $(UhcipeiUsb_DIR) \
    /I $(UsbRecovery_DIR) 

UHCI_PEI_USB_LIB_DEPS = \
    $(AMIPEILIB)
    
UhcipeiUsbBin : $(UHCI_PEI_USB_LIB_DEPS)
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\UhciPeiUsb.mak all\
		GUID=6895F6F0-8879-45B8-A9D9-9639E532319E\
        "CFLAGS=$(UHCI_PEI_USB_LIB_CFLAGS)"\
        TYPE=PEI_LIBRARY


#-----------------------------------------------------------------------
# Build script for UhcPeim.lib
#-----------------------------------------------------------------------
UhcPeim : $(BUILD_DIR)\UhcPeim.mak UhcPeimBin

#~~~~~~~~~~~~~~~~~~~~~~~ Generate UhcPeim.mak

UHC_PEIM_MAK_DEPS = \
    $(UhcPeimSrc_DIR)\UhcPeimSrc.cif \
    $(UsbRecovery_DIR)\UsbRecovery.cif \
    $(UsbRecovery_DIR)\UsbRecov.mak \
    $(BUILD_RULES)

UHC_PEIM_CIF2MAK_ARGS = \
    $(UhcPeimSrc_DIR)\UhcPeimSrc.cif \
    $(CIF2MAK_DEFAULTS) \
    $(UsbRecovery_DIR)\UsbRecovery.cif \

$(BUILD_DIR)\UhcPeim.mak :  $(UHC_PEIM_MAK_DEPS)
	$(CIF2MAK)  $(UHC_PEIM_CIF2MAK_ARGS) 

#~~~~~~~~~~~~~~~~~~~~~~~ Generate UhcPeim.lib

UHC_PEIM_LIB_CFLAGS=	$(CFLAGS) \
    /I $(UhcPeimSrc_DIR) \
    /I $(UsbRecovery_DIR) 

UHC_PEIM_LIB_DEPS = \
    $(AMIPEILIB) 

UhcPeimBin : $(UHC_PEIM_LIB_DEPS)
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\UhcPeim.mak all \
        NAME=UhcPeim\
        MAKEFILE=$(BUILD_DIR)\UhcPeim.mak \
		"CFLAGS=$(UHC_PEIM_LIB_CFLAGS)" \
		GUID=C463CEAC-FC57-4f36-88B7-356C750C3BCA \
        TYPE=PEI_LIBRARY


#-----------------------------------------------------------------------
# Build script for OhciPei.lib
#-----------------------------------------------------------------------
OhciPei : $(BUILD_DIR)\OhciPei.mak OhcipeiBin

#~~~~~~~~~~~~~~~~~~~~~~~ Generate OhciPei.mak

OHCI_PEI_MAK_DEPS = \
    $(OhciPei_DIR)\OhciPei.cif \
    $(UsbRecovery_DIR)\UsbRecovery.cif \
    $(UsbRecovery_DIR)\UsbRecov.mak \
    $(BUILD_RULES)

OHCI_PEI_CIF2MAK_ARGS = \
    $(OhciPei_DIR)\OhciPei.cif \
    $(CIF2MAK_DEFAULTS) \
    $(UsbRecovery_DIR)\UsbRecovery.cif

$(BUILD_DIR)\OhciPei.mak :  $(OHCI_PEI_MAK_DEPS)
	$(CIF2MAK)  $(OHCI_PEI_CIF2MAK_ARGS)

#~~~~~~~~~~~~~~~~~~~~~~~ Generate OhciPei.lib

OHCI_PEI_LIB_CFLAGS = \
    $(CFLAGS) \
    /I $(UsbRecovery_DIR) \
    /D\"USBR_OHCI_CONTROLLER_PCI_ADDRESS=$(USBR_OHCI_CONTROLLER_PCI_ADDRESS)\" \
    /D\"USBR_OHCI_CONTROLLER_PCI_REGISTER_VALUE=$(USBR_OHCI_CONTROLLER_PCI_REGISTER_VALUE)\" 

OHCI_PEI_LIB_DEPS = \
    $(AMIPEILIB)

OhciPeiBin : $(OHCI_PEI_LIB_DEPS)
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS) \
		/f $(BUILD_DIR)\OhciPei.mak all \
        NAME=OhciPei \
        MAKEFILE=$(BUILD_DIR)\OhciPei.mak \
		GUID=52DAA304-DEB3-449b-AFB8-A88A54F28F95 \
	    "CFLAGS=$(OHCI_PEI_LIB_CFLAGS)" \
        TYPE=PEI_LIBRARY


#-----------------------------------------------------------------------
# Build script for XhciPei.lib
#-----------------------------------------------------------------------
XhciPei : $(BUILD_DIR)\XhciPei.mak XhciPeiBin

#~~~~~~~~~~~~~~~~~~~~~~~ Generate XhciPei.mak

XHCI_PEI_MAK_DEPS = \
    $(XHCIPEI_DIR)\XhciPei.cif \
    $(UsbRecovery_DIR)\UsbRecovery.cif \
    $(UsbRecovery_DIR)\UsbRecov.mak \
    $(BUILD_RULES)

XHCI_PEI_CIF2MAK_ARGS = \
    $(XHCIPEI_DIR)\XhciPei.cif \
    $(CIF2MAK_DEFAULTS) \
    $(UsbRecovery_DIR)\UsbRecovery.cif

$(BUILD_DIR)\XhciPei.mak :  $(XHCI_PEI_MAK_DEPS)
	$(CIF2MAK)  $(XHCI_PEI_CIF2MAK_ARGS)

#~~~~~~~~~~~~~~~~~~~~~~~ Generate XhciPei.lib

XHCI_PEI_LIB_CFLAGS = \
    $(CFLAGS) \
    /I $(UsbRecovery_DIR) \

XHCI_PEI_LIB_DEPS = \
    $(AMIPEILIB)

XhciPeiBin : $(XHCI_PEI_LIB_DEPS)
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS) \
		/f $(BUILD_DIR)\XhciPei.mak all \
        NAME=XhciPei \
        MAKEFILE=$(BUILD_DIR)\XhciPei.mak \
		GUID=45D68DB9-8B4E-48c0-99E9-F21F262DB653 \
	    "CFLAGS=$(XHCI_PEI_LIB_CFLAGS)" \
        TYPE=PEI_LIBRARY

#// {45D68DB9-8B4E-48c0-99E9-F21F262DB653}
#0x45d68db9, 0x8b4e, 0x48c0, 0x99, 0xe9, 0xf2, 0x1f, 0x26, 0x2d, 0xb6, 0x53);

#-----------------------------------------------------------------------
# Build script for EhciPei.lib
#-----------------------------------------------------------------------
EhciPei : $(BUILD_DIR)\EhciPei.mak EhcipeiBin

#~~~~~~~~~~~~~~~~~~~~~~~ Generate EhciPei.mak

EHCI_PEI_MAK_DEPS = \
    $(EHCIPEI_DIR)\EhciPei.cif \
    $(UsbRecovery_DIR)\UsbRecovery.cif \
    $(UsbRecovery_DIR)\UsbRecov.mak \
    $(BUILD_RULES)

EHCI_PEI_CIF2MAK_ARGS = \
    $(EHCIPEI_DIR)\EhciPei.cif \
    $(CIF2MAK_DEFAULTS) \
    $(UsbRecovery_DIR)\UsbRecovery.cif

$(BUILD_DIR)\EhciPei.mak :  $(EHCI_PEI_MAK_DEPS)
	$(CIF2MAK)  $(EHCI_PEI_CIF2MAK_ARGS)

#~~~~~~~~~~~~~~~~~~~~~~~ Generate EhciPei.lib

EHCI_PEI_LIB_CFLAGS = \
    $(CFLAGS) \
    /I $(UsbRecovery_DIR)

EHCI_PEI_LIB_DEPS = \
    $(AMIPEILIB)

EhciPeiBin : $(EHCI_PEI_LIB_DEPS)
    $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS) \
        /f $(BUILD_DIR)\EhciPei.mak all \
        NAME=EhciPei \
        MAKEFILE=$(BUILD_DIR)\EhciPei.mak \
        GUID=D56A4094-570F-4D3D-8F5F-8D8AA0B396CB \
        "CFLAGS=$(EHCI_PEI_LIB_CFLAGS)" \
        TYPE=PEI_LIBRARY

#-----------------------------------------------------------------------
# Build script for UsbPeim.lib
#-----------------------------------------------------------------------
UsbPeimSrc : $(BUILD_DIR)\UsbPeimSrc.mak UsbPeimSrcBin

#~~~~~~~~~~~~~~~~~~~~~~~ Generate UsbPeimSrc.mak

USB_PEIM_MAK_DEPS = \
    $(UsbPeimSrc_DIR)\UsbPeimSrc.cif \
    $(UsbRecovery_DIR)\UsbRecovery.cif \
    $(UsbRecovery_DIR)\UsbRecov.mak \
    $(BUILD_RULES)

USB_PEIM_CIF2MAK_ARGS = \
    $(UsbPeimSrc_DIR)\UsbPeimSrc.cif \
    $(CIF2MAK_DEFAULTS) \
    $(UsbRecovery_DIR)\UsbRecovery.cif 

$(BUILD_DIR)\UsbPeimSrc.mak :  $(USB_PEIM_MAK_DEPS)
	$(CIF2MAK)  $(USB_PEIM_CIF2MAK_ARGS)

#~~~~~~~~~~~~~~~~~~~~~~~ Generate UsbPeim.lib

USB_PEIM_LIB_CFLAGS = \
    $(CFLAGS) \
    /I $(UsbRecovery_DIR)

USB_PEIM_LIB_DEPS = \
    $(AMIPEILIB)

UsbPeimSrcBin : $(USB_PEIM_LIB_DEPS)
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
	/f $(BUILD_DIR)\UsbPeimSrc.mak all \
    NAME=UsbPeim \
    MAKEFILE=$(BUILD_DIR)\UsbPeimSrc.mak \
	"CFLAGS=$(USB_PEIM_LIB_CFLAGS)" \
    TYPE=PEI_LIBRARY


#-----------------------------------------------------------------------
# Build script for UsbBotPeim.ffs
#-----------------------------------------------------------------------
UsbBotPeimSrc: $(BUILD_DIR)\UsbBotPeimSrc.mak UsbBotPeimSrcBin

#~~~~~~~~~~~~~~~~~~~~~~~ Generate UsbPeimSrc.mak using Cif2Mak.exe

USB_BOT_PEIM_MAK_DEPS = \
    $(UsbBotPeimSrc_DIR)\UsbBotPeim.cif \
    $(UsbRecovery_DIR)\UsbRecovery.cif \
    $(UsbRecovery_DIR)\UsbRecov.mak \
    $(BUILD_RULES)

USB_BOT_PEIM_CIF2MAK_ARGS = \
    $(UsbBotPeimSrc_DIR)\UsbBotPeim.cif \
    $(CIF2MAK_DEFAULTS) 

$(BUILD_DIR)\UsbBotPeimSrc.mak :  $(USB_BOT_PEIM_MAK_DEPS)
	$(CIF2MAK)  $(USB_BOT_PEIM_CIF2MAK_ARGS) 

#~~~~~~~~~~~~~~~~~~~~~~~ Generate UsbBotPeim.ffs

USB_BOT_PEIM_FFS_CFLAGS= \
    $(CFLAGS) \
    /I $(UsbBotPeimSrc_DIR) \
    /I $(UsbRecovery_DIR) \
    /I $(UhcPeimSrc_DIR) \
    /I $(UhcipeiUsb_DIR) \
    /I $(UsbPeimSrc_DIR) \
    /I $(OhciPei_DIR) \
    /I $(EHCIPEI_DIR) \
    /I $(XHCIPEI_DIR)

$(BUILD_DIR)\UhcPeim.lib : UhcPeim
$(BUILD_DIR)\UsbPeim.lib : UsbPeimSrc
$(BUILD_DIR)\UhcipeiUsb.lib : UhcipeiUsb
$(BUILD_DIR)\OhciPei.lib : OhciPei
$(BUILD_DIR)\EhciPei.lib : EhciPei
$(BUILD_DIR)\XhciPei.lib : XhciPei

USB_BOT_PEIM_FFS_DEPS = \
    $(AMIPEILIB) \
    $(BUILD_DIR)\UsbPeim.lib \
!if $(PEI_UHCI_SUPPORT)
    $(BUILD_DIR)\UhcPeim.lib \
    $(BUILD_DIR)\UhcipeiUsb.lib \
!endif
!if $(PEI_OHCI_SUPPORT)
    $(BUILD_DIR)\OhciPei.lib \
!endif
!if $(PEI_EHCI_SUPPORT)
    $(BUILD_DIR)\EhciPei.lib \
!endif
!if $(PEI_XHCI_SUPPORT)
    $(BUILD_DIR)\XhciPei.lib \
!endif

UsbBotPeimSrcBin : $(USB_BOT_PEIM_FFS_DEPS)
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS) \
		/f $(BUILD_DIR)\UsbBotPeimSrc.mak all \
		NAME=UsbBotPeim \
		MAKEFILE=$(BUILD_DIR)\UsbBotPeimSrc.mak \
		GUID=8401A046-6F70-4505-8471-7015B40355E3 \
		ENTRY_POINT=PeimInitializeUsbBot \
		"CFLAGS=$(USB_BOT_PEIM_FFS_CFLAGS)" \
		DEPEX1=$(UsbBotPeimSrc_DIR)\UsbBotPeim.dxs DEPEX1_TYPE=EFI_SECTION_PEI_DEPEX \
		TYPE=PEIM \
        	COMPRESS=1\
		"INIT_LIST=$(BeforeUsbRecovery)"



#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************

