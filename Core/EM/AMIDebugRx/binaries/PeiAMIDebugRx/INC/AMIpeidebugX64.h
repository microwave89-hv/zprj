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
// $Header: /Alaska/BIN/Modules/AMIDebugRx/binaries/PeiAMIDebugRx/INC/AMIpeidebugX64.h 5     3/09/11 8:22a Sudhirv $
//
// $Revision: 5 $
//
// $Date: 3/09/11 8:22a $
//*****************************************************************
//*****************************************************************
//
//	peidebug.h
//		
//
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/AMIDebugRx/binaries/PeiAMIDebugRx/INC/AMIpeidebugX64.h $
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
// 19    3/19/09 3:41p Sudhirv
// Added After changes for Target Sending Exception Packets
// 
// 17    1/30/09 12:32p Sudhirv
// Added after Console Redirection Support
// 
// 16    6/26/08 3:30p Sudhirv
// Uploaded after checking coding standards
// 
// 15    6/11/08 2:24p Sudhirv
// After Addibg GP Handling in MSR
// 
// 14    6/11/08 5:46a Sudhirv
// Uploaded for Release with Read/WriteMSR restriction, Readio/Writeio
// restriction, Read/Write IndirectIO, ListModules and PciList
// 
// 13    12/05/07 8:23a Sudhirv
// Added to support and Restrict ReadMSR/WriteMSR commands
// 
// 12    10/24/07 10:31a Madhans
// Hatdriver Support.
// 
// 11    8/29/07 3:49p Madhans
// To resolve AMD Platfrom issues.
// 
// 10    8/29/07 12:49p Madhans
// Common code for 4.x and 3.x
// 
// 9     6/13/07 3:16p Madhans
// Copyright Year updated.
// 
// 8     6/05/07 7:11p Natalyak
// Load FV support
// 
// 7     4/05/07 6:33p Madhans
// CAR_BASE_ADJUST_OFFSET removed.
// 
// 6     3/10/07 1:24p Madhans
// CAR_BASE_ADJUST_OFFSET allows to have PEI_SERVICES address above IDT
// 
// 5     2/23/07 5:37p Madhans
// Changes made for LoadImag PPI/Protocol Notifications.
// 
// 4     1/22/07 11:41a Madhans
// Modification made for Binary Release 1.04.0003.
// 
// 3     1/05/07 6:15p Madhan
// 
// 2     1/05/07 1:05p Ashrafj
// Latest version 1.04.0001 Beta
// Known issues from previous 1.04.000 Beta release has been fixed.
// 
// 1     12/26/06 7:09p Ashrafj
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
// Name:          AmiPeiDebugx64.C
//
// Description:   Contains X64 Pei Debugger prototypes
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>
#ifndef	_AMI_PEIDEBUGx64_H_
#define _AMI_PEIDEBUGx64_H_

#ifdef	USB_DEBUGGER
#include "EHCI.h"
#endif

#ifdef ALASKA_SUPPORT
#include "token.h"
#else
#include "tokens.h"
#endif

#ifdef ALASKA_SUPPORT
#if defined (PI_SPECIFICATION_VERSION) && (PI_SPECIFICATION_VERSION >= 0x00010000)
//#define	PEI_DEBUG_DATASECTION_BASEADDRESS	CAR_BASE_ADDRESS	//Starting address of PEI debugger data section
#else	
#define	PEI_DEBUG_DATASECTION_BASEADDRESS	CAR_BASE_ADDRESS	//Starting address of PEI debugger data section
#endif
#else	

#define PM_BASE_ADDRESS			APLIB_PM_BASE_ADDRESS
#define DATA_STACK_BASEADDRESS		APLIB_CAR_BASEADDRESS

#define PEI_DEBUG_DATASECTION_BASEADDRESS	DATA_STACK_BASEADDRESS  //Starting address of PEI debugger data section
#endif


