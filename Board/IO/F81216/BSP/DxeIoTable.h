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
// $Header: /Alaska/BIN/IO/Fintek/F81216_Sec/F81216 Board/DxeIoTable.h 2     7/04/11 3:23a Kasalinyi $
//
// $Revision: 2 $
//
// $Date: 7/04/11 3:23a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/IO/Fintek/F81216_Sec/F81216 Board/DxeIoTable.h $
// 
// 2     7/04/11 3:23a Kasalinyi
// [Category]  	Improvement
// [Description]  	Update to new template
// [Files]  		OemIoDecode.c
// PeiIoTable.h
// DxeIoTable.h
// BSP.cif
// 
// 1     3/31/10 5:56a Fantasylai
// Initial release to F81216 just as a second IO

//*************************************************************************
//<AMI_FHDR_START>
//
// Name:    DxeIoTable.H
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




