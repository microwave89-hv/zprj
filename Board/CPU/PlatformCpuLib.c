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
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/Haswell/AMI Cpu PKG/CPU Board/PlatformCpuLib.c 7     4/10/15 2:37a Crystallee $
//
// $Revision: 7 $
//
// $Date: 4/10/15 2:37a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/Haswell/AMI Cpu PKG/CPU Board/PlatformCpuLib.c $
// 
// 7     4/10/15 2:37a Crystallee
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
// Name:		PlatformCpuLib.c
//
// Description:	Platform CPU Lib C source file
//
//---------------------------------------------------------------------------
//<AMI_FHDR_END>

#include <efi.h>
#include <Pei.h>
#include <Dxe.h>
#include <AmiLib.h>
#include <Setup.h>
#include <Ppi\ReadOnlyVariable.h>
#include <AmiCspLib.h>
#include "PlatformCpuLib.h"
#include "Cpu.h"

static EFI_GUID gAmiSetupGuid = SETUP_GUID;
static EFI_GUID gEfiPeiReadOnlyVariablePpiGuid = EFI_PEI_READ_ONLY_VARIABLE_PPI_GUID;

typedef struct {
    SETUP_DATA *SetupData;
} PRIVATE_CPU_SETUP_LIB;

//-------------------------------------------------------------------------------

