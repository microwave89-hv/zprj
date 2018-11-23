//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.            **
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
// $Header: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/CRB/CRBPei.c 12    4/16/13 5:25a Thomaschen $
//
// $Revision: 12 $
//
// $Date: 4/16/13 5:25a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/CRB/CRBPei.c $
// 
// 12    4/16/13 5:25a Thomaschen
// 
// 11    9/28/12 10:27a Wesleychen
//  - Remove "AMI_RAPID_START_WORKAROUND"
//    CRB.SDL; CRB.PEI
// 
// 10    9/06/12 11:33a Wesleychen
// Fixed system cannot wakeup via RTC if iFFS is enable.
// (Token "AMI_RAPID_START_WORKAROUND")
// 
// 9     9/04/12 11:04p Wesleychen
//  - Always enable 60h/64h decode.
//  - Remove CRB GPIO settings.
// 
// 4     7/31/12 5:16a Wesleychen
// Programming GPIOs by reference Intel BIOS v80 setting.
// 
// 1     2/12/12 10:38p Victortu
// Intel SharkBay CRB initially releases.
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:        CRBPEI.c
//
// Description: This file contains code for Chipset Reference Board
//              Template initialization in the PEI stage
//
//<AMI_FHDR_END>
//*************************************************************************

//---------------------------------------------------------------------------
// Include(s)
//---------------------------------------------------------------------------

#include <Efi.h>
#include <Pei.h>
#include <Token.h>
#include <AmiPeiLib.h>
#include <Hob.h>
#include <Setup.h>
#include <AmiCspLib.h>
#if defined(IntelPchInclude_SUPPORT) && IntelPchInclude_SUPPORT == 1
#include <PchAccess.h>
#endif
#include <ppi\smbus.h>
// Produced PPIs

// Consumed PPIs
#include <ppi\NBPPI.h>
#include <ppi\SBPPI.h>
// Intel Platform Policy Override Sample Code >>>
//#####include <Ppi\PchPlatformPolicy\PchPlatformPolicy.h>
//#####include <Ppi\SaPlatformPolicy\SaPlatformPolicy.h>
// Intel Platform Policy Override Sample Code <<<
//---------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//---------------------------------------------------------------------------
// Constant Definition(s)

// Macro Definition(s)

// Type Definition(s)

typedef struct {
    UINT64          BusDevFunReg;
    UINT32          SubId;
} PCI_SUBID_TABLE;

//---------------------------------------------------------------------------
// Variable and External Declaration(s)
//---------------------------------------------------------------------------
// Variable Declaration(s)

// GUID Definition(s)
EFI_GUID gPeiSmBusPpiGuid             = EFI_PEI_SMBUS_PPI_GUID;
// Intel Platform Policy Override Sample Code >>>
//####EFI_GUID gOemPchPlatformPolicyOverridePpiGuid = AMI_PEI_SB_OEM_PLATFORM_POLICY_OVERRIDE_PPI_GUID;
//####EFI_GUID gOemSalatformPolicyOverridePpiGuid = AMI_PEI_NB_OEM_PLATFORM_POLICY_OVERRIDE_PPI_GUID
// Intel Platform Policy Override Sample Code <<<
// PPI Definition(s)


// Function Definition(s)
EFI_STATUS InitCK505ClockGen(
	IN EFI_PEI_SERVICES             **PeiServices,
	IN EFI_PEI_NOTIFY_DESCRIPTOR    *NotifyDescriptor,
	IN VOID                         *NullPpi
);

// Intel Platform Policy Override Sample Code >>>
//####EFI_STATUS OemPchPlatformPolicyOverride (
//####  IN EFI_PEI_SERVICES             **PeiServices,
//####  IN EFI_PEI_NOTIFY_DESCRIPTOR    *NotifyDescriptor,
//####  IN VOID                         *Ppi
//####);

