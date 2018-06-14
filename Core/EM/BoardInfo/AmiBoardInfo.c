//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
// $Header: /Alaska/BIN/Core/Modules/BoardInfo/AmiBoardInfo.c 7     12/16/11 5:02p Yakovlevs $
//
// $Revision: 7 $
//
// $Date: 12/16/11 5:02p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Modules/BoardInfo/AmiBoardInfo.c $
// 
// 7     12/16/11 5:02p Yakovlevs
// Added functions headers for CHM
// 
// 6     9/30/11 5:40p Yakovlevs
// [TAG]  		EIP66222 
// [Category]  	New Feature
// [Description]  	Modify PCI bus driver to get board info from separate
// FFS section
// [Files]  		AmiBoaardInfo.c; 
// AmiBoaardInfo.mak; 
// AmiBoaardInfo.sdl;
// PciBoard.c
// AmiBoaardInfo.h
// 
// 5     6/28/11 5:51p Yakovlevs
// [TAG]  		EIP 60123 
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	Resource padding is not functional for PCIe hot-plug.
// [RootCause]  	In HP Mode #ifndef statement was not working 
// [Solution]  	Cahnged to reference AMI_HOTPLUG_INIT_SUPPORT token
// [Files]  		AmiBoardInfo.c PciBoard.c
// 
// 4     3/01/10 5:06p Yakovlevs
// New separate Label with generic Multi-Root support.
// Uses new AMI SDL "C" sytle output for the former "ASM" style.
// 
// 3     5/05/09 3:16p Felixp
// Disable ACPI module dependent code if ACPI_MODULE_VER is less or equal
// than 30
// 
// 2     5/05/09 1:07p Felixp
// Formatting update: File headers are updated.
// 
// 1     4/28/09 1:20p Yakovlevs
// Added new ModulePart - Ami Board Info. 
// This module groups together all VeB generated outpit files as well as
// DSDT generation.
// 
// 1     3/18/07 5:23p Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	<This File Name>
//
// Description:	
//
//<AMI_FHDR_END>
//**********************************************************************
#include <Token.h>
#include <AmiDxeLib.h>
#include <Protocol\AmiBoardInfo.h>

//----------------------------------------------------------------------------
//Global GUIDs Definitions goes here
EFI_GUID    gAmiBoardInfoGuid=AMI_BOARD_INFO_PROTOCOL_GUID;

/*
//----------------------------------------------------------------------------
//Variable definitions goes here
//PCI Buses Xlate Table
extern UINTN  BusNumXlatTbl;
extern UINTN  BusNumXlatTblEnd;
//----------------------------------------------------------------------------
//Legacy IRQ routing table delivered from oempir.inc and PCIBoard.ASM
extern UINTN IRQ_Table;
extern UINTN IRQ_Table_end;
//----------------------------------------------------------------------------
//IOAPIC IRQ routing table delivered from mppciirq.inc and PCIBoard.ASM
#if AMI_BOARD_VER_COMBINED >= 100
extern MP_IRI_Table;
extern UINTN MP_IRI_Table_END;
#else
extern UINTN  MP_IRI_Table;
extern MP_IRI_Table_END;
#endif
//----------------------------------------------------------------------------
//IO/APIC(s) Info Table
extern UINTN MP_IAI_Table;
extern UINTN MP_IAI_Table_END;
//----------------------------------------------------------------------------
//Hot pluf stuff
//For PIC we need it it has SLOT # Info APIC does not.
//And for verification: HP_SlotP_Count has to much HP_SlotA_Count
extern HP_SlotP_Start;
extern HP_SlotP_End;
//----------------------------------------------------------------------------
//For APIC used in MP 1.4 Tables generation
extern HP_SlotA_Start;
extern HP_SlotA_End;
*/

