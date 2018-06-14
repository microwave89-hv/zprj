//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
// $Header: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Core/em/Runtime/Flash.c 1     7/31/17 4:54a Chienhsieh $
//
// $Revision: 1 $
//
// $Date: 7/31/17 4:54a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Core/em/Runtime/Flash.c $
// 
// 1     7/31/17 4:54a Chienhsieh
// [TAG]  		EIP344536
// [Description]  	SA40037 - BIOS update failure vulnerability
// [Files]  		Flash.c
// 
// 12    5/24/17 12:30p Felixp
// Bug fixes from Aptio V are back ported to Aptio 4.
// The following issues are addressed:
// Bug fix(EIP 201329)
//   Symptom: FlashDriver_04 did not properly mark out/restore the _FVH
// signature when updating a firmware volume
//   Root Cause: A logic error in the code that was attempting to match
// the requested flash address update prevented
//     the code from removing/adding the _FVH signature from the memory
// buffer.
// Bug fix(EIP 217270)
//   Symptom: _FVH signature was not properly restored during update of
// multiple sequential firmware volumes.
//   Root Cause: UpdatedArea[i].AreaSize was used before it was
// initialized if multiple sequential FV were updated
//     by first erasing the entire flash area occupied by all FV and then
// programming the area.
// Bug fix
//   Symptom: _FVH signature was not properly restored when more than two
// areas were simultaneously updated.
//   Root Cause: Logic error in FlashDriverDeviceWriteDisableExt
// Bug fix in BeforeErase function: the function used wrong value to
// corrupt the FV signature
// Improvement: don't corrupt the signature when area block other than the
// first one is erased.
// The code that deletes/restores the FV signature is updated to restore
// the signature only if it has actually
//   been deleted by a flash driver; the signature is not restored
// otherwise.
// 
// 11    9/12/13 4:24a Rameshr
// [TAG]  		EIP136017
// [Category]  	Improvement
// [Description]  	Buffer Address updated if the partial block write
// happens
// [Files]  		Flash.c
// 
// 10    11/11/11 3:06p Artems
// Security: Copied ROM layout structure to SMM to avoid calls outside SMM
// 
// 9     1/25/11 12:48p Oleksiyy
// [TAG]  		EIP42253
// [Category]  	New Feature
// [Description]  	Added support for platforms, where flash part is not
// memory mapped while write enabled, controlled by
// NO_MMIO_FLASH_ACCESS_DURING_UPDATE sdl token. Flash protocol used to
// access flash in that case.
// [Files]  		NVRAMDXE.c, Flash.c, Tokens.c and Runtime.sdl
// 
// 8     10/07/10 1:40p Felixp
// Debug messages are removed.
// 
// 7     10/07/10 12:07p Felixp
// Bug fix:
// Symptoms: The AFU reported verification error during update of 
//  the FFS-based ROM hole that is the first FFS file in the firmware
// volume(FV).
// Details: The FV signature was not restored.
//  The flash driver logic that destroys and restores the FV signature
// during the 
//  FV update didn't cover the partial update case. 
//  The Flash driver is updated to restore the signature during partial FV
// updates.
//  The signature is now restored:
//  - In case of full FV update, 
//    in the AfterWrite function once the last FV block is updated. 
//  - In case of partial FV update, 
//    in the FlashDriverDeviceWriteDisable function
//  The FlashDriverRead function is updated to return the valid signature
// when 
//  called in the middle of the FV update.
// 
// 6     10/01/10 7:28p Felixp
// Previous changes are rolled back. They break the recovery update.
// 
// 4     9/24/10 8:01a Felixp
// Definition of CRITICAL_SECTION is updated.
// 
// 3     8/25/09 11:46p Felixp
// Bug Fixes:
// 1. Symptoms: AFUDOS was occasionally hanging in debug mode.
//     Details: Debug message funcation Trace, which uses boot time
// services was used at runtime.
// 2. Symptoms: Erase, Write, and Update functions of the Flash Protocol
// did not work without prior call to DeviceWriteEnable protocol function.
//      Details: Nested call to DeviceWriteEnable was failing due to busy
// critical section. Code is updated to use non-blocking internal write
// enable function. 
// 3. Symptoms: DeviceWriteDisable did not work properly.
//      Details: Protocol interface structure was populated with wrong
// function pointer.
// 
// 2     7/09/09 5:29p Oleksiyy
// Files clean-up, headers added
//
// 1     5/21/09 5:12p Felixp
// Flash Driver
//
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:    Flash.c
//
// Description: Flash Driver Implementation
//
//<AMI_FHDR_END>
//**********************************************************************
#include <AmiDxeLib.h>
#include <Flash.h>
#include <Ffs.h>
#include <RomLayout.h>
#include <AmiHobs.h>
#include <Protocol/FlashProtocol.h>

