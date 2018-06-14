//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelPfat/Pfatflashlib/PfatFlashLib.c 9     4/24/13 7:39p Fredericko $
//
// $Revision: 9 $
//
// $Date: 4/24/13 7:39p $
//
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelPfat/Pfatflashlib/PfatFlashLib.c $
// 
// 9     4/24/13 7:39p Fredericko
// [TAG]  		EIP120447
// [Category]  	Improvement
// [Description]  	SHB ULT:  PFAT : Update with AFU Tools Fails SUT Locks
// [Files]  		PfatFlashLib.c
// PfatFlashLib.sdl
// 
// 8     12/19/12 7:23p Fredericko
// [TAG]  		EIP109350
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Solution]  	Building error when the token of BUILD_PEI_FLASH_LIB = 1
// for PFAT module
// [Files]  		PfatFlashLib.c
// PfatFlashLib.mak
// 
// 7     12/03/12 6:19p Fredericko
// [TAG]  		EIP107344
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	Afulnx fails
// [Solution]  	AFULNX2(Test BIOS to Test BIOS)_1AQPM016_Pretest
// [Files]  		PfatFlashLib.c
// 
// 6     11/08/12 3:23a Fredericko
// Changes for flash write. Requires Pi 1.1 and above support
// 
// 5     11/02/12 8:26p Fredericko
// [TAG]  		EIP105153
// [Description]  	Possible system hang if NVRAM is access during legacy
// O.S.
// 
// 4     10/16/12 6:45p Fredericko
// [TAG]  		EIP103945
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	System hang
// [RootCause]  	PfatInitialize check failure
// [Solution]  	The system can't enter UEFI WIN8 OS when PFAT is Disabled
// on seutp menu
// [Files]  		PfatFlashLib.c
// 
// 3     9/26/12 11:45a Fredericko
// [TAG]  		EIP102376
// [Description]  	Pfat CHM
// 
// 2     9/17/12 4:27p Fredericko
// 
// Initial Checkin
//
//
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:   PfatFlashLib.c
//
// Description: Code listing file for Pfat flashlib
//
//<AMI_FHDR_END>
//**********************************************************************

//----------------------------------------------------------------------
// Includes
#include <efi.h>
#include <FlashPart.h>
#include "token.h"
#if defined _DXE_FLASH_LIB_
#include <AmiDxeLib.h>
#include "Pfat\Pfat.h"
#include <Protocol\SmmBase2.h>
#include <Protocol\SmiFlash.h>
#include <AmiCspLib.h>
#include "ReferenceCode\Haswell\Include\CpuRegs.h"
#ifndef BIT35
#define BIT35 0x0000000800000000ULL
#endif


typedef BOOLEAN (IDENTIFY)(
    volatile UINT8*     pBlockAddress,
    FLASH_PART          **Struct
    );

extern UINT16       gFlashId;
FLASH_PART          *FlashInitialized = NULL;
PFAT_PROTOCOL       *PfatInstance = NULL;
extern IDENTIFY*    FlashList[];
EFI_SMM_SYSTEM_TABLE2   *mSmst = NULL;
EFI_SMM_BASE2_PROTOCOL *gSmmBase2 = NULL;
BOOLEAN				 InSmm;
EFI_EVENT           SmmPfatAvailableEvent;
EFI_EVENT           SmmAvailableEvent;
EFI_GUID            gSmmPfatProtocolGuid = SMM_PFAT_PROTOCOL_GUID;

VOID
PfatFlashEraseCommand   (
    volatile UINT8          *pBlockAddress
);


VOID
PfatProgramCommand (
    volatile UINT8          *pByteAddress,
    UINT8                   *Byte,
    UINT32                  *Length
);


VOID
PfatReadCommand    (
    volatile UINT8          *pByteAddress,
    UINT8                   *Byte,
    UINT32                  *Length
);


BOOLEAN
PfatIsEraseCompleted   (
   IN  volatile UINT8          *pBlockAddress,
   OUT BOOLEAN                 *pError,
   OUT UINTN                   *pStatus
);


BOOLEAN
PfatProgramCompleted (
    volatile UINT8          *pByteAddress,
    UINT8                   *Byte,
    UINT32                  Length,
    BOOLEAN                 *pError,
    UINTN                   *pStatus
);


