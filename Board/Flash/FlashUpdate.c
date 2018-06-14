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
// $Header: /Alaska/SOURCE/Flash_Combined_2/Core/FlashUpdate.c 11    8/06/10 12:03a Calvinchen $
//
// $Revision: 11 $
//
// $Date: 8/06/10 12:03a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Flash_Combined_2/Core/FlashUpdate.c $
// 
// 11    8/06/10 12:03a Calvinchen
// Added the "DIRECT_FLASH_MEMORY_ACCESS" Token. (Default setting is "ON",
// "OFF" for specific EC SPIs.) 
// 
// 10    6/24/09 3:11a Calvinchen
// (EIP22177) Updated for Aptio Source Enhancement. 
//
// 8     1/07/08 2:36p Robert
// Updates for coding standrad
//
// 7     11/09/07 3:52p Alexp
// Added FlashRead common function
//
// 6     3/26/07 7:21p Robert
// Coding standard updates
//
//
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:    FlashUpdate.c
//
// Description: Provides the rom flashing functions to the system
//
//<AMI_FHDR_END>
//**********************************************************************

// header includes
#include <EFI.h>
#include <Flash.h>
#include <Token.h>

//----------------------------------------------------------------------
// external variable defines
extern const UINTN FlashEmpty;

//----------------------------------------------------------------------
// global variable for the module
#define INT_SIZE sizeof(INTN)
#define FLASH_EMPTY_BYTE (UINT8)FlashEmpty

//----------------------------------------------------------------------
// Function prototypes
VOID
FlashEraseCommand (
    volatile UINT8* pBlockAddress
    );
VOID
FlashProgramCommand (
    volatile UINT8* pByteAddress,
    UINT8 *Byte, UINT32 Length
    );
VOID
FlashReadCommand (
    volatile UINT8* pByteAddress,
    UINT8 *Byte, UINT32 Length
    );
BOOLEAN
FlashIsEraseCompleted (
    volatile UINT8* pBlockAddress,
    BOOLEAN *pError,
    UINTN *pStatus
    );
BOOLEAN
FlashIsProgramCompleted (
    volatile UINT8* pByteAddress,
    UINT8 *Byte,
    UINT32 Length,
    BOOLEAN *pError,
    UINTN *pStatus
    );


