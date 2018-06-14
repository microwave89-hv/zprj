# MAK file for the ModulePart:PpmProtocolLib

all : CpuProtocolLib

$(BUILD_DIR)\CpuProtocolLib.lib : CpuProtocolLib

CpuProtocolLib : $(BUILD_DIR)\CpuProtocolLib.mak CpuProtocolLibBin

$(BUILD_DIR)\CpuProtocolLib.mak : $(CpuProtocolLib_DIR)\$(@B).cif $(CpuProtocolLib_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(CpuProtocolLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)


CpuProtocolLibDxe_DEFINES = \
    $(CFLAGS) \
!IF "$(x64_BUILD)"=="1" 
    /DMDE_CPU_X64 \
!ELSE
    /DMDE_CPU_IA32 \
!ENDIF


CpuProtocolLibBin : 
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		/f $(BUILD_DIR)\CpuProtocolLib.mak all\
		"MY_INCLUDES=$(EDK_INCLUDES) $(PROJECT_CPU_INCLUDES) $(EdkIIGlueLib_INCLUDES)" \
		"CFLAGS=$(CpuProtocolLibDxe_DEFINES)"\
        TYPE=LIBRARY \
        LIBRARY_NAME=$(CpuProtocolLib_LIB)
