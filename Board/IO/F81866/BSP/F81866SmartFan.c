//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2008, American Megatrends, Inc.            **
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
// $Header: /Alaska/BIN/IO/Fintek/F81866/F81866 Board/F81866SmartFan.c 1     7/20/11 4:23a Kasalinyi $Revision: 
//
// $Date:
//*************************************************************************
// Revision History
// ----------------
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:  <F81866SmartFan.c>
//
// Description: This is related to individual Smart Fan functions.
//
//<AMI_FHDR_END>
//*************************************************************************
#include <Efi.h>
#include <Token.h>
#include <AmiLib.h>
#include <Setup.h>
#include <AmiDxeLib.h>
#include <Protocol\BootScriptSave.h>
#define HWM_CONFIG_INDEX        F81866_HWM_BASE_ADDRESS+5
#define HWM_CONFIG_DATA         F81866_HWM_BASE_ADDRESS+6
SETUP_DATA                      SetupData;
static EFI_EVENT                gEvtReadyToBoot = NULL;
static EFI_GUID                 gEfiBootScriptSaveGuid = EFI_BOOT_SCRIPT_SAVE_GUID;

typedef	struct _DXE_SMF_INIT_DATA{
	UINT8 			Reg8;
	UINT8 			AndData8;
	UINT8 			OrData8;    
} DXE_SMF_INIT_DATA;

typedef	struct _S3_SAVE_DATA{
	UINT8 			Bank;
	UINT8 			Reg8;  
} S3_SAVE_DATA;
//----------------------------------------------------------------------------------------------
// smart system fan registers need init AfterActivate. !!!AfterActivate
//----------------------------------------------------------------------------------------------
#define IDX_FAN_MODE       0
#define IDX_TEMP_HYS       1
#define IDX_FAN_SPEED_MSB  2
#define IDX_FAN_SPEED_LSB  3
#define IDX_TEMP_BOUND1    4
#define IDX_TEMP_BOUND2    5
#define IDX_TEMP_BOUND3    6
#define IDX_TEMP_BOUND4    7
#define IDX_SPEED_SEG1     8
#define IDX_SPEED_SEG2     9
#define IDX_SPEED_SEG3     10
#define IDX_SPEED_SEG4     11
#define IDX_SPEED_SEG5     12
#define IDX_TEMP_SRCSEL    13

DXE_SMF_INIT_DATA   DXE_FAN1_INIT_TABLE[] = {
    {0x96, 0xFC, 0x00},
    {0x98, 0xF0, 0x02},
    {0xA2, 0xFF, 0x00},
    {0xA3, 0xFF, 0x00},
    {0xA6, 0xFF, 0x00},
    {0xA7, 0xFF, 0x00},
    {0xA8, 0xFF, 0x00},
    {0xA9, 0XFF, 0x00},
    {0xAA, 0xFF, 0xFF},
    {0xAB, 0xFF, 0x00},
    {0xAC, 0xFF, 0x00},
    {0xAD, 0xFF, 0x00},
    {0xAE, 0xFF, 0x00},
    {0xAF, 0xFC, 0x00},
};

DXE_SMF_INIT_DATA   DXE_FAN2_INIT_TABLE[] = {
	{0x96, 0xF3, 0x00},
    {0x98, 0x0F, 0x20},
	{0xB2, 0xFF, 0x00},
	{0xB3, 0xFF, 0x00},
	{0xB6, 0xFF, 0x00},
	{0xB7, 0xFF, 0x00},
	{0xB8, 0xFF, 0x00},
	{0xB9, 0XFF, 0x00},
	{0xBA, 0xFF, 0xFF},
	{0xBB, 0xFF, 0x00},
	{0xBC, 0xFF, 0x00},
	{0xBD, 0xFF, 0x00},
	{0xBE, 0xFF, 0x00},
	{0xBF, 0xFC, 0x00},
};

DXE_SMF_INIT_DATA   DXE_FAN3_INIT_TABLE[] = {
	{0x96, 0xCF, 0x00},
	{0x99, 0xF0, 0x02},
	{0xC2, 0xFF, 0x00},
	{0xC3, 0xFF, 0x00},
	{0xC6, 0xFF, 0x00},
	{0xC7, 0xFF, 0x00},
	{0xC8, 0xFF, 0x00},
	{0xC9, 0XFF, 0x00},
	{0xCA, 0xFF, 0xFF},
	{0xCB, 0xFF, 0x00},
	{0xCC, 0xFF, 0x00},
	{0xCD, 0xFF, 0x00},
	{0xCE, 0xFF, 0x00},
	{0xCF, 0xFC, 0x00},
};

