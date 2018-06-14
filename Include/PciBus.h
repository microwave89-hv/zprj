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
// $Header: /Alaska/BIN/Core/Modules/PciBus/PciBus.h 18    4/19/11 2:31p Yakovlevs $
//
// $Revision: 18 $
//
// $Date: 4/19/11 2:31p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Modules/PciBus/PciBus.h $
// 
// 18    4/19/11 2:31p Yakovlevs
// 
// 17    4/19/11 10:58a Yakovlevs
// [TAG]  		EIP 57664
// [Category]  	New Feature
// [Description]  	Aptio PI 1.2; UEFI 2.3.1 Support Extended PCI bus
// driver functionality
// [Files]  		DevicePath.h; LoadFile2.h; PciBus.h; PciBus.c.
// 
// 16    4/05/11 10:55a Yakovlevs
// [TAG]  		EIP38174
// [Category]  	New Feature
// [Description]  	Added generic support to handle PCI OUT OF RESOURDCES. 
// [Files]  		PciBus.c; PciHostBridge.c;  PciBus.h;  PciHostBridge.c;
// PciPort.c
// 
// 15    8/16/10 1:13p Yakovlevs
// 
// 14    3/01/10 5:59p Yakovlevs
// Pci Express V2.1 Support Added.
// 
// 13    9/22/09 6:06p Yakovlevs
// 
// 12    4/28/09 3:53p Yakovlevs
// Changes related to AmiBoardInfo protocol and Multiplatform support.
// 
// 11    3/25/09 10:54a Yakovlevs
// PCI_BRG_CNT_REG definition and APPLICATION added
// 
// 10    1/30/09 12:52p Yakovlevs
// Added MaxPayload field to the PCIE_DEV info structure EIP 17947
// 
// 9     10/01/08 1:08a Felixp
// 
// 8     10/01/08 12:25a Felixp
// 
// 7     9/25/08 11:31a Yakovlevs
// Changes in data structure to support new features.
// 
// 6     4/29/08 6:52p Yakovlevs
// 
// 5     12/10/07 4:23p Yakovlevs
// Added field in PCI_BRG_EXT structure to support PciBus.c recent
// changes.
// 
// 4     12/10/07 4:21p Yakovlevs
// Added field in PCI_BRG_EXT structure to support PciBus.c recent
// changes.
// 
// 3     10/16/07 4:58p Davidd
// 
// 4     10/15/07 4:14p Yakovlevs
// Added ResGran field into BRG_ALIGN_INFO structure.
// 
// 3     8/31/07 11:17a Yakovlevs
// Changes in Data Structures to accomodate improuvements in PCI Resource
// Allocation Algorithm.
// 
// 1     5/25/07 1:50p Yakovlevs
// 
// 2     5/02/07 4:42p Yakovlevs
// 
// 1     3/12/07 12:08p Yakovlevs
// 
// 16    10/13/06 4:23p Yakovlevs
// Support for IDE specisl Attributes added
// 
// 15    9/20/06 7:23p Yakovlevs
// Code cleanup. Structure headers Added!
// 
// 14    9/19/06 7:08p Yakovlevs
// Some code clen up
// 
// 13    8/09/06 5:10p Yakovlevs
// PCI Express VC initialization support 
// 
// 12    4/03/06 5:04p Felixp
// Headers updated in accordance with new PCI and Super I/O infrastructure
// 
// 11    3/13/06 1:15a Felixp
// 
//**********************************************************************

//<AMI_FHDR_START>
//---------------------------------------------------------------------------
// Name:		PciBus.h
//
// Description:	This header file contains Data Type Definitions for 
//				the PCI Bus Driver Private Data 
//
// Tabsize:		4
//---------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef _PCI_BUS_DRIVER_
#define _PCI_BUS_DRIVER_
#ifdef __cplusplus
extern "C" {
#endif

//---------------------------------------------------------------------------
// Include Files
//---------------------------------------------------------------------------
#include <Efi.h>
#include <Pci.h>
#include <PciE.h>
#include <PciE21.h>
#include <PciE30.h>
#include <PciX.h>
#include <AcpiRes.h>
#include <Protocol\PciIo.h>
#include <Protocol\BusSpecificDriverOverride.h>
#include <Protocol\DevicePath.h>
#include <Protocol\PciHostBridgeResourceAllocation.h>
#include <Protocol\PciHotplugInit.h>
#include <Protocol\PciPlatform.h>
#include <Protocol\AmiBoardInfo.h>
#include <Protocol\IncompatiblePciDeviceSupport.h>
#if ((defined EFI_SPECIFICATION_VERSION) && (EFI_SPECIFICATION_VERSION >= 0x2001F))
#include <Protocol\LoadFile2.h>
#endif
#include <Token.h>

#pragma pack(push, 1)
/////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------
// Constants Definitions
//---------------------------------------------------------------------------
//To exclude PCI Bus Messages
#ifndef TRACE_PCI
#define TRACE_PCI TRACE_ALWAYS
#endif
#if PCI_BUS_DEBUG_MESSAGES
#define PCI_TRACE(Arguments) TRACE(Arguments)
#else
#define PCI_TRACE(Arguments)
#endif


#define PCI_ASSEMBLE_ADDR(b,d,f,r) \
  ((UINT64) ( (((UINTN)b) << 24) + (((UINTN)d) << 16) + (((UINTN)f) << 8) + ((UINTN)r) ))

//I will need to store some more information for device cpabilities
//the standard PCI IO Attributes has bits from 1 to 0x40000 defined
//the attributes is 64 bit value ... 
#define MY_PCI_IO_ATTRIBUTE_MEM_WR_INVALIDATE    0x8000000000000000  

// I/O cycles 0x3C6, 0x3C8, 0x3C9 (10 bit decode) 
// MEM cycles 0xA0000-0xBFFFF (24 bit decode)
//I/O cycles 0x3B0-0x3BB and 0x3C0-0x3DF (10 bit decode)
#define PCI_VGA_ATTRIBUTES (EFI_PCI_IO_ATTRIBUTE_VGA_PALETTE_IO | \
							EFI_PCI_IO_ATTRIBUTE_VGA_MEMORY     | \
							EFI_PCI_IO_ATTRIBUTE_VGA_IO         )  


//Defining Attributes MASK which could be set based on Platform code 
#define PCI_ALLOWED_ATTRIBUTES (EFI_PCI_IO_ATTRIBUTE_EMBEDDED_DEVICE | EFI_PCI_IO_ATTRIBUTE_EMBEDDED_ROM)

//Only this attributes make sence for the BAR 
#define BAR_ATTR (EFI_PCI_IO_ATTRIBUTE_MEMORY_CACHED | EFI_PCI_IO_ATTRIBUTE_MEMORY_WRITE_COMBINE)

//PciBus Driver Signature UINT64
#define AMI_PCI_SIG			0x24494350494d4124 //'$AMIPCI$'


/////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------
//Forward Declaration
//---------------------------------------------------------------------------
typedef struct _PCI_DEV_INFO 	PCI_DEV_INFO;
typedef struct _PCI_HOST_INFO	PCI_HOST_INFO;