//----------------------------------------------------------------------
// Function definitions

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   IsCleanOrEqual
//
// Description:  Verifies if the device has been erased properly or if the
//      current byte is the same as the byte to be written at this location
//
//
// Input:   UINT8 *pDest - starting address of where the data will be written
//          const UINT8 *pSource - starting address of the data that
//                      is supposed to be written
//          UINTN Size - length of the data set to check
//          BOOLEAN *pIsClean - return value to indicate that the data area
//                      that will be written to has already been erased
//          BOOLEAN *pIsEqual - return value to indicate that the data to be
//                      written is the same as the data that is already there
//
// Output:  see info on pIsClean and pIsEqual above
//
// Return:  None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
IsCleanOrEqual  (
    IN  UINT8           *pDest,
    IN  const UINT8     *pSource,
    IN  UINTN           Size,
    OUT BOOLEAN         *pIsClean,
    OUT BOOLEAN         *pIsEqual
)
{
    *pIsEqual = TRUE;
    *pIsClean = TRUE;

#if DIRECT_FLASH_MEMORY_ACCESS
    // loops through the destination looking to see if the data is the same
    //  as the source, or if the Destination has already bee erased
    if (!( (UINTN)pDest & (INT_SIZE-1) || (UINTN)pSource & (INT_SIZE-1) ))
    {
        UINTN *Dest = (UINTN*)pDest, *Source = (UINTN*)pSource;

        for( ; Size >= INT_SIZE; Size -= INT_SIZE)
        {
            if (*Dest != FlashEmpty)
                *pIsClean = FALSE;
            if (*Dest++ != *Source++)
                *pIsEqual = FALSE;
            if ( !(*pIsEqual || *pIsClean) )
                return;
        }
    }

    // since the address may not be INT_SIZE aligned, this checks
    //  the rest of the data
    for( ; Size > 0; Size--)
    {
        if (*pDest != FLASH_EMPTY_BYTE)
            *pIsClean = FALSE;
        if (*pDest++ != *pSource++)
            *pIsEqual = FALSE;
        if ( !(*pIsEqual || *pIsClean) )
            return;
    }
#else
    {
        UINT8               bData = 0;
        for( ; Size > 0; Size--) {
            FlashReadCommand(pDest, &bData, sizeof(UINT8));
            if (bData != FLASH_EMPTY_BYTE) *pIsClean = FALSE;
            if (bData != *pSource++) *pIsEqual = FALSE;
            if (!(*pIsEqual || *pIsClean)) return;
        }
    }
#endif
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   FlashEraseBlock
//
// Description:  Erases the block pointed to by BlockAddress
//
// Input:   *BlockAddress - Address within the block to be erased
//
// Output:      TRUE - Erase completed successfully
//              FALSE - Erase did not complete properly
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN
FlashEraseBlock (
    IN volatile UINT8*      BlockAddress
)
{
    BOOLEAN Error = FALSE;
    BOOLEAN Completed = TRUE;

    FlashEraseCommand(BlockAddress);

    while(!(Completed = FlashIsEraseCompleted(BlockAddress, &Error, NULL)));

    return Completed && !Error;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   FlashProgram
//
// Description:  Programs the area pointed to by BlockAddress and defined
//      by Length with the data pointed to by Data
//
// Input:   *Address - Address where to write the Data
//          *Data - pointer to the data to write
//          Length - length of the data to write
//
// Output:  None
//
// Return:  TRUE - Program completed successfully
//          FALSE - Program did not complete properly
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN
FlashProgram    (
    IN volatile UINT8*      Address,
    IN UINT8                *Data,
    IN UINT32               Length
)
{
    BOOLEAN Error=FALSE;
    BOOLEAN Completed=TRUE;

    FlashProgramCommand(Address,Data,Length);

    while(!(Completed = \
               FlashIsProgramCompleted(Address, Data, Length, &Error,NULL)));

    if (Error) return FALSE;

    return Completed && !Error;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   FlashRead
//
// Description:  This function returns the read data from the location
//      indicated
//
// Input:   *Address - Address where to write the Data
//          *Data - pointer to the data to write
//          Length - length of the data to write
//
// Output:  None
//
// Return:  TRUE - Program completed successfully
//          FALSE - Program did not complete properly
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN
FlashRead   (
    IN  volatile UINT8*     Address,
    OUT UINT8               *Data,
    IN  UINT32              Length
)
{
    FlashReadCommand(Address,Data,Length);

    return TRUE;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   FlashProgramBlock
//
// Description:  Programs the Block pointed to by pBlock with the data
//          pointed to by pData
//
// Input:   *pBlock - Address of the beginning of the block
//          *Data - pointer to the data to write
//
// Output:  None
//
// Return:  TRUE - Program completed successfully
//          FALSE - Program did not complete properly
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN
FlashProgramBlock   (
    IN UINT8*               pBlock,
    IN UINT8*               pData
)
{
    return FlashProgram(pBlock,pData,FlashBlockSize);
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   FlashWriteBlock
//
// Description:  Enables the ability to write to the flash part and
//          programs the Block pointed to by pBlock with the data
//          pointed to by Data and then sets the block to read only
//
// Input:   *pBlock - Address of the beginning of the block
//          *Data - pointer to the data to write
//
// Output:  None
//
// Return:  TRUE - Program completed successfully
//          FALSE - Program did not complete properly
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN
FlashWriteBlock (
    IN UINT8*               pBlock,
    IN UINT8*               pData
)
{
    BOOLEAN IsClean;
    BOOLEAN IsEqual;
    BOOLEAN Result;
    // This checks to see if the data in the flash part has already been
    // erased or if it is already the same as what will be programmed there
    IsCleanOrEqual(pBlock, pData, FlashBlockSize, &IsClean, &IsEqual);

    // If it is already the same then exit
    if (IsEqual)
        return TRUE;

    // if not the same enable the block for writing
    FlashBlockWriteEnable(pBlock);

    // This loop checks IsClean to see if the block area that is to be written to
    // has already been erased.  If it hasn't then, the FlashEraseBlock() is called
    // to erase the block.
    // If it is either clean or is erased, then it calls the program function
    if (IsClean || FlashEraseBlock(pBlock))
        Result = FlashProgramBlock(pBlock,pData);
    // If it is not clean and the erase block function does not finish properly
    // then set result to return false
    else
        Result = FALSE;

    // disable the ability to write to the block
    FlashBlockWriteDisable(pBlock);

    return Result;
}

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