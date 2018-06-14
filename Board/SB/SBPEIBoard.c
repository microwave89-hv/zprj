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
// $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Board/SBPEIBoard.c 6     4/02/13 10:30a Scottyang $
//
// $Revision: 6 $
//
// $Date: 4/02/13 10:30a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Board/SBPEIBoard.c $
// 
// 6     4/02/13 10:30a Scottyang
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Follow Intel BIOS 114.4 GPIO setting at ULT platform.
// [Files]  		SB.sdl
// SBPEIBoard.c
// 
// 5     1/17/13 3:33a Scottyang
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Correct ULT GPIO's help message
// [Files]  		SB.sdl
// SBPEIBoard.c
// 
// 4     1/09/13 8:24a Scottyang
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Synchronous GPIO with Intel BIOS V104.2.
// [Files]  		SB.sdl
// SBPEIBoard.c
// 
// 3     11/08/12 7:15a Scottyang
// [TAG]  		None
// [Category]  	New Feature
// [Description]  	Add token "PROGRAM_GPIO_TYPE" for select ULT GPIO
// program function(token or array directly).
// [Files]  		SB.sdl, SBPEIBoard.c
// 
// 2     10/14/12 8:24a Scottyang
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	One rom for two chip and one chip. 
// [Files]  		SPPEIBoard.c, SB.sd, SBDxe.c, SBPEI.c, PCH.asl
// 
// 1     2/08/12 8:22a Yurenlai
// Intel Lynx Point/SB eChipset initially releases.
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:        SBPeiBoard.C
//
// Description: This file contains PEI stage board component code for
//              South Bridge.
//
//<AMI_FHDR_END>
//*************************************************************************

//----------------------------------------------------------------------------
// Include(s)
//----------------------------------------------------------------------------

#include <Efi.h>
#include <Pei.h>
#include <token.h>
#include <AmiLib.h>
#include <Ppi\CspLibPpi.h>
#include <Ppi\SBPPI.h>
#include <AmiCspLib.h>
#include "Sb.h"

//----------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//----------------------------------------------------------------------------
// Constant Definition(s)

// Macro Definition(s)

// Type Definition(s)

// Function Prototype(s)

//----------------------------------------------------------------------------
// Variable and External Declaration(s)
//----------------------------------------------------------------------------
// Variable Declaration(s)

// GUID Definition(s)

// PPI Definition(s)

// PPI that are installed

// PPI that are notified

// External Declaration(s)

// Function Definition(s)

//----------------------------------------------------------------------------

//-----------------------------------------------------------------------
// SB : GPIO Initialize Table
//-----------------------------------------------------------------------
AMI_GPIO_INIT_TABLE_STRUCT stSB_GPIODefaultInitTable[] =
{
//  { OFFSET, VALUE }
#include <SBGPIO.h>
};

