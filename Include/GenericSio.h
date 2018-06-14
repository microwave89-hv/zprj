//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2005, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
// $Header: /Alaska/BIN/Core/Include/GenericSio.h 13    11/11/11 4:03p Yakovlevs $
//
// $Revision: 13 $
//
// $Date: 11/11/11 4:03p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/GenericSio.h $
// 
// 13    11/11/11 4:03p Yakovlevs
// [TAG]  		EIP72716 
// [Category]  	Improvement
// [Description]  	Added Messages, Fixed issues in proposed by AMI China
// solution.
// [Files]  		GenericSio.c; GenericSio.h
// 
// 12    5/06/11 5:09p Yakovlevs
// Made depencency on PI_SPECIFICATIO_VERSION tolen
// 
// 11    5/04/11 6:02p Yakovlevs
// [TAG]  		EIP 56527
// [Category]  	New Feature
// [Description]  	AMI_SIO_PROTOCOL was the source for PI 1.2 spec
// proposal. Will require some minor modification of the interface plus
// adding EFI_SIO_PROTOCOL Modify() function.
// [Files]  		GenericSio.h; GenericSio.c.
// 
// 10    12/01/08 10:32a Yakovlevs
// Added isAfterBootScript SIO initialization step definition.
// 
// 9     6/11/07 11:55p Yakovlevs
// Changed definition of SIO_RESOURCE_FLAG 
// SIO_NO_RES value 0x80 meands Device does not use resources it just
// needs to be enabled.
// 
// 8     5/14/07 7:05p Yakovlevs
// Changes to support SIO Setup Data Override.
// // Usefull if SIO uses none  standard Setup Screens and Data Storage.
// 
// 7     12/26/06 10:37a Yakovlevs
// Changes for dynamic IRQ assignment
// 
// 6     7/21/06 11:36a Yakovlevs
// Added ImageHandle field to the end of SPIO_DEV structure
// 
// 5     4/10/06 5:22p Yakovlevs
// ACPI NO ACPI mode fix.
// Added function prototypes for Setting Device _PRS in NONE ACPI mode
// 
// 4     4/03/06 5:04p Felixp
// Headers updated in accordance with new PCI and Super I/O infrastructure
// 
// 3     11/23/05 11:22a Felixp
// dev_status renamed to DEV_STATUS.
// 
// 2     11/21/05 5:00p Ambikas
// Added SIO_DEV_STATUS definition and related constants. 
// 
// 1     2/08/05 10:52a Felixp
// 
// 2     2/07/05 7:04p Yakovlevs
// Preparation has been done to split SIO module into Generic and Porting
// Part
// 
// 1     2/01/05 3:06a Felixp
// 
// 1     2/01/05 3:05a Felixp
// 
// 4     1/31/05 11:49p Felixp
// 
// 3     1/31/05 11:44p Felixp
// 
// 2     1/18/05 3:21p Felixp
// PrintDebugMessage renamed to Trace
// 
// 1     1/11/05 7:09p Felixp
// 
// 2     12/23/04 10:25a Felixp
// 
// 4     12/22/04 6:42p Yakovlevs
// 
// 2     10/20/04 11:44a Yakovlevs
// 
// 1     10/19/04 7:21p Yakovlevs
// 
// 1     1/16/04 10:26a Markw
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	Sio.h
//
// Description:	AMI Sio Protocol Definitions.
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef _GENERIC_SIO_H_
#define _GENERIC_SIO_H_