//####EFI_STATUS OemSaPlatformPolicyOverride (
//####  IN EFI_PEI_SERVICES             **PeiServices,
//####  IN EFI_PEI_NOTIFY_DESCRIPTOR    *NotifyDescriptor,
//####  IN VOID                         *Ppi
//####);
// Intel Platform Policy Override Sample Code <<<

// PPI that are installed

static EFI_PEI_NOTIFY_DESCRIPTOR mNotifyList[] = 
{
  {
    EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
    &gPeiSmBusPpiGuid,
    InitCK505ClockGen
  }
};

// Intel Platform Policy Override Sample Code >>>
//####static EFI_PEI_NOTIFY_DESCRIPTOR  mOverrideNotifyList[] = {
//####  {
//####    EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK,
//####    &gOemSalatformPolicyOverridePpiGuid,
//####    OemSaPlatformPolicyOverride

//####    EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
//####    &gOemPchPlatformPolicyOverridePpiGuid,
//####    OemPchPlatformPolicyOverride
//####  }
//####};
// Intel Platform Policy Override Sample Code <<<

// Function Prototype(s)
//---------------------------------------------------------------------------
// Variable and External Declaration(s)
//---------------------------------------------------------------------------
// Variable Declaration(s)

AMI_GPIO_INIT_TABLE_STRUCT Crb1GpioTable [] = {
////  Intel CRB BIOS Setting  ////
////  Just for reference only!!    ////
/*
    {0,  IS_GPIO + IS_GPI},
    {1,  IS_GPIO + IS_GPI + GPI_INV},
    {2,  IS_GPIO + IS_GPI + GPI_INV},
    {3,  IS_NOT_GPIO},
    {4,  IS_GPIO + IS_GPI},
    {5,  IS_GPIO + IS_GPI},
    {6,  IS_GPIO + IS_GPI},
    {7,  IS_GPIO + IS_GPI + GPI_INV},

    {8,  IS_GPIO + IS_GPI + GPI_INV},
    {9,  IS_NOT_GPIO},
    {10, IS_NOT_GPIO},
    {11, IS_GPIO + IS_GPO + OUTPUT_LOW},
    {12, IS_NOT_GPIO},
    {13, IS_GPIO + IS_GPO + OUTPUT_LOW},
    {14, IS_GPIO + IS_GPI + GPI_INV},
    {15, IS_GPIO + IS_GPO + OUTPUT_LOW},

    {16, IS_NOT_GPIO},
    {17, IS_GPIO + IS_GPI + GPI_INV},
    {18, IS_GPIO + IS_GPI},
    {19, IS_GPIO + IS_GPI},
    {20, IS_NOT_GPIO},
    {21, IS_GPIO + IS_GPI},
    {22, IS_GPIO + IS_GPI},
    {23, IS_NOT_GPIO},

    {24, IS_GPIO + IS_GPI},
    {25, IS_GPIO + IS_GPI},
    {26, IS_GPIO + IS_GPI},
    {27, IS_GPIO + IS_GPI},
    {28, IS_GPIO + IS_GPI},
    {29, IS_NOT_GPIO},
    {30, IS_NOT_GPIO},
    {31, IS_GPIO + IS_GPI},

    {32, IS_GPIO + IS_GPI},
    {33, IS_GPIO + IS_GPI},
    {34, IS_GPIO + IS_GPI},
    {35, IS_GPIO + IS_GPI},
    {36, IS_GPIO + IS_GPI},
    {37, IS_GPIO + IS_GPI},
    {38, IS_GPIO + IS_GPI},
    {39, IS_GPIO + IS_GPI},

    {40, IS_NOT_GPIO},
    {41, IS_NOT_GPIO},
    {42, IS_NOT_GPIO},
    {43, IS_NOT_GPIO},
    {44, IS_GPIO + IS_GPI},
    {45, IS_GPIO + IS_GPO + OUTPUT_HIGH},
    {46, IS_GPIO + IS_GPO + OUTPUT_HIGH},
    {47, IS_GPIO + IS_GPO + OUTPUT_LOW},

    {48, IS_GPIO + IS_GPI},
    {49, IS_GPIO + IS_GPI},
    {50, IS_GPIO + IS_GPI + OUTPUT_HIGH},
    {51, IS_GPIO + IS_GPI},
    {52, IS_GPIO + IS_GPI + OUTPUT_HIGH},
    {53, IS_GPIO + IS_GPI},
    {54, IS_GPIO + IS_GPI + OUTPUT_HIGH},
    {55, IS_GPIO + IS_GPI},

    {56, IS_NOT_GPIO},
    {57, IS_GPIO + IS_GPI},
    {58, IS_NOT_GPIO},
    {59, IS_NOT_GPIO},
    {60, IS_GPIO + IS_GPO + OUTPUT_HIGH},
    {61, IS_NOT_GPIO},
    {62, IS_NOT_GPIO},
    {63, IS_NOT_GPIO},

    {64, IS_NOT_GPIO},
    {65, IS_NOT_GPIO},
    {66, IS_NOT_GPIO},
    {67, IS_NOT_GPIO},
    {68, IS_GPIO + IS_GPI},
    {69, IS_GPIO + IS_GPI},
    {70, IS_GPIO + IS_GPI},
    {71, IS_GPIO + IS_GPI},

    {72, IS_GPIO + IS_GPO + OUTPUT_HIGH},
    {73, IS_NOT_GPIO},
    {74, IS_GPIO + IS_GPI},
    {75, IS_NOT_GPIO},
*/
////  Intel CRB BIOS Setting  ////
    {0xffff, 0xffff}, // End of the table.
};
AMI_GPIO_INIT_TABLE_STRUCT Crb2GpioTable [] = {
//    {13, IS_GPIO + IS_GPI},
    {0xffff, 0xffff}, // End of the table.
};

