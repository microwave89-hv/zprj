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
// $Header: /Alaska/BIN/IO/Fintek/F81866/F81866 Board/DxeIoTable.h 1     7/20/11 4:22a Kasalinyi $
//
// $Revision: 1 $
//
// $Date: 7/20/11 4:22a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/IO/Fintek/F81866/F81866 Board/DxeIoTable.h $
// 
// 1     7/20/11 4:22a Kasalinyi
// [Category]  	Improvement
// [Description]  	Initial Porting
// [Files]  		BSP.cif
// OemIoDecode.c
// PeiIoTable.h
// DxeIoTable.h
// F81866HwmOemHooks.c
// F81866SmartFan.c
// 
// 4     3/21/11 9:44p Mikes
// Seperate the core and oem job
//
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:    DxeIoTable.C
//
// Description: 
//  SIO init table in DXE phase. Any customers have to review below tables 
//  for themselves platform and make sure each initialization is necessary.
//
// Notes:
//  In all tables, only fill with necessary setting. Don't fill with default
//
//<AMI_FHDR_END>
//*************************************************************************
#ifndef _DXEIoTable_H
#define _DXEIoTable_H
#ifdef __cplusplus
extern "C" {
#endif
//-------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
// Constants, Macros and Type Definitions
//-------------------------------------------------------------------------
typedef struct _DXE_DEVICE_INIT_DATA{
    UINT16      Reg16;
    UINT8       AndData8;   // 0xFF means register don't need AndMask
                            // only write OrData8 to regisrer.
    UINT8       OrData8;
} DXE_DEVICE_INIT_DATA;

//-------------------------------------------------------------------------
//Variable, Prototype, and External Declarations
//-------------------------------------------------------------------------

//<AMI_THDR_START>
//-------------------------------------------------------------------------
//
// Name:        DXE_XXX_Init_Table
//
// Description: 
//  Table filled with SIO GPIO,PME,HWM, etc. logical devices' setting
//  For example:
//  1. GPIO will define the GPIO pin useage
//  2. PME will power management control
//  3. HWM will set temperature, fan, voltage and start control.
//
// Notes:
//
//-------------------------------------------------------------------------
//<AMI_THDR_END>

DXE_DEVICE_INIT_DATA   DXE_COM_Mode_Init_Table[] = {
    // -----------------------------
    //| Reg16 | AndData8  | OrData8  | 
    // -----------------------------
    // OEM_TODO: Base on OEM board.
    // Program COM RS485/RS232 Mode Registers.
	{0xF0, 0xCF, (F81866_COM1_RS485_Mode << 4)| (F81866_COM1_RS485_RTS_INV << 5)},	//make no effect when com1 disabled
	{0xF0, 0xCF, (F81866_COM2_RS485_Mode << 4)| (F81866_COM2_RS485_RTS_INV << 5)},	//make no effect when com2 disabled
	{0xF0, 0xCF, (F81866_COM3_RS485_Mode << 4)| (F81866_COM3_RS485_RTS_INV << 5)},	//make no effect when com3 disabled
	{0xF0, 0xCF, (F81866_COM4_RS485_Mode << 4)| (F81866_COM4_RS485_RTS_INV << 5)},	//make no effect when com4 disabled
	{0xF0, 0xCF, (F81866_COM5_RS485_Mode << 4)| (F81866_COM5_RS485_RTS_INV << 5)},	//make no effect when com5 disabled
	{0xF0, 0xCF, (F81866_COM6_RS485_Mode << 4)| (F81866_COM6_RS485_RTS_INV << 5)},	//make no effect when com6 disabled
};

//-------------------------------------------------------------------------
// HWM registers init table.
//-------------------------------------------------------------------------
#if F81866_HWM_PRESENT
DXE_DEVICE_INIT_DATA   DXE_HWM_Init_Table_After_Active[] = {

    // -----------------------------
    //| Reg16 | AndData8  | OrData8  | 
    // -----------------------------
	// Configuration Setting
    {0x01, 0xF8, 0x03},  // Configuration Register ? Index 01h

	// PECI/TSI/SMBus Setting
#if (F81866_PECI_SUPPORT)
	{0x0A, 0xDE, (F81866_INTEL_SEL << 5) | F81866_PECI_EN },
	{0x09, 0x01, F81866_I2C_ADDR & 0xFE },
#endif
#if (F81866_IBEX_SUPPORT)
	{0x0A, 0xDD, (F81866_INTEL_SEL << 5) | (F81866_IBEX_EN << 1)},
	{0x08, 0x01, F81866_SMBUS_ADDR & 0xFE},
	{0xEE, 0xFF, 0x41},
	{0xED, 0xFF, 0x40},
#endif

	//PECI 3.0 & Temperture Setting
	{0x6B, 0xF9, (F81866_T2_MODE << 2) | (F81866_T1_MODE << 1) },

	//Fan type Setting	
#if F81866_SMF_PRESENT
	{0x94, 0xC0, (FAN3_TYPE<<4)|(FAN2_TYPE<<2)|FAN1_TYPE },
#endif
}; //DXE_HWM_Init_Table


// Define a table for BootScriptTable of SIO space
UINT8   DXE_HWM_SIO_BootScript_Table[] = {
    0x01,0x08,0x09,0x0A,0x0D,0x6B,0x94,0xEE,0xED
};
#endif 

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif //_DXEIoTable_H
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