/////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------
//PCI Bus Driver Types Definitios
//---------------------------------------------------------------------------

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:		PCI_INCOMPATIBILITY_TYPE
//
// Description:	ENUM used to specify PCI Device Incompatibility Type for Device that
// doesn't comply with defined in PCI Spec enumeration algorithm.
//
// Fields:		
//	Name			Type					Description
//   ------------------------------------------------------------------
//	icNone			ENUM		Device is Compatible with PCI Spec 
//	icBarBad		ENUM		Device doesn't set all implemented bits as "1" after writing there all "1"s. Setting icBadBar will notify PCI bus Driver that it could be a sizing problems with this BAR and it should treat this BAR differently.
//	icBarFixedSize	ENUM		Device could hang the system if all "1s" will be written in corresponded BAR register. Setting icBarFixedSize will	notify PCI bus Driver to use Value provided in Incompatible Devices table intead of querying the Device.
//	icNotBar 		ENUM		Device has a read/write register implemented but this register must not be enumerated. So the PCI Bus Driver will not consider this BAR as valid and will skip it. 
//  icBad64BitBar   ENUM		Device has a bar that is 64bit capable, but the card does not function properly when it is allocated with an address above 4G.
//	icMaxIncompatibility ENUM	Last valid value of this ENUM 
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
typedef enum {
	icNone,   	
	icBarBad,	
	icBarFixedSize,
	icNotBar, 
	icBad64BitBar,
	icMaxIncompatibility
} PCI_INCOMPATIBILITY_TYPE;


//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:		PCI_SPACE_TYPE
//
// Description:	This ENUM value definitions used to identify PCI Device's different Space types.
//
// Fields:		
//	Name			Type					Description
//   ------------------------------------------------------------------
//	stMemSpace		ENUM				Memory Space
//	stIoSpace		ENUM				I/O Space
//	stMemIoSpace	ENUM				Memory and I/O Space
//	stOptRomSpace	ENUM				PCI Option ROM Space
//	stDisableAll	ENUM				Disable all possinble decoding
//	stMaxType		ENUM				Last valid value of this ENUM 
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
typedef enum {
	stMemSpace,
	stIoSpace,
	stMemIoSpace,
	stOptRomSpace,
	stDisableAll,
	stMaxType
} PCI_SPACE_TYPE;


//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:		MRES_TYPE
//
// Description:	This ENUM value definitions used to identify PCI Device different Resource types.
//
// Fields:		
//	Name			Type					Description
//   ------------------------------------------------------------------
//	rtBus			ENUM				Bus resources 
//	rtIo16			ENUM				I/O 16bit Resources
//	rtIo32			ENUM				I/O 32bit Resources
//	rtMmio32		ENUM				MMIO 32bit Resources
//	rtMmio32p		ENUM				Prefetchable MMIO 32bit 
//	rtMmio64		ENUM				MMIO 64bit Resources
//	rtMmio64p		ENUM				Prefetchable MMIO 64bit
//	rtMaxRes		ENUM				Last valid value of this ENUM 
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
typedef enum {
	rtBus=0,
	rtIo16,		//1
	rtIo32,		//2
	rtMmio32,	//3
	rtMmio32p,	//4
	rtMmio64,	//5
	rtMmio64p,	//6
	rtMaxRes	
} MRES_TYPE;


//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:		RES_CONV_TYPE
//
// Description:	This ENUM used to identify PCI Device Resource Conversion Type
//
// Notes:	Standard P2P bridge supports 16 or 32 bit IO(rcOneOf) only 32 
//			bit MMIO(rcNarrow) and One Of PF MMIO either 64 or 32 bit (rcOneOf).
//
// Fields:		
//	Name			Type					Description
//   ------------------------------------------------------------------
//	rcNone			ENUM 		Device doesn't supports any width of IO, MMIO, or PF MMIO. 
//	rcOneOf			ENUM		If Device has any "wide" addressing resources it must considered as "narrow" if any "narrow" resources also present. (I.e. if Device has Mmio64pf and Mmio32pf on the same bridge - consider Mmio64pf resources as	Mmio32pf. However if Device doesn't have any 32bit resources but only 64bit, 64bit resources for the bridge will be considered).
//	rcNarrow		ENUM		Device doesn't supports "wide" resources. So if Device has any Io32 or Mmio64, it must be addressed as Io16 and Mmio32 resources correspondently. 
//	rcBoth			ENUM		Device has facilities to support both type of resources "wide" and "narrow" at the same time (i.e. Io16 is supported as well as Io32).
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
typedef enum {
	rcNone=0,
	rcOneOf,
	rcNarrow,
	rcBoth
} RES_CONV_TYPE;

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:		PCI_CFG_ADDR
//
// Description:	UNION of UINT64 and a Structure used to access
// and store PCI Device	Address.
//
// Fields:		
//	Name			Type					Description
//   ------------------------------------------------------------------
//	ADDR			UINT64 			All Fields together as a single value
//	Addr 			EFI_PCI_CONFIGURATION_ADDRESS	PCI Device Address Structure
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
typedef union _PCI_CFG_ADDR {
	UINT64							ADDR;
	EFI_PCI_CONFIGURATION_ADDRESS	Addr;
} PCI_CFG_ADDR;

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:		MBRG_RES_DSC
//
// Description:	Structure used to access and store PCI Device Resource Requirements
// in a form of QWORD ACPI Resource Descriptor.
//
// Notes:	See ACPI Specification 3.0 for details on ACPI Resource Descriptors.
//			See definition of MRES_TYPE for definitions of rtMaxRes.
//
// Fields:		
//	Name			Type					Description
//   ------------------------------------------------------------------
//	Res				ASLR_QWORD_ASD	An "rtMaxRes" array of all possible Resources 
//	EndDsc			ASLR_EndTag		Array terminator
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
typedef struct _MBRG_RES_DSC { 
	ASLR_QWORD_ASD		Res[rtMaxRes];
	ASLR_EndTag 		EndDsc;
} MBRG_RES_DSC;


