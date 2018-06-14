# MAK file for the ModulePart:IdeRController
all : IdeRController

$(BUILD_DIR)\IdeRController.mak : $(IdeRController_DIR)\$(@B).cif $(IdeRController_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(IdeRController_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

IdeRController : $(BUILD_DIR)\IdeRController.mak IdeRControllerBin

IdeRController_INCLUDES=\
                $(ME_INCLUDES)\
		$(EdkIIGlueLib_INCLUDES)\
		$(EDK_INCLUDES)\
  $(INTEL_PCH_INCLUDES)

IdeRController_DEFINES=\
  $(MY_DEFINES)\
  /D"__EDKII_GLUE_MODULE_ENTRY_POINT__=InitializeIdeRControllerDriver"\
  /D"__EDKII_GLUE_DRIVER_BINDING_PROTOCOL_INSTANCE__=mIdeRControllerDriverBinding"\
  /D"__EDKII_GLUE_COMPONENT_NAME_PROTOCOL_INSTANCE__=mIdeRControllerName"\
  /D __EDKII_GLUE_BASE_MEMORY_LIB__ \
  /D __EDKII_GLUE_DXE_REPORT_STATUS_CODE_LIB__ \
  /D __EDKII_GLUE_DXE_DEBUG_LIB_REPORT_STATUS_CODE__ \
  /D __EDKII_GLUE_UEFI_BOOT_SERVICES_TABLE_LIB__ \
  /D __EDKII_GLUE_UEFI_LIB__ \
  /D __EDKII_GLUE_UEFI_DRIVER_MODEL_LIB__
  
IdeRController_LIBS=\
  $(EDKPROTOCOLLIB)\
  $(AmtGuidLib_LIB)\
  $(AmtLibDxe_LIB)\
  $(EDKFRAMEWORKPROTOCOLLIB)\
  $(EdkIIGlueBaseLib_LIB)\
!IF "$(x64_BUILD)"=="1"
  $(EdkIIGlueBaseLibX64_LIB)\
!ELSE
  $(EdkIIGlueBaseLibIA32_LIB)\
!ENDIF  
  $(EdkIIGlueBaseMemoryLib_LIB)\
  $(EdkIIGlueDxeReportStatusCodeLib_LIB)\
  $(EdkIIGlueDxeDebugLibReportStatusCode_LIB)\
  $(EdkIIGlueUefiBootServicesTableLib_LIB)\
  $(EdkIIGlueUefiLib_LIB)\
  $(EdkIIGlueUefiDriverModelLib_LIB)\


IdeRControllerBin : $(IdeRController_LIBS)
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		/f $(BUILD_DIR)\IdeRController.mak all \
		"MY_INCLUDES=$(IdeRController_INCLUDES)"\
		"MY_DEFINES=$(IdeRController_DEFINES)"\
		GUID=C4F2D007-37FD-422d-B63D-7ED73886E6CA \
        ENTRY_POINT=_ModuleEntryPoint \
        TYPE=BS_DRIVER \
        EDKIIModule=DXEDRIVER\
		COMPRESS=1
