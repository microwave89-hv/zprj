//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
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
// $Archive: /Alaska/BIN/Modules/Template/FixedBootOrder Demo/Board/em/FixedBootOrder/DefaultFixedBootOrder.c $
//
// $Author: Walonli $
//
// $Revision: 7 $
//
// $Date: 8/13/14 11:20p $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/Template/FixedBootOrder Demo/Board/em/FixedBootOrder/DefaultFixedBootOrder.c $
// 
// 7     8/13/14 11:20p Walonli
// [TAG]  		EIP180632
// [Category]  	New Feature
// [Description]  	Add FixedBootOrder Protocol to change device/group
// name.
// [Files]  		DefaultFixedBootOrder.sdl
// DefaultFixedBootOrder.c
// DefaultFixedBootOrder.mak
// DefaultFixedBootOrder.cif
// 
// 6     8/12/13 4:25a Easonchen
// [TAG]  		N/A
// [Category]  	Improvement
// [Description]  	CppCheck error fix.
// [Files]  		DefaultFixedBootOrder.c
// 
// 5     5/31/13 2:33a Easonchen
// [TAG]  		EIP123284
// [Category]  	Improvement
// [Description]  	Set Boot Priority unicode string
// [Files]  		FixedBootOrder.c
// FixedBootOrder.h
// FixedBootOrder.sdl
// FixedBootOrderTSE.c
// DefaultFixedBootOrder.c
// DefaultFixedBootOrder.sd
// DefaultFixedBootOrder.uni
// 
// 4     5/28/13 5:29a Easonchen
// [TAG]  		EIP122146
// [Category]  	Improvement
// [Description]  	Support Dual mode default priority with tool AMIBCP. 
// [Files]  		
// FboSetOrder.c
// FixedBootOrder.c
// FixedBoorOrderTse.c
// DefaultFixedBootOrder.c
// DefaultFixedBootOrder.sd
// DefaultFixedBootOrder.uni
// 
// 3     4/22/13 11:20p Easonchen
// [TAG]  		EIP101213
// [Category]  	Improvement
// [Description]  	FixedBootOrder should match the BootOrder variable
// [Files]  		FboSetOrder.c
// FixedBootOrder.sdl
// DefaultFixedBootOrder.c
// 
// 2     10/04/12 2:17a Easonchen
// [TAG]  		EIP96232
// [Category]  	Improvement
// [Description]  	Support USB Floppy in UEFI mode
// [Files]  		FixedBootOrder.h
// DefaultFixedBootOrder.c
// DefaultFixedBootOrder.sd
// DefaultFixedBootOrder.uni
// 
// 1     6/28/12 11:41a Easonchen
// Make a new FixedBootOrder module by utilizing 4.6.4.1 BDS
// functionality.
// 
//
//*****************************************************************//

//<AMI_FHDR_START>
//----------------------------------------------------------------------
//
// Name:	DefaultFixedBootOrder.c
//
// Description:	Default FixedBootOrder Boot type setting.
//
//----------------------------------------------------------------------
//<AMI_FHDR_END>

//----------------------------------------------------------------------
// Include Files
//----------------------------------------------------------------------
#include <efi.h>
#include <amidxelib.h>
#include <BootOptions.h>
#include <protocol\PciIo.h>
#if CSM_SUPPORT
#include <Protocol\LegacyBios.h>
#endif
#include <protocol\PciRootBridgeIo.h>
#include <protocol\PDiskInfo.h>
#include <PciHostBridge.h>
#include <Setup.h>
#include "FixedBootOrder.h"
#include "SetupStrTokens.h"
#include "Build/DefaultFixedBootOrder.h"
//---------------------------------------------------------------------------
// Global Variable declarations
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
// External functions
//---------------------------------------------------------------------------
EFI_HANDLE GetPhysicalBlockIoHandle(EFI_HANDLE BlockIoHandle);
BOOLEAN IsUSBkeyByHandle(EFI_HANDLE Handle);
BOOLEAN IsShellBootOption(BOOT_OPTION *Option);
UINT32 FBO_FindTagPriority(UINT16 Tag);
//---------------------------------------------------------------------------
// Global Variable declarations
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
// Function Definitions
//---------------------------------------------------------------------------
UINT32 GetUefiBootOptionTag(IN EFI_DEVICE_PATH_PROTOCOL *Dp) ;
EFI_STATUS SetDevNewDescription(EFI_DEVICE_PATH_PROTOCOL *DpHead, CHAR16 *Description) ;
//---------------------------------------------------------------------------
// Type definitions
//---------------------------------------------------------------------------
typedef VOID (FBO_CHANGE_DEVICE_NAME)(FBO_DEVICE_INFORM *Content);
extern FBO_CHANGE_DEVICE_NAME FBO_CHANGE_DEVICE_NAME_FUNCS EndOfFboChangeDeviceName ;
FBO_CHANGE_DEVICE_NAME *FboChangeDeviceNameFuncs[] = { FBO_CHANGE_DEVICE_NAME_FUNCS NULL } ;