//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:		PCI_CMD_REG
//
// Description:	UNION of UINT16 and a Structure used to access and store PCI 
// COMMAND REGISTER values.
//
// Fields:		
//	Name			Type					Description
//   ------------------------------------------------------------------
//	CMD_REG		    UINT16 			Content of entire PCI COMMAND Register.
//  struct          UINT16          Bit field definition of COMMAND register bits.
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
typedef union _PCI_CMD_REG {
    UINT16          CMD_REG;
    struct {
        UINT16      IoSpace         :   1;  //bit 0
        UINT16      MemSpace        :   1;  //bit 1
        UINT16      BusMaster       :   1;  //bit 2
        UINT16      SpecialCycles   :   1;  //bit 3
        UINT16      MemWrAndInv     :   1;  //bit 4
        UINT16      VgaPaletteSnoop :   1;  //bit 5
        UINT16      ParityErrorResp :   1;  //bit 6
        UINT16      Resrved1        :   1;  //bit 7 
        UINT16      SerrEnable      :   1;  //bit 8
        UINT16      FastBack2Back   :   1;  //bit 9
        UINT16      IntDisable      :   1;  //bit 8
    };
} PCI_CMD_REG;

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:		PCI_BRG_CNT_REG
//
// Description:	UNION of UINT16 and a Structure used to access and store PCI 
// COMMAND REGISTER values.
//
// Fields:		
//	Name			Type					Description
//   ------------------------------------------------------------------
//	CMD_REG		    UINT16 			Content of entire PCI COMMAND Register.
//  struct          UINT16          Bit field definition of COMMAND register bits.
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
typedef union _PCI_BRG_CNT_REG {
    UINT16          BRG_CNT_REG;
    struct {
        UINT16      PerrEnable      :   1;  //bit 0
        UINT16      SerrEnable      :   1;  //bit 1
        UINT16      IsaEnable       :   1;  //bit 2
        UINT16      VgaEnable       :   1;  //bit 3
        UINT16      Vga16Enable     :   1;  //bit 4
        UINT16      MasterAbort     :   1;  //bit 5
        UINT16      SecBusReset     :   1;  //bit 6
        UINT16      SecFastBack2Back:   1;  //bit 7 
        UINT16      PriDiscardTmr   :   1;  //bit 8
        UINT16      SecDiscardTmr   :   1;  //bit 9
        UINT16      DiscardTmrSts   :   1;  //bit 10
        UINT16      DiscardTmrSerr  :   1;  //bit 11
//      UINT16      Reserved        :   4;  //bit 12...15 
    };
} PCI_BRG_CNT_REG;


//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:		PCI_STA_REG
//
// Description:	UNION of UINT16 and a Structure used to access and store PCI 
// COMMAND REGISTER values.
//
// Fields:		
//	Name			Type					Description
//   ------------------------------------------------------------------
//	STA_REG		    UINT16 			Content of entire PCI STATUS Register.
//  struct          UINT16          Bit field definition of STATUS register bits.
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
typedef union _PCI_STA_REG {
    UINT16          STA_REG;
    struct {
        UINT16      Resrved1        :   3;  //bit 0..2 
        UINT16      IntStatus       :   1;  //bit 3
        UINT16      CapList         :   1;  //bit 4
        UINT16      Cap66Mhz        :   1;  //bit 5
        UINT16      Resrved2        :   1;  //bit 6
        UINT16      FastBack2Back   :   1;  //bit 7
        UINT16      MasterDataPERR  :   1;  //bit 8
        UINT16      DevSellTiming   :   2;  //bit 9..10
        UINT16      TrgAbortSignaled:   1;  //bit 11
        UINT16      TrgAbortReceived:   1;  //bit 12
        UINT16      MstAbortReceived:   1;  //bit 13
        UINT16      SystErrSignaled :   1;  //bit 14
        UINT16      DetectedPERR    :   1;  //bit 15
    };
} PCI_STA_REG;



//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:		PCI_DEV_ID
//
// Description:	UNION of UINT32 and a Structure used to access and store PCI 
// Device VendorId and DeviceId values.
//
// Fields:		
//	Name			Type					Description
//   ------------------------------------------------------------------
//	DEV_VEN_ID		UINT32 			VendorId and DeviceId all together.
//	VenId			UINT16			VendorId value.
//	DevId			UINT16			DeviceId value.
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
typedef union _PCI_DEV_ID {
	UINT32	DEV_VEN_ID;
	struct {
		UINT16		VenId;
		UINT16		DevId;
	};
} PCI_DEV_ID;

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:		PCI_DEV_CLASS
//
// Description:	UNION of UINT32 and a Structure used to access and store PCI
// Device BaseClass, SubClass, ProgrammingInterface and RevisionId values.
//
// Fields:		
//	Name			Type					Description
//   ------------------------------------------------------------------
//	DEV_CLASS		UINT32 			BaseClass, SubClass, ProgrammingInterface and RevisionId all together
//	RevisionId		UINT8			RevisionId value
//	ProgInterface	UINT8			ProgInterface value
//	SubClassCode	UINT8			SubClassCode value
//	BaseCalssCode	UINT8			BaseCalssCode value
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
typedef  union _PCI_DEV_CLASS {
	UINT32		DEV_CLASS;
	struct {
		UINT8		RevisionId;
		UINT8		ProgInterface;
		UINT8		SubClassCode;
		UINT8		BaseClassCode;
	};
} PCI_DEV_CLASS;


//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:		PCI_DEVICE_TYPE
//
// Description:	This ENUM definition used to identify PCI Device different BAR types
//
// Notes:	Don't cange the order! Some PCI Bus internal routines rely on it!
//
// Fields:		
//	Name			Type					Description
//   ------------------------------------------------------------------
//	tPciUnknown		ENUM			PCI Bus Driver wasn't able to Identify the Device
//	tPciRootBrg		ENUM			Device is a PCI Root Bridge Device (A virtual device the root of PCI tree)
//	tPci2PciBrg		ENUM			Device is a PCI to PCI Bridge Device
//	tPci2CrdBrg		ENUM			Device is a PCI to CARD Bus Bridge Device
//	tPciHostDev		ENUM			Device is a PCI Host Bridge Device (North Bridge)
//	tUncompatibleDevice	ENUM		Device is an Uncompatible PCI Device
//	tPciMaxDevice	ENUM			Last valid value of this ENUM 
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
typedef enum {
	tPciUnknown=0,
	tPciRootBrg,    //1
	tPci2PciBrg,    //2
	tPci2CrdBrg,    //3
	tPciHostDev,    //4
	tPciDevice,     //5
	tUncompatibleDevice, //6
	tPciMaxDevice   //7
} PCI_DEVICE_TYPE;

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:		PCI_BAR_TYPE
//
// Description:	This ENUM value used to identify PCI Device different BAR types.
//
// Fields:		
//	Name			Type					Description
//   ------------------------------------------------------------------
//	tBarUnused		ENUM 	BAR is not used to Specify Device Resources(empty)
//	tBarBus			ENUM	Virtual BAR type to use the same mechanism to clame BUS resources for the device used in bridge specific resourse routines
//	tBarIo16		ENUM	BAR is used to Specify Device's I/O 16bit Resources
//	tBarIo32		ENUM	BAR is used to Specify Device's I/O 32bit Resources
//	tBarMmio32		ENUM	BAR is used to Specify Device's MMIO 32bit Resources
//	tBarMmio32pf	ENUM	BAR is used to Specify Device's Prefetchable MMIO 32bit 
//	tBarMmio64		ENUM	BAR is used to Specify Device's MMIO 64bit Resources
//	tBarMmio64pf	ENUM	BAR is used to Specify Device's Prefetchable MMIO 64bit
//	tBarIo			ENUM	A superset of PCI_BAR_TYPE tBarIo16 and tBarIo32
//	tBarMem			ENUM	A superset of PCI_BAR_TYPE tBarMmio32 and tBarMmio64
//	tBarMemPf		ENUM	A superset of PCI_BAR_TYPE tBarMmio32pf and tBarMmio64pf
//	tBarMaxType		ENUM	Last valid value of this ENUM 
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
typedef enum {
	tBarUnused=0,
	tBarBus,  		//1	
	tBarIo16,		//2
	tBarIo32,		//3
	tBarMmio32,		//4
	tBarMmio32pf,	//5
	tBarMmio64,		//6
	tBarMmio64pf,	//7
	tBarIo,			//8
	tBarMem,		//9
	tBarMemPf,		//a
	tBarMaxType		//b
} PCI_BAR_TYPE;

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:		PCI_BAD_BAR
//
// Description:	This structure used to identify Incapable PCI Devices which
// has some BAR irregularity.
//
// Fields:		
//	Name				Type					Description
//   ------------------------------------------------------------------
//	IncompType		PCI_INCOMPATIBILITY_TYPE Type of PCI Device Incompatibility
//	VendorId		UINT16			Vedor ID of the PCI Device (PCI CFG OFFSET 0x00)
//	DeviceId		UINT16			Device ID of the PCI Device (PCI CFG OFFSET 0x02)
//	DeviceIdMask	UINT16			AND MASK to apply to Device ID value to include wider variety of the devices from the same VENDOR
//	Reserved		UINT16			Must be ZERO
//	BarType			PCI_BAR_TYPE	PCI Device Bar Type which is Incompatible to include all device BARs of the same type Only tBarIo, tBarMem and tBarMaxType allowed.
//	BarOffset		UINTN			If BarType==tBarMaxType this field specifies BAR offset. Ignored if BarType!=tBarMaxType.
//	BarBase 		UINT64			this field will be ignored at all times Fixed Base feature not implemented yet
//	BarLength		UINT64			If IncompType==icBarFixedSize this field will indicate actual resource length for the BAR. Ignored if IncompType!=icBarFixedSize.
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
typedef struct _PCI_BAD_BAR {
	PCI_INCOMPATIBILITY_TYPE	IncompType;
	UINT16						VendorId;
	UINT16						DeviceId;
	UINT16						DevIdMask; 	//used to AND with DevID value
	UINT16						Reserved;
	PCI_BAR_TYPE				BarType; 	//if this field=tBarMaxType then BarOffset must be used
											//tBarMaxType, tBarIo and tBarMem only allowed
	UINTN						BarOffset;
	UINT64						BarBase;
	UINTN						BarLength;

}PCI_BAD_BAR;


