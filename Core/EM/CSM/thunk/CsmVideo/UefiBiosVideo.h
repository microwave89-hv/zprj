//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**        5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093         **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//
// This file contains a 'Sample Driver' and is licensed as such
// under the terms of your license agreement with Intel or your
// vendor.  This file may be modified by the user, subject to  
// the additional terms of the license agreement               
//
/*++

Copyright (c)  2006 Intel Corporation. All rights reserved
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.

Module Name:

  UefiBiosVideo.h
    
Abstract: 

Revision History
--*/

#ifndef _BIOS_GRAPHICS_OUTPUT_H
#define _BIOS_GRAPHICS_OUTPUT_H

//*** AMI PORTING BEGIN ***//
#include "AmiMapping.h"
#include "EdkIICommon.h"
//#include "Tiano.h"
//#include "EfiDriverLib.h"
#include <Protocol/CsmVideoPolicy.h>
//*** AMI PORTING END *****//
#include "VesaBiosExtensions.h"
#include "Pci22.h"

//
// Driver Consumed Protocol Prototypes
//
#include EFI_PROTOCOL_DEFINITION (DevicePath)
#include EFI_PROTOCOL_DEFINITION (PciIo)
#include EFI_PROTOCOL_DEFINITION (LegacyBios)
//*** AMI PORTING BEGIN ***//
//AMI CSM Core does not need this GUID
//#include EFI_GUID_DEFINITION (LegacyBios)
//*** AMI PORTING END *****//
//*** AMI PORTING BEGIN ***//
//#include EFI_GUID_DEFINITION (StatusCodeCallerId)
//#include EFI_GUID_DEFINITION (StatusCodeDataTypeId)
//*** AMI PORTING END *****//

//
// Driver Produced Protocol Prototypes
//
#include EFI_PROTOCOL_DEFINITION (DriverBinding)
#include EFI_PROTOCOL_DEFINITION (ComponentName)
#include EFI_PROTOCOL_DEFINITION (GraphicsOutput)
#include EFI_PROTOCOL_DEFINITION (EdidDiscovered)
#include EFI_PROTOCOL_DEFINITION (EdidActive)

//*** AMI PORTING BEGIN ***//
//#include EFI_PROTOCOL_DEFINITION (VgaMiniPort)
#include "VgaMiniPort.h"

// uncomment the following lind and remove the following block when Protocol/EdidOverride.h is available
//#include EFI_PROTOCOL_DEFINITION (EdidOverride)
#define EFI_EDID_OVERRIDE_PROTOCOL_GUID \
    { 0x48ecb431, 0xfb72, 0x45c0, 0xa9, 0x22, 0xf4, 0x58, 0xfe, 0x4, 0xb, 0xd5 }

#define EFI_EDID_OVERRIDE_DONT_OVERRIDE   0x01
#define EFI_EDID_OVERRIDE_ENABLE_HOT_PLUG 0x02

typedef struct _EFI_EDID_OVERRIDE_PROTOCOL EFI_EDID_OVERRIDE_PROTOCOL;

typedef EFI_STATUS (EFIAPI *EFI_EDID_OVERRIDE_PROTOCOL_GET_EDID) (
  IN  EFI_EDID_OVERRIDE_PROTOCOL        *This,
  IN  EFI_HANDLE                        *ChildHandle,
  OUT UINT32                            *Attributes,
  IN OUT UINTN                          *EdidSize,
  IN OUT UINT8                          **Edid
  );

struct _EFI_EDID_OVERRIDE_PROTOCOL {
  EFI_EDID_OVERRIDE_PROTOCOL_GET_EDID   GetEdid;
};
//*** AMI PORTING END *****//

//
// Packed format support: The number of bits reserved for each of the colors and the actual
// position of RGB in the frame buffer is specified in the VBE Mode information
//
typedef struct {
  UINT8 Position; // Position of the color
  UINT8 Mask;     // The number of bits expressed as a mask
} BIOS_VIDEO_COLOR_PLACEMENT;

