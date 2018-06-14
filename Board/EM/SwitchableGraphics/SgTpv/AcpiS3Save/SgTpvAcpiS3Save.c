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
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/SwitchableGraphics/Sg TPV/Sg Acpi S3 Save/SgTpvAcpiS3Save.c 6     7/16/13 5:04a Joshchou $
//
// $Revision: 6 $
//
// $Date: 7/16/13 5:04a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/SwitchableGraphics/Sg TPV/Sg Acpi S3 Save/SgTpvAcpiS3Save.c $
// 
// 6     7/16/13 5:04a Joshchou
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Save the dGPU ssid to SANV for restore.
// 
// 5     3/21/13 3:39a Joshchou
// 
// 4     1/15/13 5:04a Joshchou
// [TAG]  		EIP107237
// [Category]  	New Feature
// [Description]  	Support SG on ULT platform.
// 
// 3     10/16/12 4:45a Joshchou
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Update for SA and ACPI RC 0.7.1
// [Files]  		SgTpvAcpiS3Save.c
// 
// 2     9/09/12 10:53p Joshchou
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Tpv module support for sharkbay.
// [Files]  		SgTpvAcpiS3Save.mak
// SgTpvAcpiS3Save.c
// SgTpvAcpiS3Save.dxs
// 
// 1     6/27/11 5:27a Alanlin
// [TAG]  		EIP61848
// [Category]  	New Feature
// [Description]  	Initial check-in.Integrated SwitchableGraphics Intel
// Reference code 0.6.0
// [Files]  		SgTpvAcpiS3Save.cif
// SgTpvAcpiS3Save.sdl
// SgTpvAcpiS3Save.mak
// SgTpvAcpiS3Save.c
// SgTpvAcpiS3Save.dxs
// 
// 
// 
//**********************************************************************
//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		SgTpvAcpiS3Save.c
//
// Description:	This file will save SG TPV related offset date for S3 resume restore.
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>
#include <Token.h>
#include <AmiCspLib.h>
#include <AmiDxeLib.h>
#include <Setup.h>
#include <PCI.h>
#include <SaGlobalNvsArea\SaGlobalNvsArea.h>
#include "CpuRegs.h"
//#include "CpuPlatformLib.h"

#include "PchRegsPcie.h"

//----------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//----------------------------------------------------------------------------
// Constant Definition(s)
#define NVIDIA_VID              0x10DE
#define NVOPT_SSID_OFFSET       0x40

#define AMD_SVID_OFFSET         0x4C
#define AMD_SDID_OFFSET         0x4E
#define AMD_VID                 0x1002

// Function Prototype(s)
VOID SgTpvAcpiS3Save (
    IN EFI_EVENT        Event,
    IN VOID             *Context
);

//----------------------------------------------------------------------------
// Variable and External Declaration(s)
//----------------------------------------------------------------------------
// Variable Declaration(s)
EFI_EVENT                       gEvent;
SYSTEM_AGENT_GLOBAL_NVS_AREA_PROTOCOL    *SaGlobalNvsArea;

// GUID Definition(s)
EFI_GUID gEfiPciIoProtocolGuid           = EFI_PCI_IO_PROTOCOL_GUID;
EFI_GUID gSetupGuid                      = SETUP_GUID;
EFI_GUID gSaGlobalNvsAreaProtocolGuid    = SYSTEM_AGENT_GLOBAL_NVS_AREA_PROTOCOL_GUID;
EFI_GUID gEfiBootScriptSaveGuid            = EFI_BOOT_SCRIPT_SAVE_GUID;

CPU_FAMILY            CpuFamilyId;



