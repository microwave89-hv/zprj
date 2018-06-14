//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**        5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093         **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/SwitchableGraphics/Sg TPV/SgTpvDxe.c 4     5/13/14 4:44a Joshchou $
//
// $Revision: 4 $
//
// $Date: 5/13/14 4:44a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/SwitchableGraphics/Sg TPV/SgTpvDxe.c $
// 
// 4     5/13/14 4:44a Joshchou
// [TAG]  		EIP167034
// [Category]  	Improvement
// [Description]  	Review the variable's attribute.
// 
// 3     1/15/13 5:02a Joshchou
// [TAG]  		EIP107237
// [Category]  	New Feature
// [Description]  	Support SG function on ULT platform.
// 
// 2     9/09/12 11:15p Joshchou
// [TAG]  		EIPNone
// [Category]  	New Feature
// [Description]  	Tpv module support for sharkbay.
// [Files]  		SgTpv.sdl
// SgTpv.mak
// SgTpvPei.c
// SgTpvPei.dxs
// SgTpvDxe.c
// SgTpvDxe.dxs
// SgTpv.cif
// 
// 2     12/06/11 2:15a Alanlin
// [TAG]  		EIP76248
// [Category]  	New Feature
// [Description]  	PX 5.0 feature updated 
// 
// 1     6/27/11 5:25a Alanlin
// [TAG]  		EIP61848
// [Category]  	New Feature
// [Description]  	Initial check-in.Integrated SwitchableGraphics Intel
// Reference code 0.6.0
// [Files]  		SgTpv.cif
// SgTpv.sdl
// SgTpv.mak
// SgTpvPei.c
// SgTpvPei.dxs
// SgTpvDxe.c
// SgTpvDxe.dxs
// 
// 
// 2     9/24/10 5:37p Alexp
//  [TAG]    	  EIP43103 --> fix CPU exception error by checking if
// endpoint bus is enabled in PEG root bridge
// 
// 1     9/17/10 1:12p Alexp
// [TAG]    	  EIP43103 
// [Category]  Function Request
// [Severity]	  Normal
// [Symptom]    Initial check-in of SgTPV module
// [RootCause] Request to implement SG reference code .
// [Solution]	Initial check-in. 
// [Files]	
//         SgTpv.cif;*.sdl;*.mak;
//         SgTpvPei.c;*.dxs;
//         SgTpvDxe.c;*.dxs  
// 
// 2     6/16/10 5:07p Alexp
// 
// 1     6/10/10 4:22p Alexp
// 
// 
//**********************************************************************
//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		SgTpvDXE.c
//
// Description:	This file contains the etry point of SgTpv Support driver
//
// Notes:		MAKE SURE NO PEI OR DXE SPECIFIC CODE IS NEEDED
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>
//
// External include files do NOT need to be explicitly specified in real EDKII
// environment
//
#if !defined(EDK_RELEASE_VERSION) || (EDK_RELEASE_VERSION < 0x00020000)
#include "EdkIIGlueDxe.h"
#include "EfiScriptLib.h"
#endif

#include <Token.h>
#include <SetupDataDefinition.h>
#include "SaAccess.h"

#include "CpuRegs.h"
#include "CpuPlatformLib.h"
#include "PchRegsPcie.h"

#include EFI_PROTOCOL_PRODUCER (SaPlatformPolicy)

