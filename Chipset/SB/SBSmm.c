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
// $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/SBSmm.c 2     3/19/13 8:20a Scottyang $
//
// $Revision: 2 $
//
// $Date: 3/19/13 8:20a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/SBSmm.c $
// 
// 2     3/19/13 8:20a Scottyang
// [TAG]  		EIP118158
// [Category]  	Improvement
// [Description]  	Correct SBLib_CmosRead () offset.
// [Files]  		SmiHandlerPorting2.c, SBDxe.c, SBGeneric.c, SBSmm.c,
// SmiHandlerPorting.c
// 
// 1     2/08/12 8:24a Yurenlai
// Intel Lynx Point/SB eChipset initially releases.
// 
//*************************************************************************


//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:        SBSMM.C
//
// Description: This file contains code for SMM control - the
//              protocol defined by Framework
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>


// Module specific Includes
#include <Efi.h>
#include <token.h>
#include <HOB.h>
#include <DXE.h>
#include <AmiLib.h>
#include <AmiDxeLib.h>
#include <AmiCspLib.h>

// Used Protocols
#include <Protocol\PciRootBridgeIo.h>
#include <Protocol\BootScriptSave.h>
#include <Protocol\SmmAccess.h>
// Produced Protocols
#include <Protocol\SmmControl.h>
#if PI_SPECIFICATION_VERSION >= 0x0001000A
#include <Protocol\SmmControl2.h>
#endif

// Function Prototypes
typedef struct {
    UINT8          IoReg8;
    UINT32         Value32;
} PMIO_BOOT_SCRIPT_STRUCT;

EFI_STATUS
SBSMM_ClearSMI(
    IN EFI_SMM_CONTROL_PROTOCOL       *This,
    IN BOOLEAN                        Periodic OPTIONAL
);

VOID SBSMM_BootScript();

EFI_STATUS
SBSMM_TriggerSMI(
    IN EFI_SMM_CONTROL_PROTOCOL       *This,
    IN OUT INT8                       *ArgumentBuffer OPTIONAL,
    IN OUT UINTN                      *ArgumentBufferSize OPTIONAL,
    IN BOOLEAN                        Periodic OPTIONAL,
    IN UINTN                          ActivationInterval OPTIONAL
);

EFI_STATUS
SBSMM_GetRegisterInfo(
    IN EFI_SMM_CONTROL_PROTOCOL       *This,
    IN OUT EFI_SMM_CONTROL_REGISTER   *SmiRegister
);

VOID SaveSmiEnBeforeBoot (
    IN EFI_EVENT                    Event,
    IN VOID                         *Context
);

#if PI_SPECIFICATION_VERSION >= 0x0001000A
EFI_STATUS SBSMM_TriggerSMI2(
    IN CONST EFI_SMM_CONTROL2_PROTOCOL  *This,
    IN OUT UINT8                        *CommandPort       OPTIONAL,
    IN OUT UINT8                        *DataPort          OPTIONAL,
    IN BOOLEAN                          Periodic           OPTIONAL,
    IN UINTN                            ActivationInterval OPTIONAL
);

EFI_STATUS SBSMM_ClearSMI2(
    IN CONST EFI_SMM_CONTROL2_PROTOCOL  *This,
    IN BOOLEAN                          Periodic OPTIONAL
);
#endif

// GUID Definitions
EFI_GUID gEfiSmmAccessProtocolGuid   = EFI_SMM_ACCESS_PROTOCOL_GUID;
EFI_GUID gEfiSmmControlProtocolGuid  = EFI_SMM_CONTROL_PROTOCOL_GUID;


// Global variable declarations
//-extern EFI_BOOT_SCRIPT_SAVE_PROTOCOL  *gBootScriptSave;
EFI_SMM_ACCESS_PROTOCOL               *gSmmAccess;
EFI_SMM_CONTROL_PROTOCOL mEfiSmmControlProtocol =
{
    SBSMM_TriggerSMI,
    SBSMM_ClearSMI,
    SBSMM_GetRegisterInfo,
    0
};

EFI_SMM_CONTROL_PROTOCOL *gEfiSmmControlProtocol = NULL;

#if PI_SPECIFICATION_VERSION >= 0x0001000A
EFI_SMM_CONTROL2_PROTOCOL gEfiSmmControl2Protocol =
{
    SBSMM_TriggerSMI2,
    SBSMM_ClearSMI2,
    0
};
#endif

