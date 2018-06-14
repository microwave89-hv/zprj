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
// $Header: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Core/CORE_DXE/GenericSio.c 1     7/15/14 9:53p Chienhsieh $
//
// $Revision: 1 $Date: 4/04/05 4:37p $
//
//*****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Core/CORE_DXE/GenericSio.c $
// 
// 1     7/15/14 9:53p Chienhsieh
// Update rev.83 for EIP172950, Core updates for UEFI Variable Technical
// Advisory implement.
// 
// 83    6/26/14 6:27p Artems
// [TAG]  		EIP N/A
// [Category]  	Improvement
// [Description]  	Removed Runtime-Access attribute from internal SIO
// variables
// [Files]  		GenericSio.c
// 
// 82    2/13/13 5:29p Yakovlevs
// [TAG]  		EIP109638 
// [Category]  	Improvement
// [Description]  	Unpexetced behavior in AmiSioStart().
// Keep calling InitSio instead of breking the execution. 
// [Files]  		GenericSio.c
// 
// 81    7/20/12 2:42p Yakovlevs
// Fixing Reconnect issue in case of multiple SIO.
// 
// 80    2/09/12 12:40p Yakovlevs
// [TAG]  		EIP82016 
// [Category]  	Bug Fix
// [RootCause]  	incorrect _ALG handling in ApplyIoRes() function.
// [Solution]  	Change expression in "if" statement to correctly reflect
// _ALG operation.
// [Files]  		GenericSio.c
// 
// 79    11/08/11 11:15a Yakovlevs
// [TAG]  		EIP72716 
// [Category]  	Improvement
// [Description]  	Added Messages, Fixed issues in proposed by AMI China
// solution.
// [Files]  		GenericSio.c
// 
// 78    10/28/11 6:18p Yakovlevs
// [TAG]  		EIP72716 
// [Category]  	Improvement
// [Description]  	Improvement for GenericSio.c
// [Files]  		GenericSio.c
// 
// 77    8/12/11 12:20p Artems
// EIP 64107: Added changes for module to be compliant with UEFI
// specification v 2.3.1
// 
// 76    5/06/11 5:08p Yakovlevs
// Made depencency on PI_SPECIFICATIO_VERSION tolen
// 
// 75    5/04/11 6:03p Yakovlevs
// [TAG]  		EIP 56527
// [Category]  	New Feature
// [Description]  	AMI_SIO_PROTOCOL was the source for PI 1.2 spec
// proposal. Will require some minor modification of the interface plus
// adding EFI_SIO_PROTOCOL Modify() function.
// [Files]  		GenericSio.h; GenericSio.c.
// 
// 74    4/20/11 4:38p Yakovlevs
// Fixed potential issue in Stop function
// 
// 73    2/25/11 3:17p Artems
// EIP 54041: Renamed function AmiSioEntryPoint to GenericSioEntryPoint
// to avoid dependency from SIO module
// 
// 72    2/05/11 4:13p Artems
// Fixed bug with ellow exclamation mark in Windows when keyboard not
// present
// 
// 71    2/02/11 12:09p Yakovlevs
// [TAG]  		EIPNA
// [Category]  	Improvement
// [Description]  	Removed printing Remaining Device Path since it can
// hung the system
// 
// 67    8/23/10 3:35p Felixp
// Enhancement(EIP 29307): Part of Runtime Trace support. 
// Code is updated to disable serial port 0 based on valueo f the
// HideComPort variable.
// 
// 66    2/04/10 11:51a Oleksiyy
// Minor Fix
// 
// 65    1/26/10 11:17a Yakovlevs
// Bug fix EIP 32086: can't share IRQ when SIO logical devices' IRQ are in
// share mode.
// 
// 64    11/09/09 11:10a Krishnakumarg
// EIP#30571: CloseEvent funtion should be used to kill events in callback
// function.
// 
// 63    10/09/09 5:28p Yakovlevs
// Added Check for NULL pointer returned. 
// 
// 62    10/06/09 6:33p Yakovlevs
// 1.Fixed some minor issues with the Status returned when Starting
// Devices.
// 2. Added Debug Messages Printing Remaining Device Path.
// 
// 61    8/28/09 10:25a Felixp
// Component Name protocol implementation is upadted  to support both 
// ComponentName and ComponentName2 protocols
// (based on value of the EFI_SPECIFICATION_VERSION SDL token).
// 
// 60    8/25/09 6:35p Yakovlevs
// Fixed issue when NONE AUTO IRQ allocation method was used same IRQ may
// be assigned to the different devices.
// 
// 59    12/01/08 10:37a Yakovlevs
// Added isAfterBootScript support. Now SIO initialization routine could
// save 
// Runtime registers using isAfterBootScript initialization Step.
// 
// 58    10/31/08 6:11p Yakovlevs
// Fixed AmiSioStop routine
// 
// 57    10/13/08 4:50p Yakovlevs
// Fixed EIP 16394: ACPI removal causes infinite loop in GenericSio.c
// 
// 56    10/07/08 10:49a Yakovlevs
// Fixed potential issue when GenericSio build with ACPI_SUPPORT == 0
// 
// 55    7/03/08 6:34p Yakovlevs
// Fixed issue when SIO don't have a config mode and Pointers in GSPIO
// structure were initialized with NULLs, it might hung in infinite loop.
// 
// 4     6/06/08 10:29a Yakovlevs
// Take care if SIO_STATUS_VAR might be created by some other drivers
// Don't break if resources used by SIO IDX/DATA reg can not be clamed.
// 
// 54    3/25/08 6:10p Yakovlevs
// Code that creates device's NVRAM variables was acidentally removed.
// Restoring it.
// 
// 53    3/12/08 12:44p Felixp
// Progress/Error codes reporting added
// 
// 52    2/15/08 5:24p Felixp
// 
// 51    2/06/08 5:59p Yakovlevs
// 
// 50    2/06/08 5:19p Yakovlevs
// Added detection if SIO device is actualy present or not.
// 
// 48    10/23/07 10:20a Felixp
// Minor bug fix in AmiSioSupported routine.
// 
// 47    8/16/07 5:48p Yakovlevs
// 
// 46    8/16/07 4:50p Yakovlevs
// Chenges to fix BUILD issues when ACPI_SUPPORT is disabled
// 
// 45    6/12/07 12:07a Yakovlevs
// Fixed issue with SIO device with n o resources.
// 
// 44    5/14/07 7:04p Yakovlevs
// Changes to support SIO Setup Data Override.
// Usefull if SIO uses none  standard Setup Screens and Data Storage.
// 
// 42    3/28/07 7:43p Yakovlevs
// Changes to make use of LibGetDsdt() function
// 
// 41    1/29/07 4:57p Yakovlevs
// Fixed bug with IRQ reservation. Devices with no IRQ requests were
// wrongfully flaged as "Assigned"
// 
// 40    12/28/06 7:18p Yakovlevs
// 
// 39    12/26/06 3:16p Yakovlevs
// Dynamic IRQ Assignment final fix.
// 
// 38    12/22/06 9:42p Yakovlevs
// Fixed Dynamic ISA IRQ Allocation 
// 
// 37    11/27/06 3:56a Yakovlevs
// Set up Notification on VariableWrite protocol to update ISA_IRQ_MASK
// variable
// 
// 36    11/27/06 2:20a Yakovlevs
// 
// 35    11/27/06 12:06a Yakovlevs
// Changes to sinchronize ISA IRQ allocation here and in CSM 
// NOTE will require to change ISA_IRQ_MASK token HAVE free IRQs as 0
// 
// 34    10/12/06 9:42a Felixp
// UEFI2.0 compliance: use CreateReadyToBootEvent instead of CreateEvent
// 
// 33    9/11/06 11:10a Yakovlevs
// 
// 32    8/24/06 10:11a Felixp
// x64 support: warning/error fixes
// 
// 31    8/04/06 6:10p Yakovlevs
// Another fix for x64 SioDevStatusVarAttributes changet to UINT32
// 
// 30    8/04/06 4:06p Yakovlevs
// Fixed data types for x64 from UINN to UINT32 where needed.
// 
// 26    5/24/06 11:39a Yakovlevs
// Fixes to handle shared resources
// 
// 25    5/23/06 5:08a Felixp
// converted to the latest ACPI type definitions
// 
// 24    5/23/06 4:26a Felixp
// Device Path code updated to use NEXT_NODE/NODE_LENGTH/SET_NODE_LENGTH
// macros to remove direct access to the Length field
// 
// 23    4/13/06 7:25p Yakovlevs
// ACPI Disable Support added
// 
// 22    4/10/06 5:29p Yakovlevs
// ACPI NO ACPI mode fix.
// Added Setting LPT device  _PRS in NONE ACPI mode based on current LPT
// MODE (SPP/EPP/ECP) SetLptPrs function.
// Made Set???Prs functions Public(declared in GenericSio.H). 
// 
// 21    4/10/06 10:47a Yakovlevs
// Fixed "IsaVenDevId" and "IsaSubVenId" mask usage.
// 
// 20    4/03/06 3:52p Felixp
// Major changes in PCI and Super I/O:
// PCI - Root Bridge Resource Allocation Sepcification support
// Super I/O - multiple Super I/O support; SIO Setup page added;
// 
// 19    3/13/06 10:07a Felixp
// 
// 17    11/23/05 11:26a Felixp
// dev_status renamed to DEV_STATUS.
// 
// 16    11/18/05 4:27p Ambikas
// Creates/modifies SioDevStatusVar (formerly IOST).
// Dev->Assigned = TRUE/FALSE moved from AssignResources to
// ApplyResources.
// 
// 14    11/07/05 3:06p Felixp
// Unused references to Setup are removed
// 
// 13    11/07/05 11:54a Ambikas
// 
// 12    10/26/05 5:00p Ambikas
// 
// 11    9/29/05 2:51p Robert
// Initialization of Global Variables
// 
// 10    5/18/05 11:02a Yakovlevs
// Changes to Support Generic IO ranges for SIO GPIO, PME and HHM
// 
// 9     5/12/05 9:34a Yakovlevs
// 
// 8     5/11/05 3:05p Yakovlevs
// 
// 7     4/22/05 2:42p Markw
// Only save boot script once.
// 
// 6     4/13/05 6:22p Sivagarn
// - Included proper file header
// - Fixed the bug in programming SIO config space
// 
//
//*****************************************************************************


//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	GenericSio.c
//
// Description:	Generic Implementation of the AMI SIO Protocol.
//
//<AMI_FHDR_END>
//**********************************************************************

#include <Token.h>

#if SIO_SUPPORT
//==================================================================================

#include <Efi.h>
#include <pci.h>
#include <Protocol\AmiSio.h>
#include <Protocol\DevicePath.h>
#include <Protocol\DriverBinding.h>
#include <Protocol\ComponentName2.h>
#include <Protocol\PciIo.h>
#include <Protocol\BootScriptSave.h>
#include <Protocol\VariableWrite.h>
#include <Dxe.h>
#include <AmiDxeLib.h>
#include <GenericSio.h>
#include <AcpiRes.h>

#if ACPI_SUPPORT
//include this if ACPI is Supported
#include <Acpi20.h>
#include <Protocol\AcpiSupport.h>

//
//Some variables we need if ACPI mode is SUPPORTED 
//
ACPI_HDR 	*gPDsdt=NULL;
EFI_EVENT 	mAcpiEvent=NULL;
VOID		*mAcpiReg;
EFI_GUID	gAcpiSupportGuid=EFI_ACPI_SUPPORT_GUID;

#endif

#define _AND_ &
#define SIO_MAX_REG			0xFF

//==================================================================================
//Global Variables
//==================================================================================
//extern SPIO_LIST_ITEM SIO_DEVICE_LIST EndOfList;              // (EIP7580)-
//SPIO_LIST_ITEM	*gSpioList[] = {SIO_DEVICE_PTR_LIST NULL};  // (EIP7580)-
BOOLEAN		mVarWrite=FALSE;
extern  	SPIO_LIST_ITEM      *gSpioList[];                       // (EIP7580)+
extern const BOOLEAN HideComPort;
UINTN		gSpioCount=0;
//global SPIO structure
GSPIO 	 	*gSpio;	
EFI_EVENT	mIsaEvent=NULL;
VOID		*mIsaReg;

//--------------------------------------------------------

static EFI_GUID gEfiAmiSioProtocolGuid 			= EFI_AMI_SIO_PROTOCOL_GUID;
static EFI_GUID gDriverBindingProtocolGuid		= EFI_DRIVER_BINDING_PROTOCOL_GUID;
static EFI_GUID gDevicePathProtocolGuid			= EFI_DEVICE_PATH_PROTOCOL_GUID;
static EFI_GUID gPciIoProtocolGuid				= EFI_PCI_IO_PROTOCOL_GUID;
static EFI_GUID	gEfiBootScriptSaveGuid			= EFI_BOOT_SCRIPT_SAVE_GUID;
static EFI_GUID gDxeSvcTblGuid 					= DXE_SERVICES_TABLE_GUID;
static EFI_GUID gSioDevStatusVarGuid 			= SIO_DEV_STATUS_VAR_GUID;
static EFI_GUID gVariableWriteProtocolGuid		= EFI_VARIABLE_WRITE_ARCH_PROTOCOL_GUID;

//DxeServices table Pointer to get access to the GCD Services
static DXE_SERVICES		*gDxeSvcTbl=NULL;
//Driver Name
static 	UINT16		*gDriverName=L"AMI Generic LPC Super I/O Driver";
//ISA IRQ Mask tells which interrupts we can use for SIO devices
static 	UINT16		gAvailableIsaIrq=0;//=ISA_IRQ_MASK;
// Global variable to report which IRQs are being used in the SIO
static  UINT16      gUsedSioIrq=0;
// Global variable to report which IRQs are requested/reserved in the SIO
static  UINT16      gReservedIrq=0;
//ISA DMA Chanal Mask tells which DMA Chanals we can use for SIO devices
static  UINT8		gAvailableDmaChnl=0;//=ISA_DMA_MASK;//0xEF;

static EFI_EVENT	gEvtReadyToBoot = NULL;

//==================================================================================
//Some Function Prototypes to place Entry point at the beginning of this file 
//==================================================================================
#ifdef EFI_DEBUG
EFI_STATUS DevicePathToStr(EFI_DEVICE_PATH_PROTOCOL *Path,CHAR8	**Str);
#endif
EFI_STATUS EnumerateAll(GSPIO *Spio);

SPIO_DEV* NewDev(SPIO_DEV_LST *SioDevInfo, GSPIO *Owner);
EFI_STATUS SioSetupData(SPIO_DEV *Dev, BOOLEAN Get);

//==================================================================================
//Function Prototypes for Driver Binding Protocol Interface
//==================================================================================
EFI_STATUS AmiSioSupported(IN EFI_DRIVER_BINDING_PROTOCOL	*This,
						   IN EFI_HANDLE                    Controller,
						   IN EFI_DEVICE_PATH_PROTOCOL      *RemainingDevicePath);

EFI_STATUS AmiSioStart(IN EFI_DRIVER_BINDING_PROTOCOL		*This,
					   IN EFI_HANDLE						Controller,
					   IN EFI_DEVICE_PATH_PROTOCOL			*RemainingDevicePath );

EFI_STATUS AmiSioStop(IN EFI_DRIVER_BINDING_PROTOCOL			*This,
					   IN EFI_HANDLE						Controller,
					   IN UINTN								NumberOfChildren,
					   IN EFI_HANDLE						*ChildHandleBuffer);

EFI_STATUS AmiSioComponentNameGetControllerName(IN EFI_COMPONENT_NAME2_PROTOCOL *This,
						IN  EFI_HANDLE                   ControllerHandle,
						IN  EFI_HANDLE                   ChildHandle        OPTIONAL,
						IN  CHAR8                        *Language,
						OUT CHAR16                       **ControllerName );

EFI_STATUS AmiSioComponentNameGetDriverName(IN  EFI_COMPONENT_NAME2_PROTOCOL  *This,
						IN  CHAR8                        *Language,
						OUT CHAR16                       **DriverName);


EFI_STATUS AmiSioRegister(IN AMI_SIO_PROTOCOL	*This,
						IN BOOLEAN				Write,
						IN BOOLEAN				ExitCfgMode,
						IN UINT8            	Register,
    					IN OUT UINT8        	*Value);


EFI_STATUS AmiSioCRS(IN AMI_SIO_PROTOCOL	*This,
				    IN BOOLEAN 				Set,
					IN OUT T_ITEM_LIST		**Resources);

EFI_STATUS AmiSioPRS(IN AMI_SIO_PROTOCOL	*This,
				    IN BOOLEAN 				Set,
					IN OUT T_ITEM_LIST		**Resources);

EFI_STATUS ReserveIrq(SPIO_DEV *Dev, UINTN Index);

static VOID CallbackReadyToBoot(
	IN EFI_EVENT	Event,
	IN VOID			*Context
);




EFI_STATUS CreateSioDevStatusVar();
EFI_STATUS DisableDevInSioDevStatusVar(SPIO_DEV *Dev);
VOID SaveSioRegs(GSPIO *Sio, SPIO_DEV *Dev, UINT8* InclRegList, UINTN InclRegCount, UINT8 *Buffer);
VOID DevSelect(SPIO_DEV *Dev);

#if ACPI_SUPPORT
VOID GetDsdt(IN EFI_EVENT Event, IN VOID *Context);
#endif
VOID UpdateIsaMask(IN EFI_EVENT Event, IN VOID *Context);
//==================================================================================
//Driver binding protocol instance for AmiSio Driver
EFI_DRIVER_BINDING_PROTOCOL gAmiSioDriverBinding = {
	AmiSioSupported,	//Supported
	AmiSioStart,		//PciBusDrvStart,
	AmiSioStop,			//PciBusDrvStop,
	0x10,				//Version,
	NULL,				//Image Handle,
	NULL				//DriverBindingHandle,
};

//==================================================================================
//Component Name Protocol Instance
#ifndef EFI_COMPONENT_NAME2_PROTOCOL_GUID //old Core
#ifndef LANGUAGE_CODE_ENGLISH
#define LANGUAGE_CODE_ENGLISH "eng"
#endif
static BOOLEAN LanguageCodesEqual(
    CONST CHAR8* LangCode1, CONST CHAR8* LangCode2
){
    return    LangCode1[0]==LangCode2[0] 
           && LangCode1[1]==LangCode2[1]
           && LangCode1[2]==LangCode2[2];
}
static EFI_GUID gEfiComponentName2ProtocolGuid = EFI_COMPONENT_NAME_PROTOCOL_GUID;
#endif
EFI_COMPONENT_NAME2_PROTOCOL gAmiSioComponentName = {
  AmiSioComponentNameGetDriverName,
  AmiSioComponentNameGetControllerName,
  LANGUAGE_CODE_ENGLISH
};

//==================================================================================
//Ami SIO Protocol instance
AMI_SIO_PROTOCOL gAmiSioProtocol = {
    AmiSioRegister,
	AmiSioCRS,
	AmiSioPRS,
};

#if ((defined PI_SPECIFICATION_VERSION) && (PI_SPECIFICATION_VERSION >= 0x00010014))
//EFI_SUPERIO_PROTOCOL Functions Forward declaration.
EFI_STATUS EfiSioRegisterAccess(
  IN   CONST  EFI_SIO_PROTOCOL  *This,
  IN          BOOLEAN           Write,
  IN          BOOLEAN           ExitCfgMode,
  IN          UINT8             Register,
  IN OUT      UINT8             *Value);


EFI_STATUS EfiSioGetResourcces( 
  IN  CONST EFI_SIO_PROTOCOL            *This,
  OUT       ACPI_RESOURCE_HEADER_PTR    *ResourceList
);

EFI_STATUS EfiSioSetResources(
  IN CONST  EFI_SIO_PROTOCOL        *This,
  IN        ACPI_RESOURCE_HEADER_PTR ResourceList
);

EFI_STATUS EfiSioPossibleResources(
  IN  CONST EFI_SIO_PROTOCOL         *This,
  OUT       ACPI_RESOURCE_HEADER_PTR *ResourceCollection
);

EFI_STATUS EfiSioModify(
  IN CONST EFI_SIO_PROTOCOL         *This,
  IN CONST EFI_SIO_REGISTER_MODIFY  *Command,
  IN       UINTN                    NumberOfCommands
);


