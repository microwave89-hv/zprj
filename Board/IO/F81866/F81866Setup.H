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
// $Header: /Alaska/BIN/IO/Fintek/F81866/F81866Setup.H 1     7/20/11 4:22a Kasalinyi $
//
// $Revision: 1 $
//
// $Date: 7/20/11 4:22a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/IO/Fintek/F81866/F81866Setup.H $
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
// 3     3/21/11 9:41p Mikes
// seperate the core and oem job
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:  <F81866Setup.H>
//
// Description: GUID or structure Of Setup related Routines.
//
//<AMI_FHDR_END>
//*************************************************************************

#ifndef _F81866SETUP_H_
#define _F81866SETUP_H_
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

LDX_XV_DATA(FDC)

LDX_XV_DATA(COMA)

LDX_XV_DATA(COMB)

LDX_XV_DATA(COMC)

LDX_XV_DATA(COMD)

LDX_XV_DATA(COME)

LDX_XV_DATA(COMF)

LDX_XV_DATA(LPT)

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

typedef struct {
    UINT16      Token;  // String token value
    UINT8       Type;   // For what? Temperature, Fan, Voltage...
    UINT16      Value;  // Monitor value
    UINT8       OddPos; // Value precision
} HWM_DATA;

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

