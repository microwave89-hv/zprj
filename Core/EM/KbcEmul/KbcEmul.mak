#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**             5555 Oakbrook Pkwy, Norcross, GA 30093               **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************
# $Header: /Alaska/SOURCE/Modules/KbcEmulation/ALASKA/KBCEMUL/KbcEmul.mak 10    12/04/14 12:50a Rajeshms $
#
# $Revision: 10 $
#
# $Date: 12/04/14 12:50a $
#
#****************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/KbcEmulation/ALASKA/KBCEMUL/KbcEmul.mak $
# 
# 10    12/04/14 12:50a Rajeshms
# [TAG]  		EIP193601
# [Category]  	New Feature
# [Description]  	Aptio4.x - Security Enhancement for SMIHandler in
# KbcEmulation module, Checks if BAR address access is inside SMRAM, if
# yes, return.
# [Files]  		KbcEmul.mak, KbcEmul.c, KbcOhci.c
# 
# 9     9/16/13 6:53a Srikantakumarp
# [TAG]  		EIP136515 
# [Category]  	Bug Fix
# [Severity]  	Normal
# [Symptom]  	Build error in AMD platform when enabling Emul6064_Support
# [RootCause]  	OHCI_EMUL_LIB was not inluded while making KbcEmulBin
# [Solution]  	Added OHCI_EMUL_LIB while making KbcEmulBin
# [Files]  		KbcEmul.mak
# 
# 8     5/13/13 2:48a Rameshr
# [TAG]  		EIP119870
# [Category]  	Improvement
# [Description]  	Build error with KbcEmulation module if update USB
# module label 4.6.3_USB_08.10.26
# [Files]  		KbcEmul.Mak, KbcEmul.SDl, KbcUhci.c, KbcUhci.h, KbcOhci.c
# 
# 7     2/10/11 12:55a Rameshr
# [TAG]  		EIP53687
# [Category]  	Improvement
# [Description]  	AMI headers update for KbcEmulation Module 
# [Files]  		KbcEmul.mak,KbcEmul.dxs,KbcEmul.c,KbcEmul.h,KbcEmulLib.h,Kbc
# EmulLib.c,Kbc.h,KbcDevEmul.h,Kbccore.c,Legacykbc.c,Legacykbd.c,LegacyMo
# use.c,VirtualKbc.c,VirtualKbd.c,VirtualMouse.c,Ap4x.h,Ap4x.c,KbcUhci.c,
# KbcUhci.h,KbcEmulIrq.c, KbcOhci.c, Kbcohci.h
# 
# 6     7/08/10 1:59a Rameshr
# Ohci Emulation support Added.
# EIP 39712
# 
# 5     8/19/09 2:25p Rameshr
# Sb module component created to support SB porting for Emulation module.
# EIP:25184
# 
# 4     6/30/09 11:27a Rameshr
# Coding Standard and File header updated.
# 
# 3     6/01/09 10:01a Rameshr
# Added Emulation Support for RMH enable/Disable
# EIP 21131
# 
# 2     12/27/07 6:45p Rameshraju
# 
# 1     12/14/07 10:26a Rameshraju
# Initial Check-in
#****************************************************************************

#**********************************************************************
#<AMI_FHDR_START>
#
# Name:        KbcEmul.mak
#
# Description: Mak file the KBC Emulation
#
#<AMI_FHDR_END>
#**********************************************************************
!if $(UHCI_EMUL_SUPPORT)
UHCI_EMUL = KbcUhci
UHCI_EMUL_LIB= $(BUILD_DIR)\KbcUhciEmulBin.lib
!else
UHCI_EMUL =
UHCI_EMUL_LIB=
!endif

!if $(OHCI_EMUL_SUPPORT)
OHCI_EMUL = KbcOhci
OHCI_EMUL_LIB= $(BUILD_DIR)\KbcOhciEmulBin.lib $(BUILD_DIR)\AmiBufferValidationLib.lib
!else
OHCI_EMUL =
OHCI_EMUL_LIB=
!endif
!if $(IRQ_EMUL_SUPPORT)
IRQ_EMUL = KbcEmulIrq
IRQ_EMUL_LIB = $(BUILD_DIR)\KbcEmulIrq.lib
!else
IRQ_EMUL =
IRQ_EMUL_LIB = 
!endif

all: $(IRQ_EMUL) $(UHCI_EMUL) $(OHCI_EMUL) KbcEmul

#-----------------------------------------------------------------------
# Build script for IRQ Based Eumlation
#-----------------------------------------------------------------------
KbcEmulIrq : $(BUILD_DIR)\KbcEmulIrq.mak $(BUILD_DIR)\KbcEmulIrq.lib

