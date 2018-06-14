//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
//**                                                             **//
//**         (C)Copyright 2009, American Megatrends, Inc.        **//
//**                                                             **//
//**                     All Rights Reserved.                    **//
//**                                                             **//
//**   5555 Oakbrook Pkwy, Building 200,Norcross, Georgia 30093  **//
//**                                                             **//
//**                     Phone (770)-246-8600                    **//
//**                                                             **//
//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
// $Header: /Alaska/BIN/Modules/AMIDebugRx/binaries/LIBS/StatusCodeLib/DbgrHelp.c 5     3/17/11 7:54a Sudhirv $
//
// $Revision: 5 $
//
// $Date: 3/17/11 7:54a $
//*****************************************************************
//*****************************************************************
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/AMIDebugRx/binaries/LIBS/StatusCodeLib/DbgrHelp.c $
// 
// 5     3/17/11 7:54a Sudhirv
// Support to Boot with S3 Resume in Core_4.6.5.0
// 
// 4     3/11/11 8:41a Sudhirv
// Added support to return Database Address correctly with Cores older
// than 4.6.4x
// 
// 3     3/09/11 8:18a Sudhirv
// EIP 53658 - AMIDebugRx\Debugger support for PI 1.1
// 
// 2     7/17/09 7:15p Madhans
// DebugRx 1.30.0022
// 
// 4     7/16/09 3:07p Madhans
// To fix the Serial Debugger issuel and To do cleanup.
// 
// 3     7/15/09 5:56p Madhans
// Release mode binaries. With S3 resume Off.
// 
// 2     7/13/09 2:46p Sudhirv
// Update with Coding Standards
// 
// 1     7/07/09 4:46p Sudhirv
// Restructure Binaries Created
// 
// 1     5/01/09 7:48p Madhans
// AMIDebug Rx Module. Intial Checkin.
// 
// 1     4/29/09 7:51a Sudhirv
// AMI Debug Rx module created
// 
// 13    12/12/08 5:14p Madhans
// USB Redirecion Module.
// 
// 11    6/26/08 3:09p Sudhirv
// Uploaded after checking coding standards
// 
// 10    8/29/07 3:49p Madhans
// To resolve AMD Platfrom issues.
// 
// 9     8/29/07 12:44p Madhans
// Common code for 4.x and 3.x
// 
// 8     6/13/07 3:16p Madhans
// Copyright Year updated.
// 
// 7     3/12/07 6:19p Madhans
// !!!coding standards!!!!
// 
// 6     3/10/07 2:22p Madhans
// For non PEI debuggers it should return 0.
// 
// 5     3/01/07 10:44a Madhans
// token.h included
// 
// 4     1/22/07 11:36a Madhans
// Modification made for Binary Release 1.04.0003.
// 
// 3     1/05/07 1:05p Ashrafj
// Latest version 1.04.0001 Beta
// Known issues from previous 1.04.000 Beta release has been fixed.
// 
//*****************************************************************

//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	DbgrHelp.c
//
// Description:	File containing the globals for CAR base address & size.
//
//<AMI_FHDR_END>
//**********************************************************************

#include <EFI.h>
#include <AmiPeiLib.h>

#include "misc.h"
#include "AMIPeiDebug.h"
#ifdef ALASKA_SUPPORT
#include "token.h"
#else
#include "tokens.h"
#endif

//**********************************************************************
#if defined (PI_SPECIFICATION_VERSION) && (PI_SPECIFICATION_VERSION >= 0x00010000)
UINTN	AMI_PEIDEBUGGER_DS_BASEADDRESS 	= 0;
UINTN	AMI_PEIDEBUGGER_DS_SIZE			= 0x2048;
#else
const UINTN	AMI_PEIDEBUGGER_DS_BASEADDRESS 	= PEI_DEBUG_DATASECTION_BASEADDRESS;
const UINTN	AMI_PEIDEBUGGER_DS_SIZE			= PEI_DEBUG_DATASECTION_SIZE;
#endif
volatile UINT16 gS3ResumeSupport = AMI_DEBUG_RX_IN_S3_SUPPORT;

