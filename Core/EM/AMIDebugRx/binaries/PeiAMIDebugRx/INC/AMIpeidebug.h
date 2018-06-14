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
// $Header: /Alaska/BIN/Modules/AMIDebugRx/binaries/PeiAMIDebugRx/INC/AMIpeidebug.h 6     3/16/11 4:43p Sudhirv $
//
// $Revision: 6 $
//
// $Date: 3/16/11 4:43p $
//*****************************************************************
//*****************************************************************
//
//	peidebug.h
//
//
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/AMIDebugRx/binaries/PeiAMIDebugRx/INC/AMIpeidebug.h $
// 
// 6     3/16/11 4:43p Sudhirv
// Changes to Support Older Cores before 4.6.5.0
// 
// 5     3/09/11 8:22a Sudhirv
// EIP 53658 - AMIDebugRx\Debugger support for PI 1.1
// 
// 4     9/22/10 7:09p Sudhirv
// 4.6.2_AMIDebugRx_2.01.0026_Beta Release
//
// 3     9/30/09 8:00p Madhans
// Updated for 1.31. Refer release notes.
//
// 2     7/17/09 7:15p Madhans
// DebugRx 1.30.0022
//
// 2     7/13/09 2:49p Sudhirv
// Update with Coding Standards
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
// 25    3/19/09 3:41p Sudhirv
// Added After changes for Target Sending Exception Packets
//
// 23    1/30/09 12:32p Sudhirv
// Added after Console Redirection Support
//
// 22    9/25/08 4:29p Sudhirv
// Updated SMM Debugging and Read/Write Mem
//
// 21    7/29/08 1:09p Sudhirv
// Changes made to support SMM debugging in savemem and loadmem
// extension commands
//
// 20    6/26/08 3:30p Sudhirv
// Uploaded after checking coding standards
//
// 19    6/11/08 2:24p Sudhirv
// After Addibg GP Handling in MSR
//
// 18    6/11/08 5:46a Sudhirv
// Uploaded for Release with Read/WriteMSR restriction, Readio/Writeio
// restriction, Read/Write IndirectIO, ListModules and PciList
//
// 17    12/05/07 8:23a Sudhirv
// Added to support and Restrict ReadMSR/WriteMSR commands
//
// 16    10/24/07 10:31a Madhans
// Hatdriver Support.
//
// 15    8/29/07 3:49p Madhans
// To resolve AMD Platfrom issues.
//
// 14    8/29/07 12:49p Madhans
// Common code for 4.x and 3.x
//
// 13    6/13/07 3:16p Madhans
// Copyright Year updated.
//
// 12    6/13/07 2:37p Madhans
// To improve the performance in Load FV though Serial.
//
// 11    6/05/07 7:10p Natalyak
// Load FV support
//
// 10    4/05/07 6:33p Madhans
// CAR_BASE_ADJUST_OFFSET removed.
//
// 9     3/10/07 1:24p Madhans
// CAR_BASE_ADJUST_OFFSET allows to have PEI_SERVICES address above IDT
//
// 8     2/23/07 5:36p Madhans
// PeiDbgr_SendPeiLoadImage function added.
//
// 7     1/22/07 11:41a Madhans
// Modification made for Binary Release 1.04.0003.
//
// 11    1/05/07 6:15p Madhan
//
// 10    1/05/07 1:05p Ashrafj
// Latest version 1.04.0001 Beta
// Known issues from previous 1.04.000 Beta release has been fixed.
//
// 9     12/26/06 7:07p Ashrafj
// Support added to support the Aptio 4.5 x64 EFI BIOS (use latest
// Host.zip).
// PEI Debugger in FV_MAIN (use new PEIDEBUGFIXUP).
// Support added for StatusCode redirection without Debug feature enabled
// (not working if DXE only and x64 is enabled).
// Plus, some new SDL tokens defined to support the Aptio 4.5 build
// process in Debug or non-debug mode.
// All the components of Debugger eModule in source form.
//
// 7     6/27/06 11:44a Ashrafj
// New feature added:
// To enable the PEI Debug support after system memory is installed, based
// on build option provided through a new SDL token named
// "PEI_DEBUG_SUPPORT_AFTER_MEMORY".
//
// 6     3/15/06 7:45p Ashrafj
// Modfication done to provide the Binary integration for Aptio 4
// projects.
//
// 5     12/22/05 12:42p Ashrafj
// Changes done to support the complete Chipset template porting.
//
// To use this changes, make sure to have the latest Board components of
// CPU, SB and SIO, which have the following ELINKS ported:
// - SBPEIDBG_Initialize,
// - CPUPEIDBG_Initialize,
// - SIOPEIDBG_Initialize,
// - SBPEIDBG_InitUsbEhci.
//
// 4     12/05/05 7:29p Ashrafj
// Serial Port Debug Support added for PEI - DXE Debugger.
//
// Change in Serial Port Communication: Now the data transmission through
// Serial Port is supported with the hardware Flow control feature of the
// Serial Port controller.
//
// 3     11/29/05 6:07p Markw
// Change USB interface function parameters.
//
// 2     10/25/05 11:38a Ashrafj
// Minor fix - packed structure alignment and width size of global
// variable.
//
// 1     10/19/05 10:54a Felixp
//
// 1     10/19/05 10:44a Felixp
//
//
//
//*****************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:          AMIPeiDebug.h
//
// Description:   Contains 32 bit Pei Debugger prototypes
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>
#ifndef	_AMI_PEIDEBUG_H_
#define _AMI_PEIDEBUG_H_