#define PEI_DEBUG_DATASECTION_SIZEx64 \
		(IDT_SIZEx64 + CONTEXT_SIZEx64 + XPORTLOCALVAR_SIZEx64 + XPORTGLOBALVAR_SIZEx64\
		+ DBGRLOCALVAR_SIZEx64 + XPORTEXPTNBUF_SIZEx64 + GLOBALBUF_SIZEx64 + ACKBUF_SIZEx64)

#define IRQ_VECTOR_BASE	0x8

typedef struct {
	UINT8	Signature[4];
	UINT32	DATABASEADDRESS;
}PEI_DBG_DATA_SECTIONx64;

#ifdef	RELOCATE
extern	PEI_DBG_DATA_SECTIONx64		PeiDbgDataSection;
#define PEI_DEBUG_DATA_BASEADDRESS (PeiDbgDataSection.DATABASEADDRESS)
#else
#define PEI_DEBUG_DATA_BASEADDRESS	PEI_DEBUG_DATASECTION_BASEADDRESS  // Fixed Base Address
#endif
	
#define IDT_ENTRIES						0x14	    // Number of Entries in IDT
#define IDT_SIZEx64						0x160       // Total Size = 352 Bytes 
#define CONTEXT_SIZEx64					0x140	    // Total Size = 320 Bytes

#define XPORTLOCALVAR_SIZEx64			0x50	    // Total Size =  80 Bytes

#define XPORTGLOBALVAR_SIZEx64			0x30	    // Total Size =  48 Bytes
//#define DBGRLOCALVAR_SIZEx64			0x50	    // Total Size =  80 Bytes
#define DBGRLOCALVAR_SIZEx64			0x62	    // Total Size =  98 Bytes
#define XPORTEXPTNBUF_SIZEx64			0x20	    // Total Size =  32 Bytes

#define GLOBALBUF_SIZEx64				0x235	    // Total Size = 565 Bytes

#define ACKBUF_SIZEx64					0x0a		// Total Size =  10 Bytes 	



#define PEI_DEBUG_IDTBASEADDRx64			PEI_DEBUG_DATA_BASEADDRESS 
#define PEI_DEBUG_CONTEXTADDRx64			PEI_DEBUG_DATA_BASEADDRESS + IDT_SIZEx64		
#define PEI_DEBUG_XPORTLOCALVARADDRx64		PEI_DEBUG_CONTEXTADDRx64 + CONTEXT_SIZEx64		
#define PEI_DEBUG_XPORTGLOBALVARADDRx64		PEI_DEBUG_XPORTLOCALVARADDRx64 + XPORTLOCALVAR_SIZEx64		
#define PEI_DEBUG_DBGRLOCALVARADDRx64		PEI_DEBUG_XPORTGLOBALVARADDRx64 + XPORTGLOBALVAR_SIZEx64
#define PEI_DEBUG_XPORTEXPTNADDRx64			PEI_DEBUG_DBGRLOCALVARADDRx64 + DBGRLOCALVAR_SIZEx64
#define PEI_DEBUG_BUFADDRx64				PEI_DEBUG_XPORTEXPTNADDRx64 + XPORTEXPTNBUF_SIZEx64
#define	PEI_DEBUG_ACKADDRx64				PEI_DEBUG_BUFADDRx64 + GLOBALBUF_SIZEx64					


#pragma pack (push, pei_struct_data_pack, 1)

typedef struct {
	unsigned char	IDTSet[IDT_SIZEx64];
	unsigned char	ContextReg[CONTEXT_SIZEx64];
	unsigned char	XportLocalVar[XPORTLOCALVAR_SIZEx64];
	unsigned char	XportGlobalVar[XPORTGLOBALVAR_SIZEx64];
	unsigned char	DbgrLocalVar[DBGRLOCALVAR_SIZEx64];
	unsigned char	XportExptn[XPORTEXPTNBUF_SIZEx64];
	unsigned char	GlobalBuf[GLOBALBUF_SIZEx64];
	unsigned char	AckBuf[ACKBUF_SIZEx64];
}PEIDebugData_Tx64;


#pragma pack (pop, pei_struct_data_pack)