#define AMD_VID     0x1002
#define NVIDIA_VID  0x10DE
#define SETUP_GUID { 0xEC87D643, 0xEBA4, 0x4BB5, 0xA1, 0xE5, 0x3F, 0x3E, 0x36, 0xB2, 0x0D, 0xA9 }
SETUP_DATA    SetupDataBuffer;
CPU_FAMILY            CpuFamilyId;

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SgTpvDxeEntryPoint
//
// Description: Entry point of EFI SG Support driver.
//
// Input:       EFI_HANDLE           ImageHandle,
//              EFI_SYSTEM_TABLE     *SystemTable
//
// Output:      EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
SgTpvDxeEntryPoint (
    IN EFI_HANDLE         ImageHandle,
    IN EFI_SYSTEM_TABLE   *SystemTable
)
{
    EFI_STATUS                      Status;
    DXE_PLATFORM_SA_POLICY_PROTOCOL *DxePlatformSaPolicy;
    UINT8                           EndpointBus;
    EFI_GUID                        gSetupGuid = SETUP_GUID; 
    UINTN                           VariableSize = 0;
    UINT8                 RootPortDev;
    UINT8                 RootPortFun;
    UINT32                          Attributes = 0;

    
    EfiInitializeDriverLib (ImageHandle, SystemTable);
    CpuFamilyId = GetCpuFamily();
    //
    // Locate the SG Policy Protocol
    //
    Status = gBS->LocateProtocol (
                  &gDxePlatformSaPolicyGuid,
                  NULL,
                  &DxePlatformSaPolicy
                  );
    if (EFI_ERROR (Status)) {
    return Status;
    }
    
    //
    // Update SG DXE Policy -
    //

    // 1 = Load secondary display device VBIOS; 0 = Do not load
    //
    DxePlatformSaPolicy->VbiosConfig->LoadVbios = LOADVBIOS;
    DxePlatformSaPolicy->VbiosConfig->VbiosSource = VBIOSSOURCE;
    DxePlatformSaPolicy->VbiosConfig->ExecuteVbios = EXECUTEVBIOS;
#if (defined(SGOEMSSDT_SUPPORT) && (SGOEMSSDT_SUPPORT != 0))
    DxePlatformSaPolicy->VbiosConfig->ExecuteVbios = 0;
#endif

    //
    //  Endpoint Base Addresses and Capability Structure Offsets for ASL usage
    //

    if (CpuFamilyId == EnumCpuHswUlt) {
      /// For SwitchableGraphics support the dGPU is present on PCH RootPort
      RootPortDev = PCI_DEVICE_NUMBER_PCH_PCIE_ROOT_PORTS;
      RootPortFun = SG_ULT_PORT_FUNC;
     } else {
      /// Assume: For SwitchableGraphics support the dGPU is present on PEG RootPort by default
      RootPortDev = SA_PEG10_DEV_NUM;
      RootPortFun = SA_PEG10_FUN_NUM;
     }

    //EndpointBus  = McD1PciCfg8 (PCI_SBUS);
    EndpointBus = MmPci8 (0, 0, RootPortDev, RootPortFun, PCI_SBUS);

    if (EndpointBus != 0xff && 
        McDevFunPciCfg16 (EndpointBus, 0, 0, PCI_VID) == NVIDIA_VID) 
    {
        DxePlatformSaPolicy->VbiosConfig->ExecuteVbios = 0;
    }

    VariableSize  = sizeof (SETUP_DATA);
    Status = gRT->GetVariable (
      L"Setup",
      &gSetupGuid,
      &Attributes,
      &VariableSize,
      &SetupDataBuffer
    );
    DEBUG ((EFI_D_ERROR, "SgTpvDxeEntryPoint Attributes = %x\n",Attributes));

  
#if (defined(CSM_SUPPORT) && (CSM_SUPPORT != 0))
 #if defined(CsmOptOut_SUPPORT) && (CsmOptOut_SUPPORT == 1)
    if ((SetupDataBuffer.CsmLaunchPolicy == 0) || (SetupDataBuffer.BootOptionFilter == 2))
        {DxePlatformSaPolicy->VbiosConfig->ExecuteVbios = 0;}
 #endif
#else
        DxePlatformSaPolicy->VbiosConfig->ExecuteVbios = 0;
#endif 
//    if (SetupDataBuffer.PrimaryDisplay == 4)
//    {
      if (EndpointBus != 0xff && 
          McDevFunPciCfg16 (EndpointBus, 0, 0, PCI_VID) == AMD_VID) 
      {
          SetupDataBuffer.TPVCardCheck = 1;
      } else
          SetupDataBuffer.TPVCardCheck = 0;

      Status = gRT->SetVariable (
                              L"Setup",
                              &gSetupGuid,
                              Attributes,
                              sizeof(SETUP_DATA),
                              &SetupDataBuffer
      );
//    } // SetupDataBuffer.PrimaryDisplay == 4

    return Status;
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**        5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093         **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
