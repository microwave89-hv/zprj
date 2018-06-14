//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
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
// $Header: /Alaska/SOURCE/Modules/OFBD/DEFCFG/DefCfg.c 9     8/16/13 3:13a Terrylin $
//
// $Revision: 9 $
//
// $Date: 8/16/13 3:13a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/OFBD/DEFCFG/DefCfg.c $
// 
// 9     8/16/13 3:13a Terrylin
// [Description]  	Correct the description error.
// 
// 8     8/07/13 11:21p Terrylin
// [Description]  	Add more description.
// 
// 7     7/31/13 4:49a Terrylin
// [TAG]  		EIP125898
// [Category]  	New Feature
// [Description]  	Add the AFU's /Kn and /Ln two commands status control.
// 
// 6     8/06/12 7:00a Terrylin
// [TAG]  		EIP96286
// [Category]  	Improvement
// [Description]  	Add the template codes for SMBIOS module DMI data
// preserve support.
// [Files]  		DefCfg.sdl
// DefCfg.c
// 
// 5     2/22/12 4:37a Terrylin
// Add the GAN command support sample
// 
// 4     3/16/11 10:37p Terrylin
// [TAG]  		EIP51285
// [Category]  	Improvement
// [Description]  	Fill the description for user more clearly.
// [Files]  		DefCfg.mak
// DefCfg.h
// DefCfg.c
// 
// 3     12/17/10 3:21a Terrylin
// Fix sample code is wrong problem.
// 
// 2     6/07/10 11:22p Terrylin
// Fix sample code is wrong problem.
// 
// 1     5/06/10 2:22a Lawrencechang
// Initial check-in.
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	DefCfg.c
//
// Description:
// OFBD Default Command Configuration provides BIOS an oppertunity to override end user issued command in AFU.
//
// For example, BIOS could disable /k command even user issued it in AFU, or automatically enable /b when /p
// is issued.
//
// For AFU¡¦s "/Ln" and "/Kn" two commands parameter identify. That AFU will replace the OFBD_EXT_TBL_END data 
// from 0xFFFF55AA to OFBD_TC_51_DC_EXT_STRUCT. Therefore, BIOS can through the "ddIndexCfg" flag to identify
// who is this command structure. (The AFU version 3.05.1 or later supports.)
//
// Please reference OFBDDEFCFGHandle for more details.
//
//<AMI_FHDR_END>
//**********************************************************************
#include "Efi.h"
#include "token.h"
#include <AmiLib.h>
#include <AmiDxeLib.h>
#include "DefCfg.h"
#include "..\OFBD.h"

