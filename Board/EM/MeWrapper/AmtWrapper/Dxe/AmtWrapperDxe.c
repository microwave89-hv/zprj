//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.            **
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
//
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/AmtWrapper/AmtWrapperDxe/AmtWrapperDxe.c 10    6/18/14 3:08a Larryliu $
//
// $Revision: 10 $
//
// $Date: 6/18/14 3:08a $
//
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/AmtWrapper/AmtWrapperDxe/AmtWrapperDxe.c $
// 
// 10    6/18/14 3:08a Larryliu
// [TAG]  		EIP173999
// [Category]  	Improvement
// [Description]  	[HWR]Remove useless comments from Intel ME
// component.(except RC)
// [Files]  		AmtWrapperDxe.c
// 
// 8     5/14/14 9:52p Tristinchou
// [TAG]  		EIP167030
// [Category]  	Improvement
// [Description]  	Remove the variable runtime attribute and keep original
// attributes.
// 
// 7     9/12/13 5:26a Klzhan
// [TAG]  		EIPNone
// [Category]  	Improvement
// [Description]  	Correct gSerialOverLanDevicePath
// 
// 6     4/18/13 1:55a Klzhan
// [TAG]  		EIP119190
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	BIOS doesn't wait for KVM pass code input.
// [RootCause]  	The Con Out Start protocol GUID is different in AMI and
// ME RC.
// [Solution]  	Install ME RC ConOut Protocol when AMI ConOut Protocol
// installed.
// [Files]  		AmtWrapperDxe.c
// AmtWrapperDxe.h
// 
// 5     4/08/13 3:06a Klzhan
// [TAG]  		EIPNone
// [Category]  	Improvement
// [Description]  	Support New Security protocol.
// 
// 4     10/30/12 8:33a Klzhan
// Correct Secure IDER boot
// 
// 3     8/14/12 7:24a Klzhan
// Support UEFI IDER boot.
// 
// 2     4/24/12 12:36a Klzhan
// Update modulepart to latest
// 
// 1     2/08/12 1:08a Klzhan
// Initial Check in 
// 
// 3     6/21/11 3:42a Klzhan
// Fix comnpiler error if PCI COM is 0.
// 
// 2     3/29/11 3:18a Klzhan
// Remove un-used code.
// 
// 1     2/25/11 1:43a Klzhan
// Initial Check-in
// 
// 2     12/28/10 2:00a Klzhan
// Improvement : Enable/Disable Terminal item for SOL redirection.
// 
// 1     12/03/10 5:10a Klzhan
// Initial Check-in.
// 
//
//**********************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:            AmtWrapperDxe.c
//
// Description:     Amt Wrapper Functions
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>
/*++
Copyright (c) 2009 Intel Corporation. All rights reserved.
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.
--*/
#if EFI_SPECIFICATION_VERSION>0x20000
#include "token.h"
#define _HII_H_
#define _FORM_CALLBACK_H_
#define _GLOBAL_VARIABLE_GUID_H_
#ifndef GUID_VARIABLE_DECLARATION
#define GUID_VARIABLE_DECLARATION(Variable, Guid) extern EFI_GUID Variable
#endif
#include "AmtWrapperDxe.h"
#else
#include "AmtWrapperDxe.h"
#include "token.h"
#define __UEFI_HII__H__
#define __HII_PROTOCOL_H__
#define _HII_H_
#endif
#if defined(Terminal_SUPPORT) && (Terminal_SUPPORT == 1)
#include "Core\Em\Terminal\TerminalSetupVar.h"
#endif
#include <SetupDataDefinition.h>
#if defined(CORE_COMBINED_VERSION) && CORE_COMBINED_VERSION >=0x4028e
#include <Protocol\Security2.h>
#else
#include <Protocol\Security.h>
#endif

#include <Amt.h>
#include EFI_GUID_DEFINITION(ConsoleOutDevice)

#define SETUP_GUID { 0xEC87D643, 0xEBA4, 0x4BB5, 0xA1, 0xE5, 0x3F, 0x3E, 0x36, 0xB2, 0x0D, 0xA9 }

