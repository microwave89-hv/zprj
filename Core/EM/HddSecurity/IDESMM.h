//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/HddSecurity/IdeSmm/IDESMM.h 7     12/09/14 1:41a Anbuprakashp $ 
//
// $Revision: 7 $
//
// $Date: 12/09/14 1:41a $
//
//*********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/HddSecurity/IdeSmm/IDESMM.h $
// 
// 7     12/09/14 1:41a Anbuprakashp
// [TAG]  		EIP193600
// [Category]  	Improvement
// [Description]  	Security Enhancement for SMIHandler in HddSecurity
// module
// [Files]  		IDESMM.mak, IDESMM.h, IDESMM.c
// 
// 6     1/08/13 12:41a Rameshr
// [TAG]  		EIP109495
// [Category]  	Improvement
// [Description]  	HddSecurity driver needs to be updated for PI
// specification 1.2
// [Files]  		IdeSmm.c, IdeSmm.dxs, IdeSmm.h, IdeSmm.cif
// 
// 5     9/27/11 3:04a Rajeshms
// [TAG]  		EIP69295
// [Category]  	Improvement
// [Description]  	The Timeout values used by IDE and AHCI drivers are
// made as SDL tokens, so that the timeout values can be varied.
// [Files]  		IdeBusBoard.c, CORE_DXE.sdl, AhciSmm.h, AhciBus.h, IDESMM.h,
// Ata.c, Atapi.c, IdeBus.c, IdeBus.h, IdeBusMaster.c, IdeBusBoard.h
// 
// 4     3/24/11 5:24a Rameshr
// [TAG] - EIP 56827 
// [Category]- BUG FIX
// [Severity]- Minor
// [Symptom] - Buld error from IdeSmm.h 
// [RootCause]- Invalid characters in IdeSmm.h
// [Solution] - Removed the Invalid Charater from IdeSmm.h 
// [Files] - IdeSmm.h
// 
// 3     1/15/10 10:16a Yul
// Coding Standard
//
// 2     4/28/09 6:57p Rameshr
// HDD password support in RAID mode
// EIP:20421
//
// 1     28/02/08 6:40p Anandakrishnanl
// Created new HddSecurity module.  Isolated IdeSecurity and IdeSmm from
// IdeBus driver to be compatable with the AHCI Bus driver.
//
// 2     22/06/07 12:44p Anandakrishnanl
// HardDisk Security Support Module Added.
// Need ACPI Module and SB Module and under Core\Include we updated
// Setup.h.
// Also New IdeBus bin module.
//
// 1     13/04/07 3:08p Anandakrishnanl
// Ide Bus Module - Update source files to comply with AMI coding
// standard"!!!
//
//*********************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:	<IDESMM.h>
//
// Description:	This file contains the Includes, Definitions, typedefs,
//		        Variable and External Declarations, Structure and
//              function prototypes needed for the IDESMM Component
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef _IDESMM_H_
#define _IDESMM_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <Token.h>
#include <AmiDxeLib.h>
#if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x0001000A)&&(CORE_COMBINED_VERSION>=0x4028B)
#include <Protocol\SmmCpu.h>
#include <Protocol\SmmBase2.h>
#include <Protocol\SmmSwDispatch2.h>
#else
#include <Protocol\SmmBase.h>
#include <Protocol\SmmSwDispatch.h>
#endif
#include "IdeSecurity.h"
#include <AmiBufferValidationLib.h>

#ifndef DMA_ATAPI_COMMAND_COMPLETE_TIMEOUT
#define     DMA_ATAPI_COMMAND_COMPLETE_TIMEOUT  16000           // 16Sec
#endif

#ifndef S3_BUSY_CLEAR_TIMEOUT
#define     S3_BUSY_CLEAR_TIMEOUT               10000           // 10Sec
#endif

#ifndef HBA_CAP
#define     HBA_CAP                             0x0000
#endif

#ifndef HBA_CAP_NP_MASK
#define     HBA_CAP_NP_MASK                     0x1F
#endif

#ifndef HBA_PORTS_START
#define     HBA_PORTS_START                     0x0100
#endif

#ifndef HBA_PORTS_REG_WIDTH
#define     HBA_PORTS_REG_WIDTH                 0x0080
#endif

#define     BUSY_CLEAR_TIMEOUT                  1000            // 1Sec
#define     DRDY_TIMEOUT                        1000            // 1Sec
#define     DRQ_TIMEOUT                         10              // 10msec
#pragma pack(1)

typedef struct
{
    UINT8 bFeature;
    UINT8 bSectorCount;
    UINT8 bLbaLow;
    UINT8 bLbaMid;
    UINT8 bLbaHigh;
    UINT8 bDevice;
    UINT8 bCommand;
} COMMAND_BUFFER;

#pragma pack()

EFI_STATUS SMMSecurityUnlockCommand (
    HDD_PASSWORD *pHddPassword 
);

EFI_STATUS SMMIdeNonDataCommand (
    HDD_PASSWORD *pHddPassword,
    IN UINT8     Features,
    IN UINT8     SectorCount,
    IN UINT8     LBALow,
    IN UINT8     LBAMid,
    IN UINT8     LBAHigh,
    IN UINT8     Command );

void ZeroMemorySmm (
    void  *Buffer,
    UINTN Size );

EFI_STATUS
IdeSmmInSmmFunction(
    IN EFI_HANDLE                ImageHandle,
    IN EFI_SYSTEM_TABLE          *SystemTable
 );


/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif

#endif  // _IDESMM_H_

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
