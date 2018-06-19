//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**           5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093      **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//****************************************************************************
// $Header: /Alaska/SOURCE/Modules/CSM/Generic/Core/PciInterrupts.c 55    4/09/13 9:25a Olegi $
//
// $Revision: 55 $
//
// $Date: 4/09/13 9:25a $
//
//****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/CSM/Generic/Core/PciInterrupts.c $
// 
// 55    4/09/13 9:25a Olegi
// [TAG]  		EIP118727
// [Category]  	New Feature
// [Description]  	Onboard PCI Option ROM loading is moved outside CSM
// [Files]  		CSM.mak
// CSM.dxs
// CSM.c
// PciInterrupts.c
// CsmBsp.c
// CsmLib.c
// 
// 54    11/16/12 10:15a Olegi
// Typo in previous checkin.
// 
// 53    11/13/12 12:15p Olegi
// [TAG]  		EIP99683
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	System Hang at status code AE with Optimization disabled
// [RootCause]  	Intx2Pirq function (PciInterrupts.c) returns various
// errors. However, only EFI_NOT_FOUND is taken into consideration by the
// caller.
// [Solution]  	Analyze all errors returned by Intx2Pirq function.
// [Files]  		PciInterrupts.c
// 
// 52    4/09/12 5:32p Olegi
// [TAG]  		EIP86722
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	Function "GetXlatPciBusNumber" does not work
// [RootCause]  	C-style output does not match with the ASM style output
// [Solution]  	Corrected the XLAT table parse function depending on the
// version of PCI driver.
// [Files]  		PciInterrupts.c
// 
// 51    12/13/11 11:31a Olegi
// [TAG]  		EIP77755
// [Category]  	Improvement
// [Description]  	Modified CreateAddonBusEntry function to return if
// requested bus # is already present in AddonPciBusTable.
// [Files]  		PciInterrupts.c
// 
// 50    12/14/10 12:02p Olegi
// [TAG]  		EIP44553
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	PCI recovery card is disabled during its Option ROM
// execution
// [RootCause]  	Some mass storage controllers are not enabled before
// option ROM execution.
// [Solution]  	Modified CsmBlkIo driver to enable device before calling
// InstallPciRom function. Device enable code is removed from
// PciIterrupts.c
// [Files]  		PciInterrupts.c, CsmBlkIo.c
// 
// 49    11/09/10 9:39a Olegi
// PCI_TRACE macro replaced with TRACE.
// 
// 48    7/08/10 11:35a Olegi
// Modified IRQ distribution logic to achieve maximum interrupt
// dispersion. EIP39733
// 
// 47    6/18/10 10:30a Olegi
// EIP39733: Change in RoutePciIrq function.
// 
// 46    3/02/10 5:17p Olegi
// Making use of AmiExtPciBusProtocol when PCI Bus driver version is 240
// or newer.
// 
// 45    1/28/10 9:07a Olegi
// ProgramPciIrq: added code that sends a notification about PCI IRQ
// programming.
// 
// 44    1/12/10 11:46a Olegi
// Copyright message updated.
// 
// 43    12/08/09 5:06p Olegi
// 
// 42    9/23/09 9:25a Olegi
// GetP2PSecondaryBusNum:: Fixed the problem of reading PCI device on bus
// 80h or more.
// 
// 41    8/07/09 2:43p Rameshr
// SD boot support Added.
// 
// 40    8/05/09 5:25p Olegi
// Variable types redefinition that fixes the 32-bit mode compilation
// warning.
// 
// 39    6/16/09 1:52p Olegi
// Correction in UpdatePrt() function for multiple root bridge
// configuration.
// 
// 38    3/10/09 1:49p Olegi
// Added trace message in RoutePciIrq.
// 
// 37    3/09/09 11:47a Olegi
// Bugfix in ProgramPciIrq OEM interrupt masking: EIP#18668
// 
// 36    12/11/08 10:16a Olegi
// Bugfix in ProgramPciIrq; EIP#16563
// 
// 35    11/13/08 1:01p Olegi
// Added GetPlatformInfo call before programming PCI IRQ.
// 
// 34    11/03/08 2:19p Olegi
// Bugfix in UpdatePrt(), EIP #15167
// 
// 33    10/01/08 11:50a Olegi
// Fix for a device behind two or more P2P bridges (EIP#16563).
// 
// 32    8/08/08 9:26a Olegi
// Modified UpdatePrt function, invalid entries in BusNumXlat table as
// well as in $PIR table are suppressed.
// 
// 31    6/20/08 10:20a Olegi
// Fix for the PCI IRQ routing table parser when PCI bus is FF.
// 
// 30    11/02/07 10:39a Olegi
// Added BspUpdatePrt function.
// 
// 29    9/19/07 10:14a Olegi
// Bugfix in CreateAddonBusEntry.
// 
// 28    6/18/07 5:47p Olegi
// 
// 27    6/04/07 10:47a Olegi
// 
// 26    4/27/07 5:47p Olegi
// 
// 25    4/27/07 5:13p Olegi
// CSM.CHM file preparation.
//
// 24    4/26/07 4:24p Olegi
//
// 23    4/26/07 2:44p Olegi
// Correction in RoutePciIrq routine, that will not do the routing if the
// given register is already programmed.
//
// 22    4/13/07 9:46a Olegi
//
//**********************************************************************