EFI_SIO_PROTOCOL gEfiSioProtocol = {
    EfiSioRegisterAccess,
    EfiSioGetResourcces,
    EfiSioSetResources,
    EfiSioPossibleResources,
    EfiSioModify,
};
#endif

// <AMI_PHDR_START>
//-------------------------------------------------------------------------
//
// Procedure: UpdateIsaMask
//
// Description:
//  This function will update gAvailableIsaIrq &gAvailableDmaChnl value
//
// Input:
//
// Output: 
//
// Notes:
//------------------------------------------------------------------------- 
// <AMI_PHDR_END> 
VOID UpdateIsaMask(IN EFI_EVENT Event, IN VOID *Context){
	EFI_STATUS		Status;
#if ACPI_SUPPORT
	SPIO_DEV		*dev;
	UINTN			j;
#endif
	UINTN			i;
//-------------------------

	SIO_TRACE((TRACE_SIO,"GSIO: Variable Write Available!\n"));	
	Status = AmiIsaIrqMask(&gAvailableIsaIrq, TRUE);
	if(Status==EFI_NOT_FOUND){
		gAvailableIsaIrq=ISA_IRQ_MASK;
		SIO_TRACE((TRACE_SIO,"GSIO: Get ISA_IRQ_MASK Status=%r Updating with DEFAULT %X\n",Status, gAvailableIsaIrq));
		Status = AmiIsaIrqMask(&gAvailableIsaIrq, FALSE);
	}
	if(EFI_ERROR(Status)){
		SIO_TRACE((TRACE_SIO,"GSIO: ERROR Updating ISA_IRQ_MASK Status=%r\n",Status));
		gAvailableIsaIrq=ISA_IRQ_MASK;
	}

	Status = AmiIsaDmaMask(&gAvailableDmaChnl, TRUE);
	if(Status==EFI_NOT_FOUND){
		gAvailableDmaChnl=ISA_DMA_MASK;
		SIO_TRACE((TRACE_SIO,"GSIO: Get ISA_DMA_MASK Status=%r Updating with DEFAULT %X\n",Status, gAvailableDmaChnl));
		Status=AmiIsaDmaMask(&gAvailableDmaChnl, FALSE);
	}

	if(EFI_ERROR(Status)){
		SIO_TRACE((TRACE_SIO,"GSIO: ERROR Updating ISA_DMA_MASK Status=%r\n",Status));
		gAvailableDmaChnl=ISA_DMA_MASK;
	}

	mVarWrite=TRUE;

	//ACPI Support was Installed Before VariableWrite Protocol
	//So we have collected SIOs _PRS info but did not reserve IRQs yet!
    SIO_TRACE((TRACE_SIO,"=================================================\n"));
#if ACPI_SUPPORT
	if(gPDsdt!=NULL){
		for(i=0;i<gSpioCount;i++){
    		SIO_TRACE((TRACE_SIO,"GSIO: (ACPI Mode) Enumerate SIO Chip # %d >>>>> \n",i));
			for(j=0; j<gSpio[i].DeviceCount; j++){
				dev=gSpio[i].DeviceList[j];
		        if(dev->DeviceInfo->HasSetup) {
					Status=SioSetupData(dev,TRUE);
					SIO_TRACE((TRACE_SIO,"GSIO: Get SIO Setup Data. Status=%r\n",Status));
					ASSERT_EFI_ERROR(Status);
				}
				//Taking care of issue 1 in EIP72716 
		        if(!dev->DeviceInfo->Implemented) continue;
				//For Irq reservation it might be a disabled by setup device that shares it's resources
				//It appears to be a resource owner in such case it will have field Resource consumer filled.
				if(!dev->NvData.DevEnable) if(dev->ResConsumer==NULL) continue;
				Status=ReserveIrq(dev, j);				
				SIO_TRACE((TRACE_SIO,"GSIO: Reserve IRQ for SIO[%d].Device[%d] - Status=%r\n",i,j,Status));
			}
 			SIO_TRACE((TRACE_SIO,"GSIO: (ACPI Mode) EnumerateAll for SIO Chip # %d -> Status=%r\n\n",i, Status));
		}
	}
#else
	//Set the Possible Resources for each implemented device
	for(i=0;i<gSpioCount;i++){

		SIO_TRACE((TRACE_SIO,"GSIO: (NO ACPI Mode) Enumerate SIO Chip # %d >>>>> \n",i));
		Status=EnumerateAll(&gSpio[i]);	
		SIO_TRACE((TRACE_SIO,"GSIO: (NO ACPI Mode) EnumerateAll for SIO Chip # %d -> Status=%r\n\n",i, Status));
	}
	//install driver binding protocol here ....
	Status = pBS->InstallMultipleProtocolInterfaces(
					&gAmiSioDriverBinding.DriverBindingHandle,
					&gDriverBindingProtocolGuid,&gAmiSioDriverBinding,
					&gEfiComponentName2ProtocolGuid, &gAmiSioComponentName,
					NULL,NULL);

#endif
	if(Event) {
		Status=pBS->CloseEvent(Event);
		Event=NULL;	
	}
}

// <AMI_PHDR_START>
//-------------------------------------------------------------------------
//
// Procedure: GenericSioEntryPoint
//
// Description:
//  This is Dxe init Entrypoint 
//
// Input:
//
// Output: 
//
// Notes:
//------------------------------------------------------------------------- 
// <AMI_PHDR_END> 
EFI_STATUS AmiSioEntryPoint(
    IN EFI_HANDLE		ImageHandle,
	IN EFI_SYSTEM_TABLE *SystemTable )
{
    return EFI_SUCCESS;
}

EFI_STATUS GenericSioEntryPoint(
    IN EFI_HANDLE		ImageHandle,
	IN EFI_SYSTEM_TABLE *SystemTable )
{
  	EFI_STATUS		Status=0;
	UINTN			i,j;
	SPIO_DEV		*ro=NULL, *dev;//resource owner
	SPIO_LIST_ITEM	*sioli;
	GSPIO			*gspio;
//--------------------------------------------------------------------
	InitAmiLib(ImageHandle, SystemTable);

	gDxeSvcTbl=(DXE_SERVICES*)GetEfiConfigurationTable(SystemTable,&gDxeSvcTblGuid);
	
	//Fill ImgHandle Field in Driver Binding Protocol Structure
	gAmiSioDriverBinding.ImageHandle=ImageHandle;
	gAmiSioDriverBinding.DriverBindingHandle=NULL;


	//Here we try to find a Variable for IRQ and DMA mask 
	Status = AmiIsaIrqMask(&gAvailableIsaIrq, TRUE);
	//if Variable does not exists we create one
	if(EFI_ERROR(Status)){
		if(Status==EFI_NOT_FOUND) {
			gAvailableIsaIrq=ISA_IRQ_MASK;
		  	Status=AmiIsaIrqMask(&gAvailableIsaIrq, FALSE);
			if(EFI_ERROR(Status))SIO_TRACE((TRACE_SIO, "GSIO: Unexpected Error while creating Var ISA_IRQ_MASK. STATUS = %r\n", Status));
			else mVarWrite=TRUE;
		} else SIO_TRACE((TRACE_SIO, "GSIO: Unexpected Error while getting var ISA_IRQ_MASK. STATUS = %r\n", Status));
	} else mVarWrite=TRUE;

	Status = AmiIsaDmaMask(&gAvailableDmaChnl, TRUE);
	//if Variable does not exists we create one
	if(EFI_ERROR(Status)){
		if(Status==EFI_NOT_FOUND) {
			gAvailableDmaChnl=ISA_DMA_MASK;
		  	Status=AmiIsaDmaMask(&gAvailableDmaChnl, FALSE);
			if(EFI_ERROR(Status))SIO_TRACE((TRACE_SIO, "GSIO: Unexpected Error while creating Var ISA_DMA_MASK. STATUS = %r\n", Status));
		} else SIO_TRACE((TRACE_SIO, "GSIO: Unexpected Error while getting var ISA_DMA_MASK. STATUS = %r\n", Status));
	}

	//count number of SPIO_LIST_ITEMs in the system
	for(i=0; ;i++){
		sioli=gSpioList[i];
		if(!sioli)break;
		gSpioCount++;
	};

	
	gSpio=MallocZ(sizeof(GSPIO)*gSpioCount);
	ASSERT(gSpio);
	if(!gSpio) return EFI_OUT_OF_RESOURCES;
	//init basic GSPIO structure and collect information about spio devices
	//gSpio.Indx=SIO_CONFIG_INDEX;
	//gSpio.Data=SIO_CONFIG_DATA;
	for(j=0; j<gSpioCount; j++){
		sioli=gSpioList[j];
		gspio=&gSpio[j];
		
		//gspio->ImageHandle=ImageHandle;
		gspio->InCfgMode=FALSE;
		gspio->SpioInfo=sioli;
		
		gspio->GlobalCfgDump=MallocZ(sioli->GlobalInclRegCount);
		ASSERT(gspio->GlobalCfgDump);
		if(!gspio->GlobalCfgDump) return EFI_OUT_OF_RESOURCES;

		//Save Initial (PowerOn after PEI Init) state of SIO Global registers (reg 0.. 2F usually)
		SaveSioRegs(gspio, NULL, gspio->SpioInfo->GlobalIncludeReg,sioli->GlobalInclRegCount,gspio->GlobalCfgDump);
	
		gspio->DeviceList=MallocZ(sizeof(VOID*)*sioli->DevCount);
		ASSERT(gspio->DeviceList);
		if(!gspio->DeviceList)return EFI_OUT_OF_RESOURCES;

		for(i=0;i<sioli->DevCount;i++){
			dev=NewDev(&sioli->SioDevList[i],gspio);
			ASSERT(dev);
			if(!dev) return EFI_OUT_OF_RESOURCES;
			gspio->DeviceList[i]=dev;

			if(dev->DeviceInfo->Flags && ro){
				dev->ResOwner=ro;
				ro->ResConsumer=dev;
			} 
			//very first device in a list can't be a device with shared resources
			if(!i && dev->DeviceInfo->Flags) return EFI_INVALID_PARAMETER;
			ro=dev;
		}
	}
#if ACPI_SUPPORT
	GetDsdt(NULL,NULL);						
	//if no ACPISupport Protocol Available yet - install Notify Event
	if(!gPDsdt) {
		Status=RegisterProtocolCallback(&gAcpiSupportGuid,GetDsdt,NULL,&mAcpiEvent,&mAcpiReg);
		SIO_TRACE((TRACE_SIO,"GSIO: Locate ACPISupport FAILURE. Installing Callback (%r)\n", Status));
	} else SIO_TRACE((TRACE_SIO,"GSIO: Locate ACPISupport SUCCESS \n"));
	
#endif	
	//Set the Callback for Variable Write
	if(!mVarWrite){
		Status=RegisterProtocolCallback(&gVariableWriteProtocolGuid,UpdateIsaMask,NULL,&mIsaEvent,&mIsaReg);
		SIO_TRACE((TRACE_SIO,"GSIO: Variable Write FAILURE. Installing Callback (%r)\n", Status));	
	}


	//Create event for boot script
	Status = CreateReadyToBootEvent(
		TPL_NOTIFY,
		CallbackReadyToBoot,
		NULL,
		&gEvtReadyToBoot
	);
	ASSERT_EFI_ERROR(Status);


	//Here we can set up notification events if needed



	//------------------------------------
	return Status;

}

// <AMI_PHDR_START>
//-------------------------------------------------------------------------
//
// Procedure: GetDsdt
//
// Description:
//  This function will get gPDsdt address 
//
// Input:
//
// Output: 
//
// Notes:
//------------------------------------------------------------------------- 
// <AMI_PHDR_END> 
#if ACPI_SUPPORT
VOID GetDsdt(IN EFI_EVENT Event, IN VOID *Context){
	UINTN					i;
	EFI_STATUS				Status=0;
	EFI_PHYSICAL_ADDRESS	dsdtaddr=0;
//-----------------------------
	
	Status=LibGetDsdt(&dsdtaddr,EFI_ACPI_TABLE_VERSION_ALL);
	if(EFI_ERROR(Status)) return;
	else gPDsdt=(ACPI_HDR*)dsdtaddr;

	if(!gPDsdt)	SIO_TRACE((TRACE_SIO,"GSIO: FAIL to locate DSDT Table -> %r\n", Status));
	else {
		for(i=0;i<gSpioCount;i++){
			Status=EnumerateAll(&gSpio[i]);	
			SIO_TRACE((TRACE_SIO,"GSIO: EnumerateAll (ACPI Mode) for SIO Chip # %d returned %r\n",i, Status));
		}
		//install driver binding protocol here ....
		Status = pBS->InstallMultipleProtocolInterfaces(
					&gAmiSioDriverBinding.DriverBindingHandle,
					&gDriverBindingProtocolGuid,&gAmiSioDriverBinding,
					&gEfiComponentName2ProtocolGuid, &gAmiSioComponentName,
					NULL,NULL);
	}

	if(Event) Status=pBS->CloseEvent(Event);
}
#endif	

// <AMI_PHDR_START>
//------------------------------------------------------------------------- 
// Procedure: SioSetupData
//
// Description:
//This Function will get NonVolatile SioDevice Setup Var if it is not present it will create it
//or set Volatile SioDevice Setup Var parameter Get is the Action Selector
//
// Input:
//
// Output: 
//
// Notes:
//------------------------------------------------------------------------- 
// <AMI_PHDR_END>  
EFI_STATUS SioSetupData(SPIO_DEV *Dev, BOOLEAN Get){
	EFI_STATUS	Status=0,s2=0;
	EFI_GUID	ssg={0x560bf58a, 0x1e0d, 0x4d7e, 0x95, 0x3f, 0x29, 0x80, 0xa2, 0x61, 0xe0, 0x31};
	UINT16		*vname;
	UINTN		vs;
//---------------------------------
	vname=MallocZ(sizeof(UINT16)*14);
	ASSERT(vname);
	if(!vname)return EFI_OUT_OF_RESOURCES;

	if(Get){
		//Get Non Volatile Variable for this Device 
		//the variable name is spels as "PNP"+Dev->PnpId+'_'+Dev_Uid"
		Swprintf(&vname[0],L"PNP%04X_%X_NV",Dev->DeviceInfo->PnpId,Dev->DeviceInfo->UID);
		vs=sizeof(SIO_DEV_NV_DATA);
		Status = pRS->GetVariable(vname, &ssg, NULL, &vs, &Dev->NvData);
		//upon creation Dev->NvData Dev->VlData was initialized with '0'
		if(EFI_ERROR(Status)){
			if(Status!=EFI_NOT_FOUND) return Status;
			Dev->NvData.DevEnable=1; //Default is Enabled
		}
		//If SIO setup screens NOT using Generic SIO Setup Screens 
		//we need to get setup options from the global SETUP_DATA var.
		if (Dev->DeviceInfo->InitRoutine!=NULL) Status=Dev->DeviceInfo->InitRoutine(&Dev->AmiSio,NULL,isGetSetupData);
	} else {
		//Set Volatile var
		Swprintf(&vname[0],L"PNP%04X_%X_VV",Dev->DeviceInfo->PnpId,Dev->DeviceInfo->UID);
		vs=sizeof(SIO_DEV_V_DATA);
		s2 = pRS->SetVariable(vname, &ssg, EFI_VARIABLE_BOOTSERVICE_ACCESS, vs, &Dev->VlData);
		//Set NonVolatile var
		Swprintf(&vname[0],L"PNP%04X_%X_NV",Dev->DeviceInfo->PnpId,Dev->DeviceInfo->UID);
		vs=sizeof(SIO_DEV_NV_DATA);
		Status = pRS->SetVariable(vname, &ssg, EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_NON_VOLATILE, vs, &Dev->NvData);
	}
	return (s2|Status);
}

// <AMI_PHDR_START>
//------------------------------------------------------------------------- 
// Procedure: NewDev
//
// Description:
//Allocates memory for SPIO device Instance and init basic fields
//
// Input:
//
// Output: 
//
// Notes:
//------------------------------------------------------------------------- 
// <AMI_PHDR_END>  
SPIO_DEV* NewDev(SPIO_DEV_LST *SioDevInfo, GSPIO *Owner/*, UINTN BufferSize*/){
	SPIO_DEV	*dev;
//---------------------------
	dev=MallocZ(sizeof(SPIO_DEV));
	if(!dev) return NULL;
	
	//Fill out SPIO_DEV struct;
	dev->Owner=Owner;
	dev->DeviceInfo=SioDevInfo;
#if ((defined PI_SPECIFICATION_VERSION) && (PI_SPECIFICATION_VERSION >= 0x00010014))
    dev->EfiSioData.Owner=dev;
#endif

	//dev->Type=SioDevInfo->Type;
	//dev->LDN=SioDevInfo->LDN;	
	dev->EisaId.UID=SioDevInfo->UID;
	dev->EisaId.HID=PNP_HID(SioDevInfo->PnpId);
	
	//Get Device Setup Data Volatile and NonVolatile
	//Can't use variable services now because it is NOT_AVAILABLE_YET
	dev->VlData.DevImplemented=SioDevInfo->Implemented;
	dev->NvData.DevEnable=SioDevInfo->Implemented;
	//dev->Implemented=
	//dev->Flags=SioDevInfo->Flags;
	//dev->InitRoutine=SioDevInfo->InitRoutine;
	dev->LocalCfgDump=MallocZ(Owner->SpioInfo->LocalInclRegCount);
	if(!dev->LocalCfgDump){
		pBS->FreePool(dev);
		dev=NULL;
	} else {
		SaveSioRegs(Owner, dev, Owner->SpioInfo->LocalIncludeReg, Owner->SpioInfo->LocalInclRegCount, dev->LocalCfgDump);
		Owner->DeviceCount++;
	}
	return dev;
}


// <AMI_PHDR_START>
//------------------------------------------------------------------------- 
//
// Procedure: SioCfgMode
//
// Description:
//Routine to transit Sio in/from Config Mode.
//
// Input:
//
// Output: 
//
// Notes:
//------------------------------------------------------------------------- 
// <AMI_PHDR_END>  
VOID SioCfgMode(GSPIO *Sio, BOOLEAN Enter)
{
	UINTN				i;
	SPIO_SCRIPT_LST		*sl;
//---------------------------------
	if(Enter)sl=Sio->SpioInfo->EnterCfgMode;
	else sl=Sio->SpioInfo->ExitCfgMode;

    if(sl==NULL) return;

	for (i=0; i<sl->InstrCount; i++){
		switch (sl->OpType){
			case cfgNone: 
				break;
			case cfgByteSeq:
			{
				SPIO_SCRIPT  *Instr = (SPIO_SCRIPT*) sl->Instruction[0];
				SPIO_SCRIPT	*cmd = &Instr[i];
				UINT16		reg;
				UINT8		dat;	
			//------------------------
				if(cmd->IdxDat)reg=Sio->SpioInfo->SioIndex;
				else reg=Sio->SpioInfo->SioData;
				
				if (cmd->WrRd) IoWrite8(reg,cmd->Value);
				else {
					UINTN c=100000;
					dat=IoRead8(reg);
					while( c && dat!=cmd->Value ) {
						dat=IoRead8(reg);
						c--;	
					}
				}
				break;
			}
			case cfgRoutine:
			{
				SPIO_ROUTINE rt=(SPIO_ROUTINE)sl->Instruction[i];	
				rt;
			}
				break;
			default: return;
		}//switch
	}//for
	Sio->InCfgMode=Enter;
	return;
}
// <AMI_PHDR_START>
//------------------------------------------------------------------------- 
//
// Procedure: SaveSioRegs
//
// Description:
//Save Sio reg contents in the buffer
//if Dev is NULL it did not  selects the device 
//
// Input:
//
// Output: 
//
// Notes:
//------------------------------------------------------------------------- 
// <AMI_PHDR_END> 
VOID SaveSioRegs(GSPIO *Sio, SPIO_DEV *Dev, UINT8 *InclRegsList, UINTN InclRegCount, UINT8 *Buffer){
	UINTN	i;	
	UINT8	r;
//------------------------
	if(!Sio->InCfgMode) SioCfgMode(Sio, TRUE);
	if(Dev)DevSelect(Dev);
	for(i=0; i<InclRegCount; i++){
		r=InclRegsList[i];
		IoWrite8(Sio->SpioInfo->SioIndex,r);		
		Buffer[i]=IoRead8(Sio->SpioInfo->SioData);
	}
	SioCfgMode(Sio, FALSE);
}

