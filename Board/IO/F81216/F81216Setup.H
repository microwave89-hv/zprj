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
// $Header: /Alaska/BIN/IO/Fintek/F81216_Sec/F81216Setup.H 3     7/04/11 3:22a Kasalinyi $
//
// $Revision: 3 $
//
// $Date: 7/04/11 3:22a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/IO/Fintek/F81216_Sec/F81216Setup.H $
// 
// 3     7/04/11 3:22a Kasalinyi
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
// 2     10/28/10 2:30a Mikes
// Make code readable
// 
// 1     3/31/10 5:55a Fantasylai
// Initial release to F81216 just as a second IO
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:  <F81216Setup.H>
//
// Description: GUID or structure Of Setup related Routines.
//
//<AMI_FHDR_END>
//*************************************************************************

#ifndef _F81216SETUP_H_
#define _F81216SETUP_H_
#ifdef __cplusplus
extern "C" {
#endif
//-------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------
#include "token.h"
#include <Setup.h>
#include <SetupStrTokens.h>

//-------------------------------------------------------------------------
// Constants, Macros and Type Definitions
//-------------------------------------------------------------------------

//**********************************************************************//
//                        Belos is for SD files                         //
//**********************************************************************//
#define SIO_VAR_GUID \
    {0x560bf58a, 0x1e0d, 0x4d7e, 0x95, 0x3f, 0x29, 0x80, 0xa2, 0x61, 0xe0, 0x31}

#define AMI_SIO_VARSTORE(ldxn, PNPxxxx_n) \
varstore ldxn##_V_DATA,\
    key    = ldxn##_V_DATA_KEY,\
    name    = PNPxxxx_n##_VV,\
    guid    = SIO_VAR_GUID;\
varstore ldxn##_NV_DATA,\
    key    = ldxn##_NV_DATA_KEY,\
    name    = PNPxxxx_n##_NV,\
    guid    = SIO_VAR_GUID;

#define LDX_XV_DATA(ldxn) \
typedef struct {\
    UINT8        DevImplemented;\
    UINT16       DevBase1;\
    UINT16       DevBase2;\
    UINT8        DevIrq1;\
    UINT8        DevIrq2;\
    UINT8        DevDma1;\
    UINT8        DevDma2;\
} ldxn##_V_DATA;\
typedef struct {\
    UINT8        DevEnable;\
    UINT8        DevPrsId;\
    UINT8        DevMode;\
} ldxn##_NV_DATA;


#pragma pack(1)

#if F81216SEC_SERIAL_PORT0_PRESENT
LDX_XV_DATA(COMA2)
#endif

#if F81216SEC_SERIAL_PORT1_PRESENT
LDX_XV_DATA(COMB2)
#endif

#if F81216SEC_SERIAL_PORT2_PRESENT
LDX_XV_DATA(COMC2)
#endif

#if F81216SEC_SERIAL_PORT3_PRESENT
LDX_XV_DATA(COMD2)
#endif

#pragma pack()

//**********************************************************************//
//                    Below is for "xxSetup.c"                   //
//**********************************************************************//
#define STR_BUFFER_LENGTH   0x10
//Defination of function 
#define VOLTAGE             0x01
#define TEMPERATURE         0x02
#define FAN_SPEED           0x03

#define LEFT_JUSTIFY              0x01
#define PREFIX_SIGN               0x02
#define PREFIX_BLANK              0x04
#define COMMA_TYPE                0x08
#define LONG_TYPE                 0x10
#define PREFIX_ZERO               0x20

#define CHARACTER_NUMBER_FOR_VALUE 30

#pragma pack(1)

/*
typedef struct {
    UINT16      Token;  // String token value
    UINT8       Type;   // For what? Temperature, Fan, Voltage...
    UINT16      Value;  // Monitor value
    UINT8       OddPos; // Value precision
} HWM_DATA;
*/

#pragma pack()

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif

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