//****************************************************************************
//<AMI_FHDR_START>
//
//  Name:           PciInterrupts.c
//
//  Description:    PCI Interrupt routing functions
//
//<AMI_FHDR_END>
//****************************************************************************


#include <AmiDxeLib.h>
#include <Pci.h>
#define PCI_BASE_CLASS_INTELLIGENT  0x0e
#define PCI_SUB_CLASS_INTELLIGENT   0x00

#include <AcpiRes.h>
#include <Token.h>
#include <Protocol/PciRootBridgeIo.h>
#include <Protocol/DevicePath.h>
#include <Protocol/LegacyBios.h>
#include <Protocol/LegacyBiosPlatform.h>
#include <Protocol/PciIo.h>
#include <Protocol/Legacy8259.h>
#include "csm.h"
#include "AmiCspLib.h"
#include <Protocol/AmiBoardInfo.h>

EFI_GUID    gEfiPciRootBridgeIoProtocol = EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_GUID;

VOID                            *gPciIoNotifyReg;
extern EFI_BOOT_SERVICES        *pBS;
BIOS_INFO                       *CoreBiosInfo;
EFI_LEGACY_PIRQ_TABLE_HEADER    *MsPrt; // To be obtained after
EFI_LEGACY_IRQ_ROUTING_ENTRY    *Prt;   // reading GUIDed section.
UINTN   gUsedPciEntries;



extern  BOOLEAN IsValidPrt;
extern  PLATFORM_BIOS_INFO  *BspBiosInfo;

EFI_GUID gBusNumXlatProtocol = AMICSM_PCIBUSNUM_XLAT_PROTOCOL_GUID;
AMICSM_PCIBUSNUM_XLAT_PROTOCOL  BusNumXlatProtocol;

extern AMI_BOARD_INFO_PROTOCOL *gAmiBoardInfo;

UINTN   CopyLegacyTable(VOID*, UINT16, UINT16, UINT16);

UINT8   *BusNumXlat;
UINT8   *BusNumXlatEnd;

EFI_HANDLE gHandle = NULL;
UINTN           PciRBHandlesNo=0;
EFI_HANDLE      *PciRBHandles=NULL;
UINT16          XlatTblEntriesRemaining=0;
//
// The following two external variables specifiy the PCI device/function number of the root
// bridge(s). Number of entries in this table defined by RbCount.
// This data is a missing link between RootBridgeIo and PciIo, which allows to update
// BusNumXlat table with actual bus numbers.
// Each entry in the RbMap is a pair of RootBridge UID (UINT32), provided in RootBridge
// device path, and PCI Dev/Func number (UINT8) that can be used to access Root Bridge on
// PCI bus.
//
extern  ROOT_BRIDGE_MAPPING_ENTRY       RbMap[];
extern  UINTN                           RbCount;

UINT8   SBGen_GetPIRQIndex (UINT8);

//UINT8   irq_priority_map[] = {11, 10, 9, 15, 5, 3, 7, 4, 14};
UINT8   irq_priority_map[] = {15, 7, 14, 6, 11, 10, 9, 5, 3, 4};
UINT8   irq_allocated_count[sizeof(irq_priority_map)] = {0};
UINT16  IsaIrqMask;

EFI_ADDON_PCIBUS_TABLE AddonPciBusTable[MAX_ADDITIONAL_P2P_BRIDGES];

UINT8   gAddonPciBusIndx;

EFI_LEGACY_8259_PROTOCOL *i8259;

