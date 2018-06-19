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
//
//*************************************************************************
// $Header: /Alaska/BIN/IO/Fintek/F81866/F81866DXE.C 3     2/03/12 2:02a Elviscai $
//
// $Revision: 3 $
//
// $Date: 2/03/12 2:02a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/IO/Fintek/F81866/F81866DXE.C $
// 
// 3     2/03/12 2:02a Elviscai
// [TAG]  		EIPNONE
// [Category]  	Bug Fix
// [Solution]  	Add WDT_INIT routine for WDT
// 
// 2     12/14/11 9:19p Kasalinyi
// [TAG]  		EIPNone
// [Category]  	Improvement
// [Description]  	Fix Smart Function build error
// [Files]  		F81866DXE.C
// F81866.UNI
// F81866.MAK
// IO_F81866.SDL
// 
// 1     7/20/11 4:22a Kasalinyi
// [Category]  	Improvement
// [Description]  	Initial Porting 
// [Files]  		F81866.CIF
// IO_F81866.SDL
// F81866.ASL
// F81866.MAK
// F81866.SD
// F81866.UNI
// F81866DXE.C
// F81866PEI.C
// F81866PeiDebugger.C
// F81866Setup.C
// F81866Setup.H
// History.txt
// F81866.chm
// 
// 4     3/21/11 9:41p Mikes
// seperate the core and oem job
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:  <F81866DXE.C>
//
// Description: 1. Port SIO DXE initial table and routine for genericsio.c
//              2. Define enter/exit config mode scrip table
//              3. Define SIO bootscriptable table
//
//<AMI_FHDR_END>
//*************************************************************************
//-------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------
#include <Efi.h>
#include <Token.h>
#include <GenericSIO.h>
#include <Setup.h>
#include <Protocol\AmiSio.h>
#include <Protocol\PciIo.h>
#include <AmiCspLib.h>
#include "BSP\DxeIoTable.h"

//-------------------------------------------------------------------------
// Constants, Macros and Type Definitions
//-------------------------------------------------------------------------
#define INITIAL_ROUTINE(name) \
static EFI_STATUS name(\
    IN    AMI_SIO_PROTOCOL     *AmiSio,\
    IN    EFI_PCI_IO_PROTOCOL  *PciIo,\
    IN    SIO_INIT_STEP        InitStep\
);

//-------------------------------------------------------------------------
//Variable, Prototype, and External Declarations
//-------------------------------------------------------------------------
EFI_BOOT_SCRIPT_SAVE_PROTOCOL * BootScriptProtocol = NULL;
#if (IODECODETYPE)
// SIO DECODE list creation code must be in this order
typedef EFI_STATUS (IO_RANGE_DECODE)(
//    IN  void            *LpcPciIo,
    IN EFI_PCI_IO_PROTOCOL      *LpcPciIo,
    IN  UINT16          DevBase, 
    IN  UINT8           UID, 
    IN  SIO_DEV_TYPE    Type
); 
extern IO_RANGE_DECODE  SIO_IoRange_Decode_LIST EndOfInitList;
static IO_RANGE_DECODE* CspIoRangeDecodeList[] = {SIO_IoRange_Decode_LIST NULL};
#endif //#if (IODECODETYPE)

extern VOID SioCfgMode(GSPIO *Sio, BOOLEAN Enter);
extern VOID DevSelect(SPIO_DEV *Dev);
extern VOID SioRegister(SPIO_DEV *Dev, BOOLEAN Write, UINT8 Reg, UINT8 *Val);

//smart fan
#if F81866_SMF_SUPPORT
extern VOID F81866SmartFunction(VOID);
#endif

EFI_STATUS LoopCspIoDecodeListInit(
    IN    EFI_PCI_IO_PROTOCOL *PciIo,
    IN    AMI_SIO_PROTOCOL    *AmiSio
);

VOID ProgramSioRegisterTable(
    IN  AMI_SIO_PROTOCOL    *AmiSio,
    IN  DXE_DEVICE_INIT_DATA *Table,
    IN  UINT8               Count
);

VOID ProgramIsaRegisterTable(
    IN  UINT16  Index,
    IN  UINT16  Data,
    IN  DXE_DEVICE_INIT_DATA *Table,
    IN  UINT8   Count
);

VOID ProgramRtRegisterTable(
    IN  UINT16  Base,
    IN  DXE_DEVICE_INIT_DATA  *Table,
    IN  UINT8   Count
);

VOID SaveSxSioRegisterTable(
    IN  UINT16  Index,
    IN  UINT16  Data,
    IN  UINT8   *Table,
    IN  UINT8   Count
);
VOID SaveSxRtRegisterTable(
    IN  UINT16  Base,
    IN  UINT16  *Table,
    IN  UINT8   Count
);
VOID ClearDevResource(
    IN    SPIO_DEV* dev
);
//Declare initial routines for your SPIO_DEV_LST list.
INITIAL_ROUTINE(FDC_Init)

INITIAL_ROUTINE(COM_Init)

INITIAL_ROUTINE(LPT_Init)

INITIAL_ROUTINE(KBC_Init)

INITIAL_ROUTINE(PME_Init)

INITIAL_ROUTINE(HWM_Init)

INITIAL_ROUTINE(GPIO_Init)

INITIAL_ROUTINE(WDT_Init)