$(BUILD_DIR)\KbcEmulIrq.mak : $(KBCEMUL_DIR)\KbcEmulIrq.cif  $(KBCEMUL_DIR)\KbcEmul.mak $(BUILD_RULES)
                              $(CIF2MAK) $(KBCEMUL_DIR)\KbcEmulIrq.cif $(CIF2MAK_DEFAULTS)

$(BUILD_DIR)\KbcEmulIrq.lib : $(AMIDXELIB)
                    $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
                    "CFLAGS=$(CFLAGS) /I$(KBCEMUL_DIR) /DFRAMEWORK_AP4"\
                    /f $(BUILD_DIR)\KbcEmulIrq.mak all\
                    TYPE=LIBRARY LIBRARY_NAME=$(BUILD_DIR)\KbcEmulIrq.lib

#-----------------------------------------------------------------------
# Build script for Uhci Based Eumlation
#-----------------------------------------------------------------------
KbcUhci : $(BUILD_DIR)\KbcUhci.mak $(BUILD_DIR)\KbcUhciEmulBin.lib

$(BUILD_DIR)\KbcUhci.mak : $(KBCEMUL_DIR)\KbcUhci.cif  $(KBCEMUL_DIR)\KbcEmul.mak $(BUILD_RULES)
                           $(CIF2MAK) $(KBCEMUL_DIR)\KbcUhci.cif $(CIF2MAK_DEFAULTS)

$(BUILD_DIR)\KbcUhciEmulBin.lib : $(AMIDXELIB)
                    $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
                    "CFLAGS=$(CFLAGS) /I$(KBCEMUL_DIR) /DFRAMEWORK_AP4"\
                    /f $(BUILD_DIR)\KbcUhci.mak all\
                    TYPE=LIBRARY LIBRARY_NAME=$(BUILD_DIR)\KbcUhciEmulBin.lib

#-----------------------------------------------------------------------
# Build script for Ohci Based Eumlation
#-----------------------------------------------------------------------
KbcOhci : $(BUILD_DIR)\KbcOhci.mak $(BUILD_DIR)\KbcOhciEmulBin.lib

$(BUILD_DIR)\KbcOhci.mak : $(KBCEMUL_DIR)\KbcOhci.cif  $(KBCEMUL_DIR)\KbcEmul.mak $(BUILD_RULES)
                           $(CIF2MAK) $(KBCEMUL_DIR)\KbcOhci.cif $(CIF2MAK_DEFAULTS)

$(BUILD_DIR)\KbcOhciEmulBin.lib : $(AMIDXELIB)
                    $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
                    "CFLAGS=$(CFLAGS) /I$(KBCEMUL_DIR) /DFRAMEWORK_AP4"\
                    /f $(BUILD_DIR)\KbcOhci.mak all\
                    TYPE=LIBRARY LIBRARY_NAME=$(BUILD_DIR)\KbcOhciEmulBin.lib


#-----------------------------------------------------------------------
# Build script for KBC Emulation
#-----------------------------------------------------------------------
KbcEmul : $(BUILD_DIR)\KbcEmul.mak  KbcEmulBin

$(BUILD_DIR)\KbcEmul.mak : $(KBCEMUL_DIR)\$(@B).cif $(KBCEMUL_DIR)\$(@B).mak $(BUILD_RULES)
                           $(CIF2MAK) $(KBCEMUL_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

$(BUILD_DIR)\KbcEmul.lib : $(BUILD_DIR)\debug.obj $(BUILD_DIR)\guids.obj
                $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
                /f $(BUILD_DIR)\KbcEmul.mak all\
                "CFLAGS=$(CFLAGS) /I$(KBCEMUL_DIR) /DFRAMEWORK_AP4"\
                TYPE=LIBRARY LIBRARY_NAME=$(BUILD_DIR)\KbcEmul.lib

KbcEmulBin : $(AMIDXELIB) $(UHCI_EMUL_LIB) $(OHCI_EMUL_LIB) $(IRQ_EMUL_LIB) $(BUILD_DIR)\KbcEmul.lib
                @set INCLUDE=%%INCLUDE%%
                $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
                /f $(BUILD_DIR)\KbcEmul.mak all\
                GUID=3b24f79d-91a0-46ff-be29-458ae211fac5 \
                ENTRY_POINT=EmulationEntryPoint \
                "CFLAGS=$(CFLAGS) /I$(KBCEMUL_DIR) /DFRAMEWORK_AP4"\
                DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX \
                "EXT_HEADERS=$(EXT_HEADERS)"\
                TYPE=BS_DRIVER \
                COMPRESS=1\
                DEPEX1=$(KBCEMUL_DIR)\KbcEmul.dxs \

IMAGE_ENTRY_POINT = EmulationEntryPoint

#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**             5555 Oakbrook Pkwy, Norcross, GA 30093               **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************
