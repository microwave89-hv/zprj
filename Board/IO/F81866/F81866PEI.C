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
//
//*************************************************************************
// $Header: /Alaska/BIN/IO/Fintek/F81866/F81866PEI.C 1     7/20/11 4:22a Kasalinyi $
//
// $Revision: 1 $
//
// $Date: 7/20/11 4:22a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/IO/Fintek/F81866/F81866PEI.C $
// 
// 1     7/20/11 4:22a Kasalinyi
// [Category]  	Improvement
// [Description]  	Initial Porting 
// [Files]  		F81866.CIF
// IO_F81866.SDL
// F81866.ASL
// F81866.MAK
// F81866.SD
// F81866.UNI
// F81866DXE.C
// F81866PEI.C
// F81866PeiDebugger.C
// F81866Setup.C
// F81866Setup.H
// History.txt
// F81866.chm
// 
// 4     3/21/11 9:41p Mikes
// seperate the core and oem job
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:  <F81866PEI.C>
//
// Description: Porting for PEI phase.Just for necessary devices porting.
//
//
//<AMI_FHDR_END>
//*************************************************************************
//-------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------
#include <Pei.h>
#include <Token.h>
#include <AmiLib.h>
#include <Protocol\AmiSio.h>
#include <AmiCspLib.h>
#include "BSP\PeiIoTable.h"

//-------------------------------------------------------------------------
// Constants, Macros and Type Definitions
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
//Variable, Prototype, and External Declarations
//-------------------------------------------------------------------------
#if (IODECODETYPE)
extern IO_RANGE_DECODE  SIO_IoRange_Decode_LIST EndOfInitList;
static IO_RANGE_DECODE* CspIoRangeDecodeList[] = {SIO_IoRange_Decode_LIST NULL};
#endif //#if (IODECODETYPE)

EFI_STATUS PeiLoopCspIoDecodeListInit (
   IN      VOID             *Fun, 
   IN      UINT16           Base, 
   IN      UINT8            DevUid,  
   IN      SIO_DEV_TYPE     Type    
);  //

VOID PeiSetLpcDeviceDecoding(VOID); //

VOID F81866_INIT(VOID); //

VOID PeiF81866Init (
    IN EFI_FFS_FILE_HEADER        *FfsHeader,
    IN EFI_PEI_SERVICES            **PeiServices 
);

 
// <AMI_PHDR_START>
//-------------------------------------------------------------------------
//
// Procedure: PeiF81866Init
//
// Description:
//  This function provide PEI phase SIO initialization
//
// Input:
//  IN  EFI_FFS_FILE_HEADER    *FfsHeader - Logical Device's information
//  IN  EFI_PEI_SERVICES       **PeiServices  - Read/Write PCI config space
//
// Output:    None
//
// Modified:  Nothing
//
// Referrals: None
//
// Note:
//------------------------------------------------------------------------- 
// <AMI_PHDR_END> 
VOID PeiF81866Init (
    IN EFI_FFS_FILE_HEADER        *FfsHeader,
    IN EFI_PEI_SERVICES            **PeiServices 
)
{
    F81866_INIT();
}

// <AMI_PHDR_START>
//-------------------------------------------------------------------------
//
// Procedure: F81866_INIT
//
// Description:
//
//  This function Step through table and initialize the Logic Device
//
// Input:     None
//
// Output:    EFI_STATUS
//
// Modified:  Nothing
//
// Referrals: None
//
// Note:
//------------------------------------------------------------------------- 
// <AMI_PHDR_END> 
VOID F81866_INIT(VOID) 
{
    UINTN   i;

    // Decode neccessary IO resource in PEI phase
    PeiSetLpcDeviceDecoding();

    // Step through table and initialize the Serial Port
    for(i=0; i<(sizeof(F81866_PEI_Init_Table))/(sizeof(SIO_DATA));i++) {
        // If Mask=0xFF,only write register.
        if(F81866_PEI_Init_Table[i].DataMask == 0xFF) { 
            IoWrite8(F81866_PEI_Init_Table[i].Addr, F81866_PEI_Init_Table[i].DataValue);
        } 
        // Read and writer register
        else { 
            IoWrite8(F81866_PEI_Init_Table[i].Addr, \
                                IoRead8(F81866_PEI_Init_Table[i].Addr) \
                                & F81866_PEI_Init_Table[i].DataMask \
                                | F81866_PEI_Init_Table[i].DataValue);
        }
    }
}

//<AMI_PHDR_START>
//-------------------------------------------------------------------------
// Procedure:    PeiLoopCspIoDecodeListInit
//
// Description:  
//  Looking for the suitable IoDecode Funtion circularly.
//
// Input:   
//  IN  VOID            *Fun,     -- EFI_PCI_IO_PROTOCOL *LpcPciIo
//  IN  UINT16          Base,     -- I/O base address, Base=0 means disable the decode of the device
//  IN  UINT8           DevUid,   -- The device Unique ID,If type is 0xFF, DevUid contain the IO length
//  IN  SIO_DEV_TYPE    Type      -- device type
//
// Output:    
//  EFI_STATUS
//
//-------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PeiLoopCspIoDecodeListInit (
   IN      VOID             *Fun, 
   IN      UINT16           Base, 
   IN      UINT8            DevUid,  
   IN      SIO_DEV_TYPE     Type
)
{
    EFI_STATUS  Status;
    UINTN       i = 0;

    #if(IODECODETYPE)
    for(i=0; CspIoRangeDecodeList[i]; i++)
    {
        //decode by OEM porting with eLink function(default)
        Status = CspIoRangeDecodeList[i](Fun, Base, DevUid, Type); 
        if(Status == EFI_SUCCESS) return Status;
    }

    #else
    if ( (Type != 0xFF) || (Base == 0x2E) || (Base == 0x4E) ) 
        // decode by chipset porting in SBGeneric.c
        Status = SbLib_SetLpcDeviceDecoding(Fun, Base, DevUid, Type);  
    else
        // decode by chipset porting in SBGeneric.c
        Status = SbLib_SetLpcGenericDecoding(Fun, Base, DevUid,Type);  

    #endif

    return Status;
}

//<AMI_PHDR_START>
//-------------------------------------------------------------------------
// Procedure:    PeiSetLpcDeviceDecoding
//
// Description:    
//  This function is used to open IoDecode for logic devices initialized in PEI
//
// Input:    
//
// Output:    EFI_STATUS
//
// Notes:    PORTING REQUIRED
//-------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID PeiSetLpcDeviceDecoding(VOID)
{
    EFI_STATUS  Status=EFI_SUCCESS;
    UINT8       i;

    for(i=0;i<(sizeof(F81866_Decode_Table))/(sizeof(IO_DECODE_DATA));i++)
    {
        Status = PeiLoopCspIoDecodeListInit(  NULL,\
                    F81866_Decode_Table[i].BaseAdd,\
                    F81866_Decode_Table[i].UID,\
                    F81866_Decode_Table[i].Type);
    }
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

