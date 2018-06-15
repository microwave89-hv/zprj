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
// $Header: /Alaska/BIN/IO/Fintek/F81866/F81866 Board/PeiIoTable.h 5     9/16/12 9:38p Elviscai $
//
// $Revision: 5 $
//
// $Date: 9/16/12 9:38p $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/IO/Fintek/F81866/F81866 Board/PeiIoTable.h $
// 
// 5     9/16/12 9:38p Elviscai
// [TAG]  		EIPNONE
// [Category]  	Bug Fix
// [Solution]  	Remove token control, LDN05h index FEh bit7& bit4 to ��0��
// as fixed.
// 
// 4     2/16/12 9:22p Elviscai
// [TAG]  		EIP82572
// [Category]  	Improvement
// [Description]  	Remove PS2 SWAP auto detection according Spec v0.13
// 
// 3     2/09/12 5:23a Kasalinyi
// [TAG]  		EIP82488 
// [Category]  	Improvement
// [Description]  	Fintek Workaround
// [Files]  		PeiIoTable.h
// 
// 2     2/03/12 1:29a Elviscai
// [TAG]  		EIP68967
// [Category]  	Improvement
// [Description]  	Correct UART/LPT/FDC muti-function pin definations.
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
// Name:    PeiIoTable.C
//
// Description: 
//  SIO init table in PEI phase. Any customers have to review below tables 
//  for themselves platform and make sure each initialization is necessary.
//
// Notes:
//
//<AMI_FHDR_END>
//*************************************************************************
#ifndef _PEIIoTable_H
#define _PEIIoTable_H
#ifdef __cplusplus
extern "C" {
#endif

//-------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
// Constants, Macros and Type Definitions
//-------------------------------------------------------------------------
typedef struct _IO_DECODE_DATA{
    UINT16          BaseAdd;
    //!!!Attention!!!If type is 0xFF, UID is a IO legth
    UINT8           UID;
    SIO_DEV_TYPE    Type;
} IO_DECODE_DATA;

typedef struct _SIO_DATA{
    UINT16           Addr;
    //AND mask value, 0xFF means register don't need AndMask and 
    //only write OrData8 to regisrer.
    UINT8           DataMask; 
    //OR mask value.  
    UINT8           DataValue;
} SIO_DATA;

// SIO DECODE list creation code must be in this order
typedef EFI_STATUS (IO_RANGE_DECODE)(
//    IN  void            *LpcPciIo,
    IN EFI_PCI_IO_PROTOCOL      *LpcPciIo,
    IN  UINT16          DevBase, 
    IN  UINT8           UID, 
    IN  SIO_DEV_TYPE    Type
); 

//-------------------------------------------------------------------------
//Variable, Prototype, and External Declarations
//-------------------------------------------------------------------------

//<AMI_THDR_START>
//-------------------------------------------------------------------------
//
// Name:        F81866_Decode_Table
//
// Description: 
//  Table filled with SIO IO resource to decode. It is used 
//  for PEI IO Decode function. For example:
//  1. Decode Index/data port
//  2. Decode KBC,FDC IO for recovery
//  3. Decode COM port for debug
//  4. Decode total IO base for runtime, pme, acpi, etc...
//  5. Decode more com ports wirh "generic IO range decode"
//
// Notes:
//  Attention! Cann't open 3F6(it was used by IDE controller.)
//
//-------------------------------------------------------------------------
//<AMI_THDR_END>
IO_DECODE_DATA F81866_Decode_Table[]={
    // -----------------------------
    //|  BaseAdd | UID  | Type | 
    // -----------------------------
    {F81866_CONFIG_INDEX, 2, 0xFF},
    //Below decode is for DEBUG Mode
    #if defined(EFI_DEBUG) || (defined(Recovery_SUPPORT) && (SERIAL_RECOVERY_SUPPORT))
    #if (F81866_SERIAL_PORT0_PRESENT)
    {F81866_SERIAL_PORT0_BASE_ADDRESS, 0, dsUART}, 
    #endif
    #endif
    //Below decode is for recovery mode
    #if defined(Recovery_SUPPORT) && (Recovery_SUPPORT) 
    #if (F81866_KEYBOARD_PRESENT)
    {0x60, 0, dsPS2K},                                  // KBC decode
    #endif
    #if (F81866_FLOPPY_PORT_PRESENT)
    {0x3F0, 0, dsFDC},                                  // FDC decode
    #endif
    #endif
    //Below decode is for SIO generic IO decode
    #if defined(F81866_TOTAL_BASE_ADDRESS) && (F81866_TOTAL_BASE_ADDRESS != 0)
    {F81866_TOTAL_BASE_ADDRESS, F81866_TOTAL_LENGTH, 0xFF},
    #endif
    // !!!!Attention!!!!This is necessary
    //OEM_TODO//OEM_TODO//OEM_TODO//OEM_TODO
    // If your com port number > 2 , you'd add more table for more com ports.
    {0x3E0, 0x10, 0xFF}, // 0x3E0~0x3F0 , open a IODecode section for UART3 4 
    {0x2E0, 0x20, 0xFF}, // 0x2E0~0x2FF , open a IODecode section for UART5 6
    // Add more OEM IO decode below.
};

//<AMI_THDR_START>
//-------------------------------------------------------------------------
//
// Name:        F81866_PEI_Init_Table
//
// Description: Table filled with SIO logical devices' register value. 
//              Only do the necessary initialization. For example:
//              1. Program clock and multi-pin setting in global registers
//              2. Program KBC,FDC IO for recovery
//              3. Program COM port for debug
//
// Notes:
//
//-------------------------------------------------------------------------
//<AMI_THDR_END>
SIO_DATA F81866_PEI_Init_Table[] = {
    // -----------------------------
    //|  Addr | DataMask  | DataValue | 
    // -----------------------------

    //---------------------------------------------------------------------
    // Enter Configuration Mode.
    //---------------------------------------------------------------------
    {F81866_CONFIG_INDEX, 0xFF, F81866_CONFIG_MODE_ENTER_VALUE},
    {F81866_CONFIG_INDEX, 0xFF, F81866_CONFIG_MODE_ENTER_VALUE},

    //---------------------------------------------------------------------
    // Before init all logical devices, program Global register if needed.
    //---------------------------------------------------------------------
    {F81866_CONFIG_INDEX, 0xFF, 0x26},
    {F81866_CONFIG_DATA,  0x3F, F81866_CLOCK << 6},
    //#if (F81866_SERIAL_PORT2_PRESENT)
	//{F81866_CONFIG_INDEX, 0xFF, 0x29},
    //{F81866_CONFIG_DATA,  0xCF, 0x30},
	//#endif
	//#if (F81866_SERIAL_PORT3_PRESENT)
	//{F81866_CONFIG_INDEX, 0xFF, 0x29},
    //{F81866_CONFIG_DATA,  0x3F, 0xC0},
	//#endif
    //#if (F81866_MOUSE_PRESENT)
	//{F81866_CONFIG_INDEX, 0xFF, 0x28},
    //{F81866_CONFIG_DATA,  0xEF, 0x00},
	//#endif
	//#if (F81866_SERIAL_PORT4_PRESENT)
	//{F81866_CONFIG_INDEX, 0xFF, 0x28},
    //{F81866_CONFIG_DATA,  0xB3, 0x0C},
	//#endif
	//#if (F81866_SERIAL_PORT5_PRESENT)
	//{F81866_CONFIG_INDEX, 0xFF, 0x28},
    //{F81866_CONFIG_DATA,  0xBC, 0x03},
	//#endif
	//#if (F81866_PARALLEL_PORT_PRESENT)
	//{F81866_CONFIG_INDEX, 0xFF, 0x28},
    //{F81866_CONFIG_DATA,  0xDF, 0x00},
	//{F81866_CONFIG_INDEX, 0xFF, 0x2B},
    //{F81866_CONFIG_DATA,  0xFC, 0x00},
	//#endif
	//#if (F81866_FLOPPY_PORT_PRESENT)
	//{F81866_CONFIG_INDEX, 0xFF, 0x28},
    //{F81866_CONFIG_DATA,  0xB0, 0x00},
	//#endif
	// Enable PS/2 KB/MS Wake-up Function
    //#if (F81866_KEYBOARD_PRESENT)
    //{F81866_CONFIG_INDEX, 0xFF, 0x2D},
    //{F81866_CONFIG_DATA,  0xF7, 0x0F},
    //#endif
	{F81866_CONFIG_INDEX, 0xFF, 0x27},
    {F81866_CONFIG_DATA,  0xF3, 0x00}, // GPIO_PROG_SEL = 00b
	{F81866_CONFIG_INDEX, 0xFF, 0x28},
    {F81866_CONFIG_DATA,  0x80, 0x6F}, 
	{F81866_CONFIG_INDEX, 0xFF, 0x27},
    {F81866_CONFIG_DATA,  0xF3, 0x04}, // GPIO_PROG_SEL = 01b
	{F81866_CONFIG_INDEX, 0xFF, 0x28},
    {F81866_CONFIG_DATA,  0xFC, 0x00}, 
	{F81866_CONFIG_INDEX, 0xFF, 0x27},
    {F81866_CONFIG_DATA,  0xFE, 0x00}, // CLK_TUNE_PROG_EN = 0b
	{F81866_CONFIG_INDEX, 0xFF, 0x29},
    {F81866_CONFIG_DATA,  0xFF, 0xF0}, 
	{F81866_CONFIG_INDEX, 0xFF, 0x2B},
    {F81866_CONFIG_DATA,  0xE3, 0x00}, 
	{F81866_CONFIG_INDEX, 0xFF, 0x27},
    {F81866_CONFIG_DATA,  0xF2, 0x00}, // GPIO_PROG_SEL = 00b , CLK_TUNE_PROG_EN = 0b
	{F81866_CONFIG_INDEX, 0xFF, 0x2C},
    {F81866_CONFIG_DATA,  0xE0, 0x0F}, 
	{F81866_CONFIG_INDEX, 0xFF, 0x27},
    {F81866_CONFIG_DATA,  0xF2, 0x04}, // GPIO_PROG_SEL = 01b , CLK_TUNE_PROG_EN = 0b
	{F81866_CONFIG_INDEX, 0xFF, 0x2C},
    {F81866_CONFIG_DATA,  0x10, 0x6F}, 
	{F81866_CONFIG_INDEX, 0xFF, 0x27},
    {F81866_CONFIG_DATA,  0xF2, 0x08}, // GPIO_PROG_SEL = 10b , CLK_TUNE_PROG_EN = 0b
	{F81866_CONFIG_INDEX, 0xFF, 0x2C},
    {F81866_CONFIG_DATA,  0xFF, 0x01}, 

    //---------------------------------------------------------------------
    // Initialize the Serial Port for debug useage. Default is COMA
    //---------------------------------------------------------------------
    #if defined(EFI_DEBUG) || (defined(Recovery_SUPPORT) && (SERIAL_RECOVERY_SUPPORT))
    #if (F81866_SERIAL_PORT0_PRESENT)
    // Select device
    {F81866_CONFIG_INDEX, 0xFF, F81866_LDN_SEL_REGISTER},
    {F81866_CONFIG_DATA,  0xFF, F81866_LDN_UART1},
    // Program Base Addr 
    {F81866_CONFIG_INDEX, 0xFF, F81866_BASE1_LO_REGISTER},
    {F81866_CONFIG_DATA,  0xFF, (UINT8)(F81866_SERIAL_PORT0_BASE_ADDRESS & 0xFF)},
    {F81866_CONFIG_INDEX, 0xFF, F81866_BASE1_HI_REGISTER},
    {F81866_CONFIG_DATA,  0xFF, (UINT8)(F81866_SERIAL_PORT0_BASE_ADDRESS >> 8)},
    // Activate Device
    {F81866_CONFIG_INDEX, 0xFF, F81866_ACTIVATE_REGISTER},
    {F81866_CONFIG_DATA,  0xFF, F81866_ACTIVATE_VALUE},
    #endif // F81866_SERIAL_PORT0_PRESENT
    #endif // #ifdef EFI_DEBUG

    //---------------------------------------------------------------------
    // Initialize the KeyBoard and floppy controller for Recovery
    //---------------------------------------------------------------------
    #if defined(Recovery_SUPPORT) && (Recovery_SUPPORT)
    #if (F81866_KEYBOARD_PRESENT)
    // Seclect device KEYBOARD
    {F81866_CONFIG_INDEX, 0xFF, F81866_LDN_SEL_REGISTER},
    {F81866_CONFIG_DATA,  0xFF, F81866_LDN_PS2K},
    // Program Base Addr
    {F81866_CONFIG_INDEX, 0xFF, F81866_BASE1_HI_REGISTER},
    {F81866_CONFIG_DATA,  0xFF, 0x00},
    {F81866_CONFIG_INDEX, 0xFF, F81866_BASE1_LO_REGISTER},
    {F81866_CONFIG_DATA,  0xFF, 0x60},
    // Program Interrupt
    {F81866_CONFIG_INDEX, 0xFF, F81866_IRQ1_REGISTER},
    {F81866_CONFIG_DATA,  0xFF, 0x01},
    // Activate Device
    {F81866_CONFIG_INDEX, 0xFF, F81866_ACTIVATE_REGISTER},
    {F81866_CONFIG_DATA,  0xFF, F81866_ACTIVATE_VALUE},
    #endif //F81866_KEYBOARD_PRESENT

    #if (F81866_FLOPPY_PORT_PRESENT)
    // Seclect device FLOPPY
    {F81866_CONFIG_INDEX, 0xFF, F81866_LDN_SEL_REGISTER},
    {F81866_CONFIG_DATA,  0xFF, F81866_LDN_FDC},
    // Program Base Addr
    {F81866_CONFIG_INDEX, 0xFF, F81866_BASE1_HI_REGISTER},
    {F81866_CONFIG_DATA,  0xFF, 0x03},
    {F81866_CONFIG_INDEX, 0xFF, F81866_BASE1_LO_REGISTER},
    {F81866_CONFIG_DATA,  0xFF, 0xF0},
    // Program Interrupt
    {F81866_CONFIG_INDEX, 0xFF, F81866_IRQ1_REGISTER},
    {F81866_CONFIG_DATA,  0xFF, 0x06},
    // Activate Device
    {F81866_CONFIG_INDEX, 0xFF, F81866_ACTIVATE_REGISTER},
    {F81866_CONFIG_DATA,  0xFF, F81866_ACTIVATE_VALUE},
    #endif //F81866_FLOPPY_PORT_PRESENT
    #endif //#if defined(Recovery_SUPPORT) && (Recovery_SUPPORT == 1)

    //---------------------------------------------------------------------
    // Program and initialize some logical device if needed.
    //---------------------------------------------------------------------
    // Seclect device KEYBOARD
    {F81866_CONFIG_INDEX, 0xFF, F81866_LDN_SEL_REGISTER},
    {F81866_CONFIG_DATA,  0xFF, F81866_LDN_PS2K},
    // >>EIP82488 [Fintek Workaround]:system will hangs up during RAID1 reboot aging with PS2KB 
    // >>EIPNONE LDN05h index FEh bit7& bit4 to "0".
    {F81866_CONFIG_INDEX, 0xFF, 0xFE},
    {F81866_CONFIG_DATA,  0x63, 0x0C},//set bit2,bit3=1 1
    // >>EIPNONE
    // <<EIP82488 
    //---------------------------------------------------------------------
    // After init all logical devices, program Global register if needed.
    //---------------------------------------------------------------------

    //---------------------------------------------------------------------
    // After init all logical devices,  Exit Configuration Mode.
    //---------------------------------------------------------------------
    {F81866_CONFIG_INDEX, 0xFF, F81866_CONFIG_MODE_EXIT_VALUE},
};

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif //_PEIIoTable_H
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

