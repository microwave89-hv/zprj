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
// $Header: /Alaska/BIN/Chipset/Intel/NorthBridge/Haswell/Intel SystemAgent NB Chipset/NbPciCSP.c 2     5/13/14 10:41p Dennisliu $
//
// $Revision: 2 $
//
// $Date: 5/13/14 10:41p $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Chipset/Intel/NorthBridge/Haswell/Intel SystemAgent NB Chipset/NbPciCSP.c $
// 
// 2     5/13/14 10:41p Dennisliu
// [TAG]           EIP167027
// [Category]      Improvement
// [Description]   [SharkBay Aptio4]Variable's attribute needs to be
// reviewed by SA component driver
// [Files]         NBDXEBoard.c; IntelSaGopSetup.c; IntelSaGopPolicy.c;
// NBDxe.c; NbPciCSP.c; PciHostBridge.c;
//
// 1     2/08/12 4:34a Yurenlai
// Intel Haswell/NB eChipset initially releases.
//
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:        NbPciCSP.c
//
// Description: Chipset Porting Hooks for PCI Host Bridge Driver.
//
//<AMI_FHDR_END>
//*************************************************************************

#include <Token.h>
#if AMI_ROOT_BRIDGE_SUPPORT == 1
/****** DO NOT WRITE ABOVE THIS LINE *******/

//----------------------------------------------------------------------------
// Include(s)
//----------------------------------------------------------------------------

#include "PciHostBridge.h"
#include <Acpi11.h>
#include <Acpi20.h>
#include <Protocol\AcpiTable.h>
#include <AmiCspLib.h>

//----------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//----------------------------------------------------------------------------
// Constant Definition(s)

#if ACPI_SUPPORT
 #if defined(PI_SPECIFICATION_VERSION) && (PI_SPECIFICATION_VERSION >= 0x00010014)
 #include <Protocol\AcpiSystemDescriptionTable.h>
 #else
 #include <Protocol\AcpiSupport.h>
 #endif
#endif

// Macro Definition(s)

// Type Definition(s)

// Function Prototype(s)

//----------------------------------------------------------------------------
// Variable and External Declaration(s)
//----------------------------------------------------------------------------
// GUID Definition(s)

EFI_GUID gEfiGlobalVariableGuid = EFI_GLOBAL_VARIABLE;

// Variable Declaration(s)

EFI_EVENT       mAcpiEvent;
VOID            *mAcpiReg;
UINTN           mMcfgTblHandle = 0;
CHAR16          gMemoryCeilingVariable[] = L"MemCeil.";

#if (CORE_VERSION <= 4635)
//----------------------------------------------------------------------------
// For HOST AND ROOT BRIDGE Architectural information
// see chapter 12.1.1 PCI Root Bridge I/O Overview of EFI 1.1 spec
//----------------------------------------------------------------------------
//This table will provide information on how many Root Bridges
//particular Host Bridge will produce.
//The table has NB_NUMBER_OF_HOST_BRG entries.
//(Token NB_NUMBER_OF_HOST_BRG is defined in NB.sdl)
//
//For desktop chipset it will be ONE ROOT UNDER ONE HOST.
//
//If system has more than ONE Host Add more Lines
//-----------------------------------------------------------------------------------------------

UINTN   gRbCountTbl[NB_NUMBER_OF_HOST_BRG]={
    1,  //Number of root bridges produced by Host #0
        //Number of root bridges produced by Host #1
        //Number of root bridges produced by Host #2
        //Number of root bridges produced by Host #3
};

//-----------------------------------------------------------------------------------------------
// This is the table to provide each host allocation attributes
// The table has NB_NUMBER_OF_HOST_BRG entries.
// (Token NB_NUMBER_OF_HOST_BRG is defined in NB.sdl)
// Accepted values are:
//  EFI_PCI_HOST_BRIDGE_COMBINE_MEM_PMEM
//  EFI_PCI_HOST_BRIDGE_MEM64_DECODE
// These values can be ORed.
// The values are defined and explained in
// PCI Host Bridge Resource Allocation Protocol Specification V 0.9
//-----------------------------------------------------------------------------------------------

UINT64 gHbAllocAttribTbl[NB_NUMBER_OF_HOST_BRG]={
    0,  //Allocation Attributes of Host #0
        //Allocation Attributes of Host #1
        //Allocation Attributes of Host #2
        //Allocation Attributes of Host #3
        // And so on
};

//-----------------------------------------------------------------------------------------------
// This table will provide PCI Buses Decoding Information
// in form of ACPI QWORD resource descriptor.
// The only valid fields are:
//   ResourceType,  _MIN, _LEN.
//   Maximum Bus may be calculated as: _MAX=_MIN+_LEN -1
//
// If system has more then one root bridge, add more lines
//
// Desktop chipset is simple chipset with only one root bridge
// which decodes all bus ranges from 0 to 0xFF
//
// See definition of QWORD ACPI Resource Descriptor in ACPI 2.0 Spec
// and "Address Space Resource Descriptor Internal definitions" in AcpiRes.h
// Number of table entries depends on values ported in gRbCountTbl
//-----------------------------------------------------------------------------------------------

