#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1987-2013, American Megatrends, Inc.            **
#**                                                                     **
#**                       All Rights Reserved.                          **
#**                                                                     **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
#**                                                                     **
#**                       Phone: (770)-246-8600                         **
#**                                                                     **
#*************************************************************************
#*************************************************************************

#*************************************************************************
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/Haswell/AMI Cpu PKG/CPU Board/CPU.mak 2     6/15/12 3:29a Davidhsieh $
#
# $Revision: 2 $
#
# $Date: 6/15/12 3:29a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/Haswell/AMI Cpu PKG/CPU Board/CPU.mak $
# 
# 2     6/15/12 3:29a Davidhsieh
# [TAG]  		None
# [Category]  	New Feature
# [Description]  	For FIT module support
# 
# 1     2/07/12 3:57a Davidhsieh
# 
#
#**********************************************************************

#<AMI_FHDR_START>
#---------------------------------------------------------------------------
# Name:			CPU.mak
#
# Description:	Make file for the CPU component.
#
#---------------------------------------------------------------------------
#<AMI_FHDR_END>


#---------------------------------------------------------------------------
#			Global Build Dependency List
#---------------------------------------------------------------------------
all : $(BUILD_DIR)\equates.equ CPUMODULE

CPUMODULE : STARTUP_DIR SECCORE CPU_PEI_BEFORE_MEM CPUPEI CPUDXE

$(BUILD_DIR)\Cpu.mak : $(CPU_BOARD_DIR)\CPU.mak $(CPU_CORE_DIR)\CPUCore.cif $(BUILD_RULES) $(CPU_BOARD_DIR)\CPUBSP.cif
	$(CIF2MAK) $(CPU_CORE_DIR)\CPUCore.cif $(CIF2MAK_DEFAULTS) $(CPU_BOARD_DIR)\CPUBSP.cif

$(BUILD_DIR)\equates.equ :
  @copy << $(BUILD_DIR)\equates.equ

<<
  @copy << $(BUILD_DIR)\mbiosequ.equ

<<

STARTUP_DIR: CREATE_BUILD_DIR CREATE_CPU_CORE_BUILD_DIR  CREATE_CPU_BOARD_BUILD_DIR CREATE_NB_SEC CREATE_SB_SEC

CREATE_BUILD_DIR:
	if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)

CREATE_CPU_CORE_BUILD_DIR:
	if not exist $(BUILD_DIR)\$(CPU_CORE_DIR) mkdir $(BUILD_DIR)\$(CPU_CORE_DIR)

CREATE_CPU_BOARD_BUILD_DIR:
	if not exist $(BUILD_DIR)\$(CPU_BOARD_DIR) mkdir $(BUILD_DIR)\$(CPU_BOARD_DIR)


#---------------------------------------------------------------------------

#---------------------------------------------------------------------------
#			Add files into CSP Library
#---------------------------------------------------------------------------
AMI_CSP_LIB_LIBRARY_PATH = $(PROJECT_DIR)\$(AMI_CSP_LIB_LIBRARY_PATH);$(PROJECT_DIR)\$(CPU_BOARD_DIR);$(PROJECT_DIR)\$(CPU_CORE_DIR)

AMI_CSP_LIB_INCLUDE_FILES = \
"$(CPU_CORE_DIR)\CpuCspLib.h" + \
$(AMI_CSP_LIB_INCLUDE_FILES)

AMI_CSP_LIB_OBJS = $(AMI_CSP_LIB_OBJS) \
$(BUILD_DIR)\CpuCspLib.obj \

{$(CPU_CORE_DIR)}.c{$(BUILD_DIR)}.obj::
	$(CC) $(CFLAGS) /I $(CPU_BOARD_DIR) /I $(CPU_CORE_DIR) /Fo$(BUILD_DIR)\ $<