VOID CPULib_SaveIdt(DESCRIPTOR_TABLE);

UINTN GetCARBaseAddress()
{
#if defined (PI_SPECIFICATION_VERSION) && (PI_SPECIFICATION_VERSION >= 0x00010000)
    EFI_PEI_SERVICES          **PeiServices;
    VOID *PeiDbgData; 
    EFI_GUID  mPeiDbgBasePpiGuid = EFI_PEI_DBG_BASEADDRESS_PPI_GUID;
    EFI_STATUS Status;
	IDTBASE 	Idtr;

#ifndef	EFIx64
	_asm{
		sidt fword ptr Idtr
	}
#else
    CPULib_SaveIdt(&Idtr);
#endif
    PeiServices = (EFI_PEI_SERVICES **) (*(UINTN*)(Idtr.IDTBaseAddr - sizeof (UINTN)));

    if (PeiServices == NULL)
		return (Idtr.IDTBaseAddr);	//Point to the area after PEI Services
    else
    {
        Status = (**PeiServices).LocatePpi(
                                 PeiServices,
                                 &mPeiDbgBasePpiGuid,  // GUID
                                 0,               // INSTANCE
                                 NULL,            // EFI_PEI_PPI_DESCRIPTOR
                                 &PeiDbgData     // PPI
                                 );
        if (!EFI_ERROR(Status)) 
            return *((UINTN*)PeiDbgData);
        else
            return (Idtr.IDTBaseAddr);
    }
#else
    return AMI_PEIDEBUGGER_DS_BASEADDRESS;
#endif

}

//<AMI_PHDR_START>
//--------------------------------------------------------------------
// Procedure:	IsAmiDbgrBaseValid
//
// Description:	It is a function that helps to behave the status 
//				code redirection through debugger differently 
//				based in SDL tokens in different cases.
//
// Input:		void
//
// Output:		UINT8 
//
//--------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8 IsAmiDbgrBaseValid(void)
{

#if REDIRECTION_ONLY_MODE
	return 1;
#else
#ifndef AMI_PEI_DEBUG_SUPPORT
	return 0;
#else
// if PEI Debugger is enabled
#ifdef	EFIx64
	return 0;
#else
	IDTBASE 	Idtr;
	_asm{
		sidt fword ptr Idtr
	}
#if defined (PI_SPECIFICATION_VERSION) && (PI_SPECIFICATION_VERSION >= 0x00010000)
	// Doubtful code recheck again
	if(Idtr.IDTBaseAddr != NULL)
#else
	if(Idtr.IDTBaseAddr == AMI_PEIDEBUGGER_DS_BASEADDRESS)
#endif
		return 1;
	else
		return 0;
#endif
#endif
#endif
}

//<AMI_PHDR_START>
//--------------------------------------------------------------------
// Procedure:	IsBsp()
//
// Description:	
//
// Input:		void
//
// Output:		UINT8 
//
//--------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8 IsBsp(void)
{
#ifdef	EFIx64
	return 1;
#else
	UINT8 IsBsp = 1;
#define	MSR_XAPIC_BASE				0x1B
#define	XAPIC_BASE_BSP_BIT			8
#define	XAPIC_BASE_BSP_BIT_MASK		(1 << XAPIC_BASE_BSP_BIT)
	_asm
	{
		mov ecx,MSR_XAPIC_BASE
		rdmsr
		and eax,0x100
		cmp eax,0x100
		je  BSP
		mov	IsBsp,0
BSP:
	}	
	return IsBsp;
#endif
}

//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
//**                                                             **//
//**         (C)Copyright 2009, American Megatrends, Inc.        **//
//**                                                             **//
//**                     All Rights Reserved.                    **//
//**                                                             **//
//**   5555 Oakbrook Pkwy, Building 200,Norcross, Georgia 30093  **//
//**                                                             **//
//**                     Phone (770)-246-8600                    **//
//**                                                             **//
//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