//  Name,  Len, Resource Type,  Flags   ,_GRA,  _MIN,   _MAX,   _TRA,  _LEN
ASLR_QWORD_ASD  gRbBusesTbl[] = {
// for Root 0 at Host 0
    {0x8a, 0x2b,ASLRV_SPC_TYPE_BUS, 0, 0, 0x1,  0x00,   0xff,   0,     0x100}
// for Root 1 at Host 0 if any

// for Root 0 at Host 1 if any
};

//-----------------------------------------------------------------------------------------------
// This is the table for the Capabilities Supported by ROOT BRIDGE
// See EFI 1.1 spec for meaning of the Capabilities bits
//
// if system has more than one root bridge add more lines
// Number of table entries depends on values ported in gRbCountTbl
//-----------------------------------------------------------------------------------------------

UINT64  gRbSupportsTbl[] = {
//for Root 0 at Host 0
    (EFI_PCI_ATTRIBUTE_IDE_PRIMARY_IO | EFI_PCI_ATTRIBUTE_IDE_SECONDARY_IO| \
     EFI_PCI_ATTRIBUTE_ISA_IO | EFI_PCI_ATTRIBUTE_VGA_PALETTE_IO  | \
     EFI_PCI_ATTRIBUTE_VGA_MEMORY | EFI_PCI_ATTRIBUTE_VGA_IO | \
     EFI_PCI_ATTRIBUTE_ISA_MOTHERBOARD_IO),
//for Root 1 at Host 0 if any

//for Root 0 at Host 1 if any

// and so on...
};
#endif

// Protocol Definition(s)

// External Declaration(s)

// Function Definition(s)