//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: SgTpvAcpiS3Save_Init
//
// Description: This function is the entry point for this DXE. This function
//              will save SG TPV related offset date for S3 resume restore.
//
// Input:       ImageHandle - Image handle
//              SystemTable - Pointer to the system table
//
// Output:      Return Status based on errors that occurred while waiting for
//              time to expire.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
SgTpvAcpiS3Save_Init (
  IN EFI_HANDLE       ImageHandle,
  IN EFI_SYSTEM_TABLE *SystemTable
  )
{
    EFI_STATUS                    Status;
    UINTN              		      VariableSize = NULL;
    SETUP_DATA      		      *SetupData = NULL;



    InitAmiLib(ImageHandle,SystemTable);

  // Initialize Setup Data 
	Status = GetEfiVariable(
		L"Setup",
		&gSetupGuid,
		NULL,
		&VariableSize,
		&SetupData
	);

   
  // If Select SG mode
  if (SetupData->PrimaryDisplay == 4){

    Status = CreateReadyToBootEvent( TPL_NOTIFY, SgTpvAcpiS3Save, \
                                     NULL, &gEvent );

    ASSERT_EFI_ERROR(Status);

  }

    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SgTpvAcpiS3Save
//
// Description: This callback function is called when ReadyToBoot is
//              installed.
//
// Input:       Event   - Event of callback
//              Context - Context of callback.
//
// Output:      EFI_SUCCESS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID SgTpvAcpiS3Save (
    IN EFI_EVENT        Event,
    IN VOID             *Context )
{

    EFI_STATUS              Status;
    UINT16                  VendorId;
    UINT8                   EndpointBus;
    UINT16                  Data16;
    UINT32                  Data32;
    UINT16                  Count;
    UINTN                   Index;
    UINTN                   VariableSize = NULL;
    UINT32                  RegEax, RegEbx, RegEcx, RegEdx;
    SETUP_DATA      		*SetupData = NULL;
    EFI_BOOT_SCRIPT_SAVE_PROTOCOL   *BootScriptSave;
    UINT8                 RootPortDev;
    UINT8                 RootPortFun;


  TRACE((-1, "==============SgTpvAcpiS3Save==========\n"));
    // Initialize Setup Data 
	Status = GetEfiVariable(
		L"Setup",
		&gSetupGuid,
		NULL,
		&VariableSize,
		&SetupData
	);
    if (EFI_ERROR (Status)) {
      return ;
    }
    //
    //  Locate the SA Global NVS Protocol.
    //
    Status = pBS->LocateProtocol (
                    &gSaGlobalNvsAreaProtocolGuid,
                    NULL,
                    &SaGlobalNvsArea
                    );
    if (EFI_ERROR (Status)) {
      return ;
    }

    Status = pBS->LocateProtocol( \
                    &gEfiBootScriptSaveGuid, \
                    NULL, \
                    &BootScriptSave
                    );
    if (EFI_ERROR (Status)) {
      return ;
    }

   CPULib_CpuID(1, &RegEax, &RegEbx, &RegEcx, &RegEdx);
   CpuFamilyId = (RegEax & CPUID_FULL_FAMILY_MODEL);

   TRACE((-1, "CpuFamilyId = 0x%x\n",CpuFamilyId));
   RootPortDev = 1;
   RootPortFun = 0;
   
    if (CpuFamilyId == EnumCpuHswUlt) {
      /// For SwitchableGraphics support the dGPU is present on PCH RootPort
      RootPortDev = PCI_DEVICE_NUMBER_PCH_PCIE_ROOT_PORTS;
      RootPortFun = SG_ULT_PORT_FUNC;
     }

    //EndpointBus  = READ_PCI8 (0, 1, 0, PCI_SBUS);
    EndpointBus = READ_PCI8 ( 0, RootPortDev, RootPortFun, PCI_SBUS);
    //
    //  Endpoint Device Not found
    //
    if (EndpointBus == 0xFF) { 
       return ;
    }

    VendorId = READ_PCI16 (EndpointBus, 0, 0, PCI_VID); 
    //
    //  if Device Not found or Devide is not AMD and Nvidia VGA device
    //
    if (VendorId == 0xFFFF || ((VendorId != NVIDIA_VID) && (VendorId != AMD_VID))) { 
       return ;
    }


    //
    // Store the Root port Bus assignemnt for S3 resume path
    //

    Data32 = READ_PCI32 (0, RootPortDev, RootPortFun, PCI_PBUS);
    BOOT_SCRIPT_S3_MEM_WRITE_MACRO (
    BootScriptSave, 
    EfiBootScriptWidthUint32, 
    NB_PCIE_CFG_ADDRESS(0, RootPortDev, RootPortFun, PCI_PBUS),
    1,
    &Data32
    );

    Data16 = READ_PCI16 (0, RootPortDev, RootPortFun, PCI_BAR3);
    BOOT_SCRIPT_S3_MEM_WRITE_MACRO (
    BootScriptSave, 
    EfiBootScriptWidthUint16, 
    NB_PCIE_CFG_ADDRESS(0, RootPortDev, RootPortFun, PCI_BAR3),
    1,
    &Data16
    );

    //
    // Store the Generic PCI config space of dGPU for S3 resume path 
    //

    for (Count = 4; Count < 0x40; Count+=4) {
    Data32 = READ_PCI32 (EndpointBus, 0, 0, Count);
    BOOT_SCRIPT_S3_MEM_WRITE_MACRO (
    BootScriptSave, 
    EfiBootScriptWidthUint32, 
    NB_PCIE_CFG_ADDRESS(EndpointBus, 0, 0, Count),
    1,
    &Data32
    );
    } 

  switch(VendorId){
    case NVIDIA_VID:
        //
        // if PEG is NVIDIA and supports Muxless mode
        //
      if (SetupData->SgMuxMode == 2){  


        //
        // Set a unique SSID on the Nv Optimus Graphics
        //
        Data32 = READ_PCI32 (0, 2, 0, PCI_SVID);
        WRITE_PCI32 (EndpointBus, 0, 0, NVOPT_SSID_OFFSET, Data32);

        SaGlobalNvsArea->Area->DgpuSsid = READ_PCI32 (EndpointBus, 0, 0, NVOPT_SSID_OFFSET); // DEBUG
        TRACE((-1, "DgpuSsid in SgTpvAcpiS3Save =0x%X\n", SaGlobalNvsArea->Area->DgpuSsid));

        BOOT_SCRIPT_S3_MEM_WRITE_MACRO (
        BootScriptSave, 
        EfiBootScriptWidthUint32, 
        NB_PCIE_CFG_ADDRESS(EndpointBus, 0, 0, NVOPT_SSID_OFFSET),
        1,
        &Data32
        );

        //
        // Disable Peg Endpoint Function 1 (HDMI Support)
        //
        Data16 = READ_PCI16(EndpointBus, 0, 0, PCI_CMD);
        Data16 = (Data16 & (!(BIT0+BIT1+BIT2)));
        Data16 = (Data16 | (BIT1+BIT2));
        WRITE_PCI16 (EndpointBus, 0, 0, PCI_CMD, Data16);

        Data32 = READ_PCI32 (EndpointBus, 0, 0, PCI_BAR0); // Resd Bar 0 MMIO address
        Data32 += 0x88488;
        Index = (UINT32)Data32;
        *(UINT32*)(Data32) &= ~BIT25;       // Clear Bit 25
        // Keep HDA enabled on cold boots. Optimus Gfx driver shall disable it if not needed
        // or read from CMOS...
        Data32 = ((SaGlobalNvsArea->Area->SgFeatureList & 0x2) << 24); // dGPUAudioCodec bit2
        BOOT_SCRIPT_S3_MEM_WRITE_MACRO (
        BootScriptSave, 
        EfiBootScriptWidthUint32, 
        (UINTN)(Index),  
        1,
        &Data32
        );

      }
    break;
    case AMD_VID:
        //
        // if PEG is AMD
        //
        //
        // Set a unique SSID on the AMD MXM
        //
        Data32 = READ_PCI32 (0, 2, 0, PCI_SVID);
        WRITE_PCI32 (EndpointBus, 0, 0, AMD_SVID_OFFSET, Data32);

        SaGlobalNvsArea->Area->DgpuSsid = READ_PCI32 (EndpointBus, 0, 0, AMD_SVID_OFFSET); // DEBUG
        TRACE((-1, "DgpuSsid in SgTpvAcpiS3Save =0x%X\n", SaGlobalNvsArea->Area->DgpuSsid));

        BOOT_SCRIPT_S3_MEM_WRITE_MACRO (
        BootScriptSave, 
        EfiBootScriptWidthUint32, 
        NB_PCIE_CFG_ADDRESS(EndpointBus, 0, 0, AMD_SVID_OFFSET),
        1,
        &Data32
        );

    break;
    default:
        //
        // either means the Device ID is not on the list of devices we know - we return from this function
    break;
        //
  }

        pBS->CloseEvent(Event); 
}



//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2012 American Megatrends, Inc.          **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**        5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093         **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