#ifndef EFI_PCI_CFG_ADDRESS
#define	EFI_PCI_CFG_ADDRESS(bus,dev,func,reg)	\
 ((UINT64) ( (((UINTN)bus) << 24)+(((UINTN)dev)	<< 16) + (((UINTN)func)	<< 8) + ((UINTN)reg)))& 0x00000000ffffffff
#endif
#define offsetof(type, member) ( (int) & ((type*)0) -> member )
//---------------------------------------------------------------------------
// Constant and Variables declarations
//---------------------------------------------------------------------------
typedef enum{
//    BoTagLegacyXxx
//    BoTagUefiXxx
//    BoTagXxx
//--standard device type don't modify--//
    BoTagLegacyFloppy = 1,	//1
    BoTagLegacyHardDisk,	//2
    BoTagLegacyCdrom,		//3
    BoTagLegacyPcmcia,		//4
    BoTagLegacyUsb,		//5
    BoTagLegacyEmbedNetwork,	//6
    BoTagLegacyBevDevice = 0x80,//7
//--standard device type don't modify--// end
    BoTagLegacyUSBFloppy = 8,
    BoTagLegacyUSBHardDisk,
    BoTagLegacyUSBCdrom,
    BoTagLegacyUSBKey,
    BoTagUefiUSBFloppy,				//(EIP96232+)
    BoTagUefiHardDisk,
    BoTagUefiCdrom,
    BoTagUefiUsbHardDisk,
    BoTagUefiUsbKey,
    BoTagUefiUsbCdrom,
    BoTagUefiNetWork,
    BoTagUefi,
    BoTagEmbeddedShell
} FIXED_BOOT_OPTION_TAG;


FIXED_BOOT_OPTION_TAG FixedLegacyBootOptionTags[] = {
		    0,
    BoTagLegacyFloppy,
    BoTagLegacyHardDisk,
    BoTagLegacyCdrom,
    BoTagLegacyPcmcia,
    BoTagLegacyUsb,
    BoTagLegacyEmbedNetwork,
    BoTagLegacyBevDevice,
    BoTagLegacyUSBFloppy,
    BoTagLegacyUSBHardDisk,
    BoTagLegacyUSBCdrom,
    BoTagLegacyUSBKey,
    UNASSIGNED_HIGHEST_TAG
};

FBODevMap FBOUefiDevMapData[]={
	{  BoTagUefiHardDisk,  	    0,      0xff, 0},
	{  BoTagUefiCdrom,          0,      0xff, 0},
	{  BoTagUefiUsbHardDisk,    0,      0xff, 0},
	{  BoTagUefiUsbCdrom,       0,      0xff, 0},
	{  BoTagUefiUsbKey,	        0,	    0xff, 0},
	{  BoTagUefiUSBFloppy,	    0,	    0xff, 0},		//(EIP96232+)
	{  BoTagUefiNetWork,        0,      0xff, 0},
	{  0, 0 }	//end of data
};

#if CSM_SUPPORT
FBODevMap FBOLegacyDevMapData[]={

	{  BoTagLegacyHardDisk,     BBS_HARDDISK,      0xff, 0},
	{  BoTagLegacyCdrom,        BBS_CDROM,         0xff, 0},
	{  BoTagLegacyUSBHardDisk,  BBS_HARDDISK,      0xff, F_USB},
	{  BoTagLegacyUSBCdrom,     BBS_CDROM,         0xff, F_USB},
	{  BoTagLegacyUSBKey,       BBS_HARDDISK,      0xff, F_USB | F_USBKEY},
	{  BoTagLegacyUSBFloppy,    BBS_FLOPPY,        0xff, F_USB},
	{  BoTagLegacyEmbedNetwork, BBS_EMBED_NETWORK, 0xff, 0},
	{  0, 0 }	//end of data
};

FBODevMap FBODualDevMapData[]={
	{  BoTagUefiHardDisk,  	    0,      	       	0xff, 0},
	{  BoTagUefiCdrom,          0,      	       	0xff, 0},
	{  BoTagUefiUsbHardDisk,    0,     	       		0xff, 0},
	{  BoTagUefiUsbCdrom,       0,     	       		0xff, 0},
	{  BoTagUefiUsbKey,	    	0,	   	       		0xff, 0},
	{  BoTagUefiUSBFloppy,	    0,	    			0xff, 0},		//(EIP96232+)
	{  BoTagUefiNetWork,        0,     	       		0xff, 0},

	{  BoTagLegacyHardDisk,     BBS_HARDDISK,      	0xff, 0},
	{  BoTagLegacyCdrom,        BBS_CDROM,         	0xff, 0},
	{  BoTagLegacyUSBHardDisk,  BBS_HARDDISK,      	0xff, F_USB},
	{  BoTagLegacyUSBCdrom,     BBS_CDROM,         	0xff, F_USB},
	{  BoTagLegacyUSBKey,       BBS_HARDDISK,      	0xff, F_USB | F_USBKEY},
	{  BoTagLegacyUSBFloppy,    BBS_FLOPPY,        	0xff, F_USB},
	{  BoTagLegacyEmbedNetwork, BBS_EMBED_NETWORK, 	0xff, 0},
	{  0, 0 }	//end of data
};
#endif