//----------------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   HbCspGetPciSegment
//
// Description: This procedure returns PCI segment number for chipsets which
//              capable of decoding multiple PCI segments.
//
// Input:       HostBridgeNumber - Host Bridge Number (0 Based)
//              RootBridgeNumber - Root Bridge Number (0 Based)
//
// Output:      UINTN - PCI Segment Number (0 Based)
//
// Notes:       Porting required if needed.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINTN HbCspGetPciSegment (
    IN UINTN        HostBridgeNumber,
    IN UINTN        RootBridgeNumber )
{

    // Usually even server chipsets decodes only one PCI segment
    // but if  chipsets has more than one SEGMENT we have to specify
    // which HOST/ROOT(s) pare will have SEG=0; SEG=1 and so on...

    return 0; // this is for Single Host chipset

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   HbNotifyCspBeforeEnumeration
//
// Description: This procedure will be invoked in PCI Host Bridge Protocol
//              when NotifyPhase function is called with phase
//              EfiPciHostBridgeBeginEnumeration.
//
// Input:       ResAllocProtocol   - Pointer to Host Bridge Resource
//                                   Allocation Protocol.
//              RbIoProtocolBuffer - Pointer to Root Bridge I/O Protocol.
//              RbCount            - Root Bridge counter.
//
// Output:      EFI_STATUS
//
// Notes:       Porting required if needed.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS HbNotifyCspBeforeEnumeration (
    IN EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL *ResAllocProtocol,
    IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL                  **RbIoProtocolBuffer,
    IN UINTN                                            RbCount )
{
    EFI_STATUS  Status = EFI_SUCCESS;

    // Any Additional Variables goes here

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   HbNotifyCspBeginBusAllocation
//
// Description: This procedure will be invoked in PCI Host Bridge Protocol
//              when NotifyPhase function is called with phase
//              EfiPciHostBridgeBeginBusAllocation.
//
// Input:       ResAllocProtocol   - Pointer to Host Bridge Resource
//                                   Allocation Protocol.
//              RbIoProtocolBuffer - Pointer to Root Bridge I/O Protocol.
//              RbCount            - Root Bridge counter.
//
// Output:      EFI_STATUS
//
// Notes:       Porting required if needed.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS HbNotifyCspBeginBusAllocation (
    IN EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL *ResAllocProtocol,
    IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL                   **RbIoProtocolBuffer,
    IN UINTN                                             RbCount )
{
    EFI_STATUS  Status = EFI_SUCCESS;

    // Any Additional Variables goes here

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   HbNotifyCspEndBusAllocation
//
// Description: This procedure will be invoked in PCI Host Bridge Protocol
//              when NotifyPhase function is called with phase
//              EfiPciHostBridgeEndBusAllocation
//
// Input:       ResAllocProtocol   - Pointer to Host Bridge Resource
//                                   Allocation Protocol.
//              RbIoProtocolBuffer - Pointer to Root Bridge I/O Protocol.
//              RbCount            - Root Bridge counter.
//
// Output:      EFI_STATUS
//
// Notes:       Porting required if needed.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS HbNotifyCspEndBusAllocation (
    IN EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL *ResAllocProtocol,
    IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL                  **RbIoProtocolBuffer,
    IN UINTN                                            RbCount )
{
    EFI_STATUS  Status = EFI_SUCCESS;

    // Any Additional Variables goes here

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   HbNotifyCspBeginResourceAllocation
//
// Description: This procedure will be invoked in PCI Host Bridge Protocol
//              when NotifyPhase function is called with phase
//              EfiPciHostBridgeBeginResourceAllocation.
//
// Input:       ResAllocProtocol   - Pointer to Host Bridge Resource
//                                   Allocation Protocol.
//              RbIoProtocolBuffer - Pointer to Root Bridge I/O Protocol.
//              RbCount            - Root Bridge counter.
//
// Output:      EFI_STATUS
//
// Notes:       Porting required if needed.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS HbNotifyCspBeginResourceAllocation (
    IN EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL *ResAllocProtocol,
    IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL                  **RbIoProtocolBuffer,
    IN UINTN                                            RbCount )
{
    EFI_STATUS  Status = EFI_SUCCESS;

    // Any Additional Variables goes here

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   HbNotifyCspAllocateResources
//
// Description: This procedure will be invoked in PCI Host Bridge Protocol
//              when NotifyPhase function is called with phase
//              EfiPciHostBridgeAllocateResources.
//
// Input:       ResAllocProtocol   - Pointer to Host Bridge Resource
//                                   Allocation Protocol.
//              RbIoProtocolBuffer - Pointer to Root Bridge I/O Protocol.
//              RbCount            - Root Bridge counter.
//
// Output:      EFI_STATUS
//
// Notes:       Porting required if needed.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS HbNotifyCspAllocateResources (
    IN EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL *ResAllocProtocol,
    IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL                  **RbIoProtocolBuffer,
    IN UINTN                                            RbCount )
{
    EFI_STATUS  Status = EFI_SUCCESS;

    // Any Additional Variables goes here

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   HbNotifyCspSetResources
//
// Description: This procedure will be invoked in PCI Host Bridge Protocol
//              when NotifyPhase function is called with phase
//              EfiPciHostBridgeSetResources.
//
// Input:       ResAllocProtocol   - Pointer to Host Bridge Resource
//                                   Allocation Protocol.
//              RbIoProtocolBuffer - Pointer to Root Bridge I/O Protocol.
//              RbCount            - Root Bridge counter.
//
// Output:      EFI_STATUS
//
// Notes:       Porting required if needed.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS HbNotifyCspSetResources (
    IN EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL *ResAllocProtocol,
    IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL                  **RbIoProtocolBuffer,
    IN UINTN                                            RbCount )
{
    EFI_STATUS  Status = EFI_SUCCESS;

    // Any Additional Variables goes here

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   HbNotifyCspEndResourceAllocation
//
// Description: This procedure will be invoked in PCI Host Bridge Protocol
//              when NotifyPhase function is called with phase
//              EfiPciHostBridgeEndResourceAllocation
//
// Input:       ResAllocProtocol   - Pointer to Host Bridge Resource
//                                   Allocation Protocol.
//              RbIoProtocolBuffer - Pointer to Root Bridge I/O Protocol.
//              RbCount            - Root Bridge counter.
//
// Output:      EFI_STATUS
//
// Notes:       Porting required if needed.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS HbNotifyCspEndResourceAllocation (
    IN EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL *ResAllocProtocol,
    IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL                  **RbIoProtocolBuffer,
    IN UINTN                                            RbCount )
{
    EFI_STATUS  Status = EFI_SUCCESS;

    // Any Additional Variables goes here

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   HbCspStartBusEnumeration
//
// Description: This procedure will be invoked in PCI Host Bridge Protocol
//              StartBusEnumeration function, it must prepare initial Bus
//              ACPI Resource
//
// Input:       HostBrgData  - Pointer to Host Bridge private structure data.
//              RootBrgData  - Pointer to Root Bridge private structure data.
//              RootBrgIndex - Root Bridge index (0 Based).
//
// Output:      EFI_STATUS
//
// Notes:       Porting required if needed.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS HbCspStartBusEnumeration (
    IN PCI_HOST_BRG_DATA    *HostBrgData,
    IN PCI_ROOT_BRG_DATA    *RootBrgData,
    IN UINTN                RootBrgIndex )
{
    EFI_STATUS  Status = EFI_SUCCESS;
#if (CORE_COMBINED_VERSION <= 0x4027B) // 4.6.3.5

    ASLR_QWORD_ASD  *br;        // Bus Resource Descriptor

    br = Malloc(sizeof(ASLR_QWORD_ASD));
    ASSERT(br);
    if(!br) return EFI_OUT_OF_RESOURCES;

    // Fill out Bus Resource Requirements
    MemCpy(br, &gRbBusesTbl[RootBrgIndex], sizeof(ASLR_QWORD_ASD));
    Status = AppendItemLst((T_ITEM_LIST*)&RootBrgData->ResInitCnt, br);
    ASSERT_EFI_ERROR(Status);
#endif

    // Any Additional Variables goes here

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   HbCspSetBusNnumbers
//
// Description: This procedure will be invoked in PCI Host Bridge Protocol
//              SubmitBusNumbers function.
//
// Input:       HostBrgData  - Pointer to Host Bridge private structure data.
//              RootBrgData  - Pointer to Root Bridge private structure data.
//              RootBrgIndex - Root Bridge index (0 Based).
//
// Output:      EFI_STATUS
//
// Notes:       Porting required if needed.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS HbCspSetBusNnumbers (
    IN PCI_HOST_BRG_DATA    *HostBrgData,
    IN PCI_ROOT_BRG_DATA    *RootBrgData,
    IN UINTN                RootBrgIndex )
{
    EFI_STATUS  Status = EFI_SUCCESS;

    // Any Additional Variables goes here

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   HbCspSubmitResources
//
// Description: This procedure will be invoked in PCI Host Bridge Protocol
//              SubmitResources function.
//
// Input:       HostBrgData  - Pointer to Host Bridge private structure data.
//              RootBrgData  - Pointer to Root Bridge private structure data.
//              RootBrgIndex - Root Bridge index (0 Based).
//
// Output:      EFI_STATUS
//
// Notes:       Porting required if needed.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS HbCspSubmitResources (
    IN PCI_HOST_BRG_DATA    *HostBrgData,
    IN PCI_ROOT_BRG_DATA    *RootBrgData,
    IN UINTN                RootBrgIndex )
{
    EFI_STATUS  Status = EFI_SUCCESS;

    // Any Additional Variables goes here

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   HbCspAdjustMemoryMmioOverlap
//
// Description: This procedure will be invoked during PCI bus enumeration,
//              it determines the PCI memory base address below 4GB whether
//              it is overlapping the main memory, if it is overlapped, then
//              updates MemoryCeiling variable and reboot.
//
// Input:       HostBrgData  - Pointer to Host Bridge private structure data.
//              RootBrgData  - Pointer to Root Bridge private structure data.
//              RootBrgIndex - Root Bridge index (0 Based).
//
// Output:      EFI_STATUS
//
// Notes:       Porting required if needed.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS HbCspAdjustMemoryMmioOverlap (
    IN PCI_HOST_BRG_DATA    *HostBrgData,
    IN PCI_ROOT_BRG_DATA    *RootBrgData,
    IN UINTN                RootBrgIndex )
{
    EFI_STATUS  Status;

    EFI_GCD_MEMORY_SPACE_DESCRIPTOR *MemorySpaceMap;
    UINTN                           NumberOfDescriptors;
    ASLR_QWORD_ASD                  *Res;
    UINTN                           i;
    EFI_PHYSICAL_ADDRESS            Highest4GMem    = 0;
    EFI_PHYSICAL_ADDRESS            LowestMMIO      = 0xffffffff;
    EFI_PHYSICAL_ADDRESS            LowestAllocMMIO = 0xffffffff;
    UINTN                           MemoryCeiling = 0; // Init to 0
    UINTN                           NewMemoryCeiling = 0xffffffff;
    UINTN                           DataSize = sizeof(UINT32);
    UINT32                          Attributes; // [ EIP167027 ]
#if (CORE_VERSION >= 4600)
    DXE_SERVICES                    *DxeSvc;

//------------------------------------
    Status = LibGetDxeSvcTbl( &DxeSvc );
    ASSERT_EFI_ERROR(Status)
    if(EFI_ERROR(Status)) return Status;
#else
    ASSERT(gDxeSvcTbl);
#endif
        return EFI_SUCCESS;
    //pRS->GetVariable ( gMemoryCeilingVariable, \  // [ EIP167027 ]
    //                   &gEfiGlobalVariableGuid, \
    //                   NULL, \
    //                   &DataSize, \
    //                   &MemoryCeiling );
    pRS->GetVariable ( gMemoryCeilingVariable, \
                       &gEfiGlobalVariableGuid, \
                       &Attributes, \
                       &DataSize, \
                       &MemoryCeiling );
    if (EFI_ERROR(Status))
        Attributes = EFI_VARIABLE_NON_VOLATILE + EFI_VARIABLE_BOOTSERVICE_ACCESS;

    // Memory sizing uses memory ceiling to set top of memory.


#if (CORE_VERSION >= 4600)
    Status = DxeSvc->GetMemorySpaceMap( &NumberOfDescriptors, \
                                        &MemorySpaceMap );
#else
    Status = gDxeSvcTbl->GetMemorySpaceMap( &NumberOfDescriptors, \
                                            &MemorySpaceMap );
#endif
    ASSERT_EFI_ERROR(Status)

    // Find the lowest MMIO and lowest allocated MMIO in GCD.
    for (i = 0; i < NumberOfDescriptors; ++i) {
        EFI_GCD_MEMORY_SPACE_DESCRIPTOR *Descr = &MemorySpaceMap[i];
        EFI_PHYSICAL_ADDRESS Base = Descr->BaseAddress;

        // Find highest system below 4GB memory.
        // Treat any non MMIO as system memory. Not all system memory is
        // reported as system memory, such as SMM.

        if (Descr->GcdMemoryType != EfiGcdMemoryTypeMemoryMappedIo && \
                                                        Base < LowestMMIO) {
            EFI_PHYSICAL_ADDRESS EndMem = Base + Descr->Length - 1;
            if (EndMem > Highest4GMem && EndMem <= 0xffffffff)
                Highest4GMem = EndMem;

        // Find Lowest mmio above system memory.
        } else if (Descr->GcdMemoryType == EfiGcdMemoryTypeMemoryMappedIo) {
            if (Base >= 0x100000) {
                if (Base < LowestMMIO) LowestMMIO = Base;

                // If ImageHandle, then MMIO is allocated.
                if ((Base < LowestAllocMMIO) && Descr->ImageHandle)
                    LowestAllocMMIO = Base;
            }
        }
    }

    pBS->FreePool(MemorySpaceMap);

    if (Highest4GMem + 1 != LowestMMIO) {
        TRACE( (-1, "PciHostCSHooks: ") );
        TRACE( (-1, "System Memory and MMIO are not consequitive.\n") );
        TRACE( (-1, "Top of Below 4G Memory: %lX", Highest4GMem) );
        TRACE( (-1, "Bottom of MMIO: %X\n", LowestMMIO) );
    }


    // Find any MMIO that could not be allocated due to small of MMIO region.
    for (i = 0; i < RootBrgData->ResCount; ++i) {
        EFI_PHYSICAL_ADDRESS NeededBottomMmio;

        Res = RootBrgData->RbRes[i];

        // Any unallocated MMIO will have Res->_MIN set to zero for the MMIO
        // type.
        if (Res->Type != ASLRV_SPC_TYPE_MEM || Res->_GRA != 32 || Res->_MIN)
            continue;

        // Determine new memory ceiling variable needed to allocate this
        // memory.
        NeededBottomMmio = LowestAllocMMIO - Res->_LEN;

        // Round down. If resource is not allocated, _MAX contains
        // granularity.
        NeededBottomMmio &= ~Res->_MAX;
        if (NeededBottomMmio < NewMemoryCeiling)
            NewMemoryCeiling = (UINTN) NeededBottomMmio;
    }

    // Check if a NewMemory Ceiling is needed.
    if (NewMemoryCeiling < 0xffffffff) {
        if (!MemoryCeiling || MemoryCeiling != NewMemoryCeiling ) {

            // Set memory ceiling variable.
            //pRS->SetVariable( gMemoryCeilingVariable, \   // [ EIP167027 ]
            //                  &gEfiGlobalVariableGuid, \
            //                  EFI_VARIABLE_NON_VOLATILE + \
            //                  EFI_VARIABLE_BOOTSERVICE_ACCESS + \
            //                  EFI_VARIABLE_RUNTIME_ACCESS,
            //                  sizeof (UINT32), \
            //                  &NewMemoryCeiling );
            pRS->SetVariable( gMemoryCeilingVariable, \
                              &gEfiGlobalVariableGuid, \
                              Attributes,
                              sizeof (UINT32), \
                              &NewMemoryCeiling );

            TRACE((-1, "Adjusting maximum top of RAM.\n Resetting System.\n"));

        // Reset only needed of type of physical memory overlaps with MMIO.

#if (NV_SIMULATION != 1)
            // Don't reset system in case of NVRAM simulation
            pRS->ResetSystem (EfiResetCold, EFI_SUCCESS, 0, NULL);
#endif
        // Control should not come here if NV_SIMULATION = 0.
        }
        return EFI_SUCCESS;
    }

    // Check to see if Ceiling needs to be increased. If too low,
    // then part of the memory be not be usuable.
    if (MemoryCeiling != LowestAllocMMIO) {

        // Set memory ceiling variable.
        //pRS->SetVariable( gMemoryCeilingVariable, \   // [ EIP167027 ]
        //                  &gEfiGlobalVariableGuid, \
        //                  EFI_VARIABLE_NON_VOLATILE + \
        //                  EFI_VARIABLE_BOOTSERVICE_ACCESS + \
        //                  EFI_VARIABLE_RUNTIME_ACCESS,
        //                  sizeof (UINT32), \
        //                  &LowestAllocMMIO );
        pRS->SetVariable( gMemoryCeilingVariable, \
                          &gEfiGlobalVariableGuid, \
                          Attributes,
                          sizeof (UINT32), \
                          &LowestAllocMMIO );

        TRACE((-1, "Adjusting maximum top of RAM.\n Resetting System.\n"));

#if (NV_SIMULATION != 1)
        // Don't reset system in case of NVRAM simulation
        pRS->ResetSystem (EfiResetCold, EFI_SUCCESS, 0, NULL);
#endif
        // Control should not come here if NV_SIMULATION = 0.
    }

        return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   HbCspPreprocessController
//
// Description: This function is called for all the PCI controllers that
//              the PCI bus driver finds.
//              It can be used to Preprogram the controller.
//
// Input:       HostBrgData   - Pointer to Host Bridge private structure data.
//              RootBrgData   - Pointer to Root Bridge private structure data.
//              RootBrgNumber - Root Bridge number (0 Based).
//              PciAddress    - Address of the controller on the PCI bus.
//              Phase         - The phase during enumeration
//
// Output:      EFI_STATUS
//
// Notes:       Porting required if needed.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS HbCspPreprocessController (
    IN PCI_HOST_BRG_DATA                            *HostBrgData,
    IN PCI_ROOT_BRG_DATA                            *RootBrgData,
    IN UINTN                                        RootBrgNumber,
    IN EFI_PCI_CONFIGURATION_ADDRESS                PciAddress,
    IN EFI_PCI_CONTROLLER_RESOURCE_ALLOCATION_PHASE Phase )
{
    EFI_STATUS  Status = EFI_SUCCESS;

    // Any Additional Variables goes here

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   HbCspMapRootBrgToHost
//
// Description: Chipset specific function that returns Host Bridge Number for
//              the corresponded Root Bridge.
//
// Input:       RootBrgXlatHdr - Pointer to Root Bridge XLAT table entry.
//              AllocationAttr - Pointer to allocation attribute.
//              RbSuportedAttr - Pointer to Root Bridge supported attribute.
//
// Output:      UINTN - Number of the Host Bridge that root bridge
//                      identified by  RootBrgXlatHdr belongs to.
//
// Note:        THIS FUNCTION MUST BE PORTED FOR MULTI-HOST SYSTEMS
//                  HOST bridge handle supports:
//                      - ResourceAllocation Protocol (REQUIRED);
//                      - RootHotplugControllerInitialization
//                        Protocol (OPTIONAL);
//                      - PciPlatform Protocol (OPTIONAL).
//                  ROOT bridge handle supports:
//                      - PciRootBridgeIo Protocol (REQUIRED).
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINTN HbCspMapRootBrgToHost (
#if (PCIBUS_VERSION > 020102)
    IN PCI_BUS_XLAT_HDR     *RootBrgXlatHdr,
    IN UINT64               *AllocationAttr,
    IN UINT64               *RbSuportedAttr )
#else
    IN PCI_BUS_XLAT_HDR     *RootBrgXlatHdr )
