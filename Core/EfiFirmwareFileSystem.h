/*++

Copyright (c) 2004, Intel Corporation                                                         
All rights reserved. This program and the accompanying materials                          
are licensed and made available under the terms and conditions of the BSD License         
which accompanies this distribution.  The full text of the license may be found at        
http://opensource.org/licenses/bsd-license.php                                            
                                                                                          
THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,                     
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.             

Module Name:

  EfiFirmwareFileSystem.h

Abstract:

  This file defines the data structures that comprise the FFS file system.

--*/

#ifndef _EFI_FFS_FILE_SYSTEM_H_
#define _EFI_FFS_FILE_SYSTEM_H_

#include <FFS.h>

//
// FFS_FIXED_CHECKSUM is the default checksum value used when the
// FFS_ATTRIB_CHECKSUM attribute bit is clear
// note this is NOT an architecturally defined value, but is in this file for
// implementation convenience
//
#define FFS_FIXED_CHECKSUM  0x5A

#define EFI_FILE_ALL_STATE_BITS       (EFI_FILE_HEADER_CONSTRUCTION | \
                                 EFI_FILE_HEADER_VALID | \
                                 EFI_FILE_DATA_VALID | \
                                 EFI_FILE_MARKED_FOR_UPDATE | \
                                 EFI_FILE_DELETED | \
                                 EFI_FILE_HEADER_INVALID \
          )

#define EFI_TEST_FFS_ATTRIBUTES_BIT(FvbAttributes, TestAttributes, Bit) \
    ( \
      (BOOLEAN) ( \
          (FvbAttributes & EFI_FVB_ERASE_POLARITY) ? (((~TestAttributes) & Bit) == Bit) : ((TestAttributes & Bit) == Bit) \
        ) \
    )
#endif
