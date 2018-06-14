//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.            **
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
// $Header: /Alaska/SOURCE/Modules/PTT/FastBootPei.c 2     11/09/10 8:43a Bibbyyeh $
//
// $Revision: 2 $
//
// $Date: 11/09/10 8:43a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/PTT/FastBootPei.c $
// 
// 2     11/09/10 8:43a Bibbyyeh
// [TAG]  		EIP47280
// [Category]  	New Feature
// [Description]  	Currently, BIOS will copy FV_MAIN or FV_BB into memory
// in DXE phase. If BIOS copy rom before CPU disable flash cache in PEI
// phase. Some data are in cache already, don't need to read from physical
// ROM. It can help to save some time.
// [Files]  		FastBootPei.c
// 
// 1     11/02/10 1:47a Bibbyyeh
// [TAG]  		EIP47280
// [Category]  	New Feature
// [Description]  	Currently, BIOS will copy FV_MAIN or FV_BB into memory
// in DXE phase.
// If BIOS copy rom before CPU disable flash cache in PEI phase.
// Some data are in cache already, don't need to read from physical ROM.
// It can help to save some time.
// [Files]  		FastBootPei.cif
// FastBootPei.mak
// FastBootPei.c
// FastBootPei.dxs
// 
//
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:  FastBootPei.c
//
//  Description:
//  Fast Boot Pei Driver
//
//<AMI_FHDR_END>
//*************************************************************************

//============================================================================
// Includes
//============================================================================

#include <AmiPeiLib.h>
#include <Pei.h>
#include <Token.h>

//============================================================================
// Glocal Variable Declaration
//============================================================================
EFI_GUID gEfiPeiEndOfPeiPhasePpiGuid    = EFI_PEI_END_OF_PEI_PHASE_PPI_GUID;

EFI_STATUS NotifyAtPeiEnd (
    IN EFI_PEI_SERVICES             **PeiServices,
    IN EFI_PEI_NOTIFY_DESCRIPTOR    *NotifyDescriptor,
    IN VOID                         *Ppi
);

EFI_PEI_NOTIFY_DESCRIPTOR FastBootNotifyDescs = {
    EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
    &gEfiPeiEndOfPeiPhasePpiGuid,
    NotifyAtPeiEnd
};


//============================================================================
// Procedure
//============================================================================

VOID CopyRomImageToRam(EFI_PEI_SERVICES **PeiServices) 
{
	EFI_STATUS				Status;
 	VOID *p;
	EFI_HOB_FIRMWARE_VOLUME	*FvHob;
	EFI_PHYSICAL_ADDRESS  	MemoryBuffer;
	EFI_PHYSICAL_ADDRESS	FvHobAddress;
	UINT64					FvHobLength;

	for(  (*PeiServices)->GetHobList(PeiServices,&p)
		; !EFI_ERROR(FindNextHobByType(EFI_HOB_TYPE_FV,&p))
		;
	)
	{
		FvHob = (EFI_HOB_FIRMWARE_VOLUME*)p;
		FvHobAddress = FvHob->BaseAddress;
		FvHobLength = FvHob->Length;

		if ( FvHobAddress == FV_MAIN_BASE || FvHobAddress == FV_BB_BASE) {
            
			// Allocate Memory
			Status = (*PeiServices)->AllocatePages (
										PeiServices,
										EfiBootServicesData,
										EFI_SIZE_TO_PAGES ((UINT32)FvHobLength),
										&MemoryBuffer
									);
			ASSERT_PEI_ERROR (PeiServices, Status);

			// Copy FV HOB from ROM to RAM
	    	(*PeiServices)->CopyMem (
	                      		(VOID*)MemoryBuffer, 
	                      		(VOID*)FvHobAddress,
	                      		(UINTN)FvHobLength
	                      	);

			// Update FV HOB (BaseAddress)
			FvHob->BaseAddress = MemoryBuffer;
		} // end for
	} // end if
}


EFI_STATUS NotifyAtPeiEnd (
    IN EFI_PEI_SERVICES             **PeiServices,
    IN EFI_PEI_NOTIFY_DESCRIPTOR    *NotifyDescriptor,
    IN VOID                         *Ppi
)
{
	EFI_BOOT_MODE	BootMode;
	EFI_STATUS		Status;

    Status = (*PeiServices)->GetBootMode(PeiServices, &BootMode);
    ASSERT_PEI_ERROR(PeiServices, Status);


	if ( (BootMode != BOOT_ON_S3_RESUME) && (BootMode != BOOT_IN_RECOVERY_MODE) ) {
        CopyRomImageToRam(PeiServices);
	}
    return EFI_SUCCESS;
}


EFI_STATUS 
FastBootPeiEntry (
	IN EFI_FFS_FILE_HEADER		*FfsHeader,
	IN EFI_PEI_SERVICES		**PeiServices
  )
{
    (*PeiServices)->NotifyPpi(
        PeiServices,
        &FastBootNotifyDescs
    );
    
    
    return EFI_SUCCESS;
}

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
