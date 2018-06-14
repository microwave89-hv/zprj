//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             5555 Oakbrook Pkwy, Norcross, GA 30093               **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
// $Header: /Alaska/BIN/Modules/ACPI/Template/Core/ACPICORE.H 25    10/28/13 12:06p Oleksiyy $
//
// $Revision: 25 $
//
// $Date: 10/28/13 12:06p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/ACPI/Template/Core/ACPICORE.H $
// 
// 25    10/28/13 12:06p Oleksiyy
// [TAG]  		EIP121819
// [Category]  	Improvement
// [Description]  	Add $FID ACPI table.
// [Files]  		AcpiCore.c, AcpiCore.h
// 
// 24    12/03/12 11:50a Oleksiyy
// [TAG]  		EIP107890
// [Category]  	Improvement
// [Description]  	Create a token that it define the Bot and Top of Io
// APIC address.
// [Files]  		AcpiCore.h and mptable.h
// 
// 23    5/27/11 5:34p Felixp
// AcpiSdt.h is renamed to AcpiSystemDescriptionTable.h.
// 
// 22    5/14/11 2:48p Yakovlevs
// [TAG]  		EIP 56526
// [Category]  	New Feature
// [Description]  	ACPI Manipulation Protocol. PI 1.2 Spec Vol 5 Section
// 9.
// [Files]  		AcpiCore.c; AcpiCore.h; AcpiSdtPrivate.h; Aml.c; AmlChild.c;
// AmlNamespace.c; AmlOption.c; AmlString.c AcpiSdt.c; 
// Protocol\AcpiSdt.h. 
// 
// 21    8/11/09 12:46p Markw
// EIP# 24914 -- Add Local x2APIC support.
// 
// 20    5/26/09 1:43p Yakovlevs
// 
// 19    5/14/09 5:38p Yakovlevs
// Commented out Duplicated EFI_ACPI_TABLE_VERSION definition
// 
// 18    3/26/09 4:51p Oleksiyy
// New ACPI Core implementation - improves logic, execution time and
// memory usage of ACPI module.
// 
// 1     2/18/09 3:51p Oleksiyy
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	AcpiCore.h
//
// Description:	ACPI Core Header File. Main ACPI Driver Specific Definitions.
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __AcpiCore__H__
#define __AcpiCore__H__
#ifdef __cplusplus
extern "C" {
#endif

#include <Protocol\FirmwareVolume.h >
#include <Protocol\AmiSio.h>
#include <Protocol\DevicePath.h>
#include <Protocol\AcpiSupport.h>
#include <AmiDxeLib.h>
#include <AMIHobs.h>
#include <token.h>
#include <Dxe.h>
#include <AcpiRes.h>
#include "OEM_ACPI.h"
#if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x00010014)
#include <Protocol\AcpiSystemDescriptionTable.h>
#include "AcpiSdtPrivate.h"
#endif
#include <Setup.h>
#include <acpi11.h>
#include <acpi20.h>
#include <Efi.h>
#include <Acpi.h>
#include <GenericSio.h>
#pragma	pack(push, 1)

//**********************************************************************
// Protocol Data Definitions
//**********************************************************************
// ACPI Version bitmap definition:
//
// EFI_ACPI_TABLE_VERSION_1_0B - ACPI Version 1.0b (not supported curently)
// EFI_ACPI_TABLE_VERSION_2_0 - ACPI Version 2.0 
// EFI_ACPI_TABLE_VERSION_NONE - No ACPI Versions.  This might be used
//  to create memory-based operation regions or other information
//  that is not part of the ACPI "tree" but must still be found
//  in ACPI memory space and/or managed by the core ACPI driver.
//
//**********************************************************************
/*
#define EFI_ACPI_TABLE_VERSION 			UINT32

#define EFI_ACPI_TABLE_VERSION_NONE		0x00000001
#define EFI_ACPI_TABLE_VERSION_1_0B   	0x00000002
#define EFI_ACPI_TABLE_VERSION_2_0    	0x00000004
#define EFI_ACPI_TABLE_VERSION_3_0    	0x00000008
#define EFI_ACPI_TABLE_VERSION_X    	(EFI_ACPI_TABLE_VERSION_2_0 | EFI_ACPI_TABLE_VERSION_3_0)
#define EFI_ACPI_TABLE_VERSION_ALL  	(EFI_ACPI_TABLE_VERSION_1_0B|EFI_ACPI_TABLE_VERSION_X)
*/
//==================================================================//
//GUID for DSDT storage type	FFS_FILEGUID                = 11D8AC35-FB8A-44d1-8D09-0B5606D321B9
#define EFI_ACPI_DSDT_V_1_1_GUID {0x9410046e,0x1d26,0x45bc,0xb6,0x58,0xde,0xca,0xb1,0x4d,0x75,0x65}

#define EFI_ACPI_DSDT_V_2_0_GUID {0x11D8AC35,0xFB8A,0x44d1,0x8D,0x09,0x0B,0x56,0x06,0xD3,0x21,0xB9}
//ACPI tables GUIDs must be published in System Configuration table
#define EFI_ACPI_11_TABLE_GUID   {0xeb9d2d30,0x2d88,0x11d3,0x9a,0x16,0x00,0x90,0x27,0x3f,0xc1,0x4d}
#define EFI_ACPI_20_TABLE_GUID   {0x8868e871,0xe4f1,0x11d3,0xbc,0x22,0x00,0x80,0xc7,0x3c,0x88,0x81}

#define	ACPI_REV1       0x01
#define	ACPI_REV2       0x02
#define	ACPI_REV3       0x03
#define	ACPI_REV4       0x04

#define ACPI_TABLE_NOT_FOUND        (~0)
#define ACPI_TABLE_NOT_REMOVABLE    (~1)
//======================================================
//  Here Follows Definitions that are not Chipset specific
//======================================================

#define CREATOR_ID_MS 0x5446534D  //"TFSM""MSFT"(Microsoft)

#define	CREATOR_REV_MS 0x00010013

#define CREATOR_ID_AMI 0x20494D41  //" IMA""AMI "(AMI)

#define	CREATOR_REV	0x00000000


#define APIC_SIG 0x43495041  //"APIC"Multiple APIC Description Table

#define SPIC_SIG 0x43495053  //"SPIC"Multiple SAPIC Description Table

#define BOOT_SIG 0x544F4F42  //"BOOT"MS Simple Boot Spec

#define DBGP_SIG 0x50474244  //"DBGP" MS Bebug Port Spec

#define DSDT_SIG 0x54445344  //"DSDT" Differentiated System Description Table

#define ECDT_SIG 0x54444345	//"ECDT" Embedded Controller Boot Resources Table

#define ETDT_SIG 0x54445445	//"ETDT" Event Timer Description Table

#define FACP_SIG 0x50434146  //"FACP" Fixed ACPI Description Table (FADT)

#define FACS_SIG 0x53434146  //"FACS" //Firmware ACPI Control Structure

#define PSDT_SIG 0x54445350  //"PSDT"Persistent System Description Table

#define RSDT_SIG 0x54445352  //"RSDT"Root System Description Table

#define SBST_SIG 0x54534253  //"SBST"Smart Battery Specification Table

#define SLIT_SIG 0x54494C53  //"SLIT"System Locality Information Table

#define SPCR_SIG 0x52435053  //"SPCR"Serial Port Concole Redirection Table

#define SRAT_SIG 0x54415253  //"SBST"Static Resource Affinity Table

#define SSDT_SIG 0x54445353  //"SSDT"Secondary System Description Table

#define SPMI_SIG 0x494D5053  //"SPMI"Server Platform Management Interface Table

#define XSDT_SIG 0x54445358  //"XSDT" eXtended System Description Table

#define RSDP_SIG 0x2052545020445352 //"RSD PTR "

//======================================================
//  ACPI Description Headers Signatures
//======================================================
#define MCFG_SIG 0x4746434D  //PCI Express Congiguration Table

#define	HPET_SIG 0x54455048

//for testing purposes only
#define IPPT_SIG 0x54505049 // "IPPT" --  IA64 Platform Properties Table

#define FIDT_SIG 0x54444946  //"FIDT" $FID Table

#define THREE_CHAR_ARRAY(x) {(x)/10+'0',(x)%10+'0',0}

//======================================================
//  Bits Description in APICXX.Type field. ACPI 2.0
//======================================================
#ifndef AT_LAPIC_H
#define			AT_LAPIC_H		0
#endif

#ifndef	AT_IOAPIC
#define			AT_IOAPIC		1
#endif

#ifndef	AT_ISO
#define			AT_ISO			2
#endif

#ifndef	AT_NMI
#define			AT_NMI			3
#endif

#ifndef AT_LAPIC_H_NMI
#define			AT_LAPIC_H_NMI	4
#endif

#ifndef AT_LAPIC_H_ADR
#define			AT_LAPIC_H_ADR	5
#endif

#ifndef	AT_IOSAPIC
#define			AT_IOSAPIC		6
#endif
//Updated according ACPI Spec 2.0 errata 1.3
#ifndef AT_LSAPIC
#define			AT_LSAPIC		7
#endif

#ifndef AT_PIS
#define			AT_PIS			8
#endif

#ifndef AT_LX2APIC
#define			AT_LX2APIC      9
#endif

#ifndef AT_LX2APIC_NMI
#define			AT_LX2APIC_NMI  0xa
#endif

#define		IOA_BASE_BOT		APCB

#if defined(IO_APIC_BASE_TOP_ADDRESS)
#define		IOA_BASE_TOP		IO_APIC_BASE_TOP_ADDRESS
#else
#define		IOA_BASE_TOP		0xFED00000
#endif

#define		IOA_IND_REG_OFFS	0x00
#define		IOA_DAT_REG_OFFS	0x10
#define		IOA_ID_IND		    0x00
#define		IOA_VER_IND		    0x01

//<AMI_THDR_START>
//----------------------------------------------------------------------------
// Name: ACPI_AML_RES
//
// Description: Structure to store System resource Information
//
// Fields: Name             Type                    Description
//----------------------------------------------------------------------------
// Base                 UINT64
// Length               UINT64
// 
//----------------------------------------------------------------------------
//<AMI_THDR_END>

typedef struct _ACPI_AML_RES {
	UINT64			Base;
	UINT64			Length;	
} ACPI_AML_RES;

//<AMI_THDR_START>
//----------------------------------------------------------------------------
// Name: ACPI_AML_UPD_INFO
//
// Description: Structure to store Aml update information
//
// Fields: Name             Type                    Description
//----------------------------------------------------------------------------
// Dsdt1Addr            UINT64
// Dsdt2Addr            UINT64
// PciGap               ACPI_AML_RES[3]
// SS1                  BOOLEAN
// SS2                  BOOLEAN
// SS3                  BOOLEAN
// SS4                  BOOLEAN
// RomStart             UINT32
// TopOfMemory          UINT32
// SioDevStatusVar      SIO_DEV_STATUS
// 
//----------------------------------------------------------------------------
//<AMI_THDR_END>
typedef struct _ACPI_AML_UPD_INFO {
	UINT64			Dsdt1Addr;
	UINT64			Dsdt2Addr;
	ACPI_AML_RES	PciGap[3];
	BOOLEAN 		SS1;
	BOOLEAN 		SS2;
	BOOLEAN 		SS3;
	BOOLEAN 		SS4;
	UINT32			RomStart;
	UINT32			TopOfMemory;
	SIO_DEV_STATUS	SioDevStatusVar;
} ACPI_AML_UPD_INFO;

EFI_STATUS LocateACPITableProtocol (IN EFI_GUID *Protocol, OUT VOID  **Instance, IN UINT8 Version);

typedef enum {
	pgBelow1M,
	pgBelow4G,
	pgAbove4G,
	pgMaxResType,
} AML_RES_TYPE;

//======================================================
//  Bits Description in LAPIC_XX.Flags field. ACPI 2.0
//======================================================
#define		FL_ENABLE		0x0001

//<AMI_THDR_START>
//----------------------------------------------------------------------------
// Name: MADT_ENTRY_HEADER
//
// Description: Header of the entrie for MADT table.
//             
//
// Fields: Type             Name                    Description
//----------------------------------------------------------------------------
//	    UINT8	        Type
//	    UINT8	        Length
// 
//----------------------------------------------------------------------------
//<AMI_THDR_END>
typedef struct _MADT_ENTRY_HEADER{
	UINT8	Type;
	UINT8	Length; 
}MADT_ENTRY_HEADER;

//======================================================
//  LAPIC Structure per each CPU  IA32
//======================================================
typedef	struct _LAPIC_H32 {
    MADT_ENTRY_HEADER   Header;
	UINT8		        CpuId;
	UINT8		        LapicId;
	UINT32	            Flags;
} LAPIC_H32,*PLAPIC_H32, LAPIC_H_20,*PLAPIC_H_20;

//======================================================
//  LX2APIC Structure per each CPU  IA32
//======================================================
typedef	struct _LX2APIC {
    MADT_ENTRY_HEADER   Header;
    UINT16              Reserved;
	UINT32              ApicId;
	UINT32	            Flags;
    UINT32              Uid;
} LX2APIC,*PLX2APIC;

//======================================================
//  IOAPIC Structure per each CPU  IA32
//======================================================
typedef	struct _IOAPIC_H32 {
    MADT_ENTRY_HEADER   Header;
	UINT8		        IoapicId;			//2
	UINT8		        Reserved;			//3
	UINT32	            IoapicAddress;		//4
	UINT32	            SysVectBase;		//8
} IOAPIC_H32,*PIOAPIC_H32, IOAPIC_H20,*PIOAPIC_H20;

//======================================================
//  ISO Interrupt Source Override Structure IA32
//======================================================
//  Should be present per each ISA Interrupt which
//  is not identity-mapped into SAPIC Interrupt space
//======================================================
typedef	struct _ISO_H32 {
    MADT_ENTRY_HEADER   Header;
	UINT8		        Bus;				//2
	UINT8		        Source;				//3
	UINT32	            GlobalSysVect;		//4
	UINT16	            Flags;				//8

} ISO_H20,*PISO_H20;

typedef	struct _LSAPIC_H20 {	
    MADT_ENTRY_HEADER   Header;		    
	UINT8			CpuId;				//2
	UINT8			LsapicId;			//3
	UINT8			LsapicEid;			//4
    UINT8           Reserved1;          //5
    UINT8           Reserved2;          //6
    UINT8           Reserved3;          //7
	UINT32			Flags;				//8 Same as MPS 1.4 
} LSAPIC_H20,*PLSAPIC_H20;

typedef	struct _LSAPIC_H30 {	
    MADT_ENTRY_HEADER   Header;
	UINT8			CpuId;				//2
	UINT8			LsapicId;			//3
	UINT8			LsapicEid;			//4
    UINT8           Reserved1;          //5
    UINT8           Reserved2;          //6
    UINT8           Reserved3;          //7
	UINT32			Flags;				//8 Same as MPS 1.4 
    UINT32          AcpiProcUidVal;      //12
    UINT8           AcpiProcUidString;   //16 This value could be bigger than 1 byte
    //------ To Do - Deal with variable length of AcpiProcUidString
} LSAPIC_H30,*PLSAPIC_H30;

typedef	struct _IOSAPIC_H20 {	
    MADT_ENTRY_HEADER   Header;
	UINT8			IoapicId;			//2
	UINT8			Reserved;			//3
	UINT32			SysVectBase;		//8
	UINT64			IosapicAddress;		//4
} IOSAPIC_H20,*PIOSAPIC_H20;

typedef struct _ISO_PARAMETER_TABLE{
	UINT8	PicIrq;
	UINT8	Flags; 
	UINT16	ApicInt;
}ISO_PARAMETER_TABLE;


typedef	struct _NMI_H20 {
    MADT_ENTRY_HEADER   Header;
	UINT16			Flags;				//2 same as MPS INTI flags 1.4
	UINT32			GlobalSysVect;		//4
} NMI_H20,*PNMI_H20;

typedef	struct _LNMI_H20 {
    MADT_ENTRY_HEADER   Header;
	UINT8			CPU_ID;				//2
	UINT16			Flags;				//3 same as MPS INTI flags 1.4
	UINT8			LapicIntin;			//5
} LNMI_H20,*PLNMI_H20;

typedef	struct _LX2APIC_NMI {
    MADT_ENTRY_HEADER   Header;
	UINT16			Flags;				//same as MPS INTI flags 1.4
    UINT32          Uid;
	UINT8			LapicIntin;
    UINT8           Reserved[3];
} LX2APIC_NMI,*PLX2APIC_NMI;


//<AMI_THDR_START>
//----------------------------------------------------------------------------
// Name: MADT_ENTRIES
//
// Description: Structure for storing collected entries for MADT table before 
//              actualy building it. It is in the form of T_ITEM_LIST.
//
// Fields: Type             Name                    Description
//----------------------------------------------------------------------------
//    UINTN               MadtEntInitCount
//    UINTN               MadtEntCount
//    MADT_ENTRY_HEADER   **MadtEntries
// 
//----------------------------------------------------------------------------
//<AMI_THDR_END>
typedef	struct _MADT_ENTRIES {
    UINTN               MadtEntInitCount;
    UINTN               MadtEntCount;
    MADT_ENTRY_HEADER   **MadtEntries;

} MADT_ENTRIES;

//======================================================
//  Bits Description in FACS.GlobalLock field. ACPI 2.0
//======================================================
#define     GL_PENDING          0x01
#define     GL_OWNED			0x20

//<AMI_THDR_START>
//----------------------------------------------------------------------------
// Name: ACPI_TBL_ITEM
//
// Description: Structure for storing pointers for ACPI tables and it's Version
//              Member of ACPI_DB
//
// Fields: Type             Name                    Description
//----------------------------------------------------------------------------
//    ACPI_HDR                *BtHeaderPtr
//    EFI_ACPI_TABLE_VERSION  AcpiTblVer
// 
//----------------------------------------------------------------------------
//<AMI_THDR_END>
typedef	struct _ACPI_TBL_ITEM {
    ACPI_HDR                *BtHeaderPtr;
    EFI_ACPI_TABLE_VERSION  AcpiTblVer;

} ACPI_TBL_ITEM;

//<AMI_THDR_START>
//----------------------------------------------------------------------------
// Name: ACPI_DB
//
// Description: Structure for storing ACPI tables and protocols during Boottime.
//              ACPI tables are stored in the form of T_ITEM_LIST.
//
// Fields: Type             Name                   Description
//----------------------------------------------------------------------------
//    UINTN                         AcpiInitCount
//    UINTN                         AcpiEntCount
//    ACPI_TBL_ITEM                 **AcpiEntries
//    UINT32                        AcpiLength
//    EFI_ACPI_TABLE_PROTOCOL       AcpiTableProtocol
//    EFI_ACPI_SUPPORT_PROTOCOL	    AcpiSupportProtocol
//	  EFI_HANDLE					AcpiSupportHandle
// 
//----------------------------------------------------------------------------
//<AMI_THDR_END>
typedef	struct _ACPI_DB {
    UINTN                       AcpiInitCount;
    UINTN                       AcpiEntCount;
    ACPI_TBL_ITEM               **AcpiEntries;
    UINT32                      AcpiLength;
    EFI_ACPI_TABLE_PROTOCOL     AcpiTableProtocol;
    EFI_ACPI_SUPPORT_PROTOCOL	AcpiSupportProtocol;
	EFI_HANDLE					AcpiSupportHandle;
#if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x00010014)
    EFI_ACPI_SDT_PROTOCOL       AcpiSdtProtocol;
    UINTN                       NotifyInitCount;
    UINTN                       NotifyFnCount;
    EFI_ACPI_NOTIFICATION_FN    *AcpiNotifyFn;

//    UINTN                       SdtHndInitCount;
//    UINTN                       SdtHandleCount;
//    EFI_ACPI_NOTIFICATION_FN    *AcpiNotifyFn;
    EFI_AML_NODE_LIST           *AmlRootNode;
#endif
} ACPI_DB;

//Function Prototypes
UINTN FindAcpiTblByHandle (UINTN *Handle);



#pragma pack(pop)

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             5555 Oakbrook Pkwy, Norcross, GA 30093               **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