#if (FBO_DUAL_MODE == 1) && (CSM_SUPPORT == 1)
FBOHiiMap FBOHiiMapData[]={
	{  BoTagLegacyHardDisk,     STR_BOOT_HDD,               HDD_BOOT_FORM_ID,         HDD_BOOT_FORM_LABEL,         offsetof(FIXED_BOOT_GROUP, LegacyHDD)},
	{  BoTagLegacyCdrom,        STR_BOOT_CDROM,             ODD_BOOT_FORM_ID,         ODD_BOOT_FORM_LABEL,         offsetof(FIXED_BOOT_GROUP, LegacyODD)},
	{  BoTagLegacyEmbedNetwork, STR_BOOT_NETWORK,           NET_BOOT_FORM_ID,         NET_BOOT_FORM_LABEL,         offsetof(FIXED_BOOT_GROUP, LegacyNET)},
	{  BoTagLegacyUSBFloppy,    STR_BOOT_USBFDD,            USBFDD_BOOT_FORM_ID,      USBFDD_BOOT_FORM_LABEL,      offsetof(FIXED_BOOT_GROUP, LegacyUSBFDD)},
	{  BoTagLegacyUSBHardDisk,  STR_BOOT_USBHDD,            USBHDD_BOOT_FORM_ID,      USBHDD_BOOT_FORM_LABEL,      offsetof(FIXED_BOOT_GROUP, LegacyUSBHDD)},
	{  BoTagLegacyUSBCdrom,     STR_BOOT_USBODD,            USBODD_BOOT_FORM_ID,      USBODD_BOOT_FORM_LABEL,      offsetof(FIXED_BOOT_GROUP, LegacyUSBODD)},
	{  BoTagLegacyUSBKey,       STR_BOOT_USBKEY,            USBKEY_BOOT_FORM_ID,      USBKEY_BOOT_FORM_LABEL,      offsetof(FIXED_BOOT_GROUP, LegacyUSBKEY)},
	{  BoTagUefiHardDisk,	    STR_DUAL_BOOT_UEFI_HDD,     UEFI_HDD_BOOT_FORM_ID,    UEFI_HDD_BOOT_FORM_LABEL,    offsetof(FIXED_BOOT_GROUP, UefiHDD)},
	{  BoTagUefiCdrom,	    	STR_DUAL_BOOT_UEFI_CDROM,   UEFI_ODD_BOOT_FORM_ID,    UEFI_ODD_BOOT_FORM_LABEL,    offsetof(FIXED_BOOT_GROUP, UefiODD)},
	{  BoTagUefiNetWork,	    STR_DUAL_BOOT_UEFI_NETWORK, UEFI_NET_BOOT_FORM_ID,    UEFI_NET_BOOT_FORM_LABEL,    offsetof(FIXED_BOOT_GROUP, UefiNET)},
	{  BoTagUefiUsbHardDisk,    STR_DUAL_BOOT_UEFI_USBHDD,  UEFI_USBHDD_BOOT_FORM_ID, UEFI_USBHDD_BOOT_FORM_LABEL, offsetof(FIXED_BOOT_GROUP, UefiUSBHDD)},
	{  BoTagUefiUsbCdrom,	    STR_DUAL_BOOT_UEFI_USBODD,  UEFI_USBODD_BOOT_FORM_ID, UEFI_USBODD_BOOT_FORM_LABEL, offsetof(FIXED_BOOT_GROUP, UefiUSBODD)},
	{  BoTagUefiUsbKey,	    	STR_DUAL_BOOT_UEFI_USBKEY,  UEFI_USBKEY_BOOT_FORM_ID, UEFI_USBKEY_BOOT_FORM_LABEL, offsetof(FIXED_BOOT_GROUP, UefiUSBKEY)},
	{  BoTagUefiUSBFloppy,	    STR_DUAL_BOOT_UEFI_USBFDD,  UEFI_USBFDD_BOOT_FORM_ID, UEFI_USBFDD_BOOT_FORM_LABEL, offsetof(FIXED_BOOT_GROUP, UefiUSBFDD)},		//(EIP96232+)
	{  0, 0 }	//end of data
};
#else
FBOHiiMap FBOHiiMapData[]={
	{  BoTagLegacyHardDisk,     STR_BOOT_HDD,          HDD_BOOT_FORM_ID,         HDD_BOOT_FORM_LABEL,         offsetof(FIXED_BOOT_GROUP, LegacyHDD)},
	{  BoTagLegacyCdrom,        STR_BOOT_CDROM,        ODD_BOOT_FORM_ID,         ODD_BOOT_FORM_LABEL,         offsetof(FIXED_BOOT_GROUP, LegacyODD)},
	{  BoTagLegacyEmbedNetwork, STR_BOOT_NETWORK,      NET_BOOT_FORM_ID,         NET_BOOT_FORM_LABEL,         offsetof(FIXED_BOOT_GROUP, LegacyNET)},
	{  BoTagLegacyUSBFloppy,    STR_BOOT_USBFDD,       USBFDD_BOOT_FORM_ID,      USBFDD_BOOT_FORM_LABEL,      offsetof(FIXED_BOOT_GROUP, LegacyUSBFDD)},
	{  BoTagLegacyUSBHardDisk,  STR_BOOT_USBHDD,       USBHDD_BOOT_FORM_ID,      USBHDD_BOOT_FORM_LABEL,      offsetof(FIXED_BOOT_GROUP, LegacyUSBHDD)},
	{  BoTagLegacyUSBCdrom,     STR_BOOT_USBODD,       USBODD_BOOT_FORM_ID,      USBODD_BOOT_FORM_LABEL,      offsetof(FIXED_BOOT_GROUP, LegacyUSBODD)},
	{  BoTagLegacyUSBKey,       STR_BOOT_USBKEY,       USBKEY_BOOT_FORM_ID,      USBKEY_BOOT_FORM_LABEL,      offsetof(FIXED_BOOT_GROUP, LegacyUSBKEY)},
	{  BoTagUefiHardDisk,	    STR_BOOT_UEFI_HDD,     UEFI_HDD_BOOT_FORM_ID,    UEFI_HDD_BOOT_FORM_LABEL,    offsetof(FIXED_BOOT_GROUP, UefiHDD)},
	{  BoTagUefiCdrom,	    	STR_BOOT_UEFI_CDROM,   UEFI_ODD_BOOT_FORM_ID,    UEFI_ODD_BOOT_FORM_LABEL,    offsetof(FIXED_BOOT_GROUP, UefiODD)},
	{  BoTagUefiNetWork,	    STR_BOOT_UEFI_NETWORK, UEFI_NET_BOOT_FORM_ID,    UEFI_NET_BOOT_FORM_LABEL,    offsetof(FIXED_BOOT_GROUP, UefiNET)},
	{  BoTagUefiUsbHardDisk,    STR_BOOT_UEFI_USBHDD,  UEFI_USBHDD_BOOT_FORM_ID, UEFI_USBHDD_BOOT_FORM_LABEL, offsetof(FIXED_BOOT_GROUP, UefiUSBHDD)},
	{  BoTagUefiUsbCdrom,	    STR_BOOT_UEFI_USBODD,  UEFI_USBODD_BOOT_FORM_ID, UEFI_USBODD_BOOT_FORM_LABEL, offsetof(FIXED_BOOT_GROUP, UefiUSBODD)},
	{  BoTagUefiUsbKey,	    	STR_BOOT_UEFI_USBKEY,  UEFI_USBKEY_BOOT_FORM_ID, UEFI_USBKEY_BOOT_FORM_LABEL, offsetof(FIXED_BOOT_GROUP, UefiUSBKEY)},
	{  BoTagUefiUSBFloppy,	    STR_BOOT_UEFI_USBFDD,  UEFI_USBFDD_BOOT_FORM_ID, UEFI_USBFDD_BOOT_FORM_LABEL, offsetof(FIXED_BOOT_GROUP, UefiUSBFDD)},		//(EIP96232+)
	{  0, 0 }	//end of data
};
#endif
                //(EIP123284+)>
