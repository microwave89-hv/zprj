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
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/Platform/EfiCombineImage/EfiCombineImage.c 1     12/18/12 11:10p Alanlin $
//
// $Revision: 1 $
//
// $Date: 12/18/12 11:10p $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/Platform/EfiCombineImage/EfiCombineImage.c $
// 
// 1     12/18/12 11:10p Alanlin
// 
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:
//
// Description:
//
//<AMI_FHDR_END>
//*************************************************************************

// Include(s)

#include "Efi.h"
#include "token.h"
#include <AmiLib.h>
#include <AmiCspLib.h>
#include <AmiDxeLib.h>
#include <Pci.h>
#include <Setup.h>
#include <Protocol\PciIo.h>

// Constant Definition(s)

// Macro Definition(s)

// Type Definition(s)

// Function Prototype(s)


// Variable Declaration(s)

// GUID Definition(s)
#if (PI_SPECIFICATION_VERSION < 0x00010000)    
EFI_GUID gFvProtocolGuid = EFI_FIRMWARE_VOLUME_PROTOCOL_GUID;
#else
EFI_GUID gFvProtocolGuid = EFI_FIRMWARE_VOLUME2_PROTOCOL_GUID;
#endif

#if NVidia_Optimus_dGPU == 1
EFI_GUID gEfiCombineImageGuid = NVidia_dGPU_HEADER_GUID;
#endif
#if AMD_PX_CHELSEA_dGPU == 1
EFI_GUID gEfiCombineImageGuid1 = AMD_CHELSEA_HEADER_GUID;
#endif
#if AMD_PX_THAMES_dGPU == 1
EFI_GUID gEfiCombineImageGuid2 = AMD_THAMES_HEADER_GUID;
#endif

// Protocol Definition(s)

// External Declaration(s)

// Function Definition(s)


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:        GetEfiCombineImage
//
// Description: None.
//
// Input:       None.
//
// Output:      None.
//
// Notes:       None.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS GetEfiCombineImage (
    IN  PCI_DEV_INFO    *Device,
    OUT VOID            *RomImage,
    OUT UINT64          RomSize
)
{
    EFI_STATUS                      Status;
    UINTN                           FvProtocolCount;
    EFI_HANDLE                      *FvHandles = NULL;
#if (PI_SPECIFICATION_VERSION < 0x00010000)
    EFI_FIRMWARE_VOLUME_PROTOCOL    *Fv;
#else
    EFI_FIRMWARE_VOLUME2_PROTOCOL   *Fv;
#endif
    UINTN                           Index;
    UINT32                          AuthenticationStatus;
    UINT8                           *Buffer = NULL;
    UINTN                           BufferSize;

    Status = pBS->LocateHandleBuffer (
                  ByProtocol,
                  &gFvProtocolGuid,
                  NULL,
                  &FvProtocolCount,
                  &FvHandles
                  );
    if (!EFI_ERROR (Status)) {
        for (Index = 0; Index < FvProtocolCount; Index++) {
            Status = pBS->HandleProtocol (
                          FvHandles[Index],
                          &gFvProtocolGuid,
                          (VOID **) &Fv
                          );
            if (!EFI_ERROR (Status)) {

	      switch (Device->DevVenId.DevId) 
	      {
#if NVidia_Optimus_dGPU == 1
		case NVidia_dGPU_DID :	
		Status = Fv->ReadSection(
			Fv,&gEfiCombineImageGuid,
			EFI_SECTION_RAW,0,
			&Buffer,&BufferSize,
			&AuthenticationStatus
		);
		  break;
#endif

#if AMD_PX_CHELSEA_dGPU == 1
		case AMD_CHELSEA_DID :	
		Status = Fv->ReadSection(
			Fv,&gEfiCombineImageGuid1,
			EFI_SECTION_RAW,0,
			&Buffer,&BufferSize,
			&AuthenticationStatus
		);
		  break;
#endif

#if AMD_PX_THAMES_dGPU == 1
		case AMD_THAMES_DID :	
		Status = Fv->ReadSection(
			Fv,&gEfiCombineImageGuid2,
			EFI_SECTION_RAW,0,
			&Buffer,&BufferSize,
			&AuthenticationStatus
		);
		  break;
#endif
		default :
		  break;
	      }

                if (!EFI_ERROR (Status)) {
                    if(Device->PciIo.RomImage != NULL) {
                        pBS->FreePool (Device->PciIo.RomImage);
                        Device->PciIo.RomImage = NULL;
                        Device->PciIo.RomSize = 0;
                    }
                    //Check if Embeded Op ROM is valid...
                    if(*((UINT16*)Buffer)!=PCI_OPT_ROM_SIG) Status=EFI_NOT_FOUND;
                    else{
                        //Allocate buffer for ROM Image.
                        Device->PciIo.RomImage = Malloc (BufferSize);
                        if(Device->PciIo.RomImage == NULL) Status = EFI_OUT_OF_RESOURCES;
                        else {
                            MemCpy (Device->PciIo.RomImage, Buffer, BufferSize);
                            Device->PciIo.RomSize = BufferSize;
                            Device->Capab |= (EFI_PCI_IO_ATTRIBUTE_EMBEDDED_DEVICE + EFI_PCI_IO_ATTRIBUTE_EMBEDDED_ROM);
                            Device->Attrib |= (EFI_PCI_IO_ATTRIBUTE_EMBEDDED_DEVICE + EFI_PCI_IO_ATTRIBUTE_EMBEDDED_ROM);
                            Status = EFI_SUCCESS;
                        }
                    }
                    break;
                }
            }
        }
    }
    else {
        Status = EFI_NOT_FOUND;
    }

    if (FvHandles != NULL) {
        pBS->FreePool (FvHandles);
        FvHandles = NULL;
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