typedef struct
{
    BOOLEAN Busy;
    BOOLEAN SmiState;
    UINT8 IntState[2];
} CRITICAL_SECTION;

typedef struct
{
    ROM_AREA *RomLayout;
    UINT32 WriteEnableStatus;
    CRITICAL_SECTION Cs;
    UINT32 RomLayoutSize;
} FLASH_DRIVER_MAILBOX;

typedef struct
{
    FLASH_PROTOCOL Flash;
    FLASH_DRIVER_MAILBOX *MailBox;
} FLASH_PROTOCOL_PRIVATE;

typedef struct
{
    ROM_AREA *RomArea;
    UINT32 AreaSize ;
    BOOLEAN RestoreSignature;	
} UPDATED_AREA_DESCRIPTOR;

//-----Prototypes------------------------------------
EFI_STATUS EFIAPI FlashDriverRead(
    VOID* FlashAddress, UINTN Size, VOID* DataBuffer
);
EFI_STATUS EFIAPI FlashDriverErase(
    VOID* FlashAddress, UINTN Size
);
EFI_STATUS EFIAPI FlashDriverWrite(
    VOID* FlashAddress, UINTN Size, VOID* DataBuffer
);
EFI_STATUS EFIAPI FlashDriverUpdate(
    VOID* FlashAddress, UINTN Size, VOID* DataBuffer
);
EFI_STATUS EFIAPI FlashDriverDeviceWriteEnable();
EFI_STATUS EFIAPI FlashDriverDeviceWriteDisable();

EFI_STATUS EFIAPI FlashDriverReadExt(
    VOID* FlashAddress, UINTN Size, VOID* DataBuffer
);
EFI_STATUS EFIAPI FlashDriverEraseExt(
    VOID* FlashAddress, UINTN Size
);
EFI_STATUS EFIAPI FlashDriverWriteExt(
    VOID* FlashAddress, UINTN Size, VOID* DataBuffer
);
EFI_STATUS EFIAPI FlashDriverUpdateExt(
    VOID* FlashAddress, UINTN Size, VOID* DataBuffer
);
EFI_STATUS EFIAPI FlashDriverDeviceWriteEnableExt();
EFI_STATUS EFIAPI FlashDriverDeviceWriteDisableExt();

extern const UINTN FlashEmpty;
extern const BOOLEAN FlashNotMemoryMapped;

#define BEGIN_CRITICAL_SECTION(Cs) \
    { if ((Cs)->Busy) return EFI_ACCESS_DENIED;\
      BeginCriticalSection(Cs);\
    }
#define END_CRITICAL_SECTION(Cs) EndCriticalSection(Cs)

VOID BeginCriticalSection(CRITICAL_SECTION *Cs);
VOID EndCriticalSection(CRITICAL_SECTION *Cs);

//---Flash data protocole------------------------------------------
FLASH_PROTOCOL_PRIVATE FlashData =
{
    {
        FlashDriverReadExt, FlashDriverEraseExt, FlashDriverWriteExt, FlashDriverUpdateExt,
        FlashDriverDeviceWriteEnableExt, FlashDriverDeviceWriteDisableExt
    },
    NULL
};

ROM_AREA *RomLayout = NULL;
#define MAX_NUMBER_OF_UPDATED_AREAS 10
UPDATED_AREA_DESCRIPTOR UpdatedArea[MAX_NUMBER_OF_UPDATED_AREAS];
INT32 NumberOfUpdatedAreas=0;

