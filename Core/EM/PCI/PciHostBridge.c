//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
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
// $Header: /Alaska/SOURCE/Core/Modules/PciBus/PciHostBridge.c 48    9/10/12 12:49p Yakovlevs $
//
// $Revision: 48 $
//
// $Date: 9/10/12 12:49p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Core/Modules/PciBus/PciHostBridge.c $
// 
// 48    9/10/12 12:49p Yakovlevs
// Minor changes fix for multi host system
// 
// 47    7/17/12 1:48p Yakovlevs
// 
// 45    7/16/12 3:10p Yakovlevs
// [TAG]  		EIP90378 
// [Category]  	Improvement
// [Description]  	Pci Root bridge driver should be able to access MMIO
// above 4G
// [Files]  		PciHostBridge.c
// 
// 44    6/26/12 6:24p Yakovlevs
// [TAG]  		EIP90378 
// [Category]  	Improvement
// [Description]  	Pci Root bridge driver should be able to access MMIO
// above 4G
// [Files]  		PciHostBridge.c
// 
// 43    5/22/12 4:50p Yakovlevs
// Removing wrong comment
// 
// 42    5/01/12 5:05p Yakovlevs
// [TAG]  		EIP84986
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Yellow mark issue in windows device manager on
// PCIe slots if only 2 CPU for potter city platform.
// [RootCause]  	For multy root system where root socets partialy
// populated SDL data interfered with 
// Actual Hardware configuration.
// [Solution]  	Allow control flow keep going when certain 
// ERROR_STATUS received.
// [Files]  		PciBus.c; PciHostBridge.c
// 
// 41    2/27/12 4:47p Yakovlevs
// 
// 40    11/23/11 11:08a Yakovlevs
// [TAG]  		EIP76109
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	VIA VX900 / VX11 CopyMem issue 
// [RootCause]  	When Src and Dst buffers overlaps 
// size of copy operation was determined incorrectly.
// [Solution]  	Added additional cases with negative increments
// [Files]  		PciHostBridge.c
// 
// 39    11/10/11 12:26p Yakovlevs
// [TAG]  		EIP72122 
// [Category]  	Improvement
// [Description]  	If system uses UEFI GOP driver, then BIOS does not
// report legacy VGA resources to ACPI.
// 
// [Files]  		PciHostBridge.c
// 
// 38    8/30/11 2:27p Yakovlevs
// [TAG]  		EIP68120
// [Category]  	Bug Fix
// [Symptom]  	When new PCIe card be plugged, It hangs at 0x94 before
// adjusting new memory ceiling to nvram with CORE4651.
// [RootCause]  	AdjustMmioOverlap() was not called if builtin allocation
// function returned  EFI_ERROR.
// [Solution]  	Reorganize code to call this function before returning
// ERROR Status.
// [Files]  		PciHostBridge.c
// 
// 37    8/02/11 4:13p Yakovlevs
// [TAG]  		EIP66216
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Hotplug resource padding not working for ROOT bridges other
// than 0
// [RootCause]  	Hot plug slots was incorrectly associated alvays withthe
// RootBridge #0
// [Solution]  	Changed algorithm to beter distinguish between Root
// Bridges.  Added debug messagers to monitor HPC_LOCATION_DATA.
// [Files]  		PciBus.c; PciHostBridge.c. 
// 
// 36    7/08/11 5:00p Yakovlevs
// [TAG]  		EIP64414
// [Category]  	Improvement
// [Description]  	During PCIOUTOF RESOURCE Condition,resource freeing is
// not done
// [Files]  		PciHostBridge.c
// 
// 35    6/28/11 5:29p Yakovlevs
// [TAG]  		EIP 60123 
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	Resource padding is not functional for PCIe hot-plug.
// [RootCause]  	In hot plug function was missed changes in BusXlat
// Structure.
// [Solution]  	Xlat header gets incremented based on AMI_BOARD_INFO
// driver wersion.
// [Files]  		PciHostBridge.c
// 
// 34    5/04/11 6:15p Yakovlevs
// Fixed potential issue with EFI_PCI_ATTRIBUTE_DUAL_ADDRESS_CYCLE
// attribute some drivers may set.
// 
// 33    4/05/11 11:40a Yakovlevs
// [TAG]  		EIP 38174
// [Category]  	New Feature
// [Description]  	Generic support to handle PCI OUT OF RESOURDCES added. 
// [Files]  		PciBus.c; PciHostBridge.c;
// 
// 32    1/20/11 3:07p Yakovlevs
// [TAG]  		EIP45278
// [Category]  	Improvement
// [Description]  	Added PCI_MMIO_RES_TOP_ALLIGN token to control Resource
// allocation algorithm selection.
// [Files]  		PciBus.c; PciHostBridge.c; PciBus.sdl.
// 
// 31    1/13/11 1:30p Yakovlevs
// 
// 30    1/13/11 1:28p Yakovlevs
// [TAG]  		EIP45278
// [Category]  	Improvement
// [Description]  	Changed default resource allocation algorithm to work
// more efficiently. 
// [Files]  		PciBus.c; PciHostBridge.c
// 
// 28    8/23/10 12:29p Yakovlevs
// Fixed issue with incorrect settings COMPATIBILITY ATTRIBUTES was
// missing Legacy VGA_ATTRIBUTES.
// 
// 27    8/16/10 1:07p Yakovlevs
// Updated ClaimMmioResources to use MMIO resources as-is if AllocType is
// set to EfiGcdAllocateAddress. For this chipset, each root bridge is
// programmed with base and limit values for 32bit and 64bit MMIO. The
// root bridge will only decode addresses within these ranges. For this
// reason, the Base and Limit values passed to the PCI Bus driver should
// be used as-is and not modified.
// 
// 26    3/01/10 6:18p Yakovlevs
// Generic Multi-ROOT Support Added.
// 
// 25    9/22/09 6:10p Yakovlevs
// 3.	Generic support for multiple root bridges resources reporting to
// ACPI DSDT Root Bridge Object (EIP 23548 Support MMIO allocation above
// 4GB, if devices are capable)
// 
// 24    8/21/09 4:25p Yakovlevs
// Added Print out Message in DEBUG_MODE with PCI BUS Driver Version.
// Added Initialization of ImageHandle field in Host Bridge and Root
// Bridge Structures. New PciHostBridge.h required.
// 
// 23    4/28/09 5:50p Yakovlevs
// Ami Board Info Protocol moved into separate Core\AmiBoardInfo
// subcomponent.
// 
// 22    3/27/09 11:48a Yakovlevs
// 
// 21    3/23/09 2:27p Yakovlevs
// ADDED support for PCI Root HPC INit Protocol generation based on AMI
// SDL output.
// 
// 20    1/30/09 1:01p Yakovlevs
// Changed gPciHost to gPciRbHost to avoid name collision gPCiHost
// variable name been differently used in PciBus.c 
// 
// 19    11/21/08 7:01p Yakovlevs
// 
// 18    11/14/08 3:34p Yakovlevs
// Removed EFI_DEADLOOP() used for debug
// 
// 17    11/14/08 1:28p Yakovlevs
// Implemented AMI Board Info Protocol which has *.inc OUTPUTs generated 
// by AMISDL tool. To keep it in one place and Make PciBus Driver use it.
// 
// 16    11/03/08 2:35p Yakovlevs
// 
// 15    11/03/08 2:33p Yakovlevs
// Fixed EIP 17068:  AdjustMmioOverlap() has to be called each boot.
// 
// 14    10/01/08 7:12p Yakovlevs
// Updated AMI FUNC HEADER information
// 
// 13    9/24/08 6:08p Yakovlevs
// New features added. Multy host support using VeB wizard. No initial
// porting required.
// 
// 12    4/29/08 6:56p Yakovlevs
// Added mechanism to suppress PCI BUs driver debug messages(Latest
// PciBus.sdl and PciBus.h required).
// 
// 11    2/19/08 3:38p Felixp
// 
// 10    2/13/08 1:02p Yakovlevs
// Fixed issue with incorrect usage of GCD AllocateXX services.
// 
// 9     10/23/07 5:30p Felixp
// VC8 warnings fixed
// 
// 8     8/07/07 2:45p Felixp
// Additional Status Codes added
// 
// 7     4/19/07 12:59p Felixp
// Added Chipset specific call to set RB Attributes
// 
// 5     4/17/07 11:55a Yakovlevs
// 
// 4     4/17/07 11:19a Yakovlevs
// 
// 3     4/17/07 11:18a Yakovlevs
// Added Chipset specific call to set RB Attributes
// 
// 2     4/13/07 6:23p Yakovlevs
// make use of LibGetDxeSvcTbl() instead of manualy getting the DXE Svc
// Tbl pointer.
// 
// 1     3/12/07 12:02p Yakovlevs
// 
// 9     12/28/06 7:20p Yakovlevs
// 
// 8     12/19/06 12:07p Yakovlevs
// PciRb->Map; Unmap implementation fixes
// 
// 7     10/24/06 12:18p Yakovlevs
// Removed EFI_MEMORY_RUNTIME attribute from PCI BUS resource request.
// 
// 6     9/20/06 4:47p Felixp
// x64 warnings fixed
// 
// 5     6/01/06 12:17p Yakovlevs
// Handling of memceil logic added.
// 
// 4     5/23/06 12:59a Felixp
// Bug fix in HbResAllocStartBusEnumeration - invalid error condition
// check
// 
// 3     5/19/06 10:51p Felixp
// Device Path code updated to use NEXT_NODE/NODE_LENGTH/SET_NODE_LENGTH
// macros to remove direct access to the Length field
// 
// 2     4/07/06 2:33p Felixp
// Bug fix in resource allocation (AllocateResources): Attributes for
// Prefetchable memory changed from WB to WT
// 
// 1     4/03/06 5:32p Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	PciHostBridge.c
//
// Description:	AMI's Native Root Bridge Protocol Implementation
//
//<AMI_FHDR_END>
//**********************************************************************

#include <Token.h>
#include <AmiDxeLib.h>
#include <PciHostBridge.h>
#include <Protocol\DevicePath.h>
#include <AmiCspLib.h>
#include "PciPort.h"
#include "PciSetup.h"

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:		gAmiBoardProtocol
//
// Description:	Ami Board Info Protocol Instance.
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
AMI_BOARD_INFO_PROTOCOL *gAmiBoardInfoProtocol=NULL;



//**********************************************************************
//Global Vars and Constants been used 
//**********************************************************************

//GUIDs
EFI_GUID	gHbResAllocProtocolGuid=EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL_GUID;
EFI_GUID	gRbIoProtocolGuid=EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_GUID;
EFI_GUID    gDevPathProtocolGuid=EFI_DEVICE_PATH_PROTOCOL_GUID;
EFI_GUID	gDeviceIoProtocolGuid=DEVICE_IO_PROTOCOL;
EFI_GUID    gAmiBoardInfoGuid=AMI_BOARD_INFO_PROTOCOL_GUID;

#if AMI_HOTPLUG_INIT_SUPPORT == 1 
EFI_GUID	gHotPlugInitProtocolGuid=EFI_PCI_HOT_PLUG_INIT_PROTOCOL_GUID;
#endif



//**********************************************************************
//Variables

T_ITEM_LIST                 gRootBusDb={0,0,NULL};

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:		gPciHost
//
// Description:	Array of PCI Host Bridge Data Sructures.
//              Initial data point for PCI Subsystem.
//
// Notes: See PCI_HOST_BRG_DATA. Number of elements in gPciHost[] array
//        defined by NB_NUMBER_OF_HOST_BRG in NB.sdl
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
PCI_HOST_BRG_DATA	gPciRbHost[NB_NUMBER_OF_HOST_BRG];

//TODO//TODO //TODO //TODO //TODO  
//Change this to reference VeB output EIP 24469
//TEMP Hardcoding of ASL RB Device Object NAME
#if AMI_BOARD_VER_COMBINED < 100
CHAR8   *RbAslName[]={"PCI0","PCFF"};
#endif

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:		*gPciSetupData; PciSetupDataBuffer
//
// Description:	Global Setup Variable to get the setup settings pointer.
//
// Notes: PCI_SETUP_DATA
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
PCI_SETUP_DATA      gRbSetupData;

UINT64		TmpBot[raMaxRes]={0,0,0,0};
UINT64		TmpTop[raMaxRes]={0,0,0,0};

//**********************************************************************
//Function Prototypes needed forward declaration
//**********************************************************************
EFI_STATUS ConvertMemoryMap(EFI_HANDLE	ImgHandle, EFI_HANDLE	CntrHandle OPTIONAL);
EFI_STATUS CreateRootBusData();
EFI_STATUS HpcInitProtocol(PCI_HOST_BRG_DATA *HostBrg);
BOOLEAN    IsPowerOfTwo(UINT64 Value);
VOID       RbReadyToBoot(IN EFI_EVENT Event,	IN VOID	*Context);


