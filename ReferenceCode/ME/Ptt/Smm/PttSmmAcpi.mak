#-----------------------------------------------------------------------
# ASL compiler definition
#-----------------------------------------------------------------------
MASL     = $(SILENT)asl.exe   # Microsoft ASL compiler
!IF "$(ACPIPLATFORM_ASL_COMPILER)"==""
!ERROR It is an invalid path, please check your ASL compiler path.
!ENDIF

IASL = $(ACPIPLATFORM_ASL_COMPILER)  
#-----------------------------------------------------------------------
ASL_COMPILER = IASL  # Default ASL compiler. Can be 'IASL' for Intel ASL and 'MASL' for Microsoft ASL compiler.
# Note. Msft. ASL compiler of version 1.0.14NT correctly process ACPI 2.0 extended ASL objects.
#-----------------------------------------------------------------------
EDK : PTTASL

PTTASL:  $(BUILD_DIR)\PTTACPI.ffs

$(BUILD_DIR)\TPM.aml: $(INTEL_PTT_ASL_FILE)
!if "$(ASL_COMPILER)" == "MASL"
  $(MASL) /Fo=$@ $**
!elseif "$(ASL_COMPILER)" == "IASL"
  $(IASL) -p $(BUILD_DIR)\TPM.aml $(INTEL_PTT_ASL_FILE)
!endif

$(BUILD_DIR)\TPM.sec: $(BUILD_DIR)\TPM.aml
  $(GENSECTION) -I $** -O $@ -S EFI_SECTION_RAW
  
$(BUILD_DIR)\PTTACPI.ffs: $(BUILD_DIR)\TPM.sec $(PttHciSmm_DIR)\PttSmmAcpi.mak
  $(GENFFSFILE) -B $(BUILD_DIR) -V -o $@ -P1 <<$(BUILD_DIR)\PTTACPI.pkg
PACKAGE.INF
[.]
BASE_NAME                   = PTTACPI
FFS_FILEGUID                = 7D279373-EECC-4d4f-AE2F-CEC4B706B06A
FFS_FILETYPE                = EFI_FV_FILETYPE_FREEFORM
FFS_ATTRIB_CHECKSUM         = TRUE

IMAGE_SCRIPT =
{
  Compress (dummy) {
			$(PROJECT_DIR)\$(BUILD_DIR)\TPM.sec
  }
}
<<KEEP
#-----------------------------------------------------------------------