/*************** OUTSIDE SMM **********************************/
// <AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name: FlashDrvVirtAddressChange
//
// Description: Function updates the current pointer to FlashData protocol functions and
//              UpdatedArea pointed to by Address to be the proper value for the new address map
//
// Input:
//  IN EFI_EVENT                Event       Signalled event
//  IN VOID                     *Context    Calling context
//
// Output:      NON
//
//--------------------------------------------------------------------------
// <AMI_PHDR_END>
VOID FlashDrvVirtAddressChange (
    IN EFI_EVENT Event, IN VOID *Context
)
{
    VOID **p;
    INT32 i;
    FlashVirtualFixup(pRS);
    //Fixup protocol member functions
    p=(VOID**)&FlashData.Flash.Write;
    
    do
    {
        pRS->ConvertPointer(0, p++);
    }
    while (p!=(VOID**)&FlashData.Flash.DeviceWriteDisable);
    
    pRS->ConvertPointer(0, &FlashData.MailBox);
    
//    if (RomLayout!=NULL) pRS->ConvertPointer(0, &RomLayout);
    
    for (i=0; i<NumberOfUpdatedAreas; i++)
    {
        pRS->ConvertPointer(0, &UpdatedArea[i].RomArea);
    }
}

// <AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name: FlashDriverInit
//
// Description: Creates necessary structures and instatlls Flash services before SMM mode.
//
// Input:
//  IN EFI_HANDLE               ImageHandle     Image Handle
//  IN EFI_SYSTEM_TABLE         *SystemTable    Pointer to System Table
//
// Output:      EFI_STATUS
//
//--------------------------------------------------------------------------
// <AMI_PHDR_END>

EFI_STATUS FlashDriverInit(
    IN EFI_HANDLE ImageHandle, 
    IN EFI_SYSTEM_TABLE *SystemTable
)
{
    static EFI_GUID HobListGuid = HOB_LIST_GUID;
    static EFI_GUID AmiRomLayoutHobGuid = AMI_ROM_LAYOUT_HOB_GUID;
    EFI_STATUS Status;
    EFI_HANDLE Handler = NULL;
    ROM_LAYOUT_HOB *RomLayoutHob;
    UINTN MailboxSize = sizeof(FLASH_DRIVER_MAILBOX);
    UINTN RomLayoutSize;
    
    InitAmiRuntimeLib(ImageHandle, SystemTable, NULL, FlashDrvVirtAddressChange);

//Create mailbox
    VERIFY_EFI_ERROR(pBS->AllocatePool(EfiRuntimeServicesData, MailboxSize, (VOID **)&FlashData.MailBox));
//Get ROM layout
    RomLayoutHob = GetEfiConfigurationTable(SystemTable, &HobListGuid);
    if (RomLayoutHob != NULL) {
        if (!EFI_ERROR(FindNextHobByGuid(&AmiRomLayoutHobGuid, &RomLayoutHob))) {
            ROM_AREA *Area;
            RomLayoutSize = RomLayoutHob->Header.Header.HobLength - sizeof(ROM_LAYOUT_HOB);
            VERIFY_EFI_ERROR(pBS->AllocatePool(EfiBootServicesData, RomLayoutSize, &RomLayout));
            pBS->CopyMem(RomLayout, RomLayoutHob + 1, RomLayoutSize);   //save ROM Layout for future use

            for (Area = RomLayout; Area->Size != 0; Area++) {   //update address
                Area->Address -= FlashDeviceBase;
            }

            //pass ROM layout to SMM driver
            FlashData.MailBox->RomLayout = RomLayout;
            FlashData.MailBox->RomLayoutSize = (UINT32)RomLayoutSize;
        } else {
            FlashData.MailBox->RomLayout = NULL;
            FlashData.MailBox->RomLayoutSize = 0;
        }
    }

//Fill MailBox 
    FlashData.MailBox->WriteEnableStatus = 0;
    FlashData.MailBox->Cs.Busy = FALSE;
    FlashData.MailBox->Cs.SmiState = FALSE;
    FlashData.MailBox->Cs.IntState[0] = 0;
    FlashData.MailBox->Cs.IntState[1] = 0;

    Status = pBS->InstallProtocolInterface(&Handler, &gFlashProtocolGuid, EFI_NATIVE_INTERFACE, &FlashData.Flash);

    ASSERT_EFI_ERROR(Status);
    return Status;
}

/*************** INSIDE SMM **********************************/
// <AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name: FlashDriverSmmInit
//
// Description: Reinitialize necessary structures and instatlls Flash services in SMM mode.
//
// Input:
//  IN EFI_HANDLE               ImageHandle     Image Handle
//  IN EFI_SYSTEM_TABLE         *SystemTable    Pointer to System Table
//
// Output:      EFI_STATUS
//
//--------------------------------------------------------------------------
// <AMI_PHDR_END>