// GUID Definition(s)

// PPI Definition(s)
AMI_GPIO_INIT_PPI Crb1GpioInitPpi = { 
    GPIO_BASE_ADDRESS,
    Crb1GpioTable,
    TRUE
};

AMI_GPIO_INIT_PPI Crb2GpioInitPpi = { 
    GPIO_BASE_ADDRESS,
    Crb2GpioTable,
    TRUE
};

AMI_SB_PCI_SSID_TABLE_STRUCT Crb1SbSsidTable[] = { 
    CRB1_SB_PCI_DEVICES_SSID_TABLE
};

AMI_NB_PCI_SSID_TABLE_STRUCT Crb1NbSsidTable[] = { 
    CRB1_NB_PCI_DEVICES_SSID_TABLE
};

AMI_SB_PCI_SSID_TABLE_STRUCT Crb2SbSsidTable[] = { 
    CRB2_SB_PCI_DEVICES_SSID_TABLE
};

AMI_NB_PCI_SSID_TABLE_STRUCT Crb2NbSsidTable[] = { 
    CRB2_NB_PCI_DEVICES_SSID_TABLE
};

static AMI_PEI_SB_CUSTOM_PPI Crb1SbCustomPpi = {
    &Crb1GpioInitPpi, 
    Crb1SbSsidTable
};

static AMI_PEI_NB_CUSTOM_PPI Crb1NbCustomPpi = {
    Crb1NbSsidTable
};

static AMI_PEI_SB_CUSTOM_PPI Crb2SbCustomPpi = {
    &Crb2GpioInitPpi, 
    Crb2SbSsidTable
};

static AMI_PEI_NB_CUSTOM_PPI Crb2NbCustomPpi = {
    Crb2NbSsidTable
};

// PPI that are installed

static EFI_PEI_PPI_DESCRIPTOR Crb1CustomPpi[] = {
    { EFI_PEI_PPI_DESCRIPTOR_PPI , \
      &gAmiPeiNBCustomPpiGuid, &Crb1NbCustomPpi },
    { EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST, \
      &gAmiPeiSBCustomPpiGuid, &Crb1SbCustomPpi },
};