// <AMI_PHDR_START>
//------------------------------------------------------------------------- 
//
// Procedure: GetPrsFromTable
//
// Description:
//This function will get _PRS from mSpioDeviceList[] table
//"Index" is the entry # in mSpioDeviceList[] 
//
// Input:
//
// Output: 
//
// Notes:
//------------------------------------------------------------------------- 
// <AMI_PHDR_END> 
EFI_STATUS GetPrsFromTable(SPIO_DEV* Dev, UINTN Index){
	SPIO_DEV_LST	*de=Dev->DeviceInfo;//device entry
							//IO1 IO2  IRQ1 IRQ2 DMA1 DMA2 
	VOID*			*rl[6]=	{NULL,NULL,NULL,NULL,NULL,NULL}; //resource list
	UINT16			i=0;
	T_ITEM_LIST		*dl;	
//-----------------------------------
    SIO_TRACE((TRACE_SIO,"Dev[%d]: PRS Tbl=> \n", Index));
    
    if (Dev->DeviceInfo->Flags==SIO_NO_RES){
        SIO_TRACE((TRACE_SIO," Device NOT USING Resources FLAGS=0x%X\n", Dev->DeviceInfo->Flags));
        return EFI_SUCCESS;
    }
    
	i = de->ResLen[0] | de->ResLen[1] | de->IrqMask[0] | de->IrqMask[1] | de->DmaMask[0] | de->DmaMask[1];
	if(!i){
		SIO_TRACE((TRACE_SIO,"Entry is Empty! Check 'YourSioName_DevLst' table.\n"));
		return EFI_NOT_FOUND;
	}
	//Resource base and length 1
		rl[0]=ASLM_FixedIO(de->ResBase[0],de->ResLen[0]);
		if(!rl[0]) return EFI_OUT_OF_RESOURCES;
		SIO_TRACE((TRACE_SIO,"IO1.B=%X; IO1.L=%X; ",de->ResBase[0],de->ResLen[0]));

	//Resource base and length 2
		rl[1]=ASLM_FixedIO(de->ResBase[1],de->ResLen[1]);
		if(!rl[1]) return EFI_OUT_OF_RESOURCES;
		SIO_TRACE((TRACE_SIO,"IO2.B=%X IO2.L=%X; ",de->ResBase[1],de->ResLen[1]));

	//IRQ settings 1
		rl[2]=ASLM_IRQNoFlags(1,0);
		if(!rl[2]) return EFI_OUT_OF_RESOURCES;
		((ASLR_IRQNoFlags*)rl[2])->_INT=de->IrqMask[0];
		SIO_TRACE((TRACE_SIO,"IRQ1=%X; ",de->IrqMask[0]));

	//IRQ settings 2

		rl[3]=ASLM_IRQNoFlags(1,0);
		if(!rl[3]) return EFI_OUT_OF_RESOURCES;
		((ASLR_IRQNoFlags*)rl[3])->_INT=de->IrqMask[1];
		SIO_TRACE((TRACE_SIO,"IRQ2=%X; ",de->IrqMask[1]));
	//DMA settings 1
		rl[4]=ASLM_DMA(1,ASLV_Compatibility, ASLV_NotBusMaster, ASLV_Transfer8, 0);
		if(!rl[4]) return EFI_OUT_OF_RESOURCES;
		((ASLR_DMA*)rl[4])->_DMA=de->DmaMask[0];
		SIO_TRACE((TRACE_SIO,"DMA1=%X; ",de->DmaMask[0]));
	//DMA settings 2
		rl[5]=ASLM_DMA(1,ASLV_Compatibility, ASLV_NotBusMaster, ASLV_Transfer8, 0);
		if(!rl[5]) return EFI_OUT_OF_RESOURCES;
		((ASLR_DMA*)rl[5])->_DMA=de->DmaMask[1];
		SIO_TRACE((TRACE_SIO,"DMA2=%X;",de->DmaMask[1]));

    	SIO_TRACE((TRACE_SIO,"\n"));

	    //Now Create _PRS Object for this device with best priorities
	    dl=ASLM_StartDependentFn(6,0,0,rl[0],rl[1],rl[2],rl[3],rl[4],rl[5]);
	    if(!dl) return EFI_OUT_OF_RESOURCES;
	    
		SIO_TRACE((TRACE_SIO,"DepFn=%X,ItemCount=%d; ",(EFI_ASL_DepFn*)dl,((EFI_ASL_DepFn*)dl)->DepRes.ItemCount));
        for(i=0;i<6;i++) {
	        SIO_TRACE((TRACE_SIO,"Item[%d]=%X  ",i,((EFI_ASL_DepFn*)dl)->DepRes.Items[i]));
        }
	    SIO_TRACE((TRACE_SIO,"\n <= Dev[%d]: PRS Tbl End \n",Index));	
	    return AppendItemLst(&Dev->PRS, dl);
}


#if (! ACPI_SUPPORT)

// <AMI_PHDR_START>
//------------------------------------------------------------------------- 
// Procedure: Set***Prs
//
// Description:
//These functions will collect _PRS from legacy concept,it is not support ACPI
//
// Input:
//
// Output: 
//
// Notes:
//------------------------------------------------------------------------- 
// <AMI_PHDR_END> 
//Create Possible Resource Settings Buffer for FDC
EFI_STATUS SetFdcPrs(SPIO_DEV *Dev)
{
	EFI_STATUS			Status;			
	T_ITEM_LIST 		*dl;
//-----------------------------------
//	StartDependentFn(0, 0) {
//			IO(Decode16, 0x3F0, 0x3F0, 1, 8)
//			IRQNoFlags() {6}
//			DMA(Compatibility, NotBusMaster, Transfer8) {2}
//		} //Same as
//						sdc_cnt,pComp,pPerf
	dl=ASLM_StartDependentFn(4,    0,   0,
			ASLM_FixedIO(0x3F0, 6), //0x3F6 port reserved for Legacy IDE
			ASLM_FixedIO(0x3F7, 1),
			ASLM_IRQNoFlags(1,6),
			ASLM_DMA(1,ASLV_Compatibility, ASLV_NotBusMaster, ASLV_Transfer8, 2)
			);	
	if(!dl) return EFI_OUT_OF_RESOURCES;	
	Status=AppendItemLst(&Dev->PRS, dl);
	if(EFI_ERROR(Status)) return Status;

//	StartDependentFnNoPri() {
//			IO(Decode16, 0x3F0, 0x3F0, 1, 6)
//			IRQNoFlags() {3,4,5,6,7,10,11,12}
//			DMA(Compatibility, NotBusMaster, Transfer8) {0,1,2,3}
//		} same as
	dl=ASLM_StartDependentFnNoPri(4,
		ASLM_FixedIO(0x3F0,6), //0x3F6 port reserved for Legacy IDE
		ASLM_FixedIO(0x3F7,1),
		ASLM_IRQNoFlags(7, 3,4,5,6,10,11,12),	
		ASLM_DMA(4,ASLV_Compatibility, ASLV_NotBusMaster, ASLV_Transfer8,0,1,2,3)
	);	
	if(!dl) return EFI_OUT_OF_RESOURCES;	
	
	Status=AppendItemLst(&Dev->PRS, dl);
	if(EFI_ERROR(Status)) return Status;

	dl=ASLM_StartDependentFnNoPri( 3, 
			ASLM_FixedIO(0x370, 6), //0x376 port reserved for Legacy IDE
			ASLM_FixedIO(0x377, 1),
			ASLM_IRQNoFlags(7, 3,4,5,6,10,11,12),
			ASLM_DMA(4,ASLV_Compatibility, ASLV_NotBusMaster, ASLV_Transfer8,0,1,2,3)
			);	
	if(!dl) return EFI_OUT_OF_RESOURCES;	
	
	Status=AppendItemLst(&Dev->PRS, dl);
	return Status;
}

// <AMI_PHDR_START>
//------------------------------------------------------------------------- 
// Procedure: Set***Prs
//
// Description:
//These functions will collect _PRS from legacy concept,it is not support ACPI
//
// Input:
//
// Output: 
//
// Notes:
//------------------------------------------------------------------------- 
// <AMI_PHDR_END> 
//Create Possible Resource Settings Buffer for PS2 Keyboard 
EFI_STATUS SetPs2kPrs(SPIO_DEV *Dev)
{
	EFI_STATUS			Status=0;			
	T_ITEM_LIST 		*dl;
//-----------------------------------	
	if(Dev->DeviceInfo->Type==dsPS2CM){
		//Just in case overwrite porting settings
		//Dev->DeviceInfo->Flags=SIO_SHR_ALL;
		dl=ASLM_StartDependentFnNoPri( 4, 
			ASLM_FixedIO(0x60, 1),
			ASLM_FixedIO(0x64, 1),
			ASLM_IRQNoFlags(1, 1),
			ASLM_IRQNoFlags(1, 12) );	
	} else {
		Dev->DeviceInfo->Flags=SIO_SHR_IO;
		dl=ASLM_StartDependentFnNoPri( 3, 
			ASLM_FixedIO(0x60, 1),
			ASLM_FixedIO(0x64, 1),
			ASLM_IRQNoFlags(1, 1) );	
	}
	if(!dl) return EFI_OUT_OF_RESOURCES;	

	Status=AppendItemLst(&Dev->PRS, dl);
	return Status;
}

// <AMI_PHDR_START>
//------------------------------------------------------------------------- 
// Procedure: Set***Prs
//
// Description:
//These functions will collect _PRS from legacy concept,it is not support ACPI
//
// Input:
//
// Output: 
//
// Notes:
//------------------------------------------------------------------------- 
// <AMI_PHDR_END> 
//Create Possible Resource Settings Buffer for PS2 mouse 
EFI_STATUS SetPs2mPrs(SPIO_DEV *Dev)
{
	EFI_STATUS			Status=0;			
	T_ITEM_LIST 		*dl;
//-----------------------------------	
	if(Dev->DeviceInfo->Type==dsPS2CM){
		//Just in case overwrite porting settings
		//Dev->DeviceInfo->Flags=SIO_SHR_ALL;
		dl=ASLM_StartDependentFnNoPri( 4, 
			ASLM_FixedIO(0x60, 1),
			ASLM_FixedIO(0x64, 1),
			ASLM_IRQNoFlags(1, 1),
			ASLM_IRQNoFlags(1, 12) );	
	} else {
		Dev->DeviceInfo->Flags=SIO_SHR_IO;
		dl=ASLM_StartDependentFnNoPri( 3, 
			ASLM_FixedIO(0x60, 1),
			ASLM_FixedIO(0x64, 1),
			ASLM_IRQNoFlags(1, 12) );	
	}
	if(!dl) return EFI_OUT_OF_RESOURCES;	

	Status=AppendItemLst(&Dev->PRS, dl);
	return Status;
}

EFI_STATUS SetUartPrs(SPIO_DEV *Dev){
	EFI_STATUS			Status=0;			
	T_ITEM_LIST			*dl;
//-----------------------------------	
	switch(Dev->EisaId.UID){
		case 0 : //priority for Com 1;
			dl=ASLM_StartDependentFn(2, 0,0,
				ASLM_FixedIO(0x3F8, 8),
				ASLM_IRQNoFlags(1,4)
			);
			break;
		case 1 : //priority for Com 2;
			dl=ASLM_StartDependentFn(2, 0,0,
				ASLM_FixedIO(0x2F8, 8),
				ASLM_IRQNoFlags(1,3)
			);
			break;
		case 2 : //priority for Com 3;
			dl=ASLM_StartDependentFn(2, 0,0,
				ASLM_FixedIO(0x3E8, 8),
				ASLM_IRQNoFlags(1,11)
			);
			break;

		case 3 : //priority for Com 4;
			dl=ASLM_StartDependentFn(2, 0,0,
				ASLM_FixedIO(0x2E8, 8),
				ASLM_IRQNoFlags(1,10)
			);
			break;
	}
	if(!dl) return EFI_OUT_OF_RESOURCES;	
	Status=AppendItemLst(&Dev->PRS, dl);
	if(EFI_ERROR(Status)) return Status;
	
	//the rest of resource combinations will go with No Priority
	dl=ASLM_StartDependentFnNoPri(2,
		ASLM_FixedIO(0x3F8, 8),
		ASLM_IRQNoFlags(7, 3,4,5,6,10,11,12)
	);
	if(!dl) return EFI_OUT_OF_RESOURCES;	
	Status=AppendItemLst(&Dev->PRS, dl);
	if(EFI_ERROR(Status)) return Status;

	dl=ASLM_StartDependentFnNoPri(2,
		ASLM_FixedIO(0x2F8, 8),
		ASLM_IRQNoFlags(7, 3,4,5,6,10,11,12)
	);
	if(!dl) return EFI_OUT_OF_RESOURCES;	
	Status=AppendItemLst(&Dev->PRS, dl);
	if(EFI_ERROR(Status)) return Status;
	
	dl=ASLM_StartDependentFnNoPri(2,
		ASLM_FixedIO(0x3E8, 8),
		ASLM_IRQNoFlags(7, 3,4,5,6,10,11,12)
	);
	if(!dl) return EFI_OUT_OF_RESOURCES;	
	Status=AppendItemLst(&Dev->PRS, dl);
	if(EFI_ERROR(Status)) return Status;

	dl=ASLM_StartDependentFnNoPri(2,
		ASLM_FixedIO(0x2E8, 8),
		ASLM_IRQNoFlags(7, 3,4,5,6,10,11,12)
	);
	if(!dl) return EFI_OUT_OF_RESOURCES;	
	Status=AppendItemLst(&Dev->PRS, dl);

	return Status;
}

// <AMI_PHDR_START>
//------------------------------------------------------------------------- 
// Procedure: Set***Prs
//
// Description:
//These functions will collect _PRS from legacy concept,it is not support ACPI
//
// Input:
//
// Output: 
//
// Notes:
//------------------------------------------------------------------------- 
// <AMI_PHDR_END> 
EFI_STATUS SetLptPrs(SPIO_DEV *Dev, BOOLEAN UseDma){
	EFI_STATUS			Status=0;			
	T_ITEM_LIST			*dl;
//-----------------------------------	

	switch(Dev->EisaId.UID){
		case 0 : //priority for LPT 1;
			if(UseDma){
				dl=ASLM_StartDependentFn(4, 0,0,
					ASLM_FixedIO(0x378, 8),
					ASLM_FixedIO(0x778, 8),
					ASLM_IRQNoFlags(1,7),
					ASLM_DMA(1,ASLV_Compatibility, ASLV_NotBusMaster, ASLV_Transfer8, 3)
				);
			} else {
				dl=ASLM_StartDependentFn(2, 0,0,
					ASLM_FixedIO(0x378, 8),
					ASLM_IRQNoFlags(1,7)
				);
			}
			break;
		case 1 : //priority for LPT 2;
			if(UseDma){
				dl=ASLM_StartDependentFn(4, 0,0,
					ASLM_FixedIO(0x278, 8),
					ASLM_FixedIO(0x678, 8),
					ASLM_IRQNoFlags(1,5),
					ASLM_DMA(1,ASLV_Compatibility, ASLV_NotBusMaster, ASLV_Transfer8, 1)
				);
			} else {
				dl=ASLM_StartDependentFn(2, 0,0,
					ASLM_FixedIO(0x278, 8),
					ASLM_IRQNoFlags(1,5)
				);
			}
			break;
	}
	if(!dl) return EFI_OUT_OF_RESOURCES;	
	Status=AppendItemLst(&Dev->PRS, dl);
	if(EFI_ERROR(Status)) return Status;
	
	//the rest of resource combinations will go with No Priority
	if(UseDma){
		//IRQ
		dl=ASLM_StartDependentFnNoPri(4,
			ASLM_FixedIO(0x378, 8),
			ASLM_FixedIO(0x778, 8),
			ASLM_IRQNoFlags(7, 3,4,5,6,10,11,12),
			ASLM_DMA(2,ASLV_Compatibility, ASLV_NotBusMaster, ASLV_Transfer8, 1, 3)
		);
		if(!dl) return EFI_OUT_OF_RESOURCES;	
		Status=AppendItemLst(&Dev->PRS, dl);
		if(EFI_ERROR(Status)) return Status;

		dl=ASLM_StartDependentFnNoPri(4,
			ASLM_FixedIO(0x278, 8),
			ASLM_FixedIO(0x678, 8),
			ASLM_IRQNoFlags(7, 3,4,5,6,10,11,12),
			ASLM_DMA(2,ASLV_Compatibility, ASLV_NotBusMaster, ASLV_Transfer8, 1, 3)
		);
		if(!dl) return EFI_OUT_OF_RESOURCES;	
		Status=AppendItemLst(&Dev->PRS, dl);
		if(EFI_ERROR(Status)) return Status;
	
		dl=ASLM_StartDependentFnNoPri(4,
			ASLM_FixedIO(0x3BC, 4),
			ASLM_FixedIO(0x7BC, 4),
			ASLM_IRQNoFlags(7, 3,4,5,6,10,11,12),
			ASLM_DMA(2,ASLV_Compatibility, ASLV_NotBusMaster, ASLV_Transfer8, 1, 3)
		);
		if(!dl) return EFI_OUT_OF_RESOURCES;	
		Status=AppendItemLst(&Dev->PRS, dl);
		if(EFI_ERROR(Status)) return Status;
		//No IRQ
		dl=ASLM_StartDependentFnNoPri(3,
			ASLM_FixedIO(0x378, 8),
			ASLM_FixedIO(0x778, 8),
			ASLM_DMA(2,ASLV_Compatibility, ASLV_NotBusMaster, ASLV_Transfer8, 1, 3)
		);
		if(!dl) return EFI_OUT_OF_RESOURCES;	
		Status=AppendItemLst(&Dev->PRS, dl);
		if(EFI_ERROR(Status)) return Status;

		dl=ASLM_StartDependentFnNoPri(3,
			ASLM_FixedIO(0x278, 8),
			ASLM_FixedIO(0x678, 8),
			ASLM_DMA(2,ASLV_Compatibility, ASLV_NotBusMaster, ASLV_Transfer8, 1, 3)
		);
		if(!dl) return EFI_OUT_OF_RESOURCES;	
		Status=AppendItemLst(&Dev->PRS, dl);
		if(EFI_ERROR(Status)) return Status;
	
		dl=ASLM_StartDependentFnNoPri(3,
			ASLM_FixedIO(0x3BC, 4),
			ASLM_FixedIO(0x7BC, 4),
			ASLM_DMA(2,ASLV_Compatibility, ASLV_NotBusMaster, ASLV_Transfer8, 1, 3)
		);
		if(!dl) return EFI_OUT_OF_RESOURCES;	
		Status=AppendItemLst(&Dev->PRS, dl);

	} else { //No DMA MODE
		//IRQ
		dl=ASLM_StartDependentFnNoPri(2,
			ASLM_FixedIO(0x378, 8),
			ASLM_IRQNoFlags(7, 3,4,5,6,10,11,12)
		);
		if(!dl) return EFI_OUT_OF_RESOURCES;	
		Status=AppendItemLst(&Dev->PRS, dl);
		if(EFI_ERROR(Status)) return Status;

		dl=ASLM_StartDependentFnNoPri(2,
			ASLM_FixedIO(0x278, 8),
			ASLM_IRQNoFlags(7, 3,4,5,6,10,11,12)
		);
		if(!dl) return EFI_OUT_OF_RESOURCES;	
		Status=AppendItemLst(&Dev->PRS, dl);
		if(EFI_ERROR(Status)) return Status;
	
		dl=ASLM_StartDependentFnNoPri(2,
			ASLM_FixedIO(0x3BC, 4),
			ASLM_IRQNoFlags(7, 3,4,5,6,10,11,12)
		);
		if(!dl) return EFI_OUT_OF_RESOURCES;	
		Status=AppendItemLst(&Dev->PRS, dl);
		if(EFI_ERROR(Status)) return Status;
		//No IRQ
		dl=ASLM_StartDependentFnNoPri(1,
			ASLM_FixedIO(0x378, 8)
		);
		if(!dl) return EFI_OUT_OF_RESOURCES;	
		Status=AppendItemLst(&Dev->PRS, dl);
		if(EFI_ERROR(Status)) return Status;

		dl=ASLM_StartDependentFnNoPri(1,
			ASLM_FixedIO(0x278, 8)
		);
		if(!dl) return EFI_OUT_OF_RESOURCES;	
		Status=AppendItemLst(&Dev->PRS, dl);
		if(EFI_ERROR(Status)) return Status;
	
		dl=ASLM_StartDependentFnNoPri(1,
			ASLM_FixedIO(0x3BC, 4)
		);
		if(!dl) return EFI_OUT_OF_RESOURCES;	
		Status=AppendItemLst(&Dev->PRS, dl);
	}
	return Status;
}

