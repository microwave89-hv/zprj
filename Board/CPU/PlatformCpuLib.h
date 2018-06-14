//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1987-2013, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

//*************************************************************************
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/Haswell/AMI Cpu PKG/CPU Board/PlatformCpuLib.h 6     7/23/13 7:41a Crystallee $
//
// $Revision: 6 $
//
// $Date: 7/23/13 7:41a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/Haswell/AMI Cpu PKG/CPU Board/PlatformCpuLib.h $
// 
// 6     7/23/13 7:41a Crystallee
// [TAG]  		EIP128089
// [Category]  	Improvement
// [Description]  	TXT will be disabled and grayed out in Setup when TPM
// Support is disabled.
// 
// 5     2/22/13 2:00a Crystallee
// [TAG]  		EIP112238
// [Category]  	Improvement
// [Description]  	Refer Intel BIOS and provide setup items for Intel
// Haswell RC policy.
// 
// 4     11/23/12 4:14a Davidhsieh
// [TAG]  		EIPNone
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	Ctdp setup item is not displayed in setup menu
// [RootCause]  	The cTDPAvailable value is not initialzied
// [Solution]  	Initial cTDPAvailable value
// 
// 3     10/17/12 2:23a Davidhsieh
// [TAG]                None
// [Category]         Improvement
// [Description]      Setup items CTDP BIOS, C8, C9 and C10 created
// 
// 2     3/16/12 3:35a Davidhsieh
// Setup items create for CPU RC policy
// 
// 1     2/07/12 3:57a Davidhsieh
// 
//**********************************************************************

//<AMI_FHDR_START>
//---------------------------------------------------------------------------
// Name:		PlatformCpuLib.h
//
// Description:	Platform CPU library.
//
//---------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef __PLATFORM_CPU_LIB_H__
#define __PLATFORM_CPU_LIB_H__