extern UINT8 AmlCode[];

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:		gAmiBoardProtocol
//
// Description:	Ami Board Info Protocol Instance.
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
AMI_BOARD_INFO_PROTOCOL gAmiBoardProtocol = {
    //BOOLEAN                 DataValid;      //Signifies if Board Specific IRQ data was updated. 
    FALSE,
    //UINT16                  BusXlatEntries;
    0,
    //UINT16                  SdlPciIrqMask;
    0,
    //UINT8                   Reserved[3];
    {0,0,0},
    //PCI_BUS_XLAT_HDR        *BusXlatTable;
    //UINTN                   BusXlatLength;
    NULL,0,//(PCI_BUS_XLAT_HDR*)&BusNumXlatTbl,      0,
    //PCI_IRQ_PIC_ROUTE       *PicRoutTable;
    //UINTN                   PicRoutLength;
    NULL,0,//(PCI_IRQ_PIC_ROUTE*)&IRQ_Table,         0,
    //PCI_IRQ_PIC_ROUTE       *HpSltTablePic;
    //UINTN                   HpSltPicLength;
    NULL,0,//(PCI_IRQ_PIC_ROUTE*)&HP_SlotP_Start,    0,
    //PCI_IRQ_APIC_ROUTE      *ApicRoutTable;
    //UINTN                   ApicRoutLength;
    NULL,0,//(PCI_IRQ_APIC_ROUTE*)&MP_IRI_Table,     0,
    //PCI_IRQ_APIC_ROUTE      *HpSltTableApic;
    //UINTN                   HpSltApicLength;
    NULL,0,//(PCI_IRQ_APIC_ROUTE*)&HP_SlotA_Start,   0,
    //AMI_APIC_INFO           *ApicInfoTable;
    //UINTN                   ApicInfoLength;
    NULL,0,//(AMI_APIC_INFO*)&MP_IAI_Table,          0,
    //VOID                    *BoardAcpiInfo;
#if ACPI_MODULE_VER<=30
    NULL,
#else
    &AmlCode,
#endif
    //VOID                    *BoardOemInfo;
    NULL
};

UINT8 *gSdlDataStart=NULL;
UINTN  gSdlDataLen=0;

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:		gAmiBoardProtocolHandle
//
// Description:	Ami Board Info Protocol Handle.
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
EFI_HANDLE      gAmiBoardInfoHandle=NULL;

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ParseAmiSdlData()
//
// Description: Seaarches SDL Generated Data structures for specific table 
// Signature.
//
// Input:
//  UINT8*  IN   *DataPtr    Pointer To the beginning of SDL Data.
//  UINTN   IN   DataLen     Number of bytes to parse.
//  UINT32  IN   Signature   Table Signature to Look for.
//  VOID**  IN OUT TblPtr    Double Pointer To return desired tble start address.
//                                              
// Output:	EFI_STATUS
//  EFI_SUCCESS             When everything is going on fine!
//  EFI_NOT_FOUND		    When there are no more handles to override.
//  EFI_INVALID_PARAMETER   When Parameter passed is invalid.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ParseAmiSdlData(UINT8 *DataPtr, UINTN DataLen, UINT32 Signature, OUT VOID **TblPtr){
    UINT8   *start=DataPtr;
    UINT32  *sig;
    UINTN   i;
//-----------------
    if(start==NULL || TblPtr==NULL || DataLen==0 ) return EFI_INVALID_PARAMETER;

    for(i=0; i<DataLen-sizeof(UINT32); i++){
        sig=(UINT32*)(&start[i]);
        if(*sig == Signature) {
            *TblPtr=sig;
            return EFI_SUCCESS;
        }
    }
    return EFI_NOT_FOUND;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PciBusEntryPoint()
