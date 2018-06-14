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
// $Header: /Alaska/BIN/Core/Modules/PciBus/PciPort.c 22    9/10/12 12:54p Yakovlevs $
//
// $Revision: 22 $
//
// $Date: 9/10/12 12:54p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Modules/PciBus/PciPort.c $
// 
// 22    9/10/12 12:54p Yakovlevs
// [TAG]  		EIP93341
// [Category]  	Improvement
// [Description]  	Preserve PCI DEV/LNK/SLT control register in S3 resume
// path.
// [Files]  		PciBus.c  PciBus.sd PciBus.uni PciSetup.h PciPort.c
// 
// 21    11/09/11 1:55p Yakovlevs
// [TAG]  		EIP71380
// [Category]  	New Feature
// [Description]  	Core support for CSM opt-out feature
// [Files]  		PciBus.c; PciPort.c; PciBus.sd; PciBus.uni; PciSetup.h;
// PciBusSetup.c; 
// 
// 20    4/11/11 10:42a Yakovlevs
// SkipDevice() changed.
// 
// 19    4/05/11 11:26a Yakovlevs
// [TAG]  		EIP 38174; EIP 53475; 
// [Description]  	38174 Generic support to handle PCI OUT OF RESOURDCES
// added. 
// 53475 PCI Express 3.0 support added.
// [Files]  		PciBus.c; PciBus.mak; PciHostBridge.c;  PciBus.h;
// PciHostBridge.c; PciPort.c;
// 
// 17    1/31/11 2:33p Yakovlevs
// [TAG]  		EIP43879
// [Category]  	New Feature
// [Description]  	Added new conditions to have Overwrite Option ROM hook
// called for every device.
// [Files]  		PciPort.c
// 
// 16    1/28/11 3:01p Yakovlevs
// [TAG]  		EIP43879
// [Category]  	New Feature
// [Description]  	Added PciPortOemGetOptRom() OEM Hook to override
// content of the PCI Device Option ROM.
// [Files]  		PciBus.c; PciPort.c; PciPort.h; PciBus.mak; PciBus.sdl
// 
// 15    12/08/10 3:22p Yakovlevs
// Removed Setup Option "Selectable DeEmphasis" since it is HwInit Bit.
// 
// 14    11/11/10 11:58a Yakovlevs
// 
// 13    10/18/10 1:23p Yakovlevs
// Link Training retry and Timeout moved in #if PCI_EXPRESS_SUPPORT scope.
// 
// 12    8/16/10 1:12p Yakovlevs
// Added ASPM Programming cipset hook
// 
// 11    3/01/10 6:12p Yakovlevs
// Pci Express V2.1 Support Added.
// 
// 10    9/22/09 6:02p Yakovlevs
// 1.	Added infrastructure to ELINKs as porting Functions delivered from
// Platform and Chipset files. Now you can port PCI Bus driver without
// modifying Core files
// 
// 9     4/28/09 3:49p Yakovlevs
// Changes related to AmiBoardInfo protocol and Multiplatform support.
// 
// 8     3/23/09 4:57p Yakovlevs
// Added generic support for PCI Express Hot-Plug.
// 
// 7     2/03/09 1:28p Yakovlevs
// 
// 6     1/30/09 12:47p Yakovlevs
// Added Porting functoion to skip PCI Device from enumeration.
// 
// 5     10/01/08 7:10p Yakovlevs
// Updated AMI FUNC HEADER information.
// 
// 4     10/01/08 12:34p Yakovlevs
// 
// 3     9/25/08 12:00p Yakovlevs
// 
// 1     6/05/08 7:14p Yakovlevs
// 
// 1     6/05/08 7:06p Yakovlevs
// 
// 1     6/05/08 6:46p Yakovlevs
// 
// 2     10/23/07 12:59p Felixp
// 
// 1     10/18/07 11:22a Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	PciPort.c
//
// Description:	PCI porting
//
//<AMI_FHDR_END>
//**********************************************************************
#include <EFI.h>
#include <Dxe.h>
#include <Token.h>
#include <PciBus.h>
#include <PciHostBridge.h>
#include <Setup.h>
#include "PciSetup.h"
#include "PciPort.h"

//----------------------------------------------------------------------
//Define Variables == TOKENS to be able to use binary
// See token help for details
//----------------------------------------------------------------------

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:    NbDmiL0ExitLatency;
//
// Description:	Variable to replace NB_DMI_L0_EXIT_LATENCY token.
//
// Notes: const UINT16
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
const UINT16 NbDmiL0ExitLatency = 
#ifdef NB_DMI_L0_EXIT_LATENCY
    NB_DMI_L0_EXIT_LATENCY
#else
    0
