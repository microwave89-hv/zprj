/*++

Copyright (c) 2004, Intel Corporation                                                         
All rights reserved. This program and the accompanying materials                          
are licensed and made available under the terms and conditions of the BSD License         
which accompanies this distribution.  The full text of the license may be found at        
http://opensource.org/licenses/bsd-license.php                                            
                                                                                          
THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,                     
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.             

Module Name:

  EfiImageFormat.h

Abstract:

  This file defines the data structures that are architecturally defined for file
  images loaded via the FirmwareVolume protocol.  The Firmware Volume specification
  is the basis for these definitions.

--*/

#ifndef _EFI_IMAGE_FORMAT_H_
#define _EFI_IMAGE_FORMAT_H_
#include <FFS.h>
//
// pack all data structures since this is actually a binary format and we cannot
// allow internal padding in the data structures because of some compilerism..
//
#pragma pack(1)

// ************************************************************
// Leaf section Type values
// ************************************************************
//
#define EFI_SECTION_FIRST_LEAF_SECTION_TYPE 0x10
#define EFI_SECTION_LAST_LEAF_SECTION_TYPE  0x1B
#define EFI_SECTION_LAST_SECTION_TYPE       0x1B

#define SECTION_SIZE(SectionHeaderPtr) \
    ((UINT32) (*((UINT32 *) ((EFI_COMMON_SECTION_HEADER *) SectionHeaderPtr)->Size) & 0x00ffffff))

//
// ////////////////////////////////////////////////////////////////////////////
//
// Compression section
//
//
// CompressionType values
//
#define EFI_CUSTOMIZED_COMPRESSION  0x02

//
// Bit values for AuthenticationStatus
//
#define EFI_AGGREGATE_AUTH_STATUS_PLATFORM_OVERRIDE 0x000001
#define EFI_AGGREGATE_AUTH_STATUS_IMAGE_SIGNED      0x000002
#define EFI_AGGREGATE_AUTH_STATUS_NOT_TESTED        0x000004
#define EFI_AGGREGATE_AUTH_STATUS_TEST_FAILED       0x000008
#define EFI_AGGREGATE_AUTH_STATUS_ALL               0x00000f

#define EFI_LOCAL_AUTH_STATUS_PLATFORM_OVERRIDE     0x010000
#define EFI_LOCAL_AUTH_STATUS_IMAGE_SIGNED          0x020000
#define EFI_LOCAL_AUTH_STATUS_NOT_TESTED            0x040000
#define EFI_LOCAL_AUTH_STATUS_TEST_FAILED           0x080000
#define EFI_LOCAL_AUTH_STATUS_ALL                   0x0f0000


// ////////////////////////////////////////////////////////////////////////////
//
// PEIM header section
//
typedef struct {
  EFI_COMMON_SECTION_HEADER CommonHeader;
} EFI_PEIM_HEADER_SECTION;

//
// ////////////////////////////////////////////////////////////////////////////
//
// DEPEX section
//
typedef struct {
  EFI_COMMON_SECTION_HEADER CommonHeader;
} EFI_DEPEX_SECTION;

// ////////////////////////////////////////////////////////////////////////////
//
// Code16 section
//
typedef struct {
  EFI_COMMON_SECTION_HEADER CommonHeader;
} EFI_CODE16_SECTION;


// ////////////////////////////////////////////////////////////////////////////
//
// Raw section
//
typedef struct {
  EFI_COMMON_SECTION_HEADER CommonHeader;
} EFI_RAW_SECTION;

//
// undo the pragma from the beginning...
//
#pragma pack()

typedef union {
  EFI_COMMON_SECTION_HEADER         *CommonHeader;
  EFI_COMPRESSION_SECTION           *CompressionSection;
  EFI_GUID_DEFINED_SECTION          *GuidDefinedSection;
  EFI_PE32_SECTION                  *Pe32Section;
  EFI_PIC_SECTION                   *PicSection;
  EFI_PEIM_HEADER_SECTION           *PeimHeaderSection;
  EFI_DEPEX_SECTION                 *DependencySection;
  EFI_VERSION_SECTION               *VersionSection;
  EFI_USER_INTERFACE_SECTION        *UISection;
  EFI_CODE16_SECTION                *Code16Section;
  EFI_FIRMWARE_VOLUME_IMAGE_SECTION *FVImageSection;
  EFI_FREEFORM_SUBTYPE_GUID_SECTION *FreeformSubtypeSection;
  EFI_RAW_SECTION                   *RawSection;
} EFI_FILE_SECTION_POINTER;

#endif