//
// BIOS Graphics Output Graphical Mode Data
//
typedef struct {
  UINT16                      VbeModeNumber;
  UINT16                      BytesPerScanLine;
  VOID                        *LinearFrameBuffer;
  UINTN                       FrameBufferSize;
  UINT32                      HorizontalResolution;
  UINT32                      VerticalResolution;
  UINT32                      RefreshRate;
  UINT32                      BitsPerPixel;
  BIOS_VIDEO_COLOR_PLACEMENT  Red;
  BIOS_VIDEO_COLOR_PLACEMENT  Green;
  BIOS_VIDEO_COLOR_PLACEMENT  Blue;
  BIOS_VIDEO_COLOR_PLACEMENT  Reserved;
  EFI_GRAPHICS_PIXEL_FORMAT   PixelFormat;
  EFI_PIXEL_BITMASK           PixelBitMask;
} BIOS_VIDEO_MODE_DATA;

//
// BIOS video child handle private data Structure
//
#define BIOS_VIDEO_DEV_SIGNATURE    EFI_SIGNATURE_32 ('B', 'V', 'M', 'p')

typedef struct {
  UINTN                                       Signature;
  EFI_HANDLE                                  Handle;

  //
  // Consumed Protocols
  //
  EFI_PCI_IO_PROTOCOL                         *PciIo;
  EFI_LEGACY_BIOS_PROTOCOL                    *LegacyBios;

  //
  // Produced Protocols
  //
  EFI_GRAPHICS_OUTPUT_PROTOCOL                GraphicsOutput;
  EFI_EDID_DISCOVERED_PROTOCOL                EdidDiscovered;
  EFI_EDID_ACTIVE_PROTOCOL                    EdidActive;
  EFI_VGA_MINI_PORT_PROTOCOL                  VgaMiniPort;

  //
  // General fields
  //
  BOOLEAN                                     VgaCompatible;
  BOOLEAN                                     ProduceGraphicsOutput;
//*** AMI PORTING BEGIN ***//
// ExitBootServicesEvent is not used
//  EFI_EVENT                                   ExitBootServicesEvent;
//*** AMI PORTING END *****//

  //
  // Graphics Output Protocol related fields
  //
  BOOLEAN                                     HardwareNeedsStarting;
  BIOS_VIDEO_MODE_DATA                        *ModeData;
  UINT8                                       *LineBuffer;
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL               *VbeFrameBuffer;
  UINT8                                       *VgaFrameBuffer;

  //
  // VESA Bios Extensions related fields
  //
  UINTN                                       NumberOfPagesBelow1MB;    // Number of 4KB pages in PagesBelow1MB
  EFI_PHYSICAL_ADDRESS                        PagesBelow1MB;            // Buffer for all VBE Information Blocks
  VESA_BIOS_EXTENSIONS_INFORMATION_BLOCK      *VbeInformationBlock;     // 0x200 bytes.  Must be allocated below 1MB
  VESA_BIOS_EXTENSIONS_MODE_INFORMATION_BLOCK *VbeModeInformationBlock; // 0x100 bytes.  Must be allocated below 1MB
  VESA_BIOS_EXTENSIONS_EDID_DATA_BLOCK        *VbeEdidDataBlock;        // 0x80  bytes.  Must be allocated below 1MB
  VESA_BIOS_EXTENSIONS_CRTC_INFORMATION_BLOCK *VbeCrtcInformationBlock; // 59 bytes.  Must be allocated below 1MB
  UINTN                                       VbeSaveRestorePages;      // Number of 4KB pages in VbeSaveRestoreBuffer
  EFI_PHYSICAL_ADDRESS                        VbeSaveRestoreBuffer;     // Must be allocated below 1MB
  //
  // Status code
  //
  EFI_DEVICE_PATH_PROTOCOL                    *DevicePath;
} BIOS_VIDEO_DEV;

#define BIOS_VIDEO_DEV_FROM_PCI_IO_THIS(a)      CR (a, BIOS_VIDEO_DEV, PciIo, BIOS_VIDEO_DEV_SIGNATURE)
#define BIOS_VIDEO_DEV_FROM_GRAPHICS_OUTPUT_THIS(a)      CR (a, BIOS_VIDEO_DEV, GraphicsOutput, BIOS_VIDEO_DEV_SIGNATURE)
#define BIOS_VIDEO_DEV_FROM_VGA_MINI_PORT_THIS(a) CR (a, BIOS_VIDEO_DEV, VgaMiniPort, BIOS_VIDEO_DEV_SIGNATURE)

