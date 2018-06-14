//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2005, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
// $Header: /Alaska/BIN/Chipset/Intel/NorthBridge/Haswell/Intel SystemAgent NB Chipset/LegacyRegion/LegacyRegion.c 1     4/02/13 6:27a Ireneyang $
//
// $Revision: 1 $
//
// $Date: 4/02/13 6:27a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Chipset/Intel/NorthBridge/Haswell/Intel SystemAgent NB Chipset/LegacyRegion/LegacyRegion.c $
// 
// 1     4/02/13 6:27a Ireneyang
// Support CSM Label 80.
// 
// 3     12/25/12 4:41a Abelwu
// Updated for supporting PI 1.x
// 
// 2     12/25/12 3:57a Abelwu
// Update for supporting PI 1.x
// 
// 1     12/25/12 3:03a Abelwu
// Move Legacy Region from CSM to NB eChipset
// 
// 1     12/20/12 12:35p Olegi
// 
// 18    6/16/11 6:30p Olegi
// Added variable that was accidently removed during previous check-in.
// 
// 17    5/27/11 11:46a Olegi
// [TAG]  		EIP56524
// [Category]  	New Feature
// [Description]  	Support for LEGACY_REGION2_PROTOCOL
// [Files]  		LegacyRegion.c, LegacyRegion2.h
// 
// 16    10/14/09 11:21a Krishnakumarg
// CloseEvent funtion used instead of a static variable in callback
// routines - EIP 27065
// 
// 15    6/26/09 11:12a Olegi
// 
// 14    6/26/09 10:00a Olegi
// gPciRootBridgeIo defined as "static". EIP#23538
// 
// 13    4/27/07 5:45p Olegi
// 
// 12    4/27/07 5:42p Olegi
//
// 11    4/27/07 5:21p Olegi
// CSM.CHM preparations.
//
// 10    10/13/06 12:32a Felixp
// UEFI2.0 compliance: use CreateReadyToBootEvent instead of
// CreateEvent(READY_TO_BOOT)
//
// 9     4/24/06 12:47p Olegi
//
// 3     4/24/06 12:43p Olegi
//
// 2     4/18/06 12:11p Olegi
//
// 8     3/31/06 9:43a Olegi
//
// 7     3/31/06 9:06a Olegi
//
// 6     5/27/05 4:24p Markw
// Added Boot Script.
//
// 5     5/06/05 11:27a Yakovlevs
//
// 3     5/06/05 11:02a Yakovlevs
//
// 4     4/19/05 2:42p Sivagarn
// Included pointer to Boot & Runtime Services in PAM programming
//
// 3     4/04/05 4:21p Sivagarn
// Updated to latest template
//
// 2     2/22/05 10:00a Sivagarn
// - Updated to latest labeled CSM & Core
//
// 2     1/18/05 3:22p Felixp
// PrintDebugMessage renamed to Trace
//
// 1     10/26/04 9:48a Olegi
//
//
//**********************************************************************
//<AMI_FHDR_START>
//
// Name: LegacyRegion.c
//
// Description: Legacy Region functions implementation
//
//<AMI_FHDR_END>
//**********************************************************************

#include <efi.h>
#include <Token.h>
#include <AmiDxeLib.h>
#include <AmiCspLib.h>
#include <Protocol\LegacyRegion.h>
#include <Protocol\LegacyRegion2.h>
#include <Protocol\PciRootBridgeIo.h>
#include <Protocol\BootScriptSave.h>
#include <Protocol\cpu.h>

#if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x0001000A)
EFI_GUID gAmiS3SaveProtocolGuid     = EFI_S3_SAVE_STATE_PROTOCOL_GUID;
#else
EFI_GUID gAmiS3SaveProtocolGuid     = EFI_BOOT_SCRIPT_SAVE_GUID;
#endif

EFI_GUID gCpu                           = EFI_CPU_ARCH_PROTOCOL_GUID;

EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *gPciRootBridgeIo;

