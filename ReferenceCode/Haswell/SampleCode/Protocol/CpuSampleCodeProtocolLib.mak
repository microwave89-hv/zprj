all : CpuSampleCodeProtocolLib

$(CpuSampleCodeProtocolLib_LIB) : CpuSampleCodeProtocolLib

CpuSampleCodeProtocolLib : $(BUILD_DIR)\CpuSampleCodeProtocolLib.mak CpuSampleCodeProtocolLibBin

$(BUILD_DIR)\CpuSampleCodeProtocolLib.mak : $(CpuSampleCodeProtocolLib_DIR)\$(@B).cif $(CpuSampleCodeProtocolLib_DIR)\$(@B).mak $(BUILD_RULES)
        $(CIF2MAK) $(CpuSampleCodeProtocolLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

CpuSampleCodeProtocolLib_INCLUDES=\
		$(EDK_INCLUDES)\
		$(EdkIIGlueLib_INCLUDES)\
		$(PROJECT_CPU_INCLUDES)\

CpuSampleCodeProtocolLibBin :
        $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
                /f $(BUILD_DIR)\CpuSampleCodeProtocolLib.mak all\
                "MY_INCLUDES=$(CpuSampleCodeProtocolLib_INCLUDES)" \
                TYPE=LIBRARY
!IF "$(x64_BUILD)"=="1"
        $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS) BUILD_DIR=$(BUILD_DIR)\IA32\
                /f $(BUILD_DIR)\CpuSampleCodeProtocolLib.mak all\
                "MY_INCLUDES=$(CpuSampleCodeProtocolLib_INCLUDES)" \
                TYPE=PEI_LIBRARY
!ENDIF