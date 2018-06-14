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
# $Header: /Alaska/BIN/Core/Modules/IA32Core/IA32rules.mak 2     12/28/06 6:22p Felixp $
#
# $Revision: 2 $
#
# $Date: 12/28/06 6:22p $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Core/Modules/IA32Core/IA32rules.mak $
# 
# 2     12/28/06 6:22p Felixp
# VC8 32-bit compiler support added
# 
# 1     10/13/06 8:30p Felixp
# 
# 1     8/24/06 12:54p Felixp
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	IA32rules.mak
#
# Description: Defines IA32-specific build rules. 
# This file is included into the template makefile rules.mak
#
#<AMI_FHDR_END>
#**********************************************************************
!IF "$(TOOLS)"=="vc8"
EXTRA_CFLAGS=$(EXTRA_CFLAGS) /GS-
!ENDIF

EXTRA_CFLAGS=$(EXTRA_CFLAGS) $(CFLAGSIA32)
EXTRA_LFLAGS=$(EXTRA_LFLAGS) $(LFLAGSIA32)
EXTRA_AFLAGS=$(EXTRA_AFLAGS) $(AFLAGSIA32)
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