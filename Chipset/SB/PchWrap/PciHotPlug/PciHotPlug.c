//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
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
// $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/PchWrap/PciHotPlug/PciHotPlug.c 6     5/16/14 5:56p Barretlin $
//
// $Revision: 6 $
//
// $Date: 5/16/14 5:56p $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/PchWrap/PciHotPlug/PciHotPlug.c $
// 
// 6     5/16/14 5:56p Barretlin
// [TAG]  		EIP165410
// [Category]  	Improvement
// [Description]  	Support Thunderbolt AIC at NB PCIE slot
// [Files]  		PciHotplug.c
// 
// 5     5/14/14 1:15p Barretlin
// [TAG]  		EIP165410
// [Category]  	New Feature
// [Description]  	Support Thunderbolt AIC at NB PCIE slot
// [Files]  		PciHotPlug.c
// 
// 4     4/24/13 5:02a Scottyang
// 
// 3     9/12/12 5:15a Victortu
// [TAG]           None
// [Category]      Improvement
// [Description]   Modify for Thunderbolt support.
// [Files]         GetSetupData.c, SB.sdl, SB.sd, SB.uni, SbSetupData.h,
// PciHotPlug.c
// 
// 2     5/03/12 6:30a Victortu
// [TAG]           None 
// [Category]      Improvement 
// [Description]   Modify to support Thunderbolt. 
// [Files]         SB.sd; SB.uni; SB.sdl; SbSetupData.h; PciHotPlug.c 
// 
// 1     2/08/12 8:37a Yurenlai
// Intel Lynx Point/SB eChipset initially releases.
// 
//*************************************************************************

//
// Statements that include other files
//
#include "PciHotPlug.h"
#include <token.h>

#define PCIE_NUM  (11)

//
// Instantiation of Driver private data.
//
PCIE_HOT_PLUG_DEVICE_PATH mPcieList[PCIE_NUM] = {
  {
    ACPI,
    PCI(0x1C, 0),
    END
  },  // PCI Express 0
  {
    ACPI,
    PCI(0x1C, 1),
    END
  },  // PCI Express 1
  {
    ACPI,
    PCI(0x1C, 2),
    END
  },  // PCI Express 2
  {
    ACPI,
    PCI(0x1C, 3),
    END
  },   // PCI Express 3
  {
    ACPI,
    PCI(0x1C, 4),
    END
  },   // PCI Express 4
  {
    ACPI,
    PCI(0x1C, 5),
    END
  },   // PCI Express 5
  {
    ACPI,
    PCI(0x1C, 6),
    END
  },   // PCI Express 6
  {
    ACPI,
    PCI(0x1C, 7),
    END
  },   // PCI Express 7
  {
    ACPI,
    PCI(0x01, 0),
    END
  },   // NB PCI Express 0
  {
    ACPI,
    PCI(0x01, 1),
    END
  },   // NB PCI Express 1
  {
    ACPI,
    PCI(0x01, 2),
    END
  },   // NB PCI Express 2
};