//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//PCI Root Bridge Driver Entry Point
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	InitializePCIHostBridge()
//
// Description:	This function is the entry point for PCI Root Bridge Driver. 
// Since PCI Root Bridge Driver follows EFI 1.1 driver model in it's entry 
// point it will initialize some global data and install
// EFI_DRIVER_BINDING_PROTOCOL. 
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
// Notes: 
//  Entry Points are used to locate or install protocol interfaces and
// 	notification events. 
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS InitializePCIHostBridge(IN EFI_HANDLE ImageHandle,IN EFI_SYSTEM_TABLE *SystemTable)
{
	EFI_STATUS					Status=EFI_SUCCESS;
	UINTN						i,j,n;
	PCI_HOST_BRG_DATA			*hb;
	PCI_ROOT_BRG_DATA			*rb;
    EFI_EVENT                   ReadyToBootEvent=NULL;
//-----------------------------------------

	//Init Lib globals...
	InitAmiLib(ImageHandle,SystemTable);
    PROGRESS_CODE(DXE_NB_HB_INIT);

    //Print PCI Bus Driver Version
    PCI_TRACE((TRACE_PCI,"\nPciRootBrg: Initializing... PCI Driver Version %d.%d.%d\n", PCI_BUS_MAJOR_VER, PCI_BUS_MINOR_VER, PCI_BUS_REVISION));

	Status = pBS->LocateProtocol(&gAmiBoardInfoGuid, NULL,(VOID**)&gAmiBoardInfoProtocol);
	if(EFI_ERROR(Status)){
        PCI_TRACE((TRACE_PCI,"PciRootBrg: Fail to Locate AMI_BOARD_INFO_PROTOCOL Status=%r\n",Status));
        ASSERT_EFI_ERROR(Status);
        return Status;
    }

    //Zerouot Privete HOST BRG data structure and Setup Data Buffer
    pBS->SetMem(&gPciRbHost[0], sizeof(gPciRbHost), 0);
    pBS->SetMem(&gRbSetupData, sizeof(PCI_SETUP_DATA), 0);

    //Get Setup Data it has some Root Brg related features
    BrdGetPciSetupData(&gRbSetupData);    

	//Update GCD resource map with static Chipset Specific Resources decoded.
	Status=ConvertMemoryMap(ImageHandle,NULL);
	ASSERT_EFI_ERROR(Status);
	if(EFI_ERROR(Status)) return Status;

    //Parse BusXlatTable extracting ROOT BRIDGE data from there.
    Status=CreateRootBusData();
	ASSERT_EFI_ERROR(Status);
	if(EFI_ERROR(Status)) return Status;
    
    //try to map available roots from gRootBusDb.Items to 
    //the corresponded HOST abstraction
    //each HOST has to have a separate instance of ResourceAllocation Protocol
    //each ROOT will have a separate instance of RootBridgeIo Protocol. 
    //This "FOR" loop will construcr HOST/ROOT bridge infrastructure and will
    //try to map each root collected in call CreateRootBusData() to it's correcponded HOST
    //using HbCspMapRootBrgToHost() CSP hook. For MULTY-HOST systems this hook must be ported
    for(i=0;i<gRootBusDb.ItemCount; i++){
        PCI_BUS_XLAT_HDR    *roothdr=(PCI_BUS_XLAT_HDR*)gRootBusDb.Items[i];
        PCI_BUS_XLAT_HDR    *nexthdr=NULL;
        ASLR_QWORD_ASD      *busrd;
        UINT64              aa=0, ra=0;
        //---------------------------------------    
        //fill Allocation Atributes Property.
        //Based on Token values of COMBINE_MEM_PMEM and ABOVE_4G_PCI_DECODE 
        if(COMBINE_MEM_PMEM) aa |= EFI_PCI_HOST_BRIDGE_COMBINE_MEM_PMEM; 
        if(ABOVE_4G_PCI_DECODE){
            aa |= EFI_PCI_HOST_BRIDGE_MEM64_DECODE;
            ra |= EFI_PCI_ATTRIBUTE_DUAL_ADDRESS_CYCLE;           
        }

        if(roothdr->BusBuild ==0) ra |= (PCI_ROOT_COMPATIBILITY_ATTRIBUTES | PCI_ROOT_VGA_ATTRIBUTES);
         
        //Call Chipset Specific function to map this ROOT to HOST.
        //And override Allocation attributes based on TOKEN VALUES.
        //Have no clue how to do it automatically though..........
        j=HbCspMapRootBrgToHost(roothdr, &aa, &ra);
        
        //If we got NUMBER 
        if(j>=NB_NUMBER_OF_HOST_BRG) {
            PCI_TRACE((TRACE_PCI,"PciRootBrg: Root2Host mapping [HOST=%d >= MAX_HOSTs=%d; ROOT %X|%X \n ",
                                        j, NB_NUMBER_OF_HOST_BRG, roothdr->BusBuild, roothdr->BusRun ));
            ASSERT_EFI_ERROR(EFI_INVALID_PARAMETER);
            return EFI_INVALID_PARAMETER;            
        }

		hb=&gPciRbHost[j];
        
        //Check if setup allows us to decode PCI Space above 4G
        if( gRbSetupData.Above4gDecode == 0 ) aa &= (~(EFI_PCI_HOST_BRIDGE_MEM64_DECODE));
        
        hb->AllocAttrib=aa;

        //Allocate memory for Root Bridge Data structure;
		rb=MallocZ(sizeof(PCI_ROOT_BRG_DATA));
        ASSERT(rb);
		if(!rb)return EFI_OUT_OF_RESOURCES;

        //Save BusXlatEntry for this Root
        rb->BusXlatEntry=roothdr;

#if AMI_BOARD_VER_COMBINED >= 100
        //Change this to reference VeB output EIP 24469
        rb->RbAslName=(CHAR8*)((UINT8*)(roothdr+1)+2); //Including DEV_FN 1Byte + terminator 1 byte.
#endif

        //Save returned Attributes
        rb->Supports=ra;

        //Get Next root header to determine current root Build Bus range
        if(i<gRootBusDb.ItemCount-1) nexthdr=(PCI_BUS_XLAT_HDR*)gRootBusDb.Items[i+1];
        
        //Get memory for Bus Resource Descriptor        
        busrd=MallocZ(sizeof(ASLR_QWORD_ASD));
        //fill Bus Resource descriptor fields
        busrd->Hdr.HDR=0x8A;
        busrd->Hdr.Length=0x2B;
        busrd->Type=ASLRV_SPC_TYPE_BUS;
        busrd->_GRA=1;
        busrd->_MIN=roothdr->BusBuild;
        //if this is last ROOT xlat entry make it MAX Bus Number;
        if(nexthdr == NULL) busrd->_MAX = 0xFF;
        else busrd->_MAX=nexthdr->BusBuild-1;
        busrd->_LEN = busrd->_MAX - busrd->_MIN + 1;

		Status=AppendItemLst((T_ITEM_LIST*)&hb->RbInitCnt,rb);			
		ASSERT_EFI_ERROR(Status);	
		if(EFI_ERROR(Status)) return Status;
        
		Status=AppendItemLst((T_ITEM_LIST*)&rb->ResInitCnt,busrd);			
		ASSERT_EFI_ERROR(Status);	
		if(EFI_ERROR(Status)) return Status;
    }

	//Init Number of nitial Host Bridge Structures;
	for(i=0,n=0; i<NB_NUMBER_OF_HOST_BRG; i++){
        hb=&gPciRbHost[i];
        hb->ImageHandle=ImageHandle;
		//Init Host Bridge Private Data instance
		//here goes Allocation Arrtibutes
		//hb->AllocAttrib=gHbAllocAttribTbl[i];		

		//Init Prtocol Functions
		hb->ResAllocProtocol.NotifyPhase=HbResAllocNotifyPhase;
		hb->ResAllocProtocol.GetNextRootBridge=HbResAllocGetNextRootBridge;
		hb->ResAllocProtocol.GetAllocAttributes=HbResAllocGetAllocAttributes; 
	  	hb->ResAllocProtocol.StartBusEnumeration=HbResAllocStartBusEnumeration;
		hb->ResAllocProtocol.SetBusNumbers=HbResAllocSetBusNumbers;
		hb->ResAllocProtocol.SubmitResources=HbResAllocSubmitResources;          
		hb->ResAllocProtocol.GetProposedResources=HbResAllocGetProposedResources;
		hb->ResAllocProtocol.PreprocessController=HbResAllocPreprocessController;
		
		hb->AllocPhase=-1; 
		//hb->PciSegment=HbCspGetPicSegment();

		//Install HB res Alloc Protocol on this HOST BRG
		Status=pBS->InstallMultipleProtocolInterfaces(
			&hb->HbHandle,		//it was NULL so it going to be a new handle				
			&gHbResAllocProtocolGuid, &hb->ResAllocProtocol,//RbIo Protocol GUID - I/F pare
			NULL);									//terminator
		

		//Init Root Bridge objects of Current Host Bridge 
		//hb->RbInitCnt=gRbCountTbl[i]+1;
		for(j=0; j<hb->RootBridgeCount; j++,n++){
			ACPI_HID_DEVICE_PATH	*rbdp;
			//-----------------------------------
            //Reinit rb pointer for this loop
            rb=hb->RootBridges[j];
            rb->ImageHandle=ImageHandle;            

#if AMI_BOARD_VER_COMBINED < 100
        //Change this to reference VeB output EIP 24469
           rb->RbAslName=RbAslName[j];
#endif

			//Init Root Bridge Private Data instance		
			rbdp=Malloc(sizeof(ACPI_HID_DEVICE_PATH)+sizeof(EFI_DEVICE_PATH_PROTOCOL));			
			ASSERT(rbdp);
			if(!rbdp)return EFI_OUT_OF_RESOURCES;
			
			rb->DevPath=&rbdp->Header;	
			//generate RB device path 
			rbdp->Header.Type=ACPI_DEVICE_PATH;
			rbdp->Header.SubType=ACPI_DP;
			SET_NODE_LENGTH(&rbdp->Header,ACPI_DEVICE_PATH_LENGTH);
			rbdp->HID=EISA_PNP_ID(0x0A03);	
			rbdp->UID=(UINT32)j;
			
			rbdp++;
			rbdp->Header.Type=END_DEVICE_PATH;
			rbdp->Header.SubType=END_ENTIRE_SUBTYPE;
			SET_NODE_LENGTH(&rbdp->Header,END_DEVICE_PATH_LENGTH);
			
			//FillOut Capabilities
			//rb->Supports=gRbSupportsTbl[n];
            //if Host bridge has capability to decode 64 bit address space we 
			//will add EFI_PCI_IO_ATTRIBUTE_DUAL_ADDRESS_CYCLE Capability bit
			//to the RootBridge Supported features Set. 
            if(hb->AllocAttrib & EFI_PCI_HOST_BRIDGE_MEM64_DECODE)
				rb->Supports |= EFI_PCI_IO_ATTRIBUTE_DUAL_ADDRESS_CYCLE;

			//Fill out Protocol Interface for RB Protocol Member functions
			rb->RbIoProtocol.ParentHandle=hb->HbHandle;
			rb->RbIoProtocol.PollMem=PollMem;
			rb->RbIoProtocol.PollIo=PollIo;
			rb->RbIoProtocol.Mem.Read=PciMemRead;
			rb->RbIoProtocol.Mem.Write=PciMemWrite;
			rb->RbIoProtocol.Io.Read=PciIoRead;
			rb->RbIoProtocol.Io.Write=PciIoWrite;
			rb->RbIoProtocol.Pci.Read=PciRead;
			rb->RbIoProtocol.Pci.Write=PciWrite;
			rb->RbIoProtocol.CopyMem=CopyMem;
			rb->RbIoProtocol.Map=Map;
			rb->RbIoProtocol.Unmap=Unmap;
			rb->RbIoProtocol.AllocateBuffer=AllocateBuffer;
			rb->RbIoProtocol.FreeBuffer=FreeBuffer;
			rb->RbIoProtocol.Flush=Flush;
			rb->RbIoProtocol.GetAttributes=GetAttributes;
			rb->RbIoProtocol.SetAttributes=SetAttributes;
			rb->RbIoProtocol.Configuration=Configuration;
			rb->RbIoProtocol.SegmentNumber=(UINT32)HbCspGetPciSegment(i,j);
			rb->Owner=hb;
			
    		rb->DevIoProtocol=ConstructDeviceIoProtocol(&rb->RbIoProtocol, rb->DevPath);	
			ASSERT(rb->DevIoProtocol);
			if(!rb->DevIoProtocol) return EFI_OUT_OF_RESOURCES;		
	
			Status=pBS->InstallMultipleProtocolInterfaces(
				&rb->RbHandle,		//it was NULL so it going to be a new handle				
				&gRbIoProtocolGuid, &rb->RbIoProtocol, 	//RbIo Protocol GUID - I/F pare
				&gDevPathProtocolGuid, rb->DevPath, 		//DevPath Protocol GUID - I/F pare
				&gDeviceIoProtocolGuid, rb->DevIoProtocol,
				NULL);									//terminator
			ASSERT_EFI_ERROR(Status);
			if(EFI_ERROR(Status)) return Status;
		} //rb loop
        //Here we must initialize and install PciHotPlugControllerInit Protocol 
        //based on VeB provided OUTPUT, IRQ_ASM_APIC output registy can do that.

#if AMI_HOTPLUG_INIT_SUPPORT
        if(gRbSetupData.HotPlug == 1){
            Status = HpcInitProtocol(hb);    
            PCI_TRACE((TRACE_PCI,"PciRootBrg: HpcInitProtocol() call returned %r\n", Status));

            if(!EFI_ERROR(Status)){
    		    // Install HB res Alloc Protocol on this HOST BRG
		        Status=pBS->InstallMultipleProtocolInterfaces(
			        &hb->HbHandle,		//it is NOT NULL now 
			        &gHotPlugInitProtocolGuid, &hb->HpcData->RootHotplugProtocol,
    			    NULL);									//terminator
                PCI_TRACE((TRACE_PCI,"PciRootBrg: Install PCI RHPC Init Protocol call - returned %r\n", Status));
            } else {
                if (Status!=EFI_NOT_FOUND) ASSERT_EFI_ERROR(Status);
                
            }
            
        }//if Setup allows (gRbSetupData.HotPlug==1)...
#endif

	} //hb loop
	
    Status = CreateReadyToBootEvent(TPL_CALLBACK,
                                    RbReadyToBoot,
                                    NULL,
                                    &ReadyToBootEvent);
    PCI_TRACE((TRACE_PCI,"PciRootBrg: Create ReadyToBootEvent - returned %r\n", Status));
	ASSERT_EFI_ERROR(Status);
    
	//Call Chipset Hook aftert we have initialized Pci Host bridge.
	Status=HbCspBasicChipsetInit(&gPciRbHost[0]);
	ASSERT_EFI_ERROR(Status);

	return Status;
}


//**********************************************************************
//HelperFunctions
//**********************************************************************
#if AMI_HOTPLUG_INIT_SUPPORT == 1

BOOLEAN HpcCheckHpBus(PCI_HOST_BRG_DATA *HostBrg, UINT8 HpSlotBus,
                      OUT PCI_ROOT_BRG_DATA **RootBrg, OUT PCI_BUS_XLAT_HDR **HlatHdr){
    UINTN               i;
    PCI_ROOT_BRG_DATA   *rb=NULL;
    PCI_DEV_FUN         *rootdf=NULL;
    UINT8               maxbus;
//---------------
    if(RootBrg==NULL || HlatHdr == NULL) return FALSE;

    PCI_TRACE((TRACE_PCI,"PciHp: Locating RB for Slot @ bus 0x%X ... ", HpSlotBus));

    for(i=0; i<HostBrg->RootBridgeCount; i++){
        PCI_BUS_XLAT_HDR    *xhdr=gAmiBoardInfoProtocol->BusXlatTable;
        PCI_DEV_FUN         *devf = (PCI_DEV_FUN*)(xhdr+1);
    //-----------------------------

        //Init Data...
        rb=HostBrg->RootBridges[i];
               
        //See how many buses this root decodes...
        if(i < HostBrg->RootBridgeCount-1) maxbus=HostBrg->RootBridges[i+1]->BusXlatEntry->BusBuild-1;
        else maxbus=0xFF;

        //Check if it HpSlotBus falls in this RB bus range. 
        if( (HpSlotBus > maxbus) || (rb->BusXlatEntry->BusBuild > HpSlotBus) )continue;        


        rootdf=(PCI_DEV_FUN*)(rb->BusXlatEntry+1);
        
        while((UINTN)devf<=(UINTN)(gAmiBoardInfoProtocol->BusXlatTable)+gAmiBoardInfoProtocol->BusXlatLength){
            //Terminator found...
            if(devf->DEV_FUN == 0xFF){
                //Check if BusBuild # of Xlat entry matches the HpSlotBus 
                if(xhdr->BusBuild == HpSlotBus){
                    PCI_DEV_FUN *rdf=(PCI_DEV_FUN*)(xhdr+1); //Root DevFunc is the first node after header.
                //-----------------
                    if(rootdf->DEV_FUN == rdf->DEV_FUN ){
                        *RootBrg=rb;
                        *HlatHdr=xhdr;
                        PCI_TRACE((TRACE_PCI,"FOUND! Rb #%d; maxbus=0x%X minbus=0x%X\n ",i, maxbus, rb->BusXlatEntry->BusBuild));
                        return TRUE;
                    }
                }
                //Advance to the next record in BusXlatTbl.
#if AMI_BOARD_VER_COMBINED >= 100
            //Now we have AslName[5] following devf data
                xhdr=(PCI_BUS_XLAT_HDR*)(devf+1+5);
#else
                xhdr=(PCI_BUS_XLAT_HDR*)(devf+1);
#endif
                devf = (PCI_DEV_FUN*)(xhdr+1);
                continue;
            } else {
                devf++;
            }
        }
        //Search through all the ROOTs..
    } //for   
    
    //we can't find
    *RootBrg=NULL;
    *HlatHdr=NULL;
    
    PCI_TRACE((TRACE_PCI,"NOT FOUND! Rb #%d; maxbus=0x%X minbus=0x%X\n",i, maxbus, rb->BusXlatEntry->BusBuild));
    return FALSE;

}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	HpcFindHpSlots
//
// Description:	
//  This function find  
//  information and initialize an instance of PCI Root Hotplug Controller 
//  Initialization Protocol.
//
// Input:		PCI_HOST_BRG_DATA   *HostBrg - Pointer on Private Data 
//              structure for which PCI Hot Plug Init Protocol going to 
//              be initialized
//
// Output:		EFI_SUCCESS is OK
//              EFI_NOT_FOUND no Hotplug slots where found. 
//
// Notes:		CHIPSET AND/OR BOARD PORTING NEEDED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS HpcFindSlots(PCI_HOST_BRG_DATA *HostBrg){
    EFI_STATUS  Status=EFI_NOT_FOUND;
    UINTN       i;
    PCI_IRQ_PIC_ROUTE   *picr=NULL;
    PCI_IRQ_APIC_ROUTE  *apicr=NULL;
    PCI_DEVICE_PATH     pcidp;
    UINTN               hpscnt=0;
//-------------------------
    //Check The conditions and validity of a call...using PIC HP Slots Information...
    hpscnt=gAmiBoardInfoProtocol->HpSltPicLength/sizeof(PCI_IRQ_PIC_ROUTE);

    PCI_TRACE((TRACE_PCI,"PciHp: Found 0x%X HP Slots; processing...:\n", hpscnt));

    if(hpscnt != (gAmiBoardInfoProtocol->HpSltApicLength/sizeof(PCI_IRQ_APIC_ROUTE)) ){
        PCI_TRACE((TRACE_PCI,"PciHp: APIC HP Slot count != PIC HPC Slot Count: exiting - EFI_INVALID_PARAMETER\n"));        
        return EFI_INVALID_PARAMETER;
    }
    

    //init PCI Device Path variable we will not touch header data there..
	pcidp.Header.SubType=HW_PCI_DP;
	pcidp.Header.Type=HARDWARE_DEVICE_PATH;
	SET_NODE_LENGTH(&pcidp.Header,HW_PCI_DEVICE_PATH_LENGTH);

    //Now look for Hotplug slots we know it must be there...
    for(i=0,picr=gAmiBoardInfoProtocol->HpSltTablePic; i<hpscnt; i++, picr++){
        PCI_ROOT_BRG_DATA   *hprb=NULL; 
        PCI_BUS_XLAT_HDR    *hpsh=NULL;        
    //--------------------------

        //Our helper function identified the Slot and ROOT where it belongs.
        //We are assuming PCI Express Hotplug. So the Bridge is the HPC and Bus It produces is HPB.
        if( HpcCheckHpBus(HostBrg, picr->PciBusNumber, &hprb, &hpsh)){
            HPC_LOCATION_DATA           *locdata=NULL;
            EFI_DEVICE_PATH_PROTOCOL    *tmpdp=NULL;
            PCI_DEV_FUN                 *df;    
        //----------------
            PCI_TRACE((TRACE_PCI,"PciHp: Found HP Slot #0x%X (%d dec) at BusBuild #0x%X\n",picr->SlotNum, picr->SlotNum, picr->PciBusNumber));
            
            //Generate the device path for the HPController\HPBus we have pci device path reserved there.
            tmpdp=DPCopy(hprb->DevPath);
            if(tmpdp==NULL) {
                Status=EFI_OUT_OF_RESOURCES;
                ASSERT_EFI_ERROR(Status);
                return Status;
            }

            df=(PCI_DEV_FUN*)(hpsh+1);
            df+=1; //One node is for ROOT bridge

            while (df->DEV_FUN != 0xFF){
                VOID    *oldp=tmpdp;
            //---------
                pcidp.Function=df->Fun;
                pcidp.Device=df->Dev;
                tmpdp=DPAddNode(tmpdp, (EFI_DEVICE_PATH_PROTOCOL*)&pcidp);

                if(tmpdp==NULL) {
                    Status=EFI_OUT_OF_RESOURCES;
                    ASSERT_EFI_ERROR(Status);
                    return Status;
                }
                df+=1;
                if(oldp!=NULL)pBS->FreePool(oldp);
            }
            //Here DevicePath Is Ready.

            //Store data returned by HpcCheckHpBus in private structures.
            locdata=MallocZ(sizeof(HPC_LOCATION_DATA));
            if(locdata==NULL) {
                Status = EFI_OUT_OF_RESOURCES;
                ASSERT_EFI_ERROR(Status);
                return Status;
            } else Status=EFI_SUCCESS;
            
            locdata->Owner=hprb;
            locdata->SlotHdr=hpsh;

            //For SHPC and PCIExpress Hotplug HPC==HPB = tmpdp.
            //make a copy of generated DP into hpclocation buffer
            locdata->HpcLocation.HpcDevicePath=DPCopy(tmpdp);            
            locdata->HpcLocation.HpbDevicePath=DPCopy(tmpdp);            
            
            pBS->FreePool(tmpdp);

            if(locdata->HpcLocation.HpbDevicePath==NULL || locdata->HpcLocation.HpcDevicePath==NULL) {
                Status = EFI_OUT_OF_RESOURCES;
                ASSERT_EFI_ERROR(Status);
                return Status;
            }

            //fill out Padding Information for this slot...
            locdata->Padding[ptBus]     = gRbSetupData.BusPadd;
            locdata->Padding[ptIo ]     = gRbSetupData.IoPadd;
            locdata->Padding[ptMmio32]  = gRbSetupData.Mmio32Padd;
            locdata->Padding[ptMmio32pf]= gRbSetupData.Mmio32PfPadd;
            locdata->Padding[ptMmio64]  = gRbSetupData.Mmio64Padd;
            locdata->Padding[ptMmio64pf]= gRbSetupData.Mmio64PfPadd;
            
            Status=AppendItemLst((T_ITEM_LIST*)&HostBrg->HpcData->HpclInitCnt, locdata);
            ASSERT_EFI_ERROR(Status);
            if(EFI_ERROR(Status)) break;
        }
        if((UINTN)picr>((UINTN)gAmiBoardInfoProtocol->HpSltTablePic+gAmiBoardInfoProtocol->HpSltPicLength)) break;
    }
    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	HpcInitGetRootHpcList
