//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             5555 Oakbrook Pkwy, Norcross, GA 30093               **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/HardwareSignatureManagement/Protocol/HardwareChangeProtocol.h 7     1/09/14 8:04a Albertlin $
//
// $Revision: 7 $
//
// $Date: 1/09/14 8:04a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/HardwareSignatureManagement/Protocol/HardwareChangeProtocol.h $
// 
// 7     1/09/14 8:04a Albertlin
// [TAG]           EIP147244
// [Category]      Not Specified
// [Description]   BIOS need to report changed hardware signature when
// BIOS setup was modified.
// [Files]         HardwareChangeProtocol.h
// 
// 6     3/01/13 3:34a Albertlin
// [TAG]           EIP115994
// [Category]      Improvement
// [Description]   Modify the comment for chm table.
// [Files]         HardwareChangeProtocol.h
// 
// 5     1/10/13 10:28p Albertlin
// [TAG]           EIP109014
// [Category]      Improvement
// [Description]   Currently, HardwareSignature module report signature by
// changed count.But it cause the same hardware may have different
// signature.
// For solve this issue, BIOS should report signature by hardware config.
// [Files]         HardwareChangeDetect.c HardwareSignatureManagement.c
// HardwareSignatureManagement.sdl HardwareChangeProtocol.h
// 
// 4     12/11/12 1:51a Sophiachen
// [TAG]  		EIP105523
// [Category]  	New Feature
// [Description]  	Record the disk configuration data to check the
// connection change of disk.
// [Files]  		HardwareChangeDetect.c, HardwareSignatureManagement.c,
// HardwareChangeProtocol.h
// 
// 3     11/20/12 8:20a Sophiachen
// [TAG]  		EIP105154
// [Category]  	New Feature
// [Description]  	Record the video configuration data to check the
// connection change of monitor.
// [Files]  		HardwareChangeDetect.c, HardwareSignatureManagement.c,
// HardwareChangeProtocol.h
// 
// 2     10/18/12 7:53a Sophiachen
// 
// 1     9/25/12 8:58a Sophiachen
// [TAG]  		EIP96258
// [Category]  	New Feature
// [Description]  	Update the Hardware Signature of the ACPI table FACS
// field can notify ACPI OS whether any hardware configuration change.
// [Files]  		HardwareChangeProtocols.cif
// Protocol\HardwareChangeProtocol.h
//
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:    HardwareChangeProtocol.h
//
// Description: The header file for Hardware change protocol. 
//
//<AMI_FHDR_END>
//**********************************************************************

#ifndef __HARDWARE_CHANGE_PROTOCOL__H__
#define __HARDWARE_CHANGE_PROTOCOL__H__

