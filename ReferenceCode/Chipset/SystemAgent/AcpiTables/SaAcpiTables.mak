all : SaAcpiTables

SaAcpiTables : $(BUILD_DIR)\SaAcpiTables.ffS

SaAcpiTables_Includes = \
	$(EDK_INCLUDES)\
	$(INTEL_MCH_INCLUDES)\

SaAcpiTables_Defines = \
    /D"TIANO_RELEASE_VERSION=0x00080006"\

SaAcpiTables_ACPIS = \
    $(BUILD_DIR)\Dmar.acpi\

$(BUILD_DIR)\SaAcpiTables.asl: $(BUILD_DIR)\token.mak $(SaAcpiTables_DIR)\SaAcpiTables.mak
	copy << $@
!IF "$(TCG2Support)" == "0" || "$(TCG2Support)" == ""
!IF "$(TCG_SUPPORT)" != "1" 
Name(TPMF, 0x0)
!ENDIF
!ENDIF
<<

$(BUILD_DIR)\Dmar.exe : $(SaAcpiTables_DIR)\Dmar\Dmar.act $(SaAcpiTables_DIR)\Dmar\Dmar.h
	@CL $(CFLAGS) $(SaAcpiTables_Defines) /Fo$(BUILD_DIR)\ $(SaAcpiTables_Includes) /TC $(SaAcpiTables_DIR)\Dmar\Dmar.act
	@Link  /OUT:$(BUILD_DIR)\Dmar.exe /NODEFAULTLIB /ENTRY:main $(BUILD_DIR)\Dmar.obj

$(BUILD_DIR)\Dmar.acpi : $(BUILD_DIR)\Dmar.exe
	$(GENACPITABLE) $(BUILD_DIR)\Dmar.exe $(BUILD_DIR)\Dmar.acpi

$(BUILD_DIR)\SaAcpiTables.sec : $(SaAcpiTables_ACPIS)
  $(GENSECTION) -I $** -O $@ -S EFI_SECTION_RAW

$(BUILD_DIR)\SaAcpiTables.ffs: $(BUILD_DIR)\SaAcpiTables.sec $(SaAcpiTables_DIR)\SaAcpiTables.mak
	$(MAKE) /f Core\FFS.mak \
		BUILD_DIR=$(BUILD_DIR) \
        GUID=27E569D5-0AFC-4D8F-8C90-783AC4A318AB\
		TYPE=EFI_FV_FILETYPE_FREEFORM \
        FFS_CHECKSUM=1\
		RAWFILE=$(BUILD_DIR)\SaAcpiTables.sec FFSFILE=$(BUILD_DIR)\SaAcpiTables.ffs COMPRESS=0 NAME=SaAcpiTables

