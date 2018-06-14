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
// $Header: /Alaska/BIN/Modules/AMIDebugRx/binaries/PeiAMIDebugRx/DBGR/DbgrHdr.c 11    4/04/12 4:56p Sudhirv $
//
// $Revision: 11 $
//
// $Date: 4/04/12 4:56p $
//*****************************************************************
//*****************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/AMIDebugRx/binaries/PeiAMIDebugRx/DBGR/DbgrHdr.c $
// 
// 11    4/04/12 4:56p Sudhirv
// To Avoid Build errors in special cases.
// 
// 10    4/03/12 4:43p Sudhirv
// To avoid Build errors for redirection modes.
// 
// 9     3/27/12 12:02p Sudhirv
// [TAG]  		EIP80406
// [Category]  	Improvement
// [Description]  	Debugger support for Dynamic pci express base token
// 
// 8     3/13/12 10:47a Sudhirv
// [TAG]  		EIP60224
// [Category]  	Improvement
// [Description]  Function implement When broken in SMM, show the register
// context for 'outside' SMM.
// 
// [TAG]  		EIP80406
// [Category]  	Improvement
// [Description]  Debugger support for Dynamic pci express base token
// 
// [TAG]  		EIP81423
// [Category]  	Improvement
// [Description]  VeB Debugger - Improve the EFI tab's Handle Display
// feature
// 
// [TAG]  		EIP84201
// [Category]  	Improvement
// [Description]  AMIDebugRx\Debugger Target modules usage of the Port 80
// must be controlable
// 
// 7     8/19/11 8:28p Sudhirv
// Fix To get PCIExBaseaddress correctly for ReadPCI.
// 
// 6     7/22/11 12:19p Sudhirv
// [TAG]  		Compilation Error
// [Description]  	To avoid Compilation errors in some Projects.
// [Files]  		DbgrHdr.c
// 
// 5     7/12/11 5:23p Sudhirv
// [TAG]  		SMM Info
// [Category]  	New Feature
// [Description]  	To support send SMM Info to host
// 
// 4     3/17/11 7:57a Sudhirv
// Support to Boot with S3 Resume in Core_4.6.5.0
// 
// 3     3/09/11 8:21a Sudhirv
// EIP 53658 - AMIDebugRx\Debugger support for PI 1.1
// 
// 2     7/17/09 7:15p Madhans
// DebugRx 1.30.0022
// 
// 2     7/13/09 2:49p Sudhirv
// Updated with Coding Standards
// 
// 1     7/07/09 4:46p Sudhirv
// Restructure Binaries Created
// 
// 1     5/01/09 7:48p Madhans
// AMIDebug Rx Module. Intial Checkin.
// 
// 1     4/29/09 7:52a Sudhirv
// AMI Debug Rx module created
// 
// 8     3/27/09 8:38a Sudhirv
// Updated Coding Standards.
// 
// 7     8/29/07 12:47p Madhans
// Common code for 4.x and 3.x
// 
// 6     6/13/07 3:16p Madhans
// Copyright Year updated.
// 
// 5     2/27/07 5:01p Madhans
//
//*****************************************************************

//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	DbgrHdr.c
//
// Description:	File containing the globals for CAR base address & size.
//				Also the code which make use of this so that it can be
//				integrated as it is Debugger eModule of binary.
//
//<AMI_FHDR_END>
//**********************************************************************

#include "pei.h"
#include "misc.h"
#include "AMIPeiDebug.h"
//**********************************************************************
#ifdef ALASKA_SUPPORT
#define CAR_Start_Addr		PEI_DEBUG_DATASECTION_BASEADDRESS		// CAR Size = 8k
#define CAR_End_Addr		PEI_DEBUG_DATASECTION_BASEADDRESS + PEI_DEBUG_DATASECTION_SIZE
#define Code_Start_Addr			0xffffffff - FLASH_SIZE
#define Code_End_Addr			0xffffffff			
#else
#define CAR_Start_Addr			DATA_STACK_BASEADDRESS		// CAR Size = 64k
#define CAR_End_Addr			(DATA_STACK_BASEADDRESS | 0x10000)
#define Code_Start_Addr			0xffdfffff		// Max BootBlock Size = 4Gig - 2MB
#define Code_End_Addr			0xffffffff			
#endif

#ifndef SW_SMI_IO_ADDRESS
#define SW_SMI_IO_ADDRESS 0
#endif
#ifndef SMM_BASE_SAVE_STATE_OFFSET
#define SMM_BASE_SAVE_STATE_OFFSET 0
#endif
#ifndef MAX_SMM_SAVE_STATE_SIZE
#define MAX_SMM_SAVE_STATE_SIZE 0
#endif
#ifndef SMM_BSP_BASE
#define SMM_BSP_BASE 0
#endif
#ifndef TSEG_SIZE
#define TSEG_SIZE 0
#endif
#ifndef PCIEX_BASE_ADDRESS
#define PCIEX_BASE_ADDRESS 0
#endif
#ifndef DYNAMIC_PCIEXBASE_SUPPORT
#define DYNAMIC_PCIEXBASE_SUPPORT 0
#endif
#ifndef DBG_WRITE_IO_SUPPORT
#define DBG_WRITE_IO_SUPPORT 0
#endif
#ifndef DBG_WRITE_IO_80_SUPPORT
#define DBG_WRITE_IO_80_SUPPORT 0
#endif