#endif
{
    // Usually even server chipsets use only one PCI HOST abstraction
    // but if  chipset has more than one HOST we have to specify
    // which ROOT from PciBusXlat table belongs to which HOST.

    // Check if we need to update/change Allocation Attributes Passed to
    // this function.
    // Here we have ability to override Automaticaly generated Attributes
    // based on SDL tokens COMBINE_MEM_PMEM and ABOVE_4G_PCI_DECODE
    // bits currently defined for Allocation Attributes is:
    //    EFI_PCI_HOST_BRIDGE_COMBINE_MEM_PMEM
    //    EFI_PCI_HOST_BRIDGE_MEM64_DECODE
    // Usually nothing needs to be done sor SINGLE HOST-SINGLE-ROOT systems
    // NOTE: this function could be called more than one time for each HOST
    // if you updating AllocationAttr only last data will be valid.
    // PCI HostBridge Driver sets DEFAULT allocation attributes.
    // Add code only if you need to overwrite it.

    // if i.e. second root does not support PF_MMIO
    // if(RootBrgXlatHdr->BusBuild == 0x80 ) \
    //            *AllocationAttr &= ~(EFI_PCI_HOST_BRIDGE_COMBINE_MEM_PMEM);
    // else *RbSuportedAttr = ....;

    // Check that in VeB PCI Wizard this Root creates bus 0
    // This is usualy a compatibility bus
    // Set the Compatibility bus Attributes it must decode Legacy resources

    // PCI HostBridge Driver sets DEFAULT Supported ROOT BRIDGE Attributes.
    // Add code only if you need to overwrite it.

    // if (RootBrgXlatHdr->BusBuild == 0) *RbSuportedAttr= \
    //                                 (EFI_PCI_ATTRIBUTE_IDE_PRIMARY_IO | \
    //                                  EFI_PCI_ATTRIBUTE_IDE_SECONDARY_IO | \
    //                                  EFI_PCI_ATTRIBUTE_ISA_IO | \
    //                                  EFI_PCI_ATTRIBUTE_VGA_PALETTE_IO | \
    //                                  EFI_PCI_ATTRIBUTE_VGA_MEMORY | \
    //                                  EFI_PCI_ATTRIBUTE_VGA_IO | \
    //                                  EFI_PCI_ATTRIBUTE_ISA_MOTHERBOARD_IO);
    // else *RbSuportedAttr = 0;

    // Returning Host Number for Root Bridge corresponded to the Root
    // ported as RootBrgXlatHdr->BusBuild from BusXLat Table
    // for single SINGLEHOST-SINGLE-ROOT system this value always 0

    // If your system MULTY-HOST/MULTY-ROOTs system
    // you need to add code here to correctly map each ROOT referenced in
    // VeB wizard to it's corresponded host

    return 0;
}

