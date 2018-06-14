# MAK file for the ModulePart:CPU SEC RC
CPU_RC_DEPENDANCIES = \
$(CPU_RC_SEC_DIR)\Platform.inc \
$(CPU_RC_SEC_DIR)\Chipset.inc \
$(CPU_RC_SEC_DIR)\SecFlat32.inc 

$(BUILD_DIR)\CpuRcSec.obj : $(CPU_RC_SEC_DIR)\CpuRcSec.asm $(CPU_RC_DEPENDANCIES)
  $(ASM) /c /nologo /coff /Sa /I$(BUILD_DIR) /Fo$@ $(CPU_RC_SEC_DIR)\CpuRcSec.asm


# Add its own include path to
MY_INC =  \
/ICore \
/IEDK\Foundation\Framework\Ppi\SecPlatformInformation

# Add CrcSecPpi.obj to CORE_PEIBin dependency list, so it will be linked with PEI CORE
CORE_PEIBin: $(BUILD_DIR)\CrcSecPpi.obj 
# Add SecPlatformInformation.obj to CORE_PEIBin dependency list, so it will be linked with PEI CORE
CORE_PEIBin: $(BUILD_DIR)\SecPlatformInformation.obj

# Add a description block for CrcSecPpi.OBJ for cross-module link
$(BUILD_DIR)\CrcSecPpi.OBJ : $(CPU_RC_SEC_DIR)\CrcSecPpi.c
    $(CC) $(CFLAGS) $(MY_INC) /Fo$(BUILD_DIR)\CrcSecPpi.obj $(CPU_RC_SEC_DIR)\CrcSecPpi.c
 
# Add a description block for SecPlatformInformation.OBJ
$(BUILD_DIR)\SecPlatformInformation.obj : $(EdkFrameworkPpiLib_DIR)\SECPLATFORMINFORMATION\SecPlatformInformation.c
    $(CC) $(CFLAGS) $(EDK_INCLUDES) /D TIANO_RELEASE_VERSION=0x00080006 /Fo$(BUILD_DIR)\SecPlatformInformation.obj $(EdkFrameworkPpiLib_DIR)\SECPLATFORMINFORMATION\SecPlatformInformation.c 