#endif
    ;

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:    NbDmiL1ExitLatency;
//
// Description:	Variable to replace NB_DMI_L1_EXIT_LATENCY token.
//
// Notes: const UINT16
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
const UINT16 NbDmiL1ExitLatency = 
#ifdef NB_DMI_L1_EXIT_LATENCY
    NB_DMI_L1_EXIT_LATENCY
#else
    0
#endif
    ;

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:    SbDmiL0ExitLatency;
//
// Description:	Variable to replace SB_DMI_L0_EXIT_LATENCY token.
//
// Notes: const UINT16
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
const UINT16 SbDmiL0ExitLatency = 
#ifdef SB_DMI_L0_EXIT_LATENCY
    SB_DMI_L0_EXIT_LATENCY
#else
    0
#endif
    ;

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:    SbDmiL1ExitLatency;
//
// Description:	Variable to replace SB_DMI_L1_EXIT_LATENCY token.
//
// Notes: const UINT16
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
const UINT16 SbDmiL1ExitLatency = 
#ifdef SB_DMI_L1_EXIT_LATENCY
    SB_DMI_L1_EXIT_LATENCY
#else
    0
#endif
    ;

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:    NbDmiAspmSupport;
//
// Description:	Variable to replace NB_DMI_ASPM_SUPPORT token.
//
// Notes: const UINT16
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
const UINT16 NbDmiAspmSupport = 
#ifdef NB_DMI_ASPM_SUPPORT
    NB_DMI_ASPM_SUPPORT
#else
    0
#endif
    ;

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:    SbDmiAspmSupport;
//
// Description:	Variable to replace SB_DMI_ASPM_SUPPORT token.
//
// Notes: const UINT16
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
const UINT16 SbDmiAspmSupport = 
#ifdef SB_DMI_ASPM_SUPPORT
    SB_DMI_ASPM_SUPPORT
#else
    0
#endif
    ;

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:    SbInternalDelay;
//
// Description:	Variable to replace SB_INTERNAL_DELAY token.
//
// Notes: const UINT16
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
const UINT16 SbInternalDelay = 
#ifdef SB_INTERNAL_DELAY
    SB_INTERNAL_DELAY
#else
    0
#endif
    ;

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:    S3VideoRepost;
//
// Description:	Variable to replace S3_VIDEO_REPOST_SUPPORT token.
//
// Notes: const BOOLEAN
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
const BOOLEAN S3VideoRepost = 
#ifdef S3_VIDEO_REPOST_SUPPORT
	S3_VIDEO_REPOST_SUPPORT
#else
	0
#endif
;

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:    FixedBusAssign;
//
// Description:	Variable to replace PCI_FIXED_BUS_ASSIGNMENT token.
//
// Notes: const BOOLEAN
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
const BOOLEAN FixedBusAssign = 
#ifdef PCI_FIXED_BUS_ASSIGNMENT
	PCI_FIXED_BUS_ASSIGNMENT
#else
	0
#endif
;

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:    ScanFullBusRange;
//
// Description:	Variable to replace PCI_SCAN_FULL_BUS_RANGE token.
//
// Notes:   const BOOLEAN
// This option exists for testing purposes. If System will have additional 
// PCI devices which don't have tree strucuture it might be Pci Device Path 
// conflict
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
const BOOLEAN ScanFullBusRange = 
#ifdef PCI_SCAN_FULL_BUS_RANGE
	PCI_SCAN_FULL_BUS_RANGE
#else
	0
#endif
;

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:    PciExpressSupport;
//
// Description:	Variable to replace PCI_EXPRESS_SUPPORT token.
//
// Notes: const BOOLEAN
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
const BOOLEAN PciExpressSupport = 
#ifdef PCI_EXPRESS_SUPPORT
	PCI_EXPRESS_SUPPORT
#else
	0
#endif
;

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:    HotPlugSupport;
//
// Description:	Variable to replace HOTPLUG_SUPPORT token.
//
// Notes: const BOOLEAN
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
const BOOLEAN HotPlugSupport = 
#ifdef HOTPLUG_SUPPORT
	HOTPLUG_SUPPORT
#else
	0
#endif
;

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:    PciXSupport;
//
// Description:	Variable to replace PCI_X_SUPPORT token.
//
// Notes: const BOOLEAN
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
const BOOLEAN PciXSupport = 
#ifdef PCI_X_SUPPORT
	PCI_X_SUPPORT
#else
	0
#endif
;

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:    SriovSupport;
//
// Description:	Variable to replace SRIOV_SUPPORT token.
//
// Notes: const BOOLEAN
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
const BOOLEAN SriovSupport = 
#ifdef SRIOV_SUPPORT
	SRIOV_SUPPORT
#else
	0