// Portable Constants

// Function Definition

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SBSMM_EnableSWSmi
//
// Description: This function programs the SB chipset registers to enable
//              S/W SMI generation
//
// Input:       None
//
// Output:      EFI_SUCCESS   Always
//
// Notes:       CHIPSET AND/OR BOARD PORTING NEEDED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
SBSMM_EnableSWSmi(VOID)
{
/*
    UINT32     Value32;

    SBSMM_ClearSMI(&mEfiSmmControlProtocol, FALSE);
    SBSMM_BootScript();

//Porting Required.  Include code to enable S/W SMI generation
    Value32 = IoRead32(PM_BASE_ADDRESS + ICH_IOREG_SMI_EN) | (BIT05 | BIT00);
    IoWrite32(PM_BASE_ADDRESS + ICH_IOREG_SMI_EN, Value32);       //Enable global SMIs.

    Value32 = 0x00002002B;
    BOOT_SCRIPT_S3_IO_WRITE_MACRO(gBootScriptSave,
                                  EfiBootScriptWidthUint32,
                                  PM_BASE_ADDRESS + ICH_IOREG_SMI_EN,
                                  1,
                                  &Value32);
//End Porting
*/

    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SBSMM_TriggerSMI
//
// Description: This function generates a software SMI by writing the provided
//              byte value into the software SMI generation register
//
// Input:       *This                 Pointer to the SMM control protocol
//              *ArgumentBuffer       Contains the value to be written to the
//                                    S/W SMI port. Currently supports byte only
//                                    and this is a optional pointer
//              *ArgumentBufferSize   Optional. Valid value is 1
//              Periodic              Boolean indicating the nature of generation
//              TRUE                  means periodic generation depending on
//                                    timing value provided in the next variable
//                                    CURRENTLY NOT SUPPORTED. EXPECTS FALSE
//              ActivationInterval    Optional. NOT SUPPORTED
//
// Output:      EFI_STATUS
//              EFI_SUCCESS           S/W SMI triggered successfully
//              EFI_INVALID_PARAMETER If Periodic is TRUE or when
//                                    (ArgumentBuffer is not NULL and
//                                    ArgumentBufferSize is not 1)
//
// Notes:       CHIPSET AND/OR BOARD PORTING NEEDED
//              Here is the control flow of this function:
//                1. If Periodic was TRUE, return EFI_INVALID_PARAMETER.
//                2. If ArgumentBuffer == NULL, use 0xFF as data.
//                3. If not NULL, if valid byte, use it as data. Otherwise
//                    return EFI_INVALID_PARAMETER.
//                4. Deactive any active SMI status.
//                5. Write the data to the SMI trigger port.
//                6. Return EFI_SUCCESS.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SBSMM_TriggerSMI(
    IN EFI_SMM_CONTROL_PROTOCOL   *This,
    IN OUT INT8                   *ArgumentBuffer OPTIONAL,
    IN OUT UINTN                  *ArgumentBufferSize OPTIONAL,
    IN BOOLEAN                    Periodic OPTIONAL,
    IN UINTN                      ActivationInterval OPTIONAL
)
{
    UINT8           Data;
    EFI_STATUS      Status = EFI_SUCCESS;

    if (Periodic)
        return EFI_INVALID_PARAMETER;

    if (ArgumentBuffer == NULL)
    {
        Data = 0xFF;                        // If no data given, use 0xFF to trigger SMI.
    }
    else
    {
        if (ArgumentBufferSize == NULL || *ArgumentBufferSize != 1)
            return EFI_INVALID_PARAMETER;     // Only able to send 1 byte.
        Data = *ArgumentBuffer;
    }

    // Porting Required.  Include code to generate S/W SMI
    WRITE_IO32_PM(ICH_IOREG_SMI_EN, (READ_IO32_PM(ICH_IOREG_SMI_EN) | (BIT5 | BIT0)));
    WRITE_IO8(SW_SMI_IO_ADDRESS, Data);          // This triggers SMI
    // Porting End

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SBSMM_ClearSMI
//
// Description: This function clears all SMI status registers and generates
//              End-of-SMI (EOS)
//
// Input:       *This     Pointer to the SMM control protocol
//              Periodic  Boolean indicating the nature of clearing
//              TRUE      means periodic SMI clearing
//                        CURRENTLY NOT SUPPORTED. EXPECTS FALSE
//
// Output:      EFI_STATUS
//              EFI_SUCCESS           SMI status successfully cleared
//              EFI_INVALID_PARAMETER If Periodic is TRUE
//
// Notes:       CHIPSET AND/OR BOARD PORTING NEEDED
//              Here is the control flow of this function:
//                1. If Periodic was TRUE, return EFI_INVALID_PARAMETER.
//                2. Clear SMI Status on all appropriate SMI status registers
//                3. Set EOS.
//                4. Return EFI_SUCCESS.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
SBSMM_ClearSMI(
    IN EFI_SMM_CONTROL_PROTOCOL     *This,
    IN BOOLEAN                      Periodic OPTIONAL
)
{

    if (Periodic) return EFI_INVALID_PARAMETER;

    // Porting Required.  Include code to clear software SMI status only
    WRITE_IO8_PM(ICH_IOREG_SMI_STS, 0x20); // 0x34


    //Set EOS
    SET_IO8_PM(ICH_IOREG_SMI_EN, BIT01);

    // Porting end

    return EFI_SUCCESS;
}

#if PI_SPECIFICATION_VERSION >= 0x0001000A
EFI_STATUS SBSMM_TriggerSMI2(
    IN CONST EFI_SMM_CONTROL2_PROTOCOL  *This,
    IN OUT UINT8                        *CommandPort       OPTIONAL,
    IN OUT UINT8                        *DataPort          OPTIONAL,
    IN BOOLEAN                          Periodic           OPTIONAL,
    IN UINTN                            ActivationInterval OPTIONAL
)
{
    EFI_STATUS Status = EFI_SUCCESS;
    UINTN DataSize = 1;
    UINT8 Data;

    if (Periodic)
        return EFI_INVALID_PARAMETER;

    if (CommandPort == NULL)
    {
        Data = 0xFF;                        // If no data given, use 0xFF to trigger SMI.
    }
    else
    {
        Data = *CommandPort;
    }

    Status = gEfiSmmControlProtocol->Trigger(gEfiSmmControlProtocol, &Data, &DataSize, FALSE, 0);

    return Status;
}

EFI_STATUS SBSMM_ClearSMI2(
    IN CONST EFI_SMM_CONTROL2_PROTOCOL  *This,
    IN BOOLEAN                          Periodic OPTIONAL
)
{
    if (Periodic)
        return EFI_INVALID_PARAMETER;

    gEfiSmmControlProtocol->Clear(gEfiSmmControlProtocol, FALSE);

    return EFI_SUCCESS;
}
#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SBSMM_BootScript
//
// Description: This function clears all SMI enables registers and generates
//              End-of-SMI (EOS) in Boot Script
//
// Input:       None
//
// Output:      None
//
// Notes:       CHIPSET AND/OR BOARD PORTING NEEDED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID SBSMM_BootScript(VOID)
{
/*
    UINT16          i;
    UINT16          j;

// 0x00-0x03
// 0x28-0x2B
// 0x2C-0x2F
// 0x20-0x23
// 0x24-0x27
// 0x38-0x3B
// 0x34-0x37
    PMIO_BOOT_SCRIPT_STRUCT PMIoBootScriptTbl[] = { \
        {ICH_IOREG_PM1_STS, 0x01000831},\
        {ICH_IOREG_GPE0_EN, 0},\
        {ICH_IOREG_GPE0_EN + 4, 0},\
        {ICH_IOREG_GPE0_STS, 0xFFFFFFFF},\
        {ICH_IOREG_GPE0_STS + 4, 0xFFFFFFFF},\
        {ICH_IOREG_ALT_GP_SMI_EN + 4, 0xFFFF0000},\
        {ICH_IOREG_SMI_STS, 0xFFFFFFF}};

    // Use boot script to do :
    // 1. Clear PM1 statuses except power button & RTC statuses and
    //    enable power button, OS will setup it as a wake event anyway.
    // 2. disable GPE enables.
    // 3. disable SMI enables and clear SMI statuses.
    // 4. Enable SCI (SCI_EN).

    j = sizeof(PMIoBootScriptTbl) / sizeof(PMIO_BOOT_SCRIPT_STRUCT);
    for (i = 0; i < j; i++)
        BOOT_SCRIPT_S3_IO_WRITE_MACRO( \
            gBootScriptSave, \
            EfiBootScriptWidthUint32, \
            PM_BASE_ADDRESS + PMIoBootScriptTbl[i].IoReg8,\
            1, \
            &PMIoBootScriptTbl[i].Value32 );


    // Enable SCI.
    i = 1;
    j = 0xffff;
    BOOT_SCRIPT_S3_IO_READ_WRITE_MACRO( \
        gBootScriptSave, \
        EfiBootScriptWidthUint16, \
        PM_BASE_ADDRESS + ICH_IOREG_PM1_CNT,
        &i, \
        &j );
*/
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SaveSmiEnBeforeBoot
//
// Description: This function uses boot script to all SMI enables before boot
//              to OS. 
//              
// Input:       Event   - Event of callback
//              Context - Context of callback.
//
// Output:      None
//
// Notes:       CHIPSET AND/OR BOARD PORTING NEEDED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID SaveSmiEnBeforeBoot (
    IN EFI_EVENT Event,
    IN VOID      *Context )
{
/*
    // Porting Required.
    UINT32  Buffer32;
    UINT32  PCIAdd;
    UINT8   Data8;

    // Remove SLP_SMI from boot script if needed.
    Buffer32 = READ_IO32_PM(ICH_IOREG_SMI_EN) & ~(BIT04 | BIT06);

    BOOT_SCRIPT_S3_IO_WRITE_MACRO( \
        gBootScriptSave, \
        EfiBootScriptWidthUint32, \
        PM_BASE_ADDRESS + ICH_IOREG_SMI_EN, \
        1, \
        &Buffer32 );


    // Save NMI2SMI_EN, TCO_TMR_HLT and TCO_LOCK
    Data8 = READ_IO8_TCO(ICH_IOREG_TCO1_CNT + 1) & (BIT01 | BIT03 | BIT04);
    BOOT_SCRIPT_S3_IO_WRITE_MACRO( \
        gBootScriptSave, \
        EfiBootScriptWidthUint8, \
        TCO_BASE_ADDRESS + ICH_IOREG_TCO1_CNT + 1, \
        1, \
        &Data8 );


    PCIAdd = EFI_SB_PCI_CFG_ADDRESS(LPC_BUS, LPC_DEVICE, LPC_FUNC, ICH_REG_LPC_VID);

    Data8 = READ_PCI8_SB(ICH_REG_GEN_PMCON_1);
    BOOT_SCRIPT_S3_PCI_CONFIG_WRITE_MACRO( \
        gBootScriptSave, \
        EfiPciIoWidthUint8, \
        EFI_SB_PCI_CFG_ADDRESS(LPC_BUS, LPC_DEVICE, LPC_FUNC, ICH_REG_GEN_PMCON_1), \
        1, \
        &Data8
    );

    Data8 = READ_PCI8_SB(ICH_REG_GEN_PMCON_3);
    Data8 &= ~(BIT01);
    BOOT_SCRIPT_S3_PCI_CONFIG_WRITE_MACRO( \
        gBootScriptSave, \
        EfiPciIoWidthUint8, \
        EFI_SB_PCI_CFG_ADDRESS(LPC_BUS, LPC_DEVICE, LPC_FUNC, ICH_REG_GEN_PMCON_3), \
        1, \
        &Data8
    );
*/

    // Porting End
    pBS->CloseEvent(Event);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SBSMM_GetRegisterInfo
//
// Description: This function returns the S/W SMI generation register and
//              its status register values
//
// Input:       *This         Pointer to the SMM control protocol
//              SmiRegister   Pointer to the SMM control register structure
//
// Output:      EFI_UNSUPPORTED
//
// Notes:       CHIPSET AND/OR BOARD PORTING NEEDED
//              1. Return EFI_UNSUPPORTED.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
SBSMM_GetRegisterInfo(
    IN EFI_SMM_CONTROL_PROTOCOL       *This,
    IN OUT EFI_SMM_CONTROL_REGISTER   *SmiRegister
)
{

    // Porting Required.  Include code to return I/O port to generate S/W SMI
    SmiRegister->SmiTriggerRegister = SW_SMI_IO_ADDRESS;
    SmiRegister->SmiDataRegister    = SW_SMI_IO_ADDRESS + 1;
    // Porting End

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   DisableAllSmi
//
// Description: This function disables all SMI's which can be caused by
//              SouthBridge, include global SMI.
//
// Input:       None
//
// Output:      None
//
// Notes:       CHIPSET AND/OR BOARD PORTING NEEDED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID DisableAllSmi(VOID)
{
    //--WRITE_IO16_PM(ICH_IOREG_PM1_EN, 0x0000);            // 0x02
    //--WRITE_IO32_PM(ICH_IOREG_GPE0_EN, 0x00000000);       // 0x2C
    //--WRITE_IO32_PM(ICH_IOREG_SMI_EN, 0x00000000);        // 0x30
    //--WRITE_IO32_PM(ICH_IOREG_ALT_GP_SMI_EN, 0x00000000); // 0x38
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SBSMM_Init
//
// Description: This function is invoked from SB DXE to initialize SMM
//              related stuff in NorthBridge and install appropriate
//              SMM protocols such as SMM Access & SMM Control
//
// Input:       ImageHandle   Image handle
//              SystemTable   Pointer to the system table
//
// Output:      Return Status based on errors that occurred while waiting for
//              time to expire.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
SbSmmInit(
    IN EFI_EVENT        Event,
    IN VOID             *Context
)
{
    EFI_STATUS Status;
    EFI_EVENT  mEvent;
    UINT8      Value;

    PROGRESS_CODE(DXE_SB_SMM_INIT);

    Status = pBS->LocateProtocol(&gEfiSmmControlProtocolGuid, NULL, &gEfiSmmControlProtocol);
    if (EFI_ERROR(Status))
    {
        Status = pBS->LocateProtocol(&gEfiSmmAccessProtocolGuid, NULL, &gSmmAccess);
        ASSERT_EFI_ERROR(Status);

        // Disable all SMI enables here
        DisableAllSmi();

        //Must read RTC Reg C to be able to clear SMM RTC alarm flag.
        Value = SBLib_CmosRead(0x0C);

        // Clear all SMI status here.
        //--WRITE_IO16_PM(ICH_IOREG_PM1_STS, 0xCF31);     // 0x00
        //--WRITE_IO32_PM(ICH_IOREG_GPE0_STS, 0xFFFFFFFF);     // 0x20
        //--WRITE_IO32_PM(ICH_IOREG_GPE0_STS + 4, 0xffffffff); // 0x24
        //--WRITE_IO16_PM(ICH_IOREG_ALT_GP_SMI_STS, 0xFFFF);   // 0x3A
        //--WRITE_IO16_PM(ICH_IOREG_DEVACT_STS, 0xFFFF);  // 0x44
        //--WRITE_IO16_TCO(ICH_IOREG_TCO1_STS, 0xFFFF);   // 0x04
        //--WRITE_IO16_TCO(ICH_IOREG_TCO2_STS, (0xFFFF));   // 0x06
        //--WRITE_IO32_PM(ICH_IOREG_SMI_STS, 0xFFFFFFFF); // 0x34

        // Enable S/W SMI Generation
        SBSMM_EnableSWSmi();

        Status = CreateReadyToBootEvent( TPL_NOTIFY, \
                                         SaveSmiEnBeforeBoot, \
                                         NULL, \
                                         &mEvent );
        ASSERT_EFI_ERROR(Status);

        Status = pBS->InstallMultipleProtocolInterfaces(
                   &TheImageHandle,
                   &gEfiSmmControlProtocolGuid,
                   &mEfiSmmControlProtocol,
#if PI_SPECIFICATION_VERSION >= 0x0001000A
                   &gEfiSmmControl2ProtocolGuid,
                   &gEfiSmmControl2Protocol,
#endif
                   NULL,
                   NULL
                   );
        ASSERT_EFI_ERROR(Status);
    }
    else
    {
#if PI_SPECIFICATION_VERSION >= 0x0001000A
        Status = pBS->InstallMultipleProtocolInterfaces(
                   &TheImageHandle,
                   &gEfiSmmControl2ProtocolGuid,
                   &gEfiSmmControl2Protocol,
                   NULL,
                   NULL
                   );
        ASSERT_EFI_ERROR(Status);
#endif
    }

    return Status;
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
