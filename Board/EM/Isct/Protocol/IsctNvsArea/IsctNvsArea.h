//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ISCT/IsctProtocolLib/IsctNvsArea/IsctNvsArea.h 1     9/02/12 11:20p Bensonlai $
//
// $Revision: 1 $
//
// $Date: 9/02/12 11:20p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ISCT/IsctProtocolLib/IsctNvsArea/IsctNvsArea.h $
// 
// 1     9/02/12 11:20p Bensonlai
// Intel Smart Connect Technology initially releases.
//
//
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:  IsctNvsArea.h
//
// Description:	Data structures defined in this protocol are not naturally aligned.
//
//<AMI_FHDR_END>
//**********************************************************************

#ifndef _ISCT_NVS_AREA_H_
#define _ISCT_NVS_AREA_H_

//
// Includes
//
//
// Forward reference for pure ANSI compatability
//
EFI_FORWARD_DECLARATION (ISCT_NVS_AREA_PROTOCOL);

//
// Isct NVS Area Protocol GUID
//
#define ISCT_NVS_AREA_PROTOCOL_GUID \
  { \
    0x6614a586, 0x788c, 0x47e2, 0x89, 0x2d, 0x72, 0xe2, 0xc, 0x34, 0x48, 0x90 \
  }

//
// Extern the GUID for protocol users.
//
extern EFI_GUID gIsctNvsAreaProtocolGuid;

//
// Isct NVS Area definition
//
#pragma pack(1)
typedef struct {
  UINT8       IsctWakeReason;      //(0): Wake Reason
  UINT8       IsctEnabled;         //(1): 1 - Enabled, 0 - Disabled
  UINT8       RapidStartEnabled;   //(2): IFFS service enabled
  UINT8       IsctTimerChoice;     //(3): 1 - RTC timer, 0 - EC timer
  UINT32      EcDurationTime;      //(4): EC Duration Time
  UINT32      RtcDurationTime;     //(8): RTC Duration Time
  UINT32      IsctNvsPtr;          //(12): Ptr of Isct GlobalNvs
  UINT8       IsctOverWrite;       //(16): 1 - Isct , 0 - OS RTC
} ISCT_NVS_AREA;
#pragma pack()

//
// Isct NVS Area Protocol
//
typedef struct _ISCT_NVS_AREA_PROTOCOL {
  ISCT_NVS_AREA     *Area;
  VOID              *IsctData;
} ISCT_NVS_AREA_PROTOCOL;

#endif

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