#endif
;

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:    Use4KBar;
//
// Description:	Variable to replace PCI_4K_RESOURCE_ALIGNMENT token.
//
// Notes: const BOOLEAN
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
const BOOLEAN Use4KBar = 
#ifdef PCI_4K_RESOURCE_ALIGNMENT
	PCI_4K_RESOURCE_ALIGNMENT
#else
	0
#endif
;


//----------------------------------------------------------------------
//Define Bord Porting Functions (Hooks) Herte...
//----------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   BrdGetPciSetupData()
//
// Description: Porting function which collects all PCI Bus Driver specific 
// SETUP configuration data and returns it to the PCI Bus Driver.
//
// Input:
//  PCI_SETUP_DATA*   PciSetupData  Pointer to the Pci Bus specific setup data buffer. 
//  
// Output:	Nothing
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID BrdGetPciSetupData(PCI_SETUP_DATA *PciSetupData){
    EFI_GUID 			SetupGuid	= SETUP_GUID;
    EFI_STATUS          Status;
    UINTN               sz=sizeof(SETUP_DATA);
    SETUP_DATA          *SetupData=MallocZ(sizeof(SETUP_DATA));
//-------------------------------------
	//Get Setup Data 
    if ( SetupData==NULL) return;

//Initially ALL Setup Data will be initialized with ZEROs 
//So id Defs

    //Zero out PCI_SETUP_DATA buffer
    pBS->SetMem(PciSetupData, sizeof(PCI_SETUP_DATA), 0);

    //Get global setup variable
    Status=GetEfiVariable(L"Setup",&SetupGuid, NULL, &sz, &SetupData);
	if(EFI_ERROR(Status)){
		//General PCI Settings: [] - default
		//UINT8 PciLatency;				//[32]\ 64 \ 96 \ 128 \ 160 \ 192 \ 224 \ 248
		PciSetupData->PciLatency=32;
#if PCI_X_SUPPORT
		//UINT8 PciXLatency;			// 32 \[64]\ 96 \ 128 \ 160 \ 192 \ 224 \ 248
		PciSetupData->PciXLatency=64;
#endif
#if PCI_EXPRESS_SUPPORT
		//PCI Express Device Settings: [] - default
		//UINT8	RelaxedOrdering; 		//[Disable]\ Enable
		//UINT8	ExtTagField; 			//[Disable]\ Enable
		//UINT8	NoSnoop;				// Disable \[Enable]
		PciSetupData->NoSnoop=1;

		//UINT8	MaxPayload;				//[Auto]\ 128 \ 256 \ 512 \ 1024 \ 2048 \ 4096 (in bytes)
		PciSetupData->MaxPayload=55;
		//UINT8 MaxReadRequest;			//[Auto]\ 128 \ 256 \ 512 \ 1024 \ 2048 \ 4096 (in bytes)
		PciSetupData->MaxReadRequest=55;
		//PCI Express Link settings: [] - default
		//UINT8 AspmMode; 				//[Disable]\ Auto \ Forse L0
		//UINT8 ExtendedSynch;			//[Disable]\ Enable

        //Fill in Default Values... (buffer was initialized with ZEROs)
        //UINT8   LnkTrRetry;             //Disable\ 2 \ 3 \[5]
        PciSetupData->LnkTrRetry=5;
        //UINT16  LnkTrTimout;            //<1.[2]..100> (Microseconds uS)
        PciSetupData->LnkTrTimeout=0x10;
        //UINT8   LnkDisable;             //[Keep ON == 0] / Disable ==1  
        PciSetupData->S3PciExpressScripts = 0;
#endif
        //UINTN S3ResumeVideoRepost     //[Disable]\ Enable
        
        //UINT8   Above4gDecode;          //[Disable]\ Enable 
	    //General PCI Settings: [] - default
        //UINT8   VgaPallete;             //[Disable]\ Enable 
        //UINT8   PerrEnable;             //[Disable]\ Enable 
        //UINT8   SerrEnable;             //[Disable]\ Enable 
#if AMI_HOTPLUG_INIT_SUPPORT 
        //INT8   HotPlug;                 // Disable \[Enable]
        PciSetupData->HotPlug=1;             
        //UINT8   BusPadd;                // Disable \[1]\ 2 \ 3 \ 4 \ 5
        PciSetupData->BusPadd=1;          //    0       1    2     3    4   
        //UINT8   IoPadd;                 // Disable \[ 4K]\ 8K \ 16K \ 32K  
        PciSetupData->IoPadd=0x1000;      //    0       1    2     3    4     5     6     7
        //UINT8   Mmio32Padd;             // Disable \  1M \ 4M \  8M \[16M]\ 32M \ 64M \128M  
        PciSetupData->Mmio32Padd=0x1000000; 
        //UINT8   Mmio32PfPadd;           // Disable \  1M \ 4M \  8M \[16M]\ 32M \ 64M \128M  
        PciSetupData->Mmio32PfPadd=0x1000000;
        //UINT8   Mmio64Padd;             //[Disable]\  1M \ 4M \  8M \ 16M \ 32M \ 64M \ 128M \ 256M \ 512M \ 1G
        //UINT8   Mmio64PfPadd;           //[Disable]\  1M \ 4M \  8M \ 16M \ 32M \ 64M \ 128M \ 256M \ 512M \ 1G
#endif

#if PCI_EXPRESS_GEN2_SUPPORT
        //Gen2 Device Settings

        //UINT8   ComplTimeOut;           //[Disable]\ Default \ 50 - 100 us \ 1ms - 10ms \ 16...
     
        //UINT8   AriFwd;                 //[Disable]\ Enable
        //UINT8   AtomOpReq;              //[Disable]\ Enable
        //UINT8   AtomOpEgressBlk;        //[Disable]\ Enable
        //UINT8   IDOReq;                 //[Disable]\ Enable
        //UINT8   IDOCompl;               //[Disable]\ Enable
        //UINT8   LtrReport;              //[Disable]\ Enable
        //UINT8   E2ETlpPrBlk;            //[Disable]\ Enable

        //Gen2 Link Settings
        //UINT8   LnkSpeed;               //[Auto]\ 5.0 GHz \ 2.5 GHz
        PciSetupData->LnkSpeed=55;
        //UINT8   DeEmphasis;             //[Disable]\ Enable
        //UINT8   ClockPm;                //[Disable]\ Enable
        //UINT8   ComplSos;               //[Disable]\ Enable

        //UINT8   HwAutoWidth;            //[Enable]\ Disable    
        //PciSetupData->HwAutoWidth=0;
        //UINT8   HwAutoSpeed;            //[Enable]\ Disable
        //PciSetupData->HwAutoSpeed=0;
#endif        

	} else {
		//General PCI Settings: [] - default
		PciSetupData->PciLatency = SetupData->PciLatency;
#if PCI_X_SUPPORT
		PciSetupData->PciXLatency = SetupData->PciXLatency;
#endif
#if PCI_EXPRESS_SUPPORT
		//PCI Express Device Settings: [] - default
		PciSetupData->RelaxedOrdering = SetupData->RelaxedOrdering;
		PciSetupData->ExtTagField = SetupData->ExtTagField;
		PciSetupData->NoSnoop = SetupData->NoSnoop;
		PciSetupData->MaxPayload = SetupData->MaxPayload;
		PciSetupData->MaxReadRequest = SetupData->MaxReadRequest;
		//PCI Express Link settings: [] - default
		PciSetupData->AspmMode = SetupData->AspmMode;
		PciSetupData->ExtendedSynch = SetupData->ExtendedSynch;

        //Fill in Default Values... (buffer was initialized with ZEROs)
        //UINT8   LnkTrRetry;             //[Disable]\ 2 \ 3 \ 5
        PciSetupData->LnkTrRetry=SetupData->LnkTrRetry;
        PciSetupData->LnkTrTimeout=SetupData->LnkTrTimeout;
        PciSetupData->LnkDisable=SetupData->LnkDisable; //[Keep ON == 0] / Disable ==1  
        //UINT8 S3PciExpressScripts       //[Disable]\ Enable
        PciSetupData->S3PciExpressScripts = SetupData->S3PciExpressScripts;

#endif
#if S3_VIDEO_REPOST_SUPPORT
        PciSetupData->S3ResumeVideoRepost = SetupData->S3ResumeVideoRepost;
#endif
	    //General2 PCI Settings: [] - default
        PciSetupData->VgaPallete = SetupData->VgaPallete;
        PciSetupData->PerrEnable = SetupData->PerrEnable;
        PciSetupData->SerrEnable = SetupData->SerrEnable;
#if ABOVE_4G_PCI_DECODE
        PciSetupData->Above4gDecode = SetupData->Above4gDecode;
#endif

#if AMI_HOTPLUG_INIT_SUPPORT 
        //INT8   HotPlug;                 // Disable \[Enable]
        PciSetupData->HotPlug=SetupData->HotPlugEnable;
        //if HP Enabled...
        if(PciSetupData->HotPlug){             
            PciSetupData->BusPadd=SetupData->BusPadd;
            PciSetupData->IoPadd=SetupData->IoPadd*0x400; //Stored in units of KB
            PciSetupData->Mmio32Padd=SetupData->Mmio32Padd*0x100000; 
            PciSetupData->Mmio32PfPadd=SetupData->Mmio32PfPadd*0x100000; 
            if(PciSetupData->Above4gDecode == 1){
                PciSetupData->Mmio64Padd=SetupData->Mmio64Padd*0x100000; 
                PciSetupData->Mmio64PfPadd=SetupData->Mmio64PfPadd*0x100000; 
            } else {
                PciSetupData->Mmio64Padd=0; 
                PciSetupData->Mmio64PfPadd=0; 
            }
        }
#endif

#if PCI_EXPRESS_GEN2_SUPPORT
        //Gen2 Device Settings
        //UINT8   ComplTimeOut;           //[Disable]\ Default \ 50 - 100 us \ 1ms - 10ms \ 16...
        PciSetupData->ComplTimeOut=SetupData->ComplTimeOut;
        //UINT8   AriFwd;                 //[Disable]\ Enable
        PciSetupData->AriFwd=SetupData->AriFwd;
        //UINT8   AtomOpReq;              //[Disable]\ Enable
        PciSetupData->AtomOpReq=SetupData->AtomOpReq;
        //UINT8   AtomOpEgressBlk;        //[Disable]\ Enable
        PciSetupData->AtomOpEgressBlk=SetupData->AtomOpEgressBlk;
        //UINT8   IDOReq;                 //[Disable]\ Enable
        PciSetupData->IDOReq=SetupData->IDOReq;
        //UINT8   IDOCompl;               //[Disable]\ Enable
        PciSetupData->IDOCompl=SetupData->IDOCompl;
        //UINT8   LtrReport;              //[Disable]\ Enable
        PciSetupData->LtrReport=SetupData->LtrReport;
        //UINT8   E2ETlpPrBlk;            //[Disable]\ Enable
        PciSetupData->E2ETlpPrBlk=SetupData->E2ETlpPrBlk;

        //Gen2 Link Settings
        //UINT8   LnkSpeed;               //[Auto]\ 5.0 GHz \ 2.5 GHz
        PciSetupData->LnkSpeed=SetupData->LnkSpeed;
        //UINT8   ComplSos;               //[Disable]\ Enable
        PciSetupData->ComplSos=SetupData->ComplSos;
        //UINT8   ClockPm;               //[Disable]\ Enable
        PciSetupData->ClockPm=SetupData->ClockPm;
        //UINT8   HwAutoWidth;            //[Enable]\ Disable    
        PciSetupData->HwAutoWidth=SetupData->HwAutoWidth;
        //UINT8   HwAutoSpeed;            //[Enable]\ Disable
        PciSetupData->HwAutoSpeed=SetupData->HwAutoSpeed;
#endif        
    }
    pBS->FreePool(SetupData);    

}

