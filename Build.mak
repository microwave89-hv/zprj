#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2005, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************

#**********************************************************************
# $Header: /Alaska/BIN/Core/Build.mak 20    6/20/11 6:52p Felixp $
#
# $Revision: 20 $
#
# $Date: 6/20/11 6:52p $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Core/Build.mak $
# 
# 20    6/20/11 6:52p Felixp
# [TAG]  		EIP59772
# Script that generates Build\build.mak is updated to include
# token.mak into Build\build.mak. This is required to support override of
# the TODAY/NOW
# vairables via the SDL tokens.
# 
# 19    1/22/10 4:07p Felixp
# 
# 18    1/21/10 5:09p Felixp
# Updated to use ParseVeB tool. The tool generates project.ldl and
# project.lfo files.
# 
# 17    11/13/09 5:49p Felixp
# 
# 16    11/13/09 4:42p Felixp
# Script that generates Build\Timestamp.h is updated to include integer
# constants for the date/time components.
# 
# 15    3/05/09 9:47a Felixp
# Bug fix: Problem with target specific builds (build.bat target=X).
# Description: The target specific build didn't work for modules that 
#   use Setup.h without prior full build.
# Symptoms: Build fails with "SetupDefinitions.h not found" error.
# Details: Core make files are updated to add target that 
#   generates SetupDefinitions.h into the list of dependents of the top 
#   level target being built (original code only did it for target
# "all").
# 
# 14    4/10/08 11:53a Felixp
# Support for VS2008 tools added
# Return nmake error code
# 
# 13    12/28/06 6:38p Felixp
# 
# 12    12/28/06 6:37p Felixp
# 
# 11    12/28/06 6:22p Felixp
# VC8 32-bit compiler support added
# 
# 10    11/11/06 11:48a Felixp
# Support for date/time stamps(All executables generated with the
# identical date/time stamp)
# 
# 9     7/14/06 9:55a Pavell
# 
# 8     3/30/06 6:06p Felixp
# Support for compiler version auto-detection added.
# 
# 7     8/23/05 3:13p Felixp
# dependency from Build.mak added (once Build.mak modified "build all" is
# performed)
# 
# 6     6/17/05 3:25p Felixp
# $(PROJECT_DIR) added to the list of Include directories
# 
# 5     5/25/05 10:40a Felixp
# 
# 4     5/24/05 12:13a Felixp
# build all conditions extended
# 
# 3     5/23/05 3:55p Felixp
# AMISDL dependency from project.ldl added
# 
# 2     2/04/05 9:20a Felixp
# Clean command : hardcoded rom name replaced with logic to read the name
# from
# $(BUILD_DIR)\amiromname.txt (it is saved by the Core.mak)
# 
# 1     1/28/05 12:43p Felixp
# 
# 4     1/18/05 3:21p Felixp
# PrintDebugMessage renamed to Trace
# 
# 2     12/24/04 3:03p Felixp
# Full rebuild performed if system header modified
# 
# 1     12/23/04 9:41a Felixp
# 
# 9     7/13/04 10:42a Felixp
# 
# 8     5/14/04 5:15p Felixp
# 
# 7     1/22/04 9:37a Felixp
# 
# 6     1/15/04 11:58a Felixp
# 
# 5     1/08/04 4:46p Felixp
# comments improved
# 
# 4     12/15/03 5:11p Robert
# 
# 3     12/12/03 3:29p Felixp
# support for global includes for the C compiler added (BIOS_INCLUDE)
# 
# 2     12/12/03 12:22p Felixp
# if TARGET is not specified by the build.bat it is set to ALL
# 
# 1     12/05/03 4:15p Felixp
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	Build.mak
#
# Description:	
#	This is the file that is used to launch BIOS build process
#	It sets up all the necessary environment macros,
#	runs AMISDL if necessary, and
#	invokes Core.mak to do the rest.
#
#<AMI_FHDR_END>
#**********************************************************************
BUILD_DIR = Build
PROJECT_DIR = $(MAKEDIR)

!IF "$(TARGET)"==""
TARGET=ALL
!ENDIF

BIOS_INCLUDE = INCLUDE;$(BUILD_DIR);$(PROJECT_DIR)

ALL: CREATE_BUILD_DIR $(BUILD_DIR)\flag.txt TIMESTAMP $(BUILD_DIR)\TOKEN.MAK BUILD_BIOS_ROM

CREATE_BUILD_DIR:
	if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)
!IF "$(VEB)"!=""
    -ParseVeB /v$(VEB).veb /sproject.ldl /oproject.lfo /i /b
