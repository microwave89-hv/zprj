# MAK file for the ModulePart:PciSerial

all : PciSerial

$(BUILD_DIR)\PciSerial.mak : $(PciSerial_DIR)\$(@B).cif $(PciSerial_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(PciSerial_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

PciSerial : $(BUILD_DIR)\PciSerial.mak PciSerialBin

PciSerial_INCLUDES=\
  $(EdkIIGlueLib_INCLUDES)\
  $(ME_INCLUDES)\
  $(INTEL_PCH_INCLUDES)

PciSerial_LIBS=\
  $(EDKPROTOCOLLIB)\
  $(AmtLibDxe_LIB)\
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
  $(EdkIIGlueUefiDevicePathLib_LIB)\
  $(EdkIIGlueUefiLib_LIB)\
  $(EdkIIGlueUefiDriverModelLib_LIB)\

PciSerial_DEFINES=\
  $(MY_DEFINES)\
  /D"__EDKII_GLUE_MODULE_ENTRY_POINT__=PciSerialControllerDriverEntryPoint"\
  /D"__EDKII_GLUE_DRIVER_BINDING_PROTOCOL_INSTANCE__=mPciSerialControllerDriverBinding"\
  /D"__EDKII_GLUE_COMPONENT_NAME_PROTOCOL_INSTANCE__=mPciSerialComponentName"\
  /D __EDKII_GLUE_BASE_LIB__\
  /D __EDKII_GLUE_BASE_MEMORY_LIB__\
  /D __EDKII_GLUE_DXE_REPORT_STATUS_CODE_LIB__ \
  /D __EDKII_GLUE_DXE_DEBUG_LIB_REPORT_STATUS_CODE__ \
  /D __EDKII_GLUE_UEFI_BOOT_SERVICES_TABLE_LIB__\
  /D __EDKII_GLUE_UEFI_DEVICE_PATH_LIB__\
  /D __EDKII_GLUE_UEFI_LIB__  \
  /D __EDKII_GLUE_UEFI_DRIVER_MODEL_LIB__

PciSerialBin : $(PciSerial_LIBS)
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		/f $(BUILD_DIR)\PciSerial.mak all \
		"MY_INCLUDES=$(PciSerial_INCLUDES)"\
		"MY_DEFINES=$(PciSerial_DEFINES)"\
		GUID=FB142B99-DF57-46cb-BC69-0BF858A734F9 \
        ENTRY_POINT=_ModuleEntryPoint \
        TYPE=BS_DRIVER \
        EDKIIModule=DXEDRIVER\
		COMPRESS=1