EFI_EVENT   gEvtBootScript;
EFI_CPU_ARCH_PROTOCOL   Cpu;
EFI_CPU_ARCH_PROTOCOL   *pCpu;

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   CallbackBootScript
//
// Description: Saves the PAM registers to Boot Script
//
// Input:
//      IN EFI_EVENT    Event
//      IN VOID         *Context
// Output:
//      None
//
//<AMI_PHDR_END>
//**********************************************************************
VOID CallbackBootScript(IN EFI_EVENT Event, IN VOID *Context)
{
    EFI_STATUS  Status;
#if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x0001000A)
    EFI_S3_SAVE_STATE_PROTOCOL    *BootScriptSave;
#else
    EFI_BOOT_SCRIPT_SAVE_PROTOCOL *BootScriptSave;
#endif

    Status = pBS->LocateProtocol(
        &gAmiS3SaveProtocolGuid,
        NULL,
        &BootScriptSave
        );
    if (EFI_ERROR(Status)) return;

    NBPAMWriteBootScript(BootScriptSave);

    //
    //Kill the Event
    //
    pBS->CloseEvent(Event);

}


#define LEGACY_REGION_LOCK          0
#define LEGACY_REGION_BOOT_LOCK     1
#define LEGACY_REGION_UNLOCK        2
#define LEGACY_REGION_DECODE_ROM    3

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ProgramPamRegisters
//
// Description: Program 0xc0000 - 0xfffff regions to Lock/Unlock.
//
// Input:       UINT32  StartAddress
//              UINT32  Length
//              UINT8   Setting
//              UINT32  *Granularity
//
// Output:      Status of the operation
//
// Notes:       Here is the control flow of this function:
//              1. Search the structure for the first entry matching
//                  the StartAddress.
//              2. If not found, return EFI_INVALID_PARAMETER.
//              3. Find the last entry in structure for the region to program,
//                  by adding the lengths of the entries.
//              4. If not found, return EFI_INVALID_PARAMETER.
//              5. Read/Write each register for the entry to set region.
//              6. Return the Granularity for the region.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS ProgramPamRegisters(
    UINT32  StartAddress,
    UINT32  Length,
    UINT8   Setting,
    UINT32  *Granularity)
{
    EFI_STATUS      Status;
    UINT64          Attributes;

    Status = NBProgramPAMRegisters (pBS, pRS, StartAddress, Length, Setting, Granularity);
    if (Status != EFI_SUCCESS) return Status;

    Status = CPUProgramPAMRegisters (pBS, pRS, StartAddress, Length, Setting, Granularity);
    if (Status != EFI_SUCCESS) return Status;

//  Program the MTRRs
    switch (Setting) {

        case LEGACY_REGION_LOCK:
            Attributes = EFI_MEMORY_WP;
            break;

        case LEGACY_REGION_BOOT_LOCK:
            Attributes = EFI_MEMORY_WP;
            break;

        case LEGACY_REGION_UNLOCK:
            Attributes = EFI_MEMORY_WT;
            break;

        default:
        Attributes = EFI_MEMORY_UC;

    }

//  Status=DxeSvcTbl->SetMemorySpaceAttributes(StartAddress,Length,Attributes);
    pCpu->SetMemoryAttributes(pCpu, StartAddress, Length, Attributes);

    return Status;
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   Decode
//
// Description: Program chipset to allow decoding of 0xc0000 - 0xfffff.
//
// Input:
//  IN EFI_LEGACY_REGION_PROTOCOL   *This,
//  IN UINT32                       Start,
//  IN UINT32                       Length,
//  IN BOOLEAN                      *On
//
// Output:
//  Status of the operation
//
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS Decode(
    IN EFI_LEGACY_REGION_PROTOCOL   *This,
    IN UINT32                       Start,
    IN UINT32                       Length,
    IN BOOLEAN                      *On
)
{
    UINT32  Granularity;
    if (*On) {
        return ProgramPamRegisters(Start, Length, LEGACY_REGION_UNLOCK, &Granularity);
    } else {
        return ProgramPamRegisters(Start, Length, LEGACY_REGION_DECODE_ROM, &Granularity);
    }
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   LegacyRegionDecode
//
// Description: Program chipset to allow decoding of 0xc0000 - 0xfffff.
//
// Input:
//  IN EFI_LEGACY_REGION_PROTOCOL   *This,
//  IN UINT32                       Start,
//  IN UINT32                       Length,
//  OUT UINT32                      *Granularity,
//  IN BOOLEAN                      *On
//
// Output:
//  Status of the operation
//
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS LegacyRegionDecode(
    IN EFI_LEGACY_REGION2_PROTOCOL   *This,
    IN UINT32                       Start,
    IN UINT32                       Length,
    OUT UINT32                      *Granularity,
    IN BOOLEAN                      *On
)
{
    if (*On) {
        return ProgramPamRegisters(Start, Length, LEGACY_REGION_UNLOCK, Granularity);
    } else {
        return ProgramPamRegisters(Start, Length, LEGACY_REGION_DECODE_ROM, Granularity);
    }
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   Lock
//
// Description: To disallow writes to memory 0xc0000 - 0xfffff.
//
// Input:
//  IN  EFI_LEGACY_REGION_PROTOCOL  *This,
//  IN  UINT32                      Start,
//  IN  UINT32                      Length,
//  OUT UINT32                      *Granularity  OPTIONAL
//
// Output:
//  Status of the operation
//
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS Lock(
    IN  EFI_LEGACY_REGION_PROTOCOL  *This,
    IN  UINT32                      Start,
    IN  UINT32                      Length,
    OUT UINT32                      *Granularity  OPTIONAL
)
{
    return ProgramPamRegisters(Start, Length, LEGACY_REGION_LOCK, Granularity);
}

EFI_STATUS LegacyRegionLock(
    IN  EFI_LEGACY_REGION2_PROTOCOL *This,
    IN  UINT32                      Start,
    IN  UINT32                      Length,
    OUT UINT32                      *Granularity  OPTIONAL
)
{
    return ProgramPamRegisters(Start, Length, LEGACY_REGION_LOCK, Granularity);
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   BootLock
//
// Description: To permanently disallow writes to memory 0xc0000 - 0xffff.
//
// Input:
//  IN  EFI_LEGACY_REGION_PROTOCOL  *This,
//  IN  UINT32                      Start,
//  IN  UINT32                      Length,
//  OUT UINT32                      *Granularity  OPTIONAL
//
// Output:
//  Status of the operation
//
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS BootLock(
    IN  EFI_LEGACY_REGION_PROTOCOL  *This,
    IN  UINT32                      Start,
    IN  UINT32                      Length,
    OUT UINT32                      *Granularity  OPTIONAL
)
{
    //Can't lock Region permanently.
    return ProgramPamRegisters(Start, Length, LEGACY_REGION_BOOT_LOCK, Granularity);
}

EFI_STATUS LegacyRegionBootLock(
    IN  EFI_LEGACY_REGION2_PROTOCOL *This,
    IN  UINT32                      Start,
    IN  UINT32                      Length,
    OUT UINT32                      *Granularity  OPTIONAL
)
{
    return ProgramPamRegisters(Start, Length, LEGACY_REGION_BOOT_LOCK, Granularity);
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   Unlock
//
// Description: To allow read/write of memory 0xc0000-0xfffff.
//
// Input:
//  IN  EFI_LEGACY_REGION_PROTOCOL  *This,
//  IN  UINT32                      Start,
//  IN  UINT32                      Length,
//  OUT UINT32                      *Granularity  OPTIONAL
//
// Output:
//  Status of the operation
//
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS Unlock(
    IN  EFI_LEGACY_REGION_PROTOCOL  *This,
    IN  UINT32                      Start,
    IN  UINT32                      Length,
    OUT UINT32                      *Granularity  OPTIONAL
)
{
    return ProgramPamRegisters(Start, Length, LEGACY_REGION_UNLOCK, Granularity);
}

EFI_STATUS LegacyRegionUnlock(
    IN  EFI_LEGACY_REGION2_PROTOCOL *This,
    IN  UINT32                      Start,
    IN  UINT32                      Length,
    OUT UINT32                      *Granularity  OPTIONAL
)
{
    return ProgramPamRegisters(Start, Length, LEGACY_REGION_UNLOCK, Granularity);
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   GetLegacyRegionInfo
//
// Description:
//  This function is used to discover the granularity of the attributes
//  for the memory in the legacy region. Each attribute may have a different
//  granularity and the granularity may not be the same for all memory ranges
//  in the legacy region.  
//
// Input:
//  IN  EFI_LEGACY_REGION_PROTOCOL    *This
//      --  Indicates the EFI_LEGACY_REGION_PROTOCOL instance.
//
// Output:
//  EFI_UNSUPPORTED - This function is not supported
//  EFI_SUCCESS - The following information structure is returned:
//      OUT UINT32                          *DescriptorCount
//      --  The number of region descriptor entries returned in the Descriptor
//          buffer. See EFI_LEGACY_REGION_DESCRIPTOR definition for reference.
//      OUT EFI_LEGACY_REGION_DESCRIPTOR    **Descriptor
//      --  A pointer to a pointer used to return a buffer where the legacy
//          region information is deposited. This buffer will contain a list
//          of DescriptorCount number of region descriptors. This function will
//          provide the memory for the buffer.
//
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS GetLegacyRegionInfo(
    IN  EFI_LEGACY_REGION2_PROTOCOL *This,
    OUT UINT32                      *DescriptorCount,
    OUT EFI_LEGACY_REGION_DESCRIPTOR    **Descriptor
)
{
    return EFI_UNSUPPORTED; // Note: to support this function there is a need
                            // to update NB template.
}

EFI_LEGACY_REGION_PROTOCOL gLegacyRegionProtocol =
{
    Decode, Lock, BootLock, Unlock
};

EFI_LEGACY_REGION2_PROTOCOL gLegacyRegion2Protocol =
{
    LegacyRegionDecode, LegacyRegionLock,
    LegacyRegionBootLock, LegacyRegionUnlock,
    GetLegacyRegionInfo
};


//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   InitializeLegacyRegion
//
// Description: Install the legacy region protocol.
//
// Input:
//  IN EFI_HANDLE        ImageHandle,
//  IN EFI_SYSTEM_TABLE  *SystemTable
//
// Output:
//  Status of the operation
//
// Notes:
//  Here is the control flow of this function:
//  1. Get root bridge io protocol.
//  2. Install legacy region protocol.
//
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS InitializeLegacyRegion(
    IN EFI_HANDLE        ImageHandle,
    IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
    EFI_STATUS  Status;

    InitAmiLib(ImageHandle, SystemTable);

    pCpu = &Cpu;
    Status = pBS->LocateProtocol(&gCpu, NULL, &pCpu);
    ASSERT_EFI_ERROR(Status);
    if (EFI_ERROR(Status)) return Status;

    Status = pBS->LocateProtocol(
            &gEfiPciRootBridgeIoProtocolGuid,
            NULL,
            &gPciRootBridgeIo);
    ASSERT_EFI_ERROR(Status);

    //Create event for boot script
    Status = CreateReadyToBootEvent(
        TPL_NOTIFY,
        CallbackBootScript,
        NULL,
        &gEvtBootScript
    );
    ASSERT_EFI_ERROR(Status);

    return pBS->InstallMultipleProtocolInterfaces(
        &ImageHandle,
        &gEfiLegacyRegionProtocolGuid, &gLegacyRegionProtocol,
        &gEfiLegacyRegion2ProtocolGuid, &gLegacyRegion2Protocol,
        NULL
        );
}


//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2005, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