#define GRAPHICS_OUTPUT_INVALIDE_MODE_NUMBER	0xffff

//
// Global Variables
//
extern EFI_DRIVER_BINDING_PROTOCOL      gBiosVideoDriverBinding;
extern EFI_COMPONENT_NAME_PROTOCOL      gBiosVideoComponentName;
extern EFI_COMPONENT_NAME2_PROTOCOL     gBiosVideoComponentName2;

//
// Driver Binding Protocol functions
//
EFI_STATUS
EFIAPI
BiosVideoDriverBindingSupported (
  IN EFI_DRIVER_BINDING_PROTOCOL  *This,
  IN EFI_HANDLE                   Controller,
  IN EFI_DEVICE_PATH_PROTOCOL     *RemainingDevicePath
  )
/*++

Routine Description:

  GC_TODO: Add function description

Arguments:

  This                - GC_TODO: add argument description
  Controller          - GC_TODO: add argument description
  RemainingDevicePath - GC_TODO: add argument description

Returns:

  GC_TODO: add return values

--*/
;

EFI_STATUS
EFIAPI
BiosVideoDriverBindingStart (
  IN EFI_DRIVER_BINDING_PROTOCOL  *This,
  IN EFI_HANDLE                   Controller,
  IN EFI_DEVICE_PATH_PROTOCOL     *RemainingDevicePath
  )
/*++

Routine Description:

  GC_TODO: Add function description

Arguments:

  This                - GC_TODO: add argument description
  Controller          - GC_TODO: add argument description
  RemainingDevicePath - GC_TODO: add argument description

Returns:

  GC_TODO: add return values

--*/
;

EFI_STATUS
EFIAPI
BiosVideoDriverBindingStop (
  IN  EFI_DRIVER_BINDING_PROTOCOL  *This,
  IN  EFI_HANDLE                   Controller,
  IN  UINTN                        NumberOfChildren,
  IN  EFI_HANDLE                   *ChildHandleBuffer
  )
/*++

Routine Description:

  GC_TODO: Add function description

Arguments:

  This              - GC_TODO: add argument description
  Controller        - GC_TODO: add argument description
  NumberOfChildren  - GC_TODO: add argument description
  ChildHandleBuffer - GC_TODO: add argument description

Returns:

  GC_TODO: add return values

--*/
;

//
// Private worker functions
//
EFI_STATUS
BiosVideoCheckForVbe (
  BIOS_VIDEO_DEV  *BiosVideoPrivate,
//*** AMI PORTING BEGIN ***//
  PCI_TYPE00	 *PciConfSpace
//*** AMI PORTING END *****//
)
/*++

Routine Description:

  GC_TODO: Add function description

Arguments:

  BiosVideoPrivate  - GC_TODO: add argument description

Returns:

  GC_TODO: add return values

--*/
;

EFI_STATUS
BiosVideoCheckForVga (
  BIOS_VIDEO_DEV  *BiosVideoPrivate
  )
/*++

Routine Description:

  GC_TODO: Add function description

Arguments:

  BiosVideoPrivate  - GC_TODO: add argument description

Returns:

  GC_TODO: add return values

--*/
;

STATIC
EFI_STATUS
DeRegisterVideoChildHandle (
  EFI_DRIVER_BINDING_PROTOCOL    *This,
  EFI_HANDLE                     Controller,
  EFI_HANDLE                     Handle
  )
/*++

Routine Description:

  Deregister an video child handle and free resources

Arguments:

  This            - Protocol instance pointer.
  Controller      - Video controller handle
  Handle          - Video child handle

Returns:

  EFI_STATUS

--*/
;

VOID
BiosVideoDeviceReleaseResource (
  BIOS_VIDEO_DEV  *BiosVideoChildPrivate
  )
/*++
Routing Description:

  Release resources of a video child device before stopping it.

Arguments:

  BiosVideoChildPrivate  -  Video child device private data structure

Returns:

    NONE
    
---*/
;

