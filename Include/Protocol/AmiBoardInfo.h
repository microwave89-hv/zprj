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
// $Header: /Alaska/BIN/Core/Modules/BoardInfo/Protocol/AmiBoardInfo.h 3     9/30/11 5:43p Yakovlevs $
//
// $Revision: 3 $
//
// $Date: 9/30/11 5:43p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Modules/BoardInfo/Protocol/AmiBoardInfo.h $
// 
// 3     9/30/11 5:43p Yakovlevs
// [TAG]  		EIP66222
// [Category]  	New Feature
// [Description]  	Modify PCI bus driver to get board info from separate
// FFS section
// [Files]  		AmiBoaardInfo.mak; 
// AmiBoaardInfo.sdl;
// PciBoard.c
// AmiBoaardInfo.h
// 
// 2     3/01/10 5:06p Yakovlevs
// New separate Label with generic Multi-Root support.
// Uses new AMI SDL "C" sytle output for the former "ASM" style.
// 
// 1     5/18/09 2:49p Yakovlevs
// 
// 1     4/28/09 1:26p Yakovlevs
// 
// 5     1/30/09 12:53p Yakovlevs
// Added Porting Function declaration EIP 8874
// 
// 4     11/14/08 1:37p Yakovlevs
// Declared NEW AMI Board Info Protocol
// 
// 3     10/01/08 7:10p Yakovlevs
// Updated AMI FUNC HEADER information.
// 
// 2     10/01/08 12:46p Yakovlevs
// Added missing constants associated with PCI BUS TOKENS
// 
// 1     9/25/08 11:29a Yakovlevs


#ifndef AMI_BOARD_INFO_H_
#define AMI_BOARD_INFO_H_