SETUP_CPU_FEATURES  gSetupCpuFeatures;

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PlatformTpmDevicePresent
//
// Description:	Set if Tpm device is present.
//
// Input:
//      IN VOID *Handle
//      IN BOOLEAN Supported
//
// Output: VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID PlatformTpmDevicePresent(
    IN VOID *Handle,
    IN BOOLEAN Supported
)
{
    gSetupCpuFeatures.TpmDeviceAvailable = Supported;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PlatformCpuCtdpSupport
//
// Description:	Set if supported by platform.
//
// Input:
//      IN VOID *Handle
//      IN BOOLEAN Supported
//
// Output: VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID PlatformCpuCtdpSupport(
    IN VOID *Handle,
    IN BOOLEAN Supported
)
{
    gSetupCpuFeatures.cTDPAvailable = Supported;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PlatformCpuLimitCpuidSupport
//
// Description:	Set if supported by platform.
//
// Input:
//      IN VOID *Handle
//      IN BOOLEAN Supported
//
// Output: VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID PlatformCpuLimitCpuidSupport(
    IN VOID *Handle,
    IN BOOLEAN Supported
)
{
    gSetupCpuFeatures.LimitCpuidAvailable = Supported;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PlatformCpuHtSupport
//
// Description:	Set if supported by platform.
//
// Input:
//      IN VOID *Handle
//      IN BOOLEAN Supported
//
// Output: VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID PlatformCpuHtSupport(
    IN VOID *Handle,
    IN BOOLEAN Supported
)
{
	gSetupCpuFeatures.HTAvailable = Supported;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PlatformCpuMultiCoreSupport
//
// Description:	Set if supported by platform.
//
// Input:
//      IN VOID *Handle
//      IN BOOLEAN Supported
//
// Output: VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID PlatformCpuMultiCoreSupport(
    IN VOID *Handle,
    IN BOOLEAN Supported
)
{
    gSetupCpuFeatures.MultiCoreAvailable = Supported;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PlatformCpuMultiSocketSupport
//
// Description:	Set if supported by platform.
//
// Input:
//      IN VOID *Handle
//      IN BOOLEAN Supported
//
// Output: VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID PlatformCpuMultiSocketSupport(
    IN VOID *Handle,
    IN BOOLEAN Supported
)
{
    gSetupCpuFeatures.MultiSocketAvailable = Supported;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PlatformCpuMultiSocketPopulated
//
// Description:	Set if supported by platform.
//
// Input:
//      IN VOID *Handle
//      IN BOOLEAN Populated
//
// Output: VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID PlatformCpuMultiSocketPopulated(
    IN VOID *Handle,
    IN BOOLEAN Populated
)
{
    gSetupCpuFeatures.MultiSocketPopulated = Populated;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PlatformCpuXdSupport
//
// Description:	Set if supported by platform.
//
// Input:
//      IN VOID *Handle
//      IN BOOLEAN Supported
//
// Output: VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID PlatformCpuXdSupport(
    IN VOID *Handle,
    IN BOOLEAN Supported
)
{
    gSetupCpuFeatures.XDBitAvailable = Supported;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PlatformCpuSmxSupport
//
// Description:	Set if supported by platform.
//
// Input:
//      IN VOID *Handle
//      IN BOOLEAN Supported
//
// Output: VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID PlatformCpuSmxSupport(
    IN VOID *Handle,
    IN BOOLEAN Supported
)
{
    gSetupCpuFeatures.SmxAvailable = Supported;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PlatformCpuVtSupport
//
// Description:	Set if supported by platform.
//
// Input:
//      IN VOID *Handle
//      IN BOOLEAN Supported
//
// Output: VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID PlatformCpuVtSupport(
    IN VOID *Handle,
    IN BOOLEAN Supported
)
{
    gSetupCpuFeatures.VTAvailable = Supported;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PlatformCpuLocalx2ApicSupport
//
// Description:	Set if supported by platform.
//
// Input:
//      IN VOID *Handle
//      IN BOOLEAN Supported
//
// Output: VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID PlatformCpuLocalx2ApicSupport(
    IN VOID *Handle,
    IN BOOLEAN Supported
)
{
    gSetupCpuFeatures.LocalX2ApicAvailable = Supported;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PlatformCpuSocketSetPopulated
//
// Description:	Set sockets populated.
//
// Input:
//  IN VOID *Handle - Setup Handle
//  IN UINT32 Socket - Socket (0-based)
//  IN BOOLEAN Populated - TRUE if populated. Default: Not populated.
//
// Output: VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID PlatformCpuSocketSetPopulated(
    IN VOID *Handle,
    IN UINT32 Socket,
    IN BOOLEAN Populated
)
{
    switch(Socket) {
    case 0: gSetupCpuFeatures.Skt0Pop = TRUE; break;
    case 1: gSetupCpuFeatures.Skt1Pop = TRUE; break;
    case 2: gSetupCpuFeatures.Skt2Pop = TRUE; break;
    case 3: gSetupCpuFeatures.Skt3Pop = TRUE; break;
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PlatformCpuXeCoreRatioLimitSupport
//
// Description:	Set if supported by platform.
//
// Input:
//      IN VOID *Handle
//      IN BOOLEAN Supported
//
// Output: VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID PlatformCpuXeCoreRatioLimitSupport(
    IN VOID *Handle,
    IN BOOLEAN Supported
)
{
	gSetupCpuFeatures.XECoreRatioLimitAvailable = Supported;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PlatformCpuCurrentLimitSupport
//
// Description:	Set if supported by platform.
//
// Input:
//      IN VOID *Handle
//      IN BOOLEAN Supported
//
// Output: VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID PlatformCpuCurrentLimitSupport(
    IN VOID *Handle,
    IN BOOLEAN Supported
)
{
	gSetupCpuFeatures.CurrentLimitAvailable = Supported;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PlatformCpuPwrLimitConfigSupport
//
// Description:	Set if supported by platform.
//
// Input:
//      IN VOID *Handle
//      IN BOOLEAN Supported
//
// Output: VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID PlatformCpuPwrLimitConfigSupport(
    IN VOID *Handle,
    IN BOOLEAN Supported
)
{
	gSetupCpuFeatures.PwrLimitAvailable = Supported;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PlatformCpuEistSupport
//
// Description:	Set if supported by platform.
//
// Input:
//      IN VOID *Handle
//      IN BOOLEAN Supported
//
// Output: VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID PlatformCpuEistSupport(
    IN VOID *Handle,
    IN BOOLEAN Supported
)
{
	gSetupCpuFeatures.EistAvailable = Supported;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PlatformCpuTurboModeSupport
//
// Description:	Set if supported by platform.
//
// Input:
//      IN VOID *Handle
//      IN BOOLEAN Supported
//
// Output: VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID PlatformCpuTurboModeSupport(
    IN VOID *Handle,
    IN BOOLEAN Supported
)
{
	gSetupCpuFeatures.TurboModeAvailable = Supported;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PlatformCpuPkgCStateDemotionSupport
//
// Description:	Set if supported by platform.
//				Available only in 4th Generation Intelr CoreT
//				processors with signature greater than 000306C1h.
//
// Input:
//      IN VOID *Handle
//      IN BOOLEAN Supported
//
// Output: VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID PlatformCpuPkgCStateDemotionSupport(
    IN VOID *Handle,
    IN BOOLEAN Supported
)
{
	gSetupCpuFeatures.PkgCStateDemotionAvailable = Supported;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PlatformCpuC3Support
//
// Description:	Set if supported by platform.
//
// Input:
//      IN VOID *Handle
//      IN BOOLEAN Supported
//
// Output: VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID PlatformCpuC3Support(
    IN VOID *Handle,
    IN BOOLEAN Supported
)
{
	gSetupCpuFeatures.C3Available = Supported;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PlatformCpuC6Support
//
// Description:	Set if supported by platform.
//
// Input:
//      IN VOID *Handle
//      IN BOOLEAN Supported
//
// Output: VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID PlatformCpuC6Support(
    IN VOID *Handle,
    IN BOOLEAN Supported
)
{
	gSetupCpuFeatures.C6Available = Supported;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PlatformCpuC7Support
//
// Description:	Set if supported by platform.
//
// Input:
//      IN VOID *Handle
//      IN BOOLEAN Supported
//
// Output: VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID PlatformCpuC7Support(
    IN VOID *Handle,
    IN BOOLEAN Supported
)
{
	gSetupCpuFeatures.C7Available = Supported;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PlatformCpuC8Support
//
// Description:	Set if supported by platform.
//
// Input:
//      IN VOID *Handle
//      IN BOOLEAN Supported
//
// Output: VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID PlatformCpuC8Support(
    IN VOID *Handle,
    IN BOOLEAN Supported
)
{
	gSetupCpuFeatures.C8Available = Supported;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PlatformCpuC9Support
//
// Description:	Set if supported by platform.
//
// Input:
//      IN VOID *Handle
//      IN BOOLEAN Supported
//
// Output: VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID PlatformCpuC9Support(
    IN VOID *Handle,
    IN BOOLEAN Supported
)
{
	gSetupCpuFeatures.C9Available = Supported;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PlatformCpuC10Support
//
// Description:	Set if supported by platform.
//
// Input:
//      IN VOID *Handle
//      IN BOOLEAN Supported
//
// Output: VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID PlatformCpuC10Support(
    IN VOID *Handle,
    IN BOOLEAN Supported
)
{
	gSetupCpuFeatures.C10Available = Supported;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PlatformCpuAesSupport
//
// Description:	Set if supported by platform.
//
// Input:
//      IN VOID *Handle
//      IN BOOLEAN Supported
//
// Output: VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID PlatformCpuAesSupport(
    IN VOID *Handle,
    IN BOOLEAN Supported
)
{
	gSetupCpuFeatures.AesAvailable = Supported;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PlatformCpuCurrentLimitSupport
//
// Description:	Set if supported by platform.
//
// Input:
//      IN VOID *Handle
//      IN BOOLEAN Supported
//
// Output: VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID PlatformCpuTccActiveOffsetSupport(
    IN VOID *Handle,
    IN BOOLEAN Supported
)
{
	gSetupCpuFeatures.TccActivationAvailable = Supported;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PlatformCpuMismatch
//
// Description:	Report is populated CPU combination is not supported.
//
// Input:
//  IN VOID *Handle - Setup Handle
//  IN BOOLEAN Mismatch - TRUE if CPU combination not supported. Default: Not populated.
//
// Output: VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID PlatformCpuMismatch(
    IN VOID *Handle,
    IN BOOLEAN Mismatch
)
{
    gSetupCpuFeatures.CpuMismatch = Mismatch;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	DxePlatformCpuSaveSupportedData
//
// Description:	This functions saves the CPU supported data.
//
// Input:
//      IN EFI_RUNTIME_SERVICES    *Rs
//
// Output: EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS DxePlatformCpuSaveSupportedData(
    IN EFI_RUNTIME_SERVICES    *Rs
)
{
    return Rs->SetVariable(
        L"SetupCpuFeatures",
        &gAmiSetupGuid,
        EFI_VARIABLE_BOOTSERVICE_ACCESS,
        sizeof(SETUP_CPU_FEATURES),
        &gSetupCpuFeatures
    );
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure:	GetPlatformCpuGroup
//
// Description:	Get the CPU group for the platform policy.
//
// Input:
//      IN VOID *Handle
//
// Output:
//      UINT32 Cpu Group
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT32 GetPlatformCpuGroup(IN VOID *Handle) {
    UINT32 NumCores = NumSupportedCpuCores();
          
	switch (NumCores) {
		case 8: return 1;
		case 4: return 2;
		case 2: return 5;
		default: return 2;
	}
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	GetPlatformNumCores
//
// Description:	Get the maximum number of cores supported by processor.
//
// Input:
//      IN VOID     *Handle
//      IN UINT32   Package - Package number. If question applies to all packages, use 0.
//
// Output:
//      UINT8 - Number of cores
//          Output may be CPU specific, since this is handled by CPU specific model.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8 GetPlatformNumCores(IN VOID *Handle, UINT32 Package)
{
    SETUP_DATA *SetupData;
    if (Handle == NULL) return 0xff;	//No setup

	SetupData = ((PRIVATE_CPU_SETUP_LIB*)Handle)->SetupData;
    return SetupData->ActiveCoreCount;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	GetPlatformCpuLimitCpuidEnable
//
// Description:	Get the platform policy of limiting Cpuid.
//
// Input:
//      IN VOID *Handle
//
// Output:
//      BOOLEAN -- True Limit CPU ID.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN GetPlatformCpuLimitCpuidEnable(IN VOID *Handle)
{
    SETUP_DATA *SetupData;
    if (Handle == NULL) return FALSE;	//No setup

    SetupData = ((PRIVATE_CPU_SETUP_LIB*)Handle)->SetupData;
    return (BOOLEAN) SetupData->LimitCpuid;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	GetPlatformCpux2ApicEnable
//
// Description:	Get the platform policy of enable x2Apic.
//
// Input:
//      IN VOID *Handle
//
// Output:
//      BOOLEAN -- True Enable x2Apic
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN GetPlatformCpux2ApicEnable(IN VOID *Handle)
{
    SETUP_DATA *SetupData;
    if (Handle == NULL) return FALSE;	//No setup

    SetupData = ((PRIVATE_CPU_SETUP_LIB*)Handle)->SetupData;
    return (BOOLEAN) SetupData->LocalX2Apic;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	GetPlatformCpuVtEnable
//
// Description:	Get the platform policy of enable VT.
//
// Input:
//      IN VOID *Handle
//
// Output:
//      BOOLEAN -- True Enable VT
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN GetPlatformCpuVtEnable(IN VOID *Handle)
{
    SETUP_DATA *SetupData;
    if (Handle == NULL) return FALSE;

    SetupData = ((PRIVATE_CPU_SETUP_LIB*)Handle)->SetupData;
    return (BOOLEAN) SetupData->VT;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	GetPlatformCpuXdEnable
//
// Description:	Get the platform policy of enable XD.
//
// Input:
//      IN VOID *Handle
//
// Output:
//      BOOLEAN -- True Enable XD.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN GetPlatformCpuXdEnable(IN VOID *Handle)
{
    SETUP_DATA *SetupData;
    if (Handle == NULL) return FALSE;	//No Setup

    SetupData = ((PRIVATE_CPU_SETUP_LIB*)Handle)->SetupData;
    return (BOOLEAN) SetupData->XDBit;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	GetPlatformCpuBootRatio
//
// Description:	Get the platform policy of for boot ratio.
//
// Input:
//      IN VOID *Handle
//
// Output:
//      UINT32 Boot Ratio
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT32 GetPlatformCpuBootRatio(IN VOID *Handle)
{
#if CPU_SETUP_SET_BOOT_RATIO == 0
    return 0xffffffff;
#else
    SETUP_DATA *SetupData;
    if (Handle == NULL) return 0xffffffff;

    SetupData = ((PRIVATE_CPU_SETUP_LIB*)Handle)->SetupData;
    return SetupData->CpuSetBootRatio;
#endif
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PeiInitPlatformCpuLib
//
// Description:	Init platform policy in PEI.
//
// Input:
//      IN EFI_PEI_SERVICES **PeiServices
//
// Output:
//      VOID **Handle
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS PeiInitPlatformCpuLib(IN EFI_PEI_SERVICES **PeiServices, OUT VOID **Handle)
{
    EFI_PEI_READ_ONLY_VARIABLE_PPI  *ReadOnlyVariable;
    PRIVATE_CPU_SETUP_LIB   *Private;
    UINTN                   VariableSize;
    EFI_STATUS              Status;

    *Handle = NULL;

    Status = (*PeiServices)->LocatePpi(
        PeiServices,
        &gEfiPeiReadOnlyVariablePpiGuid,
        0, NULL,
        &ReadOnlyVariable       
    );
    if (EFI_ERROR(Status)) return Status;


    Status = (*PeiServices)->AllocatePool(PeiServices,
        sizeof(PRIVATE_CPU_SETUP_LIB),
        &Private
    );
    if (EFI_ERROR(Status)) return Status;

    Status = (*PeiServices)->AllocatePool(PeiServices,
        sizeof(SETUP_DATA),
        &Private->SetupData
    );
    if (EFI_ERROR(Status)) return Status;

    VariableSize = sizeof(SETUP_DATA);
    Status = ReadOnlyVariable->GetVariable(
        PeiServices,
        L"Setup", &gAmiSetupGuid,
        NULL,
        &VariableSize,
        Private->SetupData
    );
    if (EFI_ERROR(Status)) return Status;

    *Handle = (VOID*)Private;

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	DxeInitPlatformCpuLib
//
// Description:	Initialize DXE Init Platform Cpu Lib.
//
// Input:
//  IN EFI_BOOT_SERVICES       *Bs
//  IN EFI_RUNTIME_SERVICES    *Rs
//  OUT VOID                   **Handle
//
// Output:
//  EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS DxeInitPlatformCpuLib(
    IN EFI_BOOT_SERVICES       *Bs,
    IN EFI_RUNTIME_SERVICES    *Rs,
	OUT VOID **Handle
)
{
    UINTN VariableSize = sizeof(SETUP_DATA);
    PRIVATE_CPU_SETUP_LIB   *Private;
    EFI_STATUS              Status;
    UINT32                  CpuSignature = GetCpuSignature() & 0xfffffff0;

    //Only show as supported if all are supported.
    MemSet(&gSetupCpuFeatures, sizeof(gSetupCpuFeatures), 0);     //Initialize features to 0.

    gSetupCpuFeatures.CpuGroup = GetPlatformCpuGroup(NULL);
    if (CpuSignature == SANDY_BRIDGE || CpuSignature == JAKETOWN ||CpuSignature == IVY_BRIDGE) 
        gSetupCpuFeatures.IsSandyBridge = TRUE;

    gSetupCpuFeatures.NumCores = NumCpuCores();

    *Handle = NULL;

    Status = Bs->AllocatePool(EfiBootServicesData, sizeof(PRIVATE_CPU_SETUP_LIB), &Private);
    if (EFI_ERROR(Status)) return Status;

    Status = Bs->AllocatePool(EfiBootServicesData, sizeof(SETUP_DATA), &Private->SetupData);
    if (EFI_ERROR(Status)) return Status;

    VariableSize = sizeof(SETUP_DATA);
    Status = Rs->GetVariable(
        L"Setup",
        &gAmiSetupGuid,
        NULL,
        &VariableSize,
        Private->SetupData
    );
    if (EFI_ERROR(Status)) return Status;

    *Handle = (VOID*)Private;

    return EFI_SUCCESS;
}

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