!ENDIF

!IF EXIST(project.ldl)
SDL_FILES =\
!include project.ldl

$(BUILD_DIR)\TOKEN.MAK : project.ldl $(SDL_FILES)
        AMISDL PROJECT.LDL s
!ELSE
$(BUILD_DIR)\TOKEN.MAK :
	@echo project.ldl not found. 
    @echo Use VeB "Rebuild All" command to create project.ldl.
    @echo To build from the command line(without VeB), initialize VEB variable with the name of the project .veb file (For example: set VEB=MyProject).
	@AMISDL PROJECT.LDL s > NULL
!ENDIF

$(BUILD_DIR)\flag.txt: Include\*.* Include\Protocol\*.* Include\PPI\*.* Core\Core.sdl Build.mak
	-del /S /Q $(BUILD_DIR)\* > NUL
	time /T >>$(BUILD_DIR)\flag.txt	


TIMESTAMP:
!IF "$(TODAY)"=="" || "$(NOW)"==""
    cd $(BUILD_DIR)
    dater.exe /CREATEMAKEFILE
    cd $(PROJECT_DIR)
!ENDIF
	@COPY << $(BUILD_DIR)\stamp.bat
@ECHO OFF
ECHO TODAY = %1 > $(BUILD_DIR)\timestamp.mak
ECHO NOW = %2 >> $(BUILD_DIR)\timestamp.mak
ECHO TODAY  TEXTEQU ^<%1^> > $(BUILD_DIR)\timestamp.equ
ECHO NOW  TEXTEQU ^<%2^> >> $(BUILD_DIR)\timestamp.equ
ECHO #ifndef __TIMESTAMP_H__ > $(BUILD_DIR)\timestamp.h
ECHO #define __TIMESTAMP_H__ >> $(BUILD_DIR)\timestamp.h
ECHO #define TODAY "%1" >> $(BUILD_DIR)\timestamp.h
ECHO #define NOW "%2" >> $(BUILD_DIR)\timestamp.h
ECHO #define L_TODAY L"%1" >> $(BUILD_DIR)\timestamp.h
ECHO #define L_NOW L"%2" >> $(BUILD_DIR)\timestamp.h
FOR /F "TOKENS=1,2,3 DELIMS=/ " %%A IN ('ECHO %1') DO (
ECHO FOUR_DIGIT_YEAR = %%C >> $(BUILD_DIR)\timestamp.mak
ECHO TWO_DIGIT_MONTH = %%A >> $(BUILD_DIR)\timestamp.mak
ECHO TWO_DIGIT_DAY = %%B >> $(BUILD_DIR)\timestamp.mak
ECHO FOUR_DIGIT_YEAR  TEXTEQU ^<%%C^> >> $(BUILD_DIR)\timestamp.equ
ECHO TWO_DIGIT_MONTH  TEXTEQU ^<%%A^> >> $(BUILD_DIR)\timestamp.equ
ECHO TWO_DIGIT_DAY    TEXTEQU ^<%%B^> >> $(BUILD_DIR)\timestamp.equ
ECHO #define FOUR_DIGIT_YEAR "%%C" >> $(BUILD_DIR)\timestamp.h
ECHO #define TWO_DIGIT_MONTH "%%A" >> $(BUILD_DIR)\timestamp.h
ECHO #define TWO_DIGIT_DAY   "%%B" >> $(BUILD_DIR)\timestamp.h
ECHO #define L_FOUR_DIGIT_YEAR L"%%C" >> $(BUILD_DIR)\timestamp.h
ECHO #define L_TWO_DIGIT_MONTH L"%%A" >> $(BUILD_DIR)\timestamp.h
ECHO #define L_TWO_DIGIT_DAY   L"%%B" >> $(BUILD_DIR)\timestamp.h
ECHO #define FOUR_DIGIT_YEAR_INT %%C >> $(BUILD_DIR)\timestamp.h
ECHO #define TWO_DIGIT_MONTH_INT ^(1%%A-100^) >> $(BUILD_DIR)\timestamp.h
ECHO #define TWO_DIGIT_DAY_INT   ^(1%%B-100^) >> $(BUILD_DIR)\timestamp.h
)
FOR /F "TOKENS=1,2,3 DELIMS=: " %%A IN ('ECHO %2') DO (
ECHO TWO_DIGIT_HOUR = %%A >> $(BUILD_DIR)\timestamp.mak
ECHO TWO_DIGIT_MINUTE = %%B >> $(BUILD_DIR)\timestamp.mak
ECHO TWO_DIGIT_SECOND = %%C >> $(BUILD_DIR)\timestamp.mak
ECHO TWO_DIGIT_HOUR    TEXTEQU ^<%%A^> >> $(BUILD_DIR)\timestamp.equ
ECHO TWO_DIGIT_MINUTE  TEXTEQU ^<%%B^> >> $(BUILD_DIR)\timestamp.equ
ECHO TWO_DIGIT_SECOND  TEXTEQU ^<%%C^> >> $(BUILD_DIR)\timestamp.equ
ECHO #define TWO_DIGIT_HOUR    "%%A" >> $(BUILD_DIR)\timestamp.h
ECHO #define TWO_DIGIT_MINUTE  "%%B" >> $(BUILD_DIR)\timestamp.h
ECHO #define TWO_DIGIT_SECOND  "%%C" >> $(BUILD_DIR)\timestamp.h
ECHO #define L_TWO_DIGIT_HOUR    L"%%A" >> $(BUILD_DIR)\timestamp.h
ECHO #define L_TWO_DIGIT_MINUTE  L"%%B" >> $(BUILD_DIR)\timestamp.h
ECHO #define L_TWO_DIGIT_SECOND  L"%%C" >> $(BUILD_DIR)\timestamp.h
ECHO #define TWO_DIGIT_HOUR_INT    ^(1%%A-100^) >> $(BUILD_DIR)\timestamp.h
ECHO #define TWO_DIGIT_MINUTE_INT  ^(1%%B-100^) >> $(BUILD_DIR)\timestamp.h
ECHO #define TWO_DIGIT_SECOND_INT  ^(1%%C-100^) >> $(BUILD_DIR)\timestamp.h
)
ECHO #endif >> $(BUILD_DIR)\timestamp.h
<<