PROGRAMMED_PCIIRQ_CTX   gIrqPgmCtx = {0};
EFI_GUID gPciIrqProgramGuid = EFI_PCIIRQ_PGM_PROTOCOL_GUID;


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:    RoutePciIrq
//
// Description: This routine selects the IRQ from the list of allowed PCI
//              interrupts, picks the best interrupt number according to
//              interrupt priority table and programs the PCI interrupt
//              router.
// Input:
//   Int - zero based index in the list of router registers for INTA, INTB,...
//   Irq - new interrupt number
//   IrqMask - IRQ bit mask, bits are set for the interrupts that are not allowed
//
// Output:      EFI_SUCCESS if interrupt is routed
//              EFI_ABORTED if routing register is already programmed
//
// Notes:       This routine can not be called externally. It is to be
//              called after TranslatePirq returns the Rirq register is
//              not programmed.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
RoutePciIrq(
    IN  UINT8   Int,
    OUT UINT8   *Irq,
    IN  UINT16  IrqMask
)
{
    UINT16  Mask = ~IrqMask;    // PIC-style mask (1 is for interrupts that are not allowed)
    EFI_LEGACY_INTERRUPT_PROTOCOL   *iInterrupt;
    UINT8   NewIrq;
    EFI_STATUS  Status;
    UINT8 i;
    UINT8   IrqIndex;
    UINT8   IrqFound = FALSE;

    Status = pBS->LocateProtocol (&gEfiLegacyInterruptProtocolGuid, NULL, &iInterrupt);
    if (EFI_ERROR(Status)) return Status;

    //
    // See if routing register is already programmed, return EFI_ABORTED if so.
    //
    Status = iInterrupt->ReadPirq(iInterrupt, Int, &NewIrq);
    ASSERT_EFI_ERROR(Status);
    if (EFI_ERROR(Status)) return Status;

    for (i=0; irq_priority_map[i]; i++) {
        if (NewIrq==irq_priority_map[i]) {
TRACE(((UINTN)-1, "The requested PIRQ[%d] is already programmed to IRQ%x. PCI Routing ABORTED.\n", Int, NewIrq));
            return EFI_ABORTED;
        }
    }

TRACE(((UINTN)-1,"..........IRQ MASK %x....", Mask));
    //
    // Remove ISA interrupts from Mask
    //
    Mask |= IsaIrqMask;

TRACE(((UINTN)-1,"%x....\n", Mask));
    //
    // Find the next available interrupt; irq_priority_map is zero-terminated array
    // used as priority list. Lower index in irq_priority_map indicates higher priority
    // interrupt.
    // Initially irq_priority_index is the index of zero in irq_priority_map; it will
    // be advanced to the beginning in the following for loop.
    //
    for (IrqIndex = 0; IrqIndex < sizeof(irq_priority_map); IrqIndex++) {
TRACE(((UINTN)-1,"IrqIndex %d....Allocated %d....\n", IrqIndex, irq_allocated_count[IrqIndex]));
        if (!((1 << irq_priority_map[IrqIndex]) & Mask)) {
            IrqFound = TRUE;    // Assume that IRQ was found
            for (i = 0; i < sizeof(irq_allocated_count); i++) {
                // Check if the least allocated IRQ
                if (!((1 << irq_priority_map[i]) & Mask)) {
                    if (irq_allocated_count[IrqIndex] > irq_allocated_count[i]) {
                        IrqFound = FALSE;
                        break;
                    }
                }
            }
        }
        if (IrqFound) break;
    }
    if (!IrqFound) return EFI_NOT_FOUND;

    irq_allocated_count[IrqIndex] += 1;
    NewIrq = irq_priority_map[IrqIndex];

    // Adjust irq_priority_index

    Status = iInterrupt->WritePirq(iInterrupt, Int, NewIrq);
    if (EFI_ERROR(Status)) return Status;

    *Irq = NewIrq;
    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:        Intx2Pirq
//
// Description: This function is similar to TranslatePirq with the additional
//              output of IrqMask. See TranslatePirq description.
// Input:
//  This        Indicates the EFI_LEGACY_BIOS_PLATFORM_PROTOCOL instance.
//  PCI bus, device and function number for this device.
//  Pirq        The PIRQ. PIRQ A = 0, PIRQ B = 1, and so on.
//  PirqIrq     IRQ assigned to the indicated PIRQ.
//  IrqMask     Mask of IRQs that could be assigned to this register
//
// Output:
//  EFI_SUCCESS     The PIRQ was translated.
//  EFI_NOT_FOUND   The device was not in the table.
//  EFI_NOT_READY   The interrupt translation table is not ready.
//  EFI_INVALID_PARAMETER   Wrong input
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
Intx2Pirq (
  IN  EFI_LEGACY_BIOS_PLATFORM_PROTOCOL  *This,
  IN  UINTN                              PciBus,
  IN  UINTN                              PciDevice,
  IN  UINTN                              PciFunction,
  IN  OUT UINT8                          *Pirq,
  OUT UINT8                              *PciIrq,
  OUT UINT16                             *IrqMask OPTIONAL
  )
{
    UINT8   Irq;
    UINT8   counter;
    EFI_LEGACY_IRQ_ROUTING_ENTRY    *p;
    EFI_LEGACY_INTERRUPT_PROTOCOL   *iInterrupt;
    EFI_STATUS  Status;

    UINT8   PciDev;
    UINT8   rr = 0;     // Router register
    UINT8   rrIndx;     // Router register index
    UINT8   pirq = *Pirq;
    UINT8   i;

    if (!IsValidPrt) return EFI_NOT_READY;

    if (pirq > 3) {
		TRACE (((UINTN)TRACE_ALWAYS, "Invalid PIRQ value (%d, %d, %d) %d\n", PciBus, PciDevice, PciFunction, pirq));
        return EFI_INVALID_PARAMETER;
    }

    PciDev = (UINT8)(PciDevice << 3);

    for (p = Prt, counter = 0; counter < gUsedPciEntries; counter++, p++) {
        if ((PciBus == p->Bus) && (PciDev == p->Device)) {
            rr = p->PirqEntry[pirq].Pirq;
            if (IrqMask != NULL) *IrqMask = p->PirqEntry[pirq].IrqMask;
            break;  // rrIndx is found
        }
    }

    if (counter == gUsedPciEntries) {
        if (gAddonPciBusIndx == 0) return EFI_NOT_FOUND; // No additional P2P bridges

        //
        // Not found in &PIR - see if device is generated by the P2P which is not
        // listed in BusNumXlat, e.g. it is behind P2P bridge located on off-board card.
        //
        for (counter = 0; counter < gAddonPciBusIndx; counter++) {
            if (AddonPciBusTable[counter].Bus == PciBus) {
                i = (UINT8)((PciDevice + pirq) % 4);  // INTA/B/C/D for Dev0, INTB/C/D/A for dev1, etc.
                rr = AddonPciBusTable[counter].PirqEntry[i].Pirq;
                if (IrqMask != NULL) *IrqMask = AddonPciBusTable[counter].PirqEntry[i].IrqMask;
                break;
            }
        }
        if (counter == gAddonPciBusIndx) return EFI_NOT_FOUND;   // Device not found
    }

    //
    // Find the index of given register within RRegs
    //
    rrIndx = SBGen_GetPIRQIndex (rr);
    if (rrIndx == 0xFF) return EFI_UNSUPPORTED;

    //
    // Get the programmed interrupt number off the LegacyInterrupt for rrIndx
    //
    Status = pBS->LocateProtocol (&gEfiLegacyInterruptProtocolGuid, NULL, &iInterrupt);
    if (EFI_ERROR(Status)) return Status;

    Status = iInterrupt->ReadPirq(iInterrupt, rrIndx, &Irq);
    if (EFI_ERROR(Status)) return Status;

    *Pirq = rrIndx;
    *PciIrq = Irq;

    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:        CreateAddonBusEntry
//
// Description: This function inserts a new entry into AddonPciBusTable.
//
// Input:
//  Bus      - new bus number
//  PirqData - pointer to the new PIRQ data array
//
// Output:
//  EFI_SUCCESS     Entry has been created successfully.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
CreateAddonBusEntry(
    UINT8   Bus,
    VOID    *PirqData
)
{
    UINT8   i;

    // Check if the requested entry already exists in AddonPciBusTable. This will be
    // the case when PCI bus driver has been reconnected.
    //
    for (i = 0; i < gAddonPciBusIndx; i++) {
        if (AddonPciBusTable[i].Bus == Bus) {
            return EFI_SUCCESS;
        }
    }

    //
    // Insert new entry into AddonPciBusTable
    //
    AddonPciBusTable[gAddonPciBusIndx].Bus = Bus;
    pBS->CopyMem(
            AddonPciBusTable[gAddonPciBusIndx].PirqEntry,
            PirqData,
            sizeof(EFI_LEGACY_PIRQ_ENTRY)*4
    );
    TRACE((-1, "AddonPciBusTable entry [%d] created: Bus %x, PIRQs: %x %x %x %x\n",
        gAddonPciBusIndx,
        AddonPciBusTable[gAddonPciBusIndx].Bus,
        AddonPciBusTable[gAddonPciBusIndx].PirqEntry[0].Pirq,
        AddonPciBusTable[gAddonPciBusIndx].PirqEntry[1].Pirq,
        AddonPciBusTable[gAddonPciBusIndx].PirqEntry[2].Pirq,
        AddonPciBusTable[gAddonPciBusIndx].PirqEntry[3].Pirq));

    gAddonPciBusIndx++;
    ASSERT(gAddonPciBusIndx<MAX_ADDITIONAL_P2P_BRIDGES);
    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:        CheckP2PBridge
//
// Description: This function verifies whether device is P2P bridge which is
//              not listed in BusNumXlat table, e.g. bridge is on PCI Add-on card.
//              For this bridge we create a new entry in AddonPciBusTable which
//              will be used for PCI IRQ routing for the devices that are located
//              behind this bridge.
// Input:
//  PciIo       pointer to EFI_PCI_IO_PROTOCOL protocol associated with this device
//  Bus, Dev    PCI bus location for this device
//
// Output:
//  EFI_SUCCESS     Device is P2P bridge; if bus generated by this bridge is not
//                  described in $PIR table, then another entry in AddonPciBusTable
//                  is created.
//  EFI_NOT_FOUND   Device is not P2P bridge.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
CheckP2PBridge(
    EFI_PCI_IO_PROTOCOL *PciIo,
    UINT8               Bus,
    UINT8               Dev
)
{
    EFI_STATUS  Status;
    UINT16      PciClassSubclass;
    UINT8       SecBusNum;
    EFI_LEGACY_IRQ_ROUTING_ENTRY    *re;
    UINT8       counter;

    //
    // Check if this is a P2P bridge
    //
    Status = PciIo->Pci.Read(PciIo, EfiPciIoWidthUint16, 0xA, 1, &PciClassSubclass);
    ASSERT_EFI_ERROR(Status);
    //
    // Base Class=6 Ofs B (Bridge), SubClass=4 Ofs A (P2P Bridge)
    //
    if (PciClassSubclass != 0x0604) return EFI_NOT_FOUND;
    //
    // It is P2P bridge - read its secondary bus number and try to find a match in
    // BusNumXlat table
    //
    TRACE((-1,"P2P bridge.\n"));
    Status = PciIo->Pci.Read(
                PciIo,
                EfiPciIoWidthUint8,
                PCI_BRIDGE_SECONDARY_BUS_REGISTER_OFFSET,
                1,
                &SecBusNum);
    ASSERT_EFI_ERROR(Status);

    //
    // Locate the P2P bridge as PCI device in $PIR and get EFI_LEGACY_IRQ_ROUTING_ENTRY;
    // if found - insert new entry into AddonPciBusTable and return EFI_SUCCESS,
    // otherwise return EFI_NOT_FOUND.
    //
    for (re = Prt, counter = 0; counter < gUsedPciEntries; counter++, re++) {
        if ((re->Bus == Bus) && (re->Device == (Dev << 3))) {
            return CreateAddonBusEntry(SecBusNum, re->PirqEntry);
        }
    }
    //
    // Not found in $PIR table - try AddonPciBusTable
    //

    if (gAddonPciBusIndx == 0) return EFI_NOT_FOUND; // No additional P2P bridges

    for (counter = 0; counter < gAddonPciBusIndx; counter++) {
        if (AddonPciBusTable[counter].Bus == Bus) {
            //
            // Connected to an add-on bridge, do the INT pin swizzling
            //
            EFI_LEGACY_PIRQ_ENTRY PirqData[4];
            UINT8 RoundRobinXlatTable[4][4] = {
                0, 1, 2, 3,
                1, 2, 3, 0,
                2, 3, 0, 1,
                3, 0, 1, 2
            };
            UINT8 i = (UINT8)(Dev % 4);
            UINT8 counter1;

            for (counter1 = 0; counter1 < 4; counter1++) {
                pBS->CopyMem(
                    &PirqData[counter1],
                    &AddonPciBusTable[counter].PirqEntry[RoundRobinXlatTable[i][counter1]],
                    sizeof(EFI_LEGACY_PIRQ_ENTRY)
                );
            }

            return CreateAddonBusEntry(SecBusNum, PirqData);
        }
    }
    return EFI_NOT_FOUND;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:  GetIsaIrqs
//
// Description: Returns the ISA interrupt mask
//
// Input:       None
//
// Output:      ISA interrupt mask
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
GetIsaIrqs(
    OUT UINT16  *IrqMask
)
{
    EFI_STATUS Status;

    Status=AmiIsaIrqMask(IrqMask, TRUE);
    if(EFI_ERROR(Status)){
        *IrqMask = ISA_IRQ_MASK;    // allow IRQ 0..8, 12..15 for ISA
        Status=AmiIsaIrqMask(IrqMask, FALSE);
		TRACE(((UINTN)-1, "PciInterrupts: Set ISA_IRQ_MASK, Status=%r\n", Status));
    }
    return Status;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:  ProgramPciIrq
//
// Description: This function assigns IRQ to a PCI device. It programs PCI
//              IRQ register if:
//                  - device requires IRQ to be assigned (reg 3D is 1..3)
//                  - PCI bus information is updated in $PIR table (step 1
//                    has been completed)
//                  - device is present in IRQ routing table
//              When all these conditions are met, then IRQ is assigned to this
//              device according to the PCI IRQ priorities; then IRQ is programmed
//              in PCI register 3C
//
// Input:  PCI Bus, Device and Function number of the PCI device
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID ProgramPciIrq(
    EFI_PCI_IO_PROTOCOL *PciIo,
    VOID *Context)
{
    UINT16      IrqMask;
    UINT16      Mask, EdgeLevel;
    UINT8       Int, Irq;
    EFI_STATUS  Status;
    EFI_LEGACY_BIOS_PLATFORM_PROTOCOL *iBiosPlatform;
    UINTN Seg, Bus, Dev, Func;
    UINTN       OemIrqMask;

    Status = PciIo->GetLocation(PciIo, &Seg, &Bus, &Dev, &Func);
    ASSERT_EFI_ERROR(Status);
    if (EFI_ERROR(Status)) return;

    TRACE((-1,"PCI device: %x %x %x ... ", Bus, Dev, Func));

    //
    // Find out whether device is P2P bridge that is not listed in BusXlatNum table;
    // if found - add entry into P2P bridge table and exit. Function returns:
    // EFI_NOT_FOUND - not P2P bridge; EFI_SUCCESS - P2P bridge found and bridge table
    // is updated.
    //
    Status = CheckP2PBridge(PciIo, (UINT8)Bus, (UINT8)Dev);

    //
    // Check if device requires IRQ
    //
    Status = PciIo->Pci.Read(PciIo, EfiPciIoWidthUint8, 0x3D, 1, &Int);
    ASSERT_EFI_ERROR(Status);

    if (EFI_ERROR(Status)) return;

    if (!Int) {
        TRACE((-1,"does not require IRQ.\n"));
        return; // Device does not support IRQ
    }

    Int--;              // Zero based INTx
    iBiosPlatform = (EFI_LEGACY_BIOS_PLATFORM_PROTOCOL *)Context;
    Status = Intx2Pirq(
                    iBiosPlatform,
                    Bus, Dev, Func,
                    &Int,
                    &Irq,
                    &IrqMask);

    TRACE((-1,"Intx2Pirq returns %r\n", Status));

    if (Status == EFI_NOT_FOUND) {
        // Device is not in the table
        TRACE((-1,"Device is not found in the PCI IRQ routing table.\n"));
    }

    if (EFI_ERROR(Status)) {
        return;
    }

    //
    // Intx2Pirq returns:
    //  Int - routing register index;
    //  Irq - interrupt currently programmed in that index.
    //  IrqMask - bit mask of the interrupts that can possibly be
    //  assigned to this device.
    //

    // Call OEM function that can modify the list of interrupts that can be
    // assigned. Note that the list can only be shrunk, not extended.

    Status = CoreBiosInfo->iBiosPlatform->GetPlatformInfo(
                    CoreBiosInfo->iBiosPlatform,
                    EfiGetPlatformPciIrqMask,
                    &PciIo,
                    NULL, NULL,
                    &OemIrqMask,
                    IrqMask,
                    0);
    if (!EFI_ERROR(Status)) {
        IrqMask &= (UINT16)OemIrqMask;
    }

    Status = RoutePciIrq(Int, &Irq, IrqMask);

    TRACE((-1,"RoutePciIrq status: %r,  Intx2Pirq: Int %x IRQ %x mask %x\n", Status, Int, Irq, IrqMask));

    Status = PciIo->Pci.Write(PciIo, EfiPciIoWidthUint8, 0x3C, 1, &Irq);
    ASSERT_EFI_ERROR(Status);

    if (EFI_ERROR(Status)) return;

    //
    // Set corresponding mask and edge/level mode in 8259 for real mode operation
    //
    i8259->GetMask(i8259, &Mask, &EdgeLevel, NULL, NULL);
    Mask &= (UINT16)~(1 << Irq);
    EdgeLevel |= (UINT16)(1 << Irq);
    i8259->SetMask(i8259, &Mask, &EdgeLevel, NULL, NULL);

    // Send out a word about programmed PCI interrupt
    gIrqPgmCtx.PciIo = (VOID*)PciIo;
    gIrqPgmCtx.Irq = Irq;
    Status = pBS->ReinstallProtocolInterface(
        gHandle,
        &gPciIrqProgramGuid,
        &gIrqPgmCtx,
        &gIrqPgmCtx
    );
    ASSERT_EFI_ERROR(Status);
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:        GetXlatPciBusNumber
//
// Description: This function returns the PCI bus number translated according
//              to Xlat table defined in BusNumXlat.inc. This translation file
//              is generated by AMISDL using "BUSNUM_XLAT" output type.
//
// Input:       Build time PCI bus number - 1st coulmn of the xlat table
//
// Output:      EFI_SUCCESS, real PCI bus number - 2nd column of the xlat table
//              EFI_NOT_FOUND, the requested bus is not found in the xlat table
//              EFI_INVALID_PARAMETER, if NULL pointer is supplied on input.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
GetXlatPciBusNumber (
  IN OUT UINT8  *busNumber
)
{
    UINT8 *p;

    if (busNumber == NULL) return EFI_UNSUPPORTED;

    for(p = BusNumXlat; p < BusNumXlatEnd; p++) {
        if (*p == *busNumber) {
            if (*(p+1)==0xFE) return EFI_NOT_FOUND;
            *busNumber = *(p+1);
            return EFI_SUCCESS;
        }
        while (*p != 0xFF) {p++;}   // p points to -1 at the end of the line
        // C style BusXlatNum output adds five more Bytes after FF, so skip them
        p+=5;
    }
    return EFI_NOT_FOUND;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:  UpdatePrt
//
// Description: This function updates $PIR table with the actual PCI bus numbers.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID UpdatePrt()
{
    EFI_STATUS Status;
    UINTN count1;//, count2, count3;
    UINT8 *p;
    UINT8 chksum = 0;
    UINTN PrtAddress;
//-----------------------------------------

    //Check if PciBus Driver updated IRQ Routing Table yet
    ASSERT(gAmiBoardInfo->DataValid==TRUE);
    
    //Create an instance of IRQ ROUTING tasble with $PIR Headr
    p=MallocZ(sizeof(EFI_LEGACY_PIRQ_TABLE_HEADER) + gAmiBoardInfo->PicRoutLength);
    MemCpy(p,MsPrt,sizeof(EFI_LEGACY_PIRQ_TABLE_HEADER));

    //Since $PRT Table header was created separately 
    //free memory used for Header instance since we have copy it already.
    pBS->FreePool(MsPrt);
    MsPrt=(EFI_LEGACY_PIRQ_TABLE_HEADER*)p;
    p+=sizeof(EFI_LEGACY_PIRQ_TABLE_HEADER);
    MemCpy(p, gAmiBoardInfo->PicRoutTable, gAmiBoardInfo->PicRoutLength);

    //Update gUsedPciEntries since PciBus Driver removed unused entries from the table
    gUsedPciEntries=gAmiBoardInfo->PicRoutLength/sizeof(PCI_IRQ_PIC_ROUTE);
    
    //Update Prt pointer to point at new instance of table and header together.
    Prt=(EFI_LEGACY_IRQ_ROUTING_ENTRY*)p;
    
    //Update table size in $PRT header 
    MsPrt->TableSize = (UINT16)(gAmiBoardInfo->PicRoutLength + sizeof(EFI_LEGACY_PIRQ_TABLE_HEADER));

    // Call BSP routine to do Chipset/OEM specific modifications to PRT
    BspUpdatePrt(&CoreBiosInfo->iBios, MsPrt);

    
    // Checksum the table
    for (count1 = 0; count1 < MsPrt->TableSize; count1++) {
        chksum = chksum + *((UINT8*)MsPrt+count1);
    }
    MsPrt->Checksum = (~chksum) + 1;
    IsValidPrt = TRUE;

    // Load the PCI routing table into CSM16
    PrtAddress = CopyLegacyTable(
                MsPrt,
                (UINT16)MsPrt->TableSize,
                1,  // alignment
                F0000_BIT);
    ASSERT(PrtAddress);

    Status = CoreBiosInfo->iRegion->UnLock (CoreBiosInfo->iRegion, 0xF0000, 0x10000, NULL);
    ASSERT_EFI_ERROR(Status);

    CoreBiosInfo->Csm16Header->IrqRoutingTablePointer = (UINT32)PrtAddress;
    CoreBiosInfo->Csm16Header->IrqRoutingTableLength = (UINT32)MsPrt->TableSize;

    Status = CoreBiosInfo->iRegion->Lock (CoreBiosInfo->iRegion, 0xF0000, 0x10000, NULL);
    ASSERT_EFI_ERROR(Status);

    BusNumXlatProtocol.GetXlatPciBusNum = GetXlatPciBusNumber;
    Status = pBS->InstallProtocolInterface(
        &gHandle,
        &gBusNumXlatProtocol,
        EFI_NATIVE_INTERFACE,
        &BusNumXlatProtocol
    );
    ASSERT_EFI_ERROR(Status);
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:  PciIoNotifyCallback
//
// Description: PciIo notification callback. It serves two purposes:
//              1) Updates bus numbers in BusNumXlat table and in $PIR table. For
//              this the routine uses PciIo to get PCI loaction of the handle;
//              then it will match the found dev/fun against BusNumXlat table
//              and fill global RootBridges data and update bus numbers in
//              $PIR table.
//              2) Programs PCI IRQ register if:
//                  - device requires IRQ to be assigned (reg 3D is 1..3)
//                  - PCI bus information is updated in $PIR table (step 1
//                    has been completed)
//                  - device is present in IRQ routing table
//              When all these conditions are met, then IRQ is assigned to this
//              device according to the PCI IRQ priorities; then IRQ is programmed
//              in PCI register 3C
//
// Input:       Event - event signaled by the DXE Core upon PciIo installation
//              Context - event context
//
// Output:    Nothing
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID PciIoNotifyCallback (
    EFI_EVENT Event,
    VOID      *Context)
{
//  UINT16      counter;
    UINTN       BufferSize = sizeof(EFI_HANDLE);
    EFI_HANDLE  Handle;
    EFI_PCI_IO_PROTOCOL *PciIo;
    EFI_STATUS  Status;
    BOOLEAN     IsRootBridge;
    UINT8       dData[4];
    UINT16      IrqMask;

    if (!IsValidPrt) {
        //
        // Set 8259 interrupt mask for 16 bit mode
        //
        Status = GetIsaIrqs(&IsaIrqMask);   // Ones for ISA IRQs
    //  TRACE((-1, "PciInterrupts: Init PRT Get ISA_IRQ_MASK, Status=%r\n", Status));
        ASSERT_EFI_ERROR(Status);

        IrqMask = ~IsaIrqMask;

        Status = i8259->SetMask(i8259, &IrqMask, NULL, NULL, NULL);
        ASSERT_EFI_ERROR(Status);

        UpdatePrt();    // Update bus numbers in PRT
    }

    //gBS->LocateProtocol(&gEfiPciIoProtocol, gPciIoNotifyReg, &PciIo);
    Status = pBS->LocateHandle(ByRegisterNotify,
                NULL, gPciIoNotifyReg, &BufferSize, &Handle);
    ASSERT_EFI_ERROR(Status);
    if (EFI_ERROR(Status)) return;

    //
    // Locate PciIo protocol installed on Handle
    //
    Status = pBS->HandleProtocol(Handle, &gEfiPciIoProtocolGuid, &PciIo);
    ASSERT_EFI_ERROR(Status);
    if (EFI_ERROR(Status)) return;

    //
    // Check whether Handle is PCI Root Bridge handle.
    //
    Status = PciIo->Pci.Read(
        PciIo,
        EfiPciIoWidthUint32,
        8,  // offset
        1,  // width
        &dData);
    ASSERT_EFI_ERROR(Status);
    if (EFI_ERROR(Status)) return;

    IsRootBridge = (dData[1] == 0) &&
        (dData[2] == PCI_CL_BRIDGE_SCL_HOST) &&
        (dData[3] == PCI_CL_BRIDGE);    // Host bridge

    if (IsRootBridge) return;   // Do not process root bridges

    ProgramPciIrq(PciIo, Context);
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:  InitPrt
//
// Description: Initialize PCI IRQ routing table
//
// Input:   iBiosPlatform - pointer to EFI_LEGACY_BIOS_PLATFORM_PROTOCOL
//
// Output:  PCI IRQ routing table initialization status
//
// Notes:   1) BusNumXlat table is generated by AMISDL and requires the actual PCI bus
//          number fields to be updated. Actual PCI bus numbers can not be obtained at
//          this time due to the following:
//          - BusNumXlat table provides PCI dev/fun information for the PCI Host Bridge(s),
//            whereas PciRootBridgeIo does not give PCI dev/fun information; in case of
//            several PCI Root Bridges, PCI location ambiguity can not be resolved at this
//            time.
//          - PCI Dev/Fun information for PCI Host bridge(s) is not available until
//            PCI Bus driver installs PciIo on PCI Host Bridge devices' handles.
//
//          2) In order to match PCI Root Bridge(s) against the BusNumXlat table, we
//          will register callback notification function that will be called every
//          time PciIo protocol is installed. This would identify every PCI RootBridge's
//          PCI location(dev/fun), allow to match this PCI location against XlatBusNum table,
//          traverse through XlatBusNum table entry and update the appropriate bus number
//          fields in $PIR table.
//
//          3) This driver must be made dependent on PciRootBridge driver since it expects
//          the valid information about PCI root bridges.
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS InitPrt(
    EFI_LEGACY_BIOS_PLATFORM_PROTOCOL   *iBiosPlatform
)
{
    EFI_EVENT   Event;
    EFI_STATUS  Status;
    EFI_LEGACY_INTERRUPT_PROTOCOL       *iInterrupt;
    UINT8       Dev, Func;
//------------------------------------------

    Status = pBS->LocateProtocol (&gEfiLegacyInterruptProtocolGuid, NULL, &iInterrupt);
    if (EFI_ERROR(Status)) return Status;

    //
    // Initialize global variables
    //
    MsPrt = MallocZ(sizeof(EFI_LEGACY_PIRQ_TABLE_HEADER));
    ASSERT(MsPrt!=NULL);
    

    BusNumXlat = (UINT8*)gAmiBoardInfo->BusXlatTable;
    BusNumXlatEnd = (UINT8*)((UINTN)gAmiBoardInfo->BusXlatTable+gAmiBoardInfo->BusXlatLength);
    Prt = (EFI_LEGACY_IRQ_ROUTING_ENTRY*)gAmiBoardInfo->PicRoutTable;
    gUsedPciEntries=gAmiBoardInfo->PicRoutLength/sizeof(PCI_IRQ_PIC_ROUTE);
    IsValidPrt = FALSE; // becomes TRUE after bus numbers and checksum in $PRT table is updated

    pBS->SetMem(AddonPciBusTable, sizeof(EFI_ADDON_PCIBUS_TABLE)*MAX_ADDITIONAL_P2P_BRIDGES, 0);
    gAddonPciBusIndx = 0;

    //Fill MSPRT Structure Header
    MsPrt->Signature=0x52495024; //"$PIR"
    MsPrt->MinorVersion=0; //version (low byte = minor, high byte = major)
    MsPrt->MajorVersion=1;
    MsPrt->TableSize=sizeof(EFI_LEGACY_PIRQ_TABLE_HEADER); //It's only header for now we will connet header and table later

    Status = iInterrupt->GetLocation(iInterrupt, &MsPrt->Bus, &Dev, &Func);
    if (EFI_ERROR(Status)) return Status;

    MsPrt->DevFun = (Dev << 3) + Func;
    MsPrt->CompatibleVid = SB_PIRQ_ROUTER_VID;
    MsPrt->CompatibleDid = SB_PIRQ_ROUTER_DID;

    MemSet(irq_allocated_count, sizeof(irq_allocated_count), 0);

    //
    // Set 8259 interrupt mask for 16 bit mode
    //
    Status = pBS->LocateProtocol (&gEfiLegacy8259ProtocolGuid, NULL, &i8259);
    ASSERT_EFI_ERROR(Status);

    //
    // Count number of entries in BusNumXlat table globally in XlatTblEntriesRemaining
    //
    XlatTblEntriesRemaining=gAmiBoardInfo->BusXlatEntries;
    //
    // Get the list of PCI Root Bridge handles; later on, in the notification callback function,
    // use this list to find the corresponding bus number.
    //
    Status = pBS->LocateHandleBuffer(
                    ByProtocol,
                    &gEfiPciRootBridgeIoProtocol,
                    NULL,
                    &PciRBHandlesNo,
                    &PciRBHandles);
    ASSERT_EFI_ERROR(Status);
    if EFI_ERROR(Status) return Status;

    //
    // Create the notification and register callback function on the PciIo installation,
    // callback function will update $PIR table
    //
    Status = pBS->CreateEvent (
        EVT_NOTIFY_SIGNAL,
        TPL_CALLBACK,
        PciIoNotifyCallback,
        iBiosPlatform,
        &Event);
    ASSERT_EFI_ERROR(Status);
    if (EFI_ERROR(Status)) return Status;

    Status = pBS->RegisterProtocolNotify (
        &gEfiPciIoProtocolGuid,
        Event,
        &gPciIoNotifyReg);
    ASSERT_EFI_ERROR(Status);

    // Install PCI IRQ programming interface
    gIrqPgmCtx.PciIo = NULL;
    gIrqPgmCtx.Irq = 0;
    Status = pBS->InstallProtocolInterface(
        &gHandle,
        &gPciIrqProgramGuid,
        EFI_NATIVE_INTERFACE,
        &gIrqPgmCtx
    );
    ASSERT_EFI_ERROR(Status);

    return Status;
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**           5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093      **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
