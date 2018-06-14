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
// $Header: /Alaska/BIN/Core/Modules/PciBus/PciPort.h 5     4/05/11 11:28a Yakovlevs $
//
// $Revision: 5 $
//
// $Date: 4/05/11 11:28a $
//**********************************************************************
// Revision History
// ----------------
//$Log: /Alaska/BIN/Core/Modules/PciBus/PciPort.h $
// 
// 5     4/05/11 11:28a Yakovlevs
// [TAG]  		EIP 38174; EIP 53475;
// [Description]  	38174 Generic support to handle PCI OUT OF RESOURDCES
// added. 
// 53475 PCI Express 3.0 support added.
// 
// [Files]  		PciBus.c; PciBus.mak; PciHostBridge.c;  PciBus.h;
// PciHostBridge.c; PciPort.c;
// 
// 4     1/28/11 3:02p Yakovlevs
// [TAG]  		EIP43879
// [Category]  	New Feature
// [Description]  	Added PciPortOemGetOptRom() OEM Hook to override
// content of the PCI Device Option ROM.
// [Files]  		PciBus.c; PciPort.c; PciPort.h; PciBus.mak; PciBus.sdl
// 
// 3     8/16/10 1:12p Yakovlevs
// ASPM Custom Programming.
// 
// 2     9/22/09 6:02p Yakovlevs
// 1.	Added infrastructure to ELINKs as porting Functions delivered from
// Platform and Chipset files. Now you can port PCI Bus driver without
// modifying Core files
// 
// 1     4/28/09 3:47p Yakovlevs

#ifndef PCI_PORT_H_
#define PCI_PORT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <Efi.h>


//----------------------------------------------------------------------------------
//PCI Bus Porting Constants definitions
const UINT16 NbDmiL0ExitLatency;
const UINT16 NbDmiL1ExitLatency;
const UINT16 SbDmiL0ExitLatency;
const UINT16 SbDmiL1ExitLatency;
const UINT16 NbDmiAspmSupport;
const UINT16 SbDmiAspmSupport;
const UINT16 SbInternalDelay;
//PCI Bus Configuration Constants definitions
const BOOLEAN S3VideoRepost;
const BOOLEAN FixedBusAssign;
const BOOLEAN ScanFullBusRange;
const BOOLEAN PciExpressSupport;
const BOOLEAN HotPlugSupport;
const BOOLEAN PciXSupport; 
const BOOLEAN SriovSupport;
const BOOLEAN Use4KBar; 

//Define OEM_PCI_DEVICE_PROGRAM_CALLBACK
typedef EFI_STATUS (OEM_PCI_PROGRAM_DEVICE_FUNCTION)(VOID *PciIoProtocol);
typedef EFI_STATUS (OEM_PCI_DEVICE_ATTRIBUTE_FUNCTION)(VOID *PciIoProtocol, UINT64 *Attr, UINT64 Capab, BOOLEAN Set);
typedef EFI_STATUS (OEM_PCI_DEVICE_SET_ASPM_FUNCTION)(VOID *PciIoProtocol, VOID *AspmMode);
typedef EFI_STATUS (OEM_PCI_DEVICE_SET_LNK_SPEED_FUNCTION)(VOID *PciIoProtocol, UINT8 *LnkSpeed, UINT8 SuppSpeeds);
typedef EFI_STATUS (OEM_PCI_DEVICE_GET_OPT_ROM_FUNCTION)(VOID *PciIoProtocol, VOID **OptRom, UINT64 *OptRomSize);
typedef EFI_STATUS (OEM_PCI_DEVICE_OUT_OF_RESOURCES_FUNCTION)(VOID *PciIoProtocol, UINTN Count, UINTN ResType);
typedef EFI_STATUS (OEM_PCI_PADDING_FUNCTION)(VOID *HpcData, VOID *HpcLocationData, UINT64 PciAddress);

//Data structure of CallBack delivered trough eLink
typedef struct{
	UINT16  VendorId;
    UINT16  DeviceId;
	VOID    *Callback;
} OEM_PCI_DEVICE_PROGRAM_CALLBACK;



//PCI Bus Porting Function Prototypes
EFI_STATUS PciPortSkipThisDevice(VOID *Device);

EFI_STATUS PciPortOemProgDevice(VOID *Device);

EFI_STATUS PciPortOemAttributes(VOID *Device, UINT64 *Attr, UINT64 Capab, BOOLEAN Set);

EFI_STATUS PciPortOemSetAspm(PCI_DEV_INFO *Device, VOID *AspmMode);

EFI_STATUS PciPortOemSetLnkSpeed(PCI_DEV_INFO *Device, UINT8 *LnkSpeed, UINT8 SuppSpeeds);

EFI_STATUS PciPortSetOemPadding(VOID *HpcData, VOID *HpcLocationData, UINT64 PciAddress);

EFI_STATUS PciPortOemGetOptRom(PCI_DEV_INFO *Device, VOID **OptRom, UINT64 *OptRomSize);

EFI_STATUS PciPortOutOfResourcesRemoveDevice(PCI_DEV_INFO *Device, UINTN Count, UINTN LowResType);

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif	//PCI_BOARD_H_


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