//To avoid compilation error define STRUCT delivered trough eLink as extern function.
#define OEM_PCI_DEVICE_CALLBACK( VendorId, DeviceId, Callback ) Callback
extern OEM_PCI_PROGRAM_DEVICE_FUNCTION  OEM_PCI_PROGRAM_DEVICE_CALLBACK_LIST EndOfList;
extern OEM_PCI_PROGRAM_DEVICE_FUNCTION  OEM_PCI_SKIP_DEVICE_CALLBACK_LIST EndOfList;
extern OEM_PCI_PROGRAM_DEVICE_FUNCTION  OEM_PCI_DEVICE_SET_ASPM_CALLBACK_LIST EndOfList;
extern OEM_PCI_PROGRAM_DEVICE_FUNCTION  OEM_PCI_DEVICE_SET_LNK_SPEED_CALLBACK_LIST EndOfList;
extern OEM_PCI_PROGRAM_DEVICE_FUNCTION  OEM_PCI_DEVICE_ATTRIBUTE_CALLBACK_LIST EndOfList;
extern OEM_PCI_PROGRAM_DEVICE_FUNCTION  OEM_PCI_DEVICE_OUT_OF_RESOURCES_CALLBACK_LIST EndOfList;
extern OEM_PCI_PROGRAM_DEVICE_FUNCTION  OEM_PCI_DEVICE_GET_OPT_ROM_CALLBACK_LIST EndOfList;
#undef OEM_PCI_DEVICE_CALLBACK