//<AMI_THDR_START>
//-------------------------------------------------------------------------
//
// Name:        F81866_DevLst
//
// Description: Table filled with SIO porting information
//
//------------+-------+-------+--------+---------+---------+-------------+------------+------------+-----------+------------+------------+-------------|
//SIO_DEV_TYP | UINT8 | UINT8 | UINT16 | BOOLEAN | BOOLEAN | UINT8       | UINT8      | UINT16     | UINT16    | UINT16     | UINT8      | SIO_INIT    |
//Type        | LDN   | UID   | PnpId  | Impleme | HasSetu |   Flags     | AslName[5] | ResBase[2] | ResLen[2] | IrqMask[2] | DmaMask[2] | InitRoutine |
//------------+-------+-------+--------+---------+---------+-------------+------------+------------+-----------+------------+------------+-------------|
//  Field "Falgs" is needed to indicate that SIO Logical Device represented
//  by this table entry shares all or some resources with previous entry.
//  Such situation is sutable for FDC - and PS2 controller
//  This field must be filled properely in order to have driver working right.
//  Here possible Flags Settings
//  #define SIO_SHR_NONE    0x00
//  #define SIO_SHR_IO1     0x01 //device shares resources programmed in SIO_1_BASE_REG
//  #define SIO_SHR_IO2     0x02 //device shares resources programmed in SIO_2_BASE_REG    
//  #define SIO_SHR_IO      0x03 //device shares resources programmed in all SIO_BASE_REG
//  #define SIO_SHR_IRQ1    0x04
//  #define SIO_SHR_IRQ2    0x08
//  #define SIO_SHR_IRQ     0x0C
//  #define SIO_SHR_DMA1    0x10
//  #define SIO_SHR_DMA2    0x20
//  #define SIO_SHR_DMA     0x30
//  #define SIO_SHR_ALL     0x3F
//  #define SIO_NO_RES      0x80 //this bit will be set if GCD call to allocate resource succeed
//                               //at least one call must return SUCCESS if this flag
//
//-------------------------------------------------------------------------
//<AMI_THDR_END>
//AMI_TODO: Please check below notes.
//1. if device has no ASL code and has IO base register to be initialized, fill it in below table
//2. If device has no IO base register to be initialized, set flag to SIO_NO_RES
//3. if more device PnpId is 0x0C08, please check the UID of these devices.
static SPIO_DEV_LST F81866_DevLst[]={
//If device Implemented=FALSE the rest of the table will be ignored, just to avoid compilation ERROR
//Type      LDN               UID PnpId   Implement                     HasSetu  Share RES     AslName[5] Base   Length  IrqMask  DmaMask  InitRoutine
//===============================================================================
{dsFDC,   F81866_LDN_FDC,   0, 0x0604, F81866_FLOPPY_PORT_PRESENT,    TRUE,  SIO_SHR_NONE, {"FDC"},  {0, 0}, {0, 0}, {0, 0}, {0, 0}, FDC_Init},//LDN 0x00
{dsLPT,   F81866_LDN_LPT,   0, 0x0400, F81866_PARALLEL_PORT_PRESENT,  TRUE,  SIO_SHR_NONE, {"LPTE"}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, LPT_Init},//LDN 0x03
{dsUART,  F81866_LDN_UART1, 0, 0x0501, F81866_SERIAL_PORT0_PRESENT,   TRUE,  SIO_SHR_NONE, {"UAR1"}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, COM_Init},//LDN 0x10
{dsUART,  F81866_LDN_UART2, 1, 0x0501, F81866_SERIAL_PORT1_PRESENT,   TRUE,  SIO_SHR_NONE, {"UAR2"}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, COM_Init},//LDN 0x11
{dsUART,  F81866_LDN_UART3, 2, 0x0501, F81866_SERIAL_PORT2_PRESENT,   TRUE,  SIO_SHR_NONE, {"UAR3"}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, COM_Init},//LDN 0x12
{dsUART,  F81866_LDN_UART4, 3, 0x0501, F81866_SERIAL_PORT3_PRESENT,   TRUE,  SIO_SHR_IRQ1, {"UAR4"}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, COM_Init},//LDN 0x13
{dsUART,  F81866_LDN_UART5, 4, 0x0501, F81866_SERIAL_PORT4_PRESENT,   TRUE,  SIO_SHR_NONE, {"UAR5"}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, COM_Init},//LDN 0x14
{dsUART,  F81866_LDN_UART6, 5, 0x0501, F81866_SERIAL_PORT5_PRESENT,   TRUE,  SIO_SHR_IRQ1, {"UAR6"}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, COM_Init},//LDN 0x15
{dsPS2CK, F81866_LDN_PS2K,  0, 0x0303, F81866_KEYBOARD_PRESENT,       FALSE, SIO_SHR_NONE, {"PS2K"}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, KBC_Init},//LDN 0x05
#if F81866_MOUSE_PRESENT
{dsPS2CM, F81866_LDN_PS2M,  0, 0x0F03, F81866_MOUSE_PRESENT,          FALSE, SIO_SHR_IO,   {"PS2M"}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, NULL},//LDN 0x05
#endif
{dsPME,   F81866_LDN_PME,   0, 0x0C08, F81866_PME_CONTROLLER_PRESENT,FALSE, SIO_NO_RES,   {NULL},   {0, 0}, {0, 0}, {0, 0}, {0, 0}, PME_Init},//LDN 0x0A
{dsHwMon, F81866_LDN_HWM,   1, 0x0C08, F81866_HWM_PRESENT,           FALSE, SIO_SHR_NONE, {NULL},   {IO3B, 0}, {IO3L, 0}, {0, 0}, {0, 0}, HWM_Init},//LDN 0x04
{dsGPIO,  F81866_LDN_GPIO,  2, 0x0C08, F81866_GPIO_PORT_PRESENT,     FALSE, SIO_SHR_NONE, {NULL},   {IO1B, 0}, {IO1L, 0}, {0, 0}, {0, 0}, GPIO_Init},//LDN 0x06
{dsNone,  F81866_LDN_WDT,   3, 0x0C08, F81866_WDT_PRESENT,           FALSE, SIO_SHR_NONE, {NULL},   {IO2B, 0}, {IO2L, 0}, {0, 0}, {0, 0}, WDT_Init},//LDN 0x06
//===============================================================================
};//SPIO_DEV_LST mSpioDeviceList[] END of structure Buffer
#define F81866_DEV_CNT (sizeof(F81866_DevLst)/sizeof(SPIO_DEV_LST))

// Note: below bootscript table->more registers, more post time
//-------------------------------------------------------------------------
// Define the registers to save/restore in BootScriptSave table when SIO sleep
//-------------------------------------------------------------------------
static UINT8 F81866_GLOBAL_REGS[] = {
    //AMI_TODO:
    //Global registers. For example:
    //LDN Register, Multi-fun registers and Device Specific registers
    //0x07,
    0x25,0x26,0x27,0x28,0x29,0x2A,0x2B,0x2C,0x2D
};
#define F81866_G_REG_CNT (sizeof(F81866_GLOBAL_REGS)/sizeof(UINT8))

//-------------------------------------------------------------------------
// Define the local registers for configure SIO
//-------------------------------------------------------------------------
static UINT8 F81866_LOCAL_REGS[] = {
//AMI_TODO: 
    F81866_ACTIVATE_REGISTER, //Activate Reg
    F81866_BASE1_HI_REGISTER, //IO Base Registers
    F81866_BASE1_LO_REGISTER, //IO Base Registers
    F81866_BASE2_HI_REGISTER, //IO Base Registers
    F81866_BASE2_LO_REGISTER, //IO Base Registers
    F81866_IRQ1_REGISTER,     //IRQ & DMA Select Regs
    F81866_IRQ2_REGISTER,     //IRQ & DMA Select Regs
    F81866_DMA1_REGISTER,     //IRQ & DMA Select Regs
    F81866_DMA2_REGISTER,     //IRQ & DMA Select Regs
    //Logical Device Configuration Registers(Dwevice Specific)
    0xE0,0xE1,0xE2,0xE3,0xE4,0xE5,0xE6,0xE7,0xE8,0xE9,0xEA,0xEB,0xEC,0xED,0xEE,
    0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,0xF8,0xF9,0xFA,0xFB,0xFC,0xFD,0xFE,
};
#define F81866_L_REG_CNT (sizeof(F81866_LOCAL_REGS)/sizeof(UINT8))