static EFI_PEI_PPI_DESCRIPTOR Crb2CustomPpi[] = {
    { EFI_PEI_PPI_DESCRIPTOR_PPI , \
      &gAmiPeiNBCustomPpiGuid, &Crb2NbCustomPpi },
    { EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST, \
      &gAmiPeiSBCustomPpiGuid, &Crb2SbCustomPpi },
};
// PPI that are notified

// External Declaration(s)
#define		PORT_SELECT_REGISTER			0x27
	#define		GPIO_PROG_SEL			BIT2|BIT3
	#define		GPIO0_EN			0
	#define		GPIO1_EN			BIT2
	#define		GPIO2_EN			BIT3

#define		MULTI_FUNCTION_SELECT_1_REGISTER	0x28
	#define		LPT_GP_EN			BIT5

// Function Definition(s)
VOID F81866_CRBPeiClearDevResource(
    IN  UINT8    Ldn
)
{
    // Seclect device LDN
    IoWrite8(F81866_CONFIG_INDEX, F81866_LDN_SEL_REGISTER);
    IoWrite8(F81866_CONFIG_DATA, Ldn);
    // Deactivate Device
    IoWrite8(F81866_CONFIG_INDEX, F81866_ACTIVATE_REGISTER);
    IoWrite8(F81866_CONFIG_DATA,  F81866_DEACTIVATE_VALUE);
    // Clear Base Address
    IoWrite8(F81866_CONFIG_INDEX, F81866_BASE1_HI_REGISTER);
    IoWrite8(F81866_CONFIG_DATA,  0);
    IoWrite8(F81866_CONFIG_INDEX, F81866_BASE1_LO_REGISTER);
    IoWrite8(F81866_CONFIG_DATA,  0);
    // Clear Interrupt
    IoWrite8(F81866_CONFIG_INDEX, F81866_IRQ1_REGISTER);
    IoWrite8(F81866_CONFIG_DATA,  0);
//    return;
}

VOID F81866ConfigRegisterWrite(UINT8 Index, UINT8 Data)
{
	IoWrite8(F81866_CONFIG_INDEX, Index);
	IoWrite8(F81866_CONFIG_DATA, Data);
}
UINT8 F81866ConfigRegisterRead(UINT8 Index)
{
	UINT8 Data8;
	IoWrite8(F81866_CONFIG_INDEX, Index);
	Data8 = IoRead8(F81866_CONFIG_DATA);
	return Data8;
}
VOID F81866LDNSelect(UINT8 Ldn)
{
	IoWrite8(F81866_CONFIG_INDEX, F81866_LDN_SEL_REGISTER);
	IoWrite8(F81866_CONFIG_DATA, Ldn);
}
VOID F81866EnterConfigMode()
{
	IoWrite8(F81866_CONFIG_INDEX, F81866_CONFIG_MODE_ENTER_VALUE);
	IoWrite8(F81866_CONFIG_INDEX, F81866_CONFIG_MODE_ENTER_VALUE);
}
VOID F81866ExitConfigMode()
{
	// Exit config mode
	IoWrite8(F81866_CONFIG_INDEX, F81866_CONFIG_MODE_EXIT_VALUE);
}
VOID F81866SetGpioPin(IN UINT8 GpioNum, IN UINT8 Type, IN UINT8 Level, IN UINT8 Drive)
{
	UINT8	Data8, Offset;
	
//	F81866EnterConfigMode();	
	F81866LDNSelect(F81866_LDN_GPIO);		//GPIO Device Configuration Registers
	
	if( (GpioNum/10) <= 7 ){
		Offset = ( ~(GpioNum/10) );
		Offset = Offset << 4;
		Offset &= 0xF0;
	}
	else if ( (GpioNum/10) == 8 )
		Offset = 0x88;	
	Data8 = F81866ConfigRegisterRead(Offset + 3);	//Drive Enable Register
	Data8 &= ~( 1 << ( GpioNum%10 ) );
	if(Drive == 1)
		Data8 |= ( 1 << ( GpioNum%10 ) );
	F81866ConfigRegisterWrite(Offset + 3, Data8);
	
	Data8 = F81866ConfigRegisterRead(Offset + 1);	//Output Data Register
	Data8 &= ~( 1 << ( GpioNum%10 ) );
	if(Level == 1)
		Data8 |= ( 1 << ( GpioNum%10 ) );
	F81866ConfigRegisterWrite(Offset + 1, Data8);		

	Data8 = F81866ConfigRegisterRead(Offset);	//Output Enable Register
	Data8 &= ~( 1 << ( GpioNum%10 ) );
	if(Type == 0)
		Data8 |= ( 1 << ( GpioNum%10 ) );
	F81866ConfigRegisterWrite(Offset, Data8);

//	F81866ExitConfigMode();
}