#if (PCIBUS_VERSION > 020102)

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   HbCspAllocateResources
//
// Description: This function is invoked in PCI Host Bridge Driver when time
//              to ask GCD for resources. You can overwrite a default
//              algorithm used to allocate resources for the Root Bridge.
//
// Input:       HostBrgData  - Pointer to Host Bridge private structure data.
//              RootBrgData  - Pointer to Root Bridge private structure data.
//              RootBrgIndex - Root Bridge index (0 Based).
//
// Output:      EFI_STATUS
//
// Notes:       Porting required if needed.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS HbCspAllocateResources (
    IN PCI_HOST_BRG_DATA    *HostBrgData,
    IN PCI_ROOT_BRG_DATA    *RootBrgData,
    IN UINTN                RootBrgIndex )
{
    EFI_STATUS  Status = EFI_UNSUPPORTED;

    return Status;
}
#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   HbCspBasicChipsetInit
//
// Description: This function will be invoked after Initialization of generic
//              part of the Host and Root Bridges.
//              All Handles for PCIHostBrg and PciRootBrg has been created
//              and Protocol Intergaces installed.
//
// Input:       HostBrgData  - Pointer to Host Bridge private structure data.
//
// Output:      EFI_STATUS
//
// Notes:       Porting required if needed.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS HbCspBasicChipsetInit (
    IN PCI_HOST_BRG_DATA    *HostBrg0 )
{

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   RbCspIoPciMap
//
// Description: Chipset Specific function to Map Internal Device address
//              residing ABOVE 4G to the BELOW 4G address space for DMA.
//              MUST BE IMPLEMENTED if CHIPSET supports address space
//              decoding ABOVE 4G.
//
// Input:       *RbData        - Root Bridge private structure data
//              Operation      - Operation to provide Mapping for
//              HostAddress    - HostAddress of the Device
//              *NumberOfBytes - Number of Byte in Mapped Buffer.
//              *DeviceAddress - Mapped Device Address.
//              **Mapping      - Mapping Info Structure this function must
//                               allocate and fill.
//
// Output:      EFI_STATUS
//                  EFI_SUCCESS - Successful.
//                  EFI_UNSUPPORTED - The Map function is not supported.
//                  EFI_INVALID_PARAMETER - One of the parameters has an
//                                          invalid value.
//
// Notes:       Porting is required for chipsets that supports Decoding
//              of the PCI Address Space ABOVE 4G.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS RbCspIoPciMap (
    IN PCI_ROOT_BRG_DATA                            *RbData,
    IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_OPERATION    Operation,
    IN EFI_PHYSICAL_ADDRESS                         HostAddress,
    IN OUT UINTN                                    *NumberOfBytes,
    OUT EFI_PHYSICAL_ADDRESS                        *DeviceAddress,
    OUT VOID                                        **Mapping )
{

    EFI_STATUS  Status = EFI_SUCCESS;

    // Any Additional Variables goes here

    *Mapping = NULL;
    Status = EFI_UNSUPPORTED;

    // For Chipsets which DOES support decoding of the PCI resources ABOVE 4G.
    // here must be something like that.

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   RbCspIoPciUnmap
//
// Description: Chipset Specific function to Unmap previousely Mapped
//              buffer for DMA.
//              MUST BE IMPLEMENTED if CHIPSET supports address space
//              decoding ABOVE 4G.
//
// Input:       *RbData  - Root Bridge private structure data
//              *Mapping - Mapping Info Structure this function must free.
//
// Output:      EFI_STATUS
//                  EFI_SUCCESS - Successful.
//                  EFI_UNSUPPORTED - The Unmap function is not supported.
//                  EFI_INVALID_PARAMETER - One of the parameters has an
//                                          invalid value.
//
// Notes:       Porting required if needed.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS RbCspIoPciUnmap (
    IN PCI_ROOT_BRG_DATA                            *RbData,
    OUT PCI_ROOT_BRIDGE_MAPPING                     *Mapping )
{
    EFI_STATUS  Status = EFI_SUCCESS;

    // Any Additional Variables goes here


    if (Mapping != NULL) return EFI_INVALID_PARAMETER;
    // for all other conditions we would return EFI_UNSUPPORTED.
    Status = EFI_UNSUPPORTED;

    // for Chipsets which DOES support decoding of the PCI resources ABOVE 4G.
    // And provides corresponded mapping for the host address
    // here must be something like that.

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   RbCspIoPciAttributes
//
// Description: Chipset Specific function to do PCI RB Attributes releated
//              programming.
//
// Input:       RbData         - Pointer to Root Bridge private structure.
//              Attributes     - The Root Bridge attributes to be programming.
//              ResourceBase   - Pointer to the resource base. (OPTIONAL)
//              ResourceLength - Pointer to the resource Length. (OPTIONAL)
//
// Output:      EFI_STATUS
//                  EFI_SUCCESS - Successful.
//                  EFI_INVALID_PARAMETER - One of the parameters has an
//                                          invalid value.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS RbCspIoPciAttributes (
    IN PCI_ROOT_BRG_DATA                            *RbData,
    IN UINT64                                       Attributes,
    IN OUT UINT64                                   *ResourceBase OPTIONAL,
    IN OUT UINT64                                   *ResourceLength OPTIONAL )
{


    EFI_STATUS  Status = EFI_SUCCESS;

    // Any Additional Variables goes here

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   RootBridgeIoPciRW
//
// Description: Read Pci Registers into buffer.
//              Csp Function which actualy access PCI Config Space.
//              Chipsets that capable of having PCI EXPRESS Ext Cfg Space
//              transactions.
//              Must Implement this access routine here.
//
// Input:       *RbData - Root Bridge private structure.
//              Width   - PCI Width.
//              Address - PCI Address.
//              Count   - Number of width reads/writes.
//              *Buffer - Buffer where read/written.
//              Write   - Set if write.
//
// Output:      EFI_STATUS
//                  EFI_SUCCESS - Successful read.
//                  EFI_INVALID_PARAMETER - One of the parameters has an
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS RootBridgeIoPciRW (
    IN PCI_ROOT_BRG_DATA                        *RbData,
    IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH    Width,
    IN UINT64                                   Address,
    IN UINTN                                    Count,
    IN OUT VOID                                 *Buffer,
    IN BOOLEAN                                  Write )
{
    BOOLEAN ValidCfg = TRUE;
    UINT8   IncrementValue = 1 << (Width & 3); // 1st 2 bits currently define
                                               // width.
                                               // Other bits define type.

    UINTN  PciAddress = PCIEX_BASE_ADDRESS + \
        (((EFI_PCI_CONFIGURATION_ADDRESS*) &Address)->Bus << 20 ) + \
        (((EFI_PCI_CONFIGURATION_ADDRESS*) &Address)->Device << 15 ) + \
        (((EFI_PCI_CONFIGURATION_ADDRESS*) &Address)->Function << 12 );

    PciAddress += \
        ((EFI_PCI_CONFIGURATION_ADDRESS*) &Address)->ExtendedRegister ? \
            ((EFI_PCI_CONFIGURATION_ADDRESS*) &Address)->ExtendedRegister : \
            ((EFI_PCI_CONFIGURATION_ADDRESS*) &Address)->Register;

    // To read 64bit values, reduce Increment Value (by half) and
    // double the count value (by twice)
    if (IncrementValue > 4) {
        IncrementValue >>= 1;
        Count <<= 1;
    }

    if (Width >= EfiPciWidthMaximum || IncrementValue > 4)
        return EFI_INVALID_PARAMETER;

    while (Count--) {
        if (PciAddress >= (PCIEX_BASE_ADDRESS + PCIEX_LENGTH)) \
                                                             ValidCfg = FALSE;
        if (Write) {
            switch(IncrementValue) {
                case 1:
                    if (ValidCfg) *(UINT8*)PciAddress = *(UINT8*)Buffer;
                    break;
                case 2:
                    if (ValidCfg) *(UINT16*)PciAddress = *(UINT16*)Buffer;
                    break;
                default:
                    if (ValidCfg) *(UINT32*)PciAddress = *(UINT32*)Buffer;
                    break;
            }
        } else {
            switch(IncrementValue) {
                case 1:
                    *(UINT8*)Buffer = (ValidCfg) ? *(UINT8*)PciAddress : -1;
                    break;
                case 2:
                    *(UINT16*)Buffer = (ValidCfg) ? *(UINT16*)PciAddress : -1;
                    break;
                default:
                    *(UINT32*)Buffer = (ValidCfg) ? *(UINT32*)PciAddress : -1;
                    break;
            }
        }

        if (Width <= EfiPciWidthFifoUint64) {
             Buffer = ((UINT8 *)Buffer + IncrementValue);
            // Buffer is increased for only EfiPciWidthUintxx and
            // EfiPciWidthFifoUintxx
        }

        // Only increment the PCI address if Width is not a FIFO.
        if ((Width & 4) == 0) {
            PciAddress += IncrementValue;
        }
    }

    return EFI_SUCCESS;
}

/****** DO NOT WRITE BELOW THIS LINE *******/
#endif  //#if AMI_ROOT_BRIDGE_SUPPORT == 1

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