AMT_WRAPPER_PROTOCOL AmtWrapperInstance = {
                                        AmtWrapperInit,
                                        AmtWrapperGet,
                                        AmtWrapperSet,                                      
                                        AmtWrapperEnableSol,
                                        AmtWrapperEnableIdeR,
                                        AmtWrapperPauseBoot,
                                        AmtWrapperEnterSetup,
                                        //AsfSupportInit,
                                        AmtWrapperBdsBootViaAsf,
                                        BdsLibUpdateConsoleVariable,
                                        ActiveManagementConsoleLocked,
                                        AmtWrapperEnableKvm,
                                        AmtWrapperInitializationKvm
                                  };

extern EFI_ACTIVE_MANAGEMENT_PROTOCOL   *mActiveManagement;
extern EFI_ASF_BOOT_OPTIONS             *mAsfBootOptions;
#if defined(LEGACYSREDIR_SUPPORT) && (LEGACYSREDIR_SUPPORT == 1)
EFI_GUID gEfiLegacySredirProtocolGuid = EFI_LEGACY_SREDIR_PROTOCOL_GUID;
#endif
EFI_GUID gSetupGuid                 	= SETUP_GUID;
EFI_GUID gEfiAmtWrapperProtocolGuid 	= EFI_AMT_WRAPPER_PROTOCOL_GUID;
EFI_GUID gEfiMeBiosExtensionSetupGuid 	= EFI_ME_BIOS_EXTENSION_SETUP_GUID;
CHAR16   gEfiMeBiosExtensionSetupName[] = EFI_ME_BIOS_EXTENSION_SETUP_VARIABLE_NAME;

PLATFORM_PCI_SERIAL_OVER_LAN_DEVICE_PATH gSerialOverLanDevicePath = {
            gPciRootBridge,
            {
                HARDWARE_DEVICE_PATH,
                HW_PCI_DP,
                (UINT8)(sizeof(PCI_DEVICE_PATH)),
                (UINT8)((sizeof(PCI_DEVICE_PATH)) >> 8),
                SOL_FUNCTION_NUMBER,
                ME_DEVICE_NUMBER
            },
            {
                MESSAGING_DEVICE_PATH,
                MSG_UART_DP,
                (UINT8)(sizeof(UART_DEVICE_PATH)),
                (UINT8)((sizeof(UART_DEVICE_PATH)) >> 8),
                0,
                115200,
                8,
                1,
                1
            },
            {
                MESSAGING_DEVICE_PATH,
                MSG_VENDOR_DP,
                (UINT8)(sizeof(VENDOR_DEVICE_PATH)),
                (UINT8)((sizeof(VENDOR_DEVICE_PATH)) >> 8),
                DEVICE_PATH_MESSAGING_PC_ANSI
            },
            gEndEntire
        };
        

EFI_HANDLE mBdsImageHandle;
UINT16 gPlatformBootTimeOutDefault = 1;


//
// Driver entry point
//
EFI_DRIVER_ENTRY_POINT (AmtWrapperDxeEntryPoint);

//
// Function implementations
//
#if defined(CORE_COMBINED_VERSION) && CORE_COMBINED_VERSION >=0x4028e
EFI_STATUS EmptyFileAuthentication
(
    IN CONST EFI_SECURITY2_ARCH_PROTOCOL *This,
    IN CONST EFI_DEVICE_PATH_PROTOCOL *File,
    IN VOID *FileBuffer,
    IN UINTN FileSize,
    IN BOOLEAN BootPolicy
)
#else
EFI_STATUS EmptyFileAuthentication
(
    IN EFI_SECURITY_ARCH_PROTOCOL *This,
    IN UINT32 AuthenticationStatus,
    IN EFI_DEVICE_PATH_PROTOCOL *File
)
#endif
{
    if (File==NULL) return EFI_INVALID_PARAMETER;
    return EFI_SUCCESS;
}

VOID
EFIAPI
InstallEDKConOutStartProtocol (
  IN EFI_EVENT                    Event,
  IN VOID                         *Context
  )
{

  gBS->InstallProtocolInterface(
      &mBdsImageHandle, &gEfiConsoleOutDeviceGuid, EFI_NATIVE_INTERFACE, NULL);

  gBS->CloseEvent (Event);
}

