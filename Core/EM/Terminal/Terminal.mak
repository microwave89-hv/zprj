#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**             5555 Oakbrook Pkwy, Norcross, GA 30093               **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************
# $Header: /Alaska/BIN/Modules/Terminal/Terminal.mak 12    12/22/11 1:32a Rajeshms $
#
# $Revision: 12 $
#
# $Date: 12/22/11 1:32a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Modules/Terminal/Terminal.mak $
# 
# 12    12/22/11 1:32a Rajeshms
# [TAG]  		EIP57579
# [Category]  	Improvement
# [Description]  	PCI legacy console redirection causes Legacy OS
# installation slow because when Redirection is enabled for Legacy OS,
# Legacy Serial Redirection enables the PCI Serial interrupt for
# redirection and sometime after that OS uses its own IVT but still PCI
# Serial interrupt is generated and not handled.So, disable redirection
# at OS level. we disable redirection on ACPI enable/disable call and
# reset the Interrupt Enable Register so that interrupt is not generated.
# [Files]  		Terminal.sdl, Terminal.mak, Terminal.cif, TerminalAcpi.c
# 
# 11    2/12/10 5:06p Felixp
# Clean up (unneeded target removed)
# 
# 10    7/02/09 5:00p Rameshr
# Coding Standard and File header updated.
# 
# 9     4/14/08 6:52p Ambikas
# 
# 8     11/29/07 11:58a Ambikas
# Fixed bug.  If Terminal_SUPPORT was set to 0, InitTerminalStrings.c 
# would still be compiled and incorporated into SetupBin, 
# which would result in an assert while booting.  
# Made the compiling of InitTerminalStrings.obj and the generation of 
# Terminal.sdb dependent on the value of Terminal_SUPPORT.
# 
# 7     11/07/07 4:53p Ambikas
# Terminal.sd is dependent on token.h.  
# 
# 6     6/05/07 4:14p Ambikas
# 
# 5     5/24/07 2:30p Ambikas
# Added rule for InitTerminalStrings.c.
# 
# 4     12/02/05 11:50a Felixp
# 
# 3     11/11/05 2:07p Ambikas
# 
# 2     2/11/05 5:49p Felixp
# Binary files organization improved:
#   - extra layer of sub-component removed
#   - macros initialization moved to SDL tokens to eliminate undefined
# macros situation
#   - debug and release binaries have different names now (workaround for
# VeB limitation)
#   - binaries reside in the component home directory (eliminates
# hardcoded paths)
# 
# 1     1/28/05 12:47p Felixp
# 
# 2     1/18/05 3:22p Felixp
# PrintDebugMessage renamed to Trace
# 
# 1     12/22/04 6:19p Admin
# 
# 1     12/22/04 6:18p Admin
# 
# 1     11/07/04 3:20p Markw
# Adding unfinished code to source control. Partially works.  Currently
# turned off.
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	Terminal_mak
#
# Description:	Creates Terminal.efi.  
#		Includes either Terminal.lib or Terminalx64.lib depending 
#		on the cpu mode. 
#
#		These two files are not part of Terminal.efi:
#		The Terminal.sd file is compiled as part of the target SetupSdbs 
#		in Setup.mak.
#		InitTerminalStrings.c is compiled as part of the target SetupBin 
#		in Setup.mak.				
#
#<AMI_FHDR_END>
#**********************************************************************
all : TERMINAL

TERMINAL : $(BUILD_DIR)\Terminal.mak TERMINALBIN

$(BUILD_DIR)\Terminal.mak : $(TERMINAL_DIR)\$(@B).cif \
                            $(TERMINAL_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(TERMINAL_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

TERMINALBIN : $(AMIDXELIB) $(Terminal_LIB) 
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\Terminal.mak all\
		OBJECTS=$(BUILD_DIR)\$(TERMINAL_DIR)\TerminalSetup.obj\
		GUID=7A08CB98-E9BC-41c3-BE19-B302F3F1F595\
		ENTRY_POINT=TerminalEntryPoint \
		"EXT_HEADERS=$(BUILD_DIR)\token.h"\
		TYPE=BS_DRIVER LIBRARIES= \
		COMPRESS=1\
		"INIT_LIST=$(TerminalInitialize)"

#***********************************************************************

!IF "$(Terminal_SUPPORT)"=="1"
SetupSdbs : TerminalSDB
!ENDIF

TerminalSDB : $(BUILD_DIR)\Terminal.mak 
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
	/f $(BUILD_DIR)\Terminal.mak all\
	TYPE=SDB NAME=Terminal STRING_CONSUMERS=$(TERMINAL_DIR)\Terminal.sd

!IF "$(Terminal_SUPPORT)"=="1"
SetupBin : $(BUILD_DIR)\InitTerminalStrings.obj
!ENDIF

$(BUILD_DIR)\InitTerminalStrings.obj : \
                                    $(TERMINAL_DIR)\InitTerminalStrings.c \
                                    $(BUILD_DIR)\SetupStrTokens.h
	$(CC) $(CFLAGS) /Fo$(BUILD_DIR)\ $(TERMINAL_DIR)\InitTerminalStrings.c

#***********************************************************************

!IF "$(DISABLE_PCI_REDIRECTION_ON_ACPI_ENABLE_DISABLE)"=="1"

$(BUILD_DIR)\TerminalAcpi.obj: $(TERMINAL_DIR)\TerminalAcpi.c
    $(CC) $(CFLAGS) /Fo$(BUILD_DIR)\ $(TERMINAL_DIR)\TerminalAcpi.c /I$(TERMINAL_DIR)

AcpiModeEnableBin: $(BUILD_DIR)\TerminalAcpi.obj
!ENDIF

#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**             5555 Oakbrook Pkwy, Norcross, GA 30093               **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************

