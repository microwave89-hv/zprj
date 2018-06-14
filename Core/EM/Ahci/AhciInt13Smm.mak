#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************
#**********************************************************************
# $Header: /Alaska/SOURCE/Modules/AHCI/INT13/AhciInt13Smm.mak 2     12/08/14 5:39a Anbuprakashp $Revision:
#
# $Date: 12/08/14 5:39a $Log: /Alaska/SOURCE/Modules/AHCI/INT13/AhciInt13Smm.mak $
# 
# 
#
#****************************************************************************

#<AMI_FHDR_START>
#****************************************************************************
#
# Name:    AhciInt13Smm.mak
#
# Description: 
#    MAK file for the AhciInt13Smm component
#****************************************************************************
#<AMI_FHDR_END>

all : AhciInt13Smm
AhciInt13Smm : $(BUILD_DIR)\AhciInt13Smm.mak AhciInt13SmmBin

$(BUILD_DIR)\AhciInt13Smm.mak : $(AHCI_INT13_SMM_DIR)\AhciInt13Smm.cif $(AHCI_INT13_SMM_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(AHCI_INT13_SMM_DIR)\AhciInt13Smm.cif $(CIF2MAK_DEFAULTS)

AHCI_INT13_SMM_INCLUDES = $(AMIDXELIB) \
                          $(BUILD_DIR)\AmiBufferValidationLib.lib

AhciInt13SmmBin : $(AHCI_INT13_SMM_INCLUDES)
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
        /f $(BUILD_DIR)\AhciInt13Smm.mak all\
        GUID=501f30e9-d14f-47da-ae60-b101e4189d07\
        ENTRY_POINT=AhciInt13SmmEntryPoint\
!IF $(PI_SPECIFICATION_VERSION) >= 0x1000A && $(CORE_COMBINED_VERSION) >= 0x4028B
        TYPE=DXESMM_DRIVER PE_TYPE=RT_DRIVER\
        DEPEX1=$(AHCI_INT13_SMM_DIR)\AhciInt13Smm.dxs \
        DEPEX1_TYPE=EFI_SECTION_SMM_DEPEX \
        DEPEX2=$(AHCI_INT13_SMM_DIR)\AhciInt13Dxe.dxs \
        DEPEX2_TYPE=EFI_SECTION_DXE_DEPEX \
!ELSE
        TYPE=BS_DRIVER\
        DEPEX1=$(AHCI_INT13_SMM_DIR)\AhciInt13Smm.dxs \
        DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX \
!ENDIF
        COMPRESS=1

#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************