#ifdef __cplusplus
extern "C" {
#endif

// {43169678-506C-46fe-B32A-FCB301F74FBD}
#define HARDWARE_CHANGE_PROTOCOL_GUID \
   { 0x43169678, 0x506c, 0x46fe, 0xb3, 0x2a, 0xfc, 0xb3, 0x1, 0xf7, 0x4f, 0xbd  }

// {B80A8E5B-C02A-4a31-AE12-58E46E803E89}
#define HARDWARE_CONFIG_DATA_GUID \
   { 0xb80a8e5b, 0xc02a, 0x4a31,  0xae, 0x12, 0x58, 0xe4, 0x6e, 0x80, 0x3e, 0x89  }

// {e08126e5-b93c-4f5e-8e81-6dfcf34ff88e}
#define FIRMWARE_UPDATE_COUNT_GUID \
   { 0xe08126e5, 0xb93c, 0x4f5e, 0x8e, 0x81, 0x6d, 0xfc, 0xf3, 0x4f, 0xf8, 0x8e }

//<EIP147244 >
// {81c76078-bfde-4368-9790-570914c01a65}
#define SETUP_UPDATE_COUNT_GUID \
   { 0x81c76078, 0xbfde, 0x4368, 0x97, 0x90, 0x57, 0x09, 0x14, 0xc0, 0x1a, 0x65 }

#define SETUP_UPDATE_COUNT_VARIABLE L"SetUpdateCountVar"
//EFI_GUID  gSetupUpdateCountGuid = SETUP_UPDATE_COUNT_GUID;
//<EIP147244 >

#define HW_CHANGE_PS2_KEYBOARD       BIT0
#define HW_CHANGE_PS2_MOUSE          BIT1
#define HW_CHANGE_MEMORY_SIZE_CONFIG BIT2
#define HW_CHANGE_MEMORY_MAP_CONFIG  BIT3
#define HW_CHANGE_PCI_CONFIG         BIT4
#define HW_CHANGE_USB_CONFIG         BIT5
#define HW_CHANGE_VIDEO_CONFIG       BIT6
#define HW_CHANGE_DISK_CONFIG        BIT7
//For limit the protocol be called
#define LIMIT_PROTOCOL_CALLED 20

#if HARDWARE_SIGNATURE_DEBUG_MESSAGES
#define HWSIG_TRACE(Arguments) TRACE(Arguments)
#else
#define HWSIG_TRACE(Arguments)
#endif

typedef enum {
  Ps2KeyboardConfigType,
  Ps2MouseConfigType,
  MemorySizeConfigType,
  MemoryMapConfigType,
  PciConfigType,
  UsbConfigType,
  VideoConfigType,
  DiskConfigType,
  MaxConfigType
} HW_CONFIG_TYPE;

#pragma pack (push,1)

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name: HW_MEMORY_MAP_DATA
//
// Description: This structure represents the memory map data which contains
// memory size(Megabyte) and checksum of the runtime memory type.
//
// Fields: Name             Type        Description
//   ------------------------------------------------------------------
//  MemMapCheckSum          UINT8       Checksum of the runtime memory type
//  MemoryMbSize            UINT32      Total memory size(Megabyte)
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
typedef struct _HW_MEMORY_MAP_DATA {
  UINT8   MemMapCheckSum;
  UINT32  MemoryMbSize;
} HW_MEMORY_MAP_DATA;

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name: HW_PCI_DATA
//
// Description: This structure represents the PCI configuration data which 
// contains number of PCI/PCIE devices, checksum of Bus number/Device number/ 
// Function number, and checksum of VID/DID.
//
// Fields: Name             Type        Description
//   ------------------------------------------------------------------
//  PciNum                  UINT16      Number of PCI/PCIE devices 
//  BdfChecksum             UINT8       Checksum of Bus number/Device number/Function number 
//  VidDidChecksum          UINT8       Checksum of VID/DID
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
typedef struct _HW_PCI_DATA {
  UINT16  PciNum;
  UINT8   BdfChecksum;
  UINT8   VidDidChecksum;
} HW_PCI_DATA;

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name: HW_USB_DATA
//
// Description: This structure represents the USB configuration data which 
// contains number of USB devices, checksum of VID/PID, and checksum of Port  
// number and Interface number.
//
// Fields: Name                       Type        Description
//   ------------------------------------------------------------------
//  UsbNum                            UINT16      Number of USB devices
//  VidPidChecksum                    UINT8       Checksum of VID/PID
//  PortNumInterfaceNumChecksum       UINT8       Checksum of Port number and Interface number
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
typedef struct _HW_USB_DATA {
  UINT16  UsbNum;
  UINT8   VidPidChecksum;
  UINT8   PortNumInterfaceNumChecksum;
} HW_USB_DATA;

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name: HW_VIDEO_DATA
//
// Description: This structure represents the Video configuration data which 
// contains checksum of EDID data, and checksum of resolution.  
//
// Fields: Name                       Type        Description
//   ------------------------------------------------------------------
//  EdidCheckNum                      UINT8       Checksum of EDID data
//  ResolutionChecksum                UINT8       Checksum of resolution
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
typedef struct _HW_VIDEO_DATA {
  UINT8   EdidCheckNum;
  UINT8   ResolutionChecksum;
} HW_VIDEO_DATA;

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name: HW_DISK_DATA
//
// Description: This structure represents the Disk configuration data with checksum.
//
// Fields: Name                    Type        Description
//   ------------------------------------------------------------------
//  CDSchecksum                    UINT8       Checksum
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
typedef struct _HW_DISK_DATA {
  UINT32	CDSchecksum;
} HW_DISK_DATA;

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name: DISK_STRUCTURE
//
// Description: This structure represents the Disk configuration data which 
// contains port number and serial number .
//
// Fields: Name                    Type        Description
//   ------------------------------------------------------------------
//  Portnumber                     UINT8       Port number
//  Serialnumber                   UINT8       Serial number
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
typedef struct _DISK_STRUCTURE {
  UINT8		Portnumber;
  UINT8		Serialnumber[20];
} DISK_STRUCTURE;

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name: HW_CONFIG_DATA
//
// Description: This structure represents the hardware configuration data 
// which contains PS2 Keyboard/Mouse configuration, Memory Map configuration,  
// PCI configuration Data, USB configuration Data,  Video configuration data, 
// Disk configuration data, Firmware update times, and Checksum which external 
// function given.
//
// Fields: Name         Type                  Description
//   ------------------------------------------------------------------
//  bPs2Keyboard        BOOLEAN               The present state of PS2 Keyboard
//  bPs2Mouse           BOOLEAN               The present state of PS2 Mouse
//  MemMapData          HW_MEMORY_MAP_DATA    Memory configuration data            
//  PciData             HW_PCI_DATA           PCI configuration data 
//  UsbData             HW_USB_DATA           USB configuration data      
//  VideoData           HW_VIDEO_DATA         Video configuration data
//  DiskData            HW_DISK_DATA          Disk configuration data
//  FirmwareUpdateCount UINT32                Firmware update count
//  ReturnChecksum      UINT32                Checksum which the external function given
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
typedef struct _HW_CONFIG_DATA {
  BOOLEAN bPs2Keyboard;
  BOOLEAN bPs2Mouse;  
  HW_MEMORY_MAP_DATA MemMapData;
  HW_PCI_DATA PciData;
#if HARDWARE_SIGNATURE_USB_CHANGE  
  HW_USB_DATA UsbData;
#endif
  HW_VIDEO_DATA VideoData;
  HW_DISK_DATA DiskData;
  UINT32 FirmwareUpdateCount;
//<EIP147244 >  
  UINT32 SetupUpdateCount;
//<EIP147244 >
  UINT32 ReturnChecksum[LIMIT_PROTOCOL_CALLED];
} HW_CONFIG_DATA;
#pragma pack (pop)

typedef 
EFI_STATUS (EFIAPI *SET_HW_CONFIG_DATA) (
    IN HW_CONFIG_TYPE ConfigType, 
    IN UINTN BufferSize,
    IN VOID *Buffer
);

typedef 
EFI_STATUS (EFIAPI *GET_HW_CONFIG_DATA_FROM_NVRAM) (
    IN OUT HW_CONFIG_DATA *HardwareConfigData
);

typedef 
EFI_STATUS (EFIAPI *SIGNAL_HW_SIGNATURE_CHANGE) (
    IN UINT32 ReturnChecksum
);
  
typedef struct {
    SET_HW_CONFIG_DATA             SetHardwareConfigData;
    GET_HW_CONFIG_DATA_FROM_NVRAM  GetHardwareConfigDataFromNvram;
    SIGNAL_HW_SIGNATURE_CHANGE     SignalHardwareSignatureChange;
} EFI_HARDWARE_CHANGE_PROTOCOL;

EFI_STATUS SetHardwareConfigData(
    IN HW_CONFIG_TYPE ConfigType, 
    IN UINTN BufferSize,
    IN VOID *Buffer
);

EFI_STATUS GetHardwareConfigDataFromNvram(
    IN OUT HW_CONFIG_DATA *HardwareConfigData
);

EFI_STATUS SignalHardwareSignatureChange( 
	IN UINT32 ReturnChecksum );

UINT32 CRC32 (
    IN UINT8  *fpData,
    IN UINT16 Length,
    IN UINT8  ExtenData 
);


/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             5555 Oakbrook Pkwy, Norcross, GA 30093               **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