//To support send SMM Info to host
volatile UINT16 gSMIIOAddress = SW_SMI_IO_ADDRESS;
volatile UINTN gSMMBaseSaveState = SMM_BASE_SAVE_STATE_OFFSET;
volatile UINTN gSMMSaveStateSize = MAX_SMM_SAVE_STATE_SIZE;
volatile UINTN gSMMBspBase = SMM_BSP_BASE;
volatile UINTN gTsegSize = TSEG_SIZE;
//**********************************************************************

volatile UINTN gPCIEXBaseAddress = PCIEX_BASE_ADDRESS;

//EIP 80406 - Debugger support for Dynamic pci express base token
#ifdef DYNAMIC_PCIEXBASE_SUPPORT
volatile UINTN gDynamicPCIExBase = DYNAMIC_PCIEXBASE_SUPPORT;
#else
volatile UINTN gDynamicPCIExBase = 0;
#endif

volatile UINTN gDbgWriteIOSupport = DBG_WRITE_IO_SUPPORT;
volatile UINTN gDbgWriteIO80Support = DBG_WRITE_IO_80_SUPPORT;

//**********************************************************************
//<AMI_SHDR_START>
//
// Name:		PeiDbgDataSection of type PEI_DBG_DATA_SECTION
//
// Description:	The following global data structure is for relocation purpose
//				in order to support debugging after the debugger data section
//				is relocated. This second parameter of the data structure has
//				to be updated by the debugger service PEIM to point to relocated
//				data section into memory.The code section has this module
//				has to relocated before the update of second parameter.
//
//<AMI_SHDR_END>
//**********************************************************************
#if defined (PI_SPECIFICATION_VERSION) && (PI_SPECIFICATION_VERSION >= 0x00010000)
PEI_DBG_DATA_SECTION PeiDbgDataSection = {	
	"DBGR",
	0		//This will be updated by debugger service PEIM
};					//after the DBgr data section is relocated to memory from CAR
#else
PEI_DBG_DATA_SECTION PeiDbgDataSection = {	
	"DBGR",
	PEI_DEBUG_DATASECTION_BASEADDRESS		//This will be updated by debugger service PEIM
};					//after the DBgr data section is relocated to memory from CAR

#endif

UINTN GetCARBaseAddress()
{
    EFI_PEI_SERVICES          **PeiServices;
    VOID *PeiDbgData; 
    EFI_GUID  mPeiDbgBasePpiGuid = EFI_PEI_DBG_BASEADDRESS_PPI_GUID;
    EFI_STATUS Status;

	if((PeiDbgDataSection.DATABASEADDRESS)==NULL)
	{
		IDTBASE 	Idtr;
		_asm{
			sidt fword ptr Idtr
		}
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
	}
	else {
		return((UINTN)PeiDbgDataSection.DATABASEADDRESS);
	}
}


//<AMI_PHDR_START>
//--------------------------------------------------------------------
// Procedure:	IsDbgrInCAR
//
// Description:	Internal Helper function.
//
// Input:		none
//
// Output:		1 - yes or 0 - no (UINT32)
//
//--------------------------------------------------------------------
//<AMI_PHDR_END>
UINT32	IsDbgrInCAR()
{
#if defined (PI_SPECIFICATION_VERSION) && (PI_SPECIFICATION_VERSION >= 0x00010000)
	if((PeiDbgDataSection.DATABASEADDRESS)==NULL)
#else
	if(PEI_DEBUG_DATA_BASEADDRESS == PEI_DEBUG_DATASECTION_BASEADDRESS)
#endif
		return 1;	//yes
	else
		return 0;	//no
}

//<AMI_PHDR_START>
//--------------------------------------------------------------------
// Procedure:	IsAddrValidInCAR
//
// Description:	Internal Helper function.
//
// Input:		UINT64 Addr
//
// Output:		1 - TRUE OR 0 - FALSE (INTN)
//
//--------------------------------------------------------------------
//<AMI_PHDR_END>
INTN IsAddrValidInCAR (UINT64 Addr) {

	if (Addr >= CAR_Start_Addr && Addr <= CAR_End_Addr) 
		return(1);
	else
		return(0);
}

//<AMI_PHDR_START>
//--------------------------------------------------------------------
// Procedure:	IsAddrValidInCode
//
// Description:	Internal Helper function.
//
// Input:		UINT64 Addr
//
// Output:		1 OR 0 (INTN)
//
//--------------------------------------------------------------------
//<AMI_PHDR_END>
INTN IsAddrValidInCode (UINT64 Addr) {

	if (Addr >= Code_Start_Addr && Addr <= Code_End_Addr) 
		return(1);
	else
		return(0);
}

//<AMI_PHDR_START>
//--------------------------------------------------------------------
// Procedure:	Get_CAR_EndAddr
//
// Description:	Internal Helper function.
//
// Input:		none
//
// Output:		CAR_End_Addr (UINTN)
//
//--------------------------------------------------------------------
//<AMI_PHDR_END>
UINTN	Get_CAR_EndAddr()
{
	return (CAR_End_Addr);
}

//<AMI_PHDR_START>
//--------------------------------------------------------------------
// Procedure:	Get_Code_EndAddr
//
// Description:	Internal Helper function.
//
// Input:		none
//
// Output:		Code_End_Addr (UINTN)
//
//--------------------------------------------------------------------
//<AMI_PHDR_END>
UINTN	Get_Code_EndAddr()
{
	return (Code_End_Addr);
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
