//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2006, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/DEBUGGER/Include/AmiDebugPort.h 7     10/30/07 10:49a Madhans $
//
// $Revision: 7 $
//
// $Date: 10/30/07 10:49a $
//**********************************************************************
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/DEBUGGER/Include/AmiDebugPort.h $
// 
// 7     10/30/07 10:49a Madhans
// 1.20.0010 Eng Release
// 
// 3     1/22/07 11:35a Madhans
// Modification made for Binary Release 1.04.0003.
// 
// 3     1/05/07 1:05p Ashrafj
// Latest version 1.04.0001 Beta
// Known issues from previous 1.04.000 Beta release has been fixed.
// 
//**********************************************************************
//*****************************************************************
#ifndef	_AMI_DEBUGPORT_H_
#define _AMI_DEBUGPORT_H_

#include "Hob.h"
#include "Protocol\PciRootBridgeIo.h"
#include "PciBus.h"					//For Defn, of PCI_CFG_ADDR


// {E894B313-54CA-4bb2-8CDD-851E8AC9027C}
#define	AMI_DEBUGPORT_HOB_GUID \
 {0xe894b313, 0x54ca, 0x4bb2, 0x8c, 0xdd, 0x85, 0x1e, 0x8a, 0xc9, 0x2, 0x7c}

typedef enum {
	SERIAL,
	USB2_EHCI,		//currently only intel chipset has USB2 debug port on EHCI
	USB2_UHCI,		//for future chipset if any is going to support USB2 debug port
	USB2_OHCI,		//for future chipset if any is going to support USB2 debug port
	LPT,
	SMBUS_TO_USB
}DEBUGPORT_TYPE;

typedef struct _DEBUG_PORT_INFO 
{ 
    DEBUGPORT_TYPE		DebugPortType;	//Type of physical Port used for communication
    UINT64				BaseAddress;    //BAR address 
    UINT64				Length;         //Size of relocateable window size 
    UINT16				IRQn;           //IRQ number 
	UINT8				BarOffset; 		//offset of this bar register in PCI_CFG space 
	UINT8				BarIndex;		//Index from 0 to 5 of the the BAR 
    PCI_CFG_ADDR		Address;        //PCI configuration address like B,D,F for USB 
										//or Logical Device number in case Serial 
	PCI_BAR_TYPE		BarType;		//Type Of Resource (MMIO32/MMIO64/pfMMIO32/pfMMIO64/Io16/Io32)
										//Offset=0x10 => Index=0;
										//Offset=0x14 => Index=1;
										//And soo on
} DEBUG_PORT_INFO; 

typedef	struct _AMI_DEBUGPORT_INFORMATION_HOB AMI_DEBUGPORT_INFORMATION_HOB;	//forward declaration

typedef EFI_STATUS (* GET_DEBUGPORT_PROPERTIES ) ( 
					IN AMI_DEBUGPORT_INFORMATION_HOB *This,
					IN OUT DEBUG_PORT_INFO *pDeviceInfo 
					);

typedef EFI_STATUS (* SET_DEBUGPORT_RESOURCES) (
					IN AMI_DEBUGPORT_INFORMATION_HOB *This,
					IN EFI_BOOT_SERVICES *pBS,												
					IN DEBUG_PORT_INFO  *pDeviceInfo 
					); 

typedef  struct _AMI_DEBUGPORT_INFORMATION_HOB 
{ 
	EFI_HOB_GUID_TYPE			EfiHobGuidType;
	DEBUG_PORT_INFO				DeviceInfo; 

	GET_DEBUGPORT_PROPERTIES	GetDebugPortProperties;

	SET_DEBUGPORT_RESOURCES		SetDebugPortResources;

	UINT64						Reserved;		//For PEI Debug support - do not use
} 
AMI_DEBUGPORT_INFORMATION_HOB; 

typedef union	_PEI_DBG_PORT_INFO	PEI_DBG_PORT_INFO;
typedef EFI_STATUS (PEI_INIT_FUNCTION) (IN OUT PEI_DBG_PORT_INFO   *DebugPort);

typedef struct _PEI_DBG_COM_PORT{
	UINT16				COMBaseAddr;
	UINT8				SIO_COM_LDN;
}PEI_DBG_COM_PORT;

typedef struct _PEI_DBG_USB_PORT{
	UINT32				USBBaseAddr;
	UINT32				USBDebugPortStartAddr;
	UINT16				MemoryMappedIoSpaceSize;
	UINT8				PciBusNumber;
	UINT8				PciDeviceNumber;
	UINT8				PciFunctionNumber;
	UINT8				PciBAROffset;
	PEI_INIT_FUNCTION	*InitUSBEHCI;
}PEI_DBG_USB_PORT;

typedef union _PEI_DBG_PORT_INFO{
	PEI_DBG_COM_PORT	SerialPort;
	PEI_DBG_USB_PORT	UsbDebugPort;
}PEI_DBG_PORT_INFO;

#endif


//****************************************************************
//****************************************************************
//**															**
//**	(C)Copyright 1985-2006, American Megatrends Inc.		**
//**															**
//**			All Rights Reserved.							**
//**															**
//**		6145-F, Northbelt Parkway, Norcross,				**
//**															**
//**		Georgia - 30071, USA. Phone-(770)-246-8600.			**
//**															**
//****************************************************************
//****************************************************************


