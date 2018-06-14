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
// $Header: /Alaska/BIN/Modules/AMIDebugRx/binaries/PeiAMIDebugRx/XPORT/XportHdr.c 9     4/04/12 4:57p Sudhirv $
//
// $Revision: 9 $
//
// $Date: 4/04/12 4:57p $
//*****************************************************************
//*****************************************************************
//
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/AMIDebugRx/binaries/PeiAMIDebugRx/XPORT/XportHdr.c $
// 
// 9     4/04/12 4:57p Sudhirv
// To Avoid Build errors in special cases.
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
// 7     7/12/11 5:27p Sudhirv
// [TAG]  		EIP62342
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Target Crashes when Debugger enabled and AMIDebugRx is in
// Checkpoint mode
// [RootCause]  	Debugger is Enabled and AMIDebugRx device is connected in
// checkpoint mode. Target MAchine is unaware of the type of host
// connected in DXE phase.
// [Solution]  	Support to not crash when Debugger enabled and Rx switch
// in Checkpoint Mode.
// 
// 6     3/17/11 8:09a Sudhirv
// Support to Boot with S3 Resume in Core_4.6.5.0
// 
// 5     3/09/11 8:27a Sudhirv
// EIP 53658 - AMIDebugRx\Debugger support for PI 1.1
// 
// 4     2/15/10 8:05a Mallikarjunanv
// Updated after fix for EIP 35101 - Binary Debug Rx module doesn't report
// BIOS TAG correctly.
// 
// 3     9/30/09 3:03p Sudhirv
// For Debugger 1.31.0023_PreAlpha
// 
// 2     7/13/09 2:53p Sudhirv
// Updated with Coding Standards
// 
// 1     7/07/09 4:47p Sudhirv
// Restructure Binaries Created
// 
// 2     5/05/09 8:05p Madhans
// Use the timestamp.h instead of timstamp.mak to avoid the octal issues.
// 
// 1     5/01/09 7:48p Madhans
// AMIDebug Rx Module. Intial Checkin.
// 
// 1     4/29/09 7:52a Sudhirv
// AMI Debug Rx module created
//
// 8     3/27/09 8:43a Sudhirv
// Updated Coding Standards.
//
// 7     8/29/07 12:59p Madhans
// Common code for 4.x and 3.x
//
// 6     6/13/07 3:17p Madhans
// Copyright Year updated.
//
// 5     3/12/07 6:19p Madhans
// !!!coding standards!!!!
//
// 4     1/22/07 11:43a Madhans
// Modification made for Binary Release 1.04.0003.
//
// 4     1/05/07 6:15p Madhan
//
// 3     1/05/07 1:05p Ashrafj
// Latest version 1.04.0001 Beta
// Known issues from previous 1.04.000 Beta release has been fixed.
//
//
//*****************************************************************
//*****************************************************************

//**********************************************************************
//<AMI_FHDR_START>
//
// Name:		XportHdr.c
//
// Description:	File containing the globals for CAR base address & size.
//				Also the code which make use of this so that it can be
//				integrated as it is Debugger eModule of binary.
//
//<AMI_FHDR_END>
//**********************************************************************
#include "efi.h"
#include "Pei.h"

#include "misc.h"
#ifndef	EFIx64
#include "AMIPeiDebug.h"
#else
#include "AMIPeiDebugX64.h"
#include "AsmDbgrx64Libs.h"
#endif
#include "timestamp.h"

#define CONVERT_TO_STRING(a) #a
#define STR(a) CONVERT_TO_STRING(a)
#ifndef DBG_WRITE_IO_80_SUPPORT
#define DBG_WRITE_IO_80_SUPPORT 0
#endif

const char *sTargetProjectTag= STR(TARGET_PROJECT_TAG);

//EIP 62342 - Support to not crash when Debugger enabled and Rx switch in Checkpoint Mode.
UINTN gAMIDebuggerEnabled = REDIRECTION_ONLY_MODE;

volatile UINTN gDbgWriteIO80Support = DBG_WRITE_IO_80_SUPPORT;

typedef struct {
	UINT16		Year;
	UINT8		Month;
	UINT8		Day;
	UINT8		Hour;
	UINT8		Minute;
	UINT8		Second;
} DateTime_T;

VOID AddExtDelay();

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
	"XPRT",
	NULL
};
#else
PEI_DBG_DATA_SECTION PeiDbgDataSection = {
	"XPRT",
	PEI_DEBUG_DATASECTION_BASEADDRESS
};

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
#ifndef	EFIx64
    	_asm{
    		sidt fword ptr Idtr
    	}
#else
        GetIdtr(&Idtr);
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
// Output:		1 for yes & 0 for no (UINT32)
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
// Procedure:	IoRead32
//
// Description:	Internal Helper function. Reads 32-bit value from IO port
//
// Input:		UINT16 Port
//
// Output:		UINT32 - port data
//
//--------------------------------------------------------------------
//<AMI_PHDR_END>
UINT32 IoRead32(UINT16 Port)
{
#ifdef	EFIx64
	return IoReadDword(Port);
#else
	_asm {
		mov dx, Port
		in eax, dx
	}
#endif
}