EFI_STATUS FlashDriverSmmInit(
    IN EFI_HANDLE ImageHandle, 
    IN EFI_SYSTEM_TABLE *SystemTable
)
{
    EFI_STATUS Status;
    EFI_HANDLE Handler = NULL;
    FLASH_PROTOCOL_PRIVATE *NotSmmFlash;

    VERIFY_EFI_ERROR(pBS->LocateProtocol(&gFlashProtocolGuid, NULL, &NotSmmFlash));

//Reasign MailBox
    FlashData.MailBox = NotSmmFlash->MailBox;

//Save SMM copy of ROM layout
    if(FlashData.MailBox->RomLayoutSize != 0) {
        VERIFY_EFI_ERROR(pSmst->SmmAllocatePool(0, FlashData.MailBox->RomLayoutSize, &RomLayout));
        pBS->CopyMem(RomLayout, FlashData.MailBox->RomLayout, FlashData.MailBox->RomLayoutSize);
    }

    Status = pBS->InstallProtocolInterface(&Handler, &gFlashSmmProtocolGuid, EFI_NATIVE_INTERFACE, &FlashData.Flash);
    ASSERT_EFI_ERROR(Status);
    return Status;
}

/*************** INSIDE and OUSIDE SMM ************************/

// <AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name: BeforeErase
//
// Description: Invalidates FV by destroying the signature before erasing flash.
//
// Input:
//  VOID*       FlashAddress    Pointer to address of a flash 
//
// Output:      NON
//
//--------------------------------------------------------------------------
// <AMI_PHDR_END>

VOID BeforeErase(VOID* FlashAddress)
{
    ROM_AREA *Area;
    UINT32 Data;	

    if (   RomLayout == NULL
            || NumberOfUpdatedAreas == MAX_NUMBER_OF_UPDATED_AREAS
       ) return;
    //---For Areas in Rom Layout------------------------------------------   
    for (Area=RomLayout; Area->Size!=0; Area++)
    {
    //---If this is area we are looking for-------------------------------
        if (Area->Address+FlashDeviceBase==(EFI_PHYSICAL_ADDRESS)(UINTN)FlashAddress)
        {
            if (Area->Type!=RomAreaTypeFv) return;

            UpdatedArea[NumberOfUpdatedAreas].AreaSize = Area->Size;
			UpdatedArea[NumberOfUpdatedAreas].RomArea = Area;
			UpdatedArea[NumberOfUpdatedAreas++].RestoreSignature = FALSE;
            // Invalidate FV by destroying the signature
            Data = (UINT32)~FlashEmpty;			
            FlashDriverWrite(
                &((EFI_FIRMWARE_VOLUME_HEADER*)FlashAddress)->Signature,
                sizeof(UINT32),
                &Data
            );
            return;
        }
    }
}

// <AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name: BeforeWrite
//
// Description: Invalidates FV by destroying the signature before writing to flash.
//
// Input:
//  VOID*       FlashAddress    Pointer to address of a flash 
//  UINTN       Size            Size to write
//  VOID*       DataBuffer      Poiner to the Data Buffer
//
// Output:      NON
//
//--------------------------------------------------------------------------
// <AMI_PHDR_END>

VOID BeforeWrite(VOID* FlashAddress, UINTN Size, VOID* DataBuffer)
{
    EFI_FIRMWARE_VOLUME_HEADER* Fv;
    INT32 i;

    for (i=0; i<NumberOfUpdatedAreas; i++)
    {
        //---Invalidate FV by destroying the signature
        //---(alter data being programmed)
        if (  UpdatedArea[i].RomArea->Address+FlashDeviceBase
                ==(EFI_PHYSICAL_ADDRESS)(UINTN)FlashAddress
           )
        {
            Fv = (EFI_FIRMWARE_VOLUME_HEADER*)DataBuffer;
            
            if (   Size < sizeof(EFI_FIRMWARE_VOLUME_HEADER)
                    || Fv->Signature != FV_SIGNATURE
               )   //The data being programmed is not FV, don't do anything
            {
                UpdatedArea[i] = UpdatedArea[NumberOfUpdatedAreas-1];
                NumberOfUpdatedAreas--;
            }
            
            else
            {
                Fv->Signature = (UINT32)FlashEmpty;
                UpdatedArea[i].AreaSize = (UINT32)Fv->FvLength;
				UpdatedArea[i].RestoreSignature = TRUE;
            }
            
            return;
        }
    }
}

