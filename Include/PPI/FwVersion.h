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
// $Header: /Alaska/BIN/Chipset/Template/CSPLibrary/FwVersion.h 11    2/22/11 4:41p Artems $
//
// $Revision: 11 $
//
// $Date: 2/22/11 4:41p $
//*****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Chipset/Template/CSPLibrary/FwVersion.h $
// 
// 11    2/22/11 4:41p Artems
// EIP 51548 - Added AMI copyright headers, replaced TABs with spaces
// 
// 10    12/17/10 4:41p Artems
// Added OEM activation key support
// 
// 9     5/21/10 4:29p Artems
// Changed to version 3 as per Utility specification
// 
// 8     4/05/10 6:15p Artems
// Added Core 4.6.3 backward compatibility fix
// 
// 7     12/03/09 12:07p Robert
// updated table header information
// 
// 6     12/02/09 4:55p Robert
// Added changes for support for Revision 2 of the Firmware Version
// Structure
// 
// 5     6/12/09 1:40p Robert
// added source safe headers
// 
//
//*****************************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:        FwVersion.h
//
// Description: 
//  This file the FW_VERSION data structure which is used by AMI utilities to 
//  provide information about the BIOS
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef __FW_VERSION_H__
#define __FW_VERSION_H__
#ifdef __cplusplus
extern "C" {
#endif


#define FID_SIGNATURE   0x24464944      //'$FID' signature of the FW VERSION STRUCTURE
#pragma pack (1)


//<AMI_GHDR_START>
//------------------------------------------------------------------
//
// Name:        FW_VERSION
//
// Fields:      Type    ParameterName    Description
//------------------------------------------------------------------
//  CHAR8 "FirmwareID[4]" - Signature '$FID'
//  UINT8 StructVersion - Version of the FW_VERSION Structure
//  UINT16 Size - Size of this structure
//  CHAR8 "BiosTag[9]" - BIOS Tag
//  EFI_GUID FirmwareGuid - Firmware GUID
//  CHAR8 "CoreMajorVersion[3]" - Aptio Core Major Version
//  CHAR8 "CoreMinorVersion[3]" - Aptio Core Minor Version
//  CHAR8 "ProjectMajorVersion[3]" - Project Major Version
//  CHAR8 "ProjectMinorVersion[3]" - Project Minor Version
//  UINT16 Year - Build Year
//  UINT8 Month - Build Month
//  UINT8 Day - Build Day
//  UINT8 Hour - Build Hour
//  UINT8 Minute - Build Minute
//  UINT8 Second - Build Second
//  UINT32 OemActivationKeyLength - Length of the OEM Activation key
//  UINT8  OemActivationKey[49] - OEM Activation key
//
// Description: 
//  This data structure contains the information used by AMI utilities
//  to provide information about the current BIOS 
//  
//
// Notes:   
//  Data structure changed for version 2 of the Firmware Version Structure
//  Version 1 is no longer supported
//      
//------------------------------------------------------------------
//<AMI_GHDR_END>
typedef struct{
CHAR8       FirmwareID[4];      //Signature '$FID'
UINT8       StructVersion;      //Version of the FW_VERSION Struct
UINT16      Size;           //Size of this structure
CHAR8       BiosTag[9];     //BIOS Tag
EFI_GUID    FirmwareGuid;       //Firmware GUID
CHAR8       CoreMajorVersion[3];    
CHAR8       CoreMinorVersion[3];
CHAR8       ProjectMajorVersion[3];
CHAR8       ProjectMinorVersion[3];
UINT16      Year;
UINT8       Month;
UINT8       Day;
UINT8       Hour;
UINT8       Minute;
UINT8       Second;
UINT16      SignOnStringId;
UINT8       OemId[6];
UINT8       OemTableId[8];
UINT32      OemActivationKeyLength;
UINT8       OemActivationKey[49];
}FW_VERSION;
#pragma pack ()



/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif

#endif

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

