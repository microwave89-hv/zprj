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
// $Header: /Alaska/BIN/IO/Fintek/F81216_Sec/F81216DXE.C 5     7/18/12 9:32p Elviscai $
//
// $Revision: 5 $
//
// $Date: 7/18/12 9:32p $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/IO/Fintek/F81216_Sec/F81216DXE.C $
// 
// 5     7/18/12 9:32p Elviscai
// [TAG]  		EIPNONE
// [Category]  	Bug Fix
// [Solution]  	Correct IR mode register setting in COM_INIT
// 
// 4     7/04/11 3:22a Kasalinyi
// [Category]  	Improvement
// [Description]  	Update to new template
// [Files]  		IO_F81216.SDL
// F81216.ASL
// F81216.MAK
// F81216.SD
// F81216.UNI
// F81216DXE.C
// F81216PEI.C
// F81216Setup.H
// F81216.CIF
// 
// 3     10/28/10 2:30a Mikes
// Implement new name rule
// 
// 2     9/06/10 3:50a Mikes
// Fix compile issue with first IO module
// 
// 1     3/31/10 5:55a Fantasylai
// Initial release to F81216 just as a second IO
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:  <F81216DXE.C>
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
extern VOID SioCfgMode(GSPIO *Sio, BOOLEAN Enter);
extern VOID DevSelect(SPIO_DEV *Dev);
extern VOID SioRegister(SPIO_DEV *Dev, BOOLEAN Write, UINT8 Reg, UINT8 *Val);

extern EFI_STATUS LoopCspIoDecodeListInit(
    IN    EFI_PCI_IO_PROTOCOL *PciIo,
    IN    AMI_SIO_PROTOCOL    *AmiSio    );

static VOID ClearDevResource(
    IN  SPIO_DEV* dev
);

//Declare initial routines for your SPIO_DEV_LST list.
INITIAL_ROUTINE(COM_Init)

//<AMI_THDR_START>
//-------------------------------------------------------------------------
//
// Name:        F81216SEC_DevLst
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
static SPIO_DEV_LST F81216SEC_DevLst[]={
//If device Implemented=FALSE the rest of the table will be ignored, just to avoid compilation ERROR
//Type      LDN               UID PnpId   Implement                     HasSetu  Share RES     AslName[5] Base   Length  IrqMask  DmaMask  InitRoutine
//===============================================================================
{dsUART,  F81216SEC_LDN_UART0, 0x10, 0x0501, F81216SEC_SERIAL_PORT0_PRESENT,   TRUE,  SIO_SHR_NONE, {"UR11"}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, COM_Init},//LDN 0x00
{dsUART,  F81216SEC_LDN_UART1, 0x11, 0x0501, F81216SEC_SERIAL_PORT1_PRESENT,   TRUE,  SIO_SHR_IRQ1, {"UR12"}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, COM_Init},//LDN 0x01
{dsUART,  F81216SEC_LDN_UART2, 0x12, 0x0501, F81216SEC_SERIAL_PORT2_PRESENT,   TRUE,  SIO_SHR_IRQ1, {"UR13"}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, COM_Init},//LDN 0x02
{dsUART,  F81216SEC_LDN_UART3, 0x13, 0x0501, F81216SEC_SERIAL_PORT3_PRESENT,   TRUE,  SIO_SHR_IRQ1, {"UR14"}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, COM_Init},//LDN 0x03
//===============================================================================
};//SPIO_DEV_LST mSpioDeviceList[] END of structure Buffer
#define F81216SEC_DEV_CNT (sizeof(F81216SEC_DevLst)/sizeof(SPIO_DEV_LST))

// Note: below bootscript table->more registers, more post time
//-------------------------------------------------------------------------
// Define the registers to save/restore in BootScriptSave table when SIO sleep
//-------------------------------------------------------------------------
static UINT8 F81216SEC_GLOBAL_REGS[] = {
    //AMI_TODO:
    //Global registers. For example:
    //LDN Register, Multi-fun registers and Device Specific registers
    //0x07,
    0x25
};
#define F81216SEC_G_REG_CNT (sizeof(F81216SEC_GLOBAL_REGS)/sizeof(UINT8))

