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
// $Header: /Alaska/BIN/IO/Fintek/F81216_Sec/F81216PEI.C 3     7/04/11 3:22a Kasalinyi $
//
// $Revision: 3 $
//
// $Date: 7/04/11 3:22a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/IO/Fintek/F81216_Sec/F81216PEI.C $
// 
// 3     7/04/11 3:22a Kasalinyi
// [Category]  	Improvement
// [Description]  	Update to new template
// [Files]  		IO_F81216.SDL
// F81216.ASL
// F81216.MAK
// F81216.SD
// F81216.UNI
// F81216DXE.C
// F81216PEI.C
// F81216Setup.H
// F81216.CIF
// 
// 2     9/06/10 3:50a Mikes
// Fix compile issue with first IO module
// 
// 1     3/31/10 5:55a Fantasylai
// Initial release to F81216 just as a second IO
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:  <F81216PEI.C>
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
#include <Setup.h>
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
extern EFI_STATUS PeiLoopCspIoDecodeListInit (
   IN      VOID             *Fun, 
   IN      UINT16           Base, 
   IN      UINT8            DevUid,  
   IN      SIO_DEV_TYPE     Type);

static VOID PeiSetLpcDeviceDecoding(VOID); //

VOID F81216SEC_INIT(VOID); //

VOID PeiF81216SECInit (
    IN EFI_FFS_FILE_HEADER        *FfsHeader,
    IN EFI_PEI_SERVICES            **PeiServices 
);

// <AMI_PHDR_START>
//-------------------------------------------------------------------------
//
// Procedure: PeiF81216SECInit
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
VOID PeiF81216SECInit (
    IN EFI_FFS_FILE_HEADER        *FfsHeader,
    IN EFI_PEI_SERVICES            **PeiServices 
)
{
    F81216SEC_INIT();
}

// <AMI_PHDR_START>
//-------------------------------------------------------------------------
//
// Procedure: F81216SEC_INIT
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
VOID F81216SEC_INIT(VOID) 
{
    UINTN   i;

    // Decode neccessary IO resource in PEI phase
//    PeiSetLpcDeviceDecoding();

    // Step through table and initialize the Serial Port
    for(i=0; i<(sizeof(F81216SEC_PEI_Init_Table))/(sizeof(SIO_DATA));i++) {
        // If Mask=0xFF,only write register.
        if(F81216SEC_PEI_Init_Table[i].DataMask == 0xFF) { 
            IoWrite8(F81216SEC_PEI_Init_Table[i].Addr, F81216SEC_PEI_Init_Table[i].DataValue);
        } 
        // Read and writer register
        else { 
            IoWrite8(F81216SEC_PEI_Init_Table[i].Addr, \
                                IoRead8(F81216SEC_PEI_Init_Table[i].Addr) \
                                & F81216SEC_PEI_Init_Table[i].DataMask \
                                | F81216SEC_PEI_Init_Table[i].DataValue);
        }
    }
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
static VOID PeiSetLpcDeviceDecoding(VOID)
{
    EFI_STATUS  Status=EFI_SUCCESS;
    UINT8       i;

    for(i=0;i<(sizeof(F81216SEC_Decode_Table))/(sizeof(IO_DECODE_DATA));i++)
    {
        Status = PeiLoopCspIoDecodeListInit(  NULL,\
                    F81216SEC_Decode_Table[i].BaseAdd,\
                    F81216SEC_Decode_Table[i].UID,\
                    F81216SEC_Decode_Table[i].Type);
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
