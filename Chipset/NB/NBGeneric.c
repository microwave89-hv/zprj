//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

//*************************************************************************
// $Header: /Alaska/BIN/Chipset/Intel/NorthBridge/Haswell/Intel SystemAgent NB Chipset/NBGeneric.c 6     10/14/12 5:17a Jeffch $
//
// $Revision: 6 $
//
// $Date: 10/14/12 5:17a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Chipset/Intel/NorthBridge/Haswell/Intel SystemAgent NB Chipset/NBGeneric.c $
// 
// 6     10/14/12 5:17a Jeffch
// [TAG]          None
// [Severity]     Important
// [Description]  Follow SA RC 0.71.
// [Files]        NBPei.c, NBDxe.c; NBGeneric.c; NBCspLib.h; NBSetup.c;
// Nb.sd; GetSetupData.c
// 
// 5     10/14/12 12:20a Jeffch
// [TAG]         None
// [Severity]    Important
// [Description] Update by XTU4.0.
// [Files]       NBPei.c, NBDxe.c, NBCspLib.h, NBGeneric.c
// 
// 4     9/12/12 6:20a Yurenlai
// [TAG]           None
// [Category]      Improvement
// [Severity]      Important
// [Description]   Fixed some pcie card compatibility issue. <from Jeffch>
// [Files]         NBGeneric.c
// 
// 3     8/24/12 8:09a Yurenlai
// [TAG]  		    None
// [Category]  	Improvement
// [Severity]  	Important
// [Description]  	Remove useless SB_SHADOW_CONTROL.
// [Files]  		NBGeneric.c
// 
// 2     4/05/12 2:45a Yurenlai
// [TAG]  		EIP87103
// [Category]  	Spec Update
// [Severity]  	Important
// [Description]  	Change for SystemAgent RefCode Revision: 0.5.5 .
// [Files]  		NBDxe.c, NBPEI.c, NBSMI.C, NBGeneric.cm NB.sd, NBSetup.c,
// GetSetupData.c, NbSetupData.
// 
// 1     2/08/12 4:34a Yurenlai
// Intel Haswell/NB eChipset initially releases.
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:        NBGeneric.C
//
// Description: This file contains generic NB code that is common between
//              various components such as NB PEI, DXE etc
//
// Notes:       MAKE SURE NO PEI OR DXE SPECIFIC CODE IS NEEDED
//
//<AMI_FHDR_END>
//*************************************************************************

//----------------------------------------------------------------------------
// Include(s)
//----------------------------------------------------------------------------

#include <Efi.h>
#include <token.h>
#include <AmiLib.h>
#include <AmiCspLib.h>
#include <AmiDxeLib.h>
#include <Protocol\PciRootBridgeIo.h>

//----------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//----------------------------------------------------------------------------
// Constant Definition(s)
//--------------------EMRR Support--------------------------------------------
#define MAX_NR_BUS ((PCIEX_LENGTH/0x100000)-1)
#define UNCORE_CR_MCSEG_BASE0 (volatile UINT64*)NB_PCIE_CFG_ADDRESS(MAX_NR_BUS, 0, 1, 0x60) 
#define UNCORE_CR_MCSEG_MASK0_LOW  (volatile UINT32*)NB_PCIE_CFG_ADDRESS(MAX_NR_BUS, 0, 1, 0x68)
#define UNCORE_CR_MCSEG_MASK0_HIGH (volatile UINT32*)NB_PCIE_CFG_ADDRESS(MAX_NR_BUS, 0, 1, 0x6C)
#define UNCORE_CR_MCSEG_BASE1      (volatile UINT64*)NB_PCIE_CFG_ADDRESS((MAX_NR_BUS - 1), 0, 1, 0x60)
#define UNCORE_CR_MCSEG_MASK1_LOW  (volatile UINT32*)NB_PCIE_CFG_ADDRESS((MAX_NR_BUS - 1), 0, 1, 0x68)
#define UNCORE_CR_MCSEG_MASK1_HIGH (volatile UINT32*)NB_PCIE_CFG_ADDRESS((MAX_NR_BUS - 1), 0, 1, 0x6C)
//----------------------------------------------------------------------------

#if     CSM_SUPPORT
#define ATTR_DISABLED           0       // Shadow RAM Disabled
#define ATTR_READ               1       // Shadow RAM Read Enabled
#define ATTR_WRITE              2       // Shadow RAM Write Enabled
#define ATTR_READ_WRITE         3       // Shadow RAM Read/Write Enabled
#endif

// Macro Definition(s)

// Type Definition(s)

// Function Prototype(s)

//----------------------------------------------------------------------------
// Variable and External Declaration(s)
//----------------------------------------------------------------------------
// Variable Declaration(s)

EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *gPciRootBridgeIo;

EFI_RUNTIME_SERVICES            *pRS;

//----------------------------------------------------------------------------
// The following table contains the information regarding the shadow RAM
// registers and other North Bridge registers that need to be restored
// during the S3 wakeup.
// Mention all register address (bus, device, function , register), specify
// the size of the register ans the mask also.
//----------------------------------------------------------------------------
BOOT_SCRIPT_NB_PCI_REG_SAVE gNbRegsSaveTbl[] = {
    {SA_MC_BUS, SA_MC_DEV, SA_MC_FUN, R_SA_PAM0, EfiBootScriptWidthUint8, 0x33},
    {SA_MC_BUS, SA_MC_DEV, SA_MC_FUN, R_SA_PAM1, EfiBootScriptWidthUint8, 0x33},
    {SA_MC_BUS, SA_MC_DEV, SA_MC_FUN, R_SA_PAM2, EfiBootScriptWidthUint8, 0x33},
    {SA_MC_BUS, SA_MC_DEV, SA_MC_FUN, R_SA_PAM3, EfiBootScriptWidthUint8, 0x33},
    {SA_MC_BUS, SA_MC_DEV, SA_MC_FUN, R_SA_PAM4, EfiBootScriptWidthUint8, 0x33},
    {SA_MC_BUS, SA_MC_DEV, SA_MC_FUN, R_SA_PAM5, EfiBootScriptWidthUint8, 0x33},
    {SA_MC_BUS, SA_MC_DEV, SA_MC_FUN, R_SA_PAM6, EfiBootScriptWidthUint8, 0x33},
 //   {SAD_BUS, SAD_DEV, SAD_FUN, SAD_REG_SMRAM, EfiBootScriptWidthUint8, 0xff},
};

#define NUM_NB_PCI_REG_SAVE \
                    sizeof(gNbRegsSaveTbl)/sizeof(BOOT_SCRIPT_NB_PCI_REG_SAVE)

#if     CSM_SUPPORT