//
// BIOS Graphics Output Protocol functions
//
EFI_STATUS
EFIAPI
BiosVideoGraphicsOutputQueryMode (
  IN  EFI_GRAPHICS_OUTPUT_PROTOCOL          *This,
  IN  UINT32                                ModeNumber,
  OUT UINTN                                 *SizeOfInfo,
  OUT EFI_GRAPHICS_OUTPUT_MODE_INFORMATION  **Info
  )
/*++

Routine Description:

  Graphics Output protocol interface to get video mode

  Arguments:
    This                  - Protocol instance pointer.
    ModeNumber            - The mode number to return information on.
    Info                  - Caller allocated buffer that returns information about ModeNumber.
    SizeOfInfo            - A pointer to the size, in bytes, of the Info buffer.

  Returns:
    EFI_SUCCESS           - Mode information returned.
    EFI_BUFFER_TOO_SMALL  - The Info buffer was too small.
    EFI_DEVICE_ERROR      - A hardware error occurred trying to retrieve the video mode.
    EFI_NOT_STARTED       - Video display is not initialized. Call SetMode ()
    EFI_INVALID_PARAMETER - One of the input args was NULL.

--*/
;

EFI_STATUS
EFIAPI
BiosVideoGraphicsOutputSetMode (
  IN  EFI_GRAPHICS_OUTPUT_PROTOCOL * This,
  IN  UINT32                       ModeNumber
  )
/*++

Routine Description:

  Graphics Output protocol interface to set video mode

  Arguments:
    This             - Protocol instance pointer.
    ModeNumber       - The mode number to be set.

  Returns:
    EFI_SUCCESS      - Graphics mode was changed.
    EFI_DEVICE_ERROR - The device had an error and could not complete the request.
    EFI_UNSUPPORTED  - ModeNumber is not supported by this device.

--*/
;

EFI_STATUS
EFIAPI
BiosVideoGraphicsOutputVbeBlt (
  IN  EFI_GRAPHICS_OUTPUT_PROTOCOL       *This,
  IN  EFI_GRAPHICS_OUTPUT_BLT_PIXEL      *BltBuffer, OPTIONAL
  IN  EFI_GRAPHICS_OUTPUT_BLT_OPERATION  BltOperation,
  IN  UINTN                              SourceX,
  IN  UINTN                              SourceY,
  IN  UINTN                              DestinationX,
  IN  UINTN                              DestinationY,
  IN  UINTN                              Width,
  IN  UINTN                              Height,
  IN  UINTN                              Delta
  )
/*++

Routine Description:

  Graphics Output protocol instance to block transfer for VBE device

Arguments:

  This          - Pointer to Graphics Output protocol instance
  BltBuffer     - The data to transfer to screen
  BltOperation  - The operation to perform
  SourceX       - The X coordinate of the source for BltOperation
  SourceY       - The Y coordinate of the source for BltOperation
  DestinationX  - The X coordinate of the destination for BltOperation
  DestinationY  - The Y coordinate of the destination for BltOperation
  Width         - The width of a rectangle in the blt rectangle in pixels
  Height        - The height of a rectangle in the blt rectangle in pixels
  Delta         - Not used for EfiBltVideoFill and EfiBltVideoToVideo operation.
                  If a Delta of 0 is used, the entire BltBuffer will be operated on.
                  If a subrectangle of the BltBuffer is used, then Delta represents
                  the number of bytes in a row of the BltBuffer.

Returns:

  EFI_INVALID_PARAMETER - Invalid parameter passed in
  EFI_SUCCESS - Blt operation success

--*/
;

EFI_STATUS
EFIAPI
BiosVideoGraphicsOutputVgaBlt (
  IN  EFI_GRAPHICS_OUTPUT_PROTOCOL       *This,
  IN  EFI_GRAPHICS_OUTPUT_BLT_PIXEL      *BltBuffer, OPTIONAL
  IN  EFI_GRAPHICS_OUTPUT_BLT_OPERATION  BltOperation,
  IN  UINTN                              SourceX,
  IN  UINTN                              SourceY,
  IN  UINTN                              DestinationX,
  IN  UINTN                              DestinationY,
  IN  UINTN                              Width,
  IN  UINTN                              Height,
  IN  UINTN                              Delta
  )