#ifdef __cplusplus
extern "C" {
#endif


#include <Efi.h>
#include <Token.h>

//Define AmiBoardInfo Protocol Intreface GUID
#define AMI_BOARD_INFO_PROTOCOL_GUID \
{ 0x0273146c, 0x96c4, 0x45a1, 0xa7, 0xaf, 0x78, 0xe0, 0x52, 0x4a, 0x0a, 0xe2 }

#define AMI_BOARD_INFO_SECTION_GUID \
{ 0xE6F4F8F7, 0x4992, 0x47b2, 0x83, 0x02, 0x85, 0x08, 0x74, 0x5E, 0x4A, 0x23 }

GUID_VARIABLE_DECLARATION(gAmiBoardInfoProtocolGuid,AMI_BOARD_INFO_PROTOCOL_GUID);

GUID_VARIABLE_DECLARATION(gAmiBoardInfoSectionGuid, AMI_BOARD_INFO_SECTION_GUID);

#ifndef GUID_VARIABLE_DEFINITION

//-------------------------------------------------
//Forward Declarations
//-------------------------------------------------
typedef struct _AMI_BOARD_INFO_PROTOCOL AMI_BOARD_INFO_PROTOCOL;


//SDL Binary Signature Defifnition
#define AMI_PIR_SIGNATURE   0x52495024 //"$PIR" Legacy PCI IRQ Routing 
#define AMI_AIR_SIGNATURE   0x52494124 //"$AIR" IO APIC IRQ Routing
#define AMI_APD_SIGNATURE   0x44504124 //"$APD" APIC Data Structure
#define AMI_XLT_SIGNATURE   0x544C5824 //"$XLT" APIC Data Structure

/////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------
//Define Internal VeB Structures
//Use BYTE alignment since tis stuff comes from ASM file. 
//---------------------------------------------------------------------------
#pragma pack(push, 1)

typedef struct _AMI_SDL_IRQR_HDR {
    UINT32  Sugnature;       //"$PIR" or "$AIR"
	UINT16  Version;         //Version 0x100
	UINT16  Size;            //Size 0x142 data + header
	UINT8   RouterBus;       //bRouterBus 0	
	UINT8   RouterDevFunc;   //bRouterDevFunc 0	
	UINT16  ExclusiveIRQ;    // 
	UINT32	CompatibleRouter;//
	UINT32	MiniPortData;    //
	UINT32  SlotCount;       //Number of Non-hotplug devices
	UINT32	HpSlotCount;	 //Number of Hotplug devices Total slots == SlotsCounrt+ HpSlotsCount
	UINT8   Reserved [3];    //0,0,0
	UINT8   Checksum;        //0
} AMI_SDL_IRQR_HDR;

typedef struct _AMI_SDL_INFO_HDR {
    UINT32  Sugnature; //"$XLT" or "$APD"
    UINT16  Size;
} AMI_SDL_INFO_HDR;

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:		PCI_DEV_FUN
//
// Description:	UNION of UINT8 and a Structure used to describe AMISDL format
// for PCI Device Function Package. Packed PCI DEV/FUNCTION number.
//
// Fields:		
//  Name            Type        Description
//   ------------------------------------------------------------------
//  DEV_FUN         UINT8       Device / Function all together
//	Fun             UINT8       PCI Device's Function#
//	Dev             UINT8       PCI Device's Device#
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
typedef  union _PCI_DEV_FUN {
	UINT8				DEV_FUN;			
	struct {
		UINT8			Fun	: 3;
		UINT8			Dev	: 5;
	};
} PCI_DEV_FUN;

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:		PCI_PIC_IRQ_DATA
//
// Description:	Structure used to describe PCI IRQ Router Register and available 
// IRQ MASK used by AMISDL output format.
//
// Fields:		
//  Name            Type        Description
//   ------------------------------------------------------------------
//  ChipsetReg      UINT8       Chipset register number 
//	IrqMask         UINT16      IRQ MASK for legacy Interrupts
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
typedef struct _PCI_PIC_IRQ_DATA {
	UINT8				ChipsetReg;
	UINT16				IrqMask;
} PCI_PIC_IRQ_DATA;

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:		PCI_IRQ_PIC_ROUTE
//
// Description:	Structure used to describe Legacy (PIC) IRQ Routing Information.
// AUTOGENERATED DATA.
//
// Fields:		
//  Name            Type                Description
//   ------------------------------------------------------------------
//  PciBusNumber    UINT8               PCI Bus # 
//	DevFun          PCI_DEV_FUN         PCI Device # \ Function #
//  PciIrq[4]       PCI_PIC_IRQ_DATA    Register \ IRQ MASK
//  SlotNum         UINT8               Pci Slot # or 0 if embeded device
//  Reserved        UINT8
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
typedef struct _PCI_IRQ_PIC_ROUTE {
	UINT8				PciBusNumber;
	PCI_DEV_FUN			DevFun;
	PCI_PIC_IRQ_DATA	PciIrq[4];
	UINT8				SlotNum;
	UINT8				Reserved;
} PCI_IRQ_PIC_ROUTE;


//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:		PCI_APIC_IRQ_DATA
//
// Description:	Structure used to describe (APIC) IRQ Routing DATA.
//
// Fields:		
//  Name            Type                Description
//   ------------------------------------------------------------------
//  IoApicItin      UINT8               IO/APIC INTIN pin 
//	IoApicId        UINT8               IO/APIC ID value
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
typedef struct _PCI_APIC_IRQ_DATA {
    UINT8   IoApicItin;
    UINT8   IoApicId;
} PCI_APIC_IRQ_DATA;


//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:		PCI_IRQ_APIC_ROUTE
//
// Description:	Structure used to describe Extended (IO/APIC) IRQ Routing 
// Information. AUTOGENERATED DATA.
//
// Fields:		
//  Name            Type                Description
//   ------------------------------------------------------------------
//  PciBusNumber    UINT8               PCI Bus # 
//	DeviceNumber    UINT8               PCI Device # 
//  Intn[4]         PCI_APIC_IRQ_DATA   APIC IRQ Routing Info.
//  Reserved        UINT8
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
typedef struct _PCI_IRQ_APIC_ROUTE {
    UINT8   			PciBusNumber;
    UINT8   			DeviceNumber;
    PCI_APIC_IRQ_DATA 	Intn[4];
    UINT8   			Reserved;
} PCI_IRQ_APIC_ROUTE;


//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:		PCI_BUS_XLAT_HDR
//
// Description:	Structure used to describe Extended (IO/APIC) IRQ Routing 
// Information. AUTOGENERATED DATA.
//
// Fields:		
//  Name            Type                Description
//   ------------------------------------------------------------------
//  BusBuild        UINT8               PCI Bus# Assigned at BIOS build time  
//	BusRun          UINT8               PCI Bus# Assigned at run time  
//  Bridge[]        PCI_DEV_FUN         Describes bridges chain 
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
typedef struct _PCI_BUS_XLAT_HDR {
	UINT8				BusBuild;
	UINT8				BusRun;
//	PCI_DEV_FUN			Bridge[];
//  UINT8               Terminator==0xFF;    
//  CAHR8               AslName[5]; //0 terminates ASL Name (4 Letters)
} PCI_BUS_XLAT_HDR;


typedef union _AMI_IOAPIC_ADDRESS{
    UINT32          ADDRESS;
    struct {
        UINT32      Func    : 8;
        UINT32      Dev     : 8;  
        UINT32      Bus     : 8;
        UINT32      Seg     : 8;
    };
}AMI_IOAPIC_ADDRESS;

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:		AMI_APIC_INFO
//
// Description:	Structure used to describe IO/APIC Information
//
// Fields:		
//  Name            Type                Description
//   ------------------------------------------------------------------
//  BusBuild        UINT8               PCI Bus# Assigned at BIOS build time  
//	BusRun          UINT8               PCI Bus# Assigned at run time  
//  Bridge[]        PCI_DEV_FUN         Describes bridges chain 
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
typedef struct _AMI_APIC_INFO {
    AMI_IOAPIC_ADDRESS      ApicAddress;
    UINT8                   ApicIdBuild;
    UINT8                   ApicIdRun;
    UINT8                   VectorBase;
} AMI_APIC_INFO;


#pragma pack(pop)

//----------------------------------------------------------------------------
//Definition of AMI Board Info Protocol.
//All PCI related VeB configuration output files 
//generated based on PCI Portibg using VeB Wizards
typedef struct _AMI_BOARD_INFO_PROTOCOL {
    BOOLEAN                 DataValid;      //Signifies if Board Specific IRQ data was updated. 
    UINT16                  BusXlatEntries;
    UINT16                  SdlPciIrqMask;  //rth_pci_dedicated_irqs_equ value from IQR_C output.
    UINT8                   Reserved[3];
    PCI_BUS_XLAT_HDR        *BusXlatTable;
    UINTN                   BusXlatLength;
    PCI_IRQ_PIC_ROUTE       *PicRoutTable;
    UINTN                   PicRoutLength;
    PCI_IRQ_PIC_ROUTE       *HpSltTablePic;
    UINTN                   HpSltPicLength;
    PCI_IRQ_APIC_ROUTE      *ApicRoutTable;
    UINTN                   ApicRoutLength;
    PCI_IRQ_APIC_ROUTE      *HpSltTableApic;
    UINTN                   HpSltApicLength;
    AMI_APIC_INFO           *ApicInfoTable;
    UINTN                   ApicInfoLength;
    VOID                    *BoardAcpiInfo;
    VOID                    *BoardOemInfo;
} AMI_BOARD_INFO_PROTOCOL;

/*
#define AMI_SDL_PICR_SIG    0x52495024
#define AMI_SDL_APICR_SIG   0x52494124
#define AMI_SDL_XLAT_SIG    0x52494124



typedef struct _AMI_BOARD_INFO_IRQ_HEADER
		 0x24,	0x50,	0x49,	0x52, // $PIR 
		 0x00,	0x01,		 // Version 0x100
		 0xF0,	0x01,		 // Size 0x1F0
		 0x00,				 // bRouterBus 0	
		 0x00,				 // bRouterDevFunc 0	
		 0x00,	0x00,		 // wExclusiveIRQ 0 
		 0x00,	0x00,	0x00,	0x00, // dCompatibleRouter 0
		 0x00,	0x00,	0x00,	0x00, // dMiniPortData 0
		 0x00,	0x00,	0x00,	0x12, //Number of Non-hotplug devices
		 0x00,	0x00,	0x00,	0x00, //Number of Hotplug devices
		 0x00,	0x00,	0x00,	 // Reserved [3]
		 0x00 			 // Checksum 0???
*/


#endif //ifndef GUID_VARIABLE_DEFINITION

/****** DO NOT WRITE BELOW THIS LINE *******/

#ifdef __cplusplus
}
#endif
#endif	//AMI_BOARD_INFO_H_


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

