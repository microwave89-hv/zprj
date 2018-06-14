#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
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
# $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Refcode/PeiSmmControl/PeiSmmControl.mak 1     9/26/12 3:34a Victortu $
#
# $Revision: 1 $
#
# $Date: 9/26/12 3:34a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Refcode/PeiSmmControl/PeiSmmControl.mak $
# 
# 1     9/26/12 3:34a Victortu
# Lynx Point PCH Chipset Framework Reference Code Beta 0.7.0
# 
# 6     1/13/10 2:13p Felixp
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	PeiSmmControl.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************
EDK : PeiSmmControl

PeiSmmControl : $(BUILD_DIR)\PeiSmmControl.mak PeiSmmControlBin

$(BUILD_DIR)\PeiSmmControl.mak : $(PeiSmmControl_DIR)\$(@B).cif $(PeiSmmControl_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(PeiSmmControl_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

PeiSmmControl_INCLUDES=\
            $(EDK_INCLUDES)\
            $(EdkIIGlueLib_INCLUDES)\
            $(INTEL_PCH_INCLUDES)\
            
PeiSmmControl_DEFINES = $(MY_DEFINES)\
            /D"__EDKII_GLUE_MODULE_ENTRY_POINT__=SmmControlPeiDriverEntryInit"\
            /D __EDKII_GLUE_BASE_IO_LIB_INTRINSIC__ \
            /D __EDKII_GLUE_BASE_MEMORY_LIB__ \
            /D __EDKII_GLUE_PEI_REPORT_STATUS_CODE_LIB__ \
            /D __EDKII_GLUE_PEI_DEBUG_LIB_REPORT_STATUS_CODE__ \
            /D __EDKII_GLUE_PEI_SERVICES_LIB__ \
            /D __EDKII_GLUE_BASE_PCI_LIB_PCI_EXPRESS__

PeiSmmControl_LIB_LINKS =\
            $(EdkIIGlueBaseIoLibIntrinsic_LIB)\
            $(EdkIIGlueBaseMemoryLib_LIB)\
            $(EdkIIGluePeiDebugLibReportStatusCode_LIB)\
            $(EdkIIGluePeiReportStatusCodeLib_LIB)\
            $(EdkIIGluePeiServicesLib_LIB)\
            $(EdkIIGlueBasePciLibPciExpress_LIB)\

PeiSmmControlBin : $(PeiSmmControl_LIB_LINKS)
            $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
            /f $(BUILD_DIR)\PeiSmmControl.mak all\
            "MY_INCLUDES=$(PeiSmmControl_INCLUDES)" \
            "MY_DEFINES=$(PeiSmmControl_DEFINES)" \
            GUID=FF456B9C-0DC7-4682-9E92-0DE84B6E4067\
            ENTRY_POINT=_ModuleEntryPoint \
            TYPE=PEIM \
            EDKIIModule=PEIM\
            DEPEX1=$(PeiSmmControl_DIR)\SmmControl.dxs\
            DEPEX1_TYPE=EFI_SECTION_PEI_DEPEX\
            COMPRESS=0
#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************