UINT16 BootOptionStringToken[]={
    STR_BOOT_ORDER_1,
    STR_BOOT_ORDER_2,
    STR_BOOT_ORDER_3,
    STR_BOOT_ORDER_4,
    STR_BOOT_ORDER_5,
    STR_BOOT_ORDER_6,
    STR_BOOT_ORDER_7,
    STR_BOOT_ORDER_8,
    STR_BOOT_ORDER_9,
    STR_BOOT_ORDER_10,
    STR_BOOT_ORDER_11,
    STR_BOOT_ORDER_12,
    STR_BOOT_ORDER_13,
    STR_BOOT_ORDER_14,
    STR_BOOT_ORDER_15,
    STR_BOOT_ORDER_16
};
                //<(EIP123284+)

EFI_STATUS DefaultFixedBootOrder_Init(IN void)
{
	EFI_STATUS Status;
	EFI_GUID FixedBootOrderGuid=FIXED_BOOT_ORDER_GUID;
	EFI_FIXED_BOOT_ORDER_PROTOCOL *pFBO=NULL;
		
    Status = pBS->LocateProtocol( &FixedBootOrderGuid, NULL, &pFBO );
	if( !EFI_ERROR(Status) )
	{
		pFBO->SetUefiDevMap( FBOUefiDevMapData );
#if CSM_SUPPORT
		pFBO->SetLegacyDevMap( FBOLegacyDevMapData );
		pFBO->SetDualDevMap( FBODualDevMapData );
#endif
		pFBO->SetHiiMap( FBOHiiMapData );
		pFBO->SetBootOptionTokenMap( BootOptionStringToken );  //(EIP123284+)
	}
	return Status;
}

