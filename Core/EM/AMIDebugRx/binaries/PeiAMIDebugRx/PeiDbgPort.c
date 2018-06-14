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
// $Header: /Alaska/BIN/Modules/AMIDebugRx/binaries/PeiAMIDebugRx/PeiDbgPort.c 10    4/04/12 4:55p Sudhirv $
//
// $Revision: 10 $
//
// $Date: 4/04/12 4:55p $
//*****************************************************************
//*****************************************************************
//
//	PeiSer.c
//		
//
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/AMIDebugRx/binaries/PeiAMIDebugRx/PeiDbgPort.c $
// 
// 10    4/04/12 4:55p Sudhirv
// To Avoid Build errors in special cases.
// 
// 9     3/13/12 10:47a Sudhirv
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
// 8     4/01/11 2:46p Sudhirv
// [TAG]  		EIP56888
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	DEBURX S3 resume hang 0x05 problem on Sabine platform
// [Solution]  	Fixed the Initialization of the Debug Port to not differ
// with Normal boot or S3 Resume.
// [Files]  		PeiDbgPort.c
// 
// 7     3/16/11 4:43p Sudhirv
// Changes to Support Older Core before 4.6.5.0
// 
// 6     3/09/11 8:20a Sudhirv
// EIP 53658 - AMIDebugRx\Debugger support for PI 1.1
// 
// 5     9/22/10 7:09p Sudhirv
// 4.6.2_AMIDebugRx_2.01.0026_Beta Release
// 
// 4     2/22/10 4:17p Madhans
// 1.32
// 
// 4     10/19/09 7:25a Sudhirv
// Updated to Reduce S3 Resume wake time and fix SIO Issue
// 
// 3     9/30/09 3:05p Sudhirv
// For Debugger 1.31.0023_PreAlpha
// 
// 2     7/13/09 2:48p Sudhirv
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
// 11    3/27/09 8:45a Sudhirv
// Updated Coding Standards.
// 
// 10    8/29/07 1:00p Madhans
// Common code for 4.x and 3.x
// 
// 9     6/13/07 3:16p Madhans
// Copyright Year updated.
// 
// 8     3/13/07 4:00p Ashrafj
// Update for Coding standard
// 
// 7     3/06/07 7:51p Ashrafj
// Checkpoint error code added for improper chipset init porting support
// form the Aptio Core.
// 
// 6     1/22/07 11:41a Madhans
// Modification made for Binary Release 1.04.0003.
// 
// 10    1/05/07 6:15p Madhan
// 
// 9     1/05/07 1:05p Ashrafj
// Latest version 1.04.0001 Beta
// Known issues from previous 1.04.000 Beta release has been fixed.
// 
// 8     12/26/06 7:07p Ashrafj
// Support added to support the Aptio 4.5 x64 EFI BIOS (use latest
// Host.zip).
// PEI Debugger in FV_MAIN (use new PEIDEBUGFIXUP).
// Support added for StatusCode redirection without Debug feature enabled
// (not working if DXE only and x64 is enabled).
// Plus, some new SDL tokens defined to support the Aptio 4.5 build
// process in Debug or non-debug mode.
// All the components of Debugger eModule in source form.
// 
// 7     12/15/06 4:51p Ashrafj
// Updated the Debugger eModule sources to support the CAR base address
// define in the APtio 4.5 project SDL token itself.
// Move the PEI Debugger modules (except PeiDebugSupport) from FV_BB to
// FV_MAIN to avoid insufficient space problem in PEI. Note that for this
// changes the Aptio 4.5 project should have the new version 0.4
// PEIDEBUGFIXUP utility build tool with CORE.MAK modified (Refer Santa
// Rosa project).
// 
// 6     6/27/06 11:44a Ashrafj
// New feature added: 
// To enable the PEI Debug support after system memory is installed, based
// on build option provided through a new SDL token named
// "PEI_DEBUG_SUPPORT_AFTER_MEMORY".
// 
// 5     4/21/06 12:38p Ashrafj
// Code cleanup.
// 
// 4     3/15/06 7:41p Ashrafj
// Modfication done to provide the Binary integration for Aptio 4
// projects.
// 
// 3     12/22/05 12:42p Ashrafj
// Changes done to support the complete Chipset template porting.
// 
// To use this changes, make sure to have the latest Board components of
// CPU, SB and SIO, which have the following ELINKS ported:
// - SBPEIDBG_Initialize,
// - CPUPEIDBG_Initialize,
// - SIOPEIDBG_Initialize,
// - SBPEIDBG_InitUsbEhci.
// 
// 2     12/15/05 12:13p Ashrafj
// Minor reorganisation of Chipset porting method.
// 
// 1     11/29/05 6:04p Markw
// 
// 1     10/19/05 10:54a Felixp
// 
//
//*****************************************************************
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:		peidbgport.c
//
// Description:	Calls the chipset elink and calls the initializartion  
//				routines of debug port.
//
//<AMI_FHDR_END>
//**********************************************************************