{$(CPU_BOARD_DIR)}.c{$(BUILD_DIR)\$(CPU_BOARD_DIR)}.obj::
	$(CC) $(CFLAGS) /I $(CPU_BOARD_DIR) /I $(CPU_CORE_DIR) /Fo$(BUILD_DIR)\$(CPU_BOARD_DIR)\ $<

$(BUILD_DIR)\CpuCspLibAsm.obj: $(PROJECT_DIR)\$(CPU_CORE_DIR)\CpuCspLibAsm.asm
	$(ASM_TARGET) $(AFLAGS) /I $(CPU_BOARD_DIR) /Fo$(BUILD_DIR)\ $**

#---------------------------------------------------------------------------


#---------------------------------------------------------------------------
#			Making STARTUP Module
#---------------------------------------------------------------------------
TOP_FILE_GUID = 1BA0062E-C779-4582-8566-336AE8F78F09

SECCORE: $(BUILD_DIR)\Cpu.mak $(BUILD_DIR)\SecCore.ffs

$(BUILD_DIR)\ResVec.bin : $(BUILD_DIR)\ResVec.exe
	exe2bin $? $@

$(BUILD_DIR)\ResVec.exe : $(BUILD_DIR)\ResVec.obj
	$(ASMLINK) /m /ONERROR:NOEXE $?,$@,$(BUILD_DIR)\ResVec.map,,,

$(BUILD_DIR)\ResVec.obj : $(CPU_CORE_DIR)\ResetVector.asm
	$(ASM) $(AFLAGS) /c /nologo /Fo$@ $?

SEC_CORE_OBJ_FILES = \
$(BUILD_DIR)\$(CPU_CORE_DIR)\Startup32.obj

$(BUILD_DIR)\Startup.efi : $(ADDON_SEC_CORE_OBJ_FILES) $(BUILD_DIR)\$(CPU_CORE_DIR)\SecCoreSdl.obj
	@set INCLUDE=%%INCLUDE%%;$(CPU_BOARD_DIR)
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\Cpu.mak efi\
		NAME=Startup  MAKEFILE=$(BUILD_DIR)\Cpu.mak\
		"OBJECTS=$(SEC_CORE_OBJ_FILES)" \
		ENTRY_POINT=CPU_START\
		TYPE=PEIM 


$(BUILD_DIR)\$(CPU_CORE_DIR)\SecCoreSdl.obj : $(BUILD_DIR)\SECCoreL.ASM $(BUILD_DIR)\equates.equ
    $(ASM) $(AFLAGS) /coff /I$(CPU_CORE_DIR) /I$(CPU_BOARD_DIR) /Fo$@ $(BUILD_DIR)\SECCoreL.asm

$(BUILD_DIR)\SecCoreHdr.txt :
  @copy << $(BUILD_DIR)\SecCoreHdr.txt

.586p
.XMM

<<

$(BUILD_DIR)\SECCoreL.ASM : $(BUILD_DIR)\SECCore.ASM $(BUILD_DIR)\SecCoreHdr.txt
  copy /b $(BUILD_DIR)\SecCoreHdr.txt+$(BUILD_DIR)\SECCore.ASM $@


$(BUILD_DIR)\ApResetVec.bin : $(CPU_BOARD_DIR)\Cpu.mak
  @copy << $(BUILD_DIR)\StartupMerge.ini
output
	SEC_CORE($(BUILD_DIR)\ApResetVec.bin)
end
group SEC_CORE
 size = 0x10
 lower = 0
	components
		const(0xff, 0xff, 0xff)
		const(0xea, 0xd0, 0xff, 0x00, 0xf0)
	end
end
<<
    $(MERGE) $(BUILD_DIR)\StartupMerge.ini

$(BUILD_DIR)\SecCore.ffs : $(BUILD_DIR)\ResVec.bin $(BUILD_DIR)\Startup.efi $(BUILD_DIR)\ApResetVec.bin $(CPU_BOARD_DIR)\Cpu.mak
    $(CPU_TOOLS_DIR)\SecFixup $(BUILD_DIR)\Startup.efi $(BUILD_DIR)\ResVec.bin $(BUILD_DIR)\ResVec.fixup