//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:		PCI_BAR
//
// Description:	This Structure used to store information about PCI Device 
//	Base Address Register (BAR)
//
// Fields:		
//	Name			Type					Description
//   ------------------------------------------------------------------
//	Type			PCI_BAR_TYPE		Type of PCI Device BAR may be converted
//  DiscoveredType  PCI_BAR_TYPE		Actual Type of PCI Device BAR 
//	Base			UINT64				Base Address of the Resource assigned to this BAR
//	Length			UINT64				Length of the Resource assigned to this BAR in bytes
//	Gran			UINT64				Grenularity of the Resource assigned to this BAR - a value that was read back after all ONEs was applied to the BAR.
//	Offset			UINT8				Offset of the PCI Config Space where this bar Located 
//	Reserved		UINT8				7 Reserved Byte Fields to make structure 4 byte aligned 
//	BarAttr			UINT64				PCI BAR Attributes see EFI 1.1 spec for details 
//	*Owner			PCI_DEV_INFO		Pointer to Device Private data Structure of the device who owns this structure.
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
typedef struct _PCI_BAR {
	PCI_BAR_TYPE	Type;
	PCI_BAR_TYPE	DiscoveredType;
	UINT64			Base;
	UINT64			Length;
	UINT64			Gran;
	UINT8			Offset; //offset of this bar register in PCI_CFG space 
	UINT8			Reserved[7];
	UINT64			BarAttr;
    UINT16          ExtOffset;
	struct _PCI_DEV_INFO *Owner;
} PCI_BAR;

typedef struct _BRG_RES_ORDER {
	//To make it look Like _T_ITEM_LST
	UINTN 		InitCount;
	UINTN 		BarCount;
	PCI_BAR		**BarList;	//this is array of Pointers 
}BRG_RES_ORDER;

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:		BRG_ALIGN_INFO
//
// Description:	This Structure used to store information about PCI Bridge
//	alignment requirements since behind the bridge could be more than one
//  device. 
//
// Fields:		
//	Name			Type					Description
//   ------------------------------------------------------------------
//	MaxGran			UINT64				Maximum Granularity of the Resources Behind the Bridge
//	ResGran			UINT64				Granularity that will apply after Bridge Resources would be assigned
//	MinGran			UINT64				Minimum Granularity supported by the Bridge
//	PCI_BAR			ExtraRes			Resource window Padded in order to support Granularity of the next allocation
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
typedef struct _BRG_ALIGN_INFO {
	UINT64			MaxGran;
	UINT64			ResGran;
	UINT64			MinGran;
	PCI_BAR			ExtraRes;
} BRG_ALIGN_INFO;



//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:		PCI_BUS_OVERRIDE_DATA
//
// Description:	This Structure used to store information about PCI Device's
// EFI_BUS_SPECIFIC_DRIVER_OVERRIDE_PROTOCOL Instance, if any.
//
// Fields:		
//	Name			Type					Description
//   ------------------------------------------------------------------
//	BusOverride		EFI_BUS_SPECIFIC_DRIVER_OVERRIDE_PROTOCOL	EFI_BUS_SPECIFIC_DRIVER_OVERRIDE_PROTOCOL instance. 
//	*OverrideHandles EFI_HANDLE			Pointer	to the EFI_HANDLEs Buffer gets overriden by the	inctance of EFI_BUS_SPECIFIC_DRIVER_OVERRIDE_PROTOCOL above.
//	OhCount			UINTN				Number of EFI_HANDLEs in "OverrideHandles" buffer
//	*Owner			PCI_DEV_INFO		Pointer to Device Private data Structure of the device who owns this structure.
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
typedef struct _PCI_BUS_OVERRIDE_DATA {
	EFI_BUS_SPECIFIC_DRIVER_OVERRIDE_PROTOCOL	BusOverride;
	struct _PCI_DEV_INFO						*Owner;
}PCI_BUS_OVERRIDE_DATA;


#if ((defined EFI_SPECIFICATION_VERSION) && (EFI_SPECIFICATION_VERSION >= 0x2001F))
typedef struct _PCI_LOAD_FILE_DATA {
    EFI_LOAD_FILE2_PROTOCOL                     LoadFile2;
	struct _PCI_DEV_INFO						*Owner;
}PCI_LOAD_FILE_DATA;
#endif

typedef struct _PCI_ROM_IMAGE_DATA {
	EFI_HANDLE									RomImgHandle;
    MEDIA_RELATIVE_OFFSET_RANGE_DEVICE_PATH     RomImageDP;
    PCI_EFI_OPT_ROM_HEADER                      *RomHeader;
    UINTN                                       ActualSize;
} PCI_ROM_IMAGE_DATA;


