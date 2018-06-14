/** @file
  AMT Platform Policy for AMT PEIMs

@copyright
  Copyright (c) 2008 - 2012 Intel Corporation. All rights reserved
  This software and associated documentation (if any) is furnished
  under a license and may only be used or copied in accordance
  with the terms of the license. Except as permitted by such
  license, no part of this software or documentation may be
  reproduced, stored in a retrieval system, or transmitted in any
  form or by any means without the express written consent of
  Intel Corporation.

  This file contains a 'Sample Driver' and is licensed as such
  under the terms of your license agreement with Intel or your
  vendor.  This file may be modified by the user, subject to
  the additional terms of the license agreement
**/
#ifndef _PEI_AMT_PLATFORM_POLICY_PPI_H_
#define _PEI_AMT_PLATFORM_POLICY_PPI_H_

//
// Include other definitions
//
///
/// Intel AMT Platform Policy PPI GUID
/// This PPI provides an interface to get the current Intel AMT SKU information
///
#define PEI_AMT_PLATFORM_POLICY_PPI_GUID \
  { \
    0xb4a1208e, 0x4d9a, 0x4ea2, 0x9d, 0x6b, 0xe4, 0x1a, 0x61, 0xe6, 0xc5, 0xac \
  }

//
// Extern the GUID for PPI users.
//
extern EFI_GUID gPeiAmtPlatformPolicyPpiGuid;

///
/// Revision
///
#define PEI_AMT_PLATFORM_POLICY_PPI_REVISION_1  1
///
/// Add AsfEnabled, and ManageabilityMode
///
#define PEI_AMT_PLATFORM_POLICY_PPI_REVISION_2  2
///
/// Added FWProgress
///
#define PEI_AMT_PLATFORM_POLICY_PPI_REVISION_3  3
///
/// Cleanup
///
#define PEI_AMT_PLATFORM_POLICY_PPI_REVISION_4  4
///
/// Cleanup
///
#define PEI_AMT_PLATFORM_POLICY_PPI_REVISION_5  5

///
/// Intel AMT Platform Policy PPI
/// The Intel AMT Platform Policy PPI returns the Intel ME feature set in PEI phase
///
typedef struct _PEI_AMT_PLATFORM_POLICY_PPI {
  UINT8   Revision;               ///< Policy structure revision number
  UINT8   iAmtEnabled : 1;        ///< Intel AMT features enabled/disable
  UINT8   WatchDog : 1;           ///< Asf Watch Dog timer message enabled/disable
  UINT8   Reserved : 1;
  UINT8   AsfEnabled : 1;         ///< Asf features enable/disable
  UINT8   ManageabilityMode : 1;  ///< Manageability Mode, 0: Off, 1:On
  UINT8   Reserved1 : 1;
  UINT16  WatchDogTimerOs;        ///< Watch Dog timeout value for OS
  UINT16  WatchDogTimerBios;      ///< Watch Dog timeout value for BIOS
  UINT8   FWProgress;             ///< Progress Event option enable/disable
} PEI_AMT_PLATFORM_POLICY_PPI;

#endif