// <AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name: AfterWrite
//
// Description: Restores FV signature after writing to flash.
//
// Input:
//  VOID*       FlashAddress    Pointer to address of a flash 
//  UINTN       Size            Size to write
//  VOID*       DataBuffer      Poiner to the Data Buffer
//
// Output:      NON
//
//--------------------------------------------------------------------------
// <AMI_PHDR_END>

VOID AfterWrite(VOID* FlashAddress, UINTN Size, VOID* DataBuffer)
{
    EFI_PHYSICAL_ADDRESS Address;
    EFI_PHYSICAL_ADDRESS AreaAddress;
    INT32 i;
    
    Address = (EFI_PHYSICAL_ADDRESS)(UINTN)FlashAddress;
    for (i=0; i<NumberOfUpdatedAreas; i++)
    {
        AreaAddress = UpdatedArea[i].RomArea->Address+FlashDeviceBase;
        
        if (AreaAddress==Address)
        {
            //Restore original data
            ((EFI_FIRMWARE_VOLUME_HEADER*)DataBuffer)->Signature=FV_SIGNATURE;
        }
        
        if (AreaAddress+UpdatedArea[i].AreaSize==Address+Size)
        {
            UINT32 FvSignature = FV_SIGNATURE;
            //Restore FV signature
            FlashDriverWrite(
                &((EFI_FIRMWARE_VOLUME_HEADER*)AreaAddress)->Signature,
                sizeof(UINT32),
                &FvSignature
            );
            UpdatedArea[i] = UpdatedArea[NumberOfUpdatedAreas-1];
            NumberOfUpdatedAreas--;
        }
    }
}

// <AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name: AfterRead
//
// Description: Hook that is being called after the read operation.
//
// Input:
//  VOID*       FlashAddress    Pointer to address of a flash 
//  UINTN       Size            Size to read
//
// Output:      NON
//
//--------------------------------------------------------------------------
// <AMI_PHDR_END>

VOID AfterRead(VOID* FlashAddress, UINTN Size, VOID* DataBuffer)
{
    INT32 i;

    if (FlashData.MailBox->WriteEnableStatus==0) return;
    // If we are in the middle of flash update 
    // (FlashData.MailBox->WriteEnableStatus is not zero), 
    // it may happen that the FV signature has not been restored yet 
    // (typically happens during partial FV updates).
    // Let's return the proper value. The signature will be restored later.
    for (i=0; i<NumberOfUpdatedAreas; i++)
    {
        EFI_FIRMWARE_VOLUME_HEADER* Fv 
            = (EFI_FIRMWARE_VOLUME_HEADER*)(
                UpdatedArea[i].RomArea->Address+FlashDeviceBase
              );
        if ( Fv == FlashAddress && Size >= EFI_FIELD_OFFSET(EFI_FIRMWARE_VOLUME_HEADER, Attributes))
        {
            ((EFI_FIRMWARE_VOLUME_HEADER*)DataBuffer)->Signature = FV_SIGNATURE;
            return;
        }
    }
}

// Protocl Functions Implementation
// <AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name: FlashDriverRead
//
// Description: Implementation of the Read Function of the Flash protocol
//
// Input:
//  VOID*       FlashAddress    Pointer to address of a flash 
//  UINTN       Size            Size to write
//  VOID*       DataBuffer      Poiner to the Data Buffer to write
//
// Output:      NON
//
//--------------------------------------------------------------------------
// <AMI_PHDR_END>

EFI_STATUS EFIAPI FlashDriverRead(
    VOID* FlashAddress, UINTN Size, VOID* DataBuffer
)
{
    BOOLEAN Status;

    if (FlashData.MailBox->WriteEnableStatus!=0)
    {
        Status = FlashRead(FlashAddress, DataBuffer, (UINT32)Size);
    }
    else
    {
        UINTN i;
        
        for (i=0; i<Size; i++)
            ((UINT8*)DataBuffer)[i] = ((UINT8*)FlashAddress)[i];
            
        Status = TRUE;
    }
    return (Status) ? EFI_SUCCESS : EFI_DEVICE_ERROR;
}

#define INT_SIZE sizeof(INTN)
#define FLASH_EMPTY_BYTE ((UINT8)FlashEmpty)

