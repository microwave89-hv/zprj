//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
//**********************************************************************
// $Header: /Alaska/BIN/Core/Include/Protocol/DevicePath.h 16    4/10/12 12:50p Artems $
//
// $Revision: 16 $
//
// $Date: 4/10/12 12:50p $
//*****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/Protocol/DevicePath.h $
// 
// 16    4/10/12 12:50p Artems
// EIP 87234: SCT devicepath test error - added support for SAS Ex device
// path
// 
// 15    10/20/11 7:01p Artems
// Added new DevicePath types as described in UEFI spec v.2.3.1
// 
// 14    5/05/11 12:05p Artems
// Added support for new device types. Minor changes done to reduce
// difference with EDKII 
// 
// 13    4/21/11 12:53p Artems
// EIP 58707: Added changes introduced in UEFI specification v. 2.3.1
// 
// 11    11/15/10 4:34p Felixp
// MSG_SATA_DP constant is added.
// 
// 10    28/02/08 7:38p Anandakrishnanl
// Added sata device path length definition
// 
// 9     3/19/07 2:21p Felixp
// 
// 8     1/17/07 9:54a Felixp
// New device path types added
// 
// 4     1/12/07 5:24p Felixp
// 
// 3     12/06/06 11:46a Vyacheslava
// 
// 6     5/19/06 10:20p Felixp
// SET_NODE_LENGTH & NODE_LENGTH macros added
// 
// 5     3/13/06 1:40a Felixp
// 
// 4     4/20/05 4:54p Andriyn
// USB_DEVICE_PATH added
// 
// 2     2/03/05 4:56p Felixp
// NEXT_NODE macros added
// 
// 1     1/28/05 12:44p Felixp
// 
// 2     1/18/05 3:21p Felixp
// PrintDebugMessage renamed to Trace
// 
// 1     12/23/04 9:41a Felixp
// 
// 17    12/22/04 11:10a Markw
// Added the rest of the device paths.
// 
// 16    12/21/04 5:53p Markw
// Added several device path structures.
// 
// 15    12/21/04 5:00p Markw
// Modified device path defines for consistency and added defines for all
// types and subtypes.
// 
// 14    12/21/04 4:21p Markw
// Renamed hardware device path definition for consistency and some more
// hardware paths.
// 
// 13    12/13/04 3:36p Markw
// Device Path checked erasing previous changes. Fixed. Added Vendor
// Define Device Path Terminal GUIDs.
// 
// 12    12/10/04 4:24p Felixp
// 
// 11    12/08/04 8:57a Radhikav
// Added UART Devicpath.

// 10    12/02/04 6:27p Markw
// Added Vendor Define Device Path and Terminal GUIDs.
// 
// 9     11/16/04 6:15p Robert
// Updated errors in the Hard drive device path and the cdrom device path
// structures
// 
// 8     10/11/04 5:54p Olegi
// 
// 7     10/01/04 5:46p Robert
// Added support for Hard drives and CDROM device paths
// 
// 6     9/27/04 12:09p Felixp
// 
// 5     7/16/04 3:57p Felixp
// Changes to support both 7f and ff values for the device path end type
// 
// 4     3/18/04 5:22p Markw
// Add memory mapped device path.
// 
// 3     2/17/04 4:38p Felixp
// Media device path added
// 
// 2     2/09/04 2:23p Markw
// header/typedef fixes
// 
// 1     2/09/04 1:25p Markw
// 
//*****************************************************************************
//<AMI_FHDR_START>
//
// Name:    DevicePath.h
//
// Description: This file is an include file used to define the Protocol and
//               definitions for the Device Path.
//
//<AMI_FHDR_END>
//*****************************************************************************

