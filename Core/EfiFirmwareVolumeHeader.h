/*++

Copyright (c) 2004, Intel Corporation                                                         
All rights reserved. This program and the accompanying materials                          
are licensed and made available under the terms and conditions of the BSD License         
which accompanies this distribution.  The full text of the license may be found at        
http://opensource.org/licenses/bsd-license.php                                            
                                                                                          
THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,                     
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.             

Module Name:

  EfiFirmwareVolumeHeader.h

Abstract:

  Defines data structure that is the volume header found at the beginning of
  all firmware volumes that are either memory mapped, or have an
  associated FirmwareVolumeBlock protocol.

--*/

#ifndef _EFI_FIRMWARE_VOLUME_HEADER_H_
#define _EFI_FIRMWARE_VOLUME_HEADER_H_
#include <FFS.h>

//PI 1.1 ++
#if defined (PI_SPECIFICATION_VERSION) && (PI_SPECIFICATION_VERSION >= 0x00010000)

#define EFI_FVB_CAPABILITIES  (EFI_FVB2_READ_DISABLED_CAP | \
                              EFI_FVB2_READ_ENABLED_CAP   | \
                              EFI_FVB2_WRITE_DISABLED_CAP | \
                              EFI_FVB2_WRITE_ENABLED_CAP  | \
                              EFI_FVB2_LOCK_CAP           | \
                              EFI_FVB2_READ_LOCK_CAP     | \
                              EFI_FVB2_WRITE_LOCK_CAP    )

#define EFI_FVB_STATUS    (EFI_FVB2_READ_STATUS | EFI_FVB2_WRITE_STATUS       | \
                           EFI_FVB2_LOCK_STATUS | EFI_FVB2_READ_LOCK_STATUS  | \
                           EFI_FVB2_WRITE_LOCK_STATUS )

#ifndef EFI_FVB_ERASE_POLARITY
#define EFI_FVB_ERASE_POLARITY EFI_FVB2_ERASE_POLARITY
#endif
#ifndef EFI_FVB_READ_STATUS
#define EFI_FVB_READ_STATUS EFI_FVB2_READ_STATUS
#endif
//*** AMI PORTING BEGIN ***//
#ifndef EFI_FVB_WRITE_STATUS
#define EFI_FVB_WRITE_STATUS EFI_FVB2_WRITE_STATUS
#endif
//*** AMI PORTING END ***//
#ifndef EFI_FVB_MEMORY_MAPPED
#define EFI_FVB_MEMORY_MAPPED EFI_FVB2_MEMORY_MAPPED
#endif
#else

#define EFI_FVB_CAPABILITIES  (EFI_FVB_READ_DISABLED_CAP | \
                              EFI_FVB_READ_ENABLED_CAP | \
                              EFI_FVB_WRITE_DISABLED_CAP | \
                              EFI_FVB_WRITE_ENABLED_CAP | \
                              EFI_FVB_LOCK_CAP \
                              )

#define EFI_FVB_STATUS    (EFI_FVB_READ_STATUS | EFI_FVB_WRITE_STATUS | EFI_FVB_LOCK_STATUS)

#endif
//PI 1.1 ++
//
// Firmware Volume Header Revision definition
//
#define EFI_FVH_REVISION  0x01
//
// PI1.0 define Firmware Volume Header Revision to 2
//
#define EFI_FVH_PI_REVISION  0x02

//
// Firmware Volume Header Signature definition
//
//Defined in Tiano.h #define EFI_FVH_SIGNATURE EFI_SIGNATURE_32 ('_', 'F', 'V', 'H')

//
// Firmware Volume Header Block Map Entry definition
//

#endif