VOID
PfatBlockWriteEnable(
   UINT8      *pBlockAddress
);


VOID
PfatBlockWriteDisable  (
  UINT8          *pBlockAddress
);


VOID
PfatDeviceWriteEnable  (
    VOID
);


VOID
PfatDeviceWriteDisable (
    VOID
);


VOID
PfatDeviceVirtualFixup (
    EFI_RUNTIME_SERVICES    *pRS
);


#define SECTOR_SIZE_4KB             0x1000  // Common 4kBytes sector size

FLASH_PART mPfatFlash =
    {
        PfatReadCommand,
        PfatFlashEraseCommand,
        PfatProgramCommand,
        PfatIsEraseCompleted,
        PfatProgramCompleted,
        PfatBlockWriteEnable,
        PfatBlockWriteDisable,
        PfatDeviceWriteEnable,
        PfatDeviceWriteDisable,
        PfatDeviceVirtualFixup,      
        1,                           
        SECTOR_SIZE_4KB                    
    };





EFI_STATUS
OnSmmPfatProtocolAvailable (
  IN  EFI_EVENT                   Event,
  IN  VOID                        *Context
  )
{
     EFI_STATUS Status;
  
     if(gSmmBase2 == NULL){
        Status = pBS->LocateProtocol( &gEfiSmmBase2ProtocolGuid, NULL, &gSmmBase2 );
     }
          
     if(gSmmBase2!= NULL){
         if(mSmst == NULL){
              Status = gSmmBase2->GetSmstLocation (gSmmBase2, &mSmst);
         }
      }
                
      Status = gSmmBase2->InSmm(gSmmBase2, &InSmm);

      Status = pBS->LocateProtocol (&gSmmPfatProtocolGuid,
                                        NULL,
                                        &PfatInstance);

      pBS->CloseEvent (SmmPfatAvailableEvent);
      return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   IdentifyPfatFlash
//
// Description: Identifies whether PfatFlash library should control access to
//              SPI flash part
//
// Input:   volatile UINT8 *pBlockAddress
//
// Output:  FLASH_PART     **FlashStruc
//
// Returns: BOOLEAN
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN
IdentifyPfatFlash (
    IN  volatile UINT8 *pBlockAddress,
    OUT FLASH_PART     **FlashStruc
)
{
    UINTN       i;
    BOOLEAN     found = FALSE;  
    EFI_STATUS  Status;
    VOID       *Reg;
   
    if ( !((ReadMsr (MSR_PLATFORM_INFO) & B_MSR_PLATFORM_INFO_PFAT_AVAIL) && 
           (ReadMsr (MSR_PLAT_FRMW_PROT_CTRL) & B_MSR_PLAT_FRMW_PROT_CTRL_EN)) ) {  
         //
		 // Pfat disabled or not support
		 //
		 return FALSE;
    }

    if(FlashInitialized == NULL)
    {
       for(i=1; !found && FlashList[i]; i++)
       {
          found=FlashList[i](pBlockAddress, &FlashInitialized);
       }    
    }

    if(FlashInitialized == NULL)return FALSE;

    if(found)
    {
       *FlashStruc = &mPfatFlash;

        Status = pBS->CreateEvent (EFI_EVENT_NOTIFY_SIGNAL,
                                   TPL_CALLBACK,
                                   OnSmmPfatProtocolAvailable,
                                   NULL,
                                   &SmmPfatAvailableEvent);

        if(!EFI_ERROR(Status)){
            Status = pBS->RegisterProtocolNotify (
            &gSmmPfatProtocolGuid,
            SmmPfatAvailableEvent,
            &Reg);
        }
    }


    return found;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   IsPfatFlashInitialized
//
// Description: Verifies whether Pfat library has been initialized or not
//
// Input:   VOID
//
// Output:  VOID
//
// Returns: BOOLEAN
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN
IsPfatFlashInitialized()
{
  EFI_STATUS  Status;
 
  if((PfatInstance == NULL) && (pST->BootServices != NULL)){
    if(InSmm == FALSE)
      {
        if(gSmmBase2 == NULL){
            Status = pBS->LocateProtocol( &gEfiSmmBase2ProtocolGuid, NULL, &gSmmBase2 );
         }
          
        if(gSmmBase2!= NULL){
             if(mSmst == NULL){
                  Status = gSmmBase2->GetSmstLocation (gSmmBase2, &mSmst);
            }
            Status = gSmmBase2->InSmm(gSmmBase2, &InSmm);
        }

              Status = pBS->LocateProtocol (&gSmmPfatProtocolGuid,
                                        NULL,
                                        &PfatInstance);
             
      }

  }

  if( PfatInstance != NULL ){ return TRUE; }
  PfatInstance = NULL;
  return FALSE;
}




//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   PfatFlashEraseCommand
//
// Description: Erases SPI via PFAT library
//
// Input:   IN volatile UINT8*      pBlockAddress
//
// Output:  VOID
//
// Returns: VOID
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
PfatFlashEraseCommand   (
    IN volatile UINT8*      pBlockAddress
)
{
  if(IsPfatFlashInitialized()){
      PfatInstance->Erase(PfatInstance,
                    (UINTN)(EFI_PHYSICAL_ADDRESS)pBlockAddress);
  }else{
    if ( FlashInitialized == NULL)return;
    FlashInitialized->FlashEraseCommand(pBlockAddress);
  }
}



//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   PfatIsEraseCompleted 
//
// Description: Checks whether PFAT erase command was completed
//
// Input: volatile UINT8  *pBlockAddress
//
// Output: BOOLEAN                 *pError
//         UINTN                   *pStatus
//
// Returns: BOOLEAN
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN 
PfatIsEraseCompleted (
   IN  volatile UINT8          *pBlockAddress,
   OUT BOOLEAN                 *pError,
   OUT UINTN                   *pStatus
)
{
  if(IsPfatFlashInitialized()){
      *pError = FALSE;
      *pStatus = EFI_SUCCESS;
  }else{
    if ( FlashInitialized == NULL)return FALSE;
    return (FlashInitialized->FlashIsEraseCompleted(pBlockAddress,\
                             pError, pStatus));
  }

  return TRUE;
}



//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   PfatFlashProgramCommand
//
// Description: Programs SPI part via PFAT library
//
// Input:  volatile UINT8*      pByteAddress
//         UINT8                *Byte
//         UINT32               *Length
//
// Output:  VOID
//
// Return:  VOID 
//----------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
PfatProgramCommand (
    IN volatile UINT8*      pByteAddress,
    IN UINT8                *Byte,
    IN UINT32               *Length
)
{ 
   if(IsPfatFlashInitialized()){  
        PfatInstance->Write(PfatInstance,
                       (UINTN)pByteAddress,
                       *Length, Byte);
        if(((*(UINT8 *)(UINTN)0xFED1F890) & BIT4))
        {
           (*(UINT16 *)(UINTN)0xFED1F804)|= BIT2;
        }
        PfatInstance->Execute(PfatInstance, FALSE);
        *Length = 0;

    }else{
       if ( FlashInitialized == NULL)return;
       FlashInitialized->FlashProgramCommand(pByteAddress, Byte, Length); 
    }
}




//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   PfatReadCommand
//
// Description: Reads the SPI flash part via PFAT library
//      
//
// Input:   *pBlockAddress - Address to access flash part
//          *Byte - pointer to data to write to the flash part
//          Length - The total amount of data that Byte points to
//
// Output:  VOID
//
// Return:  VOID
//----------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
PfatReadCommand    (
    volatile UINT8          *pByteAddress,
    UINT8                   *Byte,
    UINT32                  *Length
)
{
    if ( FlashInitialized == NULL)return;
    FlashInitialized->FlashReadCommand(pByteAddress, Byte, Length);
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   PfatProgramCompleted
//
// Description: Checks whether Pfat Flash program was completed
//      
//
// Input:   *pBlockAddress - Address to access flash part
//          *Byte - values previously written to the Flash Device
//          Length - The amount of data that needs to be checked
//          *pError - Boolean that tells if fatal error occured
//          *pStatus - Status of the erase command
//
// Output: *pError - Boolean that tells if fatal error occured
//         *pStatus - Status of the erase command
//
// Return:  TRUE - Program completed, check pError for fatal error
//          FALSE - programming in progress
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN
PfatProgramCompleted (
    IN  volatile UINT8*     pByteAddress,
    IN  UINT8               *Byte,
    IN  UINT32              Length,
    OUT BOOLEAN             *pError,
    OUT UINTN               *pStatus
)
{
    if (pError) *pError = FALSE;
    return TRUE;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   PfatBlockWriteEnable
//
// Description: This function chooses the correct flash part to call and
//      then enables write operations(erase/programming) for a specific block
//
// Input:   *pBlockAddress - Address to access flash part
//
// Output:  VOID
//
// Return:  VOID
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
PfatBlockWriteEnable(
    UINT8      *pBlockAddress
)
{
    if (IsPfatFlashInitialized())return;
    if ( FlashInitialized == NULL)return;
    FlashInitialized->FlashBlockWriteEnable(pBlockAddress);
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   PfatBlockWriteDisable
//
// Description: This function chooses the correct flash part to call and
//      then disables write operations(erase/programming) for a specific
//      block
//
// Input:   *pBlockAddress - Address to access flash part
//
// Output:  VOID
//
// Return:  VOID
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
PfatBlockWriteDisable (
    IN  UINT8          *pBlockAddress
)
{
    if (IsPfatFlashInitialized())return;
    if ( FlashInitialized == NULL)return;
    FlashInitialized->FlashBlockWriteDisable(pBlockAddress);
}



//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   PfatDeviceWriteEnable
//
// Description: This function chooses the correct flash part to call and
//      then enables write operation for a flash device
//
// Input:   VOID
//
// Output:  VOID
//
// Return:  VOID
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
PfatDeviceWriteEnable (VOID)
{
    if (IsPfatFlashInitialized())return;
    if ( FlashInitialized == NULL)return;
    FlashInitialized->FlashDeviceWriteEnable();
}




//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   PfatDeviceWriteDisable
//
// Description: This function chooses the correct flash part to call and
//      then disables write operation for a flash device
//
// Input:   VOID
//
// Output:  VOID
//
// Return:  VOID
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
PfatDeviceWriteDisable(VOID)
{
    if (IsPfatFlashInitialized())return;
    if ( FlashInitialized == NULL)return;
    FlashInitialized->FlashDeviceWriteDisable();
}



//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   PfatDeviceVirtualFixup
//
// Description: Fixup global data for for a virtual address space.
//      This routine must be called by the library consumer in the
//      EVT_SIGNAL_VIRTUAL_ADDRESS_CHANGE event handler
//
// Input:   EFI_RUNTIME_SERVICES *pRS - pointer to the Runtime Services Table
//
// Output:  VOID
//
// Return:  VOID
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
PfatDeviceVirtualFixup   (
    IN EFI_RUNTIME_SERVICES *pRS
)
{
   VOID            **p;

   if (IsPfatFlashInitialized()){
       return;
   }

   if ( FlashInitialized == NULL)return;

   FlashInitialized->FlashVirtualFixup(pRS);

   for(p = (VOID**)FlashInitialized; p < (VOID**)(FlashInitialized + 1); p++)
   pRS->ConvertPointer(0, p);

   //Fixup FlashAPI pointer
   pRS->ConvertPointer(0, &FlashInitialized);
}

#else

BOOLEAN
IdentifyPfatFlash (
    IN  volatile UINT8 *pBlockAddress,
    OUT FLASH_PART     **FlashStruc
)
{
	return FALSE;
}

#endif

VOID
PreventAFUWhenPfatEnable (
    IN     UINT8        SwSmiNum,
    IN OUT UINT64       Buffer
)
{
    if (SwSmiNum != 0x25) return; 
    if ( ((ReadMsr (MSR_PLATFORM_INFO) & B_MSR_PLATFORM_INFO_PFAT_AVAIL) && 
         (ReadMsr (MSR_PLAT_FRMW_PROT_CTRL) & B_MSR_PLAT_FRMW_PROT_CTRL_EN)) ) {
          //
          // Update Implemented to TRUE, AFU will assume the SMIFlash is no support.
          //
          ((INFO_BLOCK*)Buffer)->Implemented = TRUE;
    }
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