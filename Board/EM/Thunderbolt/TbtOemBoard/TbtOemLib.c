//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.            **
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
// $Header: /Alaska/SOURCE/Modules/Thunderbolt/TbtOemBoard/TbtOemLib.c 13    5/19/14 7:38a Barretlin $
//
// $Revision: 13 $
//
// $Date: 5/19/14 7:38a $
//*************************************************************************
// ReviGpion History
// ----------------
// $Log: /Alaska/SOURCE/Modules/Thunderbolt/TbtOemBoard/TbtOemLib.c $
// 
// 13    5/19/14 7:38a Barretlin
// [TAG]  		EIP165410
// [Category]  	New Feature
// [Description]  	Support Thunderbolt AIC at NB PCIE slot
// [Files]  		TbtPei.c TbtDxe.c TbtGpe.asl TbtSmm.c TbtOemBoard.c
// TbtOemLib.c TbtOemLib.h TbtSetup.sdl TbtSetup.sd TbtSetup.uni
// TbtSetupReset.c
// 
// 12    2/18/14 12:16p Barretlin
// [TAG]  		EIP152401
// [Category]  	Spec Update
// [Severity]  	Minor
// [Description]  	add new Thunderbolt chip series
// [Files]  		TbtOemLib.c
// 
// 11    1/05/14 2:06p Barretlin
// [TAG]  		EIP N/A
// [Category]  	New Feature
// [Description]  	Support Thunderbolt feature Enable/Disable in run time
// Support dynamic Thunderbolt AIC location in run time
// [Files]  		TbtOemBoard.h TbtOemBoard.c TbtOemLib.c TbtOemLib.h
// 
// 10    5/27/13 8:11a Barretlin
// [TAG]  		EIP124914
// [Category]  	New Feature
// [Description]  	Support Falcon Ridge chip
// [Files]  		TbtOemLib.c
// 
// 9     4/12/13 1:48p Barretlin
// [TAG]  		EIP N/A
// [Category]  	Improvement
// [Description]  	Use token decide default thunderbolt Chip
// [Files]  		TbtOemBoard.sdl TbtOemLib.c
// 
// 8     4/12/13 1:30p Barretlin
// 
// 7     4/10/13 2:57p Barretlin
// [TAG]  		EIP N/A
// [Category]  	Improvement
// [Description]  	Add new sample code for CRB
// [Files]  		TbtOemLib.c
// 
// 6     4/03/13 2:47a Barretlin
// [TAG]  		EIP N/A
// [Category]  	Improvement
// [Description]  	Double check Security Level between Thunderbolt host FW
// and BIOS are same or not for Redwood Ridge chip when entering setup
// page.
// [Files]  		TbtOemLib.c TbtOemLib.h TbtSetupReset.c
// 
// 5     3/21/13 6:48a Barretlin
// [TAG]  		EIP N/A
// [Category]  	Improvement
// [Description]  	Update sample code to fix FW's security level doesn't
// match BIOS configuration.
// [Files]  		TbtOemLib.c
// 
// 4     2/08/13 2:05a Barretlin
// 
// 3     2/06/13 6:45a Barretlin
// [TAG]  		EIP114556
// [Category]  	Spec Update
// [Severity]  	Minor
// [Description]  	Update RR handshake flow and sample code for
// Thunderbolt RR Spec 0.9
// [Files]  		TbtOemLib.c
// 
// 2     1/27/13 4:36a Barretlin
// [TAG]  		EIP N/A
// [Category]  	Improvement
// [Description]  	Change sample code avoiding side effect
// [Files]  		TbtOemLib.c
// 
// 1     1/10/13 4:57a Barretlin
// Change SS path and update module for Thunderbolt Spec 1.6 for Cactus
// Ridge chip and Thunderbolt Spec 0.5 for Redwood Ridge chip
// 
// 12    12/13/12 4:06a Barretlin
// [TAG]  		EIP N/A
// [Category]  	Improvement
// [Description]  	Fix build error
// [Files]  		TbtOemLib.c
// 
// 11    12/12/12 4:14a Barretlin
// [TAG]  		EIP108272
// [Category]  	Spec Update
// [Severity]  	Important
// [Description]  	Update to Spec 1.4 to support Redwood Ridge chip
// [Files]  		TbtPei.c TbtSmm.c TbtDxe.c TbtDxe.sdl TbtGpe.asl
// TbtOemBoard.c TbtOemBoard.h TbtOemLib.c TbtOemLib.h
// 
// 10    10/28/12 11:50p Barretlin
// [TAG]  		EIP104870
// [Category]  	Spec Update
// [Severity]  	Important
// [Description]  	Change wake up flow for Spec 1.2 and Spec 1.3
// [Files]  		TbtPei.c TbtSmm.c TbtOemBoard.c TbtOemBoard.h
// TbtOemBoard.sdl TbtOemLib.c TbtOemLib.h
// 
// 9     10/04/12 10:42p Barretlin
// [TAG]  		EIP102947
// [Category]  	Spec Update
// [Severity]  	Normal
// [Description]  	Update Thunderbolt Spec to Rev 1.2
// [Files]  		TbtPei.c TbtOemLib.c TbtOemLib.h
// 
// 8     10/03/12 9:27p Barretlin
// [TAG]  		EIP N/A
// [Category]  	Improvement
// [Description]  	Change Programming security level timing for saving
// boot time
// [Files]  		TbtPei.c TbtDxe.c TbtOemBoard.h TbtOemLib.c TbtOemLib.h
// 
// 7     5/21/12 2:56a Barretlin
// [TAG]  		EIP90334
// [Category]  	Improvement
// [Description]  	Implement security level function on CRB
// [Files]  		TbtOemLib.c
// 
// 6     4/14/12 4:58a Barretlin
// 
// 5     3/05/12 1:16a Barretlin
// [TAG]  		EIP83266
// [Category]  	Spec Update
// [Description]  	Specificatoin Update 0.90
// [Files]  		TbtSetup.sdl
// TbtSetup.sd
// TbtSetup.uni
// TbtSetup.cif
// TbtOemBoard.h
// TbtOemLib.c
// TbtOemLib.h
// TbtSmm.c
// TbtPei..
// 
// 3     2/20/12 4:50a Wesleychen
// [TAG]         None
// [Category]    Improvement
// [Description] Add TbtOemLib.
// [Files]       TbtOemLib.c; TbtOemLib.h; TbtOemBoard,mak;
//               TbtOemBoard.cif.
// 
//*************************************************************************
#include <Efi.h>
#include <token.h>
#include <AmiLib.h>
#include <AmiDxeLib.h>
#include <AmiCspLib.h>