#ifdef __cplusplus
extern "C" {
#endif

#include <Efi.h>
#include <Protocol\DevicePath.h>
#include <Protocol\BootScriptSave.h>
#include <Protocol\AmiSio.h>
#include <Protocol\PciIo.h>
#include <AmiDxeLib.h>
#if ((defined PI_SPECIFICATION_VERSION) && (PI_SPECIFICATION_VERSION >= 0x00010014))
#include <Protocol\SuperIo.h>
#endif;
#include <Token.h>
//---------------------------------------------------------
//To exclude SIO Messages
#ifndef TRACE_SIO
#define TRACE_SIO TRACE_ALWAYS
#endif

#if SIO_DEBUG_MESSAGES
#define SIO_TRACE(Arguments) TRACE(Arguments)
#else
#define SIO_TRACE(Arguments)
#endif
//---------------------------------------------------------


#define PNP_HID EFI_PNP_ID

//--------------------------------------------
//Defines how to enter Exit config Mode
typedef enum _SPIO_GFG_OP_TYPE{
	cfgNone=0,		//Not required any sequence
	cfgByteSeq,
	cfgRoutine,
	cfgMaxCfg
} SPIO_GFG_OP_TYPE;

typedef VOID (*SPIO_ROUTINE)();

typedef struct _SPIO_SCRIPT {
	BOOLEAN		IdxDat;	//1=IDX 0=DAT
	BOOLEAN		WrRd; 	//1=Write 0=Read
	UINT8		Value; 	//if WrRd=0 wait for this data to come	
} SPIO_SCRIPT;

typedef struct SPIO_SCRIPT_LST {
	SPIO_GFG_OP_TYPE	OpType;
	UINTN				InstrCount;		
	VOID				*Instruction[]; 	//using woid pointer to specify 
										//script or routine
} SPIO_SCRIPT_LST;

//==================================================================
//Definitions of SIO Shared Resource Flags if this flags set 
//and will share following type of resources with PREVIOUSE device
#define SIO_SHR_NONE	0x00
#define SIO_SHR_IO1		0x01 //device shares resources programmed in SIO_1_BASE_REG
#define SIO_SHR_IO2		0x02 //device shares resources programmed in SIO_2_BASE_REG	
#define SIO_SHR_IO		(SIO_SHR_IO1 | SIO_SHR_IO2) //device shares resources programmed in both SIO_BASE_REG
#define SIO_SHR_IRQ1	0x04	
#define SIO_SHR_IRQ2	0x08
#define SIO_SHR_IRQ		(SIO_SHR_IRQ1 | SIO_SHR_IRQ2)
#define SIO_SHR_DMA1	0x10
#define SIO_SHR_DMA2	0x20
#define SIO_SHR_DMA		(SIO_SHR_DMA1 | SIO_SHR_DMA2)
#define SIO_SHR_ALL		(SIO_SHR_IO | SIO_SHR_IRQ | SIO_SHR_DMA)
#define SIO_NO_RES		0x80 //this bit will be set if device not using any resources but must be enabled
//all other values reserved

#pragma pack(push,1)

	typedef struct _SIO_DEV_V_DATA {
		UINT8		DevImplemented;	
		UINT16		DevBase1;
		UINT16		DevBase2;
		UINT8		DevIrq1;
		UINT8		DevIrq2;
		UINT8		DevDma1;
		UINT8		DevDma2;
	} SIO_DEV_V_DATA;

	typedef struct _SIO_DEV_NV_DATA {
		UINT8		DevEnable;
		UINT8		DevPrsId;
		UINT8		DevMode;
	} SIO_DEV_NV_DATA;

#pragma pack(pop)

typedef enum {
	isNone=0,
	isPrsSelect,
	isBeforeActivate,
	isAfterActivate,
	isGetSetupData,
    isAfterBootScript, //this init step will be invoked after all SIO regs added to boot script
                       //for each device which has initialization function implemented.  
	isMaxInitStep
} SIO_INIT_STEP;

//SIO Component Initialization Routine ptrototype
typedef EFI_STATUS (*SIO_INIT)( IN AMI_SIO_PROTOCOL 	*This, 
								IN EFI_PCI_IO_PROTOCOL 	*PciIo, 
								IN SIO_INIT_STEP 		InitStep);

//Device table used for porting see YourSioNameDxe.c 
typedef struct _SPIO_DEV_LST {
	SIO_DEV_TYPE	Type;
	UINT8			LDN;		//LogicalDevice #
	UINT8			UID; 		//Unique ID if there are 2 or more 
								//devices of the same type in this SPIO 
	UINT16			PnpId;
	BOOLEAN     	Implemented;//Implemented on this Platform (has connector)
	BOOLEAN			HasSetup;	//TRUE If Device has SETUP screen and se
	UINT8			Flags;		//set if Device shares all or some of it's resources 
	UINT8			AslName[5]; //ASL DEVICE OBJECT NAME to look for _PRS in AML
								//if this field not 0,0,0,0 the rest of the table ignored.
	UINT16			ResBase[2];	//Base Address for SIO_1_BASE_REG and SIO_2_BASE_REG
	UINT8			ResLen[2];
	UINT16			IrqMask[2];
	UINT8			DmaMask[2];
	SIO_INIT		InitRoutine;
//	UINTN			SetupOffset; //offset in SIO_SETUP_VAR for this device if any
//	UINTN			VolatileOffset; //offset in SIO_SETUP_VOLATILE data for this device if any
} SPIO_DEV_LST;

//This structure will define a multiple SIO Porting Information
//It will be an array of such structures each of them will represent
//a different SIO Device.
typedef struct _SPIO_LIST_ITEM {
	//This Information is needed to identify right LPC bridge for the SIO
	// value of  -1 (0xF..F) means Do not check this parameter
	UINT32			IsaVenDevId; 
	UINT32			IsaSubVenId;
	UINT8			IsaBusNo;
	UINT8			IsaDevNo;
	UINT8			IsaFuncNo;
//	//This is the information Needed Get Sio Setup Data
//	//----------------------------------------
//	UINT16			*SetupVarName;
//	UINT16			*VolatileVarName;
//	EFI_GUID		*SioVarGuid;
//	//This is the information Needed to access SIO Generic Registers
//	//----------------------------------------
	UINT16			SioIndex;
	UINT16			SioData;
	// Dev Select and Activate
	UINT8			DevSel;
	UINT8			Activate;
	UINT8			ActivVal;
	UINT8			DeactVal;
	//Generic registers location
	UINT8			Base1Hi;
	UINT8			Base1Lo;
	UINT8			Base2Hi;
	UINT8			Base2Lo;
	UINT8			Irq1;
	UINT8			Irq2;
	UINT8			Dma1;
	UINT8			Dma2;
	//List of devices inside this SIO
	UINTN			DevCount;
	SPIO_DEV_LST	*SioDevList;
	//List of valid registers inside SIO to check if they has to be saved
	//----------------------------------------
	//in BOOT_SCRIPT_SAVE for S3 state Resume 
	//This is for global registers which are the same for all devices in SIO
	UINTN			GlobalInclRegCount;
	UINT8			*GlobalIncludeReg; //Buffer will be located in GSPIO structure
	//This is for Local registers they are unique for each device in SIO
	UINTN			LocalInclRegCount;
	UINT8			*LocalIncludeReg; //Buffer will be located in SIO_DEV structure
	//----------------------------------------
	//How To enter/exit Configuration mode if any 
	SPIO_SCRIPT_LST	*EnterCfgMode;
	SPIO_SCRIPT_LST	*ExitCfgMode;
}SPIO_LIST_ITEM;

typedef struct _GSPIO GSPIO;

#if ((defined PI_SPECIFICATION_VERSION) && (PI_SPECIFICATION_VERSION >= 0x00010014))
typedef struct _EFI_SIO_DATA{
    EFI_SIO_PROTOCOL    EfiSio;
    struct _SPIO_DEV    *Owner;        
}EFI_SIO_DATA;
#endif

//SPIO Device Private Data section
typedef struct _SPIO_DEV {
	AMI_SIO_PROTOCOL	AmiSio;
	EFI_DEVICE_PATH_PROTOCOL *DevicePath;
	EFI_HANDLE			Handle;
//	BOOLEAN				Implemented;	//Present in SPIO_DEV.DeviceInfo;
	BOOLEAN				Started;
	BOOLEAN				Assigned;
	BOOLEAN				Initialized;
	BOOLEAN				IrqReserved;
//	UINT8				LDN;			//Present in SPIO_DEV.DeviceInfo;
//	UINTN				Flags;			//Present in SPIO_DEV.DeviceInfo;
	struct _SPIO_DEV	*ResOwner;
	struct _SPIO_DEV	*ResConsumer;
//	SIO_DEV_TYPE		Type;			//Present in SPIO_DEV.DeviceInfo;
	EFI_EISAID			EisaId;
	T_ITEM_LIST			CRS;
	T_ITEM_LIST			PRS;
	//SIO_INIT			InitRoutine;	//Present in SPIO_DEV.DeviceInfo;
//we will need it to generate boot script for s3 resume
	UINT8				*LocalCfgDump;
	GSPIO				*Owner;	
	SPIO_DEV_LST		*DeviceInfo;
	SIO_DEV_NV_DATA		NvData;
	SIO_DEV_V_DATA		VlData;	
	EFI_HANDLE			ImageHandle;
#if ((defined PI_SPECIFICATION_VERSION) && (PI_SPECIFICATION_VERSION >= 0x00010014))
    EFI_SIO_DATA        EfiSioData;
#endif;
} SPIO_DEV;

//Global Super IO device Private Structure
typedef struct _GSPIO {
	//UINT16			Indx;
	//UINT16			Data;
//	EFI_HANDLE		ImageHandle; don't need it since we have it gAmiSioDriverBinding.ImageHandle
	EFI_HANDLE		CntrHandle;
	EFI_HANDLE		SupportedHandle; //
	EFI_DEVICE_PATH_PROTOCOL 	*CntrDevPath;
	EFI_PCI_IO_PROTOCOL *IsaBrgPciIo;
	BOOLEAN			InCfgMode;
	UINTN			DeviceCount;
	SPIO_DEV		**DeviceList;
	//we will need it to generate boot script for s3 resume
	UINT8			*GlobalCfgDump;
	SPIO_LIST_ITEM	*SpioInfo;
    EFI_BOOT_SCRIPT_SAVE_PROTOCOL *BootScript;
} GSPIO;

#define SIO_DEV_STATUS_VAR_NAME  L"SIO_DEV_STATUS_VAR"

#define SIO_DEV_STATUS_VAR_GUID \
	{0x5820de98, 0xfc8e, 0x4b0b, 0xa4, 0xb9, 0xa, 0x94, 0xd, 0x16, 0x2a, 0x7e}

//
// Bit values of various SIO devices defined in SIO_DEV_STATUS
//
#define SIO_DEV_COM1		0x0001
#define SIO_DEV_COM2		0x0002
#define SIO_DEV_LPT			0x0004
#define SIO_DEV_FDC			0x0008
#define SIO_DEV_SB16		0x0010
#define SIO_DEV_MIDI		0x0020
#define SIO_DEV_MSSAUDIO	0x0040
#define SIO_DEV_FMSYNTH		0x0080
#define SIO_DEV_GAME1		0x0100
#define SIO_DEV_GAME2		0x0200
#define SIO_DEV_KBC			0x0400
#define SIO_DEV_EC			0x0800
#define SIO_DEV_PS2MS		0x4000

typedef union {
	UINT16	DEV_STATUS;
	struct  {
		UINT16 	SerialA		: 1;	//bit 0 - Serial A
		UINT16 	SerialB 	: 1;	//bit 1	- Serial B
		UINT16  Lpt			: 1;	//bit 2 - LPT
		UINT16	Fdd			: 1;	//bit 3 - FDD
		UINT16	Sb16		: 1;	//bit 4 - SB16 Audio
		UINT16	Midi		: 1;	//bit 5 - MIDI
		UINT16	MssAudio	: 1;	//bit 6 - MSS Audio
		UINT16	FmSynth		: 1;	//bit 7 - AdLib sound (FM synth)
		UINT16	Game1		: 1;	//bit 8 - Game port #1
		UINT16	Game2		: 1;	//bit 9 - Game port #2
		UINT16	Key60_64	: 1;	//bit a - KBC
		UINT16	Ec62_66		: 1;	//bit b - EC
		UINT16	Res1		: 1;	//bit c - Reserved
		UINT16	Res2		: 1;	//bit d - Reserved
		UINT16	Ps2Mouse	: 1;	//bit e - PS/2 Mouse
		UINT16	Res3		: 1;	//bit f - Reserved
	};
} SIO_DEV_STATUS;

#if ACPI_SUPPORT
//_PRS Functions definition for ACPI 
EFI_STATUS GetPrsFromAml(SPIO_DEV* Dev, UINT8 *PrsName ,UINTN Index);
#else
//and NO ACPI mode
EFI_STATUS SetUartPrs(SPIO_DEV *Dev);
EFI_STATUS SetLptPrs(SPIO_DEV *Dev, BOOLEAN UseDma);
EFI_STATUS SetFdcPrs(SPIO_DEV *Dev);
EFI_STATUS SetPs2kPrs(SPIO_DEV *Dev);
EFI_STATUS SetPs2mPrs(SPIO_DEV *Dev);
EFI_STATUS SetGamePrs(SPIO_DEV *Dev);
EFI_STATUS SetMpu401Prs(SPIO_DEV *Dev);
#endif




/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2005, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
