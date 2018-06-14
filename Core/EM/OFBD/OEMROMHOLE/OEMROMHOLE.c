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
// $Header: /Alaska/SOURCE/Modules/OFBD/OEMROMHOLE/OEMROMHOLE.c 3     3/16/11 10:33p Terrylin $
//
// $Revision: 3 $
//
// $Date: 3/16/11 10:33p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/OFBD/OEMROMHOLE/OEMROMHOLE.c $
// 
// 3     3/16/11 10:33p Terrylin
// [TAG]  		EIP51285
// [Category]  	Improvement
// [Description]  	Fill the description for user more clearly.
// [Files]  		OEMROMHOLE.mak
// OEMROMHOLE.c
// OEMROMHOLE.h
// 
// 2     1/11/10 4:00a Lawrencechang
// Solve compiling warning about type casting from UINTN to UINT16.
// 
// 1     12/16/09 12:51a Lawrencechang
// Initial check-in.
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:    OEMROMHOLE.c
//
// Description: 
// Unlike the same name module in CORE8. Due to AFUAPTIO has ability to identify ROM hole location and size in ROM
// file. This function is only used to provide AFU the messages to show on screen if user tries to flash sesitive data
// in ROM hole.
//
//<AMI_FHDR_END>
//**********************************************************************
#include "Efi.h"
#include "token.h"
#include <AmiLib.h>
#include <AmiDxeLib.h>
#include "OEMROMHOLE.h"
#include "..\OFBD.h"