EFI_STATUS
EFIAPI
AmtWrapperDxeEntryPoint (
    IN EFI_HANDLE ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable
)
/*++
 
Routine Description:
 
  Entry point for the Active Management Driver.
  
Arguments:
 
  ImageHandle       Image handle of this driver.
  SystemTable       Global system service table.
 
Returns:
 
  EFI_SUCCESS           Initialization complete.
  EFI_UNSUPPORTED       The chipset is unsupported by this driver.
  EFI_OUT_OF_RESOURCES  Do not have enough resources to initialize the driver.
  EFI_DEVICE_ERROR      Device error, driver exits abnormally.
 
--*/
{
    EFI_STATUS Status;
    EFI_EVENT  ReadyToBootEvent;
    EFI_GUID   gSetupGuid = SETUP_GUID;
    UINTN      VariableSize  = sizeof(SETUP_DATA);
    SETUP_DATA SetupDataBuffer;
    SETUP_DATA *SetupData = &SetupDataBuffer;
    VOID       *AfterConsolOutNotifyReg;
    EFI_EVENT  AfterConsolOutInstalledEvent;
    EFI_GUID   AmiConOutStartProtocolGuid = AMI_CONSOLE_OUT_DEVICES_STARTED_PROTOCOL_GUID;

    mBdsImageHandle = ImageHandle;
    //
    // Initialize the EFI Driver Library
    //
    EfiInitializeDriverLib (ImageHandle, SystemTable);
    INITIALIZE_SCRIPT (ImageHandle, SystemTable);

    mAsfBootOptions = NULL;
    mActiveManagement = NULL;
    
    InitAmtWrapperLib();
    //
    // Install the EFI_ACTIVE_MANAGEMENT_PROTOCOL interface
    //
    Status = gBS->InstallMultipleProtocolInterfaces (
                 &ImageHandle,
                 &gEfiAmtWrapperProtocolGuid,   &AmtWrapperInstance,
                 NULL
             );

    // This event is for KVM function, because ConOut Start GUID is different from AMI to ME RC.
    Status = gBS->CreateEvent (
                    EFI_EVENT_NOTIFY_SIGNAL,
                    EFI_TPL_NOTIFY,
                    InstallEDKConOutStartProtocol,
                    NULL,
                    &AfterConsolOutInstalledEvent
                    );

    Status = gBS->RegisterProtocolNotify (
                    &AmiConOutStartProtocolGuid,
                    AfterConsolOutInstalledEvent,
                    &AfterConsolOutNotifyReg
                    );

#if defined(Terminal_SUPPORT) && (Terminal_SUPPORT == 1)
    // Enable/Disable Sol redirection
    SetSOLCOMEnable(AmtWrapperEnableSol());
#endif
    //
    // Register Ready to Boot Event for AMT Wrapper 
    //
#if defined(EFI_EVENT_SIGNAL_READY_TO_BOOT) && EFI_SPECIFICATION_VERSION<0x20000
    Status = gBS->CreateEvent(
                EFI_EVENT_SIGNAL_READY_TO_BOOT | EFI_EVENT_NOTIFY_SIGNAL_ALL,
                EFI_TPL_CALLBACK,
               	AmtWrapperReadyToBoot,
               	(VOID *)&ImageHandle,
                &ReadyToBootEvent
                );
#else
    Status = EfiCreateEventReadyToBoot(
                EFI_TPL_CALLBACK,
               	AmtWrapperReadyToBoot,
               	(VOID *)&ImageHandle,
                &ReadyToBootEvent
                );
#endif
  	
    return Status;
}