//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:		PCIE_EXT_DATA_HDR
//
// Description:	This Structure used to store PCI Express Device's Extended
// Data Structure Header. It is the same for all data types.
//
// Notes:	See PCIE.h for details on PCIE_VC_RESCAP_REG.
//
// Fields:		
//	Name			Type					Description
//   ------------------------------------------------------------------
//	VcResOffset		UINT16		Offset in PCI Express Extanded Configuration Space of the Virtual Channel Resources header.
//	Reserved		UINT8		2 Reserved bytes to make structure 4 byte aligned.
//	VcResCap		PCIE_VC_RESCAP_REG	Contents of Virtual Channel Capability Register.
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
typedef struct _PCIE_EXT_DATA_HDR {
	UINT16				CapHdrOffset; 
    UINT32              CapReg;
}PCIE_EXT_DATA_HDR;


//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:		VC_RES_DATA
//
// Description:	This Structure used to store PCI Express Device's Virtual
// Channel Resource Data.
//
// Notes:	See PCIE.h for details on PCIE_VC_RESCAP_REG.
//
// Fields:		
//	Name			Type					Description
//   ------------------------------------------------------------------
//	VcResOffset		UINT16		Offset in PCI Express Extanded Configuration Space of the Virtual Channel Resources header.
//	Reserved		UINT8		2 Reserved bytes to make structure 4 byte aligned.
//	VcResCap		PCIE_VC_RESCAP_REG	Contents of Virtual Channel Capability Register.
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
typedef struct _VC_RES_DATA {
	UINT16				VcResOffset; 
	PCIE_VC_RESCAP_REG	VcResCap;
	UINT8				Reserved[2];
}VC_RES_DATA;




//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:		VC_DATA
//
// Description:	This Structure used to store PCI Express Device's Virtual Channel Data.
//
// Notes:	See PCIE.h for details on PCIE_PORTVC_CAP_REG1, PCIE_PORTVC_CAP_REG2. 
//			See AmiDxeLib.h for details on T_ITEM_LIST;
//
// Fields:		
//	Name			Type					Description
//   ------------------------------------------------------------------
//	VcResOffset		UINT16			Offset in extanded PCI Express Extanded Configuration Space of the Virtual Channel Capability header
//	Reserved		UINT8			2 Reserved bytes to make structure 4 byte aligned
//	VcCap1	PCIE_PORTVC_CAP_REG1	Contents of Virtual Channel Port Capability Register 1
//	VcCap2	PCIE_PORTVC_CAP_REG2	Contents of Virtual Channel Port Capability Register 2
//	InitCnt			UINTN			to make this and 2 following fields look like T_ITEM_LIST
//	VcCount			UINTN			Number of VC resource Headers found in this Device
//	**VcResData		VC_RES_DATA		Pointer on Array of "VcCount" pointers on the Devices VC_RES_DATA structure.
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
typedef struct _VC_DATA {
	UINT16					VcOffset; //Offset of Extd VC Cap Header
	PCIE_PORTVC_CAP_REG1	VcCap1;
	PCIE_PORTVC_CAP_REG2	VcCap2;
	UINT8					Reserved[2];
//to make it look like T_ITEM_LIST		
	UINTN					InitCnt;	
	UINTN					VcCount;
	VC_RES_DATA				**VcResData;
}VC_DATA;


typedef struct _PCIE_SRIOV_DATA{
    UINT16              SriovCapHdrOffs;
    PCIE_ARI_CAP_REG    AriCaps;    //16 bit reg
    UINT8               Reserved[2];            
    PCI_BAR Bar[PCI_MAX_BAR_NO]; //VF BARs
}PCIE_SRIOV_DATA;


//Alternative routing ID
typedef struct _PCIE2_ARI_DATA {
    UINT16              AriCapHdrOffs;
    PCIE_ARI_CAP_REG    AriCaps;    //16 bit reg
    UINT8               Reserved[4];
}PCIE2_ARI_DATA;

//Access Control
typedef struct _PCIE2_ACS_DATA {
    UINT16              AcsCapHdrOffs;
    PCIE_ACS_CAP_REG    AcsCaps;    //16 bit reg
    UINT8               Reserved[4];
}PCIE2_ACS_DATA;

//Address Translation
typedef struct _PCIE2_ATS_DATA {
    UINT16              AtsCapHdrOffs;
    PCIE_ATS_CAP_REG    AtsCaps;    //16 bit reg
    UINT8               Reserved[4];
}PCIE2_ATS_DATA;

//Internal RC Link
typedef struct _PCIE_RCLNK_DATA {
    UINT16              RcLnkCapHdrOffs;
    PCIE_RC_LNK_CAP_REG PcLncCap;   //32 bit reg
    UINT8               Reserved[2];
}PCIE_RCLNK_DATA;

//Secondary PCIe Ext Capability 
typedef struct _PCIE3_DATA {
    UINT16              SecPcieCapOffs;
    UINT32              LaneErrSts; //32 bit reg
    UINT8               MaxLanesCount;    
} PCIE3_DATA;

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:		PCIE2_DATA
//
// Description:	This Structure used to store Device's PCI Express Gen2 Specific Data.
//
// Notes:	See PCIE.h for details on PCIE_PCIE_CAP_REG, PCIE_DEV_CAP_REG, 
//			PCIE_LNK_CAP_REG, PCIE_SLT_CAP_REG;
//			See AmiDxeLib.h for details on T_ITEM_LIST;
//
// Fields:		
//	Name			Type					Description
//   ------------------------------------------------------------------
//	PcieOffs		UINT16			Offset in Standard PCI Configuration Space of the PCI Express Capability header
//	DeviceCap	PCIE_DEV_CAP2_REG	Contents of PCI Express Device Capability 2 Register
//	LinkCap		PCIE_LNK_CAP2_REG	Contents of PCI Express Link Capability 2 Register
//	SlotCap		PCIE_SLT_CAP2_REG	Contents of PCI Express Slot Capability 2 Register
//	*Owner			PCI_DEV_INFO	Pointer to Device Private data Structure of the Device who owns this structure.
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
typedef struct _PCIE2_DATA {
    PCIE_DEV_CAP2_REG	DeviceCap2;
	PCIE_LNK_CAP2_REG   LinkCap2;   //in spec v2.1 this reg is a place holder reserved for future use
                                    //in spec v3.0 this register was defined and holds LNK Supported Speed 
	PCIE_SLT_CAP2_REG	SlotCap2;   //in spec v2.1 this reg is a place holder reserved for future use
                                    //in spec v3.0 this reg a place holder as well
    BOOLEAN             AriEnabled; //to indicate for Dowm Stream Port has ARI forwarding ON
    UINT8               LnkSpeed;
    UINT8               Reserved[2];
    PCI_DEV_INFO        *Owner;
} PCIE2_DATA;