//#define CONVERT_TO_STRING(a) #a
#define STR(a) CONVERT_TO_STRING(a)

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	OFBDDEFCFGHandle
//
// Description:	OFBD Default Command Configuration Handle
//
// Input:
//      IN OUT OFBD_HDR *pOFBDHdr
// Output:
//      EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
OFBDDEFCFGHandle( 
    IN OUT OFBD_HDR *pOFBDHdr)
{
    EFI_STATUS Status = EFI_SUCCESS;

	UINT8 *pOFBDTblEnd;
	OFBD_TC_51_DC_STRUCT *DCStructPtr;
	OFBD_TC_51_DC_EXT_STRUCT *DCExtStructPtr;
	UINT32 ExtAddr;
	
	pOFBDTblEnd = (UINT8 *)((UINT8 *)pOFBDHdr + (pOFBDHdr->OFBD_Size));
	DCStructPtr = (OFBD_TC_51_DC_STRUCT *)((UINT8 *)pOFBDHdr + pOFBDHdr->OFBD_HDR_SIZE + sizeof(OFBD_EXT_HDR)); 
	DCExtStructPtr = (OFBD_TC_51_DC_EXT_STRUCT *)((UINT8 *)pOFBDHdr + (pOFBDHdr->OFBD_Size) - sizeof(OFBD_END));
	ExtAddr = *(UINT32 *)((UINT8 *)pOFBDTblEnd - sizeof(OFBD_END));
	if (ExtAddr == OFBD_EXT_TBL_END)
	    DCExtStructPtr = NULL;
	
#if SMBIOS_DMIEDIT_DATA_LOC == 2

	if ((DCStructPtr->ddRetSts & OFBD_TC_CFG_N) && (DCStructPtr->ddRetSts & OFBD_TC_CFG_R) && (DCStructPtr->ddRetSts & OFBD_TC_CFG_CAPSULE))
    {
        EFI_GUID    gEfiSmbiosNvramGuid = {0x4b3082a3, 0x80c6, 0x4d7e, { 0x9c, 0xd0, 0x58, 0x39, 0x17, 0x26, 0x5d, 0xf1 }};
        CHAR16      *PreserveSmbiosNvramVar = L"PreserveSmbiosNvramVar";
		UINTN 		Size = sizeof (UINT8);
        UINT32      PreserveSmbiosNvram;

		// Set PreserveSmbiosNvram
		pRS->SetVariable (
			PreserveSmbiosNvramVar,
			&gEfiSmbiosNvramGuid,
			EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_NON_VOLATILE,
			Size,
			&PreserveSmbiosNvram
			);
	}

#endif
    
#if DEF_CFG_SAMPLE_TEST
    //
	// OEM add
	//
	
	// Sample : always cancel /K command
	if (DCStructPtr->ddRetSts & OFBD_TC_CFG_K)
	{
		DCStructPtr->ddExtCfg |= OFBD_TC_CFG_K;
	}
	
	// Sample : add new /B command when /P has issued
	if (DCStructPtr->ddRetSts & OFBD_TC_CFG_P)
	{
		DCStructPtr->ddRetSts |= OFBD_TC_CFG_B;
	}

    // Sample : For GAN command 
    // If ddRetSts equals to "0xFFFFFFFF", this means BIOS supply "/GAN" command.
	if (DCStructPtr->ddRetSts & OFBD_TC_CFG_GAN)
	{
		DCStructPtr->ddRetSts = 0xFFFFFFFF;
	}
		
	// Sample : For /Ln or /Kn command status setting
	if (DCExtStructPtr)
    {
        OFBD_TC_51_DC_EXT_STRUCT *NStructPtr = DCExtStructPtr;
        
        do
        {
            // Check current struct is Ln command or not
            if (NStructPtr->ddIndexCfg == OFBD_TC_CFG_LN)
            {
                // Sample : add new /L1 command when /L0 command is issued
                if (NStructPtr->ddExtCfg & BIT00)
                {
                    NStructPtr->ddExtCfg |= BIT01;
                }
            }
            
            // Check current struct is Kn command or not
            if (NStructPtr->ddIndexCfg == OFBD_TC_CFG_KN)
            {
                // Sample : always cancel /K0 command
                if (NStructPtr->ddExtCfg & BIT00)
                {
                    NStructPtr->ddIgnCfg |= BIT00;
                }
            }
            // Ponit to next structure
            NStructPtr++;
            ExtAddr = *(UINT32 *)NStructPtr;
        }while(ExtAddr && ExtAddr != 0xFFFFFFFF);
    }
#endif

    return(Status);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	DEFCFGEntry
//
// Description:	OFBD Default Command Configuration Entry Point
//
// Input:
//      IN VOID             *Buffer
//      IN OUT UINT8        *pOFBDDataHandled
// Output:
//      VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID DEFCFGEntry (
    IN VOID             *Buffer,
    IN OUT UINT8        *pOFBDDataHandled )
{
	OFBD_HDR *pOFBDHdr;
	OFBD_EXT_HDR *pOFBDExtHdr; 
	VOID *pOFBDTblEnd;
	OFBD_TC_51_DC_STRUCT *DCStructPtr;  

	if(*pOFBDDataHandled == 0)
	{
		pOFBDHdr = (OFBD_HDR *)Buffer;
		pOFBDExtHdr = (OFBD_EXT_HDR *)((UINT8 *)Buffer + (pOFBDHdr->OFBD_HDR_SIZE));
		DCStructPtr = (OFBD_TC_51_DC_STRUCT *)((UINT8 *)pOFBDExtHdr + sizeof(OFBD_EXT_HDR)); 
		pOFBDTblEnd = (VOID *)((UINT8 *)Buffer + (pOFBDHdr->OFBD_Size));    
		
		if(pOFBDHdr->OFBD_FS & OFBD_FS_CFG)
		{   
			//Check Type Code ID
			if(pOFBDExtHdr->TypeCodeID == OFBD_EXT_TC_AFUDEFCFG)
			{  
				if(OFBDDEFCFGHandle(pOFBDHdr) == EFI_SUCCESS)
				{
					//OEM Default Command Configuration Handled.
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
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