#ifdef	USB_DEBUGGER
#include "EHCI.h"
#endif

#ifdef ALASKA_SUPPORT
#include "token.h"
#else
#include "tokens.h"
#endif

#define EFI_PEI_DBG_BASEADDRESS_PPI_GUID \
  { 0x9bf4e141, 0xa4ec, 0x4d72,  {0xbc, 0xc4, 0x94, 0x2, 0x1d, 0x2b, 0x80, 0xbd }}

#if defined (PI_SPECIFICATION_VERSION) 
#if PI_SPECIFICATION_VERSION>=0x00010000
UINTN GetCARBaseAddress();
#define	PEI_DEBUG_DATASECTION_BASEADDRESS	GetCARBaseAddress()	//Starting address of PEI debugger data section
#define PEI_DEBUG_DATASECTION_SIZE		    0x2048

#else	//if PI_SPECIFICATION_VERSION >= 0x00010000
#ifdef ALASKA_SUPPORT
#define	PEI_DEBUG_DATASECTION_BASEADDRESS	CAR_BASE_ADDRESS	//Starting address of PEI debugger data section
#define PEI_DEBUG_DATASECTION_SIZE		    CAR_TOTAL_SIZE
#else	//ifdef ALASKA_SUPPORT
#define PM_BASE_ADDRESS			APLIB_PM_BASE_ADDRESS
#define DATA_STACK_BASEADDRESS		APLIB_CAR_BASEADDRESS
#define PEI_DEBUG_DATASECTION_BASEADDRESS	DATA_STACK_BASEADDRESS  //Starting address of PEI debugger data section
#define PEI_DEBUG_DATASECTION_SIZE		0x400
#endif 	//ifdef ALASKA_SUPPORT

#endif	//if PI_SPECIFICATION_VERSION >= 0x00010000

#else	//if not defined (PI_SPECIFICATION_VERSION) 
#ifdef ALASKA_SUPPORT
#define	PEI_DEBUG_DATASECTION_BASEADDRESS	CAR_BASE_ADDRESS	//Starting address of PEI debugger data section
#define PEI_DEBUG_DATASECTION_SIZE		    CAR_TOTAL_SIZE
#else	//ifdef ALASKA_SUPPORT
#define PM_BASE_ADDRESS			APLIB_PM_BASE_ADDRESS
#define DATA_STACK_BASEADDRESS		APLIB_CAR_BASEADDRESS
#define PEI_DEBUG_DATASECTION_BASEADDRESS	DATA_STACK_BASEADDRESS  //Starting address of PEI debugger data section
#define PEI_DEBUG_DATASECTION_SIZE		0x400
#endif	//ifdef ALASKA_SUPPORT

#endif	//if defined (PI_SPECIFICATION_VERSION)

#define IRQ_VECTOR_BASE	0x8

typedef struct {
	UINT8	Signature[4];
	UINT32	DATABASEADDRESS;
}PEI_DBG_DATA_SECTION;

#ifdef	RELOCATE

#if defined PI_SPECIFICATION_VERSION  
#if (PI_SPECIFICATION_VERSION >= 0x00010000)
#define PEI_DEBUG_DATA_BASEADDRESS  GetCARBaseAddress() //(PeiDbgDataSection.DATABASEADDRESS)
#else
extern	PEI_DBG_DATA_SECTION		PeiDbgDataSection;
#define PEI_DEBUG_DATA_BASEADDRESS  (PeiDbgDataSection.DATABASEADDRESS)
#endif
#else
extern	PEI_DBG_DATA_SECTION		PeiDbgDataSection;
#define PEI_DEBUG_DATA_BASEADDRESS  (PeiDbgDataSection.DATABASEADDRESS)
#endif

#else
#define PEI_DEBUG_DATA_BASEADDRESS	PEI_DEBUG_DATASECTION_BASEADDRESS  // Fixed Base Address
#endif