//---------------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   CRBPEI_Init
//
// Description: This function is the entry point for CRB PEIM.
//              It initializes the chipset CRB in PEI phase.
//
// Input:       FfsHeader   - Pointer to the FFS file header.
//              PeiServices - Pointer to the PEI services table.
//
// Output:      EFI_SUCCESS
//
// Notes:       This routine is called very early, prior to SBPEI and NBPEI.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS EFIAPI CRBPEI_Init (
    IN EFI_FFS_FILE_HEADER      *FfsHeader,
    IN EFI_PEI_SERVICES         **PeiServices )
{
    EFI_STATUS                  Status = EFI_SUCCESS;
    EFI_PEI_PCI_CFG2_PPI        *PciCfg;
    EFI_PEI_CPU_IO_PPI          *CpuIo;

    // Get pointer to the PCI config PPI
    PciCfg = (*PeiServices)->PciCfg;

    // Get pointer to the CpuIo PPI
    CpuIo = (*PeiServices)->CpuIo;

//    Status = SbLib_SetLpcDeviceDecoding(NULL,0x60, 0, dsPS2K);          // Decode SB Port 0x60,0x64

    // Install custom PPI for customization
    // Customers or OEM can define SSID and GPIO by different platform type
#if CRB_CUSTOM_PPI_SUPPORT
    // This is a sample for reference.
    Status = (*PeiServices)->InstallPpi( PeiServices, Crb1CustomPpi );
    ASSERT_PEI_ERROR( PeiServices, Status );
//####  Status = (*PeiServices)->InstallPpi( PeiServices, Crb2CustomPpi );
//####  ASSERT_PEI_ERROR( PeiServices, Status );
#endif
	// Set the CRB Notify PPI
    if ( CLOCK_GENERATOR_ADDRESS != 0xFF)
    {
      Status = (*PeiServices)->NotifyPpi(PeiServices, mNotifyList);
      ASSERT_PEI_ERROR (PeiServices, Status);
    }

// Intel Platform Policy Override Sample Code >>>
//####    Status = (*PeiServices)->NotifyPpi(PeiServices, &mOverrideNotifyList[0]);
//####    ASSERT_PEI_ERROR (PeiServices, Status);
// Intel Platform Policy Override Sample Code <<<

{
#include <Setup.h>
#include <Ppi\ReadOnlyVariable2.h>

    EFI_PEI_READ_ONLY_VARIABLE2_PPI *ReadOnlyVariable = NULL;
    EFI_GUID gPeiReadOnlyVarPpiGuid = EFI_PEI_READ_ONLY_VARIABLE2_PPI_GUID;
    EFI_GUID gSetupGuid = SETUP_GUID;
    UINTN                           VariableSize = sizeof( SETUP_DATA );
    SETUP_DATA                      SetupData;

    Status = (*PeiServices)->LocatePpi( PeiServices, \
                                        &gPeiReadOnlyVarPpiGuid, \
                                        0, \
                                        NULL, \
                                        &ReadOnlyVariable );
    VariableSize = sizeof(SetupData);
    Status = ReadOnlyVariable->GetVariable( ReadOnlyVariable, \
                                            L"Setup", \
                                            &gSetupGuid, \
                                            NULL, \
                                            &VariableSize, \
                                            &SetupData );

	// Parallel Port / Gpio multi function selection _Begin >>
	if(SetupData.ParallelGpioSettings == 1) {
		UINT8	Data8;

		F81866EnterConfigMode();

        Data8 = F81866ConfigRegisterRead(PORT_SELECT_REGISTER);
		Data8 &= ~(GPIO_PROG_SEL);
		Data8 |= GPIO0_EN;

		Data8 = F81866ConfigRegisterRead(MULTI_FUNCTION_SELECT_1_REGISTER);
		Data8 &= ~(LPT_GP_EN);
		//if(SetupData.ParallelGpioSettings == 1)
			Data8 |= LPT_GP_EN;
		F81866ConfigRegisterWrite(MULTI_FUNCTION_SELECT_1_REGISTER, Data8);

        F81866_CRBPeiClearDevResource(F81866_LDN_LPT);

    F81866LDNSelect(F81866_LDN_GPIO);
    // GPIO7x
    F81866ConfigRegisterWrite(0x83, 0xFF); // All push pull
    F81866ConfigRegisterWrite(0x81, 
                        SetupData.F81866LptGpioConfiguration7xLevel[7] << 7
                    |   SetupData.F81866LptGpioConfiguration7xLevel[6] << 6
                    |   SetupData.F81866LptGpioConfiguration7xLevel[5] << 5
                    |   SetupData.F81866LptGpioConfiguration7xLevel[4] << 4
                    |   SetupData.F81866LptGpioConfiguration7xLevel[3] << 3
                    |   SetupData.F81866LptGpioConfiguration7xLevel[2] << 2
                    |   SetupData.F81866LptGpioConfiguration7xLevel[1] << 1
                    |   SetupData.F81866LptGpioConfiguration7xLevel[0] );
    F81866ConfigRegisterWrite(0x80, 
                        SetupData.F81866LptGpioConfiguration7x[7] << 7
                    |   SetupData.F81866LptGpioConfiguration7x[6] << 6
                    |   SetupData.F81866LptGpioConfiguration7x[5] << 5
                    |   SetupData.F81866LptGpioConfiguration7x[4] << 4
                    |   SetupData.F81866LptGpioConfiguration7x[3] << 3
                    |   SetupData.F81866LptGpioConfiguration7x[2] << 2
                    |   SetupData.F81866LptGpioConfiguration7x[1] << 1
                    |   SetupData.F81866LptGpioConfiguration7x[0] );
    // GPIO8x
    F81866ConfigRegisterWrite(0x8B, 0xFF); // All push pull
    F81866ConfigRegisterWrite(0x89, 
                        SetupData.F81866LptGpioConfiguration8xLevel[7] << 7
                    |   SetupData.F81866LptGpioConfiguration8xLevel[6] << 6
                    |   SetupData.F81866LptGpioConfiguration8xLevel[5] << 5
                    |   SetupData.F81866LptGpioConfiguration8xLevel[4] << 4
                    |   SetupData.F81866LptGpioConfiguration8xLevel[3] << 3
                    |   SetupData.F81866LptGpioConfiguration8xLevel[2] << 2
                    |   SetupData.F81866LptGpioConfiguration8xLevel[1] << 1
                    |   SetupData.F81866LptGpioConfiguration8xLevel[0] );
    F81866ConfigRegisterWrite(0x88, 
                        SetupData.F81866LptGpioConfiguration8x[7] << 7
                    |   SetupData.F81866LptGpioConfiguration8x[6] << 6
                    |   SetupData.F81866LptGpioConfiguration8x[5] << 5
                    |   SetupData.F81866LptGpioConfiguration8x[4] << 4
                    |   SetupData.F81866LptGpioConfiguration8x[3] << 3
                    |   SetupData.F81866LptGpioConfiguration8x[2] << 2
                    |   SetupData.F81866LptGpioConfiguration8x[1] << 1
                    |   SetupData.F81866LptGpioConfiguration8x[0] );

        F81866ExitConfigMode();
	}
	// Parallel Port / Gpio multi function selection _End <<

    {
        F81866EnterConfigMode() ;
        F81866LDNSelect(F81866_LDN_WDT) ;
        
        switch( SetupData.F81866WdtEnable ) {
            case 1 : // WDT Enabled
                // Disable WDT
                F81866ConfigRegisterWrite( 0xF5 , F81866ConfigRegisterRead(0xF5) & ~BIT5 ) ;
                // Clear WDT Status
                F81866ConfigRegisterWrite( 0xF5 , F81866ConfigRegisterRead(0xF5) | BIT6 ) ;

                // Configure WDT to Pulse Mode
                F81866ConfigRegisterWrite( 0xF5 , F81866ConfigRegisterRead(0xF5) | BIT4 ) ;
                // Configure WDT Pulse Width to 25ms
                F81866ConfigRegisterWrite( 0xF5 , F81866ConfigRegisterRead(0xF5) & ~(BIT1 + BIT0) ) ;
                F81866ConfigRegisterWrite( 0xF5 , F81866ConfigRegisterRead(0xF5) | BIT0 ) ;
                // Configure WDT Polarity to Low Active
                F81866ConfigRegisterWrite( 0xF5 , F81866ConfigRegisterRead(0xF5) & ~BIT2 ) ;
                // Configure WDT Reset via WDTRST#
                F81866ConfigRegisterWrite( 0xFA , F81866ConfigRegisterRead(0xFA) | BIT0 ) ;

                // Configure WDT Timer
                F81866ConfigRegisterWrite( 0xF6 , SetupData.F81866WdtTimer ) ;
                F81866ConfigRegisterWrite( 0xF5 , F81866ConfigRegisterRead(0xF5) & ~BIT3 ) ; // Configure Timer Unit : 1 Second

                // Enable WDT
                F81866ConfigRegisterWrite( 0xF5 , F81866ConfigRegisterRead(0xF5) | BIT5 ) ;
            break ;

            default :
            case 0 : // WDT Disabled
                F81866ConfigRegisterWrite( 0xF5 , F81866ConfigRegisterRead(0xF5) & ~BIT5 ) ;
            break ;
        }

        F81866ExitConfigMode() ;
    }
}
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   InitCK505ClockGen
//
// Description: This function is to initialiae CK505 clock generator.
//
// Input:       IN EFI_PEI_SERVICES             **PeiServices,
//              IN EFI_PEI_NOTIFY_DESCRIPTOR    *NotifyDescriptor,
//              IN VOID                         *NullPpi
//
// Output:      EFI_SUCCESS
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS InitCK505ClockGen
(
    IN EFI_PEI_SERVICES             **PeiServices,
    IN EFI_PEI_NOTIFY_DESCRIPTOR    *NotifyDescriptor,
    IN VOID                         *NullPpi
)
{
    EFI_STATUS        Status;
    EFI_PEI_SMBUS_PPI    *SmBus;
    EFI_SMBUS_DEVICE_ADDRESS    Address;
    UINT8        CK505TBL[] =  CLOCK_GENERATOR_SETTINGS;
    UINTN        Len = sizeof(CK505TBL);

    PEI_TRACE((TRACE_ALWAYS, PeiServices, "Program CK505 start.\n"));

    Address.SmbusDeviceAddress = CLOCK_GENERATOR_ADDRESS >> 1;

    Status = (*PeiServices)->LocatePpi( PeiServices,
			                &gPeiSmBusPpiGuid,
			                0,
			                NULL,
			                &SmBus );
    ASSERT_PEI_ERROR( PeiServices, Status);

    SmBus->Execute( PeiServices,
	            SmBus,
 	            Address,
  	            0,
   	            EfiSmbusWriteBlock,
	            0,
 	            &Len,
	            CK505TBL
 	           );

    PEI_TRACE((TRACE_ALWAYS, PeiServices, "Program CK505 end.\n"));

    return EFI_SUCCESS;
}


// Intel Platform Policy Override Sample Code >>>
//####//<AMI_PHDR_START>
//####//----------------------------------------------------------------------------
//####//
//####// Procedure:   OemPchPlatformPolicyOverride
//####//
//####// Description: This function is a sample code to guide user how to use
//####//              AMI_PEI_SB_OEM_PLATFORM_POLICY_OVERRIDE_PPI_GUID to override
//####//              Intel platform policy.
//####//
//####// Input:       IN EFI_PEI_SERVICES             **PeiServices,
//####//              IN EFI_PEI_NOTIFY_DESCRIPTOR    *NotifyDescriptor,
//####//              IN VOID                         *NullPpi
//####//
//####// Output:      EFI_SUCCESS
//####//
//####// Notes:
//####//----------------------------------------------------------------------------
//####//<AMI_PHDR_END>
//####EFI_STATUS OemPchPlatformPolicyOverride (
//####  IN EFI_PEI_SERVICES             **PeiServices,
//####  IN EFI_PEI_NOTIFY_DESCRIPTOR    *NotifyDescriptor,
//####  IN VOID                         *Ppi
//####  )
//####{
//####  EFI_STATUS              Status;
//####  PCH_PLATFORM_POLICY_PPI *PchPlatformPolicyPpi;
//####  //
//####  // Get platform policy settings through the PchPlatformPolicy PPI
//####  //
//####  Status = (**PeiServices).LocatePpi (
//####                            PeiServices,
//####                            &gOemPchPlatformPolicyOverridePpiGuid,
//####                            0,
//####                            NULL,
//####                            &PchPlatformPolicyPpi );
//####  ASSERT_PEI_ERROR (PeiServices, Status);

//####  PchPlatformPolicyPpi->SataConfig->SataTraceConfig->PortLength[0] = 0x35;
//####  PchPlatformPolicyPpi->SataConfig->SataTraceConfig->PortTopology[0] = 0;
//####  PchPlatformPolicyPpi->SataConfig->SataTraceConfig->PortLength[1] = 0x20;
//####  PchPlatformPolicyPpi->SataConfig->SataTraceConfig->PortTopology[1] = 1;
//####
//####  return Status;
//####}

//####//<AMI_PHDR_START>
//####//----------------------------------------------------------------------------
//####//
//####// Procedure:   OemSaPlatformPolicyOverride
//####//
//####// Description: This function is a sample code to guide user how to use
//####//              AMI_PEI_NB_OEM_PLATFORM_POLICY_OVERRIDE_PPI_GUID to override
//####//              Intel platform policy.
//####//
//####// Input:       IN EFI_PEI_SERVICES             **PeiServices,
//####//              IN EFI_PEI_NOTIFY_DESCRIPTOR    *NotifyDescriptor,
//####//              IN VOID                         *NullPpi
//####//
//####// Output:      EFI_SUCCESS
//####//
//####// Notes:
//####//----------------------------------------------------------------------------
//####//<AMI_PHDR_END>
//####EFI_STATUS OemPchPlatformPolicyOverride (
//####  IN EFI_PEI_SERVICES             **PeiServices,
//####  IN EFI_PEI_NOTIFY_DESCRIPTOR    *NotifyDescriptor,
//####  IN VOID                         *Ppi
//####  )
//####{
//####  EFI_STATUS              Status;
//####  PCH_PLATFORM_POLICY_PPI *SaPlatformPolicyPpi;
//####  //
//####  // Get platform policy settings through the SaPlatformPolicyPpi
//####  //
//####  Status = (**PeiServices).LocatePpi (
//####                            PeiServices,
//####                            &gOemSalatformPolicyOverridePpiGuid,
//####                            0,
//####                            NULL,
//####                            &SaPlatformPolicyPpi );
//####  ASSERT_PEI_ERROR (PeiServices, Status);

//####  SaPlatformPolicyPpi->PlatformData->FastBoot = 0;
//####  SaPlatformPolicyPpi->MemConfig->RemapEnable = 0;
//####
//####  return Status;
//####}
// Intel Platform Policy Override Sample Code <<<

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