#if CSM_SUPPORT
//TODO:: OEM FUNCTION	>>>
//reference CRB SbSetup.c
UINT16 gSATAAhci[6] = { 0, 1, 2, 3, 4, 5 };

UINT16 gSATA[3][2] = {
  { 0, 1 },
  { 2, 3 },
  { 4, 5 }
};


//Check ATA port number
UINT16 CheckAhciSata(BBS_TABLE *BbsTable)
{
	EFI_STATUS Status;
	EFI_GUID gEfiDiskInfoProtocolGuid = EFI_DISK_INFO_PROTOCOL_GUID;
  	EFI_DISK_INFO_PROTOCOL *DiskInfo;
  	UINT32 SataPortIndex;
	UINT32 SataPMPort;
	EFI_HANDLE Handle;

	Handle = *(VOID**)(&BbsTable->IBV1);

	Status = pBS->HandleProtocol ( Handle, &gEfiDiskInfoProtocolGuid, &DiskInfo );

	if ( !EFI_ERROR(Status) )
	{
	   	Status = DiskInfo->WhichIde(
                                DiskInfo,
                                &SataPortIndex,
                                &SataPMPort
                                );

                if( !EFI_ERROR(Status) )
                    return gSATAAhci[SataPortIndex];
	}  
	return 0xff;
}


UINT16 CheckATAPortNumber(BBS_TABLE *BbsTable)
{
	EFI_STATUS Status;
	EFI_GUID gEfiDiskInfoProtocolGuid = EFI_DISK_INFO_PROTOCOL_GUID;
	EFI_DISK_INFO_PROTOCOL *DiskInfo;
	UINT32 IdeChannel;
	UINT32 IdeDevice;
	EFI_HANDLE Handle;

	Handle = *(VOID**)(&BbsTable->IBV1);     

	Status = pBS->HandleProtocol ( Handle, &gEfiDiskInfoProtocolGuid, &DiskInfo );

	if ( !EFI_ERROR(Status) )
	{
   	 	Status = DiskInfo->WhichIde ( DiskInfo, &IdeChannel, &IdeDevice );

		if( !EFI_ERROR(Status) )
		{
			if( BbsTable->Function == 5 ) 
				return gSATA[IdeDevice+2][IdeChannel];
			else
				return gSATA[IdeDevice][IdeChannel];    
		}
	}
	return 0xff;
}

UINT8 CheckSATAMode(BBS_TABLE *BbsTable)
{
	EFI_STATUS Status;
	EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *gPciRootBridgeIo;

	UINT8 PciData8;

  	Status = pBS->LocateProtocol(
                      &gEfiPciRootBridgeIoProtocolGuid,
                      NULL,
                      &gPciRootBridgeIo
                    );

	if(!EFI_ERROR(Status))	
	{
                UINT32 PciBus, PciDevice, PciFunction;

		PciBus=BbsTable->Bus;
		PciDevice=BbsTable->Device;
		PciFunction=BbsTable->Function;

                gPciRootBridgeIo->Pci.Read(
                            gPciRootBridgeIo,
                            EfiPciIoWidthUint8,
                            EFI_PCI_CFG_ADDRESS(PciBus, PciDevice, PciFunction, 0x0a),	//0A=PCI ClassCode Regsiter
                            1,
                            &PciData8 );

		return PciData8;
	}

	return 0xff;
}
			