//-------------------------------------------------------------------------
// Define script variable for enter config mode
//-------------------------------------------------------------------------
static SPIO_SCRIPT F81866_OPEN_CONFIG[]={
    //AMI_TODO:

    {
        1,    //BOOLEAN   IdxDat;     //1=IDX 0=DAT
        1,    //BOOLEAN   WrRd;       //1=Write 0=Read
        F81866_CONFIG_MODE_ENTER_VALUE  //UINT8     Value;      //if WrRd=0 wait for this data to come
    },{
        1,    //BOOLEAN   IdxDat;     //1=IDX 0=DAT
        1,    //BOOLEAN   WrRd;       //1=Write 0=Read
        F81866_CONFIG_MODE_ENTER_VALUE  //UINT8     Value;      //if WrRd=0 wait for this data to come
    }
};

//-------------------------------------------------------------------------
// Define script variable for exit config mode
//-------------------------------------------------------------------------
static SPIO_SCRIPT F81866_CLOSE_CONFIG[]={
    //AMI_TODO:

    {
        1,      //BOOLEAN   IdxDat; //1=IDX 0=DAT
        1,      //BOOLEAN   WrRd;   //1=Write 0=Read
        F81866_CONFIG_MODE_EXIT_VALUE    //UINT8     Value;  //if WrRd=0 wait for this data to come
    }
};

//-------------------------------------------------------------------------
// Here comes the table telling how to enter "SIO Config Mode"
//-------------------------------------------------------------------------
static SPIO_SCRIPT_LST    F81866_ENTER_CONFIG={
    cfgByteSeq,                 //Operation Type
    (sizeof(F81866_OPEN_CONFIG))/(sizeof(SPIO_SCRIPT)),
    &F81866_OPEN_CONFIG    //Instruction
}; 

//-------------------------------------------------------------------------
// Here comes the table telling how to exit "SIO Config Mode"
//-------------------------------------------------------------------------
static SPIO_SCRIPT_LST    F81866_EXIT_CONFIG={
    cfgByteSeq,                 //Operation Type
    (sizeof(F81866_CLOSE_CONFIG))/(sizeof(SPIO_SCRIPT)),
    &F81866_CLOSE_CONFIG   //Instruction
};

//-------------------------------------------------------------------------
// If Spio uses complicated way to enter and exit config mode
// use cfgRoutine as Operation Type instead
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
//     Here goes SPIO_LIST_ITEM structure for F81866
//-------------------------------------------------------------------------
// value of  -1 (0xF..F) means Do not check this parameter
#ifndef SB_BUS_NUM
#define SB_BUS_NUM    SIO_SB_BUS_NUM
#endif
#ifndef SB_DEV_NUM
#define SB_DEV_NUM    SIO_SB_DEV_NUM
#endif
#ifndef SB_FUNC_NUM
#define SB_FUNC_NUM    SIO_SB_FUNC_NUM
#endif

SPIO_LIST_ITEM F81866={
    //This Information is needed to identify right LPC bridge for the SIO
    -1,                             //UINT32    IsaVenDevId;
    -1,                             //UINT32    IsaSubVenId;
    SB_BUS_NUM,                     //UINT8     IsaBusNo;
    SB_DEV_NUM,                     //UINT8     IsaDevNo;
    SB_FUNC_NUM,                    //UINT8     IsaFuncNo;
    //This is the information Needed to access SIO Generic Registers
    //for the second SIO in the system change F81866 name to to SIO2_....
    //and so on
    F81866_CONFIG_INDEX,           //UINT16    SioIndex;
    F81866_CONFIG_DATA,            //UINT16    SioData;
    // Dev Select and Activate
    F81866_LDN_SEL_REGISTER,        //UINT8     DevSel;
    F81866_ACTIVATE_REGISTER,      //UINT8     Activate;
    F81866_ACTIVATE_VALUE,         //UINT8     ActivVal;
    F81866_DEACTIVATE_VALUE,       //UINT8     DeactVal;
    //Generic registers location
    F81866_BASE1_HI_REGISTER,      //UINT8     Base1Hi;
    F81866_BASE1_LO_REGISTER,      //UINT8     Base1Lo;
    F81866_BASE2_HI_REGISTER,      //UINT8     Base2Hi;
    F81866_BASE2_LO_REGISTER,      //UINT8     Base2Lo;
    F81866_IRQ1_REGISTER,          //UINT8     Irq1;
    F81866_IRQ2_REGISTER,          //UINT8     Irq2;
    F81866_DMA1_REGISTER,          //UINT8     Dma1;
    F81866_DMA2_REGISTER,          //UINT8     Dma2;
    //List of devices inside this SIO
    F81866_DEV_CNT,                //UINTN    DevCount;
    &F81866_DevLst[0],             //SPIO_DEV_LST    *SioDevList;
    //List of valid registers inside SIO to check if they has to be saved
    //in BOOT_SCRIPT_SAVE for S3 state Resume 
    //This is for global registers which are the same for all devices in SIO
    F81866_G_REG_CNT,              //UINTN        GlobalInclRegCount;
    &F81866_GLOBAL_REGS[0],        //UINT8        *GlobalIncludeReg;
    //This is for Local registers they are unique for each device in SIO
    F81866_L_REG_CNT,              //UINTN        LocalInclRegCount;
    &F81866_LOCAL_REGS[0],         //UINT8        *LocalIncludeReg; 
    //How To enter/exit Configuration mode if any 
    &F81866_ENTER_CONFIG,          //SPIO_SCRIPT_LST    *EnterCfgMode;
    &F81866_EXIT_CONFIG,           //SPIO_SCRIPT_LST    *ExitCfgMode;
};

