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

//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/HddSmart/IdeSMART.h 10    12/22/11 4:35a Lavanyap $
//
// $Revision: 10 $
//
// $Date: 12/22/11 4:35a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/HddSmart/IdeSMART.h $
// 
// 10    12/22/11 4:35a Lavanyap
// [TAG]  		EIP77259
// [Category]  	Improvement
// [Description]  	Included rollbacked check-ins from ver 6, 7, 8 and made
// it compatible with core 4.6.5.3.
// [Files]  		IdeSMART.c, IdeSMART.h, IdeSMART.mak, IdeSMART.uni,
// IdeSMART.dxs
// 
// 9     3/17/11 10:37a Krishnakumarg
// [TAG] - EIP 55534
// [Category]- Defect
// [Symptom] - Component HddSmart not labeled for CORE 4.6.4.1
// [Solution] - IdeSmart is updated for Core 4.6.4.1
// [Files] - IdeSmart.c,Idesmart.h,IdeSmart.mak,IdeSmart.dxs,IdeSmart.uni,
// IdeSmart.chm
// 
// 5     8/20/10 4:29p Krishnakumarg
// Ide Smart doesn't support the ATA 8 Read Smart Data. EIP#42492
// Corrected datasize for PollPeriod in Selftest funtion
// 
// 4     5/03/10 11:03a Krishnakumarg
// Request additional generic functionality to be added to the IdeSMART
// component.EIP#31559
// 
// 3     1/22/10 10:32a Yul
// Refer to EIP 34207
// 
// 2     1/15/10 9:57a Yul
// coding standard
//
// 1     7/03/08 5:19p Anandakrishnanl
// Added IdeSmart Module after removing IdeSmart.c from Idebus Src Module
//
//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:	<IdeSMART.h>
//
// Description:	This file contains the Includes, Definitions, typedefs,
//		        Variable and External Declarations, Structure and
//              function prototypes needed for the IdeSMART driver
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef _IdeSMART_
#define _IdeSMART_

#ifdef __cplusplus
extern "C" {
#endif

#include <Efi.h>
#include <Token.h>
#include <Dxe.h>
#include <AmiDxeLib.h>
#include "Protocol\PciIo.h"
#include "Protocol\DevicePath.h"
#include "protocol\DriverBinding.h"
#include "protocol\BlockIo.h"
#include "Protocol\PDiskInfo.h"
#include "Protocol\PIDEController.h"
#include "Protocol\PIDEBus.h"
#include "Protocol\PAhciBus.h"
#include <Protocol/AMIPostMgr.h>
#include <Protocol/SimpleTextIn.h>

HDD_SMART_INIT_PROTOCOL *gHddSmartInitProtocol;

#define     ZeroMemory( Buffer, Size ) pBS->SetMem( Buffer, Size, 0 )

#define     FIS_REGISTER_D2H               0x34           // Device To Host

#pragma pack(1)
typedef struct
{
    UINT8  Ahci_Dsfis[0x1C];              // DMA Setup Fis
    UINT8  Ahci_Dsfis_Rsvd[0x04];
    UINT8  Ahci_Psfis[0x14];              // PIO Setip Fis
    UINT8  Ahci_Psfis_Rsvd[0x0C];
    UINT8  Ahci_Rfis[0x14];               // D2H Register Fis
    UINT8  Ahci_Rfis_Rsvd[0x04];
    UINT64 Ahci_Sdbfis;                    // Set Device Bits Fis
    UINT8  Ahci_Ufis[0x40];                // Unkonw FIS
    UINT8  Ahci_Ufis_Rsvd[0x60];
} AHCI_RECEIVED_FIS;
#pragma pack()

UINTN EfiValueToString (
    IN OUT CHAR16 *Buffer,
    IN INT64      Value,
    IN UINTN      Flags,
    IN UINTN      Width );

EFI_STATUS GetHiiString (
    IN EFI_HII_HANDLE HiiHandle,
    IN STRING_REF     Token,
    IN OUT UINTN      *pDataSize,
    OUT EFI_STRING    *ppData );

EFI_STATUS CommonNonDataHook (
    IN VOID              *BusInterface,
    IN COMMAND_STRUCTURE CommandStructure,
    IN BOOLEAN           ModeFlag );

EFI_STATUS InitSMARTSupport (
    IN VOID    *BusInterface,
    IN BOOLEAN ModeFlag );

EFI_STATUS SMARTReturnStatusWrapper (
    IN VOID    *BusInterface,
    IN BOOLEAN ModeFlag );

EFI_STATUS InstallSMARTInterface (
    IN VOID    *BusInterface,
    IN BOOLEAN ModeFlag );

EFI_STATUS UnInstallSMARTInterface (
    IN VOID    *BusInterface,
    IN BOOLEAN ModeFlag );

//---------------------------------------------------------------------------
// SMART DIAGNOSTICS SUPPORT START
//---------------------------------------------------------------------------
//#if SMART_DIAGNOSTICS_SUPPORT

EFI_STATUS SMARTSelfTest (
    IN IDE_SMART_INTERFACE *This,
    IN UINT8               SelfTestType,
    OUT UINT16              *PollPeriod );

EFI_STATUS SMARTSelfTestStatus (
    IN IDE_SMART_INTERFACE *This,
    OUT UINT8              *TestStatus );

EFI_STATUS SMARTReturnStatus (
    IN IDE_SMART_INTERFACE *This );

EFI_STATUS SendSmartCommand (
    IN IDE_SMART_INTERFACE  *This,
    IN UINT8                SubCommand,
    IN UINT8                AutoSaveEnable,    //OPTIONAL
    IN UINT8                SelfTestType       //OPTIONAL
               );
EFI_STATUS SmartReadData (
    IN  IDE_SMART_INTERFACE  *This,
    IN  UINT8                SubCommand,
    OUT VOID                 *Buffer,
    IN  UINT8                LogAddress,   //OPTIONAL    
    IN  UINT8                SectorCount   //OPTIONAL 
);

EFI_STATUS SmartWriteData (
    IN IDE_SMART_INTERFACE  *This,
    IN UINT8                SubCommand,
    IN VOID                 *Buffer,
    IN UINT8                LogAddress,   
    IN UINT8                SectorCount   
);

EFI_STATUS SMARTAbortSelfTest (
	IN 	IDE_SMART_INTERFACE			*This
);

EFI_STATUS SMARTGetSmartData (
	IN 	IDE_SMART_INTERFACE			*This,
    OUT UINT8                       **SmartData
);

//#endif      /* SMART DIAGNOSTICS SUPPORT END */

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif

#endif

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