//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:		PCIE_DATA
//
// Description:	This Structure used to store Device's PCI Express Specific Data.
//
// Notes:	See PCIE.h for details on PCIE_PCIE_CAP_REG, PCIE_DEV_CAP_REG, 
//			PCIE_LNK_CAP_REG, PCIE_SLT_CAP_REG;
//			See AmiDxeLib.h for details on T_ITEM_LIST;
//
// Fields:		
//	Name			Type					Description
//   ------------------------------------------------------------------
//	PcieOffs		UINT16			Offset in Standard PCI Configuration Space of the PCI Express Capability header
//	PcieCap		PCIE_PCIE_CAP_REG	Contents of PCI Express Capability Register
//	DeviceCap	PCIE_DEV_CAP_REG	Contents of PCI Express Device Capability Register
//	LinkCap		PCIE_LNK_CAP_REG	Contents of PCI Express Link Capability Register
//	SlotCap		PCIE_SLT_CAP_REG	Contents of PCI Express Slot Capability Register
//	CommonClk		BOOLEAN			Flag to record Device's Link Clock Configuration
//	ClockSet		BOOLEAN			Flag to mark PCI Express Initialization Process steps
//	PayloadSet		BOOLEAN			Flag to mark PCI Express Initialization Process steps
//	AspmSet			BOOLEAN			Flag to mark PCI Express Initialization Process steps
//	*VcData			VC_DATA			Pointer to Device's Virtual Channel Data Structure
//	*Owner			PCI_DEV_INFO	Pointer to Device Private data Structure of the Device who owns this structure.
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
typedef struct _PCIE_DATA {
	UINT16				PcieOffs; 	//in order not to calculate Offset every time we need to access it
	PCIE_PCIE_CAP_REG	PcieCap; 
	PCIE_DEV_CAP_REG	DeviceCap;
	PCIE_LNK_CAP_REG	LinkCap;
	PCIE_SLT_CAP_REG	SlotCap;
    PCIE_ROOT_CAP_REG   RootCap;
	BOOLEAN				LinkSet;   //to indicate - Link Cnt Reg was programmed  
	BOOLEAN				DevSet;    //to indicate - Device Cnt Reg was programmed 
    BOOLEAN             SlotSet;   //to indicate - Slot Cnt Reg was programmed 
    UINT8               Reserved;
    UINT16              MaxPayload;//Calculated and stored on both sides of the stored in 
    UINT16              MaxL0Lat; //Calculated Max latency on the link from top down 
    UINT16              MaxL1Lat;  //(not included internal latency of Switch or Root Complex)
                        //in 2 fields abowe 
                        //value of 0xFFFF indicates corresponded Lx state is not supported)
                        //values form 0...7 corresponds to Maximum latency for the link to which device is connected.
                        //All other values 8..0xFFFE are illegal and reserved.
    UINT8               CurrLnkSpeed;   // encoding changed from previous versiom 8GT/s speed added so name as well  
    UINT8               CurrLnkWidth;
    PCIE2_DATA          *Pcie2; 
    PCIE3_DATA          *Pcie3;
    //Ext Capabilities collected information
	VC_DATA				*VcData;
    PCIE_SRIOV_DATA     *SriovData;
    PCIE2_ARI_DATA      *AriData;
    PCIE2_ACS_DATA      *AcsData;
    PCIE2_ATS_DATA      *AtsData;
    PCIE_RCLNK_DATA     *RcLnkData;
    //Back reference information
	PCI_DEV_INFO		*Owner;
} PCIE_DATA;


//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:		PCIX_DATA
//
// Description:	This Structure used to store Device's PCI-X Specific Data.
//
// Notes:	See PCIX.h for details on PCIX_DEV_STA_REG, PCIX_SEC_STA_REG;
//
// Fields:		
//	Name			Type					Description
//   ------------------------------------------------------------------
//	PcixOffs		UINT16			Offset in Standard PCI Configuration Space of the PCI-X Capability header
//	PcixDevStatus PCIX_DEV_STA_REG	Contents of PCI-X Device Status Register
//	PcixSecStatus PCIX_SEC_STA_REG	Contents of PCI-X Device Secondary Status Register
//	*Owner			PCI_DEV_INFO	Pointer to Device Private data Structure of the Device who owns this structure.
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
typedef struct _PCIX_DATA {
	UINT16				PcixOffs;
	PCIX_DEV_STA_REG	PcixDevStatus;
	PCIX_SEC_STA_REG	PcixSecStatus;
	PCI_DEV_INFO		*Owner;
} PCIX_DATA;


//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:		PCIX_DATA
//
// Description:	This Structure used to store Device's Hot Plug Controller (HPC) Specific Data.
//
// Notes:	See "PciHotPlugInit.h" for details on HPC and RHPC;
//
// Fields:		
//	Name			Type					Description
//   ------------------------------------------------------------------
//	HpcOffs			UINT16			Offset in Standard PCI Configuration Space of the PCI Hotplug Capability header.
//	Root 			BOOLEAN			Flag to indicate Root Hot Plug Controller (RHPC).
//	Reserved 		UINT8			3 Reserved bytes to make structure 4 byte aligned.
//	*HpcLocation	EFI_HPC_LOCATION Location of the RHPC delivered from EFI_PCI_HOT_PLUG_INIT_PROTOCOL.
//	*HpbBridge		PCI_DEV_INFO	The P2P Bridge which creates the bus controlled by this HPC.
//	HpcPciAddr		PCI_CFG_ADDR	Address on the PCI Bus of this HPC.
//	BusFound		BOOLEAN			Flag to indicate that bus controlled by this HPC was alresdy found.
//	Initialized		BOOLEAN			Flag to indicate that HPC Initialization Routine was called.
//	HpcState		EFI_HPC_STATE	Current state of the HPC
//	*Owner			PCI_DEV_INFO	Pointer to Device Private data Structure of the Device who owns this structure.
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
typedef struct _PCI_HPC_INFO {
	UINT16				HpcOffs;
	BOOLEAN				Root;
	UINT8				Reserved[3];
	EFI_HPC_LOCATION	*HpcLocation;
	PCI_DEV_INFO		*HpbBridge;
	PCI_CFG_ADDR		HpcPciAddr;
	BOOLEAN				BusFound;
	BOOLEAN 			Initialized;
	EFI_HPC_STATE		HpcState; //UINT16
	PCI_DEV_INFO		*Owner;
}PCI_HPC_INFO;