!IF "$(SEC_CAN_START_APS)"=="1"
    $(CPU_TOOLS_DIR)\CreateSecFfs $(BUILD_DIR)\ApResetVec.bin 4096 $(BUILD_DIR)\Startup.efi $(BUILD_DIR)\ResVec.fixup $(BUILD_DIR)\SecCore.ffs
!ELSE
    $(CPU_TOOLS_DIR)\CreateSecFfs $(BUILD_DIR)\Startup.efi $(BUILD_DIR)\ResVec.fixup $(BUILD_DIR)\SecCore.ffs
!ENDIF

#---------------------------------------------------------------------------


#---------------------------------------------------------------------------
#			Making CPU PEI Module
#---------------------------------------------------------------------------
CPU_INCLUDE_DIR = $(CPU_BOARD_DIR)

CPU_BEFOREMEM_INCLUDE = \
    $(CPU_BOARD_DIR)\
    $(PROJECT_CPU_INCLUDES)

CPU_PEI_BEFORE_MEM : $(BUILD_DIR)\Cpu.mak CPU_PEI_BEFORE_MEM_BIN

CPU_PEI_BEFORE_MEM_OBJECTS = \
	$(BUILD_DIR)\$(CPU_CORE_DIR)\CpuPeiBeforeMem.obj

CPU_PEI_BEFORE_MEM_BIN : $(AMICSPLib) $(AMIPEILIB)
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\Cpu.mak all\
		NAME=CpuPeiBeforeMem MAKEFILE=$(BUILD_DIR)\Cpu.mak\
		"MY_INCLUDES=$(CPU_BEFOREMEM_INCLUDE)" \
		GUID=1555ACF3-BD07-4685-B668-A86945A4124D \
		"OBJECTS=$(CPU_PEI_BEFORE_MEM_OBJECTS)" \
		ENTRY_POINT=CpuPeiBeforeMemEntry\
		TYPE=PEIM \
		DEPEX1=\
		COMPRESS=0

CPU_PEI_OBJECTS = \
$(BUILD_DIR)\$(CPU_CORE_DIR)\CpuPei.obj \
$(BUILD_DIR)\$(CPU_CORE_DIR)\CpuPeiFuncs.obj \

CPUPEI : $(BUILD_DIR)\Cpu.mak CpuPeiBin

CpuPeiBin : $(AMIPEILIB) $(AMICSPLib)
	@set INCLUDE=%%INCLUDE%%;$(CPU_INCLUDE_DIR)
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\Cpu.mak all\
		NAME=CpuPei MAKEFILE=$(BUILD_DIR)\Cpu.mak\
		GUID=2BB5AFA9-FF33-417b-8497-CB773C2B93BF \
		"OBJECTS=$(CPU_PEI_OBJECTS)" \
		ENTRY_POINT=CpuPeiEntry\
		TYPE=PEIM \
		DEPEX1=$(CPU_CORE_DIR)\CpuPei.dxs DEPEX1_TYPE=EFI_SECTION_PEI_DEPEX \
		COMPRESS=0
#---------------------------------------------------------------------------

#---------------------------------------------------------------------------
#			Making CPU DXE Module
#---------------------------------------------------------------------------
CpuDxe : $(BUILD_DIR)\Cpu.mak CpuDxeBin

CPU_DXE_OBJECTS = \
$(BUILD_DIR)\$(CPU_CORE_DIR)\CpuDxe.obj \
$(BUILD_DIR)\$(CPU_CORE_DIR)\CpuDxeFuncs.obj \
!if "$(CPU_MODULE_CREATE_SMBIOS_TABLES)"=="1"
$(BUILD_DIR)\$(CPU_CORE_DIR)\CpuSmbios.obj \
!endif

