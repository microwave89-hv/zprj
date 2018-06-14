//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2007, American Megatrends, Inc.         **
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
// $Header: /Alaska/BIN/Core/Modules/PciBus/PciSetup.h 6     9/10/12 12:54p Yakovlevs $
//
// $Revision: 6 $
//
// $Date: 9/10/12 12:54p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Modules/PciBus/PciSetup.h $
// 
// 6     9/10/12 12:54p Yakovlevs
// [TAG]  		EIP93341
// [Category]  	Improvement
// [Description]  	Preserve PCI DEV/LNK/SLT control register in S3 resume
// path.
// [Files]  		PciBus.c  PciBus.sd PciBus.uni PciSetup.h PciPort.c
// 
// 5     11/09/11 1:55p Yakovlevs
// [TAG]  		EIP71380
// [Category]  	New Feature
// [Description]  	Core support for CSM opt-out feature
// [Files]  		PciBus.c; PciPort.c; PciBus.sd; PciBus.uni; PciSetup.h;
// PciBusSetup.c; 
// 
// 4     12/08/10 3:22p Yakovlevs
// Removed Setup Option "Selectable DeEmphasis" since it is HwInit Bit.
// 
// 3     3/01/10 6:12p Yakovlevs
// Pci Express V2.1 Support Added.
// 
// 2     3/23/09 4:57p Yakovlevs
// Added generic support for PCI Express Hot-Plug.
// 
// 1     9/25/08 11:35a Yakovlevs
// 
// 1     6/05/08 7:14p Yakovlevs
// 
// 1     6/05/08 7:06p Yakovlevs
// 
// 1     6/05/08 6:46p Yakovlevs
// 
// 1     3/18/07 5:23p Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	PciSetup.h
//
// Description:	
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __PCI_SETUP__H__
#define __PCI_SETUP__H__
#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(push)
//---------------------------------------------------------------------------------
//Structure Defines PCI Releated data stored in GLOBAL SETUP_DATA NVRAM variable
typedef struct _PCI_SETUP_DATA {
	//General PCI Settings: [] - default
	UINT8   PciLatency;				//[32]\ 64 \ 96 \ 128 \ 160 \ 192 \ 224 \ 248
	UINT8   PciXLatency;			// 32 \[64]\ 96 \ 128 \ 160 \ 192 \ 224 \ 248
	//PCI Express Device Settings: [] - default
	UINT8	RelaxedOrdering; 		//[Disable]\ Enable 
	UINT8	ExtTagField; 			//[Disable]\ Enable 
	UINT8	NoSnoop;				// Disable \[Enable]
	UINT8	MaxPayload;				//[Auto]\ 128 \ 256 \ 512 \ 1024 \ 2048 \ 4096 (in bytes)
	UINT8   MaxReadRequest;			//[Auto]\ 128 \ 256 \ 512 \ 1024 \ 2048 \ 4096 (in bytes)
	//PCI Express Link settings: [] - default
	UINT8   AspmMode; 				//[Disable]\ Auto \ Force L0
	UINT8   ExtendedSynch;			//[Disable]\ Enable 
    //Acpi related questions
    UINT8   S3ResumeVideoRepost;
//new stuff added in PCI BUS 2.2.0
    UINT8   Above4gDecode;          //[Disable]\ Enable 
	//General PCI Settings: [] - default
    UINT8   VgaPallete;             //[Disable]\ Enable 
    UINT8   PerrEnable;             //[Disable]\ Enable 
    UINT8   SerrEnable;             //[Disable]\ Enable 
    //Hotlpug Related Settings visible if PCI_HOTPLUG_SUPPORT == 1 && PCI_EXPRESS_SUPPORT == 1
    UINT8   HotPlug;                // Disable \[Enable]
    UINT8   BusPadd;                // Disable \[1]\ 2 \ 3 \ 4 \ 5
    UINT64  IoPadd;                 // Disable \[ 4K]\ 8K \ 16K \ 32K  
    UINT64  Mmio32Padd;             // Disable \  1M \ 4M \  8M \[16M]\ 32M \ 64M \ 128M  
    UINT64  Mmio32PfPadd;           // Disable \  1M \ 4M \  8M \[16M]\ 32M \ 64M \ 128M  
    UINT64  Mmio64Padd;             //[Disable]\  1M \ 4M \  8M \ 16M \ 32M \ 64M \ 128M \ 256M \ 512M \ 1G
    UINT64  Mmio64PfPadd;           //[Disable]\  1M \ 4M \  8M \ 16M \ 32M \ 64M \ 128M \ 256M \ 512M \ 1G

    UINT8   LnkTrRetry;             //[Disable]\ 2 \ 3 \ 5
    UINT16  LnkTrTimeout;           //[1...1000] (Microseconds uS) 
    UINT8   LnkDisable;             //[Keep ON == 0] / Disable ==1  

    UINT8   S3PciExpressScripts;    //[Disable]\ Enable

//PCI_EXPRESS_GEN2_SUPPORT
    //Gen2 Device Settings
    UINT8   ComplTimeOut;           //[Disable]\ Default \ 50 - 100 us \ 1ms - 10ms \ 16...
    UINT8   AriFwd;                 //[Disable]\ Enable
    UINT8   AtomOpReq;              //[Disable]\ Enable
    UINT8   AtomOpEgressBlk;        //[Disable]\ Enable
    UINT8   IDOReq;                 //[Disable]\ Enable
    UINT8   IDOCompl;               //[Disable]\ Enable
    UINT8   LtrReport;              //[Disable]\ Enable
    UINT8   E2ETlpPrBlk;            //[Disable]\ Enable

    //Gen2 Link Settings
    UINT8   LnkSpeed;               //[Auto]\ 5.0 GHz \ 2.5 GHz
    UINT8   ClockPm;                //[Disable]\ Enable
    UINT8   ComplSos;               //[Disable]\ Enable
    UINT8   HwAutoWidth;            //[Enable]\ Disable    //LNK_CNT_REG #1
    UINT8   HwAutoSpeed;            //[Enable]\ Disable

} PCI_SETUP_DATA;

#pragma pack(pop)

//Function Prototypes
VOID BrdGetPciSetupData(PCI_SETUP_DATA *PciSetupData);

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2007, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