#define OEM_PCI_DEVICE_CALLBACK( VendorId, DeviceId, Callback ) { VendorId, DeviceId, &Callback }
OEM_PCI_DEVICE_PROGRAM_CALLBACK OemSkipPciDevice[] =
    { OEM_PCI_SKIP_DEVICE_CALLBACK_LIST { 0, 0, NULL } };


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   PciPortSkipThisDevice()
//
// Description: Porting function which collects all Pci Specific configuration 
// data return it to the PCI Bus Driver.
//
// Input:
//  PCI_DEV_INFO    *Device   Pointer to the Pci Bus Driver Private data buffer. 
//  
// Output:	 EFI_STATUS     
//  EFI_SUCCESS     - SKIP this device, do not touch PCI Command register.
//  EFI_UNSUPPORTED - DON'T SKIP this device do complete enumeration as usual.
//  
// NOTE:
//  If device decodes or requires some resources to function properely, 
//  allocating and and reporting this reaources to GCD is a total responsibility 
//  of this hook. If this FUNCTION RETURNS EFI_SUCCESS PciBus Driver assumes that 
//  RESOURCES ARE ALLOCATED AND REPORTED TO THE GCD DXE SERVICES.
//  Reporting resources to GCD Services is important to avoid same resource range
//  been allocated twice.
//  If device you want to skip is PCI2PCI or PCI2CRD bus bridge 1 bus will be allocated 
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PciPortSkipThisDevice(PCI_DEV_INFO *Device){
    EFI_STATUS      Status=EFI_UNSUPPORTED;
    OEM_PCI_DEVICE_PROGRAM_CALLBACK *List = OemSkipPciDevice;
    EFI_STATUS      retStatus=EFI_UNSUPPORTED;
//-------------------
    while(List->Callback)
    {
        OEM_PCI_PROGRAM_DEVICE_FUNCTION *CallBack=(OEM_PCI_PROGRAM_DEVICE_FUNCTION*)List->Callback;
    //--------------------------------
        if((List->VendorId == Device->DevVenId.VenId && List->DeviceId == Device->DevVenId.DevId)||
            (List->VendorId == 0 && List->DeviceId == 0))
        {
        	PCI_TRACE((TRACE_PCI, "PciBus: OEM Skip Device Callback @ B%X|D%X|F%X VID=0x%X; DID=0x%X;", 
	        Device->Address.Addr.Bus,Device->Address.Addr.Device,Device->Address.Addr.Function, 
            Device->DevVenId.VenId, Device->DevVenId.DevId));

            Status = CallBack(Device);
        	PCI_TRACE((TRACE_PCI, " %r,\n", Status));
            if( EFI_ERROR(Status) && (Status!=EFI_UNSUPPORTED))return Status;
            else if(Status==EFI_SUCCESS)retStatus=Status;
        }
        //if(List->VendorId == 0 && List->DeviceId == 0) break;
        List++;
    }
    
    return retStatus;
}