// <AMI_PHDR_START>
//------------------------------------------------------------------------- 
// Procedure: Set***Prs
//
// Description:
//These functions will collect _PRS from legacy concept,it is not support ACPI
//
// Input:
//
// Output: 
//
// Notes:
//------------------------------------------------------------------------- 
// <AMI_PHDR_END> 
EFI_STATUS SetGamePrs(SPIO_DEV *Dev){
	EFI_STATUS			Status=0;			
	T_ITEM_LIST 		*dl;
//-----------------------------------	

	dl=ASLM_StartDependentFnNoPri(1,
		ASLM_FixedIO(0x200, 8)
	);
	if(!dl) return EFI_OUT_OF_RESOURCES;	
	Status=AppendItemLst(&Dev->PRS, dl);

	return Status;
}

EFI_STATUS SetMpu401Prs(SPIO_DEV *Dev){
	EFI_STATUS		Status=0;			
	T_ITEM_LIST 	*dl;
//-----------------------------------	


	//the rest of resource combinations will go with No Priority
	dl=ASLM_StartDependentFnNoPri(2,
		ASLM_FixedIO(0x300, 2),
		ASLM_IRQNoFlags(5, 5,7,9,10,11)
	);
	if(!dl) return EFI_OUT_OF_RESOURCES;	
	Status=AppendItemLst(&Dev->PRS, dl);
	if(EFI_ERROR(Status)) return Status;

	dl=ASLM_StartDependentFnNoPri(2,
		ASLM_FixedIO(0x330, 2),
		ASLM_IRQNoFlags(5, 5,7,9,10,11)
	);
	if(!dl) return EFI_OUT_OF_RESOURCES;	
	Status=AppendItemLst(&Dev->PRS, dl);
	return Status;
}

#else 

// <AMI_PHDR_START>
//------------------------------------------------------------------------- 
//
// Procedure: GetPrsFromAml
//
// Description:
//These function will collect _PRS from Aml code which support ACPI
//"Index" is the entry # in mSpioDeviceList[] 
//
// Input:
//
// Output: 
//
// Notes:
//------------------------------------------------------------------------- 
// <AMI_PHDR_END> 
EFI_STATUS GetPrsFromAml(SPIO_DEV* Dev, UINT8 *PrsName ,UINTN Index){
	EFI_STATUS		Status=0;
	SPIO_DEV_LST 	*de=Dev->DeviceInfo;
	ASL_OBJ_INFO	obj={0}, prs={0};
	UINT8			bc, *p, *prsb;
	UINTN			pl, bl;
	ASLRF_S_HDR		*rd;
	EFI_ASL_DepFn	*pdf=NULL;
//---------------------------				
	if(de->AslName[0]==0) return GetPrsFromTable(Dev, Index);

	Status=GetAslObj((UINT8*)gPDsdt+sizeof(ACPI_HDR),gPDsdt->Length-sizeof(ACPI_HDR)-1,&de->AslName[0],otDevice,&obj);
	if(EFI_ERROR(Status)) {
		SIO_TRACE((TRACE_SIO,"SIO[%d]: Aml=> Failed to Locate ASL Object %s in DSDT at %08X\n",Index,&de->AslName[0], gPDsdt));
		return GetPrsFromTable(Dev, Index);
	}

	//it must be _PRS name Object there 
	if(!PrsName) Status = GetAslObj(obj.DataStart,obj.Length,"_PRS",otName,&prs);
	else Status = GetAslObj(obj.DataStart,obj.Length,PrsName,otName,&prs);
	if(EFI_ERROR(Status)) {
		SIO_TRACE((TRACE_SIO,"SIO[%d]: Aml=> Failed to Locate _PRS Object in %s Object Scope at %08X\n",Index, &de->AslName[0], obj.Object));
		return GetPrsFromTable(Dev, Index);
	}

	p=prs.DataStart;
	if(*p==AML_OP_BUFFER){
		pl=GetPackageLen((AML_PACKAGE_LBYTE*)(p+1),&bc);
		//_PRS Name must be a "Buffer"
		//DefBuffer := BufferOp PkgLength BufferSize ByteList
		//BufferSize := TermArg=>Integer
		//DataObject := (in our case ComputationalData) | DefPackage | DefVarPackage
		p+=bc+2;
		switch(*p){
			case AML_PR_BYTE:
				bl=*(p+1);
				prsb=p+2;
				break;
			case AML_PR_WORD:
				bl=*((UINT16*)(p+1));
				prsb=p+3;
				break;
			case AML_PR_DWORD:
				bl=*((UINT32*)(p+1));
				prsb=p+5;
				break;
			default: return EFI_INVALID_PARAMETER;
		}
		//Now Copy _PRS Buffer into new location and fill SIO.PRS T_ITEM_LIST 
		p=Malloc(bl);
		if(!p) return EFI_OUT_OF_RESOURCES;
		MemCpy(p,prsb,bl);
		//Parse AML _PRS Buffer
		rd=(ASLRF_S_HDR*)p;
		prsb=p;		
		while(rd->Name!=ASLV_SR_EndTag){
		//------------------------------
			if(rd->Name==ASLV_RT_StartDependentFn){
				//Add this item to device PRS list
				pdf=MallocZ(sizeof(EFI_ASL_DepFn));
				if(!pdf) return EFI_OUT_OF_RESOURCES;
				pdf->DepFn=rd;
				Status=AppendItemLst(&Dev->PRS, (VOID*)pdf);
				if(EFI_ERROR(Status)) return EFI_OUT_OF_RESOURCES;
			} else {
				Status=AppendItemLst(&pdf->DepRes,rd);
				if(EFI_ERROR(Status)) return EFI_OUT_OF_RESOURCES;
			}
			//advance to the next descriptor in _PRS ResourceTemplate
			p+=sizeof(ASLRF_S_HDR)+rd->Length; //rd->Length => Byte length excluding length of the header
			//It could be only IO, FixedIO, IRQ and DMA types of resources so it is small resource descriptor type
			if((prsb+bl)<p){ //check if we still inside _PRS buffer or went out..
				SIO_TRACE((TRACE_SIO,"SIO[%d]: Aml=> Failed to Locate EndDepFn in _PRS buffer of %s Object at %08X\n",Index ,&de->AslName[0],prs.Object));
				return GetPrsFromTable(Dev, Index);
			}
			rd=(ASLRF_S_HDR*)p;
			if(rd->Name==ASLV_RT_EndDependentFn) break;
		} //while
		if(!Dev->PRS.ItemCount){
			SIO_TRACE((TRACE_SIO,"SIO[%d]: Aml=> Failed to Locate StartDepFn in _PRS buffer of %s Object at %08X\n",Index,&de->AslName[0],prs.Object));
			return GetPrsFromTable(Dev, Index);
		}
		SIO_TRACE((TRACE_SIO,"SIO[%d]: Aml=> Collected %d DepFunc Items of %s Object \n",Index,Dev->PRS.ItemCount,&de->AslName[0]));
	} else {
		SIO_TRACE((TRACE_SIO,"SIO[%d]: Aml=> _PRS Object of %s Object is not a Buffer Type at %08X\n",Index,&de->AslName[0],prs.Object));
		return GetPrsFromTable(Dev, Index);
	}
	return Status;
}

#endif


// <AMI_PHDR_START>
//------------------------------------------------------------------------- 
//
// Procedure: EnumerateAll
//
// Description:
//This Routine fill PRS property of the Implemented devices 
//
// Input:
//
// Output: 
//
// Notes:
//------------------------------------------------------------------------- 
// <AMI_PHDR_END> 
static EFI_STATUS EnumerateAll(GSPIO *Spio){
	UINTN			i;
	SPIO_DEV		*dev;	
	EFI_STATUS		Status=0;
//-------------------
	for(i=0; i<Spio->DeviceCount; i++){
		dev=Spio->DeviceList[i];
		SIO_TRACE((TRACE_SIO,"=================================================\n"));
        SIO_TRACE((TRACE_SIO,"+> SIO[%d]; Implemented=%d; FLAGS=%X;", i, dev->DeviceInfo->Implemented, dev->DeviceInfo->Flags));  
        //Taking care of issue 1 in EIP72716 
		if (!dev->DeviceInfo->Implemented){
			SIO_TRACE((TRACE_SIO,"<-\n"));
			continue;
		}	
		if(dev->DeviceInfo->HasSetup)Status=SioSetupData(dev,TRUE);
		//For Irq reservation it might be a disabled by setup device that shares it's resources
		//It appears to be a resource owner in such case it will have field Resource consumer filled.
		SIO_TRACE((TRACE_SIO," Enabled=%d; SHR_RES=%d. <-\n",dev->NvData.DevEnable, (dev->ResConsumer!=NULL)));
		if(!dev->NvData.DevEnable) if(dev->ResConsumer==NULL) continue;
//if we don't have any ACPI support we still have to prowide _PRS for SIO devices
//#ifndef rather DEBUG
#if (!ACPI_SUPPORT)		
		switch (dev->DeviceInfo->Type){
			case dsFDC: 	Status=SetFdcPrs(dev); 
				break;
			case dsPS2CK:
			case dsPS2K: 	Status=SetPs2kPrs(dev);
				break;
			case dsPS2CM:
			case dsPS2M: 	Status=SetPs2mPrs(dev);
				break;
			case dsUART:	Status=SetUartPrs(dev);
				break;		
			case dsLPT:		Status=SetLptPrs(dev,FALSE);
				break;
			case dsGAME:	Status=SetGamePrs(dev);		
				break;
//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO
			case dsSB16:	//Status=SetSb16Prs(dev);
//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO
				break;
			case dsMPU401:	Status=SetMpu401Prs(dev);
				break;		
//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO
			case dsFmSynth: //fill this
//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO
				break;
//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO
			case dsCIR:
//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO
				break;
//			case dsGPIO:	Status=SetGpioPrs(dev);
//				break;
//			case dsHwMon:	Status=SetHhmPrs(dev);
//				break;
//			case dsPME:		Status=SetPmePrs(dev);
//				break;
//			case dsACPI:
//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO
//				break;
//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO
// Add to SIO_DEV_TYPE devices which may reside in SIO
// Fill this switch with implementatio for missed SIO_DEV_TYPE
//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO
			default : Status=GetPrsFromTable(dev, i);
		}//switch
#else
		Status=GetPrsFromAml(dev,NULL,i);
#endif
		//if ACPI Support was Installed after VariableWrite Protocol
		//we will reserve ISA IRQs now! 
		//if not we will do it when VariableWrite Event signalled.
		if(EFI_ERROR(Status)) {
			//check if device has a custom routine to get PRS settings.
			if(dev->DeviceInfo->InitRoutine){
				Status=dev->DeviceInfo->InitRoutine(&dev->AmiSio,NULL,isPrsSelect);
				SIO_TRACE((TRACE_SIO,"GSIO: DevInitRoutine(isPrsSelect) - Status=%r.\n", Status));
			}
			Status=EFI_SUCCESS;
		} 
		if(mVarWrite){
		    Status=ReserveIrq(dev, i);
		    SIO_TRACE((TRACE_SIO,"GSIO: Reserve IRQ for SIO.Device[%d] - Status=%r\n",i,Status));
		}
        SIO_TRACE((TRACE_SIO,"-------------------------------------------------\n\n"));
	}//for

	return Status;
}
	


//==================================================================================
//Functions for Driver Binding Protocol Interface
//==================================================================================
EFI_STATUS AmiSioComponentNameGetControllerName(IN EFI_COMPONENT_NAME2_PROTOCOL *This,
						IN  EFI_HANDLE                   ControllerHandle,
						IN  EFI_HANDLE                   ChildHandle        OPTIONAL,
						IN  CHAR8                        *Language,
						OUT CHAR16                       **ControllerName )
{
	return EFI_UNSUPPORTED;
}

EFI_STATUS AmiSioComponentNameGetDriverName(IN  EFI_COMPONENT_NAME2_PROTOCOL  *This,
						IN  CHAR8                        *Language,
						OUT CHAR16                       **DriverName)
{
	//Supports only English
	if(!Language || !DriverName) return EFI_INVALID_PARAMETER;

	if (!LanguageCodesEqual( Language, LANGUAGE_CODE_ENGLISH)) 
        return EFI_UNSUPPORTED;
	else 
        *DriverName=gDriverName;
	
	return EFI_SUCCESS;
}


//==============================================================================
EFI_STATUS CheckSioDevicePath(EFI_DEVICE_PATH_PROTOCOL *DevicePath)
{
    // Check if the RemainingDevicePath is valid
	if (DevicePath->Type!=ACPI_DEVICE_PATH ||
			DevicePath->SubType!= ACPI_DP ||
			NODE_LENGTH(DevicePath) != ACPI_DEVICE_PATH_LENGTH ) 
	return EFI_UNSUPPORTED;
	else return EFI_SUCCESS;
}


//==================================================================================
//Functions for Driver Binding Protocol Interface
//==================================================================================
EFI_STATUS AmiSioSupported(IN EFI_DRIVER_BINDING_PROTOCOL	*This,
						   IN EFI_HANDLE                    Controller,
						   IN EFI_DEVICE_PATH_PROTOCOL      *RemainingDevicePath)
{
	EFI_PCI_IO_PROTOCOL		*PciIo;		
	EFI_STATUS				Status;
	EFI_DEVICE_PATH_PROTOCOL	*ParentDevicePath;
	UINT8					cc[4];
	UINTN					sn,bn,dn,fn,i;
	UINT32					sid, id;
	BOOLEAN					AlreadyStarted = FALSE, m;
	GSPIO					*spio;
//---------------------------------------------------------
	//Check if it is valid Device Path 
	if(RemainingDevicePath){
		Status=CheckSioDevicePath(RemainingDevicePath);
		if(EFI_ERROR(Status))return Status;
	}

	//Check if it is real hardware or some virtual driver faking hardware
	//the real hardware has to have DevPath Protocol on it's HAndle
	Status=pBS->OpenProtocol( Controller, &gDevicePathProtocolGuid,
							(VOID **)&ParentDevicePath,	This->DriverBindingHandle,     
							Controller, EFI_OPEN_PROTOCOL_BY_DRIVER	);
	if ( EFI_ERROR(Status) && Status!= EFI_ALREADY_STARTED) return Status;
 
	pBS->CloseProtocol(Controller,&gDevicePathProtocolGuid,This->DriverBindingHandle, Controller);

	//This is real hardware we are dealing with but it has to be PCI2LPC/ISA bridge
	//So check if it has PCI IO Protocol on its Handle
	Status=pBS->OpenProtocol( Controller,&gPciIoProtocolGuid,(VOID **)&PciIo,
							This->DriverBindingHandle,Controller,EFI_OPEN_PROTOCOL_BY_DRIVER);

	if(Status==EFI_ALREADY_STARTED){
		AlreadyStarted = TRUE;
		Status=pBS->OpenProtocol(Controller,&gPciIoProtocolGuid,(VOID **)&PciIo,
							This->DriverBindingHandle,Controller,EFI_OPEN_PROTOCOL_GET_PROTOCOL);
	}
	
	if(EFI_ERROR(Status))return Status;

	//PciIo Protocol present. 
	//Read PCI Class Code Reg to find out which Device is that 
	Status=PciIo->Pci.Read(PciIo,EfiPciIoWidthUint32,PCI_REV_ID_OFFSET,1,&cc);
	ASSERT_EFI_ERROR(Status);
	if(EFI_ERROR(Status)) return Status;	
	//VendorID DevId
	Status=PciIo->Pci.Read(PciIo,EfiPciIoWidthUint32,0,1,&id);
	ASSERT_EFI_ERROR(Status);
	if(EFI_ERROR(Status)) return Status;	
	//Subsystem VendorID 
	Status=PciIo->Pci.Read(PciIo,EfiPciIoWidthUint32,0x2c,1,&sid);
	ASSERT_EFI_ERROR(Status);
	if(EFI_ERROR(Status)) return Status;	
	//Controller PCI Location 
	Status=PciIo->GetLocation(PciIo,&sn, &bn, &dn, &fn);
	ASSERT_EFI_ERROR(Status);
	if(EFI_ERROR(Status)) return Status;	

	//try to select right SIO device bridge for this sio
	Status=EFI_UNSUPPORTED;
	for(i=0; i<gSpioCount; i++){
		spio=&gSpio[i];
		
		//if(spio->SpioInfo->IsaVenDevId==-1)m=TRUE;
		//else 
		m=((spio->SpioInfo->IsaVenDevId & id) == id );
		if(!m) continue; 

		//if(spio->SpioInfo->IsaSubVenId==-1)m=TRUE;
		//else 
		m=((spio->SpioInfo->IsaSubVenId & sid) == sid);
		if(!m) continue;
		
		if(spio->SpioInfo->IsaBusNo==(UINT8)-1)m=TRUE;
		else m=(spio->SpioInfo->IsaBusNo==bn);
		if(!m) continue;

		if(spio->SpioInfo->IsaDevNo==(UINT8)-1)m=TRUE;
		else m=(spio->SpioInfo->IsaDevNo==dn);
		if(!m) continue;

		if(spio->SpioInfo->IsaFuncNo==(UINT8)-1)m=TRUE;
		else m=(spio->SpioInfo->IsaFuncNo==fn);
		if(!m) continue;

		//if we are here: The controller PCi properties matched the SPIO_LIST ITEM table
		spio->SupportedHandle=Controller;
		Status=EFI_SUCCESS;
	}			
	//Check it has to be LPC/ISA bridge who hosts SIO	
	//byte0=RevId;byte1=BaseClassCode;byte2=SubClassCode;byte3=ProgrInterface
	if( Status && ( cc[3]==PCI_CL_BRIDGE && cc[2]==PCI_CL_BRIDGE_SCL_ISA && cc[1]==0 )) Status=EFI_SUCCESS;
	
	if (!AlreadyStarted) pBS->CloseProtocol(Controller,&gPciIoProtocolGuid,This->DriverBindingHandle,Controller);

	return Status;
}


//==============================================================================================
//This Function Assumes SIO in Config Mode and LD has been selected
VOID SioRegister(SPIO_DEV *Dev, BOOLEAN Write, UINT8 Reg, UINT8 *Val){
	IoWrite8(Dev->Owner->SpioInfo->SioIndex,Reg);
	if(Write)IoWrite8(Dev->Owner->SpioInfo->SioData,*Val);
	else *Val=IoRead8(Dev->Owner->SpioInfo->SioData);
}

//==============================================================================================
//this Function Assumes SIO is in Config Mode
VOID DevSelect(SPIO_DEV *Dev){
//----------------
	IoWrite8(Dev->Owner->SpioInfo->SioIndex,Dev->Owner->SpioInfo->DevSel);
	IoWrite8(Dev->Owner->SpioInfo->SioData,Dev->DeviceInfo->LDN);
}


//==============================================================================================
//this function will probe SIO device if something "alive" there.
//this Function Assumes SIO is in Config Mode
EFI_STATUS CheckDevicePresent(SPIO_DEV *Dev){
	UINT8		val;
//---------------
	DevSelect(Dev);
	val=IoRead8(Dev->Owner->SpioInfo->SioData);
	//it must read Device's LDN
	if(Dev->DeviceInfo->LDN!=val) return EFI_NO_RESPONSE;
	else return EFI_SUCCESS;
}