//
// Description:	This function is the entry point for AMI Board Info Driver. 
// There it will initialize some global data and install an instance of 
// AMI_BOARD_INFO_PROTOCOL. 
//
// Input:
//	EFI_HANDLE          ImageHandle     Image handle.
//	EFI_SYSTEM_TABLE    *SystemTable    Pointer to the EFI system table.
//
// Output:	EFI_STATUS
//	EFI_SUCCESS         When everything is going on fine!
//	EFI_NOT_FOUND       When something required is not found!
//	EFI_DEVICE_ERROR    When the device is not responding!
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS AmiBoardEntryPoint(
	IN EFI_HANDLE ImageHandle,
	IN EFI_SYSTEM_TABLE *SystemTable
)
{
    EFI_STATUS                  Status;
    AMI_BOARD_INFO_PROTOCOL     *amibrd=NULL;
    UINT8                       *sdldata=NULL;
    UINTN                       sdlsize=0;
    VOID                        *DataPtr;
    UINTN                       DataLen;
    UINT8                       *p8;  
//VARIABLES TO VERIFY CONSISTANCY OF THE DATA STRUCTURES AND PORTING
    UINTN                       psc=0; //PIC table slot count
    UINTN                       asc=0; //APIC table slot count
    UINTN                       hpsc=0; //PIC table slot count
    UINTN                       hasc=0; //APIC table slot count
    
//--------------------------------
	InitAmiLib(ImageHandle,SystemTable);

    //First try to check if we are running on MultiPlatfortm Enabled BIOS
    Status=pBS->LocateProtocol(&gAmiBoardInfoGuid, NULL, &amibrd);
    if(!EFI_ERROR(Status)){
        TRACE((-1,"AmiBrdInfo: Multi-Platform BrdInfo present Status=%r Exiting",Status));
        return Status;
    }

//DEBUG
//EFI_DEADLOOP();
//DEBUG    

    amibrd=&gAmiBoardProtocol;
    
    // Reade resource section from this driver image.
    Status=ReadImageResource(ImageHandle, &gAmiBoardInfoSectionGuid, &gSdlDataStart, &gSdlDataLen);
    ASSERT_EFI_ERROR(Status);
    if(EFI_ERROR(Status)) return Status;
  
    //Init Ami Platform Info Protocol Instance...

    //1. First get Xlat Table Signature
    Status=ParseAmiSdlData(gSdlDataStart,gSdlDataLen,AMI_XLT_SIGNATURE,&DataPtr);
    ASSERT_EFI_ERROR(Status);
    if(EFI_ERROR(Status)) return Status;

    //Here we got XLAT Pointer
    DataLen=((AMI_SDL_INFO_HDR*)DataPtr)->Size;
    p8=(UINT8*)DataPtr;
    gAmiBoardProtocol.BusXlatTable=(PCI_BUS_XLAT_HDR*)(p8+sizeof(AMI_SDL_INFO_HDR));
    gAmiBoardProtocol.BusXlatLength=DataLen-sizeof(AMI_SDL_INFO_HDR);

    //2. Than get Legacy $PIR table...
    DataPtr=NULL;
    Status=ParseAmiSdlData(gSdlDataStart,gSdlDataLen,AMI_PIR_SIGNATURE,&DataPtr);
    ASSERT_EFI_ERROR(Status);
    if(EFI_ERROR(Status)) return Status;

    //Here we suppose to get PIC IRQ Routing Table.    
    DataLen=((AMI_SDL_IRQR_HDR*)DataPtr)->Size;
    p8=(UINT8*)DataPtr; //p8 points on the table header.
    //Make it point at the beginning of a data 
    p8+=sizeof(AMI_SDL_IRQR_HDR);
    gAmiBoardProtocol.PicRoutTable=(PCI_IRQ_PIC_ROUTE*)p8;
   
    //Save slot count data for verification later.
    psc=((AMI_SDL_IRQR_HDR*)DataPtr)->SlotCount;
    gAmiBoardProtocol.PicRoutLength=sizeof(PCI_IRQ_PIC_ROUTE)*psc;
   
    //advance pointer to point on HP slots start
    p8+=gAmiBoardProtocol.PicRoutLength;

    //Save HP slot count data for verification later.
    hpsc=((AMI_SDL_IRQR_HDR*)DataPtr)->HpSlotCount;

    //Now check HP Slots if any...
    if(hpsc) {
        gAmiBoardProtocol.HpSltTablePic=(PCI_IRQ_PIC_ROUTE*)p8;
        gAmiBoardProtocol.HpSltPicLength=sizeof(PCI_IRQ_PIC_ROUTE)*hpsc;
    }
    //Add to the totoal length of the system's slots length of the HP slots.
    gAmiBoardProtocol.PicRoutLength+=gAmiBoardProtocol.HpSltPicLength;

    //Update SdlPciIrqMask field ... it is last 2 bytes of the IRQ routing data buffer.
    p8=(UINT8*)DataPtr+DataLen-sizeof(UINT16);
    gAmiBoardProtocol.SdlPciIrqMask=*((UINT16*)p8);

    //3. Now get APIC Routing info.
    DataPtr=NULL;
    Status=ParseAmiSdlData(gSdlDataStart,gSdlDataLen,AMI_AIR_SIGNATURE,&DataPtr);
    ASSERT_EFI_ERROR(Status);
    if(EFI_ERROR(Status)) return Status;

    //Here we suppose to get APIC IRQ Routing Table.    
    DataLen=((AMI_SDL_IRQR_HDR*)DataPtr)->Size;
    p8=(UINT8*)DataPtr; //p8 points on the table header.
    //Make it point at the beginning of a data 
    p8+=sizeof(AMI_SDL_IRQR_HDR);
    gAmiBoardProtocol.ApicRoutTable=(PCI_IRQ_APIC_ROUTE*)p8;

    //Save slot count data for verification later.
    asc=((AMI_SDL_IRQR_HDR*)DataPtr)->SlotCount;
    gAmiBoardProtocol.ApicRoutLength=sizeof(PCI_IRQ_APIC_ROUTE)*asc;

    //advance pointer to point on HP slots start
    p8+=gAmiBoardProtocol.ApicRoutLength;

    //Save HP slot count data for verification later.
    hasc=((AMI_SDL_IRQR_HDR*)DataPtr)->HpSlotCount;

    //Now check HP Slots if any...
    if( hasc ) {
        gAmiBoardProtocol.HpSltTableApic=(PCI_IRQ_APIC_ROUTE*)p8;
        gAmiBoardProtocol.HpSltApicLength=sizeof(PCI_IRQ_APIC_ROUTE)*hasc;
    }
    //Add to the totoal length of the system's slots length of the HP slots.
    gAmiBoardProtocol.ApicRoutLength+=gAmiBoardProtocol.HpSltApicLength;

    //4. Update IO APIC info.
    DataPtr=NULL;
    Status=ParseAmiSdlData(gSdlDataStart,gSdlDataLen,AMI_APD_SIGNATURE,&DataPtr);
    ASSERT_EFI_ERROR(Status);
    if(EFI_ERROR(Status)) return Status;

    //Here we suppose to get IOA APIC Informationtable.    
    DataLen=((AMI_SDL_INFO_HDR*)DataPtr)->Size;
    p8=(UINT8*)DataPtr; //p8 points on the table header.
    gAmiBoardProtocol.ApicInfoTable=(AMI_APIC_INFO*)(p8+sizeof(AMI_SDL_INFO_HDR));
    gAmiBoardProtocol.ApicInfoLength=DataLen-sizeof(AMI_SDL_INFO_HDR);

    //So far so good...
    //Just Check consistancy of data collected.
    if( psc!=asc || hpsc!=hasc) {
        ASSERT_EFI_ERROR(EFI_INVALID_PARAMETER);
    }

    //Now install AMI BOARD INFO Protocol...
    Status=pBS->InstallMultipleProtocolInterfaces(
        &gAmiBoardInfoHandle, 
        &gAmiBoardInfoGuid, &gAmiBoardProtocol, NULL
    );

	return Status;
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************