// <AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name: IsClean
//
// Description: Function to loops through the buffer and check if it's empty
//
// Input:
//  IN UINT8*   Address    Pointer to address to check
//  IN UINTN    Size    Size of data to check
//
// Output:      TRUE or FALSE
//
//--------------------------------------------------------------------------
// <AMI_PHDR_END>

BOOLEAN IsClean(IN UINT8 *Address, IN UINTN Size)
{
    // loops through the buffer and check if it's empty
    if (!( (UINTN)Address & (INT_SIZE-1) ))
    {
        for ( ; Size >= INT_SIZE; Size -= INT_SIZE, Address += INT_SIZE)
        {
            if (FlashNotMemoryMapped)
            {
                UINTN nData=0;	
		        FlashDriverRead (Address, INT_SIZE, &(UINT8)nData );
		        if (nData != FlashEmpty) return FALSE;
            }
            else
                if (*(UINTN*)Address != FlashEmpty) return FALSE;
	    }

    }
    
    // the address may not be INT_SIZE aligned
    // check the remaining part of the buffer
    for ( ; Size > 0; Size--, Address++)
    {
        if (FlashNotMemoryMapped)
        {
            UINT8 nData=0;	
		    FlashDriverRead (Address, 1, &nData );
		    if (nData != FLASH_EMPTY_BYTE) return FALSE;
        }
        else
            if (*Address != FLASH_EMPTY_BYTE) return FALSE;

	}

    return TRUE;
}

// <AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name: FlashDriverErase
//
// Description: Implementation of the Erase Function of the Flash protocol
//
// Input:
//  VOID*       FlashAddress    Pointer to address of a flash to erase 
//  UINTN       Size            Size to erase
//
// Output:      EFI_SUCCESS or EFI_DEVICE_ERROR depending on result
//
//--------------------------------------------------------------------------
// <AMI_PHDR_END>

EFI_STATUS EFIAPI FlashDriverErase(VOID* FlashAddress, UINTN Size)
{
    BOOLEAN Status = TRUE;
    UINT8 *Address = (UINT8*)FlashAddress;
    
    //---Enable write---------------------------------------------
    FlashDriverDeviceWriteEnable();
    
    for (; Status && Size>0; Address+=FlashBlockSize, Size-=FlashBlockSize)
    {
        //--- If block clean already - continue to next-----------
        if (IsClean(Address, FlashBlockSize)) continue;
        //---If not - Erase block---------------------------------
        FlashBlockWriteEnable(Address);
        Status=FlashEraseBlock(Address);
        FlashBlockWriteDisable(Address);
    }
    //---Disable Write-------------------------------------------
    FlashDriverDeviceWriteDisable();
    return (Status) ? EFI_SUCCESS : EFI_DEVICE_ERROR;
}

// <AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name: FlashDriverWrite
//
// Description: Implementation of the Write Function of the Flash protocol
//
// Input:
//  VOID*       FlashAddress    Pointer to address of a flash to write to 
//  UINTN       Size            Size to write
//  VOID*       DataBuffer -    pointer to data to write to the flash part
//
// Output:      EFI_SUCCESS or EFI_DEVICE_ERROR depending on result
//
//--------------------------------------------------------------------------
// <AMI_PHDR_END>

EFI_STATUS EFIAPI FlashDriverWrite(
    VOID* FlashAddress, UINTN Size, VOID* DataBuffer
)
{
    BOOLEAN Status = TRUE;
    UINT8 *Address = (UINT8*)FlashAddress;
    UINT8 *Data = (UINT8*)DataBuffer;
    UINT8 *BlockAddress = (UINT8*)BLOCK(Address); //Align to the block size
    UINTN PartialSize;
    
    FlashDriverDeviceWriteEnable();
    //---If FlashAddress was not the begining of flash----------------
    if (BlockAddress!=Address)
    {
        PartialSize = FlashBlockSize - (Address - BlockAddress);
        
        if (PartialSize > Size) PartialSize = Size;
        //---Write data and update address----------------------------
        FlashBlockWriteEnable(BlockAddress);
        Status=FlashProgram(Address, Data, (UINT32)PartialSize);
        FlashBlockWriteDisable(BlockAddress);
        Address = BlockAddress + FlashBlockSize;
        Size -= PartialSize;
        Data += PartialSize; 
    }
    //---Else Write data and update address----------------------------
    for (; Status && Size>=FlashBlockSize
            ; Address+=FlashBlockSize, Size-=FlashBlockSize, Data+=FlashBlockSize
        )
    {
        FlashBlockWriteEnable(Address);
        Status=FlashProgram(Address, Data, FlashBlockSize);
        FlashBlockWriteDisable(Address);
    }
    //--- If last chunk < FlashBlockSize-------------------------------
    if (Size!=0 && Status)
    {
        FlashBlockWriteEnable(Address);
        Status=FlashProgram(Address, Data, (UINT32)Size);
        FlashBlockWriteDisable(Address);
    }
    
    FlashDriverDeviceWriteDisable();
    return (Status) ? EFI_SUCCESS : EFI_DEVICE_ERROR;
}