#ifndef ALASKA_SUPPORT
#include "Efi.h"
#include "SimpleCpuIoLib.h"
#else
#include <Efi.h>
#endif
#include "AmiDebugPort.h"
#include "AMIPeiDebug.h"

/////////////////////////////Porting definitions////////////////
#ifdef ALASKA_SUPPORT
#include "token.h"
#else
#include "tokens.h"
#endif

#ifdef	ALASKA_SUPPORT
#ifdef PEI_DBG_INIT_LIST
extern PEI_INIT_FUNCTION PEI_DBG_INIT_LIST EndOfInitList;
PEI_INIT_FUNCTION* PeiDebuggerInitList [] = {PEI_DBG_INIT_LIST NULL};
#endif
#endif

#ifdef	ALASKA_SUPPORT
#ifdef PEI_DBG_S3_INIT_LIST
extern PEI_INIT_FUNCTION PEI_DBG_S3_INIT_LIST EndOfInitS3List;
PEI_INIT_FUNCTION* PeiDebuggerS3InitList [] = {PEI_DBG_S3_INIT_LIST NULL};
#endif
#endif

#ifdef	ALASKA_SUPPORT
#ifdef IS_S3
extern DBG_IS_S3 IS_S3 EndOfS3InitList;
DBG_IS_S3 * IsDbgInS3[] = {IS_S3 NULL};
#endif
#endif

#if defined PI_SPECIFICATION_VERSION 
#if PI_SPECIFICATION_VERSION >= 0x00010000
const UINTN	AMI_PEIDEBUGGER_DS_BASEADDRESS 	= 0;
#else
const UINTN	AMI_PEIDEBUGGER_DS_BASEADDRESS 	= PEI_DEBUG_DATASECTION_BASEADDRESS;
#endif
#else
const UINTN	AMI_PEIDEBUGGER_DS_BASEADDRESS 	= PEI_DEBUG_DATASECTION_BASEADDRESS;
#endif

#ifndef ALASKA_SUPPORT
extern EFI_STATUS SBPEIDBG_Initialize(PEI_DBG_PORT_INFO *DebugPort);
extern EFI_STATUS CPUPEIDBG_Initialize(PEI_DBG_PORT_INFO *DebugPort);
extern EFI_STATUS SIOPEIDBG_Initialize(PEI_DBG_PORT_INFO *DebugPort);
#ifdef USB_DEBUGGER
extern EFI_STATUS SBPEIDBG_InitUsbEhci(PEI_DBG_PORT_INFO *DebugPort);
#endif
#endif;

#ifndef DBG_WRITE_IO_80_SUPPORT
DBG_WRITE_IO_80_SUPPORT 0
#endif
//---->EIP 38453
volatile UINT16 gS3ResumeSupport = AMI_DEBUG_RX_IN_S3_SUPPORT;
volatile UINTN gDbgWriteIO80Support = DBG_WRITE_IO_80_SUPPORT;

//---->EIP 38453

