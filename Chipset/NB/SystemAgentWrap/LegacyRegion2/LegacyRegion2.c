//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.            **
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
// $Header: /Alaska/BIN/Chipset/Intel/NorthBridge/Haswell/Intel SystemAgent NB Chipset/SystemAgentWrap/LegacyRegion2/LegacyRegion2.c 1     4/05/12 3:08a Yurenlai $
//
// $Date: 4/05/12 3:08a $
//*************************************************************************
// Revision History
// ----------------
// $Log:
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name: LegacyRegion2.c
//
// Description: Legacy Region 2 functions implementation
//
//<AMI_FHDR_END>
//*************************************************************************

#include <efi.h>
#include <AmiDxeLib.h>
#include <AmiCspLib.h>
#include <Protocol\LegacyRegion.h>
#include <Protocol\LegacyRegion2.h>

EFI_LEGACY_REGION_PROTOCOL *gLegacyRegionProtocol = NULL;

//*************************************************************************
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
//*************************************************************************
EFI_STATUS LegacyRegionDecode(
    IN EFI_LEGACY_REGION2_PROTOCOL   *This,
    IN UINT32                       Start,
    IN UINT32                       Length,
    OUT UINT32                      *Granularity,
    IN BOOLEAN                      *On
)
{
    return gLegacyRegionProtocol->Decode( gLegacyRegionProtocol, Start, Length, On);
}

//*************************************************************************
//<AMI_PHDR_START>
//
// Procedure:   LegacyRegionLock
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
//*************************************************************************
EFI_STATUS LegacyRegionLock(
    IN  EFI_LEGACY_REGION2_PROTOCOL *This,
    IN  UINT32                      Start,
    IN  UINT32                      Length,
    OUT UINT32                      *Granularity  OPTIONAL
)
{
    return gLegacyRegionProtocol->Lock( gLegacyRegionProtocol, Start, Length, Granularity);
}

//*************************************************************************
//<AMI_PHDR_START>
//
// Procedure:   LegacyRegionBootLock
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
//*************************************************************************
EFI_STATUS LegacyRegionBootLock(
    IN  EFI_LEGACY_REGION2_PROTOCOL *This,
    IN  UINT32                      Start,
    IN  UINT32                      Length,
    OUT UINT32                      *Granularity  OPTIONAL
)
{
    return gLegacyRegionProtocol->BootLock( gLegacyRegionProtocol, Start, Length, Granularity);
}

//*************************************************************************
//<AMI_PHDR_START>
//
// Procedure:   LegacyRegionUnlock
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
//*************************************************************************
EFI_STATUS LegacyRegionUnlock(
    IN  EFI_LEGACY_REGION2_PROTOCOL *This,
    IN  UINT32                      Start,
    IN  UINT32                      Length,
    OUT UINT32                      *Granularity  OPTIONAL
)
{
    return gLegacyRegionProtocol->UnLock(gLegacyRegionProtocol, Start, Length, Granularity);
}

//*************************************************************************
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
//*************************************************************************
EFI_STATUS GetLegacyRegionInfo(
    IN  EFI_LEGACY_REGION2_PROTOCOL *This,
    OUT UINT32                      *DescriptorCount,
    OUT EFI_LEGACY_REGION_DESCRIPTOR    **Descriptor
)
{
    return EFI_UNSUPPORTED; // Note: to support this function there is a need
                            // to update NB template.
}

EFI_LEGACY_REGION2_PROTOCOL gLegacyRegion2Protocol =
{
    LegacyRegionDecode, LegacyRegionLock,
    LegacyRegionBootLock, LegacyRegionUnlock,
    GetLegacyRegionInfo
};

//*************************************************************************
//<AMI_PHDR_START>
//
// Procedure:   InitializeLegacyRegion2
//
// Description: Install the legacy region 2 protocol.
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
//*************************************************************************
EFI_STATUS InitializeLegacyRegion2(
    IN EFI_HANDLE        ImageHandle,
    IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
    EFI_STATUS  Status;

    InitAmiLib(ImageHandle, SystemTable);

    Status = pBS->LocateProtocol(
            &gEfiLegacyRegionProtocolGuid,
            NULL,
            &gLegacyRegionProtocol);

    if(!EFI_ERROR(Status)) {

       Status = pBS->InstallProtocolInterface (
                     &ImageHandle,
                     &gEfiLegacyRegion2ProtocolGuid,
                     EFI_NATIVE_INTERFACE,
                     &gLegacyRegion2Protocol
                     );
    }

    return Status;

}

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
