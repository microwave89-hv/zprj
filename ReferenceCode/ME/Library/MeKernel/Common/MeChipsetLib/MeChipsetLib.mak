# MAK file for the ModulePart:MeChipsetLib
EDK : MeChipsetLib

MeChipsetLib : MeChipsetSmmLib MeChipsetDxeLib MeChipsetPeiLib

$(MeChipsetSmmLib_LIB) : MeChipsetSmmLib
$(MeChipsetDxeLib_LIB) : MeChipsetDxeLib
$(MeChipsetPeiLib_LIB) : MeChipsetPeiLib

MeChipsetSmmLib : $(BUILD_DIR)\MeChipsetLib.mak MeChipsetLibSmmBin

MeChipsetDxeLib : $(BUILD_DIR)\MeChipsetLib.mak MeChipsetLibDxeBin

MeChipsetPeiLib : $(BUILD_DIR)\MeChipsetLib.mak MeChipsetLibPeiBin

$(BUILD_DIR)\MeChipsetLib.mak : $(MeChipsetLib_DIR)\$(@B).cif $(MeChipsetLib_DIR)\$(@B).mak $(BUILD_RULES)
  $(CIF2MAK) $(MeChipsetLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

MeChipsetLib_INCLUDES =\
  $(EDK_INCLUDES) \
  $(EdkIIGlueLib_INCLUDES) \
  $(ME_INCLUDES) \
  $(INTEL_PCH_INCLUDES)

MeChipsetLibSmmBin : 
  $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
          /f $(BUILD_DIR)\MeChipsetLib.mak all\
          "MY_INCLUDES=$(MeChipsetLib_INCLUDES)" \
          TYPE=LIBRARY \
          LIBRARIES=\
          LIBRARY_NAME=$(MeChipsetSmmLib_LIB)

MeChipsetLibDxeBin : 
  $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
          /f $(BUILD_DIR)\MeChipsetLib.mak all\
          "MY_INCLUDES=$(MeChipsetLib_INCLUDES)" \
          "CFLAGS=$(CFLAGS) $(MeChipsetLib_DEFINES)"\
          TYPE=LIBRARY \
          LIBRARIES=\
          LIBRARY_NAME=$(MeChipsetDxeLib_LIB)

MeChipsetLibPeiBin :
!IF "$(x64_BUILD)"=="1" 
          $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS) BUILD_DIR=$(BUILD_DIR)\IA32\
!ELSE
          $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
!ENDIF
              /f $(BUILD_DIR)\MeChipsetLib.mak all\
              "MY_INCLUDES=$(MeChipsetLib_INCLUDES)"\
              "CFLAGS=$(CFLAGS) $(MeChipsetLib_DEFINES)"\
              TYPE=PEI_LIBRARY \
              LIBRARIES=\
              LIBRARY_NAME=$(MeChipsetPeiLib_LIB)