S3_SAVE_DATA HwmS3SaveRegisterTbl[] = {
// ----------------------
//| Bank | Reg8 | 
// ----------------------
    {0x00,0x94},
    {0x00,0x96},
    {0x00,0x98},
    {0x00,0xA2},
    {0x00,0xA3},
    {0x00,0xA6},
    {0x00,0xA7},
    {0x00,0xA8},
    {0x00,0xA9},
    {0x00,0xAA},
    {0x00,0xAB},
    {0x00,0xAC},
    {0x00,0xAD},
    {0x00,0xAE},
    {0x00,0xAF},
    {0x00,0xB2},
    {0x00,0xB3},
    {0x00,0xB6},
    {0x00,0xB7},
    {0x00,0xB8},
    {0x00,0xB9},
    {0x00,0xBA},
    {0x00,0xBB},
    {0x00,0xBC},
    {0x00,0xBD},
    {0x00,0xBE},
    {0x00,0xBF},
    {0x00,0xC2},
    {0x00,0xC3},
    {0x00,0xC6},
    {0x00,0xC7},
    {0x00,0xC8},
    {0x00,0xC9},
    {0x00,0xCA},
    {0x00,0xCB},
    {0x00,0xCC},
    {0x00,0xCD},
    {0x00,0xCE},
    {0x00,0xCF},
};
//--------------------------------------------------------------------------
// Definition of smart fan functions
//--------------------------------------------------------------------------
VOID F81866SmartFunction (VOID);
static VOID SmartFanFuncStart(VOID);
static VOID F81866_SMF1_INIT(void);
static VOID F81866_SMF2_INIT(void);
static VOID F81866_SMF3_INIT(void);
VOID F81866_FAN_Full();
static void F81866_SMF_WRITE_CFG(DXE_SMF_INIT_DATA DXE_SMF_MODEx_Table);
static EFI_STATUS HwmCallbackReadyToBoot(
    IN  EFI_EVENT Event,
    IN  VOID    *Context);