/** Porting required for the following structure **/
NB_PAM_STRUCT gPamStruct[] =
{
    {R_SA_PAM1, 0xfc, 0xc0000, 0x4000},   
    {R_SA_PAM1, 0xcf, 0xc4000, 0x4000},   
    {R_SA_PAM2, 0xfc, 0xc8000, 0x4000},   
    {R_SA_PAM2, 0xcf, 0xcc000, 0x4000},   
    {R_SA_PAM3, 0xfc, 0xd0000, 0x4000},   
    {R_SA_PAM3, 0xcf, 0xd4000, 0x4000},   
    {R_SA_PAM4, 0xfc, 0xd8000, 0x4000},   
    {R_SA_PAM4, 0xcf, 0xdc000, 0x4000},   
    {R_SA_PAM5, 0xfc, 0xe0000, 0x4000},
    {R_SA_PAM5, 0xcf, 0xe4000, 0x4000},
    {R_SA_PAM6, 0xfc, 0xe8000, 0x4000},
    {R_SA_PAM6, 0xcf, 0xec000, 0x4000},
    {R_SA_PAM0, 0xcf, 0xf0000,0x10000}
};

#define NUM_PAM_ENTRIES (sizeof(gPamStruct) / sizeof(NB_PAM_STRUCT))

//----------------------------------------------------------------------------
// Start OF CSM Related Porting Hooks
//----------------------------------------------------------------------------

// The following data structure specifies the PCI device/function number of
// the root bridge(s). Number of entries in this table defined by
// ROOT_BRIDGE_COUNT.
// This table is a missing link between RootBridgeIo and PciIo, which allows
// to update BusNumXlat table with actual bus numbers.
// Each entry in the table is a pair of RootBridge UID (UINT32), provided in
// RootBridge device path, and PCI Dev/Func number (UINT8) that can be used 
// to access Root Bridge on
// PCI bus.

// PORTING PORTING - Include device function number of RB 

ROOT_BRIDGE_MAPPING_ENTRY   RbMap[ROOT_BRIDGE_COUNT] = {
//  RB ID           Device function number
    {0x00,          (UINT8)((NB_DEV << 3) + NB_FUN)}
};
UINTN   RbCount = ROOT_BRIDGE_COUNT;

#endif
/*
typedef enum {
  fNoInit   = 0,
  f800      = 800,
  f1000     = 1000,
  f1067     = 1067,
  f1200     = 1200,
  f1333     = 1333,
  f1400     = 1400,
  f1600     = 1600,
  f1800     = 1800,
  f1867     = 1867,
  f2000     = 2000,
  f2133     = 2133,
  f2200     = 2200,
  f2400     = 2400,
  f2600     = 2600,
  f2667     = 2667,
  fUnSupport= 0x7FFFFFFF
} NbFrequency;
*/
#define BCLK_DEFAULT    (100 * 1000 * 1000)
#define fNoInit     (0)
#define f800        (800)
#define f1000       (1000)
#define f1067       (1067)
#define f1200       (1200)
#define f1333       (1333)
#define f1400       (1400)
#define f1600       (1600)
#define f1800       (1800)
#define f1867       (1867)
#define f2000       (2000)
#define f2133       (2133)
#define f2200       (2200)
#define f2400       (2400)
#define f2600       (2600)
#define f2667       (2667)
#define fUnSupport  (0x7FFFFFFF)
typedef UINT32 NbFrequency;
typedef UINT8 NbClockRatio;

// GUID Definition(s)

// Protocol Definition(s)

// External Declaration(s)

