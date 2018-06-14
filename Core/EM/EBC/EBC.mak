#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
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
# $Header: /Alaska/BIN/Core/Modules/Ebc/EBC.mak 1     5/13/11 5:03p Artems $
#
# $Revision: 1 $
#
# $Date: 5/13/11 5:03p $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Core/Modules/Ebc/EBC.mak $
# 
# 1     5/13/11 5:03p Artems
# 
# 6     1/13/10 2:13p Felixp
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	EBC.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************
all : EBC

EBC : $(BUILD_DIR)\EBC.mak EBCBin

$(BUILD_DIR)\EBC.mak : $(EBC_DIR)\$(@B).cif $(EBC_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(EBC_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

EBCBin :
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\EBC.mak all\
		GUID=13AC6DD0-73D0-11D4-B06B-00AA00BD6DE7\
!IF "$(x64_BUILD)"=="1"
        EFI_FILE=$(EBC_DIR)\EBCx64.efi\
!ELSE
        EFI_FILE=$(EBC_DIR)\EBC.efi\
!ENDIF
		TYPE=BS_DRIVER \
		COMPRESS=1\
#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************