//==============================================================================================
//this Function Assumes SIO is in Config Mode
VOID DevEnable(SPIO_DEV *Dev, BOOLEAN Enable){
	UINT8		v = Enable ? Dev->Owner->SpioInfo->ActivVal : Dev->Owner->SpioInfo->DeactVal;
//----------------
	DevSelect(Dev);
	IoWrite8(Dev->Owner->SpioInfo->SioIndex,Dev->Owner->SpioInfo->Activate);
	IoWrite8(Dev->Owner->SpioInfo->SioData,v);
//	Dev->Active=Enable;
}


//selects resource by number
T_ITEM_LIST *GetNumResources(T_ITEM_LIST *DfLst, UINT8 *num ){
//	ASLRF_S_HDR		*hdr;
	EFI_ASL_DepFn	*df=NULL;//*dfnp,*dfwp;
//-------------------------------------
	
	if(*num<DfLst->ItemCount){
//		hdr=(ASLRF_S_HDR*)DfLst->Items[*num];
//		if(hdr->Length==1) {	
//			dfwp=(EFI_ASL_DepFn*)hdr;
			df=(EFI_ASL_DepFn*)DfLst->Items[*num];
			return &df->DepRes;
//		}
//		if(hdr->Length==0) {	
//			dfnp=(EFI_ASL_DepFnNoPri*)hdr;
//			return &dfnp->DepRes;
//		}
//		*num=(UINT8)DfLst->ItemCount;
//		return NULL;
	} else *num=(UINT8)DfLst->ItemCount;
	return NULL; 
}


//Selects Resources by Priotity settings.
//UINT8 *num number of descriptors in Dependency list;
T_ITEM_LIST *GetPriResources(T_ITEM_LIST *DfLst, UINT8 cmp, UINT8 prf){
	UINTN				i;
	ASLRF_S_HDR			*hdr;
	EFI_ASL_DepFn		*df;		
//-------------------------------------
	for(i=0; i<DfLst->ItemCount; i++){
		df=DfLst->Items[i];
		hdr=(ASLRF_S_HDR*)df->DepFn;
		if(hdr->Length==1) {	
			if(((ASLR_StartDependentFn*)df->DepFn)->_PRI._CMP==cmp || 
				((ASLR_StartDependentFn*)df->DepFn)->_PRI._PRF==prf)
				return &df->DepRes;
		}
	} 
	return NULL; 
}


//Implement Function which(like GCD) will controll DMA resource assignment
BOOLEAN AssignDma(UINT8 ChNo, ASLRF_DFLAGS *Flags){
	UINT16		dma;
	UINTN		sz=sizeof(gAvailableIsaIrq);
	EFI_STATUS 	Status;
//------------------------	
  	Status=AmiIsaDmaMask(&gAvailableDmaChnl, TRUE);
	if(EFI_ERROR(Status)){
		SIO_TRACE((TRACE_SIO, "Unexpected Error while refreshing Var ISA_DMA_MASK. STATUS = %r\n", Status));
		return FALSE;
	}

	SIO_TRACE((TRACE_SIO, "Updating ISA_DMA_MASK = 0x%X", gAvailableIsaIrq));

	dma=(1<<ChNo);
	if((~gAvailableDmaChnl) & dma){
		gAvailableDmaChnl |= dma;
  		Status=AmiIsaDmaMask(&gAvailableDmaChnl,FALSE);
		if(EFI_ERROR(Status)){
			SIO_TRACE((TRACE_SIO, "Unexpected Error. STATUS = %r\n", Status));
			return FALSE;
		}
		SIO_TRACE((TRACE_SIO, " with 0x%X for Chnl %d\n", dma, ChNo ));
		return TRUE;
	} else return FALSE;	
}

//Implement Function which(like GCD) will controll IRQ resource assignment
BOOLEAN AssignIrq(UINT8 IrqNo, ASLRF_IFLAGS *Flags){
	UINT16		irq;
	EFI_STATUS 	Status;
//------------------------	

  	Status=AmiIsaIrqMask(&gAvailableIsaIrq, TRUE);
	if(EFI_ERROR(Status)){
		SIO_TRACE((TRACE_SIO, "Unexpected Error while refreshing Var ISA_IRQ_MASK. STATUS = %r\n", Status));
		return FALSE;
	}
	
	SIO_TRACE((TRACE_SIO, "Updating ISA_IRQ_MASK = 0x%X", gAvailableIsaIrq));

	irq=(1<<IrqNo);
	if((~gAvailableIsaIrq) & irq){
		gAvailableIsaIrq |= irq;
		gReservedIrq |= irq;
  		Status=AmiIsaIrqMask(&gAvailableIsaIrq,FALSE);
		if(EFI_ERROR(Status)){
			SIO_TRACE((TRACE_SIO, "Unexpected Error. STATUS = %r\n", Status));
			return FALSE;
		}
		SIO_TRACE((TRACE_SIO, " with 0x%X for IRQ# %d ISA_IRQ_MASK=%X gReservedIrq=%X\n", irq, IrqNo,gAvailableIsaIrq, gReservedIrq));
		return TRUE;
	} else return FALSE;	
}

BOOLEAN AssignIo(UINT16 *Base, UINT8 Len, UINT8 Aln){
	EFI_PHYSICAL_ADDRESS	addr=*Base;
	EFI_STATUS				Status;
//------------------------------------
	
	if(!gDxeSvcTbl)	return FALSE;
	Status=gDxeSvcTbl->AllocateIoSpace(EfiGcdAllocateAddress,//IN EFI_GCD_ALLOCATE_TYPE AllocateType,
								EfiGcdIoTypeIo,//IN EFI_GCD_IO_TYPE GcdIoType,
								Aln,//IN UINTN Alignment,
								Len, //IN UINT64 Length,
								&addr,//IN OUT EFI_PHYSICAL_ADDRESS *BaseAddress,
								gAmiSioDriverBinding.ImageHandle,// IN EFI_HANDLE ImageHandle,
								NULL	//IN EFI_HANDLE DeviceHandle OPTIONAL
	);
	SIO_TRACE((TRACE_SIO,"AssignIo Status=%r,*Base=%x, addr=%x, Len=%x, Aln=%x\n",Status,*Base,addr,Len,Aln));	
	if(EFI_ERROR(Status)||((*Base)!=(UINT16)addr))return FALSE;	
	*Base=(UINT16)addr;
	return TRUE;	
}



VOID *ApplyDmaRes(ASLRF_S_HDR* Hdr, SPIO_DEV* Dev,UINT8 ResNo ){
	UINT8 			dmac=0;
	UINT8			i;
	BOOLEAN			a=FALSE;
	ASLR_DMA		*dmar=(ASLR_DMA*)Hdr, *rd=NULL;
//--------------------------
	
	rd=ASLM_DMA(1,dmar->Flags._TYP,dmar->Flags._BM, dmar->Flags._SIZ,0); 
    if(rd==NULL) return rd;

	rd->_DMA=0;

	//Don't need to run all this if we got an empty descriptor
	if(!dmar->_DMA) return rd;
	
	for(i=0; i<8; i++){
		dmac=dmar->_DMA&(1<<i);
		if(dmac){
			if((Dev->DeviceInfo->Flags&SIO_SHR_DMA2) && ResNo ) a=TRUE;
			else { 
				if((Dev->DeviceInfo->Flags&SIO_SHR_DMA1) && !ResNo) a=TRUE;
				else a=AssignDma(i, &dmar->Flags);
			}
			if(a){
				UINT8 r;
			//---------------------
				if(ResNo){
					r=Dev->Owner->SpioInfo->Dma2;
					Dev->VlData.DevDma2=i;
				} else {
					r=Dev->Owner->SpioInfo->Dma1;
					Dev->VlData.DevDma1=i;
				}
				SioRegister(Dev,TRUE,r,&i);

				rd->_DMA=i;
				return rd;
			}  		
		}
	} //for 
	if(rd)pBS->FreePool(rd);
	return NULL;
}



VOID *ApplyIrqRes(ASLRF_S_HDR* Hdr, SPIO_DEV* Dev, UINT8 ResNo, BOOLEAN IrqReserve){
	UINT16 			irqm=0;
	UINT8			i;
	BOOLEAN			a=FALSE;
	ASLR_IRQ		*irqr=(ASLR_IRQ*)Hdr, *rd=NULL;	
//--------------------------
	
	SIO_TRACE((TRACE_SIO,"GSIO: Device's IRQ_MSK=%X; ",irqr->_INT));
	
	//Create Irq resource descriptors based on request 
	if(!IrqReserve){
		if(irqr->Hdr.Length==3) rd=ASLM_IRQ(1,irqr->Flags._LL,irqr->Flags._HE, irqr->Flags._SHR,0); 
		else rd=ASLM_IRQNoFlags(1,0); 
		rd->_INT=0;
	}

	//Don't need to run all this if we got an empty descriptor
	if(!irqr->_INT) {
	   SIO_TRACE((TRACE_SIO," - Device's has empty IRQ descriptor.rd=NULL\n"));
       return rd; 
    }

	
	for(i=0; i<16; i++){
		irqm=irqr->_INT&(1<<i);
		if(irqm ){
            //if we hit IRQ that was used already by some other SIO device, just skip it.
            if((IrqReserve == FALSE) && ((irqm & gUsedSioIrq ) && (!(Dev->DeviceInfo->Flags & SIO_SHR_IRQ)) ) ) continue;
            
			if((Dev->DeviceInfo->Flags&SIO_SHR_IRQ2) && ResNo ) a=TRUE;
			else {
				if((Dev->DeviceInfo->Flags&SIO_SHR_IRQ1) && !ResNo) a=TRUE;
				else {
					if(!Dev->IrqReserved) a=AssignIrq(i, &irqr->Flags);
					else a=TRUE;
				}
			}
			if(a){
				UINT8 r;
			//---------------------
				if(IrqReserve) {
					Dev->IrqReserved=TRUE;
					SIO_TRACE((TRACE_SIO,"GSIO: ApplyIrq - IrqReserve=%d. Returning NULL!",IrqReserve));
					return NULL;
				}
				//Special Case for PS2C (PS2K and PS2M in the same LD)
				if(Dev->DeviceInfo->Type==dsPS2CM) ResNo=1;				
				if(ResNo){
					r=Dev->Owner->SpioInfo->Irq2;
					Dev->VlData.DevIrq2=i;
				} else {
					r=Dev->Owner->SpioInfo->Irq1;
					Dev->VlData.DevIrq1=i;
				}
                gUsedSioIrq |= irqm;
				SIO_TRACE((TRACE_SIO,"GSIO: ApplyIrq - dsPS2CM=%d; Register=0x%X; Value=0x%X; gUsedSioIrq=0x%X.",
				(Dev->DeviceInfo->Type==dsPS2CM), r, i, gUsedSioIrq));
				SioRegister(Dev,TRUE,r,&i);
				rd->_INT=i;
				return rd;
			}
		}  		
	}
	if(rd)pBS->FreePool(rd);
	SIO_TRACE((TRACE_SIO,"GSIO: ApplyIrq - can't find resources. Returning NULL!"));
	return NULL;
}

VOID *ApplyFixedIoRes(ASLRF_S_HDR* Hdr, SPIO_DEV* Dev, UINT8 ResNo){
	BOOLEAN			a=FALSE;
	ASLR_FixedIO	*iord=(ASLR_FixedIO*)Hdr, *rd=NULL;
//--------------------------
	rd=ASLM_FixedIO(iord->_BAS, iord->_LEN);

	SIO_TRACE((TRACE_SIO,"GSIO: ApplyFixedIO BAS=%x, LEN=%x, rd=%x; ",iord->_BAS,iord->_LEN,rd));

	//Don't need to run all this if we got an empty descriptor
	if(!iord->_LEN) {
		SIO_TRACE((TRACE_SIO,"Empty Descriptor\n"));
		return rd;
	}
	
	if((Dev->DeviceInfo->Flags&SIO_SHR_IO2) && ResNo ) a=TRUE;
	else {
		if((Dev->DeviceInfo->Flags&SIO_SHR_IO1) && !ResNo) a=TRUE;
		else a=AssignIo(&rd->_BAS, rd->_LEN, 0);
	}

	if(a){
		UINT8 r, *b;
	//---------------------
		b=(UINT8*)&iord->_BAS;

		if(ResNo){
			r=Dev->Owner->SpioInfo->Base2Hi;
			Dev->VlData.DevBase2=iord->_BAS;
		} else {
			r=Dev->Owner->SpioInfo->Base1Hi;
			Dev->VlData.DevBase1=iord->_BAS;
		}
		SioRegister(Dev,TRUE,r,&b[1]);

		if(ResNo)r=Dev->Owner->SpioInfo->Base2Lo;
		else r=Dev->Owner->SpioInfo->Base1Lo;
		SioRegister(Dev,TRUE,r,&b[0]);

	    SIO_TRACE((TRACE_SIO,"r=%x,b[0]=%x,b[1]=%x\n",r,b[0],b[1]));

		return rd;
	}
	if(rd)pBS->FreePool(rd);	
	SIO_TRACE((TRACE_SIO,"returning NULL\n"));	
	return NULL;
}

VOID *ApplyIoRes(ASLRF_S_HDR* Hdr, SPIO_DEV* Dev, UINT8 ResNo){
	BOOLEAN			a=FALSE;
	ASLR_IO			*iord=(ASLR_IO*)Hdr,*rd;
	UINT8			aln=0;
//--------------------------
	rd=ASLM_IO(iord->_DEC,iord->_MIN,iord->_MAX,iord->_ALN,iord->_LEN);

	//Don't need to run all this if we got an empty descriptor
	if(!iord->_LEN) return rd;

	if((Dev->DeviceInfo->Flags&SIO_SHR_IO2) && ResNo ) a=TRUE;
	else {
		if((Dev->DeviceInfo->Flags&SIO_SHR_IO1) && !ResNo) a=TRUE;
		else {
			if((rd->_ALN) != 0)aln=rd->_ALN-1;
			a=AssignIo(&rd->_MIN, rd->_LEN,aln);
		}
	}

	if(a){
		UINT8 r, *b;
	//---------------------
		b=(UINT8*)&iord->_MIN;

		//Special Case for FDC (second resource request 0x3F7 don't have a corresponded register)
		if((Dev->DeviceInfo->Type==dsFDC) && (ResNo==1)) return rd;				

		if(ResNo){
			r=Dev->Owner->SpioInfo->Base2Hi;
			Dev->VlData.DevBase2=iord->_MIN;
		} else {
			r=Dev->Owner->SpioInfo->Base1Hi;
			Dev->VlData.DevBase1=iord->_MIN;
		}
		SioRegister(Dev,TRUE,r,&b[1]);

		if(ResNo)r=Dev->Owner->SpioInfo->Base2Lo;
		else r=Dev->Owner->SpioInfo->Base1Lo;
		SioRegister(Dev,TRUE,r,&b[0]);

		return rd;
	} 
	if(rd)pBS->FreePool(rd);
	return NULL;
}

VOID FreeIrq(SPIO_DEV *dev, ASLR_IRQ *dsc)
{
	if ((gAvailableIsaIrq & dsc->_INT) == 0) {
		gAvailableIsaIrq &= dsc->_INT;
		SioRegister(dev, TRUE, dev->Owner->SpioInfo->Irq1, 0); 
		SioRegister(dev, TRUE, dev->Owner->SpioInfo->Irq2, 0); 
	}
}

VOID FreeDma(SPIO_DEV *dev, ASLR_DMA *dsc)
{
	if ((gAvailableDmaChnl & dsc->_DMA) == 0) {
		gAvailableDmaChnl &= dsc->_DMA;
		SioRegister(dev, TRUE, dev->Owner->SpioInfo->Dma1, 0); 
		SioRegister(dev, TRUE, dev->Owner->SpioInfo->Dma2, 0); 
	}
}

VOID FreeIo(SPIO_DEV *dev, ASLRF_S_HDR	*dsc){
	
	if(dsc->Name==ASLV_RT_FixedIO){
		gDxeSvcTbl->FreeIoSpace( ((ASLR_FixedIO*)dsc)->_BAS, ((ASLR_FixedIO*)dsc)->_LEN);
	} else {
		gDxeSvcTbl->FreeIoSpace( ((ASLR_IO*)dsc)->_MIN, ((ASLR_IO*)dsc)->_LEN);
	}
	SioRegister(dev, TRUE, dev->Owner->SpioInfo->Base1Hi, 0); 
	SioRegister(dev, TRUE, dev->Owner->SpioInfo->Base1Lo, 0); 
	SioRegister(dev, TRUE, dev->Owner->SpioInfo->Base2Hi, 0); 
	SioRegister(dev, TRUE, dev->Owner->SpioInfo->Base2Lo, 0); 
}

//Free GCD resources if Tesource Tamplete Allocation failed
VOID FreeResources(SPIO_DEV *dev, T_ITEM_LIST *Res){
	UINTN 				i;
	ASLRF_S_HDR			*hdr;
	UINTN				bas,irq,dma;
//---------------------
	for(i=0, bas=0,irq=0,dma=0; i<Res->ItemCount; i++){
		hdr=(ASLRF_S_HDR*)Res->Items[i];

		switch(hdr->Name){

			case ASLV_RT_IO:
			case ASLV_RT_FixedIO: 
				bas++;
				if( (!(dev->DeviceInfo->Flags & SIO_SHR_IO1)) && (bas==1))FreeIo(dev,hdr);
				if( (!(dev->DeviceInfo->Flags & SIO_SHR_IO2)) && (bas==2))FreeIo(dev,hdr);
				break;
			case ASLV_RT_IRQ: 
				irq++;
				if( (!(dev->DeviceInfo->Flags & SIO_SHR_IRQ1)) && (irq==1))FreeIrq(dev, (ASLR_IRQ*)hdr);
				if( (!(dev->DeviceInfo->Flags & SIO_SHR_IRQ2)) && (irq==2))FreeIrq(dev, (ASLR_IRQ*)hdr);
				break;

			case ASLV_RT_DMA:
				dma++;
				if( (!(dev->DeviceInfo->Flags & SIO_SHR_DMA1)) && (dma==1))FreeDma(dev, (ASLR_DMA*)hdr);
				if( (!(dev->DeviceInfo->Flags & SIO_SHR_DMA2)) && (dma==2))FreeDma(dev, (ASLR_DMA*)hdr);
				break;
		} 
	}	
	dev->Assigned=FALSE;
}