#define OEM_PCI_DEVICE_CALLBACK( VendorId, DeviceId, Callback ) { VendorId, DeviceId, &Callback }
OEM_PCI_DEVICE_PROGRAM_CALLBACK OemProgramPciDevice[] =
    { OEM_PCI_PROGRAM_DEVICE_CALLBACK_LIST { 0, 0, NULL } };

EFI_STATUS PciPortOemProgDevice(PCI_DEV_INFO *Device){
    EFI_STATUS                      Status=EFI_SUCCESS;
    OEM_PCI_DEVICE_PROGRAM_CALLBACK *List = OemProgramPciDevice;
//-------------------
    while(List->Callback)
    {
        OEM_PCI_PROGRAM_DEVICE_FUNCTION *CallBack=(OEM_PCI_PROGRAM_DEVICE_FUNCTION*)List->Callback;
    //--------------------------------
        if((List->VendorId == Device->DevVenId.VenId && List->DeviceId == Device->DevVenId.DevId)||
            (List->VendorId == 0 && List->DeviceId == 0))
        {
        	PCI_TRACE((TRACE_PCI, "PciBus: OEM Programm Device Callback @ B%X|D%X|F%X VID=0x%X; DID=0x%X;", 
	        Device->Address.Addr.Bus,Device->Address.Addr.Device,Device->Address.Addr.Function, 
            Device->DevVenId.VenId, Device->DevVenId.DevId));

            Status = CallBack(Device);
        	PCI_TRACE((TRACE_PCI, " %r,\n", Status));
            if( EFI_ERROR(Status) )
                return Status;
        }
        List++;
    }

    return Status;
}

//To avoid compilation error define Srtuct delivered trough eLink as extern function.
#define OEM_PCI_DEVICE_CALLBACK( VendorId, DeviceId, Callback ) { VendorId, DeviceId, &Callback }
OEM_PCI_DEVICE_PROGRAM_CALLBACK OemSetAspmPciDevice[] =
    { OEM_PCI_DEVICE_SET_ASPM_CALLBACK_LIST { 0, 0, NULL } };