#if defined(Terminal_SUPPORT) && (Terminal_SUPPORT == 1)
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SetSOLCOMEnable
//
// Description: Enable/Disable SOL COM.
//
// Input:
//
// Output:
//
// Notes:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
SetSOLCOMEnable(
    IN BOOLEAN         Enabled
)
{
    UINT32      ComPort;
    UINT32      SetupVarAttr;
    UINTN       SetupDataSize;
    SETUP_DATA  gSetupData;
    EFI_STATUS  Status;
#if (TOTAL_PCI_SERIAL_PORTS > 0)
    UINT32      i = 0;
    EFI_GUID    gTerminalVarGuid   = TERMINAL_VAR_GUID;
    UINTN       PciSerialPortsLocationVarSize = 
                                    sizeof(PCI_SERIAL_PORTS_LOCATION_VAR);
    UINT32      PciSerialPortsLocationVarAttributes=0;
    PCI_SERIAL_PORTS_LOCATION_VAR PciSerialPortsLocationVar; 
    UINT32 gTotalSioSerialPorts = TOTAL_SIO_SERIAL_PORTS;
    Status = gRT->GetVariable(L"PciSerialPortsLocationVar", 
                                &gTerminalVarGuid, 
                                &PciSerialPortsLocationVarAttributes, 
                                &PciSerialPortsLocationVarSize, 
                                &PciSerialPortsLocationVar);

    if(EFI_ERROR(Status)) {
        ComPort = gTotalSioSerialPorts;
    }

    ComPort = gTotalSioSerialPorts; 

    for (i = 0; i < TOTAL_PCI_SERIAL_PORTS; i++) {
        if ((PciSerialPortsLocationVar.Device[i] == SOL_DEVICE_NUMBER) && 
            (PciSerialPortsLocationVar.Function[i] == SOL_FUNCTION_NUMBER)) {
                ComPort = gTotalSioSerialPorts+i; 
                break;            
        }
    }	
#else 
    return;
#endif

    SetupVarAttr = 0;
    SetupDataSize = sizeof(SETUP_DATA);
    Status = gRT->GetVariable( \
                    L"Setup", \
                    &gSetupGuid, \
                    &SetupVarAttr, \
                    &SetupDataSize, \
                    &gSetupData );

    if(Enabled)
        gSetupData.ConsoleRedirectionEnable[ComPort] = 1;
    else
        gSetupData.ConsoleRedirectionEnable[ComPort] = 0;

    Status = gRT->SetVariable( \
                    L"Setup", \
                    &gSetupGuid, \
                    SetupVarAttr, \
                    SetupDataSize, \
                    &gSetupData );
}
#endif

EFI_STATUS
BdsRefreshBbsTableForBoot (
    IN BDS_COMMON_OPTION *Entry
)
{
    return EFI_NOT_FOUND;
}

VOID
PrintBbsTable (
    IN BBS_TABLE *LocalBbsTable
)
{
    UINT16 Idx;

    DEBUG ((EFI_D_ERROR, "\n"));
    DEBUG ((EFI_D_ERROR, " NO  Prio bb/dd/ff cl/sc Type Stat segm:offs\n"));
    DEBUG ((EFI_D_ERROR, "=============================================\n"));
    for (Idx = 0; Idx < MAX_BBS_ENTRIES; Idx++)
    {
        if (LocalBbsTable[Idx].BootPriority == BBS_IGNORE_ENTRY)
        {
            continue;
        }

        DEBUG (
            (EFI_D_ERROR,
             " %02x: %04x %02x/%02x/%02x %02x/02%x %04x %04x %04x:%04x\n",
             (UINTN) Idx,
             (UINTN) LocalBbsTable[Idx].BootPriority,
             (UINTN) LocalBbsTable[Idx].Bus,
             (UINTN) LocalBbsTable[Idx].Device,
             (UINTN) LocalBbsTable[Idx].Function,
             (UINTN) LocalBbsTable[Idx].Class,
             (UINTN) LocalBbsTable[Idx].SubClass,
             (UINTN) LocalBbsTable[Idx].DeviceType,
             (UINTN) * (UINT16 *) &LocalBbsTable[Idx].StatusFlags,
             (UINTN) LocalBbsTable[Idx].BootHandlerSegment,
             (UINTN) LocalBbsTable[Idx].BootHandlerOffset,
             (UINTN) ((LocalBbsTable[Idx].MfgStringSegment << 4) + LocalBbsTable[Idx].MfgStringOffset),
             (UINTN) ((LocalBbsTable[Idx].DescStringSegment << 4) + LocalBbsTable[Idx].DescStringOffset))
        );
    }

    DEBUG ((EFI_D_ERROR, "\n"));
}

