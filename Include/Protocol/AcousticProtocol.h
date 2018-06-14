//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/HddAcoustic/AcousticProtocol.h 2     2/10/11 11:31a Pats $
//
// $Revision: 2 $
//
// $Date: 2/10/11 11:31a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/HddAcoustic/AcousticProtocol.h $
// 
// 2     2/10/11 11:31a Pats
// [TAG] - EIP 52920
// [Category]- Function Request
// [Severity]- Minor
// [Symptom] - The Acoustic mode (Bypass/Quiet/Max Performance) of port 5
// is invalid on AMD SB700.
// [RootCause] - Special case where 2nd controller counts by incrementing
// device number only not handled properly
// [Solution] - Added another item (ControllerNumber) to protocol.
// [Files] - Acoustic.c, AcousticBoard.c, AcousticSetup.c,
// AcousticProtocol.n
// 
// 1     1/05/11 12:22a Rameshr
// Initial check-in for Hdd Acoustic Management Support.
// 
//**********************************************************************

//<AMI_FHDR_START>
//--------------------------------------------------------------------------
//
// Name: AcousticProtocol.h 		
//
// Description: Header file that has protocol structure for Acoustic Module.
//
//--------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef  _AcousticProtocol_H   
#define  _AcousticProtocol_H

#ifdef __cplusplus
extern "C" {
#endif

#include <Efi.h>

#define ACOUSTIC_SETUP_PROTOCOL_GUID\
        { 0xc1d7859d, 0x5719, 0x46c3, 0xa2, 0x98, 0xd0, 0x71, 0xe3, 0x2, 0x64, 0xd1 }

//  Equates used for Acoustic Flags
#define     ACOUSTIC_SUPPORT_DISABLE            0x00
#define     ACOUSTIC_SUPPORT_ENABLE             0x01
#define     ACOUSTIC_LEVEL_BYPASS               0xFF
#define     ACOUSTIC_LEVEL_MAXIMUM_PERFORMANCE  0xFE
#define     ACOUSTIC_LEVEL_QUIET                0x80

typedef struct {
    UINT8       DeviceCount;                // Should be updated by the Protocol installer
    UINT8       ControllerNumber;
    UINT8       AcousticPwrMgmt;
    UINT8       AcousticLevel;   
    UINT8       *DeviceDetected;
    UINT8       *AcousticLevelIndv;         // Each byte is for a port. For IDE mode it is PM, PS, SM and SS. 
                                            // If there is any translation it has to be done at a later stage.
    UINT8       *AcousticSupportIndv;
}ACOUSTIC_SETUP_PROTOCOL;

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif

#endif

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