EFI_STATUS ApplyResources(SPIO_DEV *Dev, T_ITEM_LIST *ResLst, BOOLEAN IrqReserve){
	UINTN			i;
	ASLRF_S_HDR		*hdr;
	EFI_STATUS		Status = IrqReserve ? EFI_UNSUPPORTED : EFI_SUCCESS;
	VOID			*rd;
	UINT8			irqc=0, basc=0, dmac=0;
//--------------------------------		
    SIO_TRACE((TRACE_SIO,"GSIO: ApplyResources "));
	//if device shares all resources we'll copy Resource Owner's CRS
	if(Dev->Assigned){
        SIO_TRACE((TRACE_SIO,"- Assigned Already\n"));
        return EFI_SUCCESS;
	}

    if(Dev->DeviceInfo->Flags & SIO_NO_RES){
        SIO_TRACE((TRACE_SIO,"- NO RSESOURCES USED\n"));
        return EFI_SUCCESS;
	}  

	if( (Dev->DeviceInfo->Flags & SIO_SHR_ALL )==SIO_SHR_ALL && 
			Dev->ResOwner->DeviceInfo->LDN==Dev->DeviceInfo->LDN && 
			(!IrqReserve))
	{
        SIO_TRACE((TRACE_SIO,"- Same LDN Share ALL Resources\n"));
		Dev->CRS.ItemCount=Dev->ResOwner->CRS.ItemCount;
		Dev->CRS.Items=Dev->ResOwner->CRS.Items;
		Dev->Assigned=TRUE;
		return EFI_SUCCESS;
	}
	
	for(i=0; i<ResLst->ItemCount; i++){
		rd=NULL;
		hdr=(ASLRF_S_HDR*)ResLst->Items[i];
		if (hdr->Type==ASLV_SMALL_RES){ //SIO mast have only small resources types
	//-------------------------
			switch(hdr->Name){
				case ASLV_RT_IRQ:
                    SIO_TRACE((TRACE_SIO,"- IRQ%d; IrqReserve=%d\n",irqc+1, IrqReserve));

					rd=ApplyIrqRes(hdr,Dev,irqc,IrqReserve);
					irqc++;					
					break;

				case ASLV_RT_DMA:
					if(!IrqReserve){
                        SIO_TRACE((TRACE_SIO,"- DMA%d >>",dmac+1));
						rd=ApplyDmaRes(hdr, Dev, dmac);
						dmac++;
					} else continue; 
					break;

				case ASLV_RT_IO:
					if(!IrqReserve){
                        SIO_TRACE((TRACE_SIO," IO%d >>",basc+1));
						rd=ApplyIoRes(hdr, Dev, basc);
						basc++;
					} else continue; 
					break;

				case ASLV_RT_FixedIO:
					if(!IrqReserve){
                        SIO_TRACE((TRACE_SIO,"Fixed IO%d >>",basc+1));
						rd=ApplyFixedIoRes(hdr, Dev, basc);
						basc++;
					} else continue; 
					break;
			}
		
			if(IrqReserve) continue;	
        
		    SIO_TRACE((TRACE_SIO,"rd=%x \n",rd));
			if(rd) Status=AppendItemLst(&Dev->CRS, rd);
			else Status=EFI_UNSUPPORTED;
		} else Status=EFI_UNSUPPORTED; //the SIO - doesn't supports LARGE RESOURCES  
		if (EFI_ERROR(Status)) break;
	}
    SIO_TRACE((TRACE_SIO,"\n"));

	//If Irq Reservation we no need to add any res descriptors yet
	if(IrqReserve && (Status==EFI_UNSUPPORTED)){
        SIO_TRACE((TRACE_SIO,"GSIO: ApplyResources(IrqReserve=%d) Status=EFI_SUCCESS\n",IrqReserve));
	    return EFI_SUCCESS; 
	}
	//clear resource tamplete if we fail to assign one of the members of ResLst
	if (EFI_ERROR(Status)){
		FreeResources(Dev, &Dev->CRS);
		ClearItemLst(&Dev->CRS, TRUE);
		Dev->Assigned=FALSE;
	} else Dev->Assigned=TRUE;
    SIO_TRACE((TRACE_SIO,"GSIO: ApplyResources(IrqReserve=%d) Dev->CRS count=%d; Status=%r\n",IrqReserve, Dev->CRS.ItemCount, Status));
	return Status;
}

EFI_STATUS AssignSharedResources(SPIO_DEV *Dev){
	EFI_STATUS		Status;
	UINTN			i, bas,irq,dma;
	T_ITEM_LIST		*crs=&Dev->ResOwner->CRS;
	ASLRF_S_HDR		*hdr;
	BOOLEAN			app;
//----------------------------	
	for(i=0,bas=0,irq=0,dma=0,app=FALSE; i<crs->ItemCount; i++,app=FALSE){
		hdr=crs->Items[i];
		switch(hdr->Name){
			//IO resource type
			case ASLV_RT_FixedIO:
			case ASLV_RT_IO:
				bas++;
				if( (Dev->DeviceInfo->Flags&SIO_SHR_IO1)&& (bas==1)) app=TRUE;
				if( (Dev->DeviceInfo->Flags&SIO_SHR_IO2)&& (bas==2)) app=TRUE;
			break;
			//IRQ resource
			case ASLV_RT_IRQ :
				irq++;
				if( (Dev->DeviceInfo->Flags&SIO_SHR_IRQ1)&& (irq==1)) app=TRUE;
				if( (Dev->DeviceInfo->Flags&SIO_SHR_IRQ2)&& (irq==2)) app=TRUE;
				break;
			//DMA Resource
			case ASLV_RT_DMA:
				dma++;
				if( (Dev->DeviceInfo->Flags&SIO_SHR_DMA1)&& (dma==1)) app=TRUE;
				if( (Dev->DeviceInfo->Flags&SIO_SHR_DMA2)&& (dma==2)) app=TRUE;
				break;
		} //switch
		if(app){
			Status=AppendItemLst(&Dev->CRS,(VOID*)hdr);			
			if(EFI_ERROR(Status)) return Status;
		}
	}
	return Status;	
}

//this Function Assumes SIO is in Config Mode
//and device has been selected in LDN reg
EFI_STATUS AssignResources(SPIO_DEV *Dev){
	T_ITEM_LIST		*dl, *rl;
	UINT8			p=0,c=0, n=0;
	EFI_STATUS		Status;
//------------------------------------
	SIO_TRACE((TRACE_SIO,"GSIO: AssignResources "));
	if(gDxeSvcTbl==NULL) { 
        SIO_TRACE((TRACE_SIO,"- Dxe Sevice Table NOT_FOUND, returning EFI_UNSUPPORTED\n"));
        return EFI_UNSUPPORTED;
	}	

	if(Dev->Assigned) {
        SIO_TRACE((TRACE_SIO,"- Device has Resourcs Assigned, returning EFI_SUCCESS\n"));
        return EFI_SUCCESS;
	}

	//Take care about shared resources if any
	if(Dev->DeviceInfo->Flags & SIO_SHR_ALL){
        SIO_TRACE((TRACE_SIO,"- SHARED Flags=0x%X, Status=",Dev->DeviceInfo->Flags));
		Status=AssignSharedResources(Dev);
		if(Dev->DeviceInfo->Flags==SIO_SHR_ALL) {
			Dev->Assigned=TRUE;
			Status=EFI_SUCCESS;
	    	SIO_TRACE((TRACE_SIO,"%r\n",Status));
			return Status;
		}
        SIO_TRACE((TRACE_SIO,"%r\n",Status));
		ASSERT_EFI_ERROR(Status);
	}
	
	dl=&Dev->PRS;
	
	if(Dev->NvData.DevPrsId){
		n=Dev->NvData.DevPrsId-1;
		if(n<dl->ItemCount){
			rl=GetNumResources(dl,&n);
			if(rl){
				Status=ApplyResources(Dev,rl,FALSE);
                SIO_TRACE((TRACE_SIO,"- By PrsId(%x),get DepFn(%X) Status=%r\n",Dev->NvData.DevPrsId,rl,Status));
				if(!EFI_ERROR(Status))	return Status;
			}
		}
        SIO_TRACE((TRACE_SIO,"GSIO: AssignResources Fail to reserve By PrsId,%d DepFn in Count %d is %X \n",n,dl->ItemCount,rl));
		//if we can't apply selected resources reset it to "auto" again
		Dev->NvData.DevPrsId=0;
	}
	//use Auto Resource settings
	//try to get Prioritized resources
	while( c < 3 || p < 3 ){
		rl=GetPriResources(dl,c,p);
		if(rl) {
			Status=ApplyResources(Dev,rl,FALSE);
			if(!Status) return EFI_SUCCESS;
		}
		c++; p++; 
	}
	//Fail to get Dependent Function with Priority 
	//try by number
	while( n < dl->ItemCount){
		rl=GetNumResources(dl,&n);
		if(rl) {
			Status=ApplyResources(Dev,rl,FALSE);
            SIO_TRACE((TRACE_SIO,"- By PRS Num(n=%d),get DepFn(%X) Status=%r\n",n,rl,Status));
			if(!Status) return EFI_SUCCESS;
		}
		n++;
	}
	SIO_TRACE((TRACE_SIO,"\n"));	
	return EFI_NOT_FOUND;
}

////////////////////////////////////////////////////////////////////
EFI_STATUS StartSioChildDevice(EFI_HANDLE CtrlHandle, SPIO_DEV *Dev){
	EFI_STATUS			Status=0;
	EFI_PCI_IO_PROTOCOL	*PciIo;		
//----------------------------------
	if(Dev->Started) return EFI_ALREADY_STARTED;
	//Now Install All protocols
	Status=pBS->InstallMultipleProtocolInterfaces(
				&Dev->Handle,
				&gEfiAmiSioProtocolGuid,  &Dev->AmiSio,
#if ((defined PI_SPECIFICATION_VERSION) && (PI_SPECIFICATION_VERSION >= 0x00010014))

		        &gEfiSioProtocolGuid, &Dev->EfiSioData.EfiSio, 
#endif
				&gDevicePathProtocolGuid, Dev->DevicePath, //DevPath  GUID - I/F pare
				NULL, NULL );

	SIO_TRACE((TRACE_SIO,"InstallProt()=%r.", Status));

    ASSERT_EFI_ERROR(Status);	
    if(EFI_ERROR(Status))return Status;

	Dev->Started=TRUE;

	//Open Protocol BY_CHILD_CONTROLLER to notify core we may produce CHILDS
	Status=pBS->OpenProtocol( CtrlHandle, &gPciIoProtocolGuid, &PciIo,
					gAmiSioDriverBinding.DriverBindingHandle, Dev->Handle,
					EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER);

	SIO_TRACE((TRACE_SIO,"Open(PciIo)=%r\n", Status));
    ASSERT_EFI_ERROR(Status);	
	
	return Status;	
}

EFI_STATUS ReserveIrq(SPIO_DEV *Dev, UINTN Index){
	EFI_STATUS		Status;
	T_ITEM_LIST		*dl, *rl;
	UINT8			p=0,c=0, n=0;
//------------------------------------
	if(gDxeSvcTbl==NULL) return EFI_UNSUPPORTED;	

	if(Dev->IrqReserved) return EFI_SUCCESS;
	
    if(Dev->DeviceInfo->Flags & SIO_NO_RES){
        SIO_TRACE((TRACE_SIO,"- NO RSESOURCES USED\n"));
        return EFI_SUCCESS;
	}  


	//Take care about shared resources if any
	if((Dev->DeviceInfo->Flags & SIO_SHR_IRQ) == SIO_SHR_IRQ) return EFI_SUCCESS;
	
	dl=&Dev->PRS;
	
	if(Dev->NvData.DevPrsId){
		n=Dev->NvData.DevPrsId-1; //Very first Option is AUTO Select
		if(n<dl->ItemCount){
			rl=GetNumResources(dl,&n);
			if(rl){
				Status=ApplyResources(Dev,rl,TRUE); //Reserve Interrupts
				if(!EFI_ERROR(Status))	return Status;
			}
		}
		//if we can't apply selected resources reset it to "auto" again
		Dev->NvData.DevPrsId=0;
	}
	//use Auto Resource settings
	//try to get Prioritized resources
	while( c < 3 || p < 3 ){
		rl=GetPriResources(dl,c,p);
		if(rl) {
			Status=ApplyResources(Dev,rl,TRUE);
            SIO_TRACE((TRACE_SIO,"GSIO: ReserveIrq by PRI, Status=%r\n",Status));
   			if(!Status) return EFI_SUCCESS;
		}
		c++; p++; 
	}
	//Fail to get Dependent Function with Priority 
	//try by number
	while( n < dl->ItemCount){
		rl=GetNumResources(dl,&n);
		if(rl) {
			Status=ApplyResources(Dev,rl,TRUE);
	        SIO_TRACE((TRACE_SIO,"GSIO: ReserveIrq PRS[%d], Status==%r\n",n,Status));
			if(!Status) return EFI_SUCCESS;
		}
		n++;
	}
	
	return EFI_NOT_FOUND;
}



EFI_STATUS InitSioDevice(SPIO_DEV *Dev){
	EFI_STATUS			Status=0;
	BOOLEAN			    Dis_Flag=TRUE;
//	EFI_PCI_IO_PROTOCOL	*PciIo;		
	//SPIO_DEV			*ro=NULL;//rtesource owner in case of shared resources
//-------------------------

	if (Dev->Started||Dev->Initialized) {
		SIO_TRACE((TRACE_SIO,"GSIO: InitSioDevice() Device was Started=%d Initialized=%d - returning EFI_SUCCESS\n", 
		Dev->Started, Dev->Initialized));
        return EFI_SUCCESS;	
    }

	if(!Dev->Owner->InCfgMode) SioCfgMode(Dev->Owner, TRUE);	

	//See if there actual SIO there or just empty space
	Status=CheckDevicePresent(Dev);
	SIO_TRACE((TRACE_SIO,"GSIO: InitSioDevice() - CheckDevicePresent() Status=%r",Status));
	if(Status==EFI_NO_RESPONSE) Dev->DeviceInfo->Implemented=FALSE;
	SIO_TRACE((TRACE_SIO," Implemented=%d \n",Dev->DeviceInfo->Implemented));

	if(!EFI_ERROR(Status)) {
        if(Dev->DeviceInfo->Type == dsPS2CM) Dis_Flag=FALSE; //if ps2 mouse &ps2 keyboard in same logical device,not disable it
        if(Dis_Flag){ 
	       SIO_TRACE((TRACE_SIO,"GSIO: InitSioDevice() Disabling Device\n"));
           DevEnable(Dev,FALSE);//disable all devices before programing
        }
      }
	
	if(Dev->DeviceInfo->Implemented && Dev->NvData.DevEnable){
		//if we are Initializing device with shared resources
		//make sure resource owner has it's resources Allocated! 
		if((Dev->DeviceInfo->Flags & SIO_SHR_ALL) && Dev->ResOwner){
          //we don't care about the irq share case
          if(!(Dev->DeviceInfo->Flags & SIO_SHR_IRQ)) {
			DevSelect(Dev->ResOwner);
            SIO_TRACE((TRACE_SIO,"GSIO: InitSioDevice() AssignResources(Dev->ResOwner) -"));
			Status=AssignResources(Dev->ResOwner);
	        SIO_TRACE((TRACE_SIO," Status=%r; FLAGS=0x%X\n",Status, Dev->DeviceInfo->Flags));
			if(EFI_ERROR(Status)) return Status;

          }//if
		}//if
		
		DevSelect(Dev);
		if(Dev->DeviceInfo->Flags & SIO_NO_RES) {
	        SIO_TRACE((TRACE_SIO,"GSIO: InitSioDevice() - Device has NO Resourcs\n"));
            Dev->Assigned=TRUE; 
        }else{ 
            SIO_TRACE((TRACE_SIO,"SIO InitSioDevice() AssignResources(Dev) -"));
            Status=AssignResources(Dev); //Assigned Flag is changed inside AssignResources
	        SIO_TRACE((TRACE_SIO," Status=%r\n",Status));
        }

		if(!EFI_ERROR(Status)){
			pBS->CopyMem(&Dev->AmiSio,&gAmiSioProtocol, sizeof(AMI_SIO_PROTOCOL));

#if ((defined PI_SPECIFICATION_VERSION) && (PI_SPECIFICATION_VERSION >= 0x00010014))
			pBS->CopyMem(&Dev->EfiSioData.EfiSio, &gEfiSioProtocol, sizeof(EFI_SIO_PROTOCOL));
#endif
		
			if(!Dev->DevicePath){
				ACPI_HID_DEVICE_PATH	siodp;
			//--------------------------
				siodp.Header.Type=ACPI_DEVICE_PATH;
				siodp.Header.SubType=ACPI_DP;
				SET_NODE_LENGTH(&siodp.Header,ACPI_DEVICE_PATH_LENGTH);
				siodp.HID=Dev->EisaId.HID;
				siodp.UID=Dev->EisaId.UID;
				Dev->DevicePath = DPAddNode(Dev->Owner->CntrDevPath,&siodp.Header);
	            SIO_TRACE((TRACE_SIO,"GSIO: InitSioDevice() - Set DevicePath=%X\n",Dev->DevicePath));
			}
			//Call Init BeforeActivate
			//if device is not implemented it might be needed to do some initialization 
			// even for disabled devices if so here we are 
			if(Dev->DeviceInfo->InitRoutine){
	            SIO_TRACE((TRACE_SIO,"GSIO: InitSioDevice() - Device InitRoutine(isBeforeActivate)"));
				Status=Dev->DeviceInfo->InitRoutine(&Dev->AmiSio,Dev->Owner->IsaBrgPciIo, isBeforeActivate);
				SIO_TRACE((TRACE_SIO," Status=%r\n"));				
				if(EFI_ERROR(Status))return Status;

			}
			//In config routine we might exit config mode
			if(!Dev->Owner->InCfgMode) SioCfgMode(Dev->Owner, TRUE);	
	        SIO_TRACE((TRACE_SIO,"GSIO: InitSioDevice() - Enabling Device\n"));	
			DevEnable(Dev,TRUE);
			//Call Init AfterActivate
			if(Dev->DeviceInfo->InitRoutine){
	        	SIO_TRACE((TRACE_SIO,"GSIO: InitSioDevice() - Calling InitRoutine(isAfterActivate)"));
				Status=Dev->DeviceInfo->InitRoutine(&Dev->AmiSio,Dev->Owner->IsaBrgPciIo, isAfterActivate);
				SIO_TRACE((TRACE_SIO," Status=%r\n", Status));
				if(EFI_ERROR(Status)) return Status;

			}
		} else {
		//Fail to assign device resource - so disable the device
	        SIO_TRACE((TRACE_SIO,"GSIO: InitSioDevice() - Fail to Assign Resources, Disable Device!\n"));
			Dev->Started=TRUE;
			Dev->Assigned=TRUE;
			Dev->VlData.DevImplemented=FALSE;
		}
	} else { //if device was not Implemented on the board or was disabled by setup
		//set Flags in not implemented devices to avoid creating handles on them
	    SIO_TRACE((TRACE_SIO,"GSIO: InitSioDevice() - Not Implemented or Disabled by Setup, Disable Device\n"));
		Dev->Started=TRUE;
		Dev->Assigned=TRUE;
	} 

	Dev->Initialized=TRUE;
		
	if(Dev->Owner->InCfgMode) SioCfgMode(Dev->Owner, FALSE);	

	if(Dev->DeviceInfo->HasSetup) Status=SioSetupData(Dev, FALSE);
 	SIO_TRACE((TRACE_SIO,"GSIO: InitSioDevice() - Set Device VlData(DevImplemented=%x,DevBase1=%x,DevBase2=%x,DevIrq1=%x,DevIrq2=%x,DevDma1=%x,DevDma2=%x);\n",Dev->VlData.DevImplemented,Dev->VlData.DevBase1,Dev->VlData.DevBase2,Dev->VlData.DevIrq1,Dev->VlData.DevIrq2,Dev->VlData.DevDma1,Dev->VlData.DevDma2));
	SIO_TRACE((TRACE_SIO,"GSIO: InitSioDevice() - Set Device NvData(DevEnable=%x,DevPrsId=%x,DevMode=%x)\n",Dev->NvData.DevEnable,Dev->NvData.DevPrsId,Dev->NvData.DevMode));
	return Status;
}