//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:		PCI_DEV_INFO
//
// Description:	This Structure is the main data structure associated with the PCI Device.
// It holds all device specific data and references all other data srtuctures defined in "PciBus.h".
//
// Notes:	See "PCI.h" for details;
//
// Fields:		
//	Name			Type						Description
//   ------------------------------------------------------------------
//	PciIo		EFI_PCI_IO_PROTOCOL				An instance of the EFI_PCI_IO_PROTOCOL for This Device.
//	BusOvrData	PCI_BUS_OVERRIDE_DATA 			An instance of PCI_BUS_OVERRIDE_DATA structure for This Device.
//	*DevicePath	EFI_DEVICE_PATH_PROTOCOL 		A pointer to an instance of EFI_DEVICE_PATH_PROTOCOL for This Device.
//	*RbIo		EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL	A pointer to an instance of EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL of This Device's Root Bridge.
//	*ParentBrg	PCI_DEV_INFO					Pointer to a private datastructure of This Device's "Parent" Bridge.
//	*HostData	PCI_HOST_INFO					Pointer to This Device's Host Bridge private data.
//	Type		PCI_DEVICE_TYPE					Type of This Device. See PCI_DEVICE_TYPE for details.
//	Started 	BOOLEAN							Flag to indicate that device has been Registred with HandleDatabase and has its EFI_PCI_IO_PROTOCOL installed. Device is READY TO USE
//	Assigned 	BOOLEAN							Flag to indicate that resources requested by this Device was assigned to it and corresponded BARs were programmed.
//	Discovered 	BOOLEAN							Flag to indicate that resource requested information of This Device has been gethered and recorded.
//	Discovered 	BOOLEAN							Flag to indicate that that This Device was enumerated and it's Address; ClassCode; Type and DevID/VendId data recorded.
//	Address		PCI_CFG_ADDR					Address on the PCI Bus of This Device.
//	Handle		EFI_HANDLE						This Device Handle.
//	DevVenId	PCI_DEV_ID						This Device Identification - Contents of DevID and VendorID Registers
//	Class		PCI_DEV_CLASS					This Device RevisionId Cllas, Sub Class and ProgrInterface Code. 
//	Bar			PCI_BAR							PCI_MAX_BAR_NO+1 Bar Registers if Device has implemented Option ROM BAR it is also covered.
//	Capab		UINT64							This Device Capabilities.				
//	Attrib		UINT64							This Device Attributes.
//	PmiCapOffs	UINTN							This Device Power Management Capabilities Header Offset in PCI Config Space.
//	*PciExpress	PCIE_DATA						If This Device has PCI Express features this field will have pointer to the PCI Express Data Structure.
//	*PciX		PCIX_DATA						If This Device has PCI-X or PCI-X2  features this field will have pointer to the PCI X Data Structure.
//	*HotPlug	PCI_HPC_INFO					If This Device is a Hot Plug Controller or the bridge behind which Hot Plug Slots located this field will have a Pointer to a member of PCI_HOST_INFO.HpcList[?].
//	Incompatible BOOLEAN						Flag to indicaste that This Device's VendorID DeviceID was found in Bad Pci Device Table.
//	RbError		BOOLEAN							Flag to indicaste that Root Bridge Access failed during initialization.
//	RomBarError	BOOLEAN							Flag to indicaste that Option ROM BAR implemented but Invalid.
//	DebugPort	BOOLEAN							Flag to indicaste that This Device is reserved as a Debug Port.
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
typedef struct _PCI_DEV_INFO {
    EFI_PCI_IO_PROTOCOL		PciIo;		//PCI IO Protocol Instance
	PCI_BUS_OVERRIDE_DATA	BusOvrData;	//PCI Specific 
	EFI_DEVICE_PATH_PROTOCOL			*DevicePath;
//-- Device Parent Info 
	EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL	*RbIo;//Root Bridge PCI IO protocol Instance	
	struct _PCI_DEV_INFO	*ParentBrg; //to help iterate backwards
	PCI_HOST_INFO			*HostData;	//will have pointers 
//-- Device Specific Info
	PCI_DEVICE_TYPE			Type;		//Identifies the device
	BOOLEAN					Started;	//Indicate that device has been Registred with HandleDatabase 
										//and ready to use by others - Device is READY TO USE 
	BOOLEAN					Assigned;   //Indicates that resources requested by this device 
										//was assigned to it and corresponded BARs were programmed
	BOOLEAN					Discovered; //Indicates that resources information requested by this device 
										//has been gethered and recorded
 	BOOLEAN                 Enumerated;	//Indicates that Device was enumerated 
										//and it's Addrss; ClassCode; Type and DevID/VendId data recorded 
	PCI_CFG_ADDR			Address;	//Device Location On The Pci Bus
	EFI_HANDLE				Handle;		//this Device  Handle 
	PCI_DEV_ID				DevVenId;	//Device Identification - Contents of DevID and VendorID Registers
	PCI_DEV_CLASS			Class;	    //Device Cllas, Sub Class and Progr Interface Code 
	PCI_BAR					Bar[PCI_MAX_BAR_NO+1];//Bar Registers if Device has an Option ROM it is also covered by this bar
	UINT64					Capab;
	UINT64                  Attrib;
	UINTN					PmiCapOffs;
//-- Device Features Info
	PCIE_DATA				*PciExpress;
	PCIX_DATA				*PciX;
	PCI_HPC_INFO			*HotPlug;
//This fields will indicate problems the device might have during initialization.
	BOOLEAN					Incompatible;
	BOOLEAN 				RbError;
	BOOLEAN					RomBarError;
	BOOLEAN 				DebugPort;
//-------------------------------------------------------------------
//Additional stuff used in CORE Version 4.6.3.2 and up
	UINT64					Signature;
	UINT8					MajorVersion;
	UINT8					MinorVersion;
    UINT8                   Revision;
    BOOLEAN                 SkipDevice;
    BOOLEAN                 OutOfResRemove;
	UINT8					Reserved0[3];				
    PCI_IRQ_PIC_ROUTE       *PicIrqEntry;
    PCI_IRQ_APIC_ROUTE      *ApicIrqEntry;
//This field added to meet compatibility with UEFI 2.1
	PCI_CMD_REG				CmdReg;
    PCI_STA_REG             StaReg;
//Additional stuff used in PCI Bus Version 2.3.1 and up
//if device a Multi Finctional 
//T_ITEM_LIST to store all available functions of this device
//and signify Function 0 since with PCIe some programinig applicable for F0 only.
    PCI_DEV_INFO            *Func0; //Signifies if Device Is Multy Function ==NULL single
    // following fieds holds all other functions of the device.
    UINTN                   FuncInitCnt;
    //If (Func0==NULL && FuncCount==0) function is a single function device, following fields are not used and reserved;
    //If (Func0!=NULL && FuncCount==0) function is one of the Func1..Func7 of multyfunc device Func0 points on DevFunc0;
    //If (Func0!=NULL && (FuncCount!=0 || FuncInitCnt!=0)) function is Func0 of multyfunc device DevFunc holds pointers at all other Func1..7 found
    //If (Func0==NULL && FuncCount!=0) Illehgal combination - reserved!
    UINTN                   FuncCount;
    PCI_DEV_INFO            **DevFunc;
//Collection of EFI Compatible Option ROMs    
    UINTN                   RomInitCnt;
    UINTN                   EfiRomCount;
    PCI_ROM_IMAGE_DATA      **EfiRomImages;
#if ((defined EFI_SPECIFICATION_VERSION) && (EFI_SPECIFICATION_VERSION >= 0x2001F))
    PCI_LOAD_FILE_DATA      LoadFileData;
#endif
}PCI_DEV_INFO;


