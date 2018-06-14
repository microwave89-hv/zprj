#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2006, American Megatrends, Inc.         **
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
# $Header: /Alaska/BIN/Core/Modules/x64Core/x64rules.mak 3     8/02/07 1:33a Felixp $
#
# $Revision: 3 $
#
# $Date: 8/02/07 1:33a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Core/Modules/x64Core/x64rules.mak $
# 
# 3     8/02/07 1:33a Felixp
# minor modification to use newly defined COMPONENT_BUILD_RULES macro
# defined in rules.mak
# 
# 2     3/13/07 11:53a Felixp
# Global and CPU architecture specific macros are now passed 
# to C preprocessor (used during DepEx and VFR compilation)
# 
# 1     10/13/06 8:31p Felixp
# 
# 3     9/05/06 6:03p Felixp
# define PROCESSOR is IA32 when building PEI components in x64 build.
# 
# 2     8/25/06 11:12a Felixp
# 
# 1     8/24/06 12:57p Felixp
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	x64rules.mak
#
# Description: Defines x64-specific build rules. 
# This file is included into the template makefile rules.mak
#
#<AMI_FHDR_END>
#**********************************************************************
!IF "$(COMPONENT_BUILD_RULES)"=="PEI"
# IA32 Build
CC = $(CCPEI)
LINK = $(LINKPEI)
LIBEXE=$(LIBEXEPEI)

LIB_BUILD_DIR=$(BUILD_ROOT)\IA32
!UNDEF PROCESSOR
PROCESSOR=IA32
!INCLUDE $(IA32Core_DIR)\IA32rules.mak

!ELSE 
# x64 Build
ASM=$(ASMx64)

EXTRA_CFLAGS=$(EXTRA_CFLAGS) $(CFLAGSx64)
EXTRA_LFLAGS=$(EXTRA_LFLAGS) $(LFLAGSx64)
EXTRA_AFLAGS=$(EXTRA_AFLAGS) $(AFLAGSx64)
EXTRA_AFLAGS16=$(EXTRA_AFLAGS16) $(GLOBAL_DEFINES_x64)
CPFLAGS=$(CPFLAGS) $(GLOBAL_DEFINES_x64)
!ENDIF
#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2006, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************