// Sample code for ITE8728F
/*
VOID SetSioLdn( IN UINT8 Ldn)
{
    IoWrite8(0x2e, Ldn);
    IoWrite8(0x2f, Ldn);
}

UINT8 ReadSio( IN UINT8 Index )
{
    IoWrite8(0x2e, Index);
    return IoRead8(0x2f);
}

VOID WriteSio( IN UINT8 Index, IN UINT8 Value )
{
    IoWrite8(0x2e, Index);
    IoWrite8(0x2f, Value);
}

VOID SetSio( IN UINT8 Index, IN UINT8 Set )
{
    UINT8 Data8;

    IoWrite8(0x2e, Index);
    Data8 = IoRead8(0x2f);
    Data8 |= Set;
    IoWrite8(0x2f, Data8);
}

VOID ResetSio( IN UINT8 Index, IN UINT8 Rst )
{
    UINT8 Data8;

    IoWrite8(0x2e, Index);
    Data8 = IoRead8(0x2f);
    Data8 &= ~Rst;
    IoWrite8(0x2f, Data8);
}

VOID OpenSioConfig ( VOID ) 
{
    IoWrite8(0x2e, 0x87);
    IoWrite8(0x2e, 0x01);
    IoWrite8(0x2e, 0x55);
    IoWrite8(0x2e, 0x55);
}
//*/

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   TbtSetPCIe2TBTCommand
//
// Description: This snipped code contains PCIE2TBT <-> TBT2PCIE handshake 
//              procedure and all related methods called directly or underectly 
//              by TbtSetPCIe2TBTCommand.
//              This function is Intel Sample code(Rev. 1.5).
//
// Input:       UINT8 - UpPortBus
//              UINT8 - Data
//              UINT8 - Command
//              UINTN - Timeout
//
// Output:      BOOLEAN
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN TbtSetPCIe2TBTCommand(
    IN UINT8             UpPortBus,
    IN UINT8             Data,
    IN UINT8             Command,
    IN UINTN             Timeout
)
{
    UINT32 REG_VAL = 0;
    UINTN  Counter = Timeout;
    
    REG_VAL = (Data << 8) | (Command << 1) | PCIE2TBT_VLD_B;
    
    WRITE_PCI32(UpPortBus, 0, 0, RR_PCIE2TBT, REG_VAL);
    
    while(Counter-- > 0){
        // BIOS support of Thunderbolt devices Specification Update Revision 0.9
        // Check Classcode, RevID
        REG_VAL = MMIO_READ32(TBT_CFG_ADDRESS(UpPortBus, 0, 0, PCI_RID));
        if (0xFFFFFFFF == REG_VAL){
            // Device is not here return now
            return FALSE;
        }
    
        // Check TBT2PCIE.Done
        REG_VAL = MMIO_READ32(TBT_CFG_ADDRESS(UpPortBus, 0, 0, RR_TBT2PCIE));
        if (REG_VAL & TBT2PCIE_DON_R){
            break;
        }
    }
    WRITE_PCI32(UpPortBus, 0, 0, RR_PCIE2TBT, 0);
    
    return TRUE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   TbtBeforeSxExitFlow
//
// Description: 
//              
//
// Input:       EFI_PEI_SERVICES - **PeiServices
//              UINT8            - TbtHostSeries
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID TbtBeforeSxExitFlow(
    IN VOID              *Services,
    IN UINT8             TbtHostSeries )
{
// Sample code for CRB
/*
    EFI_PEI_SERVICES    **PeiServices;
    UINT16      GPIOInv;
#if !defined BWT2_BOARD || BWT2_BOARD == 0
    UINT8       Data8;
#else
    UINT32      Data32;
#endif

    PeiServices = (EFI_PEI_SERVICES **)Services;

    if (TbtHostSeries == Cactus_Ridge){
        // only for SharkBay CRB
        GPIOInv = (IoRead16(GPIO_BASE_ADDRESS + GP_IOREG_GPI_INV) & 0xF7FF);
        IoWrite16(GPIO_BASE_ADDRESS + GP_IOREG_GPI_INV, GPIOInv);
    }

#if !defined BWT2_BOARD || BWT2_BOARD == 0
    OpenSioConfig();
    SetSioLdn (0x07);
    
    //program Super IO Base Address
    WriteSio(0x62, (UINT8)(IT8728_GPIO_BASE_ADDRESS >> 8));
    WriteSio(0x63, (UINT8)(IT8728_GPIO_BASE_ADDRESS & 0xFF));

    //program GP20, GP21, GP22 as GPIO pin
    Data8 = ReadSio (0x26);
    Data8 |= 0x07;
    WriteSio (0x26, Data8);
    
    if (TbtHostSeries == Cactus_Ridge){
#if defined (TBT_HR_PWR) && (TBT_HR_PWR != 0xFF)
        //program GP40 as GPIO pin
        Data8 = ReadSio (0x28);
        Data8 |= 0x01;
        WriteSio (0x28, Data8);
#endif
        
        //program GP66, GP67 as GPIO pin
        Data8 = ReadSio (0x29);
        Data8 |= BIT07;
        WriteSio (0x29, Data8);
    } // Cactus Ridge
    
    //program GP20, GP21, GP22 GPIO polarity
    Data8 = ReadSio (0xB1);
    Data8 &= 0xF8;
    WriteSio (0xB1, Data8);
    
#if defined (TBT_HR_PWR) && (TBT_HR_PWR != 0xFF)
    if (TbtHostSeries == Cactus_Ridge){
        //program GP40 GPIO polarity
        Data8 = ReadSio (0xB3);
        Data8 &= 0xFE;
        WriteSio (0xB3, Data8);
    }
#endif
    
    //GP20, GP21, GP22 internal pull-up enable
    Data8 = ReadSio (0xB9);
    Data8 |= 0x03;
    WriteSio (0xB9, Data8);
    
    if (TbtHostSeries == Cactus_Ridge){
#if defined (TBT_HR_PWR) && (TBT_HR_PWR != 0xFF)
        //GP40 internal internal pull-up enable
        Data8 = ReadSio (0xBB);
        Data8 |= 0x01;
        WriteSio (0xBB, Data8);
#endif
     
        //GP66, GP67 internal pull-up enable
        Data8 = ReadSio (0xBD);
        Data8 |= 0xC0;
        WriteSio (0xBD, Data8);
    }
    
    //GP20, GP21, GP22 Simple I/O enable
    Data8 = ReadSio (0xC1);
    Data8 |= 0x07;
    WriteSio (0xC1, Data8);
     
#if defined (TBT_HR_PWR) && (TBT_HR_PWR != 0xFF)
    if (TbtHostSeries == Cactus_Ridge){
        //GP40 Simple I/O enable
        Data8 = ReadSio (0xC3);
        Data8 |= 0x01;
        WriteSio (0xC3, Data8);
    }
#endif
     
    //GP20, GP21, GP22 Input/Output Configure
    //1:Output Mode 0:Input Mode
    Data8 = ReadSio (0xC9);
    Data8 |= 0x03;
    WriteSio (0xC9, Data8);
    
    if (TbtHostSeries == Cactus_Ridge){
#if defined (TBT_HR_PWR) && (TBT_HR_PWR != 0xFF)
        //GP40 Input/Output Configure
        //1:Output Mode 0:Input Mode
        Data8 = ReadSio (0xCB);
        Data8 |= 0x01;
        WriteSio (0xCB, Data8);
#endif
        
        //GP66, GP67 Input/Output Configure
        //1:Output Mode 0:Input Mode
        Data8 = ReadSio (0xCD);
        Data8 |= 0xC0;
        WriteSio (0xCD, Data8);
    }
    
    if (TbtHostSeries != Cactus_Ridge){
        //Pull high GPIO_9
        IoWrite8(IT8728_GPIO_BASE_ADDRESS + 1, 0x04);
    } // RR, FR and WR
#else
    // program ownship
    //Data32 = IoRead32(GPIO_BASE_ADDRESS + (TBT_HotPlugEvt/32)*4);
    //Data32 |= (BIT00 << (TBT_ForcePWR%32));
    //IoWrite32((GPIO_BASE_ADDRESS + (TBT_HotPlugEvt/32)*4), Data32);
    
    //Data32 = IoRead32(GPIO_BASE_ADDRESS + (TBT_HotPlugEvt/32)*4);
    //Data32 &= ~(BIT00 << (TBT_HotPlugEvt%32));
    //IoWrite32((GPIO_BASE_ADDRESS + (TBT_HotPlugEvt/32)*4), Data32);
    
    // program GPIO pin setting
    // TBT_ForcePWR is GPIO, is Output, is Level mode
    //Data32 = (BIT00 | BIT04) & (~BIT02);
    //IoWrite32((GPIO_BASE_ADDRESS + 0x100 + (TBT_ForcePWR * 8)), Data32);
    
    // TBT_HotPlugEvt is GPIO, is input, need invert, is Edge mode
    //Data32 = (BIT00 | BIT02 | BIT03) & (~BIT04);
    //IoWrite32((GPIO_BASE_ADDRESS + 0x100 + (TBT_HotPlugEvt * 8)), Data32);
#endif
//*/
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   GetHRInfo
//
// Description: Pull High GPIO_3 and assign temp bus to get Thunderbolt Host
//              Chip Series for distinguishing Thunderbolt host is Cactus Ridge 
//              or Redwood Ridge
//
//              If your case is only support Redwood Ridge or only support Cactus
//              Ridge, you can just return Thunderbolt Host number which is defined
//              in TbtOemBoard.h
//
//              According test result, the dynamic detect Thunderbolt HR series
//              still has fail rate, so we don't suggest you using the same way
//              to decide HR series. sample code is just for testing !!!
//
// Input:       None
//
// Output:      UINT8 - Thunderbolt Host chip Series
//                      1 - Cactus Ridge
//                      2 - Redwood Ridge
//                      3 - Falcon Ridge
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8 GetHRInfo( VOID )
{
    UINT8        TBTHostSeries = DEFAULT_TBT_CHIP;
// Sample code for ITE8728F and WTM2
/*
#if !defined BWT2_BOARD || BWT2_BOARD == 0
    UINT8        Data8;
#else
    UINT32       Data32;
#endif
    UINT16       HRID;
    UINT32       REG_VAL = 0;
    BOOLEAN      RRCmd = FALSE;

#if !defined BWT2_BOARD || BWT2_BOARD == 0  
    OpenSioConfig();
    
    SetSioLdn(0x07);
    
    if(ReadSio (0x62) == 0x00){
        //program Super IO Base Address
        WriteSio(0x62, (UINT8)(IT8728_GPIO_BASE_ADDRESS >> 8));
        WriteSio(0x63, (UINT8)(IT8728_GPIO_BASE_ADDRESS & 0xFF));
    }
    
    //program GP21 as GPIO pin
    Data8 = ReadSio (0x26);
    Data8 |= 0x02;
    WriteSio (0x26, Data8);
    
    //program GP21 GPIO polarity
    Data8 = ReadSio (0xB1);
    Data8 &= 0xFD;
    WriteSio (0xB1, Data8);
    
    //program GP21 internal pull-up enable
    Data8 = ReadSio (0xB9);
    Data8 |= 0x02;
    WriteSio (0xB9, Data8);
    
    //program GP21 Simple I/O enable
    Data8 = ReadSio (0xC1);
    Data8 |= 0x02;
    WriteSio (0xC1, Data8);
    
    //program GP21 Input/Output Configure
    //1:Output Mode 0:Input Mode
    Data8 = ReadSio (0xC9);
    Data8 |= 0x02;
    WriteSio (0xC9, Data8);
#else
#endif
    
    // Assign temp bus
    WRITE_PCI16(TBT_UP_PORT_BUS, TBT_UP_PORT_DEV, TBT_UP_PORT_FUNC, PCI_PBUS+1, 0x0505);
    // Do a dummy Write
    WRITE_PCI32(5, 0, 0, PCI_VID, 0x12345678);
    
    // Pull High GPIO_3(__FORCE_PWR)
#if !defined BWT2_BOARD || BWT2_BOARD == 0
    Data8 = IoRead8(IT8728_GPIO_BASE_ADDRESS + 1);
    Data8 |= 0x02;
    IoWrite8(IT8728_GPIO_BASE_ADDRESS + 1, Data8);
#else
    Data32 = IoRead32((GPIO_BASE_ADDRESS + 0x100 + (TBT_ForcePWR * 8)));
    Data32 |= BIT31;
    IoWrite32((GPIO_BASE_ADDRESS + 0x100 + (TBT_ForcePWR * 8)), Data32);
#endif

    // Delay 100 ms
    CountTime(100000, PM_BASE_ADDRESS);
    
    //Write OS_UP commond for RR chip
    TbtSetPCIe2TBTCommand(5, 0, TBT_OS_UP, 0x8FFFF);
    
    // Delay 600 ms
    CountTime(600000, PM_BASE_ADDRESS);
    
    // Get HR Info
    HRID = READ_PCI16(5, 0, 0, PCI_DID);
    switch (HRID){
        case 0x1547: // Cactus Ridge 4C
        case 0x1548: // Cactus Ridge 2C
            TBTHostSeries = Cactus_Ridge;
            break;
        
        case 0x1567: // Redwood Ridge 2C
        case 0x1569: // Redwood Ridge 4C
        case 0x156B: // Falcon Ridge 2C
        case 0x156D: // Falcon Ridge 4C
        case 0x157E: // BDW-TBT-LP(WR)
        default:
            if ((HRID == 0x1567) || (HRID == 0x1569)){
                TBTHostSeries = Redwood_Ridge;
            } else if ((HRID == 0x156B) || (HRID == 0x156D)){
                TBTHostSeries = Falcon_Ridge;
            } else {
                TBTHostSeries = BDW_TBT_LP;
            }
            
            // Reset FW's security level for RR chip, only for FW rev.26 or above.
            TbtSetPCIe2TBTCommand(5, 0, TBT_SET_SECURITY_LEVEL, 0x8FFFF);
            // Delay 100 ms
            CountTime(100000, PM_BASE_ADDRESS);
    } // end switch

    // Pull Low GPIO_3(__FORCE_PWR)
#if !defined BWT2_BOARD || BWT2_BOARD == 0
    Data8 = IoRead8(IT8728_GPIO_BASE_ADDRESS + 1);
    Data8 &= 0xFD;
    IoWrite8(IT8728_GPIO_BASE_ADDRESS + 1, Data8);
#else
    Data32 = IoRead32((GPIO_BASE_ADDRESS + 0x100 + (TBT_ForcePWR * 8)));
    Data32 &= ~BIT31;
    IoWrite32((GPIO_BASE_ADDRESS + 0x100 + (TBT_ForcePWR * 8)), Data32);
#endif
    
    // Delay 100 ms
    CountTime(100000, PM_BASE_ADDRESS);
    
    // Remove temp bus
    WRITE_PCI32(TBT_UP_PORT_BUS, TBT_UP_PORT_DEV, TBT_UP_PORT_FUNC, PCI_PBUS, 0xFF000000);
//*/
    return TBTHostSeries;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SynchSecurityLevel
//
// Description: When entering Setup page, double check Security Level setting  
//              is same or not between Thunderbolt host Fw and BIOS.
//
//              This function only work for Thunderbolt Redwood Ridge chip
//
// Input:       UINT8           BiosSecurityLevel
//              UINT8           TbtHostLocation
//
// Output:      UINT8           0 - Security Level synchnized without change
//                              1 - Security Level synchnized with programming
//                                  again
//                              2 - Error
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8 SynchSecurityLevel(
    IN UINT8             BiosSecurityLevel,
    IN UINT8             TbtHostLocation
)
{
    UINT8            SynchState = 0;
// Sample code for ITE8728F and WTM2
/*
    UINT8            TbtHRbus;
    UINT8            PWRFlag = 0;
    UINT8            TBus = TBT_UP_PORT_BUS;
    UINT8            TDev = TBT_UP_PORT_DEV;
    UINT8            TFun = TBT_UP_PORT_FUNC;
#if !defined BWT2_BOARD || BWT2_BOARD == 0
    UINT8            Data8;
#else
    UINT32           Data32;
#endif
    UINT32           RegVal;
    BOOLEAN          CmdDone;

    if (TbtHostLocation < 0x20){
        TFun = TbtHostLocation;
    } else {
        TDev = 0x01;
        TFun = TbtHostLocation - 0x20;
    }

    // Get Thunderbolt Host Router Location
    TbtHRbus = READ_PCI8(TBus, TDev, TFun, PCI_SBUS);

    // Check Thunderbolt Host state
    RegVal = MMIO_READ32(TBT_CFG_ADDRESS(TbtHRbus, 0, 0, PCI_RID));
    if (RegVal == 0xFFFFFFFF){
        // Pull high GPIO_3(__FORCE_PWR) pin
#if !defined BWT2_BOARD || BWT2_BOARD == 0
        Data8 = IoRead8(IT8728_GPIO_BASE_ADDRESS + 1);
        Data8 |= 0x02;
        IoWrite8(IT8728_GPIO_BASE_ADDRESS + 1, Data8);
#else
        Data32 = IoRead32((GPIO_BASE_ADDRESS + 0x100 + (TBT_ForcePWR * 8)));
        Data32 |= BIT31;
        IoWrite32((GPIO_BASE_ADDRESS + 0x100 + (TBT_ForcePWR * 8)), Data32);
#endif
    
        // Delay 50ms
        CountTime(50000, PM_BASE_ADDRESS);
        PWRFlag = 1;
    }
    
    // Do Redwood Ridge handshake to get Thunderbolt FW security level 
    CmdDone = TbtSetPCIe2TBTCommand(TbtHRbus, 0, TBT_GET_SECURITY_LEVEL, 0x008FFFFF);
    
    if (CmdDone){
        RegVal = READ_PCI32(TbtHRbus, 0, 0, RR_TBT2PCIE);

        if ((RegVal & MASK_ERROR) == 0){
            RegVal = (RegVal & MASK_DATA) >> 8;
        }
        else SynchState = 2;
    } else SynchState = 2;
    // So far, RegVal variable might be:
    // 1: 0xFFFFFFFF
    // 2: Thunderbolt host Revision ID and Class Code
    // 3: Thunderbolt host Fw security level setting

    // check Security Level setting between Thunderbolt Fw and BIOS
    if ((UINT8)RegVal != (BiosSecurityLevel - 1)){ 
        if (PWRFlag == 0){
            // Pull high GPIO_3(__FORCE_PWR) pin
#if !defined BWT2_BOARD || BWT2_BOARD == 0
            Data8 = IoRead8(IT8728_GPIO_BASE_ADDRESS + 1);
            Data8 |= 0x02;
            IoWrite8(IT8728_GPIO_BASE_ADDRESS + 1, Data8);
#else
            Data32 = IoRead32((GPIO_BASE_ADDRESS + 0x100 + (TBT_ForcePWR * 8)));
            Data32 |= BIT31;
            IoWrite32((GPIO_BASE_ADDRESS + 0x100 + (TBT_ForcePWR * 8)), Data32);
#endif

            PWRFlag = 1;
        }
        IoWrite8(0x80, (BiosSecurityLevel - 1 + 0xC0));
        // After testing, TBT Fw needs Delay 600ms
        CountTime(600000, PM_BASE_ADDRESS);
        
        // Re-config Security Level with BIOS setting
        CmdDone = TbtSetPCIe2TBTCommand(TbtHRbus, (BiosSecurityLevel - 1), TBT_SET_SECURITY_LEVEL, 0x008FFFFF);

        if (CmdDone)  SynchState = 1;
        else SynchState = 2;
    }
    
    if (PWRFlag == 1){
        // Pull low GPIO_3(__FORCE_PWR) pin
#if !defined BWT2_BOARD || BWT2_BOARD == 0
        Data8 = IoRead8(IT8728_GPIO_BASE_ADDRESS + 1);
        Data8 &= 0xFD;
        IoWrite8(IT8728_GPIO_BASE_ADDRESS + 1, Data8);
#else
        Data32 = IoRead32((GPIO_BASE_ADDRESS + 0x100 + (TBT_ForcePWR * 8)));
        Data32 &= (~BIT31);
        IoWrite32((GPIO_BASE_ADDRESS + 0x100 + (TBT_ForcePWR * 8)), Data32);
#endif

        // Delay 100ms
        CountTime(100000, PM_BASE_ADDRESS);
    }
//*/
    return SynchState;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   ProgramTbtSecurityLevel
//
// Description: This function is configure the Thunderbolt security level.
//              OEM Porting required !!!.
//
// Input:       UINT8           TbtSecurityLevel
//              UINT8           TBTHostSeries
//              UINT8           TbtHostLocation
//              BOOLEAN         IsPei
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID ProgramTbtSecurityLevel(
    IN UINT8             *TbtSecurityLevel,
    IN UINT8             TbtHostSeries,
    IN UINT8             TbtHostLocation,
    IN BOOLEAN           IsPei
)
{
// Sample code for ITE8728F and WTM2
/*
#if !defined BWT2_BOARD || BWT2_BOARD == 0
    UINT8               Data8    = 0;
#else
    UINT32              Data32   = 0;
#endif
    UINT8               SecLevel = *TbtSecurityLevel;
    UINT8               TbtHRbus;
    BOOLEAN             RRCmd    = FALSE;
    UINT8               TBus     = TBT_UP_PORT_BUS;
    UINT8               TDev     = TBT_UP_PORT_DEV;
    UINT8               TFun     = TBT_UP_PORT_FUNC;

#if !defined BWT2_BOARD || BWT2_BOARD == 0
    if (TbtHostSeries == Cactus_Ridge){
        // For Cactus Ridge chip
#if defined (TBT_HR_PWR) && (TBT_HR_PWR != 0xFF)
        Data8 = IoRead8(IT8728_GPIO_BASE_ADDRESS + 3);
        if (SecLevel == TBT_OFF_MODE){
            Data8 &= 0xFE;
            IoWrite8(IT8728_GPIO_BASE_ADDRESS + 3, Data8);
            return;
        }
        if (!(Data8 & BIT0)){
            Data8 |= 0x01;
            IoWrite8(IT8728_GPIO_BASE_ADDRESS + 3, Data8);
        }
#else
        if (SecLevel == TBT_OFF_MODE) return;
#endif
        
        Data8 = IoRead8(IT8728_GPIO_BASE_ADDRESS + 5);
        Data8 &= ~(BIT6 | BIT7);
        
        switch (SecLevel)
        {
            case TBT_DIRECT_CONNECTED_WO_NHI:
                Data8 |= BIT6;
                break;
            
            case TBT_REDRIVER_ONLY:
                Data8 |= BIT7;
                break;
            
            case TBT_NORMAL_MODE_WO_NHI:
                break;
            
            case TBT_NORMAL_MODE:
            case TBT_DEBUG_MODE:
            default:
                // Normal mode with NHI.
                Data8 |= (BIT6 | BIT7);
                break;
        } // end of switch

        // Set GP66 and GP67
        IoWrite8(IT8728_GPIO_BASE_ADDRESS + 5, Data8);
        
        // Set GPIO6 and GPIO7 to the desired levels and
        // assert GPIO3 for at least 400ms period.
        // GP21 Pull high
        Data8 = IoRead8(IT8728_GPIO_BASE_ADDRESS + 1);
        Data8 |= 0x02;
        IoWrite8(IT8728_GPIO_BASE_ADDRESS + 1, Data8);
    } else {
        // For Redwood Ridge / Falcon Ridge / Win Ridge chip
        if (IsPei != TRUE){
            if(TbtHostLocation < 0x20){
                TFun = TbtHostLocation;
            } else {
                TDev = 0x01;
                TFun = TbtHostLocation - 0x20;
            }
            
            // Get Thunderbolt Host Router Location
            TbtHRbus = READ_PCI8(TBus, TDev, TFun, PCI_SBUS);
            
            // First pull high GPIO_3(__FORCE_PWR) pin
            Data8 = IoRead8(IT8728_GPIO_BASE_ADDRESS + 1);
            Data8 |= 0x02;
            IoWrite8(IT8728_GPIO_BASE_ADDRESS + 1, Data8);

            IoWrite8(0x80, (0x80 | (SecLevel - 1)));
            CountTime(500000, PM_BASE_ADDRESS);
            
            // Do PCIE2TBT handshake
            RRCmd = TbtSetPCIe2TBTCommand(TbtHRbus, (SecLevel - 1), TBT_SET_SECURITY_LEVEL, 0x008FFFFF);
            if(RRCmd){
                IoWrite8(0x80, 0x5D);
                CountTime(100000, PM_BASE_ADDRESS);
            }

            // Finial pull low GPIO_3(__FORCE_PWR) pin
            Data8 = IoRead8(IT8728_GPIO_BASE_ADDRESS + 1);
            Data8 &= 0xFD;
            IoWrite8(IT8728_GPIO_BASE_ADDRESS + 1, Data8);
        } // is not at PEI phase
    }
#else
    if (IsPei != TRUE){
        if (TbtHostLocation < 20){
            TFun = TbtHostLocation;
        } else {
            TDev = 0x01;
            TFun = TbtHostLocation - 0x20;
        }
     
        //Get Thunderbolt Host Router Location
        TbtHRbus = READ_PCI8(TBus, TDev, TFun, PCI_SBUS);
        
        // First pull high GPIO_3(__FORCE_PWR) pin
        Data32 = IoRead32((GPIO_BASE_ADDRESS + 0x100 + (TBT_ForcePWR * 8)));
        Data32 |= BIT31;
        IoWrite32((GPIO_BASE_ADDRESS + 0x100 + (TBT_ForcePWR * 8)), Data32);
        
        IoWrite8(0x80, (0x80 | (SecLevel - 1)));
        CountTime(500000, PM_BASE_ADDRESS);
        
        // Do PCIE2TBT handshake
        RRCmd = TbtSetPCIe2TBTCommand(TbtHRbus, (SecLevel - 1), TBT_SET_SECURITY_LEVEL, 0x008FFFFF);
        
        //for debug
        if(RRCmd){
            IoWrite8(0x80, 0x5D);
            CountTime(100000, PM_BASE_ADDRESS);
        }
     
        // finial pull low GPIO_3(__FORCE_PWR) pin
        Data32 = IoRead32((GPIO_BASE_ADDRESS + 0x100 + (TBT_ForcePWR * 8)));
        Data32 &= ~BIT31;
        IoWrite32((GPIO_BASE_ADDRESS + 0x100 + (TBT_ForcePWR * 8)), Data32);
    }
#endif
//*/
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   PeiFinialProgramTbtSecurityLevel
//
// Description: if system does not support "Wake from Thunderbolt device" 
//              function, BIOS should depend on Security Level and BootMod to 
//              pull low FORCE_PWR pin or not in PEI phase
//
//              This function only work for Thunderbolt Cactus Ridge chip and 
//              system doesn't support wake up from Thunderbolt Device
//
// Input:       UINT8           TbtSecurityLevel
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID PeiFinialProgramTbtSecurityLevel(
    IN UINT8             TbtSecurityLevel
)
{
// Sample code for ITE8728F
/*
#if !defined BWT2_BOARD || BWT2_BOARD == 0
    UINT8 Data8;
    UINT8 SecLevel = TbtSecurityLevel;

    OpenSioConfig();
    SetSioLdn (0x07);
    if(ReadSio (0x62) == 0x00){
        //program Super IO Base Address
        WriteSio(0x62, (UINT8)(IT8728_GPIO_BASE_ADDRESS >> 8));
        WriteSio(0x63, (UINT8)(IT8728_GPIO_BASE_ADDRESS & 0xFF));
    }
    
    //The 400 ms delay has been done in TbtPei.c
    //So just pull low GPIO_3(__FORCE_PWR) pin without any delay
    if (SecLevel <= 4) {
        Data8 = IoRead8(IT8728_GPIO_BASE_ADDRESS + 1);
        Data8 &= 0xFD;
        IoWrite8(IT8728_GPIO_BASE_ADDRESS + 1, Data8);
    }
#endif
//*/
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   FinialProgramTbtSecurityLevel
//
// Description: BIOS should depend on Security Level to pull low FORCE_PWR pin
//              or not
//
//              This function only work for Thunderbolt Cactus Ridge chip
//
// Input:       AMI_TBT_PLATFORM_POLICY_PROTOCOL *PlatformPolocy
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID FinialProgramTbtSecurityLevel(
    IN AMI_TBT_PLATFORM_POLICY_PROTOCOL *PlatformPolocy
)
{
// Sample code for ITE8728F
/*
#if !defined BWT2_BOARD || BWT2_BOARD == 0
    UINT8 Data8;
    UINT8 SecLevel = PlatformPolocy->TbtSecurityLevel;
    
    OpenSioConfig();
    SetSioLdn (0x07);
    if(ReadSio (0x62) == 0x00){
        //program Super IO Base Address
        WriteSio(0x62, (UINT8)(IT8728_GPIO_BASE_ADDRESS >> 8));
        WriteSio(0x63, (UINT8)(IT8728_GPIO_BASE_ADDRESS & 0xFF));
    }
    
    if (SecLevel <= 4) {
        Data8 = IoRead8(IT8728_GPIO_BASE_ADDRESS + 1);
        Data8 &= 0xFD;
        IoWrite8(IT8728_GPIO_BASE_ADDRESS + 1, Data8);
    }
#endif
//*/
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   ActiveTbtGpio2
//
// Description: BIOS should assert GO2Sx pin
//              That will trigger Host Router to prepare underlying devices
//              For Thunderbolt host is CR chip
//
//              This function only work for Thunderbolt Cactus Ridge chip 
//
// Input:       None
//
// Output:      EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ActiveTbtGpio2 ( VOID )
{
// Sample code for ITE8728F
/*
#if !defined BWT2_BOARD || BWT2_BOARD == 0
    UINT8 Data8;

    OpenSioConfig();

    SetSioLdn(0x07);
    if(ReadSio (0x62) == 0x00){
        //program Super IO Base Address
        WriteSio(0x62, (UINT8)(IT8728_GPIO_BASE_ADDRESS >> 8));
        WriteSio(0x63, (UINT8)(IT8728_GPIO_BASE_ADDRESS & 0xFF));
    }
    
    Data8 = IoRead8(IT8728_GPIO_BASE_ADDRESS + 1);
    Data8 |= BIT0;
    IoWrite8(IT8728_GPIO_BASE_ADDRESS + 1, Data8);
#endif
//*/
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   InactiveTbtGpio2
//
// Description: BIOS should deassert GO2Sx pin
//              That will trigger Host Router to prepare underlying devices
//
//              This function only work for Thunderbolt Cactus Ridge chip
//
// Input:       None
//
// Output:      EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS InactiveTbtGpio2 ( VOID )
{
// Sample code for ITE8728F
/*
#if !defined BWT2_BOARD || BWT2_BOARD == 0
    UINT8 Data8;
    
    OpenSioConfig();
    
    SetSioLdn(0x07);
    if(ReadSio (0x62) == 0x00){
        //program Super IO Base Address
        WriteSio(0x62, (UINT8)(IT8728_GPIO_BASE_ADDRESS >> 8));
        WriteSio(0x63, (UINT8)(IT8728_GPIO_BASE_ADDRESS & 0xFF));
    }
  
    Data8 = IoRead8(IT8728_GPIO_BASE_ADDRESS + 1);
    Data8 &= 0xFE;
    IoWrite8(IT8728_GPIO_BASE_ADDRESS + 1, Data8);
#endif
//*/
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   PollTbtGpio9
//
// Description: BIOS should poll OK2GO2SX_N_OD pin
//              Upon completion of all preparations, Host Router will assert
//              this pin to indicate readiness for Sx entry.
//
//              This function only work for Thunderbolt Cactus Ridge chip
//
// Input:       None
//
// Output:      EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PollTbtGpio9 ( VOID )
{
// Sample code for ITE8728F
/*
#if !defined BWT2_BOARD || BWT2_BOARD == 0
    UINT32 counter = 0;
    
    while(IoRead8(IT8728_GPIO_BASE_ADDRESS + 1) & BIT2){
        if (counter == 0x008FFFFF) break;
            counter++;
    }
#endif
//*/
    return EFI_SUCCESS;
};

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   PullDownTbtGpio9
//
// Description: BIOS should pull down OK2GO2SX_N_OD pin in Wake flow
//              if remebered Host Router state was active.
//
//              This function only work for Thunderbolt Cactus Ridge chip and 
//              system doesn't support wake up from Thunderbolt Device
//
// Input:       None
//
// Output:      EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PullDownTbtGpio9 ( VOID )
{
// Sample code for ITE8728F
/*
#if !defined BWT2_BOARD || BWT2_BOARD == 0
    UINT8 Data8;
    
    OpenSioConfig();
    
    SetSioLdn(0x07);
    
    if(ReadSio (0x62) == 0x00){
        //program Super IO Base Address
        WriteSio(0x62, (UINT8)(IT8728_GPIO_BASE_ADDRESS >> 8));
        WriteSio(0x63, (UINT8)(IT8728_GPIO_BASE_ADDRESS & 0xFF));
    }
    
    //program GP22 as GPIO pin
    Data8 = ReadSio (0x26);
    Data8 |= 0x04;
    WriteSio (0x26, Data8);
    
    //program GP22 GPIO polarity
    Data8 = ReadSio (0xB1);
    Data8 &= 0xF8;
    WriteSio (0xB1, Data8);
    
    //program GP22 internal pull-up enable
    Data8 = ReadSio (0xB9);
    Data8 |= 0x04;
    WriteSio (0xB9, Data8);
    
    //program GP22 Simple I/O enable
    Data8 = ReadSio (0xC1);
    Data8 |= 0x04;
    WriteSio (0xC1, Data8);
    
    //program GP22 Input/Output Configure
    //1:Output Mode 0:Input Mode
    Data8 = ReadSio (0xC9);
    Data8 |= 0x04;
    WriteSio (0xC9, Data8);
    
    Data8 = IoRead8(IT8728_GPIO_BASE_ADDRESS + 1);
    Data8 &= 0xFB;
    IoWrite8(IT8728_GPIO_BASE_ADDRESS + 1, Data8);
#endif
//*/
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   ReleaseTbtGpio9
//
// Description: BIOS should release pull down OK2GO2SX_N_OD pin in Wake flow
//              if remebered Host Router state was active
//
//              This function only work for Thunderbolt Cactus Ridge chip and 
//              system doesn't support wake up from Thunderbolt Device
//
// Input:       None
//
// Output:      EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ReleaseTbtGpio9 ( VOID )
{
// Sample code for ITE8728F
/*
#if !defined BWT2_BOARD || BWT2_BOARD == 0
    UINT8 Data8;
    
    OpenSioConfig();
    
    SetSioLdn(0x07);
    
    //program GP22 Input/Output Configure
    //1:Output Mode 0:Input Mode
    Data8 = ReadSio (0xC9);
    Data8 &= 0xFB;
    WriteSio (0xC9, Data8);
#endif
//*/
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   PowerOnPOC
//
// Description: Power on POC to wake up thunderbolt
//
//              This function is optional and only work for Thunderbolt Cactus 
//              Ridge chip and system doesn't support wake up from Thunderbolt 
//              Device.
//
// Input:       None
//
// Output:      EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PowerOnPOC ( VOID )
{
// Sample code for ITE8728F
/*
#if !defined BWT2_BOARD || BWT2_BOARD == 0
    UINT8 Data8;
    
    OpenSioConfig();
    SetSioLdn(0x07);
    
    if(ReadSio (0x62) == 0x00){
        //program Super IO Base Address
        WriteSio(0x62, (UINT8)(IT8728_GPIO_BASE_ADDRESS >> 8));
        WriteSio(0x63, (UINT8)(IT8728_GPIO_BASE_ADDRESS & 0xFF));
    }

    //program GP40 as GPIO pin
    Data8 = ReadSio (0x28);
    Data8 |= 0x01;
    WriteSio (0x28, Data8);
    
    //program GP40 GPIO polarity
    Data8 = ReadSio (0xB3);
    Data8 &= 0xFE;
    WriteSio (0xB3, Data8);
    
    //GP40 internal internal pull-up enable
    Data8 = ReadSio (0xBB);
    Data8 |= 0x01;
    WriteSio (0xBB, Data8);
    
    //GP40 Simple I/O enable
    Data8 = ReadSio (0xC3);
    Data8 |= 0x01;
    WriteSio (0xC3, Data8);
    
    //GP40 Input/Output Configure
    //1:Output Mode 0:Input Mode
    Data8 = ReadSio (0xCB);
    Data8 |= 0x01;
    WriteSio (0xCB, Data8);
    
    Data8 = IoRead8(IT8728_GPIO_BASE_ADDRESS + 3);
    if (!(Data8 & BIT0)){
        Data8 |= 0x01;
        IoWrite8(IT8728_GPIO_BASE_ADDRESS + 3, Data8);
    }
#endif
//*/
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   PowerOffPOC
//
// Description: Power off POC to cut off thunderbolt power 
//
//              This function is optional and only work for Thunderbolt Cactus 
//              Ridge chip and system doesn't support wake up from Thunderbolt 
//              Device.
//
// Input:       None
//
// Output:      EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PowerOffPOC ( VOID )
{
// Sample code for ITE8728F
/*
#if !defined BWT2_BOARD || BWT2_BOARD == 0
    UINT8 Data8;
    
    OpenSioConfig();
    SetSioLdn(0x07);
    
    if(ReadSio (0x62) == 0x00){
        //program Super IO Base Address
        WriteSio(0x62, (UINT8)(IT8728_GPIO_BASE_ADDRESS >> 8));
        WriteSio(0x63, (UINT8)(IT8728_GPIO_BASE_ADDRESS & 0xFF));
    }
  
    Data8 = IoRead8(IT8728_GPIO_BASE_ADDRESS + 3);
    Data8 &= 0xFE;
    IoWrite8(IT8728_GPIO_BASE_ADDRESS + 3, Data8);
#endif
//*/
    return EFI_SUCCESS;
}

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