EFI_STATUS AmiSioStart(IN EFI_DRIVER_BINDING_PROTOCOL		*This,
					   IN EFI_HANDLE						Controller,
					   IN EFI_DEVICE_PATH_PROTOCOL			*RemainingDevicePath )
{
	EFI_PCI_IO_PROTOCOL		*PciIo;		
	EFI_STATUS			Status=EFI_SUCCESS,StatusRdp=EFI_SUCCESS;
	INTN				i;
	UINTN				j,k;
	SPIO_DEV			*dev;
	ACPI_HID_DEVICE_PATH	*dp=NULL;
	GSPIO				*spio;
    BOOLEAN             AllStarted=TRUE;
    BOOLEAN             GcdIndex=TRUE;
    BOOLEAN             Init_Flag=FALSE;
#ifdef EFI_DEBUG
    CHAR8               *DpString=NULL;
#endif
//--------------------------------
#if ACPI_SUPPORT
	if(!gPDsdt) return EFI_DEVICE_ERROR;
#endif
    PROGRESS_CODE(DXE_SIO_INIT);
	SIO_TRACE((TRACE_SIO,"GSIO: AmiSioStart() - gSpio=%x,gSpioCount=%x\n",gSpio,gSpioCount));
	for(j=0; j<gSpioCount; j++){
		spio=&gSpio[j];	
	    SIO_TRACE((TRACE_SIO,"\nSIO: AmiSioStart() - SIO[%d] SupportController=%X, This Controller=%X\n",j,spio->SupportedHandle,Controller));	
		if(spio->SupportedHandle!=Controller) continue;
		if(!spio->CntrDevPath){
			Status=pBS->OpenProtocol( Controller, &gDevicePathProtocolGuid,
								(VOID **)&dp,This->DriverBindingHandle,     
								Controller, EFI_OPEN_PROTOCOL_GET_PROTOCOL	);
			if(EFI_ERROR(Status) && Status!= EFI_ALREADY_STARTED) return Status;
			spio->CntrDevPath=DPCopy((EFI_DEVICE_PATH_PROTOCOL*)dp);
			pBS->CloseProtocol(Controller,&gDevicePathProtocolGuid,This->DriverBindingHandle, Controller);
			spio->CntrHandle=Controller;
			//To Create a chain of childs
			Status=pBS->OpenProtocol( Controller,&gPciIoProtocolGuid,(VOID **)&PciIo,
								  This->DriverBindingHandle,Controller,EFI_OPEN_PROTOCOL_BY_DRIVER);
			//if there are 2 or more SIO on the same LPC Bridge it should return something like that
			if(EFI_ERROR(Status)) {
				if(Status!=EFI_ALREADY_STARTED)	return Status;	
				//Try to scan back and find opend PciIoProtocol for the previouse SIO
	            SIO_TRACE((TRACE_SIO,"GSIO: AmiSioStart() - The BindingDriver has been opened PciIo protocol for formor SIO chip=%X\n"));	
				for (i=j-1; i>=0; i--)if(gSpio[i].CntrHandle==Controller) spio->IsaBrgPciIo=gSpio[i].IsaBrgPciIo;
				if(!spio->IsaBrgPciIo) return EFI_DEVICE_ERROR;
			} else spio->IsaBrgPciIo=PciIo;
			//Reserve SIO Index/Data port in GCD
	        SIO_TRACE((TRACE_SIO,"GSIO: AmiSioStart() - SIO[%d] =>Assign cfg Index=%X\n",j,spio->SpioInfo->SioIndex));
        //it is not first sio index and it is different with former index.

         if(j) {
			for (i=j-1; i>=0; i--)  
              if( (gSpio[i].SpioInfo)->SioIndex==spio->SpioInfo->SioIndex ) {
                  GcdIndex=FALSE;
                  break;
              }
          }
			//Reserve SIO Index/Data port in GCD when it is first io index or the index is different with other
          if(GcdIndex) {
			if(!AssignIo(&spio->SpioInfo->SioIndex, 1, 0)) continue;	
			if(!AssignIo(&spio->SpioInfo->SioData, 1, 0)) continue;	
          }
		} //if(!spio->CntrDevPath)

		dp=(ACPI_HID_DEVICE_PATH*)RemainingDevicePath;
		
		SIO_TRACE((TRACE_SIO,"\nGSIO: Starting ... RDP= %X\n",(UINTN)RemainingDevicePath));
	
    for(k=0;k<2;k++){
		//Locate Right SIO Device
		for (i=0; (UINTN)i<spio->DeviceCount; i++){
            Status=EFI_SUCCESS;
			dev=spio->DeviceList[i];
            if((k==0)&&(dev->DeviceInfo->Type==dsUART)&&(dev->NvData.DevPrsId!=0)){
			   SIO_TRACE((TRACE_SIO,"\nSIO[%d]Dev[%d] InitSio Starting: first time=>\n",j,i));
               Init_Flag=TRUE;
            }
            if((k==1)&&((dev->DeviceInfo->Type!=dsUART)||(dev->NvData.DevPrsId==0))){
			   SIO_TRACE((TRACE_SIO,"\nSIO[%d]Dev[%d] InitSio Starting: second time=>\n",j,i));
               Init_Flag=TRUE;
            }
            if(Init_Flag) {
              	Status=InitSioDevice(dev);
                Init_Flag=FALSE;
            }
            else continue;

			SIO_TRACE((TRACE_SIO,"InitSioDevice()=%r;\n ", Status));
			if(EFI_ERROR(Status)){
				if (Status == EFI_NO_RESPONSE) {
			    SIO_TRACE((TRACE_SIO,"Device check EFI_NO_RESPONSE,Continue next device...\n",j,i));
                continue;
               }else {
			   SIO_TRACE((TRACE_SIO,"=>ERROR,Stop  AmiSioStart...<=\n",j,i));
               return Status;}
			}

			if(RemainingDevicePath==NULL){
				SIO_TRACE((TRACE_SIO,"Start SIO[%d]Dev[%d] ChildDevice:",j,i));
				Status=StartSioChildDevice(Controller,dev);
				SIO_TRACE((TRACE_SIO,"StartSioDev()=%r; Hnd=%X;\n", Status, dev->Handle));
			
				if(EFI_ERROR(Status)){
                    if(Status!=EFI_ALREADY_STARTED){
					    return Status; 	
				    } else Status=EFI_SUCCESS;
                } else AllStarted=FALSE;
				SIO_TRACE((TRACE_SIO,"AllStarted=%X;\n", AllStarted));
			} else {
				SIO_TRACE((TRACE_SIO,"RemainingDevicePath is not Null,HID(%x)_UID(%x)\n",dp->HID,dp->UID));
                StatusRdp=EFI_NOT_FOUND;
			    if(dp->HID==dev->EisaId.HID && dp->UID==dev->EisaId.UID){
				    StatusRdp=StartSioChildDevice(Controller,dev);
				    SIO_TRACE((TRACE_SIO,"RDP; StartSioDev()=%r; Hnd=%X;\n", StatusRdp, dev->Handle));
				    //break; //return Status;
			    }
            }
		    SIO_TRACE((TRACE_SIO,"\n"));
		}//for i
      }//for j
	}// for k
	//if(AllStarted && RemainingDevicePath==NULL) CreateSioDevStatusVar();  
    CreateSioDevStatusVar();  
    
    if(RemainingDevicePath!=NULL) {
		SIO_TRACE((TRACE_SIO,"\nSIO: AmiSioStart() - returning RdpStatus = %r\n", StatusRdp));
    	return StatusRdp;
    }

    if(AllStarted) Status=EFI_ALREADY_STARTED;
    else  Status=EFI_SUCCESS;
	SIO_TRACE((TRACE_SIO,"\nSIO: AmiSioStart() - AllStarted=%d, returning %r\n", AllStarted, Status));
	return Status;

}


EFI_STATUS StopSioDevice(SPIO_DEV *Dev,EFI_HANDLE Controller)
{
	EFI_STATUS 				Status=EFI_SUCCESS;
//--------------------------------------------------------------------

    if(Dev->DeviceInfo->Implemented==FALSE || Dev->VlData.DevImplemented==FALSE){
        SIO_TRACE((TRACE_SIO,"GSIO: StopSioDevice - Device is NOT Implemented, returning EFI_SUCCESS\n"));
        return Status;
    }

    if(Dev->Started==FALSE) return Status;    

	Status=pBS->CloseProtocol(Controller,&gPciIoProtocolGuid,
			gAmiSioDriverBinding.DriverBindingHandle, Dev->Handle);


	SIO_TRACE((TRACE_SIO,"GSIO: Closing(PciIo)=%r; ", Status));
    ASSERT_EFI_ERROR(Status);
	if(EFI_ERROR(Status))return Status;	


	Status=pBS->UninstallMultipleProtocolInterfaces(
					Dev->Handle,
					&gEfiAmiSioProtocolGuid,&Dev->AmiSio,
#if ((defined PI_SPECIFICATION_VERSION) && (PI_SPECIFICATION_VERSION >= 0x00010014))
			        &gEfiSioProtocolGuid, &Dev->EfiSioData.EfiSio, 
#endif
					&gDevicePathProtocolGuid,Dev->DevicePath,
					NULL, NULL );
	SIO_TRACE((TRACE_SIO,"Uninstalling(AmiSio;"));
#if ((defined PI_SPECIFICATION_VERSION) && (PI_SPECIFICATION_VERSION >= 0x00010014))
	SIO_TRACE((TRACE_SIO," EfiSio;")); 
#endif 
    SIO_TRACE((TRACE_SIO," DevPath)=%r;\n", Status));
    ASSERT_EFI_ERROR(Status);
	if(EFI_ERROR(Status)) 	return Status;

	//don't need to free and clear the device path buffer of the device 
	//- it not going to change any way. Just care not to create it over again 
	//when Start function will be called
	Dev->Handle=NULL;
	Dev->Started=FALSE;
	DevEnable(Dev, FALSE); 

	Status = DisableDevInSioDevStatusVar(Dev);

	if(EFI_ERROR(Status))SIO_TRACE((TRACE_SIO,"GSIO: Stop=> %r - Update SioDevStatusVar.\n", Status));
    ASSERT_EFI_ERROR(Status);

	return Status;
}	



EFI_STATUS AmiSioStop(IN EFI_DRIVER_BINDING_PROTOCOL			*This,
					   IN EFI_HANDLE						Controller,
					   IN UINTN								NumberOfChildren,
					   IN EFI_HANDLE						*ChildHandleBuffer)
{
	EFI_STATUS	Status;
	UINTN		i,j,k,cnt=0;	
	SPIO_DEV	*dev;
	GSPIO		*spio;
//------------------------
	SIO_TRACE((TRACE_SIO,"\nGenericSIOStop: gSpioCount=%d, NumberOfChildren=0x%X, Controller=0x%X\n",
                            gSpioCount, NumberOfChildren, Controller));

	for(k=0,j=0; k<gSpioCount; k++){
		spio=&gSpio[k];
		if(spio->CntrHandle!=Controller) continue;

		if (!NumberOfChildren) {
			for(i=0; i<spio->DeviceCount; i++){
				SIO_TRACE((TRACE_SIO,"SIO[%d] Stopping: ", i));
                dev=spio->DeviceList[i];
                if(dev->Started) Status=StopSioDevice(spio->DeviceList[i], Controller);
				SIO_TRACE((TRACE_SIO,"%r.\n", Status));
				if(EFI_ERROR(Status)) return Status;
 			}
            //If everything OK we should close PciIo Protocol that we opened BY_DRIVER
            //In case of multiple SIO on the same LPC Bridge this code can cause ERROR_STATUS.
            Status=pBS->CloseProtocol(Controller,&gPciIoProtocolGuid,This->DriverBindingHandle,Controller);
            if(EFI_ERROR(Status)){
                SIO_TRACE((TRACE_SIO, "\nAttempt to Close LpcBrg PCI_IO was UNSUCCESSFUL %r!\n", Status));
                Status=EFI_SUCCESS;// clear error status Status.
            }
 		} else {
			for( ;j<NumberOfChildren; j++){

				for(i=0; i<spio->DeviceCount; i++){
					dev=spio->DeviceList[i];

					if(dev->Handle==ChildHandleBuffer[j]){		
						SIO_TRACE((TRACE_SIO,"SIO[%d] Stopping: ", i));
						Status=StopSioDevice(dev,Controller);
						SIO_TRACE((TRACE_SIO,"%r.\n", Status));
						if(EFI_ERROR(Status)) return Status;
						cnt++;
						break;
					}
				} //for i
			} //for j				
		} //else
        spio->CntrDevPath=NULL;
 	}//for k	
	
	if(NumberOfChildren && (!cnt)) Status=EFI_NOT_FOUND;
    ASSERT_EFI_ERROR(Status);

    return Status;
}



//AmiSIO Protocol Functions Implementation
EFI_STATUS AmiSioRegister(IN AMI_SIO_PROTOCOL		*This,
						IN BOOLEAN				Write,
						IN BOOLEAN				ExitCfgMode,					
						IN UINT8            	Register,
    					IN OUT UINT8        	*Value)
{
	SPIO_DEV	*dev=(SPIO_DEV*)This;	
//-----------------------------------	
	if(!This || !Value || Register>SIO_MAX_REG ) return EFI_INVALID_PARAMETER;
	
	if(!dev->Owner->InCfgMode) SioCfgMode(dev->Owner, TRUE);	
	
	DevSelect(dev);
	SioRegister(dev, Write, Register, Value);

	if(ExitCfgMode) {
		if(dev->Owner->InCfgMode) SioCfgMode(dev->Owner, FALSE);	
	} 
	return EFI_SUCCESS;

}

EFI_STATUS AmiSioCRS(IN AMI_SIO_PROTOCOL	*This,
				    IN BOOLEAN 				Set,
					IN OUT T_ITEM_LIST		**Resources)
{
	EFI_STATUS	Status;
	SPIO_DEV		*dev=(SPIO_DEV*)This;	
//-----------------------------------	
	if (!This || !Resources) return EFI_INVALID_PARAMETER;
	
	if (Set) {
		FreeResources(dev, &dev->CRS);
//		ClearResLst(&dev->CRS);
		ClearItemLst(&dev->CRS, TRUE);
		Status = ApplyResources(dev, *Resources, FALSE);
//		ProgramResources(dev);
	} else {
		CopyItemLst(&dev->CRS, Resources); 
//		*Resources=&dev->CRS;
	}

	return EFI_SUCCESS;
}


#if ((defined PI_SPECIFICATION_VERSION) && (PI_SPECIFICATION_VERSION >= 0x00010014))

EFI_STATUS EfiSioRegisterAccess(
  IN   CONST  EFI_SIO_PROTOCOL  *This,
  IN          BOOLEAN           Write,
  IN          BOOLEAN           ExitCfgMode,
  IN          UINT8             Register,
  IN OUT      UINT8             *Value)
{
    EFI_SIO_DATA    *EfiSioData=(EFI_SIO_DATA*)This;
//---------------------
	if(This==NULL) return EFI_INVALID_PARAMETER;
    
    return AmiSioRegister(&EfiSioData->Owner->AmiSio,Write,ExitCfgMode,Register,Value);     
    
}

EFI_STATUS EfiSioGetRes(T_ITEM_LIST *AmiResLst, ACPI_RESOURCE_HEADER_PTR  *EfiResLst){
    UINTN                       i, sz=0;
    ASLRF_S_HDR                 *pRes;
    VOID                        *EfiSioRes=NULL;       
    UINT8                       *p8;
//----------------
    for(i=0; i<AmiResLst->ItemCount; i++){
        pRes=(ASLRF_S_HDR*)AmiResLst->Items[i];
        if(pRes->Type==ASLV_SMALL_RES) sz+=(UINTN)pRes->Length;
        else sz+=((ASLRF_L_HDR*)pRes)->Length;
    }

    EfiSioRes=Malloc(sz+sizeof(ASLR_EndTag));
    if(EfiSioRes==NULL) return EFI_OUT_OF_RESOURCES;

    for(i=0,p8=EfiSioRes; i<AmiResLst->ItemCount; i++){
        pRes=(ASLRF_S_HDR*)AmiResLst->Items[i];
        if(pRes->Type==ASLV_SMALL_RES) sz=(UINTN)pRes->Length;
        else sz=(UINTN)((ASLRF_L_HDR*)pRes)->Length;
        
        MemCpy(p8,(VOID*)pRes, sz);        
        p8+=sz;        
    }
    
    ((ASLR_EndTag*)p8)->Hdr.HDR=ASLV_END_TAG_HDR;
	((ASLR_EndTag*)p8)->Chsum=0;
    
    EfiResLst->SmallHeader=EfiSioRes;
    
    return EFI_SUCCESS;
}


EFI_STATUS EfiSioGetResourcces( 
  IN  CONST EFI_SIO_PROTOCOL            *This,
  OUT       ACPI_RESOURCE_HEADER_PTR    *ResourceList)
{
    EFI_STATUS      Status;
    EFI_SIO_DATA    *EfiSioData=(EFI_SIO_DATA*)This;
    T_ITEM_LIST		*ResLst=NULL; //if NULL new Buffer will be allocated...
    UINTN           EfiSioBuffSize=0;
//---------------------
	if(This==NULL || ResourceList==NULL) return EFI_INVALID_PARAMETER;

    //Get resources in AMI SIO format...
	Status=AmiSioCRS(&EfiSioData->Owner->AmiSio, FALSE, &ResLst);
    ASSERT_EFI_ERROR(Status);
    if(EFI_ERROR(Status)) return Status;

    //Convert it to EFI_SUPER_IO format.
    Status=EfiSioGetRes(ResLst, ResourceList);
    ASSERT_EFI_ERROR(Status);
    return Status;
}


EFI_STATUS EfiSioSetRes(T_ITEM_LIST *AmiResLst, ACPI_RESOURCE_HEADER_PTR  EfiResLst){
    UINTN       sz=0;
    UINT8       *p8;
    EFI_STATUS  Status;
//----------------
    p8=(UINT8*)EfiResLst.SmallHeader;
        
    //Convert resources to AMI_SIO format.
    while( ((ASLR_EndTag*)p8)->Hdr.HDR!=ASLV_END_TAG_HDR ){
        if( ((ASLRF_S_HDR*)p8)->Type==ASLV_SMALL_RES )sz=(UINTN)((ASLRF_S_HDR*)p8)->Length;
        else sz=(UINTN)((ASLRF_L_HDR*)p8)->Length;
        
        Status=AppendItemLst(AmiResLst, p8);
        ASSERT_EFI_ERROR(Status);
        if(EFI_ERROR(Status)) return Status;
        
        p8+=sz;
    }
    return Status;
}

EFI_STATUS EfiSioSetResources(
  IN CONST  EFI_SIO_PROTOCOL        *This,
  IN        ACPI_RESOURCE_HEADER_PTR ResourceList)
{
    EFI_STATUS      Status;
    EFI_SIO_DATA    *EfiSioData=(EFI_SIO_DATA*)This;
    T_ITEM_LIST		*ResLst=NULL; //if NULL new Buffer will be allocated...
    UINTN           EfiSioBuffSize=0;
//---------------------
	if(This==NULL || ResourceList.SmallHeader==NULL) return EFI_INVALID_PARAMETER;

    //Get Bubber for T_ITEM_LIST object...
    ResLst=(T_ITEM_LIST*)MallocZ(sizeof(T_ITEM_LIST));
    if(ResLst==NULL) return EFI_OUT_OF_RESOURCES;

    //Convert resources to AMI_SIO format.
    Status=EfiSioSetRes(ResLst, ResourceList);
    ASSERT_EFI_ERROR(Status);
    if(EFI_ERROR(Status)) return Status;
    
	//Submit converted resources.
    return AmiSioCRS(&EfiSioData->Owner->AmiSio, TRUE, &ResLst);
}


EFI_STATUS EfiSioPrs(T_ITEM_LIST *AmiPrsLst, ACPI_RESOURCE_HEADER_PTR  *EfiResLst){
    UINTN                       i,j, sz=0;
    ASLRF_S_HDR                 *pRes;
    EFI_ASL_DepFn               *pPrs;
    VOID                        *EfiSioPrs=NULL;       
    UINT8                       *p8;
//----------------
    for(i=0; i<AmiPrsLst->ItemCount; i++){
        pPrs=(EFI_ASL_DepFn*)AmiPrsLst->Items[i];
        pRes=pPrs->DepFn;
        sz+=pRes->Length;
        
        for(j=0; j<pPrs->DepRes.ItemCount; j++){
            pRes=(ASLRF_S_HDR*)pPrs->DepRes.Items[j];
            if(pRes->Type==ASLV_SMALL_RES) sz+=(UINTN)pRes->Length;
            else sz+=((ASLRF_L_HDR*)pRes)->Length;
        }
    }

    //Allocate Buffer including EndDepFn object + Resource EndTag
    EfiSioPrs=Malloc(sz+sizeof(ASLR_EndTag)+sizeof(ASLV_RT_EndDependentFn));
    if(EfiSioPrs==NULL) return EFI_OUT_OF_RESOURCES;

    //Dump everything in buffer.
    for(i=0,p8=EfiSioPrs; i<AmiPrsLst->ItemCount; i++){
        pPrs=(EFI_ASL_DepFn*)AmiPrsLst->Items[i];
        //Copy StartDepFn Object...
        pRes=pPrs->DepFn;
        sz=pRes->Length;
        MemCpy(p8,(VOID*)pRes, sz);        
        p8+=sz;

        for(j=0; j<pPrs->DepRes.ItemCount; j++){
            pRes=(ASLRF_S_HDR*)pPrs->DepRes.Items[j];
        
            if(pRes->Type==ASLV_SMALL_RES) sz=(UINTN)pRes->Length;
            else sz=(UINTN)((ASLRF_L_HDR*)pRes)->Length;
        
            MemCpy(p8,(VOID*)pRes, sz);        
            p8+=sz;        
        }
    }
    
    ((ASLRF_S_HDR*)p8)->Name=ASLV_RT_EndDependentFn;
    ((ASLRF_S_HDR*)p8)->Type=ASLV_SMALL_RES;
    ((ASLRF_S_HDR*)p8)->Length=sizeof(ASLV_RT_EndDependentFn);
    p8+=sizeof(ASLRF_S_HDR);

    ((ASLR_EndTag*)p8)->Hdr.HDR=ASLV_END_TAG_HDR;
	((ASLR_EndTag*)p8)->Chsum=0;
    
    EfiResLst->SmallHeader=EfiSioPrs;
    
    return EFI_SUCCESS;
}