#pragma pack(1)
typedef struct {
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
	VOID	(*IrqHandler)();	//Not to be use as API by any other drivers	
} AMI_PEI_TRANSPORT_PROTOCOLx64;	

//typedef	UINT32	GET_DESCRIPTOR_DEBUG_PORT;

//#pragma pack(1)
typedef struct {
	UINT64	m_EIP;
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
}SerXPortGblData_Tx64;

typedef struct {
	AMI_PEI_TRANSPORT_PROTOCOLx64	*gTransportProtocol;
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
}SerXPortGblVar_Tx64;

typedef	struct{
	UINT8	Signature[4];
	VOID	(*ExceptionCallback)();
	VOID	(*SendMessage)();
	UINTN	(*PeiDbgr_EnableDebugSupport)(UINTN BrkPtAddr);
	VOID	(*INT1ExceptionHandler)();		//not to be use as API
	VOID	(*INT3ExceptionHandler)();		//not to be use as API
	VOID	(*INTnExceptionHandler)();		//not to be use as API
	UINTN	(*PeiDbgr_SendPeiLoadImage)(UINTN FileHandle,UINTN ImageAddr,UINTN ImageSize,void * PDBFileName);
	VOID	(*INTFExceptionHandler)();		//not to be use as API
}AMI_DEBUGGER_INTERFACEx64;

typedef struct {
	UINT8	m_BrkPtType;
	UINT16	m_CS;
	UINT64	m_EIP;
	UINT16	m_SS;
	UINT64	m_ESP;
	UINT64	m_DR2;
	UINT64	m_DR7;
	UINT8	m_TargetRunning;

	UINT8	m_MSRState;
	UINT8	m_GPOccrd;
	
	UINT8	m_NotifyAndBreak;

	UINT8	m_DbgrBusy;
	UINT8	m_DR2Valid;
	UINT16	m_DbgSendBufSize;
	UINT16	m_DbgRcvBufSize;
	UINT64	m_BackupDR7;
	UINT8	m_PICMask;
	union{
	VOID	(*PeiDbgrReportStatusCode)();
	UINT64	res1;
	};
	UINT8	m_FlagToDebugAfterMemory;
	union{
	UINTN	(*PeiDbgr_EnableDebugSupport)(UINTN BrkPtAddr);
	UINT64	res2;
	};
	union{
	AMI_DEBUGGER_INTERFACEx64	*pPeiDbgDbgrIfc;
	UINT64	res3;
	};
	UINT8	m_TargetState;
	VOID*	m_ppPeiSVC;
//	VOID*	m_pFVHob;
	EFI_STATUS (*UpdateFVHob)();
}DbgGblData_Tx64;
//#pragma pack()

//#pragma pack(1)
typedef struct {
	UINT16	m_OffLow;
	UINT16	m_SegSel;
	UINT16	m_Reserved;
	UINT16	m_OffHigh;
	UINT32	m_OffHighExt;
	UINT32	m_Reserved2;
}IDTEntry_Tx64;

typedef struct {
	UINT16	IDTLength;
	UINT64	IDTBaseAddr;	//should work for both 32 and 64 mode
}IDTBASEx64;
#pragma pack()

//=========================================================================
// Prototypes of structure definitions to be used handoff of 32 to 64 PEI 
// Debugger
//=========================================================================
#pragma pack(1)
typedef struct {
	UINT64	gTransportProtocol;		//AMI_PEI_TRANSPORT_PROTOCOL	*gTransportProtocol;
	UINT64	Handler;				//UINT16 (*Handler)();

	//Additional parameters added in order to support DXE phase callback of
	//IRQ register handlers
	UINTN	InterruptType;
	UINTN	ContextData;
	UINT64	IRQRegisterHandler;			//VOID	(*IRQRegisterHandler)(UINTN,UINTN);

#ifdef	USB_DEBUGGER
	UINT64	PeiDbgSIO_Init_USB_EHCI;	//void	(*PeiDbgSIO_Init_USB_EHCI)(VOID *);
#endif
}SerXPortGblVar_Tx64_Proto;