#The logic below used to detect which version 
# of compiler we are dealing with.
#If compiler version can not be detected, use default settings.
_IF=!IF
_ELSE=!ELSE
_ELSEIF=!ELSEIF
_ENDIF=!ENDIF
_MESSAGE=!MESSAGE
_INCLUDE=!INCLUDE

BUILD_BIOS_ROM :
	set PROJECT_DIR=$(PROJECT_DIR)
	set INCLUDE=$(BIOS_INCLUDE);%%INCLUDE%%
	@cl /nologo /EP << > $(BUILD_DIR)\build.mak
$(_IF) _MSC_VER>=1400
AUTO_TOOLS=vc8
$(_ELSEIF) _MSC_VER==1310
AUTO_TOOLS=vc71
$(_ELSEIF) _MSC_VER==1200
AUTO_TOOLS=vc6
$(_ELSE)
AUTO_TOOLS=Unknown(MSC_VER=_MSC_VER)
TOOLS=vc6
$(_ENDIF)
$(_IF) "$$(TOOLS)"==""
TOOLS=$$(AUTO_TOOLS)
$(_ENDIF)
$(_IF) EXIST ($(BUILD_DIR)\Dater.mak)
$(_INCLUDE) $(BUILD_DIR)\Dater.mak
$(_ENDIF)
$(_INCLUDE) $(BUILD_DIR)\token.mak
all :
    $(BUILD_DIR)\stamp.bat $$(TODAY) $$(NOW)
$(_IF) "$$(TOOLS)"!="$$(AUTO_TOOLS)"
	@echo BUILD OPTIONS USED: $$(TOOLS);  COMPILER USED: $$(AUTO_TOOLS)
$(_ELSE)
//#	@echo COMPILER USED: $$(AUTO_TOOLS)
$(_ENDIF)
	@set TOOLS=$$(TOOLS)
	$(MAKE) /$(MAKEFLAGS) /f Core\core.mak BUILD_DIR=$(BUILD_DIR) TARGET=$(TARGET) $(TARGET)
$(_IF) "$$(TOOLS)"!="$$(AUTO_TOOLS)"
	@echo BUILD OPTIONS USED: $$(TOOLS);  COMPILER USED: $$(AUTO_TOOLS)
$(_ELSE)
//#	@echo COMPILER USED: $$(AUTO_TOOLS)
$(_ENDIF)
<<KEEP
	@$(MAKE) /$(MAKEFLAGS) /f $(BUILD_DIR)\build.mak

CLEAN: 
!IF EXISTS($(BUILD_DIR)\amiromname.txt)
	 -for /F %f in ($(BUILD_DIR)\amiromname.txt) do del %f
!ENDIF
     -rd /S /Q $(BUILD_DIR)
	 -md $(BUILD_DIR)
     -del build.log

REBUILD: CLEAN ALL
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2005, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************