//
// Description:	GetRootHpcList() Function of the PCI Root Hotplug Controller 
// Initialization Protocol. See PI 1.1 Spec or details
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS HpcInitGetRootHpcList(IN EFI_PCI_HOT_PLUG_INIT_PROTOCOL      *This,
                                 OUT UINTN                              *HpcCount,
                                 OUT EFI_HPC_LOCATION                   **HpcList)
{
    EFI_STATUS          Status=EFI_SUCCESS;
    UINTN               i;
    EFI_HPC_LOCATION    *hpcl=NULL, *lp=NULL;
    PCI_HPC_DATA        *hpcdata=NULL;

//------------------------
    hpcdata=(PCI_HPC_DATA*)This;
    
    PCI_TRACE((TRACE_PCI,"PciHb: Get Location - HpcLocCount=%d\n", hpcdata->HpcLocCount));
    PCI_TRACE((TRACE_PCI,"-------------------------------------------------\n"));
    
    //Allocate Buffer for HPC List
    hpcl=MallocZ(sizeof(EFI_HPC_LOCATION) * hpcdata->HpcLocCount);

    //Check conditions 
    if(hpcl==NULL){
        Status=EFI_OUT_OF_RESOURCES;
        ASSERT_EFI_ERROR(Status);
        return Status;
    }
    
    //Fill data in RHPC List Data...
    for(i=0, lp=hpcl; i<hpcdata->HpcLocCount; i++, lp++){
        HPC_LOCATION_DATA   *locdata=hpcdata->HpcLocData[i];
    //----------------
        MemCpy(lp, &locdata->HpcLocation, sizeof(EFI_HPC_LOCATION));
        PCI_TRACE((TRACE_PCI,"  lp->HpcDP=[HID(%X)UID(%X)]; lp->HpbDP[HID(%X)UID(%X)]\n",
            ((ACPI_HID_DEVICE_PATH*)lp->HpcDevicePath)->HID,((ACPI_HID_DEVICE_PATH*)lp->HpcDevicePath)->UID,
            ((ACPI_HID_DEVICE_PATH*)lp->HpbDevicePath)->HID,((ACPI_HID_DEVICE_PATH*)lp->HpbDevicePath)->UID));
    }
    PCI_TRACE((TRACE_PCI,"-------------------------------------------------\n"));
    
    *HpcCount=hpcdata->HpcLocCount;
    *HpcList=hpcl;
 
    return Status;    
}


EFI_STATUS FindHpcLocData(  IN EFI_DEVICE_PATH_PROTOCOL *HpcDevicePath, 
                            IN PCI_HPC_DATA             *HpcData,
                            OUT HPC_LOCATION_DATA       **HpcLocData )
{
    UINTN               i;
    HPC_LOCATION_DATA   *locdata;
//------------------

    for(i=0; i< HpcData->HpcLocCount; i++){
        locdata=HpcData->HpcLocData[i];
        if(DPCmp(HpcDevicePath, locdata->HpcLocation.HpcDevicePath) == 0 ){
            *HpcLocData=locdata;
            return EFI_SUCCESS;
        }
    }

    PCI_TRACE((TRACE_PCI,"PciHp: Can't find matching HPC for DevicePath @ 0x%X \n",HpcDevicePath));

    return EFI_NOT_FOUND;

}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	HpcInitInitializeRootHpc
//
// Description:	InitializeRootHpc() Function of the PCI Root Hotplug Controller 
// Initialization Protocol. See PI 1.1 Spec or details
//
// NOTE:
//  This function call will be used to overwrite default resource Padding settings.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS HpcInitInitializeRootHpc(IN EFI_PCI_HOT_PLUG_INIT_PROTOCOL       *This,
                                    IN  EFI_DEVICE_PATH_PROTOCOL            *HpcDevicePath,
                                    IN  UINT64                              HpcPciAddress,
                                    IN  EFI_EVENT                         	Event, OPTIONAL
                                    OUT EFI_HPC_STATE                    	*HpcState)
{
    EFI_STATUS          Status=EFI_SUCCESS;
    PCI_HPC_DATA        *hpcdata=NULL;
    HPC_LOCATION_DATA   *locdata;
//------------------------
    hpcdata=(PCI_HPC_DATA*)This;

    //Find which exactly HPC PCI BUS Driver means..
    Status=FindHpcLocData(HpcDevicePath, hpcdata,&locdata);
    if(EFI_ERROR(Status)) return Status;
    
    //Call Porting function to overwrite HP Padding Settings if needed;
    PciPortSetOemPadding(hpcdata, locdata, HpcPciAddress);

    *HpcState=(EFI_HPC_STATE_INITIALIZED|EFI_HPC_STATE_ENABLED);

    return EFI_SUCCESS;
}

VOID HpcFillDescriptor(ASLR_QWORD_ASD *Descriptor, HP_PADD_RES_TYPE PaddType, UINT64  Length){

//---------------------

    Descriptor->Hdr.HDR=0x8A;
    Descriptor->Hdr.Length=0x2B;
    
    Descriptor->_LEN=Length;
    if(PaddType==ptBus)Descriptor->_MAX=1;
    else{
        if(IsPowerOfTwo(Length))Descriptor->_MAX=Length-1;
        else Descriptor->_MAX=1;
    }

    Descriptor->GFlags._MIF=1;
    Descriptor->GFlags._MAF=1;
    Descriptor->TFlags.TFLAGS=0;            

    switch(PaddType){
        case ptBus:
            Descriptor->Type=ASLRV_SPC_TYPE_BUS;
            break;
        case ptIo:
            Descriptor->Type=ASLRV_SPC_TYPE_IO;
            break;
        case ptMmio32:
            Descriptor->Type=ASLRV_SPC_TYPE_MEM;
            Descriptor->_GRA=32;
            break;
        case ptMmio32pf:
            Descriptor->Type=ASLRV_SPC_TYPE_MEM;
            Descriptor->TFlags.TFLAGS=0x06;            
            Descriptor->_GRA=32;
            break;
        case ptMmio64:   //4
            Descriptor->Type=ASLRV_SPC_TYPE_MEM;
            Descriptor->_GRA=64;
            break;
        case ptMmio64pf:  //5
            Descriptor->Type=ASLRV_SPC_TYPE_MEM;
            Descriptor->TFlags.TFLAGS=0x06;            
            Descriptor->_GRA=64;
            break;
    } 

}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	HpcInitInitializeRootHpc
//
// Description:	InitializeRootHpc() Function of the PCI Root Hotplug Controller 
// Initialization Protocol. See PI 1.1 Spec or details
//
// NOTE:
//  This function call will be used to overwrite default resource Padding settings.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS HpcGetResourcePadding(IN  EFI_PCI_HOT_PLUG_INIT_PROTOCOL *This,
                                 IN  EFI_DEVICE_PATH_PROTOCOL       *HpcDevicePath,
                                 IN  UINT64                         HpcPciAddress,
                                 OUT EFI_HPC_STATE                  *HpcState,
                                 OUT VOID                           **Padding,
                                 OUT EFI_HPC_PADDING_ATTRIBUTES     *Attributes)
{
    EFI_STATUS          Status=EFI_SUCCESS;
    PCI_HPC_DATA        *hpcdata=NULL;
    HPC_LOCATION_DATA   *locdata;
    UINTN               i, cnt;    
    ASLR_QWORD_ASD      *pd, *qw; 
//----------------------------------------------
    hpcdata=(PCI_HPC_DATA*)This;

    //Find which exactly HPC PCI BUS Driver means..
    Status=FindHpcLocData(HpcDevicePath, hpcdata,&locdata);
    if(EFI_ERROR(Status)) return Status;

    //Calculate how many ACPI_QW_DESC we need for Padding Info. 
    for(i=0, cnt=0; i<ptMaxType; i++){
        if(locdata->Padding[i]!=0) cnt++;
    }
    
    //Get memory for it.
    pd=MallocZ(sizeof(ASLR_QWORD_ASD)*cnt+sizeof(ASLR_EndTag));
    if (pd==NULL) {
        Status=EFI_OUT_OF_RESOURCES;
        ASSERT_EFI_ERROR(Status);
        return Status;
    }

    //fill out QW Resopurce Descriptors for resource requirements.
    for(i=0, qw=pd; i<ptMaxType; i++){
        if(locdata->Padding[i]!=0){
            HpcFillDescriptor(qw, (HP_PADD_RES_TYPE)i, locdata->Padding[i]);
            qw++;
        }        
    }    

	((ASLR_EndTag*)qw)->Hdr.HDR=ASLV_END_TAG_HDR;
	((ASLR_EndTag*)qw)->Chsum=0;

    *Padding=pd;
    *HpcState=(EFI_HPC_STATE_INITIALIZED|EFI_HPC_STATE_ENABLED);
    *Attributes=EfiPaddingPciBus;
        
    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	HpcInitProtocol
//
// Description:	This function will collect all information HP related 
// information and initialize an instance of PCI Root Hotplug Controller 
// Initialization Protocol.
//
// Input:		PCI_HOST_BRG_DATA   *HostBrg - Pointer on Private Data 
//              structure for which PCI Hot Plug Init Protocol going to 
//              be initialized
//
// Output:		EFI_SUCCESS is OK
//              EFI_NOT_FOUND no Hotplug slots where found. 
//
// Notes:		CHIPSET AND/OR BOARD PORTING NEEDED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS HpcInitProtocol(PCI_HOST_BRG_DATA *HostBrg){
    EFI_STATUS          Status=EFI_NOT_FOUND;
//    PCI_HPC_DATA        *HpcData;
//---------------------------
        
    HostBrg->HpcData=MallocZ(sizeof(PCI_HPC_DATA));
    if(HostBrg->HpcData==NULL){
        Status=EFI_OUT_OF_RESOURCES;
        ASSERT_EFI_ERROR(Status);
        return Status;
    }
    HostBrg->HpcData->Owner=HostBrg;    

    //Get HP Slots information and Device Path.
    Status=HpcFindSlots(HostBrg);
    if(EFI_ERROR(Status)) return Status;    
        
    //So far so good... Init Protocol Instance Functions
    HostBrg->HpcData->RootHotplugProtocol.GetRootHpcList=HpcInitGetRootHpcList;        
    HostBrg->HpcData->RootHotplugProtocol.InitializeRootHpc=HpcInitInitializeRootHpc;        
    HostBrg->HpcData->RootHotplugProtocol.GetResourcePadding=HpcGetResourcePadding;        
    

    return Status;
}

#endif  //AMI_HOTPLUG_INIT_SUPPORT == 1

EFI_STATUS FindRbBusData(PCI_ROOT_BRG_DATA *RootBrg, ASLR_QWORD_ASD **ResDsc){
    UINTN           i;
    ASLR_QWORD_ASD  *res;
//----------------------------

   //Init return walue with NOT_FOUND result
    *ResDsc=NULL;    

    for(i=0;i<RootBrg->ResCount;i++){

        res=RootBrg->RbRes[i];
        if(res->Type== ASLRV_SPC_TYPE_BUS){
            *ResDsc=res;
            return EFI_SUCCESS;
        }
    }//for k
    
    return EFI_NOT_FOUND;
}


EFI_STATUS ClaimMmioResources(PCI_ROOT_BRG_DATA *CurRootBrg, PCI_ROOT_BRG_DATA *NextRootBrg, ACPI_RES_TYPE ResType){
    EFI_STATUS                      Status;
    DXE_SERVICES                    *dxe=NULL;
    EFI_GCD_MEMORY_SPACE_DESCRIPTOR mem;
    UINT64                          top, bot, tmp, ct, cb;    
    ACPI_RES_DATA                   *car, *nar;
//--------------------------------
	// Get GCD's Memory Space and IO Space Maps
	Status=LibGetDxeSvcTbl(&dxe);
    if(EFI_ERROR(Status)){
        PCI_TRACE((TRACE_PCI,"PciRootBrg: Fail to Get DXE Services Table Pointer - %r\n", Status));
        ASSERT_EFI_ERROR(Status);
        return EFI_DEVICE_ERROR;
    }
    
    if(ResType==raMmio32)car=&CurRootBrg->AcpiRbRes[raMmio32];
    else car=&CurRootBrg->AcpiRbRes[raMmio64];

    if(car->Len==0) return EFI_NOT_FOUND;

	// Use MMIO resources as-is if AllocType is set to EfiGcdAllocateAddress.
	if(car->AllocType == EfiGcdAllocateAddress) return EFI_SUCCESS;

    if(NextRootBrg!=NULL) {
        if(ResType==raMmio32)nar=&NextRootBrg->AcpiRbRes[raMmio32];
        else nar=&NextRootBrg->AcpiRbRes[raMmio64];
    }else nar=NULL;


    if( nar==NULL ) {
        if(ResType==raMmio32){
            top=MAX_PCI_MMIO32;
            bot=MIN_PCI_MMIO32;
        } else {
            top=MAX_PCI_MMIO64;
            bot=MIN_PCI_MMIO64;
        }
    } else {
        if(car->AllocType<=EfiGcdAllocateAddress){
            top=nar->Min-1;
            bot=car->Min;
        } else {
            top=car->Max;
            if(ResType==raMmio32) bot=MIN_PCI_MMIO32;
            else bot=MIN_PCI_MMIO64;
        }
    }
	
	if( TmpTop[ResType] != 0 ) bot=TmpTop[ResType]+1;
//	if( TmpBot[ResType] != 0 ) bot=TmpBot[ResType];
	
    cb=car->Min;
    ct=car->Max;

    PCI_TRACE((TRACE_PCI,"  Ajusting ACPI MMIO MAP [0x%lX...[0x%lX...0x%lX]...0x%lX]\n",bot,cb,ct,top));
    
    PCI_TRACE((TRACE_PCI,"    Searching from "));

    if(car->AllocType<=EfiGcdAllocateAddress) {
        tmp=ct+1;
        PCI_TRACE((TRACE_PCI,"0x%lX ==> UP.....to 0x%lX\n", tmp, top));
    } else {
        tmp=cb-1;
        PCI_TRACE((TRACE_PCI,"0x%lX <== DOWN...to 0x%lX\n", tmp, bot));
    }
    
    //All IO map's EfiGcdIoTypeNonExistent IO type, must be converted to EfiGcdIoTypeIo    
    while(TRUE){
        Status=dxe->GetMemorySpaceDescriptor(tmp,&mem);
        
        //Check if we reach end of GCD Space map... 
        if(EFI_ERROR(Status)) break;
        
        //Check if we hit another RB 
        if(mem.DeviceHandle!=NULL && mem.DeviceHandle!=CurRootBrg->RbHandle) break;

        //Check if we hit system memory...
        if(mem.GcdMemoryType != EfiGcdMemoryTypeMemoryMappedIo) break;        

        PCI_TRACE((TRACE_PCI,"    MemDsc: BAS=0x%lX; LEN=0x%lX; TYP=%d; IH=0x%X; DX=0x%X; %r\n",
        mem.BaseAddress, mem.Length, mem.GcdMemoryType, mem.ImageHandle, mem.DeviceHandle, Status));

        if(car->AllocType<=EfiGcdAllocateAddress){
           ct=mem.BaseAddress+mem.Length-1;   
        } else {
            cb=mem.BaseAddress;
        }                

        if(car->AllocType<=EfiGcdAllocateAddress){
            //if we are searching bottom to top...
            if(ct>=top){
                ct=top;
                break;
            }
        } else {
            //if we are searching top to bottom...
            if(cb<=bot){
                cb=bot;
                break;
            }
        }
        
        if(car->AllocType<=EfiGcdAllocateAddress) tmp=ct+1;
        else tmp=cb-1;
    }

    car->Max=ct;
    car->Min=cb;
    car->Len=ct-cb+1;    

	TmpTop[ResType]=ct;
	TmpBot[ResType]=cb;

    return EFI_SUCCESS;
}


EFI_STATUS ClaimIoResources(PCI_ROOT_BRG_DATA *CurRootBrg, PCI_ROOT_BRG_DATA *NextRootBrg){
    EFI_STATUS                      Status;
    DXE_SERVICES                    *dxe=NULL;
    EFI_GCD_IO_SPACE_DESCRIPTOR     io;
    UINT64                          top, bot, tmp, ct, cb;    
    ACPI_RES_DATA                   *car, *nar;
//--------------------------------
	// Get GCD's Memory Space and IO Space Maps
	Status=LibGetDxeSvcTbl(&dxe);
    if(EFI_ERROR(Status)){
        PCI_TRACE((TRACE_PCI,"PciRootBrg: Fail to Get DXE Services Table Pointer - %r\n", Status));
        ASSERT_EFI_ERROR(Status);
        return EFI_DEVICE_ERROR;
    }

    car=&CurRootBrg->AcpiRbRes[raIo];

    if(car->Len==0) return EFI_NOT_FOUND;

    if(NextRootBrg!=NULL) nar=&NextRootBrg->AcpiRbRes[raIo];
    else nar=NULL;

    if( nar==NULL ) {
        top=MAX_PCI_IO;
        bot=MIN_PCI_IO;
    } else {
        if(car->AllocType<=EfiGcdAllocateAddress){
            top=nar->Min-1;
            bot=car->Min;
        } else {
            top=car->Max;
            bot=MIN_PCI_IO;
        }
    }

	if( TmpTop[raIo] != 0 ) bot=TmpTop[raIo]+1;
	//if( TmpBot[raIo] != 0 ) bot=TmpBot[raIo];

    cb=car->Min;
    ct=car->Max;

    PCI_TRACE((TRACE_PCI,"  Ajusting ACPI IO MAP [0x%lX...[0x%lX...0x%lX]...0x%lX]\n",bot,cb,ct,top));
    
    PCI_TRACE((TRACE_PCI,"    Searching from "));

    if(car->AllocType<=EfiGcdAllocateAddress) {
        tmp=ct+1;
        PCI_TRACE((TRACE_PCI,"0x%lX ==> UP.....to 0x%lX\n", tmp, top));
    } else {
        tmp=cb-1;
        PCI_TRACE((TRACE_PCI,"0x%lX <== DOWN...to 0x%lX\n", tmp, bot));
    }
    
    //All IO map's EfiGcdIoTypeNonExistent IO type, must be converted to EfiGcdIoTypeIo    
    while(TRUE){
        Status=dxe->GetIoSpaceDescriptor(tmp,&io);

        //Check if we reach end of GCD Space map... 
        if(EFI_ERROR(Status)) break;
        
        //Check if we hit another RB 
        if(io.DeviceHandle!=NULL && io.DeviceHandle!=CurRootBrg->RbHandle) break;        

        PCI_TRACE((TRACE_PCI,"    IoDes: BAS=0x%lX; LEN=0x%lX; TYP=%d; IH=0x%X; DX=0x%X; %r\n",
        io.BaseAddress, io.Length, io.GcdIoType, io.ImageHandle, io.DeviceHandle, Status));

        if(car->AllocType<=EfiGcdAllocateAddress){
           ct=io.BaseAddress+io.Length-1;   
        } else {
            cb=io.BaseAddress;
        }                
        if(car->AllocType<=EfiGcdAllocateAddress){
            //if we are searching bottom to top...
            if(ct>=top){
                ct=top;
                break;
            }
        } else {
            //if we are searching top to bottom...
            if(cb<=bot){
                cb=bot;
                break;
            }
        }
        
        if(car->AllocType<=EfiGcdAllocateAddress) tmp=ct+1;
        else tmp=cb-1;
    }

    car->Max=ct;
    car->Min=cb;
    car->Len=ct-cb+1;    

	TmpTop[raIo]=ct;
	TmpBot[raIo]=cb;

    return EFI_SUCCESS;
}