EFI_STATUS EfiSioPossibleResources(
  IN  CONST EFI_SIO_PROTOCOL         *This,
  OUT       ACPI_RESOURCE_HEADER_PTR *ResourceCollection)
{
    EFI_STATUS      Status;
    EFI_SIO_DATA    *EfiSioData=(EFI_SIO_DATA*)This;
    T_ITEM_LIST		*ResLst=NULL; //if NULL new Buffer will be allocated...
//----------------------------------
	if(This==NULL || ResourceCollection==NULL) return EFI_INVALID_PARAMETER;

    //Get PRS in AMI SIO format...
	Status=AmiSioPRS(&EfiSioData->Owner->AmiSio, FALSE, &ResLst);
    ASSERT_EFI_ERROR(Status);
    if(EFI_ERROR(Status)) return Status;

    //Convert it to EFI_SUPER_IO format.
    Status=EfiSioPrs(ResLst, ResourceCollection);
    ASSERT_EFI_ERROR(Status);

    return Status;
}

EFI_STATUS EfiSioModify(
  IN CONST EFI_SIO_PROTOCOL         *This,
  IN CONST EFI_SIO_REGISTER_MODIFY  *Command,
  IN       UINTN                    NumberOfCommands)
{
    EFI_STATUS      Status;
    EFI_SIO_DATA    *EfiSioData=(EFI_SIO_DATA*)This;
    UINTN           i;
    UINT8           val;
    BOOLEAN         ExitCfg;
//----------------------------------
	if(This==NULL || Command==NULL) return EFI_INVALID_PARAMETER;
    
    if(NumberOfCommands==0) return EFI_SUCCESS;
    
    for(i=0; i<NumberOfCommands; i++){
        if(i<NumberOfCommands-1)ExitCfg=FALSE;
        else ExitCfg=TRUE;
        
        //Read Register
        Status=AmiSioRegister(&EfiSioData->Owner->AmiSio, FALSE, ExitCfg,
                              Command->Register, &val);
        ASSERT_EFI_ERROR(Status);
        if(EFI_ERROR(Status)) return Status;

        val&=Command->AndMask;
        val|=Command->OrMask;

        Status=AmiSioRegister(&EfiSioData->Owner->AmiSio, TRUE, ExitCfg,
                              Command->Register, &val);
        ASSERT_EFI_ERROR(Status);
        if(EFI_ERROR(Status)) return Status;

    }    
    return Status;
}
#endif


EFI_STATUS AmiSioPRS(IN AMI_SIO_PROTOCOL	*This,
				    IN BOOLEAN 				Set,
					IN OUT T_ITEM_LIST		**Resources)
{
	SPIO_DEV		*dev=(SPIO_DEV*)This;	
//---------------------------------------
	if(Set) return EFI_UNSUPPORTED;
	CopyItemLst(&dev->PRS, Resources); 
//	*Resources=&dev->PRS;	
	return EFI_SUCCESS;
}

//Routine to transit Sio in/from Config Mode.
static VOID BootScriptSioCfgMode(GSPIO *Sio, BOOLEAN Enter, EFI_BOOT_SCRIPT_SAVE_PROTOCOL *BootScriptSave)
{
	UINTN				i;
	SPIO_SCRIPT_LST		*sl;

//---------------------------------
	if(Enter)sl=Sio->SpioInfo->EnterCfgMode;
	else sl=Sio->SpioInfo->ExitCfgMode;

    if(sl==NULL) return;

	for (i=0; i<sl->InstrCount; i++){
		switch (sl->OpType){
			case cfgNone: 
				break;
			case cfgByteSeq:
			{
				SPIO_SCRIPT  *Instr = (SPIO_SCRIPT*) sl->Instruction[0];
				SPIO_SCRIPT	*cmd = &Instr[i];
				UINT16		reg;
			//------------------------
				if(cmd->IdxDat)reg=Sio->SpioInfo->SioIndex;
				else reg=Sio->SpioInfo->SioData;
				
				if (cmd->WrRd) {
					BOOT_SCRIPT_S3_IO_WRITE_MACRO(BootScriptSave,
						EfiBootScriptWidthUint8,
						reg, 1, &cmd->Value
					);
				} else {
					//This waits until SIO provides a specific value.
					//This unsupported by boot script Io read/writes.

					//<markw>I know of no SIO that needs this.
					//If needed, SIO S3 resume must be implemented differently
					// than the normal boot script.
					SIO_TRACE((TRACE_SIO,"GSIO: Reading Index/Data SIO registers not supported entering/exit in for S3 resume.\n"));
					ASSERT_EFI_ERROR(EFI_UNSUPPORTED);
				}
				break;
			}
			case cfgRoutine:
			{
				//Implementing a generic routine like this is difficult using boot scripts in this
				//SIO implementation.
				//Use cfgByteSeq.
				SIO_TRACE((TRACE_SIO,"GSIO: cfgRoutine in SIO not supported for S3 resume. Use cfgByteSeq for enter/exit config space in IOx.c.\n"));
				ASSERT_EFI_ERROR(EFI_UNSUPPORTED);
			}
				break;
			default: return;
		}//switch
	}//for
	Sio->InCfgMode=Enter;
	return;
}

VOID BootScriptSioDevSelect(SPIO_DEV *Dev, EFI_BOOT_SCRIPT_SAVE_PROTOCOL *BootScriptSave){

		BOOT_SCRIPT_S3_IO_WRITE_MACRO(BootScriptSave,
			EfiBootScriptWidthUint8,
			Dev->Owner->SpioInfo->SioIndex, 1, &Dev->Owner->SpioInfo->DevSel);

		BOOT_SCRIPT_S3_IO_WRITE_MACRO(BootScriptSave,
			EfiBootScriptWidthUint8,
			Dev->Owner->SpioInfo->SioData, 1, &Dev->DeviceInfo->LDN	);
}

static VOID CallbackReadyToBoot(IN EFI_EVENT Event,	IN VOID	*Context)
{
	EFI_BOOT_SCRIPT_SAVE_PROTOCOL *bss;
	EFI_STATUS	Status;
	UINTN		i, j, s, ari;//, cnt1,cnt2;
	UINT8		b,r;
	BOOLEAN		devsel, devact, cfgmod;
	SPIO_DEV	*dev;
	GSPIO		*spio;
//----------------------------------

	Status = pBS->LocateProtocol(&gEfiBootScriptSaveGuid,NULL,&bss);
	if (EFI_ERROR(Status)) {
		SIO_TRACE((TRACE_SIO,"GSIO: FAIL to locate EfiBootScriptSaveProtocol %r",Status));
		return;
	}
	
	for(s=0;s<gSpioCount;s++){	
		cfgmod=FALSE;
		spio=&gSpio[s];
		if(!spio->InCfgMode) SioCfgMode(spio, TRUE);
        spio->BootScript=bss;	

		//first Check if something changed in Global Config regs programming
		for(i=0;  i<spio->SpioInfo->GlobalInclRegCount; i++){
			//if we got DevSel register just skip it
			r=spio->SpioInfo->GlobalIncludeReg[i];
			if((r==spio->SpioInfo->Activate)||(r==spio->SpioInfo->DevSel)) continue;
			//select register
			IoWrite8(spio->SpioInfo->SioIndex,r);		
			//read actual data
			b=IoRead8(spio->SpioInfo->SioData);
			//if nothing has changed just skip it
			if(b==spio->GlobalCfgDump[i]) continue; 

			//enter config mode only if we really need it
			if(!cfgmod){
				BootScriptSioCfgMode(spio,TRUE,bss);
				cfgmod=TRUE;
			}	
			//if this reg was different before the initialization of SIO - record that into boot script
			BOOT_SCRIPT_S3_IO_WRITE_MACRO(bss,EfiBootScriptWidthUint8,spio->SpioInfo->SioIndex, 1, &r);
			BOOT_SCRIPT_S3_IO_WRITE_MACRO(bss,EfiBootScriptWidthUint8,spio->SpioInfo->SioData, 1, &b);
		}
		
		//Found out Activate register index in spio->SpioInfo->LocalIncludeReg[] buffer
		//it must be in LocalIncludeReg[] Buffer
		for(ari=0; ari<spio->SpioInfo->LocalInclRegCount; ari++) 
			if(spio->SpioInfo->LocalIncludeReg[ari]==spio->SpioInfo->Activate)break;

		//Now check Local registers - unique for each device
		for (j=0; j<spio->DeviceCount; j++) {

		//---------------------
			devsel=FALSE;
			dev=spio->DeviceList[j];
			//found out if device was active after PEI phase before DXE SIO Intialization
			devact=(dev->LocalCfgDump[ari]==spio->SpioInfo->ActivVal);
			DevSelect(dev);

			//check current device active status
			IoWrite8(spio->SpioInfo->SioIndex,spio->SpioInfo->Activate);
			b=IoRead8(spio->SpioInfo->SioData);
			
			//if device is NOT active now and was NOT active before just skip it 
			if( (b==spio->SpioInfo->DeactVal) && (dev->LocalCfgDump[ari]==spio->SpioInfo->DeactVal)) continue;
		
			//if before and after device was ACTIVE that means - nothing has changed 
			//in Device Active Status. We need not to add this device in boot script
			if((b==spio->SpioInfo->ActivVal)&&(dev->LocalCfgDump[ari]==spio->SpioInfo->ActivVal));
			else{
				//before and after SIO Init Activate register values does not mutch	
				//we need to enter config mode if not in config mode yet and select the device 
				if(!cfgmod){ //if still not in config mode
					BootScriptSioCfgMode(spio,TRUE,bss);
					cfgmod=TRUE;
				}	
				if(!devsel){//device has not been selected
					BootScriptSioDevSelect(dev, bss);
					devsel=TRUE;
				}	
				//Device was Active after PEI phase, but now it is NOT
				if(devact){
					BOOT_SCRIPT_S3_IO_WRITE_MACRO(bss,EfiBootScriptWidthUint8,spio->SpioInfo->SioIndex, 1, &spio->SpioInfo->Activate);
					BOOT_SCRIPT_S3_IO_WRITE_MACRO(bss,EfiBootScriptWidthUint8,spio->SpioInfo->SioData, 1, &spio->SpioInfo->DeactVal);
					devact=FALSE; 
				}
				if(b==spio->SpioInfo->DeactVal)continue;
			}

			//if we are here that means - Device is active after DXE initialization 
			//and we must check if something gets changed in Generic register programming
			for(i=0;  i<spio->SpioInfo->LocalInclRegCount; i++) {
				r=spio->SpioInfo->LocalIncludeReg[i];
				//We took care about activate register erlier 	
				if((r==spio->SpioInfo->Activate)||(r==spio->SpioInfo->DevSel)) continue;
			
				//select register
				IoWrite8(spio->SpioInfo->SioIndex,r);		
				//read actual data
				b=IoRead8(spio->SpioInfo->SioData);
				//if nothing has changed just skip it
				if(b==dev->LocalCfgDump[i]) continue; 	

				//enter config mode only if we really need it
				if(!cfgmod){
					BootScriptSioCfgMode(spio, TRUE, bss);
					cfgmod=TRUE;
				}
				//device has not been selected
				if(!devsel){
					BootScriptSioDevSelect(dev, bss);
					devsel=TRUE;
				}
				//Deactivate the device before changing registers 
				if(devact){	
					BOOT_SCRIPT_S3_IO_WRITE_MACRO(bss,EfiBootScriptWidthUint8,spio->SpioInfo->SioIndex, 1, &spio->SpioInfo->Activate);
					BOOT_SCRIPT_S3_IO_WRITE_MACRO(bss,EfiBootScriptWidthUint8,spio->SpioInfo->SioData, 1, &spio->SpioInfo->DeactVal);
					devact=FALSE;
				}
				//if this reg was different before the DXE initialization of SIO - record that into boot script
				BOOT_SCRIPT_S3_IO_WRITE_MACRO(bss,EfiBootScriptWidthUint8,spio->SpioInfo->SioIndex, 1, &r);
				BOOT_SCRIPT_S3_IO_WRITE_MACRO(bss,EfiBootScriptWidthUint8,spio->SpioInfo->SioData, 1, &b);

			} //reg dump compare loop

			//if we are here we have checked the device registers 
			if(!devact){ // we must Activate device now if we have deactivated it erlear
				BOOT_SCRIPT_S3_IO_WRITE_MACRO(bss,EfiBootScriptWidthUint8,spio->SpioInfo->SioIndex, 1, &spio->SpioInfo->Activate);
				BOOT_SCRIPT_S3_IO_WRITE_MACRO(bss,EfiBootScriptWidthUint8,spio->SpioInfo->SioData, 1, &spio->SpioInfo->ActivVal);
			}
            
            //Now if device has programmed some registers mapped through LD Decoded registers
            //we need so save them aswell. We will not do this automatically, but call Porting function to do so...
            if(dev->DeviceInfo->InitRoutine!=NULL)
                Status=dev->DeviceInfo->InitRoutine(&dev->AmiSio,dev->Owner->IsaBrgPciIo,isAfterBootScript);

		} //end device loop
		if(cfgmod)BootScriptSioCfgMode(spio, FALSE, bss);
		SioCfgMode(spio, FALSE);
	}//for s
		
	//
    //Kill the Event
	//
    pBS->CloseEvent(Event);

}


EFI_STATUS CreateSioDevStatusVar()  
{
  UINTN SioDevStatusVarSize = sizeof(SIO_DEV_STATUS);
	UINT32 SioDevStatusVarAttributes = 0;
	SIO_DEV_STATUS 	SioDevStatusVar;
	UINTN 			i,j;
	BOOLEAN 		Implemented; 
	UINT32			UID=0; 
	EFI_STATUS 		Status = EFI_SUCCESS;
	GSPIO			*spio;
//	SPIO_DEV		*dev;
//--------------------------------------
	Status = pRS->GetVariable(SIO_DEV_STATUS_VAR_NAME, &gSioDevStatusVarGuid, 
														&SioDevStatusVarAttributes, 
														&SioDevStatusVarSize, &SioDevStatusVar.DEV_STATUS);
	if (EFI_ERROR(Status)) {
		SioDevStatusVar.DEV_STATUS = 0;
		SioDevStatusVarAttributes = EFI_VARIABLE_BOOTSERVICE_ACCESS;
	}	

	for (i = 0; i < gSpioCount; i++) {
		spio=&gSpio[i];
		for(j=0;j<spio->DeviceCount;j++){
			Implemented = (spio->DeviceList[j]->DeviceInfo->Implemented && spio->DeviceList[j]->NvData.DevEnable);
			UID = spio->DeviceList[j]->DeviceInfo->UID;
			switch (spio->DeviceList[j]->DeviceInfo->Type){
				case dsFDC:		SioDevStatusVar.Fdd = Implemented;
	                SIO_TRACE((TRACE_SIO,"SIO[%d]Dev[%d] FDC is Implemented=%d\n",i,j,Implemented));
					break;
				case dsPS2CK:
				case dsPS2K:	SioDevStatusVar.Key60_64 = Implemented;
	                SIO_TRACE((TRACE_SIO,"SIO[%d]Dev[%d] PS2K is Implemented=%d\n",i,j,Implemented));
					break;
				case dsPS2CM:
				case dsPS2M: 	SioDevStatusVar.Ps2Mouse = Implemented;
	                SIO_TRACE((TRACE_SIO,"SIO[%d]Dev[%d] PS2M is Implemented=%d\n",i,j,Implemented));
					break;
				case dsUART:	
					if (UID == 0) SioDevStatusVar.SerialA = Implemented;
					else 
						if (UID == 1) SioDevStatusVar.SerialB = Implemented;
	                SIO_TRACE((TRACE_SIO,"SIO[%d]Dev[%d] UART(UID=%x) is Implemented=%d\n",i,j,UID,Implemented));
					break;
				case dsLPT:		SioDevStatusVar.Lpt = Implemented;
	                SIO_TRACE((TRACE_SIO,"SIO[%d]Dev[%d] LPT is Implemented=%d\n",i,j,Implemented));
					break;
				case dsGAME:	
					if (UID == 0)SioDevStatusVar.Game1 = Implemented;
					else 
						if (UID == 1)SioDevStatusVar.Game2 = Implemented;
	                SIO_TRACE((TRACE_SIO,"SIO[%d]Dev[%d] GAME(UID=%x) is Implemented=%d\n",i,j,UID,Implemented));
					break;
				case dsSB16:	SioDevStatusVar.Sb16 = Implemented;
	                SIO_TRACE((TRACE_SIO,"SIO[%d]Dev[%d] SB16 is Implemented=%d\n",i,j,Implemented));
					break;
				case dsFmSynth: SioDevStatusVar.FmSynth = Implemented;
	                SIO_TRACE((TRACE_SIO,"SIO[%d]Dev[%d] FmSynth is Implemented=%d\n",i,j,Implemented));
					break;
				case dsMPU401:	
				case dsCIR:	
				case dsGPIO:	
				case dsHwMon:	
				case dsPME:	
				case dsACPI:	
					break;
			}//switch
		} //for j
	}//for i
	Status = pRS->SetVariable(SIO_DEV_STATUS_VAR_NAME, &gSioDevStatusVarGuid, 
														SioDevStatusVarAttributes,
														SioDevStatusVarSize, &SioDevStatusVar);
	SIO_TRACE((TRACE_SIO,"GSIO: DevStatusVar=%X Status=%r\n",SioDevStatusVar.DEV_STATUS,Status));
	return Status; 
}


EFI_STATUS DisableDevInSioDevStatusVar(SPIO_DEV *Dev)
{
	UINTN SioDevStatusVarSize = sizeof(SIO_DEV_STATUS);
	UINT32 SioDevStatusVarAttributes = 0;
	SIO_DEV_STATUS SioDevStatusVar; 
	EFI_STATUS Status = EFI_SUCCESS; 
	SIO_DEV_TYPE Type = Dev->DeviceInfo->Type;
	SIO_DEV_TYPE UID = Dev->EisaId.UID;
//----------------------
	Status = pRS->GetVariable(SIO_DEV_STATUS_VAR_NAME, &gSioDevStatusVarGuid, 
														&SioDevStatusVarAttributes, 
														&SioDevStatusVarSize, &SioDevStatusVar.DEV_STATUS);
	if (!EFI_ERROR(Status)) {	
		switch (Type) {
			case dsFDC:	SioDevStatusVar.Fdd = 0;
									break;
			case dsPS2CK:
			case dsPS2K:	SioDevStatusVar.Key60_64 = 0;
										break;
			case dsPS2CM:
			case dsPS2M: 	SioDevStatusVar.Ps2Mouse = 0;
										break;
			case dsUART:	if (UID == 0) { 	
											SioDevStatusVar.SerialA = 0;
										} else if (UID == 1) {
											SioDevStatusVar.SerialB = 0;
										}
										break;
			case dsLPT:		SioDevStatusVar.Lpt = 0;
										break;
			case dsGAME:	if (UID == 0) { 	
											SioDevStatusVar.Game1 = 0;
										} else if (UID == 1) {
											SioDevStatusVar.Game2 = 0;
										}			
										break;
			case dsSB16:	SioDevStatusVar.Sb16 = 0;
										break;
			case dsFmSynth: SioDevStatusVar.FmSynth = 0;
											break;
			case dsMPU401:	case dsCIR:	case dsGPIO:	
			case dsHwMon:	case dsPME:	case dsACPI:	break;
	
		} //switch

		Status = pRS->SetVariable(SIO_DEV_STATUS_VAR_NAME, &gSioDevStatusVarGuid, 
															SioDevStatusVarAttributes,
															SioDevStatusVarSize, &SioDevStatusVar);
	} 
	SIO_TRACE((TRACE_SIO,"GSIO: DevStatusVar=%X\n",SioDevStatusVar.DEV_STATUS));
	return Status; 
}

#endif //#if SIO_SUPPORT
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
                                                                                                                    
