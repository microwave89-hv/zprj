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
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ISCT/IsctGuidLib/IsctPersistentData/IsctPersistentData.h 2     7/16/14 1:59a Mirayang $
//
// $Revision: 2 $
//
// $Date: 7/16/14 1:59a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ISCT/IsctGuidLib/IsctPersistentData/IsctPersistentData.h $
// 
// 2     7/16/14 1:59a Mirayang
// Add complete function with iRST.
// 
// 1     9/02/12 11:20p Bensonlai
// Intel Smart Connect Technology initially releases.
//
//
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:  IsctPersistentData.h
//
// Description:	GUID definition for the Isct Persistent Data
//
//<AMI_FHDR_END>
//**********************************************************************

#ifndef _ISCT_PERSISTENT_DATA_H_
#define _ISCT_PERSISTENT_DATA_H_

// GUID {69A20012-B167-4e35-A999-98EE0835F02E}
#define ISCT_PERSISTENT_DATA_GUID \
  { \
    0x69a20012, 0xb167, 0x4e35, 0xa9, 0x99, 0x98, 0xee, 0x8, 0x35, 0xf0, 0x2e \
  }

#define ISCT_PERSISTENT_DATA_NAME L"IsctData"

extern EFI_GUID gIsctPersistentDataGuid;

#pragma pack(1)
typedef struct {
  UINT32      IsctNvsPtr;
  UINT8       IsctOverWrite;
} ISCT_PERSISTENT_DATA;
#pragma pack()

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