//<AMI_PHDR_START>
//--------------------------------------------------------------------
// Procedure:	Stall
//
// Description:	Internal Helper function.
//
// Input:		UINTN Usec (microseconds)
//
// Output:		void
//
//--------------------------------------------------------------------
//<AMI_PHDR_END>
VOID Stall (UINTN Usec)
{
    UINTN   Counter = (Usec * 7)/2; // 3.58 count per microsec
    UINTN   i;
    UINT32  Data32;
    UINT32  PrevData;

    PrevData = IoRead32(PM_BASE_ADDRESS + 8);
    for (i=0; i < Counter; ) {
       Data32 = IoRead32(PM_BASE_ADDRESS + 8);
        if (Data32 < PrevData) {        // Reset if there is a overlap
            PrevData=Data32;
            continue;
        }
        i += (Data32 - PrevData);
		PrevData=Data32; // FIX need to find out the real diff betweek different count.
    }
}

//<AMI_PHDR_START>
//--------------------------------------------------------------------
// Procedure:	AddDelay
//
// Description:	Internal Helper function.
//
// Input:		is currently designed to provide either software delay
//				or through ACPI timer who has fixed frequency.
//
// Output:		void
//
//--------------------------------------------------------------------
//<AMI_PHDR_END>
void	AddDelay()
{
	Stall(10*1000);	//for 10 milliseconds
	return;
}

//<AMI_PHDR_START>
//--------------------------------------------------------------------
// Procedure:	AddUsbDelay
//
// Description:	Internal Helper function.
//
// Input:		is currently designed to provide either software delay
//				or through ACPI timer who has fixed frequency.
//
// Output:		void
//
//--------------------------------------------------------------------
//<AMI_PHDR_END>
void	AddUsbDelay()
{
	Stall(2*1000);	//for 2 milliseconds
	return;
}

//<AMI_PHDR_START>
//--------------------------------------------------------------------
// Procedure:	AddSpecialDelay()
//
// Description:	Internal Helper function.
//
// Input:		void
//
// Output:		void
//
//--------------------------------------------------------------------
//<AMI_PHDR_END>
void AddSpecialDelay()
{
#if !PEI_CACHE_ENABLED
	if(IsDbgrInCAR())
		AddExtDelay();
	else{
		UINTN CriticalDelay = 60;
		while(CriticalDelay--)
			AddExtDelay();
	}
#else
  UINTN CriticalDelay = 60;

CriticalDelay = 1; // TESTING...
	while(CriticalDelay--)
		AddExtDelay();
#endif
}

//<AMI_PHDR_START>
//--------------------------------------------------------------------
// Procedure:	AddExtDelay()
//
// Description:	Internal Helper function.
//
// Input:		void
//
// Output:		void
//
//--------------------------------------------------------------------
//<AMI_PHDR_END>
void AddExtDelay()
{
//	UINT8	i = 35;		//providing 250 ms delay
	UINT8	i = 25;
	i =1; // TESTING...
	while(i--)
		AddDelay();
	return;
}

//<AMI_PHDR_START>
//--------------------------------------------------------------------
// Procedure:	GetBuildTime()
//
// Description:	Sends the Build Time Details
//
// Input:		void*
//
// Output:		void
//
//--------------------------------------------------------------------
//<AMI_PHDR_END>

#define Str2No(A)	(A - '0')
	
#define TwoDigitStr2BCD(String) (Str2No(String[0])*0x10+Str2No(String[1]))

VOID GetBuildTime(void *Buffer)
{
	UINT8 *strYear = FOUR_DIGIT_YEAR;
	UINT8 *strMonth = TWO_DIGIT_MONTH;
	UINT8 *strDay = TWO_DIGIT_DAY;
	UINT8 *strHour = TWO_DIGIT_HOUR;
	UINT8 *strMin = TWO_DIGIT_MINUTE;
	UINT8 *strSec = TWO_DIGIT_SECOND;


	((DateTime_T*)Buffer)->Year=(Str2No(strYear[0])*0x1000+Str2No(strYear[1])*0x100+Str2No(strYear[2])*0x10+Str2No(strYear[3]));
	((DateTime_T*)Buffer)->Month=TwoDigitStr2BCD(strMonth);
	((DateTime_T*)Buffer)->Day=TwoDigitStr2BCD(strDay);
	((DateTime_T*)Buffer)->Hour=TwoDigitStr2BCD(strHour);
	((DateTime_T*)Buffer)->Minute=TwoDigitStr2BCD(strMin);
	((DateTime_T*)Buffer)->Second=TwoDigitStr2BCD(strSec);
	return;
}


//#endif
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