#define IDT_ENTRIES					0x14	    // Number of Entries in IDT
#define IDT_SIZE					0xa0        // Total Size = 160 Bytes
#define CONTEXT_SIZE				0x74	    // Total Size = 116 Bytes

#define XPORTLOCALVAR_SIZE			0x48	    // Total Size =  72 Bytes

#define XPORTGLOBALVAR_SIZE			0x18	    // Total Size =  24 Bytes
//#define DBGRLOCALVAR_SIZE			0x2c	    // Total Size =  44 Bytes
#define DBGRLOCALVAR_SIZE			0x36	    // Total Size =  56 Bytes
#define XPORTEXPTNBUF_SIZE			0x20	    // Total Size =  32 Bytes

//#define GLOBALBUF_SIZE				0x235	    // Total Size = 565 Bytes
#define GLOBALBUF_SIZE				0x210	    // Total Size = 528 Bytes

#define ACKBUF_SIZE					0x0a		// Total Size =  10 Bytes



#define PEI_DEBUG_IDTBASEADDR			PEI_DEBUG_DATA_BASEADDRESS
#define PEI_DEBUG_CONTEXTADDR			PEI_DEBUG_DATA_BASEADDRESS + IDT_SIZE
#define PEI_DEBUG_XPORTLOCALVARADDR		PEI_DEBUG_CONTEXTADDR + CONTEXT_SIZE
#define PEI_DEBUG_XPORTGLOBALVARADDR	PEI_DEBUG_XPORTLOCALVARADDR + XPORTLOCALVAR_SIZE
#define PEI_DEBUG_DBGRLOCALVARADDR		PEI_DEBUG_XPORTGLOBALVARADDR + XPORTGLOBALVAR_SIZE
#define PEI_DEBUG_XPORTEXPTNADDR		PEI_DEBUG_DBGRLOCALVARADDR + DBGRLOCALVAR_SIZE
#define PEI_DEBUG_BUFADDR				PEI_DEBUG_XPORTEXPTNADDR + XPORTEXPTNBUF_SIZE
#define	PEI_DEBUG_ACKADDR				PEI_DEBUG_BUFADDR + GLOBALBUF_SIZE

#define	IN_PEI_BEFORE_MEMORY		0
#define	IN_PEI_AFTER_MEMORY			01
#define	IN_DXE_WITH_PEI_DBGR		02
#define	IN_DXE_WITH_DXE_DBGR		03

#pragma pack (push, pei_struct_data_pack, 1)

typedef struct {
	unsigned char	IDTSet[IDT_SIZE];
	unsigned char	ContextReg[CONTEXT_SIZE];
	unsigned char	XportLocalVar[XPORTLOCALVAR_SIZE];
	unsigned char	XportGlobalVar[XPORTGLOBALVAR_SIZE];
	unsigned char	DbgrLocalVar[DBGRLOCALVAR_SIZE];
	unsigned char	XportExptn[XPORTEXPTNBUF_SIZE];
	unsigned char	GlobalBuf[GLOBALBUF_SIZE];
	unsigned char	AckBuf[ACKBUF_SIZE];
} PEIDebugData_T;


#pragma pack (pop, pei_struct_data_pack)


typedef struct _AMI_PEI_TRANSPORT_PROTOCOL	{
	UINT8	Signature[4];
	UINT16	(*Initialize)();
	UINT16	(*Restore)();
	UINT16	(*Send)();
	UINT16	(*Receive)();
	UINT16	(*SyncPacketNumber)();
	UINT16  (*RegisterHandler)();
	VOID	(*Callback)();
	UINT16	(*SendNoAck)();
	EFI_STATUS	(*ConsoleIn)();
	VOID 	(*SendExptn)();
} AMI_PEI_TRANSPORT_PROTOCOL;

typedef	struct{
	UINT8	Signature[4];
	VOID	(*ExceptionCallback)();
	VOID	(*SendMessage)();
	UINTN	(*PeiDbgr_EnableDebugSupport)(UINTN BrkPtAddr);
	UINTN	(*PeiDbgr_SendPeiLoadImage)(UINTN FileHandle,UINTN ImageAddr,UINTN ImageSize,void * PDBFileName);
	VOID	(*DoSpecialBreakPoint)(UINT32 EaxValue,UINT32 EdxValue);
}AMI_DEBUGGER_INTERFACE;