// <AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name: FlashDriverUpdate
//
// Description: Implementation of the Update Function of the Flash protocol 
//
// Input:
//  VOID*       FlashAddress    Pointer to address of a flash to update (must be aligned to FlashBlockSize)
//  UINTN       Size            Size to update (must be multiple of FlashBlockSize)
//  VOID*       DataBuffer -    pointer to data to write to the flash part
//
// Output:      EFI_SUCCESS or EFI_DEVICE_ERROR depending on result
//
//--------------------------------------------------------------------------
// <AMI_PHDR_END>

EFI_STATUS EFIAPI FlashDriverUpdate(
    VOID* FlashAddress, UINTN Size, VOID* DataBuffer
)
{
    BOOLEAN Status = TRUE;
    UINT8 *Address = (UINT8*)FlashAddress;
    UINT8 *Data = (UINT8*)DataBuffer;
    
    FlashDriverDeviceWriteEnable();
    
    for (; Status && Size>=FlashBlockSize
            ; Address+=FlashBlockSize, Size-=FlashBlockSize, Data+=FlashBlockSize
        )
    {
        //---Writes a block checking is flash block clean or equal-----------
        Status = FlashWriteBlock(Address, Data);
    }
    
    FlashDriverDeviceWriteDisable();
    return (Status) ? EFI_SUCCESS : EFI_DEVICE_ERROR;
}

// <AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name: FlashDriverDeviceWriteEnable
//
// Description: Enables writes to flash device 
//
// Input:       NON
// 
//
// Output:      EFI_SUCCESS
//
//--------------------------------------------------------------------------
// <AMI_PHDR_END>

EFI_STATUS EFIAPI FlashDriverDeviceWriteEnable()
{
    FlashData.MailBox->WriteEnableStatus++;
    
    if (FlashData.MailBox->WriteEnableStatus==1)
    {
        FlashDeviceWriteEnable();
    }
    
    return EFI_SUCCESS;
}

// <AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name: FlashDriverDeviceWriteDisable
//
// Description: Disables writes to flash device
//
// Input:       NON
// 
//
// Output:      EFI_SUCCESS
//
//--------------------------------------------------------------------------
// <AMI_PHDR_END>

EFI_STATUS EFIAPI FlashDriverDeviceWriteDisable()
{
    if (FlashData.MailBox->WriteEnableStatus!=0)
    {
        FlashData.MailBox->WriteEnableStatus--;
        
        if (FlashData.MailBox->WriteEnableStatus==0)
        {
            FlashDeviceWriteDisable();
        }
    }
    
    return EFI_SUCCESS;
}

EFI_STATUS EFIAPI FlashDriverReadExt(
    VOID* FlashAddress, UINTN Size, VOID* DataBuffer
){
    EFI_STATUS Status;
    BEGIN_CRITICAL_SECTION(&FlashData.MailBox->Cs);
    Status = FlashDriverRead(FlashAddress,Size,DataBuffer);
    AfterRead(FlashAddress, Size, DataBuffer);
    END_CRITICAL_SECTION(&FlashData.MailBox->Cs);
    return Status;
}

EFI_STATUS EFIAPI FlashDriverEraseExt(
    VOID* FlashAddress, UINTN Size
){
    EFI_STATUS Status;

    if (Size==0) return EFI_SUCCESS;
    //---If Addres in not alligned properly or Size is not multiple to FlashBlockSize
    //---Abort----------------------------------
    if ((UINT8*)BLOCK(FlashAddress)!=FlashAddress || Size%FlashBlockSize!=0)
        return EFI_UNSUPPORTED;

    BEGIN_CRITICAL_SECTION(&FlashData.MailBox->Cs);
    //---Invalidate FV by destroying the signature----------------
    BeforeErase(FlashAddress);
    Status = FlashDriverErase(FlashAddress, Size);
    END_CRITICAL_SECTION(&FlashData.MailBox->Cs);
    return Status;
}

