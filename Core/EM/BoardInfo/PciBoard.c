//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
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
// $Header: /Alaska/BIN/Core/Modules/BoardInfo/PciBoard.c 4     10/03/11 4:40p Yakovlevs $
//
// $Revision: 4 $
//
// $Date: 10/03/11 4:40p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Modules/BoardInfo/PciBoard.c $
// 
// 4     10/03/11 4:40p Yakovlevs
// 
// 3     9/30/11 5:42p Yakovlevs
// [TAG]  		EIP66222
// [Category]  	New Feature
// [Description]  	Modify PCI bus driver to get board info from separate
// FFS section
// [Files]  		AmiBoaardInfo.mak; 
// AmiBoaardInfo.sdl;
// PciBoard.c
// AmiBoaardInfo.h
// 
// 2     6/28/11 5:51p Yakovlevs
// [TAG]  		EIP 60123 
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	Resource padding is not functional for PCIe hot-plug.
// [RootCause]  	In HP Mode #ifndef statement was not working 
// [Solution]  	Cahnged to reference AMI_HOTPLUG_INIT_SUPPORT token
// [Files]  		AmiBoardInfo.c PciBoard.c
// 
// 1     3/01/10 5:04p Yakovlevs
// "C" syle file replaces PciBoard.asm
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
//#include <Efi.h>
#pragma pack(push, 1)
#include "oempir.h"
#include "BusNumXlat.h"
#include "mppciirq.h"
#pragma pack(pop)

/*
//APIC Hhot Plug Slots
#if AMI_HOTPLUG_INIT_SUPPORT
//extern   UINT8* APIC_HotPlug_Slots_start;
UINTN    HP_SlotA_Start   = (UINTN)&APIC_HotPlug_Slots_start;
UINTN    HP_SlotA_End     = (UINTN)&APIC_HotPlug_Slots_start + sizeof(APIC_HotPlug_Slots_start);
#else 
UINTN    HP_SlotA_Start   = (UINTN)&MP_IRI_Table+sizeof(MP_IRI_Table);
UINTN    HP_SlotA_End     = (UINTN)&MP_IRI_Table+sizeof(MP_IRI_Table);
#endif

#include "oempir.c"
UINTN IRQ_Table = (UINTN)arr_rth_pci_dedicated_irqs_equ;
UINTN IRQ_Table_end=(UINTN)arr_rth_pci_dedicated_irqs_equ+sizeof(arr_rth_pci_dedicated_irqs_equ);

//PIC Hhot Plug Slots
#if AMI_HOTPLUG_INIT_SUPPORT
//extern  UINT8* HotPlugIrqRoutingStart;
UINTN    HP_SlotP_Start   = (UINTN)&HotPlugIrqRoutingStart;
UINTN    HP_SlotP_End     = (UINTN)&HotPlugIrqRoutingStart + sizeof(HotPlugIrqRoutingStart);
#else 
UINTN    HP_SlotP_Start   = (UINTN)arr_rth_pci_dedicated_irqs_equ+sizeof(arr_rth_pci_dedicated_irqs_equ);
UINTN    HP_SlotP_End     = (UINTN)arr_rth_pci_dedicated_irqs_equ+sizeof(arr_rth_pci_dedicated_irqs_equ);
#endif
*/


//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************