//-------------------------------------------------------------------------
// Define the local registers for configure SIO
//-------------------------------------------------------------------------
static UINT8 F81216SEC_LOCAL_REGS[] = {
//AMI_TODO: 
    F81216SEC_ACTIVATE_REGISTER, //Activate Reg
    F81216SEC_BASE1_HI_REGISTER, //IO Base Registers
    F81216SEC_BASE1_LO_REGISTER, //IO Base Registers
    F81216SEC_BASE2_HI_REGISTER, //IO Base Registers
    F81216SEC_BASE2_LO_REGISTER, //IO Base Registers
    F81216SEC_IRQ1_REGISTER,     //IRQ & DMA Select Regs
    F81216SEC_IRQ2_REGISTER,     //IRQ & DMA Select Regs
    F81216SEC_DMA1_REGISTER,     //IRQ & DMA Select Regs
    F81216SEC_DMA2_REGISTER,     //IRQ & DMA Select Regs
    //Logical Device Configuration Registers(Dwevice Specific)
    0xE0,0xE1,0xE2,0xE3,0xE4,0xE5,0xE6,0xE7,0xE8,0xE9,0xEA,0xEB,0xEC,0xED,0xEE,
    0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,0xF8,0xF9,0xFA,0xFB,0xFC,0xFD,0xFE,
};
#define F81216SEC_L_REG_CNT (sizeof(F81216SEC_LOCAL_REGS)/sizeof(UINT8))

//-------------------------------------------------------------------------
// Define script variable for enter config mode
//-------------------------------------------------------------------------
static SPIO_SCRIPT F81216SEC_OPEN_CONFIG[]={
    //AMI_TODO:
    {
        1,    //BOOLEAN   IdxDat;     //1=IDX 0=DAT
        1,    //BOOLEAN   WrRd;       //1=Write 0=Read
        F81216SEC_CONFIG_MODE_ENTER_VALUE  //UINT8     Value;      //if WrRd=0 wait for this data to come
    },
    {
        1,    //BOOLEAN   IdxDat;     //1=IDX 0=DAT
        1,    //BOOLEAN   WrRd;       //1=Write 0=Read
        F81216SEC_CONFIG_MODE_ENTER_VALUE  //UINT8     Value;      //if WrRd=0 wait for this data to come
    }
};

//-------------------------------------------------------------------------
// Define script variable for exit config mode
//-------------------------------------------------------------------------
static SPIO_SCRIPT F81216SEC_CLOSE_CONFIG[]={
    //AMI_TODO:
    {
        1,      //BOOLEAN   IdxDat; //1=IDX 0=DAT
        1,      //BOOLEAN   WrRd;   //1=Write 0=Read
        0xAA    //UINT8     Value;  //if WrRd=0 wait for this data to come
    }
};

//-------------------------------------------------------------------------
// Here comes the table telling how to enter "SIO Config Mode"
//-------------------------------------------------------------------------
static SPIO_SCRIPT_LST    F81216SEC_ENTER_CONFIG={
    cfgByteSeq,                 //Operation Type
    (sizeof(F81216SEC_OPEN_CONFIG))/(sizeof(SPIO_SCRIPT)),
    &F81216SEC_OPEN_CONFIG    //Instruction
}; 

//-------------------------------------------------------------------------
// Here comes the table telling how to exit "SIO Config Mode"
//-------------------------------------------------------------------------
static SPIO_SCRIPT_LST    F81216SEC_EXIT_CONFIG={
    cfgByteSeq,                 //Operation Type
    (sizeof(F81216SEC_CLOSE_CONFIG))/(sizeof(SPIO_SCRIPT)),
    &F81216SEC_CLOSE_CONFIG   //Instruction
};

//-------------------------------------------------------------------------
// If Spio uses complicated way to enter and exit config mode
// use cfgRoutine as Operation Type instead
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
//     Here goes SPIO_LIST_ITEM structure for F81216SEC
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