// <AMI_PHDR_START>
//-------------------------------------------------------------------------
//
// Procedure: LoopCspIoDecodeListInit
//
// Description:
//  This function goes throught the elinked list IoRangeDecodeList
//
// Input:
//  IN  EFI_PCI_IO_PROTOCOL *PciIo - Read/Write PCI config space
//  IN  AMI_SIO_PROTOCOL *AmiSio -  contents SIO device information
//
// Output:
//  EFI_NOT_FOUND - can't find the decode routine.
//  EFI_SUCCESS - decode sucessfully.
//
// Modified: Nothing
//
// Referrals: None
//
// Notes:
//
//-------------------------------------------------------------------------
// <AMI_PHDR_END> 
EFI_STATUS LoopCspIoDecodeListInit(
    IN    EFI_PCI_IO_PROTOCOL *PciIo,
    IN    AMI_SIO_PROTOCOL    *AmiSio    )
{
    EFI_STATUS Status;
    SPIO_DEV    *dev=(SPIO_DEV*)AmiSio;
    #if(IODECODETYPE)  
    UINTN i;

    for(i=0; CspIoRangeDecodeList[i]; i++)
    {
        Status = CspIoRangeDecodeList[i](PciIo,dev->VlData.DevBase1, dev->DeviceInfo->UID, dev->DeviceInfo->Type);
        if(Status == EFI_SUCCESS) return Status;
    }
    #else
    Status = SbLib_SetLpcDeviceDecoding(PciIo,dev->VlData.DevBase1, dev->DeviceInfo->UID, dev->DeviceInfo->Type);
    #endif

    return Status;
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
//!!!!!!!!!!! PORTING REQUIRED !!!!!!!!!!! PORTING REQUIRED !!!!!!!!!!!*
//!!!!!!!!!!!!!!!! must be maintained for SIO devices!!!!!!!!!!!!!!!!!!*
//-------------------------------------------------------------------------
// <AMI_PHDR_START>
//-------------------------------------------------------------------------
//
// Procedure: XXXX_Init
//
// Description:
//  Each of INIT functions will be called twice by GenericSIO after standart 
//  initialization(Assigning and Programming IO/IRQ/DMA resources),
//  First time it will be called before Activating the device,
//  If device requires some additional initialization like
//      - programming SIO device registers except IO1, IO2, IRQ1, IRQ2, DMA1 DMA2  
//  Second time After Installing AmiSioProtocol, and DevicePath Protocol of SIO Device.  
//  If device requires some additional initialization like
//      - if programming of some runtime registers like SIO_GPIO, SIO_PM SIO_HHM is needed
//      - implementation of some additional setup questions 
//  do it here
//  NOTE#1 Once SIO_INIT function invoced SIO Logical device allready selected
//  NOTE#2 If Device Does not require any additional initialization just set 
//     InitRoutine field to NULL in SioDevLst[] Table.
//
// Input:
//  IN  AMI_SIO_PROTOCOL    *AmiSio - Logical Device's information
//  IN  EFI_PCI_IO_PROTOCOL *PciIo - Read/Write PCI config space
//  IN  SIO_INIT_STEP       InitStep - Initial routine step
//
// Output: None
//  EFI_STATUS
//  EFI_SUCCESS - Initial step sucessfully
//  EFI_INVALID_PARAMETER - not find the initial step
//
// Modified: Nothing
//
// Referrals: None
//
// Note:
//  It is recommended to have a separate Initialization Routine for each SIO Device.
//  it will save you some code needed to detect which device is currently selected.
//        case isGetSetupData:
//            SIO implementation uses separate set of NVRAM variables 
//            associated with each LogicalDevice who has 
//            SPIO_DEV.DeviceInfo->HasSetup property set to true.
//            Current Setup Settings are stored in SPIO_DEV.NvData. 
//            If due to different look and fill we need to overwrite standard 
//            Setup settings, we can do it here.....
//            =====================================================
//            if(SetupData==NULL){
//                Status=GetSetupData();
//                if(EFI_ERROR(Status)) return Status;
//                }
//            dev->NvData.DevEnable = SetupData->FdcEnable;
//            dev->NvData.DevPrsId  = 0;//SetupData->FdcPrsId;
//            dev->NvData.DevMode   = 0;//SetupData->FdcMode;
//            break;
//
//        case isPrsSelect:
//            If LDN uses non-standard way to determine possible resources(_PRS),
//            or _PRS may wary based  on LD mode. Then here we can get LD mode using 
//            SPIO_DEV.NvData.Mode field and get corresponded to the mode _PRS Buffer 
//            using GetPrsFromAml() function if ACPISUPPORT is ON. Or set of functions 
//            EFI_STATUS SetUartPrs(SPIO_DEV *Dev);
//            EFI_STATUS SetLptPrs(SPIO_DEV *Dev, BOOLEAN UseDma);
//            EFI_STATUS SetFdcPrs(SPIO_DEV *Dev);
//            EFI_STATUS SetPs2kPrs(SPIO_DEV *Dev);
//            EFI_STATUS SetPs2mPrs(SPIO_DEV *Dev);
//            EFI_STATUS SetGamePrs(SPIO_DEV *Dev);
//            EFI_STATUS SetMpu401Prs(SPIO_DEV *Dev);
//            Defined in GenericSio.h  
//            
//        case isBeforeActivate:
//            //If any register needs to be initialized, whle enumerating all SIO devices.        
//            //Use NEW SbLib_SetLpcDeviceDecoding() function to set Device Decoding Range for 
//            //Legacy devices. Implementation in SbGeneric.c, definition in SbCspLib.h
//            //=====================================================
//
//        case isAfterActivate:
//            //Ttis Initialization step is used to programm any runtime registers rsiding in
//            //Decvice's decoded io space like SIO_GPIOs, SIO_PM, HHM registers. 
//            //This Programming is needed if device doesnot have or don't need driver to do so.
//            //If there are a spetial driver like could be for HHM which could get THIS device handle
//            //and programm like Terminal Driver for COM ports and Floppy Driver for FDC 
//            //nothing needs to be done here
//
//        case isAfterBootScript:
//            //This initialization step is needed to 
//            //Use NEW SbLib_SetLpcDeviceDecoding() function to set Device Decoding Range for Legacy devices
//
//-------------------------------------------------------------------------
// <AMI_PHDR_END> 

// <AMI_PHDR_START>
//-------------------------------------------------------------------------
//
// Procedure: FDC_Init
//
// Description:
//  This function provide each initial routine in genericsio.c
//
// Input:
//  IN  AMI_SIO_PROTOCOL    *AmiSio - Logical Device's information
//  IN  EFI_PCI_IO_PROTOCOL *PciIo - Read/Write PCI config space
//  IN  SIO_INIT_STEP       InitStep - Initial routine step
//
// Output: 
//  EFI_SUCCESS - Initial step sucessfully
//  EFI_INVALID_PARAMETER - not find the initial step
//
// Modified:    Nothing
//
// Referrals:   None
//
// Notes:
//------------------------------------------------------------------------- 
// <AMI_PHDR_END> 
static EFI_STATUS FDC_Init(
    IN    AMI_SIO_PROTOCOL     *AmiSio, 
    IN    EFI_PCI_IO_PROTOCOL  *PciIo, 
    IN    SIO_INIT_STEP        InitStep 
)
{
    EFI_STATUS  Status=EFI_SUCCESS;
    SPIO_DEV    *dev=(SPIO_DEV*)AmiSio;
    UINT8       rv;     //FdcMode Register

    switch (InitStep)
    {
        case isGetSetupData:
            // Disable IODecode?
            if((!dev->DeviceInfo->Implemented) || (!dev->NvData.DevEnable))
                LoopCspIoDecodeListInit(NULL,AmiSio); 
        break;

        case isPrsSelect:
        break;

        case isBeforeActivate:
            LoopCspIoDecodeListInit(PciIo,AmiSio); // Enable IODecode 

            //AMI_TODO: please check the register define and program FDC mode

            //Read FDC Mode register
            Status=AmiSio->Access(AmiSio,FALSE,FALSE,0xF0,&rv);
            ASSERT_EFI_ERROR(Status);
            if(EFI_ERROR(Status))return Status;
    
            if(dev->NvData.DevMode)rv |= 0x10; //Bit00 set = FDD is Write Protect
            else rv &= (UINT8)(~0x10);
    
            Status=AmiSio->Access(AmiSio,TRUE,FALSE,0xF0,&rv);
            ASSERT_EFI_ERROR(Status);


        break;

        case isAfterActivate:
        break;

        #if(CORE_AFTER_4634)
        case isAfterBootScript:
        break;
        #endif

        default: Status=EFI_INVALID_PARAMETER;
    } //switch

    return Status;
}

// <AMI_PHDR_START>
//-------------------------------------------------------------------------
//
// Procedure: COM_Init
//
// Description:
//  This function provide each initial routine in genericsio.c
//
// Input:
//  IN  AMI_SIO_PROTOCOL    *AmiSio - Logical Device's information
//  IN  EFI_PCI_IO_PROTOCOL *PciIo - Read/Write PCI config space
//  IN  SIO_INIT_STEP       InitStep - Initial routine step
//
// Output: 
//  EFI_SUCCESS - Initial step sucessfully
//  EFI_INVALID_PARAMETER - not find the initial step
//
// Modified:  Nothing
//
// Referrals: None
//
// Notes:
//------------------------------------------------------------------------- 
// <AMI_PHDR_END> 
static EFI_STATUS COM_Init(
    IN    AMI_SIO_PROTOCOL     *AmiSio, 
    IN    EFI_PCI_IO_PROTOCOL  *PciIo, 
    IN    SIO_INIT_STEP        InitStep 
)
{
    EFI_STATUS  Status=EFI_SUCCESS;
    SPIO_DEV    *dev=(SPIO_DEV*)AmiSio;
    UINT8       rv;

    switch (InitStep)
    {
        case isGetSetupData:
//            if((!dev->DeviceInfo->Implemented) || (!dev->NvData.DevEnable)) {
//                 LoopCspIoDecodeListInit(NULL,AmiSio); 
//                 ClearDevResource(dev);
//            }
        break;
    
        case isPrsSelect:
        break;

        case isBeforeActivate:

//            //Only decode UART1/UART2. More others UART port is decode in PEI
//            //Attention! Remove the more com ports to PEI decode.
//            if(dev->DeviceInfo->UID <= 0x02)
//                LoopCspIoDecodeListInit(PciIo,AmiSio);
        
            //Programm Device Mode register here(if NEEDED)use AmiSioProtocol
//            if(DXE_COM_Mode_Init_Table[dev->DeviceInfo->UID].AndData8 == 0xFF) {
//                rv=DXE_COM_Mode_Init_Table[dev->DeviceInfo->UID].OrData8;
//            } else {
//                Status=AmiSio->Access(AmiSio, FALSE, FALSE, 0xF0, &rv);
//                ASSERT_EFI_ERROR(Status);
//                rv &= DXE_COM_Mode_Init_Table[dev->DeviceInfo->UID].AndData8;
//                rv |= DXE_COM_Mode_Init_Table[dev->DeviceInfo->UID].OrData8;
//            }
//			Status=AmiSio->Access(AmiSio,TRUE,FALSE,0xF0,&rv);            

            //AMI_TODO: You can program device mode as follow:

//            if(dev->DeviceInfo->UID == 0x05)    {
//                    Status=AmiSio->Access(AmiSio,FALSE,FALSE,0xF1,&rv);
//					ASSERT_EFI_ERROR(Status);
//					if(EFI_ERROR(Status))return Status;
//					//clear Bit4~3 where COM Port mode is:
//					rv &= 0xE7;            
//					switch (dev->NvData.DevMode) {
//						case 0:
//							rv |= 0x00;    //Bit4~3 = 000, Disable IR1 function
//						break;
//						case 1:
//							rv |= 0x10;    //Bit4~3 = 010, Enable IR1 function, active pulse is 1.6uS
//						break;
//						case 2:
//							rv |= 0x18;    //Bit4~3 = 011, Enable IR1 function, active pulse is 3/16 bit time
//						break;
//						default: return EFI_INVALID_PARAMETER;
//					}
//					Status=AmiSio->Access(AmiSio,TRUE,FALSE,0xF1,&rv);
//					ASSERT_EFI_ERROR(Status);
//                }
           
                //Programm Serial_X IRQ Share register.
                if((dev->DeviceInfo->Flags & SIO_SHR_IRQ1) && dev->ResOwner) { 
                    //enter cfgmode
                    SioCfgMode(dev->Owner, TRUE);
                    //set device resource owner share register
                    DevSelect(dev->ResOwner);
                      SioRegister(dev->ResOwner, FALSE, 0xF0, &rv);//read reg0xF0 value
                      rv |= 0x01; //Bit1:share or normal
                      SioRegister(dev->ResOwner, TRUE, 0xF0, &rv);//write reg0xF0 value
                    //set device irq register
                    DevSelect(dev);
                      SioRegister(dev->ResOwner, FALSE, 0x70, &rv);//read reg0x70 value
                      SioRegister(dev, TRUE, 0x70, &rv);//write reg0x70 value
                      SioRegister(dev, FALSE, 0xF0, &rv);//read reg0xF0 value
                      rv |= 0x01; //Bit1:share or normal
                      SioRegister(dev, TRUE, 0xF0, &rv);//write reg0xF0 value
                    //exit cfgmode
                    SioCfgMode(dev->Owner, FALSE);
                    dev->VlData.DevIrq1=dev->ResOwner->VlData.DevIrq1;
                }

        break;
            
        case isAfterActivate:
        break;

        #if(CORE_AFTER_4634)
        case isAfterBootScript:
        break;
        #endif

        default: Status=EFI_INVALID_PARAMETER;
    }//switch
    return Status;
}

// <AMI_PHDR_START>
//-------------------------------------------------------------------------
//
// Procedure: LPT_Init
//
// Description:
//  This function provide each initial routine in genericsio.c
//
// Input:
//  IN  AMI_SIO_PROTOCOL    *AmiSio - Logical Device's information
//  IN  EFI_PCI_IO_PROTOCOL *PciIo - Read/Write PCI config space
//  IN  SIO_INIT_STEP       InitStep - Initial routine step
//
// Output: 
//  EFI_SUCCESS - Initial step sucessfully
//  EFI_INVALID_PARAMETER - not find the initial step
//
// Modified:  Nothing
//
// Referrals: None
//
// Notes:
//------------------------------------------------------------------------- 
// <AMI_PHDR_END> 
static EFI_STATUS LPT_Init(
    IN    AMI_SIO_PROTOCOL     *AmiSio, 
    IN    EFI_PCI_IO_PROTOCOL  *PciIo, 
    IN    SIO_INIT_STEP        InitStep 
)
{
    EFI_STATUS  Status=EFI_SUCCESS;
    SPIO_DEV    *dev=(SPIO_DEV*)AmiSio;
    UINT8       rv;                //LptMode Register    

    switch (InitStep) {
        case isGetSetupData:
            // Disable decode?
            if((!dev->DeviceInfo->Implemented) || (!dev->NvData.DevEnable))
                LoopCspIoDecodeListInit(NULL,AmiSio); 
        break;
    
        case isPrsSelect:
            //depend on LPT Mode it may or may not use a DMA channel
            Strcpy(&dev->DeviceInfo->AslName[0],"LPTE");
            if(dev->NvData.DevMode&0x04) {
                #if ACPI_SUPPORT
                //if ACPI is Supported get _PRS for Extended Parallel Port from DSDT 
                //last parameter is 0-based index in F81866_DevLst[] table.
                Status=GetPrsFromAml(dev,"EPPR", 1);
                #else
                //if ACPI is not supported use corresponded Function seting 
                //"UseDma" parameter to TRUE for Extended Parallel Port
                Status=SetLptPrs(dev, TRUE);
                #endif
            }else { 
                #if ACPI_SUPPORT
                //if ACPI is Supported get _PRS for Standard Parallel Port from DSDT 
                //last parameter is 0-based index in WPCD376I_DevLst[] table.
                Status=GetPrsFromAml(dev,"LPPR", 1);
                #else
                //if ACPI is not supported use corresponded Function seting 
                //"UseDma" parameter to FALSE for Standard Parallel Port
                Status=SetLptPrs(dev, FALSE);
                #endif
            }
            ASSERT_EFI_ERROR(Status);

        break;

        case isBeforeActivate:
            LoopCspIoDecodeListInit(PciIo,AmiSio);   // Enable IODecode

            //Programm Device Mode register here(if NEEDED)use AmiSioProtocol  

            //AMI_TODO: You can program device mode as follow:

            //Programm Device Mode register here(if NEEDED)use AmiSioProtocol  
            Status=AmiSio->Access(AmiSio,FALSE,FALSE,0xF0,&rv);    //LPT Configuration Reg, Read the reg value
            ASSERT_EFI_ERROR(Status);
            if(EFI_ERROR(Status))return Status;

            //Program Lpt Mode register following SIO Specification instructions. 
            //Set mode:Bit2-0 set = LPT mode
            //clear lowest 3 bits where LPT mode is:
            rv&=0xF8;                                 
            switch (dev->NvData.DevMode) {
                    case 0:    rv|=4; //STD Printer Mode
                        break;
                    case 1:    rv|=0; //SPP Mode
                        break;
                    case 2:    rv|=1; //EPP-1.9 and SPP Mode
                        break;
                    case 3:    rv|=5; //EPP-1.7 and SPP Mode
                        break;
                    case 4:    rv|=2; //ECP Mode 
                        break;
                    case 5:    rv|=3; //ECP and EPP-1.9 Mode
                        break;
                    case 6:    rv|=7; //ECP and EPP-1.7 Mode
                        break;
                default: return EFI_INVALID_PARAMETER;
            }
            //Program back Device Mode register
            Status=AmiSio->Access(AmiSio,TRUE,FALSE,0xF0,&rv);
            ASSERT_EFI_ERROR(Status);

        break;

        case isAfterActivate:
        break;

        #if(CORE_AFTER_4634)
        case isAfterBootScript:
        break;
        #endif

        default: Status=EFI_INVALID_PARAMETER;
    } //switch

    return Status;
}

// <AMI_PHDR_START>
//-------------------------------------------------------------------------
//
// Procedure: KBC_Init
//
// Description:
//  This function provide each initial routine in genericsio.c
//
// Input:
//  IN  AMI_SIO_PROTOCOL    *AmiSio - Logical Device's information
//  IN  EFI_PCI_IO_PROTOCOL *PciIo - Read/Write PCI config space
//  IN  SIO_INIT_STEP       InitStep - Initial routine step
//
// Output: 
//  EFI_SUCCESS - Initial step sucessfully
//  EFI_INVALID_PARAMETER - not find the initial step
//
// Modified:  Nothing
//
// Referrals: None
//
// Notes:
//------------------------------------------------------------------------- 
// <AMI_PHDR_END> 
static EFI_STATUS KBC_Init(
    IN    AMI_SIO_PROTOCOL     *AmiSio, 
    IN    EFI_PCI_IO_PROTOCOL  *PciIo, 
    IN    SIO_INIT_STEP        InitStep 
)
{
    EFI_STATUS  Status=EFI_SUCCESS;

    switch (InitStep) {
        case isGetSetupData:
        case isPrsSelect:
        case isAfterActivate:
        #if(CORE_AFTER_4634)
        case isAfterBootScript:
        #endif
        break;

        case isBeforeActivate:
//            LoopCspIoDecodeListInit(PciIo,AmiSio);  // Enable IODecode
        break;

        default: Status=EFI_INVALID_PARAMETER;
    } //switch

    return Status;
}

// <AMI_PHDR_START>
//-------------------------------------------------------------------------
//
// Procedure: PME_Init
//
// Description:
//  This function provide each initial routine in genericsio.c
//
// Input:
//  IN  AMI_SIO_PROTOCOL    *AmiSio - Logical Device's information
//  IN  EFI_PCI_IO_PROTOCOL *PciIo - Read/Write PCI config space
//  IN  SIO_INIT_STEP       InitStep - Initial routine step
//
// Output: 
//  EFI_SUCCESS - Initial step sucessfully
//  EFI_INVALID_PARAMETER - not find the initial step
//
// Modified:  Nothing
//
// Referrals: None
//
// Notes:
//------------------------------------------------------------------------- 
// <AMI_PHDR_END> 
static EFI_STATUS PME_Init(
    IN    AMI_SIO_PROTOCOL     *AmiSio, 
    IN    EFI_PCI_IO_PROTOCOL  *PciIo, 
    IN    SIO_INIT_STEP        InitStep 
)
{
    EFI_STATUS  Status=EFI_SUCCESS;

    #if F81866_PME_CONTROLLER_PRESENT


    switch (InitStep) {
        case isGetSetupData:
        break;

        case isPrsSelect:
        break;

        case isBeforeActivate:
          // OEM_TODO: You need to fill DXE_PME_Init_Table[] first.
       
        break;
        
        case isAfterActivate:
        break;

        #if(CORE_AFTER_4634)
        case isAfterBootScript:
        break;
        #endif

        default: Status=EFI_INVALID_PARAMETER;
    } //switch
    #endif

    return Status;
}

// <AMI_PHDR_START>
//-------------------------------------------------------------------------
//
// Procedure: HWM_Init
//
// Description:
//  This function provide each initial routine in genericsio.c
//
// Input:
//  IN  AMI_SIO_PROTOCOL    *AmiSio - Logical Device's information
//  IN  EFI_PCI_IO_PROTOCOL *PciIo - Read/Write PCI config space
//  IN  SIO_INIT_STEP       InitStep - Initial routine step
//
// Output: 
//  EFI_SUCCESS - Initial step sucessfully
//  EFI_INVALID_PARAMETER - not find the initial step
//
// Modified:  Nothing
//
// Referrals: None
//
// Notes:
//------------------------------------------------------------------------- 
// <AMI_PHDR_END> 
static EFI_STATUS HWM_Init(
    IN    AMI_SIO_PROTOCOL     *AmiSio, 
    IN    EFI_PCI_IO_PROTOCOL  *PciIo, 
    IN    SIO_INIT_STEP        InitStep 
)
{
    EFI_STATUS  Status=EFI_SUCCESS;
    SPIO_DEV    *dev=(SPIO_DEV*)AmiSio;
    BootScriptProtocol = dev->Owner->BootScript;     

    #if F81866_HWM_PRESENT

    switch (InitStep) {
        case isGetSetupData:
        break;

        case isPrsSelect:
        break;

        case isBeforeActivate:
        // HWM registers initial if needed.
        // AMI_TODO: Add init function for configure HWM SIO space.
        
        break;
        
        case isAfterActivate:
        // HWM registers initial if needed.
        // AMI_TODO: Add init function for configure HWM SIO space.
            ProgramIsaRegisterTable(F81866_HWM_BASE_ADDRESS+0x05, \
                    F81866_HWM_BASE_ADDRESS+0x06, \
                    DXE_HWM_Init_Table_After_Active,                   
                    sizeof(DXE_HWM_Init_Table_After_Active)/sizeof(DXE_DEVICE_INIT_DATA));

            #if F81866_SMF_SUPPORT
                F81866SmartFunction();
			#endif
        break;

        #if(CORE_AFTER_4634)
        case isAfterBootScript:
        //AMI_TODO:
        // Restore HWM registers after Sx resume, if needed.
        // Below HWM read/write interface is LPC/ISA interface, 
        // if other interface, please re-program it.
        // This, Width, Address, Count, Buffer
            SaveSxSioRegisterTable(F81866_HWM_BASE_ADDRESS+0x05, \
                            F81866_HWM_BASE_ADDRESS+0x06, \
                            DXE_HWM_SIO_BootScript_Table,                           
                            sizeof(DXE_HWM_SIO_BootScript_Table)/sizeof(UINT8));
        break;
        #endif


        default: Status=EFI_INVALID_PARAMETER;
    } //switch
    #endif

    return Status;
}

// <AMI_PHDR_START>
//-------------------------------------------------------------------------
//
// Procedure: GPIO_Init
//
// Description:
//  This function provide each initial routine in genericsio.c
//
// Input:
//  IN  AMI_SIO_PROTOCOL    *AmiSio - Logical Device's information
//  IN  EFI_PCI_IO_PROTOCOL *PciIo - Read/Write PCI config space
//  IN  SIO_INIT_STEP       InitStep - Initial routine step
//
// Output: 
//  EFI_SUCCESS - Initial step sucessfully
//  EFI_INVALID_PARAMETER - not find the initial step
//
// Modified:  Nothing
//
// Referrals: None
//
// Notes:
//------------------------------------------------------------------------- 
// <AMI_PHDR_END> 
static EFI_STATUS GPIO_Init(
    IN    AMI_SIO_PROTOCOL     *AmiSio, 
    IN    EFI_PCI_IO_PROTOCOL  *PciIo, 
    IN    SIO_INIT_STEP        InitStep 
)
{
    EFI_STATUS  Status=EFI_SUCCESS;    
    #if F81866_GPIO_PORT_PRESENT
 

    switch (InitStep) {
        case isGetSetupData:
        break;

        case isPrsSelect:
        break;

        case isBeforeActivate:

        break;
        case isAfterActivate:
        break;

        #if(CORE_AFTER_4634)
        case isAfterBootScript:
        break;
        #endif

        default: Status=EFI_INVALID_PARAMETER;
    } //switch
    #endif

    return Status;
}

// <AMI_PHDR_START>
//-------------------------------------------------------------------------
//
// Procedure: WDT_Init
//
// Description:
//  This function provide each initial routine in genericsio.c
//
// Input:
//  IN  AMI_SIO_PROTOCOL    *AmiSio - Logical Device's information
//  IN  EFI_PCI_IO_PROTOCOL *PciIo - Read/Write PCI config space
//  IN  SIO_INIT_STEP       InitStep - Initial routine step
//
// Output: 
//  EFI_SUCCESS - Initial step sucessfully
//  EFI_INVALID_PARAMETER - not find the initial step
//
// Modified:  Nothing
//
// Referrals: None
//
// Notes:
//------------------------------------------------------------------------- 
// <AMI_PHDR_END> 
static EFI_STATUS WDT_Init(
    IN    AMI_SIO_PROTOCOL     *AmiSio, 
    IN    EFI_PCI_IO_PROTOCOL  *PciIo, 
    IN    SIO_INIT_STEP        InitStep 
)
{
    EFI_STATUS  Status=EFI_SUCCESS;    

    switch (InitStep) {
        case isGetSetupData:
        break;

        case isPrsSelect:
        break;

        case isBeforeActivate:

        break;
        case isAfterActivate:
        break;

        #if(CORE_AFTER_4634)
        case isAfterBootScript:
        break;
        #endif

        default: Status=EFI_INVALID_PARAMETER;
    } //switch

    return Status;
}

//-------------------------------------------------------------------------
//!!!!!!!!!!! Porting  End  !!!!!!!!!!! 
//-------------------------------------------------------------------------
// <AMI_PHDR_START>
//-------------------------------------------------------------------------
//
// Procedure: ClearDevResource
//
// Description:
//  This function will Clear SIO resource
//
// Input:
//  SPIO_DEV* dev
// Output: 
//  NONE
//
//------------------------------------------------------------------------- 
// <AMI_PHDR_END>
VOID ClearDevResource(
    IN    SPIO_DEV* dev)
{
    UINT8   Value8;
    Value8=0x00;
    SioCfgMode(dev->Owner, TRUE);
    DevSelect(dev);
    SioRegister(dev, TRUE,F81866_BASE1_HI_REGISTER,&Value8);
    SioRegister(dev, TRUE,F81866_BASE1_LO_REGISTER,&Value8);
//    SioRegister(dev, TRUE,F81866_BASE2_HI_REGISTER,&Value8);
//    SioRegister(dev, TRUE,F81866_BASE2_LO_REGISTER,&Value8);
    SioRegister(dev, TRUE,F81866_IRQ1_REGISTER,&Value8);
//    SioRegister(dev, TRUE,F81866_IRQ2_REGISTER,&Value8);
//    SioRegister(dev, TRUE,F81866_DMA1_REGISTER,&Value8);
//    SioRegister(dev, TRUE,F81866_DMA2_REGISTER,&Value8);
    SioCfgMode(dev->Owner, FALSE);
    return;

}
// <AMI_PHDR_START>
//-------------------------------------------------------------------------
//
// Procedure: ProgramSioRegisterTable
//
// Description:
//  This function will Program the SIO config space.
//
// Input:
//  IN  DXE_DEVICE_INIT_DATA    *Table - initial table
//  IN  UINT8                   Count    Table Length
//
// Output: 
//  NONE
//
//------------------------------------------------------------------------- 
// <AMI_PHDR_END> 
VOID ProgramSioRegisterTable(
    IN  AMI_SIO_PROTOCOL    *AmiSio,
    IN  DXE_DEVICE_INIT_DATA *Table,    
    IN  UINT8               Count
)
{
    UINT8   i;
    UINT8   Value8;
 
    for(i=0;i<Count;i++) {
        if(Table[i].AndData8 == 0xFF)
            Value8=Table[i].OrData8;
        else {
            AmiSio->Access(AmiSio, FALSE, FALSE, (UINT8)(Table[i].Reg16), &Value8);
            Value8 &= Table[i].AndData8;
            Value8 |= Table[i].OrData8;
        }
        AmiSio->Access(AmiSio, TRUE, FALSE, (UINT8)(Table[i].Reg16), &Value8);
    }

    return;
}

// <AMI_PHDR_START>
//-------------------------------------------------------------------------
//
// Procedure: ProgramIsaRegisterTable
//
// Description:
//  This function will Program the SIO config space.
//
// Input:
//  IN  UINT16  Index - Index port   
//  IN  UINT16  Data - Data port
//  IN  UINT16  *Table - initial table
//  IN  UINT8   Count    Table Length
//
// Output: 
//  NONE
//
//------------------------------------------------------------------------- 
// <AMI_PHDR_END> 
VOID ProgramIsaRegisterTable(
    IN  UINT16  Index,
    IN  UINT16  Data,
    IN  DXE_DEVICE_INIT_DATA *Table,
    IN  UINT8   Count
)
{
    UINT8   i;
    UINT8   Value8;
 
    for(i=0;i<Count;i++) {
        if(Table[i].AndData8 == 0xFF)
            Value8=Table[i].OrData8;
        else {
            IoWrite8(Index, (UINT8)(Table[i].Reg16));
            Value8 = IoRead8(Data);
            Value8 &= Table[i].AndData8;
            Value8 |= Table[i].OrData8;
        }
        IoWrite8(Index, (UINT8)(Table[i].Reg16));
        IoWrite8(Data, Value8);
    }

    return;
}
// <AMI_PHDR_START>
//-------------------------------------------------------------------------
//
// Procedure: ProgramRtRegisterTable
//
// Description:
//  This function will program the runtime register.
//
// Input:
//  IN  UINT16  Base - Runtime register IO base
//  IN  DXE_DEVICE_INIT_DATA  *Table - initial table
//  IN  UINT8                   Count    Table Length
//
// Output: 
//  NONE
//
//------------------------------------------------------------------------- 
// <AMI_PHDR_END> 
VOID ProgramRtRegisterTable(
    IN  UINT16  Base,
    IN  DXE_DEVICE_INIT_DATA  *Table,    
    IN  UINT8   Count

)
{
    UINT8   i;
    UINT8   Value8;

    for(i=0;i<Count;i++) {
        if(Table[i].AndData8 == 0xFF)
            Value8 = Table[i].OrData8;
        else
            Value8 = (IoRead8(Base+Table[i].Reg16) & Table[i].AndData8)|\
                     Table[i].OrData8;
        IoWrite8(Base+Table[i].Reg16, Value8 );
    }
}

// <AMI_PHDR_START>
//-------------------------------------------------------------------------
//
// Procedure: SaveSxSioRegisterTable
//
// Description:
//  This function will Save the SIO registers to boot script Table
//
// Input:
//  IN  UINT16  Index - Index port   
//  IN  UINT16  Data - Data port
//  IN  UINT16  *Table - initial table
//  IN  UINT8   Count    Table Length
//
// Output: 
//  NONE
//
//------------------------------------------------------------------------- 
// <AMI_PHDR_END> 
VOID SaveSxSioRegisterTable(
    IN  UINT16  Index,
    IN  UINT16  Data,
    IN  UINT8   *Table,    
    IN  UINT8   Count
)
{
    UINT8   i;
    UINT8   Value8;

    for(i=0;i<Count;i++) {
      IoWrite8(Index,Table[i]);
      BOOT_SCRIPT_S3_IO_WRITE_MACRO(BootScriptProtocol,
                                  EfiBootScriptWidthUint8,
                                  Index,
                                  1,
                                  &Table[i]);
      Value8 = IoRead8(Data);
      BOOT_SCRIPT_S3_IO_WRITE_MACRO(BootScriptProtocol,
                                  EfiBootScriptWidthUint8,
                                  Data,
                                  1,
                                  &Value8);
    }

    return;
}

// <AMI_PHDR_START>
//-------------------------------------------------------------------------
//
// Procedure: SaveSxRtRegisterTable
//
// Description:
//  This function will Save the runtime registers to boot script Table
//
// Input:
//  IN  UINT16  Index - Index port   
//  IN  UINT16  Data - Data port
//  IN  UINT16  *Table - initial table
//  IN  UINT8   Count    Table Length
//
// Output: 
//  NONE
//
//------------------------------------------------------------------------- 
// <AMI_PHDR_END>
VOID SaveSxRtRegisterTable(
    IN  UINT16  Base,
    IN  UINT16  *Table,    
    IN  UINT8   Count
)
{
    UINT8   i;
    UINT8   Value8;

    for(i=0;i<Count;i++) {
        Value8 = IoRead8(Base+Table[i]);
        BOOT_SCRIPT_S3_IO_WRITE_MACRO(BootScriptProtocol,
                                    EfiBootScriptWidthUint8,
                                    (Base+Table[i]),
                                    1,
                                    &Value8);
    }

    return;

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

