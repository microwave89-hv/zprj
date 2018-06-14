all : PttHeciDxeLib

$(BUILD_DIR)\PttHeciDxeLib.lib : PttHeciDxeLib

PttHeciDxeLib : $(BUILD_DIR)\PttHeciDxeLib.mak PttHeciDxeLibBin

$(BUILD_DIR)\PttHeciDxeLib.mak : $(PttHeciDxeLib_DIR)\$(@B).cif $(PttHeciDxeLib_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(PttHeciDxeLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

PttHeciDxeLib_INCLUDES=\
  $(EDK_INCLUDES) \
  $(EdkIIGlueLib_INCLUDES) \
  $(ME_INCLUDES) \
  -I$(INTEL_COUGAR_POINT_DIR)\
  $(INTEL_PCH_INCLUDES)

PttHeciDxeLib_DEFINES=$(MY_DEFINES)\
  /D __EDKII_GLUE_BASE_LIB__ \
  /D __EDKII_GLUE_UEFI_LIB__ \
  /D __EDKII_GLUE_DXE_DEBUG_LIB_REPORT_STATUS_CODE__ \
  /D PTT_FLAG

PttHeciDxeLib_LIBS=\
      $(EdkIIGlueBaseLib_LIB)\
!IF "$(x64_BUILD)"=="1"
      $(EdkIIGlueBaseLibX64_LIB)\
!ELSE
      $(EdkIIGlueBaseLibIA32_LIB)\
!ENDIF
      $(EdkIIGlueUefiLib_LIB)\
      $(EdkIIGlueDxeDebugLibReportStatusCode_LIB)\
      $(MeProtocolLib_LIB)\
  

PttHeciDxeLibBin : $(PttHeciDxeLib_LIBS)
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS) \
		/f $(BUILD_DIR)\PttHeciDxeLib.mak all \
		"MY_INCLUDES=$(PttHeciDxeLib_INCLUDES)" \
		"MY_DEFINES=$(PttHeciDxeLib_DEFINES)"\
		TYPE=LIBRARY \