SPIO_LIST_ITEM F81216SEC={
    //This Information is needed to identify right LPC bridge for the SIO
    -1,                             //UINT32    IsaVenDevId;
    -1,                             //UINT32    IsaSubVenId;
    SB_BUS_NUM,                     //UINT8     IsaBusNo;
    SB_DEV_NUM,                     //UINT8     IsaDevNo;
    SB_FUNC_NUM,                    //UINT8     IsaFuncNo;
    //This is the information Needed to access SIO Generic Registers
    //for the second SIO in the system change F81216SEC name to to SIO2_....
    //and so on
    F81216SEC_CONFIG_INDEX,           //UINT16    SioIndex;
    F81216SEC_CONFIG_DATA,            //UINT16    SioData;
    // Dev Select and Activate
    F81216SEC_LDN_SEL_REGISTER,        //UINT8     DevSel;
    F81216SEC_ACTIVATE_REGISTER,      //UINT8     Activate;
    F81216SEC_ACTIVATE_VALUE,         //UINT8     ActivVal;
    F81216SEC_DEACTIVATE_VALUE,       //UINT8     DeactVal;
    //Generic registers location
    F81216SEC_BASE1_HI_REGISTER,      //UINT8     Base1Hi;
    F81216SEC_BASE1_LO_REGISTER,      //UINT8     Base1Lo;
    F81216SEC_BASE2_HI_REGISTER,      //UINT8     Base2Hi;
    F81216SEC_BASE2_LO_REGISTER,      //UINT8     Base2Lo;
    F81216SEC_IRQ1_REGISTER,          //UINT8     Irq1;
    F81216SEC_IRQ2_REGISTER,          //UINT8     Irq2;
    F81216SEC_DMA1_REGISTER,          //UINT8     Dma1;
    F81216SEC_DMA2_REGISTER,          //UINT8     Dma2;
    //List of devices inside this SIO
    F81216SEC_DEV_CNT,                //UINTN    DevCount;
    &F81216SEC_DevLst[0],             //SPIO_DEV_LST    *SioDevList;
    //List of valid registers inside SIO to check if they has to be saved
    //in BOOT_SCRIPT_SAVE for S3 state Resume 
    //This is for global registers which are the same for all devices in SIO
    F81216SEC_G_REG_CNT,              //UINTN        GlobalInclRegCount;
    &F81216SEC_GLOBAL_REGS[0],        //UINT8        *GlobalIncludeReg;
    //This is for Local registers they are unique for each device in SIO
    F81216SEC_L_REG_CNT,              //UINTN        LocalInclRegCount;
    &F81216SEC_LOCAL_REGS[0],         //UINT8        *LocalIncludeReg; 
    //How To enter/exit Configuration mode if any 
    &F81216SEC_ENTER_CONFIG,          //SPIO_SCRIPT_LST    *EnterCfgMode;
    &F81216SEC_EXIT_CONFIG,           //SPIO_SCRIPT_LST    *ExitCfgMode;
};

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
// Note:
//------------------------------------------------------------------------- 
// <AMI_PHDR_END> 
static EFI_STATUS COM_Init(
    IN    AMI_SIO_PROTOCOL     *AmiSio, 
    IN    EFI_PCI_IO_PROTOCOL  *PciIo, 
    IN    SIO_INIT_STEP        InitStep 
)
{
    EFI_STATUS       Status=EFI_SUCCESS;
    SPIO_DEV          *dev=(SPIO_DEV*)AmiSio;
    UINT8             rv;
//-----------------------------
    switch (InitStep)
    {
        case isGetSetupData:
 //           // Disable IODecode?
            if((!dev->DeviceInfo->Implemented) || (!dev->NvData.DevEnable)) {
 //                LoopCspIoDecodeListInit(NULL,AmiSio); 
                 ClearDevResource(dev);
            }
        break;
    
        case isPrsSelect:
        break;

        case isBeforeActivate:

            //Programm Device Mode register here(if NEEDED)use AmiSioProtocol
            //make serial port 0 as IR port funtion only
//            if(dev->DeviceInfo->UID == 0x10)
//            {
//                //Programm Device Mode register here(if NEEDED)use AmiSioProtocol
//                Status=AmiSio->Access(AmiSio,FALSE,FALSE,0xF1,&rv);
//                ASSERT_EFI_ERROR(Status);
//                if(EFI_ERROR(Status)) return Status;
//				
//				rv &= 0xE3;
//				
//                switch (dev->NvData.DevMode)
//                {
//                    case 0:			//Bit4 = 0, Serial Port Function Mode
//                        break;
//                    case 1:
//                        rv|=0x10;    //Bit4 = 1 Bit3,Bit2 = 00 , IR Mode,Pusle 1.6us,Full Duplex
//                        break;
//                    case 2:
//                        rv|=0x14;    //Bit4 = 1 Bit3,Bit2 = 01 , IR Mode,Pusle 1.6us,Half Duplex
//                        break;
//                    case 3:
//                        rv|=0x18;    //Bit4 = 1 Bit3,Bit2 = 10 , IR Mode,Pusle 3/16 Bit Time,Full Duplex
//                        break;
//                    case 4:
//                        rv|=0x1C;    //Bit4 = 1 Bit3,Bit2 = 11 , IR Mode,Pusle 3/16 Bit Time,Half Duplex
//                        break;
//                    default: return EFI_INVALID_PARAMETER;
//                }
//                Status=AmiSio->Access(AmiSio,TRUE,FALSE,0xF1,&rv);
//                ASSERT_EFI_ERROR(Status);
//            }
            //Programm Serial_X IRQ Share register.
            if((dev->DeviceInfo->Flags & SIO_SHR_IRQ1) && dev->ResOwner) { 
                //enter cfgmode
                SioCfgMode(dev->Owner, TRUE);
                //set device resource owner share register
                DevSelect(dev->ResOwner);
	              SioRegister(dev->ResOwner, FALSE, 0x70, &rv);//read reg0x70 value
                rv |= 0x10; //Bit4:share or normal
	              SioRegister(dev->ResOwner, TRUE, 0x70, &rv);//write reg0x70 value
                //set device share register
                DevSelect(dev);
	              SioRegister(dev, TRUE, 0x70, &rv);//read reg0x70 value
                //exit cfgmode
                SioCfgMode(dev->Owner, FALSE);
				dev->VlData.DevIrq1=dev->ResOwner->VlData.DevIrq1;
            }

            {
                EFI_GUID SetupGuid = SETUP_GUID;
                UINTN       Size = sizeof(SETUP_DATA);
                SETUP_DATA                      SetupData;
            
                  Status = pRS->GetVariable ( L"Setup", \
                                              &SetupGuid, \
                                              NULL,\
                                              &Size, \
                                              &SetupData );

                Status=AmiSio->Access(AmiSio,FALSE,FALSE,0x70,&rv);
                // PCI Share Mode
                if( SetupData.F81216ComIrqShareMode == 0 ) {
                    rv &= ~(BIT5) ;
                    rv |= BIT4 ;
                }
                else { // ISA Share Mode
                    rv |= BIT5 ;
                    rv |= BIT4 ;
                }
                Status=AmiSio->Access(AmiSio,TRUE,FALSE,0x70,&rv);
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
static VOID ClearDevResource(
    IN  SPIO_DEV* dev
)
{
    UINT8   Value8;
    Value8=0x00;
    SioCfgMode(dev->Owner, TRUE);
    DevSelect(dev);
    SioRegister(dev, TRUE,F81216SEC_BASE1_HI_REGISTER,&Value8);
    SioRegister(dev, TRUE,F81216SEC_BASE1_LO_REGISTER,&Value8);
//    SioRegister(dev, TRUE,F81216SEC_BASE2_HI_REGISTER,&Value8);
//    SioRegister(dev, TRUE,F81216SEC_BASE2_LO_REGISTER,&Value8);
    SioRegister(dev, TRUE,F81216SEC_IRQ1_REGISTER,&Value8);
//    SioRegister(dev, TRUE,F81216SEC_IRQ2_REGISTER,&Value8);
//    SioRegister(dev, TRUE,F81216SEC_DMA1_REGISTER,&Value8);
//    SioRegister(dev, TRUE,F81216SEC_DMA2_REGISTER,&Value8);
    SioCfgMode(dev->Owner, FALSE);
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