//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure:    F81866SmartFunction
//
// Description:    This function initializes the IT8783 in BDS phase
//
// Input:        
//      IN      EFI_HANDLE              ImageHandle
//      IN      EFI_SYSTEM_TABLE        SystemTable
//
// Output:      Status
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID F81866SmartFunction (VOID)
{
    EFI_STATUS      Status = EFI_SUCCESS;
    UINTN           Size = sizeof(SETUP_DATA);
    EFI_GUID        SetupGuid = SETUP_GUID;

    //Get Setup variable
    Status=pRS->GetVariable( L"Setup", &SetupGuid, NULL, &Size, &SetupData);
    if(Status != EFI_SUCCESS) return;

    //Init the smart fan function
    if(SetupData.SmartFanEnable)  
        SmartFanFuncStart();
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure:    SmartFanFuncStart
//
// Description:    This function start to initialize the smart fan function
//
// Input:        NULL
//
//
// Output:      NULL
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
static VOID SmartFanFuncStart(VOID)
{
    EFI_STATUS      Status;
    //--------------------------------------------------------------------------
    // Before speed control, program neccessary registers if needed.
    //--------------------------------------------------------------------------
   
    //--------------------------------------------------------------------------
    // Start to program the smart fan mode
    //--------------------------------------------------------------------------
    F81866_SMF1_INIT();
    F81866_SMF2_INIT();
//    F81866_SMF3_INIT(); // Zprj Not Suported FAN3
    F81866_FAN_Full();

    //Create event for boot script
    Status = CreateReadyToBootEvent(
        TPL_NOTIFY,
         HwmCallbackReadyToBoot,
        NULL,
        &gEvtReadyToBoot
    );
    ASSERT_EFI_ERROR(Status);
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure:    F81866_SMF1_INIT
//
// Description:    This function do smart fan1 config
//
// Input:        NULL
//
//
// Output:      NULL
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
void  F81866_SMF1_INIT(VOID)
{
    UINT8   i, temp;
	switch (SetupData.Fan1SmartFanMode) {
    case 0:
    // Manual RPM Mode
      DXE_FAN1_INIT_TABLE[ IDX_FAN_MODE ].OrData8 = 0x02;//mode
      DXE_FAN1_INIT_TABLE[ IDX_FAN_SPEED_MSB ].OrData8 = (UINT8)(1500000/SetupData.Fan1Mode0FixedSpeed >> 8);//mode
      DXE_FAN1_INIT_TABLE[ IDX_FAN_SPEED_LSB ].OrData8 = (UINT8)(1500000/SetupData.Fan1Mode0FixedSpeed & 0xFF);//mode
    break;
    case 1:
      // Manual Duty Mode
      DXE_FAN1_INIT_TABLE[ IDX_FAN_MODE ].OrData8 = 0x03;//mode
      DXE_FAN1_INIT_TABLE[ IDX_FAN_SPEED_LSB ].OrData8 = (UINT8)SetupData.Fan1Mode1FixedDuty*0xFF/100;//mode
    break;
    case 2:
      // Auto RPM Mode
      DXE_FAN1_INIT_TABLE[ IDX_FAN_MODE ].OrData8 = 0x00;//mode
      DXE_FAN1_INIT_TABLE[ IDX_TEMP_HYS ].OrData8 = 0x02; // Set hysteresis as 2
      DXE_FAN1_INIT_TABLE[ IDX_TEMP_BOUND1 ].OrData8 = SetupData.Fan1Mode2AutoRpmT1;
      DXE_FAN1_INIT_TABLE[ IDX_TEMP_BOUND2 ].OrData8 = SetupData.Fan1Mode2AutoRpmT2;
      DXE_FAN1_INIT_TABLE[ IDX_TEMP_BOUND3 ].OrData8 = SetupData.Fan1Mode2AutoRpmT3;
      DXE_FAN1_INIT_TABLE[ IDX_TEMP_BOUND4 ].OrData8 = SetupData.Fan1Mode2AutoRpmT4; 
      DXE_FAN1_INIT_TABLE[ IDX_SPEED_SEG1 ].OrData8 = (UINT8)((100-SetupData.Fan1Mode2AutoRpmF1)*32/SetupData.Fan1Mode2AutoRpmF1); 
      DXE_FAN1_INIT_TABLE[ IDX_SPEED_SEG2 ].OrData8 = (UINT8)((100-SetupData.Fan1Mode2AutoRpmF2)*32/SetupData.Fan1Mode2AutoRpmF2);
      DXE_FAN1_INIT_TABLE[ IDX_SPEED_SEG3 ].OrData8 = (UINT8)((100-SetupData.Fan1Mode2AutoRpmF3)*32/SetupData.Fan1Mode2AutoRpmF3);       
      DXE_FAN1_INIT_TABLE[ IDX_SPEED_SEG4 ].OrData8 = (UINT8)((100-SetupData.Fan1Mode2AutoRpmF4)*32/SetupData.Fan1Mode2AutoRpmF4);  
      DXE_FAN1_INIT_TABLE[ IDX_SPEED_SEG5 ].OrData8 = (UINT8)((100-SetupData.Fan1Mode2AutoRpmF5)*32/SetupData.Fan1Mode2AutoRpmF5);  
      DXE_FAN1_INIT_TABLE[ IDX_TEMP_SRCSEL ].OrData8 = SetupData.Fan1TempSrc;
    break;
    case 3:
      // Auto Duty-Cycle Mode
      DXE_FAN1_INIT_TABLE[ IDX_FAN_MODE ].OrData8 = 0x01;//mode
      DXE_FAN1_INIT_TABLE[ IDX_TEMP_HYS ].OrData8 = 0x02; // Set hysteresis as 2      
      DXE_FAN1_INIT_TABLE[ IDX_TEMP_BOUND1 ].OrData8 = SetupData.Fan1Mode3AutoDutyT1;
      DXE_FAN1_INIT_TABLE[ IDX_TEMP_BOUND2 ].OrData8 = SetupData.Fan1Mode3AutoDutyT2;
      DXE_FAN1_INIT_TABLE[ IDX_TEMP_BOUND3 ].OrData8 = SetupData.Fan1Mode3AutoDutyT3;
      DXE_FAN1_INIT_TABLE[ IDX_TEMP_BOUND4 ].OrData8 = SetupData.Fan1Mode3AutoDutyT4; 
      DXE_FAN1_INIT_TABLE[ IDX_SPEED_SEG1 ].OrData8 = (UINT8)(SetupData.Fan1Mode3AutoDutyF1*0xFF/100); 
      DXE_FAN1_INIT_TABLE[ IDX_SPEED_SEG2 ].OrData8 = (UINT8)(SetupData.Fan1Mode3AutoDutyF2*0xFF/100); 
      DXE_FAN1_INIT_TABLE[ IDX_SPEED_SEG3 ].OrData8 = (UINT8)(SetupData.Fan1Mode3AutoDutyF3*0xFF/100); 
      DXE_FAN1_INIT_TABLE[ IDX_SPEED_SEG4 ].OrData8 = (UINT8)(SetupData.Fan1Mode3AutoDutyF4*0xFF/100);   
      DXE_FAN1_INIT_TABLE[ IDX_SPEED_SEG5 ].OrData8 = (UINT8)(SetupData.Fan1Mode3AutoDutyF5*0xFF/100);   
      DXE_FAN1_INIT_TABLE[ IDX_TEMP_SRCSEL ].OrData8 = SetupData.Fan1TempSrc;
    break;
    default:
    break;
    }
    for(i=0; i<( (sizeof(DXE_FAN1_INIT_TABLE))/(sizeof(DXE_SMF_INIT_DATA)) ); i++) {
        IoWrite8(HWM_CONFIG_INDEX, DXE_FAN1_INIT_TABLE[i].Reg8 ); 
        if(DXE_FAN1_INIT_TABLE[i].AndData8 == 0xFF) {
            temp = DXE_FAN1_INIT_TABLE[i].OrData8;
            } else {
            temp = IoRead8(HWM_CONFIG_DATA);
            temp &= DXE_FAN1_INIT_TABLE[i].AndData8;
            temp |= DXE_FAN1_INIT_TABLE[i].OrData8;
        }
        IoWrite8(HWM_CONFIG_DATA, temp); 
    }
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure:    F81866_SMF2_INIT
//
// Description:    This function do smart fan2 config
//
// Input:        NULL
//
//
// Output:      NULL
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
void    F81866_SMF2_INIT(VOID)
{
    UINT8   i, temp;
	switch (SetupData.Fan2SmartFanMode) {
    case 0:
    // Manual RPM Mode
      DXE_FAN2_INIT_TABLE[ IDX_FAN_MODE ].OrData8 = (0x02 << 2);//mode
      DXE_FAN2_INIT_TABLE[ IDX_FAN_SPEED_MSB ].OrData8 = (UINT8)(1500000/SetupData.Fan2Mode0FixedSpeed >> 8);//mode
      DXE_FAN2_INIT_TABLE[ IDX_FAN_SPEED_LSB ].OrData8 = (UINT8)(1500000/SetupData.Fan2Mode0FixedSpeed & 0xFF);//mode
    break;
    case 1:
      // Manual Duty Mode
      DXE_FAN2_INIT_TABLE[ IDX_FAN_MODE ].OrData8 = (0x03 << 2);//mode
      DXE_FAN2_INIT_TABLE[ IDX_FAN_SPEED_LSB ].OrData8 = (UINT8)SetupData.Fan2Mode1FixedDuty*0xFF/100;//mode
    break;
    case 2:
      // Auto RPM Mode
      DXE_FAN2_INIT_TABLE[ IDX_FAN_MODE ].OrData8 = 0x00;//mode
      DXE_FAN2_INIT_TABLE[ IDX_TEMP_HYS ].OrData8 = (0x02 << 4); // Set hysteresis as 2
      DXE_FAN2_INIT_TABLE[ IDX_TEMP_BOUND1 ].OrData8 = SetupData.Fan2Mode2AutoRpmT1;
      DXE_FAN2_INIT_TABLE[ IDX_TEMP_BOUND2 ].OrData8 = SetupData.Fan2Mode2AutoRpmT2;
      DXE_FAN2_INIT_TABLE[ IDX_TEMP_BOUND3 ].OrData8 = SetupData.Fan2Mode2AutoRpmT3;
      DXE_FAN2_INIT_TABLE[ IDX_TEMP_BOUND4 ].OrData8 = SetupData.Fan2Mode2AutoRpmT4; 
      DXE_FAN2_INIT_TABLE[ IDX_SPEED_SEG1 ].OrData8 = (UINT8)((100-SetupData.Fan2Mode2AutoRpmF1)*32/SetupData.Fan2Mode2AutoRpmF1); 
      DXE_FAN2_INIT_TABLE[ IDX_SPEED_SEG2 ].OrData8 = (UINT8)((100-SetupData.Fan2Mode2AutoRpmF2)*32/SetupData.Fan2Mode2AutoRpmF2);
      DXE_FAN2_INIT_TABLE[ IDX_SPEED_SEG3 ].OrData8 = (UINT8)((100-SetupData.Fan2Mode2AutoRpmF3)*32/SetupData.Fan2Mode2AutoRpmF3);       
      DXE_FAN2_INIT_TABLE[ IDX_SPEED_SEG4 ].OrData8 = (UINT8)((100-SetupData.Fan2Mode2AutoRpmF4)*32/SetupData.Fan2Mode2AutoRpmF4);  
      DXE_FAN2_INIT_TABLE[ IDX_SPEED_SEG5 ].OrData8 = (UINT8)((100-SetupData.Fan2Mode2AutoRpmF5)*32/SetupData.Fan2Mode2AutoRpmF5);  
      DXE_FAN2_INIT_TABLE[ IDX_TEMP_SRCSEL ].OrData8 = SetupData.Fan2TempSrc;
    break;
    case 3:
      // Auto Duty-Cycle Mode
      DXE_FAN2_INIT_TABLE[ IDX_FAN_MODE ].OrData8 = (0x01 << 2);//mode
      DXE_FAN2_INIT_TABLE[ IDX_TEMP_HYS ].OrData8 = (0x02 << 4); // Set hysteresis as 2
      DXE_FAN2_INIT_TABLE[ IDX_TEMP_BOUND1 ].OrData8 = SetupData.Fan2Mode3AutoDutyT1;
      DXE_FAN2_INIT_TABLE[ IDX_TEMP_BOUND2 ].OrData8 = SetupData.Fan2Mode3AutoDutyT2;
      DXE_FAN2_INIT_TABLE[ IDX_TEMP_BOUND3 ].OrData8 = SetupData.Fan2Mode3AutoDutyT3;
      DXE_FAN2_INIT_TABLE[ IDX_TEMP_BOUND4 ].OrData8 = SetupData.Fan2Mode3AutoDutyT4; 
      DXE_FAN2_INIT_TABLE[ IDX_SPEED_SEG1 ].OrData8 = (UINT8)(SetupData.Fan2Mode3AutoDutyF1*0xFF/100); 
      DXE_FAN2_INIT_TABLE[ IDX_SPEED_SEG2 ].OrData8 = (UINT8)(SetupData.Fan2Mode3AutoDutyF2*0xFF/100); 
      DXE_FAN2_INIT_TABLE[ IDX_SPEED_SEG3 ].OrData8 = (UINT8)(SetupData.Fan2Mode3AutoDutyF3*0xFF/100); 
      DXE_FAN2_INIT_TABLE[ IDX_SPEED_SEG4 ].OrData8 = (UINT8)(SetupData.Fan2Mode3AutoDutyF4*0xFF/100);   
      DXE_FAN2_INIT_TABLE[ IDX_SPEED_SEG5 ].OrData8 = (UINT8)(SetupData.Fan2Mode3AutoDutyF5*0xFF/100);   
      DXE_FAN2_INIT_TABLE[ IDX_TEMP_SRCSEL ].OrData8 = SetupData.Fan2TempSrc;
    break;
    default:
    break;
    }
    for(i=0; i<( (sizeof(DXE_FAN2_INIT_TABLE))/(sizeof(DXE_SMF_INIT_DATA)) ); i++) {
        IoWrite8(HWM_CONFIG_INDEX, DXE_FAN2_INIT_TABLE[i].Reg8 ); 
        if(DXE_FAN2_INIT_TABLE[i].AndData8 == 0xFF) {
            temp = DXE_FAN2_INIT_TABLE[i].OrData8;
            } else {
            temp = IoRead8(HWM_CONFIG_DATA);
            temp &= DXE_FAN2_INIT_TABLE[i].AndData8;
            temp |= DXE_FAN2_INIT_TABLE[i].OrData8;
        }
        IoWrite8(HWM_CONFIG_DATA, temp); 
    }
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure:    F81866_SMF3_INIT
//
// Description:    This function do smart fan3 config
//
// Input:        NULL
//
//
// Output:      NULL
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
void    F81866_SMF3_INIT(VOID)
{
    UINT8   i, temp;
	switch (SetupData.Fan3SmartFanMode) {
    case 0:
    // Manual RPM Mode
      DXE_FAN3_INIT_TABLE[ IDX_FAN_MODE ].OrData8 = (0x02 << 4);//mode
      DXE_FAN3_INIT_TABLE[ IDX_FAN_SPEED_MSB ].OrData8 = (UINT8)(1500000/SetupData.Fan3Mode0FixedSpeed >> 8);//mode
      DXE_FAN3_INIT_TABLE[ IDX_FAN_SPEED_LSB ].OrData8 = (UINT8)(1500000/SetupData.Fan3Mode0FixedSpeed & 0xFF);//mode
    break;
    case 1:
      // Manual Duty Mode
      DXE_FAN3_INIT_TABLE[ IDX_FAN_MODE ].OrData8 = (0x03 << 4);//mode
      DXE_FAN3_INIT_TABLE[ IDX_FAN_SPEED_LSB ].OrData8 = (UINT8)SetupData.Fan3Mode1FixedDuty*0xFF/100;//mode
    break;
    case 2:
      // Auto RPM Mode
      DXE_FAN3_INIT_TABLE[ IDX_FAN_MODE ].OrData8 = 0x00;//mode
      DXE_FAN3_INIT_TABLE[ IDX_TEMP_HYS ].OrData8 = 0x02; // Set hysteresis as 2
      DXE_FAN3_INIT_TABLE[ IDX_TEMP_BOUND1 ].OrData8 = SetupData.Fan3Mode2AutoRpmT1;
      DXE_FAN3_INIT_TABLE[ IDX_TEMP_BOUND2 ].OrData8 = SetupData.Fan3Mode2AutoRpmT2;
      DXE_FAN3_INIT_TABLE[ IDX_TEMP_BOUND3 ].OrData8 = SetupData.Fan3Mode2AutoRpmT3;
      DXE_FAN3_INIT_TABLE[ IDX_TEMP_BOUND4 ].OrData8 = SetupData.Fan3Mode2AutoRpmT4; 
      DXE_FAN3_INIT_TABLE[ IDX_SPEED_SEG1 ].OrData8 = (UINT8)((100-SetupData.Fan3Mode2AutoRpmF1)*32/SetupData.Fan3Mode2AutoRpmF1); 
      DXE_FAN3_INIT_TABLE[ IDX_SPEED_SEG2 ].OrData8 = (UINT8)((100-SetupData.Fan3Mode2AutoRpmF2)*32/SetupData.Fan3Mode2AutoRpmF2);
      DXE_FAN3_INIT_TABLE[ IDX_SPEED_SEG3 ].OrData8 = (UINT8)((100-SetupData.Fan3Mode2AutoRpmF3)*32/SetupData.Fan3Mode2AutoRpmF3);       
      DXE_FAN3_INIT_TABLE[ IDX_SPEED_SEG4 ].OrData8 = (UINT8)((100-SetupData.Fan3Mode2AutoRpmF4)*32/SetupData.Fan3Mode2AutoRpmF4);  
      DXE_FAN3_INIT_TABLE[ IDX_SPEED_SEG5 ].OrData8 = (UINT8)((100-SetupData.Fan3Mode2AutoRpmF5)*32/SetupData.Fan3Mode2AutoRpmF5);  
      DXE_FAN3_INIT_TABLE[ IDX_TEMP_SRCSEL ].OrData8 = SetupData.Fan3TempSrc;
    break;
    case 3:
      // Auto Duty-Cycle Mode
      DXE_FAN3_INIT_TABLE[ IDX_FAN_MODE ].OrData8 = (0x01 << 4);//mode
      DXE_FAN3_INIT_TABLE[ IDX_TEMP_HYS ].OrData8 = 0x02; // Set hysteresis as 2      
      DXE_FAN3_INIT_TABLE[ IDX_TEMP_BOUND1 ].OrData8 = SetupData.Fan3Mode3AutoDutyT1;
      DXE_FAN3_INIT_TABLE[ IDX_TEMP_BOUND2 ].OrData8 = SetupData.Fan3Mode3AutoDutyT2;
      DXE_FAN3_INIT_TABLE[ IDX_TEMP_BOUND3 ].OrData8 = SetupData.Fan3Mode3AutoDutyT3;
      DXE_FAN3_INIT_TABLE[ IDX_TEMP_BOUND4 ].OrData8 = SetupData.Fan3Mode3AutoDutyT4; 
      DXE_FAN3_INIT_TABLE[ IDX_SPEED_SEG1 ].OrData8 = (UINT8)(SetupData.Fan3Mode3AutoDutyF1*0xFF/100); 
      DXE_FAN3_INIT_TABLE[ IDX_SPEED_SEG2 ].OrData8 = (UINT8)(SetupData.Fan3Mode3AutoDutyF2*0xFF/100); 
      DXE_FAN3_INIT_TABLE[ IDX_SPEED_SEG3 ].OrData8 = (UINT8)(SetupData.Fan3Mode3AutoDutyF3*0xFF/100); 
      DXE_FAN3_INIT_TABLE[ IDX_SPEED_SEG4 ].OrData8 = (UINT8)(SetupData.Fan3Mode3AutoDutyF4*0xFF/100);   
      DXE_FAN3_INIT_TABLE[ IDX_SPEED_SEG5 ].OrData8 = (UINT8)(SetupData.Fan3Mode3AutoDutyF5*0xFF/100);   
      DXE_FAN3_INIT_TABLE[ IDX_TEMP_SRCSEL ].OrData8 = SetupData.Fan3TempSrc;
    break;
    default:
    break;
    }
    for(i=0; i<( (sizeof(DXE_FAN3_INIT_TABLE))/(sizeof(DXE_SMF_INIT_DATA)) ); i++) {
        IoWrite8(HWM_CONFIG_INDEX, DXE_FAN3_INIT_TABLE[i].Reg8 ); 
        if(DXE_FAN3_INIT_TABLE[i].AndData8 == 0xFF) {
            temp = DXE_FAN3_INIT_TABLE[i].OrData8;
            } else {
            temp = IoRead8(HWM_CONFIG_DATA);
            temp &= DXE_FAN3_INIT_TABLE[i].AndData8;
            temp |= DXE_FAN3_INIT_TABLE[i].OrData8;
        }
        IoWrite8(HWM_CONFIG_DATA, temp); 
    }
}

void F81866_FAN_Full(VOID)
{
  // Full Speed 
  // Manual Duty Mode
#if defined(F81866_SMF_SUPPORT) && (F81866_SMF_SUPPORT == 1)
  UINT8   i, temp;
#endif
  
//#if defined(F81866_SMF1_SUPPORT) && (F81866_SMF1_SUPPORT == 1)
  DXE_FAN1_INIT_TABLE[ IDX_FAN_MODE ].OrData8 = 0x03;//mode
  DXE_FAN1_INIT_TABLE[ IDX_FAN_SPEED_LSB ].OrData8 = 0xFF;
  
  for(i=0; i<( (sizeof(DXE_FAN1_INIT_TABLE))/(sizeof(DXE_SMF_INIT_DATA)) ); i++) {
      IoWrite8(HWM_CONFIG_INDEX, DXE_FAN1_INIT_TABLE[i].Reg8 ); 
      if(DXE_FAN1_INIT_TABLE[i].AndData8 == 0xFF) {
          temp = DXE_FAN1_INIT_TABLE[i].OrData8;
          } else {
          temp = IoRead8(HWM_CONFIG_DATA);
          temp &= DXE_FAN1_INIT_TABLE[i].AndData8;
          temp |= DXE_FAN1_INIT_TABLE[i].OrData8;
      }
      IoWrite8(HWM_CONFIG_DATA, temp); 
  }  
//#endif

//#if defined(F81866_SMF2_SUPPORT) && (F81866_SMF2_SUPPORT == 1)
  DXE_FAN2_INIT_TABLE[ IDX_FAN_MODE ].OrData8 = 0x0C;//mode
  DXE_FAN2_INIT_TABLE[ IDX_FAN_SPEED_LSB ].OrData8 = 0xFF;
  
  for(i=0; i<( (sizeof(DXE_FAN2_INIT_TABLE))/(sizeof(DXE_SMF_INIT_DATA)) ); i++) {
      IoWrite8(HWM_CONFIG_INDEX, DXE_FAN2_INIT_TABLE[i].Reg8 ); 
      if(DXE_FAN2_INIT_TABLE[i].AndData8 == 0xFF) {
          temp = DXE_FAN2_INIT_TABLE[i].OrData8;
          } else {
          temp = IoRead8(HWM_CONFIG_DATA);
          temp &= DXE_FAN2_INIT_TABLE[i].AndData8;
          temp |= DXE_FAN2_INIT_TABLE[i].OrData8;
      }
      IoWrite8(HWM_CONFIG_DATA, temp); 
  }  
//#endif

// Zprj Not Supported FAN3
//#if defined(F81866_SMF3_SUPPORT) && (F81866_SMF3_SUPPORT == 1)
//  DXE_FAN3_INIT_TABLE[ IDX_FAN_MODE ].OrData8 = 0x30;//mode
//  DXE_FAN3_INIT_TABLE[ IDX_FAN_SPEED_LSB ].OrData8 = 0xFF;
//  
//  for(i=0; i<( (sizeof(DXE_FAN3_INIT_TABLE))/(sizeof(DXE_SMF_INIT_DATA)) ); i++) {
//      IoWrite8(HWM_CONFIG_INDEX, DXE_FAN3_INIT_TABLE[i].Reg8 ); 
//      if(DXE_FAN3_INIT_TABLE[i].AndData8 == 0xFF) {
//          temp = DXE_FAN3_INIT_TABLE[i].OrData8;
//          } else {
//          temp = IoRead8(HWM_CONFIG_DATA);
//          temp &= DXE_FAN3_INIT_TABLE[i].AndData8;
//          temp |= DXE_FAN3_INIT_TABLE[i].OrData8;
//      }
//      IoWrite8(HWM_CONFIG_DATA, temp); 
//  }  
//#endif
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure:    HwmCallbackReadyToBoot
//
// Description:    This function save registers for S3
//
// Input:        NULL
//
//
// Output:      NULL
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
static EFI_STATUS HwmCallbackReadyToBoot(
    IN  EFI_EVENT Event,
    IN  VOID    *Context)
{
    EFI_BOOT_SCRIPT_SAVE_PROTOCOL *bss;
    EFI_STATUS      Status;
    UINT8           bank_reg,bank,r,v,i;

    Status = pBS->LocateProtocol(&gEfiBootScriptSaveGuid,NULL,&bss);
    if(EFI_ERROR(Status)) return Status;

    // record the register from table into boot script 
    for (i=0; i < ((sizeof(HwmS3SaveRegisterTbl))/(sizeof(S3_SAVE_DATA))); i++) {
        bank = HwmS3SaveRegisterTbl[i].Bank;
        bank_reg = 0x4e;
        r = HwmS3SaveRegisterTbl[i].Reg8;

        //select bank
        IoWrite8(HWM_CONFIG_INDEX, bank_reg);
        IoWrite8(HWM_CONFIG_DATA, bank);
        //select register to read actual data
        IoWrite8(HWM_CONFIG_INDEX, r);
        v = IoRead8(HWM_CONFIG_DATA);
        //save to s3 bootscrip table
        BOOT_SCRIPT_S3_IO_WRITE_MACRO(bss,EfiBootScriptWidthUint8,HWM_CONFIG_INDEX, 1, &bank_reg);
        BOOT_SCRIPT_S3_IO_WRITE_MACRO(bss,EfiBootScriptWidthUint8,HWM_CONFIG_DATA, 1, &bank);

        BOOT_SCRIPT_S3_IO_WRITE_MACRO(bss,EfiBootScriptWidthUint8,HWM_CONFIG_INDEX, 1, &r);
        BOOT_SCRIPT_S3_IO_WRITE_MACRO(bss,EfiBootScriptWidthUint8,HWM_CONFIG_DATA, 1, &v);
    }

    return Status;
}


//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2008, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