//Suppose to be called 2 times for UpStream and DownStream component of a LINK.
EFI_STATUS PciPortOemSetAspm(PCI_DEV_INFO *Device, VOID *AspmMode){
    EFI_STATUS                          Status=EFI_SUCCESS;
    OEM_PCI_DEVICE_PROGRAM_CALLBACK     *List = OemSetAspmPciDevice;
//-------------------
    while(List->Callback)
    {
        OEM_PCI_DEVICE_SET_ASPM_FUNCTION *CallBack =(OEM_PCI_DEVICE_SET_ASPM_FUNCTION*)List->Callback; 
    //--------------------------------

        if((List->VendorId == Device->DevVenId.VenId && List->DeviceId == Device->DevVenId.DevId)||
            (List->VendorId == 0 && List->DeviceId == 0))
        {
        	PCI_TRACE((TRACE_PCI, "PciBus: OEM Device Set ASPM Callback @ B%X|D%X|F%X VID=0x%X; DID=0x%X;", 
	        Device->Address.Addr.Bus,Device->Address.Addr.Device,Device->Address.Addr.Function, 
            Device->DevVenId.VenId, Device->DevVenId.DevId));

            Status = CallBack(Device, AspmMode);
        	PCI_TRACE((TRACE_PCI, " %r,\n", Status));
            if( EFI_ERROR(Status))
                return Status;
        }
        List++;
    }

    return Status;
}

//To avoid compilation error define Srtuct delivered trough eLink as extern function.
#define OEM_PCI_DEVICE_CALLBACK( VendorId, DeviceId, Callback ) { VendorId, DeviceId, &Callback }
OEM_PCI_DEVICE_PROGRAM_CALLBACK OemSetLnkSpeedPciDevice[] =
    { OEM_PCI_DEVICE_SET_LNK_SPEED_CALLBACK_LIST { 0, 0, NULL } };

//Suppose to be called 2 times for UpStream and DownStream component of a LINK.
EFI_STATUS PciPortOemSetLnkSpeed(PCI_DEV_INFO *Device, UINT8 *LnkSpeed, UINT8 SuppSpeeds){
    EFI_STATUS                          Status=EFI_SUCCESS;
    OEM_PCI_DEVICE_PROGRAM_CALLBACK     *List = OemSetLnkSpeedPciDevice;
//-------------------
    while(List->Callback)
    {
        OEM_PCI_DEVICE_SET_LNK_SPEED_FUNCTION *CallBack =(OEM_PCI_DEVICE_SET_LNK_SPEED_FUNCTION*)List->Callback; 
    //--------------------------------

        if((List->VendorId == Device->DevVenId.VenId && List->DeviceId == Device->DevVenId.DevId)||
            (List->VendorId == 0 && List->DeviceId == 0))
        {
        	PCI_TRACE((TRACE_PCI, "PciBus: OEM Device Set LNK SPEED Callback @ B%X|D%X|F%X VID=0x%X; DID=0x%X;", 
	        Device->Address.Addr.Bus,Device->Address.Addr.Device,Device->Address.Addr.Function, 
            Device->DevVenId.VenId, Device->DevVenId.DevId));

            Status = CallBack(Device, LnkSpeed, SuppSpeeds);
        	PCI_TRACE((TRACE_PCI, " %r,\n", Status));
            if( EFI_ERROR(Status))
                return Status;
        }
        List++;
    }

    return Status;
}

//To avoid compilation error define Srtuct delivered trough eLink as extern function.
#define OEM_PCI_DEVICE_CALLBACK( VendorId, DeviceId, Callback ) { VendorId, DeviceId, &Callback }
OEM_PCI_DEVICE_PROGRAM_CALLBACK OemGetOptRomPciDevice[] =
    { OEM_PCI_DEVICE_GET_OPT_ROM_CALLBACK_LIST { 0, 0, NULL } };



EFI_STATUS PciPortOemGetOptRom(PCI_DEV_INFO *Device, VOID **OptRom, UINT64 *OptRomSize){
    EFI_STATUS                          Status=EFI_SUCCESS;
    OEM_PCI_DEVICE_PROGRAM_CALLBACK     *List = OemGetOptRomPciDevice;
//-------------------
    while(List->Callback)
    {
        OEM_PCI_DEVICE_GET_OPT_ROM_FUNCTION *CallBack =(OEM_PCI_DEVICE_GET_OPT_ROM_FUNCTION*)List->Callback; 
    //--------------------------------

         if((List->VendorId == Device->DevVenId.VenId && List->DeviceId == Device->DevVenId.DevId)||
            (List->VendorId == 0 && List->DeviceId == 0))
        {
        	PCI_TRACE((TRACE_PCI, "PciBus: OEM Device Get Opt ROM Callback @ B%X|D%X|F%X VID=0x%X; DID=0x%X;", 
	        Device->Address.Addr.Bus,Device->Address.Addr.Device,Device->Address.Addr.Function, 
            Device->DevVenId.VenId, Device->DevVenId.DevId));

            Status = CallBack(Device, OptRom, OptRomSize);
        	PCI_TRACE((TRACE_PCI, " %r,\n", Status));
            if( EFI_ERROR(Status))
                return Status;
        }
        List++;
    }

    return Status;
}