typedef	struct{
	UINT8	Signature[4];
	UINT64	pExceptionCallback;				//VOID	(*ExceptionCallback)();
	UINT64	pSendMessage;					//VOID	(*SendMessage)();
	UINT64	pPeiDbgr_EnableDebugSupport;	//UINTN	(*PeiDbgr_EnableDebugSupport)(UINTN BrkPtAddr);
	UINT64	pINT1ExceptionHandler;			//VOID	(*INT1ExceptionHandler)();
	UINT64	pINT3ExceptionHandler;			//VOID	(*INT3ExceptionHandler)();
	UINT64	pINTnExceptionHandler;			//VOID	(*INTnExceptionHandler)();
	UINT64  pPeiDbgr_SendPeiLoadImage;		//UINTN	(*PeiDbgr_SendPeiLoadImage)(UINTN FileHandle,UINTN ImageAddr,UINTN ImageSize,void * PDBFileName);
	UINT64	pINTFExceptionHandler;			//VOID	(*INTFExceptionHandler)();
}AMI_DEBUGGER_INTERFACEx64_Proto;

typedef struct {
	UINT8	Signature[4];				
	UINT64	pInitialize;					//UINT16	(*Initialize)();			
	UINT64	pRestore;						//UINT16	(*Restore)();				
	UINT64	pSend;							//UINT16	(*Send)();				
	UINT64	pReceive;						//UINT16	(*Receive)();			
	UINT64	pSyncPacketNumber;				//UINT16	(*SyncPacketNumber)();	
	UINT64	pRegisterHandler;				//UINT16  (*RegisterHandler)();		
	UINT64	pCallback;						//VOID	(*Callback)();
	UINT64	pSendNoAck;						//UINT16	(*SendNoAck)();
	UINT64	pConsoleIn;						//	EFI_STATUS	(*ConsoleIn)();
	UINT64	pSendExptn;						//	VOID 	(*SendExptn)();
	UINT64	pIrqHandler;					//VOID	(*IrqHandler)();
} AMI_PEI_TRANSPORT_PROTOCOLx64__Proto;
#pragma pack()

#ifdef	EFIx64
typedef PEI_DBG_DATA_SECTIONx64			PEI_DBG_DATA_SECTION;
typedef	DbgGblData_Tx64 				DbgGblData_T;
typedef SerXPortGblData_Tx64 			SerXPortGblData_T;
typedef PEIDebugData_Tx64 				PEIDebugData_T;
typedef AMI_PEI_TRANSPORT_PROTOCOLx64 	AMI_PEI_TRANSPORT_PROTOCOL;
typedef SerXPortGblVar_Tx64				SerXPortGblVar_T;
typedef AMI_DEBUGGER_INTERFACEx64		AMI_DEBUGGER_INTERFACE;
typedef IDTEntry_Tx64					IDTEntry_T;
typedef IDTBASEx64						IDTBASE;

#define PEI_DEBUG_IDTBASEADDR			PEI_DEBUG_IDTBASEADDRx64 
#define PEI_DEBUG_CONTEXTADDR			PEI_DEBUG_CONTEXTADDRx64
#define PEI_DEBUG_XPORTLOCALVARADDR		PEI_DEBUG_XPORTLOCALVARADDRx64
#define PEI_DEBUG_XPORTGLOBALVARADDR	PEI_DEBUG_XPORTGLOBALVARADDRx64
#define PEI_DEBUG_DBGRLOCALVARADDR		PEI_DEBUG_DBGRLOCALVARADDRx64
#define PEI_DEBUG_XPORTEXPTNADDR		PEI_DEBUG_XPORTEXPTNADDRx64
#define PEI_DEBUG_BUFADDR				PEI_DEBUG_BUFADDRx64
#define	PEI_DEBUG_ACKADDR				PEI_DEBUG_ACKADDRx64
#endif

//=========================================================================
//#define SET_SWBRKPT	_SetBrkPt:0xcc;
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