EFI_STATUS AjustAcpiResource(UINTN HostIndex, UINTN RootIndex, ACPI_RES_TYPE ResType){
    EFI_STATUS          Status=EFI_SUCCESS;
    PCI_HOST_BRG_DATA   *hb, *nexthb;
    PCI_ROOT_BRG_DATA   *rb, *nextrb;
    ASLR_QWORD_ASD      *res, *nextres;
//--------------------

    //Get pointers to the main data structures we are going to work with.
    hb=&gPciRbHost[HostIndex];
    rb=hb->RootBridges[RootIndex];

    //Check if system has NEXT entity available...
    if(NB_NUMBER_OF_HOST_BRG>HostIndex+1) nexthb=&gPciRbHost[HostIndex+1];
    else nexthb=NULL;

    if(hb->RootBridgeCount>RootIndex+1)nextrb=hb->RootBridges[RootIndex+1];
    else {
        if(nexthb!=NULL) nextrb=nexthb->RootBridges[0];
        else nextrb=NULL;
    }

    //Start parsing resources...
    switch(ResType){
        case raBus:
            //Trying to make bus ranges among the bridges be decoded consistently
            //even RB0 decodes buses 0..5 and RB1 decodes 0x80..0x82 for ACPI 
            //make it decode 0..0x7F and 80..0xFF correspondently.
            Status=FindRbBusData(rb, &res);
            //BUS resources must be there
            ASSERT_EFI_ERROR(Status);
            if(EFI_ERROR(Status)) return EFI_DEVICE_ERROR;

            //fill ACPI Resource properties
            rb->AcpiRbRes[raBus].Min=res->_MIN;
            rb->AcpiRbRes[raBus].Gra=1;
            if (nextrb!=NULL) {
                Status=FindRbBusData(nextrb, &nextres);        
                //BUS resources must be there
                ASSERT_EFI_ERROR(Status);
                if(EFI_ERROR(Status)) return EFI_DEVICE_ERROR;
				//Check if NULL bus descriptor...
				if(nextres->_MIN==0 && nextres->_MAX==0 && nextres->_LEN==0)
	               rb->AcpiRbRes[raBus].Max=MAX_PCI_BUSES; 
				else
                   rb->AcpiRbRes[raBus].Max=nextres->_MIN-1;
           } else {
                rb->AcpiRbRes[raBus].Max=MAX_PCI_BUSES;
           }
           rb->AcpiRbRes[raBus].Len=rb->AcpiRbRes[raBus].Max-rb->AcpiRbRes[raBus].Min+1;

           PCI_TRACE((TRACE_PCI,"  Ajusting ACPI BUS MAP [0x%lX...[0x%lX...0x%lX]...0x%lX]\n",
           rb->AcpiRbRes[raBus].Min,res->_MIN,res->_MIN+res->_LEN-1,rb->AcpiRbRes[raBus].Max));
           PCI_TRACE((TRACE_PCI,"  ACPI BUS MAP Set to [0x%lX...0x%lX]\n",
                        rb->AcpiRbRes[raBus].Min,rb->AcpiRbRes[raBus].Max));
        break;

        case raIo:
        //With IO picture is much worse. we should scan and assume any unallocated IO to the 
        //corresponded RB keeping in mind boundary between RB0..RB1..RBn decoding ranges.
            //IO resources may not be there ISA res 0...0xFFF is taken care of automatically
            //If system don't have second root bridge and does not decode any IO, assume all IO 
            //from 0x1000...Fset  decoded by
            Status=ClaimIoResources(rb, nextrb);
            PCI_TRACE((TRACE_PCI,"  ACPI IO MAP Set to [0x%lX...0x%lX] %r\n",
                        rb->AcpiRbRes[raIo].Min,rb->AcpiRbRes[raIo].Max,Status));
        break;
        case raMmio32:
            Status=ClaimMmioResources(rb, nextrb, raMmio32);
            PCI_TRACE((TRACE_PCI,"  ACPI MEM32 MAP Set to [0x%lX...0x%lX] %r\n",
                        rb->AcpiRbRes[raMmio32].Min,rb->AcpiRbRes[raMmio32].Max, Status));
            
        break;
        case raMmio64:
            Status=ClaimMmioResources(rb, nextrb, raMmio64);
            PCI_TRACE((TRACE_PCI,"  ACPI MEM64 MAP Set to [0x%lX...0x%lX] %r\n",
                        rb->AcpiRbRes[raMmio64].Min,rb->AcpiRbRes[raMmio64].Max, Status));
        break;
        default: return EFI_DEVICE_ERROR; 
    }

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	RbReadyToBoot
//
// Description:	This function will create ReadyToBoot Event to update each 
//              Root Bridge ASL Object with corresponded resources decoded.
//
// Input:		Nothing
//
// Output:		EFI_SUCCESS is OK
//              
//
// Notes:		CHIPSET AND/OR BOARD PORTING NEEDED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID RbReadyToBoot(IN EFI_EVENT Event,	IN VOID	*Context){
    EFI_STATUS                      Status;
    UINTN                           i,j,k;
    PCI_HOST_BRG_DATA               *hb;
    PCI_ROOT_BRG_DATA               *rb;
    ACPI_HDR                        *dsdt;
    EFI_PHYSICAL_ADDRESS            a;   
    BOOLEAN                         vga=FALSE;
//-----------------------------
    
//	EFI_DEADLOOP();

    //Get DSDT.. we have to update it.
    Status=LibGetDsdt(&a,EFI_ACPI_TABLE_VERSION_ALL);
   	if(EFI_ERROR(Status)){
        PCI_TRACE((TRACE_PCI,"PciRootBrg: Fail to Get DSDT - returned %r\n", Status));
	    ASSERT_EFI_ERROR(Status);
        return;
    } else dsdt=(ACPI_HDR*)a;

    //Collect currently programed resource requirements, we will need to ajust it
    //to clame all Unallocated IO/MMIO to report it to OS. 
    for(i=0; i<NB_NUMBER_OF_HOST_BRG; i++){
        hb=&gPciRbHost[i];
        for(j=0; j<hb->RootBridgeCount; j++){
            rb=hb->RootBridges[j];            

            PCI_TRACE((TRACE_PCI,"PciRootBrg: Host[ %d ].Root[ %d ] \n", i, j));

            for(k=raBus; k<raMaxRes; k++){
                Status=AjustAcpiResource(i,j,k);
            }//for k
        }//for j
    }//for i

    //after collectinfg and ajusting all Rb decoding info info
    //Update place holders in each Rb Device Scope in DSDT.
    for(i=0; i<NB_NUMBER_OF_HOST_BRG; i++){
        hb=&gPciRbHost[i];
        for(j=0; j<hb->RootBridgeCount; j++){
            rb=hb->RootBridges[j];            
            
            //Check if this is a Compatibility Root Bridge.                        
            PCI_TRACE((TRACE_PCI,"PciRootBrg: Updating ASL Device Object '%s': ...\n", rb->RbAslName));

            if(rb->Supports & (PCI_ROOT_COMPATIBILITY_ATTRIBUTES)){
                Status=UpdateAslNameOfDevice(dsdt, rb->RbAslName, "CPRB", 1); 
                PCI_TRACE((TRACE_PCI,"        =>'CPRB'= 1 -> %r;\n", Status));
            } else {
                Status=UpdateAslNameOfDevice(dsdt, rb->RbAslName, "CPRB", 0); 
                PCI_TRACE((TRACE_PCI,"        =>'CPRB'= 0 -> %r;\n", Status));
            }

            if(rb->Attributes & (PCI_ROOT_VGA_ATTRIBUTES)){
                Status=UpdateAslNameOfDevice(dsdt, rb->RbAslName, "LVGA", 1);
                PCI_TRACE((TRACE_PCI,"        =>'LVGA'= 1 -> %r;\n", Status));
                vga=TRUE;
            } else {
                Status=UpdateAslNameOfDevice(dsdt, rb->RbAslName, "LVGA", 0); 
                PCI_TRACE((TRACE_PCI,"        =>'LVGA'= 0 -> %r;\n", Status));
            }

            //Now Update place holders fit in collected system resource consumption.

            //0. Update device Status
            if( rb->NotPresent ) Status=UpdateAslNameOfDevice(dsdt, rb->RbAslName, "STAV", 0x00);
            PCI_TRACE((TRACE_PCI,"        =>'SATV'=%d -> %r;\n", !rb->NotPresent, Status));

            //1.Update Bus Object
            Status=UpdateAslNameOfDevice(dsdt, rb->RbAslName, "BRB", rb->AcpiRbRes[raBus].Min);
            PCI_TRACE((TRACE_PCI,"        =>'BRB_'=0x%lX -> %r; ",rb->AcpiRbRes[raBus].Min, Status));
            Status=UpdateAslNameOfDevice(dsdt, rb->RbAslName, "BRL", rb->AcpiRbRes[raBus].Len);
            PCI_TRACE((TRACE_PCI," 'BRL_'=0x%lX -> %r;\n",rb->AcpiRbRes[raBus].Len, Status));

            //2.Update IO Object
            Status=UpdateAslNameOfDevice(dsdt, rb->RbAslName, "IOB", rb->AcpiRbRes[raIo].Min);
            PCI_TRACE((TRACE_PCI,"        =>'IOB_'=0x%lX -> %r; ",rb->AcpiRbRes[raIo].Min, Status));
            Status=UpdateAslNameOfDevice(dsdt, rb->RbAslName, "IOL", rb->AcpiRbRes[raIo].Len);
            PCI_TRACE((TRACE_PCI," 'IOL_'=0x%lX -> %r;\n",rb->AcpiRbRes[raIo].Len, Status));

            //3.Update MMIO32 Object
            Status=UpdateAslNameOfDevice(dsdt, rb->RbAslName, "MBB", rb->AcpiRbRes[raMmio32].Min);
            PCI_TRACE((TRACE_PCI,"        =>'MBB_'=0x%lX -> %r; ",rb->AcpiRbRes[raMmio32].Min, Status));
            Status=UpdateAslNameOfDevice(dsdt, rb->RbAslName, "MBL", rb->AcpiRbRes[raMmio32].Len);
            PCI_TRACE((TRACE_PCI," 'MBL_'=0x%lX -> %r;\n",rb->AcpiRbRes[raMmio32].Len, Status));

            //3.Update MMIO64 Object
            //3.1 Update LO part of _MIN
            a=rb->AcpiRbRes[raMmio64].Min & 0xFFFFFFFF;
            Status=UpdateAslNameOfDevice(dsdt, rb->RbAslName, "MABL", a);
            PCI_TRACE((TRACE_PCI,"        =>'MABL'=0x%lX -> %r; ", a, Status));

            //3.2 Update HI part of _MIN
            a=Shr64(rb->AcpiRbRes[raMmio64].Min, 32);
            Status=UpdateAslNameOfDevice(dsdt, rb->RbAslName, "MABH", a);
            PCI_TRACE((TRACE_PCI,"'MABH'=0x%lX -> %r;\n", a, Status));

            //3.3 Update LO part of MAX
            a=rb->AcpiRbRes[raMmio64].Max & 0xFFFFFFFF;
            Status=UpdateAslNameOfDevice(dsdt, rb->RbAslName, "MAML", a);
            PCI_TRACE((TRACE_PCI,"        =>'MAML'=0x%lX -> %r; ", a, Status));

            //3.4 Update HI part of _MAX
            a=Shr64(rb->AcpiRbRes[raMmio64].Max, 32);
            Status=UpdateAslNameOfDevice(dsdt, rb->RbAslName, "MAMH", a);
            PCI_TRACE((TRACE_PCI,"'MAMH'=0x%lX -> %r;\n", a, Status));

            //3.3 Update LO part of MAX
            a=rb->AcpiRbRes[raMmio64].Len & 0xFFFFFFFF;
            Status=UpdateAslNameOfDevice(dsdt, rb->RbAslName, "MALL", a);
            PCI_TRACE((TRACE_PCI,"        =>'MALL'=0x%lX -> %r; ", a, Status));

            //3.4 Update HI part of _MAX
            a=Shr64(rb->AcpiRbRes[raMmio64].Len, 32);
            Status=UpdateAslNameOfDevice(dsdt, rb->RbAslName, "MALH", a);
            PCI_TRACE((TRACE_PCI,"'MALH'=0x%lX -> %r;\n", a, Status));

        }//j
    }//i    

    //if PCI_ROOT_VGA_ATTRIBUTES were not set by drivers we have to clame Legacy VGS IO and MEM Space.
    if(!vga){
        hb=&gPciRbHost[0];
        rb=hb->RootBridges[0];            
        PCI_TRACE((TRACE_PCI,"PciRootBrg: Legacy VGA Attributes were not set!!!\n"));
        PCI_TRACE((TRACE_PCI,"    Setting 'LVGA'=1 of Device Object '%s' for Hb[0].Rb[0] -> ", rb->RbAslName));
        Status=UpdateAslNameOfDevice(dsdt, rb->RbAslName, "LVGA", 1);
        PCI_TRACE((TRACE_PCI,"%r;\n", Status));
    }

    //Checksum 
	dsdt->Checksum = 0;
	dsdt->Checksum = ChsumTbl((UINT8*)dsdt, dsdt->Length);

	// Check for invalid Pci RootBridge Handle. 
	//If Rootbridge handle is invalid, then uninstall PCI Rootbridge IO protocol on this handle.
	for(i=0; i<NB_NUMBER_OF_HOST_BRG; i++){
        hb=&gPciRbHost[i];
        for(j=0; j<hb->RootBridgeCount; j++){
            rb=hb->RootBridges[j];  
            PCI_TRACE((TRACE_PCI,"PciRootBrg: Host[ %d ].Root[ %d ] \n", i, j));

			if(rb->NotPresent) {
				PCI_TRACE((TRACE_PCI,"Hb.SetBusNumbers - Invalid RB Hndle Passed\n"));
				Status = pBS->UninstallMultipleProtocolInterfaces (
        			rb->RbHandle, 
					&gRbIoProtocolGuid, &rb->RbIoProtocol,
					&gDevPathProtocolGuid, rb->DevPath,
					NULL
    			);
			
				PCI_TRACE((TRACE_PCI,"Uninstall RbIoProtocol Status %r; \n", Status));			
			    rb->RbHandle=NULL;
			}//if     
        }//for j
    }//for i
	
    pBS->CloseEvent(Event);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	CreateRootBusData
//
// Description:	This function will parse NusXlat Table looking for HostBridge 
//              entries (one who has Bus IN == Bus OUT) and populate gRootBusDb
//              Structure.
//
// Input:		Nothing
//
// Output:		EFI_SUCCESS is OK
//              
//
// Notes:		CHIPSET AND/OR BOARD PORTING NEEDED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS CreateRootBusData(){
    PCI_BUS_XLAT_HDR    *xhdr=gAmiBoardInfoProtocol->BusXlatTable;
    PCI_DEV_FUN         *devf = (PCI_DEV_FUN*)(xhdr+1);
    UINTN               i=0;
    EFI_STATUS          Status;
//--------------------------------
    while((UINTN)devf<=(UINTN)(gAmiBoardInfoProtocol->BusXlatTable)+gAmiBoardInfoProtocol->BusXlatLength){
        if(devf->DEV_FUN == 0xFF){
            //if we are looking for host device it shouldn't be any other guys in it's chain.
            if(i==1) {
                Status=AddBusDbEntry(xhdr, &gRootBusDb);
                ASSERT_EFI_ERROR(Status);
                if(EFI_ERROR(Status)) return Status;
            }
            //Advance to the next record in BusXlatTbl.
#if AMI_BOARD_VER_COMBINED >= 100
            //Now we have AslName[5] following devf data
            xhdr=(PCI_BUS_XLAT_HDR*)(devf+1+5);
#else
            xhdr=(PCI_BUS_XLAT_HDR*)(devf+1);
#endif
            devf = (PCI_DEV_FUN*)(xhdr+1);
            i=0;
        } else {
            devf++;
            i++;
        }
    }
    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ConvertMemoryMap
//
// Description:	This function will adjust the final GCD resource map and
//				convert all NonrExistant Memory resources into MMIO.
//
// Input:		ImgHandle	Image handle
//				CntrHandle	Controller Handle
//
// Output:		None
//
// Notes:		CHIPSET AND/OR BOARD PORTING NEEDED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ConvertMemoryMap(EFI_HANDLE	ImgHandle, EFI_HANDLE	CntrHandle)
{
	EFI_STATUS						Status;
	EFI_GCD_MEMORY_SPACE_DESCRIPTOR	*pMap;
	EFI_GCD_IO_SPACE_DESCRIPTOR		*pIo;
	UINTN 							Size, i;
	DXE_SERVICES					*dxe;	
//----------------------------------------------------------------------

	// Convert All Nonexistent Memory space to MMIO
	// Once GCD and Memory manager gets initialized
	Status=LibGetDxeSvcTbl(&dxe);
	if(EFI_ERROR(Status)) return Status;


	Status=dxe->GetMemorySpaceMap(&Size, &pMap);
	ASSERT_EFI_ERROR(Status);
	if(EFI_ERROR(Status)) return Status;

	for(i=0; i<Size; i++)
	if (pMap[i].GcdMemoryType == EfiGcdMemoryTypeNonExistent ){
		Status=dxe->AddMemorySpace(EfiGcdMemoryTypeMemoryMappedIo,
			pMap[i].BaseAddress,pMap[i].Length, GCD_COMMON_MMIO_CAPS);
		ASSERT_EFI_ERROR(Status);
		if(EFI_ERROR(Status)) return Status;
	}
	pBS->FreePool(pMap);

	//Convert all non-existant IO to existant IO
	Status=dxe->GetIoSpaceMap(&Size, &pIo);
	ASSERT_EFI_ERROR(Status);
	if(EFI_ERROR(Status)) return Status;
   	for(i=0; i<Size; i++)
	if (pIo[i].GcdIoType == EfiGcdIoTypeNonExistent){
		Status=dxe->AddIoSpace(EfiGcdIoTypeIo,pIo[i].BaseAddress,pIo[i].Length);
		ASSERT_EFI_ERROR(Status);
		if(EFI_ERROR(Status)) return Status;
	}
	pBS->FreePool(pIo);

	return Status;	
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   IsResSubmited()
//
// Description:
//   Will check if all root bridges belonging to the "Host" has submitted 
//   it's resources
//
// Input:
//  PCI_HOST_BRG_DATA *Host  Pointer to HOST Bridge private data
//  EFI_HANDLE  RootBridgeHandle    PCI Root Bridge to be configured
//  VOID        **Configuration     Pointer to the pointer to the PCI bus resource descriptor
//  EFI_PCI_CONFIGURATION_ADDRESS   PciBusAddress   Address of the controller on the PCI bus
//  EFI_PCI_CONTROLLER_RESOURCE_ALLOCATION_PHASE    Phase   The Phase during resource allocation
//
// Output: BOOLEAN
//  TRUE    all root bridges belonging to the "Host" has its resources submitted
//  FALSE   opposite ...
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN IsResSubmited(PCI_HOST_BRG_DATA *Host){
	PCI_ROOT_BRG_DATA	*rb;
	UINTN				i;
//---------------------
	for(i=0; i<NB_NUMBER_OF_HOST_BRG; i++){
		rb=Host->RootBridges[i];
		if(!rb->ResSubmited) return FALSE;
	}
	return TRUE;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetRbByHandle()
//
// Description: 
//  Lokates 
//
// Input:
//  EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL *This  Protocol instance
//  EFI_HANDLE  RbHandle            PCI Root Bridge Handle to get Private data for.
//  UINTN       *Index              Updated Index of the Found Root Bridge private data
//
// Output: PCI_ROOT_BRG_DATA 
//  Not NULL if Root was found.
//  NULL if Root was not found.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
PCI_ROOT_BRG_DATA *GetRbByHandle(EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL	*This,
								 EFI_HANDLE										 	RbHandle,
								 UINTN												*Index OPTIONAL)
{
	PCI_HOST_BRG_DATA	*hbdata=(PCI_HOST_BRG_DATA*)This;
	PCI_ROOT_BRG_DATA	*rbdata;
	UINTN				i;
//----------------------------------
	for(i=0;i<hbdata->RootBridgeCount;i++){
		rbdata=hbdata->RootBridges[i];
		if(rbdata->RbHandle==RbHandle){
			if(Index)(*Index)=i;
//			hbdata->CurrentRb=i;
			return rbdata;
		}
	}
	return NULL;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetResources()
//
// Description:
//  This function will generate Resource descriptors block based on information
//  stored in RootBridge->RbRes array
//
// Input:
//  PCI_HOST_BRG_DATA   *Host       Pointer to HOST Bridge private data
//  ASLR_QWORD_ASD      **Resources Resource List in a form of ACPI QWORD Resource Descriptor.
//  ASLR_TYPE_ENUM      ResType     Describes what type of resources we are getting.
//
// Output: EFI_STATUS
//  EFI_SUCCESS - Success
//  EFI_OUT_OF_RESOURCES - If SubmitResources ( ) could not allocate resources
//  EFI_NOT_READY        - This phase cannot be entered at this time
//  EFI_DEVICE_ERROR     - SetResources failed due to HW error.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS GetResources(PCI_ROOT_BRG_DATA *RootBrg, ASLR_QWORD_ASD **Resources, ASLR_TYPE_ENUM ResType)
{
	UINTN				i,cnt=0;
	ASLR_QWORD_ASD		*qw;
	BOOLEAN				cpy;
//---------------------------------1
	//count descriptors first
	if(ResType==tResAll) cnt=RootBrg->ResCount;
	else { 
		for(i=0;i<RootBrg->ResCount;i++){
			if(ResType==tResBus){
				if(RootBrg->RbRes[i]->Type == ASLRV_SPC_TYPE_BUS)cnt++;
			} else {
				if(RootBrg->RbRes[i]->Type < ASLRV_SPC_TYPE_BUS) cnt++;
			}
		}
	}
	//if(!cnt) return EFI_NOT_FOUND;

	//Allocate memory for ASL Resource Descriptors
	qw=Malloc(sizeof(ASLR_QWORD_ASD)*cnt+sizeof(ASLR_EndTag));
	if(!qw) return EFI_OUT_OF_RESOURCES;

	*Resources=qw;
	
	//Copy Resource information
	for(i=0; i<RootBrg->ResCount; i++, cpy=FALSE){
		if(ResType==tResAll) cpy=TRUE;
		else {
			if(ResType==tResBus){
				if(RootBrg->RbRes[i]->Type == ASLRV_SPC_TYPE_BUS)cpy=TRUE;
			} else {
				if(RootBrg->RbRes[i]->Type < ASLRV_SPC_TYPE_BUS) cpy=TRUE;
			}
		}
		if(cpy){
			MemCpy(qw,RootBrg->RbRes[i],sizeof(ASLR_QWORD_ASD));
			qw++;
		}
	}
	((ASLR_EndTag*)qw)->Hdr.HDR=ASLV_END_TAG_HDR;
	((ASLR_EndTag*)qw)->Chsum=0;
	
	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SetResources()
//
// Description:
//  This function will update RootBridge->RbRes array with Descriptors 
//  prowided with *Resources parameter
//
// Input:
//  PCI_HOST_BRG_DATA   *Host       Pointer to HOST Bridge private data
//  ASLR_QWORD_ASD      *Resources Resource List in a form of ACPI QWORD Resource Descriptor.
//  ASLR_TYPE_ENUM      ResType     Describes what type of resources we are getting.
//  BOOLEAN             Replace     if TRUE function will Remove all descriptors of "ResType" before adding.
//                                  if FALSE function will just add "Resources"
//
// Output: EFI_STATUS
//  EFI_SUCCESS - Success
//  EFI_OUT_OF_RESOURCES - If SubmitResources ( ) could not allocate resources
//  EFI_NOT_READY        - This phase cannot be entered at this time
//  EFI_DEVICE_ERROR     - SetResources failed due to HW error.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS SetResources(PCI_ROOT_BRG_DATA *RootBrg, ASLR_QWORD_ASD *Resources, 
			ASLR_TYPE_ENUM ResType, BOOLEAN	Replace)
{
	UINTN				i, len, cnt;
	ASLR_QWORD_ASD		*res;
//---------------------------------

	len=ValidateDescriptorBlock((ASLR_QWORD_ASD*)Resources, ResType, FALSE);
	if(!len) return EFI_INVALID_PARAMETER;

	cnt=(len-sizeof(ASLR_EndTag))/sizeof(ASLR_QWORD_ASD);
    //We have received Empty descriptor nothing to do just return.
    if(!cnt) return EFI_SUCCESS;

	if(Replace){
		if(ResType==tResAll) ClearItemLst((T_ITEM_LIST*)&RootBrg->ResInitCnt, TRUE);
		else {
            i=RootBrg->ResCount;
            while(i){
                i--;
    		    if(ResType==tResBus){
			        if(RootBrg->RbRes[i]->Type == ASLRV_SPC_TYPE_BUS)
				        DeleteItemLst((T_ITEM_LIST*)&RootBrg->ResInitCnt, i,TRUE);
                } else {
					if(RootBrg->RbRes[i]->Type < ASLRV_SPC_TYPE_BUS)
					    DeleteItemLst((T_ITEM_LIST*)&RootBrg->ResInitCnt, i,TRUE);
			    }
            }	
		}
	}

	//Update Bus Resources in rbdata
	for(i=0; i<cnt; i++,Resources++) {
		res=Malloc(sizeof(ASLR_QWORD_ASD));
		if(!res) return EFI_OUT_OF_RESOURCES;

		MemCpy(res,Resources,sizeof(ASLR_QWORD_ASD));
		
		if(EFI_ERROR(AppendItemLst((T_ITEM_LIST*)&RootBrg->ResInitCnt,res))) return EFI_OUT_OF_RESOURCES;
	}
	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   IsPowerOfTwo()
//
// Description: 
//  Checks if value passed makes "POWER OF TWO"
//
// Input:
//  UINT64      Value       Value to check.
//
// Output: BOOLEAN 
//  TRUE or FALSE based on value passed.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN IsPowerOfTwo(UINT64 Value){
	UINTN 	i;
	UINT64 	t;
//--------------
	for(i=0; i<64; i++){
		t=Shl64(1,(UINT8)i);
		if(Value&t) {
			if(Value&(~t))return FALSE;
			else return TRUE;
		}
	}
	return FALSE;
}

//(EIP45278)>
#if PCI_MMIO_RES_TOP_ALLIGN == 1
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   AllocateMemoryResource()
//
// Description: 
//  This function will try to Allocate from GCD set of resources requested by
//  input Length and Alignment.
//
// Input:
//  UINTN                   Alignment       Align with 2^Alignment
//  UINT64                  Length          Length to allocate
//  EFI_PHYSICAL_ADDRESS    *BaseAddress    Base address to allocate
//  EFI_HANDLE              ImageHandle     The image handle consume the allocated space.
//  EFI_HANDLE              DeviceHandle    The device handle consume the allocated space.
//
// Output: EFI_STATUS
//  EFI_INVALID_PARAMETER   Invalid parameter.
//  EFI_NOT_FOUND           No descriptor contains the desired space.
//  EFI_SUCCESS             Memory space successfully allocated.
//
//  EFI_PHYSICAL_ADDRESS    *BaseAddress    Base address to be allocated
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS AllocateMemoryResource (
    IN      UINTN                   Alignment,
    IN      UINT64                  Length,
    IN OUT  EFI_PHYSICAL_ADDRESS    *BaseAddress,
    IN      EFI_HANDLE              ImageHandle,
    IN      EFI_HANDLE              DeviceHandle
)
{
    EFI_STATUS                      Status;
    DXE_SERVICES                    *dxe;
    EFI_PHYSICAL_ADDRESS            AlignmentMask;

    Status=LibGetDxeSvcTbl(&dxe);
    if(EFI_ERROR(Status)) return Status;

    AlignmentMask = (1 << Alignment) - 1;
    // Search an unused for fit the length
    while (((*BaseAddress + Length) & AlignmentMask)) {
        Status = dxe->AllocateMemorySpace (
                      EfiGcdAllocateMaxAddressSearchTopDown,
                      EfiGcdMemoryTypeMemoryMappedIo,
                      0,
                      Length,
                      BaseAddress,
                      ImageHandle,
                      DeviceHandle);
        if(EFI_ERROR(Status)) break;
        // Check if the space is under Alignment
        if (((*BaseAddress + Length) & AlignmentMask)) {
            Status = dxe->FreeMemorySpace (*BaseAddress, Length);
            if(EFI_ERROR(Status)) break;
            *BaseAddress = ((*BaseAddress + Length) & (~AlignmentMask)) - Length;
        }
    }
    return  Status;
}
#endif
//<(EIP45278)

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   AlignFromGra()
//
// Description: 
//  Converts C passed into Alignment format 
//
// Input:
//  UINTN      g       AlignFromGra Value to convert
//
// Output: UINTN
//  Converted Alignment value.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINTN AlignFromGra(UINTN g){
	UINTN a=0;
//------------
	while(g&1){
		a++;
		g=g>>1;
	}
	return a;	
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   AllocateResources()
//
// Description: 
//  This function will try to Allocate from GCD set of resources requested by 
//  PCI BUS driver in "*Resources" buffer.
//
// Input:
//  PCI_ROOT_BRG_DATA *RootBrg  Pointer to ROOT Bridge private data
//
// Output: EFI_STATUS
//  EFI_SUCCESS - Success
//  EFI_OUT_OF_RESOURCES - If could not allocate resources
//  EFI_DEVICE_ERROR     - failed due to HW error.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS AllocateResources(PCI_ROOT_BRG_DATA *RootBrg){
	EFI_STATUS 			Status=0;
    EFI_STATUS          ReturnStatus = 0;
	UINTN				i;
	ASLR_QWORD_ASD		*res;
    ACPI_RES_DATA       *ar;
	UINT64				a=0;
	DXE_SERVICES		*dxe;	
//OUT_OF_RES HANDLING++ must be added in Custom Res allocate function.
#if BoardPciRes_SUPPORT
    AMI_OUT_OF_RES_VAR  OutOfResVar;
//--------------------------------------
    //Check if OUT_OF_RES_VAR was already created.
    Status=AmiPciOutOfRes(&OutOfResVar, TRUE);
    if(EFI_ERROR(Status)) pBS->SetMem(&OutOfResVar,sizeof(AMI_OUT_OF_RES_VAR),0);
    else OutOfResVar.Count++;
#endif
//OUT_OF_RES HANDLING-- must be added in Custom Res allocate function.

	Status=LibGetDxeSvcTbl(&dxe);
	if(EFI_ERROR(Status)) return Status;

 
	for(i=0; i<RootBrg->ResCount; i++){
		res=RootBrg->RbRes[i];
		if(res->Type==ASLRV_SPC_TYPE_BUS) continue;
		//Check if Alignment
		if(!IsPowerOfTwo(res->_MAX+1)) return EFI_INVALID_PARAMETER;
		switch(res->_GRA){
			case 16 : 	a=0xFFFF;//-res->_LEN;
				break;
			case 32	:	a=0xFFFFFFFF;//-res->_LEN;
				break;
			case 64	:	a=0xFFFFFFFFFFFFFFFF;//-res->_LEN+1;
				break;
			default :ASSERT(0); return EFI_INVALID_PARAMETER;
		}
        
        PCI_TRACE((TRACE_PCI,"PciRootBrg:AllocateResources In -> _MIN=0x%lX; _MAX=0x%lX; _LEN=0x%lX; _GRA=0x%lX\n",
        res->_MIN,res->_MAX,res->_LEN,res->_GRA));


		//Allocate IO
		if(res->Type==ASLRV_SPC_TYPE_IO){
            
            ar=&RootBrg->AcpiRbRes[raIo];
            ar->AddrUsed=a;
            ar->AllocType=EfiGcdAllocateMaxAddressSearchTopDown;

			Status=dxe->AllocateIoSpace(EfiGcdAllocateMaxAddressSearchTopDown,
							EfiGcdIoTypeIo,
							AlignFromGra((UINTN)res->_MAX),
							res->_LEN,
							&a,
							RootBrg->ImageHandle, RootBrg->RbHandle);
            
			if(EFI_ERROR(Status)) {
                ReturnStatus = Status;
                PCI_TRACE((TRACE_PCI,"PciRootBrg: IO Allocation Failed: Length: %lX\n",res->_LEN));
//++OUT_OF_RES!! IO                
#if BoardPciRes_SUPPORT
                OutOfResVar.Resource=*res;
                Status=AmiPciOutOfRes(&OutOfResVar, FALSE);                
                return ReturnStatus;
//--OUT_OF_RES!! IO                
#else
                continue;
#endif
		    }
            
        }
		//Allocate MMIO
		else if( res->Type==ASLRV_SPC_TYPE_MEM){

            if(res->_GRA==32)ar=&RootBrg->AcpiRbRes[raMmio32];
            else ar=&RootBrg->AcpiRbRes[raMmio64];
            ar->AddrUsed=a;
            ar->AllocType=EfiGcdAllocateMaxAddressSearchTopDown;
//(EIP45278)>
#if PCI_MMIO_RES_TOP_ALLIGN == 1
            Status = AllocateMemoryResource(
                     AlignFromGra((UINTN)res->_MAX),
                     res->_LEN,
                     &a,
                     RootBrg->ImageHandle,
                     RootBrg->RbHandle);
#else
			Status=dxe->AllocateMemorySpace(EfiGcdAllocateMaxAddressSearchTopDown,
							EfiGcdMemoryTypeMemoryMappedIo,
							AlignFromGra((UINTN)res->_MAX),
							res->_LEN,
							&a,
							RootBrg->ImageHandle, RootBrg->RbHandle);
#endif
//<(EIP45278)

			if(EFI_ERROR(Status)) {
                ReturnStatus = Status;
                PCI_TRACE((TRACE_PCI,"PciRootBrg: Memory Allocation Failed: Length: %lX\n",res->_LEN));
//++OUT_OF_RES!! MEM                
#if BoardPciRes_SUPPORT
                OutOfResVar.Resource=*res;
                Status=AmiPciOutOfRes(&OutOfResVar, FALSE);                
                return ReturnStatus;
#else
//--OUT_OF_RES!! MEM                
                continue;
#endif
            }

			//Set this region as WT cache if it is PREFETCHABLE 
			if(res->TFlags.MEM_FLAGS._MEM!=ASLRV_MEM_UC) 
			{
				//Status=gDxeSvcTbl->SetMemorySpaceAttributes(a,res->_LEN,EFI_MEMORY_WT|EFI_MEMORY_RUNTIME);
				Status=dxe->SetMemorySpaceAttributes(a,res->_LEN,EFI_MEMORY_WT);
				//if attempt to set WT attributes has filed, let's try UC
				if(EFI_ERROR(Status))
				{
					PCI_TRACE((TRACE_DXE_CHIPSET,"PciHostBridge: Setting of WT attributes for prefetchable memory has failed(%r). UC is used.\n",Status));
					//Status=gDxeSvcTbl->SetMemorySpaceAttributes(a,res->_LEN,EFI_MEMORY_UC|EFI_MEMORY_RUNTIME);
					Status=dxe->SetMemorySpaceAttributes(a,res->_LEN,EFI_MEMORY_UC);
				}
			}
			else Status=dxe->SetMemorySpaceAttributes(a,res->_LEN,EFI_MEMORY_UC);
			//	Status=gDxeSvcTbl->SetMemorySpaceAttributes(a,res->_LEN,EFI_MEMORY_UC|EFI_MEMORY_RUNTIME);
			ASSERT_EFI_ERROR(Status);
			if(EFI_ERROR(Status)) return Status;

		}
		res->_MIN=a;


        PCI_TRACE((TRACE_PCI,"PciRootBrg:AllocateResources Out-> _MIN=0x%lX; _MAX=0x%lX; _LEN=0x%lX; _GRA=0x%lX\n",
        res->_MIN,res->_MAX,res->_LEN,res->_GRA));

        //Do some calculation for ACPI _CRS update.        
        if (ar->Min==0) ar->Min=res->_MIN;
        else {
            if(ar->Min > res->_MIN)ar->Min=res->_MIN;
        }
//(EIP45278+)>
#if PCI_MMIO_RES_TOP_ALLIGN == 1
        ar->Gra = 0;
#else
        if (ar->Gra==0) ar->Gra=res->_MAX;
        else {
            if(ar->Gra<res->_MAX)ar->Gra=res->_MAX;
        }
#endif
//<(EIP45278+)
        if(ar->Len==0){
            ar->Len=res->_LEN;
            if(ar->Len & ar->Gra) ar->Len=(ar->Len |ar->Gra)+1;
            ar->Max=ar->Min+ar->Len-1; 
        } else {
            UINT64  max;
        //--------
            max=res->_MIN + res->_LEN - 1;
            if(max>ar->Max)ar->Max=max; 
            ar->Len=ar->Max - ar->Min + 1;
            if(ar->Len & ar->Gra) ar->Len=(ar->Len |ar->Gra)+1;
            ar->Max=ar->Min+ar->Len-1; 
        }
        PCI_TRACE((TRACE_PCI,"PciRootBrg:AcpiResources Min=0x%lX; Max=0x%lX; Len=0x%lX; Gra=0x%lX, AdrUsed=0x%lX\n\n",
        ar->Min,ar->Max,ar->Len,ar->Gra, ar->AddrUsed));

        //Don't need to set this to actual value it could be calculated using commented formula.
        //More important to preserve alignment requirements of the resource window.
		//res->_MAX=res->_MIN+res->_LEN-1;
	}
	return ReturnStatus;	
}




//**********************************************************************
//Pci Host Bridge Resource Allocation Protocol function Implementation
//**********************************************************************

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   HbResAllocNotifyPhase()
//
//Description:  Enter a certain phase of the PCI enumeration process
//
// Input:
//  EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL    *This   Protocol instance
//  EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PHASE       Phase   The phase during enumeration
//    
// Output: EFI_STATUS
//  EFI_SUCCESS - Success
//  EFI_OUT_OF_RESOURCES - If SubmitResources ( ) could not allocate resources
//  EFI_NOT_READY        - This phase cannot be entered at this time
//  EFI_DEVICE_ERROR     - SetResources failed due to HW error.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS HbResAllocNotifyPhase(IN EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL 		*This,
						  		 IN EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PHASE            Phase )
{
	PCI_HOST_BRG_DATA	*hbdata=(PCI_HOST_BRG_DATA*)This;				
	EFI_STATUS			Status=0;	
	EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL		**pp;
	UINTN				i;
//--------------------------------------------------------
	pp=Malloc(sizeof(VOID*)*hbdata->RootBridgeCount);
	ASSERT(pp);
	if(!pp) return EFI_INVALID_PARAMETER;
	
	for(i=0; i<hbdata->RootBridgeCount; i++) pp[i]=&hbdata->RootBridges[i]->RbIoProtocol;  

	switch(Phase){
  		case EfiPciHostBridgeBeginEnumeration:
			//if(hbdata->AllocPhase!=EfiPciHostBridgeBeginEnumeration) return EFI_INVALID_PARAMETER;
			Status=HbNotifyCspBeforeEnumeration(&hbdata->ResAllocProtocol, &pp[0], hbdata->RootBridgeCount);
			ASSERT_EFI_ERROR(Status);
			if(EFI_ERROR(Status)) return Status;
			break;
  		case EfiPciHostBridgeBeginBusAllocation:
			Status=HbNotifyCspBeginBusAllocation(&hbdata->ResAllocProtocol, &pp[0],hbdata->RootBridgeCount);
			ASSERT_EFI_ERROR(Status);
			break;
  		case EfiPciHostBridgeEndBusAllocation:
			if(hbdata->AllocPhase+1!=Phase) return EFI_INVALID_PARAMETER;
			Status=HbNotifyCspEndBusAllocation(&hbdata->ResAllocProtocol, &pp[0],hbdata->RootBridgeCount);
			ASSERT_EFI_ERROR(Status);
			break;
  		case EfiPciHostBridgeBeginResourceAllocation:
			if(hbdata->AllocPhase+1!=Phase) return EFI_INVALID_PARAMETER;
			Status=HbNotifyCspBeginResourceAllocation(&hbdata->ResAllocProtocol, &pp[0],hbdata->RootBridgeCount);
			ASSERT_EFI_ERROR(Status);
			break;
  		case EfiPciHostBridgeAllocateResources:
			if(hbdata->AllocPhase+1!=Phase) return EFI_INVALID_PARAMETER;
			if(!IsResSubmited(hbdata)) return EFI_NOT_READY;			
			Status=HbNotifyCspAllocateResources(&hbdata->ResAllocProtocol, &pp[0],hbdata->RootBridgeCount);
			ASSERT_EFI_ERROR(Status);
			break;
  		case EfiPciHostBridgeSetResources:
			if(hbdata->AllocPhase+1!=Phase) return EFI_INVALID_PARAMETER;
			if(!IsResSubmited(hbdata)) return EFI_NOT_READY;			
			Status=HbNotifyCspSetResources(&hbdata->ResAllocProtocol, &pp[0],hbdata->RootBridgeCount);
			ASSERT_EFI_ERROR(Status);
			break;
  		case EfiPciHostBridgeFreeResources:
			return EFI_UNSUPPORTED;
			break;
  		case EfiPciHostBridgeEndResourceAllocation:
			if(hbdata->AllocPhase+2!=Phase) return EFI_INVALID_PARAMETER;
			Status=HbNotifyCspEndResourceAllocation(&hbdata->ResAllocProtocol, &pp[0],hbdata->RootBridgeCount);
			ASSERT_EFI_ERROR(Status);
			break;
		default: return EFI_INVALID_PARAMETER;	
	}

	if(EFI_ERROR(Status)) return Status;
	hbdata->AllocPhase=Phase;
	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   HbResAllocGetNextRootBridge()
//
// Description: 
//  Return the device handle of the next PCI root bridge that is 
//  associated with this Host Bridge.
//
// Input:
//  EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL    *This   Protocol instance
//  EFI_HANDLE  *RootBridgeHandle                       Returns the device handle 
//      of the next PCI Root Bridge. On input, it holds the RootBridgeHandle 
//      returned by the most recent call to GetNextRootBridge().
//      The handle for the first PCI Root Bridge is returned if RootBridgeHandle 
//      is NULL on input.
//   
// Output: EFI_STATUS
//  EFI_SUCCESS - Success
//  EFI_INVALID_PARAMETER - RootBridgeHandle is invalid
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS HbResAllocGetNextRootBridge(
		IN EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL  	*This,
  		IN OUT EFI_HANDLE                                       *RootBridgeHandle)
{
	PCI_HOST_BRG_DATA	*hbdata=(PCI_HOST_BRG_DATA*)This;
	PCI_ROOT_BRG_DATA	*rbdata;
	UINTN				i=0;
//--------------------------------------------------
	if(!This) return EFI_INVALID_PARAMETER;
	if(*RootBridgeHandle==NULL) {
		rbdata=hbdata->RootBridges[i];
		*RootBridgeHandle=rbdata->RbHandle;
		return EFI_SUCCESS;
	} else {
		rbdata=GetRbByHandle(This,*RootBridgeHandle,&i);
		if(!rbdata) return EFI_INVALID_PARAMETER;
		if(hbdata->RootBridgeCount-1>i){
			rbdata=hbdata->RootBridges[i+1];				
			*RootBridgeHandle=rbdata->RbHandle;
			return EFI_SUCCESS;
		} else return  EFI_NOT_FOUND;
	}		
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   HbResAllocGetAllocAttributes()
//
// Description:
//  Returns the attributes of a PCI Root Bridge.
//
// Input:
//  EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL *This Protocol instance
//  EFI_HANDLE      RootBridgeHandle    The device handle of the PCI Root Bridge 
//                                      that the caller is interested in
//  UINT64          Attribute           The pointer to attributes of the PCI Root Bridge                    
//    
// Output: EFI_STATUS
//  EFI_SUCCESS - Success
//  EFI_INVALID_PARAMETER - RootBridgeHandle is invalid
//  EFI_INVALID_PARAMETER - Attributes is NULL
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS HbResAllocGetAllocAttributes(
		IN EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL  	*This,
  		IN EFI_HANDLE	                                        RootBridgeHandle,
	  	OUT UINT64                                              *Attributes)
{
	PCI_ROOT_BRG_DATA	*rbdata;
//----------------------------------
	if(!This || !Attributes) return EFI_INVALID_PARAMETER;
	rbdata=GetRbByHandle(This,RootBridgeHandle,NULL);
	if(!rbdata)return EFI_INVALID_PARAMETER;
	else *Attributes=rbdata->Owner->AllocAttrib;
	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   HbResAllocStartBusEnumeration()
//
// Description:
//  This is the request from the PCI enumerator to set up 
//  the specified PCI Root Bridge for bus enumeration process. 
//
// Input:
//  EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL *This PROTOCOL instance
//  EFI_HANDLE  RootBridgeHandle    PCI Root Bridge to be configured
//  VOID        **Configuration     Pointer to the pointer to the PCI bus resource descriptor
//    
// Output: EFI_STATUS
//  EFI_SUCCESS - Success
//  EFI_INVALID_PARAMETER - RootBridgeHandle is invalid
//  EFI_DEVICE_ERROR      - Request failed due to hardware error
//  EFI_OUT_OF_RESOURCES  - Request failed due to lack of resources
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS HbResAllocStartBusEnumeration(
		IN EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL		*This,
  		IN EFI_HANDLE                                      		RootBridgeHandle,
		OUT VOID                                                **Configuration)
{
	PCI_ROOT_BRG_DATA	*rbdata;
	UINTN				i;
	EFI_STATUS 			Status;
    ASLR_QWORD_ASD      *qw;
//-----------------------------
	if(!Configuration || !This) return EFI_INVALID_PARAMETER;


	rbdata=GetRbByHandle(This,RootBridgeHandle,&i);		
	if(!rbdata){
		PCI_TRACE((TRACE_PCI,"Hb.StartBusEnumeration - Invalid Rb Handle  Passed\n"));
		ASSERT(rbdata);
		return EFI_INVALID_PARAMETER;
	}

    //ThisCSP Function MIGHT Update rbdata->RbRes[] with bus ranges to scan
	//and program corresponded RB registers to decode this ranges.
    //If function overwrites BUS ranges this ROOT decodes IT MUST UPDATE  rbdata->RbRes[]!
    //If NOT it should not touch BUS resource descriptor.
	Status=HbCspStartBusEnumeration((PCI_HOST_BRG_DATA*)This, rbdata,i);	
	if(EFI_ERROR(Status)){
		PCI_TRACE((TRACE_PCI,"Hb.StartBusEnumeration - HbCspUpdateBusesBefore returned ERROR!\n"));
		ASSERT_EFI_ERROR(Status);
		return Status;	
	}

	Status=GetResources(rbdata, (ASLR_QWORD_ASD**)Configuration, tResBus);
	if(EFI_ERROR(Status)){
		PCI_TRACE((TRACE_PCI,"Hb.StartBusEnum - RB Resources Invalid!\n"));
		ASSERT_EFI_ERROR(Status);
		return Status; 
	}
    
    qw=(ASLR_QWORD_ASD*)*Configuration;

    PCI_TRACE((TRACE_PCI,"PciRb#%d: Enumerating Buses 0x%lX - 0x%lX \n", i, qw->_MIN, qw->_MIN+qw->_LEN-1));    
	PCI_TRACE((TRACE_PCI,"=====================================================================\n\n"));


	((PCI_HOST_BRG_DATA*)This)->EnumStarted=TRUE;
	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   HbResAllocSetBusNumbers()
//
// Description:
//  This function programs the PCI Root Bridge hardware so that 
//  it decodes the specified PCI bus range
//
//Input:
//  EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL *This  Protocol instance
//  EFI_HANDLE  RootBridgeHandle    PCI Root Bridge to be configured
//  VOID        **Configuration     Pointer to the pointer to the PCI bus resource descriptor
//    
// Output: EFI_STATUS
//  EFI_SUCCESS - Success
//  EFI_INVALID_PARAMETER - RootBridgeHandle is invalid
//  EFI_INVALID_PARAMETER - Configuration is NULL
//  EFI_INVALID_PARAMETER - Configuration does not point to a valid ACPI resource descriptor
//  EFI_INVALID_PARAMETER - Configuration contains one or more memory or IO ACPI resource descriptor
//  EFI_INVALID_PARAMETER - Address Range Minimum or Address Range Length fields in Configuration 
//                          are invalid for this Root Bridge.
//  EFI_INVALID_PARAMETER - Configuration contains one or more invalid ACPI resource descriptor
//  EFI_DEVICE_ERROR      - Request failed due to hardware error
//  EFI_OUT_OF_RESOURCES  - Request failed due to lack of resources
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS HbResAllocSetBusNumbers(
		IN EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL		*This,
  		IN EFI_HANDLE                                           RootBridgeHandle,
  		IN VOID                                                 *Configuration)
{
	PCI_ROOT_BRG_DATA	*rbdata;
	UINTN				i;
	EFI_STATUS 			Status;
    ASLR_QWORD_ASD      *qw=(ASLR_QWORD_ASD*)Configuration;
//-----------------------------
	if(!Configuration || !This) return EFI_INVALID_PARAMETER;

	rbdata=GetRbByHandle(This,RootBridgeHandle,&i);		
	if(!rbdata) {
		PCI_TRACE((TRACE_PCI,"Hb.SetBusNumbers - Invalid RB Hndle Passed\n"));
		return EFI_INVALID_PARAMETER;
	}

	Status=SetResources(rbdata, Configuration, tResBus, TRUE);
	
	if(EFI_ERROR(Status)){
		PCI_TRACE((TRACE_PCI,"Hb.SetBusNumbers - Invalid Resoutce Descriptor(s) Passed\n"));
		ASSERT_EFI_ERROR(Status);
		return Status;
	}
	
	//Call CSP function to update RB Buses accordinaly submited information
	Status=HbCspSetBusNnumbers((PCI_HOST_BRG_DATA*)This, rbdata, i);
	
	if(EFI_ERROR(Status)){
		PCI_TRACE((TRACE_PCI,"Hb.SetBusNumbers - HbCspUpdateBusesAfter returned ERROR!\n"));
		ASSERT_EFI_ERROR(Status);
		return Status;	
	}
		
    PCI_TRACE((TRACE_PCI,"PciRb#%d: Assigning Buses 0x%lX - 0x%lX \n", i, qw->_MIN, qw->_MIN+qw->_LEN-1));    

		
	rbdata->BusesSet=TRUE;
	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   FreeUsedResources()
//
// Description:
//  Cleans internal RB data and free resources allocated trough GCD.
//  
// Input:
//  PCI_ROOT_BRG_DATA	*RootBrg Pointer to RB Private data.
//
// Output: NONE
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID FreeUsedResources(PCI_ROOT_BRG_DATA	*RootBrg){
	ASLR_QWORD_ASD		*res;
    UINTN               i;
	DXE_SERVICES		*dxe;	
    EFI_STATUS          Status;
//------------------------------
	Status=LibGetDxeSvcTbl(&dxe);
    ASSERT_EFI_ERROR(Status);

	for(i=0; i<RootBrg->ResCount; i++){
		res=RootBrg->RbRes[i];
        
        //Clean only IO and MMIO resources buses was submitted in different call and must stay.
		if(res->Type < ASLRV_SPC_TYPE_BUS){
            if(res->_MIN != 0){
		        //Free IO
		        if(res->Type==ASLRV_SPC_TYPE_IO){
                    Status=dxe->FreeIoSpace(res->_MIN, res->_LEN);
                } else {
                    Status=dxe->FreeMemorySpace(res->_MIN, res->_LEN);
                }
                ASSERT_EFI_ERROR(Status);
            } //res_MIN
            //Don't free resource list, it will be reupdated with RPLACE option.
        }
    } //for

    //Almost done now clean AcpiRbRes[] data
    pBS->SetMem(&RootBrg->AcpiRbRes[0], sizeof(RootBrg->AcpiRbRes),0);
   
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   HbResAllocSubmitResources()
//
// Description:
//  Submits the I/O and memory resource requirements for the specified PCI Root Bridge
//  
// Input:
//  EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL *This  Protocol instance
//  EFI_HANDLE  RootBridgeHandle    PCI Root Bridge to be configured
//  VOID        **Configuration     Pointer to the pointer to the PCI bus resource descriptor
//
// Output: EFI_STATUS
//  EFI_SUCCESS - Success
//  EFI_INVALID_PARAMETER - RootBridgeHandle is invalid
//  EFI_INVALID_PARAMETER - Configuration is NULL
//  EFI_INVALID_PARAMETER - Configuration does not point to a valid ACPI resource descriptor
//  EFI_INVALID_PARAMETER - Configuration includes a resource descriptor of unsupported type
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS HbResAllocSubmitResources(
		IN EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL  		*This,
  		IN EFI_HANDLE                                               RootBridgeHandle,
	  	IN VOID                                                     *Configuration)
{
	PCI_ROOT_BRG_DATA	*rbdata;
	UINTN				i, sz=sizeof(UINT32);
	EFI_STATUS 			Status,AllocStatus;
//    UINT32              mc;     //MemCeil Variable Available?
//    EFI_GUID            gvg	= EFI_GLOBAL_VARIABLE;
   	ASLR_EndTag		    *endtag=(ASLR_EndTag*)Configuration;
//-----------------------------
	if(!Configuration || !This) return EFI_INVALID_PARAMETER;

	rbdata=GetRbByHandle(This,RootBridgeHandle,&i);		
	if(!rbdata) {
		PCI_TRACE((TRACE_PCI,"Hb.SubmitResources - Invalid RB Hndle Passed\n"));
		return EFI_INVALID_PARAMETER;
	}

	//Update Internal data structures with Resource Request
    Status=SetResources(rbdata, Configuration, tResIoMem, TRUE);
	if(EFI_ERROR(Status)){
		PCI_TRACE((TRACE_PCI,"Hb.SubmitResources - Invalid Resoutce Descriptor(s) Passed\n"));
		ASSERT_EFI_ERROR(Status);
		return Status;
	}
    
  
	//Call CSP function to update RB Resources Windows
	Status=HbCspSubmitResources((PCI_HOST_BRG_DATA*)This, rbdata,i);
	if(EFI_ERROR(Status)){
		PCI_TRACE((TRACE_PCI,"Hb.SubmitResources - HbCspSubmitResources return an ERROR!\n"));
		ASSERT_EFI_ERROR(Status);
		return Status;	
	}
	rbdata->ResSubmited=TRUE; //set the FLAG

    //Check if we are able to accomodate resource request 
    //CSP Routine First...
    PCI_TRACE((TRACE_PCI,"PciRb: Calling CSP HbCspAllocateResources() - returned "));        
    AllocStatus=HbCspAllocateResources((PCI_HOST_BRG_DATA*)This, rbdata,i);
    PCI_TRACE((TRACE_PCI,"%r\n", AllocStatus));        
    
    if(EFI_ERROR(AllocStatus)){    
        if( AllocStatus==EFI_UNSUPPORTED ){
            PCI_TRACE((TRACE_PCI,"PciRb: Calling Generic AllocateResources() routine; returned "));
            AllocStatus=AllocateResources(rbdata);
            PCI_TRACE((TRACE_PCI,"%r\n", AllocStatus));        
        }  
        //If custom function Fails or Generic on report it.
        if(EFI_ERROR(AllocStatus)){
            PCI_TRACE((TRACE_PCI,"Hb.SubmitResources - Fail to allocate resources AllocStatus=%r\n",AllocStatus));        
        }
    } else {   
        //Custom function Returned Correct Status:
        //Check if Above 4G Memory was correctly updated by custom function 
        //and if it match with Above4g setup question?
        if((gRbSetupData.Above4gDecode==0) && (rbdata->AcpiRbRes[raMmio64].Len!=0)){
            rbdata->AcpiRbRes[raMmio64].Min=0;
            rbdata->AcpiRbRes[raMmio64].Max=0;
            rbdata->AcpiRbRes[raMmio64].Len=0;
            rbdata->AcpiRbRes[raMmio64].AddrUsed=0;
            rbdata->AcpiRbRes[raMmio64].AllocType=0;
            PCI_TRACE((TRACE_PCI,"PciRB:  PCI Above 4G Decode Setup Settings and Custom Alloc Function Data Mismatched\n"));        
        }
    }
    
    //Check if we can use previoce MRC settings 
    //if(!mc || EFI_ERROR(Status)){ 
    Status = HbCspAdjustMemoryMmioOverlap((PCI_HOST_BRG_DATA*)This, rbdata,i );

	if(EFI_ERROR(Status)){
		PCI_TRACE((TRACE_PCI,"Hb.SubmitResources - AdjustMmioOverlap() returned %r\n",Status));
        //AdjustMmioOverlap() must return SUCCESS or Reset the system...
		ASSERT_EFI_ERROR(Status);
    }

    //Reflecting What TYPE and HOW MUCH of resouces is not enough...
    if(EFI_ERROR(AllocStatus)) {
        ((PCI_HOST_BRG_DATA*)This)->AllocPhase--;
        FreeUsedResources(rbdata);
        Status=AllocStatus;
    }

	if(EFI_ERROR(Status))return Status;

	rbdata->ResAsquired=TRUE; //set the FLAG
		
	return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   HbResAllocGetProposedResources()
//
// Description:
//  This function returns the proposed resource settings for the specified 
//  PCI Root Bridge
//
// Input:
//  EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL *This  Protocol instance
//  EFI_HANDLE  RootBridgeHandle    PCI Root Bridge to be configured
//  VOID        **Configuration     Pointer to the pointer to the PCI bus resource descriptor
//
// Output: EFI_STATUS
//  EFI_SUCCESS - Success
//  EFI_INVALID_PARAMETER - RootBridgeHandle is invalid
//  EFI_DEVICE_ERROR      - Request failed due to hardware error
//  EFI_OUT_OF_RESOURCES  - Request failed due to lack of resources
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS HbResAllocGetProposedResources(
  		IN EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL			*This,
		IN EFI_HANDLE                                              	RootBridgeHandle,
		OUT VOID                                                    **Configuration)
{
/*
	PCI_ROOT_BRG_DATA	*rbdata;
	UINTN				i;
	EFI_STATUS 			Status;
//-----------------------------
	if(!Configuration || !This) return EFI_INVALID_PARAMETER;

	rbdata=GetRbByHandle(This,RootBridgeHandle,&i);		
	if(!rbdata) {
		PCI_TRACE((TRACE_PCI,"Hb.GetProposedResources - Invalid RB Hndle Passed\n"));
		return EFI_INVALID_PARAMETER;
	}

	//Call CSP function to update RB Resources Windows
	Status=HbCspGetProposedResources((PCI_HOST_BRG_DATA*)This, rbdata,i);
	
	if(EFI_ERROR(Status)){
		PCI_TRACE((TRACE_PCI,"Hb.GetProposedResources - HbCspGetProposedResources return an ERROR!\n"));
		ASSERT_EFI_ERROR(Status);
		return Status;	
	}
*/


//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//
//	implement this function
//	
//	
// 
//	
// 
// 
//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//


	return EFI_UNSUPPORTED;	
		
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   HbResAllocPreprocessController()
//
// Description:
//  This function is called for all the PCI controllers that the PCI 
//  bus driver finds. Can be used to Preprogram the controller.
//
//Arguments:
// Input:
//  EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL *This  Protocol instance
//  EFI_HANDLE  RootBridgeHandle    PCI Root Bridge to be configured
//  EFI_PCI_CONFIGURATION_ADDRESS   PciBusAddress   Address of the controller on the PCI bus
//  EFI_PCI_CONTROLLER_RESOURCE_ALLOCATION_PHASE    Phase   The Phase during resource allocation
//    
// Output: EFI_STATUS
//  EFI_SUCCESS - Success
//  EFI_INVALID_PARAMETER - RootBridgeHandle is invalid
//  EFI_DEVICE_ERROR      - Device pre-initialization failed due to hardware error.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS HbResAllocPreprocessController(
		IN EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL  		*This,
		IN EFI_HANDLE                                               RootBridgeHandle,
  		IN EFI_PCI_CONFIGURATION_ADDRESS              				PciAddress,
		IN EFI_PCI_CONTROLLER_RESOURCE_ALLOCATION_PHASE             Phase)
{
//	EFI_STATUS	Status=0;
	UINTN				i;
	PCI_ROOT_BRG_DATA	*rb;
//-----------------------------------		
	rb=GetRbByHandle(This,RootBridgeHandle,&i);
	ASSERT(rb)
	if(!rb) return EFI_INVALID_PARAMETER;
	//Call CSP function...
	return HbCspPreprocessController((PCI_HOST_BRG_DATA*)This,rb,i,PciAddress,Phase);
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SetTmr()
//
// Description:
//  Enables timer event to poll PCI IO and MEMORY.
//
//Arguments:
// Input:
//  UINT64  Delay   Delay value in us
//    
// Output: EFI_EVENT if Success
//  NULL if unable to set timer event. 
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_EVENT SetTmr(UINT64 Delay)
{
	EFI_STATUS	Status;
	EFI_EVENT 	evt;
//--------------------------------------------
	Status=pBS->CreateEvent(EVT_TIMER,TPL_NOTIFY,NULL,NULL,&evt);
	if (EFI_ERROR(Status)) return NULL;


	Status = pBS->SetTimer(evt, TimerRelative, Delay);
	if (EFI_ERROR(Status)){
		pBS->CloseEvent(evt);
		evt=NULL;
	}
	return evt;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   KillTmr()
//
// Description:
//  Disables and Clear timer event to poll PCI IO and MEMORY.
//
//Arguments:
// Input:
//  EFI_EVENT  TmrEvt   Timer event to close.
//    
// Output:  Nothing
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
void KillTmr(EFI_EVENT TmrEvt)
{
	pBS->CloseEvent(TmrEvt);
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:	PollMem
//
// Description:	Poll Memory for a value or until times out.
//
// Input:	IN  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL	*		- This
//			IN  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH	- Memory Width
//			IN  UINT64		- Memory Address
//			IN  UINT64		- Bit Mask
//			IN  UINT64		- Value for exit
//			IN  UINT64		- Timout
//			OUT UINT64 *	- Contents of memory
//
// Output: EFI_STATUS
//		EFI_SUCCESS			- Found value
//		EFI_TIMEOUT			- Did not find value.
//		EFI_INVALID_PARAMETER
//
// Modified:	None
//
// Referrals:	None
//
// Notes:		None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PollMem (
	IN  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL			*This,
	IN  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH	Width,
	IN  UINT64		Address,
	IN  UINT64		Mask,
	IN  UINT64		Value,
	IN  UINT64		Delay,
	OUT UINT64		*Result)
{
	EFI_STATUS	Status;
	EFI_EVENT	Event;

	if (Result==NULL ||((UINTN)Width>=(UINTN)EfiPciWidthFifoUint8)) return EFI_INVALID_PARAMETER;

	Status = PciMemRead(This, Width, Address, 1, Result);	//Read memory at least once.
	if (EFI_ERROR(Status)) return Status;

	if ((*Result & Mask)==Value) return EFI_SUCCESS;			//If correct value, exit.
	if (Delay == 0)	return EFI_TIMEOUT;

	Event=SetTmr(Delay);
	if (!Event) return EFI_NOT_AVAILABLE_YET;

	while(pBS->CheckEvent(Event)==EFI_NOT_READY){
		Status = PciMemRead(This, Width, Address, 1, Result);
		if (EFI_ERROR(Status)) break;
		if ((*Result & Mask)==Value){
			Status = EFI_SUCCESS;
			break;
		} else Status=EFI_TIMEOUT;	//correct value?
	}
	KillTmr(Event);		//Correct value not read, in time alloted.
	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:	PollIo
//
// Description:	Poll IO for a value or until times out.
//
// Input:	IN  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL	*		- This
//			IN  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH	- Memory Width
//			IN  UINT64		- Memory Address
//			IN  UINT64		- Bit Mask
//			IN  UINT64		- Value for exit
//			IN  UINT64		- Timout
//			OUT UINT64 *	- Contents of IO
//
// Output: EFI_STATUS
//		EFI_SUCCESS			- Found value
//		EFI_TIMEOUT			- Did not find value.
//		EFI_INVALID_PARAMETER
//
// Modified:	None
//
// Referrals:	None
//
// Notes:		None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PollIo (
	IN  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL			*This,
	IN  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH	Width,
	IN  UINT64		Address,
	IN  UINT64		Mask,
	IN  UINT64		Value,
	IN  UINT64		Delay,
	OUT UINT64		*Result)
{
	EFI_STATUS	Status;
	EFI_EVENT	Event;

	if (Result==NULL) return EFI_INVALID_PARAMETER;
	if ((UINTN)Width >= (UINTN)EfiPciWidthFifoUint8) return EFI_INVALID_PARAMETER;


	Status = PciIoRead(This, Width, Address, 1, Result);	//Read memory at least once.
	if (EFI_ERROR(Status)) return Status;

	if ((*Result & Mask)==Value) return EFI_SUCCESS;			//If correct value, exit.
	if (Delay == 0)	return EFI_TIMEOUT;

	Event=SetTmr(Delay);
	if (!Event) return EFI_NOT_AVAILABLE_YET;

	while(pBS->CheckEvent(Event)==EFI_NOT_READY){
		Status = PciIoRead(This, Width, Address, 1, Result);
		if (EFI_ERROR(Status)) break;
		if ((*Result & Mask)==Value){
			Status = EFI_SUCCESS;
			break;
		} else Status=EFI_TIMEOUT;	//correct value?
	}
	KillTmr(Event);		//Correct value not read, in time alloted.
	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:	PciMemRead
//
// Description:	Read memory IO into buffer.
//
// Input:	IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL	*		- This
//			IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH	- Memory Width
//			IN UINT64		- Memory Address
//			IN UINTN		- Number of width reads.
//			IN OUT VOID *	- Buffer where memory is read into.
//
// Output: EFI_STATUS
//		EFI_SUCCESS			- Successful read.
//		EFI_INVALID_PARAMETER
//
// Modified:	None
//
// Referrals:	None
//
// Notes:		None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PciMemRead (
IN     EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL        *This,
IN     EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH  Width,
IN     UINT64		Address,
IN     UINTN		Count,
IN OUT VOID			*Buffer)
{
	UINTN	IncrementType		= Width & ~3;
	UINT8	IncrementValue		= 1 << (Width & 3); //1st 2 bits currently define width. Other bits define type.
	UINT8	IncrementBuffer		= 0;
	UINT8	IncrementAddress	= 0;

	if (Buffer==NULL || ((UINTN)Width>=(UINTN)EfiPciWidthMaximum)) return EFI_INVALID_PARAMETER;
	if (IncrementType > 16 || IncrementValue > 8) return EFI_INVALID_PARAMETER;

    if(sizeof(UINTN)==8){
	    if (( 0xffffffffffffffff - Count * IncrementValue) <= Address)
			return EFI_INVALID_PARAMETER;						
    } else {
	    if ((Address + Count * IncrementValue) > 0xffffffff)
			return EFI_INVALID_PARAMETER;						
    }

	switch (IncrementType)
	{
	case 0:	//EfiPciWidthUintxx
		IncrementAddress = IncrementBuffer = IncrementValue;
		break;
	case 4: //EfiPciWidthFifoUintxx
		IncrementBuffer = IncrementValue;
		break;
	default: //EfiPciWidthFillUintxx
		IncrementAddress = IncrementValue;
	}

	while(Count--)
	{
		switch(IncrementValue)
		{
		case 1:		//byte
			*(UINT8*) Buffer = *(UINT8*)Address;
			break;
		case 2:		//word
			*(UINT16*) Buffer = *(UINT16*)Address;
			break;
		case 4: 	//dword
			*(UINT32*) Buffer = *(UINT32*)Address;
			break;		
		case 8:	//dword
			*(UINT64*) Buffer = *(UINT64*)Address;
			break;
		default: return EFI_INVALID_PARAMETER;
		}
		(UINT8*) Buffer += IncrementBuffer;
		Address += IncrementAddress;
	}

	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:	PciMemWrite
//
// Description:	Write memory IO from buffer.
//
// Input:	IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL	*		- This
//			IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH	- Memory Width
//			IN UINT64		- Memory Address
//			IN UINTN		- Number of width writes.
//			IN OUT VOID *	- Buffer where memory is written from.
//
// Output: EFI_STATUS
//		EFI_SUCCESS			- Successful write.
//		EFI_INVALID_PARAMETER
//
// Modified:	None
//
// Referrals:	None
//
// Notes:		None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PciMemWrite (
IN     EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL        *This,
IN     EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH  Width,
IN     UINT64		Address,
IN     UINTN		Count,
IN OUT VOID			*Buffer)
{
	UINTN	IncrementType		= Width & ~3;
	UINT8	IncrementValue		= 1 << (Width & 3); //1st 2 bits currently define width. Other bits define type.
	UINT8	IncrementBuffer		= 0;
	UINT8	IncrementAddress	= 0;

	if (Buffer==NULL || ((UINTN)Width>=(UINTN)EfiPciWidthMaximum)) return EFI_INVALID_PARAMETER;
	if (IncrementType > 16 || IncrementValue > 8) return EFI_INVALID_PARAMETER;

	if ((Address + Count * IncrementValue) > 0xffffffff)
			return EFI_INVALID_PARAMETER;						//Memory must be within range of the bridge.

	switch (IncrementType)
	{
	case 0:	//EfiPciWidthUintxx
		IncrementAddress = IncrementBuffer = IncrementValue;
		break;
	case 4: //EfiPciWidthFifoUintxx
		IncrementBuffer = IncrementValue;
		break;
	default: //EfiPciWidthFillUintxx
		IncrementAddress = IncrementValue;
	}

	while(Count--)
	{
		switch(IncrementValue)
		{
		case 1:		//byte
			*(UINT8*) Address = *(UINT8*)Buffer;
			break;
		case 2:		//word
			*(UINT16*) Address = *(UINT16*)Buffer;
			break;
		case 4:	//dword
			*(UINT32*) Address = *(UINT32*)Buffer;
			break;
		case 8:	//dword
			*(UINT64*) Address = *(UINT64*)Buffer;
			break;
		default: return EFI_INVALID_PARAMETER;
		}
		(UINT8*) Buffer += IncrementBuffer;
		Address += IncrementAddress;
	}

	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:	PciIoRead
//
// Description:	Read IO into buffer.
//
// Input:	
//  IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL	*		- This
//  IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH	- Io Width
//  IN UINT64		- Io Address
//  IN UINTN		- Number of width reads.
//  IN OUT VOID *	- Buffer where Io is read into.
//
// Output: EFI_STATUS
//		EFI_SUCCESS - Successful read.
//		EFI_INVALID_PARAMETER
//
// Modified:	None
//
// Referrals:	None
//
// Notes:		None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PciIoRead (
IN     EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL        *This,
IN     EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH  Width,
IN     UINT64		Address,
IN     UINTN		Count,
IN OUT VOID			*Buffer)
{
	UINTN	IncrementType		= Width & ~3;
	UINT8	IncrementValue		= 1 << (Width & 3); //1st 2 bits currently define width. Other bits define type.
	UINT8	IncrementBuffer		= 0;
	UINT8	IncrementAddress	= 0;

	if (Buffer==NULL || ((UINTN)Width>=(UINTN)EfiPciWidthMaximum)) return EFI_INVALID_PARAMETER;
	if (IncrementType > 16 || IncrementValue > 8) return EFI_INVALID_PARAMETER;

	if ((Address + Count * IncrementValue) > 0xffff)
			return EFI_INVALID_PARAMETER;						//Memory must be within range of the bridge.

	switch (IncrementType)
	{
	case 0:	//EfiPciWidthUintxx
		IncrementAddress = IncrementBuffer = IncrementValue;
		break;
	case 4: //EfiPciWidthFifoUintxx
		IncrementBuffer = IncrementValue;
		break;
	default: //EfiPciWidthFillUintxx
		IncrementAddress = IncrementValue;
	}

	while(Count--)
	{
		switch(IncrementValue)
		{
		case 1:		//byte
			*(UINT8*) Buffer = IoRead8((UINT16)Address);
			break;
		case 2:		//word
			*(UINT16*) Buffer = IoRead16((UINT16)Address);
			break;
		case 4:	//dword
			*(UINT32*) Buffer = IoRead32((UINT16)Address);
			break;
		case 8:
			*(UINT32*) Buffer = IoRead32((UINT16)Address);
			*((UINT32*)((UINT32*)Buffer+1)) = IoRead32((UINT16)(Address+4));
			break;
		default: return EFI_INVALID_PARAMETER;
		}
		(UINT8*) Buffer += IncrementBuffer;
		Address += IncrementAddress;
	}

	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:	PciIoWrite
//
// Description:	Write IO from buffer.
//
// Input:
//  IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL  *This   Protocol instance
//  IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH    Width   Pci Width
//  IN UINT64       Address     IO Address
//  IN UINTN        Count       Number of width writes.
//  IN OUT VOID     *Buffer     where Pci registers are written from.
//
// Output: EFI_STATUS
//  EFI_SUCCESS - Successful write.
//  EFI_INVALID_PARAMETER
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PciIoWrite (
	IN     EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL        *This,
	IN     EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH  Width,
	IN     UINT64		Address,
	IN     UINTN		Count,
	IN OUT VOID			*Buffer)
{
	UINTN	IncrementType		= Width & ~3;
	UINT8	IncrementValue		= 1 << (Width & 3); //1st 2 bits currently define width. Other bits define type.
	UINT8	IncrementBuffer		= 0;
	UINT8	IncrementAddress	= 0;

	if (Buffer==NULL || ((UINTN)Width>=(UINTN)EfiPciWidthMaximum)) return EFI_INVALID_PARAMETER;
	if (IncrementType > 16 || IncrementValue > 4) return EFI_INVALID_PARAMETER;

	if ((Address + Count * IncrementValue) > 0xffff)
			return EFI_INVALID_PARAMETER;						//Memory must be within range of the bridge.

	switch (IncrementType)
	{
	case 0:	//EfiPciWidthUintxx
		IncrementAddress = IncrementBuffer = IncrementValue;
		break;
	case 4: //EfiPciWidthFifoUintxx
		IncrementBuffer = IncrementValue;
		break;
	default: //EfiPciWidthFillUintxx
		IncrementAddress = IncrementValue;
	}

	while(Count--)
	{
		switch(IncrementValue)
		{
		case 1:		//byte
			 IoWrite8((UINT16)Address,*(UINT8*) Buffer);
			break;
		case 2:		//word
			 IoWrite16((UINT16)Address,*(UINT16*) Buffer);
			break;
		default:	//dword
			 IoWrite32((UINT16)Address,*(UINT32*) Buffer);
			break;
		}
		(UINT8*) Buffer += IncrementBuffer;
		Address += IncrementAddress;
	}

	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:	CopyMem
//
// Description:	Copy PCI memory to PCI memory in bridge.
//
// Input:
//  IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL  *This   Protocol instance
//  IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH    Width   Pci Width
//  IN UINT64       DestAddress  Pci Address
//  IN UINT64       SrcAddress  Pci Address
//  IN UINTN        Count       Number of width writes.
//  IN OUT VOID     *Buffer     where Pci registers are written from.
//
// Output: EFI_STATUS
//  EFI_SUCCESS - Successful copy.
//  EFI_INVALID_PARAMETER
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS CopyMem (
	IN  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL			*This,
	IN  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH	Width,
	IN  UINT64									DestAddress,
	IN  UINT64									SrcAddress,
	IN  UINTN									Count)
{
	INTN	IncrementValue;

	if ((SrcAddress == 0) || (DestAddress==0)) return EFI_INVALID_PARAMETER;
	if	((UINTN)Width > (UINTN)EfiPciWidthUint64) return EFI_INVALID_PARAMETER;

	IncrementValue = (INTN)1<<(Width&3);
	if ((SrcAddress + Count * IncrementValue) > 0xffffffff)
			return EFI_INVALID_PARAMETER;						//Memory must be within range of the bridge.

	if ((DestAddress + Count * IncrementValue) > 0xffffffff)
			return EFI_INVALID_PARAMETER;						//Memory must be within range of the bridge.


	if	(SrcAddress==DestAddress) return EFI_SUCCESS;			//Nothing to do.


	if ( (DestAddress > SrcAddress) && (SrcAddress + Count * IncrementValue) ) {
		SrcAddress += (Count-1) * IncrementValue;		//End of source
		DestAddress += (Count-1) * IncrementValue;		//End of destination
		IncrementValue = -IncrementValue;				//Count backwards.
	}	//If Destination addres and after and overlapps Source Address, Copy backwards.

	switch(IncrementValue)
	{
	case 1:
    case -1:
		while (Count--)
		{
			*(UINT8*) DestAddress = *(UINT8*)SrcAddress;
			SrcAddress += IncrementValue;
			DestAddress += IncrementValue;
		}
		break;
	case 2:
    case -2:
		while (Count--)
		{
			*(UINT16*) DestAddress = *(UINT16*)SrcAddress;
			SrcAddress += IncrementValue;
			DestAddress += IncrementValue;
		}
		break;
	default:
		while (Count--)
		{
			*(UINT32*) DestAddress = *(UINT32*)SrcAddress;
			SrcAddress += IncrementValue;
			DestAddress += IncrementValue;
		}
		break;
	}
	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   PciRead()
//
// Description:
//  Read Pci registers into buffer.
//
// Input:
//  IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL  *This   Protocol instance
//  IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH    Width   Pci Width
//  IN UINT64       Address  Pci Address
//  IN UINTN        Count       Number of width writes.
//  IN OUT VOID     *Buffer     where Pci registers are written from.
//
// Output: EFI_STATUS
//  EFI_SUCCESS - Successful read.
//  EFI_INVALID_PARAMETER
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PciRead (
	IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL        *This,
	IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH  Width,
	IN UINT64		Address,
	IN UINTN		Count,
	IN OUT VOID		*Buffer)
{
	PCI_ROOT_BRG_DATA	*Private = (PCI_ROOT_BRG_DATA*)This;

	if (Buffer == NULL ||((UINTN)Width>=(UINTN)EfiPciWidthMaximum) ) return EFI_INVALID_PARAMETER;

	return RootBridgeIoPciRW (Private, Width, Address, Count, Buffer, FALSE);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   PciWrite()
//
// Description:
//  Write Pci registers from buffer.
//
// Input:
//  IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL  *This   Protocol instance
//  IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH    Width   Pci Width
//  IN UINT64       Address  Pci Address
//  IN UINTN        Count       Number of width writes.
//  IN OUT VOID     *Buffer     where Pci registers are written from.
//
// Output: EFI_STATUS
//  EFI_SUCCESS - Successful write.
//  EFI_INVALID_PARAMETER
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PciWrite (
	IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL        *This,
	IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH  Width,
	IN UINT64		Address,
	IN UINTN		Count,
	IN OUT VOID		*Buffer)
{
	PCI_ROOT_BRG_DATA	*Private = (PCI_ROOT_BRG_DATA*)This;

	if (Buffer == NULL || ((UINTN)Width>=(UINTN)EfiPciWidthMaximum)) return EFI_INVALID_PARAMETER;

	Private = (PCI_ROOT_BRG_DATA *) This;

	return RootBridgeIoPciRW (Private, Width, Address, Count, Buffer, TRUE);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   Map()
//
// Description: 
//  Provide addresses required to access system memory from a DMA
//  bus master.
//
// Input:
//  IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL      *This
//  IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_OPERATION    Operation
//  IN VOID         *HostAddress        Host address
//  IN OUT UINTN    **NumberOfBytes     Number of bytes
//  OUT EFI_PHYSICAL_ADDRESS    *DeviceAddress  Device Address
//  OUT VOID        **Mapping
//
// Output: EFI_STATUS
//		EFI_SUCCESS											- Successful map
//
// Modified:	None
//
// Referrals:	None
//
// Notes:		None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS Map (
	IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL    *This,
	IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_OPERATION    Operation,
	IN VOID                         *HostAddress,
	IN OUT UINTN                    *NumberOfBytes,
	OUT EFI_PHYSICAL_ADDRESS        *DeviceAddress,
	OUT VOID                        **Mapping)
{
    EFI_STATUS					Status;
//	PCI_ROOT_BRIDGE_MAPPING		*mapping;
	EFI_PHYSICAL_ADDRESS		addr;
//-------------------------------------------------

	if ( !HostAddress || !NumberOfBytes || !DeviceAddress || !Mapping )
		return EFI_INVALID_PARAMETER;

	if ((UINT32)Operation >= (UINT32)EfiPciOperationMaximum ) return EFI_INVALID_PARAMETER;

	*Mapping=NULL;

	addr=(EFI_PHYSICAL_ADDRESS) (UINTN) HostAddress;

	if ((addr + *NumberOfBytes) > 0xffffffff)Status=RbCspIoPciMap((PCI_ROOT_BRG_DATA*)This,
		Operation, addr, NumberOfBytes, DeviceAddress, Mapping);
	else *DeviceAddress = addr;

	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:	Unmap
//
// Description:	Remove mapping
//
// Input:	
//  IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL  *This   Protocol Instance
//	IN VOID         *Mapping        Pointer to Mapping formation to Unmap
//
// Output: EFI_STATUS
//  EFI_SUCCESS - Successful unmapping.
//  EFI_INVALID_PARAMETER
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS Unmap (
	IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL  *This,
	IN VOID		*Mapping)

{
	EFI_STATUS	Status=EFI_SUCCESS;
	PCI_ROOT_BRIDGE_MAPPING	*mapping=(PCI_ROOT_BRIDGE_MAPPING*)Mapping;
//-------

	if (mapping!=NULL) Status=RbCspIoPciUnmap((PCI_ROOT_BRG_DATA*)This,mapping);
	
	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:	AllocateBuffer
//
// Description:	Allocate buffer for PCI use.
//
// Input:
//  IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL  *This   Protocol Instance
//  IN EFI_ALLOCATE_TYPE    Type        Alloocation Type (ignored and uses AllocateMaxAddress)
//  IN EFI_MEMORY_TYPE      MemoryType  Memory Type (ex. EfiBootServicesData)
//  IN UINTN                Pages       Number of pages to allocate.
//  OUT VOID                **HostAddress   Host Address
//  IN UINT64               Attributes  Allocation Attributes.
//
// Output: EFI_STATUS
//  EFI_SUCCESS - Successful allocation.
//  EFI_UNSUPPORTED	- Attribute not supported.
//  EFI_INVALID_PARAMETER
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
#define BUFF_ATTR 	(EFI_PCI_ATTRIBUTE_MEMORY_WRITE_COMBINE |\
					EFI_PCI_ATTRIBUTE_MEMORY_CACHED |\
					EFI_PCI_ATTRIBUTE_DUAL_ADDRESS_CYCLE)
//---------------------------------------------------------------
EFI_STATUS AllocateBuffer (
	IN  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL  *This,
	IN  EFI_ALLOCATE_TYPE	Type,
	IN  EFI_MEMORY_TYPE		MemoryType,
	IN  UINTN				Pages,
	OUT VOID				**HostAddress,
	IN  UINT64				Attributes)

{
	//PCI_ROOT_BRIDGE_STRUCT	*Private = (PCI_ROOT_BRIDGE_STRUCT	*)This;

	EFI_STATUS				Status;
	EFI_PHYSICAL_ADDRESS	addr;

	if (HostAddress == NULL) return EFI_INVALID_PARAMETER;

	// The only valid memory types are EfiBootServicesData and EfiRuntimeServicesData
	if (MemoryType != EfiBootServicesData && MemoryType != EfiRuntimeServicesData)
		return EFI_INVALID_PARAMETER;

	//Check if legal Attributes for this function is passed
	//Check if any other Attributes set except supported
	if( Attributes & ~BUFF_ATTR ) return EFI_UNSUPPORTED;


	//865 chipset does not support any of Attributes above so as spec. says ignore it
	//and Allocate buffer
	// Limit allocations to memory below 4GB
	addr = 0xffffffff;

	Status = pBS->AllocatePages (AllocateMaxAddress, MemoryType, Pages, &addr);
	if (EFI_ERROR(Status)) return Status;

	*HostAddress = (VOID *)(UINTN)addr;
	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:	FreeBuffer()
//
// Description:	Frees buffer
//
// Input:	IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL	*This   Protocol Instance
//			IN UINTN    Pages           Number of pages to free.
//			IN VOID*    HostAddress     Host Address
//
// Output: EFI_STATUS
//		EFI_SUCCESS	- Successful free.
//		EFI_INVALID_PARAMETER
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS FreeBuffer (
	IN  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL  *This,
	IN  UINTN		Pages,
	IN  VOID		*HostAddress)

{
	return pBS->FreePages((EFI_PHYSICAL_ADDRESS) HostAddress, Pages);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   Flush()
//
// Description:	
//  Flush buffer used by PCI DMA Transfere.
//
// Input:
//  IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL	*This   Protocol Instance
//
// Output: EFI_STATUS
//  EFI_SUCCESS - Successful flushing
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS Flush (IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *This)
{
	return EFI_SUCCESS;		//Doesn't need buffer to be flushed.
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:	GetAttributes()
//
// Description:	Get Supported and Current Root Bridge Attributes.
//
// Input:
//  IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL	*This Protocol Instance
//  OUT UINT64      *Supported      Supported Attributes
//	OUT UINT64      *Attributes     Current Attributes
//
// Output: EFI_STATUS
//  EFI_SUCCESS - Successful reading attributes.
//  EFI_INVALID_PARAMETER - If both for attributes are invalid.
//
// Notes:		None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS GetAttributes (
	IN  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL  *This,
	OUT UINT64	*Supported,
	OUT UINT64	*Attributes)
{
	PCI_ROOT_BRG_DATA	*Private = (PCI_ROOT_BRG_DATA*) This;

	if (Attributes == NULL && Supported == NULL) return EFI_INVALID_PARAMETER;

	if (Supported) *Supported  = Private->Supports;
	if (Attributes) *Attributes = Private->Attributes;

	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   GetAttributes()
//
// Description:	Get Supported and Current Root Bridge Attributes.
//
// Input:
//  IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL	*This Protocol Instance
//  IN UINT64       Attributes
//  IN OUT UINT64   *ResourceBase   Resource Base (optional, unused)
//  IN OUT UINT64   *ResourceLength Resource Length (optional, unused)
//
// Output: EFI_STATUS
//  EFI_SUCCESS     Successful setting attributes.
//  EFI_UNSUPPORTED Unsupported attributes
//
// Notes:		None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS SetAttributes (
	IN     EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL  *This,
	IN     UINT64	Attributes,
	IN OUT UINT64	*ResourceBase,
	IN OUT UINT64	*ResourceLength)
{
	EFI_STATUS			Status;
	PCI_ROOT_BRG_DATA	*Private  = (PCI_ROOT_BRG_DATA *) This;
//------------------------------------
	

	//First Check if RB supports passed Attributes
	if((Attributes & Private->Supports)!=Attributes)return EFI_UNSUPPORTED;

	//Note: Only some attributes can be both enabled and disabled.

	Status=RbCspIoPciAttributes(Private, Attributes, ResourceBase, ResourceLength);
	
	if(EFI_ERROR(Status)) return Status;	

	//Update the attributes property
	//Private->Attributes&=Attributes; //reset all bits that has to be reseted
	Private->Attributes |= Attributes; //set bits that has to be seted

	return Status;
}
//--------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:	Configuration()
//
// Description:	Returns, using ACPI 2.0 Descriptors, resources allocated.
//
// Input:	IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL  *This
//			IN VOID                             *Resources
//
// Output: EFI_STATUS
//		EFI_SUCCESS	
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS Configuration (
	IN     EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL	*This,
	OUT    VOID								**Resources)
{
	PCI_ROOT_BRG_DATA	*rb=(PCI_ROOT_BRG_DATA*)This;
	EFI_STATUS			Status=0;
//---------------------
	if(rb->ResAsquired)	
		Status=GetResources((PCI_ROOT_BRG_DATA*)This, (ASLR_QWORD_ASD**)Resources, tResAll);
	else Status=EFI_NOT_AVAILABLE_YET;
	return Status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:	PciRw()
//
// Description:	Provides Read and Write access to the PCI Configuration Space.
//
// Input:	
//  IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL  *This   Protocol Instance
//  IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH    Width   Data Width.
//  IN UINT64   Address     PCI Config Address
//  IN UINT32   Mask        Mask for the bits to be preserved
//  IN UINT32   Value       Data to be written
//
// Output: EFI_STATUS
//  EFI_SUCCESS	- OK
//  EFI_DEVICE_ERROR - HW ERROR
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID PciRw (
	IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL			*This,
	IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH	Width,
	IN UINT64	Address,
	IN UINT32	Mask,
	IN UINT32	Value
	)
{
	EFI_STATUS Status;
	UINT32	Data;

	Status = This->Pci.Read (This,Width,Address,1,&Data);
	ASSERT_EFI_ERROR (Status);

	Data = (Data & Mask) | Value;
	Status = This->Pci.Write (This,Width,Address,1,&Data);
	ASSERT_EFI_ERROR (Status);
} 




//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