static UINT16 dwOFBDTblEndOffset = 0;

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   OFBDOemStrHandle
//
// Description: OFBD OEM STRING Handle
// 
// This routine will output the OEM String message to the flash utility.
//
// Input:
//      IN OUT  OFBD_HDR    *pOFBDHdr
//      IN      char        *OEMSTR
//      IN      EFI_GUID    *ROMHOLEGUID
//      IN      BOOLEAN     IsAppend
// Output:
//      EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
OFBDOemStrHandle(
    IN OUT OFBD_HDR *pOFBDHdr,
    IN char *OEMSTR,
    IN EFI_GUID * ROMHOLEGUID,
    IN BOOLEAN IsAppend)
{
    EFI_STATUS Status = EFI_SUCCESS;
    OFBD_TC_50_RH_STRUCT *RomHoleStructPtr;
    UINT8 *pOFBDTblEnd;
    
    RomHoleStructPtr = (OFBD_TC_50_RH_STRUCT *)((UINT8 *)pOFBDHdr + pOFBDHdr->OFBD_HDR_SIZE + sizeof(OFBD_EXT_HDR)); 
    pOFBDTblEnd = (UINT8 *)((UINT8 *)pOFBDHdr + (pOFBDHdr->OFBD_Size));
    
    if (MemCmp(&(RomHoleStructPtr->HoleGuid), ROMHOLEGUID, sizeof(EFI_GUID)) == 0)
    {
        if (IsAppend == 0 && dwOFBDTblEndOffset > 0) {
            Strcpy((char *)pOFBDTblEnd+dwOFBDTblEndOffset, "\n");
            dwOFBDTblEndOffset += (UINT16)Strlen("\n");
            Strcpy((char *)pOFBDTblEnd+dwOFBDTblEndOffset, OEMSTR);
        }else
            Strcpy((char *)pOFBDTblEnd+dwOFBDTblEndOffset, OEMSTR);
        dwOFBDTblEndOffset += (UINT16)Strlen(OEMSTR);
        pOFBDHdr->OFBD_RS |= OFBD_RS_DIS_OEMSTR;
    }

    return(Status);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   OFBDRomHoleCheckHandle
//
// Description: OFBD Rom Hole Check Handle
//
// Input:
//      IN OUT OFBD_HDR *pOFBDHdr
// Output:
//      EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
OFBDRomHoleCheckHandle(
    IN OUT OFBD_HDR *pOFBDHdr)
{
    EFI_STATUS Status = EFI_SUCCESS;
    
    //
    // About OEM RomHole Message, PLEASE FOLLOW BELOW 3 Steps TO DO. +>>> <OEM_STR>
    //
#if OEM_ROM_HOLE_SAMPLE_TEST

    OFBD_TC_50_RH_STRUCT *RHPtr;  
//
//  Step 1: Add your RomHole OEM string message for AFU to display
//
    char *DisOemStr0Protect = "RomHole 0 is Protected!";
    char *DisOemStr0Program = "RomHole 0 is Programming!";
    char *DisOemStr1Protect = "RomHole 1 is Protected!";
    char *DisOemStr1Program = "RomHole 1 is Programming!";
    char *DisOemStrNewLine = "After next line ";
    char *DisOemStrAppend  = "& Test!";
//
//  Step 2: Add your RomHole GUID definition here for AFU to compare
//
//  For example :
//                EFI_GUID gEfiRomHoleX = OEM_ROM_HOLE_X_GUID;    // Specific Rom Hole X Guid
//
//  Notice: X range should be 0~7. ( Max of 8 RomHole support )
//
    EFI_GUID gEfiRomHole0 = OEM_ROM_HOLE_0_GUID;    // Specific Rom Hole 0 Guid
    EFI_GUID gEfiRomHole1 = OEM_ROM_HOLE_1_GUID;    // Specific Rom Hole 1 Guid

    // --------------------------------------------------------------------------------------------------
    // DO NOT MODIFY +>>>>
    // --------------------------------------------------------------------------------------------------
    RHPtr = (OFBD_TC_50_RH_STRUCT *)((UINT8 *)pOFBDHdr + pOFBDHdr->OFBD_HDR_SIZE + sizeof(OFBD_EXT_HDR));    
    dwOFBDTblEndOffset = 0;
    // --------------------------------------------------------------------------------------------------
    // DO NOT MODIFY <<<<+
    // --------------------------------------------------------------------------------------------------

//
//  Step 3: Define your RomHole message to the corresponding AFU commands.
//    
//  Notice: OFBD_TC_CFG_XXX reference from OFBD.H file (Type Code 51 Return Status)
//
    //
    // Sample 1: AFU issued the /Hole command to update the specific Rom Hole
    //
    if (RHPtr->ddExtCmd == OFBD_TC_CFG_ROMHOLE)
    {
        //  Display the OEM message
        OFBDOemStrHandle(pOFBDHdr, DisOemStr0Program, &gEfiRomHole0, 0);
        OFBDOemStrHandle(pOFBDHdr, DisOemStr1Program, &gEfiRomHole1, 0);
    }
    //
    // Sample 2: AFU issued the /P or /B command to update the FV_MAIN or FV_BB region (default the Rom Hole is been protected.)
    //
    if (RHPtr->ddExtCmd == OFBD_TC_CFG_P || RHPtr->ddExtCmd == OFBD_TC_CFG_B)
    {
        //  Display the OEM message
        OFBDOemStrHandle(pOFBDHdr, DisOemStr0Protect, &gEfiRomHole0, 0);
        OFBDOemStrHandle(pOFBDHdr, DisOemStr1Protect, &gEfiRomHole1, 0);
        OFBDOemStrHandle(pOFBDHdr, DisOemStrNewLine, &gEfiRomHole0, 0);
        OFBDOemStrHandle(pOFBDHdr, DisOemStrAppend, &gEfiRomHole0, 1);
    }
    
#endif // #if OEM_ROM_HOLE_SAMPLE_TEST
    // About OEM RomHole Message, PLEASE FOLLOW ABOVE 3 Steps TO DO. <<<+ <OEM_STR>
    
    return(Status);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   OEMROMHOLEEntry
//
// Description: OFBD OEM ROM HOLE Entry Point
//
// Input:
//      IN VOID             *Buffer
//      IN OUT UINT8        *pOFBDDataHandled
// Output:
//      VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID OEMROMHOLEEntry (
    IN VOID             *Buffer,
    IN OUT UINT8        *pOFBDDataHandled )
{
    OFBD_HDR *pOFBDHdr;
    OFBD_EXT_HDR *pOFBDExtHdr; 

    if(*pOFBDDataHandled == 0)
    {
        pOFBDHdr = (OFBD_HDR *)Buffer;
        pOFBDExtHdr = (OFBD_EXT_HDR *)((UINT8 *)Buffer + (pOFBDHdr->OFBD_HDR_SIZE));
        
        if(pOFBDHdr->OFBD_FS & OFBD_FS_ROMH)
        {   
            //Check Type Code ID
            if(pOFBDExtHdr->TypeCodeID == OFBD_EXT_TC_ROMHOLE)
            {                  
                if(OFBDRomHoleCheckHandle(pOFBDHdr) == EFI_SUCCESS)
                {
                    //OEM ROM HOLE Data Handled.
                    *pOFBDDataHandled = 0xFF;      
                    return;
                }
            } 
            //Error occured
            *pOFBDDataHandled = 0xFE;          
            return;
        }  
    }

    return;
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