EFI_HPC_LOCATION          mPcieLocation[PCIE_NUM] = {
  {
    (EFI_DEVICE_PATH_PROTOCOL *) &mPcieList[0],
    (EFI_DEVICE_PATH_PROTOCOL *) &mPcieList[0]
  },
  {
    (EFI_DEVICE_PATH_PROTOCOL *) &mPcieList[1],
    (EFI_DEVICE_PATH_PROTOCOL *) &mPcieList[1]
  },
  {
    (EFI_DEVICE_PATH_PROTOCOL *) &mPcieList[2],
    (EFI_DEVICE_PATH_PROTOCOL *) &mPcieList[2]
  },
  {
    (EFI_DEVICE_PATH_PROTOCOL *) &mPcieList[3],
    (EFI_DEVICE_PATH_PROTOCOL *) &mPcieList[3]
  },
  {
    (EFI_DEVICE_PATH_PROTOCOL *) &mPcieList[4],
    (EFI_DEVICE_PATH_PROTOCOL *) &mPcieList[4]
  },
  {
    (EFI_DEVICE_PATH_PROTOCOL *) &mPcieList[5],
    (EFI_DEVICE_PATH_PROTOCOL *) &mPcieList[5]
  },
  {
    (EFI_DEVICE_PATH_PROTOCOL *) &mPcieList[6],
    (EFI_DEVICE_PATH_PROTOCOL *) &mPcieList[6]
  },
  {
    (EFI_DEVICE_PATH_PROTOCOL *) &mPcieList[7],
    (EFI_DEVICE_PATH_PROTOCOL *) &mPcieList[7]
  },
  {
    (EFI_DEVICE_PATH_PROTOCOL *) &mPcieList[8],
    (EFI_DEVICE_PATH_PROTOCOL *) &mPcieList[8]
  },
  {
    (EFI_DEVICE_PATH_PROTOCOL *) &mPcieList[9],
    (EFI_DEVICE_PATH_PROTOCOL *) &mPcieList[9]
  },
  {
    (EFI_DEVICE_PATH_PROTOCOL *) &mPcieList[10],
    (EFI_DEVICE_PATH_PROTOCOL *) &mPcieList[10]
  },
};

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   PciHotPlug
//
// Description:  This routine reads the PlatformType GPI on FWH and produces a protocol 
//               to be consumed by the chipset driver to effect those settings.
//
// Input:       ImageHandle               An image handle.
//              SystemTable               A pointer to the system table.
//
// Output:      EFI_SUCCESS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
PciHotPlug (
  IN EFI_HANDLE                   ImageHandle,
  IN EFI_SYSTEM_TABLE             *SystemTable
  )
{
  EFI_STATUS            Status;
  PCI_HOT_PLUG_INSTANCE *PciHotPlug;


  PciHotPlug = AllocatePool (sizeof (PCI_HOT_PLUG_INSTANCE));
  ASSERT (PciHotPlug != NULL);

  //
  // Initialize driver private data.
  //
  ZeroMem (PciHotPlug, sizeof (PCI_HOT_PLUG_INSTANCE));

  PciHotPlug->Signature                               = PCI_HOT_PLUG_DRIVER_PRIVATE_SIGNATURE;
  PciHotPlug->HotPlugInitProtocol.GetRootHpcList      = GetRootHpcList;
  PciHotPlug->HotPlugInitProtocol.InitializeRootHpc   = InitializeRootHpc;
  PciHotPlug->HotPlugInitProtocol.GetResourcePadding  = GetResourcePadding;

  Status = gBS->InstallProtocolInterface (
                  &PciHotPlug->Handle,
                  &gEfiPciHotPlugInitProtocolGuid,
                  EFI_NATIVE_INTERFACE,
                  &PciHotPlug->HotPlugInitProtocol
                  );
  ASSERT_EFI_ERROR (Status);

  return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   GetRootHpcList
//
// Description:  This procedure returns a list of Root Hot Plug controllers
//               that require initialization during boot process
//
// Input:        This            The pointer to the instance of the
//                               EFI_PCI_HOT_PLUG_INIT protocol.
//               HpcCount        The number of Root HPCs returned. 
//               HpcList         The list of Root HPCs. HpcCount defines the
//                               number of elements in this list.
//
// Output:      EFI_SUCCESS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
GetRootHpcList (
  IN EFI_PCI_HOT_PLUG_INIT_PROTOCOL    *This,
  OUT UINTN                            *HpcCount,
  OUT EFI_HPC_LOCATION                 **HpcList
  )
{

  *HpcCount = PCIE_NUM;
  *HpcList  = mPcieLocation;

  return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   InitializeRootHpc
//
// Description: This procedure Initializes one Root Hot Plug Controller
//              This process may casue initialization of its subordinate buses
//
// Input:       This            The pointer to the instance of the
//                              EFI_PCI_HOT_PLUG_INIT protocol. 
//              HpcDevicePath   The Device Path to the HPC that is being initialized.
//              HpcPciAddress   The address of the Hot Plug Controller function
//                              on the PCI bus. 
//              Event           The event that should be signaled when the Hot
//                              Plug Controller initialization is complete.
//                              Set to NULL if the caller wants to wait until
//                              the entire initialization process is complete.
//                              The event must be of the type EFI_EVT_SIGNAL.
//              HpcState        The state of the Hot Plug Controller hardware.
//                              The type EFI_Hpc_STATE is defined in section 3.1.
//
// Output:      EFI_SUCCESS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
InitializeRootHpc (
  IN  EFI_PCI_HOT_PLUG_INIT_PROTOCOL      *This,
  IN  EFI_DEVICE_PATH_PROTOCOL            *HpcDevicePath,
  IN  UINT64                              HpcPciAddress,
  IN  EFI_EVENT                           Event, OPTIONAL
  OUT EFI_HPC_STATE                       *HpcState
  )
{
  if (Event) {
    gBS->SignalEvent (Event);
  }

  *HpcState = EFI_HPC_STATE_INITIALIZED;

  return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   GetResourcePadding
//
// Description: Returns the resource padding required by the PCI bus that is
//              controlled by the specified Hot Plug Controller.
//
// Input:       This            The pointer to the instance of the
//                              EFI_PCI_HOT_PLUG_INIT protocol. 
//              HpcDevicePath   The Device Path to the HPC that is being initialized.
//              HpcPciAddress   The address of the Hot Plug Controller function
//                              on the PCI bus. 
//              HpcState        The state of the Hot Plug Controller hardware.
//                              The type EFI_Hpc_STATE is defined in section 3.1.
//              Padding         This is the amount of resource padding required
//                              by the PCI bus under the control of the specified Hpc.
//                              Since the caller does not know the size of this buffer,
//                              this buffer is allocated by the callee and freed by the
//                              caller.
//              Attribute       Describes how padding is accounted for.
//
// Output:      EFI_SUCCESS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
GetResourcePadding (
  IN  EFI_PCI_HOT_PLUG_INIT_PROTOCOL  *This,
  IN  EFI_DEVICE_PATH_PROTOCOL        *HpcDevicePath,
  IN  UINT64                          HpcPciAddress,
  OUT EFI_HPC_STATE                   *HpcState,
  OUT VOID                            **Padding,
  OUT EFI_HPC_PADDING_ATTRIBUTES      *Attributes
  )
{
  EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR *PaddingResource;
  EFI_STATUS                        Status;
  UINT8                             FindRP;
  UINT8                             RsvdExtraBusNum = 0;
                                        // (SB082311A)>
  UINT16                            RsvdPcieMegaMem = 0;
  UINT8                             RsvdPcieKiloIo = 0;
  UINT16                            RsvdPcieMegaPFMem = 0;
  UINT8                             RsvdPcieMegaMemalig = 0; 
  UINT8                             RsvdPcieMegaPFMemalig = 0;
                                        // <(SB082311A)
  UINTN                             VariableSize;
  SETUP_DATA                        SetupData;
  EFI_GUID                          SetupGuid = SETUP_GUID;
  UINT32                            RPFN; //Root Port Function Number
  UINT8                             SwRPFN;

  PaddingResource = AllocatePool (PCIE_NUM * sizeof (EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR) + sizeof (EFI_ACPI_END_TAG_DESCRIPTOR));
  ASSERT (PaddingResource != NULL);

  *Padding = (VOID *) PaddingResource;

  RPFN = MmioRead32(SB_RCRB_BASE_ADDRESS + R_PCH_RCRB_RPFN);
  DEBUG((EFI_D_INFO, "\nRCBA RPFN = %x\n", RPFN));
  //
  // Check if PCIe Root Hob Controller need to reserve bus for docking downstream P2P hotplug
  //
  
  VariableSize = sizeof(SETUP_DATA);
  Status = gRT->GetVariable(L"Setup",
                            &SetupGuid,
                            NULL,
                            &VariableSize,
                            &SetupData);
  
  for (FindRP = 0; FindRP < PCIE_NUM; FindRP ++) {
    if (HpcPciAddress == EFI_PCI_ADDRESS(0, 0x1C, FindRP, 0)) {    
      if (!EFI_ERROR(Status)) {
        switch (FindRP){
            case 0:
                SwRPFN = (UINT8)(RPFN & B_PCH_RCRB_RPFN_RP1FN);
                break;
            case 1:
                SwRPFN = (UINT8)((RPFN & B_PCH_RCRB_RPFN_RP2FN) >> 4);
                break;
            case 2:
                SwRPFN = (UINT8)((RPFN & B_PCH_RCRB_RPFN_RP3FN) >> 8);
                break;
            case 3:
                SwRPFN = (UINT8)((RPFN & B_PCH_RCRB_RPFN_RP4FN) >> 12);
                break;
            case 4:
                SwRPFN = (UINT8)((RPFN & B_PCH_RCRB_RPFN_RP5FN) >> 16);
                break;
            case 5:
                SwRPFN = (UINT8)((RPFN & B_PCH_RCRB_RPFN_RP6FN) >> 20);
                break;
            case 6:
                SwRPFN = (UINT8)((RPFN & B_PCH_RCRB_RPFN_RP7FN) >> 24);
                break;
            case 7:
                SwRPFN = (UINT8)((RPFN & B_PCH_RCRB_RPFN_RP8FN) >> 28);
                break;
            default:
                ASSERT_EFI_ERROR(EFI_DEVICE_ERROR);
        }
        DEBUG((EFI_D_INFO, "FindRP = %x\nSwRPFN = %x\n", FindRP, SwRPFN));
#if (defined SB_SETUP_SUPPORT && SB_SETUP_SUPPORT) || \
    (defined OEM_SB_SETUP_SUPPORT && OEM_SB_SETUP_SUPPORT)
        if (SwRPFN == FindRP) {
           DEBUG((EFI_D_INFO, "PCIE Root Port#%x does not swap...\n", FindRP));
           if (SetupData.PcieRootPortHPE[FindRP]){
                RsvdExtraBusNum = SetupData.ExtraBusRsvd[FindRP];
                RsvdPcieMegaMem = SetupData.PcieMemRsvd[FindRP];
                RsvdPcieMegaPFMem = SetupData.PciePFMemRsvd[FindRP];
                RsvdPcieKiloIo  = SetupData.PcieIoRsvd[FindRP];
                RsvdPcieMegaMemalig = SetupData.PcieMemRsvdalig[FindRP];
                RsvdPcieMegaPFMemalig = SetupData.PciePFMemRsvdalig[FindRP];
           }
        }
        else{
           DEBUG((EFI_D_INFO, "PCIE Root Port#%x is mapping to PCIE slot#%x...\n", FindRP, SwRPFN));
           if (SetupData.PcieRootPortHPE[SwRPFN]){
                RsvdExtraBusNum = SetupData.ExtraBusRsvd[SwRPFN];
                RsvdPcieMegaMem = SetupData.PcieMemRsvd[SwRPFN];
                RsvdPcieMegaPFMem = SetupData.PciePFMemRsvd[SwRPFN];
                RsvdPcieKiloIo  = SetupData.PcieIoRsvd[SwRPFN];
                RsvdPcieMegaMemalig = SetupData.PcieMemRsvdalig[SwRPFN];
                RsvdPcieMegaPFMemalig = SetupData.PciePFMemRsvdalig[SwRPFN];
           }
        }
#endif
      }
      break;
    } // SB PCIE root port
#if defined Thunderbolt_SUPPORT && Thunderbolt_SUPPORT == 1
    if (HpcPciAddress == EFI_PCI_ADDRESS(0, 0x01, (FindRP - 8), 0)) {
        if (!EFI_ERROR(Status)) {
            DEBUG((EFI_D_INFO, "Hotplug root port is NB PCIE root port\n"));
            if ((SetupData.TbtEnable != 0) && (SetupData.TbtHostLocation >= 0x20) && (SetupData.TbtHostLocation < 0x23)){
                DEBUG((EFI_D_INFO, "Update resource for NB PCIE root port\n"));
                RsvdExtraBusNum       = TBT_DEFAULT_EXTRA_BUS_RESERVED;
                RsvdPcieMegaMem       = TBT_DEFAULT_PCIE_MEM_RESERVED;
                RsvdPcieMegaPFMem     = TBT_DEFAULT_PCIE_PF_MEM_RESERVED;
                RsvdPcieKiloIo        = TBT_DEFAULT_PCIE_IO_RESERVED;
                RsvdPcieMegaMemalig   = 26;
                RsvdPcieMegaPFMemalig = 28;
            }
        }
    } // NB PCIE root port
#endif
  } // for loop

  //
  // Padding for bus
  //
  ZeroMem (PaddingResource, PCIE_NUM * sizeof (EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR) + sizeof (EFI_ACPI_END_TAG_DESCRIPTOR));
  *Attributes                   = EfiPaddingPciBus;

  PaddingResource->Desc         = 0x8A;
  PaddingResource->Len          = 0x2B;
  PaddingResource->ResType      = ACPI_ADDRESS_SPACE_TYPE_BUS;
  PaddingResource->GenFlag      = 0x0;
  PaddingResource->SpecificFlag = 0;
  PaddingResource->AddrRangeMin = 0;
  PaddingResource->AddrRangeMax = 0;
  PaddingResource->AddrLen      = RsvdExtraBusNum;

  //
  // Padding for non-prefetchable memory
  //
  PaddingResource++;
  PaddingResource->Desc                 = 0x8A;
  PaddingResource->Len                  = 0x2B;
  PaddingResource->ResType              = ACPI_ADDRESS_SPACE_TYPE_MEM;
  PaddingResource->GenFlag              = 0x0;
  PaddingResource->AddrSpaceGranularity = 32;
  PaddingResource->SpecificFlag         = 0;
  //
  // Pad non-prefetchable
  //
  PaddingResource->AddrRangeMin = 0;
  PaddingResource->AddrLen      = RsvdPcieMegaMem * 0x100000;
  PaddingResource->AddrRangeMax = (1 << RsvdPcieMegaMemalig) - 1;  // 0x3FFFFFF

  //
  // Padding for prefetchable memory
  //
  PaddingResource++;
  PaddingResource->Desc                 = 0x8A;
  PaddingResource->Len                  = 0x2B;
  PaddingResource->ResType              = ACPI_ADDRESS_SPACE_TYPE_MEM;
  PaddingResource->GenFlag              = 0x0;
  PaddingResource->AddrSpaceGranularity = 32;
  PaddingResource->SpecificFlag         = 06;
  //
  // Padding for prefetchable memory
  //
  PaddingResource->AddrRangeMin = 0;
  PaddingResource->AddrLen      = RsvdPcieMegaPFMem * 0x100000;
  //
  // Pad 16 MB of MEM
  //
  PaddingResource->AddrRangeMax = (1 << RsvdPcieMegaPFMemalig) - 1; // 0xfffffff
  //
  // Alignment
  //
  // Padding for I/O
  //
  PaddingResource++;
  PaddingResource->Desc         = 0x8A;
  PaddingResource->Len          = 0x2B;
  PaddingResource->ResType      = ACPI_ADDRESS_SPACE_TYPE_IO;
  PaddingResource->GenFlag      = 0x0;
  PaddingResource->SpecificFlag = 0;
  PaddingResource->AddrRangeMin = 0;
  PaddingResource->AddrLen      = RsvdPcieKiloIo * 0x400;
  //
  // Pad 4K of IO
  //
  PaddingResource->AddrRangeMax = 1;
  //
  // Alignment
  //
  // Terminate the entries.
  //
  PaddingResource++;
  ((EFI_ACPI_END_TAG_DESCRIPTOR *) PaddingResource)->Desc     = ACPI_END_TAG_DESCRIPTOR;
  ((EFI_ACPI_END_TAG_DESCRIPTOR *) PaddingResource)->Checksum = 0x0;

  *HpcState = EFI_HPC_STATE_INITIALIZED | EFI_HPC_STATE_ENABLED;

  return EFI_SUCCESS;
}
//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