//To avoid compilation error define Srtuct delivered trough eLink as extern function.
#define OEM_PCI_DEVICE_CALLBACK( VendorId, DeviceId, Callback ) { VendorId, DeviceId, &Callback }
OEM_PCI_DEVICE_PROGRAM_CALLBACK OemPciOutOfResourcesRemoveDevice[] =
    { OEM_PCI_DEVICE_OUT_OF_RESOURCES_CALLBACK_LIST { 0, 0, NULL } };

EFI_STATUS PciPortOutOfResourcesRemoveDevice(PCI_DEV_INFO *Device, UINTN Count, UINTN LowResType){
    EFI_STATUS                          Status=EFI_UNSUPPORTED;
    OEM_PCI_DEVICE_PROGRAM_CALLBACK     *List = OemPciOutOfResourcesRemoveDevice;
//-----------------------------    

    //must be only one + TERMIONATOR.
    while(List->Callback)
    {
        OEM_PCI_DEVICE_OUT_OF_RESOURCES_FUNCTION *CallBack =(OEM_PCI_DEVICE_OUT_OF_RESOURCES_FUNCTION*)List->Callback; 
    //-----------------------------

        PCI_TRACE((TRACE_PCI, "\nPciBus: OEM PCI OUT OF RESOURCES Callback @ B%X|D%X|F%X VID=0x%X; DID=0x%X;", 
        Device->Address.Addr.Bus,Device->Address.Addr.Device,Device->Address.Addr.Function, 
        Device->DevVenId.VenId, Device->DevVenId.DevId));

        Status = CallBack(Device, Count, LowResType);
        PCI_TRACE((TRACE_PCI, " %r,\n\n", Status));

        List++;

    }
    return Status;
}


//To avoid compilation error define Srtuct delivered trough eLink as extern function.
#define OEM_PCI_DEVICE_CALLBACK( VendorId, DeviceId, Callback ) { VendorId, DeviceId, &Callback }
OEM_PCI_DEVICE_PROGRAM_CALLBACK OemAttributesPciDevice[] =
    { OEM_PCI_DEVICE_ATTRIBUTE_CALLBACK_LIST { 0, 0, NULL } };



EFI_STATUS PciPortOemAttributes(PCI_DEV_INFO *Device, UINT64 *Attr, UINT64 Capab, BOOLEAN Set){
    EFI_STATUS                          Status=EFI_SUCCESS;
    OEM_PCI_DEVICE_PROGRAM_CALLBACK     *List = OemAttributesPciDevice;
//-------------------
    while(List->Callback)
    {
        OEM_PCI_DEVICE_ATTRIBUTE_FUNCTION *CallBack =(OEM_PCI_DEVICE_ATTRIBUTE_FUNCTION*)List->Callback; 
    //--------------------------------

        if((List->VendorId == Device->DevVenId.VenId && List->DeviceId == Device->DevVenId.DevId)||
            (List->VendorId == 0 && List->DeviceId == 0))
        {
        	PCI_TRACE((TRACE_PCI, "PciBus: OEM Device Attributes Callback @ B%X|D%X|F%X VID=0x%X; DID=0x%X;", 
	        Device->Address.Addr.Bus,Device->Address.Addr.Device,Device->Address.Addr.Function, 
            Device->DevVenId.VenId, Device->DevVenId.DevId));

            Status = CallBack(Device, Attr, Capab, Set);
        	PCI_TRACE((TRACE_PCI, " %r,\n", Status));
            if( EFI_ERROR(Status))
                return Status;
        }
        List++;
    }

    return Status;
}


EFI_STATUS PciPortSetOemPadding(VOID *HpcData, VOID *HpcLocationData, UINT64 PciAddress){
    EFI_STATUS  Status=EFI_SUCCESS;
//ADD VARIABLES HERE..

//-----------------

//PORTING START//PORTING START//PORTING START//PORTING START//PORTING START
//ADD PORTING CODE HERE...
/*
    //VOID *HpcData, VOID *HpcLocationData could be typecasted to 
    // (PCI_HPC_DATA*)HpcData and (HPC_LOCATION_DATA*)HpcLocationData.
    //Update Padding requirements if needed HERE.
    //PCI_HPC_DATA *HpcData has pointer to the PCI_HOST_BRG_DATA* HpcData->Owner 
    //And number of HPC in subsystem of this HOST - HpcData->HpcLocCount.
    //HPC_LOCATION_DATA *HpcLocationData has information about Location and Paddin for this 
    //Particular HPC. If system has more than ONE HPC checking needs to be done to 
    //detect correct if PASSED the data from correct HPC.
    

    //Do something like this.
    
    HpcLocationData->Padding[ptBus]=10; 

*/
//PORTING END//PORTING END//PORTING END//PORTING END//PORTING END//PORTING END
//DO NOT WRITE BELOW THIS LINE FOR THIS PORTING FUNCTION

    return Status;
}


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