#ifndef __DEVICE_PATH_PROTOCOL_H__
#define __DEVICE_PATH_PROTOCOL_H__
#ifdef __cplusplus
extern "C" {
#endif
#include <EFI.h>

#define EFI_DEVICE_PATH_PROTOCOL_GUID \
    { 0x09576e91, 0x6d3f, 0x11d2, 0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b}

GUID_VARIABLE_DECLARATION(gEfiDevicePathProtocolGuid, EFI_DEVICE_PATH_PROTOCOL_GUID);

#define NODE_LENGTH(pPath) (*(UINT16*)&(pPath)->Length[0])
#define SET_NODE_LENGTH(pPath,Length) (NODE_LENGTH(pPath)=(Length))
#define NEXT_NODE(pPath) ((EFI_DEVICE_PATH_PROTOCOL*)((UINT8*)(pPath)+NODE_LENGTH(pPath)))

#define END_DEVICE_PATH                 0x7F
#define END_DEVICE_PATH1                0xFF
    #define END_INSTANCE_SUBTYPE            0x01
    #define END_ENTIRE_SUBTYPE              0xFF
    #define END_DEVICE_PATH_LENGTH          0x04

#define isEndNode(pDp) ((pDp)->Type==END_DEVICE_PATH||(pDp)->Type==END_DEVICE_PATH1)

#define HARDWARE_DEVICE_PATH            0x01
    #define HW_PCI_DP                       0x01
    #define HW_PCCARD_DP                    0x02
    #define HW_MEMMAP_DP                    0x03
    #define HW_VENDOR_DP                    0x04
    #define HW_CONTROLLER_DP                0x05
    #define HW_PCI_DEVICE_PATH_LENGTH       0x06

#define ACPI_DEVICE_PATH                0x02
    #define ACPI_DP                         0x01
    #define ACPI_DEVICE_PATH_LENGTH         0x0C
    #define ACPI_EXTENDED_DP                0x02
    #define ACPI_ADR_DP                     0x03

#define MESSAGING_DEVICE_PATH           0x03
    #define MSG_ATAPI_DP                    0x01
    #define MSG_SCSI_DP                     0x02
    #define MSG_FIBRECHANNEL_DP             0x03
    #define MSG_1394_DP                     0x04
    #define MSG_USB_DP                      0x05
    #define MSG_I2O_DP                      0x06
    #define MSG_INFINIBAND_DP               0x09
    #define MSG_VENDOR_DP                   0x0A
    #define MSG_MAC_ADDR_DP                 0x0B
    #define MSG_IPv4_DP                     0x0C
    #define MSG_IPv6_DP                     0x0D
    #define MSG_UART_DP                     0x0E
    #define MSG_USB_CLASS_DP                0x0F
    #define MSG_USB_WWID_CLASS_DP           0x10
    #define MSG_USB_LOGICAL_UNIT_CLASS_DP   0x11
    #define MSG_USB_SATA_DP                 0x12
    #define MSG_SATA_DP                     0x12
    #define MSG_ISCSI_DP                    0x13
    #define MSG_VLAN_DP                     0x14
    #define MSG_FIBRECHANNELEX_DP           0x15
    #define MSG_SASEX_DP                    0x16

    #define MSG_DEVICE_PATH_LENGTH          0x08
    #define ATAPI_DEVICE_PATH_LENGTH        0x08
    #define SATA_DEVICE_PATH_LENGTH         0x0A            
    #define UART_DEVICE_PATH_LENGTH         0x13

#define MEDIA_DEVICE_PATH               0x04
    #define MEDIA_HARDDRIVE_DP              0x01
    #define MEDIA_CDROM_DP                  0x02
    #define MEDIA_VENDOR_DP                 0x03
    #define MEDIA_FILEPATH_DP               0x04
    #define MEDIA_PROTOCOL_DP               0x05
    #define MEDIA_FV_FILEPATH_DP            0x06
    #define MEDIA_FV_DP                     0x07
    #define MEDIA_RELATIVE_OFFSET_RANGE_DP  0x08

//Does not follow our device path naming convensions but
//this is how it is defined in the CSM Spec
#define BBS_DEVICE_PATH                 0x05
    #define BBS_BBS_DP                      0x01

//EFI defined Vendor defined device path guids.
#define EFI_PC_ANSI_GUID \
    {0xe0c14753,0xf9be,0x11d2,0x9a,0x0c,0x00,0x90,0x27,0x3f,0xc1,0x4d}
#define EFI_VT_100_GUID \
    {0xdfa66065,0xb419,0x11d3,0x9a,0x2d,0x00,0x90,0x27,0x3f,0xc1,0x4d}
#define EFI_VT_100_PLUS_GUID \
    {0x7baec70b,0x57e0,0x4c76,0x8e,0x87,0x2f,0x9e,0x28,0x08,0x83,0x43}
#define EFI_VT_UTF8_GUID \
    {0xad15a0d6,0x8bec,0x4acf,0xa0,0x73,0xd0,0x1d,0xe7,0x7e,0x2d,0x88}
#define DEVICE_PATH_MESSAGING_UART_FLOW_CONTROL \
    {0x37499A9D,0x542F,0x4C89,0xA0,0x26,0x35,0xDA,0x14,0x20,0x94,0xE4}
#define EFI_SAS_PROTOCOL_GUID \
    {0xd487ddb4,0x008b,0x11d9,0xaf,0xdc,0x00,0x10,0x83,0xff,0xca,0x4d}
#define EFI_DEBUGPORT_PROTOCOL_GUID \
    {0xEBA4E8D2,0x3858,0x41EC,0xA2,0x81,0x26,0x47,0xBA,0x96,0x60,0xD0}

GUID_VARIABLE_DECLARATION(gEfiPcAnsiGuid, EFI_PC_ANSI_GUID);
GUID_VARIABLE_DECLARATION(gEfiVT100Guid, EFI_VT_100_GUID);
GUID_VARIABLE_DECLARATION(gEfiVT100PlusGuid, EFI_VT_100_PLUS_GUID);
GUID_VARIABLE_DECLARATION(gEfiVTUTF8Guid, EFI_VT_UTF8_GUID);
GUID_VARIABLE_DECLARATION(gEfiUartDevicePathGuid, DEVICE_PATH_MESSAGING_UART_FLOW_CONTROL);
GUID_VARIABLE_DECLARATION(gEfiSasDevicePathGuid, EFI_SAS_PROTOCOL_GUID);
GUID_VARIABLE_DECLARATION(gEfiDebugPortProtocolGuid, EFI_DEBUGPORT_PROTOCOL_GUID);

#pragma pack (push) //May not be alligned on a boundary.
#pragma pack (1)

//Hardware Device Path Type
typedef struct {
    EFI_DEVICE_PATH_PROTOCOL Header;
    UINT8                    Function;
    UINT8                    Device;
} PCI_DEVICE_PATH;

//Hardware Device Path Type
typedef struct {
    EFI_DEVICE_PATH_PROTOCOL Header;
    UINT8                    Function;
} PCCARD_DEVICE_PATH;

//Hardware Device Path Type
typedef struct {
    EFI_DEVICE_PATH_PROTOCOL Header;
    EFI_MEMORY_TYPE          MemoryType;
    EFI_PHYSICAL_ADDRESS     StartingAddress;
    EFI_PHYSICAL_ADDRESS     EndingAddress;
} MEMMAP_DEVICE_PATH;

//Hardware Device Path Type
typedef struct {
    EFI_DEVICE_PATH_PROTOCOL Header;
    EFI_GUID                 Guid;
    //Variable Length Vendor Defined Data
} VENDOR_DEVICE_PATH;
    
//Hardware Device Path Type
typedef struct {
    EFI_DEVICE_PATH_PROTOCOL Header;
    UINT32                   Controller;
} CONTROLLER_DEVICE_PATH;

//ACPI Device Path Type
typedef struct {
    EFI_DEVICE_PATH_PROTOCOL Header;
    UINT32                   HID;
    UINT32                   UID;
} ACPI_HID_DEVICE_PATH;

//ACPI Device Path Type
typedef struct {
    EFI_DEVICE_PATH_PROTOCOL Header;
    UINT32                   HID;
    UINT32                   UID;
    UINT32                   CID;
    //Variable Length _HIDSTR string
    //Variable Length _UIDSTR string
    //Variable Length _CIDSTR string
} ACPI_EXTENDED_HID_DEVICE_PATH;

#define PNP_EISA_ID_CONST         0x41d0
#define EISA_ID(_Name, _Num)      ((UINT32) ((_Name) | (_Num) << 16))
#define EISA_PNP_ID(_PNPId)       (EISA_ID(PNP_EISA_ID_CONST, (_PNPId)))
#define EFI_PNP_ID(_PNPId)        (EISA_ID(PNP_EISA_ID_CONST, (_PNPId)))

#define PNP_EISA_ID_MASK          0xffff
#define EISA_ID_TO_NUM(_Id)       ((_Id) >> 16)

//ACPI Address Device Path Type
typedef struct {
    EFI_DEVICE_PATH_PROTOCOL Header;
    UINT32                   ADR;
} ACPI_ADR_DEVICE_PATH;

//Messaging Device Path Type
typedef struct {
    EFI_DEVICE_PATH_PROTOCOL Header;
    UINT8                    PrimarySecondary;
    UINT8                    SlaveMaster;
    UINT16                   Lun;
} ATAPI_DEVICE_PATH;

//Messaging Device Path Type
typedef struct {
    EFI_DEVICE_PATH_PROTOCOL Header;
    UINT16                   Pun;
    UINT16                   Lun;
} SCSI_DEVICE_PATH;

//Messaging Device Path Type
typedef struct {
    EFI_DEVICE_PATH_PROTOCOL Header;
    UINT32                   Reserved;
    UINT64                   WWN;
    UINT64                   Lun;
} FIBRECHANNEL_DEVICE_PATH;

//Messaging Device Path Type
typedef struct {
    EFI_DEVICE_PATH_PROTOCOL Header;
    UINT32                   Reserved;
    UINT8                    WWN[8];
    UINT8                    Lun[8];
} FIBRECHANNELEX_DEVICE_PATH;

//Messaging Device Path Type
typedef struct {
    EFI_DEVICE_PATH_PROTOCOL Header;
    UINT32                   Reserved;
    UINT64                   Guid;       //Different than EFI_GUID.
} F1394_DEVICE_PATH;

//Messaging Device Path Type
typedef struct {
    EFI_DEVICE_PATH_PROTOCOL Header;
    UINT8                    ParentPortNumber;
    UINT8                    InterfaceNumber;
} USB_DEVICE_PATH;

//Messaging Device Path Type
typedef struct {
    EFI_DEVICE_PATH_PROTOCOL Header;
    UINT16                   VendorId;
    UINT16                   ProductId;
    UINT8                    DeviceClass;
    UINT8                    DeviceSubClass;
    UINT8                    DeviceProtocol;
} USB_CLASS_DEVICE_PATH;

//USB WWID Device Path
typedef struct {
    EFI_DEVICE_PATH_PROTOCOL Header;
    UINT16                   InterfaceNumber;
    UINT16                   VendorId;
    UINT16                   ProductId;
} USB_WWID_DEVICE_PATH;

// Device Logical Unit
typedef struct {
    EFI_DEVICE_PATH_PROTOCOL Header;
    UINT8                    Lun;
} LOGICAL_UNIT_DEVICE_PATH;

//SATA Device Path
typedef struct {
    EFI_DEVICE_PATH_PROTOCOL Header;
    UINT16                   PortNumber;
    UINT16                   MultiplierPortNumber;
    UINT16                   LogicalUnitNumber;
} SATA_DEVICE_PATH;

#define SATA_HBA_DIRECT_CONNECT_FLAG 0x8000

//iSCSI Device Path Node
typedef struct {
    EFI_DEVICE_PATH_PROTOCOL Header;
    UINT16                   NetworkProtocol;
    UINT16                   LoginOption;
    UINT64                   Lun;
    UINT16                   TargetPortalGroupTag;
    // CHAR8                 iSCSI Target Name
} iSCSI_DEVICE_PATH;

typedef struct {
    EFI_DEVICE_PATH_PROTOCOL Header;
    UINT16                   VlanId;
} VLAN_DEVICE_PATH;

//Serial Attached SCSI (SAS) Device Path
typedef struct {
    EFI_DEVICE_PATH_PROTOCOL Header;
    EFI_GUID                 Guid;
    UINT32                   Reserved;
    UINT64                   SasAddress;
    UINT64                   Lun;
    UINT16                   DeviceTopology;
    UINT16                   RelativeTargetPort;
} SAS_DEVICE_PATH;

//Serial Attached SCSI (SAS) Ex Device Path
typedef struct {
  EFI_DEVICE_PATH_PROTOCOL        Header;
  UINT8                           SasAddress[8];
  UINT8                           Lun[8];
  UINT16                          DeviceTopology;
  UINT16                          RelativeTargetPort;
} SASEX_DEVICE_PATH;

//Messaging Device Path Type
typedef struct {
    EFI_DEVICE_PATH_PROTOCOL Header;
    UINT32                   Tid;
} I20_DEVICE_PATH;

//Messaging Device Path Type
typedef struct {
    EFI_DEVICE_PATH_PROTOCOL Header;
    EFI_MAC_ADDRESS          MacAddr;
    UINT8                    IfType;
} MAC_ADDRESS_DEVICE_PATH;
    
//Messaging Device Path Type
typedef struct {
    EFI_DEVICE_PATH_PROTOCOL Header;
    EFI_IPv4_ADDRESS         LocalIpAddress;
    EFI_IPv4_ADDRESS         RemoteIpAddress;
    UINT16                   LocalPort;
    UINT16                   RemotePort;
    UINT16                   Protocol;
    BOOLEAN                  StaticIpAddress;
    EFI_IPv4_ADDRESS         GatewayIpAddress;
    EFI_IPv4_ADDRESS         SubnetMask;
} IPv4_DEVICE_PATH;

//Messaging Device Path Type
typedef struct {
    EFI_DEVICE_PATH_PROTOCOL Header;
    EFI_IPv6_ADDRESS         LocalIp;
    EFI_IPv6_ADDRESS         RemoteIp;
    UINT16                   LocalPort;
    UINT16                   RemotePort;
    UINT16                   Protocol;
    UINT8                    IpAddressOrigin;
    UINT8                    PrefixLength;
    EFI_IPv6_ADDRESS         GatewayIpAddress;
} IPv6_DEVICE_PATH;

//Messaging Device Path Type
typedef struct {
    EFI_DEVICE_PATH_PROTOCOL Header;
    UINT32                   ResourceFlags;
    UINT64                   PortGid[2];
    UINT64                   ServiceId;
    UINT64                   TargetPortId;
    UINT64                   DeviceId;
} INFINIBAND_DEVICE_PATH;

//Messaging Device Path Type
typedef struct {
    EFI_DEVICE_PATH_PROTOCOL Header;
    UINT32                   Reserved;
    UINT64                   BaudRate;
    UINT8                    DataBits;
    UINT8                    Parity;
    UINT8                    StopBits;
} UART_DEVICE_PATH;

//Messaging Device Path Type
typedef struct {
    EFI_DEVICE_PATH_PROTOCOL Header;
    EFI_GUID                 Guid;
    UINT32                   FlowControlMap;
} UART_FLOW_CONTROL_DEVICE_PATH;

//Media Device Path Type
typedef struct {
    EFI_DEVICE_PATH_PROTOCOL Header;
    UINT32                   PartitionNumber;
    UINT64                   PartitionStart;
    UINT64                   PartitionSize;
    UINT8                    Signature[16];
    UINT8                    MBRType;
    UINT8                    SignatureType;
} HARDDRIVE_DEVICE_PATH;

#define MBR_TYPE_MASTER_BOOT_RECORD             0x01
#define MBR_TYPE_EFI_PARTITION_TABLE_HEADER     0x02

#define SIGNATURE_TYPE_MBR        0x01
#define SIGNATURE_TYPE_GUID       0x02

//Media Device Path Type
typedef struct {
    EFI_DEVICE_PATH_PROTOCOL Header;
    UINT32                   BootEntry;
    UINT64                   PartitionStart;
    UINT64                   PartitionSize;
} CDROM_DEVICE_PATH;

//Media Device Path Type
typedef struct {
    EFI_DEVICE_PATH_PROTOCOL Header;
    CHAR16                   PathName[1];
} FILEPATH_DEVICE_PATH;

//Media Device Path Type
typedef struct {
    EFI_DEVICE_PATH_PROTOCOL Header;
    EFI_GUID                 NameGuid;
    //Variable Unicode Path String.
} MEDIA_FW_VOL_FILEPATH_DEVICE_PATH;

//Media Device Path Type
typedef struct {
    EFI_DEVICE_PATH_PROTOCOL Header;
    EFI_GUID                 ProtocolGuid;
} PROTOCOL_DEVICE_PATH;

// Media relative offset range device path.
typedef struct _{
    EFI_DEVICE_PATH_PROTOCOL Header;
    UINT32                   Reserved;
    UINT64                   StartingOffset;
    UINT64                   EndingOffset;
} MEDIA_RELATIVE_OFFSET_RANGE_DEVICE_PATH;

//BIOS Boot Specification Device Path
//Does not follow our device path naming convensions but
//this is how it is defined in the CSM Spec
typedef struct _BBS_BBS_DEVICE_PATH {
    EFI_DEVICE_PATH_PROTOCOL Header;
    UINT16                   DeviceType;
    UINT16                   StatusFlag;
    CHAR8                    String[1];
} BBS_BBS_DEVICE_PATH;
#pragma pack (pop)


/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