#pragma pack(1)
typedef struct {
	UINT32	m_EIP;
	UINT16	m_SendPktSize;
	UINT8	m_CurSendPktNum;
	UINT16	m_CurIxInRcvPkt;
	UINT8	m_CurRcvPktNum;
	UINT32  m_ExptnHndlr;
	UINT8	m_IsSending;
	UINT16	m_ExptnType;
	UINT8	m_PrevByteEsc;
	UINT8	m_RcvingPkt;
	UINT8	m_RcvPktReady;
	UINT16	m_RcvPktSize;
	UINT8	m_IsPortInListenMode;
	UINT8	m_IsHostConnected;
	UINT8	m_IsPeiDbgIsS3;
#ifndef	USB_DEBUGGER
	UINT16  m_BaseAddr;
//	UINT8	m_IsCOMPortInListenMode;
//	UINT32	m_ReadAttempts;			//only for debugging purpose -remove later
//	UINT8	m_CacheRecvFIFO[24];
//	UINT8	m_CacheSize;
//	UINT8	m_CacheIndex;

	//To obtain info from Porting template support, and use it to publish HOB
	UINT8	m_SIO_LDN_UART;			//Logical Device Number for COM port
#else
	UINT32	USBBASE;
	UINT32	USB2_DEBUG_PORT_REGISTER_INTERFACE;
	UINT8	gDebugUSBAddress;
	UINT8	gDebugInEndpoint;
	UINT8	gDebugOutEndpoint;
	GET_DESCRIPTOR_DEBUG_PORT	Descriptor;
	UINT8	gUSBBulkTransferSetAddr;

	UINT8	gIN_DATAPID;
	UINT8	gOUT_DATAPID;

	UINT8	gIN_DATABUFFER[8];
	UINT8	gOUT_DATABUFFER[8];

	UINT8	gCurrentINDataBufferLength;
	UINT8	gCurrentINDataBufferIndex;
	UINT8	gCurrentOUTDataBufferIndex;

	UINT8 	lastdata;

	UINT8	gIsUsbDebugPortInUse;
//	UINT8	gIsUsbDebugPortInListenMode;

	//To obtain info from Porting template support, and use it to publish HOB
	UINT16	m_EHCI_MEMORY_SIZE;
	UINT8	m_PCI_EHCI_BUS_NUMBER;
	UINT8	m_PCI_EHCI_DEVICE_NUMBER;
	UINT8	m_PCI_EHCI_FUNCTION_NUMBER;
	UINT8	m_PCI_EHCI_BAR_OFFSET;
#endif
	UINT64	m_PeiDbgRxInitTimerVal;
}SerXPortGblData_T;

typedef struct {
	AMI_PEI_TRANSPORT_PROTOCOL	*gTransportProtocol;
	UINT16 (*Handler)();

	//Additional parameters added in order to support DXE phase callback of
	//IRQ register handlers
	UINTN	InterruptType;
	UINTN	ContextData;
	VOID	(*IRQRegisterHandler)(UINTN,UINTN);

#ifdef	USB_DEBUGGER
	//Additional interface for PeiDbgSIO module to reinit EHCI memory base
//	void	(*PeiDbgSIO_Init_USB_EHCI)(UINTN PeiDbgData_BaseAddr,UINTN MMIO_BaseAddr);
//	void	(*PeiDbgSIO_Init_USB_EHCI)(UINTN UsbBaseAddress, UINTN *Usb2DebugPortReg);
	void	(*PeiDbgSIO_Init_USB_EHCI)(VOID *);
#endif
}SerXPortGblVar_T;

typedef struct {
	UINT8	m_BrkPtType;
	UINT16	m_CS;
	UINT32	m_EIP;
	UINT16	m_SS;
	UINT32	m_ESP;
	UINT32	m_DR2;
	UINT32	m_DR7;
	UINT8	m_TargetRunning;
	UINT8	m_DbgrBusy;
	UINT8	m_DR2Valid;

	UINT8	m_GPOccrd;
	UINT8   m_MSRState;

	UINT8	m_NotifyAndBreak;

	UINT16	m_DbgSendBufSize;
	UINT16	m_DbgRcvBufSize;
	VOID	(*PeiDbgrReportStatusCode)();
	UINT8	m_FlagToDebugAfterMemory;
	UINTN	(*PeiDbgr_EnableDebugSupport)(UINTN BrkPtAddr);
	AMI_DEBUGGER_INTERFACE	*pPeiDbgDbgrIfc;
	UINT8	m_TargetState;
	VOID*	m_ppPeiSVC;
	EFI_STATUS (*UpdateFVHob)();
}DbgGblData_T;

#pragma pack()

#pragma pack(1)
typedef struct {
	UINT16	m_OffLow;
	UINT16	m_SegSel;
	UINT16	m_Reserved;
	UINT16	m_OffHigh;
}IDTEntry_T;

typedef struct {
	UINT16	IDTLength;
	UINTN	IDTBaseAddr;	//should work for both 32 and 64 mode
}IDTBASE;

typedef UINT8 (DBG_IS_S3)(void);
#pragma pack()

void DriverSpecialBreakPoint(UINT32 EaxVal, UINT32 EdxVal);

#endif

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