UINT16 GetDevicePortNumber(BBS_TABLE *BbsTable)
{
    UINT16 PortNumber=0xff;

//	if( (BbsTable->Class!=0xc) && (BbsTable->SubClass!=0x3) )
	if( BbsTable->DeviceType == BBS_HARDDISK )
	{
    	switch (CheckSATAMode(BbsTable))
    	{
			case 0x01:	//IDE Class Code
            	PortNumber=CheckATAPortNumber(BbsTable);
            	break;
           
        	case 0x06:	//AHCI Class Code
            	PortNumber=CheckAhciSata(BbsTable);
           		break;
    	}
	}
    return PortNumber;
}
//TODO:: OEM FUNCTION	<<<	
#endif	//#if CSM_SUPPORT

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: FboChangeGroupName
//
// Description: Change Boot Option Group Name, OEM have two way to modify Group Name in run time, such as USB Key - > OEM USB Key
//                  1.Provide StrToken(Define in .uni), New Group Name.
//                      FboChangeGroupName( STR_BOOT_HDD, NULL, NewGroupName) ;
//                  2.Provide Original Group Name(ex:Hard Disk), New Group Name.
//                      FboChangeGroupName( 0, OrgGroupName, NewGroupName) ;  
//          
// Referrals: None
//
// Notes: EIP 143657
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
FboChangeGroupName(
    IN OPTIONAL UINT16 StrToken,
    IN OPTIONAL CHAR16* OrgGroupName, 
    IN CHAR16* NewGroupName )
{
    EFI_STATUS Status ;
    UINT32 Attr ;
    UINTN Size = 0 ,*GroupPtrAddr = NULL ;
    FBO_GROUP_OPTION *Group = NULL ;
    EFI_GUID FixedBootOrderGuid = FIXED_BOOT_ORDER_GUID ;
    
    TRACE((-1,"DefaultFixedBootOrder.c FboChangeGroupName\n")) ;
    if (StrToken == 0 && OrgGroupName == NULL )
        return EFI_INVALID_PARAMETER ;
    
    Status = GetEfiVariable(L"FboGroupNameData", &FixedBootOrderGuid, &Attr, &Size, &GroupPtrAddr);
    if(EFI_ERROR(Status))
    {
        Group = MallocZ(sizeof(FBO_GROUP_OPTION)) ;
        // Firsrt time, Restore the group pointer address to variable.
        Status = pRS->SetVariable ( L"FboGroupNameData",
                                    &FixedBootOrderGuid,
                                    EFI_VARIABLE_BOOTSERVICE_ACCESS,
                                    sizeof(UINTN),
                                    &Group );
    }
    else
    {
        // Go To the last node.
        Group = (FBO_GROUP_OPTION*)*GroupPtrAddr ;
        while (Group->Next)
            Group = Group->Next ;
        // Create the new node.
        Group->Next = MallocZ(sizeof(FBO_GROUP_OPTION)) ;
        Group = Group->Next ;
    }

    Group->NewGroupName = MallocZ( Wcslen(NewGroupName)*sizeof(CHAR16)+1) ;
    Wcscpy( Group->NewGroupName, NewGroupName) ;
    if (StrToken) Group->StrToken = StrToken ;
    else
    {
        Group->OrgGroupName = MallocZ( Wcslen(OrgGroupName)*sizeof(CHAR16)+1) ;
        Wcscpy( Group->OrgGroupName, OrgGroupName) ;
    }
    pBS->FreePool(GroupPtrAddr) ; // Avoid memory leak
    return EFI_SUCCESS ;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: GetDevInform
//
// Description: Get Device Information(Description, Type, Path) by BootOptionList
//
// Input: FBO_DEVICE_INFORM **DevHead
//
// Output: FBO_DEVICE_INFORM **DevHead
// 
// Notes: EIP 143657
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
GetDevInformByBootOptionList(
    FBO_DEVICE_INFORM **DevHead)
{
    FBO_DEVICE_INFORM *DevInform = NULL;
    EFI_DEVICE_PATH_PROTOCOL *Dp = NULL ;
    DLINK *Link;
    BOOT_OPTION *Option;
    EFI_STATUS Status ;
    FOR_EACH_BOOT_OPTION(BootOptionList, Link, Option)
    {
        BOOLEAN UsbPortFlag = FALSE ;
        if (Option->GroupHeader) continue ;
        if (!DevInform)
            *DevHead = DevInform = MallocZ(sizeof(FBO_DEVICE_INFORM)) ;
        else
        {
            DevInform->Next = MallocZ(sizeof(FBO_DEVICE_INFORM)) ;
            DevInform = DevInform->Next ;
        }
        
        DevInform->DevName = Option->Description ;
        // Set Default value.
        DevInform->DevPortNum = 0xff ;
        DevInform->DevBDF = 0xffffffff ; 
        
        if (IsLegacyBootOption(Option))
        {
            // Legacy Option need use Handle Protocol to get correct Device Path.
            Status = pBS->HandleProtocol((EFI_HANDLE)Option->BbsEntry->IBV1, &gEfiDevicePathProtocolGuid, &Dp);
            if (EFI_ERROR(Status)) continue ;
            DevInform->DevPath = Dp ;
            DevInform->DevType = (UINT16)(0xff&Option->Tag) ;
            DevInform->DevBDF = (UINT32) (Option->BbsEntry->Bus << 16)|
                                                                  (Option->BbsEntry->Device << 11) |
                                                                  (Option->BbsEntry->Function << 8);
        }
        else 
        {
            UINT32 Bus = 0 ;   
            // Uefi Option just need get device path by Option->FilePathList.
            DevInform->DevPath = Option->FilePathList ;
            DevInform->DevType = (UINT16)GetUefiBootOptionTag(Option->FilePathList) ;
            
            // Get Uefi Option BDF
            Dp = DevInform->DevPath ;
            while(!(isEndNode(Dp)))
            {
                if ( Dp->Type == ACPI_DEVICE_PATH && Dp->SubType == ACPI_DP )
                {
                    Bus = ((ACPI_HID_DEVICE_PATH*)Dp)->UID ;
                }
                else if ( Dp->Type == HARDWARE_DEVICE_PATH && Dp->SubType == HW_PCI_DP )
                {
                    DevInform->DevBDF = (UINT32) (Bus << 16) |
                                                                          (((PCI_DEVICE_PATH*)Dp)->Device << 11) |
                                                                          (((PCI_DEVICE_PATH*)Dp)->Function << 8);        
                    break ;
                }
                Dp=NEXT_NODE(Dp) ;
            }
        }
        
        // Get USB and SATA Port Number
        Dp = DevInform->DevPath ;
        while (!(isEndNode(Dp)))
        {
            if ( Dp->Type == MESSAGING_DEVICE_PATH && Dp->SubType == MSG_SATA_DP )
            {
                DevInform->DevPortNum = ((SATA_DEVICE_PATH*)Dp)->PortNumber ;
                break ;
            }
            else if ( Dp->Type == MESSAGING_DEVICE_PATH && Dp->SubType == MSG_USB_DP )
            {
                if (!UsbPortFlag) UsbPortFlag = TRUE ;
                else
                {
                    DevInform->DevPortNum = (UINT16)((USB_DEVICE_PATH*)Dp)->ParentPortNumber ;
                    break ;
                }
            }
            Dp=NEXT_NODE(Dp) ;
        }
    }
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: SetDevNewDescription
//
// Description: Set Device New Description
//
// Input: EFI_DEVICE_PATH_PROTOCOL *DpHead
//           CHAR16 *Description
// Output:
//
// Notes: OEM can use this function to update new device description.
//            example: SetDevNewDescription(Dp, L"OEM USB Key")
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
SetDevNewDescription(
    EFI_DEVICE_PATH_PROTOCOL *DpHead, 
    CHAR16 *Description)
{
    EFI_STATUS Status = EFI_SUCCESS;
    EFI_FIXED_BOOT_ORDER_PROTOCOL*FBOProtocol ;
    EFI_GUID FixedBootOrderGuid=FIXED_BOOT_ORDER_GUID;
    Status = pBS->LocateProtocol (&FixedBootOrderGuid, NULL, &FBOProtocol);
    if (!EFI_ERROR(Status))
    {
        // Prepare FBO_DEVICE_INFORM data
        FBO_DEVICE_INFORM *SetData = MallocZ(sizeof(FBO_DEVICE_INFORM));
        EFI_DEVICE_PATH_PROTOCOL *Dp = NULL ;
        UINTN DpSize = 0 ;
        Dp = DpHead ;
        for ( ; !(isEndNode(Dp)) ; Dp=NEXT_NODE(Dp))
            DpSize+=NODE_LENGTH(Dp) ;
        DpSize += sizeof(EFI_DEVICE_PATH_PROTOCOL) ; //End Node Size
        
        SetData->DevName = MallocZ(Wcslen(Description)*sizeof(CHAR16)+1) ;
        SetData->DevPath = MallocZ(DpSize) ;
        Wcscpy( SetData->DevName, Description);
        MemCpy( SetData->DevPath, DpHead, DpSize);
        // Set to new description.
        Status = FBOProtocol->SetNewDescription( SetData ) ;
    }
    return Status ;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: FBO_AdjustDeviceName
//
// Description: Change FBO Device Name
//
// Input:
//
// Output:
//
// Notes: EIP 143657
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
FBO_AdjustDeviceName()
{
    EFI_STATUS Status = EFI_SUCCESS;
    FBO_DEVICE_INFORM *Node = NULL, *PreNode = NULL ;
    UINT16 x ;
    GetDevInformByBootOptionList(&Node) ;
    for ( x=0 ; FboChangeDeviceNameFuncs[x] ; x++)
        FboChangeDeviceNameFuncs[x](Node) ;
    
    // Free Linked list data ;
    while (Node)
    {
        PreNode = Node;
        Node = Node->Next;
        pBS->FreePool(PreNode);
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   FBO_SetBootOptionTags
//
// Description: Go through the entire boot option list and Apply priorities for 
//              each entry in the list.
//
// Input:       DLIST *BootOptionList - the entire Boot Option List
//
// Output:      none
//
// Note:        To change boot order priorities
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID FBO_SetBootOptionTags(){
	DLINK *Link;
    BOOT_OPTION *Option;
    UINT32 UefiBootOptionsInc = 0x100;

    FOR_EACH_BOOT_OPTION(BootOptionList,Link,Option){
        UINT32 TagPriority;
        UINT32 BaseTag = UNASSIGNED_HIGHEST_TAG;
#ifdef CSM_SUPPORT
        if (IsLegacyBootOption(Option)){
            UINT16 DeviceType;
            DeviceType = ((BBS_BBS_DEVICE_PATH*)Option->FilePathList)->DeviceType;
	    if( DeviceType == BoTagLegacyBevDevice )
			BaseTag = DeviceType;
	    else
	    if( DeviceType != BBS_UNKNOWN )
			BaseTag = FixedLegacyBootOptionTags[DeviceType];
        }else
#endif
        if (IsShellBootOption(Option)) BaseTag = BoTagEmbeddedShell;
        else BaseTag = BoTagUefi;
        if (BaseTag == UNASSIGNED_HIGHEST_TAG) continue;
        	TagPriority = FBO_FindTagPriority(BaseTag);
        //UEFI boot options must have unique tags, otherwise then will be groupped when 
        //GROUP_BOOT_OPTIONS_BY_TAG tokens is enabled
        if (BaseTag == BoTagUefi) BaseTag += UefiBootOptionsInc++;
        	Option->Tag = BootOptionTag(BaseTag, TagPriority);
	}
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetUefiBootOptionTag
//
// Description:	Function returns device type for given handle
//
// Input:       EFI_DEVICE_PATH_PROTOCOL *Dp -
//
// Output:      UINT32 - device type
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT32 GetUefiBootOptionTag(
    IN EFI_DEVICE_PATH_PROTOCOL *Dp
)
{
    EFI_STATUS Status;
    EFI_HANDLE Handle, BlockHandle;
    EFI_DEVICE_PATH_PROTOCOL *DpPtr = Dp;
    BOOLEAN IsUSB = FALSE;

    if( Dp == NULL )
	return UNASSIGNED_HIGHEST_TAG;

    for( ; !(isEndNode(DpPtr)); DpPtr = NEXT_NODE(DpPtr))
    {
        if(DpPtr->Type == MESSAGING_DEVICE_PATH)
        {
			if(DpPtr->SubType == MSG_USB_DP)
				IsUSB = TRUE;
			//Check Windows To Go USB Hard Disk boot option. (EIP101213+)>
			if(DpPtr->SubType == MSG_USB_CLASS_DP)
				return BoTagUefiUsbHardDisk;
			else					     //<(EIP101213+)
			if(DpPtr->SubType == MSG_MAC_ADDR_DP)
				return BoTagUefiNetWork;
			else
			if( (DpPtr->SubType == MSG_IPv4_DP) || (DpPtr->SubType == MSG_IPv6_DP) )
				return BoTagUefiNetWork;

			continue;
		}

		if(DpPtr->Type == MEDIA_DEVICE_PATH)
		{
			if(!IsUSB && DpPtr->SubType == MEDIA_HARDDRIVE_DP)
				return BoTagUefiHardDisk;
			else
            if(!IsUSB && DpPtr->SubType == MEDIA_CDROM_DP)
                return BoTagUefiCdrom;
			else
            if(IsUSB && DpPtr->SubType == MEDIA_HARDDRIVE_DP)
	    	{
				Status=pBS->LocateDevicePath(&gEfiSimpleFileSystemProtocolGuid, &Dp, &Handle);
				if(!EFI_ERROR(Status))
				{
					BlockHandle = GetPhysicalBlockIoHandle(Handle);
					if( IsUSBkeyByHandle( BlockHandle ) )
						return BoTagUefiUsbKey;
					else
						return BoTagUefiUsbHardDisk;
				}
			}
			else
			if(IsUSB && DpPtr->SubType == MEDIA_CDROM_DP)
				return BoTagUefiUsbCdrom;
		}
	}
										//(EIP96232+)>
  
    if( IsUSB )
    {
		Status=pBS->LocateDevicePath(&gEfiSimpleFileSystemProtocolGuid, &Dp, &Handle);
		if(!EFI_ERROR(Status))
		{
			EFI_GUID gEfiBlockIoProtocolGuid = EFI_BLOCK_IO_PROTOCOL_GUID;
			EFI_BLOCK_IO_PROTOCOL *BlkIo;

			BlockHandle = GetPhysicalBlockIoHandle(Handle);

			if ( !EFI_ERROR( pBS->HandleProtocol(
               						BlockHandle,
                                                        &gEfiBlockIoProtocolGuid,
                                                        &BlkIo)))
			{
				return BoTagUefiUSBFloppy;
			}
		}
	}
										//<(EIP96232+)
    return BoTagUefi;
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************