BOOLEAN 
AmtWrapperGet(
    IN UINTN Index, 
    IN OUT VOID *pVar
)
{
    BOOLEAN st = FALSE;
    
    InitAmtWrapperLib();
    
    if (Index == GET_SOL_DP) {
        *((PLATFORM_PCI_SERIAL_OVER_LAN_DEVICE_PATH **)pVar) = &gSerialOverLanDevicePath;
        st = TRUE;
    } else if (Index == GET_TIME_OUT) {
        *((UINT16 *)pVar) = BdsLibGetTimeout();     
        st = TRUE;
    } else if (Index == GET_BOOT_OPTION) {    
        *((UINT16 *)pVar) = mAsfBootOptions->BootOptions;
         st = TRUE;
    } else if (Index == GET_IS_SOL) {    
        *((UINTN *)pVar) = IsSOL(*((EFI_HANDLE *)pVar));
         st = TRUE;
    } else if (Index == GET_IS_IDER) {    
        *((UINTN *)pVar) = IsIDER(*((EFI_HANDLE *)pVar));
         st = TRUE;
    }

    return st;
}

UINTN IsSOL(
	IN EFI_HANDLE Controller
) 
{
	EFI_STATUS 					Status;
	EFI_PCI_IO_PROTOCOL         *PciIo;
    UINTN                       Segment=0;
    UINTN                       Bus=0; 
    UINTN                       Device=0; 
    UINTN                       Function=0;
	UINTN						flag = FALSE;
	
	Status = gBS->HandleProtocol(Controller,
                                 &gEfiPciIoProtocolGuid,
                                 &PciIo);
    if (!EFI_ERROR(Status)) {	    
	    Status = PciIo->GetLocation(PciIo, 
	    							&Segment, 
	    							&Bus, 
	                                &Device, 
	                                &Function);
		if (!EFI_ERROR(Status)) {		
			if (Device == SOL_DEVICE_NUMBER && Function == SOL_FUNCTION_NUMBER) {
				flag = TRUE;
			}
		}
	}
                    
   	return flag;                    
}

UINTN IsIDER(
	IN EFI_HANDLE Controller
) 
{
	EFI_STATUS 					Status;
	EFI_PCI_IO_PROTOCOL         *PciIo;
    UINTN                       Segment=0;
    UINTN                       Bus=0; 
    UINTN                       Device=0; 
    UINTN                       Function=0;
	UINTN						flag = FALSE;
	
	Status = gBS->HandleProtocol(Controller,
                                 &gEfiPciIoProtocolGuid,
                                 &PciIo);
    if (!EFI_ERROR(Status)) {	    
		    Status = PciIo->GetLocation(PciIo, 
		    							&Segment, 
		    							&Bus, 
		                                &Device, 
		                                &Function);
	    if (!EFI_ERROR(Status)) {	    			
			if (Device == IDER_DEVICE_NUMBER && Function == IDER_FUNCTION_NUMBER) {
				flag = TRUE;
			}
		}
	}
                    
   	return flag;                    
}

UINT16 ConvertSetupDataToUART(
	UINT8 Parity,
	UINT8 DataBits,
	UINT8 StopBits
)
{
	UINT16 DataParityStopBit = 0;
	
    switch (Parity) {
        case NoParity:
            DataParityStopBit &= ~(PAREN | EVENPAR | STICPAR);
        break;
        case EvenParity:
            DataParityStopBit |= (PAREN | EVENPAR);
            DataParityStopBit &= ~STICPAR;
        break;
        case OddParity:
            DataParityStopBit |= PAREN;
            DataParityStopBit &= ~(EVENPAR | STICPAR);
            break;
        case SpaceParity:
            DataParityStopBit |= (PAREN | EVENPAR | STICPAR);
            break;
        case MarkParity:
            DataParityStopBit |= (PAREN | STICPAR);
            DataParityStopBit &= ~EVENPAR;
        break;
    }
    
    // Set stop bits.
    switch (StopBits) {
        case OneStopBit :
            DataParityStopBit &= ~STOPB;
        break;
        case OneFiveStopBits :
        case TwoStopBits :
            DataParityStopBit |= STOPB;
            break;
    }

    // Set data bits.
    DataParityStopBit &= ~SERIALDB;
    DataParityStopBit |= (UINT8)((DataBits - 5) & 0x03);
            
    return DataParityStopBit;    
}

