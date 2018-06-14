//
// This file contains 'Framework Code' and is licensed as such 
// under the terms of your license agreement with Intel or your
// vendor.  This file may not be modified, except as allowed by
// additional terms of your license agreement.                 
//
/*++

Copyright (c)  2004 Intel Corporation. All rights reserved
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.


Module Name:

  EnhancedSpeedstep.h

Abstract:

  Enhanced Speedstep protocol 

  The Enhanced Speedstep Protocol support.   
--*/

#ifndef _ENHANCED_SPEEDSTEP_H_
#define _ENHANCED_SPEEDSTEP_H_

#define DXE_ENHANCED_SPEEDSTEP_PROTOCOL_GUID \
  { \
    0xe98021, 0xf4fe, 0x46cc, 0xab, 0x2d, 0x89, 0x4c, 0x37, 0x3a, 0xfa, 0x1 \
  }

EFI_FORWARD_DECLARATION (DXE_ENHANCED_SPEEDSTEP_PROTOCOL);

typedef struct {
  UINT32  Stepping;     // Matches value returned by CPUID function 1
  UINT8   Version;      // FVID State format
  UINT8   Size;         // Size of 1 FVID_STATE element
  UINT8   MaxVid;       // Calculated Max VID
  UINT8   MaxBusRatio;  // Calculated max ratio
  UINT8   NumStates;    // Number of states of FVID (N)
} FVID_INFORMATION;

typedef struct {
  UINT32  Power;        // Typical power consumed by CPU in this state
  UINT16  State;        // State Number (0 - N-1)
  UINT16  Vid;          // VID_SEL value to be written to PERF_CTL
  UINT16  BusRatio;     // BUS_RATIO_SEL value written to PERF_CTL
  UINT16  Reserved;     // to preserve alignment
} FVID_STATE_1;

#define ES_FVID_STATE_VERSION_1 1

typedef struct {
  UINT32  Features;
  UINT32  Locks;
} ENHANCED_SPEEDSTEP_STATE;

#define ES_GV3  (1 << 0)
#define ES_TM2  (1 << 1)
//
// All other bits reserved.
//
typedef
EFI_STATUS
(EFIAPI *ES_GET_CAPABILITIES) (
  IN      DXE_ENHANCED_SPEEDSTEP_PROTOCOL    * This,
  IN OUT  ENHANCED_SPEEDSTEP_STATE           * Capabilities
  );

typedef
EFI_STATUS
(EFIAPI *ES_GET_STATE) (
  IN      DXE_ENHANCED_SPEEDSTEP_PROTOCOL    * This,
  IN OUT  ENHANCED_SPEEDSTEP_STATE           * State
  );

typedef
EFI_STATUS
(EFIAPI *ES_SET_STATE) (
  IN      DXE_ENHANCED_SPEEDSTEP_PROTOCOL     * This,
  IN OUT  ENHANCED_SPEEDSTEP_STATE            * State,
  IN      ENHANCED_SPEEDSTEP_STATE            * Mask
  );

typedef
EFI_STATUS
(EFIAPI *ES_GET_FVID_TABLE) (
  IN    DXE_ENHANCED_SPEEDSTEP_PROTOCOL    * This,
  OUT   FVID_INFORMATION                   **FvidInformation,
  OUT   VOID                               **FvidStates
  );

typedef struct _DXE_ENHANCED_SPEEDSTEP_PROTOCOL {
  ES_GET_CAPABILITIES GetCapabilities;
  ES_GET_STATE        GetState;
  ES_SET_STATE        SetState;
  ES_GET_FVID_TABLE   GetFvidTable;
  UINT16              ProcNumber;
} DXE_ENHANCED_SPEEDSTEP_PROTOCOL;
//
// There will be an instance of this protocol for every processor
// in the system.  ProcNumber is used to manage all the different
// processors in the system and passed into the MP protocol
// to run code streams on application processors
//
extern EFI_GUID gDxeEnhancedSpeedstepProtocolGuid;

#endif
