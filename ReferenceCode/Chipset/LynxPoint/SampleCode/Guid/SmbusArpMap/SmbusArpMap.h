/** @file
  GUID for use in describing SMBus devices that were ARPed during PEI.

@copyright
  Copyright (c) 2009 - 2012 Intel Corporation. All rights reserved
  This software and associated documentation (if any) is furnished
  under a license and may only be used or copied in accordance
  with the terms of the license. Except as permitted by such
  license, no part of this software or documentation may be
  reproduced, stored in a retrieval system, or transmitted in any
  form or by any means without the express written consent of
  Intel Corporation.

  This file contains 'Framework Code' and is licensed as such
  under the terms of your license agreement with Intel or your
  vendor.  This file may not be modified, except as allowed by
  additional terms of your license agreement.
**/
#ifndef _EFI_SMBUS_ARP_MAP_GUID_H_
#define _EFI_SMBUS_ARP_MAP_GUID_H_

#define EFI_SMBUS_ARP_MAP_GUID \
  { \
    0x707be83e, 0x0bf6, 0x40a5, 0xbe, 0x64, 0x34, 0xc0, 0x3a, 0xa0, 0xb8, 0xe2 \
  }

extern EFI_GUID gEfiSmbusArpMapGuid;

#endif