// Function Definition(s)

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: NbFrequencyToRatio
//
// Description: Convert the given frequency and reference clock to a clock ratio. 
//
// Input:
//      IN Frequency - The memory frequency.
//      IN The memory reference clock.
//      IN RefBClk - The base system reference clock.
//
// Output:
//      Returns the memory clock ratio.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8
NbFrequencyToRatio (
  UINT32    Frequency,
  UINT8     RefClk,
  UINT32    RefBClk
)
{
  UINT64 Value;
  UINT64 FreqValue;
  UINT32 RefClkValue;
  UINT32 BClkValue;

  BClkValue   = (RefBClk == 0) ? (BCLK_DEFAULT / 100000) : (RefBClk / 100000);
  RefClkValue = (RefClk == 1) ? 200000 : 266667;
  FreqValue   = Mul64 (Frequency, 1000000000ULL);
  Value       = Div64 (FreqValue, (RefClkValue * BClkValue), NULL);
  Value       = ((UINT32) Value + 500) / 1000;

  return ((NbClockRatio) Value);

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: NbRatioToFrequency
//
// Description: Convert the given ratio and reference clock to a memory frequency. 
//
// Input:
//      IN Ratio   - The memory ratio.
//      IN RefClk  - The memory reference clock.
//      IN RefBClk - The base system reference clock.
//
// Output:
//      Returns the memory frequency.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT32
NbRatioToFrequency (
  UINT8   Ratio,
  UINT8   RefClk,
  UINT32  RefBClk
)
{

  UINT64 Value;
  UINT32 BClkValue;
  UINT32 RefClkValue;

  BClkValue   = (RefBClk == 0) ? BCLK_DEFAULT : RefBClk;
  RefClkValue = (RefClk == 1) ? 200000000 : 266666667;
  Value       = Mul64 (RefClkValue, Ratio * BClkValue);
  Value       += 50000000000000ULL;
  Value       = Div64 (Value, (UINTN)100000000000000ULL, NULL);
  return ((NbFrequency) Value);
}
//----------------------------------------------------------------------------
#if     CSM_SUPPORT

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   NBGetPamStartEndIndex
//
// Description: Helper function to get the Start and End Index for
//              PAM register table.
//
// Input:       StartAddress - Shadow RAM start address to be programed
//              Length       - Shadow RAM length to be programed
//              *StartIndex  - Pointer a variable for the Start index
//              *EndIndex    - Pointer a variable for the End index
//
// Output:      EFI_STATUS
//                  EFI_INVALID_PARAMETER - Input Parameter is invalid.
//                  EFI_SUCCESS           - Get indexs from PAM register
//                                          table successfully.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS NBGetPamStartEndIndex (
    IN UINT32                   StartAddress,
    IN UINT32                   Length,
    OUT UINT32                  *StartIndex,
    OUT UINT32                  *EndIndex )
{
    UINT32                  StartIdx;
    UINT32                  EndIdx;
    UINT32                  TotalLength = 0;

    if (StartAddress < gPamStruct[0].StartAddress)
        return EFI_INVALID_PARAMETER;

    for(StartIdx = 0; StartIdx < NUM_PAM_ENTRIES; ++StartIdx) {
        if (StartAddress <= gPamStruct[StartIdx].StartAddress) break;
    }
    if (StartAddress < gPamStruct[StartIdx].StartAddress) StartIdx--;

    if (StartIdx == NUM_PAM_ENTRIES) return EFI_INVALID_PARAMETER;

    // Adjust the length of the requested region if starting address is
    // out of bounds.
    Length += (StartAddress - gPamStruct[StartIdx].StartAddress);

    for(EndIdx = StartIdx; EndIdx < NUM_PAM_ENTRIES; ++EndIdx) {
        TotalLength += gPamStruct[EndIdx].Length;
        if (TotalLength >= Length) break;
    }
    if (EndIdx == NUM_PAM_ENTRIES) return EFI_INVALID_PARAMETER;

    *StartIndex = StartIdx;
    *EndIndex = EndIdx;

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   NBProgramPAMRegisters
//
// Description: Program 0xc0000 - 0xfffff regions to Lock/Unlock.
//
// Input:       pBS          - Pointer to Boot Service Table
//              pRS          - Pointer to Runtime Service Table
//              StartAddress - Shadow RAM start address to be programed
//              Length       - Shadow RAM length to be programed
//              Setting      - Shadow RAM Lock/Unlock status to program
//              *Granularity - The granularity for this region
//
// Output:      EFI_STATUS
//                  EFI_INVALID_PARAMETER - Input Parameter is invalid.
//                  EFI_SUCCESS           - Program successfully.
//
// Notes:       Here is the control flow of this function:
//              1. Search the structure for the first entry matching 
//                 the StartAddress.
//              2. If not found, return EFI_INVALID_PARAMETER.
//              3. Find the last entry in structure for the region to program,
//                 by adding the lengths of the entries.
//              4. If not found, return EFI_INVALID_PARAMETER.
//              5. Read/Write each register for the entry to set region.
//              6. Return the Granularity for the region.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS NBProgramPAMRegisters (
    IN EFI_BOOT_SERVICES    *pBS,
    IN EFI_RUNTIME_SERVICES *pRS,
    IN UINT32               StartAddress,
    IN UINT32               Length,
    IN UINT8                Setting,
    IN OUT UINT32           *Granularity )
{
    // NB shadow programming.
    // Note: For this routine to work, the gPamStruct regions must
    // be continuous.

    EFI_STATUS          Status = EFI_SUCCESS;
    UINT32              StartIndex;
    UINT32              EndIndex;
    UINTN               i;
    UINT8               Data;
    UINT8               Shift;

    Status = NBGetPamStartEndIndex( StartAddress, \
                                    Length, \
                                    &StartIndex, \
                                    &EndIndex );
    if (EFI_ERROR(Status)) return Status;


    for (i = StartIndex; i <= EndIndex; ++i) {
        //Bus 0, Device 0, Function 0
        Data = READ_PCI8_NB(gPamStruct[i].Register);
        Data &= gPamStruct[i].Mask;
        Shift = (gPamStruct[i].Mask == 0xfc) ? 0 : 4;
        switch (Setting) {
            case 0 :            // Read Only
            case 1 :            // Read Only (Permanently)
                    Data |= (ATTR_READ << Shift);
                    break;
            case 2 :            // Read/Write
                    Data |= (ATTR_READ_WRITE << Shift);
                    break;
            case 3 :            // Disabled
            default:
                    break;
        }
        WRITE_PCI8_NB(gPamStruct[i].Register, Data);
    }

    if (Granularity)
        *Granularity = ( (StartAddress+Length) < 0xf0000 ) ? 0x4000 : 0x10000;

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   NBPeiProgramPAMRegisters
//
// Description: Program 0xc0000 - 0xfffff regions to Lock/Unlock.
//
// Input:       PeiServices  - The PEI core services table.
//              StartAddress - Shadow RAM start address to be programed
//              Length       - Shadow RAM length to be programed
//              Setting      - Shadow RAM Lock/Unlock status to program
//              *Granularity - The granularity for this region
//
// Output:      EFI_STATUS
//                  EFI_INVALID_PARAMETER - Input Parameter is invalid.
//                  EFI_SUCCESS           - Program successfully.
//
// Notes:       Here is the control flow of this function:
//              1. Search the structure for the first entry matching 
//                 the StartAddress.
//              2. If not found, return EFI_INVALID_PARAMETER.
//              3. Find the last entry in structure for the region to program,
//                 by adding the lengths of the entries.
//              4. If not found, return EFI_INVALID_PARAMETER.
//              5. Read/Write each register for the entry to set region.
//              6. Return the Granularity for the region.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS NBPeiProgramPAMRegisters (
    IN EFI_PEI_SERVICES     **PeiServices,
    IN UINT32               StartAddress,
    IN UINT32               Length,
    IN UINT8                Setting,
    IN OUT UINT32           *Granularity OPTIONAL )
{
    // NB shadow programming.
    // Note: For this routine to work, the gPamStruct regions must
    // be continuous.

    EFI_STATUS          Status = EFI_SUCCESS;
    UINT32              StartIndex;
    UINT32              EndIndex;
    UINTN               i;
    UINT8               Data;
    UINT8               Shift;

    Status = NBGetPamStartEndIndex( StartAddress, \
                                    Length, \
                                    &StartIndex, \
                                    &EndIndex );
    if (EFI_ERROR(Status)) return Status;


    for (i = StartIndex; i <= EndIndex; ++i) {
        //Bus 0, Device 0, Function 0
        Data = READ_PCI8_NB(gPamStruct[i].Register);
        Data &= gPamStruct[i].Mask;
        Shift = (gPamStruct[i].Mask == 0xfc) ? 0 : 4;
        switch (Setting) {
            case 0 :            // Read Only
            case 1 :            // Read Only (Permanently)
                    Data |= (ATTR_READ << Shift);
                    break;
            case 2 :            // Read/Write
                    Data |= (ATTR_READ_WRITE << Shift);
                    break;
            case 3 :            // Disabled
            default:
                    break;
        }
        WRITE_PCI8_NB(gPamStruct[i].Register, Data);
    }

    if (Granularity)
        *Granularity = ( (StartAddress+Length) < 0xf0000 ) ? 0x4000 : 0x10000;

    return EFI_SUCCESS;
}