#ifdef __cplusplus
extern "C" {
#endif

#ifndef VFRCOMPILE
#include <efi.h>
#include <Pei.h>

EFI_STATUS PeiInitPlatformCpuLib(IN EFI_PEI_SERVICES **PeiServices, OUT VOID **Handle);
EFI_STATUS DxeInitPlatformCpuLib(
    IN EFI_BOOT_SERVICES       *Bs,
    IN EFI_RUNTIME_SERVICES    *Rs,
	OUT VOID **Handle
);

EFI_STATUS DxePlatformCpuSaveSupportedData(
    IN EFI_RUNTIME_SERVICES    *Rs
);

UINT8 GetPlatformNumCores(IN VOID *Handle, UINT32 Package);
BOOLEAN GetPlatformCpuLimitCpuidEnable(IN VOID *Handle);
BOOLEAN GetPlatformCpux2ApicEnable(IN VOID *Handle);
BOOLEAN GetPlatformCpuVtEnable(IN VOID *Handle);
BOOLEAN GetPlatformCpuXdEnable(IN VOID *Handle);
UINT32 GetPlatformCpuGroup(IN VOID *Handle);
UINT32 GetPlatformCpuBootRatio(IN VOID *Handle);
/////////////////////////////////////////////////////////////
//These functions are currently only availabe in DXE not PEI.
/////////////////////////////////////////////////////////////

VOID PlatformCpuCtdpSupport(
    IN VOID *Handle,
    IN BOOLEAN Supported
);

VOID PlatformCpuLimitCpuidSupport(
    IN VOID *Handle,
    IN BOOLEAN Supported
);

VOID PlatformCpuHtSupport(
    IN VOID *Handle,
    IN BOOLEAN Supported
);

VOID PlatformCpuMultiCoreSupport(
    IN VOID *Handle,
    IN BOOLEAN Supported
);

VOID PlatformCpuMultiSocketSupport(
    IN VOID *Handle,
    IN BOOLEAN Supported
);

VOID PlatformCpuMultiSocketPopulated(
    IN VOID *Handle,
    IN BOOLEAN Populated
);

VOID PlatformCpuXdSupport(
    IN VOID *Handle,
    IN BOOLEAN Supported
);

VOID PlatformCpuVtSupport(
    IN VOID *Handle,
    IN BOOLEAN Supported
);

VOID PlatformCpuSmxSupport(
    IN VOID *Handle,
    IN BOOLEAN Supported
);

VOID PlatformCpuLocalx2ApicSupport(
    IN VOID *Handle,
    IN BOOLEAN Supported
);

VOID PlatformCpuSocketSetPopulated(
    IN VOID *Handle,
    IN UINT32 Socket,
    IN BOOLEAN Populated
);

VOID PlatformCpuMismatch(
    IN VOID *Handle,
    IN BOOLEAN Mismatch
);

VOID PlatformCpuXeCoreRatioLimitSupport(
    IN VOID *Handle,
    IN BOOLEAN Supported
);

VOID PlatformCpuCurrentLimitSupport(
    IN VOID *Handle,
    IN BOOLEAN Supported
);

VOID PlatformCpuTccActiveOffsetSupport(
    IN VOID *Handle,
    IN BOOLEAN Supported
);

VOID PlatformCpuEistSupport(
    IN VOID *Handle,
    IN BOOLEAN Supported
);

VOID PlatformCpuTurboModeSupport(
    IN VOID *Handle,
    IN BOOLEAN Supported
);

VOID PlatformCpuC3Support(
    IN VOID *Handle,
    IN BOOLEAN Supported
);

VOID PlatformCpuC6Support(
    IN VOID *Handle,
    IN BOOLEAN Supported
);

VOID PlatformCpuC7Support(
    IN VOID *Handle,
    IN BOOLEAN Supported
);

VOID PlatformCpuC8Support(
    IN VOID *Handle,
    IN BOOLEAN Supported
);

VOID PlatformCpuC9Support(
    IN VOID *Handle,
    IN BOOLEAN Supported
);

VOID PlatformCpuC10Support(
    IN VOID *Handle,
    IN BOOLEAN Supported
);

VOID PlatformCpuAesSupport(
    IN VOID *Handle,
    IN BOOLEAN Supported
);

VOID PlatformCpuPkgCStateDemotionSupport(
    IN VOID *Handle,
    IN BOOLEAN Supported
);

VOID PlatformCpuPwrLimitConfigSupport(
    IN VOID *Handle,
    IN BOOLEAN Supported
);

VOID PlatformTpmDevicePresent(
    IN VOID *Handle,
    IN BOOLEAN Supported
);
#endif

////////////////////////////////////////////////////////////////
//This is a private structure that is used for setup by Cpu.Sd
//This structure can change any time. No drivers should refer
// directly to this structure.
////////////////////////////////////////////////////////////////
typedef struct {
	UINT8	XDBitAvailable;
	UINT8	HTAvailable;
    UINT8   MultiCoreAvailable;
	UINT8	VTAvailable;
	UINT8	LimitCpuidAvailable;
    UINT8   MultiSocketAvailable;
    UINT8   MultiSocketPopulated;
    UINT8   LocalX2ApicAvailable;
    UINT8   NumCores;
    UINT8   CpuGroup;   //Arbitrary number
    UINT8   IsSandyBridge;
    UINT8   IsHasWell;
    UINT8   Skt0Pop;
    UINT8   Skt1Pop;
    UINT8   Skt2Pop;
    UINT8   Skt3Pop;
	UINT8	SmxAvailable;
	UINT8   CpuMismatch;
	UINT8   XECoreRatioLimitAvailable;
	UINT8   CurrentLimitAvailable;
	UINT8   PwrLimitAvailable;
	UINT8   TccActivationAvailable;
	UINT8   EistAvailable;
	UINT8   TurboModeAvailable;
	UINT8   C3Available;
	UINT8   C6Available;
	UINT8   C7Available;
	UINT8   AesAvailable;
	UINT8   cTDPAvailable;
	UINT8   C8Available;
	UINT8   C9Available;
	UINT8   C10Available;
    UINT8   PkgCStateDemotionAvailable;
	UINT8	TpmDeviceAvailable;
} SETUP_CPU_FEATURES;


/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1987-2013, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