BOOLEAN 
AmtWrapperSet(
    IN UINTN Index, 
    IN OUT VOID *pVar
)
{
#if defined(LEGACYSREDIR_SUPPORT) && (LEGACYSREDIR_SUPPORT == 1)
    EFI_LEGACY_SREDIR_PROTOCOL  *pLegacySredir;
    UINT64                      PciAddress;
    UINT32                      SerialAddress;
    UINT8                       SerialIRQ;
    EFI_STATUS                  Status;
    EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *PciRootBridgeIo;
    BOOLEAN st = FALSE;
    
    InitAmtWrapperLib();
    
    if (Index == SET_BIOS_WDT_START) {
        AsfStartWatchDog(ASF_START_BIOS_WDT);
        st = TRUE;
    }
    else if (Index == SET_OS_WDT_START) {
        AsfStartWatchDog(ASF_START_OS_WDT);
        st = TRUE;
    }
    else if (Index == SET_WDT_STOP) {
        AsfStopWatchDog();
        st = TRUE;
    }
    else if (Index == SET_OS_SOL) {
        Status = gBS->LocateProtocol(&gEfiLegacySredirProtocolGuid, NULL, &pLegacySredir);
        ASSERT_EFI_ERROR(Status);
        
        Status = gBS->LocateProtocol(&gEfiPciRootBridgeIoProtocolGuid, NULL, &PciRootBridgeIo);
        ASSERT_EFI_ERROR(Status);

        PciAddress = EFI_PCI_ADDRESS (SOL_BUS_NUMBER, SOL_DEVICE_NUMBER, SOL_FUNCTION_NUMBER, 0x10);
        PciRootBridgeIo->Pci.Read (
            PciRootBridgeIo,
            EfiPciWidthUint32,
            PciAddress,
            1,
            &SerialAddress
        );
        SerialAddress &= ~1;            // mask IO/MEM bit
        
        PciAddress = EFI_PCI_ADDRESS (SOL_BUS_NUMBER, SOL_DEVICE_NUMBER, SOL_FUNCTION_NUMBER, 0x3C);
        PciRootBridgeIo->Pci.Read (
            PciRootBridgeIo,
            EfiPciWidthUint8,
            PciAddress,
            1,
            &SerialIRQ
        );
/*
		UID = TOTAL_SIO_SERIAL_PORTS;
		gEfiComParameters.BaseAddress = (UINT16)SerialAddress;
		gEfiComParameters.SerialIRQ = (UINT8)SerialIRQ;
		
		VariableSize = sizeof(SETUP_DATA);
	   	Status = gRT->GetVariable(
	   					L"Setup", 
	   					&gSetupGuid, 
	   					NULL,
	   					&VariableSize, 
	   					&SetupData);
		ASSERT(!EFI_ERROR(Status));
		        
    	gEfiComParameters.Baudrate      = BaudRates[SetupData.BaudRate[UID]];
    	gEfiComParameters.TerminalType  = TerminalTypes[SetupData.TerminalType[UID]];
    	gEfiComParameters.FlowControl   = SetupData.FlowControl[UID];
        
    	gEfiComParameters.DataParityStop = ConvertSetupDataToUART(
        					SetupData.Parity[UID],
        					SetupData.DataBits[UID],
        					SetupData.StopBits[UID]);
        
		if (SREDIR_DISPLAY_MODE == DISPLAY_BY_80x24)
			gEfiComParameters.LegacyOsResolution = 0;
		else if (SREDIR_DISPLAY_MODE == DISPLAY_BY_80x25)
			gEfiComParameters.LegacyOsResolution = 1;
		else
			gEfiComParameters.LegacyOsResolution = SetupData.LegacyOsResolution[UID];
*/
        Status = pLegacySredir->EnableLegacySredir(pLegacySredir);
        
        ASSERT_EFI_ERROR (Status);
        st = TRUE;
    }
    
    return st;
#else
    return FALSE;
#endif
}