//----------------------------------------------------------------------------
#endif          // END OF CSM Related Porting Hooks
//----------------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   NBPAMWriteBootScript
//
// Description: Writes the final settings of NB registers to the BOOT Script
//
// Input:       *BootScriptSave - Pointer to Boot Script Save Protocal
//
// Output:      EFI_STATUS
//                  EFI_SUCCESS
//
// Notes:       Here is the control flow of this function:
//              1. From the Pci register save table, read the pci register
//                 to save.
//              2. Write to the boot script the value.
//              3. Repeat 1 & 2 for all table entries.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS NBPAMWriteBootScript (
    IN AMI_S3_SAVE_PROTOCOL            *BootScriptSave )
{
    UINT8           PciBus8;
    UINT8           PciSubBus8;
    UINTN           i;
    UINT32          Value32;
    UINT64          Address64;

    //Porting required: Write Boot Script

    for (i = 0; i < NUM_NB_PCI_REG_SAVE; ++i) {
        Address64 = NB_PCI_CFG_ADDRESS( gNbRegsSaveTbl[i].Bus, \
                                        gNbRegsSaveTbl[i].Dev, \
                                        gNbRegsSaveTbl[i].Fun, \
                                        gNbRegsSaveTbl[i].Reg );
        gPciRootBridgeIo->Pci.Read( gPciRootBridgeIo, \
                                    gNbRegsSaveTbl[i].Width, \
                                    Address64, \
                                    1, \
                                    &Value32 );
        Value32 &= gNbRegsSaveTbl[i].Mask;
        BOOT_SCRIPT_S3_PCI_CONFIG_WRITE_MACRO( BootScriptSave, \
                                               gNbRegsSaveTbl[i].Width, \
                                               Address64, \
                                               1, \
                                               &Value32 );
    }

    PciBus8 = READ_PCI8_PCIEBRN(PCIEBRN_REG_SBUSN); // 0x19
    // Check nVIDIA PCIe VGA card 
    if (READ_PCI16(PciBus8, 0, 0, PCI_VID) == 0x10de) {
        Value32 = READ_PCI32(PciBus8, 0, 0, PCI_SVID); // 0x2c
        BOOT_SCRIPT_S3_PCI_CONFIG_WRITE_MACRO( \
                                        BootScriptSave, \
                                        EfiBootScriptWidthUint8, \
                                        PCIEBRN_REG(PCIEBRN_REG_SBUSN), \
                                        1, \
                                        &PciBus8 );
        PciSubBus8 = READ_PCI8_PCIEBRN(PCIEBRN_REG_SUBUSN); // 0x1a
        BOOT_SCRIPT_S3_PCI_CONFIG_WRITE_MACRO( \
                                        BootScriptSave, \
                                        EfiBootScriptWidthUint8, \
                                        PCIEBRN_REG(PCIEBRN_REG_SUBUSN), \
                                        1, \
                                        &PciSubBus8 );
        BOOT_SCRIPT_S3_PCI_CONFIG_WRITE_MACRO( \
                                     BootScriptSave, \
                                     EfiBootScriptWidthUint32, \
                                     NB_PCI_CFG_ADDRESS(PciBus8, 0 ,0, 0x40),\
                                     1, \
                                     &Value32 );
    }
    
    return EFI_SUCCESS; 
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: NbFindCapPtr
//
// Description: This function searches the PCI address space for the PCI
//              device specified for a particular capability ID and returns
//              the offset in the PCI address space if one found
//
// Input:    UINT64  PciAddress,
//           UINT8   CapId
//
// Output:  Capability ID Address if one found
//          Otherwise returns 0
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT32 NbFindCapPtr(
 IN UINT64  PciAddress,
 IN UINT8   CapId
)
{
  UINT8   Value;
  UINT32  Address = (UINT32)PciAddress;

  Address = (Address & 0xffffff00) | 6; //PCI Status Register.
  Value = READ_MEM8(Address + 0);

  if (Value == 0xff) return 0;          // No device.
  if (!(Value & (1 << 4))) return 0;    // Check if capabilities list.
   
  *(UINT8*)&Address = 0x34;             // Register to First capabilities pointer
                                        // if 0, then capabilities
  for(;;)
  {
    Value = READ_MEM8(Address + 0);
    if (Value == 0) return 0;

    *(UINT8*)&Address = Value;          // PciAddress = ptr to CapID
    Value = READ_MEM8(Address + 0);     // New cap ptr.

    //If capablity ID, return register that points to it.
    if (Value == CapId) return Address; 

    ++Address;                          // Equals to next capability pointer.
  }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   NBRetrainLinkPciDevice
//
// Description: This function is Retrain Link NB Pci Device.
//
// Input:       PciBus    - PCI Bus Number.
//              PciDev    - PCI Device Number.
//              PciFun    - PCI Function Number.
//              PciCapPtr - PCI CapPtr Number.
//
// Output:      VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID NBRetrainLinkPciDevice (
    IN UINT8                PciBus,
    IN UINT8                PciDev,
    IN UINT8                PciFun,
    IN UINT8                CapPtr )
{
    // Disable Link
    SET_PCI8(PciBus, PciDev, PciFun, CapPtr + 0x10, BIT04);

    // Retrain Link
    RW_PCI8(PciBus, PciDev, PciFun, CapPtr + 0x10 , BIT05, BIT04);

    // Wait Link States
    while (READ_PCI16(PciBus, PciDev, PciFun, CapPtr + 0x12) & BIT11);

    // if Retrain Link Anyway 1, Clear Retrain Link
    if (READ_PCI8(PciBus, PciDev, PciFun, CapPtr + 0x10) & BIT05) {
       RESET_PCI8(PciBus, PciDev, PciFun, CapPtr + 0x10 , BIT05);
    }

    // Wait Link States
    while (READ_PCI16(PciBus, PciDev, PciFun, CapPtr + 0x12) & BIT11);
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   NBProtectedPciDevice
//
// Description: This function is called by PCI Bus Driver before configuring
//              or disabling any PCI device. This function should examine the
//              Vendor/Device ID or PCI Bus, Device and Function numbers to
//              make sure it is not a north bridge device or any other device
//              which should no be configured by PCI Bus Driver.
//
// Input:       *PciDevice - Pointer to PCI Device Info structure.
//
// Output:      EFI_STATUS
//                  EFI_SUCCESS     - SKIP this device, do not touch
//                                    PCI Command register.
//                  EFI_UNSUPPORTED - DON'T SKIP this device do complete
//                                    enumeration as usual.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS NBProtectedPciDevice (
    IN PCI_DEV_INFO             *PciDevice )
{

//####if ((PciDevice->Address.Addr.Bus == NB_BUS) && \
//####    (PciDevice->Address.Addr.Device == NB_DEV) && \
//####    (PciDevice->Address.Addr.Function == NB_FUN)) {
//####
//####    return EFI_SUCCESS;
//####}

    return EFI_UNSUPPORTED;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   NBProgramPciDevice
//
// Description: This function is called by PCI Bus Driver before installing
//              Protocol Interface for the input device.
//
// Input:       *PciDevice - Pointer to PCI Device Info structure.
//
// Output:      EFI_SUCCESS
//
// Notes:       All resource in the device had been assigned, but the command
//              register is disabled.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS NBProgramPciDevice (
    IN PCI_DEV_INFO             *PciDevice )
{

//####if ((PciDevice->Address.Addr.Bus == NB_BUS) && \
//####    (PciDevice->Address.Addr.Device == NB_DEV) && \
//####    (PciDevice->Address.Addr.Function == NB_FUN)) {
//####    // Do any porting if needed.
//####}

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   NBUpdatePciDeviceAttributes
//
// Description: This function is called by PCI Bus Driver, can be used to
//              the attributes of the PCI device.
//
// Input:       *PciDevice   - Pointer to PCI Device Info structure.
//              *Attributes  - Attributes bitmask which caller whants to
//                             change.
//              Capabilities - The PCI device supports Capabilityes
//              Set          - Specifies weathere to set or reset given
//                             "Attributes".
//
// Output:      EFI_SUCCESS
//
// Notes:       This routine may be invoked twice depend on the device type,
//              the first time is at BDS phase, the second is before
//              legacy boot.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS NBUpdatePciDeviceAttributes (
    IN PCI_DEV_INFO             *PciDevice,
    IN OUT UINT64               *Attributes,
    IN UINT64                   Capabilities,
    IN BOOLEAN                  Set )
{

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   NBGetTsegBase
//
// Description: Returns the base address of TSEG.
//
// Input:       None
//
// Output:      UINT32 - The Base Address of TSEG.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT32 NBGetTsegBase (VOID)
{
    return (READ_PCI32_NB(0xB8) & 0xFFF00000);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   NBEnableEmrr
//
// Description: Enable and lock CPU EMRR.
//
// Input:       UINT32 IedStart - Intel Enhanced Debug start.
//              UINT32 IedSize  - Intel Enhanced Debug size.
// 
// Output:      VOID
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID NBEnableEmrr(
     IN UINT32 IedStart, 
     IN UINT32 IedSize
)
{
    if ((*UNCORE_CR_MCSEG_MASK0_LOW & (1 << 11)) == 0 ) {
        *UNCORE_CR_MCSEG_BASE0 = (UINT32)IedStart + 0x200000;
        *UNCORE_CR_MCSEG_MASK0_LOW  = 0xffe00000;
        *UNCORE_CR_MCSEG_MASK0_HIGH = 0xff;
        *UNCORE_CR_MCSEG_MASK0_LOW |= (1 << 11); //Enable bit.
        *UNCORE_CR_MCSEG_MASK0_LOW |= (1 << 10); //Lock bit.
    }
    
    if ((*UNCORE_CR_MCSEG_MASK1_LOW & (1 << 11)) == 0 ) {
        *UNCORE_CR_MCSEG_BASE1 = (UINT32)IedStart + 0x300000;
        *UNCORE_CR_MCSEG_MASK1_LOW = 0xffe00000;
        *UNCORE_CR_MCSEG_MASK1_HIGH = 0xff;
        *UNCORE_CR_MCSEG_MASK1_LOW |= (1 << 11); //Enable bit.
        *UNCORE_CR_MCSEG_MASK1_LOW |= (1 << 10); //Lock bit.
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   NbRuntimeShadowRamWrite
//
// Description: This function provides runtime interface to enable/disable
//              writing in E000-F000 segment
//
// Input:       IN BOOLEAN Enable - if TRUE - enable writing, if FALSE - disable
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID NbRuntimeShadowRamWrite(
    IN BOOLEAN Enable
)
{
    // Porting Required.
    static UINT8   F000Reg = 0xff; // 0x80
    static UINT8   E000Reg = 0xff; // 0x85
    static UINT8   E800Reg = 0xff; // 0x86

    if (Enable) {
        F000Reg = READ_PCI8_NB(R_SA_PAM0); // 0x80
        SET_PCI8_NB(R_SA_PAM0, 0x30);
        
        E000Reg = READ_PCI8_NB(R_SA_PAM5); // 0x85
        E800Reg = READ_PCI8_NB(R_SA_PAM6); // 0x86
        SET_PCI8_NB(R_SA_PAM5, 0x33);
        SET_PCI8_NB(R_SA_PAM6, 0x33);
    } else {
        if (F000Reg != 0xff) {
            WRITE_PCI8_NB(R_SA_PAM0, F000Reg); // 0x80
            WRITE_PCI8_NB(R_SA_PAM5, E000Reg); // 0x85
            WRITE_PCI8_NB(R_SA_PAM6, E800Reg); // 0x86
        }
    }

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: CheckPeiFvCopyToRam
//
// Description: Check system is cold or warm boot    
//
// Input:       PeiServices  - The PEI core services table.
//
// Output:      PeiFvCopyToRam - TRUE  for cold boot.
//                             - FALSE for warm boot.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN
CheckPeiFvCopyToRam (
  IN  EFI_PEI_SERVICES  **PeiServices
)
{

  UINT16        Buff16;
  BOOLEAN       PeiFvCopyToRam;


  Buff16 = READ_PCI16_SB(0xA2);

  if (((Buff16 & BIT5) != 0) && ((Buff16 & BIT7) != 0)) 
  {
    PeiFvCopyToRam = FALSE;

  } else {

    PeiFvCopyToRam = TRUE;
  }

  if (READ_MEM32_MCH(0x5D10) == 0)PeiFvCopyToRam = TRUE;

  return PeiFvCopyToRam;

}

//----------------------------------------------------------------------------
// Standard PCI Access Routines, No Porting Required.
//----------------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   ReadPci8
//
// Description: This function reads an 8bits data from the specific PCI 
//              register. 
//
// Input:       Bus - PCI Bus number.
//              Dev - PCI Device number.
//              Fun - PCI Function number.
//              Reg - PCI Register number.
//
// Output:      UINT8
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8 ReadPci8 (
    IN UINT8        Bus, 
    IN UINT8        Dev,
    IN UINT8        Fun, 
    IN UINT16       Reg )
{
    if (Reg >= 0x100) {
        return MMIO_READ8(NB_PCIE_CFG_ADDRESS(Bus, Dev, Fun, Reg));
    } else {
        IoWrite32(NB_PCICFG_SPACE_INDEX_REG, \
                BIT31 | (Bus << 16) | (Dev << 11) | (Fun << 8) | (Reg & 0xfc));
        return IoRead8(NB_PCICFG_SPACE_DATA_REG | (UINT8)(Reg & 3));
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   ReadPci16
//
// Description: This function reads a 16bits data from the specific PCI 
//              register. 
//
// Input:       Bus - PCI Bus number.
//              Dev - PCI Device number.
//              Fun - PCI Function number.
//              Reg - PCI Register number.
//
// Output:      UINT16
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT16 ReadPci16 (
    IN UINT8        Bus, 
    IN UINT8        Dev,
    IN UINT8        Fun, 
    IN UINT16       Reg )
{
    if (Reg >= 0x100) {
        return MMIO_READ16(NB_PCIE_CFG_ADDRESS(Bus, Dev, Fun, Reg));
    } else {
        IoWrite32(NB_PCICFG_SPACE_INDEX_REG, \
                BIT31 | (Bus << 16) | (Dev << 11) | (Fun << 8) | (Reg & 0xfc));
        return IoRead16(NB_PCICFG_SPACE_DATA_REG | (UINT8)(Reg & 2));
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   ReadPci32
//
// Description: This function reads a 32bits data from the specific PCI 
//              register. 
//
// Input:       Bus - PCI Bus number.
//              Dev - PCI Device number.
//              Fun - PCI Function number.
//              Reg - PCI Register number.
//
// Output:      UINT32
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT32 ReadPci32 (
    IN UINT8        Bus, 
    IN UINT8        Dev,
    IN UINT8        Fun, 
    IN UINT16       Reg )
{
    if (Reg >= 0x100) {
        return MMIO_READ32(NB_PCIE_CFG_ADDRESS(Bus, Dev, Fun, Reg));
    } else {
        IoWrite32(NB_PCICFG_SPACE_INDEX_REG, \
                BIT31 | (Bus << 16) | (Dev << 11) | (Fun << 8) | (Reg & 0xfc));
        return IoRead32(NB_PCICFG_SPACE_DATA_REG);
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   WritePci8
//
// Description: This function writes an 8bits data to the specific PCI
//              register.
//
// Input:       Bus     - PCI Bus number.
//              Dev     - PCI Device number.
//              Fun     - PCI Function number.
//              Reg     - PCI Register number.
//              Value8  - An 8 Bits data will be written to the specific 
//                        PCI register.
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID WritePci8 (
    IN UINT8        Bus, 
    IN UINT8        Dev,
    IN UINT8        Fun, 
    IN UINT16       Reg,
    IN UINT8        Value8 )
{
    if (Reg >= 0x100) {
        WriteMem8((UINT64)NB_PCIE_CFG_ADDRESS(Bus, Dev, Fun, Reg), Value8);
    } else {
        IoWrite32(NB_PCICFG_SPACE_INDEX_REG, \
                BIT31 | (Bus << 16) | (Dev << 11) | (Fun << 8) | (Reg & 0xfc));
        IoWrite8(NB_PCICFG_SPACE_DATA_REG | (UINT8)(Reg & 3), Value8);
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   WritePci16
//
// Description: This function writes a 16bits data to the specific PCI
//              register.
//
// Input:       Bus     - PCI Bus number.
//              Dev     - PCI Device number.
//              Fun     - PCI Function number.
//              Reg     - PCI Register number.
//              Value16 - A 16 Bits data will be written to the specific 
//                        PCI register.
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID WritePci16 (
    IN UINT8        Bus, 
    IN UINT8        Dev,
    IN UINT8        Fun, 
    IN UINT16       Reg,
    IN UINT16       Value16 )
{
    if (Reg >= 0x100) {
        WriteMem16((UINT64)NB_PCIE_CFG_ADDRESS(Bus, Dev, Fun, Reg), Value16);
    } else {
        IoWrite32(NB_PCICFG_SPACE_INDEX_REG, \
                BIT31 | (Bus << 16) | (Dev << 11) | (Fun << 8) | (Reg & 0xfc));
        IoWrite16(NB_PCICFG_SPACE_DATA_REG | (UINT8)(Reg & 2), Value16);
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   WritePci32
//
// Description: This function writes a 32bits data to the specific PCI
//              register.
//
// Input:       Bus     - PCI Bus number.
//              Dev     - PCI Device number.
//              Fun     - PCI Function number.
//              Reg     - PCI Register number.
//              Value32 - A 32 Bits data will be written to the specific 
//                        PCI register.
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID WritePci32 (
    IN UINT8        Bus, 
    IN UINT8        Dev,
    IN UINT8        Fun, 
    IN UINT16       Reg,
    IN UINT32       Value32 )
{
    if (Reg >= 0x100) {
        WriteMem32((UINT64)NB_PCIE_CFG_ADDRESS(Bus, Dev, Fun, Reg), Value32);
    } else {
        IoWrite32(NB_PCICFG_SPACE_INDEX_REG, \
                BIT31 | (Bus << 16) | (Dev << 11) | (Fun << 8) | (Reg & 0xfc));
        IoWrite32(NB_PCICFG_SPACE_DATA_REG, Value32);
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   WritePci8S3
//
// Description: This function writes an 8bits data to the specific PCI 
//              register and Boot Script.
//
// Input:       *mBootScriptSave - Pointer to Boot Script Save Protocal
//              Bus              - PCI Bus number.
//              Dev              - PCI Device number.
//              Fun              - PCI Function number.
//              Reg              - PCI Register number.
//              Value8           - An 8 Bits data will be written to the
//                                 specific PCI register and Boot Script.
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID WritePci8S3 (
    IN AMI_S3_SAVE_PROTOCOL             *mBootScriptSave,
    IN UINT8                            Bus, 
    IN UINT8                            Dev,
    IN UINT8                            Fun, 
    IN UINT16                           Reg,
    IN UINT8                            Value8 )
{
    WritePci8(Bus, Dev, Fun, Reg, Value8);

    if (Reg >= 0x100) 
        BOOT_SCRIPT_S3_MEM_WRITE_MACRO( \
                                    mBootScriptSave, \
                                    EfiBootScriptWidthUint8, \
                                    NB_PCIE_CFG_ADDRESS(Bus, Dev, Fun, Reg), \
                                    1, \
                                    &Value8 );
    else 
        BOOT_SCRIPT_S3_PCI_CONFIG_WRITE_MACRO( \
                                    mBootScriptSave, \
                                    EfiBootScriptWidthUint8, \
                                    NB_PCI_CFG_ADDRESS(Bus, Dev, Fun, Reg), \
                                    1, \
                                    &Value8 );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   WritePci16S3
//
// Description: This function writes a 16bits data to the specific PCI 
//              register and Boot Script.
//
// Input:       *mBootScriptSave - Pointer to Boot Script Save Protocal
//              Bus              - PCI Bus number.
//              Dev              - PCI Device number.
//              Fun              - PCI Function number.
//              Reg              - PCI Register number.
//              Value16          - A 16 Bits data will be written to the
//                                 specific PCI register and Boot Script.
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID WritePci16S3 (
    IN AMI_S3_SAVE_PROTOCOL             *mBootScriptSave,
    IN UINT8                            Bus, 
    IN UINT8                            Dev,
    IN UINT8                            Fun, 
    IN UINT16                           Reg,
    IN UINT16                           Value16 )
{

    WritePci16(Bus, Dev, Fun, Reg, Value16);

    if (Reg >= 0x100) 
        BOOT_SCRIPT_S3_MEM_WRITE_MACRO( \
                                    mBootScriptSave, \
                                    EfiBootScriptWidthUint16, \
                                    NB_PCIE_CFG_ADDRESS(Bus, Dev, Fun, Reg), \
                                    1, \
                                    &Value16 );
    else 
        BOOT_SCRIPT_S3_PCI_CONFIG_WRITE_MACRO( \
                                    mBootScriptSave, \
                                    EfiBootScriptWidthUint16, \
                                    NB_PCI_CFG_ADDRESS(Bus, Dev, Fun, Reg), \
                                    1, \
                                    &Value16 );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   WritePci32S3
//
// Description: This function writes a 32bits data to the specific PCI 
//              register and Boot Script.
//
// Input:       *mBootScriptSave - Pointer to Boot Script Save Protocal
//              Bus              - PCI Bus number.
//              Dev              - PCI Device number.
//              Fun              - PCI Function number.
//              Reg              - PCI Register number.
//              Value32          - A 32 Bits data will be written to the
//                                 specific PCI register and Boot Script.
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID WritePci32S3 (
    IN AMI_S3_SAVE_PROTOCOL             *mBootScriptSave,
    IN UINT8                            Bus, 
    IN UINT8                            Dev,
    IN UINT8                            Fun, 
    IN UINT16                           Reg,
    IN UINT32                           Value32 )
{

    WritePci32(Bus, Dev, Fun, Reg, Value32);

    if (Reg >= 0x100) 
        BOOT_SCRIPT_S3_MEM_WRITE_MACRO( \
                                    mBootScriptSave, \
                                    EfiBootScriptWidthUint32, \
                                    NB_PCIE_CFG_ADDRESS(Bus, Dev, Fun, Reg), \
                                    1, \
                                    &Value32 );
    else 
        BOOT_SCRIPT_S3_PCI_CONFIG_WRITE_MACRO( \
                                    mBootScriptSave, \
                                    EfiBootScriptWidthUint32, \
                                    NB_PCI_CFG_ADDRESS(Bus, Dev, Fun, Reg), \
                                    1, \
                                    &Value32 );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   RwPci8S3
//
// Description: This function reads an 8bits data from the specific PCI
//              register, applies masks, and writes it back, also writes it
//              to Boot Script.
//
// Input:       *mBootScriptSave - Pointer to Boot Script Save Protocal
//              Bus              - PCI Bus number.
//              Dev              - PCI Device number.
//              Fun              - PCI Function number.
//              Reg              - PCI Register number.
//              SetBit8          - Mask of bits to set (1 = Set)
//              ResetBit8        - Mask of bits to clear  (1 = clear)
//
// Output:      None.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID RwPci8S3 (
    IN AMI_S3_SAVE_PROTOCOL             *mBootScriptSave,
    IN UINT8                            Bus, 
    IN UINT8                            Dev,
    IN UINT8                            Fun, 
    IN UINT16                           Reg,
    IN UINT8                            SetBit8,
    IN UINT8                            ResetBit8 )
{
    RW_PCI8(Bus, Dev, Fun, Reg, SetBit8, ResetBit8);

    ResetBit8 = ~ResetBit8;

    if (Reg >= 0x100) 
        BOOT_SCRIPT_S3_MEM_READ_WRITE_MACRO( \
                                    mBootScriptSave, \
                                    EfiBootScriptWidthUint8, \
                                    NB_PCIE_CFG_ADDRESS(Bus, Dev, Fun, Reg), \
                                    &SetBit8, \
                                    &ResetBit8 ); 
    else 
        BOOT_SCRIPT_S3_PCI_CONFIG_READ_WRITE_MACRO( \
                                    mBootScriptSave, \
                                    EfiBootScriptWidthUint8, \
                                    NB_PCI_CFG_ADDRESS(Bus, Dev, Fun, Reg), \
                                    &SetBit8, \
                                    &ResetBit8 );

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   RwPci16S3
//
// Description: This function reads a 16bits data from the specific PCI
//              register, applies masks, and writes it back, also writes it
//              to Boot Script.
//
// Input:       *mBootScriptSave - Pointer to Boot Script Save Protocal
//              Bus              - PCI Bus number.
//              Dev              - PCI Device number.
//              Fun              - PCI Function number.
//              Reg              - PCI Register number.
//              SetBit16         - Mask of bits to set (1 = Set)
//              ResetBit16       - Mask of bits to clear  (1 = clear)
//
// Output:      None.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID RwPci16S3 (
    IN AMI_S3_SAVE_PROTOCOL             *mBootScriptSave,
    IN UINT8                            Bus, 
    IN UINT8                            Dev,
    IN UINT8                            Fun, 
    IN UINT16                           Reg,
    IN UINT16                           SetBit16,
    IN UINT16                           ResetBit16 )
{
    RW_PCI16(Bus, Dev, Fun, Reg, SetBit16, ResetBit16);

    ResetBit16 = ~ResetBit16;

    if (Reg >= 0x100) 
        BOOT_SCRIPT_S3_MEM_READ_WRITE_MACRO( \
                                    mBootScriptSave, \
                                    EfiBootScriptWidthUint16, \
                                    NB_PCIE_CFG_ADDRESS(Bus, Dev, Fun, Reg), \
                                    &SetBit16, \
                                    &ResetBit16 ); 
    else 
        BOOT_SCRIPT_S3_PCI_CONFIG_READ_WRITE_MACRO( \
                                    mBootScriptSave, \
                                    EfiBootScriptWidthUint16, \
                                    NB_PCI_CFG_ADDRESS(Bus, Dev, Fun, Reg), \
                                    &SetBit16, \
                                    &ResetBit16 );

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   RwPci32S3
//
// Description: This function reads a 32bits data from the specific PCI
//              register, applies masks, and writes it back, also writes it
//              to Boot Script.
//
// Input:       *mBootScriptSave - Pointer to Boot Script Save Protocal
//              Bus              - PCI Bus number.
//              Dev              - PCI Device number.
//              Fun              - PCI Function number.
//              Reg              - PCI Register number.
//              SetBit32         - Mask of bits to set (1 = Set)
//              ResetBit32       - Mask of bits to clear  (1 = clear)
//
// Output:      None.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID RwPci32S3 (
    IN AMI_S3_SAVE_PROTOCOL             *mBootScriptSave,
    IN UINT8                            Bus, 
    IN UINT8                            Dev,
    IN UINT8                            Fun, 
    IN UINT16                           Reg,
    IN UINT32                           SetBit32,
    IN UINT32                           ResetBit32 )
{
    RW_PCI32(Bus, Dev, Fun, Reg, SetBit32, ResetBit32);

    ResetBit32 = ~ResetBit32;

    if (Reg >= 0x100) 
        BOOT_SCRIPT_S3_MEM_READ_WRITE_MACRO( \
                                    mBootScriptSave, \
                                    EfiBootScriptWidthUint32, \
                                    NB_PCIE_CFG_ADDRESS(Bus, Dev, Fun, Reg), \
                                    &SetBit32, \
                                    &ResetBit32 ); 
    else 
        BOOT_SCRIPT_S3_PCI_CONFIG_READ_WRITE_MACRO( \
                                    mBootScriptSave, \
                                    EfiBootScriptWidthUint32, \
                                    NB_PCI_CFG_ADDRESS(Bus, Dev, Fun, Reg), \
                                    &SetBit32, \
                                    &ResetBit32 );

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   WriteMem8
//
// Description: This function writes an 8bits data to the specific memory
//              (or MMIO) register.
//
// Input:       Address - An 64Bits Memory (or MMIO) address
//              Value8  - An 8 Bits data will be written to the specific 
//                        PCI register.
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID WriteMem8 (
    IN UINT64       Address,
    IN UINT8        Value8 )
{
    MMIO_WRITE8(Address, Value8);
    Value8 = MMIO_READ8(Address);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   WriteMem16
//
// Description: This function writes a 16bits data to the specific memory
//              (or MMIO) register.
//
// Input:       Address - A 64Bits Memory (or MMIO) address
//              Value16 - A 16 Bits data will be written to the specific 
//                        PCI register.
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID WriteMem16 (
    IN UINT64       Address,
    IN UINT16       Value16 )
{
    MMIO_WRITE16(Address, Value16);
    Value16 = MMIO_READ16(Address);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   WriteMem32
//
// Description: This function writes a 32bits data to the specific memory
//              (or MMIO) register.
//
// Input:       Address - A 64Bits Memory (or MMIO) address
//              Value32 - A 32 Bits data will be written to the specific 
//                        PCI register.
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID WriteMem32 (
    IN UINT64       Address,
    IN UINT32       Value32 )
{
    MMIO_WRITE32(Address, Value32);
    Value32 = MMIO_READ32(Address);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   RwMem8
//
// Description: This function reads an 8bits data from a specific memory
//              (or MMIO) address, applies masks, and writes it back.
//
// Input:       Address - A 64Bits Memory (or MMIO) address
//              SetBit8 - Mask of bits to set (1 = Set)
//              ResetBit8 - Mask of bits to clear  (1 = clear)
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID RwMem8 (
    IN UINT64       Address,
    IN UINT8        SetBit8,
    IN UINT8        ResetBit8 )
{
    UINT8       Buffer8 = MMIO_READ8(Address) & ~ResetBit8 | SetBit8;

    WriteMem8(Address, Buffer8);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   RwMem16
//
// Description: This function reads a 16bits data from a specific memory
//              (or MMIO) address, applies masks, and writes it back.
//
// Input:       Address - A 64Bits Memory (or MMIO) address
//              SetBit16 - Mask of bits to set (1 = Set)
//              ResetBit16 - Mask of bits to clear  (1 = clear)
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID RwMem16 (
    IN UINT64       Address,
    IN UINT16       SetBit16,
    IN UINT16       ResetBit16 )
{
    UINT16      Buffer16 = MMIO_READ16(Address) & ~ResetBit16 | SetBit16;

    WriteMem16(Address, Buffer16);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   RwMem32
//
// Description: This function reads a 32bits data from a specific memory
//              (or MMIO) address, applies masks, and writes it back.
//
// Input:       Address - A 64Bits Memory (or MMIO) address
//              SetBit32 - Mask of bits to set (1 = Set)
//              ResetBit32 - Mask of bits to clear  (1 = clear)
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID RwMem32 (
    IN UINT64       Address,
    IN UINT32       SetBit32,
    IN UINT32       ResetBit32 )
{
    UINT32      Buffer32 = MMIO_READ32(Address) & ~ResetBit32 | SetBit32;

    WriteMem32(Address, Buffer32);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   WriteMem8S3
//
// Description: This function writes an 8bits data to a specific memory
//              (or MMIO) address and Boot Script. 
//
// Input:       *mBootScriptSave - Pointer to Boot Script Save Protocal
//              Address          - A 64Bits Memory (or MMIO) address
//              Value8           - An 8Bits data writes to the address.
//
// Output:      None.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID WriteMem8S3 (
    IN AMI_S3_SAVE_PROTOCOL             *mBootScriptSave,
    IN UINT64                           Address,
    IN UINT8                            Value8 )
{

    WriteMem8(Address, Value8);

    BOOT_SCRIPT_S3_MEM_WRITE_MACRO( mBootScriptSave, \
                                    EfiBootScriptWidthUint8, \
                                    Address, \
                                    1, \
                                    &Value8 );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   WriteMem16S3
//
// Description: This function writes a 16bits data to a specific memory
//              (or MMIO) address and Boot Script. 
//
// Input:       *mBootScriptSave - Pointer to Boot Script Save Protocal
//              Address          - A 64Bits Memory (or MMIO) address
//              Value16          - A 16Bits data writes to the address.
//
// Output:      None.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID WriteMem16S3(
    IN AMI_S3_SAVE_PROTOCOL             *mBootScriptSave,
    IN UINT64                           Address,
    IN UINT16                           Value16 )
{
    WriteMem16(Address, Value16);

    BOOT_SCRIPT_S3_MEM_WRITE_MACRO( mBootScriptSave, \
                                    EfiBootScriptWidthUint16, \
                                    Address, \
                                    1, \
                                    &Value16 );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   WriteMem32S3
//
// Description: This function writes a 32bits data to a specific memory
//              (or MMIO) address and Boot Script. 
//
// Input:       *mBootScriptSave - Pointer to Boot Script Save Protocal
//              Address          - A 64Bits Memory (or MMIO) address
//              Value32          - A 32Bits data writes to the address.
//
// Output:      None.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID WriteMem32S3 (
    IN AMI_S3_SAVE_PROTOCOL             *mBootScriptSave,
    IN UINT64                           Address,
    IN UINT32                           Value32 )
{

    WriteMem32(Address, Value32);

    BOOT_SCRIPT_S3_MEM_WRITE_MACRO( mBootScriptSave, \
                                    EfiBootScriptWidthUint32, \
                                    Address, \
                                    1, \
                                    &Value32 );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   RwMem8S3
//
// Description: This function reads an 8bits data from a specific memory
//              (or MMIO) address, applies masks, and writes it back, also
//              writes it to Boot Script.
//
// Input:       *mBootScriptSave - Pointer to Boot Script Save Protocal
//              Address - A 64Bits Memory (or MMIO) address
//              SetBit8 - Mask of bits to set (1 = Set)
//              ResetBit8 - Mask of bits to clear  (1 = clear)
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID RwMem8S3 (
    IN AMI_S3_SAVE_PROTOCOL             *mBootScriptSave,
    IN UINT64                           Address,
    IN UINT8                            SetBit8,
    IN UINT8                            ResetBit8 )
{
    RwMem8(Address, SetBit8, ResetBit8);

    ResetBit8 = ~ResetBit8;
    BOOT_SCRIPT_S3_MEM_READ_WRITE_MACRO( mBootScriptSave, \
                                         EfiBootScriptWidthUint8, \
                                         Address, \
                                         &SetBit8, \
                                         &ResetBit8 ); 
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   RwMem16S3
//
// Description: This function reads a 16bits data from a specific memory
//              (or MMIO) address, applies masks, and writes it back, also
//              writes it to Boot Script.
//
// Input:       *mBootScriptSave - Pointer to Boot Script Save Protocal
//              Address - A 64Bits Memory (or MMIO) address
//              SetBit16 - Mask of bits to set (1 = Set)
//              ResetBit16 - Mask of bits to clear  (1 = clear)
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID RwMem16S3 (
    IN AMI_S3_SAVE_PROTOCOL             *mBootScriptSave,
    IN UINT64                           Address,
    IN UINT16                           SetBit16,
    IN UINT16                           ResetBit16 )
{
    RwMem16(Address, SetBit16, ResetBit16);

    ResetBit16 = ~ResetBit16;
    BOOT_SCRIPT_S3_MEM_READ_WRITE_MACRO( mBootScriptSave, \
                                         EfiBootScriptWidthUint16, \
                                         Address, \
                                         &SetBit16, \
                                         &ResetBit16 );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   RwMem32S3
//
// Description: This function reads a 32bits data from a specific memory
//              (or MMIO) address, applies masks, and writes it back, also
//              writes it to Boot Script.
//
// Input:       *mBootScriptSave - Pointer to Boot Script Save Protocal
//              Address - A 64Bits Memory (or MMIO) address
//              SetBit32 - Mask of bits to set (1 = Set)
//              ResetBit32 - Mask of bits to clear  (1 = clear)
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID RwMem32S3 (
    IN AMI_S3_SAVE_PROTOCOL             *mBootScriptSave,
    IN UINT64                           Address,
    IN UINT32                           SetBit32,
    IN UINT32                           ResetBit32 )
{
    RwMem32(Address, SetBit32, ResetBit32);

    ResetBit32 = ~ResetBit32;
    BOOT_SCRIPT_S3_MEM_READ_WRITE_MACRO( mBootScriptSave, \
                                         EfiBootScriptWidthUint32, \
                                         Address, \
                                         &SetBit32, \
                                         &ResetBit32 );
}

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