//<AMI_PHDR_START>
//--------------------------------------------------------------------
// Procedure:	ExecutePeiDebuggerInitList()
//
// Description:	Internal Helper function to invoke ELINKS.
//
// Input:		PEI_DBG_PORT_INFO	*DebugPort
//
// Output:		void
//
//--------------------------------------------------------------------
//<AMI_PHDR_END>
VOID 
ExecutePeiDebuggerInitList(
	IN OUT	PEI_DBG_PORT_INFO	*DebugPort
)
{
#ifdef	ALASKA_SUPPORT
	UINTN i;
	
	if(!PeiDebuggerInitList){
		if(gDbgWriteIO80Support)	
			IoWrite8(0x80,0xD0);	//err code for No elinks found
		while(1);
	}
	for(i=0; PeiDebuggerInitList[i]; i++) PeiDebuggerInitList[i](DebugPort);
#else
	SBPEIDBG_Initialize(DebugPort);
	CPUPEIDBG_Initialize(DebugPort);
	SIOPEIDBG_Initialize(DebugPort);
#ifdef USB_DEBUGGER
	SBPEIDBG_InitUsbEhci(DebugPort);
#endif
#endif
}

//<AMI_PHDR_START>
//--------------------------------------------------------------------
// Procedure:	ExecutePeiDebuggerS3InitList()
//
// Description:	Internal Helper function to invoke ELINKS.
//
// Input:		PEI_DBG_PORT_INFO	*DebugPort
//
// Output:		void
//
//--------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
ExecutePeiDebuggerS3InitList(
	IN OUT	PEI_DBG_PORT_INFO	*DebugPort
)
{
#ifdef	ALASKA_SUPPORT
	UINTN i;
	for(i=0; PeiDebuggerS3InitList[i]; i++) PeiDebuggerS3InitList[i](DebugPort);
#else
	SIOPEIDBG_Initialize(DebugPort);
#endif
}
////////////Routine part of Chipset Porting template/////////////////////

void Initialise(PEI_DBG_PORT_INFO *DebugPort);
void InitPeiDebugPortInterface(PEI_DBG_PORT_INFO *DebugPort, UINTN SetupFlag, UINTN IDTBaseAddress);
/////////////////////////////////////////////////////////////////////////

//<AMI_PHDR_START>
//--------------------------------------------------------------------
// Procedure:	InitMain
//
// Description:	entrypoint for the PeiDbgPort, the module init the specific
//				chipset.
//
// Input:		void
//
// Output:		void
//
//--------------------------------------------------------------------
//<AMI_PHDR_END>
void InitMain(UINTN	IDTBASEADDR)
{
	PEI_DBG_PORT_INFO	DebugPort;
	UINTN				PeiDbgSetupFlag;
	UINT8				Val;

	PEIDebugData_T		*pData = (PEIDebugData_T *)IDTBASEADDR;
	SerXPortGblData_T	*SerData = (SerXPortGblData_T *)pData->XportLocalVar;
	
#if	PEI_DEBUG_SUPPORT_AFTER_MEMORY
	PeiDbgSetupFlag = 1;
#else
	PeiDbgSetupFlag = 0;
#endif
	SerData->m_IsHostConnected = 0;

//---->EIP 38453
	// If AMI_DEBUG_RX_IN_S3_SUPPORT is ON AmidebugRx should initialize for both S3 and normal boot
	if(gS3ResumeSupport) 
	{	
		// EIP 56888 - DEBURX S3 resume hang 0x05 problem on Sabine platform
		// If SDL Token is ON then there must be no difference for normal boot or S3 Resume
		SerData->m_IsPeiDbgIsS3 = 1;
		Initialise(&DebugPort);

		ExecutePeiDebuggerInitList(&DebugPort);

		InitPeiDebugPortInterface(&DebugPort,PeiDbgSetupFlag,IDTBASEADDR);
	}
	else	// else SDL token is OFF AMIDebugRx should be init only if normal boot.
	{	
		//To find if PeiDbgPort is happening for normal boot or for S3 while resume
		Val = IsDbgInS3[0]();	//Hook will return 1 if SBPeiDbg_Initialize is there else 0
		if(!Val)
		{	// 0 returned - Normal Boot
			SerData->m_IsPeiDbgIsS3 = 1;
			Initialise(&DebugPort);
	
			ExecutePeiDebuggerInitList(&DebugPort);
	
			InitPeiDebugPortInterface(&DebugPort,PeiDbgSetupFlag,IDTBASEADDR);
		}
		else
		{	//1 returned - Returning from S3
			ExecutePeiDebuggerS3InitList(&DebugPort);
			SerData->m_IsPeiDbgIsS3 = 0;
		}
//---->EIP 38453
	}
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
