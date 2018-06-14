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

//**********************************************************************
//
// $Header: /Alaska/BIN/Chipset/Template/CSPLibrary/FID.c 6     2/22/11 3:28p Artems $
//
// $Revision: 6 $
//
// $Date: 2/22/11 3:28p $
//
//*****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Chipset/Template/CSPLibrary/FID.c $
// 
// 6     2/22/11 3:28p Artems
// EIP 51548 - Added AMI copyright headers, replaced TABs with spaces
// 
// 5     12/17/10 4:42p Artems
// Added OEM activation key support
// 
// 4     5/21/10 4:29p Artems
// Changed to version 3 as per Utility specification
// 
// 3     4/05/10 6:15p Artems
// Added Core 4.6.3 backward compatibility fix
// 
// 2     12/03/09 12:09p Robert
// updated comments and file header information
// 
//
//*****************************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:        FID.C
//
// Description: 
//  This file the Firmware Version Data Structure definition
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>


// Module specific Includes
#include "Pei.h"
#include "token.h"
#include <timestamp.h>
#include <AmiLib.h>
#include <Ppi\FwVersion.h>

#define THREE_CHAR_ARRAY(x) {(x)/10+'0',(x)%10+'0',0}

FW_VERSION  FwVersionData = {
    "$FID",                                     //$FID signature of the FW VERSION STRUCTURE
    0x04,                                       //Version 4
    sizeof(FW_VERSION),                         //Size of this structure
    CONVERT_TO_STRING(BIOS_TAG),                //8 character BIOS Tag, Plus NULL Cahracter at the end
    FW_VERSION_GUID,                            //FW Version GUID
    THREE_CHAR_ARRAY(CORE_MAJOR_VERSION),       //Core Major Version from BIOS Parameters
    THREE_CHAR_ARRAY(CORE_MINOR_VERSION),       //Core Minor Version from BIOS Parameters
    THREE_CHAR_ARRAY(PROJECT_MAJOR_VERSION),    //Project Major Version from BIOS Parameters
    THREE_CHAR_ARRAY(PROJECT_MINOR_VERSION),    //Project Minor Version from BIOS Parameters
    FOUR_DIGIT_YEAR_INT,
    TWO_DIGIT_MONTH_INT,
    TWO_DIGIT_DAY_INT,
    TWO_DIGIT_HOUR_INT,
    TWO_DIGIT_MINUTE_INT,
    TWO_DIGIT_SECOND_INT,
    0xffff,
    CONVERT_TO_STRING(T_ACPI_OEM_ID),
    CONVERT_TO_STRING(T_ACPI_OEM_TBL_ID),
    49,
    { 
        0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
        0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
        0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
        0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
        0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff
    }
};

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