EFI_STATUS EFIAPI FlashDriverWriteExt(
    VOID* FlashAddress, UINTN Size, VOID* DataBuffer
){
    EFI_STATUS Status;
    if (Size==0) return EFI_SUCCESS;

    BEGIN_CRITICAL_SECTION(&FlashData.MailBox->Cs);
    //---Invalidate FV by destroying the signature--------------------
    BeforeWrite(FlashAddress, Size, DataBuffer);
    Status = FlashDriverWrite(FlashAddress,Size,DataBuffer);
    //---Restore FV signature-------------------------------------------
    AfterWrite(FlashAddress, Size, DataBuffer);
    END_CRITICAL_SECTION(&FlashData.MailBox->Cs);
    return Status;
}

EFI_STATUS EFIAPI FlashDriverUpdateExt(
    VOID* FlashAddress, UINTN Size, VOID* DataBuffer
){
    EFI_STATUS Status;

    if (Size==0) return EFI_SUCCESS;
    
    if ((UINT8*)BLOCK(FlashAddress)!=FlashAddress || Size%FlashBlockSize!=0)
        return EFI_UNSUPPORTED;

    BEGIN_CRITICAL_SECTION(&FlashData.MailBox->Cs);
    BeforeErase(FlashAddress);
    BeforeWrite(FlashAddress, Size, DataBuffer);
    Status = FlashDriverUpdate(FlashAddress,Size,DataBuffer);
    AfterWrite(FlashAddress, Size, DataBuffer);
    END_CRITICAL_SECTION(&FlashData.MailBox->Cs);
    return Status;
}

EFI_STATUS EFIAPI FlashDriverDeviceWriteEnableExt(){
    EFI_STATUS Status;
    BEGIN_CRITICAL_SECTION(&FlashData.MailBox->Cs);
    Status = FlashDriverDeviceWriteEnable();
    END_CRITICAL_SECTION(&FlashData.MailBox->Cs);
    return Status;
}

EFI_STATUS EFIAPI FlashDriverDeviceWriteDisableExt(){
    EFI_STATUS Status;
    UINT32 OldWriteEnableStatus;

    BEGIN_CRITICAL_SECTION(&FlashData.MailBox->Cs);
    OldWriteEnableStatus = FlashData.MailBox->WriteEnableStatus;
    Status = FlashDriverDeviceWriteDisable();
    if (OldWriteEnableStatus!=0 && FlashData.MailBox->WriteEnableStatus==0)
    {
        // Before disabling the flash wtrites
        // restore the destroyed FV signatures (if any).
        // In case of full FV update, the FV signature is restored 
        // in the AfterWrite function once the last FV block is updated. 
        // In case of partial FV update when last FV block is not updated, 
        // the FV Signature is restored either here or in the BeforeRead function.
        INT32 i;
        for (i=0; i<NumberOfUpdatedAreas; i++)
        {
			if (UpdatedArea[i].RestoreSignature){
                EFI_FIRMWARE_VOLUME_HEADER* Fv 
                    = (EFI_FIRMWARE_VOLUME_HEADER*)(
                        UpdatedArea[i].RomArea->Address+FlashDeviceBase
                      );
                UINT32 FvSignature = FV_SIGNATURE;
                //Restore FV signature
                FlashDriverWrite(
                    &Fv->Signature, sizeof(UINT32), &FvSignature
                );
			}
        }
		NumberOfUpdatedAreas = 0;
        FlashDeviceWriteDisable();
    }

    END_CRITICAL_SECTION(&FlashData.MailBox->Cs);
    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   FlashDriverEntry
//
// Description: This function is the entry point for this module. This function
//              installs Flash protocols before and after SMM.
//
// Input:       ImageHandle Image handle
//              SystemTable Pointer to the system table
//
// Output:      Return Status based on errors that occurred while waiting for
//              time to expire.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS FlashDriverEntry(
    IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable
)
{
    InitAmiLib(ImageHandle,SystemTable);
    return InitSmmHandlerEx(
               ImageHandle, SystemTable, FlashDriverSmmInit, FlashDriverInit
           );
}
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************