EFI_STATUS 
AmtWrapperInit(
    IN EFI_HANDLE ImageHandle, 
    IN OUT EFI_SYSTEM_TABLE *SystemTable
)
{
    mBdsImageHandle = ImageHandle;
    InitAmtWrapperLib();

    return EFI_SUCCESS;
}


VOID
InitAmtWrapperLib(VOID)
{
    if (mActiveManagement == NULL)
        AmtLibInit();
        
    if (mAsfBootOptions == NULL) {
		BdsAsfInitialization();
	}
}

BOOLEAN
AmtWrapperEnableSol(
	IN VOID
)
{
    BOOLEAN st;
    
    InitAmtWrapperLib();    
    st = ActiveManagementEnableSol();
    if(((mAsfBootOptions->OemParameters) & 0x01) && (mAsfBootOptions != NULL))
        st = TRUE;
    else
        st = FALSE;
    return st;
}

BOOLEAN
AmtWrapperEnableIdeR(
	IN VOID
)
{
    BOOLEAN     st;
    EFI_STATUS  Status;
#if defined(CORE_COMBINED_VERSION) && CORE_COMBINED_VERSION >=0x4028e
    EFI_SECURITY2_ARCH_PROTOCOL *mSecurity;
#else
    EFI_SECURITY_ARCH_PROTOCOL *mSecurity;
#endif

    InitAmtWrapperLib();    
    st = ActiveManagementEnableIdeR();
    if(!st)
        return st;
    // IDER enabled and Enforce Secure Boot enabled
    if((mAsfBootOptions->SpecialCommandParam & ENFORCE_SECURE_BOOT) 
                                            != ENFORCE_SECURE_BOOT)
    {
#if defined(CORE_COMBINED_VERSION) && CORE_COMBINED_VERSION >=0x4028e
        EFI_GUID gEfiSecurity2ArchProtocolGuid = EFI_SECURITY2_ARCH_PROTOCOL_GUID;
        Status = gBS->LocateProtocol(&gEfiSecurity2ArchProtocolGuid, 

#else
        Status = gBS->LocateProtocol(&gEfiSecurityArchProtocolGuid, 
#endif
                                     NULL, &mSecurity);

        if(EFI_ERROR(Status))
            return st;
        // Set a empty File Authentication to skip Secure check.
        // This will not been restore, because IDER boot fail system HALT

#if defined(CORE_COMBINED_VERSION) && CORE_COMBINED_VERSION >=0x4028e
        mSecurity->FileAuthentication = EmptyFileAuthentication;
#else
        mSecurity->FileAuthenticationState = EmptyFileAuthentication;
#endif
    }

    return st;
}

BOOLEAN
AmtWrapperPauseBoot(
	IN VOID
)
{
    BOOLEAN st;
    
    InitAmtWrapperLib();    
    st = ActiveManagementPauseBoot();
    
    return st;
}

BOOLEAN
AmtWrapperEnterSetup(
	IN VOID
)
{
    BOOLEAN st;
    
    InitAmtWrapperLib();    
    st = ActiveManagementEnterSetup();
    
    return st;
}

EFI_STATUS
AmtWrapperBdsBootViaAsf(
	IN VOID
)
{
	EFI_STATUS Status = EFI_NOT_FOUND;
    
    InitAmtWrapperLib();
    
    if (mActiveManagement != NULL && mAsfBootOptions != NULL) {
    	Status = BdsBootViaAsf();
    }
    
    return Status;
}



EFI_STATUS
AmtWrapperReadyToBoot(
	EFI_EVENT           Event,
    VOID                *ParentImageHandle
)
{
	EFI_STATUS Status = EFI_SUCCESS;
	
	
	return Status;
}

BOOLEAN
AmtWrapperEnableKvm(
	IN VOID
)
{
  BOOLEAN Status;

  Status = ActiveManagementEnableKvm();    

  return Status;
}

BOOLEAN
AmtWrapperInitializationKvm(
	IN VOID
)
{
  BOOLEAN Status;

  Status = BdsKvmInitialization();    

  return Status;
}
//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************