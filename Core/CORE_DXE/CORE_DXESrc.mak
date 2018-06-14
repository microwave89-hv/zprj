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
# $Header: /Alaska/SOURCE/Core/EDK/DxeMain/CORE_DXESrc.mak 20    10/20/11 7:00p Artems $
#
# $Revision: 20 $
#
# $Date: 10/20/11 7:00p $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Core/EDK/DxeMain/CORE_DXESrc.mak $
# 
# 20    10/20/11 7:00p Artems
# File BootOptions.h moved to Include folder - removed reference to its
# old place
# 
# 19    5/05/11 3:45p Artems
# Added EDKII compatibility library for EDKII code embedded into Core
# 
# 18    6/29/10 11:06p Felixp
# New Boot Options Maintenance Infrastructure.
# See AMI_Aptio_4.x_Boot_Options_Maintenance_Infrastructure_Porting_Guide
# _NDA.doc for details.
# 
# 17    11/13/09 3:56p Felixp
# MM_LEGACY_RESERVE_MEM constant in Page.c is converted to SDL token.
# 
# 16    10/09/09 6:06p Felixp
# UEFI 2.1 - related changes (suppot Framework and UEFI HII).
# 
# 15    3/05/09 1:08p Felixp
# Minor improvements:
#  - Unconditional optimization (despite debug flag settings) is removed
#  - Headers updated
# 
# 14    8/31/07 1:55p Felixp
# Updated to support new location of AMIPostMgr.h. It is moved from
# Core/em/AMITSE into Include/Protocol
# 
# 13    4/23/07 1:28p Felixp
# BootScriptSave removed from CORE_DXE(moved into AcpiS3Save driver)
# 
# 12    3/13/07 2:04a Felixp
# 
# 11    2/13/07 12:01p Felixp
# 
# 10    2/13/07 9:18a Felixp
# MRE Handshake protocol renamed to AMI POST Manager protocol
# (MreHandshake.h removed from Core Protocols and added to AMITSE module
# as AMIPostMgr.h)
# 
# 9     12/05/06 12:34p Felixp
# 
# 8     8/24/06 10:11a Felixp
# Preliminary x64 support (work in progress)
# 
# 7     5/20/06 12:38a Felixp
# 
# 6     5/19/06 10:46p Felixp
# Updated to EDK 03.16.06
# Cleanup
# 
# 5     4/14/06 2:21p Felixp
# 
# 4     4/03/06 3:52p Felixp
# Major changes in PCI and Super I/O:
# PCI - Root Bridge Resource Allocation Sepcification support
# Super I/O - multiple Super I/O support; SIO Setup page added;
# 
# 3     3/17/06 4:28p Felixp
# 
# 2     3/13/06 5:25p Felixp
# 
# 1     3/13/06 2:00a Felixp
# 
# 4     12/02/05 11:20a Felixp
# 
# 3     3/24/05 3:35p Felixp
# FloppyCtrl moved into a separate component
# 
# 2     2/01/05 1:16a Felixp
# Floppy and PS2 modules added to the CORE_DXE
# 
# 1     1/28/05 12:45p Felixp
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	CORE_DXESrc.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************
all : CORE_DXE_LIB

$(CORE_DXE_LIB) : CORE_DXE_LIB

CORE_DXE_LIB : $(BUILD_DIR)\CORE_DXESrc.mak CORE_DXE_LIBBin

CORE_DXE_CIFS=\
$(CORE_DXE_SRC_DIR)\$(@B).cif\
!IF "$(Partition_SUPPORT)"=="1"
$(PARTITION_DIR)\Partition.cif\
!ENDIF
!IF "$(ConSplitter_SUPPORT)"=="1"
$(CONSOLE_SPLITTER_DIR)\ConSplitter.cif\
!ENDIF
!IF "$(PS2Ctl_SUPPORT)"=="1"
$(PS2Ctl_DIR)\PS2Ctl.cif\
!ENDIF
!IF $(EFI_SPECIFICATION_VERSION)>0x20000
$(UefiHii_DIR)\UefiHii.cif\
!ELSE
$(FrameworkHii_DIR)\FrameworkHii.cif\
!ENDIF

$(BUILD_DIR)\CORE_DXESrc.mak : $(CORE_DXE_SRC_DIR)\$(@B).mak $(BUILD_RULES) $(CORE_DXE_CIFS)
	$(CIF2MAK) $(CIF2MAK_DEFAULTS) $(CORE_DXE_CIFS)

CORE_DXE_LIBBin : $(BUILD_DIR)\Foundation.lib $(EDK_II_LIB)
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\CORE_DXESrc.mak all\
		TYPE=LIBRARY LIBRARY_NAME=$(CORE_DXE_LIB)\
		"EXT_HEADERS=$(BUILD_DIR)\token.h  $(FoundationCpu_DIR)\Processor.h"\
		"MY_INCLUDES=/I$(CORE_PEI_DIR) /I$(Foundation_DIR) /I$(FoundationCpu_DIR)"\
        "MY_DEFINES=/DMM_LEGACY_RESERVE_MEM=$(MM_LEGACY_RESERVE_MEM)"\
		NAME=CORE_DXESrc

#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2007, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************