AMI_GPIO_INIT_TABLE_STRUCT stSB_GPIODefaultULTInitTable[] =
{
#if defined (PROGRAM_GPIO_TYPE) && (PROGRAM_GPIO_TYPE == 1) && (ULT_SUPPORT == 1)
//  { OFFSET, VALUE }
    {0, ULT_GPIO_000},
    {1, ULT_GPIO_001},
    {2, ULT_GPIO_002},
    {3, ULT_GPIO_003},
    {4, ULT_GPIO_004},
    {5, ULT_GPIO_005},
    {6, ULT_GPIO_006},
    {7, ULT_GPIO_007},
    {8, ULT_GPIO_008},
    {9, ULT_GPIO_009},
    {10, ULT_GPIO_010},
    {11, ULT_GPIO_011},
    {12, ULT_GPIO_012},
    {13, ULT_GPIO_013},
    {14, ULT_GPIO_014},
    {15, ULT_GPIO_015},
    {16, ULT_GPIO_016},
    {17, ULT_GPIO_017},
    {18, ULT_GPIO_018},
    {19, ULT_GPIO_019},
    {20, ULT_GPIO_020},
    {21, ULT_GPIO_021},
    {22, ULT_GPIO_022},
    {23, ULT_GPIO_023},
    {24, ULT_GPIO_024},
    {25, ULT_GPIO_025},
    {26, ULT_GPIO_026},
    {27, ULT_GPIO_027},
    {28, ULT_GPIO_028},
    {29, ULT_GPIO_029},
    {30, ULT_GPIO_030},
    {31, ULT_GPIO_031},
    {32, ULT_GPIO_032},
    {33, ULT_GPIO_033},
    {34, ULT_GPIO_034},
    {35, ULT_GPIO_035},
    {36, ULT_GPIO_036},
    {37, ULT_GPIO_037},
    {38, ULT_GPIO_038},
    {39, ULT_GPIO_039},
    {40, ULT_GPIO_040},
    {41, ULT_GPIO_041},
    {42, ULT_GPIO_042},
    {43, ULT_GPIO_043},
    {44, ULT_GPIO_044},
    {45, ULT_GPIO_045},
    {46, ULT_GPIO_046},
    {47, ULT_GPIO_047},
    {48, ULT_GPIO_048},
    {49, ULT_GPIO_049},
    {50, ULT_GPIO_050},
    {51, ULT_GPIO_051},
    {52, ULT_GPIO_052},
    {53, ULT_GPIO_053},
    {54, ULT_GPIO_054},
    {55, ULT_GPIO_055},
    {56, ULT_GPIO_056},
    {57, ULT_GPIO_057},
    {58, ULT_GPIO_058},
    {59, ULT_GPIO_059},
    {60, ULT_GPIO_060},
    {61, ULT_GPIO_061},
    {62, ULT_GPIO_062},
    {63, ULT_GPIO_063},
    {64, ULT_GPIO_064},
    {65, ULT_GPIO_065},
    {66, ULT_GPIO_066},
    {67, ULT_GPIO_067},
    {68, ULT_GPIO_068},
    {69, ULT_GPIO_069},
    {70, ULT_GPIO_070},
    {71, ULT_GPIO_071},
    {72, ULT_GPIO_072},
    {73, ULT_GPIO_073},
    {74, ULT_GPIO_074},
    {75, ULT_GPIO_075},
    {76, ULT_GPIO_076},
    {77, ULT_GPIO_077},
    {78, ULT_GPIO_078},
    {79, ULT_GPIO_079},
    {80, ULT_GPIO_080},
    {81, ULT_GPIO_081},
    {82, ULT_GPIO_082},
    {83, ULT_GPIO_083},
    {84, ULT_GPIO_084},
    {85, ULT_GPIO_085},
    {86, ULT_GPIO_086},
    {87, ULT_GPIO_087},
    {88, ULT_GPIO_088},
    {89, ULT_GPIO_089},
    {90, ULT_GPIO_090},
    {91, ULT_GPIO_091},
    {92, ULT_GPIO_092},
    {93, ULT_GPIO_093},
    {94, ULT_GPIO_094},
    {95, ULT_GPIO_095},
#else
//  { OFFSET, VALUE("BIT0:GPIO USE Select - 0:Native Mode/1:GPIO Mode.;\BIT1:GPIO Input/Output Select.\BIT2:GPIO Level Select.\BIT3:GPIO Signal Invert(Only For GPIO_00~31).\BIT4:GPIO Blink Enable(Only For GPIO_00~31).\BIT5:GPIO Reset Select.\BIT6:GPIO OWN - 0:ACPI driver/ 1:GPIO driver \ BIT7:GPIO LEB - 0: Edge Mode/ 1: Level Mode \BIT8: GPIO DIS - 0: Input seneing enable/ 1: Iutput seneing disable \BIT9~10 - 00: none/ 01:pull down/ 10: pull up/ 11: invalid ") }
    {0, (IS_NOT_GPIO)|(OUTPUT_HIGH)|(GPIO_OWN_GPIO)},
    {1, (IS_NOT_GPIO)|(OUTPUT_HIGH)|(GPIO_OWN_GPIO)},
    {2, (IS_NOT_GPIO)|(OUTPUT_HIGH)|(GPIO_OWN_GPIO)},
    {3, (IS_NOT_GPIO)|(OUTPUT_HIGH)|(GPIO_OWN_GPIO)},
    {4, (IS_NOT_GPIO)|(OUTPUT_HIGH)|(GPIO_OWN_GPIO)},
    {5, (IS_NOT_GPIO)|(OUTPUT_HIGH)|(GPIO_OWN_GPIO)},
    {6, (IS_NOT_GPIO)|(OUTPUT_HIGH)|(GPIO_OWN_GPIO)},
    {7, (IS_NOT_GPIO)|(OUTPUT_HIGH)|(GPIO_OWN_GPIO)},
    {8, (IS_GPIO)|(IS_GPI)|(GPI_INV)|(GPI_LEB_LEVEL)|(GPIO_OWN_GPIO)},
    {9, (IS_GPIO)|(IS_GPI)|(GPI_LEB_LEVEL)|(GPIO_OWN_GPIO)},
    {10, (IS_GPIO)|(IS_GPI)|(GPI_INV)},
    {11, (IS_NOT_GPIO)|(OUTPUT_HIGH)|(GPI_LEB_LEVEL)|(GPIO_OWN_GPIO)},
    {12, (IS_NOT_GPIO)|(OUTPUT_HIGH)|(GPIO_OWN_GPIO)},
    {13, (IS_GPIO)|(OUTPUT_HIGH)|(GPI_NDIS_DISABLE)|(GPIO_OWN_GPIO)},
    {14, (IS_GPIO)|(IS_GPI)|(GPI_INV)|(GPIO_GPIWP_DOWN)|(GPIO_OWN_GPIO)},
    {15, (IS_GPIO)|(OUTPUT_LOW)|(GPI_NDIS_DISABLE)|(GPIO_OWN_GPIO)},
    {16, (IS_GPIO)|(OUTPUT_HIGH)|(GPI_NDIS_DISABLE)|(GPIO_OWN_GPIO)},
    {17, (IS_GPIO)|(IS_GPI)|(GPI_INV)|(GPI_LEB_LEVEL)|(GPIO_OWN_GPIO)},
    {18, (IS_NOT_GPIO)|(OUTPUT_HIGH)|(GPI_LEB_LEVEL)|(GPIO_OWN_GPIO)},
    {19, (IS_NOT_GPIO)|(OUTPUT_HIGH)|(GPIO_OWN_GPIO)},
    {20, (IS_NOT_GPIO)|(OUTPUT_HIGH)|(GPIO_OWN_GPIO)},
    {21, (IS_NOT_GPIO)|(OUTPUT_HIGH)|(GPIO_OWN_GPIO)},
    {22, (IS_GPIO)|(OUTPUT_LOW)|(GPI_NDIS_DISABLE)|(GPIO_OWN_GPIO)},
    {23, (IS_NOT_GPIO)|(OUTPUT_HIGH)|(GPIO_OWN_GPIO)},
    {24, (IS_GPIO)|(IS_GPI)|(GPIO_OWN_GPIO)|(GPIO_RESET)},
    {25, (IS_GPIO)|(OUTPUT_HIGH)|(GPI_NDIS_DISABLE)|(GPIO_OWN_GPIO)},
    {26, (IS_GPIO)|(IS_GPI)|(GPIO_OWN_GPIO)},
    {27, (IS_GPIO)|(IS_GPI)|(GPI_INV)|(GPI_LEB_LEVEL)},
    {28, (IS_GPIO)|(OUTPUT_LOW)|(GPI_NDIS_DISABLE)|(GPIO_OWN_GPIO)},
    {29, (IS_NOT_GPIO)|(OUTPUT_HIGH)|(GPIO_OWN_GPIO)},
    {30, (IS_NOT_GPIO)|(OUTPUT_HIGH)|(GPIO_OWN_GPIO)},
    {31, (IS_NOT_GPIO)|(OUTPUT_HIGH)|(GPIO_OWN_GPIO)},
    {32, (IS_NOT_GPIO)|(OUTPUT_HIGH)|(GPIO_OWN_GPIO)},
    {33, (IS_NOT_GPIO)|(OUTPUT_HIGH)|(GPIO_OWN_GPIO)},
    {34, (IS_GPIO)|(IS_GPI)|(GPI_INV)|(GPIO_OWN_GPIO)},
    {35, (IS_GPIO)|(IS_GPI)|(GPI_INV)|(OUTPUT_HIGH)},
    {36, (IS_GPIO)|(IS_GPI)|(GPI_INV)|(GPI_LEB_LEVEL)|(GPIO_OWN_GPIO)},
    {37, (IS_NOT_GPIO)|(OUTPUT_HIGH)|(GPIO_OWN_GPIO)},
    {38, (IS_NOT_GPIO)|(OUTPUT_HIGH)|(GPIO_OWN_GPIO)},
    {39, (IS_NOT_GPIO)|(OUTPUT_HIGH)|(GPIO_OWN_GPIO)},
    {40, (IS_NOT_GPIO)|(OUTPUT_HIGH)|(GPIO_OWN_GPIO)},
    {41, (IS_NOT_GPIO)|(OUTPUT_HIGH)|(GPIO_OWN_GPIO)},
    {42, (IS_NOT_GPIO)|(OUTPUT_HIGH)|(GPIO_OWN_GPIO)},
    {43, (IS_GPIO)|(OUTPUT_HIGH)|(GPI_NDIS_DISABLE)|(GPIO_OWN_GPIO)},
    {44, (IS_GPIO)|(OUTPUT_HIGH)|(GPI_NDIS_DISABLE)|(GPIO_OWN_GPIO)},
    {45, (IS_GPIO)|(IS_GPI)|(GPI_INV)|(GPI_LEB_LEVEL)|(GPIO_OWN_GPIO)},
    {46, (IS_GPIO)|(OUTPUT_HIGH)|(GPI_NDIS_DISABLE)|(GPIO_OWN_GPIO)},
    {47, (IS_GPIO)|(IS_GPI)|(GPI_INV)|(GPIO_OWN_GPIO)},
    {48, (IS_GPIO)|(OUTPUT_HIGH)|(GPI_NDIS_DISABLE)|(GPIO_OWN_GPIO)},
    {49, (IS_GPIO)|(OUTPUT_HIGH)|(GPIO_OWN_GPIO)},
    {50, (IS_GPIO)|(IS_GPI)|(GPI_LEB_LEVEL)|(GPIO_OWN_GPIO)},
    {51, (IS_GPIO)|(IS_GPI)|(GPI_INV)|(GPI_LEB_LEVEL)|(GPIO_OWN_GPIO)},
    {52, (IS_GPIO)|(OUTPUT_HIGH)|(GPI_NDIS_DISABLE)|(GPIO_OWN_GPIO)},
    {53, (IS_GPIO)|(IS_GPI)|(GPIO_OWN_GPIO)},
    {54, (IS_GPIO)|(IS_GPI)|(GPI_INV)|(GPI_LEB_LEVEL)|(GPIO_OWN_GPIO)},
    {55, (IS_GPIO)|(IS_GPI)|(GPI_LEB_LEVEL)|(GPIO_OWN_GPIO)},
    {56, (IS_GPIO)|(OUTPUT_HIGH)|(GPI_NDIS_DISABLE)|(GPIO_OWN_GPIO)},
    {57, (IS_GPIO)|(OUTPUT_LOW)|(GPI_NDIS_DISABLE)|(GPIO_OWN_GPIO)},
    {58, (IS_GPIO)|(IS_GPI)|(GPI_LEB_LEVEL)|(GPIO_OWN_GPIO)},
    {59, (IS_GPIO)|(OUTPUT_HIGH)|(GPI_NDIS_DISABLE)|(GPIO_OWN_GPIO)},
    {60, (IS_GPIO)|(OUTPUT_LOW)|(GPI_NDIS_DISABLE)|(GPIO_OWN_GPIO)},
    {61, (IS_NOT_GPIO)|(OUTPUT_HIGH)|(GPIO_OWN_GPIO)},
    {62, (IS_NOT_GPIO)|(OUTPUT_HIGH)|(GPIO_OWN_GPIO)},
    {63, (IS_NOT_GPIO)|(OUTPUT_HIGH)|(GPIO_OWN_GPIO)},
    {64, (IS_NOT_GPIO)|(OUTPUT_HIGH)|(GPIO_OWN_GPIO)},
    {65, (IS_NOT_GPIO)|(OUTPUT_HIGH)|(GPIO_OWN_GPIO)},
    {66, (IS_NOT_GPIO)|(OUTPUT_HIGH)|(GPIO_OWN_GPIO)},
    {67, (IS_NOT_GPIO)|(OUTPUT_HIGH)|(GPIO_OWN_GPIO)},
    {68, (IS_NOT_GPIO)|(OUTPUT_HIGH)|(GPIO_OWN_GPIO)},
    {69, (IS_NOT_GPIO)|(OUTPUT_HIGH)|(GPIO_OWN_GPIO)},
    {70, (IS_GPIO)|(OUTPUT_HIGH)|(GPIO_OWN_GPIO)},
    {71, (IS_NOT_GPIO)|(OUTPUT_HIGH)|(GPIO_OWN_GPIO)},
    {72, (IS_NOT_GPIO)|(OUTPUT_HIGH)|(GPIO_OWN_GPIO)},
    {73, (IS_NOT_GPIO)|(OUTPUT_HIGH)|(GPIO_OWN_GPIO)},
    {74, (IS_NOT_GPIO)|(OUTPUT_HIGH)|(GPIO_OWN_GPIO)},
    {75, (IS_NOT_GPIO)|(OUTPUT_HIGH)|(GPIO_OWN_GPIO)},
    {76, (IS_GPIO)|(OUTPUT_HIGH)|(GPI_NDIS_DISABLE)|(GPIO_OWN_GPIO)},
    {77, (IS_GPIO)|(OUTPUT_HIGH)|(GPI_NDIS_DISABLE)|(GPIO_OWN_GPIO)},
    {78, (IS_GPIO)|(IS_GPI)|(GPI_LEB_LEVEL)|(GPIO_OWN_GPIO)},
    {79, (IS_GPIO)|(IS_GPI)|(GPI_INV)|(GPI_LEB_LEVEL)|(GPIO_OWN_GPIO)},
    {80, (IS_GPIO)|(IS_GPI)|(GPI_LEB_LEVEL)|(GPIO_OWN_GPIO)},
    {81, (IS_NOT_GPIO)|(OUTPUT_HIGH)|(GPIO_OWN_GPIO)},
    {82, (IS_NOT_GPIO)|(OUTPUT_HIGH)|(GPIO_OWN_GPIO)},
    {83, (IS_GPIO)|(OUTPUT_LOW)|(GPI_NDIS_DISABLE)|(GPIO_OWN_GPIO)},
    {84, (IS_GPIO)|(OUTPUT_LOW)|(GPI_NDIS_DISABLE)|(GPIO_OWN_GPIO)},
    {85, (IS_GPIO)|(OUTPUT_LOW)|(GPI_NDIS_DISABLE)|(GPIO_OWN_GPIO)},
    {86, (IS_GPIO)|(OUTPUT_LOW)|(GPI_LEB_LEVEL)|(GPI_NDIS_DISABLE)|(GPIO_OWN_GPIO)},
    {87, (IS_GPIO)|(OUTPUT_LOW)|(GPI_NDIS_DISABLE)|(GPIO_OWN_GPIO)},
    {88, (IS_GPIO)|(OUTPUT_HIGH)|(GPI_NDIS_DISABLE)|(GPIO_OWN_GPIO)},
    {89, (IS_GPIO)|(OUTPUT_HIGH)|(GPI_NDIS_DISABLE)|(GPIO_OWN_GPIO)},
    {90, (IS_GPIO)|(OUTPUT_LOW)|(GPI_NDIS_DISABLE)|(GPIO_OWN_GPIO)},
    {91, (IS_NOT_GPIO)|(OUTPUT_HIGH)|(GPIO_OWN_GPIO)},
    {92, (IS_NOT_GPIO)|(OUTPUT_HIGH)|(GPIO_OWN_GPIO)},
    {93, (IS_NOT_GPIO)|(OUTPUT_HIGH)|(GPIO_OWN_GPIO)},
    {94, (IS_NOT_GPIO)|(OUTPUT_HIGH)|(GPIO_OWN_GPIO)},
    {95, (IS_NOT_GPIO)|(OUTPUT_HIGH)|(GPIO_OWN_GPIO)},
#endif
    {0xffff, 0xffff}, // End of the table.

};

//----------------------------------------------------------------------------

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