DXE_PLATFORM_CPU_LIB = $(BUILD_DIR)\$(CPU_BOARD_DIR)\PlatformCpuLibDxe.obj

$(BUILD_DIR)\$(CPU_BOARD_DIR)\PlatformCpuLibDxe.obj : $(CPU_BOARD_DIR)\PlatformCpuLib.c
	$(CC) $(CFLAGS) /I$(CPU_CORE_DIR) /Fo$@ $(CPU_BOARD_DIR)\PlatformCpuLib.c

CpuDxeBin : $(DXE_PLATFORM_CPU_LIB) $(AMIDXELIB) $(AMICSPLib)
	@set INCLUDE=%%INCLUDE%%;$(CPU_INCLUDE_DIR)
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\Cpu.mak all\
		NAME=CpuDxe MAKEFILE=$(BUILD_DIR)\Cpu.mak\
		OBJECTS="$(CPU_DXE_OBJECTS)" \
		GUID=E03ABADF-E536-4e88-B3A0-B77F78EB34FE \
		ENTRY_POINT=DxeInitializeCpu\
		TYPE=RT_DRIVER \
		DEPEX1=$(CPU_CORE_DIR)\CpuDxe.dxs DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX \
		COMPRESS=1
#---------------------------------------------------------------------------

#-#---------------------------------------------------------------------------
#-#			Making CPU EIST ASL Module
#-#---------------------------------------------------------------------------
#-#-----------------------------------------------------------------------
#-# ASL compiler definition
#-#-----------------------------------------------------------------------
#-MASL 		= asl.exe 	# Microsoft ASL compiler
#-IASL 		= iasl.exe # Intel ASL compiler. Supports extended ACPI 2.0 asl objects
#-#-----------------------------------------------------------------------
#-ASL_COMPILER = MASL	# Default ASL compiler. Can be 'IASL' for Intel ASL and 'MASL' for Microsoft ASL compiler.
#-# Note. Msft. ASL compiler of version 1.0.14NT correctly process ACPI 2.0 extended ASL objects.
#-#-----------------------------------------------------------------------



#---------------------------------------------------------------------------
#		Create CPU Setup Screens
#---------------------------------------------------------------------------
SetupSdbs : $(BUILD_DIR)\CPU.mak CPUSDB
SetupBin : $(BUILD_DIR)\CpuSetup.obj $(AMICSPLib)

CPUSDB :
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\CPU.mak all\
		TYPE=SDB NAME=CPU MAKEFILE=$(BUILD_DIR)\CPU.mak "STRING_CONSUMERS=$(CPU_BOARD_DIR)\CPU.sd $(CPU_BOARD_DIR)\CpuSetup.c"

$(BUILD_DIR)\CPUSetup.obj : $(PROJECT_DIR)\$(CPU_BOARD_DIR)\CPUSetup.c $(BUILD_DIR)\SetupStrTokens.h
	$(CC) $(CFLAGS) /Fo$@ $(PROJECT_DIR)\$(CPU_BOARD_DIR)\CPUSetup.c

#---------------------------------------------------------------------------
#		CPU Debugger Initialization
#---------------------------------------------------------------------------

$(BUILD_DIR)\$(CPU_BOARD_DIR)\CpuPeiDebugger.obj : $(PROJECT_DIR)\$(CPU_BOARD_DIR)\CpuPeiDebugger.c
	$(CC) $(CFLAGS) /I $(CPU_CORE_DIR) /Fo$@ $(PROJECT_DIR)\$(CPU_BOARD_DIR)\CpuPeiDebugger.c

PeiDbgPortBin : $(BUILD_DIR)\$(CPU_BOARD_DIR)\CpuPeiDebugger.obj

#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1987-2013, American Megatrends, Inc.            **
#**                                                                     **
#**                       All Rights Reserved.                          **
#**                                                                     **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
#**                                                                     **
#**                       Phone: (770)-246-8600                         **
#**                                                                     **
#*************************************************************************
#*************************************************************************
