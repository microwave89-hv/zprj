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
// $Header: /Alaska/BIN/Core/Include/Protocol/AbsPointerProtocol.h 1     4/15/10 3:58a Rameshr $
//
// $Revision: 1 $
//
// $Date: 4/15/10 3:58a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/Protocol/AbsPointerProtocol.h $
// 
// 1     4/15/10 3:58a Rameshr
// Initial Check-in
// 
// 
//**********************************************************************

//<AMI_FHDR_START>
//--------------------------------------------------------------------------
//
// Name: AbsPointerProtocol.h
//
// Description: Absolute Pointer Protocol 
//
//--------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef __EFI_ABSOLUTE_POINTER_PROTOCOL_H__
#define __EFI_ABSOLUTE_POINTER_PROTOCOL_H__
#ifdef __cplusplus
extern "C" {
#endif

#include <EFI.h>

#define EFI_ABSOLUTE_POINTER_PROTOCOL_GUID \
{0x8D59D32B, 0xC655, 0x4AE9, 0x9B, 0x15, 0xF2, 0x59, 0x04, 0x99, 0x2A, 0x43};

GUID_VARIABLE_DECLARATION(gEfiAbsolutePointerProtocolGuid,EFI_ABSOLUTE_POINTER_PROTOCOL_GUID);

// Forward declaration
typedef struct _EFI_ABSOLUTE_POINTER_PROTOCOL EFI_ABSOLUTE_POINTER_PROTOCOL;

#define EFI_ABSP_SupportsAltActive      0x00000001
#define EFI_ABSP_SupportsPressureAsZ    0x00000002

//
//definitions of bits within ActiveButtons
//
#define EFI_ABSP_TouchActive            0x00000001
#define EFI_ABS_AltActive               0x00000002

//
// EFI_ABSOLUTE_POINTER_STATE
//
typedef struct {
    UINT64 CurrentX;
    UINT64 CurrentY;
    UINT64 CurrentZ;
    UINT32 ActiveButtons;
} EFI_ABSOLUTE_POINTER_STATE;

//
// EFI_ABSOLUTE_POINTER_MODE
//
typedef struct {
    UINT64 AbsoluteMinX;
    UINT64 AbsoluteMinY;
    UINT64 AbsoluteMinZ;
    UINT64 AbsoluteMaxX;
    UINT64 AbsoluteMaxY;
    UINT64 AbsoluteMaxZ;
    UINT32 Attributes;
} EFI_ABSOLUTE_POINTER_MODE;

typedef
EFI_STATUS
(EFIAPI *EFI_ABSOLUTE_POINTER_RESET) (
  IN EFI_ABSOLUTE_POINTER_PROTOCOL              * This,
  IN BOOLEAN                                    ExtendedVerification
  );

typedef
EFI_STATUS
(EFIAPI *EFI_ABSOLUTE_POINTER_GET_STATE) (
  IN EFI_ABSOLUTE_POINTER_PROTOCOL          * This,
  IN OUT EFI_ABSOLUTE_POINTER_STATE         * State
  );

typedef struct _EFI_ABSOLUTE_POINTER_PROTOCOL {
  EFI_ABSOLUTE_POINTER_RESET        Reset;
  EFI_ABSOLUTE_POINTER_GET_STATE    GetState;
  EFI_EVENT                         WaitForInput;
  EFI_ABSOLUTE_POINTER_MODE         *Mode;
} EFI_ABSOLUTE_POINTER_PROTOCOL;


/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif

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