/*++

Routine Description:

  Grahpics Output protocol instance to block transfer for VGA device

Arguments:

  This          - Pointer to Grahpics Output protocol instance
  BltBuffer     - The data to transfer to screen
  BltOperation  - The operation to perform
  SourceX       - The X coordinate of the source for BltOperation
  SourceY       - The Y coordinate of the source for BltOperation
  DestinationX  - The X coordinate of the destination for BltOperation
  DestinationY  - The Y coordinate of the destination for BltOperation
  Width         - The width of a rectangle in the blt rectangle in pixels
  Height        - The height of a rectangle in the blt rectangle in pixels
  Delta         - Not used for EfiBltVideoFill and EfiBltVideoToVideo operation.
                  If a Delta of 0 is used, the entire BltBuffer will be operated on.
                  If a subrectangle of the BltBuffer is used, then Delta represents
                  the number of bytes in a row of the BltBuffer.

Returns:

  EFI_INVALID_PARAMETER - Invalid parameter passed in
  EFI_SUCCESS - Blt operation success

--*/
;

//
// BIOS VGA Mini Port Protocol functions
//
EFI_STATUS
EFIAPI
BiosVideoVgaMiniPortSetMode (
  IN  EFI_VGA_MINI_PORT_PROTOCOL  *This,
  IN  UINTN                       ModeNumber
  )
/*++

Routine Description:

  VgaMiniPort protocol interface to set mode

Arguments:

  This        - Pointer to VgaMiniPort protocol instance
  ModeNumber  - The index of the mode

Returns:

  EFI_UNSUPPORTED - The requested mode is not supported
  EFI_SUCCESS - The requested mode is set successfully

--*/
;

//
// Standard VGA Definitions
//
#define VGA_HORIZONTAL_RESOLUTION                         640
#define VGA_VERTICAL_RESOLUTION                           480
#define VGA_NUMBER_OF_BIT_PLANES                          4
#define VGA_PIXELS_PER_BYTE                               8
#define VGA_BYTES_PER_SCAN_LINE                           (VGA_HORIZONTAL_RESOLUTION / VGA_PIXELS_PER_BYTE)
#define VGA_BYTES_PER_BIT_PLANE                           (VGA_VERTICAL_RESOLUTION * VGA_BYTES_PER_SCAN_LINE)

#define VGA_GRAPHICS_CONTROLLER_ADDRESS_REGISTER          0x3ce
#define VGA_GRAPHICS_CONTROLLER_DATA_REGISTER             0x3cf

#define VGA_GRAPHICS_CONTROLLER_SET_RESET_REGISTER        0x00

#define VGA_GRAPHICS_CONTROLLER_ENABLE_SET_RESET_REGISTER 0x01

#define VGA_GRAPHICS_CONTROLLER_COLOR_COMPARE_REGISTER    0x02

#define VGA_GRAPHICS_CONTROLLER_DATA_ROTATE_REGISTER      0x03
#define VGA_GRAPHICS_CONTROLLER_FUNCTION_REPLACE          0x00
#define VGA_GRAPHICS_CONTROLLER_FUNCTION_AND              0x08
#define VGA_GRAPHICS_CONTROLLER_FUNCTION_OR               0x10
#define VGA_GRAPHICS_CONTROLLER_FUNCTION_XOR              0x18

#define VGA_GRAPHICS_CONTROLLER_READ_MAP_SELECT_REGISTER  0x04

#define VGA_GRAPHICS_CONTROLLER_MODE_REGISTER             0x05
#define VGA_GRAPHICS_CONTROLLER_READ_MODE_0               0x00
#define VGA_GRAPHICS_CONTROLLER_READ_MODE_1               0x08
#define VGA_GRAPHICS_CONTROLLER_WRITE_MODE_0              0x00
#define VGA_GRAPHICS_CONTROLLER_WRITE_MODE_1              0x01
#define VGA_GRAPHICS_CONTROLLER_WRITE_MODE_2              0x02
#define VGA_GRAPHICS_CONTROLLER_WRITE_MODE_3              0x03

#define VGA_GRAPHICS_CONTROLLER_MISCELLANEOUS_REGISTER    0x06

#define VGA_GRAPHICS_CONTROLLER_COLOR_DONT_CARE_REGISTER  0x07

#define VGA_GRAPHICS_CONTROLLER_BIT_MASK_REGISTER         0x08

#endif
