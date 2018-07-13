#include <EFI.h>
#include <Token.h>
#include <AmiDxeLib.h>
#include <Protocol\LegacyRegion.h>

//----------------------------------------------------------------------------
// Description: InstallSecurityString
//----------------------------------------------------------------------------
EFI_STATUS InstallSecurityString()
{
    EFI_GUID 			gEfiLegacyRegionProtocol = EFI_LEGACY_REGION_PROTOCOL_GUID;
    EFI_LEGACY_REGION_PROTOCOL	*LegacyRegionProtocol;
    UINTN      			NumberOfHandles;
    EFI_HANDLE 			*HandleBuffer;
    EFI_STATUS              	Status;

    CHAR8  SIGNATURE_STR1[] = {0x22, 0x34, 0x03, 0x98, "AAEON Technology Inc."};
    CHAR8  SIGNATURE_STR2[] = CONVERT_TO_STRING(SIGNATURE_MODEL_TAG);

    //F0000-F1000 unlock
    Status = pBS->LocateHandleBuffer ( ByProtocol, &gEfiLegacyRegionProtocol, NULL, &NumberOfHandles,  &HandleBuffer );
    Status = pBS->HandleProtocol ( HandleBuffer[0], &gEfiLegacyRegionProtocol, &LegacyRegionProtocol);
    pBS->FreePool(HandleBuffer);
    Status = LegacyRegionProtocol->UnLock(LegacyRegionProtocol, 0xF0000, 0x10000, NULL);

//    pBS->CopyMem((VOID*)(SIGNATURE_ADDRESS1), SIGNATURE_STR1, sizeof (SIGNATURE_STR1) );
    pBS->CopyMem((VOID*)(SIGNATURE_ADDRESS2), SIGNATURE_STR2, sizeof (SIGNATURE_STR2) );

    Status = LegacyRegionProtocol->Lock(LegacyRegionProtocol, 0xF0000, 0x10000, NULL);

    return Status;
}

//----------------------------------------------------------------------------
// Description: AAEONSecurityEntryPoint
//----------------------------------------------------------------------------
EFI_STATUS AAEONSecurityEntryPoint(
	IN EFI_HANDLE		ImageHandle,
	IN EFI_SYSTEM_TABLE	*SystemTable
)
{
    InitAmiLib(ImageHandle, SystemTable);

    return InstallSecurityString();
}
