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
// $Header: /Alaska/BIN/IO/Fintek/F81216_Sec/F81216 Board/PeiIoTable.h 4     1/19/12 3:07a Elviscai $
//
// $Revision: 4 $
//
// $Date: 1/19/12 3:07a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/IO/Fintek/F81216_Sec/F81216 Board/PeiIoTable.h $
// 
// 4     1/19/12 3:07a Elviscai
// [TAG]  		EIPNONE
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	Base 0x200 generic IO decode fail
// [RootCause]  	1ST IO OemIoDecode will take 0x200 as GamePort
// [Solution]  	Change Com port IoDecodeBase from 0x200 to 0x240.
// 
// 3     7/04/11 3:23a Kasalinyi
// [Category]  	Improvement
// [Description]  	Update to new template
// [Files]  		OemIoDecode.c
// PeiIoTable.h
// DxeIoTable.h
// BSP.cif
// 
// 2     10/28/10 2:34a Mikes
// Change configure key with a token
// 
// 1     3/31/10 5:56a Fantasylai
// Initial release to F81216 just as a second IO

//*************************************************************************
//<AMI_FHDR_START>
//
// Name:    PeiIoTable.H
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
    IN  void            *LpcPciIo,
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
// Name:        F81216SEC_Decode_Table
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
IO_DECODE_DATA F81216SEC_Decode_Table[]={
    // -----------------------------
    //|  BaseAdd | UID  | Type | 
    // -----------------------------
    {F81216SEC_CONFIG_INDEX, 2, 0xFF},

    // !!!!Attention!!!!This is necessary
    //OEM_TODO//OEM_TODO//OEM_TODO//OEM_TODO
    {0x240, 0x40, 0xFF}, // 0x200~0x27f , open a IODecode section for UART1,2,3,4
    // Add more OEM IO decode below.
};

//<AMI_THDR_START>
//-------------------------------------------------------------------------
//
// Name:        F81216SEC_PEI_Init_Table
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
SIO_DATA F81216SEC_PEI_Init_Table[] = {
    // -----------------------------
    //|  Addr | DataMask  | DataValue | 
    // -----------------------------

    //---------------------------------------------------------------------
    // Enter Configuration Mode.
    //---------------------------------------------------------------------
    //AMI_TODO: 
    {F81216SEC_CONFIG_INDEX, 0xFF, F81216SEC_CONFIG_MODE_ENTER_VALUE},
    {F81216SEC_CONFIG_INDEX, 0xFF, F81216SEC_CONFIG_MODE_ENTER_VALUE},
    //---------------------------------------------------------------------
    // Before init all logical devices, program Global register if needed.
    //---------------------------------------------------------------------
    // Program clock setting in global registers
    // Bit0: 0/1 for CLKIN is 48Mhz/24MHz .
    {F81216SEC_CONFIG_INDEX, 0xFF, 0x25},
    {F81216SEC_CONFIG_DATA,  0xFE, 0x00 | F81216SEC_CLOCK},

    //---------------------------------------------------------------------
    // Initialize the Serial Port for debug useage. Default is COMA
    //---------------------------------------------------------------------
    //if first io have no comport debug,open it
/*
    #if defined(EFI_DEBUG) || (defined(Recovery_SUPPORT) && (SERIAL_RECOVERY_SUPPORT))
    #if (F81216SEC_SERIAL_PORT0_PRESENT)
    // Select device
    {F81216SEC_CONFIG_INDEX, 0xFF, F81216SEC_LDN_SEL_REGISTER},
    {F81216SEC_CONFIG_DATA,  0xFF, F81216SEC_LDN_UART0},
    // Program Base Addr 
    {F81216SEC_CONFIG_INDEX, 0xFF, F81216SEC_BASE1_LO_REGISTER},
    {F81216SEC_CONFIG_DATA,  0xFF ,0x60},
    {F81216SEC_CONFIG_INDEX, 0xFF, F81216SEC_BASE1_HI_REGISTER},
    {F81216SEC_CONFIG_DATA,  0xFF, 0x02},
    // Activate Device
    {F81216SEC_CONFIG_INDEX, 0xFF, F81216SEC_ACTIVATE_REGISTER},
    {F81216SEC_CONFIG_DATA,  0xFF, F81216SEC_ACTIVATE_VALUE},
    #endif // F81216SEC_SERIAL_PORT1_PRESENT
    #endif // #ifdef EFI_DEBUG
*/
    //---------------------------------------------------------------------
    // Disable non-used devices
    //---------------------------------------------------------------------

//--------------------------------------------------------------------------
// After init all logical devices, program Global register if needed.
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
// After init all logical devices,  Exit Configuration Mode.
//--------------------------------------------------------------------------
    {F81216SEC_CONFIG_INDEX, 0xFF, 0xAA},

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