//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:		PCI_BRG_EXT
//
// Description:	PCI Bridge Extended Data Structure. This Structure used to store
// Hosts and PCI to PCI Bridges additional data. It must follow exactly after the
// PCI_DEV_INFO data structure of the device identified as a Bridge.
//
// Notes:	See PCI.h for details;
//
// Fields:		
//	Name			Type					Description
//   ------------------------------------------------------------------
//	Res			PCI_BAR				An Array of "rtMaxRes" PCI_BAR structures to hold resource requirements of bridge secondary interface
//	Pad			PCI_BAR				An Array of "rtMaxRes" PCI_BAR structures to hold resource Padding requirements of bridge secondary interface
//  Align       BRG_ALIGN_INFO      An Array of "rtMaxRes" BRG_ALIGN_INFO structures to hold Resource Alignment requirements of bridge secondary interface
//  BarOrder    BRG_RES_ORDER		An Array of "rtMaxRes" BRG_RES_ORDER structures to hold BAR Order of bridge secondary interface
//	PaddAttr	EFI_HPC_PADDING_ATTRIBUTES		Resource Padding Attributes.
//	AllocAttr	UINT64				Resource Allocation Attributes.
//	InitialCount UINTN				To make this and 2 following fields look like T_ITEM_LIST.
//	ChildCount	UINTN				Number of PCI Devices descovered on Bridge's secondary interface.
//	**ChildList	PCI_DEV_INFO		Pointer to the array of pointers on Child Devices Private Data.
//  Padded      BOOLEAN             Indicaes that resources Vas Padded for that Bridge.
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
typedef struct _PCI_BRG_EXT {
	PCI_BAR					Res[rtMaxRes]; 	//it will include Bus properties 
											//SecBus= Bar.Base SubBus=Len   
	PCI_BAR					Pad[rtMaxRes];	//Same as above but for Padding
	BRG_ALIGN_INFO			Align[rtMaxRes];
	BRG_RES_ORDER			BarOrder[rtMaxRes];
	EFI_HPC_PADDING_ATTRIBUTES	PaddAttr;	//Attributes For Resource Padding
	UINT64					AllocAttr;
//to make it look like as T_ITEM_LIST structure 
	UINTN					InitialCount;
	UINTN					ChildCount;
    PCI_DEV_INFO			**ChildList;
	BOOLEAN					Padded;
	BOOLEAN					Reserved;
    UINT8                   ItemNumber;       //Item Number in sorted gPciBusDb array 
    UINT8                   ChainNumber;
    PCI_BUS_XLAT_HDR        *XlatTblEntry;
    PCI_BRG_CNT_REG         BrgCmdReg;
} PCI_BRG_EXT;


//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:		PCI_BRG_INFO
//
// Description:	PCI Bridge Private Data Structure. 
//
// Fields:		
//	Name			Type					Description
//   ------------------------------------------------------------------
//	Common			PCI_DEV_INFO	Data Structure which common for all Objects. See PCI_DEV_INFO.
//	Bridge			PCI_BRG_EXT		PCI Bridge additional information. See PCI_BRG_EXT.
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
typedef struct _PCI_BRG_INFO {
	PCI_DEV_INFO			Common;
    PCI_BRG_EXT				Bridge;
}PCI_BRG_INFO;


//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:		PCI_HOST_INFO
//
// Description:	Root Srtucture of the PCI Subsystem. 
//
// Fields:		
//	Name			Type					Description
//   ------------------------------------------------------------------
//	*VgaDev			PCI_DEV_INFO	Pointer on curently selected Legacy VGA device.
//	*PriIde			PCI_DEV_INFO	Pointer on curently selected Legacy Primary IDE device.
//	*SecIde			PCI_DEV_INFO	Pointer on curently selected Legacy Secondary IDE device.
//	RbInitCount 	UINTN			To make this and 2 following fields look like T_ITEM_LIST.
//	RbCount 		UINTN			Number of Root Bridges in the System.
//	**RootBridges	PCI_DEV_INFO	Pointer to the array of pointers on PCI Root Bridge PCI Devices Private Data.
//	HostHandle		EFI_HANDLE		Handle of the PCI Host Bridge Associated with this Root Bridge
//	*ResAllocProt	EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL	Pointer to the EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL Instance.
//	*PlatformProt	EFI_PCI_PLATFORM_PROTOCOL	Pointer to the EFI_PCI_PLATFORM_PROTOCOL Instance.
//	*IncompDevProt	EFI_INCOMPATIBLE_PCI_DEVICE_SUPPORT_PROTOCOL	Pointer to the EFI_INCOMPATIBLE_PCI_DEVICE_SUPPORT_PROTOCOL Instance.
//	*HpInitProt		EFI_PCI_HOT_PLUG_INIT_PROTOCOL	Pointer to the EFI_PCI_HOT_PLUG_INIT_PROTOCOL Instance.
//	RhpcInitCnt 	UINTN			To make this and 2 following fields look like T_ITEM_LIST.
//	RhpcCount 		UINTN			Number of Root Hot plug Controllers in the System.
//	**RhpcList		PCI_HPC_INFO	Pointer to the array of pointers on PCI Root Hot Plug Controller Private Data. See PCI_HPC_INFO.
//	InitRhpcCount	UINTN			Number of Initialized PCI Root Hot Plug Controllers
//	Updated			BOOLEAN			Flag to indicate that Host information has been collected.
//	Enumerated		BOOLEAN			Flag to indicate that This Host infrastructure has been enumerated.
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
typedef struct _PCI_HOST_INFO {
	PCI_DEV_INFO										*VgaDev;
	PCI_DEV_INFO										*PriIde;
	PCI_DEV_INFO										*SecIde;
//T_ITEM_LST object with pointer on type
	UINTN												RbInitCnt;
	UINTN												RbCount; 
	PCI_DEV_INFO										**RootBridges;
//Protocols Associated with PCI Host Infrastructure and Pci Enumeration
	EFI_HANDLE											HostHandle;
	EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL	*ResAllocProt;
	EFI_PCI_PLATFORM_PROTOCOL							*PlatformProt;
	EFI_INCOMPATIBLE_PCI_DEVICE_SUPPORT_PROTOCOL		*IncompDevProt;
	EFI_PCI_HOT_PLUG_INIT_PROTOCOL						*HpInitProt;
//T_ITEM_LST object with pointer on type
	UINTN												RhpcInitCnt;
	UINTN												RhpcCount;
	PCI_HPC_INFO										**RhpcList;
	UINTN												InitRhpcCount; //to save some time InitializedRhpcCount
//------------------------------------------------------------------------
	BOOLEAN												Updated; 	//this will indicate that Host information has been collected
	BOOLEAN												Enumerated; //this host infrastructure has been enumerated
} PCI_HOST_INFO;


#pragma pack(pop)

//Export some routines to be used in PciHostBridge.c
EFI_STATUS  AddBusDbEntry(PCI_BUS_XLAT_HDR *BusHdr, T_ITEM_LIST *BusDb);


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
