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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/EDKRules.mak 1     1/20/12 3:45a Jeffch $
#
# $Revision: 1 $
#
# $Date: 1/20/12 3:45a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/EDKRules.mak $
# 
# 1     1/20/12 3:45a Jeffch
# Create Intel EDK 1117 Patch 7.
# 
# 1     1/20/12 3:24a Jeffch
# Create Intel EDK 1117 Patch 7. 
# 
# 1     9/27/11 6:06a Wesleychen
# Intel EDK initially releases.
# 
# 2     9/02/09 3:00a Iminglin
# EIP24919
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	EdkRules.mak
#
# Description:	EDK specific build rules.
#               This file is included by rules.mak
#
#<AMI_FHDR_END>
#**********************************************************************
EXTRA_CFLAGS=$(EXTRA_CFLAGS) /X
EXTRA_INCLUDES=$(EDK_INCLUDES) $(EXTRA_INCLUDES)
EXTRA_DEFINES=$(EXTRA_DEFINES) /DEFI_S3_RESUME /DTIANO_RELEASE_VERSION=$(TIANO_RELEASE_VERSION)
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